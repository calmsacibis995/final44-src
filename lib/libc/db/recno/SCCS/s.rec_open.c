h53736
s 00006/00004/00198
d D 8.6 94/02/22 12:29:32 bostic 27 26
c update the comment
e
s 00000/00001/00202
d D 8.5 94/02/21 15:12:47 bostic 26 25
c first pass at making DB use basic integral types (the Alpha port)
e
s 00001/00000/00202
d D 8.4 93/09/07 12:02:14 bostic 25 24
c lint
e
s 00011/00004/00191
d D 8.3 93/09/07 11:52:33 bostic 24 23
c add DB_ flags to __rec_open
c if DB_LOCK not set, pin page across calls and don't copy key/data pair
e
s 00002/00002/00193
d D 8.2 93/08/16 16:20:29 bostic 23 22
c SunOS 4.1.3 and SVR4 require either MAP_PRIVATE or MAP_SHARED
e
s 00002/00002/00193
d D 8.1 93/06/04 15:25:26 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00015/00188
d D 5.21 93/05/30 12:49:54 bostic 21 20
c give up on the EFBIG test
e
s 00016/00000/00187
d D 5.20 93/05/24 09:48:53 bostic 20 19
c add __rec_fd, to return a file descriptor
e
s 00001/00001/00186
d D 5.19 93/05/16 16:16:04 bostic 19 18
c pass psize down to the btree routines
e
s 00013/00012/00174
d D 5.18 93/05/16 15:47:23 bostic 18 17
c underlying btree is always O_RDWR, recno may be O_RDONLY
c break BTF flags up into btree/recno (B_, R_) categories
e
s 00016/00003/00170
d D 5.17 93/05/06 15:29:59 bostic 17 16
c another shot at fixing the SIZE_T_MAX test
e
s 00008/00007/00165
d D 5.16 93/03/23 18:33:38 ralph 16 15
c initialize uninitialized fields in btopeninfo. minor speedup, don't
c check for cases which are the same as default:
e
s 00036/00020/00136
d D 5.15 93/03/19 14:50:22 bostic 15 14
c guarantee that bt_rfd gets set; pipes are read-only (check for einval)
c don't read the file if the size is 0; return the right errno
c clean up mmap and file pointer uses in recno interface
e
s 00001/00001/00155
d D 5.14 93/02/28 14:47:22 bostic 14 13
c cast the SIZE_T_MAX, so compilers don't get upset
e
s 00001/00001/00155
d D 5.13 93/02/11 11:42:20 bostic 13 12
c move db.h to the end of the includes, make compat.h work better
e
s 00002/00002/00154
d D 5.12 92/12/19 15:24:15 bostic 12 11
c read slowly if can't mmap the file
e
s 00001/00000/00155
d D 5.11 92/12/04 20:07:35 bostic 11 10
c initialize cursor so that first R_CURSORLOG works
e
s 00051/00040/00104
d D 5.10 92/11/13 17:29:19 bostic 10 9
c add in-memory versions of recno trees, lint fixes
e
s 00015/00009/00129
d D 5.9 92/11/07 10:19:41 bostic 9 8
c only permit O_RDONLY or O_RDWR, not O_WRONLY
e
s 00001/00001/00137
d D 5.8 92/07/17 09:42:25 bostic 8 7
c lseek takes an off_t, not a long
e
s 00008/00009/00130
d D 5.7 92/07/16 13:41:55 bostic 7 6
c don't test rec_len field if flag bit not set
e
s 00001/00001/00138
d D 5.6 92/07/15 16:32:20 bostic 6 5
c mmap returns -1 on error
e
s 00002/00001/00137
d D 5.5 92/06/24 09:36:22 bostic 5 4
c use constant SIZE_T_MAX instead of knowing what size it is
e
s 00003/00003/00135
d D 5.4 92/06/23 16:51:50 bostic 4 3
c second arg to mmap is a size_t, MAP_FILE disappears
e
s 00011/00005/00127
d D 5.3 92/06/23 12:37:47 bostic 3 2
c make eof flag part of each BT struct; test for sb.st_size larger than
c the maximum int; set bt_rfp to NULL if not set, used as a flag in close
e
s 00012/00007/00120
d D 5.2 91/09/11 16:26:35 bostic 2 1
c check user flags; minor error changes
e
s 00127/00000/00000
d D 5.1 91/09/04 12:54:07 bostic 1 0
c Rev #2.  Redo the btree code add recno's and checkpoint
e
u
U
t
T
I 1
/*-
D 22
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
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
#include <sys/mman.h>
#include <sys/stat.h>
I 5

E 5
D 10
#include <fcntl.h>
E 10
I 10
D 13
#include <db.h>
E 13
E 10
#include <errno.h>
I 10
#include <fcntl.h>
E 10
#include <limits.h>
D 10
#include <db.h>
#include <unistd.h>
#include <stdio.h>
E 10
#include <stddef.h>
I 10
#include <stdio.h>
#include <unistd.h>

I 25
D 26
#define	__DBINTERFACE_PRIVATE
E 26
E 25
I 13
#include <db.h>
E 13
E 10
D 2
#include "../btree/btree.h"
E 2
I 2
#include "recno.h"
E 2

DB *
D 24
__rec_open(fname, flags, mode, openinfo)
E 24
I 24
__rec_open(fname, flags, mode, openinfo, dflags)
E 24
	const char *fname;
D 24
	int flags, mode;
E 24
I 24
	int flags, mode, dflags;
E 24
	const RECNOINFO *openinfo;
{
	BTREE *t;
	BTREEINFO btopeninfo;
	DB *dbp;
	PAGE *h;
	struct stat sb;
D 15
	int rfd;
E 15
I 15
	int rfd, sverrno;
E 15

	/* Open the user's file -- if this fails, we're done. */
D 10
	if ((rfd = open(fname, flags, mode)) < 0)
E 10
I 10
	if (fname != NULL && (rfd = open(fname, flags, mode)) < 0)
E 10
		return (NULL);

	/* Create a btree in memory (backed by disk). */
I 10
	dbp = NULL;
E 10
	if (openinfo) {
I 2
D 9
		if (openinfo->flags & ~(R_FIXEDLEN|R_NOKEY|R_SNAPSHOT)) {
			errno = EINVAL;
			goto err;
		}
E 9
I 9
D 10
		if (openinfo->flags & ~(R_FIXEDLEN|R_NOKEY|R_SNAPSHOT))
E 10
I 10
		if (openinfo->flags & ~(R_FIXEDLEN | R_NOKEY | R_SNAPSHOT))
E 10
			goto einval;
E 9
E 2
		btopeninfo.flags = 0;
		btopeninfo.cachesize = openinfo->cachesize;
I 16
		btopeninfo.maxkeypage = 0;
		btopeninfo.minkeypage = 0;
E 16
D 19
		btopeninfo.psize = 0;
E 19
I 19
		btopeninfo.psize = openinfo->psize;
E 19
		btopeninfo.compare = NULL;
I 16
		btopeninfo.prefix = NULL;
E 16
		btopeninfo.lorder = openinfo->lorder;
D 18
		dbp = __bt_open(NULL, O_RDWR, S_IRUSR | S_IWUSR, &btopeninfo);
E 18
I 18
		dbp = __bt_open(openinfo->bfname,
D 24
		    O_RDWR, S_IRUSR | S_IWUSR, &btopeninfo);
E 24
I 24
		    O_RDWR, S_IRUSR | S_IWUSR, &btopeninfo, dflags);
E 24
E 18
	} else
D 24
		dbp = __bt_open(NULL, O_RDWR, S_IRUSR | S_IWUSR, NULL);
E 24
I 24
		dbp = __bt_open(NULL, O_RDWR, S_IRUSR | S_IWUSR, NULL, dflags);
E 24
D 2
	if (dbp == NULL) {
		(void)close(rfd);
		return (NULL);
	}
E 2
I 2
	if (dbp == NULL)
		goto err;
E 2

	/*
	 * Some fields in the tree structure are recno specific.  Fill them
D 2
	 * in and make the btree structure look like a recno structure.
E 2
I 2
	 * in and make the btree structure look like a recno structure.  We
	 * don't change the bt_ovflsize value, it's close enough and slightly
	 * bigger.
E 2
	 */
	t = dbp->internal;
	if (openinfo) {
D 7
		if (openinfo->flags & R_FIXEDLEN)
E 7
I 7
		if (openinfo->flags & R_FIXEDLEN) {
E 7
D 10
			t->bt_flags |= BTF_FIXEDLEN;
E 10
I 10
D 18
			SET(t, BTF_FIXEDLEN);
E 18
I 18
			SET(t, R_FIXLEN);
E 18
E 10
D 7

		t->bt_reclen = openinfo->reclen;
		if (t->bt_reclen == 0) {
			errno = EINVAL;
			goto err;
E 7
I 7
			t->bt_reclen = openinfo->reclen;
D 9
			if (t->bt_reclen == 0) {
				errno = EINVAL;
				goto err;
			}
E 9
I 9
			if (t->bt_reclen == 0)
				goto einval;
E 9
E 7
		}
D 7

E 7
		t->bt_bval = openinfo->bval;
	} else
		t->bt_bval = '\n';

D 10
	t->bt_flags = BTF_RECNO;
I 3
	t->bt_reof = 0;
E 10
I 10
D 18
	SET(t, BTF_RECNO);
E 18
I 18
	SET(t, R_RECNO);
E 18
D 15
	if (fname == NULL) {
		SET(t, BTF_RINMEM);
		t->bt_reof = 1;
	} else
		t->bt_reof = 0;
E 15
I 15
	if (fname == NULL)
D 18
		SET(t, BTF_EOF | BTF_RINMEM);
E 18
I 18
		SET(t, R_EOF | R_INMEM);
E 18
	else
		t->bt_rfd = rfd;
E 15
I 11
	t->bt_rcursor = 0;
E 11
E 10
E 3

D 27
	/*
D 3
 	 * In 4.4BSD stat(2) returns true for ISSOCK on pipes.  Until then,
	 * this is fairly close.  Pipes are read-only.
 	 */
E 3
I 3
	 * In 4.4BSD stat(2) returns true for ISSOCK on pipes.  Until
	 * then, this is fairly close.  Pipes are read-only.
	 */
E 27
E 3
D 8
	if (lseek(rfd, 0L, SEEK_CUR) == -1 && errno == ESPIPE) {
E 8
I 8
D 10
	if (lseek(rfd, (off_t)0, SEEK_CUR) == -1 && errno == ESPIPE) {
E 8
		SET(t, BTF_RDONLY);
		if ((t->bt_rfp = fdopen(rfd, "r")) == NULL)
			goto err;
		t->bt_irec = ISSET(t, BTF_FIXEDLEN) ? __rec_fpipe : __rec_vpipe;
	} else {
		if (fstat(rfd, &sb))
			goto err;
D 9
		if (!(flags & (O_RDWR | O_WRONLY)))
E 9
I 9
		switch(flags & O_ACCMODE) {
		case O_RDONLY:
E 10
I 10
D 16
	if (fname != NULL)
E 16
I 16
	if (fname != NULL) {
I 27
		/*
		 * In 4.4BSD, stat(2) returns true for ISSOCK on pipes.
		 * Unfortunately, that's not portable, so we use lseek
		 * and check the errno values.
		 */
		errno = 0;
E 27
E 16
		if (lseek(rfd, (off_t)0, SEEK_CUR) == -1 && errno == ESPIPE) {
E 10
E 9
D 15
			SET(t, BTF_RDONLY);
E 15
I 15
D 16
			switch(flags & O_ACCMODE) {
E 16
I 16
			switch (flags & O_ACCMODE) {
E 16
			case O_RDONLY:
D 18
				SET(t, BTF_RDONLY);
E 18
I 18
				SET(t, R_RDONLY);
E 18
				break;
D 16
			case O_RDWR:
			case O_WRONLY:
E 16
			default:
				goto einval;
			}
E 15
I 9
D 10
			break;
		case O_RDWR:
			break;
		case O_WRONLY:
		default:
			goto einval;
E 10
I 10
D 12
			if ((t->bt_rfp = fdopen(rfd, "r")) == NULL)
E 12
I 12
slow:			if ((t->bt_rfp = fdopen(rfd, "r")) == NULL)
E 12
				goto err;
I 15
D 18
			SET(t, BTF_CLOSEFP);
E 18
I 18
			SET(t, R_CLOSEFP);
E 18
E 15
			t->bt_irec =
D 18
			    ISSET(t, BTF_FIXEDLEN) ? __rec_fpipe : __rec_vpipe;
E 18
I 18
			    ISSET(t, R_FIXLEN) ? __rec_fpipe : __rec_vpipe;
E 18
		} else {
D 15
			if (fstat(rfd, &sb))
				goto err;
E 15
D 16
			switch(flags & O_ACCMODE) {
E 16
I 16
			switch (flags & O_ACCMODE) {
E 16
			case O_RDONLY:
D 18
				SET(t, BTF_RDONLY);
E 18
I 18
				SET(t, R_RDONLY);
E 18
				break;
			case O_RDWR:
				break;
D 16
			case O_WRONLY:
E 16
			default:
				goto einval;
			}
D 16
				
E 16
I 16

E 16
I 15
			if (fstat(rfd, &sb))
				goto err;
E 15
D 14
			if (sb.st_size > SIZE_T_MAX) {
E 14
I 14
D 17
			if (sb.st_size > (off_t)SIZE_T_MAX) {
E 14
				errno = EFBIG;
				goto err;
E 17
I 17
			/*
D 21
			 * Kludge -- but we don't know what size an off_t
			 * is or what size a size_t is, although we do
			 * know that the former is signed and the latter
			 * unsigned.
E 21
I 21
			 * Kluge -- we'd like to test to see if the file is too
			 * big to mmap.  Since, we don't know what size or type
			 * off_t's or size_t's are, what the largest unsigned
			 * integral type is, or what random insanity the local
			 * C compiler will perpetrate, doing the comparison in
			 * a portable way is flatly impossible.  Hope that mmap
			 * fails if the file is too large.
E 21
			 */
D 21
			if (sizeof(sb.st_size) > sizeof(size_t)) {
				if (sb.st_size > (off_t)SIZE_T_MAX) {
					errno = EFBIG;
					goto err;
				}
			} else {
				if ((size_t)sb.st_size > SIZE_T_MAX) {
					errno = EFBIG;
					goto err;
				}
E 17
			}
E 21
D 15
			if ((t->bt_smap = mmap(NULL, (size_t)sb.st_size,
			    PROT_READ, 0, rfd, (off_t)0)) == (caddr_t)-1)
D 12
				goto err;
E 12
I 12
				goto slow;
E 12
			t->bt_emap = t->bt_smap + sb.st_size;
			t->bt_rfd = rfd;
			t->bt_rfp = NULL;
			t->bt_irec =
			    ISSET(t, BTF_FIXEDLEN) ? __rec_fmap : __rec_vmap;
E 15
I 15
			if (sb.st_size == 0)
D 18
				SET(t, BTF_EOF);
E 18
I 18
				SET(t, R_EOF);
E 18
			else {
				t->bt_msize = sb.st_size;
D 23
				if ((t->bt_smap =
				    mmap(NULL, t->bt_msize, PROT_READ, 0, rfd,
E 23
I 23
				if ((t->bt_smap = mmap(NULL, t->bt_msize,
				    PROT_READ, MAP_PRIVATE, rfd,
E 23
				    (off_t)0)) == (caddr_t)-1)
					goto slow;
				t->bt_cmap = t->bt_smap;
				t->bt_emap = t->bt_smap + sb.st_size;
D 18
				t->bt_irec = ISSET(t, BTF_FIXEDLEN) ?
E 18
I 18
				t->bt_irec = ISSET(t, R_FIXLEN) ?
E 18
				    __rec_fmap : __rec_vmap;
D 18
				SET(t, BTF_MEMMAPPED);
E 18
I 18
				SET(t, R_MEMMAPPED);
E 18
			}
E 15
E 10
		}
I 16
	}
E 16
D 10
			
E 9
D 3
		if ((t->bt_smap = mmap(NULL, sb.st_size, PROT_READ, MAP_FILE,
		    rfd, (off_t)0)) == NULL)
E 3
I 3
D 4
		if (sb.st_size > INT_MAX) {
E 4
I 4
D 5
		if (sb.st_size > UINT_MAX) {
E 5
I 5
		if (sb.st_size > SIZE_T_MAX) {
E 5
E 4
			errno = EFBIG;
E 3
			goto err;
I 3
		}
D 4
		if ((t->bt_smap = mmap(NULL, (int)sb.st_size,
		    PROT_READ, MAP_FILE, rfd, (off_t)0)) == NULL)
E 4
I 4
D 7
		if ((t->bt_smap = mmap(NULL,
D 6
		    (size_t)sb.st_size, PROT_READ, 0, rfd, (off_t)0)) == NULL)
E 6
I 6
		    (size_t)sb.st_size, PROT_READ, 0, rfd, (off_t)0)) == -1)
E 7
I 7
		if ((t->bt_smap = mmap(NULL, (size_t)sb.st_size,
		    PROT_READ, 0, rfd, (off_t)0)) == (caddr_t)-1)
E 7
E 6
E 4
			goto err;
E 3
		t->bt_emap = t->bt_smap + sb.st_size;
		t->bt_rfd = rfd;
I 3
		t->bt_rfp = NULL;
E 3
		t->bt_irec = ISSET(t, BTF_FIXEDLEN) ? __rec_fmap : __rec_vmap;
	}
E 10

	/* Use the recno routines. */
	dbp->close = __rec_close;
	dbp->del = __rec_delete;
I 20
	dbp->fd = __rec_fd;
E 20
	dbp->get = __rec_get;
	dbp->put = __rec_put;
	dbp->seq = __rec_seq;
	dbp->sync = __rec_sync;

	/* If the root page was created, reset the flags. */
	if ((h = mpool_get(t->bt_mp, P_ROOT, 0)) == NULL)
		goto err;
	if ((h->flags & P_TYPE) == P_BLEAF) {
		h->flags = h->flags & ~P_TYPE | P_RLEAF;
		mpool_put(t->bt_mp, h, MPOOL_DIRTY);
	} else
		mpool_put(t->bt_mp, h, 0);

	if (openinfo && openinfo->flags & R_SNAPSHOT &&
I 10
D 15
	    !ISSET(t, BTF_RINMEM) &&
E 15
I 15
D 18
	    !ISSET(t, BTF_EOF | BTF_RINMEM) &&
E 18
I 18
	    !ISSET(t, R_EOF | R_INMEM) &&
E 18
E 15
E 10
	    t->bt_irec(t, MAX_REC_NUMBER) == RET_ERROR)
                goto err;
	return (dbp);

I 9
einval:	errno = EINVAL;
E 9
D 2
err:	__bt_close(dbp);
E 2
I 2
D 10
err:	if (dbp)
E 10
I 10
D 15
err:	if (dbp != NULL)
E 10
		__bt_close(dbp);
E 15
I 15
err:	sverrno = errno;
	if (dbp != NULL)
		(void)__bt_close(dbp);
E 15
E 2
D 10
	(void)close(rfd);
E 10
I 10
	if (fname != NULL)
		(void)close(rfd);
I 15
	errno = sverrno;
E 15
E 10
	return (NULL);
I 20
}

int
__rec_fd(dbp)
	const DB *dbp;
{
	BTREE *t;

	t = dbp->internal;

I 24
	/* Toss any page pinned across calls. */
	if (t->bt_pinned != NULL) {
		mpool_put(t->bt_mp, t->bt_pinned, 0);
		t->bt_pinned = NULL;
	}

	/* In-memory database can't have a file descriptor. */
E 24
	if (ISSET(t, R_INMEM)) {
		errno = ENOENT;
		return (-1);
	}
	return (t->bt_rfd);
E 20
}
E 1
