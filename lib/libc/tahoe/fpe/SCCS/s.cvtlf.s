h30282
s 00002/00002/00073
d D 8.1 93/06/04 13:14:19 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00074
d D 1.3 90/06/01 14:47:53 bostic 3 2
c new copyright notice
e
s 00023/00003/00062
d D 1.2 89/02/17 17:35:31 bostic 2 1
c add Berkeley specific copyright notice
e
s 00065/00000/00000
d D 1.1 86/07/02 16:25:49 sam 1 0
c date and time created 86/07/02 16:25:49 by sam
e
u
U
t
T
I 1
D 2
#ifdef LIBC_SCCS
	.asciz	"%W% (Berkeley/CCI) %G%"
#endif LIBC_SCCS
E 2
I 2
/*
D 4
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */
E 2

#include <tahoemath/fp.h>
#include "DEFS.h"

XENTRY(cvtlf, R2|R3|R4|R5)
 #
 #Some initializations:
 #
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


	
E 1
