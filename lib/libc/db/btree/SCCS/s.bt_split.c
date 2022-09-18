h31428
s 00001/00001/00798
d D 8.4 95/01/09 13:32:45 bostic 21 20
c Fix to split code for single large record at the end of a page.
e
s 00001/00001/00798
d D 8.3 94/02/21 17:43:19 bostic 20 19
c cast alloc's to shut SunOS up
e
s 00008/00009/00791
d D 8.2 94/02/21 15:08:16 bostic 19 18
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00798
d D 8.1 93/06/04 15:20:59 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00029/00012/00771
d D 5.17 93/05/22 14:16:54 bostic 17 16
c recno bug -- if split to a new page on index 0 (a sorted split) was
c changing a random value as the new number of records on the left page
e
s 00004/00004/00779
d D 5.16 93/05/16 15:43:50 bostic 16 15
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00006/00006/00777
d D 5.15 93/02/19 20:17:16 bostic 15 14
c more lint
e
s 00004/00004/00779
d D 5.14 93/02/19 14:31:42 bostic 14 13
c fix some types for the Sun compiler
e
s 00008/00008/00775
d D 5.13 93/02/16 12:33:47 bostic 13 12
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00012/00012/00771
d D 5.12 93/02/14 17:39:24 bostic 12 11
c index -> indx_t
e
s 00001/00001/00782
d D 5.11 93/02/11 11:39:29 bostic 11 10
c move db.h to the end of the includes, make compat.h work better
e
s 00126/00108/00657
d D 5.10 93/01/10 12:38:18 bostic 10 9
c if large key/data pairs, can split and still not have enough room for
c the new key.  Pass the length of the new key into the split routines so the 
c calculation is correct.  Remove prefix compression when BINTERNAL pages are
c being split -- it's not possible (Bayer's paper agrees).  Most of the actual
c split code was reworked, including cursor adjustment.
e
s 00043/00033/00722
d D 5.9 93/01/09 15:41:55 bostic 9 8
c Put new key/data pair into split page before fixing up the root page
c if the root page split.  The old method, of guaranteeing that the split wasn't
c on the leftmost key of the right page doesn't work, there are cases where the
c split HAS to be that key.  Example is three keys, A, B, D, each 1/3 of a page
c and an insert of a key C which is 1/2 of a page.
e
s 00014/00001/00741
d D 5.8 92/11/13 16:06:18 bostic 8 7
c abort() if unrecognized switch value; initialize nksize (thanks GCC!)
e
s 00003/00003/00739
d D 5.7 92/10/09 16:26:11 bostic 7 6
c implement free page reuse
e
s 00007/00006/00735
d D 5.6 92/10/03 14:57:34 bostic 6 5
c once half < nbytes, don't decrement further, can wrap around
e
s 00008/00006/00733
d D 5.5 92/10/03 13:37:44 bostic 5 4
c bytes needed calculation for BLEAF parent page was wrong -- included
c data bytes as well.  This caused a later error, not positive that it's fixed.
c Also, page was being allowed to split on "skipped" offset, which caused root
c split to drop core
e
s 00041/00042/00698
d D 5.4 91/09/12 11:42:28 bostic 4 3
c change bt_nrecs and set BTF_METADIRTY, BTF_MODIFIED elsewhwere; fix bug
c using rchild->flags instead of bl->flags to get bigkey flag; increment parent
c pages in search routines, so just clear stack; fix cursor repositioning code
c in routine doing the physical split
e
s 00624/00549/00116
d D 5.3 91/09/04 12:47:24 bostic 3 2
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00002/00000/00663
d D 5.2 91/02/22 17:16:42 bostic 2 1
c ANSI prototypes
e
s 00663/00000/00000
d D 5.1 91/01/23 08:12:46 mao 1 0
c date and time created 91/01/23 08:12:46 by mao
e
u
U
t
T
I 1
/*-
D 18
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
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
I 8

E 8
I 3
D 19
#define	__DBINTERFACE_PRIVATE
E 19
E 3
D 11
#include <db.h>
E 11
I 3
#include <limits.h>
#include <stdio.h>
E 3
I 2
#include <stdlib.h>
#include <string.h>
I 8

I 11
#include <db.h>
E 11
E 8
E 2
#include "btree.h"

I 9
static int	 bt_broot __P((BTREE *, PAGE *, PAGE *, PAGE *));
D 10
static PAGE	*bt_page __P((BTREE *, PAGE *, PAGE **, PAGE **, int *));
E 10
I 10
static PAGE	*bt_page
D 15
		    __P((BTREE *, PAGE *, PAGE **, PAGE **, int *, size_t));
E 15
I 15
D 19
		    __P((BTREE *, PAGE *, PAGE **, PAGE **, u_int *, size_t));
E 19
I 19
		    __P((BTREE *, PAGE *, PAGE **, PAGE **, indx_t *, size_t));
E 19
E 15
E 10
E 9
I 3
static int	 bt_preserve __P((BTREE *, pgno_t));
D 10
static PAGE	*bt_psplit __P((BTREE *, PAGE *, PAGE *, PAGE *, int *));
D 9
static PAGE	*bt_page __P((BTREE *, PAGE *, PAGE **, PAGE **, int *));
E 9
static PAGE	*bt_root __P((BTREE *, PAGE *, PAGE **, PAGE **, int *));
E 10
I 10
static PAGE	*bt_psplit
D 15
		    __P((BTREE *, PAGE *, PAGE *, PAGE *, int *, size_t));
E 15
I 15
D 19
		    __P((BTREE *, PAGE *, PAGE *, PAGE *, u_int *, size_t));
E 19
I 19
		    __P((BTREE *, PAGE *, PAGE *, PAGE *, indx_t *, size_t));
E 19
E 15
static PAGE	*bt_root
D 15
		    __P((BTREE *, PAGE *, PAGE **, PAGE **, int *, size_t));
E 15
I 15
D 19
		    __P((BTREE *, PAGE *, PAGE **, PAGE **, u_int *, size_t));
E 19
I 19
		    __P((BTREE *, PAGE *, PAGE **, PAGE **, indx_t *, size_t));
E 19
E 15
E 10
static int	 bt_rroot __P((BTREE *, PAGE *, PAGE *, PAGE *));
D 9
static int	 bt_broot __P((BTREE *, PAGE *, PAGE *, PAGE *));
E 9
static recno_t	 rec_total __P((PAGE *));

#ifdef STATISTICS
u_long	bt_rootsplit, bt_split, bt_sortsplit, bt_pfxsaved;
#endif

E 3
/*
D 3
 *  _BT_SPLIT -- Split a page into two pages.
E 3
I 3
 * __BT_SPLIT -- Split the tree.
E 3
 *
D 3
 *	Splits are caused by insertions, and propogate up the tree in
 *	the usual way.  The root page is always page 1 in the file on
 *	disk, so root splits are handled specially.  On entry to this
 *	routine, t->bt_curpage is the page to be split.
E 3
I 3
 * Parameters:
 *	t:	tree
D 9
 *	h:	page to split
E 9
I 9
 *	sp:	page to split
E 9
 *	key:	key to insert
 *	data:	data to insert
 *	flags:	BIGKEY/BIGDATA flags
D 10
 *	nbytes:	length of insertion
E 10
I 10
 *	ilen:	insert length
E 10
 *	skip:	index to leave open
E 3
 *
D 3
 *	Parameters:
 *		t -- btree in which to do split.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Changes the notion of the current page.
E 3
I 3
 * Returns:
 *	RET_ERROR, RET_SUCCESS
E 3
 */
D 3

E 3
int
D 3
_bt_split(t)
	BTREE_P t;
E 3
I 3
D 9
__bt_split(t, h, key, data, flags, nbytes, skip)
E 9
I 9
D 10
__bt_split(t, sp, key, data, flags, nbytes, skip)
E 10
I 10
__bt_split(t, sp, key, data, flags, ilen, skip)
E 10
E 9
	BTREE *t;
D 9
	PAGE *h;
E 9
I 9
	PAGE *sp;
E 9
	const DBT *key, *data;
D 19
	u_long flags;
E 19
I 19
	int flags;
E 19
D 10
	size_t nbytes;
E 10
I 10
	size_t ilen;
E 10
D 14
	int skip;
E 14
I 14
D 19
	u_int skip;
E 19
I 19
	indx_t skip;
E 19
E 14
E 3
{
D 3
	BTHEADER *h;
	BTHEADER *left, *right;
	pgno_t nextpgno, parent;
	int nbytes, len;
	IDATUM *id;
	DATUM *d;
	char *src;
	IDATUM *new;
	pgno_t oldchain;
	u_char flags;
E 3
I 3
	BINTERNAL *bi;
D 10
	BLEAF *bl;
E 10
I 10
	BLEAF *bl, *tbl;
E 10
	DBT a, b;
	EPGNO *parent;
D 9
	PAGE *l, *r, *lchild, *rchild;
E 9
I 9
	PAGE *h, *l, *r, *lchild, *rchild;
E 9
D 12
	index_t nxtindex;
E 12
I 12
	indx_t nxtindex;
E 12
D 10
	size_t nksize;
E 10
I 10
	size_t n, nbytes, nksize;
E 10
D 17
	int nosplit;
E 17
I 17
	int parentsplit;
E 17
	char *dest;
E 3

D 3
	h = (BTHEADER *) t->bt_curpage;

	/* split root page specially, since it must remain page 1 */
	if (h->h_pgno == P_ROOT) {
		return (_bt_splitroot(t));
	}

E 3
	/*
D 3
	 *  This is a little complicated.  We go to some trouble to
	 *  figure out which of the three possible cases -- in-memory tree,
	 *  disk tree (no cache), and disk tree (cache) -- we have, in order
	 *  to avoid unnecessary copying.  If we have a disk cache, then we
	 *  have to do some extra copying, though, since the cache code
	 *  manages buffers externally to this code.
E 3
I 3
	 * Split the page into two pages, l and r.  The split routines return
D 9
	 * a pointer to the page into which the key should be inserted and skip
	 * set to the offset which should be used.  Additionally, l and r are
	 * pinned.
E 9
I 9
	 * a pointer to the page into which the key should be inserted and with
	 * skip set to the offset which should be used.  Additionally, l and r
	 * are pinned.
E 9
E 3
	 */
D 3

	if (ISDISK(t) && ISCACHE(t)) {
		if ((left = (BTHEADER *) malloc((unsigned) t->bt_psize))
		    == (BTHEADER *) NULL)
			return (RET_ERROR);
		left->h_pgno = left->h_prevpg = left->h_nextpg = P_NONE;
		left->h_flags = t->bt_curpage->h_flags;
		left->h_lower = (index_t)
			  (((char *) &(left->h_linp[0])) - ((char *) left));
		left->h_upper = t->bt_psize;

	} else {
		if ((left = _bt_allocpg(t)) == (BTHEADER *) NULL)
			return (RET_ERROR);
	}
	left->h_pgno = h->h_pgno;

	if ((right = _bt_allocpg(t)) == (BTHEADER *) NULL)
E 3
I 3
D 9
	h = h->pgno == P_ROOT ?
	    bt_root(t, h, &l, &r, &skip) : bt_page(t, h, &l, &r, &skip);
E 9
I 9
	h = sp->pgno == P_ROOT ?
D 10
	    bt_root(t, sp, &l, &r, &skip) : bt_page(t, sp, &l, &r, &skip);
E 10
I 10
	    bt_root(t, sp, &l, &r, &skip, ilen) :
	    bt_page(t, sp, &l, &r, &skip, ilen);
E 10
E 9
	if (h == NULL)
E 3
		return (RET_ERROR);
D 3
	right->h_pgno = ++(t->bt_npages);
E 3

D 3
	/* now do the split */
	if (_bt_dopsplit(t, left, right) == RET_ERROR)
		return (RET_ERROR);

	right->h_prevpg = left->h_pgno;
	nextpgno = right->h_nextpg = h->h_nextpg;
	left->h_nextpg = right->h_pgno;
	left->h_prevpg = h->h_prevpg;

	/* okay, now use the left half of the page as the new page */
	if (ISDISK(t) && ISCACHE(t)) {
		(void) bcopy((char *) left, (char *) t->bt_curpage,
			     (int) t->bt_psize);
		(void) free ((char *) left);
		left = t->bt_curpage;
E 3
I 3
	/*
D 9
	 * Grab the space and insert the [rb]leaf structure.  Always a [rb]leaf
	 * structure since key inserts always cause a leaf page to split first.
E 9
I 9
	 * Insert the new key/data pair into the leaf page.  (Key inserts
	 * always cause a leaf page to split first.)
E 9
	 */
D 10
	h->linp[skip] = h->upper -= nbytes;
E 10
I 10
	h->linp[skip] = h->upper -= ilen;
E 10
	dest = (char *)h + h->upper;
D 4
	if (ISSET(t, BTF_RECNO)) {
E 4
I 4
D 16
	if (ISSET(t, BTF_RECNO))
E 16
I 16
	if (ISSET(t, R_RECNO))
E 16
E 4
		WR_RLEAF(dest, data, flags)
D 4
		++t->bt_nrecs;
		SET(t, BTF_METADIRTY | BTF_MODIFIED);
E 3
	} else {
E 4
I 4
	else
E 4
D 3
		(void) free((char *) t->bt_curpage);
		t->bt_curpage = left;
E 3
I 3
		WR_BLEAF(dest, key, data, flags)
D 4
		SET(t, BTF_MODIFIED);
E 3
	}
E 4

I 9
	/* If the root page was split, make it look right. */
	if (sp->pgno == P_ROOT &&
D 16
	    (ISSET(t, BTF_RECNO) ?
E 16
I 16
	    (ISSET(t, R_RECNO) ?
E 16
	    bt_rroot(t, sp, l, r) : bt_broot(t, sp, l, r)) == RET_ERROR)
		goto err2;

E 9
	/*
D 3
	 *  Write the new pages out.  We need them to stay where they are
	 *  until we're done updating the parent pages.
E 3
I 3
	 * Now we walk the parent page stack -- a LIFO stack of the pages that
	 * were traversed when we searched for the page that split.  Each stack
	 * entry is a page number and a page index offset.  The offset is for
	 * the page traversed on the search.  We've just split a page, so we
	 * have to insert a new key into the parent page.
	 *
	 * If the insert into the parent page causes it to split, may have to
	 * continue splitting all the way up the tree.  We stop if the root
	 * splits or the page inserted into didn't have to split to hold the
	 * new key.  Some algorithms replace the key for the old page as well
	 * as the new page.  We don't, as there's no reason to believe that the
	 * first key on the old page is any better than the key we have, and,
	 * in the case of a key being placed at index 0 causing the split, the
	 * key is unavailable.
	 *
	 * There are a maximum of 5 pages pinned at any time.  We keep the left
	 * and right pages pinned while working on the parent.   The 5 are the
	 * two children, left parent and right parent (when the parent splits)
	 * and the root page or the overflow key page when calling bt_preserve.
	 * This code must make sure that all pins are released other than the
	 * root page or overflow page which is unlocked elsewhere.
E 3
	 */
I 3
D 17
	for (nosplit = 0; (parent = BT_POP(t)) != NULL;) {
E 17
I 17
	while ((parent = BT_POP(t)) != NULL) {
E 17
		lchild = l;
		rchild = r;
E 3

D 3
	if (_bt_write(t, left, NORELEASE) == RET_ERROR)
		return (RET_ERROR);
	if (_bt_write(t, right, NORELEASE) == RET_ERROR)
		return (RET_ERROR);
E 3
I 3
		/* Get the parent page. */
		if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
			goto err2;
E 3

D 3
	/* update 'prev' pointer of old neighbor of left */
	if (nextpgno != P_NONE) {
		if (_bt_getpage(t, nextpgno) == RET_ERROR)
			return (RET_ERROR);
		h = t->bt_curpage;
		h->h_prevpg = right->h_pgno;
		h->h_flags |= F_DIRTY;
	}
E 3
I 3
D 10
	 	/* The new key goes ONE AFTER the index. */
E 10
I 10
	 	/*
		 * The new key goes ONE AFTER the index, because the split
		 * was to the right.
		 */
E 10
		skip = parent->index + 1;
E 3

D 3
	if ((parent = _bt_pop(t)) != P_NONE) {
		if (right->h_flags & F_LEAF) {
			d = (DATUM *) GETDATUM(right, 0);
			len = d->d_ksize;
			if (d->d_flags & D_BIGKEY) {
				bcopy(&(d->d_bytes[0]),
				      (char *) &oldchain,
				      sizeof(oldchain));
				if (_bt_markchain(t, oldchain) == RET_ERROR)
					return (RET_ERROR);
				src = (char *) &oldchain;
				flags = D_BIGKEY;
			} else {
				src = (char *) &(d->d_bytes[0]);
				flags = 0;
E 3
I 3
		/*
		 * Calculate the space needed on the parent page.
		 *
D 4
		 * Space hack when insertin into BINTERNAL pages.  Only need to
E 4
I 4
D 10
		 * Space hack when inserting into BINTERNAL pages.  Only need to
E 4
		 * retain the number of bytes that will distinguish between the
D 4
		 * new entry and the LAST entry on the page to its left.  If
		 * the keys compare equal, only need to retain one byte as a
		 * placeholder.  Special cases are that the entire key must be
		 * retained for the next-to-leftmost key on the leftmost page
		 * of each level, or the search will fail, and can't mess with
		 * overflow keys.
E 4
I 4
		 * new entry and the LAST entry on the page to its left.  If the
		 * keys compare equal, retain the entire key.  Note, we don't
		 * touch overflow keys and the entire key must be retained for
		 * the next-to-leftmost key on the leftmost page of each level,
		 * or the search will fail.
E 10
I 10
		 * Prefix trees: space hack when inserting into BINTERNAL
		 * pages.  Retain only what's needed to distinguish between
		 * the new entry and the LAST entry on the page to its left.
		 * If the keys compare equal, retain the entire key.  Note,
		 * we don't touch overflow keys, and the entire key must be
		 * retained for the next-to-left most key on the leftmost
		 * page of each level, or the search will fail.  Applicable
		 * ONLY to internal pages that have leaf pages as children.
		 * Further reduction of the key between pairs of internal
		 * pages loses too much information.
E 10
E 4
		 */
		switch (rchild->flags & P_TYPE) {
		case P_BINTERNAL:
			bi = GETBINTERNAL(rchild, 0);
			nbytes = NBINTERNAL(bi->ksize);
D 10
			if (t->bt_pfx && (h->prevpg != P_INVALID || skip > 1) &&
			    !(bi->flags & P_BIGKEY)) {
				BINTERNAL *tbi;
				tbi =
				    GETBINTERNAL(lchild, NEXTINDEX(lchild) - 1);
				a.size = tbi->ksize;
				a.data = tbi->bytes;
				b.size = bi->ksize;
				b.data = bi->bytes;
				goto prefix;
E 3
D 8
			}
E 8
I 8
			} else
				nksize = 0;
E 10
E 8
I 3
			break;
		case P_BLEAF:
			bl = GETBLEAF(rchild, 0);
D 5
			nbytes = NBLEAF(bl);
E 5
I 5
			nbytes = NBINTERNAL(bl->ksize);
E 5
D 10
			if (t->bt_pfx && (h->prevpg != P_INVALID || skip > 1) &&
			    !(bl->flags & P_BIGKEY)) {
				BLEAF *tbl;
				size_t n;

E 10
I 10
			if (t->bt_pfx && !(bl->flags & P_BIGKEY) &&
			    (h->prevpg != P_INVALID || skip > 1)) {
E 10
				tbl = GETBLEAF(lchild, NEXTINDEX(lchild) - 1);
				a.size = tbl->ksize;
				a.data = tbl->bytes;
				b.size = bl->ksize;
				b.data = bl->bytes;
D 10
prefix:				nksize = t->bt_pfx(&a, &b);
E 10
I 10
				nksize = t->bt_pfx(&a, &b);
E 10
				n = NBINTERNAL(nksize);
				if (n < nbytes) {
#ifdef STATISTICS
					bt_pfxsaved += nbytes - n;
#endif
					nbytes = n;
				} else
					nksize = 0;
			} else
				nksize = 0;
			break;
		case P_RINTERNAL:
		case P_RLEAF:
			nbytes = NRINTERNAL;
			break;
I 8
		default:
			abort();
E 8
		}

		/* Split the parent page if necessary or shift the indices. */
D 12
		if (h->upper - h->lower < nbytes + sizeof(index_t)) {
E 12
I 12
		if (h->upper - h->lower < nbytes + sizeof(indx_t)) {
E 12
I 9
			sp = h;
E 9
			h = h->pgno == P_ROOT ?
D 10
			    bt_root(t, h, &l, &r, &skip) :
			    bt_page(t, h, &l, &r, &skip);
E 10
I 10
			    bt_root(t, h, &l, &r, &skip, nbytes) :
			    bt_page(t, h, &l, &r, &skip, nbytes);
E 10
			if (h == NULL)
				goto err1;
I 17
			parentsplit = 1;
E 17
E 3
		} else {
D 3
			id = (IDATUM *) GETDATUM(right, 0);
			len = id->i_size;
			flags = id->i_flags;
			src = (char *) &(id->i_bytes[0]);
E 3
I 3
			if (skip < (nxtindex = NEXTINDEX(h)))
D 13
				bcopy(h->linp + skip, h->linp + skip + 1,
E 13
I 13
				memmove(h->linp + skip + 1, h->linp + skip,
E 13
D 12
				    (nxtindex - skip) * sizeof(index_t));
			h->lower += sizeof(index_t);
E 12
I 12
				    (nxtindex - skip) * sizeof(indx_t));
			h->lower += sizeof(indx_t);
E 12
D 17
			nosplit = 1;
E 17
I 17
			parentsplit = 0;
E 17
E 3
		}
D 3
		nbytes = len + (sizeof(IDATUM) - sizeof(char));
		new = (IDATUM *) malloc((unsigned) nbytes);
		if (new == (IDATUM *) NULL)
			return (RET_ERROR);
		new->i_size = len;
		new->i_pgno = right->h_pgno;
		new->i_flags = flags;
		if (len > 0)
			(void) bcopy(src, (char *) &(new->i_bytes[0]), len);
E 3

D 3
		nbytes = LONGALIGN(nbytes) + sizeof(index_t);
		if (_bt_getpage(t, parent) == RET_ERROR)
			return (RET_ERROR);
E 3
I 3
		/* Insert the key into the parent page. */
		switch(rchild->flags & P_TYPE) {
		case P_BINTERNAL:
			h->linp[skip] = h->upper -= nbytes;
			dest = (char *)h + h->linp[skip];
D 13
			bcopy(bi, dest, nbytes);
E 13
I 13
			memmove(dest, bi, nbytes);
E 13
D 10
			if (nksize)
				((BINTERNAL *)dest)->ksize = nksize;
E 10
			((BINTERNAL *)dest)->pgno = rchild->pgno;
			break;
		case P_BLEAF:
			h->linp[skip] = h->upper -= nbytes;
			dest = (char *)h + h->linp[skip];
			WR_BINTERNAL(dest, nksize ? nksize : bl->ksize,
D 4
			    rchild->pgno, rchild->flags & P_OVERFLOW);
E 4
I 4
			    rchild->pgno, bl->flags & P_BIGKEY);
E 4
D 13
			bcopy(bl->bytes, dest, nksize ? nksize : bl->ksize);
E 13
I 13
			memmove(dest, bl->bytes, nksize ? nksize : bl->ksize);
E 13
			if (bl->flags & P_BIGKEY &&
			    bt_preserve(t, *(pgno_t *)bl->bytes) == RET_ERROR)
				goto err1;
			break;
		case P_RINTERNAL:
D 17
			/* Update both left and right page counts. */
E 17
I 17
			/*
			 * Update the left page count.  If split
			 * added at index 0, fix the correct page.
			 */
			if (skip > 0)
				dest = (char *)h + h->linp[skip - 1];
			else
				dest = (char *)l + l->linp[NEXTINDEX(l) - 1];
			((RINTERNAL *)dest)->nrecs = rec_total(lchild);
			((RINTERNAL *)dest)->pgno = lchild->pgno;

			/* Update the right page count. */
E 17
			h->linp[skip] = h->upper -= nbytes;
			dest = (char *)h + h->linp[skip];
			((RINTERNAL *)dest)->nrecs = rec_total(rchild);
			((RINTERNAL *)dest)->pgno = rchild->pgno;
D 17
			dest = (char *)h + h->linp[skip - 1];
			((RINTERNAL *)dest)->nrecs = rec_total(lchild);
			((RINTERNAL *)dest)->pgno = lchild->pgno;
E 17
			break;
		case P_RLEAF:
D 17
			/* Update both left and right page counts. */
E 17
I 17
			/*
			 * Update the left page count.  If split
			 * added at index 0, fix the correct page.
			 */
			if (skip > 0)
				dest = (char *)h + h->linp[skip - 1];
			else
				dest = (char *)l + l->linp[NEXTINDEX(l) - 1];
			((RINTERNAL *)dest)->nrecs = NEXTINDEX(lchild);
			((RINTERNAL *)dest)->pgno = lchild->pgno;

			/* Update the right page count. */
E 17
			h->linp[skip] = h->upper -= nbytes;
			dest = (char *)h + h->linp[skip];
			((RINTERNAL *)dest)->nrecs = NEXTINDEX(rchild);
			((RINTERNAL *)dest)->pgno = rchild->pgno;
D 17
			dest = (char *)h + h->linp[skip - 1];
			((RINTERNAL *)dest)->nrecs = NEXTINDEX(lchild);
			((RINTERNAL *)dest)->pgno = lchild->pgno;
E 17
			break;
I 8
		default:
			abort();
E 8
		}
E 3

D 3
		h = t->bt_curpage;
E 3
I 3
		/* Unpin the held pages. */
D 17
		if (nosplit) {
E 17
I 17
		if (!parentsplit) {
E 17
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
			break;
		}
I 9

		/* If the root page was split, make it look right. */
		if (sp->pgno == P_ROOT &&
D 16
		    (ISSET(t, BTF_RECNO) ?
E 16
I 16
		    (ISSET(t, R_RECNO) ?
E 16
		    bt_rroot(t, sp, l, r) : bt_broot(t, sp, l, r)) == RET_ERROR)
			goto err1;

E 9
		mpool_put(t->bt_mp, lchild, MPOOL_DIRTY);
		mpool_put(t->bt_mp, rchild, MPOOL_DIRTY);
	}
E 3

D 3
		/*
		 *  Split the parent if we need to, then reposition the
		 *  tree's current page pointer for the new datum.
		 */
		if ((h->h_upper - h->h_lower) < nbytes) {
			if (_bt_split(t) == RET_ERROR)
E 3
I 3
	/* Unpin the held pages. */
	mpool_put(t->bt_mp, l, MPOOL_DIRTY);
	mpool_put(t->bt_mp, r, MPOOL_DIRTY);

D 4
	/*
	 * If it's a recno tree, increment the count on all remaining parent
	 * pages.  Otherwise, clear the stack.
	 */
	if (ISSET(t, BTF_RECNO))
		while  ((parent = BT_POP(t)) != NULL) {
			if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
E 3
				return (RET_ERROR);
D 3
			if (_bt_reposition(t, new, parent, right->h_prevpg)
			      == RET_ERROR)
				return (RET_ERROR);
E 3
I 3
			++GETRINTERNAL(h, parent->index)->nrecs;
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 3
		}
I 3
	else
		BT_CLR(t);
E 4
I 4
	/* Clear any pages left on the stack. */
D 10
	BT_CLR(t);
E 10
E 4
	return (RET_SUCCESS);
E 3

D 3
		/* okay, now insert the new idatum */
		if (_bt_inserti(t, new, right->h_prevpg) == RET_ERROR)
			return (RET_ERROR);
	}

E 3
	/*
D 3
	 *  Okay, split is done; don't need right page stapled down anymore.
	 *  The page we call 'left' above is the new version of the old
	 *  (split) page, so we can't release it.
E 3
I 3
	 * If something fails in the above loop we were already walking back
	 * up the tree and the tree is now inconsistent.  Nothing much we can
	 * do about it but release any memory we're holding.
E 3
	 */
I 3
err1:	mpool_put(t->bt_mp, lchild, MPOOL_DIRTY);
	mpool_put(t->bt_mp, rchild, MPOOL_DIRTY);
E 3

D 3
	if (_bt_release(t, right) == RET_ERROR)
		return (RET_ERROR);
	if (ISDISK(t) && !ISCACHE(t))
		(void) free((char *) right);

	return (RET_SUCCESS);
E 3
I 3
err2:	mpool_put(t->bt_mp, l, 0);
	mpool_put(t->bt_mp, r, 0);
	__dbpanic(t->bt_dbp);
	return (RET_ERROR);
E 3
}

/*
D 3
 *  _BT_REPOSITION -- Reposition the current page pointer of a btree.
E 3
I 3
 * BT_PAGE -- Split a non-root page of a btree.
E 3
 *
D 3
 *	After splitting a node in the tree in order to make room for
 *	an insertion, we need to figure out which page after the split
 *	should get the item we want to insert.  This routine positions
 *	the tree's current page pointer appropriately.
E 3
I 3
 * Parameters:
 *	t:	tree
 *	h:	root page
 *	lp:	pointer to left page pointer
 *	rp:	pointer to right page pointer
 *	skip:	pointer to index to leave open
I 10
 *	ilen:	insert length
E 10
E 3
 *
D 3
 *	Parameters:
 *		t -- tree to position
 *		new -- the item we want to insert
 *		parent -- parent of the node that we just split
 *		prev -- page number of item directly to the left of
 *			new's position in the tree.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		None.
E 3
I 3
 * Returns:
 *	Pointer to page in which to insert or NULL on error.
E 3
 */
D 3

int
_bt_reposition(t, new, parent, prev)
	BTREE_P t;
	IDATUM *new;
	pgno_t parent;
	pgno_t prev;
E 3
I 3
static PAGE *
D 10
bt_page(t, h, lp, rp, skip)
E 10
I 10
bt_page(t, h, lp, rp, skip, ilen)
E 10
	BTREE *t;
	PAGE *h, **lp, **rp;
D 15
	int *skip;
E 15
I 15
D 19
	u_int *skip;
E 19
I 19
	indx_t *skip;
E 19
E 15
I 10
	size_t ilen;
E 10
E 3
{
D 3
	index_t i, next;
	IDATUM *idx;
E 3
I 3
	PAGE *l, *r, *tp;
	pgno_t npg;
E 3

D 3
	if (parent == P_ROOT) {
E 3
I 3
#ifdef STATISTICS
	++bt_split;
#endif
	/* Put the new right page for the split into place. */
D 7
	if ((r = mpool_new(t->bt_mp, &npg)) == NULL)
E 7
I 7
	if ((r = __bt_new(t, &npg)) == NULL)
E 7
		return (NULL);
	r->pgno = npg;
	r->lower = BTDATAOFF;
	r->upper = t->bt_psize;
	r->nextpg = h->nextpg;
	r->prevpg = h->pgno;
	r->flags = h->flags & P_TYPE;
E 3

D 3
		/*
		 *  If we just split the root page, then there are guaranteed
		 *  to be exactly two IDATUMs on it.  Look at both of them
		 *  to see if they point to the page that we want.
		 */
E 3
I 3
	/*
	 * If we're splitting the last page on a level because we're appending
	 * a key to it (skip is NEXTINDEX()), it's likely that the data is
	 * sorted.  Adding an empty page on the side of the level is less work
	 * and can push the fill factor much higher than normal.  If we're
	 * wrong it's no big deal, we'll just do the split the right way next
	 * time.  It may look like it's equally easy to do a similar hack for
	 * reverse sorted data, that is, split the tree left, but it's not.
	 * Don't even try.
	 */
	if (h->nextpg == P_INVALID && *skip == NEXTINDEX(h)) {
#ifdef STATISTICS
		++bt_sortsplit;
#endif
		h->nextpg = r->pgno;
D 12
		r->lower = BTDATAOFF + sizeof(index_t);
E 12
I 12
		r->lower = BTDATAOFF + sizeof(indx_t);
E 12
		*skip = 0;
		*lp = h;
		*rp = r;
		return (r);
	}
E 3

D 3
		if (_bt_getpage(t, parent) == RET_ERROR)
			return (RET_ERROR);
E 3
I 3
	/* Put the new left page for the split into place. */
D 20
	if ((l = malloc(t->bt_psize)) == NULL) {
E 20
I 20
	if ((l = (PAGE *)malloc(t->bt_psize)) == NULL) {
E 20
		mpool_put(t->bt_mp, r, 0);
		return (NULL);
	}
	l->pgno = h->pgno;
	l->nextpg = r->pgno;
	l->prevpg = h->prevpg;
	l->lower = BTDATAOFF;
	l->upper = t->bt_psize;
	l->flags = h->flags & P_TYPE;
E 3

D 3
		next = NEXTINDEX(t->bt_curpage);
		for (i = 0; i < next; i++) {
			idx = (IDATUM *) GETDATUM(t->bt_curpage, i);
			if (_bt_getpage(t, idx->i_pgno) == RET_ERROR)
				return (RET_ERROR);
			if (_bt_isonpage(t, new, prev) == RET_SUCCESS)
				return (RET_SUCCESS);
			if (_bt_getpage(t, parent) == RET_ERROR)
				return (RET_ERROR);
E 3
I 3
	/* Fix up the previous pointer of the page after the split page. */
	if (h->nextpg != P_INVALID) {
		if ((tp = mpool_get(t->bt_mp, h->nextpg, 0)) == NULL) {
			free(l);
			/* XXX mpool_free(t->bt_mp, r->pgno); */
			return (NULL);
E 3
		}
D 3
	} else {
E 3
I 3
		tp->prevpg = r->pgno;
		mpool_put(t->bt_mp, tp, 0);
	}
E 3

D 3
		/*
		 *  Get the parent page -- which is where the new item would
		 *  have gone -- and figure out whether the new item now goes
		 *  on the parent, or the page immediately to the right of
		 *  the parent.
		 */
E 3
I 3
	/*
	 * Split right.  The key/data pairs aren't sorted in the btree page so
	 * it's simpler to copy the data from the split page onto two new pages
	 * instead of copying half the data to the right page and compacting
	 * the left page in place.  Since the left page can't change, we have
	 * to swap the original and the allocated left page after the split.
	 */
D 10
	tp = bt_psplit(t, h, l, r, skip);
E 10
I 10
	tp = bt_psplit(t, h, l, r, skip, ilen);
E 10
E 3

D 3
		if (_bt_getpage(t, parent) == RET_ERROR)
			return (RET_ERROR);
		if (_bt_isonpage(t, new, prev) == RET_SUCCESS)
			return (RET_SUCCESS);
		if (_bt_getpage(t, t->bt_curpage->h_nextpg) == RET_ERROR)
			return (RET_ERROR);
		if (_bt_isonpage(t, new, prev) == RET_SUCCESS)
			return (RET_SUCCESS);
	}
	return (RET_ERROR);
E 3
I 3
	/* Move the new left page onto the old left page. */
D 9
	bcopy(l, h, t->bt_psize);
E 9
I 9
D 10
	memmove(h, l, t->bt_psize);
E 10
I 10
D 13
	bcopy(l, h, t->bt_psize);
E 13
I 13
	memmove(h, l, t->bt_psize);
E 13
E 10
E 9
	if (tp == l)
		tp = h;
	free(l);

	*lp = h;
	*rp = r;
	return (tp);
E 3
}

/*
D 3
 *  _BT_ISONPAGE -- Is the IDATUM for a given page number on the current page?
E 3
I 3
D 4
 * BT_RSPLIT -- Split the root page of a btree.
E 4
I 4
 * BT_ROOT -- Split the root page of a btree.
E 4
E 3
 *
D 3
 *	This routine is used by _bt_reposition to decide whether the current
 *	page is the correct one on which to insert a new item.
E 3
I 3
 * Parameters:
 *	t:	tree
 *	h:	root page
 *	lp:	pointer to left page pointer
 *	rp:	pointer to right page pointer
 *	skip:	pointer to index to leave open
I 10
 *	ilen:	insert length
E 10
E 3
 *
D 3
 *	Parameters:
 *		t -- tree to check
 *		new -- the item that will be inserted (used for binary search)
 *		prev -- page number of page whose IDATUM is immediately to
 *			the left of new's position in the tree.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR (corresponding to TRUE, FALSE).
E 3
I 3
 * Returns:
 *	Pointer to page in which to insert or NULL on error.
E 3
 */
D 3

int
_bt_isonpage(t, new, prev)
	BTREE_P t;
	IDATUM *new;
	pgno_t prev;
E 3
I 3
static PAGE *
D 10
bt_root(t, h, lp, rp, skip)
E 10
I 10
bt_root(t, h, lp, rp, skip, ilen)
E 10
	BTREE *t;
	PAGE *h, **lp, **rp;
D 15
	int *skip;
E 15
I 15
D 19
	u_int *skip;
E 19
I 19
	indx_t *skip;
E 19
E 15
I 10
	size_t ilen;
E 10
E 3
{
D 3
	BTHEADER *h = (BTHEADER *) t->bt_curpage;
	index_t i, next;
	IDATUM *idx;
E 3
I 3
	PAGE *l, *r, *tp;
	pgno_t lnpg, rnpg;
E 3

D 3
	i = _bt_binsrch(t, &(new->i_bytes[0]));
	while (i != 0 && _bt_cmp(t, &(new->i_bytes[0]), i) == 0)
		--i;
	next = NEXTINDEX(h);
	idx = (IDATUM *) GETDATUM(h, i);
	while (i < next && idx->i_pgno != prev) {
		i++;
		idx = (IDATUM *) GETDATUM(h, i);
	}
	if (idx->i_pgno == prev)
		return (RET_SUCCESS);
	else
		return (RET_ERROR);
E 3
I 3
#ifdef STATISTICS
	++bt_split;
	++bt_rootsplit;
#endif
	/* Put the new left and right pages for the split into place. */
D 7
	if ((l = mpool_new(t->bt_mp, &lnpg)) == NULL ||
	    (r = mpool_new(t->bt_mp, &rnpg)) == NULL)
E 7
I 7
	if ((l = __bt_new(t, &lnpg)) == NULL ||
	    (r = __bt_new(t, &rnpg)) == NULL)
E 7
		return (NULL);
	l->pgno = lnpg;
	r->pgno = rnpg;
	l->nextpg = r->pgno;
	r->prevpg = l->pgno;
	l->prevpg = r->nextpg = P_INVALID;
	l->lower = r->lower = BTDATAOFF;
	l->upper = r->upper = t->bt_psize;
	l->flags = r->flags = h->flags & P_TYPE;

	/* Split the root page. */
D 10
	tp = bt_psplit(t, h, l, r, skip);
E 10
I 10
	tp = bt_psplit(t, h, l, r, skip, ilen);
E 10

D 9
	/* Make the root page look right. */
	if ((ISSET(t, BTF_RECNO) ?
	    bt_rroot(t, h, l, r) : bt_broot(t, h, l, r)) == RET_ERROR)
		return (NULL);

E 9
	*lp = l;
	*rp = r;
	return (tp);
E 3
}

/*
D 3
 *  _BT_SPLITROOT -- Split the root of a btree.
E 3
I 3
D 9
 * BT_RROOT -- Fix up the recno root page after the split.
E 9
I 9
 * BT_RROOT -- Fix up the recno root page after it has been split.
E 9
E 3
 *
D 3
 *	The root page for a btree is always page one.  This means that in
 *	order to split the root, we need to do extra work.
E 3
I 3
 * Parameters:
 *	t:	tree
 *	h:	root page
I 9
 *	l:	left page
 *	r:	right page
E 9
E 3
 *
D 3
 *	Parameters:
 *		t -- tree to split
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Splits root upward in the usual way, adding two new pages
 *		to the tree (rather than just one, as in usual splits).
E 3
I 3
 * Returns:
 *	RET_ERROR, RET_SUCCESS
E 3
 */
D 3

int
_bt_splitroot(t)
	BTREE_P t;
E 3
I 3
static int
bt_rroot(t, h, l, r)
	BTREE *t;
	PAGE *h, *l, *r;
E 3
{
D 3
	BTHEADER *h = t->bt_curpage;
	BTHEADER *left, *right;
	IDATUM *id;
	BTHEADER *where_h;
	char *src, *dest;
	int len, nbytes;
	u_long was_leaf;
	pgno_t oldchain;
	u_char flags;
E 3
I 3
	char *dest;
E 3

D 3
	/* get two new pages for the split */
	if ((left = _bt_allocpg(t)) == (BTHEADER *) NULL)
		return (RET_ERROR);
	left->h_pgno = ++(t->bt_npages);
	if ((right = _bt_allocpg(t)) == (BTHEADER *) NULL)
		return (RET_ERROR);
	right->h_pgno = ++(t->bt_npages);
E 3
I 3
	/* Insert the left and right keys, set the header information. */
	h->linp[0] = h->upper = t->bt_psize - NRINTERNAL;
	dest = (char *)h + h->upper;
	WR_RINTERNAL(dest,
	    l->flags & P_RLEAF ? NEXTINDEX(l) : rec_total(l), l->pgno);
E 3

D 3
	/* do the split */
	if (_bt_dopsplit(t, left, right) == RET_ERROR)
		return (RET_ERROR);
E 3
I 3
	h->linp[1] = h->upper -= NRINTERNAL;
	dest = (char *)h + h->upper;
	WR_RINTERNAL(dest,
	    r->flags & P_RLEAF ? NEXTINDEX(r) : rec_total(r), r->pgno);
E 3

D 3
	/* connect the new pages correctly */
	right->h_prevpg = left->h_pgno;
	left->h_nextpg = right->h_pgno;
E 3
I 3
D 12
	h->lower = BTDATAOFF + 2 * sizeof(index_t);
E 12
I 12
	h->lower = BTDATAOFF + 2 * sizeof(indx_t);
E 12
E 3

D 3
	/*
	 *  Write the child pages out now.  We need them to remain
	 *  where they are until we finish updating parent pages,
	 *  however.
	 */
E 3
I 3
	/* Unpin the root page, set to recno internal page. */
	h->flags &= ~P_TYPE;
	h->flags |= P_RINTERNAL;
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 3

D 3
	if (_bt_write(t, left, NORELEASE) == RET_ERROR)
		return (RET_ERROR);
	if (_bt_write(t, right, NORELEASE) == RET_ERROR)
		return (RET_ERROR);
E 3
I 3
	return (RET_SUCCESS);
}
E 3

D 3
	/* now change the root page into an internal page */
	was_leaf = (h->h_flags & F_LEAF);
	h->h_flags &= ~F_LEAF;
	h->h_lower = (index_t) (((char *) (&(h->h_linp[0]))) - ((char *) h));
	h->h_upper = (index_t) t->bt_psize;
	(void) bzero((char *) &(h->h_linp[0]), (int) (h->h_upper - h->h_lower));
E 3
I 3
/*
D 9
 * BT_BROOT -- Fix up the btree root page after the split.
E 9
I 9
 * BT_BROOT -- Fix up the btree root page after it has been split.
E 9
 *
 * Parameters:
 *	t:	tree
 *	h:	root page
I 9
 *	l:	left page
 *	r:	right page
E 9
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
static int
bt_broot(t, h, l, r)
	BTREE *t;
	PAGE *h, *l, *r;
{
	BINTERNAL *bi;
	BLEAF *bl;
	size_t nbytes;
	char *dest;
E 3

D 3
	/* put two new keys on root page */
	where_h = left;
	while (where_h) {
		DATUM *data;
		IDATUM *idata;

		if (was_leaf) {
			data = (DATUM *) GETDATUM(where_h, 0);

			if (where_h == left) {
				len = 0;	/* first key in tree is null */
			} else {
				if (data->d_flags & D_BIGKEY) {
					bcopy(&(data->d_bytes[0]),
					      (char *) &oldchain,
					      sizeof(oldchain));
					if (_bt_markchain(t, oldchain) == RET_ERROR)
						return (RET_ERROR);
					src = (char *) &oldchain;
					flags = D_BIGKEY;
				} else {
					src = (char *) &(data->d_bytes[0]);
					flags = 0;
				}
				len = data->d_ksize;
			}
		} else {
			idata = (IDATUM *) GETDATUM(where_h, 0);
			len = idata->i_size;
			flags = idata->i_flags;
			src = &(idata->i_bytes[0]);
		}
		dest = ((char *) h) + h->h_upper;
		nbytes = len + (sizeof (IDATUM) - sizeof(char));
		dest -= LONGALIGN(nbytes);
		id = (IDATUM *) dest;
		id->i_size = len;
		id->i_pgno = where_h->h_pgno;
		id->i_flags = flags;
		if (len > 0)
			(void) bcopy((char *) src, (char *) &(id->i_bytes[0]), len);
		dest -= ((int) h);
		h->h_linp[NEXTINDEX(h)] = (index_t) dest;
		h->h_upper = (index_t) dest;
		h->h_lower += sizeof(index_t);

		/* next page */
		if (where_h == left)
			where_h = right;
		else
			where_h = (BTHEADER *) NULL;
	}

	if (_bt_release(t, left) == RET_ERROR)
		return (RET_ERROR);
	if (_bt_release(t, right) == RET_ERROR)
		return (RET_ERROR);

E 3
	/*
D 3
	 *  That's it, split is done.  If we're doing a non-cached disk
	 *  btree, we can free up the pages we allocated, as they're on
	 *  disk, now.
E 3
I 3
	 * If the root page was a leaf page, change it into an internal page.
	 * We copy the key we split on (but not the key's data, in the case of
D 5
	 * a leaf page) to the new root page.  If the key is on an overflow
	 * page, mark the overflow chain so it isn't deleted when the leaf copy
	 * of the key is deleted.
E 5
I 5
	 * a leaf page) to the new root page.
E 5
	 *
	 * The btree comparison code guarantees that the left-most key on any
D 9
	 * level of the tree is never used, so it doesn't need to be filled
	 * in.  (This is not just convenience -- if the insert index is 0, we
	 * don't *have* a key to fill in.)  The right key is available because
	 * the split code guarantees not to split on the skipped index.
E 9
I 9
	 * level of the tree is never used, so it doesn't need to be filled in.
E 9
E 3
	 */
I 3
D 5
	nbytes = LALIGN(sizeof(size_t) + sizeof(pgno_t) + sizeof(u_char));
E 5
I 5
	nbytes = NBINTERNAL(0);
E 5
	h->linp[0] = h->upper = t->bt_psize - nbytes;
	dest = (char *)h + h->upper;
	WR_BINTERNAL(dest, 0, l->pgno, 0);
E 3

D 3
	if (ISDISK(t) && !ISCACHE(t)) {
		(void) free ((char *) left);
		(void) free ((char *) right);
E 3
I 3
	switch(h->flags & P_TYPE) {
	case P_BLEAF:
		bl = GETBLEAF(r, 0);
		nbytes = NBINTERNAL(bl->ksize);
		h->linp[1] = h->upper -= nbytes;
		dest = (char *)h + h->upper;
		WR_BINTERNAL(dest, bl->ksize, r->pgno, 0);
D 13
		bcopy(bl->bytes, dest, bl->ksize);
E 13
I 13
		memmove(dest, bl->bytes, bl->ksize);
E 13

I 5
		/*
		 * If the key is on an overflow page, mark the overflow chain
		 * so it isn't deleted when the leaf copy of the key is deleted.
		 */
E 5
		if (bl->flags & P_BIGKEY &&
		    bt_preserve(t, *(pgno_t *)bl->bytes) == RET_ERROR)
			return (RET_ERROR);
		break;
	case P_BINTERNAL:
		bi = GETBINTERNAL(r, 0);
		nbytes = NBINTERNAL(bi->ksize);
		h->linp[1] = h->upper -= nbytes;
		dest = (char *)h + h->upper;
D 13
		bcopy(bi, dest, nbytes);
E 13
I 13
		memmove(dest, bi, nbytes);
E 13
		((BINTERNAL *)dest)->pgno = r->pgno;
		break;
I 8
	default:
		abort();
E 8
E 3
	}
I 9

	/* There are two keys on the page. */
E 9
I 3
D 12
	h->lower = BTDATAOFF + 2 * sizeof(index_t);
E 12
I 12
	h->lower = BTDATAOFF + 2 * sizeof(indx_t);
E 12
E 3

D 3
	h->h_flags |= F_DIRTY;
E 3
I 3
	/* Unpin the root page, set to btree internal page. */
	h->flags &= ~P_TYPE;
	h->flags |= P_BINTERNAL;
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 3

	return (RET_SUCCESS);
}

/*
D 3
 *  _BT_DOPSPLIT -- Do the work of splitting a page
E 3
I 3
 * BT_PSPLIT -- Do the real work of splitting the page.
E 3
 *
D 3
 *	This routine takes two page pointers and splits the data on the
 *	current page of the btree between them.
E 3
I 3
 * Parameters:
 *	t:	tree
 *	h:	page to be split
 *	l:	page to put lower half of data
 *	r:	page to put upper half of data
D 9
 *	skip:	pointer to index to leave open
E 9
I 9
 *	pskip:	pointer to index to leave open
I 10
 *	ilen:	insert length
E 10
E 9
E 3
 *
D 3
 *	We do a lot of work here to handle duplicate keys on a page; we
 *	have to place these keys carefully to guarantee that later searches
 *	will find them correctly.  See comments in the code below for details.
 *
 *	Parameters:
 *		t -- tree to split
 *		left -- pointer to page to get left half of the data
 *		right -- pointer to page to get right half of the data
 *
 *	Returns:
 *		None.
E 3
I 3
 * Returns:
 *	Pointer to page in which to insert.
E 3
 */
D 3

int
_bt_dopsplit(t, left, right)
	BTREE_P t;
	BTHEADER *left;
	BTHEADER *right;
E 3
I 3
static PAGE *
D 4
bt_psplit(t, h, l, r, skip)
E 4
I 4
D 10
bt_psplit(t, h, l, r, pskip)
E 10
I 10
bt_psplit(t, h, l, r, pskip, ilen)
E 10
E 4
	BTREE *t;
	PAGE *h, *l, *r;
D 4
	int *skip;
E 4
I 4
D 15
	int *pskip;
E 15
I 15
D 19
	u_int *pskip;
E 19
I 19
	indx_t *pskip;
E 19
E 15
I 10
	size_t ilen;
E 10
E 4
E 3
{
D 3
	BTHEADER *h = t->bt_curpage;
	size_t psize;
	char *where;
	BTHEADER *where_h;
	index_t where_i;
	int nbytes, dsize, fixedsize, freespc;
	index_t i;
	index_t save_lower, save_upper, save_i;
	index_t switch_i;
	char *save_key;
	DATUM *d;
	CURSOR *c;
	index_t top;
	int free_save;
	pgno_t chain;
	int ignore;
E 3
I 3
	BINTERNAL *bi;
	BLEAF *bl;
	RLEAF *rl;
	EPGNO *c;
	PAGE *rval;
D 4
	index_t half, sval;
E 4
I 4
D 10
	index_t half, skip;
E 10
I 10
D 12
	index_t full, half, skip, used;
E 12
I 12
D 14
	indx_t full, half, skip, used;
E 12
E 10
E 4
	size_t nbytes;
E 14
	void *src;
D 14
	int bigkeycnt, isbigkey, nxt, off, top;
E 14
I 14
	indx_t full, half, nxt, off, skip, top, used;
	size_t nbytes;
	int bigkeycnt, isbigkey;
E 14
E 3

	/*
D 3
	 *  Our strategy is to put half the bytes on each page.  We figure
	 *  out how many bytes we have total, and then move items until
	 *  the last item moved put at least 50% of the data on the left
	 *  page.
E 3
I 3
D 10
	 * Split the data to the left and right pages. Leave the skip index
D 9
	 * open and guarantee that the split doesn't happen on that index (the
	 * right key must be available for the parent page).  Additionally,
E 9
I 9
	 * open.  Additionally,
E 9
	 * make some effort not to split on an overflow key.  This makes it
	 * faster to process internal pages and can save space since overflow
	 * keys used by internal pages are never deleted.
E 10
I 10
	 * Split the data to the left and right pages.  Leave the skip index
	 * open.  Additionally, make some effort not to split on an overflow
	 * key.  This makes internal page processing faster and can save
	 * space as overflow keys used by internal pages are never deleted.
E 10
E 3
	 */
D 3
	save_key = (char *) NULL;
	psize = (int) t->bt_psize;
	where = ((char *) left) + psize;
	where_h = left;
	where_i = 0;
	nbytes = psize - (int) ((char *) &(h->h_linp[0]) - ((char *) h));
	freespc = nbytes;

	top = NEXTINDEX(h);
	if (h->h_flags & F_LEAF)
		fixedsize = (sizeof(DATUM) - sizeof(char));
	else
		fixedsize = (sizeof(IDATUM) - sizeof(char));

	save_key = (char *) NULL;

	/* move data */
	for (i = 0; i < top; i++) {

		/*
		 *  Internal and leaf pages have different layouts for
		 *  data items, but in both cases the first entry in the
		 *  data item is a size_t.
		 */
		d = (DATUM *) GETDATUM(h,i);
		if (h->h_flags & F_LEAF) {
			dsize = d->d_ksize + d->d_dsize + fixedsize;
		} else {
			dsize = d->d_ksize + fixedsize;
E 3
I 3
	bigkeycnt = 0;
D 4
	sval = *skip;
E 4
I 4
	skip = *pskip;
E 4
D 10
	half = (t->bt_psize - BTDATAOFF) / 2;
E 10
I 10
	full = t->bt_psize - BTDATAOFF;
	half = full / 2;
	used = 0;
E 10
	for (nxt = off = 0, top = NEXTINDEX(h); nxt < top; ++off) {
D 4
		if (sval == off)
E 4
I 4
D 10
		if (skip == off)
E 4
			continue;
		switch (h->flags & P_TYPE) {
		case P_BINTERNAL:
			src = bi = GETBINTERNAL(h, nxt);
			nbytes = NBINTERNAL(bi->ksize);
			isbigkey = bi->flags & P_BIGKEY;
E 10
I 10
		if (skip == off) {
			nbytes = ilen;
			isbigkey = 0;		/* XXX: not really known. */
		} else
			switch (h->flags & P_TYPE) {
			case P_BINTERNAL:
				src = bi = GETBINTERNAL(h, nxt);
				nbytes = NBINTERNAL(bi->ksize);
				isbigkey = bi->flags & P_BIGKEY;
				break;
			case P_BLEAF:
				src = bl = GETBLEAF(h, nxt);
				nbytes = NBLEAF(bl);
				isbigkey = bl->flags & P_BIGKEY;
				break;
			case P_RINTERNAL:
				src = GETRINTERNAL(h, nxt);
				nbytes = NRINTERNAL;
				isbigkey = 0;
				break;
			case P_RLEAF:
				src = rl = GETRLEAF(h, nxt);
				nbytes = NRLEAF(rl);
				isbigkey = 0;
				break;
			default:
				abort();
			}

		/*
		 * If the key/data pairs are substantial fractions of the max
		 * possible size for the page, it's possible to get situations
		 * where we decide to try and copy too much onto the left page.
		 * Make sure that doesn't happen.
		 */
D 21
		if (skip <= off && used + nbytes >= full) {
E 21
I 21
		if (skip <= off && used + nbytes >= full || nxt == top - 1) {
E 21
			--off;
E 10
			break;
D 10
		case P_BLEAF:
			src = bl = GETBLEAF(h, nxt);
			nbytes = NBLEAF(bl);
			isbigkey = bl->flags & P_BIGKEY;
			break;
		case P_RINTERNAL:
			src = GETRINTERNAL(h, nxt);
			nbytes = NRINTERNAL;
			isbigkey = 0;
			break;
		case P_RLEAF:
			src = rl = GETRLEAF(h, nxt);
			nbytes = NRLEAF(rl);
			isbigkey = 0;
			break;
I 8
		default:
			abort();
E 10
E 8
E 3
		}
I 3
D 10
		++nxt;
		l->linp[off] = l->upper -= nbytes;
		bcopy(src, (char *)l + l->upper, nbytes);
E 10
E 3

D 3
		/*
		 *  If a page contains duplicate keys, we have to be
		 *  careful about splits.  A sequence of duplicate keys
		 *  may not begin in the middle of one page and end in
		 *  the middle of another; it must begin on a page boundary,
		 *  in order for searches on the internal nodes to work
		 *  correctly.
		 */
		if (where_h == left) {
			if (save_key == (char *) NULL) {
				if (h->h_flags & F_LEAF) {
					if (d->d_flags & D_BIGKEY) {
						free_save = TRUE;
						bcopy(&(d->d_bytes[0]),
						     (char *) &chain,
						     sizeof(chain));
						if (_bt_getbig(t, chain,
							       &save_key,
							       &ignore)
						    == RET_ERROR)
							return (RET_ERROR);
					} else {
						free_save = FALSE;
						save_key = (char *) &(d->d_bytes[0]);
					}
				} else {
					IDATUM *id = (IDATUM *) d;
E 3
I 3
D 10
		/* There's no empirical justification for the '3'. */
D 5
		if (half < nbytes)
E 5
I 5
D 6
		if (half < nbytes && skip != off + 1)
E 5
			if (!isbigkey || bigkeycnt == 3)
				break;
			else
				++bigkeycnt;
		else
E 6
I 6
		if (half < nbytes) {
E 10
I 10
		/* Copy the key/data pair, if not the skipped index. */
		if (skip != off) {
			++nxt;

			l->linp[off] = l->upper -= nbytes;
D 13
			bcopy(src, (char *)l + l->upper, nbytes);
E 13
I 13
			memmove((char *)l + l->upper, src, nbytes);
E 13
		}

		used += nbytes;
		if (used >= half) {
E 10
D 9
			if (skip != off + 1)
				if (!isbigkey || bigkeycnt == 3)
					break;
				else
					++bigkeycnt;
E 9
I 9
			if (!isbigkey || bigkeycnt == 3)
				break;
			else
				++bigkeycnt;
E 9
D 10
		} else
E 6
			half -= nbytes;
E 10
I 10
		}
E 10
	}
I 10

	/*
	 * Off is the last offset that's valid for the left page.
	 * Nxt is the first offset to be placed on the right page.
	 */
E 10
D 12
	l->lower += (off + 1) * sizeof(index_t);
E 12
I 12
	l->lower += (off + 1) * sizeof(indx_t);
E 12
E 3

D 3
					if (id->i_flags & D_BIGKEY) {
						free_save = TRUE;
						bcopy(&(id->i_bytes[0]),
						     (char *) &chain,
						     sizeof(chain));
						if (_bt_getbig(t, chain,
							       &save_key,
							       &ignore)
						    == RET_ERROR)
							return (RET_ERROR);
					} else {
						free_save = FALSE;
						save_key = (char *)
							&(id->i_bytes[0]);
					}
				}
				save_i = 0;
				save_lower = where_h->h_lower;
				save_upper = where_h->h_upper;
			} else {
				if (_bt_cmp(t, save_key, i) != 0) {
					save_lower = where_h->h_lower;
					save_upper = where_h->h_upper;
					save_i = i;
				}
				if (h->h_flags & F_LEAF) {
					if (free_save)
						(void) free(save_key);
					if (d->d_flags & D_BIGKEY) {
						free_save = TRUE;
						bcopy(&(d->d_bytes[0]),
						     (char *) &chain,
						     sizeof(chain));
						if (_bt_getbig(t, chain,
							       &save_key,
							       &ignore)
						    == RET_ERROR)
							return (RET_ERROR);
					} else {
						free_save = FALSE;
						save_key = (char *) &(d->d_bytes[0]);
					}
				} else {
					IDATUM *id = (IDATUM *) d;

					if (id->i_flags & D_BIGKEY) {
						free_save = TRUE;
						bcopy(&(id->i_bytes[0]),
						     (char *) &chain,
						     sizeof(chain));
						if (_bt_getbig(t, chain,
							       &save_key,
							       &ignore)
						    == RET_ERROR)
							return (RET_ERROR);
					} else {
						free_save = FALSE;
						save_key = (char *)
							&(id->i_bytes[0]);
					}
				}
			}
E 3
I 3
	/*
D 4
	 * If we're splitting the page that the cursor was on, have to adjust
	 * the cursor to point to the same record as before the split.
E 4
I 4
	 * If splitting the page that the cursor was on, the cursor has to be
	 * adjusted to point to the same record as before the split.  If the
D 10
	 * skipped slot and the cursor are both on the left page and the cursor
	 * is on or past the skipped slot, the cursor is incremented by one.
	 * If the skipped slot and the cursor are both on the right page and
	 * the cursor is on or past the skipped slot, the cursor is incremented
	 * by one.  If the skipped slot and the cursor aren't on the same page,
	 * the cursor isn't changed.  Regardless of the relationship of the
	 * skipped slot and the cursor, if the cursor is on the right page it
	 * is decremented by the number of records split to the left page.
E 10
I 10
	 * cursor is at or past the skipped slot, the cursor is incremented by
	 * one.  If the cursor is on the right page, it is decremented by the
	 * number of records split to the left page.
E 10
	 *
D 16
	 * Don't bother checking for the BTF_SEQINIT flag, the page number will
E 16
I 16
	 * Don't bother checking for the B_SEQINIT flag, the page number will
E 16
	 * be P_INVALID.
E 4
	 */
	c = &t->bt_bcursor;
D 10
	if (c->pgno == h->pgno)
D 4
		if (c->index < off)
E 4
I 4
		if (c->index < off) {			/* left page */
E 10
I 10
	if (c->pgno == h->pgno) {
		if (c->index >= skip)
			++c->index;
		if (c->index < nxt)			/* Left page. */
E 10
E 4
			c->pgno = l->pgno;
D 4
		else {
E 4
I 4
D 10
			if (c->index >= skip)
				++c->index;
		} else {				/* right page */
E 10
I 10
		else {					/* Right page. */
E 10
E 4
			c->pgno = r->pgno;
I 4
D 10
			if (c->index >= skip && skip > off)
				++c->index;
E 4
			c->index -= off;
E 10
I 10
			c->index -= nxt;
E 10
E 3
		}
I 10
	}
E 10

D 3
		/* copy data and update page state */
		where -= LONGALIGN(dsize);
		(void) bcopy((char *) d, (char *) where, dsize);
		where_h->h_upper = where_h->h_linp[where_i] =
			(index_t) (where - (int) where_h);
		where_h->h_lower += sizeof(index_t);
		where_i++;
E 3
I 3
	/*
D 10
	 * Decide which page to return, and adjust the skip index if the
	 * to-be-inserted-upon page has changed.
E 10
I 10
	 * If the skipped index was on the left page, just return that page.
	 * Otherwise, adjust the skip index to reflect the new position on
	 * the right page.
E 10
	 */
D 4
	if (sval > off) {
E 4
I 4
D 10
	if (skip > off) {
E 4
		rval = r;
D 4
		*skip -= off + 1;
E 4
I 4
		*pskip -= off + 1;
E 4
	} else
E 10
I 10
	if (skip <= off) {
		skip = 0;
E 10
		rval = l;
I 10
	} else {
		rval = r;
		*pskip -= nxt;
	}
E 10
E 3

D 3
		/* if we've moved half, switch to the right-hand page */
		nbytes -= LONGALIGN(dsize) + sizeof(index_t);
		if ((freespc - nbytes) > nbytes) {
			nbytes = 2 * freespc;

			/* identical keys go on the same page */
			if (save_i > 0) {
				/* i gets incremented at loop bottom... */
				i = save_i - 1;
				where_h->h_lower = save_lower;
				where_h->h_upper = save_upper;
			}
			where = ((char *) right) + psize;
			where_h = right;
			switch_i = where_i;
			where_i = 0;
E 3
I 3
	for (off = 0; nxt < top; ++off) {
D 4
		if (sval == nxt) {
			sval = 0;
E 4
I 4
		if (skip == nxt) {
I 10
			++off;
E 10
			skip = 0;
E 4
D 10
			continue;
E 10
E 3
		}
I 3
		switch (h->flags & P_TYPE) {
		case P_BINTERNAL:
			src = bi = GETBINTERNAL(h, nxt);
			nbytes = NBINTERNAL(bi->ksize);
			break;
		case P_BLEAF:
			src = bl = GETBLEAF(h, nxt);
			nbytes = NBLEAF(bl);
			break;
		case P_RINTERNAL:
			src = GETRINTERNAL(h, nxt);
			nbytes = NRINTERNAL;
			break;
		case P_RLEAF:
			src = rl = GETRLEAF(h, nxt);
			nbytes = NRLEAF(rl);
			break;
I 8
		default:
			abort();
E 8
		}
		++nxt;
		r->linp[off] = r->upper -= nbytes;
D 13
		bcopy(src, (char *)r + r->upper, nbytes);
E 13
I 13
		memmove((char *)r + r->upper, src, nbytes);
E 13
E 3
	}
I 3
D 12
	r->lower += off * sizeof(index_t);
E 12
I 12
	r->lower += off * sizeof(indx_t);
E 12
E 3

D 3
	/*
	 *  If there was an active scan on the database, and we just
	 *  split the page that the cursor was on, we may need to
	 *  adjust the cursor to point to the same entry as before the
	 *  split.
	 */
E 3
I 3
	/* If the key is being appended to the page, adjust the index. */
D 4
	if (sval == top)
E 4
I 4
	if (skip == top)
E 4
D 12
		r->lower += sizeof(index_t);
E 12
I 12
		r->lower += sizeof(indx_t);
E 12
E 3

D 3
	c = &(t->bt_cursor);
	if ((t->bt_flags & BTF_SEQINIT)
	    && (c->c_pgno == h->h_pgno)
	    && (c->c_index >= switch_i)) {
		c->c_pgno = where_h->h_pgno;
		c->c_index -= where_i;
	}
E 3
I 3
	return (rval);
}

/*
 * BT_PRESERVE -- Mark a chain of pages as used by an internal node.
 *
 * Chains of indirect blocks pointed to by leaf nodes get reclaimed when the
 * record that references them gets deleted.  Chains pointed to by internal
 * pages never get deleted.  This routine marks a chain as pointed to by an
 * internal page.
 *
 * Parameters:
 *	t:	tree
 *	pg:	page number of first page in the chain.
 *
 * Returns:
 *	RET_SUCCESS, RET_ERROR.
 */
static int
bt_preserve(t, pg)
	BTREE *t;
	pgno_t pg;
{
	PAGE *h;

	if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
		return (RET_ERROR);
	h->flags |= P_PRESERVE;
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 3
	return (RET_SUCCESS);
I 3
}

/*
 * REC_TOTAL -- Return the number of recno entries below a page.
 *
 * Parameters:
 *	h:	page
 *
 * Returns:
 *	The number of recno entries below a page.
 *
 * XXX
 * These values could be set by the bt_psplit routine.  The problem is that the
 * entry has to be popped off of the stack etc. or the values have to be passed
 * all the way back to bt_split/bt_rroot and it's not very clean.
 */
static recno_t
rec_total(h)
	PAGE *h;
{
	recno_t recs;
D 12
	index_t nxt, top;
E 12
I 12
	indx_t nxt, top;
E 12

	for (recs = 0, nxt = 0, top = NEXTINDEX(h); nxt < top; ++nxt)
		recs += GETRINTERNAL(h, nxt)->nrecs;
	return (recs);
E 3
}
E 1
