h44619
s 00002/00002/00037
d D 8.1 93/06/04 17:41:35 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00033
d D 6.2 91/04/22 15:22:39 bostic 2 1
c new copyright; att/bsd/shared
e
s 00039/00000/00000
d D 6.1 86/08/29 15:06:25 sklower 1 0
c date and time created 86/08/29 15:06:25 by sklower
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

/*
 * converts plot to grn
 */

#include "grnplot.h"

int curx, cury;		/* Current world position */
int xbot=0, ybot=0;	/* Coordinates of screen lower-left corner */
double scale=1;		/* The number of pixels per 2**12 units
			 * of world coordinates.
			 */
int linestyle = 5;
int	ingrnfile = 0;
int	invector = 0;


/*---------------------------------------------------------
 *	Openpl initializes the graphics display and clears its screen.
 *
 *	Results:	None.
 *
 *	Side Effects:
 *
 *	Errors:		None.
 *---------------------------------------------------------
 */
openpl()
{}
E 1
