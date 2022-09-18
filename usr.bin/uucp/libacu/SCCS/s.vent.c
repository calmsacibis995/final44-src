h08838
s 00002/00002/00103
d D 8.1 93/06/06 22:09:45 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00097
d D 4.5 91/04/24 17:30:45 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00097
d D 4.4 91/03/02 13:13:48 bostic 4 3
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00002/00098
d D 4.3 88/02/24 20:45:35 rick 3 2
c remove extraneous ifdefs
e
s 00001/00000/00099
d D 4.2 85/10/10 11:41:37 bloom 2 1
c reset alarm (from rick@seismo)
e
s 00099/00000/00000
d D 4.1 85/01/22 13:04:57 ralph 1 0
c date and time created 85/01/22 13:04:57 by ralph
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
#ifdef	VENTEL
E 3

ventopn(telno, flds, dev)
char *flds[], *telno;
struct Devices *dev;
{
	int	dh;
	int	i, ok = -1;
	char dcname[20];

	sprintf(dcname, "/dev/%s", dev->D_line);
	if (setjmp(Sjbuf)) {
		DEBUG(1, "timeout ventel open\n", "");
		logent("ventel open", "TIMEOUT");
		if (dh >= 0)
			close(dh);
		delock(dev->D_line);
		return CF_NODEV;
	}
	signal(SIGALRM, alarmtr);
	getnextfd();
	alarm(10);
	dh = open(dcname, 2);
	next_fd = -1;
I 2
	alarm(0);
E 2
	if (dh < 0) {
		DEBUG(4,"%s\n", errno == 4 ? "no carrier" : "can't open modem");
		delock(dev->D_line);
		return errno == 4 ? CF_DIAL : CF_NODEV;
	}

	/* modem is open */
	fixline(dh, dev->D_speed);

	/* translate - to % and = to & for VenTel */
	DEBUG(4, "calling %s -> ", telno);
	for (i = 0; i < strlen(telno); ++i) {
		switch(telno[i]) {
		case '-':	/* delay */
			telno[i] = '%';
			break;
		case '=':	/* await dial tone */
			telno[i] = '&';
			break;
		case '<':
			telno[i] = '%';
			break;
		}
	}
	DEBUG(4, "%s\n", telno);
	sleep(1);
	for(i = 0; i < 5; ++i) {	/* make up to 5 tries */
		slowrite(dh, "\r\r");/* awake, thou lowly VenTel! */

		DEBUG(4, "wanted %s ", "$");
		ok = expect("$", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok != 0)
			continue;
		slowrite(dh, "K");	/* "K" (enter number) command */
		DEBUG(4, "wanted %s ", "DIAL: ");
		ok = expect("DIAL: ", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
		if (ok == 0)
			break;
	}

	if (ok == 0) {
		slowrite(dh, telno); /* send telno, send \r */
		slowrite(dh, "\r");
		DEBUG(4, "wanted %s ", "ONLINE");
		ok = expect("ONLINE!", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
	}
	if (ok != 0) {
		if (dh > 2)
			close(dh);
		DEBUG(4, "venDial failed\n", "");
		return CF_DIAL;
	} 
	else
		DEBUG(4, "venDial ok\n", "");
	return dh;
}

ventcls(fd)
int fd;
{
	if (fd > 0) {
		close(fd);
		sleep(5);
		delock(devSel);
	}
}
D 3
#endif VENTEL
E 3
E 1
