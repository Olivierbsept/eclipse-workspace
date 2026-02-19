/*
 * Vbm2.c
 *
 *  Created on: 27 oct. 2025
 *      Author: BESSETT
 */
#include "Vbm.h"
#include "Rte_CtApTis.h"

static SG_CmaTis CmaTis;
static uint32 PreviousHour;
static boolean StartRecvOpHours;
static char* filename_Vbm1 = "data.xml";
static char* filename_dtc = "dtc.xml";
static char* filename_nvm = "nvm.xml";

extern void ReceiveVbmMsg(uint32_T mh);
extern void VbmToLimMsg2(uint32_T mh);
extern Phases phases;
extern uint8 ecuname;
extern uint32 mnl, mhl;
extern uint16 mtl;
extern uint32 mnf, mhf;
extern uint16 mtf;
extern uint32 mnv, mhv;
extern uint16 mtv;
extern uint32 mnbu, mhbu;
extern uint16 mtbu;

void Rte_Enter_EA_RhoBackup(void){

}
void Rte_Exit_EA_RhoBackup(void){

}

void Rte_Call_CTAPDTC_SetDtc(uint16 dtc){
	 Store_dtc(filename_dtc, dtc, 1);
}
void Rte_Call_CTAPDTC_ClrDtc(uint16 dtc){
	 Store_dtc(filename_dtc, dtc, 0);
}

Std_ReturnType Rte_Read_CtApTis_PpInCmaTis_DeCmaTis(SG_CmaTis *data){
	*data = CmaTis;
	return E_OK;
}

Std_ReturnType Rte_Read_PpInOpHoursCANmsg_TotalCounterHours(sTotalCounterHours *data){
	data->TotalCountEngine1OpHours = mhv;
	return E_OK;
}
Std_ReturnType Rte_Call_DataServices_Data_Config_MachineNumber_Read_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode){
	mnv = (Data[0]<<24)+(Data[1]<<16)+(Data[2]<<8)+Data[3];;
	return E_OK;
}
Std_ReturnType Rte_Call_DataServices_Data_Config_Machinetype_Read_WriteData(const uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode){
	mtv = (Data[0]<<8)+Data[1];
	return E_OK;
}
Std_ReturnType Rte_Call_PpMachineCounter_SetMachineCounter(uint32 set_MachineCounter){
	mhv= set_MachineCounter;
	Store(filename_Vbm1,mnv, mtv, mhv);
	return E_OK;
}
Std_ReturnType Rte_Write_PpOutTisModuleVersion_DeModuleVersion(const SG_ModuleVersion *data){
	return E_OK;
}
void Rte_IrvWrite_RCtApTis_Init_Irv_PreviousHour(uint32 data){
	PreviousHour=data;
}
void Rte_IrvWrite_RCtApTis_Init_Irv_StartRecvOpHours(boolean data){
	StartRecvOpHours=data;
}

Std_ReturnType Rte_Read_PpInCmaTis_DeCmaTis(SG_CmaTis *data){
	data->ConfigMachineNumber=mnv;
	data->ConfigMachineType=mtv;
	return E_OK;
}
Std_ReturnType Rte_Read_PpInEemStates_DeValues(SG_EemStates *data){
	if (phases.SyncConfigPhase==true){
		data->OverallEemState=TIS_EemState_GeneratorOn;
	}
	else if (phases.SyncDiagPhase == true){
		data->OverallEemState=TIS_EemState_ReadyToStartEngine;
	}
	return E_OK;
}
Std_ReturnType Rte_Read_PpInFumHourTis_DeOperatingHours(SG_HourCan *data){
	data->HourReceivedFromCan=mhf;
	return E_OK;
}
Std_ReturnType Rte_Read_PpInFumIdTis_DeEcuTis(SG_CmaTis *data){
	data->ConfigMachineNumber=mnf;
	data->ConfigMachineType=mtf;
	return E_OK;
}
Std_ReturnType Rte_Read_PpInLimHourTis_DeOperatingHours(SG_HourCan *data){
	data->HourReceivedFromCan=mhl;
	return E_OK;
}
Std_ReturnType Rte_Read_PpInLimIdTis_DeEcuTis(SG_CmaTis *data){
	data->ConfigMachineNumber=mnl;
	data->ConfigMachineType=mtl;
	return E_OK;
}

Std_ReturnType Rte_Write_PpOutStdHours_DeStdHours(const SG_Hours *data){
	return E_OK;
}
Std_ReturnType Rte_Write_PpOutTisOpHours_DeOpHoursInternal(uint32 data){
	return E_OK;
}
Std_ReturnType Rte_Write_PpOutTisOpHoursClaasCANmsg_TotalVehicleHours(const sTotalVehicleHours *data){
	return E_OK;
}
Std_ReturnType Rte_Write_PpOutTisOpHoursHydCANmsg_TotalVehicleHours(const sTotalVehicleHours *data){
	return E_OK;
}
Std_ReturnType Rte_Write_PpOutTisOpHoursJ1939CANmsg_TotalVehicleHours(const sTotalVehicleHours *data){
	ReceiveVbmMsg(mhv);//VbmToFumMsg(ident0);
	VbmToLimMsg2(mhv);
	return E_OK;
}

uint32 Rte_IrvRead_RCtApTis_RxEvents_Irv_PreviousHour(void){
	return PreviousHour;
}
boolean Rte_IrvRead_RCtApTis_RxEvents_Irv_StartRecvOpHours(void){
	return StartRecvOpHours;
}
void Rte_IrvWrite_RCtApTis_RxEvents_Irv_PreviousHour(uint32 data){
	PreviousHour=data;
}
void Rte_IrvWrite_RCtApTis_RxEvents_Irv_StartRecvOpHours(boolean data){
	StartRecvOpHours=data;
}
Std_ReturnType Rte_Call_PpMasterConfig_StartCanTransmission(void){
	return E_OK;
}
Std_ReturnType Rte_Call_PpMasterConfig_StartMachineCounter(void){
	return E_OK;
}
Std_ReturnType Rte_Call_PpMasterConfig_StopMachineCounter(void){
	return E_OK;
}
Std_ReturnType Rte_Write_PpOutVbmIdCANmsg_DeEcuTis(const SG_CmaTis *data){
	ReceiveVbmIdMsg(data->ConfigMachineNumber,data->ConfigMachineType);//VbmIdToFumMsg(ident0);
	VbmIdToLimMsg2(data->ConfigMachineNumber,data->ConfigMachineType);
	return E_OK;
}

Std_ReturnType Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_GetErrorStatus(NvM_RequestResultType *data){
	*data = NVM_REQ_OK;
	return E_OK;
}
Std_ReturnType Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_WriteBlock(unsigned char data[23]){
	mhbu = (data[0]<<24)+(data[1]<<16)+(data[2]<<8)+data[3];
	mtbu= (data[4]<<8)+ data[5];
	mnbu=(data[6]<<24)+(data[7]<<16)+(data[8]<<8)+data[9];
	ecuname=data[10];
	mtf= (data[11]<<8)+ data[12];
	mnf=(data[13]<<24)+(data[14]<<16)+(data[15]<<8)+data[16];
	mtl=(data[17]<<8)+ data[18];
	mnl=(data[19]<<24)+(data[20]<<16)+(data[21]<<8)+data[22];
    start_xml(filename_nvm);
	Store_nvm(filename_nvm,mhbu, mtbu, mnbu,ecuname,mtf,mnf,mtl,mnl);
	return E_OK;
}
Std_ReturnType Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_RestoreBlockDefaults(unsigned char Rte_CtApTis_PimRhoBackup[23]){
	return E_OK;
}
/*int i;
for (i = 0; i < 23; i++)
{
    printf("data[%d] = %d\n", i, data[i]);
}*/

//printf("Debug Vbm2c : Rte_Write_PpOutVbmIdCANmsg_DeEcuTis = %" PRId32 "\n", data->ConfigMachineNumber);
