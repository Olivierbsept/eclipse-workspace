#ifndef VBM_H_
#define VBM_H_

#include "VbmDhoCommun.h"

// === Variables globales définies dans Lim.c ===
void VbmToLimMsg(IdentVbm ident);
void FumToLimMsg(IdentVbm ident);
void VbmIdToLimMsg(IdentVbm ident);
void FumIdToLimMsg(IdentVbm ident);

// === Variables globales définies dans Vbm.c===
extern void LimToVbmMsg(IdentVbm ident);
extern void LimIdToVbmMsg(IdentVbm ident);

// === Variables globales définies dans Fum.c===
extern void LimToFumMsg(IdentVbm ident);
extern void LimIdToFumMsg(IdentVbm ident);

// === Variables globales définies dans Dho.c===
extern char* filename_Lim;
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);

// === Variables globales définies dans DhoCore.c===
extern void Call100msDho_Lim(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
extern void Call100msDho_Lim_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
extern void InitDho_Lim(Configs configs);

// === Variables globales privées ===
static uint32_t compteurStep = 0;
static const uint16_t PERIOD_MSGID100ms_5s = 50;
static const uint16_t PERIOD_MSGID100ms_3s = 30;
static const uint16_t PERIOD_STORE100ms_5s = 50;
static IdentVbm ident0;
static Trigs trigs;
static Idents idents;
static Phases phases;
static uint32_t LimCounter;
static Configs configs;

#endif /* VBM_H_ */
