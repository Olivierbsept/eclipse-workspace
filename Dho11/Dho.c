#include <stdio.h>
#include "Dho.h"
#include "rec.h"
#include "Rte_CtApTis.h"

#define max(a,b)    (((a) > (b)) ? (a) : (b))

static EcuStruct ecu_Vbm, ecu_Fum, ecu_Lim;
static EcuName ecuName = EcuNA;
static uint32 mn_repair = 0xFFFFFFFF;
static uint16 mt_repair = 0xFFFF;
static uint32 mh_repair = 0xFFFFFFFF;

uint32 getMn_repair(){
	return mn_repair;
}
uint32 getMh_repair(){
	return mh_repair;
}
uint16 getMt_repair(){
	return mt_repair;
}
uint32 getEcuName(){
	return ecuName;
}
void DhoInit_Ecu(EcuStruct* ecuAddr,DhoConfigs dhoConfigs){
	ecuAddr->cc_100ms=0;
	ecuAddr->cc2_100ms=0;
	ecuAddr->cc1_100ms=0;
	ecuAddr->per_100ms=20;
	ecuAddr->counterDebounce1=0;
	ecuAddr->paramCheckCfg=dhoConfigs.ParamCheckCfg;
	ecuAddr->diagTrigCfg=dhoConfigs.DiagTrigCfg;
	ecuAddr->ovrwEnbldCfg=dhoConfigs.OvrwEnbldCfg;
	ecuAddr->ResetMnCfg=dhoConfigs.ResetMnCfg;
	ecuAddr->ResetMtCfg=dhoConfigs.ResetMtCfg;
}

void DhoInit_Vbm(DhoConfigs dhoConfigs){
	DhoInit_Ecu(&ecu_Vbm,dhoConfigs);
}
void DhoInit_Fum(DhoConfigs dhoConfigs){
	DhoInit_Ecu(&ecu_Fum,dhoConfigs);
}
void DhoInit_Lim(DhoConfigs dhoConfigs){
	DhoInit_Ecu(&ecu_Lim,dhoConfigs);
}
void SetOvrwEnbldCfg_Vbm(boolean OvrwEnbldCfg){
	SetOvrwEnbldCfg_Ecu(&ecu_Vbm, OvrwEnbldCfg);
}
void SetOvrwEnbldCfg_Fum(boolean OvrwEnbldCfg){
	SetOvrwEnbldCfg_Ecu(&ecu_Fum, OvrwEnbldCfg);
}
void SetOvrwEnbldCfg_Lim(boolean OvrwEnbldCfg){
	SetOvrwEnbldCfg_Ecu(&ecu_Lim, OvrwEnbldCfg);
}
void SetOvrwEnbldCfg_Ecu(EcuStruct* ecuAddr,boolean OvrwEnbldCfg){
	ecuAddr->ovrwEnbldCfg=OvrwEnbldCfg;
}

void DhoCall_100ms_Ecu(EcuStruct* ecuAddr,DhoTrigs* trigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	ecuAddr->cc_100ms++;
	if ((ecuAddr->per_100ms != 0) && ((ecuAddr->cc_100ms % ecuAddr->per_100ms) == 0) ) {
		trigsAddr->TxTrig=TRUE;
	}
	if (trigsAddr->Rx1Trig){
		trigsAddr->Rx1Trig=FALSE;
		trigsAddr->Rx1TooSlowTrig=FALSE;
		ecuAddr->cc1_100ms=0;
	}
	else if (ecuAddr->cc1_100ms >= TIMEOUT100ms_5S){
		trigsAddr->Rx1TooSlowTrig=TRUE;
	}
	else{
		ecuAddr->cc1_100ms++;
	}

	if (trigsAddr->Rx2Trig){
		trigsAddr->Rx2Trig=FALSE;
		trigsAddr->Rx2TooSlowTrig=FALSE;
		ecuAddr->cc2_100ms=0;
	}
	else if (ecuAddr->cc2_100ms >= TIMEOUT100ms_5S){
		trigsAddr->Rx2TooSlowTrig=TRUE;
	}
	else{
		ecuAddr->cc2_100ms++;
	}

	if (trigsAddr->SyncAllwd)
	{
		trigsAddr->SyncAllwd = FALSE;
		// Synchronisation with Ecu1 and Ecu2
		if ( (ident0Addr->mn == idents.Ident1.mn && ident0Addr->mt == idents.Ident1.mt) && (idents.Ident1.mn == idents.Ident2.mn && idents.Ident1.mt == idents.Ident2.mt)
					&& (!trigsAddr->Rx1TooSlowTrig && !trigsAddr->Rx2TooSlowTrig)
					&& (idents.Ident1.mn !=0xFFFFFFFF && idents.Ident1.mt!=0xFFFF)
					&& (idents.Ident1.mn != 0 && idents.Ident1.mt != 0)//CR3027839
					&& (idents.Ident1.mh != 0xFFFFFFFF && idents.Ident2.mh != 0xFFFFFFFF) )
		{
			ecuAddr->per_100ms = SYNCRATE100ms_1s;
			if (ident0Addr->mh < idents.Ident1.mh || ident0Addr->mh < idents.Ident2.mh){
				ident0Addr->mh = max(idents.Ident1.mh, idents.Ident2.mh);
				trigsAddr->MhTrig = TRUE;
			}
		}

		// Synchronisation with Ecu1 only :
		else if (  ( (ident0Addr->mn == idents.Ident1.mn && ident0Addr->mt == idents.Ident1.mt)// Ecu2 is missing and Ecu0 and Ecu1 have the same identity
				&& (!trigsAddr->Rx1TooSlowTrig)
				&& (trigsAddr->Rx2TooSlowTrig)
				&& (idents.Ident1.mn !=0xFFFFFFFF && idents.Ident1.mt!=0xFFFF)
				&& (idents.Ident1.mn != 0 && idents.Ident1.mt != 0)//CR3027839
				&& (idents.Ident1.mh!=0xFFFFFFFF) )
				|| ( (ident0Addr->mn == idents.Ident1.mn && ident0Addr->mt == idents.Ident1.mt)// Ecu2 is present and has a different identity than Ecu0 and Ecu1
				&& (idents.Ident1.mn != idents.Ident2.mn || idents.Ident1.mt != idents.Ident2.mt)
				&& (!trigsAddr->Rx1TooSlowTrig && !trigsAddr->Rx2TooSlowTrig)
				&& (idents.Ident1.mn != 0xFFFFFFFF && idents.Ident1.mt != 0xFFFF)
				&& (idents.Ident1.mn != 0 && idents.Ident1.mt != 0)//CR3027839
				&& (idents.Ident1.mh != 0xFFFFFFFF) )  )
		{
			ecuAddr->per_100ms = SYNCRATE100ms_1s;
			if (ident0Addr->mh < idents.Ident1.mh){
				ident0Addr->mh = idents.Ident1.mh;
				trigsAddr->MhTrig = TRUE;
			}
			if (ecuAddr->diagTrigCfg && (!trigsAddr->SyncBlkd) )
			{
				if (ecuAddr->ovrwEnbldCfg){
					ecuName = EcuLim;
				}
				else{
					ecuName = EcuNA;
				}
				mn_repair=idents.Ident2.mn;
				mt_repair=idents.Ident2.mt;
				mh_repair=idents.Ident2.mh;
				trigsAddr->changeIdTrig=TRUE;
			}
		}

		// Synchronisation with Ecu2 only :
		else if (  ( (ident0Addr->mn == idents.Ident2.mn && ident0Addr->mt == idents.Ident2.mt)// Ecu1 is missing and Ecu0 has same identity than Ecu2
				&& (!trigsAddr->Rx2TooSlowTrig)
				&& (trigsAddr->Rx1TooSlowTrig)
				&& (idents.Ident2.mn != 0xFFFFFFFF && idents.Ident2.mt != 0xFFFF)
				&& (idents.Ident2.mn != 0 && idents.Ident2.mt != 0)//CR3027839
				&& (idents.Ident2.mh != 0xFFFFFFFF) )
				|| ( (ident0Addr->mn == idents.Ident2.mn && ident0Addr->mt == idents.Ident2.mt) // Ecu1 is present and has a different identity than Ecu0 and Ecu2
				&& (idents.Ident2.mn != idents.Ident1.mn || idents.Ident2.mt != idents.Ident1.mt)
				&& (!trigsAddr->Rx2TooSlowTrig && !trigsAddr->Rx1TooSlowTrig)
				&& (idents.Ident2.mn != 0xFFFFFFFF && idents.Ident2.mt != 0xFFFF)
				&& (idents.Ident2.mn != 0 && idents.Ident2.mt != 0)//CR3027839
				&& (idents.Ident2.mh != 0xFFFFFFFF) )  )
		{
			ecuAddr->per_100ms = SYNCRATE100ms_1s;
			if (ident0Addr->mh < idents.Ident2.mh){
				ident0Addr->mh = idents.Ident2.mh;
				trigsAddr->MhTrig = TRUE;
			}
			if (ecuAddr->diagTrigCfg && (!trigsAddr->SyncBlkd) )
			{
				if (ecuAddr->ovrwEnbldCfg){
					ecuName = EcuFum;
				}
				else{
					ecuName = EcuNA;
				}
				mn_repair=idents.Ident2.mn;
				mt_repair=idents.Ident2.mt;
				mh_repair=idents.Ident2.mh;
				trigsAddr->changeIdTrig=TRUE;
			}
		}
		// Synchronisation by Ecu1 and Ecu2 : Ecu1 and Ecu2 have same identity, different of Ecu0
		else if (  ( (ident0Addr->mn != idents.Ident1.mn) || (ident0Addr->mt != idents.Ident1.mt) ) && ( (idents.Ident1.mn == idents.Ident2.mn) && (idents.Ident1.mt == idents.Ident2.mt) )
				&& (!trigsAddr->Rx1TooSlowTrig && !trigsAddr->Rx2TooSlowTrig)
				&& ( (idents.Ident1.mn != 0xFFFFFFFF) && (idents.Ident1.mt != 0xFFFF) && (idents.Ident1.mh != 0xFFFFFFFF) )
				&& ( (idents.Ident1.mn != 0) && (idents.Ident1.mt != 0) )
				&& ( (ident0Addr->mn != 0) && (ident0Addr->mt != 0) )  )
		{
			if (ecuAddr->diagTrigCfg)
			{
				mn_repair=ident0Addr->mn;
				mt_repair=ident0Addr->mt;
				mh_repair=ident0Addr->mh;
				if (ecuAddr->ovrwEnbldCfg){
					ecuAddr->ecuName = EcuVbm;
				}
				else{
					ecuAddr->ecuName = EcuNA;
				}
				trigsAddr->changeIdTrig=TRUE;
			}
			if (ecuAddr->ovrwEnbldCfg){
				ident0Addr->mn=idents.Ident1.mn;
				ident0Addr->mt=idents.Ident1.mt;
				ident0Addr->mh=max(idents.Ident1.mh,idents.Ident2.mh);
				trigsAddr->TxTrig = TRUE;// Hour must be sent first, with old configuration
				trigsAddr->MhTrig = TRUE;
				trigsAddr->MnTrig = TRUE;
				ecuAddr->per_100ms = SYNCRATE100ms_1s;
			}
		}

		// Synchronisation by Ecu1 and Ecu2 with Ecu0 = 0 : Ecu1 and Ecu2 have same identity, different of Ecu0 and Ecu0 has MT = MN = 0.
		else if (  ( (ident0Addr->mn != idents.Ident1.mn) || (ident0Addr->mt != idents.Ident1.mt) ) && ( (idents.Ident1.mn == idents.Ident2.mn) && (idents.Ident1.mt == idents.Ident2.mt) )
				&& (!trigsAddr->Rx1TooSlowTrig && !trigsAddr->Rx2TooSlowTrig)
				&& ( (idents.Ident1.mn != 0xFFFFFFFF) && (idents.Ident1.mt != 0xFFFF) && (idents.Ident1.mh != 0xFFFFFFFF) )
				&&  ( (idents.Ident1.mn != 0) && (idents.Ident1.mt != 0) )
				&& ( (ident0Addr->mn == 0) && (ident0Addr->mt==0) )  )
		{
			ident0Addr->mn=idents.Ident1.mn;
			ident0Addr->mt=idents.Ident1.mt;
			ident0Addr->mh=max(idents.Ident1.mh,idents.Ident2.mh);
			trigsAddr->TxTrig = TRUE;// Hour must be sent first, with old configuration
			trigsAddr->MhTrig = TRUE;
			trigsAddr->MnTrig = TRUE;
			ecuAddr->per_100ms = SYNCRATE100ms_1s;
		}

		// Synchronisation by only one valid Ecu1 //CR3027839
		else if (   (  ( (ident0Addr->mn == 0xFFFFFFFF || ident0Addr->mn == 0)// Ecu2 is missing and Ecu0 is not valid and Ecu1 is valid
			|| (ident0Addr->mt == 0xFFFF || ident0Addr->mt == 0) )
			&& (!trigsAddr->Rx1TooSlowTrig)
			&& (trigsAddr->Rx2TooSlowTrig)
			&& (idents.Ident1.mn != 0xFFFFFFFF && idents.Ident1.mt != 0xFFFF)
			&& (idents.Ident1.mn != 0 && idents.Ident1.mt != 0)
			&& (idents.Ident1.mh != 0xFFFFFFFF) )
			|| (  ( (ident0Addr->mn == 0xFFFFFFFF || ident0Addr->mn == 0)// Ecu2 is present and is not valid
			|| (ident0Addr->mt == 0xFFFF || ident0Addr->mt == 0) )
			&& ( (idents.Ident2.mn == 0xFFFFFFFF || idents.Ident2.mn == 0)
			|| (idents.Ident2.mt == 0xFFFF || idents.Ident2.mt == 0) )
			&& (!trigsAddr->Rx1TooSlowTrig && !trigsAddr->Rx2TooSlowTrig)
			&& (idents.Ident1.mn != 0xFFFFFFFF && idents.Ident1.mt != 0xFFFF)
			&& (idents.Ident1.mn != 0 && idents.Ident1.mt != 0)
			&& (idents.Ident1.mh != 0xFFFFFFFF) )  )
		{
			ecuAddr->per_100ms =SYNCRATE100ms_1s;
			if (ident0Addr->mh > idents.Ident1.mh){
				ident0Addr->mh = idents.Ident1.mh;
				trigsAddr->MhTrig = TRUE;
			}
			ident0Addr->mn = idents.Ident1.mn;
			ident0Addr->mt = idents.Ident1.mt;
			trigsAddr->MnTrig = TRUE;
		}

		// Synchronisation by only one valid Ecu2//CR3027839
		else if (   (  ( (ident0Addr->mn == 0xFFFFFFFF || ident0Addr->mn == 0)// Ecu1 is missing and Ecu0 is not valid and Ecu2 is valid
			|| (ident0Addr->mt == 0xFFFF || ident0Addr->mt == 0) )
			&& (!trigsAddr->Rx2TooSlowTrig)
			&& (trigsAddr->Rx1TooSlowTrig)
			&& (idents.Ident2.mn != 0xFFFFFFFF && idents.Ident2.mt != 0xFFFF)
			&& (idents.Ident2.mn != 0 && idents.Ident2.mt != 0)
			&& (idents.Ident2.mh != 0xFFFFFFFF))
			|| (((ident0Addr->mn == 0xFFFFFFFF || ident0Addr->mn == 0)// Ecu1 is present and is not valid
			|| (ident0Addr->mt == 0xFFFF || ident0Addr->mt == 0))
			&& ((idents.Ident1.mn == 0xFFFFFFFF || idents.Ident1.mn == 0)
			|| (idents.Ident1.mt == 0xFFFF || idents.Ident1.mt == 0))
			&& (!trigsAddr->Rx2TooSlowTrig && !trigsAddr->Rx1TooSlowTrig)
			&& (idents.Ident2.mn != 0xFFFFFFFF && idents.Ident2.mt != 0xFFFF)
			&& (idents.Ident2.mn != 0 && idents.Ident2.mt != 0)
			&& (idents.Ident2.mh != 0xFFFFFFFF) )  )
		{
			ecuAddr->per_100ms =SYNCRATE100ms_1s;
			if (ident0Addr->mh > idents.Ident2.mh){
				ident0Addr->mh = idents.Ident2.mh;
				trigsAddr->MhTrig=TRUE;
			}
			ident0Addr->mn = idents.Ident2.mn;
			ident0Addr->mt = idents.Ident2.mt;
			trigsAddr->MnTrig=TRUE;
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
	else {
		ecuAddr->per_100ms = UNSYNCRATE100ms_2s;
	}
}

void DhoCall_100ms_Diag_Ecu(EcuStruct* ecuAddr,DhoTrigs* trigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	ecuAddr->cc_100ms++;
	if ( (ecuAddr->per_100ms != 0) && ((ecuAddr->cc_100ms % ecuAddr->per_100ms) == 0) ) {
		trigsAddr->TxTrig=TRUE;
	}
	if (trigsAddr->Rx1Trig){
		trigsAddr->Rx1Trig=FALSE;
		trigsAddr->Rx1TooSlowTrig=FALSE;
		if (ecuAddr->paramCheckCfg){
			if (ecuAddr->cc1_100ms >= READYTOSTARTRATE100ms_2sBelow){
				trigsAddr->Rx1Slow= FALSE;
				ecuAddr->counterDebounce1 = 0;
			} else if (ecuAddr->cc1_100ms >= SLOWRATE100ms_1500msBelow) {
				if (ecuAddr->counterDebounce1 < DEBOUNCE_3x) {
					ecuAddr->counterDebounce1++;
				} else {
					trigsAddr->Rx1Slow = TRUE;
				}
			}
		}
		ecuAddr->cc1_100ms=0;
	}
	else if (ecuAddr->cc1_100ms >= TIMEOUT100ms_5S){
		trigsAddr->Rx1TooSlowTrig=TRUE;
	}
	else{
		ecuAddr->cc1_100ms++;
	}

	if (trigsAddr->Rx2Trig){
		trigsAddr->Rx2Trig=FALSE;
		ecuAddr->cc2_100ms=0;
	}
	else if (ecuAddr->cc2_100ms >= TIMEOUT100ms_5S){
		trigsAddr->Rx2TooSlowTrig=TRUE;
	}
	else{
		ecuAddr->cc2_100ms++;
	}
	// Synchronisation by Ecu1 (ie. FUM synchronised by VBM)
	if ( (ecuAddr->paramCheckCfg) && (trigsAddr->Rx1Slow && trigsAddr->RxId1Trig)
			&& (idents.Ident1.mn != 0xFFFFFFFF) && (idents.Ident1.mt != 0xFFFF) && (idents.Ident1.mh != 0xFFFFFFFF)
			&& (idents.Ident1.mn != 0) && (idents.Ident1.mt != 0) && (idents.Ident1.mh != 0) )
	{//CR3027839
		if ( (idents.Ident1.mn == ecuAddr->ResetMnCfg) && (idents.Ident1.mt == ecuAddr->ResetMtCfg) ){
			ident0Addr->mh=0;
			ident0Addr->mn=0;
			ident0Addr->mt=0;
		}
		else if ( (idents.Ident1.mn != 0xFFFFFFFD) && (idents.Ident1.mt != 0xFFFD) && (idents.Ident1.mn != 0xFFFFFFFE) && (idents.Ident1.mt != 0xFFFE) ){
			ident0Addr->mh=idents.Ident1.mh;
			ident0Addr->mn=idents.Ident1.mn;
			ident0Addr->mt=idents.Ident1.mt;
		}
		trigsAddr->MhTrig = TRUE;
		trigsAddr->MnTrig = TRUE;
		trigsAddr->RxId1Trig = FALSE;
	}

	// Synchronisation active (ie. VBM)
	if (ecuAddr->diagTrigCfg && trigsAddr->DiagTrig){
		ecuAddr->per_100ms = SLOWRATE100ms_1500ms;
	}
	else{
		ecuAddr->per_100ms = READYTOSTARTRATE100ms_2s;
	}
}

void DhoCall_100ms_Vbm(DhoTrigs* rxTrigsAddr, DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Ecu(&ecu_Vbm,rxTrigsAddr,ident0Addr,idents);
}
void DhoCall_100ms_FumLim(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Ecu(&ecu_Fum,rxTrigsAddr,ident0Addr,idents);
}
void DhoCall_100ms_Lim(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Ecu(&ecu_Lim,rxTrigsAddr,ident0Addr,idents);
}

void DhoCall_100ms_Diag_Vbm(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Diag_Ecu(&ecu_Vbm,rxTrigsAddr,ident0Addr,idents);
}
void DhoCall_100ms_Diag_FumLim(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Diag_Ecu(&ecu_Fum,rxTrigsAddr,ident0Addr,idents);//ecu0 = FUM
}
void DhoCall_100ms_Diag_Lim(DhoTrigs* rxTrigsAddr,DhoIdent* ident0Addr, DhoIdents idents){
	DhoCall_100ms_Diag_Ecu(&ecu_Lim,rxTrigsAddr,ident0Addr,idents);
}


//printf("Debug DhoCore by valid Ecu2 mn : %" PRId32 "\n", ident0Addr->mn);
//printf("Debug DhoCore by valid Ecu2 mh : %" PRId32 "\n", ident0Addr->mh);
