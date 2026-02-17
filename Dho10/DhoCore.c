
#include "DhoCore.h"
#include <inttypes.h>
#include <stdio.h>

void DhoInit(EcuStruct* ecuAddr,DhoConfigs configs){
	ecuAddr->cc_100ms=0;
	ecuAddr->cc2_100ms=0;
	ecuAddr->cc1_100ms=0;
	ecuAddr->per_100ms=20;
	ecuAddr->rxSlow1=false;
	ecuAddr->rxTooSlow1=true;
	ecuAddr->rxTooSlow2=true;
	ecuAddr->counterDebounce1=0;
	ecuAddr->paramCheckCfg=configs.ParamCheckCfg;
	ecuAddr->diagTrigCfg=configs.DiagTrigCfg;
}
void DhoInit_Ecu1(DhoConfigs configs){
	DhoInit(&ecu1,configs);
}
void InitDho(DhoConfigs configs){
	DhoInit(&ecu0,configs);
}
void InitDho_Ecu2(DhoConfigs configs){
	DhoInit(&ecu2,configs);
}

void DhoCall_100ms_Ecu(EcuStruct* ecuAddr,DhoTrigs* trigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	ecuAddr->cc_100ms++;
	if ((ecuAddr->per_100ms != 0) && ((ecuAddr->cc_100ms % ecuAddr->per_100ms) == 0) ) {
		trigsAddr->TxTrig=true;
	}
	if (trigsAddr->Rx1Trig){
		trigsAddr->Rx1Trig=false;
		ecuAddr->rxTooSlow1=false;
		ecuAddr->cc1_100ms=0;
	}
	else if (ecuAddr->cc1_100ms >= TIMEOUT100ms_5S){
		ecuAddr->rxTooSlow1=true;
	}
	else{
		ecuAddr->cc1_100ms++;
	}

	if (trigsAddr->Rx2Trig){
		trigsAddr->Rx2Trig=false;
		ecuAddr->rxTooSlow2=false;
		ecuAddr->cc2_100ms=0;
	}
	else if (ecuAddr->cc2_100ms >= TIMEOUT100ms_5S){
		ecuAddr->rxTooSlow2=true;
	}
	else{
		ecuAddr->cc2_100ms++;
	}

	// Synchronisation passive with Ecu1 and Ecu2
	if ( (ident0Addr->mn == idents.Ident1.mn && ident0Addr->mt == idents.Ident1.mt) && (idents.Ident1.mn == idents.Ident2.mn && idents.Ident1.mt == idents.Ident2.mt)
				&& (!ecuAddr->rxTooSlow1 && !ecuAddr->rxTooSlow2)
				&& (idents.Ident1.mn !=0xFFFFFFFF && idents.Ident1.mt!=0xFFFF)
				&& (idents.Ident1.mh != 0xFFFFFFFF && idents.Ident2.mh != 0xFFFFFFFF) ){
		ecuAddr->per_100ms = SYNCRATE100ms_1s;
		if (ident0Addr->mh < idents.Ident1.mh || ident0Addr->mh < idents.Ident2.mh){
			ident0Addr->mh = max(idents.Ident1.mh, idents.Ident2.mh);
			trigsAddr->MhTrig = true;
		}
	}

	// Synchronisation passive with Ecu1 only :
	else if (  ( (ident0Addr->mn == idents.Ident1.mn && ident0Addr->mt == idents.Ident1.mt)// Ecu2 is missing and Ecu0 and Ecu1 have the same identity
			&& (!ecuAddr->rxTooSlow1)
			&& (ecuAddr->rxTooSlow2)
			&& (idents.Ident1.mn !=0xFFFFFFFF && idents.Ident1.mt!=0xFFFF)
			&& (idents.Ident1.mh!=0xFFFFFFFF) )
			|| ( (ident0Addr->mn == idents.Ident1.mn && ident0Addr->mt == idents.Ident1.mt)// Ecu2 is present and has a different identity than Ecu0 and Ecu1
			&& (idents.Ident1.mn != idents.Ident2.mn || idents.Ident1.mt != idents.Ident2.mt)
			&& (!ecuAddr->rxTooSlow1 && !ecuAddr->rxTooSlow2)
			&& (idents.Ident1.mn != 0xFFFFFFFF && idents.Ident1.mt != 0xFFFF)
			&& (idents.Ident1.mh != 0xFFFFFFFF) )  ){
		ecuAddr->per_100ms = SYNCRATE100ms_1s;
		if (ident0Addr->mh < idents.Ident1.mh){
			ident0Addr->mh = idents.Ident1.mh;
			trigsAddr->MhTrig = true;
		}
	}

	// Synchronisation passive with Ecu2 only :
	else if (  ( (ident0Addr->mn == idents.Ident2.mn && ident0Addr->mt == idents.Ident2.mt)// Ecu1 is missing and Ecu0 has same identity than Ecu2
			&& (!ecuAddr->rxTooSlow2)
			&& (ecuAddr->rxTooSlow1)
			&& (idents.Ident2.mn != 0xFFFFFFFF && idents.Ident2.mt != 0xFFFF)
			&& (idents.Ident2.mh != 0xFFFFFFFF) )
			|| ( (ident0Addr->mn == idents.Ident2.mn && ident0Addr->mt == idents.Ident2.mt) // Ecu1 is present and has a different identity than Ecu0 and Ecu2
			&& (idents.Ident2.mn != idents.Ident1.mn || idents.Ident2.mt != idents.Ident1.mt)
			&& (!ecuAddr->rxTooSlow2 && !ecuAddr->rxTooSlow1)
			&& (idents.Ident2.mn != 0xFFFFFFFF && idents.Ident2.mt != 0xFFFF)
			&& (idents.Ident2.mh != 0xFFFFFFFF) )  ){
		ecuAddr->per_100ms = SYNCRATE100ms_1s;
		if (ident0Addr->mh < idents.Ident2.mh){
			ident0Addr->mh = idents.Ident2.mh;
			trigsAddr->MhTrig = true;
		}
	}

	// Forced synchronisation passive with Ecu1 and Ecu2 : Ecu1 and Ecu2 have same identity, different of Ecu0
	else if ((ident0Addr->mn != idents.Ident1.mn || ident0Addr->mt != idents.Ident1.mt) && (idents.Ident1.mn == idents.Ident2.mn && idents.Ident1.mt == idents.Ident2.mt)
			&& (!ecuAddr->rxTooSlow1 && !ecuAddr->rxTooSlow2)
			&& (idents.Ident1.mn != 0xFFFFFFFF && idents.Ident1.mt != 0xFFFF && idents.Ident1.mh != 0xFFFFFFFF) ){
		ident0Addr->mh=idents.Ident1.mh;
		ident0Addr->mn=idents.Ident1.mn;
		ident0Addr->mt=idents.Ident1.mt;
		ecuAddr->per_100ms = SYNCRATE100ms_1s;
		trigsAddr->MhTrig = true;
		trigsAddr->MnTrig = true;
	}

	// No synchronisation:
	// Ecu1 and Ecu2 are both absent or
	// Ecu1 is absent and Ecu0 and Ecu2 have different identities or
	// Ecu2 is absent and Ecu0 and Ecu1 have different identities or
	// Ecu1 and Ecu2 are all present with each identity different
	else {
		ecuAddr->per_100ms = UNSYNCRATE100ms_2s;
	}
}
void DhoCall_100ms_Diag_Ecu(EcuStruct* ecuAddr,DhoTrigs* trigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	ecuAddr->cc_100ms++;
	if ( (ecuAddr->per_100ms != 0) && ((ecuAddr->cc_100ms % ecuAddr->per_100ms) == 0) ) {
		trigsAddr->TxTrig=true;
	}
	if (trigsAddr->Rx1Trig){
		trigsAddr->Rx1Trig=false;
		ecuAddr->rxTooSlow1=false;
		if (ecuAddr->paramCheckCfg){
			if (ecuAddr->cc1_100ms >= READYTOSTARTRATE100ms_2sBelow) {
				ecuAddr->rxSlow1= false;
				ecuAddr->counterDebounce1 = 0;
			} else if (ecuAddr->cc1_100ms >= SLOWRATE100ms_1500msBelow) {
				if (ecuAddr->counterDebounce1 < DEBOUNCE_3x) {
					ecuAddr->counterDebounce1++;
				} else {
					ecuAddr->rxSlow1 = true;
				}
			}
		}
		ecuAddr->cc1_100ms=0;
	}
	else if (ecuAddr->cc1_100ms >= TIMEOUT100ms_5S){
		ecuAddr->rxTooSlow1=true;
	}
	else{
		ecuAddr->cc1_100ms++;
	}

	if (trigsAddr->Rx2Trig){
		trigsAddr->Rx2Trig=false;
		ecuAddr->cc2_100ms=0;
	}
	else if (ecuAddr->cc2_100ms >= TIMEOUT100ms_5S){
		ecuAddr->rxTooSlow2=true;
	}
	else{
		ecuAddr->cc2_100ms++;
	}

	// Forced synchronisation passive with Ecu1 (ie. FUM)
	if (ecuAddr->paramCheckCfg && ecuAddr->rxSlow1 && trigsAddr->RxId1Trig && idents.Ident1.mn != 0xFFFFFFFF && idents.Ident1.mt != 0xFFFF && idents.Ident1.mh != 0xFFFFFFFF){
		ident0Addr->mh=idents.Ident1.mh;
		ident0Addr->mn=idents.Ident1.mn;
		ident0Addr->mt = idents.Ident1.mt;
		trigsAddr->MhTrig=true;
		trigsAddr->MnTrig = true;
		trigsAddr->RxId1Trig = false;
	}

	// Forced synchronisation active (ie. VBM)
	if (ecuAddr->diagTrigCfg && trigsAddr->DiagTrig){
		ecuAddr->per_100ms = SLOWRATE100ms_1500ms;
	}
	else{
		ecuAddr->per_100ms = READYTOSTARTRATE100ms_2s;
	}
}

void DhoCall_100ms_Ecu1(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Ecu(&ecu1,rxTrigsAddr,ident0Addr,idents);
}
void DhoCall_100ms(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Ecu(&ecu0,rxTrigsAddr,ident0Addr,idents);
}
void DhoCall_100ms_Ecu2(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Ecu(&ecu2,rxTrigsAddr,ident0Addr,idents);
}

void DhoCall_100ms_Diag_Ecu1(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Diag_Ecu(&ecu1,rxTrigsAddr,ident0Addr,idents);
}
void DhoCall_100ms_Diag(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Diag_Ecu(&ecu0,rxTrigsAddr,ident0Addr,idents);
}
void DhoCall_100ms_Diag_Ecu2(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Diag_Ecu(&ecu2,rxTrigsAddr,ident0Addr,idents);
}
