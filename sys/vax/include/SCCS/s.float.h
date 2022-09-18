h39015
s 00001/00011/00040
d D 7.2 90/06/28 22:32:16 bostic 2 1
c new copyright notice
e
s 00051/00000/00000
d D 7.1 89/08/15 11:53:45 bostic 1 0
c date and time created 89/08/15 11:53:45 by bostic
c No VAX G_floating support was included in the "float.h" I just sent you.
c All constants rely heavily upon a correctly-rounded decimal-binary
c conversion routine; at least the following 6 constants *must* be converted
c exactly to what the comments say they ought to be:
c 
c #define FLT_EPSILON	1.19209290E-07F			/* 2^-23 */
c #define FLT_MIN		2.93873588E-39F			/* 2^-128 */
c #define FLT_MAX		1.70141173E+38F			/* (1-2^-24)*2^127 */
c #define DBL_EPSILON	2.775557561562891351E-17	/* 2^-55 */
c #define DBL_MIN		2.938735877055718770E-39	/* 2^-128 */
c #define DBL_MAX		1.701411834604692294E+38	/* (1-2^-56)*2^127 */
c 
c DBL_MAX/FLT_MAX may generate spurious floating-point overflows if your
c decimal-binary conversion routine is deficient; likewise DBL_MIN/FLT_MIN
c may underflow inadvertently to zero after conversion.
c 
c The constants of type float rely on the ANSI-invented suffix of "F" to
c precisely specify their type.
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

#define FLT_RADIX	2		/* b */
#define FLT_ROUNDS	1		/* FP addition rounds to nearest */

#define FLT_MANT_DIG	24		/* p */
#define FLT_EPSILON	1.19209290E-07F	/* b**(1-p) */
#define FLT_DIG		6		/* floor((p-1)*log10(b))+(b == 10) */
#define FLT_MIN_EXP	-127		/* emin */
#define FLT_MIN		2.93873588E-39F	/* b**(emin-1) */
#define FLT_MIN_10_EXP	-38		/* ceil(log10(b**(emin-1))) */
#define FLT_MAX_EXP	127		/* emax */
#define FLT_MAX		1.70141173E+38F	/* (1-b**(-p))*b**emax */
#define FLT_MAX_10_EXP	38		/* floor(log10((1-b**(-p))*b**emax)) */

#define DBL_MANT_DIG	56
#define DBL_EPSILON	2.775557561562891351E-17
#define DBL_DIG		16
#define DBL_MIN_EXP	-127
#define DBL_MIN		2.938735877055718770E-39
#define DBL_MIN_10_EXP	-38
#define DBL_MAX_EXP	127
#define DBL_MAX		1.701411834604692294E+38
#define DBL_MAX_10_EXP	38

#define LDBL_MANT_DIG	DBL_MANT_DIG
#define LDBL_EPSILON	DBL_EPSILON
#define LDBL_DIG	DBL_DIG
#define LDBL_MIN_EXP	DBL_MIN_EXP
#define LDBL_MIN	DBL_MIN
#define LDBL_MIN_10_EXP	DBL_MIN_10_EXP
#define LDBL_MAX_EXP	DBL_MAX_EXP
#define LDBL_MAX	DBL_MAX
#define LDBL_MAX_10_EXP	DBL_MAX_10_EXP
E 1
