h32339
s 00002/00002/00019
d D 8.1 93/06/04 17:22:26 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00015
d D 5.3 91/04/22 14:57:09 bostic 4 3
c new copyright; att/bsd/shared
e
s 00009/00002/00012
d D 5.2 85/04/30 16:15:05 dist 3 2
c add copyright
e
s 00001/00001/00013
d D 5.1 85/04/30 15:43:37 dist 2 1
c add copyright
e
s 00014/00000/00000
d D 4.1 83/11/10 11:01:06 ralph 1 0
c date and time created 83/11/10 11:01:06 by ralph
e
u
U
t
T
I 3
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

E 3
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 3
static char sccsid[] = "@(#)cont.c	4.1 (Berkeley) 11/10/83";
E 2
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint

E 4
I 4
#endif /* not lint */
E 4
E 3

#include "bg.h"

cont(xi,yi)
int xi,yi;
{
	currentx = scaleX(xi);
	currenty = scaleY(yi);
	putchar( ESC );
	printf(":%d;%dd", currentx, currenty);
}
E 1
