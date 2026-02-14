// hex_patch.cpp
// Compile: g++ -std=c++11 -O2 -o hex_patch hex_patch.cpp
// Usage: ./hex_patch input.hex output.hex
//
// Remplace pattern 00 40 AD 10 00 xx -> 00 40 AD 10 00 10
// Recalcule checksums de lignes et met à jour CRC32 (little-endian) aux adresses 0x806BC02C..0x806BC02F
// CRC calculé sur la plage 0x806A0000 .. 0x806BC02B inclusive.
#include <stdint.h> // nécessaire pour uint32_t
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

// === CONFIG ===
const uint32_t RANGE_START = 0x806A0000u;
const uint32_t RANGE_END   = 0x806BFFFFu;
const uint32_t CRC_ADDR    = 0x806BC02Cu; // where CRC is stored (4 bytes)
const uint32_t CRC_RANGE_END = 0x806BC02Bu; // CRC computed from RANGE_START..CRC_RANGE_END inclusive

// Pattern to find: 00 40 AD 10 00 xx  -> replace last byte by 0x10
const uint8_t PAT_PREFIX[5] = { 0x00, 0x40, 0xAD, 0x10, 0x00 };
const uint8_t PAT_REPLACE_BYTE = 0x10;

// Endianness for writing CRC: little-endian if true
const bool CRC_LITTLE_ENDIAN = true;

// === Helpers ===
static inline int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

static bool parseHexByte(const std::string &s, size_t pos, uint8_t &out) {
    if (pos + 1 >= s.size()) return false;
    int hi = hexCharToInt(s[pos]);
    int lo = hexCharToInt(s[pos+1]);
    if (hi < 0 || lo < 0) return false;
    out = (uint8_t)((hi << 4) | lo);
    return true;
}

static std::string byteToHex(uint8_t b) {
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}

// CRC32 (IEEE 802.3) table
static uint32_t crc_table[256];
static void init_crc32_table() {
    const uint32_t poly = 0xEDB88320u;
    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t crc = i;
        for (int j = 0; j < 8; ++j) {
            if (crc & 1) crc = (crc >> 1) ^ poly;
            else crc = crc >> 1;
        }
        crc_table[i] = crc;
    }
}

static uint32_t crc32(const uint8_t* data, size_t len) {
    uint32_t crc = 0xFFFFFFFFu;
    for (size_t i = 0; i < len; ++i) {
        uint8_t idx = (uint8_t)((crc ^ data[i]) & 0xFFu);
        crc = (crc >> 8) ^ crc_table[idx];
    }
    return crc ^ 0xFFFFFFFFu;
}

// === Main processing ===

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::fprintf(stderr, "Usage: %s input.hex output.hex\n", argv[0]);
        return 1;
    }

    std::string inPath = argv[1];
    std::string outPath = argv[2];

    // Read all input lines
    std::vector<std::string> lines;
    {
        std::ifstream ifs(inPath);
        if (!ifs) {
            std::perror(("Cannot open input file: " + inPath).c_str());
            return 2;
        }
        std::string line;
        while (std::getline(ifs, line)) {
            // trim possible CR at line end
            if (!line.empty() && line.back() == '\r') line.pop_back();
            lines.push_back(line);
        }
    }

    // Parse Intel HEX into a memory map (uint32 -> byte)
    // We'll also remember data record positions to regenerate lines later.
    std::map<uint32_t, uint8_t> mem; // sparse map of bytes
    struct DataRecordInfo {
        size_t lineIndex;
        uint32_t absAddr;
        uint8_t len;
    };
    std::vector<DataRecordInfo> dataRecords; // in file order

    uint32_t curr_ext_linear = 0;
    uint32_t curr_ext_segment = 0; // for record type 02
    for (size_t li = 0; li < lines.size(); ++li) {
        const std::string &ln = lines[li];
        if (ln.empty()) continue;
        if (ln[0] != ':') continue;

        // minimal length check
        if (ln.size() < 11) continue;

        uint8_t rec_len = 0;
        if (!parseHexByte(ln, 1, rec_len)) continue;
        uint8_t addr_hi = 0, addr_lo = 0;
        if (!parseHexByte(ln, 3, addr_hi)) continue;
        if (!parseHexByte(ln, 5, addr_lo)) continue;
        uint16_t addr16 = (uint16_t)((addr_hi << 8) | addr_lo);
        uint8_t rectype = 0;
        if (!parseHexByte(ln, 7, rectype)) continue;

        if (rectype == 0x00) {
            // data record
            uint32_t base_addr = (curr_ext_linear << 16) + (curr_ext_segment << 4) + addr16;
            // read data bytes
            std::vector<uint8_t> data;
            data.reserve(rec_len);
            size_t pos = 9;
            for (int i=0;i<rec_len;i++) {
                uint8_t b;
                if (!parseHexByte(ln, pos, b)) { data.clear(); break; }
                data.push_back(b);
                pos += 2;
            }
            if ((size_t)rec_len == data.size()) {
                for (uint8_t i = 0; i < rec_len; ++i) {
                    mem[base_addr + i] = data[i];
                }
                DataRecordInfo info;
                info.lineIndex = li;
                info.absAddr = base_addr;
                info.len = rec_len;
                dataRecords.push_back(info);
            }
        } else if (rectype == 0x04) {
            // extended linear address
            // two data bytes give upper 16 bits
            if (rec_len >= 2 && ln.size() >= 13) {
                uint8_t b1,b2;
                parseHexByte(ln, 9, b1);
                parseHexByte(ln, 11, b2);
                curr_ext_linear = ((uint32_t)b1 << 8) | (uint32_t)b2;
                curr_ext_segment = 0;
            }
        } else if (rectype == 0x02) {
            // extended segment address
            if (rec_len >= 2 && ln.size() >= 13) {
                uint8_t b1,b2;
                parseHexByte(ln, 9, b1);
                parseHexByte(ln, 11, b2);
                curr_ext_segment = ((uint32_t)b1 << 8) | (uint32_t)b2;
                curr_ext_linear = 0;
            }
        } else {
            // other record types: ignore for mem filling
        }
    }

    // Build contiguous buffer for the interest region (RANGE_START .. RANGE_END)
    if (RANGE_END < RANGE_START) {
        std::fprintf(stderr, "Invalid range\n");
        return 3;
    }
    size_t region_size = (size_t)(RANGE_END - RANGE_START + 1);
    std::vector<uint8_t> region(region_size, 0xFF); // default fill 0xFF

    for (auto it = mem.lower_bound(RANGE_START); it != mem.end() && it->first <= RANGE_END; ++it) {
        uint32_t addr = it->first;
        uint8_t val = it->second;
        region[addr - RANGE_START] = val;
    }

    // SEARCH & REPLACE across the region
    size_t pat_len = 6; // prefix 5 + last byte
    size_t replaced_count = 0;
    for (size_t i = 0; i + pat_len - 1 < region.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < 5; ++j) {
            if (region[i + j] != PAT_PREFIX[j]) { match = false; break; }
        }
        if (!match) continue;
        // found prefix; check sixth byte; we replace it to 0x10 regardless of its current value (but only if different)
        if (region[i + 5] != PAT_REPLACE_BYTE) {
            region[i + 5] = PAT_REPLACE_BYTE;
            ++replaced_count;
        }
    }
    std::printf("Replaced %zu occurrences of pattern (modified sixth byte to 0x%02X)\n", replaced_count, PAT_REPLACE_BYTE);

    // Update the mem map from the region (so regeneration uses updated bytes)
    for (size_t k = 0; k < region_size; ++k) {
        uint32_t addr = RANGE_START + (uint32_t)k;
        mem[addr] = region[k];
    }

    // Compute CRC32 over RANGE_START..CRC_RANGE_END inclusive
    if (CRC_RANGE_END < RANGE_START || CRC_ADDR + 3 > RANGE_END) {
        std::fprintf(stderr, "CRC addresses out of range, aborting\n");
        return 4;
    }
    // build buffer for CRC region
    size_t crc_len = (size_t)(CRC_RANGE_END - RANGE_START + 1);
    std::vector<uint8_t> crc_buf;
    crc_buf.reserve(crc_len);
    for (size_t i = 0; i < crc_len; ++i) crc_buf.push_back(region[i]);

    init_crc32_table();
    uint32_t crc = crc32(crc_buf.data(), crc_buf.size());
    std::printf("Computed CRC32 = 0x%08X\n", crc);

    // write CRC bytes into region at CRC_ADDR
    uint32_t crc_offset = CRC_ADDR - RANGE_START;
    if (crc_offset + 4 > region.size()) {
        std::fprintf(stderr, "CRC write out of range\n");
        return 5;
    }
    if (CRC_LITTLE_ENDIAN) {
        region[crc_offset + 0] = (uint8_t)(crc & 0xFFu);
        region[crc_offset + 1] = (uint8_t)((crc >> 8) & 0xFFu);
        region[crc_offset + 2] = (uint8_t)((crc >> 16) & 0xFFu);
        region[crc_offset + 3] = (uint8_t)((crc >> 24) & 0xFFu);
    } else {
        region[crc_offset + 0] = (uint8_t)((crc >> 24) & 0xFFu);
        region[crc_offset + 1] = (uint8_t)((crc >> 16) & 0xFFu);
        region[crc_offset + 2] = (uint8_t)((crc >> 8) & 0xFFu);
        region[crc_offset + 3] = (uint8_t)(crc & 0xFFu);
    }

    // Update mem map with CRC-modified bytes
    for (size_t k = 0; k < region_size; ++k) {
        uint32_t addr = RANGE_START + (uint32_t)k;
        mem[addr] = region[k];
    }

    // BACKUP original file
    std::string backupPath = inPath + ".bak";
    if (std::rename(inPath.c_str(), backupPath.c_str()) != 0) {
        // If rename fails, proceed but warn
        std::perror(("Warning: couldn't create backup " + backupPath).c_str());
    } else {
        std::printf("Backup saved to %s\n", backupPath.c_str());
    }

    // Re-generate output lines: for data records replace data bytes and checksum using mem map
    std::ofstream ofs(outPath);
    if (!ofs) {
        std::perror(("Cannot open output file: " + outPath).c_str());
        return 6;
    }

    curr_ext_linear = 0;
    curr_ext_segment = 0;
    for (size_t li = 0; li < lines.size(); ++li) {
        const std::string &ln = lines[li];
        if (ln.empty() || ln[0] != ':') {
            ofs << ln << "\n";
            continue;
        }
        // parse header
        uint8_t rec_len = 0;
        if (!parseHexByte(ln, 1, rec_len)) { ofs << ln << "\n"; continue; }
        uint8_t addr_hi = 0, addr_lo = 0;
        if (!parseHexByte(ln, 3, addr_hi) || !parseHexByte(ln, 5, addr_lo)) { ofs << ln << "\n"; continue; }
        uint16_t addr16 = (uint16_t)((addr_hi << 8) | addr_lo);
        uint8_t rectype = 0;
        if (!parseHexByte(ln, 7, rectype)) { ofs << ln << "\n"; continue; }

        if (rectype == 0x00) {
            // data record, rebuild data using mem
            uint32_t base_addr = (curr_ext_linear << 16) + (curr_ext_segment << 4) + addr16;
            // collect bytes
            std::vector<uint8_t> data;
            for (uint8_t i = 0; i < rec_len; ++i) {
                uint32_t a = base_addr + i;
                uint8_t b = 0xFF;
                auto it = mem.find(a);
                if (it != mem.end()) b = it->second;
                data.push_back(b);
            }
            // compute checksum: sum of len + addr_hi + addr_lo + rectype + data bytes, then two's complement
            uint32_t sum = 0;
            sum += rec_len;
            sum += (addr16 >> 8) & 0xFF;
            sum += addr16 & 0xFF;
            sum += rectype;
            for (uint8_t b : data) sum += b;
            uint8_t checksum = (uint8_t)((~sum + 1) & 0xFFu);

            // build line
            std::ostringstream oss;
            oss << ":" << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)rec_len;
            oss << std::setw(4) << std::setfill('0') << (int)addr16;
            oss << std::setw(2) << (int)rectype;
            for (uint8_t b : data) {
                oss << std::setw(2) << (int)b;
            }
            oss << std::setw(2) << (int)checksum;
            ofs << oss.str() << "\n";
        } else {
            // keep line but update extended address trackers
            if (rectype == 0x04) {
                // update curr_ext_linear from data bytes
                uint8_t b1=0,b2=0;
                parseHexByte(ln, 9, b1);
                parseHexByte(ln, 11, b2);
                curr_ext_linear = ((uint32_t)b1 << 8) | (uint32_t)b2;
                curr_ext_segment = 0;
            } else if (rectype == 0x02) {
                uint8_t b1=0,b2=0;
                parseHexByte(ln, 9, b1);
                parseHexByte(ln, 11, b2);
                curr_ext_segment = ((uint32_t)b1 << 8) | (uint32_t)b2;
                curr_ext_linear = 0;
            }
            ofs << ln << "\n";
        }
    }

    ofs.close();
    std::printf("Wrote modified hex to %s\n", outPath.c_str());
    return 0;
}
