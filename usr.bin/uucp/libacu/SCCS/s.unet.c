h27569
s 00002/00002/00071
d D 8.1 93/06/06 22:09:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00065
d D 4.4 91/04/24 17:30:41 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00065
d D 4.3 91/03/02 13:13:43 bostic 3 2
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00000/00066
d D 4.2 88/02/24 20:45:28 rick 2 1
c remove extraneous ifdefs
e
s 00066/00000/00000
d D 4.1 85/01/22 13:04:44 ralph 1 0
c date and time created 85/01/22 13:04:44 by ralph
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

D 3
#include "../condevs.h"
E 3
I 3
#include "condevs.h"
E 3
#ifdef UNETTCP

/*
 *	unetopn -- make UNET (tcp-ip) connection
 *
 *	return codes:
 *		>0 - file number - ok
 *		FAIL - failed
 */

/* Default port of uucico server */
#define	DFLTPORT	33

unetopn(flds)
register char *flds[];
{
	register int ret, port;
	int unetcls();

	port = atoi(flds[F_PHONE]);
	if (port <= 0 || port > 255)
		port = DFLTPORT;
	DEBUG(4, "unetopn host %s, ", flds[F_NAME]);
	DEBUG(4, "port %d\n", port);
	if (setjmp(Sjbuf)) {
		logent("tcpopen", "TIMEOUT");
		endhnent();	/* see below */
		return CF_DIAL;
	}
	signal(SIGALRM, alarmtr);
	alarm(30);
	ret = tcpopen(flds[F_NAME], port, 0, TO_ACTIVE, "rw");
	alarm(0);
	endhnent();	/* wave magic wand at 3com and incant "eat it, bruce" */
	if (ret < 0) {
		DEBUG(5, "tcpopen failed: errno %d\n", errno);
		logent("tcpopen", _FAILED);
		return CF_DIAL;
	}
	CU_end = unetcls;
	return ret;
}

/*
 * unetcls -- close UNET connection.
 */
unetcls(fd)
register int fd;
{
	DEBUG(4, "UNET CLOSE called\n", 0);
	if (fd > 0) {
#ifdef notdef
		/* disable this until a timeout is put in */
		if (ioctl(fd, UIOCCLOSE, STBNULL))
			logent("UNET CLOSE", _FAILED);
#endif notdef
		close(fd);
		DEBUG(4, "closed fd %d\n", fd);
	}
}
#endif UNETTCP
E 1
