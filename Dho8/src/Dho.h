
#ifndef DHO3_H_
#define DHO3_H_

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>


void VbmInit(void);
void FumInit(void);
void LimInit(void);

void Vbm_step50ms(void);
void Fum_step50ms(void);
void Lim_step50ms(void);

typedef enum {
    ST_ReadytoStart,
    ST_GeneratorOn
} EemStates;


#endif /* DHO3_H_ */
