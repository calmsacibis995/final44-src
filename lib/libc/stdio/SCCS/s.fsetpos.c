h02158
s 00002/00002/00023
d D 8.1 93/06/04 13:06:41 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00024
d D 5.2 91/02/05 00:27:10 torek 2 1
c repair arguments (add const)
e
s 00025/00000/00000
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

/*
 * fsetpos: like fseek.
 */
fsetpos(iop, pos)
	FILE *iop;
D 2
	fpos_t *pos;
E 2
I 2
	const fpos_t *pos;
E 2
{
	return (fseek(iop, (long)*pos, SEEK_SET));
}
E 1
