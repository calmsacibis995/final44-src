h51507
s 00002/00002/00035
d D 8.1 93/06/04 17:41:42 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00031
d D 6.2 91/04/22 15:22:41 bostic 2 1
c new copyright; att/bsd/shared
e
s 00037/00000/00000
d D 6.1 86/08/29 15:06:27 sklower 1 0
c date and time created 86/08/29 15:06:27 by sklower
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
 *
 * %sccs.include.proprietary.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint

E 2
I 2
#endif /* not lint */
E 2

#include "grnplot.h"

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
    double xscale=0.0, yscale=0.0;
    if (x1>x0)
	    xscale = GRXMAX/(double)(x1-x0);
    if (y1>y0)
	    yscale = GRYMAX/(double)(y1-y0);
    scale = (xscale > yscale && yscale > 0)? yscale : xscale;
    if (scale == 0.0) scale == 1.0;
    xbot = x0;
    ybot = y0;
}
E 1
