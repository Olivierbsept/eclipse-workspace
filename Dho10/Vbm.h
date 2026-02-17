#ifndef VBM_H_
#define VBM_H_

#include "DhoCommun.h"
#include "rtwtypes.h"
#include <inttypes.h>
#include <stdio.h>

// === Variables globales définies dans Vbm.c ===
void FumToVbmMsg(DhoIdent ident);
void LimToVbmMsg(DhoIdent ident);
void FumIdToVbmMsg(DhoIdent ident);
void LimIdToVbmMsg(DhoIdent ident);
void sendFumToVbmMsg (uint32_T mh);
void sendFumIdToVbmMsg(uint32_T mn, uint16_t mt);

// === Variables globales définies dans Fum.c===
extern void ReceiveVbmMsg (uint32_T mh);//extern void VbmToFumMsg(IdentVbm ident);
extern void ReceiveVbmIdMsg (uint32_T mn, uint32_T mt);//extern void VbmIdToFumMsg(IdentVbm ident);

// === Variables globales définies dans Lim.c===
extern void VbmToLimMsg(DhoIdent ident);
extern void VbmIdToLimMsg(DhoIdent ident);

// === Variables globales définies dans Dho.c===
extern char* filename_Vbm;
extern void Store(char* fileName, uint32_T mn, uint16_T mt, uint32_T mh);

// === Variables globales définies dans DhoCore.c===
extern void DhoCall_100ms_Ecu1(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoCall_100ms_Diag_Ecu1(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoInit_Ecu1(DhoConfigs configs);

// === Variables globales privées ===
static uint32_T compteurStep100ms = 0;
static DhoIdent ident0;
static DhoTrigs trigs;
static DhoIdents idents;
static Phases phases;
static uint32_T VbmCounter;
static DhoConfigs configs;

#endif /* VBM_H_ */
