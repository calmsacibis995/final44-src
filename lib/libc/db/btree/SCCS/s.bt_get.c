h54754
s 00018/00002/00194
d D 8.2 93/09/07 11:49:28 bostic 11 10
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00194
d D 8.1 93/06/04 15:20:22 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00194
d D 5.9 93/05/16 15:42:04 bostic 9 8
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00001/00001/00195
d D 5.8 93/02/14 17:39:19 bostic 8 7
c index -> indx_t
e
s 00001/00001/00195
d D 5.7 93/02/11 11:39:21 bostic 7 6
c move db.h to the end of the includes, make compat.h work better
e
s 00013/00014/00183
d D 5.6 92/12/04 17:44:51 bostic 6 5
c initialize the e->page element, not just the e->index element when
c crossing to a new page; from Rodney
e
s 00007/00003/00190
d D 5.5 92/11/13 16:03:45 bostic 5 4
c litn
e
s 00010/00010/00183
d D 5.4 91/09/12 11:12:59 bostic 4 3
c don't modify the key in get function; change __bt_first to return
c first key greater than or equal to the key.
e
s 00140/00585/00053
d D 5.3 91/09/04 12:47:08 bostic 3 2
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00004/00003/00634
d D 5.2 91/02/22 17:16:43 bostic 2 1
c ANSI prototypes
e
s 00637/00000/00000
d D 5.1 91/01/23 08:12:48 mao 1 0
c date and time created 91/01/23 08:12:48 by mao
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

D 3
#include <sys/param.h>
D 2
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/file.h>
E 2
#include <db.h>
E 3
I 3
#include <sys/types.h>
E 3
I 2
D 5
#include <errno.h>
E 5
I 5

E 5
D 3
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
E 3
I 3
D 7
#include <db.h>
E 7
D 5
#include <stdio.h>
E 5
I 5
#include <errno.h>
E 5
#include <stddef.h>
I 5
#include <stdio.h>

I 7
#include <db.h>
E 7
E 5
E 3
E 2
#include "btree.h"

/*
D 3
 *  BT_GETPAGE -- Make pgno the current page of the btree.
E 3
I 3
 * __BT_GET -- Get a record from the btree.
E 3
 *
D 3
 *	This routine is just a wrapper that decides whether to call the
 *	memory or disk-based routine to do the work.
E 3
I 3
 * Parameters:
 *	dbp:	pointer to access method
 *	key:	key to find
 *	data:	data to return
 *	flag:	currently unused
E 3
 *
D 3
 *	Parameters:
 *		t -- btree in which to get page
 *		pgno -- page number to get
 *
 *	Returns:
 *		RET_SUCCESS or RET_ERROR.
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
_bt_getpage(t, pgno)
	BTREE_P t;
	pgno_t pgno;
E 3
I 3
__bt_get(dbp, key, data, flags)
	const DB *dbp;
D 4
	DBT *key, *data;
E 4
I 4
	const DBT *key;
	DBT *data;
E 4
	u_int flags;
E 3
{
D 3
#ifdef DEBUG
	if (pgno == P_NONE)
		_punt();
#endif /* DEBUG */
E 3
I 3
	BTREE *t;
	EPG *e;
	int exact, status;
E 3

I 11
	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	/* Get currently doesn't take any flags. */
E 11
D 3
	/* see if we can get away without doing any work */
	if (t->bt_curpage != (BTHEADER *) NULL) {
		if (t->bt_curpage->h_pgno == pgno)
			return (RET_SUCCESS);
E 3
I 3
	if (flags) {
		errno = EINVAL;
		return (RET_ERROR);
E 3
	}
I 3
D 11
	t = dbp->internal;
E 11
I 11

E 11
	if ((e = __bt_search(t, key, &exact)) == NULL)
		return (RET_ERROR);
	if (!exact) {
		mpool_put(t->bt_mp, e->page, 0);
		return (RET_SPECIAL);
	}
E 3

D 3
	if (t->bt_fname == (char *) NULL)
		return (_bt_getmpage(t, pgno));
	else
		return (_bt_getdpage(t, pgno));
}

/*
 *  _BT_GETMPAGE -- Make pgno the current page of the btree.
 *
 *	This routine gets pages for in-memory btrees.
 *
 *	Parameters:
 *		t -- btree in which to get page
 *		pgno -- page number to get
 *
 *	Returns:
 *		RET_SUCCESS or RET_ERROR.
 */

int
_bt_getmpage(t, pgno)
	register BTREE_P t;
	pgno_t pgno;
{
	int htindex;
	BTHEADER *h;
	HTBUCKET *b;

	if (t->bt_curpage == (BTHEADER *) NULL) {
		if (pgno != P_ROOT) {
			errno = EBADF;
E 3
I 3
	/*
	 * A special case is if we found the record but it's flagged for
	 * deletion.  In this case, we want to find another record with the
	 * same key, if it exists.  Rather than look around the tree we call
D 4
	 * __bt_first and have it redo the search as __bt_first will not
E 4
I 4
	 * __bt_first and have it redo the search, as __bt_first will not
E 4
	 * return keys marked for deletion.  Slow, but should never happen.
	 */
D 9
	if (ISSET(t, BTF_DELCRSR) && e->page->pgno == t->bt_bcursor.pgno &&
E 9
I 9
	if (ISSET(t, B_DELCRSR) && e->page->pgno == t->bt_bcursor.pgno &&
E 9
	    e->index == t->bt_bcursor.index) {
		mpool_put(t->bt_mp, e->page, 0);
		if ((e = __bt_first(t, key, &exact)) == NULL)
E 3
			return (RET_ERROR);
D 3
		}

		t->bt_npages++;
		h = (BTHEADER *) malloc((unsigned) t->bt_psize);
		if (h == (BTHEADER *) NULL)
			return (RET_ERROR);

		h->h_pgno = P_ROOT;
		h->h_flags = F_LEAF;
		h->h_lower = (index_t)
				(((char *) &(h->h_linp[0])) - ((char *) h));
		h->h_upper = t->bt_psize;
		h->h_prevpg = h->h_nextpg = P_NONE;

		t->bt_curpage = h;

		/* get the root page into the hash table */
		if (_bt_write(t, h, RELEASE) == RET_ERROR)
			return (RET_ERROR);
E 3
I 3
		if (!exact)
			return (RET_SPECIAL);
E 3
	}

D 3
	htindex = HASHKEY(pgno);

	for (b = t->bt_s.bt_ht[htindex];
	     b != (HTBUCKET *) NULL;
	     b = b->ht_next) {
		if (b->ht_pgno == pgno) {
			t->bt_curpage = b->ht_page;
			return (RET_SUCCESS);
		}
	}
	return (RET_ERROR);
E 3
I 3
D 4
	status = __bt_ret(t, e, data, key);
E 4
I 4
	status = __bt_ret(t, e, NULL, data);
E 4
D 11
	mpool_put(t->bt_mp, e->page, 0);
E 11
I 11
	/*
	 * If the user is doing concurrent access, we copied the
	 * key/data, toss the page.
	 */
	if (ISSET(t, B_DB_LOCK))
		mpool_put(t->bt_mp, e->page, 0);
	else
		t->bt_pinned = e->page;
E 11
	return (status);
E 3
}

/*
D 3
 *  _BT_GETDPAGE -- Make pgno the current page of the btree.
E 3
I 3
D 4
 * __BT_FIRST -- Find the first record in the tree matching the key.
E 4
I 4
 * __BT_FIRST -- Find the first entry.
E 4
E 3
 *
D 3
 *	This routine gets pages for disk btrees.
E 3
I 3
 * Parameters:
 *	t:	the tree
 *	key:	the key
E 3
 *
D 3
 *	Because disk btree pages must be readable across machine architectures,
 *	the btree code writes integers out in network format.  This routine
 *	converts them back to host format before returning the page.
 *
 *	Parameters:
 *		t -- btree in which to get page
 *		pgno -- page number to get
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
E 3
I 3
 * Returns:
D 4
 *	The first matching record.
E 4
I 4
 *	The first entry in the tree greater than or equal to key.
E 4
E 3
 */
D 3

int
_bt_getdpage(t, pgno)
	register BTREE_P t;
	pgno_t pgno;
E 3
I 3
EPG *
__bt_first(t, key, exactp)
	BTREE *t;
D 4
	DBT *key;
E 4
I 4
	const DBT *key;
E 4
	int *exactp;
E 3
{
D 3
	BTHEADER *h;
	char *cache;
	long pos;
	int n, nbytes;
E 3
I 3
	register PAGE *h;
	register EPG *e;
	EPG save;
	pgno_t cpgno, pg;
D 8
	index_t cindex;
E 8
I 8
	indx_t cindex;
E 8
	int found;
E 3

D 3
	/* if we have an lru cache, let the cache code do the work */
	if (ISCACHE(t)) {
		cache = t->bt_s.bt_d.d_cache;

		/* release the old page */
		if (t->bt_curpage != (BTHEADER *) NULL) {
			pgno_t opgno = t->bt_curpage->h_pgno;
			t->bt_curpage->h_flags &= ~F_DIRTY;

			if (lruwrite(cache, (int) opgno) < 0)
				return (RET_ERROR);

			if (lrurelease(cache, (int) opgno) < 0)
				return (RET_ERROR);
		}

		if (pgno > t->bt_npages) {
			if ((h = (BTHEADER *) lrugetnew(cache, (int)pgno, &nbytes))
			    == (BTHEADER *) NULL)
				return (RET_ERROR);
			t->bt_npages = pgno;
		} else {
			if ((h = (BTHEADER *) lruget(cache, (int)pgno, &nbytes))
			    == (BTHEADER *) NULL)
				return (RET_ERROR);
		}

		/* init this page, if necessary */
		if (nbytes == 0) {
			h->h_pgno = pgno;
			h->h_flags = F_LEAF;
			h->h_lower = (index_t)
				(((char *) &(h->h_linp[0])) - ((char *) h));
			h->h_upper = t->bt_psize;
			h->h_prevpg = h->h_nextpg = P_NONE;
		}

		t->bt_curpage = h;

		return (RET_SUCCESS);
E 3
I 3
	/*
	 * Find any matching record; __bt_search pins the page.  Only exact
D 4
	 * matches are interesting.
E 4
I 4
	 * matches are tricky, otherwise just return the location of the key
	 * if it were to be inserted into the tree.
E 4
	 */
	if ((e = __bt_search(t, key, exactp)) == NULL)
		return (NULL);
D 4
	if (!*exactp) {
		mpool_put(t->bt_mp, e->page, 0);
E 4
I 4
	if (!*exactp)
E 4
		return (e);
E 3
D 4
	}
E 4

D 3
	/* sync the current page, if necessary */
	if (t->bt_curpage != (BTHEADER *) NULL) {
		if (t->bt_curpage->h_flags & F_DIRTY)
			if (_bt_write(t, t->bt_curpage, RELEASE) == RET_ERROR)
				return (RET_ERROR);
	} else {
		if (t->bt_npages == 0)
			t->bt_npages = 1;
E 3
I 3
D 9
	if (ISSET(t, BTF_DELCRSR)) {
E 9
I 9
	if (ISSET(t, B_DELCRSR)) {
E 9
		cpgno = t->bt_bcursor.pgno;
		cindex = t->bt_bcursor.index;
D 5
	} else
E 5
I 5
	} else {
E 5
		cpgno = P_INVALID;
I 5
		cindex = 0;		/* GCC thinks it's uninitialized. */
	}
E 5
E 3

D 3
		/* if no current page, get space for one */
		if ((t->bt_curpage = (BTHEADER *) malloc((unsigned) t->bt_psize))
		    == (BTHEADER *) NULL) {
			return (RET_ERROR);
E 3
I 3
	/*
	 * Walk backwards, skipping empty pages, as long as the entry matches
	 * and there are keys left in the tree.  Save a copy of each match in
	 * case we go too far.  A special case is that we don't return a match
	 * on records that the cursor references that have already been flagged
	 * for deletion.
	 */
	save = *e;
	h = e->page;
	found = 0;
	do {
		if (cpgno != h->pgno || cindex != e->index) {
			if (save.page->pgno != e->page->pgno) {
				mpool_put(t->bt_mp, save.page, 0);
				save = *e;
			} else
				save.index = e->index;
			found = 1;
E 3
		}
D 3
	}

	n = t->bt_psize;
	pos = (long) (pgno * n);

	/* seek to correct location in file */
	if (lseek(t->bt_s.bt_d.d_fd, pos, L_SET) != pos) {
		return (RET_ERROR);
	}

	/* read the page */
	if ((nbytes = read(t->bt_s.bt_d.d_fd, t->bt_curpage, n)) < n) {

E 3
		/*
D 3
		 *  If we didn't get a full page, we must have gotten no
		 *  data at all -- in which case we're trying to read a
		 *  root page that doesn't exist yet.  This is the only
		 *  case in which this is okay.  If this happens, construct
		 *  an empty root page by hand.
E 3
I 3
		 * Make a special effort not to unpin the page the last (or
		 * original) match was on, but also make sure it's unpinned
		 * if an error occurs.
E 3
		 */
D 3
		if (nbytes != 0 || pgno != P_ROOT) {
			errno = EBADF;
			return (RET_ERROR);
		}

		h = (BTHEADER *) t->bt_curpage;
		h->h_pgno = pgno;
		h->h_flags = F_LEAF;
		h->h_lower = (index_t)
				(((char *) &(h->h_linp[0])) - ((char *) h));
		h->h_upper = t->bt_psize;
		h->h_prevpg = h->h_nextpg = P_NONE;
	} else
		(void) _bt_pgin(t->bt_curpage, (char *) t->bt_lorder);

	return (RET_SUCCESS);
}

/*
 *  _BT_PGOUT, _BT_PGIN -- Convert host-specific number layout to/from
 *			   the host-independent format stored on disk.
 *
 *	Parameters:
 *		h -- page to convert
 *		_lorder -- byte order for pages (stored as a char * in the
 *			   cache, and passed around as a magic cookie).
 *
 *	Returns:
 *		RET_SUCCESS (lru code requires a return value).
 *
 *	Side Effects:
 *		Layout of tree metadata on the page is changed in place.
 *
 *	Warnings:
 *		Everywhere else in the code, the types pgno_t and index_t
 *		are opaque.  These two routines know what they really
 *		are.
 */

int
_bt_pgout(h, _lorder)
	BTHEADER *h;
	char *_lorder;
{
	int i;
	int top;
	int lorder;
	DATUM *d;
	IDATUM *id;
	size_t chain;

	lorder = (int) _lorder;
	if (lorder == BYTE_ORDER)
		return (RET_SUCCESS);

	if (h->h_flags & F_LEAF) {
		if (h->h_flags & F_CONT) {
			if (h->h_prevpg == P_NONE) {
				size_t longsz;

				(void) bcopy((char *) &(h->h_linp[0]),
					      (char *) &longsz,
					      sizeof(longsz));
				BLSWAP(longsz);
				(void) bcopy((char *) &longsz,
					      (char *) &(h->h_linp[0]),
					      sizeof(longsz));
			}
		} else {
			top = NEXTINDEX(h);
			for (i = 0; i < top; i++) {
				d = (DATUM *) GETDATUM(h, i);
				if (d->d_flags & D_BIGKEY) {
					(void) bcopy((char *) &(d->d_bytes[0]),
						      (char *) &chain,
						      sizeof(chain));
					BLSWAP(chain);
					(void) bcopy((char *) &chain,
						      (char *) &(d->d_bytes[0]),
						      sizeof(chain));
E 3
I 3
D 6
		if (e->index == 0)
			do {
				if (h->prevpg == P_INVALID)
					goto done1;
				if (h->pgno != save.page->pgno)
					mpool_put(t->bt_mp, h, 0);
				if ((h = mpool_get(t->bt_mp,
				    h->prevpg, 0)) == NULL) {
					if (h->pgno == save.page->pgno)
						mpool_put(t->bt_mp,
						    save.page, 0);
					return (NULL);
E 3
				}
D 3
				if (d->d_flags & D_BIGDATA) {
					(void) bcopy((char *) &(d->d_bytes[d->d_ksize]),
						      (char *) &chain,
						      sizeof(chain));
					BLSWAP(chain);
					(void) bcopy((char *) &chain,
						      (char *) &(d->d_bytes[d->d_ksize]),
						      sizeof(chain));
				}
				BLSWAP(d->d_dsize);
				BLSWAP(d->d_ksize);
				BLSWAP(d->d_flags);
				BLSWAP(h->h_linp[i]);
			}
		}
	} else {
		top = NEXTINDEX(h);
		for (i = 0; i < top; i++) {
			id = (IDATUM *) GETDATUM(h, i);
			BLSWAP(id->i_size);
			BLSWAP(id->i_pgno);
			BLSWAP(id->i_flags);
			if (id->i_flags & D_BIGKEY) {
				(void) bcopy((char *) &(id->i_bytes[0]),
					      (char *) &chain,
					      sizeof(chain));
				BLSWAP(chain);
				(void) bcopy((char *) &chain,
					      (char *) &(id->i_bytes[0]),
					      sizeof(chain));
			}
			BLSWAP(h->h_linp[i]);
		}
	}
	BLSWAP(h->h_flags);
	BLSWAP(h->h_pgno);
	BLSWAP(h->h_prevpg);
	BLSWAP(h->h_nextpg);
	BLSWAP(h->h_lower);
	BLSWAP(h->h_upper);
E 3
I 3
			} while ((e->index = NEXTINDEX(h)) == 0);
E 6
I 6
		while (e->index == 0) {
			if (h->prevpg == P_INVALID)
				goto done1;
			if (h->pgno != save.page->pgno)
				mpool_put(t->bt_mp, h, 0);
			if ((h = mpool_get(t->bt_mp, h->prevpg, 0)) == NULL) {
				if (h->pgno == save.page->pgno)
					mpool_put(t->bt_mp, save.page, 0);
				return (NULL);
			}
			e->page = h;
			e->index = NEXTINDEX(h);
		}
E 6
		--e->index;
	} while (__bt_cmp(t, key, e) == 0);
E 3

D 3
	return (RET_SUCCESS);
}

int
_bt_pgin(h, _lorder)
	BTHEADER *h;
	char *_lorder;
{
	int i;
	int top;
	int lorder;
	DATUM *d;
	IDATUM *id;
	size_t chain;

E 3
	/*
D 3
	 *  If btree pages are to be stored in the host byte order, don't
	 *  bother swapping.
E 3
I 3
	 * Reach here with the last page that was looked at pinned, which may
	 * or may not be the same as the last (or original) match page.  If
	 * it's not useful, release it.
E 3
	 */
D 3
	lorder = (int) _lorder;
	if (lorder == BYTE_ORDER)
		return (RET_SUCCESS);
E 3
I 3
done1:	if (h->pgno != save.page->pgno)
		mpool_put(t->bt_mp, h, 0);
E 3

D 3
	BLSWAP(h->h_upper);
	BLSWAP(h->h_lower);
	BLSWAP(h->h_nextpg);
	BLSWAP(h->h_prevpg);
	BLSWAP(h->h_pgno);
	BLSWAP(h->h_flags);

	if (h->h_flags & F_LEAF) {
		if (h->h_flags & F_CONT) {
			if (h->h_prevpg == P_NONE) {
				size_t longsz;

				(void) bcopy((char *) &(h->h_linp[0]),
					      (char *) &longsz,
					      sizeof(longsz));
				BLSWAP(longsz);
				(void) bcopy((char *) &longsz,
					      (char *) &(h->h_linp[0]),
					      sizeof(longsz));
			}
		} else {
			top = NEXTINDEX(h);
			for (i = 0; i < top; i++) {
				BLSWAP(h->h_linp[i]);
				d = (DATUM *) GETDATUM(h, i);
				BLSWAP(d->d_dsize);
				BLSWAP(d->d_ksize);
				BLSWAP(d->d_flags);
				if (d->d_flags & D_BIGKEY) {
					(void) bcopy((char *) &(d->d_bytes[0]),
						      (char *) &chain,
						      sizeof(chain));
					BLSWAP(chain);
					(void) bcopy((char *) &chain,
						      (char *) &(d->d_bytes[0]),
						      sizeof(chain));
E 3
I 3
	/*
	 * If still haven't found a record, the only possibility left is the
	 * next one.  Move forward one slot, skipping empty pages and check.
	 */
	if (!found) {
		h = save.page;
		if (++save.index == NEXTINDEX(h)) {
			do {
				pg = h->nextpg;
				mpool_put(t->bt_mp, h, 0);
				if (pg == P_INVALID) {
					*exactp = 0;
					return (e);
E 3
				}
D 3
				if (d->d_flags & D_BIGDATA) {
					(void) bcopy((char *) &(d->d_bytes[d->d_ksize]),
						      (char *) &chain,
						      sizeof(chain));
					BLSWAP(chain);
					(void) bcopy((char *) &chain,
						      (char *) &(d->d_bytes[d->d_ksize]),
						      sizeof(chain));
				}
			}
E 3
I 3
				if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
					return (NULL);
			} while ((save.index = NEXTINDEX(h)) == 0);
			save.page = h;
E 3
		}
D 3
	} else {
		top = NEXTINDEX(h);
		for (i = 0; i < top; i++) {
			BLSWAP(h->h_linp[i]);
			id = (IDATUM *) GETDATUM(h, i);
			BLSWAP(id->i_size);
			BLSWAP(id->i_pgno);
			BLSWAP(id->i_flags);
			if (id->i_flags & D_BIGKEY) {
				(void) bcopy((char *) &(id->i_bytes[0]),
					      (char *) &chain,
					      sizeof(chain));
				BLSWAP(chain);
				(void) bcopy((char *) &chain,
					      (char *) &(id->i_bytes[0]),
					      sizeof(chain));
			}
E 3
I 3
		if (__bt_cmp(t, key, &save) != 0) {
			*exactp = 0;
			return (e);
E 3
		}
	}
D 3
	return (RET_SUCCESS);
}

/*
 *  _BT_ALLOCPG -- allocate a new page in the btree.
 *
 *	This is called when we split a page, to get space to do the split.
 *	For disk btrees, these pages are released when the split is done.
 *	For memory btrees, they are not.
 *
 *	Parameters:
 *		t -- tree in which to do split
 *
 *	Returns:
 *		Pointer to the newly-allocated page
 */

BTHEADER *
_bt_allocpg(t)
	BTREE_P t;
{
	BTHEADER *h = t->bt_curpage;
	BTHEADER *nh;
	int nbytes;

	/* if we have a cache, let the cache code do the work */
	if (ISDISK(t) && ISCACHE(t)) {
		nh = (BTHEADER *) lrugetnew(t->bt_s.bt_d.d_cache,
					    (int) (t->bt_npages + 1),
					    &nbytes);
	} else {
		nh = (BTHEADER *) malloc((unsigned) t->bt_psize);
	}

	if (nh != (BTHEADER *) NULL) {
		nh->h_pgno = nh->h_prevpg = nh->h_nextpg = P_NONE;
		nh->h_flags = h->h_flags;
		nh->h_lower = (index_t)
				(((char *) &(nh->h_linp[0])) - ((char *) nh));
		nh->h_upper = t->bt_psize;
	}

	return (nh);
}

/*
 *  _BT_WRITE -- Write a specific page to a btree file.
 *
 *	Parameters:
 *		t -- btree to get the page
 *		h -- page to write
 *		relflag -- (int) this page may/may not be released
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Writes a metadata page if none has been written yet.
 */

int
_bt_write(t, h, relflag)
	BTREE_P t;
	BTHEADER *h;
	int relflag;
{
	long pos;
	int htindex;
	HTBUCKET *b;
	char *cache;
	pgno_t pgno;

	h->h_flags &= ~F_DIRTY;
	if (ISDISK(t)) {

		/* if we haven't done so yet, write the metadata */
		if (!(t->bt_flags & BTF_METAOK)) {
			if (_bt_wrtmeta(t) == RET_ERROR)
				return (RET_ERROR);
		}

		pgno = h->h_pgno;


		/* if we have a cache, let the cache code do the work */
		if ((cache = t->bt_s.bt_d.d_cache) != (char *) NULL) {
			if (lruwrite(cache, (int) pgno) < 0)
				return (RET_ERROR);
			if (relflag && lrurelease(cache, (int) pgno) < 0)
				return (RET_ERROR);
				
		} else {
			(void) _bt_pgout(h, (char *) t->bt_lorder);
			/* now write the current page */
			pos = (long) (pgno * t->bt_psize);
			if (lseek(t->bt_s.bt_d.d_fd, pos, L_SET) != pos)
				return (RET_ERROR);
			if (write(t->bt_s.bt_d.d_fd, (char *) h, (int) t->bt_psize)
			    < t->bt_psize)
				return (RET_ERROR);
			if (!relflag)
				(void) _bt_pgin(h, (char *) t->bt_lorder);
		}
	} else {
		/* in-memory btree */
		htindex = HASHKEY(h->h_pgno);

		/* see if we need to overwrite existing entry */
		for (b = t->bt_s.bt_ht[htindex];
		     b != (HTBUCKET *) NULL;
		     b = b->ht_next) {
			if (b->ht_pgno == h->h_pgno) {
				b->ht_page = h;
				return (RET_SUCCESS);
			}
		}

		/* new entry, write it */
		b = (HTBUCKET *) malloc((unsigned) sizeof (HTBUCKET));
		if (b == (HTBUCKET *) NULL)
			return (RET_ERROR);

		b->ht_pgno = h->h_pgno;
		b->ht_page = h;
		b->ht_next = t->bt_s.bt_ht[htindex];
		t->bt_s.bt_ht[htindex] = b;
	}
	return (RET_SUCCESS);
}

/*
 *  _BT_RELEASE -- Release a locked-down cache page
 *
 *	During page splits, we want to force pages out to the cache
 *	before we actually release them, in some cases.  This routine
 *	releases such a page when it is no longer needed.
 *
 *	Parameters:
 *		t -- btree in which to release page
 *		h -- page to release
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		None.
 */

int
_bt_release(t, h)
	BTREE_P t;
	BTHEADER *h;
{
	if (ISDISK(t) && ISCACHE(t)) {
		if (lrurelease(t->bt_s.bt_d.d_cache, (int) (h->h_pgno)) < 0)
			return (RET_ERROR);
	}
	return (RET_SUCCESS);
}

/*
 *  _BT_WRTMETA -- Write metadata to the btree.
 *
 *	Parameters:
 *		t -- tree to which to write
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 */

int
_bt_wrtmeta(t)
	BTREE_P t;
{
	BTMETA m;

	if (lseek(t->bt_s.bt_d.d_fd, 0l, L_SET) != 0l)
		return (RET_ERROR);

	/* lorder has to be in host-independent format */
	m.m_lorder = (u_long) htonl((long) t->bt_lorder);

	m.m_magic = BTREEMAGIC;
	m.m_version = BTREEVERSION;
	m.m_psize = t->bt_psize;
	m.m_free = t->bt_free;
	m.m_flags = t->bt_flags & BTF_NODUPS;

	if (t->bt_lorder != BYTE_ORDER) {
		BLSWAP(m.m_magic);
		BLSWAP(m.m_version);
		BLSWAP(m.m_psize);
		BLSWAP(m.m_free);
		BLSWAP(m.m_flags);
	}

	if (write(t->bt_s.bt_d.d_fd, (char *) &m, sizeof(m))
	    != sizeof(m)) {
		return (RET_ERROR);
	}

	t->bt_flags |= BTF_METAOK;

	return (RET_SUCCESS);
E 3
I 3
	*e = save;
	*exactp = 1;
	return (e);
E 3
}
E 1
