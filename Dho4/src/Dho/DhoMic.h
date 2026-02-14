/*
 * DhoMic.h
 *
 *  Created on: 7 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef SRC_DHO_DHOMIC_H_
#define SRC_DHO_DHOMIC_H_

#include "../VbmDhoCommun.h"
#include "DhoFctCommun.h"


// === Variables globales définies dans Vbm.c ===
extern DhoMicStruct dhoMic;
extern DhoMicStruct dhoMic_Fum;

// === Variables globales définies dans DhoMic.c ===
void DhoMicInit(void);
void DhoMicStep10ms(void);
void DhoMicInit_Fum(void);
void DhoMicStep10ms_Fum(void);

//== Variables globales visibles uniquement dans DhoMic.c ===
static IdentVbm DhoMergeMhc(void);
static IdentVbm DhoMergeMpc(void);
static FCTONOFF_StCh mhc1_StCh, mhc2_StCh, mcc_StCh, mpc_StCh;
static FCTONOFF_StCh mhc1_StCh_Fum, mhc2_StCh_Fum, mcc_StCh_Fum, mpc_StCh_Fum;
static FCTONOFF_In mhc1_In, mhc2_In, mcc_In, mpc_In;
static FCTONOFF_Out mhc1_Out, mhc2_Out, mcc_Out, mpc_Out;
static Cmds cmdsOff1, cmdsOn1, cmdsOff2, cmdsOn2, cmdsOff12, cmdsOn12, cmdsOn, cmdsOff;
static uint32_t cc1_step10ms,cc2_step10ms, cc_step10ms_RxSlow;
static bool RxTooSlow1, RxTooSlow2;

static const uint16_t TIMEOUT_5S = 500;
static const uint16_t UNSYNCRATE_2s = 200;
static const uint16_t READYTOSTARTRATE_1s = 100;
static const uint16_t THRESHRATE_100ms = 10;
static const uint16_t DEBOUNCE_3x = 3;
static const uint16_t SLOWRATE_1500ms = 150;
static bool RxSlow1, RxSlow1Effect=false;
static IdentVbm ident0Prv;

static uint8_t counterDebounce = 0;

#endif /* SRC_DHO_DHOMIC_H_ */
