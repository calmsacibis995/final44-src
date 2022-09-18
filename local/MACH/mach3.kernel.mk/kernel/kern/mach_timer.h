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
 * $Log:	mach_timer.h,v $
 * Revision 2.3  94/12/16  10:45:36  dbg
 * 	Exported routines now begin with 'mach_timer_'.  Renamed
 * 	'time_spec' to 'timespec'.
 * 	[94/05/23            dbg]
 * 
 * Revision 2.2  93/11/17  17:16:14  dbg
 * 	Changed timer_arm_internal to timer_sleep_periodic.
 * 	Added BUSY bit to show that timer is either enqueued
 * 	or in timeout routine.
 * 	[93/07/15            dbg]
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
 * 	Added tm_overruns.
 * 	[93/05/06            dbg]
 * 
 * 	Moved kernel time_out element definitions to this file.
 * 	[93/04/09            dbg]
 * 
 * 	Fixed to put in kernel.  Based on kernel timer elements.
 * 
 * 	Changed time_values_t to timespec_t to account for timer hardware skew.
 * 	[92/07/18	savage]
 * 	Redefined timer structure for user exportation.  Forced to define
 * 	it as mach_timer_t instead of timer_t...  I'd love to change timer_t
 * 	into counter_t but I'm sure the political headache isn't worth it.
 * 	[92/06/12	savage]
 * 	changed locks to work on multiprocessor (one hopes...)
 * 	[92/06/10]	savage]
 * 	Created
 * 	[92/05/01	savage]
 * 
 */

#ifndef	_KERN_MACH_TIMER_H_
#define _KERN_MACH_TIMER_H_

#include <mach/boolean.h>
#include <mach/message.h>
#include <mach/timespec.h>
#include <mach/mach_timer.h>

#include <kern/eventcount.h>
#include <kern/lock.h>
#include <kern/macro_help.h>
#include <kern/queue.h>
#include <kern/kern_types.h>

/*
 *	A timer element is queued on a clock.
 */
struct mach_clock;			/* opaque imported type */

/*
 *	Common structure for head of timer element list and
 *	head of queue.  Allows use of a sentinel at the end
 *	of the list.
 */
struct timer_elt_head {
	queue_chain_t	chain;		/* chain in order of expiration */
	timespec_t	expire_time;	/* expiration time */
};

/*
 *	The internal timer element structure.
 */
struct timer_elt {
	struct timer_elt_head
			te_head;	/* chain/expire time */
	void		(*te_fcn)(void *);
					/* function to call */
	void *		te_param;	/* with this parameter */
	unsigned int	te_flags;	/* unset | set | allocated | periodic*/
	struct mach_clock *
			te_clock;	/* clock that keeps time for
					   this timer */
	timespec_t	te_period;	/* period */
};
#define	te_chain	te_head.chain
#define	te_expire_time	te_head.expire_time

#define	TELT_UNSET	0		/* timer not set */
#define	TELT_SET	0x01		/* timer set */
#define	TELT_ALLOC	0x02		/* timer allocated from pool */
#define	TELT_PERIODIC	0x10		/* periodic timer */
#define	TELT_ABSOLUTE	0x20		/* expiration time is absolute */

typedef	struct timer_elt	timer_elt_data_t;
typedef	struct timer_elt	*timer_elt_t;

/*
 *	Add a timer element to its clock queue.
 *	if absolute, time is absolute expiration time;
 *	otherwise, time is interval from clock time.
 *	Returns FALSE if expiration time is in the past.
 */
extern boolean_t timer_elt_enqueue(
	timer_elt_t	elt,
	timespec_t	time,
	boolean_t	absolute);

/*
 *	Remove a timer element from its clock queue.
 *	Return TRUE if the timer element was on the queue.
 */
extern boolean_t timer_elt_dequeue(
	timer_elt_t	telt);

/*
 *	Fast version of timer_elt_dequeue.
 */
#define	timer_elt_remove(telt) \
    MACRO_BEGIN \
	if (((telt)->te_flags & TELT_SET) != 0) { \
	    (void) timer_elt_dequeue(telt); \
	} \
    MACRO_END

/*
 * Convert milliseconds to seconds/nanoseconds.
 */
#define	milliseconds_to_timespec(milli, interval)		\
MACRO_BEGIN							\
	(interval).seconds = (milli) / 1000;			\
	(interval).nanoseconds = ((milli) % 1000) * 1000000;	\
MACRO_END

/*
 * Timeout functions are called at AST time.
 */

extern void timer_ast(void);



/*
 *	The mach_timer structure is an exported form
 *	of a timer element.
 */
struct mach_timer {
	struct timer_elt te;		/* chain,
					   expire_time,
					   function/param,
					   set/unset,
					   period */
	struct ipc_port	*tm_self;	/* kernel port for timer */
	decl_simple_lock_data(,tm_ref_lock)	/* lock for ref count*/
	int		tm_ref_count;	/* number of references to me */
	decl_simple_lock_data(,tm_lock)	/* lock for everything else */
	int		tm_misc;	/* flags: */
#define	TM_ACTIVE		0x01		/* timer alive */
#define	TM_EVENT_ALLOC		0x02		/* event counter allocated */
#define	TM_BUSY			0x04		/* timer enqueued or
						   timeout routine running */
#define	TM_SUSPEND		0x08		/* suspend thread at
						   expiration */
	struct ipc_port	*tm_expire;	/* timer expiration send right */
	struct evc	tm_event;	/* event! blame sandro not me :-) */
	thread_t	tm_thread;	/* thread to be suspended or awoken */
	int		tm_overruns;	/* number of times a periodic timer
					   could not send message */
};

#define	tm_chain	te.te_chain
#define	tm_expire_time	te.te_expire_time
#define	tm_fcn		te.te_fcn
#define	tm_param	te.te_param
#define	tm_flags	te.te_flags
#define	tm_clock	te.te_clock
#define	tm_period	te.te_period

typedef struct mach_timer	*mach_timer_t;
typedef struct mach_timer	mach_timer_data_t;

#define TIMER_NULL	((mach_timer_t) 0)

/* 
 *	For zalloc()
 */
#define TIMER_MAX		1024
#define TIMER_CHUNK		64

/*
 *	Macros to lock and unlock timer
 */
#define timer_lock(tm)		simple_lock(&(tm)->tm_lock)
#define timer_unlock(tm)	simple_unlock(&(tm)->tm_lock)

#define timer_ref_lock(tm)	simple_lock(&(tm)->tm_ref_lock)
#define timer_ref_unlock(tm)	simple_unlock(&(tm)->tm_ref_lock)

/*
 *	Internal only routines
 */
extern void		mach_timer_init(void);
extern void		mach_timer_reference(mach_timer_t);
extern void		mach_timer_deallocate(mach_timer_t);
extern boolean_t	mach_timer_thread_reference(mach_timer_t);
extern void		mach_timer_thread_deallocate(mach_timer_t);

extern mach_timer_t	convert_port_to_timer(struct ipc_port *);
extern struct ipc_port *convert_timer_to_port(mach_timer_t);

extern boolean_t	mach_timer_notify(mach_msg_header_t *);

/*
 *	Exported routines
 */
extern kern_return_t mach_timer_arm(
	mach_timer_t	timer,
	timespec_t	expire_time,
	timespec_t	interval_time,
	struct ipc_port	*expire_port,
	thread_t	thread,
	int		flags);

extern kern_return_t mach_timer_cancel(
	mach_timer_t	timer,
	int		flags);

extern kern_return_t mach_timer_create(
	struct mach_clock *clock,
	mach_timer_t	*timer);

extern kern_return_t mach_timer_get_evc(
	mach_timer_t	timer,
	natural_t	*event);

extern kern_return_t mach_timer_info(
	mach_timer_t	timer,
	int		flavor,
	struct mach_clock **clock,		/* out */
	struct ipc_port	**expire_port,		/* out */
	thread_t	*thread,		/* out */
	mach_timer_info_t timer_info_out,	/* out */
	natural_t	*timer_info_count);	/* inout */

extern kern_return_t mach_timer_sleep(
	mach_timer_t	timer,
	timespec_t	expire_time,
	int		flags,
	timespec_t	*wakeup_time);

extern kern_return_t mach_timer_terminate(
	mach_timer_t	timer);

/*
 *	Internal-only routines (mostly for periodic threads)
 */
extern kern_return_t mach_timer_sleep_periodic(
	mach_timer_t	timer,
	timespec_t	expire_time,
	timespec_t	interval_time,
	thread_t	thread,
	int		flags);

extern void mach_timer_wait(
	mach_timer_t	timer,
	thread_t	thread);

extern kern_return_t mach_timer_rearm(
	mach_timer_t	timer,
	timespec_t	new_expire_time,
	timespec_t	new_interval,
	int		flags);

extern boolean_t mach_timer_start_time(
	mach_timer_t	timer,
	timespec_t	*start_time);	/* OUT */

#endif	/*_KERN_MACH_TIMER_H_ */

