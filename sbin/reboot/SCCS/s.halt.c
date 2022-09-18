h19231
s 00001/00001/00127
d D 5.10 91/04/03 08:35:36 bostic 19 18
c use reboot system call, don't use syscall(55, ...)
e
s 00001/00000/00127
d D 5.9 91/02/26 15:35:04 bostic 18 17
c ANSI fixes
e
s 00002/00001/00125
d D 5.8 91/02/03 01:39:22 torek 17 16
c getpwuid() is already declared in <pwd.h>
e
s 00001/00011/00125
d D 5.7 90/06/01 16:16:48 bostic 16 15
c new copyright notice
e
s 00005/00004/00131
d D 5.6 89/05/11 13:53:19 bostic 15 14
c file reorg, pathnames.h, paths.h
e
s 00048/00053/00087
d D 5.5 88/09/20 12:00:54 bostic 14 13
c add getopt, fix usage message, errors should be "halt", not "reboot"
c use logwtmp() routine, remove markdown, add Berkeley specific copyright
e
s 00014/00007/00126
d D 5.4 86/05/26 22:12:00 karels 13 12
c consistency, use SIGTERM once then SIGKILL's, uniform logging (once)
e
s 00018/00011/00115
d D 5.3 86/05/24 22:46:18 karels 12 11
c log username, log before kill, give init a sec to TSTP
e
s 00003/00030/00123
d D 5.2 86/05/12 18:30:07 eric 11 10
c eliminate shutdownlog in favor of syslog
e
s 00014/00002/00139
d D 5.1 85/04/29 12:47:58 dist 10 9
c Add copyright
e
s 00001/00001/00140
d D 4.9 83/07/02 00:18:51 sam 9 8
c include fixes
e
s 00004/00000/00137
d D 4.8 83/05/22 23:57:41 sam 8 7
c utmp changed format
e
s 00001/00000/00136
d D 4.7 83/01/02 14:55:46 sam 7 6
c don't die when halted over the net
e
s 00001/00001/00135
d D 4.6 82/12/03 20:39:42 mckusick 6 5
c initialize "qflag" as per bob gray's report
e
s 00002/00000/00134
d D 4.5 81/04/17 20:30:44 root 5 4
c check for fp==NULL and return
e
s 00031/00000/00103
d D 4.4 81/04/02 23:11:53 root 4 3
c Added log entry
e
s 00069/00000/00034
d D 4.3 81/02/28 23:00:26 wnj 3 2
c new reboot scheme
e
s 00007/00000/00027
d D 4.2 80/11/10 20:19:54 bill 2 1
c paranoia about dialups
e
s 00027/00000/00000
d D 4.1 80/10/10 00:42:56 bill 1 0
c date and time created 80/10/10 00:42:56 by bill
e
u
U
t
T
I 10
/*
D 12
 * Copyright (c) 1980 Regents of the University of California.
E 12
I 12
D 14
 * Copyright (c) 1980,1986 Regents of the University of California.
E 12
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
 *
D 16
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
E 16
I 16
 * %sccs.include.redist.c%
E 16
E 14
 */

E 10
I 8
#ifndef lint
E 8
I 1
D 10
static	char *sccsid = "%W% (Berkeley) %G%";
I 8
#endif
E 10
I 10
char copyright[] =
D 13
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 13
I 13
D 14
"%Z% Copyright (c) 1980,1986 Regents of the University of California.\n\
E 14
I 14
"%Z% Copyright (c) 1980, 1986 The Regents of the University of California.\n\
E 14
E 13
 All rights reserved.\n";
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
E 10

E 8
/*
 * Halt
 */
D 15
#include <stdio.h>
#include <sys/reboot.h>
E 15
I 4
#include <sys/types.h>
I 15
#include <sys/reboot.h>
E 15
D 9
#include <time.h>
E 9
I 9
#include <sys/time.h>
I 12
#include <sys/syslog.h>
I 15
#include <sys/signal.h>
E 15
E 12
E 9
E 4
I 3
#include <errno.h>
D 15
#include <signal.h>
E 15
I 11
D 12
#include <syslog.h>
E 12
I 12
#include <pwd.h>
I 15
#include <stdio.h>
#include <paths.h>
E 15
E 12
E 11
E 3

I 4
D 11
#define SHUTDOWNLOG "/usr/adm/shutdownlog"

E 11
E 4
main(argc, argv)
	int argc;
	char **argv;
{
D 14
	int howto;
I 2
	char *ttyn = (char *)ttyname(2);
I 3
	register i;
D 6
	register qflag;
E 6
I 6
	register qflag = 0;
I 13
	int needlog = 1;
E 13
I 12
	char *user, *getlogin();
E 14
I 14
	register int i;
	register int qflag = 0;
E 14
D 17
	struct passwd *pw, *getpwuid();
E 17
I 17
	struct passwd *pw;
E 17
I 14
	int ch, howto, needlog = 1;
	char *user, *ttyn, *getlogin(), *ttyname();
E 14
E 12
E 6
E 3
E 2

I 11
D 14
	openlog("halt", 0, LOG_AUTH);
E 14
E 11
	howto = RB_HALT;
D 14
	argc--, argv++;
	while (argc > 0) {
		if (!strcmp(*argv, "-n"))
E 14
I 14
	ttyn = ttyname(2);
	while ((ch = getopt(argc, argv, "lnqy")) != EOF)
		switch((char)ch) {
		case 'l':		/* undocumented; for shutdown(8) */
			needlog = 0;
			break;
		case 'n':
E 14
			howto |= RB_NOSYNC;
I 2
D 14
		else if (!strcmp(*argv, "-y"))
			ttyn = 0;
I 3
		else if (!strcmp(*argv, "-q"))
E 14
I 14
			break;
		case 'q':
E 14
			qflag++;
I 13
D 14
		else if (!strcmp(*argv, "-l"))
			needlog = 0;
E 13
E 3
E 2
		else {
			fprintf(stderr, "usage: halt [ -n ]\n");
E 14
I 14
			break;
		case 'y':
			ttyn = 0;
			break;
		case '?':
		default:
			fprintf(stderr, "usage: halt [-nqy]\n");
E 14
			exit(1);
		}
D 14
		argc--, argv++;
I 2
	}
E 14
I 14

E 14
D 15
	if (ttyn && *(ttyn+strlen("/dev/tty")) == 'd') {
E 15
I 15
	if (ttyn && ttyn[sizeof(_PATH_TTY) - 1] == 'd') {
E 15
		fprintf(stderr, "halt: dangerous on a dialup; use ``halt -y'' if you are really sure\n");
		exit(1);
E 2
	}
I 3

I 12
D 13
	user = getlogin();
	if (user == (char *)0 && (pw = getpwuid(getuid())))
		user = pw->pw_name;
	if (user == (char *)0)
		user = "root";
	syslog(LOG_CRIT, "halted by %s", user);
E 13
I 13
	if (needlog) {
D 14
		user = getlogin();
		if (user == (char *)0 && (pw = getpwuid(getuid())))
			user = pw->pw_name;
		if (user == (char *)0)
			user = "root";
E 14
I 14
		openlog("halt", 0, LOG_AUTH);
		if ((user = getlogin()) == NULL)
			if ((pw = getpwuid(getuid())))
				user = pw->pw_name;
			else
				user = "???";
E 14
		syslog(LOG_CRIT, "halted by %s", user);
	}
E 13

E 12
I 7
	signal(SIGHUP, SIG_IGN);		/* for network connections */
E 7
	if (kill(1, SIGTSTP) == -1) {
D 14
		fprintf(stderr, "reboot: can't idle init\n");
E 14
I 14
		fprintf(stderr, "halt: can't idle init\n");
E 14
		exit(1);
	}
I 12
	sleep(1);
I 13
	(void) kill(-1, SIGTERM);	/* one chance to catch it */
	sleep(5);
E 13
E 12

	if (!qflag) for (i = 1; ; i++) {
		if (kill(-1, SIGKILL) == -1) {
			extern int errno;

			if (errno == ESRCH)
				break;

D 14
			perror("reboot: kill");
E 14
I 14
			perror("halt: kill");
E 14
			kill(1, SIGHUP);
			exit(1);
		}
		if (i > 5) {
D 12
	fprintf(stderr, "CAUTION: some process(es) wouldn't die\n");
E 12
I 12
			fprintf(stderr,
			    "CAUTION: some process(es) wouldn't die\n");
E 12
			break;
		}
		setalarm(2 * i);
		pause();
	}

I 4
D 12
	if ((howto & RB_NOSYNC) == 0)
D 11
		log_entry();
E 11
I 11
		syslog(LOG_CRIT, "halted");
E 11
E 4
	if (!qflag) {
		if ((howto & RB_NOSYNC)==0) {
			markdown();
			sync();
			sync();
		}
E 12
I 12
	if (!qflag && (howto & RB_NOSYNC) == 0) {
D 14
		markdown();
E 14
I 14
		logwtmp("~", "shutdown", "");
E 14
		sync();
E 12
		setalarm(5);
		pause();
	}
E 3
D 19
	syscall(55, howto);
E 19
I 19
	reboot(howto);
E 19
D 14
	perror("reboot");
E 14
I 14
	perror("halt");
E 14
I 3
}

I 18
void
E 18
dingdong()
{
	/* RRRIIINNNGGG RRRIIINNNGGG */
}

setalarm(n)
I 17
	int n;
E 17
{
	signal(SIGALRM, dingdong);
	alarm(n);
D 14
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
I 8
		SCPYN(wtmp.ut_host, "");
E 8
		time(&wtmp.ut_time);
		write(f, (char *)&wtmp, sizeof(wtmp));
		close(f);
	}
E 14
I 4
D 11
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
	if (fp == NULL)
		return;
E 5
	fseek(fp, 0L, 2);
	fprintf(fp, "%02d:%02d  %s %s %2d, %4d.  Halted.\n", tm->tm_hour,
		tm->tm_min, days[tm->tm_wday], months[tm->tm_mon],
		tm->tm_mday, tm->tm_year + 1900);
	fclose(fp);
E 11
E 4
E 3
}
E 1
