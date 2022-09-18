h01938
s 00000/00002/00048
d D 8.2 94/01/07 15:08:44 bostic 5 4
c lint
e
s 00002/00002/00048
d D 8.1 93/06/04 17:31:59 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00044
d D 5.2 91/04/22 14:59:39 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00042
d D 5.1 85/05/07 11:40:18 dist 2 1
c Add copyright notice
e
s 00042/00000/00000
d D 4.1 83/11/10 11:55:19 ralph 1 0
c date and time created 83/11/10 11:55:19 by ralph
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

#include "dumb.h"

/* Does not plot first point -- assumed that it is already plotted */
dda_line(ch, x0, y0, x1, y1)
	char ch;
	int x0, y0;	/* already transformed to screen coords */
	int x1, y1;	/* untransformed */
{
	int length, i;
	double deltaX, deltaY;
	double x, y;
D 5
	double floor();
	int abs();
E 5

	scale(x1, y1);

	length = abs(x1 - x0);
	if (abs(y1 -y0) > length)
		length = abs(y1 - y0);

	if (length == 0)
		return;

	deltaX = (double) (x1 - x0)/(double) length;
	deltaY = (double) (y1 - y0)/(double) length;

	x = (double) x0 + 0.5;
	y = (double) y0 + 0.5;

	for (i=0; i < length; ++i) {
		x += deltaX;
		y += deltaY;
		x0 = floor(x);
		y0 = floor(y);
		currentx = x0;
		currenty = y0;
		screenmat[currentx][currenty] = ch;
	}
}
E 1
