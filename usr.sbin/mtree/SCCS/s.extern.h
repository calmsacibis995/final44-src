h08345
s 00002/00002/00016
d D 8.1 93/06/06 14:03:00 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00017
d D 5.2 92/04/17 17:21:33 bostic 2 1
c add needvalue argument to parsekey
e
s 00018/00000/00000
d D 5.1 91/12/11 17:56:40 bostic 1 0
c version 2; add cksum, make keywords flexible, new output format
c date and time created 91/12/11 17:56:40 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

int	 compare __P((char *, NODE *, FTSENT *));
int	 crc __P((int, u_long *, u_long *));
void	 cwalk __P((void));
void	 err __P((const char *, ...));
char	*inotype __P((u_int));
D 2
u_int	 parsekey __P((char *));
E 2
I 2
u_int	 parsekey __P((char *, int *));
E 2
char	*rlink __P((char *));
NODE	*spec __P((void));
int	 verify __P((void));
E 1
