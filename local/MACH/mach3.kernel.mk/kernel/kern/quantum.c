/* 
 * Mach Operating System
 * Copyright (c) 1993-1987 Carnegie Mellon University
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
 * $Log:	quantum.c,v $
 * Revision 2.2  93/11/17  17:19:04  dbg
 * 	Separated quantum calculation code from clock update routines
 * 	and moved into this file.
 * 	[93/05/11            dbg]
 * 
 */

#include <mach/boolean.h>

#include <kern/processor.h>
#include <kern/sched_policy.h>
#include <kern/thread.h>

/*
 *	Quantum adjustment.
 */

/*
 *	Max context switch rate, in microseconds.
 */
int	min_quantum = 100 * 1000;	/* 10/second = 100 milliseconds */

/*
 *	Precalculate the appropriate system quanta based on load.  The
 *	index into machine_quantum is the number of threads on the
 *	processor set queue.  It is limited to the number of processors in
 *	the set.
 */

void quantum_set(
	processor_set_t	pset)
{
#if	NCPUS > 1
	register int	i,ncpus;

	ncpus = pset->processor_count;

	for (i = 1; i <= ncpus; i++) {
	    pset->machine_quantum[i] = ((min_quantum * ncpus) + (i/2)) / i ;
	}
	pset->machine_quantum[0] = 2 * pset->machine_quantum[1];

	i = (pset->runq.count > pset->processor_count)
		? pset->processor_count
		: pset->runq.count;
	pset->set_quantum = pset->machine_quantum[i];
#else	/* NCPUS > 1 */
	default_pset.set_quantum = min_quantum;
#endif	/* NCPUS > 1 */
}

/*
 *	clock_quantum_update:
 *
 *	Recalculate the quantum and priority for a thread.
 *	The number of microseconds that has elapsed since
 *	we were last called is passed in.
 */

void
clock_quantum_update(
	thread_t	thread,
	int		mycpu,
	unsigned int	usecs)
{
	int		quantum;
	processor_t	myprocessor = cpu_to_processor(mycpu);
	boolean_t	end_quantum;

#if	NCPUS > 1
	/*
	 *	Update set_quantum.
	 */
    {
	processor_set_t	pset = myprocessor->processor_set;

	if (pset == 0) {
	    /*
	     * Processor is being reassigned.
	     *
	     * Should rewrite processor assignment code to
	     * block clock interrupts.
	     */
	    return;
	}

	if (pset->runq.count > pset->processor_count)
	    pset->set_quantum = pset->machine_quantum[pset->processor_count];
	else
	    pset->set_quantum = pset->machine_quantum[pset->runq.count];

	if (myprocessor->state == PROCESSOR_IDLE)
	    return;

#if	MACH_IO_BINDING
	if (myprocessor->runq.count != 0)
	    quantum = min_quantum;
	else
#endif
	    quantum = pset->set_quantum;

	/*
	 * Runtime quantum adjustment.  Use quantum_adj_index
	 * to avoid synchronizing quantum expirations.
	 */
	if (quantum != myprocessor->last_quantum &&
	    pset->processor_count > 1)
	{
	    myprocessor->last_quantum = quantum;
	    simple_lock(&pset->quantum_adj_lock);
	    quantum = min_quantum +
			(pset->quantum_adj_index * (quantum - min_quantum))
			    / (pset->processor_count - 1);
	    if (++pset->quantum_adj_index >= pset->processor_count)
		pset->quantum_adj_index = 0;
	    simple_unlock(&pset->quantum_adj_lock);
	}
    }

#else	/* NCPUS > 1 */
	quantum = min_quantum;

	if (myprocessor->state == PROCESSOR_IDLE)
	    return;
#endif	/* NCPUS > 1 */

	/*
	 * Decrement quantum
	 */
	myprocessor->quantum -= usecs;
	if (myprocessor->quantum <= 0) {
	    /*
	     * The quantum is up.  Give the thread another.
	     */
	    myprocessor->first_quantum = FALSE;
	    myprocessor->quantum += quantum;
	    end_quantum = TRUE;
	}
	else {
	    end_quantum = FALSE;
	}

	CLOCK_SCHED(thread, end_quantum);
}
