
#include "TIS_modelIO_Lim.h"

//From jPropA_Vbm_Config
uint16_T getMachineTypeVbm_Lim(void){
	uint16_T value;
 	value = rx_jPropA_VbConfigMachineType_b_Lim;
	return value;
};
uint32_T getMachineNumberVbm_Lim(void){
	uint32_T value;
 	value = rx_jPropA_VbConfigMachineNumber_b_Lim;
	return value;
};
uint8_T getFlag_jPropA_Vbm_Config_Lim(void){
	uint8_T value;
 	value = jPropA_Vbm_Config_ind_b_Lim;
	return value;	
};
void setFlagReset_jPropA_Vbm_Config_Lim(uint8_T value){
	jPropA_Vbm_Config_ind_b_Lim = value;
};  

//From jVhbcBrc_VehicleHours
uint32_T getMachineHourVbm_Lim(void){
	uint32_T value;
 	value = rx_jVhbcBrc_TotalVehicleHours_b_Lim;
	return value;
};
uint8_T getFlag_jVhbcBrc_VehicleHours_Lim(void){
	uint8_T value;
 	value = jVhbcBrc_VehicleHours_ind_b_Lim;
	return value;	
};
void setFlagReset_jVhbcBrc_VehicleHours_Lim(uint8_T value){
	jVhbcBrc_VehicleHours_ind_b_Lim = value;
};  

//From jPropA_Fum_Config
uint16_T getMachineTypeFum(void){
	uint16_T value;
 	value = rx_jPropA_FuConfigMachineType_b_Lim;
	return value;
};
uint32_T getMachineNumberFum(void){
	uint32_T value;
 	value = rx_jPropA_FuConfigMachineNumber_b_Lim;
	return value;
};
uint8_T getFlag_jPropA_Fum_Config(void){
	uint8_T value;
 	value = jPropA_Fum_Config_ind_b;
	return value;	
};
void setFlagReset_jPropA_Fum_Config(uint8_T value){
	jPropA_Fum_Config_ind_b= value;
};  
	
//From jPropA_Fum_TotalCounterHours
uint32_T getMachineHourFum(void){
	uint32_T value;
 	value = rx_jPropA_FuTotalVehicleHours_b;
	return value;
};
uint8_T getFlag_jPropA_Fum_TotalCounterHours(void){
	uint8_T value;
 	value = jPropA_FuTotalCounterHours_ind_b;
	return value;	
};
void setFlagReset_jPropA_Fum_TotalCounterHours(uint8_T value){
	jPropA_FuTotalCounterHours_ind_b = value;
}; 
	
//From & To Storage
uint16_T getMachineTypeStorage_Lim(void){
	uint16_T value;
	value = MachineType_Lim;
	return value;
};
uint32_T getMachineNumberStorage_Lim(void){
	uint32_T value;
	value = MachineNumber_Lim;
	return value;
};
uint32_T getMachineHourStorage_Lim(void){
	uint32_T value;
	value = MachineHour_Lim;
	return value;
};
uint8_T setMachineTypeStorage_lim(uint16_T value){
	MachineType_Lim=value;
	return 0;
};
uint8_T setMachineNumberStorage_Lim(uint32_T value){
	MachineNumber_Lim=value;
	return 0;
};
uint8_T setMachineHourStorage_Lim(uint32_T value){
	MachineHour_Lim=value;
	return 0;
};
	
//From jVbmcBrc_SystemStatus
uint8_T getOverallEemState_Lim(void){
	uint8_T value;
 	value = rx_jVbmcBrcSOverallEemState_b_Lim;
	return value;
};

//To jPropA_Lim_Config
void setMachineTypeLim(uint16_T value){
	tx_jPropA_LiConfigMachineType_b = value;
};
void setMachineNumberLim(uint32_T value){
	tx_jPropA_LiConfigMachineNumber_b = value;
};
void setTrig_jPropA_Lim_Config(uint8_T value){
	jPropA_Lim_Config_tx_b = value;
};
uint8_T getTrigReset_jPropA_Lim_Config(void){
	uint8_T value;
 	value = jPropA_Lim_Config_tx_b;
	return value;	
};

//To jPropA_Fum_TotalCounterHours
void setMachineHourLim(uint32_T value){
	tx_jPropA_LiTotalVehicleHours_b = value;
};
void setTrig_jPropA_Lim_TotalCounterHours(uint8_T value){
	jPropA_Lim_TotalCounterHours_tx_b = value;
};
uint8_T getTrigReset_jPropA_Lim_TotalCounterHours(void){
	uint8_T value;
 	value = jPropA_Lim_TotalCounterHours_tx_b;
	return value;	
};	

//Declaration setFlagReset_Init
//void setFlagReset_Init(uint8_T value)){

//};

	

