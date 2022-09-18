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
 * $Log:	mach_clock.h,v $
 * Revision 2.2  94/12/16  10:45:05  dbg
 * 	Renamed to mach_clock.h, and merged with RT-MACH changes.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  17:07:22  dbg
 * 	Added check_seconds and clock_time, so that time can be
 * 	read without having to lock the clock.
 * 	[93/06/18            dbg]
 * 
 * 	Added correction_delta, correction_count.
 * 	[93/06/02            dbg]
 * 
 * 	Moved timer element definitions to kern/mach_timer.h.
 * 	[93/04/09            dbg]
 * 
 * 	Moved user-visible definitions to kern/clock.h.
 * 
 * 	Created
 * 	[92/07/12	savage]
 * 
 */
/*
 *	File:	kern/clock.h
 *	Author:
 *		Stefan Savage and David Golub, 1993
 *
 *	This file contains the definition for kernel clock objects.
 *	A clock is a time keeper that increments periodically and
 *	may have an associated queue of timer elements for alarms,
 *	periodic wakeups, and the like.
 */
#ifndef	_KERN_MACH_CLOCK_H_
#define	_KERN_MACH_CLOCK_H_

#include <mach_kdb.h>

#include <mach/machine/vm_types.h>

#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/port.h>
#include <mach/timespec.h>

#include <kern/host.h>
#include <kern/kern_types.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/mach_timer.h>

#include <ipc/ipc_types.h>

/*
 *	Type declarations
 */
struct mach_clock;		/* forward */

typedef	char			mach_clock_name_t[128];

/*
 *	Operations on a clock
 */
struct clock_ops {
	kern_return_t	(*set_time)(
		struct mach_clock *clock,
		timespec_t	*new_time);	/* IN/OUT */
				/*
				 * set the current time for the clock.
				 * At the end of the call, timespec
				 * will contain the clock`s current
				 * time.
				 */
	kern_return_t	(*set_resolution)(
		struct mach_clock *clock,
		natural_t	*resolution,	/* IN/OUT */
		integer_t	*skew);		/* IN/OUT */
				/*
				 * Set the resolution and skew for
				 * the clock.  At the end of the
				 * call, resolution and skew contain
				 * the current values from the clock.
				 *
				 * The actual clock resolution may
				 * not be updated until the end of
				 * the current clock tick.
				 */
	void		(*set_timeout)(
		struct mach_clock *clock);
				/*
				 * Update any hardware interrupt timer
				 * attached to the clock.  This is
				 * called whenever a timer is enqueued
				 * or dequeued from the clock.  It
				 * is not required.
				 */
	void		(*update)(
		struct mach_clock *clock);
				/*
				 * Update the clock`s current time into
				 * clock->time and clock->check_seconds.
				 * It is only required for aperiodic
				 * clocks.
				 */
	void		(*change_resolution)(
		struct mach_clock *clock);
				/*
				 * If the clock can only change its
				 * resolution at clock interrupts,
				 * this routine is called to change
				 * the resolution to the value in
				 * newresolution +/- newskew.
				 */
	void		(*stop)(
		struct mach_clock *clock);
				/*
				 * Stop advancing time on the clock.
				 */
	void		(*start)(
		struct mach_clock *clock);
				/*
				 * Resume advancing time on the clock.
				 */
	void		(*enable_interrupts)(
		struct mach_clock *clock,
		boolean_t	on);
				/*
				 * Allow clock to interrupt.
				 */
};

#define	CLOCK_SET_TIMEOUT(clock) \
    MACRO_BEGIN \
	void (*set_timeout)(struct mach_clock *); \
	if ((set_timeout = (clock)->ops->set_timeout) != 0) \
	    (*set_timeout)((clock)); \
    MACRO_END

#define	CLOCK_UPDATE(clock) \
    MACRO_BEGIN \
	void (*update)(struct mach_clock *); \
	if ((update = (clock)->ops->update) != 0) { \
	    (*update)((clock)); \
	    clock_set_mtime((clock)); \
	} \
    MACRO_END

/*
 *	A clock.
 */
struct mach_clock {
	volatile timespec_t	time;		/* current time */
	volatile unsigned int	check_seconds;	/* to read time without lock */
	mapped_timespec_t	*mtime;		/* pointer to mapped time,
						   if clock is mapped */
	natural_t		resolution;	/* nanoseconds per 'tick' */
	integer_t		skew;		/* difference from desired
						   resolution */
	natural_t		new_resolution;	/* new resolution requested */
	integer_t		new_skew;	/* skew for new resolution */
	natural_t		best_resolution;
						/* best resolution possible
						   for this clock */
	boolean_t		periodic:1,	/* clock is periodic */
				can_time:1,	/* clock supports timeouts */
				aperiodic_update:1;
						/* clock updates aperiodic
						   clocks */
	struct clock_ops	*ops;		/* operations on clock */
	struct timer_elt_head	head;		/* queue of timers */
	decl_simple_lock_data(,queue_lock)	/* lock for queue */
	struct mach_clock *	clock_list;	/* list of all clocks */
	struct mach_clock *	aperiodic_clock_list;
						/* next aperiodic clock */

	ipc_port_t		clk_status;	/* status port */
	ipc_port_t		clk_control;	/* control port */
	char			*name;		/* ASCII name */
	void			*data;		/* pointer to hardware data */
#if	MACH_KDB
	timespec_t		savetime;	/* saved when entering DDB */
#endif
};

typedef struct mach_clock	*mach_clock_t;
typedef struct mach_clock	mach_clock_data_t;

#define MACH_CLOCK_NULL		((mach_clock_t)0)

typedef	mach_port_t		*mach_clock_array_t;

#define clock_queue_head(clock)		(&(clock)->head)
#define clock_queue_lock(clock)		simple_lock(&(clock)->queue_lock)
#define clock_queue_unlock(clock)	simple_unlock(&(clock)->queue_lock)

/*
 *	Add a clock to the system.  The clock structure
 *	must be fully set up, except for the timer element
 *	queue.
 */
extern kern_return_t clock_add(mach_clock_t);

/*
 *	Attach the "time-of-day" clock.
 */
extern void tod_clock_attach(
		timespec_t	cur_time,
		kern_return_t	(*set_time)(mach_clock_t, timespec_t *));

/*
 *	Distinguished system clocks:
 */
extern mach_clock_t		real_time_clock;
					/* real-time clock, counts from 0 */
extern mach_clock_t		periodic_clock;
					/* highest-resolution clock that
					   delivers periodic interrupts.
					   Counts from 0.
					   Used as the "system" clock. */
extern mach_clock_t		tod_clock;
					/* (Possibly) low-resolution clock
					   with (possibly) non-volatile
					   storage for time.  Counts
					   from "epoch" start. */

/*
 *	Normal and system clock interrupt service routines.
 */
extern void
clock_interrupt(
	mach_clock_t	clock,
	boolean_t	usermode);

extern void
aperiodic_clock_interrupt(
	mach_clock_t	clock,
	boolean_t	usermode);

extern void
system_clock_interrupt(
	boolean_t	usermode);

/*
 *	Enable system clock interrupts for the current CPU.
 */
extern void
enable_clock_interrupts(
	boolean_t	on);

/*
 *	void clock_read(timespec_t&  result,
 *			mach_clock_t clock)
 *
 *	Read the clock`s time, without locking the clock,
 *	and produce a consistent time reading.
 *
 *	Results are passed by lvalue.
 */
#define	clock_read(result, clock)				\
	do {							\
	    (result).seconds = (clock)->time.seconds;		\
	    (result).nanoseconds = (clock)->time.nanoseconds;	\
	} while ((result).seconds != (clock)->check_seconds)

/*
 *	Set the mapped time from the current clock reading,
 *	obeying the update protocol (set check_seconds first).
 */
#define	clock_set_mtime(clock) \
    MACRO_BEGIN							\
	mapped_timespec_t *mtime = (clock)->mtime;		\
	if (mtime != 0) {					\
	    mtime->check_seconds = (clock)->time.seconds;	\
	    mtime->nanoseconds   = (clock)->time.nanoseconds;	\
	    mtime->seconds	 = (clock)->time.seconds;	\
	}							\
    MACRO_END

/*
 *	Exported routines
 */
extern kern_return_t	clock_get_time(
		mach_clock_t	clock,
		timespec_t	*ts);
extern kern_return_t	clock_set_time(
		mach_clock_t	clock,
		timespec_t	*ts);
extern kern_return_t	clock_get_resolution(
		mach_clock_t	clock,
		natural_t	*res,
		natural_t	*skew);
extern kern_return_t	clock_get_best_resolution(
		mach_clock_t	clock,
		natural_t	*res,
		natural_t	*skew);
extern kern_return_t	clock_set_resolution(
		mach_clock_t	clock,
		natural_t	*res,
		natural_t	*skew);
extern kern_return_t	clock_map(
		mach_clock_t	clock,
		ipc_port_t	*pager);
extern kern_return_t	clock_name(
		mach_clock_t	clock,
		mach_clock_name_t name);

extern kern_return_t	host_get_clock(
		host_t		host,
		mach_clock_t	*clock);
extern kern_return_t	host_get_update_clock(
		host_t		host,
		mach_clock_t	*clock);
extern kern_return_t	host_get_named_clock(
		host_t		host,
		mach_clock_name_t name,
		mach_clock_t	*clock);
extern kern_return_t	host_get_clock_control(
		host_t		host_priv,
		mach_clock_t	clock,
		mach_clock_t	*clock_ctrl);
extern kern_return_t	host_clocks(
		host_t		host,
		mach_clock_array_t *out_clock_list,
		natural_t	*count);


/*
 *	Internal routines.
 */
extern void	mach_clock_init(void);
extern void	ipc_clock_enable(mach_clock_t);
extern mach_clock_t	convert_port_to_clock(ipc_port_t);
extern mach_clock_t	convert_port_to_clock_control(ipc_port_t);
extern ipc_port_t	convert_clock_to_port(mach_clock_t);
extern ipc_port_t	convert_clock_control_to_port(mach_clock_t);

#endif	/* _KERN_MACH_CLOCK_H_ */
