h21011
s 00002/00002/00093
d D 8.1 93/06/04 17:04:40 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00095
d D 5.6 90/10/09 17:48:58 bostic 12 11
c new copyright notice
e
s 00001/00011/00099
d D 5.5 90/06/01 15:41:38 bostic 11 10
c new copyright notice
e
s 00018/00024/00092
d D 5.4 88/09/22 16:23:34 bostic 10 9
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00010/00005/00106
d D 5.3 88/06/30 17:45:37 bostic 9 8
c install approved copyright notice
e
s 00016/00013/00095
d D 5.2 88/04/29 12:42:06 bostic 8 7
c add Berkeley specific header
e
s 00000/00000/00108
d D 5.1 87/11/30 18:34:11 bostic 7 6
c tahoe release
e
s 00012/00012/00096
d D 1.6 87/07/13 19:20:50 zliu 6 5
c clean-ups.
e
s 00008/00003/00100
d D 1.5 87/07/10 10:36:37 zliu 5 4
c adding _0x macro for TAHOE.
e
s 00003/00003/00100
d D 1.4 87/07/07 01:32:10 zliu 4 3
c first shot at TAHOE.
e
s 00002/00002/00101
d D 1.3 86/03/16 19:08:54 elefunt 3 2
c All instances of "double static" got converted to "static double",
c as it should be.
e
s 00002/00001/00101
d D 1.2 85/09/11 23:54:45 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00102/00000/00000
d D 1.1 85/09/06 17:53:06 zliu 1 0
c date and time created 85/09/06 17:53:06 by zliu
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
D 13
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
E 13
I 13
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
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
"%Z%%M%	4.3 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G%";
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

/* SINH(X)
 * RETURN THE HYPERBOLIC SINE OF X
 * DOUBLE PRECISION (VAX D format 56 bits, IEEE DOUBLE 53 BITS)
 * CODED IN C BY K.C. NG, 1/8/85; 
 * REVISED BY K.C. NG on 2/8/85, 3/7/85, 3/24/85, 4/16/85.
 *
 * Required system supported functions :
 *	copysign(x,y)
 *	scalb(x,N)
 *
 * Required kernel functions:
 *	expm1(x)	...return exp(x)-1
 *
 * Method :
 *	1. reduce x to non-negative by sinh(-x) = - sinh(x).
 *	2. 
 *
 *	                                      expm1(x) + expm1(x)/(expm1(x)+1)
 *	    0 <= x <= lnovfl     : sinh(x) := --------------------------------
 *			       		                      2
 *     lnovfl <= x <= lnovfl+ln2 : sinh(x) := expm1(x)/2 (avoid overflow)
 * lnovfl+ln2 <  x <  INF        :  overflow to INF
 *	
 *
 * Special cases:
 *	sinh(x) is x if x is +INF, -INF, or NaN.
 *	only sinh(0)=0 is exact for finite argument.
 *
 * Accuracy:
 *	sinh(x) returns the exact hyperbolic sine of x nearly rounded. In
 *	a test run with 1,024,000 random arguments on a VAX, the maximum
 *	observed error was 1.93 ulps (units in the last place).
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following constants.
 * The decimal values may be used, provided that the compiler will convert
 * from decimal to binary accurately enough to produce the hexadecimal values
 * shown.
 */
D 4
#ifdef VAX
E 4
I 4
D 6
#if (defined(VAX)||defined(TAHOE))
I 5
#ifdef VAX
E 6
I 6
D 10
#if defined(vax)||defined(tahoe)
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
/* mln2hi =  8.8029691931113054792E1     , Hex  2^  7   *  .B00F33C7E22BDB */
/* mln2lo = -4.9650192275318476525E-16   , Hex  2^-50   * -.8F1B60279E582A */
/* lnovfl =  8.8029691931113053016E1     ; Hex  2^  7   *  .B00F33C7E22BDA */
D 5
static long    mln2hix[] = { 0x0f3343b0, 0x2bdbc7e2};
static long    mln2lox[] = { 0x1b60a70f, 0x582a279e};
static long    lnovflx[] = { 0x0f3343b0, 0x2bdac7e2};
E 5
I 5
static long    mln2hix[] = { _0x(0f33,43b0), _0x(2bdb,c7e2)};
static long    mln2lox[] = { _0x(1b60,a70f), _0x(582a,279e)};
static long    lnovflx[] = { _0x(0f33,43b0), _0x(2bda,c7e2)};
E 5
#define   mln2hi    (*(double*)mln2hix)
#define   mln2lo    (*(double*)mln2lox)
#define   lnovfl    (*(double*)lnovflx)
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe) */
E 6
D 3
double static 
E 3
I 3
static double 
E 3
mln2hi =  7.0978271289338397310E2     , /*Hex  2^ 10   *  1.62E42FEFA39EF */
mln2lo =  2.3747039373786107478E-14   , /*Hex  2^-45   *  1.ABC9E3B39803F */
lnovfl =  7.0978271289338397310E2     ; /*Hex  2^  9   *  1.62E42FEFA39EF */
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe) */
E 10
E 6

I 10
#include "mathimpl.h"

vc(mln2hi, 8.8029691931113054792E1   ,0f33,43b0,2bdb,c7e2,   7, .B00F33C7E22BDB)
vc(mln2lo,-4.9650192275318476525E-16 ,1b60,a70f,582a,279e, -50,-.8F1B60279E582A)
vc(lnovfl, 8.8029691931113053016E1   ,0f33,43b0,2bda,c7e2,   7, .B00F33C7E22BDA)

ic(mln2hi, 7.0978271289338397310E2,    10, 1.62E42FEFA39EF)
ic(mln2lo, 2.3747039373786107478E-14, -45, 1.ABC9E3B39803F)
ic(lnovfl, 7.0978271289338397310E2,     9, 1.62E42FEFA39EF)

#ifdef vccast
#define	mln2hi	vccast(mln2hi)
#define	mln2lo	vccast(mln2lo)
#define	lnovfl	vccast(lnovfl)
#endif

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
static max = 126                      ;
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe) */
E 6
static max = 1023                     ;
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe) */
E 6


double sinh(x)
double x;
{
D 10
	static double  one=1.0, half=1.0/2.0 ;
	double expm1(), t, scalb(), copysign(), sign;
E 10
I 10
	static const double  one=1.0, half=1.0/2.0 ;
	double t, sign;
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
	sign=copysign(one,x);
	x=copysign(x,one);
	if(x<lnovfl)
	    {t=expm1(x); return(copysign((t+t/(one+t))*half,sign));}

	else if(x <= lnovfl+0.7)
		/* subtract x by ln(2^(max+1)) and return 2^max*exp(x) 
	    		to avoid unnecessary overflow */
	    return(copysign(scalb(one+expm1((x-mln2hi)-mln2lo),max),sign));

	else  /* sinh(+-INF) = +-INF, sinh(+-big no.) overflow to +-INF */
	    return( expm1(x)*sign );
}
E 1
