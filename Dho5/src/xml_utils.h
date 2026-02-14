/*
 * xml_utils.h
 *
 *  Created on: 29 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef XML_UTILS_H_
#define XML_UTILS_H_

#include <stdint.h>

void start_xml(const char* filename);
void append_to_xml(const char* filename, uint32_t mn, uint16_t mt, uint32_t mh);
void Store(const char* filename, uint32_t mn, uint16_t mt, uint32_t mh);

#endif /* XML_UTILS_H_ */
