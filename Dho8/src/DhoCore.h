/*
 * DhoCore.h
 *
 *  Created on: 9 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef SRC_DHOCORE_H_
#define SRC_DHOCORE_H_

#include "DhoCommun.h"

void Call50msDho_Vbm(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call50msDho_Fum(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call50msDho_Lim(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call50msDho_Vbm_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call50msDho_Fum_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call50msDho_Lim_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void InitDho_Vbm(Configs configs);

static const uint16_t	TIMEOUT50ms_5S =			100;
static const uint8_t	DEBOUNCE_3x =				3;
static const uint16_t	SYNCRATE50ms_1s=			20;
static const uint16_t	UNSYNCRATE50ms_2s=			40;
static const uint16_t	THRESHRATE50ms_100ms=		2;
static const uint16_t	SLOWRATE50ms_1500ms=		30;
static const uint16_t	READYTOSTARTRATE50ms_1s=	20;

typedef struct{
	uint32_t cc_50ms,cc1_50ms,cc2_50ms;
	uint16_t per_50ms;
	uint8_t counterDebounce1;
	bool rxSlow1, rxTooSlow1, rxTooSlow2, paramCheckCfg, diagTrigCfg;
} EcuStruct;

static EcuStruct ecuVbm, ecuFum, ecuLim;
static void Call50msDho(EcuStruct* ecu,Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
static void Call50msDho_Diag(EcuStruct* ecu,Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);

#endif /* SRC_DHOCORE_H_ */
