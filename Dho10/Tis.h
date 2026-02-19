#ifndef VBM_H_
#define VBM_H_

#include "DhoCommun.h"
#include "TIS_modelIO.h"
#include "Eem.h"

// === Variables globales définies dans Tis.c===
void Tis_Step_100ms(void);

// === Variables globales définies dans DhoCore.c===
extern void DhoCall_100ms(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void DhoCall_100ms_Diag(DhoTrigs* rxTrigs,DhoIdent* ident0Addr, DhoIdents idents);
extern void InitDho(DhoConfigs configs);

extern void Tis_initialize(void);
extern void Tis_terminate(void);

// === Variables globales privées ===

static uint32_T compteurStep100ms = 0;
static DhoIdent ident0;
static DhoTrigs trigs;
static DhoIdents idents;
static DhoConfigs configs;
static ENU_OverallEemState eemState;

#endif /* VBM_H_ */
