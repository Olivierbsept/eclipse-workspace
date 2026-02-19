#ifndef VBM_H_
#define VBM_H_

#include "Rho.h"
#include <inttypes.h>
#include <stdio.h>
#include "Dho.h"

// === Variables globales définies dans Lim.c ===
void VbmToLimMsg(DhoIdent ident);void VbmToLimMsg2(uint32_T mh);
void FumToLimMsg(DhoIdent ident);
void VbmIdToLimMsg(DhoIdent ident);
void VbmIdToLimMsg2(uint32 mn, uint16 mt);
void FumIdToLimMsg(DhoIdent ident);
void sendFumToLimMsg (uint32_T mh);
void sendFumIdToLimMsg(uint32_T mn, uint16_T mt);

// === Variables globales définies dans Vbm.c===
extern void LimToVbmMsg(DhoIdent ident);
extern void LimIdToVbmMsg(DhoIdent ident);

// === Variables globales définies dans Fum.c===
extern void ReceiveLimMsg (uint32_T mh);//extern void VbmToFumMsg(IdentVbm ident);
extern void ReceiveLimIdMsg (uint32_T mn, uint32_t mt);//extern void VbmIdToFumMsg(IdentVbm ident);

// === Variables globales définies dans Dho.c===
extern char* filename_Lim;
extern void Store(char* fileName, uint32_T mn, uint16_T mt, uint32_T mh);

// === Variables globales définies dans DhoCore.c===
extern void DhoCall_100ms_Lim(DhoTrigs* rxTrigs, DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoCall_100ms_Diag_Lim(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoInit_Lim(DhoConfigs configs);

#endif /* VBM_H_ */
