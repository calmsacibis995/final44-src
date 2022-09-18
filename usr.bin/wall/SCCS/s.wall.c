h31398
s 00014/00004/00161
d D 8.2 93/11/16 11:39:26 bostic 27 26
c The source ttymsg.c needed a check for slash in the utmp entries. Don't
c forget to recompile talkd and syslogd in addition to wall after fixing
c this. Also, I found that the string wall passes to ttymsg() wasn't
c strictly terminated. And there were some new gcc warnings to contend
c with.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00005/00005/00160
d D 8.1 93/06/06 22:23:30 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00164
d D 5.16 91/10/29 16:36:19 torek 25 24
c no *(char *)NULL please
e
s 00001/00001/00164
d D 5.15 91/08/01 16:05:32 marc 24 23
c ttymsg now takes timeout parameter
e
s 00003/00002/00162
d D 5.14 91/03/02 13:23:10 bostic 23 22
c ANSI
e
s 00001/00011/00163
d D 5.13 90/09/07 12:05:00 bostic 22 21
c new copyright notice
e
s 00001/00001/00173
d D 5.12 90/06/29 00:44:38 marc 21 20
c fix ttymsg
e
s 00043/00024/00131
d D 5.11 90/02/24 19:50:57 karels 20 19
c add -n for shutdown
e
s 00037/00076/00118
d D 5.10 89/10/28 13:50:17 bostic 19 18
c separate out sendmsg for syslogd(8); put blank padding back in;
c minor cleanups
e
s 00004/00003/00190
d D 5.9 89/10/28 10:08:52 bostic 18 17
c checked in for Marc; he made wall work on the dial-up slip lines
e
s 00002/00001/00191
d D 5.8 89/09/11 22:13:08 bostic 17 16
c get rid of pathnames.h
e
s 00042/00049/00150
d D 5.7 89/09/07 15:32:13 marc 16 15
c pathnames.h, use O_NONBLOCK, extra error checking, cleanups
e
s 00014/00012/00185
d D 5.6 88/10/10 12:04:58 bostic 15 14
c not stepping through the buffer correctly
e
s 00156/00114/00041
d D 5.5 88/09/18 16:59:19 bostic 14 13
c remove message length limit; blank out message area; fix FNDELAY stuff
c complete rewrite
e
s 00001/00001/00154
d D 5.4 87/10/22 09:59:09 bostic 13 12
c ANSI C; sprintf now returns an int.
e
s 00001/00001/00154
d D 5.3 86/04/20 05:30:40 lepreau 12 11
c ^G -> \007
e
s 00013/00007/00142
d D 5.2 85/06/04 00:25:02 bloom 11 9
c add support for arbitrary number of utmp entries
e
s 00013/00007/00142
d R 5.2 85/06/03 11:14:55 bloom 10 9
c add support for arbitrary number of utmp entries
e
s 00016/00001/00133
d D 5.1 85/05/02 14:49:10 dist 9 8
c 
e
s 00067/00056/00067
d D 4.8 84/03/30 11:27:45 ralph 8 7
c use non-blocking I/O instead of forking so much.
e
s 00001/00001/00122
d D 4.7 83/07/01 23:57:09 wnj 7 6
c include problems
e
s 00003/00012/00120
d D 4.6 82/03/15 04:19:28 root 6 5
c machine independent
e
s 00003/00001/00129
d D 4.5 81/06/12 13:23:15 root 5 4
c I suppressed wall messages to the sleeper program
e
s 00001/00001/00129
d D 4.4 81/05/06 18:44:43 mark 4 3
c 2nd try at delta from last bug fix
e
s 00000/00000/00130
d D 4.3 81/05/06 18:43:04 mark 3 2
c fixed portability bug - time(0) returns a long.
e
s 00039/00015/00091
d D 4.2 81/03/10 07:02:14 wnj 2 1
c miscellaneous minor fixups
e
s 00106/00000/00000
d D 4.1 80/10/01 17:29:26 bill 1 0
c date and time created 80/10/01 17:29:26 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 9
static char *sccsid = "%W% (Berkeley) %E%";
E 9
I 9
/*
D 14
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
D 20
 * Copyright (c) 1988 Regents of the University of California.
E 20
I 20
D 26
 * Copyright (c) 1988, 1990 Regents of the University of California.
E 20
 * All rights reserved.
E 26
I 26
 * Copyright (c) 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 22
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
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 14
 */

#ifndef lint
D 26
char copyright[] =
D 14
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 14
I 14
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
E 14
 All rights reserved.\n";
E 26
I 26
static char copyright[] =
"%Z% Copyright (c) 1988, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 26
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
E 2
/*
D 14
 * wall.c - Broadcast a message to all users.
 *
E 14
 * This program is not related to David Wall, whose Stanford Ph.D. thesis
 * is entitled "Mechanisms for Broadcast and Selective Broadcast".
 */

D 14
#include <stdio.h>
#include <utmp.h>
D 7
#include <time.h>
E 7
I 7
D 8
#include <sys/time.h>
E 8
I 8
#include <errno.h>
E 8
E 7
I 2
D 6
#include <whoami.h>
E 6
#include <signal.h>
E 14
I 14
#include <sys/param.h>
E 14
I 8
D 19
#include <sys/time.h>
E 19
D 14
#include <fcntl.h>
I 11
#include <sys/types.h>
E 14
I 14
D 16
#include <sys/signal.h>
E 16
E 14
#include <sys/stat.h>
I 14
D 19
#include <sys/dir.h>
D 16
#include <fcntl.h>
E 16
I 16
#include <sys/file.h>
E 19
I 19
#include <sys/time.h>
#include <sys/uio.h>
E 19
E 16
D 27
#include <utmp.h>
E 27
I 27

#include <paths.h>
E 27
#include <pwd.h>
D 19
#include <errno.h>
E 19
#include <stdio.h>
I 23
#include <stdlib.h>
E 23
I 16
D 17
#include "pathnames.h"
E 17
I 17
D 27
#include <paths.h>
E 27
I 27
#include <string.h>
#include <unistd.h>
#include <utmp.h>
E 27
E 17
E 16
E 14
E 11

I 27
void	makemsg __P((char *));

E 27
E 8
E 2
D 11
#define	USERS	128
E 11
I 5
D 14
#define IGNOREUSER	"sleeper"
E 14
I 14
#define	IGNOREUSER	"sleeper"
D 16
#define	UTMP		"/etc/utmp"
E 16
E 14
E 5

I 20
int nobanner;
E 20
I 6
D 14
char	hostname[32];
E 6
char	mesg[3000];
int	msize,sline;
D 11
struct	utmp utmp[USERS];
E 11
I 11
struct	utmp *utmp;
E 11
char	*strcpy();
char	*strcat();
I 11
char	*malloc();
E 11
D 8
char who[9] = "???";
E 8
I 8
char	who[9] = "???";
E 8
D 4
long	clock;
E 4
I 4
long	clock, time();
E 4
struct tm *localtime();
struct tm *localclock;
E 14
I 14
D 16
static int mbufsize;
static char *mbuf;
E 16
I 16
int mbufsize;
char *mbuf;
E 16
E 14

I 8
D 14
extern	errno;

E 14
I 14
/* ARGSUSED */
I 27
int
E 27
E 14
E 8
main(argc, argv)
D 14
char *argv[];
E 14
I 14
	int argc;
	char **argv;
E 14
{
I 20
	extern int optind;
	int ch;
E 20
I 19
	struct iovec iov;
E 19
D 8
	register i;
	register char c;
E 8
I 8
D 14
	register int i, c;
E 8
	register struct utmp *p;
D 11
	FILE *f;
E 11
I 11
	int f;
	struct stat statb;
E 14
I 14
	struct utmp utmp;
	FILE *fp;
I 19
	char *p, *ttymsg();
I 27
	char line[sizeof(utmp.ut_line) + 1];
E 27
E 19
E 14
E 11
I 2
D 8
	FILE *mf;
E 8
E 2

I 6
D 11
	gethostname(hostname, sizeof (hostname));
E 6
D 8
	if((f = fopen("/etc/utmp", "r")) == NULL) {
E 8
I 8
	if ((f = fopen("/etc/utmp", "r")) == NULL) {
E 11
I 11
D 14
	(void) gethostname(hostname, sizeof (hostname));
	if ((f = open("/etc/utmp", O_RDONLY, 0)) < 0) {
E 11
E 8
		fprintf(stderr, "Cannot open /etc/utmp\n");
E 14
I 14
D 20
	if (argc > 2) {
D 19
		fprintf(stderr, "usage: wall [file]\n");
E 19
I 19
		(void)fprintf(stderr, "usage: wall [file]\n");
E 19
E 14
		exit(1);
	}
E 20
I 20
	while ((ch = getopt(argc, argv, "n")) != EOF)
		switch (ch) {
		case 'n':
			/* undoc option for shutdown: suppress banner */
			if (geteuid() == 0)
				nobanner = 1;
			break;
		case '?':
		default:
usage:
			(void)fprintf(stderr, "usage: wall [file]\n");
			exit(1);
		}
	argc -= optind;
	argv += optind;
	if (argc > 1)
		goto usage;
E 20
D 14
	clock = time( 0 );
	localclock = localtime( &clock );
D 2
	fread((char *)utmp, sizeof(struct utmp), USERS, f);
	fclose(f);
	f = stdin;
E 2
I 2
D 8
	mf = stdin;
E 2
	if(argc >= 2) {
E 8
I 8
	sline = ttyslot();	/* 'utmp' slot no. of sender */
D 11
	c = fread((char *)utmp, sizeof(struct utmp), USERS, f);
	fclose(f);
E 11
I 11
	(void) fstat(f, &statb);
	utmp = (struct utmp *)malloc(statb.st_size);
	c = read(f, (char *)utmp, statb.st_size);
	(void) close(f);
	c /= sizeof(struct utmp);
E 11
	if (sline)
		strncpy(who, utmp[sline].ut_name, sizeof(utmp[sline].ut_name));
D 13
	sprintf(mesg,
E 13
I 13
	(void)sprintf(mesg,
E 13
D 12
	    "\nBroadcast Message from %s@%s (%.*s) at %d:%02d ...\r\n\n"
E 12
I 12
	    "\n\007\007Broadcast Message from %s@%s (%.*s) at %d:%02d ...\r\n\n"
E 12
		, who
		, hostname
		, sizeof(utmp[sline].ut_line)
		, utmp[sline].ut_line
		, localclock -> tm_hour
		, localclock -> tm_min
	);
	msize = strlen(mesg);
	if (argc >= 2) {
E 8
		/* take message from unix file instead of standard input */
D 2
		if((f = fopen(argv[1], "r")) == NULL) {
E 2
I 2
D 8
		if((mf = fopen(argv[1], "r")) == NULL) {
E 2
			fprintf(stderr,"Cannot open %s\n", argv[1]);
E 8
I 8
		if (freopen(argv[1], "r", stdin) == NULL) {
			perror(argv[1]);
E 8
			exit(1);
		}
E 14
I 14
D 19
	makemsg(argv);
E 19

I 19
D 20
	makemsg(*++argv);
E 20
I 20
	makemsg(*argv);
E 20

E 19
D 16
	if (!(fp = fopen(UTMP, "r"))) {
		fprintf(stderr, "wall: cannot read /etc/utmp.\n");
E 16
I 16
	if (!(fp = fopen(_PATH_UTMP, "r"))) {
D 19
		fprintf(stderr, "wall: cannot read %s.\n", _PATH_UTMP);
E 19
I 19
		(void)fprintf(stderr, "wall: cannot read %s.\n", _PATH_UTMP);
E 19
E 16
		exit(1);
E 14
	}
I 19
	iov.iov_base = mbuf;
	iov.iov_len = mbufsize;
E 19
D 2
	while((i = getc(f)) != EOF) mesg[msize++] = i;
	fclose(f);
	sline = ttyslot(2); /* 'utmp' slot no. of sender */
	if (sline) {
		for (i=0;(c=utmp[sline].ut_name[i]) && i<sizeof(utmp[0].ut_name);i++)
			who[i]=c;
		who[i] = '\0'; /* sender initials */
E 2
I 2
D 8
	while((i = getc(mf)) != EOF) {
E 8
I 8
D 14
	while ((i = getchar()) != EOF) {
		if (i == '\n')
			mesg[msize++] = '\r';
E 8
		if (msize >= sizeof mesg) {
			fprintf(stderr, "Message too long\n");
			exit(1);
E 2
		}
I 2
		mesg[msize++] = i;
	}
D 8
	fclose(mf);
	sline = ttyslot(2); /* 'utmp' slot no. of sender */
	fread((char *)utmp, sizeof(struct utmp), USERS, f);
	fclose(f);
	if (sline)
		strncpy(who, utmp[sline].ut_name, sizeof(utmp[sline].ut_name));
E 2
	for(i=0; i<USERS; i++) {
E 8
I 8
	fclose(stdin);
	for (i=0; i<c; i++) {
E 8
		p = &utmp[i];
D 5
		if(p->ut_name[0] == 0)
E 5
I 5
D 8
		if ((p->ut_name[0] == 0) ||
		    (strncmp (p->ut_name, IGNOREUSER, sizeof(p->ut_name)) == 0))
E 8
I 8
		if (p->ut_name[0] == 0 ||
		    strncmp(p->ut_name, IGNOREUSER, sizeof(p->ut_name)) == 0)
E 14
I 14
	/* NOSTRICT */
D 15
	while (fread((char *)&utmp, sizeof(utmp), 1, fp) == 1) {
		if (!utmp.ut_name[0] ||
		    !strncmp(utmp.ut_name, IGNOREUSER, sizeof(utmp.ut_name)))
E 14
E 8
E 5
			continue;
I 2
D 6
	/***		this might be nice, but utmp gets so out of date !!
E 2
		sleep(1);
I 2
	***/
E 6
E 2
D 14
		sendmes(p->ut_line);
E 14
I 14
		sendmsg(utmp.ut_line);
E 14
	}
E 15
I 15
D 19
	while (fread((char *)&utmp, sizeof(utmp), 1, fp) == 1)
		if (utmp.ut_name[0] &&
		    strncmp(utmp.ut_name, IGNOREUSER, sizeof(utmp.ut_name)))
D 16
			sendmsg(utmp.ut_line);
E 16
I 16
			sendmsg(utmp.ut_line, 1, mbufsize);
E 19
I 19
	while (fread((char *)&utmp, sizeof(utmp), 1, fp) == 1) {
		if (!utmp.ut_name[0] ||
		    !strncmp(utmp.ut_name, IGNOREUSER, sizeof(utmp.ut_name)))
			continue;
D 21
		if (p = ttymsg(&iov, 1, utmp.ut_line, 1))
E 21
I 21
D 24
		if (p = ttymsg(&iov, 1, utmp.ut_line))
E 24
I 24
D 27
		if (p = ttymsg(&iov, 1, utmp.ut_line, 60*5))
E 27
I 27
		strncpy(line, utmp.ut_line, sizeof(utmp.ut_line));
		line[sizeof(utmp.ut_line)] = '\0';
		if ((p = ttymsg(&iov, 1, line, 60*5)) != NULL)
E 27
E 24
E 21
			(void)fprintf(stderr, "wall: %s\n", p);
	}
E 19
E 16
E 15
	exit(0);
}

I 27
void
E 27
D 14
sendmes(tty)
char *tty;
E 14
I 14
D 19
makemsg(argv)
	char **argv;
E 19
I 19
makemsg(fname)
	char *fname;
E 19
E 14
{
D 8
	register i;
	char t[50], buf[BUFSIZ];
	register char *cp;
	register int c, ch;
	FILE *f;
E 8
I 8
D 14
	register f, flags;
	static char t[50] = "/dev/";
	int e, i;
E 14
I 14
	register int ch, cnt;
	struct tm *lt;
D 23
	struct passwd *pw, *getpwuid();
E 23
I 23
	struct passwd *pw;
E 23
	struct stat sbuf;
	time_t now, time();
	FILE *fp;
	int fd;
	char *p, *whom, hostname[MAXHOSTNAMELEN], lbuf[100], tmpname[15];
D 23
	char *getlogin(), *malloc(), *strcpy(), *ttyname();
E 23
I 23
	char *getlogin(), *strcpy(), *ttyname();
E 23
E 14
E 8

I 8
D 14
	strcpy(t + 5, tty);
E 14
I 14
D 16
	(void)strcpy(tmpname, "/tmp/wall.XXX");
E 16
I 16
	(void)strcpy(tmpname, _PATH_TMP);
I 17
	(void)strcat(tmpname, "/wall.XXXXXX");
E 17
E 16
	if (!(fd = mkstemp(tmpname)) || !(fp = fdopen(fd, "r+"))) {
D 19
		fprintf(stderr, "wall: can't open temporary file.\n");
E 19
I 19
		(void)fprintf(stderr, "wall: can't open temporary file.\n");
E 19
		exit(1);
	}
	(void)unlink(tmpname);
E 14

D 14
	if ((f = open(t, O_WRONLY|O_NDELAY)) < 0) {
		if (errno != EWOULDBLOCK)
			perror(t);
		return;
E 14
I 14
D 20
	if (!(whom = getlogin()))
		whom = (pw = getpwuid(getuid())) ? pw->pw_name : "???";
	(void)gethostname(hostname, sizeof(hostname));
	(void)time(&now);
	lt = localtime(&now);
E 20
I 20
	if (!nobanner) {
		if (!(whom = getlogin()))
			whom = (pw = getpwuid(getuid())) ? pw->pw_name : "???";
		(void)gethostname(hostname, sizeof(hostname));
		(void)time(&now);
		lt = localtime(&now);
E 20

D 20
	/*
D 19
	 * all this stuff is to blank out a square for the message; we
D 16
	 * limit message lines to 75 characters, and blank out to 79.
	 * Not 80 'cause some terminals do weird stuff then.
E 16
I 16
	 * wrap message lines at column 79, not 80, because some terminals
	 * wrap after 79, some do not, and we can't tell.
E 19
I 19
	 * all this stuff is to blank out a square for the message; we wrap
	 * message lines at column 79, not 80, because some terminals wrap
	 * after 79, some do not, and we can't tell.  Which means that we
	 * may leave a non-blank character in column 80, but that can't be
	 * helped.
E 19
E 16
	 */
D 19
	fprintf(fp, "\r%79s\r\n", " ");
E 19
I 19
	(void)fprintf(fp, "\r%79s\r\n", " ");
E 19
	(void)sprintf(lbuf, "Broadcast Message from %s@%s", whom, hostname);
D 19
	fprintf(fp, "%-79.79s\007\007\r\n", lbuf);
E 19
I 19
	(void)fprintf(fp, "%-79.79s\007\007\r\n", lbuf);
E 19
	(void)sprintf(lbuf, "        (%s) at %d:%02d ...", ttyname(2),
	    lt->tm_hour, lt->tm_min);
D 19
	fprintf(fp, "%-79.79s\r\n", lbuf);
	fprintf(fp, "%79s\r\n", " ");
E 19
I 19
	(void)fprintf(fp, "%-79.79s\r\n", lbuf);
E 20
I 20
		/*
		 * all this stuff is to blank out a square for the message;
		 * we wrap message lines at column 79, not 80, because some
		 * terminals wrap after 79, some do not, and we can't tell.
		 * Which means that we may leave a non-blank character
		 * in column 80, but that can't be helped.
		 */
		(void)fprintf(fp, "\r%79s\r\n", " ");
		(void)sprintf(lbuf, "Broadcast Message from %s@%s",
		    whom, hostname);
		(void)fprintf(fp, "%-79.79s\007\007\r\n", lbuf);
		(void)sprintf(lbuf, "        (%s) at %d:%02d ...", ttyname(2),
		    lt->tm_hour, lt->tm_min);
		(void)fprintf(fp, "%-79.79s\r\n", lbuf);
	}
E 20
	(void)fprintf(fp, "%79s\r\n", " ");
E 19

D 19
	if (*++argv && !(freopen(*argv, "r", stdin))) {
		fprintf(stderr, "wall: can't read %s.\n", *argv);
E 19
I 19
D 25
	if (*fname && !(freopen(fname, "r", stdin))) {
E 25
I 25
	if (fname && !(freopen(fname, "r", stdin))) {
E 25
		(void)fprintf(stderr, "wall: can't read %s.\n", fname);
E 19
		exit(1);
E 14
	}
D 14
	if ((flags = fcntl(f, F_GETFL, 0)) == -1) {
		perror(t);
		return;
E 14
I 14
	while (fgets(lbuf, sizeof(lbuf), stdin))
D 16
		for (cnt = 0, p = lbuf; ch = *p; ++p, ++cnt)
			if (cnt == 75 || ch == '\n') {
				for (; cnt < 79; ++cnt)
					putc(' ', fp);
E 16
I 16
D 27
		for (cnt = 0, p = lbuf; ch = *p; ++p, ++cnt) {
E 27
I 27
		for (cnt = 0, p = lbuf; (ch = *p) != '\0'; ++p, ++cnt) {
E 27
			if (cnt == 79 || ch == '\n') {
I 19
				for (; cnt < 79; ++cnt)
					putc(' ', fp);
E 19
E 16
				putc('\r', fp);
				putc('\n', fp);
D 16
				cnt = 1;
E 16
I 16
				cnt = 0;
E 16
			} else
				putc(ch, fp);
I 16
		}
E 16
D 19
	fprintf(fp, "%79s\r\n", " ");
E 19
I 19
	(void)fprintf(fp, "%79s\r\n", " ");
E 19
	rewind(fp);

	if (fstat(fd, &sbuf)) {
D 19
		fprintf(stderr, "wall: can't stat temporary file.\n");
E 19
I 19
		(void)fprintf(stderr, "wall: can't stat temporary file.\n");
E 19
		exit(1);
E 14
	}
D 14
	if (fcntl(f, F_SETFL, flags | FNDELAY) == -1)
		goto oldway;
	i = write(f, mesg, msize);
	e = errno;
	(void) fcntl(f, F_SETFL, flags);
	if (i == msize) {
		(void) close(f);
		return;
E 14
I 14
	mbufsize = sbuf.st_size;
	if (!(mbuf = malloc((u_int)mbufsize))) {
D 19
		fprintf(stderr, "wall: out of memory.\n");
E 19
I 19
		(void)fprintf(stderr, "wall: out of memory.\n");
E 19
		exit(1);
E 14
	}
D 14
	if (e != EWOULDBLOCK) {
		errno = e;
		perror(t);
		(void) close(f);
		return;
E 14
I 14
D 15
	(void)fread(mbuf, sizeof(*mbuf), mbufsize, fp);
E 15
I 15
	if (fread(mbuf, sizeof(*mbuf), mbufsize, fp) != mbufsize) {
D 19
		fprintf(stderr, "wall: can't read temporary file.\n");
E 19
I 19
		(void)fprintf(stderr, "wall: can't read temporary file.\n");
E 19
		exit(1);
D 19
	}
E 15
	(void)close(fd);
}

D 16
sendmsg(line)
E 16
I 16
sendmsg(line, nonblock, left)
E 16
	char *line;
{
	extern int errno;
D 16
	static char device[MAXNAMLEN] = "/dev/";
D 15
	register int fd, flags, nread;
E 15
I 15
	register int fd, flags, left, wret;
E 15
	char *lp, *strcpy();
E 16
I 16
	static char device[MAXNAMLEN] = _PATH_DEV;
	register int fd, wret;
	char *lp, *strcpy(), *strerror();
E 16

	(void)strcpy(device + 5, line);
D 16
	if ((fd = open(device, O_WRONLY, 0)) < 0) {
		fprintf(stderr, "wall: %s: ", device);
		perror((char *)NULL);
E 16
I 16
	/*
	 * open will fail on slip lines or exclusive-use lines
	 * if not running as root
	 */
	if ((fd = open(device, O_WRONLY|(nonblock ? O_NONBLOCK : 0), 0)) < 0) {
		if (errno != EBUSY && errno != EPERM)
			(void)fprintf(stderr, "wall: %s: %s\n",
			    device, strerror(errno));
		return;
E 16
E 14
	}
D 14
oldway:
E 8
I 2
D 6
/***			you can't do this with lots of users & MAXUPROC
E 2
	i = fork();
	if(i == -1) {
		fprintf(stderr, "Try again\n");
		return;
	}
I 2
 ***/
E 6
	while ((i = fork()) == -1)
		if (wait((int *)0) == -1) {
			fprintf(stderr, "Try again\n");
			return;
E 14
I 14
D 16
	flags = fcntl(fd, F_GETFL, 0);
	if (!(flags & FNDELAY)) {
		/* NDELAY bit not set; if can't set, fork instead */
		if (fcntl(fd, F_SETFL, flags|FNDELAY) == -1) {
			flags = 0;
			goto forkit;
E 14
		}
E 2
D 8
	if(i)
E 8
I 8
D 14
	if (i) {
		(void) close(f);
E 8
		return;
E 14
D 8
	strcpy(t, "/dev/");
	strcat(t, tty);

I 2
	signal(SIGALRM, SIG_DFL);	/* blow away if open hangs */
	alarm(10);

E 2
	if((f = fopen(t, "w")) == NULL) {
		fprintf(stderr,"cannot open %s\n", t);
		exit(1);
E 8
	}
D 8
	setbuf(f, buf);
D 2
	fprintf(f, "\nBroadcast Message from %s (%s) at %d:%02d ...\r\n\n"
	       ,who, utmp[sline].ut_line
	       , localclock -> tm_hour , localclock -> tm_min );
E 2
I 2
	fprintf(f,
	    "\nBroadcast Message from %s!%s (%.*s) at %d:%02d ...\r\n\n"
D 6
		, sysname
E 6
I 6
		, hostname
E 6
		, who
		, sizeof(utmp[sline].ut_line)
		, utmp[sline].ut_line
		, localclock -> tm_hour
		, localclock -> tm_min
	);
E 2
	/* fwrite(mesg, msize, 1, f); */
	for (cp = mesg, c = msize; c-- > 0; cp++) {
		ch = *cp;
		if (ch == '\n')
			putc('\r', f);
		putc(ch, f);
	}
E 8
D 14

D 8
	/*
	 * Bitchin'.
	 */

E 8
I 8
	(void) write(f, mesg, msize);
E 8
	exit(0);
E 14
I 14
	else
		flags = 0;
	lp = mbuf;
D 15
	while ((nread = write(fd, lp, mbufsize)) != mbufsize) {
		if (mbufsize > 0) {
			mbufsize -= nread;
			lp += nread;
E 15
I 15
	left = mbufsize;
	while ((wret = write(fd, lp, left)) != left) {
E 16
I 16
	lp = mbuf + mbufsize - left;
	while (left) {
		wret = write(fd, lp, left);
E 16
		if (wret >= 0) {
			lp += wret;
			left -= wret;
E 15
D 16
		} else if (errno == EWOULDBLOCK) {
			/* child resets FNDELAY if necessary; parent leaves */
forkit:			if (fork()) {
E 16
I 16
		} else
		if (errno == EWOULDBLOCK) {
			if (fork()) {
E 16
				(void)close(fd);
				return;
			}
D 16
			if (flags)
				(void)fcntl(fd, F_SETFL, flags);
			/* wait 5 minutes and then quit */
E 16
I 16
			/* wait at most 5 minutes */
E 16
			(void)alarm((u_int)(60 * 5));
D 16
			(void)write(fd, mbuf, mbufsize);
E 16
I 16
			sendmsg(line, 0, left);
E 16
			exit(0);
D 16
		} else {
			fprintf(stderr, "wall: %s: ", device);
			perror((char *)NULL);
E 16
I 16
D 18
		} else if (errno != ENODEV) {
E 18
I 18
		} else {
E 18
			/*
			 * We get ENODEV on a slip line
			 * if we're running as root
			 */
D 18
			(void)fprintf(stderr, "wall: %s: %s\n",
			    device, strerror(errno));
E 18
I 18
			if (errno != ENODEV)
				(void)fprintf(stderr, "wall: %s: %s\n",
				    device, strerror(errno));
E 18
E 16
			break;
		}
E 19
	}
D 16
	/* write was successful, or error != EWOULDBLOCK; cleanup */
	if (flags)
		(void)fcntl(fd, F_SETFL, flags);
E 16
	(void)close(fd);
E 14
}
E 1
