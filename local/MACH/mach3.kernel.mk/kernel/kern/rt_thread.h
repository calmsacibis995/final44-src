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
 * $Log:	rt_thread.h,v $
 * Revision 2.3  94/12/16  10:47:25  dbg
 * 	Renamed 'time_spec' to 'timespec'.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  17:20:11  dbg
 * 	Renamed 'rt' or 'realtime' threads and timers to 'periodic'
 * 	threads and timers (even though they can be used for nonperiodic
 * 	threads).
 * 	[93/11/16            dbg]
 * 
 * 	Created.
 * 	[93/05/12            dbg]
 * 
 */

#ifndef	_KERN_RT_THREAD_H_
#define	_KERN_RT_THREAD_H_

#include <mach/time_spec.h>
#include <mach/realtime_policy.h>
#include <kern/mach_clock.h>
#include <kern/thread.h>
#include <kern/mach_timer.h>
#include <ipc/ipc_types.h>

/*
 *	Common thread scheduling fields for real-time scheduling
 *	policies.
 */

struct rt_sched_data {
	timespec_t	start_time;
	timespec_t	period;
	timespec_t	deadline;
};

#define	rt_sched(th)	((struct rt_sched_data *)&(th)->sched_data)

/*
 *	Periodic (real-time) thread routines.
 */

extern kern_return_t
thread_get_periodic_timers(
	thread_t	thread,
	mach_timer_t	*wakeup_timer_p,
	mach_timer_t	*deadline_timer_p);

extern kern_return_t
thread_set_periodic_timers(
	thread_t	thread,
	mach_timer_t	wakeup_timer,
	mach_timer_t	deadline_timer);

extern kern_return_t
periodic_thread_create(
	task_t			parent_task,
	mach_clock_t		clock,
	policy_param_realtime_t	rt_attr,
	ipc_port_t		deadline_port,
	int			state_flavor,
	thread_state_t		state,
	natural_t		state_count,
	thread_t		*child_thread);	/* out */

extern kern_return_t
periodic_thread_restart(
	thread_t	thread);

#endif	/* _KERN_RT_THREAD_H_ */
