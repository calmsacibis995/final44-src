h51687
s 00002/00002/00124
d D 8.1 93/06/06 22:09:15 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00118
d D 4.4 91/04/24 17:30:37 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00118
d D 4.3 91/03/02 13:13:39 bostic 3 2
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00003/00119
d D 4.2 88/02/24 20:45:22 rick 2 1
c remove extraneous ifdefs
e
s 00122/00000/00000
d D 4.1 85/01/22 13:04:34 ralph 1 0
c date and time created 85/01/22 13:04:34 by ralph
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
#ifdef NOVATION
E 2

/***
 *	novopn(telno, flds, dev) connect to novation Smart-Cat
 *	(similar to hayes smartmodem)
 *	char *flds[], *dev[];
 *
 *	return codes:
 *		>0  -  file number  -  ok
 *		CF_DIAL,CF_DEVICE  -  failed
 */

novopn(telno, flds, dev)
char *telno;
char *flds[];
struct Devices *dev;
{
	int	dh = -1;
	extern errno;
	char dcname[20];
	int pulse = 0;

	sprintf(dcname, "/dev/%s", dev->D_line);
	DEBUG(4, "dc - %s\n", dcname);
	if (strcmp(dev->D_calldev, "pulse") == 0)
		pulse = 1;
	if (setjmp(Sjbuf)) {
		DEBUG(1, "timeout novation open %s\n", dcname);
		logent("novation open", "TIMEOUT");
		if (dh >= 0)
			close(dh);
		delock(dev->D_line);
		return CF_DIAL;
	}
	signal(SIGALRM, alarmtr);
	getnextfd();
	alarm(10);
	dh = open(dcname, 2); /* read/write */
	alarm(0);

	/* modem is open */
	next_fd = -1;
	if (dh >= 0) {
		fixline(dh, dev->D_speed);
		/* set guard time small so line is in transparant mode */
		slowrite(dh, "\rATS12=1\r");
		if (expect("OK", dh) != 0) {
			logent("NOV no line", _FAILED);
			strcpy(devSel, dev->D_line);
			novcls(dh);
			return CF_DIAL;
		}

		if (pulse)
			slowrite(dh, "ATDP");
		else
			slowrite(dh, "ATDT");
		slowrite(dh, telno);
		slowrite(dh, "\r");

		if (expect("CONNECT", dh) != 0) {
			logent("NOV no carrier", _FAILED);
			strcpy(devSel, dev->D_line);
			novcls(dh);
			return CF_DIAL;
		}

	}
	if (dh < 0) {
		DEBUG(4, "novation failed\n", CNULL);
		delock(dev->D_line);
	}
	DEBUG(4, "novation ok\n", CNULL);
	return dh;
}

novcls(fd)
int fd;
{
	char dcname[20];
	struct sgttyb hup, sav;

	if (fd > 0) {
		sprintf(dcname, "/dev/%s", devSel);
		DEBUG(4, "Hanging up fd = %d\n", fd);
		/*
		 * code to drop DTR -- change to 0 baud then back to default.
		 */
		gtty(fd, &hup);
		gtty(fd, &sav);
		hup.sg_ispeed = B0;
		hup.sg_ospeed = B0;
		stty(fd, &hup);
		sleep(2);
		stty(fd, &sav);
		/*
		 * now raise DTR -- close the device & open it again.
		 */
		sleep(2);
		close(fd);
		sleep(2);
		fd = open(dcname, 2);
		/*
		 * Since we have a getty sleeping on this line, when it wakes up it sends
		 * all kinds of garbage to the modem.  Unfortunatly, the modem likes to
		 * execute the previous command when it sees the garbage.  The previous
		 * command was to dial the phone, so let's make the last command reset
		 * the modem.
		 */
		sleep(2);
		slowrite(fd, "\rATZ\r");
		close(fd);
		delock(devSel);
	}
}
D 2

#endif NOVATION
E 2
E 1
