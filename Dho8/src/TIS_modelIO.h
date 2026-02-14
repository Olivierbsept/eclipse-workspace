

#include "rtwtypes.h"

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
 	uint8_T setMachineTypeStorage(uint32_T value);
	uint8_T setMachineNumberStorage(uint32_T value);
	uint8_T setMachineHourStorage(uint16_T value);
	
//From jVbmcBrc_SystemStatus
	uint8_T getOverallEemState(void);

//To jPropA_Fum_Config
	void setMachineTypeStorage(uint16_T value);
	void setMachineNumberStorage(uint32_T value);
	void setTrig_jPropA_Fum_Config(uint8_T);
	uint8_T getTrigReset_jPropA_Fum_Config(void);

//To jPropA_Fum_TotalCounterHours
	void setMachineHourStorage(uint32_T value);
	void setTrig_jPropA_Fum_TotalCounterHours(uint8_T);
	uint8_T getTrigReset_jPropA_Fum_TotalCounterHours(void);	

//Declaration setFlagReset_Init
	void setFlagReset_Init(uint8_T value);  

//Version
	void setOutTisModuleVersion(uint8_T index, uint8_T value);
}