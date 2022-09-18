h62679
s 00002/00002/00014
d D 8.1 93/05/31 17:53:54 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00013
d D 5.2 92/12/23 10:16:43 bostic 2 1
c update copyright notice with contrib notice
e
s 00013/00000/00000
d D 5.1 92/12/22 11:50:36 bostic 1 0
c date and time created 92/12/22 11:50:36 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Chris Torek and Darren F. Provine.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

void	eat_input __P((void));
int	rwait __P((struct timeval *));
int	tgetchar __P((void));
void	tsleep __P((void));
E 1
