h61414
s 00002/00002/00061
d D 8.1 93/06/04 13:04:08 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00061
d D 5.6 91/02/24 13:30:04 bostic 13 12
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00061
d D 5.5 91/02/05 00:25:30 torek 12 11
c repair arguments (add const)
e
s 00009/00011/00053
d D 5.4 91/02/01 19:28:46 bostic 11 10
c fdopen got messed up
e
s 00040/00038/00024
d D 5.3 91/01/20 21:09:07 bostic 10 9
c new stdio
e
s 00002/00002/00060
d D 5.2 86/03/09 20:48:53 donn 9 8
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00052
d D 5.1 85/05/30 14:26:53 dist 8 7
c Add copyright
e
s 00035/00019/00018
d D 4.5 85/02/13 15:56:11 serge 7 5
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00035/00019/00018
d R 4.5 85/02/13 15:48:26 serge 6 5
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00002/00002/00035
d D 4.4 83/09/12 16:23:52 karels 5 4
c don't allow file pointer to fall off file table
e
s 00002/00000/00035
d D 4.3 83/06/30 15:39:00 sam 4 2
c bounds check
e
s 00006/00003/00032
d R 4.3 83/05/26 14:33:16 ralph 3 2
c fixed case where loop exits with iop == _lastbuf.
e
s 00005/00001/00030
d D 4.2 81/03/09 20:59:07 toy 2 1
c Feldman's stdio changes
e
s 00031/00000/00000
d D 4.1 80/12/21 16:50:07 wnj 1 0
c date and time created 80/12/21 16:50:07 by wnj
e
u
U
t
T
I 1
D 8
/* %W% (Berkeley) %G% */
E 8
I 8
D 10
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
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
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 10
 */

D 9
#ifndef lint
E 9
I 9
#if defined(LIBC_SCCS) && !defined(lint)
E 9
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
D 10
#endif LIBC_SCCS and not lint
E 10
I 10
#endif /* LIBC_SCCS and not lint */
E 10
E 9

E 8
D 10
/*
 * Unix routine to do an "fopen" on file descriptor
 * The mode has to be repeated because you can't query its
 * status
 */

E 10
D 7
#include	<stdio.h>
#include	<errno.h>
E 7
I 7
#include <sys/types.h>
D 13
#include <sys/file.h>
E 13
I 13
#include <fcntl.h>
#include <unistd.h>
E 13
I 10
D 11
#include <sys/errno.h>
E 11
E 10
#include <stdio.h>
I 11
#include <errno.h>
E 11
I 10
#include "local.h"
E 10
E 7

FILE *
fdopen(fd, mode)
D 7
register char *mode;
E 7
I 7
D 10
	register char *mode;
E 10
I 10
	int fd;
D 12
	char *mode;
E 12
I 12
	const char *mode;
E 12
E 10
E 7
{
D 7
	extern int errno;
E 7
I 7
D 10
	extern FILE *_findiop();
	static int nofile = -1;
E 7
	register FILE *iop;
E 10
I 10
D 11
	static int nofile;
E 11
	register FILE *fp;
D 11
	int flags, oflags, fdflags, fdmode;
E 11
I 11
	static int nofile;
	int flags, oflags, fdflags, tmp;
E 11
E 10
D 7
	extern FILE *_lastbuf;
E 7

I 4
D 7
	if ((unsigned)fd >= getdtablesize())
E 7
I 7
D 10
	if (nofile < 0)
E 10
I 10
	if (nofile == 0)
E 10
		nofile = getdtablesize();

D 10
	if (fd < 0 || fd >= nofile)
E 10
I 10
D 11
	if ((fdflags = fcntl(fd, F_GETFL, 0)) < 0)
E 11
I 11
	if ((flags = __sflags(mode, &oflags)) == 0)
E 11
E 10
E 7
		return (NULL);
E 4
D 2
	for (iop = _iob; iop->_flag&(_IOREAD|_IOWRT); iop++)
E 2
I 2
D 5
	for (iop = _iob; iop->_flag&(_IOREAD|_IOWRT|_IORW); iop++)
E 2
		if (iop >= _lastbuf)
E 5
I 5
D 7
	for (iop = _iob; iop->_flag&(_IOREAD|_IOWRT|_IORW); )
		if (++iop >= _lastbuf)
E 5
			return(NULL);
E 7
I 7

D 10
	iop = _findiop();
	if (iop == NULL)
E 10
I 10
	/* Make sure the mode the user wants is a subset of the actual mode. */
D 11
	fdmode = fdflags & O_ACCMODE;
	if (fdmode != O_RDWR && fdmode != (oflags & O_ACCMODE)) {
E 11
I 11
	if ((fdflags = fcntl(fd, F_GETFL, 0)) < 0)
		return (NULL);
	tmp = fdflags & O_ACCMODE;
	if (tmp != O_RDWR && (tmp != (oflags & O_ACCMODE))) {
E 11
		errno = EINVAL;
E 10
		return (NULL);
I 10
	}
E 10

E 7
D 10
	iop->_cnt = 0;
	iop->_file = fd;
D 7
	if (*mode != 'r') {
		iop->_flag |= _IOWRT;
		if (*mode == 'a')
			lseek(fd, 0L, 2);
	} else
		iop->_flag |= _IOREAD;
I 2
	if (mode[1] == '+') {
		iop->_flag &= ~(_IOREAD|_IOWRT);
		iop->_flag |= _IORW;
E 7
I 7
	iop->_bufsiz = 0;
	iop->_base = iop->_ptr = NULL;
E 10
I 10
	if ((fp = __sfp()) == NULL)
		return (NULL);
E 10
D 11

D 10
	switch (*mode) {
	case 'r':
		iop->_flag = _IOREAD;
		break;
	case 'a':
		lseek(fd, (off_t)0, L_XTND);
		/* fall into ... */
	case 'w':
		iop->_flag = _IOWRT;
		break;
	default:
E 10
I 10
	if ((fp->_flags = __sflags(mode, &oflags)) == 0) 
E 10
		return (NULL);
E 7
D 10
	}
E 10
E 2
D 7
	return(iop);
E 7
I 7

E 11
I 11
	fp->_flags = flags;
E 11
D 10
	if (mode[1] == '+')
		iop->_flag = _IORW;
E 10
I 10
	/*
	 * If opened for appending, but underlying descriptor does not have
	 * O_APPEND bit set, assert __SAPP so that __swrite() will lseek to
	 * end before each write.
	 */
	if ((oflags & O_APPEND) && !(fdflags & O_APPEND))
		fp->_flags |= __SAPP;
E 10
D 11

E 11
D 10
	return (iop);
E 10
I 10
	fp->_file = fd;
	fp->_cookie = fp;
	fp->_read = __sread;
	fp->_write = __swrite;
	fp->_seek = __sseek;
	fp->_close = __sclose;
	return (fp);
E 10
E 7
}
E 1
