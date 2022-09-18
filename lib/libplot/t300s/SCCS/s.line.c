h48826
s 00002/00002/00050
d D 8.1 93/06/04 17:50:43 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00051
d D 4.3 93/02/10 00:31:24 torek 3 2
c sqrt() is double; dist2() might as well be too [caught by gcc2]
e
s 00008/00001/00044
d D 4.2 91/04/22 16:01:51 bostic 2 1
c new copyright; att/bsd/shared
e
s 00045/00000/00000
d D 4.1 83/06/27 14:16:29 sam 1 0
c date and time created 83/06/27 14:16:29 by sam
e
u
U
t
T
I 2
/*-
D 4
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

#include "con.h"
line(x0,y0,x1,y1){
	iline(xconv(xsc(x0)),yconv(ysc(y0)),xconv(xsc(x1)),yconv(ysc(y1)));
	return;
}
cont(x0,y0){
	iline(xnow,ynow,xconv(xsc(x0)),yconv(ysc(y0)));
	return;
}
iline(cx0,cy0,cx1,cy1){
	int maxp,tt,j,np;
	char chx,chy,command;
	    float xd,yd;
D 3
	float dist2(),sqrt();
E 3
I 3
	double dist2(),sqrt();
E 3
	movep(cx0,cy0);
	maxp = sqrt(dist2(cx0,cy0,cx1,cy1))/2.;
	xd = cx1-cx0;
	yd = cy1-cy0;
	command = COM|((xd<0)<<1)|(yd<0);
	if(maxp == 0){
		xd=0;
		yd=0;
	}
	else {
		xd /= maxp;
		yd /= maxp;
	}
	inplot();
	spew(command);
	for (tt=0; tt<=maxp; tt++){
		chx= cx0+xd*tt-xnow;
		xnow += chx;
		chx = abval(chx);
		chy = cy0+yd*tt-ynow;
		ynow += chy;
		chy = abval(chy);
		spew(ADDR|chx<<3|chy);
	}
	outplot();
	return;
}
E 1
