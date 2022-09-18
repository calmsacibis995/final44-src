h62609
s 00002/00002/00070
d D 8.1 93/06/04 16:59:10 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00072
d D 5.5 90/10/09 17:46:42 bostic 6 5
c new copyright notice
e
s 00001/00011/00076
d D 5.4 90/06/01 15:38:04 bostic 5 4
c new copyright notice
e
s 00010/00005/00077
d D 5.3 88/06/30 17:35:31 bostic 4 3
c install approved copyright notice
e
s 00016/00012/00066
d D 5.2 88/04/29 13:17:11 bostic 3 2
c add Berkeley specific header
e
s 00000/00000/00078
d D 5.1 87/11/30 18:41:24 bostic 2 1
c tahoe release
e
s 00078/00000/00000
d D 1.1 87/07/24 13:32:05 zliu 1 0
c date and time created 87/07/24 13:32:05 by zliu
e
u
U
t
T
I 1
D 3
/* 
E 3
I 3
/*
E 3
D 7
 * Copyright (c) 1987 Regents of the University of California.
D 3
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 3
I 3
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
D 6
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
E 6
E 3
 */

#ifndef lint
D 3
static char sccsid[] = "%W%	%I% (ucb.elefunt) %G%";
#endif	/* not lint */
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "trig.h"
double
sin(x)
double x;
{
	double a,c,z;

        if(!finite(x))		/* sin(NaN) and sin(INF) must be NaN */
		return x-x;
	x=drem(x,PI2);		/* reduce x into [-PI,PI] */
	a=copysign(x,one);
	if (a >= PIo4) {
		if(a >= PI3o4)		/* ... in [3PI/4,PI] */
			x = copysign((a = PI-a),x);
		else {			/* ... in [PI/4,3PI/4]  */
			a = PIo2-a;		/* rtn. sign(x)*C(PI/2-|x|) */
			z = a*a;
			c = cos__C(z);
			z *= half;
			a = (z >= thresh ? half-((z-half)-c) : one-(z-c));
			return copysign(a,x);
		}
	}

	if (a < small) {		/* rtn. S(x) */
		big+a;
		return x;
	}
	return x+x*sin__S(x*x);
}

double
cos(x) 
double x;
{
	double a,c,z,s = 1.0;

	if(!finite(x))		/* cos(NaN) and cos(INF) must be NaN */
		return x-x;
	x=drem(x,PI2);		/* reduce x into [-PI,PI] */
	a=copysign(x,one);
	if (a >= PIo4) {
		if (a >= PI3o4) {	/* ... in [3PI/4,PI] */
			a = PI-a;
			s = negone;
		}
		else {			/* ... in [PI/4,3PI/4] */
			a = PIo2-a;
			return a+a*sin__S(a*a);	/* rtn. S(PI/2-|x|) */ 
		}
	}
	if (a < small) {
		big+a;
		return s;		/* rtn. s*C(a) */
	}
	z = a*a;
	c = cos__C(z);
	z *= half;
	a = (z >= thresh ? half-((z-half)-c) : one-(z-c));
	return copysign(a,s);
}
E 1
