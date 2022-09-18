h53405
s 00000/00001/00012
d D 8.2 95/04/28 10:19:57 bostic 3 2
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00011
d D 8.1 93/06/05 10:54:45 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00000/00000
d D 5.1 91/09/19 10:16:34 bostic 1 0
c date and time created 91/09/19 10:16:34 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
void	err __P((const char *, ...));
E 3
void	get __P((int, off_t, void *, size_t));

extern char *special;
E 1
