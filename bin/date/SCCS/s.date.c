h40290
s 00003/00003/00208
d D 8.2 95/04/28 09:46:19 bostic 42 41
c POSIX.2 states that user-defined formats are always followed by a
c <newline>
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00005/00005/00206
d D 8.1 93/05/31 14:20:40 bostic 41 40
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00013/00188
d D 5.9 93/04/28 16:25:00 bostic 40 39
c lint, bzero -> memset, prototypes, use library err/warn routines
e
s 00014/00013/00187
d D 5.8 92/03/20 10:11:25 bostic 39 38
c minor cleanup, more consistency checking
e
s 00002/00001/00196
d D 5.7 92/03/15 19:26:26 ralph 38 37
c fix setting date with '.ss' for seconds
e
s 00006/00006/00191
d D 5.6 91/10/17 18:51:56 bostic 37 36
c don't log the date as changed before it actually happens
e
s 00001/00001/00196
d D 5.5 91/03/18 14:20:50 bostic 36 35
c use GMT0, not GMT (defined by POSIX, don't know why)
e
s 00005/00003/00192
d D 5.4 91/03/09 18:50:48 bostic 35 34
c there aren't any OOB's for time_t's; use another variable
e
s 00007/00003/00188
d D 5.3 91/03/09 18:43:45 bostic 34 33
c add -r option so user can specify an Epoch # of seconds
e
s 00003/00002/00188
d D 5.2 91/02/25 07:27:27 bostic 33 32
c ANSI fixes
e
s 00001/00000/00189
d D 5.1 91/01/15 14:03:16 bostic 32 31
c time structure stores month from 0-11; man page shouldn't list
c "impossible" times
e
s 00099/00258/00090
d D 4.28 90/12/04 22:05:47 bostic 31 30
c new version with S5/POSIX formatting capability
c use mktime, instead of doing it by hand
c break out network version into netdate.c
e
s 00001/00011/00347
d D 4.27 90/05/31 20:29:32 bostic 30 29
c new copyright notice
e
s 00001/00001/00357
d D 4.26 90/05/15 19:39:20 bostic 29 28
c string.h is ANSI C include file
e
s 00014/00017/00344
d D 4.25 89/03/14 12:22:53 bostic 28 27
c use new tzfile.h; don't display on error, just exit
e
s 00002/00007/00359
d D 4.24 89/03/06 20:44:57 bostic 27 26
c I can't think of a reason to allow ``24XX'' as settable time.
e
s 00055/00061/00312
d D 4.23 88/09/20 12:22:33 bostic 26 25
c use logwtmp routine; add Berkeley specific copyright
e
s 00001/00001/00372
d D 4.22 87/04/06 12:21:07 bostic 25 24
c new time package, general cleanup
e
s 00018/00018/00355
d D 4.21 87/04/06 12:19:43 bostic 24 23
c new time package, cleanup
e
s 00165/00144/00208
d D 4.20 87/03/24 08:48:32 bostic 23 22
c new time package, general cleanup
e
s 00010/00022/00342
d D 4.19 86/05/18 21:43:21 lepreau 22 21
c lint
e
s 00013/00005/00351
d D 4.18 86/05/18 01:18:42 lepreau 21 20
c reqork exit codes: 0 = success, 1 = failure, 2 = failed to set remote.
c errors got to stderr
e
s 00001/00002/00355
d D 4.17 86/04/29 19:46:54 bloom 20 19
c use absolute instead of relative time for setting network date
e
s 00019/00005/00338
d D 4.16 86/04/13 21:28:42 karels 19 17
c add -n to avoid setting network time
e
s 00007/00002/00341
d R 4.16 86/04/13 21:07:58 karels 18 17
c add -n to avoid timed
e
s 00141/00142/00202
d D 4.15 86/02/17 01:22:06 karels 17 16
c cleanups from sam; connect in order to be able to get async. errors;
c check for ECONNREFUSED later
e
s 00001/00001/00343
d D 4.14 85/11/01 16:57:27 bloom 16 15
c fix syslog message
e
s 00012/00000/00332
d D 4.13 85/10/11 17:57:32 mckusick 15 14
c copyright
e
s 00002/00001/00330
d D 4.12 85/10/11 11:44:39 karels 14 13
c don't complain about not binding if network not turned on
e
s 00002/00001/00329
d D 4.11 85/09/17 23:59:11 eric 13 12
c facilities in syslog
e
s 00002/00003/00328
d D 4.10 85/06/26 11:08:43 bloom 12 11
c don't want date set wrong on errors
e
s 00057/00068/00274
d D 4.9 85/06/25 15:14:50 karels 11 10
c patch things up a bit
e
s 00001/00000/00341
d D 4.8 85/06/19 16:27:36 mckusick 10 9
c need to declare errno
e
s 00213/00033/00128
d D 4.7 85/06/17 21:26:00 gusella 9 6
c now works with timed
e
s 00213/00033/00128
d R 4.7 85/06/14 23:07:21 gusella 8 6
c now works with timed
e
s 00203/00025/00136
d R 4.7 85/06/14 17:01:31 gusella 7 6
c now works with timed
e
s 00001/00001/00160
d D 4.6 83/09/28 10:21:24 ralph 6 5
c wtmp[0] wasn't being set to previous time.
e
s 00001/00001/00160
d D 4.5 83/07/01 23:57:57 wnj 5 4
c include problems
e
s 00004/00001/00157
d D 4.4 83/05/23 00:02:44 sam 4 3
c utmp format changed
e
s 00035/00032/00123
d D 4.3 83/02/28 18:58:55 leres 3 2
c Changed to print out usage if new date is botched. Cleaned
c up a few things
e
s 00046/00058/00109
d D 4.2 83/02/26 18:17:02 sam 2 1
c almost lost changes
e
s 00167/00000/00000
d D 4.1 80/10/01 17:26:05 bill 1 0
c date and time created 80/10/01 17:26:05 by bill
e
u
U
t
T
I 15
/*
D 26
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 26
I 26
D 41
 * Copyright (c) 1985, 1987, 1988 The Regents of the University of California.
 * All rights reserved.
E 41
I 41
 * Copyright (c) 1985, 1987, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 41
 *
D 30
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
E 30
I 30
 * %sccs.include.redist.c%
E 30
E 26
 */

#ifndef lint
D 41
char copyright[] =
D 17
"%Z% Copyright (c) 1985 Regents of the University of California.\n\
E 17
I 17
D 26
"@(#) Copyright (c) 1985 Regents of the University of California.\n\
E 26
I 26
"%Z% Copyright (c) 1985, 1987, 1988 The Regents of the University of California.\n\
E 26
E 17
 All rights reserved.\n";
E 41
I 41
static char copyright[] =
"%Z% Copyright (c) 1985, 1987, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 41
D 26
#endif not lint
E 26
I 26
#endif /* not lint */
E 26

E 15
I 2
#ifndef lint
E 2
I 1
D 9
static char *sccsid = "%W% (Berkeley) %G%";
I 2
#endif
E 9
I 9
D 24
static char sccsid[] = "%W% (Berkeley) %G%";
E 24
I 24
D 25
static char sccsid[] = "@(#)date.c	4.20 (Berkeley) 3/24/87";
E 25
I 25
D 26
static char *sccsid = "%W% (Berkeley) %G%";
E 25
E 24
#endif not lint
E 26
I 26
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 26
E 9

E 2
D 3
#include <stdio.h>
E 3
D 31
/*
D 3
 * date : print date
 * date YYMMDDHHMM[.SS] : set date, if allowed
 * date -u ... : date in GMT
E 3
I 3
 * Date - print and set date
I 9
D 17
 * Modified by Riccardo Gusella to work with timed 
E 17
E 9
E 3
 */
I 3

E 31
I 9
D 11
#include <sys/types.h>
E 11
I 11
#include <sys/param.h>
E 11
E 9
D 23
#include <stdio.h>
E 23
E 3
D 5
#include <time.h>
E 5
I 5
#include <sys/time.h>
I 9
D 17
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define TSPTYPES
#include <protocols/timed.h>
E 17
D 40
#include <sys/file.h>
D 31
#include <errno.h>
E 31
#include <syslog.h>
I 33
#include <unistd.h>
E 40
I 40

#include <ctype.h>
#include <err.h>
#include <fcntl.h>
E 40
E 33
E 9
E 5
D 2
#include <sys/types.h>
#include <sys/timeb.h>
E 2
D 31
#include <utmp.h>
I 23
#include <tzfile.h>
E 31
#include <stdio.h>
D 33
#include <ctype.h>
D 29
#include <strings.h>
E 29
I 29
#include <string.h>
E 33
I 31
#include <stdlib.h>
I 33
#include <string.h>
D 40
#include <ctype.h>
E 40
I 40
#include <syslog.h>
#include <unistd.h>
E 40
E 33
E 31
E 29
E 23
I 9

I 40
#include "extern.h"

E 40
E 9
I 3
D 17
#define WTMP "/usr/adm/wtmp"
I 11
D 12
#define	TRIES		3	/* attempts to contact time server */
E 12
#define WAITACK		2	/* seconds */
#define WAITDATEACK	5	/* seconds */
E 17
I 17
D 23
#define WTMP	"/usr/adm/wtmp"
E 23
I 23
D 26
#define	WTMP		"/usr/adm/wtmp"
E 26
D 31
#define	ATOI2(ar)	(ar[0] - '0') * 10 + (ar[1] - '0'); ar += 2;
E 31
I 31
time_t tval;
int retval, nflag;
E 31
E 23
E 17
E 11
E 3
D 2
long	timbuf;
E 2
I 2

I 40
static void setthetime __P((char *));
static void badformat __P((void));
static void usage __P((void));

int logwtmp __P((char *, char *, char *));

int
E 40
D 9
struct	timeval tv;
E 9
I 9
D 23
struct	timeval tv, now;
E 9
struct	timezone tz;
E 2
char	*ap, *ep, *sp;
D 19
int	uflag;
E 19
I 19
int	uflag, nflag;
I 21
int	retval;
E 23
I 23
D 31
static struct timeval	tv;
static int	retval;
E 23
E 21
E 19

D 23
char	*timezone();
D 17
static	int	dmsize[12] =
E 17
I 17
static	int dmsize[12] =
E 17
D 2
{
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
E 2
I 2
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
I 3
D 17
static char *usage = "usage: date [-u] [yymmddhhmm[.ss]]\n";
E 17
I 17
D 19
static	char *usage = "usage: date [-u] [yymmddhhmm[.ss]]\n";
E 19
I 19
static	char *usage = "usage: date [-n] [-u] [yymmddhhmm[.ss]]\n";
E 23
I 23
static int	dmsize[] =
	{ -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
E 23
E 19
E 17
E 3
E 2

E 31
D 4
struct utmp wtmp[2] = { {"|", "", 0}, {"{", "", 0}};
E 4
I 4
D 23
struct utmp wtmp[2] = {
E 23
I 23
D 26
static struct utmp	wtmp[2] = {
E 23
	{ "|", "", "", 0 },
	{ "{", "", "", 0 }
};
E 4

D 23
char	*ctime();
char	*asctime();
struct	tm *localtime();
struct	tm *gmtime();
I 17
D 22
char	*strcpy();
E 22
I 22
char	*strcpy(), *strncpy();
E 22
char	*username, *getlogin();
I 22
long	time();
uid_t	getuid();
E 22
E 17

I 9
D 17
char *strcpy();
char *username, *getlogin();

D 11
#define WAITACK		10	/* seconds */
#define WAITDATEACK	5	/* seconds */

E 11
int sock, length, port;
D 11
int ready, found;
char hostname[32];
E 11
I 11
char hostname[MAXHOSTNAMELEN];
E 11
struct timeval tout;
struct servent *srvp;
D 11
struct hostent *hp, *gethostbyname();
E 11
struct tsp msg;
struct sockaddr_in sin, dest, from;

E 17
E 9
main(argc, argv)
D 2
char *argv[];
E 2
I 2
	int argc;
	char *argv[];
E 23
I 23
main(argc,argv)
	int	argc;
	char	**argv;
E 26
I 26
main(argc, argv)
	int argc;
	char **argv;
E 26
E 23
E 2
{
I 9
D 17
	int wf;
D 11
	int timed_ack;
E 11
I 11
	int timed_ack, found;
	long waittime;
E 17
E 11
E 9
D 23
	register char *tzn;
E 23
I 23
D 26
	extern int	optind;
	extern char	*optarg;
D 24
	static char	usage[] = "usage: date [-n] [-u] [yymmddhhmm[.ss]]\n";
E 24
	struct timezone	tz;
	char	*ap,			/* time string */
		*tzn;			/* time zone */
	int	ch,			/* getopts char */
		uflag,			/* do it in GMT */
		nflag,			/* only set time locally */
		wf;			/* wtmp file descriptor */
	long	time();
	uid_t	getuid();
	char	*username, *getlogin();
E 26
I 26
	extern int optind;
	extern char *optarg;
	struct timezone tz;
D 31
	char *ap, *tzn;
	int ch, uflag, nflag;
	char *username, *getlogin();
	time_t time();
E 31
I 31
D 35
	int ch;
E 35
I 35
	int ch, rflag;
E 35
	char *format, buf[1024];
E 31
E 26
E 23
I 11
D 17
	fd_set ready;
E 11
I 10
	extern int errno;
E 10
D 2
	struct timeb info;
E 2
D 9
	int wf, rc;
E 9
I 9
	int bytenetorder(), bytehostorder();
E 17
E 9
D 2
	extern char _sobuf[];
E 2

I 13
D 24
	openlog("date", LOG_ODELAY, LOG_AUTH);
E 13
D 2
	setbuf(stdout, _sobuf);
E 2
D 9
	rc = 0;
D 2
	ftime(&info);
E 2
I 2
	gettimeofday(&tv, &tz);
E 9
I 9
D 23
	(void) gettimeofday(&tv, &tz);
I 11
	now = tv;
E 23
E 11

E 24
E 9
E 2
D 3
	if (argc>1 && argv[1][0]=='-' && argv[1][1]=='u') {
E 3
I 3
D 19
	if (argc > 1 && strcmp(argv[1], "-u") == 0) {
E 19
I 19
D 23
	while (argc > 1 && argv[1][0] == '-') {
		while (*++argv[1])
		    switch ((int)argv[1][0]) {

		    case 'n':
			nflag++;
E 23
I 23
D 31
	nflag = uflag = 0;
E 31
D 24
	while ((ch = getopt(argc,argv,"nu")) != EOF)
E 24
I 24
	tz.tz_dsttime = tz.tz_minuteswest = 0;
I 35
	rflag = 0;
E 35
D 26
	while ((ch = getopt(argc,argv,"d:nut:")) != EOF)
E 26
I 26
D 34
	while ((ch = getopt(argc, argv, "d:nut:")) != EOF)
E 34
I 34
D 42
	while ((ch = getopt(argc, argv, "d:nr:ut:")) != EOF)
E 42
I 42
	while ((ch = getopt(argc, argv, "d:nr:ut:")) != -1)
E 42
E 34
E 26
E 24
		switch((char)ch) {
D 26
		case 'd':
E 26
I 26
		case 'd':		/* daylight savings time */
E 26
			tz.tz_dsttime = atoi(optarg) ? 1 : 0;
E 23
			break;
D 23

		    case 'u':
			uflag++;
E 23
I 23
D 26
		case 'n':
E 26
I 26
		case 'n':		/* don't set network */
E 26
			nflag = 1;
E 23
			break;
I 34
D 35
		case 'r':
E 35
I 35
		case 'r':		/* user specified seconds */
			rflag = 1;
E 35
			tval = atol(optarg);
			break;
E 34
D 23

		    default:
D 21
			printf(usage);
E 21
I 21
			fprintf(stderr, usage);
E 23
I 23
D 24
		case 't':
			tz.tz_minuteswest = atoi(optarg);
			break;
E 24
D 26
		case 'u':
E 26
I 26
D 31
		case 'u':		/* do it in GMT */
E 26
			uflag = 1;
E 31
I 31
		case 'u':		/* do everything in GMT */
D 36
			(void)setenv("TZ", "GMT", 1);
E 36
I 36
			(void)setenv("TZ", "GMT0", 1);
E 36
E 31
			break;
I 24
D 26
		case 't':	/* error check; we can't allow "PST" */
E 26
I 26
		case 't':		/* minutes west of GMT */
D 31
					/* error check; we can't allow "PST" */
E 31
I 31
					/* error check; don't allow "PST" */
E 31
E 26
			if (isdigit(*optarg)) {
				tz.tz_minuteswest = atoi(optarg);
				break;
			}
D 31
			/*FALLTHROUGH*/
E 31
I 31
			/* FALLTHROUGH */
E 31
E 24
		default:
D 24
			fputs(usage,stderr);
E 24
I 24
			usage();
E 24
E 23
E 21
D 31
			exit(1);
E 31
		}
E 19
E 3
D 23
		argc--;
		argv++;
E 23
I 23
	argc -= optind;
	argv += optind;

D 31
	if (argc > 1) {
D 24
		fputs(usage,stderr);
E 24
I 24
		usage();
E 24
		exit(1);
E 23
D 19
		uflag++;
E 19
	}
D 2
	if(argc > 1) {
E 2
I 2
D 9
	if (argc > 1) {
E 2
		ap = argv[1];
I 6
		wtmp[0].ut_time = tv.tv_sec;
E 6
		if (gtime()) {
D 3
			printf("date: bad conversion\n");
E 3
I 3
			printf(usage);
E 9
I 9
D 23
	if (argc > 2) {
D 21
		printf(usage);
E 21
I 21
		fprintf(stderr, usage);
E 23
I 23

E 31
I 31
	/*
	 * If -d or -t, set the timezone or daylight savings time; this
	 * doesn't belong here, there kernel should not know about either.
	 */
E 31
	if ((tz.tz_minuteswest || tz.tz_dsttime) &&
D 26
	    settimeofday((struct timeval *)NULL,&tz)) {
E 26
I 26
D 37
	    settimeofday((struct timeval *)NULL, &tz)) {
E 37
I 37
D 40
	    settimeofday(NULL, &tz)) {
E 37
E 26
D 28
		perror("settimeofday");
		retval = 1;
		goto display;
E 28
I 28
		perror("date: settimeofday");
		exit(1);
E 28
	}
E 40
I 40
	    settimeofday(NULL, &tz))
		err(1, "settimeofday");
E 40

D 26
	if (gettimeofday(&tv,&tz)) {
E 26
I 26
D 31
	if (gettimeofday(&tv, &tz)) {
E 26
D 28
		perror("gettimeofday");
E 28
I 28
		perror("date: gettimeofday");
E 31
I 31
D 34
	if (time(&tval) == (time_t)-1) {
E 34
I 34
D 35
	if (!tval && time(&tval) == (time_t)-1) {
E 35
I 35
D 40
	if (!rflag && time(&tval) == -1) {
E 35
E 34
		perror("date: time");
E 31
E 28
E 23
E 21
		exit(1);
	}
E 40
I 40
	if (!rflag && time(&tval) == -1)
		err(1, "time");
E 40
D 23
	if (argc == 1) 
E 23
I 23

D 31
	if (!argc)
E 23
		goto display;
E 31
I 31
D 42
	format = "%a %b %e %H:%M:%S %Z %Y\n";
E 42
I 42
	format = "%a %b %e %H:%M:%S %Z %Y";
E 42
E 31

D 23
	if (getuid() != 0) {
D 21
		printf("You are not superuser: date not set\n");
E 21
I 21
		fprintf(stderr, "You are not superuser: date not set\n");
E 23
I 23
D 24
	if (getuid()) {
		fputs("You are not superuser: date not set.\n",stderr);
E 23
		retval = 1;
E 21
D 11
		exit(1);
E 11
I 11
		goto display;
E 11
	}
D 23
	username = getlogin();
D 11
	if (username == NULL) {
		printf("Cannot record your name: date not set\n");
		exit(1);
	}
	syslog(LOG_ERR, "date: set by %s", username);
E 11
I 11
D 21
	if (username == NULL)		/* single-user or no tty */
E 21
I 21
	if (username == NULL || *username == '\0')  /* single-user or no tty */
E 21
		username = "root";
E 23
D 13
	syslog(LOG_SECURITY, "date: set by %s", username);
E 13
I 13
D 16
	syslog(LOG_NOTICE, "date: set by %s", username);
E 16
I 16
D 17
	syslog(LOG_NOTICE, "set by %s", username);
E 17
E 16
E 13
E 11

E 24
D 23
	ap = argv[1];
E 23
D 26
	wtmp[0].ut_time = tv.tv_sec;
E 26
D 23
	if (gtime()) {
D 21
		printf(usage);
E 21
I 21
		fprintf(stderr, usage);
E 23
I 23
D 31
	if (gtime(*argv)) {
D 24
		fprintf(stderr,usage);
E 24
I 24
		usage();
E 24
E 23
D 28
		retval = 1;
E 21
D 11
		exit(1);
E 11
I 11
		goto display;
E 28
I 28
		exit(1);
E 31
I 31
	/* allow the operands in any order */
	if (*argv && **argv == '+') {
		format = *argv + 1;
		++argv;
E 31
E 28
E 11
	}
D 23
	/* convert to GMT assuming local time */
	if (uflag == 0) {
		tv.tv_sec += (long)tz.tz_minuteswest*60;
		/* now fix up local daylight time */
E 23
I 23

D 31
	if (!uflag) {		/* convert to GMT assuming local time */
D 28
		tv.tv_sec += (long)tz.tz_minuteswest * SECS_PER_MIN;
E 28
I 28
		tv.tv_sec += (long)tz.tz_minuteswest * SECSPERMIN;
E 28
				/* now fix up local daylight time */
E 23
D 11
		if (localtime((long *)&tv.tv_sec)->tm_isdst)
E 11
I 11
		if (localtime((time_t *)&tv.tv_sec)->tm_isdst)
E 11
D 23
			tv.tv_sec -= 60*60;
E 23
I 23
D 28
			tv.tv_sec -= SECS_PER_HOUR;
E 28
I 28
			tv.tv_sec -= SECSPERHOUR;
E 31
I 31
	if (*argv) {
		setthetime(*argv);
		++argv;
E 31
E 28
E 23
	}
D 11
	(void) open("/etc/timed", O_WRONLY, 01700);
	if (errno != ETXTBSY) {
		if (settimeofday(&tv, (struct timezone *)0) < 0) {
			perror("settimeofday");
E 9
E 3
			exit(1);
		}
D 9
		/* convert to GMT assuming local time */
D 3
		if (uflag==0) {
E 3
I 3
		if (uflag == 0) {
E 3
D 2
			timbuf += (long)info.timezone*60;
E 2
I 2
			tv.tv_sec += (long)tz.tz_minuteswest*60;
E 2
			/* now fix up local daylight time */
D 2
			if(localtime(&timbuf)->tm_isdst)
				timbuf -= 60*60;
E 2
I 2
			if (localtime(&tv.tv_sec)->tm_isdst)
				tv.tv_sec -= 60*60;
E 9
I 9
		if ((wf = open(WTMP, 1)) >= 0) {
			(void) time((long *)&wtmp[1].ut_time);
			(void) lseek(wf, (off_t)0L, 2);
			(void) write(wf, (char *)wtmp, sizeof(wtmp));
			(void) close(wf);
E 9
E 2
		}
D 2
		time(&wtmp[0].ut_time);
		if(stime(&timbuf) < 0) {
E 2
I 2
D 9
		tv.tv_sec = tv.tv_sec;
D 6
		wtmp[0].ut_time = tv.tv_sec;
E 6
		if (settimeofday(&tv, (struct timezone *)0) < 0) {
E 2
			rc++;
D 3
			printf("date: no permission\n");
		} else if ((wf = open("/usr/adm/wtmp", 1)) >= 0) {
E 3
I 3
			perror("Failed to set date");
		} else if ((wf = open(WTMP, 1)) >= 0) {
E 3
			time(&wtmp[1].ut_time);
			lseek(wf, 0L, 2);
			write(wf, (char *)wtmp, sizeof(wtmp));
			close(wf);
E 9
I 9
		goto display;
	}

E 11
I 11
D 17
	
E 11
/*
 * Here we set the date in the machines controlled by timedaemons
 * by communicating the new date to the local timedaemon. 
 * If the timedaemon is in the master state, it performs the correction on 
 * all slaves. If it is in the slave state, it notifies the master 
 * that a correction is needed.
 */
E 17
I 17
D 19
	if (!settime(tv)) {
E 19
I 19
D 23
	if (nflag || !settime(tv)) {
E 19
		int wf;
E 17

D 17
	srvp = getservbyname("timed", "udp");
	if (srvp == 0) {
		fprintf(stderr, "udp/timed: unknown service\n");
D 11
		exit(1);
E 11
I 11
		goto oldway;
E 11
	}	
	dest.sin_port = srvp->s_port;
	dest.sin_family = AF_INET;
I 11
	dest.sin_addr.s_addr = htonl((u_long)INADDR_ANY);
E 11
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
D 11
		perror("opening socket");
		exit(1);
E 11
I 11
		if (errno != EPROTONOSUPPORT)
			perror("socket");
		goto oldway;
E 11
	}

	sin.sin_family = AF_INET;
	for (port = IPPORT_RESERVED - 1; port > IPPORT_RESERVED / 2; port--) {
		sin.sin_port = htons((u_short)port);
		if (bind(sock, (struct sockaddr *)&sin, sizeof (sin)) >= 0)
			break;
D 11
		if (errno != EADDRINUSE && errno != EADDRNOTAVAIL) {
E 11
I 11
		if (errno != EADDRINUSE) {
E 11
D 14
			perror("bind");
E 14
I 14
			if (errno != EADDRNOTAVAIL)
				perror("bind");
E 14
			(void) close(sock);
D 11
			exit(1);
E 11
I 11
			goto oldway;
E 11
E 9
		}
	}
D 3
	if (rc==0)
E 3
I 3
D 9
	if (rc == 0)
E 3
D 2
		time(&timbuf);
	if(uflag) {
		ap = asctime(gmtime(&timbuf));
E 2
I 2
		time(&tv.tv_sec);
E 9
I 9
	if (port == IPPORT_RESERVED / 2) {
		fprintf(stderr, "socket: All ports in use\n");
		(void) close(sock);
D 11
		exit(1);
E 11
I 11
		goto oldway;
E 11
	}

D 11
	(void) gethostname(hostname,sizeof(hostname));
	hp = gethostbyname(hostname);
	if (hp == NULL) {
		perror("gethostbyname");
		exit(1);
	}
	bcopy(hp->h_addr, &dest.sin_addr.s_addr, hp->h_length);

E 11
	msg.tsp_type = TSP_DATE;
I 11
	msg.tsp_vers = TSPVERSION;
	(void) gethostname(hostname, sizeof(hostname));
E 11
	(void) strcpy(msg.tsp_name, hostname);
D 11
	(void) gettimeofday(&now, (struct timezone *)0);
E 11
D 12
	timevalsub(&tv, &now);
E 12
	msg.tsp_time = tv;
I 12
	timevalsub(&msg.tsp_time, &now);
E 12
	bytenetorder(&msg);
	length = sizeof(struct sockaddr_in);
	if (sendto(sock, (char *)&msg, sizeof(struct tsp), 0, 
						&dest, length) < 0) {
D 11
		perror("sendto");
		exit(1);
E 11
I 11
		if (errno != ECONNREFUSED)
			perror("sendto");
		goto oldway;
E 11
	}

	timed_ack = -1;
D 11
	tout.tv_sec = WAITACK;
	tout.tv_usec = 0;
E 11
I 11
	waittime = WAITACK;
E 11
loop:
D 11
	ready = 1<<sock;
	found = select(20, &ready, (int *)0, (int *)0, &tout);
	if (found) {
E 11
I 11
	tout.tv_sec = waittime;
	tout.tv_usec = 0;
	FD_ZERO(&ready);
	FD_SET(sock, &ready);
	found = select(FD_SETSIZE, &ready, (fd_set *)0, (fd_set *)0, &tout);
	if (found > 0 && FD_ISSET(sock, &ready)) {
E 11
		length = sizeof(struct sockaddr_in);
		if (recvfrom(sock, (char *)&msg, sizeof(struct tsp), 0, 
							&from, &length) < 0) {
			perror("recvfrom");
D 11
			exit(1);
E 11
I 11
			goto oldway;
E 11
		}
		bytehostorder(&msg);

		switch (msg.tsp_type) {

		case TSP_ACK:
			timed_ack = TSP_ACK;
D 11
			tout.tv_sec = WAITDATEACK;
			tout.tv_usec = 0;
E 11
I 11
			waittime = WAITDATEACK;
E 11
			goto loop;
D 11
			break;
E 11
		case TSP_DATEACK:
D 11
			goto display;
			break;
E 11
I 11
D 12
			goto oldway;
E 12
I 12
			goto display;
E 12
E 11
		default:
D 11
			printf("Wrong ack received: %s\n", 
E 11
I 11
			printf("Wrong ack received from timed: %s\n", 
E 11
						tsptype[msg.tsp_type]);
			timed_ack = -1;
			break;
		}
	}

D 11
	if (timed_ack == TSP_ACK) {
E 11
I 11
	if (timed_ack == TSP_ACK)
E 11
		printf("Network date being set\n");
D 11
		exit(0);
	} else {
		printf("Communication problems\n");
		exit(1);
E 11
I 11
	else {
		printf("Communication error with timed\n");
oldway:
E 17
		if (settimeofday(&tv, (struct timezone *)0) < 0) {
E 23
I 23
D 31
	if (nflag || !netsettime(tv)) {
D 26
		if (settimeofday(&tv,(struct timezone *)0)) {
E 26
I 26
		logwtmp("|", "date", "");
		if (settimeofday(&tv, (struct timezone *)NULL)) {
E 26
E 23
D 28
			perror("settimeofday");
I 21
			retval = 1;
E 21
			goto display;
E 28
I 28
			perror("date: settimeofday");
			exit(1);
E 28
		}
D 17
		if ((wf = open(WTMP, 1)) >= 0) {
E 17
I 17
D 23
		if ((wf = open(WTMP, O_WRONLY|O_APPEND)) >= 0) {
E 17
			(void) time((time_t *)&wtmp[1].ut_time);
D 17
			(void) lseek(wf, (off_t)0L, 2);
E 17
			(void) write(wf, (char *)wtmp, sizeof(wtmp));
			(void) close(wf);
E 23
I 23
D 26
		if ((wf = open(WTMP,O_WRONLY|O_APPEND)) < 0)
			fputs("date: can't write wtmp file.\n",stderr);
		else {
			(void)time((time_t *)&wtmp[1].ut_time);
			/*NOSTRICT*/
			(void)write(wf,(char *)wtmp,sizeof(wtmp));
			(void)close(wf);
E 23
		}
E 26
I 26
		logwtmp("{", "date", "");
E 26
E 11
	}
E 31
I 17
D 23
	syslog(LOG_NOTICE, "set by %s", username);
E 23
E 17

I 23
D 31
	username = getlogin();
	if (!username || *username == '\0')	/* single-user or no tty */
		username = "root";
D 24
	syslog(LOG_NOTICE,"set by %s",username);
E 24
I 24
D 26
	syslog(LOG_AUTH | LOG_NOTICE,"date set by %s",username);
E 26
I 26
	syslog(LOG_AUTH | LOG_NOTICE, "date set by %s", username);
E 31
I 31
	if (*argv && **argv == '+')
		format = *argv + 1;
E 31
E 26
E 24

E 23
D 31
display:
D 23
	(void) gettimeofday(&tv, (struct timezone *)0);
E 23
I 23
D 26
	if (gettimeofday(&tv,(struct timezone *)0)) {
E 26
I 26
	if (gettimeofday(&tv, (struct timezone *)NULL)) {
E 26
D 28
		perror("gettimeofday");
E 28
I 28
		perror("date: gettimeofday");
E 28
		exit(1);
	}
E 23
E 9
	if (uflag) {
D 9
		ap = asctime(gmtime(&tv.tv_sec));
E 9
I 9
D 11
		ap = asctime(gmtime((long *)&tv.tv_sec));
E 11
I 11
		ap = asctime(gmtime((time_t *)&tv.tv_sec));
E 11
E 9
E 2
		tzn = "GMT";
D 23
	} else {
		struct tm *tp;
E 23
I 23
	}
	else {
D 26
		struct tm	*tp;
E 26
I 26
		struct tm *tp;
E 26

E 23
D 2
		tp = localtime(&timbuf);
E 2
I 2
D 9
		tp = localtime(&tv.tv_sec);
E 9
I 9
D 11
		tp = localtime((long *)&tv.tv_sec);
E 11
I 11
		tp = localtime((time_t *)&tv.tv_sec);
E 11
E 9
E 2
		ap = asctime(tp);
D 2
		tzn = timezone(info.timezone, tp->tm_isdst);
E 2
I 2
D 23
		tzn = timezone(tz.tz_minuteswest, tp->tm_isdst);
E 23
I 23
		tzn = tp->tm_zone;
E 23
E 2
	}
D 23
	printf("%.20s", ap);
	if (tzn)
		printf("%s", tzn);
	printf("%s", ap+19);
E 23
I 23
D 26
	printf("%.20s%s%s",ap,tzn,ap + 19);
E 26
I 26
	printf("%.20s%s%s", ap, tzn, ap + 19);
E 31
I 31
	(void)strftime(buf, sizeof(buf), format, localtime(&tval));
D 42
	(void)printf("%s", buf);
E 42
I 42
	(void)printf("%s\n", buf);
E 42
E 31
E 26
E 23
I 21
	exit(retval);
E 21
D 9
	exit(rc);
E 9
}

D 23
gtime()
E 23
I 23
D 31
/*
 * gtime --
 *	convert user's time into number of seconds
 */
static
gtime(ap)
D 26
	register char	*ap;		/* user argument */
E 26
I 26
	register char *ap;
E 31
I 31
#define	ATOI2(ar)	((ar)[0] - '0') * 10 + ((ar)[1] - '0'); (ar) += 2;
I 40
void
E 40
setthetime(p)
	register char *p;
E 31
E 26
E 23
{
D 23
	register int i, year, month;
	int day, hour, mins, secs;
	struct tm *L;
	char x;
E 23
I 23
D 26
	register int	year, month;
	register char	*C;		/* pointer into time argument */
	struct tm	*L;
	int	day, hour, mins, secs;
E 26
I 26
D 31
	register int year, month;
	register char *C;
	struct tm *L;
	int day, hour, mins, secs;
E 31
I 31
	register struct tm *lt;
	struct timeval tv;
D 39
	int dot;
	char *t;
E 39
I 39
	char *dot, *t;
E 39
E 31
E 26
E 23

D 3
	ep=ap;
E 3
I 3
D 23
	ep = ap;
E 3
	while(*ep) ep++;
D 3
	sp=ap;
	while(sp<ep) {
E 3
I 3
	sp = ap;
	while(sp < ep) {
E 3
		x = *sp;
		*sp++ = *--ep;
		*ep = x;
E 23
I 23
D 26
	for (secs = 0, C = ap;*C;++C) {
E 26
I 26
D 31
	for (secs = 0, C = ap; *C; ++C) {
E 26
		if (*C == '.') {		/* seconds provided */
			if (strlen(C) != 3)
				return(1);
			*C = NULL;
			secs = (C[1] - '0') * 10 + (C[2] - '0');
			break;
		}
		if (!isdigit(*C))
			return(-1);
E 23
	}
E 31
I 31
D 39
	for (t = p, dot = 0; *t; ++t)
		if (!isdigit(*t) && (*t != '.' || dot++))
			badformat();
E 39
I 39
	for (t = p, dot = NULL; *t; ++t) {
		if (isdigit(*t))
			continue;
		if (*t == '.' && dot == NULL) {
			dot = t;
			continue;
		}
		badformat();
	}
E 39
E 31
D 3
	sp=ap;
E 3
I 3
D 23
	sp = ap;
E 3
D 2
	time(&timbuf);
	L=localtime(&timbuf);
E 2
I 2
D 9
	gettimeofday(&tv, 0);
D 3
	L=localtime(&tv.tv_sec);
E 3
I 3
	L = localtime(&tv.tv_sec);
E 9
I 9
	(void) gettimeofday(&tv, (struct timezone *)0);
E 23
I 23

E 23
D 11
	L = localtime((long *)&tv.tv_sec);
E 11
I 11
D 31
	L = localtime((time_t *)&tv.tv_sec);
E 11
E 9
E 3
E 2
D 23
	secs = gp(-1);
D 2
	if(*sp!='.') {
E 2
I 2
D 3
	if (*sp!='.') {
E 2
		mins=secs;
		secs=0;
	} else {sp++;
E 3
I 3
	if (*sp != '.') {
		mins = secs;
		secs = 0;
	} else {
		sp++;
E 3
		mins = gp(-1);
E 23
I 23
	year = L->tm_year;			/* defaults */
	month = L->tm_mon + 1;
	day = L->tm_mday;
E 31
I 31
	lt = localtime(&tval);
E 31

D 31
	switch ((int)(C - ap)) {		/* length */
		case 10:			/* yymmddhhmm */
			year = ATOI2(ap);
		case 8:				/* mmddhhmm */
			month = ATOI2(ap);
		case 6:				/* ddhhmm */
			day = ATOI2(ap);
		case 4:				/* hhmm */
			hour = ATOI2(ap);
			mins = ATOI2(ap);
			break;
		default:
			return(1);
E 23
	}
E 31
I 31
D 39
	if (t = index(p, '.')) {		/* .ss */
		*t++ = '\0';
I 38
		if (strlen(t) != 2)
E 39
I 39
	if (dot != NULL) {			/* .ss */
		*dot++ = '\0';
		if (strlen(dot) != 2)
E 39
			badformat();
D 39
		lt->tm_sec = ATOI2(t);
E 39
I 39
		lt->tm_sec = ATOI2(dot);
E 39
E 38
		if (lt->tm_sec > 61)
			badformat();
	} else
		lt->tm_sec = 0;
E 31
D 23
	hour = gp(-1);
	day = gp(L->tm_mday);
	month = gp(L->tm_mon+1);
	year = gp(L->tm_year);
D 2
	if(*sp)
		return(1);
	if( month<1 || month>12 ||
E 2
I 2
	if (*sp)
		return (1);
D 3
	if (month<1 || month>12 ||
E 2
	    day<1 || day>31 ||
	    mins<0 || mins>59 ||
	    secs<0 || secs>59)
E 3
I 3
	if (month < 1 || month > 12 ||
	    day < 1 || day > 31 ||
	    mins < 0 || mins > 59 ||
	    secs < 0 || secs > 59)
E 3
D 2
		return(1);
E 2
I 2
		return (1);
E 23
I 23
D 39

D 31
	if (*ap || month < 1 || month > 12 || day < 1 || day > 31 ||
D 27
	     mins < 0 || mins > 59 || secs < 0 || secs > 59)
		return(1);
E 23
E 2
D 3
	if (hour==24) {
		hour=0; day++;
E 3
I 3
	if (hour == 24) {
I 23
		++day;
E 23
		hour = 0;
D 23
		day++;
E 23
E 3
	}
D 3
	if (hour<0 || hour>23)
E 3
I 3
D 23
	if (hour < 0 || hour > 23)
E 3
D 2
		return(1);
	timbuf = 0;
E 2
I 2
		return (1);
E 23
I 23
	else if (hour < 0 || hour > 23)
E 27
I 27
	     hour < 0 || hour > 23 || mins < 0 || mins > 59 ||
	     secs < 0 || secs > 59)
E 27
		return(1);
E 31
I 31
	for (t = p; *t; ++t)
		if (!isdigit(*t))
			badformat();
E 39
E 31

E 23
D 31
	tv.tv_sec = 0;
E 2
D 23
	year += 1900;
D 2
	for(i=1970; i<year; i++)
		timbuf += dysize(i);
E 2
I 2
D 3
	for (i=1970; i<year; i++)
E 3
I 3
	for (i = 1970; i < year; i++)
E 3
		tv.tv_sec += dysize(i);
E 2
	/* Leap year */
D 3
	if (dysize(year)==366 && month >= 3)
E 3
I 3
	if (dysize(year) == 366 && month >= 3)
E 3
D 2
		timbuf++;
	while(--month)
		timbuf += dmsize[month-1];
	timbuf += day-1;
	timbuf = 24*timbuf + hour;
	timbuf = 60*timbuf + mins;
	timbuf = 60*timbuf + secs;
	return(0);

E 2
I 2
		tv.tv_sec++;
E 23
I 23
	year += TM_YEAR_BASE;
	if (isleap(year) && month > 2)
		++tv.tv_sec;
	for (--year;year >= EPOCH_YEAR;--year)
D 28
		tv.tv_sec += isleap(year) ? DAYS_PER_LYEAR : DAYS_PER_NYEAR;
E 28
I 28
		tv.tv_sec += isleap(year) ? DAYSPERLYEAR : DAYSPERNYEAR;
E 28
E 23
	while (--month)
D 23
		tv.tv_sec += dmsize[month-1];
	tv.tv_sec += day-1;
	tv.tv_sec = 24*tv.tv_sec + hour;
	tv.tv_sec = 60*tv.tv_sec + mins;
	tv.tv_sec = 60*tv.tv_sec + secs;
	return (0);
E 23
I 23
		tv.tv_sec += dmsize[month];
	tv.tv_sec += day - 1;
D 28
	tv.tv_sec = HOURS_PER_DAY * tv.tv_sec + hour;
	tv.tv_sec = MINS_PER_HOUR * tv.tv_sec + mins;
	tv.tv_sec = SECS_PER_MIN * tv.tv_sec + secs;
E 28
I 28
	tv.tv_sec = HOURSPERDAY * tv.tv_sec + hour;
	tv.tv_sec = MINSPERHOUR * tv.tv_sec + mins;
	tv.tv_sec = SECSPERMIN * tv.tv_sec + secs;
E 28
	return(0);
E 23
E 2
}

D 23
gp(dfault)
{
	register int c, d;

D 2
	if(*sp==0)
		return(dfault);
E 2
I 2
D 3
	if (*sp==0)
E 3
I 3
	if (*sp == 0)
E 3
		return (dfault);
E 2
D 3
	c = (*sp++)-'0';
	d = (*sp ? (*sp++)-'0' : 0);
D 2
	if(c<0 || c>9 || d<0 || d>9)
		return(-1);
	return(c+10*d);
E 2
I 2
	if (c<0 || c>9 || d<0 || d>9)
E 3
I 3
	c = (*sp++) - '0';
	d = (*sp ? (*sp++) - '0' : 0);
	if (c < 0 || c > 9 || d < 0 || d > 9)
E 3
		return (-1);
	return (c+10*d);
I 9
}

E 23
I 17
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define TSPTYPES
#include <protocols/timed.h>

D 26
#define WAITACK		2	/* seconds */
#define WAITDATEACK	5	/* seconds */
E 26
I 26
#define	WAITACK		2	/* seconds */
#define	WAITDATEACK	5	/* seconds */
E 26

extern	int errno;
/*
 * Set the date in the machines controlled by timedaemons
 * by communicating the new date to the local timedaemon. 
 * If the timedaemon is in the master state, it performs the
 * correction on all slaves.  If it is in the slave state, it
 * notifies the master that a correction is needed.
I 21
 * Returns 1 on success, 0 on failure.
E 21
 */
D 23
settime(tv)
	struct timeval tv;
E 23
I 23
D 26
static
E 26
netsettime(ntv)
	struct timeval ntv;
E 23
{
	int s, length, port, timed_ack, found, err;
	long waittime;
	fd_set ready;
	char hostname[MAXHOSTNAMELEN];
	struct timeval tout;
	struct servent *sp;
	struct tsp msg;
	struct sockaddr_in sin, dest, from;

	sp = getservbyname("timed", "udp");
	if (sp == 0) {
D 23
		fprintf(stderr, "udp/timed: unknown service\n");
E 23
I 23
D 26
		fputs("udp/timed: unknown service\n",stderr);
E 26
I 26
		fputs("udp/timed: unknown service\n", stderr);
E 26
E 23
I 21
		retval = 2;
E 21
		return (0);
E 31
I 31
	switch (strlen(p)) {
	case 10:				/* yy */
		lt->tm_year = ATOI2(p);
		if (lt->tm_year < 69)		/* hack for 2000 ;-} */
			lt->tm_year += 100;
		/* FALLTHROUGH */
	case 8:					/* mm */
		lt->tm_mon = ATOI2(p);
		if (lt->tm_mon > 12)
			badformat();
I 32
		--lt->tm_mon;			/* time struct is 0 - 11 */
E 32
		/* FALLTHROUGH */
	case 6:					/* dd */
		lt->tm_mday = ATOI2(p);
		if (lt->tm_mday > 31)
			badformat();
		/* FALLTHROUGH */
	case 4:					/* hh */
		lt->tm_hour = ATOI2(p);
		if (lt->tm_hour > 23)
			badformat();
		/* FALLTHROUGH */
	case 2:					/* mm */
		lt->tm_min = ATOI2(p);
		if (lt->tm_min > 59)
			badformat();
		break;
	default:
		badformat();
E 31
D 23
	}	
E 23
I 23
	}
E 23
D 31
	dest.sin_port = sp->s_port;
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = htonl((u_long)INADDR_ANY);
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		if (errno != EPROTONOSUPPORT)
			perror("date: socket");
		goto bad;
	}
D 22
	bzero(&sin, sizeof (sin));
E 22
I 22
	bzero((char *)&sin, sizeof (sin));
E 22
	sin.sin_family = AF_INET;
	for (port = IPPORT_RESERVED - 1; port > IPPORT_RESERVED / 2; port--) {
		sin.sin_port = htons((u_short)port);
		if (bind(s, (struct sockaddr *)&sin, sizeof (sin)) >= 0)
			break;
		if (errno != EADDRINUSE) {
			if (errno != EADDRNOTAVAIL)
				perror("date: bind");
			goto bad;
		}
	}
	if (port == IPPORT_RESERVED / 2) {
D 23
		fprintf(stderr, "date: All ports in use\n");
E 23
I 23
D 26
		fputs("date: All ports in use\n",stderr);
E 26
I 26
		fputs("date: All ports in use\n", stderr);
E 26
E 23
		goto bad;
	}
D 20
	msg.tsp_type = TSP_DATE;
E 20
I 20
	msg.tsp_type = TSP_SETDATE;
E 20
	msg.tsp_vers = TSPVERSION;
D 23
	(void) gethostname(hostname, sizeof (hostname));
E 23
I 23
	if (gethostname(hostname, sizeof (hostname))) {
D 28
		perror("gethostname");
E 28
I 28
		perror("date: gethostname");
E 28
		goto bad;
	}
E 23
	(void) strncpy(msg.tsp_name, hostname, sizeof (hostname));
D 20
	timevalsub(&tv, &now);
E 20
	msg.tsp_seq = htons((u_short)0);
D 23
	msg.tsp_time.tv_sec = htonl((u_long)tv.tv_sec);
	msg.tsp_time.tv_usec = htonl((u_long)tv.tv_usec);
E 23
I 23
	msg.tsp_time.tv_sec = htonl((u_long)ntv.tv_sec);
	msg.tsp_time.tv_usec = htonl((u_long)ntv.tv_usec);
E 23
	length = sizeof (struct sockaddr_in);
	if (connect(s, &dest, length) < 0) {
		perror("date: connect");
		goto bad;
	}
D 22
	if (send(s, &msg, sizeof (struct tsp), 0) < 0) {
E 22
I 22
	if (send(s, (char *)&msg, sizeof (struct tsp), 0) < 0) {
E 22
		if (errno != ECONNREFUSED)
			perror("date: send");
		goto bad;
	}
	timed_ack = -1;
	waittime = WAITACK;
loop:
	tout.tv_sec = waittime;
	tout.tv_usec = 0;
	FD_ZERO(&ready);
	FD_SET(s, &ready);
	found = select(FD_SETSIZE, &ready, (fd_set *)0, (fd_set *)0, &tout);
	length = sizeof(err);
D 22
	if (getsockopt(s, SOL_SOCKET, SO_ERROR, &err, &length) == 0 && err) {
E 22
I 22
	if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&err, &length) == 0
	    && err) {
E 22
		errno = err;
		if (errno != ECONNREFUSED)
			perror("date: send (delayed error)");
		goto bad;
	}
	if (found > 0 && FD_ISSET(s, &ready)) {
		length = sizeof (struct sockaddr_in);
D 22
		if (recvfrom(s, &msg, sizeof (struct tsp), 0, &from,
E 22
I 22
		if (recvfrom(s, (char *)&msg, sizeof (struct tsp), 0, &from,
E 22
		    &length) < 0) {
			if (errno != ECONNREFUSED)
				perror("date: recvfrom");
			goto bad;
		}
		msg.tsp_seq = ntohs(msg.tsp_seq);
		msg.tsp_time.tv_sec = ntohl(msg.tsp_time.tv_sec);
		msg.tsp_time.tv_usec = ntohl(msg.tsp_time.tv_usec);
		switch (msg.tsp_type) {
E 31

D 31
		case TSP_ACK:
			timed_ack = TSP_ACK;
			waittime = WAITDATEACK;
			goto loop;
E 31
I 31
	/* convert broken-down time to GMT clock time */
	if ((tval = mktime(lt)) == -1)
		badformat();
E 31

D 31
		case TSP_DATEACK:
D 22
			close(s);
E 22
I 22
			(void)close(s);
E 22
			return (1);
E 31
I 31
D 37
	if (!(p = getlogin()))			/* single-user or no tty */
		p = "root";
	syslog(LOG_AUTH | LOG_NOTICE, "date set by %s", p);
E 31

E 37
D 31
		default:
			fprintf(stderr,
			    "date: Wrong ack received from timed: %s\n", 
			    tsptype[msg.tsp_type]);
			timed_ack = -1;
			break;
E 31
I 31
	/* set the time */
	if (nflag || netsettime(tval)) {
		logwtmp("|", "date", "");
		tv.tv_sec = tval;
		tv.tv_usec = 0;
D 37
		if (settimeofday(&tv, (struct timezone *)NULL)) {
E 37
I 37
		if (settimeofday(&tv, NULL)) {
E 37
			perror("date: settimeofday");
			exit(1);
E 31
		}
I 31
		logwtmp("{", "date", "");
E 31
	}
I 37

	if ((p = getlogin()) == NULL)
		p = "???";
	syslog(LOG_AUTH | LOG_NOTICE, "date set by %s", p);
E 37
D 31
	if (timed_ack == -1)
D 23
		fprintf(stderr,
		    "date: Can't reach time daemon, time set locally.\n");
E 23
I 23
		fputs("date: Can't reach time daemon, time set locally.\n",
		    stderr);
E 23
bad:
D 22
	close(s);
E 22
I 22
	(void)close(s);
E 22
I 21
	retval = 2;
E 21
	return (0);
E 31
I 24
}

I 40
static void
E 40
I 31
badformat()
{
D 40
	(void)fprintf(stderr, "date: illegal time format.\n");
E 40
I 40
	warnx("illegal time format");
E 40
	usage();
}

I 40
static void
E 40
E 31
usage()
{
D 26
	fputs("usage: date [-nu] [-d dst] [-t minutes_west] [yymmddhhmm[.ss]]\n",stderr);
E 26
I 26
D 31
	fputs("usage: date [-nu] [-d dst] [-t minutes_west] [yymmddhhmm[.ss]]\n", stderr);
E 31
I 31
	(void)fprintf(stderr,
D 34
"usage: date [-nu] [-d dst] [-t west] [+format] [yy[mm[dd[hh]]]]mm[.ss]]\n");
E 34
I 34
	    "usage: date [-nu] [-d dst] [-r seconds] [-t west] [+format]\n");
	(void)fprintf(stderr, "            [yy[mm[dd[hh]]]]mm[.ss]]\n");
E 34
	exit(1);
E 31
E 26
E 24
D 22
}

E 17
timevalsub(t1, t2)
D 17
struct timeval *t1, *t2;
E 17
I 17
	register struct timeval *t1, *t2;
E 17
{
	t1->tv_sec -= t2->tv_sec;
	t1->tv_usec -= t2->tv_usec;
	if (t1->tv_usec < 0) {
		t1->tv_sec--;
		t1->tv_usec += 1000000;
	}
	if (t1->tv_usec >= 1000000) {
		t1->tv_sec++;
		t1->tv_usec -= 1000000;
	}
E 22
D 17
}

bytenetorder(ptr)
struct tsp *ptr;
{
	ptr->tsp_seq = htons((u_short)ptr->tsp_seq);
	ptr->tsp_time.tv_sec = htonl((u_long)ptr->tsp_time.tv_sec);
	ptr->tsp_time.tv_usec = htonl((u_long)ptr->tsp_time.tv_usec);
}

bytehostorder(ptr)
struct tsp *ptr;
{
	ptr->tsp_seq = ntohs((u_short)ptr->tsp_seq);
	ptr->tsp_time.tv_sec = ntohl((u_long)ptr->tsp_time.tv_sec);
	ptr->tsp_time.tv_usec = ntohl((u_long)ptr->tsp_time.tv_usec);
E 17
E 9
E 2
}
E 1
