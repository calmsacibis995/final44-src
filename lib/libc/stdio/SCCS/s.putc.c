h60412
s 00002/00002/00025
d D 8.1 93/06/04 13:08:36 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 5.1 91/01/20 21:34:57 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
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

/*
 * A subroutine version of the macro putc.
 */
#undef putc

putc(c, fp)
	int c;
	register FILE *fp;
{
	return (__sputc(c, fp));
}
E 1
