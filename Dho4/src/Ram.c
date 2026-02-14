
#include "Ram.h"

// === Interfaces externes vers Ram ===
void VbmToRamMsg(Ident ident){
	dhoCore_Ram.ident1.mh=ident.mh;
    dhoCore_Ram.RxTooSlow1=false;
    cc_step1=0;
}
void FumToRamMsg(Ident ident){
	dhoCore_Ram.ident2.mh=ident.mh;
    dhoCore_Ram.RxTooSlow2=false;
    cc_step2=0;
}
void VbmIdToRamMsg(Ident ident){
	dhoCore_Ram.ident1.mn=ident.mn;
	dhoCore_Ram.ident1.mt=ident.mt;
}
void FumIdToRamMsg(Ident ident){
	dhoCore_Ram.ident2.mn=ident.mn;
	dhoCore_Ram.ident2.mt=ident.mt;
}

// === Init === //
void RamInit(){
	DhoCoreInit_Ram();
}

// === Fonction principale appelée toutes les 10 ms ===
void Ram_step10ms(){
	compteurStep++;
    if (compteurStep % 100 == 0) dhoCore_Ram.ident0.mh++;

    if (cc_step1 >= TIMEOUT_5S){
    	dhoCore_Ram.RxTooSlow1=true;
    }
    else{
        cc_step1++;
    }
    if (cc_step2 >= TIMEOUT_5S){
    	dhoCore_Ram.RxTooSlow2=true;
    }
    else{
        cc_step2++;
    }

    DhoCoreCall_Ram();

	if (0 == (compteurStep %PERIOD_STORE_5s)){
		Store(filename_Ram,dhoCore_Ram.ident0.mn, dhoCore_Ram.ident0.mt, dhoCore_Ram.ident0.mh);
	}
	if (0 == (compteurStep %dhoCore_Ram.per1)){
		RamToVbmMsg(dhoCore_Ram.ident0);
	}
	if (0 == (compteurStep %dhoCore_Ram.per2)){
		RamToFumMsg(dhoCore_Ram.ident0);
	}
	if (0 == (compteurStep %PERIOD_MSGID_5s)){
		RamIdToVbmMsg(dhoCore_Ram.ident0);
	}
	if (0 == (compteurStep %PERIOD_MSGID_5s)){
		RamIdToFumMsg(dhoCore_Ram.ident0);
	}
}

/*printf("Mnh_Ram -> mn: %" PRIu32 ", mh: %" PRIu32 ", mt: %" PRIu32 "\n", dhoCoreOutputs.ident.mn, dhoCoreOutputs.ident.mh, dhoCoreOutputs.ident.mt);*/
