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
 * $Log:	thread.c,v $
 * Revision 2.12  89/06/27  00:25:04  rpd
 * 	Added support for THREAD_KERNEL_PORT.
 * 	[89/06/26  23:57:10  rpd]
 * 
 * Revision 2.11  89/05/06  02:57:22  rpd
 * 	Purged <kern/thread_statistics.h>.
 * 	[89/05/05  20:42:35  rpd]
 * 
 * Revision 2.10  89/04/18  16:43:10  mwyoung
 * 	Add a template for thread initialization.  Many fields were
 * 	previously not initialized at all.
 * 
 * 	Handle resource shortage in thread_create().
 * 	[89/02/15            mwyoung]
 * 
 * Revision 2.6.2.1  89/03/15  01:02:40  mwyoung
 * 	Add a template for thread initialization.  Many fields were
 * 	previously not initialized at all.
 * 
 * 	Handle resource shortage in thread_create().
 * 	[89/02/15            mwyoung]
 * 
 * Revision 2.9  89/03/09  20:16:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/25  18:09:44  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.7  89/01/15  16:27:51  rpd
 * 	Use decl_simple_lock_data, simple_lock_addr.
 * 	[89/01/15  15:08:25  rpd]
 * 
 * Revision 2.6  88/12/19  02:48:03  mwyoung
 * 	Fix include file references.
 * 	[88/12/19  00:24:52  mwyoung]
 * 	
 * 	Remove lint.
 * 	[88/12/09            mwyoung]
 * 
 * Revision 2.5  88/10/27  10:49:43  rpd
 * 	Some cleanup, mainly in the reaper.
 * 	[88/10/26  14:46:35  rpd]
 * 
 * Revision 2.4  88/08/25  18:19:10  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Removed obsolete routines.
 * 	[88/08/11  18:48:39  mwyoung]
 * 
 * Revision 2.3  88/08/06  18:26:41  rpd
 * Changed to use ipc_thread_lock/ipc_thread_unlock macros.
 * Eliminated use of kern/mach_ipc_defs.h.
 * Added definitions of all_threads, all_threads_lock.
 * 
 *  4-May-88  David Golub (dbg) and David Black (dlb) at CMU
 *	Remove vax-specific code.  Add register declarations.
 *	MACH_TIME_NEW now standard.  Moved thread_read_times to timer.c.
 *	SIMPLE_CLOCK: clock drift compensation in cpu_usage calculation.
 *	Initialize new fields in thread_create().  Implemented cpu usage
 *	calculation in thread_info().  Added argument to thread_setrun.
 *	Initialization changes for MACH_TIME_NEW.
 *
 * 13-Apr-88  David Black (dlb) at Carnegie-Mellon University
 *	Rewrite kernel stack retry code to eliminate races and handle
 *	termination correctly.
 *
 * 19-Feb-88  David Kirschen (kirschen) at Encore Computer Corporation
 *      Retry if kernel stacks exhausted on thread_create
 *
 * 12-Feb-88  David Black (dlb) at Carnegie-Mellon University
 *	Fix MACH_TIME_NEW code.
 *
 *  1-Feb-88  David Golub (dbg) at Carnegie-Mellon University
 *	In thread_halt: mark the victim thread suspended/runnable so that it
 *	will notify the caller when it hits the next interruptible wait.
 *	The victim may not immediately proceed to a clean point once it
 *	is awakened.
 *
 * 21-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Use new swapping state machine.  Moved thread_swappable to
 *	thread_swap.c.
 *
 * 17-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Added new thread interfaces: thread_suspend, thread_resume,
 *	thread_get_state, thread_set_state, thread_abort,
 *	thread_info.  Old interfaces remain (temporarily) for binary
 *	compatibility, prefixed with 'xxx_'.
 *
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 15-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Made thread_reference and thread_deallocate check for null
 *	threads.  Call pcb_terminate when a thread is deallocated.
 *	Call pcb_init with thread pointer instead of pcb pointer.
 *	Add missing case to thread_dowait.
 *
 *  9-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Rewrote thread termination to have a terminating thread clean up
 *	after itself.
 *
 *  9-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Moved reaper invocation to thread_terminate from
 *	thread_deallocate.  [XXX temporary pending rewrite.]
 *
 *  8-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Added call to ipc_thread_disable.
 *
 *  4-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Set ipc_kernel in kernel_thread().
 *
 *  3-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Rewrote thread_create().  thread_terminate() must throw away
 *	an extra reference if called on the current thread [ref is
 *	held by caller who will not be returned to.]  Locking bug fix
 *	to thread_status.
 *
 * 19-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Eliminated TT conditionals.
 *
 * 30-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Fix race condition in thread_deallocate for thread terminating
 *	itself.
 *
 * 23-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Correctly set thread_statistics fields.
 *
 * 13-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	Use counts for suspend and resume primitives.
 *
 *  5-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH_TT: Completely replaced scheduling state machine.
 *
 * 30-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added initialization of thread->flags in thread_create().
 *	Added thread_swappable().
 *	De-linted.
 *
 * 30-Sep-87  David Black (dlb) at Carnegie-Mellon University
 *	Rewrote thread_dowait to more effectively stop threads.
 *
 * 11-Sep-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Initialize thread fields and unix_lock.
 *
 *  9-Sep-87  David Black (dlb) at Carnegie-Mellon University
 *	Changed thread_dowait to count a thread as stopped if it is
 *	sleeping and will stop immediately when woken up.  [i.e. is
 *	sleeping interruptibly].  Corresponding change to
 *	thread_terminate().
 *
 *  4-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Moved ipc_thread_terminate to thread_terminate (from
 *	thread_deallocate), to shut out other threads that are
 *	manipulating the thread via its thread_port.
 *
 * 29-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	Make sure all deallocation calls are outside of locks - they may
 *	block.  Moved task_deallocate from thread_deallocate to
 *	thread_destroy, since thread may blow up if task disappears while
 *	thread is running.
 *
 * 26-Jun-87  David Black (dlb) at Carnegie-Mellon University
 *	Added update_priority() call to thread_release() for any thread
 *	actually released.
 *
 * 23-Jun-87  David Black (dlb) at Carnegie-Mellon University
 *	Initialize thread priorities in thread_create() and kernel_thread().
 *
 * 10-Jun-87  Karl Hauth (hauth) at Carnegie-Mellon University
 *	Added code to fill in the thread_statistics structure.
 *
 *  1-Jun-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added thread_statistics stub.
 *
 * 21-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Clear the thread u-area upon creation of a thread to keep
 *	consistent.
 *
 *  4-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Call uarea_init to initialize u-area stuff.
 *
 * 29-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Moved call to ipc_thread_terminate into the MACH_TT only branch
 *	to prevent problems with non-TT systems.
 *
 * 28-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support the thread status information as a MiG refarray.
 *	[NOTE: turned off since MiG is still too braindamaged.]
 *
 * 23-Apr-87  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Moved ipc_thread_terminate to thread_deallocate from
 *	thread_destroy to eliminate having the reaper call it after
 *	the task has been freed.
 *
 * 18-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added reaper thread for deallocating threads that cannot
 *	deallocate themselves (some time ago).
 *
 * 17-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	De-linted.
 *
 * 14-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Panic if no space left in the kernel map for stacks.
 *
 *  6-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Add kernel_thread routine which starts up kernel threads.
 *
 *  4-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make thread_terminate work.
 *
 *  2-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	New kernel stack allocation mechanism.
 *
 * 27-Feb-87  David L. Black (dlb) at Carnegie-Mellon University
 *	MACH_TIME_NEW: Added timer inits to thread_create().
 *
 * 24-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Rewrote thread_suspend/thread_hold and added thread_wait for new
 *	user synchronization paradigm.
 *
 * 24-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Reorded locking protocol in thread_deallocate for the
 *	all_threads_lock (this allows one to reference a thread then
 *	release the all_threads_lock when scanning the thread list).
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged in my changes for real thread implementation.
 *
 * 30-Sep-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make floating u-area work, maintain list of threads per task.
 *
 *  1-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added initialization for Mach-style IPC.
 *
 *  7-Jul-86  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Added thread_in_use_chain to keep track of threads which
 *	have been created but not yet destroyed.
 *
 * 31-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Initialize thread state field to THREAD_WAITING.  Some general
 *	cleanup.
 *
 */
/*
 *	File:	kern/thread.c
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young, David Golub
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr., Michael Wayne Young
 *					David Golub
 *
 *	Thread management primitives implementation.
 */

#include <cpus.h>
#include <simple_clock.h>

#include <kern/mach_param.h>
#include <kern/queue.h>
#include <kern/sched.h>
#include <kern/thread.h>
#include <mach/thread_status.h>
#include <mach/thread_info.h>
#include <mach/thread_special_ports.h>
#include <mach/time_value.h>
#include <kern/zalloc.h>
#include <mach/vm_param.h>
#include <vm/vm_kern.h>
#include <kern/parallel.h>
#include <kern/ipc_tt.h>
#include <kern/sched_prim.h>
#include <kern/thread_swap.h>
#include <machine/machparam.h>		/* for splsched */

queue_head_t all_threads;	/* list of all threads in system */
decl_simple_lock_data(,all_threads_lock)

thread_t active_threads[NCPUS];
struct zone *thread_zone, *u_zone;

queue_head_t		stack_queue;
int			stack_free_count = 0;
int			stack_free_target = 5;
decl_simple_lock_data(,	stack_queue_lock)

queue_head_t		reaper_queue;
decl_simple_lock_data(,	reaper_lock)

boolean_t		need_stack_wakeup = FALSE;

vm_offset_t stack_alloc()
{
	register vm_offset_t	stack;
	register boolean_t	msg_printed = FALSE;
	register kern_return_t	result = THREAD_AWAKENED;

	do {
	    simple_lock(&stack_queue_lock);
	    if (stack_free_count != 0) {
		stack = (vm_offset_t) dequeue_head(&stack_queue);
		stack_free_count--;
	    } else {
		stack = (vm_offset_t)0;
	    }
	    simple_unlock(&stack_queue_lock);

	    /*
	     *	If no stacks on queue, kmem_alloc one.  If that fails,
	     *	pause and wait for a stack to be freed.
	     */
	    if (stack == (vm_offset_t)0)
		stack = kmem_alloc(kernel_map, KERNEL_STACK_SIZE);

	    if (stack == (vm_offset_t)0) {
		if (!msg_printed ) {
		    msg_printed = TRUE;
		    uprintf("MACH: Out of kernel stacks, pausing...");
		    if (!need_stack_wakeup)
			printf("stack_alloc: Kernel stacks exhausted\n");
		}
		else if (result != THREAD_AWAKENED) {
		    /*
		     *	Somebody wants us; return a bogus stack.
		     */
		    return((vm_offset_t)0);
		}

		/*
		 *	Now wait for stack, but first make sure one
		 *	hasn't appeared in the interim.
		 */
		simple_lock(&stack_queue_lock);
		if(stack_free_count != 0) {
		    simple_unlock(&stack_queue_lock);
		    result = THREAD_AWAKENED;
		    continue;
		}
		assert_wait((int)&stack_queue, FALSE);
		need_stack_wakeup = TRUE;
		simple_unlock(&stack_queue_lock);
		thread_block();
		result = current_thread()->wait_result;
	    } else {
		if (msg_printed)
		    uprintf("continuing\n");		  /* got a stack now */
		}
	} while (stack == (vm_offset_t)0);

	return(stack);
}

void stack_free(stack)
	vm_offset_t	stack;
{
	simple_lock(&stack_queue_lock);
	if (stack_free_count < stack_free_target) {
		stack_free_count++;
		enqueue_head(&stack_queue, (queue_entry_t) stack);
		stack = 0;
	}
	simple_unlock(&stack_queue_lock);
	if (stack != 0)
		kmem_free(kernel_map, stack, KERNEL_STACK_SIZE);

	/*
	 * If anyone is waiting for a stack, wake them up.
	 */
	if (need_stack_wakeup) {
		need_stack_wakeup = FALSE;
		thread_wakeup((int)&stack_queue);
	}
}

/* private */
struct thread	thread_template;

void thread_init()
{
	thread_zone = zinit(
			sizeof(struct thread),
			THREAD_MAX * sizeof(struct thread),
			THREAD_CHUNK * sizeof(struct thread),
			FALSE, "threads");

	/*
	 *	Fill in a template thread for fast initialization.
	 *	[Fields that must be (or are typically) reset at
	 *	time of creation are so noted.]
	 */

	/* thread_template.links (none) */
	thread_template.runq = RUN_QUEUE_NULL;
	thread_template.whichq = &global_runq;

	/* thread_template.task (later) */
	/* thread_template.thread_list (later) */
	/* thread_template.all_threads (later) */

	/* thread_template.lock (later) */
	thread_template.ref_count = 1;

	thread_template.pcb = (struct pcb *) 0;		/* (reset) */
	thread_template.kernel_stack = (vm_offset_t) 0;	/* (reset) */

	thread_template.wait_event = 0;
	/* thread_template.suspend_count (later) */
	thread_template.interruptible = TRUE;
	thread_template.wait_result = KERN_SUCCESS;
	thread_template.timer_set = FALSE;
	thread_template.wake_active = FALSE;
	thread_template.swap_state = TH_SW_IN;
	thread_template.state = TH_SUSP;

	thread_template.priority = BASEPRI_USER;
	thread_template.sched_pri = BASEPRI_USER;
	thread_template.preempt_pri = BASEPRI_USER;
	thread_template.quantum = 0;
	thread_template.cpu_usage = 0;
	thread_template.sched_usage = 0;
	thread_template.sched_stamp = sched_tick;
	thread_template.exit_code = THREAD_EXIT;

	thread_template.recover = (vm_offset_t) 0;
	thread_template.vm_privilege = FALSE;

	/* thread_template.u_address (later) */
	thread_template.unix_lock = -1;		/* XXX for Unix */

	thread_template.user_suspend_count = 0;
	thread_template.user_stop_count = 1;

	/* thread_template.<IPC structures> (later) */

	timer_init(&(thread_template.user_timer));
	timer_init(&(thread_template.system_timer));
	thread_template.user_timer_save.low = 0;
	thread_template.user_timer_save.high = 0;
	thread_template.system_timer_save.low = 0;
	thread_template.system_timer_save.high = 0;
	thread_template.cpu_delta = 0;
	thread_template.sched_delta = 0;

	thread_template.exception_port = PORT_NULL;
	thread_template.exception_clear_port = PORT_NULL;

	/*
	 *	Initialize other data structures used in
	 *	this module.
	 */
	
	queue_init(&stack_queue);
	simple_lock_init(&stack_queue_lock);

	queue_init(&reaper_queue);
	simple_lock_init(&reaper_lock);

	queue_init(&all_threads);
	simple_lock_init(&all_threads_lock);
}

kern_return_t thread_create(parent_task, child_thread)
	register task_t	parent_task;
	thread_t	*child_thread;		/* OUT */
{
	register thread_t	new_thread;
	register int		s;

	if (parent_task == TASK_NULL)
		return(KERN_INVALID_ARGUMENT);

	/*
	 *	Allocate a thread and initialize static fields
	 */

	new_thread = (thread_t) zalloc(thread_zone);

	if (new_thread == THREAD_NULL)
		return(KERN_RESOURCE_SHORTAGE);

	*new_thread = thread_template;

	/*
	 *	Initialize runtime-dependent fields
	 */

	new_thread->task = parent_task;
	simple_lock_init(&new_thread->lock);
	new_thread->sched_stamp = sched_tick;

	/*
	 *	Create a kernel stack, and put the PCB at the front.
	 */

	new_thread->kernel_stack = stack_alloc();

	/*
	 *	Only reason for stack_alloc failure is termination of
	 *	current thread.  Send back a return code anyway.
	 */
	if (new_thread->kernel_stack == 0) {
		zfree(thread_zone, (vm_offset_t) new_thread);
		return(KERN_RESOURCE_SHORTAGE);
	}

	new_thread->pcb = (struct pcb *) new_thread->kernel_stack;

	/*
	 *	Set up the u-address pointers.
	 */
	new_thread->u_address.uthread = (struct uthread *)
			(new_thread->kernel_stack + sizeof(struct pcb));
	uarea_zero(new_thread);
	new_thread->u_address.utask = parent_task->u_address;
	uarea_init(new_thread);

	pcb_init(new_thread, new_thread->kernel_stack);

	*child_thread = new_thread;

	ipc_thread_init(new_thread);
	new_thread->ipc_kernel = FALSE;

	s = splsched();
	simple_lock(&all_threads_lock);
	queue_enter(&all_threads, new_thread, thread_t, all_threads);

	task_lock(parent_task);

	parent_task->thread_count++;
	queue_enter(&parent_task->thread_list, new_thread, thread_t,
					thread_list);
	new_thread->suspend_count = parent_task->suspend_count + 1;
					/* account for start state */
	parent_task->ref_count++;
	task_unlock(parent_task);

	simple_unlock(&all_threads_lock);
	(void) splx(s);

	/* XXX parent_task isn't locked here */

	if (!parent_task->active) {
		(void) thread_terminate(new_thread);
		return(KERN_FAILURE);
	}

	ipc_thread_enable(new_thread);

	return(KERN_SUCCESS);
}

void thread_deallocate(thread)
	register thread_t	thread;
{
	int		s;
	register task_t	task;

	time_value_t	user_time, system_time;

	if (thread == THREAD_NULL)
		return;

	/*
	 *	First, check for new count > 0 (the common case).
	 *	Only the thread needs to be locked.
	 */
	s = splsched();
	thread_lock(thread);
	if (--thread->ref_count > 0) {
		thread_unlock(thread);
		(void) splx(s);
		return;
	}

	/*
	 *	Count is zero.  However, the task's thread list and
	 *	the all_threads list have implicit references to
	 *	the thread, and may make new ones.  Their locks also
	 *	dominate the thread lock.  To check for this, we
	 *	temporarily restore the one thread reference, unlock
	 *	the thread, and then lock the other structures in
	 *	the proper order.
	 */
	thread->ref_count = 1;
	thread_unlock(thread);

	task = thread->task;

	simple_lock(&all_threads_lock);
	task_lock(task);
	thread_lock(thread);
	
	if (--thread->ref_count > 0) {
		/*
		 *	Task or all_threads made extra reference.
		 */
		thread_unlock(thread);
		task_unlock(task);
		simple_unlock(&all_threads_lock);
		(void) splx(s);
		return;
	}

	/*
	 *	Thread has no references - we can remove it.
	 */

	/*
	 *	Accumulate times for dead threads in task.
	 */

	thread_read_times(thread, &user_time, &system_time);
	time_value_add(&task->total_user_time, &user_time);
	time_value_add(&task->total_system_time, &system_time);

	/*
	 *	Remove thread from task list and all_threads list.
	 */
	task->thread_count--;
	queue_remove(&task->thread_list, thread, thread_t, thread_list);

	queue_remove(&all_threads, thread, thread_t, all_threads);
	thread->all_threads.prev = (queue_entry_t) 0;
	thread->all_threads.next = (queue_entry_t) 0;

	thread_unlock(thread);		/* no more references - safe */
	task_unlock(task);
	simple_unlock(&all_threads_lock);
	(void) splx(s);

	if (thread == current_thread()) {
	    panic("thread deallocating itself");
	}
	if ((thread->state & ~(TH_RUN | TH_SWAPPED)) != TH_SUSP)
		panic("unstopped thread destroyed!");

	/*
	 *	Deallocate the task reference, since we know the thread
	 *	is not running.
	 */
	task_deallocate(thread->task);			/* may block */

	/*
	 *	Since there are no references left, we need not worry about
	 *	locking the thread.
	 */
	if (thread->state & TH_SWAPPED)
		thread_doswapin(thread);

	/*
	 *	Clean up any machine-dependent resources.
	 */
	pcb_terminate(thread);

	stack_free(thread->kernel_stack);
	zfree(thread_zone, (vm_offset_t) thread);
}
	
void thread_reference(thread)
	register thread_t	thread;
{
	int		s;

	if (thread == THREAD_NULL)
		return;

	s = splsched();
	thread_lock(thread);
	thread->ref_count++;
	thread_unlock(thread);
	(void) splx(s);
}

/*
 *	thread_terminate:
 *
 *	Permanently stop execution of the specified thread.
 *
 *	A thread to be terminated must be allowed to clean up any state
 *	that it has before it exits.  The thread is broken out of any
 *	wait condition that it is in, and signalled to exit.  It then
 *	cleans up its state and calls thread_halt_self on its way out of
 *	the kernel.  The caller waits for the thread to halt, terminates
 *	its IPC state, and then deallocates it.
 *
 *	If the caller is the current thread, it must still exit the kernel
 *	to clean up any state (thread and port references, messages, etc).
 *	When it exits the kernel, it then terminates its IPC state and
 *	queues itself for the reaper thread, which will wait for the thread
 *	to stop and then deallocate it.  (A thread cannot deallocate itself,
 *	since it needs a kernel stack to execute.)
 */
kern_return_t thread_terminate(thread)
	register thread_t	thread;
{
	if (thread == THREAD_NULL)
		return(KERN_INVALID_ARGUMENT);

	/*
	 *	Break IPC control over the thread.
	 */
	ipc_thread_disable(thread);

	if (thread == current_thread()) {
	    /*
	     *	Current thread will queue itself for reaper when
	     *	exiting kernel.
	     */
	    thread->exit_code = THREAD_TERMINATE;
	}
	else {
	    /*
	     *	Halt the thread at a clean point.
	     */
	    thread_halt(thread);

	    /*
	     *	Shut down its IPC after it is clean.
	     */
	    ipc_thread_terminate(thread);

	    /*
	     *	Deallocate its reference to itself.
	     */
	    thread_deallocate(thread);
	}

	return(KERN_SUCCESS);
}

/*
 *	Halt a thread at a clean point, leaving it suspended.
 */
void thread_halt(thread)
	register thread_t	thread;
{
	int	s;

	while (TRUE) {
	  	/*
		 *	Suspend the thread, to make sure it stops.
		 *	Don't change its suspend count.
		 */
		s = splsched();
		thread_lock(thread);
		thread->state |= TH_SUSP;
		thread_unlock(thread);
		(void) splx(s);
		thread_dowait(thread);

		/*
		 *	Knock it out of any interruptible wait.
		 */
		clear_wait(thread, THREAD_INTERRUPTED, TRUE);

		/*
		 *	If it's at a clean point, we're done.
		 */
		s = splsched();
		thread_lock(thread);
		if (thread->exit_code == THREAD_HALTED) {
			thread_unlock(thread);
			(void) splx(s);
			break;
		}

		/*
		 *	Otherwise, force the thread to stop at a clean
		 *	point, and arrange to wait for it.
		 */

		thread->exit_code = THREAD_HALT;
		thread->wake_active = TRUE;
		assert_wait((int)&thread->wake_active, FALSE);

		/*
		 *	Set it running, so it can notice.  Override
		 *	the suspend count.  We know that the thread
		 *	is suspended and not waiting.
		 *
		 *	Since the thread may hit an interruptible wait
		 *	before it reaches a clean point, we must force it
		 *	to wake us up when it does so.  This involves some
		 *	trickery:
		 *	  We mark the thread SUSPENDED so that thread_block
		 *	will suspend it and wake us up.
		 *	  We mark the thread RUNNING so that it will run.
		 *	  We mark the thread UN-INTERRUPTIBLE (!) so that
		 *	some other thread trying to halt or suspend it won't
		 *	take it off the run queue before it runs.  Since
		 *	dispatching a thread (the tail of thread_block) marks
		 *	the thread interruptible, it will stop at the next
		 *	interruptible wait.
		 */

		switch (thread->state) {

		    case TH_SUSP | TH_SWAPPED:
			thread->state = TH_SUSP | TH_SWAPPED | TH_RUN;
			thread->interruptible = FALSE;
			thread_swapin(thread);
			break;

		    case TH_SUSP:
			thread->state = TH_SUSP | TH_RUN;
			thread->interruptible = FALSE;
			thread_setrun(thread, FALSE);
			break;

		    default:
			panic("thread_halt");
		}
		thread_unlock(thread);
		(void) splx(s);

		/*
		 *	Wait for it to halt
		 */
		thread_block();
	}
}

/*
 *	Thread calls this routine on exit from the kernel when it
 *	notices a halt request.
 */
void	thread_halt_self()
{
	register thread_t	thread = current_thread();

	if (thread->exit_code == THREAD_TERMINATE) {
		/*
		 *	Thread is terminating itself.  Shut
		 *	down IPC, then queue it up for the
		 *	reaper thread.
		 */
		ipc_thread_terminate(thread);

		thread_hold(thread);

		simple_lock(&reaper_lock);
		enqueue_tail(&reaper_queue, (queue_entry_t) thread);
		simple_unlock(&reaper_lock);

		thread->exit_code = THREAD_HALTED;
		thread_wakeup((int)&reaper_queue);
		thread_block();
		panic("the zombie walks!");
		/*NOTREACHED*/
	}
	else {
		/*
		 *	Thread was asked to halt - show that it
		 *	has done so.
		 */
		thread->exit_code = THREAD_HALTED;
		thread_hold(thread);
		thread_block();
	}
}

/*
 *	thread_hold:
 *
 *	Suspend execution of the specified thread.
 *	This is a recursive-style suspension of the thread, a count of
 *	suspends is maintained.
 */
void thread_hold(thread)
	register thread_t	thread;
{
	int			s;

	s = splsched();
	thread_lock(thread);
	thread->suspend_count++;
	thread->state |= TH_SUSP;
	thread_unlock(thread);
	(void) splx(s);
}

/*
 *	thread_dowait:
 *
 *	Wait for a thread to actually enter stopped state.
 */
void thread_dowait(thread)
	register thread_t	thread;
{
	register boolean_t	need_wakeup;
	int			s;

	/*
	 *	If we are requested to wait for the thread to really
	 *	be stopped, and that thread is us, we need to context
	 *	switch (giving up execution, stopping ourselves).
	 */

	if (thread == current_thread()) {
		thread_block();
		return;
	}

	/*
	 *	If a thread is not interruptible, it may not be suspended
	 *	until it becomes interruptible.  In this case, we wait for
	 *	the thread to stop itself, and indicate that we are waiting
	 *	for it to stop so that it can wake us up when it does stop.
	 *
	 *	If the thread is interruptible, we may be able to suspend
	 *	it immediately.  There are several cases:
	 *
	 *	1) The thread is already stopped (trivial)
	 *	2) The thread is waiting.  We mark it as also stopped.
	 *	3) The thread is runnable (marked RUN and on a run queue).
	 *	   We pull it off the run queue and mark it stopped.
	 *	4) The thread is running.  We wait for it to stop.
	 */

	need_wakeup = FALSE;
	s = splsched();
	thread_lock(thread);
	switch(thread->state) {
	    case TH_SUSP:
	    case TH_SUSP | TH_SWAPPED:
	    case TH_SUSP | TH_WAIT | TH_SWAPPED:
		/*
		 *	We win!  Since thread is suspended (without any
		 *	other states) or swapped out, it must be
		 *	interruptible.
		 */
		break;

	    case TH_RUN | TH_SUSP | TH_SWAPPED:
		/*
		 *	Thread is runnable, but is being swapped in.
		 *	Since it was swapped out, it must be interruptible.
		 *	Just mark it not runnable.
		 */
		thread->state = TH_SUSP | TH_SWAPPED;
		break;

	    case TH_RUN | TH_SUSP:
		/*
		 *	If the thread is interruptible, and we can pull
		 *	it off a runq, stop it here.
		 */
		if ((thread->interruptible) &&
		    (rem_runq(thread) != RUN_QUEUE_NULL)) {
			thread->state = TH_SUSP;
			need_wakeup = thread->wake_active;
			thread->wake_active = FALSE;
			break;
		}
		/*
		 *	Fall through to wait for thread to stop.
		 */

	    case TH_RUN | TH_WAIT | TH_SUSP:
	    case TH_WAIT | TH_SUSP:
		/*
		 *	Wait for the thread to stop, or sleep interruptibly
		 *	(thread_block will stop it in the latter case).
		 */
		while ((thread->state & (TH_RUN | TH_SUSP)) != TH_SUSP ||
			!thread->interruptible) {
				thread->wake_active = TRUE;
				thread_sleep((int) &thread->wake_active,
					simple_lock_addr(thread->lock), TRUE);
				thread_lock(thread);
			   }
		break;
	}
	thread_unlock(thread);
	(void) splx(s);

	if (need_wakeup)
	    thread_wakeup((int) &thread->wake_active);
}

void thread_release(thread)
	register thread_t	thread;
{
	int			s;

	s = splsched();
	thread_lock(thread);
	if (--thread->suspend_count == 0) {

		thread->state &= ~TH_SUSP;
		switch (thread->state & (TH_WAIT | TH_RUN | TH_SWAPPED)) {

		    case TH_SWAPPED:
			thread->state |= TH_RUN;
			thread_swapin(thread);
			break;

		    case 0:	/* was only suspended */
			thread->state |= TH_RUN;
			thread_setrun(thread, TRUE);
			break;

		    default:
			break;
		}
	}
	thread_unlock(thread);
	(void) splx(s);

}

kern_return_t thread_suspend(thread)
	register thread_t	thread;
{
	register boolean_t	hold;
	int			spl;

	if (thread == THREAD_NULL)
		return(KERN_INVALID_ARGUMENT);

	hold = FALSE;
	spl = splsched();
	thread_lock(thread);
	if ((thread->user_stop_count)++ == 0)
		hold = TRUE;
	thread_unlock(thread);
	(void) splx(spl);

	/*
	 *	Now hold and wait for the thread if necessary.
	 */
	if (hold) {
		thread_hold(thread);
		thread_dowait(thread);
	}
	return(KERN_SUCCESS);
}

kern_return_t thread_resume(thread)
	register thread_t	thread;
{
	register boolean_t	release;
	register kern_return_t	ret;
	int			s;

	if (thread == THREAD_NULL)
		return(KERN_INVALID_ARGUMENT);

	ret = KERN_SUCCESS;
	release = FALSE;

	s = splsched();
	thread_lock(thread);
	if (thread->user_stop_count > 0) {
		if (--(thread->user_stop_count) == 0)
			release = TRUE;
	}
	else {
		ret = KERN_FAILURE;
	}
	thread_unlock(thread);
	(void) splx(s);

	/*
	 *	Now release the thread if necessary.
	 */
	if (release)
		thread_release(thread);
	return(ret);
}

/*
 *	Return thread's machine-dependent state.
 */
kern_return_t thread_get_state(thread, flavor, old_state, old_state_count)
	register thread_t	thread;
	int			flavor;
	thread_state_t		old_state;	/* pointer to OUT array */
	unsigned int		*old_state_count;	/*IN/OUT*/
{
	kern_return_t		ret;

	if (thread == THREAD_NULL || thread == current_thread()) {
		return (KERN_INVALID_ARGUMENT);
	}

	thread_hold(thread);
	thread_dowait(thread);

	ret = thread_getstatus(thread, flavor, old_state, old_state_count);

	thread_release(thread);
	return(ret);
}

/*
 *	Change thread's machine-dependent state.
 */
kern_return_t thread_set_state(thread, flavor, new_state, new_state_count)
	register thread_t	thread;
	int			flavor;
	thread_state_t		new_state;
	unsigned int		new_state_count;
{
	kern_return_t		ret;

	if (thread == THREAD_NULL || thread == current_thread()) {
		return (KERN_INVALID_ARGUMENT);
	}

	thread_hold(thread);
	thread_dowait(thread);

	ret = thread_setstatus(thread, flavor, new_state, new_state_count);

	thread_release(thread);
	return(ret);
}

kern_return_t thread_info(thread, flavor, thread_info_out,
			thread_info_count)
	register thread_t	thread;
	int			flavor;
	thread_info_t		thread_info_out;	/* pointer to OUT array */
	unsigned int		*thread_info_count;	/*IN/OUT*/
{
	int	s, state, flags;

	register thread_basic_info_t	basic_info;

	if (thread == THREAD_NULL)
		return(KERN_INVALID_ARGUMENT);

	/*
	 *	Only one flavor of information returned at the moment.
	 */
	if (flavor != THREAD_BASIC_INFO ||
	    *thread_info_count < THREAD_BASIC_INFO_COUNT) {
		return(KERN_INVALID_ARGUMENT);
	}

	basic_info = (thread_basic_info_t) thread_info_out;

	s = splsched();
	thread_lock(thread);

	/*
	 *	Update lazy-evaluated scheduler info because someone wants it.
	 */
	if (!(thread->state & TH_RUN) && thread->sched_stamp != sched_tick)
	    update_priority(thread);

	/* fill in info */

	thread_read_times(thread,
			&basic_info->user_time,
			&basic_info->system_time);
	basic_info->base_priority	= thread->priority;
	basic_info->cur_priority	= thread->sched_pri;

	/*
	 *	To calculate cpu_usage, first correct for timer rate,
	 *	then for 5/8 ageing.  The correction factor [3/5] is
	 *	(1/(5/8) - 1).
	 */
	basic_info->cpu_usage = thread->cpu_usage /
					(TIMER_RATE/TH_USAGE_SCALE);
	basic_info->cpu_usage = (basic_info->cpu_usage * 3) / 5;
#if	SIMPLE_CLOCK
	/*
	 *	Clock drift compensation.
	 */
	basic_info->cpu_usage = (basic_info->cpu_usage * 1000000)/sched_usec;
#endif	SIMPLE_CLOCK

	if (thread->state & TH_SWAPPED)
		flags = TH_FLAGS_SWAPPED;
	else if (thread->state & TH_IDLE)
		flags = TH_FLAGS_IDLE;
	else
		flags = 0;

	if (thread->exit_code == THREAD_HALTED)
		state = TH_STATE_HALTED;
	else
	if (thread->state & TH_RUN)
		state = TH_STATE_RUNNING;
	else
	if (!thread->interruptible)
		state = TH_STATE_UNINTERRUPTIBLE;
	else
	if (thread->state & TH_SUSP)
		state = TH_STATE_STOPPED;
	else
	if (thread->state & TH_WAIT)
		state = TH_STATE_WAITING;
	else
		state = 0;		/* ? */

	basic_info->run_state = state;
	basic_info->flags = flags;
	basic_info->suspend_count = thread->user_stop_count;
	if (state == TH_STATE_RUNNING)
		basic_info->sleep_time = 0;
	else
		basic_info->sleep_time = sched_tick - thread->sched_stamp;

	thread_unlock(thread);
	splx(s);

	*thread_info_count = THREAD_BASIC_INFO_COUNT;
	return(KERN_SUCCESS);
}

kern_return_t	thread_abort(thread)
	register thread_t	thread;
{
	int	spl;

	if (thread == THREAD_NULL || thread == current_thread()) {
		return (KERN_INVALID_ARGUMENT);
	}

	/*
	 *	First force the thread to a clean point...
	 */
	thread_halt(thread);

	/*
	 *	Then clear its exit code and set it going again.
	 */
	spl = splsched();
	thread_lock(thread);
	thread->exit_code = THREAD_EXIT;
	thread_unlock(thread);
	(void) splx(spl);
	thread_release(thread);

	return(KERN_SUCCESS);
}

kern_return_t thread_get_special_port(thread, which_port, port)
	register thread_t	thread;
	int		which_port;
	port_t		*port;
{
	register port_t	*portp;

	if (thread == THREAD_NULL)
		return(KERN_INVALID_ARGUMENT);

	switch (which_port) {
	    case THREAD_KERNEL_PORT:
		portp = &thread->thread_tself;
		break;
	    case THREAD_REPLY_PORT:
		portp = &thread->thread_reply;
		break;
	    case THREAD_EXCEPTION_PORT:
		portp = &thread->exception_port;
		break;
	    default:
		return(KERN_INVALID_ARGUMENT);
	}

	ipc_thread_lock(thread);
	if (thread->thread_self == PORT_NULL) {
		/* thread's IPC already inactive */
		ipc_thread_unlock(thread);
		return(KERN_FAILURE);
	}
	
	if ((*port = *portp) != PORT_NULL) {
		port_reference(*portp);
	}
	ipc_thread_unlock(thread);

	return(KERN_SUCCESS);
}

kern_return_t thread_set_special_port(thread, which_port, port)
	register thread_t	thread;
	int		which_port;
	port_t		port;
{
	register port_t	*portp;
	register port_t	old_port;

	if (thread == THREAD_NULL)
		return(KERN_INVALID_ARGUMENT);

	switch (which_port) {
	    case THREAD_KERNEL_PORT:
		portp = &thread->thread_tself;
		break;
	    case THREAD_REPLY_PORT:
		portp = &thread->thread_reply;
		break;
	    case THREAD_EXCEPTION_PORT:
		portp = &thread->exception_port;
		break;
	    default:
		return(KERN_INVALID_ARGUMENT);
	}

	ipc_thread_lock(thread);
	if (thread->thread_self == PORT_NULL) {
		/* thread's IPC already inactive */
		ipc_thread_unlock(thread);
		return(KERN_FAILURE);
	}
	
	old_port = *portp;
	if ((*portp = port) != PORT_NULL)
		port_reference(port);

	ipc_thread_unlock(thread);

	if (old_port != PORT_NULL)
		port_release(old_port);

	return(KERN_SUCCESS);
}

/*
 *	kernel_thread:
 *
 *	Start up a kernel thread in the specified task.
 */

thread_t kernel_thread(task, start)
	task_t	task;
	void	(*start)();
{
	thread_t	thread;

	(void) thread_create(task, &thread);
	thread_start(thread, start, THREAD_SYSTEMMODE);
	thread->priority = BASEPRI_SYSTEM;
	thread->sched_pri = BASEPRI_SYSTEM;
	thread->ipc_kernel = TRUE;
	(void) thread_resume(thread);
	return(thread);
}

/*
 *	reaper_thread:
 *
 *	This kernel thread runs forever looking for threads to destroy
 *	(when they request that they be destroyed, of course).
 */
void reaper_thread()
{
	for (;;) {
		register thread_t thread;

		simple_lock(&reaper_lock);

		while ((thread = (thread_t) dequeue_head(&reaper_queue))
					== THREAD_NULL) {
			assert_wait((int) &reaper_queue, FALSE);
			simple_unlock(&reaper_lock);
			thread_block();
			simple_lock(&reaper_lock);
		}

		simple_unlock(&reaper_lock);

		thread_dowait(thread);		/* may block */
		thread_deallocate(thread);	/* may block */
	}
}
