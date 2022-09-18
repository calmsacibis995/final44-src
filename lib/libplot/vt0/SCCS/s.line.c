h02918
s 00002/00002/00024
d D 8.1 93/06/04 18:19:16 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00018
d D 4.2 91/04/22 16:09:31 bostic 2 1
c new copyright; att/bsd/shared
e
s 00019/00000/00000
d D 4.1 83/06/27 14:26:15 sam 1 0
c date and time created 83/06/27 14:26:15 by sam
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

extern vti;
extern xnow,ynow;
line(x0,y0,x1,y1){
	struct{char x,c; int x0,y0,x1,y1;} p;
	p.c = 3;
	p.x0 = xsc(x0);
	p.y0 = ysc(y0);
	p.x1 = xnow = xsc(x1);
	p.y1 = ynow = ysc(y1);
	write(vti,&p.c,9);
}
cont(x0,y0){
	line(xnow,ynow,xsc(x0),ysc(y0));
	return;
}
E 1
