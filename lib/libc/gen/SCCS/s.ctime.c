h20172
s 00005/00000/01350
d D 8.2 94/03/20 15:28:03 bostic 35 34
c setting all of the fields to INT_MIN took forever to run
c fix from From: ado@elsie.nci.nih.gov (Arthur David Olson)
e
s 00002/00002/01348
d D 8.1 93/06/04 12:00:56 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00006/01348
d D 5.27 93/01/07 13:47:43 bostic 33 32
c normalize routine bug; bug report net2/lib/4
e
s 00002/00001/01352
d D 5.26 91/02/23 19:49:35 donn 32 31
c Add include files to get prototype declarations, and fix bugs found.
e
s 00000/00002/01353
d D 5.25 91/02/13 11:56:06 bostic 31 30
c const, volatile defined in sys/cdefs.h
e
s 00000/00001/01355
d D 5.24 91/01/20 15:14:17 bostic 30 29
c don't need FILENAME_MAX any more, it's in stdio.h
e
s 00001/00003/01355
d D 5.23 90/06/22 19:07:19 bostic 29 28
c fill in tm_gmtoff!
e
s 00001/00001/01357
d D 5.22 90/06/11 14:54:14 bostic 28 27
c fix copyright
e
s 00001/00011/01357
d D 5.21 90/06/01 14:09:16 bostic 27 26
c new copyright notice
e
s 00001/00010/01367
d D 5.20 90/02/02 17:59:57 bostic 26 25
c no reason for this access call
e
s 00001/00002/01376
d D 5.19 89/12/14 12:30:29 bostic 25 24
c don't bother using prototypes if it's not ANSI C; breaks gcc -traditional
e
s 00002/00002/01376
d D 5.18 89/09/09 15:33:45 bostic 24 23
c changes from Arthur Olson -- if TZ wrong, just use UTC
e
s 00001/00001/01377
d D 5.17 89/08/02 16:01:36 bostic 23 22
c ANS says that any positive value indicates that DST is on, not just 1
e
s 00000/00031/01378
d D 5.16 89/03/16 20:34:41 bostic 22 21
c remove offtime, timegm, timeoff
e
s 01217/00211/00192
d D 5.15 89/03/12 16:32:29 bostic 21 20
c latest Olson/Harris time package
e
s 00003/00003/00400
d D 5.14 88/07/06 10:00:37 bostic 20 19
c make tzone file copyright notices consistent
e
s 00010/00005/00393
d D 5.13 88/06/27 17:34:03 bostic 19 18
c install approved copyright notice
e
s 00012/00003/00386
d D 5.12 87/12/03 22:44:58 bostic 18 17
c put reasonable header on it
e
s 00002/00002/00387
d D 5.11 87/04/13 07:46:26 bostic 17 16
c update from Arthur Olson; bug report 4.3BSD/lib/52
e
s 00001/00001/00388
d D 5.10 87/04/06 12:37:07 bostic 16 15
c minor printf format error
e
s 00002/00002/00387
d D 5.9 87/04/01 10:00:21 bostic 15 14
c changed tztab to _tztab
e
s 00002/00002/00387
d D 5.8 87/03/28 11:33:02 bostic 14 13
c put LIBC_SCCS back
e
s 00034/00008/00355
d D 5.7 87/03/28 11:27:01 bostic 13 12
c new time package
e
s 00311/00285/00052
d D 5.6 87/03/11 18:51:33 bostic 12 11
c added new time package routines
e
s 00002/00002/00335
d D 5.5 86/03/09 19:45:24 donn 11 10
c added LIBC_SCCS condition for sccs ids
e
s 00006/00002/00331
d D 5.4 86/01/03 10:03:59 bloom 10 9
c cut down the number of unnecessary calls to gettimeofday
e
s 00001/00001/00332
d D 5.3 85/10/25 16:00:53 mckusick 9 8
c lets get it right (from ist!dt)
e
s 00020/00011/00313
d D 5.2 85/06/24 00:14:21 kre 8 7
c Fixed (?) European DST rules, and added a special set for
c Canada without the 74/75 peculiarities (Tilbrook says this is so...)
e
s 00008/00001/00316
d D 5.1 85/06/05 12:12:03 mckusick 7 6
c Add copyright
e
s 00008/00008/00309
d D 4.6 84/08/29 15:13:14 ralph 6 5
c fix ctime(time 0), year > 2100 (can't be generated with long).
e
s 00001/00001/00316
d D 4.5 84/03/16 15:53:43 karels 5 4
c handle negative times
e
s 00028/00003/00289
d D 4.4 83/07/09 14:02:56 sam 4 3
c european timezone rules
e
s 00004/00002/00288
d D 4.3 83/07/01 18:32:31 sam 3 2
c include fixes
e
s 00070/00026/00220
d D 4.2 83/06/10 22:42:43 sam 2 1
c from robert
e
s 00246/00000/00000
d D 4.1 80/12/21 16:39:33 wnj 1 0
c date and time created 80/12/21 16:39:33 by wnj
e
u
U
t
T
I 7
/*
D 13
 * Copyright (c) 1980 Regents of the University of California.
E 13
I 13
D 21
 * Copyright (c) 1987 Regents of the University of California.
E 21
I 21
D 34
 * Copyright (c) 1987, 1989 Regents of the University of California.
E 21
E 13
D 18
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
 * All rights reserved.
E 34
I 34
 * Copyright (c) 1987, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 34
 *
I 20
 * This code is derived from software contributed to Berkeley by
D 28
 * Arthur Olson.
E 28
I 28
 * Arthur David Olson of the National Cancer Institute.
E 28
 *
E 20
D 27
 * Redistribution and use in source and binary forms are permitted
D 19
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 19
I 19
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
E 27
I 27
 * %sccs.include.redist.c%
E 27
E 19
D 20
 *
 * This code was supplied by Arthur Olson, originally, and has been
 * slightly modified at the University of California.
E 20
E 18
 */

E 7
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 11
#ifndef lint
E 11
I 11
D 13
#if defined(LIBC_SCCS) && !defined(lint)
E 13
I 13
D 14
#ifndef lint
E 14
I 14
#if defined(LIBC_SCCS) && !defined(lint)
E 14
E 13
E 11
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
D 11
#endif not lint
E 11
I 11
D 13
#endif LIBC_SCCS and not lint
E 13
I 13
D 14
#endif
E 14
I 14
D 18
#endif LIBC_SCCS and not lint
E 18
I 18
#endif /* LIBC_SCCS and not lint */
E 18
E 14
E 13
E 11

E 7
E 3
D 12
/*
 * This routine converts time as follows.
 * The epoch is 0000 Jan 1 1970 GMT.
 * The argument time is in seconds since then.
 * The localtime(t) entry returns a pointer to an array
 * containing
 *  seconds (0-59)
 *  minutes (0-59)
 *  hours (0-23)
 *  day of month (1-31)
 *  month (0-11)
 *  year-1970
 *  weekday (0-6, Sun is 0)
 *  day of the year
 *  daylight savings flag
 *
 * The routine calls the system to determine the local
 * timezone and whether Daylight Saving Time is permitted locally.
D 4
 * (DST is then determined by the current US standard rules)
 * There is a table that accounts for the peculiarities
 * undergone by daylight time in 1974-1975.
E 4
I 4
 * (DST is then determined by the current local rules)
E 4
 *
 * The routine does not work
 * in Saudi Arabia which runs on Solar time.
 *
 * asctime(tvec))
 * where tvec is produced by localtime
 * returns a ptr to a character string
 * that has the ascii time in the form
D 6
 *	Thu Jan 01 00:00:00 1970n0\\
 *	01234567890123456789012345
E 6
I 6
 *	Thu Jan 01 00:00:00 1970\n\0
 *	0123456789012345678901234 5
E 6
 *	0	  1	    2
 *
 * ctime(t) just calls localtime, then asctime.
 */
E 12
I 12
D 21
#include "sys/param.h"
I 13
#include "sys/time.h"
E 13
#include "tzfile.h"
E 21
I 21
/*
** Leap second handling from Bradley White (bww@k.gp.cs.cmu.edu).
** POSIX-style TZ environment variable handling from Guy Harris
** (guy@auspex.com).
*/
E 21
D 13
#include "time.h"
E 13
E 12

D 3
#include <time.h>
E 3
I 3
D 12
#include <sys/time.h>
E 3
#include <sys/types.h>
#include <sys/timeb.h>

static	char	cbuf[26];
static	int	dmsize[12] =
E 12
I 12
D 21
char *
ctime(t)
time_t *t;
E 12
{
D 12
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31
};
E 12
I 12
	struct tm	*localtime();
	char	*asctime();
E 21
I 21
/*LINTLIBRARY*/
E 21
E 12

I 12
D 21
	return(asctime(localtime(t)));
}
E 21
I 21
#include <sys/param.h>
#include <fcntl.h>
#include <time.h>
#include <tzfile.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
I 32
#include <unistd.h>
E 32
E 21

E 12
D 21
/*
D 12
 * The following table is used for 1974 and 1975 and
 * gives the day number of the first day after the Sunday of the
 * change.
 */
D 2
static struct {
E 2
I 2
struct dstab {
	int	dayyr;
E 2
	int	daylb;
	int	dayle;
D 2
} daytab[] = {
	5,	333,	/* 1974: Jan 6 - last Sun. in Nov */
	58,	303,	/* 1975: Last Sun. in Feb - last Sun in Oct */
E 2
};
E 12
I 12
** A la X3J11
*/
E 21
I 21
#ifdef __STDC__
#include <stdlib.h>
E 21
E 12

I 2
D 12
static struct dstab usdaytab[] = {
	1974,	5,	333,	/* 1974: Jan 6 - last Sun. in Nov */
	1975,	58,	303,	/* 1975: Last Sun. in Feb - last Sun in Oct */
	0,	119,	303,	/* all other years: end Apr - end Oct */
};
static struct dstab ausdaytab[] = {
	1970,	400,	0,	/* 1970: no daylight saving at all */
	1971,	303,	0,	/* 1971: daylight saving from Oct 31 */
	1972,	303,	58,	/* 1972: Jan 1 -> Feb 27 & Oct 31 -> dec 31 */
	0,	303,	65,	/* others: -> Mar 7, Oct 31 -> */
};
E 12
I 12
D 21
char *
asctime(timeptr)
register struct tm *	timeptr;
{
	static char	wday_name[DAYS_PER_WEEK][3] = {
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
	static char	mon_name[MONS_PER_YEAR][3] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	static char	result[26];
E 21
I 21
#define P(s)		s
#define alloc_size_t	size_t
#define qsort_size_t	size_t
#define fread_size_t	size_t
#define fwrite_size_t	size_t
E 21
E 12

I 4
D 12
/*
 * The European tables ... based on hearsay
 * Believed correct for:
D 8
 *	WE:	Great Britain, Ireland, Portugal
E 8
I 8
 *	WE:	Great Britain, Portugal?
E 8
 *	ME:	Belgium, Luxembourg, Netherlands, Denmark, Norway,
 *		Austria, Poland, Czechoslovakia, Sweden, Switzerland,
 *		DDR, DBR, France, Spain, Hungary, Italy, Jugoslavia
I 8
 *		Finland (EE timezone, but ME dst rules)
E 8
 * Eastern European dst is unknown, we'll make it ME until someone speaks up.
D 8
 *	EE:	Bulgaria, Finland, Greece, Rumania, Turkey, Western Russia
E 8
I 8
 *	EE:	Bulgaria, Greece, Rumania, Turkey, Western Russia
 *
 * Ireland is unpredictable.  (Years when Easter Sunday just happens ...)
 * Years before 1983 are suspect.
E 8
 */
static struct dstab wedaytab[] = {
D 8
	1983,	86,	303,	/* 1983: end March - end Oct */
	1984,	86,	303,	/* 1984: end March - end Oct */
	1985,	86,	303,	/* 1985: end March - end Oct */
	0,	400,	0,	/* others: no daylight saving at all ??? */
E 8
I 8
	1983,	89,	296,	/* 1983: end March - end Oct */
	0,	89,	303,	/* others: end March - end Oct */
E 8
};
E 12
I 12
D 16
	(void) sprintf(result, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
E 16
I 16
D 21
	(void) sprintf(result, "%.3s %.3s%3d %02d:%02d:%02d %d\n",
E 16
		wday_name[timeptr->tm_wday],
		mon_name[timeptr->tm_mon],
		timeptr->tm_mday, timeptr->tm_hour,
		timeptr->tm_min, timeptr->tm_sec,
		TM_YEAR_BASE + timeptr->tm_year);
	return result;
}
E 21
I 21
#else /* !defined __STDC__ */
E 21
E 12

I 21
D 25
#define ASTERISK	*
#define P(s)		(/ASTERISK s ASTERISK/)
E 25
I 25
#define P(s)		()
E 25
D 31
#define const
#define volatile
E 31

typedef char *		genericptr_t;
typedef unsigned	alloc_size_t;
typedef int		qsort_size_t;
typedef int		fread_size_t;
typedef int		fwrite_size_t;

extern char *	calloc();
extern char *	malloc();
extern char *	realloc();
extern char *	getenv();

#endif /* !defined __STDC__ */

extern time_t	time();

D 30
#define FILENAME_MAX	MAXPATHLEN
E 30
#define ACCESS_MODE	O_RDONLY
#define OPEN_MODE	O_RDONLY

#ifndef WILDABBR
/*
** Someone might make incorrect use of a time zone abbreviation:
**	1.	They might reference tzname[0] before calling tzset (explicitly
**	 	or implicitly).
**	2.	They might reference tzname[1] before calling tzset (explicitly
**	 	or implicitly).
**	3.	They might reference tzname[1] after setting to a time zone
**		in which Daylight Saving Time is never observed.
**	4.	They might reference tzname[0] after setting to a time zone
**		in which Standard Time is never observed.
**	5.	They might reference tm.TM_ZONE after calling offtime.
** What's best to do in the above cases is open to debate;
** for now, we just set things up so that in any of the five cases
** WILDABBR is used.  Another possibility:  initialize tzname[0] to the
** string "tzname[0] used before set", and similarly for the other cases.
** And another:  initialize tzname[0] to "ERA", with an explanation in the
** manual page of what this "time zone abbreviation" means (doing this so
** that tzname[0] has the "normal" length of three characters).
*/
#define WILDABBR	"   "
#endif /* !defined WILDABBR */

E 21
D 12
static struct dstab medaytab[] = {
D 8
	1983,	86,	272,	/* 1983: end March - end Sep */
	1984,	86,	272,	/* 1984: end March - end Sep */
	1985,	86,	272,	/* 1985: end March - end Sep */
	0,	400,	0,	/* others: no daylight saving at all ??? */
E 8
I 8
	1983,	89,	296,	/* 1983: end March - end Oct */
	0,	89,	272,	/* others: end March - end Sep */
E 12
I 12
#ifndef TRUE
#define TRUE		1
#define FALSE		0
D 21
#endif /* !TRUE */
E 21
I 21
#endif /* !defined TRUE */
E 21

D 21
extern char *		getenv();
extern char *		strcpy();
extern char *		strcat();
struct tm *		offtime();
E 21
I 21
static const char GMT[] = "GMT";
E 21

struct ttinfo {				/* time type information */
	long		tt_gmtoff;	/* GMT offset in seconds */
	int		tt_isdst;	/* used to set tm_isdst */
	int		tt_abbrind;	/* abbreviation list index */
I 21
	int		tt_ttisstd;	/* TRUE if transition is std time */
E 21
E 12
E 8
};

I 21
struct lsinfo {				/* leap second information */
	time_t		ls_trans;	/* transition time */
	long		ls_corr;	/* correction to apply */
};

E 21
I 8
D 12
/*
 * Canada, same as the US, except no early 70's fluctuations.
 * Can this really be right ??
 */
static struct dstab candaytab[] = {
	0,	119,	303,	/* all years: end Apr - end Oct */
E 12
I 12
struct state {
I 21
	int		leapcnt;
E 21
	int		timecnt;
	int		typecnt;
	int		charcnt;
	time_t		ats[TZ_MAX_TIMES];
	unsigned char	types[TZ_MAX_TIMES];
	struct ttinfo	ttis[TZ_MAX_TYPES];
D 21
	char		chars[TZ_MAX_CHARS + 1];
E 21
I 21
	char		chars[(TZ_MAX_CHARS + 1 > sizeof GMT) ?
				TZ_MAX_CHARS + 1 : sizeof GMT];
	struct lsinfo	lsis[TZ_MAX_LEAPS];
E 21
E 12
};

E 8
E 4
D 12
static struct dayrules {
	int		dst_type;	/* number obtained from system */
	int		dst_hrs;	/* hours to add when dst on */
	struct	dstab *	dst_rules;	/* one of the above */
	enum {STH,NTH}	dst_hemi;	/* southern, northern hemisphere */
} dayrules [] = {
	DST_USA,	1,	usdaytab,	NTH,
	DST_AUST,	1,	ausdaytab,	STH,
I 4
	DST_WET,	1,	wedaytab,	NTH,
	DST_MET,	1,	medaytab,	NTH,
	DST_EET,	1,	medaytab,	NTH,	/* XXX */
I 8
	DST_CAN,	1,	candaytab,	NTH,
E 8
E 4
	-1,
E 12
I 12
D 21
static struct state	s;
E 21
I 21
struct rule {
	int		r_type;		/* type of rule--see below */
	int		r_day;		/* day number of rule */
	int		r_week;		/* week number of rule */
	int		r_mon;		/* month number of rule */
	long		r_time;		/* transition time of rule */
};
E 21

D 21
static int		tz_is_set;
E 21
I 21
#define	JULIAN_DAY		0	/* Jn - Julian day */
#define	DAY_OF_YEAR		1	/* n - day of year */
#define	MONTH_NTH_DAY_OF_WEEK	2	/* Mm.n.d - month, week, day of week */
E 21

I 21
/*
** Prototypes for static functions.
*/

static long		detzcode P((const char * codep));
static const char *	getzname P((const char * strp));
static const char *	getnum P((const char * strp, int * nump, int min,
				int max));
static const char *	getsecs P((const char * strp, long * secsp));
static const char *	getoffset P((const char * strp, long * offsetp));
static const char *	getrule P((const char * strp, struct rule * rulep));
static void		gmtload P((struct state * sp));
static void		gmtsub P((const time_t * timep, long offset,
				struct tm * tmp));
static void		localsub P((const time_t * timep, long offset,
				struct tm * tmp));
static void		normalize P((int * tensptr, int * unitsptr, int base));
static void		settzname P((void));
static time_t		time1 P((struct tm * tmp, void (* funcp)(),
				long offset));
static time_t		time2 P((struct tm *tmp, void (* funcp)(),
				long offset, int * okayp));
static void		timesub P((const time_t * timep, long offset,
				const struct state * sp, struct tm * tmp));
static int		tmcomp P((const struct tm * atmp,
				const struct tm * btmp));
static time_t		transtime P((time_t janfirst, int year,
				const struct rule * rulep, long offset));
static int		tzload P((const char * name, struct state * sp));
static int		tzparse P((const char * name, struct state * sp,
				int lastditch));

#ifdef ALL_STATE
static struct state *	lclptr;
static struct state *	gmtptr;
#endif /* defined ALL_STATE */

#ifndef ALL_STATE
static struct state	lclmem;
static struct state	gmtmem;
#define lclptr		(&lclmem)
#define gmtptr		(&gmtmem)
#endif /* State Farm */

static int		lcl_is_set;
static int		gmt_is_set;

E 21
char *			tzname[2] = {
D 21
	"GMT",
	"GMT"
E 21
I 21
	WILDABBR,
	WILDABBR
E 21
E 12
};

E 2
D 12
struct tm	*gmtime();
char		*ct_numb();
struct tm	*localtime();
char	*ctime();
char	*ct_num();
char	*asctime();
E 12
I 12
#ifdef USG_COMPAT
time_t			timezone = 0;
int			daylight = 0;
D 21
#endif /* USG_COMPAT */
E 21
I 21
#endif /* defined USG_COMPAT */
E 21
E 12

I 21
#ifdef ALTZONE
time_t			altzone = 0;
#endif /* defined ALTZONE */

E 21
D 12
char *
ctime(t)
D 2
long *t;
E 2
I 2
D 6
unsigned long *t;
E 6
I 6
time_t *t;
E 12
I 12
static long
detzcode(codep)
D 21
char *	codep;
E 21
I 21
const char * const	codep;
E 21
E 12
E 6
E 2
{
D 12
	return(asctime(localtime(t)));
E 12
I 12
	register long	result;
	register int	i;

	result = 0;
	for (i = 0; i < 4; ++i)
		result = (result << 8) | (codep[i] & 0xff);
	return result;
E 12
}

D 12
struct tm *
localtime(tim)
D 2
long *tim;
E 2
I 2
D 6
unsigned long *tim;
E 6
I 6
time_t *tim;
E 12
I 12
D 21
static
tzload(name)
register char *	name;
E 21
I 21
static void
settzname()
E 21
E 12
E 6
E 2
{
D 12
	register int dayno;
	register struct tm *ct;
D 2
	register daylbegin, daylend;
	long copyt;
	struct timeb systime;
E 2
I 2
	register dalybeg, daylend;
	register struct dayrules *dr;
	register struct dstab *ds;
	int year;
D 6
	unsigned long copyt;
E 6
I 6
	time_t copyt;
E 6
	struct timeval curtime;
D 10
	struct timezone zone;
E 10
I 10
	static struct timezone zone;
	static int init = 0;
E 12
I 12
D 21
	register int	i;
	register int	fid;
E 21
I 21
	register const struct state * const	sp = lclptr;
	register int				i;
E 21
E 12
E 10
E 2

D 2
	ftime(&systime);
	copyt = *tim - (long)systime.timezone*60;
E 2
I 2
D 10
	gettimeofday(&curtime, &zone);
E 10
I 10
D 12
	if (!init) {
		gettimeofday(&curtime, &zone);
		init++;
E 12
I 12
D 21
	if (name == 0 && (name = TZDEFAULT) == 0)
E 21
I 21
	tzname[0] = WILDABBR;
	tzname[1] = WILDABBR;
#ifdef USG_COMPAT
	daylight = 0;
	timezone = 0;
#endif /* defined USG_COMPAT */
#ifdef ALTZONE
	altzone = 0;
#endif /* defined ALTZONE */
#ifdef ALL_STATE
	if (sp == NULL) {
		tzname[0] = tzname[1] = GMT;
		return;
	}
#endif /* defined ALL_STATE */
	for (i = 0; i < sp->typecnt; ++i) {
		register const struct ttinfo * const	ttisp = &sp->ttis[i];

		tzname[ttisp->tt_isdst] =
			(char *) &sp->chars[ttisp->tt_abbrind];
#ifdef USG_COMPAT
		if (ttisp->tt_isdst)
			daylight = 1;
		if (i == 0 || !ttisp->tt_isdst)
			timezone = -(ttisp->tt_gmtoff);
#endif /* defined USG_COMPAT */
#ifdef ALTZONE
		if (i == 0 || ttisp->tt_isdst)
			altzone = -(ttisp->tt_gmtoff);
#endif /* defined ALTZONE */
	}
	/*
	** And to get the latest zone names into tzname. . .
	*/
	for (i = 0; i < sp->timecnt; ++i) {
		register const struct ttinfo * const	ttisp =
							&sp->ttis[sp->types[i]];

		tzname[ttisp->tt_isdst] =
			(char *) &sp->chars[ttisp->tt_abbrind];
	}
}

static int
tzload(name, sp)
register const char *		name;
register struct state * const	sp;
{
	register const char *	p;
	register int		i;
	register int		fid;

	if (name == NULL && (name = TZDEFAULT) == NULL)
E 21
		return -1;
	{
D 21
		register char *	p;
		register int	doaccess;
		char		fullname[MAXPATHLEN];
E 21
I 21
D 26
		register int 	doaccess;
E 26
		char		fullname[FILENAME_MAX + 1];
E 21

I 21
		if (name[0] == ':')
			++name;
E 21
D 26
		doaccess = name[0] == '/';
		if (!doaccess) {
E 26
I 26
		if (name[0] != '/') {
E 26
D 21
			if ((p = TZDIR) == 0)
E 21
I 21
			if ((p = TZDIR) == NULL)
E 21
				return -1;
			if ((strlen(p) + strlen(name) + 1) >= sizeof fullname)
				return -1;
			(void) strcpy(fullname, p);
			(void) strcat(fullname, "/");
			(void) strcat(fullname, name);
D 26
			/*
			** Set doaccess if '.' (as in "../") shows up in name.
			*/
D 21
			while (*name != '\0')
				if (*name++ == '.')
					doaccess = TRUE;
E 21
I 21
			if (strchr(name, '.') != NULL)
				doaccess = TRUE;
E 26
E 21
			name = fullname;
		}
D 21
		if (doaccess && access(name, 4) != 0)
E 21
I 21
D 26
		if (doaccess && access(name, ACCESS_MODE) != 0)
E 21
			return -1;
E 26
D 21
		if ((fid = open(name, 0)) == -1)
E 21
I 21
		if ((fid = open(name, OPEN_MODE)) == -1)
E 21
			return -1;
E 12
	}
E 10
D 6
	copyt = *tim - (unsigned long)zone.tz_minuteswest*60;
E 6
I 6
D 12
	copyt = *tim - (time_t)zone.tz_minuteswest*60;
E 6
E 2
	ct = gmtime(&copyt);
	dayno = ct->tm_yday;
D 2
	daylbegin = 119;	/* last Sun in Apr */
	daylend = 303;		/* Last Sun in Oct */
	if (ct->tm_year==74 || ct->tm_year==75) {
		daylbegin = daytab[ct->tm_year-74].daylb;
		daylend = daytab[ct->tm_year-74].dayle;
	}
	daylbegin = sunday(ct, daylbegin);
	daylend = sunday(ct, daylend);
	if (systime.dstflag &&
	    (dayno>daylbegin || (dayno==daylbegin && ct->tm_hour>=2)) &&
	    (dayno<daylend || (dayno==daylend && ct->tm_hour<1))) {
		copyt += 1*60*60;
E 2
I 2
	for (dr = dayrules; dr->dst_type >= 0; dr++)
		if (dr->dst_type == zone.tz_dsttime)
			break;
	if (dr->dst_type >= 0) {
		year = ct->tm_year + 1900;
		for (ds = dr->dst_rules; ds->dayyr; ds++)
			if (ds->dayyr == year)
				break;
		dalybeg = ds->daylb;	/* first Sun after dst starts */
		daylend = ds->dayle;	/* first Sun after dst ends */
		dalybeg = sunday(ct, dalybeg);
		daylend = sunday(ct, daylend);
		switch (dr->dst_hemi) {
		case NTH:
		    if (!(
		       (dayno>dalybeg || (dayno==dalybeg && ct->tm_hour>=2)) &&
		       (dayno<daylend || (dayno==daylend && ct->tm_hour<1))
		    ))
			    return(ct);
		    break;
		case STH:
		    if (!(
		       (dayno>dalybeg || (dayno==dalybeg && ct->tm_hour>=2)) ||
		       (dayno<daylend || (dayno==daylend && ct->tm_hour<2))
		    ))
			    return(ct);
		    break;
		default:
		    return(ct);
E 12
I 12
	{
D 21
		register char *			p;
		register struct tzhead *	tzhp;
		char				buf[sizeof s];
E 21
I 21
		register const struct tzhead *	tzhp;
		char				buf[sizeof *sp + sizeof *tzhp];
		int				ttisstdcnt;
E 21

		i = read(fid, buf, sizeof buf);
		if (close(fid) != 0 || i < sizeof *tzhp)
			return -1;
		tzhp = (struct tzhead *) buf;
D 21
		s.timecnt = (int) detzcode(tzhp->tzh_timecnt);
		s.typecnt = (int) detzcode(tzhp->tzh_typecnt);
		s.charcnt = (int) detzcode(tzhp->tzh_charcnt);
		if (s.timecnt > TZ_MAX_TIMES ||
			s.typecnt == 0 ||
			s.typecnt > TZ_MAX_TYPES ||
			s.charcnt > TZ_MAX_CHARS)
E 21
I 21
		ttisstdcnt = (int) detzcode(tzhp->tzh_ttisstdcnt);
		sp->leapcnt = (int) detzcode(tzhp->tzh_leapcnt);
		sp->timecnt = (int) detzcode(tzhp->tzh_timecnt);
		sp->typecnt = (int) detzcode(tzhp->tzh_typecnt);
		sp->charcnt = (int) detzcode(tzhp->tzh_charcnt);
		if (sp->leapcnt < 0 || sp->leapcnt > TZ_MAX_LEAPS ||
			sp->typecnt <= 0 || sp->typecnt > TZ_MAX_TYPES ||
			sp->timecnt < 0 || sp->timecnt > TZ_MAX_TIMES ||
			sp->charcnt < 0 || sp->charcnt > TZ_MAX_CHARS ||
			(ttisstdcnt != sp->typecnt && ttisstdcnt != 0))
E 21
				return -1;
		if (i < sizeof *tzhp +
D 21
			s.timecnt * (4 + sizeof (char)) +
			s.typecnt * (4 + 2 * sizeof (char)) +
			s.charcnt * sizeof (char))
E 21
I 21
			sp->timecnt * (4 + sizeof (char)) +
			sp->typecnt * (4 + 2 * sizeof (char)) +
			sp->charcnt * sizeof (char) +
			sp->leapcnt * 2 * 4 +
			ttisstdcnt * sizeof (char))
E 21
				return -1;
		p = buf + sizeof *tzhp;
D 21
		for (i = 0; i < s.timecnt; ++i) {
			s.ats[i] = detzcode(p);
E 21
I 21
		for (i = 0; i < sp->timecnt; ++i) {
			sp->ats[i] = detzcode(p);
E 21
			p += 4;
E 12
		}
D 12
	        copyt += dr->dst_hrs*60*60;
E 2
		ct = gmtime(&copyt);
		ct->tm_isdst++;
E 12
I 12
D 21
		for (i = 0; i < s.timecnt; ++i)
			s.types[i] = (unsigned char) *p++;
		for (i = 0; i < s.typecnt; ++i) {
E 21
I 21
		for (i = 0; i < sp->timecnt; ++i) {
			sp->types[i] = (unsigned char) *p++;
			if (sp->types[i] >= sp->typecnt)
				return -1;
		}
		for (i = 0; i < sp->typecnt; ++i) {
E 21
			register struct ttinfo *	ttisp;

D 21
			ttisp = &s.ttis[i];
E 21
I 21
			ttisp = &sp->ttis[i];
E 21
			ttisp->tt_gmtoff = detzcode(p);
			p += 4;
			ttisp->tt_isdst = (unsigned char) *p++;
I 21
			if (ttisp->tt_isdst != 0 && ttisp->tt_isdst != 1)
				return -1;
E 21
			ttisp->tt_abbrind = (unsigned char) *p++;
I 21
			if (ttisp->tt_abbrind < 0 ||
				ttisp->tt_abbrind > sp->charcnt)
					return -1;
E 21
		}
D 21
		for (i = 0; i < s.charcnt; ++i)
			s.chars[i] = *p++;
		s.chars[i] = '\0';	/* ensure '\0' at end */
E 21
I 21
		for (i = 0; i < sp->charcnt; ++i)
			sp->chars[i] = *p++;
		sp->chars[i] = '\0';	/* ensure '\0' at end */
		for (i = 0; i < sp->leapcnt; ++i) {
			register struct lsinfo *	lsisp;

			lsisp = &sp->lsis[i];
			lsisp->ls_trans = detzcode(p);
			p += 4;
			lsisp->ls_corr = detzcode(p);
			p += 4;
		}
		for (i = 0; i < sp->typecnt; ++i) {
			register struct ttinfo *	ttisp;

			ttisp = &sp->ttis[i];
			if (ttisstdcnt == 0)
				ttisp->tt_ttisstd = FALSE;
			else {
				ttisp->tt_ttisstd = *p++;
				if (ttisp->tt_ttisstd != TRUE &&
					ttisp->tt_ttisstd != FALSE)
						return -1;
			}
		}
E 21
E 12
	}
I 21
	return 0;
}

static const int	mon_lengths[2][MONSPERYEAR] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const int	year_lengths[2] = {
	DAYSPERNYEAR, DAYSPERLYEAR
};

/*
** Given a pointer into a time zone string, scan until a character that is not
** a valid character in a zone name is found.  Return a pointer to that
** character.
*/

static const char *
getzname(strp)
register const char *	strp;
{
	register char	c;

	while ((c = *strp) != '\0' && !isdigit(c) && c != ',' && c != '-' &&
		c != '+')
			++strp;
	return strp;
}

/*
** Given a pointer into a time zone string, extract a number from that string.
** Check that the number is within a specified range; if it is not, return
** NULL.
** Otherwise, return a pointer to the first character not part of the number.
*/

static const char *
getnum(strp, nump, min, max)
register const char *	strp;
int * const		nump;
const int		min;
const int		max;
{
	register char	c;
	register int	num;

	if (strp == NULL || !isdigit(*strp))
		return NULL;
	num = 0;
	while ((c = *strp) != '\0' && isdigit(c)) {
		num = num * 10 + (c - '0');
		if (num > max)
			return NULL;	/* illegal value */
		++strp;
	}
	if (num < min)
		return NULL;		/* illegal value */
	*nump = num;
	return strp;
}

/*
** Given a pointer into a time zone string, extract a number of seconds,
** in hh[:mm[:ss]] form, from the string.
** If any error occurs, return NULL.
** Otherwise, return a pointer to the first character not part of the number
** of seconds.
*/

static const char *
getsecs(strp, secsp)
register const char *	strp;
long * const		secsp;
{
	int	num;

	strp = getnum(strp, &num, 0, HOURSPERDAY);
	if (strp == NULL)
		return NULL;
	*secsp = num * SECSPERHOUR;
	if (*strp == ':') {
		++strp;
		strp = getnum(strp, &num, 0, MINSPERHOUR - 1);
		if (strp == NULL)
			return NULL;
		*secsp += num * SECSPERMIN;
		if (*strp == ':') {
			++strp;
			strp = getnum(strp, &num, 0, SECSPERMIN - 1);
			if (strp == NULL)
				return NULL;
			*secsp += num;
		}
	}
	return strp;
}

/*
** Given a pointer into a time zone string, extract an offset, in
** [+-]hh[:mm[:ss]] form, from the string.
** If any error occurs, return NULL.
** Otherwise, return a pointer to the first character not part of the time.
*/

static const char *
getoffset(strp, offsetp)
register const char *	strp;
long * const		offsetp;
{
	register int	neg;

	if (*strp == '-') {
		neg = 1;
		++strp;
	} else if (isdigit(*strp) || *strp++ == '+')
		neg = 0;
	else	return NULL;		/* illegal offset */
	strp = getsecs(strp, offsetp);
	if (strp == NULL)
		return NULL;		/* illegal time */
	if (neg)
		*offsetp = -*offsetp;
	return strp;
}

/*
** Given a pointer into a time zone string, extract a rule in the form
** date[/time].  See POSIX section 8 for the format of "date" and "time".
** If a valid rule is not found, return NULL.
** Otherwise, return a pointer to the first character not part of the rule.
*/

static const char *
getrule(strp, rulep)
const char *			strp;
register struct rule * const	rulep;
{
	if (*strp == 'J') {
		/*
		** Julian day.
		*/
		rulep->r_type = JULIAN_DAY;
		++strp;
		strp = getnum(strp, &rulep->r_day, 1, DAYSPERNYEAR);
	} else if (*strp == 'M') {
		/*
		** Month, week, day.
		*/
		rulep->r_type = MONTH_NTH_DAY_OF_WEEK;
		++strp;
		strp = getnum(strp, &rulep->r_mon, 1, MONSPERYEAR);
		if (strp == NULL)
			return NULL;
		if (*strp++ != '.')
			return NULL;
		strp = getnum(strp, &rulep->r_week, 1, 5);
		if (strp == NULL)
			return NULL;
		if (*strp++ != '.')
			return NULL;
		strp = getnum(strp, &rulep->r_day, 0, DAYSPERWEEK - 1);
	} else if (isdigit(*strp)) {
		/*
		** Day of year.
		*/
		rulep->r_type = DAY_OF_YEAR;
		strp = getnum(strp, &rulep->r_day, 0, DAYSPERLYEAR - 1);
	} else	return NULL;		/* invalid format */
	if (strp == NULL)
		return NULL;
	if (*strp == '/') {
		/*
		** Time specified.
		*/
		++strp;
		strp = getsecs(strp, &rulep->r_time);
	} else	rulep->r_time = 2 * SECSPERHOUR;	/* default = 2:00:00 */
	return strp;
}

/*
** Given the Epoch-relative time of January 1, 00:00:00 GMT, in a year, the
** year, a rule, and the offset from GMT at the time that rule takes effect,
** calculate the Epoch-relative time that rule takes effect.
*/

static time_t
transtime(janfirst, year, rulep, offset)
const time_t				janfirst;
const int				year;
register const struct rule * const	rulep;
const long				offset;
{
	register int	leapyear;
	register time_t	value;
	register int	i;
	int		d, m1, yy0, yy1, yy2, dow;

	leapyear = isleap(year);
	switch (rulep->r_type) {

	case JULIAN_DAY:
		/*
		** Jn - Julian day, 1 == January 1, 60 == March 1 even in leap
		** years.
		** In non-leap years, or if the day number is 59 or less, just
		** add SECSPERDAY times the day number-1 to the time of
		** January 1, midnight, to get the day.
		*/
		value = janfirst + (rulep->r_day - 1) * SECSPERDAY;
		if (leapyear && rulep->r_day >= 60)
			value += SECSPERDAY;
		break;

	case DAY_OF_YEAR:
		/*
		** n - day of year.
		** Just add SECSPERDAY times the day number to the time of
		** January 1, midnight, to get the day.
		*/
		value = janfirst + rulep->r_day * SECSPERDAY;
		break;

	case MONTH_NTH_DAY_OF_WEEK:
		/*
		** Mm.n.d - nth "dth day" of month m.
		*/
		value = janfirst;
		for (i = 0; i < rulep->r_mon - 1; ++i)
			value += mon_lengths[leapyear][i] * SECSPERDAY;

		/*
		** Use Zeller's Congruence to get day-of-week of first day of
		** month.
		*/
		m1 = (rulep->r_mon + 9) % 12 + 1;
		yy0 = (rulep->r_mon <= 2) ? (year - 1) : year;
		yy1 = yy0 / 100;
		yy2 = yy0 % 100;
		dow = ((26 * m1 - 2) / 10 +
			1 + yy2 + yy2 / 4 + yy1 / 4 - 2 * yy1) % 7;
		if (dow < 0)
			dow += DAYSPERWEEK;

		/*
		** "dow" is the day-of-week of the first day of the month.  Get
		** the day-of-month (zero-origin) of the first "dow" day of the
		** month.
		*/
		d = rulep->r_day - dow;
		if (d < 0)
			d += DAYSPERWEEK;
		for (i = 1; i < rulep->r_week; ++i) {
			if (d + DAYSPERWEEK >=
				mon_lengths[leapyear][rulep->r_mon - 1])
					break;
			d += DAYSPERWEEK;
		}

		/*
		** "d" is the day-of-month (zero-origin) of the day we want.
		*/
		value += d * SECSPERDAY;
		break;
	}

E 21
D 12
	return(ct);
E 12
I 12
	/*
D 21
	** Check that all the local time type indices are valid.
E 21
I 21
	** "value" is the Epoch-relative time of 00:00:00 GMT on the day in
	** question.  To get the Epoch-relative time of the specified local
	** time on that day, add the transition time and the current offset
	** from GMT.
E 21
	*/
D 21
	for (i = 0; i < s.timecnt; ++i)
		if (s.types[i] >= s.typecnt)
E 21
I 21
	return value + rulep->r_time + offset;
}

/*
** Given a POSIX section 8-style TZ string, fill in the rule tables as
** appropriate.
*/

static int
tzparse(name, sp, lastditch)
const char *			name;
register struct state * const	sp;
const int			lastditch;
{
	const char *			stdname;
	const char *			dstname;
	int				stdlen;
	int				dstlen;
	long				stdoffset;
	long				dstoffset;
	register time_t *		atp;
	register unsigned char *	typep;
	register char *			cp;
	register int			load_result;

	stdname = name;
	if (lastditch) {
		stdlen = strlen(name);	/* length of standard zone name */
		name += stdlen;
		if (stdlen >= sizeof sp->chars)
			stdlen = (sizeof sp->chars) - 1;
	} else {
		name = getzname(name);
		stdlen = name - stdname;
		if (stdlen < 3)
E 21
			return -1;
D 21
	/*
	** Check that all abbreviation indices are valid.
	*/
	for (i = 0; i < s.typecnt; ++i)
		if (s.ttis[i].tt_abbrind >= s.charcnt)
E 21
I 21
	}
	if (*name == '\0')
D 24
		stdoffset = 0;
E 24
I 24
		return -1;
E 24
	else {
		name = getoffset(name, &stdoffset);
		if (name == NULL)
E 21
			return -1;
D 21
	/*
	** Set tzname elements to initial values.
	*/
	tzname[0] = tzname[1] = &s.chars[0];
#ifdef USG_COMPAT
D 17
	timezone = s.ttis[0].tt_gmtoff;
E 17
I 17
	timezone = -s.ttis[0].tt_gmtoff;
E 17
	daylight = 0;
#endif /* USG_COMPAT */
	for (i = 1; i < s.typecnt; ++i) {
		register struct ttinfo *	ttisp;
E 21
I 21
	}
	load_result = tzload(TZDEFRULES, sp);
	if (load_result != 0)
		sp->leapcnt = 0;		/* so, we're off a little */
	if (*name != '\0') {
		dstname = name;
		name = getzname(name);
		dstlen = name - dstname;	/* length of DST zone name */
		if (dstlen < 3)
			return -1;
		if (*name != '\0' && *name != ',' && *name != ';') {
			name = getoffset(name, &dstoffset);
			if (name == NULL)
				return -1;
		} else	dstoffset = stdoffset - SECSPERHOUR;
		if (*name == ',' || *name == ';') {
			struct rule	start;
			struct rule	end;
			register int	year;
			register time_t	janfirst;
			time_t		starttime;
			time_t		endtime;
E 21

D 21
		ttisp = &s.ttis[i];
		if (ttisp->tt_isdst) {
			tzname[1] = &s.chars[ttisp->tt_abbrind];
#ifdef USG_COMPAT
			daylight = 1;
#endif /* USG_COMPAT */ 
E 21
I 21
			++name;
			if ((name = getrule(name, &start)) == NULL)
				return -1;
			if (*name++ != ',')
				return -1;
			if ((name = getrule(name, &end)) == NULL)
				return -1;
			if (*name != '\0')
				return -1;
			sp->typecnt = 2;	/* standard time and DST */
			/*
			** Two transitions per year, from EPOCH_YEAR to 2037.
			*/
			sp->timecnt = 2 * (2037 - EPOCH_YEAR + 1);
			if (sp->timecnt > TZ_MAX_TIMES)
				return -1;
			sp->ttis[0].tt_gmtoff = -dstoffset;
			sp->ttis[0].tt_isdst = 1;
			sp->ttis[0].tt_abbrind = stdlen + 1;
			sp->ttis[1].tt_gmtoff = -stdoffset;
			sp->ttis[1].tt_isdst = 0;
			sp->ttis[1].tt_abbrind = 0;
			atp = sp->ats;
			typep = sp->types;
			janfirst = 0;
			for (year = EPOCH_YEAR; year <= 2037; ++year) {
				starttime = transtime(janfirst, year, &start,
					stdoffset);
				endtime = transtime(janfirst, year, &end,
					dstoffset);
				if (starttime > endtime) {
					*atp++ = endtime;
					*typep++ = 1;	/* DST ends */
					*atp++ = starttime;
					*typep++ = 0;	/* DST begins */
				} else {
					*atp++ = starttime;
					*typep++ = 0;	/* DST begins */
					*atp++ = endtime;
					*typep++ = 1;	/* DST ends */
				}
				janfirst +=
					year_lengths[isleap(year)] * SECSPERDAY;
			}
E 21
		} else {
D 21
			tzname[0] = &s.chars[ttisp->tt_abbrind];
#ifdef USG_COMPAT
D 17
			timezone = ttisp->tt_gmtoff;
E 17
I 17
			timezone = -ttisp->tt_gmtoff;
E 17
#endif /* USG_COMPAT */ 
		}
	}
	return 0;
E 12
}
E 21
I 21
			int		sawstd;
			int		sawdst;
			long		stdfix;
			long		dstfix;
			long		oldfix;
			int		isdst;
			register int	i;
E 21

D 12
/*
 * The argument is a 0-origin day number.
D 9
 * The value is the day number of the first
E 9
I 9
 * The value is the day number of the last
E 9
D 8
 * Sunday on or after the day.
E 8
I 8
 * Sunday on or before the day.
E 8
 */
E 12
D 21
static
I 13
tzsetkernel()
{
	struct timeval	tv;
	struct timezone	tz;
D 15
	char	*tztab();
E 15
I 15
	char	*_tztab();
E 21
I 21
			if (*name != '\0')
				return -1;
			if (load_result != 0)
				return -1;
			/*
			** Compute the difference between the real and
			** prototype standard and summer time offsets
			** from GMT, and put the real standard and summer
			** time offsets into the rules in place of the
			** prototype offsets.
			*/
			sawstd = FALSE;
			sawdst = FALSE;
			stdfix = 0;
			dstfix = 0;
			for (i = 0; i < sp->typecnt; ++i) {
				if (sp->ttis[i].tt_isdst) {
					oldfix = dstfix;
					dstfix =
					    sp->ttis[i].tt_gmtoff + dstoffset;
					if (sawdst && (oldfix != dstfix))
						return -1;
					sp->ttis[i].tt_gmtoff = -dstoffset;
					sp->ttis[i].tt_abbrind = stdlen + 1;
					sawdst = TRUE;
				} else {
					oldfix = stdfix;
					stdfix =
					    sp->ttis[i].tt_gmtoff + stdoffset;
					if (sawstd && (oldfix != stdfix))
						return -1;
					sp->ttis[i].tt_gmtoff = -stdoffset;
					sp->ttis[i].tt_abbrind = 0;
					sawstd = TRUE;
				}
			}
			/*
			** Make sure we have both standard and summer time.
			*/
			if (!sawdst || !sawstd)
				return -1;
			/*
			** Now correct the transition times by shifting
			** them by the difference between the real and
			** prototype offsets.  Note that this difference
			** can be different in standard and summer time;
			** the prototype probably has a 1-hour difference
			** between standard and summer time, but a different
			** difference can be specified in TZ.
			*/
			isdst = FALSE;	/* we start in standard time */
			for (i = 0; i < sp->timecnt; ++i) {
				register const struct ttinfo *	ttisp;
E 21
E 15

D 21
	if (gettimeofday(&tv, &tz))
E 21
I 21
				/*
				** If summer time is in effect, and the
				** transition time was not specified as
				** standard time, add the summer time
				** offset to the transition time;
				** otherwise, add the standard time offset
				** to the transition time.
				*/
				ttisp = &sp->ttis[sp->types[i]];
				sp->ats[i] +=
					(isdst && !ttisp->tt_ttisstd) ?
						dstfix : stdfix;
				isdst = ttisp->tt_isdst;
			}
		}
	} else {
		dstlen = 0;
		sp->typecnt = 1;		/* only standard time */
		sp->timecnt = 0;
		sp->ttis[0].tt_gmtoff = -stdoffset;
		sp->ttis[0].tt_isdst = 0;
		sp->ttis[0].tt_abbrind = 0;
	}
	sp->charcnt = stdlen + 1;
	if (dstlen != 0)
		sp->charcnt += dstlen + 1;
	if (sp->charcnt > sizeof sp->chars)
E 21
		return -1;
D 21
	s.timecnt = 0;		/* UNIX counts *west* of Greenwich */
	s.ttis[0].tt_gmtoff = tz.tz_minuteswest * -SECS_PER_MIN;
	s.ttis[0].tt_abbrind = 0;
D 15
	(void)strcpy(s.chars, tztab(tz.tz_minuteswest, 0));
E 15
I 15
	(void)strcpy(s.chars, _tztab(tz.tz_minuteswest, 0));
E 15
	tzname[0] = tzname[1] = s.chars;
#ifdef USG_COMPAT
	timezone = tz.tz_minuteswest * 60;
	daylight = tz.tz_dsttime;
#endif /* USG_COMPAT */
E 21
I 21
	cp = sp->chars;
	(void) strncpy(cp, stdname, stdlen);
	cp += stdlen;
	*cp++ = '\0';
	if (dstlen != 0) {
		(void) strncpy(cp, dstname, dstlen);
		*(cp + dstlen) = '\0';
	}
E 21
	return 0;
}

D 21
static
E 13
D 12
sunday(t, d)
register struct tm *t;
register int d;
E 12
I 12
tzsetgmt()
E 21
I 21
static void
gmtload(sp)
struct state * const	sp;
E 21
E 12
{
D 12
	if (d >= 58)
		d += dysize(t->tm_year) - 365;
	return(d - (d - t->tm_yday + t->tm_wday + 700) % 7);
E 12
I 12
D 21
	s.timecnt = 0;
	s.ttis[0].tt_gmtoff = 0;
	s.ttis[0].tt_abbrind = 0;
	(void) strcpy(s.chars, "GMT");
	tzname[0] = tzname[1] = s.chars;
#ifdef USG_COMPAT
	timezone = 0;
	daylight = 0;
#endif /* USG_COMPAT */
E 21
I 21
	if (tzload(GMT, sp) != 0)
		(void) tzparse(GMT, sp, TRUE);
E 21
E 12
}

D 12
struct tm *
gmtime(tim)
D 2
long *tim;
E 2
I 2
D 6
unsigned long *tim;
E 6
I 6
time_t *tim;
E 12
I 12
void
tzset()
E 12
E 6
E 2
{
D 12
	register int d0, d1;
D 2
	long hms, day;
E 2
I 2
D 5
	unsigned long hms, day;
E 5
I 5
	long hms, day;
E 5
E 2
	register int *tp;
	static struct tm xtime;
E 12
I 12
D 21
	register char *	name;
E 21
I 21
	register const char *	name;
	void tzsetwall();
E 21
E 12

D 12
	/*
	 * break initial number into days
	 */
	hms = *tim % 86400;
	day = *tim / 86400;
	if (hms<0) {
		hms += 86400;
		day -= 1;
	}
	tp = (int *)&xtime;

	/*
	 * generate hours:minutes:seconds
	 */
	*tp++ = hms%60;
	d1 = hms/60;
	*tp++ = d1%60;
	d1 /= 60;
	*tp++ = d1;

	/*
	 * day is the day number.
	 * generate day of the week.
	 * The addend is 4 mod 7 (1/1/1970 was Thursday)
	 */

	xtime.tm_wday = (day+7340036)%7;

	/*
	 * year number
	 */
	if (day>=0) for(d1=70; day >= dysize(d1); d1++)
		day -= dysize(d1);
	else for (d1=70; day<0; d1--)
		day += dysize(d1-1);
	xtime.tm_year = d1;
	xtime.tm_yday = d0 = day;

	/*
	 * generate month
	 */

	if (dysize(d1)==366)
		dmsize[1] = 29;
	for(d1=0; d0 >= dmsize[d1]; d1++)
		d0 -= dmsize[d1];
	dmsize[1] = 28;
	*tp++ = d0+1;
	*tp++ = d1;
	xtime.tm_isdst = 0;
	return(&xtime);
E 12
I 12
D 21
	tz_is_set = TRUE;
E 21
	name = getenv("TZ");
D 13
	if (name != 0 && *name == '\0')
		tzsetgmt();		/* GMT by request */
	else if (tzload(name) != 0)
		tzsetgmt();
E 13
I 13
D 21
	if (!name || *name) {			/* did not request GMT */
		if (name && !tzload(name))	/* requested name worked */
E 21
I 21
	if (name == NULL) {
		tzsetwall();
		return;
	}
	lcl_is_set = TRUE;
#ifdef ALL_STATE
	if (lclptr == NULL) {
		lclptr = (struct state *) malloc(sizeof *lclptr);
		if (lclptr == NULL) {
			settzname();	/* all we can do */
E 21
			return;
D 21
		if (!tzload((char *)0))		/* default name worked */
E 21
I 21
		}
	}
#endif /* defined ALL_STATE */
	if (*name == '\0') {
		/*
		** User wants it fast rather than right.
		*/
		lclptr->leapcnt = 0;		/* so, we're off a little */
		lclptr->timecnt = 0;
		lclptr->ttis[0].tt_gmtoff = 0;
		lclptr->ttis[0].tt_abbrind = 0;
		(void) strcpy(lclptr->chars, GMT);
	} else if (tzload(name, lclptr) != 0)
		if (name[0] == ':' || tzparse(name, lclptr, FALSE) != 0)
D 24
			(void) tzparse(name, lclptr, TRUE);
E 24
I 24
			(void) gmtload(lclptr);
E 24
	settzname();
}

void
tzsetwall()
{
	lcl_is_set = TRUE;
#ifdef ALL_STATE
	if (lclptr == NULL) {
		lclptr = (struct state *) malloc(sizeof *lclptr);
		if (lclptr == NULL) {
			settzname();	/* all we can do */
E 21
			return;
D 21
		if (!tzsetkernel())		/* kernel guess worked */
			return;
E 21
I 21
		}
E 21
	}
D 21
	tzsetgmt();				/* GMT is default */
E 21
I 21
#endif /* defined ALL_STATE */
	if (tzload((char *) NULL, lclptr) != 0)
		gmtload(lclptr);
	settzname();
E 21
E 13
E 12
}

D 12
char *
asctime(t)
struct tm *t;
E 12
I 12
D 21
struct tm *
localtime(timep)
time_t *	timep;
E 21
I 21
/*
** The easy way to behave "as if no library function calls" localtime
** is to not call it--so we drop its guts into "localsub", which can be
** freely called.  (And no, the PANS doesn't require the above behavior--
** but it *is* desirable.)
**
** The unused offset argument is for the benefit of mktime variants.
*/

/*ARGSUSED*/
static void
localsub(timep, offset, tmp)
const time_t * const	timep;
const long		offset;
struct tm * const	tmp;
E 21
E 12
{
D 12
	register char *cp, *ncp;
	register int *tp;
E 12
I 12
D 21
	register struct ttinfo *	ttisp;
	register struct tm *		tmp;
E 21
I 21
D 32
	register const struct state *	sp;
E 32
I 32
	register struct state *	sp;
E 32
	register const struct ttinfo *	ttisp;
E 21
	register int			i;
D 21
	time_t				t;
E 21
I 21
	const time_t			t = *timep;
E 21
E 12

D 12
	cp = cbuf;
	for (ncp = "Day Mon 00 00:00:00 1900\n"; *cp++ = *ncp++;);
	ncp = &"SunMonTueWedThuFriSat"[3*t->tm_wday];
	cp = cbuf;
	*cp++ = *ncp++;
	*cp++ = *ncp++;
	*cp++ = *ncp++;
	cp++;
	tp = &t->tm_mon;
	ncp = &"JanFebMarAprMayJunJulAugSepOctNovDec"[(*tp)*3];
	*cp++ = *ncp++;
	*cp++ = *ncp++;
	*cp++ = *ncp++;
	cp = ct_numb(cp, *--tp);
	cp = ct_numb(cp, *--tp+100);
	cp = ct_numb(cp, *--tp+100);
	cp = ct_numb(cp, *--tp+100);
	if (t->tm_year>=100) {
		cp[1] = '2';
D 2
		cp[2] = '0';
E 2
I 2
D 6
		cp[2] = '0' + t->tm_year >= 200;
E 6
I 6
		cp[2] = '0' + (t->tm_year-100) / 100;
E 12
I 12
D 21
	if (!tz_is_set)
		(void) tzset();
	t = *timep;
	if (s.timecnt == 0 || t < s.ats[0]) {
E 21
I 21
	if (!lcl_is_set)
		tzset();
	sp = lclptr;
#ifdef ALL_STATE
	if (sp == NULL) {
		gmtsub(timep, offset, tmp);
		return;
	}
#endif /* defined ALL_STATE */
	if (sp->timecnt == 0 || t < sp->ats[0]) {
E 21
		i = 0;
D 21
		while (s.ttis[i].tt_isdst)
			if (++i >= s.timecnt) {
E 21
I 21
		while (sp->ttis[i].tt_isdst)
			if (++i >= sp->typecnt) {
E 21
				i = 0;
				break;
			}
	} else {
D 21
		for (i = 1; i < s.timecnt; ++i)
			if (t < s.ats[i])
E 21
I 21
		for (i = 1; i < sp->timecnt; ++i)
			if (t < sp->ats[i])
E 21
				break;
D 21
		i = s.types[i - 1];
E 21
I 21
		i = sp->types[i - 1];
E 21
E 12
E 6
E 2
	}
D 12
	cp += 2;
	cp = ct_numb(cp, t->tm_year+100);
	return(cbuf);
E 12
I 12
D 21
	ttisp = &s.ttis[i];
E 21
I 21
	ttisp = &sp->ttis[i];
E 21
	/*
	** To get (wrong) behavior that's compatible with System V Release 2.0
	** you'd replace the statement below with
D 21
	**	tmp = offtime((time_t) (t + ttisp->tt_gmtoff), 0L);
E 21
I 21
	**	t += ttisp->tt_gmtoff;
	**	timesub(&t, 0L, sp, tmp);
E 21
	*/
D 21
	tmp = offtime(&t, ttisp->tt_gmtoff);
E 21
I 21
	timesub(&t, ttisp->tt_gmtoff, sp, tmp);
E 21
	tmp->tm_isdst = ttisp->tt_isdst;
D 21
	tzname[tmp->tm_isdst] = &s.chars[ttisp->tt_abbrind];
	tmp->tm_zone = &s.chars[ttisp->tt_abbrind];
	return tmp;
E 21
I 21
	tzname[tmp->tm_isdst] = (char *) &sp->chars[ttisp->tt_abbrind];
	tmp->tm_zone = &sp->chars[ttisp->tt_abbrind];
E 21
E 12
}

D 12
dysize(y)
E 12
I 12
struct tm *
D 21
gmtime(clock)
time_t *	clock;
E 21
I 21
localtime(timep)
const time_t * const	timep;
E 21
E 12
{
D 12
	if((y%4) == 0)
		return(366);
	return(365);
E 12
I 12
D 21
	register struct tm *	tmp;
E 21
I 21
	static struct tm	tm;
E 21

D 21
	tmp = offtime(clock, 0L);
	tzname[0] = "GMT";
	tmp->tm_zone = "GMT";		/* UCT ? */
	return tmp;
E 21
I 21
	localsub(timep, 0L, &tm);
	return &tm;
E 21
E 12
}

D 12
static char *
ct_numb(cp, n)
register char *cp;
E 12
I 12
D 21
static int	mon_lengths[2][MONS_PER_YEAR] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
	31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
E 21
I 21
/*
** gmtsub is to gmtime as localsub is to localtime.
*/
E 21

D 21
static int	year_lengths[2] = {
	DAYS_PER_NYEAR, DAYS_PER_LYEAR
};
E 21
I 21
static void
gmtsub(timep, offset, tmp)
const time_t * const	timep;
const long		offset;
struct tm * const	tmp;
{
	if (!gmt_is_set) {
		gmt_is_set = TRUE;
#ifdef ALL_STATE
		gmtptr = (struct state *) malloc(sizeof *gmtptr);
		if (gmtptr != NULL)
#endif /* defined ALL_STATE */
			gmtload(gmtptr);
	}
	timesub(timep, offset, gmtptr, tmp);
	/*
	** Could get fancy here and deliver something such as
	** "GMT+xxxx" or "GMT-xxxx" if offset is non-zero,
	** but this is no time for a treasure hunt.
	*/
	if (offset != 0)
		tmp->tm_zone = WILDABBR;
	else {
#ifdef ALL_STATE
		if (gmtptr == NULL)
			tmp->TM_ZONE = GMT;
		else	tmp->TM_ZONE = gmtptr->chars;
#endif /* defined ALL_STATE */
#ifndef ALL_STATE
		tmp->tm_zone = gmtptr->chars;
#endif /* State Farm */
	}
}
E 21

struct tm *
D 21
offtime(clock, offset)
time_t *	clock;
long		offset;
E 21
I 21
gmtime(timep)
const time_t * const	timep;
E 21
E 12
{
D 12
	cp++;
	if (n>=10)
		*cp++ = (n/10)%10 + '0';
	else
		*cp++ = ' ';
	*cp++ = n%10 + '0';
	return(cp);
E 12
I 12
D 21
	register struct tm *	tmp;
	register long		days;
	register long		rem;
	register int		y;
	register int		yleap;
	register int *		ip;
E 21
	static struct tm	tm;

D 21
	tmp = &tm;
	days = *clock / SECS_PER_DAY;
	rem = *clock % SECS_PER_DAY;
	rem += offset;
E 21
I 21
	gmtsub(timep, 0L, &tm);
	return &tm;
}

D 22
#ifdef STD_INSPIRED

struct tm *
offtime(timep, offset)
const time_t * const	timep;
const long		offset;
{
	static struct tm	tm;

	gmtsub(timep, offset, &tm);
	return &tm;
}

#endif /* defined STD_INSPIRED */

E 22
static void
timesub(timep, offset, sp, tmp)
const time_t * const			timep;
const long				offset;
register const struct state * const	sp;
register struct tm * const		tmp;
{
	register const struct lsinfo *	lp;
	register long			days;
	register long			rem;
	register int			y;
	register int			yleap;
	register const int *		ip;
	register long			corr;
	register int			hit;
	register int			i;

	corr = 0;
	hit = FALSE;
#ifdef ALL_STATE
	i = (sp == NULL) ? 0 : sp->leapcnt;
#endif /* defined ALL_STATE */
#ifndef ALL_STATE
	i = sp->leapcnt;
#endif /* State Farm */
	while (--i >= 0) {
		lp = &sp->lsis[i];
		if (*timep >= lp->ls_trans) {
			if (*timep == lp->ls_trans)
				hit = ((i == 0 && lp->ls_corr > 0) ||
					lp->ls_corr > sp->lsis[i - 1].ls_corr);
			corr = lp->ls_corr;
			break;
		}
	}
	days = *timep / SECSPERDAY;
	rem = *timep % SECSPERDAY;
#ifdef mc68k
	if (*timep == 0x80000000) {
		/*
		** A 3B1 muffs the division on the most negative number.
		*/
		days = -24855;
		rem = -11648;
	}
#endif /* mc68k */
	rem += (offset - corr);
E 21
	while (rem < 0) {
D 21
		rem += SECS_PER_DAY;
E 21
I 21
		rem += SECSPERDAY;
E 21
		--days;
	}
D 21
	while (rem >= SECS_PER_DAY) {
		rem -= SECS_PER_DAY;
E 21
I 21
	while (rem >= SECSPERDAY) {
		rem -= SECSPERDAY;
E 21
		++days;
	}
D 21
	tmp->tm_hour = (int) (rem / SECS_PER_HOUR);
	rem = rem % SECS_PER_HOUR;
	tmp->tm_min = (int) (rem / SECS_PER_MIN);
	tmp->tm_sec = (int) (rem % SECS_PER_MIN);
	tmp->tm_wday = (int) ((EPOCH_WDAY + days) % DAYS_PER_WEEK);
E 21
I 21
	tmp->tm_hour = (int) (rem / SECSPERHOUR);
	rem = rem % SECSPERHOUR;
	tmp->tm_min = (int) (rem / SECSPERMIN);
	tmp->tm_sec = (int) (rem % SECSPERMIN);
	if (hit)
		/*
		** A positive leap second requires a special
		** representation.  This uses "... ??:59:60".
		*/
		++(tmp->tm_sec);
	tmp->tm_wday = (int) ((EPOCH_WDAY + days) % DAYSPERWEEK);
E 21
	if (tmp->tm_wday < 0)
D 21
		tmp->tm_wday += DAYS_PER_WEEK;
E 21
I 21
		tmp->tm_wday += DAYSPERWEEK;
E 21
	y = EPOCH_YEAR;
	if (days >= 0)
		for ( ; ; ) {
			yleap = isleap(y);
			if (days < (long) year_lengths[yleap])
				break;
			++y;
			days = days - (long) year_lengths[yleap];
		}
	else do {
		--y;
		yleap = isleap(y);
		days = days + (long) year_lengths[yleap];
	} while (days < 0);
	tmp->tm_year = y - TM_YEAR_BASE;
	tmp->tm_yday = (int) days;
	ip = mon_lengths[yleap];
	for (tmp->tm_mon = 0; days >= (long) ip[tmp->tm_mon]; ++(tmp->tm_mon))
		days = days - (long) ip[tmp->tm_mon];
	tmp->tm_mday = (int) (days + 1);
	tmp->tm_isdst = 0;
D 21
	tmp->tm_zone = "";
	tmp->tm_gmtoff = offset;
	return tmp;
E 21
I 21
D 29
#ifdef TM_GMTOFF
	tmp->TM_GMTOFF = offset;
#endif /* defined TM_GMTOFF */
E 29
I 29
	tmp->tm_gmtoff = offset;
E 29
}

/*
** A la X3J11
*/

char *
asctime(timeptr)
register const struct tm *	timeptr;
{
	static const char	wday_name[DAYSPERWEEK][3] = {
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
	static const char	mon_name[MONSPERYEAR][3] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	static char	result[26];

	(void) sprintf(result, "%.3s %.3s%3d %02.2d:%02.2d:%02.2d %d\n",
		wday_name[timeptr->tm_wday],
		mon_name[timeptr->tm_mon],
		timeptr->tm_mday, timeptr->tm_hour,
		timeptr->tm_min, timeptr->tm_sec,
		TM_YEAR_BASE + timeptr->tm_year);
	return result;
}

char *
ctime(timep)
const time_t * const	timep;
{
	return asctime(localtime(timep));
}

/*
** Adapted from code provided by Robert Elz, who writes:
**	The "best" way to do mktime I think is based on an idea of Bob
**	Kridle's (so its said...) from a long time ago. (mtxinu!kridle now).
**	It does a binary search of the time_t space.  Since time_t's are
**	just 32 bits, its a max of 32 iterations (even at 64 bits it
**	would still be very reasonable).
*/

#ifndef WRONG
#define WRONG	(-1)
#endif /* !defined WRONG */

static void
normalize(tensptr, unitsptr, base)
int * const	tensptr;
int * const	unitsptr;
const int	base;
{
	if (*unitsptr >= base) {
		*tensptr += *unitsptr / base;
		*unitsptr %= base;
	} else if (*unitsptr < 0) {
D 33
		--*tensptr;
		*unitsptr += base;
		if (*unitsptr < 0) {
			*tensptr -= 1 + (-*unitsptr) / base;
			*unitsptr = base - (-*unitsptr) % base;
		}
E 33
I 33
		*tensptr -= 1 + (-(*unitsptr + 1)) / base;
		*unitsptr = base - 1 - (-(*unitsptr + 1)) % base;
E 33
	}
}

static int
tmcomp(atmp, btmp)
register const struct tm * const atmp;
register const struct tm * const btmp;
{
	register int	result;

	if ((result = (atmp->tm_year - btmp->tm_year)) == 0 &&
		(result = (atmp->tm_mon - btmp->tm_mon)) == 0 &&
		(result = (atmp->tm_mday - btmp->tm_mday)) == 0 &&
		(result = (atmp->tm_hour - btmp->tm_hour)) == 0 &&
		(result = (atmp->tm_min - btmp->tm_min)) == 0)
			result = atmp->tm_sec - btmp->tm_sec;
	return result;
}

static time_t
time2(tmp, funcp, offset, okayp)
struct tm * const	tmp;
void (* const		funcp)();
const long		offset;
int * const		okayp;
{
	register const struct state *	sp;
	register int			dir;
	register int			bits;
	register int			i, j ;
	register int			saved_seconds;
	time_t				newt;
	time_t				t;
	struct tm			yourtm, mytm;

	*okayp = FALSE;
	yourtm = *tmp;
	if (yourtm.tm_sec >= SECSPERMIN + 2 || yourtm.tm_sec < 0)
		normalize(&yourtm.tm_min, &yourtm.tm_sec, SECSPERMIN);
	normalize(&yourtm.tm_hour, &yourtm.tm_min, MINSPERHOUR);
	normalize(&yourtm.tm_mday, &yourtm.tm_hour, HOURSPERDAY);
	normalize(&yourtm.tm_year, &yourtm.tm_mon, MONSPERYEAR);
	while (yourtm.tm_mday <= 0) {
		--yourtm.tm_year;
		yourtm.tm_mday +=
			year_lengths[isleap(yourtm.tm_year + TM_YEAR_BASE)];
	}
I 35
	while (yourtm.tm_mday > DAYSPERLYEAR) {
		yourtm.tm_mday -=
		    year_lengths[isleap(yourtm.tm_year + TM_YEAR_BASE)];
		++yourtm.tm_year;
	}
E 35
	for ( ; ; ) {
		i = mon_lengths[isleap(yourtm.tm_year +
			TM_YEAR_BASE)][yourtm.tm_mon];
		if (yourtm.tm_mday <= i)
			break;
		yourtm.tm_mday -= i;
		if (++yourtm.tm_mon >= MONSPERYEAR) {
			yourtm.tm_mon = 0;
			++yourtm.tm_year;
		}
	}
	saved_seconds = yourtm.tm_sec;
	yourtm.tm_sec = 0;
	/*
	** Calculate the number of magnitude bits in a time_t
	** (this works regardless of whether time_t is
	** signed or unsigned, though lint complains if unsigned).
	*/
	for (bits = 0, t = 1; t > 0; ++bits, t <<= 1)
		;
	/*
	** If time_t is signed, then 0 is the median value,
	** if time_t is unsigned, then 1 << bits is median.
	*/
	t = (t < 0) ? 0 : ((time_t) 1 << bits);
	for ( ; ; ) {
		(*funcp)(&t, offset, &mytm);
		dir = tmcomp(&mytm, &yourtm);
		if (dir != 0) {
			if (bits-- < 0)
				return WRONG;
			if (bits < 0)
				--t;
			else if (dir > 0)
				t -= (time_t) 1 << bits;
			else	t += (time_t) 1 << bits;
			continue;
		}
		if (yourtm.tm_isdst < 0 || mytm.tm_isdst == yourtm.tm_isdst)
			break;
		/*
		** Right time, wrong type.
		** Hunt for right time, right type.
		** It's okay to guess wrong since the guess
		** gets checked.
		*/
		sp = (const struct state *)
			((funcp == localsub) ? lclptr : gmtptr);
#ifdef ALL_STATE
		if (sp == NULL)
			return WRONG;
#endif /* defined ALL_STATE */
		for (i = 0; i < sp->typecnt; ++i) {
			if (sp->ttis[i].tt_isdst != yourtm.tm_isdst)
				continue;
			for (j = 0; j < sp->typecnt; ++j) {
				if (sp->ttis[j].tt_isdst == yourtm.tm_isdst)
					continue;
				newt = t + sp->ttis[j].tt_gmtoff -
					sp->ttis[i].tt_gmtoff;
				(*funcp)(&newt, offset, &mytm);
				if (tmcomp(&mytm, &yourtm) != 0)
					continue;
				if (mytm.tm_isdst != yourtm.tm_isdst)
					continue;
				/*
				** We have a match.
				*/
				t = newt;
				goto label;
			}
		}
		return WRONG;
	}
label:
	t += saved_seconds;
	(*funcp)(&t, offset, tmp);
	*okayp = TRUE;
	return t;
}

static time_t
time1(tmp, funcp, offset)
struct tm * const	tmp;
void (* const		funcp)();
const long		offset;
{
	register time_t			t;
	register const struct state *	sp;
	register int			samei, otheri;
	int				okay;

	if (tmp->tm_isdst > 1)
D 23
		return WRONG;
E 23
I 23
		tmp->tm_isdst = 1;
E 23
	t = time2(tmp, funcp, offset, &okay);
	if (okay || tmp->tm_isdst < 0)
		return t;
	/*
	** We're supposed to assume that somebody took a time of one type
	** and did some math on it that yielded a "struct tm" that's bad.
	** We try to divine the type they started from and adjust to the
	** type they need.
	*/
	sp = (const struct state *) ((funcp == localsub) ? lclptr : gmtptr);
#ifdef ALL_STATE
	if (sp == NULL)
		return WRONG;
#endif /* defined ALL_STATE */
	for (samei = 0; samei < sp->typecnt; ++samei) {
		if (sp->ttis[samei].tt_isdst != tmp->tm_isdst)
			continue;
		for (otheri = 0; otheri < sp->typecnt; ++otheri) {
			if (sp->ttis[otheri].tt_isdst == tmp->tm_isdst)
				continue;
			tmp->tm_sec += sp->ttis[otheri].tt_gmtoff -
					sp->ttis[samei].tt_gmtoff;
			tmp->tm_isdst = !tmp->tm_isdst;
			t = time2(tmp, funcp, offset, &okay);
			if (okay)
				return t;
			tmp->tm_sec -= sp->ttis[otheri].tt_gmtoff -
					sp->ttis[samei].tt_gmtoff;
			tmp->tm_isdst = !tmp->tm_isdst;
		}
	}
	return WRONG;
}

time_t
mktime(tmp)
struct tm * const	tmp;
{
	return time1(tmp, localsub, 0L);
D 22
}

time_t
timegm(tmp)
struct tm * const	tmp;
{
	return time1(tmp, gmtsub, 0L);
}

time_t
timeoff(tmp, offset)
struct tm * const	tmp;
const long		offset;
{

	return time1(tmp, gmtsub, offset);
E 22
E 21
E 12
}
E 1
