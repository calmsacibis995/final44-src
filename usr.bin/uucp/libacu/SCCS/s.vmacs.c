h26587
s 00002/00002/00171
d D 8.1 93/06/06 22:09:48 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00165
d D 4.7 91/04/24 17:30:45 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00001/00165
d D 4.6 91/03/02 13:13:49 bostic 6 5
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00001/00001/00165
d D 4.5 88/02/24 21:04:11 rick 5 4
c typo
e
s 00000/00002/00166
d D 4.4 88/02/24 20:45:36 rick 4 3
c remove extraneous ifdefs
e
s 00001/00000/00167
d D 4.3 85/10/10 11:40:23 bloom 3 2
c fix from rick@seismo
e
s 00007/00003/00160
d D 4.2 85/06/23 15:30:09 bloom 2 1
c fixes from rick adams
e
s 00163/00000/00000
d D 4.1 85/01/22 13:04:59 ralph 1 0
c date and time created 85/01/22 13:04:59 by ralph
e
u
U
t
T
I 7
/*-
D 8
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.proprietary.c%
 */

E 7
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
#endif /* not lint */
E 7

D 6
#include "../condevs.h"
E 6
I 6
#include "condevs.h"
E 6
D 5
#ifdef	VMACS
E 5
I 5

E 5
/*
D 4
 * Racal-Vadic 'RV811' MACS system with 831 adaptor.
E 4
 *
 * A typical 300 baud L-devices entry is
 *	ACU /dev/tty10 /dev/tty11,48,1200 300 vmacs
 * where tty10 is the communication line (D_Line),
 * tty11 is the dialer line (D_calldev),
 * the '4' is the dialer address + modem type (viz. dialer 0, Bell 103),
 * and the '8' is the communication port
 * (Note: Based on RVMACS version for 820 dialer.  This version
 *  developed by Doug Kingston @ BRL, 13 December 83.)
 */

#define	SOH	01	/* Abort */
#define	STX	02	/* Access Adaptor */
#define	ETX	03	/* Transfer to Dialer */
#define	SI	017	/* Buffer Empty (end of phone number) */

vmacsopn(ph, flds, dev)
char *ph, *flds[];
struct Devices *dev;
{
	register int va, i, child;
	register char *p;
	char c, acu[20], com[20];
	char	modem, dialer;
	int	dialspeed;
	char c_STX = STX;
	char c_ETX = ETX;
	char c_SI = SI;
	char c_SOH = SOH;

	/* create child to open comm line */
	child = -1;
	sprintf(com, "/dev/%s", dev->D_line);
	if ((child = fork()) == 0) {
		signal(SIGINT, SIG_DFL);
		open(com, 0);
		DEBUG(5, "%s Opened.", com);
		sleep(5);
		exit(1);
	}

	if ((p = index(dev->D_calldev, ',')) == NULL) {
		DEBUG(2, "No dialer/modem specification\n", 0);
		goto failret;
	}
	*p++ = '\0';
	if (*p < '0' || *p > '7') {
		logent(p, "Bad dialer address/modem type");
		goto failret;
	}
	dialer = *p++;
	if (*p < '0' || *p > '>') {
		logent(p, "Bad modem address");
		goto failret;
	}
	modem = *p++;
	if (*p++ == ',')
		dialspeed = atoi (p);
	else
		dialspeed = dev->D_speed;
	if (setjmp(Sjbuf)) {
		logent("vmacsopn", "TIMEOUT");
		i = CF_DIAL;
		goto ret;
	}
	DEBUG(4, "STARTING CALL\n", 0);
	sprintf(acu, "/dev/%s", dev->D_calldev);
	getnextfd();
	signal(SIGALRM, alarmtr);
D 2
	alarm(45);
E 2
I 2
	alarm(60);
E 2
	if ((va = open(acu, 2)) < 0) {
		logent(acu, "CAN'T OPEN");
		i = CF_NODEV;
		goto ret;
	}
	DEBUG(5, "ACU %s opened.\n", acu);
I 3
	next_fd = -1;
E 3
	fixline(va, dialspeed);

	write(va, &c_SOH, 1);		/* abort, reset the dialer */
	do {
		if (read (va, &c, 1) != 1) {
			logent ("MACS initialization", _FAILED);
			goto failret;
		}
	} while ((c&0177) != 'B');
	DEBUG(5, "ACU initialized\n", 0);

	write(va, &c_STX, 1);		/* start text, access adaptor */
	write(va, &dialer, 1);		/* send dialer address digit */
	write(va, &modem, 1);		/* send modem address digit */
D 2
	write(va, ph, strlen(ph));	/* Send Phone Number */
E 2
I 2
	for (p=ph; *p; p++) {
		if (*p == '=' || (*p >= '0' && *p <= '9'))
			write(va, p, 1);
	}
E 2
	write(va, &c_SI, 1);		/* send buffer empty */
	write(va, &c_ETX, 1);		/* end of text, initiate call */

	if (read(va, &c, 1) != 1) {
		logent("ACU READ", _FAILED);
		goto failret;
	}
	switch(c) {
	case 'A':
		/* Fine! */
		DEBUG(5, "Call connected\n", 0);
		break;
	case 'B':
D 2
		DEBUG(2, "CALL ABORTED\n", 0);
E 2
I 2
		DEBUG(2, "Dialer Timeout or Abort\n", 0);
E 2
		goto failret;
	case 'D':
		DEBUG(2, "Dialer format error\n", 0);
		goto failret;
	case 'E':
		DEBUG(2, "Dialer parity error\n", 0);
		goto failret;
	case 'F':
		DEBUG(2, "Phone number too long\n", 0);
		goto failret;
	case 'G':
		DEBUG(2, "Busy signal\n", 0);
		goto failret;
	default:
		DEBUG(2, "Unknown MACS return code '%c'\n", i);
		goto failret;
	}
	/*
	 * open line - will return on carrier
	 */
	if ((i = open(com, 2)) < 0) {
		if (errno == EIO)
			logent("carrier", "LOST");
		else
			logent("dialup open", _FAILED);
		goto failret;
	}
	fixline(i, dev->D_speed);
	goto ret;
failret:
	i = CF_DIAL;
ret:
	alarm(0);
	if (child > 1)
		kill(child, SIGKILL);
	close(va);
I 2
	sleep(2);
E 2
	return i;
}

vmacscls(fd)
register int fd;
{
	char c_SOH = SOH;

	DEBUG(2, "MACS close %d\n", fd);
	write(fd, &c_SOH, 1);
/*	ioctl(fd, TIOCCDTR, NULL);*/
	close(fd);
}
D 4
#endif VMACS
E 4
E 1
