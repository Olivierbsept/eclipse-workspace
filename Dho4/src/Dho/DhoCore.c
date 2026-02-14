
#include "DhoCore.h"

void DhoCoreInit_Vbm(){
	FctOnOff_InitStCh(&mhc1_StCh_Vbm);
	FctOnOff_InitStCh(&mhc2_StCh_Vbm);
	FctOnOff_InitStCh(&mcc_StCh_Vbm);
	FctOnOff_InitStCh(&mhr1_StCh_Vbm);
	FctOnOff_InitStCh(&mhr2_StCh_Vbm);
	stCharts_Vbm.mcc_StCh=mcc_StCh_Vbm;
	stCharts_Vbm.mhc1_StCh=mhc1_StCh_Vbm;
	stCharts_Vbm.mhc2_StCh=mhc2_StCh_Vbm;
	stCharts_Vbm.mhr1_StCh=mhr1_StCh_Vbm;
	stCharts_Vbm.mhr2_StCh=mhr2_StCh_Vbm;
	dhoCore_Vbm.stChartsAddr=&stCharts_Vbm;
	dhoCore_Vbm.RxTooSlow1 = false; dhoCore_Vbm.RxTooSlow2 = false;

	dhoCore_Vbm.ident1 = (Ident){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };
	dhoCore_Vbm.ident2 = (Ident){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };

	dhoCore_Vbm.ident0 = (Ident){ .mh = 1000, .mn = 10, .mt = 11 };
}
void DhoCoreInit_Fum(){
	FctOnOff_InitStCh(&mhc1_StCh_Fum);
	FctOnOff_InitStCh(&mhc2_StCh_Fum);
	FctOnOff_InitStCh(&mcc_StCh_Fum);
	FctOnOff_InitStCh(&mhr1_StCh_Fum);
	FctOnOff_InitStCh(&mhr2_StCh_Fum);
	stCharts_Fum.mcc_StCh=mcc_StCh_Fum;
	stCharts_Fum.mhc1_StCh=mhc1_StCh_Fum;
	stCharts_Fum.mhc2_StCh=mhc2_StCh_Fum;
	stCharts_Fum.mhr1_StCh=mhr1_StCh_Fum;
	stCharts_Fum.mhr2_StCh=mhr2_StCh_Fum;
	dhoCore_Fum.stChartsAddr=&stCharts_Fum;
	dhoCore_Fum.RxTooSlow1 = false; dhoCore_Fum.RxTooSlow2 = false;

	dhoCore_Fum.ident1 = (Ident){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };
	dhoCore_Fum.ident2 = (Ident){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };

	dhoCore_Fum.ident0 = (Ident){ .mh = 50, .mn = 100, .mt = 101 };
}
void DhoCoreInit_Ram(){
	FctOnOff_InitStCh(&mhc1_StCh_Ram);
	FctOnOff_InitStCh(&mhc2_StCh_Ram);
	FctOnOff_InitStCh(&mcc_StCh_Ram);
	FctOnOff_InitStCh(&mhr1_StCh_Ram);
	FctOnOff_InitStCh(&mhr2_StCh_Ram);
	stCharts_Ram.mcc_StCh=mcc_StCh_Ram;
	stCharts_Ram.mhc1_StCh=mhc1_StCh_Ram;
	stCharts_Ram.mhc2_StCh=mhc2_StCh_Ram;
	stCharts_Ram.mhr1_StCh=mhr1_StCh_Ram;
	stCharts_Ram.mhr2_StCh=mhr2_StCh_Ram;
	dhoCore_Ram.stChartsAddr=&stCharts_Ram;
	dhoCore_Ram.RxTooSlow1 = false; dhoCore_Ram.RxTooSlow2 = false;

	dhoCore_Ram.ident1 = (Ident){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };
	dhoCore_Ram.ident2 = (Ident){ .mh = 0xFFFFFFFF, .mn = 0xFFFFFFFF, .mt = 0xFFFF };

	dhoCore_Ram.ident0 = (Ident){ .mh = 500, .mn = 100, .mt = 101 };
}

void DhoCoreCall_Vbm(){
	DhoCoreCall(&dhoCore_Vbm);
}
void DhoCoreCall_Fum(){
	DhoCoreCall(&dhoCore_Fum);
}
void DhoCoreCall_Ram(){
	DhoCoreCall(&dhoCore_Ram);
}
void DhoCoreCall(DhoCoreIntern* dhoCore){

    dhoCore->Inputs.eemState = currentEemState;
	dhoCore->Inputs.ident0=dhoCore->ident0;
	dhoCore->Inputs.ident1=dhoCore->ident1;
	dhoCore->Inputs.ident2=dhoCore->ident2;
	dhoCore->Inputs.RxTooSlow1=dhoCore->RxTooSlow1;
	dhoCore->Inputs.RxTooSlow2=dhoCore->RxTooSlow2;

	mn0=dhoCore->Inputs.ident0.mn;
	mh0=dhoCore->Inputs.ident0.mh;
	mt0=dhoCore->Inputs.ident0.mt;
	mn1=dhoCore->Inputs.ident1.mn;
	mh1=dhoCore->Inputs.ident1.mh;
	mt1=dhoCore->Inputs.ident1.mt;
	mn2=dhoCore->Inputs.ident2.mn;
	mh2=dhoCore->Inputs.ident2.mh;
	mt2=dhoCore->Inputs.ident2.mt;
	RxTooSlow1=dhoCore->Inputs.RxTooSlow1;
	RxTooSlow2=dhoCore->Inputs.RxTooSlow2;

	cmdsOff12.cmd2=mh0;
	cmdsOff12.cmd3=mt0;
	cmdsOn12.cmd1=mn1;
	cmdsOn12.cmd2=max2(mh1,mh2);
	cmdsOn12.cmd3=mt1;
	mcc_In.Cmds_off=cmdsOff12;
	mcc_In.Cmds_on=cmdsOn12;
	mcc_In.Create=true;
	mcc_In.Enable=(dhoCore->Inputs.eemState == ST_GeneratorOn);
	mcc_In.Activate=((mn1 == mn2) && (mt1 == mt2));
	mcc_In.Start=((mn0 != mn1)||(mt0 != mt1));
	mcc_In.Stop=((mn0 == mn1)&&(mt0 == mt1));
	mcc_In.Fail=(mn1 == 0xFFFFFFFF || mh1 == 0xFFFFFFFF || mt1 == 0xFFFF ||  mh2 == 0xFFFFFFFF || RxTooSlow1 || RxTooSlow2);
	FctOnOff_Update(&mcc_In, &mcc_Out, &dhoCore->stChartsAddr->mcc_StCh);

	cmdsOff1.cmd1=mn0;
	cmdsOff1.cmd2=mh0;
	cmdsOff1.cmd3=mt0;
	cmdsOn1.cmd1=mn0;
	cmdsOn1.cmd2=max2(mh0,mh1);
	cmdsOn1.cmd3=mt0;
	mhc1_In.Cmds_off=cmdsOff1;
	mhc1_In.Cmds_on=cmdsOn1;
	mhc1_In.Create=true;
	mhc1_In.Enable=(dhoCore->Inputs.eemState == ST_GeneratorOn);
	mhc1_In.Activate=((mn0 == mn1) && (mt0 == mt1));
	mhc1_In.Start=(mh0 != mh1);
	mhc1_In.Stop=(mh0 == mh1);
	mhc1_In.Fail=(mh0 == 0xFFFFFFFF || mh1 == 0xFFFFFFFF || mn0 == 0xFFFFFFFF || mt0 == 0xFFFF || RxTooSlow1);
	FctOnOff_Update(&mhc1_In, &mhc1_Out, &dhoCore->stChartsAddr->mhc1_StCh);

	cmdsOff2.cmd1=mn0;
	cmdsOff2.cmd2=mh0;
	cmdsOff2.cmd3=mt0;
	cmdsOn2.cmd1=mn0;
	cmdsOn2.cmd2=max2(mh0,mh2);
	cmdsOn1.cmd3=mt0;
	mhc2_In.Cmds_off=cmdsOff2;
	mhc2_In.Cmds_on=cmdsOn2;
	mhc2_In.Create=true;
	mhc2_In.Enable=(dhoCore->Inputs.eemState == ST_GeneratorOn);
	mhc2_In.Activate=((mn0 == mn2)&& (mt0 == mt2));
	mhc2_In.Start=(mh0 != mh2);
	mhc2_In.Stop=(mh0 == mh2);
	mhc2_In.Fail=(mh0 == 0xFFFFFFFF|| mh2 == 0xFFFFFFFF || mn0 == 0xFFFFFFFF || mt0 == 0xFFFF || RxTooSlow2);
	FctOnOff_Update(&mhc2_In, &mhc2_Out, &dhoCore->stChartsAddr->mhc2_StCh);

	//dhoCore->Outputs.ident=DhoMergeMhc(&mhc1_Out,&mhc2_Out, &mcc_Out);
	dhoCore->Outputs.ident=DhoMergeMhc();

	cmdsOffTx.cmd1=200;
	cmdsOffTx.cmd2=0;
	cmdsOffTx.cmd3=0;
	cmdsOnTx.cmd1=100;
	cmdsOnTx.cmd2=0;
	cmdsOnTx.cmd3=0;
	mhr1_In.Cmds_off=cmdsOffTx;
	mhr1_In.Cmds_on=cmdsOnTx;
	mhr1_In.Create=true;
	mhr1_In.Enable=(dhoCore->Inputs.eemState == ST_GeneratorOn);
	mhr1_In.Activate=((mn0 == mn1) && (mt0 == mt1));
	mhr1_In.Start=(!RxTooSlow1);
	mhr1_In.Stop=(RxTooSlow1);
	mhr1_In.Fail=((mn0 == 0xFFFFFFFF) || (mt0 == 0xFFFF) || (mh0 == 0xFFFFFFFF));
	FctOnOff_Update(&mhr1_In, &mhr1_Out, &dhoCore->stChartsAddr->mhr1_StCh);
	dhoCore->Outputs.mhr1_per=mhr1_Out.Cmds.cmd1;
	dhoCore->Outputs.mhr1OutAddr=&mhr1_Out;

	cmdsOffTx.cmd1=200;
	cmdsOffTx.cmd2=0;
	cmdsOffTx.cmd3=0;
	cmdsOnTx.cmd1=100;
	cmdsOnTx.cmd2=0;
	cmdsOnTx.cmd3=0;
	mhr2_In.Cmds_off=cmdsOffTx;
	mhr2_In.Cmds_on=cmdsOnTx;
	mhr2_In.Create=true;
	mhr2_In.Enable=(dhoCore->Inputs.eemState == ST_GeneratorOn);
	mhr2_In.Activate=((mn0 == mn2)&&(mt0 == mt2));
	mhr2_In.Start=(!RxTooSlow2);
	mhr2_In.Stop=(RxTooSlow2);
	mhr2_In.Fail=((mn0 == 0xFFFFFFFF) || (mt0 == 0xFFFF) ||(mh0 == 0xFFFFFFFF));
	FctOnOff_Update(&mhr2_In, &mhr2_Out, &dhoCore->stChartsAddr->mhr2_StCh);
	dhoCore->Outputs.mhr2_per = mhr2_Out.Cmds.cmd1;

	dhoCore->ident0 = dhoCore->Outputs.ident;
	dhoCore->per1 = dhoCore->Outputs.mhr1_per;
	dhoCore->per2 = dhoCore->Outputs.mhr2_per;
}

Ident DhoMergeMhc(){
	Ident ident;
	bool mccCmdsStateOn = mcc_Out.CmdsStateOn;
	if (mccCmdsStateOn){
		ident.mn = mcc_Out.Cmds.cmd1;
		ident.mh = mcc_Out.Cmds.cmd2;
		ident.mt = mcc_Out.Cmds.cmd3;
	}
	else{
		ident.mn = mhc1_Out.Cmds.cmd1;
		ident.mh = max2(mhc1_Out.Cmds.cmd2, mhc2_Out.Cmds.cmd2);
		ident.mt = mhc1_Out.Cmds.cmd3;
	}
	return ident;
}

/*Ident DhoMergeMhc(FCTONOFF_Out* mhc1OutAddr, FCTONOFF_Out* mhc2OutAddr, FCTONOFF_Out* mccOutAddr){
	Ident ident;
	bool mccCmdsStateOn = mccOutAddr->CmdsStateOn;
	if (mccCmdsStateOn){
		ident.mn = mccOutAddr->Cmds.cmd1;
		ident.mh = mccOutAddr->Cmds.cmd2;
		ident.mt = mccOutAddr->Cmds.cmd3;
	}
	else{
		ident.mn = mhc1OutAddr->Cmds.cmd1;
		ident.mh = max2(mhc1OutAddr->Cmds.cmd2, mhc2OutAddr->Cmds.cmd2);
		ident.mt = mhc1OutAddr->Cmds.cmd3;
	}
	return ident;
}*/
/*
printf("mhc1. cmd1: %" PRIu32 ",cmd2 %" PRIu32 ",State: %d\n",mhc1_Out.Cmds.cmd1, mhc1_Out.Cmds.cmd2, mhc1_StCh.StateCurrent->Name);
printf("mhc2. cmd1: %" PRIu32 ",cmd2 %" PRIu32", State: %d\n",mhc2_Out.Cmds.cmd1, mhc1_Out.Cmds.cmd2, mhc2_StCh.StateCurrent->Name);
printf("mcc . cmd1: %" PRIu32 ",cmd2 %" PRIu32", State: %d\n",mcc_Out.Cmds.cmd1, mcc_Out.Cmds.cmd2, mcc_StCh.StateCurrent->Name);
*/
