h07861
s 00012/00002/00215
d D 8.3 94/03/01 07:46:20 bostic 16 15
c When you put a record beyond the "end" of the database, in the fixed-
c length record world, the intermediate records weren't being created
c correctly, nor were they filled with the fill character.
c From: "Chris G. Demetriou" <cgd@postgres.Berkeley.EDU>
e
s 00006/00000/00211
d D 8.2 93/09/07 11:51:51 bostic 15 14
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00209
d D 8.1 93/06/04 15:25:30 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00205
d D 5.13 93/05/16 15:46:10 bostic 13 12
c break modify into two parts, recno file modify and btree modify
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00004/00014/00205
d D 5.12 93/05/10 12:18:43 bostic 12 11
c delete R_CURSORLOG from the interface (and the code)
e
s 00002/00001/00217
d D 5.11 93/03/19 14:49:16 bostic 11 10
c add BTF_EOF flag, test it instead of bt_reof
c clean up mmap and file pointer uses in recno interface
e
s 00001/00001/00217
d D 5.10 93/02/16 12:33:13 bostic 10 9
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00004/00004/00214
d D 5.9 93/02/14 17:39:04 bostic 9 8
c index_t -> indx_t
e
s 00001/00001/00217
d D 5.8 93/02/11 11:42:21 bostic 8 7
c move db.h to the end of the includes, make compat.h work better
e
s 00000/00001/00218
d D 5.7 93/01/10 12:27:08 bostic 7 6
c clear the stack in the search routine; it's a lot simpler
e
s 00002/00001/00217
d D 5.6 92/12/04 14:19:52 bostic 6 5
c it's an insertion if R_IAFTER or R_IBEFORE are set, regardless
e
s 00031/00012/00187
d D 5.5 92/11/13 17:31:24 bostic 5 4
c key can be set by put, now, so no longer const *; change R_APPEND to
c R_CUSORLOG, with minor changes in semantics
c remove BTF_DELCRSR, since recno just decrements the cursor, add test for
c BTF_SEQINIT if using R_CURSOR
c add in memory recno trees; add R_SETCURSOR, and return the key
e
s 00004/00003/00195
d D 5.4 92/08/26 13:02:29 bostic 4 3
c using the wrong variable to count when entering empty records, so
c only a single empty record was ever entered.  Also, not inserting a record
c unless nrec > bt_nrecs.
e
s 00010/00005/00188
d D 5.3 92/06/23 12:29:55 bostic 3 2
c make R_IAFTER of recno 0 work
e
s 00053/00057/00140
d D 5.2 91/09/11 16:25:33 bostic 2 1
c check user flags; redo cursor implementation; recno doesn't care about
c exactness of search results; do R_NOOVERWRITE at user interface level;
c don't do parent page increments here
e
s 00197/00000/00000
d D 5.1 91/09/04 12:54:08 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 14
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
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
D 8
#include <db.h>
E 8
I 5
#include <errno.h>
E 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 5

I 8
#include <db.h>
E 8
E 5
D 2
#include "../btree/btree.h"
E 2
I 2
#include "recno.h"
E 2

/*
 * __REC_PUT -- Add a recno item to the tree.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *	key:	key
 *	data:	data
D 2
 *	flag:	R_NOOVERWRITE
E 2
I 2
D 5
 *	flag:	R_APPEND, R_IAFTER, R_IBEFORE, R_NOOVERWRITE
E 5
I 5
D 12
 *	flag:	R_CURSORLOG, R_CURSOR, R_IAFTER, R_IBEFORE, R_NOOVERWRITE
E 12
I 12
 *	flag:	R_CURSOR, R_IAFTER, R_IBEFORE, R_NOOVERWRITE
E 12
E 5
E 2
 *
 * Returns:
D 12
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key is already in the
 *	tree and R_NOOVERWRITE specified.
E 12
I 12
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key is
 *	already in the tree and R_NOOVERWRITE specified.
E 12
 */
int
__rec_put(dbp, key, data, flags)
	const DB *dbp;
D 5
	const DBT *key, *data;
E 5
I 5
	DBT *key;
	const DBT *data;
E 5
	u_int flags;
{
	BTREE *t;
	DBT tdata;
	recno_t nrec;
	int status;

D 2
	if (flags &&
	    flags != R_IAFTER && flags != R_IBEFORE && flags != R_NOOVERWRITE ||
	    (nrec = *(recno_t *)key->data) == 0) {
		errno = EINVAL;
E 2
I 2
	t = dbp->internal;

I 15
	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

E 15
	switch (flags) {
D 5
	case R_APPEND:
		nrec = t->bt_nrecs + 1;
		break;
E 5
	case R_CURSOR:
D 5
		if (ISSET(t, BTF_DELCRSR))
E 5
I 5
D 13
		if (!ISSET(t, BTF_SEQINIT))
E 13
I 13
		if (!ISSET(t, B_SEQINIT))
E 13
E 5
			goto einval;
		nrec = t->bt_rcursor;
		break;
I 5
D 12
	case R_CURSORLOG:
		nrec = t->bt_rcursor + 1;
		SET(t, BTF_SEQINIT);
		break;
E 12
	case R_SETCURSOR:
		if ((nrec = *(recno_t *)key->data) == 0)
			goto einval;
		break;
E 5
D 3
	case 0:
E 3
	case R_IAFTER:
I 3
		if ((nrec = *(recno_t *)key->data) == 0) {
			nrec = 1;
			flags = R_IBEFORE;
		}
		break;
	case 0:
E 3
	case R_IBEFORE:
		if ((nrec = *(recno_t *)key->data) == 0)
			goto einval;
		break;
	case R_NOOVERWRITE:
		if ((nrec = *(recno_t *)key->data) == 0)
			goto einval;
		if (nrec <= t->bt_nrecs)
			return (RET_SPECIAL);
		break;
	default:
einval:		errno = EINVAL;
E 2
		return (RET_ERROR);
	}

	/*
D 2
	 * If skipping records, either get them from the original file or
	 * create empty ones.
E 2
I 2
D 3
	 * Make sure that records up to and including the put record are already
 	 * in the database.  If skipping records, create empty ones.
E 3
I 3
	 * Make sure that records up to and including the put record are
	 * already in the database.  If skipping records, create empty ones.
E 3
E 2
	 */
D 2
	t = dbp->internal;
	if (nrec > t->bt_nrecs && t->bt_irec(t, nrec) == RET_ERROR)
		return (RET_ERROR);
E 2
	if (nrec > t->bt_nrecs) {
D 2
		tdata.data = NULL;
		tdata.size = 0;
		while (nrec > t->bt_nrecs) {
			status = __rec_iput(t, nrec, &tdata, 0);
			if (status != RET_SUCCESS)
				return (RET_ERROR);
E 2
I 2
D 5
		if (t->bt_irec(t, nrec) == RET_ERROR)
E 5
I 5
D 11
		if (!ISSET(t, BTF_RINMEM) && t->bt_irec(t, nrec) == RET_ERROR)
E 11
I 11
D 13
		if (!ISSET(t, BTF_EOF | BTF_RINMEM) &&
E 13
I 13
		if (!ISSET(t, R_EOF | R_INMEM) &&
E 13
		    t->bt_irec(t, nrec) == RET_ERROR)
E 11
E 5
			return (RET_ERROR);
		if (nrec > t->bt_nrecs + 1) {
D 16
			tdata.data = NULL;
			tdata.size = 0;
E 16
I 16
			if (ISSET(t, R_FIXLEN)) {
				if ((tdata.data =
				    (void *)malloc(t->bt_reclen)) == NULL)
					return (RET_ERROR);
				tdata.size = t->bt_reclen;
				memset(tdata.data, t->bt_bval, tdata.size);
			} else {
				tdata.data = NULL;
				tdata.size = 0;
			}
E 16
D 4
			while (nrec > t->bt_nrecs)
E 4
I 4
			while (nrec > t->bt_nrecs + 1)
E 4
D 3
				if (__rec_iput(t, nrec, &tdata, 0)
				    != RET_SUCCESS)
E 3
I 3
				if (__rec_iput(t,
D 4
				    nrec, &tdata, 0) != RET_SUCCESS)
E 4
I 4
				    t->bt_nrecs, &tdata, 0) != RET_SUCCESS)
E 4
E 3
					return (RET_ERROR);
I 16
			if (ISSET(t, R_FIXLEN))
				free(tdata.data);
E 16
E 2
		}
	}
D 5
	--nrec;
	if ((status = __rec_iput(t, nrec, data, flags)) == RET_SUCCESS)
		SET(t, BTF_MODIFIED);
	return (status);
E 5
I 5

	if ((status = __rec_iput(t, nrec - 1, data, flags)) != RET_SUCCESS)
		return (status);

D 13
	SET(t, BTF_MODIFIED);
E 13
D 12
	switch(flags) {
	case R_CURSORLOG:
		++t->bt_rcursor;
		break;
	case R_SETCURSOR:
E 12
I 12
	if (flags == R_SETCURSOR)
E 12
		t->bt_rcursor = nrec;
D 12
		break;
	}
E 12
	
I 13
	SET(t, R_MODIFIED);
E 13
	return (__rec_ret(t, NULL, nrec, key, NULL));
E 5
}

/*
 * __REC_IPUT -- Add a recno item to the tree.
 *
 * Parameters:
 *	t:	tree
 *	nrec:	record number
 *	data:	data
D 2
 *	flag:	R_NOOVERWRITE
E 2
 *
 * Returns:
D 2
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key is already in the
 *	tree and R_NOOVERWRITE specified.
E 2
I 2
 *	RET_ERROR, RET_SUCCESS
E 2
 */
int
__rec_iput(t, nrec, data, flags)
	BTREE *t;
	recno_t nrec;
	const DBT *data;
	u_int flags;
{
	DBT tdata;
	EPG *e;
D 2
	EPGNO *parent;
E 2
	PAGE *h;
D 9
	index_t index, nxtindex;
E 9
I 9
	indx_t index, nxtindex;
E 9
	pgno_t pg;
	size_t nbytes;
D 2
	int dflags, exact;
E 2
I 2
	int dflags, status;
E 2
	char *dest, db[NOVFLSIZE];

	/*
	 * If the data won't fit on a page, store it on indirect pages.
	 *
	 * XXX
	 * If the insert fails later on, these pages aren't recovered.
	 */
D 2
	if (data->size >= t->bt_minkeypage) {
E 2
I 2
	if (data->size > t->bt_ovflsize) {
E 2
		if (__ovfl_put(t, data, &pg) == RET_ERROR)
			return (RET_ERROR);
		tdata.data = db;
		tdata.size = NOVFLSIZE;
		*(pgno_t *)db = pg;
		*(size_t *)(db + sizeof(pgno_t)) = data->size;
		dflags = P_BIGDATA;
		data = &tdata;
	} else
		dflags = 0;

	/* __rec_search pins the returned page. */
D 2
	if ((e = __rec_search(t, nrec, &exact)) == NULL)
E 2
I 2
D 4
	if ((e = __rec_search(t, nrec, SINSERT)) == NULL)
E 4
I 4
	if ((e = __rec_search(t, nrec,
D 6
	    nrec > t->bt_nrecs ? SINSERT : SEARCH)) == NULL)
E 6
I 6
	    nrec > t->bt_nrecs || flags == R_IAFTER || flags == R_IBEFORE ?
	    SINSERT : SEARCH)) == NULL)
E 6
E 4
E 2
		return (RET_ERROR);

	h = e->page;
	index = e->index;

	/*
D 2
	 * Add the specified key/data pair to the tree.  If an identical key
	 * is already in the tree, and R_NOOVERWRITE is set, an error is
	 * returned.  If R_NOOVERWRITE is not set, the key is either added (if
	 * duplicates are permitted) or an error is returned.  The R_IAFTER
	 * and R_IBEFORE flags insert the key after/before the specified key.
E 2
I 2
	 * Add the specified key/data pair to the tree.  The R_IAFTER and
	 * R_IBEFORE flags insert the key after/before the specified key.
E 2
	 *
	 * Pages are split as required.
	 */
	switch (flags) {
	case R_IAFTER:
D 2
		if (!exact) {
			errno = EINVAL;
			goto err;
		}
E 2
		++index;
		break;
	case R_IBEFORE:
D 2
		if (!exact) {
			errno = EINVAL;
			goto err;
		}
E 2
		break;
D 2
	case R_NOOVERWRITE:
		if (!exact)
			break;
		BT_CLR(t);
		mpool_put(t->bt_mp, h, 0);
		return (RET_SPECIAL);
E 2
	default:
D 2
		if (!exact || NOTSET(t, BTF_NODUPS))
			break;
		if (__rec_dleaf(t, h, index) == RET_ERROR) {
err:			BT_CLR(t);
E 2
I 2
		if (nrec < t->bt_nrecs &&
		    __rec_dleaf(t, h, index) == RET_ERROR) {
D 7
			BT_CLR(t);
E 7
E 2
			mpool_put(t->bt_mp, h, 0);
			return (RET_ERROR);
		}
		break;
	}

	/*
	 * If not enough room, split the page.  The split code will insert
	 * the key and data and unpin the current page.  If inserting into
	 * the offset array, shift the pointers up.
	 */
	nbytes = NRLEAFDBT(data->size);
D 2
	if (h->upper - h->lower < nbytes + sizeof(index_t))
		return (__bt_split(t, h, NULL, data, dflags, nbytes, index));
E 2
I 2
D 9
	if (h->upper - h->lower < nbytes + sizeof(index_t)) {
E 9
I 9
	if (h->upper - h->lower < nbytes + sizeof(indx_t)) {
E 9
		status = __bt_split(t, h, NULL, data, dflags, nbytes, index);
		if (status == RET_SUCCESS)
			++t->bt_nrecs;
		return (status);
	}
E 2

	if (index < (nxtindex = NEXTINDEX(h)))
D 10
		bcopy(h->linp + index, h->linp + index + 1,
E 10
I 10
		memmove(h->linp + index + 1, h->linp + index,
E 10
D 9
		    (nxtindex - index) * sizeof(index_t));
	h->lower += sizeof(index_t);
E 9
I 9
		    (nxtindex - index) * sizeof(indx_t));
	h->lower += sizeof(indx_t);
E 9

	h->linp[index] = h->upper -= nbytes;
	dest = (char *)h + h->upper;
	WR_RLEAF(dest, data, dflags);

D 13
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 13
D 2

	/* Increment the count on all parent pages. */
	while  ((parent = BT_POP(t)) != NULL) {
		if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
			return (RET_ERROR);
		++GETRINTERNAL(h, parent->index)->nrecs;
		mpool_put(t->bt_mp, h, MPOOL_DIRTY);
	}
E 2
	++t->bt_nrecs;
I 13
	SET(t, B_MODIFIED);
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);

E 13
	return (RET_SUCCESS);
}
E 1
