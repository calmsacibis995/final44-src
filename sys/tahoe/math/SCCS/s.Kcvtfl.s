h41311
s 00011/00001/00057
d D 7.1 90/12/06 13:49:45 bostic 5 4
c add Berkeley specific copyright notice
e
s 00001/00001/00057
d D 1.4 90/12/04 22:51:13 bostic 4 3
c redo include files for kernel reorg
e
s 00002/00002/00056
d D 1.3 86/01/05 18:50:43 sam 3 2
c working (mostly)
e
s 00005/00010/00053
d D 1.2 86/01/03 23:46:42 sam 2 1
c massive cleanups; use SYS.h macros to allow profiling; moved to 
c tahoemath directory; revamp comments for cpp
e
s 00063/00000/00000
d D 1.1 85/08/02 15:42:23 sam 1 0
c date and time created 85/08/02 15:42:23 by sam
e
u
U
t
T
I 1
D 2
#include	"fp.h"
E 2
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

D 2
	.text
	.globl	_Kcvtfl
_Kcvtfl:	.word	0x003c		# we use r2,r3,r4,r5
E 2
I 2
D 3
#include "fp.h"
#include "SYS.h"
E 3
I 3
D 4
#include "../tahoemath/fp.h"
E 4
I 4
#include "../math/fp.h"
E 4
#include "../tahoe/SYS.h"
E 3
E 2

D 2
 #
 #Some initializations:
 #
E 2
I 2
	.text
ENTRY(Kcvtfl, R5|R4|R3|R2)
E 2
	clrl	r1
	clrl	r4		# r4 - negative flag.
	clrl	r2		# r2 - exponent.
	movl	4(fp),r0	# fetch operand.
	movl	r0,r5		# need another copy.
	jeql	retzero		# return zero.
	jgtr	positive
	mnegl	r0,r0
	jvs	retmin		# return minimum integer.
	incl	r4		# remember it was negative.
	movl	r0,r5		# remember the negated value.
 #
 #Compute exponent:
 #
positive:
	ffs	r0,r1
	incl 	r1
	addl2	r1,r2
	shrl	r1,r0,r0
	jneq	positive	# look for more set bits.
 #
 #we have the exponent in r2.
 #
	movl	r5,r0		# r0 will hold the resulting f.p. number.
 #
 #Shift the fraction part to its proper place:
 #
	subl3	r2,$HID_POS,r3
	jlss	shiftr		# if less then zero we have to shift right.
	shll	r3,r0,r0	# else we shift left.
	jmp	shifted
shiftr:
	mnegl	r3,r3
	shrl	r3,r0,r0
shifted:
	andl2	$CLEARHID,r0	# clear the hidden bit.
	shal	$EXPSHIFT,r2,r2	# shift the exponent to its proper place.
	orl2	$EXPSIGN,r2	# set the exponent sign bit(to bias it).
	orl2	r2,r0		# combine exponent & fraction.
	bbc	$0,r4,sign_ok	# do we  have to set the sign bit?
	orl2	$SIGNBIT,r0	# yes...
sign_ok:
	ret

retzero:
	clrl 	r0
	ret

retmin:
 	movl	$0xd0000000,r0
	ret
D 2


	
E 2
E 1
