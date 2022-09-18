h05554
s 00002/00002/00104
d D 8.5 95/05/04 15:25:37 mckusick 25 24
c POSIX says timeval's have two long's
e
s 00002/00002/00104
d D 8.4 95/03/20 23:53:33 mckusick 24 23
c proper definition for timespec
e
s 00005/00001/00101
d D 8.3 95/01/09 18:16:13 cgd 23 22
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00006/00004/00096
d D 8.2 94/07/10 22:57:07 bostic 22 20
c changes for 64-bit machines; include <sys/types.h> to avoid breakage
e
s 00004/00004/00096
d R 8.2 94/07/10 22:55:25 bostic 21 20
c changes for 64-bit machines
e
s 00002/00002/00098
d D 8.1 93/06/02 19:55:53 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00009/00094
d D 7.11 92/12/27 09:35:16 bostic 19 18
c fix timercmp to work for all operators
e
s 00009/00000/00094
d D 7.10 92/12/02 19:11:30 bostic 18 17
c add timespec/timeval conversion macros
e
s 00004/00004/00090
d D 7.9 92/06/19 22:58:48 mckusick 17 16
c phz => stathz
e
s 00008/00000/00086
d D 7.8 92/04/21 10:29:10 mckusick 16 15
c add definition for POSIX.4 timespec
e
s 00010/00000/00076
d D 7.7 92/03/09 16:56:59 mckusick 15 14
c struct clockinfo definition moves from kernel.h to time.h
e
s 00015/00001/00061
d D 7.6 91/02/22 12:12:30 donn 14 13
c Prototype declarations.
e
s 00003/00003/00059
d D 7.5 91/02/05 17:03:56 bostic 13 12
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00061
d D 7.4 90/06/28 22:01:21 bostic 12 11
c new copyright notice
e
s 00014/00003/00058
d D 7.3 89/08/08 11:26:46 bostic 11 10
c new versions of time calls; add Berkeley specific copyright
e
s 00005/00000/00056
d D 7.2 89/05/09 16:18:57 mckusick 10 9
c protect against multiple inclusions
e
s 00001/00001/00055
d D 7.1 86/06/04 23:29:20 mckusick 9 8
c 4.3BSD release version
e
s 00001/00000/00055
d D 6.4 85/06/24 00:11:41 kre 8 7
c Added defn of DST_CAN
e
s 00007/00001/00048
d D 6.3 85/06/08 15:09:32 mckusick 7 6
c Add copyright
e
s 00001/00017/00048
d D 6.2 85/03/13 16:28:34 mckusick 6 5
c break out user part of time.h
e
s 00000/00000/00065
d D 6.1 83/07/29 06:14:20 sam 5 4
c 4.2 distribution
e
s 00004/00001/00061
d D 4.4 83/07/09 14:37:48 sam 4 3
c keep europe happy
e
s 00002/00000/00060
d D 4.3 83/06/10 21:26:21 sam 3 2
c let others know
e
s 00001/00000/00059
d D 4.2 83/05/21 16:02:21 sam 2 1
c bloody australian time zone
e
s 00059/00000/00000
d D 4.1 83/02/10 18:32:26 sam 1 0
c date and time created 83/02/10 18:32:26 by sam
e
u
U
t
T
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
D 11
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 20
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 12
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
 *
 *	%W% (Berkeley) %G%
 */
E 7

I 10
D 13
#ifndef _TIME_
#define _TIME_
E 13
I 13
#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_
E 13

I 22
#include <sys/types.h>

E 22
E 10
/*
 * Structure returned by gettimeofday(2) system call,
 * and used in other calls.
 */
struct timeval {
D 22
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
E 22
I 22
D 25
	int32_t	tv_sec;		/* seconds */
	int32_t	tv_usec;	/* and microseconds */
E 25
I 25
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
E 25
E 22
};

I 16
/*
 * Structure defined by POSIX.4 to be like a timeval.
 */
struct timespec {
D 22
	long	ts_sec;		/* seconds */
	long	ts_nsec;	/* and nanoseconds */
E 22
I 22
D 24
	int32_t	ts_sec;		/* seconds */
	int32_t	ts_nsec;	/* and nanoseconds */
E 24
I 24
	time_t	ts_sec;		/* seconds */
	long	ts_nsec;	/* and nanoseconds */
E 24
E 22
};

I 18
#define	TIMEVAL_TO_TIMESPEC(tv, ts) {					\
	(ts)->ts_sec = (tv)->tv_sec;					\
	(ts)->ts_nsec = (tv)->tv_usec * 1000;				\
}
#define	TIMESPEC_TO_TIMEVAL(tv, ts) {					\
	(tv)->tv_sec = (ts)->ts_sec;					\
	(tv)->tv_usec = (ts)->ts_nsec / 1000;				\
}

E 18
E 16
struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};
#define	DST_NONE	0	/* not on dst */
D 4
#define	DST_USA		1	/* usa style dst */
E 4
I 4
#define	DST_USA		1	/* USA style dst */
E 4
I 2
#define	DST_AUST	2	/* Australian style dst */
I 4
#define	DST_WET		3	/* Western European dst */
#define	DST_MET		4	/* Middle European dst */
#define	DST_EET		5	/* Eastern European dst */
I 8
#define	DST_CAN		6	/* Canada */
E 8
E 4
E 2

D 19
/*
 * Operations on timevals.
I 3
 *
 * NB: timercmp does not work for >= or <=.
E 3
 */
#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp, uvp, cmp)	\
	((tvp)->tv_sec cmp (uvp)->tv_sec || \
	 (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
E 19
I 19
/* Operations on timevals. */
E 19
#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0
I 19
#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp, uvp, cmp)						\
	(((tvp)->tv_sec == (uvp)->tv_sec) ?				\
	    ((tvp)->tv_usec cmp (uvp)->tv_usec) :			\
	    ((tvp)->tv_sec cmp (uvp)->tv_sec))
E 19

/*
 * Names of the interval timers, and structure
 * defining a timer setting.
 */
#define	ITIMER_REAL	0
#define	ITIMER_VIRTUAL	1
#define	ITIMER_PROF	2

struct	itimerval {
	struct	timeval it_interval;	/* timer interval */
	struct	timeval it_value;	/* current value */
};

I 15
/*
 * Getkerninfo clock information structure
 */
struct clockinfo {
D 17
	int hz;		/* clock frequency */
	int tick;	/* micro-seconds per hz tick */
	int phz;	/* alternate clock frequency */
	int profhz;	/* profiling clock frequency */
E 17
I 17
	int	hz;		/* clock frequency */
	int	tick;		/* micro-seconds per hz tick */
	int	stathz;		/* statistics clock frequency */
	int	profhz;		/* profiling clock frequency */
E 17
};

E 15
D 6
/*
 * Structure returned by gmtime and localtime calls (see ctime(3)).
 */
struct tm {
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};

E 6
D 23
#ifndef KERNEL
E 23
I 23
#ifdef KERNEL
int	itimerfix __P((struct timeval *tv));
int	itimerdecr __P((struct itimerval *itp, int usec));
void	microtime __P((struct timeval *tv));
#else /* !KERNEL */
E 23
D 6
extern	struct tm *gmtime(), *localtime();
extern	char *asctime(), *ctime();
E 6
I 6
#include <time.h>
E 6
D 14
#endif
E 14
I 14

#ifndef _POSIX_SOURCE
#include <sys/cdefs.h>

__BEGIN_DECLS
int	adjtime __P((const struct timeval *, struct timeval *));
int	getitimer __P((int, struct itimerval *));
int	gettimeofday __P((struct timeval *, struct timezone *));
int	setitimer __P((int, const struct itimerval *, struct itimerval *));
int	settimeofday __P((const struct timeval *, const struct timezone *));
int	utimes __P((const char *, const struct timeval *));
__END_DECLS
#endif /* !POSIX */

#endif /* !KERNEL */
E 14
I 10

D 13
#endif /* _TIME_ */
E 13
I 13
#endif /* !_SYS_TIME_H_ */
E 13
E 10
E 1
