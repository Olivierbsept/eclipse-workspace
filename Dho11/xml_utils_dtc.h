/*
 * xml_utils.h
 *
 *  Created on: 29 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef XML_UTILS_H_
#define XML_UTILS_H_

#include <stdint.h>
#include "rtwtypes.h"
void start_xml(const char* filename);
void append_to_xml_dtc(const char* filename, uint32_T dtc, uint8_T state);
void Store_dtc(const char* filename, uint32_T dtc, uint8_T state);

#endif /* XML_UTILS_H_ */
