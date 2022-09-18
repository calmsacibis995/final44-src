h09880
s 00006/00003/00510
d D 8.7 95/05/10 05:57:50 bostic 41 40
c Paul Vixie tested this and found some problems.
e
s 00002/00001/00511
d D 8.6 95/04/28 15:39:34 tef 40 39
c Better portability to other systems.
e
s 00031/00000/00481
d D 8.5 95/04/27 21:38:42 tef 39 38
c Bug fixes.
e
s 00004/00002/00477
d D 8.4 94/04/17 09:31:18 bostic 38 37
c fromunix, frominet are declared as automatic variables in main()
c and aren't bzero()'d before use.
c From: "Chris G. Demetriou" <cgd@nobozo.CS.Berkeley.EDU>
e
s 00003/00001/00476
d D 8.3 94/02/23 06:46:40 bostic 37 36
c bzero the sockaddr_in struct before initialization
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00001/00001/00476
d D 8.2 94/01/02 12:50:23 bostic 36 35
c Assign printer pointer after forking so the parent doesn't print
c garbage in error messages
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00004/00004/00473
d D 8.1 93/06/06 14:00:08 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00473
d D 5.20 93/02/25 17:04:27 torek 34 32
c hide the magic strlen+2: use the SUN_LEN macro
e
s 00004/00002/00473
d R 5.20 93/02/25 16:37:58 torek 33 32
c hide the magic strlen+2: use the SUN_LEN macro
e
s 00001/00000/00474
d D 5.19 92/11/30 13:35:09 bostic 32 31
c add restarted line to log
e
s 00001/00001/00473
d D 5.18 92/09/16 10:52:27 elan 31 30
c copyright -> static
e
s 00004/00029/00470
d D 5.17 92/09/15 10:52:02 elan 30 29
c Added SCCS keywords.
e
s 00051/00017/00448
d D 5.16 92/09/01 11:09:47 elan 29 28
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00047/00009/00418
d D 5.15 92/07/21 10:29:22 bostic 28 27
c prototype lpr to fix quad's
e
s 00010/00021/00417
d D 5.14 92/06/29 12:34:09 leres 27 26
c use ivaliduser, not validuser, minor cleanups
e
s 00004/00004/00434
d D 5.13 91/08/21 02:05:01 torek 26 25
c sun => un, so we can compile on a sun
e
s 00013/00001/00425
d D 5.12 91/03/07 11:01:23 mckusick 25 24
c ignore add/delete requests from UNIX socket (4.3BSD-reno/usr.sbin/1)
e
s 00013/00008/00413
d D 5.11 91/03/02 14:54:05 bostic 24 23
c ANSI
e
s 00001/00001/00420
d D 5.10 90/10/12 19:48:08 karels 23 22
c init stack variables!
e
s 00001/00012/00420
d D 5.9 90/06/29 20:55:57 karels 22 21
c use daemon() call
e
s 00001/00011/00431
d D 5.8 90/06/01 18:45:13 bostic 21 20
c new copyright notice
e
s 00013/00012/00429
d D 5.7 89/05/11 14:09:35 bostic 20 19
c file reorg, pathnames.h, paths.h
e
s 00010/00005/00431
d D 5.6 88/06/30 17:59:52 bostic 19 18
c install approved copyright notice
e
s 00010/00004/00426
d D 5.5 88/05/05 18:08:00 bostic 18 17
c written by Ralph Campbell; add Berkeley specific header
e
s 00019/00009/00411
d D 5.4 86/05/06 18:38:37 bloom 17 16
c use a standard set of routines for reading hosts.equiv and hosts.lpd
e
s 00001/00001/00419
d D 5.3 85/11/17 15:53:19 eric 16 15
c clean up logging
e
s 00001/00001/00419
d D 5.2 85/09/17 19:27:02 eric 15 14
c facilities in syslog
e
s 00013/00001/00407
d D 5.1 85/06/06 10:03:08 dist 14 13
c Add copyright
e
s 00039/00089/00369
d D 4.12 84/07/25 08:52:18 ralph 13 12
c use syslog().
e
s 00017/00007/00441
d D 4.11 83/11/18 10:32:47 ralph 12 11
c added /etc/hosts.lpd to list of acceptable hosts.
e
s 00026/00002/00422
d D 4.10 83/08/24 15:17:17 ralph 11 10
c added master lock file so /dev/printer removed automatically
e
s 00004/00000/00420
d D 4.9 83/08/18 15:22:57 ralph 10 9
c signal to minor daemon caused /dev/printer to be removed.
e
s 00013/00014/00407
d D 4.8 83/07/27 09:27:05 ralph 9 8
c bug fixes for `rs' printcap entry
e
s 00017/00008/00404
d D 4.7 83/07/17 14:44:22 sam 8 6
c missing select arg
e
s 00017/00008/00404
d R 4.7 83/07/17 00:10:14 sam 7 6
c can't ignore select return value
e
s 00099/00073/00313
d D 4.6 83/07/06 22:08:52 sam 6 5
c for ralph; chnage to UNIX domain
e
s 00008/00025/00378
d D 4.5 83/06/15 14:57:10 sam 5 4
c open and flock defines changed
e
s 00018/00013/00385
d D 4.4 83/06/02 12:23:08 ralph 4 3
c made local variables static to improve separation between functions.
e
s 00003/00000/00395
d D 4.3 83/05/26 11:29:22 ralph 3 2
c doesn't check /etc/hosts.equiv if from == host
e
s 00103/00021/00292
d D 4.2 83/05/13 11:52:18 ralph 2 1
c bug fixes and changes for lpc command.
e
s 00313/00000/00000
d D 4.1 83/04/29 11:28:33 ralph 1 0
c date and time created 83/04/29 11:28:33 by ralph
e
u
U
t
T
I 14
/*
D 30
 * Copyright (c) 1983 Regents of the University of California.
E 30
I 30
D 35
 * Copyright (c) 1983 The Regents of the University of California.
E 30
D 18
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
 * All rights reserved.
E 35
I 35
D 38
 * Copyright (c) 1983, 1993
E 38
I 38
 * Copyright (c) 1983, 1993, 1994
E 38
 *	The Regents of the University of California.  All rights reserved.
E 35
 *
D 21
 * Redistribution and use in source and binary forms are permitted
D 19
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 19
I 19
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
E 21
I 21
D 29
 * %sccs.include.redist.c%
E 29
I 29
D 30
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
E 30
 *
D 30
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 30
I 30
 * %sccs.include.redist.c%
E 30
E 29
E 21
E 19
E 18
 */

E 14
I 1
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
#ifndef lint
I 14
D 31
char copyright[] =
E 31
I 31
static char copyright[] =
E 31
D 29
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 29
I 29
D 30
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 30
I 30
D 35
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 30
E 29
 All rights reserved.\n";
E 35
I 35
D 38
"%Z% Copyright (c) 1983, 1993\n\
E 38
I 38
"%Z% Copyright (c) 1983, 1993, 1994\n\
E 38
	The Regents of the University of California.  All rights reserved.\n";
E 35
D 18
#endif not lint
E 18
I 18
#endif /* not lint */
E 18

#ifndef lint
E 14
D 29
static char sccsid[] = "%W% (Berkeley) %G%";
E 29
I 29
D 30
static char sccsid[] = "@(#)lpd.c	5.16 (Berkeley) 8/6/92";
E 30
I 30
static char sccsid[] = "%W% (Berkeley) %G%";
E 30
E 29
D 14
#endif
E 14
I 14
D 18
#endif not lint
E 18
I 18
#endif /* not lint */
E 18
E 14

E 8
/*
 * lpd -- line printer daemon.
 *
 * Listen for a connection and perform the requested operation.
 * Operations are:
 *	\1printer\n
 *		check the queue for jobs and print any found.
 *	\2printer\n
 *		receive a job from another machine and queue it.
 *	\3printer [users ...] [jobs ...]\n
 *		return the current state of the queue (short form).
 *	\4printer [users ...] [jobs ...]\n
 *		return the current state of the queue (long form).
 *	\5printer person [users ...] [jobs ...]\n
 *		remove jobs from the queue.
I 2
D 13
 *	\6printer\n
 *		enable queuing on the specified printer queue.
 *	\7printer\n
 *		disable queuing on the specified printer queue.
 *	\8printer\n
 *		return the queue status (queuing enabled or disabled).
E 13
E 2
 *
 * Strategy to maintain protected spooling area:
 *	1. Spooling area is writable only by daemon and spooling group
 *	2. lpr runs setuid root and setgrp spooling group; it uses
 *	   root to access any file it wants (verifying things before
 *	   with an access call) and group id to know how it should
 *	   set up ownership of files in the spooling area.
D 2
 *	3. Files in spooling area are owned by the owner, group spooling
E 2
I 2
 *	3. Files in spooling area are owned by root, group spooling
E 2
 *	   group, with mode 660.
 *	4. lpd, lpq and lprm run setuid daemon and setgrp spooling group to
 *	   access files and printer.  Users can't get to anything
 *	   w/o help of lpq and lprm programs.
 */

I 28
#include <sys/param.h>
#include <sys/wait.h>
D 29

E 29
I 29
#include <sys/types.h>
E 29
#include <sys/socket.h>
#include <sys/un.h>
I 29
#include <sys/stat.h>
I 40
#include <sys/file.h>
E 40
E 29
#include <netinet/in.h>
D 29
#include <netdb.h>
E 29

I 29
#include <netdb.h>
#include <unistd.h>
E 29
#include <syslog.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
I 29
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
E 29
E 28
#include "lp.h"
I 28
#include "lp.local.h"
E 28
I 20
#include "pathnames.h"
I 28
#include "extern.h"
E 28
E 20

I 2
D 4
int	lflag;					/* log requests flag */
E 2
char	*logfile = DEFLOGF;
struct	sockaddr_in sin = { AF_INET };
E 4
I 4
D 13
static int	lflag;				/* log requests flag */
static char	*logfile = DEFLOGF;
E 13
I 13
int	lflag;				/* log requests flag */
I 25
int	from_remote;			/* from remote socket */
E 25
E 13
D 6
static struct	sockaddr_in sin = { AF_INET };
E 6

E 4
D 24
int	reapchild();
D 5
char	*ntoa();
E 5
I 5
D 6
char	*inet_ntoa();
E 6
I 6
D 13
int	cleanup();
E 13
I 13
int	mcleanup();
E 24
I 24
D 28
void mcleanup(), reapchild();
E 28
I 28
static void       reapchild __P((int));
static void       mcleanup __P((int));
static void       doit __P((void));
static void       startup __P((void));
static void       chkhost __P((struct sockaddr_in *));
I 41
static int	  ckqueue __P((char *));
E 41
E 28
E 24
E 13
E 6
E 5

I 28
int
E 28
main(argc, argv)
	int argc;
	char **argv;
{
D 6
	int f, options;
D 2
	struct sockaddr_in from;
E 2
I 2
	struct sockaddr_in fromaddr;
E 2
	struct servent *sp;
E 6
I 6
D 23
	int f, funix, finet, options, defreadfds, fromlen;
E 23
I 23
D 29
	int f, funix, finet, options = 0, defreadfds, fromlen;
E 29
I 29
	int f, funix, finet, options, fromlen;
	fd_set defreadfds;
E 29
E 23
D 26
	struct sockaddr_un sun, fromunix;
E 26
I 26
	struct sockaddr_un un, fromunix;
E 26
	struct sockaddr_in sin, frominet;
D 11
	int omask;
E 11
I 11
	int omask, lfd;
E 11
E 6

I 29
	options = 0;
E 29
	gethostname(host, sizeof(host));
	name = argv[0];

D 6
	sp = getservbyname("printer", "tcp");
	if (sp == NULL) {
D 2
		log("printer/tcp: unknown service");
E 2
I 2
		fprintf(stderr, "printer/tcp: unknown service");
E 2
		exit(1);
	}
	sin.sin_port = sp->s_port;

E 6
	while (--argc > 0) {
		argv++;
		if (argv[0][0] == '-')
			switch (argv[0][1]) {
			case 'd':
				options |= SO_DEBUG;
				break;
			case 'l':
I 2
				lflag++;
				break;
D 13
			case 'L':
E 2
				argc--;
				logfile = *++argv;
				break;
E 13
			}
D 6
		else {
			int port = atoi(argv[0]);
I 2
			int c = argv[0][0];
E 2

D 2
			if (port < 0) {
				fprintf(stderr, "%s: bad port #\n", argv[0]);
E 2
I 2
			if (c < '0' || c > '9' || port < 0) {
				fprintf(stderr, "lpd: %s: bad port number\n", argv[0]);
E 2
				exit(1);
			}
			sin.sin_port = htons((u_short) port);
		}
E 6
	}
I 11

E 11
#ifndef DEBUG
	/*
	 * Set up standard environment by detaching from the parent.
	 */
D 22
	if (fork())
		exit(0);
D 13
	for (f = 0; f < 3; f++)
E 13
I 13
	for (f = 0; f < 5; f++)
E 13
		(void) close(f);
D 5
	(void) open("/dev/null", FRDONLY, 0);
	(void) open("/dev/null", FWRONLY, 0);
	(void) open(logfile, FWRONLY|FAPPEND, 0);
	f = open("/dev/tty", FRDWR, 0);
E 5
I 5
D 20
	(void) open("/dev/null", O_RDONLY);
	(void) open("/dev/null", O_WRONLY);
E 20
I 20
	(void) open(_PATH_DEVNULL, O_RDONLY);
	(void) open(_PATH_DEVNULL, O_WRONLY);
E 20
D 13
	(void) open(logfile, O_WRONLY|O_APPEND);
E 13
I 13
	(void) dup(1);
E 13
D 20
	f = open("/dev/tty", O_RDWR);
E 20
I 20
	f = open(_PATH_TTY, O_RDWR);
E 20
E 5
	if (f > 0) {
		ioctl(f, TIOCNOTTY, 0);
		(void) close(f);
	}
E 22
I 22
	daemon(0, 0);
E 22
#endif
I 6
D 9
#define	mask(s)	(1 << ((s) - 1))
#define	ALLINTS	mask(SIGHUP)|mask(SIGINT)|mask(SIGQUIT)|mask(SIGTERM)
	omask = sigblock(ALLINTS);
	signal(SIGHUP, cleanup);
	signal(SIGINT, cleanup);
	signal(SIGQUIT, cleanup);
	signal(SIGTERM, cleanup);
E 9
D 11
	signal(SIGCHLD, reapchild);
E 11
I 11

I 13
D 15
	openlog("lpd", LOG_PID, 0);
E 15
I 15
D 16
	openlog("lpd", LOG_PID, LOG_DAEMON);
E 16
I 16
	openlog("lpd", LOG_PID, LOG_LPR);
I 32
	syslog(LOG_INFO, "restarted");
E 32
E 16
E 15
E 13
E 11
E 6
	(void) umask(0);
I 11
D 20
	lfd = open(MASTERLOCK, O_WRONLY|O_CREAT, 0644);
E 20
I 20
	lfd = open(_PATH_MASTERLOCK, O_WRONLY|O_CREAT, 0644);
E 20
	if (lfd < 0) {
D 13
		log("cannot create %s", MASTERLOCK);
E 13
I 13
D 20
		syslog(LOG_ERR, "%s: %m", MASTERLOCK);
E 20
I 20
		syslog(LOG_ERR, "%s: %m", _PATH_MASTERLOCK);
E 20
E 13
		exit(1);
	}
	if (flock(lfd, LOCK_EX|LOCK_NB) < 0) {
		if (errno == EWOULDBLOCK)	/* active deamon present */
			exit(0);
D 13
		log("cannot lock %s", MASTERLOCK);
E 13
I 13
D 20
		syslog(LOG_ERR, "%s: %m", MASTERLOCK);
E 20
I 20
		syslog(LOG_ERR, "%s: %m", _PATH_MASTERLOCK);
E 20
E 13
		exit(1);
	}
	ftruncate(lfd, 0);
E 11
I 4
	/*
I 11
	 * write process id for others to know
	 */
	sprintf(line, "%u\n", getpid());
	f = strlen(line);
	if (write(lfd, line, f) != f) {
D 13
		log("cannot write daemon pid");
E 13
I 13
D 20
		syslog(LOG_ERR, "%s: %m", MASTERLOCK);
E 20
I 20
		syslog(LOG_ERR, "%s: %m", _PATH_MASTERLOCK);
E 20
E 13
		exit(1);
	}
	signal(SIGCHLD, reapchild);
	/*
E 11
	 * Restart all the printers.
	 */
	startup();
I 11
D 20
	(void) unlink(SOCKETNAME);
E 20
I 20
	(void) unlink(_PATH_SOCKETNAME);
E 20
E 11
E 4
D 6
	f = socket(AF_INET, SOCK_STREAM, 0);
	if (f < 0) {
		logerror("socket");
E 6
I 6
	funix = socket(AF_UNIX, SOCK_STREAM, 0);
	if (funix < 0) {
D 13
		logerr("socket");
E 13
I 13
		syslog(LOG_ERR, "socket: %m");
E 13
E 6
		exit(1);
	}
I 9
#define	mask(s)	(1 << ((s) - 1))
	omask = sigblock(mask(SIGHUP)|mask(SIGINT)|mask(SIGQUIT)|mask(SIGTERM));
D 13
	signal(SIGHUP, cleanup);
	signal(SIGINT, cleanup);
	signal(SIGQUIT, cleanup);
	signal(SIGTERM, cleanup);
E 13
I 13
	signal(SIGHUP, mcleanup);
	signal(SIGINT, mcleanup);
	signal(SIGQUIT, mcleanup);
	signal(SIGTERM, mcleanup);
I 37
	memset(&un, 0, sizeof(un));
E 37
E 13
E 9
D 6
	if (options & SO_DEBUG)
D 2
		if (setsockopt(f, SOL_SOCKET, SO_DEBUG, 0, 0) < 0)
E 2
I 2
		if (setsockopt(f, SOL_SOCKET, SO_DEBUG, 0, 0) < 0) {
E 2
			logerror("setsockopt (SO_DEBUG)");
I 2
			exit(1);
		}
E 2
	if (bind(f, &sin, sizeof(sin), 0) < 0) {
		logerror("bind");
E 6
I 6
D 26
	sun.sun_family = AF_UNIX;
D 20
	strcpy(sun.sun_path, SOCKETNAME);
E 20
I 20
	strcpy(sun.sun_path, _PATH_SOCKETNAME);
E 26
I 26
	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, _PATH_SOCKETNAME);
E 26
E 20
D 24
	if (bind(funix, &sun, strlen(sun.sun_path) + 2) < 0) {
E 24
I 24
D 34
	if (bind(funix,
D 26
	     (struct sockaddr *)&sun, strlen(sun.sun_path) + 2) < 0) {
E 26
I 26
	     (struct sockaddr *)&un, strlen(un.sun_path) + 2) < 0) {
E 34
I 34
#ifndef SUN_LEN
#define SUN_LEN(unp) (strlen((unp)->sun_path) + 2)
#endif
	if (bind(funix, (struct sockaddr *)&un, SUN_LEN(&un)) < 0) {
E 34
E 26
E 24
D 13
		logerr("unix domain bind");
E 13
I 13
		syslog(LOG_ERR, "ubind: %m");
E 13
E 6
		exit(1);
	}
I 6
	sigsetmask(omask);
I 9
D 29
	defreadfds = 1 << funix;
E 29
I 29
	FD_ZERO(&defreadfds);
	FD_SET(funix, &defreadfds);
E 29
	listen(funix, 5);
E 9
	finet = socket(AF_INET, SOCK_STREAM, 0);
	if (finet >= 0) {
		struct servent *sp;

		if (options & SO_DEBUG)
			if (setsockopt(finet, SOL_SOCKET, SO_DEBUG, 0, 0) < 0) {
D 13
				logerr("setsockopt (SO_DEBUG)");
				cleanup();
E 13
I 13
				syslog(LOG_ERR, "setsockopt (SO_DEBUG): %m");
D 28
				mcleanup();
E 28
I 28
				mcleanup(0);
E 28
E 13
			}
		sp = getservbyname("printer", "tcp");
		if (sp == NULL) {
D 13
			log("printer/tcp: unknown service");
			cleanup();
E 13
I 13
			syslog(LOG_ERR, "printer/tcp: unknown service");
D 28
			mcleanup();
E 28
I 28
			mcleanup(0);
E 28
E 13
		}
I 37
		memset(&sin, 0, sizeof(sin));
E 37
		sin.sin_family = AF_INET;
		sin.sin_port = sp->s_port;
D 24
		if (bind(finet, &sin, sizeof(sin), 0) < 0) {
E 24
I 24
		if (bind(finet, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
E 24
D 13
			logerr("internet domain bind");
			cleanup();
E 13
I 13
			syslog(LOG_ERR, "bind: %m");
D 28
			mcleanup();
E 28
I 28
			mcleanup(0);
E 28
E 13
		}
D 9
	}
E 6
	/*
D 4
	 * Restart all the printers and tell everyone that we are
	 * up and running.
	 */
	startup();
	/*
E 4
	 * Main loop: listen, accept, do a request, continue.
	 */
D 5
	sigset(SIGCHLD, reapchild);
E 5
I 5
D 6
	signal(SIGCHLD, reapchild);
E 5
	listen(f, 10);
E 6
I 6
	defreadfds = 1 << funix;
	listen(funix, 5);
	if (finet >= 0) {
E 9
D 29
		defreadfds |= 1 << finet;
E 29
I 29
D 37
		FD_SET(finet, &defreadfds);	
E 37
I 37
		FD_SET(finet, &defreadfds);
E 37
E 29
		listen(finet, 5);
	}
I 9
	/*
	 * Main loop: accept, do a request, continue.
	 */
I 38
	memset(&frominet, 0, sizeof(frominet));
	memset(&fromunix, 0, sizeof(fromunix));
E 38
E 9
E 6
	for (;;) {
D 2
		int s, len = sizeof(from);
E 2
I 2
D 6
		int s, len = sizeof(fromaddr);
E 6
I 6
D 8
		int domain, s, readfds = defreadfds;
E 8
I 8
D 29
		int domain, nfds, s, readfds = defreadfds;
E 29
I 29
		int domain, nfds, s;
		fd_set readfds;
E 29
E 8
E 6
E 2

I 29
		FD_COPY(&defreadfds, &readfds);
E 29
D 2
		s = accept(f, &from, &len, 0);
E 2
I 2
D 6
		s = accept(f, &fromaddr, &len, 0);
E 6
I 6
D 8
		(void) select(&readfds, 0, 0, 0);
E 8
I 8
		nfds = select(20, &readfds, 0, 0, 0);
		if (nfds <= 0) {
D 13
			if (nfds < 0 && errno != EINTR) {
				logerr("select");
				cleanup();
				/*NOTREACHED*/
			}
E 13
I 13
			if (nfds < 0 && errno != EINTR)
				syslog(LOG_WARNING, "select: %m");
E 13
			continue;
		}
E 8
D 29
		if (readfds & (1 << funix)) {
E 29
I 29
		if (FD_ISSET(funix, &readfds)) {
E 29
D 8
			domain = AF_UNIX;
			fromlen = sizeof(fromunix);
E 8
I 8
			domain = AF_UNIX, fromlen = sizeof(fromunix);
E 8
D 24
			s = accept(funix, &fromunix, &fromlen);
E 24
I 24
			s = accept(funix,
			    (struct sockaddr *)&fromunix, &fromlen);
E 24
D 8
		} else {
			domain = AF_INET;
			fromlen = sizeof(frominet);
E 8
I 8
D 29
		} else if (readfds & (1 << finet)) {
E 29
I 29
		} else /* if (FD_ISSET(finet, &readfds)) */  {
E 29
			domain = AF_INET, fromlen = sizeof(frominet);
E 8
D 24
			s = accept(finet, &frominet, &fromlen);
E 24
I 24
			s = accept(finet,
			    (struct sockaddr *)&frominet, &fromlen);
E 24
		}
E 6
E 2
		if (s < 0) {
D 13
			if (errno == EINTR)
				continue;
D 6
			logerror("accept");
D 2
			continue;
E 2
I 2
			exit(1);
E 6
I 6
			logerr("accept");
			cleanup();
E 13
I 13
			if (errno != EINTR)
				syslog(LOG_WARNING, "accept: %m");
			continue;
E 13
E 6
E 2
		}
		if (fork() == 0) {
D 5
			sigset(SIGCHLD, SIG_IGN);
E 5
I 5
			signal(SIGCHLD, SIG_IGN);
I 10
			signal(SIGHUP, SIG_IGN);
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			signal(SIGTERM, SIG_IGN);
E 10
E 5
D 6
			(void) close(f);
D 2
			doit(s, &from);
E 2
I 2
			doit(s, &fromaddr);
E 6
I 6
			(void) close(funix);
			(void) close(finet);
			dup2(s, 1);
			(void) close(s);
D 25
			if (domain == AF_INET)
E 25
I 25
			if (domain == AF_INET) {
				from_remote = 1;
E 25
				chkhost(&frominet);
I 25
			} else
				from_remote = 0;
E 25
			doit();
E 6
E 2
			exit(0);
		}
		(void) close(s);
	}
}

I 24
D 28
void
E 24
I 4
D 13
static
E 13
E 4
reapchild()
E 28
I 28
static void
reapchild(signo)
	int signo;
E 28
{
	union wait status;

D 24
	while (wait3(&status, WNOHANG, 0) > 0)
E 24
I 24
	while (wait3((int *)&status, WNOHANG, 0) > 0)
E 24
		;
}

I 24
D 28
void
E 24
I 6
D 13
static
cleanup()
E 13
I 13
mcleanup()
E 28
I 28
static void
mcleanup(signo)
	int signo;
E 28
E 13
{
I 9
	if (lflag)
D 13
		log("cleanup()");
E 13
I 13
		syslog(LOG_INFO, "exiting");
E 13
E 9
D 20
	unlink(SOCKETNAME);
E 20
I 20
	unlink(_PATH_SOCKETNAME);
E 20
	exit(0);
}

E 6
/*
 * Stuff for handling job specifications
 */
char	*user[MAXUSERS];	/* users to process */
int	users;			/* # of users in user array */
int	requ[MAXREQUESTS];	/* job number of spool entries */
int	requests;		/* # of spool requests */
I 4
char	*person;		/* name of person doing lprm */
E 4

D 2
char	cbuf[BUFSIZ];		/* command line buffer */
E 2
D 4
char	fromb[32];		/* buffer for client's machine name */
I 2
char	cbuf[BUFSIZ];		/* command line buffer */
char	*cmdnames[] = {
E 4
I 4
D 13
static char	fromb[32];	/* buffer for client's machine name */
static char	cbuf[BUFSIZ];	/* command line buffer */
static char	*cmdnames[] = {
E 13
I 13
D 27
char	fromb[32];	/* buffer for client's machine name */
char	cbuf[BUFSIZ];	/* command line buffer */
E 27
I 27
char	fromb[MAXHOSTNAMELEN];	/* buffer for client's machine name */
char	cbuf[BUFSIZ];		/* command line buffer */
E 27
char	*cmdnames[] = {
E 13
E 4
	"null",
	"printjob",
	"recvjob",
	"displayq short",
	"displayq long",
	"rmjob"
};
E 2

I 28
static void
E 28
I 4
D 13
static
E 13
E 4
D 2
doit(f, fromp)
E 2
I 2
D 6
doit(f, fromaddr)
E 2
	int f;
D 2
	struct sockaddr_in *fromp;
E 2
I 2
	struct sockaddr_in *fromaddr;
E 6
I 6
doit()
E 6
E 2
{
	register char *cp;
D 6
	register struct hostent *hp;
E 6
	register int n;
D 4
	extern char *person;
E 4
D 6
	char c;
E 6

D 6
	dup2(f, 1);
	(void) close(f);
	f = 1;
D 2
	fromp->sin_port = ntohs(fromp->sin_port);
	if (fromp->sin_family != AF_INET || fromp->sin_port >= IPPORT_RESERVED)
E 2
I 2
	fromaddr->sin_port = ntohs(fromaddr->sin_port);
	if (fromaddr->sin_family != AF_INET || fromaddr->sin_port >= IPPORT_RESERVED)
E 2
		fatal("Malformed from address");
D 2
	hp = gethostbyaddr(&fromp->sin_addr, sizeof(struct in_addr),
		fromp->sin_family);
E 2
I 2
	hp = gethostbyaddr(&fromaddr->sin_addr, sizeof(struct in_addr),
		fromaddr->sin_family);
E 2
	if (hp == 0)
		fatal("Host name for your address (%s) unknown",
D 2
			ntoa(fromp->sin_addr));
E 2
I 2
D 5
			ntoa(fromaddr->sin_addr));
E 5
I 5
			inet_ntoa(fromaddr->sin_addr));
E 5
E 2
	strcpy(fromb, hp->h_name);
	from = fromb;
I 2
	if (chkhost())
		fatal("Your host does not have line printer access");
E 6
E 2
	for (;;) {
		cp = cbuf;
		do {
D 6
			if ((n = read(f, &c, 1)) != 1) {
E 6
I 6
			if (cp >= &cbuf[sizeof(cbuf) - 1])
				fatal("Command line too long");
			if ((n = read(1, cp, 1)) != 1) {
E 6
				if (n < 0)
					fatal("Lost connection");
				return;
			}
D 6
			if (cp >= &cbuf[sizeof(cbuf)])
				fatal("Command line too long");
			*cp++ = c;
		} while (c != '\n');
E 6
I 6
		} while (*cp++ != '\n');
E 6
		*--cp = '\0';
		cp = cbuf;
I 2
D 13
		if (lflag && *cp >= '\1' && *cp <= '\5') {
			printer = NULL;
			log("%s requests %s %s", from, cmdnames[*cp], cp+1);
E 13
I 13
		if (lflag) {
			if (*cp >= '\1' && *cp <= '\5')
				syslog(LOG_INFO, "%s requests %s %s",
					from, cmdnames[*cp], cp+1);
			else
				syslog(LOG_INFO, "bad request (%d) from %s",
					*cp, from);
E 13
		}
E 2
		switch (*cp++) {
		case '\1':	/* check the queue and print any jobs there */
			printer = cp;
			printjob();
			break;
		case '\2':	/* receive files to be queued */
I 25
			if (!from_remote) {
				syslog(LOG_INFO, "illegal request (%d)", *cp);
				exit(1);
			}
E 25
			printer = cp;
			recvjob();
			break;
D 2
		case '\3':	/* send back the short form queue status */
		case '\4':	/* send back the long form queue status */
E 2
I 2
		case '\3':	/* display the queue (short form) */
		case '\4':	/* display the queue (long form) */
E 2
			printer = cp;
			while (*cp) {
				if (*cp != ' ') {
					cp++;
					continue;
				}
				*cp++ = '\0';
				while (isspace(*cp))
					cp++;
				if (*cp == '\0')
					break;
				if (isdigit(*cp)) {
					if (requests >= MAXREQUESTS)
						fatal("Too many requests");
					requ[requests++] = atoi(cp);
				} else {
					if (users >= MAXUSERS)
						fatal("Too many users");
					user[users++] = cp;
				}
			}
			displayq(cbuf[0] - '\3');
			exit(0);
		case '\5':	/* remove a job from the queue */
I 25
			if (!from_remote) {
				syslog(LOG_INFO, "illegal request (%d)", *cp);
				exit(1);
			}
E 25
			printer = cp;
			while (*cp && *cp != ' ')
				cp++;
			if (!*cp)
				break;
			*cp++ = '\0';
			person = cp;
			while (*cp) {
				if (*cp != ' ') {
					cp++;
					continue;
				}
				*cp++ = '\0';
				while (isspace(*cp))
					cp++;
				if (*cp == '\0')
					break;
				if (isdigit(*cp)) {
					if (requests >= MAXREQUESTS)
						fatal("Too many requests");
					requ[requests++] = atoi(cp);
				} else {
					if (users >= MAXUSERS)
						fatal("Too many users");
					user[users++] = cp;
				}
			}
			rmjob();
			break;
		}
		fatal("Illegal service request");
D 6
		exit(1);
E 6
	}
}

/*
I 2
 * Make a pass through the printcap database and start printing any
 * files left from the last time the machine went down.
 */
I 28
static void
E 28
I 4
D 13
static
E 13
E 4
startup()
{
D 29
	char buf[BUFSIZ];
E 29
I 29
	char *buf;
E 29
	register char *cp;
	int pid;

D 29
	printer = buf;

E 29
	/*
	 * Restart the daemons.
	 */
D 29
	while (getprent(buf) > 0) {
E 29
I 29
	while (cgetnext(&buf, printcapdb) > 0) {
I 39
D 40
		if (ckqueue() <= 0 ) {
E 40
I 40
D 41
		if (ckqueue() <= 0) {
E 41
I 41
		if (ckqueue(buf) <= 0) {
E 41
E 40
			free(buf);
			continue;	/* no work to do for this printer */
		}
E 39
D 36
		printer = buf;
E 36
E 29
		for (cp = buf; *cp; cp++)
			if (*cp == '|' || *cp == ':') {
				*cp = '\0';
				break;
			}
I 39
		if (lflag)
			syslog(LOG_INFO, "work for %s", buf);
E 39
		if ((pid = fork()) < 0) {
D 13
			log("startup: cannot fork");
D 6
			exit(1);
E 6
I 6
			cleanup();
E 13
I 13
			syslog(LOG_WARNING, "startup: cannot fork");
D 28
			mcleanup();
E 28
I 28
			mcleanup(0);
E 28
E 13
E 6
		}
		if (!pid) {
I 36
			printer = buf;
E 36
D 29
			endprent();
E 29
I 29
			cgetclose();
E 29
			printjob();
I 39
			/* NOTREACHED */
E 39
		}
I 39
		else free(buf);
E 39
	}
I 39
}

/*
 * Make sure there's some work to do before forking off a child
 */
D 41
ckqueue()
E 41
I 41
static int
ckqueue(cap)
	char *cap;
E 41
{
	register struct dirent *d;
	DIR *dirp;
	char *spooldir;

D 41
	if (cgetstr(bp, "sd", &spooldir) == -1)
E 41
I 41
	if (cgetstr(cap, "sd", &spooldir) == -1)
E 41
		spooldir = _PATH_DEFSPOOL;
	if ((dirp = opendir(spooldir)) == NULL)
		return (-1);
	while ((d = readdir(dirp)) != NULL) {
		if (d->d_name[0] != 'c' || d->d_name[1] != 'f')
			continue;	/* daemon control files only */
		closedir(dirp);
		return (1);		/* found something */
	}
	closedir(dirp);
	return (0);
E 39
}

I 17
#define DUMMY ":nobody::"

E 17
/*
 * Check to see if the from host has access to the line printer.
 */
I 28
static void
E 28
I 4
D 13
static
E 13
E 4
D 6
chkhost()
E 6
I 6
chkhost(f)
	struct sockaddr_in *f;
E 6
{
I 6
	register struct hostent *hp;
E 6
	register FILE *hostf;
D 17
	register char *cp;
E 17
I 17
D 29
	register char *cp, *sp;
E 29
E 17
D 27
	char ahost[50];
E 27
I 12
	int first = 1;
E 12
I 6
	extern char *inet_ntoa();
I 17
D 27
	int baselen = -1;
E 27
E 17
E 6

I 6
	f->sin_port = ntohs(f->sin_port);
	if (f->sin_family != AF_INET || f->sin_port >= IPPORT_RESERVED)
		fatal("Malformed from address");
I 27

	/* Need real hostname for temporary filenames */
E 27
D 24
	hp = gethostbyaddr(&f->sin_addr, sizeof(struct in_addr), f->sin_family);
E 24
I 24
	hp = gethostbyaddr((char *)&f->sin_addr,
	    sizeof(struct in_addr), f->sin_family);
E 24
D 27
	if (hp == 0)
E 27
I 27
	if (hp == NULL)
E 27
		fatal("Host name for your address (%s) unknown",
			inet_ntoa(f->sin_addr));

D 27
	strcpy(fromb, hp->h_name);
E 27
I 27
	(void) strncpy(fromb, hp->h_name, sizeof(fromb));
	from[sizeof(fromb) - 1] = '\0';
E 27
	from = fromb;
E 6
I 3
D 27
	if (!strcmp(from, host))
D 6
		return(0);
E 6
I 6
		return;
E 27
E 6

I 17
D 27
	sp = fromb;
	cp = ahost;
	while (*sp) {
		if (*sp == '.') {
			if (baselen == -1)
				baselen = sp - fromb;
			*cp++ = *sp++;
		} else {
			*cp++ = isupper(*sp) ? tolower(*sp++) : *sp++;
		}
	}
	*cp = '\0';
E 27
E 17
E 3
D 20
	hostf = fopen("/etc/hosts.equiv", "r");
E 20
I 20
	hostf = fopen(_PATH_HOSTSEQUIV, "r");
E 20
D 12
	while (fgets(ahost, sizeof(ahost), hostf)) {
		if (cp = index(ahost, '\n'))
			*cp = '\0';
		cp = index(ahost, ' ');
		if (!strcmp(from, ahost) && cp == NULL) {
			(void) fclose(hostf);
D 6
			return(0);
E 6
I 6
			return;
E 12
I 12
again:
	if (hostf) {
D 17
		while (fgets(ahost, sizeof (ahost), hostf)) {
			if (cp = index(ahost, '\n'))
				*cp = '\0';
			cp = index(ahost, ' ');
			if (!strcmp(from, ahost) && cp == NULL) {
				(void) fclose(hostf);
				return;
			}
E 17
I 17
D 27
		if (!_validuser(hostf, ahost, DUMMY, DUMMY, baselen)) {
E 27
I 27
		if (__ivaliduser(hostf, f->sin_addr.s_addr,
		    DUMMY, DUMMY) == 0) {
E 27
			(void) fclose(hostf);
			return;
E 17
E 12
E 6
		}
I 12
		(void) fclose(hostf);
	}
	if (first == 1) {
		first = 0;
D 20
		hostf = fopen("/etc/hosts.lpd", "r");
E 20
I 20
		hostf = fopen(_PATH_HOSTSLPD, "r");
E 20
		goto again;
E 12
	}
D 6
	(void) fclose(hostf);
	return(-1);
E 6
I 6
	fatal("Your host does not have line printer access");
I 27
	/*NOTREACHED*/
E 27
E 6
D 5
}

/*
E 2
 * Convert network-format internet address
 * to base 256 d.d.d.d representation.
 */
D 4
char *
E 4
I 4
static char *
E 4
ntoa(in)
	struct in_addr in;
{
	static char b[18];
	register char *p;

	p = (char *)&in;
#define	UC(b)	(((int)b)&0xff)
	sprintf(b, "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3]));
	return (b);
E 5
D 13
}

/*VARARGS1*/
log(msg, a1, a2, a3)
	char *msg;
{
	short console = isatty(fileno(stderr));

	fprintf(stderr, console ? "\r\n%s: " : "%s: ", name);
	if (printer)
		fprintf(stderr, "%s: ", printer);
	fprintf(stderr, msg, a1, a2, a3);
	if (console)
		putc('\r', stderr);
	putc('\n', stderr);
	fflush(stderr);
}

I 4
static
E 4
D 6
logerror(msg)
E 6
I 6
logerr(msg)
E 6
	char *msg;
{
	register int err = errno;
	short console = isatty(fileno(stderr));
	extern int sys_nerr;
	extern char *sys_errlist[];

	fprintf(stderr, console ? "\r\n%s: " : "%s: ", name);
D 2
	if (*msg)
E 2
I 2
	if (msg)
E 2
		fprintf(stderr, "%s: ", msg);
	fputs(err < sys_nerr ? sys_errlist[err] : "Unknown error" , stderr);
	if (console)
		putc('\r', stderr);
	putc('\n', stderr);
	fflush(stderr);
E 13
}
I 28












E 28
E 1
