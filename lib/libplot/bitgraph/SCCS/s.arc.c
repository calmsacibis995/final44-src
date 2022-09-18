h01906
s 00002/00002/00094
d D 8.1 93/06/04 17:22:08 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00090
d D 5.3 91/04/22 14:57:05 bostic 4 3
c new copyright; att/bsd/shared
e
s 00009/00002/00087
d D 5.2 85/04/30 16:14:48 dist 3 2
c add copyright
e
s 00001/00001/00088
d D 5.1 85/04/30 15:43:24 dist 2 1
c add copyright
e
s 00089/00000/00000
d D 4.1 83/11/10 11:00:04 ralph 1 0
c date and time created 83/11/10 11:00:04 by ralph
e
u
U
t
T
I 3
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
E 4
 */

E 3
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 3
static char sccsid[] = "@(#)arc.c	4.1 (Berkeley) 11/10/83";
E 2
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint

E 4
I 4
#endif /* not lint */
E 4
E 3

#include "bg.h"

/* should include test for equality? */
#define side(x,y)	(a*(x)+b*(y)+c > 0.0 ? 1 : -1)

/* The beginning and ending points must be distinct. */
arc(xc,yc,xbeg,ybeg,xend,yend)
int xc,yc,xbeg,ybeg,xend,yend;
{
	double r, radius, costheta, sintheta;
	double a, b, c, x, y, tempX;
	int right_side;

	int screen_xc = scaleX(xc);
	int screen_yc = scaleY(yc);

	/* It is more convienient to beg and end relative to center. */
	int screen_xbeg = scaleX(xbeg) - screen_xc;
	int screen_ybeg = scaleY(ybeg) - screen_yc;

	int screen_xend = scaleX(xend) - screen_xc;
	int screen_yend = scaleY(yend) - screen_yc;

	/* probably should check that arc is truely circular */
	r = sqrt( (double) (screen_xbeg*screen_xbeg + screen_ybeg*screen_ybeg) );

	/*
	This method is reasonably efficient, clean, and clever.
	The easy part is generating the next point on the arc.  This is
	done by rotating the points by the angle theta.  Theta is chosen
	so that no rotation will cause more than one pixel of a move.
	This corresponds to a triangle having x side of r and y side of 1.
	The rotation is done (way) below inside the loop.

	Note:  all calculations are done in screen coordinates.
	*/
	if (r <= 1.0) {
		/* radius is mapped to length < 1*/
		point(xc,yc);
		return;
		}

	radius = sqrt(r*r + 1.0);
	sintheta = 1.0/radius;
	costheta = r/radius;

	/*
	The hard part of drawing an arc is figuring out when to stop.
	This method works by drawing the line from the beginning point
	to the ending point.  This splits the plane in half, with the
	arc that we wish to draw on one side of the line.  If we evaluate
	side(x,y) = a*x + b*y + c, then all of the points on one side of the
	line will result in side being positive, and all the points on the
	other side of the line will result in side being negative.

	We want to draw the arc in a counter-clockwise direction, so we
	must find out what the sign of "side" is for a point which is to the 
	"right" of a line drawn from "beg" to "end".  A point which must lie 
	on the right is [xbeg + (yend-ybeg), ybeg - (xend-xbeg)].  (This
	point is perpendicular to the line at "beg").

	Thus, we compute side of the above point, and then compare the
	sign of side for each new point with the sign of the above point.
	When they are different, we terminate the loop.
	*/

	a = (double) (screen_yend - screen_ybeg);
	b = (double) (screen_xend - screen_xbeg);
	c = (double) (screen_yend*screen_xbeg - screen_xend*screen_ybeg);
	right_side = side(screen_xbeg + (screen_yend-screen_ybeg),
			  screen_ybeg - (screen_xend-screen_xbeg) );

	x = screen_xbeg;
	y = screen_ybeg;
	move(xbeg, ybeg);
	do {
		currentx = screen_xc + (int) (x + 0.5);
		currenty = screen_yc + (int) (y + 0.5);
		putchar( ESC );
		printf(":%d;%dd", currentx, currenty);
		tempX = x;
		x = x*costheta - y*sintheta;
		y = tempX*sintheta + y*costheta;
	} while( side(x,y) == right_side );
}
E 1
