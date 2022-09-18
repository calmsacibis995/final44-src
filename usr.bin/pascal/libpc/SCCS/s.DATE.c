h12390
s 00002/00002/00027
d D 8.1 93/06/06 15:15:22 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00020
d D 1.2 90/04/09 18:26:10 bostic 2 1
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00022/00000/00000
d D 1.1 80/10/30 00:33:02 mckusick 1 0
c date and time created 80/10/30 00:33:02 by mckusick
e
u
U
t
T
I 1
D 2
/* Copyright (c) 1979 Regents of the University of California */
E 2
I 2
/*-
D 3
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */
E 2

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

char	_pd_date[] = {
	8, 9, 10, 4, 5, 6, 10, 22, 23, 10, 0
};

extern char *ctime();

DATE(alfap)

	register char *alfap;
{
	register char *ap, *cp, *dp;
	long a;

	time(&a);
	cp = ctime(&a);
	ap = alfap;
	for (dp = _pd_date; *dp; *ap++ = cp[*dp++]);
}
E 1
