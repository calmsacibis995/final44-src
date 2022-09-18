h35896
s 00002/00002/00121
d D 8.1 93/06/04 17:49:47 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00122
d D 4.3 93/02/10 00:25:31 torek 3 2
c sqrt() is double; dist2() might as well be too [caught by gcc2]
e
s 00008/00001/00115
d D 4.2 91/04/22 15:59:57 bostic 2 1
c new copyright; att/bsd/shared
e
s 00116/00000/00000
d D 4.1 83/06/27 14:09:12 sam 1 0
c date and time created 83/06/27 14:09:12 by sam
e
u
U
t
T
I 2
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

#include <stdio.h>
#include "con.h"
abval(q)
{
	return (q>=0 ? q : -q);
}

xconv (xp)
{
	/* x position input is -2047 to +2047, output must be 0 to PAGSIZ*HORZRES */
	xp += 2048;
	/* the computation is newx = xp*(PAGSIZ*HORZRES)/4096 */
	return (xoffset + xp /xscale);
}

yconv (yp)
{
	/* see description of xconv */
	yp += 2048;
	return (yp / yscale);
}

inplot()
{
	stty(OUTF, &PTTY);
	spew (ACK);
}

outplot()
{
	spew(ESC);
	spew(ACK);
	fflush(stdout);
	stty(OUTF, &ITTY);
}

spew(ch)
{
	if(ch == UP)putc(ESC,stdout);
	putc(ch, stdout);
}

tobotleft ()
{
	move(-2048,-2048);
}
reset()
{
	outplot();
	exit();
}

D 3
float
E 3
I 3
double
E 3
dist2 (x1, y1, x2, y2)
{
	float t,v;
	t = x2-x1;
	v = y1-y2;
	return (t*t+v*v);
}

swap (pa, pb)
int *pa, *pb;
{
	int t;
	t = *pa;
	*pa = *pb;
	*pb = t;
}
movep (xg, yg)
{
	int i,ch;
	if((xg == xnow) && (yg == ynow))return;
	/* if we need to go to left margin, just CR */
	if (xg < xnow/2)
	{
		spew(CR);
		xnow = 0;
	}
	i = (xg-xnow)/HORZRES;
	if(xnow < xg)ch = RIGHT;
	else ch = LEFT;
	xnow += i*HORZRES;
	i = abval(i);
	while(i--)spew(ch);
	i = abval(xg-xnow);
	inplot();
	while(i--) spew(ch);
	outplot();
	i=(yg-ynow)/VERTRES;
	if(ynow < yg)ch = UP;
	else ch = DOWN;
	ynow += i*VERTRES;
	i = abval(i);
	while(i--)spew(ch);
	i=abval(yg-ynow);
	inplot();
	while(i--)spew(ch);
	outplot();
	xnow = xg; ynow = yg;
}

xsc(xi){
	int xa;
	xa = (xi - obotx) * scalex + botx;
	return(xa);
}
ysc(yi){
	int ya;
	ya = (yi - oboty) *scaley +boty;
	return(ya);
}
E 1
