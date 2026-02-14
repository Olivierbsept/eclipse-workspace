

#include "rtwtypes.h"
#include <stdint.h>

extern uint16_t rx_jPropA_VbConfigMachineType_b_Lim;
extern uint32_t rx_jPropA_VbConfigMachineNumber_b_Lim;
extern uint8_t jPropA_Vbm_Config_ind_b_Lim;
extern uint32_t rx_jVhbcBrc_TotalVehicleHours_b_Lim;
extern uint8_t jVhbcBrc_VehicleHours_ind_b_Lim;
extern uint16_t rx_jPropA_FuConfigMachineType_b_Lim;
extern uint32_t rx_jPropA_FuConfigMachineNumber_b_Lim;
extern uint16_t MachineType_Lim;
extern uint32_t MachineNumber_Lim;
extern uint32_t MachineHour_Lim;
extern uint8_T jPropA_Fum_Config_ind_b;
extern uint32_T rx_jPropA_FuTotalVehicleHours_b;
extern uint8_T jPropA_FuTotalCounterHours_ind_b;
extern uint8_T rx_jVbmcBrcSOverallEemState_b_Lim;
extern uint16_T tx_jPropA_LiConfigMachineType_b;
extern uint32_T tx_jPropA_LiConfigMachineNumber_b;
extern uint8_T jPropA_Lim_Config_tx_b;
extern uint32_T tx_jPropA_LiTotalVehicleHours_b;
extern uint8_T jPropA_Lim_TotalCounterHours_tx_b;

//From jPropA_Vbm_Config
	uint16_T getMachineTypeVbm_Lim(void);
	uint32_T getMachineNumberVbm_Lim(void);
	uint8_T getFlag_jPropA_Vbm_Config_Lim(void);
	void setFlagReset_jPropA_Vbm_Config_Lim(uint8_T value);

//From jVhbcBrc_VehicleHours
	uint32_T getMachineHourVbm_lim(void);
	uint8_T getFlag_jVhbcBrc_VehicleHours_Lim(void);
	void setFlagReset_jVhbcBrc_VehicleHours_Lim(uint8_T value);

//From jPropA_Fum_Config
	uint16_T getMachineTypeFum(void);
	uint32_T getMachineNumberFum(void);
	uint8_T getFlag_jPropA_Fum_Config(void);
	void setFlagReset_jPropA_Fum_Config(uint8_T value);
	
//From jPropA_Fum_TotalCounterHours
	uint32_T getMachineHourFum(void);
	uint8_T getFlag_jPropA_Fum_TotalCounterHours(void);
	void setFlagReset_jPropA_Fum_TotalCounterHours(uint8_T value);
	
//From & To Storage
	uint16_T getMachineTypeStorage_Lim(void);
	uint32_T getMachineNumberStorage_Lim(void);
	uint32_T getMachineHourStorage_lim(void);
 	uint8_T setMachineTypeStorage_lim(uint16_T value);
	uint8_T setMachineNumberStorage_Lim(uint32_T value);
	uint8_T setMachineHourStorage_lim(uint32_T value);
	
//From jVbmcBrc_SystemStatus
	uint8_T getOverallEemState_Lim(void);

//To jPropA_Lim_Config
	void setMachineTypeLim(uint16_T value);
	void setMachineNumberLim(uint32_T value);
	void setTrig_jPropA_Lim_Config(uint8_T);
	uint8_T getTrigReset_jPropA_Lim_Config(void);

//To jPropA_Lim_TotalCounterHours
	void setMachineHourLim(uint32_T value);
	void setTrig_jPropA_Lim_TotalCounterHours(uint8_T);
	uint8_T getTrigReset_jPropA_Lim_TotalCounterHours(void);

//Declaration setFlagReset_Init
	void setFlagReset_Init(uint8_T value);  

//Version
	void setOutTisModuleVersion(uint8_T index, uint8_T value);
