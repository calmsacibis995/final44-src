h59372
s 00002/00002/00053
d D 8.1 93/06/04 13:06:56 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00052
d D 5.2 91/02/05 00:27:11 torek 2 1
c repair arguments (add const)
e
s 00055/00000/00000
d D 5.1 91/01/20 21:34:51 bostic 1 0
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

#include <stdio.h>
#include <errno.h>
#include "local.h"

FILE *
funopen(cookie, readfn, writefn, seekfn, closefn)
D 2
	char *cookie;
E 2
I 2
	const void *cookie;
E 2
	int (*readfn)(), (*writefn)();
#if __STDC__
D 2
	fpos_t (*seekfn)(char *cookie, fpos_t off, int whence);
E 2
I 2
	fpos_t (*seekfn)(void *cookie, fpos_t off, int whence);
E 2
#else
	fpos_t (*seekfn)();
#endif
	int (*closefn)();
{
	register FILE *fp;
	int flags;

	if (readfn == NULL) {
		if (writefn == NULL) {		/* illegal */
			errno = EINVAL;
			return (NULL);
		} else
			flags = __SWR;		/* write only */
	} else {
		if (writefn == NULL)
			flags = __SRD;		/* read only */
		else
			flags = __SRW;		/* read-write */
	}
	if ((fp = __sfp()) == NULL)
		return (NULL);
	fp->_flags = flags;
	fp->_file = -1;
D 2
	fp->_cookie = cookie;
E 2
I 2
	fp->_cookie = (void *)cookie;
E 2
	fp->_read = readfn;
	fp->_write = writefn;
	fp->_seek = seekfn;
	fp->_close = closefn;
	return (fp);
}
E 1
