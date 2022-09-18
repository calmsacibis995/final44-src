h18466
s 00008/00005/00027
d D 5.2 91/04/12 15:33:05 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00025
d D 5.1 85/06/07 23:20:32 kre 2 1
c Add copyright
e
s 00026/00000/00000
d D 1.1 81/02/18 21:48:56 dlw 1 0
c date and time created 81/02/18 21:48:56 by dlw
e
u
U
t
T
I 1
D 3
/*
D 2
char id_gmtime[] = "%W%";
E 2
I 2
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 3
E 2
 *
I 2
D 3
 *	%W%	%G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
 */
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

/*
E 2
 * return broken down time
 *
 * calling sequence:
 *	integer time, t[9]
 *	call gmtime(time, t)
 * where:
 *	time is a system time. (see time(3F))
 *	t will receive the broken down time assuming GMT.
 *	(see ctime(3))
 */

int *gmtime();

gmtime_(clock, t)
long *clock; long *t;
{
	int i;
	int *g;

	g = gmtime(clock);
	for (i=0; i<9; i++)
		*t++ = *g++;
}
E 1
