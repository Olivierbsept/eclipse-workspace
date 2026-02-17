#ifndef VBM_H_
#define VBM_H_

#include "CtComEemEnum.h"
#include "Dho.h"
#include "TIS_modelIO.h"

// === Variables globales définies dans Tis.c===
void Tis_Step_100ms(void);

// === Variables globales définies dans DhoCore.c===
extern void DhoCall_100ms_FumLim(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoCall_100ms_Diag_FumLim(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoInit(DhoConfigs configs);
extern void Tis_initialize(void);
extern void Tis_terminate(void);

#endif /* VBM_H_ */
