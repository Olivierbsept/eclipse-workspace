
#include "DhoMpc.h"

void DhoMpcInit(){
	FctOnOff_InitStCh(&mpc_StCh);
	dhoMpc.RxSlow1=false; dhoMpc.checkId1=false;
	dhoMpc.RxSlow1_cc=0;
}

void DhoMpcCall(){

	dhoMpc.Inputs.ident0= dhoCore_Fum.ident0;
	dhoMpc.Inputs.ident1= dhoCore_Fum.ident1;
	dhoMpc.Inputs.RxTooSlow=dhoCore_Fum.RxTooSlow1;

	dhoMpc.Inputs.eemState=currentEemState;
	dhoMpc.Inputs.RxSlow=dhoMpc.RxSlow1;
	dhoMpc.Inputs.RxSync=dhoMpc.checkId1;
	ident0=dhoMpc.Inputs.ident0;
	ident1=dhoMpc.Inputs.ident1;

	RxSlow1 = dhoMpc.Inputs.RxSlow;
	RxTooSlow1 = dhoMpc.Inputs.RxTooSlow;
	RxSync1 = dhoMpc.Inputs.RxSync;

	cmdsOff.cmd1=ident0.mn;
	cmdsOff.cmd2=ident0.mh;
	cmdsOff.cmd3=ident0.mt;
	cmdsOn.cmd1=ident1.mn;
	cmdsOn.cmd2=ident1.mh;
	cmdsOn.cmd3=ident1.mt;
	mpc_In.Cmds_off=cmdsOff;
	mpc_In.Cmds_on=cmdsOn;
	mpc_In.Create=true;
	mpc_In.Enable=(dhoMpc.Inputs.eemState == ST_ReadytoStart);
	mpc_In.Activate=RxSlow1;
	mpc_In.Start=RxSync1;
	mpc_In.Stop=(!RxSlow1);
	mpc_In.Fail=(mn1 == 0xFFFFFFFF || mh1 == 0xFFFFFFFF || mt1 == 0xFFFF || RxTooSlow1);
	FctOnOff_Update(&mpc_In, &mpc_Out, &mpc_StCh);
	dhoMpc.Outputs.CmdsStateOn=mpc_Out.CmdsStateOn;
	dhoMpc.Outputs.ident.mn=mpc_Out.Cmds.cmd1;
	dhoMpc.Outputs.ident.mh=mpc_Out.Cmds.cmd2;
	dhoMpc.Outputs.ident.mt=mpc_Out.Cmds.cmd3;
	dhoMpc.Outputs.State = mpc_StCh.StateCurrent->Name;
}

Ident DhoMergeMpc(){
	Ident identMerge;
	if (dhoMpc.Outputs.CmdsStateOn){
		identMerge = dhoMpc.Outputs.ident;
	}
	else{
		identMerge = dhoCore_Fum.Outputs.ident;
	}
	return identMerge;
}

