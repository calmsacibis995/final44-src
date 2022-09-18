h39418
s 00002/00002/00161
d D 8.1 93/06/06 22:09:09 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00155
d D 4.4 91/04/24 17:30:36 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00155
d D 4.3 91/03/02 13:13:37 bostic 3 2
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00003/00156
d D 4.2 88/02/24 20:45:20 rick 2 1
c remove extraneous ifdefs
e
s 00159/00000/00000
d D 4.1 85/01/22 13:04:29 ralph 1 0
c date and time created 85/01/22 13:04:29 by ralph
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
#ifdef HAYESQ
E 2
/*
 * New dialout routine to work with Hayes' SMART MODEM
 * 13-JUL-82, Mike Mitchell
 * Modified 23-MAR-83 to work with Tom Truscott's (rti!trt)
 * version of UUCP	(ncsu!mcm)
 *
 * The modem should be set to NOT send any result codes to
 * the system (switch 3 up, 4 down). This end will figure out
 * what is wrong.
 *
 * I had lots of problems with the modem sending
 * result codes since I am using the same modem for both incomming and
 * outgoing calls.  I'd occasionally miss the result code (getty would
 * grab it), and the connect would fail.  Worse yet, the getty would
 * think the result code was a user name, and send garbage to it while
 * it was in the command state.  I turned off ALL result codes, and hope
 * for the best.  99% of the time the modem is in the correct state.
 * Occassionally it doesn't connect, or the phone was busy, etc., and
 * uucico sits there trying to log in.  It eventually times out, calling
 * clsacu() in the process, so it resets itself for the next attempt.
 */

/*
 * NOTE: this version is not for the faint-hearted.
 * Someday it would be nice to have a single version of hayes dialer
 * with a way to specify the switch settings that are on the dialer
 * as well as tone/pulse.
 * In the meantime, using HAYES rather than HAYESQ is probably best.
 */

hysqpopn(telno, flds, dev)
char *telno, *flds[];
struct Devices *dev;
{
	return hysqopn(telno, flds, dev, 0);
}

hysqtopn(telno, flds, dev)
char *telno, *flds[];
struct Devices *dev;
{
	return hysqopn(telno, flds, dev, 1);
}

hysqopn(telno, flds, dev, toneflag)
char *telno, *flds[];
struct Devices *dev;
int toneflag;
{
	char dcname[20], phone[MAXPH+10], c = 0;
#ifdef	USG
	struct termio ttbuf;
#endif USG
	int status, dnf;
	unsigned timelim;

	signal(SIGALRM, alarmtr);
	sprintf(dcname, "/dev/%s", dev->D_line);

	getnextfd();
	if (setjmp(Sjbuf)) {
		logent("DEVICE", "NO");
		DEBUG(4, "Open timed out %s", dcname);
		return CF_NODEV;
	}
	alarm(10);

	if ((dnf = open(dcname, 2)) <= 0) {
		logent("DEVICE", "NO");
		DEBUG(4, "Can't open %s", dcname);
		return CF_NODEV;
	}

	alarm(0);
	next_fd = -1;
	fixline(dnf, dev->D_speed);
	DEBUG(4, "Hayes port - %s, ", dcname);

	if (toneflag)
		sprintf(phone, "\rATDT%s\r", telno);
	else
		sprintf(phone, "\rATDP%s\r", telno);

	write(dnf, phone, strlen(phone));

	/* calculate delay time for the other system to answer the phone.
	 * Default is 15 seconds, add 2 seconds for each comma in the phone
	 * number.
	 */
	timelim = 150;
	while(*telno) {
		c = *telno++;
		if (c == ',')
			timelim += 20;
		else if (toneflag)
			timelim += 2;	/* .2 seconds per tone */
		else {
			if (c == '0') timelim += 10;   /* .1 sec per digit */
			else if (c > '0' && c <= '9')
				timelim += (c - '0');
		}
	}
	alarm(timelim/10 + 1);
	if (setjmp(Sjbuf) == 0) {
		read(dnf, &c, 1);
		alarm(0);
	}

	return dnf;
}

hysqcls(fd)
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
		write(fd, "\rATZ\r", 5);
		close(fd);
		delock(devSel);
	}
}
D 2

#endif HAYESQ
E 2
E 1
