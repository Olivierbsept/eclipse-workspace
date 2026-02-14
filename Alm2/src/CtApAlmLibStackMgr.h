#ifndef CTAPALMLIBSTACKMGR_H
#define CTAPALMLIBSTACKMGR_H
//#include "Rte_Type.h"
#include "vbm.h"
#define MAX_ACTIVE_DTC_TEST					 8
#define MAX_ACTIVE_DTC_SERIAL				32
#define MAX_ACTIVE_DTC						MAX_ACTIVE_DTC_SERIAL
#if MAX_ACTIVE_DTC <= MAX_ACTIVE_DTC_TEST
#pragma message ( "WARNING: DTC list size is reduced to tests purpose. If you see this message for serial version modify the MAX_ACTIVE_DTC macro from MAX_ACTIVE_DTC_TEST to MAX_ACTIVE_DTC_SERIAL" )
#endif

typedef uint16 value_t;
typedef struct {
	uint16 dtcs[MAX_ACTIVE_DTC];
	sint8 cnt;
} T_StackDtcs;

typedef struct {
	value_t *a;
	size_t q, r, p, b, c, r1, b1, c1;
} T_State;
static void smoothsort(value_t *a, size_t n);
void up(size_t *a, size_t *b);
void down(size_t *a, size_t *b);
void swap(value_t *a, value_t *b);
int cmp(value_t a, value_t b);
static void sift(T_State *s);

extern boolean initDtcStack_NoMutex(T_StackDtcs *stack);
extern boolean addDtcInStack_NoMutex(T_StackDtcs *stack, const uint16 dtcId);
extern boolean delDtcFromStack_NoMutex(T_StackDtcs *stack, const uint16 dtcId);
extern boolean findDtc_NoMutex(const T_StackDtcs *stack, const uint16 dtcId);
extern sint8 getDtcNb_NoMutex(const T_StackDtcs *stack);
#endif // CTAPALMLIBSTACKMGR_H
