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
 * $Log:	rt_thread.c,v $
 * Revision 2.3  94/12/16  10:47:04  dbg
 * 	Renamed 'time_spec' to 'timespec', 'timer_' to 'mach_timer_'.
 * 	[94/05/23            dbg]
 * 
 * 	In periodic_thread_create, free extra reference returned for
 * 	timer.  Timer has one reference (from its port), and
 * 	thread_set_periodic_timers does not use the extra reference.
 * 	[94/03/06            dbg]
 * 
 * Revision 2.2  93/11/17  17:20:03  dbg
 * 	Renamed 'rt' or 'realtime' threads and timers to 'periodic'
 * 	threads and timers (even though they can be used for nonperiodic
 * 	threads).
 * 	[93/11/16            dbg]
 * 
 * 	Use thread_lock instead of ith_lock.
 * 	[93/07/12            dbg]
 * 
 * 	Handle starting timer better.
 * 	[93/06/28            dbg]
 * 
 * 	Changed thread_{get,set}_deadline_timer to
 * 	thread_{get,set}_realtime_timers.
 * 	[93/06/25            dbg]
 * 
 * 	Use clock_read to read clock without locking.
 * 	[93/06/18            dbg]
 * 
 * 	machparam.h -> machspl.h
 * 	[93/05/21            dbg]
 * 
 * 	Conditionalize for MACH_RT.
 * 	[93/05/17            dbg]
 * 
 * 	Changed for flexible thread scheduling fields.
 * 	[93/05/12            dbg]
 * 
 * 	Added thread_get_deadline_timer, thread_set_deadline_timer.
 * 	[93/04/15            dbg]
 * 
 * 	Use sleep/wakeup instead of suspend/resume to wait for wakeup
 * 	timer.
 * 	[93/04/02            dbg]
 * 
 * 	Moved thread_{get,set}_attributes here.
 * 	[93/03/31            dbg]
 * 
 * 	Merged into microkernel mainline.
 * 
 * 	Checked timespecs to make sure they're valid
 * 	[92/09/11	savage]
 * 	Changed period and deadline to timespec_t.
 * 	[92/09/06	savage]
 * 	Switched to use clock parameter instead of constant.  Cleanup.
 * 	[92/07/12	savage]
 * 	Replaced rt_timers with more generic mach_timers
 * 	[92/06/22	savage]
 * 	Replaced wakeup queue with rt_timer mechanism
 * 	[92/05/05	savage]
 * 	Re-vamped :-)
 * 	[92/02/22	savage]
 * 	Created
 * 	[90/06/28	tatsuo]
 * 
 */
#include <mach_rt.h>

#include <mach/kern_return.h>
#include <mach/realtime_policy.h>
#include <mach/timespec.h>

#include <ipc/ipc_object.h>
#include <ipc/ipc_port.h>

#include <kern/lock.h>
#include <kern/mach_clock.h>
#include <kern/mach_param.h>
#include <kern/mach_timer.h>
#include <kern/rt_thread.h>
#include <kern/thread.h>
#include <kern/zalloc.h>

#include <vm/vm_kern.h>

#include <machine/machspl.h>

#if	MACH_RT
/*
 *	Routine:	thread_get_periodic_timers
 *	Purpose:	gets the wakeup and deadline timers for a thread.
 */
kern_return_t
thread_get_periodic_timers(
	thread_t	thread,
	mach_timer_t	*wakeup_timer_p,		/* OUT */
	mach_timer_t	*deadline_timer_p)
{
	mach_timer_t	wakeup_timer, deadline_timer;

	if (thread == THREAD_NULL)
	    return KERN_INVALID_ARGUMENT;

	thread_lock(thread);
	wakeup_timer = thread->rt_wakeup_timer;
	mach_timer_reference(wakeup_timer);
	deadline_timer = thread->rt_deadline_timer;
	mach_timer_reference(deadline_timer);
	thread_unlock(thread);

	*wakeup_timer_p = wakeup_timer;
	*deadline_timer_p = deadline_timer;

	return KERN_SUCCESS;
}

/*
 *	Routine:	thread_set_periodic_timers
 *	Purpose:	sets the wakeup and deadline timers for a thread.
 */
kern_return_t
thread_set_periodic_timers(
	thread_t	thread,
	mach_timer_t	new_wakeup_timer,
	mach_timer_t	new_deadline_timer)
{
	mach_timer_t	old_wakeup_timer;
	mach_timer_t	old_deadline_timer;

	if (thread == THREAD_NULL)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Make thread references to the new timers
	 *	to keep them alive even if all send rights
	 *	vanish.
	 */
	if (!mach_timer_thread_reference(new_wakeup_timer)) {
	    /* dead already (?) */
	    return KERN_INVALID_ARGUMENT;
	}
	if (!mach_timer_thread_reference(new_deadline_timer)) {
	    mach_timer_thread_deallocate(new_wakeup_timer);
	    return KERN_INVALID_ARGUMENT;
	}


	/*
	 *	Swap the old and new timers.
	 */
	thread_lock(thread);
	old_wakeup_timer = thread->rt_wakeup_timer;
	thread->rt_wakeup_timer = new_wakeup_timer;
	old_deadline_timer = thread->rt_deadline_timer;
	thread->rt_deadline_timer = new_deadline_timer;
	thread_unlock(thread);

	/*
	 *	Deallocate the thread-references to
	 *	the old timers.
	 */
	if (old_wakeup_timer != 0)
	    mach_timer_thread_deallocate(old_wakeup_timer);
	if (old_deadline_timer != 0)
	    mach_timer_thread_deallocate(old_deadline_timer);

	return KERN_SUCCESS;
}

/*
 *	Routine:	periodic_thread_create
 *	Purpose:	Creates a thread via thread_create, sets scheduling 
 *			parameters, sets execution state, and then either
 *			thread_resumes the thread or enqueues it to be resumed
 *			later.
 *	Conditions:	None
 */
kern_return_t periodic_thread_create(
	task_t			parent_task,
	mach_clock_t		clock,
	policy_param_realtime_t	rt_attr,
	ipc_port_t		deadline_port,
	int			state_flavor,
	thread_state_t		state,
	natural_t		state_count,
	thread_t		*child_thread)	/* out */
{
	register
	thread_t	thread;
	mach_timer_t	wakeup_timer;
	mach_timer_t	deadline_timer;
	int		periodic;
	kern_return_t	ret;

	if (parent_task == TASK_NULL || clock == 0)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Are the timespecs legitimate?
	 */
	if (!timespec_valid(rt_attr.start_time) ||
	    !timespec_valid(rt_attr.period) ||
	    !timespec_valid(rt_attr.deadline))
	{
	    return KERN_INVALID_VALUE;
	}
	if (rt_attr.start_when != START_TIME_ABSOLUTE &&
	    rt_attr.start_when != START_TIME_RELATIVE)
	{
	    return KERN_INVALID_VALUE;
	}

	/*
	 *	Convert zero period or deadline to infinity.
	 */
	if (!timespec_nonzero(rt_attr.period)) {
	    timespec_set_infinite(rt_attr.period);
	}
	if (!timespec_nonzero(rt_attr.deadline)) {
	    timespec_set_infinite(rt_attr.deadline);
	}

	/*
	 *	Create the thread.
	 */
	{
	    thread_t	temp_thread;	/* to keep 'thread' in register */

	    ret = thread_create(parent_task, &temp_thread);
	    if (ret != KERN_SUCCESS)
		return ret;

	    thread = temp_thread;
	}

	/*
	 *	Set initial register state for the thread.
	 */
	ret = thread_setstatus(thread, state_flavor, state, state_count);
	if (ret != KERN_SUCCESS) {
	    (void) thread_terminate(thread);
	    return ret;
	}

	/*
	 *	Create a wakeup timer for the thread.
	 */
	ret = mach_timer_create(clock, &wakeup_timer);
	if (ret != KERN_SUCCESS) {
	    (void) thread_terminate(thread);
	    thread_deallocate(thread);
	    return ret;
	}

	/*
	 *	Free the extra reference to the wakeup timer.
	 */
	mach_timer_deallocate(wakeup_timer);

	/*
	 *	Create a deadline timer for the thread.
	 */
	ret = mach_timer_create(clock, &deadline_timer);
	if (ret != KERN_SUCCESS) {
	    (void) mach_timer_terminate(wakeup_timer);
	    (void) thread_terminate(thread);
	    thread_deallocate(thread);
	    return ret;
	}

	/*
	 *	Free the extra reference to the deadline timer.
	 */
	mach_timer_deallocate(deadline_timer);

	/*
	 *	Calculate the absolute start time, so that
	 *	the wakeup and deadline timers are consistent.
	 *	Give it to thread_set_policy_param.
	 */
	if (rt_attr.start_when == START_TIME_RELATIVE) {
	    timespec_t	cur_time;
	    clock_read(cur_time, clock);
	    timespec_add(rt_attr.start_time, cur_time);
	    rt_attr.start_when = START_TIME_ABSOLUTE;
	}

	/*
	 *	Set the scheduling policy and attributes for
	 *	the thread.  Do this before registering the
	 *	timers for the thread, so that the timers
	 *	can be set later (with the wakeup-thread
	 *	and deadline port).
	 */
	ret = thread_set_policy_param(thread,
				      FALSE,
				      (natural_t *)&rt_attr,
				      POLICY_PARAM_REALTIME_COUNT);
	if (ret != KERN_SUCCESS) {
	    (void) mach_timer_terminate(wakeup_timer);
	    (void) mach_timer_terminate(deadline_timer);
	    (void) thread_terminate(thread);
	    return ret;
	}

	/*
	 *	Register the timers with the thread.
	 */
	(void) thread_set_periodic_timers(thread,
					  wakeup_timer,
					  deadline_timer);

	/*
	 *	Set the 'periodic' flag for the timers.
	 */
	if (timespec_infinite(rt_attr.period))
	    periodic = 0;		/* not periodic */
	else
	    periodic = TIMER_PERIODIC;	/* periodic thread */

	/*
	 *	Set the wakeup timer for the starting time
	 *	of the thread, and make it periodic if thread
	 *	is periodic.
	 */
	ret = mach_timer_sleep_periodic(wakeup_timer,
				   rt_attr.start_time,
				   rt_attr.period,
				   thread,
				   TIMER_ABSOLUTE | periodic);
	if (ret != KERN_SUCCESS) {
	    (void) thread_terminate(thread);
	    return ret;
	}

	/*
	 *	Set the deadline timer, if the thread has
	 *	a deadline.
	 */
	if (!timespec_infinite(rt_attr.deadline)) {
	    timespec_t	deadline_time;

	    deadline_time = rt_attr.start_time;
	    timespec_add(deadline_time, rt_attr.deadline);
	    ret = mach_timer_arm(deadline_timer,
			    deadline_time,
			    rt_attr.period,
			    deadline_port,
			    thread,
			    TIMER_THREAD_SUSPEND | TIMER_ABSOLUTE | periodic);
	    if (ret != KERN_SUCCESS) {
		/*
		 *	Bad parameter to time?
		 */
		(void) thread_terminate(thread);
		return ret;
	    }
	}

	/*
	 *	Resume the thread.  If it has a delayed start,
	 *	it will be waiting for the wakeup timer.
	 */
	(void) thread_resume(thread);

	/*
	 *	Return the child thread.
	 */
	*child_thread = thread;
	return KERN_SUCCESS;
}


/*
 *	Routine:	periodic_thread_restart
 *	Purpose:	Resets timers and execution state for periodic threads.
 *			This routine is usually only called via fiddling with
 *			the user stack and is never invoked directly.
 *	Conditions:	None
 */
kern_return_t periodic_thread_restart(
	thread_t	thread)
{
	mach_timer_t	wakeup_timer;
	mach_timer_t	deadline_timer;

	if (thread == THREAD_NULL)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Thread must have wakeup and deadline timers
	 */
	deadline_timer = thread->rt_deadline_timer;
	wakeup_timer   = thread->rt_wakeup_timer;
	if (deadline_timer == 0 || wakeup_timer == 0)
	    return KERN_INVALID_ARGUMENT;

	/*
	 *	Cancel the current iteration of the deadline timer.
	 *	If the thread is periodic, this resets the deadline
	 *	timer to the deadline for the thread`s next
	 *	execution period.
	 */

	(void) mach_timer_cancel(deadline_timer, TIMER_PERIODIC);

	/*
	 *	If the thread is not periodic, terminate it.
	 *
	 *	XXX locking on timer
	 */
	if ((wakeup_timer->tm_flags & TELT_PERIODIC) == 0) {
	    return thread_terminate(thread);
	}

	/*
	 *	Periodic thread.  Wait for the next
	 *	expiration of the wakeup timer.
	 */
	mach_timer_wait(wakeup_timer, thread);

	/*
	 *	Thread is now waiting for timer.
	 *	If it is the current thread, block to
	 *	wait for timer.
	 *
	 *	If thread is NOT the current thread, it better
	 *	be suspended...
	 */
	if (thread == current_thread()) {
	    thread_block(CONTINUE_NULL);
	}

	return KERN_SUCCESS;
}

#else	/* MACH_RT */

/*
 *	Periodic thread interfaces are not implemented, and all
 *	return KERN_FAILURE.
 */
kern_return_t
thread_get_periodic_timers(
	thread_t	thread,
	mach_timer_t	*wakeup_timer_p,		/* OUT */
	mach_timer_t	*deadline_timer_p)
{
	return KERN_FAILURE;
}

kern_return_t
thread_set_periodic_timers(
	thread_t	thread,
	mach_timer_t	new_wakeup_timer,
	mach_timer_t	new_deadline_timer)
{
	return KERN_FAILURE;
}

kern_return_t periodic_thread_create(
	task_t			parent_task,
	mach_clock_t		clock,
	policy_param_realtime_t	rt_attr,
	ipc_port_t		deadline_port,
	int			state_flavor,
	thread_state_t		state,
	natural_t		state_count,
	thread_t		*child_thread)	/* out */
{
	return KERN_FAILURE;
}

kern_return_t periodic_thread_restart(
	thread_t	thread)
{
	return KERN_FAILURE;
}

#endif	/* MACH_RT */
