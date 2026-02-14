
#include "Vbm.h"

// === Interfaces externes vers Vbm ===
void FumToVbmMsg(IdentVbm ident) {
    dhoMic.Rx1Trig=true;
    dhoMic.ident1.mh=ident.mh;
}
void RamToVbmMsg(IdentVbm ident) {
    dhoMic.Rx2Trig=true;
    dhoMic.ident2.mh=ident.mh;
}
void FumIdToVbmMsg(IdentVbm ident) {
	dhoMic.ident1.mn=ident.mn;
	dhoMic.ident1.mt=ident.mt;
}
void RamIdToVbmMsg(IdentVbm ident) {
	dhoMic.ident2.mn=ident.mn;
	dhoMic.ident2.mt=ident.mt;
}

// === Init === //
void VbmInit(){
    DhoMicInit();
    dhoMic.eemState=ST_ReadytoStart;
    DhoMirInit();
    VbmCounter=1000;
}

// === Fonction principale appelée toutes les 10 ms ===
void Vbm_step10ms() {
	compteurStep++;
    if (compteurStep % 100 == 0){
    	VbmCounter++;
    	dhoMic.ident0.mh=VbmCounter;
    }

    DhoMicStep10ms();
    if (dhoMic.StoreTrig){
    	VbmCounter= dhoMic.ident0.mh;
		Store(filename_Vbm,dhoMic.ident0.mn, dhoMic.ident0.mt, dhoMic.ident0.mh);
		dhoMic.StoreTrig=false;
    }
    dhoMir.Sync1Active=dhoMic.Sync1Active;
    dhoMir.Sync2Active=dhoMic.Sync2Active;
    dhoMir.RxTooSlow1=false;
    dhoMir.flagDiag=true;

    DhoMirStep10ms();
    if (dhoMir.TxTrig){
    	VbmToFumMsg(dhoMic.ident0);
    	VbmToRamMsg(dhoMic.ident0);
    	dhoMir.TxTrig = false;
    }
	if (0 == (compteurStep %PERIOD_MSGID_5s)){
		VbmIdToFumMsg(dhoMic.ident0);
	}
	if (0 == (compteurStep %PERIOD_MSGID_5s)){
		VbmIdToRamMsg(dhoMic.ident0);
	}

}

