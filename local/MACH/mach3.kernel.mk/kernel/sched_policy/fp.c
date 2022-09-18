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
 * $Log:	fp.c,v $
 * Revision 2.2  93/11/17  18:37:18  dbg
 * 	Add per-policy scheduling parameters to thread and run queue.
 * 	[93/05/10            dbg]
 * 
 * 	Moved common operations to kern/run_queues.c.
 * 	[93/04/10            dbg]
 * 
 * 	Converted to per-policy run queue structure.  Merged round-robin
 * 	and fifo scheduling: difference is selected per-thread.
 * 	[93/04/09            dbg]
 * 
 * 	Merged into microkernel mainline.
 * 
 * 	Added policy_init()
 * 	[92/06/01	savage]
 * 	Created from kern/sched_prim.c and tatsuo's sched_misc.c
 * 	[92/02/01	savage]
 * 
 */

/*
 *	Fixed priority scheduling.
 */
#include <cpus.h>
#include <mach_host.h>
#include <mach_kdb.h>
#include <mach_io_binding.h>

#include <mach/boolean.h>
#include <mach/kern_return.h>

#include <kern/ast.h>
#include <kern/kalloc.h>
#include <kern/kern_io.h>
#include <kern/run_queues.h>
#include <kern/sched_policy.h>
#include <kern/processor.h>
#include <kern/thread.h>

#include <sched_policy/standard.h>

/*
 *	Fixed-priority policy.
 *	A thread may select itself to be preemptable (round-robin)
 *	or not (first-come-first-served).
 */

/*
 *	Uses 32 run queues, with a low marker.
 */
#define	MAX_PRIORITY	31

#define	NRQS		(MAX_PRIORITY + 1)
struct fp_run_queue {
	struct run_queue rq;		/* common structure */
	queue_head_t	fp_queue[NRQS];
	int		fp_low;
	int		fp_max_priority;
};
typedef	struct fp_run_queue *	fp_run_queue_t;

#define	fp_runq(rq)	((struct fp_run_queue *)(rq))
#define	fp_count	rq.rq_count

/*
 *	Per-thread scheduling fields:
 */
struct fp_sched_data {
	int	max_priority;
	int	base_priority;
	boolean_t no_preempt;
};

#define	fp_sched(th)	((struct fp_sched_data *)&(th)->sched_data)

extern struct sched_policy	fp_sched_policy;	/* forward */

/*
 *	Choose thread.
 */
thread_t
fp_thread_dequeue(
	run_queue_t	runq)
{
	fp_run_queue_t	rq = fp_runq(runq);
	int		low;
	queue_t		q;
	queue_entry_t	elt;
	processor_t	processor;

	assert(rq->fp_count > 0);

	/*
	 *	Low marker is kept accurate.
	 */
	low = rq->fp_low;
	q = &rq->fp_queue[low];
	assert(!queue_empty(q));

	dequeue_head_macro(q, elt);

	if (--rq->fp_count > 0) {
	    /*
	     *	Update low marker.
	     */
	    while (queue_empty(q)) {
		low++;
		q++;
	    }
	    rq->fp_low = low;
	}

	processor = current_processor();
	processor->quantum = processor->processor_set->set_quantum;
	processor->first_quantum = TRUE;

	return (thread_t) elt;
}

/*
 *	Put a thread onto a run queue in priority order.
 *	Return whether it can preempt the current thread.
 */
boolean_t fp_thread_enqueue(
	run_queue_t	runq,
	thread_t	thread,
	boolean_t	may_preempt)
{
	register fp_run_queue_t	rq;
	register unsigned int	whichq;
	register queue_t	q;

	whichq = fp_sched(thread)->base_priority;
	if (whichq >= NRQS) {
	    printf("fp_thread_setrun: pri too high (%d)\n", whichq);
	    whichq = NRQS - 1;
	}

	rq = fp_runq(runq);

	q = &rq->fp_queue[whichq];
	enqueue_tail_macro(q, (queue_entry_t) thread);

	if (whichq < rq->fp_low || rq->fp_count == 0)
	    rq->fp_low = whichq;	/* minimize */
	rq->fp_count++;

	if (!may_preempt)
	    return FALSE;

    {
	thread_t cth = current_thread();

	return fp_sched(cth)->base_priority > fp_sched(thread)->base_priority
	    || (fp_sched(cth)->base_priority == fp_sched(thread)->base_priority
		&& !fp_sched(cth)->no_preempt);
    }
}

/*
 *	Remove a thread from the run queue.
 */
void fp_thread_remqueue(
	run_queue_t	runq,
	thread_t	thread)
{
	fp_run_queue_t	rq = fp_runq(runq);
		
	remqueue(&rq->fp_queue[0], (queue_entry_t) thread);
	rq->fp_count--;
}

boolean_t fp_csw_needed(
	run_queue_t	runq,
	thread_t	thread)
{
	fp_run_queue_t	rq = fp_runq(runq);

	if (rq->fp_low < fp_sched(thread)->base_priority)
	    return TRUE;

	if (rq->fp_low > fp_sched(thread)->base_priority)
	    return FALSE;

	/* can we be preempted by an equal-priority thread? */

	if (fp_sched(thread)->no_preempt)
	    return FALSE;

	if (current_processor()->first_quantum)
	    return FALSE;

	return TRUE;
}

/*
 *	Set scheduling limit value for processor set.
 */
kern_return_t
fp_runq_set_limit(
	run_queue_t	runq,
	policy_param_t	limit,
	natural_t	count)
{
	int	max_priority;

	if (count == 0) {
	    /*
	     *	Default value for max priority.
	     *	Use 0 for fixed priority.
	     */
	    max_priority = 0;
	}
	else {
	    if (count < POLICY_PARAM_FIXEDPRI_COUNT)
		return KERN_INVALID_ARGUMENT;

	    max_priority = ((struct policy_param_fixedpri *)limit)->priority;
	    if (max_priority < 0 || max_priority > MAX_PRIORITY)
		return KERN_INVALID_ARGUMENT;
	}

	fp_runq(runq)->fp_max_priority = max_priority;
	return KERN_SUCCESS;
}

/*
 *	Get scheduling limit value for processor set.
 */
kern_return_t
fp_runq_get_limit(
	run_queue_t	runq,
	policy_param_t	limit,
	natural_t	*count)
{
	if (*count < POLICY_PARAM_FIXEDPRI_COUNT)
	    return KERN_INVALID_ARGUMENT;

	((struct policy_param_fixedpri *)limit)->priority
		= fp_runq(runq)->fp_max_priority;
	((struct policy_param_fixedpri *)limit)->no_preempt = TRUE;
	*count = POLICY_PARAM_FIXEDPRI_COUNT;
	return KERN_SUCCESS;
}

kern_return_t
fp_thread_set_limit(
	thread_t	thread,
	policy_param_t	limit,
	natural_t	count)
{
	int	max_priority;

	if (count < POLICY_PARAM_FIXEDPRI_COUNT)
	    return KERN_INVALID_ARGUMENT;

	max_priority = ((struct policy_param_fixedpri *)limit)->priority;
	if (max_priority < 0 || max_priority > MAX_PRIORITY)
	    return KERN_INVALID_ARGUMENT;

	fp_sched(thread)->max_priority = max_priority;
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
fp_thread_set_param(
	thread_t	thread,
	policy_param_t	param,
	natural_t	count,
	boolean_t	new_policy,
	boolean_t	check_limits)
{
	int		base_priority;
	int		max_priority;
	int		pset_max_priority;
	boolean_t	no_preempt;

	pset_max_priority =
	    fp_runq(thread->processor_set->runq.runqs[fp_sched_policy.rank])
		->fp_max_priority;

	if (new_policy) {
	    /*
	     *	Thread is not already running this policy.
	     *	Use default values for parameters and limit.
	     */
	    base_priority = FP_BASEPRI_USER;
	    max_priority  = pset_max_priority;
	    no_preempt = FALSE;
	}
	else {
	    /*
	     *	Thread is already running policy.  Use
	     *	thread`s current values.
	     */
	    base_priority = fp_sched(thread)->base_priority;
	    max_priority = fp_sched(thread)->max_priority;
	    no_preempt = fp_sched(thread)->no_preempt;
	}

	if (count != 0) {
	    /*
	     *	Data supplied: use it for scheduling parameters.
	     */
	    struct policy_param_fixedpri *pd;

	    if (count < POLICY_PARAM_FIXEDPRI_COUNT)
		return KERN_INVALID_ARGUMENT;

	    pd = (struct policy_param_fixedpri *)param;

	    base_priority = pd->priority;
	    if (base_priority < 0 || base_priority > MAX_PRIORITY)
	        return KERN_INVALID_ARGUMENT;
	    no_preempt = (pd->no_preempt != 0);
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

	fp_sched(thread)->base_priority = base_priority;
	fp_sched(thread)->max_priority  = max_priority;
	fp_sched(thread)->no_preempt	= no_preempt;

	return KERN_SUCCESS;
}

kern_return_t
fp_thread_get_param(
	thread_t	thread,
	policy_param_t	param,		/* params and limits */
	natural_t	*count)
{
	struct policy_info_fixedpri	*pi;

	if (*count < POLICY_INFO_FIXEDPRI_COUNT)
	    return KERN_INVALID_ARGUMENT;

	pi = (struct policy_info_fixedpri *)param;

	pi->priority 	= fp_sched(thread)->base_priority;
	pi->no_preempt	= fp_sched(thread)->no_preempt;
	pi->max_priority= fp_sched(thread)->max_priority;
	*count = POLICY_INFO_FIXEDPRI_COUNT;

	return KERN_SUCCESS;
}

/*
 *	Set the default scheduling parameters for a task,
 *	to be used for newly created threads.
 */
kern_return_t
fp_task_set_param(
	task_t		task,
	policy_param_t	param,
	natural_t	count)
{
	int		priority;
	boolean_t	no_preempt;

	if (count == 0) {
	    /*
	     *	Use default value for priority.
	     */
	    priority = FP_BASEPRI_USER;
	    no_preempt = FALSE;
	}
	else {
	    struct policy_param_fixedpri *pd;

	    if (count < POLICY_PARAM_FIXEDPRI_COUNT)
		return KERN_INVALID_ARGUMENT;

	    pd = (struct policy_param_fixedpri *)param;

	    priority = pd->priority;
	    if (priority < 0 || priority > MAX_PRIORITY)
		return KERN_INVALID_ARGUMENT;
	    no_preempt = (pd->no_preempt != 0);
	}

	((struct policy_param_fixedpri *)&task->sched_data)
		->priority = priority;
	((struct policy_param_fixedpri *)&task->sched_data)
		->no_preempt = no_preempt;
	task->sched_data_count = POLICY_PARAM_FIXEDPRI_COUNT;

	return KERN_SUCCESS;
}

/*
 *	Get the default scheduling parameters for a task.
 */
kern_return_t
fp_task_get_param(
	task_t		task,
	policy_param_t	param,
	natural_t	*count)
{
	struct policy_param_fixedpri	*pi;

	if (*count < POLICY_PARAM_FIXEDPRI_COUNT)
	    return KERN_INVALID_ARGUMENT;

	pi = (struct policy_param_fixedpri *)param;

	pi->priority =
	    ((struct policy_param_fixedpri *)&task->sched_data)->priority;
	pi->no_preempt =
	    ((struct policy_param_fixedpri *)&task->sched_data)->no_preempt;
	*count = POLICY_PARAM_FIXEDPRI_COUNT;

	return KERN_SUCCESS;
}


run_queue_t
fp_run_queue_alloc(void)
{
	fp_run_queue_t	rq;
	int		i;

	rq = (fp_run_queue_t) kalloc(sizeof(struct fp_run_queue));

	run_queue_init(&rq->rq, &fp_sched_policy);

	for (i = 0; i < NRQS; i++)
	    queue_init(&rq->fp_queue[i]);
	rq->fp_low = NRQS;

	return &rq->rq;
}

void
fp_run_queue_free(
	run_queue_t	runq)
{
	kfree((vm_offset_t) runq, sizeof(struct fp_run_queue));
}

#if	MACH_KDB
#include <ddb/db_output.h>
void
fp_thread_db_print(
	thread_t	thread)
{
	db_printf("%4s %2d",
		  (fp_sched(thread)->no_preempt) ? "FIFO" : "RR",
		  fp_sched(thread)->base_priority);
}
#endif

/*
 *	Statically allocated policy structure.
 */
struct sched_policy	fp_sched_policy = {
    {
	/* sched_ops */
	fp_thread_dequeue,
	fp_thread_enqueue,
	fp_thread_remqueue,

	fp_csw_needed,
	ast_check,
	0,			/* no update_priority */

	fp_run_queue_alloc,
	fp_run_queue_free,

	fp_runq_set_limit,
	fp_runq_get_limit,
	fp_thread_set_limit,
	fp_thread_set_param,
	fp_thread_get_param,
	fp_task_set_param,
	fp_task_get_param,

	fp_thread_db_print
    },
	POLICY_FIXEDPRI,
	"fixed priority"
};

