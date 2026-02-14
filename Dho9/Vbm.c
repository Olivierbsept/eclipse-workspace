
#include "Vbm.h"
#include <inttypes.h>
#include <stdio.h>
uint8_t data[8];

void node_receive_Vbm(CAN_Message msg) {
    printf("  [Node] Received message ID: %03X, Data:", msg.id);
    for (int i = 0; i < msg.dlc; i++) {
        printf(" %02X", msg.data[i]);
    }
    printf("\n");
    if (msg.id == IdFumConfig){
    	idents.Ident1.mn=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + msg.data[3];
    	idents.Ident1.mt=(msg.data[4]<<8) + msg.data[5];
    	trigs.RxId1Trig=true;
    }
    if (msg.id == IdFumHour){
    	idents.Ident1.mh=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + + msg.data[3];
        trigs.Rx1Trig=true;
    }
    if (msg.id == IdLimConfig){
    	idents.Ident2.mn=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + msg.data[3];
    	idents.Ident2.mt=(msg.data[4]<<8) + msg.data[5];
    }
    if (msg.id == IdLimHour){
    	idents.Ident2.mh=(msg.data[0]<<24) + (msg.data[1]<<16) + (msg.data[2]<<8) + + msg.data[3];
        trigs.Rx2Trig=true;
    }
}

void node_send_Vbm(CAN_Bus *bus, uint32_t id, unsigned char *data, unsigned char len) {
    CAN_Message msg;
    msg.id = id;
    msg.dlc = len;
    memcpy(msg.data, data, len);
    can_bus_send_Vbm(bus, msg);
}
void VbmSetBus(CAN_Bus *pbus){
	pcan_bus=pbus;
}

// === Init === //
void VbmInit(){
	ident0.mn=10;
	ident0.mt=11;
	ident0.mh= 1000;
	VbmCounter=ident0.mh;

	idents.Ident1.mh=0xFFFFFFFF;
	idents.Ident1.mt=0xFFFF;
	idents.Ident1.mh=0xFFFFFFFF;

	idents.Ident2.mh=0xFFFFFFFF;
	idents.Ident2.mt=0xFFFF;
	idents.Ident2.mh=0xFFFFFFFF;

	phases.SyncConfigPhase=true; //en GeneratorOn
	phases.SyncDiagPhase=false; //en ReadyToStartEngine

	trigs.DiagTrig=true;
	trigs.TxTrig=false;

	configs.DiagTrigCfg=true;//force cfg après paramétrage
	configs.ParamCheckCfg=false;// accepte cfg si condition ok

	InitDho_Vbm(configs);
}

// === Fonction principale appelée toutes les 10 ms ===
void Vbm_step50ms() {
	compteurStep50ms++;
    if (compteurStep50ms % PERIOD_COUNT50ms_1s == 0){
    	VbmCounter++;
    	ident0.mh=VbmCounter;
    }

    if (phases.SyncConfigPhase){
        Call50msDho_Vbm(&trigs,&ident0,idents);
        if (trigs.TxTrig){
    		data[0]=ident0.mh<<24;
    		data[1]=ident0.mh<<16;
    		data[2]=ident0.mh<<8;
    		data[3]=ident0.mh;
    		data[4]=0xFF;
    		data[5]=0xFF;
    		data[6]=0xFF;
    		data[7]=0xFF;
    		node_send_Vbm(pcan_bus,IdVbmHour,data, 8);
        	trigs.TxTrig = false;
        }
    }
    else if (phases.SyncDiagPhase){
        Call50msDho_Vbm_Diag(&trigs,&ident0,idents);
        if (trigs.TxTrig){
    		data[0]=ident0.mh<<24;
    		data[1]=ident0.mh<<16;
    		data[2]=ident0.mh<<8;
    		data[3]=ident0.mh;
    		data[4]=0xFF;
    		data[5]=0xFF;
    		data[6]=0xFF;
    		data[7]=0xFF;
    		node_send_Vbm(pcan_bus,IdVbmHour,data, 8);
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
		node_send_Vbm(pcan_bus,IdVbmHour,data, 8);
    }
	VbmCounter=ident0.mh;
	if (0 == (compteurStep50ms %PERIOD_STORE50ms_5s)){
		Store(filename_Vbm,ident0.mn, ident0.mt, ident0.mh);
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
		node_send_Vbm(pcan_bus, IdVbmConfig,data, 8);
	}
}

