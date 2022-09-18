h05192
s 00001/00001/00177
d D 8.3 94/02/21 17:43:15 bostic 16 15
c cast alloc's to shut SunOS up
e
s 00015/00002/00163
d D 8.2 93/09/07 11:51:02 bostic 15 14
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00163
d D 8.1 93/06/04 15:20:06 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00008/00151
d D 5.12 93/05/16 15:43:16 bostic 13 12
c sync now takes a flags argument
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00003/00013/00156
d D 5.11 93/05/01 15:34:34 bostic 12 11
c lint (bug); don't swap meta information when writing the file back,
c the __bt_pgout routine should handle this for us
e
s 00003/00003/00166
d D 5.10 93/02/16 12:33:41 bostic 11 10
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00001/00001/00168
d D 5.9 93/02/11 11:39:18 bostic 10 9
c move db.h to the end of the includes, make compat.h work better
e
s 00004/00001/00165
d D 5.8 93/01/22 11:51:28 bostic 9 7
c have to push the dirty page back to mpool, before the sync, so that it
c gets written to disk.  Then, re-pin the page, and modify it.  The MPOOL_DIRTY
c bit may not be "correct" for the second mpool_put, but since the BTF_DELCRSR
c bit is set, it shouldn't matter
e
s 00003/00001/00165
d R 5.8 93/01/22 11:39:19 bostic 8 7
c have to push the dirty page out, or won't get sync'd
e
s 00011/00010/00155
d D 5.7 92/11/13 16:08:08 bostic 7 6
c reorder malloc/mpool_get for simplicity; save off error from delete
e
s 00002/00001/00163
d D 5.6 92/11/07 10:18:54 bostic 6 5
c check MODIFIED bit on sync, before close
e
s 00001/00001/00163
d D 5.5 92/10/09 16:25:58 bostic 5 4
c implement free page reuse
e
s 00001/00001/00163
d D 5.4 91/12/16 14:03:28 bostic 4 3
c don't bother with the macros, performance isn't an issue here
e
s 00001/00001/00163
d D 5.3 91/12/09 15:16:48 bostic 3 2
c htonl -> HTONL
e
s 00029/00015/00135
d D 5.2 91/09/12 11:04:21 bostic 2 1
c make close of RDONLY succeed; fix sync call to handle a cursor marked
c for deletion
e
s 00150/00000/00000
d D 5.1 91/09/04 12:50:44 bostic 1 0
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
 * This code is derived from software contributed to Berkeley by
 * Mike Olson.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
D 7
#include <errno.h>
E 7
I 7

E 7
D 10
#include <db.h>
E 10
D 7
#include <unistd.h>
E 7
I 7
#include <errno.h>
E 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 7
#include <unistd.h>

I 10
#include <db.h>
E 10
E 7
#include "btree.h"

static int bt_meta __P((BTREE *));

/*
 * BT_CLOSE -- Close a btree.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__bt_close(dbp)
	DB *dbp;
{
	BTREE *t;
	int fd;

	t = dbp->internal;

I 15
	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

E 15
	/*
	 * Delete any already deleted record that we've been saving
	 * because the cursor pointed to it.
	 */
D 13
	if (ISSET(t, BTF_DELCRSR) && __bt_crsrdel(t, &t->bt_bcursor))
E 13
I 13
	if (ISSET(t, B_DELCRSR) && __bt_crsrdel(t, &t->bt_bcursor))
E 13
		return (RET_ERROR);

D 13
	if (__bt_sync(dbp) == RET_ERROR)
E 13
I 13
	if (__bt_sync(dbp, 0) == RET_ERROR)
E 13
		return (RET_ERROR);

	if (mpool_close(t->bt_mp) == RET_ERROR)
		return (RET_ERROR);

	if (t->bt_stack)
		free(t->bt_stack);
	if (t->bt_kbuf)
		free(t->bt_kbuf);
	if (t->bt_dbuf)
		free(t->bt_dbuf);

	fd = t->bt_fd;
	free(t);
	free(dbp);
	return (close(fd) ? RET_ERROR : RET_SUCCESS);
}

/*
 * BT_SYNC -- sync the btree to disk.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *
 * Returns:
 *	RET_SUCCESS, RET_ERROR.
D 2
 *
 * XXX
 * Currently don't handle a key marked for deletion when the tree is synced.
 * Should copy the page and write it out instead of the real page.
E 2
 */
int
D 13
__bt_sync(dbp)
E 13
I 13
__bt_sync(dbp, flags)
E 13
	const DB *dbp;
I 13
	u_int flags;
E 13
{
	BTREE *t;
	int status;
I 2
	PAGE *h;
	void *p;
E 2

I 15
	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	/* Sync doesn't currently take any flags. */
E 15
I 13
	if (flags != 0) {
		errno = EINVAL;
		return (RET_ERROR);
	}
D 15

E 13
	t = dbp->internal;
E 15

D 2
	if (ISSET(t, BTF_INMEM))
E 2
I 2
D 6
	if (ISSET(t, BTF_INMEM) || ISSET(t, BTF_RDONLY))
E 6
I 6
D 7
	if (ISSET(t, BTF_INMEM) || ISSET(t, BTF_RDONLY) ||
	    NOTSET(t, BTF_MODIFIED))
E 7
I 7
D 13
	if (ISSET(t, BTF_INMEM | BTF_RDONLY) || !ISSET(t, BTF_MODIFIED))
E 13
I 13
	if (ISSET(t, B_INMEM | B_RDONLY) || !ISSET(t, B_MODIFIED))
E 13
E 7
E 6
E 2
		return (RET_SUCCESS);

D 2
	if (ISSET(t, BTF_RDONLY)) {
		errno = EPERM;
		return (RET_ERROR);
	}

E 2
D 13
	if (ISSET(t, BTF_METADIRTY) && bt_meta(t) == RET_ERROR)
E 13
I 13
	if (ISSET(t, B_METADIRTY) && bt_meta(t) == RET_ERROR)
E 13
		return (RET_ERROR);

D 2
	if ((status = mpool_sync(t->bt_mp)) == RET_SUCCESS) {
E 2
I 2
	/*
	 * Nastiness.  If the cursor has been marked for deletion, but not
	 * actually deleted, we have to make a copy of the page, delete the
	 * key/data item, sync the file, and then restore the original page
	 * contents.
	 */
D 13
	if (ISSET(t, BTF_DELCRSR)) {
E 13
I 13
	if (ISSET(t, B_DELCRSR)) {
E 13
I 7
D 16
		if ((p = malloc(t->bt_psize)) == NULL)
E 16
I 16
		if ((p = (void *)malloc(t->bt_psize)) == NULL)
E 16
			return (RET_ERROR);
E 7
		if ((h = mpool_get(t->bt_mp, t->bt_bcursor.pgno, 0)) == NULL)
			return (RET_ERROR);
D 7
		if ((p = malloc(t->bt_psize)) == NULL) {
			mpool_put(t->bt_mp, h, 0);
			return (RET_ERROR);
		}
E 7
D 11
		bcopy(h, p, t->bt_psize);
E 11
I 11
		memmove(p, h, t->bt_psize);
E 11
D 7
		if (__bt_dleaf(t, h, t->bt_bcursor.index) == RET_ERROR)
E 7
I 7
D 12
		if (status =
		    __bt_dleaf(t, h, t->bt_bcursor.index) == RET_ERROR)
E 12
I 12
		if ((status =
		    __bt_dleaf(t, h, t->bt_bcursor.index)) == RET_ERROR)
E 12
E 7
			goto ecrsr;
I 9
		mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 9
	}
		
	if ((status = mpool_sync(t->bt_mp)) == RET_SUCCESS)
E 2
D 7
		UNSET(t, BTF_MODIFIED);
E 7
I 7
D 13
		CLR(t, BTF_MODIFIED);
E 13
I 13
		CLR(t, B_MODIFIED);
E 13

E 7
D 2
		return (RET_SUCCESS);
E 2
I 2
D 13
ecrsr:	if (ISSET(t, BTF_DELCRSR)) {
E 13
I 13
ecrsr:	if (ISSET(t, B_DELCRSR)) {
E 13
I 9
		if ((h = mpool_get(t->bt_mp, t->bt_bcursor.pgno, 0)) == NULL)
			return (RET_ERROR);
E 9
D 11
		bcopy(p, h, t->bt_psize);
E 11
I 11
		memmove(h, p, t->bt_psize);
E 11
		free(p);
D 9
		mpool_put(t->bt_mp, h, 0);
E 9
I 9
		mpool_put(t->bt_mp, h, MPOOL_DIRTY);
E 9
E 2
	}
	return (status);
}

/*
 * BT_META -- write the tree meta data to disk.
 *
 * Parameters:
 *	t:	tree
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
static int
bt_meta(t)
	BTREE *t;
{
	BTMETA m;
	void *p;

	if ((p = mpool_get(t->bt_mp, P_META, 0)) == NULL)
		return (RET_ERROR);

D 2
	/* Fill in meta structure -- lorder MUST be host-independent. */
E 2
I 2
D 12
	/* Fill in metadata -- lorder is host-independent. */
E 12
I 12
	/* Fill in metadata. */
E 12
E 2
	m.m_magic = BTREEMAGIC;
	m.m_version = BTREEVERSION;
	m.m_psize = t->bt_psize;
D 2
	m.m_free = 0;		/* XXX */
E 2
I 2
D 5
	m.m_free = 0;           		/* XXX */
E 5
I 5
	m.m_free = t->bt_free;
E 5
E 2
	m.m_nrecs = t->bt_nrecs;
	m.m_flags = t->bt_flags & SAVEMETA;
D 2
	m.m_lorder = (u_long)htonl((long)t->bt_lorder);
E 2
I 2
D 3
	m.m_lorder = htonl((long)t->bt_lorder);
E 3
I 3
D 4
	m.m_lorder = HTONL((long)t->bt_lorder);
E 4
I 4
D 12
	m.m_lorder = htonl((u_long)t->bt_lorder);
E 4
E 3
E 2

	if (t->bt_lorder != BYTE_ORDER) {
		BLSWAP(m.m_magic);
		BLSWAP(m.m_version);
		BLSWAP(m.m_psize);
		BLSWAP(m.m_free);
		BLSWAP(m.m_nrecs);
		BLSWAP(m.m_flags);
	}
E 12

D 11
	bcopy(&m, p, sizeof(BTMETA));
E 11
I 11
	memmove(p, &m, sizeof(BTMETA));
E 11
	mpool_put(t->bt_mp, p, MPOOL_DIRTY);
	return (RET_SUCCESS);
}
E 1
