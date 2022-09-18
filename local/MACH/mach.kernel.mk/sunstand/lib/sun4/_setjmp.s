/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	_setjmp.s,v $
 * Revision 2.2  89/07/12  00:24:08  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 *	.seg	"data"
 *	.asciz	"@(#)_setjmp.s 1.2 88/02/08"
 *	Copyright (c) 1986 by Sun Microsystems, Inc.
 */
 	.seg	"text"
 	.align	4

#include <machine/asm_linkage.h>

/*
 * _setjmp(buf_ptr)
 * buf_ptr points to a five word array (jmp_buf). In the first is our
 * return address, the second, is the callers SP.
 * The rest is cleared by _setjmp
 *
 *		+----------------+
 *   %i0->	|      pc        |
 *		+----------------+
 *		|      sp        |
 *		+----------------+
 *		|    sigmask     |
 *		+----------------+
 *		|   stagstack    |
 *		|   structure    |
 *		+----------------+
 *
 */

	PCVAL	=	0	! offsets in buf structure
	SPVAL	=	4
	SIGMASK	=	8
	SIGSTACK =	12

	SS_SP	   =	0	! offset in sigstack structure
	SS_ONSTACK =	4

	ENTRY(_setjmp)
	st	%o7, [%o0 + PCVAL] 	! return pc
	st	%sp, [%o0 + SPVAL] 	! save caller's sp
	clr	[%o0 + SIGMASK]		! clear the remainder of the jmp_buf
	clr	[%o0 + SIGSTACK + SS_SP]
	clr	[%o0 + SIGSTACK + SS_ONSTACK]
	retl
	clr	%o0

/*
 * _longjmp(buf_ptr, val)
 * buf_ptr points to an array which has been initialized by _setjmp.
 * val is the value we wish to return to _setjmp's caller
 *
 * We will flush our registers by doing 6 save instructions. This could be
 * better done as a kernel call. This is necessary to ensure that the
 * registers we want to pick up are stored in the stack. Then, we set fp
 * from the saved fp and make ourselves a stack frame.
 */
	ENTRY(_longjmp)
	save	%sp, -WINDOWSIZE, %sp
	!
	! flush all register windows to the stack.
	! 
	save	%sp, -WINDOWSIZE, %sp	! establish junk save area
	save	%sp, 0, %sp
	save	%sp, 0, %sp
	save	%sp, 0, %sp
	save	%sp, 0, %sp
	restore				! get back to original window
	restore
	restore
	restore
	restore

	ld	[%i0 + SPVAL], %fp	! build new stack frame
	sub	%fp, MINFRAME, %sp	! establish new save area
	ld	[%i0 + PCVAL], %i7	! get new return pc
	ret
	restore	%i1, 0, %o0		! return (val)
