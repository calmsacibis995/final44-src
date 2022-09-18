h23022
s 00002/00002/00034
d D 8.1 93/06/04 13:09:33 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00033
d D 5.6 92/12/04 04:56:17 torek 11 10
c style police; setlinebuf returns whatever setvbuf returns
e
s 00003/00001/00033
d D 5.5 91/03/18 00:55:27 torek 10 9
c get the buffering flags right in setbuffer
e
s 00000/00001/00034
d D 5.4 91/02/24 13:30:21 bostic 9 8
c Add include files to get prototype declarations, and fix bugs found.
e
s 00020/00032/00015
d D 5.3 91/01/20 21:30:04 bostic 8 7
c new stdio
e
s 00002/00002/00045
d D 5.2 86/03/09 20:53:51 donn 7 6
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00037
d D 5.1 85/05/30 14:30:21 dist 6 5
c Add copyright
e
s 00002/00002/00036
d D 4.5 85/02/13 15:49:19 serge 5 4
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00007/00002/00031
d D 4.4 84/05/22 10:44:17 karels 4 3
c be careful of malloc return; free old buffer before allocating new
c in setlinebuf
e
s 00003/00007/00030
d D 4.3 84/05/15 16:54:50 ralph 3 2
c use malloc instead of static 8K sibuf and sobuf.
e
s 00017/00000/00020
d D 4.2 83/02/27 12:01:01 mckusick 2 1
c add "setlinebuf" to request line buffering of stdout or stderr
e
s 00020/00000/00000
d D 4.1 82/10/05 22:47:01 mckusick 1 0
c date and time created 82/10/05 22:47:01 by mckusick
e
u
U
t
T
I 1
D 6
/* %W% (Berkeley) %G% */
E 6
I 6
D 8
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
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
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
E 8
 */

D 7
#ifndef lint
E 7
I 7
#if defined(LIBC_SCCS) && !defined(lint)
E 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
D 8
#endif LIBC_SCCS and not lint
E 8
I 8
#endif /* LIBC_SCCS and not lint */
E 8
E 7

E 6
D 8
#include	<stdio.h>
E 8
I 8
#include <stdio.h>
D 9
#include <stdlib.h>
E 9
E 8

D 8
setbuffer(iop, buf, size)
D 5
	register struct _iobuf *iop;
E 5
I 5
	register FILE *iop;
E 8
I 8
void
setbuffer(fp, buf, size)
	register FILE *fp;
E 8
E 5
	char *buf;
	int size;
{
D 8
	if (iop->_base != NULL && iop->_flag&_IOMYBUF)
		free(iop->_base);
	iop->_flag &= ~(_IOMYBUF|_IONBF|_IOLBF);
	if ((iop->_base = buf) == NULL) {
		iop->_flag |= _IONBF;
		iop->_bufsiz = NULL;
	} else {
		iop->_ptr = iop->_base;
		iop->_bufsiz = size;
	}
	iop->_cnt = 0;
E 8
I 8
D 10
	(void) setvbuf(fp, buf, buf ? _IONBF : _IOFBF, size);
E 10
I 10

D 11
	(void) setvbuf(fp, buf, buf ? _IOFBF : _IONBF, size);
E 11
I 11
	(void)setvbuf(fp, buf, buf ? _IOFBF : _IONBF, size);
E 11
E 10
E 8
}
I 2

/*
D 8
 * set line buffering for either stdout or stderr
E 8
I 8
 * set line buffering
E 8
 */
I 11
int
E 11
D 8
setlinebuf(iop)
D 5
	register struct _iobuf *iop;
E 5
I 5
	register FILE *iop;
E 8
I 8
setlinebuf(fp)
	FILE *fp;
E 8
E 5
{
I 10

E 10
I 4
D 8
	char *buf;
E 4
D 3
	static char _sebuf[BUFSIZ];
	extern char _sobuf[];
E 3
I 3
	extern char *malloc();
E 3

D 3
	if (iop != stdout && iop != stderr)
		return;
E 3
	fflush(iop);
D 3
	setbuffer(iop, NULL, 0);
	setbuffer(iop, iop == stderr ? _sebuf : _sobuf, BUFSIZ);
	iop->_flag |= _IOLBF;
E 3
I 3
D 4
	setbuffer(iop, malloc(BUFSIZ), BUFSIZ);
	iop->_flag |= _IOLBF|_IOMYBUF;
E 4
I 4
	setbuffer(iop, NULL, 0);
	buf = malloc(BUFSIZ);
	if (buf != NULL) {
		setbuffer(iop, buf, BUFSIZ);
		iop->_flag |= _IOLBF|_IOMYBUF;
	}
E 8
I 8
D 11
	(void) setvbuf(fp, (char *)NULL, _IOLBF, (size_t)0);
	return (0);	/* ??? */
E 11
I 11
	return (setvbuf(fp, (char *)NULL, _IOLBF, (size_t)0));
E 11
E 8
E 4
E 3
}
E 2
E 1
