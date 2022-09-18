h38940
s 00001/00001/00466
d D 8.4 95/04/28 12:37:56 bostic 41 40
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00001/00465
d D 8.3 95/04/27 16:22:27 bostic 40 39
c shutdown(8) shouldn't remove the nologin file if `-k' was used.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00055/00032/00411
d D 8.2 94/02/16 09:10:47 bostic 39 38
c display the right amount of time before a shutdown
c minor random cleanups for ANSI C
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
e
s 00005/00005/00438
d D 8.1 93/06/05 11:21:09 bostic 38 37
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00442
d D 5.16 91/02/03 01:43:39 torek 37 36
c getpwuid() is already declared in <pwd.h>
e
s 00061/00061/00382
d D 5.15 90/06/22 19:00:12 bostic 36 35
c use mktime(3) to convert times -- current code was wrong, anyway.
c lots of minor lint cleanup
e
s 00001/00011/00442
d D 5.14 90/06/01 16:29:50 bostic 35 34
c new copyright notice
e
s 00012/00006/00441
d D 5.13 90/02/24 19:52:01 karels 34 33
c restore user/host in banner, suppress wall banner
e
s 00001/00004/00446
d D 5.12 89/10/28 11:34:49 bostic 33 32
c hostname never used.
e
s 00001/00001/00449
d D 5.11 89/09/05 11:12:58 bostic 32 31
c typo; print a newline so it flushses
e
s 00021/00024/00429
d D 5.10 89/04/02 15:12:26 bostic 31 29
c add pathnames.h, fix tzfile 
e
s 00019/00020/00433
d R 5.10 89/04/02 15:11:14 bostic 30 29
c add pathnames.h, fix tzfile 
e
s 00046/00025/00407
d D 5.9 88/12/16 12:00:51 bostic 29 28
c '-' option means read from stdin, don't do it by default.  Fix call to
c reboot/halt, minor cleanups
e
s 00356/00336/00076
d D 5.8 88/09/18 16:48:05 bostic 28 27
c allow absolute time; use wall(1), getopt(3), new timing mechanism
c read message from stdin by default; complete rewrite
e
s 00002/00000/00410
d D 5.7 87/12/26 13:07:23 bostic 27 26
c predeclare finish; fix for ANSI C
e
s 00019/00015/00391
d D 5.6 86/05/26 22:12:27 karels 26 25
c consistency, use SIGTERM once then SIGKILL's, uniform logging (once)
e
s 00004/00002/00402
d D 5.5 86/05/12 17:50:55 eric 25 24
c lint
e
s 00020/00067/00384
d D 5.4 86/05/12 17:45:16 eric 24 23
c shutdownlog subsumed into syslog (as LOG_AUTH)
e
s 00052/00046/00399
d D 5.3 85/11/06 14:18:38 bloom 23 22
c make it lint (almost, putc can't be done easily)
e
s 00040/00004/00405
d D 5.2 85/11/01 16:55:51 bloom 22 21
c add fastboot and nosync flags from David Grubb (dgg@mit-athena)
e
s 00014/00002/00395
d D 5.1 85/05/28 15:36:29 dist 21 20
c Add copyright
e
s 00008/00005/00389
d D 4.20 84/02/02 13:03:00 karels 20 19
c writes restart after alarms!
e
s 00002/00002/00392
d D 4.19 83/06/17 21:19:24 root 19 18
c merge monet
e
s 00003/00002/00391
d D 4.18 83/06/02 17:41:19 sam 18 17
c purge nice
e
s 00002/00000/00391
d D 4.17 83/05/22 23:57:27 sam 17 16
c utmp changed format
e
s 00001/00000/00390
d D 4.16 83/04/29 14:39:10 edward 16 15
c Now ignores SIGTTOU
e
s 00000/00007/00390
d D 4.15 83/01/16 17:31:46 sam 15 14
c check in for bill
e
s 00066/00038/00331
d D 4.14 82/10/23 20:50:21 mckusick 14 13
c lint, output format
e
s 00002/00002/00367
d D 4.13 82/03/15 04:26:59 root 13 12
c machine independent
e
s 00003/00001/00366
d D 4.12 82/03/15 04:25:44 root 12 11
c machine independent
e
s 00004/00003/00363
d D 4.11 82/02/01 08:29:40 root 11 10
c fix by rrh: prints out sysname!username instead of just username
e
s 00004/00001/00362
d D 4.10 81/06/12 13:24:07 root 10 9
c I supressed the sending of messages to sleeper.
e
s 00001/00001/00362
d D 4.9 81/06/11 16:40:08 wnj 9 8
c !cc
e
s 00026/00009/00337
d D 4.8 81/06/11 16:35:19 wnj 8 7
c fixes per kre
e
s 00001/00001/00345
d D 4.7 81/05/11 03:29:27 root 7 6
c new sccs line
e
s 00003/00008/00343
d D 4.6 81/05/10 16:08:06 root 6 5
c no -y flag; geteuid() must be root
e
s 00010/00001/00341
d D 4.5 81/05/04 11:15:05 toy 5 4
c Added -y flag.
e
s 00002/00000/00340
d D 4.4 81/04/21 02:16:14 root 4 3
c added error check in log_entry()
e
s 00023/00015/00317
d D 4.3 81/04/03 13:02:17 root 3 2
c write log entries
e
s 00048/00007/00284
d D 4.2 81/02/28 22:42:22 wnj 2 1
c changed but still crufty
e
s 00291/00000/00000
d D 4.1 81/02/07 22:23:07 wnj 1 0
c date and time created 81/02/07 22:23:07 by wnj
e
u
U
t
T
I 21
/*
D 26
 * Copyright (c) 1983 Regents of the University of California.
E 26
I 26
D 28
 * Copyright (c) 1983,1986 Regents of the University of California.
E 26
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 28
I 28
D 34
 * Copyright (c) 1988 Regents of the University of California.
E 34
I 34
D 38
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 34
 * All rights reserved.
E 38
I 38
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 38
 *
D 35
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
E 35
I 35
 * %sccs.include.redist.c%
E 35
E 28
 */

E 21
I 17
#ifndef lint
E 17
I 1
D 7
/*	%W% (Berkeley/Melbourne) %E%	*/
E 7
I 7
D 21
static	char *sccsid = "%W% (Berkeley) %E%";
I 17
#endif
E 21
I 21
D 38
char copyright[] =
D 26
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 26
I 26
D 28
"%Z% Copyright (c) 1983,1986 Regents of the University of California.\n\
E 28
I 28
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 28
E 26
 All rights reserved.\n";
E 38
I 38
static char copyright[] =
"%Z% Copyright (c) 1988, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 38
D 28
#endif not lint
E 28
I 28
#endif /* not lint */
E 28

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 28
#endif not lint
E 28
I 28
#endif /* not lint */
E 28
E 21
E 17
E 7

D 28
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
I 20
#include <setjmp.h>
E 20
#include <utmp.h>
I 26
#include <pwd.h>
E 28
I 28
#include <sys/param.h>
E 28
E 26
D 18
#include <time.h>
E 18
I 18
#include <sys/time.h>
I 28
D 39
#include <sys/file.h>
E 39
E 28
#include <sys/resource.h>
E 18
D 26
#include <sys/types.h>
E 26
I 26
D 28
#include <sys/param.h>
E 28
E 26
I 24
#include <sys/syslog.h>
I 28
D 36
#include <signal.h>
E 36
I 36
D 39
#include <sys/signal.h>
E 36
#include <setjmp.h>
#include <tzfile.h>
E 39
I 39

#include <ctype.h>
#include <fcntl.h>
E 39
#include <pwd.h>
I 39
#include <setjmp.h>
#include <signal.h>
E 39
#include <stdio.h>
D 39
#include <ctype.h>
E 39
I 39
#include <stdlib.h>
#include <string.h>
#include <tzfile.h>
#include <unistd.h>

E 39
I 31
#include "pathnames.h"
E 31
E 28

E 24
I 11
D 12
#include <whoami.h>
E 12
E 11
D 28
/*
 *	/etc/shutdown when [messages]
 *
 *	allow super users to tell users and remind users
 *	of iminent shutdown of unix
 *	and shut it down automatically
 *	and even reboot or halt the machine if they desire
D 15
 *
 *		Ian Johnstone, Sydney, 1977
 *		Robert Elz, Melbourne, 1978
 *		Peter Lamb, Melbourne, 1980
 *		William Joy, Berkeley, 1981
I 2
 *		Michael Toy, Berkeley, 1981
I 10
 *		Dave Presotto, Berkeley, 1981
E 15
E 10
E 2
 */
E 28
I 28
D 31
#define	REBOOT		"/etc/reboot"
#define	HALT		"/etc/halt"
E 28
I 2
D 24
#ifdef DEBUG
#define LOGFILE "shutdown.log"
#else
#define LOGFILE "/usr/adm/shutdownlog"
#endif
E 24
I 24

E 31
E 24
E 2
D 28
#define	REBOOT	"/etc/reboot"
#define	HALT	"/etc/halt"
#define MAXINTS 20
#define	HOURS	*3600
#define MINUTES	*60
#define SECONDS
D 8
#define NLOG		20		/* no of lines possible for message */
E 8
I 8
D 24
#define NLOG		20		/* no of args possible for message */
E 24
I 24
#define NLOG		600		/* no of bytes possible for message */
E 24
E 8
#define	NOLOGTIME	5 MINUTES
I 10
#define IGNOREUSER	"sleeper"
E 10

I 12
D 26
char	hostname[32];
E 26
I 26
char	hostname[MAXHOSTNAMELEN];
E 26

E 12
D 20
int	do_nothing();
E 20
I 20
int	timeout();
E 20
time_t	getsdt();
I 27
void	finish();
E 27

extern	char *ctime();
extern	struct tm *localtime();
I 23
extern	long time();
E 23

I 23
extern	char *strcpy();
extern	char *strncat();
extern	off_t lseek();

E 23
struct	utmp utmp;
int	sint;
int	stogo;
char	tpath[] =	"/dev/";
int	nlflag = 1;		/* nolog yet to be done */
int	killflg = 1;
D 23
int	reboot = 0;
E 23
I 23
int	doreboot = 0;
E 23
I 5
D 6
int	noroot = 0;
E 6
E 5
int	halt = 0;
I 22
int     fast = 0;
char    *nosync = NULL;
char    nosyncflag[] = "-n";
E 22
char	term[sizeof tpath + sizeof utmp.ut_line];
char	tbuf[BUFSIZ];
char	nolog1[] = "\n\nNO LOGINS: System going down at %5.5s\n\n";
D 24
char	*nolog2[NLOG+1];
E 24
I 24
char	nolog2[NLOG+1];
E 24
#ifdef	DEBUG
char	nologin[] = "nologin";
I 22
char    fastboot[] = "fastboot";
E 28
I 28
#ifdef DEBUG
D 31
#define	NOLOGIN		"./nologin"
#define	FASTBOOT	"./fastboot"
E 28
E 22
#else
D 28
char	nologin[] = "/etc/nologin";
I 22
char	fastboot[] = "/fastboot";
E 28
I 28
#define	NOLOGIN		"/etc/nologin"
#define	FASTBOOT	"/fastboot"
E 31
I 31
#undef _PATH_NOLOGIN
#define	_PATH_NOLOGIN	"./nologin"
#undef _PATH_FASTBOOT
#define	_PATH_FASTBOOT	"./fastboot"
E 31
E 28
E 22
#endif
D 14
int slots;
E 14
I 14
D 28
time_t	nowtime;
I 20
jmp_buf	alarmbuf;
E 28
E 20

I 28
#define	H		*60*60
#define	M		*60
#define	S		*1
#define	NOLOG_TIME	5*60
E 28
E 14
struct interval {
D 28
	int stogo;
	int sint;
} interval[] = {
	4 HOURS,	1 HOURS,
	2 HOURS,	30 MINUTES,
	1 HOURS,	15 MINUTES,
	30 MINUTES,	10 MINUTES,
	15 MINUTES,	5 MINUTES,
D 2
	10 MINUTES,	2 MINUTES,
E 2
I 2
	10 MINUTES,	5 MINUTES,
	5 MINUTES,	3 MINUTES,
E 2
D 14
	2 MINUTES,	30 SECONDS,
I 8
	40 SECONDS,	10 SECONDS,
E 14
I 14
	2 MINUTES,	1 MINUTES,
	1 MINUTES,	30 SECONDS,
E 14
E 8
	0 SECONDS,	0 SECONDS
};
E 28
I 28
	int timeleft, timetowait;
} tlist[] = {
	10 H,  5 H,	 5 H,  3 H,	 2 H,  1 H,	1 H, 30 M,
	30 M, 10 M,	20 M, 10 M,	10 M,  5 M,	5 M,  3 M,
	 2 M,  1 M,	 1 M, 30 S,	30 S, 30 S,
	 0, 0,
D 39
}, *tp = tlist;
E 39
I 39
};
E 39
#undef H
#undef M
#undef S
E 28
I 14

E 14
I 2
D 28
char *shutter, *getlogin();
E 28
I 28
static time_t offset, shuttime;
static int dofast, dohalt, doreboot, killflg, mbuflen;
static char *nosync, *whom, mbuf[BUFSIZ];
E 28
I 14

I 39
void badtime __P((void));
void die_you_gravy_sucking_pig_dog __P((void));
void doitfast __P((void));
void finish __P((int));
void getoffset __P((char *));
void loop __P((void));
void nolog __P((void));
void timeout __P((int));
void timewarn __P((int));
void usage __P((void));

int
E 39
E 14
E 2
D 28
main(argc,argv)
E 28
I 28
main(argc, argv)
E 28
	int argc;
D 39
	char **argv;
E 39
I 39
	char *argv[];
E 39
{
D 28
	register i, ufd;
D 24
	register char **mess, *f;
E 24
I 24
	register char *f;
E 24
	char *ts;
D 14
	long sdt;
E 14
I 14
	time_t sdt;
E 14
	int h, m;
D 14
	long nowtime;
E 14
I 14
	int first;
E 14
	FILE *termf;
E 28
I 28
	extern int optind;
D 29
	register char *p;
	int arglen, ch, len;
E 29
I 29
	register char *p, *endp;
D 39
	int arglen, ch, len, readstdin;
E 39
E 29
E 28
I 26
D 37
	struct passwd *pw, *getpwuid();
E 37
I 37
	struct passwd *pw;
E 37
E 26
I 25
D 28
	extern char *strcat();
	extern uid_t geteuid();
E 28
I 28
D 39
	char *strcat(), *getlogin();
	uid_t geteuid();
E 39
I 39
	int arglen, ch, len, readstdin;
E 39
E 28
E 25

I 2
D 28
	shutter = getlogin();
I 26
	if (shutter == 0 && (pw = getpwuid(getuid())))
		shutter = pw->pw_name;
E 26
I 24
	if (shutter == 0)
		shutter = "???";
E 24
I 12
D 23
	gethostname(hostname, sizeof (hostname));
E 23
I 23
	(void) gethostname(hostname, sizeof (hostname));
I 24
	openlog("shutdown", 0, LOG_AUTH);
E 24
E 23
E 12
E 2
	argc--, argv++;
	while (argc > 0 && (f = argv[0], *f++ == '-')) {
		while (i = *f++) switch (i) {
E 28
I 28
#ifndef DEBUG
	if (geteuid()) {
D 36
		fprintf(stderr, "shutdown: NOT super-user\n");
E 36
I 36
		(void)fprintf(stderr, "shutdown: NOT super-user\n");
E 36
		exit(1);
	}
#endif
D 29
	nosync = "";
	while ((ch = getopt(argc, argv, "fhknr")) != EOF)
E 29
I 29
	nosync = NULL;
	readstdin = 0;
	while ((ch = getopt(argc, argv, "-fhknr")) != EOF)
E 29
D 34
		switch((char)ch) {
E 34
I 34
		switch (ch) {
E 34
I 29
		case '-':
			readstdin = 1;
			break;
E 29
		case 'f':
			dofast = 1;
			break;
		case 'h':
			dohalt = 1;
			break;
E 28
		case 'k':
D 28
			killflg = 0;
			continue;
E 28
I 28
			killflg = 1;
			break;
E 28
I 22
		case 'n':
D 28
			nosync = nosyncflag;
			continue;
		case 'f':
			fast = 1;
			continue;
E 28
I 28
			nosync = "-n";
			break;
E 28
E 22
		case 'r':
D 23
			reboot = 1;
E 23
I 23
			doreboot = 1;
E 23
D 28
			continue;
		case 'h':
			halt = 1;
			continue;
E 28
I 28
			break;
		case '?':
E 28
I 5
D 6
		case 'y':
			noroot = 1;
			continue;
E 6
E 5
		default:
D 28
			fprintf(stderr, "shutdown: '%c' - unknown flag\n", i);
			exit(1);
E 28
I 28
			usage();
E 28
		}
D 28
		argc--, argv++;
E 28
I 28
	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

D 29
	if (dofast && *nosync) {
E 29
I 29
	if (dofast && nosync) {
E 29
D 36
		fprintf(stderr,
E 36
I 36
		(void)fprintf(stderr,
E 36
		    "shutdown: incompatible switches -f and -n.\n");
		usage();
E 28
	}
D 28
	if (argc < 1) {
D 5
		printf("Usage: %s [-krd] shutdowntime [nologmessage]\n",
E 5
I 5
D 6
		printf("Usage: %s [-krdy] shutdowntime [nologmessage]\n",
E 6
I 6
D 8
		printf("Usage: %s [ -krd ] shutdowntime [ message ]\n",
E 8
I 8
D 22
		printf("Usage: %s [ -krh ] shutdowntime [ message ]\n",
E 8
E 6
E 5
		    argv[0]);
E 22
I 22
	        /* argv[0] is not available after the argument handling. */
		printf("Usage: shutdown [ -krhfn ] shutdowntime [ message ]\n");
E 22
I 5
		finish();
E 28
I 28
	if (doreboot && dohalt) {
D 36
		fprintf(stderr, 
E 36
I 36
		(void)fprintf(stderr,
E 36
		    "shutdown: incompatible switches -h and -r.\n");
		usage();
E 28
	}
I 22
D 28
	if (fast && (nosync == nosyncflag)) {
	        printf ("shutdown: Incompatible switches 'fast' & 'nosync'\n");
		finish();
E 28
I 28
	getoffset(*argv++);
I 29

E 29
	if (*argv) {
D 29
		do {
			(void)strcat(mbuf, *argv);
			(void)strcat(mbuf, " ");
		} while(*++argv);
		(void)strcat(mbuf, "\n");
E 29
I 29
		for (p = mbuf, len = sizeof(mbuf); *argv; ++argv) {
			arglen = strlen(*argv);
			if ((len -= arglen) <= 2)
				break;
			if (p != mbuf)
				*p++ = ' ';
D 41
			bcopy(*argv, p, arglen);
E 41
I 41
			memmove(p, *argv, arglen);
E 41
			p += arglen;
		}
		*p = '\n';
		*++p = '\0';
E 29
E 28
	}
E 22
D 6
	if (noroot == 0 && geteuid() != 0)
	{
		printf("Must specify -y flag to run as normal user.\n");
E 6
I 6
D 28
	if (geteuid()) {
		fprintf(stderr, "NOT super-user\n");
E 6
E 5
		finish();
E 28
I 28
D 29
	else for (len = sizeof(mbuf), p = mbuf; fgets(p, len, stdin);) {
		arglen = strlen(p);
		if (!(len -= arglen))
			break;
		p += arglen;
E 29
I 29

	if (readstdin) {
		p = mbuf;
		endp = mbuf + sizeof(mbuf) - 2;
		for (;;) {
			if (!fgets(p, endp - p + 1, stdin))
				break;
			for (; *p &&  p < endp; ++p);
			if (p == endp) {
				*p = '\n';
				*++p = '\0';
				break;
			}
		}
E 29
E 28
	}
I 14
D 23
	nowtime = time((time_t *)0);
E 23
I 23
D 28
	nowtime = time((long *)0);
E 23
E 14
	sdt = getsdt(argv[0]);
	argc--, argv++;
D 24
	i = 0;
	while (argc-- > 0)
		if (i < NLOG)
			nolog2[i++] = *argv++;
	nolog2[i] = NULL;
E 24
I 24
	nolog2[0] = '\0';
	while (argc-- > 0) {
D 25
		strcat(nolog2, " ");
		strcat(nolog2, *argv++);
E 25
I 25
		(void) strcat(nolog2, " ");
		(void) strcat(nolog2, *argv++);
E 28
I 28
	mbuflen = strlen(mbuf);

	if (offset)
D 32
		printf("Shutdown at %.24s.", ctime(&shuttime));
E 32
I 32
D 36
		printf("Shutdown at %.24s.\n", ctime(&shuttime));
E 36
I 36
		(void)printf("Shutdown at %.24s.\n", ctime(&shuttime));
E 36
E 32
	else
D 36
		printf("Shutdown NOW!\n");
E 36
I 36
		(void)printf("Shutdown NOW!\n");
E 36

	if (!(whom = getlogin()))
		whom = (pw = getpwuid(getuid())) ? pw->pw_name : "???";

#ifdef DEBUG
	(void)putc('\n', stdout);
#else
	(void)setpriority(PRIO_PROCESS, 0, PRIO_MIN);
	{
		int forkpid;

		forkpid = fork();
		if (forkpid == -1) {
			perror("shutdown: fork");
			exit(1);
		}
		if (forkpid) {
D 36
			printf("shutdown: [pid %d]\n", forkpid);
E 36
I 36
			(void)printf("shutdown: [pid %d]\n", forkpid);
E 36
			exit(0);
		}
E 28
E 25
	}
E 24
D 14
	nowtime = time((long *)0);
E 14
D 28
	m = ((stogo = sdt - nowtime) + 30)/60;
	h = m/60; 
	m %= 60;
	ts = ctime(&sdt);
D 2
	printf("Shutdown at %5.5s\n", ts+11);
	printf("ie. in ");
E 2
I 2
	printf("Shutdown at %5.5s (in ", ts+11);
E 2
	if (h > 0)
		printf("%d hour%s ", h, h != 1 ? "s" : "");
D 2
	printf("%d minute%s\n", m, m != 1 ? "s" : "");
E 2
I 2
	printf("%d minute%s) ", m, m != 1 ? "s" : "");
E 2
#ifndef DEBUG
D 23
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
E 23
I 23
	(void) signal(SIGHUP, SIG_IGN);
	(void) signal(SIGQUIT, SIG_IGN);
	(void) signal(SIGINT, SIG_IGN);
E 28
E 23
#endif
I 16
D 23
	signal(SIGTTOU, SIG_IGN);
E 16
	signal(SIGTERM, finish);
D 20
	signal(SIGALRM, do_nothing);
E 20
I 20
	signal(SIGALRM, timeout);
E 20
D 18
	nice(-20);
E 18
I 18
	setpriority(PRIO_PROCESS, 0, PRIO_MIN);
E 18
I 8
	fflush(stdout);
E 23
I 23
D 28
	(void) signal(SIGTTOU, SIG_IGN);
	(void) signal(SIGTERM, finish);
	(void) signal(SIGALRM, timeout);
	(void) setpriority(PRIO_PROCESS, 0, PRIO_MIN);
	(void) fflush(stdout);
E 23
E 8
I 2
#ifndef DEBUG
E 2
	if (i = fork()) {
D 2
		printf("%d\n", i);
E 2
I 2
		printf("[pid %d]\n", i);
E 2
		exit(0);
E 28
I 28
	openlog("shutdown", LOG_CONS, LOG_AUTH);
	loop();
D 39
	/*NOTREACHED*/
E 39
I 39
	/* NOTREACHED */
E 39
}

I 39
void
E 39
D 31
#define	WALL_CMD	"/bin/wall"

E 31
loop()
{
I 39
	struct interval *tp;
E 39
	u_int sltime;
	int logged;

	if (offset <= NOLOG_TIME) {
		logged = 1;
		nolog();
E 28
	}
I 14
D 28
#else
D 23
	putc('\n', stdout);
E 23
I 23
	(void) putc('\n', stdout);
E 23
E 14
I 2
#endif
E 2
	sint = 1 HOURS;
	f = "";
I 14
	ufd = open("/etc/utmp",0);
	if (ufd < 0) {
		perror("shutdown: /etc/utmp");
		exit(1);
E 28
I 28
	else
		logged = 0;
	tp = tlist;
	if (tp->timeleft < offset)
		(void)sleep((u_int)(offset - tp->timeleft));
	else {
		while (offset < tp->timeleft)
			++tp;
		/*
D 39
		 * warn now, if going to sleep more than a fifth of
E 39
I 39
		 * Warn now, if going to sleep more than a fifth of
E 39
		 * the next wait time.
		 */
		if (sltime = offset - tp->timeleft) {
			if (sltime > tp->timetowait / 5)
D 39
				warn();
E 39
I 39
				timewarn(offset);
E 39
			(void)sleep(sltime);
		}
E 28
	}
D 28
	first = 1;
E 14
	for (;;) {
		for (i = 0; stogo <= interval[i].stogo && interval[i].sint; i++)
			sint = interval[i].sint;
I 14
		if (stogo > 0 && (stogo-sint) < interval[i].stogo)
			sint = stogo - interval[i].stogo;
E 14
		if (stogo <= NOLOGTIME && nlflag) {
			nlflag = 0;
			nolog(sdt);
E 28
I 28
	for (;; ++tp) {
D 39
		warn();
E 39
I 39
		timewarn(tp->timeleft);
E 39
		if (!logged && tp->timeleft <= NOLOG_TIME) {
			logged = 1;
			nolog();
E 28
		}
D 28
		if (sint >= stogo || sint == 0)
			f = "FINAL ";
D 14
		ufd = open("/etc/utmp",0);
		nowtime = time((long *) 0);
E 14
I 14
D 23
		nowtime = time((time_t *) 0);
		lseek(ufd, 0L, 0);
E 14
		while (read(ufd,&utmp,sizeof utmp)==sizeof utmp)
E 23
I 23
		nowtime = time((long *)0);
		(void) lseek(ufd, 0L, 0);
		while (read(ufd,(char *)&utmp,sizeof utmp)==sizeof utmp)
E 23
D 10
		if (utmp.ut_name[0]) {
E 10
I 10
		if (utmp.ut_name[0] &&
		    strncmp(utmp.ut_name, IGNOREUSER, sizeof(utmp.ut_name))) {
I 20
			if (setjmp(alarmbuf))
				continue;
E 20
E 10
D 23
			strcpy(term, tpath);
			strncat(term, utmp.ut_line, sizeof utmp.ut_line);
			alarm(3);
E 23
I 23
			(void) strcpy(term, tpath);
			(void) strncat(term, utmp.ut_line, sizeof utmp.ut_line);
			(void) alarm(3);
E 23
#ifdef DEBUG
D 2
			if ((termf = fopen("/dev/tty", "w")) != NULL)
E 2
I 2
			if ((termf = stdout) != NULL)
E 2
#else
			if ((termf = fopen(term, "w")) != NULL)
#endif
			{
D 23
				alarm(0);
E 23
I 23
				(void) alarm(0);
E 23
				setbuf(termf, tbuf);
D 14
				fprintf(termf, "\n\n");
				warn(termf, sdt, nowtime);
				if (sdt - nowtime > 1 MINUTES)
E 14
I 14
				fprintf(termf, "\n\r\n");
				warn(termf, sdt, nowtime, f);
				if (first || sdt - nowtime > 1 MINUTES) {
					if (*nolog2)
D 24
						fprintf(termf, "\t...");
E 14
					for (mess = nolog2; *mess; mess++)
D 14
						fprintf(termf, "%s ", *mess);
E 14
I 14
						fprintf(termf, " %s", *mess);
E 24
I 24
						fprintf(termf, "\t...%s", nolog2);
E 24
				}
D 23
				fputc('\r', termf);
E 14
				fputc('\n', termf);
I 2
				alarm(5);
E 23
I 23
				(void) fputc('\r', termf);
				(void) fputc('\n', termf);
				(void) alarm(5);
E 23
#ifdef DEBUG
D 23
				fflush(termf);
E 23
I 23
				(void) fflush(termf);
E 23
#else
E 2
D 23
				fclose(termf);
E 23
I 23
				(void) fclose(termf);
E 23
I 2
#endif
E 2
D 23
				alarm(0);
E 23
I 23
				(void) alarm(0);
E 23
			}
		}
D 14
		if (stogo < 0) {
E 14
I 14
		if (stogo <= 0) {
E 14
D 24
	printf("\n\007\007System shutdown time has arrived\007\007\n");
I 2
			log_entry(sdt);
E 24
I 24
			printf("\n\007\007System shutdown time has arrived\007\007\n");
D 26
			syslog(LOG_CRIT, "%s!%s: %s", hostname, shutter, nolog2);
E 26
I 26
			syslog(LOG_CRIT, "%s by %s: %s",
			    doreboot ? "reboot" : halt ? "halt" : "shutdown",
			    shutter, nolog2);
			sleep(2);
E 26
E 24
E 2
D 23
			unlink(nologin);
E 23
I 23
			(void) unlink(nologin);
E 23
			if (!killflg) {
				printf("but you'll have to do it yourself\n");
				finish();
			}
I 22
			if (fast)
				doitfast();
E 22
#ifndef DEBUG
I 14
D 23
			kill(-1, SIGTERM);	/* terminate everyone */
E 23
I 23
D 26
			(void) kill(-1, SIGTERM);	/* terminate everyone */
E 23
			sleep(5);		/* & wait while they die */
E 26
E 14
D 23
			if (reboot)
E 23
I 23
			if (doreboot)
E 23
D 22
				execle(REBOOT, "reboot", 0, 0);
E 22
I 22
D 26
				execle(REBOOT, "reboot", nosync, 0, 0);
E 26
I 26
				execle(REBOOT, "reboot", "-l", nosync, 0, 0);
E 26
E 22
			if (halt)
D 22
				execle(HALT, "halt", 0, 0);
E 22
I 22
D 26
				execle(HALT, "halt", nosync, 0, 0);
E 22
D 23
			kill(1, SIGTERM);	/* sync */
			kill(1, SIGTERM);	/* sync */
E 23
I 23
			(void) kill(1, SIGTERM);	/* sync */
			(void) kill(1, SIGTERM);	/* sync */
E 23
			sleep(20);
E 26
I 26
				execle(HALT, "halt", "-l", nosync, 0, 0);
			(void) kill(1, SIGTERM);	/* to single user */
E 26
#else
D 26
			printf("EXTERMINATE EXTERMINATE\n");
E 26
I 22
D 23
			if (reboot)
E 23
I 23
			if (doreboot)
E 23
				printf("REBOOT");
			if (halt)
				printf(" HALT");
			if (fast)
D 26
				printf(" %s (without fsck's)\n", nosync);
E 26
I 26
				printf(" -l %s (without fsck's)\n", nosync);
E 26
			else
D 26
				printf(" %s\n", nosync);
E 26
I 26
				printf(" -l %s\n", nosync);
			else
				printf("kill -HUP 1\n");
E 26

E 22
#endif
			finish();
		}
D 14
		stogo = sdt - time((long *) 0);
		if (stogo > 0)
E 14
I 14
D 23
		stogo = sdt - time((time_t *) 0);
E 23
I 23
		stogo = sdt - time((long *) 0);
E 23
		if (stogo > 0 && sint > 0)
E 14
D 23
			sleep(sint<stogo ? sint : stogo);
E 23
I 23
			sleep((unsigned)(sint<stogo ? sint : stogo));
E 23
		stogo -= sint;
I 14
		first = 0;
E 28
I 28
		(void)sleep((u_int)tp->timetowait);
		if (!tp->timeleft)
			break;
E 28
E 14
	}
I 28
	die_you_gravy_sucking_pig_dog();
E 28
}

D 28
time_t
getsdt(s)
D 14
register char *s;
E 14
I 14
	register char *s;
E 28
I 28
static jmp_buf alarmbuf;

D 39
warn()
E 39
I 39
void
timewarn(timeleft)
	int timeleft;
E 39
E 28
E 14
{
D 28
	time_t t, t1, tim;
	register char c;
	struct tm *lt;
E 28
I 28
	static int first;
I 34
	static char hostname[MAXHOSTNAMELEN + 1];
D 39
	char wcmd[MAXPATHLEN + 4];
E 39
E 34
D 33
	static char hostname[MAXHOSTNAMELEN];
E 33
	FILE *pf;
D 39
	char *ctime();
D 36
	int timeout();
E 36
I 36
	void timeout();
E 39
I 39
	char wcmd[MAXPATHLEN + 4];
E 39
E 36
E 28

I 14
D 28
	if (strcmp(s, "now") == 0)
		return(nowtime);
E 14
	if (*s == '+') {
		++s; 
		t = 0;
		for (;;) {
			c = *s++;
			if (!isdigit(c))
				break;
			t = t * 10 + c - '0';
		}
		if (t <= 0)
			t = 5;
		t *= 60;
D 14
		tim = time((long *) 0) + t;
E 14
I 14
D 23
		tim = time((time_t *) 0) + t;
E 23
I 23
		tim = time((long *) 0) + t;
E 23
E 14
		return(tim);
E 28
I 28
D 33
	if (!first++) {
E 33
I 33
	if (!first++)
E 33
D 34
		(void)signal(SIGALRM, timeout);
E 34
I 34
		(void)gethostname(hostname, sizeof(hostname));
E 34
D 33
		(void)gethostname(hostname, sizeof(hostname));
E 28
	}
E 33
D 28
	t = 0;
	while (strlen(s) > 2 && isdigit(*s))
		t = t * 10 + *s++ - '0';
	if (*s == ':')
		s++;
	if (t > 23)
		goto badform;
	tim = t*60;
	t = 0;
	while (isdigit(*s))
		t = t * 10 + *s++ - '0';
	if (t > 59)
		goto badform;
	tim += t; 
	tim *= 60;
D 14
	t1 = time((long *) 0);
E 14
I 14
D 23
	t1 = time((time_t *) 0);
E 23
I 23
	t1 = time((long *) 0);
E 23
E 14
	lt = localtime(&t1);
	t = lt->tm_sec + lt->tm_min*60 + lt->tm_hour*3600;
	if (tim < t || tim >= (24*3600)) {
		/* before now or after midnight */
		printf("That must be tomorrow\nCan't you wait till then?\n");
E 28
I 28

D 31
	if (!(pf = popen(WALL_CMD, "w"))) {
		syslog(LOG_ERR, "shutdown: can't find %s: %m", WALL_CMD);
E 31
I 31
D 34
	if (!(pf = popen(_PATH_WALL, "w"))) {
E 34
I 34
	/* undoc -n option to wall suppresses normal wall banner */
D 36
	(void) sprintf(wcmd, "%s -n", _PATH_WALL);
E 36
I 36
D 39
	(void)sprintf(wcmd, "%s -n", _PATH_WALL);
E 39
I 39
	(void)snprintf(wcmd, sizeof(wcmd), "%s -n", _PATH_WALL);
E 39
E 36
	if (!(pf = popen(wcmd, "w"))) {
E 34
		syslog(LOG_ERR, "shutdown: can't find %s: %m", _PATH_WALL);
E 31
		return;
	}

D 34
	fprintf(pf, "*** %sSystem shutdown message ***\n",
	    tp->timeleft ? "": "FINAL ");
E 34
I 34
D 36
	fprintf(pf, "\007*** %sSystem shutdown message from %s@%s ***\007\n",
E 36
I 36
	(void)fprintf(pf,
	    "\007*** %sSystem shutdown message from %s@%s ***\007\n",
E 36
D 39
	    tp->timeleft ? "": "FINAL ", whom, hostname);
E 39
I 39
	    timeleft ? "": "FINAL ", whom, hostname);
E 39
E 34

D 39
	if (tp->timeleft > 10*60)
E 39
I 39
	if (timeleft > 10*60)
E 39
D 36
		fprintf(pf, "System going down at %5.5s\n\n",
E 36
I 36
		(void)fprintf(pf, "System going down at %5.5s\n\n",
E 36
		    ctime(&shuttime) + 11);
D 39
	else if (tp->timeleft > 59)
E 39
I 39
	else if (timeleft > 59)
E 39
D 36
		fprintf(pf, "System going down in %d minute%s\n\n",
E 36
I 36
		(void)fprintf(pf, "System going down in %d minute%s\n\n",
E 36
D 39
		    tp->timeleft / 60, (tp->timeleft > 60) ? "s" : "");
	else if (tp->timeleft)
E 39
I 39
		    timeleft / 60, (timeleft > 60) ? "s" : "");
	else if (timeleft)
E 39
D 36
		fprintf(pf, "System going down in 30 seconds\n\n");
E 36
I 36
		(void)fprintf(pf, "System going down in 30 seconds\n\n");
E 36
	else
D 36
		fprintf(pf, "System going down IMMEDIATELY\n\n");
E 36
I 36
		(void)fprintf(pf, "System going down IMMEDIATELY\n\n");
E 36

D 29
	(void)fwrite(mbuf, sizeof(*mbuf), mbuflen, pf);
E 29
I 29
	if (mbuflen)
		(void)fwrite(mbuf, sizeof(*mbuf), mbuflen, pf);
E 29

	/*
	 * play some games, just in case wall doesn't come back
	 * probably unecessary, given that wall is careful.
	 */
	if (!setjmp(alarmbuf)) {
I 34
		(void)signal(SIGALRM, timeout);
E 34
		(void)alarm((u_int)30);
		(void)pclose(pf);
		(void)alarm((u_int)0);
I 34
		(void)signal(SIGALRM, SIG_DFL);
E 34
	}
}

I 36
void
E 36
D 39
timeout()
E 39
I 39
timeout(signo)
	int signo;
E 39
{
	longjmp(alarmbuf, 1);
}

I 39
void
E 39
die_you_gravy_sucking_pig_dog()
{
I 36
D 39
	void finish();
E 39

E 36
	syslog(LOG_NOTICE, "%s by %s: %s",
	    doreboot ? "reboot" : dohalt ? "halt" : "shutdown", whom, mbuf);
	(void)sleep(2);

D 36
	printf("\r\nSystem shutdown time has arrived\007\007\r\n");
E 36
I 36
	(void)printf("\r\nSystem shutdown time has arrived\007\007\r\n");
E 36
	if (killflg) {
D 36
		printf("\rbut you'll have to do it yourself\r\n");
E 36
I 36
		(void)printf("\rbut you'll have to do it yourself\r\n");
E 36
E 28
D 39
		finish();
E 39
I 39
		finish(0);
E 39
	}
D 14
	return (t1 + tim -t);
E 14
I 14
D 28
	return (t1 + tim - t);
E 14
badform:
	printf("Bad time format\n");
E 28
I 28
	if (dofast)
		doitfast();
#ifdef DEBUG
	if (doreboot)
D 29
		printf("REBOOT");
	if (dohalt)
		printf(" HALT");
E 29
I 29
D 36
		printf("reboot");
E 36
I 36
		(void)printf("reboot");
E 36
	else if (dohalt)
D 36
		printf("halt");
E 36
I 36
		(void)printf("halt");
E 36
	if (nosync)
D 36
		printf(" no sync");
E 36
I 36
		(void)printf(" no sync");
E 36
E 29
	if (dofast)
D 29
		printf(" -l %s (without fsck's)\n", nosync);
	else
		printf(" -l %s\n", nosync);
	printf("kill -HUP 1\n");
E 29
I 29
D 36
		printf(" no fsck");
	printf("\nkill -HUP 1\n");
E 36
I 36
		(void)printf(" no fsck");
	(void)printf("\nkill -HUP 1\n");
E 36
E 29
#else
	if (doreboot) {
D 29
		execle(REBOOT, "reboot", "-l", nosync, 0, 0);
E 29
I 29
D 31
		execle(REBOOT, "reboot", "-l", nosync, 0);
E 29
		syslog(LOG_ERR, "shutdown: can't exec %s: %m.", REBOOT);
E 31
I 31
		execle(_PATH_REBOOT, "reboot", "-l", nosync, 0);
		syslog(LOG_ERR, "shutdown: can't exec %s: %m.", _PATH_REBOOT);
E 31
		perror("shutdown");
	}
	else if (dohalt) {
D 29
		execle(HALT, "halt", "-l", nosync, 0, 0);
E 29
I 29
D 31
		execle(HALT, "halt", "-l", nosync, 0);
E 29
		syslog(LOG_ERR, "shutdown: can't exec %s: %m.", HALT);
E 31
I 31
		execle(_PATH_HALT, "halt", "-l", nosync, 0);
		syslog(LOG_ERR, "shutdown: can't exec %s: %m.", _PATH_HALT);
E 31
		perror("shutdown");
	}
	(void)kill(1, SIGTERM);		/* to single user */
#endif
E 28
D 39
	finish();
E 39
I 39
	finish(0);
E 39
I 23
D 28
	/*NOTREACHED*/
E 28
E 23
}

D 14
warn(term, sdt, nowtime)
E 14
I 14
D 28
warn(term, sdt, now, type)
E 14
	FILE *term;
D 14
	long sdt, nowtime;
E 14
I 14
	time_t sdt, now;
	char *type;
E 28
I 28
#define	ATOI2(p)	(p[0] - '0') * 10 + (p[1] - '0'); p += 2;
D 36
static int dmsize[] =
	{ -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
E 36

I 39
void
E 39
getoffset(timearg)
	register char *timearg;
E 28
E 14
{
D 28
	char *ts;
I 8
D 9
	register delay = std - nowtime;
E 9
I 9
D 14
	register delay = sdt - nowtime;
E 14
I 14
	register delay = sdt - now;
E 28
I 28
	register struct tm *lt;
	register char *p;
D 39
	time_t now, time();
E 39
I 39
	time_t now;
E 39
D 36
	int year, month, day, hour, min;
E 36
E 28
E 14
E 9
E 8

I 2
D 8
	fprintf(term, "\007\007*** System shutdown message from %s ***\n", shutter);
E 8
I 8
D 28
	if (delay > 8)
		while (delay % 5)
			delay++;
E 28
I 28
	if (!strcasecmp(timearg, "now")) {		/* now */
		offset = 0;
		return;
	}
E 28

D 24
	if (shutter)
		fprintf(term,
E 24
I 24
D 28
	fprintf(term,
E 24
D 11
		    "\007\007*** System shutdown message from %s ***\n",
		    shutter);
E 11
I 11
D 14
		    "\007\007*** System shutdown message from %s!%s ***\n",
D 13
		    sysname,shutter);
E 13
I 13
		    hostname,shutter);
E 14
I 14
D 19
	    "\007\007\t*** %sSystem shutdown message from %s!%s ***\r\n\n",
		    type, hostname, shutter);
E 19
I 19
	    "\007\007\t*** %sSystem shutdown message from %s@%s ***\r\n\n",
		    type, shutter, hostname);
E 28
I 28
	(void)time(&now);
	if (*timearg == '+') {				/* +minutes */
		if (!isdigit(*++timearg))
D 36
			goto badtime;
		min = atoi(timearg);
		offset = min * 60;
E 36
I 36
			badtime();
		offset = atoi(timearg) * 60;
E 36
		shuttime = now + offset;
		return;
	}
E 28
E 19
E 14
E 13
E 11
D 24
	else
		fprintf(term,
D 14
		    "\007\007*** System shutdown message ***\n");
E 14
I 14
		    "\007\007\t*** %sSystem shutdown message (%s) ***\r\n\n",
		    type, hostname);
E 24

E 14
E 8
E 2
D 28
	ts = ctime(&sdt);
D 8
	if (sdt - nowtime > 10 MINUTES)
E 8
I 8
D 14
	if (delay> 10 MINUTES)
E 8
		fprintf(term, "System going down at %5.5s\n", ts+11);
D 8
	else if ( sdt - nowtime > 60 SECONDS ) {
E 8
I 8
	else if ( delay > 60 SECONDS ) {
E 8
		fprintf(term, "System going down in %d minute%s\n",
D 8
		(sdt-nowtime+30)/60, (sdt-nowtime+30)/60 != 1 ? "s" : "");
	} else if ( sdt - nowtime > 0 ) {
E 8
I 8
		(delay+30)/60, (delay+30)/60 != 1 ? "s" : "");
	} else if ( delay > 0 ) {
E 8
D 2
		fprintf(term, "System going down in %d seconds\n",
E 2
I 2
		fprintf(term, "System going down in %d second%s\n",
E 2
D 8
		sdt-nowtime, sdt-nowtime != 1 ? "s" : "");
E 8
I 8
		delay, delay != 1 ? "s" : "");
E 14
I 14
	if (delay > 10 MINUTES)
		fprintf(term, "System going down at %5.5s\r\n", ts+11);
	else if (delay > 95 SECONDS) {
		fprintf(term, "System going down in %d minute%s\r\n",
		    (delay+30)/60, (delay+30)/60 != 1 ? "s" : "");
	} else if (delay > 0) {
		fprintf(term, "System going down in %d second%s\r\n",
		    delay, delay != 1 ? "s" : "");
E 14
E 8
	} else
D 14
		fprintf(term, "System going down IMMEDIATELY\n");
E 14
I 14
		fprintf(term, "System going down IMMEDIATELY\r\n");
E 28
I 28
	/* handle hh:mm by getting rid of the colon */
	for (p = timearg; *p; ++p)
		if (!isascii(*p) || !isdigit(*p))
			if (*p == ':' && strlen(p) == 3) {
				p[0] = p[1];
				p[1] = p[2];
				p[2] = '\0';
			}
			else
D 36
				goto badtime;
E 36
I 36
				badtime();
E 36

	unsetenv("TZ");					/* OUR timezone */
D 36
	lt = localtime(&now);				/* [yymmdd]hhmm */
	year = lt->tm_year;
	month = lt->tm_mon + 1;
	day = lt->tm_mday;
E 36
I 36
	lt = localtime(&now);				/* current time val */
E 36

	switch(strlen(timearg)) {
	case 10:
D 36
		year = ATOI2(timearg);
E 36
I 36
		lt->tm_year = ATOI2(timearg);
E 36
		/* FALLTHROUGH */
	case 8:
D 36
		month = ATOI2(timearg);
E 36
I 36
		lt->tm_mon = ATOI2(timearg);
		if (--lt->tm_mon < 0 || lt->tm_mon > 11)
			badtime();
E 36
		/* FALLTHROUGH */
	case 6:
D 36
		day = ATOI2(timearg);
E 36
I 36
		lt->tm_mday = ATOI2(timearg);
		if (lt->tm_mday < 1 || lt->tm_mday > 31)
			badtime();
E 36
		/* FALLTHROUGH */
	case 4:
D 36
		hour = ATOI2(timearg);
		min = ATOI2(timearg);
		if (month < 1 || month > 12 || day < 1 || day > 31 ||
		    hour < 0 || hour > 23 || min < 0 || min > 59)
			goto badtime;
		shuttime = 0;
		year += TM_YEAR_BASE;
		if (isleap(year) && month > 2)
			++shuttime;
		for (--year; year >= EPOCH_YEAR; --year)
			shuttime += isleap(year) ?
D 31
			    DAYS_PER_LYEAR : DAYS_PER_NYEAR;
E 31
I 31
			    DAYSPERLYEAR : DAYSPERNYEAR;
E 31
		while (--month)
			shuttime += dmsize[month];
		shuttime += day - 1;
D 31
		shuttime = HOURS_PER_DAY * shuttime + hour;
		shuttime = MINS_PER_HOUR * shuttime + min;
		shuttime *= SECS_PER_MIN;
E 31
I 31
		shuttime = HOURSPERDAY * shuttime + hour;
		shuttime = MINSPERHOUR * shuttime + min;
		shuttime *= SECSPERMIN;
E 31
		shuttime -= lt->tm_gmtoff;
		if ((offset = shuttime - now) >= 0)
			break;
		/* FALLTHROUGH */
E 36
I 36
		lt->tm_hour = ATOI2(timearg);
		if (lt->tm_hour < 0 || lt->tm_hour > 23)
			badtime();
		lt->tm_min = ATOI2(timearg);
		if (lt->tm_min < 0 || lt->tm_min > 59)
			badtime();
		lt->tm_sec = 0;
		if ((shuttime = mktime(lt)) == -1)
			badtime();
		if ((offset = shuttime - now) < 0) {
			(void)fprintf(stderr,
			    "shutdown: that time is already past.\n");
			exit(1);
		}
		break;
E 36
	default:
D 36
badtime:	fprintf(stderr,
		    "shutdown: bad time format, or already past.\n");
		exit(1);
E 36
I 36
		badtime();
E 36
	}
E 28
I 22
}

I 28
#define	FSMSG	"fastboot file for fsck\n"
I 39
void
E 39
E 28
doitfast()
{
D 28
	FILE *fastd;
E 28
I 28
	int fastfd;
E 28

D 28
	if ((fastd = fopen(fastboot, "w")) != NULL) {
		putc('\n', fastd);
D 23
		fclose(fastd);
E 23
I 23
		(void) fclose(fastd);
E 28
I 28
D 31
	if ((fastfd = open(FASTBOOT, O_WRONLY|O_CREAT|O_TRUNC, 0664)) >= 0) {
E 31
I 31
	if ((fastfd = open(_PATH_FASTBOOT, O_WRONLY|O_CREAT|O_TRUNC,
	    0664)) >= 0) {
E 31
		(void)write(fastfd, FSMSG, sizeof(FSMSG) - 1);
		(void)close(fastfd);
E 28
E 23
	}
E 22
E 14
}

D 28
nolog(sdt)
D 14
	long sdt;
E 14
I 14
	time_t sdt;
E 28
I 28
#define	NOMSG	"\n\nNO LOGINS: System going down at "
I 39
void
E 39
nolog()
E 28
E 14
{
D 28
	FILE *nologf;
E 28
I 28
D 36
	int logfd, finish();
E 36
I 36
	int logfd;
E 36
D 39
	char *ct, *ctime();
I 36
	void finish();
E 39
I 39
	char *ct;
E 39
E 36
E 28
D 24
	register char **mess;
E 24

I 14
D 23
	unlink(nologin);			/* in case linked to std file */
E 23
I 23
D 28
	(void) unlink(nologin);			/* in case linked to std file */
E 23
E 14
	if ((nologf = fopen(nologin, "w")) != NULL) {
		fprintf(nologf, nolog1, (ctime(&sdt)) + 11);
I 8
D 23
		putc('\t', nologf);
E 23
I 23
D 24
		(void) putc('\t', nologf);
E 23
E 8
		for (mess = nolog2; *mess; mess++)
D 8
			fprintf(nologf, "\t%s\n", *mess);
E 8
I 8
			fprintf(nologf, " %s", *mess);
D 23
		putc('\n', nologf);
E 8
		fclose(nologf);
E 23
I 23
		(void) putc('\n', nologf);
E 24
I 24
		if (*nolog2)
			fprintf(nologf, "\t%s\n", nolog2 + 1);
E 24
		(void) fclose(nologf);
E 28
I 28
D 31
	(void)unlink(NOLOGIN);		/* in case linked to another file */
E 31
I 31
	(void)unlink(_PATH_NOLOGIN);	/* in case linked to another file */
E 31
	(void)signal(SIGINT, finish);
	(void)signal(SIGHUP, finish);
	(void)signal(SIGQUIT, finish);
	(void)signal(SIGTERM, finish);
D 31
	if ((logfd = open(NOLOGIN, O_WRONLY|O_CREAT|O_TRUNC, 0664)) >= 0) {
E 31
I 31
	if ((logfd = open(_PATH_NOLOGIN, O_WRONLY|O_CREAT|O_TRUNC,
	    0664)) >= 0) {
E 31
		(void)write(logfd, NOMSG, sizeof(NOMSG) - 1);
		ct = ctime(&shuttime);
		(void)write(logfd, ct + 11, 5);
		(void)write(logfd, "\n\n", 2);
		(void)write(logfd, mbuf, strlen(mbuf));
		(void)close(logfd);
E 28
E 23
	}
}

I 36
void
E 36
I 27
D 28
void
E 28
E 27
D 39
finish()
E 39
I 39
finish(signo)
	int signo;
E 39
{
D 23
	signal(SIGTERM, SIG_IGN);
	unlink(nologin);
E 23
I 23
D 28
	(void) signal(SIGTERM, SIG_IGN);
	(void) unlink(nologin);
E 28
I 28
D 31
	(void)unlink(NOLOGIN);
E 31
I 31
D 40
	(void)unlink(_PATH_NOLOGIN);
E 40
I 40
	if (!killflg)
		(void)unlink(_PATH_NOLOGIN);
E 40
E 31
E 28
E 23
	exit(0);
I 36
}

I 39
void
E 39
badtime()
{
	(void)fprintf(stderr, "shutdown: bad time format.\n");
	exit(1);
E 36
}

I 39
void
E 39
D 20
do_nothing()
E 20
I 20
D 28
timeout()
E 28
I 28
usage()
E 28
E 20
{
D 20

	signal(SIGALRM, do_nothing);
E 20
I 20
D 28
	longjmp(alarmbuf, 1);
E 28
I 28
	fprintf(stderr, "usage: shutdown [-fhknr] shutdowntime [ message ]\n");
	exit(1);
E 28
E 20
I 2
D 24
}

/*
 * make an entry in the shutdown log
 */

D 3
log_entry(sdt)
time_t sdt;
E 3
I 3
char *days[] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

char *months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
	"Oct", "Nov", "Dec"
};

log_entry(now)
D 14
time_t now;
E 14
I 14
	time_t now;
E 14
E 3
{
D 3
	FILE *logf;
	char **mess;
E 3
I 3
	register FILE *fp;
	register char **mess;
	struct tm *tm, *localtime();
E 3

D 3
	if ((logf = fopen(LOGFILE, "a")) == NULL)
	{
		fprintf(stderr, "*** Can't write on log file ***\n");
		return;
	}
	fseek(logf, 0L, 2);
	fprintf(logf, "Shutdown by %s at %s",
			shutter, ctime(&sdt));
E 3
I 3
	tm = localtime(&now);
	fp = fopen(LOGFILE, "a");
I 4
D 14
	if (fp==0)
E 14
I 14
	if (fp == NULL) {
		printf("Shutdown: log entry failed\n");
E 14
		return;
I 14
	}
E 14
E 4
D 23
	fseek(fp, 0L, 2);
E 23
I 23
	(void) fseek(fp, 0L, 2);
E 23
	fprintf(fp, "%02d:%02d  %s %s %2d, %4d.  Shutdown:", tm->tm_hour,
		tm->tm_min, days[tm->tm_wday], months[tm->tm_mon],
		tm->tm_mday, tm->tm_year + 1900);
E 3
	for (mess = nolog2; *mess; mess++)
D 3
		fprintf(logf, "\t%s\n", *mess);
	fputc('\n', logf);
	fclose(logf);
E 3
I 3
		fprintf(fp, " %s", *mess);
I 8
	if (shutter)
D 11
		fprintf(fp, " (by %s)", shutter);
E 11
I 11
D 13
		fprintf(fp, " (by %s!%s)", sysname,shutter);
E 13
I 13
D 14
		fprintf(fp, " (by %s!%s)", hostname,shutter);
E 14
I 14
		fprintf(fp, " (by %s!%s)", hostname, shutter);
E 14
E 13
E 11
E 8
D 23
	fputc('\n', fp);
	fclose(fp);
E 23
I 23
	(void) fputc('\n', fp);
	(void) fclose(fp);
E 24
E 23
E 3
E 2
}
E 1
