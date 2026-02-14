/*
 * FctOnOffVbm.h
 *
 *  Created on: 7 juin 2025
 *      Author: olivierbessettemac
 */

#ifndef SRC_DHO_FCTONOFF_FCTONOFFVBM_H_
#define SRC_DHO_FCTONOFF_FCTONOFFVBM_H_
#include <stdbool.h>

// === Variables globales privées===
static struct State Absent;
static struct State Create;
static struct State Enable;
static struct State Activate;
static struct State Off;
static struct State On;
static struct State ErrorUser;
static struct State ErrorSystem;
//static bool StatesInitialised=false;

#endif /* SRC_DHO_FCTONOFF_FCTONOFFVBM_H_ */
