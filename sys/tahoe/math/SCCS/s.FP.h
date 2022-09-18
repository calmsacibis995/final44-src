h21876
s 00012/00002/00029
d D 7.1 90/12/06 13:49:34 bostic 2 1
c add Berkeley specific copyright notice
e
s 00031/00000/00000
d D 5.1 86/11/03 22:03:57 mckusick 1 0
c from CCI
e
u
U
t
T
I 1
D 2
/*
 *	%W% (Berkeley) %G%
E 2
I 2
/*-
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 2
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
E 2
 * General definitions of the floating point stuff on Power 6/32.
 * The floating point format definition is:
 *
 *		S    (exp-128)
 *	    (-1)  * 2	       * F
 *
 *	Where exp is the exponent field and F is the binary
 *	mantissa following it, including the hidden bit.
 *	The hidden bit actually is 1/2, so F is known to
 *	satisfy the range:
 *		1/2 <= F < 1
 */

typedef struct {
	unsigned	sign:1;
	unsigned	exponent:8;
	unsigned	mantissa:23;
} sp_format;

typedef struct {
	unsigned	sign:1;
	unsigned	exponent:8;
	unsigned	mantissa:23;
	unsigned	mantissa_lst;
} dp_format;

#define	EXP_BIAS	128		/* Exponent bias */
#define SIGN_BIT	0x80000000	/* S bit mask */
E 1
