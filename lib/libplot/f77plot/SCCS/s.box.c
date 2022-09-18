h23567
s 00002/00002/00019
d D 8.1 93/06/04 17:34:05 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00015
d D 5.3 91/04/22 15:02:59 bostic 4 3
c new copyright; att/bsd/shared
e
s 00006/00001/00014
d D 5.2 85/06/08 11:07:21 mckusick 3 2
c from berkman
e
s 00008/00001/00007
d D 5.1 85/06/07 09:26:47 dist 2 1
c Add copyright
e
s 00008/00000/00000
d D 1.1 85/01/02 20:29:37 jak 1 0
c date and time created 85/01/02 20:29:37 by jak
e
u
U
t
T
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
E 4
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

E 2
box_(x0, y0, x1, y1)
int *x0, *y0, *x1, *y1;
{
D 3
	box(*x0, *y0, *x1, *y1);
E 3
I 3
	move(*x0, *y0);
	cont(*x0, *y1);
	cont(*x1, *y1);
	cont(*x1, *y0);
	cont(*x0, *y0);
	move(*x1, *y1);
E 3
}
E 1
