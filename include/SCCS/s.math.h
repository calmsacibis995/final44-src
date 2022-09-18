h16182
s 00002/00002/00104
d D 8.1 93/06/02 20:05:47 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00105
d D 5.10 93/02/10 10:48:08 bostic 18 17
c M_* are not in ANSI or POSIX
e
s 00048/00048/00058
d D 5.9 92/03/02 20:31:51 torek 17 16
c declare pure functions as such
e
s 00013/00003/00093
d D 5.8 91/04/02 12:25:57 bostic 16 15
c get HUGE right for the VAX and Tahoe
e
s 00000/00005/00096
d D 5.7 91/04/02 08:24:56 bostic 15 14
c remove math library specific part of copyright
e
s 00016/00002/00085
d D 5.6 91/04/02 06:44:24 bostic 14 13
c add XPG, Sun, Sys V math constants
e
s 00004/00004/00083
d D 5.5 91/04/01 09:01:52 bostic 13 12
c add isinf(), isnan() for all architectures
e
s 00005/00000/00082
d D 5.4 91/03/18 11:03:17 donn 12 11
c Prevent re-inclusions
e
s 00001/00001/00081
d D 5.3 91/02/24 14:09:50 bostic 11 10
c modf takes a double * as it's second argument
e
s 00063/00009/00019
d D 5.2 91/02/14 17:50:28 donn 10 9
c Proto-ized, ANSI-ized, POSIX-ized for your protection.
e
s 00011/00017/00017
d D 5.1 91/02/05 17:10:55 bostic 9 8
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00033
d D 4.8 90/06/01 14:00:56 bostic 8 7
c new copyright notice
e
s 00028/00004/00016
d D 4.7 88/09/22 16:00:37 bostic 7 6
c update for ANSI C from Alex Zliu and John Gilmore
c replaces usr.lib/libm/math.h, add Berkeley copyright
e
s 00002/00002/00018
d D 4.6 85/09/11 18:07:52 mckusick 6 5
c new from Kahan
e
s 00001/00001/00019
d D 4.5 85/08/22 16:04:52 miriam 5 4
c Use old gamma.
e
s 00006/00002/00014
d D 4.4 85/08/20 14:21:31 miriam 4 3
c Update from Prof. Kahan.
e
s 00011/00006/00005
d D 4.3 85/05/23 15:40:28 miriam 3 2
c From Prof. Kahan - includes addition routines in the math library.
e
s 00001/00001/00010
d D 4.2 84/03/08 08:31:44 karels 2 1
c fmod=>modf
e
s 00011/00000/00000
d D 4.1 83/05/03 13:48:02 sam 1 0
c date and time created 83/05/03 13:48:02 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 7
/*	%M%	%I%	%G%	*/
E 7
I 7
/*
D 16
 * Copyright (c) 1985 The Regents of the University of California.
E 16
I 16
D 19
 * Copyright (c) 1985, 1990 The Regents of the University of California.
E 16
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1985, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
D 8
 * Redistribution and use in source and binary forms are permitted
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 *
D 15
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
 *
E 15
 *	%W% (Berkeley) %G%
 */
E 7
E 3

I 12
#ifndef	_MATH_H_
#define	_MATH_H_

E 12
D 2
extern double fabs(), floor(), ceil(), fmod(), ldexp(), frexp();
E 2
I 2
D 3
extern double fabs(), floor(), ceil(), modf(), ldexp(), frexp();
E 2
extern double sqrt(), hypot(), atof();
extern double sin(), cos(), tan(), asin(), acos(), atan(), atan2();
extern double exp(), log(), log10(), pow();
extern double sinh(), cosh(), tanh();
E 3
I 3
D 9
extern double asinh(), acosh(), atanh();
extern double erf(), erfc();
D 4
extern double E(), L(), exp(), log(), log10(), pow();
E 4
I 4
extern double exp(), expm1(), log(), log10(), log1p(), pow();
E 4
D 6
extern double fabs(), floor(), ceil();
E 3
D 4
extern double gamma();
E 4
I 4
D 5
extern double lgama();
E 5
I 5
extern double gamma();
E 6
I 6
extern double fabs(), floor(), ceil(), rint();
extern double lgamma();
E 6
E 5
E 4
I 3
extern double hypot(), cabs();
extern double copysign(), drem(), logb(), scalb();
E 9
I 9
D 10
#define	HUGE	1.701411733192644270e38
E 10
I 10
D 16
#if defined(vax) || defined(tahoe)
D 14
#define	HUGE_VAL	1.701411733192644270e38
E 14
I 14
#define	HUGE_VAL	1.701411733192644270e+38
E 16
I 16
#if defined(vax) || defined(tahoe)		/* DBL_MAX from float.h */
#define	HUGE_VAL	1.701411834604692294E+38
E 16
E 14
#else
D 13
#define	HUGE_VAL	1e500	/* positive infinity */
E 13
I 13
D 14
#define	HUGE_VAL	1e500		/* positive infinity */
E 14
I 14
#define	HUGE_VAL	1e500			/* IEEE: positive infinity */
E 14
E 13
#endif
E 10
E 9
I 4
D 7
extern int finite();
#ifdef vax
E 7
I 7

D 9
#if defined(vax) || defined(tahoe)
E 7
extern double infnan();
#endif
E 9
I 9
D 10
double	acos(), acosh(), asin(), asinh(), atan(), atan2(), atanh(),
	atof(), cabs(), cbrt(), ceil(), copysign(), cos(), cosh(),
	drem(), erf(), erfc(), exp(), expm1(), fabs(), floor(), frexp(),
	hypot(), j0(), j1(), jn(), ldexp(), lgamma(), log(), log10(),
	log1p(), logb(), modf(), pow(), rint(), scalb(), sin(), sinh(),
	sqrt(), tan(), tanh(), y0(), y1(), yn();
E 10
I 10
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
I 16
#if defined(vax) || defined(tahoe)
/*
 * HUGE for the VAX and Tahoe converts to the largest possible F-float value.
 * This implies an understanding of the conversion behavior of atof(3).  It
 * was defined to be the largest float so that overflow didn't occur when it
 * was assigned to a single precision number.  HUGE_VAL is strongly preferred.
 */
#define	HUGE	1.701411733192644270E+38		
#else
E 16
D 13
#define	HUGE		HUGE_VAL
E 13
I 13
#define	HUGE	HUGE_VAL
I 16
#endif
E 16
E 13
D 18
#endif
E 18
I 14

#define	M_E		2.7182818284590452354	/* e */
#define	M_LOG2E		1.4426950408889634074	/* log 2e */
#define	M_LOG10E	0.43429448190325182765	/* log 10e */
#define	M_LN2		0.69314718055994530942	/* log e2 */
#define	M_LN10		2.30258509299404568402	/* log e10 */
#define	M_PI		3.14159265358979323846	/* pi */
#define	M_PI_2		1.57079632679489661923	/* pi/2 */
#define	M_PI_4		0.78539816339744830962	/* pi/4 */
#define	M_1_PI		0.31830988618379067154	/* 1/pi */
#define	M_2_PI		0.63661977236758134308	/* 2/pi */
#define	M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define	M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define	M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
I 18
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */
E 18
E 14
E 10
E 9
I 7

D 9
extern int finite();
E 7
E 4
E 3
extern double j0(), j1(), jn(), y0(), y1(), yn();
I 3
extern double sin(), cos(), tan(), asin(), acos(), atan(), atan2();
extern double sinh(), cosh(), tanh();
extern double cbrt(), sqrt();
extern double modf(), ldexp(), frexp(), atof();
E 9
I 9
D 10
int finite();
E 10
I 10
#include <sys/cdefs.h>
E 10
E 9
E 3

I 10
__BEGIN_DECLS
D 17
double	acos __P((double));
double	asin __P((double));
double	atan __P((double));
double	atan2 __P((double, double));
double	ceil __P((double));
double	cos __P((double));
double	cosh __P((double));
double	exp __P((double));
double	fabs __P((double));
double	floor __P((double));
double	fmod __P((double, double));
double	frexp __P((double, int *));
double	ldexp __P((double, int));
double	log __P((double));
double	log10 __P((double));
D 11
double	modf __P((double, int *));
E 11
I 11
double	modf __P((double, double *));
E 11
double	pow __P((double, double));
double	sin __P((double));
double	sinh __P((double));
double	sqrt __P((double));
double	tan __P((double));
double	tanh __P((double));
E 17
I 17
__pure	double	acos __P((double));
__pure	double	asin __P((double));
__pure	double	atan __P((double));
__pure	double	atan2 __P((double, double));
__pure	double	ceil __P((double));
__pure	double	cos __P((double));
__pure	double	cosh __P((double));
__pure	double	exp __P((double));
__pure	double	fabs __P((double));
__pure	double	floor __P((double));
__pure	double	fmod __P((double, double));
	double	frexp __P((double, int *));
__pure	double	ldexp __P((double, int));
__pure	double	log __P((double));
__pure	double	log10 __P((double));
	double	modf __P((double, double *));
__pure	double	pow __P((double, double));
__pure	double	sin __P((double));
__pure	double	sinh __P((double));
__pure	double	sqrt __P((double));
__pure	double	tan __P((double));
__pure	double	tanh __P((double));
E 17

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
D 17
double	acosh __P((double));
double	asinh __P((double));
double	atanh __P((double));
double	cabs();		/* we can't describe cabs()'s argument properly */
double	cbrt __P((double));
double	copysign __P((double, double));
double	drem __P((double, double));
double	erf __P((double));
double	erfc __P((double));
double	expm1 __P((double));
int	finite __P((double));
double	hypot __P((double, double));
E 17
I 17
__pure	double	acosh __P((double));
__pure	double	asinh __P((double));
__pure	double	atanh __P((double));
	double	cabs();	/* we can't describe cabs()'s argument properly */
__pure	double	cbrt __P((double));
__pure	double	copysign __P((double, double));
__pure	double	drem __P((double, double));
__pure	double	erf __P((double));
__pure	double	erfc __P((double));
__pure	double	expm1 __P((double));
__pure	int	finite __P((double));
__pure	double	hypot __P((double, double));
E 17
E 10
D 7
#define HUGE	1.701411733192644270e38
E 7
I 7
D 9
#define	HUGE	1.701411733192644270e38
E 9
I 9
#if defined(vax) || defined(tahoe)
D 10
double infnan();
E 10
I 10
D 17
double	infnan __P((int));
E 17
I 17
__pure	double	infnan __P((int));
E 17
D 13
#else
int	isnan __P((double));
E 13
E 10
#endif
I 13
D 17
int	isinf __P((double));
int	isnan __P((double));
E 13
I 10
double	j0 __P((double));
double	j1 __P((double));
double	jn __P((int, double));
double	lgamma __P((double));
double	log1p __P((double));
double	logb __P((double));
double	rint __P((double));
double	scalb __P((double, int));
double	y0 __P((double));
double	y1 __P((double));
double	yn __P((int, double));
E 17
I 17
__pure	int	isinf __P((double));
__pure	int	isnan __P((double));
__pure	double	j0 __P((double));
__pure	double	j1 __P((double));
__pure	double	jn __P((int, double));
__pure	double	lgamma __P((double));
__pure	double	log1p __P((double));
__pure	double	logb __P((double));
__pure	double	rint __P((double));
__pure	double	scalb __P((double, int));
__pure	double	y0 __P((double));
__pure	double	y1 __P((double));
__pure	double	yn __P((int, double));
E 17
#endif

__END_DECLS
I 12

#endif /* _MATH_H_ */
E 12
E 10
E 9
E 7
E 1
