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
 * $Log:	dm.c,v $
 * Revision 2.3  94/12/16  11:04:31  dbg
 * 	Renamed 'time_spec' to 'timespec'.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  18:36:45  dbg
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
 * 	Changed deadline to timespec_t.
 * 	[92/09/06	savage]
 * 	Added policy_init()
 * 	[92/06/01	savage]
 * 	Created 
 * 	[92/05/04	takuro]
 * 
 */

/*
 *	Deadline-monotonic scheduling policy.
 *
 *	Threads are scheduled in the order of shortest
 *	deadline interval first.
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
 *	Uses a single run queue, ordered by deadline interval.
 *	No policy limits.
 */
struct dm_run_queue {
	struct run_queue rq;		/* common structure */
	queue_head_t	dm_queue;	/* queue */
};
typedef	struct dm_run_queue *	dm_run_queue_t;

#define	dm_runq(rq)	((struct dm_run_queue *)(rq))
#define	dm_count	rq.rq_count

/*
 *	Choose thread.
 */
thread_t
dm_thread_dequeue(
	run_queue_t	runq)
{
	dm_run_queue_t	rq = dm_runq(runq);
	queue_entry_t	elt;

	assert(rq->dm_count > 0);
	assert(!queue_empty(&rq->dm_queue));

	dequeue_head_macro(&rq->dm_queue, elt);
	rq->dm_count--;

	current_processor()->first_quantum = TRUE;	/* XXX */

	return (thread_t) elt;
}

/*
 *	Put a thread onto a run queue in priority order.
 *	Return whether it can preempt the current thread.
 */
boolean_t dm_thread_enqueue(
	run_queue_t	runq,
	thread_t	thread,
	boolean_t	may_preempt)
{
	register dm_run_queue_t	rq;
	register thread_t	next;
	register queue_t	q;

	rq = dm_runq(runq);

	q = &rq->dm_queue;
	queue_iterate(q, next, thread_t, links) {
	    if (timespec_le(rt_sched(thread)->deadline,
			      rt_sched(next)->deadline))
		break;
	}
	enqueue_tail_macro((queue_t) next, (queue_entry_t) thread);
	rq->dm_count++;

	if (!may_preempt)
	    return FALSE;

    {
	thread_t cth = current_thread();

	return !timespec_le(rt_sched(cth)->deadline,
			      rt_sched(thread)->deadline);
    }
}

/*
 *	Remove a thread from the run queue.
 */
void dm_thread_remqueue(
	run_queue_t	runq,
	thread_t	thread)
{
	dm_run_queue_t	rq = dm_runq(runq);
		
	remqueue(&rq->dm_queue, (queue_entry_t) thread);
	rq->dm_count--;
}

boolean_t dm_csw_needed(
	run_queue_t	runq,
	thread_t	thread)
{
	dm_run_queue_t	rq = dm_runq(runq);
	thread_t	th;

	th = (thread_t) queue_first(&rq->dm_queue);
	
	return timespec_le(rt_sched(th)->deadline,
			     rt_sched(thread)->deadline);
}

extern struct sched_policy	dm_sched_policy;	/* forward */

run_queue_t
dm_run_queue_alloc(void)
{
	dm_run_queue_t	rq;

	rq = (dm_run_queue_t) kalloc(sizeof(struct dm_run_queue));
	run_queue_init(&rq->rq, &dm_sched_policy);

	queue_init(&rq->dm_queue);

	return &rq->rq;
}

void
dm_run_queue_free(
	run_queue_t	runq)
{
	kfree((vm_offset_t) runq, sizeof(struct dm_run_queue));
}

#if	MACH_KDB
#include <ddb/db_output.h>
void dm_thread_db_print(
	thread_t	thread)
{
	db_printf("DM     ");
}
#endif

/*
 *	Statically allocated policy structure.
 */
struct sched_policy	dm_sched_policy = {
    {
	/* sched_ops */
	dm_thread_dequeue,
	dm_thread_enqueue,
	dm_thread_remqueue,

	dm_csw_needed,
	ast_check,
	0,			/* no update_priority */

	dm_run_queue_alloc,
	dm_run_queue_free,

	rt_runq_set_limit,
	rt_runq_get_limit,
	rt_thread_set_limit,
	rt_thread_set_param,
	rt_thread_get_param,
	rt_task_set_param,
	rt_task_get_param,

#if	MACH_KDB
	dm_thread_db_print
#endif

    },
	POLICY_DEADLINE_MONOTONIC,
	"deadline monotonic"
};

