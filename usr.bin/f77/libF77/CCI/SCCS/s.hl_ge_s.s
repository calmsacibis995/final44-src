h23254
s 00013/00001/00041
d D 5.2 91/04/12 15:15:53 bostic 2 1
c new copyright; att/bsd/shared
e
s 00042/00000/00000
d D 5.1 86/11/03 20:00:36 mckusick 1 0
c from CCI
e
u
U
t
T
I 1
D 2
#	"%W% (Berkeley) %G%"
E 2
I 2
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.proprietary.c%
 */

#ifndef lint
	.asciz "%W% (Berkeley) %G%"
#endif /* not lint */
E 2

.data
.text
LL0:.align	1
.globl	_hl_ge
.set	MASK__, 0x4
.data
.text
_hl_ge:.word	MASK__
	movl	4(fp),r0		/* a */
	movl	8(fp),r1		/* b */
	cmpl	12(fp),16(fp)		/* if (la <= lb) */
	jgtr	LB
	movl	12(fp), r2		/* compare according to la */
	cmps3
	jlss	out0			/* if less return(0) */
	jgtr	out1			/* if greater return(1) */

	cmpl	12(fp),16(fp)		/* if (la == lb) */
	jeql	out1			/* then equal */

	addl3	8(fp), 16(fp), r2	/* bend */
LOOP1:
	cmpb	(r1), $32		/* if *b != space */
	jneq	out0			/* then astring < bstring */
	incl	r1			/* else continue */
	cmpl	r1, r2			/* till bend */
	jlssu	LOOP1
	jbr	out1

LB:					/* else */
	movl	16(fp), r2		/* compare according to lb */
	cmps3
	jlss	out0			/* if less return(0) */

out1:
	movl	$1, r0
	ret
out0:
	clrl	r0
	ret
E 1
