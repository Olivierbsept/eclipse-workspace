
#include "Dho3.h"
#include "xml_utils.h"

const char* filename_Vbm = "data.xml";
const char* filename_Fum = "data_Fum.xml";
const char* filename_Ram = "data_Ram.xml";

EemStates currentEemState = ST_GeneratorOn;
bool flagDiag = false;
const uint16_t	TIMEOUT_5S = 500;
const uint8_t 	DEBOUNCE_3x=3;
const uint16_t	SYNCRATE_1s=100;
const uint16_t	UNSYNCRATE_2s=200;
const uint16_t	THRESHRATE_100ms=10;
const uint16_t	SLOWRATE_1500ms=150;
const uint16_t	READYTOSTARTRATE_1s=100;
const uint16_t	PERIOD_MSGID_5s=500;
const uint16_t	PERIOD_STORE_5s=500;

int main(void) {
    start_xml(filename_Vbm);
    start_xml(filename_Fum);
    start_xml(filename_Ram);

    VbmInit();
    FumInit();
    RamInit();

    while (true) {
        usleep(10000); // 10 ms
        Vbm_step10ms();
        Fum_step10ms();
        Ram_step10ms();
    }
}
