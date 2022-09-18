h05920
s 00002/00002/00165
d D 8.1 93/06/04 17:51:14 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00166
d D 4.3 93/02/10 00:31:26 torek 3 2
c sqrt() is double; dist2() might as well be too [caught by gcc2]
e
s 00008/00001/00159
d D 4.2 91/04/22 16:01:55 bostic 2 1
c new copyright; att/bsd/shared
e
s 00160/00000/00000
d D 4.1 83/06/27 14:16:36 sam 1 0
c date and time created 83/06/27 14:16:36 by sam
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
	spew(ESC);
	spew (INPLOT);
}

outplot()
{
	spew(ESC);
	spew(ACK);
	spew(ESC);
	spew(ACK);
	fflush(stdout);
	stty (OUTF, &ITTY);
}

spew(ch)
{
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

#define DOUBLE 010
#define ADDR 0100
#define COM 060
#define MAXX 070
#define MAXY 07
extern xnow,ynow;
#define SPACES 7
movep(ix,iy){
	int dx,dy,remx,remy,pts,i;
	int xd,yd;
	int addr,command;
	char c;
	if(xnow == ix && ynow == iy)return;
	inplot();
	dx = ix-xnow;
	dy = iy-ynow;
	command = COM|PENUP|((dx<0)<<1)|(dy<0);
	dx = abval(dx);
	dy = abval(dy);
	xd = dx/(SPACES*2);
	yd = dy/(SPACES*2);
	pts = xd<yd?xd:yd;
	if((i=pts)>0){
		c=command|DOUBLE;
		addr=ADDR;
		if(xd>0)addr|=MAXX;
		if(yd>0)addr|=MAXY;
		spew(c);
		while(i--){
			spew(addr);
		}
	}
	if(xd!=yd){
		if(xd>pts){
			i=xd-pts;
			addr=ADDR|MAXX;
		}
		else{
			i=yd-pts;
			addr=ADDR|MAXY;
		}
		c=command|DOUBLE;
		spew(c);
		while(i--){
			spew(addr);
		}
	}
	remx=dx-xd*SPACES*2;
	remy=dy-yd*SPACES*2;
	addr=ADDR;
	i = 0;
	if(remx>7){
		i=1;
		addr|=MAXX;
		remx -= 7;
	}
	if(remy>7){
		i=1;
		addr|=MAXY;
		remy -= 7;
	}
	while(i--){
		spew(command);
		spew(addr);
	}
	if(remx>0||remy>0){
		spew(command);
		spew(ADDR|remx<<3|remy);
	}
	xnow=ix;
	ynow=iy;
	outplot();
	return;
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
