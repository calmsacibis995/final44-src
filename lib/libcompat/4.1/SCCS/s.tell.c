h28781
s 00002/00002/00019
d D 8.1 93/06/04 16:22:03 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00015
d D 5.3 91/04/19 19:08:05 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00018
d D 5.2 86/03/09 19:24:04 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00010
d D 5.1 85/05/30 10:29:09 dist 2 1
c Add copyright
e
s 00011/00000/00000
d D 4.1 80/12/21 16:40:24 wnj 1 0
c date and time created 80/12/21 16:40:24 by wnj
e
u
U
t
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
E 4
 */

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
 * return offset in file.
 */

long	lseek();

long tell(f)
{
	return(lseek(f, 0L, 1));
}
E 1
