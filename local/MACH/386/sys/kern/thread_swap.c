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
 * $Log:	thread_swap.c,v $
 * Revision 2.7.2.1  90/07/10  11:45:49  rvb
 * 	The flag "stack_swapout_allowed" says to swap out the kernel
 * 	stack; by default it is FALSE.
 * 	The flag "pmap_collect_allowed" says do a pmap_collect;
 * 	by default it is TRUE.
 * 	[90/06/20            rvb]
 * 
 * Revision 2.7  89/03/09  20:17:00  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  18:10:17  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/01/15  16:28:14  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:09:18  rpd]
 * 
 * Revision 2.4  88/10/27  10:50:40  rpd
 * 	Changed includes to the new style.  Removed extraneous semis
 * 	from the swapper_lock/swapper_unlock macros.
 * 	[88/10/26  14:49:09  rpd]
 * 
 * 15-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Fix improper handling of swapper_lock() in swapin_thread().
 *	Problem discovery and elegant recoding due to Richard Draves.
 *
 *  4-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Remove vax-specific code.
 *
 *  1-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Logic change due to replacement of wait_time field in thread
 *	with sched_stamp.  Extra argument to thread_setrun().
 *
 * 25-Jan-88  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Notify pcb module that pcb is about to be unwired by calling
 *	pcb_synch(thread).
 *	
 * 21-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Fix lots more race conditions (thread_swapin called during
 *	swapout, thread_swapin called twice) by adding a swapper state
 *	machine to each thread.  Moved thread_swappable here from
 *	kern/thread.c.
 *
 * 12-Nov-87  David Golub (dbg) at Carnegie-Mellon University
 *	Fix race condition in thread_swapout: mark thread as swapped
 *	before swapping out its stack, so that an intervening wakeup
 *	will put it on the swapin list.
 *
 *  5-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changed to new scheduling state machine.
 *
 * 15-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 *  5-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added check for THREAD_SWAPPABLE in swapout_scan().
 *
 * 14-Jul-87  David Golub (dbg) at Carnegie-Mellon University
 *	Truncate the starting address and round up the size given to
 *	vm_map_pageable, when wiring/unwiring kernel stacks.
 *	KERNEL_STACK_SIZE is not necessarily a multiple of page_size; if
 *	it isn't, forgetting to round the address and size to page
 *	boundaries results in panic.  Kmem_alloc and kmem_free, used in
 *	thread.c to allocate and free kernel stacks, already round to
 *	page boundaries.
 *
 * 26-Jun-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Add thread_swapout_allowed flag to make it easy to turn
 *	off swapping when debugging.
 *
 *  4-Jun-87  David Golub (dbg) at Carnegie-Mellon University
 *	Pass correct number of parameters to lock_init - initialize
 *	swap_lock as sleepable instead of calling lock_sleepable
 *	separately.
 *
 *  1-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Include vm_param.h to pick up KERNEL_STACK_SIZE definition.
 *
 * 20-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Lower ipl before calling thread_swapout().
 *
 * 19-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Fix one race condition in this (not so buggy) version - since
 *	thread_swapin can be called from interrupts, must raise IPL when
 *	locking swapper_lock.
 *
 * 09-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created, based somewhat loosely on the earlier (which was a highly
 *	buggy, race condition filled version).
 *
 */
/*
 *
 *	File:	kern/thread_swap.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1987, Avadis Tevanian, Jr. and Richard F. Rashid
 *
 *	Mach thread swapper:
 *		Find idle threads to swap, freeing up kernel stack resources
 *		at the expense of allowing them to execute.
 *
 *		Swap in threads that need to be run.  This is done here
 *		by the swapper thread since it cannot be done (in general)
 *		when the kernel tries to place a thread on a run queue.
 *
 *	Note: The act of swapping a thread in Mach does not mean that
 *	its memory gets forcibly swapped to secondary storage.  The memory
 *	for the task corresponding to a swapped thread is paged out
 *	through the normal paging mechanism.
 *
 */

#include <kern/thread.h>
#include <kern/lock.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#include <kern/sched_prim.h>
#include <kern/thread_swap.h>
#include <machine/machparam.h>		/* for splsched */

boolean_t		 stack_swapout_allowed = FALSE;
boolean_t		thread_swapout_allowed = TRUE;
boolean_t		  pmap_collect_allowed = TRUE;

queue_head_t		swapin_queue;
decl_simple_lock_data(,	swapper_lock_data)

#define swapper_lock()		simple_lock(&swapper_lock_data)
#define swapper_unlock()	simple_unlock(&swapper_lock_data)

/*
 *	swapper_init: [exported]
 *
 *	Initialize the swapper module.
 */
void swapper_init()
{
	queue_init(&swapin_queue);
	simple_lock_init(&swapper_lock_data);
}

/*
 *	thread_swapin: [exported]
 *
 *	Place the specified thread in the list of threads to swapin.  It
 *	is assumed that the thread is locked, therefore we are at splsched.
 */

void thread_swapin(thread)
	thread_t	thread;
{
	switch (thread->swap_state) {
	    case TH_SW_OUT:
		/*
		 *	Swapped out - queue for swapin thread
		 */
		thread->swap_state = TH_SW_COMING_IN;
		swapper_lock();
		enqueue_tail(&swapin_queue, (queue_entry_t) thread);
		swapper_unlock();
		thread_wakeup((int) &swapin_queue);
		break;

	    case TH_SW_GOING_OUT:
		/*
		 *	Being swapped out - wait until swapped out,
		 *	then queue for swapin thread (in thread_swapout).
		 */
		thread->swap_state = TH_SW_WANT_IN;
		break;

	    case TH_SW_WANT_IN:
	    case TH_SW_COMING_IN:
		/*
		 *	Already queued for swapin thread, or being
		 *	swapped in
		 */
		break;

	    default:
		/*
		 *	Swapped in or unswappable
		 */
		panic("thread_swapin");
	}
}

/*
 *	thread_doswapin:
 *
 *	Swapin the specified thread, if it should be runnable, then put
 *	it on a run queue.  No locks should be held on entry, as it is
 *	likely that this routine will sleep (waiting for page faults).
 */
void thread_doswapin(thread)
	thread_t	thread;
{
	register vm_offset_t	addr;
	register int		s;

	/*
	 *	Wire down the kernel stack.
	 */

	if (stack_swapout_allowed) {
		addr = thread->kernel_stack;
		(void) vm_map_pageable(kernel_map, trunc_page(addr),
				round_page(addr + KERNEL_STACK_SIZE), FALSE);
	}

	/*
	 *	Place on run queue if appropriate.
	 */

	s = splsched();
	thread_lock(thread);
	thread->swap_state = TH_SW_IN;
	thread->state &= ~TH_SWAPPED;
	if (thread->state & TH_RUN)
		thread_setrun(thread, TRUE);
	thread_unlock(thread);
	(void) splx(s);
}

/*
 *	thread_swapout:
 *
 *	Swap out the specified thread (unwire its kernel stack).
 *	The thread must already be marked as 'swapping out'.
 */
void thread_swapout(thread)
	thread_t	thread;
{
	register vm_offset_t	addr;
	int			s;

	/*
	 *	Thread is marked as swapped before we swap it out; if
	 *	it is awakened while we are swapping it out, it will
	 *	be put on the swapin list.
	 */

	/*
	 * Notify the pcb module that it must update any
 	 * hardware state associated with this thread.
	 */
	pcb_synch(thread);

	/*
	 *	Unwire the kernel stack.
	 */

	if (stack_swapout_allowed) {
		addr = thread->kernel_stack;
		(void) vm_map_pageable(kernel_map, trunc_page(addr),
				round_page(addr + KERNEL_STACK_SIZE), TRUE);
	}

	if (pmap_collect_allowed)
		pmap_collect(vm_map_pmap(thread->task->map));

	s = splsched();
	thread_lock(thread);
	switch (thread->swap_state) {
	    case TH_SW_GOING_OUT:
		thread->swap_state = TH_SW_OUT;
		break;

	    case TH_SW_WANT_IN:
		thread->swap_state = TH_SW_OUT;
		thread_swapin(thread);
		break;

	    default:
		panic("thread_swapout");
	}
	thread_unlock(thread);
	splx(s);
}

/*
 *	swapin_thread: [exported]
 *
 *	This procedure executes as a kernel thread.  Threads that need to
 *	be swapped in are swapped in by this thread.
 */
void swapin_thread()
{
	while (TRUE) {
		register thread_t	thread;
		register int		s;

		s = splsched();
		swapper_lock();

		while ((thread = (thread_t) dequeue_head(&swapin_queue))
							== THREAD_NULL) {
			assert_wait((int) &swapin_queue, FALSE);
			swapper_unlock();
			splx(s);
			thread_block();
			s = splsched();
			swapper_lock();
		}

		swapper_unlock();
		splx(s);

		thread_doswapin(thread);
	}
}

int	thread_swap_tick = 0;
int	last_swap_tick = 0;

#define MAX_SWAP_RATE	60

/*
 *	swapout_threads: [exported]
 *
 *	This procedure is called periodically by the pageout daemon.  It
 *	determines if it should scan for threads to swap and starts that
 *	scan if appropriate.  (Algorithm is like that of old package)
 */
void swapout_threads()
{
	if (thread_swapout_allowed &&
	    (thread_swap_tick > (last_swap_tick + MAX_SWAP_RATE))) {
		last_swap_tick = thread_swap_tick;
		thread_wakeup((int) &thread_swap_tick);	/* poke swapper */
	}
}

/*
 *	swapout_scan:
 *
 *	Scan the list of all threads looking for threads to swap.
 */
void swapout_scan()
{
	register thread_t	thread, prev;
	register int		s;

	prev = THREAD_NULL;
	s = splsched();
	simple_lock(&all_threads_lock);
	thread = (thread_t) queue_first(&all_threads);
	while (!queue_end(&all_threads, (queue_entry_t) thread)) {
		thread_lock(thread);
		if ((thread->state & (TH_RUN | TH_SWAPPED)) == 0 &&
		    thread->swap_state == TH_SW_IN &&
		    thread->interruptible &&
		    (sched_tick - thread->sched_stamp > 10)) {
			thread->state |= TH_SWAPPED;
			thread->swap_state = TH_SW_GOING_OUT;
			thread->ref_count++;
			thread_unlock(thread);
			simple_unlock(&all_threads_lock);
			(void) splx(s);
			thread_swapout(thread);		/* swap it */

			if (prev != THREAD_NULL)
				thread_deallocate(prev);	/* may block */
			prev = thread;
			s = splsched();
			simple_lock(&all_threads_lock);
			thread_lock(thread);
		}
		thread_unlock(thread);
		thread = (thread_t) queue_next(&thread->all_threads);
	}
	simple_unlock(&all_threads_lock);
	splx(s);
	if (prev != THREAD_NULL)
		thread_deallocate(prev);
}

/*
 *	swapout_thread: [exported]
 *
 *	Executes as a separate kernel thread.  This thread is periodically
 *	woken up.  When this happens, it initiates the scan for threads
 *	to swap.
 */
void swapout_thread()
{
	(void) spl0();
	while (TRUE) {
		assert_wait((int) &thread_swap_tick, FALSE);
		thread_block();
		swapout_scan();
	}
}

/*
 *	Mark a thread as swappable or unswappable.  Must be called
 *	before the thread is first allowed to run.
 */
void thread_swappable(thread, is_swappable)
	thread_t	thread;
	boolean_t	is_swappable;
{
	int	s = splsched();
	thread_lock(thread);
	if (is_swappable)
	    thread->swap_state = TH_SW_IN;
	else
	    thread->swap_state = TH_SW_UNSWAPPABLE;
	thread_unlock(thread);
	(void) splx(s);
}
