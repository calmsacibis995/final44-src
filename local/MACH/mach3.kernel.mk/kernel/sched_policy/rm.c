/* 
 * Mach Operating System
 * Copyright (c) 1994,1993,1992 Carnegie Mellon University
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
 * $Log:	rm.c,v $
 * Revision 2.3  94/12/16  11:20:49  dbg
 * 	Renamed 'time_spec' to 'timespec'.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  18:38:18  dbg
 * 	Add per-policy scheduling parameters to thread and run queue.
 * 	[93/05/10            dbg]
 * 
 * 	Moved common operations to kern/run_queues.c.
 * 	[93/04/10            dbg]
 * 
 * 	Converted to per-policy run queue structure.
 * 	[93/04/09            dbg]
 * 
 * 	Merged into microkernel mainline.
 * 
 * 	Changed period to timespec_t.
 * 	[92/09/06	savage]
 * 	Added policy_init()
 * 	[92/06/01	savage]
 * 	Created 
 * 	[92/05/04	takuro]
 * 
 */

/*
 *	Rate-monotonic scheduling policy.
 *
 *	Threads are scheduled in the order of shortest
 *	period first.
 */
#include <mach_kdb.h>

#include <mach/boolean.h>
#include <mach/timespec.h>
#include <mach/realtime_policy.h>

#include <kern/macro_help.h>
#include <kern/ast.h>
#include <kern/kalloc.h>
#include <kern/run_queues.h>
#include <kern/sched_policy.h>
#include <kern/processor.h>
#include <kern/thread.h>
#include <kern/rt_thread.h>
#include <sched_policy/real_time.h>

/*
 *	Uses a single run queue, ordered by period.
 */
struct rm_run_queue {
	struct run_queue rq;		/* common structure */
	queue_head_t	rm_queue;	/* queue */
};
typedef	struct rm_run_queue *	rm_run_queue_t;

#define	rm_runq(rq)	((struct rm_run_queue *)(rq))
#define	rm_count	rq.rq_count

/*
 *	Choose thread.
 */
thread_t
rm_thread_dequeue(
	run_queue_t	runq)
{
	rm_run_queue_t	rq = rm_runq(runq);
	queue_entry_t	elt;

	assert(rq->rm_count > 0);
	assert(!queue_empty(&rq->rm_queue));

	dequeue_head_macro(&rq->rm_queue, elt);
	rq->rm_count--;

	current_processor()->first_quantum = TRUE;	/* XXX */

	return (thread_t) elt;
}

/*
 *	Put a thread onto a run queue in priority order.
 *	Return whether it can preempt the current thread.
 */
boolean_t rm_thread_enqueue(
	run_queue_t	runq,
	thread_t	thread,
	boolean_t	may_preempt)
{
	register rm_run_queue_t	rq;
	register thread_t	next;
	register queue_t	q;

	rq = rm_runq(runq);

	q = &rq->rm_queue;
	queue_iterate(q, next, thread_t, links) {
	    if (timespec_le(rt_sched(thread)->period,
			      rt_sched(next)->period))
		break;
	}
	enqueue_tail_macro((queue_t) next, (queue_entry_t) thread);
	rq->rm_count++;

	if (!may_preempt)
	    return FALSE;

    {
	thread_t cth = current_thread();

	return !timespec_le(rt_sched(cth)->period,
			      rt_sched(thread)->period);
    }
}

/*
 *	Remove a thread from the run queue.
 */
void rm_thread_remqueue(
	run_queue_t	runq,
	thread_t	thread)
{
	rm_run_queue_t	rq = rm_runq(runq);
		
	remqueue(&rq->rm_queue, (queue_entry_t) thread);
	rq->rm_count--;
}

boolean_t rm_csw_needed(
	run_queue_t	runq,
	thread_t	thread)
{
	rm_run_queue_t	rq = rm_runq(runq);
	thread_t	th;

	th = (thread_t) queue_first(&rq->rm_queue);
	
	return timespec_le(rt_sched(th)->period,
			     rt_sched(thread)->period);
}

extern struct sched_policy	rm_sched_policy;	/* forward */

run_queue_t
rm_run_queue_alloc(void)
{
	rm_run_queue_t	rq;

	rq = (rm_run_queue_t) kalloc(sizeof(struct rm_run_queue));
	run_queue_init(&rq->rq, &rm_sched_policy);

	queue_init(&rq->rm_queue);

	return &rq->rq;
}

void
rm_run_queue_free(
	run_queue_t	runq)
{
	kfree((vm_offset_t) runq, sizeof(struct rm_run_queue));
}

#if	MACH_KDB
#include <ddb/db_output.h>
void rm_thread_db_print(
	thread_t	thread)
{
	db_printf("RM     ");
}
#endif

/*
 *	Statically allocated policy structure.
 */
struct sched_policy	rm_sched_policy = {
    {
	/* sched_ops */
	rm_thread_dequeue,
	rm_thread_enqueue,
	rm_thread_remqueue,

	rm_csw_needed,
	ast_check,
	0,			/* no update_priority */

	rm_run_queue_alloc,
	rm_run_queue_free,

	rt_runq_set_limit,
	rt_runq_get_limit,
	rt_thread_set_limit,
	rt_thread_set_param,
	rt_thread_get_param,
	rt_task_set_param,
	rt_task_get_param,

#if	MACH_KDB
	rm_thread_db_print
#endif

    },
	POLICY_RATE_MONOTONIC,
	"rate monotonic"
};

