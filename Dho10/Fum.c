
#include "Fum.h"
#include "Eem.h"

uint16_T rx_jPropA_VbConfigMachineType_b = 0xFFFF;
uint32_T rx_jPropA_VbConfigMachineNumber_b = 0xFFFFFFFF;
uint8_T jPropA_Vbm_Config_ind_b=0;
uint32_T rx_jVhbcBrc_TotalVehicleHours_b = 0xFFFFFFFF;
uint8_T jVhbcBrc_VehicleHours_ind_b=0;
uint16_T rx_jPropA_LiConfigMachineType_b = 0xFFFF;
uint32_T rx_jPropA_LiConfigMachineNumber_b = 0xFFFFFFFF;
uint16_T MachineType= 0xFFFF;
uint32_T MachineNumber= 0xFFFFFFFF;
uint32_T MachineHour= 0xFFFFFFFF;
uint8_T MachineCountFlag = false;
uint8_T jPropA_Lim_Config_ind_b=0;
uint32_T rx_jPropA_LiTotalVehicleHours_b=0;
uint8_T jPropA_LiTotalCounterHours_ind_b=0;
uint8_T rx_jVbmcBrcSOverallEemState_b = EemState_GeneratorOn;
uint16_T tx_jPropA_FuConfigMachineType_b = 0xFFFF;
uint32_T tx_jPropA_FuConfigMachineNumber_b = 0xFFFFFFFF;
uint8_T jPropA_Fum_Config_tx_b = 0;
uint32_T tx_jPropA_FuTotalVehicleHours_b = 0xFFFFFFFF;
uint8_T jPropA_Fum_TotalCounterHours_tx_b = 0;

void ReceiveVbmMsg(uint32_T mh) {
	if (jVhbcBrc_VehicleHours_ind_b == false){
		rx_jVhbcBrc_TotalVehicleHours_b=mh;
		jVhbcBrc_VehicleHours_ind_b=true;
	}
}
void ReceiveLimMsg(uint32_T mh) {
	if (jPropA_LiTotalCounterHours_ind_b == false){
		rx_jPropA_LiTotalVehicleHours_b=mh;
		jPropA_LiTotalCounterHours_ind_b=true;
	}
}
void ReceiveVbmIdMsg(uint32_T mn, uint16_T mt) {
	if (jPropA_Vbm_Config_ind_b == false){
		rx_jPropA_VbConfigMachineType_b = mt;
		rx_jPropA_VbConfigMachineNumber_b = mn;
		jPropA_Vbm_Config_ind_b=true;
	}
}
void ReceiveLimIdMsg(uint32_T mn, uint16_T mt) {
	if (jPropA_Lim_Config_ind_b == false){
		rx_jPropA_LiConfigMachineType_b=mt;
		rx_jPropA_LiConfigMachineNumber_b=mn;
		jPropA_Lim_Config_ind_b=true;
	}
}

void FumInit(){
	MachineNumber=100;
	MachineType=101;
	MachineHour=10000;
	rx_jVbmcBrcSOverallEemState_b = EemState_GeneratorOn ;
	Tis_initialize();
}

// === Fonction principale appelée toutes les 10 ms ===
void Fum_step100ms() {
	compteurStep100ms++;
	if (MachineCountFlag){
	    if (compteurStep100ms % PERIOD_COUNT100ms_1s == 0){
	    	MachineHour++;
	    }
	}
	Tis_step_100ms();
	if (jPropA_Fum_Config_tx_b){
		sendFumIdToVbmMsg(tx_jPropA_FuConfigMachineNumber_b, tx_jPropA_FuConfigMachineType_b);
		sendFumIdToLimMsg(tx_jPropA_FuConfigMachineNumber_b, tx_jPropA_FuConfigMachineType_b);
		jPropA_Fum_Config_tx_b = false;
    	//printf("Debug Fum mt : %" PRId32 "\n", tx_jPropA_FuConfigMachineType_b);
	}
	if (jPropA_Fum_TotalCounterHours_tx_b){
		sendFumToVbmMsg(tx_jPropA_FuTotalVehicleHours_b);
		sendFumToLimMsg(tx_jPropA_FuTotalVehicleHours_b);
		jPropA_Fum_TotalCounterHours_tx_b=false;
    	//printf("Debug Fum mh : %" PRId32 "\n", tx_jPropA_FuTotalVehicleHours_b);
	}
	if (0 == (compteurStep100ms %PERIOD_STORE100ms_5s)){
		Store(filename_Fum,MachineNumber, MachineType, MachineHour);
	}
}
