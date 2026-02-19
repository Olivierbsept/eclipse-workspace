/*
 * DhoCommun.h
 *
 *  Created on: 7 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef SRC_DHO_DHOCOMMUN_H_
#define SRC_DHO_DHOCOMMUN_H_

#include <stdint.h>
#include "rtwtypes.h"

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define max2(a,b) ((a) > (b) ? (a) : (b))
#define max3(a,b,c) ((max2(a,b)) > (c) ? (max2(a,b)) : (c))

// === Structures ===
typedef struct{
	uint16_T mt;
	uint32_T mn, mh;
} DhoIdent;

typedef struct{
	boolean_T Rx1Trig,Rx2Trig,RxId1Trig,DiagTrig,TxTrig,MhTrig,MnTrig;
} DhoTrigs;

typedef struct{
	DhoIdent Ident1,Ident2;
} DhoIdents;

typedef struct{
	boolean_T SyncConfigPhase,SyncDiagPhase;
} Phases;

typedef struct{
	boolean_T DiagTrigCfg, ParamCheckCfg;
} DhoConfigs;

static const uint16_t PERIOD_MSGID100ms_5s = 50;
static const uint16_t PERIOD_MSGID100ms_3s = 30;
static const uint16_t PERIOD_STORE100ms_5s = 50;
static const uint16_t PERIOD_COUNT100ms_1s = 10;
static const uint16_t PERIOD_COUNT4ms_100ms = 25;

#endif /* SRC_DHO_DHOCOMMUN_H_ */
