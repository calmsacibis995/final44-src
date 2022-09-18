h48528
s 00002/00002/00013
d D 8.1 93/06/04 18:46:13 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00000/00000
d D 5.1 93/05/17 10:04:15 bostic 1 0
c date and time created 93/05/17 10:04:15 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

void	error __P((char *, char *));
void	gethead __P((int));
int	process __P((void));
void	redist __P((void));
void	reply __P((void));
void	seterr __P((void));
E 1
