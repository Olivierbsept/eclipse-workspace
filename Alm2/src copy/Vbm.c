/*
 * Vbm.c
 *
 *  Created on: 4 oct. 2025
 *      Author: olivierbessettemac
 */



#include "vbm.h"

boolean Reset, RciReset;
SG_ModuleVersion ModuleVersion, DeModuleVersion;
SG_ModuleAlive AliveStatus, DeModuleAlive;
uint8 MsgCounter;
int DelayUnlockInputAlarmCnt;
boolean LockInputAlarm;
boolean LockOutputAlarm;
SG_LedsReq DeLedsReq,LedsReqPrev;
boolean DeLedsTestModeEnabled, LedsInTestMode;
SG_EemStates EemStates;
SG_Alarm DeAlarm;
SG_AlarmCnt DeAlarmCnt;

// Obtenir le chrono (en ms) depuis le premier appel
static long getCurrentTimeInMs(void) {
    static struct timeval start_time;
    static int initialized = 0;

    if (!initialized) {
        gettimeofday(&start_time, NULL);
        initialized = 1;
    }

    struct timeval now;
    gettimeofday(&now, NULL);
    long seconds = now.tv_sec - start_time.tv_sec;
    long usec    = now.tv_usec - start_time.tv_usec;

    return (seconds * 1000L) + (usec / 1000L);
}

// Dummy function
Std_ReturnType Rte_Call_PpAlmDataBaseDtcToType_LookupDtcType(uint16 Dtc, CTAPALMDB_TYPE_e* DtcType)
{
    // DUMMY LOGIC: Simule toujours une erreur par défaut
    if (DtcType != NULL)
    {
        *DtcType = CTAPALMDB_WARNING_TYPE;  // Par exemple, renvoie toujours WARNING_TYPE
        return E_OK;
    }
    return E_NOT_OK;
}

boolean Rte_IrvRead_RCtApAlmDtc_SendDtc_Irv_RciReset()
{
	return RciReset;
}
void Rte_IrvWrite_RCtApAlm_Init_Irv_RciReset(boolean Reset){
	//RciReset = Reset;
	RciReset = FALSE; //force
}
void Rte_Enter_Ex_InputAlarm(void){

}
void Rte_Exit_Ex_InputAlarm(void){

}

void Rte_Enter_Ex_OutputAlarm(void){

}
void Rte_Write_PpOutAlmModuleVersion_DeModuleVersion(const SG_ModuleVersion* pModuleVersion){
	DeModuleVersion = *pModuleVersion;
}

void Rte_IrvRead_RCtApAlm_RxEvents_Irv_AliveStatus(SG_ModuleAlive* pAlive){
	*pAlive = AliveStatus;
}
void Rte_IrvWrite_RCtApAlm_Init_Irv_AliveStatus(const SG_ModuleAlive* pAlive_Init){
	AliveStatus = *pAlive_Init;
}
void Rte_Write_PpOutAlmAlive_DeModuleAlive(const SG_ModuleAlive* pModuleAlive){
	DeModuleAlive = *pModuleAlive;
}

void Rte_Write_PpOutAlmReset_DeReset(boolean Attr){
	Reset = Attr;
}
void Rte_IrvWrite_RCtApAlm_Init_Irv_MsgCounter(uint8 Attr)
{
	MsgCounter = Attr;
}
void Rte_IrvWrite_RCtApAlm_Init_Irv_LockInputAlarm(boolean Attr){
	LockInputAlarm = Attr;
	//LockInputAlarm = FALSE;//force
}
void Rte_IrvWrite_RCtApAlm_Init_Irv_LockOutputAlarm(boolean Attr){
	//LockOutputAlarm = Attr;
	LockOutputAlarm = FALSE;//force
}
void Rte_IrvWrite_RCtApAlm_Init_Irv_DelayUnlockInputAlarmCnt(int Attr){
	DelayUnlockInputAlarmCnt = Attr;
}
void Rte_IrvWrite_RCtApAlm_Init_Irv_LedsReqPrev(const SG_LedsReq* pAttr){
	LedsReqPrev = *pAttr;
}
void Rte_Write_PpOutAlmLedsReq_DeLedsReq(const SG_LedsReq* pAttr){
	DeLedsReq = *pAttr;
}
void Rte_IrvWrite_RCtApAlm_Init_Irv_LedsInTestMode(boolean Attr){
	LedsInTestMode = Attr;
}
void Rte_Write_PpOutAlmLedsTestModeEnabled_DeLedsTestModeEnabled(boolean Attr){
	DeLedsTestModeEnabled = Attr;
}
boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_LedsInTestMode(){
	return LedsInTestMode;
}
boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_RciReset(){
	return RciReset;
}
void Rte_Read_PpInAlmLedsInTestMode_DeLedsTestMode(boolean* pAttr){
	*pAttr=DeLedsTestModeEnabled;
}
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsInTestMode(boolean Attr){
	LedsInTestMode = Attr;
}
void Rte_Read_PpInAlmEemStates_DeValues(SG_EemStates* pAttr){
	*pAttr = EemStates;
}

boolean Rte_IrvRead_RCtApAlm_RxEvents_Irv_LockInputAlarm(void){
	return LockInputAlarm;
}
sint32 Rte_IrvRead_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt(void){
	return DelayUnlockInputAlarmCnt;
}

void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_DelayUnlockInputAlarmCnt(sint32 Attr){
	DelayUnlockInputAlarmCnt = Attr;
}

void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockInputAlarm(boolean Attr){
	LockInputAlarm = Attr;
}

void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_RciReset(boolean Attr){
	RciReset = Attr;
}
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LockOutputAlarm(boolean Attr){
	LockOutputAlarm=Attr;
}
void Rte_Exit_Ex_OutputAlarm(){

}
void Rte_Enter_Ex_MsgCounter(){

}
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_MsgCounter(uint8 Attr){
	MsgCounter = Attr;
}
void Rte_Exit_Ex_MsgCounter(){

}
void Rte_Enter_Ex_LedsReq(){

}
void Rte_Exit_Ex_LedsReq(){

}
void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_LedsReqPrev(const SG_LedsReq* pAttr){
	LedsReqPrev = *pAttr;
}

void Rte_IrvWrite_RCtApAlm_RxEvents_Irv_AliveStatus(const SG_ModuleAlive* pAttr){
	AliveStatus = *pAttr;
}
void Rte_IrvRead_RCtApAlm_Step_Irv_AliveStatus(SG_ModuleAlive* pAttr){
	*pAttr = AliveStatus;

}
void Rte_IrvWrite_RCtApAlm_Step_Irv_AliveStatus(const SG_ModuleAlive* pAttr){
	AliveStatus = *pAttr;
}
boolean Rte_IrvRead_RCtApAlm_Step_Irv_RciReset(){
	return RciReset;
}
sint32 Rte_IrvRead_RCtApAlm_Step_Irv_DelayUnlockInputAlarmCnt(){
	return DelayUnlockInputAlarmCnt;
}
void Rte_IrvWrite_RCtApAlm_Step_Irv_LockInputAlarm(boolean Attr){
	LockInputAlarm = Attr;
}
void Rte_IrvWrite_RCtApAlm_Step_Irv_DelayUnlockInputAlarmCnt(sint32 Attr){
	DelayUnlockInputAlarmCnt=Attr;
}
boolean Rte_IrvRead_RCtApAlm_Step_Irv_LockInputAlarm(){
	return LockInputAlarm;
}
boolean Rte_IrvRead_RCtApAlm_Step_Irv_LockOutputAlarm(){
	return LockOutputAlarm;
}
void Rte_IrvRead_RCtApAlm_Step_Irv_LedsReqPrev(SG_LedsReq* pAttr){
	*pAttr=LedsReqPrev;
}
void Rte_IrvWrite_RCtApAlm_Step_Irv_LedsReqPrev(const SG_LedsReq* pAttr){
	LedsReqPrev=*pAttr;
}
uint8 Rte_IrvRead_RCtApAlm_Step_Irv_MsgCounter(void){
	return MsgCounter;
}
void Rte_IrvWrite_RCtApAlm_Step_Irv_MsgCounter(uint8 Attr){
	MsgCounter = Attr;
}
void Rte_Write_PpOutAlmAlarm_DeAlarm(SG_Alarm* pAttr){
	DeAlarm = *pAttr;
    if (pAttr == NULL) {
        return;
    }

    FILE* file = fopen("src/dtc.txt", "a");
    if (!file) {
        perror("Erreur ouverture dtc.txt");
        return;
    }

    long chrono_ms = getCurrentTimeInMs();

    // Format : [chrono_ms] AlarmId AlarmStatus
    fprintf(file, "%ld %u %u\n", chrono_ms, pAttr->AlarmId, pAttr->AlarmStatus);

    fclose(file);
}
void Rte_Write_PpOutAlmAlarmCnt_DeAlarmCnt(SG_AlarmCnt* pAttr){
	DeAlarmCnt=*pAttr;
}
