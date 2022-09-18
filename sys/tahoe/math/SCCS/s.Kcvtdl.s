h24933
s 00011/00001/00058
d D 7.1 90/12/06 13:49:43 bostic 5 4
c add Berkeley specific copyright notice
e
s 00002/00002/00057
d D 1.4 90/12/04 22:51:12 bostic 4 3
c redo include files for kernel reorg
e
s 00003/00003/00056
d D 1.3 86/01/05 18:50:42 sam 3 2
c working (mostly)
e
s 00007/00003/00052
d D 1.2 86/01/03 23:46:40 sam 2 1
c massive cleanups; use SYS.h macros to allow profiling; moved to 
c tahoemath directory; revamp comments for cpp
e
s 00055/00000/00000
d D 1.1 85/08/02 15:31:17 sam 1 0
c date and time created 85/08/02 15:31:17 by sam
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
#include	"fp.h"
#include	"fp_in_krnl.h"
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
 
	.text
	.globl	_Kcvtdl
	.globl	_Kcvtdu
_Kcvtdu:
D 2
_Kcvtdl:	.word	0x003c		# we use r2,r3,r4,r5
E 2
I 2
_Kcvtdl:
	.word	R5|R4|R3|R2
E 2

 #
 #Some initializations:
 #
	clrl	r3		# r3 - negative flag.
	movl	4(fp),r0	# fetch operand.
	movl	8(fp),r1	
 #
 #get exponent
 #
	andl3	$EXPMASK,r0,r2	# r2 will hold the exponent.
	jeql	retzero	
	cmpl	$TWO_EXP,r2	# if exponent is less then -2,return zero.
	jgtr	retzero
	andl2	$0!EXPSIGN,r2	# turn off biased exponent sign
	shrl	$EXPSHIFT,r2,r2
 #
 #get fraction
 #
	bbc	$31,r0,positive	# if negative remember it.
	incl	r3
positive:
				# clear the non fraction parts.
	andl2	$(0!(EXPMASK | SIGNBIT)),r0
				# add the hidden bit.
	orl2	$(0!CLEARHID),r0
	subl2	$24,r2		# compute the shift.
	jgtr	shift_left
	mnegl	r2,r2
	shrl	r2,r0,r0	# shift right.
	jmp	shifted
shift_left:
	cmpl	r2,$7
	jgtr	overflow
go_on:	shlq	r2,r0,r0	# shift right.
shifted:
	bbc	$0,r3,done	# check for negative
	mnegl	r0,r0
done:	
	ret

retzero:
	clrl	r0
	ret
overflow:
	ret
E 1
