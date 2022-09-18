h41610
s 00011/00002/00094
d D 8.2 93/09/07 11:52:45 bostic 11 10
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00094
d D 8.1 93/06/04 15:25:37 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00091
d D 5.9 93/05/16 15:46:25 bostic 9 8
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00002/00002/00094
d D 5.8 93/03/19 14:48:55 bostic 8 7
c add BTF_EOF to test instead of bt_reof
c clean up mmap and file pointer uses in recno interface
e
s 00001/00001/00095
d D 5.7 93/02/11 12:00:05 bostic 7 6
c strings.h -> string.h
e
s 00001/00001/00095
d D 5.6 93/02/11 11:42:23 bostic 6 5
c move db.h to the end of the includes, make compat.h work better
e
s 00016/00019/00080
d D 5.5 92/11/13 17:37:31 bostic 5 4
c return RET_SPECIAL if R_PREV and at record 1; check for in memory
c trees; use __rec_ret to return the keys
e
s 00002/00000/00097
d D 5.4 92/07/17 09:52:09 bostic 4 3
c lint
e
s 00004/00002/00093
d D 5.3 92/06/23 12:32:48 bostic 3 2
c make CURSOR of recno 0 do the right thing; copy the key out, too
e
s 00017/00014/00078
d D 5.2 91/09/11 16:27:11 bostic 2 1
c redo cursor implementation, __rec_search interface
e
s 00092/00000/00000
d D 5.1 91/09/04 12:54:09 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 4

E 4
D 5
#include <errno.h>
E 5
D 6
#include <db.h>
E 6
I 5
#include <errno.h>
E 5
#include <limits.h>
#include <stdio.h>
I 4
D 7
#include <strings.h>
E 7
I 7
#include <string.h>
E 7
I 5

I 6
#include <db.h>
E 6
E 5
E 4
D 2
#include "../btree/btree.h"
E 2
I 2
#include "recno.h"
E 2

/*
 * __REC_SEQ -- Recno sequential scan interface.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *	key:	key for positioning and return value
 *	data:	data return value
 *	flags:	R_CURSOR, R_FIRST, R_LAST, R_NEXT, R_PREV.
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS or RET_SPECIAL if there's no next key.
 */
int
__rec_seq(dbp, key, data, flags)
	const DB *dbp;
	DBT *key, *data;
	u_int flags;
{
	BTREE *t;
	EPG *e;
	recno_t nrec;
D 2
	int exact, status;
E 2
I 2
	int status;
E 2

	t = dbp->internal;
I 11

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

E 11
	switch(flags) {
	case R_CURSOR:
D 5
		if ((nrec = *(recno_t *)key->data) == 0) {
			errno = EINVAL;
			return (RET_ERROR);
		}
E 5
I 5
		if ((nrec = *(recno_t *)key->data) == 0)
			goto einval;
E 5
		break;
	case R_NEXT:
D 9
		if (ISSET(t, BTF_SEQINIT)) {
E 9
I 9
		if (ISSET(t, B_SEQINIT)) {
E 9
			nrec = t->bt_rcursor + 1;
			break;
		}
		/* FALLTHROUGH */
	case R_FIRST:
		nrec = 1;
D 2
		SET(t, BTF_SEQINIT);
E 2
		break;
	case R_PREV:
D 9
		if (ISSET(t, BTF_SEQINIT)) {
E 9
I 9
		if (ISSET(t, B_SEQINIT)) {
E 9
D 2
			nrec = t->bt_rcursor - 1;
E 2
I 2
D 5
			if ((nrec = t->bt_rcursor - 1) == 0) {
				errno = EINVAL;
				return (RET_ERROR);
			}
E 5
I 5
			if ((nrec = t->bt_rcursor - 1) == 0)
				return (RET_SPECIAL);
E 5
E 2
			break;
		}
		/* FALLTHROUGH */
	case R_LAST:
D 5
		if (t->bt_irec(t, MAX_REC_NUMBER) == RET_ERROR)
E 5
I 5
D 8
		if (!ISSET(t, BTF_RINMEM) &&
E 8
I 8
D 9
		if (!ISSET(t, BTF_EOF | BTF_RINMEM) &&
E 9
I 9
		if (!ISSET(t, R_EOF | R_INMEM) &&
E 9
E 8
		    t->bt_irec(t, MAX_REC_NUMBER) == RET_ERROR)
E 5
			return (RET_ERROR);
		nrec = t->bt_nrecs;
D 2
		SET(t, BTF_SEQINIT);
E 2
		break;
	default:
D 5
		errno = EINVAL;
E 5
I 5
einval:		errno = EINVAL;
E 5
		return (RET_ERROR);
	}
	
D 2
	if (nrec > t->bt_nrecs && (status = t->bt_irec(t, nrec)) != RET_SUCCESS)
		return (status);
E 2
I 2
D 3
	if (nrec > t->bt_nrecs) {
E 3
I 3
	if (t->bt_nrecs == 0 || nrec > t->bt_nrecs) {
E 3
D 5
		if ((status = t->bt_irec(t, nrec)) != RET_SUCCESS)
E 5
I 5
D 8
		if (!ISSET(t, BTF_RINMEM) &&
E 8
I 8
D 9
		if (!ISSET(t, BTF_EOF | BTF_RINMEM) &&
E 9
I 9
		if (!ISSET(t, R_EOF | R_INMEM) &&
E 9
E 8
		    (status = t->bt_irec(t, nrec)) != RET_SUCCESS)
E 5
			return (status);
D 3
		if (nrec > t->bt_nrecs)
E 3
I 3
		if (t->bt_nrecs == 0 || nrec > t->bt_nrecs)
E 3
			return (RET_SPECIAL);
	}
E 2

D 2
	if ((e = __rec_search(t, nrec - 1, &exact)) == NULL)
E 2
I 2
	if ((e = __rec_search(t, nrec - 1, SEARCH)) == NULL)
E 2
		return (RET_ERROR);

D 2
	if (!exact) {
		mpool_put(t->bt_mp, e->page, 0);
		return (RET_SPECIAL);
	}

	if ((status = __rec_ret(t, e, data)) == RET_SUCCESS)
E 2
I 2
D 5
	if ((status = __rec_ret(t, e, data)) == RET_SUCCESS) {
I 3
		key->size = sizeof(recno_t);
		bcopy(&nrec, key->data, sizeof(recno_t));
E 3
E 2
		t->bt_rcursor = nrec;
I 2
		SET(t, BTF_SEQINIT);
		UNSET(t, BTF_DELCRSR);
	}
E 5
I 5
D 9
	SET(t, BTF_SEQINIT);
E 9
I 9
	SET(t, B_SEQINIT);
E 9
	t->bt_rcursor = nrec;

	status = __rec_ret(t, e, nrec, key, data);
D 11

E 5
E 2
	mpool_put(t->bt_mp, e->page, 0);
E 11
I 11
	if (ISSET(t, B_DB_LOCK))
		mpool_put(t->bt_mp, e->page, 0);
	else
		t->bt_pinned = e->page;
E 11
	return (status);
}
E 1
