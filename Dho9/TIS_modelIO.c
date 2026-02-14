
#include "TIS_modelIO.h"

//From jPropA_Vbm_Config
uint16_T getMachineTypeVbm(void){
	uint16_T value;
 	value = rx_jPropA_VbConfigMachineType_b;
	return value;
};
uint32_T getMachineNumberVbm(void){
	uint32_T value;
 	value = rx_jPropA_VbConfigMachineNumber_b;
	return value;
};
uint8_T getFlag_jPropA_Vbm_Config(void){
	uint8_T value;
 	value = jPropA_Vbm_Config_ind_b;
	return value;	
};
void setFlagReset_jPropA_Vbm_Config(uint8_T value){
	jPropA_Vbm_Config_ind_b = value;
};  

//From jVhbcBrc_VehicleHours
uint32_T getMachineHourVbm(void){
	uint32_T value;
 	value = rx_jVhbcBrc_TotalVehicleHours_b;
	return value;
};
uint8_T getFlag_jVhbcBrc_VehicleHours(void){
	uint8_T value;
 	value = jVhbcBrc_VehicleHours_ind_b;
	return value;	
};
void setFlagReset_jVhbcBrc_VehicleHours(uint8_T value){
	jVhbcBrc_VehicleHours_ind_b = value;
};  

//From jPropA_Lim_Config
uint16_T getMachineTypeLim(void){
	uint16_T value;
 	value = rx_jPropA_LiConfigMachineType_b;
	return value;
};
uint32_T getMachineNumberLim(void){
	uint32_T value;
 	value = rx_jPropA_LiConfigMachineNumber_b;
	return value;
};
uint8_T getFlag_jPropA_Lim_Config(void){
	uint8_T value;
 	value = jPropA_Lim_Config_ind_b;
	return value;	
};
void setFlagReset_jPropA_Lim_Config(uint8_T value){
	jPropA_Lim_Config_ind_b = value;
};  
	
//From jPropA_Lim_TotalCounterHours
uint32_T getMachineHourLim(void){
	uint32_T value;
 	value = rx_jPropA_LiTotalVehicleHours_b;
	return value;
};
uint8_T getFlag_jPropA_Lim_TotalCounterHours(void){
	uint8_T value;
 	value = jPropA_LiTotalCounterHours_ind_b;
	return value;	
};
void setFlagReset_jPropA_Lim_TotalCounterHours(uint8_T value){
	jPropA_LiTotalCounterHours_ind_b = value;
}; 
	
//From & To Storage
uint16_T getMachineTypeStorage(void){
	uint16_T value;
	value = MachineType;
	return value;
};
uint32_T getMachineNumberStorage(void){
	uint32_T value;
	value = MachineNumber;
	return value;
};
uint32_T getMachineHourStorage(void){
	uint32_T value;
	value = MachineHour;
	return value;
};
uint8_T setMachineTypeStorage(uint16_T value){
	MachineType=value;
	return 0;
};
uint8_T setMachineNumberStorage(uint32_T value){
	MachineNumber=value;
	return 0;
};
uint8_T setMachineHourStorage(uint32_T value){
	MachineHour=value;
	return 0;
};
	
//From jVbmcBrc_SystemStatus
uint8_T getOverallEemState(void){
	uint8_T value;
 	value = rx_jVbmcBrcSOverallEemState_b;
	return value;
};

//To jPropA_Fum_Config
void setMachineTypeFum(uint16_T value){
	tx_jPropA_FuConfigMachineType_b = value;
};
void setMachineNumberFum(uint32_T value){
	tx_jPropA_FuConfigMachineNumber_b = value;
};
void setTrig_jPropA_Fum_Config(uint8_T value){
	jPropA_Fum_Config_tx_b = value;
};
uint8_T getTrigReset_jPropA_Fum_Config(void){
	uint8_T value;
 	value = jPropA_Fum_Config_tx_b;
	return value;	
};

//To jPropA_Fum_TotalCounterHours
void setMachineHourFum(uint32_T value){
	tx_jPropA_FuTotalVehicleHours_b = value;
};
void setTrig_jPropA_Fum_TotalCounterHours(uint8_T value){
	jPropA_Fum_TotalCounterHours_tx_b = value;
};
uint8_T getTrigReset_jPropA_Fum_TotalCounterHours(void){
	uint8_T value;
 	value = jPropA_Fum_TotalCounterHours_tx_b;
	return value;	
};	

//Declaration setFlagReset_Init
//void setFlagReset_Init(uint8_T value)){

//};

	

