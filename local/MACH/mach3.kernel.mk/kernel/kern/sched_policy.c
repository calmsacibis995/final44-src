/* 
 * Mach Operating System
 * Copyright (c) 1994,1993 Carnegie Mellon University
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
 * $Log:	sched_policy.c,v $
 * Revision 2.3  94/12/16  10:51:03  dbg
 * 	Thread_enforce_policy_limits checks thread->sched_policy 
 * 	to avoid error if the thread is reassigned to a new
 * 	processor set while its priority is depressed.
 * 	[94/07/14            dbg]
 * 
 * 	Removed the per-processor runq pointers if multiprocessor
 * 	and not MACH_IO_BINDING: we only have one possible bound
 * 	thread (the action thread).  Replaced the "last" field in
 * 	the run queue header with a bitmap of policies with
 * 	runnable threads.
 * 	[94/03/10            dbg]
 * 
 * Revision 2.2  93/11/17  17:21:24  dbg
 * 	Use runq pointers in processor if NCPUS > 1 - processor_shutdown
 * 	does not depend on MACH_HOST.
 * 	[93/07/21            dbg]
 * 
 * 	Break up thread lock.  Change lock ordering to
 * 	thread_lock -> pset_lock -> thread_sched_lock.
 * 	[93/05/27            dbg]
 * 
 * 	machparam.h -> machspl.h
 * 	[93/05/21            dbg]
 * 
 * 	New interfaces.
 * 	[93/05/05            dbg]
 * 
 * 	Created.
 * 	[93/04/02            dbg]
 * 
 */

/*
 *	Scheduling policies and instances.
 */

#include <mach_host.h>
#include <mach_io_binding.h>

#include <mach/kern_return.h>

#include <kern/kern_types.h>
#include <kern/sched_policy.h>
#include <kern/processor.h>
#include <kern/thread.h>

#include <sched_policy/standard.h>	/* BG, TS, FP */

#include <machine/machspl.h>

void thread_set_default_policy(thread_t);	/* forward */
void thread_enforce_policy_limits(thread_t, processor_set_t);
						/* forward */

/*
 *	processor_set_policy_add
 *
 *	Add a new scheduling policy to a processor set,
 *	and supply the limit values for the policy.
 */
kern_return_t processor_set_policy_add(
	processor_set_t	pset,
	int		policy,
	policy_param_t	limit,
	natural_t	count)
{
	sched_policy_t	sched_policy;
	int		policy_index;
	run_queue_t	rq;
	kern_return_t	kr;

	/*
	 *	Make sure we have a processor set.
	 */
	if (pset == PROCESSOR_SET_NULL)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Look up the scheduling policy, by name.
	 */
	sched_policy = sched_policy_lookup(policy);
	if (sched_policy == 0)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Allocate the run queue (and other policy-specific
	 *	data structures) for the policy.
	 */
	rq = RUNQ_ALLOC(sched_policy);

	/*
	 *	Set the limits for the policy
	 */
	kr = RUNQ_SET_LIMIT(rq, limit, count);
	if (kr != KERN_SUCCESS) {
	    /*
	     *	Limit values were bad
	     */
	    RUNQ_FREE(rq);
	    return kr;
	}

	/*
	 *	Attach the run queue to the processor set`s policy
	 *	list, at its proper rank.
	 */
	policy_index = sched_policy->rank;

	pset_lock(pset);
	if (pset->runq.runqs[policy_index] != 0) {
	    /*
	     *	Someone else added the policy while we
	     *	were unlocked.
	     */
	    pset_unlock(pset);

	    RUNQ_FREE(rq);

	    return KERN_SUCCESS;	/* already there */
	}

	pset->runq.runqs[policy_index] = rq;

	pset_unlock(pset);

	return KERN_SUCCESS;
}

/*
 *	Processor_set_policy_remove:
 *
 *	Remove a scheduling policy from a processor set.
 *	Threads running that policy are reset to
 *	timesharing, or to background if timesharing
 *	is not available on the processor set.
 *
 *	The background policy cannot be removed.
 */
kern_return_t processor_set_policy_remove(
	processor_set_t	pset,
	int		policy)
{
	sched_policy_t	sched_policy;
	run_queue_t	rq;
	thread_t	thread;
	int		policy_index;

	/*
	 *	Check that we have a processor set.
	 */
	if (pset == PROCESSOR_SET_NULL)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Background policy cannot be removed.
	 */
	if (policy == POLICY_BACKGROUND)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Look up the scheduling policy, by name.
	 */
	sched_policy = sched_policy_lookup(policy);
	if (sched_policy == 0)
	    return KERN_INVALID_ARGUMENT;

	policy_index = sched_policy->rank;

	/*
	 *	Check whether the policy is enabled
	 *	for the processor set.
	 */
	pset_lock(pset);
	if ((rq = pset->runq.runqs[policy_index]) == RUN_QUEUE_NULL) {
	    pset_unlock(pset);
	    return KERN_FAILURE;	/* not enabled */
	}

	/*
	 *	Remove policy from list.
	 */
	pset->runq.runqs[policy_index] = RUN_QUEUE_NULL;

	/*
	 *	Reassign all threads that run that policy
	 */
	queue_iterate(&pset->threads, thread, thread_t, pset_threads) {
	    spl_t	s;

	    s = splsched();
	    thread_sched_lock(thread);
	    if (thread->sched_policy == sched_policy)
		thread_set_default_policy(thread);
	    thread_sched_unlock(thread);
	    splx(s);
	}
	pset_unlock(pset);

	/*
	 *	Deallocate the run queues.
	 */
	RUNQ_FREE(rq);

	return KERN_SUCCESS;
}

/*
 *	processor_set_policy_limit
 *
 *	Change the limit values for an existing scheduling policy
 *	on a processor set.  This affects newly created and assigned
 *	threads.  Optionally change existing ones.
 */
kern_return_t processor_set_policy_limit(
	processor_set_t	pset,
	int		policy,
	policy_param_t	limit,
	natural_t	count,
	boolean_t	change_threads)
{
	sched_policy_t	sched_policy;
	int		policy_index;
	run_queue_t	rq;
	kern_return_t	kr;

	/*
	 *	Make sure we have a processor set.
	 */
	if (pset == PROCESSOR_SET_NULL)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Look up the scheduling policy, by name.
	 */
	sched_policy = sched_policy_lookup(policy);
	if (sched_policy == 0)
	    return KERN_INVALID_ARGUMENT;

	policy_index = sched_policy->rank;

	/*
	 *	Check whether the policy is enabled
	 *	for the processor set.
	 */
	pset_lock(pset);

	if ((rq = pset->runq.runqs[policy_index]) == RUN_QUEUE_NULL) {
	    pset_unlock(pset);
	    return KERN_FAILURE;	/* not enabled */
	}

	/*
	 *	Set the limits for the policy
	 */
	kr = RUNQ_SET_LIMIT(rq, limit, count);
	if (kr == KERN_SUCCESS) {

	    if (change_threads) {
		register queue_head_t *list;
		register thread_t	thread;

		list = &pset->threads;
		queue_iterate(list, thread, thread_t, pset_threads) {
		    spl_t	s;

		    s = splsched();
		    thread_sched_lock(thread);
		    if (thread->sched_policy == sched_policy)
			thread_enforce_policy_limits(thread, pset);
		    thread_sched_unlock(thread);
		    splx(s);
		}
	    }
	}

	pset_unlock(pset);
	return kr;
}

/*
 *	Set the default policies for a new processor set.
 *
 *	Default is timesharing (which includes background).
 */
void processor_set_default_policies(
	processor_set_t	pset)
{
	(void) processor_set_policy_add(pset, POLICY_TIMESHARE, 0, 0);
}

/*
 *	Thread_set_policy:
 *
 *	Set the scheduling policy for the thread,
 *	and provide the scheduling parameters.
 *	Pset control port must be provided as a key.
 *	If no scheduling parameters are provided,

 *	the default values for the policy will be used.
 */
kern_return_t
thread_set_policy(
	thread_t	thread,
	processor_set_t	pset,
	int		policy,
	policy_param_t	param,
	natural_t	count)
{
	spl_t		s;
	sched_policy_t	old_policy, new_policy;
	int		new_policy_index;
	run_queue_head_t runq;
	kern_return_t	kr;

	if (thread == THREAD_NULL || pset == PROCESSOR_SET_NULL)
	    return KERN_INVALID_ARGUMENT;

	kr = KERN_SUCCESS;

	/*
	 *	Look up the scheduling policy, by name.
	 */
	new_policy = sched_policy_lookup(policy);
	if (new_policy == 0)
	    return KERN_INVALID_ARGUMENT;

	new_policy_index = new_policy->rank;

	/*
	 *	Check whether the policy is enabled
	 *	for the processor set, and whether
	 *	this is indeed the thread`s processor
	 *	set.
	 *
	 *	We only have to hold the pset lock to
	 *	check the thread`s assignment: both the
	 *	pset and thread locks must be held to
	 *	change it.
	 */
	pset_lock(pset);

	if (pset != thread->processor_set) {
	    pset_unlock(pset);
	    return KERN_FAILURE;
	}

	if (pset->runq.runqs[new_policy_index] == RUN_QUEUE_NULL) {
	    pset_unlock(pset);
	    return KERN_FAILURE;	/* not enabled */
	}

	s = splsched();
	thread_sched_lock(thread);

	/*
	 *	Remove thread from its current run queue.
	 */
	runq = rem_runq(thread);

	old_policy = thread->sched_policy;
	if (old_policy == new_policy) {
	    /*
	     *	Thread already runs this policy.  Just change
	     *	scheduling parameters.  Limits for policy
	     *	parameters are those already set for the thread.
	     */
	    kr = THREAD_SET_PARAM(thread, param, count,
				  FALSE,	/* not new policy -
						   use thread limits */
				  TRUE);	/* error if over limits */
	}
	else {
	    /*
	     *	Changing policy.  Set the new policy.
	     */
	    thread->sched_policy = new_policy;

	    /*
	     *	Set parameters from input: if they are
	     *	not supplied, use per-policy defaults.
	     *	Set per-thread limits from processor set.
	     */
	    kr = THREAD_SET_PARAM(thread, param, count,
				  TRUE,		/* new policy -
						   use pset limits */
				  TRUE);	/* error if over limits */
	    if (kr != KERN_SUCCESS) {
		/*
		 *	If parameters are invalid, reset thread
		 *	to old policy.
		 */
		thread->sched_policy = old_policy;
	    }
	    else {
		/*
		 *	Policy parameters are valid.
		 *	Change current policy, if thread
		 *	is not depressed.
		 */
		if (thread->cur_policy == 0 ||
		    thread->cur_policy == old_policy)
		{
		    thread->cur_policy = new_policy;
		    thread->policy_index = new_policy_index;
		}
	    }
	}

	/*
	 *	If the thread had been on a run queue,
	 *	put it back on one.
	 */
	if (runq != RUN_QUEUE_HEAD_NULL)
	    thread_setrun(thread, TRUE);

	thread_sched_unlock(thread);
	splx(s);
	pset_unlock(pset);

	return kr;
}

/*
 *	Set initial policy for thread, from parent task.
 *	If parent task has set no policy, set to the
 *	default policy.
 */
void thread_set_initial_policy(
	thread_t	thread,
	task_t		task)
{
	processor_set_t	pset = thread->processor_set;
	sched_policy_t	new_policy;
	int		new_policy_index;
	spl_t	s;

	new_policy = task->sched_policy;
	new_policy_index = new_policy->rank;

	/*
	 *	If policy is not enabled on processor set,
	 *	use pset`s default policy.
	 */
	if (pset->runq.runqs[new_policy_index] == RUN_QUEUE_NULL) {
	    thread_set_default_policy(thread);
	    return;
	}

	s = splsched();
	thread_sched_lock(thread);

	thread->sched_policy = new_policy;
	thread->cur_policy   = new_policy;
	thread->policy_index = new_policy_index;

	(void) THREAD_SET_PARAM(thread,
				&task->sched_data.data[0],
				task->sched_data_count,
				TRUE,		/* new policy -
						   use pset limits */
				FALSE);		/* no error if over limits */

	thread_sched_unlock(thread);
	splx(s);
}

/*
 *	Set default policy for thread.
 *	Use timesharing if enabled; otherwise use background.
 *
 *	Pset lock and thread_sched_lock must be held.
 */
void thread_set_default_policy(
	thread_t	thread)
{
	processor_set_t	pset = thread->processor_set;
	sched_policy_t	policy;
	run_queue_head_t runq_head;

	policy = &ts_sched_policy;
	if (pset->runq.runqs[policy->rank] == RUN_QUEUE_NULL) {
	    policy = &bg_sched_policy;
	}

	/*
	 *	Since this is called by thread_create,
	 *	we must check for no scheduling policy.
	 */
	if (thread->sched_policy)
	    runq_head = rem_runq(thread);
	else
	    runq_head = RUN_QUEUE_HEAD_NULL;

	if (thread->cur_policy == 0 || 
	    thread->cur_policy == thread->sched_policy)
	{
	    /*
	     *	Not depressed - set current policy.
	     */
	    thread->cur_policy = policy;
	    thread->policy_index = policy->rank;
	}
	thread->sched_policy = policy;

	/*
	 *	Set parameters from per-policy defaults.
	 *	Set limits from processor set.
	 */
	(void) THREAD_SET_PARAM(thread, 0, 0,
				TRUE,		/* new policy -
						   use pset limits */
				FALSE);		/* no error if over limits */

	if (runq_head != RUN_QUEUE_HEAD_NULL) {
	    thread_setrun(thread, TRUE);	/* updates priority */
	}
	else {
	    UPDATE_PRIORITY(thread);
	}
}

/*
 *	Check whether the thread`s policy is valid
 *	in the thread`s processor set.  If it is,
 *	enforce the processor set`s limits.  If not,
 *	reassign the thread to the default policy.
 *
 *	Pset lock and thread_sched_lock must be held.
 */
void thread_enforce_policy_limits(
	thread_t	thread,
	processor_set_t	pset)
{
	run_queue_head_t runq_head;

	if (pset->runq.runqs[thread->sched_policy->rank] == RUN_QUEUE_NULL) {
	    thread_set_default_policy(thread);
	    return;
	}

	runq_head = rem_runq(thread);

	/*
	 *	Check per-thread parameters and limits
	 *	against the pset`s limit values.
	 */
	(void) THREAD_SET_PARAM(thread, 0, 0,
				FALSE,		/* same policy -
						   use thread limits */
				FALSE);		/* no error if over limits */

	if (runq_head != RUN_QUEUE_HEAD_NULL) {
	    thread_setrun(thread, TRUE);	/* updates priority */
	}
	else {
	    UPDATE_PRIORITY(thread);
	}
}

/*
 *	Set scheduling parameters for a thread.
 *	The parameters must be valid for the current
 *	scheduling policy.
 */
kern_return_t
thread_set_policy_param(
	thread_t	thread,
	boolean_t	set_limit,
	policy_param_t	param,
	natural_t	count)
{
	run_queue_head_t runq;
	spl_t		s;
	kern_return_t	kr;

	if (thread == THREAD_NULL)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Hold the thread lock to prevent the
	 *	thread from being reassigned.
	 */
	thread_lock(thread);

	s = splsched();
	thread_sched_lock(thread);

	/*
	 *	Remove thread from its current run queue.
	 */
	runq = rem_runq(thread);

	/*
	 *	Set the new per-policy scheduling parameters.
	 */
	kr = THREAD_SET_PARAM(thread, param, count,
			      FALSE,	/* not new policy -
					   use thread limits */
			      TRUE);	/* error if over limits */

	/*
	 *	If user asked to lower the limit, set that
	 *	also.
	 */
	if (set_limit && kr == KERN_SUCCESS) {
	    kr = THREAD_SET_LIMIT(thread, param, count);
	    assert(kr == KERN_SUCCESS);
	}

	/*
	 *	If the thread had been on a run queue,
	 *	put it back on the run queue.
	 */
	if (runq != RUN_QUEUE_HEAD_NULL)
	    thread_setrun(thread, TRUE);

	thread_sched_unlock(thread);
	splx(s);

	thread_unlock(thread);

	return kr;
}

/*
 *	Set scheduling limits for a thread.
 *	The parameters must be valid for the current
 *	scheduling policy.
 */
kern_return_t
thread_set_policy_limit(
	thread_t	thread,
	processor_set_t	pset,
	policy_param_t	limit,
	natural_t	count)
{
	run_queue_head_t runq;
	spl_t		s;
	kern_return_t	kr;

	if (thread == THREAD_NULL || pset == PROCESSOR_SET_NULL)
	    return KERN_INVALID_ARGUMENT;

	pset_lock(pset);
	if (pset != thread->processor_set) {
	    pset_unlock(pset);
	    return KERN_FAILURE;
	}

	s = splsched();
	thread_sched_lock(thread);

	/*
	 *	Remove thread from its current run queue.
	 */
	runq = rem_runq(thread);

	/*
	 *	Set the new per-policy scheduling information.
	 */
	kr = THREAD_SET_LIMIT(thread, limit, count);

	/*
	 *	If the thread had been on a run queue,
	 *	put it back on the run queue.
	 */
	if (runq != RUN_QUEUE_HEAD_NULL)
	    thread_setrun(thread, TRUE);

	thread_sched_unlock(thread);
	splx(s);

	pset_unlock(pset);

	return kr;
}

/*
 *	Set default scheduling policy and parameters for a
 *	task, to be used when creating new threads in the
 *	task.  Optionally change the policy and parameters
 *	for all threads in the task.
 *
 *	The task must be assigned to the processor set
 *	(security key).
 */
kern_return_t
task_set_default_policy(
	task_t		task,
	processor_set_t	pset,
	int		policy,
	policy_param_t	param,
	natural_t	count,
	boolean_t	assign_threads)
{
	sched_policy_t	old_policy, new_policy;
	int		new_policy_index;
	kern_return_t	kr;

	if (task == TASK_NULL || pset == PROCESSOR_SET_NULL)
	    return KERN_INVALID_ARGUMENT;

	kr = KERN_SUCCESS;

	/*
	 *	Look up the scheduling policy, by name.
	 */
	new_policy = sched_policy_lookup(policy);
	if (new_policy == 0)
	    return KERN_INVALID_ARGUMENT;

	new_policy_index = new_policy->rank;

	/*
	 *	Check whether the policy is enabled
	 *	for the processor set, and whether
	 *	this is indeed the task`s processor
	 *	set.
	 *
	 *	We must hold both the task and pset
	 *	lock to do this, since the task lock
	 *	must be acquired first.
	 */

	task_lock(task);
	pset_lock(pset);

	if (pset != task->processor_set) {
	    pset_unlock(pset);
	    task_unlock(task);
	    return KERN_FAILURE;
	}

	if (pset->runq.runqs[new_policy_index] == RUN_QUEUE_NULL) {
	    pset_unlock(pset);
	    task_unlock(task);
	    return KERN_FAILURE;	/* not enabled */
	}

	/*
	 *	Save the old policy, if we are changing
	 *	policy and the new parameters are invalid.
	 */
	old_policy = task->sched_policy;

	/*
	 *	Set the new policy.
	 */
	task->sched_policy = new_policy;

	/*
	 *	Set parameters from input: if they are
	 *	not supplied, use per-policy defaults.
	 */
	kr = TASK_SET_PARAM(task, param, count);
	if (kr != KERN_SUCCESS) {
	    /*
	     *	If parameters are invalid, reset task
	     *	to old policy.  Parameters have not been changed.
	     */
	    task->sched_policy = old_policy;
	    pset_unlock(pset);
	}
	else {
	    /*
	     *	Policy parameters are valid.
	     *	Change policy/parameters for threads,
	     *	if requested.
	     */
	    pset_unlock(pset);	/* so thread_set_policy can lock it */

	    if (assign_threads) {
		thread_t thread;

		queue_iterate(&task->thread_list, thread, thread_t,
			      thread_list)
		{
		    if (thread_set_policy(thread,
					  pset,
					  policy,
					  param,
					  count) != KERN_SUCCESS)
			kr = KERN_FAILURE;
		}
	    }
	}
	task_unlock(task);

	return kr;
}

/*
 *	Inherit task default policy from parent task,
 *	or system defaults if none.
 */
void task_inherit_default_policy(
	task_t	parent_task,
	task_t	new_task)
{
	if (parent_task != TASK_NULL) {
	    /*
	     *	Copy from parent task
	     */
	    new_task->sched_policy     = parent_task->sched_policy;
	    new_task->sched_data       = parent_task->sched_data;
	    new_task->sched_data_count = parent_task->sched_data_count;
	}
	else {
	    /*
	     *	No parent task - default to timesharing
	     */
	    new_task->sched_policy = &ts_sched_policy;
	    (void) TASK_SET_PARAM(new_task, 0, 0);	/* use default */
	}
}

