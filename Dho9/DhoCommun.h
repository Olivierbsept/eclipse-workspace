/*
 * DhoCommun.h
 *
 *  Created on: 7 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef SRC_DHO_DHOCOMMUN_H_
#define SRC_DHO_DHOCOMMUN_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define max2(a,b) ((a) > (b) ? (a) : (b))
#define max3(a,b,c) ((max2(a,b)) > (c) ? (max2(a,b)) : (c))

// === Structures ===
typedef struct{
	uint32_t mn, mt, mh;
} IdentEcu;

typedef struct{
	bool Rx1Trig,Rx2Trig,RxId1Trig,DiagTrig,TxTrig;
} Trigs;

typedef struct{
	IdentEcu Ident1,Ident2;
} Idents;

typedef struct{
	bool SyncConfigPhase,SyncDiagPhase;
} Phases;

typedef struct{
	bool DiagTrigCfg, ParamCheckCfg;
} Configs;

static const uint16_t PERIOD_MSGID50ms_5s = 100;
static const uint16_t PERIOD_MSGID50ms_3s = 60;
static const uint16_t PERIOD_STORE50ms_5s = 100;
static const uint16_t PERIOD_COUNT50ms_1s = 20;

#endif /* SRC_DHO_DHOCOMMUN_H_ */
