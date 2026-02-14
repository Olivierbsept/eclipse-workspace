/*
 * Core.h
 *
 *  Created on: 22 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef FCTONOFF_H_
#define FCTONOFF_H_

#include <stdlib.h> // pour définir le pointeur nul
#include <stdbool.h>

#define max2(a,b) ((a) > (b) ? (a) : (b))

typedef enum {
	ST_ABSENT = 0,
	ST_CREATED,
	ST_ENABLED,
	ST_ACTIVATED,
    ST_OFF,
    ST_ON,
    ST_ERRORSYSTEM,
    ST_ERRORUSER
} EnumState;

typedef struct {
    uint32_t cmd1;
    uint32_t cmd2;
    uint16_t cmd3;
} Cmds;

typedef struct{
	Cmds Cmds_off;
	Cmds Cmds_on;
	bool Create;
	bool Enable;
	bool Activate;
	bool Start;
	bool Stop;
	bool Fail;
} FCTONOFF_In;

typedef struct{
	bool CmdsStateOn;
	Cmds Cmds;
} FCTONOFF_Out;

struct State {
	EnumState Name;
	struct State *StatePrev;
	struct State *StateFollw;
	struct State *StateFail;
	bool (*condPrev)(FCTONOFF_In* In);
	bool (*condFollw)(FCTONOFF_In* In);
	bool (*condFail)(FCTONOFF_In* In);
	Cmds (*Cmds)(Cmds,Cmds);
};

typedef struct {
	EnumState Name;
	struct State *StateFirst;
	struct State *StateCurrent;
} FCTONOFF_StCh;

// === Variables globales publiques ===
void FctOnOff_InitStCh(FCTONOFF_StCh* StCh);
void FctOnOff_InitStates(void);
void FctOnOff_Update(FCTONOFF_In* In, FCTONOFF_Out* Out, FCTONOFF_StCh* StCh);

bool nope(FCTONOFF_In* mhc);
bool create(FCTONOFF_In* mhc);
bool disable(FCTONOFF_In* mhc);
bool enable(FCTONOFF_In* mhc);
bool activate(FCTONOFF_In* mhc);
bool deactivate(FCTONOFF_In* mhc);
bool start(FCTONOFF_In* mhc);
bool stop(FCTONOFF_In* mhc);
bool fail(FCTONOFF_In* mhc);
bool misuse(FCTONOFF_In* mhc);
bool demisuse(FCTONOFF_In* mhc);
bool endofmisuse(FCTONOFF_In* mhc);

Cmds CmdsOff(Cmds ValsOff,Cmds ValsOn);
Cmds CmdsOn(Cmds ValsOff,Cmds ValsOn);

// === Variables globales privées===
static struct State Absent;
static struct State Create;
static struct State Enable;
static struct State Activate;
static struct State Off;
static struct State On;
static struct State ErrorUser;
static struct State ErrorSystem;
static bool StatesInitialised=false;

#endif /* FCTONOFF_H_ */
