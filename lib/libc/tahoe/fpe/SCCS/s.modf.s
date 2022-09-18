h07270
s 00002/00002/00144
d D 8.1 93/06/04 13:14:56 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00145
d D 1.3 90/06/01 14:48:41 bostic 3 2
c new copyright notice
e
s 00023/00003/00133
d D 1.2 89/02/17 17:35:40 bostic 2 1
c add Berkeley specific copyright notice
e
s 00136/00000/00000
d D 1.1 86/07/02 16:25:53 sam 1 0
c date and time created 86/07/02 16:25:53 by sam
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

/* 
 *  double modf (value, iptr)
 *  double value, *iptr;
 * 
 *  Modf returns the fractional part of "value",
 *  and stores the integer part indirectly through "iptr".
 */ 
#include <tahoemath/fp.h>
#include "DEFS.h"
 
ENTRY(modf, R2|R3|R4|R5)
 /*
 * Some initializations:
 */
	ldd	4(fp)		/* load accumulator, for converison	*/
	cvdl	r2		/*  to an integer.			*/
	bvs	gsb		/* iff too big grunt it out		*/
	cvld	r2		/* float the integer part		*/
	std	r2
	ldd	4(fp)		/* isolate the fraction			*/
	subd	r2
	std	r0
	movl	12(fp),r6	/* get int return address */
	movl	r2,(r6)
	movl	r3,4(r6)
	ret
gsb:	clrl	r3
	movl	4(fp),r0	/* fetch operand to r0,r1. */
	movl	8(fp),r1	
	movl	12(fp),r6	/* fetch addr of int to r6. */
 /*
 * get exponent
 */
	andl3	$EXPMASK,r0,r2	/* r2 will hold the exponent. */
	jeql	is_reserved	/* check for reserved operand.  */
	shrl	$EXPSHIFT,r2,r2
	subl2	$BIAS,r2	/* unbias it.  */
	jleq	allfrac		/* it's int part is  zero. */
	cmpl	r2,$56
	jgeq	allint		/* it's fraction part is zero. */
 /*
 * get fraction
 */
	movl	r0,r4		/* remember the original number. */
	movl	r1,r5
	bbc	$31,r0,positive	/* if negative remember it. */
	incl	r3
positive:
				/* clear the non fraction parts. */
	andl2	$(0!(EXPMASK | SIGNBIT)),r0
				/* add the hidden bit. */
	orl2	$(0!CLEARHID),r0

	cmpl	r2,$HID_POS	/* see if there are bits to clear only in r0 */
				/* or r1 has to be taken care of. */
				/* ( for fraction calculation) */

	jgtr	in_r1		/* some bytes in r1. */

	jeql	onlyallr0	/* all r0 must be cleared,r1 unchanged. */

				/* only r0 must be canged. */
	mnegl	r2,r7		/* r7 - loop counter. */
	movl	$CLEARHID,r8	/* first bit to clear. */
1:
	andl2	r8,r0		/* clear int. bits from fraction part. */
	shar	$1,r8,r8
	aoblss	$0,r7,1b
1:
	andl2	r8,r4		/* clear frac bits for int calculation: */
	shar	$1,r8,r8
	cmpl	$0xffffffff,r8
	jneq	1b
	clrl	r5
	jmp	norm

onlyallr0:
	clrl	r0
	clrl	r5
	jmp 	norm

in_r1:
	clrl	r0		/* clear int part for frac. calculation. */
	subl3	r2,$HID_POS,r7
	movl	$0x7fffffff,r8
1:
	andl2	r8,r1
	shar	$1,r8,r8
	orl2	$0x80000000,r8		/* force the 'sign' bit to be on. */
	aoblss	$0,r7,1b
1:
	andl2	r8,r5
	shar	$1,r8,r8
	cmpl	$0xffffffff,r8
	jneq	1b

norm:
	addl2	$BIAS,r2	/* fnorm expects it biased. */
	callf	$4,fnorm	/* normelize fraction part. */
	cmpl	$0,r0
	jeql	1f
	bbc	$0,r3,1f
	orl2	$0x80000000,r0
1:
	movl	r4,(r6)		/* put int part in place. */
	movl	r5,4(r6)
	ret
 
allint:
	movl	r0,(r6)		/* copy the argument to the int addr. */
	movl	r1,4(r6)
	clrl	r0		/* clear the fraction part. */
	clrl	r1
	ret

allfrac:
				/* the fraction is ready in r0,r1. */
	clrl	(r6)		/* zero the int part. */
	clrl	4(r6)
	ret

ret_zero:
	clrl	(r6)
	clrl	4(r6)
	clrl	r0
	clrl	r1
	ret

is_reserved:
	bbc	$31,r0,ret_zero
	callf 	$4,fpresop
	ret
E 1
