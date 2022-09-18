h03795
s 00002/00002/00100
d D 8.1 93/06/06 22:08:45 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00101
d D 4.7 93/05/17 23:03:28 torek 7 6
c sys_errlist type changed
e
s 00008/00001/00094
d D 4.6 91/04/24 17:30:30 bostic 6 5
c new copyright; att/bsd/shared
e
s 00003/00003/00092
d D 4.5 91/03/02 13:13:30 bostic 5 4
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00001/00003/00094
d D 4.4 88/02/24 20:44:35 rick 4 3
c increase alarm timeout
e
s 00003/00002/00094
d D 4.3 86/06/07 08:29:39 bloom 3 2
c old changes that hadn't been delta'ed in
e
s 00012/00002/00084
d D 4.2 85/06/23 15:11:32 bloom 2 1
c fixes from rick adams
e
s 00086/00000/00000
d D 4.1 85/01/22 13:04:17 ralph 1 0
c date and time created 85/01/22 13:04:17 by ralph
e
u
U
t
T
I 6
/*-
D 8
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.proprietary.c%
 */

E 6
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif
E 6
I 6
#endif /* not lint */
E 6

D 5
#include "../condevs.h"
E 5
I 5
#include "condevs.h"
E 5
D 4
#ifdef BSDTCP
E 4
I 2
#include <netdb.h>
E 2
#include <sys/socket.h>
#include <netinet/in.h>
D 2
#include <netdb.h>
E 2

/*
 *	bsdtcpopn -- make a tcp connection
 *
 *	return codes:
 *		>0 - file number - ok
 *		FAIL - failed
 */

bsdtcpopn(flds)
register char *flds[];
{
	struct servent *sp;
	struct hostent *hp;
	struct	sockaddr_in hisctladdr;
D 3
	int s, port;
E 3
I 3
	int s = -1, port;
E 3
	extern int errno;
D 7
	extern char *sys_errlist[];
E 7
I 7
	extern const char *const sys_errlist[];
E 7

	sp = getservbyname(flds[F_CLASS], "tcp");
	if (sp == NULL) {
		port = htons(atoi(flds[F_CLASS]));
		if (port == 0) {
			logent(_FAILED, "UNKNOWN PORT NUMBER");
			return CF_SYSTEM;
		}
	} else
		port = sp->s_port;
	DEBUG(4, "bsdtcpopn host %s, ", flds[F_PHONE]);
	DEBUG(4, "port %d\n", ntohs(port));
	if (setjmp(Sjbuf)) {
I 3
		bsdtcpcls(s);
E 3
		logent("tcpopen", "TIMEOUT");
		return CF_DIAL;
	}

	bzero((char *)&hisctladdr, sizeof (hisctladdr));
	hp = gethostbyname(flds[F_PHONE]);
	if (hp == NULL) {
		logent("tcpopen","UNKNOWN HOST");
		return CF_DIAL;
	}
	signal(SIGALRM, alarmtr);
D 4
	alarm(30);
E 4
I 4
	alarm(MAXMSGTIME*2);
E 4
	hisctladdr.sin_family = hp->h_addrtype;
D 2
	s = socket(hp->h_addrtype, SOCK_STREAM, 0, 0);
E 2
I 2
#ifdef BSD2_9
	s = socket(SOCK_STREAM, 0, &hisctladdr, 0);
#else BSD4_2
	s = socket(hp->h_addrtype, SOCK_STREAM, 0);
#endif BSD4_2
E 2
	if (s < 0)
		goto bad;
I 2
#ifndef BSD2_9
E 2
D 5
	if (bind(s, (char *)&hisctladdr, sizeof (hisctladdr), 0) < 0)
E 5
I 5
	if (bind(s, (struct sockaddr *)&hisctladdr, sizeof (hisctladdr)) < 0)
E 5
		goto bad;
I 2
#endif BSD2_9
E 2
	bcopy(hp->h_addr, (char *)&hisctladdr.sin_addr, hp->h_length);
	hisctladdr.sin_port = port;
I 2
#ifdef BSD2_9
	if (connect(s, (char *)&hisctladdr) < 0)
#else BSD4_2
E 2
D 5
	if (connect(s, (char *)&hisctladdr, sizeof (hisctladdr), 0) < 0)
E 5
I 5
	if (connect(s, (struct sockaddr *)&hisctladdr, sizeof (hisctladdr)) < 0)
E 5
I 2
#endif BSD4_2
E 2
		goto bad;
	alarm(0);
	CU_end = bsdtcpcls;
	return s;
bad:
	alarm(0);
D 3
	close(s);
E 3
I 3
	bsdtcpcls(s);
E 3
	DEBUG(5, "tcpopen failed: errno %d\n", errno);
	logent(sys_errlist[errno], _FAILED);
	return CF_DIAL;
}

/*
 * bsdtcpcls -- close tcp connection
 */
bsdtcpcls(fd)
register int fd;
{
	DEBUG(4, "TCP CLOSE called\n", 0);
	if (fd > 0) {
		close(fd);
		DEBUG(4, "closed fd %d\n", fd);
	}
}
D 4
#endif BSDTCP
E 4
E 1
