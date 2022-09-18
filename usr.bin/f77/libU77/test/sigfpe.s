/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
	.asciz "@(#)sigfpe.s	5.2 (Berkeley) 4/12/91"
#endif /* not lint */

	.data
	.even
L16:
	0.;8.
	.even
L17:
	-1.;-1.
	.data
	.bss
~~sigfpe_ = _sigfpe_
~~:
	.data
	.globl	_sigfpe_
	.globl	_signal_
	.even
.text
jbr	L11
L14:mov	$L17,(sp)
mov	r5,-(sp)
mov	$L16,-(sp)
jsr	pc,*$_signal_
cmp	(sp)+,(sp)+
jbr	L13
L13:L12:jmp	cret
L11:_sigfpe_:
~~sigfpe_:
jsr	r5,csv
mov	r5,r4
add	$4,r4
jbr	L14
.globl
.data
