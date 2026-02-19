
#ifndef FUM_H_
#define FUM_H_

#include "TIS_modelIO.h"
#include "xml_utils.h"
#include "DhoCommun.h"
#include "rtwtypes.h"
#include <stdio.h>
#include <inttypes.h>

//#define uint8_T uint8_t
//#define uint16_T uint16_t
//#define uint32_T uint32_t

extern void Tis_initialize(void);
extern void Tis_step_100ms(void);
extern const char* filename_Fum;

void ReceiveVbmMsg(uint32_T mh);
void ReceiveLimMsg(uint32_T mh);
void ReceiveVbmIdMsg(uint32_T mn, uint16_T mt);
void ReceiveLimIdMsg(uint32_T mh, uint16_T mt);

extern void sendFumToVbmMsg(uint32_T mh);
extern void sendFumIdToVbmMsg(uint32_T mn, uint16_T mt);
extern void sendFumToLimMsg(uint32_T mh);
extern void sendFumIdToLimMsg(uint32_T mn, uint16_T mt);

static uint32_T compteurStep100ms = 0;

#endif /* FUM_H_ */
