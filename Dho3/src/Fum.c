
#include "Fum.h"

// === Interfaces externes vers Fum ===
void VbmToFumMsg(Ident ident) {
	dhoCore_Fum.ident1.mh=ident.mh;
    if (cc_step1 >= UNSYNCRATE_2s-THRESHRATE_100ms || cc_step1<= READYTOSTARTRATE_1s+THRESHRATE_100ms) {
    	dhoMpc.RxSlow1= false;
        counterDebounce1 = 0;
    } else if (cc_step1 >= SLOWRATE_1500ms-THRESHRATE_100ms) {
        if (counterDebounce1 < DEBOUNCE_3x) {
            (counterDebounce1)++;
        } else {
        	dhoMpc.RxSlow1 = true;
        }
    }
    dhoCore_Fum.RxTooSlow1=false;
    cc_step1=0;
}
void RamToFumMsg(Ident ident) {
	dhoCore_Fum.ident2.mh=ident.mh;
    dhoCore_Fum.RxTooSlow2=false;
    cc_step2=0;
}
void VbmIdToFumMsg(Ident ident) {
	dhoMpc.checkId1= dhoMpc.RxSlow1;
	dhoCore_Fum.ident1.mn=ident.mn;
	dhoCore_Fum.ident1.mt=ident.mt;
}
void RamIdToFumMsg(Ident ident) {
	dhoCore_Fum.ident2.mn=ident.mn;
	dhoCore_Fum.ident2.mt=ident.mt;
}
// === Init === //
void FumInit(){
	DhoCoreInit_Fum();
	DhoMpcInit();
}

// === Fonction principale appelée toutes les 10 ms ===
void Fum_step10ms(){
	compteurStep++;
    if (compteurStep % 100 == 0) dhoCore_Fum.ident0.mh++;

    if (cc_step1 >= TIMEOUT_5S){
    	dhoCore_Fum.RxTooSlow1=true;
    }
    else{
        cc_step1++;
    }
    if (cc_step2 >= TIMEOUT_5S){
    	dhoCore_Fum.RxTooSlow2=true;
    }
    else{
        cc_step2++;
    }
    if (cc_step1 >= SLOWRATE_1500ms+THRESHRATE_100ms){
    	dhoMpc.RxSlow1=false;
    }

	DhoCoreCall_Fum();
	DhoMpcCall();
	dhoCore_Fum.ident0 = DhoMergeMpc();

	if (0 == (compteurStep %PERIOD_STORE_5s)){
		Store(filename_Fum,dhoCore_Fum.ident0.mn, dhoCore_Fum.ident0.mt, dhoCore_Fum.ident0.mh);
	}
	if (0 == (compteurStep %dhoCore_Fum.per1)){
		FumToVbmMsg(dhoCore_Fum.ident0);
	}
	if (0 == (compteurStep %dhoCore_Fum.per2)){
		FumToRamMsg(dhoCore_Fum.ident0);
	}
	if (0 == (compteurStep %PERIOD_MSGID_5s)){
		FumIdToVbmMsg(dhoCore_Fum.ident0);
	}
	if (0 == (compteurStep %PERIOD_MSGID_5s)){
		FumIdToRamMsg(dhoCore_Fum.ident0);
	}
}


/*
 * 	printf("Fum : Mpc cmd State on: %s\n", dhoMpcOutputs.CmdsStateOn ? "true" : "false");
	printf("Fum : DhoMpc state: %d\n",dhoMpcOutputs.State);
	printf("Fum : RxSlow1_cc %" PRIu32 ", cc_step1: %" PRIu32", cc_step2: %" PRIu32 "\n", RxSlow1_cc, cc_step1, cc_step2);
	printf("Mnh_Fum -> mn1: %" PRIu32 ", mh1: %" PRIu32 "\n", mn1, mh1);
	printf("********Fum : mn: %" PRIu32 ", mh: %" PRIu32", mt: %" PRIu32 "\n", mn0, mh0, mt0);
 */
