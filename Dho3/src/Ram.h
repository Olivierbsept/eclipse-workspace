/*
 * Ram.h
 *
 *  Created on: 30 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef RAM_H_
#define RAM_H_

#include "Dho/DhoCore.h"

// === Variables globales définies ailleurs ===
extern void RamToVbmMsg(Ident ident);
extern void RamToFumMsg(Ident ident);
extern void RamIdToVbmMsg(Ident ident);
extern void RamIdToFumMsg(Ident ident);
extern char* filename_Ram;
extern EemStates currentEemState;
extern void DhoTx_Ram(void);
extern void RamToVbmMsg(Ident ident);
extern void RamToFumMsg(Ident ident);
extern void RamIdToVbmMsg(Ident ident);
extern void RamIdToFumMsg(Ident ident);
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);

extern const uint16_t UNSYNCRATE_2s;
extern const uint16_t THRESHRATE_100ms;
extern const uint16_t READYTOSTARTRATE_1s;
extern const uint16_t SLOWRATE_1500ms;
extern const uint16_t DEBOUNCE_3x;
extern const uint16_t TIMEOUT_5S;
extern const uint16_t PERIOD_STORE_5s;
extern const uint16_t PERIOD_MSGID_5s;

// === Variables globales définies ici ===
void VbmToRamMsg(Ident ident);
void FumToRamMsg(Ident ident);
void VbmIdToRamMsg(Ident ident);
void FumIdToRamMsg(Ident ident);

void DhoCoreInit_Ram(void);
void DhoCoreCall_Ram(void);

// === Variables globales privées===
static StCharts stCharts_Ram;
static FCTONOFF_StCh mhc1_StCh_Ram, mhc2_StCh_Ram, mcc_StCh_Ram, mhr1_StCh_Ram, mhr2_StCh_Ram;
static uint32_t compteurStep = 0;
static uint32_t cc_step1 = 0, cc_step2 = 0;
#endif /* RAM_H_ */

