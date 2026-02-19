
#include "Lim.h"

// === Interfaces externes vers Vbm ===
void VbmToLimMsg(DhoIdent ident) {
	idents.Ident1.mh=ident.mh;
    trigs.Rx1Trig=true;
}
void VbmIdToLimMsg(DhoIdent ident) {
	idents.Ident1.mn=ident.mn;
	idents.Ident1.mt=ident.mt;
	trigs.RxId1Trig=true;
}

void sendFumToLimMsg(uint32_T mh){
	idents.Ident2.mh=mh;
    trigs.Rx2Trig=true;
}
void sendFumIdToLimMsg(uint32_T mn, uint16_T mt){
	idents.Ident2.mn=mn;
	idents.Ident2.mt=mt;
	printf("Debug Lim mn : %" PRId32 "\n", mn);
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

	InitDho_Ecu2(configs);
}

// === Fonction principale appelée toutes les 100 ms ===
void Lim_step100ms() {
	compteurStep100ms++;
    if (compteurStep100ms % PERIOD_COUNT100ms_1s == 0){
    	LimCounter++;
    	ident0.mh=LimCounter;
    }
    if (phases.SyncConfigPhase){
        DhoCall_100ms_Ecu2(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	LimToVbmMsg(ident0);
        	ReceiveLimMsg(ident0.mh);//LimToFumMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (phases.SyncDiagPhase){
        DhoCall_100ms_Diag_Ecu2(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	LimToVbmMsg(ident0);
        	ReceiveLimMsg(ident0.mh);//LimToFumMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (0 == (compteurStep100ms %PERIOD_MSGID100ms_3s)){
    	LimToVbmMsg(ident0);
    	ReceiveLimMsg(ident0.mh);//LimToFumMsg(ident0);
    }

	LimCounter=ident0.mh;

	if (0 == (compteurStep100ms %PERIOD_STORE100ms_5s)){
		Store(filename_Lim,ident0.mn, ident0.mt, ident0.mh);
	}

	if (0 == (compteurStep100ms %PERIOD_MSGID100ms_5s)){
		LimIdToVbmMsg(ident0);
		ReceiveLimIdMsg(ident0.mn,ident0.mt);//LimIdToFumMsg(ident0);
	}
}

