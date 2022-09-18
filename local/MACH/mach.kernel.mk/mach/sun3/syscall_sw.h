/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	syscall_sw.h,v $
 * Revision 2.4  89/03/09  20:23:37  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:40:44  gm0w
 * 	Changes for cleanup.
 * 
 * 15-Feb-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Modified for Sun (again).
 *
 *  1-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created from mach_syscalls.h in the user library sources.
 *
 */

#ifndef	_MACH_SUN3_SYSCALL_SW_H_
#define _MACH_SUN3_SYSCALL_SW_H_

#define kernel_trap(trap_name, trap_number, number_args) \
	.globl	_/**/trap_name; \
_/**/trap_name: \
	pea	trap_number; \
	trap	#0; \
	rts

#endif	_MACH_SUN3_SYSCALL_SW_H_
