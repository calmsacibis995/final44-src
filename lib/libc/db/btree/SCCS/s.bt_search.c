h43823
s 00001/00001/00208
d D 8.6 94/03/15 07:19:22 bostic 15 14
c lint
e
s 00002/00002/00207
d D 8.5 94/02/21 15:08:15 bostic 14 13
c first pass at making DB use basic integral types (the Alpha port)
e
s 00042/00014/00167
d D 8.4 93/12/10 09:49:55 bostic 13 12
c search both backwards and forwards if the page is empty and
c duplicates are turned on
e
s 00096/00004/00085
d D 8.3 93/12/03 13:10:10 bostic 12 11
c if enough duplicate keys are entered and deleted, it's possible for
c the search to end up in a leaf page that doesn't have any of the searched
c for keys, while adjacent pages still have them.  If the key we end up with
c is not an exact match and we're on a page boundary, and duplicate keys are
c in the DB, check the adjacent pages for an exact match
e
s 00009/00013/00080
d D 8.2 93/09/14 10:18:17 bostic 11 10
c the __bt_search value shouldn't be stored in a static, can't pin
c across calls in that case
e
s 00002/00002/00091
d D 8.1 93/06/04 15:20:48 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00092
d D 5.9 93/02/14 17:39:22 bostic 9 8
c index -> indx_t
e
s 00001/00001/00092
d D 5.8 93/02/11 11:39:27 bostic 8 7
c move db.h to the end of the includes, make compat.h work better
e
s 00001/00000/00092
d D 5.7 93/01/10 12:32:07 bostic 7 6
c clear the stack in the search routine; it's a lot simpler
e
s 00010/00009/00082
d D 5.6 93/01/10 12:31:31 bostic 6 5
c if the tree is being prefix compressed, it's possible to get a base
c of zero.
e
s 00002/00000/00089
d D 5.5 92/11/13 16:05:25 bostic 5 4
c prettiness police
e
s 00001/00001/00088
d D 5.4 91/09/12 11:39:06 bostic 4 3
c bt_push -> __bt_push
e
s 00055/00236/00034
d D 5.3 91/09/04 12:47:20 bostic 3 2
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00001/00001/00269
d D 5.2 91/04/08 20:55:06 bostic 2 1
c use the pointer name, not the address of its first element
e
s 00270/00000/00000
d D 5.1 91/01/23 08:12:43 mao 1 0
c date and time created 91/01/23 08:12:43 by mao
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
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
I 5

E 5
D 8
#include <db.h>
E 8
I 3
#include <stdio.h>
I 5

I 8
#include <db.h>
E 8
E 5
E 3
#include "btree.h"

I 12
D 13
static EPG *bt_snext __P((BTREE *, PAGE *, const DBT *, int *));
static EPG *bt_sprev __P((BTREE *, PAGE *, const DBT *, int *));
E 13
I 13
static int bt_snext __P((BTREE *, PAGE *, const DBT *, int *));
static int bt_sprev __P((BTREE *, PAGE *, const DBT *, int *));
E 13

E 12
/*
D 3
 *  _BT_FIRST -- Find the first item in the tree that matches the supplied
 *		 key.
E 3
I 3
 * __BT_SEARCH -- Search a btree for a key.
E 3
 *
D 3
 *	This routine supports deletion.  When the user supplies a key to
 *	be deleted, we find the first one, and iteratively delete all the
 *	matching ones that follow it.
E 3
I 3
 * Parameters:
 *	t:	tree to search
 *	key:	key to find
 *	exactp:	pointer to exact match flag
E 3
 *
D 3
 *	Parameters:
 *		t -- btree in which to find first occurrence
 *		key -- key to find
E 3
I 3
 * Returns:
D 11
 *	EPG for matching record, if any, or the EPG for the location of the
 *	key, if it were inserted into the tree.
E 3
 *
D 3
 *	Returns:
 *		The BTITEM for the matching item.  If there's no match,
 *		this may point to the first item > than the supplied key,
 *		or off the end of the page.
 *
 *	Warnings:
 *		The BTITEM returned is in static space and will be overwritten
 *		by the next search of any kind in any btree.
E 3
I 3
 * Warnings:
 *	The EPG returned is in static memory, and will be overwritten by the
 *	next search of any kind in any tree.
E 11
I 11
 *	The EPG for matching record, if any, or the EPG for the location
 *	of the key, if it were inserted into the tree, is entered into
 *	the bt_cur field of the tree.  A pointer to the field is returned.
E 11
E 3
 */
D 3

BTITEM *
_bt_first(t, key)
	BTREE_P t;
	DBT *key;
E 3
I 3
EPG *
__bt_search(t, key, exactp)
	BTREE *t;
	const DBT *key;
	int *exactp;
E 3
{
D 3
	BTHEADER *h;
	BTITEM *item;
	index_t next;
	int r;
E 3
I 3
D 9
	register index_t index;
E 9
I 9
D 12
	register indx_t index;
E 9
	register int base, cmp, lim;
	register PAGE *h;
E 12
I 12
D 15
	PAGE *h, *n;
E 15
I 15
	PAGE *h;
E 15
D 14
	indx_t index;
E 14
I 14
	indx_t base, index, lim;
E 14
E 12
	pgno_t pg;
I 12
D 14
	int base, cmp, lim;
E 14
I 14
	int cmp;
E 14
E 12
D 11
	static EPG e;
E 11
E 3

I 7
	BT_CLR(t);
E 7
D 3
	/* find any matching item */
	item = _bt_search(t, key);
	h = t->bt_curpage;
	next = NEXTINDEX(h);
E 3
I 3
	for (pg = P_ROOT;;) {
		if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
			return (NULL);
E 3

D 3
	/* if we're off the end of the page, search failed and we're done */
	if (item->bti_index >= next)
		return (item);

	/* as long as we have an exact match, walk backwards */
	while ((r = _bt_cmp(t, key->data, item->bti_index)) == 0) {

		/* at start of page? */
		if (item->bti_index == 0) {

			/* if no prev page, we're done */
			if (h->h_prevpg == P_NONE)
				return (item);

			/* walk backward, skipping empty pages */
			do {
				if (_bt_getpage(t, h->h_prevpg) == RET_ERROR)
					return ((BTITEM *) NULL);
				h = t->bt_curpage;
			} while (NEXTINDEX(h) == 0 && h->h_prevpg != P_NONE);

			if (NEXTINDEX(h) != 0)
				item->bti_index = NEXTINDEX(h) - 1;
			else
				item->bti_index = 0;

			item->bti_pgno = h->h_pgno;
		} else {
			item->bti_index--;
		}
	}

	/* if we went too far backwards, step forward one entry */
	if (r > 0) {
		if (++(item->bti_index) >= NEXTINDEX(h)
		    && h->h_nextpg != P_NONE) {

			/* walk forward, skipping empty pages */
			do {
				if (_bt_getpage(t, h->h_nextpg) == RET_ERROR)
					return ((BTITEM *) NULL);
				h = t->bt_curpage;
			} while (h->h_nextpg != P_NONE && NEXTINDEX(h) == 0);

			item->bti_index = 0;
			item->bti_pgno = h->h_pgno;
		}
	}

	/* got it */
	return (item);
}

/*
 *  _BT_SEARCH, _BT_SEARCHR -- Search for a particular key in the tree.
 *
 *	Parameters:
 *		t -- btree in which to search
 *		key -- key to find
 *
 *	Returns:
 *		BTITEM for matching item, if any, or the BTITEM for the
 *		location of the key, if it were in the tree.
 *
 *	Warnings:
 *		The BTITEM returned is in static memory, and will be
 *		overwritten by the next search of any kind in any tree.
 */

BTITEM *
_bt_search(t, key)
	BTREE_P t;
	DBT *key;
{
	/* we want to start all of our searches at the root */
	if (_bt_getpage(t, (pgno_t) P_ROOT) == RET_ERROR)
		return ((BTITEM *) NULL);

	return (_bt_searchr(t, key));
}

BTITEM *
_bt_searchr(t, key)
	BTREE_P t;
	DBT *key;
{
	BTHEADER *h = t->bt_curpage;
	index_t index;
	IDATUM *id;
	DATUM *d;
	static BTITEM item;

	/* do a binary search on the current page */
D 2
	index = _bt_binsrch(t, &(key->data[0]));
E 2
I 2
	index = _bt_binsrch(t, key->data);
E 2

	/*
	 *  At this point, the binary search terminated because the endpoints
	 *  got too close together, or we have a match.  Figure out which
	 *  case applies and decide what to do based on the page type.
	 */
	if (h->h_flags & F_LEAF) {
		item.bti_pgno = h->h_pgno;
		item.bti_index = index;
		if (index < NEXTINDEX(h))
			d = (DATUM *) GETDATUM(h,index);
		else
			d = (DATUM *) NULL;

		item.bti_datum = d;
		return(&item);
	} else {
		id = (IDATUM *) GETDATUM(h, index);
		if (_bt_push(t, h->h_pgno) == RET_ERROR)
			return ((BTITEM *) NULL);
		if (_bt_getpage(t, id->i_pgno) == RET_ERROR)
			return ((BTITEM *) NULL);
		return (_bt_searchr(t, key));
	}
}

/*
 *  _BT_BINSRCH -- Do a binary search for a given key on the current page.
 *
 *	Searches on internal pages are handled slightly differently from
 *	searches on leaf pages.  This is because internal page searches
 *	find the largest item <= key in the tree, and leaf searches find
 *	the smallest item >= key.  This guarantees that leaf page searches
 *	leave us pointing at the item's correct position, and internal
 *	searches descend the tree correctly.
 *
 *	Parameters:
 *		t -- tree to search
 *		key -- key we're looking for
 *
 *	Returns:
 *		Index of the line pointer array entry for the (closest)
 *		match to key on the current page, with "closest" as defined
 *		above.
 */

index_t
_bt_binsrch(t, key)
	BTREE_P t;
	char *key;
{
	index_t lbound, ubound, cur;
	BTHEADER *h = t->bt_curpage;
	int match = 0;
	int r;

	lbound = 0;
	ubound = NEXTINDEX(h);
	if (ubound > 0)
		--ubound;

	/* do a binary search on the current page */
	while ((ubound - lbound) > 1) {
		cur = lbound + ((ubound - lbound) / 2);
		r = _bt_cmp(t, key, cur);

		if (r > 0)
			lbound = cur + 1;
		else if (r < 0)
			ubound = cur;
		else {
			match++;
			break;
		}
	}

	/*
	 *  At this point, the binary search terminated because the endpoints
	 *  got too close together, or we have a match.  Figure out which
	 *  case applies, decide what to do based on the page type (leaf or
	 *  internal), and do the right thing.
	 */
	if (match) {
		return (cur);
	} else if (ubound != lbound) {
		if (h->h_flags & F_LEAF) {
			r = _bt_cmp(t, key, lbound);
			if (r <= 0) {
				return (lbound);
E 3
I 3
		/* Do a binary search on the current page. */
D 11
		e.page = h;
E 11
I 11
		t->bt_cur.page = h;
E 11
		for (base = 0, lim = NEXTINDEX(h); lim; lim >>= 1) {
D 11
			e.index = index = base + (lim >> 1);
			if ((cmp = __bt_cmp(t, key, &e)) == 0) {
E 11
I 11
			t->bt_cur.index = index = base + (lim >> 1);
			if ((cmp = __bt_cmp(t, key, &t->bt_cur)) == 0) {
E 11
				if (h->flags & P_BLEAF) {
					*exactp = 1;
D 11
					return (&e);
E 11
I 11
					return (&t->bt_cur);
E 11
				}
				goto next;
E 3
			}
D 3
		} else {
			r = _bt_cmp(t, key, ubound);

			/* for internal nodes, move as far left as possible */
			if (r < 0) {
				r = _bt_cmp(t, key, lbound);
				if (r < 0 && lbound > 0)
					--lbound;
				return (lbound);
			} else {
				return (ubound);
E 3
I 3
			if (cmp > 0) {
				base = index + 1;
				--lim;
E 3
			}
		}
D 3
	}
E 3

D 3
	if (h->h_flags & F_LEAF) {
		if (ubound < NEXTINDEX(h)) {
			r = _bt_cmp(t, key, ubound);
			if (r > 0)
				ubound++;
E 3
I 3
D 6
		/*
		 * No match found.  Base is the smallest index greater than
		 * key but may be an illegal index.  Use base if it's a leaf
		 * page, decrement it by one if it's an internal page.  This
		 * is safe because internal pages can't be empty.
		 */
		index = h->flags & P_BLEAF ? base : base - 1;

E 6
D 12
		/* If it's a leaf page, we're done. */
E 12
I 12
		/*
		 * If it's a leaf page, and duplicates aren't allowed, we're
D 13
		 * done.  If duplicates are allowed, it's possible that the
		 * matching spanned pages, and were later deleted, so we could
		 * be on the wrong page.  If we're at the start or end of a
		 * page, check.
E 13
I 13
		 * done.  If duplicates are allowed, it's possible that there
		 * were duplicate keys on duplicate pages, and they were later
		 * deleted, so we could be on a page with no matches while
		 * there are matches on other pages.  If we're at the start or
		 * end of a page, check on both sides.
E 13
		 */
E 12
		if (h->flags & P_BLEAF) {
D 6
			e.index = index;
E 6
I 6
D 11
			e.index = base;
E 11
I 11
			t->bt_cur.index = base;
E 11
E 6
			*exactp = 0;
I 12
			if (!ISSET(t, B_NODUPS)) {
D 13
				if (base == 0 && h->prevpg != P_INVALID)
					return (bt_sprev(t, h, key, exactp));
E 13
I 13
				if (base == 0 &&
				    bt_sprev(t, h, key, exactp))
					return (&t->bt_cur);
E 13
				if (base == NEXTINDEX(h) &&
D 13
				    h->nextpg != P_INVALID)
					return (bt_snext(t, h, key, exactp));
E 13
I 13
				    bt_snext(t, h, key, exactp))
					return (&t->bt_cur);
E 13
			}
E 12
D 11
			return (&e);
E 11
I 11
			return (&t->bt_cur);
E 11
E 3
		}
I 6

		/*
		 * No match found.  Base is the smallest index greater than
		 * key and may be zero or a last + 1 index.  If it's non-zero,
		 * decrement by one, and record the internal page which should
		 * be a parent page for the key.  If a split later occurs, the
		 * inserted page will be to the right of the saved page.
		 */
		index = base ? base - 1 : base;
E 6
D 3
	} else {
		/* for internal pages, move as far left as possible */
		if (ubound == NEXTINDEX(h))
			ubound--;
E 3

D 3
		while (_bt_cmp(t, key, ubound) < 0)
			ubound--;
E 3
I 3
D 4
next:		if (bt_push(t, h->pgno, index) == RET_ERROR)
E 4
I 4
next:		if (__bt_push(t, h->pgno, index) == RET_ERROR)
E 4
			return (NULL);
		pg = GETBINTERNAL(h, index)->pgno;
		mpool_put(t->bt_mp, h, 0);
E 3
	}
I 12
}

D 13
static EPG *
E 13
I 13
/*
 * BT_SNEXT -- Check for an exact match after the key.
 *
 * Parameters:
 *	t:	tree to search
 *	h:	current page.
 *	key:	key to find
 *	exactp:	pointer to exact match flag
 *
 * Returns:
 *	If an exact match found.
 */
static int
E 13
bt_snext(t, h, key, exactp)
	BTREE *t;
	PAGE *h;
	const DBT *key;
	int *exactp;
{
	EPG e;
	PAGE *tp;
	pgno_t pg;

	/* Skip until reach the end of the tree or a key. */
	for (pg = h->nextpg; pg != P_INVALID;) {
		if ((tp = mpool_get(t->bt_mp, pg, 0)) == NULL) {
			mpool_put(t->bt_mp, h, 0);
			return (NULL);
		}
		if (NEXTINDEX(tp) != 0)
			break;
		pg = tp->prevpg;
		mpool_put(t->bt_mp, tp, 0);
	}
	/*
	 * The key is either an exact match, or not as good as
	 * the one we already have.
	 */
	if (pg != P_INVALID) {
		e.page = tp;
		e.index = NEXTINDEX(tp) - 1;
		if (__bt_cmp(t, key, &e) == 0) {
			mpool_put(t->bt_mp, h, 0);
			t->bt_cur = e;
			*exactp = 1;
I 13
			return (1);
E 13
		}
	}
D 13
	return (&t->bt_cur);
E 13
I 13
	return (0);
E 13
}

D 13
static EPG *
E 13
I 13
/*
 * BT_SPREV -- Check for an exact match before the key.
 *
 * Parameters:
 *	t:	tree to search
 *	h:	current page.
 *	key:	key to find
 *	exactp:	pointer to exact match flag
 *
 * Returns:
 *	If an exact match found.
 */
static int
E 13
bt_sprev(t, h, key, exactp)
	BTREE *t;
	PAGE *h;
	const DBT *key;
	int *exactp;
{
	EPG e;
	PAGE *tp;
	pgno_t pg;

	/* Skip until reach the beginning of the tree or a key. */
	for (pg = h->prevpg; pg != P_INVALID;) {
		if ((tp = mpool_get(t->bt_mp, pg, 0)) == NULL) {
			mpool_put(t->bt_mp, h, 0);
			return (NULL);
		}
		if (NEXTINDEX(tp) != 0)
			break;
		pg = tp->prevpg;
		mpool_put(t->bt_mp, tp, 0);
	}
	/*
	 * The key is either an exact match, or not as good as
	 * the one we already have.
	 */
	if (pg != P_INVALID) {
		e.page = tp;
		e.index = NEXTINDEX(tp) - 1;
		if (__bt_cmp(t, key, &e) == 0) {
			mpool_put(t->bt_mp, h, 0);
			t->bt_cur = e;
			*exactp = 1;
I 13
			return (1);
E 13
		}
	}
D 13
	return (&t->bt_cur);
E 13
I 13
	return (0);
E 13
E 12
D 3
	return (ubound);
E 3
}
E 1
