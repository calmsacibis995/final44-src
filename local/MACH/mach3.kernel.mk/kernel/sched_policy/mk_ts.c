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
 * $Log:	mk_ts.c,v $
 * Revision 2.3  94/12/16  11:20:12  dbg
 * 	Made 'background' policy be the same as the lowest possible
 * 	timesharing priority.  Since depressed threads use the
 * 	background policy, they must not be scheduled at a lower
 * 	priority than a spinning timesharing thread, or they will never
 * 	run.  (This is needed to keep CThreads working, and perhaps
 * 	other packages).
 * 	[94/07/14            dbg]
 * 
 * 	CSW_NEEDED is called with pset->runq locked.
 * 	[94/03/16            dbg]
 * 
 * 	Replaced count in run_queue_head structure by bitmap of policies
 * 	with runnable threads.  Removed spls from ts_clock_sched; it is
 * 	always called at splsched.
 * 	[94/03/09            dbg]
 * 
 * Revision 2.2  93/11/17  18:37:33  dbg
 * 	Break up thread lock.
 * 	[93/05/26            dbg]
 * 
 * 	Add per-policy scheduling parameters to thread and run queue.
 * 	[93/05/10            dbg]
 * 
 * 	Moved common operations to kern/run_queues.c.
 * 	[93/04/10            dbg]
 * 
 * 	Converted to per-policy run queue structure.
 * 	[93/04/06            dbg]
 * 
 * 	Always enable fixed-priority threads.
 * 	[93/03/27            dbg]
 * 
 * 	Merged back into microkernel mainline.  Simplfied idle-processor
 * 	logic for single CPU.
 * 
 * 	Added policy_init()
 * 	[92/06/01	savage]
 * 	Copied from kern/sched_prim.c
 * 	[92/02/01	savage]
 * 
 */

#include <mach_host.h>
#include <mach_io_binding.h>
#include <stat_time.h>

#include <mach/boolean.h>

#include <kern/macro_help.h>
#include <kern/ast.h>
#include <kern/kalloc.h>
#include <kern/kern_io.h>
#include <kern/processor.h>
#include <kern/run_queues.h>
#include <kern/sched.h>			/* sched_tick */
#include <kern/sched_policy.h>
#include <kern/thread.h>

#include <sched_policy/standard.h>

#include <machine/machspl.h>

/*
 *	Timesharing policy.
 */

/*
 *	Uses 32 run queues, with a low marker.
 */
#define	MAX_PRIORITY	31		/* priorities 0..31 */

#define	NRQS		(MAX_PRIORITY+1)
struct ts_run_queue {
	struct run_queue rq;		/* common structure */
	queue_head_t	ts_queue[NRQS];
	int		ts_low;		/* hint */
	int		ts_max_priority;
					/* limits for policy */
};
typedef	struct ts_run_queue *	ts_run_queue_t;

#define	ts_runq(rq)	((struct ts_run_queue *)(rq))
#define	ts_count	rq.rq_count

/*
 *	Per-thread scheduling fields:
 */
struct ts_sched_data {
	int	max_priority;		/* maximum priority */
	int	base_priority;		/* base priority */
	int	sched_priority;		/* current priority */
};

#define	ts_sched(th)	((struct ts_sched_data *)&(th)->sched_data)

extern struct sched_policy	ts_sched_policy;	/* forward */

/*
 *	Choose thread.
 */
thread_t
ts_thread_dequeue(
	run_queue_t	runq)
{
	ts_run_queue_t	rq = ts_runq(runq);
	int		low;
	queue_t		q;
	queue_entry_t	elt;
	processor_t	processor;

	assert(rq->ts_count > 0);

	for (low = rq->ts_low, q = &rq->ts_queue[low];
	      low < NRQS;
	      low++, q++)
	{
	    if (!queue_empty(q)) {
		dequeue_head_macro(q, elt);
		rq->ts_count--;
		rq->ts_low = low;

		processor = current_processor();
		processor->quantum = processor->processor_set->set_quantum;
		processor->first_quantum = TRUE;

		return (thread_t) elt;
	    }
	}
	panic("ts_choose_thread");
}

/*
 *	Put a thread onto a run queue.
 *	Return whether it can preempt the currently
 *	running thread.
 */
boolean_t ts_thread_enqueue(
	run_queue_t	runq,
	thread_t	th,
	boolean_t	may_preempt)
{
	register ts_run_queue_t	rq;
	register unsigned int	whichq;
	register queue_t	q;

	whichq = ts_sched(th)->sched_priority;
	if (whichq >= NRQS) {
	    printf("ts_thread_setrun: pri too high (%d)\n", whichq);
	    whichq = NRQS - 1;
	}

	rq = ts_runq(runq);

	q = &rq->ts_queue[whichq];
	enqueue_tail_macro(q, (queue_entry_t) th);

	if (whichq < rq->ts_low || rq->ts_count == 0)
	    rq->ts_low = whichq;	/* minimize */
	rq->ts_count++;

	if (!may_preempt)
	    return FALSE;

	return ts_sched(th)->sched_priority
	     <= ts_sched(current_thread())->sched_priority;
}

void
ts_thread_remqueue(
	run_queue_t	runq,
	thread_t	thread)
{
	ts_run_queue_t	rq = ts_runq(runq);
		
	remqueue(&rq->ts_queue[0], (queue_entry_t) thread);
	rq->ts_count--;
}

boolean_t ts_csw_needed(
	run_queue_t	runq,
	thread_t	thread)
{
	ts_run_queue_t	rq = ts_runq(runq);
	queue_t		q;

	if (current_processor()->first_quantum)
	    return FALSE;

	/*
	 *	Check whether low hint is accurate.
	 */
	q = rq->ts_queue + *(volatile int *)&rq->ts_low;
	if (queue_empty(q)) {
	    register int i;

	    q = rq->ts_queue + rq->ts_low;
	    if (rq->ts_count > 0) {
		for (i = rq->ts_low; i < NRQS; i++) {
		    if (!queue_empty(q))
			break;
		    q++;
		}
		rq->ts_low = i;
	    }
	}
	return rq->ts_low <= ts_sched(thread)->sched_priority;
}

/*
 *	Set scheduling limit value for processor set.
 */
kern_return_t
ts_runq_set_limit(
	run_queue_t	runq,
	policy_param_t	limit,
	natural_t	count)
{
	int	max_priority;

	if (count == 0) {
	    /*
	     *	Use default value for max priority.
	     */
	    max_priority = TS_BASEPRI_USER;
	}
	else {
	    if (count < POLICY_PARAM_TIMESHARE_COUNT)
		return KERN_INVALID_ARGUMENT;

	    max_priority = ((struct policy_param_timeshare *)limit)->priority;
	    if (max_priority < 0 || max_priority > MAX_PRIORITY)
		return KERN_INVALID_ARGUMENT;
	}

	ts_runq(runq)->ts_max_priority = max_priority;
	return KERN_SUCCESS;
}

/*
 *	Get scheduling limit value for processor set.
 */
kern_return_t
ts_runq_get_limit(
	run_queue_t	runq,
	policy_param_t	limit,
	natural_t	*count)
{
	if (*count < POLICY_PARAM_TIMESHARE_COUNT)
	    return KERN_INVALID_ARGUMENT;

	((struct policy_param_timeshare *)limit)->priority
		= ts_runq(runq)->ts_max_priority;
	*count = POLICY_PARAM_TIMESHARE_COUNT;
	return KERN_SUCCESS;
}

kern_return_t
ts_thread_set_limit(
	thread_t	thread,
	policy_param_t	limit,
	natural_t	count)
{
	int	max_priority;

	if (count < POLICY_PARAM_TIMESHARE_COUNT)
	    return KERN_INVALID_ARGUMENT;

	max_priority = ((struct policy_param_timeshare *)limit)->priority;
	if (max_priority < 0 || max_priority > MAX_PRIORITY)
	    return KERN_INVALID_ARGUMENT;

	ts_sched(thread)->max_priority = max_priority;
	return KERN_SUCCESS;
}

/*
 *	Set the scheduling parameters for a thread.  If they
 *	are not supplied, the thread`s current parameters
 *	are used if 'new_policy' is FALSE; otherwise, per-
 *	policy defaults are used.  If 'new_policy' is FALSE,
 *	limit values are taken from the thread`s processor
 *	set; otherwise, the thread`s current limit values
 *	are used.  If 'check_limits' is TRUE, returns an
 *	error if parameter values violate the limits; otherwise,
 *	the limits are silently enforced.
 */
kern_return_t
ts_thread_set_param(
	thread_t	thread,
	policy_param_t	param,
	natural_t	count,
	boolean_t	new_policy,
	boolean_t	check_limits)
{
	int	base_priority;
	int	max_priority;
	int	pset_max_priority;

	pset_max_priority =
	    ts_runq(thread->processor_set->runq.runqs[ts_sched_policy.rank])
		->ts_max_priority;

	if (new_policy) {
	    /*
	     *	Thread is not already running this policy.
	     *	Use default values for parameters and limit.
	     */
	    base_priority = TS_BASEPRI_USER;
	    max_priority  = pset_max_priority;
	}
	else {
	    /*
	     *	Thread is already running policy.  Use
	     *	thread`s current values.
	     */
	    base_priority = ts_sched(thread)->base_priority;
	    max_priority = ts_sched(thread)->max_priority;
	}

	if (count != 0) {
	    /*
	     *	Parameters supplied: use it for scheduling parameters.
	     */
	    assert(count >= POLICY_PARAM_TIMESHARE_COUNT);
	    base_priority =
		((struct policy_param_timeshare *)param)->priority;
	    if (base_priority < 0 || base_priority > MAX_PRIORITY)
	        return KERN_INVALID_ARGUMENT;
	}

	if (check_limits) {
	    /*
	     *	Error if parameters violate limits.
	     */
	    if (base_priority < max_priority)
		return KERN_FAILURE;
	}
	else {
	    /*
	     *	Validate current (or default)
	     *	parameters against limits.
	     */
	    if (max_priority < pset_max_priority)
		max_priority = pset_max_priority;
	    if (base_priority < max_priority)
		base_priority = max_priority;
	}

	ts_sched(thread)->base_priority = base_priority;
	ts_sched(thread)->max_priority  = max_priority;

	return KERN_SUCCESS;
}

kern_return_t
ts_thread_get_param(
	thread_t	thread,
	policy_param_t	param,	/* data and limits */
	natural_t	*count)
{
	struct policy_info_timeshare	*pi;

	if (*count < POLICY_INFO_TIMESHARE_COUNT)
	    return KERN_INVALID_ARGUMENT;

	pi = (struct policy_info_timeshare *)param;

	pi->base_priority = ts_sched(thread)->base_priority;
	pi->cur_priority  = ts_sched(thread)->sched_priority;
	pi->max_priority  = ts_sched(thread)->max_priority;
	*count = POLICY_INFO_TIMESHARE_COUNT;

	return KERN_SUCCESS;
}

/*
 *	Set the default scheduling parameters for a task,
 *	to be used for newly created threads.
 */
kern_return_t
ts_task_set_param(
	task_t		task,
	policy_param_t	param,
	natural_t	count)
{
	int		priority;

	if (count == 0) {
	    /*
	     *	Use default value for priority.
	     */
	    priority = TS_BASEPRI_USER;
	}
	else {
	    if (count < POLICY_PARAM_TIMESHARE_COUNT)
		return KERN_INVALID_ARGUMENT;

	    priority = ((struct policy_param_timeshare *)param)->priority;
	    if (priority < 0 || priority > MAX_PRIORITY)
		return KERN_INVALID_ARGUMENT;
	}

	((struct policy_param_timeshare *)&task->sched_data)
		->priority = priority;
	task->sched_data_count = POLICY_PARAM_TIMESHARE_COUNT;

	return KERN_SUCCESS;
}

/*
 *	Get the default scheduling parameters for a task.
 */
kern_return_t
ts_task_get_param(
	task_t		task,
	policy_param_t	param,
	natural_t	*count)
{
	if (*count < POLICY_PARAM_TIMESHARE_COUNT)
	    return KERN_INVALID_ARGUMENT;

	((struct policy_param_timeshare *)param)->priority =
		((struct policy_param_timeshare *)&task->sched_data)
			->priority;
	*count = POLICY_PARAM_TIMESHARE_COUNT;

	return KERN_SUCCESS;
}

run_queue_t
ts_run_queue_alloc(void)
{
	ts_run_queue_t	rq;
	int		i;

	rq = (ts_run_queue_t) kalloc(sizeof(struct ts_run_queue));

	run_queue_init(&rq->rq, &ts_sched_policy);

	for (i = 0; i < NRQS; i++)
	    queue_init(&rq->ts_queue[i]);
	rq->ts_low = NRQS;

	return &rq->rq;
}

void
ts_run_queue_free(
	run_queue_t	runq)
{
	kfree((vm_offset_t) runq, sizeof(struct ts_run_queue));
}

#if	MACH_KDB
#include <ddb/db_output.h>
void
ts_thread_db_print(
	thread_t	thread)
{
	db_printf("TS  %3d", ts_sched(thread)->sched_priority);
}
#endif

/*
 *	Statically allocated policy structure.
 */
void ts_clock_sched(
	thread_t	thread,
	boolean_t	end_quantum);	/* forward */
void ts_update_priority(
	thread_t	thread);	/* forward */

struct sched_policy	ts_sched_policy = {
    {
	/* sched_ops */
	ts_thread_dequeue,
	ts_thread_enqueue,
	ts_thread_remqueue,

	ts_csw_needed,
	ts_clock_sched,
	ts_update_priority,

	ts_run_queue_alloc,
	ts_run_queue_free,

	ts_runq_set_limit,
	ts_runq_get_limit,
	ts_thread_set_limit,
	ts_thread_set_param,
	ts_thread_get_param,
	ts_task_set_param,
	ts_task_get_param,

#if	MACH_KDB
	ts_thread_db_print
#endif
    },
	POLICY_TIMESHARE,
	"ts_timeshare"
};

/*
 ****************************************************************
 *
 *	Priority aging routines for Mach timesharing priority.
 *
 ****************************************************************
 */

#if	STAT_TIME

/*
 * Statistical timing uses microseconds as timer units.
 * 18 bit shift yields priorities.  PRI_SHIFT_2 isn`t needed.
 *
 * pri = usecs >> 18 == usecs / 2**18 ~= usecs / 250000;
 * i.e. 1 priority level = 1/4 second
 */
#define	PRI_SHIFT	18

#else	/* STAT_TIME */

/*
 * Otherwise machine provides shifts based on time units it uses.
 */
#include <machine/sched_param.h>

#endif	/* STAT_TIME */

/*
 *	thread_timer_delta macro takes care of both thread timers.
 */

#define thread_timer_delta(thread)  				\
MACRO_BEGIN							\
	register unsigned	delta;				\
								\
	delta = 0;						\
	TIMER_DELTA((thread)->system_timer,			\
		(thread)->system_timer_save, delta);		\
	TIMER_DELTA((thread)->user_timer,			\
		(thread)->user_timer_save, delta);		\
	(thread)->cpu_delta += delta;				\
	(thread)->sched_delta += delta * 			\
			(thread)->processor_set->sched_load;	\
MACRO_END

/*
 *	Shift structures for holding update shifts.  Actual computation
 *	is  usage = (usage >> shift1) +/- (usage >> abs(shift2))  where the
 *	+/- is determined by the sign of shift 2.
 */
struct shift {
	int	shift1;
	int	shift2;
};

typedef	struct shift	*shift_t, shift_data_t;

/*
 *	USAGE_THRESHOLD is the amount by which usage must change to
 *	cause a priority shift that moves a thread between run queues.
 *	It has an additional fudge factor (* 4) to slow down context
 *	switches.
 *
 *	PRI_USAGE is the priority shift resulting from an amount
 *	of CPU usage.
 *
 *	PRI_SHIFT and PRI_SHIFT_2 convert from usage to priorities.
 *	SCHED_SHIFT converts for the scaling of the sched_usage field
 *	by SCHED_SCALE.  This scaling comes from the multiplication
 *	by sched_load in thread_timer_delta.  sched_load is calculated
 *	as a scaled overload factor in compute_mach_factor.
 */

#define	USAGE_THRESHOLD_FACTOR	4

#ifdef	PRI_SHIFT_2
#if	PRI_SHIFT_2 > 0
#define	PRI_USAGE(usage) \
	(   (usage) >> (SCHED_SHIFT + PRI_SHIFT) \
	  + (usage) >> (SCHED_SHIFT + PRI_SHIFT_2) \
	)
#define	USAGE_THRESHOLD \
	( (((1 << PRI_SHIFT) + (1 << PRI_SHIFT_2)) << SCHED_SHIFT) \
	  * USAGE_THRESHOLD_FACTOR)

#else	/* PRI_SHIFT_2 > 0 */
#define	PRI_USAGE(usage) \
	(   (usage) >> (SCHED_SHIFT + PRI_SHIFT) \
	  - (usage) >> (SCHED_SHIFT - PRI_SHIFT_2) \
	)
#define	USAGE_THRESHOLD \
	( (((1 << PRI_SHIFT) - (1 << -(PRI_SHIFT_2))) << SCHED_SHIFT) \
	  * USAGE_THRESHOLD_FACTOR)

#endif	/* PRI_SHIFT_2 > 0 */

#else	/* PRI_SHIFT_2 */
#define	PRI_USAGE(usage) \
	(   (usage) >> (SCHED_SHIFT + PRI_SHIFT) \
	)
#define USAGE_THRESHOLD	\
	( (1 << (PRI_SHIFT + SCHED_SHIFT)) \
	  * USAGE_THRESHOLD_FACTOR)

#endif	/* PRI_SHIFT_2 */

/*
 *	compute_sched_priority:
 *
 *	Calculate new priority for thread based on its base priority
 *	plus accumulated usage.  PRI_SHIFT and PRI_SHIFT_2 convert
 *	from usage to priorities.  SCHED_SHIFT converts for the scaling
 *	of the sched_usage field by SCHED_SCALE.  This scaling comes
 *	from the multiplication by sched_load (thread_timer_delta)
 *	in sched.h.  sched_load is calculated as a scaled overload
 *	factor in compute_mach_factor (mach_factor.c).
 */

#define compute_sched_priority(th)					\
    MACRO_BEGIN								\
	int	pri;							\
	pri = ts_sched(th)->base_priority				\
	    + PRI_USAGE((th)->sched_usage);				\
	if (pri > MAX_PRIORITY)						\
	    pri = MAX_PRIORITY;						\
	ts_sched(th)->sched_priority = pri;				\
    MACRO_END

/*
 *	ts_clock_sched:
 *
 *	Recalculate the quantum and priority for a timesharing
 *	thread.  The priority is recalculated:
 *
 *	1.  Once per second
 *	2.  At the end of the current quantum
 *	3.  When the current usage is above USAGE_THRESHOLD
 */

void ts_clock_sched(
	thread_t	thread,
	boolean_t	end_quantum)
{
	/*
	 * Check for thread priority update.
	 */
	thread_sched_lock(thread);

	if (thread->sched_stamp != sched_tick)		/* 1/second */
	    ts_update_priority(thread);
	else {
	    thread_timer_delta(thread);
	    if (thread->sched_delta >= USAGE_THRESHOLD ||
		end_quantum)
	    {
		thread->sched_usage += thread->sched_delta;
		thread->sched_delta = 0;
		compute_sched_priority(thread);
	    }
	}
	thread_sched_unlock(thread);

	/*
	 * Check for context switch.
	 */
	ast_check(thread, end_quantum);
}

/*
 *	Define shifts for simulating (5/8)**n
 */

shift_data_t	wait_shift[32] = {
	{1,1},{1,3},{1,-3},{2,-7},{3,5},{3,-5},{4,-8},{5,7},
	{5,-7},{6,-10},{7,10},{7,-9},{8,-11},{9,12},{9,-11},{10,-13},
	{11,14},{11,-13},{12,-15},{13,17},{13,-15},{14,-17},{15,19},{16,18},
	{16,-19},{17,22},{18,20},{18,-20},{19,26},{20,22},{20,-22},{21,-27}};

/*
 *	update_priority
 *
 *	Cause the priority computation of a thread that has been 
 *	sleeping or suspended to "catch up" with the system.  Thread
 *	*MUST* be locked by caller.  If thread is running, then this
 *	can only be called by the thread on itself.
 */
void ts_update_priority(
	register thread_t	thread)
{
	register unsigned int	ticks;
	register shift_t	shiftp;

	ticks = sched_tick - thread->sched_stamp;

	assert(ticks != 0);

	/*
	 *	If asleep for more than 30 seconds forget all
	 *	cpu_usage, else catch up on missed aging.
	 *	5/8 ** n is approximated by the two shifts
	 *	in the wait_shift array.
	 */
	thread->sched_stamp += ticks;
	thread_timer_delta(thread);
	if (ticks >  30) {
	    thread->cpu_usage = 0;
	    thread->sched_usage = 0;
	}
	else {
	    thread->cpu_usage += thread->cpu_delta;
	    thread->sched_usage += thread->sched_delta;
	    shiftp = &wait_shift[ticks];
	    if (shiftp->shift2 > 0) {
		thread->cpu_usage =
			(thread->cpu_usage >> shiftp->shift1) +
			(thread->cpu_usage >> shiftp->shift2);
		thread->sched_usage =
			(thread->sched_usage >> shiftp->shift1) +
			(thread->sched_usage >> shiftp->shift2);
	    }
	    else {
		thread->cpu_usage =
			(thread->cpu_usage >> shiftp->shift1) -
			(thread->cpu_usage >> -(shiftp->shift2));
		thread->sched_usage =
			(thread->sched_usage >> shiftp->shift1) -
			(thread->sched_usage >> -(shiftp->shift2));
	    }
	}
	thread->cpu_delta = 0;
	thread->sched_delta = 0;

	/*
	 *	Recompute priority.
	 */
	compute_sched_priority(thread);
}

/*
 *	do_thread_scan: scan for stuck threads.  A thread is stuck if
 *	it is runnable but its priority is so low that it has not
 *	run for several seconds.  Its priority should be higher, but
 *	won't be until it runs and calls update_priority.  The scanner
 *	finds these threads and does the updates.
 *
 *	Scanner runs in two passes.  Pass one squirrels likely
 *	thread ids away in an array, and removes them from the run queue.
 *	Pass two does the priority updates.  This is necessary because
 *	the run queue lock is required for the candidate scan, but
 *	cannot be held during updates [set_pri will deadlock].
 *
 *	Array length should be enough so that restart isn't necessary,
 *	but restart logic is included.  Does not scan processor runqs.
 *
 *	Only scans timesharing run queues.
 *
 */

boolean_t	do_thread_scan_debug = FALSE;

#define	MAX_STUCK_THREADS	16

thread_t	stuck_threads[MAX_STUCK_THREADS];
int		stuck_count = 0;

/*
 *	do_runq_scan is the guts of pass 1.  It scans a runq for
 *	stuck threads.  A boolean is returned indicating whether
 *	it ran out of space.
 */

boolean_t
do_runq_scan(
	run_queue_head_t	runq)
{
	ts_run_queue_t		rq;
	spl_t			s;
	register queue_t	q;
	register thread_t	thread;
	register int		count;

	/*
	 *	Find the timeshare run queue.
	 */
	rq = ts_runq(runq->runqs[ts_sched_policy.rank]);
	if (rq == 0)
	    return FALSE;

	s = splsched();
	simple_lock(&runq->lock);
	if ((count = rq->ts_count) > 0) {
	    q = &rq->ts_queue[rq->ts_low];
	    while (count > 0) {
		thread = (thread_t) queue_first(q);
		while (!queue_end(q, (queue_entry_t) thread)) {
		    /*
		     *	Get the next thread now, since we may
		     *	remove this thread from the run queue.
		     */
		    thread_t next = (thread_t) queue_next(&thread->links);

		    if ((thread->state & TH_SCHED_STATE) == TH_RUN &&
			sched_tick - thread->sched_stamp > 1)
		    {
			/*
			 *	Stuck, save its id for later.
			 */
			if (stuck_count == MAX_STUCK_THREADS) {
			    /*
			     *	!@#$% No more room.
			     */
			    simple_unlock(&runq->lock);
			    splx(s);
			    return TRUE;
			}

			/*
			 *	We can`t take the thread_lock here,
			 *	since we already have the runq lock.
			 *	So we can`t grab a reference to the
			 *	thread.  However, a thread that is
			 *	in RUN state cannot be deallocated
			 *	until it stops running.  If it isn`t
			 *	on the runq, then thread_halt cannot
			 *	see it.  So we remove the thread
			 *	from the runq to make it safe.
			 */
			remqueue(q, (queue_entry_t) thread);
			rq->ts_count--;
			/* no need to turn off bit -
			   this thread will be put back on the runq */
			thread->runq = RUN_QUEUE_HEAD_NULL;

			stuck_threads[stuck_count++] = thread;

			if (do_thread_scan_debug)
			    printf("do_runq_scan: adding thread %#x\n",
				   (vm_offset_t) thread);

		    }
		    count--;
		    thread = next;
		}
		q++;
	    }
	}
	simple_unlock(&runq->lock);
	splx(s);

	return FALSE;
}

void ts_thread_scan(void)
{
	spl_t			s;
	register boolean_t	restart_needed = FALSE;
	register thread_t	thread;
#if	MACH_HOST
	register processor_set_t	pset;
#endif	/* MACH_HOST */

	do {
#if	MACH_HOST
	    simple_lock(&all_psets_lock);
	    queue_iterate(&all_psets, pset, processor_set_t, all_psets) {
		restart_needed = do_runq_scan(&pset->runq);
		if (restart_needed)
			break;
	    }
	    simple_unlock(&all_psets_lock);
#else	/* MACH_HOST */
	    restart_needed = do_runq_scan(&default_pset.runq);
#endif	/* MACH_HOST */

#if	MACH_IO_BINDING
	    if (!restart_needed)
	    	restart_needed = do_runq_scan(&master_processor->runq);
#endif

	    /*
	     *	Ok, we now have a collection of candidates -- fix them.
	     */

	    while (stuck_count > 0) {
		thread = stuck_threads[--stuck_count];
		stuck_threads[stuck_count] = THREAD_NULL;
		s = splsched();
		thread_sched_lock(thread);
		if ((thread->state & TH_SCHED_STATE) == TH_RUN) {
		    /*
		     *	Call thread_setrun to update the thread`s
		     *	priority and put it back on the run queue.
		     */
		    thread_setrun(thread, TRUE);
		}
		thread_sched_unlock(thread);
		splx(s);
	    }
	} while (restart_needed);
}
		
/*
 *	Background thread scheduling.
 *
 *	Also provides 'null' parameter/limit routines, for policies
 *	that do not have parameters or limits.
 *
 *	The background policy is the same as the lowest possible
 *	timesharing priority.  Since depressed threads use the
 *	background policy, they must not be scheduled at a lower
 *	priority than a spinning timesharing thread, or they will never
 *	run.  (This is needed to keep CThreads working, and perhaps
 *	other packages).
 *
 */

/*
 *	Uses the timesharing run queue.
 */
struct bg_run_queue {
	struct run_queue rq;		/* common structure */
	queue_head_t	bg_queue;
};

/*
 *	The background policy must have NO per-thread scheduling
 *	parameters.  Using background policy for thread depression
 *	assumes that the thread`s per-policy scheduling parameters
 *	will be untouched.
 */

/*
 *	Choose thread - uses timesharing routine.
 */
#define	bg_thread_dequeue	ts_thread_dequeue

/*
 *	Put a thread onto a run queue in priority order.
 *	Return whether it can preempt the current thread.
 *
 *	We use the lowest timesharing queue (NRQS-1).
 */
boolean_t bg_thread_enqueue(
	run_queue_t	runq,
	thread_t	thread,
	boolean_t	may_preempt)
{
	register ts_run_queue_t	rq;
	register queue_t	q;

	rq = ts_runq(runq);

	q = &rq->ts_queue[NRQS-1];
	enqueue_tail_macro(q, (queue_entry_t) thread);

	if (NRQS-1 < rq->ts_low || rq->ts_count == 0)
	    rq->ts_low = NRQS-1;	/* minimize */
	rq->ts_count++;

	return FALSE;	/* never preempts */
}

/*
 *	Remqueue uses timesharing routine.
 */
#define	bg_thread_remqueue	ts_thread_remqueue

/*
 *	Context switch check uses timesharing routine.
 */
#define	bg_csw_needed		ts_csw_needed

kern_return_t
null_runq_set_limit(
	run_queue_t	runq,
	policy_param_t	limit,
	natural_t	count)
{
	if (count == 0)
	    return KERN_SUCCESS;
	return KERN_FAILURE;	/* no parameters */
}

kern_return_t
null_runq_get_limit(
	run_queue_t	runq,
	policy_param_t	limit,
	natural_t	*count)
{
	*count = 0;
	return KERN_SUCCESS;
}

kern_return_t
null_thread_set_limit(
	thread_t	thread,
	policy_param_t	limit,
	natural_t	count)
{
	if (count == 0)
	    return KERN_SUCCESS;
	return KERN_FAILURE;		/* no parameters */
}

kern_return_t
null_thread_set_param(
	thread_t	thread,
	policy_param_t	param,
	natural_t	count,
	boolean_t	new_policy,
	boolean_t	check_limits)
{
	if (count == 0)
	    return KERN_SUCCESS;
	return KERN_FAILURE;		/* no parameters */
}

kern_return_t
null_thread_get_param(
	thread_t	thread,
	policy_param_t	param,
	natural_t	*count)
{
	*count = 0;
	return KERN_SUCCESS;
}

kern_return_t
null_task_set_param(
	task_t		task,
	policy_param_t	param,
	natural_t	count)
{
	if (count == 0)
	    return KERN_SUCCESS;
	return KERN_FAILURE;		/* no parameters */
}

kern_return_t
null_task_get_param(
	task_t		task,
	policy_param_t	param,
	natural_t	*count)
{
	*count = 0;
	return KERN_SUCCESS;
}

/*
 *	The background policy shares its run queues
 *	with the timesharing policy.
 */

#if	MACH_KDB
#include <ddb/db_output.h>
void bg_thread_db_print(
	thread_t	thread)
{
	db_printf("BG     ");
}
#endif

/*
 *	Statically allocated policy structure.
 */
struct sched_policy	bg_sched_policy = {
    {
	/* sched_ops */
	bg_thread_dequeue,
	bg_thread_enqueue,
	bg_thread_remqueue,

	bg_csw_needed,
	ast_check,
	0,			/* no update_priority */

	0,			/* no run_queue_alloc */
	0,			/* no run_queue_free */

	null_runq_set_limit,
	null_runq_get_limit,
	null_thread_set_limit,
	null_thread_set_param,
	null_thread_get_param,
	null_task_set_param,
	null_task_get_param,

#if	MACH_KDB
	bg_thread_db_print
#endif
    },
	POLICY_BACKGROUND,
	"background"
};

