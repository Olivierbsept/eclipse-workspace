
#include "Tis.h"
#include <stdio.h>
#include <inttypes.h>

// === Init === //
void Tis_initialize(){
	//ident0 = (DhoIdent) { getMachineTypeStorage(),getMachineNumberStorage(),getMachineHourStorage() };
	ident0.mh=getMachineHourStorage();
	ident0.mn=getMachineNumberStorage();
	ident0.mt=getMachineTypeStorage();
	//idents = (DhoIdents){ (DhoIdent) { 0xFFFF, 0xFFFFFFFF, 0xFFFFFFFF }, (DhoIdent) { 0xFFFF, 0xFFFFFFFF, 0xFFFFFFFF } };
	idents.Ident1.mh=0xFFFFFFFF;
	idents.Ident1.mn=0xFFFFFFFF;
	idents.Ident1.mt=0xFFFF;
	idents.Ident2.mh=0xFFFFFFFF;
	idents.Ident2.mn=0xFFFFFFFF;
	idents.Ident2.mt=0xFFFF;
	//trigs = (DhoTrigs){ false, false, false, false, false, false, false };
	trigs.DiagTrig=false;
	trigs.MhTrig=false;
	trigs.MnTrig=false;
	trigs.Rx1Trig=false;
	trigs.Rx2Trig=false;
	trigs.RxId1Trig=false;
	trigs.TxTrig=false;
	configs.DiagTrigCfg = isConfigRequester(); // if true then requests to set configuration after parametrisation
	configs.ParamCheckCfg = isConfigController(); // if true then gets configuration
	InitDho(configs);
}

// === Fonction principale appelée toutes les 10 ms ===
void Tis_step_100ms() {
	compteurStep100ms++;
	eemState = (ENU_OverallEemState)getOverallEemState();

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
			DhoCall_100ms_Diag(&trigs, &ident0, idents);
		}
		else if ( (EemState_GeneratorOnHighLoad == eemState) ||
			(EemState_GeneratorOn == eemState) ){
			DhoCall_100ms(&trigs, &ident0, idents);
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
}

