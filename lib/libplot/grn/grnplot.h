/*-
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)grnplot.h	8.1 (Berkeley) 6/4/93
 */

/*
 * Given a plot file, produces a grn file.
 *
 * Modified to grnplot by Brad Rubenstein 8/29/86.
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
