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
 * Implement a lockfree allocator based upon lockless queues
 * that communicate between processors, and btrees to hold the
 * unallocated memory.
 */

#define _GNU_SOURCE

#include "compiler.h"
#include "ll_asm.h"
#include "ll_list.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#ifndef WINDOWS
#include <sys/mman.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#endif /* !WINDOWS */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <malloc.h>

/* Debugging */
//#define DEBUG_ALLOC

/* Extra checking */
//#define DEBUG_ALLOC_SLOW

/* Memory leak debugging */
//#define DEBUG_LEAK
//#define DEBUG_LEAK_DISP		0

/* For windows and valgrind */
//#define EMU_SBRK
//#define EMU_SBRK_VG

/* Turn off slab usage - useful for debugging btree and small alloc code */
//#define DEBUG_NO_SLAB

/* Turn on home-made profiler */
//#define DEBUG_PROFILE

#ifdef DEBUG_PROFILE
#include "prof.h"
#else
#define DECL_PROF_FUNC
#endif


#ifndef WINDOWS
#define PAGESIZE		4096UL
#else
#define PAGESIZE		((size_t) 65536)
#endif

/* Seperator between allocations */
#define SEPSIZE			16
#define PTRSIZE			8

#define HEADERSIZE		32

#define ADDR_SIZE		27

#define SLABSIZE		((uintptr_t) (1 << 17))
//#define SLABBMAX		((SLABSIZE / 8) - 2)
#define SLABBMAX		64	/* About 4M per thread */

/* Slab sizes 0 to 512 bytes in steps of 16 */
#define NUM_SB			33
#define SB_MAX			((NUM_SB - 1) * 16)

/* Maximum size of medium allocations */
#define BTMALLOC		((1L << ADDR_SIZE) - HEADERSIZE)

#define TOP_SIZE		(-(PAGESIZE * 2))

/* Minimum size to allocate at a time */
#define MINALLOC		(1L << 21)

/* 64 queues */
#define NUM_QS			64
#define QS_MAX			(NUM_QS * 16 - SEPSIZE)

/* Only check four fast bins */
#define FAST_MASK		0x0fULL

/* Clear the fast lists at least this often on free() */
#define FREE_FAST		((1 << 16) - 1)

/* The biggest size that can reasonably be stored in the fast lists */
#ifdef __x86_64__
#define FAST_64_BIN		67108863
#else
#define FAST_64_BIN		3669975
#endif


#ifdef __x86_64__
#define MYSIZE_TO_PTR(T, N) ((dlist *) (((char *) T) + offsetof(atls, qs) + N - SEPSIZE))
#else
#define MYSIZE_TO_PTR(T, N) ((dlist *) (((char *) T) + offsetof(atls, qs) + N/2 - PTRSIZE))
#endif

/* Fast-lists */
#define NUM_FL			64

/* btree size */
#define BT_MAX			16

/* 64bit mask type */
typedef unsigned long long u64b;

/* Pre declare */
typedef struct btree btree;

typedef struct sep sep;
struct sep
{
	btree *left;

#ifndef __x86_64__
	int pad;
#endif

	__extension__ union
	{
		__extension__ struct
		{
			unsigned bs_offset;
			unsigned size;
		};
		uintptr_t prev;
	};
};

struct btree
{
	/* Seperator */
	sep s;

	__extension__ union
	{
		slist list;
		dlist list2;
		void *data;

		__extension__ struct
		{
			btree *parent;
			unsigned bsize[BT_MAX + 1];
			char prev[BT_MAX + 1];
			btree *ptr[BT_MAX];
		};
	};
#ifndef __x86_64__
	unsigned pad;
#endif
};

#ifdef WINDOWS
/* For documentation purposes only */
struct mallinfo
{
	/* Total space allocated with sbrk in all threads */
	int arena;

	/* Number of ordinary (non-slab and non-mmap) allocations */
	int ordblks;

	/* Number of blocks in this threads slab */
	int smblks;

	/* Number of mmaped chunks in our thread */
	int hblks;

	/* Number of btree nodes for our thread */
	int hblkhd;

	/* Total (possibly partially) used slab blocks */
	int usmblks;

	/* Total number of free slab blocks */
	int fsmblks;

	/* Total allocated space for this thread including overhead */
	int uordblks;

	/* Total free space for this thread in ordinary mmap region */
	int fordblks;

	/* zero */
	int keepcost;
};
#endif


/* Seperator bitflags */
#define FLG_UNUSED	0x01
#define FLG_LUNUSED	0x02
#define FLG_LSIZE8	0x04
#define FLG_SIZE8	0x08

static int b_leaf(btree *b);

#define SEP_INDEX(b, loc, v) (((unsigned char *) &((b)->bsize[loc]))[v])

/* Index into the zeroth int in bsize[] */
#define b_start(b) SEP_INDEX(b, 0, 0)
#define b_pindex(b) SEP_INDEX(b, 0, 1)
#define b_mask(b) (*(unsigned short*) &SEP_INDEX(b, 0, 2))

#define b_next(b, loc) SEP_INDEX(b, loc, 0)
#define b_prev(b, loc) (b->prev[loc])
#define b_last(b) b_prev(b, 0)
#define b_ptr(b, loc) (b->ptr[(loc) - 1])

typedef union mealloc mealloc;
union mealloc
{
	__extension__ struct
	{
		slist **tail;
		dlist m_list;
	};

	__extension__ struct
	{
		char pad[16];
		btree b;
	};

	/* Prevent compiler warning "no named members" */
	void *dummy;
};

typedef struct sbheader sbheader;
struct sbheader
{
	__extension__ union
	{
		__extension__ struct
		{
			slist **tail;

			dlist list;

			uintptr_t max;

			unsigned size;

		};

		/* First cache line is mostly read-only */
		char pad[64];
	};

	/* Second cache line is read-write */
	uintptr_t first;

	unsigned used;

#ifndef __x86_64__
	u64b dummy;	/* padding to get right alignment */
#endif

	/* This needs to be 16 byte aligned */
	void *data;
};

/* 64k block of pointers to free blocks */
typedef struct freesb freesb;
struct freesb
{
	freesb *next;
	unsigned count;

	sbheader *blocks[SLABBMAX];
};

typedef struct atls atls;
struct atls
{
	slist fl[NUM_FL];
	u64b f_mask;

#ifndef __x86_64__
	unsigned dummy;	/* padding to get right q8 alignment */
#endif

	/* Note that qs[0] is a miss-aligned btree pointer! */
	dlist qs[NUM_QS];

	__extension__ union
	{
		__extension__ struct
		{
			/* Overlap with the seperator in bheap */
			slist btree_freenode;
			unsigned b_hgt;
			unsigned b_cnt;
		};

		btree bheap;
	};

	u64b q_mask;

	/* Partially full slabs */
	dlist slab[NUM_SB];

	dlist slab_full;

	freesb *slab_chunk;

	size_t percpu_hash;

	size_t a_alloced;
	size_t s_wanted;

	slist *head;

	dlist bl;

#ifdef DEBUG_LEAK
	int leak_fd;
#endif

	/* Hazard list */
	dlist h_list;
	void *hazard;

	/* Deleted list */
	atls *d_list;

	int fcount;

	char callocable;

	char dummy3[59];

	/* Off by itself to reduce false sharing */
	slist *tail;
};

#ifdef USE_DLL
#define PREFIX(X)	llalloc##X
#else
#ifdef USE_PREFIX
#define PREFIX(X)	llalloc##X
#else
#define PREFIX(X)	X
#endif
#endif

#ifndef DEBUG_ALLOC
#ifdef _MSC_VER
#define always_inline __forceinline
#else
#define always_inline inline __attribute__((always_inline))
#endif
#else /* DEBUG_ALLOC */
#define always_inline
#endif

/* This ISO C11 function might not have a prototype in older headers */
void *aligned_alloc(size_t alignment, size_t size);

#ifdef WINDOWS

void llmutex_lock(void *l);
void llmutex_unlock(void *l);
int llmutex_trylock(void *l);

typedef void * mutex_t;
#define mutex_lock llmutex_lock
#define mutex_unlock llmutex_unlock
#define mutex_trylock llmutex_trylock
#define MUTEX_INITIALIZER {0}

#ifndef EMU_SBRK
#define EMU_SBRK
#endif

#define set_enomem() _set_errno(ENOMEM)

/* Other functions that need prototypes */
#if defined USE_DLL || defined USE_PREFIX
void llallocfree(void *p);
void *llallocmalloc(size_t size);
void *llalloccalloc(size_t size, size_t n);
void *llallocrealloc(void *p, size_t size);
size_t llalloc_msize(void *p);
void *llalloc_expand(void *p, size_t size);

/* Hack - indirect calls to crt functions */
int (* __callnewh)(size_t);
int (* __newmode)(void);
#endif /* USE_DLL */

void cfree(void *p);
void *memalign(size_t align, size_t size);
int posix_memalign(void **p, size_t align, size_t size);
void *valloc(size_t size);
void *pvalloc(size_t size);
struct mallinfo mallinfo(void);
int malloc_trim(size_t pad);
int mallopt(int param, int val);
void *PREFIX(_calloc_impl)(size_t n, size_t size, int *errno_tmp);
void PREFIX(_free_nolock)(void *p);
void *PREFIX(_realloc_nolock)(void *p, size_t size);
void *PREFIX(_calloc_nolock)(size_t n, size_t size);
size_t PREFIX(_msize_nolock)(void *p);
static size_t malloc_usable_size(void *p);

void __tlregdtor(void (*)(void *));

#else /* WINDOWS */

static int sys_futex(void *addr1, int op, int val1, struct timespec *timeout, void *addr2, int val3)
{
	return syscall(SYS_futex, addr1, op, val1, timeout, addr2, val3);
}

#define cmpxchg(P, O, N) __sync_val_compare_and_swap((P), (O), (N))

typedef union mutex_t mutex_t;

union mutex_t
{
	unsigned u;
	struct
	{
		unsigned char locked;
		unsigned char contended;
	} b;
};

static void mutex_init(mutex_t *m)
{
	m->u = 0;
}

static void mutex_lock(mutex_t *m)
{
	int i;

	/* Try to grab lock */
	for (i = 0; i < 100; i++)
	{
		if (!xchg_8(&m->b.locked, 1)) return;

		cpu_relax();
	}

	/* Have to sleep */
	while (xchg_32(&m->u, 257) & 1)
	{
		sys_futex(m, FUTEX_WAIT_PRIVATE, 257, NULL, NULL, 0);
	}
}

static void mutex_unlock(mutex_t *m)
{
	DECL_PROF_FUNC;

	int i;

	/* Locked and not contended */
	if ((m->u == 1) && (cmpxchg(&m->u, 1, 0) == 1)) return;

	/* Unlock */
	m->b.locked = 0;

	barrier();

	/* Spin and hope someone takes the lock */
	for (i = 0; i < 200; i++)
	{
		if (m->b.locked) return;

		cpu_relax();
	}

	/* We need to wake someone up */
	m->b.contended = 0;

	sys_futex(m, FUTEX_WAKE_PRIVATE, 1, NULL, NULL, 0);
}

static int mutex_trylock(mutex_t *m)
{
	unsigned c;

	if (m->b.locked) return EBUSY;
	c = xchg_8(&m->b.locked, 1);
	if (!c) return 0;
	return EBUSY;
}

#define MUTEX_INITIALIZER {0}

/* Interface for hooks, if needed */
#ifdef USE_ALLOC_HOOK
#include "ll_alloc_hook.c"
#endif


static void malloc_stats_aux(int show_nodes);

static gcc_used char dummy1[64];
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
static pthread_key_t death_key;

/*
 * If pthread isn't linked in,
 * have weak replacements for the single-threaded case
 */
#pragma weak pthread_atfork
#pragma weak pthread_key_create
#pragma weak pthread_setspecific
#pragma weak pthread_once

#define set_enomem() (errno = ENOMEM)

#endif /* WINDOWS */

typedef union percpu_list percpu_list;
union percpu_list
{
	__extension__ struct
	{
		mutex_t m;
		freesb *list;
	};
	char pad[64];
};

/* Global thread hazard list */
static cache_align mutex_t h_lock = MUTEX_INITIALIZER;
static dlist h_list = DLIST_INIT(h_list);

static cache_align mutex_t d_lock = MUTEX_INITIALIZER;
static atls *d_list = NULL;

/* List of freed slab blocks */
static cache_align percpu_list *pc_slab;
static size_t cpu_total;

/* sbrk information */
#ifndef HOOK_SBRK
static cache_align mutex_t sb_lock = MUTEX_INITIALIZER;
static cache_align uintptr_t sbrk_start = 0;
static uintptr_t sbrk_size = 0;
static int sbrk_oom = 0;
#endif /* HOOK_SBRK */
static unsigned sltotal[NUM_SB];

#ifdef DEBUG_LEAK
#define LEAK_MAX		1024
typedef struct bigallocs bigallocs;
struct bigallocs
{
	void *p;
	size_t size;
};

static bigallocs big_leak[LEAK_MAX] = {{NULL, 0}};
static mutex_t l_lock = MUTEX_INITIALIZER;

#endif

/* Hack */
#define BUILD_ASSERT(C) do {switch (0){case 0:; case (C):;}} while (0)

/* Pre-declares */
static always_inline void *split_node(atls *tl, btree *b, size_t t_size, size_t size);
static void merge_node(atls *tl, void *p);
static int init_sldata(void);
static void slab_free(atls *tl, void *p);
static void local_free(atls *tl, void *p);
static void *local_alloc(atls *tl, size_t size);
static void *slab_alloc_safe(atls *tl, size_t size);
static always_inline void *fast_alloc(atls *tl, size_t size);
static void *slow_alloc(atls *tl, size_t size);
static void atls_merge(atls *tl1, atls *tl2);
static void test_all(atls *tl);
static void *zalloc(atls *tl, size_t size);
void **independent_calloc(size_t n, size_t size, void **chunks);
void **independent_comalloc(size_t n, size_t *sizes, void **chunks);

static inline btree *small_next(btree *b)
{
	return b->data;
}

static inline void set_small_next(btree *b, btree *next)
{
	b->data = next;
}

#ifdef __x86_64__
static inline btree *small_prev(btree *b)
{
	return (btree *) (b->s.prev & ~15);
}

static inline void set_small_prev(btree *b, btree *prev)
{
	uintptr_t p = b->s.prev & 15;
	b->s.prev = p + (uintptr_t) prev;
}
#else
static inline btree *small_prev(btree *b)
{
	return (btree *) b->s.size;
}

static inline void set_small_prev(btree *b, btree *prev)
{
	b->s.size = (unsigned) prev;
}

#endif

static inline void *shift(void *p, size_t s)
{
	return &(((char *)p)[s]);
}

/* Unfortunately, TLS support with mingw is totally broken... so we need to emulate it */
#ifdef WINDOWS
static DWORD tls_index = TLS_OUT_OF_INDEXES;
static atls *get_tls(void)
{
	if (tls_index == TLS_OUT_OF_INDEXES) return NULL;

	return TlsGetValue(tls_index);
}

static void set_tls(atls *tls)
{
	TlsSetValue(tls_index, tls);
}
#else
#ifndef USE_ALLOC_HOOK
static __thread__ atls *tls = NULL;
#define get_tls() tls
#define set_tls(T) (tls = (T))
#endif
#endif

static size_t cpu_num(void)
{
#ifdef WINDOWS
	SYSTEM_INFO info;

	GetSystemInfo(&info);
	return info.dwNumberOfProcessors;
#else
#ifdef SYS_MACOSX
	int num;
	size_t len = sizeof(num);
	if (sysctlbyname("hw.ncpu", &num, &len, NULL, 0)) num = 1;
	return num;
#else
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif	/* SYS_MACOSX */
#endif  /* WINDOWS */
}

/*
 * Emulate sbrk()
 * Assumes we are called under a lock */
#ifdef EMU_SBRK

#ifdef EMU_SBRK_VG
#define SBRK_SIZE (1ULL << 30)
#else /* EMU_SBRK_VG */

#ifdef __x86_64__

/* Default to 32GiB of sbrk space */
#define SBRK_SIZE (1ULL << 37)
#else /* __x86_64__ */

/* Default to 1GiB of sbrk space */
#define SBRK_SIZE (1ULL << 30)
#endif /* __x86_64__ */
#endif /* EMU_SBRK_VG */


static void *sbrk_mmap_base = NULL;
static void *sbrk_mmap_end = 0;
static void init_sbrk(void)
{
	DECL_PROF_FUNC;

	size_t size = SBRK_SIZE;

	while (1)
	{
#ifndef WINDOWS
		sbrk_mmap_base = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_NORESERVE, -1, 0);
#else
		/* Allocate address space - but no memory */
		sbrk_mmap_base = VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_READWRITE);
#endif
		if (sbrk_mmap_base == MAP_FAILED)
		{
			sbrk_mmap_base = NULL;
			size = size / 2;
			if (size < 65536) return;
		}
		else
		{
			sbrk_mmap_end = shift(sbrk_mmap_base, size);

			return;
		}
	}
}

static void *emu_sbrk(size_t size)
{
	DECL_PROF_FUNC;

	void *out;

	/* Hack - initialize if required */
	if (!size) init_sbrk();
	if (!sbrk_mmap_base) return MAP_FAILED;

	out = sbrk_mmap_base;
	sbrk_mmap_base = shift(sbrk_mmap_base, size);
	if (sbrk_mmap_base >= sbrk_mmap_end)
	{
		sbrk_mmap_base = out;

		return MAP_FAILED;
	}

#ifdef WINDOWS
	/* Enable memory */
	VirtualAlloc(out, size, MEM_COMMIT, PAGE_READWRITE);
#endif

	return out;
}

#define sbrk(S) emu_sbrk(S)
#endif

#ifndef HOOK_SBRK
static inline void init_sbrk_start(void)
{
	void *v = sbrk(0);
	sbrk_start = (uintptr_t) v;
}
#endif

static inline int is_slab(void *p)
{
	return ((uintptr_t) p - sbrk_start < sbrk_size);
}

static inline void *page_start(void *p)
{
	return (void *) (-PAGESIZE & (uintptr_t) p);
}

static inline size_t page_align(size_t s)
{
	return -PAGESIZE & (s + PAGESIZE - 1);
}

static inline size_t sep_align(size_t s)
{
	/*
	 * We want to align on 16byte boundaries
	 *
	 * 16 -> 16
	 * 24 -> 16
	 * 25 -> 32
	 * 32 -> 32
	 */
	/*
	 * Then we want to include the extra 8 bytes of last ptr that are free.
	 * Finally, we want to include the following sep data.
	 */
	/*
	 *	0 -> 16
	 *  8 -> 16
	 *  9 -> 32
	 * 16 -> 32
	 * 24 -> 32
	 * 25 -> 48
	 * 32 -> 48
	 * 40 -> 48
	 */

	return (s + 7 + 16) & ~15;
}

static inline int un_used(btree *b)
{
	return (b->s.bs_offset & FLG_UNUSED);
}

static inline int left_unused(btree *b)
{
	return b->s.bs_offset & FLG_LUNUSED;
}

static inline void set_unused(btree *b, btree *br)
{
	br->s.bs_offset |= FLG_LUNUSED;
	br->s.left = b;

	b->s.bs_offset |= FLG_UNUSED;
}

static inline void set_used(btree *b, size_t size)
{
	btree *br = shift(b, size);
	br->s.bs_offset &= ~FLG_LUNUSED;

#ifdef DEBUG_ALLOC_SLOW
	if (size != b->s.size) errx(1, "size missmatch\n");
#endif

	b->s.bs_offset &= ~FLG_UNUSED;
}

static inline void set_size8(btree *b)
{
	btree *br = shift(b, 16);
	br->s.bs_offset |= FLG_LSIZE8;
	b->s.bs_offset |= FLG_SIZE8;
}

static inline void unset_size8(btree *b)
{
	btree *br = shift(b, 16);
	br->s.bs_offset &= ~FLG_LSIZE8;
	b->s.bs_offset &= ~FLG_SIZE8;
	b->s.size = 16;
	b->s.bs_offset &= 15;
	b->s.bs_offset += (br->s.bs_offset & ~15) - 16;
}

#ifdef __x86_64__
static inline btree *get_q8(atls *tl)
{
	/* Mega hack - align so that we return a btree object pointer to the correct memory locations */
	return shift(&tl->qs[0], -(uintptr_t)8);
}
#else
static inline btree *get_q8(atls *tl)
{
	/* Mega hack - align so that we return a btree object pointer to the correct memory locations */
	return shift(&tl->qs[0], -(uintptr_t)12);
}
#endif

static inline btree *read_left(btree *b)
{
	if (!left_unused(b)) return NULL;
	if (b->s.bs_offset & FLG_LSIZE8) return shift(b, -(uintptr_t)16);
	return b->s.left;
}

static inline mealloc *read_bs(btree *b)
{
	uintptr_t s = b->s.bs_offset & ~15;

#ifdef DEBUG_ALLOC_SLOW
	void *v = shift(b, -s);
	if ((PAGESIZE - 1) & (uintptr_t) v) errx(1, "mealloc misaligned\n");
#endif

	return (mealloc *) shift(b, -s);
}

static void btree_init(btree *b)
{
	/* Init header */
	//b_start(b) = 0;
	b_mask(b) = -1;
	//b_pindex(b) = 0;
	//b_last(b) = 0;
}

static inline void set_sep(btree *b, int size, btree *bo)
{
	unsigned offset = bo->s.bs_offset & ~15;

	/* Store split block offset + size + used indicators */
	b->s.bs_offset = offset + ((uintptr_t) b - (uintptr_t) bo);
	b->s.size = size;
}

#ifdef DEBUG_ALLOC
static void check_sep(btree *b)
{
	btree *br = shift(b, b->s.size);

	if (((uintptr_t) b) & 15) errx(1, "btree misaligned\n");

	if (is_slab(&b->data)) errx(1, "btree slab overlap\n");

	/* Test unused bit */
	if (un_used(b))
	{
		if (b->s.bs_offset & FLG_SIZE8)
		{
			br = shift(b, 16);

			if (!(br->s.bs_offset & FLG_LSIZE8)) errx(1, "size8 bit missmatch\n");
		}
		else
		{
			if (b->s.size & 15) errx(1, "mysize misaligned\n");

			if ((b->s.size == 16) || (br->s.bs_offset & FLG_LSIZE8)) errx(1, "size8 bit missmatch\n");
			if (read_left(br) != b) errx(1, "left pointer wrong\n");
		}

		if (!left_unused(br)) errx(1, "Unused flag conflict\n");
	}
	else
	{
		if (b->s.size & 15) errx(1, "mysize misaligned\n");
		if (left_unused(br)) errx(1, "Unused flag conflict\n");
	}
}
#else
#define check_sep(B) ((void) sizeof(B))
#endif

#ifndef WINDOWS
static __attribute__((format (gnu_printf, 2, 3))) void leak_print(atls *tl, const char *format, ...)
{
	char buf[1024];

	va_list ap;

	va_start(ap, format);
	vsnprintf(buf, 1024, format, ap);
	va_end(ap);

#ifdef DEBUG_LEAK
	/* Need tls and leak_fd initialized */
	if (tl)
	{
		if (tl->leak_fd == -1)
		{
			char buf[1024];
			int pid = getpid();
			int tid = syscall(SYS_gettid);

			snprintf(buf, 1024, "/tmp/leak-%d:%d.txt", pid, tid);

			tl->leak_fd = open(buf, O_WRONLY | O_CREAT | O_APPEND,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}

		if (tl->leak_fd != -1)
		{
			int len = strlen(buf);
			char *c = buf;

			while (len)
			{
				int out = write(tl->leak_fd, c, len);

				/* Interrupted - try again */
				if (out == -1) continue;

				/* Device is full - stop writing */
				if (!out) return;

				len -= out;
				c += out;
			}
		}
	}
#else
	/* Shut up compiler warning */
	(void) tl;

	/* Otherwise output to stderr */
	fprintf(stderr, "%s", buf);

#endif
}
#else
#define leak_print(...)
#define malloc_stats_aux(...)
#endif

#ifdef DEBUG_LEAK
static void big_alloced(void *p, size_t size)
{
	int i;

	mutex_lock(&l_lock);
	for (i = 0; i < LEAK_MAX; i++)
	{
		if (big_leak[i].p) continue;

		big_leak[i].p = p;
		big_leak[i].size = size;
		mutex_unlock(&l_lock);
		leak_print(get_tls(), "Big alloc %p %llu\n", p, (unsigned long long) size);
		return;
	}
	mutex_unlock(&l_lock);

	errx(1, "debug leak oom, increase LEAK_MAX\n");
}

static void big_freed(void *p, size_t size)
{
	int i;

	mutex_lock(&l_lock);
	for (i = 0; i < LEAK_MAX; i++)
	{
		if (big_leak[i].p != p) continue;

		if (big_leak[i].size != size) errx(1, "big alloc size missmatch\n");
		big_leak[i].p = NULL;
		mutex_unlock(&l_lock);
		leak_print(get_tls(), "Big free %p %llu\n", p, (unsigned long long) size);
		return;
	}
	mutex_unlock(&l_lock);

	errx(1, "freeing unknown large block %p\n", p);
}

static size_t big_block_size(void *p)
{
	int i;

	mutex_lock(&l_lock);
	for (i = 0; i < LEAK_MAX; i++)
	{
		if (big_leak[i].p != p) continue;
		mutex_unlock(&l_lock);
		return big_leak[i].size;
	}

	mutex_unlock(&l_lock);

	errx(1, "freeing unknown large block %p\n", p);
}

static void test_leak_aux(void)
{
	atls *tl = get_tls();
	if (!tl) return;
	malloc_stats_aux(3);
	leak_print(tl, "Done\n");
	close(tl->leak_fd);
}

static void test_leak(void)
{
	static int count = 0;

	/* Display turned off? */
	if (!DEBUG_LEAK_DISP) return;

	/* Don't bother to be thread safe - it doesn't matter much */
	if (count++ == DEBUG_LEAK_DISP)
	{
		count = 0;
		malloc_stats_aux(3);
	}
}


#else
#define big_alloced(p, size) ((void) (sizeof(p) + sizeof(size)))
#define big_freed(p, size) ((void)(sizeof(p) + sizeof(size)))
#define test_leak_aux()
#define test_leak()
#define big_block_size(p) (sizeof(p) * 0)
#endif


/* Big allocations */
static void *big_alloc_aux(size_t size)
{
	DECL_PROF_FUNC;

	/* Get memory */
#ifndef WINDOWS
	void *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
#else
	void *p = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#endif

	/* Out of memory */
	if (p == MAP_FAILED) return NULL;

	big_alloced(p, size);

	/* Done */
	return p;
}

#ifdef WINDOWS
int handle_oom(int aize);
#else
#define handle_oom(S)	((errno = ENOMEM), 0)
#endif


static noinline void *big_alloc(atls *tl, size_t size)
{
	DECL_PROF_FUNC;

	size_t psize;

	size_t *p;

	/* This arguement prevents register problems in the fast path */
	(void) tl;

	if (size > TOP_SIZE) goto nomem;

	/* Get real size to allocate */
	psize = page_align(size + SEPSIZE);

	p = big_alloc_aux(psize);

	if (p)
	{
		*p = psize;
		return shift(p, SEPSIZE);
	}

nomem:

	if (handle_oom(size)) return big_alloc(tl, size);

	return NULL;
}

#ifdef WINDOWS
static noinline void big_free_aux(size_t *p)
{
	DECL_PROF_FUNC;

	big_freed(p, *p);

	VirtualFree(p, 0, MEM_RELEASE);
}
#else
static inline void big_free_aux(size_t *p)
{
	big_freed(p, *p);

	munmap(p, *p);
}
#endif


#ifdef DEBUG_ALLOC_SLOW
static void test_queue(atls *tl)
{
	slist *q;

	btree *b;

	/* Scan incoming queue, looking for corruption */
	for (q = tl->head; q; q = q->next)
	{
		/* Ignore slab nodes */
		if (is_slab(q)) continue;

		if (((uintptr_t) q) & 15) errx(1, "incoming queue corrupted\n");

		b = CONTAINER(btree, data, q);

		if (un_used(b)) errx(1, "queue element marked as unused\n");
	}
}
#else
#define test_queue(T) ((void) sizeof(T))
#endif

#ifdef __x86_64__
/* Magic code that converts size to entry in fast-list array */
static always_inline size_t size2fl(size_t size)
{
	size_t n = (size / 32);

	/* Make sure we don't overflow */
	if (size == 16) return 0;
	if (size > FAST_64_BIN) return NUM_FL - 1;

	n = n * n * n;

	return flsq(n);
}
#else
/* Magic code that converts size to entry in fast-list array */
static inline size_t size2fl(size_t size)
{
	size_t n;

	/* 32 bit version uses old floating point instructions */
	union di
	{
		double d;
		unsigned u2[2];
	} di;

	di.d = size + 40;

	n = (di.u2[1] >> 18) - 4115;

	/* Make sure we don't overflow */
	if (n >= NUM_FL) n = NUM_FL - 1;

	return n;
}
#endif


/* Add to previous list - but don't set flag */
static always_inline void fast_add(atls *tl, btree *b, size_t n)
{
	slist_add(&tl->fl[n], &b->list);
	tl->f_mask |= 1ULL << n;
}

/* Add to free lists */
static always_inline void fast_free(atls *tl, btree *b, size_t ms)
{
	size_t n = size2fl(ms);

#ifdef DEBUG_ALLOC_SLOW
	if (un_used(b)) errx(1, "fast_free() needs used node\n");
	if (b->s.size != ms) errx(1, "fast_free size wrong\n");
#endif

	fast_add(tl, b, n);
}

static int scan_queue(atls *tl, slist **qh, size_t wanted)
{
	DECL_PROF_FUNC;

	slist *q, *qn, *qp = NULL;

	btree *b;

	size_t msize;
	int flag = 0;

	/* Size wanted */
	tl->s_wanted = wanted;

	/* Scan incoming queue, freeing as we go */
	for (q = *qh; q; q = qn)
	{
#ifdef DEBUG_ALLOC_SLOW
		if (!is_slab(q))
		{
			if (((uintptr_t) q) & 15) errx(1, "incoming queue corrupted\n");
		}
#endif

		qn = q->next;
		qp = q;
		if (qn)
		{
			if (is_slab(q))
			{
				slab_free(tl, q);
			}
			else
			{
				merge_node(tl, q);
			}

			flag = 1;
		}
	}

	*qh = qp;

	/* Reset size wanted */
	tl->s_wanted = 0;

	/*
	 * Make sure the last node isn't taking up too much room.
	 * Not that a slab node could only take up a max of SB_MAX bytes.
	 * (They aren't splittable anyway)
	 */
	if (is_slab(qp)) return flag;

	b = CONTAINER(btree, data, qp);

	msize = b->s.size;

	/* Don't split if too small */
	if (msize <= (1 << 16)) return flag;

	/* Make the head node take up less room.  Also, size 32 is faster than 16. */
	split_node(tl, b, msize, 32);

	return 1;
}


#ifdef DEBUG_ALLOC_SLOW

static void test_node(atls *tl, btree *b)
{
	mealloc *m = read_bs(b);

	if (tl != get_tls()) errx(1, "tls incorrect\n");
	if (m->tail != &tl->tail) errx(1, "node owner wrong\n");
}

/* Test fast list constraints */
static void test_fast_lists(atls *tl)
{
	int i, j;

	//if (tl->fl[63].next) errx(1, "fast list overflow\n");

	for (i = 0; i < NUM_FL; i++)
	{
		slist *p = &tl->fl[i];
		slist *f;

		scan_slist(p, f)
		{
			btree *b = CONTAINER(btree, list, f);

			/* Are we a slab node? */
			if (is_slab(&b->data))
			{
				errx(1, "Slab node on fast list\n");
			}

			test_node(tl, b);

			if (un_used(b)) errx(1, "Unused element in fast list\n");
			check_sep(b);

			j = size2fl(b->s.size);
			if ((i != j) && (i != j - 1)) errx(1, "Fast element in wrong bin\n");


			if (!(((uintptr_t) b ^ (uintptr_t) tl) & ~(PAGESIZE - 1))) errx(1, "tls on fast list!\n");
			//if (f == tl->head) errx(1, "queue head in fast list\n");

			if (f->next == f) errx(1, "fast list loop\n");
		}
	}
}
#else
#define test_fast_lists(T) ((void) sizeof(T))
#endif

/* Clear fast-lists */
static void clear_fast(atls *tl)
{
	DECL_PROF_FUNC;

	u64b mask = tl->f_mask;

	/* Anything to do? */
	while (mask)
	{
		size_t n = ffsq(mask);

		slist *p = &tl->fl[n];

		/* Get mask bit */
		mask &= -mask;

		/* Convert to a mask */
		mask = ~mask;

		/* Properly free everything in the list */
		while (p->next)
		{
			merge_node(tl, slist_rem(p));
		}

		/* Clear bottom bit */
		tl->f_mask &= mask;
		mask = tl->f_mask;
	}
}

/* Hack - same as clear_fast() but free nodes from tl2 into tl1 */
static void fast_merge(atls *tl1, atls *tl2)
{
	size_t n;
	//slist *p = tl2->fl;
	slist *p;

	/* Anything to do? */
	while (tl2->f_mask)
	{
		n = ffsq(tl2->f_mask);
		p = &tl2->fl[n];

		/* Turn off bit in f_mask, as nothing will be left there */
		tl2->f_mask &= tl2->f_mask - 1;

		/* Properly free everything in the list */
		while (p->next)
		{
			void *l = slist_rem(p);

			merge_node(tl1, l);
		}
	}
}

static noinline int reap_dead(atls *tl)
{
	DECL_PROF_FUNC;

	dlist *d;

	atls *tl2, *tl3;

	/* Check without taking mutex */
	if (!d_list) return 0;

	/* Try to get dead thread */
	if (mutex_trylock(&d_lock)) return 0;

	if (!d_list)
	{
		/* Nothing there */
		mutex_unlock(&d_lock);
		return 0;
	}

	/* Grab dead thread */
	tl2 = d_list;
	d_list = tl2->d_list;
	mutex_unlock(&d_lock);

	mutex_lock(&h_lock);

	/* Remove from hazard list */
	dlist_del(&tl2->h_list);

	/* Set flag so that memless free works */
	tl2->h_list.next = NULL;

	/* Merge data + update tail pointers */
	atls_merge(tl, tl2);

	/* Wait for all threads to not point to dead thread */
	scan_list(&h_list, d)
	{
		tl3 = list_entry(atls, h_list, d);

		while (tl3->hazard == &tl2->tail) cpu_relax();
	}

	mutex_unlock(&h_lock);

	/* Scan all final pending */
	scan_queue(tl, &tl2->head, 0);

	/* Free head */
	local_free(tl, tl2->head);

	/* Finally free tls data for dead thread */
#ifdef WINDOWS		
	VirtualFree(page_start(tl2), 0, MEM_RELEASE);
#else
	munmap(page_start(tl2), PAGESIZE);
#endif

	test_all(tl);

	/* Try to free up memory */
	return 1;
}

static void prepend_queue(slist *p, atls *tl, slist ***bs)
{
	DECL_PROF_FUNC;

	slist *tail;

	slist **btail = *bs;
	slist **btold;

	do
	{
		btold = btail;

		/* Make sure we write to the hazard pointer */
		xchg_ptr(&tl->hazard, btail);

		/* Has it changed while we were writing to our hazard pointer? */
		btail = *bs;
	}
	while (btold != btail);

	p->next = NULL;
	tail = xchg_ptr(btail, p);
	tail->next = p;

	barrier();

	tl->hazard = NULL;
}

static void destroy_tls(void *dummy)
{
	DECL_PROF_FUNC;

	atls *tl = get_tls();

	(void) dummy;

	test_all(tl);

	test_leak_aux();

	/*
	 * Make sure that any recursion via signals or other
	 * pthread_key destructors will reset this handler.
	 */
#ifdef WINDOWS
	set_tls((atls *) 1);
#else
	set_tls(NULL);
#endif

	/* The above line isn't allowed to be moved inside the lock due to possible signals */
	barrier();

	/* Add to dead list */
	mutex_lock(&d_lock);
	tl->d_list = d_list;
	d_list = tl;
	mutex_unlock(&d_lock);
}


/* Convert a pointer into a 32bit random number */
static unsigned rnd_ptr(void *p)
{
	u64b rnd_seed = (uintptr_t) p;
	rnd_seed *= 7319936632422683443ULL;
	rnd_seed ^= rnd_seed >> 32;
	rnd_seed *= 7319936632422683443ULL;
	rnd_seed ^= rnd_seed >> 32;

	/* Truncate to 32 bits */
	return rnd_seed;
}

/*
 * Pick a random offset from p into a region of size total
 * to fit an object of size size.
 *
 * Return a pointer to the object
 */
static void *rnd_offset(void *p, size_t total, size_t size)
{
	u64b slack_space = total - size;

	unsigned rng = rnd_ptr(p);

	unsigned offset = (slack_space * rng) >> 32;

	/* Keep 16-byte alignment */
	offset &= ~15;

	return shift(p, offset);
}

static atls *init_atls(atls *tl)
{
	int i;

	mealloc *m;
	btree *b, *br;

	btree *q8;

	/* Init lists */
	dlist_init(&tl->bl);

	/* queue 0 is taken by size 8 small-list */
	for (i = 1; i < NUM_QS; i++)
	{
		dlist_init(&tl->qs[i]);
	}

	/* Init small list */
	q8 = get_q8(tl);

#ifdef DEBUG_ALLOC_SLOW
	/* Btree needs to be correctly aligned */
	if (((uintptr_t) q8) & 15) errx(1, "q8 misaligned\n");
#endif

	set_small_next(q8, q8);
	set_small_prev(q8, q8);

	/* Init slabs */
	for (i = 0; i < NUM_SB; i++)
	{
		dlist_init(&tl->slab[i]);
	}
	dlist_init(&tl->slab_full);

	tl->percpu_hash = rnd_ptr(tl);

	/* Init btree */
	btree_init(&tl->bheap);

	/* Need a maximum of 2 nodes at this point */
	tl->b_hgt = 2;

#ifdef DEBUG_LEAK
	tl->leak_fd = -1;
#endif

	/* Grab initial allocation */
	m = big_alloc_aux(PAGESIZE);
	if (!m)
	{
		set_tls(NULL);
#ifdef WINDOWS
		VirtualFree(page_start(tl), 0, MEM_RELEASE);
#else
		munmap(page_start(tl), PAGESIZE);
#endif
		return NULL;
	}

	/* Keep track of total allocations */
	tl->a_alloced = PAGESIZE;

	/* Fill in header */
	dlist_add(&tl->bl, &m->m_list);

	m->tail = &tl->tail;

	b = &m->b;

	/* Create left seperator */
	b->s.size = PAGESIZE - HEADERSIZE;
	b->s.bs_offset = 16;

	/* Position of right seperator */
	br = shift(b, b->s.size);

	/* Create right seperator */
	br->s.bs_offset = PAGESIZE - SEPSIZE;
	split_node(tl, b, b->s.size, SEPSIZE);

	/* Make queue */
	tl->head = (void *) &b->data;
	tl->tail = tl->head;
	tl->head->next = NULL;

	/* Add to hazard list */
	mutex_lock(&h_lock);
	dlist_add(&h_list, &tl->h_list);
	mutex_unlock(&h_lock);

	return tl;
}

#ifndef WINDOWS

static void prepare_fork(void)
{
	size_t i;

	/* Stablize slab */
	for (i = 0; i < cpu_total; i++)
	{
		mutex_lock(&pc_slab[i].m);
	}

	/* Stablize hazard list */
	mutex_lock(&h_lock);

	/* Stabilize dead list */
	mutex_lock(&d_lock);

	/* Stablize sbrk */
	mutex_lock(&sb_lock);
}

static void parent_fork(void)
{
	size_t i;

	/* Done with sbrk */
	mutex_unlock(&sb_lock);

	/* Done with dead list */
	mutex_unlock(&d_lock);

	/* Done with hazard list */
	mutex_unlock(&h_lock);

	/* Done with slab */
	for (i = 0; i < cpu_total; i++)
	{
		mutex_unlock(&pc_slab[i].m);
	}
}

static void child_fork(void)
{
	size_t i;

	/* Clean up sb_lock in child */
	mutex_init(&sb_lock);

	/* Clean up d_lock in child */
	mutex_init(&d_lock);

	/* Clean up h_lock in child */
	mutex_init(&h_lock);

	/* Clean up slab locks in child */
	for (i = 0; i < cpu_total; i++)
	{
		mutex_unlock(&pc_slab[i].m);
	}

	/*
	 * Wipe hazard list as the other threads no longer exist
	 * This leaks memory, but we can't help it,
	 * as the other threads may be concurrently modifying internal
	 * data structures now.
	 */
	dlist_init(&h_list);

	/* We are the only member */
	dlist_add(&h_list, &get_tls()->h_list);
}

/*
 * Initialize things.
 * Unfortunately, we don't have a failure return value so we must die instead.
 */
static void init_handler(void)
{
	int res;

	/* Init sbrk information */
	init_sbrk_start();

	/* Add a fork handler */
	if (pthread_atfork)
	{
		res = pthread_atfork(prepare_fork, parent_fork, child_fork);
		if (res) errx(1, "pthread_atfork failed\n");
	}

	/* Create thread death key */
	if (pthread_key_create)
	{
		res = pthread_key_create(&death_key, destroy_tls);
		if (res) errx(1, "pthread_key_create() failed\n");
	}

	if (init_sldata())
	{
		errx(1, "Failed to allocate enough memory to initialize slab\n");
	}

#ifdef DEBUG_LEAK
	atexit(test_leak_aux);
#endif
}

static atls *init_tls(void)
{
	DECL_PROF_FUNC;

	atls *tl;

	/* Can we use a dead thread's tls data? */
	if (d_list)
	{
		mutex_lock(&d_lock);

		if (d_list)
		{
			/* Grab from death list */
			tl = d_list;
			d_list = tl->d_list;
			mutex_unlock(&d_lock);

			set_tls(tl);

			/* Init my thread destructor */
			if (pthread_setspecific) pthread_setspecific(death_key, tl);

			test_all(tl);

			/* Done */
			return tl;
		}
		mutex_unlock(&d_lock);
	}

	/* Hack - use a full page for it */
	tl = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	/* Out of memory */
	if (tl == MAP_FAILED) goto nomem;

	/* Randomly cache colour the tls data */
	tl = rnd_offset(tl, PAGESIZE, sizeof(atls));

	/* Save pointer for later memory calls */
	set_tls(tl);

	/* Make sure that we can always allocate two btree nodes from within itself */
	BUILD_ASSERT(NUM_QS * 8 + 16 >= sizeof(btree) * 2);

	/* Make sure atls isn't too big */
	BUILD_ASSERT(sizeof(atls) <= PAGESIZE);

	/* Make sure btree nodes fit in the slab */
	BUILD_ASSERT(sizeof(btree) <= SB_MAX);

	/* Hack - we should use the rest of the space to init the heap... */
	tl = init_atls(tl);
	if (!tl) goto nomem;

	/*
	 * Init handler.
	 * Note that this can allocate memory, so needs to be done last
	 */
	if (pthread_once)
	{
		pthread_once(&init_once, init_handler);
	}
	else
	{
		/* Since there are no threads... */
		if (!sbrk_start) init_handler();
	}

	/* Init my thread destructor */
	if (pthread_setspecific) pthread_setspecific(death_key, tl);

	test_all(tl);

	return tl;

nomem:
	set_enomem();
	return NULL;
}
#else /* WINDOWS */


#ifdef USE_DLL

typedef struct patch patch;
struct patch
{
	const char *name;
	void *func;
};


#define PATCH_FUNC(X)\
	{#X, (void *) ((uintptr_t) llalloc##X)}

static patch patch_list[] =
{
	PATCH_FUNC(free),
	PATCH_FUNC(malloc),
	PATCH_FUNC(calloc),
	PATCH_FUNC(realloc),
	PATCH_FUNC(_msize),
	PATCH_FUNC(_expand),
	PATCH_FUNC(_free_nolock),
	PATCH_FUNC(_realloc_nolock),
	PATCH_FUNC(_calloc_nolock),
	PATCH_FUNC(_msize_nolock),
	{NULL, NULL}
};

#define JMP_OP	0xE9
#define CALL_OP	0xE8
#define JMP_OFFSET(P1, P2)	(((uintptr_t)(P1)) - ((uintptr_t)(P2)) - 5)

/* Follow a call to its target */
static void *follow_call(void *p)
{
	int target;

	/* Are we pointing to a jump? */
	if ((*(unsigned char *)p) != CALL_OP) return NULL;

	target = *(int *) shift(p, 1);

	return (void *) shift(p, (uintptr_t) target + 5);
}

/* Find a jump in a dumb manner */
static void *find_call(void *p)
{
	while ((*(unsigned char *) p) != CALL_OP)
	{
		p = shift(p, 1);
	}

	return p;
}

static void patch_function(void *func, void *my_func)
{
	MEMORY_BASIC_INFORMATION mbi;

	/* Make code read/write */
	VirtualQuery(func, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize,
						PAGE_EXECUTE_READWRITE, &mbi.Protect);

	/* Patch in a jmp to our routine */
	*(unsigned char *) func = JMP_OP;
	*(unsigned *) shift(func, 1) = JMP_OFFSET(my_func, func);

	/* Reset code permissions */
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);
}

static void *init_crt_funcs(void)
{
	FARPROC func_f;
	patch *p;
	void *f;

	HMODULE library = GetModuleHandle("MSVCR90.DLL");
	if (!library) return NULL;

	func_f = GetProcAddress(library, "_callnewh");
	if (!func_f) return NULL;
	__callnewh = (typeof(__callnewh)) func_f;

	func_f = GetProcAddress(library, "?_query_new_mode@@YAHXZ");
	if (!func_f) return NULL;
	__newmode = (typeof(__newmode)) func_f;

	for (p = patch_list; p->name; p++)
	{
		func_f = GetProcAddress(library, p->name);
		if (!func_f) continue;

		patch_function((void *) (uintptr_t) func_f, p->func);
	}

	func_f = GetProcAddress(library, "calloc");
	f = (void *) (uintptr_t) func_f;

	/* Not here... don't crash */
	if (!f) goto out;

	/* Get pointer to _calloc_impl() */
	f = find_call(f);
	f = follow_call(f);

	/* Finally patch _calloc_impl */
	patch_function(f, (void *) (uintptr_t) llalloc_calloc_impl);

out:

	/* Success */
	return (void*) 1;
}


#endif

void lldebug_hook(void);
static atls *init_tls(void)
{
	DECL_PROF_FUNC;

	atls *tl;

	static void *init = (void *) 1;
	void *first = xchg_ptr(&init, NULL);

	if (!first)
	{
		/* We've already died - use free_nomem() */
		if (get_tls() == (atls *) 1) return NULL;

		/* Can we use a dead thread's tls data? */
		if (d_list)
		{
			mutex_lock(&d_lock);

			if (d_list)
			{
				/* Grab from death list */
				tl = d_list;
				d_list = tl->d_list;
				mutex_unlock(&d_lock);

				set_tls(tl);

				test_all(tl);

				/* Undocumented crt function */
				__tlregdtor(destroy_tls);

				/* Done */
				return tl;
			}
			mutex_unlock(&d_lock);
		}
	}
	else
	{
		/* Init slab */
		if (init_sldata())
		{
			init = (void *) 1;
			return NULL;
		}

		tls_index = TlsAlloc();
		if (tls_index == TLS_OUT_OF_INDEXES)
		{
			/* We can't handle this */
			init = (void *) 1;
			return NULL;
		}

#ifdef USE_DLL
		/* Initialize function pointers */
		if (!init_crt_funcs())
		{
			/* Doesn't work... fail and bail out of dll init */
			init = (void *) 1;
			return NULL;
		}
#endif
		/* Init sbrk information */
		init_sbrk_start();
	}

	/* Hack - use a full page for it */
	tl = VirtualAlloc(NULL, PAGESIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	/* Out of memory */
	if (!tl) goto nomem;

	/* Randomly cache colour the tls data */
	tl = rnd_offset(tl, PAGESIZE, sizeof(atls));

	/* Save pointer for later memory calls */
	set_tls(tl);

	/* Make sure that we can always allocate two btree nodes from within itself */
	//BUILD_ASSERT(NUM_QS * 8 + 16 >= sizeof(btree) * 2);

	/* Hack - we should use the rest of the space to init the heap... */
	tl = init_atls(tl);
	if (!tl) goto nomem;

	/* Undocumented crt function */
	__tlregdtor(destroy_tls);

	test_all(tl);

	return tl;

nomem:
	/* Try again if possible */
	if (handle_oom(PAGESIZE * 2)) return init_tls();

	return NULL;
}

#ifdef USE_DLL
BOOL DllMain(HINSTANCE h, DWORD reason, LPVOID reserved);
BOOL DllMain(HINSTANCE h, DWORD reason, LPVOID reserved)
{
	/* Silence compiler warnings */
	(void) h;
	(void) reserved;

	/* Init the memory allocator */
	if ((reason == DLL_PROCESS_ATTACH) || (reason == DLL_THREAD_ATTACH))
	{
		if (!init_tls()) return 0;
	}
#ifdef DEBUG_PROFILE
	else if(reason == DLL_PROCESS_DETACH)
	{
		ll_print_prof();
	}
#endif

	return 1;
}
#endif /* USE_DLL */

#endif /* WINDOWS */

#ifdef DEBUG_ALLOC_SLOW

/* Get node previous to loc in b */
static void test_btree_linked(btree *b, int loc)
{
	int i, j = 0;

	if (b_leaf(b)) errx(1, "No previous!\n");

	for (i = b_start(b); i != loc; i = b_next(b, i))
	{
		j++;

		if (j > BT_MAX) errx(1, "Btree node loop!\n");
	}
}

static void test_in_btree(atls *tl, btree *b)
{
	btree *bp;

	if (!b_leaf(b)) errx(1, "Unused btree object that is not a leaf\n");

	while (b->parent)
	{
		bp = b->parent;

		if (b_ptr(bp, b_pindex(b)) != b) errx(1, "Parent doesn't own %p\n", (void *) b);
		if (!bp->bsize[b_pindex(b)]) errx(1, "Parent link broken\n");

		test_btree_linked(bp, b_pindex(b));

		b = bp;
	}

	if (&tl->bheap != b) errx(1, "Heap doesn't own %p\n", (void *) b);
}

#ifdef UNUSED_FUNC
static int is_fast_node(atls *tl, btree *b)
{
	size_t bin = size2fl(b->s.size);
	slist *f;

	scan_slist(&tl->fl[bin], f)
	{
		/* Found it? */
		if (f == &b->list) return 1;
	}

	/* Didn't find it */
	return 0;
}
#endif /* UNUSED_FUNC */

static void test_blocks(atls *tl)
{
	mealloc *m;
	dlist *d;

	btree *b;

	size_t size;

	if (tl->bl.next->prev != &tl->bl) errx(1, "Block list corrupt\n");

	/* Scan blocks */
	scan_list(&tl->bl, d)
	{
		m = list_entry(mealloc, m_list, d);

		if (d->next->prev != d) errx(1, "Block list corrupt\n");

		/* Scan seps for this block */
		for (b = &m->b;; b = shift(b, size))
		{
			if (b < &m->b) errx(1, "Node before block start!\n");

			if (b->s.bs_offset & FLG_SIZE8)
			{
				size = 16;
			}
			else
			{
				size = b->s.size;

				if (!size) break;

				if (shift(b, -(uintptr_t)(b->s.bs_offset & ~15)) != m) errx(1, "Block back link broken\n");

				if (read_bs(b) != m) errx(1, "Block start corrupted\n");
			}

			check_sep(b);

			if ((size > QS_MAX) && un_used(b)) test_in_btree(tl, b);
		}
	}
}
#else
#define test_blocks(T) ((void) sizeof(T))
#endif

/* Medium allocations */

#ifdef DEBUG_ALLOC_SLOW

static unsigned test_btree_aux(atls *tl, btree *b, unsigned lsize)
{
	btree *bn;
	int n = b_start(b);
	int i = 0;
	unsigned ssize = lsize;

	unsigned short msk = -1;

	/* Size of node can be incorrect if splitting not possible */
	if (n && b->parent && !is_slab(b) && (b->s.size < sizeof(btree)))
	{
		errx(1, "Btree nodesize wrong\n");
	}

	while (n)
	{
		bn = b_ptr(b, n);

		i++;

		if (bn->parent != b) errx(1, "Btree parent incorrect\n");
		if (b_pindex(bn) != n) errx(1, "Btree p_index incorrect\n");

		if (b_mask(b) & (1 << (n - 1))) errx(1, "Used btree node marked free\n");
		msk -= (1 << (n - 1));

		/* Scan lower */
		ssize = test_btree_aux(tl, bn, ssize);

		if (b->bsize[n] < ssize) errx(1, "Btree size misordered\n");
		ssize = b->bsize[n] & ~0xff;

		if (b_leaf(bn))
		{
			if (bn->s.size*16 != ssize) errx(1, "Btree leaf size wrong\n");

			if (!un_used(bn)) errx(1, "Btree leaf marked used!\n");
		}
		else if (!is_slab(bn) && un_used(bn)) errx(1, "Btree node marked unused!\n");

		if (b_prev(b, b_next(b, n)) != n) errx(1, "prev link broken\n");

		n = b_next(b, n);

		if (i > BT_MAX) errx(1, "Btree node loop!\n");
	}

	/* Leaf node? */
	if (!i) return ssize;

	if (msk != b_mask(b)) errx(1, "Btree free mask missmatch\n");

	if (b->parent && (i <= 3)) errx(1, "Btree has too few children\n");

	return ssize & ~0xff;
}

static void test_btree(atls *tl)
{
	if ((tl->b_hgt > 100) || (tl->b_cnt > 100)) errx(1, "btree height corrupt\n");

	test_btree_aux(tl, &tl->bheap, 0);
}
#else
#define test_btree(T) ((void) sizeof(T))
#endif

static char btree_count(btree *b)
{
	int x = b_mask(b);

	/* See Wikipedia for this algorithm for popcount */
	int m1 = 0x5555;
	int m2 = 0x3333;
	int m4 = 0x0f0f;

	/* Put counts into pairs of bits */
	x -= (x >> 1) & m1;

	/* 4 bit counts */
	x = (x & m2) + ((x >> 2) & m2);

	/* Make 8bit counts */
	x = (x + (x >> 4)) & m4;

	return 16 - (x + (x >> 8));
}

static inline int btree_alloc(btree *b)
{
	int loc = ffsu(b_mask(b));

	b_mask(b) &= ~(1 << loc);

	return loc + 1;
}

static inline void btree_free(btree *b, int loc)
{
	b_mask(b) |= 1 << (loc - 1);
}

static int b_leaf(btree *b)
{
	/* Check to see if there are no children */
	return !b_start(b);
}

static inline unsigned btree_ssize(btree *b, int loc)
{
	return b->bsize[loc] & ~0xff;
}

static inline void btree_update_daughter(btree *bp, btree *b, int loc)
{
	b_ptr(bp, loc) = b;
	b->parent = bp;
	b_pindex(b) = loc;
}


/* Update my parent with my new size */
static void btree_update_psize(btree *b, unsigned ssize)
{
	int bpi = b_pindex(b);
	btree *bp;

	/* Update parent size value */
	for (bp = b->parent; bp; bp = bp->parent)
	{
		bp->bsize[bpi] &= 0xff;
		bp->bsize[bpi] += ssize;

		/* Are we done with the chain of updates? */
		if (b_next(bp, bpi)) break;

		bpi = b_pindex(bp);
	}
}

/* Forward declare */
static void btree_node_del(atls *tl, btree *b, int loc);

static void btree_merge_aux(atls *tl, btree *bl, btree *br)
{
	int i, j, k;

	int ip, pi;

	int next;

	unsigned ssize;

	btree *bp;

	int bcl, bcr;

#ifdef DEBUG_ALLOC_SLOW	
	if (!bl->parent || !br->parent) errx(1, "Trying to merge heap top\n");
	if (bl->parent != br->parent) errx(1, "Trying to merge two nodes with different parents\n");
#endif

	bcl = btree_count(bl);
	bcr = btree_count(br);

	/* Move some from neighbour to me */
	if (bcr + bcl > BT_MAX)
	{
		if (bcr > bcl)
		{
			/* Silence compiler warning */
			next = 0;

			/* Move some nodes from br to bl */
			ip = b_last(bl);

			for (j = bcr / 3, k = b_start(br); j; k = next, j--)
			{
				next = b_next(br, k);
				i = btree_alloc(bl);

				/* Add in new node */
				bl->bsize[i] = br->bsize[k];
				b_next(bl, ip) = i;
				b_prev(bl, i) = ip;
				btree_update_daughter(bl, b_ptr(br, k), i);
				ip = i;

				/* Remove old node */
				btree_free(br, k);
			}
			b_next(bl, ip) = 0;
			ssize = bl->bsize[ip];
			b_last(bl) = ip;

			b_start(br) = next;
			b_prev(br, next) = 0;

			/* Notify parent of my new size */
			btree_update_psize(bl, ssize);

			return;
		}

		/* Scan 2/3rds of the way through bl */
		for (j = bcl / 3, ip = b_last(bl); j; ip = b_prev(bl, ip), j--);

		k = b_start(br);
		ssize = btree_ssize(bl, ip);
		j = b_next(bl, ip);
		b_next(bl, ip) = 0;
		b_last(bl) = ip;

		/* Copy remainder to br, deleting as we go */
		for (ip = 0; j; j = next)
		{
			next = b_next(bl, j);
			i = btree_alloc(br);

			/* Add in new node */
			br->bsize[i] = bl->bsize[j];
			b_next(br, ip) = i;
			b_prev(br, i) = ip;
			ip = i;
			btree_update_daughter(br, b_ptr(bl, j), i);

			/* Remove old node */
			btree_free(bl, j);
		}

		/* link to remainder of nodes in br */
		b_next(br, ip) = k;
		b_prev(br, k) = ip;

		/* Notify parent of my new size */
		btree_update_psize(bl, ssize);

		return;
	}

	/* merge bl into br and delete bl */
	ip = 0;
	k = b_start(br);
	for (j = b_start(bl); j; j = b_next(bl, j))
	{
		i = btree_alloc(br);

		/* Add in new node */
		br->bsize[i] = bl->bsize[j];
		b_next(br, ip) = i;
		b_prev(br, i) = ip;
		ip = i;

		btree_update_daughter(br, b_ptr(bl, j), i);
	}

#ifdef DEBUG_ALLOC_SLOW
	if (!ip) errx(1, "Empty left node?\n");
#endif

	b_next(br, ip) = k;
	b_prev(br, k) = ip;

	/* Save these so we can delete */
	bp = bl->parent;
	pi = b_pindex(bl);

	/* Delete this node when done */
	local_free(tl, &bl->data);

	/* Delete bl */
	btree_node_del(tl, bp, pi);

	/* Tail recursion */
}

static noinline void btree_node_del_aux(atls *tl, btree *b, btree *bp)
{
	size_t prev, next;

	int pi = b_pindex(b);

	int i;

#ifdef DEBUG_ALLOC_SLOW
	if (!pi) errx(1, "Corrupted leaf\n");
#endif

	/* Rebalance if possible */
	next = b_next(bp, pi);
	if (next)
	{
		/* Merge with next node */
		btree_merge_aux(tl, b, b_ptr(bp, next));

		return;
	}

	prev = b_prev(bp, pi);
	if (prev)
	{
		/* Merge with previous node */
		btree_merge_aux(tl, b_ptr(bp, prev), b);

		return;
	}

	/* Just me here? */
#ifdef DEBUG_ALLOC_SLOW
	if (bp != &tl->bheap) errx(1, "Invalid node count\n");
#endif

	/* Move my data to the top of the btree */
	b_start(bp) = b_start(b);
	b_last(bp) = b_last(b);
	b_mask(bp) = b_mask(b);

	/* Init alloced list */
	for (i = b_start(b); i; i = b_next(b, i))
	{
		bp->bsize[i] = b->bsize[i];
		bp->prev[i] = b->prev[i];
		btree_update_daughter(bp, b_ptr(b, i), i);
	}

	/* Btree is shorter */
	tl->b_hgt--;

	/* Delete this node when done */
	local_free(tl, &b->data);

	/* Prevent having too many spare nodes which can cause fragmentation */
	if (tl->b_hgt < tl->b_cnt)
	{
		/* Pop off the extra node */
		void *st = slist_rem(&tl->btree_freenode);
		b = list_entry(btree, data, st);

		/* Delete it */
		local_free(tl, &b->data);
		tl->b_cnt--;
	}
}

/* Delete node at location loc */
static void btree_node_del(atls *tl, btree *b, int loc)
{
	size_t prev = b_prev(b, loc);
	size_t next = b_next(b, loc);

	btree *bp = b->parent;

	b_next(b, prev) = next;
	b_prev(b, next) = prev;

	/* Add to free list */
	btree_free(b, loc);

	/* If top - am done */
	if (!bp) return;

	/* Was last? */
	if (!next)
	{
		/* Update parent size (we know there must be at least one other node) */
		btree_update_psize(b, btree_ssize(b, prev));
	}

	/* Still not empty enough btree_count(b) > 3) (faster than popcount) */
	if (b_next(b, b_next(b, b_next(b, b_start(b))))) return;

	btree_node_del_aux(tl, b, bp);
}

static __pure inline btree *btree_search(atls *tl, unsigned ssize)
{
	btree *b = &tl->bheap;
	size_t i = b_start(b);

	while (i)
	{
		/* Scan level below? */
		if (b->bsize[i] < ssize)
		{
			i = b_next(b, i);
		}
		else
		{
			b = b_ptr(b, i);
			i = b_start(b);
		}
	}

	return b;
}

/* Return node of size ssize if possible */
static btree *btree_remove(atls *tl, unsigned ssize)
{
	btree *b = btree_search(tl, ssize);

	/* Nothing? */
	if (b == &tl->bheap) return NULL;

	/* Disconnect it */
	btree_node_del(tl, b->parent, b_pindex(b));

	return b;
}

/* Find space for node of size ssize */
static btree *btree_find(atls *tl, unsigned ssize, int *ipv)
{
	btree *b = btree_search(tl, ssize);
	btree *bp = &tl->bheap;

	if (b != bp)
	{
		bp = b->parent;
		*ipv = b_prev(bp, b_pindex(b));
		return bp;
	}

	/* Nothing in btree? */
	if (b_leaf(b)) return bp;

	/* We are larger than anything */
	do
	{
		/* Scan level below */
		b = b_ptr(b, (int) b_last(b));
	}
	while (!b_leaf(b));

	*ipv = b_pindex(b);

	return b->parent;
}

/* Cleanup - make sure we have enough temp nodes */
static noinline void btree_cleanup(atls *tl)
{
	/* First try to use slab allocations to prevent fragmentation */
	while (tl->b_hgt > tl->b_cnt)
	{
		slist *s = slab_alloc_safe(tl, sizeof(btree) - SEPSIZE);

		/* Fall back to in-btree allocations */
		if (!s) goto use_btree;

		slist_add(&tl->btree_freenode, s);
		tl->b_cnt++;
	}

	return;

use_btree:

	/* In-btree allocation by manual memory manipulation */
	while (tl->b_hgt > tl->b_cnt)
	{
		size_t num, msize;

		unsigned i;

		btree *br;

		unsigned offset;

		/* Get smallest allocation in btree */
		btree *b = btree_remove(tl, 0);

		msize = b->s.size;

		/* How many nodes can fit? */
		num = msize / sizeof(btree);

		/* As many as required */
		if (num > tl->b_hgt - tl->b_cnt) num = tl->b_hgt - tl->b_cnt;

		/* Prevent recursion by always adding at least one node */
		if (num < 1) num = 1;

		/* We are using this */
		set_used(b, msize);
		offset = b->s.bs_offset & ~15;

		for (i = 0; i < num; i++)
		{
			br = shift(b, sizeof(btree));
			b->s.size = sizeof(btree);
			offset += sizeof(btree);
			if (i != num - 1) br->s.bs_offset = offset;
			msize -= sizeof(btree);

			slist_add(&tl->btree_freenode, &b->list);
			b = br;
		}

		tl->b_cnt += num;

		/* Any room left? */
		if (!msize) continue;

		/* Free remaining fragment */
		b->s.size = msize;
		b->s.bs_offset = offset;
		fast_free(tl, b, msize);
	}
}

static void btree_node_insert(atls *tl, btree *b, int loc, unsigned ssize, btree *node);

/* Split myself */
static noinline void btree_node_insert_aux(atls *tl, btree *b, int loc, unsigned ssize, btree *node)
{
	btree *tmp, *tmp2, *bp;

	unsigned bsize = 0, tsize;

	int i, j, bn;

	void *st;

	size_t new;
	int inserted = 0;
	size_t next;

	/* New node */
	st = slist_rem(&tl->btree_freenode);
	tmp = list_entry(btree, data, st);
	tl->b_cnt--;

	/* Clear it */
	memset(&tmp->data, 0, offsetof(btree, prev) - SEPSIZE);

#if 0
	/* Hack - get daughter testing to work */
	tmp->parent = (btree *) 1;
#endif

	/* Special case - insert at start? */
	if (!loc)
	{
		/* Insert at the beginning */
		tmp->bsize[1] = ssize + 2;
		tmp->prev[1] = 0;
		btree_update_daughter(tmp, node, 1);
		inserted = 1;

		/* Copy things below median here */
		for (i = 2, j = b_start(b); i <= BT_MAX/2; i++, j = bn)
		{
			bn = b_next(b, j);

			tmp->bsize[i] = btree_ssize(b, j) + i + 1;
			tmp->prev[i] = i - 1;
			btree_update_daughter(tmp, b_ptr(b, j), i);

			btree_free(b, j);
		}
	}
	else
	{
		/* Copy things below median here */
		for (i = 1, j = b_start(b); i <= BT_MAX/2; i++, j = bn)
		{
			bn = b_next(b, j);

			tmp->bsize[i] = btree_ssize(b, j) + i + 1;
			tmp->prev[i] = i - 1;
			btree_update_daughter(tmp, b_ptr(b, j), i);

			btree_free(b, j);

			/* Need to insert new node? */
			if (j == loc)
			{
				i++;
				tmp->bsize[i] = ssize + i + 1;
				tmp->prev[i] = i - 1;
				btree_update_daughter(tmp, node, i);
				inserted = 1;
			}
		}
	}
	b_start(b) = j;
	b_prev(b, j) = 0;

	/* Finish initialization of new node */
	b_start(tmp) = 1;
	b_last(tmp) = i - 1;
	b_next(tmp, i - 1) = 0;
	tsize = tmp->bsize[i - 1];
	b_mask(tmp) = -(1 << (i - 1));

	/* Need to insert in remainder? */
	if (!inserted)
	{
		next = b_next(b, loc);

		/* We have space - add it */
		new = btree_alloc(b);

		b->bsize[new] = ssize + next;
		b_prev(b, next) = new;
		b_next(b, loc) = new;
		b_prev(b, new) = loc;

		/* Am I last?  Need to update parents */
		if (!next) btree_update_psize(b, ssize);

		btree_update_daughter(b, node, new);
	}

	bp = b->parent;
	if (bp)
	{
		/* Get node previous to myself above */
		size_t ip = b_prev(bp, b_pindex(b));

		/* Easy - just insert into the parent, tail recurse */
		btree_node_insert(tl, bp, ip, tsize, tmp);

		return;
	}

	/* I'm the top node */

	/* New node */
	st = slist_rem(&tl->btree_freenode);
	tmp2 = list_entry(btree, data, st);
	tl->b_cnt--;

	/* btree is taller */
	tl->b_hgt++;

	/* Copy b into this -shouldn't need this, use allocated root instead */
	memcpy(&tmp2->data, &b->data, sizeof(btree) - SEPSIZE);

	for (i = b_start(b); i; i = b_next(b, i))
	{
		b_ptr(b, i)->parent = tmp2;
		bsize = b->bsize[i];
	}

	/* Init b */
	b->bsize[1] = tsize + 2;
	b->bsize[2] = bsize & ~0xff;
	b_ptr(b, 1) = tmp;
	b_ptr(b, 2) = tmp2;
	b_prev(b, 0) = 2;
	b_prev(b, 1) = 0;
	b_prev(b, 2) = 1;
	b_start(b) = 1;
	b_mask(b) = -4;
	b->parent = NULL;

	/* Make links */
	tmp->parent = b;
	tmp2->parent = b;
	b_pindex(tmp) = 1;
	b_pindex(tmp2) = 2;
}

static void btree_node_insert(atls *tl, btree *b, int loc, unsigned ssize, btree *node)
{
	size_t new;
	size_t next;

#ifdef DEBUG_ALLOC_SLOW
	if (ssize & 0xff) errx(1, "ssize not clean\n");
#endif

	if (!b_mask(b))
	{
		btree_node_insert_aux(tl, b, loc, ssize, node);

		return;
	}

	/* We have space - add it */
	new = btree_alloc(b);

	next = b_next(b, loc);
	b->bsize[new] = ssize + next;
	b_prev(b, next) = new;
	b_next(b, loc) = new;
	b_prev(b, new) = loc;

	/* Am I last?  Need to update parents */
	if (!next) btree_update_psize(b, ssize);

	btree_update_daughter(b, node, new);
}

static void btree_insert(atls *tl, btree *n, size_t size)
{
	int ip = 0;

	/* Convert to internal size (upper 24bits of 32bit bsize) */
	unsigned ssize = size * 16;

	/* First find where to put it, splitting to make room */
	btree *b = btree_find(tl, ssize, &ip);

#ifdef DEBUG_ALLOC_SLOW
	if (!un_used(n)) errx(1, "inserting a used node\n");
	if (size != n->s.size) errx(1, "size missmatch\n");
#endif

	/* Make a leaf node */
	//b_start(n) = 0;

	/* Hack - do the above more efficiently */
	n->bsize[0] = 0;

	/* Insert it */
	btree_node_insert(tl, b, ip, ssize, n);

	btree_cleanup(tl);
}

static noinline btree *btree_get(atls *tl, unsigned size)
{
	DECL_PROF_FUNC;

	unsigned ssize = size * 16;
	btree *b;

	b = btree_remove(tl, ssize);

	if (b)
	{
		/* Do not try to merge with me - I'm already taken! */
		set_used(b, b->s.size);
	}

	return b;
}

/* Dumb nlogn merge.  Avoids recursion though */
static void btree_merge(atls *tl1, atls *tl2)
{
	btree *b;

	slist *s, *sn;

	while ((b = btree_remove(tl2, 0)))
	{
		btree_insert(tl1, b, b->s.size);
	}

	/* Update allocated size */
	tl1->a_alloced += tl2->a_alloced;

	/* Free the old extra btree nodes */
	scan_slist_safe(&tl2->btree_freenode, s, sn)
	{
		b = list_entry(btree, data, s);

		/* Delete it */
		local_free(tl1, &b->data);
	}

	tl2->b_cnt = 0;
}

/* Count number of nodes + leaves in the btree recursively */
static __pure int count_btree(btree *b)
{
	int i, count = 1;

	for (i = b_start(b); i; i = b_next(b, i))
	{
		count += count_btree(b_ptr(b, i));
	}

	return count;
}

static __pure int count_btree_space(btree *b)
{
	int i, count = 0;

	if (b_leaf(b)) return b->s.size - PTRSIZE;

	for (i = b_start(b); i; i = b_next(b, i))
	{
		count += count_btree_space(b_ptr(b, i));
	}

	return count;
}


#ifdef DEBUG_ALLOC_SLOW

/* Check double list constraints */
static void test_double_lists(atls *tl)
{
	btree *b;
	dlist *d, *dn;

	unsigned i;

	for (i = 1; i < NUM_QS; i++)
	{
		if (tl->qs[i].next->prev != &tl->qs[i]) errx(1, "First double link broken\n");

		scan_list_safe(&tl->qs[i], d, dn)
		{
			b = list_entry(btree, list, d);
			check_sep(b);

			if (!un_used(b)) errx(1, "False used\n");
			if (b->s.size != (i+1)*16) errx(1, "Wrong sized double link\n");
			if (b->s.bs_offset & FLG_SIZE8) errx(1, "flag size wrong\n");

			if (dn->prev != d) errx(1, "Back-link broken\n");
		}
	}

	if (tl->q_mask & (1ULL << 63)) errx(1, "double list last bit set\n");
}

#else
#define test_double_lists(T) ((void) sizeof(T))
#endif


#ifdef DEBUG_ALLOC_SLOW
/* Test small list constraints */
static void test_small_list(atls *tl)
{
	btree *b, *bn;

	btree *q8 = get_q8(tl);

	if (small_prev(small_next(q8)) != q8) errx(1, "First link broken\n");

	for (b = small_next(q8); b != q8; b = bn)
	{
		check_sep(b);
		bn = small_next(b);

		if (!(b->s.bs_offset & FLG_SIZE8)) errx(1, "Wrong sized small link\n");
		if (!un_used(b)) errx(1, "False used\n");
		if (small_prev(bn) != b) errx(1, "Back-link broken\n");
	}
}
#else
#define test_small_list(T) ((void) sizeof(T))
#endif

/* Add to end of small list */
static void small_insert(atls *tl, btree *b)
{
	btree *q8 = get_q8(tl);
	btree *qp;

	/* Set flag */
	set_size8(b);

	qp = small_prev(q8);

	set_small_prev(b, qp);
	set_small_next(qp, b);

	set_small_next(b, q8);
	set_small_prev(q8, b);
}

static void small_remove(btree *b)
{
	btree *qn = small_next(b);
	btree *qp = small_prev(b);

	set_small_next(qp, qn);
	set_small_prev(qn, qp);

	/* Clear flag */
	unset_size8(b);
}

static btree *small_del_first(atls *tl)
{
	btree *q8 = get_q8(tl);
	btree *b = small_next(q8);
	btree *qn = small_next(b);

	/* List is empty */
	if (b == q8) return NULL;

	/* Dequeue b */
	set_small_next(q8, qn);
	set_small_prev(qn, q8);

	/* Clear flag */
	unset_size8(b);

	return b;
}

static void small_merge(atls *tl1, atls *tl2)
{
	btree *q81 = get_q8(tl1);
	btree *q82 = get_q8(tl2);

	btree *q1p = small_prev(q81);
	btree *q2n = small_next(q82);
	btree *q2p = small_prev(q82);

	/* Don't need to do anything if adding an empty list */
	if (q2n == q82) return;

	set_small_next(q1p, q2n);
	set_small_prev(q2n, q1p);

	set_small_prev(q81, q2p);
	set_small_next(q2p, q81);
}

/* Slab implementation */

static sbheader *slab_start(void *p)
{
	return (sbheader *) (-SLABSIZE & (uintptr_t) p);
}

#ifdef DEBUG_ALLOC_SLOW

static void test_slab(atls *tl)
{
	int i;

	dlist *d, *dn;

	for (i = 0; i < NUM_SB; i++)
	{
		scan_list_safe(&tl->slab[i], d, dn)
		{
			if (dn->prev != d) errx(1, "Back-link broken\n");
		}
	}

	scan_list_safe(&tl->slab_full, d, dn)
	{
		if (dn->prev != d) errx(1, "Back-link broken\n");
	}
}
#else
#define test_slab(T) ((void) sizeof(T))
#endif


static freesb *slab_alloc_chunk(atls *tl)
{
	DECL_PROF_FUNC;

	freesb *fsb;

	size_t alloc_amount = SLABSIZE * (SLABBMAX + 1);
	size_t sbrk_end;

	unsigned i;
	unsigned alloced = SLABBMAX;

	/* Handle oom more efficiently */
	if (sbrk_oom) return NULL;

	/* Make sure percpu value isn't too big */
	if (tl->percpu_hash > cpu_total)
	{
		tl->percpu_hash %= cpu_total;
	}

	/* Find an unlocked list with something in it */
	for (i = tl->percpu_hash; i < cpu_total; i++)
	{
		if (pc_slab[i].list && !mutex_trylock(&pc_slab[i].m))
		{
			if (pc_slab[i].list)
			{
				fsb = pc_slab[i].list;
				pc_slab[i].list = fsb->next;

				mutex_unlock(&pc_slab[i].m);
#ifdef WINDOWS
				/* Reallow use of pages */
				for (i = 0; i < fsb->count; i++)
				{
					VirtualAlloc(fsb->blocks[i], SLABSIZE, MEM_COMMIT, PAGE_READWRITE);
				}
#endif

				return fsb;
			}

			mutex_unlock(&pc_slab[i].m);
		}
	}

	for (i = 0; i < tl->percpu_hash; i++)
	{
		if (pc_slab[i].list && !mutex_trylock(&pc_slab[i].m))
		{
			if (pc_slab[i].list)
			{
				fsb = pc_slab[i].list;
				pc_slab[i].list = fsb->next;

				mutex_unlock(&pc_slab[i].m);
#ifdef WINDOWS
				/* Reallow use of pages */
				for (i = 0; i < fsb->count; i++)
				{
					VirtualAlloc(fsb->blocks[i], SLABSIZE, MEM_COMMIT, PAGE_READWRITE);
				}
#endif

				return fsb;
			}

			mutex_unlock(&pc_slab[i].m);
		}
	}

	mutex_lock(&sb_lock);

	sbrk_end = sbrk_start + sbrk_size;

	/* Try to realign with SLABSIZE boundaries */
	if (sbrk_end & (SLABSIZE - 1))
	{
		alloc_amount += SLABSIZE - (sbrk_end & (SLABSIZE - 1));
	}

	fsb = sbrk(alloc_amount);

	if (fsb == MAP_FAILED)
	{
		/* Too much to allocate - fall back on mmap */
		sbrk_oom = 1;
		mutex_unlock(&sb_lock);

		return NULL;
	}

	/* Update sbrk information */
	sbrk_size = alloc_amount + (uintptr_t) fsb - sbrk_start;

	mutex_unlock(&sb_lock);

	/* Are we improperly aligned? */
	if ((SLABSIZE - 1) & (uintptr_t) fsb)
	{
		/* Realign myself (wastes memory) */
		freesb *fsb_new = (freesb *) slab_start(shift(fsb, SLABSIZE - 1));

		/* Did we shift too much? */
		if ((uintptr_t) fsb_new - (uintptr_t) fsb > alloc_amount - SLABSIZE * (SLABBMAX + 1))
		{
			alloced--;
		}

		fsb = fsb_new;
	}

	/* Fill in details */
	for (i = 0; i < alloced; i++)
	{
		fsb->blocks[i] = shift(fsb, SLABSIZE * (i + 1));
	}
	fsb->count = alloced;

	return fsb;
}

static noinline void slab_free_chunk(atls *tl, freesb *fsb)
{
	DECL_PROF_FUNC;

	unsigned i;

	/* Mark memory as unused */
	for (i = 0; i < fsb->count; i++)
	{
#ifdef WINDOWS
		VirtualFree(fsb->blocks[i], SLABSIZE, MEM_DECOMMIT);
#else
		madvise(fsb->blocks[i], SLABSIZE, MADV_DONTNEED);
#endif
	}

	/* Make sure percpu value isn't too big */
	if (tl->percpu_hash > cpu_total)
	{
		tl->percpu_hash %= cpu_total;
	}

	/* First trylock everything, to find something that works */
	for (i = tl->percpu_hash; i < cpu_total; i++)
	{
		if (!mutex_trylock(&pc_slab[i].m))
		{
			tl->percpu_hash = i;
			goto success;
		}
	}

	for (i = 0; i < tl->percpu_hash; i++)
	{
		if (!mutex_trylock(&pc_slab[i].m))
		{
			tl->percpu_hash = i;
			goto success;
		}
	}

	/* Failure - too much contention, just use our current value */
	i = tl->percpu_hash;
	mutex_lock(&pc_slab[i].m);

success:
	tl->percpu_hash = i;
	fsb->next = pc_slab[i].list;
	pc_slab[i].list = fsb;
	mutex_unlock(&pc_slab[i].m);
}


static sbheader *slab_alloc_block(atls *tl)
{
	freesb *fsb;
	sbheader *sb;

	/* Make sure we have empty blocks */
	if (!tl->slab_chunk)
	{
		tl->slab_chunk = slab_alloc_chunk(tl);
		if (!tl->slab_chunk) return NULL;
	}

	fsb = tl->slab_chunk;

	if (!fsb->count)
	{
		sb = (sbheader *) fsb;

		tl->slab_chunk = NULL;

		/* Prevent reuse of this overwritten block */
		sb->size = 0;

		return sb;
	}

	fsb->count--;
	sb = fsb->blocks[fsb->count];

	return sb;
}

static void slab_free_block(atls *tl, sbheader *sb)
{
	freesb *ofsb = tl->slab_chunk;
	freesb *fsb = (freesb *) sb;

	if (ofsb)
	{
		if (ofsb->count < SLABBMAX - 1)
		{
			ofsb->blocks[ofsb->count] = sb;
			ofsb->count++;
			return;
		}

		/* Simplest case - no chunk yet */
		fsb->count = 0;
		tl->slab_chunk = fsb;

		slab_free_chunk(tl, ofsb);

		return;
	}

	/* Simplest case - no chunk yet */
	fsb->count = 0;
	tl->slab_chunk = fsb;
}

static int init_sldata(void)
{
	unsigned i;

	/* Init total number of cpus */
	cpu_total = cpu_num();

	/* Init per-cpu free slab lists */
	pc_slab = big_alloc_aux(page_align(cpu_total * 64));
	if (!pc_slab) return 1;

	/*
	 * Initialized mutexes have state zero, and initialized lists are NULL
	 * so we don't have to do anything to pc_slab to finish initializing it.
	 */

	/* Calculate slab total sizes so we avoid a division later */
	for (i = 1; i < NUM_SB; i++)
	{
		unsigned size = i * 16;

		/* total size taken by all blocks */
		sltotal[i] = ((SLABSIZE - offsetof(sbheader, data))/size) * size;
	}

	return 0;
}

static sbheader *slab_create(atls *tl, dlist *slab, unsigned size)
{
	DECL_PROF_FUNC;

	unsigned index = size/16;
	unsigned total = sltotal[index];

	uintptr_t offset;

	sbheader *sb = slab_alloc_block(tl);
	if (!sb) return NULL;

	/* Normalize size */
	size = index * 16;

	/* Fill in details */
	sb->tail = &tl->tail;

	dlist_add(slab, &sb->list);

	/* Already initialized? */
	if (sb->size == size) return sb;

	sb->used = 0;
	sb->size = size;

	/* Calculate offset */
	if ((size == 64) || (size == 256))
	{
		/* Make cacheline-aligned */
		offset = (uintptr_t) sb + 128 + 1;
	}
	else
	{
		void *tmp;

		/* Start of region */
		offset = (-16 & (uintptr_t) &sb->data);

		/* Randomize offset */
		tmp = rnd_offset((void *) offset, (uintptr_t) sb + SLABSIZE - (uintptr_t) offset, total);

		offset = (uintptr_t) tmp + 1;
	}

#ifdef DEBUG_ALLOC
	if (offset - 1 + total - (uintptr_t) sb > SLABSIZE) errx(1, "slab overflow\n");
#endif

	sb->first = offset;
	sb->max = (uintptr_t) sb + SLABSIZE - sb->size;

	return sb;
}

static void slab_free(atls *tl, void *p)
{
	DECL_PROF_FUNC;

	sbheader *sb = slab_start(p);

	/* Do I own this? */
	if (unlikely(sb->tail != &tl->tail))
	{
		/* Hack wrt mealloc */
		prepend_queue(p, tl, &sb->tail);

		return;
	}

	/* Add to this slab's free list */
	*(uintptr_t *)p = sb->first;
	sb->first = (uintptr_t) p;

	sb->used--;
	if (!sb->used)
	{
		/* If I am the only one in the partial list, don't bother to delete */
		if (sb->list.next == sb->list.prev) return;

		dlist_del(&sb->list);

		/* Free it */
		slab_free_block(tl, sb);
	}
}

static void *slab_alloc(atls *tl, size_t size);
static noinline void *slab_alloc_nolist(size_t size, dlist *slab, atls *tl)
{
	DECL_PROF_FUNC;

	void *res;

	/* Out of line zero-check */
	if (!size)
	{
		size++;
	}
	else
	{
		/* Scan queue if we have nothing left */
		if (!tl->slab_chunk)
		{
			scan_queue(tl, &tl->head, 0);
		}

		/* Still nothing? */
		if (dlist_empty(slab))
		{
			if (!slab_create(tl, slab, size + 15))
			{
				goto again;
			}
		}
	}

	/* We have something to use */
	res = slab_alloc(tl, size);
	if (res) return res;

again:

	size = sep_align(size);
	return local_alloc(tl, size);
}

static void *slab_alloc_aux(atls *tl, dlist *slab)
{
	DECL_PROF_FUNC;

	/* Get sbheader */
	sbheader *sb = list_entry(sbheader, list, slab->next);

	uintptr_t p = sb->first;

	sb->used++;

	if (!(p & 1))
	{
		sb->first = *(uintptr_t *) (void *) p;

		if (!sb->first) goto done;
	}
	else
	{
		p--;
		sb->first += sb->size;
		if (sb->first > sb->max)
		{
			sb->first = 0;

			goto done;
		}
	}

	return (void *) p;

done:
	/* Move to full list */
	dlist_del(&sb->list);
	dlist_add(&tl->slab_full, &sb->list);

	return (void *) p;
}

static void *slab_alloc(atls *tl, size_t size)
{
	dlist *slab;

	size_t nsize = size + 15;

#ifdef DEBUG_NO_SLAB
	size = sep_align(size);
	return local_alloc(tl, size);
#endif

	/* Get slab */
#ifdef __x86_64__
	slab = shift(&tl->slab[0], nsize & ~15);
#else
	slab = shift(&tl->slab[0], (nsize & ~15) / 2);
#endif

	if (dlist_empty(slab)) return slab_alloc_nolist(size, slab, tl);

	return slab_alloc_aux(tl, slab);
}

/* Same as above, but fail if we can't quickly allocate */
static void *slab_alloc_safe(atls *tl, size_t size)
{
	dlist *slab;

#ifdef DEBUG_NO_SLAB
	return NULL;
#endif

	size += 15;

	/* Get slab */
#ifdef __x86_64__
	slab = shift(&tl->slab[0], size & ~15);
#else
	slab = shift(&tl->slab[0], (size & ~15) / 2);
#endif

	/* Fail if we can't quickly allocate (don't call scan_queue) */
	if (dlist_empty(slab) && !slab_create(tl, slab, size)) return NULL;

	return slab_alloc_aux(tl, slab);
}

static noinline void *slab_zalloc(atls *tl, size_t size)
{
	void *p = slab_alloc(tl, size);
	if (p) return memset(p, 0, size);

	size = sep_align(size);

	p = fast_alloc(tl, size);
	if (!p)
	{
		tl->callocable = 0;
		p = slow_alloc(tl, size);

		/* No need to memset? */
		if (!p || tl->callocable)
		{
			return p;
		}
	}

	/* Success */
	return memset(p, 0, size - 8);
}

static void slab_merge(atls *tl1, atls *tl2)
{
	int i;
	dlist *d, *dn;

	/* Merge partial slabs */
	for (i = 0; i < NUM_SB; i++)
	{
		/* Update all the tail pointers */
		scan_list_safe(&tl2->slab[i], d, dn)
		{
			sbheader *sb = list_entry(sbheader, list, d);
			sb->tail = &tl1->tail;

			/* There may be one empty slab in this slot */
			if (!sb->used)
			{
				/* Move to full list */
				dlist_del(&sb->list);
				dlist_add(&tl1->slab_full, &sb->list);
			}
		}

		dlist_merge(&tl1->slab[i], &tl2->slab[i]);
	}

	/* Merge full and empty slabs */

	/* Update all the tail pointers */
	scan_list(&tl2->slab_full, d)
	{
		sbheader *sb = list_entry(sbheader, list, d);
		sb->tail = &tl1->tail;
	}

	dlist_merge(&tl1->slab_full, &tl2->slab_full);

	/* Get rid of empty pages */
	if (tl2->slab_chunk) slab_free_chunk(tl1, tl2->slab_chunk);
}

static void local_free(atls *tl, void *p)
{
	if (is_slab(p))
	{
		slab_free(tl, p);
	}
	else
	{
		btree *b = CONTAINER(btree, data, p);
		fast_free(tl, b, b->s.size);
	}
}

static void *local_alloc(atls *tl, size_t size)
{
	DECL_PROF_FUNC;

	void *p = fast_alloc(tl, size);
	if (p) return p;

	return slow_alloc(tl, size);
}

static void test_all(atls *tl)
{
	test_fast_lists(tl);
	test_double_lists(tl);
	test_small_list(tl);
	test_btree(tl);
	test_queue(tl);
	test_slab(tl);
	test_blocks(tl);
}

static void block_list_merge(atls *tl1, atls *tl2)
{
	mealloc *m;
	dlist *d;

	/* Scan block list, and update all tail pointers */
	scan_list(&tl2->bl, d)
	{
		m = list_entry(mealloc, m_list, d);
		m->tail = &tl1->tail;
	}

	dlist_merge(&tl1->bl, &tl2->bl);
}

static void atls_merge(atls *tl1, atls *tl2)
{
	int i;

	/* Merge block lists so others know about us */
	block_list_merge(tl1, tl2);

	/* Then merge the btrees */
	btree_merge(tl1, tl2);

	/* Merge the fast lists */
	fast_merge(tl1, tl2);

	/* Merge the slabs */
	slab_merge(tl1, tl2);

	/* Then the double links */
	for (i = 1; i < NUM_QS; i++)
	{
		dlist_merge(&tl1->qs[i], &tl2->qs[i]);
	}

	/* Finally the small list */
	small_merge(tl1, tl2);

	test_all(tl1);
}

static btree *split_node_rhs(atls *tl, btree *b, size_t t_size, size_t msize)
{
	size_t r_size = t_size - msize;

	btree *bm = shift(b, msize);

#ifdef DEBUG_ALLOC_SLOW	
	if (t_size != b->s.size) errx(1, "size missmatch\n");
	if (msize > t_size) errx(1, "too big to fit in split\n");
	check_sep(b);
#endif

	/* Too large to split profitably? */
	if (!r_size) return b;

	/* Update local size */
	b->s.size = msize;

	/* Create middle seperator */
	set_sep(bm, r_size, b);

	check_sep(bm);

	/* Make sure to try to use remainder */
	fast_free(tl, b, msize);

	/* Paranoia */
	check_sep(b);
	check_sep(bm);

	/* Used for when right node is used */
	return bm;
}

static always_inline void *split_node(atls *tl, btree *b, size_t t_size, size_t msize)
{
	size_t r_size = t_size - msize;

	btree *bm = shift(b, msize);

#ifdef DEBUG_ALLOC_SLOW	
	if (t_size != b->s.size) errx(1, "size missmatch\n");
	if (msize > t_size) errx(1, "too big to fit in split\n");
	check_sep(b);
#endif

	/* Too large to split profitably? */
	if (r_size * 4 < msize)
	{
		/* Used this whole */
		return &b->data;
	}

	/* Update local size */
	b->s.size = msize;

	/* Create middle seperator */
	set_sep(bm, r_size, b);

	check_sep(bm);

	/* Make sure to try to use remainder */
	fast_free(tl, bm, r_size);

	/* Paranoia */
	check_sep(b);
	check_sep(bm);

	return &b->data;
}

static void node_insert(atls *tl, btree *b)
{
	size_t size = b->s.size;

	if (size > QS_MAX)
	{
		/* Insert new segment into btree */
		btree_insert(tl, b, size);

		return;
	}

	if (size == 16)
	{
		small_insert(tl, b);

		return;
	}

	dlist_add(MYSIZE_TO_PTR(tl, size), &b->list2);
	tl->q_mask |= 1ULL << ((size - 8) / 16);
}

/* Complete merge */
static void merge_node_aux(atls *tl, btree *bl)
{
	DECL_PROF_FUNC;

	size_t msize = bl->s.size;

	/* Are we the only element in the allocation? */
	btree *br = shift(bl, msize);

	mealloc *m;

	/* Is block empty? */
	if ((bl->s.bs_offset >= HEADERSIZE) || br->s.size || (msize * 4 > tl->a_alloced)) goto save;

	/* Save a block, if it is big enough to use for a pending allocation */
	if (tl->s_wanted && (tl->s_wanted <= bl->s.size))
	{
		/* No longer wanted */
		tl->s_wanted = 0;

		goto save;
	}

	/* Get header */
	m = page_start(bl);

	/* Remove from the list */
	dlist_del(&m->m_list);

	/* Size of block */
	msize = m->b.s.size + HEADERSIZE;

#ifdef DEBUG_ALLOC_SLOW
	if (msize & (PAGESIZE - 1)) errx(1, "big block size incorrect\n");
#endif

	tl->a_alloced -= msize;

	big_freed(m, msize);

#ifndef WINDOWS
	munmap(m, msize);
#else
	VirtualFree(m, 0, MEM_RELEASE);
#endif
	return;

save:
	/* element is unallocated */
	set_unused(bl, br);

	/* Insert into correct data structure */
	node_insert(tl, bl);
}

/* Merge a node with unallocated neighbours + insert into free list */
static void merge_node(atls *tl, void *p)
{
	DECL_PROF_FUNC;

	btree *b = CONTAINER(btree, data, p);
	btree *bl = b, *br = shift(b, b->s.size);

	size_t tsize;

#ifdef DEBUG_ALLOC_SLOW
	if (un_used(b)) errx(1, "merging unused node");
#endif

	/* Test right */
	if (un_used(br))
	{
		if (br->s.bs_offset & FLG_SIZE8)
		{
			small_remove(br);
			tsize = 16;
		}
		else
		{
			tsize = br->s.size;

			if (tsize > QS_MAX)
			{
				btree_node_del(tl, br->parent, b_pindex(br));
			}
			else
			{
				dlist_del(&br->list2);
			}
		}

		/* Fixup sizes */
		b->s.size += tsize;
	}

	/* Test left */
	if (left_unused(b))
	{
		if (b->s.bs_offset & FLG_LSIZE8)
		{
			bl = shift(b, -(uintptr_t)16);

			small_remove(bl);
		}
		else
		{
			bl = b->s.left;

			if (bl->s.size > QS_MAX)
			{
				btree_node_del(tl, bl->parent, b_pindex(bl));
			}
			else
			{
				dlist_del(&bl->list2);
			}
		}

		/* Fixup sizes */
		bl->s.size += b->s.size;
	}

	merge_node_aux(tl, bl);
}

#ifdef __x86_64__

#ifdef _MSC_VER

#define INIT_REG(N) u64b xmm##N
#define SAVE_REG(N, V) xmm##N = V
#define RESTORE_REG(N, V) V = xmm##N

#else

#define INIT_REG(N)

#define SAVE_REG(N, V)\
	asm volatile ("movq %0, %%xmm" #N :: "mr" (V))

#define RESTORE_REG(N, V)\
	asm volatile ("movq %%xmm" #N ", %0" : "=r" (V))

#endif

static always_inline void *fast_alloc(atls *tl, size_t size)
{
	DECL_PROF_FUNC;

	size_t n;
	u64b mask, tmask;
	slist *p;

	btree *b;
	size_t rsize;

	if (unlikely(size > FAST_64_BIN)) return NULL;

	n = size2fl(size);
	mask = FAST_MASK << n;
	tmask = tl->f_mask & mask;

	/* Anything to do? */
	while (tmask)
	{
		INIT_REG(0);
		n = ffsq(tmask);
		p = &tl->fl[n];

		SAVE_REG(0, tmask);

		while (p->next)
		{
			slist *s = slist_rem(p);
			b = CONTAINER(btree, list, s);

			rsize = b->s.size;

			check_sep(b);

			/* Found a match? */
			if (likely(rsize >= size)) return &b->data;

			RESTORE_REG(0, tmask);

			/* Move to lower bin */
			//fast_add(tl, b, n - 1);

			/* Inlined version of the above so %rbx isn't used */
			slist_add(&p[-1], &b->list);
			tmask = tmask / 2;
			tl->f_mask |= tmask & (-tmask);
		}

		RESTORE_REG(0, tmask);

		/*
		 * Turn off least significant bit in tmask, as nothing is left there
		 */
		mask = (tmask - 1) | ~tmask;
		tmask &= mask;
		tl->f_mask &= mask;
	}

	return NULL;
}

static void *slow_alloc_aux(atls *tl, size_t size)
{
	DECL_PROF_FUNC;

	size_t n;
	u64b mask, tmask;

	btree *b;
	dlist *d;
	size_t rsize;

	/* Special case empty allocations */
	if (size == 16)
	{
		b = small_del_first(tl);
		if (b)
		{
			set_used(b, 16);

			return &b->data;
		}

		n = 1;
	}
	else
	{
		n = (size / 16) - 1;
	}

	mask = (~0ULL) << n;
	tmask = tl->q_mask & mask;

	/* Are there nodes big enough in the queues? */
	while (tmask)
	{
		/* Ignore if bit unset */
		n = ffsq(tmask);
		d = &tl->qs[n];

		/* Found something? */
		if (d->next != d)
		{
			b = list_entry(btree, list2, d->next);

			/* Paranoia */
			check_sep(b);

			dlist_del(&b->list2);

			rsize = (n + 1) * 16;
			set_used(b, rsize);
			return split_node(tl, b, rsize, size);
		}

		/*
		 * Turn off least significant bit in tmask, as nothing is left there
		 */
		mask = (tmask - 1) | ~tmask;
		tmask &= mask;
		tl->q_mask &= mask;
	}

	return NULL;
}

#else

/* Versions optimized for 32bit */
static always_inline void *fast_alloc(atls *tl, size_t size)
{
	size_t n = size2fl(size);

	unsigned tmask;

	slist *p;

	btree *b;
	size_t rsize;

	if (n < 32)
	{
		tmask = tl->f_mask & (FAST_MASK << n);

		/* Anything to do? */
		while (tmask)
		{
			n = ffsu(tmask);
			p = &tl->fl[n];

			while (p->next)
			{
				slist *s = slist_rem(p);
				b = CONTAINER(btree, list, s);

				rsize = b->s.size;

				check_sep(b);

				/* Found a match? */
				if (likely(rsize >= size)) return &b->data;

				/* Move to lower bin */
				fast_add(tl, b, n - 1);
			}

			/*
			 * Turn off least significant bit in tmask, as nothing is left there
			 */
			tmask &= tmask - 1;
			tl->f_mask &= ~(1ULL << n);
		}

		tmask = (tl->f_mask >> 32) & (FAST_MASK >> (32 - n));
	}
	else
	{
		tmask = (tl->f_mask >> 32) & (FAST_MASK << (n - 32));
	}

	if (unlikely(size >= FAST_64_BIN)) return NULL;

	/* Anything to do? */
	while (tmask)
	{
		n = ffsu(tmask) + 32;
		p = &tl->fl[n];

		while (p->next)
		{
			slist *s = slist_rem(p);
			b = CONTAINER(btree, list, s);

			rsize = b->s.size;

			check_sep(b);

			/* Found a match */
			if (likely(rsize >= size)) return &b->data;

			/* Move to lower bin */
			fast_add(tl, b, n - 1);
		}

		/*
		 * Turn off least significant bit in tmask, as nothing is left there
		 */
		tmask &= tmask - 1;
		tl->f_mask &= ~(1ULL << n);
	}

	return NULL;
}

static void *slow_alloc_aux(atls *tl, size_t size)
{
	size_t n;
	unsigned tmask;

	btree *b;
	dlist *d;
	size_t rsize;

	/* Special case empty allocations */
	if (size == 16)
	{
		b = small_del_first(tl);
		if (b)
		{
			set_used(b, 16);
			return &b->data;
		}

		n = 1;
	}
	else
	{
		n = (size / 16) - 1;
	}

	if (n < 32)
	{
		tmask = tl->q_mask & (~0 << n);

		/* Are there nodes big enough in the queues? */
		while (tmask)
		{
			/* Ignore if bit unset */
			n = ffsu(tmask);
			d = &tl->qs[n];

			/* Found something? */
			if (d->next != d)
			{
				b = list_entry(btree, list, d->next);

				/* Paranoia */
				check_sep(b);

				dlist_del(&b->list2);

				rsize = (n + 1) * 16;
				set_used(b, rsize);

				return split_node(tl, b, rsize, size);
			}

			/*
			 * Turn off least significant bit in tmask, as nothing is left there
			 */
			tmask &= tmask - 1;
			tl->q_mask &= ~(1ULL << n);
		}

		tmask = tl->q_mask >> 32;
	}
	else
	{
		tmask = (tl->q_mask >> 32) & (~0 << (n - 32));
	}

	/* Are there nodes big enough in the queues? */
	while (tmask)
	{
		/* Ignore if bit unset */
		n = ffsu(tmask) + 32;
		d = &tl->qs[n];

		/* Found something? */
		if (d->next != d)
		{
			b = list_entry(btree, list, d->next);

			/* Paranoia */
			check_sep(b);

			dlist_del(&b->list2);

			rsize = (n + 1) * 16;
			set_used(b, rsize);

			return split_node(tl, b, rsize, size);
		}

		/*
		 * Turn off least significant bit in tmask, as nothing is left there
		 */
		tmask &= tmask - 1;
		tl->q_mask &= ~(1ULL << n);
	}

	/* Failed */
	return NULL;
}

#endif

static void *block_alloc_aux(atls *tl, size_t size)
{
	DECL_PROF_FUNC;

	btree *b, *br;
	mealloc *ma;
	size_t rsize, tasize;

	/* Make overhead 1/4th of total allocated after this allocation */
	tasize = size + (size + tl->a_alloced) / 3;
	tasize = page_align(tasize);

	/* Clip to BTMALLOC */
	if (tasize > BTMALLOC) tasize = BTMALLOC;

	/* Must be more than MINALLOC */
	if (tasize < MINALLOC) tasize = MINALLOC;

	ma = big_alloc_aux(tasize);

	if (!ma)
	{
		/* Try with smaller alloc */
		tasize = page_align(size + HEADERSIZE);

		ma = big_alloc_aux(tasize);

		if (!ma)
		{
			/* Try again if new handler works */
			if (handle_oom(size)) return slow_alloc(tl, size);

			return NULL;
		}
	}

	rsize = tasize - HEADERSIZE;

	/* Keep track of total allocations */
	tl->a_alloced += tasize;

	/* Fill in header */
	dlist_add(&tl->bl, &ma->m_list);

	ma->tail = &tl->tail;

	b = &ma->b;

	/* Create left seperator */
	b->s.size = rsize;
	b->s.bs_offset = 16;

	/* Position of right seperator */
	br = shift(b, rsize);

	/* Create right seperator */
	br->s.bs_offset = tasize - SEPSIZE;

	tl->callocable = 1;

	return split_node(tl, b, rsize, size);
}

static void *block_alloc(atls *tl, size_t size)
{
	DECL_PROF_FUNC;

	btree *b;
	void *p;

	if (size >= BTMALLOC)
	{
		tl->callocable = 1;
		return big_alloc(tl, size);
	}

	if (size <= QS_MAX)
	{
		p = slow_alloc_aux(tl, size);
		if (p) return p;

		/* Clear fast lists */
		clear_fast(tl);

		p = slow_alloc_aux(tl, size);
		if (p) return p;
	}
	else
	{
		/* Clear fast lists */
		clear_fast(tl);
	}

	/* Try to alloc on the btree */
	b = btree_get(tl, size);
	if (b) return split_node(tl, b, b->s.size, size);

	/* Try to grab space from a dead thread */
	if (reap_dead(tl)) return local_alloc(tl, size);

	/* We need more space, so try to free memory. */
	if (scan_queue(tl, &tl->head, size)) return slow_alloc(tl, size);

#ifdef DEBUG_LEAK
	leak_print(tl, "Trying to allocate %llu (%p) but cannot\n", (unsigned long long) size, (void *) size);
	malloc_stats_aux(3);
#endif

	/* Failure - make a big alloc, and add to the btree */
	return block_alloc_aux(tl, size);
}


static void *slow_alloc(atls *tl, size_t size)
{
	DECL_PROF_FUNC;

	/* Fast allocation failed - try normal data structures */
	if (size <= QS_MAX)
	{
		void *res = slow_alloc_aux(tl, size);
		if (res) return res;
	}

	return block_alloc(tl, size);
}

/* Free with no memory usage */
static void free_nomem(void *p)
{
	DECL_PROF_FUNC;

	btree *b = CONTAINER(btree, data, p);

	mealloc *m;

	slist *v, *tail;

#ifdef DEBUG_ALLOC	
	/* Check for double-free errors */
	if (un_used(b)) errx(1, "Double free with %p\n", p);
#endif

	/* Get block start */
	m = read_bs(b);

	/* Treat node as a list now */
	v = &b->list;

	v->next = NULL;

	/*
	 * Prevent other threads from dying because we have no hazard pointer
	 * This protects the dereference of m->tail
	 */
	mutex_lock(&h_lock);

	/* Prepend the data */
	tail = xchg_ptr(m->tail, v);

	/* Done */
	mutex_unlock(&h_lock);

	tail->next = v;
}

static noinline void free_aux(void *p)
{
	DECL_PROF_FUNC;

	atls *tl = init_tls();
	if (!tl)
	{
		free_nomem(p);
		return;
	}

	PREFIX(free)(p);
}

static noinline void free_clear(atls *tl)
{
	clear_fast(tl);
}

void PREFIX(free)(void *p)
{
	DECL_PROF_FUNC;

	btree *b;
	size_t size;

	atls *tl;

	if (!p) return;

	tl = get_tls();

	if (!tl)
	{
		free_aux(p);
		return;
	}

	test_all(tl);

	if (likely(is_slab(p)))
	{
		slab_free(tl, p);

		test_all(tl);

		return;
	}

	b = CONTAINER(btree, data, p);
	size = b->s.size;

#ifdef DEBUG_ALLOC
	/* Check for double-free errors */
	if (un_used(b)) errx(1, "Double free with %p\n", p);
#endif

	if (size)
	{
		/* Get block start */
		mealloc *m = read_bs(b);

		/* My tail = a local node */
		if (unlikely(m->tail != &tl->tail))
		{

			/* Add to their queue, and let them deal with it */
			prepend_queue(p, tl, &m->tail);

			return;
		}

		/* Inlined version of fast_free() */
		size = size2fl(size);
		tl->f_mask |= 1ULL << size;
		slist_add(&tl->fl[size], p);

		tl->fcount++;
		if (!(tl->fcount & FREE_FAST)) free_clear(tl);

		test_all(tl);
	}
	else
	{
		big_free_aux(page_start(b));
	}
}

void cfree(void *p)
{
	PREFIX(free)(p);
}

static noinline void *malloc_aux(size_t size)
{
	DECL_PROF_FUNC;

	atls *tl = init_tls();
	if (!tl) return NULL;
	return PREFIX(malloc)(size);
}

void *PREFIX(malloc)(size_t size)
{
	DECL_PROF_FUNC;

	void *res;
	atls *tl;

	test_leak();

	/* Init local data if required */
	tl = get_tls();

	if (!tl) return malloc_aux(size);

	test_all(tl);

	if (likely(size <= SB_MAX)) return slab_alloc(tl, size);

	/* Prevent overflow bug in sep_align() below */
	if (unlikely(size > BTMALLOC)) return big_alloc(tl, size);

	size = sep_align(size);
	res = fast_alloc(tl, size);
	if (res) return res;

	return slow_alloc(tl, size);
}

#ifdef DEBUG_ALLOC_SLOW
static void test_wiped(void *p, size_t len)
{
	char *endy = &(((char *)p)[len - 8]);
	char *y;

	if (!len) return;

	for (y = p; y < endy; y++)
	{
		if (*y) errx(1, "found non-zero\n");
	}
}
#else
#define test_wiped(P, L) ((void) (sizeof(P) + sizeof(L)))
#endif

static noinline void *zalloc_aux(size_t size)
{
	atls *tl = init_tls();
	if (!tl) return NULL;
	return zalloc(tl, size);
}

static void *zalloc(atls *tl, size_t size)
{
	void *p;

	test_leak();
	test_all(tl);

	if (likely(size <= SB_MAX)) return slab_zalloc(tl, size);

	/* Prevent overflow bug in sep_align() below */
	if (unlikely(size > BTMALLOC)) return big_alloc(tl, size);

	size = sep_align(size);

	p = fast_alloc(tl, size);

	if (!p)
	{
		tl->callocable = 0;
		p = slow_alloc(tl, size);

		/* No need to memset? */
		if (!p || tl->callocable)
		{
			test_wiped(p, size);

			return p;
		}
	}

	test_all(tl);

	return memset(p, 0, size - 8);
}

static size_t safemul(size_t n, size_t size)
{
#ifdef __x86_64__
#ifdef _MSC_VER
	size_t highproduct;
	size_t rsize = _mul128(n, size, &highproduct);
	if (highproduct)
		return TOP_SIZE + 1;
#else /* _MSC_VER */
	/* 64 bit */
	__uint128_t dn = n;
	__uint128_t dsize = size;
	__uint128_t drsize = dn*dsize;
	size_t rsize = drsize;
	if (drsize >> 64)
	{
		/* Overflow */
		return TOP_SIZE + 1;
	}
#endif /* _MSC_VER */
#else

	/* 32 bit */
	u64b dn = n;
	u64b dsize = size;
	u64b drsize = dn*dsize;
	size_t rsize = drsize;

	if (drsize >> 32)
	{
		/* Overflow */
		return TOP_SIZE + 1;
	}
#endif

	return rsize;
}

void *PREFIX(calloc)(size_t n, size_t size)
{
	DECL_PROF_FUNC;

	/* Init local data if required */
	atls *tl = get_tls();

	size = safemul(n, size);

	test_leak();

	if (!tl) return zalloc_aux(size);

	return zalloc(tl, size);
}

#ifdef WINDOWS
void *PREFIX(_calloc_impl)(size_t n, size_t size, int *errno_tmp)
{
	DECL_PROF_FUNC;

	void *ret;
	atls *tl;

	int errno_orig;
	if (!errno_tmp) return PREFIX(calloc)(n, size);

	/* Init local data if required */
	tl = get_tls();

	size = safemul(n, size);

	test_leak();

	if (!tl) return zalloc_aux(size);

	_get_errno(&errno_orig);

	ret = zalloc(tl, safemul(n, size));
	_get_errno(errno_tmp);
	_set_errno(errno_orig);

	return ret;
}
#endif

static noinline void *realloc_aux(void *p, size_t size)
{
	atls *tl = init_tls();

	/* Cannot allocate anything */
	if (!tl) return NULL;

	return PREFIX(realloc)(p, size);
}

static noinline void *realloc_aux2(void *p, size_t size, atls *tl)
{
	btree *b = CONTAINER(btree, data, p);
	size_t msize = b->s.size;

	size_t old_size;

#ifdef DEBUG_ALLOC
	if (un_used(b)) errx(1, "Realloc of unmalloced pointer %p\n", p);
#endif

	/* Was a big block? */
	if (!msize)
	{
#ifndef WINDOWS
		size_t *np;
#endif
		size_t *ps = page_start(b);

		size_t offset = (char *) b - (char *) ps;

		/* Get old size */
		old_size = *ps;

		/* Don't bother resizing shrinks that are more than half the allocated size */
		if ((old_size - offset <= size * 2) && (old_size - offset >= size)) return p;

		/* Resize to new big block if possible */
		if (size >= BTMALLOC)
		{
			/* Align */
			size = page_align(size + offset + offsetof(btree, data));

#ifndef WINDOWS
			/* Use (nonportable) mremap */
			np = mremap(ps, old_size, size, MREMAP_MAYMOVE);

			/* Success? */
			if (np != MAP_FAILED)
			{
				/* Save new size */
				*np = size;

				/* Return new pointer */
				return shift(np, offset + offsetof(btree, data));
			}
#endif

			if (size < old_size)
			{
#ifndef WINDOWS
				if (!munmap(shift(ps, size), old_size - size))
				{
					/* Update size */
					*ps = size;
				}
#else
				/*
				 * Say we no longer want the memory....
				 * But it is still mapped into our address space taking up room!
				 */
				if (VirtualAlloc(shift(ps, size), old_size - size, MEM_RESET,
				PAGE_NOACCESS))
				{
					/* Update size */
					*ps = size;
				}
#endif

				return p;
			}
		}
	}
	else
	{
		mealloc *m;

		/* Get old size */
		old_size = msize;

		size = sep_align(size);

		/* Don't bother resizing shrinks that are more than half the allocated size */
		if ((old_size <= size * 2) && (old_size >= size)) return p;

		m = read_bs(b);

		/* Local node? */
		if (m->tail == &tl->tail)
		{
			btree *br;

			/* Easy case */
			if (size <= msize) return split_node(tl, b, msize, size);

			/* Make sure adjacent nodes are in the btree */
			clear_fast(tl);

			/* Medium or small size - try to merge */
			br = shift(b, msize);
			if (un_used(br))
			{
				if (br->s.bs_offset & FLG_SIZE8)
				{
					small_remove(br);

					/* Fixup sizes */
					b->s.size += 16;
					msize += 16;

					br = shift(br, 16);

					/* Set it as used */
					br->s.bs_offset &= ~FLG_LUNUSED;
				}
				else
				{
					size_t rsize = br->s.size;
					if (rsize)
					{
						if (rsize > QS_MAX)
						{
							btree_node_del(tl, br->parent, b_pindex(br));
						}
						else
						{
							dlist_del(&br->list2);
						}

						/* Fixup sizes */
						b->s.size += rsize;
						msize += rsize;

						br = shift(br, rsize);

						/* Set it as used */
						br->s.bs_offset &= ~FLG_LUNUSED;
					}
				}
			}

			/* Region fits? */
			if (size <= msize) return split_node(tl, b, msize, size);
		}
		else
		{
			/* We can only shrink a foreign node */
			if (size <= msize)
			{
				/* Open coded split node */
				btree *bm = shift(b, size);

				/* Update my size */
				b->s.size = size;

				/* Create middle seperator */
				set_sep(bm, old_size - size, b);

				/* Free the foreign excess */
				prepend_queue((void *) &bm->data, tl, &m->tail);

				return p;
			}
		}
	}

	/* Failure */
	return NULL;
}

/* Same as realloc(), but takes additional parameter 'actual_old_size' to eliminate overcopying */
void *PREFIX(exrealloc)(void *p, size_t size, size_t actual_old_size, size_t copy_offset)
{
	DECL_PROF_FUNC;

	void *np;

	/* Init local data if required */
	atls *tl = get_tls();

	int old_errno;

	test_leak();

	if (!tl) return realloc_aux(p, size);

	test_all(tl);

	/* realloc(p, 0) is the same as free(p) */
	if (!size)
	{
		PREFIX(free)(p);

		return NULL;
	}

	/* Relloc NULL is the same as malloc */
	if (!p) return PREFIX(malloc)(size);

	/* Too large to allocate */
	if (size > TOP_SIZE) goto nomem;

	if (!is_slab(p))
	{
		/* See if merging will work */
		np = realloc_aux2(p, size, tl);

		if (np) return np;
	}

#ifdef WINDOWS
	_get_errno(&old_errno);
#else
	/* Failure - have to do it manually */
	old_errno = errno;
#endif
	np = PREFIX(malloc)(size);
	if (!np)
	{
		/* Is original allocation still okay? */
		if (size <= malloc_usable_size(p))
		{
			/* Don't set errno to be ENOMEM */
#ifdef WINDOWS
			_set_errno(old_errno);
#else
			errno = old_errno;
#endif

			/* Return old allocation */
			return p;
		}
		goto nomem;
	}

	/* Copy data */
	if (size > actual_old_size) size = actual_old_size;
	memcpy((unsigned char *) np + copy_offset, (unsigned char *) p + copy_offset, size - copy_offset);

	PREFIX(free)(p);

	/* Done */
	return np;

nomem:
	set_enomem();
	return NULL;
}

void *PREFIX(realloc)(void *p, size_t size)
{
	DECL_PROF_FUNC;

	void *np;

	size_t old_size;

	/* Init local data if required */
	atls *tl = get_tls();

	int old_errno;

	test_leak();

	if (!tl) return realloc_aux(p, size);

	test_all(tl);

	/* realloc(p, 0) is the same as free(p) */
	if (!size)
	{
		PREFIX(free)(p);

		return NULL;
	}

	/* Relloc NULL is the same as malloc */
	if (!p) return PREFIX(malloc)(size);

	/* Too large to allocate */
	if (size > TOP_SIZE) goto nomem;

	if (!is_slab(p))
	{
		/* See if merging will work */
		np = realloc_aux2(p, size, tl);

		if (np) return np;
	}

	old_size = malloc_usable_size(p);

#ifdef WINDOWS
	_get_errno(&old_errno);
#else
	/* Failure - have to do it manually */
	old_errno = errno;
#endif

	np = PREFIX(malloc)(size);
	if (!np)
	{
		/* Is original allocation still okay? */
		if (size <= old_size)
		{
			/* Don't set errno to be ENOMEM */
#ifdef WINDOWS
			_set_errno(old_errno);
#else
			errno = old_errno;
#endif

			/* Return old allocation */
			return p;
		}
		goto nomem;
	}

	/* Copy data */
	if (size > old_size) size = old_size;
	memcpy(np, p, size);

	PREFIX(free)(p);

	/* Done */
	return np;

nomem:
	set_enomem();
	return NULL;
}

#ifndef WINDOWS
static void unmap_range(void *x1, void *x2)
{
	if (x1 != x2)
	{
		munmap(x1, (char *) x2 - (char *) x1);
	}
}
#endif

#ifdef DEBUG_ALLOC_SLOW
static void test_align(size_t align, void *p)
{
	uintptr_t x = (uintptr_t) p;
	if (align && (x & (align - 1))) errx(1, "Incorrect alignment of pointer\n");
}
#else
#define test_align(a, p) ((void) (sizeof(a) + sizeof(p)))
#endif

static noinline void *aligned_alloc_aux(size_t align, size_t size)
{
	atls *tl = init_tls();

	/* Cannot allocate anything! */
	if (!tl) return NULL;

	return aligned_alloc(align, size);
}

#ifdef WINDOWS
static void *aligned_alloc_aux2(size_t align, size_t size, size_t rsize)
{
	size_t psize = page_align(rsize + PAGESIZE);
	size_t *ps;

	(void) size;

	if (align > PAGESIZE) goto nomem;
	if (rsize > TOP_SIZE) goto nomem;

	ps = VirtualAlloc(NULL, rsize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (ps == MAP_FAILED) goto nomem;

	/* Small alignment */
	*ps = psize;
	ps = shift(ps, PAGESIZE);

	test_align(align, ps);

	return ps;

nomem:
	set_enomem();
	return NULL;
}
#else
static void *aligned_alloc_aux2(size_t align, size_t size, size_t rsize)
{
	size_t pssize = page_align(size + PAGESIZE);
	size_t psize = page_align(rsize + PAGESIZE);
	size_t lsize;
	int flags = MAP_PRIVATE | MAP_ANONYMOUS;

	size_t *lstart, *lend;

	size_t *ps;
	void *p;

	if (rsize > TOP_SIZE) goto nomem;

	/*
	 * Hack - large alignments require no reservation,
	 * otherwise we run out of memory
	 */
	if (align > size) flags |= MAP_NORESERVE;

	ps = mmap(NULL, psize, PROT_READ | PROT_WRITE, flags, -1, 0);

	/* Out of memory */
	if (ps == MAP_FAILED) goto nomem;

	/* Small alignment */
	if (align <= PAGESIZE)
	{
		*ps = psize;
		p = shift(ps, PAGESIZE);

		test_align(align, p);

		return p;
	}

	/* Large alignment */
	lstart = ps;
	lsize = (-(uintptr_t) ps) & (align - 1);

	/* Already aligned - need to shift to get sep+size at beginning */
	if (!lsize)
	{
		ps = shift(ps, align - PAGESIZE);

		/* Fragment at beginning to unmap */
		unmap_range(lstart, ps);

		*ps = pssize;
		p = shift(ps, PAGESIZE);

		test_align(align, p);
		return p;
	}

	lend = shift(ps, rsize);
	ps = shift(ps, lsize - PAGESIZE);

	/* Fragment at beginning to unmap */
	unmap_range(lstart, ps);
	*ps = pssize;
	p = shift(ps, PAGESIZE);

	lstart = shift(p, pssize);

	/* Fragment at end to unmap */
	unmap_range(lstart, lend);

	test_align(align, p);
	return p;

nomem:
	set_enomem();
	return NULL;
}
#endif

void *aligned_alloc(size_t align, size_t size)
{
	DECL_PROF_FUNC;

	size_t rsize, lsize;

	void *p;

	btree *b;

	atls *tl = get_tls();

	test_leak();

	/* Too large to allocate */
	if (size > TOP_SIZE) goto nomem;

	if (align <= SEPSIZE) return PREFIX(malloc)(size);

	if (!tl) return aligned_alloc_aux(align, size);

	/* Try to cache-line align via slab special case */
	if ((size <= 64) && (align <= 64))
	{
		p = slab_alloc(tl, 64);
		if (p)
		{
			/* Double-check alignment as slab_alloc may fall-back in low mem */
			if (!(63 & (uintptr_t) p)) return p;
			local_free(tl, p);
		}
	}

	size = sep_align(size);
	rsize = sep_align(size + align);

	/* Check for overflow */
	if ((rsize <= size) || (rsize <= align)) goto nomem;

#ifdef WINDOWS
	/* Large allocations are special */
	if (rsize >= BTMALLOC)
	{
		return aligned_alloc_aux2(align, size, rsize);
	}
#else
	/* Large allocations are special */
	if (rsize >= BTMALLOC)
	{
		return aligned_alloc_aux2(align, size, rsize);
	}
#endif

	while (1)
	{
		p = fast_alloc(tl, rsize);
		if (p) break;

		if (rsize < QS_MAX)
		{
			p = slow_alloc_aux(tl, rsize);
			if (p) break;

			/* Clear fast lists */
			clear_fast(tl);

			p = slow_alloc_aux(tl, rsize);
			if (p) break;
		}
		else
		{
			/* Clear fast lists */
			clear_fast(tl);
		}

		/* Try to alloc on the btree */
		b = btree_get(tl, rsize);
		if (b)
		{
			p = split_node(tl, b, b->s.size, rsize);
			break;
		}

		/* Try to grab space from a dead thread */
		if (reap_dead(tl)) continue;

		/* We need more space, so try to free memory. */
		if (scan_queue(tl, &tl->head, rsize)) continue;

		/* Everything failed - fall back to large allocation */
		return aligned_alloc_aux2(align, size, rsize);
	}

	lsize = (-(uintptr_t) p) & (align - 1);

	b = CONTAINER(btree, data, p);

#ifdef DEBUG_ALLOC_SLOW
	if (rsize > b->s.size) errx(1, "node received is too small\n");
#endif

	/* get real size allocated */
	rsize = b->s.size;

	/* Already aligned? */
	if (!lsize)
	{
		test_align(align, &b->data);

		/* Split off part we need */
		return split_node(tl, b, rsize, size);
	}

	b = split_node_rhs(tl, b, rsize, lsize);
	test_align(align, &b->data);

	return split_node(tl, b, rsize - lsize, size);

nomem:
	set_enomem();
	return NULL;
}

/* This is now just a wrapper around the ISO C11 aligned_alloc() function */
void *memalign(size_t align, size_t size)
{
	return aligned_alloc(align, size);
}

int posix_memalign(void **p, size_t align, size_t size)
{
	/* Make sure power of two and greater than sizeof(void *) */
#ifdef __x86_64__	
	if (align & ((align - 1) | 7))
	{
		*p = NULL;
		return EINVAL;
	}
#else
	if (align & ((align - 1) | 3))
	{
		*p = NULL;
		return EINVAL;
	}
#endif

	*p = aligned_alloc(align, size);

	if (!*p) return ENOMEM;

	return 0;
}

void *valloc(size_t size)
{
	return aligned_alloc(PAGESIZE, size);
}

void *pvalloc(size_t size)
{
	return aligned_alloc(PAGESIZE, page_align(size));
}

#ifdef WINDOWS
static
#endif
size_t malloc_usable_size(void *p)
{
	size_t offset;
	size_t *ps;
	size_t size;

	DECL_PROF_FUNC;

	btree *b = CONTAINER(btree, data, p);

	/* Don't crash on a NULL pointer */
	if (!p) return 0;

	/* Handle slab allocations */
	if (is_slab(p))
	{
		sbheader *sb = slab_start(p);
		return sb->size;
	}

	size = b->s.size;

	/* Small allocation */
	if (size) return size - PTRSIZE;

	/* Large allocation */
	ps = page_start(b);
	offset = (uintptr_t) &b->data - (uintptr_t) ps;

	return *ps - offset;
}

#ifdef WINDOWS
#ifdef PREFIX
size_t __pure PREFIX(_msize)(void *p)
#else /* !PREFIX */
__attribute__((dllimport)) size_t _msize(void *p)
#endif /* PREFIX */
{
	return malloc_usable_size(p);
}
#endif

struct mallinfo mallinfo(void)
{
	atls *tl = get_tls();
	struct mallinfo mi = {0,0,0,0,0,0,0,0,0,0};

	dlist *d;
	slist *s;

	int i;

	btree *b;

	size_t size;

	mi.arena = sbrk_size;

	if (!tl)
	{
		tl = init_tls();

		/* Cannot allocate anything, just return arena count */
		if (!tl) return mi;
	}

	/* Scan slab */
	for (i = 0; i < NUM_SB; i++)
	{
		scan_list(&tl->slab[i], d)
		{
			mi.smblks++;
			mi.usmblks++;
		}
	}

	scan_list(&tl->slab_full, d)
	{
		mi.smblks++;
		mi.usmblks++;
	}

	if (tl->slab_chunk)
	{
		mi.fsmblks = 1 + tl->slab_chunk->count;
		mi.smblks += mi.fsmblks;
	}

	/* Scan dlists */
	for (i = 1; i < NUM_QS; i++)
	{
		scan_list(&tl->qs[i], d)
		{
			mi.ordblks++;

			b = CONTAINER(btree, list, d);
			size = b->s.size - PTRSIZE;
			mi.fordblks += size;
		}
	}

	/* Add in results from small list */
	for (b = small_next((btree *) &tl->qs[0]); b != (btree *) &tl->qs[0]; b = small_next(b))
	{
		mi.ordblks++;
		mi.fordblks += 8;
	}

	/* Scan fastlists */
	for (i = 0; i < NUM_FL; i++)
	{
		scan_slist(&tl->fl[i], s)
		{
			mi.ordblks++;

			b = CONTAINER(btree, list, s);
			size = b->s.size - PTRSIZE;
			mi.fordblks += size;
		}
	}

	/* Count memory blocks */
	scan_list(&tl->bl, d)
	{
		mi.hblks++;
	}

	/* Count btree nodes */
	mi.hblkhd = count_btree(&tl->bheap);

	/* Count btree space */
	mi.fordblks += count_btree_space(&tl->bheap);

	/* Total allocated space (including overhead of seperators and atls) */
	mi.uordblks = tl->a_alloced - mi.fordblks + PAGESIZE;

	/* Total easily callocable region */
	mi.keepcost = 0;

	/* Done */
	return mi;
}

int malloc_trim(size_t pad)
{
	atls *tl = get_tls();

	/* Nothing allocated - do nothing */
	if (!tl) return 1;

	/* Clear incoming frees */
	scan_queue(tl, &tl->head, 0);

	/* Hack - ignore pad - and just free as much as possible */
	clear_fast(tl);

	(void) pad;

	/* Always return success */
	return 1;
}

int mallopt(int param, int val)
{
	/* Ignore parameters */
	(void) param;
	(void) val;

	/* Just return success - we don't have any parameters to modify */
	return 1;
}

#ifdef DEBUG_LEAK
static int btree_print(atls *tl, btree *b)
{
	int i;
	btree *bc;

	int count = 1;

	if (b_leaf(b))
	{
		leak_print(tl, "%u\n", b->s.size);
		return 0;
	}

	leak_print(tl, "Btree: %p\n", (void *) b);

	for (i = b_start(b); i; i = b_next(b, i))
	{
		bc = b_ptr(b, i);
		leak_print(tl, "link %p\n", (void *) bc);
		count += btree_print(tl, bc);
	}

	return count;
}
#endif

#ifndef WINDOWS

static void mem_slab(void)
{
	int i;
	int count;
	dlist *d;

	atls *tl = get_tls();
	if (!tl) return;

	leak_print(tl, "Total Slab Virtual: %llu\n", (unsigned long long) sbrk_size);

	for (i = 0; i < NUM_SB; i++)
	{
		if (dlist_empty(&tl->slab[i])) continue;

		count = 0;
		scan_list(&tl->slab[i], d)
		{
			count++;
		}
		leak_print(tl, "Partial slab %d used: %lld\n", i * 16, count * 65536ULL);
	}

	if (!dlist_empty(&tl->slab_full))
	{
		count = 0;
		scan_list(&tl->slab_full, d)
		{
			count++;
		}
		leak_print(tl, "Full slab used: %lld\n", count * 65536ULL);
	}

	if (tl->slab_chunk)
	{
		leak_print(tl, "Local free slabs: %lld\n", (tl->slab_chunk->count + 1) * 65536LL);
	}
	else
	{
		leak_print(tl, "Local free slabs: 0\n");
	}
}

#ifdef DEBUG_LEAK
static void mem_big(void)
{
	int i;

	/* If vsnprintf allocates, we may have a problem... */
	mutex_lock(&l_lock);

	for (i = 0; i < LEAK_MAX; i++)
	{
		if (big_leak[i].p)
		{
			leak_print(get_tls(), "big block %p: %llu\n", big_leak[i].p, (unsigned long long) big_leak[i].size);
		}
	}

	mutex_unlock(&l_lock);
}
#endif

static void malloc_stats_aux(int show_nodes)
{
	atls *tl = get_tls();

	dlist *d;
	btree *b;

	size_t size;
	size_t tsize = 0;
	size_t asize = 0;

	/* Nothing allocated - print nothing */
	if (!tl) return;

	clear_fast(tl);

	scan_list(&tl->bl, d)
	{
		mealloc *m = list_entry(mealloc, m_list, d);

		size = big_block_size(m);

		if (size)
		{
			leak_print(tl, "Block: %p %llu\n", (void *) m, (unsigned long long) size);
		}

		/* Scan seps for this block */
		for (b = &m->b;; b = shift(b, size))
		{
			if (b->s.bs_offset & FLG_SIZE8)
			{
				size = 16;
			}
			else
			{
				size = b->s.size;
			}

			if (!size) break;

			tsize += size;

			if (un_used(b))
			{
				if (show_nodes) leak_print(tl, "  %p\n", (void *) size);
			}
			else
			{
				if (show_nodes) leak_print(tl, "* %p\n", (void *) size);
				asize += size;
			}
		}
	}

	leak_print(tl, "Total in btree %llu, total alloced %llu\n", (unsigned long long) tsize, (unsigned long long) asize);

#ifdef DEBUG_LEAK
	if (show_nodes & 2)
	{
		int count = btree_print(tl, &tl->bheap);

		leak_print(tl, "b_cnt = %d, b_hgt = %d, total = %d\n", tl->b_cnt, tl->b_hgt, count);
	}

	mutex_lock(&h_lock);
	size = 0;
	scan_list(&h_list, d)
	{
		size++;
	}
	mutex_unlock(&h_lock);
	leak_print(tl, "%d threads\n", (int) size);

	mem_big();
#endif
	mem_slab();
}

void malloc_stats(void)
{
	malloc_stats_aux(0);
}
#endif

static void **ialloc_fallback(atls *tl, size_t n, size_t *sizes, void **chunks, int clear)
{
	size_t i;
	void **out;

	/* Get storage for pointers */
	if (!chunks)
	{
		out = local_alloc(tl, sep_align(sizeof(void *) * n));
		if (!out) return NULL;
	}
	else
	{
		out = chunks;
	}

	/* Do it manually */
	if (clear)
	{
		for (i = 0; i < n; i++)
		{
			out[i] = zalloc(tl, sizes[0]);
			if (!out[i]) goto fail;
		}
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			out[i] = local_alloc(tl, sizes[i]);
			if (!out[i]) goto fail;
		}
	}

	return out;

fail:
	for (n = 0; n < i; n++)
	{
		PREFIX(free)(out[n]);
	}

	if (!chunks) PREFIX(free)(out);

	return NULL;
}

static void **ialloc(atls *tl, size_t n, size_t *sizes, void **chunks, int clear)
{
	size_t i;

	size_t nsize;
	size_t total_size = 0;

	void *p;
	btree *b, *br;
	unsigned offset;

	void **out;

	test_all(tl);

	test_leak();

	/* Zero sized array? */
	if (!n)
	{
		if (chunks) return chunks;

		return PREFIX(malloc)(0);
	}

	/* Get total size to allocate */
	if (clear)
	{
		total_size = safemul(sep_align(sizes[0]), n);

		/* Overflow */
		if (total_size >= TOP_SIZE)
		{
			set_enomem();
			return NULL;
		}
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			nsize = sep_align(sizes[i]);
			total_size += nsize;

			/* Overflow */
			if (total_size < nsize)
			{
				set_enomem();
				return NULL;
			}
		}
	}

	if (clear) tl->callocable = 0;

	while (1)
	{
		p = fast_alloc(tl, total_size);
		if (p) break;

		if (total_size < QS_MAX) p = slow_alloc(tl, total_size);
		if (p) break;

		/* Too large to allocate normally */
		if (total_size >= BTMALLOC) return ialloc_fallback(tl, n, sizes, chunks, clear);

		/* Clear fast lists */
		clear_fast(tl);

		/* Try to alloc on the btree */
		b = btree_get(tl, total_size);
		if (b)
		{
			p = split_node(tl, b, b->s.size, total_size);
			break;
		}

		/* Try to grab space from a dead thread */
		if (reap_dead(tl)) continue;

		/* We need more space, so try to free memory. */
		if (scan_queue(tl, &tl->head, total_size)) continue;

		/* Try to allocate a new block */
		p = block_alloc_aux(tl, total_size);
		if (p) break;

		/* Everything failed - fall back to individual allocations */
		return ialloc_fallback(tl, n, sizes, chunks, clear);
	}

	b = CONTAINER(btree, data, p);

	/* Get real total size */
	total_size = b->s.size;
	offset = b->s.bs_offset & ~15;

	/* Do we need to clear it? */
	if (clear && !tl->callocable) memset(p, 0, total_size - 8);

	/* Get storage for pointers */
	if (!chunks)
	{
		out = local_alloc(tl, sep_align(sizeof(void *) * n));

		if (!out)
		{
			PREFIX(free)(p);
			return NULL;
		}
	}
	else
	{
		out = chunks;
	}

	for (i = 0; i < n; i++)
	{
		out[i] = p;

		if (clear)
		{
			nsize = sep_align(sizes[0]);
		}
		else
		{
			nsize = sep_align(sizes[i]);
		}
		total_size -= nsize;

		/* Update local size */
		b->s.size = nsize;

		p = shift(p, nsize);
		br = CONTAINER(btree, data, p);

		/* Create offset part of right seperator */
		offset += nsize;
		if (i != n - 1) br->s.bs_offset = offset;

		b = br;
	}

	/* Nothing left - then we are done */
	if (!total_size)
	{
		test_all(tl);
		return out;
	}

	/* Resize last element to have the slack */
	p = out[n - 1];
	b = CONTAINER(btree, data, p);

	b->s.size += total_size;
	check_sep(b);

	/* How big is last allocation? */
	if (clear)
	{
		nsize = sep_align(sizes[0]);
	}
	else
	{
		nsize = sep_align(sizes[n - 1]);
	}

	/* Split off excess if too much */
	split_node(tl, b, b->s.size, nsize);

	test_all(tl);
	return out;
}

static noinline void **ialloc_aux(size_t n, size_t *sizes, void **chunks, int clear)
{
	atls *tl = init_tls();
	if (!tl) return NULL;

	return ialloc(tl, n, sizes, chunks, clear);
}

void **independent_calloc(size_t n, size_t size, void **chunks)
{
	atls *tl = get_tls();

	if (!tl) return ialloc_aux(n, &size, chunks, 1);

	return ialloc(tl, n, &size, chunks, 1);
}

void **independent_comalloc(size_t n, size_t *sizes, void **chunks)
{
	atls *tl = get_tls();

	if (!tl) return ialloc_aux(n, sizes, chunks, 0);

	return ialloc(tl, n, sizes, chunks, 0);
}

#ifndef WINDOWS
void *malloc_get_state(void)
{
	abort();

	return NULL;
}

int malloc_set_state(void *p)
{
	(void) p;
	abort();

	return 0;
}
#endif


#ifdef WINDOWS
#ifdef PREFIX
void *PREFIX(_expand)(void *p, size_t size)
#else /* PREFIX */
__attribute__((dllimport)) void *_expand(void *p, size_t size)
#endif /* PREFIX */
{
	DECL_PROF_FUNC;

	atls *tl = get_tls();

	/* paranoia */
	if (!p) return NULL;

	/* Handle expansion into already allocated memory */
	if (malloc_usable_size(p) <= size) return p;

	/* Don't handle slab allocations */
	if (is_slab(p)) return NULL;

	/* Cannot expand a block created by someone else */
	if (!tl) goto nomem;

	p = realloc_aux2(p, size, tl);

	/* Did it work? */
	if (malloc_usable_size(p) >= size) return p;

nomem:
	set_enomem();
	return NULL;
}

/* Nolock functions call their normal functions */
void PREFIX(_free_nolock)(void *p)
{
	PREFIX(free)(p);
}

void *PREFIX(_realloc_nolock)(void *p, size_t size)
{
	return PREFIX(realloc)(p, size);
}

void *PREFIX(_calloc_nolock)(size_t n, size_t size)
{
	return PREFIX(calloc)(n, size);
}

size_t __pure PREFIX(_msize_nolock)(void *p)
{
	return malloc_usable_size(p);
}

#endif
