h24249
s 00002/00002/00025
d D 8.1 93/06/04 17:31:30 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00021
d D 5.2 91/04/22 14:59:35 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00019
d D 5.1 85/05/07 11:39:58 dist 2 1
c Add copyright notice
e
s 00020/00000/00000
d D 4.1 83/11/10 11:54:06 ralph 1 0
c date and time created 83/11/10 11:54:06 by ralph
e
u
U
t
T
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
E 3
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

#include "dumb.h"

line(x0, y0, x1, y1)
	int x0, y0, x1, y1;
{
	int x,y;

	scale(x0, y0);
	x = x1;
	y = y1;
	scale(x, y);
	currentx = x0;
	currenty = y0;
	screenmat[currentx][currenty] = '*';
	dda_line('*', x0, y0, x1, y1);
}
E 1
