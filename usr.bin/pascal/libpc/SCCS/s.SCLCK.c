h37332
s 00001/00000/00023
d D 8.2 94/05/23 15:37:36 mckusick 6 5
c needs types.h
e
s 00002/00002/00021
d D 8.1 93/06/06 15:19:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00003/00016
d D 1.4 90/06/29 17:04:16 mckusick 4 3
c check in for Kirk; use getrusage, not times()
e
s 00009/00002/00010
d D 1.3 90/04/09 18:27:47 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00000/00011
d D 1.2 81/03/07 16:03:31 mckusic 2 1
c merge in onyx changes
e
s 00011/00000/00000
d D 1.1 80/10/30 00:35:35 mckusick 1 0
c date and time created 80/10/30 00:35:35 by mckusick
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
E 3

D 3
static char sccsid[] = "%Z%%M% %I% %G%";
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

I 6
#include <sys/types.h>
E 6
I 4
#include <sys/time.h>
#include <sys/resource.h>

E 4
I 2
long
E 2
SCLCK()
{
D 4
	long	tim[4];
E 4
I 4
	struct rusage ru;
E 4

D 4
	times(tim);
	return (tim[1] * 50) / 3;
E 4
I 4
	if (getrusage(RUSAGE_SELF, &ru) < 0)
		return (-1);
	return (ru.ru_stime.tv_sec * 1000 + ru.ru_stime.tv_usec / 1000);
E 4
}
E 1
