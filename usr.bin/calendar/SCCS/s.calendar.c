h34469
s 00001/00001/00384
d D 8.4 95/01/07 17:54:59 mckusick 16 15
c need -P to cpp (from cgd)
e
s 00065/00044/00320
d D 8.3 94/03/25 14:49:37 bostic 15 14
c KNF, ANSI C
e
s 00016/00011/00348
d D 8.2 94/03/25 14:30:52 bostic 14 13
c off-by-one error in the daytab causing all dates in january to be
c off by one (day 1 of february == day 32 of the year, and is recorded by
c "30", etc.)
c fix the recognition of day-of-week items (e.g. "monday foo bar baz").
c  Before, they'd print on day 1 of the month, regardless of whether or not
c  was the appropriate day.
c print whole message when doing "monday   foo bar baz" -- used to print
c "monday  foo" only.
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00005/00005/00354
d D 8.1 93/06/06 14:26:18 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00004/00351
d D 4.12 92/05/11 16:19:26 marc 12 11
c fix processing of '*' and a few other minor nits
e
s 00001/00001/00354
d D 4.11 90/10/12 08:07:56 bostic 11 10
c Friday is tm_wday 5, not 6
e
s 00001/00011/00354
d D 4.10 90/06/01 16:38:01 bostic 10 9
c new copyright notice
e
s 00024/00012/00341
d D 4.9 90/05/03 21:27:31 bostic 9 8
c execl was missing a terminating NULL
c use an iov structure to avoid either a sprintf or an fdopen
e
s 00001/00001/00352
d D 4.8 90/02/21 14:15:17 bostic 8 7
c not any space, just tabs; people used " 2/1" because it formatted
c with "10/1" so it broke things
e
s 00342/00044/00012
d D 4.7 89/10/13 14:12:29 bostic 7 6
c redone from scratch as a C program to fix cpp security problem
e
s 00002/00002/00054
d D 4.6 87/05/02 15:57:51 bostic 6 5
c don't use char tabs in printfs
e
s 00002/00002/00054
d D 4.5 84/05/07 14:40:36 ralph 5 4
c allow tabs for sepparators.
e
s 00001/00001/00055
d D 4.4 83/07/03 20:15:51 sam 4 3
c include fix
e
s 00003/00002/00053
d D 4.3 82/06/28 03:39:39 wnj 3 2
c fix to allow 08/... in dates (for Ted Kowalski)
e
s 00002/00000/00053
d D 4.2 81/02/28 20:49:29 wnj 2 1
c fixes from various sources for clean termination
e
s 00053/00000/00000
d D 4.1 81/02/28 20:45:55 wnj 1 0
c date and time created 81/02/28 20:45:55 by wnj
e
u
U
t
T
I 1
D 7
static	char *sccsid = "%W% (Berkeley) %E%";
/* /usr/lib/calendar produces an egrep -f file
   that will select today's and tomorrow's
   calendar entries, with special weekend provisions
E 7
I 7
/*
D 13
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
D 14
 * Copyright (c) 1989, 1993
E 14
I 14
 * Copyright (c) 1989, 1993, 1994
E 14
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
 */
E 7

D 7
   used by calendar command
*/
E 7
I 7
#ifndef lint
D 13
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
E 7
D 4
#include <time.h>
E 4
I 4
#include <sys/time.h>
I 7
#include <sys/stat.h>
D 15
#include <sys/file.h>
E 15
I 9
#include <sys/uio.h>
I 15
#include <sys/wait.h>
E 15
E 9
D 14
#include <pwd.h>
E 14
I 14

#include <ctype.h>
I 15
#include <err.h>
E 15
E 14
#include <errno.h>
I 15
#include <fcntl.h>
E 15
D 14
#include <tzfile.h>
E 14
I 14
#include <pwd.h>
E 14
#include <stdio.h>
I 15
#include <stdlib.h>
E 15
D 14
#include <ctype.h>
#include <unistd.h>
E 14
#include <string.h>
I 14
#include <tzfile.h>
#include <unistd.h>

E 14
D 9
#include <paths.h>
E 9
#include "pathnames.h"
E 7
E 4

I 9
D 14
extern int errno;
E 14
E 9
D 7
#define DAY (3600*24L)
E 7
I 7
struct passwd *pw;
int doall;
E 7

I 15
void	 cal __P((void));
void	 closecal __P((FILE *));
int	 getday __P((char *));
int	 getfield __P((char *, char **, int *));
int	 getmonth __P((char *));
int	 isnow __P((char *));
FILE	*opencal __P((void));
void	 settime __P((void));
void	 usage __P((void));

E 15
I 14
int
E 14
D 7
char *month[] = {
	"[Jj]an",
	"[Ff]eb",
	"[Mm]ar",
	"[Aa]pr",
	"[Mm]ay",
	"[Jj]un",
	"[Jj]ul",
	"[Aa]ug",
	"[Ss]ep",
	"[Oo]ct",
	"[Nn]ov",
	"[Dd]ec"
E 7
I 7
main(argc, argv)
	int argc;
D 14
	char **argv;
E 14
I 14
	char *argv[];
E 14
{
D 9
	extern int errno, optind;
E 9
I 9
	extern int optind;
E 9
	int ch;

	while ((ch = getopt(argc, argv, "-a")) != EOF)
D 15
		switch(ch) {
E 15
I 15
		switch (ch) {
E 15
		case '-':		/* backward contemptible */
		case 'a':
			if (getuid()) {
D 15
				(void)fprintf(stderr,
				    "calendar: %s\n", strerror(EPERM));
				exit(1);
E 15
I 15
				errno = EPERM;
				err(1, NULL);
E 15
			}
			doall = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc)
		usage();

	settime();
	if (doall)
D 15
		while (pw = getpwent()) {
E 15
I 15
		while ((pw = getpwent()) != NULL) {
E 15
			(void)setegid(pw->pw_gid);
			(void)seteuid(pw->pw_uid);
			if (!chdir(pw->pw_dir))
				cal();
			(void)seteuid(0);
		}
	else
		cal();
	exit(0);
}

I 15
void
E 15
cal()
{
	register int printing;
	register char *p;
D 15
	FILE *fp, *opencal();
E 15
I 15
	FILE *fp;
E 15
	int ch;
	char buf[2048 + 1];

D 15
	if (!(fp = opencal()))
E 15
I 15
	if ((fp = opencal()) == NULL)
E 15
		return;
D 15
	for (printing = 0; fgets(buf, sizeof(buf), stdin);) {
		if (p = index(buf, '\n'))
E 15
I 15
	for (printing = 0; fgets(buf, sizeof(buf), stdin) != NULL;) {
		if ((p = strchr(buf, '\n')) != NULL)
E 15
			*p = '\0';
		else
			while ((ch = getchar()) != '\n' && ch != EOF);
		if (buf[0] == '\0')
			continue;
D 8
		if (!isspace(buf[0]))
E 8
I 8
		if (buf[0] != '\t')
E 8
			printing = isnow(buf) ? 1 : 0;
		if (printing)
			(void)fprintf(fp, "%s\n", buf);
	}
	closecal(fp);
}

I 9
struct iovec header[] = {
	"From: ", 6,
	NULL, 0,
	" (Reminder Service)\nTo: ", 24,
	NULL, 0,
	"\nSubject: ", 10,
	NULL, 0,
	"'s Calendar\nPrecedence: bulk\n\n",  30,
};

E 9
/* 1-based month, 0-based days, cumulative */
int daytab[][14] = {
D 14
	0, 0, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364,
	0, 0, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365,
E 14
I 14
	0, -1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364,
	0, -1, 30, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365,
E 14
E 7
};
D 7
struct tm *localtime();
E 7
I 7
struct tm *tp;
int *cumdays, offset, yrdays;
char dayname[10];
E 7

I 15
void
E 15
D 7
tprint(t)
long t;
E 7
I 7
settime()
E 7
{
D 7
	struct tm *tm;
	tm = localtime(&t);
D 3
	printf("(^|[ (,;])((%s[^ ]* *|%d/)0*%d)([^0123456789]|$)\n",
		month[tm->tm_mon], tm->tm_mon + 1, tm->tm_mday);
E 3
I 3
D 5
	printf("(^|[ (,;])((%s[^ ]* *|(0%d|%d)/)0*%d)([^0123456789]|$)\n",
E 5
I 5
D 6
	printf("(^|[ 	(,;])((%s[^ \t]*[ \t]*|(0%d|%d)/)0*%d)([^0123456789]|$)\n",
E 6
I 6
	printf("(^|[ \t(,;])((%s[^ \t]*[ \t]*|(0%d|%d)/)0*%d)([^0123456789]|$)\n",
E 6
E 5
		month[tm->tm_mon],
		tm->tm_mon + 1, tm->tm_mon + 1, tm->tm_mday);
E 3
I 2
D 5
	printf("(^|[ (,;])((\\* *)0*%d)([^0123456789]|$)\n",
E 5
I 5
D 6
	printf("(^|[ 	(,;])((\\*[ \t]*)0*%d)([^0123456789]|$)\n",
E 6
I 6
	printf("(^|[ \t(,;])((\\*[ \t]*)0*%d)([^0123456789]|$)\n",
E 6
E 5
		tm->tm_mday);
E 7
I 7
D 15
	time_t now, time();
E 15
I 15
	time_t now;
E 15

	(void)time(&now);
	tp = localtime(&now);
	if (isleap(tp->tm_year + 1900)) {
		yrdays = DAYSPERLYEAR;
		cumdays = daytab[1];
	} else {
		yrdays = DAYSPERNYEAR;
		cumdays = daytab[0];
	}
	/* Friday displays Monday's events */
D 11
	offset = tp->tm_wday == 6 ? 3 : 1;
E 11
I 11
	offset = tp->tm_wday == 5 ? 3 : 1;
E 11
D 9
	(void)strftime(dayname, sizeof(dayname), "%A", tp);
E 9
I 9
	header[5].iov_base = dayname;
	header[5].iov_len = strftime(dayname, sizeof(dayname), "%A", tp);
E 9
E 7
E 2
}

D 7
main()
E 7
I 7
/*
 * Possible date formats include any combination of:
 *	3-charmonth			(January, Jan, Jan)
 *	3-charweekday			(Friday, Monday, mon.)
 *	numeric month or day		(1, 2, 04)
 *
 * Any character may separate them, or they may not be separated.  Any line,
 * following a line that is matched, that starts with "whitespace", is shown
 * along with the matched line.
 */
I 15
int
E 15
isnow(endp)
	char *endp;
E 7
{
D 7
	long t;
	time(&t);
	tprint(t);
	switch(localtime(&t)->tm_wday) {
	case 5:
		t += DAY;
		tprint(t);
	case 6:
		t += DAY;
		tprint(t);
	default:
		t += DAY;
		tprint(t);
E 7
I 7
	int day, flags, month, v1, v2;

#define	F_ISMONTH	0x01
#define	F_ISDAY		0x02
	flags = 0;
	/* didn't recognize anything, skip it */
	if (!(v1 = getfield(endp, &endp, &flags)))
D 15
		return(0);
	if (flags&F_ISDAY || v1 > 12) {
E 15
I 15
		return (0);
	if (flags & F_ISDAY || v1 > 12) {
E 15
		/* found a day */
		day = v1;
		/* if no recognizable month, assume just a day alone */
		if (!(month = getfield(endp, &endp, &flags)))
D 12
			month = tp->tm_mon;
E 12
I 12
			month = tp->tm_mon + 1;
E 12
D 15
	} else if (flags&F_ISMONTH) {
E 15
I 15
	} else if (flags & F_ISMONTH) {
E 15
		month = v1;
		/* if no recognizable day, assume the first */
		if (!(day = getfield(endp, &endp, &flags)))
			day = 1;
	} else {
		v2 = getfield(endp, &endp, &flags);
D 15
		if (flags&F_ISMONTH) {
E 15
I 15
		if (flags & F_ISMONTH) {
E 15
			day = v1;
			month = v2;
		} else {
			/* F_ISDAY set, v2 > 12, or no way to tell */
			month = v1;
			/* if no recognizable day, assume the first */
			day = v2 ? v2 : 1;
		}
E 7
	}
I 12
D 14
	/* ASSUME THIS SHIT WORKS... %^&%&^%^& */
E 14
I 14
D 15
	if (flags&F_ISDAY)
E 15
I 15
	if (flags & F_ISDAY)
E 15
		day = tp->tm_mday + (((day - 1) - tp->tm_wday + 7) % 7);
E 14
E 12
I 7
	day = cumdays[month] + day;

	/* if today or today + offset days */
	if (day >= tp->tm_yday && day <= tp->tm_yday + offset)
D 15
		return(1);
E 15
I 15
		return (1);
E 15
	/* if number of days left in this year + days to event in next year */
	if (yrdays - tp->tm_yday + day <= offset)
D 15
		return(1);
	return(0);
E 15
I 15
		return (1);
	return (0);
E 15
}

I 15
int
E 15
getfield(p, endp, flags)
	char *p, **endp;
	int *flags;
{
	int val;
	char *start, savech;

I 12
D 15
	for (; !isdigit(*p) && !isalpha(*p) && *p != '*'; ++p)
		;
E 15
I 15
	for (; !isdigit(*p) && !isalpha(*p) && *p != '*'; ++p);
E 15
E 12
	if (*p == '*') {			/* `*' is current month */
		*flags |= F_ISMONTH;
D 12
		return(tp->tm_mon);
E 12
I 12
		*endp = p+1;
D 15
		return(tp->tm_mon + 1);
E 15
I 15
		return (tp->tm_mon + 1);
E 15
E 12
	}
	if (isdigit(*p)) {
		val = strtol(p, &p, 10);	/* if 0, it's failure */
D 12
		for (; !isdigit(*p) && !isalpha(*p); ++p);
E 12
I 12
		for (; !isdigit(*p) && !isalpha(*p) && *p != '*'; ++p);
E 12
		*endp = p;
D 15
		return(val);
E 15
I 15
		return (val);
E 15
	}
	for (start = p; isalpha(*++p););
	savech = *p;
	*p = '\0';
D 15
	if (val = getmonth(start))
E 15
I 15
	if ((val = getmonth(start)) != 0)
E 15
		*flags |= F_ISMONTH;
D 15
	else if (val = getday(start))
E 15
I 15
	else if ((val = getday(start)) != 0)
E 15
		*flags |= F_ISDAY;
D 14
	else
E 14
I 14
	else {
		*p = savech;
E 14
D 15
		return(0);
E 15
I 15
		return (0);
E 15
I 14
	}
E 14
D 12
	for (*p = savech; !isdigit(*p) && !isalpha(*p); ++p);
E 12
I 12
	for (*p = savech; !isdigit(*p) && !isalpha(*p) && *p != '*'; ++p);
E 12
	*endp = p;
D 15
	return(val);
E 15
I 15
	return (val);
E 15
}

char path[MAXPATHLEN + 1];

FILE *
opencal()
{
	int fd, pdes[2];
D 15
	char *mktemp();
E 15

	/* open up calendar file as stdin */
	if (!freopen("calendar", "r", stdin)) {
		if (doall)
D 15
			return((FILE *)NULL);
		(void)fprintf(stderr, "calendar: no calendar file.\n");
		exit(1);
E 15
I 15
			return (NULL);
		errx(1, "no calendar file.");
E 15
	}
	if (pipe(pdes) < 0) 
D 15
		return(NULL);
E 15
I 15
		return (NULL);
E 15
	switch (vfork()) {
	case -1:			/* error */
		(void)close(pdes[0]);
		(void)close(pdes[1]);
D 15
		return(NULL);
E 15
I 15
		return (NULL);
E 15
	case 0:
		/* child -- stdin already setup, set stdout to pipe input */
		if (pdes[1] != STDOUT_FILENO) {
			(void)dup2(pdes[1], STDOUT_FILENO);
			(void)close(pdes[1]);
		}
		(void)close(pdes[0]);
D 16
		execl(_PATH_CPP, "cpp", "-I.", _PATH_INCLUDE, NULL);
E 16
I 16
		execl(_PATH_CPP, "cpp", "-P", "-I.", _PATH_INCLUDE, NULL);
E 16
I 15
		(void)fprintf(stderr,
		    "calendar: execl: %s: %s.\n", _PATH_CPP, strerror(errno));
E 15
		_exit(1);
	}
	/* parent -- set stdin to pipe output */
	(void)dup2(pdes[0], STDIN_FILENO);
I 9
	(void)close(pdes[0]);
E 9
	(void)close(pdes[1]);

	/* not reading all calendar files, just set output to stdout */
	if (!doall)
D 15
		return(stdout);
E 15
I 15
		return (stdout);
E 15

	/* set output to a temporary file, so if no output don't send mail */
D 15
	(void)sprintf(path, "%s/_calXXXXXX", _PATH_TMP);
E 15
I 15
	(void)snprintf(path, sizeof(path), "%s/_calXXXXXX", _PATH_TMP);
E 15
	if ((fd = mkstemp(path)) < 0)
D 15
		return(NULL);
	return(fdopen(fd, "w+"));
E 15
I 15
		return (NULL);
	return (fdopen(fd, "w+"));
E 15
}

I 15
void
E 15
closecal(fp)
	FILE *fp;
{
	struct stat sbuf;
D 9
	FILE *iop;
E 9
	int nread, pdes[2], status;
D 15
	char buf[1024], *mktemp();
E 15
I 15
	char buf[1024];
E 15

	if (!doall)
		return;

	(void)rewind(fp);
	if (fstat(fileno(fp), &sbuf) || !sbuf.st_size)
		goto done;
	if (pipe(pdes) < 0) 
		goto done;
	switch (vfork()) {
	case -1:			/* error */
		(void)close(pdes[0]);
		(void)close(pdes[1]);
		goto done;
	case 0:		
		/* child -- set stdin to pipe output */
		if (pdes[0] != STDIN_FILENO) {
			(void)dup2(pdes[0], STDIN_FILENO);
			(void)close(pdes[0]);
		}
		(void)close(pdes[1]);
D 9
		execl(_PATH_SENDMAIL, "-i", "-t", "-F",
		    "\"Reminder Service\"", "-f", "root");
E 9
I 9
		execl(_PATH_SENDMAIL, "sendmail", "-i", "-t", "-F",
		    "\"Reminder Service\"", "-f", "root", NULL);
D 15
		(void)fprintf(stderr, "calendar: %s: %s.\n", 
		    _PATH_SENDMAIL, strerror(errno));
E 15
I 15
		(void)fprintf(stderr,
		    "calendar: %s: %s.\n", _PATH_SENDMAIL, strerror(errno));
E 15
E 9
		_exit(1);
	}
D 9
	/* parent -- rewind file, write to pipe input */
E 9
I 9
	/* parent -- write to pipe input */
E 9
	(void)close(pdes[0]);

D 9
	iop = fdopen(pdes[1], "w");
	(void)fprintf(iop,
"From: %s (Reminder Service)\nTo: %s\nSubject: %s's Calendar\nPrecedence: bulk\n\n",
	    pw->pw_name, pw->pw_name, dayname);
	(void)fflush(iop);
E 9
I 9
	header[1].iov_base = header[3].iov_base = pw->pw_name;
	header[1].iov_len = header[3].iov_len = strlen(pw->pw_name);
	writev(pdes[1], header, 7);
E 9
	while ((nread = read(fileno(fp), buf, sizeof(buf))) > 0)
		(void)write(pdes[1], buf, nread);
	(void)close(pdes[1]);
done:	(void)fclose(fp);
	(void)unlink(path);
	while (wait(&status) >= 0);
}

static char *months[] = {
	"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec", NULL,
};
I 15

int
E 15
getmonth(s)
	register char *s;
{
	register char **p;

	for (p = months; *p; ++p)
		if (!strncasecmp(s, *p, 3))
D 15
			return((p - months) + 1);
	return(0);
E 15
I 15
			return ((p - months) + 1);
	return (0);
E 15
}

static char *days[] = {
	"sun", "mon", "tue", "wed", "thu", "fri", "sat", NULL,
};
I 15

int
E 15
getday(s)
	register char *s;
{
	register char **p;

	for (p = days; *p; ++p)
		if (!strncasecmp(s, *p, 3))
D 15
			return((p - days) + 1);
	return(0);
E 15
I 15
			return ((p - days) + 1);
	return (0);
E 15
}

I 15
void
E 15
usage()
{
	(void)fprintf(stderr, "usage: calendar [-a]\n");
	exit(1);
E 7
}
E 1
