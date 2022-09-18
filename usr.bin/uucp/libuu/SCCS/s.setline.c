h03326
s 00002/00002/00055
d D 8.1 93/06/06 22:11:12 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00049
d D 5.4 91/04/24 17:33:51 bostic 4 3
c new copyright; att/bsd/shared
e
s 00004/00001/00046
d D 5.3 85/06/20 10:15:15 bloom 3 2
c fixes from rick adams
e
s 00008/00010/00039
d D 5.2 85/01/22 14:10:51 ralph 2 1
c bug fixes and changes from Rick Adams
e
s 00049/00000/00000
d D 5.1 83/07/02 17:57:30 sam 1 0
c date and time created 83/07/02 17:57:30 by sam
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

D 2
/***
 *	setline - optimize line setting for sending or receiving files
 *
 *	return code - none
 */

E 2
#include "uucp.h"
D 2
#ifdef	SYSIII
E 2
I 2
#ifdef	USG
E 2
#include <termio.h>
#endif

#define PACKSIZE	64
#define SNDFILE	'S'
#define RCVFILE 'R'
#define RESET	'X'

I 3
/*LINTLIBRARY*/

E 3
I 2
/*
 *	optimize line setting for sending or receiving files
 *
 *	return code - none
 */
E 2
D 3
setline(type)
E 3
I 3
/*ARGSUSED*/
setupline(type)
E 3
char type;
{
D 2
#ifdef	SYSIII
E 2
I 2
#ifdef	USG
E 2
	static struct termio tbuf, sbuf;
	static int set = 0;

	DEBUG(2, "setline - %c\n", type);
D 2
	if (Unet)
E 2
I 2
	if (IsTcpIp)
E 2
		return;
	switch(type) {
	case SNDFILE:
		break;
	case RCVFILE:
		ioctl(Ifn, TCGETA, &tbuf);
		sbuf = tbuf;
		tbuf.c_cc[VMIN] = PACKSIZE;
		ioctl(Ifn, TCSETAW, &tbuf);
		set++;
		break;
	case RESET:
		if (set == 0) break;
D 2
/* Anticipatory bug fixes: set, sbuf now static, 'set' is now reset.  rti!trt */
E 2
		set = 0;
		ioctl(Ifn, TCSETAW, &sbuf);
		break;
	}
#endif
}
E 1
