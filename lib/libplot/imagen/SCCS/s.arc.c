h54093
s 00002/00002/00118
d D 8.1 93/06/04 17:44:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00114
d D 5.2 91/04/22 15:55:09 bostic 2 1
c new copyright; att/bsd/shared
e
s 00119/00000/00000
d D 5.1 85/09/21 15:05:46 sam 1 0
c date and time created 85/09/21 15:05:46 by sam
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

int del = 20;
step(d){
	del = d;
}
arc(x,y,x0,y0,x1,y1){
	double pc;
	double sqrt();
	int flg,m,xc,yc,xs,ys,qs,qf;
	float dx,dy,r;
	char use;
	dx = x-x0;
	dy = y-y0;
	r = dx*dx+dy*dy;
	pc = r;
	pc = sqrt(pc);
	flg = pc/4;
	if(flg == 0)step(1);
	else if(flg < del)step(flg);
	xc = xs = x0;
	yc = ys = y0;
	move(xs,ys);
	if(x0 == x1 && y0 == y1)flg=0;
	else flg=1;
	qs = quad(x,y,x0,y0);
	qf = quad(x,y,x1,y1);
	if(abs(x-x1) < abs(y-y1)){
		use = 'x';
		if(qs == 2 || qs ==3)m = -1;
		else m=1;
	}
	else {
		use = 'y';
		if(qs > 2)m= -1;
		else m= 1;
	}
	while(1){
		switch(use){
		case 'x':	
			if(qs == 2 || qs == 3)yc -= del;
			else yc += del;
			dy = yc-y;
			pc = r-dy*dy;
			xc = m*sqrt(pc)+x;
			if((x < xs && x >= xc) || ( x > xs && x <= xc) ||
			    (y < ys && y >= yc) || ( y > ys && y <=  yc) )
			{
				if(++qs > 4)qs=1;
				if(qs == 2 || qs == 3)m= -1;
				else m=1;
				flg=1;
			}
			cont(xc,yc);
			xs = xc; 
			ys = yc;
			if(qs == qf && flg == 1)
				switch(qf){
				case 3:
				case 4:	
					if(xs >= x1)return;
					continue;
				case 1:
				case 2:
					if(xs <= x1)return;
				}
			continue;
		case 'y':	
			if(qs > 2)xc += del;
			else xc -= del;
			dx = xc-x;
			pc = r-dx*dx;
			yc = m*sqrt(pc)+y;
			if((x < xs && x >= xc) || ( x > xs && x <= xc ) ||
			    (y < ys && y >= yc) || (y > ys && y <= yc) )
			{
				if(++qs > 4)qs=1;
				if(qs > 2)m = -1;
				else m = 1;
				flg=1;
			}
			cont(xc,yc);
			xs = xc; 
			ys = yc;
			if(qs == qf && flg == 1)
				switch(qs){
				case 1:
				case 4:
					if(ys >= y1)return;
					continue;
				case 2:
				case 3:
					if(ys <= y1)return;
				}
		}
	}
}
quad(x,y,xp,yp){
	if(x < xp)
		if(y <= yp)return(1);
		else return(4);
	else if(x > xp)
		if(y < yp)return(2);
		else return(3);
	else if(y < yp)return(2);
	else return(4);
}
abs(a){
	if(a < 0)return(-a);
	return(a);
}
E 1
