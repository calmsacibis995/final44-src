h25311
s 00002/00002/00026
d D 8.1 93/06/04 17:41:25 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00022
d D 6.2 91/04/22 15:22:37 bostic 2 1
c new copyright; att/bsd/shared
e
s 00027/00000/00000
d D 6.1 86/08/29 15:06:23 sklower 1 0
c date and time created 86/08/29 15:06:23 by sklower
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1986, 1993
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
 *	Line draws a line between two points.
 *
 *	Results:	None.
 *
 *	Side Effects:
 *	A line is drawn on the screen between (x1, y1) and (x2, y2).
 *---------------------------------------------------------
 */
line(x1, y1, x2, y2)
int x1, y1, x2, y2;
{
	move(x1,y1);
	cont(x2,y2);
}
E 1
