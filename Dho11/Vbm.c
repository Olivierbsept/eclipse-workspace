
#include "Vbm.h"
#include "Rte_CtApTis.h"

static char* filename_Vbm2 = "data.xml";
static char* filename_nvm_Vbm2 = "nvm.xml";
static uint32_T compteurStep100ms = 0;

Phases phases;
uint8 ecuname;
uint32 mnl, mhl;
uint16 mtl;
uint32 mnf, mhf;
uint16 mtf;
uint32 mnv, mhv;
uint16 mtv;
uint32 mnbu, mhbu;
uint16 mtbu;


unsigned char Rte_CtApTis_PimRhoBackup[23];

// === Interfaces externes vers Vbm ===
void LimToVbmMsg(DhoIdent ident) {
	mhl = ident.mh;
	RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_LimHour);
}

void LimIdToVbmMsg(DhoIdent ident) {
	mnl=ident.mn;
	mtl=ident.mt;
	RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_LimId);
}

void sendFumToVbmMsg(uint32_t mh){
	mhf=mh;
	RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_FumHour);
}
void sendFumIdToVbmMsg(uint32_t mn, uint16_t mt){
	mnf=mn;
	mtf=mt;
	RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_FumId);
}

// === Init === //
void VbmInit(){
	mnv=10;
	mtv=11;
	mhv=300;
	mhf=0xFFFFFFFF;
	mhl=0xFFFFFFFF;
	phases.SyncConfigPhase=false;  //en GeneratorOn
	phases.SyncDiagPhase=true; //en ReadyToStartEngine

	mtf= Read_mtf(filename_nvm_Vbm2);
	mtl = Read_mtl(filename_nvm_Vbm2);
	mnf = Read_mnf(filename_nvm_Vbm2);
	mnl= Read_mnl(filename_nvm_Vbm2);

	mhbu = Read_mhbu(filename_nvm_Vbm2);
	mtbu = Read_mtbu(filename_nvm_Vbm2);
	mnbu = Read_mnbu(filename_nvm_Vbm2);
	ecuname = Read_ecuname(filename_nvm_Vbm2);
	(*RtePim_PimRhoBackup() )[0] = (uint8)(mhbu >> 24);
	(*RtePim_PimRhoBackup() )[1] = (uint8)(mhbu >> 16);
	(*RtePim_PimRhoBackup() )[2] = (uint8)(mhbu >> 8);
	(*RtePim_PimRhoBackup() )[3] = (uint8)(mhbu);
	(*RtePim_PimRhoBackup() )[4] = (uint8)(mtbu >> 8);
	(*RtePim_PimRhoBackup() )[5] = (uint8)(mtbu);
	(*RtePim_PimRhoBackup() )[6] = (uint8)(mnbu >> 24);
	(*RtePim_PimRhoBackup() )[7] = (uint8)(mnbu >> 16);
	(*RtePim_PimRhoBackup() )[8] = (uint8)(mnbu >> 8);
	(*RtePim_PimRhoBackup() )[9] = (uint8)(mnbu);
	(*RtePim_PimRhoBackup() )[10] = (uint8)(ecuname);

	(*RtePim_PimRhoBackup() )[11] = (uint8)(mtf >> 8);
	(*RtePim_PimRhoBackup() )[12] = (uint8)(mtf);
	(*RtePim_PimRhoBackup() )[13] = (uint8)(mnf >> 24);
	(*RtePim_PimRhoBackup() )[14] = (uint8)(mnf >> 16);
	(*RtePim_PimRhoBackup() )[15] = (uint8)(mnf >> 8);
	(*RtePim_PimRhoBackup() )[16] = (uint8)(mnf);

	(*RtePim_PimRhoBackup() )[17] = (uint8)(mtl >> 8);
	(*RtePim_PimRhoBackup() )[18] = (uint8)(mtl);
	(*RtePim_PimRhoBackup() )[19] = (uint8)(mnl >> 24);
	(*RtePim_PimRhoBackup() )[20] = (uint8)(mnl >> 16);
	(*RtePim_PimRhoBackup() )[21] = (uint8)(mnl >> 8);
	(*RtePim_PimRhoBackup() )[22] = (uint8)(mnl);

	RCtApTis_Init();
	RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_EemStates);
	RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_VbmId);
}

// === Fonction principale appelée toutes les 100 ms ===
void Vbm_step100ms() {
	compteurStep100ms++;
	RCtApTis_Step100ms();
	if (0 == (compteurStep100ms %PERIOD_STORE100ms_5s)){
			Store(filename_Vbm2,mnv, mtv, mhv);
	}
	if (compteurStep100ms % PERIOD_COUNT100ms_1s == 0){
	    	if (phases.SyncConfigPhase)mhv++;
	    	RCtApTis_RxEvents(Rte_ActivatingEvent_RCtApTis_RxEvents_ActReason_OpHoursCANmsg);
	}
}

