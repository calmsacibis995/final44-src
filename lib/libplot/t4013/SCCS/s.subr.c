h00449
s 00002/00002/00053
d D 8.1 93/06/04 17:52:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00049
d D 5.2 91/04/22 16:03:44 bostic 4 3
c new copyright; att/bsd/shared
e
s 00007/00001/00047
d D 5.1 85/06/07 08:28:37 dist 3 2
c Add copyright
e
s 00000/00004/00048
d D 1.2 85/03/27 10:20:00 ralph 2 1
c abs is in standard C library.
e
s 00052/00000/00000
d D 1.1 85/01/02 20:10:49 jak 1 0
c date and time created 85/01/02 20:10:49 by jak
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
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
E 4
 */

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 3

#include <stdio.h>
float obotx = 0.;
float oboty = 0.;
float botx = 0.;
float boty = 0.;
float scalex = 1.;
float scaley = 1.;
int scaleflag;

int oloy = -1;
int ohiy = -1;
int ohix = -1;
cont(x,y){
	int hix,hiy,lox,loy;
	int n;
	x = (x-obotx)*scalex + botx;
	y = (y-oboty)*scaley + boty;
	hix=(x>>5) & 037;
	hiy=(y>>5) & 037;
	lox = x & 037;
	loy = y & 037;
	n = (abs(hix-ohix) + abs(hiy-ohiy) + 6) / 12;
	if(hiy != ohiy){
		putch(hiy|040);
		ohiy=hiy;
	}
	if(hix != ohix){
		putch(loy|0140);
		putch(hix|040);
		ohix=hix;
		oloy=loy;
	}
	else if(loy != oloy){
		putch(loy|0140);
		oloy=loy;
	}
	putch(lox|0100);
	while(n--)
		putch(0);
}

putch(c){
	putc(c,stdout);
}
D 2
abs(a){
	if(a < 0)return(-a);
	return(a);
}
E 2
E 1
