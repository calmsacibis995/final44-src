h13565
s 00002/00002/00139
d D 8.1 93/06/04 17:01:37 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00135
d D 5.7 93/01/10 12:47:52 bostic 13 12
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00000/00005/00141
d D 5.6 90/10/09 17:48:18 bostic 12 11
c new copyright notice
e
s 00001/00011/00145
d D 5.5 90/06/01 15:40:36 bostic 11 10
c new copyright notice
e
s 00022/00029/00134
d D 5.4 88/09/22 16:23:14 bostic 10 9
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00010/00005/00153
d D 5.3 88/06/30 17:45:17 bostic 9 8
c install approved copyright notice
e
s 00016/00013/00142
d D 5.2 88/04/29 12:28:49 bostic 8 7
c add Berkeley specific copyright                            
e
s 00000/00000/00155
d D 5.1 87/11/30 18:33:58 bostic 7 6
c tahoe release
e
s 00012/00012/00143
d D 1.6 87/07/13 19:20:33 zliu 6 5
c clean-ups.
e
s 00009/00004/00146
d D 1.5 87/07/10 10:36:27 zliu 5 4
c adding _0x macro for TAHOE.
e
s 00003/00003/00147
d D 1.4 87/07/07 01:31:51 zliu 4 3
c first shot at TAHOE.
e
s 00003/00003/00147
d D 1.3 86/03/16 19:08:41 elefunt 3 2
c All instances of "double static" got converted to "static double",
c as it should be.
e
s 00002/00001/00148
d D 1.2 85/09/11 23:53:57 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00149/00000/00000
d D 1.1 85/09/06 17:52:49 zliu 1 0
c date and time created 85/09/06 17:52:49 by zliu
e
u
U
t
T
I 1
D 8
/* 
E 8
I 8
/*
E 8
D 14
 * Copyright (c) 1985 Regents of the University of California.
D 8
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 8
I 8
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 11
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
D 12
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
E 12
E 8
 */

#ifndef lint
D 2
static char sccsid[] = "%W% (ELEFUNT) %G%";
E 2
I 2
D 8
static char sccsid[] =
"%Z%%M%	1.2 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G%";
E 2
D 6
#endif not lint
E 6
I 6
#endif	/* not lint */
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8
E 6

/* EXPM1(X)
 * RETURN THE EXPONENTIAL OF X MINUS ONE
 * DOUBLE PRECISION (IEEE 53 BITS, VAX D FORMAT 56 BITS)
 * CODED IN C BY K.C. NG, 1/19/85; 
 * REVISED BY K.C. NG on 2/6/85, 3/7/85, 3/21/85, 4/16/85.
 *
 * Required system supported functions:
 *	scalb(x,n)	
 *	copysign(x,y)	
 *	finite(x)
 *
 * Kernel function:
 *	exp__E(x,c)
 *
 * Method:
 *	1. Argument Reduction: given the input x, find r and integer k such 
 *	   that
 *	                   x = k*ln2 + r,  |r| <= 0.5*ln2 .  
 *	   r will be represented as r := z+c for better accuracy.
 *
 *	2. Compute EXPM1(r)=exp(r)-1 by 
 *
 *			EXPM1(r=z+c) := z + exp__E(z,c)
 *
 *	3. EXPM1(x) =  2^k * ( EXPM1(r) + 1-2^-k ).
 *
 * 	Remarks: 
 *	   1. When k=1 and z < -0.25, we use the following formula for
 *	      better accuracy:
 *			EXPM1(x) = 2 * ( (z+0.5) + exp__E(z,c) )
 *	   2. To avoid rounding error in 1-2^-k where k is large, we use
 *			EXPM1(x) = 2^k * { [z+(exp__E(z,c)-2^-k )] + 1 }
 *	      when k>56. 
 *
 * Special cases:
 *	EXPM1(INF) is INF, EXPM1(NaN) is NaN;
 *	EXPM1(-INF)= -1;
 *	for finite argument, only EXPM1(0)=0 is exact.
 *
 * Accuracy:
 *	EXPM1(x) returns the exact (exp(x)-1) nearly rounded. In a test run with
 *	1,166,000 random arguments on a VAX, the maximum observed error was
 *	.872 ulps (units of the last place).
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following constants.
 * The decimal values may be used, provided that the compiler will convert
 * from decimal to binary accurately enough to produce the hexadecimal values
 * shown.
 */

D 4
#ifdef VAX	/* VAX D format */
E 4
I 4
D 6
#if (defined(VAX)||defined(TAHOE))	/* VAX D format */
I 5
#ifdef VAX
E 6
I 6
D 10
#if defined(vax)||defined(tahoe)	/* VAX D format */
#ifdef vax
E 6
#define _0x(A,B)	0x/**/A/**/B
D 6
#else	/* VAX */
E 6
I 6
#else	/* vax */
E 6
#define _0x(A,B)	0x/**/B/**/A
D 6
#endif	/* VAX */
E 6
I 6
#endif	/* vax */
E 6
E 5
E 4
D 3
/* double static */
E 3
I 3
/* static double */
E 3
/* ln2hi  =  6.9314718055829871446E-1    , Hex  2^  0   *  .B17217F7D00000 */
/* ln2lo  =  1.6465949582897081279E-12   , Hex  2^-39   *  .E7BCD5E4F1D9CC */
/* lnhuge =  9.4961163736712506989E1     , Hex  2^  7   *  .BDEC1DA73E9010 */
/* invln2 =  1.4426950408889634148E0     ; Hex  2^  1   *  .B8AA3B295C17F1 */
D 5
static long     ln2hix[] = { 0x72174031, 0x0000f7d0};
static long     ln2lox[] = { 0xbcd52ce7, 0xd9cce4f1};
static long    lnhugex[] = { 0xec1d43bd, 0x9010a73e};
static long    invln2x[] = { 0xaa3b40b8, 0x17f1295c};
E 5
I 5
static long     ln2hix[] = { _0x(7217,4031), _0x(0000,f7d0)};
static long     ln2lox[] = { _0x(bcd5,2ce7), _0x(d9cc,e4f1)};
static long    lnhugex[] = { _0x(ec1d,43bd), _0x(9010,a73e)};
static long    invln2x[] = { _0x(aa3b,40b8), _0x(17f1,295c)};
E 5
#define    ln2hi    (*(double*)ln2hix)
#define    ln2lo    (*(double*)ln2lox)
#define   lnhuge    (*(double*)lnhugex)
#define   invln2    (*(double*)invln2x)
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe)	*/
E 6
D 3
double static
E 3
I 3
static double
E 3
ln2hi  =  6.9314718036912381649E-1    , /*Hex  2^ -1   *  1.62E42FEE00000 */
ln2lo  =  1.9082149292705877000E-10   , /*Hex  2^-33   *  1.A39EF35793C76 */
lnhuge =  7.1602103751842355450E2     , /*Hex  2^  9   *  1.6602B15B7ECF2 */
invln2 =  1.4426950408889633870E0     ; /*Hex  2^  0   *  1.71547652B82FE */
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe)	*/
E 10
I 10
#include "mathimpl.h"
E 10
E 6

I 10
vc(ln2hi,  6.9314718055829871446E-1  ,7217,4031,0000,f7d0,   0, .B17217F7D00000)
vc(ln2lo,  1.6465949582897081279E-12 ,bcd5,2ce7,d9cc,e4f1, -39, .E7BCD5E4F1D9CC)
vc(lnhuge, 9.4961163736712506989E1   ,ec1d,43bd,9010,a73e,   7, .BDEC1DA73E9010)
vc(invln2, 1.4426950408889634148E0   ,aa3b,40b8,17f1,295c,   1, .B8AA3B295C17F1)

ic(ln2hi,  6.9314718036912381649E-1,   -1, 1.62E42FEE00000)
ic(ln2lo,  1.9082149292705877000E-10, -33, 1.A39EF35793C76)
ic(lnhuge, 7.1602103751842355450E2,     9, 1.6602B15B7ECF2)
ic(invln2, 1.4426950408889633870E0,     0, 1.71547652B82FE)

#ifdef vccast
#define	ln2hi	vccast(ln2hi)
#define	ln2lo	vccast(ln2lo)
#define	lnhuge	vccast(lnhuge)
#define	invln2	vccast(invln2)
#endif

E 10
double expm1(x)
double x;
{
D 3
	double static one=1.0, half=1.0/2.0; 
E 3
I 3
D 10
	static double one=1.0, half=1.0/2.0; 
E 3
	double scalb(), copysign(), exp__E(), z,hi,lo,c;
	int k,finite();
E 10
I 10
	const static double one=1.0, half=1.0/2.0; 
	double  z,hi,lo,c;
	int k;
E 10
D 4
#ifdef VAX
E 4
I 4
D 6
#if (defined(VAX)||defined(TAHOE))
E 6
I 6
#if defined(vax)||defined(tahoe)
E 6
E 4
	static prec=56;
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe) */
E 6
	static prec=53;
D 6
#endif
D 4
#ifndef VAX
E 4
I 4
#if (!defined(VAX)&&!defined(TAHOE))
E 6
I 6
#endif	/* defined(vax)||defined(tahoe) */
I 10

E 10
#if !defined(vax)&&!defined(tahoe)
E 6
E 4
	if(x!=x) return(x);	/* x is NaN */
D 6
#endif
E 6
I 6
#endif	/* !defined(vax)&&!defined(tahoe) */
E 6

	if( x <= lnhuge ) {
		if( x >= -40.0 ) {

		    /* argument reduction : x - k*ln2 */
			k= invln2 *x+copysign(0.5,x);	/* k=NINT(x/ln2) */
			hi=x-k*ln2hi ; 
			z=hi-(lo=k*ln2lo);
			c=(hi-z)-lo;

D 13
			if(k==0) return(z+exp__E(z,c));
E 13
I 13
			if(k==0) return(z+__exp__E(z,c));
E 13
			if(k==1)
			    if(z< -0.25) 
D 13
				{x=z+half;x +=exp__E(z,c); return(x+x);}
E 13
I 13
				{x=z+half;x +=__exp__E(z,c); return(x+x);}
E 13
			    else
D 13
				{z+=exp__E(z,c); x=half+z; return(x+x);}
E 13
I 13
				{z+=__exp__E(z,c); x=half+z; return(x+x);}
E 13
		    /* end of k=1 */

			else {
			    if(k<=prec)
D 13
			      { x=one-scalb(one,-k); z += exp__E(z,c);}
E 13
I 13
			      { x=one-scalb(one,-k); z += __exp__E(z,c);}
E 13
			    else if(k<100)
D 13
			      { x = exp__E(z,c)-scalb(one,-k); x+=z; z=one;}
E 13
I 13
			      { x = __exp__E(z,c)-scalb(one,-k); x+=z; z=one;}
E 13
			    else 
D 13
			      { x = exp__E(z,c)+z; z=one;}
E 13
I 13
			      { x = __exp__E(z,c)+z; z=one;}
E 13

			    return (scalb(x+z,k));  
			}
		}
		/* end of x > lnunfl */

		else 
		     /* expm1(-big#) rounded to -1 (inexact) */
		     if(finite(x))  
			 { ln2hi+ln2lo; return(-one);}

		     /* expm1(-INF) is -1 */
		     else return(-one);
	}
	/* end of x < lnhuge */

	else 
	/*  expm1(INF) is INF, expm1(+big#) overflows to INF */
	    return( finite(x) ?  scalb(one,5000) : x);
}
E 1
