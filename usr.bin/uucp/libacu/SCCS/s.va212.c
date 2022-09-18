h52276
s 00002/00002/00129
d D 8.1 93/06/06 22:09:33 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00123
d D 4.5 91/04/24 17:30:42 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00123
d D 4.4 91/03/02 13:13:44 bostic 4 3
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00002/00124
d D 4.3 88/02/24 20:45:29 rick 3 2
c remove extraneous ifdefs
e
s 00002/00002/00124
d D 4.2 85/06/23 15:26:50 bloom 2 1
c fixes from rick adams
e
s 00126/00000/00000
d D 4.1 85/01/22 13:04:47 ralph 1 0
c date and time created 85/01/22 13:04:47 by ralph
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

D 3
#ifdef VA212
E 3
va212opn(telno, flds, dev)
char *telno;
char *flds[];
struct Devices *dev;
{
	int	dh = -1;
	int	i, ok, er = 0, delay;
	extern errno;
	char dcname[20];

	sprintf(dcname, "/dev/%s", dev->D_line);
	if (setjmp(Sjbuf)) {
		DEBUG(1, "timeout va212 open\n", 0);
		logent("va212 open", "TIMEOUT");
		if (dh >= 0)
			close(dh);
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
		DEBUG (4, errno == 4 ? "%s: no carrier\n" : "%s: can't open\n",
		dcname);
		delock(dev->D_line);
		return errno == 4 ? CF_DIAL : CF_NODEV;
	}
	fixline(dh, dev->D_speed);

	/* translate - to K for Vadic */
	DEBUG(4, "calling %s -> ", telno);
	delay = 0;
	for (i = 0; i < strlen(telno); ++i) {
		switch(telno[i]) {
		case '=':	/* await dial tone */
		case '-':	/* delay */
		case '<':
			telno[i] = 'K';
			delay += 5;
			break;
		}
	}
	DEBUG(4, "%s\n", telno);
	for(i = 0; i < TRYCALLS; ++i) {	/* make TRYCALLS tries */
		/* wake up Vadic */
		sendthem("\005\\d", dh);
		DEBUG(4, "wanted * ", CNULL);
		ok = expect("*", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;

		sendthem("D\\d", dh);	/* "D" (enter number) command */
		DEBUG(4, "wanted NUMBER? ", CNULL);
		ok = expect("NUMBER?", dh);
		if (ok == 0)
			ok = expect("\n", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;

		/* send telno, send \r */
		sendthem(telno, dh);
		DEBUG(4, "wanted %s ", telno);
		ok = expect(telno, dh);
		if (ok == 0)
			ok = expect("\n", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;

		sendthem("", dh); /* confirm number */
		DEBUG(4, "wanted %s ", "DIALING...");
		ok = expect("DIALING...", dh);
		if (ok == 0) {
			ok = expect("\n", dh);
			DEBUG(4, "wanted ANSWER TONE", CNULL);
			ok = expect("ANSWER TONE", dh);
			if (ok == 0)
				ok = expect("\n", dh);
		}
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok == 0)
			break;
	}

	if (ok == 0) {
D 2
		DEBUG(4, "wanted ON LINE \\r\\n ", CNULL);
		ok = expect("ON LINE \r\n", dh);
E 2
I 2
		DEBUG(4, "wanted ON LINE\\r\\n ", CNULL);
		ok = expect("ON LINE\r\n", dh);
E 2
		DEBUG(4, "got %s\n", ok ? "?" : "that");
	}

	if (ok != 0) {
		sendthem("I\\d", dh);	/* back to idle */
		if (dh > 2)
			close(dh);
		DEBUG(4, "vadDial failed\n", CNULL);
		delock(dev->D_line);
		return CF_DIAL;
	}
	DEBUG(4, "va212 ok\n", 0);
	return dh;
}

va212cls(fd)
{
	if (fd > 0) {
		close(fd);
		sleep(5);
		delock(devSel);
	}
}
D 3
#endif VA212
E 3
E 1
