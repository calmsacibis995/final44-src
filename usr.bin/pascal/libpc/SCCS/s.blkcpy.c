h36416
s 00002/00002/00026
d D 8.1 93/06/06 15:13:20 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00019
d D 1.4 90/04/09 18:28:15 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00002/00002/00019
d D 1.3 82/11/12 14:48:48 mckusick 3 2
c make size last arg to blkcpy and blkclr to be compatable with bcopy and bcmp
e
s 00001/00001/00020
d D 1.2 81/09/28 22:00:55 mckusic 2 1
c fix for possibly overlapping strings
e
s 00021/00000/00000
d D 1.1 81/03/07 15:27:09 mckusick 1 0
c date and time created 81/03/07 15:27:09 by mckusick
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1979 Regents of the University of California */
E 4
I 4
/*-
D 5
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */
E 4

D 4
static char sccsid[] = "%Z%%M% %I% %G%";
E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

D 3
blkcpy(siz, from, to)
	long		siz;
E 3
I 3
blkcpy(from, to, siz)
E 3
	register char	*from;
	register char	*to;
I 3
	long		siz;
E 3
{
	register int	size = siz;

D 2
	if (from + size < to)
E 2
I 2
	if (to < from)
E 2
		while(size-- > 0)
			*to++ = *from++;
	else {
		to += size;
		from += size;
		while(size-- > 0)
			*--to = *--from;
	}
}
E 1
