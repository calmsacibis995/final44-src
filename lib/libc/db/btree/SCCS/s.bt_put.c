h12564
s 00010/00011/00282
d D 8.3 93/09/16 16:41:42 bostic 18 17
c was returning a pointer into the stack!
c change to use bt_cur as bt_search does
e
s 00006/00000/00287
d D 8.2 93/09/07 11:49:01 bostic 17 16
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00285
d D 8.1 93/06/04 15:20:43 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00280
d D 5.15 93/05/16 15:41:48 bostic 15 14
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00007/00005/00280
d D 5.14 93/02/16 12:33:46 bostic 14 13
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00005/00005/00280
d D 5.13 93/02/14 17:39:21 bostic 13 12
c index -> indx_t
e
s 00001/00001/00284
d D 5.12 93/02/11 11:39:27 bostic 12 11
c move db.h to the end of the includes, make compat.h work better
e
s 00000/00003/00285
d D 5.11 93/01/10 12:32:26 bostic 11 10
c clear the stack in the search routine; it's a lot simpler
e
s 00003/00003/00285
d D 5.10 93/01/10 12:23:24 bostic 10 9
c just clear the stack in on entry to put instead of trying to
c clear it when it's used
e
s 00005/00005/00283
d D 5.9 92/12/04 14:18:15 bostic 9 8
c R_CURSOR fails if cursor not initialized or if cursor deleted
e
s 00019/00009/00269
d D 5.8 92/11/13 17:15:01 bostic 8 7
c lint cleanup, prettiness polic, add R_SETCURSOR
e
s 00004/00004/00274
d D 5.7 92/10/13 13:00:00 bostic 7 6
c bcopy the pgno/size for overflow pages, may not be long aligned
c flag all overflow pages with P_OVERFLOW, not just the first one.
e
s 00001/00001/00277
d D 5.6 91/12/11 10:16:15 bostic 6 5
c If two keys compare equal, return the index of the matching key
c not the next index.  Test case is inserting two identical keys
c into the database at the beginning of a page (before anything else).
e
s 00062/00035/00216
d D 5.5 91/09/12 11:07:26 bostic 5 4
c fix overflow checking code to always keep the key in memory, if possible
c and take into account both key and data; add MODIFIED bit; fix maxkepage and
c minkeypage (bt_ovflsize)
e
s 00190/00225/00061
d D 5.4 91/09/04 12:47:19 bostic 4 3
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00002/00000/00284
d D 5.3 91/02/22 17:16:37 bostic 3 2
c ANSI prototypes
e
s 00004/00001/00280
d D 5.2 91/02/18 22:48:49 mao 2 1
c fix stack management bug
e
s 00281/00000/00000
d D 5.1 91/01/23 08:12:42 mao 1 0
c date and time created 91/01/23 08:12:42 by mao
e
u
U
t
T
I 1
/*-
D 16
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
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
I 4
D 8
#include <errno.h>
E 8
I 8

E 8
E 4
D 12
#include <db.h>
E 12
I 8
#include <errno.h>
E 8
I 4
#include <stdio.h>
E 4
I 3
#include <stdlib.h>
#include <string.h>
I 8

I 12
#include <db.h>
E 12
E 8
E 3
#include "btree.h"

I 4
static EPG *bt_fast __P((BTREE *, const DBT *, const DBT *, int *));

E 4
/*
D 4
 *  _BT_INSERT -- Insert a new user datum in the btree.
E 4
I 4
 * __BT_PUT -- Add a btree item to the tree.
E 4
 *
D 4
 *	This routine is called by bt_put, the public interface, once the
 *	location for the new item is known.  We do the work here, and
 *	handle splits if necessary.
E 4
I 4
 * Parameters:
 *	dbp:	pointer to access method
 *	key:	key
 *	data:	data
 *	flag:	R_NOOVERWRITE
E 4
 *
D 4
 *	Parameters:
 *		t -- btree in which to do the insertion.
 *		item -- BTITEM describing location of new datum
 *		key -- key to insert
 *		data -- data associated with key
 *		flag -- magic cookie passed recursively to bt_put if we
 *			have to do a split
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
E 4
I 4
 * Returns:
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key is already in the
 *	tree and R_NOOVERWRITE specified.
E 4
 */
D 4

E 4
int
D 4
_bt_insert(t, item, key, data, flag)
	BTREE_P t;
	BTITEM *item;
	DBT *key;
	DBT *data;
	int flag;
E 4
I 4
__bt_put(dbp, key, data, flags)
	const DB *dbp;
D 8
	const DBT *key, *data;
E 8
I 8
	DBT *key;
	const DBT *data;
E 8
	u_int flags;
E 4
{
D 4
	index_t index;
	BTHEADER *h;
	DATUM *d;
	int nbytes;
	int status;
	pgno_t pgno;
	int keysize, datasize;
	int bigkey, bigdata;
E 4
I 4
	BTREE *t;
	DBT tkey, tdata;
	EPG *e;
	PAGE *h;
D 13
	index_t index, nxtindex;
E 13
I 13
	indx_t index, nxtindex;
E 13
	pgno_t pg;
	size_t nbytes;
D 5
	int dflags, exact;
E 5
I 5
	int dflags, exact, status;
E 5
	char *dest, db[NOVFLSIZE], kb[NOVFLSIZE];
E 4

I 8
	t = dbp->internal;

I 17
	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

E 17
I 10
D 11
	/* Clear any stack. */
	BT_CLR(t);

E 11
E 10
E 8
D 4
	if (_bt_getpage(t, item->bti_pgno) == RET_ERROR)
E 4
I 4
D 5
	if (flags && flags != R_NOOVERWRITE) {
E 5
I 5
	switch (flags) {
	case R_CURSOR:
D 9
		if (ISSET(t, BTF_DELCRSR)) {
			errno = EINVAL;
			return (RET_ERROR);
		}
E 9
I 9
D 15
		if (!ISSET(t, BTF_SEQINIT))
E 15
I 15
		if (!ISSET(t, B_SEQINIT))
E 15
			goto einval;
D 15
		if (ISSET(t, BTF_DELCRSR))
E 15
I 15
		if (ISSET(t, B_DELCRSR))
E 15
			goto einval;
E 9
		break;
	case 0:
	case R_NOOVERWRITE:
		break;
	default:
E 5
D 9
		errno = EINVAL;
E 9
I 9
einval:		errno = EINVAL;
E 9
E 4
		return (RET_ERROR);
D 4
	h = t->bt_curpage;

	if (TOOBIG(t, data->size)) {
		bigdata = TRUE;
		datasize = sizeof(pgno_t);
	} else {
		bigdata = FALSE;
		datasize = data->size;
E 4
	}
I 5

E 5
D 4

	if (TOOBIG(t, key->size)) {
		bigkey = TRUE;
		keysize = sizeof(pgno_t);
	} else {
		bigkey = FALSE;
		keysize = key->size;
E 4
I 4
D 8
	t = dbp->internal;
E 8
D 15
	if (ISSET(t, BTF_RDONLY)) {
E 15
I 15
	if (ISSET(t, B_RDONLY)) {
E 15
		errno = EPERM;
		return (RET_ERROR);
E 4
	}
D 4

	nbytes = keysize + datasize + (sizeof(DATUM) - sizeof(char));
	nbytes = LONGALIGN(nbytes) + sizeof(index_t);

	/* if there's not enough room here, split the page */
	if ((h->h_upper - h->h_lower) < nbytes) {
		if (_bt_split(t) == RET_ERROR)
E 4
I 4
D 5
	
E 5
I 5

E 5
	/*
	 * If the key/data won't fit on a page, store it on indirect pages.
I 5
	 * Only store the key on the overflow page if it's too big after the
	 * data is on an overflow page.
E 5
	 *
	 * XXX
	 * If the insert fails later on, these pages aren't recovered.
	 */
	dflags = 0;
D 5
	if (key->size >= t->bt_minkeypage) {
		if (__ovfl_put(t, key, &pg) == RET_ERROR)
E 4
			return (RET_ERROR);
D 4

D 2
		/* okay, try again */
E 2
I 2
		/* okay, try again (empty the stack first, though) */
		while (_bt_pop((BTREE) t) != P_NONE)
			continue;

E 2
		return (bt_put((BTREE) t, key, data, flag));
E 4
I 4
		tkey.data = kb;
		tkey.size = NOVFLSIZE;
		*(pgno_t *)kb = pg;
		*(size_t *)(kb + sizeof(pgno_t)) = key->size;
		dflags |= P_BIGKEY;
		key = &tkey;
E 5
I 5
	if (key->size + data->size > t->bt_ovflsize) {
		if (key->size > t->bt_ovflsize) {
storekey:		if (__ovfl_put(t, key, &pg) == RET_ERROR)
				return (RET_ERROR);
			tkey.data = kb;
			tkey.size = NOVFLSIZE;
D 7
			*(pgno_t *)kb = pg;
			*(size_t *)(kb + sizeof(pgno_t)) = key->size;
E 7
I 7
D 14
			bcopy(&pg, kb, sizeof(pgno_t));
			bcopy(&key->size, kb + sizeof(pgno_t), sizeof(size_t));
E 14
I 14
			memmove(kb, &pg, sizeof(pgno_t));
			memmove(kb + sizeof(pgno_t),
			    &key->size, sizeof(size_t));
E 14
E 7
			dflags |= P_BIGKEY;
			key = &tkey;
		}
		if (key->size + data->size > t->bt_ovflsize) {
			if (__ovfl_put(t, data, &pg) == RET_ERROR)
				return (RET_ERROR);
			tdata.data = db;
			tdata.size = NOVFLSIZE;
D 7
			*(pgno_t *)db = pg;
			*(size_t *)(db + sizeof(pgno_t)) = data->size;
E 7
I 7
D 14
			bcopy(&pg, db, sizeof(pgno_t));
			bcopy(&data->size, db + sizeof(pgno_t), sizeof(size_t));
E 14
I 14
			memmove(db, &pg, sizeof(pgno_t));
			memmove(db + sizeof(pgno_t),
			    &data->size, sizeof(size_t));
E 14
E 7
			dflags |= P_BIGDATA;
			data = &tdata;
		}
		if (key->size + data->size > t->bt_ovflsize)
			goto storekey;
E 5
E 4
	}
D 4

	/* put together a leaf page datum from the key/data pair */
	index = item->bti_index;
	nbytes = keysize + datasize + (sizeof(DATUM) - sizeof(char));

	if ((d = (DATUM *) malloc((unsigned) nbytes)) == (DATUM *) NULL)
		return (RET_ERROR);

	d->d_ksize = keysize;
	d->d_dsize = datasize;
	d->d_flags = 0;

	if (bigkey) {
		if (_bt_indirect(t, key, &pgno) == RET_ERROR)
E 4
I 4
D 5
	if (data->size >= t->bt_minkeypage) {
		if (__ovfl_put(t, data, &pg) == RET_ERROR)
E 5
I 5

	/* Replace the cursor. */
	if (flags == R_CURSOR) {
		if ((h = mpool_get(t->bt_mp, t->bt_bcursor.pgno, 0)) == NULL)
E 5
E 4
			return (RET_ERROR);
D 4
		(void) bcopy((char *) &pgno, &(d->d_bytes[0]), sizeof(pgno));
		d->d_flags |= D_BIGKEY;
		if (_bt_getpage(t, item->bti_pgno) == RET_ERROR)
			return (RET_ERROR);
	} else {
		if (d->d_ksize > 0) {
			(void) bcopy((char *) key->data,
				      (char *) &(d->d_bytes[0]),
				      (int) d->d_ksize);
		}
E 4
I 4
D 5
		tdata.data = db;
		tdata.size = NOVFLSIZE;
		*(pgno_t *)db = pg;
		*(size_t *)(db + sizeof(pgno_t)) = data->size;
		dflags |= P_BIGDATA;
		data = &tdata;
E 5
I 5
		index = t->bt_bcursor.index;
		goto delete;
E 5
E 4
	}

D 4
	if (bigdata) {
		if (_bt_indirect(t, data, &pgno) == RET_ERROR)
E 4
I 4
D 5
	/* bt_fast and __bt_search pin the returned page. */
E 5
I 5
	/*
	 * Find the key to delete, or, the location at which to insert.  Bt_fast
	 * and __bt_search pin the returned page.
	 */
E 5
	if (t->bt_order == NOT || (e = bt_fast(t, key, data, &exact)) == NULL)
		if ((e = __bt_search(t, key, &exact)) == NULL)
E 4
			return (RET_ERROR);
D 4
		(void) bcopy((char *) &pgno,
			     &(d->d_bytes[keysize]),
			     sizeof(pgno));
		d->d_flags |= D_BIGDATA;
		if (_bt_getpage(t, item->bti_pgno) == RET_ERROR)
			return (RET_ERROR);
	} else {
		if (d->d_dsize > 0) {
			(void) bcopy((char *) data->data,
				      (char *) &(d->d_bytes[keysize]),
				      (int) d->d_dsize);
		}
	}
E 4
D 5

E 5
D 4
	/* do the insertion */
	status = _bt_insertat(t, (char *) d, index);
E 4
I 4
	h = e->page;
	index = e->index;
E 4

D 4
	(void) free((char *) d);

	return (status);
}

/*
 *  _BT_INSERTI -- Insert IDATUM on current page in the btree.
 *
 *	This routine handles insertions to internal pages after splits
 *	lower in the tree.  On entry, t->bt_curpage is the page to get
 *	the new IDATUM.  We are also given pgno, the page number of the
 *	IDATUM that is immediately left of the new IDATUM's position.
 *	This guarantees that the IDATUM for the right half of the page
 *	after a split goes next to the IDATUM for its left half.
 *
 *	Parameters:
 *		t -- tree in which to do insertion.
 *		id -- new IDATUM to insert
 *		pgno -- page number of IDATUM left of id's position
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 */

int
_bt_inserti(t, id, pgno)
	BTREE_P t;
	IDATUM *id;
	pgno_t pgno;
{
	BTHEADER *h = t->bt_curpage;
	index_t next, i;
	IDATUM *idx;
	char *key;
	pgno_t chain;
	int free_key;
	int ignore;

	if (id->i_flags & D_BIGKEY) {
		free_key = TRUE;
		bcopy(&(id->i_bytes[0]), (char *) &chain, sizeof(chain));
		if (_bt_getbig(t, chain, &key, &ignore) == RET_ERROR)
E 4
I 4
	/*
	 * Add the specified key/data pair to the tree.  If an identical key
	 * is already in the tree, and R_NOOVERWRITE is set, an error is
	 * returned.  If R_NOOVERWRITE is not set, the key is either added (if
	 * duplicates are permitted) or an error is returned.
	 *
	 * Pages are split as required.
	 */
	switch (flags) {
	case R_NOOVERWRITE:
		if (!exact)
			break;
		/*
		 * One special case is if the cursor references the record and
D 5
		 * it's been flagged for deletion.  If so, we delete it and
		 * pretend it was never there.  Since the cursor will move to
		 * the next record the inserted record won't be seen.
E 5
I 5
		 * it's been flagged for deletion.  Then, we delete the record,
		 * leaving the cursor there -- this means that the inserted
		 * record will not be seen in a cursor scan.
E 5
		 */
D 15
		if (ISSET(t, BTF_DELCRSR) && t->bt_bcursor.pgno == h->pgno &&
E 15
I 15
		if (ISSET(t, B_DELCRSR) && t->bt_bcursor.pgno == h->pgno &&
E 15
		    t->bt_bcursor.index == index) {
D 8
			UNSET(t, BTF_DELCRSR);
E 8
I 8
D 15
			CLR(t, BTF_DELCRSR);
E 15
I 15
			CLR(t, B_DELCRSR);
E 15
E 8
			goto delete;
		}
D 10
		BT_CLR(t);
E 10
		mpool_put(t->bt_mp, h, 0);
		return (RET_SPECIAL);
	default:
D 8
		if (!exact || NOTSET(t, BTF_NODUPS))
E 8
I 8
D 15
		if (!exact || !ISSET(t, BTF_NODUPS))
E 15
I 15
		if (!exact || !ISSET(t, B_NODUPS))
E 15
E 8
			break;
delete:		if (__bt_dleaf(t, h, index) == RET_ERROR) {
D 10
			BT_CLR(t);
E 10
			mpool_put(t->bt_mp, h, 0);
E 4
			return (RET_ERROR);
D 4
	} else {
		free_key = FALSE;
		key = &(id->i_bytes[0]);
E 4
I 4
		}
		break;
E 4
	}
D 4
	i = _bt_binsrch(t, key);
E 4

D 4
	next = NEXTINDEX(h);
	while (i < next && _bt_cmp(t, key, i) >= 0)
		i++;
E 4
I 4
	/*
	 * If not enough room, or the user has put a ceiling on the number of
	 * keys permitted in the page, split the page.  The split code will
	 * insert the key and data and unpin the current page.  If inserting
	 * into the offset array, shift the pointers up.
	 */
	nbytes = NBLEAFDBT(key->size, data->size);
D 5
	if (h->upper - h->lower < nbytes + sizeof(index_t) ||
	    t->bt_maxkeypage && t->bt_maxkeypage < NEXTINDEX(h))
		return (__bt_split(t, h, key, data, dflags, nbytes, index));
E 5
I 5
D 13
	if (h->upper - h->lower < nbytes + sizeof(index_t)) {
E 13
I 13
	if (h->upper - h->lower < nbytes + sizeof(indx_t)) {
E 13
D 8
		status = __bt_split(t, h, key, data, dflags, nbytes, index);
		if (status == RET_SUCCESS)
			SET(t, BTF_MODIFIED);
		return (status);
E 8
I 8
		if ((status = __bt_split(t, h, key,
		    data, dflags, nbytes, index)) != RET_SUCCESS)
			return (status);
		goto success;
E 8
	}
E 5
E 4

D 4
	if (free_key)
		(void) free(key);
E 4
I 4
	if (index < (nxtindex = NEXTINDEX(h)))
D 14
		bcopy(h->linp + index, h->linp + index + 1,
E 14
I 14
		memmove(h->linp + index + 1, h->linp + index,
E 14
D 13
		    (nxtindex - index) * sizeof(index_t));
	h->lower += sizeof(index_t);
E 13
I 13
		    (nxtindex - index) * sizeof(indx_t));
	h->lower += sizeof(indx_t);
E 13
E 4

D 4
	/* okay, now we're close; find adjacent IDATUM */
	for (;;) {
		idx = (IDATUM *) GETDATUM(h,i);
		if (idx->i_pgno == pgno) {
			i++;
			break;
E 4
I 4
	h->linp[index] = h->upper -= nbytes;
	dest = (char *)h + h->upper;
	WR_BLEAF(dest, key, data, dflags);

	if (t->bt_order == NOT)
		if (h->nextpg == P_INVALID) {
			if (index == NEXTINDEX(h) - 1) {
				t->bt_order = FORWARD;
				t->bt_last.index = index;
				t->bt_last.pgno = h->pgno;
			}
		} else if (h->prevpg == P_INVALID) {
			if (index == 0) {
				t->bt_order = BACK;
				t->bt_last.index = 0;
				t->bt_last.pgno = h->pgno;
			}
E 4
		}
D 4
		--i;
	}
E 4

D 4
	/* correctly positioned, do the insertion */
	return (_bt_insertat(t, (char *) id, i));
E 4
I 4
D 5
	BT_CLR(t);
E 5
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);
I 5
D 10
	BT_CLR(t);
E 10
I 8

success:
	if (flags == R_SETCURSOR) {
		t->bt_bcursor.pgno = e->page->pgno;
		t->bt_bcursor.index = e->index;
	}
E 8
E 5
D 15
	SET(t, BTF_MODIFIED);
E 15
I 15
	SET(t, B_MODIFIED);
E 15
	return (RET_SUCCESS);
E 4
}

I 4
#ifdef STATISTICS
u_long bt_cache_hit, bt_cache_miss;
#endif

E 4
/*
D 4
 *  _BT_INSERTAT -- Insert a datum at a given location on the current page.
E 4
I 4
 * BT_FAST -- Do a quick check for sorted data.
E 4
 *
D 4
 *	This routine does insertions on both leaf and internal pages.
E 4
I 4
 * Parameters:
 *	t:	tree
 *	key:	key to insert
E 4
 *
D 4
 *	Parameters:
 *		t -- tree in which to do insertion.
 *		p -- DATUM or IDATUM to insert.
 *		index -- index in line pointer array to put this item.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Will rearrange line pointers to make space for the new
 *		entry.  This means that any scans currently active are
 *		invalid after this.
 *
 *	Warnings:
 *		There must be sufficient room for the new item on the page.
E 4
I 4
 * Returns:
 * 	EPG for new record or NULL if not found.
E 4
 */
D 4

int
_bt_insertat(t, p, index)
	BTREE_P t;
	char *p;
	index_t index;
E 4
I 4
static EPG *
bt_fast(t, key, data, exactp)
	BTREE *t;
	const DBT *key, *data;
	int *exactp;
E 4
{
D 4
	IDATUM *id = (IDATUM *) p;
	DATUM *d = (DATUM *) p;
	BTHEADER *h;
	CURSOR *c;
	index_t nxtindex;
	char *src, *dest;
	int nbytes;
E 4
I 4
D 18
	EPG e;
E 18
	PAGE *h;
	size_t nbytes;
	int cmp;
E 4

D 4
	/* insertion may confuse an active scan.  fix it. */
	c = &(t->bt_cursor);
	if (t->bt_flags & BTF_SEQINIT && t->bt_curpage->h_pgno == c->c_pgno)
		if (_bt_fixscan(t, index, d, INSERT) == RET_ERROR)
			return (RET_ERROR);
E 4
I 4
	if ((h = mpool_get(t->bt_mp, t->bt_last.pgno, 0)) == NULL) {
		t->bt_order = NOT;
		return (NULL);
	}
D 18
	e.page = h;
	e.index = t->bt_last.index;
E 18
I 18
	t->bt_cur.page = h;
	t->bt_cur.index = t->bt_last.index;
E 18
E 4

D 4
	h = t->bt_curpage;
	nxtindex = (index_t) NEXTINDEX(h);

E 4
	/*
D 4
	 *  If we're inserting at the middle of the line pointer array,
	 *  copy pointers that will follow the new one up on the page.
E 4
I 4
	 * If won't fit in this page or have too many keys in this page, have
	 * to search to get split stack.
E 4
	 */
I 4
D 5
	nbytes =
	    NBLEAFDBT(key->size >= t->bt_minkeypage ? NOVFLSIZE : key->size,
	    data->size >= t->bt_minkeypage ? NOVFLSIZE : data->size);
	if (h->upper - h->lower < nbytes + sizeof(index_t) ||
	    t->bt_maxkeypage && t->bt_maxkeypage < NEXTINDEX(h))
E 5
I 5
	nbytes = NBLEAFDBT(key->size, data->size);
D 13
	if (h->upper - h->lower < nbytes + sizeof(index_t))
E 13
I 13
	if (h->upper - h->lower < nbytes + sizeof(indx_t))
E 13
E 5
		goto miss;
E 4

D 4
	if (index < nxtindex) {
		src = (char *) &(h->h_linp[index]);
		dest = (char *) &(h->h_linp[index + 1]);
		nbytes = (h->h_lower - (src - ((char *) h)))
			 + sizeof(h->h_linp[0]);
		(void) bcopy(src, dest, nbytes);
	}

	/* compute size and copy data to page */
	if (h->h_flags & F_LEAF) {
		nbytes = d->d_ksize + d->d_dsize
			 + (sizeof(DATUM) - sizeof(char));
E 4
I 4
	if (t->bt_order == FORWARD) {
D 18
		if (e.page->nextpg != P_INVALID)
E 18
I 18
		if (t->bt_cur.page->nextpg != P_INVALID)
E 18
			goto miss;
D 18
		if (e.index != NEXTINDEX(h) - 1)
E 18
I 18
		if (t->bt_cur.index != NEXTINDEX(h) - 1)
E 18
			goto miss;
D 18
		if ((cmp = __bt_cmp(t, key, &e)) < 0)
E 18
I 18
		if ((cmp = __bt_cmp(t, key, &t->bt_cur)) < 0)
E 18
			goto miss;
D 6
		t->bt_last.index = ++e.index;
E 6
I 6
D 18
		t->bt_last.index = cmp ? ++e.index : e.index;
E 18
I 18
		t->bt_last.index = cmp ? ++t->bt_cur.index : t->bt_cur.index;
E 18
E 6
E 4
	} else {
D 4
		nbytes = id->i_size + (sizeof(IDATUM) - sizeof(char));
E 4
I 4
D 18
		if (e.page->prevpg != P_INVALID)
E 18
I 18
		if (t->bt_cur.page->prevpg != P_INVALID)
E 18
			goto miss;
D 18
		if (e.index != 0)
E 18
I 18
		if (t->bt_cur.index != 0)
E 18
			goto miss;
D 18
		if ((cmp = __bt_cmp(t, key, &e)) > 0)
E 18
I 18
		if ((cmp = __bt_cmp(t, key, &t->bt_cur)) > 0)
E 18
			goto miss;
		t->bt_last.index = 0;
E 4
	}
D 4
	dest = (((char *) h) + h->h_upper) - LONGALIGN(nbytes);
	(void) bcopy((char *) p, dest, nbytes);
E 4
I 4
	*exactp = cmp == 0;
#ifdef STATISTICS
	++bt_cache_hit;
#endif
D 18
	return (&e);
E 18
I 18
	return (&t->bt_cur);
E 18
E 4

D 4
	/* update statistics */
	dest -= (int) h;
	h->h_linp[index] = (index_t) dest;
	h->h_upper = (index_t) dest;
	h->h_lower += sizeof(index_t);

	/* we're done */
	h->h_flags |= F_DIRTY;

	return (RET_SUCCESS);
E 4
I 4
D 5
miss:	
E 5
I 5
miss:
E 5
#ifdef STATISTICS
	++bt_cache_miss;
#endif
	t->bt_order = NOT;
	mpool_put(t->bt_mp, h, 0);
	return (NULL);
E 4
}
E 1
