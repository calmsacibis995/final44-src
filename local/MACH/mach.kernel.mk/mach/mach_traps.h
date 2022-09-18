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
 * $Log:	mach_traps.h,v $
 * Revision 2.6  89/10/11  14:38:46  dlb
 * 	Add host traps.
 * 	[89/01/25            dlb]
 * 
 * Revision 2.5  89/03/09  20:20:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:37:15  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/19  12:57:44  rpd
 * 	Moved from kern/ to mach/.
 * 
 * Revision 2.2  89/01/15  16:24:46  rpd
 * 	Updated includes for the new mach/ directory.
 * 	[89/01/15  15:03:03  rpd]
 * 
 * 18-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Add thread_reply.  Leave in task_data as an alternate name -
 *	they are functionally indistinguishable.
 *
 * 15-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Include ../kern/mach_types.h instead of <kern/mach_types.h> when
 *	building for the kernel.
 *
 *  1-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created, mostly to help build the lint library.
 *	Should eventually include this in "syscall_sw.c".
 *
 */
/*
 *	Definitions of general Mach system traps.
 *
 *	IPC traps are defined in <mach/message.h>.
 *	Kernel RPC functions are defined in <kern/mach.h>.
 */

#ifndef	_MACH_MACH_TRAPS_H_
#define _MACH_MACH_TRAPS_H_

#define _MACH_INIT_	1

#include <mach/mach_types.h>

#ifdef	KERNEL
port_t		task_self
#else	KERNEL
task_t		task_self
#endif	KERNEL
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	LINTLIBRARY
			();
#endif	LINTLIBRARY

port_t		task_data
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	LINTLIBRARY
			();
#endif	LINTLIBRARY

port_t		task_notify
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	LINTLIBRARY
			();

#endif	LINTLIBRARY

#ifdef	KERNEL
port_t		thread_self
#else	KERNEL
thread_t	thread_self
#endif	KERNEL
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	LINTLIBRARY
			();
#endif	LINTLIBRARY

port_t		thread_reply
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	LINTLIBRARY
			();
#endif	LINTLIBRARY

#ifdef	KERNEL
port_t		host_self
#else	KERNEL
host_t		host_self
#endif	KERNEL
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	LINTLIBRARY
			();
#endif	LINTLIBRARY

#ifdef	KERNEL
port_t		host_priv_self
#else	KERNEL
host_priv_t	host_priv_self
#endif	KERNEL
#ifdef	LINTLIBRARY
			()
	 { return(PORT_NULL); }
#else	LINTLIBRARY
			();
#endif	LINTLIBRARY

#endif	_MACH_MACH_TRAPS_H_
