h06740
s 00001/00000/00031
d D 8.2 94/01/07 15:08:43 bostic 5 4
c lint
e
s 00002/00002/00029
d D 8.1 93/06/04 17:31:17 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00023
d D 5.2 91/04/22 14:59:33 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00022
d D 5.1 85/05/07 11:27:34 dist 2 1
c Add copyright notice
e
s 00023/00000/00000
d D 4.1 83/11/10 11:53:21 ralph 1 0
c date and time created 83/11/10 11:53:21 by ralph
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
D 3
/*
I 2
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
E 3
 *
D 3
 *	%W% (Berkeley) %G%
E 3
I 3
 * %sccs.include.proprietary.c%
E 3
 *
D 3
 *
E 3
I 3
 *	%W% (Berkeley) %G%
 */

/*
E 3
E 2
 * This accepts plot file formats and produces the appropriate plots
 * for dumb terminals.  It can also be used for printing terminals and
 * lineprinter listings, although there is no way to specify number of
 * lines and columns different from your terminal.  This would be easy
 * to change, and is left as an exercise for the reader.
 */

I 5
#include <stdlib.h>
E 5
#include <math.h>

#define scale(x,y) y = LINES-1-(LINES*y/rangeY +minY); x = COLS*x/rangeX + minX

extern int minX, rangeX;	/* min and range of x */
extern int minY, rangeY;	/* min and range of y */
extern int currentx, currenty;
extern int COLS, LINES;

/* A very large screen! (probably should use malloc) */
#define MAXCOLS		132
#define MAXLINES	90

extern char screenmat[MAXCOLS][MAXLINES];
E 1
