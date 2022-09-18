h39013
s 00002/00002/00049
d D 8.1 93/06/04 16:21:52 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00002/00037
d D 5.4 93/05/13 16:50:49 torek 5 4
c obey local timezone file (a bit gross, but it seems to work)
e
s 00006/00005/00033
d D 5.3 91/04/19 19:08:02 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00036
d D 5.2 86/03/09 19:22:50 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00029
d D 5.1 85/05/30 10:26:47 dist 2 1
c Add copyright
e
s 00030/00000/00000
d D 4.1 83/05/31 00:19:54 sam 1 0
c date and time created 83/05/31 00:19:54 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
E 4
 */

D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3
E 2

#include <sys/types.h>
#include <sys/time.h>

/*
 * Backwards compatible ftime.
 */

/* from old timeb.h */
struct timeb {
	time_t	time;
	u_short	millitm;
	short	timezone;
	short	dstflag;
};

ftime(tp)
	register struct timeb *tp;
{
	struct timeval t;
	struct timezone tz;
I 5
	struct tm *tm;
	time_t zero;
E 5

	if (gettimeofday(&t, &tz) < 0)
		return (-1);
	tp->time = t.tv_sec;
	tp->millitm = t.tv_usec / 1000;
D 5
	tp->timezone = tz.tz_minuteswest;
	tp->dstflag = tz.tz_dsttime;
E 5
I 5
	if ((tm = localtime(&tp->time)) == NULL) {
		/* in the absence of anything better, use kernel's timezone */
		tp->timezone = tz.tz_minuteswest;
		tp->dstflag = tz.tz_dsttime;
	} else {
		tp->dstflag = tm->tm_isdst;
		if (tm->tm_isdst) {	/* tm_gmtoff has an offset applied */
			zero = 0;	/* try 0 and hope for the best */
			tp->timezone = -localtime(&zero)->tm_gmtoff / 60;
		} else
			tp->timezone = -tm->tm_gmtoff / 60;
	}
E 5
}
E 1
