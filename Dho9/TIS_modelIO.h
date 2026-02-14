

#include "rtwtypes.h"
#include <stdint.h>

extern uint16_t rx_jPropA_VbConfigMachineType_b;
extern uint32_t rx_jPropA_VbConfigMachineNumber_b;
extern uint8_t jPropA_Vbm_Config_ind_b;
extern uint32_t rx_jVhbcBrc_TotalVehicleHours_b;
extern uint8_t jVhbcBrc_VehicleHours_ind_b;
extern uint16_t rx_jPropA_LiConfigMachineType_b;
extern uint32_t rx_jPropA_LiConfigMachineNumber_b;
extern uint16_t MachineType;
extern uint32_t MachineNumber;
extern uint32_t MachineHour;
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
	uint16_T getMachineTypeVbm(void);
	uint32_T getMachineNumberVbm(void);
	uint8_T getFlag_jPropA_Vbm_Config(void);
	void setFlagReset_jPropA_Vbm_Config(uint8_T value);  

//From jVhbcBrc_VehicleHours
	uint32_T getMachineHourVbm(void);
	uint8_T getFlag_jVhbcBrc_VehicleHours(void);
	void setFlagReset_jVhbcBrc_VehicleHours(uint8_T value);  

//From jPropA_Lim_Config
	uint16_T getMachineTypeLim(void);
	uint32_T getMachineNumberLim(void);
	uint8_T getFlag_jPropA_Lim_Config(void);
	void setFlagReset_jPropA_Lim_Config(uint8_T value);  
	
//From jPropA_Lim_TotalCounterHours
	uint32_T getMachineHourLim(void);
	uint8_T getFlag_jPropA_Lim_TotalCounterHours(void);
	void setFlagReset_jPropA_Lim_TotalCounterHours(uint8_T value);  
	
//From & To Storage
	uint16_T getMachineTypeStorage(void);
	uint32_T getMachineNumberStorage(void);
	uint32_T getMachineHourStorage(void);
 	uint8_T setMachineTypeStorage(uint16_T value);
	uint8_T setMachineNumberStorage(uint32_T value);
	uint8_T setMachineHourStorage(uint32_T value);
	
//From jVbmcBrc_SystemStatus
	uint8_T getOverallEemState(void);

//To jPropA_Fum_Config
	void setMachineTypeFum(uint16_T value);
	void setMachineNumberFum(uint32_T value);
	void setTrig_jPropA_Fum_Config(uint8_T);
	uint8_T getTrigReset_jPropA_Fum_Config(void);

//To jPropA_Fum_TotalCounterHours
	void setMachineHourFum(uint32_T value);
	void setTrig_jPropA_Fum_TotalCounterHours(uint8_T);
	uint8_T getTrigReset_jPropA_Fum_TotalCounterHours(void);	

//Declaration setFlagReset_Init
	void setFlagReset_Init(uint8_T value);  

//Version
	void setOutTisModuleVersion(uint8_T index, uint8_T value);
