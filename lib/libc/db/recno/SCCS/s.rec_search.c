h35110
s 00003/00003/00098
d D 8.3 94/02/21 15:12:48 bostic 11 10
c first pass at making DB use basic integral types (the Alpha port)
e
s 00007/00007/00094
d D 8.2 93/09/14 10:18:37 bostic 10 9
c the __rec_search value shouldn't be stored in a static, can't pin
c across calls in that case
e
s 00002/00002/00099
d D 8.1 93/06/04 15:25:34 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00099
d D 5.8 93/02/14 17:39:05 bostic 8 7
c index_t -> indx_t
e
s 00001/00001/00100
d D 5.7 93/02/11 11:42:22 bostic 7 6
c move db.h to the end of the includes, make compat.h work better
e
s 00001/00000/00100
d D 5.6 93/01/10 12:27:09 bostic 6 5
c clear the stack in the search routine; it's a lot simpler
e
s 00003/00001/00097
d D 5.5 92/11/13 17:31:50 bostic 5 4
c prettiness police
e
s 00003/00003/00095
d D 5.4 92/08/26 13:05:50 bostic 4 3
c nrec is 0-based, here, so > recno, not >= recno, also index was
c off-by-one when incrementing/decrementing internal page counts
e
s 00002/00003/00096
d D 5.3 92/06/23 12:33:36 bostic 3 2
c __bt_push index was off-by-one
e
s 00037/00017/00062
d D 5.2 91/09/11 16:28:42 bostic 2 1
c  drop exact flag (always exact if found at all); increment/decrement
c parent pages while searching the tree instead of waiting
e
s 00079/00000/00000
d D 5.1 91/09/04 12:54:09 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
D 5
#include <errno.h>
E 5
I 5

E 5
D 7
#include <db.h>
E 7
I 5
#include <errno.h>
E 5
#include <stdio.h>
I 5

I 7
#include <db.h>
E 7
E 5
D 2
#include "../btree/btree.h"
E 2
I 2
#include "recno.h"
E 2

/*
 * __REC_SEARCH -- Search a btree for a key.
 *
 * Parameters:
 *	t:	tree to search
D 3
 *	key:	key to find
E 3
I 3
 *	recno:	key to find
E 3
I 2
 *	op: 	search operation
E 2
D 3
 *	exactp:	pointer to exact match flag
E 3
 *
 * Returns:
 *	EPG for matching record, if any, or the EPG for the location of the
 *	key, if it were inserted into the tree.
 *
D 10
 * Warnings:
 *	The EPG returned is in static memory, and will be overwritten by the
 *	next search of any kind in any tree.
E 10
I 10
 * Returns:
 *	The EPG for matching record, if any, or the EPG for the location
 *	of the key, if it were inserted into the tree, is entered into
 *	the bt_cur field of the tree.  A pointer to the field is returned.
E 10
 */
EPG *
D 2
__rec_search(t, recno, exactp)
E 2
I 2
__rec_search(t, recno, op)
E 2
	BTREE *t;
	recno_t recno;
D 2
	int *exactp;
E 2
I 2
	enum SRCHOP op;
E 2
{
D 10
	static EPG e;
E 10
D 8
	register index_t index;
E 8
I 8
	register indx_t index;
E 8
	register PAGE *h;
I 2
	EPGNO *parent;
E 2
	RINTERNAL *r;
	pgno_t pg;
D 8
	index_t top;
E 8
I 8
	indx_t top;
E 8
	recno_t total;
I 2
D 11
	int serrno;
E 11
I 11
	int sverrno;
E 11
E 2

I 6
	BT_CLR(t);
E 6
	for (pg = P_ROOT, total = 0;;) {
		if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
D 2
			return (NULL);
E 2
I 2
			goto err;
E 2
		if (h->flags & P_RLEAF) {
D 10
			e.page = h;
			e.index = recno - total;
D 2
			top = NEXTINDEX(h);

			if (e.index > top) {
				mpool_put(t->bt_mp, h, 0);
				errno = EINVAL;
				return (NULL);
			}

			*exactp = e.index < top ? 1 : 0;
E 2
			return (&e);
E 10
I 10
			t->bt_cur.page = h;
			t->bt_cur.index = recno - total;
			return (&t->bt_cur);
E 10
		}
D 2

E 2
		for (index = 0, top = NEXTINDEX(h);;) {
			r = GETRINTERNAL(h, index);
D 4
			if (++index == top || total + r->nrecs >= recno)
E 4
I 4
			if (++index == top || total + r->nrecs > recno)
E 4
				break;
			total += r->nrecs;
		}

D 2
		if (bt_push(t, h->pgno, index - 1) == RET_ERROR)
E 2
I 2
D 3
		if (__bt_push(t, pg, index) == RET_ERROR)
E 3
I 3
		if (__bt_push(t, pg, index - 1) == RET_ERROR)
E 3
E 2
			return (NULL);
D 2

E 2
I 2
		
E 2
		pg = r->pgno;
D 2
		mpool_put(t->bt_mp, h, 0);
E 2
I 2
		switch (op) {
		case SDELETE:
D 4
			--GETRINTERNAL(h, index)->nrecs;
E 4
I 4
			--GETRINTERNAL(h, (index - 1))->nrecs;
E 4
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			break;
		case SINSERT:
D 4
			++GETRINTERNAL(h, index)->nrecs;
E 4
I 4
			++GETRINTERNAL(h, (index - 1))->nrecs;
E 4
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			break;
		case SEARCH:
			mpool_put(t->bt_mp, h, 0);
			break;
		}

E 2
	}
I 2
	/* Try and recover the tree. */
D 11
err:	serrno = errno;
E 11
I 11
err:	sverrno = errno;
E 11
	if (op != SEARCH)
		while  ((parent = BT_POP(t)) != NULL) {
			if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
				break;
			if (op == SINSERT)
				--GETRINTERNAL(h, parent->index)->nrecs;
			else
				++GETRINTERNAL(h, parent->index)->nrecs;
                        mpool_put(t->bt_mp, h, MPOOL_DIRTY);
                }
D 11
	errno = serrno;
E 11
I 11
	errno = sverrno;
E 11
	return (NULL);
E 2
}
E 1
