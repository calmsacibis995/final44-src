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
 * $Log:	ast.c,v $
 * Revision 2.5  89/04/05  13:03:02  rvb
 * 	Forward declaration of csw_check() as boolean_t.
 * 	[89/03/21            rvb]
 * 
 * Revision 2.4  89/02/25  18:00:04  gm0w
 * 	Changes for cleanup.
 * 
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	Moved cpu not running check to ast_check().
 *	New preempt priority logic.
 *	Increment runrun if ast is for context switch.
 *	Give absolute priority to local run queues.
 *
 * 20-Apr-88  David Black (dlb) at Carnegie-Mellon University
 *	New signal check logic.
 *
 * 18-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flushed conditionals, reset history.
 */ 

/*
 *
 *	This file contains routines to check whether ast's and context
 *	switches are needed.
 *
 *	ast_check() - check whether ast is needed for signal, or context
 *	switch.
 *
 *	csw_check() - check whether context switch is needed
 *
 *
 */

#include <cpus.h>

#include <machine/cpu.h>
#include <machine/pcb.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <kern/sched.h>
#include <sys/systm.h>
#include <kern/thread.h>
#include <sys/user.h>

	/*
	 *	Forward Declarations.
	 */

boolean_t	csw_check();

ast_check()
{
	register struct proc	*p;
	register struct uthread	*uthreadp;

	/*
	 *	If this processor is not RUNNING, no ast.
	 */
	if (cpu_state(cpu_number()) != CPU_RUNNING)
		return;

	/*
	 *	First check if a context switch is needed.
	 */
	if (csw_check()) {
		runrun[cpu_number()]++;
		aston();
		return;
	}

	/*
	 *	Else check for signals and thread halt condition.
	 */
	p = u.u_procp;
	uthreadp = current_thread()->u_address.uthread;
	if (thread_should_halt() || p->p_cursig || SHOULDissig(p,uthreadp))
		aston();
}

boolean_t csw_check()
{
	register int		mycpu, rqi;
	register thread_t	thread;

	mycpu = cpu_number();
	thread = current_thread();

	/*
	 *	If the current thread should be suspended, context switch.
	 */
	if (thread->suspend_count > 0)
		return(TRUE);

	/*
	 *	Calculate run queue index for context switch.  If runrun
	 *	is set, use scheduler priority.  Else use preempt priority
	 *	and subtract two to require significant preempt.
	 */
	if (runrun[mycpu]) {
	    rqi = (thread->sched_pri >> 2);
	}
	else {
	    rqi = (thread->preempt_pri >> 2) - 2;
	}

	/*
	 *	Look for other threads that could run on this cpu.  Note
	 *	that the global runq is empty if there are idle cpus.
	 */

	if (thread->whichq == &global_runq) {
		if (local_runq[mycpu].count > 0) {
			return(TRUE);
		}
		else {
			if (idle_count == 0 &&
			    other_threads_runnable(rqi,&global_runq))
				return(TRUE);
			else
				return(FALSE);
		}
	}
	else {
		if (other_threads_runnable(rqi,&local_runq[mycpu]))
			return(TRUE);
		else
			return(FALSE);
	}
}
