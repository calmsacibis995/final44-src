h56247
s 00002/00002/00037
d D 8.1 93/06/04 17:20:24 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00030
d D 5.2 91/04/22 14:54:50 bostic 4 2
c new copyright; att/bsd/shared
e
s 00009/00002/00030
d R 5.2 85/04/30 16:06:18 dist 3 2
c add copyright
e
s 00001/00001/00031
d D 5.1 85/04/30 15:48:14 dist 2 1
c add copyright
e
s 00032/00000/00000
d D 4.1 83/11/11 15:12:46 ralph 1 0
c date and time created 83/11/11 15:12:46 by ralph
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 4
static char sccsid[] = "@(#)space.c	4.1 (Berkeley) 11/11/83";
E 2
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

#include "aed.h"

/*---------------------------------------------------------
 *	Space sets up the world-to-screen transformation so
 *	that the rectangular area described by (x0, y0) and
 *	(x1, y1) will all be on-screen.
 *
 *	Results:	None.
 *
 *	Side Effects:
 *	Our own variables scale, xbot, and ybot are changed.
 *---------------------------------------------------------
 */
space(x0, y0, x1, y1)
int x0, y0, x1, y1;
{
    int xscale, yscale, xsize, ysize;
    xscale = (GRXMAX<<12)/(x1-x0);
    yscale = (GRYMAX<<12)/(y1-y0);
    if (xscale > yscale) scale = yscale;
    else scale = xscale;
    scale = (scale*9)/10 - 1;
    if (scale<1) scale = 1;
    xsize = (2048*GRXMAX)/scale + 1;
    xbot = (x1+x0)/2 - xsize;
    ysize = (2048*GRYMAX)/scale + 1;
    ybot = (y1+y0)/2 - ysize;
}
E 1
