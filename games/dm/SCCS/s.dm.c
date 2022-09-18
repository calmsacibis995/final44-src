h42518
s 00005/00005/00298
d D 8.1 93/05/31 16:52:21 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00011/00290
d D 5.17 93/03/22 05:53:36 bostic 17 16
c lint
e
s 00001/00010/00300
d D 5.16 91/02/28 09:36:58 bostic 16 15
c ANSI
e
s 00001/00011/00309
d D 5.15 90/06/01 13:05:29 bostic 15 14
c new copyright notice
e
s 00005/00003/00315
d D 5.14 90/05/01 21:10:04 bostic 14 13
c remove path of utmp file
e
s 00002/00013/00316
d D 5.13 90/01/06 15:06:01 bostic 13 12
c after reorg, don't need config.MACHINE any more
e
s 00002/00016/00327
d D 5.12 89/05/29 17:59:35 mckusick 12 11
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00010/00021/00333
d D 5.11 89/04/12 17:32:06 bostic 11 10
c add pathnames.h, move config files, if no config file, just play
e
s 00003/00002/00351
d D 5.10 89/02/16 17:02:15 bostic 10 9
c make failure a bit more informative
e
s 00001/00001/00352
d D 5.9 88/09/26 14:45:03 bostic 9 8
c dm messes up stop time; bug report 4.3BSD-tahoe/games/1
e
s 00010/00005/00343
d D 5.8 88/06/18 14:47:03 bostic 8 7
c install approved copyright notice
e
s 00057/00045/00291
d D 5.7 88/03/25 14:00:59 bostic 7 6
c reformat to kernel normal; add per machine config files
e
s 00006/00006/00330
d D 5.6 87/12/29 17:05:27 bostic 6 5
c don't change directory; programs get wrong relative path names
e
s 00010/00004/00326
d D 5.5 87/11/30 16:09:44 bostic 5 4
c Berkeley code; correct copyright
e
s 00105/00102/00225
d D 5.4 87/10/08 18:25:03 bostic 4 3
c change to keyword search
e
s 00005/00005/00322
d D 5.3 87/09/21 12:17:52 bostic 3 2
c change default directories; priority is never negative
e
s 00118/00109/00209
d D 5.2 87/09/20 12:57:11 bostic 2 1
c general cleanup to minimize work; fix setuid stuff; this is 
c probably the first "real" version
e
s 00318/00000/00000
d D 5.1 87/09/18 13:11:17 bostic 1 0
c date and time created 87/09/18 13:11:17 by bostic
e
u
U
t
T
I 1
/*
D 18
 * Copyright (c) 1987 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 15
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 8
E 5
 */

#ifndef lint
D 18
char copyright[] =
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
 All rights reserved.\n";
E 18
I 18
static char copyright[] =
"%Z% Copyright (c) 1987, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 18
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#include <sys/param.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/resource.h>
D 17
#include <pwd.h>
#include <utmp.h>
E 17
I 17

#include <ctype.h>
E 17
#include <nlist.h>
I 17
#include <pwd.h>
E 17
#include <stdio.h>
D 17
#include <ctype.h>
E 17
I 17
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <utmp.h>

E 17
I 11
#include "pathnames.h"
E 11

I 14
extern int errno;
E 14
D 2
#define	LOG			/* if want game usage logged */

E 2
D 6
#define	GAMEHIDE	"/usr/games/hide"
E 6
I 6
D 7
#define	GAMEHIDE	"/usr/games/hide/"
E 6
D 3
#define	NOGAMING	"/etc/nogames"
#define	CONTROL		"/usr/games/game.control"
E 3
I 3
#define	NOGAMING	"/usr/games/nogames"
#define	CONTROL		"/usr/games/dm.config"
E 3
#ifdef LOG
D 3
#define	LOGFILE		"/usr/adm/gamelog"
E 3
I 3
#define	LOGFILE		"/usr/adm/dm.log"
E 3
#endif

E 7
D 2
static struct tm	*ct;		/* current time structure */
E 2
I 2
D 4
static FILE	*cfp;
E 4
E 2
static time_t	now;			/* current time value */
D 2
static double	maxload = -1;		/* max load for game */
static int	maxusers = -1;		/* max users for game */
		priority = 0;		/* priority game runs at */
static char	*game;			/* requested game */
E 2
I 2
static int	priority = 0;		/* priority game runs at */
static char	*game,			/* requested game */
		*gametty;		/* from tty? */
E 2

I 7
D 17
/*ARGSUSED*/
E 17
I 17
int
E 17
E 7
D 2
typedef struct dow {
	char	*day;
	int	start, stop;
} DOW;

static DOW	days[] = {
	"sunday",	25, -1,
	"monday",	25, -1,
	"tuesday",	25, -1,
	"wednesday",	25, -1,
	"thursday",	25, -1,
	"friday",	25, -1,
	"saturday",	25, -1,
	0,		0,  0,
};

E 2
main(argc, argv)
D 7
	int	argc;
	char	**argv;
E 7
I 7
	int argc;
D 17
	char **argv;
E 17
I 17
	char *argv[];
E 17
E 7
{
D 2
	FILE	*fp;
	char	*C, *hour(), *rindex();
	struct tm	*localtime();
	time_t	time();
E 2
I 2
D 4
	char	*C, *rindex();
E 2
	double	load();
E 4
I 4
D 7
	char	*cp, *rindex(), *ttyname();
	time_t	time();
E 7
I 7
D 17
	char *cp, *rindex(), *ttyname();
	time_t time();
E 17
I 17
	char *cp;
E 17
E 7
E 4

	nogamefile();
I 4
	game = (cp = rindex(*argv, '/')) ? ++cp : *argv;
E 4

D 2
	if (argc == 1) {
		fputs("dm: game\n", stderr);
		exit(1);
	}
E 2
I 2
D 4
	if (!strcmp(*argv, "dm"))
E 4
I 4
	if (!strcmp(game, "dm"))
E 4
		exit(0);
E 2

D 2
	if (!(fp = fopen(CONTROL, "r"))) {
E 2
I 2
D 4
	if (!(cfp = fopen(CONTROL, "r"))) {
E 2
		fprintf(stderr, "dm: unable to read %s.\n", CONTROL);
		exit(1);
	}
E 4
I 4
	gametty = ttyname(0);
	(void)time(&now);
	read_config();
E 4
D 7

E 7
D 2
	read_days(fp);
	(void)time(&now);
	ct = localtime(&now);
	if (ct->tm_hour >= days[ct->tm_wday].start && ct->tm_hour <= days[ct->tm_wday].stop) {
		fprintf(stderr, "dm: Sorry, games are only available from %s to %s today.\n", hour(days[ct->tm_wday].start), hour(days[ct->tm_wday].stop));
		exit(0);
	}
E 2
I 2
D 4
	read_days();
	read_ttys();
E 2

D 2
	++argv;
E 2
	game = (C = rindex(*argv, '/')) ? ++C : *argv;
I 2
	read_games();
E 2

E 4
D 2
	read_games(fp);
	if (maxusers >= 0 && maxusers <= users()) {
		fputs("dm: Sorry, there are too many users logged on right now.\n", stderr);
		exit(0);
	}
	if (maxload >= 0 && maxload < load()) {
		fputs("dm: Sorry, the load average is too high right now.\n", stderr);
		exit(0);
	}
	(void)fclose(fp);

E 2
#ifdef LOG
	logfile();
#endif
	play(argv);
I 2
D 4
/*NOTREACHED*/
E 4
I 4
	/*NOTREACHED*/
E 4
E 2
}

/*
 * play --
 *	play the game
 */
I 7
D 11
#define	GAMEHIDE	"/usr/games/hide/"
E 11
E 7
D 16
static
E 16
play(args)
D 7
	char	**args;
E 7
I 7
	char **args;
E 7
{
D 2
	uid_t	uid;
	gid_t	gid;

E 2
D 6
	if (chdir(GAMEHIDE)) {
		perror("dm: chdir");
		exit(1);
	}
E 6
I 6
D 7
	char	pbuf[MAXPATHLEN], *strcpy();
E 7
I 7
D 10
	char pbuf[MAXPATHLEN], *strcpy();
E 10
I 10
D 14
	extern int errno;
E 14
D 17
	char pbuf[MAXPATHLEN], *strcpy(), *strerror();
E 17
I 17
	char pbuf[MAXPATHLEN];
E 17
E 10
E 7

D 11
	(void)strcpy(pbuf, GAMEHIDE);
	(void)strcpy(pbuf + sizeof(GAMEHIDE) - 1, game);
E 11
I 11
	(void)strcpy(pbuf, _PATH_HIDE);
	(void)strcpy(pbuf + sizeof(_PATH_HIDE) - 1, game);
E 11
E 6
D 3
	if (priority && setpriority(PRIO_PROCESS, 0, priority) < 0)
E 3
I 3
D 4
	if (priority > 0 && setpriority(PRIO_PROCESS, 0, priority) < 0)
E 3
		fputs("dm: unable to set priority!\n", stderr);
E 4
I 4
	if (priority > 0)	/* < 0 requires root */
		(void)setpriority(PRIO_PROCESS, 0, priority);
E 4
D 2
	uid = getuid();
	setreuid(uid, uid);
	gid = getgid();
	setregid(gid, gid);
E 2
I 2
	setgid(getgid());	/* we run setgid kmem; lose it */
E 2
D 6
	execv(game, args);
E 6
I 6
	execv(pbuf, args);
E 6
D 2
	fprintf(stderr, "dm: can't find %s.\n", game);
E 2
I 2
D 10
	perror("dm");
E 10
I 10
	(void)fprintf(stderr, "dm: %s: %s\n", pbuf, strerror(errno));
E 10
E 2
	exit(1);
}

I 2
D 4
#define	lcontrol(buf)	(buf[0] == '%' && buf[1] == '%')
#define	lignore(buf)	(buf[0] == '\n' || buf[0] == '#')
E 4
E 2
/*
D 4
 * read_days --
D 2
 *	read through days listed in the control file
E 2
I 2
 *	read through days listed in the control file, decide
 *	if current time is an okay play time.
E 4
I 4
 * read_config --
 *	read through config file, looking for key words.
E 4
E 2
 */
I 7
D 11
#define	CONTROL		"/usr/games/dm.config"
E 11
E 7
D 16
static
E 16
D 2
read_days(fp)
	register FILE	*fp;
E 2
I 2
D 4
read_days()
E 4
I 4
read_config()
E 4
E 2
{
I 4
D 7
	FILE	*cfp;
	char	lbuf[BUFSIZ], f1[40], f2[40], f3[40], f4[40], f5[40];
E 7
I 7
	FILE *cfp;
D 13
	char *control, *host, *index(), *strcpy();
D 11
	char lbuf[BUFSIZ], path[MAXHOSTNAMELEN + sizeof(CONTROL)];
E 11
I 11
	char lbuf[BUFSIZ], path[MAXHOSTNAMELEN + sizeof(_PATH_CONFIG)];
E 11
	char f1[40], f2[40], f3[40], f4[40], f5[40];
E 13
I 13
	char lbuf[BUFSIZ], f1[40], f2[40], f3[40], f4[40], f5[40];
E 13
E 7

D 7
	if (!(cfp = fopen(CONTROL, "r"))) {
		fprintf(stderr, "dm: unable to read %s.\n", CONTROL);
E 7
I 7
D 11
	host = &path[sizeof(CONTROL)];
E 11
I 11
D 13
	host = &path[sizeof(_PATH_CONFIG)];
E 11
	if (gethostname(host, MAXHOSTNAMELEN)) {
		perror("dm: gethostname");
E 7
		exit(1);
	}
I 7
D 11
	(void)strcpy(path, control = CONTROL);
E 11
I 11
	(void)strcpy(path, control = _PATH_CONFIG);
E 11
	host[-1] = '.';
	if (host = index(host, '.'))
		*host = '\0';
D 11
	if (!(cfp = fopen(path, "r")) && !(cfp = fopen(control, "r"))) {
		fprintf(stderr, "dm: unable to read %s or %s.\n",
		    path, control);
		exit(1);
	}
E 11
I 11
	if (!(cfp = fopen(path, "r")) && !(cfp = fopen(control, "r")))
E 13
I 13
	if (!(cfp = fopen(_PATH_CONFIG, "r")))
E 13
		return;
E 11
E 7
	while (fgets(lbuf, sizeof(lbuf), cfp))
		switch(*lbuf) {
		case 'b':		/* badtty */
			if (sscanf(lbuf, "%s%s", f1, f2) != 2 ||
			    strcasecmp(f1, "badtty"))
				break;
			c_tty(f2);
			break;
		case 'g':		/* game */
			if (sscanf(lbuf, "%s%s%s%s%s",
			    f1, f2, f3, f4, f5) != 5 || strcasecmp(f1, "game"))
				break;
			c_game(f2, f3, f4, f5);
			break;
		case 't':		/* time */
			if (sscanf(lbuf, "%s%s%s%s", f1, f2, f3, f4) != 4 ||
			    strcasecmp(f1, "time"))
				break;
			c_day(f2, f3, f4);
		}
	(void)fclose(cfp);
}

/*
 * c_day --
 *	if day is today, see if okay to play
 */
D 16
static
E 16
c_day(s_day, s_start, s_stop)
D 7
	char	*s_day, *s_start, *s_stop;
E 7
I 7
	char *s_day, *s_start, *s_stop;
E 7
{
E 4
D 2
	register DOW	*dp;
	char	lbuf[BUFSIZ], f1[20], f2[20], f3[20];
E 2
I 2
D 7
	static char	*days[] = {
E 7
I 7
	static char *days[] = {
E 7
		"sunday", "monday", "tuesday", "wednesday",
		"thursday", "friday", "saturday",
	};
D 4
	struct tm	*ct;
	register char	*dp;
E 4
I 4
D 7
	static struct tm	*ct;
E 4
	int	start, stop;
E 7
I 7
	static struct tm *ct;
	int start, stop;
E 7
D 4
	char	lbuf[BUFSIZ], f1[40], f2[40], f3[40];
	time_t	time();
E 4
E 2

D 2
	while (fgets(lbuf, sizeof(lbuf), fp)) {
		if (lbuf[0] == '\n' || lbuf[0] == '#')
E 2
I 2
D 4
	(void)time(&now);
	ct = localtime(&now);
	dp = days[ct->tm_wday];

	while (fgets(lbuf, sizeof(lbuf), cfp)) {
		if (lignore(lbuf))
E 2
			continue;
D 2
		/* special line separates days from game names */
		if (lbuf[0] == '%' && lbuf[1] == '%')
E 2
I 2
		if (lcontrol(lbuf))
E 2
			return;
D 2
		if (sscanf(lbuf, "%s%s%s\n", f1, f2, f3) != 3)
E 2
I 2
		if (sscanf(lbuf, "%s%s%s", f1, f2, f3) != 3)
E 2
			continue;
D 2
		for (dp = days; dp->day; ++dp)
			if (dp->start <= 0 && !strcasecmp(dp->day, f1)) {
				if (isdigit(*f2))
					dp->start = atoi(f2);
				if (isdigit(*f3))
					dp->stop = atoi(f3);
				break;
E 2
I 2
		if (!strcasecmp(dp, f1)) {
			if (!isdigit(*f2) || !isdigit(*f3))
				continue;
			start = atoi(f2);
			stop = atoi(f3);
			if (ct->tm_hour >= start && ct->tm_hour <= stop) {
				fputs("dm: Sorry, games are not available from ", stderr);
				hour(start);
				fputs(" to ", stderr);
				hour(stop);
				fputs(" today.\n", stderr);
				exit(0);
E 2
			}
I 2
			continue;
		}
E 4
I 4
	if (!ct)
		ct = localtime(&now);
	if (strcasecmp(s_day, days[ct->tm_wday]))
		return;
	if (!isdigit(*s_start) || !isdigit(*s_stop))
		return;
	start = atoi(s_start);
	stop = atoi(s_stop);
D 9
	if (ct->tm_hour >= start && ct->tm_hour <= stop) {
E 9
I 9
	if (ct->tm_hour >= start && ct->tm_hour < stop) {
E 9
		fputs("dm: Sorry, games are not available from ", stderr);
		hour(start);
		fputs(" to ", stderr);
		hour(stop);
		fputs(" today.\n", stderr);
		exit(0);
E 4
E 2
	}
}

/*
I 2
D 4
 * read_ttys --
 *	read through ttys listed in the control file, decide if this
 *	tty can be used for games.
E 4
I 4
 * c_tty --
 *	decide if this tty can be used for games.
E 4
 */
D 16
static
E 16
D 4
read_ttys()
E 4
I 4
c_tty(tty)
D 7
	char	*tty;
E 7
I 7
	char *tty;
E 7
E 4
{
D 4
	register char	*p_tty;
	char	lbuf[BUFSIZ], f1[40], f2[40],
		*ttyname(), *rindex();
E 4
I 4
D 7
	static int	first = 1;
	static char	*p_tty;
	char	*rindex();
E 7
I 7
	static int first = 1;
	static char *p_tty;
D 17
	char *rindex();
E 17
E 7
E 4

D 4
	gametty = ttyname(0);
	if (p_tty = rindex(gametty, '/'))
		++p_tty;
	while (fgets(lbuf, sizeof(lbuf), cfp)) {
		if (lignore(lbuf))
			continue;
		if (lcontrol(lbuf))
			return;
		if (sscanf(lbuf, "%s%s", f1, f2) != 2)
			continue;
		if (strcasecmp("badtty", f1))
			continue;
		if (!strcmp(gametty, f2) || p_tty && !strcmp(p_tty, f2)) {
			fprintf(stderr, "dm: Sorry, you may not play games on %s.\n", gametty);
			exit(0);
		}
E 4
I 4
	if (first) {
		p_tty = rindex(gametty, '/');
		first = 0;
E 4
	}
I 4

	if (!strcmp(gametty, tty) || p_tty && !strcmp(p_tty, tty)) {
		fprintf(stderr, "dm: Sorry, you may not play games on %s.\n", gametty);
		exit(0);
	}
E 4
}

/*
E 2
D 4
 * read_games --
D 2
 *	read through games listed in the control file
E 2
I 2
 *	read through games listed in the control file, decide if this
 *	game can be played now.
E 4
I 4
 * c_game --
 *	see if game can be played now.
E 4
E 2
 */
D 16
static
E 16
D 2
read_games(fp)
	register FILE	*fp;
E 2
I 2
D 4
read_games()
E 4
I 4
c_game(s_game, s_load, s_users, s_priority)
D 7
	char	*s_game, *s_load, *s_users, *s_priority;
E 7
I 7
	char *s_game, *s_load, *s_users, *s_priority;
E 7
E 4
E 2
{
D 2
	register char	*C;
	char	lbuf[BUFSIZ], f1[20], f2[20], f3[20];
	double	atof();
E 2
I 2
D 4
	char	lbuf[BUFSIZ], f1[40], f2[40], f3[40], f4[40];
E 4
I 4
D 7
	static int	found;
	double	load();
E 7
I 7
	static int found;
	double load();
E 7
E 4
E 2

D 2
	while (fgets(lbuf, sizeof(lbuf), fp)) {
		if (lbuf[0] == '\n' || lbuf[0] == '#')
E 2
I 2
D 4
	while (fgets(lbuf, sizeof(lbuf), cfp)) {
		if (lignore(lbuf))
E 2
			continue;
D 2
		for (C = lbuf; *C && !isspace(*C); ++C);
		*C = '\0';
		if (!strcmp(game, lbuf) || !strcasecmp("default", lbuf)) {
			if (sscanf(++C, "%s%s%s\n", f1, f2, f3) != 3)
				break;
			if (isdigit(*f1))
				maxload = atof(f1);
			if (isdigit(*f2))
				maxusers = atoi(f2);
			if (isdigit(*f3) || *f3 == '-' || *f3 == '+')
				priority = atoi(f3);
E 2
I 2
		if (lcontrol(lbuf))
			return;
		if (sscanf(lbuf, "%s%s%s%s", f1, f2, f3, f4) != 4)
E 2
			break;
I 2
		if (!strcmp(game, f1) || !strcasecmp("default", f1)) {
			if (isdigit(*f2) && atoi(f2) < load()) {
				fputs("dm: Sorry, the load average is too high right now.\n", stderr);
				exit(0);
			}
			if (isdigit(*f3) && atoi(f3) <= users()) {
				fputs("dm: Sorry, there are too many users logged on right now.\n", stderr);
				exit(0);
			}
D 3
			if (isdigit(*f4) || *f4 == '-' || *f4 == '+')
E 3
I 3
			if (isdigit(*f4))
E 3
				priority = atoi(f3);
			return;
E 2
		}
E 4
I 4
	if (found)
		return;
	if (strcmp(game, s_game) && strcasecmp("default", s_game))
		return;
	++found;
	if (isdigit(*s_load) && atoi(s_load) < load()) {
		fputs("dm: Sorry, the load average is too high right now.\n", stderr);
		exit(0);
E 4
	}
I 4
	if (isdigit(*s_users) && atoi(s_users) <= users()) {
		fputs("dm: Sorry, there are too many users logged on right now.\n", stderr);
		exit(0);
	}
	if (isdigit(*s_priority))
		priority = atoi(s_priority);
E 4
}

D 7
static struct	nlist nl[] = {
E 7
I 7
D 12
static struct nlist nl[] = {
E 7
	{ "_avenrun" },
#define	X_AVENRUN	0
	{ "" },
};

E 12
/*
 * load --
 *	return 15 minute load average
 */
D 16
static double
E 16
I 16
double
E 16
load()
{
D 7
	double	avenrun[3];
	int	kmem;
	long	lseek();
E 7
I 7
	double avenrun[3];
D 12
	int kmem;
	long lseek();
E 12
E 7

D 12
	if (nlist("/vmunix", nl)) {
		fputs("dm: nlist of /vmunix failed.\n", stderr);
E 12
I 12
	if (getloadavg(avenrun, sizeof(avenrun)/sizeof(avenrun[0])) < 0) {
		fputs("dm: getloadavg() failed.\n", stderr);
E 12
		exit(1);
	}
D 12
	if ((kmem = open("/dev/kmem", O_RDONLY, 0)) < 0) {
		perror("dm: /dev/kmem");
		exit(1);
	}
	(void)lseek(kmem, (long)nl[X_AVENRUN].n_value, L_SET);
D 4
	(void)read(kmem, avenrun, sizeof(avenrun));
E 4
I 4
	(void)read(kmem, (char *)avenrun, sizeof(avenrun));
E 12
E 4
	return(avenrun[2]);
}

/*
 * users --
 *	return current number of users
I 4
 *	todo: check idle time; if idle more than X minutes, don't
 *	count them.
E 4
 */
D 16
static
E 16
users()
{
I 14
	
E 14
D 7
	register int	nusers,
			utmp;
	struct utmp	buf;
E 7
I 7
	register int nusers, utmp;
	struct utmp buf;
E 7

D 14
	if ((utmp = open("/etc/utmp", O_RDONLY, 0)) < 0) {
		perror("dm: /etc/utmp");
E 14
I 14
	if ((utmp = open(_PATH_UTMP, O_RDONLY, 0)) < 0) {
		(void)fprintf(stderr, "dm: %s: %s\n",
		    _PATH_UTMP, strerror(errno));
E 14
		exit(1);
	}
	for (nusers = 0; read(utmp, (char *)&buf, sizeof(struct utmp)) > 0;)
		if (buf.ut_name[0] != '\0')
			++nusers;
	return(nusers);
}

D 11
/*
 * nogamefile --
 *	if the file NOGAMING exists, no games allowed.
 *	file may also contain a message for the user.
 */
I 7
#define	NOGAMING	"/usr/games/nogames"
E 11
E 7
D 16
static
E 16
nogamefile()
{
D 7
	register int	fd, n;
	char	buf[BUFSIZ];
E 7
I 7
	register int fd, n;
	char buf[BUFSIZ];
E 7

D 11
	if ((fd = open(NOGAMING, O_RDONLY, 0)) >= 0) {
E 11
I 11
	if ((fd = open(_PATH_NOGAMES, O_RDONLY, 0)) >= 0) {
E 11
#define	MESG	"Sorry, no games right now.\n\n"
		(void)write(2, MESG, sizeof(MESG) - 1);
		while ((n = read(fd, buf, sizeof(buf))) > 0)
			(void)write(2, buf, n);
		exit(1);
	}
}

/*
 * hour --
 *	print out the hour in human form
 */
D 2
static char *
E 2
I 2
D 16
static
E 16
E 2
hour(h)
D 7
	int	h;
E 7
I 7
	int h;
E 7
{
D 2
	static char	buf[20];

	if (!h)
		return("midnight");
	if (h == 12)
		return("noon");
	if (h < 12)
		(void)sprintf(buf, "%d pm", h - 12);
	else
		(void)sprintf(buf, "%d am", h);
	return(buf);
E 2
I 2
	switch(h) {
	case 0:
		fputs("midnight", stderr);
		break;
	case 12:
		fputs("noon", stderr);
		break;
	default:
		if (h > 12)
			fprintf(stderr, "%dpm", h - 12);
		else
			fprintf(stderr, "%dam", h);
	}
E 2
}

#ifdef LOG
I 7
/*
 * logfile --
 *	log play of game
 */
D 11
#define	LOGFILE		"/usr/adm/dm.log"
E 11
E 7
D 16
static
E 16
logfile()
{
D 7
	struct passwd	*pw, *getpwuid();
	FILE	*lp;
	uid_t	uid;
	int	lock_cnt;
D 2
	char	*ctime(), *ttyname();
E 2
I 2
	char	*ctime();
E 7
I 7
D 17
	struct passwd *pw, *getpwuid();
E 17
I 17
	struct passwd *pw;
E 17
	FILE *lp;
	uid_t uid;
	int lock_cnt;
D 17
	char *ctime();
E 17
E 7
E 2

D 11
	if (lp = fopen(LOGFILE, "a")) {
E 11
I 11
	if (lp = fopen(_PATH_LOG, "a")) {
E 11
		for (lock_cnt = 0;; ++lock_cnt) {
			if (!flock(fileno(lp), LOCK_EX))
				break;
			if (lock_cnt == 4) {
				perror("dm: log lock");
				(void)fclose(lp);
				return;
			}
			sleep((u_int)1);
		}
		if (pw = getpwuid(uid = getuid()))
			fputs(pw->pw_name, lp);
		else
			fprintf(lp, "%u", uid);
D 2
		fprintf(lp, "\t%s\t%s\t%s", game, ttyname(0), ctime(&now));
E 2
I 2
		fprintf(lp, "\t%s\t%s\t%s", game, gametty, ctime(&now));
E 2
		(void)fclose(lp);
		(void)flock(fileno(lp), LOCK_UN);
	}
}
D 7
#endif
E 7
I 7
#endif /* LOG */
E 7
E 1
