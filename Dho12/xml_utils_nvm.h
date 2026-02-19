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
void start_xml_nvm(const char* filename);
void Store_nvm(const char* filename, uint32 mnbu, uint16 mtbu, uint32 mhbu, uint8 ecuname, uint16 mtf, uint32 mnf, uint16 mtl, uint32 mnl);
void append_to_xml_nvm(const char* filename, uint32 mn, uint16 mt, uint32 mh, uint8 ecuname, uint16 mtf, uint32 mnf, uint16 mtl, uint32 mnl);
uint16 Read_mtf(const char* filename);
uint16 Read_mtl(const char* filename);
uint32 Read_mnf(const char* filename);
uint32 Read_mnl(const char* filename);
uint32 Read_mhbu(const char* filename);
uint16 Read_mtbu(const char* filename);
uint32 Read_mnbu(const char* filename);
uint8 Read_ecuname(const char* filename);
#endif /* XML_UTILS_H_ */
