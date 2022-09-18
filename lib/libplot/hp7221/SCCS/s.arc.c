h58498
s 00002/00002/00050
d D 8.1 93/06/04 17:43:26 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00046
d D 5.2 91/04/22 15:52:52 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00044
d D 5.1 85/05/07 12:14:27 dist 2 1
c Add copyright notice
e
s 00045/00000/00000
d D 4.1 83/11/10 14:30:00 ralph 1 0
c date and time created 83/11/10 14:30:00 by ralph
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

#include "hp7221.h"

/* 
 * 7221 requires knowing the anlge of arc.  To do this, the triangle formula
 *	c^2 = a^2 + b^2 - 2*a*b*cos(angle)
 * is used where "a" and "b" are the radius of the circle and "c" is the
 * distance between the beginning point and the end point.
 *
 * This gives us "angle" or angle - 180.  To find out which, draw a line from
 * beg to center.  This splits the plane in half.  All points on one side of the
 * plane will have the same sign when plugged into the equation for the line.
 * Pick a point on the "right side" of the line (see program below).  If "end"
 * has the same sign as this point does, then they are both on the same side
 * of the line and so angle is < 180.  Otherwise, angle > 180.
 */
   
#define side(x,y)	(a*(x)+b*(y)+c > 0.0 ? 1 : -1)

arc(xcent,ycent,xbeg,ybeg,xend,yend)
int xcent,ycent,xbeg,ybeg,xend,yend;
{
	double radius2, c2;
	double a,b,c;
	int angle;

	/* Probably should check that this is really a circular arc.  */
	radius2 = (xcent-xbeg)*(xcent-xbeg) + (ycent-ybeg)*(ycent-ybeg);
	c2 = (xend-xbeg)*(xend-xbeg) + (yend-ybeg)*(yend-ybeg);
	angle = (int) ( 180.0/PI * acos(1.0 - c2/(2.0*radius2)) + 0.5 );

	a = (double) (ycent - ybeg);
	b = (double) (xcent - xbeg);
	c = (double) (ycent*xbeg - xcent*ybeg);
	if (side(xbeg + (ycent-ybeg), ybeg - (xcent-xbeg)) != side(xend,yend))
		angle += 180;
	
	move(xcent, ycent);
	/* Not quite implemented...
	printf("C(A%d c)[%d,%d]", angle, xbeg, ybeg);
	*/
}
E 1
