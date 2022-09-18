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
 * $Log:	mach_timer.c,v $
 * Revision 2.3  94/12/16  10:45:22  dbg
 * 	Use new ipc_kobject_type_t.
 * 	[94/05/26            dbg]
 * 
 * 	Exported routines now begin with 'mach_timer_'.  Renamed
 * 	'time_spec' to 'timespec'.
 * 	[94/05/23            dbg]
 * 
 * 	Fixed timer_terminate_internal: it was trying to deallocate
 * 	the port after setting it to 0.  Fixed lots of bugs in
 * 	counting timer references to threads.
 * 	[94/03/06            dbg]
 * 
 * Revision 2.2  93/11/17  17:15:58  dbg
 * 	Use thread_deallocate_nowait to remove thread reference as early
 * 	as possible.  Move syscall_timer_sleep here and make it use
 * 	continuations.
 * 	[93/07/21            dbg]
 * 
 * 	Changed timer_arm_internal to timer_sleep_periodic.
 * 	Added BUSY bit to show that timer is either enqueued
 * 	or in timeout routine.
 * 	[93/07/15            dbg]
 * 
 * 	If the expiration time is before the current time, do the
 * 	timeout action immediately.
 * 	[93/07/14            dbg]
 * 
 * 	Return actual wakeup time for timer_sleep.
 * 	[93/07/13            dbg]
 * 
 * 	Added timer_start_time.
 * 	[93/07/01            dbg]
 * 
 * 	Changed timer_ipc_lock to timer_lock, timer_lock to
 * 	timer_ref_lock.  Added mach_timer_thread_reference,
 * 	mach_timer_thread_deallocate, so that a timer that is
 * 	in use by a thread will remain even if all send rights
 * 	vanish.
 * 	[93/06/24            dbg]
 * 
 * 	Use clock_read to read clock without locking.
 * 	[93/06/18            dbg]
 * 
 * 	Add interval parameter to timer_arm_internal.
 * 	[93/05/12            dbg]
 * 
 * 	Increment overrun count in timer instead of queuing repeated
 * 	messages to an overflowing expire port.
 * 	[93/05/06            dbg]
 * 
 * 	Use normal waiting mechanism to wait for timer expiration
 * 	instead of thread_suspend.
 * 	[93/04/02            dbg]
 * 
 * 	Timer_lock does not need splhigh.
 * 	[93/02/26            dbg]
 * 
 * 	Merged into kernel mainline.
 * 
 * 	Make sure timespecs are valid
 * 	[92/09/11	savage]
 * 	Fixed race with task_lock in task_timers.
 * 	[92/07/31	savage]
 * 	Added TIMER_THREAD_SUSPEND.  Needs fix since there is a possible 
 * 	priority inversion when the thread associated with timer is 
 * 	uninterruptible.
 * 	[92/07/30	savage]
 * 	Changed time_values_t to timespec_t to account for timer hardware skew.
 * 	Changed clock parameter in timer_create to clock_t instead of constant.
 * 	[92/07/18	savage]
 * 	Added timer_info, and task_timers
 * 	[92/07/02	savage]
 * 	Added timer_cancel, cleaned up flags & types, and fixed bug with
 * 	freeing event and send right resources.  Turns out we do need
 * 	the reference counting :-)
 * 	[92/06/22	savage]
 * 	Added timer_sleep and timer_get_evc for performance reasons.
 * 	[92/06/17	savage]
 * 	Changed all references to timer_t to mach_timer_t and renamed
 * 	timer_init to mach_timer_init... timer_t really should be counter_t
 * 	[92/06/13	savage]
 * 	Exported to user (with significant "borrowing" from thread.c)
 * 	Added timer_arm, timer_create, timer_terminate, and timer_deallocate
 * 	I'm not sure about the reference counting... do we really need this?
 * 	[92/06/11	savage]
 * 	Created 
 * 	[92/05/01	savage]
 * 
 */

/*
 *	Timer alarm object, to provide accurate alarm services.
 *	Depends on a clock object.
 */

#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/timespec.h>
#include <mach/notify.h>
#include <device/device_types.h>
#include <ipc/ipc_port.h>
#include <ipc/ipc_space.h>
#include <kern/eventcount.h>
#include <kern/kern_io.h>
#include <kern/mach_clock.h>
#include <kern/queue.h>
#include <kern/lock.h>
#include <kern/mach_param.h>
#include <kern/mach_timer.h>
#include <kern/sched_prim.h>
#include <kern/task.h>
#include <kern/zalloc.h>
#include <kern/memory.h>
#include <machine/machspl.h>	/* For def'n of splsched() */

struct zone		*timer_zone;
struct mach_timer	timer_template;

/*
 *	Expiration routines
 */
void mach_timer_expire_synch(void *);	/* wakeup */
void mach_timer_expire_event(void *);	/* event signal */
void mach_timer_expire_message(void *);	/* message/suspend */

void mach_timer_no_senders(
	ipc_port_t		port,
	mach_port_mscount_t	make_send_count);	/* forward */

/*
 *	Kernel object type for a timer
 */
struct ipc_kobject_type	ikot_timer = {
	mach_timer_no_senders,	/* no more senders */
	0,			/* destroy */
	FALSE,			/* use page list */
	FALSE			/* steal pages */
};

/*
 *	Routine:	mach_timer_init
 *	Purpose:	Initialize memory, queues and locks for timer package
 *	Conditions:	None
 */
void mach_timer_init(void)
{
	timer_zone = zinit(
			sizeof(mach_timer_data_t),
			TIMER_MAX * sizeof(mach_timer_data_t),
			TIMER_CHUNK * sizeof(mach_timer_data_t),
			FALSE, "timers");

	/* timer_template.tm_chain (later) */
	timer_template.tm_expire_time.seconds = 0;
	timer_template.tm_expire_time.nanoseconds = 0;
	/* timer_template.tm_fcn (later) */
	/* timer_template.tm_param (later) */
	timer_template.tm_flags = TELT_UNSET;
	/* timer_template.tm_clock (later) */
	timer_template.tm_period.seconds = 0;
	timer_template.tm_period.nanoseconds = 0;

	/* timer_template.tm_self (later) */
	/* timer_template.tm_lock (later) */
	/* timer_template.tm_ref_lock (later) */

	/* one ref for being alive, the other for the caller */
	timer_template.tm_ref_count = 2;

	timer_template.tm_misc = TM_ACTIVE;
	timer_template.tm_expire = IP_NULL;

	/* No event allocated yet... */
	timer_template.tm_event.ev_id = 0;
	timer_template.tm_event.sanity = ((struct evc *)0);

	timer_template.tm_thread = THREAD_NULL;
	timer_template.tm_overruns = 0;
}

/*
 *	Routine:	mach_timer_deallocate
 *	Purpose:	Decrement timer reference count; if it's zero then
 *			free up the kernel resources associated with the
 *			timer.
 *	Conditions:	None
 */
void mach_timer_deallocate(
	mach_timer_t	timer)
{
	if (timer == TIMER_NULL)
	    return;

	timer_ref_lock(timer);
	if (--timer->tm_ref_count > 0) {
		timer_ref_unlock(timer);
		return;
	}
	timer_ref_unlock(timer);

	assert(!(timer->tm_misc & TM_ACTIVE));
	assert(timer->tm_flags == TELT_UNSET);

	/* give up kernel memory */
	zfree(timer_zone, (vm_offset_t) timer);
}


/*
 *	Routine:	timer_reference
 *	Purpose:	Increment timer reference count
 *	Conditions:	None
 */
void mach_timer_reference(
	mach_timer_t	timer)
{
	if (timer == TIMER_NULL)
	    return;

	timer_ref_lock(timer);
	timer->tm_ref_count++;
	timer_ref_unlock(timer);
}

/*
 *	Routine:	convert_port_to_timer
 *	Purpose:	Convert from a port to a timer.  If the port isn't
 *			valid, or doesn't represent a timer then return
 *			TIMER_NULL.  Produces a timer reference.
 *	Conditions:	None
 */
mach_timer_t convert_port_to_timer(
	ipc_port_t port)
{
	mach_timer_t timer = TIMER_NULL;

	if (IP_VALID(port)) {
		ip_lock(port);
		if (ip_active(port) && port->ip_kotype == &ikot_timer) {
			timer = (mach_timer_t) port->ip_kobject;
			mach_timer_reference(timer);
		}
		ip_unlock(port);
	}

	return timer;
}


/*
 *	Routine:	convert_timer_to_port
 *	Purpose:	Convert from a port to a timer.  Consumes a timer
 *			reference.
 *	Conditions:	None
 */
ipc_port_t convert_timer_to_port(
	mach_timer_t timer)
{
	ipc_port_t port;

	timer_lock(timer);

	if (timer->tm_misc & TM_ACTIVE) {
	    assert(timer->tm_self != IP_NULL);
	    port = ipc_port_make_send(timer->tm_self);
	} else {
	    port = IP_NULL;
	}

	timer_unlock(timer);

	mach_timer_deallocate(timer);
	return port;
}

/*
 *	Routine:	mach_timer_disarm
 *	Purpose:	SAFELY take a timer off its queue, wakeup any
 *			threads waiting on it, and free any expired
 *			send rights.
 *	Conditions:	Caller should hold the timer lock.
 */
void mach_timer_disarm(
	mach_timer_t	timer)
{
	if (timer_elt_dequeue(&timer->te)) {
	    /*
	     *	Was on queue.  If a thread is waiting
	     *	for the timer, wake it up.  This
	     *	frees the timer`s reference to the
	     *	thread if the timer is not periodic.
	     */
	    if (timer->tm_fcn == mach_timer_expire_synch)
		mach_timer_expire_synch(timer->tm_param);

	    /*
	     *	Timer is no longer busy.
	     */
	    timer->tm_misc &= ~TM_BUSY;
	}
}


/*
 *	Routine:	timer_create
 *	Purpose:	Allocate a new timer object in the kernel,
 *			and enable its ipc connection to the world.
 *
 *	Conditions:	None
 */
kern_return_t mach_timer_create(
	register mach_clock_t	clock,
	register mach_timer_t	*timer)
{
	register mach_timer_t	new_timer;
	ipc_port_t	kport;
	ipc_port_t	kport_send_once;
	ipc_port_t	nprev;

	if (clock == MACH_CLOCK_NULL)
	    return KERN_INVALID_ARGUMENT;

	if (!clock->can_time)
	    return KERN_INVALID_ARGUMENT;

	new_timer = (mach_timer_t) zalloc(timer_zone);
	if (new_timer == TIMER_NULL)
	    return KERN_RESOURCE_SHORTAGE;

	*new_timer = timer_template;

	/* timeout routine parameter is always timer itself */
	new_timer->tm_param = new_timer;

	/* which clock device is responsible for this timer */
	new_timer->tm_clock = clock;

	/* for serialization of access to a particular timer */
	simple_lock_init(&new_timer->tm_lock);
	simple_lock_init(&new_timer->tm_ref_lock);

	/* setup IPC structures and let it talk to the world */

	kport = ipc_port_alloc_kernel();
	if (kport == IP_NULL) {
	    /*
	     *	No resources
	     */
	    zfree(timer_zone, (vm_offset_t) new_timer);
	    return KERN_RESOURCE_SHORTAGE;
	}

	new_timer->tm_self = kport;
	ipc_kobject_set(kport, (ipc_kobject_t) new_timer, &ikot_timer);

	/*
	 *	Add no-more-senders notify request, sent
	 *	to timer port.  Since current make-send count
	 *	is 0, sync must be 1 to avoid an immediate
	 *	notification.  One send right will be created
	 *	when the timer port is returned to caller.
	 */
	kport_send_once = ipc_port_make_sonce(kport);
	ip_lock(kport);
	ipc_port_nsrequest(kport, 1, kport_send_once, &nprev);
			/* unlocks kport */
	assert(nprev == IP_NULL);

	*timer = new_timer;
	return KERN_SUCCESS;
}

/*
 *	Internal routine to terminate a timer, shared between
 *	timer_terminate and timer_no_more_senders.
 *
 *	Timer is locked on entry; will be unlocked (and perhaps
 *	deallocated) on exit.
 */
void mach_timer_terminate_internal(
	mach_timer_t timer)
{
	ipc_port_t	kport;
	thread_t	old_thread;

	/*
	 *	Remove timer from queue.
	 */
	mach_timer_disarm(timer);

	/*
	 *	Mark timer inactive, and remove its port.
	 */
	timer->tm_misc &= ~TM_ACTIVE;
	kport = timer->tm_self;
	timer->tm_self = IP_NULL;
	ipc_kobject_set(kport, IKO_NULL, IKOT_NONE);

	/*
	 *	Free event resources
	 */
	if (timer->tm_misc & TM_EVENT_ALLOC)
	    evc_destroy(&timer->tm_event);

	old_thread = timer->tm_thread;
	timer_unlock(timer);

	/*
	 *	Release reference and send right for expire port.
	 */
	if (IP_VALID(timer->tm_expire))
	    ipc_port_release_send(timer->tm_expire);

	/*
	 *	Deallocate the timer`s thread reference
	 *	if there was one.
	 */
	if (old_thread != THREAD_NULL)
	    thread_deallocate(old_thread);

	/*
	 *	Deallocate the timer port, and the timer structure
	 *	itself.
	 */
	ipc_port_dealloc_kernel(kport);
	mach_timer_deallocate(timer);
}


/*
 *	Routine:	timer_terminate
 *	Purpose:	Destroy a timer.  If the timer is already being killed
 *			then we will return KERN_FAILURE
 *	Conditions:	None
 */
kern_return_t mach_timer_terminate(
	register mach_timer_t	timer)
{
	if (timer == TIMER_NULL)
	    return KERN_INVALID_ARGUMENT;
	   
	timer_lock(timer);

	/*
	 *	Is it already being killed?  If not then mark it as such.
	 */
	if (!(timer->tm_misc & TM_ACTIVE)) {
	    timer_unlock(timer);
	    return KERN_FAILURE;
	}

	/*
	 *	Destroy the timer (code is shared with no-more-senders)
	 */
	mach_timer_terminate_internal(timer);

	return KERN_SUCCESS;
}

/*
 *	Routine:	mach_timer_thread_reference
 *	Purpose:
 *		Create a internal reference to a timer from a thread,
 *		to use the timer as the deadline or wakeup timer for
 *		the thread.  This reference must keep the timer alive
 *		just as a send-once reference would; further rights
 *		to the timer port can be obtained from the thread.
 *
 *	Implementation:
 *		Make a new send right to the timer port.
 */
boolean_t
mach_timer_thread_reference(
	mach_timer_t	timer)
{
	if (timer == TIMER_NULL)
	    return TRUE;

	timer_lock(timer);
	if (!(timer->tm_misc & TM_ACTIVE)) {
	    timer_unlock(timer);
	    return FALSE;	/* timer died suddenly */
	}

	/*
	 *	Make a new send right to the timer port.
	 */
	(void) ipc_port_make_send(timer->tm_self);
	timer_unlock(timer);

	return TRUE;
}

/*
 *	Routine:	mach_timer_thread_deallocate
 *	Purpose:
 *		Remove an internal reference to a timer from a thread.
 *		If the timer now has no more send rights to its kernel
 *		port, terminate the timer.
 *
 *	Implementation:
 *		Release the corresponding send right for the timer
 *		port.
 */
void mach_timer_thread_deallocate(
	mach_timer_t	timer)
{
	ipc_port_t	kport;

	if (timer == TIMER_NULL)
	    return;

	timer_lock(timer);
	assert(timer->tm_misc & TM_ACTIVE);

	/*
	 *	Release a send right to the timer port.
	 *	Since this may send a no-more-senders
	 *	message, we must unlock the timer first.
	 *	The port is safe, since it has an extra
	 *	reference corresponding to the send right
	 *	that we are releasing.  ipc_port_release_send
	 *	will also release the reference.
	 */
	kport = timer->tm_self;
	timer_unlock(timer);

	ipc_port_release_send(kport);
}


/*
 *	Routine:	mach_timer_get_evc
 *	Purpose:	Associate timer with event handle and pass it back to
 *			the user.  This is a significant performance
 *			improvement over a message, but it conveys less
 *			information and is only quasi-supported.
 *	Conditions:	None.
 */
kern_return_t mach_timer_get_evc(
	register mach_timer_t	timer,
	natural_t		*event)
{
	if (timer == TIMER_NULL)
	    return KERN_INVALID_ARGUMENT;

	timer_lock(timer);

	/*
	 *	Do we already have an event?
	 */
	if (timer->tm_misc & TM_EVENT_ALLOC) {
	    timer_unlock(timer);
	    return KERN_SUCCESS;
	}

	if (evc_init(&timer->tm_event) != KERN_SUCCESS) {
	    timer_unlock(timer);
	    return KERN_RESOURCE_SHORTAGE;
	}

	*event = timer->tm_event.ev_id;
	
	/* Timer now owns event */
	timer->tm_misc |= TM_EVENT_ALLOC;

	timer_unlock(timer);

	return KERN_SUCCESS;
}


/*
 *	Routine:	mach_timer_arm
 *	Purpose:	Attempts to set a timer and enqueue it in a clock 
 *			queue.  This call may fail if the timer is already 
 *			enqueued, if it is being killed, if the port specified
 *			for timer expiration messages is invalid, if the user
 *			specifies an event timer without allocating an event
 *			first, or if the specified expiration time has
 *			already passed.
 *	Conditions:	None
 */
kern_return_t mach_timer_arm(
	register mach_timer_t	timer,
	timespec_t		expire_time,
	timespec_t		interval_time,
	register ipc_port_t	expire_port,
	thread_t		thread,
	register int		flags)
{	
	if (timer == TIMER_NULL)
	    return KERN_INVALID_ARGUMENT;

	if (!timespec_valid(expire_time) ||
	    ((flags & TIMER_PERIODIC) && !timespec_valid(interval_time)))
	{
	    return KERN_INVALID_VALUE;
	}

	timer_lock(timer);

	/*
	 *	Is the timer currently being killed or is it enqueued?
	 */
	if (!(timer->tm_misc & TM_ACTIVE) || (timer->tm_misc & TM_BUSY)) {
	    timer_unlock(timer);
	    return KERN_FAILURE;
	}

	/*
	 *	If TIMER_PERIODIC flag is set then the interval_time argument
	 *	must be more than the clock resolution.
	 */
	if (flags & TIMER_PERIODIC) {
	    if (interval_time.seconds == 0 &&
		interval_time.nanoseconds < timer->tm_clock->resolution)
	    {
		timer_unlock(timer);
		return KERN_INVALID_VALUE;
	    }
	    timer->tm_period = interval_time;
	    timer->tm_flags |= TELT_PERIODIC;
	}
	else {
	    timer->tm_flags &= ~TELT_PERIODIC;
	}

	/*
	 *	If the user claims that this is an event timer then make
	 *	sure he's allocated the event already.
	 */  
	if (flags & TIMER_EVENT) {
	    if (!(timer->tm_misc & TM_EVENT_ALLOC)) {
		timer_unlock(timer);
		return KERN_INVALID_ARGUMENT;
	    }
	    timer->tm_event.count = 0;
	    timer->tm_fcn = mach_timer_expire_event;
	}
	else {
	    /*
	     *	It's a Message timer... now check to see if
	     *	the expire port is valid?
	     */
	    if (!IP_VALID(expire_port)) {
		timer_unlock(timer);
		return KERN_INVALID_CAPABILITY;
	    }
	    /*
	     *	Donate expire port reference and send right to timer
	     */
	    assert(timer->tm_expire == IP_NULL);
	    timer->tm_expire = expire_port;
	    timer->tm_fcn = mach_timer_expire_message;
	}
		
	/*
	 *	Save the thread to be suspended 
	 */
	if (flags & TIMER_THREAD_SUSPEND) {
	    if (thread == THREAD_NULL) {
		timer->tm_expire = IP_NULL;	/* error return will dealloc */
		timer_unlock(timer);
		return KERN_INVALID_ARGUMENT;
	    }
	    assert(timer->tm_thread == THREAD_NULL);
	    timer->tm_thread = thread;
	    thread_reference(thread);
	    timer->tm_misc |= TM_SUSPEND;
	}

	/*
	 *	Mark the timer busy, and put it on the
	 *	clock`s timeout queue.
	 */
	timer->tm_misc |= TM_BUSY;
	if (!timer_elt_enqueue(&timer->te,
			       expire_time,
			       (flags & TIMER_ABSOLUTE) != 0))
	{
	    /*
	     *	Time value was less than current time.
	     *	Make the timer expire immediately.
	     */
	    timer_unlock(timer);
	    (*timer->tm_fcn)(timer->tm_param);	/* resets 'busy' */
	}
	else {
	    timer_unlock(timer);
	}

	return KERN_SUCCESS;
}


/*
 *	Routine:	timer_sleep
 *	Purpose:	Attempts to set a timer and enqueue it in a clock 
 *			queue.  Similar to timer_arm except that the calling
 *			thread is blocked on on the timer and will be awakened
 *			when the timer expires.
 *	Conditions:	None
 */
kern_return_t mach_timer_sleep(
	mach_timer_t	timer,
	timespec_t	expire_time,
	int		flags,
	timespec_t	*wakeup_time)
{	
	kern_return_t	kr;
	thread_t	thread = current_thread();

	if (timer == TIMER_NULL)
	    return KERN_INVALID_ARGUMENT;

	if (!timespec_valid(expire_time))
	    return KERN_INVALID_VALUE;

	timer_lock(timer);

	/*
	 *	Is the timer currently enqueued or being killed?
	 */
	if (!(timer->tm_misc & TM_ACTIVE) || (timer->tm_misc & TM_BUSY)) {
	    timer_unlock(timer);
	    return KERN_FAILURE;
	}

	assert(timer->tm_thread == THREAD_NULL);
	timer->tm_thread = thread;
	thread_reference(thread);		/* for timer */
	timer->tm_fcn = mach_timer_expire_synch;

	timer->tm_misc |= TM_BUSY;
	if (!timer_elt_enqueue(&timer->te,
			       expire_time,
			       (flags & TIMER_ABSOLUTE) != 0))
	{
	    /*
	     *	Time has already passed - don`t sleep.
	     *	Release timer`s reference to thread.
	     */
	    timer->tm_misc &= ~TM_BUSY;
	    thread_deallocate(thread);
	    timer_unlock(timer);
	    kr = KERN_SUCCESS;
	}
	else {
	    /*
	     *	Wait for timer to expire.  Expiration
	     *	releases timer`s reference to thread.
	     */
	    thread_will_wait(thread);
	    timer_unlock(timer);
	    thread_block(CONTINUE_NULL);
	    kr = (thread->wait_result == THREAD_INTERRUPTED)
			? KERN_ABORTED
			: KERN_SUCCESS;
	}

	clock_read(*wakeup_time, timer->tm_clock);

	return kr;
}

/*
 *	Routine:	syscall_mach_timer_sleep
 *	Purpose:	same as mach_timer_sleep, but called as a trap.
 *			Uses a continuation.
 */

struct mach_timer_sleep_save {
	mach_timer_t	timer;
	timespec_t	*wakeup_time;
};

#define	SAVE(thread)	((struct mach_timer_sleep_save *)&(thread)->saved)

no_return
mach_timer_sleep_continue(void)
{
	thread_t	thread = current_thread();
	mach_timer_t	timer = SAVE(thread)->timer;
	timespec_t	*wakeup_time = SAVE(thread)->wakeup_time;
	kern_return_t	kr = (thread->wait_result == THREAD_INTERRUPTED)
				? KERN_ABORTED
				: KERN_SUCCESS;
	timespec_t	wake_time;

	clock_read(wake_time, timer->tm_clock);
	mach_timer_deallocate(timer);

	(void) copyout(&wake_time,
		       wakeup_time,
		       sizeof(timespec_t));
	thread_syscall_return(kr);
	/*NOTREACHED*/
}

extern mach_timer_t port_name_to_timer(mach_port_t);

kern_return_t syscall_mach_timer_sleep(
	mach_port_t	timer_port,
	timespec_t	expire_time,
	int		flags,
	timespec_t	*wakeup_time)
{
	thread_t	thread = current_thread();
	mach_timer_t	timer;

	timer = port_name_to_timer(timer_port);
	if (timer == TIMER_NULL)
	    return KERN_INVALID_ARGUMENT;

	if (!timespec_valid(expire_time)) {
	    mach_timer_deallocate(timer);
	    return KERN_INVALID_VALUE;
	}

	/*
	 *	Save the values we will need when the
	 *	continuation is called.
	 */
	SAVE(thread)->timer = timer;
	SAVE(thread)->wakeup_time = wakeup_time;

	timer_lock(timer);

	/*
	 *	Is the timer currently enqueued or being killed?
	 */
	if (!(timer->tm_misc & TM_ACTIVE) || (timer->tm_misc & TM_BUSY)) {
	    timer_unlock(timer);
	    mach_timer_deallocate(timer);
	    return KERN_FAILURE;
	}

	assert(timer->tm_thread == THREAD_NULL);
	timer->tm_thread = thread;
	thread_reference(thread);	/* for timer */
	timer->tm_fcn = mach_timer_expire_synch;

	timer->tm_misc |= TM_BUSY;
	if (!timer_elt_enqueue(&timer->te,
			       expire_time,
			       (flags & TIMER_ABSOLUTE) != 0))
	{
	    /*
	     *	Time has already passed - don`t sleep.
	     *	Release timer`s reference to thread.
	     */
	    timer->tm_misc &= ~TM_BUSY;
	    timer_unlock(timer);
	    thread_deallocate(thread);
	    mach_timer_sleep_continue();
	    /*NOTREACHED*/
	}
	else {
	    /*
	     *	Wait for timer to expire.  Expiration
	     *	releases timer`s reference to thread.
	     */
	    thread_will_wait(thread);
	    timer_unlock(timer);
	    thread_block_noreturn(mach_timer_sleep_continue);
	    /*NOTREACHED*/
	}
}


	
/*
 *	Routine:	timer_cancel
 *	Purpose:	Attempts to cancel a timer which has been enqueued.
 *			If the timer is periodic and flags specifies
 *			TIMER_PERIODIC then only the current iteration of
 *			the timer is canceled.  If a thread is sleeping on
 *			the timer then it will wake up.
 *	Conditions:	None
 */
kern_return_t mach_timer_cancel(
	mach_timer_t	timer,
	int		flags)
{
	ipc_port_t	expire_port = IP_NULL;
	thread_t	thread = THREAD_NULL;

	if (timer == TIMER_NULL)
	    return KERN_INVALID_ARGUMENT;

	timer_lock(timer);
	
	if (!(timer->tm_misc & TM_ACTIVE) || !(timer->tm_misc & TM_BUSY)) {
	    timer_unlock(timer);
	    return KERN_FAILURE;
	}
	
	mach_timer_disarm(timer);

	/*
	 *	If the timer is periodic and the user specified that
	 *	we should only cancel one iteration of the timer
	 *	then re-enqueue it.
	 */

	if ((timer->tm_flags & TELT_PERIODIC) &&
	    (flags & TIMER_PERIODIC))
	{
	    timespec_add(timer->tm_expire_time, timer->tm_period);
	    timer->tm_misc |= TM_BUSY;
	    (void) timer_elt_enqueue(&timer->te, timer->tm_expire_time, TRUE);
	}
	else {
	    /*
	     *	Mark timer non-periodic - we are cancelling all iterations.
	     */
	    timer->tm_flags &= ~TELT_PERIODIC;

	    /*
	     *	Release reference and send right to the expire_port,
	     *	after we unlock the timer.
	     */
	    expire_port = timer->tm_expire;
	    timer->tm_expire = IP_NULL;

	    /*
	     *	Also release reference to the thread.
	     */
	    thread = timer->tm_thread;
	    timer->tm_thread = THREAD_NULL;
	}

	timer_unlock(timer);

	if (IP_VALID(expire_port))
	    ipc_port_release_send(expire_port);
	if (thread != THREAD_NULL)
	    thread_deallocate(thread);

	return KERN_SUCCESS;
}

/*
 *	Routine:	timer_info
 *	Purpose:	Returns the current state of the specified timer.
 *	Conditions:	None
 */
kern_return_t mach_timer_info(
	register mach_timer_t	timer,
	int			flavor,
	mach_clock_t		*clock,		/* out */
	ipc_port_t		*expire_port,	/* out */
	thread_t		*thread,	/* out */
	mach_timer_info_t	timer_info_out,	/* pointer to OUT array */
	natural_t		*timer_info_count)	/*IN/OUT*/
{

	if (timer == TIMER_NULL)
	    return KERN_INVALID_ARGUMENT;

	if (flavor == MACH_TIMER_BASIC_INFO) {
	    register mach_timer_basic_info_t	basic_info;

	    if (*timer_info_count < MACH_TIMER_BASIC_INFO_COUNT) {
		return KERN_INVALID_ARGUMENT;
	    }

	    basic_info = (mach_timer_basic_info_t) timer_info_out;

	    timer_lock(timer);

	    /*
	     *	Return ports
	     */
	    *clock = timer->tm_clock;

	    if (IP_VALID(timer->tm_expire)) {
		*expire_port = ipc_port_copy_send(timer->tm_expire);
	    } else {
		*expire_port = MACH_PORT_NULL;
	    }

	    if (timer->tm_thread != THREAD_NULL) {
	    	thread_reference(timer->tm_thread);
		*thread = timer->tm_thread;
	    } else {
		*thread = MACH_PORT_NULL;
	    }

	    /*
	     *	Fill in info
	     */
	    basic_info->type = 0;
	    if (timer->tm_flags & TELT_ABSOLUTE)
		basic_info->type |= TIMER_ABSOLUTE;
	    if (timer->tm_flags & TELT_PERIODIC)
		basic_info->type |= TIMER_PERIODIC;
	    if (timer->tm_fcn == mach_timer_expire_event)
		basic_info->type |= TIMER_EVENT;
	    if (timer->tm_misc & TM_SUSPEND)
		basic_info->type |= TIMER_THREAD_SUSPEND;

	    basic_info->expire_time = timer->tm_expire_time;
	    basic_info->interval_time = timer->tm_period;
	    basic_info->event = timer->tm_event.ev_id;
	    basic_info->overruns = timer->tm_overruns;
	    basic_info->enqueued = (timer->tm_misc & TM_BUSY) != 0;

	    timer_unlock(timer);

	    *timer_info_count = MACH_TIMER_BASIC_INFO_COUNT;
	    return KERN_SUCCESS;
	}
	else {
	    return KERN_INVALID_ARGUMENT;
	}
}

/*
 *	What to do when timer expires:
 */

/*
 *	Wakeup thread.
 */
void mach_timer_expire_synch(void *param)
{
	mach_timer_t	timer = (mach_timer_t) param;

	thread_go(timer->tm_thread);

	timer_lock(timer);
	if (!(timer->tm_flags & TELT_PERIODIC)) {
	    timer->tm_misc &= ~TM_BUSY;
	    thread_deallocate_nowait(timer->tm_thread);
	    timer->tm_thread = THREAD_NULL;
	}
	timer_unlock(timer);
}

/*
 *	Signal event.
 */
void mach_timer_expire_event(void *param)
{
	mach_timer_t	timer = (mach_timer_t) param;

	evc_signal(&timer->tm_event);

	timer_lock(timer);
	if (!(timer->tm_flags & TELT_PERIODIC))
	    timer->tm_misc &= ~TM_BUSY;
	timer_unlock(timer);
}

/*
 *	Send message; optionally suspend the thread.
 */
extern kern_return_t
mach_timer_expire(ipc_port_t expire_port, timespec_t time);

void mach_timer_expire_message(void *param)
{
	mach_timer_t	timer = (mach_timer_t) param;
	ipc_port_t	expire_port;
	timespec_t	cur_time;
	thread_t	thread;

	thread = timer->tm_thread;
	if (timer->tm_misc & TM_SUSPEND)
	    thread_suspend_nowait(thread);

	timer_lock(timer);
	expire_port = timer->tm_expire;

	if (!IP_VALID(expire_port)) {
	    /*
	     *	Port expired on the previous iteration,
	     *	but we didn`t have the proper locking to
	     *	notice it then.  Clear the timer.
	     */
	    timer->tm_expire = IP_NULL;
	    timer->tm_thread = THREAD_NULL;
	    timer->tm_flags &= ~TELT_PERIODIC;
	    timer->tm_misc &= ~(TM_BUSY | TM_SUSPEND);
	    timer_unlock(timer);

	    if (thread != THREAD_NULL)
		thread_deallocate_nowait(thread);
	}

	else if (timer->tm_flags & TELT_PERIODIC) {
	    /*
	     *	Check here for port overflow.
	     *	If the port is full, don`t send the
	     *	message, since that will eventually
	     *	fill the kernel with undelivered
	     *	timer expirations.  Instead increment
	     *	the timer`s overrun counter.
	     *
	     *	(should be detected by the return code
	     *	from timer_expire, but that requires
	     *	patching it to not use SEND_ALWAYS.)
	     */
	    ip_lock(expire_port);
	    if (ip_active(expire_port) &&
		expire_port->ip_receiver != ipc_space_kernel &&
		expire_port->ip_msgcount >= expire_port->ip_qlimit)
	    {
		/*
		 *	Port is over its queue limit.
		 *	Increment timer overrun counter.
		 */
		ip_unlock(expire_port);
		timer->tm_overruns++;
		timer_unlock(timer);
	    }
	    else {
		/*
		 *	Port is OK.
		 *	Clone another send right for the expire
		 *	port (for the next expiration), and send
		 *	the message.
		 */
		ip_unlock(expire_port);
		timer->tm_expire = ipc_port_copy_send(expire_port);
		timer_unlock(timer);

		clock_read(cur_time, timer->tm_clock);
		(void) mach_timer_expire(expire_port, cur_time);
					/* may NOT block */
	    }
	}
	else {
	    /*
	     *	Single expiration.  Move send right
	     *	to message, and clear the timer.
	     */
	    timer->tm_expire = IP_NULL;
	    timer->tm_thread = THREAD_NULL;
	    timer->tm_misc &= ~(TM_BUSY | TM_SUSPEND);
	    timer_unlock(timer);

	    if (thread != THREAD_NULL)
		thread_deallocate_nowait(thread);

	    clock_read(cur_time, timer->tm_clock);
	    (void) mach_timer_expire(expire_port, cur_time);
					/* may NOT block */
	}
}

/*
 *	Internal version of timer_sleep that allows
 *	sleeping on a periodic timer.
 */
kern_return_t mach_timer_sleep_periodic(
	mach_timer_t	timer,
	timespec_t	expire_time,
	timespec_t	interval_time,
	thread_t	thread,
	int		flags)
{
	timer_lock(timer);

	assert((timer->tm_misc & TM_ACTIVE) && !(timer->tm_misc & TM_BUSY));
	assert(timer->tm_expire == IP_NULL);
	assert(timer->tm_thread == THREAD_NULL);

	thread_reference(thread);		/* keep for timer */
	timer->tm_thread = thread;
	timer->tm_fcn = mach_timer_expire_synch;

	if (flags & TIMER_PERIODIC) {
	    timer->tm_period = interval_time;
	    timer->tm_flags |= TELT_PERIODIC;
	}
	else {
	    timer->tm_flags &= ~TELT_PERIODIC;
	}

	timer->tm_misc |= TM_BUSY;
	if (!timer_elt_enqueue(&timer->te,
			       expire_time,
			       (flags & TIMER_ABSOLUTE) != 0))
	{
	    /*
	     *	Time already passed.  Don`t make thread sleep.
	     *	Free timer`s reference to thread.
	     */
	    timer->tm_misc &= ~TM_BUSY;
	    timer_unlock(timer);
	    thread_deallocate(thread);
	}
	else {
	    /*
	     *	Make thread wait for timer.  Expiration
	     *	releases timer`s reference to thread.
	     */
	    thread_will_wait(thread);
	    timer_unlock(timer);
	}

	return KERN_SUCCESS;
}

/*
 *	Change the expiration time or period of a timer
 */
kern_return_t mach_timer_rearm(
	mach_timer_t	timer,
	timespec_t	new_expire_time,
	timespec_t	new_interval,
	int		flags)
{
	timer_lock(timer);

	(void) timer_elt_dequeue(&timer->te);

	if (flags & TIMER_PERIODIC) {
	    timer->tm_period = new_interval;
	    timer->tm_flags |= TELT_PERIODIC;
	}
	else {
	    timer->tm_flags &= ~TELT_PERIODIC;
	}

	timer->tm_flags |= TM_BUSY;
	if (!timer_elt_enqueue(&timer->te,
			       new_expire_time,
			       (flags & TIMER_ABSOLUTE) != 0))
	{
	    /*
	     *	Time already expired - do action.
	     */
	    timer_unlock(timer);
	    (*timer->tm_fcn)(timer->tm_param);	/* resets 'busy' */
	}
	else {
	    timer_unlock(timer);
	}
	return KERN_SUCCESS;
}

/*
 *	Return the time that the *current* period of a periodic
 *	timer started: expiration_time minus interval.
 *
 *	Returns FALSE if the timer is not queued or not periodic.
 */
boolean_t mach_timer_start_time(
	mach_timer_t	timer,
	timespec_t	*start_time)	/* OUT */
{
	spl_t	s;

	/*
	 *	Lock the timer, to check whether it is
	 *	enqueued.
	 */
	timer_lock(timer);
	if (!(timer->tm_misc & TM_ACTIVE) ||
	    ((timer->tm_flags & (TELT_SET|TELT_PERIODIC))
		!= (TELT_SET|TELT_PERIODIC)))
	{
	    timer_unlock(timer);
	    return FALSE;
	}

	/*
	 *	Lock the clock, to keep the timer from expiring
	 *	while we read it.
	 */
	s = splsched();
	clock_queue_lock(timer->tm_clock);

	/*
	 *	The start of the *current* period is
	 *	<expire_time> - <interval>.
	 */
	*start_time = timer->tm_expire_time;
	timespec_subtract(*start_time, timer->tm_period);

	clock_queue_unlock(timer->tm_clock);
	splx(s);

	return TRUE;
}


/*
 *	Make a thread wait for the next expiration of
 *	a periodic timer.
 */
void mach_timer_wait(
	mach_timer_t	timer,
	thread_t	thread)
{
	timer_lock(timer);

	thread_will_wait(thread);	/* XXX doesn`t need timer! */

	timer_unlock(timer);
}

/*
 *	Handle no_more_senders notification by terminating timer.
 */
void mach_timer_no_senders(
	ipc_port_t		port,
	mach_port_mscount_t	make_send_count)
{
	mach_timer_t	timer;

	/*
	 *	Get the timer from the port, and check that
	 *	the make-send count is still the same as
	 *	the count received in the no-more-senders
	 *	notification.
	 */

	assert(IP_VALID(port));
	timer = convert_port_to_timer(port);
	if (timer == TIMER_NULL)
	    return;

	timer_lock(timer);
	ip_lock(port);
	if (ip_active(port) &&
	    port->ip_kotype == &ikot_timer &&
	    port->ip_mscount == make_send_count)
	{
	    /*
	     *	Port is still active, no new send rights have been
	     *	created, and there are no internal references from
	     *	threads.
	     *
	     *	Set timer inactive to prevent convert_timer_to_port
	     *	from making new send rights.  Then terminate the
	     *	timer.
	     */
	    timer->tm_misc &= ~TM_ACTIVE;
	    ip_unlock(port);

	    mach_timer_terminate_internal(timer);
		/* timer is now unlocked */
	}
	else {
	    timer_unlock(timer);
	}

	/*
	 *	Deallocate reference from convert_port_to_timer.
	 */
	mach_timer_deallocate(timer);

}

