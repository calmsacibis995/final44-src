h12414
s 00002/00002/00149
d D 8.1 93/06/06 22:08:54 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00143
d D 4.5 91/04/24 17:30:32 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00143
d D 4.4 91/03/02 13:13:32 bostic 4 3
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00002/00144
d D 4.3 88/02/24 20:45:15 rick 3 2
c remove extraneous ifdefs
e
s 00008/00005/00138
d D 4.2 85/06/23 15:15:29 bloom 2 1
c fixes from rick adams
e
s 00143/00000/00000
d D 4.1 85/01/22 13:04:19 ralph 1 0
c date and time created 85/01/22 13:04:19 by ralph
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
#ifdef DF02
E 3

/*
 *	df2opn(ph, flds, dev)	dial remote machine
 *
 *	return codes:
 *		file descriptor  -  succeeded
 *		FAIL  -  failed
 */
df2opn(ph, flds, dev)
char *ph;
char *flds[];
struct Devices *dev;
{
	char dcname[20], dnname[20], phone[MAXPH+2], c = 0;
D 2
#ifdef	SYSIII
E 2
I 2
#ifdef	USG
E 2
	struct termio ttbuf;
D 2
#endif
E 2
I 2
#endif  USG
E 2
	int dcf, dnf;
	int nw, lt, pid, st, status;
	unsigned timelim;
I 2
#ifdef	TIOCFLUSH
	int zero = 0;
#endif	TIOCFLUSH
E 2

	sprintf(dnname, "/dev/%s", dev->D_calldev);
	if (setjmp(Sjbuf)) {
		logent(dnname, "CAN'T OPEN");
		DEBUG(4, "%s Open timed out\n", dnname);
		return CF_NODEV;
	}
	signal(SIGALRM, alarmtr);
	getnextfd();
	errno = 0;
	alarm(10);
	dnf = open(dnname, 2 );
	alarm(0);
	next_fd = -1;
	if (dnf < 0 && errno == EACCES) {
		logent(dnname, "CAN'T OPEN");
		delock(dev->D_line);
		logent("DEVICE", "NO");
		return CF_NODEV;
	}
	fioclex(dnf);

	sprintf(dcname, "/dev/%s", dev->D_line);
	fixline(dnf, dev->D_speed);
	sprintf(phone, "\02%s", ph);
	DEBUG(4, "dc - %s, ", dcname);
	DEBUG(4, "acu - %s\n", dnname);
	pid = 0;
	if (setjmp(Sjbuf)) {
		logent("DIALUP DN write", "TIMEOUT");
		if (pid)
			kill(pid, 9);
		delock(dev->D_line);
		if (dnf)
			close(dnf);
		return CF_DIAL;
	}
	signal(SIGALRM, alarmtr);
	timelim = 5 * strlen(phone);
	alarm(timelim < 30 ? 30 : timelim);
	if ((pid = fork()) == 0) {
		sleep(2);
		fclose(stdin);
		fclose(stdout);
#ifdef TIOCFLUSH
D 2
		ioctl(dnf, TIOCFLUSH, STBNULL);
E 2
I 2
		ioctl(dnf, TIOCFLUSH, &zero);
E 2
#endif TIOCFLUSH
		write(dnf, "\01", 1);
		sleep(1);
		nw = write(dnf, phone, lt = strlen(phone));
		if (nw != lt) {
			logent("DIALUP ACU write", _FAILED);
			exit(1);
		}
		DEBUG(4, "ACU write ok%s\n", CNULL);
		exit(0);
	}
	/*  open line - will return on carrier */
	/* RT needs a sleep here because it returns immediately from open */

#if RT
	sleep(15);
#endif

	if (read(dnf, &c, 1) != 1 || c != 'A')
		dcf = -1;
	else
		dcf = 0;
	DEBUG(4, "dcf is %d\n", dcf);
	if (dcf < 0) {
		logent("DIALUP LINE open", _FAILED);
		alarm(0);
		kill(pid, 9);
		close(dnf);
		delock(dev->D_line);
		return CF_DIAL;
	}
	dcf = dnf;
	dnf = 0;
	while ((nw = wait(&lt)) != pid && nw != -1)
		;
D 2
#ifdef	SYSIII
E 2
I 2
#ifdef	USG
E 2
	ioctl(dcf, TCGETA, &ttbuf);
	if(!(ttbuf.c_cflag & HUPCL)) {
		ttbuf.c_cflag |= HUPCL;
		ioctl(dcf, TCSETA, &ttbuf);
	}
D 2
#endif SYSIII
E 2
I 2
#endif USG
E 2
	alarm(0);
	fflush(stdout);
	fixline(dcf, dev->D_speed);
	DEBUG(4, "Fork Stat %o\n", lt);
	if (lt != 0) {
		close(dcf);
		if (dnf)
			close(dnf);
		delock(dev->D_line);
		return CF_DIAL;
	}
	return dcf;
}

/*
 * df2cls()	close the DF02/DF03 call unit
 *
 *	return codes: none
 */
df2cls(fd)
register int fd;
{
	if (fd > 0) {
		close(fd);
		sleep(5);
		delock(devSel);
	}
}
D 3
#endif DF02
E 3
E 1
