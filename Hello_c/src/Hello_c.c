/*
 ============================================================================
 Name        : Hello_c.c
 Author      : OB
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcRec.h"

int CfgTbm2 =1;
int SpdIn =2;
int SpdSecIn =5;
int ignitionKey=1;
int parklock=0;

#define MAX(i,j) (((i)>(j))? (i):(j))

enum ST_OnOff{
	ST_OFF,
	ST_ON,
	ST_ERROR,
	ST_NA
};

struct State {
	char* Name;
	struct State *StatePrev;
	struct State *StateFollw;
	struct State *StateFail;
	bool (*condPrev)(void);
	bool (*condFollw)(void);
	bool (*condFail)(void);
	int (*SpdMrg)(int,int);
};
struct StateChart{
	char* Name;
	struct State *StateFirst;
	struct State *StateCurrent;
};

typedef struct {
	int count;
} CountStruct;

static bool nope(void);
static bool create(void);
static bool activate(void);
static bool deactivate(void);
static bool start(void);
static bool stop(void);
static bool misuse(void);
static bool demisuse(void);
static bool endofmisuse(void);
static bool fail(void);
static bool recover(void);
static int SpdMrg1(int SpdIn, int SpdSecIn);
static int SpdMrg2(int SpdIn, int SpdSecIn);
static int SpdMrg3(int SpdIn, int SpdSecIn);
static void updateState (struct StateChart *StCh);
static void Increment(CountStruct*);

CountStruct countStruct = {2};

int count=1;

int main(void) {
	//puts("!!!Hello World in c!!!");
	static struct State Absent;
	static struct State Passive;
	static struct State Off;
	static struct State On;
	static struct State ErrorUser;
	static struct State ErrorSystem;

	static struct StateChart FctOnOff;
	FctOnOff.StateFirst = &Absent;

	Absent.Name = "Absent";
	Absent.condFollw= &create;
	Absent.StateFollw= &Passive;
	Absent.condPrev= &nope;
	Absent.condFail= &nope;
	Absent.SpdMrg = &SpdMrg1;

	Passive.Name = "Passive";
	Passive.condFollw= &activate;
	Passive.StateFollw= &Off;
	Passive.condPrev= &nope;
	Passive.condFail=&fail;
	Passive.StateFail=&ErrorSystem;
	Passive.SpdMrg = &SpdMrg1;

	Off.Name = "Off";
	Off.condFollw= &start;
	Off.StateFollw= &On;
	Off.condPrev=&deactivate;
	Off.StatePrev= &Passive;
	Off.condFail=&fail;
	Off.StateFail=&ErrorSystem;
	Off.SpdMrg = &SpdMrg1;

	On.Name = "On";
	On.condFollw= &misuse;
	On.StateFollw= &ErrorUser;
	On.condPrev= &stop;
	On.StatePrev= &Off;
	On.condFail=&fail;
	On.StateFail=&ErrorSystem;
	On.SpdMrg = &SpdMrg2;

	ErrorUser.Name = "ErrorUser";
	ErrorUser.condFollw= &endofmisuse;
	ErrorUser.StateFollw= &Passive;
	ErrorUser.condPrev= &demisuse;
	ErrorUser.StatePrev= &On;
	ErrorUser.condFail=&fail;
	ErrorUser.StateFail=&ErrorSystem;
	ErrorUser.SpdMrg = &SpdMrg3;

	ErrorSystem.Name = "ErrorSystem";
	ErrorSystem.condFollw= &recover;
	ErrorSystem.StateFollw= &Passive;
	ErrorSystem.condPrev= &nope;
	ErrorSystem.condFail=&nope;
	ErrorSystem.SpdMrg = &SpdMrg3;

	struct State StateCurrent = *FctOnOff.StateFirst;
	FctOnOff.StateCurrent = &StateCurrent;
	printf("%s\n",StateCurrent.Name);

	updateState(&FctOnOff);//passive
	updateState(&FctOnOff);//off
	updateState(&FctOnOff);//on
	ignitionKey=0;
	updateState(&FctOnOff);//erroruser
	//ignitionKey=1;
	SpdIn =0xFF00;
	updateState(&FctOnOff);//retour on

	SpdIn=0;
	updateState(&FctOnOff);//retour off
	ignitionKey=0;
	updateState(&FctOnOff);//retour passive


	return 0;//EXIT_SUCCESS;
}

static void updateState(struct StateChart *StCh){
	struct State StateCurrent = *StCh->StateCurrent;
	if (StateCurrent.condFail()==1){
			StateCurrent= *StateCurrent.StateFail;
			*StCh->StateCurrent =StateCurrent;
	}
	else if (StateCurrent.condPrev()==1){
		StateCurrent= *StateCurrent.StatePrev;
		*StCh->StateCurrent =StateCurrent;
	}
	else if (StateCurrent.condFollw()==1){
		//puts("!!!Hello World in c!!!");
		StateCurrent= *StateCurrent.StateFollw;
		*StCh->StateCurrent =StateCurrent;
	}
	printf("%s\n",StateCurrent.Name);
	printf("Spd : %i\n",StateCurrent.SpdMrg(SpdIn,SpdSecIn));
	Increment (&countStruct);
	printf("Count: %i\n",countStruct.count);
}

static bool nope(){
	return false;
}
static bool create(){
	if (CfgTbm2 == 1) return true; else return false;
}
static bool activate(){
	if (ignitionKey == 1) return true; else return false;
}
static bool deactivate(){
	if (ignitionKey == 0) return true; else return false;
}
static bool start(){
	if (SpdIn > 1) return true; else return false;
}
static bool stop(){
	if (SpdIn <= 1) return true; else return false;
}
static bool fail(){
	if (SpdIn > 0xFEFF)return true; else return false;
}
static bool recover(){
	if (SpdIn < 0xFAFF)return true; else return false;
}
static bool misuse(){
	if (ignitionKey == 0) return true; else return false;
}
static bool demisuse(){
	if (ignitionKey == 1) return true; else return false;
}
static bool endofmisuse(){
	if (parklock == 1) return true; else return false;
}
static int SpdMrg1(int SpdIn,int SpdSecIn){
	return 0;
}
static int SpdMrg2(int SpdIn,int SpdSecIn){
	int res=0;
	if ((SpdIn-SpdSecIn)*(SpdIn-SpdSecIn) > 25) res= 0xFEFF;
	else res = MAX(SpdIn,SpdSecIn);
	return res;
}
static int SpdMrg3(int SpdIn,int SpdSecIn){
	return 2;
}
static void Increment(CountStruct* CountStructAdres){
	(*CountStructAdres).count++;
}

