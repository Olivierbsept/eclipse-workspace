
#ifndef DHO3_H_
#define DHO3_H_

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include "CtComEemEnum.h"

void VbmInit(void);
void FumInit(void);
void LimInit(void);

extern void Vbm_step100ms(void);
extern void Fum_step100ms(void);
extern void Lim_step100ms(void);
extern void RCtApTis_Step100ms(void);

#endif /* DHO3_H_ */
