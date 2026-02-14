/*
 * Fum.h
 *
 *  Created on: 28 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef FUM_H_
#define FUM_H_


//#include <stdint.h>
#include "TIS_modelIO.h"
#include "xml_utils.h"
#include <string.h>// ✅ Ajout nécessaire pour memcpy
#include "Can.h"
#include "Can_bus.h"

#define uint8_T uint8_t
#define uint16_T uint16_t
#define uint32_T uint32_t

extern void Tis_initialize(void);
extern void Tis_step_50ms(void);
extern const char* filename_Fum;

extern uint32_t IdFumConfig;
extern uint32_t IdFumHour;
extern uint32_t IdVbmConfig;
extern uint32_t IdVbmHour;
extern uint32_t IdLimConfig;
extern uint32_t IdLimHour;

static uint32_T compteurStep50ms = 0;
static const uint16_t PERIOD_STORE50ms_5s = 100;
static CAN_Bus *pcan_bus;

#endif /* FUM_H_ */
