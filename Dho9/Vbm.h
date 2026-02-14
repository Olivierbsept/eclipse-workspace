#ifndef VBM_H_
#define VBM_H_

#include "DhoCommun.h"
#include "rtwtypes.h"
#include <string.h>// ✅ Ajout nécessaire pour memcpy
#include "Can.h"
#include "Can_bus.h"

// === Variables globales définies dans Dho.c===
extern char* filename_Vbm;
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);

// === Variables globales définies dans DhoCore.c===
extern void Call50msDho_Vbm(Trigs* rxTrigs,IdentEcu* ident0Addr, Idents idents);
extern void Call50msDho_Vbm_Diag(Trigs* rxTrigs,IdentEcu* ident0Addr, Idents idents);
extern void InitDho_Vbm(Configs configs);

extern uint32_t IdFumConfig;
extern uint32_t IdFumHour;
extern uint32_t IdVbmConfig;
extern uint32_t IdVbmHour;
extern uint32_t IdLimConfig;
extern uint32_t IdLimHour;

// === Variables globales privées ===
static uint32_t compteurStep50ms = 0;
static IdentEcu ident0;
static Trigs trigs;
static Idents idents;
static Phases phases;
static uint32_t VbmCounter;
static Configs configs;
static CAN_Bus *pcan_bus;

#endif /* VBM_H_ */
