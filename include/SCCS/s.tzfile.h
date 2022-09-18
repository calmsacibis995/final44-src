h59502
s 00002/00002/00123
d D 8.1 93/06/02 20:07:24 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00003/00118
d D 5.10 91/04/03 16:41:17 bostic 10 9
c protect all user-level include files against reinclusion
e
s 00001/00001/00120
d D 5.9 90/06/11 14:53:51 bostic 9 8
c fix copyright
e
s 00001/00011/00120
d D 5.8 90/06/01 14:02:04 bostic 8 7
c new copyright notice
e
s 00002/00002/00129
d D 5.7 90/02/12 12:22:06 bostic 7 6
c one more time; move TZDIR to /usr/share, leave localtime in /etc
e
s 00001/00001/00130
d D 5.6 89/08/21 22:25:32 bostic 6 5
c move TZDIR back to /etc, expect to have high number of accesses
e
s 00002/00001/00129
d D 5.5 89/04/12 10:34:30 bostic 5 4
c mv zoneinfo
e
s 00058/00046/00072
d D 5.4 89/03/12 13:31:14 bostic 4 3
c latest Olson/Harris time package
e
s 00019/00001/00099
d D 5.3 88/07/06 09:59:26 bostic 3 2
c install approved copyright notice
e
s 00001/00005/00099
d D 5.2 87/03/04 17:27:42 bostic 2 1
c remove Berkeley copyright
e
s 00104/00000/00000
d D 5.1 87/03/04 16:55:11 bostic 1 0
c date and time created 87/03/04 16:55:11 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
E 2
I 2
D 3
 *	%W% tzfile.h %G%
E 3
I 3
D 11
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
D 9
 * Arthur Olson.
E 9
I 9
 * Arthur David Olson of the National Cancer Institute.
E 9
 *
D 8
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
E 3
E 2
 */

D 10
/*
** Information about time zone files.
*/
E 10
I 10
#ifndef _TZFILE_H_
#define	_TZFILE_H_
E 10

I 10
/*
 * Information about time zone files.
 */
E 10
D 4
#define	TZDIR		"/etc/zoneinfo"	/* Time zone object file directory */
#define	TZDEFAULT	"localtime"
E 4
I 4
D 5
#define TZDIR		"/etc/zoneinfo"	/* Time zone object file directory */
E 5
I 5
			/* Time zone object file directory */
D 6
#define TZDIR		"/usr/share/zoneinfo"
E 6
I 6
D 7
#define TZDIR		"/etc/zoneinfo"
E 6
E 5
#define TZDEFAULT	"localtime"
E 7
I 7
#define TZDIR		"/usr/share/zoneinfo"
#define TZDEFAULT	"/etc/localtime"
E 7
#define TZDEFRULES	"posixrules"
E 4

/*
** Each file begins with. . .
*/

struct tzhead {
D 4
	char	tzh_reserved[32];	/* reserved for future use */
E 4
I 4
	char	tzh_reserved[24];	/* reserved for future use */
	char	tzh_ttisstdcnt[4];	/* coded number of trans. time flags */
	char	tzh_leapcnt[4];		/* coded number of leap seconds */
E 4
	char	tzh_timecnt[4];		/* coded number of transition times */
	char	tzh_typecnt[4];		/* coded number of local time types */
	char	tzh_charcnt[4];		/* coded number of abbr. chars */
};

/*
** . . .followed by. . .
**
**	tzh_timecnt (char [4])s		coded transition times a la time(2)
**	tzh_timecnt (unsigned char)s	types of local time starting at above
**	tzh_typecnt repetitions of
**		one (char [4])		coded GMT offset in seconds
D 4
**		one (unsigned char)	used to set tm_isdt
E 4
I 4
**		one (unsigned char)	used to set tm_isdst
E 4
**		one (unsigned char)	that's an abbreviation list index
D 4
**	tzh_charcnt (char)s		'\0'-terminated zone abbreviaton strings
E 4
I 4
**	tzh_charcnt (char)s		'\0'-terminated zone abbreviations
**	tzh_leapcnt repetitions of
**		one (char [4])		coded leap second transition times
**		one (char [4])		total correction after above
**	tzh_ttisstdcnt (char)s		indexed by type; if TRUE, transition
**					time is standard time, if FALSE,
**					transition time is wall clock time
**					if absent, transition times are
**					assumed to be wall clock time
E 4
*/

/*
** In the current implementation, "tzset()" refuses to deal with files that
** exceed any of the limits below.
*/

/*
** The TZ_MAX_TIMES value below is enough to handle a bit more than a
** year's worth of solar time (corrected daily to the nearest second) or
** 138 years of Pacific Presidential Election time
** (where there are three time zone transitions every fourth year).
*/
D 4
#define	TZ_MAX_TIMES	370
E 4
I 4
#define TZ_MAX_TIMES	370
E 4

D 4
#define	NOSOLAR			/* We currently don't handle solar time */
E 4
I 4
#define NOSOLAR			/* 4BSD doesn't currently handle solar time */
E 4

D 4
#ifndef	NOSOLAR
#define	TZ_MAX_TYPES	256	/* Limited by what (unsigned char)'s can hold */
#else /* !NOSOLAR */
#define	TZ_MAX_TYPES	10	/* Maximum number of local time types */
#endif /* !NOSOLAR */
E 4
I 4
#ifndef NOSOLAR
#define TZ_MAX_TYPES	256	/* Limited by what (unsigned char)'s can hold */
#else
#define TZ_MAX_TYPES	10	/* Maximum number of local time types */
#endif
E 4

D 4
#define	TZ_MAX_CHARS	50	/* Maximum number of abbreviation characters */
E 4
I 4
#define TZ_MAX_CHARS	50	/* Maximum number of abbreviation characters */
E 4

D 4
#define	SECS_PER_MIN	60
#define	MINS_PER_HOUR	60
#define	HOURS_PER_DAY	24
#define	DAYS_PER_WEEK	7
#define	DAYS_PER_NYEAR	365
#define	DAYS_PER_LYEAR	366
#define	SECS_PER_HOUR	(SECS_PER_MIN * MINS_PER_HOUR)
#define	SECS_PER_DAY	((long) SECS_PER_HOUR * HOURS_PER_DAY)
#define	MONS_PER_YEAR	12
E 4
I 4
#define	TZ_MAX_LEAPS	50	/* Maximum number of leap second corrections */
E 4

D 4
#define	TM_SUNDAY	0
#define	TM_MONDAY	1
#define	TM_TUESDAY	2
#define	TM_WEDNESDAY	3
#define	TM_THURSDAY	4
#define	TM_FRIDAY	5
#define	TM_SATURDAY	6
E 4
I 4
#define SECSPERMIN	60
#define MINSPERHOUR	60
#define HOURSPERDAY	24
#define DAYSPERWEEK	7
#define DAYSPERNYEAR	365
#define DAYSPERLYEAR	366
#define SECSPERHOUR	(SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY	((long) SECSPERHOUR * HOURSPERDAY)
#define MONSPERYEAR	12
E 4

D 4
#define	TM_JANUARY	0
#define	TM_FEBRUARY	1
#define	TM_MARCH	2
#define	TM_APRIL	3
#define	TM_MAY		4
#define	TM_JUNE		5
#define	TM_JULY		6
#define	TM_AUGUST	7
#define	TM_SEPTEMBER	8
#define	TM_OCTOBER	9
#define	TM_NOVEMBER	10
#define	TM_DECEMBER	11
#define	TM_SUNDAY	0
E 4
I 4
#define TM_SUNDAY	0
#define TM_MONDAY	1
#define TM_TUESDAY	2
#define TM_WEDNESDAY	3
#define TM_THURSDAY	4
#define TM_FRIDAY	5
#define TM_SATURDAY	6
E 4

D 4
#define	TM_YEAR_BASE	1900
E 4
I 4
#define TM_JANUARY	0
#define TM_FEBRUARY	1
#define TM_MARCH	2
#define TM_APRIL	3
#define TM_MAY		4
#define TM_JUNE		5
#define TM_JULY		6
#define TM_AUGUST	7
#define TM_SEPTEMBER	8
#define TM_OCTOBER	9
#define TM_NOVEMBER	10
#define TM_DECEMBER	11
E 4

D 4
#define	EPOCH_YEAR	1970
#define	EPOCH_WDAY	TM_THURSDAY
E 4
I 4
#define TM_YEAR_BASE	1900
E 4

I 4
#define EPOCH_YEAR	1970
#define EPOCH_WDAY	TM_THURSDAY

E 4
/*
** Accurate only for the past couple of centuries;
** that will probably do.
*/

D 4
#define	isleap(y) (((y) % 4) == 0 && ((y) % 100) != 0 || ((y) % 400) == 0)
E 4
I 4
#define isleap(y) (((y) % 4) == 0 && ((y) % 100) != 0 || ((y) % 400) == 0)
I 10

#endif /* !_TZFILE_H_ */
E 10
E 4
E 1
