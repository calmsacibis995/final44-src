/*-
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)unet.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#include "condevs.h"
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
