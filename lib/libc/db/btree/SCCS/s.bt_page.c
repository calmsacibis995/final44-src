h10824
s 00000/00001/00067
d D 8.2 94/02/21 15:08:14 bostic 5 4
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00066
d D 8.1 93/06/04 15:20:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00067
d D 5.3 93/02/11 11:39:26 bostic 3 2
c move db.h to the end of the includes, make compat.h work better
e
s 00001/00000/00067
d D 5.2 92/11/13 16:05:20 bostic 2 1
c prettiness police
e
s 00067/00000/00000
d D 5.1 92/10/10 10:18:44 bostic 1 0
c date and time created 92/10/10 10:18:44 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
I 2

E 2
D 5
#define	__DBINTERFACE_PRIVATE
E 5
D 3
#include <db.h>
E 3
#include <stdio.h>

I 3
#include <db.h>
E 3
#include "btree.h"

/*
 * __BT_FREE -- Put a page on the freelist.
 *
 * Parameters:
 *	t:	tree
 *	h:	page to free
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__bt_free(t, h)
	BTREE *t;
	PAGE *h;
{
	/* Insert the page at the start of the free list. */
	h->prevpg = P_INVALID;
	h->nextpg = t->bt_free;
	t->bt_free = h->pgno;

	/* Make sure the page gets written back. */
	return (mpool_put(t->bt_mp, h, MPOOL_DIRTY));
}

/*
 * __BT_NEW -- Get a new page, preferably from the freelist.
 *
 * Parameters:
 *	t:	tree
 *	npg:	storage for page number.
 *
 * Returns:
 *	Pointer to a page, NULL on error.
 */
PAGE *
__bt_new(t, npg)
	BTREE *t;
	pgno_t *npg;
{
	PAGE *h;

	if (t->bt_free != P_INVALID &&
	    (h = mpool_get(t->bt_mp, t->bt_free, 0)) != NULL) {
			*npg = t->bt_free;
			t->bt_free = h->nextpg;
			return (h);
	}
	return (mpool_new(t->bt_mp, npg));
}
E 1
