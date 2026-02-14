
#include "Tis.h"
#include <stdio.h>
#include <inttypes.h>

// === Init === //
void Tis_initialize(){
	ident0.mn=getMachineNumberStorage();//ident0.mn=100;
	ident0.mt=getMachineTypeStorage();//ident0.mt=101;
	ident0.mh=getMachineHourStorage();//ident0.mh= 10000;

	idents.Ident1.mh=0xFFFFFFFF;
	idents.Ident1.mt=0xFFFF;
	idents.Ident1.mh=0xFFFFFFFF;

	idents.Ident2.mh=0xFFFFFFFF;
	idents.Ident2.mt=0xFFFF;
	idents.Ident2.mh=0xFFFFFFFF;

	phases.SyncConfigPhase=true; //en GeneratorOn
	phases.SyncDiagPhase=false; // en readyToStartEngine

	trigs.TxTrig=false;
	trigs.DiagTrig=false;

	configs.DiagTrigCfg=false;//force cfg après paramétrage
	configs.ParamCheckCfg=true;//accepte cfg si condition ok
	InitDho_Fum(configs);
}

// === Fonction principale appelée toutes les 10 ms ===
void Tis_step_50ms() {
	compteurStep50ms++;

	//From jPropA_Vbm_Config
		trigs.RxId1Trig = getFlag_jPropA_Vbm_Config();
		if (trigs.RxId1Trig){
			idents.Ident1.mn=getMachineNumberVbm();
			idents.Ident1.mt=getMachineTypeVbm();
			setFlagReset_jPropA_Vbm_Config(false);
		}

	//From jVhbcBrc_VehicleHours
		trigs.Rx1Trig = getFlag_jVhbcBrc_VehicleHours();
		if (trigs.Rx1Trig){
			idents.Ident1.mh= getMachineHourVbm();
			setFlagReset_jVhbcBrc_VehicleHours(false);
		}

	//From jPropA_Lim_Config
		if (getFlag_jPropA_Lim_Config()){
			idents.Ident2.mn=getMachineNumberLim();
			idents.Ident2.mt=getMachineTypeLim();
			setFlagReset_jPropA_Lim_Config(false);
		}

	//From jPropA_Lim_TotalCounterHours
		trigs.Rx2Trig = getFlag_jPropA_Lim_TotalCounterHours();
		if (trigs.Rx2Trig){
			idents.Ident2.mh= getMachineHourLim();
			setFlagReset_jPropA_Lim_TotalCounterHours(false);
		}
	//
    if (compteurStep50ms % PERIOD_COUNT50ms_1s == 0){
    	FumCounter++;
    	ident0.mh=FumCounter;
    }
    if (phases.SyncConfigPhase){
        Call50msDho_Fum(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	if (getTrigReset_jPropA_Fum_TotalCounterHours() == false){
            	setMachineHourFum(ident0.mh);
            	setTrig_jPropA_Fum_TotalCounterHours(true);
            	trigs.TxTrig = false;
        	}
        }
    }
    else if (phases.SyncDiagPhase){
        Call50msDho_Fum_Diag(&trigs,&ident0,idents);
        if (trigs.TxTrig){
        	if (getTrigReset_jPropA_Fum_TotalCounterHours() == false){
            	setMachineHourFum(ident0.mh);
            	setTrig_jPropA_Fum_TotalCounterHours(true);
            	trigs.TxTrig = false;
        	}
        }
    }
    else if (0 == (compteurStep50ms %PERIOD_MSGID50ms_3s)){
    	if (getTrigReset_jPropA_Fum_Config()==false){
        	setMachineHourFum(ident0.mh);
        	setTrig_jPropA_Fum_TotalCounterHours(true);
    	}
    }

	if (0 == (compteurStep50ms %PERIOD_STORE50ms_5s)){
		setMachineNumberStorage(ident0.mn);
		setMachineTypeStorage(ident0.mt);
		setMachineHourStorage(ident0.mh);
	}

	if (0 == (compteurStep50ms %PERIOD_MSGID50ms_5s)){
    	if (getTrigReset_jPropA_Fum_Config()==false){
        	setMachineTypeFum(ident0.mt);
        	setMachineNumberFum(ident0.mn);
        	setTrig_jPropA_Fum_Config(true);
    	}
	}
}

