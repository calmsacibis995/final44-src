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
 * Revision 2.6  89/03/09  20:16:10  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  18:09:12  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/10/27  10:48:53  rpd
 * 	Changed msg_{send,receive,rpc}_trap to 20, 21, 22.
 * 	Added a bunch of mach_sctimes syscalls.
 * 	[88/10/26  14:45:13  rpd]
 * 
 * Revision 2.3  88/10/11  10:21:04  rpd
 * 	Changed traps msg_send, msg_receive_, msg_rpc_ to
 * 	msg_send_old, msg_receive_old, msg_rpc_old.
 * 	Added msg_send_trap, msg_receive_trap, msg_rpc_trap.
 * 	[88/10/06  12:24:33  rpd]
 * 
 * 20-Apr-88  David Black (dlb) at Carnegie-Mellon University
 *	Removed thread_times().
 *
 * 18-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Replaced task_data with thread_reply; change is invisible to
 *	users.  Carried over Mary Thompson's change below:
 *
 * Mary Thompson (originally made 19-May-87 in /usr/mach/include)
 *	Went back to old msg_receive_ and msg_rpc_ traps
 *	so that the library would work with the standard kernels
 *
 * 01-Mar-88  Douglas Orr (dorr) at Carnegie-Mellon University
 *	Add htg_unix_syscall
 *
 * 15-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	LOCORE -> ASSEMBLER.  Removed unnecessary conditional
 *	compilation (assumes MACH to the full extent).
 *
 *  8-Apr-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Change name for "msg_receive" to "msg_receive_", to enable user
 *	library to loop looking for software interrupt condition.
 *	Same for msg_rpc.
 *
 * 30-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	Added kern_timestamp()
 *
 * 27-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	Added thread_times for MACH_TIME_NEW.  Flushed MACH_TIME.
 *
 * 25-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added map_fd, deleted DEFUNCT code.
 *
 * 18-Feb-87  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Added # args to the kernel_trap() macro.
 *	Balance needs to know # of args passed to trap routine
 *
 *  4-Feb-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added ctimes().
 *
 *  7-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added "init_process".
 *
 *  4-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed some old Accent calls; they should be supplanted by
 *	library conversion routines to Mach calls.
 *
 * 29-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Put swtch under MACH_MP; added inode_swap_preference.
 *
 * 12-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added traps for msg_send, msg_receive, msg_rpc, under
 *	either MACH_ACC or MACH_IPC.  Removed unused calls.
 *	Restructured and renamed trap table.
 *
 *  1-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Moved stuff from user source directory back here, and into
 *	<mach/machine/syscall_sw.h>.  It's only natural that the kernel
 *	sources describe what traps exist, and how they're made.
 */

#ifndef	_KERN_SYSCALL_SW_H_
#define _KERN_SYSCALL_SW_H_

#ifndef	ASSEMBLER

typedef struct {
	short		mach_trap_length;
	short		mach_trap_flags;
	int		(*mach_trap_function)();
} mach_trap_t;

extern mach_trap_t	mach_trap_table[];
extern int		mach_trap_count;

#define MACH_TRAP(name, arg_count, flags)	\
		{ sizeof(int) * ((arg_count)+1), (flags), (name) }
#define FF1(name,argno,flags)	MACH_TRAP(name, argno, 1<<flags)
#define FN(name, argno)		MACH_TRAP(name, argno, 0)

#endif	ASSEMBLER

/*
 *	Flag values (actually bit numbers)
 */

#define ASETJMP		0
#define APSIG		2

#endif	_KERN_SYSCALL_SW_H_
