/*-
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)aed.h	8.1 (Berkeley) 6/4/93
 */

/*
 * Displays plot files on an AED512 graphics terminal.
 */

#include <stdio.h>
#include <sgtty.h>

extern char dbuf[BUFSIZ];	/* Used to buffer display characters */
extern struct sgttyb sgttyb;	/* Used to save terminal control bits */
extern curx, cury;		/* Current screen position */
extern int xbot, ybot;		/* Coordinates of screen lower-left corner */
extern int scale;		/* The number of pixels per 2**12 units
				 * of world coordinates.
				 */

/* The following variables describe the screen. */

#define GRXMAX	511	/* Maximum x-coordinate of screen */
#define GRYMAX	482	/* Maximum y-coordinate of screen */
