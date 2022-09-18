/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	misc.s,v $
 * Revision 2.2  89/07/12  00:24:45  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 *	.seg	"data"
 *	.asciz	"@(#)misc.s 1.2 88/02/08"
 *	Copyright (c) 1986 by Sun Microsystems, Inc.
 */
 	.seg	"text"
 	.align	4

#include <sun4/asm_linkage.h>
#include <sun4/mmu.h>
#include <sun4/enable.h>
#include <sun4/trap.h>

/*
 * Call a procedure though a pointer in a register.
 */
	RTENTRY(.ptr_call)
	jmp	%g1			! just jump to whatever's in %g1
	nop

/*
 * reset the vme bus via the enable register
 */
	ENTRY(reset_vme)
	set	ENABLEREG, %g1		! addr of enable register in ctl space
	lduba	[%g1]ASI_CTL,%g2	! read current value of enable register 
	bset	0x2, %g2
	stba	%g2, [%g1]ASI_CTL	! write out reset
	bclr	0x2, %g2
	retl
	stba	%g2, [%g1]ASI_CTL	! back to normal
