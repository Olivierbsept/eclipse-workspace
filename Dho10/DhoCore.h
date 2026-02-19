/*
 * DhoCore.h
 *
 *  Created on: 9 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef SRC_DHOCORE_H_
#define SRC_DHOCORE_H_

#include "DhoCommun.h"


void DhoCall_100ms_Ecu1(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Ecu2(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Diag_Ecu1(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Diag(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Diag_Ecu2(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoInit_Ecu1(DhoConfigs configs);
void DhoInit_Fum(DhoConfigs configs);
void DhoInit_Lim(DhoConfigs configs);

static const uint16_T	TIMEOUT100ms_5S =			50;
static const uint8_T	DEBOUNCE_3x =				3;
static const uint16_T	SYNCRATE100ms_1s=			10;
static const uint16_T	UNSYNCRATE100ms_2s=			20;
static const uint16_T	THRESHRATE100ms_100ms=		1;
static const uint16_T	SLOWRATE100ms_1500ms=		15;
static const uint16_T	SLOWRATE100ms_1500msBelow = 14;
static const uint16_T	READYTOSTARTRATE100ms_2s = 	20;
static const uint16_T	READYTOSTARTRATE100ms_2sBelow = 19;

typedef struct{
	uint32_T cc_100ms,cc1_100ms,cc2_100ms;
	uint16_T per_100ms;
	uint8_T counterDebounce1;
	boolean_T rxSlow1, rxTooSlow1, rxTooSlow2, paramCheckCfg, diagTrigCfg;
} EcuStruct;

static EcuStruct ecu1, ecu0, ecu2;
static void DhoCall_100ms_Ecu(EcuStruct* ecu,DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
static void DhoCall_100ms_Diag_Ecu(EcuStruct* ecu,DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);

#endif /* SRC_DHOCORE_H_ */
