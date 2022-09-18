h41335
s 00002/00002/00032
d D 8.1 93/06/04 17:37:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00029
d D 5.2 91/04/22 15:05:27 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00001/00025
d D 5.1 85/05/07 11:42:49 dist 2 1
c Add copyright notice
e
s 00026/00000/00000
d D 4.1 83/11/10 16:30:26 ralph 1 0
c date and time created 83/11/10 16:30:26 by ralph
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
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
 *
 *	%W% (Berkeley) %G%
 */

E 2
/*
 * Displays plot files on a gigi "graphics" terminal.
 */

#include <stdio.h>
#include <math.h>

#define ESC	033
#define PI	3.141592659

/*
 * The graphics address range is 0..XMAX, YMAX..0 where (0, YMAX) is the
 * lower left corner.
 */
#define XMAX	767
#define YMAX	479
#define xsc(xi)	((int) ((xi -lowx)*scalex +0.5))
#define ysc(yi)	((int) (YMAX - (yi - lowy)*scaley +0.5))

extern int currentx;
extern int currenty;
extern double lowx;
extern double lowy;
extern double scalex;
extern double scaley;
E 1
