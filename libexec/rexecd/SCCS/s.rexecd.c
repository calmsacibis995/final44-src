h33796
s 00005/00005/00228
d D 8.1 93/06/04 18:58:42 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00226
d D 5.13 93/05/17 11:21:20 bostic 26 25
c rindex -> strrchr
e
s 00003/00001/00228
d D 5.12 91/02/25 17:27:01 bostic 25 24
c the last change broke the path stuff
e
s 00017/00018/00212
d D 5.11 91/02/25 17:13:14 bostic 24 23
c ANSI fixes
e
s 00001/00011/00229
d D 5.10 90/06/01 15:54:06 bostic 23 22
c new copyright notice
e
s 00001/00001/00239
d D 5.9 89/05/11 14:33:18 bostic 22 21
c file reorg, pathnames.h, paths.h
e
s 00004/00003/00236
d D 5.8 89/04/02 14:41:01 bostic 21 20
c add pathnames.h
e
s 00002/00002/00237
d D 5.7 89/01/04 12:15:46 bostic 20 19
c port should be a u_short; bug report 4.3BSD-tahoe/lib/18
e
s 00017/00006/00222
d D 5.6 88/09/27 22:17:40 bostic 19 18
c Berkeley copyright notice
e
s 00001/00001/00227
d D 5.5 87/10/22 10:37:59 bostic 18 17
c ANSI C; sprintf now returns an int.
e
s 00011/00017/00217
d D 5.4 86/05/09 03:08:04 lepreau 17 16
c setgid before initgroups; lint
e
s 00002/00002/00232
d D 5.3 85/10/25 10:18:02 bloom 16 15
c correct arguments to bind() and socket()
e
s 00001/00001/00233
d D 5.2 85/08/28 08:46:27 bloom 15 14
c reverse setuid and setgid
e
s 00014/00002/00220
d D 5.1 85/05/28 15:07:45 dist 14 13
c Add copyright
e
s 00002/00001/00220
d D 4.12 84/09/11 13:29:36 ralph 13 12
c don't close stdin.
e
s 00007/00052/00214
d D 4.11 84/04/11 15:58:11 karels 12 10
c convert for use with inetd
e
s 00000/00000/00266
d R 4.11 84/04/11 15:37:24 karels 11 10
c convert for inetd
e
s 00002/00002/00264
d D 4.10 83/07/02 00:19:05 sam 10 9
c include fixes
e
s 00001/00001/00265
d D 4.9 83/06/12 01:40:09 sam 9 8
c new signals
e
s 00003/00001/00263
d D 4.8 83/02/21 19:42:14 sam 8 7
c ignore SIGCHLD in child
e
s 00012/00003/00252
d D 4.7 83/01/22 16:23:48 sam 7 6
c reap children immediately
e
s 00001/00002/00254
d D 4.6 83/01/07 20:37:19 sam 6 5
c no more SIOCDONE
e
s 00001/00001/00255
d D 4.5 82/12/25 21:17:23 sam 5 4
c port numbers now byte swapped
e
s 00005/00006/00251
d D 4.4 82/11/15 18:32:08 sam 4 3
c fix socket calls and missing binding of socket used on fd 2
e
s 00001/00001/00256
d D 4.3 82/11/15 01:21:28 sam 3 2
c using wrong port for fd 2
e
s 00035/00029/00222
d D 4.2 82/11/14 15:09:42 sam 2 1
c convert to 4.1c sys calls and directory layout
e
s 00251/00000/00000
d D 4.1 82/04/02 10:28:55 wnj 1 0
c date and time created 82/04/02 10:28:55 by wnj
e
u
U
t
T
I 14
/*
D 19
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 19
I 19
D 27
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
D 23
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
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 19
 */

E 14
I 1
#ifndef lint
D 10
static char sccsid[] = "%W% %E%";
E 10
I 10
D 12
static char sccsid[] = "%W% (Berkeley) %E%";
E 12
I 12
D 14
static	char sccsid[] = "%W% (Berkeley) %G%";
E 12
E 10
#endif
E 14
I 14
D 27
char copyright[] =
D 19
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 19
I 19
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 19
 All rights reserved.\n";
E 27
I 27
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 27
D 19
#endif not lint
E 19
I 19
#endif /* not lint */
E 19

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 19
#endif not lint
E 19
I 19
#endif /* not lint */
E 19
E 14

D 2
#include <stdio.h>
E 2
D 24
#include <sys/ioctl.h>
E 24
#include <sys/param.h>
I 24
#include <sys/ioctl.h>
E 24
#include <sys/socket.h>
I 10
D 17
#include <sys/wait.h>
E 17
I 17
#include <sys/time.h>
I 26

E 26
E 17
E 10
D 2
#include <net/in.h>
E 2
I 2
D 24

E 24
#include <netinet/in.h>
D 24

#include <stdio.h>
E 2
#include <errno.h>
#include <pwd.h>
E 24
D 10
#include <wait.h>
E 10
D 26
#include <signal.h>
E 26
I 26

#include <errno.h>
E 26
I 2
#include <netdb.h>
I 26
#include <paths.h>
E 26
I 21
D 24
#include "pathnames.h"
E 24
I 24
#include <pwd.h>
D 26
#include <errno.h>
#include <unistd.h>
E 26
I 26
#include <signal.h>
E 26
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
D 26
#include <paths.h>
E 26
I 26
#include <unistd.h>
E 26
E 24
E 21
E 2

D 21
extern	errno;
E 21
I 21
D 24
extern	int errno;
E 21
D 2
struct	sockaddr_in sin = { AF_INET, IPPORT_EXECSERVER };
E 2
I 2
D 12
struct	sockaddr_in sin = { AF_INET };
E 12
E 2
struct	passwd *getpwnam();
D 17
char	*crypt(), *rindex(), *sprintf();
D 2
int	options = SO_ACCEPTCONN|SO_KEEPALIVE;
E 2
/* VARARGS 1 */
E 17
I 17
D 18
char	*crypt(), *rindex(), *strncat(), *sprintf();
E 18
I 18
char	*crypt(), *rindex(), *strncat();
E 24
E 18
/*VARARGS1*/
E 17
D 24
int	error();
E 24
I 24
int error();
E 24
I 7
D 17
int	reapchild();
E 17
I 17

E 17
E 7
/*
 * remote execute server:
 *	username\0
 *	password\0
 *	command\0
 *	data
 */
I 17
/*ARGSUSED*/
E 17
main(argc, argv)
	int argc;
	char **argv;
{
D 7
	union wait status;
E 7
D 12
	int f;
E 12
	struct sockaddr_in from;
I 2
D 12
	struct servent *sp;
E 12
I 12
	int fromlen;
E 12
E 2

I 2
D 12
	sp = getservbyname("exec", "tcp");
	if (sp == 0) {
		fprintf(stderr, "tcp/exec: unknown service\n");
E 12
I 12
	fromlen = sizeof (from);
D 24
	if (getpeername(0, &from, &fromlen) < 0) {
		fprintf(stderr, "%s: ", argv[0]);
		perror("getpeername");
E 24
I 24
	if (getpeername(0, (struct sockaddr *)&from, &fromlen) < 0) {
		(void)fprintf(stderr,
		    "rexecd: getpeername: %s\n", strerror(errno));
E 24
E 12
		exit(1);
	}
D 5
	sin.sin_port = htons((u_short)sp->s_port);
E 5
I 5
D 12
	sin.sin_port = sp->s_port;
E 5
E 2
#ifndef DEBUG
	if (fork())
		exit(0);
	for (f = 0; f < 10; f++)
		(void) close(f);
	(void) open("/", 0);
	(void) dup2(0, 1);
	(void) dup2(0, 2);
	{ int t = open("/dev/tty", 2);
	  if (t >= 0) {
		ioctl(t, TIOCNOTTY, (char *)0);
		(void) close(t);
	  }
	}
#endif
D 2
#if vax
	sin.sin_port = htons(sin.sin_port);
#endif
E 2
	argc--, argv++;
D 2
	if (argc > 0 && !strcmp(argv[0], "-d"))
		options |= SO_DEBUG;
E 2
I 2
D 4
	f = socket(0, SOCK_STREAM, 0, 0);
E 4
I 4
	f = socket(AF_INET, SOCK_STREAM, 0, 0);
E 4
	if (f < 0) {
		perror("rexecd: socket");
		exit(1);
	}
	if (bind(f, &sin, sizeof (sin), 0) < 0) {
		perror("rexecd: bind:");
		exit(1);
	}
I 7
D 9
	sigset(SIGCHLD, reapchild);
E 9
I 9
	signal(SIGCHLD, reapchild);
E 9
E 7
	listen(f, 10);
E 2
	for (;;) {
D 2
		errno = 0;
		f = socket(SOCK_STREAM, 0, &sin, options);
		if (f < 0) {
			perror("socket");
			sleep(5);
			continue;
		}
		if (accept(f, &from) < 0) {
			perror("accept");
			(void) close(f);
E 2
I 2
		int s, len = sizeof (from);

		s = accept(f, &from, &len, 0);
		if (s < 0) {
I 7
			if (errno == EINTR)
				continue;
E 7
			perror("rexecd: accept");
E 2
			sleep(1);
			continue;
		}
D 8
		if (fork() == 0)
E 8
I 8
		if (fork() == 0) {
			signal(SIGCHLD, SIG_IGN);
E 8
D 2
			doit(f, &from);
		(void) close(f);
		while(wait3(status, WNOHANG, 0) > 0)
E 2
I 2
			doit(s, &from);
I 8
		}
E 8
		(void) close(s);
D 7
		while (wait3(status, WNOHANG, 0) > 0)
E 2
			continue;
E 7
	}
E 12
I 12
	doit(0, &from);
E 12
I 7
}

D 17
reapchild()
{
	union wait status;

	while (wait3(&status, WNOHANG, 0) > 0)
		;
E 7
}

E 17
char	username[20] = "USER=";
char	homedir[64] = "HOME=";
char	shell[64] = "SHELL=";
I 25
char	path[sizeof(_PATH_DEFPATH) + sizeof("PATH=")] = "PATH=";
E 25
char	*envinit[] =
D 21
	    {homedir, shell, "PATH=:/usr/ucb:/bin:/usr/bin", username, 0};
E 21
I 21
D 25
	    {homedir, shell, _PATH_DEFPATH, username, 0};
E 25
I 25
	    {homedir, shell, path, username, 0};
E 25
E 21
char	**environ;

struct	sockaddr_in asin = { AF_INET };

doit(f, fromp)
	int f;
	struct sockaddr_in *fromp;
{
	char cmdbuf[NCARGS+1], *cp, *namep;
	char user[16], pass[16];
	struct passwd *pwd;
	int s;
D 20
	short port;
E 20
I 20
	u_short port;
E 20
	int pv[2], pid, ready, readfrom, cc;
	char buf[BUFSIZ], sig;
	int one = 1;

	(void) signal(SIGINT, SIG_DFL);
	(void) signal(SIGQUIT, SIG_DFL);
	(void) signal(SIGTERM, SIG_DFL);
#ifdef DEBUG
D 22
	{ int t = open("/dev/tty", 2);
E 22
I 22
	{ int t = open(_PATH_TTY, 2);
E 22
	  if (t >= 0) {
		ioctl(t, TIOCNOTTY, (char *)0);
		(void) close(t);
	  }
	}
#endif
	dup2(f, 0);
	dup2(f, 1);
	dup2(f, 2);
D 4
#if vax
	fromp->sin_port = ntohs((u_short)fromp->sin_port);
#endif
E 4
	(void) alarm(60);
	port = 0;
	for (;;) {
		char c;
		if (read(f, &c, 1) != 1)
			exit(1);
		if (c == 0)
			break;
		port = port * 10 + c - '0';
	}
	(void) alarm(0);
	if (port != 0) {
D 4
		s = socket(SOCK_STREAM, 0, &asin, 0);
E 4
I 4
D 16
		s = socket(AF_INET, SOCK_STREAM, 0, 0);
E 16
I 16
		s = socket(AF_INET, SOCK_STREAM, 0);
E 16
E 4
		if (s < 0)
			exit(1);
I 4
D 16
		if (bind(s, &asin, sizeof (asin), 0) < 0)
E 16
I 16
D 24
		if (bind(s, &asin, sizeof (asin)) < 0)
E 24
I 24
		if (bind(s, (struct sockaddr *)&asin, sizeof (asin)) < 0)
E 24
E 16
			exit(1);
E 4
		(void) alarm(60);
D 2
		fromp->sin_port = port;
#if vax
		fromp->sin_port = ntohs(fromp->sin_port);
#endif
		if (connect(s, fromp) < 0)
E 2
I 2
D 3
		fromp->sin_port = ntohs((u_short)fromp->sin_port);
E 3
I 3
D 4
		fromp->sin_port = ntohs((u_short)port);
E 4
I 4
D 20
		fromp->sin_port = htons((u_short)port);
E 20
I 20
		fromp->sin_port = htons(port);
E 20
E 4
E 3
D 17
		if (connect(s, fromp, sizeof (*fromp), 0) < 0)
E 17
I 17
D 24
		if (connect(s, fromp, sizeof (*fromp)) < 0)
E 24
I 24
		if (connect(s, (struct sockaddr *)fromp, sizeof (*fromp)) < 0)
E 24
E 17
E 2
			exit(1);
		(void) alarm(0);
	}
	getstr(user, sizeof(user), "username");
	getstr(pass, sizeof(pass), "password");
	getstr(cmdbuf, sizeof(cmdbuf), "command");
	setpwent();
	pwd = getpwnam(user);
	if (pwd == NULL) {
		error("Login incorrect.\n");
		exit(1);
	}
	endpwent();
	if (*pwd->pw_passwd != '\0') {
		namep = crypt(pass, pwd->pw_passwd);
		if (strcmp(namep, pwd->pw_passwd)) {
			error("Password incorrect.\n");
			exit(1);
		}
	}
	if (chdir(pwd->pw_dir) < 0) {
		error("No remote directory.\n");
		exit(1);
	}
	(void) write(2, "\0", 1);
	if (port) {
		(void) pipe(pv);
		pid = fork();
		if (pid == -1)  {
			error("Try again.\n");
			exit(1);
		}
		if (pid) {
			(void) close(0); (void) close(1); (void) close(2);
			(void) close(f); (void) close(pv[1]);
			readfrom = (1<<s) | (1<<pv[0]);
			ioctl(pv[1], FIONBIO, (char *)&one);
			/* should set s nbio! */
			do {
				ready = readfrom;
D 2
				(void) select(32, &ready, 0, 1000000);
E 2
I 2
D 17
				(void) select(16, &ready, 0, 0, 0);
E 17
I 17
D 24
				(void) select(16, &ready, (fd_set *)0,
				    (fd_set *)0, (struct timeval *)0);
E 24
I 24
				(void) select(16, (fd_set *)&ready,
				    (fd_set *)NULL, (fd_set *)NULL,
				    (struct timeval *)NULL);
E 24
E 17
E 2
				if (ready & (1<<s)) {
					if (read(s, &sig, 1) <= 0)
						readfrom &= ~(1<<s);
					else
						killpg(pid, sig);
				}
				if (ready & (1<<pv[0])) {
					cc = read(pv[0], buf, sizeof (buf));
					if (cc <= 0) {
D 6
						int done = 1+1;
						ioctl(s, SIOCDONE, (char *)&done);
E 6
I 6
						shutdown(s, 1+1);
E 6
						readfrom &= ~(1<<pv[0]);
					} else
						(void) write(s, buf, cc);
				}
			} while (readfrom);
			exit(0);
		}
		setpgrp(0, getpid());
		(void) close(s); (void)close(pv[0]);
		dup2(pv[1], 2);
	}
	if (*pwd->pw_shell == '\0')
D 21
		pwd->pw_shell = "/bin/sh";
E 21
I 21
		pwd->pw_shell = _PATH_BSHELL;
E 21
D 13
	(void) close(f);
E 13
I 13
	if (f > 2)
		(void) close(f);
I 17
	(void) setgid((gid_t)pwd->pw_gid);
E 17
E 13
D 2
	inigrp(pwd->pw_name, pwd->pw_gid);
E 2
I 2
	initgroups(pwd->pw_name, pwd->pw_gid);
E 2
D 15
	(void) setuid(pwd->pw_uid);
E 15
D 17
	(void) setgid(pwd->pw_gid);
I 15
	(void) setuid(pwd->pw_uid);
E 17
I 17
	(void) setuid((uid_t)pwd->pw_uid);
I 25
	(void)strcat(path, _PATH_DEFPATH);
E 25
E 17
E 15
	environ = envinit;
	strncat(homedir, pwd->pw_dir, sizeof(homedir)-6);
	strncat(shell, pwd->pw_shell, sizeof(shell)-7);
	strncat(username, pwd->pw_name, sizeof(username)-6);
D 26
	cp = rindex(pwd->pw_shell, '/');
E 26
I 26
	cp = strrchr(pwd->pw_shell, '/');
E 26
	if (cp)
		cp++;
	else
		cp = pwd->pw_shell;
	execl(pwd->pw_shell, cp, "-c", cmdbuf, 0);
	perror(pwd->pw_shell);
	exit(1);
}

D 17
/* VARARGS 1 */
E 17
I 17
/*VARARGS1*/
E 17
error(fmt, a1, a2, a3)
	char *fmt;
	int a1, a2, a3;
{
	char buf[BUFSIZ];

	buf[0] = 1;
	(void) sprintf(buf+1, fmt, a1, a2, a3);
	(void) write(2, buf, strlen(buf));
}

getstr(buf, cnt, err)
	char *buf;
	int cnt;
	char *err;
{
	char c;

	do {
		if (read(0, &c, 1) != 1)
			exit(1);
		*buf++ = c;
		if (--cnt == 0) {
			error("%s too long\n", err);
			exit(1);
		}
	} while (c != 0);
}
E 1
