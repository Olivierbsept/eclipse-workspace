#ifndef VBM_H_
#define VBM_H_

#include "rtwtypes.h"
#include <inttypes.h>
#include <stdio.h>
#include "Rho.h"
#include "Dho.h"


// === Variables globales définies dans Vbm.c ===
void FumToVbmMsg(DhoIdent ident);
void LimToVbmMsg(DhoIdent ident);
void FumIdToVbmMsg(DhoIdent ident);
void LimIdToVbmMsg(DhoIdent ident);
void sendFumToVbmMsg (uint32_T mh);
void sendFumIdToVbmMsg(uint32_T mn, uint16_t mt);

// === Variables globales définies dans Fum.c===
extern void ReceiveVbmMsg (uint32_T mh);//extern void VbmToFumMsg(IdentVbm ident);
extern void ReceiveVbmIdMsg (uint32 mn, uint16 mt);//extern void VbmIdToFumMsg(IdentVbm ident);

// === Variables globales définies dans Lim.c===
extern void VbmToLimMsg(DhoIdent ident);extern void VbmToLimMsg2(uint32_T mh);
extern void VbmIdToLimMsg(DhoIdent ident);extern void VbmIdToLimMsg2(uint32 mn, uint16 mt);

// === Variables globales définies dans Dho.c===
extern void Store(char* fileName, uint32_T mn, uint16_T mt, uint32_T mh);
extern uint16 Read_mtf(const char* filename);
extern uint16 Read_mtl(const char* filename);
extern uint32 Read_mnf(const char* filename);
extern uint32 Read_mnl(const char* filename);
extern uint32 Read_mhbu(const char* filename);
extern uint16 Read_mtbu(const char* filename);
extern uint32 Read_mnbu(const char* filename);
extern uint8 Read_ecuname(const char* filename);

// === Variables globales définies dans DhoCore.c===
extern void DhoCall_100ms_Vbm(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoCall_100ms_Diag_Vbm(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void SetOvrwEnbldCfg_Vbm(boolean OvrwEnbldCfg);

extern void RCtApTis_Step100ms(void);

extern const uint16_t PERIOD_MSGID100ms_5s;
extern const uint16_t PERIOD_MSGID100ms_3s;
extern const uint16_t PERIOD_STORE100ms_5s;
extern const uint16_t PERIOD_COUNT100ms_1s;
extern const uint16_t PERIOD_COUNT4ms_100ms;
extern const uint16_t PERIOD_MSGID50ms_5s;
extern const uint16_t PERIOD_MSGID50ms_3s;
extern const uint16_t PERIOD_STORE50ms_5s;
extern const uint16_t PERIOD_COUNT50ms_1s;

extern void Store(char* fileName, uint32_T mn, uint16_T mt, uint32_T mh);
extern void Store_dtc(const char* filename, uint32_T dtc, uint8_T state);
extern void Store_nvm(const char* filename, uint32 mnbu, uint16 mtbu, uint32 mhbu, uint8 ecuname, uint16 mtf, uint32 mnf, uint16 mtl, uint32 mnl);
extern void ReceiveVbmIdMsg(uint32 mn, uint16 mt);
extern void ReceiveLimMsg2(uint32 mh, uint16 mt);
extern void VbmIdToLimMsg2(uint32 mn, uint16 mt);

extern void start_xml(const char* filename);

#endif /* VBM_H_ */
