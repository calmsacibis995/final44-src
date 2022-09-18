h22119
s 00001/00001/00347
d D 8.3 95/04/28 10:29:24 bostic 33 32
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00007/00013/00341
d D 8.2 95/04/28 10:16:04 bostic 32 31
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00352
d D 8.1 93/06/05 10:52:39 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00011/00336
d D 5.18 93/05/11 13:57:43 torek 30 29
c lint; fix protocol botch message (had an embedded newline)
e
s 00012/00000/00335
d D 5.17 93/01/25 16:08:53 mckusick 29 28
c put back rmtioctl in case someone is using it
e
s 00096/00054/00239
d D 5.16 93/01/25 15:35:38 mckusick 28 27
c make error messages less cryptic; cleanups from leres@lbl
e
s 00010/00010/00283
d D 5.15 92/06/18 14:12:50 mckusick 27 26
c lint
e
s 00001/00000/00292
d D 5.14 92/05/18 18:24:05 mckusick 26 25
c need additional include
e
s 00001/00001/00291
d D 5.13 91/11/10 13:05:07 bostic 25 24
c break UFS up into FFS/UFS/LFS/MFS
e
s 00015/00001/00277
d D 5.12 91/07/23 16:56:21 mckusick 24 23
c temporarily add ifdef sunos (includes) to assist Steve Romig in debugging
e
s 00005/00004/00273
d D 5.11 91/03/07 17:50:01 mckusick 23 22
c verified to be free of AT&T code
e
s 00004/00000/00273
d D 5.10 91/02/28 19:33:53 bostic 22 21
c ANSI; break #includes out of dump.h into separate files
e
s 00026/00004/00247
d D 5.9 91/02/23 16:15:29 torek 21 20
c fix gcc warnings
e
s 00001/00003/00250
d D 5.8 90/02/15 13:28:46 mckusick 20 19
c just need dinode.h, not inode, and vnode
e
s 00003/00001/00250
d D 5.7 89/07/30 10:49:26 bostic 19 18
c vnodes
e
s 00004/00003/00247
d D 5.6 89/05/11 13:52:25 bostic 18 17
c file reorg, pathnames.h, paths.h
e
s 00006/00006/00244
d D 5.5 87/10/22 10:52:59 bostic 17 16
c ANSI C; sprintf now returns an int.
e
s 00000/00002/00250
d D 5.4 85/12/11 18:36:20 karels 16 15
c let's try SO_SNDBUF again
e
s 00001/00001/00251
d D 5.3 85/09/17 17:54:17 mckusick 15 14
c return a value from rmtopen()
e
s 00001/00001/00251
d D 5.2 85/06/18 21:07:02 mckusick 14 13
c dumpretore.h moves into protocols
e
s 00009/00001/00243
d D 5.1 85/06/05 08:46:48 dist 13 12
c Add copyright
e
s 00002/00000/00242
d D 1.10 85/05/07 19:01:56 mckusick 12 10
c get rid of setsockopt for now as it breaks rdump
e
s 00003/00001/00241
d R 1.10 85/05/07 18:47:20 mckusick 11 10
c get rid of setsockopt for now as it breaks rdump
e
s 00003/00002/00239
d D 1.9 85/03/24 18:05:56 mckusick 10 9
c retry setsockopt until an agreeable size is found
e
s 00012/00002/00229
d D 1.8 84/12/19 11:55:53 ralph 9 7
c use setsockopt to increase buffer size
e
s 00016/00004/00227
d R 1.8 84/12/19 11:47:11 ralph 8 7
c use setsockopt to increase buffer size.
e
s 00007/00001/00224
d D 1.7 84/04/12 09:33:40 karels 7 6
c don't assume that we're root
e
s 00001/00001/00224
d D 1.6 83/07/01 03:07:37 sam 6 5
c from sun
e
s 00001/00001/00224
d D 1.5 83/06/12 02:44:00 sam 5 4
c new signals == no libjobs
e
s 00014/00004/00211
d D 1.4 82/11/19 17:51:17 sam 4 3
c update to 4.1c and use netdb.h
e
s 00000/00007/00215
d D 1.3 82/10/11 16:36:32 mckusick 3 2
c get rid of msg() since it is already defined
e
s 00018/00020/00204
d D 1.2 82/05/20 15:13:06 sam 2 1
c forget about reconnecting on error
e
s 00224/00000/00000
d D 1.1 82/05/07 15:43:29 sam 1 0
c date and time created 82/05/07 15:43:29 by sam
e
u
U
t
T
I 1
D 13
static	char *sccsid = "%W% (Berkeley) %G%";
E 13
I 13
D 23
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 23
I 23
/*-
D 31
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
 * %sccs.include.redist.c%
E 23
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 21
#endif not lint
E 21
I 21
#endif /* not lint */
E 21
E 13
D 2
#include "dump.h"
E 2

I 24
D 28
#ifdef sunos
#include <stdio.h>
#include <ctype.h>
E 28
E 24
I 2
D 4
#include <stdio.h>
E 4
#include <sys/param.h>
E 2
#include <sys/mtio.h>
#include <sys/ioctl.h>
I 9
#include <sys/socket.h>
I 24
D 28
#include <sys/stat.h>
D 27
#include <sys/time.h>
#include <sys/dir.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 27
#else
#include <sys/param.h>
#include <sys/mtio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
E 28
I 26
#include <sys/time.h>
E 26
E 24
D 19
#include <sys/inode.h>
E 19
I 19
D 20
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 20
I 20
D 25
#include <ufs/dinode.h>
E 25
I 25
D 27
#include <ufs/ufs/dinode.h>
E 27
E 25
I 24
D 28
#include <stdio.h>
#endif
E 28
I 28
#ifdef sunos
#include <sys/vnode.h>

#include <ufs/inode.h>
#else
E 28
I 27
#include <ufs/ufs/dinode.h>
E 27
E 24
I 22
D 28
#include <signal.h>
E 28
I 28
#endif
E 28
E 22
E 20
E 19
E 9
D 4
#include <net/in.h>
E 4

I 4
#include <netinet/in.h>
I 28
#include <netinet/tcp.h>
E 28

D 18
#include <stdio.h>
I 7
#include <pwd.h>
E 18
E 7
D 28
#include <netdb.h>
E 28
I 9
D 14
#include <dumprestor.h>
E 14
I 14
#include <protocols/dumprestore.h>
I 28

#include <ctype.h>
I 32
#include <err.h>
E 32
#include <netdb.h>
E 28
I 18
#include <pwd.h>
I 28
#include <signal.h>
#include <stdio.h>
E 28
D 24
#include <stdio.h>
E 24
I 22
#ifdef __STDC__
D 28
#include <unistd.h>
E 28
E 22
I 21
#include <stdlib.h>
#include <string.h>
I 28
#include <unistd.h>
E 28
I 22
#endif
I 28

E 28
E 22
E 21
#include "pathnames.h"
I 28
#include "dump.h"
E 28
E 18
E 14
E 9

E 4
#define	TS_CLOSED	0
#define	TS_OPEN		1

static	int rmtstate = TS_CLOSED;
D 28
int	rmtape;
D 21
int	rmtconnaborted();
E 21
I 21
void	rmtgetconn();
void	rmtconnaborted();
int	rmtreply();
int	rmtgetb();
void	rmtgets();
int	rmtcall();
E 21
char	*rmtpeer;
E 28
I 28
static	int rmtape;
static	char *rmtpeer;
E 28

I 9
D 28
extern int ntrec;		/* blocking factor on tape */
I 21
extern void msg();
E 28
I 28
static	int okname __P((char *));
static	int rmtcall __P((char *, char *));
static	void rmtconnaborted __P((/* int, int */));
static	int rmtgetb __P((void));
static	void rmtgetconn __P((void));
static	void rmtgets __P((char *, int));
static	int rmtreply __P((char *));
E 28
E 21

I 27
D 28
extern void exit();
E 28
I 28
extern	int ntrec;		/* blocking factor on tape */
E 28

E 27
I 21
int
E 21
E 9
rmthost(host)
	char *host;
{

D 28
	rmtpeer = host;
E 28
I 28
	rmtpeer = malloc(strlen(host) + 1);
	if (rmtpeer)
		strcpy(rmtpeer, host);
	else
		rmtpeer = host;
E 28
D 5
	sigset(SIGPIPE, rmtconnaborted);
E 5
I 5
	signal(SIGPIPE, rmtconnaborted);
E 5
	rmtgetconn();
	if (rmtape < 0)
D 2
		rmtreconnect();
E 2
I 2
D 9
		exit(1);
E 9
I 9
		return (0);
	return (1);
E 9
E 2
}

I 21
D 28
void
E 28
I 28
static void
E 28
E 21
rmtconnaborted()
{

D 2
	msg("Lost connection to tape server.\n");
	if (rmtape >= 0) {
		close(rmtape);
		rmtape = -1;
	}
	exit(X_REWRITE);
E 2
I 2
D 9
	fprintf(stderr, "Lost connection to remote host.\n");
E 9
I 9
D 27
	fprintf(stderr, "rdump: Lost connection to remote host.\n");
E 9
	exit(1);
E 27
I 27
D 32
	(void) fprintf(stderr, "rdump: Lost connection to remote host.\n");
D 28
	(void) exit(1);
E 28
I 28
	exit(1);
E 32
I 32
	errx(1, "Lost connection to remote host.");
E 32
E 28
E 27
E 2
}

I 21
void
E 21
D 2
rmtreconnect()
{

	do {
		if (query("Retry conection to remote host?") == 0)
			exit(X_ABORT);
		rmtgetconn();
	} while (rmtape < 0);
}

E 2
rmtgetconn()
{
I 28
	register char *cp;
E 28
I 4
D 30
	static struct servent *sp = 0;
I 7
D 28
	struct passwd *pw;
	char *name = "root";
E 28
I 28
	static struct passwd *pwd = 0;
E 30
I 30
	static struct servent *sp = NULL;
	static struct passwd *pwd = NULL;
E 30
#ifdef notdef
	static int on = 1;
#endif
	char *tuser;
E 28
I 9
	int size;
I 28
	int maxseg;
E 28
E 9
E 7
E 4

D 4
	rmtape = rcmd(&rmtpeer, IPPORT_CMDSERVER,
	    "root", "root", "/etc/rmt", 0);
E 4
I 4
D 30
	if (sp == 0) {
E 30
I 30
	if (sp == NULL) {
E 30
		sp = getservbyname("shell", "tcp");
D 30
		if (sp == 0) {
E 30
I 30
D 32
		if (sp == NULL) {
E 30
D 27
			fprintf(stderr, "rdump: shell/tcp: unknown service\n");
			exit(1);
E 27
I 27
			(void) fprintf(stderr,
			    "rdump: shell/tcp: unknown service\n");
D 28
			(void) exit(1);
E 28
I 28
			exit(1);
E 28
E 27
		}
E 32
I 32
		if (sp == NULL)
			errx(1, "shell/tcp: unknown service");
E 32
I 28
		pwd = getpwuid(getuid());
D 30
		if (pwd == 0) {
E 30
I 30
D 32
		if (pwd == NULL) {
E 30
			(void) fprintf(stderr, "rdump: who are you?\n");
			exit(1);
		}
E 32
I 32
		if (pwd == NULL)
			errx(1, "who are you?");
E 32
E 28
	}
D 7
	rmtape = rcmd(&rmtpeer, sp->s_port, "root", "root", "/etc/rmt", 0);
E 7
I 7
D 28
	pw = getpwuid(getuid());
	if (pw && pw->pw_name)
		name = pw->pw_name;
D 18
	rmtape = rcmd(&rmtpeer, sp->s_port, name, name, "/etc/rmt", 0);
E 18
I 18
D 27
	rmtape = rcmd(&rmtpeer, sp->s_port, name, name, _PATH_RMT, 0);
E 27
I 27
	rmtape = rcmd(&rmtpeer, (u_short)sp->s_port, name, name, _PATH_RMT,
	    (int *)0);
E 28
I 28
D 30
	if (cp = index(rmtpeer, '@')) {
E 30
I 30
D 33
	if ((cp = index(rmtpeer, '@')) != NULL) {
E 33
I 33
	if ((cp = strchr(rmtpeer, '@')) != NULL) {
E 33
E 30
		tuser = rmtpeer;
		*cp = '\0';
		if (!okname(tuser))
			exit(1);
		rmtpeer = ++cp;
	} else
		tuser = pwd->pw_name;
	rmtape = rcmd(&rmtpeer, (u_short)sp->s_port, pwd->pw_name, tuser,
	    _PATH_RMT, (int *)0);
E 28
E 27
E 18
I 12
D 16
#ifdef notdef	/* broken */
E 16
E 12
I 9
	size = ntrec * TP_BSIZE;
I 28
	if (size > 60 * 1024)		/* XXX */
		size = 60 * 1024;
	/* Leave some space for rmt request/response protocol */
	size += 2 * 1024;
E 28
D 10
	if (setsockopt(rmtape, SOL_SOCKET, SO_SNDBUF, &size, sizeof (size)) < 0)
		fprintf(stderr, "rdump: Warning: setsockopt buffer size failed.\n");
E 10
I 10
	while (size > TP_BSIZE &&
	    setsockopt(rmtape, SOL_SOCKET, SO_SNDBUF, &size, sizeof (size)) < 0)
D 28
		size -= TP_BSIZE;
E 28
I 28
		    size -= TP_BSIZE;
	(void)setsockopt(rmtape, SOL_SOCKET, SO_RCVBUF, &size, sizeof (size));
	maxseg = 1024;
	if (setsockopt(rmtape, IPPROTO_TCP, TCP_MAXSEG,
	    &maxseg, sizeof (maxseg)) < 0)
		perror("TCP_MAXSEG setsockopt");

#ifdef notdef
	if (setsockopt(rmtape, IPPROTO_TCP, TCP_NODELAY, &on, sizeof (on)) < 0)
		perror("TCP_NODELAY setsockopt");
#endif
E 28
I 12
D 16
#endif notdef
E 16
E 12
E 10
E 9
E 7
E 4
}

I 28
static int
okname(cp0)
	char *cp0;
{
	register char *cp;
	register int c;

	for (cp = cp0; *cp; cp++) {
		c = *cp;
		if (!isascii(c) || !(isalnum(c) || c == '_' || c == '-')) {
D 32
			(void) fprintf(stderr, "rdump: invalid user name %s\n",
			    cp0);
E 32
I 32
			warnx("invalid user name: %s", cp0);
E 32
			return (0);
		}
	}
	return (1);
}

E 28
I 21
int
E 21
rmtopen(tape, mode)
	char *tape;
	int mode;
{
	char buf[256];

D 17
	sprintf(buf, "O%s\n%d\n", tape, mode);
E 17
I 17
	(void)sprintf(buf, "O%s\n%d\n", tape, mode);
E 17
D 15
	rmtcall(tape, buf);
E 15
	rmtstate = TS_OPEN;
I 15
	return (rmtcall(tape, buf));
E 15
}

I 21
void
E 21
rmtclose()
{

	if (rmtstate != TS_OPEN)
		return;
	rmtcall("close", "C\n");
	rmtstate = TS_CLOSED;
}

I 21
int
E 21
rmtread(buf, count)
	char *buf;
	int count;
{
	char line[30];
	int n, i, cc;
I 2
	extern errno;
E 2

D 17
	sprintf(line, "R%d\n", count);
E 17
I 17
	(void)sprintf(line, "R%d\n", count);
E 17
	n = rmtcall("read", line);
D 2
	if (n < 0)
E 2
I 2
	if (n < 0) {
		errno = n;
E 2
		return (-1);
I 2
	}
E 2
	for (i = 0; i < n; i += cc) {
		cc = read(rmtape, buf+i, n - i);
D 2
		if (cc <= 0)
E 2
I 2
		if (cc <= 0) {
E 2
			rmtconnaborted();
I 2
		}
E 2
	}
	return (n);
}

I 21
int
E 21
rmtwrite(buf, count)
	char *buf;
	int count;
{
	char line[30];

D 17
	sprintf(line, "W%d\n", count);
E 17
I 17
	(void)sprintf(line, "W%d\n", count);
E 17
	write(rmtape, line, strlen(line));
	write(rmtape, buf, count);
	return (rmtreply("write"));
}

I 21
void
E 21
rmtwrite0(count)
	int count;
{
	char line[30];

D 17
	sprintf(line, "W%d\n", count);
E 17
I 17
	(void)sprintf(line, "W%d\n", count);
E 17
	write(rmtape, line, strlen(line));
}

I 21
void
E 21
rmtwrite1(buf, count)
	char *buf;
	int count;
{

	write(rmtape, buf, count);
}

I 21
int
E 21
rmtwrite2()
{
D 21
	int i;
E 21

	return (rmtreply("write"));
}

I 21
int
E 21
rmtseek(offset, pos)
	int offset, pos;
{
	char line[80];

D 17
	sprintf(line, "L%d\n%d\n", offset, pos);
E 17
I 17
	(void)sprintf(line, "L%d\n%d\n", offset, pos);
E 17
	return (rmtcall("seek", line));
}

struct	mtget mts;

struct mtget *
rmtstatus()
{
	register int i;
	register char *cp;

	if (rmtstate != TS_OPEN)
D 30
		return (0);
E 30
I 30
		return (NULL);
E 30
	rmtcall("status", "S\n");
	for (i = 0, cp = (char *)&mts; i < sizeof(mts); i++)
		*cp++ = rmtgetb();
	return (&mts);
}

I 29
int
rmtioctl(cmd, count)
	int cmd, count;
{
	char buf[256];

	if (count < 0)
		return (-1);
	(void)sprintf(buf, "I%d\n%d\n", cmd, count);
	return (rmtcall("ioctl", buf));
}

E 29
I 21
D 28
int
E 21
rmtioctl(cmd, count)
	int cmd, count;
{
	char buf[256];

	if (count < 0)
		return (-1);
D 17
	sprintf(buf, "I%d\n%d\n", cmd, count);
E 17
I 17
	(void)sprintf(buf, "I%d\n%d\n", cmd, count);
E 17
D 6
	rmtcall("ioctl", buf);
E 6
I 6
	return (rmtcall("ioctl", buf));
E 6
}

I 21
int
E 28
I 28
static int
E 28
E 21
rmtcall(cmd, buf)
	char *cmd, *buf;
{

	if (write(rmtape, buf, strlen(buf)) != strlen(buf))
		rmtconnaborted();
	return (rmtreply(cmd));
}

I 21
D 28
int
E 28
I 28
static int
E 28
E 21
rmtreply(cmd)
	char *cmd;
{
I 30
	register char *cp;
E 30
D 21
	register int c;
E 21
	char code[30], emsg[BUFSIZ];

	rmtgets(code, sizeof (code));
	if (*code == 'E' || *code == 'F') {
		rmtgets(emsg, sizeof (emsg));
D 30
		msg("%s: %s\n", cmd, emsg, code + 1);
E 30
I 30
		msg("%s: %s", cmd, emsg);
E 30
		if (*code == 'F') {
			rmtstate = TS_CLOSED;
			return (-1);
		}
		return (-1);
	}
	if (*code != 'A') {
D 30
		msg("Protocol to remote tape server botched (code %s?).\n",
E 30
I 30
		/* Kill trailing newline */
		cp = code + strlen(code);
		if (cp > code && *--cp == '\n')
			*cp = '\0';

		msg("Protocol to remote tape server botched (code \"%s\").\n",
E 30
		    code);
		rmtconnaborted();
	}
	return (atoi(code + 1));
}

I 21
int
E 21
rmtgetb()
{
	char c;

	if (read(rmtape, &c, 1) != 1)
		rmtconnaborted();
	return (c);
}

I 30
/* Get a line (guaranteed to have a trailing newline). */
E 30
I 21
void
E 21
D 28
rmtgets(cp, len)
	char *cp;
E 28
I 28
rmtgets(line, len)
	char *line;
E 28
	int len;
{
I 28
	register char *cp = line;
E 28

	while (len > 1) {
		*cp = rmtgetb();
		if (*cp == '\n') {
D 30
			cp[1] = 0;
E 30
I 30
			cp[1] = '\0';
E 30
			return;
		}
		cp++;
		len--;
	}
D 28
	msg("Protocol to remote tape server botched (in rmtgets).\n");
E 28
I 28
D 30
	*cp = 0;
E 30
I 30
	*cp = '\0';
E 30
	msg("Protocol to remote tape server botched.\n");
	msg("(rmtgets got \"%s\").\n", line);
E 28
	rmtconnaborted();
I 2
}
D 3

msg(cp, a1, a2, a3)
	char *cp;
{

	fprintf(stderr, cp, a1, a2, a3);
E 2
}
E 3
E 1
