h32514
s 00002/00002/00026
d D 8.1 93/06/04 13:08:41 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00006/00010
d D 5.3 91/01/20 21:26:19 bostic 4 3
c new stdio
e
s 00002/00002/00014
d D 5.2 86/03/09 20:52:53 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00012
d D 5.1 85/06/05 13:38:34 mckusick 2 1
c Add copyright
e
s 00013/00000/00000
d D 4.1 80/12/21 16:50:48 wnj 1 0
c date and time created 80/12/21 16:50:48 by wnj
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
D 4
/*
 * A subroutine version of the macro putchar
 */
E 4
#include <stdio.h>

#undef putchar

I 4
/*
 * A subroutine version of the macro putchar
 */
E 4
putchar(c)
D 4
register c;
E 4
I 4
	int c;
E 4
{
D 4
	putc(c, stdout);
E 4
I 4
	register FILE *so = stdout;

	return (__sputc(c, so));
E 4
}
E 1
