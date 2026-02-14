/*
 * File: CtApTb_types.h
 *
 * Code generated for Simulink model 'CtApTb'.
 *
 * Model version                  : 1.122
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 26 18:40:27 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CtApTb_types_h_
#define RTW_HEADER_CtApTb_types_h_
#include "rtwtypes.h"

#ifndef _DEFINED_TYPEDEF_FOR_SG_jVbmcBrc_SystemStatus_
#define _DEFINED_TYPEDEF_FOR_SG_jVbmcBrc_SystemStatus_

typedef struct {
  uint8_T OverallEemState;
} SG_jVbmcBrc_SystemStatus;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_SG_jTBR2_PropB_
#define _DEFINED_TYPEDEF_FOR_SG_jTBR2_PropB_

typedef struct {
  uint8_T SecondaryBrakePosition;
  uint8_T TrailerParkBrakeReleaseRq;
  uint8_T ParkLockStatusActVal;
  uint8_T BrakeRight;
  uint8_T BrakeLeft;
  uint16_T WheelBasedVehicleSpeed;
  uint8_T SecondaryBrakeSwitch;
  uint8_T TBR2_Counter;
  uint8_T TBR2_Crc;
} SG_jTBR2_PropB;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_SG_ModuleVersion_
#define _DEFINED_TYPEDEF_FOR_SG_ModuleVersion_

typedef struct {
  uint8_T HighValue;
  uint8_T MiddleValue;
  uint8_T LowValue;
} SG_ModuleVersion;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_SG_jPropA_Vbm_Config_
#define _DEFINED_TYPEDEF_FOR_SG_jPropA_Vbm_Config_

typedef struct {
  uint32_T ConfigMachineNumber;
  uint16_T ConfigMachineType;
} SG_jPropA_Vbm_Config;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_SG_jPropA_Fum_Config_
#define _DEFINED_TYPEDEF_FOR_SG_SG_jPropA_Fum_Config_

typedef struct {
  uint32_T ConfigMachineNumber;
  uint16_T ConfigMachineType;
} SG_jPropA_Fum_Config;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_SG_jPropA_Lim_Config_
#define _DEFINED_TYPEDEF_FOR_SG_jPropA_Lim_Config_

typedef struct {
  uint32_T ConfigMachineNumber;
  uint16_T ConfigMachineType;
} SG_jPropA_Lim_Config;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_ENU_OverallEemState_
#define _DEFINED_TYPEDEF_FOR_ENU_OverallEemState_

typedef enum {
  EemState_PowersourceImminentShutdown = 0,
  EemState_PowersourcePendingShutdown = 1,
  EemState_FullSleep = 2,
  EemState_PartialSleep = 3,
  EemState_HiddenWakeUp = 4,
  EemState_OverallWakeUp = 5,
  EemState_ReadyToStartEngine = 8,
  EemState_EnginePreStart = 9,
  EemState_EngineStart = 10,
  EemState_EnginePostStart = 11,
  EemState_GeneratorOn = 16,
  EemState_GeneratorOnHighLoad = 17,
  EemState_EngineStalled = 23,
  EemState_GoToStop = 24,
  EemState_GoToSleep = 25,
  EemState_ReadyToSleep = 26,
  EemState_ShutdownWakeUp = 28,
  EemState_GhostWakeUp = 29,
  EemState_Error = 30,
  EemState_NotAvailable = 31           /* Default value */
} ENU_OverallEemState;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_ENU_U2_OnOff_
#define _DEFINED_TYPEDEF_FOR_ENU_U2_OnOff_

typedef enum {
  u2_OFF = 0,
  u2_Off = 0,
  u2_No = 0,
  u2_NO = 0,
  u2_ON = 1,
  u2_YES = 1,
  u2_Yes = 1,
  u2_On = 1,
  u2_ERROR = 2,                        /* Default value */
  u2_Error = 2,
  u2_NOTAVAILABLE = 3,
  u2_Notavailable = 3,
  u2_NA = 3
} ENU_U2_OnOff;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Enum_InternalState_
#define _DEFINED_TYPEDEF_FOR_Enum_InternalState_

typedef enum {
  STATEGEN_ABSENT = 0,
  STATEGEN_INHIB = 1,
  STATEGEN_PASSIVE = 2,
  STATEGEN_ERR_USER = 3,
  STATEGEN_OFF = 4,
  STATEGEN_ON = 5,
  STATEGEN_TEST_Obsolete = 6,
  STATEGEN_WOACT_Obsolete = 6,
  STATEGEN_ERR_SYST = 7,
  STATEGEN_BYPASS_ON = 8,
  STATEGEN_NA = 9,                     /* Default value */
  STATEGEN_BYPASS_OFF = 10,
  STATEGEN_ERR_SYST_WIALRM = 12,
  STATEGEN_ERR_SYST_WOALRM = 13,
  STATEGEN_ERR_SYST_WIALRM_PRIO = 14,
  STATEGEN_WAITCMD = 15,
  STATEGEN_SUSPEND = 16
} Enum_InternalState;

#endif

#endif                                 /* RTW_HEADER_CtApTis_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
