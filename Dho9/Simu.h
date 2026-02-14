
#ifndef DHO3_H_
#define DHO3_H_

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include "Can_bus.h"
#include "Can.h"

void VbmInit(void);
void FumInit(void);
void LimInit(void);

void Vbm_step50ms(void);
void Fum_step50ms(void);
void Lim_step50ms(void);

void node_receive_Fum(CAN_Message msg);
void node_send_Fum(CAN_Bus *bus, uint32_t id, unsigned char *data, unsigned char len);

void node_receive_Lim(CAN_Message msg);
void node_send_Lim(CAN_Bus *bus, uint32_t id, unsigned char *data, unsigned char len);

void node_receive_Vbm(CAN_Message msg);
void node_send_Vbm(CAN_Bus *bus, uint32_t id, unsigned char *data, unsigned char len);

void VbmSetBus(CAN_Bus *pcan_bus);
void FumSetBus(CAN_Bus *pcan_bus);
void LimSetBus(CAN_Bus *pcan_bus);

typedef enum {
    ST_ReadytoStart,
    ST_GeneratorOn
} EemStates;

uint32_t IdFumConfig = 0x100;
uint32_t IdFumHour = 0x110;
uint32_t IdVbmConfig = 0x200;
uint32_t IdVbmHour = 0x210;
uint32_t IdLimConfig = 0x300;
uint32_t IdLimHour = 0x310;
#endif /* DHO3_H_ */
