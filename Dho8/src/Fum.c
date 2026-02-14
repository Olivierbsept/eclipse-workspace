
#include "Fum.h"

// === Interfaces externes vers Fum ===
void VbmToFumMsg(IdentVbm ident) {
	idents.Ident1.mh=ident.mh;
    trigs.Rx1Trig=true;
}
void LimToFumMsg(IdentVbm ident) {
	idents.Ident2.mh=ident.mh;
    trigs.Rx2Trig=true;
}
void VbmIdToFumMsg(IdentVbm ident) {
	idents.Ident1.mn=ident.mn;
	idents.Ident1.mt=ident.mt;
	trigs.RxId1Trig=true;
}
void LimIdToFumMsg(IdentVbm ident) {
	idents.Ident2.mn=ident.mn;
	idents.Ident2.mt=ident.mt;
}

// === Init === //
void FumInit(){
	ident0.mn=100;
	ident0.mt=101;
	ident0.mh= 10000;
	FumCounter=ident0.mh;

	phases.SyncConfigPhase=false;
	phases.SyncDiagPhase=true;

	trigs.TxTrig=false;
	trigs.DiagTrig=false;

	configs.DiagTrigCfg=false;
	configs.ParamCheckCfg=true;
	InitDho_Fum(configs);
}

// === Fonction principale appelée toutes les 10 ms ===
void Fum_step50ms() {
	compteurStep50ms++;
    if (compteurStep50ms % PERIOD_COUNT50ms_1s == 0){
    	FumCounter++;
    	ident0.mh=FumCounter;
    }
    if (phases.SyncConfigPhase){
        Call50msDho_Fum(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	FumToVbmMsg(ident0);
        	FumToLimMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (phases.SyncDiagPhase){
        Call50msDho_Fum_Diag(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	FumToVbmMsg(ident0);
        	FumToLimMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (0 == (compteurStep50ms %PERIOD_MSGID50ms_3s)){
    	FumToVbmMsg(ident0);
    	FumToLimMsg(ident0);
    }
    FumCounter=ident0.mh;

	if (0 == (compteurStep50ms %PERIOD_STORE50ms_5s)){
		Store(filename_Fum,ident0.mn, ident0.mt, ident0.mh);
	}

	if (0 == (compteurStep50ms %PERIOD_MSGID50ms_5s)){
		FumIdToVbmMsg(ident0);
		FumIdToLimMsg(ident0);
	}


}

