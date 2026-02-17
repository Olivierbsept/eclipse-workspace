

#include "rtwtypes.h"
#include <stdint.h>


//From jPropA_Vbm_Config
	uint16_T getMachineTypeEcu1(void);
	uint32_T getMachineNumberEcu1(void);
	uint8_T getFlag_Ecu1_Config(void);
	void setFlagReset_Ecu1_Config(uint8_T value);  

//From jVhbcBrc_VehicleHours
	uint32_T getMachineHourEcu1(void);
	uint8_T getFlag_Ecu1_VehicleHours(void);
	void setFlagReset_Ecu1_VehicleHours(uint8_T value);  

//From jPropA_Lim_Config
	uint16_T getMachineTypeEcu2(void);
	uint32_T getMachineNumberEcu2(void);
	uint8_T getFlag_Ecu2_Config(void);
	void setFlagReset_Ecu2_Config(uint8_T value);  
	
//From jPropA_Lim_TotalCounterHours
	uint32_T getMachineHourEcu2(void);
	uint8_T getFlag_Ecu2_TotalCounterHours(void);
	void setFlagReset_Ecu2_TotalCounterHours(uint8_T value);  
	
//From & To Storage
	uint16_T getMachineTypeStorage(void);
	uint32_T getMachineNumberStorage(void);
	uint32_T getMachineHourStorage(void);
 	uint8_T setMachineTypeStorage(uint16_T value);
	uint8_T setMachineNumberStorage(uint32_T value);
	uint8_T setMachineHourStorage(uint32_T value);
	void startMachineHourCount(void);
	void stopMachineHourCount(void);

//Configuration
	uint8_T isConfigRequester(void);
	uint8_T isConfigController(void);
	uint32_T getResetMn();
	uint16_T getResetMt();
	
//From jVbmcBrc_SystemStatus
	uint8_T getOverallEemState(void);

//To jPropA_Fum_Config
	void setMachineTypeEcu0(uint16_T value);
	void setMachineNumberEcu0(uint32_T value);
	void setTrig_Ecu0_Config(uint8_T);
	uint8_T getTrigReset_Ecu0_Config(void);

//To jPropA_Fum_TotalCounterHours
	void setMachineHourEcu0(uint32_T value);
	void setTrig_Ecu0_TotalCounterHours(uint8_T);
	uint8_T getTrigReset_Ecu0_TotalCounterHours(void);	

//Declaration setFlagReset_Init
	void setFlagReset_Init(uint8_T value);  

//Version
	void setOutTisModuleVersion(uint8_T index, uint8_T value);
