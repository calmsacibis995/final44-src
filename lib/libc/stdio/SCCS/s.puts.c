h20699
s 00002/00002/00035
d D 8.1 93/06/04 13:08:46 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00037
d D 5.6 91/02/24 13:30:17 bostic 7 6
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00001/00037
d D 5.5 91/02/05 00:28:06 torek 6 5
c iov base is not const; perhaps it should be...
e
s 00001/00001/00037
d D 5.4 91/02/01 19:30:27 bostic 5 4
c stdc.h -> cdefs.h
e
s 00030/00007/00008
d D 5.3 91/01/20 21:26:38 bostic 4 3
c new stdio
e
s 00002/00002/00013
d D 5.2 86/03/09 20:53:03 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00011
d D 5.1 85/06/05 13:38:51 mckusick 2 1
c Add copyright
e
s 00012/00000/00000
d D 4.1 80/12/21 16:50:50 wnj 1 0
c date and time created 80/12/21 16:50:50 by wnj
e
u
U
t
T
I 4
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 4
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3

E 2
D 4
#include	<stdio.h>
E 4
I 4
D 5
#include <sys/stdc.h>
E 5
I 5
D 7
#include <sys/cdefs.h>
E 7
E 5
#include <stdio.h>
#include <string.h>
#include "fvwrite.h"
E 4

I 4
/*
 * Write the given string to stdout, appending a newline.
 */
E 4
puts(s)
D 4
register char *s;
E 4
I 4
	char const *s;
E 4
{
D 4
	register c;
E 4
I 4
	size_t c = strlen(s);
	struct __suio uio;
	struct __siov iov[2];
E 4

D 4
	while (c = *s++)
		putchar(c);
	return(putchar('\n'));
E 4
I 4
D 6
	iov[0].iov_base = s;
E 6
I 6
	iov[0].iov_base = (void *)s;
E 6
	iov[0].iov_len = c;
	iov[1].iov_base = "\n";
	iov[1].iov_len = 1;
	uio.uio_resid = c + 1;
	uio.uio_iov = &iov[0];
	uio.uio_iovcnt = 2;
	return (__sfvwrite(stdout, &uio) ? EOF : '\n');
E 4
}
E 1
