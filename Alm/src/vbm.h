/*
 * vbm.h
 *
 *  Created on: 4 oct. 2025
 *      Author: olivierbessettemac
 */

#ifndef VBM_H_
#define VBM_H_
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <stddef.h>
#include "rtwtypes.h"

#define FUNC(rettype, memclass) rettype
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *
typedef int8_T sint8;
typedef int32_T sint32;
typedef uint16 Alarm_AlarmId;
//typedef boolean bool;
typedef uint8 CTAPALMDB_TYPE_e;

#define MAX_ACTIVE_DTC_TEST					 8
#define MAX_ACTIVE_DTC_SERIAL				32
#define MAX_ACTIVE_DTC						MAX_ACTIVE_DTC_SERIAL
#if MAX_ACTIVE_DTC <= MAX_ACTIVE_DTC_TEST
#pragma message ( "WARNING: DTC list size is reduced to tests purpose. If you see this message for serial version modify the MAX_ACTIVE_DTC macro from MAX_ACTIVE_DTC_TEST to MAX_ACTIVE_DTC_SERIAL" )
#endif

typedef uint32 Rte_ActivatingEvent_RCtApAlm_RxEvents;
#define Rte_ActivatingEvent_RCtApAlm_RxEvents_ActReason_LedsInTestMode 1
#define Rte_ActivatingEvent_RCtApAlm_RxEvents_ActReason_EemStates 2

#define CTAPALMDB_DTC_NOT_VALID 0xFFFF
#define CTAPALMDB_NO_TYPE       0U
#define CTAPALMDB_ERROR_TYPE    1U
#define CTAPALMDB_ICON_TYPE     2U
#define CTAPALMDB_INFO_TYPE    4U
#define CTAPALMDB_PING_TYPE    8U
#define CTAPALMDB_SILENT_TYPE  16U
#define CTAPALMDB_WARNING_TYPE 32U
#define CTAPALMDB_MAX_TYPE 48U;


typedef enum {
    Default_AlarmStatus_AlarmOff = 0U,
    Default_AlarmStatus_AlarmOn = 1U,
    Default_AlarmStatus_Error = 254U,
    Default_AlarmStatus_NotAvailable = 255U
} Alarm_AlarmStatus;

typedef struct {
    uint8_T major;
    uint8_T middle;
    uint8_T minor;
} SG_ModuleVersion;

typedef struct {
	Alarm_AlarmId AlarmId;
    Alarm_AlarmStatus AlarmStatus;
} SG_Alarm;

typedef struct {
	Alarm_AlarmId AlarmId;
	Alarm_AlarmStatus AlarmStatus;
    uint8 AlarmMsgCounter;
} SG_AlarmCnt;

typedef struct {
	uint16 AlarmSrc;
	Alarm_AlarmId AlarmId;
	Alarm_AlarmStatus AlarmStatus;
} SG_AlarmWithSrc;

typedef struct {
    uint8 WakeUpSleepRequest;
	uint8 EngineRunningState;
	uint8 ElectricalIgnitionState;
	uint8 DiagInhibit;
	uint8 OverallEemState;
	uint8 AvailableFeedbackState;
} SG_EemStates;

typedef struct {
    boolean StopLedReq;
    boolean WarningLedReq;
} SG_LedsReq;

typedef struct {
    uint8 Counter;
	uint8 Status;
	uint8 Dummy;
} SG_ModuleAlive;

typedef enum {
    EemState_PowersourceImminentShutdown = 0,
    EemState_PowersourcePendingShutdown,
    EemState_FullSleep,
    EemState_PartialSleep,
    EemState_OverallWakeUp,
    EemState_HiddenWakeUp,
    EemState_NotUse6,
    EemState_NotUse7,
    EemState_ReadyToStartEngine,
    EemState_EnginePreStart,
    EemState_EngineStart,
    EemState_EnginePostStart,
    EemState_NotUse12,
    EemState_NotUse13,
    EemState_NotUse14,
    EemState_NotUse15,
    EemState_GeneratorOn,
    EemState_GeneratorOnHighLoad,
    EemState_NotUse18,
    EemState_NotUse19,
    EemState_NotUse20,
    EemState_NotUse21,
    EemState_NotUse22,
    EemState_EngineStalled,
    EemState_GoToStop,
    EemState_GoToSleep,
    EemState_ReadyToSleep,
    EemState_NotUse27,
    EemState_ShutdownWakeUp,
    EemState_GhostWakeUp,
    EemState_Error,
    EemState_NotAvailable
} EemState_t;

typedef enum {
    AvailableFeedback_None = 0,
    AvailableFeedback_Full,
    AvailableFeedback_TerminalNotAvailable,
    AvailableFeedback_DashboardTerminalNotAvailable,
    AvailableFeedback_DashboardTerminalDisplayingPartially,
    AvailableFeedback_DashboardTerminalDisplayNotAvailable
} AvailableFeedbackState_t;

#define DCM_E_POSITIVERESPONSE 0
#define RTE_E_OK 0
#define RTE_E_DataServices_Data_DHO_MI_Read_E_NOT_OK 1
#define RTE_E_INVALID 2
#define E_OK 0
#define E_NOT_OK 1


// Types de retour standards
typedef unsigned char Std_ReturnType;         // souvent défini comme uint8
typedef unsigned char Dcm_OpStatusType;       // type standard AUTOSAR
typedef unsigned char Dcm_NegativeResponseCodeType;

#define ALM_FIFO_MAX_SIZE_TEST					 8
#define ALM_FIFO_MAX_SIZE_SERIAL				64
#define ALM_FIFO_MAX_SIZE						ALM_FIFO_MAX_SIZE_SERIAL

boolean Rte_IrvRead_RCtApAlmDtc_SendDtc_Irv_RciReset(void);
Std_ReturnType Rte_Call_PpAlmDataBaseDtcToType_LookupDtcType(uint16 Dtc, CTAPALMDB_TYPE_e* DtcType);

void RCtApAlm_RxEvents(Rte_ActivatingEvent_RCtApAlm_RxEvents);
void Rte_Enter_Ex_InputAlarm(void);
void Rte_Exit_Ex_InputAlarm(void);
void Rte_Enter_Ex_OutputAlarm(void);
void Rte_Write_PpOutAlmModuleVersion_DeModuleVersion(const SG_ModuleVersion* pModuleVersion);
void Rte_IrvRead_RCtApAlm_RxEvents_Irv_AliveStatus(SG_ModuleAlive* Alive);
void Rte_IrvWrite_RCtApAlm_Init_Irv_AliveStatus(const SG_ModuleAlive* pAlive_Init);
void Rte_Write_PpOutAlmAlive_DeModuleAlive(const SG_ModuleAlive* pModuleAlive);
void Rte_IrvWrite_RCtApAlm_Init_Irv_RciReset(boolean);
void Rte_Write_PpOutAlmReset_DeReset(boolean);
void Rte_IrvWrite_RCtApAlm_Init_Irv_MsgCounter(uint8);

void Rte_IrvWrite_RCtApAlm_Init_Irv_LockInputAlarm(boolean);
void Rte_IrvWrite_RCtApAlm_Init_Irv_LockOutputAlarm(boolean);
void Rte_IrvWrite_RCtApAlm_Init_Irv_DelayUnlockInputAlarmCnt(sint32);

void Rte_IrvWrite_RCtApAlm_Init_Irv_LedsReqPrev(const SG_LedsReq*);
void Rte_Write_PpOutAlmLedsReq_DeLedsReq(const SG_LedsReq*);
void Rte_IrvRead_RCtApAlm_Step_Irv_LedsReqPrev(SG_LedsReq*);
void Rte_IrvWrite_RCtApAlm_Step_Irv_LedsReqPrev(const SG_LedsReq*);
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsReqPrev(const SG_LedsReq*);

void Rte_IrvWrite_RCtApAlm_Init_Irv_LedsInTestMode(boolean);
void Rte_Write_PpOutAlmLedsTestModeEnabled_DeLedsTestModeEnabled(boolean);

boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_LedsInTestMode();
boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_RciReset();

void Rte_Read_PpInAlmLedsInTestMode_DeLedsTestMode(boolean*);
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsInTestMode(boolean);

void Rte_Read_PpInAlmEemStates_DeValues(SG_EemStates*);
boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_LockInputAlarm(void);
sint32 Rte_IrvRead_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt(void);
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt(sint32);
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockInputAlarm(boolean);
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_RciReset(boolean);

void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockOutputAlarm(boolean);
void Rte_Exit_Ex_OutputAlarm();
void Rte_Enter_Ex_MsgCounter();
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_MsgCounter(uint8);
void Rte_Exit_Ex_MsgCounter();
void Rte_Enter_Ex_LedsReq();
void Rte_Exit_Ex_LedsReq();

void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_AliveStatus(const SG_ModuleAlive* pAlive);

void Rte_IrvRead_RCtApAlm_Step_Irv_AliveStatus(SG_ModuleAlive* Alive);
void Rte_IrvWrite_RCtApAlm_Step_Irv_AliveStatus(const SG_ModuleAlive* Alive);
boolean Rte_IrvRead_RCtApAlm_Step_Irv_RciReset();
sint32 Rte_IrvRead_RCtApAlm_Step_Irv_DelayUnlockInputAlarmCnt();
void Rte_IrvWrite_RCtApAlm_Step_Irv_LockInputAlarm(boolean);
void Rte_IrvWrite_RCtApAlm_Step_Irv_DelayUnlockInputAlarmCnt(sint32);
boolean Rte_IrvRead_RCtApAlm_Step_Irv_LockInputAlarm();
boolean Rte_IrvRead_RCtApAlm_Step_Irv_LockOutputAlarm();


uint8 Rte_IrvRead_RCtApAlm_Step_Irv_MsgCounter(void);
void Rte_IrvWrite_RCtApAlm_Step_Irv_MsgCounter(uint8);
void Rte_Write_PpOutAlmAlarm_DeAlarm(SG_Alarm*);
void Rte_Write_PpOutAlmAlarmCnt_DeAlarmCnt(SG_AlarmCnt*);


#endif /* VBM_H_ */
