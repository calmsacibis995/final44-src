h34486
s 00003/00005/00075
d D 8.2 94/04/04 05:40:29 pendry 6 5
c prettiness police
e
s 00002/00002/00078
d D 8.1 93/06/06 22:23:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00010/00065
d D 5.4 93/04/27 16:02:40 bostic 4 3
c fuckin' SCCS...
e
s 00046/00050/00029
d D 5.3 93/04/27 15:21:06 bostic 3 2
c use strftime, don't roll our own
e
s 00016/00015/00063
d D 5.2 90/08/30 11:55:10 marc 2 1
c fixes from chris
e
s 00078/00000/00000
d D 5.1 90/05/04 15:53:06 marc 1 0
c date and time created 90/05/04 15:53:06 by marc
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 6
 * Copyright (c) 1990, 1993
E 6
I 6
 * Copyright (c) 1990, 1993, 1994
E 6
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/time.h>
I 3

E 3
#include <stdio.h>
I 2
#include <string.h>
I 3
#include <tzfile.h>
E 3
E 2

D 3
#define	HR	(60 * 60)
#define	DAY	(24 * HR)
#define	MON	(30 * DAY)
E 3
I 3
#include "extern.h"
E 3

D 3
static time_t now;
E 3
/*
D 3
 * prttime prints a time in hours and minutes or minutes and seconds.
 * The character string tail is printed at the end, obvious
 * strings to pass are "", " ", or "am".
E 3
I 3
 * pr_attime --
 *	Print the time since the user logged in. 
I 4
 *
 *	Note: SCCS forces the bizarre string manipulation, things like
 *	%I% get replaced in the source code.
E 4
E 3
 */
D 3
static char *
prttime(tim, tail)
	time_t tim;
	char *tail;
E 3
I 3
void
pr_attime(started, now)
	time_t *started, *now;
E 3
{
D 2
	static char timebuf[32], *cp;
E 2
I 2
D 3
	int mins;
	static char timebuf[32];
E 3
I 3
	static char buf[256];
	struct tm *tp;
	time_t diff;
I 4
	char fmt[20];
E 4
E 3
E 2

D 3
	if (tim >= 60) {
D 2
		int mins = tim % 60;
		sprintf(timebuf, "%2d:%02d", tim/60, mins);
E 2
I 2
		mins = tim % 60;
		(void) sprintf(timebuf, "%2d:%02d%s", (int)(tim / 60), mins,
		    tail);
E 2
	} else if (tim >= 0)
D 2
		sprintf(timebuf, "    %2d", tim);
	cp = timebuf;
	while (*cp)
		cp++;
	sprintf(cp, "%s", tail);
E 2
I 2
		(void) sprintf(timebuf, "    %2d%s", (int)tim, tail);
E 3
I 3
	tp = localtime(started);
	diff = *now - *started;

	/* If more than a week, use day-month-year. */
	if (diff > SECSPERDAY * DAYSPERWEEK)
D 4
		(void)strftime(buf, sizeof(buf), "%d%b%y", tp);
E 4
I 4
		(void)strcpy(fmt, "%d%b%y");
E 4

	/* If not today, use day-hour-am/pm. */
D 4
	else if (*now / SECSPERDAY != *started / SECSPERDAY)
		(void)strftime(buf, sizeof(buf), "%a%I%p", tp);
E 4
I 4
	else if (*now / SECSPERDAY != *started / SECSPERDAY) {
D 6
		(void)strcpy(fmt, "%a%%%p");
		fmt[3] = 'I';
E 6
I 6
		(void)strcpy(fmt, __CONCAT("%a%", "I%p"));
E 6
	}
E 4

D 4
	/* If more than an hour, use hh:mm{am,pm}. */
	else if (diff > SECSPERHOUR)
		(void)strftime(buf, sizeof(buf), "%l:%M%p", tp);
E 4
I 4
	/* Default is hh:mm{am,pm}. */
	else {
D 6
		(void)strcpy(fmt, "%l:%%%p");
		fmt[4] = 'M';
E 6
I 6
		(void)strcpy(fmt, __CONCAT("%l:%", "M%p"));
E 6
	}
E 4

D 4
	/* Default is mm. */
E 3
	else
D 3
		(void) strcpy(timebuf, tail);
E 3
I 3
		(void)strftime(buf, sizeof(buf), "    %M", tp);
E 3
E 2

E 4
I 4
	(void)strftime(buf, sizeof(buf), fmt, tp);
E 4
D 3
	return (timebuf);
E 3
I 3
	(void)printf("%s", buf);
E 3
}

D 3
static char *weekday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
static char *month[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

/* prtat prints a 12 hour time given a pointer to a time of day */
char *
attime(started)
D 2
	long *started;
E 2
I 2
	time_t *started;
E 3
I 3
/*
 * pr_idle --
 *	Display the idle time.
 */
void
pr_idle(idle)
	time_t idle;
E 3
E 2
{
D 3
	struct tm *p;
	register int hr, pm;
	static char prbuff[64];
E 3
I 3
	/* If idle more than 36 hours, print as a number of days. */
	if (idle >= 36 * SECSPERHOUR)
		(void)printf(" %ddays ", idle / SECSPERDAY);
E 3

D 3
	if (now == 0)
D 2
		time(&now);
E 2
I 2
		(void) time(&now);
E 2
	p = localtime(started);
	hr = p->tm_hour;
	pm = (hr > 11);
	if (hr > 11)
		hr -= 12;
	if (hr == 0)
		hr = 12;
	if (now - *started <= 18 * HR)
D 2
		return (prttime(hr * 60 + p->tm_min, pm ? "pm" : "am"));
	else if (now - *started <= 7 * DAY)
		sprintf(prbuff, "%*s%d%s", hr < 10 ? 4 : 3,
E 2
I 2
		return (prttime((time_t)hr * 60 + p->tm_min, pm ? "pm" : "am"));
	if (now - *started <= 7 * DAY)
		(void) sprintf(prbuff, "%*s%d%s", hr < 10 ? 4 : 3,
E 2
			weekday[p->tm_wday], hr, pm ? "pm" : "am");
	else
D 2
		sprintf(prbuff, "%2d%s%2d", p->tm_mday, month[p->tm_mon], 
			p->tm_year);
E 2
I 2
		(void) sprintf(prbuff, "%2d%s%2d", p->tm_mday,
			month[p->tm_mon], p->tm_year);
E 3
I 3
	/* If idle more than an hour, print as HH:MM. */
	else if (idle >= SECSPERHOUR)
		(void)printf(" %2d:%02d ",
		    idle / SECSPERHOUR, (idle % SECSPERHOUR) / SECSPERMIN);
E 3
E 2

D 3
	return (prbuff);
E 3
I 3
	/* Else print the minutes idle. */
	else
		(void)printf("    %2d ", idle / SECSPERMIN);
E 3
}
E 1
