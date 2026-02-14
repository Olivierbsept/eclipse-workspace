
#ifndef DHO3_H_
#define DHO3_H_

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

typedef enum {
    ST_ReadytoStart,
    ST_GeneratorOn
} EemStates;

void VbmInit(void);
void FumInit(void);
void RamInit(void);

void Vbm_step10ms(void);
void Fum_step10ms(void);
void Ram_step10ms(void);

#endif /* DHO3_H_ */
