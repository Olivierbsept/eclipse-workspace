#ifndef VBM_H_
#define VBM_H_

#include "VbmDhoCommun.h"

// === Variables globales définies dans Vbm.c ===
void FumToVbmMsg(IdentVbm ident);
void LimToVbmMsg(IdentVbm ident);
void FumIdToVbmMsg(IdentVbm ident);
void LimIdToVbmMsg(IdentVbm ident);

// === Variables globales définies dans Fum.c===
extern void VbmToFumMsg(IdentVbm ident);
extern void VbmIdToFumMsg(IdentVbm ident);

// === Variables globales définies dans Lim.c===
extern void VbmToLimMsg(IdentVbm ident);
extern void VbmIdToLimMsg(IdentVbm ident);

// === Variables globales définies dans Dho.c===
extern char* filename_Vbm;
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);

// === Variables globales définies dans DhoCore.c===
extern void Call100msDho_Vbm(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
extern void Call100msDho_Vbm_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
extern void InitDho_Vbm(Configs configs);

// === Variables globales privées ===
static uint32_t compteurStep = 0;
static const uint16_t PERIOD_MSGID100ms_5s = 50;
static const uint16_t PERIOD_MSGID100ms_3s = 30;
static const uint16_t PERIOD_STORE100ms_5s = 50;
static IdentVbm ident0;
static Trigs trigs;
static Idents idents;
static Phases phases;
static uint32_t VbmCounter;
static Configs configs;

#endif /* VBM_H_ */
