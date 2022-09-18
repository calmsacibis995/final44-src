h06497
s 00002/00002/00026
d D 8.1 93/06/04 18:16:22 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00020
d D 4.2 91/04/22 16:06:05 bostic 2 1
c new copyright; att/bsd/shared
e
s 00021/00000/00000
d D 4.1 83/06/27 14:19:27 sam 1 0
c date and time created 83/06/27 14:19:27 by sam
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
#endif /* not lint */
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
	scalex = 3120./(x1-x0);
	scaley = 3120./(y1-y0);
}
E 1
