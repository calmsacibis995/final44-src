h45113
s 00002/00002/00028
d D 8.1 93/06/04 13:08:52 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00009/00008
d D 5.3 91/01/20 21:26:49 bostic 4 3
c new stdio
e
s 00002/00002/00015
d D 5.2 86/03/09 20:53:12 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00013
d D 5.1 85/06/05 13:39:13 mckusick 2 1
c Add copyright
e
s 00014/00000/00000
d D 4.1 80/12/21 16:50:51 wnj 1 0
c date and time created 80/12/21 16:50:51 by wnj
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
#include <stdio.h>
I 4
#include "fvwrite.h"
E 4

D 4
putw(w, iop)
register FILE *iop;
E 4
I 4
putw(w, fp)
	int w;
	FILE *fp;
E 4
{
D 4
	register char *p;
	register i;
E 4
I 4
	struct __suio uio;
	struct __siov iov;
E 4

D 4
	p = (char *)&w;
	for (i=sizeof(int); --i>=0;)
		putc(*p++, iop);
	return(ferror(iop));
E 4
I 4
	iov.iov_base = &w;
	iov.iov_len = uio.uio_resid = sizeof(w);
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	return (__sfvwrite(fp, &uio));
E 4
}
E 1
