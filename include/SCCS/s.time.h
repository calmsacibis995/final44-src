h32517
s 00005/00000/00073
d D 8.3 94/01/21 16:53:06 bostic 19 18
c add USL's copyright notice
e
s 00002/00000/00071
d D 8.2 94/01/04 13:39:37 bostic 18 17
c include <machine/limits.h>; POSIX.1 requires time.h to have CLK_TCK
e
s 00002/00002/00069
d D 8.1 93/06/02 20:07:16 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00009/00062
d D 5.13 92/06/22 21:27:45 bostic 16 15
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00001/00001/00070
d D 5.12 91/03/09 17:56:00 bostic 15 14
c create {hp300,i386,tahoe,vax}/include/ansi.h
e
s 00002/00002/00069
d D 5.11 91/02/22 17:06:57 donn 14 12
c Fix some overeager use of 'const'.
e
s 00001/00001/00070
d R 5.11 91/02/22 17:02:56 donn 13 12
c mktime()'s argument isn't const.
e
s 00012/00005/00059
d D 5.10 91/02/22 08:03:40 donn 12 11
c Added new prototype declarations and cleaned up.
e
s 00020/00025/00044
d D 5.9 91/02/05 17:10:59 bostic 11 10
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00068
d D 5.8 90/12/18 10:51:47 bostic 10 9
c kernel reorg
e
s 00002/00000/00067
d D 5.7 90/08/27 18:32:35 bostic 9 8
c add clock, POSIX.1 times is going to use it
e
s 00020/00001/00047
d D 5.6 90/06/23 12:11:46 bostic 8 7
c ANSI typedef's; no longer need sys/types.h, though
e
s 00001/00001/00047
d D 5.5 90/06/23 11:56:51 bostic 7 6
c add c_plusplus to STDC ifdef
e
s 00001/00011/00047
d D 5.4 90/06/01 14:01:51 bostic 6 5
c new copyright notice
e
s 00002/00000/00056
d D 5.3 90/03/13 17:32:41 mckusick 5 4
c have to include <sys/types.h>
e
s 00023/00003/00033
d D 5.2 90/03/06 16:58:24 bostic 4 3
c add ANSI C prototypes
e
s 00028/00019/00008
d D 5.1 89/03/08 15:45:57 bostic 3 2
c from scratch, for ANSI, yank to 5.1
e
s 00009/00001/00018
d D 1.2 87/03/04 17:28:35 bostic 2 1
c added Robert Elz's additions for new time package
e
s 00019/00000/00000
d D 1.1 85/03/13 16:30:25 mckusick 1 0
c date and time created 85/03/13 16:30:25 by mckusick
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
/*
D 3
 * Copyright (c) 1983, 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 17
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 19
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 19
E 17
E 3
 *
I 3
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
E 3
 *	%W% (Berkeley) %G%
 */
E 2

I 11
#ifndef _TIME_H_
#define	_TIME_H_

E 11
I 5
D 8
#include <sys/types.h>
E 8
I 8
D 10
#include <machine/machtypes.h>
E 10
I 10
D 15
#include <machine/types.h>
E 15
I 15
#include <machine/ansi.h>
E 15
E 10

#ifndef	NULL
#define	NULL	0
#endif

D 16
#ifdef	_CLOCK_T_
typedef	_CLOCK_T_	clock_t;
#undef	_CLOCK_T_
E 16
I 16
#ifdef	_BSD_CLOCK_T_
typedef	_BSD_CLOCK_T_	clock_t;
#undef	_BSD_CLOCK_T_
E 16
#endif

D 16
#ifdef	_TIME_T_
typedef	_TIME_T_	time_t;
#undef	_TIME_T_
E 16
I 16
#ifdef	_BSD_TIME_T_
typedef	_BSD_TIME_T_	time_t;
#undef	_BSD_TIME_T_
E 16
#endif

D 16
#ifdef	_SIZE_T_
typedef	_SIZE_T_	size_t;
#undef	_SIZE_T_
E 16
I 16
#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
E 16
#endif
E 8

E 5
D 3
/*
 * Structure returned by gmtime and localtime calls (see ctime(3)).
 */
E 3
struct tm {
D 3
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
I 2
	long	tm_gmtoff;
	char	*tm_zone;
E 3
I 3
	int	tm_sec;		/* seconds after the minute [0-60] */
	int	tm_min;		/* minutes after the hour [0-59] */
	int	tm_hour;	/* hours since midnight [0-23] */
	int	tm_mday;	/* day of the month [1-31] */
	int	tm_mon;		/* months since January [0-11] */
	int	tm_year;	/* years since 1900 */
	int	tm_wday;	/* days since Sunday [0-6] */
	int	tm_yday;	/* days since January 1 [0-365] */
	int	tm_isdst;	/* Daylight Savings Time flag */
	long	tm_gmtoff;	/* offset from CUT in seconds */
	char	*tm_zone;	/* timezone abbreviation */
E 3
E 2
};

I 18
#include <machine/limits.h>	/* Include file containing CLK_TCK. */

E 18
D 3
extern	struct tm *gmtime(), *localtime();
extern	char *asctime(), *ctime();
E 3
I 3
D 4
void tzset();
struct tm *gmtime(), *localtime();
char *asctime(), *ctime(), *timezone();
E 4
I 4
D 7
#ifdef __STDC__
E 7
I 7
D 11
#if __STDC__ || c_plusplus
E 7
extern struct tm *gmtime(const time_t *);
extern struct tm *localtime(const time_t *);
extern time_t mktime(const struct tm *);
extern time_t time(time_t *);
I 9
extern clock_t clock(void);
E 9
extern double difftime(const time_t, const time_t);
extern char *asctime(const struct tm *);
extern char *ctime(const time_t *);
extern char *timezone(int , int);
extern void tzset(void);
extern void tzsetwall(void);
#else
extern struct tm *gmtime();
extern struct tm *localtime();
I 9
extern clock_t clock();
E 9
extern time_t mktime();
extern time_t time();
extern double difftime();
extern char *asctime();
extern char *ctime();
extern char *timezone();
extern void tzset();
extern void tzsetwall();
#endif 
E 11
I 11
#include <sys/cdefs.h>

__BEGIN_DECLS
I 12
char *asctime __P((const struct tm *));
clock_t clock __P((void));
char *ctime __P((const time_t *));
D 14
double difftime __P((const time_t, const time_t));
E 14
I 14
double difftime __P((time_t, time_t));
E 14
E 12
struct tm *gmtime __P((const time_t *));
struct tm *localtime __P((const time_t *));
D 14
time_t mktime __P((const struct tm *));
E 14
I 14
time_t mktime __P((struct tm *));
E 14
I 12
size_t strftime __P((char *, size_t, const char *, const struct tm *));
E 12
time_t time __P((time_t *));
D 12
clock_t clock __P((void));
double difftime __P((const time_t, const time_t));
char *asctime __P((const struct tm *));
char *ctime __P((const time_t *));
char *timezone __P((int , int));
E 12
I 12

#ifndef _ANSI_SOURCE
E 12
void tzset __P((void));
I 12
#endif /* not ANSI */

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
char *timezone __P((int, int));
E 12
void tzsetwall __P((void));
I 12
#endif /* neither ANSI nor POSIX */
E 12
__END_DECLS

#endif /* !_TIME_H_ */
E 11
E 4
E 3
E 1
