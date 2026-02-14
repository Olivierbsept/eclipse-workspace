/**********************************************************************************************************************
 *  FILE REQUIRES USER MODIFICATIONS
 *  Template Scope: sections marked with Start and End comments
 *  -------------------------------------------------------------------------------------------------------------------
 *  This file includes template code that must be completed and/or adapted during BSW integration.
 *  The template code is incomplete and only intended for providing a signature and an empty implementation.
 *  It is neither intended nor qualified for use in series production without applying suitable quality measures.
 *  The template code must be completed as described in the instructions given within this file and/or in the.
 *  Technical Reference.
 *  The completed implementation must be tested with diligent care and must comply with all quality requirements which.
 *  are necessary according to the state of the art before its use.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  CtApAlm.c
 *           Config:  C_UCP.dpa
 *        SW-C Type:  CtApAlm
 *
 *        Generator:  MICROSAR RTE Generator Version 4.21.0
 *                    RTE Core Version 1.21.0
 *          License:  CBD1600472
 *
 *      Description:  C-Code implementation template for SW-C <CtApAlm>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2 */
/* PRQA S 0857 EOF */ /* MD_MSR_Dir1.1 */
/* PRQA S 0614 EOF */ /* MD_Rte_TestCode */

/* PRQA S 3109 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3112 EOF */ /* MD_Rte_TestCode */
/* PRQA S 2982 EOF */ /* MD_Rte_TestCode */
/* PRQA S 2983 EOF */ /* MD_Rte_TestCode */
/* PRQA S 2880 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3203 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3205 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3206 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3218 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3229 EOF */ /* MD_Rte_TestCode */
/* PRQA S 2002 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3334 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3417 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3426 EOF */ /* MD_Rte_TestCode */
/* PRQA S 3453 EOF */ /* MD_Rte_TestCode */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

//#include "Rte_CtApAlm.h"//PATCH
//#include "TSC_CtApAlm.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "vbm.h"
#include "string.h"
#include "CtApAlmModuleVersion.h"
#include "CtApAlm_AliveStates.h"
#include "CtApAlmDbSources.h"
#include "CtApAlmLibStackMgr.h"

//#include "CtApAlmDb.h"
#include "CtApAlmFifoMgr.h"
//#include "CtApAlmLibStackMgr.h"
//#include "CtComEemEnum.h"//PATCH
//#include "CtEngCfgEnum.h"//PATCH

//#include "rtwtypes.h"//PATCH

//#define ALLOW_DEBUG_VIA_XCP//PATCH

#define CTAPALM_STEP_TICKS_MS								  50
#define CTAPALM_ALIVE_PERIOD_MS								 100
#define CTAPALM_ALIVE_PERIOD_CNT_INIT						(CTAPALM_ALIVE_PERIOD_MS/CTAPALM_STEP_TICKS_MS)
#define CTAPALM_DELAY_AFTER_ReadyToStartEngine_MS			3000
#define CTAPALM_DELAY_AFTER_GeneratorOn_MS					3000

#define CTAPALM_DELAY_AFTER_ReadyToStartEngine_CNT_INIT		(CTAPALM_DELAY_AFTER_ReadyToStartEngine_MS/CTAPALM_STEP_TICKS_MS)
#define CTAPALM_DELAY_AFTER_GeneratorOn_CNT_INIT			(CTAPALM_DELAY_AFTER_GeneratorOn_MS/CTAPALM_STEP_TICKS_MS)

static const SG_ModuleAlive Alive_Init = { 0x00, ALIVE_STATE_INITIALISATION, 0xFF };
static const SG_LedsReq LedsReq_Init = { FALSE, FALSE };

static T_AlmFifo InDtcsFifo;
static T_AlmFifo OutDtcsFifo;
static T_AlmFifo ActiveDtcsFifo;

static T_StackDtcs WarningStack;
static T_StackDtcs ErrorStack;

static bool EnableTestModeFirstTime = FALSE;
static bool ST_ON_b = FALSE;
static bool SendDtcForAllActiveAlarms_b = FALSE;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * Alarm_AlarmId: Integer in interval [0...65535]
 * Boolean: Boolean
 * UInt8: Integer in interval [0...255]
 * boolean: Boolean (standard type)
 * sint32: Integer in interval [-2147483648...2147483647] (standard type)
 * uint16: Integer in interval [0...65535] (standard type)
 * uint16: Integer in interval [0...65535] (standard type)
 * uint8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * Alarm_AlarmStatus: Enumeration of integer in interval [0...255] with enumerators
 *   Default_AlarmStatus_AlarmOff (0U)
 *   Default_AlarmStatus_AlarmOn (1U)
 *   Default_AlarmStatus_Error (254U)
 *   Default_AlarmStatus_NotAvailable (255U)
 *
 * Record Types:
 * =============
 * SG_Alarm: Record with elements
 *   AlarmId of type Alarm_AlarmId
 *   AlarmStatus of type Alarm_AlarmStatus
 * SG_AlarmCnt: Record with elements
 *   AlarmId of type Alarm_AlarmId
 *   AlarmStatus of type Alarm_AlarmStatus
 *   AlarmMsgCounter of type uint8
 * SG_AlarmWithSrc: Record with elements
 *   AlarmSrc of type uint16
 *   AlarmId of type Alarm_AlarmId
 *   AlarmStatus of type Alarm_AlarmStatus
 * SG_EemStates: Record with elements
 *   WakeUpSleepRequest of type UInt8
 *   EngineRunningState of type UInt8
 *   ElectricalIgnitionState of type UInt8
 *   DiagInhibit of type UInt8
 *   OverallEemState of type UInt8
 *   AvailableFeedbackState of type UInt8
 * SG_LedsReq: Record with elements
 *   StopLedReq of type boolean
 *   WarningLedReq of type boolean
 * SG_ModuleAlive: Record with elements
 *   Counter of type uint8
 *   Status of type uint8
 *   Dummy of type uint8
 * SG_ModuleVersion: Record with elements
 *   HighValue of type uint8
 *   MiddleValue of type uint8
 *   LowValue of type uint8
 *
 *********************************************************************************************************************/


#define CtApAlm_START_SEC_CODE
//#include "CtApAlm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApAlmDtc_SendDtc
 *
 * This runnable can be invoked concurrently (reentrant implementation).
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SendDtc> of PortPrototype <PpAlmDtc>
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PpOutUnfilteredAlarm_DeAlarmWithSrc(const SG_AlarmWithSrc *data)
 *
 * Inter Runnable Variables:
 * =========================
 *   Explicit Read Access:
 *   ---------------------
 *   void Rte_IrvRead_RCtApAlmDtc_SendDtc_Irv_DbgAlarmWithSrc(SG_AlarmWithSrc *data)
 *   boolean Rte_IrvRead_RCtApAlmDtc_SendDtc_Irv_RciReset(void)
 *
 *   Explicit Write Access:
 *   ----------------------
 *   void Rte_IrvWrite_RCtApAlmDtc_SendDtc_Irv_DbgAlarmWithSrc(const SG_AlarmWithSrc *data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_PpAlmDataBaseDtcToType_LookupDtcType(uint16 Dtc, uint8 *DtcType)
 *     Synchronous Server Invocation. Timeout: None
 *
 * Exclusive Area Access:
 * ======================
 *   void Rte_Enter_Ex_InputAlarm(void)
 *   void Rte_Exit_Ex_InputAlarm(void)
 *   void Rte_Enter_Ex_LedsReq(void)
 *   void Rte_Exit_Ex_LedsReq(void)
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void RCtApAlmDtc_SendDtc(uint16 Src, uint16 Dtc, boolean State)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApAlmDtc_SendDtc_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, CtApAlm_CODE) RCtApAlmDtc_SendDtc(uint16 Src, uint16 Dtc, boolean State) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApAlmDtc_SendDtc
 *********************************************************************************************************************/

  if (FALSE == Rte_IrvRead_RCtApAlmDtc_SendDtc_Irv_RciReset())
  {
#ifdef ALLOW_DEBUG_VIA_XCP
    SG_AlarmWithSrc AlarmWithSrc_t;
	AlarmWithSrc_t.AlarmSrc = Src;
	AlarmWithSrc_t.AlarmId = (Alarm_AlarmId)Dtc;
	AlarmWithSrc_t.AlarmStatus = (Alarm_AlarmStatus)State;
	Rte_IrvWrite_RCtApAlmDtc_SendDtc_Irv_DbgAlarmWithSrc(&AlarmWithSrc_t);
#endif // ALLOW_DEBUG_VIA_XCP
    if (CTAPALMDB_DTC_NOT_VALID != Dtc)
    {
      uint8 DtcType;
      Rte_Call_PpAlmDataBaseDtcToType_LookupDtcType(Dtc, &DtcType);
      switch (DtcType)
      {
	  case CTAPALMDB_NO_TYPE:
	  case CTAPALMDB_ERROR_TYPE:
      case CTAPALMDB_ICON_TYPE:
      case CTAPALMDB_INFO_TYPE:
      case CTAPALMDB_PING_TYPE:
	  case CTAPALMDB_WARNING_TYPE:
        {
          Alarm_AlarmStatus AlarmStatus;
		  SG_AlarmWithSrc AlarmWithSrc_t;
          if (TRUE == State)
          {
            AlarmStatus = Default_AlarmStatus_AlarmOn;
          }
          else
          {
            AlarmStatus = Default_AlarmStatus_AlarmOff;
          }
		  AlarmWithSrc_t.AlarmSrc = Src;
		  AlarmWithSrc_t.AlarmId = Dtc;
		  AlarmWithSrc_t.AlarmStatus = AlarmStatus;

		  Rte_Enter_Ex_InputAlarm();
		  pushAlmToAlmFifo_NoMutex(&InDtcsFifo, Src, Dtc, AlarmStatus);
		  pushAlmToAlmFifo_NoMutex(&ActiveDtcsFifo, Src, Dtc, AlarmStatus);
          Rte_Exit_Ex_InputAlarm();
        }
        break;
	  case CTAPALMDB_SILENT_TYPE:
	    // Do nothing
		break;
	  default:
		 // Do nothing
		 break;
	  }
    }
  }


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApAlm_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PpOutAlmAlive_DeModuleAlive(const SG_ModuleAlive *data)
 *   Std_ReturnType Rte_Write_PpOutAlmLedsReq_DeLedsReq(const SG_LedsReq *data)
 *   Std_ReturnType Rte_Write_PpOutAlmLedsTestModeEnabled_DeLedsTestModeEnabled(boolean data)
 *   Std_ReturnType Rte_Write_PpOutAlmModuleVersion_DeModuleVersion(const SG_ModuleVersion *data)
 *   Std_ReturnType Rte_Write_PpOutAlmReset_DeReset(Boolean data)
 *
 * Inter Runnable Variables:
 * =========================
 *   Explicit Write Access:
 *   ----------------------
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_AliveStatus(const SG_ModuleAlive *data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_DbgAlarmWithSrc(const SG_AlarmWithSrc *data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_DelayUnlockInputAlarmCnt(sint32 data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_DisplayNotAvailable(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_LedsInTestMode(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_LedsReqPrev(const SG_LedsReq *data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_LockInputAlarm(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_LockOutputAlarm(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_MsgCounter(uint8 data)
 *   void Rte_IrvWrite_RCtApAlm_Init_Irv_RciReset(boolean data)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApAlm_Init_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, CtApAlm_CODE) RCtApAlm_Init(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApAlm_Init
 *********************************************************************************************************************/
  
  // Module Version
  const SG_ModuleVersion ModuleVersion = { MODULE_VERSION_HIGH, MODULE_VERSION_MIDDLE, MODULE_VERSION_LOW };
  Rte_Write_PpOutAlmModuleVersion_DeModuleVersion(&ModuleVersion);

  // Alive Init
  Rte_IrvWrite_RCtApAlm_Init_Irv_AliveStatus(&Alive_Init);
  Rte_Write_PpOutAlmAlive_DeModuleAlive(&Alive_Init);

  // Reset Init
  Rte_IrvWrite_RCtApAlm_Init_Irv_RciReset(TRUE);
  Rte_Write_PpOutAlmReset_DeReset(TRUE);
  Rte_IrvWrite_RCtApAlm_Init_Irv_MsgCounter(0x00);

  // Input FIFO Init
  initAlmFifo_NoMutex(&InDtcsFifo);
  setCleanEnableFlag_NoMutex(&InDtcsFifo, TRUE);
  Rte_IrvWrite_RCtApAlm_Init_Irv_LockInputAlarm(TRUE);
  Rte_IrvWrite_RCtApAlm_Init_Irv_DelayUnlockInputAlarmCnt(-1);

  initAlmFifo_NoMutex(&ActiveDtcsFifo);
  setCleanEnableFlag_NoMutex(&ActiveDtcsFifo, TRUE);

  // Outout FIFO Init
  initAlmFifo_NoMutex(&OutDtcsFifo);
  Rte_IrvWrite_RCtApAlm_Init_Irv_LockOutputAlarm(TRUE);
  setCleanEnableFlag_NoMutex(&OutDtcsFifo, TRUE);

  // LEDs Req Init
  initDtcStack_NoMutex(&WarningStack);
  initDtcStack_NoMutex(&ErrorStack);
  Rte_IrvWrite_RCtApAlm_Init_Irv_LedsReqPrev(&LedsReq_Init);
  Rte_Write_PpOutAlmLedsReq_DeLedsReq(&LedsReq_Init);

  // Init Alarm Message Counter
  Rte_IrvWrite_RCtApAlm_Init_Irv_MsgCounter(0x00);

  // DBT LED Test Mode
  Rte_IrvWrite_RCtApAlm_Init_Irv_LedsInTestMode(FALSE);

  // Disable Test mode
  Rte_Write_PpOutAlmLedsTestModeEnabled_DeLedsTestModeEnabled(FALSE);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApAlm_RxEvents
 *
 * This runnable can be invoked concurrently (reentrant implementation).
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <DeValues> of PortPrototype <PpInAlmEemStates> (Activation Reason: Rte_ActivatingEvent_RCtApAlm_RxEvents_ActReason_EemStates)
 *   - triggered on DataReceivedEvent for DataElementPrototype <DeLedsTestMode> of PortPrototype <PpInAlmLedsInTestMode> (Activation Reason: Rte_ActivatingEvent_RCtApAlm_RxEvents_ActReason_LedsInTestMode)
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_PpInAlmEemStates_DeValues(SG_EemStates *data)
 *   Std_ReturnType Rte_Read_PpInAlmLedsInTestMode_DeLedsTestMode(boolean *data)
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PpOutAlmLedsReq_DeLedsReq(const SG_LedsReq *data)
 *   Std_ReturnType Rte_Write_PpOutAlmLedsTestModeEnabled_DeLedsTestModeEnabled(boolean data)
 *   Std_ReturnType Rte_Write_PpOutAlmReset_DeReset(Boolean data)
 *
 * Inter Runnable Variables:
 * =========================
 *   Explicit Read Access:
 *   ---------------------
 *   void Rte_IrvRead_RCtApAlm_RxEvents_Irv_AliveStatus(SG_ModuleAlive *data)
 *   sint32 Rte_IrvRead_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt(void)
 *   boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_LedsInTestMode(void)
 *   boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_LockInputAlarm(void)
 *   boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_RciReset(void)
 *
 *   Explicit Write Access:
 *   ----------------------
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_AliveStatus(const SG_ModuleAlive *data)
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt(sint32 data)
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_DisplayNotAvailable(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsInTestMode(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsReqPrev(const SG_LedsReq *data)
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockInputAlarm(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockOutputAlarm(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_MsgCounter(uint8 data)
 *   void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_RciReset(boolean data)
 *
 * Exclusive Area Access:
 * ======================
 *   void Rte_Enter_Ex_InputAlarm(void)
 *   void Rte_Exit_Ex_InputAlarm(void)
 *   void Rte_Enter_Ex_LedsReq(void)
 *   void Rte_Exit_Ex_LedsReq(void)
 *   void Rte_Enter_Ex_MsgCounter(void)
 *   void Rte_Exit_Ex_MsgCounter(void)
 *   void Rte_Enter_Ex_OutputAlarm(void)
 *   void Rte_Exit_Ex_OutputAlarm(void)
 *   void Rte_Enter_Ex_SpnFmiAlarm(void)
 *   void Rte_Exit_Ex_SpnFmiAlarm(void)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApAlm_RxEvents_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, CtApAlm_CODE) RCtApAlm_RxEvents(Rte_ActivatingEvent_RCtApAlm_RxEvents activationVector) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApAlm_RxEvents
 *********************************************************************************************************************/

  SG_EemStates EemStates_t;
  SG_ModuleAlive Alive_t;
  boolean PrevReset_b, Reset_b, LockInputAlarm_b, LockOutputAlarm_b, LedsTestMode_b, EemStatesReceived_b = FALSE;
  sint32 DelayUnlockInputAlarmCnt;
  bool EnableTestMode = FALSE;

  Rte_IrvRead_RCtApAlm_RxEvents_Irv_AliveStatus(&Alive_t);

  LedsTestMode_b = Rte_IrvRead_RCtApAlm_RxEvents_Irv_LedsInTestMode();
  Reset_b = PrevReset_b = Rte_IrvRead_RCtApAlm_RxEvents_Irv_RciReset();

  if ((Rte_ActivatingEvent_RCtApAlm_RxEvents_ActReason_LedsInTestMode&activationVector) != 0)
  {
	  Rte_Read_PpInAlmLedsInTestMode_DeLedsTestMode(&LedsTestMode_b);
	  Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsInTestMode(LedsTestMode_b);
  }

  if ((Rte_ActivatingEvent_RCtApAlm_RxEvents_ActReason_EemStates&activationVector) != 0)
  {
	  Rte_Read_PpInAlmEemStates_DeValues(&EemStates_t);
	  EemStatesReceived_b = TRUE;
  }

  Rte_Enter_Ex_InputAlarm();
  LockInputAlarm_b = Rte_IrvRead_RCtApAlm_RxEvents_Irv_LockInputAlarm();
  if (FALSE == LedsTestMode_b)
  {
	  if (TRUE == EemStatesReceived_b)
	  {
		  DelayUnlockInputAlarmCnt = Rte_IrvRead_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt();
		  switch (EemStates_t.OverallEemState)
		  {
		  case EemState_PowersourceImminentShutdown:
		  case EemState_PowersourcePendingShutdown:
		  case EemState_FullSleep:
			  SendDtcForAllActiveAlarms_b = FALSE;
			  ST_ON_b = FALSE;
			  Reset_b = TRUE;
			  break;
		  case EemState_PartialSleep:
			  Reset_b = FALSE;//CANCEL Defect2890461
			  LockInputAlarm_b = FALSE;
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  case EemState_OverallWakeUp:
			  EnableTestMode = TRUE;
			  // NO BREAK
		  case EemState_HiddenWakeUp:
			  if (ST_ON_b){
				  SendDtcForAllActiveAlarms_b=TRUE;
			  }
			  Reset_b = FALSE;//CANCEL Defect2890461
			  LockInputAlarm_b = TRUE;//CANCEL Defect2890461
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  case EemState_NotUse6:
		  case EemState_NotUse7:
			  Reset_b = FALSE;
			  LockInputAlarm_b = FALSE;
			  DelayUnlockInputAlarmCnt = -1;
			  // Send an ALM dtc MAYBE
			  break;
		  case EemState_ReadyToStartEngine:
			  SendDtcForAllActiveAlarms_b=FALSE;
			  Reset_b = FALSE;
			  if (DelayUnlockInputAlarmCnt < 0)
			  {
				  DelayUnlockInputAlarmCnt = CTAPALM_DELAY_AFTER_ReadyToStartEngine_CNT_INIT;
			  }
			  break;
		  case EemState_EnginePreStart:
		  case EemState_EngineStart:
		  case EemState_EnginePostStart:
			  Reset_b = FALSE;
			  LockInputAlarm_b = TRUE;
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  case EemState_NotUse12:
		  case EemState_NotUse13:
		  case EemState_NotUse14:
		  case EemState_NotUse15:
			  // Send an ALM dtc MAYBE
			  Reset_b = FALSE;
			  LockInputAlarm_b = FALSE;
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  case EemState_GeneratorOn:
		  case EemState_GeneratorOnHighLoad:
			  ST_ON_b=TRUE;
			  Reset_b = FALSE;
			  Alive_t.Status = ALIVE_STATE_ACTIVE;
			  if (DelayUnlockInputAlarmCnt < 0)
			  {
				  DelayUnlockInputAlarmCnt = CTAPALM_DELAY_AFTER_GeneratorOn_CNT_INIT;
			  }
			  break;
		  case EemState_NotUse18:
		  case EemState_NotUse19:
		  case EemState_NotUse20:
		  case EemState_NotUse21:
		  case EemState_NotUse22:
			  // Send an ALM dtc MAYBE
			  Reset_b = FALSE;
			  LockInputAlarm_b = FALSE;
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  case EemState_EngineStalled:
		  case EemState_GoToStop:
		  case EemState_GoToSleep:
		  case EemState_ReadyToSleep:
			  Reset_b = FALSE;
			  LockInputAlarm_b = FALSE;
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  case EemState_NotUse27:
			  // Send an ALM dtc MAYBE
			  Reset_b = FALSE;
			  LockInputAlarm_b = FALSE;
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  case EemState_ShutdownWakeUp:
		  case EemState_GhostWakeUp:
			  Reset_b = TRUE;
			  break;
		  case EemState_Error:
			  Reset_b = FALSE;
			  LockInputAlarm_b = FALSE;
			  // Send an ALM dtc MAYBE
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  case EemState_NotAvailable:
			  Reset_b = TRUE;
			  break;
		  default:
			  // Send an ALM dtc MAYBE
			  Reset_b = FALSE;
			  LockInputAlarm_b = FALSE;
			  DelayUnlockInputAlarmCnt = -1;
			  break;
		  }
		  Rte_IrvWrite_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt(DelayUnlockInputAlarmCnt);
	  }
  }
  else
  {
	  LockInputAlarm_b = TRUE;
  }
  printf("ST_ON_b = %s, SendDtcForAllActiveAlarms_b = %s\n",
            ST_ON_b ? "TRUE" : "FALSE",
            SendDtcForAllActiveAlarms_b ? "TRUE" : "FALSE");
  if (SendDtcForAllActiveAlarms_b){
	  CopyAlmFifo_Linked(&ActiveDtcsFifo,&InDtcsFifo);
	  SendDtcForAllActiveAlarms_b=FALSE;
  }

  Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockInputAlarm(LockInputAlarm_b);
  setCleanEnableFlag_NoMutex(&InDtcsFifo, LockInputAlarm_b);
  Rte_Exit_Ex_InputAlarm();

  Rte_IrvWrite_RCtApAlm_RxEvents_Irv_RciReset(Reset_b);
  if (PrevReset_b != Reset_b)
  {
    Rte_Write_PpOutAlmReset_DeReset(Reset_b);
  }

  if ((FALSE == EnableTestModeFirstTime) && (TRUE == EnableTestMode))
  {
	  Rte_Write_PpOutAlmLedsTestModeEnabled_DeLedsTestModeEnabled(TRUE);
	  EnableTestModeFirstTime = TRUE;
  }

  if (TRUE == Reset_b)
  {
	// Alive Init
	Alive_t.Status = ALIVE_STATE_INITIALISATION;

	// Input FIFO Init
	Rte_Enter_Ex_InputAlarm();
	initAlmFifo_NoMutex(&InDtcsFifo);
	setCleanEnableFlag_NoMutex(&InDtcsFifo, TRUE);
	Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockInputAlarm(TRUE);
	Rte_IrvWrite_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt(-1);
	Rte_Exit_Ex_InputAlarm();

	initAlmFifo_NoMutex(&ActiveDtcsFifo);
	setCleanEnableFlag_NoMutex(&ActiveDtcsFifo, TRUE);

	// Output FIFO Init
	Rte_Enter_Ex_OutputAlarm();
	initAlmFifo_NoMutex(&OutDtcsFifo);
	setCleanEnableFlag_NoMutex(&OutDtcsFifo, TRUE);
	Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockOutputAlarm(TRUE);
	Rte_Exit_Ex_OutputAlarm();

	Rte_Enter_Ex_MsgCounter();
	Rte_IrvWrite_RCtApAlm_RxEvents_Irv_MsgCounter(0x00);
	Rte_Exit_Ex_MsgCounter();

	// LEDs Req Init
	Rte_Enter_Ex_LedsReq();
	initDtcStack_NoMutex(&WarningStack);
	initDtcStack_NoMutex(&ErrorStack);
	Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsReqPrev(&LedsReq_Init);
	Rte_Exit_Ex_LedsReq();
	Rte_Write_PpOutAlmLedsReq_DeLedsReq(&LedsReq_Init);

	// DBT LED Test Mode
	Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsInTestMode(FALSE);

	// Disable Test mode
	Rte_Write_PpOutAlmLedsTestModeEnabled_DeLedsTestModeEnabled(FALSE);
  }
  else
  {
	  if (TRUE == EemStatesReceived_b)
	  {
		  switch (EemStates_t.AvailableFeedbackState)
		  {
		  case AvailableFeedback_None:
			  LockOutputAlarm_b = TRUE;
			  break;
		  case AvailableFeedback_Full:
		  case AvailableFeedback_TerminalNotAvailable:
			  LockOutputAlarm_b = FALSE;
			  break;
		  case AvailableFeedback_DashboardTerminalNotAvailable:
			  LockOutputAlarm_b = TRUE;
			  break;
		  case AvailableFeedback_DashboardTerminalDisplayingPartially:
			  LockOutputAlarm_b = FALSE;
			  break;
		  case AvailableFeedback_DashboardTerminalDisplayNotAvailable:
			  LockOutputAlarm_b = TRUE;
			  break;
		  default:
			  LockOutputAlarm_b = TRUE;
			  break;
		  }

		  Rte_Enter_Ex_OutputAlarm();
		  Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockOutputAlarm(LockOutputAlarm_b);
		  setCleanEnableFlag_NoMutex(&OutDtcsFifo, LockOutputAlarm_b);
		  Rte_Exit_Ex_OutputAlarm();
	  }

	  // BEGIN Fix Defect 1670779
	  // Alive Active
	  Alive_t.Status = ALIVE_STATE_ACTIVE;
	  // END   Fix Defect 1670779
  }

  Rte_IrvWrite_RCtApAlm_RxEvents_Irv_AliveStatus(&Alive_t);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApAlm_Step
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 50ms
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PpOutAlmAlarm_DeAlarm(const SG_Alarm *data)
 *   Std_ReturnType Rte_Write_PpOutAlmAlarmCnt_DeAlarmCnt(const SG_AlarmCnt *data)
 *   Std_ReturnType Rte_Write_PpOutAlmAlive_DeModuleAlive(const SG_ModuleAlive *data)
 *   Std_ReturnType Rte_Write_PpOutAlmLedsReq_DeLedsReq(const SG_LedsReq *data)
 *   Std_ReturnType Rte_Write_PpOutAlmLedsTestModeEnabled_DeLedsTestModeEnabled(boolean data)
 *
 * Inter Runnable Variables:
 * =========================
 *   Explicit Read Access:
 *   ---------------------
 *   void Rte_IrvRead_RCtApAlm_Step_Irv_AliveStatus(SG_ModuleAlive *data)
 *   sint32 Rte_IrvRead_RCtApAlm_Step_Irv_DelayUnlockInputAlarmCnt(void)
 *   boolean Rte_IrvRead_RCtApAlm_Step_Irv_DisplayNotAvailable(void)
 *   boolean Rte_IrvRead_RCtApAlm_Step_Irv_LedsInTestMode(void)
 *   void Rte_IrvRead_RCtApAlm_Step_Irv_LedsReqPrev(SG_LedsReq *data)
 *   boolean Rte_IrvRead_RCtApAlm_Step_Irv_LockInputAlarm(void)
 *   boolean Rte_IrvRead_RCtApAlm_Step_Irv_LockOutputAlarm(void)
 *   uint8 Rte_IrvRead_RCtApAlm_Step_Irv_MsgCounter(void)
 *   boolean Rte_IrvRead_RCtApAlm_Step_Irv_RciReset(void)
 *
 *   Explicit Write Access:
 *   ----------------------
 *   void Rte_IrvWrite_RCtApAlm_Step_Irv_AliveStatus(const SG_ModuleAlive *data)
 *   void Rte_IrvWrite_RCtApAlm_Step_Irv_DelayUnlockInputAlarmCnt(sint32 data)
 *   void Rte_IrvWrite_RCtApAlm_Step_Irv_LedsReqPrev(const SG_LedsReq *data)
 *   void Rte_IrvWrite_RCtApAlm_Step_Irv_LockInputAlarm(boolean data)
 *   void Rte_IrvWrite_RCtApAlm_Step_Irv_MsgCounter(uint8 data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_PpAlmDataBaseDtcToType_LookupDtcType(uint16 Dtc, uint8 *DtcType)
 *     Synchronous Server Invocation. Timeout: None
 *
 * Exclusive Area Access:
 * ======================
 *   void Rte_Enter_Ex_InputAlarm(void)
 *   void Rte_Exit_Ex_InputAlarm(void)
 *   void Rte_Enter_Ex_LedsReq(void)
 *   void Rte_Exit_Ex_LedsReq(void)
 *   void Rte_Enter_Ex_MsgCounter(void)
 *   void Rte_Exit_Ex_MsgCounter(void)
 *   void Rte_Enter_Ex_OutputAlarm(void)
 *   void Rte_Exit_Ex_OutputAlarm(void)
 *   void Rte_Enter_Ex_SpnFmiAlarm(void)
 *   void Rte_Exit_Ex_SpnFmiAlarm(void)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApAlm_Step_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, CtApAlm_CODE) RCtApAlm_Step(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApAlm_Step
 *********************************************************************************************************************/

  static uint8 AliveCnt = CTAPALM_ALIVE_PERIOD_CNT_INIT;

  // Manage Alive Status
  if (AliveCnt > 0)
  {
	  AliveCnt--;
  }
  else
  {
	SG_ModuleAlive Alive_t;
	Rte_IrvRead_RCtApAlm_Step_Irv_AliveStatus(&Alive_t);
	Alive_t.Counter++;
	Rte_IrvWrite_RCtApAlm_Step_Irv_AliveStatus(&Alive_t);
	Rte_Write_PpOutAlmAlive_DeModuleAlive(&Alive_t);

	AliveCnt = CTAPALM_ALIVE_PERIOD_CNT_INIT;
  }

  if (FALSE == Rte_IrvRead_RCtApAlm_Step_Irv_RciReset())
  {
    // Manage delayed unlock FIFO input
	sint32 DelayUnlockInputAlarmCnt;
	Rte_Enter_Ex_InputAlarm();
	DelayUnlockInputAlarmCnt = Rte_IrvRead_RCtApAlm_Step_Irv_DelayUnlockInputAlarmCnt();
	if (DelayUnlockInputAlarmCnt > 0)
	{
	  DelayUnlockInputAlarmCnt--;
	}
	else if (0 == DelayUnlockInputAlarmCnt)
	{
	  Rte_IrvWrite_RCtApAlm_Step_Irv_LockInputAlarm(FALSE);
	}
	Rte_IrvWrite_RCtApAlm_Step_Irv_DelayUnlockInputAlarmCnt(DelayUnlockInputAlarmCnt);
	Rte_Exit_Ex_InputAlarm();

	// Manage FIFO input
	if (FALSE == Rte_IrvRead_RCtApAlm_Step_Irv_LockInputAlarm())
	{
	  Rte_Enter_Ex_OutputAlarm();
	  if (isFifoFull_NoMutex(&OutDtcsFifo) == FALSE)
	  {
		  boolean InFifoNotEmpty;
		  uint16 Source;
		  Alarm_AlarmId Id;
		  Alarm_AlarmStatus Status;

		  Rte_Enter_Ex_InputAlarm();
		  InFifoNotEmpty = pullAlmFromAlmFifo_NoMutex(&InDtcsFifo, &Source, &Id, &Status);
		  Rte_Exit_Ex_InputAlarm();
		  if (TRUE == InFifoNotEmpty)
		  {
			pushAlmToAlmFifo_NoMutex(&OutDtcsFifo, Source, Id, Status);
printf("Rte_IrvRead_RCtApAlm_Step_Irv_LockInputAlarm() = %d\n", Rte_IrvRead_RCtApAlm_Step_Irv_LockInputAlarm());

		  }
	  }
	  Rte_Exit_Ex_OutputAlarm();
	}

	// Manage FIFO output

	if ((FALSE == Rte_IrvRead_RCtApAlm_Step_Irv_LockOutputAlarm()))
	{
      boolean OutFifoNotEmpty;
	  uint16 Source;
	  Alarm_AlarmId Id;
	  Alarm_AlarmStatus Status;

	  Rte_Enter_Ex_OutputAlarm();
	  OutFifoNotEmpty = pullAlmFromAlmFifo_NoMutex(&OutDtcsFifo, &Source, &Id, &Status);
      Rte_Exit_Ex_OutputAlarm();
	  
	  if (TRUE == OutFifoNotEmpty)
	  {
        uint8 DtcType;
		boolean SendLedReq = TRUE;
		boolean SendDtc = TRUE;
		SG_LedsReq LedsReq_Prev;
		SG_LedsReq LedsReq_New = { FALSE, FALSE };

		Rte_Call_PpAlmDataBaseDtcToType_LookupDtcType(Id, &DtcType);
		switch(DtcType)
		{
        case CTAPALMDB_ERROR_TYPE:
		  Rte_Enter_Ex_LedsReq();
		  if (Default_AlarmStatus_AlarmOn == Status)
		  {
			addDtcInStack_NoMutex(&ErrorStack, Id);
		  }
		  else
		  {
			delDtcFromStack_NoMutex(&ErrorStack, Id);
		  }
		  Rte_Exit_Ex_LedsReq();
          break;
        case CTAPALMDB_ICON_TYPE:
        case CTAPALMDB_INFO_TYPE:
        case CTAPALMDB_PING_TYPE:
		  SendLedReq = FALSE;
          break;
        case CTAPALMDB_WARNING_TYPE:
		  Rte_Enter_Ex_LedsReq();
		  if (Default_AlarmStatus_AlarmOn == Status)
		  {
			addDtcInStack_NoMutex(&WarningStack, Id);
			printf("Rte_IrvRead_RCtApAlm_Step_Irv_LockOutputAlarm() = %d\n", Rte_IrvRead_RCtApAlm_Step_Irv_LockOutputAlarm());
		  }
		  else
		  {
			delDtcFromStack_NoMutex(&WarningStack, Id);
		  }
		  Rte_Exit_Ex_LedsReq();
          break;
		default:
          SendDtc = FALSE;
		  break;
		}
		if (TRUE == SendDtc)
		{
          SG_Alarm Alarm;
		  SG_AlarmCnt AlarmCnt;
		  uint8 MsgCounter;

		  if (TRUE == SendLedReq)
		  {
			  Rte_IrvRead_RCtApAlm_Step_Irv_LedsReqPrev(&LedsReq_Prev);
			  Rte_Enter_Ex_LedsReq();
			  LedsReq_New.WarningLedReq = (getDtcNb_NoMutex(&WarningStack) > 0);
			  LedsReq_New.StopLedReq = (getDtcNb_NoMutex(&ErrorStack) > 0);
			  Rte_Exit_Ex_LedsReq();
			  if ((LedsReq_Prev.WarningLedReq != LedsReq_New.WarningLedReq) ||
				  (LedsReq_Prev.StopLedReq != LedsReq_New.StopLedReq)
				  )
			  {
				  Rte_Write_PpOutAlmLedsReq_DeLedsReq(&LedsReq_New);
			  }
			  Rte_IrvWrite_RCtApAlm_Step_Irv_LedsReqPrev(&LedsReq_New);
		  }
		  printf("Rte_() = %d\n", Rte_IrvRead_RCtApAlm_Step_Irv_LockOutputAlarm());

		  AlarmCnt.AlarmId = Alarm.AlarmId = Id;
		  AlarmCnt.AlarmStatus = Alarm.AlarmStatus = Status;
		  Rte_Enter_Ex_MsgCounter();
		  MsgCounter = Rte_IrvRead_RCtApAlm_Step_Irv_MsgCounter();
		  Rte_IrvWrite_RCtApAlm_Step_Irv_MsgCounter(MsgCounter + 1);
		  Rte_Exit_Ex_MsgCounter();
		  AlarmCnt.AlarmMsgCounter = MsgCounter;
		  Rte_Write_PpOutAlmAlarm_DeAlarm(&Alarm);
		  Rte_Write_PpOutAlmAlarmCnt_DeAlarmCnt(&AlarmCnt);
		}
	  }
	}
  }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define CtApAlm_STOP_SEC_CODE
//#include "CtApAlm_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 MISRA 2012 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_0315:  MISRA rule: Dir1.1
     Reason:     Pointer cast to void because generic access is necessary.
     Risk:       No functional risk. Only a cast to uint8* is performed.
     Prevention: Not required.

   MD_Rte_0624:  MISRA rule: Rule8.3
     Reason:     This MISRA violation is a consequence from the RTE requirements [SWS_Rte_01007] [SWS_Rte_01150].
                 The typedefs are never used in the same context.
     Risk:       No functional risk. Only a cast to uint8* is performed.
     Prevention: Not required.

   MD_Rte_2987:  MISRA rule: Rule2.2
     Reason:     Used to simplify code generation.
     Risk:       No functional risk. There is no side effect.
     Prevention: Not required.

   MD_Rte_3206:  MISRA rule: Rule2.7
     Reason:     The parameter are not used by the code in all possible code variants.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_3226:  MISRA rule: Rule13.4
     Reason:     Needed for function like macro to do arithmetic operations in sub macros
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_Os:
     Reason:     This justification is used as summary justification for all deviations caused by the MICROSAR OS
                 which is for testing of the RTE. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

   MD_Rte_TestCode:
     Reason:     This justification is used as summary justification for all deviations caused by wrong analysis tool results.
                 The used analysis tool QAC 9.0 sometimes creates wrong messages. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
