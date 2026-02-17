#ifndef VBM_H_
#define VBM_H_

#include "DhoCommun.h"
#include <inttypes.h>
#include <stdio.h>

// === Variables globales définies dans Lim.c ===
void VbmToLimMsg(DhoIdent ident);
void FumToLimMsg(DhoIdent ident);
void VbmIdToLimMsg(DhoIdent ident);
void FumIdToLimMsg(DhoIdent ident);
void sendFumToLimMsg (uint32_T mh);
void sendFumIdToLimMsg(uint32_T mn, uint16_T mt);

// === Variables globales définies dans Vbm.c===
extern void LimToVbmMsg(DhoIdent ident);
extern void LimIdToVbmMsg(DhoIdent ident);

// === Variables globales définies dans Fum.c===
//extern void LimToFumMsg(IdentVbm ident);
//extern void LimIdToFumMsg(IdentVbm ident);
extern void ReceiveLimMsg (uint32_T mh);//extern void VbmToFumMsg(IdentVbm ident);
extern void ReceiveLimIdMsg (uint32_T mn, uint32_t mt);//extern void VbmIdToFumMsg(IdentVbm ident);

// === Variables globales définies dans Dho.c===
extern char* filename_Lim;
extern void Store(char* fileName, uint32_T mn, uint16_T mt, uint32_T mh);

// === Variables globales définies dans DhoCore.c===
extern void DhoCall_100ms_Ecu2(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoCall_100ms_Diag_Ecu2(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void InitDho_Ecu2(DhoConfigs configs);

// === Variables globales privées ===
static uint32_t compteurStep100ms = 0;
static DhoIdent ident0;
static DhoTrigs trigs;
static DhoIdents idents;
static Phases phases;
static uint32_T LimCounter;
static DhoConfigs configs;

#endif /* VBM_H_ */
