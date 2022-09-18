h04120
s 00002/00002/00135
d D 8.1 93/06/06 22:09:42 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00129
d D 4.5 91/04/24 17:30:44 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00129
d D 4.4 91/03/02 13:13:47 bostic 4 3
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00002/00130
d D 4.3 88/02/24 20:45:33 rick 3 2
c remove extraneous ifdefs
e
s 00007/00005/00125
d D 4.2 85/10/10 11:42:44 bloom 2 1
c still more fixes from rick@seismo
e
s 00130/00000/00000
d D 4.1 85/01/22 13:04:54 ralph 1 0
c date and time created 85/01/22 13:04:54 by ralph
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
#ifdef VADIC
E 3

/*
 *	vadopn: establish dial-out connection through a Racal-Vadic 3450.
 *	Returns descriptor open to tty for reading and writing.
 *	Negative values (-1...-7) denote errors in connmsg.
 *	Be sure to disconnect tty when done, via HUPCL or stty 0.
 */

vadopn(telno, flds, dev)
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
		DEBUG(1, "timeout vadic open\n", "");
		logent("vadic open", "TIMEOUT");
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
		delock(dev->D_line);
		return CF_NODEV;
	}
	fixline(dh, dev->D_speed);

	DEBUG(4, "calling %s -> ", telno);
	if (dochat(dev, flds, dh)) {
		logent(dcname, "CHAT FAILED");
		close(dh);
		return CF_DIAL;
	}
	delay = 0;
	for (i = 0; i < strlen(telno); ++i) {
		switch(telno[i]) {
		case '=':	/* await dial tone */
		case '-':
		case ',':
		case '<':
		case 'K':
			telno[i] = 'K';
			delay += 5;
			break;
		}
	}
	DEBUG(4, "%s\n", telno);
	for(i = 0; i < 5; ++i) {	/* make 5 tries */
		/* wake up Vadic */
D 2
		write(dh, "\005\r", 2);
E 2
I 2
		write(dh, "\005", 1);
		sleep(1);
		write(dh, "\r", 1);
E 2
		DEBUG(4, "wanted * ", CNULL);
D 2
		ok = expect("*", dh);
E 2
I 2
		ok = expect("*~5", dh);
E 2
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;

		write(dh, "D\r", 2); /* "D" (enter number) command */
		DEBUG(4, "wanted NUMBER?\\r\\n ", CNULL);
D 2
		ok = expect("NUMBER?\r\n", dh);
E 2
I 2
		ok = expect("NUMBER?\r\n~5", dh);
E 2
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;

		/* send telno, send \r */
		write(dh, telno, strlen(telno));
		sleep(1);
		write(dh, "\r", 1);
		DEBUG(4, "wanted %s ", telno);
		ok = expect(telno, dh);
		if (ok == 0)
			ok = expect("\r\n", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;

		write(dh, "\r", 1); /* confirm number */
		DEBUG(4, "wanted DIALING: ", CNULL);
		ok = expect("DIALING: ", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok == 0)
			break;
	}

	if (ok == 0) {
		sleep(10 + delay);	/* give vadic some time */
		DEBUG(4, "wanted ON LINE\\r\\n ", CNULL);
		ok = expect("ON LINE\r\n", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
	}

	if (ok != 0) {
		if (dh > 2)
			close(dh);
		DEBUG(4, "vadDial failed\n", CNULL);
		delock(dev->D_line);
		return CF_DIAL;
	}
	DEBUG(4, "vadic ok\n", CNULL);
	return dh;
}

D 2
vadcls(fd) {

E 2
I 2
vadcls(fd)
{
E 2
	if (fd > 0) {
		close(fd);
		sleep(5);
		delock(devSel);
	}
}
D 3
#endif VADIC
E 3
E 1
