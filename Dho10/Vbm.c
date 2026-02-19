
#include "Vbm.h"
// === Interfaces externes vers Vbm ===
void LimToVbmMsg(DhoIdent ident) {
	idents.Ident2.mh=ident.mh;
    trigs.Rx2Trig=true;
}

void LimIdToVbmMsg(DhoIdent ident) {
	idents.Ident2.mn=ident.mn;
	idents.Ident2.mt=ident.mt;
}

void sendFumToVbmMsg(uint32_t mh){
	idents.Ident1.mh=mh;
    trigs.Rx1Trig=true;
}
void sendFumIdToVbmMsg(uint32_t mn, uint16_t mt){
	idents.Ident1.mn=mn;
	idents.Ident1.mt=mt;
	trigs.RxId1Trig=true;
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

	DhoInit_Ecu1(configs);
}

// === Fonction principale appelée toutes les 100 ms ===
void Vbm_step100ms() {
	compteurStep100ms++;
    if (compteurStep100ms % PERIOD_COUNT100ms_1s == 0){
    	VbmCounter++;
    	ident0.mh=VbmCounter;
    }

    if (phases.SyncConfigPhase){
        DhoCall_100ms_Ecu1(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	ReceiveVbmMsg(ident0.mh);//VbmToFumMsg(ident0);
        	VbmToLimMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (phases.SyncDiagPhase){
        DhoCall_100ms_Diag_Ecu1(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	ReceiveVbmMsg(ident0.mh);//VbmToFumMsg(ident0);
        	VbmToLimMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (0 == (compteurStep100ms %PERIOD_MSGID100ms_3s)){
    	ReceiveVbmMsg(ident0.mh);//VbmToFumMsg(ident0);
    	VbmToLimMsg(ident0);
    }
	VbmCounter=ident0.mh;
	if (0 == (compteurStep100ms %PERIOD_STORE100ms_5s)){
		Store(filename_Vbm,ident0.mn, ident0.mt, ident0.mh);
	}
	if (0 == (compteurStep100ms %PERIOD_MSGID100ms_5s)){
		ReceiveVbmIdMsg(ident0.mn,ident0.mt);//VbmIdToFumMsg(ident0);

    	printf("Debug Vbm : %" PRId32 "\n", ident0.mn);
		VbmIdToLimMsg(ident0);
	}
}

