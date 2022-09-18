h18539
s 00002/00002/00187
d D 8.1 93/06/04 17:04:15 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00001/00174
d D 5.11 93/05/02 20:24:39 hibler 19 18
c pow_P needs to test for x==0 and x==+inf since __log__D will fail 
c given those values
e
s 00004/00004/00171
d D 5.10 93/01/10 12:47:58 bostic 18 17
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00006/00005/00169
d D 5.9 92/12/16 18:36:14 mcilroy 17 16
c Fixed endian behavior
e
s 00078/00128/00096
d D 5.8 92/12/02 15:31:17 bostic 16 15
c new version from Peter McIlroy
e
s 00000/00005/00224
d D 5.7 90/10/09 17:48:52 bostic 15 14
c new copyright notice
e
s 00001/00011/00228
d D 5.6 90/06/01 15:41:30 bostic 14 13
c new copyright notice
e
s 00002/00000/00237
d D 5.5 90/05/17 18:59:19 bostic 13 12
c there's an assembly language version for the HP's
e
s 00022/00031/00215
d D 5.4 88/09/22 16:23:31 bostic 12 11
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00010/00005/00236
d D 5.3 88/06/30 17:45:35 bostic 11 10
c install approved copyright notice
e
s 00016/00013/00225
d D 5.2 88/04/29 12:42:04 bostic 10 9
c add Berkeley specific header
e
s 00000/00000/00238
d D 5.1 87/11/30 18:34:10 bostic 9 8
c tahoe release
e
s 00024/00024/00214
d D 1.7 87/07/13 19:20:48 zliu 8 7
c clean-ups.
e
s 00007/00000/00231
d D 1.6 87/07/10 22:17:38 zliu 7 5
c TAHOE's code generator doesn't give us correct code for such
c constructs as (double)sx*sy.  work-around: force temporary store.
e
s 00007/00000/00231
d R 1.6 87/07/10 22:05:33 zliu 6 5
c (double)sx*sy bug on TAHOE work-around: force temporary storage.
e
s 00009/00005/00222
d D 1.5 87/07/10 10:36:35 zliu 5 4
c adding _0x macro for TAHOE.
e
s 00006/00006/00221
d D 1.4 87/07/07 01:32:08 zliu 4 3
c first shot at TAHOE.
e
s 00003/00003/00224
d D 1.3 86/03/16 19:08:50 elefunt 3 2
c All instances of "double static" got converted to "static double",
c as it should be.
e
s 00002/00001/00225
d D 1.2 85/09/11 23:54:39 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00226/00000/00000
d D 1.1 85/09/06 17:53:04 zliu 1 0
c date and time created 85/09/06 17:53:04 by zliu
e
u
U
t
T
I 1
D 10
/* 
E 10
I 10
/*
E 10
D 20
 * Copyright (c) 1985 Regents of the University of California.
D 10
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 10
I 10
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 14
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 11
D 15
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
E 15
E 10
 */

#ifndef lint
D 2
static char sccsid[] = "%W% (ELEFUNT) %G%";
E 2
I 2
D 10
static char sccsid[] =
"%Z%%M%	4.5 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G%";
E 2
D 8
#endif not lint
E 8
I 8
#endif	/* not lint */
E 10
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 10
E 8

/* POW(X,Y)  
 * RETURN X**Y 
 * DOUBLE PRECISION (VAX D format 56 bits, IEEE DOUBLE 53 BITS)
 * CODED IN C BY K.C. NG, 1/8/85; 
 * REVISED BY K.C. NG on 7/10/85.
D 16
 *
E 16
I 16
 * KERNEL pow_P() REPLACED BY P. McILROY 7/22/92.
E 16
 * Required system supported functions:
 *      scalb(x,n)      
 *      logb(x)         
 *	copysign(x,y)	
 *	finite(x)	
 *	drem(x,y)
 *
 * Required kernel functions:
D 16
 *	exp__E(a,c)	...return  exp(a+c) - 1 - a*a/2
 *	log__L(x)	...return  (log(1+x) - 2s)/s, s=x/(2+x) 
 *	pow_p(x,y)	...return  +(anything)**(finite non zero)
E 16
I 16
 *	exp__D(a,c)			exp(a + c) for |a| << |c|
 *	struct d_double dlog(x)		r.a + r.b, |r.b| < |r.a|
E 16
 *
 * Method
 *	1. Compute and return log(x) in three pieces:
 *		log(x) = n*ln2 + hi + lo,
 *	   where n is an integer.
 *	2. Perform y*log(x) by simulating muti-precision arithmetic and 
 *	   return the answer in three pieces:
 *		y*log(x) = m*ln2 + hi + lo,
 *	   where m is an integer.
 *	3. Return x**y = exp(y*log(x))
 *		= 2^m * ( exp(hi+lo) ).
 *
 * Special cases:
 *	(anything) ** 0  is 1 ;
 *	(anything) ** 1  is itself;
 *	(anything) ** NaN is NaN;
 *	NaN ** (anything except 0) is NaN;
D 16
 *	+-(anything > 1) ** +INF is +INF;
E 16
I 16
 *	+(anything > 1) ** +INF is +INF;
 *	-(anything > 1) ** +INF is NaN;
E 16
 *	+-(anything > 1) ** -INF is +0;
 *	+-(anything < 1) ** +INF is +0;
D 16
 *	+-(anything < 1) ** -INF is +INF;
E 16
I 16
 *	+(anything < 1) ** -INF is +INF;
 *	-(anything < 1) ** -INF is NaN;
E 16
 *	+-1 ** +-INF is NaN and signal INVALID;
 *	+0 ** +(anything except 0, NaN)  is +0;
 *	-0 ** +(anything except 0, NaN, odd integer)  is +0;
 *	+0 ** -(anything except 0, NaN)  is +INF and signal DIV-BY-ZERO;
 *	-0 ** -(anything except 0, NaN, odd integer)  is +INF with signal;
 *	-0 ** (odd integer) = -( +0 ** (odd integer) );
 *	+INF ** +(anything except 0,NaN) is +INF;
 *	+INF ** -(anything except 0,NaN) is +0;
 *	-INF ** (odd integer) = -( +INF ** (odd integer) );
 *	-INF ** (even integer) = ( +INF ** (even integer) );
 *	-INF ** -(anything except integer,NaN) is NaN with signal;
 *	-(x=anything) ** (k=integer) is (-1)**k * (x ** k);
 *	-(anything except 0) ** (non-integer) is NaN with signal;
 *
 * Accuracy:
 *	pow(x,y) returns x**y nearly rounded. In particular, on a SUN, a VAX,
 *	and a Zilog Z8000,
 *			pow(integer,integer)
 *	always returns the correct integer provided it is representable.
 *	In a test run with 100,000 random arguments with 0 < x, y < 20.0
 *	on a VAX, the maximum observed error was 1.79 ulps (units in the 
 *	last place).
 *
 * Constants :
 * The hexadecimal values are the intended ones for the following constants.
 * The decimal values may be used, provided that the compiler will convert
 * from decimal to binary accurately enough to produce the hexadecimal values
 * shown.
 */

D 4
#ifdef VAX	/* VAX D format */
E 4
I 4
D 8
#if (defined(VAX)||defined(TAHOE))	/* VAX D format */
E 8
I 8
D 12
#if defined(vax)||defined(tahoe)	/* VAX D format */
E 12
E 8
E 4
#include <errno.h>
I 16
#include <math.h>

E 16
D 12
extern double infnan();
D 5

E 5
I 5
D 8
#ifdef VAX
E 8
I 8
#ifdef vax
E 8
#define _0x(A,B)	0x/**/A/**/B
D 8
#else	/* VAX */
E 8
I 8
#else	/* vax */
E 8
#define _0x(A,B)	0x/**/B/**/A
D 8
#endif	/* VAX */
E 8
I 8
#endif	/* vax */
E 8
E 5
D 3
/* double static */
E 3
I 3
/* static double */
E 3
/* ln2hi  =  6.9314718055829871446E-1    , Hex  2^  0   *  .B17217F7D00000 */
/* ln2lo  =  1.6465949582897081279E-12   , Hex  2^-39   *  .E7BCD5E4F1D9CC */
/* invln2 =  1.4426950408889634148E0     , Hex  2^  1   *  .B8AA3B295C17F1 */
/* sqrt2  =  1.4142135623730950622E0     ; Hex  2^  1   *  .B504F333F9DE65 */
D 5
static long     ln2hix[] = { 0x72174031, 0x0000f7d0};
static long     ln2lox[] = { 0xbcd52ce7, 0xd9cce4f1};
static long    invln2x[] = { 0xaa3b40b8, 0x17f1295c};
static long     sqrt2x[] = { 0x04f340b5, 0xde6533f9};
E 5
I 5
static long     ln2hix[] = { _0x(7217,4031), _0x(0000,f7d0)};
static long     ln2lox[] = { _0x(bcd5,2ce7), _0x(d9cc,e4f1)};
static long    invln2x[] = { _0x(aa3b,40b8), _0x(17f1,295c)};
static long     sqrt2x[] = { _0x(04f3,40b5), _0x(de65,33f9)};
E 5
#define    ln2hi    (*(double*)ln2hix)
#define    ln2lo    (*(double*)ln2lox)
#define   invln2    (*(double*)invln2x)
#define    sqrt2    (*(double*)sqrt2x)
D 8
#else	/* IEEE double */
E 8
I 8
#else	/* defined(vax)||defined(tahoe)	*/
E 8
D 3
double static
E 3
I 3
static double
E 3
ln2hi  =  6.9314718036912381649E-1    , /*Hex  2^ -1   *  1.62E42FEE00000 */
ln2lo  =  1.9082149292705877000E-10   , /*Hex  2^-33   *  1.A39EF35793C76 */
invln2 =  1.4426950408889633870E0     , /*Hex  2^  0   *  1.71547652B82FE */
sqrt2  =  1.4142135623730951455E0     ; /*Hex  2^  0   *  1.6A09E667F3BCD */
D 8
#endif
E 8
I 8
#endif	/* defined(vax)||defined(tahoe)	*/
E 12
I 12
#include "mathimpl.h"
E 12
E 8

D 3
double static zero=0.0, half=1.0/2.0, one=1.0, two=2.0, negone= -1.0;
E 3
I 3
D 12
static double zero=0.0, half=1.0/2.0, one=1.0, two=2.0, negone= -1.0;
E 12
I 12
D 16
vc(ln2hi,  6.9314718055829871446E-1  ,7217,4031,0000,f7d0,   0, .B17217F7D00000)
vc(ln2lo,  1.6465949582897081279E-12 ,bcd5,2ce7,d9cc,e4f1, -39, .E7BCD5E4F1D9CC)
vc(invln2, 1.4426950408889634148E0   ,aa3b,40b8,17f1,295c,   1, .B8AA3B295C17F1)
vc(sqrt2,  1.4142135623730950622E0   ,04f3,40b5,de65,33f9,   1, .B504F333F9DE65)
E 16
I 16
#if (defined(vax) || defined(tahoe))
D 17
		x = (double) (float) x
#	define _IEEE	0
E 17
I 17
#define TRUNC(x)	x = (double) (float) x
#define _IEEE		0
E 17
#else
D 17
#	define _IEEE	1
#	define TRUNC(x)  *(((int *) &x)+1)  &= 0xf8000000
#	define infnan(x) ((x == EDOM)? zero/zero : ((x < 0) ? -one/zero : one/zero))
E 17
I 17
#define _IEEE		1
#define endian		(((*(int *) &one)) ? 1 : 0)
#define TRUNC(x) 	*(((int *) &x)+endian) &= 0xf8000000
#define infnan(x)	0.0
E 17
#endif		/* vax or tahoe */
E 16
E 12
E 3

I 12
D 16
ic(ln2hi,  6.9314718036912381649E-1,   -1, 1.62E42FEE00000)
ic(ln2lo,  1.9082149292705877000E-10, -33, 1.A39EF35793C76)
ic(invln2, 1.4426950408889633870E0,     0, 1.71547652B82FE)
ic(sqrt2,  1.4142135623730951455E0,     0, 1.6A09E667F3BCD)
E 16
I 16
const static double zero=0.0, one=1.0, two=2.0, negone= -1.0;
E 16

D 16
#ifdef vccast
#define	ln2hi	vccast(ln2hi)
#define	ln2lo	vccast(ln2lo)
#define	invln2	vccast(invln2)
#define	sqrt2	vccast(sqrt2)
#endif
E 16
I 16
static double pow_P __P((double, double));
E 16

D 16
const static double zero=0.0, half=1.0/2.0, one=1.0, two=2.0, negone= -1.0;

static double pow_p();

E 16
E 12
double pow(x,y)  	
double x,y;
{
D 12
	double drem(),pow_p(),copysign(),t;
	int finite();
E 12
I 12
	double t;
I 16
	if (y==zero)
		return (one);
	else if (y==one || (_IEEE && x != x))
		return (x);		/* if x is NaN or y=1 */
	else if (_IEEE && y!=y)		/* if y is NaN */
		return (y);
	else if (!finite(y))		/* if y is INF */
		if ((t=fabs(x))==one)	/* +-1 ** +-INF is NaN */
			return (y - y);
		else if (t>one)
			return ((y<0)? zero : ((x<zero)? y-y : y));
		else
			return ((y>0)? zero : ((x<0)? y-y : -y));
	else if (y==two)
		return (x*x);
	else if (y==negone)
		return (one/x);
    /* x > 0, x == +0 */
	else if (copysign(one, x) == one)
		return (pow_P(x, y));
E 16
E 12

D 16
	if     (y==zero)      return(one);
	else if(y==one
D 4
#ifndef VAX
E 4
I 4
D 8
#if (!defined(VAX)&&!defined(TAHOE))
E 8
I 8
#if !defined(vax)&&!defined(tahoe)
E 8
E 4
		||x!=x
D 8
#endif
E 8
I 8
#endif	/* !defined(vax)&&!defined(tahoe) */
E 8
		) return( x );      /* if x is NaN or y=1 */
D 4
#ifndef VAX
E 4
I 4
D 8
#if (!defined(VAX)&&!defined(TAHOE))
E 8
I 8
#if !defined(vax)&&!defined(tahoe)
E 8
E 4
	else if(y!=y)         return( y );      /* if y is NaN */
D 8
#endif
E 8
I 8
#endif	/* !defined(vax)&&!defined(tahoe) */
E 8
	else if(!finite(y))                     /* if y is INF */
	     if((t=copysign(x,one))==one) return(zero/zero);
	     else if(t>one) return((y>zero)?y:zero);
	     else return((y<zero)?-y:zero);
	else if(y==two)       return(x*x);
	else if(y==negone)    return(one/x);

    /* sign(x) = 1 */
	else if(copysign(one,x)==one) return(pow_p(x,y));

E 16
    /* sign(x)= -1 */
	/* if y is an even integer */
D 16
	else if ( (t=drem(y,two)) == zero)	return( pow_p(-x,y) );
E 16
I 16
	else if ( (t=drem(y,two)) == zero)
		return (pow_P(-x, y));
E 16

	/* if y is an odd integer */
D 16
	else if (copysign(t,one) == one) return( -pow_p(-x,y) );
E 16
I 16
	else if (copysign(t,one) == one)
		return (-pow_P(-x, y));
E 16

	/* Henceforth y is not an integer */
D 16
	else if(x==zero)	/* x is -0 */
	    return((y>zero)?-x:one/(-x));
	else {			/* return NaN */
D 4
#ifdef VAX
E 4
I 4
D 8
#if (defined(VAX)||defined(TAHOE))
E 8
I 8
#if defined(vax)||defined(tahoe)
E 8
E 4
	    return (infnan(EDOM));	/* NaN */
D 8
#else	/* IEEE double */
E 8
I 8
#else	/* defined(vax)||defined(tahoe) */
E 8
	    return(zero/zero);
D 8
#endif
E 8
I 8
#endif	/* defined(vax)||defined(tahoe) */
E 8
	}
E 16
I 16
	else if (x==zero)	/* x is -0 */
		return ((y>zero)? -x : one/(-x));
	else if (_IEEE)
		return (zero/zero);
	else
		return (infnan(EDOM));
E 16
}
D 16

I 13
#ifndef mc68881
E 13
/* pow_p(x,y) return x**y for x with sign=1 and finite y */
static double pow_p(x,y)       
double x,y;
E 16
I 16
/* kernel function for x >= 0 */
static double
#ifdef _ANSI_SOURCE
pow_P(double x, double y)
#else
pow_P(x, y) double x, y;
#endif
E 16
{
D 12
        double logb(),scalb(),copysign(),log__L(),exp__E();
E 12
D 16
        double c,s,t,z,tx,ty;
I 7
D 8
#ifdef TAHOE
E 8
I 8
#ifdef tahoe
E 8
	double tahoe_tmp;
D 8
#endif
E 8
I 8
#endif	/* tahoe */
E 8
E 7
        float sx,sy;
	long k=0;
        int n,m;
E 16
I 16
D 18
	struct Double s, t, log__D();
	double  exp__D(), huge = 1e300, tiny = 1e-300;
E 18
I 18
	struct Double s, t, __log__D();
	double  __exp__D(), huge = 1e300, tiny = 1e-300;
E 18
E 16

D 16
	if(x==zero||!finite(x)) {           /* if x is +INF or +0 */
D 4
#ifdef VAX
E 4
I 4
D 8
#if (defined(VAX)||defined(TAHOE))
E 8
I 8
#if defined(vax)||defined(tahoe)
E 8
E 4
	     return((y>zero)?x:infnan(ERANGE));	/* if y<zero, return +INF */
D 8
#else
E 8
I 8
#else	/* defined(vax)||defined(tahoe) */
E 8
	     return((y>zero)?x:one/x);
D 8
#endif
E 8
I 8
#endif	/* defined(vax)||defined(tahoe) */
E 8
	}
	if(x==1.0) return(x);	/* if x=1.0, return 1 since y is finite */
E 16
I 16
D 19
	if (x == 1)
E 19
I 19
	if (x == zero)
		if (y > zero)
			return (zero);
		else if (_IEEE)
			return (huge*huge);
		else
			return (infnan(ERANGE));
	if (x == one)
E 19
		return (one);
I 19
	if (!finite(x))
		if (y < zero)
			return (zero);
		else if (_IEEE)
			return (huge*huge);
		else
			return (infnan(ERANGE));
E 19
	if (y >= 7e18)		/* infinity */
		if (x < 1)
			return(tiny*tiny);
		else if (_IEEE)
			return (huge*huge);
		else
			return (infnan(ERANGE));
E 16

D 16
    /* reduce x to z in [sqrt(1/2)-1, sqrt(2)-1] */
        z=scalb(x,-(n=logb(x)));  
D 4
#ifndef VAX	/* IEEE double */	/* subnormal number */
E 4
I 4
D 8
#if (!defined(VAX)&&!defined(TAHOE))	/* IEEE double; subnormal number */
E 8
I 8
#if !defined(vax)&&!defined(tahoe)	/* IEEE double; subnormal number */
E 8
E 4
        if(n <= -1022) {n += (m=logb(z)); z=scalb(z,-m);} 
D 8
#endif
E 8
I 8
#endif	/* !defined(vax)&&!defined(tahoe) */
E 8
        if(z >= sqrt2 ) {n += 1; z *= half;}  z -= one ;
E 16
I 16
	/* Return exp(y*log(x)), using simulated extended */
	/* precision for the log and the multiply.	  */
E 16

D 16
    /* log(x) = nlog2+log(1+z) ~ nlog2 + t + tx */
	s=z/(two+z); c=z*z*half; tx=s*(c+log__L(s*s)); 
	t= z-(c-tx); tx += (z-t)-c;

   /* if y*log(x) is neither too big nor too small */
	if((s=logb(y)+logb(n+t)) < 12.0) 
	    if(s>-60.0) {

	/* compute y*log(x) ~ mlog2 + t + c */
        	s=y*(n+invln2*t);
                m=s+copysign(half,s);   /* m := nint(y*log(x)) */ 
		k=y; 
		if((double)k==y) {	/* if y is an integer */
		    k = m-k*n;
		    sx=t; tx+=(t-sx); }
		else	{		/* if y is not an integer */    
		    k =m;
	 	    tx+=n*ln2lo;
		    sx=(c=n*ln2hi)+t; tx+=(c-sx)+t; }
	   /* end of checking whether k==y */

                sy=y; ty=y-sy;          /* y ~ sy + ty */
I 7
D 8
#ifdef TAHOE
E 8
I 8
#ifdef tahoe
E 8
		s = (tahoe_tmp = sx)*sy-k*ln2hi;
D 8
#else
E 8
I 8
#else	/* tahoe */
E 8
E 7
		s=(double)sx*sy-k*ln2hi;        /* (sy+ty)*(sx+tx)-kln2 */
I 7
D 8
#endif
E 8
I 8
#endif	/* tahoe */
E 8
E 7
		z=(tx*ty-k*ln2lo);
		tx=tx*sy; ty=sx*ty;
		t=ty+z; t+=tx; t+=s;
		c= -((((t-s)-tx)-ty)-z);

	    /* return exp(y*log(x)) */
		t += exp__E(t,c); return(scalb(one+t,m));
	     }
	/* end of if log(y*log(x)) > -60.0 */
	    
	    else
		/* exp(+- tiny) = 1 with inexact flag */
			{ln2hi+ln2lo; return(one);}
	    else if(copysign(one,y)*(n+invln2*t) <zero)
		/* exp(-(big#)) underflows to zero */
	        	return(scalb(one,-5000)); 
	    else
	        /* exp(+(big#)) overflows to INF */
	    		return(scalb(one, 5000)); 

E 16
I 16
D 18
	s = log__D(x);
E 18
I 18
	s = __log__D(x);
E 18
	t.a = y;
	TRUNC(t.a);
	t.b = y - t.a;
	t.b = s.b*y + t.b*s.a;
	t.a *= s.a;
	s.a = t.a + t.b;
	s.b = (t.a - s.a) + t.b;
D 18
	return (exp__D(s.a, s.b));
E 18
I 18
	return (__exp__D(s.a, s.b));
E 18
E 16
}
I 13
D 16
#endif /* mc68881 */
E 16
E 13
E 1
