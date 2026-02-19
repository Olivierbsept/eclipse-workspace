#ifndef DHO_H_
#define DHO_H_

#include "Platform_Types.h"

typedef struct{
	uint16 mt;
	uint32 mn,mh;
} DhoIdent;

typedef struct{
	boolean Rx1Trig,Rx2Trig,RxId1Trig,DiagTrig,TxTrig,MhTrig,MnTrig,Rx1TooSlowTrig,Rx2TooSlowTrig,Rx1Slow, SyncAllwd, SyncBlkd, Reset1Trig, Reset2Trig, changeIdTrig;
} DhoTrigs;

typedef struct{
	DhoIdent Ident1,Ident2;
} DhoIdents;

typedef struct{
	boolean SyncConfigPhase,SyncDiagPhase;
} Phases;

typedef struct{
	boolean DiagTrigCfg, ParamCheckCfg, OvrwEnbldCfg;
	uint32 ResetMnCfg;
	uint16 ResetMtCfg;
} DhoConfigs;

static const uint16_T PERIOD_MSGID100ms_6s = 60;
static const uint16_T PERIOD_MSGID100ms_5s = 50;
static const uint16_T PERIOD_MSGID100ms_3s = 30;
static const uint16_T PERIOD_STORE100ms_5s = 50;
static const uint16_T PERIOD_COUNT100ms_1s = 10;
static const uint16_T PERIOD_COUNT4ms_100ms = 25;

static const uint16_T PERIOD_MSGID50ms_6s = 120;
static const uint16_T PERIOD_MSGID50ms_5s = 100;
static const uint16_T PERIOD_MSGID50ms_3s = 60;
static const uint16_T PERIOD_STORE50ms_5s = 100;
static const uint16_T PERIOD_COUNT50ms_1s = 20;

static const uint16_T	TIMEOUT100ms_5S =			50;
static const uint8_T	DEBOUNCE_3x =				3;
static const uint16_T	SYNCRATE100ms_1s=			10;
static const uint16_T	UNSYNCRATE100ms_2s=			20;
static const uint16_T	SLOWRATE100ms_1500ms=		15;
static const uint16_T	SLOWRATE100ms_1500msBelow = 14;
static const uint16_T	READYTOSTARTRATE100ms_2s = 	20;
static const uint16_T	READYTOSTARTRATE100ms_2sBelow = 19;

extern void DhoInit(DhoConfigs dhoConfigs);

typedef enum{
	EcuVbm = 1,
	EcuFum,
	EcuLim,
	EcuNA = 0xFF,
} EcuName;

typedef struct{
	uint32_T cc_100ms,cc1_100ms,cc2_100ms;
	uint16_T per_100ms;
	uint8_T counterDebounce1;
	boolean_T paramCheckCfg, diagTrigCfg, ovrwEnbldCfg;
	uint32_T ResetMnCfg;
	uint16_T ResetMtCfg;
	EcuName ecuName;
	DhoIdent ident;
} EcuStruct;

void DhoCall_100ms_Vbm(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Fum(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Lim(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Diag_Vbm(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Diag_Fum(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Diag_Lim(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoInit_Vbm(DhoConfigs configs);
void DhoInit_Fum(DhoConfigs configs);
void DhoInit_Lim(DhoConfigs configs);
void SetOvrwEnbldCfg_Vbm(boolean OvrwEnbldCfg);
void SetOvrwEnbldCfg_Fum(boolean OvrwEnbldCfg);
void SetOvrwEnbldCfg_Lim(boolean OvrwEnbldCfg);
void SetOvrwEnbldCfg_Ecu(EcuStruct* ecu,boolean OvrwEnbldCfg);

void DhoCall_100ms_Ecu(EcuStruct* ecu,DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
void DhoCall_100ms_Diag_Ecu(EcuStruct* ecu,DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);

#endif /* DHO_H_ */
