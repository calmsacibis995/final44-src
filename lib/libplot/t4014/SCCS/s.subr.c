h63830
s 00002/00002/00067
d D 8.1 93/06/04 18:16:26 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00061
d D 4.3 91/04/22 16:06:06 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00061
d D 4.2 87/07/15 11:03:54 mckusick 2 1
c missing parens in calculation of "extra byte" (from Keith Muller)
c bug report 4.3BSD/usr.lib/55
e
s 00062/00000/00000
d D 4.1 83/06/27 14:19:28 sam 1 0
c date and time created 83/06/27 14:19:28 by sam
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
int oextra = -1;
cont(x,y){
	int hix,hiy,lox,loy,extra;
	int n;
	x = (x-obotx)*scalex + botx;
	y = (y-oboty)*scaley + boty;
	hix=(x>>7) & 037;
	hiy=(y>>7) & 037;
	lox = (x>>2)&037;
	loy=(y>>2)&037;
D 2
	extra=x&03+(y<<2)&014;
E 2
I 2
	extra=(x&03)+((y<<2)&014);
E 2
	n = (abs(hix-ohix) + abs(hiy-ohiy) + 6) / 12;
	if(hiy != ohiy){
		putch(hiy|040);
		ohiy=hiy;
	}
	if(hix != ohix){
		if(extra != oextra){
			putch(extra|0140);
			oextra=extra;
		}
		putch(loy|0140);
		putch(hix|040);
		ohix=hix;
		oloy=loy;
	}
	else{
		if(extra != oextra){
			putch(extra|0140);
			putch(loy|0140);
			oextra=extra;
			oloy=loy;
		}
		else if(loy != oloy){
			putch(loy|0140);
			oloy=loy;
		}
	}
	putch(lox|0100);
	while(n--)
		putch(0);
}

putch(c){
	putc(c,stdout);
}
E 1
