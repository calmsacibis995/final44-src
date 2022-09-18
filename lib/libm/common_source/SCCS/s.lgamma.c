h02144
s 00001/00002/00280
d D 8.2 93/11/30 16:28:45 mckusick 18 17
c lint
e
s 00002/00002/00280
d D 8.1 93/06/04 17:03:31 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00276
d D 5.12 93/01/10 12:47:54 bostic 16 15
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00001/00005/00281
d D 5.11 92/12/16 21:18:31 mcilroy 15 14
c Fixed comments section.
e
s 00001/00001/00285
d D 5.10 92/12/16 21:11:35 mcilroy 14 13
c 
e
s 00049/00023/00237
d D 5.9 92/12/16 18:08:56 bostic 13 12
c new version from Peter McIlroy; note, funded by UUNET
e
s 00001/00001/00259
d D 5.8 92/12/14 19:03:11 mcilroy 12 11
c 
e
s 00178/00166/00082
d D 5.7 92/12/14 18:37:15 mcilroy 11 10
c 
e
s 00002/00002/00246
d D 5.6 92/12/02 15:33:33 bostic 10 9
c original software, not AT&T proprietary
e
s 00207/00106/00041
d D 5.5 92/12/02 15:29:17 bostic 9 8
c original version from Peter McIlroy
e
s 00005/00004/00142
d D 5.4 91/04/20 14:21:40 bostic 8 7
c new copyright; att/bsd/shared
e
s 00009/00010/00137
d D 5.3 88/09/22 16:23:22 bostic 7 6
c update for ANSI C from Alex Zliu and John Gilmore
e
s 00008/00003/00139
d D 5.2 88/04/29 12:20:09 bostic 6 5
c add Berkeley copyright; NOTE: this code is AT&T derived!
e
s 00000/00000/00142
d D 5.1 87/11/30 18:34:03 bostic 5 4
c tahoe release
e
s 00005/00005/00137
d D 1.4 87/07/13 19:20:41 zliu 4 3
c clean-ups.
e
s 00002/00002/00140
d D 1.3 87/07/07 01:31:58 zliu 3 2
c first shot at TAHOE.
e
s 00004/00003/00138
d D 1.2 85/09/11 23:52:53 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00141/00000/00000
d D 1.1 85/09/06 17:52:57 zliu 1 0
c date and time created 85/09/06 17:52:57 by zliu
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
D 10
 * Copyright (c) 1985 The Regents of the University of California.
E 10
I 10
D 17
 * Copyright (c) 1992 The Regents of the University of California.
E 10
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 10
 * %sccs.include.proprietary.c%
E 10
I 10
 * %sccs.include.redist.c%
E 10
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
"%Z%%M%	4.4 (Berkeley) 9/11/85; %I% (ucb.elefunt) %G%";
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

I 13
/*
 * Coded by Peter McIlroy, Nov 1992;
 *
 * The financial support of UUNET Communications Services is greatfully
 * acknowledged.
 */

E 13
D 9
/*
	C program for floating point log Gamma function
E 9
I 9
#include <math.h>
#include <errno.h>
E 9

D 2
	lgama(x) computes the log of the absolute
E 2
I 2
D 9
	lgamma(x) computes the log of the absolute
E 2
	value of the Gamma function.
	The sign of the Gamma function is returned in the
	external quantity signgam.
E 9
I 9
#include "mathimpl.h"
E 9

D 9
	The coefficients for expansion around zero
	are #5243 from Hart & Cheney; for expansion
	around infinity they are #5404.

	Calls log, floor and sin.
E 9
I 9
D 11
/* TRUNC sets trailing bits in a floating-point number to zero.
 * ptrx points to the second half of the floating-point number.
 * x1 is a temporary variable.
E 11
I 11
/* Log gamma function.
 * Error:  x > 0 error < 1.3ulp.
 *	   x > 4, error < 1ulp.
 *	   x > 9, error < .6ulp.
D 13
 * 	   x < 0, all bets are off.
E 13
I 13
 * 	   x < 0, all bets are off. (When G(x) ~ 1, log(G(x)) ~ 0)
E 13
 * Method:
 *	x > 6:
 *		Use the asymptotic expansion (Stirling's Formula)
 *	0 < x < 6:
D 13
 *		Use gamma(x+1) = x*gamma(x)
E 13
I 13
 *		Use gamma(x+1) = x*gamma(x) for argument reduction.
E 13
 *		Use rational approximation in
 *		the range 1.2, 2.5
I 13
 *		Two approximations are used, one centered at the
 *		minimum to ensure monotonicity; one centered at 2
 *		to maintain small relative error.
E 13
 *	x < 0:
 *		Use the reflection formula,
 *		G(1-x)G(x) = PI/sin(PI*x)
 * Special values:
 *	non-positive integer	returns +Inf.
 *	NaN			returns NaN
E 11
E 9
*/
I 13
static int endian;
E 13
D 11

E 11
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
#endif
E 4
I 4
#endif	/* defined(vax)||defined(tahoe) */
E 9
I 9
#if defined(vax) || defined(tahoe)
I 13
#define _IEEE		0
E 13
D 11
#define LSHFT_PLUS_1	(134217728.+1.)
#define TRUNC(x, dummy, x1) x1 = x*LSHFT_PLUS_1, x -= x1, x += x1
E 11
I 11
/* double and float have same size exponent field */
D 13
#define TRUNC(x) (double) (float) (x)
#define _IEEE	0
E 13
I 13
#define TRUNC(x)	x = (double) (float) (x)
E 13
E 11
#else
D 11
#define MASK 0xf8000000
#define TRUNC(x, ptrx, dummy) *ptrx &= MASK
E 11
I 11
D 13
#define TRUNC(x) *(((int *) &x) + 1) &= 0xf8000000
#define _IEEE	1
#define infnan(x) (zero/zero)
E 13
I 13
#define _IEEE		1
#define TRUNC(x)	*(((int *) &x) + endian) &= 0xf8000000
#define infnan(x)	0.0
E 13
E 11
#endif
E 9
I 7

E 7
E 4
D 9
int	signgam = 0;
D 7
static double goobie	= 0.9189385332046727417803297;	/* log(2*pi)/2 */
static double pi	= 3.1415926535897932384626434;
E 7
I 7
static const double goobie = 0.9189385332046727417803297;  /* log(2*pi)/2 */
static const double pi	   = 3.1415926535897932384626434;
E 9
I 9
D 11
#define x0	0.461632144968362356785
#define x0_lo	-.000000000000000015522348162858676890521
#define a0_hi	-0.12148629053584961146
#define a0_lo	3.07435645275902737e-18
#define LEFT	(1.0 - (x0 + .25))
#define RIGHT	(x0 - .218)
#define lns2pi_hi 0.418945312500000
#define lns2pi_lo -.000006779295327258219670263595
E 11
I 11
D 18
extern double log1p(double);
E 18
static double small_lgam(double);
static double large_lgam(double);
static double neg_lgam(double);
static double zero = 0.0, one = 1.0;
int signgam;
E 11
E 9
E 7

I 11
D 13
#define lns2pi	.418938533204672741780329736405
E 13
E 11
D 9
#define M 6
#define N 8
D 7
static double p1[] = {
E 7
I 7
static const double p1[] = {
E 7
	0.83333333333333101837e-1,
	-.277777777735865004e-2,
	0.793650576493454e-3,
	-.5951896861197e-3,
	0.83645878922e-3,
	-.1633436431e-2,
E 9
I 9
#define UNDERFL (1e-1020 * 1e-1020)
D 11
int signgam;
E 11

D 11
#define r0	-0.02771227512955130520
#define r1	-0.2980729795228150847
#define r2	-0.3257411333183093394
#define r3	-0.1126814387531706041
#define r4	-0.01129130057170225562
#define r5	-2.259650588213369095e-05
#define s0	1.7144571600017144419
#define s1	2.7864695046181946481
#define s2	1.5645463655191798047
#define s3	0.34858463899811098496
#define s4	0.024677593453636563481
E 11
I 11
#define LEFT	(1.0 - (x0 + .25))
#define RIGHT	(x0 - .218)
/*
/* Constants for approximation in [1.244,1.712]
*/
#define x0	0.461632144968362356785
#define x0_lo	-.000000000000000015522348162858676890521
#define a0_hi	-0.12148629128932952880859
#define a0_lo	.0000000007534799204229502
#define r0	-2.771227512955130520e-002
#define r1	-2.980729795228150847e-001
#define r2	-3.257411333183093394e-001
#define r3	-1.126814387531706041e-001
#define r4	-1.129130057170225562e-002
#define r5	-2.259650588213369095e-005
#define s0	 1.714457160001714442e+000
#define s1	 2.786469504618194648e+000
#define s2	 1.564546365519179805e+000
#define s3	 3.485846389981109850e-001
#define s4	 2.467759345363656348e-002
/*
 * Constants for approximation in [1.71, 2.5]
*/
#define a1_hi	4.227843350984671344505727574870e-01
#define a1_lo	4.670126436531227189e-18
#define p0	3.224670334241133695662995251041e-01
#define p1	3.569659696950364669021382724168e-01
#define p2	1.342918716072560025853732668111e-01
#define p3	1.950702176409779831089963408886e-02
#define p4	8.546740251667538090796227834289e-04
#define q0	1.000000000000000444089209850062e+00
#define q1	1.315850076960161985084596381057e+00
#define q2	6.274644311862156431658377186977e-01
#define q3	1.304706631926259297049597307705e-01
#define q4	1.102815279606722369265536798366e-02
#define q5	2.512690594856678929537585620579e-04
#define q6	-1.003597548112371003358107325598e-06
/*
 * Stirling's Formula, adjusted for equal-ripple. x in [6,Inf].
*/
D 13
#define pb0	.0833333333333333148296162562474
#define pb1	-.00277777777774548123579378966497
#define pb2	.000793650778754435631476282786423
#define pb3	-.000595235082566672847950717262222
#define pb4	.000841428560346653702135821806252
#define pb5	-.00189773526463879200348872089421
#define pb6	.00569394463439411649408050664078
#define pb7	-.0144705562421428915453880392761
E 13
I 13
#define lns2pi	.418938533204672741780329736405
#define pb0	 8.33333333333333148296162562474e-02
#define pb1	-2.77777777774548123579378966497e-03
#define pb2	 7.93650778754435631476282786423e-04
#define pb3	-5.95235082566672847950717262222e-04
#define pb4	 8.41428560346653702135821806252e-04
#define pb5	-1.89773526463879200348872089421e-03
#define pb6	 5.69394463439411649408050664078e-03
#define pb7	-1.44705562421428915453880392761e-02
E 13
E 11

D 11
#define p0     -7.721566490153286087127140e-02
#define p1	2.077324848654884653970785e-01
#define p2	3.474331160945523535787194e-01
#define p3	1.724375677840324429295524e-01
#define p4	3.546181984297784658205969e-02
#define p5	2.866163630124151557532506e-03
#define p6	6.143168512963655570532770e-05
#define q0	1.000000000000000000000000e+00
#define q1	1.485897307300750567469226e+00
#define q2	8.336064915387758261556045e-01
#define q3	2.185469782512070977585556e-01
#define q4	2.671060746990048983840354e-02
#define q5	1.296631961305647947057711e-03
#define q6	1.484566091079246905938151e-05

#define NP2 8
double P2[] = {
.0833333333333333148296162562474,
-.00277777777774548123579378966497,
.000793650778754435631476282786423,
-.000595235082566672847950717262222,
.000841428560346653702135821806252,
-.00189773526463879200348872089421,
.00569394463439411649408050664078,
-.0144705562421428915453880392761
E 9
};
D 7
static double p2[] = {
E 7
I 7
D 9
static const double p2[] = {
E 7
	-.42353689509744089647e5,
	-.20886861789269887364e5,
	-.87627102978521489560e4,
	-.20085274013072791214e4,
	-.43933044406002567613e3,
	-.50108693752970953015e2,
	-.67449507245925289918e1,
	0.0,
};
D 7
static double q2[] = {
E 7
I 7
static const double q2[] = {
E 7
	-.42353689509744090010e5,
	-.29803853309256649932e4,
	0.99403074150827709015e4,
	-.15286072737795220248e4,
	-.49902852662143904834e3,
	0.18949823415702801641e3,
	-.23081551524580124562e2,
	0.10000000000000000000e1,
};
E 9

I 7
D 9
static double pos(), neg(), asym();
E 9
I 9
static double neg_lgam __P((double));
static double small_lgam __P((double));
static double large_lgam __P((double));
E 9

E 11
E 7
D 18
double
E 18
I 18
__pure double
E 18
D 2
lgama(arg)
E 2
I 2
D 9
lgamma(arg)
E 2
double arg;
E 9
I 9
D 11
lgamma(x)
	double x;
E 11
I 11
lgamma(double x)
E 11
E 9
{
D 7
	double log(), pos(), neg(), asym();
E 7
D 9

	signgam = 1.;
	if(arg <= 0.) return(neg(arg));
	if(arg > 8.) return(asym(arg));
	return(log(pos(arg)));
E 9
I 9
D 11
	double zero = 0.0, one = 1.0;
E 11
	double r;
I 13

E 13
	signgam = 1;
I 13
	endian = ((*(int *) &one)) ? 1 : 0;

E 13
D 11
	if (!finite(x)) {
		errno = EDOM;
		if (x < 0)
			x = -x;
		else if (x > 0)
			errno = ERANGE;
		return (x);
	}
E 11
I 11
	if (!finite(x))
		if (_IEEE)
			return (x+x);
		else return (infnan(EDOM));

E 11
	if (x > 6 + RIGHT) {
D 11
		if (x > 1.0e20)
			return (x*(log(x)-one));
E 11
		r = large_lgam(x);
		return (r);
D 11
	} else if (x > 1e-17)
E 11
I 11
	} else if (x > 1e-16)
E 11
		return (small_lgam(x));
D 11
	else if(x > -1e-17) {
E 11
I 11
	else if (x > -1e-16) {
E 11
		if (x < 0)
			signgam = -1, x = -x;
		return (-log(x));
	} else
		return (neg_lgam(x));
E 9
}

I 9
D 11
/* Accurate to max(ulp(1/128) absolute, 2^-75 relative) error. */
E 11
E 9
static double
D 9
asym(arg)
double arg;
E 9
I 9
D 11
large_lgam(x)
	double x;
E 11
I 11
large_lgam(double x)
E 11
E 9
{
D 7
	double log();
E 7
D 9
	double n, argsq;
E 9
I 9
	double z, p, x1;
E 9
	int i;
I 9
D 11
	long *pva, *pua;
E 11
	struct Double t, u, v;
D 11
	pua = (long *) &u.a, pua++;
	pva = (long *) &v.a, pva++;
	z = 1.0/(x*x);
	for (p = P2[i = NP2-1]; --i >= 0;)
		p = P2[i] + p*z;	/* error in approximation = 2.8e-18 */
E 11
I 11
D 16
	u = log__D(x);
E 16
I 16
	u = __log__D(x);
E 16
	u.a -= 1.0;
	if (x > 1e15) {
		v.a = x - 0.5;
		TRUNC(v.a);
		v.b = (x - v.a) - 0.5;
		t.a = u.a*v.a;
		t.b = x*u.b + v.b*u.a;
		if (_IEEE == 0 && !finite(t.a))
			return(infnan(ERANGE));
		return(t.a + t.b);
	}
	x1 = 1./x;
	z = x1*x1;
	p = pb0+z*(pb1+z*(pb2+z*(pb3+z*(pb4+z*(pb5+z*(pb6+z*pb7))))));
					/* error in approximation = 2.8e-19 */
E 11
E 9

D 9
	argsq = 1./(arg*arg);
	for(n=0,i=M-1; i>=0; i--){
		n = n*argsq + p1[i];
	}
	return((arg-.5)*log(arg) - arg + goobie + n/arg);
E 9
I 9
D 11
	p = p/x;			/* ulp = 1.7e-18; error < 1.6ulp */
					/* 0 < frac < 1/64 (at x = 5.5) */
	t = log__D(x);
	t.a -= 1.0;
	u.a = t.a + t.b;
	TRUNC (u.a, pua, x1);		/* truncate u.a */
	u.b = (t.a - u.a);
	u.b += t.b;
	x -= .5;
	v.a = x;
	TRUNC(v.a, pva, x1);		/* truncate v.a */
E 11
I 11
	p = p*x1;			/* error < 2.3e-18 absolute */
					/* 0 < p < 1/64 (at x = 5.5) */
D 14
	x = x - 0.5;
E 14
I 14
	v.a = x = x - 0.5;
E 14
	TRUNC(v.a);			/* truncate v.a to 26 bits. */
E 11
	v.b = x - v.a;
	t.a = v.a*u.a;			/* t = (x-.5)*(log(x)-1) */
D 11
	t.b = v.b*u.a + x*u.b;
	z = t.b + lns2pi_lo;		/* return t + lns2pi + p */
	z += p; z += lns2pi_hi;
	z += t.a;
	return (z);
E 11
I 11
D 12
	t.b = v.b*u.a + z*u.b;
E 12
I 12
	t.b = v.b*u.a + x*u.b;
E 12
	t.b += p; t.b += lns2pi;	/* return t + lns2pi + p */
	return (t.a + t.b);
E 11
E 9
}
D 9

E 9
I 9
D 11
/* Good to < 1 ulp.  (provably .90 ulp; .87 ulp on 1,000,000 runs.)
   It also has correct monotonicity.
 */
E 11
I 11

E 11
E 9
static double
D 9
neg(arg)
double arg;
E 9
I 9
D 11
small_lgam(x)
	double x;
E 11
I 11
small_lgam(double x)
E 11
E 9
{
D 9
	double t;
E 9
I 9
D 11
	int xi;
	double y, z, t, r = 0, p, q;
E 11
I 11
	int x_int;
	double y, z, t, r = 0, p, q, hi, lo;
E 11
	struct Double rr;
E 9
D 7
	double log(), sin(), floor(), pos();
E 7
D 11

D 9
	arg = -arg;
     /*
      * to see if arg were a true integer, the old code used the
      * mathematically correct observation:
      * sin(n*pi) = 0 <=> n is an integer.
      * but in finite precision arithmetic, sin(n*PI) will NEVER
      * be zero simply because n*PI is a rational number.  hence
      *	it failed to work with our newer, more accurate sin()
      * which uses true pi to do the argument reduction...
      *	temp = sin(pi*arg);
      */
	t = floor(arg);
	if (arg - t  > 0.5e0)
	    t += 1.e0;				/* t := integer nearest arg */
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
	if (arg == t) {
D 7
	    extern double infnan();
E 7
	    return(infnan(ERANGE));		/* +INF */
E 9
I 9
	/* Do nasty area near the minimum.  No good for 1.25 < x < 2.5 */
	if (x < 2.0 - LEFT && x > 1.0 + RIGHT) {
		t = x - 1.0; t -= x0;
E 11
I 11
	x_int = (x + .5);
	y = x - x_int;
	if (x_int <= 2 && y > RIGHT) {
		t = y - x0;
		y--; x_int++;
		goto CONTINUE;
	} else if (y < -LEFT) {
		t = y +(1.0-x0);
CONTINUE:
E 11
		z = t - x0_lo;
		p = r0+z*(r1+z*(r2+z*(r3+z*(r4+z*r5))));
		q = s0+z*(s1+z*(s2+z*(s3+z*s4)));
D 11
		r = t*(z*(p/q) - x0_lo) + a0_lo;
		r += .5*t*t; r += a0_hi;
		return (r);
E 9
	}
D 4
#endif
E 4
I 4
D 9
#endif	/* defined(vax)||defined(tahoe) */
E 4
	signgam = (int) (t - 2*floor(t/2));	/* signgam =  1 if t was odd, */
						/*            0 if t was even */
	signgam = signgam - 1 + signgam;	/* signgam =  1 if t was odd, */
						/*           -1 if t was even */
	t = arg - t;				/*  -0.5 <= t <= 0.5 */
	if (t < 0.e0) {
	    t = -t;
	    signgam = -signgam;
E 9
I 9
	xi = (x + .5);
	y = x - xi;
	rr.a = rr.b = 0;
	if (y < -LEFT) {	/* necessary for 2.5 < x < 2.72.. */
		t = y + (1.0 - x0);
		z = t - x0_lo;
		p = r0+z*(r1+z*(r2+z*(r3+z*(r4+z*r5))));
		q = s0+z*(s1+z*(s2+z*(s3+z*s4)));
		r = t*(z*(p/q) - x0_lo) + a0_lo;
		r += .5*t*t;
		q = a0_hi;
		printf("(0)q = %.18lg r = %.18lg\n", q, r);
E 11
I 11
		r = t*(z*(p/q) - x0_lo);
		t = .5*t*t;
		z = 1.0;
		switch (x_int) {
		case 6:	z  = (y + 5);
		case 5:	z *= (y + 4);
		case 4:	z *= (y + 3);
		case 3:	z *= (y + 2);
D 16
			rr = log__D(z);
E 16
I 16
			rr = __log__D(z);
E 16
			rr.b += a0_lo; rr.a += a0_hi;
			return(((r+rr.b)+t+rr.a));
		case 2: return(((r+a0_lo)+t)+a0_hi);
		case 0: r -= log1p(x);
D 16
		default: rr = log__D(x);
E 16
I 16
		default: rr = __log__D(x);
E 16
			rr.a -= a0_hi; rr.b -= a0_lo;
			return(((r - rr.b) + t) - rr.a);
		}
E 11
	} else {
D 11
		p = y*(p0+y*(p1+y*(p2+y*(p3+y*(p4+y*(p5+y*p6))))));
E 11
I 11
		p = p0+y*(p1+y*(p2+y*(p3+y*p4)));
E 11
		q = q0+y*(q1+y*(q2+y*(q3+y*(q4+y*(q5+y*q6)))));
D 11
		r = p/q;
		q = .5*y;
		printf("(1)q = %.18lg r = %.18lg\n", q, r);
E 11
I 11
		p = p*(y/q);
		t = (double)(float) y;
		z = y-t;
		hi = (double)(float) (p+a1_hi);
		lo = a1_hi - hi; lo += p; lo += a1_lo;
		r = lo*y + z*hi;	/* q + r = y*(a0+p/q) */
		q = hi*t;
		z = 1.0;
		switch (x_int) {
		case 6:	z  = (y + 5);
		case 5:	z *= (y + 4);
		case 4:	z *= (y + 3);
		case 3:	z *= (y + 2);
D 16
			rr = log__D(z);
E 16
I 16
			rr = __log__D(z);
E 16
			r += rr.b; r += q;
			return(rr.a + r);
		case 2:	return (q+ r);
D 16
		case 0: rr = log__D(x);
E 16
I 16
		case 0: rr = __log__D(x);
E 16
			r -= rr.b; r -= log1p(x);
			r += q; r-= rr.a;
			return(r);
D 16
		default: rr = log__D(x);
E 16
I 16
		default: rr = __log__D(x);
E 16
			r -= rr.b;
			q -= rr.a;
			return (r+q);
		}
E 11
E 9
	}
D 9
	return(-log(arg*pos(arg)*sin(pi*t)/pi));
E 9
I 9
D 11
	printf("y = %lg, r = %.18lg\n", y, r);
	z = 1.0;
	switch (xi) {
	case 6:	z  = (y + 5);
	case 5:	z *= (y + 4);
	case 4:	z *= (y + 3);
	case 3:	z *= (y + 2);
		rr = log__D(z);
		printf("%.21lg, %lg\n", rr.a, rr.b);
		r += rr.b; q += r;
		return(q + rr.a);
	case 2:	return (q + r);

	case 0: printf("r = %lg\n", r);
		r -= log1p(x); printf("\t%lg\n", r);
	default: rr = log__D(x);
		r -= rr.b; printf("\t%lg\n", r);
	}
	if (q > .5 *rr.a) {
		printf("q = %lg, rr = %lg, r = %lg\n", q, rr.a, r);
		q -= rr.a;
		return(r + q);
	} else
		printf("q = %lg, rr = %lg, r = %lg\n", q, rr.a, r);
		return((r + q) - rr.a);
E 11
E 9
}

I 9
D 13
#define lpi_hi 1.1447298858494001638
#define lpi_lo .0000000000000000102659511627078262
/* Error: within 3.5 ulp for x < 171.  For large x, see lgamma. */
E 13
E 9
static double
D 9
pos(arg)
double arg;
E 9
I 9
D 11
neg_lgam(x)
	double x;
E 11
I 11
neg_lgam(double x)
E 11
E 9
{
I 13
	int xi;
E 13
D 9
	double n, d, s;
	register i;
E 9
I 9
D 11
	struct Double lg, lsine;
E 11
	double y, z, one = 1.0, zero = 0.0;
I 13
	extern double gamma();
E 13
E 9

I 13
	/* avoid destructive cancellation as much as possible */
	if (x > -170) {
		xi = x;
		if (xi == x)
			if (_IEEE)
				return(one/zero);
			else
				return(infnan(ERANGE));
		y = gamma(x);
		if (y < 0)
			y = -y, signgam = -1;
		return (log(y));
	}
E 13
D 9
	if(arg < 2.) return(pos(arg+1.)/arg);
	if(arg > 3.) return((arg-1.)*pos(arg-1.));

	s = arg - 2.;
	for(n=0,d=0,i=N-1; i>=0; i--){
		n = n*s + p2[i];
		d = d*s + q2[i];
E 9
I 9
	z = floor(x + .5);
D 11
	if (z == x) {
		errno = EDOM;
		return (one/zero);	/* convention: G(-(integer)) -> +oo */
E 11
I 11
	if (z == x) {		/* convention: G(-(integer)) -> +Inf */
		if (_IEEE)
			return (one/zero);
		else
			return (infnan(ERANGE));
E 11
E 9
	}
D 9
	return(n/d);
E 9
I 9
D 11
	y = ceil(x);
	if (y*.5 == ceil(.5*y))
E 11
I 11
	y = .5*ceil(x);
	if (y == ceil(y))
E 11
		signgam = -1;
D 11

E 11
	x = -x;
	z = fabs(x + z);	/* 0 < z <= .5 */
	if (z < .25)
		z = sin(M_PI*z);
	else
D 11
		z = cos(M_PI*(.5-z));
E 11
I 11
		z = cos(M_PI*(0.5-z));
E 11
D 13
	z = -log(z*x/M_PI);
E 13
I 13
	z = log(M_PI/(z*x));
E 13
D 15

D 11
	if (x > 6.5)
E 11
I 11
	if (x > 6. + RIGHT)
E 11
D 13
		y -= large_lgam(x);
E 13
I 13
		y = large_lgam(x);
E 13
	else
D 13
		y = -small_lgam (x);
	return (y + z);
E 13
I 13
		y = small_lgam (x);
E 15
I 15
	y = large_lgam(x);
E 15
	return (z - y);
E 13
E 9
}
E 1
