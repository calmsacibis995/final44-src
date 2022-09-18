h17602
s 00002/00002/00018
d D 8.1 93/06/06 15:19:20 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00011
d D 1.4 90/04/09 18:27:44 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00000/00012
d D 1.3 81/03/07 16:03:02 mckusic 3 2
c merge in onyx changes
e
s 00003/00001/00009
d D 1.2 81/03/07 00:31:47 mckusic 2 1
c fix negative rounding
e
s 00010/00000/00000
d D 1.1 80/10/30 00:35:30 mckusick 1 0
c date and time created 80/10/30 00:35:30 by mckusick
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

I 3
long
E 3
ROUND(value)

	double	value;
{
D 2
	return (long)(value + 0.5);
E 2
I 2
	if (value >= 0.0)
		return (long)(value + 0.5);
	return (long)(value - 0.5);
E 2
}
E 1
