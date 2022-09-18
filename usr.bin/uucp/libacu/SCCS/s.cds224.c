h25894
s 00002/00002/00113
d D 8.1 93/06/06 22:08:48 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00107
d D 1.4 91/04/24 17:30:31 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00106
d D 1.3 91/03/02 13:13:31 bostic 3 2
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00002/00108
d D 1.2 88/02/24 20:45:11 rick 2 1
c remove extraneous ifdefs
e
s 00110/00000/00000
d D 1.1 86/01/13 13:51:24 bloom 1 0
c date and time created 86/01/13 13:51:24 by bloom
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
#endif !lint
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
#ifdef CDS224
E 2

/*
 *	conopn: establish dial-out connection through a Concord CDS 224.
 *	Returns descriptor open to tty for reading and writing.
 *	Negative values (-1...-7) denote errors in connmsg.
 *	Be sure to disconnect tty when done, via HUPCL or stty 0.
 */
#define TRYS 5	/* number of trys */

cdsopn224(telno, flds, dev)
char *telno;
char *flds[];
struct Devices *dev;
{
	int	dh = -1;
	int	i, ok, er = 0, delay;
	extern errno;
	char dcname[20];
D 3
	char *tempbuf[20];
E 3
I 3
	char tempbuf[20];
E 3

	sprintf(dcname, "/dev/%s", dev->D_line);
	if (setjmp(Sjbuf)) {
		DEBUG(1, "timeout concord open\n", "");
		logent("concord open", "TIMEOUT");
		if (dh >= 0)
			cdscls224(dh);
		delock(dev->D_line);
		return CF_NODEV;
	}
	signal(SIGALRM, alarmtr);
	getnextfd();
	alarm(10);
	dh = open(dcname, 2);
	alarm(0);

	/* modem is open */
	next_fd = -1;
	if (dh < 0) {
		delock(dev->D_line);
		return CF_NODEV;
	}
	fixline(dh, dev->D_speed);

	DEBUG(4, "calling %s -> ", telno);
	if (dochat(dev, flds, dh)) {
		logent(dcname, "CHAT FAILED");
		cdscls224(dh);
		return CF_DIAL;
	}
	for(i = 0; i < TRYS; ++i) {
		/* wake up Concord */
		write(dh, "\r\r", 2);
		DEBUG(4, "wanted CDS >", CNULL);
		ok = expect("CDS >", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;

		write(dh, "\r", 2);
		DEBUG(4, "wanted CDS >", CNULL);
		ok = expect("CDS >", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;

		/* send telno \r */
		sprintf(tempbuf,"D%s\r",telno);
		write(dh, tempbuf, strlen(tempbuf));

		DEBUG(4, "wanted DIALING ", CNULL);
		ok = expect("DIALING ", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok == 0) 
			break;
	}

	if (ok == 0) {
		sleep(10);	/* give concord some time */
		DEBUG(4, "wanted INITIATING " , CNULL);
		ok = expect("INITIATING", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
	}

	if (ok != 0) {
		if (dh > 2)
			close(dh);
		DEBUG(4, "conDial failed\n", CNULL);
		delock(dev->D_line);
		return CF_DIAL;
	}
	DEBUG(4, "concord ok\n", CNULL);
	return dh;
}

cdscls224(fd)
{

	if (fd > 0) {
		close(fd);
		sleep(5);
		delock(devSel);
	}
}
D 2
#endif CDS224
E 2
E 1
