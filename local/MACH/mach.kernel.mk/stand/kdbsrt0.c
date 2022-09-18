/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 **********************************************************************
 * HISTORY
 * $Log:	kdbsrt0.c,v $
 * Revision 2.3  89/03/09  21:15:39  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  14:32:58  gm0w
 * 	Changes for cleanup.
 * 
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created.
 *	[ V5.1(F8) ]
 *
 **********************************************************************
 */

#include <machine/mtpr.h>


	.globl	start

/*
 *  The first portion of this code must be position independent so that it can
 *  be loaded anywhere before relocating itself to RELOC.  The code does
 *  assume, however, that it will be loaded somewhere well below RELOC.
 *
 *  Return with all registers and processor state preserved except with
 *  the SCB set for fault control by the debugger. 
 */

	/*
	 *  On initial entry, branch to the relocation code.  This code will
	 *  eventually comment out this branch to prevent recursive attempts to
	 *  relocate and so subsequent restarts will branch directly to the re-
	 *  initialization code instead.  We use a word of NOP's rather than an
	 *  empty mask to also permit branching directly here as well as a
	 *  procedure call (which has the benign side effect of saving R0 and
	 *  R8 for a call).
	
	 */
start:	nop; nop 
	brb	reloc
	brw	reinit

	/*
	 *  Save the current stack pointer and IPL and set the relocation
	 *  stack.  Go to high IPL (just in case).
 	 *
	 *  Save R0-R5 since they will be destroyed by the relocation
	 *  process.
	 */
reloc:	movl	sp,*$RELOC-4
	movl	$RELOC-4,sp
	mfpr	$IPL,-(sp)
	mtpr	$31,$IPL

	pushr	$0x3f

	/*
	 *  Relocate the text and data segments (with 6 saved registers and the
	 *  old stack pointer and IPL on the new stack below the relocation
	 *  area).
	 */
	movab	_edata,r0
	movab	start,r1
	subl2	r1,r0
	movc3	r0,start,8*4(sp)

	/*
	 *  Clear bss segment.
	 */
bclr:	clrl	(r3)+
	cmpl	r3,$_end
	jlss	bclr

	/*
	 *  Restore the saved R0-R5.
	 *
	 *  Transfer to the relocated code.
	 */
	popr	$0x3f

	pushl	$init
	jmp	*(sp)+

	/*
	 *  Manually adjust the register save masks for the initialization,
	 *  entry and fault routines to always save R0-R11 on each call.
	 *
	 *  Comment out the initial relocation entry point to prevent
	 *  recursive relocation attempts.
	 */
init:	bisw2	$0xfff,_kdb_init
	bisw2	$0xfff,_kdb_entry
	bisw2	$0xfff,_kdb_fault

	movw	start,start+2

	/*
	 *  Pass the relocation address to the initialization routine.
	 *
	 *  Process the entry procedure call parameters (e.g. to set the
	 *  indirect transfer address for return to the debugger on the next
	 *  program load).  Only do this, however, when we know that we
	 *  were called from an updated bootstrap program (at least 6
	 *  arguments).
	 *
	 *  Restore the saved IPL and stack pointer and return to our caller.
	 */
	pushl	$RELOC
	calls	$1,_kdb_init

	cmpl	(ap),$6
	blss	skip
	callg	(ap),_kdb_entry

skip:	mtpr	(sp)+,$IPL
exit:	movl	(sp)+,sp
	ret


	/*
	 *  Subsequent restarts of the debugger after relocating transfer here.
	 *  Save the stack pointer, and setup the debugger stack.
	 *
	 *  Invoke the initialization routine with a 0 parameter to distinguish
	 *  the restart case and arrange to trap immediately to the debugger
	 *  thereafter.  Explicit debugger action will be needed to advance
	 *  beyond the breakpoint which will normally be appropriate since on
	 *  restart we probably were not invoked with a procedure call and
	 *  shouldn't attempt to return from one by default.
	 */
reinit:	movl	sp,*$RELOC-4
	movl	$RELOC-4,sp

	pushl	$0
	calls	$1,_kdb_init
	bpt
	brb	exit



/*
 *  psl - get Processor Status Longword
 *
 */
	.globl	_psl

_psl:	.word	0
	movpsl	r0
	ret


/*
/*
 *  mfpr - move from priviliged register instruction
 *
 *  4(ap) = privileged register identifier
 */
	.globl	_mfpr

_mfpr:	.word	0
	mfpr	4(ap),r0
	ret


/*
 *  mtpr - move to priviliged register instruction
 *
 *  4(ap) = privileged register identifier
 *  8(ap) = new contents
 */
	.globl	_mtpr

_mtpr:	.word	0
	mtpr	8(ap),4(ap)
	ret



/*
 *  System Control Block
 */


	/*
	 *  Align the SCB on a page boundary.
	 */
0:	.set	size,0b-start
	.space	512-size



	/*
	 *  Initialize the SCB vectors.
	 */

#define V_(vec)	\
_kdb_V/**/vec:	.long	T_/**/vec

	.globl	_scb

_scb:	V_(00)	/* 00 */
	V_(04)	/* 04 = Machine Check			(var) */
	V_(08)	/* 08 = Kernel Stack Not Valid		(0) */
	V_(0C)	/* 0C = Power Fail			(0) */
	V_(10)	/* 10 = Reserved/Privileged Instruction	(0) */
	V_(14)	/* 14 = Customer Reserved Instruction	(0) */
	V_(18)	/* 18 = Reserved Operand		(0) */
	V_(1C)	/* 1C = Reserved Addressing Mode	(0) */
	V_(20)	/* 20 = Access Control Violation 	(2) */
	V_(24)	/* 24 = Translation Not Valid	 	(2) */
	V_(28)	/* 28 = Trace Pending			(0) */
	V_(2C)	/* 2C = Breakpoint Instruction		(0) */
	V_(30)	/* 30 = Compatibility 			(1) */
	V_(34)	/* 34 = Arithmetic 			(1) */
	V_(38)	/* 38 */
	V_(3C)	/* 3C */
	V_(40)	/* 40 = CHMK	 			(1) */
	V_(44)	/* 44 = CHME	 			(1) */
	V_(48)	/* 48 = CHMS	 			(1) */
	V_(4C)	/* 4C = CHMU	 			(1) */

	.space	512-0x50


/*
 *  Transfer vectors for exceptions through the SCB.
 *
 *  TP_ expands to push the length of the parameters and fault type on the
 *  stack.  T_ expands to push only the fault type (with the length of the
 *  parameters already on the stack, e.g. as on machine check).
 */

#define TP_(vec, params)	\
	.align 2 \
T_/**/vec: \
	pushl $(params*4); \
	pushl $(0x/**/vec>>2);	\
	brw	common

#define T_(vec)	\
	.align 2 \
T_/**/vec: \
	pushl $(0x/**/vec>>2);	\
	brw	common

	TP_(00, 0); T_ (04);    TP_(08, 0); TP_(0C, 0)
	TP_(10, 0); TP_(14, 0); TP_(18, 0); TP_(1C, 0)
	TP_(20, 2); TP_(24, 2); TP_(28, 0); TP_(2C, 0)
	TP_(30, 1); TP_(34, 1); TP_(38, 0); TP_(3C, 0)
	TP_(40, 1); TP_(44, 1); TP_(48, 1); TP_(4C, 1)


	/*
	 *  Common fault handling:
	 *
	 *  Pass the type and parameters to the handler.  Upon return, pop the
	 *  parameters from the stack (including the length word but not the
	 *  type which is removed by the calls) and return from the exception.
	 */
common: calls	$1,_kdb_fault
	addl2	(sp),sp
	tstl	(sp)+
	rei
