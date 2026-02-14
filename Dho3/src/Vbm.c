
#include "Vbm.h"

// === Interfaces externes vers Vbm ===
void FumToVbmMsg(Ident ident) {
    dhoCore_Vbm.ident1.mh=ident.mh;
    dhoCore_Vbm.RxTooSlow1=false;
    cc_step1=0;
}
void RamToVbmMsg(Ident ident) {
	dhoCore_Vbm.ident2.mh = ident.mh;
    dhoCore_Vbm.RxTooSlow2=false;
    cc_step2=0;
}
void FumIdToVbmMsg(Ident ident) {
	dhoCore_Vbm.ident1.mn=ident.mn;
	dhoCore_Vbm.ident1.mt=ident.mt;
}
void RamIdToVbmMsg(Ident ident) {
	dhoCore_Vbm.ident2.mn=ident.mn;
	dhoCore_Vbm.ident2.mt=ident.mt;
}

// === Init === //
void VbmInit(){
	DhoCoreInit_Vbm();
    DhoMprInit();
}

// === Fonction principale appelée toutes les 10 ms ===
void Vbm_step10ms() {
	compteurStep++;
    if (compteurStep % 100 == 0) dhoCore_Vbm.ident0.mh++;

    if (cc_step1 >= TIMEOUT_5S){
    	dhoCore_Vbm.RxTooSlow1=true;
    }
    else{
        cc_step1++;
    }
    if (cc_step2 >= TIMEOUT_5S){
    	dhoCore_Vbm.RxTooSlow2=true;
    }
    else{
        cc_step2++;
    }

    DhoMprCall();
    DhoCoreCall_Vbm();
    dhoCore_Vbm.per1 = DhoMergeMpr();

	if (0 == (compteurStep %PERIOD_STORE_5s)){
		Store(filename_Vbm,dhoCore_Vbm.ident0.mn, dhoCore_Vbm.ident0.mt, dhoCore_Vbm.ident0.mh);
	}
	if (0 == (compteurStep %dhoCore_Vbm.per1)){
		VbmToFumMsg(dhoCore_Vbm.ident0);
	}
	if (0 == (compteurStep %dhoCore_Vbm.per2)){
		VbmToRamMsg(dhoCore_Vbm.ident0);
	}
	if (0 == (compteurStep %PERIOD_MSGID_5s)){
		VbmIdToFumMsg(dhoCore_Vbm.ident0);
	}
	if (0 == (compteurStep %PERIOD_MSGID_5s)){
		VbmIdToRamMsg(dhoCore_Vbm.ident0);
	}
}

