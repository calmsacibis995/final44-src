h37970
s 00002/00002/00026
d D 8.1 93/06/07 20:40:07 bostic 5 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00026
d R 8.1 93/06/04 17:52:04 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00022
d D 5.2 91/04/22 16:03:44 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00020
d D 5.1 85/06/07 08:28:24 dist 2 1
c Add copyright
e
s 00021/00000/00000
d D 1.1 85/01/02 20:10:48 jak 1 0
c date and time created 85/01/02 20:10:48 by jak
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
D 5
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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

extern float botx;
extern float boty;
extern float obotx;
extern float oboty;
extern float scalex;
extern float scaley;
extern int scaleflag;
space(x0,y0,x1,y1){
	botx = 0.;
	boty = 0.;
	obotx = x0;
	oboty = y0;
	if(scaleflag)
		return;
	scalex = 780./(x1-x0);
	scaley = 780./(y1-y0);
}
E 1
