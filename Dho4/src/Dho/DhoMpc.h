/*
 * DhoMpr.h
 *
 *  Created on: 23 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef DHOMPC_H_
#define DHOMPC_H_

#include "DhoCore.h"

typedef struct{
	Ident ident0;
	Ident ident1;
	EemStates eemState;
	bool RxSlow;
	bool RxTooSlow;
	bool RxSync;
} DhoMpcInputs;

typedef struct{
	Ident ident;
	bool check1;
	bool CmdsStateOn;
	uint32_t mprPer;
	EnumState State;
} DhoMpcOutputs;

typedef struct{
	DhoMpcInputs Inputs;
	DhoMpcOutputs Outputs;
	bool RxSlow1,checkId1;
	uint8_t RxSlow1_cc;
} DhoMpcIntern;

// === Variables globales définies ici ===
void DhoMpcCall(void);
Ident DhoMergeMpc(void);
DhoMpcIntern dhoMpc;
bool CheckMpc2(uint8_t* counterDebounce);

// === Variables globales définies ailleurs ===
extern EemStates currentEemState;
extern void FctOnOff_Update(FCTONOFF_In* fctOnOffInAddr, FCTONOFF_Out* fctOnOffOutAddr, FCTONOFF_StCh* FctOnOffStChAddr);
extern void FctOnOff_InitStCh(FCTONOFF_StCh* FctOnOffStCh);
extern DhoCoreIntern dhoCore_Fum;

// === Variables globales privées ===
static FCTONOFF_In mpc_In;
static FCTONOFF_Out mpc_Out;
static FCTONOFF_StCh mpc_StCh;
static Cmds cmdsOff, cmdsOn;
static bool RxSlow1 = false;
static bool RxSync1 = false;
static uint32_t mn1, mh1;
static uint16_t mt1;
static Ident ident0, ident1;
#endif /* DHOMPC_H_ */
