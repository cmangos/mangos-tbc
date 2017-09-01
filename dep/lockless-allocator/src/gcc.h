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
#ifndef LL_GCC_H
#define LL_GCC_H
#define _GNU_SOURCE
#include <pthread.h>

#define __thread__ __thread __attribute__ ((tls_model ("initial-exec"))) 

#define HAVE_PTHREADS
#define HAVE_SYS_SELECT
#define HAVE_SYS_SOCKET
#define HAVE_NETINET_IN
#define HAVE_SYS_MMAN

#define cache_align __attribute__((aligned(64)))
#define noinline __attribute__((__noinline__))
#define prefetch(x) __builtin_prefetch(x)
#define barrier() asm volatile("": : :"memory")
#define forget(v) asm volatile("": "=m"(v) :"m"(v))
#define mfence(v) asm volatile("mfence\n": : :"memory")
#define cpu_relax() asm volatile("rep; nop\n": : :"memory")
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define gcc_used __attribute__((used))
#define _hide_ __attribute__((visibility("hidden")))
#define __pure __attribute__((pure))

#define GCC_ASM

#include <err.h>

#endif /* LL_GCC_H */
