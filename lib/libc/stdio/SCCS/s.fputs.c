h14248
s 00002/00002/00032
d D 8.1 93/06/04 13:06:04 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00034
d D 5.6 91/02/24 13:30:07 bostic 9 8
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00002/00033
d D 5.5 91/02/05 00:26:33 torek 8 7
c repair arguments (add const)
e
s 00001/00001/00034
d D 5.4 91/02/01 19:30:02 bostic 7 6
c stdc.h -> cdefs.h
e
s 00026/00032/00009
d D 5.3 91/01/20 21:20:54 bostic 6 5
c new stdio
e
s 00002/00002/00039
d D 5.2 86/03/09 20:50:56 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00031
d D 5.1 85/06/05 13:34:46 mckusick 4 3
c Add copyright
e
s 00018/00000/00014
d D 4.3 85/02/13 15:48:40 serge 3 2
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00001/00001/00013
d D 4.2 84/09/20 06:01:24 lepreau 2 1
c fix return value on null string
e
s 00014/00000/00000
d D 4.1 80/12/21 16:50:22 wnj 1 0
c date and time created 80/12/21 16:50:22 by wnj
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
 * Copyright (c) 1984 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
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
D 6
#include	<stdio.h>
E 6
I 6
D 7
#include <sys/stdc.h>
E 7
I 7
D 9
#include <sys/cdefs.h>
E 9
E 7
#include <stdio.h>
#include <string.h>
#include "fvwrite.h"
E 6

D 6
fputs(s, iop)
register char *s;
register FILE *iop;
E 6
I 6
/*
 * Write the given string to the given file.
 */
fputs(s, fp)
D 8
	char *s;
E 8
I 8
	const char *s;
E 8
	FILE *fp;
E 6
{
D 2
	register r;
E 2
I 2
D 6
	register r = 0;
E 2
	register c;
I 3
	int unbuffered;
	char localbuf[BUFSIZ];
E 6
I 6
	struct __suio uio;
	struct __siov iov;
E 6
E 3

I 3
D 6
	unbuffered = iop->_flag & _IONBF;
	if (unbuffered) {
		iop->_flag &= ~_IONBF;
		iop->_ptr = iop->_base = localbuf;
		iop->_bufsiz = BUFSIZ;
	}

E 3
	while (c = *s++)
		r = putc(c, iop);
I 3

	if (unbuffered) {
		fflush(iop);
		iop->_flag |= _IONBF;
		iop->_base = NULL;
		iop->_bufsiz = NULL;
		iop->_cnt = 0;
	}

E 3
	return(r);
E 6
I 6
D 8
	iov.iov_base = s;
E 8
I 8
	iov.iov_base = (void *)s;
E 8
	iov.iov_len = uio.uio_resid = strlen(s);
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	return (__sfvwrite(fp, &uio));
E 6
}
E 1
