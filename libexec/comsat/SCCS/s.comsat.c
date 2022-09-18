h03161
s 00005/00005/00253
d D 8.1 93/06/04 18:47:44 bostic 44 43
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00256
d D 5.27 93/05/17 10:07:06 bostic 43 42
c index -> strchr
e
s 00030/00016/00228
d D 5.26 92/11/13 11:34:43 bostic 42 41
c Must eat packet if _PATH_MAILDIR doesn't exist to avoid looping from
c inetd. Open file as user in case _PATH_MAILDIR is an nfs filesystem.
c Close mail drop when we're done.  Don't allow '/' in ut_line (security fix).
c Other minor lint; from Craig Leres
e
s 00029/00024/00215
d D 5.25 92/06/22 11:48:48 bostic 41 40
c lseek takes a quad, now; lots of ANSI style cleanups
e
s 00002/00002/00237
d D 5.24 91/02/25 16:25:15 bostic 40 39
c ANSI fixes
e
s 00000/00001/00239
d D 5.23 91/02/03 00:11:48 torek 39 38
c fseek is correctly declared in <stdio.h>; do not re-declare it,
c and especially not incorrectly.
e
s 00002/00002/00238
d D 5.22 90/06/24 23:30:50 bostic 38 37
c forgot to change the _PATH lines.
e
s 00002/00006/00238
d D 5.21 90/06/24 23:30:09 bostic 37 36
c move _PATH_MAILDIR into <paths.h>
e
s 00001/00011/00243
d D 5.20 90/06/01 15:50:24 bostic 36 35
c new copyright notice
e
s 00001/00001/00253
d D 5.19 90/05/15 19:50:05 bostic 35 34
c string.h is ANSI C include file
e
s 00003/00003/00251
d D 5.18 90/05/10 17:27:18 leres 34 33
c Minor tweaks; delete unused atol() definition. Also, might as well use
c toascii() macro since we already include ctype.h.
e
s 00010/00009/00244
d D 5.17 90/05/10 14:31:52 bostic 33 32
c minor cleanup, don't have hardcoded length
e
s 00027/00017/00226
d D 5.16 90/05/09 16:49:16 bostic 32 31
c don't pass magic characters to the terminal; minor lint fixes
e
s 00001/00001/00242
d D 5.15 89/05/11 14:32:14 bostic 31 30
c file reorg, pathnames.h, paths.h
e
s 00006/00004/00237
d D 5.14 89/04/02 12:13:04 bostic 30 29
c add pathnames.h
e
s 00005/00004/00236
d D 5.13 88/08/23 10:20:51 mckusick 29 28
c do not say ...more... when there is no more (4.3BSD/etc/146)
e
s 00010/00005/00230
d D 5.12 88/06/18 14:34:08 bostic 28 27
c install approved copyright notice
e
s 00005/00005/00230
d D 5.11 88/03/29 10:14:41 bostic 27 26
c 2.10BSD long/int problems
e
s 00001/00001/00234
d D 5.10 87/12/26 12:24:43 bostic 26 25
c wait is a union, not a struct; fix for ANSI C
e
s 00010/00004/00225
d D 5.9 87/12/04 11:44:21 bostic 25 24
c add Berkeley specific header
e
s 00020/00030/00209
d D 5.8 87/11/19 15:00:20 bostic 24 22
c minor cleanups, particularly in reading mail header
e
s 00013/00013/00226
d R 5.8 87/11/18 15:15:17 bostic 23 22
c minor cleanups
e
s 00089/00101/00150
d D 5.7 87/11/18 11:22:05 bostic 22 21
c if utmp empty drops core; bug report 4.3BSD/etc/98; 
c make lint happy; redo header reading logic completely
e
s 00014/00014/00237
d D 5.6 87/08/06 15:33:22 marc 21 20
c changed debug printf's to use syslog(LOG_DEBUG,...)
e
s 00002/00002/00249
d D 5.5 85/10/24 09:33:20 bloom 20 19
c watch for hostname overflow in printf
e
s 00001/00001/00250
d D 5.4 85/09/17 19:12:35 eric 19 18
c facilities in syslog
e
s 00001/00001/00250
d D 5.3 85/09/04 11:41:45 bloom 18 17
c check raw mode to see if cr-nl is needed (from serge@arpa)
e
s 00001/00001/00250
d D 5.2 85/06/06 22:19:49 bloom 17 16
c should use sigmask
e
s 00014/00002/00237
d D 5.1 85/06/06 14:20:49 dist 16 15
c Add copyright
e
s 00016/00006/00223
d D 4.14 85/06/06 13:56:04 bloom 15 14
c dynamically configure utmp size
e
s 00020/00044/00209
d D 4.13 84/09/13 12:00:07 ralph 14 13
c undo nonblocking I/O changes
e
s 00050/00024/00203
d D 4.12 84/08/01 12:17:01 ralph 13 12
c use non-blocking I/O, use syslog.
e
s 00022/00014/00205
d D 4.11 84/06/09 14:38:15 sam 12 11
c only fork if biff is on; do gethostname once rather than once per 
c notify; collect children off SIGCHLD
e
s 00027/00029/00192
d D 4.10 84/04/11 15:57:58 karels 11 9
c convert for use with inetd
e
s 00027/00029/00192
d R 4.10 84/04/11 15:37:17 karels 10 9
c convert for inetd
e
s 00017/00009/00204
d D 4.9 83/07/04 19:15:33 sam 9 8
c filter headers properly (kre)
e
s 00002/00002/00211
d D 4.8 83/07/01 03:12:02 sam 8 7
c include fixes
e
s 00003/00003/00210
d D 4.7 83/06/12 01:39:48 sam 7 6
c new signals
e
s 00033/00032/00180
d D 4.6 83/05/27 12:43:54 sam 6 5
c print user@hostname; filter header lines
e
s 00001/00004/00211
d D 4.5 82/12/23 13:13:13 sam 5 4
c port numbers now byte swapped
e
s 00024/00008/00191
d D 4.4 82/11/17 16:30:44 sam 4 3
c convert to 4.1c sys calls and netdb.h
e
s 00030/00086/00169
d D 4.3 82/03/31 11:44:16 root 3 2
c datagram version
e
s 00002/00000/00253
d D 4.2 80/10/20 11:28:58 bill 2 1
c _exit if error reading mpx, sleep 10 before start to prevent thrash
e
s 00253/00000/00000
d D 4.1 80/10/18 10:39:50 root 1 0
c date and time created 80/10/18 10:39:50 by root
e
u
U
t
T
I 16
/*
D 44
 * Copyright (c) 1980 Regents of the University of California.
D 25
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 25
I 25
 * All rights reserved.
E 44
I 44
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 44
 *
D 36
 * Redistribution and use in source and binary forms are permitted
D 28
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 28
I 28
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
E 36
I 36
 * %sccs.include.redist.c%
E 36
E 28
E 25
 */

E 16
I 4
#ifndef lint
E 4
I 1
D 3
static	char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
D 11
static	char *sccsid = "%W% %E%";
E 11
I 11
D 16
static	char sccsid[] = "%W% (Berkeley) %G%";
E 11
I 4
#endif
E 16
I 16
D 44
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
E 44
I 44
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 44
D 22
#endif not lint
E 22
I 22
D 25
#endif /* !lint */
E 25
I 25
#endif /* not lint */
E 25
E 22

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 22
#endif not lint
E 22
I 22
D 25
#endif /* !lint */
E 25
I 25
#endif /* not lint */
E 25
E 22
E 16
E 4

I 4
D 22
#include <sys/types.h>
E 22
I 22
#include <sys/param.h>
E 22
#include <sys/socket.h>
I 8
#include <sys/stat.h>
D 22
#include <sys/wait.h>
E 22
I 12
#include <sys/file.h>
I 22
#include <sys/wait.h>
E 22
E 12
E 8

#include <netinet/in.h>

E 4
E 3
D 41
#include <stdio.h>
E 41
I 41
D 42
#include <signal.h>
E 41
D 3
#include <sys/mx.h>
E 3
#include <sgtty.h>
#include <utmp.h>
E 42
I 42
#include <ctype.h>
E 42
D 4
#include <sys/types.h>
I 3
#include <net/in.h>
#include <sys/socket.h>
E 4
E 3
D 8
#include <stat.h>
#include <wait.h>
E 8
D 41
#include <signal.h>
E 41
I 3
#include <errno.h>
I 4
#include <netdb.h>
I 13
D 42
#include <syslog.h>
E 42
I 42
#include <paths.h>
#include <pwd.h>
#include <sgtty.h>
#include <signal.h>
E 42
I 41
#include <stdio.h>
D 42
#include <unistd.h>
E 42
#include <stdlib.h>
E 41
I 22
D 35
#include <strings.h>
E 35
I 35
D 37
#include <string.h>
E 37
E 35
I 32
D 42
#include <ctype.h>
E 42
I 37
#include <string.h>
D 42
#include <paths.h>
E 42
I 42
#include <syslog.h>
#include <unistd.h>
#include <utmp.h>
E 42
E 37
E 32
E 22
E 13
E 4
E 3

I 30
D 37
#include "pathnames.h"

E 30
/*
 * comsat
 */
E 37
D 6
#define	dprintf	if (0) printf
E 6
I 6
int	debug = 0;
D 21
#define	dprintf	if (debug) printf
E 21
I 21
D 22
#define	dsyslog     if (debug) syslog
E 22
I 22
#define	dsyslog	if (debug) syslog
E 22
E 21
E 6
D 3
int	xd;
E 3

D 3
struct  ctp {
	short   ctrl;
	short   ctrlarg;
	struct  sgttyb ctrlv;
} ctp;

E 3
D 15
#define MAXUTMP 100		/* down from init */

E 15
I 3
D 5
struct	sockaddr_in sin = { AF_INET, IPPORT_BIFFUDP };
E 5
I 5
D 22
struct	sockaddr_in sin = { AF_INET };
E 5
extern	errno;
E 22
I 22
#define MAXIDLE	120
E 22

I 12
D 22
char	hostname[32];
E 22
I 22
char	hostname[MAXHOSTNAMELEN];
E 22
E 12
E 3
D 15
struct	utmp utmp[100];
E 15
I 15
struct	utmp *utmp = NULL;
E 15
D 22
int	nutmp;
int	uf;
D 15
unsigned utmpmtime;			/* last modification time for utmp */
E 15
I 15
unsigned utmpmtime = 0;			/* last modification time for utmp */
unsigned utmpsize = 0;			/* last malloced size for utmp */
E 15
int	onalrm();
I 12
int	reapchildren();
E 12
I 4
D 11
struct	servent *sp;
E 11
I 11
long	lastmsgtime;
I 15
char 	*malloc(), *realloc();
E 22
I 22
D 41
time_t	lastmsgtime, time();
E 41
I 41
time_t	lastmsgtime;
E 41
int	nutmp, uf;
E 22
E 15
E 11
E 4

I 32
D 41
/* ARGSUSED */
E 41
I 41
void jkfprintf __P((FILE *, char[], off_t));
void mailfor __P((char *));
void notify __P((struct utmp *, off_t));
void onalrm __P((int));
void reapchildren __P((int));

int
E 41
E 32
I 11
D 22
#define	MAXIDLE	120
E 11
#define NAMLEN (sizeof (uts[0].ut_name) + 1)

E 22
main(argc, argv)
D 11
char **argv;
E 11
I 11
	int argc;
D 22
	char *argv[];
E 22
I 22
D 41
	char **argv;
E 41
I 41
	char *argv[];
E 41
E 22
E 11
{
I 22
D 41
	extern int errno;
E 22
D 11
	register cc;
E 11
I 11
	register int cc;
E 11
D 22
	char buf[BUFSIZ];
E 22
I 3
D 11
	int s;
E 11
I 11
	char msgbuf[100];
E 41
	struct sockaddr_in from;
I 41
	register int cc;
E 41
D 22
	int fromlen;
E 22
I 22
D 32
	int fromlen, reapchildren(), onalrm();
E 32
I 32
	int fromlen;
D 41
	void onalrm(), reapchildren();
E 41
I 41
	char msgbuf[100];
E 41
E 32
E 22
E 11
E 3

I 4
D 11
	sp = getservbyname("biff", "udp");
	if (sp == 0) {
		fprintf(stderr, "comsat: biff/udp: unknown service\n");
		exit(1);
E 11
I 11
	/* verify proper invocation */
D 32
	fromlen = sizeof (from);
E 32
I 32
	fromlen = sizeof(from);
E 32
D 40
	if (getsockname(0, &from, &fromlen) < 0) {
E 40
I 40
	if (getsockname(0, (struct sockaddr *)&from, &fromlen) < 0) {
E 40
D 32
		fprintf(stderr, "%s: ", argv[0]);
		perror("getsockname");
E 32
I 32
		(void)fprintf(stderr,
		    "comsat: getsockname: %s.\n", strerror(errno));
E 32
D 24
		_exit(1);
E 24
I 24
		exit(1);
E 24
E 11
	}
I 21
	openlog("comsat", LOG_PID, LOG_DAEMON);
E 21
E 4
I 3
D 6
#ifndef DEBUG
E 6
I 6
D 11
	if (!debug)
E 6
E 3
	if (fork())
		exit();
E 11
I 3
D 6
#endif
E 6
E 3
D 22
	chdir("/usr/spool/mail");
D 11
	if((uf = open("/etc/utmp",0)) < 0)
		perror("/etc/utmp"), exit(1);
I 3
D 6
#ifndef DEBUG
E 6
I 6
D 9
	if (!debug)
E 6
E 3
	while (fork())
		wait(0);
E 9
I 3
D 6
#endif
E 6
E 3
I 2
	sleep(10);
E 11
I 11
	if ((uf = open("/etc/utmp",0)) < 0) {
E 22
I 22
D 30
	if (chdir("/usr/spool/mail")) {
		syslog(LOG_ERR, "chdir: /usr/spool/mail");
E 30
I 30
D 38
	if (chdir(_PATH_MAIL)) {
		syslog(LOG_ERR, "chdir: %s: %m", _PATH_MAIL);
E 38
I 38
	if (chdir(_PATH_MAILDIR)) {
		syslog(LOG_ERR, "chdir: %s: %m", _PATH_MAILDIR);
I 42
		(void) recv(0, msgbuf, sizeof(msgbuf) - 1, 0);
E 42
E 38
E 30
		exit(1);
	}
D 30
	if ((uf = open("/etc/utmp", O_RDONLY, 0)) < 0) {
E 22
D 13
		perror("/etc/utmp");
E 13
I 13
D 19
		openlog("comsat", 0, 0);
E 19
I 19
D 21
		openlog("comsat", 0, LOG_DAEMON);
E 19
		syslog(LOG_ERR, "/etc/utmp: %m");
E 21
I 21
		syslog(LOG_ERR, ".main: /etc/utmp: %m");
E 30
I 30
	if ((uf = open(_PATH_UTMP, O_RDONLY, 0)) < 0) {
D 42
		syslog(LOG_ERR, ".main: %s: %m", _PATH_UTMP);
E 42
I 42
		syslog(LOG_ERR, "open: %s: %m", _PATH_UTMP);
E 42
E 30
E 21
E 13
D 33
		(void) recv(0, msgbuf, sizeof (msgbuf) - 1, 0);
E 33
I 33
		(void) recv(0, msgbuf, sizeof(msgbuf) - 1, 0);
E 33
		exit(1);
	}
D 22
	lastmsgtime = time(0);
I 12
	gethostname(hostname, sizeof (hostname));
E 22
I 22
	(void)time(&lastmsgtime);
D 33
	(void)gethostname(hostname, sizeof (hostname));
E 33
I 33
	(void)gethostname(hostname, sizeof(hostname));
E 33
E 22
E 12
E 11
E 2
D 41
	onalrm();
E 41
I 41
	onalrm(0);
E 41
D 7
	sigset(SIGALRM, onalrm);
	sigignore(SIGTTOU);
E 7
I 7
D 22
	signal(SIGALRM, onalrm);
	signal(SIGTTOU, SIG_IGN);
I 12
	signal(SIGCHLD, reapchildren);
E 22
I 22
	(void)signal(SIGALRM, onalrm);
	(void)signal(SIGTTOU, SIG_IGN);
	(void)signal(SIGCHLD, reapchildren);
E 22
E 12
E 7
D 3
	unlink("/dev/mail");
	xd = mpx("/dev/mail", 0666);
	if (xd < 0) {
		close(2);
		open("/dev/console", 1);
		perror("/dev/mail");
E 3
I 3
D 4
#if vax
	sin.sin_port = ((sin.sin_port<<8)&0xff00)|((sin.sin_port>>8)&0xff);
#endif
	s = socket(SOCK_DGRAM, 0, &sin, 0);
E 4
I 4
D 11
	s = socket(AF_INET, SOCK_DGRAM, 0, 0);
E 4
	if (s < 0) {
		perror("socket");
E 3
		exit(1);
	}
I 4
D 5
#if vax || pdp11
	sp->s_port = htons((u_short)sp->s_port);
#endif
E 5
	sin.sin_port = sp->s_port;
	if (bind(s, &sin, sizeof (sin), 0) < 0) {
		perror("bind");
		exit(1);
	}
E 11
E 4
D 3
	while((cc=read(xd, buf, BUFSIZ)) >= 0) {
		dprintf("0: got %d bytes\n", cc);
		unpack(buf, cc);
	}
I 2
	_exit(1);
E 2
}
E 3
I 3
	for (;;) {
D 11
		char msgbuf[100];
		int cc;
E 3

D 3
#define	skip(rp, c)	((struct rh *)(((char *)rp)+c))

unpack(rp, cc)
	register struct rh *rp;
{
	register struct rh *end;
	int i;

	i = 0;
	end = skip(rp, cc);
	while (rp < end) {
		dprintf("%d: ", ++i);
		if (rp->count==0) {
			dprintf("%d byte control message\n", rp->ccount);
			control(rp->index, rp+1, rp->ccount);
		} else {
			dprintf("%*.*s\n", rp->count, rp->count, rp+1);
			sighold(SIGALRM);
			mailfor(rp+1);
			sigrelse(SIGALRM);
E 3
I 3
D 4
		cc = receive(s, 0, msgbuf, sizeof (msgbuf) - 1);
E 4
I 4
		cc = recv(s, msgbuf, sizeof (msgbuf) - 1, 0);
E 11
I 11
D 33
		cc = recv(0, msgbuf, sizeof (msgbuf) - 1, 0);
E 33
I 33
		cc = recv(0, msgbuf, sizeof(msgbuf) - 1, 0);
E 33
E 11
E 4
		if (cc <= 0) {
			if (errno != EINTR)
				sleep(1);
			errno = 0;
			continue;
E 3
		}
I 22
		if (!nutmp)		/* no one has logged in yet */
			continue;
E 22
I 11
D 17
		sigblock(1<<SIGALRM);
E 17
I 17
		sigblock(sigmask(SIGALRM));
E 17
E 11
D 3
		rp->count += rp->ccount;
		if (rp->count & 1)
			rp->count++;
		rp = skip(rp, rp->count);
		rp++;
	}
}

control(x, cb, cc)
	register char *cb;
{
	register char *end;
	int cmd;
	short *sp;
	struct wh or;

	end = cb + cc;
	cmd = *cb++;
	sp = (short *)cb+1;
	switch (cmd) {

	case M_WATCH:
		dprintf("attach %x, uid %d\n", x, *sp);
		attach(x, xd);
		break;

	case M_CLOSE:
		sp = (short *)cb;
		dprintf("detach %x, uid %d\n", x, *sp);
		detach(x, xd);
		break;

	case M_IOCTL:
		dprintf("ioctl %x\n", x);
		or.index = x;
		or.count = 0;
		or.ccount = sizeof ctp;
		or.data = (char *) &ctp.ctrlarg;
		ctp.ctrlarg = M_IOANS;
		write(xd, &or, sizeof or);
		break;
		
	default:
		dprintf("unknown command %d\n", cmd);
		return;
E 3
I 3
D 42
		msgbuf[cc] = 0;
E 42
I 42
		msgbuf[cc] = '\0';
E 42
I 11
D 22
		lastmsgtime = time(0);
E 22
I 22
		(void)time(&lastmsgtime);
E 22
E 11
		mailfor(msgbuf);
I 11
D 22
		sigsetmask(0);
E 22
I 22
		sigsetmask(0L);
E 22
E 11
E 3
	}
}

I 32
void
E 32
I 12
D 41
reapchildren()
E 41
I 41
reapchildren(signo)
	int signo;
E 41
{
D 22

	while (wait3((struct wait *)0, WNOHANG, (struct rusage *)0) > 0)
		;
E 22
I 22
D 26
	while (wait3((struct wait *)NULL, WNOHANG, (struct rusage *)NULL) > 0);
E 26
I 26
D 40
	while (wait3((union wait *)NULL, WNOHANG, (struct rusage *)NULL) > 0);
E 40
I 40
D 41
	while (wait3((int *)NULL, WNOHANG, (struct rusage *)NULL) > 0);
E 41
I 41
	while (wait3(NULL, WNOHANG, NULL) > 0);
E 41
E 40
E 26
E 22
}

I 32
void
E 32
E 12
D 41
onalrm()
E 41
I 41
onalrm(signo)
	int signo;
E 41
{
I 22
	static u_int utmpsize;		/* last malloced size for utmp */
	static u_int utmpmtime;		/* last modification time for utmp */
E 22
	struct stat statbf;
I 22
D 41
	off_t lseek();
	char *malloc(), *realloc();
E 41
E 22
D 15
	struct utmp *utp;
E 15

I 11
D 22
	if (time(0) - lastmsgtime >= MAXIDLE)
E 22
I 22
D 41
	if (time((time_t *)NULL) - lastmsgtime >= MAXIDLE)
E 41
I 41
	if (time(NULL) - lastmsgtime >= MAXIDLE)
E 41
E 22
D 13
		exit(1);
E 13
I 13
		exit(0);
E 13
E 11
D 21
	dprintf("alarm\n");
E 21
I 21
D 22
	dsyslog(LOG_DEBUG,".onalrm: alarm");
E 21
	alarm(15);
D 13
	fstat(uf,&statbf);
E 13
I 13
	fstat(uf, &statbf);
E 22
I 22
D 24
	dsyslog(LOG_DEBUG, ".onalrm: alarm");
E 24
	(void)alarm((u_int)15);
	(void)fstat(uf, &statbf);
E 22
E 13
	if (statbf.st_mtime > utmpmtime) {
D 21
		dprintf(" changed\n");
E 21
I 21
D 22
		dsyslog(LOG_DEBUG,".onalrm: changed\n");
E 22
I 22
D 24
		dsyslog(LOG_DEBUG, ".onalrm: changed\n");
E 24
E 22
E 21
		utmpmtime = statbf.st_mtime;
I 15
		if (statbf.st_size > utmpsize) {
			utmpsize = statbf.st_size + 10 * sizeof(struct utmp);
D 41
			if (utmp)
D 22
				utmp = (struct utmp *)realloc(utmp, utmpsize);
E 22
I 22
				utmp = (struct utmp *)realloc((char *)utmp, utmpsize);
E 22
			else
				utmp = (struct utmp *)malloc(utmpsize);
D 22
			if (! utmp) {
D 21
				dprintf("malloc failed\n");
E 21
I 21
				dsyslog(LOG_DEBUG,".onalrm: malloc failed");
E 22
I 22
			if (!utmp) {
D 24
				dsyslog(LOG_DEBUG, ".onalrm: malloc failed");
E 24
I 24
				syslog(LOG_ERR, "malloc failed");
E 41
I 41
			if ((utmp = realloc(utmp, utmpsize)) == NULL) {
				syslog(LOG_ERR, "%s", strerror(errno));
E 41
E 24
E 22
E 21
				exit(1);
			}
		}
E 15
D 22
		lseek(uf, 0, 0);
D 15
		nutmp = read(uf,utmp,sizeof(utmp))/sizeof(struct utmp);
E 15
I 15
		nutmp = read(uf,utmp,statbf.st_size)/sizeof(struct utmp);
E 15
	} else
E 22
I 22
D 41
		(void)lseek(uf, 0L, L_SET);
E 41
I 41
		(void)lseek(uf, (off_t)0, L_SET);
E 41
D 27
		nutmp = read(uf, utmp, statbf.st_size)/sizeof(struct utmp);
E 27
I 27
		nutmp = read(uf, utmp, (int)statbf.st_size)/sizeof(struct utmp);
E 27
	}
D 24
	else
E 22
D 21
		dprintf(" ok\n");
E 21
I 21
		dsyslog(LOG_DEBUG, ".onalrm: ok\n");
E 24
E 21
}

I 41
void
E 41
mailfor(name)
	char *name;
{
	register struct utmp *utp = &utmp[nutmp];
	register char *cp;
D 22
	char *rindex();
E 22
D 27
	int offset;
E 27
I 27
D 34
	off_t offset, atol();
E 34
I 34
	off_t offset;
E 34
E 27

D 21
	dprintf("mailfor %s\n", name);
E 21
I 21
D 22
	dsyslog(LOG_DEBUG,".mailfor: mailfor %s\n", name);
E 21
	cp = name;
	while (*cp && *cp != '@')
		cp++;
	if (*cp == 0) {
D 21
		dprintf("bad format\n");
E 21
I 21
		dsyslog(LOG_DEBUG,".mailfor: bad format\n");
E 22
I 22
D 24
	dsyslog(LOG_DEBUG, ".mailfor: mailfor %s\n", name);
	if (!(cp = index(name, '@'))) {
		dsyslog(LOG_DEBUG, ".mailfor: bad format\n");
E 24
I 24
D 43
	if (!(cp = index(name, '@')))
E 43
I 43
	if (!(cp = strchr(name, '@')))
E 43
E 24
E 22
E 21
		return;
D 24
	}
E 24
D 22
	*cp = 0;
	offset = atoi(cp+1);
E 22
I 22
	*cp = '\0';
	offset = atoi(cp + 1);
E 22
	while (--utp >= utmp)
		if (!strncmp(utp->ut_name, name, sizeof(utmp[0].ut_name)))
D 12
			if (fork() == 0) {
				signal(SIGALRM, SIG_DFL);
				alarm(30);
				notify(utp, offset), exit(0);
			} else
				while (wait3(0, WNOHANG, 0) > 0)
					continue;
E 12
I 12
			notify(utp, offset);
E 12
}

D 13
char *cr;
E 13
I 13
D 22
char	*cr;
E 22
I 22
D 32
static char	*cr;
E 32
I 32
static char *cr;
E 32
E 22
E 13

I 41
void
E 41
notify(utp, offset)
	register struct utmp *utp;
I 22
D 27
	int offset;
E 27
I 27
	off_t offset;
E 27
E 22
{
D 13
	FILE *tp;
E 13
I 13
D 14
	int fd, flags, n, err, msglen;
E 14
I 14
D 24
	FILE *tp;
E 24
I 24
D 31
	static char tty[20] = "/dev/";
E 31
I 31
D 42
	static char tty[20] = _PATH_DEV;
E 31
E 24
E 14
E 13
	struct sgttyb gttybuf;
D 6
	char tty[20];
E 6
I 6
D 12
	char tty[20], hostname[32];
E 6
	char name[sizeof (utmp[0].ut_name) + 1];
E 12
I 12
D 13
	char tty[20], name[sizeof (utmp[0].ut_name) + 1];
E 13
I 13
D 14
	char tty[20], msgbuf[BUFSIZ];
	char name[sizeof (utmp[0].ut_name) + 1];
E 14
I 14
D 24
	char tty[20], name[sizeof (utmp[0].ut_name) + 1];
E 24
I 24
D 33
	FILE *tp;
	char name[sizeof (utmp[0].ut_name) + 1];
E 33
E 24
E 14
E 13
E 12
	struct stat stb;
E 42
I 33
	FILE *tp;
D 42
	char name[sizeof(utmp[0].ut_name) + 1];
E 42
I 42
	struct stat stb;
	struct sgttyb gttybuf;
	char tty[20], name[sizeof(utmp[0].ut_name) + 1];
E 42
E 33

D 22
	strcpy(tty, "/dev/");
	strncat(tty, utp->ut_line, sizeof(utp->ut_line));
D 21
	dprintf("notify %s on %s\n", utp->ut_name, tty);
E 21
I 21
	dsyslog(LOG_DEBUG,".notify: notify %s on %s\n", utp->ut_name, tty);
E 21
	if (stat(tty, &stb) == 0 && (stb.st_mode & 0100) == 0) {
D 21
		dprintf("wrong mode\n");
E 21
I 21
		dsyslog(LOG_DEBUG,".notify: wrong mode on tty");
E 22
I 22
D 24
	(void)strcpy(tty, "/dev/");
E 24
D 33
	(void)strncpy(tty + 5, utp->ut_line, sizeof(utp->ut_line));
E 33
I 33
D 42
	(void)strncpy(tty + sizeof(_PATH_DEV) - 1, utp->ut_line,
	    sizeof(utp->ut_line));
E 42
I 42
	(void)snprintf(tty, sizeof(tty), "%s%.*s",
	    _PATH_DEV, (int)sizeof(utp->ut_line), utp->ut_line);
D 43
	if (index(tty + sizeof(_PATH_DEV) - 1, '/')) {
E 43
I 43
	if (strchr(tty + sizeof(_PATH_DEV) - 1, '/')) {
E 43
		/* A slash is an attempt to break security... */
		syslog(LOG_AUTH | LOG_NOTICE, "'/' in \"%s\"", tty);
		return;
	}
E 42
E 33
D 24
	dsyslog(LOG_DEBUG, ".notify: notify %s on %s\n", utp->ut_name, tty);
E 24
	if (stat(tty, &stb) || !(stb.st_mode & S_IEXEC)) {
D 24
		dsyslog(LOG_DEBUG, ".notify: wrong mode on tty");
E 24
I 24
		dsyslog(LOG_DEBUG, "%s: wrong mode on %s", utp->ut_name, tty);
E 24
E 22
E 21
		return;
	}
I 24
	dsyslog(LOG_DEBUG, "notify %s on %s\n", utp->ut_name, tty);
E 24
I 12
D 13
	if (fork())
E 13
I 13
D 14
	if ((fd = open(tty, O_WRONLY|O_NDELAY)) < 0) {
		dprintf("%s: open failed\n", tty);
E 14
I 14
	if (fork())
E 14
E 13
		return;
I 14
D 22
	signal(SIGALRM, SIG_DFL);
	alarm(30);
	if ((tp = fopen(tty,"w")) == 0) {
D 21
		dprintf("fopen failed\n");
E 21
I 21
		dsyslog(LOG_DEBUG,".notify: fopen of tty failed");
E 22
I 22
	(void)signal(SIGALRM, SIG_DFL);
	(void)alarm((u_int)30);
	if ((tp = fopen(tty, "w")) == NULL) {
D 24
		dsyslog(LOG_DEBUG, ".notify: fopen of tty failed");
E 22
E 21
		exit(-1);
E 24
I 24
D 41
		dsyslog(LOG_ERR, "fopen of tty %s failed", tty);
E 41
I 41
		dsyslog(LOG_ERR, "%s: %s", tty, strerror(errno));
E 41
		_exit(-1);
E 24
E 14
D 13
	signal(SIGALRM, SIG_DFL);
	alarm(30);
E 12
	if ((tp = fopen(tty,"w")) == 0) {
		dprintf("fopen failed\n");
D 12
		return;
E 12
I 12
		exit(-1);
E 13
E 12
	}
D 6
	gtty(fileno(tp),&gttybuf);
E 6
I 6
D 13
	ioctl(fileno(tp), TIOCGETP, &gttybuf);
E 13
I 13
D 14
	if ((flags = fcntl(fd, F_GETFL, 0)) == -1) {
		dprintf("fcntl(F_GETFL) failed %d\n", errno);
		return;
	}
	ioctl(fd, TIOCGETP, &gttybuf);
E 14
I 14
D 22
	ioctl(fileno(tp), TIOCGETP, &gttybuf);
E 22
I 22
	(void)ioctl(fileno(tp), TIOCGETP, &gttybuf);
E 22
E 14
E 13
E 6
D 18
	cr = (gttybuf.sg_flags & CRMOD) ? "" : "\r";
E 18
I 18
D 32
	cr = (gttybuf.sg_flags&CRMOD) && !(gttybuf.sg_flags&RAW) ? "" : "\r";
E 32
I 32
	cr = (gttybuf.sg_flags&CRMOD) && !(gttybuf.sg_flags&RAW) ?
	    "\n" : "\n\r";
E 32
E 18
I 6
D 12
	gethostname(hostname, sizeof (hostname));
E 12
E 6
D 22
	strncpy(name, utp->ut_name, sizeof (utp->ut_name));
E 22
I 22
D 33
	(void)strncpy(name, utp->ut_name, sizeof (utp->ut_name));
E 22
D 12
	name[sizeof (name) - 1] = 0;
E 12
I 12
	name[sizeof (name) - 1] = '\0';
E 33
I 33
	(void)strncpy(name, utp->ut_name, sizeof(utp->ut_name));
	name[sizeof(name) - 1] = '\0';
E 33
E 12
D 6
	fprintf(tp,"%s\n\007New mail for %s\007 has arrived:%s\n",
	    cr, name, cr);
E 6
I 6
D 13
	fprintf(tp,"%s\n\007New mail for %s@%s\007 has arrived:%s\n",
E 13
I 13
D 14
	sprintf(msgbuf, "%s\n\007New mail for %s@%s\007 has arrived:%s\n",
E 14
I 14
D 20
	fprintf(tp,"%s\n\007New mail for %s@%s\007 has arrived:%s\n",
E 14
E 13
	    cr, name, hostname, cr);
E 20
I 20
D 22
	fprintf(tp,"%s\n\007New mail for %s@%.*s\007 has arrived:%s\n",
	    cr, name, sizeof (hostname), hostname, cr);
E 20
E 6
D 13
	fprintf(tp,"----%s\n", cr);
	jkfprintf(tp, name, offset);
E 13
I 13
D 14
	jkfprintf(msgbuf+strlen(msgbuf), name, offset);
	if (fcntl(fd, F_SETFL, flags | FNDELAY) == -1)
		goto oldway;
	msglen = strlen(msgbuf);
	n = write(fd, msgbuf, msglen);
	err = errno;
	(void) fcntl(fd, F_SETFL, flags);
	(void) close(fd);
	if (n == msglen)
		return;
	if (err != EWOULDBLOCK) {
		dprintf("write failed %d\n", errno);
		return;
	}
oldway:
	if (fork()) {
		(void) close(fd);
		return;
	}
	signal(SIGALRM, SIG_DFL);
	alarm(30);
	(void) write(fd, msgbuf, msglen);
E 14
I 14
	fprintf(tp,"----%s\n", cr);
E 22
I 22
D 32
	fprintf(tp, "%s\n\007New mail for %s@%.*s\007 has arrived:%s\n----%s\n",
	    cr, name, sizeof (hostname), hostname, cr, cr);
E 32
I 32
	(void)fprintf(tp, "%s\007New mail for %s@%.*s\007 has arrived:%s----%s",
D 42
	    cr, name, sizeof(hostname), hostname, cr, cr);
E 42
I 42
	    cr, name, (int)sizeof(hostname), hostname, cr, cr);
E 42
E 32
E 22
	jkfprintf(tp, name, offset);
E 14
E 13
D 6
	 fclose(tp);
E 6
I 6
D 12
	fclose(tp);
E 12
I 12
D 24
	exit(0);
E 24
I 24
D 32
	fclose(tp);
E 32
I 32
	(void)fclose(tp);
E 32
	_exit(0);
E 24
E 12
E 6
}

I 41
void
E 41
D 13
jkfprintf(tp, name, offset)
	register FILE *tp;
E 13
I 13
D 14
jkfprintf(mp, name, offset)
	register char *mp;
E 14
I 14
jkfprintf(tp, name, offset)
	register FILE *tp;
I 22
	char name[];
D 27
	int offset;
E 27
I 27
	off_t offset;
E 27
E 22
E 14
E 13
{
I 22
D 32
	register char *cp;
E 32
I 32
	register char *cp, ch;
E 32
E 22
	register FILE *fi;
D 22
	register int linecnt, charcnt;
E 22
I 22
	register int linecnt, charcnt, inheader;
I 42
	register struct passwd *p;
E 42
E 22
I 6
	char line[BUFSIZ];
I 9
D 22
	int inheader;
E 22
I 22
D 39
	off_t fseek();
E 39
E 22
E 9
E 6

I 42
	/* Set effective uid to user in case mail drop is on nfs */
	if ((p = getpwnam(name)) != NULL)
		(void) setuid(p->pw_uid);

E 42
D 13
	dprintf("HERE %s's mail starting at %d\n",
	    name, offset);
	if ((fi = fopen(name,"r")) == NULL) {
E 13
I 13
D 14
	dprintf("HERE %s's mail starting at %d\n", name, offset);

	if ((fi = fopen(name, "r")) == NULL) {
E 14
I 14
D 21
	dprintf("HERE %s's mail starting at %d\n",
E 21
I 21
D 22
	dsyslog(LOG_DEBUG,".jkfprint: HERE %s's mail starting at %d\n",
E 22
I 22
D 24
	dsyslog(LOG_DEBUG, ".jkfprint: HERE %s's mail starting at %d\n",
E 22
E 21
	    name, offset);
D 22
	if ((fi = fopen(name,"r")) == NULL) {
E 14
E 13
D 21
		dprintf("Cant read the mail\n");
E 21
I 21
		dsyslog(LOG_DEBUG,".jkfprintf: Cant read the mail\n");
E 22
I 22
	if ((fi = fopen(name, "r")) == NULL) {
		dsyslog(LOG_DEBUG, ".jkfprintf: Can't read the mail\n");
E 24
I 24
	if ((fi = fopen(name, "r")) == NULL)
E 24
E 22
E 21
		return;
I 42

E 42
D 24
	}
E 24
D 12
	fseek(fi, offset, 0);
E 12
I 12
D 22
	fseek(fi, offset, L_SET);
E 22
I 22
D 27
	(void)fseek(fi, (long)offset, L_SET);
E 27
I 27
	(void)fseek(fi, offset, L_SET);
E 27
E 22
E 12
D 6
	linecnt = 7;
	charcnt = 560;
E 6
D 34
	/* 
E 34
I 34
	/*
E 34
D 6
	 * print the first 7 lines or 560 characters of the new mail
	 * (whichever comes first)
E 6
I 6
	 * Print the first 7 lines or 560 characters of the new mail
	 * (whichever comes first).  Skip header crap other than
D 9
	 * From: and Subject:.
E 9
I 9
	 * From, Subject, To, and Date.
E 9
E 6
	 */
D 6
	for (;;) {
		register ch;
E 6
I 6
	linecnt = 7;
	charcnt = 560;
I 9
	inheader = 1;
E 9
D 33
	while (fgets(line, sizeof (line), fi) != NULL) {
E 33
I 33
	while (fgets(line, sizeof(line), fi) != NULL) {
E 33
D 22
		register char *cp;
		char *index();
I 9
		int cnt;
E 9
E 6

D 6
	 	if ((ch = getc(fi)) == EOF) {  
			fprintf(tp,"----%s\n", cr);
			break;
		}
		if (ch == '\n') {  
			fprintf(tp,"%s\n", cr);
		 	if (linecnt-- < 0) {  
				fprintf(tp,"...more...%s\n", cr);
				break;
			}
		} else if(linecnt <= 0) {  
E 6
I 6
		if (linecnt <= 0 || charcnt <= 0) {  
E 6
D 13
			fprintf(tp,"...more...%s\n", cr);
E 13
I 13
D 14
			sprintf(mp, "...more...%s\n", cr);
			mp += strlen(mp);
E 14
I 14
			fprintf(tp,"...more...%s\n", cr);
E 14
E 13
D 7
			break;
E 7
I 7
			return;
E 7
D 6
		} else
			putc(ch, tp);
		if (charcnt-- == 0) {   
			fprintf(tp, "%s\n", cr);
			break;
E 6
		}
E 22
I 9
D 24
		if (strncmp(line, "From ", 5) == 0)
			continue;
E 24
D 22
		if (inheader && (line[0] == ' ' || line[0] == '\t'))
			continue;
E 9
I 6
		cp = index(line, ':');
D 9
		if (cp &&
		    strncmp(line, "Date", cp - line) &&
		    strncmp(line, "From", cp - line) &&
		    strncmp(line, "Subject", cp - line) &&
		    strncmp(line, "To", cp - line))
E 9
I 9
		if (cp == 0 || (index(line, ' ') && index(line, ' ') < cp))
			inheader = 0;
		else
			cnt = cp - line;
		if (inheader &&
		    strncmp(line, "Date", cnt) &&
		    strncmp(line, "From", cnt) &&
		    strncmp(line, "Subject", cnt) &&
		    strncmp(line, "To", cnt))
E 9
			continue;
		cp = index(line, '\n');
		if (cp)
E 22
I 22
		if (inheader) {
D 24
			if (line[0] == ' ' || line[0] == '\t')
				continue;
			if (!(cp = strpbrk(line, ": ")) || *cp == ' ')
E 24
I 24
			if (line[0] == '\n') {
E 24
				inheader = 0;
D 24
			else if (strncmp(line, "From:", 5) &&
E 24
I 24
				continue;
			}
			if (line[0] == ' ' || line[0] == '\t' ||
			    strncmp(line, "From:", 5) &&
E 24
			    strncmp(line, "Subject:", 8))
				continue;
		}
I 29
		if (linecnt <= 0 || charcnt <= 0) {
D 32
			fprintf(tp, "...more...%s\n", cr);
E 32
I 32
			(void)fprintf(tp, "...more...%s", cr);
I 42
			(void)fclose(fi);
E 42
E 32
			return;
		}
E 29
D 32
		if (cp = index(line, '\n'))
E 22
			*cp = '\0';
D 13
		fprintf(tp,"%s%s\n", line, cr);
E 13
I 13
D 14
		sprintf(mp, "%s%s\n", line, cr);
		mp += strlen(mp);
E 14
I 14
D 22
		fprintf(tp,"%s%s\n", line, cr);
E 14
E 13
		linecnt--, charcnt -= strlen(line);
E 22
I 22
		fprintf(tp, "%s%s\n", line, cr);
D 24
		if (--linecnt <= 0 || (charcnt -= strlen(line)) <= 0) {
E 24
I 24
		charcnt -= strlen(line);
D 29
		if (--linecnt <= 0 || charcnt <= 0) {
E 24
			fprintf(tp, "...more...%s\n", cr);
			return;
		}
E 29
I 29
		linecnt--;
E 32
I 32
		/* strip weird stuff so can't trojan horse stupid terminals */
		for (cp = line; (ch = *cp) && ch != '\n'; ++cp, --charcnt) {
D 34
			ch &= 0x7f;
E 34
I 34
			ch = toascii(ch);
E 34
			if (!isprint(ch) && !isspace(ch))
				ch |= 0x40;
			(void)fputc(ch, tp);
		}
		(void)fputs(cr, tp);
		--linecnt;
E 32
E 29
E 22
E 6
	}
I 6
D 13
	fprintf(tp,"----%s\n", cr);
E 13
I 13
D 14
	sprintf(mp, "----%s\n", cr);
	mp += strlen(mp);
E 14
I 14
D 22
	fprintf(tp,"----%s\n", cr);
E 22
I 22
D 32
	fprintf(tp, "----%s\n", cr);
E 32
I 32
	(void)fprintf(tp, "----%s\n", cr);
I 42
	(void)fclose(fi);
E 42
E 32
E 22
E 14
E 13
E 6
}
E 1
