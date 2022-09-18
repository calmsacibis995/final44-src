h32279
s 00002/00002/00029
d D 8.1 93/06/06 15:15:54 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00022
d D 1.3 90/04/09 18:26:19 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00015/00003/00009
d D 1.2 81/03/07 15:55:27 mckusic 2 1
c merge in onyx changes
e
s 00012/00000/00000
d D 1.1 80/10/30 00:33:10 mckusick 1 0
c date and time created 80/10/30 00:33:10 by mckusick
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

I 2
long
E 2
EXPO(value)

D 2
	long	value;
E 2
I 2
	double	value;
E 2
{
D 2
	if (value == 0)
E 2
I 2
	register int retval;
	register char *cp;
	char sign, buf[30];
	extern char *index();

	if (value == 0.0)
E 2
		return 0;
D 2
	return ((value & ~0xffff8000) >> 7) - 128;
E 2
I 2
	sprintf(buf, "%.1e", value);
	cp = index(buf, 'e') + 1;
	sign = *cp++;
	retval = 0;
	while (*cp)
		retval = retval * 10 + *cp++ - '0';
	return sign == '-' ? -retval : retval;
E 2
}
E 1
