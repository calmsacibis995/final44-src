h42005
s 00024/00000/00000
d D 5.1 90/05/17 21:14:20 bostic 1 0
c date and time created 90/05/17 21:14:20 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* exp(x) */

	.text
	.globl	_exp

_exp:
	fetoxd	sp@(4),fp0
	fmoved	fp0,sp@-
	movel	sp@+,d0
	movel	sp@+,d1
	rts
E 1
