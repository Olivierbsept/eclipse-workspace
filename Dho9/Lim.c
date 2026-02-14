
#include "Lim.h"
#include <inttypes.h>
#include <stdio.h>

uint16_T rx_jPropA_VbConfigMachineType_b_Lim = 0xFFFF;
uint32_T rx_jPropA_VbConfigMachineNumber_b_Lim = 0xFFFFFFFF;
uint8_T jPropA_Vbm_Config_ind_b_Lim=0;
uint32_T rx_jVhbcBrc_TotalVehicleHours_b_Lim = 0xFFFFFFFF;
uint8_T jVhbcBrc_VehicleHours_ind_b_Lim=0;
uint16_T rx_jPropA_FuConfigMachineType_b_Lim = 0xFFFF;
uint32_T rx_jPropA_FuConfigMachineNumber_b_Lim = 0xFFFFFFFF;
uint16_T MachineType_Lim= 0xFFFF;
uint32_T MachineNumber_Lim= 0xFFFFFFFF;
uint32_T MachineHour_Lim= 0xFFFFFFFF;
uint8_T jPropA_Fum_Config_ind_b=0;
uint32_T rx_jPropA_FuTotalVehicleHours_b=0;
uint8_T jPropA_FuTotalCounterHours_ind_b=0;
uint8_T rx_jVbmcBrcSOverallEemState_b_Lim = 0;
uint16_T tx_jPropA_LiConfigMachineType_b = 0xFFFF;
uint32_T tx_jPropA_LiConfigMachineNumber_b = 0xFFFFFFFF;
uint8_T jPropA_Lim_Config_tx_b = 0;
uint32_T tx_jPropA_LiTotalVehicleHours_b = 0xFFFFFFFF;
uint8_T jPropA_Lim_TotalCounterHours_tx_b = 0;
uint8_T data[8];

void node_receive_Lim(CAN_Message msg) {
    printf("  [Node] Received message ID: %03X, Data:", msg.id);
    for (int i = 0; i < msg.dlc; i++) {
        printf(" %02X", msg.data[i]);
    }
    printf("\n");
    /*if (msg.id == IdFumConfig){
    	idents.Ident2.mn=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + msg.data[3];
    	idents.Ident2.mt=(msg.data[4]<<8) + msg.data[5];
    }
    if (msg.id == IdFumHour){
    	idents.Ident2.mh=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + + msg.data[3];
        trigs.Rx2Trig=true;
    }
    if (msg.id == IdVbmConfig){
    	idents.Ident1.mn=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + msg.data[3];
    	idents.Ident1.mt=(msg.data[4]<<8) + msg.data[5];
    	trigs.RxId1Trig=true;
    }
    if (msg.id == IdVbmHour){
    	idents.Ident1.mh=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + + msg.data[3];
        trigs.Rx1Trig=true;
    }*/
    if (msg.id == IdFumConfig){
    	if (jPropA_Fum_Config_ind_b == false){
			rx_jPropA_FuConfigMachineType_b_Lim=(msg.data[4]<<8) + msg.data[5];
			rx_jPropA_FuConfigMachineNumber_b_Lim=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + msg.data[3];
			jPropA_Fum_Config_ind_b=true;
    	}
    }
    if (msg.id == IdLimHour){
    	if (jPropA_FuTotalCounterHours_ind_b == false){
    		rx_jPropA_FuTotalVehicleHours_b=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + msg.data[3];
    		jPropA_FuTotalCounterHours_ind_b=true;
    	}
    }

    if (msg.id == IdVbmConfig){
    	if (jPropA_Vbm_Config_ind_b_Lim == false){
    		rx_jPropA_VbConfigMachineType_b_Lim = (msg.data[4]<<8) + msg.data[5];
    		rx_jPropA_VbConfigMachineNumber_b_Lim = (msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + msg.data[3];
    		jPropA_Vbm_Config_ind_b_Lim=true;
    	}
    }
    if (msg.id == IdVbmHour){
    	if (jVhbcBrc_VehicleHours_ind_b_Lim == false){
    		rx_jVhbcBrc_TotalVehicleHours_b_Lim=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + msg.data[3];
    		jVhbcBrc_VehicleHours_ind_b_Lim=true;
    	}
    }
}

void node_send_Lim(CAN_Bus *bus, uint32_t id, unsigned char *data, unsigned char len) {
    CAN_Message msg;
    msg.id = id;
    msg.dlc = len;
    memcpy(msg.data, data, len);
    can_bus_send_Lim(bus, msg);
}

void LimSetBus(CAN_Bus *pbus){
	pcan_bus=pbus;
}

// === Init === //
void LimInit(){
	ident0.mn=100;
	ident0.mt=101;
	ident0.mh= 100;
	LimCounter=ident0.mh;

	idents.Ident1.mh=0xFFFFFFFF;
	idents.Ident1.mt=0xFFFF;
	idents.Ident1.mh=0xFFFFFFFF;

	idents.Ident2.mh=0xFFFFFFFF;
	idents.Ident2.mt=0xFFFF;
	idents.Ident2.mh=0xFFFFFFFF;

	phases.SyncConfigPhase=true;  //en GeneratorOn
	phases.SyncDiagPhase=false; //en ReadyToStartEngine

	trigs.DiagTrig=false;
	trigs.TxTrig=false;

	configs.DiagTrigCfg=false; //force cfg après paramétrage
	configs.ParamCheckCfg=false; //accepte cfg si condition ok

	InitDho_Lim(configs);
}

// === Fonction principale appelée toutes les 10 ms ===
void Lim_step50ms() {
	compteurStep50ms++;
    if (compteurStep50ms % PERIOD_COUNT50ms_1s == 0){
    	LimCounter++;
    	ident0.mh=LimCounter;
    }
    if (phases.SyncConfigPhase){
        Call50msDho_Lim(&trigs,&ident0,idents);
        if (trigs.TxTrig){
    		data[0]=ident0.mh<<24;
    		data[1]=ident0.mh<<16;
    		data[2]=ident0.mh<<8;
    		data[3]=ident0.mh;
    		data[4]=0xFF;
    		data[5]=0xFF;
    		data[6]=0xFF;
    		data[7]=0xFF;
    		node_send_Lim(pcan_bus,IdLimHour,data, 8);
        	trigs.TxTrig = false;
        }
    }
    else if (phases.SyncDiagPhase){
        Call50msDho_Lim_Diag(&trigs,&ident0,idents);
        if (trigs.TxTrig){
    		data[0]=ident0.mh<<24;
    		data[1]=ident0.mh<<16;
    		data[2]=ident0.mh<<8;
    		data[3]=ident0.mh;
    		data[4]=0xFF;
    		data[5]=0xFF;
    		data[6]=0xFF;
    		data[7]=0xFF;
    		node_send_Lim(pcan_bus,IdLimHour,data, 8);
        	trigs.TxTrig = false;
        }
    }
    else if (0 == (compteurStep50ms %PERIOD_MSGID50ms_3s)){
		data[0]=ident0.mh<<24;
		data[1]=ident0.mh<<16;
		data[2]=ident0.mh<<8;
		data[3]=ident0.mh;
		data[4]=0xFF;
		data[5]=0xFF;
		data[6]=0xFF;
		data[7]=0xFF;
		node_send_Lim(pcan_bus,IdLimHour,data, 8);
    }

	LimCounter=ident0.mh;

	if (0 == (compteurStep50ms %PERIOD_STORE50ms_5s)){
		Store(filename_Lim,ident0.mn, ident0.mt, ident0.mh);
	}

	if (0 == (compteurStep50ms %PERIOD_MSGID50ms_5s)){
		data[0]=ident0.mn<<24;
		data[1]=ident0.mn<<16;
		data[2]=ident0.mn<<8;
		data[3]=ident0.mn;
		data[4]=ident0.mt<<8;
		data[5]=ident0.mt;
		data[6]=0xFF;
		data[7]=0xFF;
		node_send_Lim(pcan_bus, IdLimConfig,data, 8);
	}
}

