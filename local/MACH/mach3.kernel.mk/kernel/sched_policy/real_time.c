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
 * $Log:	real_time.c,v $
 * Revision 2.3  94/12/16  11:20:31  dbg
 * 	Renamed 'time_spec' to 'timespec', 'timer_' to 'mach_timer_'.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  18:37:51  dbg
 * 	policy_param_realtime always has start time.
 * 	[93/06/21            dbg]
 * 
 * 	Created.
 * 	[93/05/12            dbg]
 * 
 */

/*
 *	Common routines for real-time scheduling policies.
 */

#include <kern/mach_clock.h>
#include <kern/mach_timer.h>
#include <kern/run_queues.h>
#include <kern/thread.h>
#include <kern/rt_thread.h>

#include <ipc/ipc_port.h>

#include <sched_policy/real_time.h>

#include <machine/machspl.h>

/*
 *	Set the scheduling parameters for a thread.  If they
 *	are not supplied, the thread`s current parameters
 *	are used if 'new_policy' is FALSE; otherwise, per-
 *	policy defaults are used.  If 'new_policy' is FALSE,
 *	limit values are taken from the thread`s processor
 *	set; otherwise, the thread`s current limit values
 *	are used.
 *
 *	For EDF, there are no limit values.  Data sets the
 *	thread`s period and deadline timers.
 */
kern_return_t
rt_thread_set_param(
	thread_t	thread,
	policy_param_t	param,
	natural_t	count,
	boolean_t	new_policy,
	boolean_t	check_limits)
{
	if (count > 0) {
	    struct policy_param_realtime *pd;
	    timespec_t	period, deadline, start_time;
	    boolean_t	periodic;
	    mach_timer_t wakeup_timer, deadline_timer;

	    /*
	     *	Data supplied.  Set period and deadline, and
	     *	change timers to match.
	     */
	    if (count < POLICY_PARAM_REALTIME_COUNT)
		return KERN_INVALID_VALUE;

	    pd = (struct policy_param_realtime *)param;
	    period = pd->period;
	    deadline = pd->deadline;

	    if (!timespec_valid(period) || !timespec_valid(deadline) ||
		!timespec_valid(pd->start_time))
	    {
		return KERN_INVALID_VALUE;
	    }

	    /*
	     *	Treat zero period or deadline as infinite
	     */
	    if (!timespec_nonzero(period)) {
		timespec_set_infinite(period);
	    }
	    if (!timespec_nonzero(deadline)) {
		timespec_set_infinite(deadline);
	    }

	    periodic = !timespec_infinite(period);

	    /*
	     *	Get period and deadline timers
	     */
	    wakeup_timer = thread->rt_wakeup_timer;
	    deadline_timer = thread->rt_deadline_timer;

	    switch (pd->start_when) {
		case START_TIME_ABSOLUTE:
		    start_time = pd->start_time;
		    if (!timespec_nonzero(start_time)) {
			/*
			 *	No start time specified - error
			 */
			return KERN_INVALID_ARGUMENT;
		    }
		    break;

		case START_TIME_RELATIVE:
		    if (wakeup_timer != 0) {
			clock_read(start_time,
				   wakeup_timer->tm_clock);
			timespec_add(start_time, pd->start_time);
		    }
		    else {
			return KERN_INVALID_ARGUMENT;
				/* relative to what? */
		    }
		    break;

		case START_TIME_NO_CHANGE:
		    if (wakeup_timer != 0 && 
			mach_timer_start_time(wakeup_timer, &start_time))
		    {
			/*
			 *	Current starting time is the
			 *	start of the current period:
			 *	the expiration time for the
			 *	periodic timer minus the
			 *	period of the timer.
			 */
		    }
		    else {
			return KERN_INVALID_ARGUMENT;
				/* no period */
		    }
		    break;

		default:
		    return KERN_INVALID_ARGUMENT;
	    }

	    /*
	     *	If there is no periodic timer, we cannot
	     *	reset the timers.  Assume that the caller
	     *	has done so.
	     */
	    if (wakeup_timer != 0) {
		/*
		 *	If the new period is infinite, cancel the periodic
		 *	timer.  Otherwise, reset it to the new period.
		 */
		if (periodic) {
		    timespec_t	new_wakeup_time;

		    new_wakeup_time = start_time;
		    timespec_add(new_wakeup_time, period);

		    (void) mach_timer_rearm(wakeup_timer,
				new_wakeup_time,
				period,
				TIMER_ABSOLUTE | TIMER_PERIODIC);
		}
		else {
		    (void) mach_timer_cancel(wakeup_timer, 0);
		}
	    }

	    if (deadline_timer != 0) {
		/*
		 *	If the new deadline is infinite, cancel the
		 *	deadline timer.  Otherwise, calculate the
		 *	new deadline, and set the timer.
		 *
		 *	The new deadline_time is start_time +
		 *			new_deadline.
		 */
		if (!timespec_infinite(deadline)) {
		    timespec_t	new_deadline_time;

		    new_deadline_time = start_time;
		    timespec_add(new_deadline_time, deadline);

		    (void) mach_timer_rearm(deadline_timer,
				new_deadline_time,
				period,
				TIMER_ABSOLUTE |
				((periodic) ? TIMER_PERIODIC
					    : 0)
				);
		}
		else {
		    (void) mach_timer_cancel(deadline_timer, 0);
		}
	    }

	    rt_sched(thread)->period = period;
	    rt_sched(thread)->deadline = deadline;
	}
	else {
	    if (new_policy) {
		/*
		 *	Thread is not already running this policy:
		 *	use default values.
		 *
		 *	Defaults are 'infinite' period and deadline.
		 */
		rt_sched(thread)->start_time.seconds = 0;
		rt_sched(thread)->start_time.nanoseconds = 0;
		timespec_set_infinite(rt_sched(thread)->period);
		timespec_set_infinite(rt_sched(thread)->deadline);
	    }
	    /* otherwise no change */
	}

	return KERN_SUCCESS;
}

/*
 *	Get the scheduling parameters and limits for a thread.
 */
kern_return_t
rt_thread_get_param(
	thread_t	thread,
	policy_param_t	param,
	natural_t	*count)
{
	mach_timer_t	wakeup_timer;

	struct policy_param_realtime *pd;

	if (*count < POLICY_PARAM_REALTIME_COUNT)
	    return KERN_INVALID_VALUE;

	pd = (struct policy_param_realtime *)param;

	pd->period   = rt_sched(thread)->period;
	pd->deadline = rt_sched(thread)->deadline;

	wakeup_timer = thread->rt_wakeup_timer;
	if (wakeup_timer != 0 &&
	    mach_timer_start_time(wakeup_timer, &pd->start_time))
	{
	    /*
	     *	The start of the current period is
	     *	the expiration time for the periodic
	     *	timer minus the period of the timer.
	     */
	}
	else {
	    /*
	     *	Can`t get start time.
	     */
	    pd->start_time.seconds = 0;
	    pd->start_time.nanoseconds = 0;
	}
	pd->start_when = START_TIME_ABSOLUTE;

	*count = POLICY_PARAM_REALTIME_COUNT;
	return KERN_SUCCESS;
}

