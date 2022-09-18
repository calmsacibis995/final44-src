h38486
s 00002/00003/00296
d D 8.3 94/02/21 15:08:11 bostic 14 13
c first pass at making DB use basic integral types (the Alpha port)
e
s 00008/00000/00291
d D 8.2 93/09/07 11:50:56 bostic 13 12
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00289
d D 8.1 93/06/04 15:20:17 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00283
d D 5.11 93/05/16 15:42:55 bostic 11 10
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00001/00001/00290
d D 5.10 93/02/16 12:33:42 bostic 10 9
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00003/00003/00288
d D 5.9 93/02/14 17:39:18 bostic 9 8
c index -> indx_t
e
s 00001/00001/00290
d D 5.8 93/02/11 11:48:17 bostic 8 7
c typo, using wrong page in deletion loop; to test, insert a lot of
c records and delete them.  From philn@optigfx.com (Phil Nguyen)
e
s 00001/00001/00290
d D 5.7 93/02/11 11:39:20 bostic 7 6
c move db.h to the end of the includes, make compat.h work better
e
s 00003/00001/00288
d D 5.6 92/11/13 17:25:15 bostic 6 5
c require the cursor be initialized before deleting using R_CURSOR
e
s 00005/00003/00284
d D 5.5 92/11/13 16:05:09 bostic 5 4
c prettiness police
e
s 00040/00029/00247
d D 5.4 92/10/03 20:26:18 bostic 4 3
c fix delete code (pinning was incorrect)
e
s 00225/00124/00051
d D 5.3 91/09/04 12:47:07 bostic 3 2
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00002/00001/00173
d D 5.2 91/02/22 17:16:36 bostic 2 1
c ANSI prototypes
e
s 00174/00000/00000
d D 5.1 91/01/23 08:12:41 mao 1 0
c date and time created 91/01/23 08:12:41 by mao
e
u
U
t
T
I 1
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
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
D 2
#include <sys/errno.h>
E 2
D 3
#include <db.h>
E 3
I 2
D 5
#include <errno.h>
E 5
I 5

E 5
I 3
D 7
#include <db.h>
E 7
I 5
#include <errno.h>
E 5
#include <stdio.h>
E 3
#include <string.h>
I 5

I 7
#include <db.h>
E 7
E 5
E 2
#include "btree.h"

I 3
static int bt_bdelete __P((BTREE *, const DBT *));

E 3
/*
D 3
 *  _BT_CRSRDEL -- Delete the item pointed to by the cursor.
E 3
I 3
 * __BT_DELETE -- Delete the item(s) referenced by a key.
E 3
 *
D 3
 *	This routine deletes the item most recently returned by a scan
 *	through the tree.  Since it only makes sense to delete the current
 *	record once, we make sure that we don't try to delete twice without
 *	advancing the scan.
E 3
I 3
 * Parameters:
 *	dbp:	pointer to access method
 *	key:	key to delete
 *	flags:	R_CURSOR if deleting what the cursor references
E 3
 *
D 3
 *	Parameters:
 *		t -- tree in which to do deletion
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		The call to _bt_delone marks the cursor, so we can tell that
 *		the current record has been deleted.
E 3
I 3
 * Returns:
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key not found.
E 3
 */
D 3

E 3
int
D 3
_bt_crsrdel(t)
	BTREE_P t;
E 3
I 3
__bt_delete(dbp, key, flags)
	const DB *dbp;
	const DBT *key;
	u_int flags;
E 3
{
D 3
	CURSOR *c;
E 3
I 3
	BTREE *t;
	int status;
E 3

D 3
	c = &(t->bt_cursor);

	/* a cursor must exist, and can't have deleted the current key yet */
	if (!(t->bt_flags & BTF_SEQINIT) || (c->c_flags & CRSR_BEFORE)) {
		errno = EINVAL;
E 3
I 3
	t = dbp->internal;
I 13

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

E 13
D 11
	if (ISSET(t, BTF_RDONLY)) {
E 11
I 11
	if (ISSET(t, B_RDONLY)) {
E 11
		errno = EPERM;
E 3
		return (RET_ERROR);
	}
I 13

E 13
D 3

	if (_bt_getpage(t, c->c_pgno) == RET_ERROR)
		return (RET_ERROR);

	if (c->c_index >= NEXTINDEX(t->bt_curpage)) {
E 3
I 3
	switch(flags) {
	case 0:
		status = bt_bdelete(t, key);
		break;
	case R_CURSOR:
		/*
		 * If flags is R_CURSOR, delete the cursor; must already have
		 * started a scan and not have already deleted the record.  For
		 * the delete cursor bit to have been set requires that the
		 * scan be initialized, so no reason to check.
		 */
I 6
D 11
		if (!ISSET(t, BTF_SEQINIT))
E 11
I 11
		if (!ISSET(t, B_SEQINIT))
E 11
                        goto einval;
E 6
D 11
		status = ISSET(t, BTF_DELCRSR) ?
E 11
I 11
		status = ISSET(t, B_DELCRSR) ?
E 11
		    RET_SPECIAL : __bt_crsrdel(t, &t->bt_bcursor);
		break;
	default:
E 3
D 6
		errno = EINVAL;
E 6
I 6
einval:		errno = EINVAL;
E 6
		return (RET_ERROR);
	}
D 3

	return (_bt_delone(t, c->c_index));
E 3
I 3
	if (status == RET_SUCCESS)
D 11
		SET(t, BTF_MODIFIED);
E 11
I 11
		SET(t, B_MODIFIED);
E 11
	return (status);
E 3
}

/*
D 3
 *  _BT_DELONE -- Delete a single entry from a btree.
E 3
I 3
 * BT_BDELETE -- Delete all key/data pairs matching the specified key.
E 3
 *
D 3
 *	This routine physically removes a btree entry from a leaf page.
 *	IDATUM items are *never* removed from internal nodes, regardless
 *	of whether the entries that originally caused them to be added
 *	are removed from the tree or not.  In addition, pages made empty
 *	by element deletion are not actually reclaimed.  They are,
 *	however, made available for reuse.
E 3
I 3
 * Parameters:
 *	tree:	tree
 *	key:	key to delete
E 3
 *
D 3
 *	To delete an item from a page, we pack the remaining items at
 *	the end of the page, overwriting the deleted item's entry.  We
 *	move the line pointers backward on the page, overwriting the
 *	original item's line pointer.  This guarantees that the space in
 *	the middle of the page is free -- a property that our insertion
 *	strategy relies on.
 *
 *	This routine doesn't reclaim pages all of whose entries have
 *	been deleted.  These pages are available for reuse, however.
 *	If an item is deleted that was too big to fit on a page, then
 *	the blocks that it occupies are put on a free list for reuse.
 *
 *	Parameters:
 *		t -- btree from which to delete item
 *		index -- index of entry on current page to delete
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Physically changes page layout, adjusts internal page
 *		state to reflect the deletion of the item, and updates
 *		the list of free pages for this tree.
E 3
I 3
 * Returns:
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key not found.
E 3
 */
D 3

int
_bt_delone(t, index)
	BTREE_P t;
	index_t index;
E 3
I 3
static int
bt_bdelete(t, key)
	BTREE *t;
	const DBT *key;
E 3
{
D 3
	char *src, *dest;
	int nbytes, nmoved;
	index_t off;
	index_t top;
	index_t i;
	pgno_t chain;
	BTHEADER *h;
	CURSOR *c;
	DATUM *d;
E 3
I 3
	EPG *e, save;
	PAGE *h;
	pgno_t cpgno, pg;
D 9
	index_t cindex;
E 9
I 9
	indx_t cindex;
E 9
D 4
	int deleted, exact;
E 4
I 4
	int deleted, dirty1, dirty2, exact;
E 4

	/* Find any matching record; __bt_search pins the page. */
	if ((e = __bt_search(t, key, &exact)) == NULL)
		return (RET_ERROR);
	if (!exact) {
		mpool_put(t->bt_mp, e->page, 0);
		return (RET_SPECIAL);
	}

	/*
	 * Delete forward, then delete backward, from the found key.  The
	 * ordering is so that the deletions don't mess up the page refs.
D 4
	 * The first loop deletes the found key, the second unpins the found
	 * page.
E 4
I 4
	 * The first loop deletes the key from the original page, the second
	 * unpins the original page.  In the first loop, dirty1 is set if
	 * the original page is modified, and dirty2 is set if any subsequent
	 * pages are modified.  In the second loop, dirty1 starts off set if
	 * the original page has been modified, and is set if any subsequent
	 * pages are modified.
E 4
	 *
	 * If find the key referenced by the cursor, don't delete it, just
	 * flag it for future deletion.  The cursor page number is P_INVALID
	 * unless the sequential scan is initialized, so no reason to check.
	 * A special case is when the already deleted cursor record was the
	 * only record found.  If so, then the delete opertion fails as no
	 * records were deleted.
	 *
	 * Cycle in place in the current page until the current record doesn't
	 * match the key or the page is empty.  If the latter, walk forward,
D 4
	 * skipping empty pages and repeating until an record doesn't match
E 4
I 4
	 * skipping empty pages and repeating until a record doesn't match
E 4
	 * the key or the end of the tree is reached.
	 */
	cpgno = t->bt_bcursor.pgno;
	cindex = t->bt_bcursor.index;
	save = *e;
I 4
	dirty1 = 0;
E 4
	for (h = e->page, deleted = 0;;) {
I 4
		dirty2 = 0;
E 4
		do {
			if (h->pgno == cpgno && e->index == cindex) {
D 5
				if (NOTSET(t, BTF_DELCRSR)) {
E 5
I 5
D 11
				if (!ISSET(t, BTF_DELCRSR)) {
E 5
					SET(t, BTF_DELCRSR);
E 11
I 11
				if (!ISSET(t, B_DELCRSR)) {
					SET(t, B_DELCRSR);
E 11
					deleted = 1;
				}
				++e->index;
			} else {
D 4
				if (__bt_dleaf(t, h, e->index))
					goto err;
				mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 4
I 4
				if (__bt_dleaf(t, h, e->index)) {
					if (h->pgno != save.page->pgno)
						mpool_put(t->bt_mp, h, dirty2);
					mpool_put(t->bt_mp, save.page, dirty1);
					return (RET_ERROR);
				}
				if (h->pgno == save.page->pgno)
					dirty1 = MPOOL_DIRTY;
				else
					dirty2 = MPOOL_DIRTY;
E 4
				deleted = 1;
			}
		} while (e->index < NEXTINDEX(h) && __bt_cmp(t, key, e) == 0);

		/*
		 * Quit if didn't find a match, no next page, or first key on
D 4
		 * the next page doesn't match.  Make a special effort not to
		 * unpin the page the original match was on, but also make sure
		 * it's unpinned if an error occurs.
E 4
I 4
		 * the next page doesn't match.  Don't unpin the original page
		 * unless an error occurs.
E 4
		 */
		if (e->index < NEXTINDEX(h))
			break;
		for (;;) {
			if ((pg = h->nextpg) == P_INVALID)
				goto done1;
			if (h->pgno != save.page->pgno)
D 4
				mpool_put(t->bt_mp, h, 0);
E 4
I 4
				mpool_put(t->bt_mp, h, dirty2);
E 4
			if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL) {
D 4
				if (h->pgno == save.page->pgno)
					mpool_put(t->bt_mp, save.page, 0);
E 4
I 4
				mpool_put(t->bt_mp, save.page, dirty1);
E 4
				return (RET_ERROR);
			}
			if (NEXTINDEX(h) != 0) {
				e->page = h;
				e->index = 0;
				break;
			}
		}
E 3

D 3
	/* deletion may confuse an active scan.  fix it.  */
	c = &(t->bt_cursor);
	if (t->bt_flags & BTF_SEQINIT && t->bt_curpage->h_pgno == c->c_pgno)
		if (_bt_fixscan(t, index, (DATUM *) NULL, DELETE) == RET_ERROR)
			return (RET_ERROR);
E 3
I 3
		if (__bt_cmp(t, key, e) != 0)
			break;
	}
E 3

D 3
	h = t->bt_curpage;
	off = h->h_linp[index];
	d = (DATUM *) GETDATUM(h, index);
E 3
I 3
	/*
D 4
	 * Reach here with the last page that was looked at pinned, and it may
	 * or may not be the same as the page with the original match.  If it's
	 * not, release it.
E 4
I 4
	 * Reach here with the original page and the last page referenced
	 * pinned (they may be the same).  Release it if not the original.
E 4
	 */
done1:	if (h->pgno != save.page->pgno)
D 4
		mpool_put(t->bt_mp, h, 0);
E 4
I 4
		mpool_put(t->bt_mp, h, dirty2);
E 4
E 3

D 3
	/* if this is a big item, reclaim the space it occupies */
	if (d->d_flags & D_BIGKEY) {
		bcopy(&(d->d_bytes[0]),
		      (char *) &chain,
		      sizeof(chain));
		if (_bt_delindir(t, chain) == RET_ERROR)
E 3
I 3
	/*
	 * Walk backwards from the record previous to the record returned by
D 4
	 * __bt_search, skipping empty pages, until a current record doesn't
	 * match the key or reach the beginning of the tree.
E 4
I 4
	 * __bt_search, skipping empty pages, until a record doesn't match
	 * the key or reach the beginning of the tree.
E 4
	 */
	*e = save;
	for (;;) {
		if (e->index)
			--e->index;
		for (h = e->page; e->index; --e->index) {
			if (__bt_cmp(t, key, e) != 0)
				goto done2;
			if (h->pgno == cpgno && e->index == cindex) {
D 5
				if (NOTSET(t, BTF_DELCRSR)) {
E 5
I 5
D 11
				if (!ISSET(t, BTF_DELCRSR)) {
E 5
					SET(t, BTF_DELCRSR);
E 11
I 11
				if (!ISSET(t, B_DELCRSR)) {
					SET(t, B_DELCRSR);
E 11
					deleted = 1;
				}
			} else {
D 4
				if (__bt_dleaf(t, h, e->index) == RET_ERROR)
					goto err;
				mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 4
I 4
				if (__bt_dleaf(t, h, e->index) == RET_ERROR) {
					mpool_put(t->bt_mp, h, dirty1);
					return (RET_ERROR);
				}
				if (h->pgno == save.page->pgno)
					dirty1 = MPOOL_DIRTY;
E 4
				deleted = 1;
			}
		}

		if ((pg = h->prevpg) == P_INVALID)
			goto done2;
D 4
		mpool_put(t->bt_mp, h, 0);
E 4
I 4
		mpool_put(t->bt_mp, h, dirty1);
		dirty1 = 0;
E 4
		if ((e->page = mpool_get(t->bt_mp, pg, 0)) == NULL)
E 3
			return (RET_ERROR);
D 3
		h = t->bt_curpage;
		d = (DATUM *) GETDATUM(h, index);
E 3
I 3
D 8
		e->index = NEXTINDEX(h);
E 8
I 8
		e->index = NEXTINDEX(e->page);
E 8
E 3
	}
D 3
	if (d->d_flags & D_BIGDATA) {
		bcopy(&(d->d_bytes[d->d_ksize]),
		      (char *) &chain,
		      sizeof(chain));
		if (_bt_delindir(t, chain) == RET_ERROR)
			return (RET_ERROR);
		h = t->bt_curpage;
		d = (DATUM *) GETDATUM(h, index);
	}
E 3

D 3
	/* move the data down on the page */
	nbytes = d->d_ksize + d->d_dsize
		 + (sizeof(DATUM) - sizeof(char));
	nbytes = LONGALIGN(nbytes);
	src = ((char *) h) + h->h_upper;
	dest = src + nbytes;
	nmoved = (int) (((char *) d) - src);
	(void) bcopy(src, dest, nmoved);
E 3
I 3
	/*
	 * Reach here with the last page that was looked at pinned.  Release
	 * it.
	 */
D 4
done2:	mpool_put(t->bt_mp, h, 0);
E 4
I 4
done2:	mpool_put(t->bt_mp, h, dirty1);
E 4
	return (deleted ? RET_SUCCESS : RET_SPECIAL);
E 3
D 4

D 3
	/* next move the line pointers up */
	src = (char *) &(h->h_linp[index + 1]);
	dest = (char *) &(h->h_linp[index]);
	nmoved = (int) (((char *) &(h->h_linp[NEXTINDEX(h)])) - src);
	(void) bcopy(src, dest, nmoved);
E 3
I 3
err:	mpool_put(t->bt_mp, h, 0);
	return (RET_ERROR);
E 4
}
E 3

D 3
	/* remember that we freed up some space */
	h->h_upper += nbytes;
	h->h_lower -= sizeof(index_t);
E 3
I 3
/*
 * __BT_DLEAF -- Delete a single record from a leaf page.
 *
 * Parameters:
 *	t:	tree
 *	index:	index on current page to delete
 *
 * Returns:
 *	RET_SUCCESS, RET_ERROR.
 */
int
__bt_dleaf(t, h, index)
	BTREE *t;
	PAGE *h;
D 14
	int index;
E 14
I 14
	indx_t index;
E 14
{
	register BLEAF *bl;
D 9
	register index_t *ip, offset;
E 9
I 9
D 14
	register indx_t *ip, offset;
E 14
I 14
	register indx_t cnt, *ip, offset;
E 14
E 9
	register size_t nbytes;
D 14
	register int cnt;
E 14
	char *from;
	void *to;
E 3

D 3
	/* adjust offsets in line pointers affected by moving the data */
	top = NEXTINDEX(h);
	for (i = 0; i < top; i++) {
		if (h->h_linp[i] < off)
			h->h_linp[i] += nbytes;
	}
E 3
I 3
	/*
	 * Delete a record from a btree leaf page.  Internal records are never
	 * deleted from internal pages, regardless of the records that caused
	 * them to be added being deleted.  Pages made empty by deletion are
	 * not reclaimed.  They are, however, made available for reuse.
	 *
	 * Pack the remaining entries at the end of the page, shift the indices
	 * down, overwriting the deleted record and its index.  If the record
	 * uses overflow pages, make them available for reuse.
	 */
	to = bl = GETBLEAF(h, index);
	if (bl->flags & P_BIGKEY && __ovfl_delete(t, bl->bytes) == RET_ERROR)
		return (RET_ERROR);
	if (bl->flags & P_BIGDATA &&
	    __ovfl_delete(t, bl->bytes + bl->ksize) == RET_ERROR)
		return (RET_ERROR);
	nbytes = NBLEAF(bl);
E 3

D 3
	/* it's gone */
	h->h_flags |= F_DIRTY;
E 3
I 3
	/*
	 * Compress the key/data pairs.  Compress and adjust the [BR]LEAF
	 * offsets.  Reset the headers.
	 */
	from = (char *)h + h->upper;
D 10
	bcopy(from, from + nbytes, (char *)to - from);
E 10
I 10
	memmove(from + nbytes, from, (char *)to - from);
E 10
	h->upper += nbytes;
E 3

I 3
	offset = h->linp[index];
D 4
	for (cnt = &h->linp[index] - (ip = &h->linp[0]); cnt--; ++ip)
E 4
I 4
	for (cnt = index, ip = &h->linp[0]; cnt--; ++ip)
E 4
		if (ip[0] < offset)
			ip[0] += nbytes;
D 4
	for (cnt = &h->linp[NEXTINDEX(h)] - ip; --cnt; ++ip)
E 4
I 4
	for (cnt = NEXTINDEX(h) - index; --cnt; ++ip)
E 4
		ip[0] = ip[1] < offset ? ip[1] + nbytes : ip[1];
D 9
	h->lower -= sizeof(index_t);
E 9
I 9
	h->lower -= sizeof(indx_t);
E 9
E 3
	return (RET_SUCCESS);
}
E 1
