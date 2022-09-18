h24048
s 00002/00002/00034
d D 8.1 93/06/04 15:39:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 5.1 90/04/23 19:57:04 william 1 0
c date and time created 90/04/23 19:57:04 by william
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Sean Eric Fagan.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
 * ldexp(value, exp): return value * (2 ** exp).
 *
 * Written by Sean Eric Fagan (sef@kithrup.COM)
 * Sun Mar 11 20:27:09 PST 1990
 */

/*
 * We do the conversion in C to let gcc optimize it away, if possible.
 * The "fxch ; fstp" stuff is because value is still on the stack
 * (stupid 8087!).
 */
double
ldexp (double value, int exp)
{
	double temp, texp, temp2;
	texp = exp;
	asm ("fscale ; fxch %%st(1) ; fstp%L1 %1 "
		: "=f" (temp), "=0" (temp2)
		: "0" (texp), "f" (value));
	return (temp);
}
E 1
