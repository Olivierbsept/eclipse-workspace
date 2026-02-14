/*
 * DhoCore.h
 *
 *  Created on: 23 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef DHOCORE_H_
#define DHOCORE_H_

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "../VbmDhoCommun.h" //pour EemStates
#include "FctOnOff/FctOnOff.h" //pour FCTONOFF_StCh...
/*typedef enum {
    ST_ReadytoStart,
    ST_GeneratorOn
} EemStates;*/
typedef struct{
	uint32_t mn, mh;
	uint16_t mt;
} Ident;
typedef struct {
	FCTONOFF_StCh mhc1_StCh, mhc2_StCh, mcc_StCh,  mhr1_StCh, mhr2_StCh;
} StCharts;
typedef struct{
	Ident ident0, ident1, ident2;
	EemStates eemState;
	bool RxTooSlow1, RxTooSlow2;
} DhoCoreInputs;
typedef struct{
	Ident ident;
	uint32_t mhr1_per,mhr2_per;
	FCTONOFF_Out* mhr1OutAddr;
} DhoCoreOutputs;
typedef struct{
	bool RxTooSlow1,RxTooSlow2;
	uint32_t per1, per2;
	Ident ident0, ident1, ident2;
	DhoCoreInputs Inputs;
	DhoCoreOutputs Outputs;
	StCharts* stChartsAddr;
} DhoCoreIntern;


// === Variables globales définies ici ===
void DhoCoreCall(DhoCoreIntern* dhoCore);
//Ident DhoMergeMhc(FCTONOFF_Out* mhc1OutAddr, FCTONOFF_Out* mhc2OutAddr, FCTONOFF_Out* mccOutAddr);
Ident DhoMergeMhc(void);
void DhoCoreInit_Vbm(void);
void DhoCoreInit_Fum(void);
void DhoCoreInit_Ram(void);
DhoCoreIntern dhoCore_Vbm, dhoCore_Fum, dhoCore_Ram;
uint32_t nbTicksBetwPrevAndLastMsg1, nbTicksBetwPrevAndLastMsg2;

// === Variables globales définies ailleurs ===
extern EemStates currentEemState;
extern void FctOnOff_Update(FCTONOFF_In* fctOnOffIn, FCTONOFF_Out* fctOnOffOut, FCTONOFF_StCh* fctOnOffStCh);
extern void FctOnOff_InitStCh(FCTONOFF_StCh* FctOnOffStCh);

// === Variables globales privées ===
static FCTONOFF_In mhc1_In, mhc2_In, mcc_In, mhr1_In, mhr2_In;
static FCTONOFF_Out mhc1_Out, mhc2_Out, mcc_Out, mhr1_Out, mhr2_Out;
static Cmds cmdsOff1, cmdsOn1, cmdsOff2, cmdsOn2, cmdsOff12, cmdsOn12, cmdsOffTx, cmdsOnTx;
static bool RxTooSlow1 = false;
static bool RxTooSlow2 = false;
static uint32_t mn0, mh0, mn1, mh1, mn2, mh2;
static uint16_t mt0, mt1, mt2;

static StCharts stCharts_Vbm;
static FCTONOFF_StCh mhc1_StCh_Vbm, mhc2_StCh_Vbm, mcc_StCh_Vbm, mhr1_StCh_Vbm, mhr2_StCh_Vbm;

static StCharts stCharts_Fum;
static FCTONOFF_StCh mhc1_StCh_Fum, mhc2_StCh_Fum, mcc_StCh_Fum, mhr1_StCh_Fum, mhr2_StCh_Fum;

static StCharts stCharts_Ram;
static FCTONOFF_StCh mhc1_StCh_Ram, mhc2_StCh_Ram, mcc_StCh_Ram, mhr1_StCh_Ram, mhr2_StCh_Ram;
#endif /* DHOCORE_H_ */
