h63435
s 00002/00002/00126
d D 8.1 93/06/06 22:09:36 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00120
d D 4.4 91/04/24 17:30:43 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00120
d D 4.3 91/03/02 13:13:45 bostic 3 2
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00002/00121
d D 4.2 88/02/24 20:45:31 rick 2 1
c remove extraneous ifdefs
e
s 00123/00000/00000
d D 4.1 85/01/22 13:04:49 ralph 1 0
c date and time created 85/01/22 13:04:49 by ralph
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

D 2
#ifdef	VA811S
E 2
/*
 * Racal-Vadic VA811 dialer with 831 adaptor.
 * A typical 300 baud L-devices entry is
 *	ACU /dev/tty10 unused 300 va811s
 * where tty10 is the communication line (D_Line),
 * and 300 is the line speed.
 * This is almost identical to RVMACS except that we don't need to
 * send addresses and modem types, and don't need the fork.
 *	Joe Kelsey, fluke!joe, vax4.1526, Apr 11 1984.
 */

#define	STX	02	/* Access Adaptor */
#define	ETX	03	/* Transfer to Dialer */
#define	SI	017	/* Buffer Empty (end of phone number) */
#define	SOH	01	/* Abort */

va811opn(ph, flds, dev)
char *ph, *flds[];
struct Devices *dev;
{
	int va;
	register int i, tries;
	char c, dcname[20];
	char vabuf[35];		/* STX, 31 phone digits, SI, ETX, NUL */

	va = 0;
	sprintf(dcname, "/dev/%s", dev->D_line);
	if (setjmp(Sjbuf)) {
		DEBUG(1, "timeout va811 open\n", 0);
		logent("va811opn", "TIMEOUT");
		if (va >= 0)
			close(va);
		delock(dev->D_line);
		return CF_NODEV;
	}
	DEBUG(4, "va811: STARTING CALL\n", 0);
	getnextfd();
	signal(SIGALRM, alarmtr);
	alarm(10);
	va = open(dcname, 2);
	alarm(0);

	/* line is open */
	next_fd = -1;
	if (va < 0) {
		DEBUG(4, errno == 4 ? "%s: no carrier\n" : "%s: can't open\n",
			dcname);
		delock(dev->D_line);
		logent(dcname, "CAN'T OPEN");
		return(errno == 4 ? CF_DIAL : CF_NODEV);
	}
	fixline(va, dev->D_speed);

	/* first, reset everything */
	sendthem("\\01\\c", va);
	DEBUG(4, "wanted %c ", 'B');
	i = expect("B", va);
	DEBUG(4, "got %s\n", i ? "?" : "that");
	if (i != 0) {
	    DEBUG(4, "va811: NO RESPONSE\n", 0);
	    logent("va811 reset", "TIMEOUT");
	    close(va);
	    delock(dev->D_line);
	    return CF_DIAL;
	}

	sprintf(vabuf, "%c%.31s%c%c\\c", STX, ph, SI, SOH);
	sendthem(vabuf, va);
	DEBUG(4, "wanted %c ", 'B');
	i = expect("B", va);
	DEBUG(4, "got %s\n", i ? "?" : "that");

	if (i != 0) {
	    DEBUG(4, "va811: STORE NUMBER\n", 0);
	    logent("va811 STORE", _FAILED);
	    close(va);
	    delock(dev->D_line);
	    return CF_DIAL;
	}

	for (tries = 0; tries < TRYCALLS; tries++) {
	    sprintf(vabuf, "%c%c\\c", STX, ETX);
	    sendthem(vabuf, va);
	    DEBUG(4, "DIALING...", CNULL);
	    i = expect("A", va);
	    DEBUG(4, " %s\n", i ? _FAILED : "SUCCEEDED");
	    if (i != 0) {
		DEBUG(4, "va811: RESETTING\n", CNULL);
		logent("va811 DIAL", _FAILED);
	        sendthem("\\01\\c", va);
	        expect("B", va);
	    }
	    else
	        break;
	}

	if (tries >= TRYCALLS) {
	    close(va);
	    delock(dev->D_line);
	    return CF_DIAL;
	}

	DEBUG(4, "va811 ok\n", CNULL);
	return va;
}

va811cls(fd)
register int fd;
{
	DEBUG(2, "va811 close %d\n", fd);
	p_chwrite(fd, SOH);
/*	ioctl(fd, TIOCCDTR, NULL);*/
	close(fd);
	delock(devSel);
}
D 2
#endif VA811S
E 2
E 1
