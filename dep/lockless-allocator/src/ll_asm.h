/*
 *   Copyright (C) 2009, 2010, 2011 Lockless Inc., Steven Von Fuerst.
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Functions that require asm for efficiency, or to work at all...
 */

#ifndef LL_ASM_H
#define LL_ASM_H
#include "compiler.h"
#ifdef GCC_ASM
#include <stdint.h>
#define atomic_or(P, V) __sync_or_and_fetch((P), (V))
#define atomic_and(P, V) __sync_and_and_fetch((P), (V))
#define atomic_add(P, V) __sync_add_and_fetch((P), (V))
#define atomic_xadd(P, V) __sync_fetch_and_add((P), (V))
#define atomic_cmpxchg_bool(P, O, N) __sync_bool_compare_and_swap((P), (O), (N))
#define atomic_access(V) (*(volatile typeof(V) *)&(V))

static inline unsigned char bts(volatile void *mem, size_t offset)
{
	unsigned char result;
	asm (
		"lock; bts %2, %1; setc %0;"
		: "=r" (result), "+m" (* (volatile long *) mem)
		: "r" (offset)
		: "cc");
	return result;
}

static inline unsigned char btr(volatile void *mem, size_t offset)
{
	unsigned char result;
	asm (
		"lock; btr %2, %1; setc %0;"
		: "=r" (result), "+m" (* (volatile long *) mem)
		: "r" (offset)
		: "cc");
	return result;
}

static inline int ffsu(unsigned x)
{
	int result;

	asm ("bsf %[x], %[result]"
		: [result] "=r" (result)
		: [x] "mr" (x)
		:"cc");

	return result;
}

static inline size_t flsu(unsigned x)
{
	size_t result;

	asm ("bsr %[x], %[result]"
		: [result] "=r" (result)
		: [x] "mr" (x)
		:"cc");

	return result;
}

#ifdef __x86_64__
static inline size_t ffsq(size_t x)
{
	size_t result;

	asm ("bsfq %[x], %[result]"
		: [result] "=r" (result)
		: [x] "mr" (x)
		:"cc");

	return result;
}

static inline size_t flsq(size_t x)
{
	size_t result;

	asm ("bsrq %[x], %[result]"
		: [result] "=r" (result)
		: [x] "mr" (x)
		:"cc");

	return result;
}

#else
static inline size_t ffsq(unsigned long long x)
{
	size_t result;

	unsigned xlo = x & 0xffffffff;
	unsigned xhi = x >> 32;

	unsigned tmp;

	asm ("bsfl %[xhi], %[tmp]\n"
		 "addl $0x20, %[tmp]\n"
		 "bsfl %[xlo], %[result]\n"
		 "cmove %[tmp], %[result]\n"
		 :[result] "=r" (result), [tmp] "=&r" (tmp)
		 :[xlo] "rm" (xlo), [xhi] "rm" (xhi)
		 :"cc");

	return result;
}

static inline size_t flsq(unsigned long long x)
{
	size_t result;

	unsigned xlo = x & 0xffffffff;
	unsigned xhi = x >> 32;
	unsigned tmp;

	asm ("bsrl %[xlo], %[tmp]\n"
		 "addl $-0x20, %[tmp]\n"
		 "bsrl %[xhi], %[result]\n"
		 "cmove %[tmp], %[result]\n"
		 "addl $0x20, %[result]\n"
		 :[result] "=r" (result), [tmp] "=&r" (tmp)
		 :[xlo] "rm" (xlo), [xhi] "rm" (xhi)
		 :"cc");

	return result;
}

#endif

static inline unsigned char xchg_8(void *ptr, unsigned char x)
{
	asm volatile("xchgb %0,%1"
				:"=r" (x)
				:"m" (*(volatile unsigned char *)ptr), "0" (x)
				:"memory");

	return x;
}

static inline unsigned short xchg_16(void *ptr, unsigned short x)
{
	asm volatile("xchgw %0,%1"
				:"=r" (x)
				:"m" (*(volatile unsigned short *)ptr), "0" (x)
				:"memory");

	return x;
}


static inline unsigned xchg_32(void *ptr, unsigned x)
{
	asm volatile("xchgl %0,%1"
				:"=r" (x)
				:"m" (*(volatile unsigned *)ptr), "0" (x)
				:"memory");

	return x;
}

#ifdef __x86_64__
static inline unsigned long long xchg_64(void *ptr, unsigned long long x)
{
	asm volatile("xchgq %0,%1"
				:"=r" (x)
				:"m" (*(volatile unsigned long long *)ptr), "0" (x)
				:"memory");

	return x;
}

static inline void *xchg_ptr(void *ptr, void *x)
{
	__asm__ __volatile__("xchgq %0,%1"
				:"=r" (x)
				:"m" (*(volatile uintptr_t *)ptr), "0" ((uintptr_t) x)
				:"memory");

	return x;
}
#else
static inline void *xchg_ptr(void *ptr, void *x)
{
	__asm__ __volatile__("xchgl %k0,%1"
				:"=r" (x)
				:"m" (*(volatile uintptr_t *)ptr), "0" ((uintptr_t) x)
				:"memory");
	return x;
}
#endif

static inline unsigned long long rdtsc(void)
{
	unsigned hi, lo;
	asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
	return lo + ((unsigned long long)hi << 32);
}

#else /* GCC_ASM */

static inline int ffsu(unsigned x)
{
	unsigned long result;
	__assume(x);
	_BitScanForward(&result, x);

	return result;
}

static inline int flsu(unsigned x)
{
	unsigned long result;
	__assume(x);
	_BitScanReverse(&result, x);

	return result;
}

static inline size_t ffsq(unsigned long long x)
{
	unsigned long result;
	__assume(x);
	_BitScanForward64(&result, x);

	return result;
}

static inline size_t fflq(unsigned long long x)
{
	unsigned long result;
	__assume(x);
	_BitScanReverse64(&result, x);

	return result;
}

#ifdef __x86_64__
static inline void *xchg_ptr(void *ptr, void *x)
{
	return (void *) _InterlockedExchange64(ptr, (__int64) x);
}
#else
static inline void *xchg_ptr(void *ptr, void *x)
{
	return (void *) _InterlockedExchange(ptr, (long) x);
}
#endif


#endif /* GCC_ASM */

#endif /* LL_ASM_H */
