#ifndef VBM_H_
#define VBM_H_

#include "Dho/DhoMpr.h"

// === Variables globales définies ici ===
void FumToVbmMsg(Ident ident);
void RamToVbmMsg(Ident ident);
void FumIdToVbmMsg(Ident ident);
void RamIdToVbmMsg(Ident ident);

// === Variables globales définies ailleurs ===
extern void VbmToFumMsg(Ident ident);
extern void VbmToRamMsg(Ident ident);
extern void VbmIdToFumMsg(Ident ident);
extern void VbmIdToRamMsg(Ident ident);
extern void FctOnOff_InitStCh(FCTONOFF_StCh*);
extern char* filename_Vbm;
extern DhoCoreIntern dhoCore_Vbm;
extern void DhoCoreInit_Vbm(void);
extern void DhoCoreCall_Vbm(void);
extern void DhoMprInit(void);
extern void DhoTx_Vbm(void);

extern void VbmToFumMsg(Ident ident);
extern void VbmToRamMsg(Ident ident);
extern void VbmIdToFumMsg(Ident ident);
extern void VbmIdToRamMsg(Ident ident);
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
static uint32_t compteurStep = 0;
static uint32_t cc_step1 = 0, cc_step2 = 0;

#endif /* VBM_H_ */
