
#include "Lim.h"

static DhoConfigs configs_Lim;
static uint32_T compteurStep100ms = 0;
static DhoIdent ident0;
static DhoTrigs trigs;
static DhoIdents idents;
static uint32_T LimCounter;
extern Phases phases; //défini dans Vbm.h

// === Interfaces externes vers Vbm ===
void VbmToLimMsg(DhoIdent ident) {
	idents.Ident1.mh=ident.mh;
    trigs.Rx1Trig=true;
}
void VbmToLimMsg2(uint32_T mh) {
	idents.Ident1.mh=mh;
    trigs.Rx1Trig=true;
}
void VbmIdToLimMsg(DhoIdent ident) {
	idents.Ident1.mn=ident.mn;
	idents.Ident1.mt=ident.mt;
	trigs.RxId1Trig=true;
}
void VbmIdToLimMsg2(uint32 mn, uint16 mt){
	idents.Ident1.mn=mn;
	idents.Ident1.mt=mt;
	trigs.RxId1Trig=true;
}
void sendFumToLimMsg(uint32_T mh){
	idents.Ident2.mh=mh;
    trigs.Rx2Trig=true;
}
void sendFumIdToLimMsg(uint32_T mn, uint16_T mt){
	idents.Ident2.mn=mn;
	idents.Ident2.mt=mt;

}
// === Init === //
void LimInit(){
	ident0.mn=100;
	ident0.mt=110;
	ident0.mh= 100;
	LimCounter=ident0.mh;

	idents.Ident1.mh=0xFFFFFFFF;
	idents.Ident1.mt=0xFFFF;
	idents.Ident1.mh=0xFFFFFFFF;

	idents.Ident2.mh=0xFFFFFFFF;
	idents.Ident2.mt=0xFFFF;
	idents.Ident2.mh=0xFFFFFFFF;

	trigs.DiagTrig=false;
	trigs.TxTrig=false;
	trigs.SyncAllwd=false;

	configs_Lim.DiagTrigCfg=false; //force cfg après paramétrage
	configs_Lim.ParamCheckCfg=true; //accepte cfg si condition ok

	configs_Lim.ResetMnCfg= 0xFFFFFFFD;
	configs_Lim.ResetMtCfg= 0xFFFD;
	DhoInit_Lim(configs_Lim);
}

// === Fonction principale appelée toutes les 100 ms ===
void Lim_step100ms() {
	compteurStep100ms++;
    if (compteurStep100ms % PERIOD_COUNT100ms_1s == 0){
    	if (phases.SyncConfigPhase)LimCounter++;
    	ident0.mh=LimCounter;
    }
    if (phases.SyncConfigPhase){
        DhoCall_100ms_Lim(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	LimToVbmMsg(ident0);
        	ReceiveLimMsg(ident0.mh);//LimToFumMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (phases.SyncDiagPhase){
        DhoCall_100ms_Diag_Lim(&trigs,&ident0,idents);

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
	if (0 == (compteurStep100ms %PERIOD_MSGID100ms_6s)){// to receive MI not synchronised from other Ecus
		trigs.SyncAllwd = true;
	}
}

