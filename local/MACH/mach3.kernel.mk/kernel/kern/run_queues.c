 /* 
 * Mach Operating System
 * Copyright (c) 1994-1987 Carnegie Mellon University
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
 * $Log:	run_queues.c,v $
 * Revision 2.3  94/12/16  10:50:07  dbg
 * 	Restore old behavior only for timesharing threads.  It should
 * 	really be triggered only for a group of threads that use the
 * 	(obsolete) swtch_pri call, but there is no way to isolate just
 * 	those threads.
 * 	[94/10/17            dbg]
 * 
 * 	**TESTING**
 * 	Undo change of 7-Mar-94.  I think that it screws up the
 * 	multiserver, which depends on a depressed thread being able to
 * 	run much more often than its priority warrants.
 * 	**TESTING**
 * 	[94/09/23            dbg]
 * 
 * 	Fixed horrendous bugs in thread_setrun and thread_select: the
 * 	thread policy indices were being compared backwards!
 * 	[94/08/16            dbg]
 * 
 * 	Use pset->runq.lock instead of pset->idle_lock.
 * 	[94/03/17            dbg]
 * 
 * 	csw_needed now locks pset->runq.
 * 	[94/03/16            dbg]
 * 
 * 	Fixed thread_select to pick current thread if it is runnable
 * 	and of higher priority than other waiting threads: equivalent
 * 	to putting it on its run queue before selecting new thread.
 * 	[94/03/07            dbg]
 * 
 * 	Use a bit vector of policies with runnable threads instead of
 * 	scanning the count fields.  This saves enough memory references
 * 	that we don't need to duplicate the run queue pointers for
 * 	multiprocessors in order to shorten the check for bound threads.
 * 	We just check for bound threads before scanning the run queues.
 * 	(i.e. I backed out of the last change under revision 2.2.)
 * 	[94/03/06            dbg]
 * 
 * Revision 2.2  93/11/17  17:20:25  dbg
 * 	Fixed csw_needed to check per-processor run queue for the
 * 	current thread`s scheduling class on MP.  Made thread_bind
 * 	temporarily bind thread to the BP (bound-thread) policy when
 * 	binding to a particular CPU (the same way that depressing a
 * 	thread binds it to the background policy).  NOTE that this won't
 * 	work if a bound thread can be depressed; but on a symmetrical
 * 	MP, we only bind the action thread.  Fixing this (under
 * 	MACH_IO_BINDING) is left as an exercise for the reader.
 * 	[93/09/01            dbg]
 * 
 * 	Use runq pointers in processor if NCPUS > 1 - processor_shutdown
 * 	does not depend on MACH_HOST.
 * 	[93/07/21            dbg]
 * 
 * 	Break up thread lock.
 * 	[93/05/26            dbg]
 * 
 * 	machparam.h -> machspl.h
 * 	[93/05/21            dbg]
 * 
 * 	Changed policy to policy_index in thread.
 * 	[93/05/05            dbg]
 * 
 * 	Moved common code from thread_setrun and rem_runq here.
 * 	[93/04/10            dbg]
 * 
 * 	Processor set now has one run queue structure per scheduling
 * 	policy.  The actual run queues are policy-specific.
 * 	[93/04/06            dbg]
 * 
 * 	Always enable fixed-priority threads.
 * 	[93/03/27            dbg]
 * 
 * 	Moved routines here from kern/sched_prim.c.
 * 	[93/01/12            dbg]
 * 
 */

/*
 *	Run queue routines.
 *
 *	Contain routines to move threads on and off run queues.
 *	The major routine to add a thread to a run queue, thread_setrun,
 *	is specific to the thread's policy.
 *
 *	If there is no thread to run, the idle thread runs instead.
 *
 *	The runq routines also maintain the processor`s quantum,
 *	which is only used by the timesharing scheduling policy.
 *	It is ignored by all of the others, so setting it is harmless.
 */

#include <cpus.h>
#include <mach_host.h>
#include <mach_io_binding.h>

#include <kern/assert.h>
#include <kern/counters.h>
#include <kern/run_queues.h>
#include <kern/runq_bitmap.h>
#include <kern/processor.h>
#include <kern/thread.h>
#include <kern/sched.h>			/* sched_tick */
#include <kern/sched_policy.h>
#include <kern/sched_prim.h>
#include <kern/stack.h>
#include <kern/thread_swap.h>
#include <machine/machspl.h>
#include <sched_policy/standard.h>	/* ts_sched_policy */


thread_t choose_idle_thread(
	register processor_t myprocessor,
	processor_set_t	pset);		/* forward */

/*
 *	Initialize the run queue header structure.
 */
void run_queue_head_init(
	run_queue_head_t runq)
{
	int		i;

	simple_lock_init(&runq->lock);
	runq->count = 0;
	runq->bitmap = 0;
	for (i = 0; i < NUM_POLICIES; i++)
	    runq->runqs[i] = RUN_QUEUE_NULL;
}

void run_queue_head_dealloc(
	run_queue_head_t	runq)
{
	int	i;
	run_queue_t	rq;

	for (i = 0; i < NUM_POLICIES; i++) {
	    rq = runq->runqs[i];
	    if (rq)
		RUNQ_FREE(rq);
	}
}

/*
 *	thread_setrun:
 *
 *	Make thread runnable; dispatch directly onto an idle processor
 *	if possible.  Else put on appropriate run queue (processor
 *	if bound, else processor set).  Caller must have lock on thread.
 *	This is always called at splsched.
 */

void thread_setrun(
	register thread_t	thread,
	boolean_t		may_preempt)
{
	register processor_set_t pset = thread->processor_set;
	int			index = thread->policy_index;
	int			cur_thread_index;
	run_queue_t		rq;
	boolean_t		should_preempt;
#if	NCPUS > 1
	register processor_t	processor;
#endif

	/*
	 *	Update priority if needed.
	 */
	if (thread->sched_stamp != sched_tick)
	    UPDATE_PRIORITY(thread);

	assert(thread->runq == RUN_QUEUE_HEAD_NULL);

#if	NCPUS > 1
	/*
	 *	Try to dispatch the thread directly onto an idle processor.
	 */
	if ((processor = thread->bound_processor) != PROCESSOR_NULL) {
#if	MACH_IO_BINDING
	    /*
	     *	Bound, can only run on bound processor.  Have to lock
	     *  processor here because it may not be the current one.
	     */
	    if (processor->state == PROCESSOR_IDLE) {
		processor_lock(processor);
		pset = processor->processor_set;
		simple_lock(&pset->runq.lock);
		if (processor->state == PROCESSOR_IDLE) {
		    /*
		     *	Bound processor is idle.  Dispatch
		     *	thread directly to processor.
		     */
		    queue_remove(&pset->idle_queue, processor,
			processor_t, processor_queue);
		    pset->idle_count--;
		    processor->next_thread = thread;
		    processor->state = PROCESSOR_DISPATCHING;
		    simple_unlock(&pset->runq.lock);
		    processor_unlock(processor);
		    return;
		}
		simple_unlock(&pset->runq.lock);
		processor_unlock(processor);
	    }

	    /*
	     *	Bound processor is busy.  Put thread on
	     *	processor`s run queue.
	     */
	    simple_lock(&processor->runq.lock);
	    rq = processor->runq.runqs[index];
	    (void) THREAD_ENQUEUE(rq, thread, FALSE);
	    RUNQ_BIT_SET(processor->runq.bitmap, index);
	    processor->runq.count++;
	    thread->runq = &processor->runq;
	    simple_unlock(&processor->runq.lock);

#else	/* MACH_IO_BINDING */

	    /*
	     *	Only the action thread can be bound to a processor.
	     *	In this case, the processor must be in state
	     *	ASSIGN or SHUTDOWN.  Since it is not DISPATCHING,
	     *	processor->next_thread is null.  Since it is not
	     *	IDLE, it cannot be on the idle queue.  So we just
	     *	set processor->next_thread.
	     */
	    processor_lock(processor);
	    assert(processor->state == PROCESSOR_ASSIGN ||
		   processor->state == PROCESSOR_SHUTDOWN);
	    assert(processor->next_thread == THREAD_NULL);

	    processor->next_thread = thread;
	    processor_unlock(processor);

#endif	/* MACH_IO_BINDING */

	    /*
	     *	Cause ast on processor if processor is on line.
	     */
	    if (processor == current_processor()) {
		ast_on(cpu_number(), AST_BLOCK);
	    }
	    else if (processor->state != PROCESSOR_OFF_LINE) {
		cause_ast_check(processor);
	    }
	    return;
	}

	/*
	 *	Not bound, any processor in the processor set is ok.
	 */
#if	HW_FOOTPRINT
	/*
	 *	But first check the last processor it ran on.
	 */
	processor = thread->last_processor;
	if (processor->state == PROCESSOR_IDLE) {
	    processor_lock(processor);
	    simple_lock(&pset->runq.lock);
	    if (processor->state == PROCESSOR_IDLE
#if	MACH_HOST
		&& processor->processor_set == pset
#endif	/* MACH_HOST */
	       )
	    {
		queue_remove(&pset->idle_queue, processor,
			      processor_t, processor_queue);
		pset->idle_count--;
		processor->next_thread = thread;
		processor->state = PROCESSOR_DISPATCHING;
		simple_unlock(&pset->runq.lock);
		processor_unlock(processor);
	        return;
	    }
	    simple_unlock(&pset->runq.lock);
	    processor_unlock(processor);
	}
#endif	/* HW_FOOTPRINT */

	simple_lock(&pset->runq.lock);

	if (pset->idle_count > 0) {
	    queue_remove_first(&pset->idle_queue, processor,
			       processor_t, processor_queue);
	    pset->idle_count--;
	    processor->next_thread = thread;
	    processor->state = PROCESSOR_DISPATCHING;
	    simple_unlock(&pset->runq.lock);
	    return;
	}

#else	/* NCPUS == 1 */

	/*
	 *	Check for idle processor.
	 */
	if (pset->idle_count > 0) {
	    pset->idle_count = 0;
	    processor_array[0].next_thread = thread;
	    processor_array[0].state = PROCESSOR_DISPATCHING;
	    return;
	}

#endif	/* NCPUS */

	/*
	 *	Queue to processor set.
	 */
	cur_thread_index = current_thread()->policy_index;

	rq = pset->runq.runqs[index];
	should_preempt = THREAD_ENQUEUE(rq,
					thread,
					(cur_thread_index == index));
	RUNQ_BIT_SET(pset->runq.bitmap, index);
	pset->runq.count++;
	thread->runq = &pset->runq;
	simple_unlock(&pset->runq.lock);

	/*
	 *	Preemption check.  New thread first must be
	 *	on the current processor`s processor set.
	 */
	if (may_preempt
#if	MACH_HOST
	 && pset == current_processor()->processor_set
#endif
	   )
	{
	    /*
	     *	New thread preempts current thread if it is
	     *	in a higher scheduler class (higher index).
	     *
	     *	Per-policy result is used if new thread and
	     *	current thread are in the same scheduler class.
	     *
	     *	No preemption if new thread is in a lower
	     *	scheduler class (lower index) than current thread.
	     */
	    if (index > cur_thread_index ||
		(index == cur_thread_index && should_preempt))
	    {
		/*
		 *	Turn off first_quantum to allow context switch.
		 */
		current_processor()->first_quantum = FALSE;
		ast_on(cpu_number(), AST_BLOCK);
	    }
	}
}

/*
 *	Remove a thread from the run queues.  Returns the
 *	run queue that the thread was on, or RUN_QUEUE_HEAD_NULL
 *	if the thread was not found on the run queues.
 *
 *	Called with the thread locked, at splsched.
 */
run_queue_head_t
rem_runq(
	thread_t	thread)
{
	run_queue_head_t runq;

	runq = thread->runq;

	/*
	 *	If runq is RUN_QUEUE_NULL, the thread will stay out of the
	 *	run_queues because the caller locked the thread.  Otherwise
	 *	the thread is on a runq, but could leave.
	 */
	if (runq != RUN_QUEUE_HEAD_NULL) {
	    simple_lock(&runq->lock);
	    if (runq == thread->runq) {
		/*
		 *	Thread is in a runq and we have a lock on
		 *	that runq.
		 */
		run_queue_t	rq;

		rq = runq->runqs[thread->policy_index];
		THREAD_REMQUEUE(rq, thread);
		runq->count--;
		if (rq->rq_count == 0)
		    RUNQ_BIT_CLEAR(runq->bitmap, thread->policy_index);

		thread->runq = RUN_QUEUE_HEAD_NULL;
		simple_unlock(&runq->lock);
	    }
	    else {
		/*
		 *	The thread left the runq before we could
		 * 	lock the runq.  It is not on a runq now, and
		 *	can't move again because this routine's
		 *	caller locked the thread.
		 */
		simple_unlock(&runq->lock);
		runq = RUN_QUEUE_HEAD_NULL;
	    }
	}

	return runq;
}

/*
 *	Select the next thread to run on a processor.
 *
 *	Called at splsched.
 */
thread_t
thread_select(
	processor_t	processor)
{
	processor_set_t	pset = processor->processor_set;
	thread_t	cur_thread = current_thread();
	int		cur_index;
	boolean_t	cur_runnable;

	/*
	 *	Check whether the current thread is runnable.
	 *	If it is, we select it to run next if it is
	 *	of higher scheduling class or higher priority
	 *	than the first thread on the run queues.
	 *
	 *	We make an exception for a runnable time-sharing
	 *	thread: we only select it to run if no other
	 *	timesharing threads are runnable.  Some existing
	 *	code (e.g. Mach-US) depends on having depressed
	 *	threads run much more often than is indicated
	 *	by their priority (31).
	 */
    {
	int	state = cur_thread->state;

	cur_runnable = (state == TH_RUN ||
			state == (TH_RUN|TH_UNINT) ||
			state == (TH_RUN|TH_UNINT|TH_SUSP))
		    && check_processor_set(cur_thread)
		    && check_bound_processor(cur_thread);

	if (cur_runnable && cur_thread->policy_index > ts_sched_policy.rank)
	{
	    /* thread is still runnable on this processor */
	    cur_index = cur_thread->policy_index;
	}
	else {
	    /* non-runnable thread is 'lower' than all runnable threads */
	    cur_index = -1;
	}
    }

#if	MACH_IO_BINDING
	/*
	 *	Find the highest priority policy in both the
	 *	local and global run queues.  If they are the
	 *	same, call a policy_specific routine to remove
	 *	the highest_priority thread from both of the
	 *	queues.  If they are different, just pick the
	 *	first thread from the highest_priority policy.
	 */
    {
	int			global_index, local_index;
	run_queue_head_t	rqh;

	simple_lock(&pset->runq.lock);
	simple_lock(&processor->runq.lock);

	if (pset->runq.bitmap == 0)
	    global_index = -1;
	else
	    RUNQ_BIT_FIND(pset->runq.bitmap, global_index);
	if (processor->runq.bitmap == 0)
	    local_index = -1;
	else
	    RUNQ_BIT_FIND(processor->runq.bitmap, local_index);

	if (local_index >= cur_index || global_index >= cur_index) {
	    /*
	     *	Found something, in one or both run queues.
	     *	Pick the one with the higher priority.
	     */
	    if (global_index > local_index) {
		/*
		 *	Global run queue wins.
		 */
		rqh = &pset->runq;
		runq = rqh->runqs[global_index];
		index = global_index;
	    }
	    else if (local_index > global_index) {
		/*
		 *	Local run queue wins.
		 */
		rqh = &processor->runq;
		runq = rqh->runqs[local_index];
		index = local_index;
	    }
	    else {
		/*
		 *	A tie.  Must call policy-specific function
		 *	to decide between the two run queues.
		 */
		run_queue_t	global_runq, local_runq;

		global_runq = pset->runq.runqs[global_index];
		local_runq  = processor->runq.runqs[local_index];

		if (RUNQ_HEAD_PREEMPT(global_runq, local_runq)) {
		    rqh = &pset->runq;
		    runq = global_runq;
		    index = global_index;
		}
		else {
		    rqh = &processor->runq;
		    runq = local_runq;
		    index = local_index;
		}
	    }
	    if (index > cur_index ||
		(index == cur_index && CSW_NEEDED(runq, cur_thread)))
	    {
		thread = THREAD_DEQUEUE(runq);
		thread->runq = RUN_QUEUE_HEAD_NULL;
		rqh->count--;
		if (runq->rq_count == 0)
		    RUNQ_BIT_CLEAR(rqh->bitmap, index);
		simple_unlock(&processor->runq.lock);
		simple_unlock(&pset->runq.lock);
		return thread;
	    }
	}

	simple_unlock(&processor->runq.lock);
	simple_unlock(&pset->runq.lock);
    }
#else	/* MACH_IO_BINDING */

#if	NCPUS > 1
	/*
	 *	The only thread that is ever bound to a
	 *	processor is the action thread.  Check
	 *	for it before looking for threads on the
	 *	global run queue.
	 */
	if (processor->bound_thread != THREAD_NULL) {
	    thread_t	thread;

	    processor_lock(processor);
	    if ((thread = processor->bound_thread) != 0) {
		processor->bound_thread = THREAD_NULL;
		processor_unlock(processor);
		return thread;
	    }
	    processor_unlock(processor);
	}
#endif	/* NCPUS > 1 */

	/*
	 *	Run down the list of scheduling policies for
	 *	the processor set, until we find one with
	 *	runnable threads.  Then call its choose_thread
	 *	routine.
	 */
    {
	unsigned int	bitmap;

	simple_lock(&pset->runq.lock);
	if ((bitmap = pset->runq.bitmap) != 0) {
	    /*
	     *	There is a runnable thread.
	     */
	    int		index;
	    run_queue_t	runq;

	    RUNQ_BIT_FIND(bitmap, index);
	    runq = pset->runq.runqs[index];

	    if (index > cur_index ||	/* higher scheduling class */
		(index == cur_index && CSW_NEEDED(runq, cur_thread)))
					/* same class and preempts
					   current thread */
	    {
		/*
		 *	First runnable thread is of higher scheduling
		 *	class, or of the same class and preempts the
		 *	current thread.  Dequeue and return it.
		 */
		thread_t	thread;

		thread = THREAD_DEQUEUE(runq);
		thread->runq = RUN_QUEUE_HEAD_NULL;
		pset->runq.count--;
		if (runq->rq_count == 0)
		    RUNQ_BIT_CLEAR(pset->runq.bitmap, index);
		simple_unlock(&pset->runq.lock);
		return thread;
	    }
	}
    }
#endif	/* MACH_IO_BINDING */

	/*
	 *	No threads to run.  Check whether the current
	 *	thread is still runnable on this processor.
	 */
	if (cur_runnable) {
	    simple_unlock(&pset->runq.lock);

	    thread_sched_lock(cur_thread);
	    if (cur_thread->sched_stamp != sched_tick)
		UPDATE_PRIORITY(cur_thread);
	    thread_sched_unlock(cur_thread);

	    return cur_thread;
	}

	/*
	 *	Nothing is runnable, so set this processor idle if it
	 *	was running.  If it was in an assignment or shutdown,
	 *	leave it alone.  Return its idle thread.
	 */
	if (processor->state == PROCESSOR_RUNNING) {
	    processor->state = PROCESSOR_IDLE;

#if	NCPUS > 1
	    queue_enter_first(&pset->idle_queue, processor,
			processor_t, processor_queue);
	    pset->idle_count++;
#else	/* NCPUS > 1 */
	    pset->idle_count = 1;
#endif	/* NCPUS > 1 */
	}
	simple_unlock(&pset->runq.lock);

	return processor->idle_thread;
}

/*
 *	Check for preemption.
 *
 *	The current thread is always preempted by any thread in
 *	a higher-priority scheduling class.  The scheduler`s
 *	CSW_NEEDED routine checks whether the thread is preempted
 *	by a thread in the same class.  Threads in lower priority
 *	scheduling classes cannot preempt the current thread.
 */
boolean_t csw_needed(
	thread_t	thread,
	processor_t	processor)
{
	run_queue_t	runq;
	int		index, cur_index;
	processor_set_t	pset = processor->processor_set;

	if ((thread->state & TH_SUSP) != 0)
	   return TRUE;

	cur_index = thread->policy_index;

#if	MACH_IO_BINDING
	/*
	 *	Must check both local and global run queues.
	 */
    {
	int	global_index, local_index;

	if (pset->runq.bitmap == 0)
	    global_index = -1;
	else
	    RUNQ_BIT_FIND(pset->runq.bitmap, global_index);
	if (global_index > cur_index)
	    return TRUE;

	if (processor->runq.bitmap == 0)
	    local_index = -1;
	else
	    RUNQ_BIT_FIND(processor->runq.bitmap, local_index);
	if (local_index > cur_index)
	    return TRUE;

	if (global_index == cur_index) {
	    runq = pset->runq.runqs[cur_index];
	    assert(runq->rq_count > 0);
	    if (CSW_NEEDED(runq, thread))
		return TRUE;
	}

	if (local_index == cur_index) {
	    runq = processor->runq.runqs[cur_index];
	    assert(runq->rq_count > 0);
	    if (CSW_NEEDED(runq, thread))
		return TRUE;
	}

	return FALSE;
    }
#else	/* !MACH_IO_BINDING */

#if	NCPUS > 1
	if (processor->bound_thread != THREAD_NULL)
	    return TRUE;
#endif

	if (pset->runq.bitmap != 0) {
	    unsigned int	bitmap;

	    simple_lock(&pset->runq.lock);
	    if ((bitmap = pset->runq.bitmap) != 0) {
		RUNQ_BIT_FIND(bitmap, index);
		if (index > cur_index) {
		    /*
		     * Runnable thread higher policy than current thread
		     */
		    simple_unlock(&pset->runq.lock);
		    return TRUE;
		}
		if (index == cur_index) {
		    runq = pset->runq.runqs[cur_index];
		    assert(runq->rq_count > 0);
		    if (CSW_NEEDED(runq, thread)) {
			/*
			 * Runnable thread same policy as current thread,
			 * and policy says it`s higher priority
			 */
			simple_unlock(&pset->runq.lock);
			return TRUE;
		    }
		}
	    }
	    simple_unlock(&pset->runq.lock);
	}
	return FALSE;

#endif	/* !MACH_IO_BINDING */
}

/*
 *	This is the idle thread, which just looks for other threads
 *	to execute.
 */

no_return idle_thread_continue(void)
{
	register processor_t myprocessor;
	register thread_t volatile *threadp;
	register thread_t new_thread;
	int mycpu;
	spl_t s;

	mycpu = cpu_number();
	myprocessor = processor_ptr[mycpu];
	threadp = (thread_t volatile *) &myprocessor->next_thread;

	while (TRUE) {

#ifdef	MARK_CPU_IDLE
	    MARK_CPU_IDLE(mycpu);
#endif	/* MARK_CPU_IDLE */

	    /*
	     *	This cpu will be dispatched (by thread_setrun) by setting
	     *	next_thread to the value of the thread to run next.
	     */

	    while (*threadp == THREAD_NULL) {
		/*
		 * check for kernel ASTs while we wait
		 */
		AST_KERNEL_CHECK(mycpu);

		/*
		 * machine_idle is a machine dependent function,
		 * to conserve power.
		 */
#if	POWER_SAVE
		machine_idle(mycpu);
#endif /* POWER_SAVE */
	    }

#ifdef	MARK_CPU_ACTIVE
	    MARK_CPU_ACTIVE(mycpu);
#endif	/* MARK_CPU_ACTIVE */

	    s = splsched();

	    switch (myprocessor->state) {
		case PROCESSOR_DISPATCHING:
		    /*
		     *	Common case -- cpu dispatched.
		     *	Mark it running.
		     */
		    myprocessor->state = PROCESSOR_RUNNING;

		    /* fall through to... */

		case PROCESSOR_ASSIGN:
		case PROCESSOR_SHUTDOWN:
		    /*
		     *	Changing processor sets, or going off-line.
		     */
		    new_thread = *threadp;
		    *threadp = THREAD_NULL;

		    /*
		     *  Just use set quantum.  No point in
		     *  checking for shorter local runq quantum;
		     *  csw_needed will handle correctly.
		     */
#if	MACH_HOST
		    myprocessor->quantum = 
			new_thread->processor_set->set_quantum;
#else	/* MACH_HOST */
		    myprocessor->quantum = default_pset.set_quantum;
#endif	/* MACH_HOST */
		    myprocessor->first_quantum = TRUE;
		    counter(c_idle_thread_handoff++);
		    thread_run_noreturn(idle_thread_continue, new_thread);
		    /*NOTREACHED*/

		default:
		    panic("Idle thread: bad processor state %d (Cpu %d)\n",
			  myprocessor->state, mycpu);
	    }

	    splx(s);
	}
}

no_return idle_thread(void)
{
	/*
	 * thread_block() to set processor->state = PROCESSOR_STATE_IDLE
	 * when we run next time.
	 */
	counter(c_idle_thread_block++);
	thread_block_noreturn(idle_thread_continue);
	/*NOTREACHED*/
}

/*
 *	Create the idle thread for a CPU.
 */
void idle_thread_create(
	processor_t	processor)
{
	thread_t	thread;

	/*
	 *	Create the thread.
	 */
	(void) thread_create(kernel_task, &thread);

	/*
	 *	Set it to the idle policy,
	 *	though it won`t really run it.
	 */
	thread->sched_policy = sched_policy_lookup(POLICY_BACKGROUND);
	thread->cur_policy   = thread->sched_policy;
	thread->policy_index = thread->sched_policy->rank;

	thread_start(thread, idle_thread);
						/* start at idle thread */
	stack_privilege(thread);		/* give it a stack to keep */

	processor->idle_thread = thread;	/* make it this processor`s
						   idle thread */

	thread->state |= TH_RUN | TH_IDLE;	/* mark it as running and
						   idle so that */
	(void) thread_resume(thread);		/* this won`t put it on
						   the run queues */
}

#if	NCPUS > 1
/*
 *	thread_bind:
 *
 *	Force a thread to execute on the specified processor.
 *	If the thread is currently executing, it may wait until its
 *	time slice is up before switching onto the specified processor.
 *
 *	A processor of PROCESSOR_NULL causes the thread to be unbound.
 *	xxx - DO NOT export this to users.
 *
 *	Binding a thread to a particular processor temporarily switches
 *	the thread to running under the BP (bound_processor) scheduling
 *	policy.  Unbinding the thread lets it run its normal policy.
 *
 *	NOTE that this won`t work if a bound thread can be depressed,
 *	since depressing a thread also temporarily switches its
 *	scheduling policy.  However, on a symmetrical multiprocessor,
 *	the only thread that is ever bound is the action thread.
 *	Fixing this (under MACH_IO_BINDING), as well as dealing with
 *	the case of a thread that must be bound to a processor that
 *	is not in its processor set, is left as an exercise for the
 *	reader.
 */
void thread_bind(
	register thread_t	thread,
	processor_t		processor)
{
	spl_t	s;

	s = splsched();
	thread_sched_lock(thread);

	thread->bound_processor = processor;

	thread_sched_unlock(thread);
	splx(s);
}
#endif	/* NCPUS > 1 */

