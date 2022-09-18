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
 * $Log:	sched_policy.h,v $
 * Revision 2.3  94/12/16  10:51:14  dbg
 * 	Changed THREAD_ENQUEUE and THREAD_REMQUEUE to use
 * 	thread->cur_policy->ops (the thread's current scheduling policy
 * 	vector), so that different scheduling policies can share the
 * 	same set of queues.  Used to make depressed-thread policy be the same
 * 	as the lowest timesharing priority.
 * 	[94/07/14            dbg]
 * 
 * Revision 2.2  93/11/17  17:21:35  dbg
 * 	Moved common code to kern/run_queues.c.
 * 	[93/04/10            dbg]
 * 
 * 	Added more operations to support per-scheduling-policy run queue
 * 	structure.
 * 	[93/04/06            dbg]
 * 
 * 	Added THREAD_SELECT_POLICY and THREAD_REQUEUE.  Removed one
 * 	level of indirection from macros.
 * 	[93/03/31            dbg]
 * 
 * 	Added microseconds argument to CLOCK_SCHED macro.
 * 	[93/01/28            dbg]
 * 
 * 	Moved user interface into mach/sched_policy.h.
 * 
 * 	Created
 * 	[92/02/22	savage]
 * 
 */

/*
 *	Selectable scheduling policies - kernel data structures.
 */
#ifndef _KERN_SCHED_POLICY_H_
#define _KERN_SCHED_POLICY_H_

#include <mach_kdb.h>

#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/policy.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/run_queues.h>
#include <kern/kern_types.h>

/*
 *	Scheduling operations that vary by policy
 */
struct sched_ops {
	/* get the next thread to run */
	thread_t	(*thread_dequeue)(
		run_queue_t	runq);		/* choose from this run q */

	/* enqueue a thread to run */
	boolean_t	(*thread_enqueue)(
		run_queue_t	runq,		/* put on this runq */
		thread_t	thread,		/* thread */
		boolean_t	may_preempt);	/* may preempt running thread */
						/* returns whether to preempt */

	/* remove thread from a run queue */
	void		(*thread_remqueue)(
		run_queue_t	runq,		/* remove from this run q */
		thread_t	thread);	/* remove this thread */

	/* preemption check */
	boolean_t	(*csw_needed)(
		run_queue_t	runq,
		thread_t	thread);

	/* scheduling decisions at periodic clock tick */
	void		(*clock_sched)(
		thread_t	thread,
		boolean_t	end_of_quantum);

	/* priority update */
	void		(*update_priority)(
		thread_t	thread);

	/* allocate a run queue structure for this policy */
	run_queue_t	(*runq_alloc)(void);

	/* deallocate a run queue structure for this policy */
	void		(*runq_free)(
		run_queue_t	runq);

	/* set the limit values for this policy */
	kern_return_t	(*runq_set_limit)(
		run_queue_t	runq,
		policy_param_t	limit,
		natural_t	count);

	/* get the limit values for this policy */
	kern_return_t	(*runq_get_limit)(
		run_queue_t	runq,
		policy_param_t	limit,
		natural_t	*count);

	/* set the limit values for this thread */
	kern_return_t	(*thread_set_limit)(
		thread_t	thread,
		policy_param_t	limit,
		natural_t	count);

	/* set the current parameters for a thread */
	kern_return_t	(*thread_set_param)(
		thread_t	thread,
		policy_param_t	param,
		natural_t	param_count,
		boolean_t	new_policy,
		boolean_t	check_limits);

	/* get the limit and current parameters for a thread */
	kern_return_t	(*thread_get_param)(
		thread_t	thread,
		policy_param_t	param,
		natural_t	*count);

	/* set the default parameters for a task */
	kern_return_t	(*task_set_param)(
		task_t		task,
		policy_param_t	param,
		natural_t	param_count);

	/* get the default parameters for a task */
	kern_return_t	(*task_get_param)(
		task_t		task,
		policy_param_t	param,
		natural_t	*count);

#if	MACH_IO_BINDING
	/* compare threads at the heads of two run queues */
	boolean_t	(*runq_head_preempt)(
		run_queue_t	runq_1,
		run_queue_t	runq_2);
#endif	/* MACH_IO_BINDING */

#if	MACH_KDB
	/* print thread policy and priority for debugger */
	/* format is "%3s %3d" */
	void		(*thread_db_print)(
		thread_t	thread);
#endif	/* MACH_KDB */
};

/*
 *	Scheduling operations are in the processor set.
 */
#define	THREAD_DEQUEUE(runq) \
	((*(runq)->rq_policy->sched_ops.thread_dequeue)\
		((runq)) )

#define	THREAD_ENQUEUE(runq, thread, may_preempt) \
	((*(thread)->cur_policy->sched_ops.thread_enqueue)\
		((runq), (thread), (may_preempt)) )

#define	THREAD_REMQUEUE(runq, thread) \
	((*(thread)->cur_policy->sched_ops.thread_remqueue)\
		((runq), (thread)) )

#define	CSW_NEEDED(runq, thread) \
	((*(runq)->rq_policy->sched_ops.csw_needed)\
		((runq), (thread)) )

#define	CLOCK_SCHED(thread, end_of_quantum) \
	((*(thread)->cur_policy->sched_ops.clock_sched)\
		((thread), (end_of_quantum)) )

/*
 *	Update_priority is often null.
 *	Check for null routine instead of calling it.
 */
#define	UPDATE_PRIORITY(thread) \
    MACRO_BEGIN								\
	void	(*upd_pri)(thread_t);					\
									\
	upd_pri = (thread)->cur_policy->sched_ops.update_priority;	\
	if (upd_pri)							\
	    (*upd_pri) ((thread));					\
    MACRO_END

#define	RUNQ_ALLOC(sched_policy) \
	((*(sched_policy)->sched_ops.runq_alloc)())

#define	RUNQ_FREE(runq) \
	((*(runq)->rq_policy->sched_ops.runq_free)\
		((runq)) )

#define	RUNQ_SET_LIMIT(runq, limit, count) \
	((*(runq)->rq_policy->sched_ops.runq_set_limit) \
		((runq), (limit), (count)) )

#define	RUNQ_GET_LIMIT(runq, limit, count) \
	((*(runq)->rq_policy->sched_ops.runq_get_limit) \
		((runq), (limit), (count)) )

#define	THREAD_SET_LIMIT(thread, limit, count) \
	((*(thread)->sched_policy->sched_ops.thread_set_limit) \
		((thread), (limit), (count)) )

#define	THREAD_SET_PARAM(thread, param, count, new_policy, check_limits) \
	((*(thread)->sched_policy->sched_ops.thread_set_param)\
		((thread), (param), (count), (new_policy), (check_limits)) )

#define	THREAD_GET_PARAM(thread, param, count) \
	((*(thread)->sched_policy->sched_ops.thread_get_param)\
		((thread), (param), (count)) )

#define	TASK_SET_PARAM(task, param, count) \
	((*(task)->sched_policy->sched_ops.task_set_param)\
		((task), (param), (count)) )

#define	TASK_GET_PARAM(task, param, count) \
	((*(task)->sched_policy->sched_ops.task_get_param)\
		((task), (param), (count)) )

#if	MACH_IO_BINDING
#define	RUNQ_HEAD_PREEMPT(runq_1, runq_2) \
	((*(runq_1)->rq_policy->sched_ops.runq_head_preempt) \
		((runq_1), (runq_2)) )
#endif	/* MACH_IO_BINDING */

#if	MACH_KDB
#define	THREAD_DB_PRINT(thread) \
	((*(thread)->sched_policy->sched_ops.thread_db_print)\
		((thread)) )
#endif	/* MACH_KDB */

/*
 *	Scheduling Policy
 */
struct sched_policy {
	struct sched_ops sched_ops;		/* operations */
	int		name;			/* integer name */
	char *		string_name;		/* string name */
	int		rank;			/* relative ranking */
};

typedef struct sched_policy *	sched_policy_t;
typedef struct sched_policy	sched_policy_data_t;

#define SCHED_POLICY_NULL	((sched_policy_t) 0)

/*
 *	Scheduling policy ranking function.
 */
#define	sched_policy_leq(sched1, sched2) \
	((sched1)->rank <= (sched2)->rank)

extern void		sched_policy_init(void);
extern sched_policy_t	sched_policy_lookup(int policy);

/*
 *	Generic scheduling parameter data structure.
 *
 *	This should be configurable from the scheduling
 *	parameters built into the system, but it isn`t now.
 */

#define	SCHED_PARAM_MAX		8

struct sched_param {
	natural_t	data[SCHED_PARAM_MAX];
};

typedef	struct sched_param	sched_param_data_t;

/*
 *	Routines to set and get scheduling policies and parameters.
 */
extern void processor_set_default_policies(processor_set_t);

extern void task_inherit_default_policy(
		task_t		parent_task,
		task_t		new_task);

extern void thread_set_default_policy(thread_t);
extern void thread_enforce_policy_limits(thread_t, processor_set_t);
extern void thread_set_initial_policy(thread_t, task_t);

#endif	/* _KERN_SCHED_POLICY_H_ */

