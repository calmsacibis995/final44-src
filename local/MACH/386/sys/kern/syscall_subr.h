/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	syscall_subr.h,v $
 * Revision 2.3  89/05/01  17:28:32  rpd
 * 	Removed the ctimes() declaration; it's history.
 * 
 * Revision 2.2  89/05/01  17:01:50  rpd
 * 	Created.
 * 	[89/05/01  14:00:51  rpd]
 * 
 */

#ifndef	_KERN_SYSCALL_SUBR_H_
#define _KERN_SYSCALL_SUBR_H_

#include <mach_emulation.h>
#include <mach_sctimes.h>

#include <mach/port.h>
#include <mach/kern_return.h>

extern	port_t		task_by_pid();
extern	kern_return_t	init_process();
extern	kern_return_t	kern_timestamp();

extern int	swtch();
extern int	swtch_pri();

extern int	map_fd();

#if	MACH_EMULATION
extern int	htg_unix_syscall();
#endif	MACH_EMULATION

#if	MACH_SCTIMES
extern kern_return_t mach_sctimes_0();
extern kern_return_t mach_sctimes_1();
extern kern_return_t mach_sctimes_2();
extern kern_return_t mach_sctimes_3();
extern kern_return_t mach_sctimes_4();
extern kern_return_t mach_sctimes_5();
extern kern_return_t mach_sctimes_6();
extern kern_return_t mach_sctimes_7();
extern kern_return_t mach_sctimes_8();
extern kern_return_t mach_sctimes_9();
extern kern_return_t mach_sctimes_10();
extern kern_return_t mach_sctimes_11();
extern kern_return_t mach_sctimes_port_alloc_dealloc();
#endif	MACH_SCTIMES

#endif	_KERN_SYSCALL_SUBR_H_
