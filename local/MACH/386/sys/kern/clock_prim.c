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
 * $Log:	clock_prim.c,v $
 * Revision 2.4  89/03/09  20:11:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  18:00:27  gm0w
 * 	Changes for cleanup.
 * 
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TIME_NEW is now standard.
 *	Do ageing here on clock interrupts instead of in
 *	recompute_priorities.  Do accurate usage calculations.
 *
 * 18-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Delete previous history.
 *
 */ 
/*
 *	File:	clock_prim.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr.
 *
 *	Clock primitives.
 */

#include <cpus.h>

#include <machine/cpu.h>
#include <mach/machine.h>
#include <kern/thread.h>
#include <kern/sched.h>

/*
 *	USAGE_THRESHOLD is the amount by which usage must change to
 *	cause a priority shift that moves a thread between run queues.
 */

#ifdef	PRI_SHIFT_2
#if	PRI_SHIFT_2 > 0
#define USAGE_THRESHOLD (((1 << PRI_SHIFT) + (1 << PRI_SHIFT_2)) << (2 + SCHED_SHIFT))
#else	PRI_SHIFT_2 > 0
#define USAGE_THRESHOLD (((1 << PRI_SHIFT) - (1 << -(PRI_SHIFT_2))) << (2 + SCHED_SHIFT))
#endif	PRI_SHIFT_2 > 0
#else	PRI_SHIFT_2
#define USAGE_THRESHOLD	(1 << (PRI_SHIFT + 2 + SCHED_SHIFT))
#endif	PRI_SHIFT_2

/*
 *	clock_tick:
 *
 *	Handle hardware clock ticks.  The number of ticks that has elapsed
 *	since we were last called is passed as "nticks."  Note that this
 *	is called for each processor that is taking clock interrupts, and
 *	that some processors may be running at different clock rates.
 *	However, all of these rates must be some multiple of the basic clock
 *	tick.
 *
 *	The state the processor was executing in is passed as "state."
 */

clock_tick(nticks, state)
	int		nticks;
	register int	state;
{
	register int			mycpu;
	register thread_t		thread;
	register int			quantum;
#if	NCPUS > 1
	register int			ncpus;

	ncpus = machine_info.avail_cpus;
#endif	NCPUS > 1

	mycpu = cpu_number();		/* who am i? */

	/*
	 *	Update the cpu ticks for this processor.
	 */

	machine_slot[mycpu].cpu_ticks[state] += nticks;

	/*
	 *	Account for thread's utilization of these ticks.
	 *	This assumes that there is *always* a current thread.
	 *	When the processor is idle, it should be the idle thread.
	 */

	thread = current_thread();

	/*
	 *	Update sys_quantum and calculate the current quantum.
	 */
#if	NCPUS > 1
	sys_quantum = machine_quantum[((global_runq.count > ncpus) ?
		ncpus : global_runq.count)];

	if (local_runq[mycpu].count != 0)
		quantum = min_quantum;
	else
		quantum = sys_quantum;
#else	NCPUS > 1
	quantum = min_quantum;
	sys_quantum = quantum;
#endif	NCPUS > 1
		
	/*
	 *	Now recompute the priority of the thread if appropriate.
	 */

	if (state != CPU_STATE_IDLE) {
		thread->quantum -= nticks;
#if	NCPUS > 1
		/*
		 *	Runtime quantum adjustment.  Use quantum_adj_index
		 *	to avoid synchronizing quantum expirations.
		 */
		if ((quantum != last_quantum[mycpu]) && (ncpus > 1)) {
			last_quantum[mycpu] = quantum;
			simple_lock (&quantum_adj_lock);
			quantum = min_quantum + (quantum_adj_index *
				(quantum - min_quantum)) / (ncpus - 1);
			quantum_adj_index++;
			if (quantum_adj_index >= ncpus)
				quantum_adj_index = 0;
			simple_unlock (&quantum_adj_lock);
		}
#endif	NCPUS > 1
		if (thread->quantum <= 0) {
			thread_lock(thread);
			if (thread->sched_stamp != sched_tick) {
				update_priority(thread);
			}
			else {
				thread_timer_delta(thread);
				thread->sched_usage += thread->sched_delta;
				thread->sched_delta = 0;
				compute_my_priority(thread);
			}
			thread_unlock(thread);
			/*
			 *	This quantum is up, set runrun to indicate
			 *	this, and give this thread another quantum
			 *	in case it continues running.
			 */
			runrun[mycpu]++;
			thread->quantum += quantum;
		}
		/*
		 *	Recompute priority if appropriate.
		 */
		else {
		    thread_lock(thread);
		    if (thread->sched_stamp != sched_tick) {
			update_priority(thread);
		    }
		    else {
		   	thread_timer_delta(thread);
			if (thread->sched_delta >= USAGE_THRESHOLD) {
			    thread->sched_usage += thread->sched_delta;
			    thread->sched_delta = 0;
			    compute_my_priority(thread);
			}
		    }
		    thread_unlock(thread);
		}
		/*
		 * Check for and schedule ast if needed.
		 */
		ast_check();
	}
}
