/*
 * Fum.h
 *
 *  Created on: 30 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef FUM_H_
#define FUM_H_

#include "Dho/DhoMpc.h"

// === Variables globales définies ici ===
void VbmToFumMsg(Ident ident);
void RamToFumMsg(Ident ident);
void VbmIdToFumMsg(Ident ident);
void RamIdToFumMsg(Ident ident);
void DhoMpcInit();
void DhoCoreInit_Fum(void);
void DhoCoreCall_Fum(void);
void DhoMpcCall(void);

// === Variables globales définies ailleurs ===
extern void FumToVbmMsg(Ident ident);
extern void FumToRamMsg(Ident ident);
extern void FumIdToVbmMsg(Ident ident);
extern void FumIdToRamMsg(Ident ident);
extern char* filename_Fum;
extern EemStates currentEemState;
extern void DhoTx_Fum(void);
extern void FumToVbmMsg(Ident ident);
extern void FumToRamMsg(Ident ident);
extern void FumIdToVbmMsg(Ident ident);
extern void FumIdToRamMsg(Ident ident);
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);
extern const uint16_t UNSYNCRATE_2s;
extern const uint16_t THRESHRATE_100ms;
extern const uint16_t READYTOSTARTRATE_1s;
extern const uint16_t SLOWRATE_1500ms;
extern const uint16_t DEBOUNCE_3x;
extern const uint16_t TIMEOUT_5S;
extern const uint16_t PERIOD_STORE_5s;
extern const uint16_t PERIOD_MSGID_5s;

// === Variables globales privées ===
static uint8_t counterDebounce1 = 0;
static uint32_t compteurStep = 0;
static uint32_t cc_step1 = 0, cc_step2 = 0;


#endif /* FUM_H_ */
