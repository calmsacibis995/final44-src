h08459
s 00002/00002/00033
d D 8.1 93/06/04 12:05:23 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00000/00000
d D 5.1 93/05/28 00:50:23 mckusick 1 0
c date and time created 93/05/28 00:50:23 by mckusick
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1993 Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <setjmp.h>

int
sigsetjmp(jmpbuf, savemask)
	sigjmp_buf	jmpbuf;
	int		savemask;
{

	jmpbuf[_JBLEN] = savemask;
	if (savemask)
		return (setjmp(jmpbuf));
	return (_setjmp(jmpbuf));
}

void
siglongjmp(jmpbuf, retval)
	sigjmp_buf	jmpbuf;
	int		retval;
{

	if (jmpbuf[_JBLEN])
		return (longjmp(jmpbuf, retval));
	return (_longjmp(jmpbuf, retval));
}
E 1
