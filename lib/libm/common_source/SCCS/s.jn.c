h16581
s 00000/00001/00285
d D 8.2 93/11/30 16:30:30 mckusick 11 10
c lint
e
s 00002/00002/00284
d D 8.1 93/06/04 17:03:14 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00254/00089/00032
d D 5.5 92/12/16 18:06:04 bostic 9 8
c new versions from Peter McIlroy (derived from Sun Microsystems release)
e
s 00005/00004/00116
d D 5.4 91/04/20 14:21:39 bostic 8 7
c new copyright; att/bsd/shared
e
s 00001/00004/00119
d D 5.3 88/09/22 16:23:21 bostic 7 6
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00008/00003/00115
d D 5.2 88/04/29 12:19:48 bostic 6 5
c add Berkeley copyright; NOTE: this code is AT&T derived!
e
s 00000/00000/00118
d D 5.1 87/11/30 18:34:02 bostic 5 4
c tahoe release
e
s 00007/00007/00111
d D 1.4 87/07/13 19:20:39 zliu 4 3
c clean-ups.
e
s 00002/00002/00116
d D 1.3 87/07/07 01:31:56 zliu 3 2
c first shot at TAHOE.
e
s 00002/00001/00116
d D 1.2 85/09/11 23:54:16 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00117/00000/00000
d D 1.1 85/09/06 17:52:56 zliu 1 0
c date and time created 85/09/06 17:52:56 by zliu
e
u
U
t
T
I 6
D 8
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
D 9
 * Copyright (c) 1985 The Regents of the University of California.
E 9
I 9
D 10
 * Copyright (c) 1992 The Regents of the University of California.
E 9
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 9
 * %sccs.include.proprietary.c%
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
 */

E 6
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (ELEFUNT) %G%";
E 2
I 2
D 6
static char sccsid[] =
"%Z%%M%	4.2 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G%";
E 2
D 4
#endif not lint
E 4
I 4
#endif	/* not lint */
E 6
I 6
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6
E 4

/*
D 9
	floating point Bessel's function of
	the first and second kinds and of
	integer order.
E 9
I 9
 * 16 December 1992
 * Minor modifications by Peter McIlroy to adapt non-IEEE architecture.
 */
E 9

D 9
	int n;
	double x;
	jn(n,x);
E 9
I 9
/*
 * ====================================================
 * Copyright (C) 1992 by Sun Microsystems, Inc.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 *
 * ******************* WARNING ********************
 * This is an alpha version of SunPro's FDLIBM (Freely
 * Distributable Math Library) for IEEE double precision 
 * arithmetic. FDLIBM is a basic math library written
 * in C that runs on machines that conform to IEEE 
 * Standard 754/854. This alpha version is distributed 
 * for testing purpose. Those who use this software 
 * should report any bugs to 
 *
 *		fdlibm-comments@sunpro.eng.sun.com
 *
 * -- K.C. Ng, Oct 12, 1992
 * ************************************************
 */
E 9

D 9
	returns the value of Jn(x) for all
	integer values of n and all real values
	of x.
E 9
I 9
/*
 * jn(int n, double x), yn(int n, double x)
 * floating point Bessel's function of the 1st and 2nd kind
 * of order n
 *          
 * Special cases:
 *	y0(0)=y1(0)=yn(n,0) = -inf with division by zero signal;
 *	y0(-ve)=y1(-ve)=yn(n,-ve) are NaN with invalid signal.
 * Note 2. About jn(n,x), yn(n,x)
 *	For n=0, j0(x) is called,
 *	for n=1, j1(x) is called,
 *	for n<x, forward recursion us used starting
 *	from values of j0(x) and j1(x).
 *	for n>x, a continued fraction approximation to
 *	j(n,x)/j(n-1,x) is evaluated and then backward
 *	recursion is used starting from a supposed value
 *	for j(n,x). The resulting value of j(0,x) is
 *	compared with the actual value to correct the
 *	supposed value of j(n,x).
 *
 *	yn(n,x) is similar in all respects, except
 *	that forward recursion is used for all
 *	values of n>1.
 *	
 */
E 9

D 9
	There are no error returns.
	Calls j0, j1.
E 9
I 9
#include <math.h>
#include <float.h>
#include <errno.h>
E 9

D 9
	For n=0, j0(x) is called,
	for n=1, j1(x) is called,
	for n<x, forward recursion us used starting
	from values of j0(x) and j1(x).
	for n>x, a continued fraction approximation to
	j(n,x)/j(n-1,x) is evaluated and then backward
	recursion is used starting from a supposed value
	for j(n,x). The resulting value of j(0,x) is
	compared with the actual value to correct the
	supposed value of j(n,x).
E 9
I 9
#if defined(vax) || defined(tahoe)
#define _IEEE	0
#else
#define _IEEE	1
#define infnan(x) (0.0)
#endif
E 9

D 9
	yn(n,x) is similar in all respects, except
	that forward recursion is used for all
	values of n>1.
*/
E 9
I 9
D 11
extern double j0(),j1(),log(),fabs(),sqrt(),cos(),sin(),y0(),y1();
E 11
static double
invsqrtpi= 5.641895835477562869480794515607725858441e-0001,
two  = 2.0,
zero = 0.0,
one  = 1.0;
E 9

D 7
#include <math.h>
E 7
I 7
D 9
#include "mathimpl.h"
E 7
D 3
#ifdef VAX
E 3
I 3
D 4
#if defined(VAX)
E 4
I 4
#if defined(vax)||defined(tahoe)
E 4
E 3
#include <errno.h>
D 4
#else	/* IEEE double */
E 4
I 4
#else	/* defined(vax)||defined(tahoe) */
E 4
static double zero = 0.e0;
D 4
#endif
E 4
I 4
#endif	/* defined(vax)||defined(tahoe) */
E 4

double
jn(n,x) int n; double x;{
	int i;
E 9
I 9
double jn(n,x)
	int n; double x;
{
	int i, sgn;
E 9
	double a, b, temp;
D 9
	double xsq, t;
E 9
I 9
	double z, w;
E 9
D 7
	double j0(), j1();
E 7

D 9
	if(n<0){
E 9
I 9
    /* J(-n,x) = (-1)^n * J(n, x), J(n, -x) = (-1)^n * J(n, x)
     * Thus, J(-n,x) = J(n,-x)
     */
    /* if J(n,NaN) is NaN */
	if (_IEEE && isnan(x)) return x+x;
	if (n<0){		
E 9
		n = -n;
		x = -x;
	}
D 9
	if(n==0) return(j0(x));
	if(n==1) return(j1(x));
	if(x == 0.) return(0.);
	if(n>x) goto recurs;

	a = j0(x);
	b = j1(x);
	for(i=1;i<n;i++){
		temp = b;
		b = (2.*i/x)*b - a;
		a = temp;
E 9
I 9
	if (n==0) return(j0(x));
	if (n==1) return(j1(x));
	sgn = (n&1)&(x < zero);		/* even n -- 0, odd n -- sign(x) */
	x = fabs(x);
	if (x == 0 || !finite (x)) 	/* if x is 0 or inf */
	    b = zero;
	else if ((double) n <= x) {
			/* Safe to use J(n+1,x)=2n/x *J(n,x)-J(n-1,x) */
	    if (_IEEE && x >= 8.148143905337944345e+090) {
					/* x >= 2**302 */
    /* (x >> n**2) 
     *	    Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
     *	    Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
     *	    Let s=sin(x), c=cos(x), 
     *		xn=x-(2n+1)*pi/4, sqt2 = sqrt(2),then
     *
     *		   n	sin(xn)*sqt2	cos(xn)*sqt2
     *		----------------------------------
     *		   0	 s-c		 c+s
     *		   1	-s-c 		-c+s
     *		   2	-s+c		-c-s
     *		   3	 s+c		 c-s
     */
		switch(n&3) {
		    case 0: temp =  cos(x)+sin(x); break;
		    case 1: temp = -cos(x)+sin(x); break;
		    case 2: temp = -cos(x)-sin(x); break;
		    case 3: temp =  cos(x)-sin(x); break;
		}
		b = invsqrtpi*temp/sqrt(x);
	    } else {	
	        a = j0(x);
	        b = j1(x);
	        for(i=1;i<n;i++){
		    temp = b;
		    b = b*((double)(i+i)/x) - a; /* avoid underflow */
		    a = temp;
	        }
	    }
	} else {
	    if (x < 1.86264514923095703125e-009) { /* x < 2**-29 */
    /* x is tiny, return the first Taylor expansion of J(n,x) 
     * J(n,x) = 1/n!*(x/2)^n  - ...
     */
		if (n > 33)	/* underflow */
		    b = zero;
		else {
		    temp = x*0.5; b = temp;
		    for (a=one,i=2;i<=n;i++) {
			a *= (double)i;		/* a = n! */
			b *= temp;		/* b = (x/2)^n */
		    }
		    b = b/a;
		}
	    } else {
		/* use backward recurrence */
		/* 			x      x^2      x^2       
		 *  J(n,x)/J(n-1,x) =  ----   ------   ------   .....
		 *			2n  - 2(n+1) - 2(n+2)
		 *
		 * 			1      1        1       
		 *  (for large x)   =  ----  ------   ------   .....
		 *			2n   2(n+1)   2(n+2)
		 *			-- - ------ - ------ - 
		 *			 x     x         x
		 *
		 * Let w = 2n/x and h=2/x, then the above quotient
		 * is equal to the continued fraction:
		 *		    1
		 *	= -----------------------
		 *		       1
		 *	   w - -----------------
		 *			  1
		 * 	        w+h - ---------
		 *		       w+2h - ...
		 *
		 * To determine how many terms needed, let
		 * Q(0) = w, Q(1) = w(w+h) - 1,
		 * Q(k) = (w+k*h)*Q(k-1) - Q(k-2),
		 * When Q(k) > 1e4	good for single 
		 * When Q(k) > 1e9	good for double 
		 * When Q(k) > 1e17	good for quadruple 
		 */
	    /* determine k */
		double t,v;
		double q0,q1,h,tmp; int k,m;
		w  = (n+n)/(double)x; h = 2.0/(double)x;
		q0 = w;  z = w+h; q1 = w*z - 1.0; k=1;
		while (q1<1.0e9) {
			k += 1; z += h;
			tmp = z*q1 - q0;
			q0 = q1;
			q1 = tmp;
		}
		m = n+n;
		for(t=zero, i = 2*(n+k); i>=m; i -= 2) t = one/(i/x-t);
		a = t;
		b = one;
		/*  estimate log((2/x)^n*n!) = n*log(2/x)+n*ln(n)
		 *  Hence, if n*(log(2n/x)) > ...
		 *  single 8.8722839355e+01
		 *  double 7.09782712893383973096e+02
		 *  long double 1.1356523406294143949491931077970765006170e+04
		 *  then recurrent value may overflow and the result will
		 *  likely underflow to zero
		 */
		tmp = n;
		v = two/x;
		tmp = tmp*log(fabs(v*tmp));
	    	for (i=n-1;i>0;i--){
		        temp = b;
		        b = ((i+i)/x)*b - a;
		        a = temp;
		    /* scale b to avoid spurious overflow */
#			if defined(vax) || defined(tahoe)
#				define BMAX 1e13
#			else
#				define BMAX 1e100
#			endif /* defined(vax) || defined(tahoe) */
			if (b > BMAX) {
				a /= b;
				t /= b;
				b = one;
			}
		}
	    	b = (t*j0(x)/b);
	    }
E 9
	}
D 9
	return(b);

recurs:
	xsq = x*x;
	for(t=0,i=n+16;i>n;i--){
		t = xsq/(2.*i - t);
	}
	t = x/(2.*n-t);

	a = t;
	b = 1;
	for(i=n-1;i>0;i--){
		temp = b;
		b = (2.*i/x)*b - a;
		a = temp;
	}
	return(t*j0(x)/b);
E 9
I 9
	return ((sgn == 1) ? -b : b);
E 9
}
D 9

double
yn(n,x) int n; double x;{
	int i;
	int sign;
E 9
I 9
double yn(n,x) 
	int n; double x;
{
	int i, sign;
E 9
	double a, b, temp;
D 7
	double y0(), y1();
E 7

D 9
	if (x <= 0) {
D 3
#ifdef VAX
E 3
I 3
D 4
#if defined(VAX)
E 4
I 4
#if defined(vax)||defined(tahoe)
E 4
E 3
D 7
		extern double infnan();
E 7
		return(infnan(EDOM));	/* NaN */
D 4
#else	/* IEEE double */
E 4
I 4
#else	/* defined(vax)||defined(tahoe) */
E 4
		return(zero/zero);	/* IEEE machines: invalid operation */
D 4
#endif
E 4
I 4
#endif	/* defined(vax)||defined(tahoe) */
E 4
	}
E 9
I 9
    /* Y(n,NaN), Y(n, x < 0) is NaN */
	if (x <= 0 || (_IEEE && x != x))
		if (_IEEE && x < 0) return zero/zero;
		else if (x < 0)     return (infnan(EDOM));
		else if (_IEEE)     return -one/zero;
		else		    return(infnan(-ERANGE));
	else if (!finite(x)) return(0);
E 9
	sign = 1;
D 9
	if(n<0){
E 9
I 9
	if (n<0){
E 9
		n = -n;
D 9
		if(n%2 == 1) sign = -1;
E 9
I 9
		sign = 1 - ((n&1)<<2);
E 9
	}
D 9
	if(n==0) return(y0(x));
	if(n==1) return(sign*y1(x));

	a = y0(x);
	b = y1(x);
	for(i=1;i<n;i++){
E 9
I 9
	if (n == 0) return(y0(x));
	if (n == 1) return(sign*y1(x));
	if(_IEEE && x >= 8.148143905337944345e+090) { /* x > 2**302 */
    /* (x >> n**2) 
     *	    Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
     *	    Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
     *	    Let s=sin(x), c=cos(x), 
     *		xn=x-(2n+1)*pi/4, sqt2 = sqrt(2),then
     *
     *		   n	sin(xn)*sqt2	cos(xn)*sqt2
     *		----------------------------------
     *		   0	 s-c		 c+s
     *		   1	-s-c 		-c+s
     *		   2	-s+c		-c-s
     *		   3	 s+c		 c-s
     */
		switch (n&3) {
		    case 0: temp =  sin(x)-cos(x); break;
		    case 1: temp = -sin(x)-cos(x); break;
		    case 2: temp = -sin(x)+cos(x); break;
		    case 3: temp =  sin(x)+cos(x); break;
		}
		b = invsqrtpi*temp/sqrt(x);
	} else {
	    a = y0(x);
	    b = y1(x);
	/* quit if b is -inf */
	    for (i = 1; i < n && !finite(b); i++){
E 9
		temp = b;
D 9
		b = (2.*i/x)*b - a;
E 9
I 9
		b = ((double)(i+i)/x)*b - a;
E 9
		a = temp;
I 9
	    }
E 9
	}
D 9
	return(sign*b);
E 9
I 9
	if (!_IEEE && !finite(b))
		return (infnan(-sign * ERANGE));
	return ((sign > 0) ? b : -b);
E 9
}
E 1
