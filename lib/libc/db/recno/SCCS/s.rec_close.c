h57505
s 00007/00007/00130
d D 8.3 94/02/21 15:12:45 bostic 14 13
c first pass at making DB use basic integral types (the Alpha port)
e
s 00014/00002/00123
d D 8.2 93/09/07 11:51:40 bostic 13 12
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00123
d D 8.1 93/06/04 15:25:10 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00008/00113
d D 5.11 93/05/16 15:48:15 bostic 11 10
c sync now takes a flags argument
c break modify flag into two parts, recno file modify and btree modify
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00007/00003/00114
d D 5.10 93/03/25 12:29:37 bostic 10 9
c get file descriptor close logic right
e
s 00013/00006/00104
d D 5.9 93/03/19 14:48:27 bostic 9 8
c use munmap to free up the mapped memory
c lseek wasn't testing for error correctly before truncate call
c clean up mmap and file pointer uses in recno interface
e
s 00001/00001/00109
d D 5.8 93/02/11 11:42:17 bostic 8 7
c move db.h to the end of the includes, make compat.h work better
e
s 00002/00001/00108
d D 5.7 93/01/10 13:45:27 bostic 7 6
c fix includes for portability
e
s 00008/00006/00101
d D 5.6 92/11/13 17:17:54 bostic 6 5
c check for in  memory tree
e
s 00005/00013/00102
d D 5.5 92/11/07 10:19:12 bostic 5 4
c check RDONLY bit on sync, before close
e
s 00006/00003/00109
d D 5.4 92/07/17 09:43:18 bostic 4 3
c key gets filled in by seq call, should point at something
c lseek takes an off_t, not a long
e
s 00012/00001/00100
d D 5.3 92/06/23 12:28:15 bostic 3 2
c close the underlying file descriptor
e
s 00010/00006/00091
d D 5.2 91/09/11 16:22:11 bostic 2 1
c truncate when finished writing the file
e
s 00097/00000/00000
d D 5.1 91/09/04 12:54:05 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
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
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 7
#include <sys/param.h>
E 7
I 7
#include <sys/types.h>
E 7
#include <sys/uio.h>
I 9
#include <sys/mman.h>
E 9
D 6
#include <errno.h>
E 6
I 6

E 6
D 8
#include <db.h>
E 8
D 6
#include <unistd.h>
E 6
I 6
#include <errno.h>
I 7
#include <limits.h>
E 7
E 6
#include <stdio.h>
I 6
#include <unistd.h>

I 8
#include <db.h>
E 8
E 6
D 2
#include "../btree/btree.h"
E 2
I 2
#include "recno.h"
E 2

/*
 * __REC_CLOSE -- Close a recno tree.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__rec_close(dbp)
	DB *dbp;
{
I 3
	BTREE *t;
D 14
	int rval;
E 14
I 14
	int status;
E 14

I 13
	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

E 13
E 3
D 11
	if (__rec_sync(dbp) == RET_ERROR)
E 11
I 11
	if (__rec_sync(dbp, 0) == RET_ERROR)
E 11
		return (RET_ERROR);
D 3
	return (__bt_close(dbp));
E 3
I 3

	/* Committed to closing. */
D 13
	t = dbp->internal;
D 6
	rval = t->bt_rfp == NULL ? close(t->bt_rfd) : fclose(t->bt_rfp);
E 6
I 6
D 9
	rval = ISSET(t, BTF_RINMEM) ? 0 :
	    t->bt_rfp == NULL ? close(t->bt_rfd) : fclose(t->bt_rfp);
E 9
E 6

E 13
I 9
D 14
	rval = RET_SUCCESS;
E 14
I 14
	status = RET_SUCCESS;
E 14
D 11
	if (ISSET(t, BTF_MEMMAPPED) && munmap(t->bt_smap, t->bt_msize))
E 11
I 11
	if (ISSET(t, R_MEMMAPPED) && munmap(t->bt_smap, t->bt_msize))
E 11
D 14
		rval = RET_ERROR;
E 14
I 14
		status = RET_ERROR;
E 14

D 10
	if (!ISSET(t, BTF_RINMEM) &&
	    ISSET(t, BTF_CLOSEFP) ? fclose(t->bt_rfp) : close(t->bt_rfd))
		rval = RET_ERROR;
E 10
I 10
D 11
	if (!ISSET(t, BTF_RINMEM))
		if (ISSET(t, BTF_CLOSEFP)) {
E 11
I 11
	if (!ISSET(t, R_INMEM))
		if (ISSET(t, R_CLOSEFP)) {
E 11
			if (fclose(t->bt_rfp))
D 14
				rval = RET_ERROR;
E 14
I 14
				status = RET_ERROR;
E 14
		} else
			if (close(t->bt_rfd))
D 14
				rval = RET_ERROR;
E 14
I 14
				status = RET_ERROR;
E 14
E 10

E 9
	if (__bt_close(dbp) == RET_ERROR)
D 9
		return (RET_ERROR);
E 9
I 9
D 14
		rval = RET_ERROR;
E 14
I 14
		status = RET_ERROR;
E 14
E 9

D 9
	return (rval ? RET_ERROR : RET_SUCCESS);
E 9
I 9
D 14
	return (rval);
E 14
I 14
	return (status);
E 14
E 9
E 3
}

/*
 * __REC_SYNC -- sync the recno tree to disk.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *
 * Returns:
 *	RET_SUCCESS, RET_ERROR.
D 5
 *
 * XXX
 * Currently don't handle a key marked for deletion when the tree is synced.
 * Should copy the page and write it out instead of the real page.
E 5
 */
int
D 11
__rec_sync(dbp)
E 11
I 11
__rec_sync(dbp, flags)
E 11
	const DB *dbp;
I 11
	u_int flags;
E 11
{
	struct iovec iov[2];
	BTREE *t;
	DBT data, key;
I 2
	off_t off;
E 2
D 4
	recno_t scursor;
E 4
I 4
	recno_t scursor, trec;
E 4
	int status;

	t = dbp->internal;
I 13

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}
E 13

D 5
	if (ISSET(t, BTF_INMEM) || NOTSET(t, BTF_MODIFIED))
E 5
I 5
D 6
	if (ISSET(t, BTF_INMEM) || ISSET(t, BTF_RDONLY) ||
	    NOTSET(t, BTF_MODIFIED))
E 6
I 6
D 11
	if (ISSET(t, BTF_RDONLY | BTF_RINMEM) || !ISSET(t, BTF_MODIFIED))
E 11
I 11
	if (flags == R_RECNOSYNC)
		return (__bt_sync(dbp, 0));

	if (ISSET(t, R_RDONLY | R_INMEM) || !ISSET(t, R_MODIFIED))
E 11
E 6
E 5
		return (RET_SUCCESS);

D 5
	if (ISSET(t, BTF_RDONLY)) {
		errno = EPERM;
		return (RET_ERROR);
	}

	/* Suck any remaining records into the tree. */
E 5
I 5
	/* Read any remaining records into the tree. */
E 5
D 9
	if (t->bt_irec(t, MAX_REC_NUMBER) == RET_ERROR)
E 9
I 9
D 11
	if (!ISSET(t, BTF_EOF) && t->bt_irec(t, MAX_REC_NUMBER) == RET_ERROR)
E 11
I 11
	if (!ISSET(t, R_EOF) && t->bt_irec(t, MAX_REC_NUMBER) == RET_ERROR)
E 11
E 9
		return (RET_ERROR);

	/* Rewind the file descriptor. */
D 4
	if (lseek(t->bt_rfd, 0L, SEEK_SET) != 0L)
E 4
I 4
D 5
	if (lseek(t->bt_rfd, (off_t)0, SEEK_SET) != 0L)
E 5
I 5
	if (lseek(t->bt_rfd, (off_t)0, SEEK_SET) != 0)
E 5
E 4
		return (RET_ERROR);

	iov[1].iov_base = "\n";
	iov[1].iov_len = 1;
	scursor = t->bt_rcursor;

I 4
	key.size = sizeof(recno_t);
	key.data = &trec;

E 4
	status = (dbp->seq)(dbp, &key, &data, R_FIRST);
        while (status == RET_SUCCESS) {
		iov[0].iov_base = data.data;
		iov[0].iov_len = data.size;
		if (writev(t->bt_rfd, iov, 2) != data.size + 1)
			return (RET_ERROR);
                status = (dbp->seq)(dbp, &key, &data, R_NEXT);
        }
	t->bt_rcursor = scursor;
D 2
	if (status != RET_ERROR) {
		UNSET(t, BTF_MODIFIED);
		return (RET_SUCCESS);
	}
	return (RET_ERROR);
E 2
I 2
	if (status == RET_ERROR)
		return (RET_ERROR);
D 4
	if ((off = lseek(t->bt_rfd, 0L, SEEK_CUR)) == -1)
E 4
I 4
D 5
	if ((off = lseek(t->bt_rfd, (off_t)0, SEEK_CUR)) == -1)
E 5
I 5
D 9
	if ((off = lseek(t->bt_rfd, (off_t)0, SEEK_CUR)) != 0)
E 9
I 9
	if ((off = lseek(t->bt_rfd, (off_t)0, SEEK_CUR)) == -1)
E 9
E 5
E 4
		return (RET_ERROR);
	if (ftruncate(t->bt_rfd, off))
		return (RET_ERROR);
D 6
	UNSET(t, BTF_MODIFIED);
E 6
I 6
D 11
	CLR(t, BTF_MODIFIED);
E 11
I 11
	CLR(t, R_MODIFIED);
E 11
E 6
	return (RET_SUCCESS);
E 2
}
E 1
