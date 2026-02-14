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
	IdentVbm ident0, ident1, ident2;
	EemStates eemState;
	bool Rx1Trig, Rx2Trig;
	bool StoreTrig;
	bool Sync1Active, Sync2Active;
	bool RxSlowTrig, RxSlowSyncTrig;
} DhoMicStruct;

typedef struct{
	IdentVbm ident0, ident1, ident2;
	EemStates eemState;
	bool RxTooSlow1, RxTooSlow2;
	bool TxTrig;
	bool Sync1Active, Sync2Active;
	bool flagDiag;
} DhoMirStruct;

#endif /* SRC_DHO_DHOCOMMUN_H_ */
