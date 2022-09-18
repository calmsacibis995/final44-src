h35619
s 00017/00002/00337
d D 8.2 93/09/07 11:49:20 bostic 12 11
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00337
d D 8.1 93/06/04 15:20:53 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00332
d D 5.10 93/05/16 15:41:58 bostic 10 9
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00001/00001/00338
d D 5.9 93/02/14 17:39:23 bostic 9 8
c index -> indx_t
e
s 00001/00001/00338
d D 5.8 93/02/11 11:39:28 bostic 8 7
c move db.h to the end of the includes, make compat.h work better
e
s 00008/00006/00331
d D 5.7 92/11/13 16:08:40 bostic 7 6
c prettiness police
e
s 00027/00021/00310
d D 5.6 91/09/12 11:10:34 bostic 6 5
c fix cursor code in various minor ways; fix the cursor code to return
c the key greater than or equal to the specified key (implement range searches)
c skip empty pages if no exact match is found
e
s 00260/00221/00071
d D 5.5 91/09/04 12:47:21 bostic 5 4
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00001/00001/00291
d D 5.4 91/03/03 14:33:20 bostic 4 3
c DBT data changed to be unsigned
e
s 00002/00001/00290
d D 5.3 91/02/22 17:16:41 bostic 3 2
c ANSI prototypes
e
s 00004/00000/00287
d D 5.2 91/02/18 22:49:01 mao 2 1
c fix stack management bug
e
s 00287/00000/00000
d D 5.1 91/01/23 08:12:45 mao 1 0
c date and time created 91/01/23 08:12:45 by mao
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
D 3
#include <sys/errno.h>
E 3
I 3
D 7
#include <errno.h>
E 7
I 7

E 7
E 3
D 8
#include <db.h>
E 8
I 7
#include <errno.h>
#include <stddef.h>
E 7
I 5
#include <stdio.h>
E 5
I 3
#include <stdlib.h>
I 5
D 7
#include <stddef.h>
E 7
I 7

I 8
#include <db.h>
E 8
E 7
E 5
E 3
#include "btree.h"

I 5
static int	 bt_seqadv __P((BTREE *, EPG *, int));
static int	 bt_seqset __P((BTREE *, EPG *, DBT *, int));

E 5
/*
D 5
 *  _BT_SEQINIT -- Initialize a sequential scan on the btree.
E 5
I 5
 * Sequential scan support.
E 5
 *
D 5
 *	Sets the tree's notion of the current scan location correctly
 *	given a key and a direction.
E 5
I 5
 * The tree can be scanned sequentially, starting from either end of the tree
 * or from any specific key.  A scan request before any scanning is done is
 * initialized as starting from the least node.
E 5
 *
D 5
 *	Parameters:
 *		t -- tree in which to initialize scan
 *		key -- key for initial scan position
 *		flags -- R_NEXT, R_PREV
E 5
I 5
 * Each tree has an EPGNO which has the current position of the cursor.  The
 * cursor has to survive deletions/insertions in the tree without losing its
 * position.  This is done by noting deletions without doing them, and then
 * doing them when the cursor moves (or the tree is closed).
 */

/*
 * __BT_SEQ -- Btree sequential scan interface.
E 5
 *
D 5
 *	Returns:
 *		RET_SUCCESS, RET_ERROR, or RET_SPECIAL if there's no data
 *		in the tree to scan.
E 5
I 5
 * Parameters:
 *	dbp:	pointer to access method
 *	key:	key for positioning and return value
 *	data:	data return value
 *	flags:	R_CURSOR, R_FIRST, R_LAST, R_NEXT, R_PREV.
E 5
 *
D 5
 *	Side Effects:
 *		Changes current scan position for the tree.  Almost certainly
 *		changes current page, as well.  Sets BTF_SEQINIT bit in tree
 *		flags, so that we know we've initialized a scan.
E 5
I 5
 * Returns:
 *	RET_ERROR, RET_SUCCESS or RET_SPECIAL if there's no next key.
E 5
 */
D 5

E 5
int
D 5
_bt_seqinit(t, key, flags)
	BTREE_P t;
	DBT *key;
	int flags;
E 5
I 5
__bt_seq(dbp, key, data, flags)
	const DB *dbp;
	DBT *key, *data;
	u_int flags;
E 5
{
D 5
	BTITEM *item;
	BTHEADER *h;
	CURSOR *c;
	IDATUM *id;
	index_t last;
E 5
I 5
	BTREE *t;
	EPG e;
	int status;
E 5

I 12
	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

E 12
	/*
D 5
	 *  Figure out if we really have to search for the key that the
	 *  user supplied.  If key is null, then this is an unkeyed scan
	 *  and we can just start from an endpoint.
E 5
I 5
	 * If scan unitialized as yet, or starting at a specific record, set
	 * the scan to a specific key.  Both bt_seqset and bt_seqadv pin the
	 * page the cursor references if they're successful.
E 5
	 */
I 5
D 12
	t = dbp->internal;
E 12
	switch(flags) {
	case R_NEXT:
I 6
	case R_PREV:
E 6
D 10
		if (ISSET(t, BTF_SEQINIT)) {
E 10
I 10
		if (ISSET(t, B_SEQINIT)) {
E 10
			status = bt_seqadv(t, &e, flags);
			break;
		}
		/* FALLTHROUGH */
	case R_CURSOR:
	case R_FIRST:
D 6
		status = bt_seqset(t, &e, key, flags);
		SET(t, BTF_SEQINIT);
		break;
	case R_PREV:
		if (ISSET(t, BTF_SEQINIT)) {
			status = bt_seqadv(t, &e, flags);
			break;
		}
		/* FALLTHROUGH */
E 6
	case R_LAST:
		status = bt_seqset(t, &e, key, flags);
D 6
		SET(t, BTF_SEQINIT);
E 6
		break;
	default:
		errno = EINVAL;
		return (RET_ERROR);
	}
E 5

D 5
	c = &(t->bt_cursor);
E 5
I 5
	if (status == RET_SUCCESS) {
		status = __bt_ret(t, &e, key, data);
E 5

D 5
	if (flags == R_CURSOR) {
D 4
		if (key->data != (char *) NULL) {
E 4
I 4
		if (key->data != (u_char *) NULL) {
E 4

			/* key supplied, find first instance of it */
			item = _bt_first(t, key);
			c->c_index = item->bti_index;
			c->c_pgno = t->bt_curpage->h_pgno;
		} else {
			errno = EINVAL;
			return (RET_ERROR);
E 5
I 5
		/* Update the actual cursor. */
D 6
		if (status == RET_SUCCESS) {
			t->bt_bcursor.pgno = e.page->pgno;
			t->bt_bcursor.index = e.index;
E 5
		}
E 6
I 6
		t->bt_bcursor.pgno = e.page->pgno;
		t->bt_bcursor.index = e.index;
E 6
I 5
D 12
		mpool_put(t->bt_mp, e.page, 0);
E 12
I 12

		/*
		 * If the user is doing concurrent access, we copied the
		 * key/data, toss the page.
		 */
		if (ISSET(t, B_DB_LOCK))
			mpool_put(t->bt_mp, e.page, 0);
		else
			t->bt_pinned = e.page;
E 12
I 6
D 10
		SET(t, BTF_SEQINIT);
E 10
I 10
		SET(t, B_SEQINIT);
E 10
E 6
	}
	return (status);
}
E 5

D 5
	} else {
E 5
I 5
/*
 * BT_SEQSET -- Set the sequential scan to a specific key.
 *
 * Parameters:
 *	t:	tree
 *	ep:	storage for returned key
 *	key:	key for initial scan position
 *	flags:	R_CURSOR, R_FIRST, R_LAST, R_NEXT, R_PREV
 *
 * Side effects:
 *	Pins the page the cursor references.
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS or RET_SPECIAL if there's no next key.
 */
static int
bt_seqset(t, ep, key, flags)
	BTREE *t;
	EPG *ep;
	DBT *key;
	int flags;
{
	EPG *e;
	PAGE *h;
	pgno_t pg;
	int exact;
E 5

D 5
		/*
		 *  Unkeyed scan.  For backward scans, find the last item
		 *  in the tree; for forward scans, find the first item.
		 */
E 5
I 5
	/*
	 * Delete any already deleted record that we've been saving because
	 * the cursor pointed to it.  Since going to a specific key, should
	 * delete any logically deleted records so they aren't found.
	 */
D 10
	if (ISSET(t, BTF_DELCRSR) && __bt_crsrdel(t, &t->bt_bcursor))
E 10
I 10
	if (ISSET(t, B_DELCRSR) && __bt_crsrdel(t, &t->bt_bcursor))
E 10
		return (RET_ERROR);
E 5

D 5
		if (_bt_getpage(t, (pgno_t) P_ROOT) == RET_ERROR)
E 5
I 5
	/*
D 6
	 * If R_CURSOR set, find the first instance of the key in the tree and
	 * point the cursor at it.  Otherwise, find the first or the last record
	 * in the tree and point the cursor at it.  The cursor may not be moved
	 * until a new key has been found.
E 6
I 6
	 * Find the first, last or specific key in the tree and point the cursor
	 * at it.  The cursor may not be moved until a new key has been found.
E 6
	 */
	switch(flags) {
	case R_CURSOR:				/* Keyed scan. */
I 6
		/*
		 * Find the first instance of the key or the smallest key which
		 * is greater than or equal to the specified key.  If run out
		 * of keys, return RET_SPECIAL.
		 */
E 6
		if (key->data == NULL || key->size == 0) {
			errno = EINVAL;
E 5
			return (RET_ERROR);
D 5
		h = t->bt_curpage;
		if (flags == R_LAST || flags == R_PREV) {
E 5
I 5
		}
		e = __bt_first(t, key, &exact);	/* Returns pinned page. */
		if (e == NULL)
			return (RET_ERROR);
D 6
		if (!exact) {
			mpool_put(t->bt_mp, e->page, 0);
			return (RET_SPECIAL);
E 6
I 6
		/*
		 * If at the end of a page, skip any empty pages and find the
		 * next entry.
		 */
		if (e->index == NEXTINDEX(e->page)) {
			h = e->page;
			do {
				pg = h->nextpg;
				mpool_put(t->bt_mp, h, 0);
				if (pg == P_INVALID)
					return (RET_SPECIAL);
				if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
					return (RET_ERROR);
			} while (NEXTINDEX(h) == 0);
			e->index = 0;
			e->page = h;
E 6
		}
		*ep = *e;
		break;
	case R_FIRST:				/* First record. */
	case R_NEXT:
		/* Walk down the left-hand side of the tree. */
		for (pg = P_ROOT;;) {
			if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
				return (RET_ERROR);
D 7
			if (h->flags & (P_BLEAF|P_RLEAF))
E 7
I 7
			if (h->flags & (P_BLEAF | P_RLEAF))
E 7
				break;
			pg = GETBINTERNAL(h, 0)->pgno;
			mpool_put(t->bt_mp, h, 0);
		}
E 5

D 5
			/* backward scan */
			while (!(h->h_flags & F_LEAF)) {
				last = NEXTINDEX(h) - 1;
				id = (IDATUM *) GETDATUM(h,last);
				if (_bt_getpage(t, id->i_pgno) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
			}
E 5
I 5
		/* Skip any empty pages. */
		while (NEXTINDEX(h) == 0 && h->nextpg != P_INVALID) {
			pg = h->nextpg;
			mpool_put(t->bt_mp, h, 0);
			if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
				return (RET_ERROR);
		}
E 5

D 5
			/* skip empty pages */
			while (NEXTINDEX(h) == 0 && h->h_prevpg != P_NONE) {
				if (_bt_getpage(t, h->h_prevpg) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
			}
E 5
I 5
		if (NEXTINDEX(h) == 0) {
			mpool_put(t->bt_mp, h, 0);
			return (RET_SPECIAL);
		}
E 5

D 5
			c->c_pgno = h->h_pgno;
			if (NEXTINDEX(h) > 0)
				c->c_index = NEXTINDEX(h) - 1;
			else
				c->c_index = 0;
		} else if (flags == R_FIRST || flags == R_NEXT) {
			/* forward scan */
			while (!(h->h_flags & F_LEAF)) {
				id = (IDATUM *) GETDATUM(h,0);
				if (_bt_getpage(t, id->i_pgno) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
			}
E 5
I 5
		ep->page = h;
		ep->index = 0;
		break;
	case R_LAST:				/* Last record. */
	case R_PREV:
		/* Walk down the right-hand side of the tree. */
		for (pg = P_ROOT;;) {
			if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
				return (RET_ERROR);
D 7
			if (h->flags & (P_BLEAF|P_RLEAF))
E 7
I 7
			if (h->flags & (P_BLEAF | P_RLEAF))
E 7
				break;
			pg = GETBINTERNAL(h, NEXTINDEX(h) - 1)->pgno;
			mpool_put(t->bt_mp, h, 0);
		}
E 5

D 5
			/* skip empty pages */
			while (NEXTINDEX(h) == 0 && h->h_nextpg != P_NONE) {
				if (_bt_getpage(t, h->h_nextpg) == RET_ERROR)
					return (RET_ERROR);
				h = t->bt_curpage;
			}
E 5
I 5
		/* Skip any empty pages. */
		while (NEXTINDEX(h) == 0 && h->prevpg != P_INVALID) {
			pg = h->prevpg;
			mpool_put(t->bt_mp, h, 0);
			if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
				return (RET_ERROR);
		}
E 5

D 5
			c->c_pgno = h->h_pgno;
			c->c_index = 0;
		} else {
			/* no flags passed in */
			errno = EINVAL;
			return (RET_ERROR);
E 5
I 5
		if (NEXTINDEX(h) == 0) {
			mpool_put(t->bt_mp, h, 0);
			return (RET_SPECIAL);
E 5
		}
D 5
	}
E 5

D 5
	/* okay, scan is initialized */
	t->bt_flags |= BTF_SEQINIT;

I 2
	/* don't need the descent stack anymore */
	while (_bt_pop(t) != P_NONE)
		continue;

E 2
	if (c->c_index == NEXTINDEX(t->bt_curpage))
		return (RET_SPECIAL);

E 5
I 5
		ep->page = h;
		ep->index = NEXTINDEX(h) - 1;
		break;
	}
E 5
	return (RET_SUCCESS);
}

/*
D 5
 *  _BT_SEQADVANCE -- Advance the sequential scan on this tree.
E 5
I 5
 * BT_SEQADVANCE -- Advance the sequential scan.
E 5
 *
D 5
 *	Moves the current location pointer for the scan on this tree one
 *	spot in the requested direction.
E 5
I 5
 * Parameters:
 *	t:	tree
 *	flags:	R_NEXT, R_PREV
E 5
 *
D 5
 *	Parameters:
 *		t -- btree being scanned
 *		flags -- for R_NEXT, R_PREV
E 5
I 5
 * Side effects:
 *	Pins the page the new key/data record is on.
E 5
 *
D 5
 *	Returns:
 *		RET_SUCCESS, RET_ERROR, or RET_SPECIAL if there is no
 *		more data in the specified direction.
 *
 *	Side Effects:
 *		May change current page.
E 5
I 5
 * Returns:
 *	RET_ERROR, RET_SUCCESS or RET_SPECIAL if there's no next key.
E 5
 */
D 5

int
_bt_seqadvance(t, flags)
	BTREE_P t;
E 5
I 5
static int
bt_seqadv(t, e, flags)
	BTREE *t;
	EPG *e;
E 5
	int flags;
{
D 5
	BTHEADER *h;
	CURSOR *c;
E 5
I 5
	EPGNO *c, delc;
	PAGE *h;
E 5
D 9
	index_t index;
E 9
I 9
	indx_t index;
E 9
I 5
	pgno_t pg;
E 5

D 5
	c = &(t->bt_cursor);
	index = c->c_index;
E 5
I 5
	/* Save the current cursor if going to delete it. */
	c = &t->bt_bcursor;
D 10
	if (ISSET(t, BTF_DELCRSR))
E 10
I 10
	if (ISSET(t, B_DELCRSR))
E 10
		delc = *c;
E 5

D 5
	if (_bt_getpage(t, c->c_pgno) == RET_ERROR)
E 5
I 5
	if ((h = mpool_get(t->bt_mp, c->pgno, 0)) == NULL)
E 5
		return (RET_ERROR);
D 5
	h = t->bt_curpage;
E 5

D 5
	/* by the time we get here, don't need the cursor key anymore */
	if (c->c_key != (char *) NULL)
		(void) free(c->c_key);

	if (flags == R_NEXT) {

		/*
		 *  This is a forward scan.  If the cursor is pointing
		 *  at a virtual record (that is, it was pointing at
		 *  a record that got deleted), then we should return
		 *  the record it's pointing at now.  Otherwise, we
		 *  should advance the scan.  In either case, we need
		 *  to be careful not to run off the end of the current
		 *  page.
		 */

		if (c->c_flags & CRSR_BEFORE) {

			if (index >= NEXTINDEX(h)) {
				/* out of items on this page, get next page */
				if (h->h_nextpg == P_NONE) {
					/* tell caller we're done... */
					c->c_index = NEXTINDEX(h);
					return (RET_SPECIAL);
				}

				/* skip empty pages */
				do {
					if (_bt_getpage(t, h->h_nextpg)
					    == RET_ERROR) {
						c->c_index = NEXTINDEX(h);
						return (RET_ERROR);
					}
					h = t->bt_curpage;
					c->c_pgno = h->h_pgno;
				} while (NEXTINDEX(h) == 0
					 && h->h_nextpg != P_NONE);

				if (NEXTINDEX(h) == 0) {
					/* tell caller we're done */
					c->c_index = NEXTINDEX(h);
					return (RET_SPECIAL);
				}
				index = 0;
			}
			c->c_flags &= ~CRSR_BEFORE;

		} else if (++index >= NEXTINDEX(h)) {

			/* out of items on this page, get next page */
			if (h->h_nextpg == P_NONE) {
				/* tell caller we're done... */
				c->c_index = NEXTINDEX(h);
				return (RET_SPECIAL);
			}

			/* skip empty pages */
E 5
I 5
	/*
 	 * Find the next/previous record in the tree and point the cursor at it.
	 * The cursor may not be moved until a new key has been found.
	 */
	index = c->index;
	switch(flags) {
	case R_NEXT:			/* Next record. */
		if (++index == NEXTINDEX(h)) {
E 5
			do {
D 5
				if (_bt_getpage(t, h->h_nextpg) == RET_ERROR) {
					c->c_index = NEXTINDEX(h);
E 5
I 5
				pg = h->nextpg;
				mpool_put(t->bt_mp, h, 0);
				if (pg == P_INVALID)
					return (RET_SPECIAL);
				if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
E 5
					return (RET_ERROR);
D 5
				}
				h = t->bt_curpage;
				c->c_pgno = h->h_pgno;
			} while (NEXTINDEX(h) == 0 && h->h_nextpg != P_NONE);

			if (NEXTINDEX(h) == 0) {
				/* tell caller we're done */
				c->c_index = NEXTINDEX(h);
				return (RET_SPECIAL);
			}
E 5
I 5
			} while (NEXTINDEX(h) == 0);
E 5
			index = 0;
		}
D 5
	} else if (flags == R_PREV) {

		/* for backward scans, life is substantially easier */
		c->c_flags &= ~CRSR_BEFORE;
		if (c->c_key != (char *) NULL) {
			(void) free(c->c_key);
			c->c_key = (char *) NULL;
		}

		if (index == 0) {

			/* we may be done */
			c->c_index = 0;

			/* out of items on this page, get next page */
			if (h->h_prevpg == P_NONE)
				return (RET_SPECIAL);

			/* skip empty pages */
E 5
I 5
		break;
	case R_PREV:			/* Previous record. */
		if (index-- == 0) {
E 5
			do {
D 5
				if (_bt_getpage(t, h->h_prevpg) == RET_ERROR)
E 5
I 5
				pg = h->prevpg;
				mpool_put(t->bt_mp, h, 0);
				if (pg == P_INVALID)
					return (RET_SPECIAL);
				if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
E 5
					return (RET_ERROR);
D 5
				h = t->bt_curpage;
				c->c_pgno = h->h_pgno;
			} while (NEXTINDEX(h) == 0 && h->h_prevpg != P_NONE);

			if (NEXTINDEX(h) == 0)
				return (RET_SPECIAL);

E 5
I 5
			} while (NEXTINDEX(h) == 0);
E 5
			index = NEXTINDEX(h) - 1;
D 5
		} else
			--index;
	} else {
		/* must specify a direction */
		errno = EINVAL;
		return (RET_ERROR);
E 5
I 5
		}
		break;
E 5
	}

D 5
	c->c_index = index;
E 5
I 5
	e->page = h;
	e->index = index;

	/*
	 * Delete any already deleted record that we've been saving because the
	 * cursor pointed to it.  This could cause the new index to be shifted
	 * down by one if the record we're deleting is on the same page and has
	 * a larger index.
	 */
D 10
	if (ISSET(t, BTF_DELCRSR)) {
D 7
		UNSET(t, BTF_DELCRSR);			/* Don't try twice. */
E 7
I 7
		CLR(t, BTF_DELCRSR);			/* Don't try twice. */
E 10
I 10
	if (ISSET(t, B_DELCRSR)) {
		CLR(t, B_DELCRSR);			/* Don't try twice. */
E 10
E 7
		if (c->pgno == delc.pgno && c->index > delc.index)
			--c->index;
		if (__bt_crsrdel(t, &delc))
			return (RET_ERROR);
	}
E 5
	return (RET_SUCCESS);
I 5
}

/*
 * __BT_CRSRDEL -- Delete the record referenced by the cursor.
 *
 * Parameters:
 *	t:	tree
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__bt_crsrdel(t, c)
	BTREE *t;
	EPGNO *c;
{
	PAGE *h;
	int status;

D 7
	UNSET(t, BTF_DELCRSR);			/* Don't try twice. */
E 7
I 7
D 10
	CLR(t, BTF_DELCRSR);			/* Don't try twice. */
E 10
I 10
	CLR(t, B_DELCRSR);			/* Don't try twice. */
E 10
E 7
	if ((h = mpool_get(t->bt_mp, c->pgno, 0)) == NULL)
		return (RET_ERROR);
	status = __bt_dleaf(t, h, c->index);
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);
	return (status);
E 5
}
E 1
