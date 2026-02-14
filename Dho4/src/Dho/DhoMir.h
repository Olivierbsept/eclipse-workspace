/*
 * DhoMir.h
 *
 *  Created on: 7 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef SRC_DHO_DHOMIR_H_
#define SRC_DHO_DHOMIR_H_

#include "../VbmDhoCommun.h"
#include "DhoFctCommun.h"


// === Variables globales définies dans Vbm.c ===
extern DhoMirStruct dhoMir;
extern DhoMirStruct dhoMir_Fum;


// === Variables globales définies dans DhoMic.c ===
void DhoMirInit(void);
void DhoMirStep10ms(void);
void DhoMirInit_Fum(void);
void DhoMirStep10ms_Fum(void);

static void DhoMergeMhr(void);
static void DhoMergeMpr(void);
static Cmds cmdsOffTx, cmdsOnTx;
static uint32_t cc_step10ms, nbTicks_10ms;

static FCTONOFF_StCh mhr1_StCh, mhr2_StCh, mpr_StCh;
static FCTONOFF_StCh mhr1_StCh_Fum, mhr2_StCh_Fum, mpr_StCh_Fum;
static FCTONOFF_In mhr1_In, mhr2_In, mpr_In;
static FCTONOFF_Out mhr1_Out, mhr2_Out, mpr_Out;

static const uint16_t READYTOSTARTRATE_1s = 100;
static const uint16_t SLOWRATE_1500ms = 150;

static bool Slow1, Slow1Effect;

#endif /* SRC_DHO_DHOMIR_H_ */
