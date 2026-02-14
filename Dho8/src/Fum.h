#ifndef VBM_H_
#define VBM_H_

#include "DhoCommun.h"

// === Variables globales définies dans Fum.c ===
void VbmToFumMsg(IdentVbm ident);
void RamToFumMsg(IdentVbm ident);
void VbmIdToFumMsg(IdentVbm ident);
void RamIdToFumMsg(IdentVbm ident);

// === Variables globales définies dans Vbm.c===
extern void FumToVbmMsg(IdentVbm ident);
extern void FumIdToVbmMsg(IdentVbm ident);

// === Variables globales définies dans Lim.c===
extern void FumToLimMsg(IdentVbm ident);
extern void FumIdToLimMsg(IdentVbm ident);

// === Variables globales définies dans Dho.c===
extern char* filename_Fum;
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);

// === Variables globales définies dans DhoCore.c===
extern void Call50msDho_Fum(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
extern void Call50msDho_Fum_Diag(Trigs* rxTrigs,IdentVbm* ident0Addr, Idents idents);
extern void InitDho_Fum(Configs configs);

// === Variables globales privées ===
static uint32_t compteurStep50ms = 0;
static IdentVbm ident0;
static Trigs trigs;
static Idents idents;
static Phases phases;
static uint32_t FumCounter;
static Configs configs;

#endif /* VBM_H_ */
