
#include "../DhoFctCommun.h"
#include "FctOnOffVbm.h"

/*bool nope(FCTONOFF_In* mhc){
	return false;
}
bool create(FCTONOFF_In* mhc){
	return mhc->Create;
}
bool disable(FCTONOFF_In* mhc){
	return !(mhc->Create);
}
bool enable(FCTONOFF_In* mhc){
	return mhc->Enable;
}
bool activate(FCTONOFF_In* mhc){
	return mhc->Activate;
}
bool deactivate(FCTONOFF_In* mhc){
	return !(mhc->Activate);
}
bool start(FCTONOFF_In* mhc){
	return mhc->Start;
}
bool stop(FCTONOFF_In* mhc){
	return mhc->Stop;
}
bool fail(FCTONOFF_In* mhc){
	return mhc->Fail;
}
bool recover(FCTONOFF_In* mhc){
	return !(mhc->Fail);
}
bool misuse(FCTONOFF_In* mhc){
	return !(mhc->Activate);
}
bool demisuse(FCTONOFF_In* mhc){
	return false;
}
bool endofmisuse(FCTONOFF_In* mhc){
	return mhc->Activate;
}

void updateState(FCTONOFF_In* In, FCTONOFF_StCh *StCh){
	struct State* StateCurrent = StCh->StateCurrent;
	if (StateCurrent->condFail(In)==1){
			StateCurrent= StateCurrent->StateFail;
			StCh->StateCurrent =StateCurrent;
	}
	else if (StateCurrent->condPrev(In)==1){
		StateCurrent= StateCurrent->StatePrev;
		StCh->StateCurrent =StateCurrent;
	}
	else if (StateCurrent->condFollw(In)==1){
		StateCurrent= StateCurrent->StateFollw;
		if (StateCurrent != NULL){
			StCh->StateCurrent =StateCurrent;
		}
	}
}
void FctOnOff_InitStates(){
	Absent.Name = ST_ABSENT;
	Absent.condPrev= &nope;
	Absent.condFollw= &create;
	Absent.StateFollw= &Create;
	Absent.condFail= &nope;
	Absent.Cmds = &CmdsOff;

	Create.Name = ST_CREATED;
	Create.condPrev= &nope;
	Create.condFollw= &enable;
	Create.StateFollw= &Enable;
	Create.condFail=&nope;
	Create.Cmds = &CmdsOff;

	Enable.Name = ST_ENABLED;
	Enable.condPrev= &disable;
	Enable.StatePrev= &Create;
	Enable.condFollw= &activate;
	Enable.StateFollw= &Activate;
	Enable.condFail=&fail;
	Enable.StateFail=&ErrorSystem;
	Enable.Cmds = &CmdsOff;

	Activate.Name = ST_ACTIVATED;
	Activate.condPrev= &deactivate;
	Activate.StatePrev= &Enable;
	Activate.condFollw= &start;
	Activate.StateFollw= &On;
	Activate.condFail=&fail;
	Activate.StateFail=&ErrorSystem;
	Activate.Cmds = &CmdsOff;

	On.Name = ST_ON;
	On.condPrev= &stop;
	On.StatePrev= &Off;
	On.condFollw= &misuse;
	On.StateFollw=&ErrorUser;
	On.condFail=&fail;
	On.StateFail=&ErrorSystem;
	On.Cmds = &CmdsOn;

	Off.Name = ST_OFF;
	Off.condFollw= &start;
	Off.StateFollw= &On;
	Off.condPrev=&deactivate;
	Off.StatePrev= &Enable;
	Off.condFail=&fail;
	Off.StateFail=&ErrorSystem;
	Off.Cmds = &CmdsOff;

	ErrorUser.Name = ST_ERRORUSER;
	ErrorUser.condFollw= &endofmisuse;
	ErrorUser.StateFollw= &Enable;
	ErrorUser.condPrev= &demisuse;
	ErrorUser.StatePrev= &On;
	ErrorUser.condFail=&fail;
	ErrorUser.StateFail=&ErrorSystem;
	ErrorUser.Cmds = &CmdsOff;

	ErrorSystem.Name = ST_ERRORSYSTEM;
	ErrorSystem.condFollw= &recover;
	ErrorSystem.StateFollw= &Enable;
	ErrorSystem.condPrev= &nope;
	ErrorSystem.condFail=&nope;
	ErrorSystem.Cmds = &CmdsOff;

	ErrorUser.Name = ST_ERRORUSER;
	ErrorUser.condFollw= &endofmisuse;
	ErrorUser.StateFollw= &Enable;
	ErrorUser.condPrev= &demisuse;
	ErrorUser.StatePrev= &On;
	ErrorUser.condFail=&fail;
	ErrorUser.StateFail=&ErrorSystem;
	ErrorUser.Cmds = &CmdsOff;
	StatesInitialised = true;
}
void FctOnOff_InitStCh(FCTONOFF_StCh* StCh){
	if (!StatesInitialised) FctOnOff_InitStates();
	StCh->StateFirst = &Absent;
	StCh->StateCurrent = StCh->StateFirst;
}

void FctOnOff_Update(FCTONOFF_In* In, FCTONOFF_Out* Out, FCTONOFF_StCh* StCh){
	updateState(In,StCh);
	Out->Cmds = StCh->StateCurrent->Cmds(In->Cmds_off,In->Cmds_on);
	if (StCh->StateCurrent->Cmds==&CmdsOn){//if (ST_ON == StCh->StateCurrent->Name){
		Out->CmdsStateOn = true;
	}
	else{
		Out->CmdsStateOn = false;
	}
	StCh->Name=StCh->StateCurrent->Name;
}

Cmds CmdsOff(Cmds ValsOff,Cmds ValsOn){
	return ValsOff;
}
Cmds CmdsOn(Cmds ValsOff,Cmds ValsOn){
	return ValsOn;
}*/

