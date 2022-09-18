/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
	.asciz "@(#)l_gt_s.s	5.2 (Berkeley) 4/12/91"
#endif /* not lint */

.data
.text
LL0:.align	1
.globl	_l_gt
.set	MASK__,0x4
.data
.text
_l_gt:.word	MASK__
	movl	4(fp),r0		/* a */
	movl	8(fp),r1		/* b */
	cmpl	12(fp),16(fp)		/* if (la <= lb) */
	jgtr	LB
	movl	12(fp), r2		/* compare according to la */
	cmps3
	jleq	out0			/* if less or equal return(0) */
	jbr	out1			/* else greater: return(1) */

LB:					/* else */
	movl	16(fp), r2		/* compare according to lb */
	cmps3
	jlss	out0			/* if less return(0) */
	jgtr	out1			/* if greater return(1) */

	addl3	4(fp), 12(fp), r2	/* aend */
LOOP2:
	cmpb	(r0), $32		/* if *a != space */
	jneq	out1			/* then astring > bstring */
	incl	r0			/* else continue */
	cmpl	r0, r2			/* till aend */
	jlssu	LOOP2
out0:
	clrl	r0
	ret
out1:
	movl	$1, r0			/* else return(1) */
	ret
