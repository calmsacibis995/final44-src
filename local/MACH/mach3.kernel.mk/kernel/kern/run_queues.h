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
 * $Log:	run_queues.h,v $
 * Revision 2.3  94/12/16  10:50:18  dbg
 * 	Replace the "last" field in the run queue header with a
 * 	bitmap of policies with runnable threads.
 * 	[94/03/06            dbg]
 * 
 * Revision 2.2  93/11/17  17:20:32  dbg
 * 	Removed rq_rank (unused).
 * 	[93/08/18            dbg]
 * 
 * 	Processor set now has one run queue structure per scheduling
 * 	policy.  The actual run queues are policy-specific.
 * 	[93/04/06            dbg]
 * 
 * 	Moved run queue definitions here from kern/sched.h.
 * 	[93/01/12            dbg]
 * 
 */

/*
 *	File:	kern/run_queues.h
 *	Original Author: Avadis Tevanian, Jr.
 *	Date:	1986
 *
 *	Run queues.
 */

#ifndef	_KERN_RUN_QUEUES_H_
#define	_KERN_RUN_QUEUES_H_

#include <cpus.h>

#include <mach/policy.h>

#include <kern/kern_types.h>		/* thread_t, processor_t */
#include <kern/macro_help.h>
#include <kern/queue.h>
#include <kern/lock.h>
#include <kern/macro_help.h>

/*
 *	Each processor set has a prioritized list of run queues,
 *	one for each scheduling policy enabled on the processor
 *	set.  The run queue structure may vary according to the
 *	scheduling policy.  The common part of the structure
 *	holds a count of runnable threads and a pointer to the
 *	scheduling policy itself.  The head of the run queue holds
 *	the lock for all of the run queues, and an array of per-
 *	policy run queues.
 */

struct run_queue {
	struct sched_policy *	rq_policy;	/* scheduling policy */
	int			rq_count;	/* count of runnable threads */
};

typedef struct run_queue	*run_queue_t;
#define RUN_QUEUE_NULL	((run_queue_t) 0)

/*
 *	Private data follows the common run_queue structure.
 */
#define	rq_private(rq)		((void *)((rq) + 1))

/*
 *	The run queue list is headed by a run_queue_head structure.
 *	It contains the lock for all of the run queues, a count of
 *	runnable thread, a bitmap of policies with runnable threads,
 *	and pointers to the per-policy run queues.  
 */
#define	NUM_POLICIES		(8)		/* configurable! */

struct run_queue_head {
	run_queue_t		runqs[NUM_POLICIES];
	int			count;
	unsigned int		bitmap;
	decl_simple_lock_data(,	lock)
};
typedef	struct run_queue_head	*run_queue_head_t;
#define RUN_QUEUE_HEAD_NULL	((run_queue_head_t) 0)

/*
 *	Initialization
 */
#define	run_queue_init(runq, policy) \
    MACRO_BEGIN \
	(runq)->rq_policy = (policy); \
	(runq)->rq_count  = 0; \
    MACRO_END

/*
 *	Run queue head initialization and termination
 */
extern void
run_queue_head_init(
	run_queue_head_t	runq);
extern void
run_queue_head_dealloc(
	run_queue_head_t	runq);

/*
 *	Make thread runnable.
 */
extern void thread_setrun(
	thread_t	thread,
	boolean_t	may_preempt);

/*
 *	Find the next runnable thread on either the
 *	per-processor or the processor set`s collection
 *	of run queues.
 */
extern thread_t
thread_select(
	processor_t	processor);

/*
 *	Pull a thread off its run queue.
 */
extern run_queue_head_t
rem_runq(thread_t	thread);

/*
 *	Check whether the current thread should be
 *	preempted by a higher priority thread on the
 *	run queues.
 */
extern boolean_t
csw_needed(
	thread_t	thread,
	processor_t	processor);

#if	NCPUS > 1
/*
 *	Force a thread to execute on the specified processor.
 */
extern void
thread_bind(
	thread_t	thread,
	processor_t	processor);

#endif	/* NCPUS > 1 */

#endif	/* _KERN_RUN_QUEUES_H_ */
