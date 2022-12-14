/* 
 **********************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 **********************************************************************
 */ 
 
/*
 * HISTORY
 * $Log:	urem.s,v $
 * Revision 2.1  89/08/03  17:03:39  rwd
 * Created.
 * 
 *  6-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added aurem from C library - the compiler sometimes generates
 *	code that calls it.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 11-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 * Modified to allow for preprocessing.
 */

/*
 *	@(#)urem.s	7.1 (Berkeley) 6/5/86
 *
 *	urem - unsigned remainder for vax-11
 *
 *	arguments: dividend, divisor
 *	result: remainder
 *	uses r0-r2
 *
 *	if 1 < divisor <= 2147483647, zero-extend the dividend
 *	to 64 bits and let ediv do the work.  If the divisor is 1,
 *	ediv will overflow if bit 31 of the dividend is on, so
 *	just return 0.  If the divisor is 0, do the ediv also,
 *	so it will generate the proper exception.  All other values
 *	of the divisor have bit 31 on: in this case the remainder
 *	must be the dividend if divisor > dividend, and the dividend
 *	minus the divisor otherwise.  The comparison must be unsigned.
 */
	.text
	.align	1
	.globl	urem
urem:	.word	0x0000
#ifdef GPROF
	jsb	mcount
#endif GPROF
	movl	4(ap),r0	# Dividend
	movl	8(ap),r2	# Divisor
	jeql	div		# If divisor=0, force exception
	cmpl	r2,$1		# If divisor <= 1 (signed),
	jleq	nodiv		#  no division is necessary
div:	clrl	r1		# Zero-extend the dividend
	ediv	r2,r0,r2,r0	# Divide.  q->r2 (discarded), r->r0
	ret
nodiv:	jneq	nzero		# If divisor=1, return 0
	clrl	r0		#  (because doing the divide will overflow
	ret			#  if the dividend has its high bit on)
nzero:	cmpl	r0,r2		# If dividend < divisor (unsigned)
	jlssu	retn		#  remainder is dividend
	subl2	r2,r0		#  else remainder is dividend - divisor
retn:	ret

/*
 * aurem - unsigned remainder for vax-11
 *
 * arguments: *dividend, divisor
 * result: remainder in r0 and *dividend
 * uses r0-r2
 */
	.text
	.align	1
	.globl	aurem
aurem:	.word	0x0000
#ifdef GPROF
	jsb	mcount
#endif GPROF
	movl	*4(ap),r0	/* dividend */
	movl	8(ap),r2	/* divisor */
	jeql	1f		/* if divisor=0, force exception */
	cmpl	r2,$1		/* if divisor <= 1 (signed), */
	jleq	2f		/*  no division is necessary */
1:
	clrl	r1		/* zero-extend the dividend */
	ediv	r2,r0,r2,r0	/* divide.  q->r2 (discarded), r->r0 */
	movl	r0,*4(ap)	/* save result */
	ret
2:
	jneq	1f		/* if divisor=1, return 0 */
	clrl	r0		/*  (because doing the divide will overflow */
	clrl	*4(ap)		/*  if the dividend has its high bit on) */
	ret	
1:
	cmpl	r0,r2		/* if dividend < divisor (unsigned) */
	jlssu	1f		/*  remainder is dividend */
	subl2	r2,r0		/*  else remainder is dividend - divisor */
1:
	movl	r0,*4(ap)	/* save result */
	ret

