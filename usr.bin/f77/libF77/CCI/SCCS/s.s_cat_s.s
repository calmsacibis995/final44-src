h20368
s 00013/00001/00044
d D 5.2 91/04/12 15:16:04 bostic 2 1
c new copyright; att/bsd/shared
e
s 00045/00000/00000
d D 5.1 86/11/03 20:00:51 mckusick 1 0
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
.globl	_s_cat
.set	MASK__,0x1F04
.data
.text
_s_cat:.word	MASK__
movl	8(fp),r12		/* rpp */
movl	20(fp),r10		/* ll */
movl	12(fp),r9		/* pi = &rnp */
shll	$2,*16(fp),r1		/* *np * 4 */
addl3	r1,r9,r8		/* pn = &rnp + *np */
movl	4(fp),r1		/* lp */
jbr	L18			/* for */

L20:
movs3				/* copy nc chars from rp to lp */
addl2	$4,r12			/* rpp++ */
addl2	$4,r9			/* pi++ */

L18:
cmpl	r9,r8			/* pi < pn */
jgequ	L22			/* pn reached - out of loop */
movl	r10,r2			/* nc = ll */
cmpl	(r9),r2			/* if (*pi < nc) */
jgeq	L19
movl	(r9),r2			/* nc = *pi */

L19:
subl2	r2,r10			/* ll -= nc */
movl	(r12),r0		/* rp = *rpp */
jbr	L20

L2000005:			/* pad with spaces */
movb	$32,(r1)
incl	r1

L22:				/* while (--ll >= 0) */
decl	r10
jgeq	L2000005
ret#2

E 1
