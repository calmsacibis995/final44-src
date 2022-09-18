h41156
s 00002/00002/00032
d D 8.1 93/06/04 17:20:04 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00026
d D 5.3 91/04/22 14:54:45 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00025
d D 5.2 85/06/06 19:09:44 mckusick 4 2
c fix botched copyright
e
s 00042/00002/00025
d R 5.2 85/04/30 16:06:03 dist 3 2
c add copyright
e
s 00001/00001/00026
d D 5.1 85/04/30 15:48:01 dist 2 1
c add copyright
e
s 00027/00000/00000
d D 4.1 83/11/11 15:12:30 ralph 1 0
c date and time created 83/11/11 15:12:30 by ralph
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 4
static char sccsid[] = "@(#)line.c	4.1 (Berkeley) 11/11/83";
E 2
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 4

#include "aed.h"

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
    setcolor("01");
    putc('Q', stdout);
    outxy20(x1, y1);
    putc('A', stdout);
    outxy20(x2, y2);
    (void) fflush(stdout);
    curx = x2;
    cury = y2;
}
E 1
