h09632
s 00001/00001/00118
d D 8.4 94/04/02 10:06:42 pendry 18 17
c add 1994 copyright
e
s 00021/00016/00098
d D 8.3 94/04/02 07:56:54 pendry 17 16
c prettyness police
e
s 00002/00002/00112
d D 8.2 94/01/03 08:27:40 bostic 16 15
c don't assume that the year is 19XX -- user's can enter 20XX and
c (probably, theoretically) end up with something useful
e
s 00002/00002/00112
d D 8.1 93/06/06 14:27:34 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00049/00114
d D 5.14 91/02/12 22:38:05 bostic 14 13
c rework the password subsystem
e
s 00009/00017/00154
d D 5.13 90/06/29 00:18:27 marc 13 12
c new interface to strsep
e
s 00010/00000/00161
d D 5.12 89/06/01 18:37:53 bostic 12 11
c handle user inserting new (restricted) fields into the file they edit
e
s 00039/00027/00122
d D 5.11 89/06/01 18:20:34 bostic 11 10
c add -s flag to allow command line change of shell
e
s 00001/00001/00148
d D 5.10 89/05/11 09:42:11 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00002/00002/00147
d D 5.9 89/03/27 09:36:52 bostic 9 8
c buffer overflow, day fencepost
e
s 00001/00001/00148
d D 5.8 89/03/16 21:58:19 bostic 8 7
c allow re-editing of file if reject entries
e
s 00002/00002/00147
d D 5.7 89/03/15 21:03:36 bostic 7 6
c new tzfile.h
e
s 00001/00000/00148
d D 5.6 89/03/11 17:07:34 bostic 6 5
c allow root to edit encrypted passwords
e
s 00009/00008/00139
d D 5.5 89/03/09 15:28:28 bostic 5 4
c make empty fields work, get rid of pw_class keywords
e
s 00005/00004/00142
d D 5.4 89/03/05 21:20:23 bostic 4 3
c add pathnames.h
e
s 00002/00002/00144
d D 5.3 89/02/23 21:42:03 bostic 3 2
c fix gecos field ordering to be backward compatible
e
s 00007/00007/00139
d D 5.2 89/02/23 18:14:42 bostic 2 1
c change expire/change format to ``month dd, year''
e
s 00146/00000/00000
d D 5.1 89/02/22 17:23:49 bostic 1 0
c date and time created 89/02/22 17:23:49 by bostic
e
u
U
t
T
I 1
D 13
/*
E 13
I 13
/*-
E 13
D 15
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
D 18
 * Copyright (c) 1988, 1993
E 18
I 18
 * Copyright (c) 1988, 1993, 1994
E 18
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 13
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 17
#include <sys/time.h>
#include <tzfile.h>
E 17
I 17

#include <ctype.h>
E 17
D 4
#include </usr/src/include/pwd.h>
E 4
I 4
#include <pwd.h>
E 4
#include <stdio.h>
I 17
#include <stdlib.h>
E 17
D 10
#include <chpass.h>
E 10
D 13
#include <strings.h>
E 13
I 13
#include <string.h>
E 13
D 17
#include <ctype.h>
E 17
I 17
#include <time.h>
#include <tzfile.h>
#include <unistd.h>

E 17
I 10
#include "chpass.h"
E 10
I 4
#include "pathnames.h"
E 4

static int dmsize[] =
	{ -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static char *months[] =
D 5
	{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
	  "Sep", "Oct", "Nov", "Dec", NULL };
E 5
I 5
	{ "January", "February", "March", "April", "May", "June",
	  "July", "August", "September", "October", "November",
	  "December", NULL };
I 17

E 17
E 5
char *
ttoa(tval)
	time_t tval;
{
	struct tm *tp;
D 9
	static char tbuf[10];
E 9
I 9
	static char tbuf[50];
E 9

D 5
	if (!tval)
		bcopy("None", tbuf, 6);
	else {
E 5
I 5
	if (tval) {
E 5
		tp = localtime(&tval);
D 2
		(void)sprintf(tbuf, "%02d %s 19%02d", tp->tm_mday,
		    months[tp->tm_mon], tp->tm_year);
E 2
I 2
D 16
		(void)sprintf(tbuf, "%s %d, 19%d", months[tp->tm_mon],
		    tp->tm_mday, tp->tm_year);
E 16
I 16
		(void)sprintf(tbuf, "%s %d, %d", months[tp->tm_mon],
		    tp->tm_mday, tp->tm_year + TM_YEAR_BASE);
E 16
E 2
	}
I 5
	else
		*tbuf = '\0';
E 5
D 17
	return(tbuf);
E 17
I 17
	return (tbuf);
E 17
} 

I 17
int
E 17
atot(p, store)
	char *p;
	time_t *store;
{
D 17
	register char *t, **mp;
E 17
	static struct tm *lt;
D 17
	time_t tval, time();
E 17
I 17
	char *t, **mp;
	time_t tval;
E 17
	int day, month, year;

D 5
	if (!strncasecmp(p, "none", 4)) {
E 5
I 5
	if (!*p) {
E 5
		*store = 0;
D 17
		return(0);
E 17
I 17
		return (0);
E 17
	}
	if (!lt) {
		unsetenv("TZ");
		(void)time(&tval);
		lt = localtime(&tval);
	}
D 2
	if (!(t = strsep(p, " \t")) || !isdigit(*t))
E 2
I 2
	if (!(t = strtok(p, " \t")))
E 2
		goto bad;
D 2
	day = atoi(t);
	if (!(t = strsep((char *)NULL, " \t")))
		goto bad;
E 2
	for (mp = months;; ++mp) {
		if (!*mp)
			goto bad;
		if (!strncasecmp(*mp, t, 3)) {
			month = mp - months + 1;
			break;
		}
	}
D 2
	if (!(t = strsep((char *)NULL, " \t")) || !isdigit(*t))
E 2
I 2
	if (!(t = strtok((char *)NULL, " \t,")) || !isdigit(*t))
		goto bad;
	day = atoi(t);
	if (!(t = strtok((char *)NULL, " \t,")) || !isdigit(*t))
E 2
		goto bad;
	year = atoi(t);
	if (day < 1 || day > 31 || month < 1 || month > 12 || !year)
		goto bad;
	if (year < 100)
		year += TM_YEAR_BASE;
	if (year <= EPOCH_YEAR)
D 17
bad:		return(1);
E 17
I 17
bad:		return (1);
E 17
	tval = isleap(year) && month > 2;
	for (--year; year >= EPOCH_YEAR; --year)
		tval += isleap(year) ?
D 7
		    DAYS_PER_LYEAR : DAYS_PER_NYEAR;
E 7
I 7
		    DAYSPERLYEAR : DAYSPERNYEAR;
E 7
	while (--month)
		tval += dmsize[month];
D 9
	tval += day - 1;
E 9
I 9
	tval += day;
E 9
D 7
	tval = tval * HOURS_PER_DAY * MINS_PER_HOUR * SECS_PER_MIN;
E 7
I 7
	tval = tval * HOURSPERDAY * MINSPERHOUR * SECSPERMIN;
E 7
	tval -= lt->tm_gmtoff;
	*store = tval;
D 17
	return(0);
E 17
I 17
	return (0);
E 17
}

I 12
D 14
/*
 * print --
 *	print out the file for the user to edit; strange side-effect:
 *	return if the user is allowed to modify their shell.
 */
E 12
print(fp, pw)
	FILE *fp;
	struct passwd *pw;
{
	register char *p;
I 12
	int shellval;
I 13
	char *bp;
E 13
E 12
D 11
	char *getusershell(), *ttoa();
E 11
I 11
	char *getusershell(), *ok_shell(), *ttoa();
E 11

I 12
	shellval = 1;
E 12
D 8
	fprintf(fp, "Changing user database information for %s.\n",
E 8
I 8
D 11
	fprintf(fp, "#Changing user database information for %s.\n",
E 11
I 11
	(void)fprintf(fp, "#Changing user database information for %s.\n",
E 11
E 8
	    pw->pw_name);
	if (!uid) {
D 11
		fprintf(fp, "Login: %s\n", pw->pw_name);
I 6
		fprintf(fp, "Password: %s\n", pw->pw_passwd);
E 6
		fprintf(fp, "Uid [#]: %d\n", pw->pw_uid);
		fprintf(fp, "Gid [# or name]: %d\n", pw->pw_gid);
D 5
		fprintf(fp, "Change [dd month yy]: %s\n", ttoa(pw->pw_change));
		fprintf(fp, "Expire [dd month yy]: %s\n", ttoa(pw->pw_expire));
E 5
I 5
		fprintf(fp, "Change [month day year]: %s\n", ttoa(pw->pw_change));
		fprintf(fp, "Expire [month day year]: %s\n", ttoa(pw->pw_expire));
E 5
		fprintf(fp, "Class: %s\n", pw->pw_class);
		fprintf(fp, "Home directory: %s\n", pw->pw_dir);
		fprintf(fp, "Shell: %s\n",
E 11
I 11
		(void)fprintf(fp, "Login: %s\n", pw->pw_name);
		(void)fprintf(fp, "Password: %s\n", pw->pw_passwd);
		(void)fprintf(fp, "Uid [#]: %d\n", pw->pw_uid);
		(void)fprintf(fp, "Gid [# or name]: %d\n", pw->pw_gid);
		(void)fprintf(fp, "Change [month day year]: %s\n",
		    ttoa(pw->pw_change));
		(void)fprintf(fp, "Expire [month day year]: %s\n",
		    ttoa(pw->pw_expire));
		(void)fprintf(fp, "Class: %s\n", pw->pw_class);
		(void)fprintf(fp, "Home directory: %s\n", pw->pw_dir);
		(void)fprintf(fp, "Shell: %s\n",
E 11
D 4
		    *pw->pw_shell ? pw->pw_shell : "/bin/sh");
E 4
I 4
		    *pw->pw_shell ? pw->pw_shell : _PATH_BSHELL);
E 4
	}
D 11
	else {
		/* only admin can change "restricted" shells */
		setusershell();
		for (;;)
			if (!(p = getusershell()))
				break;
			else if (!strcmp(pw->pw_shell, p)) {
D 4
				fprintf(fp, "Shell: %s\n",
				    *pw->pw_shell ? pw->pw_shell : "/bin/sh");
E 4
I 4
				fprintf(fp, "Shell: %s\n", *pw->pw_shell ?
				    pw->pw_shell : _PATH_BSHELL);
E 4
				break;
			}
	}
E 11
I 11
	/* only admin can change "restricted" shells */
	else if (ok_shell(pw->pw_shell))
		(void)fprintf(fp, "Shell: %s\n",
		    *pw->pw_shell ? pw->pw_shell : _PATH_BSHELL);
I 12
	else
		shellval = 0;
E 12
E 11
D 13
	p = strsep(pw->pw_gecos, ",");
E 13
I 13
	bp = pw->pw_gecos;
	p = strsep(&bp, ",");
E 13
D 11
	fprintf(fp, "Full Name: %s\n", p ? p : "");
E 11
I 11
	(void)fprintf(fp, "Full Name: %s\n", p ? p : "");
E 11
D 13
	p = strsep((char *)NULL, ",");
E 13
I 13
	p = strsep(&bp, ",");
E 13
D 11
	fprintf(fp, "Location: %s\n", p ? p : "");
E 11
I 11
	(void)fprintf(fp, "Location: %s\n", p ? p : "");
E 11
D 13
	p = strsep((char *)NULL, ",");
E 13
I 13
	p = strsep(&bp, ",");
E 13
D 3
	fprintf(fp, "Home Phone: %s\n", p ? p : "");
	p = strsep((char *)NULL, ",");
E 3
D 11
	fprintf(fp, "Office Phone: %s\n", p ? p : "");
E 11
I 11
	(void)fprintf(fp, "Office Phone: %s\n", p ? p : "");
E 11
I 3
D 13
	p = strsep((char *)NULL, ",");
E 13
I 13
	p = strsep(&bp, ",");
E 13
D 11
	fprintf(fp, "Home Phone: %s\n", p ? p : "");
E 11
I 11
	(void)fprintf(fp, "Home Phone: %s\n", p ? p : "");
I 12
	return(shellval);
E 12
}

E 14
char *
ok_shell(name)
D 17
	register char *name;
E 17
I 17
	char *name;
E 17
{
D 17
	register char *p, *sh;
	char *getusershell();
E 17
I 17
	char *p, *sh;
E 17

	setusershell();
	while (sh = getusershell()) {
		if (!strcmp(name, sh))
D 17
			return(name);
E 17
I 17
			return (name);
E 17
		/* allow just shell name, but use "real" path */
D 17
		if ((p = rindex(sh, '/')) && !strcmp(name, p + 1))
			return(sh);
E 17
I 17
		if ((p = strrchr(sh, '/')) && strcmp(name, p + 1) == 0)
			return (sh);
E 17
	}
D 17
	return(NULL);
E 17
I 17
	return (NULL);
E 17
E 11
E 3
}
E 1
