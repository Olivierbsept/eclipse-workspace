/*
 * CtApTis.h
 *
 *  Created on: 28 nov. 2025
 *      Author: BESSETT
 */

#ifndef RTE_CTAPTIS_H_
#define RTE_CTAPTIS_H_

#include "rtwtypes.h"
#include <inttypes.h>

#define FUNC(rettype, memclass) rettype
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

#define DCM_INITIAL (0U)
#define DCM_E_POSITIVERESPONSE 0
#define DCM_E_GENERALPROGRAMMINGFAILURE 114
#define RTE_E_OK 0
#define RTE_E_DataServices_Data_DHO_MI_Read_E_NOT_OK 1
#define RTE_E_DataServices_Data_RHO_Bckup_E_NOT_OK (1U)
#define RTE_E_INVALID 2
#define E_OK 0
#define E_NOT_OK 1
#define FALSE false
#define TRUE true
#define NVM_REQ_OK (0U)
#define NVM_REQ_NV_INVALIDATED (5U)

# define Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_EemStates    1U
# define Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_FumHour    128U
# define Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_FumId    32U
# define Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_LimHour    256U
# define Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_LimId    64U
# define Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_OpHoursCANmsg    2U
# define Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_VbmId    512U

#  define RtePim_PimRhoBackup() \
  (&Rte_CtApTis_PimRhoBackup)
#   define Rte_Pim_PimRhoBackup() (&((*RtePim_PimRhoBackup())[0]))

// Types de retour standards
typedef unsigned char Std_ReturnType;         // souvent défini comme uint8
typedef unsigned char Dcm_OpStatusType;       // type standard AUTOSAR
typedef unsigned char Dcm_NegativeResponseCodeType;
typedef unsigned char NvM_RequestResultType;

typedef uint16 Alarm_AlarmId;
typedef uint8 CTAPALMDB_TYPE_e;

typedef uint8 Dcm_Data11ByteType[11];
typedef uint8 Dcm_Data10ByteType[10];
typedef uint8 Dcm_Data2ByteType[2];
typedef uint8 Dcm_Data4ByteType[4];

typedef uint16 Rte_ActivatingEvent_RCtApTis_RxEvents;
typedef uint32 Rte_DT_SG_HourCan_0;

// === typedef ===
typedef struct {
    uint8_T major;
    uint8_T middle;
    uint8_T minor;
} SG_ModuleVersion;

typedef struct
{
  uint8 WakeUpSleepRequest;
  uint8 EngineRunningState;
  uint8 ElectricalIgnitionState;
  uint8 DiagInhibit;
  uint8 OverallEemState;
  uint8 AvailableFeedbackState;
} SG_EemStates;

typedef struct
{
  uint16 ConfigMachineType;
  uint32 ConfigMachineNumber;
} SG_CmaTis;

typedef struct
{
  uint32 TotalCountEngine1OpHours;
  uint32 TotalCountEngine2OpHours;
} sTotalCounterHours;

typedef struct
{
  uint32 TotalVehicleHours;
} sTotalVehicleHours;

typedef struct
{
  Rte_DT_SG_HourCan_0 HourReceivedFromCan;
} SG_HourCan;

typedef struct
{
  uint32 EngTotalHoursOfOperation;
  uint32 u32_TotalEngineRevolutions;
} SG_Hours;

Std_ReturnType DataServices_Data_RHO_Bckup_ReadData(Dcm_OpStatusType OpStatus, uint8 *MI_data0, uint8 *MI_data1, uint8 *MI_data2, uint8 *MI_data3, uint8 *MI_data4);
FUNC(Std_ReturnType, CtApTis_CODE) DataServices_Data_RHO_Ctrl_WriteData(P2CONST(uint8, AUTOMATIC, RTE_CTAPTIS_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */

void Rte_Enter_EA_RhoBackup(void);
void Rte_Exit_EA_RhoBackup(void);
FUNC(void, CtApTis_CODE) RCtApTis_Step100ms(void);
FUNC(void, CtApTis_CODE) RCtApTis_Init(void);
Std_ReturnType MachineId_Write(P2CONST(uint8, AUTOMATIC, RTE_CTAPTIS_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
FUNC(void, CtApTis_CODE) RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents activationVector); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
Std_ReturnType Rte_Read_CtApTis_PpInCmaTis_DeCmaTis(SG_CmaTis *data);
Std_ReturnType Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(sTotalCounterHours *data);
Std_ReturnType Rte_Call_DataServices_Data_Config_MachineNumber_Read_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode);
Std_ReturnType Rte_Call_DataServices_Data_Config_Machinetype_Read_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode);
Std_ReturnType Rte_Call_PpMachineCounter_SetMachineCounter(uint32 set_MachineCounter);
Std_ReturnType Rte_Write_PpOutTisModuleVersion_DeModuleVersion(const SG_ModuleVersion *data);
void Rte_IrvWrite_RCtApTis_Init_Irv_PreviousHour(uint32 data);
void Rte_IrvWrite_RCtApTis_Init_Irv_StartRecvOpHours(boolean data);

Std_ReturnType Rte_Read_PpInCmaTis_DeCmaTis(SG_CmaTis *data);
Std_ReturnType Rte_Read_PpInEemStates_DeValues(SG_EemStates *data);
Std_ReturnType Rte_Read_PpInFumHourTis_DeOperatingHours(SG_HourCan *data);
Std_ReturnType Rte_Read_PpInFumIdTis_DeEcuTis(SG_CmaTis *data);
Std_ReturnType Rte_Read_PpInLimHourTis_DeOperatingHours(SG_HourCan *data);
Std_ReturnType Rte_Read_PpInLimIdTis_DeEcuTis(SG_CmaTis *data);
Std_ReturnType Rte_Write_PpOutStdHours_DeStdHours(const SG_Hours *data);
Std_ReturnType Rte_Write_PpOutTisOpHours_DeOpHoursInternal(uint32 data);
Std_ReturnType Rte_Write_PpOutTisOpHoursClaasCANmsg_TotalVehicleHours(const sTotalVehicleHours *data);
Std_ReturnType Rte_Write_PpOutTisOpHoursHydCANmsg_TotalVehicleHours(const sTotalVehicleHours *data);
Std_ReturnType Rte_Write_PpOutTisOpHoursJ1939CANmsg_TotalVehicleHours(const sTotalVehicleHours *data);
uint32 Rte_IrvRead_RCtApTis_RxEvents_Irv_PreviousHour(void);
boolean Rte_IrvRead_RCtApTis_RxEvents_Irv_StartRecvOpHours(void);
void Rte_IrvWrite_RCtApTis_RxEvents_Irv_PreviousHour(uint32 data);
void Rte_IrvWrite_RCtApTis_RxEvents_Irv_StartRecvOpHours(boolean data);
Std_ReturnType Rte_Call_PpMasterConfig_StartCanTransmission(void);
Std_ReturnType Rte_Call_PpMasterConfig_StartMachineCounter(void);
Std_ReturnType Rte_Call_PpMasterConfig_StopMachineCounter(void);
Std_ReturnType Rte_Write_PpOutVbmIdCANmsg_DeEcuTis(const SG_CmaTis *data);

Std_ReturnType Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_GetErrorStatus(NvM_RequestResultType *data);
Std_ReturnType Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_WriteBlock(unsigned char Rte_CtApTis_PimRhoBackup[11]);
Std_ReturnType Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_RestoreBlockDefaults(unsigned char Rte_CtApTis_PimRhoBackup[11]);

void Rte_Call_CTAPDTC_SetDtc(uint16);
void Rte_Call_CTAPDTC_ClrDtc(uint16);

#endif /* RTE_CTAPTIS_H_ */
