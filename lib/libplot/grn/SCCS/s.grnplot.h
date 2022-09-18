h57386
s 00002/00002/00032
d D 8.1 93/06/04 17:41:17 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00026
d D 6.2 91/04/22 15:22:36 bostic 2 1
c new copyright; att/bsd/shared
e
s 00032/00000/00000
d D 6.1 86/08/29 15:06:21 sklower 1 0
c date and time created 86/08/29 15:06:21 by sklower
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
E 2
 *
I 2
 * %sccs.include.proprietary.c%
 *
E 2
 *	%W% (Berkeley) %G%
D 2
 *	modified to grnplot by Brad Rubenstein 8/29/86
E 2
 */

/*
D 2
 * Given a plot file, produces a grn file
E 2
I 2
 * Given a plot file, produces a grn file.
 *
 * Modified to grnplot by Brad Rubenstein 8/29/86.
E 2
 */

#include <stdio.h>

extern curx, cury;		/* Current screen position */
extern int xbot, ybot;		/* Coordinates of screen lower-left corner */
extern double scale;		/* The number of pixels per 2**12 units
				 * of world coordinates.
				 */
extern int linestyle;
extern int invector, ingrnfile;

#define FONTSIZE 1
#define FONTSTYLE 1
#define DEFAULTLINE 5
#define POINTSTRING "."

/* The following variables describe the screen. */

#define GRXMAX	512	/* Maximum x-coordinate of screen */
#define GRYMAX	512	/* Maximum y-coordinate of screen */
E 1
