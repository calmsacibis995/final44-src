h24131
s 00005/00005/00269
d D 8.1 93/06/04 19:08:03 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00006/00263
d D 5.10 91/02/26 12:39:11 bostic 10 9
c ANSI fixes
e
s 00001/00011/00268
d D 5.9 90/06/01 15:56:11 bostic 9 8
c new copyright notice
e
s 00008/00006/00271
d D 5.8 89/05/17 13:28:17 bostic 8 7
c move out of uucp directory
e
s 00005/00006/00272
d D 5.7 89/05/11 13:44:54 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00028/00002/00250
d D 5.6 88/10/24 10:46:54 bostic 6 5
c add Berkeley copyright notice
e
s 00002/00054/00250
d D 5.5 88/04/05 12:32:23 rick 5 4
c remove 2.9BSD support
e
s 00092/00020/00212
d D 5.4 85/06/23 13:39:59 bloom 4 3
c fixes from rick adams and 2.9 support
e
s 00006/00004/00226
d D 5.3 85/04/10 15:22:03 ralph 3 2
c more changes from rick adams.
e
s 00210/00022/00020
d D 5.2 85/01/22 14:12:39 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00042/00000/00000
d D 5.1 84/08/31 11:25:19 ralph 1 0
c date and time created 84/08/31 11:25:19 by ralph
e
u
U
t
T
I 6
/*
D 11
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Adams.
 *
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
 */

E 6
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (BERKELEY) %G%";
E 2
I 2
D 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
I 5
D 6
static char sccsid[] = "%W%	(Berkeley) %G%";
E 5
E 2
#endif
E 6
I 6
D 11
char copyright[] =
"%Z% Copyright (c) 1985 The Regents of the University of California.\n\
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
"%Z% Copyright (c) 1985, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 11
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

/*
D 2
 * UUCP server daemon
 * 	Looks for attempts to connect on our uucp socket.  When it
 *	finds one it execs uucico to handle it.
 *
 * Invoked by inetd.
E 2
I 2
D 4
 * 4.2BSD TCP/IP server for uucico
E 4
I 4
D 5
 * 4.2BSD or 2.9BSD TCP/IP server for uucico
E 5
I 5
 * 4.2BSD TCP/IP server for uucico
E 5
E 4
 * uucico's TCP channel causes this server to be run at the remote end.
E 2
 */

D 2
#include <stdio.h>
#include <syslog.h>
E 2
I 2
D 8
#include "uucp.h"
I 4
#include <netdb.h>
D 5
#ifdef BSD2_9
#include <sys/localopts.h>
#include <sys/file.h>
#endif BSD2_9
E 5
E 4
#include <signal.h>
E 2
#include <errno.h>
E 8
I 8
#include <sys/types.h>
E 8
D 2
#include <sys/types.h>
E 2
I 2
D 3
#include <sys/param.h>
E 3
E 2
D 10
#include <sys/socket.h>
E 10
I 2
D 4
#include <sys/ioctl.h>
E 4
E 2
D 8
#include <netinet/in.h>
E 8
I 2
D 4
#include <netdb.h>
E 4
#include <sys/wait.h>
I 4
#include <sys/ioctl.h>
I 8
D 10
#include <sys/file.h>
E 10
I 10
#include <sys/socket.h>
E 10
#include <netinet/in.h>
I 10
#include <arpa/inet.h>
E 10
#include <netdb.h>
#include <signal.h>
D 10
#include <errno.h>
E 10
I 10
#include <fcntl.h>
#include <time.h>
E 10
E 8
E 4
#include <pwd.h>
I 10
#include <unistd.h>
#include <errno.h>
E 10
I 8
#include <stdio.h>
I 10
#include <stdlib.h>
#include <string.h>
E 10
E 8
D 7
#include <lastlog.h>
E 7
I 7
#include "pathnames.h"
E 7
E 2

I 4
D 5
#if !defined(BSD4_2) && !defined(BSD2_9)
--- You must have either BSD4_2 or BSD2_9 defined for this to work
#endif !BSD4_2 && !BSD2_9
#if defined(BSD4_2) && defined(BSD2_9)
--- You may not have both BSD4_2 and BSD2_9 defined for this to work
#endif	/* check for stupidity */

E 5
E 4
D 2
#define	UUCICO	"/usr/lib/uucp/uucico"
E 2
I 2
D 7
char lastlog[] = "/usr/adm/lastlog";
E 7
struct	sockaddr_in hisctladdr;
int hisaddrlen = sizeof hisctladdr;
struct	sockaddr_in myctladdr;
int mypid;
E 2

I 4
char Username[64];
char *nenv[] = {
	Username,
	NULL,
};
extern char **environ;

E 4
D 2
extern int errno;

E 2
main(argc, argv)
D 2
	int argc;
	char **argv;
E 2
I 2
int argc;
char **argv;
E 2
{
I 3
#ifndef BSDINETD
E 3
D 2
	int status, fromlen;
	struct sockaddr_in from;
E 2
I 2
	register int s, tcp_socket;
	struct servent *sp;
I 3
#endif !BSDINETD
E 3
	extern int errno;
	int dologout();
E 2

I 4
	environ = nenv;
E 4
D 2
	fromlen = sizeof(from);
	if (getpeername(0, &from, &fromlen) < 0) {
E 2
I 2
#ifdef BSDINETD
	close(1); close(2);
	dup(0); dup(0);
	hisaddrlen = sizeof (hisctladdr);
	if (getpeername(0, &hisctladdr, &hisaddrlen) < 0) {
E 2
		fprintf(stderr, "%s: ", argv[0]);
		perror("getpeername");
		_exit(1);
	}
D 2

	execl(UUCICO, "UUCICO", "-r0", "-v", 0);
	openlog("uucpd", 0, 0);
	syslog(LOG_ERR, "%s: %m", UUCICO);
E 2
I 2
	if (fork() == 0)
		doit(&hisctladdr);
	dologout();
E 2
	exit(1);
I 2
#else !BSDINETD
	sp = getservbyname("uucp", "tcp");
	if (sp == NULL){
		perror("uucpd: getservbyname");
		exit(1);
	}
I 4
	if (fork())
		exit(0);
E 4
D 7
	if ((s=open("/dev/tty", 2)) >= 0){
E 7
I 7
	if ((s=open(_PATH_TTY, 2)) >= 0){
E 7
		ioctl(s, TIOCNOTTY, (char *)0);
		close(s);
	}

	bzero((char *)&myctladdr, sizeof (myctladdr));
D 4
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0, 0);
	if ( tcp_socket<0 ) {
E 4
I 4
	myctladdr.sin_family = AF_INET;
	myctladdr.sin_port = sp->s_port;
#ifdef BSD4_2
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_socket < 0) {
E 4
		perror("uucpd: socket");
		exit(1);
	}
D 4
	myctladdr.sin_port = sp->s_port;
	if (bind(tcp_socket, (char *)&myctladdr, sizeof (myctladdr), 0) < 0) {
E 4
I 4
	if (bind(tcp_socket, (char *)&myctladdr, sizeof (myctladdr)) < 0) {
E 4
		perror("uucpd: bind");
		exit(1);
	}
I 4
	listen(tcp_socket, 3);	/* at most 3 simultaneuos uucp connections */
E 4
	signal(SIGCHLD, dologout);
D 4
	listen(tcp_socket, 5);	/* 5's as good as any */
E 4

	for(;;) {
		s = accept(tcp_socket, &hisctladdr, &hisaddrlen);
		if (s < 0){
D 4
			if (errno == EINTR)
E 4
I 4
			if (errno == EINTR) 
E 4
				continue;
			perror("uucpd: accept");
			exit(1);
		}
D 4
		if (fork()== 0) {
E 4
I 4
		if (fork() == 0) {
E 4
			close(0); close(1); close(2);
			dup(s); dup(s); dup(s);
D 4
			close(tcp_socket);close(s);
E 4
I 4
			close(tcp_socket); close(s);
E 4
			doit(&hisctladdr);
			exit(1);
		}
		close(s);
	}
D 4
#endif
E 4
I 4
#endif BSD4_2

D 5
#ifdef BSD2_9
	for(;;) {
		signal(SIGCHLD, dologout);
		s = socket(SOCK_STREAM, 0,  &myctladdr,
			SO_ACCEPTCONN|SO_KEEPALIVE);
		if (s < 0) {
			perror("uucpd: socket");
			exit(1);
		}
		if (accept(s, &hisctladdr) < 0) {
			if (errno == EINTR) {
				close(s);
				continue;
			}
			perror("uucpd: accept");
			exit(1);
		}
		if (fork() == 0) {
			close(0); close(1); close(2);
			dup(s); dup(s); dup(s);
			close(s);
			doit(&hisctladdr);
			exit(1);
		}
	}
#endif BSD2_9
E 5
#endif	!BSDINETD
E 4
}

doit(sinp)
struct sockaddr_in *sinp;
{
D 3
	char ebuf[32];
E 3
D 4
	char user[64];
	char passwd[64];
E 4
I 4
	char user[64], passwd[64];
E 4
	char *xpasswd, *crypt();
	struct passwd *pw, *getpwnam();

	alarm(60);
I 3
	printf("login: "); fflush(stdout);
E 3
	if (readline(user, sizeof user) < 0) {
		fprintf(stderr, "user read\n");
		return;
	}
	/* truncate username to 8 characters */
	user[8] = '\0';
	pw = getpwnam(user);
	if (pw == NULL) {
		fprintf(stderr, "user unknown\n");
		return;
	}
D 8
	if (strcmp(pw->pw_shell, UUCICO)) {
E 8
I 8
	if (strcmp(pw->pw_shell, _PATH_UUCICO)) {
E 8
		fprintf(stderr, "Login incorrect.");
		return;
	}
	if (pw->pw_passwd && *pw->pw_passwd != '\0') {
I 3
		printf("Password: "); fflush(stdout);
E 3
		if (readline(passwd, sizeof passwd) < 0) {
			fprintf(stderr, "passwd read\n");
			return;
		}
		xpasswd = crypt(passwd, pw->pw_passwd);
		if (strcmp(xpasswd, pw->pw_passwd)) {
			fprintf(stderr, "Login incorrect.");
			return;
		}
	}
	alarm(0);
I 4
	sprintf(Username, "USER=%s", user);
E 4
	dologin(pw, sinp);
D 4
	setegid(pw->pw_gid);
E 4
I 4
	setgid(pw->pw_gid);
#ifdef BSD4_2
E 4
	initgroups(pw->pw_name, pw->pw_gid);
I 4
#endif BSD4_2
E 4
	chdir(pw->pw_dir);
D 4
	seteuid(pw->pw_uid);
E 4
I 4
	setuid(pw->pw_uid);
#ifdef BSD4_2
E 4
	execl(UUCICO, "uucico", (char *)0);
I 4
#endif BSD4_2
D 5
#ifdef BSD2_9
	sprintf(passwd, "-h%s", inet_ntoa(sinp->sin_addr));
	execl(UUCICO, "uucico", passwd, (char *)0);
#endif BSD2_9
E 5
E 4
	perror("uucico server: execl");
}

readline(p, n)
D 3
	register char *p;
	register int n;
E 3
I 3
register char *p;
register int n;
E 3
{
	char c;

	while (n-- > 0) {
		if (read(0, &c, 1) <= 0)
			return(-1);
		c &= 0177;
		if (c == '\n' || c == '\r') {
			*p = '\0';
			return(0);
		}
		*p++ = c;
	}
	return(-1);
}

#include <utmp.h>
I 4
#ifdef BSD4_2
E 4
#include <fcntl.h>
I 4
#endif BSD4_2
E 4

I 4
D 5
#ifdef BSD2_9
#define O_APPEND	0 /* kludge */
#define wait3(a,b,c)	wait2(a,b)
#endif BSD2_9

E 5
E 4
#define	SCPYN(a, b)	strncpy(a, b, sizeof (a))

struct	utmp utmp;

dologout()
{
	union wait status;
	int pid, wtmp;

#ifdef BSDINETD
D 4
	while ((pid=wait(&status)) > 0 ) {
E 4
I 4
D 10
	while ((pid=wait(&status)) > 0) {
E 10
I 10
	while ((pid=wait((int *)&status)) > 0) {
E 10
E 4
#else  !BSDINETD
D 4
	while ((pid=wait3(&status,WNOHANG,0)) > 0 ) {
E 4
I 4
D 10
	while ((pid=wait3(&status,WNOHANG,0)) > 0) {
E 10
I 10
	while ((pid=wait3((int *)&status,WNOHANG,0)) > 0) {
E 10
E 4
#endif !BSDINETD
D 7
		wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
E 7
I 7
		wtmp = open(_PATH_WTMP, O_WRONLY|O_APPEND);
E 7
		if (wtmp >= 0) {
			sprintf(utmp.ut_line, "uucp%.4d", pid);
			SCPYN(utmp.ut_name, "");
			SCPYN(utmp.ut_host, "");
D 4
			utmp.ut_time = time(0);
E 4
I 4
			(void) time(&utmp.ut_time);
D 5
#ifdef BSD2_9
			(void) lseek(wtmp, 0L, 2);
#endif BSD2_9
E 5
E 4
			(void) write(wtmp, (char *)&utmp, sizeof (utmp));
			(void) close(wtmp);
		}
	}
}

/*
 * Record login in wtmp file.
 */
dologin(pw, sin)
struct passwd *pw;
struct sockaddr_in *sin;
{
	char line[32];
	char remotehost[32];
	int wtmp, f;
D 10
	struct hostent *hp = gethostbyaddr(&sin->sin_addr,
E 10
I 10
	struct hostent *hp = gethostbyaddr((char *)&sin->sin_addr,
E 10
		sizeof (struct in_addr), AF_INET);

	if (hp) {
		strncpy(remotehost, hp->h_name, sizeof (remotehost));
		endhostent();
	} else
		strncpy(remotehost, inet_ntoa(sin->sin_addr),
		    sizeof (remotehost));
D 7
	wtmp = open("/usr/adm/wtmp", O_WRONLY|O_APPEND);
E 7
I 7
	wtmp = open(_PATH_WTMP, O_WRONLY|O_APPEND);
E 7
	if (wtmp >= 0) {
		/* hack, but must be unique and no tty line */
		sprintf(line, "uucp%.4d", getpid());
		SCPYN(utmp.ut_line, line);
		SCPYN(utmp.ut_name, pw->pw_name);
		SCPYN(utmp.ut_host, remotehost);
D 4
		utmp.ut_time = time(0);
E 4
I 4
		time(&utmp.ut_time);
D 5
#ifdef BSD2_9
		(void) lseek(wtmp, 0L, 2);
#endif BSD2_9
E 5
E 4
		(void) write(wtmp, (char *)&utmp, sizeof (utmp));
		(void) close(wtmp);
	}
D 7
	if ((f = open(lastlog, 2)) >= 0) {
E 7
I 7
	if ((f = open(_PATH_LASTLOG, O_RDWR)) >= 0) {
E 7
		struct lastlog ll;

		time(&ll.ll_time);
		lseek(f, (long)pw->pw_uid * sizeof(struct lastlog), 0);
		strcpy(line, remotehost);
		SCPYN(ll.ll_line, line);
		SCPYN(ll.ll_host, remotehost);
		(void) write(f, (char *) &ll, sizeof ll);
		(void) close(f);
	}
E 2
}
E 1
