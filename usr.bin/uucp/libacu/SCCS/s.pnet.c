h04856
s 00002/00002/00052
d D 8.1 93/06/06 22:09:21 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00046
d D 4.5 91/04/24 17:30:39 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00046
d D 4.4 91/03/02 13:13:40 bostic 4 3
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00000/00047
d D 4.3 88/02/24 20:45:25 rick 3 2
c remove extraneous ifdefs
e
s 00001/00000/00046
d D 4.2 85/06/23 15:21:00 bloom 2 1
c fix from rick adams
e
s 00046/00000/00000
d D 4.1 85/01/22 13:04:37 ralph 1 0
c date and time created 85/01/22 13:04:37 by ralph
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
#endif /* not lint */
E 5

D 4
#include "../condevs.h"
E 4
I 4
#include "condevs.h"
E 4
#ifdef PNET

/***
 *	pnetopn(flds)
 *
 *	call remote machine via Purdue network
 *	use dial string as host name, speed as socket number
 *	- Steve Bellovin
 */
pnetopn(flds)
char *flds[];
{
	int fd;
	int socket;
	register char *cp;

	fd = pnetfile();
	DEBUG(4, "pnet fd - %d\n", fd);
	if (fd < 0) {
		logent("AVAILABLE DEVICE", "NO");
		return CF_NODEV;
	}
	socket = 0;
	for (cp = flds[F_CLASS]; *cp; cp++)
		socket = 10*socket + (*cp - '0');
	DEBUG(4, "socket - %d\n", socket);
	if (setjmp(Sjbuf)) {
		DEBUG(4, "pnet timeout  - %s\n", flds[F_PHONE]);
		return CF_DIAL;
	}
	signal(SIGALRM, alarmtr);
	DEBUG(4, "host - %s\n", flds[F_PHONE]);
	alarm(15);
	if (pnetscon(fd, flds[F_PHONE], socket) < 0) {
		DEBUG(4, "pnet connect failed - %s\n", flds[F_PHONE]);
I 2
		alarm(0);
E 2
		return CF_DIAL;
	}
	alarm(0);
	return fd;
}
#endif	PNET
E 1
