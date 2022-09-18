/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sched_prim_macros.h,v $
 * Revision 2.8  89/03/09  20:15:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  18:08:21  gm0w
 * 	Kernel code cleanup.
 * 	Put entire file under #indef KERNEL.
 * 	[89/02/15            mrt]
 * 
 * Revision 2.6  89/02/07  01:04:24  mwyoung
 * Relocated from sys/sched_prim_macros.h
 * 
 * Revision 2.5  88/12/19  02:42:34  mwyoung
 * 	Remove lint.
 * 	[88/12/08            mwyoung]
 * 
 * Revision 2.4  88/08/24  02:43:13  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:22:20  mwyoung]
 * 
 * Revision 2.3  88/07/20  21:07:20  rpd
 * Include sys/types.h for caddr_t.
 * 
 * 24-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Added argument to thread_setrun().
 *
 * 30-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 13-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Created.  Moved thread_will_wait and thread_go here from
 *	sched_prim.h.
 */
/*
 *	File:	sched_prim_macros.h
 *	Author:	David Golub
 *
 *	Scheduling primitive macros file
 *
 */

#ifndef	_KERN_SCHED_PRIM_MACROS_H_
#define _KERN_SCHED_PRIM_MACROS_H_

#include <sys/types.h>
#include <mach/boolean.h>
#include <kern/sched.h>
#include <kern/sched_prim.h>
#include <kern/thread.h>
#include <kern/thread_swap.h>
#include <kern/macro_help.h>
#include <machine/machparam.h>	/* for splsched */

extern int	thread_timeout();

/*
 *	Make a thread wait interruptibly.
 */
#define thread_will_wait(thread) 			\
MACRO_BEGIN						\
	register int s;					\
	s = splsched();					\
	thread_lock(thread);				\
	(thread)->state |= TH_WAIT;			\
	thread_unlock(thread);				\
	splx(s);					\
MACRO_END

/*
 *	Make a thread wait interruptibly, with a
 *	timeout.
 */
#define thread_will_wait_with_timeout(thread, t)		\
MACRO_BEGIN							\
	register int s;						\
	s = splsched();						\
	thread_lock(thread);					\
	(thread)->state |= TH_WAIT;				\
	(thread)->timer_set = TRUE;				\
	timeout(thread_timeout, (caddr_t)(thread), (int)(t));	\
	thread_unlock(thread);					\
	splx(s);						\
MACRO_END

/*
 *	Wakeup a thread, and queue it to run normally.
 */
#define thread_go(thread)  					\
MACRO_BEGIN							\
	register int s, state; 					\
	s = splsched();						\
	thread_lock(thread); 					\
	if ((thread)->timer_set) {				\
		(thread)->timer_set = FALSE;			\
		untimeout(thread_timeout, (caddr_t) (thread));	\
	}							\
	state = (thread)->state;				\
	switch (state) {					\
	    case TH_WAIT | TH_SUSP:				\
		/*						\
		 *	Suspend thread if interruptible		\
		 */						\
		if ((thread)->interruptible) {			\
		    (thread)->state = TH_SUSP;			\
		    (thread)->wait_result = THREAD_AWAKENED;	\
		    break;					\
		}						\
		/* fall through */				\
	    case TH_WAIT:					\
		/*						\
		 *	Sleeping and not suspendable - put	\
		 *	on run queue.				\
		 */						\
		(thread)->state = (state & ~TH_WAIT) | TH_RUN;	\
		(thread)->wait_result = THREAD_AWAKENED;	\
		thread_setrun(thread, TRUE);				\
		break;						\
								\
	    case TH_WAIT | TH_SWAPPED:				\
		/*						\
		 *	Thread is swapped out, but runnable	\
		 */						\
		(thread)->state = TH_RUN | TH_SWAPPED;		\
		(thread)->wait_result = THREAD_AWAKENED;	\
		thread_swapin(thread);				\
		break;						\
								\
	    default:						\
		/*						\
		 *	Either already running, or suspended.	\
		 */						\
		if (state & TH_WAIT) {				\
		    (thread)->state = state & ~TH_WAIT;		\
		    (thread)->wait_result = THREAD_AWAKENED;	\
		    break;					\
		}						\
	}							\
	thread_unlock(thread); 					\
	splx(s); 						\
MACRO_END


/*
 *	Wakeup a thread.  Block, transferring control to
 *	it immediately, if it can run (and will run on the
 *	same CPU).
 */
#define thread_go_and_switch(thread) 				\
MACRO_BEGIN							\
	register int s, state; 					\
	s = splsched();						\
	thread_lock(thread); 					\
	if ((thread)->timer_set) {				\
		(thread)->timer_set = FALSE;			\
		untimeout(thread_timeout, (caddr_t) (thread));	\
	}							\
	state = (thread)->state;				\
	switch (state) {					\
	    case TH_WAIT | TH_SUSP:				\
		/*						\
		 *	Suspend thread if interruptible		\
		 */						\
		if ((thread)->interruptible) {			\
		    (thread)->state = TH_SUSP;			\
		    (thread)->wait_result = THREAD_AWAKENED;	\
		    break;					\
		}						\
		/* fall through */				\
	    case TH_WAIT:					\
		/*						\
		 *	Sleeping and not suspendable - put	\
		 *	on run queue.				\
		 */						\
		(thread)->state = (state & ~TH_WAIT) | TH_RUN;	\
		(thread)->wait_result = THREAD_AWAKENED;	\
		if (idle_count > 0) {				\
		    /*						\
		     *	Other cpus could run thread.		\
		     *	Put it on the run queues.		\
		     */						\
		    thread_setrun(thread, TRUE);		\
		    break;					\
		}						\
		else {						\
		    /*						\
		     *	Switch immediately to new thread.	\
		     */						\
		    thread_unlock(thread);			\
		    thread_switch(thread);			\
		    goto done;					\
		}						\
								\
	    case TH_WAIT | TH_SWAPPED:				\
		/*						\
		 *	Thread is swapped out, but runnable	\
		 */						\
		(thread)->state = TH_RUN | TH_SWAPPED;		\
		(thread)->wait_result = THREAD_AWAKENED;	\
		thread_swapin(thread);				\
		break;						\
								\
	    default:						\
		/*						\
		 *	Either already running, or suspended.	\
		 */						\
		if (state & TH_WAIT) {				\
		    (thread)->state = state & ~TH_WAIT;		\
		    (thread)->wait_result = THREAD_AWAKENED;	\
		    break;					\
		}						\
	}							\
	thread_unlock(thread); 					\
    done:							\
	splx(s); 						\
MACRO_END

#endif	_KERN_SCHED_PRIM_MACROS_H_
