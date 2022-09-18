/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	syscall_sw.h,v $
 * Revision 2.9  89/12/22  16:28:45  rpd
 * 	Added rfs_make_symlink() and mach_swapon() syscalls.
 * 	[89/11/24  15:07:28  rpd]
 * 
 * Revision 2.8  89/10/11  14:41:26  dlb
 * 	Remove thread_restore_priority.
 * 	Add thread_switch.
 * 	Remove kern_timestamp.
 * 	Add host traps.
 * 
 * Revision 2.7.3.1  89/08/04  14:37:47  dlb
 * 	Add thread_restore_priority and thread_switch.
 * 	[89/06/03            dlb]
 * 
 * 	Remove kern_timestamp.
 * 	[89/05/10            dlb]
 * 
 * Revision 2.7  89/05/06  02:58:15  rpd
 * 	Purged task_data and task_by_pid.
 * 	[89/05/05  20:52:13  rpd]
 * 
 * Revision 2.6  89/05/01  17:03:04  rpd
 * 	Added mach_sctimes_port_alloc_dealloc.
 * 	[89/05/01  14:11:38  rpd]
 * 
 * Revision 2.5  89/04/22  15:25:24  gm0w
 * 	Removed old MACH ctimes() system call.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.4  89/04/08  23:32:13  rpd
 * 	Removed InitPort, SoftEnable, MessagesWaiting, ns_port.
 * 	[89/03/14  14:56:32  rpd]
 * 
 * Revision 2.3  89/03/15  15:05:52  gm0w
 * 	14-Mar-89 Mary Thompson (mrt) at Carnegie-Mellon University
 * 	Removed definition of ns_port. It was not implementated and
 * 	conflicted with a mach_sctimes trap.
 * 
 * Revision 2.2  89/03/10  13:41:58  rpd
 * 	Created from kern/syscall_sw.h.
 * 
 */

#ifndef	_MACH_SYSCALL_SW_H_
#define _MACH_SYSCALL_SW_H_

/*
 *	The machine-dependent "syscall_sw.h" file should
 *	define a macro for
 *		kernel_trap(trap_name, trap_number, arg_count)
 *	which will expand into assembly code for the
 *	trap.
 *
 *	N.B.: When adding calls, do not put spaces in the macros.
 */

#include <mach/machine/syscall_sw.h>

/*
 *	These trap numbers should be taken from the
 *	table in "../kern/syscall_sw.c".
 */

kernel_trap(task_self,-10,0)
kernel_trap(thread_reply,-11,0)
kernel_trap(task_notify,-12,0)
kernel_trap(thread_self,-13,0)
kernel_trap(msg_send_old,-14,3)
kernel_trap(msg_receive_old,-15,3)
kernel_trap(msg_rpc_old,-16,5)
kernel_trap(msg_send_trap,-20,4)
kernel_trap(msg_receive_trap,-21,5)
kernel_trap(msg_rpc_trap,-22,6)

kernel_trap(htg_unix_syscall,-52,3);

kernel_trap(inode_swap_preference,-40,3)
kernel_trap(init_process,-41,0)
kernel_trap(map_fd,-43,5)
kernel_trap(rfs_make_symlink,-44,3)
kernel_trap(mach_swapon,-45,4)

kernel_trap(host_self,-55,1)
kernel_trap(host_priv_self,-56,1)
kernel_trap(swtch_pri,-59,1)
kernel_trap(swtch,-60,0)
kernel_trap(thread_switch,-61,3)

kernel_trap(mach_sctimes_0,-70,0)
kernel_trap(mach_sctimes_1,-71,1)
kernel_trap(mach_sctimes_2,-72,2)
kernel_trap(mach_sctimes_3,-73,3)
kernel_trap(mach_sctimes_4,-74,4)
kernel_trap(mach_sctimes_5,-75,5)
kernel_trap(mach_sctimes_6,-76,6)

kernel_trap(mach_sctimes_7,-77,0)
kernel_trap(mach_sctimes_8,-78,6)

kernel_trap(mach_sctimes_9,-79,1)
kernel_trap(mach_sctimes_10,-80,2)
kernel_trap(mach_sctimes_11,-81,2)

kernel_trap(mach_sctimes_port_alloc_dealloc,-82,1)

#endif	_MACH_SYSCALL_SW_H_
