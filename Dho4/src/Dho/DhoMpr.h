/*
 * DhoMpr.h
 *
 *  Created on: 23 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef DHOMPR_H_
#define DHOMPR_H_

#include "DhoCore.h"
//#include "DhoCommun.h"

typedef struct{
	Ident ident;
	EemStates eemState;
	bool flagDiag;
	bool RxTooSlow;
} DhoMprInputs;

typedef struct{
	bool check1;
	bool CmdsStateOn;
	uint32_t mprPer;
} DhoMprOutputs;

typedef struct{
	DhoMprInputs Inputs;
	DhoMprOutputs Outputs;
} DhoMprIntern;

// === Variables globales définies ici ===
void DhoMprCall(void);
uint32_t DhoMergeMpr(void);
DhoMprIntern dhoMpr;

// === Variables globales définies ailleurs ===
extern EemStates currentEemState;
extern bool flagDiag;
extern void FctOnOff_Update(FCTONOFF_In* fctOnOffInAddr, FCTONOFF_Out* fctOnOffOutAddr, FCTONOFF_StCh* FctOnOffStChAddr);
extern void FctOnOff_InitStCh(FCTONOFF_StCh* FctOnOffStCh);
extern const uint16_t READYTOSTARTRATE_1s;
extern const uint16_t SLOWRATE_1500ms;

// === Variables globales privées ===
static FCTONOFF_In mpr_In;
static FCTONOFF_Out mpr_Out;
static FCTONOFF_StCh mpr_StCh;
static Cmds cmdsOffTx, cmdsOnTx;
static uint32_t mn0, mh0;
static uint16_t mt0;
static Ident ident;

#endif /* DHOMPR_H_ */

