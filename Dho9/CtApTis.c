#include "rtwtypes.h"
#include "CtComEemEnum.h"
#include "DhoCommun.h"
#include "Autosar.h"
#include "Rte_CtApTis.h"

SG_EemStates EemStates;
boolean MachineTimeReducedOnce;

#include "string.h"
#include "CtApTisModuleVersion.h"

#define CtApTis_START_SEC_CODE
#include "CtApTis_MemMap.h"

FUNC(Std_ReturnType, CtApTis_CODE) MachineId_ConditionCheckRead(Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) ErrorCode)
 {
	if (ErrorCode != NULL){
		*ErrorCode = DCM_E_POSITIVERESPONSE;
		return RTE_E_OK;
	}
	else{
		return RTE_E_DataServices_Data_DHO_MI_Read_E_NOT_OK;
	}

}

/*FUNC(Std_ReturnType, CtApTis_CODE) MachineId_Read(Dcm_OpStatusType OpStatus, P2VAR(uint8, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) Data)
{
	Std_ReturnType fct_status;
	SG_CmaTis Read_PpInCmaTis_DeCmaTis;
	sTotalCounterHours Read_PpInOpHoursCANmsg_TotalCounterHours;
	uint16 MachineType		= 0xFFFF;
	uint32 MachineNumber	= 0XFFFFFFFF;
	uint32 MachineTime		= 0XFFFFFFFF;

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
}*/


/*FUNC(Std_ReturnType, CtApTis_CODE) MachineId_Write(P2CONST(uint8, AUTOMATIC, RTE_CTAPTIS_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) ErrorCode)
{

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

}*/

/*FUNC(void, CtApTis_CODE) RCtApTis_Init(void)
{
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
}*/
/*
FUNC(void, CtApTis_CODE) RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents activationVector)
{

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
} */
/*
FUNC(void, CtApTis_CODE) RCtApTis_Step50ms(void)
{
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
}

#define CtApTis_STOP_SEC_CODE
#include "CtApTis_MemMap.h"
*/
