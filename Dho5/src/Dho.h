
#ifndef DHO3_H_
#define DHO3_H_

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>


void VbmInit(void);
void FumInit(void);
void LimInit(void);

void Vbm_step100ms(void);
void Fum_step100ms(void);
void Lim_step100ms(void);

#endif /* DHO3_H_ */
