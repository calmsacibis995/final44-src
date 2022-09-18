h44544
s 00002/00002/00034
d D 8.1 93/06/04 17:20:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00027
d D 5.2 91/04/22 14:54:45 bostic 4 2
c new copyright; att/bsd/shared
e
s 00009/00002/00027
d R 5.2 85/04/30 16:06:00 dist 3 2
c add copyright
e
s 00001/00001/00028
d D 5.1 85/04/30 15:47:58 dist 2 1
c add copyright
e
s 00029/00000/00000
d D 4.1 83/11/11 15:12:27 ralph 1 0
c date and time created 83/11/11 15:12:27 by ralph
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
static char sccsid[] = "@(#)label.c	4.1 (Berkeley) 11/11/83";
E 2
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

#include "aed.h"

/*---------------------------------------------------------
 *	This routine places a label starting at the current
 *	position.
 *
 *	Results:	None.
 *
 *	Side Effects:
 *	The string indicated by s starting at (curx, cury).
 *	The current position is updated accordingly.
 *---------------------------------------------------------
 */
label(s)
char *s;
{
    setcolor("02");
    putc('Q', stdout);
    outxy20(curx + (4096/scale), cury + (4096/scale));
    putc('\6', stdout);
    fputs(s, stdout);
    putc('\33', stdout);
    (void) fflush(stdout);
    curx += ((6*4096*strlen(s)) + 4000)/scale;
}
E 1
