h37479
s 00011/00001/00061
d D 7.1 90/12/06 13:50:01 bostic 5 4
c add Berkeley specific copyright notice
e
s 00002/00002/00060
d D 1.4 90/12/04 22:51:26 bostic 4 3
c redo include files for kernel reorg
e
s 00003/00004/00059
d D 1.3 86/01/05 18:50:57 sam 3 2
c working (mostly)
e
s 00029/00039/00034
d D 1.2 86/01/03 23:46:59 sam 2 1
c massive cleanups; use SYS.h macros to allow profiling; moved to 
c tahoemath directory; revamp comments for cpp
e
s 00073/00000/00000
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

I 2
D 3
#include "SYS.h"
E 3
I 3
#include "../tahoe/SYS.h"
D 4
#include "../tahoemath/fp.h"
#include "../tahoemath/Kfp.h"
E 4
I 4
#include "../math/fp.h"
#include "../math/Kfp.h"
E 4
E 3

E 2
/* @(*)Kldexpf.s	4.2 (Berkeley) 12/21/80
D 2
*	Tahoe 		2/2/83
*
*	float Kldexpf (op_most, op_least, exp, hfs)
*
*	Ldexp returns value*2**exp, if that result is in range.
*	If underflow occurs, it returns zero.  If overflow occurs,
*	it returns a value of appropriate sign and largest
*	possible magnitude.  In case of either overflow or underflow,
*	the external int "errno" is set to ERANGE.  Note that errno is
*	not modified if no error occurs, so if you intend to test it
*	after you use Kldexpf, you had better set it to something
*	other than ERANGE first (zero is a reasonable value to use).
*
*	Constants
*/
E 2
I 2
 *	Tahoe 		2/2/83
 *
 * float Kldexpf (op_most, op_least, exp, hfs)
 *
 * Ldexp returns value*2**exp, if that result is in range.
 * If underflow occurs, it returns zero.  If overflow occurs,
 * it returns a value of appropriate sign and largest
 * possible magnitude.  In case of either overflow or underflow,
 * the external int "errno" is set to ERANGE.  Note that errno is
 * not modified if no error occurs, so if you intend to test it
 * after you use Kldexpf, you had better set it to something
 * other than ERANGE first (zero is a reasonable value to use).
 */
E 2
D 3

D 2
#include "../machine/fp_in_krnl.h"
E 2
I 2
#include "fp.h"
#include "Kfp.h"
E 3
E 2

D 2
/* 	Constants to be in a flt.h file . (?) */

	.set		EXPMASK,	0x7f800000
	.set		SIGNBIT,	0x80000000
	.set		EXPSHIFT,	23
	.data

huge0:	.word	0x7fff		/* The largest number that can */
	.word	0xffff		/*   be represented in a long floating */
huge1:	.word	0xffff		/* The largest number that can */
	.word	0xffff		/*   be represented in a long floating */
/*
*	Entry point
*/
E 2
	.text
D 2
	.globl	_Kldexpf
_Kldexpf:	.word	0x0004		/* We use r2  */

E 2
I 2
ENTRY(Kldexpf, R2)
E 2
	movl	4(fp),r0	/* Fetch "value" */
	movl	8(fp),r1

	andl3	$EXPMASK,r0,r2	/* r2 := shifted biased exponent */
	jeql	ld1		/* If it's zero, we're done */
	shar	$EXPSHIFT,r2,r2	/* shift to get value of exponent  */

	addl2	12(fp),r2	/* r2 := new biased exponent */
	jleq	under		/* if it's <= 0, we have an underflow */
	cmpl	r2,$256		/* Otherwise check if it's too big */
	jgeq	over		/* jump if overflow */
/*
D 2
*	Construct the result and return
*/
E 2
I 2
 *	Construct the result and return
 */
E 2
	andl2	$0!EXPMASK,r0	/* clear old exponent */
	shal 	$EXPSHIFT,r2,r2	/* Put the exponent back in the result */
	orl2	r2,r0
ld1:	ret
/*
D 2
*	Underflow
*/
E 2
I 2
 *	Underflow
 */
E 2
under:	clrl	r0		/* Result is zero */
	clrl	r1
	orl2	$HFS_UNDF,*16(fp)
	jmp	err		/* Join general error code */
/*
D 2
*	Overflow
*/
E 2
I 2
 *	Overflow
 */
E 2
over:	movl	huge0,r0	/* Largest possible floating magnitude */
	movl	huge1,r1
	orl2	$HFS_OVF,*16(fp)
	orl2	$SIGNBIT,r0	/* If arg < 0, make result negative */

err:	orl2	$HFS_RANGE,*16(fp)	/* Indicate range error */
	ret
I 2

	.data
huge0:	.long	0x7fffffff
huge1:	.long	0xffffffff
E 2
E 1
