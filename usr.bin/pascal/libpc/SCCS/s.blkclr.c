h17015
s 00002/00002/00018
d D 8.1 93/06/06 15:13:17 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00011
d D 1.3 90/04/09 18:28:14 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00002/00002/00011
d D 1.2 82/11/12 14:48:44 mckusick 2 1
c make size last arg to blkcpy and blkclr to be compatable with bcopy and bcmp
e
s 00013/00000/00000
d D 1.1 81/03/07 15:27:28 mckusick 1 0
c date and time created 81/03/07 15:27:28 by mckusick
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1979 Regents of the University of California */
E 3
I 3
/*-
D 4
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */
E 3

D 3
static char sccsid[] = "%Z%%M% %I% %G%";
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

D 2
blkclr(siz, at)
	long		siz;
E 2
I 2
blkclr(at, siz)
E 2
	register char	*at;
I 2
	long		siz;
E 2
{
	register int	size = siz;

	while(size-- > 0)
		*at++ = 0;
}
E 1
