/*-
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)dumb.h	8.2 (Berkeley) 1/7/94
 */

/*
 * This accepts plot file formats and produces the appropriate plots
 * for dumb terminals.  It can also be used for printing terminals and
 * lineprinter listings, although there is no way to specify number of
 * lines and columns different from your terminal.  This would be easy
 * to change, and is left as an exercise for the reader.
 */

#include <stdlib.h>
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
