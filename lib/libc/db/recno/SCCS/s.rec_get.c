h10778
s 00008/00008/00264
d D 8.4 94/03/01 07:55:52 bostic 14 13
c don't assign to the data structure until after the realloc
c From: "Chris G. Demetriou" <cgd@postgres.Berkeley.EDU>
e
s 00006/00004/00266
d D 8.3 94/02/21 17:42:48 bostic 13 12
c cast alloc's to shut SunOS up
e
s 00013/00002/00257
d D 8.2 93/09/07 11:51:35 bostic 12 11
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00257
d D 8.1 93/06/04 15:25:18 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00254
d D 5.10 93/05/16 15:44:55 bostic 10 9
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00002/00000/00257
d D 5.9 93/05/07 11:40:45 bostic 9 8
c avoid zero-length record at EOF
e
s 00013/00022/00244
d D 5.8 93/03/19 14:47:38 bostic 8 7
c add BTF_EOF flag to test instead of bt_reof int
c clean up mmap and file pointer uses in recno interface
e
s 00002/00002/00264
d D 5.7 93/02/20 15:26:32 bostic 7 6
c sz is not the total size of the buffer, it's the remaining room
e
s 00001/00001/00265
d D 5.6 93/02/14 17:39:04 bostic 6 5
c index_t -> indx_t
e
s 00001/00001/00265
d D 5.5 93/02/11 11:42:19 bostic 5 4
c move db.h to the end of the includes, make compat.h work better
e
s 00008/00005/00258
d D 5.4 92/11/13 17:17:06 bostic 4 3
c check for in memory recno tree; __rec_ret takes new key arguments
c bug, wasn't setting len variable in __rec_fpipe
e
s 00011/00020/00252
d D 5.3 92/06/23 12:27:49 bostic 3 2
c exact is meaningless for recno; make eof flag part of each BT struct
e
s 00005/00004/00267
d D 5.2 91/09/11 16:21:33 bostic 2 1
c take const for key argument; specify SEARCH to __rec_search
e
s 00271/00000/00000
d D 5.1 91/09/04 12:54:06 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
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
D 4
#include <unistd.h>
E 4
I 4
#include <errno.h>
E 4
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 4
#include <unistd.h>

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

/*
 * __REC_GET -- Get a record from the btree.
 *
 * Parameters:
 *	dbp:	pointer to access method
 *	key:	key to find
 *	data:	data to return
 *	flag:	currently unused
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS and RET_SPECIAL if the key not found.
 */
int
__rec_get(dbp, key, data, flags)
	const DB *dbp;
D 2
	DBT *key, *data;
E 2
I 2
	const DBT *key;
	DBT *data;
E 2
	u_int flags;
{
	BTREE *t;
	EPG *e;
	recno_t nrec;
D 3
	int exact, status;
E 3
I 3
	int status;
E 3

I 12
	t = dbp->internal;

	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	/* Get currently doesn't take any flags, and keys of 0 are illegal. */
E 12
	if (flags || (nrec = *(recno_t *)key->data) == 0) {
		errno = EINVAL;
		return (RET_ERROR);
	}

	/*
	 * If we haven't seen this record yet, try to find it in the
	 * original file.
	 */
D 12
	t = dbp->internal;
E 12
D 3
	if (nrec > t->bt_nrecs && 
	   (status = t->bt_irec(t, nrec)) != RET_SUCCESS)
E 3
I 3
D 4
	if (nrec > t->bt_nrecs &&
	    (status = t->bt_irec(t, nrec)) != RET_SUCCESS)
E 4
I 4
D 8
	if (nrec > t->bt_nrecs && (ISSET(t, BTF_RINMEM) ||
	    (status = t->bt_irec(t, nrec)) != RET_SUCCESS))
E 8
I 8
	if (nrec > t->bt_nrecs) {
D 10
		if (ISSET(t, BTF_EOF | BTF_RINMEM))
E 10
I 10
		if (ISSET(t, R_EOF | R_INMEM))
E 10
			return (RET_SPECIAL);
		if ((status = t->bt_irec(t, nrec)) != RET_SUCCESS)
E 8
E 4
E 3
			return (status);
I 8
	}
E 8

	--nrec;
D 2
	if ((e = __rec_search(t, nrec, &exact)) == NULL)
E 2
I 2
	if ((e = __rec_search(t, nrec, SEARCH)) == NULL)
E 2
		return (RET_ERROR);

D 3
	if (!exact) {
		mpool_put(t->bt_mp, e->page, 0);
		return (RET_SPECIAL);
	}

E 3
D 4
	status = __rec_ret(t, e, data);
E 4
I 4
	status = __rec_ret(t, e, 0, NULL, data);
E 4
D 12
	mpool_put(t->bt_mp, e->page, 0);
E 12
I 12
	if (ISSET(t, B_DB_LOCK))
		mpool_put(t->bt_mp, e->page, 0);
	else
		t->bt_pinned = e->page;
E 12
	return (status);
}

/*
 * __REC_FPIPE -- Get fixed length records from a pipe.
 *
 * Parameters:
 *	t:	tree
 *	cnt:	records to read
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__rec_fpipe(t, top)
	BTREE *t;
	recno_t top;
{
D 3
	static int eof;
E 3
	DBT data;
	recno_t nrec;
	size_t len;
	int ch;
	char *p;

D 3
	if (eof)
E 3
I 3
D 8
	if (t->bt_reof)
E 3
		return (RET_SPECIAL);

E 8
D 14
	data.data = t->bt_dbuf;
	data.size = t->bt_reclen;

E 14
	if (t->bt_dbufsz < t->bt_reclen) {
D 13
		if ((t->bt_dbuf = realloc(t->bt_dbuf, t->bt_reclen)) == NULL)
E 13
I 13
		if ((t->bt_dbuf =
		    (char *)realloc(t->bt_dbuf, t->bt_reclen)) == NULL)
E 13
			return (RET_ERROR);
		t->bt_dbufsz = t->bt_reclen;
	}
I 14
	data.data = t->bt_dbuf;
	data.size = t->bt_reclen;

E 14
	for (nrec = t->bt_nrecs; nrec < top; ++nrec) {
I 4
		len = t->bt_reclen;
E 4
		for (p = t->bt_dbuf;; *p++ = ch)
			if ((ch = getc(t->bt_rfp)) == EOF || !len--) {
				if (__rec_iput(t, nrec, &data, 0)
				    != RET_SUCCESS)
					return (RET_ERROR);
				break;
			}
		if (ch == EOF)
			break;
	}
	if (nrec < top) {
D 3
		eof = 1;
E 3
I 3
D 8
		t->bt_reof = 1;
E 8
I 8
D 10
		SET(t, BTF_EOF);
E 10
I 10
		SET(t, R_EOF);
E 10
E 8
E 3
		return (RET_SPECIAL);
	}
	return (RET_SUCCESS);
}

/*
 * __REC_VPIPE -- Get variable length records from a pipe.
 *
 * Parameters:
 *	t:	tree
 *	cnt:	records to read
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__rec_vpipe(t, top)
	BTREE *t;
	recno_t top;
{
D 3
	static int eof;
E 3
	DBT data;
	recno_t nrec;
D 6
	index_t len;
E 6
I 6
	indx_t len;
E 6
	size_t sz;
	int bval, ch;
	char *p;

D 3
	if (eof)
E 3
I 3
D 8
	if (t->bt_reof)
E 3
		return (RET_SPECIAL);

E 8
	bval = t->bt_bval;
	for (nrec = t->bt_nrecs; nrec < top; ++nrec) {
		for (p = t->bt_dbuf, sz = t->bt_dbufsz;; *p++ = ch, --sz) {
			if ((ch = getc(t->bt_rfp)) == EOF || ch == bval) {
				data.data = t->bt_dbuf;
				data.size = p - t->bt_dbuf;
I 9
				if (ch == EOF && data.size == 0)
					break;
E 9
				if (__rec_iput(t, nrec, &data, 0)
				    != RET_SUCCESS)
					return (RET_ERROR);
				break;
			}
			if (sz == 0) {
				len = p - t->bt_dbuf;
D 7
				sz = t->bt_dbufsz += 256;
E 7
I 7
				t->bt_dbufsz += (sz = 256);
E 7
D 13
				if ((t->bt_dbuf =
D 7
				    realloc(t->bt_dbuf, sz)) == NULL)
E 7
I 7
				    realloc(t->bt_dbuf, t->bt_dbufsz)) == NULL)
E 13
I 13
				if ((t->bt_dbuf = (char *)realloc(t->bt_dbuf,
				    t->bt_dbufsz)) == NULL)
E 13
E 7
					return (RET_ERROR);
				p = t->bt_dbuf + len;
			}
		}
		if (ch == EOF)
			break;
	}
	if (nrec < top) {
D 3
		eof = 1;
E 3
I 3
D 8
		t->bt_reof = 1;
E 8
I 8
D 10
		SET(t, BTF_EOF);
E 10
I 10
		SET(t, R_EOF);
E 10
E 8
E 3
		return (RET_SPECIAL);
	}
	return (RET_SUCCESS);
}

/*
 * __REC_FMAP -- Get fixed length records from a file.
 *
 * Parameters:
 *	t:	tree
 *	cnt:	records to read
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__rec_fmap(t, top)
	BTREE *t;
	recno_t top;
{
D 3
	static int eof;
E 3
	DBT data;
	recno_t nrec;
	caddr_t sp, ep;
	size_t len;
	char *p;

D 3
	if (eof)
E 3
I 3
D 8
	if (t->bt_reof)
E 3
		return (RET_SPECIAL);

	sp = t->bt_smap;
E 8
I 8
D 14
	sp = t->bt_cmap;
E 8
	ep = t->bt_emap;
	data.data = t->bt_dbuf;
	data.size = t->bt_reclen;

E 14
	if (t->bt_dbufsz < t->bt_reclen) {
D 13
		if ((t->bt_dbuf = realloc(t->bt_dbuf, t->bt_reclen)) == NULL)
E 13
I 13
		if ((t->bt_dbuf =
		    (char *)realloc(t->bt_dbuf, t->bt_reclen)) == NULL)
E 13
			return (RET_ERROR);
		t->bt_dbufsz = t->bt_reclen;
	}
I 14
	data.data = t->bt_dbuf;
	data.size = t->bt_reclen;

	sp = t->bt_cmap;
	ep = t->bt_emap;
E 14
	for (nrec = t->bt_nrecs; nrec < top; ++nrec) {
		if (sp >= ep) {
D 3
			eof = 1;
E 3
I 3
D 8
			t->bt_reof = 1;
E 8
I 8
D 10
			SET(t, BTF_EOF);
E 10
I 10
			SET(t, R_EOF);
E 10
E 8
E 3
			return (RET_SPECIAL);
		}
		len = t->bt_reclen;
		for (p = t->bt_dbuf; sp < ep && len--; *p++ = *sp++);
		memset(p, t->bt_bval, len);
		if (__rec_iput(t, nrec, &data, 0) != RET_SUCCESS)
			return (RET_ERROR);
	}
D 8
	t->bt_smap = sp;
E 8
I 8
	t->bt_cmap = sp;
E 8
	return (RET_SUCCESS);
}

/*
 * __REC_VMAP -- Get variable length records from a file.
 *
 * Parameters:
 *	t:	tree
 *	cnt:	records to read
 *
 * Returns:
 *	RET_ERROR, RET_SUCCESS
 */
int
__rec_vmap(t, top)
	BTREE *t;
	recno_t top;
{
D 3
	static int eof;
E 3
	DBT data;
D 2
	recno_t nrec;
E 2
	caddr_t sp, ep;
I 2
	recno_t nrec;
E 2
	int bval;

D 3
	if (eof)
E 3
I 3
D 8
	if (t->bt_reof)
E 3
		return (RET_SPECIAL);

	sp = t->bt_smap;
E 8
I 8
	sp = t->bt_cmap;
E 8
	ep = t->bt_emap;
	bval = t->bt_bval;

	for (nrec = t->bt_nrecs; nrec < top; ++nrec) {
		if (sp >= ep) {
D 3
			eof = 1;
E 3
I 3
D 8
			t->bt_reof = 1;
E 8
I 8
D 10
			SET(t, BTF_EOF);
E 10
I 10
			SET(t, R_EOF);
E 10
E 8
E 3
			return (RET_SPECIAL);
		}
		for (data.data = sp; sp < ep && *sp != bval; ++sp);
		data.size = sp - (caddr_t)data.data;
		if (__rec_iput(t, nrec, &data, 0) != RET_SUCCESS)
			return (RET_ERROR);
		++sp;
	}
D 8
	t->bt_smap = sp;
E 8
I 8
	t->bt_cmap = sp;
E 8
	return (RET_SUCCESS);
}
E 1
