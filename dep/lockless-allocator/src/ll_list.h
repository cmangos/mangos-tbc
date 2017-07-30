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

/* Header for intrinsic lists */
#ifndef LL_LIST_H
#define LL_LIST_H

#include <stddef.h>
#include <stdint.h>

/* Go from a member * to its container */
#define CONTAINER(T, S, P)\
	((T *) (((uintptr_t) P) - offsetof(T, S)))

/* List types */
typedef struct slist slist;
struct slist
{
	slist *next;
};

typedef struct dlist dlist;
struct dlist
{
	dlist *next;
	dlist *prev;
};


#define list_entry(T, S, P) CONTAINER(T, S, P)

#define scan_list(P, I)\
	for (I = (P)->next; I != (P); I = I->next)

#define scan_list_safe(P, I, T)\
	for (I = (P)->next, T = I->next; I != (P); I = T, T = I->next)

#define dlist_empty(T) ((T)->next == T)

#define scan_slist(P, I)\
	for (I = (P)->next; I; I = I->next)

#define scan_slist_safe(P, I, T)\
	for (I = (P)->next, I?(T = I->next):0; I; I = T, I?(T = I->next):0)

/* Add an entry to the front of the list */
static inline void slist_add(slist *s, slist *a)
{
	a->next = s->next;
	s->next = a;
}

/* Remove first entry, and return it */
static inline slist *slist_rem(slist *s)
{
	slist *r = s->next;
	s->next = r->next;

	return r;
}

#define DLIST_INIT(X) {.next = &X, .prev = &X}

static inline void dlist_init(dlist *d)
{
	/* Point to self, so list deletion is faster */
	d->next = d;
	d->prev = d;
}

/* Adds "a" to start of dlist d */
static inline void dlist_add(dlist *d, dlist *a)
{
	dlist *dn = d->next;

	a->next = dn;
	a->prev = d;
	dn->prev = a;
	d->next = a;
}

/* Adds "a" to end of dlist d */
static inline void dlist_add_end(dlist *d, dlist *a)
{
	dlist *dp = d->prev;

	a->next = d;
	a->prev = dp;
	dp->next = a;
	d->prev = a;
}

/* Remove node "d" from the list */
static inline void dlist_del(dlist *d)
{
	dlist *dp = d->prev;
	dlist *dn = d->next;

	dn->prev = dp;
	dp->next = dn;
}

static inline dlist *dlist_rem_last(dlist *d)
{
	dlist *dp = d->prev;
	if (dp == d) return NULL;

	dlist_del(dp);

	return dp;
}

/* Merge two dlists: d2 into d*/
static inline void dlist_merge(dlist *d, dlist *d2)
{
	dlist *dp = d->prev;
	dlist *d2n = d2->next;
	dlist *d2p = d2->prev;

	/* Don't need to do anything if adding an empty list */
	if (d2n == d2) return;

	dp->next = d2n;
	d2n->prev = dp;

	d->prev = d2p;
	d2p->next = d;
}

#endif /* LL_LIST_H */
