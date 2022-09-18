h27900
s 00002/00002/00026
d D 8.1 93/06/04 17:43:14 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00022
d D 5.2 91/04/22 15:49:38 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00020
d D 5.1 85/05/07 12:07:30 dist 2 1
c Add copyright notice
e
s 00021/00000/00000
d D 4.1 83/11/10 14:14:39 ralph 1 0
c date and time created 83/11/10 14:14:39 by ralph
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

#include "hp2648.h"

move(xi,yi)
int xi,yi;
{
	char xb1,xb2,yb1,yb2;
	itoa(xsc(xi),&xb1,&xb2);
	itoa(ysc(yi),&yb1,&yb2);
	buffready(5);
	putchar(PENUP);
	putchar(xb2);
	putchar(xb1);
	putchar(yb2);
	putchar(yb1); 
	currentx = xsc(xi);
	currenty = ysc(yi);
}
E 1
