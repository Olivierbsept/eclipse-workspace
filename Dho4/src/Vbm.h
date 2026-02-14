#ifndef VBM_H_
#define VBM_H_

#include "VbmDhoCommun.h"

// === Variables globales définies dans Vbm.c ===
DhoMicStruct dhoMic;
DhoMirStruct dhoMir;
uint32_t VbmCounter;

//const uint16_t PERIOD_STORE_5s;
//const uint16_t PERIOD_MSGID_5s;
void FumToVbmMsg(IdentVbm ident);
void RamToVbmMsg(IdentVbm ident);
void FumIdToVbmMsg(IdentVbm ident);
void RamIdToVbmMsg(IdentVbm ident);

// === Variables globales définies dans DhoMic===
extern void DhoMicInit(void);
extern void DhoMicStep10ms(void);
extern void DhoMirInit(void);
extern void DhoMirStep10ms(void);
extern void VbmToFumMsg(IdentVbm ident);
extern void VbmToRamMsg(IdentVbm ident);
extern void VbmIdToFumMsg(IdentVbm ident);
extern void VbmIdToRamMsg(IdentVbm ident);

extern char* filename_Vbm;
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);

// === Variables globales privées ===
static uint32_t compteurStep = 0;
static const uint16_t PERIOD_MSGID_5s = 500;

#endif /* VBM_H_ */
