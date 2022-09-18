h22987
s 00002/00002/00023
d D 8.1 93/06/04 13:07:32 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00002/00013
d D 5.3 91/01/20 21:23:49 bostic 4 3
c new stdio
e
s 00002/00002/00013
d D 5.2 86/03/09 20:52:14 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00011
d D 5.1 85/06/05 13:36:59 mckusick 2 1
c Add copyright
e
s 00012/00000/00000
d D 4.1 80/12/21 16:50:30 wnj 1 0
c date and time created 80/12/21 16:50:30 by wnj
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
/*
 * A subroutine version of the macro getchar.
 */
#include <stdio.h>

#undef getchar

getchar()
{
D 4
	return(getc(stdin));
E 4
I 4
	return (getc(stdin));
E 4
}
E 1
