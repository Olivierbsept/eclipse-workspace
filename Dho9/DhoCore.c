/*
 * DhoCore.c
 *
 *  Created on: 9 juin 2025
 *      Author: olivierbessettemac
 */


#include "DhoCore.h"
#include <inttypes.h>
#include <stdio.h>

void InitDho(EcuStruct* ecuAddr,Configs configs){
	ecuAddr->cc_50ms=0;
	ecuAddr->cc2_50ms=0;
	ecuAddr->cc1_50ms=0;
	ecuAddr->per_50ms=20;
	ecuAddr->rxSlow1=false;
	ecuAddr->rxTooSlow1=true;
	ecuAddr->rxTooSlow2=true;
	ecuAddr->counterDebounce1=0;
	ecuAddr->paramCheckCfg=configs.ParamCheckCfg;
	ecuAddr->diagTrigCfg=configs.DiagTrigCfg;
}
void InitDho_Vbm(Configs configs){
	InitDho(&ecuVbm,configs);
}
void InitDho_Fum(Configs configs){
	InitDho(&ecuFum,configs);
}
void InitDho_Lim(Configs configs){
	InitDho(&ecuLim,configs);
}

void Call50msDho(EcuStruct* ecuAddr,Trigs* rxTrigsAddr,IdentEcu* ident0Addr, Idents idents){
	ecuAddr->cc_50ms++;
	if (ecuAddr->per_50ms != 0 && ecuAddr->cc_50ms % ecuAddr->per_50ms == 0) {
		rxTrigsAddr->TxTrig=true;
	}
	if (rxTrigsAddr->Rx1Trig){
		rxTrigsAddr->Rx1Trig=false;
		ecuAddr->rxTooSlow1=false;
		ecuAddr->cc1_50ms=0;
	}
	else if (ecuAddr->cc1_50ms >= TIMEOUT50ms_5S){
		ecuAddr->rxTooSlow1=true;
	}
	else{
		ecuAddr->cc1_50ms++;
	}

	if (rxTrigsAddr->Rx2Trig){
		rxTrigsAddr->Rx2Trig=false;
		ecuAddr->rxTooSlow2=false;
		ecuAddr->cc2_50ms=0;
	}
	else if (ecuAddr->cc2_50ms >= TIMEOUT50ms_5S){
		ecuAddr->rxTooSlow2=true;
	}
	else{
		ecuAddr->cc2_50ms++;
	}

	// sync à 3
	if ((ident0Addr->mn == idents.Ident1.mn && ident0Addr->mt == idents.Ident1.mt)
				&& (idents.Ident1.mn == idents.Ident2.mn && idents.Ident1.mt == idents.Ident2.mt)
				&& !ecuAddr->rxTooSlow1 && !ecuAddr->rxTooSlow2
				&& idents.Ident1.mn !=0xFFFFFFFF && idents.Ident1.mt!=0xFFFF && idents.Ident1.mh!=0xFFFFFFFF
				&& idents.Ident2.mn !=0xFFFFFFFF && idents.Ident2.mt!=0xFFFF && idents.Ident2.mh!=0xFFFFFFFF){
			ident0Addr->mh = max3(ident0Addr->mh, idents.Ident1.mh, idents.Ident2.mh);
			ecuAddr->per_50ms = SYNCRATE50ms_1s;
	}

	//sync avec 1
	else if ((ident0Addr->mn == idents.Ident1.mn && ident0Addr->mt == idents.Ident1.mt)
			&& (idents.Ident1.mn != idents.Ident2.mn || idents.Ident1.mt != idents.Ident2.mt)
			&& !ecuAddr->rxTooSlow1
			&& idents.Ident1.mn !=0xFFFFFFFF && idents.Ident1.mt!=0xFFFF && idents.Ident1.mh!=0xFFFFFFFF){
		ident0Addr->mh = max2(ident0Addr->mh, idents.Ident1.mh);
		ecuAddr->per_50ms = SYNCRATE50ms_1s;
	}

	//sync avec 2 (si LIM, avec FUM)
	else if ((ident0Addr->mn == idents.Ident2.mn && ident0Addr->mt == idents.Ident2.mt)
			&& (idents.Ident1.mn != idents.Ident2.mn || idents.Ident1.mt != idents.Ident2.mt)
			&& !ecuAddr->rxTooSlow2
			&& idents.Ident2.mn !=0xFFFFFFFF && idents.Ident2.mt!=0xFFFF && idents.Ident2.mh!=0xFFFFFFFF){
		ident0Addr->mh = max2(ident0Addr->mh, idents.Ident2.mh);
		ecuAddr->per_50ms = SYNCRATE50ms_1s;
		//printf("Debug DhoCore3-1 : %" PRId32 "\n", ident0Addr->mh);
		//printf("Debug DhoCore3-2 : %" PRId32 "\n", ident0Addr);
	}

	//forced by majority
	else if ( (ident0Addr->mn != idents.Ident1.mn || ident0Addr->mt != idents.Ident1.mt)
			&& (idents.Ident1.mn == idents.Ident2.mn && idents.Ident1.mt == idents.Ident2.mt)
			&& (!ecuAddr->rxTooSlow1 && !ecuAddr->rxTooSlow2)
			&& (idents.Ident1.mn !=0xFFFFFFFF && idents.Ident1.mt!=0xFFFF && idents.Ident1.mh!=0xFFFFFFFF) ){
		ident0Addr->mh=idents.Ident1.mh;
		ident0Addr->mn=idents.Ident1.mn;
		ident0Addr->mt=idents.Ident1.mt;
		ecuAddr->per_50ms = SYNCRATE50ms_1s;
	}
	else {
		ecuAddr->per_50ms = UNSYNCRATE50ms_2s;
	}
}
void Call50msDho_Diag(EcuStruct* ecuAddr,Trigs* rxTrigsAddr,IdentEcu* ident0Addr, Idents idents){
	ecuAddr->cc_50ms++;
	if (ecuAddr->per_50ms != 0 && ecuAddr->cc_50ms % ecuAddr->per_50ms == 0) {
		rxTrigsAddr->TxTrig=true;
	}
	if (rxTrigsAddr->Rx1Trig){
		rxTrigsAddr->Rx1Trig=false;
		ecuAddr->rxTooSlow1=false;
		if (ecuAddr->paramCheckCfg){
			if (ecuAddr->cc1_50ms >= UNSYNCRATE50ms_2s-THRESHRATE50ms_100ms || ecuAddr->cc1_50ms<= READYTOSTARTRATE50ms_1s+THRESHRATE50ms_100ms) {
				ecuAddr->rxSlow1= false;
				ecuAddr->counterDebounce1 = 0;
			} else if (ecuAddr->cc1_50ms >= SLOWRATE50ms_1500ms-THRESHRATE50ms_100ms) {
				if (ecuAddr->counterDebounce1 < DEBOUNCE_3x) {
					ecuAddr->counterDebounce1++;
				} else {
					ecuAddr->rxSlow1 = true;
				}
			}
		}
		ecuAddr->cc1_50ms=0;
	}
	else if (ecuAddr->cc1_50ms >= TIMEOUT50ms_5S){
		ecuAddr->rxTooSlow1=true;
	}
	else{
		ecuAddr->cc1_50ms++;
	}

	if (rxTrigsAddr->Rx2Trig){
		rxTrigsAddr->Rx2Trig=false;
		ecuAddr->cc2_50ms=0;
	}
	else if (ecuAddr->cc2_50ms >= TIMEOUT50ms_5S){
		ecuAddr->rxTooSlow2=true;
	}
	else{
		ecuAddr->cc2_50ms++;
	}

	if (ecuAddr->rxSlow1 && rxTrigsAddr->RxId1Trig && idents.Ident1.mn !=0xFFFFFFFF && idents.Ident1.mt!=0xFFFF && idents.Ident1.mh!=0xFFFFFFFF){
		ident0Addr->mh=idents.Ident1.mh;
		ident0Addr->mn=idents.Ident1.mn;
		ident0Addr->mt=idents.Ident1.mt;
	}
	if (rxTrigsAddr->RxId1Trig){
		rxTrigsAddr->RxId1Trig=false;
	}
	if (rxTrigsAddr->DiagTrig && ecuAddr->diagTrigCfg){
		ecuAddr->per_50ms = SLOWRATE50ms_1500ms;
	}
	else{
		ecuAddr->per_50ms = UNSYNCRATE50ms_2s;
	}
}

void Call50msDho_Vbm(Trigs* rxTrigsAddr,IdentEcu* ident0Addr, Idents idents){
	Call50msDho(&ecuVbm,rxTrigsAddr,ident0Addr,idents);
}
void Call50msDho_Fum(Trigs* rxTrigsAddr,IdentEcu* ident0Addr, Idents idents){
	Call50msDho(&ecuFum,rxTrigsAddr,ident0Addr,idents);
}
void Call50msDho_Lim(Trigs* rxTrigsAddr,IdentEcu* ident0Addr, Idents idents){
	Call50msDho(&ecuLim,rxTrigsAddr,ident0Addr,idents);
	/*printf("Debug DhoCore3 : %" PRId32 "\n", idents.Ident1.mn);
	printf("Debug DhoCore3 : %" PRId32 "\n", idents.Ident2.mn);
	printf("Debug DhoCore3 : %" PRId32 "\n", ident0Addr->mh);*/
}

void Call50msDho_Vbm_Diag(Trigs* rxTrigsAddr,IdentEcu* ident0Addr, Idents idents){
	Call50msDho_Diag(&ecuVbm,rxTrigsAddr,ident0Addr,idents);
}
void Call50msDho_Fum_Diag(Trigs* rxTrigsAddr,IdentEcu* ident0Addr, Idents idents){
	Call50msDho_Diag(&ecuFum,rxTrigsAddr,ident0Addr,idents);
}
void Call50msDho_Lim_Diag(Trigs* rxTrigsAddr,IdentEcu* ident0Addr, Idents idents){
	Call50msDho_Diag(&ecuLim,rxTrigsAddr,ident0Addr,idents);
}
