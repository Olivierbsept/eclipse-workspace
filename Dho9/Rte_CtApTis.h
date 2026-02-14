/*
 * Rte_CtApTis.h
 *
 *  Created on: 28 sept. 2025
 *      Author: olivierbessettemac
 */
#include "rtwtypes.h"

#ifndef RTE_CTAPTIS_H_
#define RTE_CTAPTIS_H_

typedef struct {
    uint8_T major;
    uint8_T middle;
    uint8_T minor;
} SG_ModuleVersion;

SG_ModuleVersion moduleVersion;
boolean MachineTimeReducedOnce;
boolean irv_StartRecvOpHours;

#endif /* RTE_CTAPTIS_H_ */
