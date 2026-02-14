/*
 * DhoCore.h
 *
 *  Created on: 9 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef SRC_DHOCORE_H_
#define SRC_DHOCORE_H_

#include "VbmDhoCommun.h"

void Call100msDho_Vbm(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call100msDho_Fum(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call100msDho_Lim(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call100msDho_Vbm_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call100msDho_Fum_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void Call100msDho_Lim_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
void InitDho_Vbm(Configs configs);

static const uint16_t	TIMEOUT100ms_5S =			50;
static const uint8_t	DEBOUNCE_3x =				3;
static const uint16_t	SYNCRATE100ms_1s=			10;
static const uint16_t	UNSYNCRATE100ms_2s=			20;
static const uint16_t	THRESHRATE100ms_100ms=		1;
static const uint16_t	SLOWRATE100ms_1500ms=		15;
static const uint16_t	READYTOSTARTRATE100ms_1s=	10;

typedef struct{
	uint32_t cc_100ms,cc1_100ms,cc2_100ms;
	uint16_t per_100ms;
	uint8_t counterDebounce1;
	bool rxSlow1, rxTooSlow1, rxTooSlow2, paramCheckCfg, diagTrigCfg;
} EcuStruct;

static EcuStruct ecuVbm, ecuFum, ecuLim;
static void Call100msDho(EcuStruct* ecu,Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
static void Call100msDho_Diag(EcuStruct* ecu,Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);

#endif /* SRC_DHOCORE_H_ */
