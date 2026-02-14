#ifndef VBM_H_
#define VBM_H_

#include "DhoCommun.h"
#include <string.h>// ✅ Ajout nécessaire pour memcpy
#include "Can.h"
#include "Can_bus.h"

#define uint8_T uint8_t
#define uint16_T uint16_t
#define uint32_T uint32_t

// === Variables globales définies dans Dho.c===
extern char* filename_Lim;
extern void Store(char* fileName, uint32_t mn, uint16_t mt, uint32_t mh);

// === Variables globales définies dans DhoCore.c===
extern void Call50msDho_Lim(Trigs* rxTrigs,IdentEcu* ident0Addr, Idents idents);
extern void Call50msDho_Lim_Diag(Trigs* rxTrigs,IdentEcu* ident0Addr, Idents idents);
extern void InitDho_Lim(Configs configs);

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
static uint32_t LimCounter;
static Configs configs;

static CAN_Bus *pcan_bus;

#endif /* VBM_H_ */
