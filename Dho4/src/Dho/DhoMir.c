/*
 * Mir.c
 *
 *  Created on: 7 juin 2025
 *      Author: olivierbessettemac
 */
#include "DhoMir.h"
#include <stdio.h>

void DhoMirInit(){
	FctOnOff_InitStCh(&mhr1_StCh);
	FctOnOff_InitStCh(&mhr2_StCh);
	FctOnOff_InitStCh(&mpr_StCh);
}

void DhoMirInit_Fum(){
	FctOnOff_InitStCh(&mhr1_StCh_Fum);
	FctOnOff_InitStCh(&mhr2_StCh_Fum);
	FctOnOff_InitStCh(&mpr_StCh_Fum);
}

void DhoMirStep10ms(){
	cmdsOffTx.cmd1=200;
	cmdsOffTx.cmd2=0;
	cmdsOffTx.cmd3=0;
	cmdsOnTx.cmd1=100;
	cmdsOnTx.cmd2=0;
	cmdsOnTx.cmd3=0;
	mhr1_In.Cmds_off=cmdsOffTx;
	mhr1_In.Cmds_on=cmdsOnTx;
	mhr1_In.Create=true;
	mhr1_In.Enable=(dhoMir.eemState == ST_GeneratorOn);
	mhr1_In.Activate=((dhoMir.ident0.mn == dhoMir.ident1.mn) && (dhoMir.ident0.mt == dhoMir.ident1.mt));
	mhr1_In.Start=(dhoMir.Sync1Active);
	mhr1_In.Stop=(!dhoMir.Sync1Active);
	mhr1_In.Fail=((dhoMir.ident0.mn == 0xFFFFFFFF) || (dhoMir.ident0.mt == 0xFFFF) || (dhoMir.ident0.mh == 0xFFFFFFFF));
	FctOnOff_Update(&mhr1_In, &mhr1_Out, &mhr1_StCh);

	cmdsOffTx.cmd1=200;
	cmdsOffTx.cmd2=0;
	cmdsOffTx.cmd3=0;
	cmdsOnTx.cmd1=100;
	cmdsOnTx.cmd2=0;
	cmdsOnTx.cmd3=0;
	mhr2_In.Cmds_off=cmdsOffTx;
	mhr2_In.Cmds_on=cmdsOnTx;
	mhr2_In.Create=true;
	mhr2_In.Enable=(dhoMir.eemState == ST_GeneratorOn);
	mhr2_In.Activate=((dhoMir.ident0.mn == dhoMir.ident2.mn)&&(dhoMir.ident0.mt == dhoMir.ident2.mt));
	mhr2_In.Start=(dhoMir.Sync2Active);
	mhr2_In.Stop=(!dhoMir.Sync1Active);
	mhr2_In.Fail=((dhoMir.ident0.mn == 0xFFFFFFFF) || (dhoMir.ident0.mt == 0xFFFF) ||(dhoMir.ident0.mh == 0xFFFFFFFF));
	FctOnOff_Update(&mhr2_In, &mhr2_Out, &mhr2_StCh);

	cmdsOffTx.cmd1=READYTOSTARTRATE_1s;
	cmdsOffTx.cmd2=0;
	cmdsOffTx.cmd3=0;
	cmdsOnTx.cmd1=SLOWRATE_1500ms;
	cmdsOnTx.cmd2=0;
	cmdsOffTx.cmd3=0;
	mpr_In.Cmds_off=cmdsOffTx;
	mpr_In.Cmds_on=cmdsOnTx;
	mpr_In.Create=true;
	mpr_In.Enable=(dhoMir.eemState == ST_ReadytoStart);
	mpr_In.Activate=(!dhoMir.RxTooSlow1);
	mpr_In.Start=(dhoMir.flagDiag);
	mpr_In.Stop=(!dhoMir.flagDiag);
	mpr_In.Fail=(dhoMir.ident0.mn == 0xFFFFFFFF || dhoMir.ident0.mh == 0xFFFFFFFF || dhoMir.ident0.mt == 0xFFFF);
	FctOnOff_Update(&mpr_In, &mpr_Out, &mpr_StCh);

	DhoMergeMhr();
	DhoMergeMpr();

	if (cc_step10ms == nbTicks_10ms){
		cc_step10ms=0;
		dhoMir.TxTrig=true;
	}
	else{
		cc_step10ms++;
		dhoMir.TxTrig=false;
	}
}

void DhoMergeMhr(){
	bool mhr1CmdsStateOn = mhr1_Out.CmdsStateOn;
	bool mhr2CmdsStateOn = mhr2_Out.CmdsStateOn;
	if (mhr1CmdsStateOn && mhr2CmdsStateOn){
		nbTicks_10ms = (mhr1_Out.Cmds.cmd1 + mhr2_Out.Cmds.cmd1)/2;
	}
	else if (mhr1CmdsStateOn){
		nbTicks_10ms = mhr1_Out.Cmds.cmd1;
	}
	else if (mhr2_Out.Cmds.cmd1){
		nbTicks_10ms = mhr2_Out.Cmds.cmd1;
	}
	else{
		nbTicks_10ms = mhr1_Out.Cmds.cmd1;
	}
}
void DhoMergeMpr(){
	bool mccCmdsStateOn = mpr_Out.CmdsStateOn;
	if (mccCmdsStateOn){
		nbTicks_10ms = mpr_Out.Cmds.cmd1;
	}
	else{
		//
	}
}

