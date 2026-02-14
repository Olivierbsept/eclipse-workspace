#ifndef VBM_H_
#define VBM_H_

#include "DhoCommun.h"
#include "TIS_modelIO.h"

// === Variables globales définies dans Dho.c===
extern char* filename_Fum;
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);

// === Variables globales définies dans DhoCore.c===
extern void Call50msDho_Fum(Trigs* rxTrigs,IdentEcu* ident0Addr, Idents idents);
extern void Call50msDho_Fum_Diag(Trigs* rxTrigs,IdentEcu* ident0Addr, Idents idents);
extern void InitDho_Fum(Configs configs);

extern void Tis_initialize(void);
extern void Tis_step_50ms(void);
extern void Tis_terminate(void);

// === Variables globales privées ===
static uint32_t compteurStep50ms = 0;
static IdentEcu ident0;
static Trigs trigs;
static Idents idents;
static Phases phases;
static uint32_t FumCounter;
static Configs configs;

#endif /* VBM_H_ */
