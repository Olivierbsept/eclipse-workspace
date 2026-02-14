/*
 * Common.h
 *
 *  Created on: 16 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

#define max2(a,b) ((a) > (b) ? (a) : (b))
#define max3(a,b,c) (max2(max2(a,b), c))

static uint32_t cc_step1 = 0;
static uint32_t cc_step2 = 0;
static uint32_t compteurStep=0;
static bool check1 = false;
static bool check2 = false;
static bool RxFast1ForSync = false;
static bool RxFast2ForSync = false;
static bool RxTooSlow1 = false;
static bool RxTooSlow2 = false;
static bool TxSlow1 = false;
static bool TxSlow2 = false;
static bool TxFastForSync=false;

#endif /* COMMON_H_ */
