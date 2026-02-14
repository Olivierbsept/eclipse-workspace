#include <stdio.h>
#include <stdlib.h>
#include "CtApAlmLibStackMgr.h"

typedef struct
{
	uint8 HighValue;
	uint8 MiddleValue;
	uint8 LowValue;
} T_ModuleVersion;

#define MODULE_VERSION_HIGH		0x00
#define MODULE_VERSION_MIDDLE	0x01
#define MODULE_VERSION_LOW		0x03

const T_ModuleVersion ModuleVersion = { MODULE_VERSION_HIGH, MODULE_VERSION_MIDDLE, MODULE_VERSION_LOW };

// BEGIN SMOOTH SORT ALGORITHM
// Adapted from https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Smoothsort#C

// Begin user-defined types and functions
// Type to sort
typedef uint16 value_t;

#ifdef __GNUC__
	__inline
#else
	#if _MSC_VER >= 1800
		_inline
	#else
		static
	#endif
#endif
int cmp(value_t a, value_t b)
{
	return a - b;
}
// End user-defined types and functions

/*typedef struct {
	value_t *a;
	size_t q, r, p, b, c, r1, b1, c1;
} T_State;*/

#ifdef __GNUC__
__inline
#else
	#ifdef _MSC_VER
		#if _MSC_VER >= 1800
_inline
		#else
static
		#endif
	#else
static
	#endif
#endif
void up(size_t *a, size_t *b)
{
	size_t tmp = *a;;
	*a += *b + 1;
	*b = tmp;
}

#ifdef __GNUC__
__inline
#else
	#ifdef _MSC_VER
		#if _MSC_VER >= 1800
_inline
		#else
static
		#endif
	#else
static
	#endif
#endif
void down(size_t *a, size_t *b)
{
	size_t tmp = *b;
	*b = *a - *b - 1;
	*a = tmp;
}

static void sift(T_State *s)
{
	size_t r0, r2;
	value_t tmp;

	r0 = s->r1;
	tmp = s->a[r0];

	while (s->b1 > 2)
	{
		r2 = s->r1 - s->b1 + s->c1;
		if (cmp(s->a[s->r1 - 1], s->a[r2]) >= 0)
		{
			r2 = s->r1 - 1;
			down(&s->b1, &s->c1);
		}
		if (cmp(s->a[r2], tmp) < 0)
		{
			s->b1 = 1;
		}
		else
		{
			s->a[s->r1] = s->a[r2];
			s->r1 = r2;
			down(&s->b1, &s->c1);
		}
	}
	if (s->r1 - r0 > 0)
	{
		s->a[s->r1] = tmp;
	}
}

static void trinkle(T_State *s)
{
	size_t p1, r0, r2, r3;
	value_t tmp;

	p1 = s->p;
	s->b1 = s->b;
	s->c1 = s->c;
	r0 = s->r1;
	tmp = s->a[r0];

	while (p1 > 0)
	{
		while ((p1 & 1) == 0)
		{
			p1 >>= 1;
			up(&s->b1, &s->c1);
		}
		r3 = s->r1 - s->b1;
		if (p1 == 1 || cmp(s->a[r3], tmp) < 0)
		{
			p1 = 0;
		}
		else
		{
			p1--;
			if (s->b1 == 1)
			{
				s->a[s->r1] = s->a[r3];
				s->r1 = r3;
			}
			else if (s->b1 >= 3)
			{
				r2 = s->r1 - s->b1 + s->c1;
				if (cmp(s->a[s->r1 - 1], s->a[r2]) >= 0)
				{
					r2 = s->r1 - 1;
					down(&s->b1, &s->c1);
					p1 <<= 1;
				}
				if (cmp(s->a[r2], s->a[r3]) < 0)
				{
					s->a[s->r1] = s->a[r3];
					s->r1 = r3;
				}
				else
				{
					s->a[s->r1] = s->a[r2];
					s->r1 = r2;
					down(&s->b1, &s->c1);
					p1 = 0;
				}
			}
		}
	}
	if (s->r1 - r0 != 0)
	{
		s->a[s->r1] = tmp;
	}
	sift(s);
}

static void semitrinkle(T_State *s)
{
	value_t tmp;
	s->r1 = s->r - s->c;
	if (cmp(s->a[s->r1], s->a[s->r]) >= 0)
	{
		tmp = s->a[s->r];
		s->a[s->r] = s->a[s->r1];
		s->a[s->r1] = tmp;
		trinkle(s);
	}
}

static void smoothsort(value_t *a, size_t n)
{
	T_State s;
	size_t tmp;

	s.a = a;
	s.r = 0;
	s.p = s.b = s.c = 1;

	// Build tree
	for (s.q = 1; s.q < n; s.q++)
	{
		s.r1 = s.r;
		if ((s.p & 7) == 3)
		{
			s.b1 = s.b;
			s.c1 = s.c;
			sift(&s);

			s.p = (s.p + 1) >> 2;

			// Two "up"s, saves us a little time
			tmp = s.b + s.c + 1;
			s.b += tmp + 1;
			s.c = tmp;
		}
		else if ((s.p & 3) == 1)
		{
			if (s.q + s.c < n)
			{
				s.b1 = s.b;
				s.c1 = s.c;
				sift(&s);
			}
			else
			{
				trinkle(&s);
			}
			do {
				down(&s.b, &s.c);
				s.p <<= 1;
			} while (s.b > 1);
			s.p++;
		}
		s.r++;
	}
	s.r1 = s.r;
	trinkle(&s);

	// Build sorted array
	while (s.q-- > 1)
	{
		if (s.b == 1)
		{
			s.r--;
			s.p--;
			while((s.p & 1) == 0)
			{
				s.p >>= 1;
				up(&s.b, &s.c);
			}
		}
		else if (s.b > 2)
		{
			s.p--;
			s.r = s.r - s.b + s.c;
			if (s.p > 0)
			{
				semitrinkle(&s);
			}
			down(&s.b, &s.c);
			s.p = (s.p << 1) + 1;
			s.r += s.c;
			semitrinkle(&s);
			down(&s.b, &s.c);
			s.p = (s.p << 1) + 1;
		}
		// element q processed
	}
	// element 0 processed
}
// END   SMOOTH SORT ALGORITHM

#ifdef __GNUC__
__inline
#else
	#ifdef _MSC_VER
		#if _MSC_VER >= 1800
_inline
		#else
static
		#endif
	#else
static
	#endif
#endif
void swap(value_t *a, value_t *b)
{
	value_t temp = *a;
	*a = *b;
	*b = temp;
}

static sint8 findDtc(const T_StackDtcs *stack, const uint16 dtcId)
{
	sint8 ret_s = -1;
	sint8 i;

	for (i = 0; (i < stack->cnt) && (stack->dtcs[i] <= dtcId); i++)
	{
		if (stack->dtcs[i] == dtcId)
		{
			ret_s = i;
			break;
		}
	}
	return ret_s;
}

boolean initDtcStack_NoMutex(T_StackDtcs *stack)
{
	boolean ret_b = FALSE;

	if (NULL != stack)
	{
		int i;
		for (i = 0; i < MAX_ACTIVE_DTC; i++)
		{
			stack->dtcs[i] = 0xFFFF;
		}
		stack->cnt = 0;
		
		ret_b = TRUE;
	}

	return ret_b;
}

boolean addDtcInStack_NoMutex(T_StackDtcs *stack, const uint16 dtcId)
{
	boolean ret_b = FALSE;

	if ((NULL != stack) && (stack->cnt < MAX_ACTIVE_DTC))
	{
		if (findDtc(stack, dtcId) == -1)
		{
			stack->dtcs[stack->cnt++] = dtcId;
			if (stack->cnt > 1)
			{
				if (2 == stack->cnt)
				{
					if (stack->dtcs[0] > stack->dtcs[1])
					{
						swap(&stack->dtcs[0], &stack->dtcs[1]);
					}
				}
				else
				{
					smoothsort(stack->dtcs, stack->cnt);
				}
			}
			ret_b = TRUE;
		}
	}

	return ret_b;
}

boolean delDtcFromStack_NoMutex(T_StackDtcs *stack, const uint16 dtcId)
{
	boolean ret_b = FALSE;
	
	if ((NULL != stack) && (stack->cnt > 0))
	{
		sint8 pos = findDtc(stack, dtcId);
		if (pos != -1)
		{
			sint8 i;
			for (i = pos; i < (stack->cnt-1); i++)
			{
				stack->dtcs[i] = stack->dtcs[i + 1];
			}
			stack->cnt--;
			ret_b = TRUE;
		}
	}

	return ret_b;
}

boolean findDtc_NoMutex(const T_StackDtcs *stack, const uint16 dtcId)
{
	boolean ret_b = FALSE;

	if ((NULL != stack) && (stack->cnt > 0))
	{
		ret_b = (findDtc(stack, dtcId) >= 0);
	}

	return ret_b;
}

sint8 getDtcNb_NoMutex(const T_StackDtcs *stack)
{
	sint8 ret_s = -1;

	if (NULL != stack)
	{
		ret_s = stack->cnt;
	}

	return ret_s;
}
