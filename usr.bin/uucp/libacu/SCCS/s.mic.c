h26496
s 00002/00002/00115
d D 8.1 93/06/06 22:09:12 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00109
d D 4.4 91/04/24 17:30:37 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00109
d D 4.3 91/03/02 13:13:38 bostic 3 2
c ANSI (real bug fix!), break up into multiple directories, new style
c Makefiles
e
s 00000/00000/00110
d D 4.2 88/02/24 20:45:21 rick 2 1
c remove extraneous ifdefs
e
s 00110/00000/00000
d D 4.1 85/01/22 13:04:31 ralph 1 0
c date and time created 85/01/22 13:04:31 by ralph
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
#ifdef MICOM

/*
 *	micopn: establish connection through a micom.
 *	Returns descriptor open to tty for reading and writing.
 *	Negative values (-1...-7) denote errors in connmsg.
 *	Be sure to disconnect tty when done, via HUPCL or stty 0.
 */
micopn(flds)
register char *flds[];
{
	extern errno;
	char *rindex(), *fdig(), dcname[20];
	int dh, ok = 0, speed;
	register struct condev *cd;
	register FILE *dfp;
	struct Devices dev;

	dfp = fopen(DEVFILE, "r");
	ASSERT(dfp != NULL, "Can't open", DEVFILE, 0);

	signal(SIGALRM, alarmtr);
	dh = -1;
	for(cd = condevs; ((cd->CU_meth != NULL)&&(dh < 0)); cd++) {
		if (snccmp(flds[F_LINE], cd->CU_meth) == SAME) {
			fseek(dfp, (off_t)0, 0);
			while(rddev(dfp, &dev) != FAIL) {
				if (strcmp(flds[F_CLASS], dev.D_class) != SAME)
					continue;
				if (snccmp(flds[F_LINE], dev.D_type) != SAME)
					continue;
				if (mlock(dev.D_line) == FAIL)
					continue;

				sprintf(dcname, "/dev/%s", dev.D_line);
				getnextfd();
				alarm(10);
				if (setjmp(Sjbuf)) {
					delock(dev.D_line);
					logent(dev.D_line,"micom open TIMEOUT");
					dh = -1;
					break;
				}
				dh = open(dcname, 2);
				alarm(0);
				next_fd = -1;
				if (dh > 0) {
					break;
				}
				devSel[0] = '\0';
				delock(dev.D_line);
			}
		}
	}
	fclose(dfp);
	if (dh < 0)
		return CF_NODEV;

	speed = atoi(fdig(flds[F_CLASS]));
	fixline(dh, speed);
	sleep(1);

	/* negotiate with micom */
	if (speed != 4800)	/* damn their eyes! */
		write(dh, "\r", 1);
	else
		write(dh, " ", 1);

	DEBUG(4, "wanted %s ", "SELECTION");
	ok = expect("SELECTION", dh);
	DEBUG(4, "got %s\n", ok ? "?" : "that");
	if (ok == 0) {
		write(dh, flds[F_PHONE], strlen(flds[F_PHONE]));
		sleep(1);
		write(dh, "\r", 1);
		DEBUG(4, "wanted %s ", "GO");
		ok = expect("GO", dh);
		DEBUG(4, "got %s\n", ok ? "?" : "that");
	}

	if (ok != 0) {
		if (dh > 2)
			close(dh);
		DEBUG(4, "micom failed\n", "");
		delock(dev.D_line);
		return(CF_DIAL);
	} 
	else
		DEBUG(4, "micom ok\n", "");

	CU_end = cd->CU_clos;
	strcat(devSel, dev.D_line);	/* for later unlock */
	return dh;
}

miccls(fd)
register int fd;
{

	if (fd > 0) {
		close(fd);
		delock(devSel);
	}
}
#endif MICOM
E 1
