h03536
s 00002/00002/00142
d D 8.1 93/06/04 17:03:54 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00143
d D 5.7 93/01/10 12:47:56 bostic 13 12
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00000/00005/00144
d D 5.6 90/10/09 17:48:39 bostic 12 11
c new copyright notice
e
s 00001/00011/00148
d D 5.5 90/06/01 15:41:10 bostic 11 10
c new copyright notice
e
s 00018/00026/00141
d D 5.4 88/09/22 16:23:27 bostic 10 9
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00010/00005/00157
d D 5.3 88/06/30 17:45:29 bostic 9 8
c install approved copyright notice
e
s 00016/00013/00146
d D 5.2 88/04/29 12:41:59 bostic 8 7
c add Berkeley specific header
e
s 00000/00000/00159
d D 5.1 87/11/30 18:34:06 bostic 7 6
c tahoe release
e
s 00012/00012/00147
d D 1.6 87/07/13 19:20:45 zliu 6 5
c clean-ups.
e
s 00008/00004/00151
d D 1.5 87/07/10 10:36:33 zliu 5 4
c adding _0x macro for TAHOE.
e
s 00003/00003/00152
d D 1.4 87/07/07 01:32:03 zliu 4 3
c first shot at TAHOE.
e
s 00002/00002/00153
d D 1.3 86/03/16 19:08:47 elefunt 3 2
c All instances of "double static" got converted to "static double",
c as it should be.
e
s 00002/00001/00153
d D 1.2 85/09/11 23:54:30 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00154/00000/00000
d D 1.1 85/09/06 17:53:01 zliu 1 0
c date and time created 85/09/06 17:53:01 by zliu
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
"%Z%%M%	1.3 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G%";
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

/* LOG1P(x) 
 * RETURN THE LOGARITHM OF 1+x
 * DOUBLE PRECISION (VAX D FORMAT 56 bits, IEEE DOUBLE 53 BITS)
 * CODED IN C BY K.C. NG, 1/19/85; 
 * REVISED BY K.C. NG on 2/6/85, 3/7/85, 3/24/85, 4/16/85.
 * 
 * Required system supported functions:
 *	scalb(x,n) 
 *	copysign(x,y)
 *	logb(x)	
 *	finite(x)
 *
 * Required kernel function:
 *	log__L(z)
 *
 * Method :
 *	1. Argument Reduction: find k and f such that 
 *			1+x  = 2^k * (1+f), 
 *	   where  sqrt(2)/2 < 1+f < sqrt(2) .
 *
 *	2. Let s = f/(2+f) ; based on log(1+f) = log(1+s) - log(1-s)
 *		 = 2s + 2/3 s**3 + 2/5 s**5 + .....,
 *	   log(1+f) is computed by
 *
 *	     		log(1+f) = 2s + s*log__L(s*s)
 *	   where
 *		log__L(z) = z*(L1 + z*(L2 + z*(... (L6 + z*L7)...)))
 *
 *	   See log__L() for the values of the coefficients.
 *
 *	3. Finally,  log(1+x) = k*ln2 + log(1+f).  
 *
 *	Remarks 1. In step 3 n*ln2 will be stored in two floating point numbers
 *		   n*ln2hi + n*ln2lo, where ln2hi is chosen such that the last 
 *		   20 bits (for VAX D format), or the last 21 bits ( for IEEE 
 *		   double) is 0. This ensures n*ln2hi is exactly representable.
 *		2. In step 1, f may not be representable. A correction term c
 *	 	   for f is computed. It follows that the correction term for
 *		   f - t (the leading term of log(1+f) in step 2) is c-c*x. We
 *		   add this correction term to n*ln2lo to attenuate the error.
 *
 *
 * Special cases:
 *	log1p(x) is NaN with signal if x < -1; log1p(NaN) is NaN with no signal;
 *	log1p(INF) is +INF; log1p(-1) is -INF with signal;
 *	only log1p(0)=0 is exact for finite argument.
 *
 * Accuracy:
 *	log1p(x) returns the exact log(1+x) nearly rounded. In a test run 
 *	with 1,536,000 random arguments on a VAX, the maximum observed
 *	error was .846 ulps (units in the last place).
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
E 6
I 6
D 10
#if defined(vax)||defined(tahoe)	/* VAX D format */
E 10
E 6
E 4
#include <errno.h>
D 5

E 5
I 5
D 6
#ifdef VAX
E 6
I 6
D 10
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
D 3
/* double static */
E 3
I 3
/* static double */
E 3
/* ln2hi  =  6.9314718055829871446E-1    , Hex  2^  0   *  .B17217F7D00000 */
/* ln2lo  =  1.6465949582897081279E-12   , Hex  2^-39   *  .E7BCD5E4F1D9CC */
/* sqrt2  =  1.4142135623730950622E0     ; Hex  2^  1   *  .B504F333F9DE65 */
D 5
static long     ln2hix[] = { 0x72174031, 0x0000f7d0};
static long     ln2lox[] = { 0xbcd52ce7, 0xd9cce4f1};
static long     sqrt2x[] = { 0x04f340b5, 0xde6533f9};
E 5
I 5
static long     ln2hix[] = { _0x(7217,4031), _0x(0000,f7d0)};
static long     ln2lox[] = { _0x(bcd5,2ce7), _0x(d9cc,e4f1)};
static long     sqrt2x[] = { _0x(04f3,40b5), _0x(de65,33f9)};
E 5
#define    ln2hi    (*(double*)ln2hix)
#define    ln2lo    (*(double*)ln2lox)
#define    sqrt2    (*(double*)sqrt2x)
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
sqrt2  =  1.4142135623730951455E0     ; /*Hex  2^  0   *  1.6A09E667F3BCD */
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
vc(ln2hi, 6.9314718055829871446E-1  ,7217,4031,0000,f7d0,   0, .B17217F7D00000)
vc(ln2lo, 1.6465949582897081279E-12 ,bcd5,2ce7,d9cc,e4f1, -39, .E7BCD5E4F1D9CC)
vc(sqrt2, 1.4142135623730950622E0   ,04f3,40b5,de65,33f9,   1, .B504F333F9DE65)

ic(ln2hi, 6.9314718036912381649E-1,   -1, 1.62E42FEE00000)
ic(ln2lo, 1.9082149292705877000E-10, -33, 1.A39EF35793C76)
ic(sqrt2, 1.4142135623730951455E0,     0, 1.6A09E667F3BCD)

#ifdef vccast
#define	ln2hi	vccast(ln2hi)
#define	ln2lo	vccast(ln2lo)
#define	sqrt2	vccast(sqrt2)
#endif

E 10
double log1p(x)
double x;
{
D 10
	static double zero=0.0, negone= -1.0, one=1.0, 
E 10
I 10
	const static double zero=0.0, negone= -1.0, one=1.0, 
E 10
		      half=1.0/2.0, small=1.0E-20;   /* 1+small == 1 */
D 10
	double logb(),copysign(),scalb(),log__L(),z,s,t,c;
	int k,finite();
E 10
I 10
	double z,s,t,c;
	int k;
E 10

D 4
#ifndef VAX
E 4
I 4
D 6
#if (!defined(VAX)&&!defined(TAHOE))
E 6
I 6
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

	if(finite(x)) {
	   if( x > negone ) {

	   /* argument reduction */
	      if(copysign(x,one)<small) return(x);
	      k=logb(one+x); z=scalb(x,-k); t=scalb(one,-k);
	      if(z+t >= sqrt2 ) 
		  { k += 1 ; z *= half; t *= half; }
	      t += negone; x = z + t;
	      c = (t-x)+z ;		/* correction term for x */

 	   /* compute log(1+x)  */
              s = x/(2+x); t = x*x*half;
	      c += (k*ln2lo-c*x);
D 13
	      z = c+s*(t+log__L(s*s));
E 13
I 13
	      z = c+s*(t+__log__L(s*s));
E 13
	      x += (z - t) ;

	      return(k*ln2hi+x);
	   }
	/* end of if (x > negone) */

	    else {
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
D 10
		extern double infnan();
E 10
		if ( x == negone )
		    return (infnan(-ERANGE));	/* -INF */
		else
		    return (infnan(EDOM));	/* NaN */
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe) */
E 6
		/* x = -1, return -INF with signal */
		if ( x == negone ) return( negone/zero );

		/* negative argument for log, return NaN with signal */
	        else return ( zero / zero );
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe) */
E 6
	    }
	}
    /* end of if (finite(x)) */

    /* log(-INF) is NaN */
	else if(x<0) 
	     return(zero/zero);

    /* log(+INF) is INF */
	else return(x);      
}
E 1
