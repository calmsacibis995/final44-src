h55173
s 00002/00002/00055
d D 8.1 93/06/04 17:49:35 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00049
d D 4.2 91/04/22 15:59:55 bostic 2 1
c new copyright; att/bsd/shared
e
s 00051/00000/00000
d D 4.1 83/06/27 14:09:08 sam 1 0
c date and time created 83/06/27 14:09:08 by sam
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
#endif /* not lint */
E 2

D 2
#
E 2
#include <sgtty.h>
/* gsi plotting output routines */
# define DOWN 012
# define UP 013
# define LEFT 010
# define RIGHT 040
# define BEL 007
# define ACK 006
# define CR 015
# define FF 014
# define VERTRESP 48
# define HORZRESP 60.
# define HORZRES 6.
# define VERTRES 8.
/* down is line feed, up is reverse oyne feed,
   left is bwckspace, right is space.  48 points per inch
   vertically, 60 horizontally */

int xnow, ynow;
int OUTF;
struct sgttyb ITTY, PTTY;
float HEIGHT = 6.0, WIDTH = 6.0, OFFSET = 0.0;
int xscale, xoffset, yscale;
float botx = 0., boty = 0., obotx = 0., oboty = 0.;
float scalex = 1., scaley = 1.;

openpl ()
{
	int reset();
		xnow = ynow = 0;
		OUTF = 1;
		printf("\r");
		gtty(OUTF, &ITTY);
		signal (2, reset);
		PTTY = ITTY;
		PTTY.sg_flags &= ~CRMOD;	/* don't map lf */
		/* initialize constants */
		xscale  = 4096./(HORZRESP * WIDTH);
		yscale = 4096 /(VERTRESP * HEIGHT);
		xoffset = OFFSET * HORZRESP;
		return;
}

openvt(){
openpl();
}
E 1
