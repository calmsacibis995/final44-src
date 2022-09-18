h24693
s 00002/00002/00037
d D 8.1 93/06/04 13:05:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00038
d D 5.2 91/02/24 13:30:06 bostic 2 1
c Add include files to get prototype declarations, and fix bugs found.
e
s 00038/00000/00000
d D 5.1 91/01/20 21:34:50 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <errno.h>
#include <stdio.h>
I 2
#include <stdlib.h>
E 2
#include "local.h"

/*
 * fpurge: like fflush, but without writing anything: leave the
 * given FILE's buffer empty.
 */
int
fpurge(fp)
	register FILE *fp;
{
	if (!fp->_flags) {
		errno = EBADF;
		return(EOF);
	}

	if (HASUB(fp))
		FREEUB(fp);
	fp->_p = fp->_bf._base;
	fp->_r = 0;
	fp->_w = fp->_flags & (__SLBF|__SNBF) ? 0 : fp->_bf._size;
	return (0);
}
E 1
