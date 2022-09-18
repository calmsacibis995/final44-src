h47525
s 00002/00002/00033
d D 8.1 93/06/06 15:17:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00009/00027
d D 1.3 90/06/29 17:04:15 mckusick 3 2
c check in for Kirk; use getrusage, not times()
e
s 00009/00002/00027
d D 1.2 90/04/09 18:26:57 bostic 2 1
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00029/00000/00000
d D 1.1 80/10/30 00:34:12 mckusick 1 0
c date and time created 80/10/30 00:34:12 by mckusick
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
E 2

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include "h00vars.h"
I 3
#include <sys/time.h>
#include <sys/resource.h>
E 3

PCEXIT(code)

	int	code;
{
D 3
	struct	{
		long	usr_time;
		long	sys_time;
		long	child_usr_time;
		long	child_sys_time;
		} tbuf;
E 3
	double l;
I 3
	struct rusage ru;
E 3

	PCLOSE(GLVL);
	PFLUSH();
	if (_stcnt > 0) {
D 3
		times(&tbuf);
		l = tbuf.usr_time;
		l = l / HZ;
E 3
I 3
		if (getrusage(RUSAGE_SELF, &ru) < 0)
			exit(code);
		l = ru.ru_utime.tv_usec;
		l /= 1000000;
		l += ru.ru_utime.tv_sec;
E 3
		fprintf(stderr, "\n%1ld %s %04.2f seconds cpu time.\n",
				_stcnt, "statements executed in", l);
	}
	exit(code);
}
E 1
