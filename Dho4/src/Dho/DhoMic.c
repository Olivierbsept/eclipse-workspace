/*
 * DhoMic.c
 *
 *  Created on: 7 juin 2025
 *      Author: olivierbessettemac
 */

#include "DhoMic.h"
#include <stdio.h>

void DhoMicInit(){
	FctOnOff_InitStCh(&mhc1_StCh);
	FctOnOff_InitStCh(&mhc2_StCh);
	FctOnOff_InitStCh(&mcc_StCh);
	FctOnOff_InitStCh(&mpc_StCh);

	dhoMic.ident1 = (IdentVbm){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };
	dhoMic.ident2 = (IdentVbm){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };
	dhoMic.ident0 = (IdentVbm){ .mh = 1000, .mn = 10, .mt = 11 };

}

void DhoMicInit_Fum(){

	FctOnOff_InitStCh(&mhc1_StCh_Fum);
	FctOnOff_InitStCh(&mhc2_StCh_Fum);
	FctOnOff_InitStCh(&mcc_StCh_Fum);
	FctOnOff_InitStCh(&mpc_StCh_Fum);

	dhoMic_Fum.ident1 = (IdentVbm){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };
	dhoMic_Fum.ident2 = (IdentVbm){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };
	dhoMic_Fum.ident0 = (IdentVbm){ .mh = 1000, .mn = 10, .mt = 11 };
}

void DhoMicStep10ms(){
	if (dhoMic.Rx1Trig){
		cc1_step10ms=0;
		dhoMic.Rx1Trig=false;
	}
	else{
	    if (cc1_step10ms >= TIMEOUT_5S){
	    	RxTooSlow1=true;
	    }
	    else{
	    	cc1_step10ms++;
	    }
	}

	if (dhoMic.Rx2Trig){
		cc2_step10ms=0;
		dhoMic.Rx2Trig=false;
	}
	else{
	    if (cc2_step10ms >= TIMEOUT_5S){
	    	RxTooSlow2=true;
	    }
	    else{
	        cc2_step10ms++;
	    }
	}

	if (dhoMic.RxSlowTrig){
	    cc_step10ms_RxSlow=0;
	    dhoMic.RxSlowTrig=false;
	    if (cc_step10ms_RxSlow >= UNSYNCRATE_2s-THRESHRATE_100ms || cc_step10ms_RxSlow <= READYTOSTARTRATE_1s+THRESHRATE_100ms) {
	    	RxSlow1 = false;
	        counterDebounce = 0;
	    }
	    else if (cc_step10ms_RxSlow >= SLOWRATE_1500ms-THRESHRATE_100ms) {
	        if (counterDebounce < DEBOUNCE_3x) {
	            (counterDebounce)++;
	        }
	        else {
	        	RxSlow1 = true;
	        }
	    }
	}
	if (dhoMic.RxSlowSyncTrig){
		dhoMic.RxSlowSyncTrig = false;
		if (RxSlow1){
			RxSlow1Effect = true;
		}
		else {
			RxSlow1Effect = false;
		}
	}

	cmdsOff12.cmd2=dhoMic.ident0.mh;
	cmdsOff12.cmd3=dhoMic.ident0.mt;
	cmdsOn12.cmd1=dhoMic.ident1.mn;
	cmdsOn12.cmd2=max2(dhoMic.ident1.mh,dhoMic.ident2.mh);
	cmdsOn12.cmd3=dhoMic.ident1.mt;
	mcc_In.Cmds_off=cmdsOff12;
	mcc_In.Cmds_on=cmdsOn12;
	mcc_In.Create=true;
	mcc_In.Enable=(dhoMic.eemState == ST_GeneratorOn);
	mcc_In.Activate=((dhoMic.ident1.mn == dhoMic.ident2.mn) && (dhoMic.ident1.mt == dhoMic.ident2.mt));
	mcc_In.Start=((dhoMic.ident0.mn != dhoMic.ident1.mn)||(dhoMic.ident0.mt != dhoMic.ident1.mt));
	mcc_In.Stop=((dhoMic.ident0.mn == dhoMic.ident1.mn)&&(dhoMic.ident0.mt == dhoMic.ident1.mt));
	mcc_In.Fail=(dhoMic.ident1.mn == 0xFFFFFFFF || dhoMic.ident1.mh == 0xFFFFFFFF || dhoMic.ident1.mt == 0xFFFF ||  dhoMic.ident2.mh == 0xFFFFFFFF || RxTooSlow1 || RxTooSlow2);
	FctOnOff_Update(&mcc_In, &mcc_Out, &mcc_StCh);

	cmdsOff1.cmd1=dhoMic.ident0.mn;
	cmdsOff1.cmd2=dhoMic.ident0.mh;
	cmdsOff1.cmd3=dhoMic.ident0.mt;
	cmdsOn1.cmd1=dhoMic.ident0.mn;
	cmdsOn1.cmd2=max2(dhoMic.ident0.mh,dhoMic.ident1.mh);
	cmdsOn1.cmd3=dhoMic.ident0.mt;
	mhc1_In.Cmds_off=cmdsOff1;
	mhc1_In.Cmds_on=cmdsOn1;
	mhc1_In.Create=true;
	mhc1_In.Enable=(dhoMic.eemState == ST_GeneratorOn);
	mhc1_In.Activate=((dhoMic.ident0.mn == dhoMic.ident1.mn) && (dhoMic.ident0.mt == dhoMic.ident1.mt));
	mhc1_In.Start=(dhoMic.ident0.mh < dhoMic.ident1.mh-5);
	mhc1_In.Stop=(dhoMic.ident0.mh >= dhoMic.ident1.mh);
	mhc1_In.Fail=(dhoMic.ident0.mh == 0xFFFFFFFF || dhoMic.ident1.mh == 0xFFFFFFFF || dhoMic.ident0.mn == 0xFFFFFFFF || dhoMic.ident0.mt == 0xFFFF || RxTooSlow1);
	FctOnOff_Update(&mhc1_In, &mhc1_Out, &mhc1_StCh);

	cmdsOff2.cmd1=dhoMic.ident0.mn;
	cmdsOff2.cmd2=dhoMic.ident0.mh;
	cmdsOff2.cmd3=dhoMic.ident0.mt;
	cmdsOn2.cmd1=dhoMic.ident0.mn;
	cmdsOn2.cmd2=max2(dhoMic.ident0.mh,dhoMic.ident2.mh);
	cmdsOn1.cmd3=dhoMic.ident0.mt;
	mhc2_In.Cmds_off=cmdsOff2;
	mhc2_In.Cmds_on=cmdsOn2;
	mhc2_In.Create=true;
	mhc2_In.Enable=(dhoMic.eemState == ST_GeneratorOn);
	mhc2_In.Activate=((dhoMic.ident0.mn == dhoMic.ident2.mn)&& (dhoMic.ident0.mt == dhoMic.ident2.mt));
	mhc2_In.Start=(dhoMic.ident0.mh < dhoMic.ident2.mh-5);
	mhc2_In.Stop=(dhoMic.ident0.mh >= dhoMic.ident2.mh);
	mhc2_In.Fail=(dhoMic.ident0.mh == 0xFFFFFFFF|| dhoMic.ident2.mh == 0xFFFFFFFF || dhoMic.ident0.mn == 0xFFFFFFFF || dhoMic.ident0.mt == 0xFFFF || RxTooSlow2);
	FctOnOff_Update(&mhc2_In, &mhc2_Out, &mhc2_StCh);

	cmdsOff.cmd1=dhoMic.ident0.mn;
	cmdsOff.cmd2=dhoMic.ident0.mh;
	cmdsOff.cmd3=dhoMic.ident0.mt;
	cmdsOn.cmd1=dhoMic.ident1.mn;
	cmdsOn.cmd2=dhoMic.ident1.mh;
	cmdsOn.cmd3=dhoMic.ident1.mt;
	mpc_In.Cmds_off=cmdsOff;
	mpc_In.Cmds_on=cmdsOn;
	mpc_In.Create=false;
	mpc_In.Enable=(dhoMic.eemState == ST_ReadytoStart);
	mpc_In.Activate=RxSlow1;
	mpc_In.Start=RxSlow1Effect;
	mpc_In.Stop=(!RxSlow1);
	mpc_In.Fail=(dhoMic.ident1.mn == 0xFFFFFFFF || dhoMic.ident1.mh == 0xFFFFFFFF || dhoMic.ident1.mt == 0xFFFF || RxTooSlow1);
	FctOnOff_Update(&mpc_In, &mpc_Out, &mpc_StCh);

	dhoMic.ident0=DhoMergeMhc();
	dhoMic.ident0=DhoMergeMpc();

	if ( (dhoMic.ident0.mh != ident0Prv.mh) || (dhoMic.ident0.mn != ident0Prv.mn) || (dhoMic.ident0.mt != ident0Prv.mt) ){
		dhoMic.StoreTrig=true;
	}

	if (mhc1_In.Activate){
		dhoMic.Sync1Active=true;
	}
	else{
		dhoMic.Sync1Active=false;
	}
	if (mhc2_In.Activate){
		dhoMic.Sync2Active=true;
	}
	else{
		dhoMic.Sync2Active=false;
	}

	ident0Prv = dhoMic.ident0;
	/*printf("******Vbm : Mhc1 state: %d\n",mhc1_StCh.StateCurrent->Name);
	printf("Vbm : Mhc2 state: %d\n",mhc2_StCh.StateCurrent->Name);
	printf("Vbm : Mcc state: %d\n",mcc_StCh.StateCurrent->Name);
	printf("Vbm : Mpc state: %d\n",mpc_StCh.StateCurrent->Name);*/

	/*
	 * 	printf("Fum : Mpc cmd State on: %s\n", dhoMpcOutputs.CmdsStateOn ? "true" : "false");
		printf("Vbm : Mpc state: %d\n",mpc_StCh.StateCurrent->Name);
		printf("Fum : RxSlow1_cc %" PRIu32 ", cc_step1: %" PRIu32", cc_step2: %" PRIu32 "\n", RxSlow1_cc, cc_step1, cc_step2);
		printf("Mnh_Fum -> mn1: %" PRIu32 ", mh1: %" PRIu32 "\n", mn1, mh1);
		printf("********Fum : mn: %" PRIu32 ", mh: %" PRIu32", mt: %" PRIu32 "\n", mn0, mh0, mt0);
	 */
}

IdentVbm DhoMergeMhc(){
	IdentVbm identMerge;
	bool mccCmdsStateOn = mcc_Out.CmdsStateOn;
	if (mccCmdsStateOn){
		identMerge.mn = mcc_Out.Cmds.cmd1;
		identMerge.mh = mcc_Out.Cmds.cmd2;
		identMerge.mt = mcc_Out.Cmds.cmd3;
	}
	else{
		identMerge.mn = mhc1_Out.Cmds.cmd1;
		identMerge.mh = max2(mhc1_Out.Cmds.cmd2, mhc2_Out.Cmds.cmd2);
		identMerge.mt = mhc1_Out.Cmds.cmd3;
	}
	return identMerge;
}

IdentVbm DhoMergeMpc(){
	IdentVbm identMerge;
	bool mpcCmdsStateOn = mpc_Out.CmdsStateOn;
	if (mpcCmdsStateOn){
		identMerge.mn = mpc_Out.Cmds.cmd1;
		identMerge.mh = mpc_Out.Cmds.cmd2;
		identMerge.mt = mpc_Out.Cmds.cmd3;
	}
	else{
		identMerge = dhoMic.ident0;
	}
	return identMerge;
}

