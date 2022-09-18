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
 * $Log:	syscall_sw.c,v $
 * Revision 2.14  89/12/22  16:28:37  rpd
 * 	Added mach_swapon() syscall.
 * 	[89/11/24  15:06:55  rpd]
 * 
 * Revision 2.13  89/10/11  14:27:54  dlb
 * 	Add thread_switch.
 * 	Removed kern_timestamp.
 * 	Add host_self, host_priv_self.
 * 
 * Revision 2.12  89/10/10  10:54:40  mwyoung
 * 	Add a new call to create an RFS link, a special form of
 * 	symbolic link that may contain null characters in the target.
 * 	[89/05/12  16:03:42  mwyoung]
 * 
 * Revision 2.11  89/05/06  02:57:03  rpd
 * 	Removed obsolete task_by_pid trap.
 * 	[89/05/05  20:51:49  rpd]
 * 
 * Revision 2.10  89/05/01  17:02:01  rpd
 * 	Moved trap function declarations to kern/syscall_subr.h.
 * 	Extended the table through trap 130.
 * 	Added mach_sctimes_port_alloc_dealloc.
 * 	[89/05/01  14:02:19  rpd]
 * 
 * Revision 2.9  89/04/22  15:25:07  gm0w
 * 	Removed old MACH ctimes() system call.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.8  89/03/05  16:48:24  rpd
 * 	Renamed the obsolete msg_{send,receive,rpc} traps to
 * 	msg_{send,receive,rpc}_old.
 * 	[89/02/15  13:50:10  rpd]
 * 
 * Revision 2.7  89/02/25  18:09:05  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/01/10  23:32:13  rpd
 * 	Added MACH_IPC_XXXHACK conditionals around the obsolete IPC traps.
 * 	[89/01/10  23:10:07  rpd]
 * 
 * Revision 2.5  88/12/19  02:47:31  mwyoung
 * 	Removed old MACH conditionals.
 * 	[88/12/13            mwyoung]
 * 
 * Revision 2.4  88/10/27  10:48:18  rpd
 * 	Added a bunch of syscalls, conditional under MACH_SCTIMES.
 * 	[88/10/26  14:43:57  rpd]
 * 
 * Revision 2.3  88/10/11  10:20:33  rpd
 * 	Changed includes to the new style.  Replaced msg_receive_,
 * 	msg_rpc_ with msg_send_trap, msg_receive_trap, msg_rpc_trap.
 * 	[88/10/06  12:22:30  rpd]
 * 
 *  7-Apr-88  David Black (dlb) at Carnegie-Mellon University
 *	removed thread_times().
 *
 * 18-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Replaced task_data with thread_reply; change is invisible to
 *	users.
 *
 * 03-Mar-88  Douglas Orr (dorr) at Carnegie-Mellon University
 *	Added htg_unix_syscall()
 *
 * 27-Apr-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added new forms of msg_receive, msg_rpc.
 *
 *  1-Apr-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Added "WARNING:" comment.
 *
 * 30-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	Added kern_timestamp()
 *
 * 27-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	Added thread_times() for MACH_TIME_NEW.  Flushed MACH_TIME.
 *
 * 25-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added map_fd.
 *
 * 27-Feb-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH_IPC: Turn off Accent compatibility traps.
 *
 *  4-Feb-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added ctimes() routine, to make a workable restore program.
 *
 * 10-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Eliminated KPortToPID.
 *
 *  7-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added "init_process".
 *
 * 29-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added inode_swap_preference.
 *
 * 12-Oct-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Major reorganization: added msg_send, msg_receive, msg_rpc;
 *	moved real Mach traps up front; renamed table.
 */

#include <mach_rfs.h>
#include <mach_ipc_xxxhack.h>
#include <mach_emulation.h>
#include <mach_sctimes.h>

/*
 *	To add a new entry:
 *		Add an "FN(routine, arg count)" to the table below.
 *
 *		Add trap definition to "kern/syscall_sw.h" and
 *		recompile user library.
 *
 * WARNING:	If you add a trap which requires more than 6
 *		parameters, mach/ca/syscall_sw.h and ca/trap.c both need
 *		to be modified for it to work successfully on an
 *		RT.
 */

#include <mach/port.h>
#include <mach/kern_return.h>
#include <kern/syscall_sw.h>

port_t		null_port()
{
	return(PORT_NULL);
}

kern_return_t	kern_invalid()
{
	return(KERN_INVALID_ARGUMENT);
}


/* Include declarations of the trap functions. */

#include <mach/mach_traps.h>
#include <kern/ipc_basics.h>
#include <kern/syscall_subr.h>
#include <builtin/inode_pager.h>

mach_trap_t	mach_trap_table[] = {
	FN(kern_invalid, 0),			/* 0 */
	FN(kern_invalid, 0),			/* 1 */
	FN(kern_invalid, 0),			/* 2 */
	FN(kern_invalid, 0),			/* 3 */
	FN(kern_invalid, 0),			/* 4 */
	FN(kern_invalid, 0),			/* 5 */
	FN(kern_invalid, 0),			/* 6 */
	FN(kern_invalid, 0),			/* 7 */
	FN(kern_invalid, 0),			/* 8 */
	FN(kern_invalid, 0),			/* 9 */
	FN(task_self, 0),			/* 10 */
	FN(thread_reply, 0),			/* 11 */
	FN(task_notify, 0),			/* 12 */
	FN(thread_self, 0),			/* 13 */
#if	MACH_IPC_XXXHACK
	FF1(msg_send_old, 3, APSIG),		/* 14 */	/* obsolete */
	FF1(msg_receive_old, 3, APSIG),		/* 15 */	/* obsolete */
	FF1(msg_rpc_old, 5, APSIG),		/* 16 */	/* obsolete */
#else	MACH_IPC_XXXHACK
	FN(kern_invalid, 0),			/* 14 */
	FN(kern_invalid, 0),			/* 15 */
	FN(kern_invalid, 0),			/* 16 */
#endif	MACH_IPC_XXXHACK
	FN(kern_invalid, 0),			/* 17 */
	FN(kern_invalid, 0),			/* 18 */
	FN(kern_invalid, 0),			/* 19 */
	FF1(msg_send_trap, 4, APSIG),		/* 20 */
	FF1(msg_receive_trap, 5, APSIG),	/* 21 */
	FF1(msg_rpc_trap, 6, APSIG),		/* 22 */
	FN(kern_invalid, 0),			/* 23 */
	FN(kern_invalid, 0),			/* 24 */
	FN(kern_invalid, 0),			/* 25 */
	FN(kern_invalid, 0),			/* 26 */
	FN(kern_invalid, 0),			/* 27 */
	FN(kern_invalid, 0),			/* 28 */
	FN(kern_invalid, 0),			/* 29 */
	FN(kern_invalid, 0),			/* 30 */
	FN(kern_invalid, 0),			/* 31 */
	FN(kern_invalid, 0),			/* 32 */
	FN(kern_invalid, 0),			/* 33 */
	FN(kern_invalid, 0),			/* 34 */
	FN(kern_invalid, 0),			/* 35 */
	FN(kern_invalid, 0),			/* 36 */
	FN(kern_invalid, 0),			/* 37 */
	FN(kern_invalid, 0),			/* 38 */
	FN(kern_invalid, 0),			/* 39 */
	FN(inode_swap_preference, 3),		/* 40 */
	FN(init_process, 0),			/* 41 */
	FN(kern_invalid, 0),			/* 42 */
	FN(map_fd, 5),				/* 43 */
#if	MACH_RFS
	FN(rfs_make_symlink, 3),		/* 44 */
#else	MACH_RFS
	FN(kern_invalid, 0),			/* 44 */
#endif	MACH_RFS
	FN(mach_swapon, 4),			/* 45 */
	FN(kern_invalid, 0),			/* 46 */
	FN(kern_invalid, 0),			/* 47 */
	FN(kern_invalid, 0),			/* 48 */
	FN(kern_invalid, 0),			/* 49 */
	FN(kern_invalid, 0),			/* 50 */
	FN(kern_invalid, 0),			/* 51 */
#if	MACH_EMULATION
	FN(htg_unix_syscall, 3),	       	/* 52 */
#else	MACH_EMULATION
	FN(kern_invalid, 0),			/* 52 */
#endif	MACH_EMUALTION
	FN(kern_invalid, 0),			/* 53 */
	FN(kern_invalid, 0),			/* 54 */
	FN(host_self, 0),			/* 55 */
	FN(host_priv_self, 0),			/* 56 */
	FN(kern_invalid, 0),			/* 57 */
	FN(kern_invalid, 0),			/* 58 */
 	FN(swtch_pri, 1),			/* 59 */
	FN(swtch, 0),				/* 60 */
	FN(thread_switch, 3),			/* 61 */
	FN(kern_invalid, 0),			/* 62 */
	FN(kern_invalid, 0),			/* 63 */
	FN(kern_invalid, 0),			/* 64 */
	FN(kern_invalid, 0),			/* 65 */
	FN(kern_invalid, 0),			/* 66 */
	FN(kern_invalid, 0),			/* 67 */
	FN(kern_invalid, 0),			/* 68 */
	FN(kern_invalid, 0),			/* 69 */
#if	MACH_SCTIMES
	FN(mach_sctimes_0, 0),			/* 70 */
	FN(mach_sctimes_1, 1),			/* 71 */
	FN(mach_sctimes_2, 2),			/* 72 */
	FN(mach_sctimes_3, 3),			/* 73 */
	FN(mach_sctimes_4, 4),			/* 74 */
	FN(mach_sctimes_5, 5),			/* 75 */
	FN(mach_sctimes_6, 6),			/* 76 */
	FF1(mach_sctimes_7, 0, APSIG),		/* 77 */
	FF1(mach_sctimes_8, 6, APSIG),		/* 78 */
	FN(mach_sctimes_9, 1),			/* 79 */
	FN(mach_sctimes_10, 2),			/* 80 */
	FN(mach_sctimes_11, 2),			/* 81 */
	FN(mach_sctimes_port_alloc_dealloc, 1),	/* 82 */
#else	MACH_SCTIMES
	FN(kern_invalid, 0),			/* 70 */
	FN(kern_invalid, 0),			/* 71 */
	FN(kern_invalid, 0),			/* 72 */
	FN(kern_invalid, 0),			/* 73 */
	FN(kern_invalid, 0),			/* 74 */
	FN(kern_invalid, 0),			/* 75 */
	FN(kern_invalid, 0),			/* 76 */
	FN(kern_invalid, 0),			/* 77 */
	FN(kern_invalid, 0),			/* 78 */
	FN(kern_invalid, 0),			/* 79 */
	FN(kern_invalid, 0),			/* 80 */
	FN(kern_invalid, 0),			/* 81 */
	FN(kern_invalid, 0),			/* 82 */
#endif	MACH_SCTIMES
	FN(kern_invalid, 0),			/* 83 */
	FN(kern_invalid, 0),			/* 84 */
	FN(kern_invalid, 0),			/* 85 */
	FN(kern_invalid, 0),			/* 86 */
	FN(kern_invalid, 0),			/* 87 */
	FN(kern_invalid, 0),			/* 88 */
	FN(kern_invalid, 0),			/* 89 */
	FN(kern_invalid, 0),			/* 90 */
	FN(kern_invalid, 0),			/* 91 */
	FN(kern_invalid, 0),			/* 92 */
	FN(kern_invalid, 0),			/* 93 */
	FN(kern_invalid, 0),			/* 94 */
	FN(kern_invalid, 0),			/* 95 */
	FN(kern_invalid, 0),			/* 96 */
	FN(kern_invalid, 0),			/* 97 */
	FN(kern_invalid, 0),			/* 98 */
	FN(kern_invalid, 0),			/* 99 */
	FN(kern_invalid, 0),			/* 100 */
	FN(kern_invalid, 0),			/* 101 */
	FN(kern_invalid, 0),			/* 102 */
	FN(kern_invalid, 0),			/* 103 */
	FN(kern_invalid, 0),			/* 104 */
	FN(kern_invalid, 0),			/* 105 */
	FN(kern_invalid, 0),			/* 106 */
	FN(kern_invalid, 0),			/* 107 */
	FN(kern_invalid, 0),			/* 108 */
	FN(kern_invalid, 0),			/* 109 */
	FN(kern_invalid, 0),			/* 110 */
	FN(kern_invalid, 0),			/* 111 */
	FN(kern_invalid, 0),			/* 112 */
	FN(kern_invalid, 0),			/* 113 */
	FN(kern_invalid, 0),			/* 114 */
	FN(kern_invalid, 0),			/* 115 */
	FN(kern_invalid, 0),			/* 116 */
	FN(kern_invalid, 0),			/* 117 */
	FN(kern_invalid, 0),			/* 118 */
	FN(kern_invalid, 0),			/* 119 */
	FN(kern_invalid, 0),			/* 120 */
	FN(kern_invalid, 0),			/* 121 */
	FN(kern_invalid, 0),			/* 122 */
	FN(kern_invalid, 0),			/* 123 */
	FN(kern_invalid, 0),			/* 124 */
	FN(kern_invalid, 0),			/* 125 */
	FN(kern_invalid, 0),			/* 126 */
	FN(kern_invalid, 0),			/* 127 */
	FN(kern_invalid, 0),			/* 128 */
	FN(kern_invalid, 0),			/* 129 */
	FN(kern_invalid, 0),			/* 130 */
};

int	mach_trap_count = (sizeof(mach_trap_table) / sizeof(mach_trap_table[0]));
