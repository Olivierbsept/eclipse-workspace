/*
 * Fum.h
 *
 *  Created on: 30 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef FUM_H_
#define FUM_H_

//#include "Dho/DhoMpc.h"
#include "VbmDhoCommun.h"

// === Variables globales définies dans Vbm.c ===
DhoMicStruct dhoMic_Fum;
DhoMirStruct dhoMir_Fum;
uint32_t FumCounter;
extern void DhoMicInit_Fum(void);
extern void DhoMicStep10ms_Fum(void);
extern void DhoMirInit_Fum(void);
extern void DhoMirStep10ms_Fum(void);

// === Variables globales définies ici ===
void VbmToFumMsg(IdentVbm ident);
void RamToFumMsg(IdentVbm ident);
void VbmIdToFumMsg(IdentVbm ident);
void RamIdToFumMsg(IdentVbm ident);
void DhoMpcInit();
void DhoCoreInit_Fum(void);
void DhoCoreCall_Fum(void);
void DhoMpcCall(void);

// === Variables globales définies ailleurs ===
extern void FumToVbmMsg(IdentVbm ident);
extern void FumToRamMsg(IdentVbm ident);
extern void FumIdToVbmMsg(IdentVbm ident);
extern void FumIdToRamMsg(IdentVbm ident);
extern char* filename_Fum;


extern EemStates currentEemState;
extern void DhoTx_Fum(void);

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
