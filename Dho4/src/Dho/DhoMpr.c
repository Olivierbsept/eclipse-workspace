
#include "DhoMpr.h"

void DhoMprInit(){
	FctOnOff_InitStCh(&mpr_StCh);
}

void DhoMprCall(){
    dhoMpr.Inputs.ident = dhoCore_Vbm.ident0;
    dhoMpr.Inputs.RxTooSlow = dhoCore_Vbm.RxTooSlow1;
    dhoMpr.Inputs.eemState = currentEemState;
    dhoMpr.Inputs.flagDiag = flagDiag;
	ident=dhoMpr.Inputs.ident;
	mn0=ident.mn;
	mh0=ident.mh;
	mt0=ident.mt;
	flagDiag=dhoMpr.Inputs.flagDiag;
	RxTooSlow1=dhoMpr.Inputs.RxTooSlow;

	cmdsOffTx.cmd1=READYTOSTARTRATE_1s;
	cmdsOffTx.cmd2=0;
	cmdsOffTx.cmd3=0;
	cmdsOnTx.cmd1=SLOWRATE_1500ms;
	cmdsOnTx.cmd2=0;
	cmdsOffTx.cmd3=0;
	mpr_In.Cmds_off=cmdsOffTx;
	mpr_In.Cmds_on=cmdsOnTx;
	mpr_In.Create=true;
	mpr_In.Enable=(dhoMpr.Inputs.eemState == ST_ReadytoStart);
	mpr_In.Activate=(!RxTooSlow1);
	mpr_In.Start=(flagDiag);
	mpr_In.Stop=(!flagDiag);
	mpr_In.Fail=(mn0 == 0xFFFFFFFF || mh0 == 0xFFFFFFFF || mt0 == 0xFFFF);
	FctOnOff_Update(&mpr_In, &mpr_Out, &mpr_StCh);
	dhoMpr.Outputs.CmdsStateOn=mpr_Out.CmdsStateOn;
	dhoMpr.Outputs.mprPer=mpr_Out.Cmds.cmd1;
}

uint32_t DhoMergeMpr(){
	uint32_t per;
	if (dhoMpr.Outputs.CmdsStateOn){
		per = dhoMpr.Outputs.mprPer;
	}
	else{
		per = dhoCore_Vbm.Outputs.mhr1_per;
	}
	return per;
}
