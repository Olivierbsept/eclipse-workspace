
#include "Lim.h"
#include <inttypes.h>
#include <stdio.h>

// === Interfaces externes vers Vbm ===
void VbmToLimMsg(IdentVbm ident) {
	idents.Ident1.mh=ident.mh;
    trigs.Rx1Trig=true;
}
void FumToLimMsg(IdentVbm ident) {
	idents.Ident2.mh=ident.mh;
    trigs.Rx2Trig=true;
}
void VbmIdToLimMsg(IdentVbm ident) {
	idents.Ident1.mn=ident.mn;
	idents.Ident1.mt=ident.mt;
	trigs.RxId1Trig=true;
}
void FumIdToLimMsg(IdentVbm ident) {
	idents.Ident2.mn=ident.mn;
	idents.Ident2.mt=ident.mt;
}

// === Init === //
void LimInit(){
	ident0.mn=100;
	ident0.mt=101;
	ident0.mh= 10000;
	LimCounter=ident0.mh;

	phases.SyncConfigPhase=false;
	phases.SyncDiagPhase=true;

	trigs.DiagTrig=false;
	trigs.TxTrig=false;

	configs.DiagTrigCfg=false;
	configs.ParamCheckCfg=false;

	InitDho_Lim(configs);
}

// === Fonction principale appelée toutes les 10 ms ===
void Lim_step100ms() {
	compteurStep++;
    if (compteurStep % 10 == 0){
    	LimCounter++;
    	ident0.mh=LimCounter;
    }
    if (phases.SyncConfigPhase){
        Call100msDho_Lim(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	LimToVbmMsg(ident0);
        	LimToFumMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (phases.SyncDiagPhase){
        Call100msDho_Lim_Diag(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	LimToVbmMsg(ident0);
        	LimToFumMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (0 == (compteurStep %PERIOD_MSGID100ms_3s)){
    	LimToVbmMsg(ident0);
    	LimToFumMsg(ident0);
    }

	LimCounter=ident0.mh;

	if (0 == (compteurStep %PERIOD_STORE100ms_5s)){
		Store(filename_Lim,ident0.mn, ident0.mt, ident0.mh);
	}

	if (0 == (compteurStep %PERIOD_MSGID100ms_5s)){
		LimIdToVbmMsg(ident0);
		LimIdToFumMsg(ident0);
	}
}

