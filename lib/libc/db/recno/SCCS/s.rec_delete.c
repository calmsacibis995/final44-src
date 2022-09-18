h17819
s 00002/00003/00169
d D 8.4 94/02/21 15:12:46 bostic 12 11
c first pass at making DB use basic integral types (the Alpha port)
e
s 00001/00003/00171
d D 8.3 94/02/17 08:44:33 bostic 11 10
c don't try and put the page if __rec_search fails!!
c From: Paul Kranenburg <pk@cs.few.eur.nl>
e
s 00007/00000/00167
d D 8.2 93/09/07 11:51:47 bostic 10 9
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00165
d D 8.1 93/06/04 15:25:14 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00165
d D 5.8 93/05/16 15:45:37 bostic 8 7
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00001/00001/00166
d D 5.7 93/02/16 12:33:12 bostic 7 6
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00002/00002/00165
d D 5.6 93/02/14 17:39:03 bostic 6 5
c index_t -> indx_t
e
s 00001/00001/00166
d D 5.5 93/02/11 11:42:18 bostic 5 4
c move db.h to the end of the includes, make compat.h work better
e
s 00010/00010/00157
d D 5.4 92/11/13 17:28:08 bostic 4 3
c test for initialization of the cursor before deleting what it refs
c deleting the cursor changes it, so the test is for no more records
c no need to set the BTF_DELCRSR flag, just decrement the cursor
e
s 00002/00003/00165
d D 5.3 92/06/23 12:28:52 bostic 3 2
c decrement record count in rec_dleaf, where the delete is really done
e
s 00021/00025/00147
d D 5.2 91/09/11 16:23:54 bostic 2 1
c redo cursor deletion; specify delete to __rec_search, don't do parent
c decrements here any more; minor cleanups
e
s 00172/00000/00000
d D 5.1 91/09/04 12:54:05 bostic 1 0
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
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
D 4
#include <errno.h>
E 4
I 4

E 4
D 5
#include <db.h>
E 5
I 4
#include <errno.h>
E 4
#include <stdio.h>
#include <string.h>
I 4

I 5
#include <db.h>
E 5
E 4
D 2
#include "../btree/btree.h"
E 2
I 2
#include "recno.h"
E 2

static int rec_rdelete __P((BTREE *, recno_t));

/*
 * __REC_DELETE -- Delete the item(s) referenced by a key.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *	key:	key to delete
 *	flags:	R_CURSOR if deleting what the cursor references
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key not found.
 */
int
__rec_delete(dbp, key, flags)
	const DB *dbp;
	const DBT *key;
	u_int flags;
{
	BTREE *t;
	recno_t nrec;
	int status;

D 2
	if ((nrec = *(recno_t *)key->data) == 0) {
		errno = EINVAL;
		return (RET_ERROR);
	}
	--nrec;

E 2
	t = dbp->internal;
I 10

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

E 10
	switch(flags) {
	case 0:
I 2
D 4
		if ((nrec = *(recno_t *)key->data) == 0) {
			errno = EINVAL;
			return (RET_ERROR);
		}
E 4
I 4
		if ((nrec = *(recno_t *)key->data) == 0)
			goto einval;
E 4
		if (nrec > t->bt_nrecs)
			return (RET_SPECIAL);
		--nrec;
E 2
		status = rec_rdelete(t, nrec);
		break;
	case R_CURSOR:
D 2
		status = rec_rdelete(t, t->bt_rcursor);
E 2
I 2
D 4
		if (ISSET(t, BTF_DELCRSR))
E 4
I 4
D 8
		if (!ISSET(t, BTF_SEQINIT))
E 8
I 8
		if (!ISSET(t, B_SEQINIT))
E 8
			goto einval;
		if (t->bt_nrecs == 0)
E 4
			return (RET_SPECIAL);
		status = rec_rdelete(t, t->bt_rcursor - 1);
D 4
		if (status == RET_SUCCESS) {
E 4
I 4
		if (status == RET_SUCCESS)
E 4
			--t->bt_rcursor;
D 4
			SET(t, BTF_DELCRSR);
		}
E 4
E 2
		break;
	default:
D 4
		errno = EINVAL;
E 4
I 4
einval:		errno = EINVAL;
E 4
		return (RET_ERROR);
	}

D 3
	if (status == RET_SUCCESS) {
		--t->bt_nrecs;
E 3
I 3
	if (status == RET_SUCCESS)
E 3
D 8
		SET(t, BTF_MODIFIED);
E 8
I 8
		SET(t, B_MODIFIED | R_MODIFIED);
E 8
D 3
	}
E 3
	return (status);
}

/*
 * REC_RDELETE -- Delete the data matching the specified key.
 *
 * Parameters:
 *	tree:	tree
 *	nrec:	record to delete
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key not found.
 */
static int
rec_rdelete(t, nrec)
	BTREE *t;
	recno_t nrec;
{
	EPG *e;
D 2
	EPGNO *parent;
E 2
	PAGE *h;
D 2
	int exact, status;
E 2
I 2
	int status;
E 2

D 2
	/* Find any matching record; __rec_search pins the page. */
	e = __rec_search(t, nrec, &exact);
	if (e == NULL || !exact) {
E 2
I 2
	/* Find the record; __rec_search pins the page. */
D 11
	if ((e = __rec_search(t, nrec, SDELETE)) == NULL) {
E 2
		mpool_put(t->bt_mp, e->page, 0);
E 11
I 11
	if ((e = __rec_search(t, nrec, SDELETE)) == NULL)
E 11
D 2
		return (e == NULL ? RET_ERROR : RET_SPECIAL);
E 2
I 2
		return (RET_ERROR);
E 2
D 11
	}
E 11

	/* Delete the record. */
	h = e->page;
	status = __rec_dleaf(t, h, e->index);
D 2
	if (status == RET_SUCCESS)
		mpool_put(t->bt_mp, h, MPOOL_DIRTY);
	else {
E 2
I 2
	if (status != RET_SUCCESS) {
E 2
		mpool_put(t->bt_mp, h, 0);
		return (status);
	}
D 2

	/* Decrement the count on all parent pages. */
	while  ((parent = BT_POP(t)) != NULL) {
		if ((h = mpool_get(t->bt_mp, parent->pgno, 0)) == NULL)
			return (RET_ERROR);
		--GETRINTERNAL(h, parent->index)->nrecs;
		mpool_put(t->bt_mp, h, MPOOL_DIRTY);
	}
E 2
I 2
	mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 2
	return (RET_SUCCESS);
}

/*
 * __REC_DLEAF -- Delete a single record from a recno leaf page.
 *
 * Parameters:
 *	t:	tree
 *	index:	index on current page to delete
 *
 * Returns:
 *	RET_SUCCESS, RET_ERROR.
 */
int
__rec_dleaf(t, h, index)
	BTREE *t;
	PAGE *h;
D 12
	int index;
E 12
I 12
	indx_t index;
E 12
{
	register RLEAF *rl;
D 6
	register index_t *ip, offset;
E 6
I 6
D 12
	register indx_t *ip, offset;
E 12
I 12
	register indx_t *ip, cnt, offset;
E 12
E 6
	register size_t nbytes;
D 12
	register int cnt;
E 12
	char *from;
	void *to;

	/*
	 * Delete a record from a recno leaf page.  Internal records are never
	 * deleted from internal pages, regardless of the records that caused
	 * them to be added being deleted.  Pages made empty by deletion are
	 * not reclaimed.  They are, however, made available for reuse.
	 *
	 * Pack the remaining entries at the end of the page, shift the indices
	 * down, overwriting the deleted record and its index.  If the record
	 * uses overflow pages, make them available for reuse.
	 */
	to = rl = GETRLEAF(h, index);
	if (rl->flags & P_BIGDATA && __ovfl_delete(t, rl->bytes) == RET_ERROR)
		return (RET_ERROR);
	nbytes = NRLEAF(rl);

	/*
	 * Compress the key/data pairs.  Compress and adjust the [BR]LEAF
	 * offsets.  Reset the headers.
	 */
	from = (char *)h + h->upper;
D 7
	bcopy(from, from + nbytes, (char *)to - from);
E 7
I 7
	memmove(from + nbytes, from, (char *)to - from);
E 7
	h->upper += nbytes;

	offset = h->linp[index];
	for (cnt = &h->linp[index] - (ip = &h->linp[0]); cnt--; ++ip)
		if (ip[0] < offset)
			ip[0] += nbytes;
	for (cnt = &h->linp[NEXTINDEX(h)] - ip; --cnt; ++ip)
		ip[0] = ip[1] < offset ? ip[1] + nbytes : ip[1];
D 6
	h->lower -= sizeof(index_t);
E 6
I 6
	h->lower -= sizeof(indx_t);
E 6
I 3
	--t->bt_nrecs;
E 3
	return (RET_SUCCESS);
}
E 1
