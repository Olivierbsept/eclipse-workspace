/*
 * Alarm.c
 *
 *  Created on: 5 oct. 2025
 *      Author: olivierbessettemac
 */

// Simu.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include "Rho.h"
#include "vbm.h" // pour uint16, boolean, TRUE/FALSE
#include "Rte_CtApTis.h"

#define MAX_LINE_LENGTH 256

extern Std_ReturnType DataServices_Data_RHO_Bckup_ReadData(Dcm_OpStatusType OpStatus, uint8 *MI_data0, uint8 *MI_data1, uint8 *MI_data2, uint8 *MI_data3, uint8 *MI_data4);
extern FUNC(Std_ReturnType, CtApTis_CODE) DataServices_Data_RHO_Ctrl_WriteData(P2CONST(uint8, AUTOMATIC, RTE_CTAPTIS_APPL_DATA) Data, Dcm_OpStatusType OpStatus, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_CTAPTIS_APPL_VAR) ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
extern uint8_T rx_jVbmcBrcSOverallEemState_b;
extern Phases phases;

typedef enum
{
    ReadBackup = 0,
    Confirm,
	Restore,
	IgnitionKeyOn,
	EngineRunning,
	IgnitionKeyOff,
	OvrwEnbld,
	Reset0,
	Reset1,
	Reset2
} ExternCallsEnum;

typedef struct {
    long chrono_ms;
    ExternCallsEnum extCall;
} ExtCallEntry;

#define MAX_ENTRIES 100

static ExtCallEntry entries[MAX_ENTRIES];
static int entry_count = 0;
static int current_index = 0;
static struct timeval start_time;

// Chrono en millisecondes depuis le lancement
static long getCurrentTimeInMs(void) {
    struct timeval now;
    gettimeofday(&now, NULL);
    long seconds = now.tv_sec - start_time.tv_sec;
    long usec = now.tv_usec - start_time.tv_usec;
    return (seconds * 1000L) + (usec / 1000L);
}

void ExternalCalls_Init(void) {
    FILE* file = fopen("ExternalCalls.txt", "r");
    if (!file) {
        perror("Erreur ouverture fichier");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && entry_count < MAX_ENTRIES) {
        long chrono;
        unsigned int extCall;
        if (sscanf(line, "%ld %u", &chrono, &extCall) == 2) {
            entries[entry_count].chrono_ms = chrono;
            entries[entry_count].extCall = (ExternCallsEnum) extCall;
            entry_count++;
        }
    }

    fclose(file);
    gettimeofday(&start_time, NULL);
}

void ExternalCalls_step(void) {
    if (current_index >= entry_count) {
        return; // Plus rien à envoyer
    }

    long current_time = getCurrentTimeInMs();

    // Envoyer tous les DTC prêts
    while (current_index < entry_count && entries[current_index].chrono_ms <= current_time) {
    	if (entries[current_index].extCall == IgnitionKeyOn){
    		phases.SyncDiagPhase = true;//en ReadyToStartEngine
    		phases.SyncConfigPhase = false; //en GeneratorOn
    		rx_jVbmcBrcSOverallEemState_b = EemState_ReadyToStartEngine;
    		RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_EemStates);
    	}
    	if (entries[current_index].extCall == EngineRunning){
    		phases.SyncDiagPhase = false;
    		phases.SyncConfigPhase = true;
    		rx_jVbmcBrcSOverallEemState_b = EemState_GeneratorOn;
    		RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_EemStates);
    	}
    	if (entries[current_index].extCall == ReadBackup){
    		Dcm_OpStatusType OpStatus;
    		uint8 MI_data0[10], MI_data1[10], MI_data2[10], MI_data3[10], MI_data4[1];
    		DataServices_Data_RHO_Bckup_ReadData(OpStatus, MI_data0, MI_data1, MI_data2, MI_data3, MI_data4);
    		int i;
    		printf("MI_data0 : ");
			for (i = 0; i < 10; i++)
				printf("%02X ", MI_data0[i]);
			printf("\n");

			printf("MI_data1 : ");
			for (i = 0; i < 10; i++)
				printf("%02X ", MI_data1[i]);
			printf("\n");

			printf("MI_data2 : ");
			for (i = 0; i < 10; i++)
				printf("%02X ", MI_data2[i]);
			printf("\n");

			printf("MI_data3 : ");
			for (i = 0; i < 10; i++)
				printf("%02X ", MI_data3[i]);
			printf("\n");

			printf("MI_data4 : ");
			printf("%02X ", MI_data4[0]);
			printf("\n");
    	}
    	if (entries[current_index].extCall == Confirm){
    		uint8 Data = RhoCtrlVal_Confirm;
    		Dcm_OpStatusType OpStatus;
    		Dcm_NegativeResponseCodeType ErrorCode;
    		DataServices_Data_RHO_Ctrl_WriteData(&Data, OpStatus, &ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
    	}
    	if (entries[current_index].extCall == Restore){
    		uint8 Data = RhoCtrlVal_Restore;
    		Dcm_OpStatusType OpStatus;
    		Dcm_NegativeResponseCodeType ErrorCode;
    		DataServices_Data_RHO_Ctrl_WriteData(&Data, OpStatus, &ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
    	}
    	if (entries[current_index].extCall == OvrwEnbld){
    		uint8 Data = RhoCtrlVal_OvrwEnbld;
    		Dcm_OpStatusType OpStatus;
    		Dcm_NegativeResponseCodeType ErrorCode;
    		DataServices_Data_RHO_Ctrl_WriteData(&Data, OpStatus, &ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
    		SetOvrwEnbldCfg_Fum(true);
    		SetOvrwEnbldCfg_Lim(true);
    	}
    	if (entries[current_index].extCall == Reset0){
    		uint8 Data = RhoCtrlVal_Reset0;
    		Dcm_OpStatusType OpStatus;
    		Dcm_NegativeResponseCodeType ErrorCode;
    		DataServices_Data_RHO_Ctrl_WriteData(&Data, OpStatus, &ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
    	}
    	if (entries[current_index].extCall == Reset1){
    		uint8 Data = RhoCtrlVal_Reset1;
    		Dcm_OpStatusType OpStatus;
    		Dcm_NegativeResponseCodeType ErrorCode;
    		DataServices_Data_RHO_Ctrl_WriteData(&Data, OpStatus, &ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
    	}
    	if (entries[current_index].extCall == Reset2){
    		uint8 Data = RhoCtrlVal_Reset2;
    		Dcm_OpStatusType OpStatus;
    		Dcm_NegativeResponseCodeType ErrorCode;
    		DataServices_Data_RHO_Ctrl_WriteData(&Data, OpStatus, &ErrorCode); /* PRQA S 0624, 3206 */ /* MD_Rte_0624, MD_Rte_3206 */
    	}
        current_index++;
    }
}
