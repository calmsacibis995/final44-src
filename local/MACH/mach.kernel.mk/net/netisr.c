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
 * $Log:	netisr.c,v $
 * Revision 2.5  89/10/11  14:49:17  dlb
 * 	Pass processor instead of cpu to thread_bind.
 * 	[89/01/25            dlb]
 * 
 * Revision 2.4  89/04/05  13:03:26  rvb
 * 	You must include machparam.h for splnet().
 * 	[89/03/22            rvb]
 * 
 * Revision 2.3  89/03/09  20:39:24  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:54:16  gm0w
 * 	Updated copyright notice.
 * 	[89/02/12            gm0w]
 * 
 * 01-Feb-88  David Golub (dbg) at Carnegie-Mellon University
 *	Goofed... netisr thread must run at splnet, because the routines
 *	it calls expect to be called from the softnet interrupt (at
 *	splnet).
 *
 * 19-Nov-87  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */

/*
 *	netisr.c
 *
 *	Kernel thread for network code.
 */

#include "imp.h"
#include <net/netisr.h>

#include <kern/processor.h>
#include <kern/thread.h>
#include <kern/sched_prim.h>
#include <machine/machparam.h>			/* for spl's */

void netisr_thread()
{
	register thread_t thread = current_thread();

	/*
	 *	Make this the highest priority thread,
	 *	and bind it to the master cpu.
	 */
	thread->priority = 0;
	thread->sched_pri = 0;
	thread_bind(thread, master_processor);
	thread_block();	/* resume on master */

	/*
	 *	All routines this thread calls expect to be called
	 *	at splnet.
	 */
	(void) splnet();

	while (TRUE) {
	    assert_wait((int) &soft_net_wakeup, FALSE);
	    thread_block();

#if	NIMP > 0
	    if (netisr & (1<<NETISR_IMP)){
		netisr &= ~(1<<NETISR_IMP);
		impintr();
	    }
#endif	NIMP > 0
#ifdef	INET
	    if (netisr & (1<<NETISR_IP)){
		netisr &= ~(1<<NETISR_IP);
		ipintr();
	    }
#endif	INET
#ifdef	NS
	    if (netisr & (1<<NETISR_NS)){
		netisr &= ~(1<<NETISR_NS);
		nsintr();
	    }
#endif	NS
	    if (netisr & (1<<NETISR_RAW)){
		netisr &= ~(1<<NETISR_RAW);
		rawintr();
	    }

	}
}
