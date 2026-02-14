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


#define max2(a,b) ((a) > (b) ? (a) : (b))
#define max3(a,b,c) ((max2(a,b)) > (c) ? (max2(a,b)) : (c))

// === Enum
typedef enum {
    ST_ReadytoStart,
    ST_GeneratorOn
} EemStates;

// === Structures ===
typedef struct{
	uint32_t mn, mh;
	uint16_t mt;
} IdentVbm;

typedef struct{
	bool Rx1Trig,Rx2Trig,RxId1Trig,DiagTrig,TxTrig;
} Trigs;

typedef struct{
	IdentVbm Ident1,Ident2;
} Idents;

typedef struct{
	bool SyncConfigPhase,SyncDiagPhase;
} Phases;

typedef struct{
	bool DiagTrigCfg, ParamCheckCfg;
} Configs;

#endif /* SRC_DHO_DHOCOMMUN_H_ */
