h58608
s 00002/00002/00022
d D 8.1 93/06/04 17:00:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00000/00000
d D 5.1 90/05/17 21:14:16 bostic 1 0
c date and time created 90/05/17 21:14:16 by bostic
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* atan(x) */

	.text
	.globl	_atan

_atan:
	fatand	sp@(4),fp0
	fmoved	fp0,sp@-
	movel	sp@+,d0
	movel	sp@+,d1
	rts
E 1
