h50895
s 00002/00002/00054
d D 8.1 93/06/04 17:49:15 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00055
d D 4.3 93/02/10 00:25:30 torek 3 2
c sqrt() is double; dist2() might as well be too [caught by gcc2]
e
s 00008/00001/00048
d D 4.2 91/04/22 15:59:53 bostic 2 1
c new copyright; att/bsd/shared
e
s 00049/00000/00000
d D 4.1 83/06/27 14:09:04 sam 1 0
c date and time created 83/06/27 14:09:04 by sam
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
	char chx,chy;
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
		if(xd >= 0)chx = RIGHT;
		else chx = LEFT;
		if(yd >= 0)chy = UP;
		else chy = DOWN;
		if(maxp==0){
			xd=0;
			yd=0;
		}
		else{
			xd /= maxp;
			yd /= maxp;
		}
		inplot();
		for (tt=0; tt<=maxp; tt++){
			j= cx0+xd*tt-xnow;
			xnow += j;
			j = abval(j);
			while(j-- > 0)spew(chx);
			j = cy0+yd*tt-ynow;
			ynow += j;
			j = abval(j);
			while(j-- > 0)spew(chy);
			spew ('.');
		}
		outplot();
		return;
}
E 1
