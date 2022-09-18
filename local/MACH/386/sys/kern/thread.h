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
 * $Log:	thread.h,v $
 * Revision 2.13  89/06/27  00:25:21  rpd
 * 	Added thread_tself.
 * 	[89/06/26  23:59:50  rpd]
 * 
 * Revision 2.12  89/05/01  17:02:19  rpd
 * 	Moved reply_port here from the task structure.
 * 	[89/05/01  14:07:31  rpd]
 * 
 * Revision 2.11  89/03/09  20:16:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.10  89/02/25  18:09:55  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.9  89/02/07  01:05:09  mwyoung
 * Relocated from sys/thread.h
 * 
 * Revision 2.8  89/01/15  16:35:23  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:19:31  rpd]
 * 
 * Revision 2.7  88/11/14  15:04:51  gm0w
 * 	Change usage and delta fields to unsigned so priority
 * 	computation works right.
 * 	[88/11/02            dlb]
 * 
 * Revision 2.6  88/10/11  10:26:00  rpd
 * 	Added ipc_data to the thread structure.
 * 	[88/10/10  08:00:16  rpd]
 * 	
 * 	Removed unnecessary include of kern/kern_msg.h.
 * 	[88/10/04  06:56:27  rpd]
 * 
 * Revision 2.5  88/08/24  02:47:53  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:24:57  mwyoung]
 * 
 * Revision 2.4  88/08/06  19:22:05  rpd
 * Declare external variables as "extern".
 * Added macros ipc_thread_lock(), ipc_thread_unlock().
 * 
 * Revision 2.3  88/07/17  18:55:10  mwyoung
 * Reorganized.  Added thread_t->vm_privilege.
 * 
 * Added current_task() declaration.
 *
 * 21-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Reorganized.  Added thread_t->vm_privilege.
 *
 *  4-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Remove vax-specific field (pcb physical address).
 *
 * 19-Apr-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added current_task() declaration.
 *
 *  7-Apr-88  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TIME_NEW is now standard.
 *
 *  4-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Added usage_save and preempt_pri fields.
 *
 * 19-Feb-88  David Black (dlb) at Carnegie-Mellon University
 *	Deleted unused ticks field.  Rearranged and added MACH_TIME_NEW
 *	fields for scheduler interface.  user_ticks and system_ticks are
 *	not needed under MACH_TIME_NEW.  Change wait_time to sched_stamp.
 *
 * 21-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Replaced swappable boolean with swap_state field.  Swap states
 *	are defined in kern/thread_swap.h.
 *
 * 17-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added declarations of new routines.
 */
/*
 *	File:	thread.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	This file contains the structure definitions for threads.
 *
 */

#ifndef	_KERN_THREAD_H_
#define _KERN_THREAD_H_

#include <mach/port.h>
#include <mach/message.h>
#include <mach/boolean.h>
#include <mach/machine/vm_types.h>
#include <kern/queue.h>
#include <kern/task.h>
#include <kern/timer.h>
#include <kern/lock.h>
#include <kern/sched.h>
#include <kern/thread_modes.h>
#include <kern/kern_msg.h>
#include <machine/cpu.h>
#include <machine/thread.h>
#include <machine/pcb.h>

struct thread {
	/* Run queues */
	queue_chain_t	links;		/* current run queue links */
	run_queue_t	runq;		/* run queue p is on SEE BELOW */
	run_queue_t	whichq;		/* which queue p must be on */
/*
 *	NOTE:	The runq field in the thread structure has an unusual
 *	locking protocol.  If its value is RUN_QUEUE_NULL, then it is
 *	locked by the thread_lock, but if its value is something else
 *	(i.e. a run_queue) then it is locked by that run_queue's lock.
 */

	/* Task information */
	task_t		task;		/* Task to which I belong */
	queue_chain_t	thread_list;	/* list of threads in task */

	/* Thread bookkeeping */
	queue_chain_t	all_threads;	/* list of all threads */


	/* Self-preservation */
	decl_simple_lock_data(,lock)
	int		ref_count;	/* number of references to me */

	/* Hardware state */
	struct pcb	*pcb;		/* hardware pcb & machine state */
	vm_offset_t	kernel_stack;	/* Where kernel stack was allocated */

	/* Blocking information */
	int		wait_event;	/* event we are waiting on */
	int		suspend_count;	/* internal use only */
	boolean_t	interruptible;	/* interruptible wait? */
	kern_return_t	wait_result;	/* outcome of wait */
	boolean_t	timer_set;	/* timeout set on wait */
	boolean_t	wake_active;
	int		swap_state;	/* swap state (or unswappable flag) */
	int		state;		/* Thread state: */
/*
 *	Thread states [bits or'ed]
 */
#define TH_WAIT			0x01	/* thread is queued for waiting */
#define TH_SUSP			0x02	/* thread has been asked to stop */
#define TH_RUN			0x04	/* thread is running or on runq */
#define TH_SWAPPED		0x08	/* thread is swapped out */
#define TH_IDLE			0x10	/* thread is an idle thread */

	/* Scheduling information */
	int		priority;	/* thread's priority */
	int		sched_pri;	/* scheduled (computed) priority */
	int		preempt_pri;	/* if quantum has not expired, use */
					/*  this priority for preemption */
	int		quantum;	/* quantum left in ticks */
	unsigned int	cpu_usage;	/* exp. decaying cpu usage [%cpu] */
	unsigned int	sched_usage;	/* load-weighted cpu usage [sched] */
	unsigned int	sched_stamp;	/* last time priority was updated */
	int		exit_code;	/* How to exit the kernel: */
/*
 *	Exit code [enumerated type]
 */
#define THREAD_EXIT		0	/* exit kernel normally */
#define THREAD_TERMINATE	1	/* terminate on exit from kernel */
#define THREAD_HALT		2	/* halt on exit from kernel */
#define THREAD_HALTED		3	/* confirmation - thread has halted */

	/* VM information */

	vm_offset_t	recover;	/* page fault recovery (copyin/out) */
	boolean_t	vm_privilege;	/* Can use reserved memory? */

	/* Compatibility garbage */
	struct u_address {
		struct uthread	*uthread;
		struct utask	*utask;
	} u_address;
	int		unix_lock;	/* bind to unix_master */

	/* User-visible scheduling state */
	int		user_suspend_count;	/* outstanding suspends */
	int		user_stop_count;	/* outstanding stops */

	/* IPC data structures */
	decl_simple_lock_data(,ipc_state_lock) /* Locks most IPC fields */
	port_t		thread_self;	/* Port representing this thread */
	port_t		thread_tself;	/* What task thinks is thread_self */
	port_t		thread_reply;	/* Initial reply port for RPCs */
	queue_chain_t	ipc_wait_queue;	/* Chain for IPC sleep queues */
	msg_return_t	ipc_state;	/* Operation state after awakening */
	union {
	msg_size_t	msize;		/* Maximum size of msg to receive */
	kern_msg_t	kmsg;		/* Message that was received */
	} ipc_data;
	/* no locking on ipc_kernel & reply_port: used by the thread itself */
	boolean_t	ipc_kernel;	/* ipc buffer in kernel space */
	port_name_t	reply_port;	/* See kern/mig_support.c. */

	/* Timing data structures */
	timer_data_t	user_timer;	/* user mode timer */
	timer_data_t	system_timer;	/* system mode timer */
	timer_save_data_t user_timer_save;  /* saved user timer value */
	timer_save_data_t system_timer_save;  /* saved sys timer val. */
	unsigned int	cpu_delta;	/* cpu usage since last update */
	unsigned int	sched_delta;	/* weighted cpu usage since update */

	/* Exception data structures */
	port_t		exception_port;
	port_t		exception_clear_port;
};

typedef struct thread *thread_t;

#define THREAD_NULL	((thread_t) 0)

typedef	port_t	*thread_array_t;	/* XXX compensate for MiG */


extern queue_head_t all_threads;	/* list of all threads in system */
decl_simple_lock_data(extern,all_threads_lock)

extern thread_t active_threads[];	/* active threads */

/*
 *	User routines
 */

extern kern_return_t	thread_create();
extern kern_return_t	thread_terminate();
extern kern_return_t	thread_suspend();
extern kern_return_t	thread_resume();
extern kern_return_t	thread_abort();
extern kern_return_t	thread_get_state();
extern kern_return_t	thread_set_state();
extern kern_return_t	thread_get_special_port();
extern kern_return_t	thread_set_special_port();
extern kern_return_t	thread_info();

/*
 *	Kernel-only routines
 */

extern void		thread_init();
extern void		thread_reference();
extern void		thread_deallocate();
extern void		thread_hold();
extern void		thread_dowait();
extern void		thread_release();
extern void		thread_swappable();
extern void		thread_halt();
extern void		thread_halt_self();
extern thread_t		kernel_thread();

extern void		reaper_thread();

/*
 *	Macro-defined routines
 */

#define thread_pcb(th)		((th)->pcb)

#define thread_lock(th)		simple_lock(&(th)->lock)
#define thread_unlock(th)	simple_unlock(&(th)->lock)

#define thread_should_halt()	(current_thread()->exit_code != THREAD_EXIT)

#define ipc_thread_lock(th)	simple_lock(&(th)->ipc_state_lock)
#define ipc_thread_unlock(th)	simple_unlock(&(th)->ipc_state_lock)

/*
 *	Machine specific implementations of the current thread macro
 *	designate this by defining CURRENT_THREAD.
 */
#ifndef	CURRENT_THREAD
#define current_thread()	(active_threads[cpu_number()])
#endif	CURRENT_THREAD

#define current_task()		((current_thread())->task)

#endif	_KERN_THREAD_H_
