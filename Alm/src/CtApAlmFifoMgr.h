
#ifndef CTAPALMFIFOMGR_H
#define CTAPALMFIFOMGR_H
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include "vbm.h"
//#include "Rte_Type.h"

#define ALM_FIFO_MAX_SIZE_TEST					 8
#define ALM_FIFO_MAX_SIZE_SERIAL				64
#define ALM_FIFO_MAX_SIZE						ALM_FIFO_MAX_SIZE_SERIAL
//#define ALM_FIFO_MAX_SIZE						ALM_FIFO_MAX_SIZE_TEST
#if ALM_FIFO_MAX_SIZE <= ALM_FIFO_MAX_SIZE_TEST
#pragma warning ( "WARNING: ALM DTC list size is reduced to tests purposes. If you see this message for serial version modify the ALM_FIFO_MAX_SIZ macro from ALM_FIFO_MAX_SIZE_TEST to ALM_FIFO_MAX_SIZE_SERIAL" )
#endif
#if ALM_FIFO_MAX_SIZE > SCHAR_MAX
#pragma error ( "ERROR: ALM_FIFO_MAX_SIZ > SCHAR_MAX" )
#endif

typedef struct {
    bool			    free_b;
    int8_t			    prev_s8;
    int8_t			    next_s8;
    uint16_t			src_u16;
  Alarm_AlarmId		Id_t;
  Alarm_AlarmStatus	Status_t;
  Alarm_AlarmStatus	FirstStatus_t;
} T_AlmFifoCell;

typedef struct {
	int8_t              head_s8;
	int8_t              tail_s8;
	bool                CleanEnable_b;
	T_AlmFifoCell Cells[ALM_FIFO_MAX_SIZE];
} T_AlmFifo;

extern void initAlmFifo_NoMutex(T_AlmFifo *pFifo);
extern void setCleanEnableFlag_NoMutex(T_AlmFifo *pFifo, bool cleanEnable);
extern bool pushAlmToAlmFifo_NoMutex(T_AlmFifo *pFifo, uint16_t src, Alarm_AlarmId id, Alarm_AlarmStatus status);
extern bool pullAlmFromAlmFifo_NoMutex(T_AlmFifo *pFifo, uint16_t *pSrc, Alarm_AlarmId *pId, Alarm_AlarmStatus *pStatus);
extern bool isFifoEmpty_NoMutex(T_AlmFifo *pFifo);
extern bool isFifoFull_NoMutex(T_AlmFifo *pFifo);
extern void CopyAlmFifo_Linked(const T_AlmFifo *pSrcFifo,T_AlmFifo *pDestFifo);
#endif // CTAPALMFIFOMGR_H
