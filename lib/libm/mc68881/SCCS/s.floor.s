h50700
s 00002/00002/00050
d D 8.1 93/06/04 17:01:11 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00052/00000/00000
d D 5.1 90/05/17 21:14:23 bostic 1 0
c date and time created 90/05/17 21:14:23 by bostic
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

	.text
	.globl	_floor,_ceil,_rint

| floor(x)
| the largest integer no larger than x
_floor:
	fmovel	fpcr,d0		| save old FPCR
	fmoved	sp@(4),fp0	| get argument
	fbun	Lret		| if NaN, return NaN
	fboge	Lrtz		| >=0, round to zero
	fmovel	#0x20,fpcr	| <0, round to -inf
	jra	Ldoit

| ceil(x)
| -floor(-x), for all real x
_ceil:
	fmovel	fpcr,d0		| save old FPCR
	fmoved	sp@(4),fp0	| get argument
	fbun	Lret		| if NaN, return NaN
	fbolt	Lrtz		| <0, round to zero
	fmovel	#0x30,fpcr	| >=0, round to inf
	jra	Ldoit

Lrtz:
	fmovel	#0x10,fpcr
Ldoit:
	fintd	sp@(4),fp0	| truncate
	fmovel	d0,fpcr		| restore old FPCR
Lret:
	fmoved	fp0,sp@-
	movel	sp@+,d0
	movel	sp@+,d1
	rts

| rint(x)
| delivers integer nearest x in direction of prevailing rounding mode
_rint:
	fintd	sp@(4),fp0	| use prevailing rounding mode
	jra	Lret
E 1
