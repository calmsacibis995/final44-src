h59018
s 00002/00002/00070
d D 8.1 93/06/04 17:04:10 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00068
d D 5.6 93/01/10 12:47:57 bostic 6 5
c exp__D, exp__E, log__D, and log__L are private; prepend leading "__"
e
s 00003/00000/00069
d D 5.5 92/12/02 15:28:32 bostic 5 4
c check in from Peter McIlroy; add exp__D, log__D, struct Double
e
s 00001/00006/00068
d D 5.4 91/03/05 09:54:54 bostic 4 3
c "const" handled by sys/cdefs.h
e
s 00000/00005/00074
d D 5.3 90/10/09 17:48:48 bostic 3 2
c new copyright notice
e
s 00001/00011/00078
d D 5.2 90/06/01 15:41:21 bostic 2 1
c new copyright notice
e
s 00089/00000/00000
d D 5.1 90/06/01 15:39:25 bostic 1 0
c date and time created 90/06/01 15:39:25 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
D 3
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
 *
E 3
 *	%W% (Berkeley) %G%
 */

I 4
#include <sys/cdefs.h>
E 4
#include <math.h>
D 4

#ifdef __STDC__
#define const const
#else
#define const /**/
#endif
E 4

#if defined(vax)||defined(tahoe)

/* Deal with different ways to concatenate in cpp */
#  ifdef __STDC__
#    define	cat3(a,b,c) a ## b ## c
#  else
#    define	cat3(a,b,c) a/**/b/**/c
#  endif

/* Deal with vax/tahoe byte order issues */
#  ifdef vax
#    define	cat3t(a,b,c) cat3(a,b,c)
#  else
#    define	cat3t(a,b,c) cat3(a,c,b)
#  endif

#  define vccast(name) (*(const double *)(cat3(name,,x)))

   /*
    * Define a constant to high precision on a Vax or Tahoe.
    *
    * Args are the name to define, the decimal floating point value,
    * four 16-bit chunks of the float value in hex
    * (because the vax and tahoe differ in float format!), the power
    * of 2 of the hex-float exponent, and the hex-float mantissa.
    * Most of these arguments are not used at compile time; they are
    * used in a post-check to make sure the constants were compiled
    * correctly.
    *
    * People who want to use the constant will have to do their own
    *     #define foo vccast(foo)
    * since CPP cannot do this for them from inside another macro (sigh).
    * We define "vccast" if this needs doing.
    */
#  define vc(name, value, x1,x2,x3,x4, bexp, xval) \
	const static long cat3(name,,x)[] = {cat3t(0x,x1,x2), cat3t(0x,x3,x4)};

#  define ic(name, value, bexp, xval) ;

#else	/* vax or tahoe */

   /* Hooray, we have an IEEE machine */
#  undef vccast
#  define vc(name, value, x1,x2,x3,x4, bexp, xval) ;

#  define ic(name, value, bexp, xval) \
	const static double name = value;

#endif	/* defined(vax)||defined(tahoe) */


/*
 * Functions internal to the math package, yet not static.
 */
D 6
extern double	exp__E();
extern double	log__L();
E 6
I 6
extern double	__exp__E();
extern double	__log__L();
E 6

I 5
struct Double {double a, b;};
D 6
double exp__D __P((double, double));
struct Double log__D __P((double));
E 6
I 6
double __exp__D __P((double, double));
struct Double __log__D __P((double));
E 6
E 5
E 1
