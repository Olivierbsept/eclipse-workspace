
#include "Rho.h"

static uint16 RhoNbTicks100ms = 0;
static boolean PrepareDtcC457 = FALSE;
static boolean DTC_RHO_MoreThanOneId_C457 = FALSE;
static boolean DTC_RHO_CfgOvrwrttn_C458 = FALSE;
static boolean OvrwEnbldCfg = FALSE;

extern unsigned char Rte_CtApTis_PimRhoBackup[23];

#define max(a,b)    (((a) > (b)) ? (a) : (b))

void RhoInit(RhoConfigs rhoConfigs)
{
	DTC_RHO_MoreThanOneId_C457 = FALSE;
	DTC_RHO_CfgOvrwrttn_C458 = FALSE;
	OvrwEnbldCfg = rhoConfigs.OvrwEnbldCfg;
}

void RhoCall_100ms(RhoTrigs* rhoTrigAddr)
{
	if (RhoNbTicks100ms >= RhoNbTicks100ms_10s){
		if (FALSE == DTC_RHO_MoreThanOneId_C457){
			Rte_Call_CTAPDTC_SetDtc(CTAPDTC_RHO_MoreThanOneId_C457);
			DTC_RHO_MoreThanOneId_C457 = TRUE;
		}
		RhoNbTicks100ms=0;
	}
	else if (PrepareDtcC457) {
		RhoNbTicks100ms++;
	}
	else{
		RhoNbTicks100ms=0;
	}
	if ( ( EcuVbm == (*RtePim_PimRhoBackup())[10]) || ( EcuFum == (*RtePim_PimRhoBackup())[10]) || ( EcuLim == (*RtePim_PimRhoBackup())[10]) ){
		rhoTrigAddr->MnthOvrWrttnTrig = TRUE;
		if (FALSE == DTC_RHO_CfgOvrwrttn_C458){
			Rte_Call_CTAPDTC_SetDtc(CTAPDTC_RHO_CfgOvrwrttn_C458);
			DTC_RHO_CfgOvrwrttn_C458 = TRUE;
		}
	}
	else{
		rhoTrigAddr->MnthOvrWrttnTrig = FALSE;
		if (TRUE == DTC_RHO_CfgOvrwrttn_C458){
			Rte_Call_CTAPDTC_SetDtc(CTAPDTC_RHO_CfgOvrwrttn_C458);
			DTC_RHO_CfgOvrwrttn_C458 = FALSE;
		}
	}
}
void RhoCtrl_OvrwEnbld(RhoTrigs* rhoTrigAddr, DhoIdent* ident0Addr)
{
	OvrwEnbldCfg = TRUE;
}
void RhoCtrl_Confirm(RhoTrigs* rhoTrigAddr, DhoIdent* ident0Addr, DhoIdents* identsAddr, RhoIdent* rhoIdent)
{
	Std_ReturnType retVal = E_NOT_OK;
	NvM_RequestResultType nvmResult = 0;
	if (TRUE == DTC_RHO_CfgOvrwrttn_C458){
		Rte_Call_CTAPDTC_ClrDtc(CTAPDTC_RHO_CfgOvrwrttn_C458);
		DTC_RHO_CfgOvrwrttn_C458 = FALSE;
	}
	if (OvrwEnbldCfg){
		Rte_Enter_EA_RhoBackup();
		(*RtePim_PimRhoBackup() )[10] = EcuNA;
		rhoIdent->ecuName = EcuNA;
		retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_GetErrorStatus(&nvmResult);
		if (E_OK == retVal)
		{
			if (NVM_REQ_OK == nvmResult)
			{
				retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_WriteBlock(Rte_Pim_PimRhoBackup());
			}
			else if (NVM_REQ_NV_INVALIDATED == nvmResult)
			{
				retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_RestoreBlockDefaults(Rte_Pim_PimRhoBackup());
			}
		}
		Rte_Exit_EA_RhoBackup();
		rhoTrigAddr->MnthOvrWrttnTrig = FALSE;
	}
	else{
		if ( (ident0Addr->mt == identsAddr->Ident2.mt) && (ident0Addr->mn == identsAddr->Ident2.mn)
						&& ( (identsAddr->Ident1.mt != identsAddr->Ident2.mt) || (identsAddr->Ident1.mn != identsAddr->Ident2.mn) )
						&& ( (ident0Addr->mt != 0xFFFF) && (ident0Addr->mn != 0xFFFFFFFF) )
						&& ( (ident0Addr->mt != 0) && (ident0Addr->mn != 0) )  )
		{
			identsAddr->Ident1.mt = ident0Addr->mt;
			identsAddr->Ident1.mn = ident0Addr->mn;
			identsAddr->Ident1.mh = max(ident0Addr->mh,identsAddr->Ident2.mh);
			rhoTrigAddr->MnthTrig = TRUE;
			rhoTrigAddr->MnthOvrWrttnTrig = FALSE;
		}
		else if ( (ident0Addr->mt == identsAddr->Ident1.mt) && (ident0Addr->mn == identsAddr->Ident1.mn)
				&& ( (identsAddr->Ident1.mt != identsAddr->Ident2.mt) || (identsAddr->Ident1.mn != identsAddr->Ident2.mn) )
				&& ( (ident0Addr->mt != 0xFFFF) && (ident0Addr->mn != 0xFFFFFFFF) )
				&& ( (ident0Addr->mt != 0) && (ident0Addr->mn != 0) )  )
		{
			identsAddr->Ident2.mt = ident0Addr->mt;
			identsAddr->Ident2.mn = ident0Addr->mn;
			identsAddr->Ident2.mh = max(ident0Addr->mh,identsAddr->Ident1.mh);
			rhoTrigAddr->MnthTrig = TRUE;
			rhoTrigAddr->MnthOvrWrttnTrig = FALSE;
		}
		else if ( (identsAddr->Ident1.mt == identsAddr->Ident2.mt) && (identsAddr->Ident1.mn == identsAddr->Ident2.mn)
				&& ( (ident0Addr->mt != identsAddr->Ident1.mt) || (ident0Addr->mn != identsAddr->Ident1.mn)  )
				&& ( (identsAddr->Ident1.mt != 0xFFFF) && (identsAddr->Ident1.mn != 0xFFFFFFFF) )
				&& ( (identsAddr->Ident1.mt != 0) && (identsAddr->Ident1.mn != 0) )  )
		{
			Std_ReturnType retVal = E_NOT_OK;
			NvM_RequestResultType nvmResult = 0;
			ident0Addr->mh = max(identsAddr->Ident1.mh, identsAddr->Ident2.mh);
			ident0Addr->mt = identsAddr->Ident1.mt;
			ident0Addr->mn = identsAddr->Ident1.mn;
			rhoTrigAddr->MnthTrig = TRUE;
			Rte_Enter_EA_RhoBackup();
			(*RtePim_PimRhoBackup() )[10] = 0xFF;
			rhoIdent->ecuName = EcuNA;
			retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_GetErrorStatus(&nvmResult);
			if (E_OK == retVal)
			{
				if (NVM_REQ_OK == nvmResult)
				{
					retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_WriteBlock(Rte_Pim_PimRhoBackup());
				}
				else if (NVM_REQ_NV_INVALIDATED == nvmResult)
				{
					retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_RestoreBlockDefaults(Rte_Pim_PimRhoBackup());
				}
			}
			Rte_Exit_EA_RhoBackup();

			rhoTrigAddr->MnthOvrWrttnTrig = FALSE;
		}
	}
}

void RhoCtrl_Restore(RhoTrigs* rhoTrigAddr, DhoIdent* ident0Addr, RhoIdent* rhoIdent)
{
	Std_ReturnType retVal = E_NOT_OK;
	NvM_RequestResultType nvmResult = 0;
	ident0Addr->mh = ( (*RtePim_PimRhoBackup())[0] << 24 ) + ( (*RtePim_PimRhoBackup())[1] << 16 ) + ( (*RtePim_PimRhoBackup())[2] << 8 ) + ( (*RtePim_PimRhoBackup())[3] );
	ident0Addr->mt = ( (*RtePim_PimRhoBackup())[4] << 8 ) + ( (*RtePim_PimRhoBackup())[5] );
	ident0Addr->mn = ( (*RtePim_PimRhoBackup())[6] << 24) + ( (*RtePim_PimRhoBackup())[7] << 16 ) + ( (*RtePim_PimRhoBackup())[8] << 8 ) + ( (*RtePim_PimRhoBackup())[9] );
	rhoTrigAddr->MnthTrig = TRUE;
	if (TRUE == DTC_RHO_CfgOvrwrttn_C458){
		Rte_Call_CTAPDTC_ClrDtc(CTAPDTC_RHO_CfgOvrwrttn_C458);
		DTC_RHO_CfgOvrwrttn_C458 = FALSE;
	}
	Rte_Enter_EA_RhoBackup();
	(*RtePim_PimRhoBackup() )[10] = 0xFF;
	rhoIdent->ecuName = EcuNA;
	retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_GetErrorStatus(&nvmResult);
	if (E_OK == retVal)
	{
		if (NVM_REQ_OK == nvmResult)
		{
			retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_WriteBlock(Rte_Pim_PimRhoBackup());
		}
		else if (NVM_REQ_NV_INVALIDATED == nvmResult)
		{
			retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_RestoreBlockDefaults(Rte_Pim_PimRhoBackup());
		}
	}
	Rte_Exit_EA_RhoBackup();
	rhoTrigAddr->MnthOvrWrttnTrig = FALSE;
}

Std_ReturnType RhoCallChangeId (RhoTrigs* rhoTrigs, RhoIdent rhoIdent)
{
	Std_ReturnType retVal = E_NOT_OK;
	NvM_RequestResultType nvmResult = 0;
	
	Rte_Enter_EA_RhoBackup();
	if ( (rhoIdent.ident.mn != 0xFFFFFFFF) && (rhoIdent.ident.mt != 0xFFFF) )
	{
		(*RtePim_PimRhoBackup() )[0] = (uint8)(rhoIdent.ident.mh >> 24);
		(*RtePim_PimRhoBackup() )[1] = (uint8)(rhoIdent.ident.mh >> 16);
		(*RtePim_PimRhoBackup() )[2] = (uint8)(rhoIdent.ident.mh >> 8);
		(*RtePim_PimRhoBackup() )[3] = (uint8)(rhoIdent.ident.mh);

		(*RtePim_PimRhoBackup() )[4] = (uint8)(rhoIdent.ident.mt >> 8);
		(*RtePim_PimRhoBackup() )[5] = (uint8)(rhoIdent.ident.mt);

		(*RtePim_PimRhoBackup() )[6] = (uint8)(rhoIdent.ident.mn >> 24);
		(*RtePim_PimRhoBackup() )[7] = (uint8)(rhoIdent.ident.mn >> 16);
		(*RtePim_PimRhoBackup() )[8] = (uint8)(rhoIdent.ident.mn >> 8);
		(*RtePim_PimRhoBackup() )[9] = (uint8)(rhoIdent.ident.mn);
		(*RtePim_PimRhoBackup())[10] = (uint8)rhoIdent.ecuName;

		retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_GetErrorStatus(&nvmResult);
		if (E_OK == retVal)
		{
			if (NVM_REQ_OK == nvmResult)
			{
				retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_WriteBlock(Rte_Pim_PimRhoBackup());
				if ( (rhoIdent.ecuName == EcuVbm) || (rhoIdent.ecuName == EcuFum) || (rhoIdent.ecuName == EcuLim) ){
					if (FALSE == DTC_RHO_CfgOvrwrttn_C458){
						Rte_Call_CTAPDTC_SetDtc(CTAPDTC_RHO_CfgOvrwrttn_C458);
						DTC_RHO_CfgOvrwrttn_C458 = TRUE;
					}
					rhoTrigs->MnthOvrWrttnTrig = TRUE;
				}

			}
			else if (NVM_REQ_NV_INVALIDATED == nvmResult)
			{
				retVal = Rte_Call_NvMService_AC3_SRBS_Defs_RhoBackup_RestoreBlockDefaults(Rte_Pim_PimRhoBackup());
			}
		}
	}
	Rte_Exit_EA_RhoBackup();
	return retVal;
}

void RhoCheckUniqueId (DhoTrigs dhoTrig, DhoIdent ident0, DhoIdents idents)
{
	PrepareDtcC457 = FALSE;
	//Ecu1 et Ecu2 sont présents
	if ((!dhoTrig.Rx1TooSlowTrig && !dhoTrig.Rx2TooSlowTrig)
		/*&& (idents.Ident1.mn != 0xFFFFFFFF && idents.Ident1.mt != 0xFFFF)
		&& (idents.Ident1.mn != 0 && idents.Ident1.mt != 0)
		&& (idents.Ident2.mn != 0xFFFFFFFF && idents.Ident2.mt != 0xFFFF)
		&& (idents.Ident2.mn != 0 && idents.Ident2.mt != 0)
		&& (ident0.mn != 0xFFFFFFFF && ident0.mt != 0xFFFF)
		&& (ident0.mn != 0 && ident0.mt != 0)*/
		&& (  ( (idents.Ident1.mn != idents.Ident2.mn) || (idents.Ident1.mt != idents.Ident2.mt) )
		|| ( (ident0.mn != idents.Ident1.mn) || (ident0.mt != idents.Ident1.mt) )
		|| ( (ident0.mn != idents.Ident2.mn) || (ident0.mt != idents.Ident2.mt) )  )   )
	{
		PrepareDtcC457 = TRUE;
	}
	//Ecu1 est présent, Ecu2 est absent
	else if ((dhoTrig.Rx1TooSlowTrig && !dhoTrig.Rx2TooSlowTrig)
		&& (  ( (ident0.mn != idents.Ident2.mn) || (ident0.mt != idents.Ident2.mt) )  )   )
	{
		PrepareDtcC457 = TRUE;
	}
	//Ecu2 est présent, Ecu1 est absent
	else if ((dhoTrig.Rx2TooSlowTrig && !dhoTrig.Rx1TooSlowTrig)
		&& (  ( (ident0.mn != idents.Ident1.mn) || (ident0.mt != idents.Ident1.mt) )  )   )
	{
		PrepareDtcC457 = TRUE;
	}
	// All present Ecus have same identity
	else{
		if (TRUE == DTC_RHO_MoreThanOneId_C457){
			Rte_Call_CTAPDTC_ClrDtc(CTAPDTC_RHO_MoreThanOneId_C457);
			DTC_RHO_MoreThanOneId_C457 = FALSE;
		}
	}
}
