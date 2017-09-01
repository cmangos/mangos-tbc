/*
 * Copyright (C) 2014 Vladislav Samsonov.
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

#ifndef LL_VS_H
#define LL_VS_H

#ifndef WINDOWS
#define WINDOWS
#endif

#include <windows.h>
#include <intrin.h>
#include <xmmintrin.h>

#define inline __inline
#define __extension__
#define cache_align __declspec(align(64))
#define noinline __declspec(noinline)
#define __pure

#ifdef _WIN64
#define __x86_64__ 1
#endif

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

#ifndef _CRT_ERRNO_DEFINED
#define _CRT_ERRNO_DEFINED
int __cdecl _set_errno(int err);
int __cdecl _get_errno(int *err);
#endif /* _CRT_ERRNO_DEFINED */

#endif
