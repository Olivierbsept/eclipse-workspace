
#include "TIS_modelIO.h"

extern uint16_T rx_jPropA_VbConfigMachineType_b;
extern uint32_T rx_jPropA_VbConfigMachineNumber_b;
extern uint8_T jPropA_Vbm_Config_ind_b;
extern uint32_T rx_jVhbcBrc_TotalVehicleHours_b;
extern uint8_T jVhbcBrc_VehicleHours_ind_b;
extern uint16_T rx_jPropA_LiConfigMachineType_b;
extern uint32_T rx_jPropA_LiConfigMachineNumber_b;
extern uint16_T MachineType;
extern uint32_T MachineNumber;
extern uint32_T MachineHour;
extern uint8_T MachineCountFlag;
extern uint8_T jPropA_Lim_Config_ind_b;
extern uint32_T rx_jPropA_LiTotalVehicleHours_b;
extern uint8_T jPropA_LiTotalCounterHours_ind_b;
extern uint8_T rx_jVbmcBrcSOverallEemState_b;
extern uint16_T tx_jPropA_FuConfigMachineType_b;
extern uint32_T tx_jPropA_FuConfigMachineNumber_b;
extern uint8_T jPropA_Fum_Config_tx_b;
extern uint32_T tx_jPropA_FuTotalVehicleHours_b;
extern uint8_T jPropA_Fum_TotalCounterHours_tx_b;

//From jPropA_Vbm_Config
uint16_T getMachineTypeEcu1(void){
	uint16_T value;
 	value = rx_jPropA_VbConfigMachineType_b;
	return value;
};
uint32_T getMachineNumberEcu1(void){
	uint32_T value;
 	value = rx_jPropA_VbConfigMachineNumber_b;
	return value;
};
uint8_T getFlag_Ecu1_Config(void){
	uint8_T value;
 	value = jPropA_Vbm_Config_ind_b;
	return value;	
};
void setFlagReset_Ecu1_Config(uint8_T value){
	jPropA_Vbm_Config_ind_b = value;
};  

//From jVhbcBrc_VehicleHours
uint32_T getMachineHourEcu1(void){
	uint32_T value;
 	value = rx_jVhbcBrc_TotalVehicleHours_b;
	return value;
};
uint8_T getFlag_Ecu1_VehicleHours(void){
	uint8_T value;
 	value = jVhbcBrc_VehicleHours_ind_b;
	return value;	
};
void setFlagReset_Ecu1_VehicleHours(uint8_T value){
	jVhbcBrc_VehicleHours_ind_b = value;
};  

//From jPropA_Lim_Config
uint16_T getMachineTypeEcu2(void){
	uint16_T value;
 	value = rx_jPropA_LiConfigMachineType_b;
	return value;
};
uint32_T getMachineNumberEcu2(void){
	uint32_T value;
 	value = rx_jPropA_LiConfigMachineNumber_b;
	return value;
};
uint8_T getFlag_Ecu2_Config(void){
	uint8_T value;
 	value = jPropA_Lim_Config_ind_b;
	return value;	
};
void setFlagReset_Ecu2_Config(uint8_T value){
	jPropA_Lim_Config_ind_b = value;
};  
	
//From jPropA_Lim_TotalCounterHours
uint32_T getMachineHourEcu2(void){
	uint32_T value;
 	value = rx_jPropA_LiTotalVehicleHours_b;
	return value;
};
uint8_T getFlag_Ecu2_TotalCounterHours(void){
	uint8_T value;
 	value = jPropA_LiTotalCounterHours_ind_b;
	return value;	
};
void setFlagReset_Ecu2_TotalCounterHours(uint8_T value){
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
void startMachineHourCount(void){
	MachineCountFlag=1;
};
void stopMachineHourCount(void){
	MachineCountFlag=0;
};

uint8_T isConfigRequester(){
	return 0;
}
uint8_T isConfigController(void){
	return 1;
}

//From jVbmcBrc_SystemStatus
uint8_T getOverallEemState(void){
	uint8_T value;
 	value = rx_jVbmcBrcSOverallEemState_b;
	return value;
};

//To jPropA_Fum_Config
void setMachineTypeEcu0(uint16_T value){
	tx_jPropA_FuConfigMachineType_b = value;
};
void setMachineNumberEcu0(uint32_T value){
	tx_jPropA_FuConfigMachineNumber_b = value;
};
void setTrig_Ecu0_Config(uint8_T value){
	jPropA_Fum_Config_tx_b = value;
};
uint8_T getTrigReset_Ecu0_Config(void){
	uint8_T value;
 	value = jPropA_Fum_Config_tx_b;
	return value;	
};

//To jPropA_Fum_TotalCounterHours
void setMachineHourEcu0(uint32_T value){
	tx_jPropA_FuTotalVehicleHours_b = value;
};
void setTrig_Ecu0_TotalCounterHours(uint8_T value){
	jPropA_Fum_TotalCounterHours_tx_b = value;
};
uint8_T getTrigReset_Ecu0_TotalCounterHours(void){
	uint8_T value;
 	value = jPropA_Fum_TotalCounterHours_tx_b;
	return value;	
};

//Declaration setFlagReset_Init
//void setFlagReset_Init(uint8_T value)){

//};

	

