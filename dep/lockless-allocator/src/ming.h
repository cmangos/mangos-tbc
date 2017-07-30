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

/* Coompiler specific details - gcc */
#ifndef LL_MING_H
#define LL_MING_H

#ifndef WINDOWS
#define WINDOWS
#endif

#include <windows.h>

void set_enomem(void);

#define __thread__ __thread __attribute__ ((tls_model ("initial-exec"))) 

/* #define HAVE_PTHREADS */
/* #define HAVE_SYS_SELECT */
/* #define HAVE_SYS_SOCKET */
/* #define HAVE_NETINET_IN */
/* #define HAVVE_SYS_MMAN */

#define cache_align __attribute__((aligned(64)))
#define noinline __attribute__((__noinline__))
#define prefetch(x) __builtin_prefetch(x)
#define barrier() asm volatile("": : :"memory")
#define forget(v) asm volatile("": "=m"(v) :"m"(v))
#define cpu_relax() asm volatile("rep; nop\n": : :"memory")
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define gcc_used __attribute__((used))
#define _export_
#define __pure __attribute__((pure))

#define GCC_ASM

#include <windows.h>

struct iovec
{
	void *iov_base;
	size_t iov_len;
};

#ifndef EBUSY
#define EBUSY 1
#endif
#define pthread_mutex_lock EnterCriticalSection
#define pthread_mutex_unlock LeaveCriticalSection
#define pthread_mutex_t CRITICAL_SECTION
static inline int pthread_mutex_trylock(pthread_mutex_t *m)
{
	return TryEnterCriticalSection(m) ? 0 : EBUSY;
}
#define pthread_mutex_init(L, A) InitializeCriticalSection(L)
#define pthread_mutex_destroy(L) DeleteCriticalSection(L)
#define pthread_cond_init(C, A) InitializeConditionVariable(C)
#define pthread_cond_signal(C) WakeConditionVariable(C)
#define pthread_cond_broadcast(C) WakeAllConditionVariable(C)
#define pthread_cond_wait(C, M) SleepConditionVariableCS((C), (M), INFINITE)
#define pthread_cond_t CONDITION_VARIABLE
#define pthread_key_create 1

#define MAP_FAILED	NULL

#include <stdlib.h>
#include <stdio.h>

static __attribute__((format (ms_printf, 2, 3))) inline void errx(int ret, const char *fmt, ...)
{
	va_list va;

	/* Get args */
	va_start(va, fmt);

	/* Print it */
	vfprintf(stderr, fmt, va);

	/* Make sure it is printed */
	fflush(NULL);

	/* Done */
	va_end(va);

	exit(ret);
}

#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED
__cdecl int _set_errno(int err);
__cdecl int _get_errno(int *err);
#endif /* _CRT_ERRNO_DEFINED */

#endif /* LL_GCC_H */
