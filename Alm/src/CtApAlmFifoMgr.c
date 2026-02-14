#include <stdint.h>
#include <stdbool.h>
#include <string.h>
//#include "Rte_CtApAlm_Type.h"
#include "CtApAlmDbSources.h"
#include "CtApAlmDb.h"
#include "CtApAlmFifoMgr.h"
#include "vbm.h"

bool isFifoEmpty_NoMutex(T_AlmFifo *pFifo)
{
    return (-1 == pFifo->head_s8);
}

bool isFifoFull_NoMutex(T_AlmFifo *pFifo)
{
    bool ret_b = true;
    int i;

    for (i = 0; i < ALM_FIFO_MAX_SIZE; i++)
    {
        if (true == pFifo->Cells[i].free_b)
        {
            ret_b = false;
            break;
        }
    }

    return ret_b;
}

static void initAlmDataCell_NoMutex(T_AlmFifo *pFifo, int8_t pos, uint16_t src, Alarm_AlarmId id, Alarm_AlarmStatus status)
{
    pFifo->Cells[pos].src_u16 = src;
    pFifo->Cells[pos].Id_t = id;
    pFifo->Cells[pos].Status_t = status;
    pFifo->Cells[pos].FirstStatus_t = status;
}

static void InitAlmCell_NoMutex(T_AlmFifo *pFifo, int8_t pos)
{
    pFifo->Cells[pos].free_b = true;
    pFifo->Cells[pos].prev_s8 = -1;
    pFifo->Cells[pos].next_s8 = -1;
    initAlmDataCell_NoMutex(pFifo, pos, CTAPALMDB_MAX_SRC, CTAPALMDB_DTC_NOT_VALID, Default_AlarmStatus_NotAvailable);
}

void initAlmFifo_NoMutex(T_AlmFifo *pFifo)
{
    int8_t i;

    for (i = 0; i < ALM_FIFO_MAX_SIZE; i++)
    {
        InitAlmCell_NoMutex(pFifo, i);
    }

    pFifo->head_s8 = -1;
    pFifo->tail_s8 = -1;
    pFifo->CleanEnable_b = false;
}

void setCleanEnableFlag_NoMutex(T_AlmFifo *pFifo, bool cleanEnable)
{
    pFifo->CleanEnable_b = cleanEnable;
}

bool getCleanEnableFlag_NoMutex(T_AlmFifo *pFifo)
{
    return pFifo->CleanEnable_b;
}

static int8_t findFirstFreeAlmCell_NoMutex(T_AlmFifo *pFifo)
{
    int8_t i, ret_s8 = -1;
	
    for (i = 0; i < ALM_FIFO_MAX_SIZE; i++)	// Find first free cell in the array
    {
        if (true == pFifo->Cells[i].free_b)
        {
            ret_s8 = i;
            break;
        }
    }

    return ret_s8;
}

static bool delAlmFromFifo_NoMutex(T_AlmFifo *pFifo, int8_t pos)
{
	bool ret_b = false;

	if ((pos >= 0) && (pos < ALM_FIFO_MAX_SIZE))	// Defensive programming
	{
	    if ((pos == pFifo->head_s8) &&
	        (pos == pFifo->tail_s8))					// Only one cell in the list ...
	    {												// ... list is now empty
			pFifo->head_s8 = -1;
			pFifo->tail_s8 = -1;
	    }
	    else											// More than one cell:
	    {
	        if (pos == pFifo->head_s8)					// * first cell of the list
	        {
	            int8_t newFirstCellPos_s8 = pFifo->Cells[pos].next_s8;
	            pFifo->head_s8 = newFirstCellPos_s8;
	            pFifo->Cells[newFirstCellPos_s8].prev_s8 = -1;
	        }
	        else if (pos == pFifo->tail_s8)				// * last cell of the list
	        {
	            int8_t newLastCellPos_s8 = pFifo->Cells[pos].prev_s8;
	            pFifo->tail_s8 = newLastCellPos_s8;
	            pFifo->Cells[pFifo->tail_s8].next_s8 = -1;
	        }
	        else											// * cell in the middle of the list
	        {
	            int8_t newNextCellPos_s8 = pFifo->Cells[pos].next_s8;
	            int8_t newPrevCellPos_s8 = pFifo->Cells[pos].prev_s8;
	            pFifo->Cells[newPrevCellPos_s8].next_s8 = newNextCellPos_s8;
	            pFifo->Cells[newNextCellPos_s8].prev_s8 = newPrevCellPos_s8;
	        }
	    }
	    InitAlmCell_NoMutex(pFifo, pos);
		ret_b = true;
	}

	return ret_b;
}

static int8_t findAlmCellById_NoMutex(T_AlmFifo *pFifo, Alarm_AlarmId id)
{
    int8_t  ret_s8 = -1,
			cnt_s8 = ALM_FIFO_MAX_SIZE,					// Defensive programming
            i = pFifo->head_s8;
  
	while ((i >= 0) && (i < ALM_FIFO_MAX_SIZE) && (cnt_s8 > 0))
    {
        // Cell is already existing in the list, stop the loop
        if (id == pFifo->Cells[i].Id_t)
        {
            ret_s8 = i;
            break;
        }

        i = pFifo->Cells[i].next_s8;
        cnt_s8--;
    }

    return ret_s8;
}

static void addCellInFifo_NoMutex(T_AlmFifo *pFifo, int8_t freepos, uint16_t src, Alarm_AlarmId id, Alarm_AlarmStatus status)
{
    int8_t lastTailCellPos = pFifo->tail_s8;
    pFifo->Cells[freepos].next_s8 = -1;
    pFifo->Cells[lastTailCellPos].next_s8 = freepos;
    pFifo->Cells[freepos].prev_s8 = lastTailCellPos;
    pFifo->tail_s8 = freepos;
    pFifo->Cells[freepos].free_b = false;
    initAlmDataCell_NoMutex(pFifo, freepos, src, id, status);
}

void CopyAlmFifo_Linked(const T_AlmFifo* pSrcFifo, T_AlmFifo* pDstFifo) {
    if (pSrcFifo == NULL || pDstFifo == NULL) {
        return;
    }

    int8_t index = pSrcFifo->head_s8;
    uint16_t copied = 0;

    while (index != -1) {
        const T_AlmFifoCell* cell = &pSrcFifo->Cells[index];

        if (!cell->free_b) {
            pushAlmToAlmFifo_NoMutex(pDstFifo, cell->src_u16, cell->Id_t, cell->Status_t);
            copied++;
        }

        index = cell->next_s8;
    }

    printf("[DEBUG] Copié %u éléments de la FIFO source vers la destination.\n", copied);
}




bool pushAlmToAlmFifo_NoMutex(T_AlmFifo *pFifo, uint16_t src, Alarm_AlarmId id, Alarm_AlarmStatus status)
{
    bool ret_b = true;

    if (true == isFifoEmpty_NoMutex(pFifo))		// If FIFO is empty
    {
#define FIRST_POS 0
        pFifo->head_s8 = FIRST_POS;
        pFifo->tail_s8 = FIRST_POS;
        pFifo->Cells[FIRST_POS].free_b = false;
        initAlmDataCell_NoMutex(pFifo, FIRST_POS, src, id, status);
#undef FIRST_POS
    }
    else											// Else, FIFO is not empty
    {
		int8_t pos_s8 = findAlmCellById_NoMutex(pFifo, id);

        if (pos_s8 < 0)							// If cell doesn't exist in the FIFO
        {
            int8_t freepos_s8 = findFirstFreeAlmCell_NoMutex(pFifo);
            if (-1 != freepos_s8)						// If Free cell has been found
            {
                addCellInFifo_NoMutex(pFifo, freepos_s8, src, id, status);
            }
            else									// Else there is no Free cell, FIFO is full: retrun FALSE
            {
                ret_b = false;
            }
        }
        else									// Else, cell exist in the FIFO
        {
            if (status != pFifo->Cells[pos_s8].Status_t)		// If DTC status are different
            {
                if (true == pFifo->CleanEnable_b)				// If the FIFO is a "cleanable" one
                {
                    if (Default_AlarmStatus_AlarmOn == status)
                    {
                        pFifo->Cells[pos_s8].Status_t = Default_AlarmStatus_AlarmOn;
                    }
                    else
                    {
                        if (Default_AlarmStatus_AlarmOff == pFifo->Cells[pos_s8].FirstStatus_t)	// If first status was OFF
                        {
                            pFifo->Cells[pos_s8].Status_t = Default_AlarmStatus_AlarmOff;			// Just restore it
                        }
                        else																	// Else first status was ON (so we receive OFF)
                        {
                            ret_b = delAlmFromFifo_NoMutex(pFifo, pos_s8);							// Delete this DTC from FIFO
                        }
                    }
                }
                else										// Just add this DTC with new status in FIFO
                {
                    int8_t freepos_s8 = findFirstFreeAlmCell_NoMutex(pFifo);
                    if (-1 != freepos_s8)							// If Free cell has been found
                    {
                        addCellInFifo_NoMutex(pFifo, freepos_s8, src, id, status);
                    }
                    else										// Else Status are equal: Return FALSE
                    {
                        ret_b = false;
                    }
                }
            }
            else										// Else Status are equal: Return FALSE
            {
                ret_b = false;
            }
        }
    }

    return ret_b;
}

bool pullAlmFromAlmFifo_NoMutex(T_AlmFifo *pFifo, uint16_t *pSrc, Alarm_AlarmId *pId, Alarm_AlarmStatus *pStatus)
{
    bool ret_b = false;

    if (false == isFifoEmpty_NoMutex(pFifo))	// If FIFO is not empty
    {
        int8_t FirstCell_s8 = pFifo->head_s8;
        *pSrc = pFifo->Cells[FirstCell_s8].src_u16;
        *pId = pFifo->Cells[FirstCell_s8].Id_t;
        *pStatus = pFifo->Cells[FirstCell_s8].Status_t;
        ret_b = delAlmFromFifo_NoMutex(pFifo, FirstCell_s8);
    }

    return ret_b;
}
