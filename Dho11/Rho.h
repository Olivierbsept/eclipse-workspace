#ifndef RHO_H_
#define RHO_H_

#include <stdio.h>
#include "CtComEemEnum.h"
#include "Dho.h"
#include "Vbm.h"
#include "rec.h"
#include "Rte_CtApTis.h"

// === Méthodes globales définies dans Rho.c==
// === Types ===
typedef struct{
	boolean MnthTrig;
	boolean MnthOvrWrttnTrig;
} RhoTrigs;

typedef struct{
	DhoIdent ident;
	EcuName ecuName;
} RhoIdent;

typedef enum
{
    RhoCtrlVal_Confirm = 1,
    RhoCtrlVal_Restore,
	RhoCtrlVal_Reset0,
	RhoCtrlVal_Reset1,
	RhoCtrlVal_Reset2,
	RhoCtrlVal_OvrwEnbld,
	RhoCtrlVal_OvrwDisbld,
} ENU_RhoCtrlVal;

typedef struct{
	boolean OvrwEnbldCfg;
} RhoConfigs;

//=== Méthodes définies dans Vbm2.c ===
extern void Rte_Call_CTAPDTC_SetDtc(uint16);
extern void Rte_Call_CTAPDTC_ClrDtc(uint16);

// === Méthodes globales définies dans Rho.c==
void RhoCtrl_Confirm(RhoTrigs* trigsAddr, DhoIdent* ident0Addr, DhoIdents* identsAddr, RhoIdent* rhoIdent);
void RhoCtrl_Restore(RhoTrigs* trigsAddr, DhoIdent* ident0Addr,RhoIdent* rhoIdent);
void RhoCall_100ms(RhoTrigs* rhoTrigAddr);
void RhoInit(RhoConfigs rhoConfigs);

Std_ReturnType RhoCallChangeId(RhoTrigs* rhoTrigs, RhoIdent rhoIdent);
void RhoCheckUniqueId(DhoTrigs dhoTrig, DhoIdent ident0, DhoIdents idents);
static const uint16 CTAPDTC_RHO_CfgOvrwrttn_C458 = 0xC458;
static const uint16 CTAPDTC_RHO_MoreThanOneId_C457 = 0xC457;
static const uint16 RhoNbTicks100ms_10s = 100;

#endif /* RHO_H_ */
