
#include "Tis.h"
#include <stdio.h>
#include <inttypes.h>

static DhoConfigs configs_Fum;
static uint32_T compteurStep100ms = 0;
static DhoIdent ident0;
static DhoTrigs trigs;
static DhoIdents idents;
static ENU_OverallEemState eemState;

// === Init === //
void Tis_initialize(){
	ident0.mh=getMachineHourStorage();
	ident0.mn=getMachineNumberStorage();
	ident0.mt=getMachineTypeStorage();
	idents.Ident1.mh=0xFFFFFFFF;
	idents.Ident1.mn=0xFFFFFFFF;
	idents.Ident1.mt=0xFFFF;
	idents.Ident2.mh=0xFFFFFFFF;
	idents.Ident2.mn=0xFFFFFFFF;
	idents.Ident2.mt=0xFFFF;
	trigs.DiagTrig=false;
	trigs.MhTrig=false;
	trigs.MnTrig=false;
	trigs.Rx1Trig=false;
	trigs.Rx2Trig=false;
	trigs.RxId1Trig=false;
	trigs.TxTrig=false;
	trigs.SyncAllwd=false;
	configs_Fum.DiagTrigCfg = isConfigRequester(); // if true then requests to set configuration after parametrisation
	configs_Fum.ParamCheckCfg = isConfigController(); // if true then gets configuration
	configs_Fum.ResetMnCfg = getResetMn();
	configs_Fum.ResetMtCfg = getResetMt();
	DhoInit_Fum(configs_Fum);
}

// === Fonction principale appelée toutes les 10 ms ===
void Tis_step_100ms() {
	compteurStep100ms++;
	eemState = (ENU_OverallEemState) getOverallEemState();

    if (compteurStep100ms % PERIOD_COUNT100ms_1s == 0){
    	ident0.mh=getMachineHourStorage();
    }

	//From jPropA_Vbm_Config
	trigs.RxId1Trig = getFlag_Ecu1_Config();
	if (trigs.RxId1Trig){
		idents.Ident1.mn=getMachineNumberEcu1();
		idents.Ident1.mt=getMachineTypeEcu1();
		setFlagReset_Ecu1_Config(false);
	}

	//From jVhbcBrc_VehicleHours
	trigs.Rx1Trig = getFlag_Ecu1_VehicleHours();
	if (trigs.Rx1Trig){
		idents.Ident1.mh= getMachineHourEcu1();
		setFlagReset_Ecu1_VehicleHours(false);
	}

	//From jPropA_Lim_Config
	if (getFlag_Ecu2_Config()){
		idents.Ident2.mn=getMachineNumberEcu2();
		idents.Ident2.mt=getMachineTypeEcu2();
		setFlagReset_Ecu2_Config(false);
	}

	//From jPropA_Lim_TotalCounterHours
	trigs.Rx2Trig = getFlag_Ecu2_TotalCounterHours();
	if (trigs.Rx2Trig){
		idents.Ident2.mh= getMachineHourEcu2();
		setFlagReset_Ecu2_TotalCounterHours(false);
	}

	if ( (eemState == EemState_GeneratorOnHighLoad) ||
		 (eemState == EemState_GeneratorOn) ){
		startMachineHourCount();
	}
	else{
		stopMachineHourCount();
	}

	if ( (eemState != EemState_ReadyToStartEngine) &&
		(eemState != EemState_GeneratorOnHighLoad) &&
		(eemState != EemState_GeneratorOn) ){
		if (0 == (compteurStep100ms %PERIOD_MSGID100ms_3s)){
	    	if (getTrigReset_Ecu0_Config()==false){
	        	setMachineHourEcu0(ident0.mh);
	        	setTrig_Ecu0_TotalCounterHours(true);
	    	}
		}
	}
	else{
		if (EemState_ReadyToStartEngine == eemState){
			DhoCall_100ms_Diag_FumLim(&trigs, &ident0, idents);
		}
		else if ( (EemState_GeneratorOnHighLoad == eemState) ||
			(EemState_GeneratorOn == eemState) ){
			DhoCall_100ms_FumLim(&trigs, &ident0, idents);
		}
		if (trigs.TxTrig){
        	if (getTrigReset_Ecu0_TotalCounterHours() == false){
            	setMachineHourEcu0(ident0.mh);
            	setTrig_Ecu0_TotalCounterHours(true);
            	trigs.TxTrig = false;
        	}
		}
		if (trigs.MhTrig){
			setMachineHourStorage(ident0.mh);
		}
		if (trigs.MnTrig){
			setMachineNumberStorage(ident0.mn);
			setMachineTypeStorage(ident0.mt);
		}
	}

	if (0 == (compteurStep100ms %PERIOD_MSGID100ms_5s)){
    	if (getTrigReset_Ecu0_Config()==false){
        	setMachineTypeEcu0(ident0.mt);
        	setMachineNumberEcu0(ident0.mn);
        	setTrig_Ecu0_Config(true);
    	}
	}
	if (0 == (compteurStep100ms %PERIOD_MSGID100ms_6s)){// to receive MI not synchronised from other Ecus
		trigs.SyncAllwd = true;
	}
}

//printf("Debug Tis_step100ms : trigs = %" PRId32 "\n", trigs.Rx1Slow);
