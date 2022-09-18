h15579
s 00002/00002/00025
d D 8.1 93/06/04 18:19:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00019
d D 4.3 91/04/22 16:09:34 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00002/00018
d D 4.2 83/11/10 15:24:07 ralph 2 1
c fixed warning messages
e
s 00020/00000/00000
d D 4.1 83/06/27 14:26:21 sam 1 0
c date and time created 83/06/27 14:26:21 by sam
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

extern float boty;
extern float botx;
extern float oboty;
extern float obotx;
extern float scalex;
extern float scaley;
D 2
float deltx 4095.;
float delty 4095.;
E 2
I 2
float deltx = 4095.;
float delty = 4095.;
E 2
space(x0,y0,x1,y1){
	botx = -2047.;
	boty = -2047;
	obotx = x0;
	oboty = y0;
	scalex = deltx/(x1-x0);
	scaley = delty/(y1-y0);
}
E 1
