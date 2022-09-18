/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	boot2.s,v $
 * Revision 2.1.1.1  90/02/09  17:26:00  rvb
 * 	Put into rcs tree
 * 	[90/02/09            rvb]
 * 
 */


#include	"machine/asm.h"

/*
 * boot2() -- second stage boot
 */

ENTRY(boot2)
	mov	%cs, %ax
	mov	%ax, %ds
	mov	%ax, %es
	/* change to protected mode */
	data16
	call	EXT(real_to_prot)

	pushl	%edx		/ bootdev
	call	EXT(boot)
	ret
