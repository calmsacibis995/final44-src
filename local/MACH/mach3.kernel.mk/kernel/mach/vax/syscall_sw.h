/*
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988,1987 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	syscall_sw.h,v $
 * Revision 2.5  93/01/14  17:48:40  danner
 * 	Standardized include symbol name.
 * 	[92/06/10            pds]
 * 
 * Revision 2.4  91/07/31  17:55:09  dbg
 * 	Fixes for ANSI and GNU C preprocessors.
 * 	[91/07/23            dbg]
 * 
 * Revision 2.3  91/05/14  17:02:09  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/02/05  17:37:08  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:15:09  mrt]
 * 
 * Revision 2.1  89/08/03  16:01:27  rwd
 * Created.
 * 
 * Revision 2.3  89/02/25  18:41:56  gm0w
 * 	Changes for cleanup.
 * 
 *  1-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created from mach_syscalls.h in the user library sources.
 *
 */

#ifndef	_MACH_VAX_SYSCALL_SW_H_
#define	_MACH_VAX_SYSCALL_SW_H_	1

#ifdef	__STDC__
#define kernel_trap(trap_name, trap_number, number_args) \
	.globl	_ ## trap_name; \
	.align	2; \
_ ## trap_name: \
	.word	0; \
	chmk	$(trap_number); \
	ret

#else	/* __STDC__ */
#define kernel_trap(trap_name, trap_number, number_args) \
	.globl	_/**/trap_name; \
	.align	2; \
_/**/trap_name: \
	.word	0; \
	chmk	$trap_number; \
	ret

#endif	/* __STDC__ */

#endif	/* _MACH_VAX_SYSCALL_SW_H_ */
