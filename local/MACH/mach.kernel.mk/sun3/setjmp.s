/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	setjmp.s,v $
 * Revision 2.6  89/02/25  19:47:12  gm0w
 * 	Removed else legs of MACH and CMU conditionals.
 * 	[89/02/08            jjc]
 * 
 * Revision 2.5  89/02/17  21:35:14  rpd
 * 	Moved to sun3/.
 * 
 * Revision 2.4  88/08/24  02:09:31  mwyoung
 * 		Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 * 25-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	For now to make things work for gcc, save all regs in
 *	syscall_setjmp.
 *
 * 11-Sep-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added longjmp_rval to return other values than 1 from 
 *	longjmp (for kernel debugger).
 *
 */
#include <mach_kdb.h>
	.data
	.asciz	"@(#)setjmp.s 1.1 86/02/03 Copyr 1984 Sun Micro"
	.even
	.text

|	Copyright (c) 1984 by Sun Microsystems, Inc.

#include <sun3/asm_linkage.h>

| Longjmp and setjmp implement non-local gotos
| using state vectors of type label_t (13 longs).
| Registers saved are the PC, d2-d7, and a2-a7.
SAVREGS = 0xFCFC

	ENTRY2(syscall_setjmp,setjmp)
	movl	sp@(4),a1		| get label_t address
	moveml	#SAVREGS,a1@(4)		| save data/address regs
	movl	sp@,a1@			| save PC of caller
	clrl	d0			| return zero
	rts

	ENTRY(longjmp)
	movl	sp@(4),a1		| get label_t address
	moveml	a1@(4),#SAVREGS		| restore data/address regs
| Note: we just changed stacks
	movl	a1@,sp@			| restore PC
	movl	#1,d0			| return one
	rts	

#if	MACH_KDB
	ENTRY(longjmp_rval)
	movl	sp@(4),a1		| get label_t address
	movl	sp@(8),d0		| get value to return
					| (assume not 0)
	moveml	a1@(4),#SAVREGS		| restore data/address regs
| Note: we just changed stacks
	movl	a1@,sp@			| restore PC
	rts	
#endif	MACH_KDB
