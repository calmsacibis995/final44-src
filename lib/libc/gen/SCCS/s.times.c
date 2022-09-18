h33982
s 00002/00002/00039
d D 8.1 93/06/04 12:06:31 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00015/00024
d D 5.4 90/08/27 20:35:08 bostic 6 5
c rewrite from scratch to look like clock(3); return offset from CUT
e
s 00013/00020/00026
d D 5.3 90/08/27 17:44:21 bostic 5 4
c bring it back from the dead; POSIX specified it
e
s 00002/00002/00044
d D 5.2 86/03/09 19:24:13 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00037
d D 5.1 85/05/30 10:29:23 dist 3 2
c Add copyright
e
s 00002/00002/00036
d D 4.2 83/06/02 16:18:08 sam 2 1
c blech...can't type
e
s 00038/00000/00000
d D 4.1 83/05/31 00:05:45 sam 1 0
c date and time created 83/05/31 00:05:45 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
E 5
 */

D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4
E 3

I 6
#include <sys/param.h>
E 6
#include <sys/time.h>
I 5
#include <sys/times.h>
E 5
#include <sys/resource.h>

I 6
/*
 * Convert usec to clock ticks; could do (usec * CLK_TCK) / 1000000,
 * but this would overflow if we switch to nanosec.
 */
#define	CONVTCK(r)	(r.tv_sec * CLK_TCK + r.tv_usec / (1000000 / CLK_TCK))

E 6
D 5
/*
 * Backwards compatible times.
 */
struct tms {
	int	tms_utime;		/* user time */
	int	tms_stime;		/* system time */
	int	tms_cutime;		/* user time, children */
	int	tms_cstime;		/* system time, children */
};

E 5
I 5
clock_t
E 5
D 6
times(tmsp)
D 2
	register struct times *tmsp;
E 2
I 2
	register struct tms *tmsp;
E 6
I 6
times(tp)
	register struct tms *tp;
E 6
E 2
{
	struct rusage ru;
I 5
D 6
	clock_t scale60();
E 6
I 6
	struct timeval t;
E 6
E 5

	if (getrusage(RUSAGE_SELF, &ru) < 0)
D 5
		return (-1);
E 5
I 5
		return ((clock_t)-1);
E 5
D 2
	tmsp->tms_utime = scale60(&ru.ru_time);
E 2
I 2
D 6
	tmsp->tms_utime = scale60(&ru.ru_utime);
E 2
	tmsp->tms_stime = scale60(&ru.ru_stime);
E 6
I 6
	tp->tms_utime = CONVTCK(ru.ru_utime);
	tp->tms_stime = CONVTCK(ru.ru_stime);
E 6
	if (getrusage(RUSAGE_CHILDREN, &ru) < 0)
D 5
		return (-1);
E 5
I 5
		return ((clock_t)-1);
E 5
D 6
	tmsp->tms_cutime = scale60(&ru.ru_utime);
	tmsp->tms_cstime = scale60(&ru.ru_stime);
D 5
	return (0);
E 5
I 5
	return ((clock_t)0);
E 5
}

D 5
static
E 5
I 5
static clock_t
E 5
scale60(tvp)
	register struct timeval *tvp;
{
D 5

E 5
	return (tvp->tv_sec * 60 + tvp->tv_usec / 16667);
E 6
I 6
	tp->tms_cutime = CONVTCK(ru.ru_utime);
	tp->tms_cstime = CONVTCK(ru.ru_stime);
	if (gettimeofday(&t, (struct timezone *)0))
		return ((clock_t)-1);
	return ((clock_t)(CONVTCK(t)));
E 6
}
E 1
