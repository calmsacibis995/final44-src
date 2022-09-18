h52643
s 00002/00002/00039
d D 8.1 93/06/04 13:04:05 bostic 5 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00040
d R 5.4 93/05/21 14:46:52 torek 4 3
c always call __sflush, in case somehow fp->_p > fp->_bf._base in __SRW
e
s 00002/00001/00039
d D 5.3 92/08/27 22:57:56 bostic 3 2
c don't allow reuse after close
e
s 00001/00001/00039
d D 5.2 91/02/01 19:29:24 bostic 2 1
c use __sflush, not fflush
e
s 00040/00000/00000
d D 5.1 91/01/20 21:34:43 bostic 1 0
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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "local.h"

fclose(fp)
	register FILE *fp;
{
	register int r;

	if (fp->_flags == 0) {	/* not open! */
		errno = EBADF;
		return (EOF);
	}
D 2
	r = fp->_flags & __SWR ? fflush(fp) : 0;
E 2
I 2
	r = fp->_flags & __SWR ? __sflush(fp) : 0;
E 2
	if (fp->_close != NULL && (*fp->_close)(fp->_cookie) < 0)
		r = EOF;
	if (fp->_flags & __SMBF)
		free((char *)fp->_bf._base);
	if (HASUB(fp))
		FREEUB(fp);
	if (HASLB(fp))
		FREELB(fp);
D 3
	fp->_flags = 0;		/* release this FILE for reuse */
E 3
I 3
	fp->_flags = 0;		/* Release this FILE for reuse. */
	fp->_r = fp->_w = 0;	/* Mess up if reaccessed. */
E 3
	return (r);
}
E 1
