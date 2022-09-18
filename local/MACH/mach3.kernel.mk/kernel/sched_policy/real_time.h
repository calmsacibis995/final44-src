/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
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
 * $Log:	real_time.h,v $
 * Revision 2.2  93/11/17  18:38:06  dbg
 * 	Created.
 * 	[93/05/12            dbg]
 * 
 */

#ifndef	_SCHED_POLICY_REAL_TIME_H_
#define	_SCHED_POLICY_REAL_TIME_H_

#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/policy.h>
#include <mach/realtime_policy.h>

#include <kern/kern_types.h>
#include <kern/run_queues.h>

/*
 *	Common routines for real-time scheduling policies.
 *
 *	Runq and thread have no limit, and task has no default parameters.
 *	The 'null' routines (from sched_policy/bg.c) are used.
 */

#define	rt_runq_set_limit	null_runq_set_limit
extern kern_return_t rt_runq_set_limit(
	run_queue_t	runq,
	policy_param_t	limit,
	natural_t	count);

#define	rt_runq_get_limit	null_runq_get_limit
extern kern_return_t rt_runq_get_limit(
	run_queue_t	runq,
	policy_param_t	limit,
	natural_t	*count);

#define	rt_thread_set_limit	null_thread_set_limit
extern kern_return_t rt_thread_set_limit(
	thread_t	thread,
	policy_param_t	limit,
	natural_t	count);

extern kern_return_t rt_thread_set_param(
	thread_t	thread,
	policy_param_t	param,
	natural_t	count,
	boolean_t	new_policy,
	boolean_t	check_limits);

extern kern_return_t rt_thread_get_param(
	thread_t	thread,
	policy_param_t	param,
	natural_t	*count);

#define	rt_task_set_param	null_task_set_param
extern kern_return_t rt_task_set_param(
	task_t		task,
	policy_param_t	param,
	natural_t	count);

#define	rt_task_get_param	null_task_get_param
extern kern_return_t rt_task_get_param(
	task_t		task,
	policy_param_t	param,
	natural_t	*count);

#endif	/* _SCHED_POLICY_REAL_TIME_H_ */

