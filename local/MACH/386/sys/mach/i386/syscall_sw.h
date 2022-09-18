/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	syscall_sw.h,v $
 * Revision 1.3.1.1  89/12/22  22:22:03  rvb
 * 	Use asm.h
 * 	[89/12/22            rvb]
 * 
 * Revision 1.3  89/03/09  20:19:53  rpd
 * 	More cleanup.
 * 
 * Revision 1.2  89/02/26  13:01:00  gm0w
 * 	Changes for cleanup.
 * 
 * 31-Dec-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Derived from MACH2.0 vax release.
 *
 *  1-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created from mach_syscalls.h in the user library sources.
 *
 */

#ifndef	_MACH_I386_SYSCALL_SW_H_
#define _MACH_I386_SYSCALL_SW_H_

#include <machine/asm.h>

#define kernel_trap(trap_name, trap_number, number_args) \
ENTRY(trap_name) \
	movl	$trap_number,%eax; \
	SVC; \
	ret; 

#endif	_MACH_I386_SYSCALL_SW_H_
