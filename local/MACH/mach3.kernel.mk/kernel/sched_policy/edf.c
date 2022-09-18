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
 * $Log:	edf.c,v $
 * Revision 2.4  94/12/16  11:04:41  dbg
 * 	Renamed 'time_spec' to 'timespec'.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.3  93/12/23  10:05:13  dbg
 * 	Removed include of machine/machparam.h.
 * 	[93/12/14            dbg]
 * 
 * Revision 2.2  93/11/17  18:37:03  dbg
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
 *	Earliest-deadline-first scheduling policy.  Threads
 *	are scheduled in the order of earliest deadline time
 *	first.
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
#include <kern/mach_timer.h>
#include <sched_policy/real_time.h>
#include <ipc/ipc_port.h>

/*
 *	Uses a single run queue, ordered by deadline time.
 *	No policy limits.
 */
struct edf_run_queue {
	struct run_queue rq;		/* common structure */
	queue_head_t	edf_queue;	/* queue */
};
typedef	struct edf_run_queue *	edf_run_queue_t;

#define	edf_runq(rq)	((struct edf_run_queue *)(rq))
#define	edf_count	rq.rq_count

/*
 *	Choose thread.
 */
thread_t
edf_thread_dequeue(
	run_queue_t	runq)
{
	edf_run_queue_t	rq = edf_runq(runq);
	queue_entry_t	elt;

	assert(rq->edf_count > 0);
	assert(!queue_empty(&rq->edf_queue));

	dequeue_head_macro(&rq->edf_queue, elt);
	rq->edf_count--;

	current_processor()->first_quantum = TRUE;	/* XXX */

	return (thread_t) elt;
}

/*
 *	Put a thread onto a run queue in priority order.
 *	Return whether it can preempt the current thread.
 */
boolean_t edf_thread_enqueue(
	run_queue_t	runq,
	thread_t	thread,
	boolean_t	may_preempt)
{
	register edf_run_queue_t rq;
	register thread_t	next;
	register queue_t	q;
	mach_timer_t		timer1, timer2;

	rq = edf_runq(runq);

	q = &rq->edf_queue;
	timer1 = thread->rt_deadline_timer;
	if (timer1 == 0) {
	    enqueue_tail_macro(q, (queue_entry_t) thread);
	    rq->edf_count++;
	    return FALSE;
	}
	queue_iterate(q, next, thread_t, links) {
	    timer2 = next->rt_deadline_timer;
	    if (timer2 == 0)
		break;
	    if (timespec_le(timer1->tm_expire_time,
			      timer2->tm_expire_time))
		break;
	}
	enqueue_tail_macro((queue_t) next, (queue_entry_t) thread);
	rq->edf_count++;

	if (!may_preempt)
	    return FALSE;

	timer2 = current_thread()->rt_deadline_timer;
	if (timer2 == 0)
	    return TRUE;
	return !timespec_le(timer2->tm_expire_time, timer1->tm_expire_time);
}

/*
 *	Remove a thread from the run queue.
 */
void edf_thread_remqueue(
	run_queue_t	runq,
	thread_t	thread)
{
	edf_run_queue_t	rq = edf_runq(runq);
		
	remqueue(&rq->edf_queue, (queue_entry_t) thread);
	rq->edf_count--;
}

boolean_t edf_csw_needed(
	run_queue_t	runq,
	thread_t	thread)
{
	edf_run_queue_t	rq = edf_runq(runq);
	thread_t	th;
	mach_timer_t	timer1, timer2;

	th = (thread_t) queue_first(&rq->edf_queue);
	timer1 = th->rt_deadline_timer;
	timer2 = thread->rt_deadline_timer;

	if (timer1 == 0)
	    return FALSE;
	if (timer2 == 0)
	    return TRUE;
	return timespec_le(timer1->tm_expire_time, timer2->tm_expire_time);
}

extern struct sched_policy	edf_sched_policy;	/* forward */

run_queue_t
edf_run_queue_alloc(void)
{
	edf_run_queue_t	rq;

	rq = (edf_run_queue_t) kalloc(sizeof(struct edf_run_queue));
	run_queue_init(&rq->rq, &edf_sched_policy);

	queue_init(&rq->edf_queue);

	return &rq->rq;
}

void
edf_run_queue_free(
	run_queue_t	runq)
{
	kfree((vm_offset_t) runq, sizeof(struct edf_run_queue));
}

#if	MACH_KDB
#include <ddb/db_output.h>
void edf_thread_db_print(
	thread_t	thread)
{
	db_printf("EDF    ");
}
#endif

/*
 *	Statically allocated policy structure.
 */
struct sched_policy	edf_sched_policy = {
    {
	/* sched_ops */
	edf_thread_dequeue,
	edf_thread_enqueue,
	edf_thread_remqueue,

	edf_csw_needed,
	ast_check,
	0,			/* no update_priority */

	edf_run_queue_alloc,
	edf_run_queue_free,

	rt_runq_set_limit,
	rt_runq_get_limit,
	rt_thread_set_limit,
	rt_thread_set_param,
	rt_thread_get_param,
	rt_task_set_param,
	rt_task_get_param,

#if	MACH_KDB
	edf_thread_db_print
#endif

    },
	POLICY_EARLIEST_DEADLINE_FIRST,
	"earliest deadline first"
};

