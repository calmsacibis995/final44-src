h35074
s 00001/00001/00197
d D 8.2 94/02/21 17:43:19 bostic 10 9
c cast alloc's to shut SunOS up
e
s 00002/00002/00196
d D 8.1 93/06/04 15:20:35 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00192
d D 5.8 93/02/16 12:33:45 bostic 8 7
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00001/00001/00197
d D 5.7 93/02/11 11:39:24 bostic 7 6
c move db.h to the end of the includes, make compat.h work better
e
s 00002/00000/00196
d D 5.6 92/11/13 16:05:41 bostic 6 5
c prettiness police
e
s 00007/00003/00192
d D 5.5 92/10/13 13:00:01 bostic 5 4
c bcopy the pgno/size for overflow pages, may not be long aligned
c flag all overflow pages with P_OVERFLOW, not just the first one.
e
s 00005/00006/00190
d D 5.4 92/10/09 16:27:32 bostic 4 3
c done freeing overflow page check had a typo, pages not being freed
c implement free page reuse
e
s 00123/00284/00073
d D 5.3 91/09/04 12:47:17 bostic 3 2
c Rev #2.  Redo the btree code add recno's and checkpoint
e
s 00002/00000/00355
d D 5.2 91/02/22 17:16:31 bostic 2 1
c ANSI prototypes
e
s 00355/00000/00000
d D 5.1 91/01/23 08:12:38 mao 1 0
c date and time created 91/01/23 08:12:38 by mao
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
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 3
#include <sys/types.h>
E 3
I 3
#include <sys/param.h>
I 6

E 6
E 3
D 7
#include <db.h>
E 7
I 3
#include <stdio.h>
E 3
I 2
#include <stdlib.h>
#include <string.h>
I 6

I 7
#include <db.h>
E 7
E 6
E 2
#include "btree.h"

/*
D 3
 *  _BT_GETBIG -- Get big data from indirect pages.
E 3
I 3
 * Big key/data code.
E 3
 *
D 3
 *	This routine chases indirect blocks for the big object at the 
 *	specified page to a buffer, and return the address of the buffer.
E 3
I 3
 * Big key and data entries are stored on linked lists of pages.  The initial
 * reference is byte string stored with the key or data and is the page number
 * and size.  The actual record is stored in a chain of pages linked by the
 * nextpg field of the PAGE header.
E 3
 *
D 3
 *	Parameters:
 *		t -- btree with the indirect blocks
 *		pgno -- page number that starts the chain
 *		p -- (char **) to get the address of the buffer containing
 *		     the key or datum.
 *		sz -- pointer to an int to get the size of the instantiated
 *		      object.
E 3
I 3
 * The first page of the chain has a special property.  If the record is used
 * by an internal page, it cannot be deleted and the P_PRESERVE bit will be set
 * in the header.
E 3
 *
D 3
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		None.
E 3
I 3
 * XXX
 * A single DBT is written to each chain, so a lot of space on the last page
 * is wasted.  This is a fairly major bug for some data sets.
E 3
 */

D 3
int
_bt_getbig(t, pgno, p, sz)
	BTREE_P t;
	pgno_t pgno;
	char **p;
	int *sz;
{
	pgno_t save;
	size_t nbytes;
	size_t nhere;
	BTHEADER *h;
	char *top, *from, *where;

	save = t->bt_curpage->h_pgno;
	if (_bt_getpage(t, pgno) == RET_ERROR)
		return (RET_ERROR);

	h = t->bt_curpage;

	bcopy((char *) &(h->h_linp[0]),
	      (char *) &nbytes,
	      (size_t) sizeof(nbytes));

	if ((*p = (char *) malloc(nbytes)) == (char *) NULL)
		return (RET_ERROR);

	*sz = nbytes;
	from = ((char *) (&h->h_linp[0])) + sizeof(nbytes);
	top = ((char *) h) + t->bt_psize;

	/* need more space for data? */

	where = *p;

	while (nbytes > 0) {
		nhere = (int) (top - from);
		if (nhere > nbytes) {
			(void) bcopy(from, where, (size_t) nbytes);
			nbytes = 0;
		} else {
			(void) bcopy(from, where, nhere);
			where += nhere;
			nbytes -= nhere;
			if (_bt_getpage(t, h->h_nextpg) == RET_ERROR)
				return (RET_ERROR);
			h = t->bt_curpage;
			top = ((char *) h) + t->bt_psize;
			from = (char *) &(h->h_linp[0]);
		}
	}

	if (_bt_getpage(t, save) == RET_ERROR)
		return (RET_ERROR);

	return (RET_SUCCESS);
}

E 3
/*
D 3
 *  _BT_DELINDIR -- Delete a chain of indirect blocks from the btree.
E 3
I 3
 * __OVFL_GET -- Get an overflow key/data item.
E 3
 *
D 3
 *	When a large item is deleted from the tree, this routine puts the
 *	space that it occupied onto the free list for later reuse.  The
 *	bt_free entry in the btree structure points at the head of this list.
 *	This value is also stored on disk in the btree's metadata.
E 3
I 3
 * Parameters:
 *	t:	tree
 *	p:	pointer to { pgno_t, size_t }
 *	buf:	storage address
 *	bufsz:	storage size
E 3
 *
D 3
 *	Parameters:
 *		t -- btree from which to delete pages
 *		chain -- page number that starts the chain.
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Invalidates the current on-disk version of the btree's
 *		metadata (if any), and updates the free list appropriately.
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
_bt_delindir(t, chain)
	BTREE_P t;
	pgno_t chain;
E 3
I 3
__ovfl_get(t, p, ssz, buf, bufsz)
	BTREE *t;
	void *p;
	size_t *ssz;
	char **buf;
	size_t *bufsz;
E 3
{
D 3
	BTHEADER *h;
	pgno_t save;
	pgno_t oldfree;
E 3
I 3
	PAGE *h;
	pgno_t pg;
	size_t nb, plen, sz;
E 3

D 3
	h = t->bt_curpage;
	save = h->h_pgno;
	if (_bt_getpage(t, chain) == RET_ERROR)
		return (RET_ERROR);
E 3
I 3
D 5
	pg = *(pgno_t *)p;
	*ssz = sz = *(size_t *)((char *)p + sizeof(pgno_t));
E 5
I 5
D 8
	bcopy(p, &pg, sizeof(pgno_t));
	bcopy((char *)p + sizeof(pgno_t), &sz, sizeof(size_t));
E 8
I 8
	memmove(&pg, p, sizeof(pgno_t));
	memmove(&sz, (char *)p + sizeof(pgno_t), sizeof(size_t));
E 8
	*ssz = sz;
E 5
E 3

D 3
	/*
	 *  If some internal node is pointing at this chain, don't
	 *  delete it.
	 */

	if (t->bt_curpage->h_flags & F_PRESERVE) {
		if (_bt_getpage(t, save) == RET_ERROR)
E 3
I 3
#ifdef DEBUG
	if (pg == P_INVALID || sz == 0)
		abort();
#endif
	/* Make the buffer bigger as necessary. */
	if (*bufsz < sz) {
D 10
		if ((*buf = realloc(*buf, sz)) == NULL)
E 10
I 10
		if ((*buf = (char *)realloc(*buf, sz)) == NULL)
E 10
E 3
			return (RET_ERROR);
D 3
		return (RET_SUCCESS);
E 3
I 3
		*bufsz = sz;
E 3
	}

D 3
	/* if there's nothing on the free list, this is easy... */
	if (t->bt_free == P_NONE) {
		t->bt_free = chain;
	} else {
		oldfree = t->bt_free;

		/* find the end of the data chain for the deleted datum */
		t->bt_free = chain;
		do {
			if (_bt_getpage(t, chain) == RET_ERROR)
				return (RET_ERROR);
			h = t->bt_curpage;
			if (h->h_nextpg != P_NONE)
				chain = h->h_nextpg;
		} while (h->h_nextpg != P_NONE);

		/* link freed pages into free list */
		h->h_nextpg = oldfree;
		if (_bt_write(t, h, RELEASE) == RET_ERROR)
E 3
I 3
	/*
	 * Step through the linked list of pages, copying the data on each one
	 * into the buffer.  Never copy more than the data's length.
	 */
	plen = t->bt_psize - BTDATAOFF;
	for (p = *buf;; p = (char *)p + nb, pg = h->nextpg) {
		if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
E 3
			return (RET_ERROR);
D 3
		if (_bt_getpage(t, oldfree) == RET_ERROR)
			return (RET_ERROR);
		h = t->bt_curpage;
		h->h_prevpg = chain;
		if (_bt_write(t, h, RELEASE) == RET_ERROR)
			return (RET_ERROR);
	}
E 3

D 3
	/* restore the tree's current page pointer */
	if (_bt_getpage(t, save) == RET_ERROR)
		return (RET_ERROR);
E 3
I 3
		nb = MIN(sz, plen);
D 8
		bcopy((char *)h + BTDATAOFF, p, nb);
E 8
I 8
		memmove(p, (char *)h + BTDATAOFF, nb);
E 8
		mpool_put(t->bt_mp, h, 0);
E 3

D 3
	/* we have trashed the tree metadata; rewrite it later */
	t->bt_flags &= ~BTF_METAOK;

E 3
I 3
		if ((sz -= nb) == 0)
			break;
	}
E 3
	return (RET_SUCCESS);
}

/*
D 3
 *  _BT_INDIRECT -- Write a series of indirect pages for big objects.
E 3
I 3
 * __OVFL_PUT -- Store an overflow key/data item.
E 3
 *
D 3
 *	A chain of indirect pages looks like
E 3
I 3
 * Parameters:
 *	t:	tree
 *	data:	DBT to store
 *	pgno:	storage page number
E 3
 *
D 3
 *	   +-------------------+   +---------------------+
 *	   |hdr|size|	       |   |hdr|		 |
 *	   +---+----+	       |   +---+		 |
 *	   |   ... data ...    |   |   ... data ...	 |    ...
 *	   |		       |   |			 |
 *	   +-------------------+   +---------------------+
 *
 *	where hdr is a standard btree page header (with the indirect bit
 *	set), size on the first page is the real size of the datum, and
 *	data are bytes of the datum, split across as many pages as necessary.
 *	Indirect pages are chained together with the h_prevpg and h_nextpg
 *	entries of the page header struct.
 *
 *	A single DBT is written per chain, so space on the last page is
 *	wasted.
 *
 *	We return the page number of the start of the chain.
 *
 *	When a big object is deleted from a tree, the space that it occupied
 *	is placed on a free list for later reuse.  This routine checks that
 *	free list before allocating new pages to the big datum being inserted.
 *
 *	Parameters:
 *		t -- btree in which to store indirect blocks
 *		data -- DBT with the big datum in it
 *		pgno -- place to put the starting page number of the chain
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		Current page is changed on return.
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
_bt_indirect(t, data, pgno)
	BTREE_P t;
	DBT *data;
	pgno_t *pgno;
E 3
I 3
__ovfl_put(t, dbt, pg)
	BTREE *t;
	const DBT *dbt;
	pgno_t *pg;
E 3
{
D 3
	pgno_t prev;
	char *top;
	char *where;
	char *from;
	size_t dsize;
	pgno_t nextchn;
	int ischain;
	BTHEADER *cur;
E 3
I 3
	PAGE *h, *last;
	void *p;
	pgno_t npg;
	size_t nb, plen, sz;
E 3

D 3
	/* get set for first page in chain */
	prev = P_NONE;
	dsize = data->size;
	from = (char *) data->data;

	/* if there are blocks on the free list, use them first */
	if ((*pgno = t->bt_free) == P_NONE) {
		if ((cur = _bt_allocpg(t)) == (BTHEADER *) NULL)
E 3
I 3
	/*
	 * Allocate pages and copy the key/data record into them.  Store the
	 * number of the first page in the chain.
	 */
	plen = t->bt_psize - BTDATAOFF;
	for (last = NULL, p = dbt->data, sz = dbt->size;;
	    p = (char *)p + plen, last = h) {
D 4
		if ((h = mpool_new(t->bt_mp, &npg)) == NULL)
E 4
I 4
		if ((h = __bt_new(t, &npg)) == NULL)
E 4
E 3
			return (RET_ERROR);

D 3
		ischain = 0;
		*pgno = cur->h_pgno = ++(t->bt_npages);
	} else {
		if (_bt_getpage(t, *pgno) == RET_ERROR)
			return (RET_ERROR);
		ischain = 1;
		cur = t->bt_curpage;
	}
E 3
I 3
		h->pgno = npg;
		h->nextpg = h->prevpg = P_INVALID;
I 5
		h->flags = P_OVERFLOW;
E 5
		h->lower = h->upper = 0;
E 3

D 3
	cur->h_flags = F_CONT|F_LEAF;
	(void) bcopy((char *) &dsize, (char *) &cur->h_linp[0], sizeof(size_t));
	where = ((char *) (&cur->h_linp[0])) + sizeof(size_t);
E 3
I 3
		nb = MIN(sz, plen);
D 8
		bcopy(p, (char *)h + BTDATAOFF, nb);
E 8
I 8
		memmove((char *)h + BTDATAOFF, p, nb);
E 8
E 3

D 3
	/* fill and write pages in the chain */
	for (;;) {
		int nhere;
E 3
I 3
		if (last) {
			last->nextpg = h->pgno;
D 5
			last->flags |= P_OVERFLOW;
E 5
			mpool_put(t->bt_mp, last, MPOOL_DIRTY);
		} else
			*pg = h->pgno;
E 3

D 3
		top = ((char *) cur) + t->bt_psize;
		cur->h_prevpg = prev;
		nextchn = cur->h_nextpg;
		nhere = (int) (top - where);

		if (nhere >= dsize) {
			(void) bcopy(from, where, (int) dsize);
			cur->h_nextpg = P_NONE;
			dsize = 0;
		} else {
			(void) bcopy(from, where, (int) nhere);
			dsize -= nhere;
			from += nhere;
			if (nextchn == P_NONE)
				cur->h_nextpg = t->bt_npages + 1;
			prev = cur->h_pgno;
		}

		/* current page is ready to go; write it out */
		if (_bt_write(t, cur, RELEASE) == RET_ERROR)
			return (RET_ERROR);

		/* free the current page, if appropriate */
		if (ISDISK(t) && !ISCACHE(t) && !ischain) {
			(void) free ((char *) cur);
		}

		/* done? */
		if (dsize == 0)
E 3
I 3
		if ((sz -= nb) == 0) {
			mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 3
			break;
D 3

		/* allocate another page */
		if (nextchn == P_NONE) {
			if ((cur = _bt_allocpg(t)) == (BTHEADER *) NULL)
				return (RET_ERROR);
			ischain = 0;
			cur->h_pgno = ++(t->bt_npages);
		} else {
			if (_bt_getpage(t, nextchn) == RET_ERROR)
				return (RET_ERROR);
			ischain = 1;
			cur = t->bt_curpage;
E 3
		}
D 3
		cur->h_flags = F_LEAF | F_CONT;

		where = (char *) (&cur->h_linp[0]);
E 3
	}
D 3

	/* if we used pages from the free list, record changes to it */
	if (*pgno == t->bt_free) {
		t->bt_free = nextchn;
		t->bt_flags &= ~BTF_METAOK;
	}

E 3
	return (RET_SUCCESS);
}

/*
D 3
 *  _BT_MARKCHAIN -- Mark a chain of pages as used by an internal node.
E 3
I 3
 * __OVFL_DELETE -- Delete an overflow chain.
E 3
 *
D 3
 *	Chains of indirect blocks pointed to by leaf nodes get reclaimed
 *	when the item that points to them gets deleted.  Chains pointed
 *	to by internal nodes never get deleted.  This routine marks a
 *	chain as pointed to by an internal node.
E 3
I 3
 * Parameters:
 *	t:	tree
 *	p:	pointer to { pgno_t, size_t }
E 3
 *
D 3
 *	Parameters:
 *		t -- tree in which to mark
 *		chain -- number of first page in chain
 *
 *	Returns:
 *		RET_SUCCESS, RET_ERROR.
 *
 *	Side Effects:
 *		None.
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
_bt_markchain(t, chain)
	BTREE_P t;
	pgno_t chain;
E 3
I 3
__ovfl_delete(t, p)
	BTREE *t;
	void *p;
E 3
{
D 3
	pgno_t save;
E 3
I 3
	PAGE *h;
	pgno_t pg;
	size_t plen, sz;
E 3

D 3
	save = t->bt_curpage->h_pgno;
E 3
I 3
D 5
	pg = *(pgno_t *)p;
	sz = *(size_t *)((char *)p + sizeof(pgno_t));
E 5
I 5
D 8
	bcopy(p, &pg, sizeof(pgno_t));
	bcopy((char *)p + sizeof(pgno_t), &sz, sizeof(size_t));
E 8
I 8
	memmove(&pg, p, sizeof(pgno_t));
	memmove(&sz, (char *)p + sizeof(pgno_t), sizeof(size_t));
E 8
E 5
E 3

D 3
	if (_bt_getpage(t, chain) == RET_ERROR)
E 3
I 3
#ifdef DEBUG
	if (pg == P_INVALID || sz == 0)
		abort();
#endif
	if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
E 3
		return (RET_ERROR);

D 3
	t->bt_curpage->h_flags |= (F_DIRTY|F_PRESERVE);
E 3
I 3
	/* Don't delete chains used by internal pages. */
	if (h->flags & P_PRESERVE) {
		mpool_put(t->bt_mp, h, 0);
		return (RET_SUCCESS);
	}
E 3

D 3
	if (_bt_getpage(t, save) == RET_ERROR)
		return (RET_ERROR);

E 3
I 3
	/* Step through the chain, calling the free routine for each page. */
D 4
	plen = t->bt_psize - BTDATAOFF;
	for (;; sz -= plen) {
		if (sz >= plen)
			break;
E 4
I 4
	for (plen = t->bt_psize - BTDATAOFF;; sz -= plen) {
E 4
		pg = h->nextpg;
D 4
		/* XXX mpool_free(t->bt_mp, h->pgno); */
E 4
I 4
		__bt_free(t, h);
		if (sz <= plen)
			break;
E 4
		if ((h = mpool_get(t->bt_mp, pg, 0)) == NULL)
			return (RET_ERROR);
	}
E 3
	return (RET_SUCCESS);
}
E 1
