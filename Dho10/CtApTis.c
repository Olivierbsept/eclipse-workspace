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
 *             File:  CtApTis.c
 *           Config:  C_UCP.dpa
 *        SW-C Type:  CtApTis
 *
 *        Generator:  MICROSAR RTE Generator Version 4.21.0
 *                    RTE Core Version 1.21.0
 *          License:  CBD1600472
 *
 *      Description:  C-Code implementation template for SW-C <CtApTis>
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

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************
 *
 * Data Types:
 * ===========
 * Dcm_NegativeResponseCodeType
 *   
 *
 * Dcm_NegativeResponseCodeType
 *   
 *
 * Dcm_OpStatusType
 *   
 *
 *
 * Port Prototypes:
 * ================
 * PpInFumHourTis
 *
 * PpInFumIdTis
 *
 * PpInLimHourTis
 *
 * PpInLimIdTis
 *
 * PpOutVbmIdCANmsg
 *
 *
 * Runnable Entities:
 * ==================
 * RCtApTis_Step50ms
 *   
 *
 *********************************************************************************************************************/

#include "Rte_CtApTis.h"
#include "CtComEemEnum.h"
#include "Dho.h"

SG_EemStates EemStates;
boolean MachineTimeReducedOnce;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "string.h"
#include "CtApTisModuleVersion.h"

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
 * Rte_DT_SG_CmaTis_0: Integer in interval [0...65535]
 * Rte_DT_SG_CmaTis_1: Integer in interval [0...4294967295]
 * Rte_DT_SG_HourCan_0: Integer in interval [0...4294967295]
 * boolean: Boolean (standard type)
 * uint32: Integer in interval [0...4294967295] (standard type)
 * uint32: Integer in interval [0...4294967295] (standard type)
 * uint8: Integer in interval [0...255] (standard type)
 * uint8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * Dcm_NegativeResponseCodeType: Enumeration of integer in interval [0...254] with enumerators
 *   DCM_E_POSITIVERESPONSE (0U)
 *   DCM_E_GENERALREJECT (16U)
 *   DCM_E_SERVICENOTSUPPORTED (17U)
 *   DCM_E_SUBFUNCTIONNOTSUPPORTED (18U)
 *   DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT (19U)
 *   DCM_E_RESPONSETOOLONG (20U)
 *   DCM_E_BUSYREPEATREQUEST (33U)
 *   DCM_E_CONDITIONSNOTCORRECT (34U)
 *   DCM_E_REQUESTSEQUENCEERROR (36U)
 *   DCM_E_NORESPONSEFROMSUBNETCOMPONENT (37U)
 *   DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION (38U)
 *   DCM_E_REQUESTOUTOFRANGE (49U)
 *   DCM_E_SECURITYACCESSDENIED (51U)
 *   DCM_E_INVALIDKEY (53U)
 *   DCM_E_EXCEEDNUMBEROFATTEMPTS (54U)
 *   DCM_E_REQUIREDTIMEDELAYNOTEXPIRED (55U)
 *   DCM_E_UPLOADDOWNLOADNOTACCEPTED (112U)
 *   DCM_E_TRANSFERDATASUSPENDED (113U)
 *   DCM_E_GENERALPROGRAMMINGFAILURE (114U)
 *   DCM_E_WRONGBLOCKSEQUENCECOUNTER (115U)
 *   DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING (120U)
 *   DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION (126U)
 *   DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION (127U)
 *   DCM_E_RPMTOOHIGH (129U)
 *   DCM_E_RPMTOOLOW (130U)
 *   DCM_E_ENGINEISRUNNING (131U)
 *   DCM_E_ENGINEISNOTRUNNING (132U)
 *   DCM_E_ENGINERUNTIMETOOLOW (133U)
 *   DCM_E_TEMPERATURETOOHIGH (134U)
 *   DCM_E_TEMPERATURETOOLOW (135U)
 *   DCM_E_VEHICLESPEEDTOOHIGH (136U)
 *   DCM_E_VEHICLESPEEDTOOLOW (137U)
 *   DCM_E_THROTTLE_PEDALTOOHIGH (138U)
 *   DCM_E_THROTTLE_PEDALTOOLOW (139U)
 *   DCM_E_TRANSMISSIONRANGENOTINNEUTRAL (140U)
 *   DCM_E_TRANSMISSIONRANGENOTINGEAR (141U)
 *   DCM_E_BRAKESWITCH_NOTCLOSED (143U)
 *   DCM_E_SHIFTERLEVERNOTINPARK (144U)
 *   DCM_E_TORQUECONVERTERCLUTCHLOCKED (145U)
 *   DCM_E_VOLTAGETOOHIGH (146U)
 *   DCM_E_VOLTAGETOOLOW (147U)
 *   DCM_E_VMSCNC_0 (240U)
 *   DCM_E_VMSCNC_1 (241U)
 *   DCM_E_VMSCNC_2 (242U)
 *   DCM_E_VMSCNC_3 (243U)
 *   DCM_E_VMSCNC_4 (244U)
 *   DCM_E_VMSCNC_5 (245U)
 *   DCM_E_VMSCNC_6 (246U)
 *   DCM_E_VMSCNC_7 (247U)
 *   DCM_E_VMSCNC_8 (248U)
 *   DCM_E_VMSCNC_9 (249U)
 *   DCM_E_VMSCNC_A (250U)
 *   DCM_E_VMSCNC_B (251U)
 *   DCM_E_VMSCNC_C (252U)
 *   DCM_E_VMSCNC_D (253U)
 *   DCM_E_VMSCNC_E (254U)
 * Dcm_OpStatusType: Enumeration of integer in interval [0...64] with enumerators
 *   DCM_INITIAL (0U)
 *   DCM_PENDING (1U)
 *   DCM_CANCEL (2U)
 *   DCM_FORCE_RCRRP_OK (3U)
 *   DCM_FORCE_RCRRP_NOT_OK (64U)
 *
 * Array Types:
 * ============
 * Dcm_Data10ByteType: Array with 10 element(s) of type uint8
 * Dcm_Data2ByteType: Array with 2 element(s) of type uint8
 * Dcm_Data4ByteType: Array with 4 element(s) of type uint8
 *
 * Record Types:
 * =============
 * SG_CmaTis: Record with elements
 *   ConfigMachineType of type Rte_DT_SG_CmaTis_0
 *   ConfigMachineNumber of type Rte_DT_SG_CmaTis_1
 * SG_EemStates: Record with elements
 *   WakeUpSleepRequest of type uint8
 *   EngineRunningState of type uint8
 *   ElectricalIgnitionState of type uint8
 *   DiagInhibit of type uint8
 *   OverallEemState of type uint8
 *   AvailableFeedbackState of type uint8
 * SG_HourCan: Record with elements
 *   HourReceivedFromCan of type Rte_DT_SG_HourCan_0
 * SG_Hours: Record with elements
 *   EngTotalHoursOfOperation of type uint32
 *   u32_TotalEngineRevolutions of type uint32
 * SG_ModuleVersion: Record with elements
 *   HighValue of type uint8
 *   MiddleValue of type uint8
 *   LowValue of type uint8
 * sTotalCounterHours: Record with elements
 *   TotalCountEngine1OpHours of type uint32
 *   TotalCountEngine2OpHours of type uint32
 * sTotalVehicleHours: Record with elements
 *   TotalVehicleHours of type uint32
 *
 *********************************************************************************************************************/


#define CtApTis_START_SEC_CODE
#include "CtApTis_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MachineId_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DataServices_Data_DHO_MI_Read>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType MachineId_ConditionCheckRead(Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Data_DHO_MI_Read_DCM_E_PENDING
 *   RTE_E_DataServices_Data_DHO_MI_Read_DCM_E_TIMEINVALID
 *   RTE_E_DataServices_Data_DHO_MI_Read_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: MachineId_ConditionCheckRead_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, CtApTis_CODE) MachineId_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) ErrorCode) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MachineId_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/

	if (ErrorCode != NULL){
		*ErrorCode = DCM_E_POSITIVERESPONSE;
		return RTE_E_OK;
	}
	else{
		return RTE_E_DataServices_Data_DHO_MI_Read_E_NOT_OK;
	}

	/**********************************************************************************************************************
	* DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
	*********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MachineId_Read
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DataServices_Data_DHO_MI_Read>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_PpInCmaTis_DeCmaTis(SG_CmaTis *data)
 *   Std_ReturnType Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(sTotalCounterHours *data)
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType MachineId_Read(Dcm_OpStatusType OpStatus, uint8 *Data)
 *     Argument Data: uint8* is of type Dcm_Data10ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Data_DHO_MI_Read_DCM_E_PENDING
 *   RTE_E_DataServices_Data_DHO_MI_Read_DCM_E_TIMEINVALID
 *   RTE_E_DataServices_Data_DHO_MI_Read_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: MachineId_Read_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, CtApTis_CODE) MachineId_Read(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) Data) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MachineId_Read (returns application error)
 *********************************************************************************************************************/

	Std_ReturnType fct_status;
	SG_CmaTis Read_PpInCmaTis_DeCmaTis;
	sTotalCounterHours Read_PpInOpHoursCANmsg_TotalCounterHours;
	uint16 MachineType		= 0xFFFF;
	uint32 MachineNumber	= 0XFFFFFFFF;
	uint32 MachineTime		= 0XFFFFFFFF;

	/*************************************************
	* Direct Function Accesses
	*************************************************/
	if (Data == NULL){
		return RTE_E_INVALID;
	}

	fct_status = Rte_Read_CtApTis_PpInCmaTis_DeCmaTis(&Read_PpInCmaTis_DeCmaTis);
	if (RTE_E_OK == fct_status){
		MachineType = Read_PpInCmaTis_DeCmaTis.ConfigMachineType;
		MachineNumber = Read_PpInCmaTis_DeCmaTis.ConfigMachineNumber;
	}

	fct_status = Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(&Read_PpInOpHoursCANmsg_TotalCounterHours);
	if (RTE_E_OK == fct_status){
		MachineTime = Read_PpInOpHoursCANmsg_TotalCounterHours.TotalCountEngine1OpHours;
	}

	Data[0] = (uint8)(MachineTime >> 24);
	Data[1] = (uint8)(MachineTime >> 16);
	Data[2] = (uint8)(MachineTime >> 8);
	Data[3] = (uint8)(MachineTime);

	Data[4] = (uint8)(MachineType >> 8);
	Data[5] = (uint8)(MachineType);

	Data[6] = (uint8)(MachineNumber >> 24);
	Data[7] = (uint8)(MachineNumber >> 16);
	Data[8] = (uint8)(MachineNumber >> 8);
	Data[9] = (uint8)(MachineNumber);
	return RTE_E_OK;

	/**********************************************************************************************************************
	* DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
	*********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: MachineId_Write
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DataServices_Data_DHO_MI_Read>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(sTotalCounterHours *data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_PpMachineCounter_SetMachineCounter(uint32 set_MachineCounter)
 *     Synchronous Server Invocation. Timeout: None
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_DataServices_Data_Config_MachineNumber_Read_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data4ByteType
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DataServices_Data_Config_MachineNumber_Read_DCM_E_PENDING, RTE_E_DataServices_Data_Config_MachineNumber_Read_E_NOT_OK
 *   Std_ReturnType Rte_Call_DataServices_Data_Config_Machinetype_Read_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data2ByteType
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DataServices_Data_Config_Machinetype_Read_DCM_E_PENDING, RTE_E_DataServices_Data_Config_Machinetype_Read_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType MachineId_Write(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
 *     Argument Data: uint8* is of type Dcm_Data10ByteType
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DataServices_Data_DHO_MI_Read_DCM_E_PENDING
 *   RTE_E_DataServices_Data_DHO_MI_Read_DCM_E_TIMEINVALID
 *   RTE_E_DataServices_Data_DHO_MI_Read_E_NOT_OK
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: MachineId_Write_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(Std_ReturnType, CtApTis_CODE) MachineId_Write(P2CONST(uint8, AUTOMATIC, RTE_CTAPTIS_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) ErrorCode) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: MachineId_Write (returns application error)
 *********************************************************************************************************************/

	Std_ReturnType fct_status;
	sTotalCounterHours Read_PpInOpHoursCANmsg_TotalCounterHours;
	Dcm_NegativeResponseCodeType Call_DataServices_Data_Config_MachineNumber_Read_WriteData_ErrorCode = 0U;
	Dcm_NegativeResponseCodeType Call_DataServices_Data_Config_Machinetype_Read_WriteData_ErrorCode = 0U;
	Dcm_Data4ByteType Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data = {0U, 0U, 0U, 0U};
	Dcm_Data2ByteType Call_DataServices_Data_Config_Machinetype_Read_WriteData_Data = {0U, 0U};

	uint32 MachineTime				= 0XFFFFFFFF;
	uint16 MachineType				= 0xFFFF;
	uint32 MachineNumber			= 0XFFFFFFFF;
	uint32 PAR_TimeMaxSec			= 180000;
	uint8 PAR_TimeInvalid			= 0x15;
	uint8 PAR_TimeAlreadyReduced	= 0x16;

	/*************************************************
	* Direct Function Accesses
	*************************************************/
	if (Data == NULL || ErrorCode == NULL){
		return RTE_E_INVALID;
	}// pointers null

	fct_status = Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(&Read_PpInOpHoursCANmsg_TotalCounterHours);
	if (RTE_E_OK == fct_status){
		MachineTime = Read_PpInOpHoursCANmsg_TotalCounterHours.TotalCountEngine1OpHours;
	}
	if (0xFFFFFFFF == MachineTime){
		*ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
		return RTE_E_INVALID;
	}// MachineTime not readable

	uint32 MachineIdTimeRequest = ((uint32)Data[0] << 24) | ((uint32)Data[1] << 16) | ((uint32)Data[2] << 8) | ((uint32)Data[3]);
	if ((MachineIdTimeRequest < MachineTime) && (MachineTimeReducedOnce == true)){
		*ErrorCode = PAR_TimeAlreadyReduced;
		return RTE_E_INVALID;
	}//MachineTime already reduced

	if ((MachineIdTimeRequest < MachineTime) && ((MachineTime - MachineIdTimeRequest) > PAR_TimeMaxSec)){
		*ErrorCode = PAR_TimeInvalid;
		return RTE_E_INVALID;
	}//MachineTime and MachineIdTimeRequest not coherent

	Call_DataServices_Data_Config_Machinetype_Read_WriteData_Data[0] = (uint8)Data[4];
	Call_DataServices_Data_Config_Machinetype_Read_WriteData_Data[1] = (uint8)Data[5];
	fct_status = Rte_Call_DataServices_Data_Config_Machinetype_Read_WriteData(Call_DataServices_Data_Config_Machinetype_Read_WriteData_Data, DCM_INITIAL, &Call_DataServices_Data_Config_Machinetype_Read_WriteData_ErrorCode);
	if (fct_status != RTE_E_OK){
		*ErrorCode = Call_DataServices_Data_Config_Machinetype_Read_WriteData_ErrorCode;
		return fct_status;
	}//MachineType writeData error

	Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data[0] = (uint8)Data[6];
	Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data[1] = (uint8)Data[7];
	Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data[2] = (uint8)Data[8];
	Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data[3] = (uint8)Data[9];
	fct_status = Rte_Call_DataServices_Data_Config_MachineNumber_Read_WriteData(Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data, DCM_INITIAL, &Call_DataServices_Data_Config_MachineNumber_Read_WriteData_ErrorCode);
	if (fct_status != RTE_E_OK){
		*ErrorCode = Call_DataServices_Data_Config_MachineNumber_Read_WriteData_ErrorCode;
		return fct_status;
	}//MachineNumber writeData error

	fct_status = Rte_Call_PpMachineCounter_SetMachineCounter(MachineIdTimeRequest);
	*ErrorCode = DCM_E_POSITIVERESPONSE;

	if (MachineIdTimeRequest < MachineTime){
		MachineTimeReducedOnce = true;
	}
	trigs.DiagTrig = true;
	return fct_status;
	/**********************************************************************************************************************
	* DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
	*********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApTis_Init
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
 *   Std_ReturnType Rte_Write_PpOutTisModuleVersion_DeModuleVersion(const SG_ModuleVersion *data)
 *
 * Inter Runnable Variables:
 * =========================
 *   Explicit Write Access:
 *   ----------------------
 *   void Rte_IrvWrite_RCtApTis_Init_Irv_PreviousHour(uint32 data)
 *   void Rte_IrvWrite_RCtApTis_Init_Irv_StartRecvOpHours(boolean data)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApTis_Init_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, CtApTis_CODE) RCtApTis_Init(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
	/**********************************************************************************************************************
	* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
	* Symbol: RCtApTis_Init
	*********************************************************************************************************************/

	const SG_ModuleVersion ModuleVersion = { MODULE_VERSION_HIGH, MODULE_VERSION_MIDDLE, MODULE_VERSION_LOW };
	Rte_Write_PpOutTisModuleVersion_DeModuleVersion(&ModuleVersion);
	Rte_IrvWrite_RCtApTis_Init_Irv_StartRecvOpHours(FALSE);
	Rte_IrvWrite_RCtApTis_Init_Irv_PreviousHour(0xFFFFFFFF);
	EemStates.OverallEemState = EemState_NotAvailable;
	MachineTimeReducedOnce = false;

	dhoConfigs.DiagTrigCfg = true;
	dhoConfigs.ParamCheckCfg = false;
	DhoInit(dhoConfigs);

	ident0 = (DhoIdent) { 0xFFFF,0xFFFFFFFF,0xFFFFFFFF };
	idents = (DhoIdents){ (DhoIdent) { 0xFFFF, 0xFFFFFFFF, 0xFFFFFFFF }, (DhoIdent) { 0xFFFF, 0xFFFFFFFF, 0xFFFFFFFF } };
	trigs = (DhoTrigs){ false, false, false, false, false, false, false };

	/**********************************************************************************************************************
	* DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
	*********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApTis_RxEvents
 *
 * This runnable can be invoked concurrently (reentrant implementation).
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <DeCmaTis> of PortPrototype <PpInCmaTis> (Activation Reason: Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_VbmId)
 *   - triggered on DataReceivedEvent for DataElementPrototype <DeValues> of PortPrototype <PpInEemStates> (Activation Reason: Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_EemStates)
 *   - triggered on DataReceivedEvent for DataElementPrototype <DeOperatingHours> of PortPrototype <PpInFumHourTis> (Activation Reason: Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_FumHour)
 *   - triggered on DataReceivedEvent for DataElementPrototype <DeEcuTis> of PortPrototype <PpInFumIdTis> (Activation Reason: Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_FumId)
 *   - triggered on DataReceivedEvent for DataElementPrototype <DeOperatingHours> of PortPrototype <PpInLimHourTis> (Activation Reason: Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_LimHour)
 *   - triggered on DataReceivedEvent for DataElementPrototype <DeEcuTis> of PortPrototype <PpInLimIdTis> (Activation Reason: Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_LimId)
 *   - triggered on DataReceivedEvent for DataElementPrototype <TotalCounterHours> of PortPrototype <PpInOpHoursCANmsg> (Activation Reason: Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_OpHoursCANmsg)
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_PpInCmaTis_DeCmaTis(SG_CmaTis *data)
 *   Std_ReturnType Rte_Read_PpInEemStates_DeValues(SG_EemStates *data)
 *   Std_ReturnType Rte_Read_PpInFumHourTis_DeOperatingHours(SG_HourCan *data)
 *   Std_ReturnType Rte_Read_PpInFumIdTis_DeEcuTis(SG_CmaTis *data)
 *   Std_ReturnType Rte_Read_PpInLimHourTis_DeOperatingHours(SG_HourCan *data)
 *   Std_ReturnType Rte_Read_PpInLimIdTis_DeEcuTis(SG_CmaTis *data)
 *   Std_ReturnType Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(sTotalCounterHours *data)
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PpOutStdHours_DeStdHours(const SG_Hours *data)
 *   Std_ReturnType Rte_Write_PpOutTisOpHours_DeOpHoursInternal(uint32 data)
 *   Std_ReturnType Rte_Write_PpOutTisOpHoursClaasCANmsg_TotalVehicleHours(const sTotalVehicleHours *data)
 *   Std_ReturnType Rte_Write_PpOutTisOpHoursHydCANmsg_TotalVehicleHours(const sTotalVehicleHours *data)
 *
 * Inter Runnable Variables:
 * =========================
 *   Explicit Read Access:
 *   ---------------------
 *   uint32 Rte_IrvRead_RCtApTis_RxEvents_Irv_PreviousHour(void)
 *   boolean Rte_IrvRead_RCtApTis_RxEvents_Irv_StartRecvOpHours(void)
 *
 *   Explicit Write Access:
 *   ----------------------
 *   void Rte_IrvWrite_RCtApTis_RxEvents_Irv_PreviousHour(uint32 data)
 *   void Rte_IrvWrite_RCtApTis_RxEvents_Irv_StartRecvOpHours(boolean data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_PpMasterConfig_StartCanTransmission(void)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PpMasterConfig_StartMachineCounter(void)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PpMasterConfig_StopMachineCounter(void)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApTis_RxEvents_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, CtApTis_CODE) RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents activationVector) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
	/**********************************************************************************************************************
	* DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
	* Symbol: RCtApTis_RxEvents
	*********************************************************************************************************************/

	if ((Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_EemStates & activationVector) != 0)
	{
		Rte_Read_PpInEemStates_DeValues(&EemStates);
		switch (EemStates.OverallEemState)
		{
		case EemState_GeneratorOn:
		case EemState_GeneratorOnHighLoad:
			Rte_Call_PpMasterConfig_StartMachineCounter();
			break;
		case EemState_ReadyToStartEngine:
			Rte_Call_PpMasterConfig_StopMachineCounter();
			MachineTimeReducedOnce = false;
		default:
			Rte_Call_PpMasterConfig_StopMachineCounter();
			break;
		}

		if (FALSE == Rte_IrvRead_RCtApTis_RxEvents_Irv_StartRecvOpHours())
		{
			Rte_Call_PpMasterConfig_StartCanTransmission();
			Rte_IrvWrite_RCtApTis_RxEvents_Irv_StartRecvOpHours(TRUE);
		}
	}

	if ((Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_OpHoursCANmsg & activationVector) != 0)
	{
		sTotalCounterHours TotalCounterHours;
		sTotalVehicleHours CANmsg_TotalCounterHours;
		SG_Hours CANmsg_StdHours;

		Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(&TotalCounterHours);
		CANmsg_TotalCounterHours.TotalVehicleHours = TotalCounterHours.TotalCountEngine1OpHours;
		ident0.mh = CANmsg_TotalCounterHours.TotalVehicleHours;

		Rte_Write_PpOutTisOpHours_DeOpHoursInternal(TotalCounterHours.TotalCountEngine1OpHours);
		Rte_Write_PpOutTisOpHoursClaasCANmsg_TotalVehicleHours(&CANmsg_TotalCounterHours);
		Rte_Write_PpOutTisOpHoursHydCANmsg_TotalVehicleHours(&CANmsg_TotalCounterHours);

		CANmsg_StdHours.EngTotalHoursOfOperation = TotalCounterHours.TotalCountEngine1OpHours / 180;//to send every 3 minutes
		if (CANmsg_StdHours.EngTotalHoursOfOperation != Rte_IrvRead_RCtApTis_RxEvents_Irv_PreviousHour())
		{
			Rte_IrvWrite_RCtApTis_RxEvents_Irv_PreviousHour(CANmsg_StdHours.EngTotalHoursOfOperation);
			CANmsg_StdHours.u32_TotalEngineRevolutions = 0xFFFFFFFF;
			Rte_Write_PpOutStdHours_DeStdHours(&CANmsg_StdHours);
		}
	}

	if ((Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_FumHour & activationVector) != 0)
	{
		uint32 data;
		SG_HourCan CANmsg_Hour;
		Std_ReturnType returnType = Rte_Read_PpInFumHourTis_DeOperatingHours(&CANmsg_Hour);
		data = CANmsg_Hour.HourReceivedFromCan;
		if (E_OK == returnType) {
			idents.Ident1.mh = data;
			trigs.Rx1Trig = true;
		}
	}

	if ((Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_FumId & activationVector) != 0)
	{
		SG_CmaTis data;
		Std_ReturnType returnType = Rte_Read_PpInFumIdTis_DeEcuTis(&data);
		if (E_OK == returnType) {
			idents.Ident1.mn = data.ConfigMachineNumber;
			idents.Ident1.mt = data.ConfigMachineType;
		}
	}

	if ((Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_LimHour & activationVector) != 0)
	{
		uint32 data;
		SG_HourCan CANmsg_Hour;
		Std_ReturnType returnType = Rte_Read_PpInLimHourTis_DeOperatingHours(&CANmsg_Hour);
		data = CANmsg_Hour.HourReceivedFromCan;
		if (E_OK == returnType) {
			idents.Ident2.mh = data;
			trigs.Rx2Trig = true;
		}
	}

	if ((Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_LimId & activationVector) != 0)
	{
		SG_CmaTis data;
		Std_ReturnType returnType = Rte_Read_PpInLimIdTis_DeEcuTis(&data);
		if (E_OK == returnType) {
			idents.Ident2.mn = data.ConfigMachineNumber;
			idents.Ident2.mt = data.ConfigMachineType;
		}
	}

	if ((Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_VbmId & activationVector) != 0)
	{
		SG_CmaTis data;
		Std_ReturnType returnType = Rte_Read_PpInCmaTis_DeCmaTis(&data);
		if (E_OK == returnType) {
			ident0.mn = data.ConfigMachineNumber;
			ident0.mt = data.ConfigMachineType;
		}
	}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApTis_Step50ms
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 50ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(sTotalCounterHours *data)
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PpOutStdHours_DeStdHours(const SG_Hours *data)
 *   Std_ReturnType Rte_Write_PpOutTisOpHours_DeOpHoursInternal(uint32 data)
 *   Std_ReturnType Rte_Write_PpOutTisOpHoursClaasCANmsg_TotalVehicleHours(const sTotalVehicleHours *data)
 *   Std_ReturnType Rte_Write_PpOutTisOpHoursHydCANmsg_TotalVehicleHours(const sTotalVehicleHours *data)
 *   Std_ReturnType Rte_Write_PpOutTisOpHoursJ1939CANmsg_TotalVehicleHours(const sTotalVehicleHours *data)
 *   Std_ReturnType Rte_Write_PpOutVbmIdCANmsg_DeEcuTis(const SG_CmaTis *data)
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of documentation area >>                  DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApTis_Step50ms_doc
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of documentation area >>                    DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

FUNC(void, CtApTis_CODE) RCtApTis_Step50ms(void) /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApTis_Step50ms
 *********************************************************************************************************************/

	compteurStep50ms++;
	if ((EemStates.OverallEemState != EemState_ReadyToStartEngine) &&
		(EemStates.OverallEemState != EemState_GeneratorOnHighLoad) &&
		(EemStates.OverallEemState != EemState_GeneratorOn)){

		if (0 == (compteurStep50ms %PERIOD_MSGID50ms_3s)){
			sTotalVehicleHours TotalVehicleHours;
			TotalVehicleHours.TotalVehicleHours = ident0.mh;
			Rte_Write_PpOutTisOpHoursJ1939CANmsg_TotalVehicleHours(&TotalVehicleHours);
		}
	}
	else{
		if (EemState_ReadyToStartEngine == EemStates.OverallEemState){
			DhoCall50ms_Diag(&trigs, &ident0, idents);
		}
		else if (EemState_GeneratorOnHighLoad == EemStates.OverallEemState ||
			EemState_GeneratorOn == EemStates.OverallEemState){
			DhoCall50ms(&trigs, &ident0, idents);
		}
		if (trigs.TxTrig){
			sTotalVehicleHours TotalVehicleHours;
			TotalVehicleHours.TotalVehicleHours = ident0.mh;
			Std_ReturnType fct_status = Rte_Write_PpOutTisOpHoursJ1939CANmsg_TotalVehicleHours(&TotalVehicleHours);
			if (E_OK == fct_status) trigs.TxTrig = false;
		}
		if (trigs.MhTrig){
			Std_ReturnType fct_status = Rte_Call_PpMachineCounter_SetMachineCounter(ident0.mh);
			if (E_OK == fct_status) trigs.MhTrig = false;
		}
		if (trigs.MnTrig){
			Dcm_NegativeResponseCodeType Call_DataServices_Data_Config_MachineNumber_Read_WriteData_ErrorCode = 0U;
			Dcm_NegativeResponseCodeType Call_DataServices_Data_Config_Machinetype_Read_WriteData_ErrorCode = 0U;
			Dcm_Data4ByteType Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data = { 0U, 0U, 0U, 0U };
			Dcm_Data2ByteType Call_DataServices_Data_Config_Machinetype_Read_WriteData_Data = { 0U, 0U };

			Call_DataServices_Data_Config_Machinetype_Read_WriteData_Data[0] = (uint8)(ident0.mt >> 8);
			Call_DataServices_Data_Config_Machinetype_Read_WriteData_Data[1] = (uint8)(ident0.mt);

			Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data[0] = (uint8)(ident0.mn >> 24);
			Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data[1] = (uint8)(ident0.mn >> 16);
			Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data[2] = (uint8)(ident0.mn >> 8);
			Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data[3] = (uint8)(ident0.mn);

			Std_ReturnType fct_status1 = Rte_Call_DataServices_Data_Config_Machinetype_Read_WriteData(Call_DataServices_Data_Config_Machinetype_Read_WriteData_Data, DCM_INITIAL, &Call_DataServices_Data_Config_Machinetype_Read_WriteData_ErrorCode);
			Std_ReturnType fct_status2 = Rte_Call_DataServices_Data_Config_MachineNumber_Read_WriteData(Call_DataServices_Data_Config_MachineNumber_Read_WriteData_Data, DCM_INITIAL, &Call_DataServices_Data_Config_MachineNumber_Read_WriteData_ErrorCode);

			if (fct_status1 == RTE_E_OK && fct_status1 == RTE_E_OK){
				trigs.MnTrig = false;
			}
		}
	}

	if (0 == (compteurStep50ms %PERIOD_MSGID50ms_5s)){
		SG_CmaTis data;
		data.ConfigMachineNumber = ident0.mn;
		data.ConfigMachineType = ident0.mt;
		Rte_Write_PpOutVbmIdCANmsg_DeEcuTis(&data);
	}


  /*************************************************
  * Direct Function Accesses
  *************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

#define CtApTis_STOP_SEC_CODE
#include "CtApTis_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

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

   MD_Rte_TestCode:
     Reason:     This justification is used as summary justification for all deviations caused by wrong analysis tool results.
                 The used analysis tool QAC 9.0 sometimes creates wrong messages. Those deviations are no issues in the RTE code.
     Risk:       No functional risk.
     Prevention: Not required.

*/
