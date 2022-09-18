h10857
s 00002/00002/00061
d D 8.1 93/06/04 13:04:33 bostic 5 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00062
d R 5.4 93/05/21 14:44:50 torek 4 3
c allow __SRW flush if somehow fp->_p > fp->_bf._base
e
s 00001/00001/00062
d D 5.3 92/10/04 12:55:32 bostic 3 2
c <sys/errno.h> -> <errno.h>
e
s 00002/00002/00061
d D 5.2 92/09/11 15:38:06 torek 2 1
c make sure we allow flush on update-mode streams
e
s 00063/00000/00000
d D 5.1 91/01/20 21:34:45 bostic 1 0
c new stdio
e
u
U
t
T
I 1
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

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 3
#include <sys/errno.h>
E 3
I 3
#include <errno.h>
E 3
#include <stdio.h>
#include "local.h"

/* Flush a single file, or (if fp is NULL) all files.  */
fflush(fp)
	register FILE *fp;
{
I 2

E 2
	if (fp == NULL)
		return (_fwalk(__sflush));
D 2

	if ((fp->_flags & __SWR) == 0) {
E 2
I 2
	if ((fp->_flags & (__SWR | __SRW)) == 0) {
E 2
		errno = EBADF;
		return (EOF);
	}
	return (__sflush(fp));
}

__sflush(fp)
	register FILE *fp;
{
	register unsigned char *p;
	register int n, t;

	t = fp->_flags;
	if ((t & __SWR) == 0)
		return (0);

	if ((p = fp->_bf._base) == NULL)
		return (0);

	n = fp->_p - p;		/* write this much */

	/*
	 * Set these immediately to avoid problems with longjmp and to allow
	 * exchange buffering (via setvbuf) in user write function.
	 */
	fp->_p = p;
	fp->_w = t & (__SLBF|__SNBF) ? 0 : fp->_bf._size;

	for (; n > 0; n -= t, p += t) {
		t = (*fp->_write)(fp->_cookie, (char *)p, n);
		if (t <= 0) {
			fp->_flags |= __SERR;
			return (EOF);
		}
	}
	return (0);
}
E 1
