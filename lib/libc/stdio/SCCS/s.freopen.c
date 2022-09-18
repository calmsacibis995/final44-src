h43383
s 00002/00002/00127
d D 8.1 93/06/04 13:06:19 bostic 11 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00007/00122
d R 5.7 93/05/21 14:50:14 torek 10 9
c always call __sflush, in case somehow fp->_p > fp->_bf._base in __SRW
e
s 00002/00001/00127
d D 5.6 91/02/24 13:30:08 bostic 9 8
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00127
d D 5.5 91/02/05 00:26:34 torek 8 7
c repair arguments (add const)
e
s 00001/00001/00127
d D 5.4 91/02/01 19:30:15 bostic 7 6
c fflush -> __sflush
e
s 00108/00039/00020
d D 5.3 91/01/20 21:21:59 bostic 6 5
c new stdio
e
s 00002/00002/00057
d D 5.2 86/03/09 20:51:24 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00049
d D 5.1 85/05/30 14:29:05 dist 4 3
c Add copyright
e
s 00036/00034/00014
d D 4.3 85/02/13 15:48:43 serge 3 2
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00028/00009/00020
d D 4.2 81/03/09 20:59:18 toy 2 1
c Feldman's stdio changes
e
s 00029/00000/00000
d D 4.1 80/12/21 16:50:24 wnj 1 0
c date and time created 80/12/21 16:50:24 by wnj
e
u
U
t
T
I 1
D 4
/* %W% (Berkeley) %G% */
E 4
I 4
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
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
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 6
 */

D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5

E 4
D 2
#include <stdio.h>
E 2
I 2
D 3
#include	<stdio.h>
#include	<errno.h>
E 3
I 3
#include <sys/types.h>
D 9
#include <sys/file.h>
E 9
I 6
#include <sys/stat.h>
I 9
#include <fcntl.h>
E 9
#include <errno.h>
I 9
#include <unistd.h>
E 9
E 6
#include <stdio.h>
I 6
#include <stdlib.h>
#include "local.h"
E 6
E 3
E 2

I 6
/* 
 * Re-direct an existing, open (probably) file to some other file. 
 * ANSI is written such that the original file gets closed if at
 * all possible, no matter what.
 */
E 6
FILE *
D 6
freopen(file, mode, iop)
D 3
char *file;
register char *mode;
register FILE *iop;
E 3
I 3
	char *file;
	register char *mode;
	register FILE *iop;
E 6
I 6
freopen(file, mode, fp)
D 8
	char *file, *mode;
E 8
I 8
	const char *file, *mode;
E 8
	register FILE *fp;
E 6
E 3
{
D 2
	register f;
E 2
I 2
D 3
	extern int errno;
	register f, rw;
E 3
I 3
D 6
	register f, rw, oflags;
E 6
I 6
	register int f;
	int flags, isopen, oflags, sverrno, wantfd;
E 6
E 3
E 2

I 2
D 3
	rw = mode[1] == '+';
E 3
I 3
D 6
	rw = (mode[1] == '+');
E 6
I 6
	if ((flags = __sflags(mode, &oflags)) == 0) {
		(void) fclose(fp);
		return (NULL);
	}
E 6
E 3

E 2
D 6
	fclose(iop);
E 6
I 6
	if (!__sdidinit)
		__sinit();
E 6
D 2
	if (*mode=='w')
E 2
I 2
D 3
	if (*mode=='w') {
E 2
		f = creat(file, 0666);
D 2
	else if (*mode=='a') {
		if ((f = open(file, 1)) < 0)
			f = creat(file, 0666);
		lseek(f, 0L, 2);
E 2
I 2
		if (rw && f>=0) {
			close(f);
			f = open(file, 2);
		}
	} else if (*mode=='a') {
		if ((f = open(file, rw? 2: 1)) < 0) {
			if (errno == ENOENT) {
				f = creat(file, 0666);
				if (rw && f>=0) {
					close(f);
					f = open(file, 2);
				}
			}
		}
		if (f >= 0)
			lseek(f, 0L, 2);
E 2
	} else
D 2
		f = open(file, 0);
E 2
I 2
		f = open(file, rw? 2: 0);
E 3
I 3

D 6
	switch (*mode) {
	case 'a':
		oflags = O_CREAT | (rw ? O_RDWR : O_WRONLY);
		break;
	case 'r':
		oflags = rw ? O_RDWR : O_RDONLY;
		break;
	case 'w':
		oflags = O_TRUNC | O_CREAT | (rw ? O_RDWR : O_WRONLY);
		break;
	default:
		return (NULL);
E 6
I 6
	/*
	 * There are actually programs that depend on being able to "freopen"
	 * descriptors that weren't originally open.  Keep this from breaking.
	 * Remember whether the stream was open to begin with, and which file
	 * descriptor (if any) was associated with it.  If it was attached to
	 * a descriptor, defer closing it; freopen("/dev/stdin", "r", stdin)
	 * should work.  This is unnecessary if it was not a Unix file.
	 */
	if (fp->_flags == 0) {
		fp->_flags = __SEOF;	/* hold on to it */
		isopen = 0;
		wantfd = -1;
	} else {
		/* flush the stream; ANSI doesn't require this. */
		if (fp->_flags & __SWR)
D 7
			(void) fflush(fp);
E 7
I 7
			(void) __sflush(fp);
E 7
		/* if close is NULL, closing is a no-op, hence pointless */
		isopen = fp->_close != NULL;
		if ((wantfd = fp->_file) < 0 && isopen) {
			(void) (*fp->_close)(fp->_cookie);
			isopen = 0;
		}
E 6
	}

D 6
	f = open(file, oflags, 0666);
E 3
E 2
	if (f < 0)
E 6
I 6
	/* Get a new descriptor to refer to the new file. */
	f = open(file, oflags, DEFFILEMODE);
	if (f < 0 && isopen) {
		/* If out of fd's close the old one and try again. */
		if (errno == ENFILE || errno == EMFILE) {
			(void) (*fp->_close)(fp->_cookie);
			isopen = 0;
			f = open(file, oflags, DEFFILEMODE);
		}
	}
	sverrno = errno;

	/*
	 * Finish closing fp.  Even if the open succeeded above, we cannot
	 * keep fp->_base: it may be the wrong size.  This loses the effect
	 * of any setbuffer calls, but stdio has always done this before.
	 */
	if (isopen)
		(void) (*fp->_close)(fp->_cookie);
	if (fp->_flags & __SMBF)
		free((char *)fp->_bf._base);
	fp->_w = 0;
	fp->_r = 0;
	fp->_p = NULL;
	fp->_bf._base = NULL;
	fp->_bf._size = 0;
	fp->_lbfsize = 0;
	if (HASUB(fp))
		FREEUB(fp);
	fp->_ub._size = 0;
	if (HASLB(fp))
		FREELB(fp);
	fp->_lb._size = 0;

	if (f < 0) {			/* did not get it after all */
		fp->_flags = 0;		/* set it free */
		errno = sverrno;	/* restore in case _close clobbered */
E 6
D 3
		return(NULL);
E 3
I 3
		return (NULL);
I 6
	}
E 6

D 6
	if (*mode == 'a')
		lseek(f, (off_t)0, L_XTND);
E 6
I 6
	/*
	 * If reopening something that was open before on a real file, try
	 * to maintain the descriptor.  Various C library routines (perror)
	 * assume stderr is always fd STDERR_FILENO, even if being freopen'd.
	 */
	if (wantfd >= 0 && f != wantfd) {
		if (dup2(f, wantfd) >= 0) {
			(void) close(f);
			f = wantfd;
		}
	}
E 6

E 3
I 2
D 6
	iop->_cnt = 0;
E 2
	iop->_file = f;
I 3
	iop->_bufsiz = 0;
E 3
D 2
	if (*mode != 'r')
E 2
I 2
	if (rw)
D 3
		iop->_flag |= _IORW;
	else if (*mode != 'r')
E 2
		iop->_flag |= _IOWRT;
E 3
I 3
		iop->_flag = _IORW;
	else if (*mode == 'r')
		iop->_flag = _IOREAD;
E 3
	else
D 3
		iop->_flag |= _IOREAD;
	return(iop);
E 3
I 3
		iop->_flag = _IOWRT;
	iop->_base = iop->_ptr = NULL;
	return (iop);
E 6
I 6
	fp->_flags = flags;
	fp->_file = f;
	fp->_cookie = fp;
	fp->_read = __sread;
	fp->_write = __swrite;
	fp->_seek = __sseek;
	fp->_close = __sclose;
	return (fp);
E 6
E 3
}
E 1
