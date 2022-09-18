h09202
s 00002/00002/00108
d D 8.1 93/06/04 17:01:30 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00109
d D 5.7 93/01/10 12:47:51 bostic 13 12
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00000/00005/00110
d D 5.6 90/10/09 17:48:14 bostic 12 11
c new copyright notice
e
s 00001/00011/00114
d D 5.5 90/06/01 15:40:28 bostic 11 10
c new copyright notice
e
s 00022/00031/00103
d D 5.4 88/09/22 16:23:12 bostic 10 9
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00010/00005/00124
d D 5.3 88/06/30 17:45:16 bostic 9 8
c install approved copyright notice
e
s 00016/00013/00113
d D 5.2 88/04/29 12:41:54 bostic 8 7
c add Berkeley specific header
e
s 00000/00000/00126
d D 5.1 87/11/30 18:33:57 bostic 7 6
c tahoe release
e
s 00010/00010/00116
d D 1.6 87/07/13 19:20:31 zliu 6 5
c clean-ups.
e
s 00010/00005/00116
d D 1.5 87/07/10 10:36:25 zliu 5 4
c adding _0x macro for TAHOE.
e
s 00002/00002/00119
d D 1.4 87/07/07 01:31:49 zliu 4 3
c first shot at TAHOE.
e
s 00001/00001/00120
d D 1.3 86/03/16 19:08:38 elefunt 3 2
c All instances of "double static" got converted to "static double",
c as it should be.
e
s 00002/00001/00119
d D 1.2 85/09/11 23:53:52 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00120/00000/00000
d D 1.1 85/09/06 17:52:47 zliu 1 0
c date and time created 85/09/06 17:52:47 by zliu
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

/* exp__E(x,c)
 * ASSUMPTION: c << x  SO THAT  fl(x+c)=x.
 * (c is the correction term for x)
 * exp__E RETURNS
 *
 *			 /  exp(x+c) - 1 - x ,  1E-19 < |x| < .3465736
 *       exp__E(x,c) = 	| 		     
 *			 \  0 ,  |x| < 1E-19.
 *
 * DOUBLE PRECISION (IEEE 53 bits, VAX D FORMAT 56 BITS)
 * KERNEL FUNCTION OF EXP, EXPM1, POW FUNCTIONS
 * CODED IN C BY K.C. NG, 1/31/85;
 * REVISED BY K.C. NG on 3/16/85, 4/16/85.
 *
 * Required system supported function:
 *	copysign(x,y)	
 *
 * Method:
 *	1. Rational approximation. Let r=x+c.
 *	   Based on
 *                                   2 * sinh(r/2)     
 *                exp(r) - 1 =   ----------------------   ,
 *                               cosh(r/2) - sinh(r/2)
 *	   exp__E(r) is computed using
 *                   x*x            (x/2)*W - ( Q - ( 2*P  + x*P ) )
 *                   --- + (c + x*[---------------------------------- + c ])
 *                    2                          1 - W
 * 	   where  P := p1*x^2 + p2*x^4,
 *	          Q := q1*x^2 + q2*x^4 (for 56 bits precision, add q3*x^6)
 *	          W := x/2-(Q-x*P),
 *
 *	   (See the listing below for the values of p1,p2,q1,q2,q3. The poly-
 *	    nomials P and Q may be regarded as the approximations to sinh
 *	    and cosh :
 *		sinh(r/2) =  r/2 + r * P  ,  cosh(r/2) =  1 + Q . )
 *
 *         The coefficients were obtained by a special Remez algorithm.
 *
 * Approximation error:
 *
 *   |	exp(x) - 1			   |        2**(-57),  (IEEE double)
 *   | ------------  -  (exp__E(x,0)+x)/x  |  <= 
 *   |	     x			           |	    2**(-69).  (VAX D)
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
/* static double */
/* p1     =  1.5150724356786683059E-2    , Hex  2^ -6   *  .F83ABE67E1066A */
/* p2     =  6.3112487873718332688E-5    , Hex  2^-13   *  .845B4248CD0173 */
/* q1     =  1.1363478204690669916E-1    , Hex  2^ -3   *  .E8B95A44A2EC45 */
/* q2     =  1.2624568129896839182E-3    , Hex  2^ -9   *  .A5790572E4F5E7 */
/* q3     =  1.5021856115869022674E-6    ; Hex  2^-19   *  .C99EB4604AC395 */
D 5
static long        p1x[] = { 0x3abe3d78, 0x066a67e1};
static long        p2x[] = { 0x5b423984, 0x017348cd};
static long        q1x[] = { 0xb95a3ee8, 0xec4544a2};
static long        q2x[] = { 0x79053ba5, 0xf5e772e4};
static long        q3x[] = { 0x9eb436c9, 0xc395604a};
E 5
I 5
static long        p1x[] = { _0x(3abe,3d78), _0x(066a,67e1)};
static long        p2x[] = { _0x(5b42,3984), _0x(0173,48cd)};
static long        q1x[] = { _0x(b95a,3ee8), _0x(ec45,44a2)};
static long        q2x[] = { _0x(7905,3ba5), _0x(f5e7,72e4)};
static long        q3x[] = { _0x(9eb4,36c9), _0x(c395,604a)};
E 5
#define       p1    (*(double*)p1x)
#define       p2    (*(double*)p2x)
#define       q1    (*(double*)q1x)
#define       q2    (*(double*)q2x)
#define       q3    (*(double*)q3x)
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe)	*/
E 6
static double 
p1     =  1.3887401997267371720E-2    , /*Hex  2^ -7   *  1.C70FF8B3CC2CF */
p2     =  3.3044019718331897649E-5    , /*Hex  2^-15   *  1.15317DF4526C4 */
q1     =  1.1110813732786649355E-1    , /*Hex  2^ -4   *  1.C719538248597 */
q2     =  9.9176615021572857300E-4    ; /*Hex  2^-10   *  1.03FC4CB8C98E8 */
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
vc(p1, 1.5150724356786683059E-2 ,3abe,3d78,066a,67e1,  -6, .F83ABE67E1066A)
vc(p2, 6.3112487873718332688E-5 ,5b42,3984,0173,48cd, -13, .845B4248CD0173)
vc(q1, 1.1363478204690669916E-1 ,b95a,3ee8,ec45,44a2,  -3, .E8B95A44A2EC45)
vc(q2, 1.2624568129896839182E-3 ,7905,3ba5,f5e7,72e4,  -9, .A5790572E4F5E7)
vc(q3, 1.5021856115869022674E-6 ,9eb4,36c9,c395,604a, -19, .C99EB4604AC395)

ic(p1, 1.3887401997267371720E-2,  -7, 1.C70FF8B3CC2CF)
ic(p2, 3.3044019718331897649E-5, -15, 1.15317DF4526C4)
ic(q1, 1.1110813732786649355E-1,  -4, 1.C719538248597)
ic(q2, 9.9176615021572857300E-4, -10, 1.03FC4CB8C98E8)

#ifdef vccast
#define       p1    vccast(p1)
#define       p2    vccast(p2)
#define       q1    vccast(q1)
#define       q2    vccast(q2)
#define       q3    vccast(q3)
#endif

E 10
D 13
double exp__E(x,c)
E 13
I 13
double __exp__E(x,c)
E 13
double x,c;
{
D 3
	double static zero=0.0, one=1.0, half=1.0/2.0, small=1.0E-19;
E 3
I 3
D 10
	static double zero=0.0, one=1.0, half=1.0/2.0, small=1.0E-19;
E 3
	double copysign(),z,p,q,xp,xh,w;
E 10
I 10
	const static double zero=0.0, one=1.0, half=1.0/2.0, small=1.0E-19;
	double z,p,q,xp,xh,w;
E 10
	if(copysign(x,one)>small) {
           z = x*x  ;
	   p = z*( p1 +z* p2 );
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
           q = z*( q1 +z*( q2 +z* q3 ));
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe) */
E 6
           q = z*( q1 +z*  q2 );
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe) */
E 6
           xp= x*p     ; 
	   xh= x*half  ;
           w = xh-(q-xp)  ;
	   p = p+p;
	   c += x*((xh*w-(q-(p+xp)))/(one-w)+c);
	   return(z*half+c);
	}
	/* end of |x| > small */

	else {
	    if(x!=zero) one+small;	/* raise the inexact flag */
	    return(copysign(zero,x));
	}
}
E 1
