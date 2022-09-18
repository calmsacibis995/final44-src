h27217
s 00005/00005/00173
d D 8.1 93/06/05 11:11:07 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00043/00021/00135
d D 5.13 91/10/30 14:42:56 bostic 22 21
c fold halt into reboot; clean up the options, add -l back in
e
s 00103/00067/00053
d D 5.12 91/10/28 17:44:00 bostic 21 20
c add getopt(3), delete -l option; do sync early on, lots of minor
c cleanups
e
s 00001/00003/00119
d D 5.11 91/02/27 17:01:22 bostic 20 18
c ANSI fixes
e
s 00001/00000/00122
d R 5.11 91/02/26 15:44:14 bostic 19 18
c ANSI fixes
e
s 00002/00001/00120
d D 5.10 91/02/03 01:41:22 torek 18 17
c getpwuid() is already declared in <pwd.h>
e
s 00001/00011/00120
d D 5.9 90/06/01 16:20:10 bostic 17 16
c new copyright notice
e
s 00005/00005/00126
d D 5.8 89/03/05 14:11:57 bostic 16 15
c pwd.h needs types.h
e
s 00002/00001/00129
d D 5.7 88/12/06 17:14:26 mckusick 15 14
c use values from <sys/syscall.h> (4.3BSD/etc/150)
e
s 00017/00006/00113
d D 5.6 88/10/29 21:59:03 bostic 14 13
c add Berkeley specific copyright
e
s 00001/00020/00118
d D 5.5 88/09/20 13:44:29 bostic 13 12
c use logwtmp()
e
s 00014/00007/00124
d D 5.4 86/05/26 22:12:21 karels 12 11
c consistency, use SIGTERM once then SIGKILL's, uniform logging (once)
e
s 00018/00011/00113
d D 5.3 86/05/24 22:46:26 karels 11 10
c log username, log before kill, give init a sec to TSTP
e
s 00003/00030/00121
d D 5.2 86/05/12 18:30:14 eric 10 9
c eliminate shutdownlog in favor of syslog
e
s 00014/00002/00137
d D 5.1 85/05/28 15:05:07 dist 9 8
c Add copyright
e
s 00001/00001/00138
d D 4.8 83/07/02 00:18:56 sam 8 7
c include fixes
e
s 00004/00000/00135
d D 4.7 83/05/22 23:57:36 sam 7 6
c utmp changed format
e
s 00001/00000/00134
d D 4.6 83/02/09 14:59:26 sam 6 5
c allow reboots across the net
e
s 00002/00000/00132
d D 4.5 81/04/21 02:07:16 root 5 4
c add check for failure to fopen shutdownlog
e
s 00002/00000/00130
d D 4.4 81/04/02 23:17:58 root 4 3
c Fixed previous
e
s 00029/00000/00101
d D 4.3 81/04/02 23:15:50 root 3 2
c Added logging
e
s 00076/00008/00025
d D 4.2 81/02/28 23:00:30 wnj 2 1
c new reboot scheme
e
s 00033/00000/00000
d D 4.1 80/10/10 00:45:10 bill 1 0
c date and time created 80/10/10 00:45:10 by bill
e
u
U
t
T
I 9
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
E 11
I 11
D 14
 * Copyright (c) 1980,1986 Regents of the University of California.
E 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
D 23
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
D 17
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
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 14
 */

E 9
I 7
#ifndef lint
E 7
I 1
D 2
#include <stdio.h>
#include <sys/reboot.h>
E 2
I 2
D 9
static	char *sccsid = "%W% (Berkeley) %G%";
I 7
#endif
E 9
I 9
D 23
char copyright[] =
D 12
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 12
I 12
D 14
"%Z% Copyright (c) 1980,1986 Regents of the University of California.\n\
E 14
I 14
"%Z% Copyright (c) 1980, 1986 The Regents of the University of California.\n\
E 14
E 12
 All rights reserved.\n";
E 23
I 23
static char copyright[] =
"%Z% Copyright (c) 1980, 1986, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 23
D 14
#endif not lint
E 14
I 14
#endif /* not lint */
E 14

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 14
#endif not lint
E 14
I 14
#endif /* not lint */
E 14
E 9

E 7
E 2
D 20
/*
 * Reboot
 */
E 20
D 2
static	char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 16
#include <stdio.h>
#include <sys/reboot.h>
#include <errno.h>
#include <signal.h>
I 11
#include <pwd.h>
E 16
E 11
I 3
D 21
#include <sys/types.h>
D 8
#include <time.h>
E 8
I 8
#include <sys/time.h>
I 10
D 11
#include <syslog.h>
E 11
I 11
#include <sys/syslog.h>
I 15
#include <sys/syscall.h>
E 21
I 16
#include <sys/reboot.h>
D 21
#include <sys/signal.h>
E 21
I 21
#include <signal.h>
E 21
#include <pwd.h>
D 21
#include <stdio.h>
E 21
#include <errno.h>
I 21
#include <syslog.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
E 21
E 16
E 15
E 11
E 10
E 8
E 3
E 2

I 21
void err __P((const char *fmt, ...));
void usage __P((void));

I 22
int dohalt;

E 22
int
E 21
I 3
D 10
#define SHUTDOWNLOG "/usr/adm/shutdownlog"

E 10
E 3
main(argc, argv)
	int argc;
D 21
	char **argv;
E 21
I 21
	char *argv[];
E 21
{
D 21
	int howto;
	register char *argp;
I 2
	register i;
	register ok = 0;
	register qflag = 0;
I 12
	int needlog = 1;
E 12
I 11
	char *user, *getlogin();
E 21
I 21
	register int i;
E 21
D 18
	struct passwd *pw, *getpwuid();
E 18
I 18
	struct passwd *pw;
I 21
D 22
	int ch, howto, nflag, qflag, sverrno;
	char *user;
E 22
I 22
	int ch, howto, lflag, nflag, qflag, sverrno;
	char *p, *user;
E 22
E 21
E 18
E 11
E 2

I 10
D 21
	openlog("reboot", 0, LOG_AUTH);
E 10
	argc--, argv++;
	howto = 0;
	while (argc > 0) {
D 2
		if (!strcmp(*argv, "-s"))
			howto |= RB_SINGLE;
E 2
I 2
		if (!strcmp(*argv, "-q"))
			qflag++;
E 2
		else if (!strcmp(*argv, "-n"))
E 21
I 21
D 22
	howto = nflag = qflag = 0;
	while ((ch = getopt(argc, argv, "nq")) != EOF)
E 22
I 22
	if (!strcmp((p = rindex(*argv, '/')) ? p + 1 : *argv, "halt")) {
		dohalt = 1;
		howto = RB_HALT;
	} else
		howto = 0;
	lflag = nflag = qflag = 0;
	while ((ch = getopt(argc, argv, "lnq")) != EOF)
E 22
		switch(ch) {
I 22
		case 'l':		/* Undocumented; used by shutdown. */
			lflag = 1;
			break;
E 22
		case 'n':
			nflag = 1;
E 21
			howto |= RB_NOSYNC;
I 12
D 21
		else if (!strcmp(*argv, "-l"))
			needlog = 0;
E 12
D 2
		else if (!strcmp(*argv, "-a"))
			howto |= RB_ASKNAME;
E 2
		else {
			fprintf(stderr,
D 2
			    "usage: reboot [ -a ] [ -n ] [ -s ]\n");
E 2
I 2
			    "usage: reboot [ -n ][ -q ]\n");
E 2
			exit(1);
E 21
I 21
			break;
		case 'q':
			qflag = 1;
D 22
			howto |= RB_NOSYNC;
E 22
			break;
		case '?':
		default:
			usage();
E 21
		}
D 21
		argc--, argv++;
	}
E 21
I 21
	argc -= optind;
	argv += optind;
E 21
I 2

I 11
D 12
	user = getlogin();
	if (user == (char *)0 && (pw = getpwuid(getuid())))
		user = pw->pw_name;
	if (user == (char *)0)
		user = "root";
	syslog(LOG_CRIT, "halted by %s", user);
E 12
I 12
D 21
	if (needlog) {
		user = getlogin();
		if (user == (char *)0 && (pw = getpwuid(getuid())))
			user = pw->pw_name;
		if (user == (char *)0)
			user = "root";
		syslog(LOG_CRIT, "rebooted by %s", user);
	}
E 21
I 21
	if (geteuid())
		err("%s", strerror(EPERM));
E 21
E 12

E 11
I 6
D 21
	signal(SIGHUP, SIG_IGN);	/* for remote connections */
E 6
	if (kill(1, SIGTSTP) == -1) {
		fprintf(stderr, "reboot: can't idle init\n");
		exit(1);
E 21
I 21
	if (qflag) {
		reboot(howto);
		err("%s", strerror(errno));
E 21
	}
I 21

I 22
	/* Log the reboot. */
	if (!lflag)  {
		if ((user = getlogin()) == NULL)
			user = (pw = getpwuid(getuid())) ?
			    pw->pw_name : "???";
		if (dohalt) {
			openlog("halt", 0, LOG_AUTH | LOG_CONS);
			syslog(LOG_CRIT, "halted by %s", user);
		} else {
			openlog("reboot", 0, LOG_AUTH | LOG_CONS);
			syslog(LOG_CRIT, "rebooted by %s", user);
		}
	}
	logwtmp("~", "shutdown", "");

E 22
	/*
	 * Do a sync early on, so disks start transfers while we're off
	 * killing processes.  Don't worry about writes done before the
	 * processes die, the reboot system call syncs the disks.
	 */
	if (!nflag)
		sync();

	/* Just stop init -- if we fail, we'll restart it. */
	if (kill(1, SIGTSTP) == -1)
		err("SIGTSTP init: %s", strerror(errno));
E 21
I 11
D 22
	sleep(1);
E 22
I 12
D 21
	(void) kill(-1, SIGTERM);	/* one chance to catch it */
E 21
I 21

	/* Ignore the SIGHUP we get when our parent shell dies. */
	(void)signal(SIGHUP, SIG_IGN);

	/* Send a SIGTERM first, a chance to save the buffers. */
	if (kill(-1, SIGTERM) == -1)
		err("SIGTERM processes: %s", strerror(errno));
E 21
D 22
	sleep(5);
E 22
E 12
E 11

I 22
	/*
	 * After the processes receive the signal, start the rest of the
	 * buffers on their way.  Wait 5 seconds between the SIGTERM and
	 * the SIGKILL to give everybody a chance.
	 */
	sleep(2);
	if (!nflag)
		sync();
	sleep(3);

E 22
D 21
	if (!qflag) for (i = 1; ; i++) {
E 21
I 21
	for (i = 1;; ++i) {
E 21
		if (kill(-1, SIGKILL) == -1) {
D 21
			extern int errno;

E 21
			if (errno == ESRCH)
				break;
D 21

			perror("reboot: kill");
			kill(1, SIGHUP);
			exit(1);
E 21
I 21
			goto restart;
E 21
		}
		if (i > 5) {
D 11
	fprintf(stderr, "CAUTION: some process(es) wouldn't die\n");
E 11
I 11
D 21
			fprintf(stderr,
			    "CAUTION: some process(es) wouldn't die\n");
E 21
I 21
			(void)fprintf(stderr,
			    "WARNING: some process(es) wouldn't die\n");
E 21
E 11
			break;
		}
D 21
		setalarm(2 * i);
		pause();
E 21
I 21
		(void)sleep(2 * i);
E 21
	}

I 4
D 11
	if ((howto & RB_NOSYNC) == 0)
D 10
		log_entry();
E 10
I 10
		syslog(LOG_CRIT, "halted for reboot");
E 10
E 4
	if (!qflag) {
		if (!(howto & RB_NOSYNC)) {
			markdown();
			sync();
			sync();
		}
E 11
I 11
D 21
	if (!qflag && (howto & RB_NOSYNC) == 0) {
E 21
I 21
D 22
	/* Log the reboot. */
	if (!nflag) {
		openlog("reboot", 0, LOG_AUTH | LOG_CONS);

		if ((user = getlogin()) == NULL)
			user = (pw = getpwuid(getuid())) ? pw->pw_name : "???";
		syslog(LOG_CRIT, "rebooted by %s", user);
E 21
D 13
		markdown();
E 13
I 13
		logwtmp("~", "shutdown", "");
E 13
D 21
		sync();
E 11
		setalarm(5);
		pause();
E 21
	}
E 2
D 15
	syscall(55, howto);
E 15
I 15
D 21
	syscall(SYS_reboot, howto);
E 15
	perror("reboot");
I 2
	kill(1, SIGHUP);
	exit(1);
E 21
I 21

E 22
	reboot(howto);
D 22
	/* NOTREACHED */
E 22
I 22
	/* FALLTHROUGH */
E 22

restart:
	sverrno = errno;
D 22
	err("%s%s", kill(1, SIGHUP) == -1 ? "(can't restart init)" : "",
E 22
I 22
	err("%s%s", kill(1, SIGHUP) == -1 ? "(can't restart init): " : "",
E 22
	    strerror(sverrno));
	/* NOTREACHED */
E 21
}

I 20
void
E 20
D 21
dingdong()
E 21
I 21
usage()
E 21
{
D 21
	/* RRRIIINNNGGG RRRIIINNNGGG */
E 21
I 21
D 22
	(void)fprintf(stderr, "usage: reboot [-nq]\n");
E 22
I 22
	(void)fprintf(stderr, "usage: %s [-nq]\n", dohalt ? "halt" : "reboot");
E 22
	exit(1);
E 21
}

D 21
setalarm(n)
I 18
	int n;
E 21
I 21
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
E 21
E 18
{
D 21
	signal(SIGALRM, dingdong);
	alarm(n);
E 21
I 21
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
D 22
	(void)fprintf(stderr, "reboot: ");
E 22
I 22
	(void)fprintf(stderr, "%s: ", dohalt ? "halt" : "reboot");
E 22
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 21
D 13
}

#include <utmp.h>
#define SCPYN(a, b)	strncpy(a, b, sizeof(a))
char	wtmpf[]	= "/usr/adm/wtmp";
struct utmp wtmp;

markdown()
{
	register f = open(wtmpf, 1);
	if (f >= 0) {
		lseek(f, 0L, 2);
		SCPYN(wtmp.ut_line, "~");
		SCPYN(wtmp.ut_name, "shutdown");
I 7
		SCPYN(wtmp.ut_host, "");
E 7
		time(&wtmp.ut_time);
		write(f, (char *)&wtmp, sizeof(wtmp));
		close(f);
	}
E 13
I 3
D 10
}

char *days[] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

char *months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
	"Oct", "Nov", "Dec"
};

log_entry()
{
	FILE *fp;
	struct tm *tm, *localtime();
	time_t now;

	time(&now);
	tm = localtime(&now);
	fp = fopen(SHUTDOWNLOG, "a");
I 5
	if (fp == 0)
		return;
E 5
	fseek(fp, 0L, 2);
	fprintf(fp, "%02d:%02d  %s %s %2d, %4d.  Halted for reboot.\n", tm->tm_hour,
		tm->tm_min, days[tm->tm_wday], months[tm->tm_mon],
		tm->tm_mday, tm->tm_year + 1900);
	fclose(fp);
E 10
E 3
E 2
}
E 1
