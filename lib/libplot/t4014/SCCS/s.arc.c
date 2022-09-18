h63722
s 00002/00002/00114
d D 8.1 93/06/04 17:51:54 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00108
d D 4.4 91/04/22 16:05:56 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00003/00106
d D 4.3 85/06/23 13:42:32 mckusick 3 2
c check arguments to sqrt() (from jerry@opal)
e
s 00000/00004/00109
d D 4.2 85/01/02 19:11:59 jak 2 1
c move abs.c from arc.c to subr.c so arc.c, sqrt(), etc. 
c are only loaded when actually needed.
e
s 00113/00000/00000
d D 4.1 83/06/27 14:19:12 sam 1 0
c date and time created 83/06/27 14:19:12 by sam
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

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
D 3
	pc = sqrt(pc);
E 3
I 3
	pc = pc > 0 ? sqrt(pc) : 0;
E 3
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
D 3
			xc = m*sqrt(pc)+x;
E 3
I 3
			xc = m*(pc > 0 ? sqrt(pc) : 0)+x;
E 3
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
D 3
			yc = m*sqrt(pc)+y;
E 3
I 3
			yc = m*(pc > 0 ? sqrt(pc) : 0)+y;
E 3
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
D 2
abs(a){
	if(a < 0)return(-a);
	return(a);
}
E 2
E 1
