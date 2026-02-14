
#include "Vbm.h"
#include <inttypes.h>
#include <stdio.h>

// === Interfaces externes vers Vbm ===
void FumToVbmMsg(IdentVbm ident) {
	idents.Ident1.mh=ident.mh;
    trigs.Rx1Trig=true;
}
void LimToVbmMsg(IdentVbm ident) {
	idents.Ident2.mh=ident.mh;
    trigs.Rx2Trig=true;
}
void FumIdToVbmMsg(IdentVbm ident) {
	idents.Ident1.mn=ident.mn;
	idents.Ident1.mt=ident.mt;
	trigs.RxId1Trig=true;
}
void LimIdToVbmMsg(IdentVbm ident) {
	idents.Ident2.mn=ident.mn;
	idents.Ident2.mt=ident.mt;
}

// === Init === //
void VbmInit(){
	ident0.mn=10;
	ident0.mt=11;
	ident0.mh= 1000;
	VbmCounter=ident0.mh;

	phases.SyncConfigPhase=false;
	phases.SyncDiagPhase=true;

	trigs.DiagTrig=true;
	trigs.TxTrig=false;

	configs.DiagTrigCfg=true;
	configs.ParamCheckCfg=false;

	InitDho_Vbm(configs);
}

// === Fonction principale appelée toutes les 10 ms ===
void Vbm_step100ms() {
	compteurStep++;
    if (compteurStep % 10 == 0){
    	VbmCounter++;
    	ident0.mh=VbmCounter;
    }

    if (phases.SyncConfigPhase){
        Call100msDho_Vbm(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	VbmToFumMsg(ident0);
        	VbmToLimMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (phases.SyncDiagPhase){
        Call100msDho_Vbm_Diag(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	VbmToFumMsg(ident0);
        	VbmToLimMsg(ident0);
        	trigs.TxTrig = false;
        }
    }
    else if (0 == (compteurStep %PERIOD_MSGID100ms_3s)){
    	VbmToFumMsg(ident0);
    	VbmToLimMsg(ident0);
    }
	VbmCounter=ident0.mh;
	if (0 == (compteurStep %PERIOD_STORE100ms_5s)){
		Store(filename_Vbm,ident0.mn, ident0.mt, ident0.mh);
	}
	if (0 == (compteurStep %PERIOD_MSGID100ms_5s)){
		VbmIdToFumMsg(ident0);
		VbmIdToLimMsg(ident0);
	}
}

