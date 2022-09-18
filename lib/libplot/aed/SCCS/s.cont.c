h24053
s 00002/00002/00023
d D 8.1 93/06/04 17:19:47 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00016
d D 5.2 91/04/22 14:54:42 bostic 5 2
c new copyright; att/bsd/shared
e
s 00009/00002/00016
d R 5.3 85/04/30 16:05:52 dist 4 3
c add copyright
e
s 00000/00000/00018
d R 5.2 85/04/30 15:47:52 dist 3 2
c add copyright
e
s 00001/00001/00017
d D 5.1 85/04/30 15:39:01 dist 2 1
c add copyright
e
s 00018/00000/00000
d D 4.1 83/11/11 15:12:17 ralph 1 0
c date and time created 83/11/11 15:12:17 by ralph
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
D 5
static char sccsid[] = "@(#)cont.c	4.1 (Berkeley) 11/11/83";
E 2
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include "aed.h"

/*---------------------------------------------------------
 *	Cont plots a line between (curx, cury) and (x, y).
 *
 *	Results:	None.
 *	Side Effects:	As above.
 *---------------------------------------------------------
 */
cont(x, y)
int x, y;
{
    line(curx, cury, x, y);
}
E 1
