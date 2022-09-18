h55475
s 00002/00002/00021
d D 8.1 93/06/04 16:22:00 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00017
d D 5.3 91/04/19 19:08:04 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00020
d D 5.2 86/03/09 19:23:53 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00013
d D 5.1 85/05/30 10:28:50 dist 3 2
c Add copyright
e
s 00005/00009/00009
d D 4.2 83/07/04 11:56:16 sam 2 1
c split out gtty
e
s 00018/00000/00000
d D 4.1 80/12/21 16:40:21 wnj 1 0
c date and time created 80/12/21 16:40:21 by wnj
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
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
E 5
 */

D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4
E 3

E 2
/*
D 2
 * Writearound to old stty and gtty system calls
E 2
I 2
 * Writearound to old stty system call.
E 2
 */

#include <sgtty.h>

stty(fd, ap)
D 2
struct sgtty *ap;
E 2
I 2
	struct sgtty *ap;
E 2
{
D 2
	return(ioctl(fd, TIOCSETP, ap));
}
E 2

D 2
gtty(fd, ap)
struct sgtty *ap;
{
	return(ioctl(fd, TIOCGETP, ap));
E 2
I 2
	return(ioctl(fd, TIOCSETP, ap));
E 2
}
E 1
