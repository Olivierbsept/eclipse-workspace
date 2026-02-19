
#ifndef FUM_H_
#define FUM_H_

#include "xml_utils.h"
#include "rtwtypes.h"
#include <stdio.h>
#include <inttypes.h>
#include "Dho.h"
#include "TIS_modelIO.h"

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

#endif /* FUM_H_ */
