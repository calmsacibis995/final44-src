h13883
s 00002/00002/00054
d D 8.1 93/06/04 17:42:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00050
d D 5.2 91/04/22 15:49:30 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00048
d D 5.1 85/05/07 12:07:04 dist 2 1
c Add copyright notice
e
s 00049/00000/00000
d D 4.1 83/11/10 14:12:19 ralph 1 0
c date and time created 83/11/10 14:12:19 by ralph
e
u
U
t
T
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
E 3
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

#include "hp2648.h"

arc(xcent,ycent,xbeg,ybeg,xend,yend)
int xcent,ycent,xbeg,ybeg,xend,yend;
{
	double costheta,sintheta,x,y,xn,r;
	double x1,y1,x2,y2;
	int xi,yi,crosspflag,crossp;

	r = (xcent-xbeg)*(xcent-xbeg)+(ycent-ybeg)*(ycent-ybeg);
	r = pow(r,0.5);
	if(r<1){
		point(xcent,ycent);
		return;
	}
	sintheta = 1.0/r;
	costheta = pow(1-sintheta*sintheta,0.5);
	xi = x = xbeg-xcent;
	yi = y = ybeg-ycent;
	x1 = xcent;
	y1 = ycent;
	x2 = xend;
	y2 = yend;
	crosspflag = 0;
	do {
		crossp = cross_product(x1,y1,x2,y2,x,y);
		if(crossp >0 && crosspflag == 0) crosspflag = 1;
		point(xcent+xi,ycent+yi);
		xn = x;
		xi = x = x*costheta + y*sintheta;
		yi = y = y*costheta - xn*sintheta;
	} while( crosspflag == 0 || crossp >0);
}

cross_product(x1,y1,x2,y2,x3,y3)
double x1,x2,x3,y1,y2,y3;
{
	double z,a,b;
	a = (y3-y2)*(x2-x1);
	b = (x3-x2)*(y2-y1);
	z = a-b;
	if(z<0) return(-1);
	if(z>0) return(1);
	return(0);
}
E 1
