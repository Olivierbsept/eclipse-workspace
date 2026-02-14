
#include "Rte_CtApTis.h"
#include "Autosar.h"

void Rte_Write_PpOutTisModuleVersion_DeModuleVersion(SG_ModuleVersion* pModuleVersion)
{
	moduleVersion.major=pModuleVersion->major;
	moduleVersion.middle=pModuleVersion->middle;
	moduleVersion.minor=pModuleVersion->minor;
}

void Rte_IrvWrite_RCtApTis_Init_Irv_StartRecvOpHours(boolean Irv_StartRecvOpHours)
{
	irv_StartRecvOpHours = Irv_StartRecvOpHours;
}
