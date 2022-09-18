h44931
s 00005/00005/00377
d D 8.3 94/03/26 06:24:42 bostic 43 42
c change "ahost" name to "buf", pick a reasonable length
c I don't know why this code gets people so upset...
e
s 00006/00000/00376
d D 8.2 94/03/17 08:16:52 bostic 42 39
c skip lines that are too long
c should be logged, it's probably an attempt to crack the system.
e
s 00001/00002/00374
d R 8.2 93/11/16 12:01:46 bostic 41 39
c While installing rdist v6, I noticed that a file descriptor leak in
c rcmd.c documented in the README still existed in the bsd source. A
c context diff is appended.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00001/00002/00374
d R 8.2 93/11/16 11:59:23 bostic 40 39
c While installing rdist v6, I noticed that a file descriptor leak in
c rcmd.c documented in the READM still existed in the bsd source. A
c context diff is appended.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00002/00002/00374
d D 8.1 93/06/04 12:51:06 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00373
d D 5.28 93/02/13 10:18:58 bostic 38 37
c POSIX notation for file permissions and type
e
s 00004/00003/00372
d D 5.27 93/01/09 10:32:26 bostic 37 36
c pid's should be stored in pid_t's; from Craig Leres
e
s 00012/00010/00363
d D 5.26 92/06/30 18:34:53 bostic 36 35
c use a temporary variable for the error, in case already set
c from Craig Leres
e
s 00166/00118/00207
d D 5.25 92/06/30 16:38:35 leres 35 34
c add iruserok; from Van and Craig
e
s 00001/00000/00324
d D 5.24 91/02/24 13:14:37 bostic 34 33
c need ctype.h, shouldn't have deleted it
e
s 00015/00019/00309
d D 5.23 91/02/24 12:40:20 bostic 33 32
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00327
d D 5.22 90/06/01 14:16:25 bostic 32 31
c new copyright notice
e
s 00001/00001/00337
d D 5.21 90/05/21 16:58:23 bostic 31 30
c put pathnames into netdb.h
e
s 00018/00003/00320
d D 5.20 89/01/24 11:56:43 karels 30 29
c don't hang if 2nd connection doesn't arrive before first closes down
e
s 00018/00008/00305
d D 5.19 88/12/08 10:35:18 bostic 29 28
c sockaddr's now require length (K. Sklower);
c add _check_rhosts_file flag for rshd and rlogind; don't use .rhosts if owned
c by someone other than user or root, or if writeable by anyone but the owner
e
s 00001/00001/00312
d D 5.18 88/10/11 13:35:59 bostic 28 27
c use herror routine
e
s 00010/00005/00303
d D 5.17 88/06/27 17:14:09 bostic 27 26
c install approved copyright notice
e
s 00009/00003/00299
d D 5.16 88/03/07 21:17:15 bostic 26 25
c added Berkeley specific header
e
s 00001/00001/00301
d D 5.15 87/11/07 15:45:42 karels 25 24
c minor cleanup
e
s 00001/00001/00301
d D 5.14 87/10/22 17:43:22 bostic 24 23
c ANSI C; sprintf now returns an int.
e
s 00008/00007/00294
d D 5.13 87/09/30 12:27:22 bostic 23 22
c null pointer fix; bug report 4.3BSD/lib/23
e
s 00002/00001/00299
d D 5.12 87/09/30 10:44:55 bostic 22 21
c signals are longs; bug report 4.3BSD/lib/38
e
s 00041/00025/00259
d D 5.11 86/05/06 14:35:11 bloom 21 20
c separate reading of file into its own routine, lpd needed it
e
s 00040/00016/00244
d D 5.10 86/03/30 16:38:13 karels 20 19
c set socket pgrp to avoid races; block SIGURG till done;
c try alternate addresses
e
s 00002/00002/00258
d D 5.9 86/03/09 20:27:05 donn 19 18
c added LIBC_SCCS condition for sccs ids
e
s 00001/00001/00259
d D 5.8 85/10/25 10:28:13 bloom 18 17
c bind has only 3 args now
e
s 00001/00001/00259
d D 5.7 85/09/17 20:07:56 karels 17 16
c I know it works, but ...
e
s 00007/00005/00253
d D 5.6 85/09/10 20:36:17 karels 16 15
c make rresvport always quiet, rcmd do perror on failure;
c don't lose more file descriptors
e
s 00017/00001/00241
d D 5.5 85/09/09 19:42:50 bloom 15 14
c check ownership of .rhosts
e
s 00002/00001/00240
d D 5.4 85/09/09 16:29:08 bloom 14 13
c fix problem with hostname returning name w/o a domain
e
s 00052/00005/00189
d D 5.3 85/09/06 16:50:46 bloom 13 12
c fix ruserok to handle case independent comparisons and for domain naming
e
s 00005/00003/00189
d D 5.2 85/09/06 11:47:13 karels 12 11
c no retries or perror if EADDRNOTAVAIL, so can fail gracefully if no net
e
s 00008/00002/00184
d D 5.1 85/05/30 14:23:08 dist 11 10
c Add copyright
e
s 00016/00006/00170
d D 4.10 85/05/30 12:01:05 bloom 10 9
c make .rhosts a bit more forgiving
e
s 00009/00011/00167
d D 4.9 84/12/07 09:28:19 ralph 9 8
c fix file closes so multiple rcmd's work.
e
s 00000/00006/00178
d D 4.8 83/03/19 14:21:21 sam 8 7
c purge socketaddr call in favor of getsockname
e
s 00009/00008/00175
d D 4.7 83/02/23 13:51:23 sam 7 6
c super user uses only .rhosts for validation
e
s 00005/00001/00178
d D 4.6 83/01/22 18:59:54 sam 6 5
c a bit more careful about write errors
e
s 00008/00012/00171
d D 4.5 83/01/13 17:50:56 sam 5 4
c eliminate socketaddr and options
e
s 00002/00002/00181
d D 4.4 82/12/17 17:06:43 sam 4 3
c pass port numbers around in network order
e
s 00050/00027/00133
d D 4.3 82/11/14 13:55:34 sam 3 2
c merge off 4.1b with 4.1c; and random conversion to netdb library
e
s 00010/00018/00150
d D 4.2 82/10/07 23:42:06 sam 2 1
c use new date base routines
e
s 00168/00000/00000
d D 4.1 82/04/02 10:28:51 wnj 1 0
c date and time created 82/04/02 10:28:51 by wnj
e
u
U
t
T
I 11
/*
D 39
 * Copyright (c) 1983 Regents of the University of California.
D 26
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 26
I 26
 * All rights reserved.
E 39
I 39
D 43
 * Copyright (c) 1983, 1993
E 43
I 43
 * Copyright (c) 1983, 1993, 1994
E 43
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
D 32
 * Redistribution and use in source and binary forms are permitted
D 27
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 27
I 27
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
E 32
I 32
 * %sccs.include.redist.c%
E 32
E 27
E 26
 */

E 11
I 1
D 19
#ifndef lint
E 19
I 19
#if defined(LIBC_SCCS) && !defined(lint)
E 19
D 3
static char sccsid[] = "%W% %E%";
E 3
I 3
D 11
static char sccsid[] = "%W% %G%";
E 3
#endif
E 11
I 11
static char sccsid[] = "%W% (Berkeley) %G%";
D 19
#endif not lint
E 19
I 19
D 26
#endif LIBC_SCCS and not lint
E 26
I 26
#endif /* LIBC_SCCS and not lint */
E 26
E 19
E 11

D 33
#include <stdio.h>
D 13
#include <sys/types.h>
E 13
I 13
#include <ctype.h>
I 15
#include <pwd.h>
E 33
E 15
#include <sys/param.h>
I 20
D 33
#include <sys/file.h>
#include <sys/signal.h>
E 33
E 20
E 13
#include <sys/socket.h>
I 15
#include <sys/stat.h>
I 35

E 35
E 15
D 3
#include <net/in.h>
#include <errno.h>
E 3
I 3
D 33

E 33
#include <netinet/in.h>
D 33

E 33
I 33
#include <arpa/inet.h>
I 35

E 35
#include <signal.h>
#include <fcntl.h>
E 33
E 3
I 2
#include <netdb.h>
I 35
#include <unistd.h>
E 35
I 33
#include <pwd.h>
E 33
I 3
#include <errno.h>
I 33
#include <stdio.h>
I 34
#include <ctype.h>
E 34
D 35
#include <unistd.h>
E 35
#include <string.h>
E 33
E 3
E 2

I 35
int	__ivaliduser __P((FILE *, u_long, const char *, const char *));
static int __icheckhost __P((u_long, char *));

int
E 35
D 33
extern	errno;
D 24
char	*index(), *sprintf();
E 24
I 24
char	*index();
E 24
D 5
int	rcmdoptions;
E 5

E 33
rcmd(ahost, rport, locuser, remuser, cmd, fd2p)
	char **ahost;
D 21
	int rport;
E 21
I 21
	u_short rport;
E 21
D 33
	char *locuser, *remuser, *cmd;
E 33
I 33
	const char *locuser, *remuser, *cmd;
E 33
	int *fd2p;
{
D 3
	int s, addr, timo = 1;
E 3
I 3
D 20
	int s, timo = 1;
E 20
I 20
D 22
	int s, timo = 1, pid, oldmask;
E 22
I 22
D 35
	int s, timo = 1, pid;
	long oldmask;
E 22
E 20
E 3
	struct sockaddr_in sin, sin2, from;
	char c;
D 5
	short port;
E 5
I 3
	int lport = IPPORT_RESERVED - 1;
E 35
E 3
I 2
	struct hostent *hp;
I 35
	struct sockaddr_in sin, from;
E 35
I 30
	fd_set reads;
I 35
	long oldmask;
D 37
	int s, lport, pid, timo;
E 37
I 37
	pid_t pid;
	int s, lport, timo;
E 37
	char c;
E 35
E 30
E 2

I 20
	pid = getpid();
E 20
D 2
	addr = rhost(ahost);
	if (addr == -1) {
E 2
I 2
	hp = gethostbyname(*ahost);
D 35
	if (hp == 0) {
E 35
I 35
	if (hp == NULL) {
E 35
E 2
D 28
		fprintf(stderr, "%s: unknown host\n", *ahost);
E 28
I 28
		herror(*ahost);
E 28
		return (-1);
	}
I 2
	*ahost = hp->h_name;
E 2
D 20
retry:
D 3
	s = rresvport(rcmdoptions|SO_KEEPALIVE);
E 3
I 3
D 5
	s = rresvport(rcmdoptions|SO_KEEPALIVE, &lport);
E 5
I 5
	s = rresvport(&lport);
E 5
E 3
D 16
	if (s < 0)
E 16
I 16
	if (s < 0) {
		if (errno == EAGAIN)
			fprintf(stderr, "socket: All ports in use\n");
		else
			perror("rcmd: socket");
E 16
		return (-1);
I 16
	}
E 16
D 2
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = addr;
	sin.sin_port = rport;
#ifdef vax
	sin.sin_port = htons(sin.sin_port);
#endif
E 2
I 2
	sin.sin_family = hp->h_addrtype;
D 3
	bcopy(hp->h_addr, &sin.sin_addr, hp->h_length);
	sin.sin_port = htons(rport);
E 2
	if (connect(s, &sin) < 0) {
E 3
I 3
	bcopy(hp->h_addr, (caddr_t)&sin.sin_addr, hp->h_length);
D 4
	sin.sin_port = htons((u_short)rport);
E 4
I 4
	sin.sin_port = rport;
E 4
	if (connect(s, (caddr_t)&sin, sizeof (sin), 0) < 0) {
E 20
I 20
	oldmask = sigblock(sigmask(SIGURG));
D 35
	for (;;) {
E 35
I 35
	for (timo = 1, lport = IPPORT_RESERVED - 1;;) {
E 35
		s = rresvport(&lport);
		if (s < 0) {
			if (errno == EAGAIN)
D 35
				fprintf(stderr, "socket: All ports in use\n");
E 35
I 35
				(void)fprintf(stderr,
				    "rcmd: socket: All ports in use\n");
E 35
			else
D 35
				perror("rcmd: socket");
E 35
I 35
				(void)fprintf(stderr, "rcmd: socket: %s\n",
				    strerror(errno));
E 35
			sigsetmask(oldmask);
			return (-1);
		}
		fcntl(s, F_SETOWN, pid);
		sin.sin_family = hp->h_addrtype;
D 35
		bcopy(hp->h_addr_list[0], (caddr_t)&sin.sin_addr, hp->h_length);
E 35
I 35
		bcopy(hp->h_addr_list[0], &sin.sin_addr, hp->h_length);
E 35
		sin.sin_port = rport;
D 33
		if (connect(s, (caddr_t)&sin, sizeof (sin), 0) >= 0)
E 33
I 33
		if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) >= 0)
E 33
			break;
E 20
I 9
D 35
		(void) close(s);
E 35
I 35
		(void)close(s);
E 35
E 9
		if (errno == EADDRINUSE) {
D 9
			close(s);
E 9
			lport--;
D 20
			goto retry;
E 20
I 20
			continue;
E 20
		}
E 3
		if (errno == ECONNREFUSED && timo <= 16) {
D 9
			(void) close(s);
E 9
D 35
			sleep(timo);
E 35
I 35
			(void)sleep(timo);
E 35
			timo *= 2;
D 20
			goto retry;
E 20
I 20
			continue;
E 20
		}
I 20
		if (hp->h_addr_list[1] != NULL) {
			int oerrno = errno;

D 35
			fprintf(stderr,
			    "connect to address %s: ", inet_ntoa(sin.sin_addr));
E 35
I 35
			(void)fprintf(stderr, "connect to address %s: ",
			    inet_ntoa(sin.sin_addr));
E 35
			errno = oerrno;
			perror(0);
			hp->h_addr_list++;
D 35
			bcopy(hp->h_addr_list[0], (caddr_t)&sin.sin_addr,
			    hp->h_length);
			fprintf(stderr, "Trying %s...\n",
				inet_ntoa(sin.sin_addr));
E 35
I 35
			bcopy(hp->h_addr_list[0], &sin.sin_addr, hp->h_length);
			(void)fprintf(stderr, "Trying %s...\n",
			    inet_ntoa(sin.sin_addr));
E 35
			continue;
		}
E 20
D 3
		perror(*ahost);
E 3
I 3
D 35
		perror(hp->h_name);
E 35
I 35
		(void)fprintf(stderr, "%s: %s\n", hp->h_name, strerror(errno));
E 35
I 20
		sigsetmask(oldmask);
E 20
E 3
		return (-1);
	}
I 3
	lport--;
E 3
	if (fd2p == 0) {
		write(s, "", 1);
D 5
		port = 0;
E 5
I 5
		lport = 0;
E 5
	} else {
		char num[8];
D 3
		int s2 = rresvport(rcmdoptions|SO_ACCEPTCONN);
E 3
I 3
D 5
		int s2 = rresvport(rcmdoptions|SO_ACCEPTCONN, &lport), s3;
E 5
I 5
		int s2 = rresvport(&lport), s3;
I 9
D 35
		int len = sizeof (from);
E 35
I 35
		int len = sizeof(from);
E 35
E 9
E 5
E 3

D 9
		if (s2 < 0) {
			(void) close(s);
			return (-1);
		}
E 9
I 9
		if (s2 < 0)
			goto bad;
E 9
I 3
		listen(s2, 1);
E 3
D 5
		socketaddr(s2, &sin2);
D 2
		port = sin2.sin_port;
#if vax
		port = htons((u_short)port);
#endif
E 2
I 2
		port = htons((u_short)sin2.sin_port);
E 2
		(void) sprintf(num, "%d", port);
E 5
I 5
D 35
		(void) sprintf(num, "%d", lport);
E 35
I 35
		(void)snprintf(num, sizeof(num), "%d", lport);
E 35
E 5
D 6
		(void) write(s, num, strlen(num)+1);
E 6
I 6
		if (write(s, num, strlen(num)+1) != strlen(num)+1) {
D 35
			perror("write: setting up stderr");
			(void) close(s2);
E 35
I 35
			(void)fprintf(stderr,
			    "rcmd: write (setting up stderr): %s\n",
			    strerror(errno));
			(void)close(s2);
E 35
			goto bad;
		}
I 30
		FD_ZERO(&reads);
		FD_SET(s, &reads);
		FD_SET(s2, &reads);
		errno = 0;
D 35
		if (select(32, &reads, 0, 0, 0) < 1 ||
		    !FD_ISSET(s2, &reads)) {
E 35
I 35
		if (select(32, &reads, 0, 0, 0) < 1 || !FD_ISSET(s2, &reads)) {
E 35
			if (errno != 0)
D 35
				perror("select: setting up stderr");
E 35
I 35
				(void)fprintf(stderr,
				    "rcmd: select (setting up stderr): %s\n",
				    strerror(errno));
E 35
			else
D 35
			    fprintf(stderr,
				"select: protocol failure in circuit setup.\n");
			(void) close(s2);
E 35
I 35
				(void)fprintf(stderr,
				"select: protocol failure in circuit setup\n");
			(void)close(s2);
E 35
			goto bad;
		}
E 30
E 6
D 3
		if (accept(s2, &from) < 0) {
E 3
I 3
D 9
		{ int len = sizeof (from);
		  s3 = accept(s2, &from, &len, 0);
		  close(s2);
		  if (s3 < 0) {
E 9
I 9
D 33
		s3 = accept(s2, &from, &len, 0);
E 33
I 33
		s3 = accept(s2, (struct sockaddr *)&from, &len);
E 33
D 35
		(void) close(s2);
E 35
I 35
		(void)close(s2);
E 35
		if (s3 < 0) {
E 9
E 3
D 35
			perror("accept");
E 35
I 35
			(void)fprintf(stderr,
			    "rcmd: accept: %s\n", strerror(errno));
E 35
I 3
D 5
			port = 0;
E 5
I 5
			lport = 0;
E 5
E 3
			goto bad;
I 3
D 9
		  }
E 9
E 3
		}
D 2
#if vax
E 2
D 3
		from.sin_port = ntohs(from.sin_port);
E 3
I 3
		*fd2p = s3;
		from.sin_port = ntohs((u_short)from.sin_port);
E 3
D 2
#endif
E 2
		if (from.sin_family != AF_INET ||
D 30
		    from.sin_port >= IPPORT_RESERVED) {
E 30
I 30
		    from.sin_port >= IPPORT_RESERVED ||
		    from.sin_port < IPPORT_RESERVED / 2) {
E 30
D 35
			fprintf(stderr,
E 35
I 35
			(void)fprintf(stderr,
E 35
			    "socket: protocol failure in circuit setup.\n");
D 3
			goto bad;
E 3
I 3
			goto bad2;
E 3
		}
D 3
		*fd2p = s2;
E 3
	}
D 35
	(void) write(s, locuser, strlen(locuser)+1);
	(void) write(s, remuser, strlen(remuser)+1);
	(void) write(s, cmd, strlen(cmd)+1);
E 35
I 35
	(void)write(s, locuser, strlen(locuser)+1);
	(void)write(s, remuser, strlen(remuser)+1);
	(void)write(s, cmd, strlen(cmd)+1);
E 35
	if (read(s, &c, 1) != 1) {
D 35
		perror(*ahost);
E 35
I 35
		(void)fprintf(stderr,
		    "rcmd: %s: %s\n", *ahost, strerror(errno));
E 35
D 3
		goto bad;
E 3
I 3
		goto bad2;
E 3
	}
	if (c != 0) {
		while (read(s, &c, 1) == 1) {
D 37
			(void) write(2, &c, 1);
E 37
I 37
			(void)write(STDERR_FILENO, &c, 1);
E 37
			if (c == '\n')
				break;
		}
D 3
		goto bad;
E 3
I 3
		goto bad2;
E 3
	}
I 20
	sigsetmask(oldmask);
E 20
	return (s);
D 3
bad:
E 3
I 3
bad2:
E 3
D 5
	if (port)
E 5
I 5
	if (lport)
E 5
D 35
		(void) close(*fd2p);
E 35
I 35
		(void)close(*fd2p);
E 35
I 3
bad:
E 3
D 35
	(void) close(s);
E 35
I 35
	(void)close(s);
E 35
I 20
	sigsetmask(oldmask);
E 20
	return (-1);
}

I 35
int
E 35
D 3
rresvport(options)
	int options;
E 3
I 3
D 5
rresvport(options, alport)
	int options, *alport;
E 5
I 5
rresvport(alport)
	int *alport;
E 5
E 3
{
	struct sockaddr_in sin;
D 3
	short lport = IPPORT_RESERVED - 1;
E 3
	int s;

I 3
	sin.sin_family = AF_INET;
I 29
D 30
	sin.sin_len = sizeof(sin);
E 30
E 29
D 12
	sin.sin_addr.s_addr = 0;
D 4
	s = socket(0, SOCK_STREAM, 0, 0);
E 4
I 4
	s = socket(AF_INET, SOCK_STREAM, 0, 0);
E 12
I 12
	sin.sin_addr.s_addr = INADDR_ANY;
	s = socket(AF_INET, SOCK_STREAM, 0);
E 12
E 4
	if (s < 0)
		return (-1);
E 3
	for (;;) {
D 3
		sin.sin_family = AF_INET;
D 2
		sin.sin_port = lport;
E 2
I 2
		sin.sin_port = htons(lport);
E 2
		sin.sin_addr.s_addr = 0;
D 2
#ifdef vax
		sin.sin_port = htons(sin.sin_port);
#endif
E 2
		s = socket(SOCK_STREAM, 0, &sin, options);
		if (s >= 0)
E 3
I 3
		sin.sin_port = htons((u_short)*alport);
D 18
		if (bind(s, (caddr_t)&sin, sizeof (sin), 0) >= 0)
E 18
I 18
D 33
		if (bind(s, (caddr_t)&sin, sizeof (sin)) >= 0)
E 33
I 33
D 37
		if (bind(s, (struct sockaddr *)&sin, sizeof (sin)) >= 0)
E 37
I 37
		if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) >= 0)
E 37
E 33
E 18
E 3
			return (s);
D 12
		if (errno != EADDRINUSE && errno != EADDRNOTAVAIL) {
E 12
I 12
D 16
		if (errno == EADDRNOTAVAIL)
			return (-1);
E 16
		if (errno != EADDRINUSE) {
E 12
D 16
			perror("socket");
E 16
I 9
D 35
			(void) close(s);
E 35
I 35
			(void)close(s);
E 35
E 9
			return (-1);
		}
D 3
		lport--;
		if (lport == IPPORT_RESERVED/2) {
E 3
I 3
		(*alport)--;
		if (*alport == IPPORT_RESERVED/2) {
E 3
D 16
			fprintf(stderr, "socket: All ports in use\n");
E 16
I 9
D 35
			(void) close(s);
E 35
I 35
			(void)close(s);
E 35
I 16
			errno = EAGAIN;		/* close */
E 16
E 9
			return (-1);
		}
	}
}

I 29
D 35
int	_check_rhosts_file = 1;
E 35
I 35
int	__check_rhosts_file = 1;
char	*__rcmd_errstr;
E 35

I 35
int
E 35
E 29
D 7
ruserok(rhost, ruser, luser)
	char *rhost, *ruser, *luser;
E 7
I 7
ruserok(rhost, superuser, ruser, luser)
D 33
	char *rhost;
E 33
I 33
	const char *rhost, *ruser, *luser;
E 33
	int superuser;
D 33
	char *ruser, *luser;
E 33
E 7
{
D 35
	FILE *hostf;
D 13
	char ahost[32];
E 13
I 13
	char fhost[MAXHOSTNAMELEN];
D 21
	char ahost[MAXHOSTNAMELEN];
E 21
E 13
	int first = 1;
I 13
	register char *sp, *p;
	int baselen = -1;
E 35
I 35
	struct hostent *hp;
	u_long addr;
	char **ap;
E 35
E 13

I 13
D 33
	sp = rhost;
E 33
I 33
D 35
	sp = (char *)rhost;
E 33
	p = fhost;
	while (*sp) {
		if (*sp == '.') {
			if (baselen == -1)
				baselen = sp - rhost;
			*p++ = *sp++;
		} else {
			*p++ = isupper(*sp) ? tolower(*sp++) : *sp++;
		}
E 35
I 35
	if ((hp = gethostbyname(rhost)) == NULL)
		return (-1);
	for (ap = hp->h_addr_list; *ap; ++ap) {
		bcopy(*ap, &addr, sizeof(addr));
		if (iruserok(addr, superuser, ruser, luser) == 0)
			return (0);
E 35
	}
D 35
	*p = '\0';
E 13
D 7
	hostf = fopen("/etc/hosts.equiv", "r");
E 7
I 7
D 31
	hostf = superuser ? (FILE *)0 : fopen("/etc/hosts.equiv", "r");
E 31
I 31
	hostf = superuser ? (FILE *)0 : fopen(_PATH_HEQUIV, "r");
E 35
I 35
	return (-1);
}

/*
 * New .rhosts strategy: We are passed an ip address. We spin through
 * hosts.equiv and .rhosts looking for a match. When the .rhosts only
 * has ip addresses, we don't have to trust a nameserver.  When it
 * contains hostnames, we spin through the list of addresses the nameserver
 * gives us and look for a match.
 *
 * Returns 0 if ok, -1 if not ok.
 */
int
iruserok(raddr, superuser, ruser, luser)
	u_long raddr;
	int superuser;
	const char *ruser, *luser;
{
I 36
	register char *cp;
	struct stat sbuf;
	struct passwd *pwd;
E 36
	FILE *hostf;
	uid_t uid;
	int first;
I 36
	char pbuf[MAXPATHLEN];
E 36

	first = 1;
	hostf = superuser ? NULL : fopen(_PATH_HEQUIV, "r");
E 35
E 31
E 7
again:
	if (hostf) {
D 21
		while (fgets(ahost, sizeof (ahost), hostf)) {
I 10
D 13
			register char *p;
E 13
E 10
			char *user;
D 10
			if (index(ahost, '\n'))
				*index(ahost, '\n') = 0;
			user = index(ahost, ' ');
			if (user)
				*user++ = 0;
E 10
I 10

			p = ahost;
			while (*p != '\n' && *p != ' ' && *p != '\t' && *p != '\0')
D 13
				p++;
E 13
I 13
				*p++ = isupper(*p) ? tolower(*p) : *p;
E 13
			if (*p == ' ' || *p == '\t') {
				*p++ = '\0';
				while (*p == ' ' || *p == '\t')
					p++;
				user = p;
				while (*p != '\n' && *p != ' ' && *p != '\t' && *p != '\0')
					p++;
			} else
				user = p;
			*p = '\0';
E 10
D 13
			if (!strcmp(rhost, ahost) &&
E 13
I 13
			if (_checkhost(fhost, ahost, baselen) &&
E 13
D 7
			    !strcmp(ruser, user ? user : luser))
				goto ok;
E 7
I 7
D 10
			    !strcmp(ruser, user ? user : luser)) {
E 10
I 10
			    !strcmp(ruser, *user ? user : luser)) {
E 10
				(void) fclose(hostf);
				return (0);
			}
E 21
I 21
D 35
		if (!_validuser(hostf, fhost, luser, ruser, baselen)) {
			(void) fclose(hostf);
			return(0);
E 35
I 35
		if (__ivaliduser(hostf, raddr, luser, ruser) == 0) {
			(void)fclose(hostf);
			return (0);
E 35
E 21
E 7
		}
D 35
		(void) fclose(hostf);
E 35
I 35
		(void)fclose(hostf);
E 35
	}
D 29
	if (first == 1) {
E 29
I 29
D 35
	if (first == 1 && (_check_rhosts_file || superuser)) {
E 35
I 35
	if (first == 1 && (__check_rhosts_file || superuser)) {
E 35
E 29
I 15
D 36
		struct stat sbuf;
		struct passwd *pwd;
		char pbuf[MAXPATHLEN];

E 36
E 15
		first = 0;
D 15
		hostf = fopen(".rhosts", "r");
E 15
I 15
		if ((pwd = getpwnam(luser)) == NULL)
D 35
			return(-1);
E 35
I 35
			return (-1);
E 35
		(void)strcpy(pbuf, pwd->pw_dir);
		(void)strcat(pbuf, "/.rhosts");
D 35
		if ((hostf = fopen(pbuf, "r")) == NULL)
			return(-1);
E 35
I 35

E 35
D 29
		(void)fstat(fileno(hostf), &sbuf);
		if (sbuf.st_uid && sbuf.st_uid != pwd->pw_uid) {
E 29
I 29
		/*
D 35
		 * if owned by someone other than user or root or if
		 * writeable by anyone but the owner, quit
E 35
I 35
		 * Change effective uid while opening .rhosts.  If root and
		 * reading an NFS mounted file system, can't read files that
		 * are protected read/write owner only.
E 35
		 */
D 35
		if (fstat(fileno(hostf), &sbuf) ||
		    sbuf.st_uid && sbuf.st_uid != pwd->pw_uid ||
		    sbuf.st_mode&022) {
E 29
			fclose(hostf);
			return(-1);
E 35
I 35
		uid = geteuid();
		(void)seteuid(pwd->pw_uid);
		hostf = fopen(pbuf, "r");
		(void)seteuid(uid);

		if (hostf == NULL)
			return (-1);
		/*
		 * If not a regular file, or is owned by someone other than
		 * user or root or if writeable by anyone but the owner, quit.
		 */
I 36
		cp = NULL;
E 36
		if (lstat(pbuf, &sbuf) < 0)
D 36
			__rcmd_errstr = ".rhosts lstat failed";
E 36
I 36
			cp = ".rhosts lstat failed";
E 36
D 38
		else if ((sbuf.st_mode & S_IFMT) != S_IFREG)
E 38
I 38
		else if (!S_ISREG(sbuf.st_mode))
E 38
D 36
			__rcmd_errstr = ".rhosts not regular file";
E 36
I 36
			cp = ".rhosts not regular file";
E 36
		else if (fstat(fileno(hostf), &sbuf) < 0)
D 36
			__rcmd_errstr = ".rhosts fstat failed";
E 36
I 36
			cp = ".rhosts fstat failed";
E 36
		else if (sbuf.st_uid && sbuf.st_uid != pwd->pw_uid)
D 36
			__rcmd_errstr = "bad .rhosts owner";
E 36
I 36
			cp = "bad .rhosts owner";
E 36
D 38
		else if (sbuf.st_mode & 022)
D 36
			__rcmd_errstr = "bad .rhosts permissions";
E 36
I 36
			cp = "bad .rhosts permissions";
E 38
I 38
		else if (sbuf.st_mode & (S_IWGRP|S_IWOTH))
			cp = ".rhosts writeable by other than owner";
E 38
E 36
		/* If there were any problems, quit. */
D 36
		if (__rcmd_errstr) {
E 36
I 36
		if (cp) {
			__rcmd_errstr = cp;
E 36
			(void)fclose(hostf);
			return (-1);
E 35
		}
E 15
		goto again;
	}
	return (-1);
I 13
}

I 29
D 30
static
E 30
I 30
D 35
/* don't make static, used by lpd(8) */
E 30
E 29
I 21
_validuser(hostf, rhost, luser, ruser, baselen)
D 29
char *rhost, *luser, *ruser;
FILE *hostf;
int baselen;
E 29
I 29
	char *rhost, *luser, *ruser;
E 35
I 35
/*
 * XXX
 * Don't make static, used by lpd(8).
 *
 * Returns 0 if ok, -1 if not ok.
 */
int
__ivaliduser(hostf, raddr, luser, ruser)
E 35
	FILE *hostf;
D 35
	int baselen;
E 35
I 35
	u_long raddr;
	const char *luser, *ruser;
E 35
E 29
{
D 33
	char *user;
	char ahost[MAXHOSTNAMELEN];
E 33
D 35
	register char *p;
I 33
	char *user, ahost[MAXHOSTNAMELEN];
	static int _checkhost();
E 35
I 35
	register char *user, *p;
I 42
	int ch;
E 42
D 43
	char ahost[MAXHOSTNAMELEN];
E 43
I 43
	char buf[MAXHOSTNAMELEN + 128];		/* host + login */
E 43
E 35
E 33

D 35
	while (fgets(ahost, sizeof (ahost), hostf)) {
E 35
I 35
D 43
	while (fgets(ahost, sizeof(ahost), hostf)) {
E 35
		p = ahost;
E 43
I 43
	while (fgets(buf, sizeof(buf), hostf)) {
		p = buf;
E 43
I 42
		/* Skip lines that are too long. */
		if (strchr(p, '\n') == NULL) {
			while ((ch = getc(hostf)) != '\n' && ch != EOF);
			continue;
		}
E 42
		while (*p != '\n' && *p != ' ' && *p != '\t' && *p != '\0') {
			*p = isupper(*p) ? tolower(*p) : *p;
			p++;
		}
		if (*p == ' ' || *p == '\t') {
			*p++ = '\0';
			while (*p == ' ' || *p == '\t')
				p++;
			user = p;
D 35
			while (*p != '\n' && *p != ' ' && *p != '\t' && *p != '\0')
E 35
I 35
			while (*p != '\n' && *p != ' ' &&
			    *p != '\t' && *p != '\0')
E 35
				p++;
		} else
			user = p;
		*p = '\0';
D 35
		if (_checkhost(rhost, ahost, baselen) &&
		    !strcmp(ruser, *user ? user : luser)) {
E 35
I 35
D 43
		if (__icheckhost(raddr, ahost) &&
E 43
I 43
		if (__icheckhost(raddr, buf) &&
E 43
		    strcmp(ruser, *user ? user : luser) == 0) {
E 35
			return (0);
		}
	}
	return (-1);
}

I 29
D 35
static
E 29
E 21
_checkhost(rhost, lhost, len)
D 29
char *rhost, *lhost;
int len;
E 29
I 29
	char *rhost, *lhost;
	int len;
E 35
I 35
/*
 * Returns "true" if match, 0 if no match.
 */
static int
__icheckhost(raddr, lhost)
	u_long raddr;
	register char *lhost;
E 35
E 29
{
D 17
	static char ldomain[MAXHOSTNAMELEN];
E 17
I 17
D 35
	static char ldomain[MAXHOSTNAMELEN + 1];
E 17
	static char *domainp = NULL;
I 23
	static int nodomain = 0;
E 23
	register char *cp;
E 35
I 35
	register struct hostent *hp;
	register u_long laddr;
	register char **pp;
E 35

D 35
	if (len == -1)
		return(!strcmp(rhost, lhost));
	if (strncmp(rhost, lhost, len))
		return(0);
	if (!strcmp(rhost, lhost))
		return(1);
	if (*(lhost + len) != '\0')
		return(0);
I 23
	if (nodomain)
		return(0);
E 23
	if (!domainp) {
		if (gethostname(ldomain, sizeof(ldomain)) == -1) {
D 25
			domainp = (char *)1;
E 25
I 25
			nodomain = 1;
E 25
			return(0);
		}
		ldomain[MAXHOSTNAMELEN] = NULL;
D 14
		domainp = index(ldomain, '.') + 1;
E 14
I 14
D 23
		if ((domainp = index(ldomain, '.') + 1) == (char *)1)
E 23
I 23
		if ((domainp = index(ldomain, '.')) == (char *)NULL) {
			nodomain = 1;
E 23
			return(0);
E 14
D 23
		cp = domainp;
D 21
		while (*cp)
			*cp++ = isupper(*cp) ? tolower(*cp) : *cp;
E 21
I 21
		while (*cp) {
			*cp = isupper(*cp) ? tolower(*cp) : *cp;
			cp++;
E 23
		}
I 23
		for (cp = ++domainp; *cp; ++cp)
			if (isupper(*cp))
				*cp = tolower(*cp);
E 23
E 21
	}
D 23
	if (domainp == (char *)1)
		return(0);
E 23
	return(!strcmp(domainp, rhost + len +1));
E 35
I 35
	/* Try for raw ip address first. */
	if (isdigit(*lhost) && (long)(laddr = inet_addr(lhost)) != -1)
		return (raddr == laddr);

	/* Better be a hostname. */
	if ((hp = gethostbyname(lhost)) == NULL)
		return (0);

	/* Spin through ip addresses. */
	for (pp = hp->h_addr_list; *pp; ++pp)
		if (!bcmp(&raddr, *pp, sizeof(u_long)))
			return (1);

	/* No match. */
	return (0);
E 35
E 13
D 7
ok:
	(void) fclose(hostf);
	return (0);
E 7
I 3
}
D 8

socketaddr(x, y)
{

	syscall(103,x,y);
E 3
}
E 8
E 1
