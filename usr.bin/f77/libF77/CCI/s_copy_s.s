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
	.asciz "@(#)s_copy_s.s	5.2 (Berkeley) 4/12/91"
#endif /* not lint */

.data
.text
LL0:.align	1
.globl	_s_copy
.set	MASK__,0x1004		/* save r2, r12 */
.data
.text
_s_copy:.word	MASK__
movl	4(fp),r1		/* dest addr */
movl	8(fp),r0		/* src addr */
movl	12(fp),r12		/* dest length */
cmpl	r12,16(fp)		/* if (ldest <= lsrc) */
jgtr	L16
movl	r12, r2			/* copy according to ldest */
movs3
ret
L16: 				/* else */
movl	16(fp),r2		/* copy according to lsrc */
movs3
addl2	4(fp),r12		/* and pad with spaces */
L20:movb	$32,(r1)
incl	r1
cmpl	r1,r12
jlssu	L20
ret

