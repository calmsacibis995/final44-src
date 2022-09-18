h32258
s 00011/00001/00059
d D 7.1 90/12/06 13:49:53 bostic 5 4
c add Berkeley specific copyright notice
e
s 00002/00002/00058
d D 1.4 90/12/04 22:51:20 bostic 4 3
c redo include files for kernel reorg
e
s 00003/00003/00057
d D 1.3 86/01/05 18:50:51 sam 3 2
c working (mostly)
e
s 00005/00006/00055
d D 1.2 86/01/03 23:46:51 sam 2 1
c massive cleanups; use SYS.h macros to allow profiling; moved to 
c tahoemath directory; revamp comments for cpp
e
s 00061/00000/00000
d D 1.1 85/07/31 21:33:41 sam 1 0
c date and time created 85/07/31 21:33:41 by sam
e
u
U
t
T
I 2
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*-
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 5
E 2
I 1

D 2
#include 	"fp.h"
#include 	"fp_in_krnl.h"
E 2
I 2
D 3
#include "fp.h"
#include "Kfp.h"
#include "SYS.h"
E 3
I 3
D 4
#include "../tahoemath/fp.h"
#include "../tahoemath/Kfp.h"
E 4
I 4
#include "../math/fp.h"
#include "../math/Kfp.h"
E 4
#include "../tahoe/SYS.h"
E 3
E 2

D 2

E 2
	.text
D 2
	.globl	Kfnorm		# Kfnorm(hfs)
Kfnorm:	.word	0x007c
E 2
I 2
ENTRY(Kfnorm, R6|R5|R4|R3|R2)
E 2
				# clrl	r1
	movl	r0,r4		# copy to temporary.
	jneq	inr0
	movl	r1,r5
	clrl	r3		# r3 - pos of m.s.b
inr1:	ffs	r5,r6
	incl	r6
	addl2	r6,r3
	shrl	r6,r5,r5
	jneq	inr1
	cmpl	$0,r3
	jeql	retzero
	jmp	cmpshift
inr0:	movl	$32,r3
inr00:	ffs	r4,r6
	incl	r6
	addl2	r6,r3
	shrl	r6,r4,r4
	jneq	inr00

cmpshift:
				# compute the shift (r4).
	subl3	r3,$HID_R0R1,r4
	jlss	shiftr		# if less then zero we shift right.
	shlq	r4,r0,r0	# else we shift left.
	subl2	r4,r2		# uodate exponent.
	jleq	underflow	# if less then 0 (biased) it is underflow.
	jmp	combine		# go to combine exponent and fraction.
shiftr:
	mnegl	r4,r4
	shrq	r4,r0,r0	# shift right.
	addl2	r4,r2		# update exponent
	cmpl	r2,$256
	jgeq	overflow	# check for overflow.
combine:
	andl2	$CLEARHID,r0	# clear the hidden bit.
	shal	$EXPSHIFT,r2,r2	# shift the exponent to its proper place.
	orl2	r2,r0
	ret

underflow:
	clrl	r0
	orl2	$HFS_UNDF,*4(fp)	
	ret

overflow:
	orl2	$HFS_OVF,*4(fp) 	
	ret
retzero:
	clrl	r0
	clrl	r1
	ret
D 2
	
E 2
E 1
