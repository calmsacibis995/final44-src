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
 * $Log:	sched_prim.c,v $
 * Revision 2.17  89/05/30  10:37:44  rvb
 * 	In the idle_thread()'s loop, call some function for mips, so
 * 	that the compiler does not play too smart with caching pointers.
 * 	[89/04/26            af]
 * 
 * Revision 2.16  89/04/22  15:24:45  gm0w
 * 	Removed MACH_NFS dependency from thread_wakeup_one().
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.15  89/03/09  20:15:19  rpd
 * 	More cleanup.
 * 
 * Revision 2.14  89/03/07  18:01:49  rpd
 * 	Picked up fix from dlb for a starvation bug.
 * 
 * Revision 2.13  89/02/25  18:08:04  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.12  89/01/30  22:07:30  rpd
 * 	Added declarations of variables from kern/sched.h.
 * 	(The declarations there use "extern" now.)
 * 	[89/01/25  15:18:44  rpd]
 * 
 * 	Changed "NCPUS > 1" conditionals to MACH_SLOCKS in thread_wakeup_one.
 * 	[89/01/24  13:29:42  rpd]
 * 
 * Revision 2.11  89/01/27  10:21:03  rvb
 * 	Fix locking in thread_wakeup_one().
 * 	[89/01/25            dlb]
 * 
 * Revision 2.10  89/01/18  00:50:06  jsb
 * 	NFS: Added thread_wakeup_one.
 * 	[89/01/17  10:18:12  jsb]
 * 
 * Revision 2.9  89/01/15  16:26:20  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:05:58  rpd]
 * 
 * Revision 2.8  88/12/19  02:46:33  mwyoung
 * 	Corrected include file references.  Use <kern/macro_help.h>.
 * 	[88/11/22            mwyoung]
 * 	
 * 	In thread_wakeup_with_result(), only lock threads that have the
 * 	appropriate wait_event.  Both the wait_event and the hash bucket
 * 	links are only modified with both the thread *and* hash bucket
 * 	locked, so it should be safe to read them with either locked.
 * 	
 * 	Documented the wait event mechanism.
 * 	
 * 	Summarized ancient history.
 * 	[88/11/21            mwyoung]
 * 
 * Revision 2.7  88/08/25  18:18:00  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Avoid unsigned computation in wait_hash.
 * 	[88/08/16  00:29:51  mwyoung]
 * 	
 * 	Add priority check to thread_check; make queue index unsigned,
 * 	so that checking works correctly at all.
 * 	[88/08/11  18:47:55  mwyoung]
 * 
 * Revision 2.6  88/08/06  18:25:03  rpd
 * Eliminated use of kern/mach_ipc_defs.h.
 * 
 * Revision 2.5  88/07/20  16:39:35  rpd
 * Changed "NCPUS > 1" conditionals that were eliminating dead
 * simple locking code to MACH_SLOCKS conditionals.
 *
 */
/*
 *	File:	sched_prim.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr.
 *
 *	Scheduling primitives
 *
 * Historical summary:
 *
 *	Redo priority recomputation. [dlb, 29 feb 88]
 *	New accurate timing. [dlb, 19 feb 88]
 *	Simplified choose_thread and thread_block. [dlb, 18 dec 87]
 *	Add machine-dependent hooks in idle loop. [dbg, 24 nov 87]
 *	Quantum scheduling changes. [dlb, 14 oct 87]
 *	Replaced scheduling logic with a state machine, and included
 *	 timeout handling. [dbg, 05 oct 87]
 *	Deactivate kernel pmap in idle_thread. [dlb, 23 sep 87]
 *	Favor local_runq in choose_thread. [dlb, 23 sep 87]
 *	Hacks for master processor handling. [rvb, 12 sep 87]
 *	Improved idle cpu and idle threads logic. [dlb, 24 aug 87]
 *	Priority computation improvements. [dlb, 26 jun 87]
 *	Quantum-based scheduling. [avie, dlb, apr 87]
 *	Improved thread swapper. [avie, 13 mar 87]
 *	Lots of bug fixes. [dbg, mar 87]
 *	Accurate timing support. [dlb, 27 feb 87]
 *	Reductions in scheduler lock contention. [dlb, 18 feb 87]
 *	Revise thread suspension mechanism. [avie, 17 feb 87]
 *	Real thread handling [avie, 31 jan 87]
 *	Direct idle cpu dispatching. [dlb, 19 jan 87]
 *	Initial processor binding. [avie, 30 sep 86]
 *	Initial sleep/wakeup. [dbg, 12 jun 86]
 *	Created. [avie, 08 apr 86]
 */

#include <cpus.h>
#include <simple_clock.h>
#include <stat_time.h>	/* XXX */

#include <sys/types.h>

#include <kern/queue.h>
#include <kern/thread.h>
#include <kern/lock.h>
#include <kern/sched.h>
#include <mach/machine.h>
#include <vm/vm_kern.h>
#include <vm/vm_map.h>
#include <kern/parallel.h>
#include <machine/machparam.h>	/* For def'n of splsched() */
#include <machine/pmap.h>

#include <machine/cpu.h>

#include <kern/sched_prim.h>
#include <kern/thread_swap.h>

#include <kern/macro_help.h>

extern int hz, thread_swap_tick;

struct run_queue	global_runq;
struct run_queue	local_runq[NCPUS];

struct cpu_info	cpu_info[NCPUS];
struct thread	*next_thread[NCPUS];	/* next thread to run */
int		runrun[NCPUS];	/* cpu can be resched. at same pri */

struct thread	*idle_thread_array[NCPUS]; /* holds idle threads */

queue_head_t	idle_queue;		/* queue for idle cpus */
int		idle_count;		/* number of idle cpus */
decl_simple_lock_data(,idle_lock)	/* lock for idle structures */

#if	NCPUS > 1
int		machine_quantum[NCPUS+1];
int		quantum_adj_index;	/* used to spread out cpus
						   when quantum changes */
decl_simple_lock_data(,quantum_adj_lock)

int		last_quantum[NCPUS];	/* used to detect changes */
#endif	NCPUS > 1
int		min_quantum;	/* defines max context switch rate */
int		sys_quantum;	/* used by set_runq */

unsigned	sched_tick;
int		sched_load;

#if	SIMPLE_CLOCK
int		sched_usec;
#endif	SIMPLE_CLOCK


/*
 *	State machine
 *
 * states are combinations of:
 *  R	running
 *  W	waiting (or on wait queue)
 *  S	suspended (or will suspend)
 *  N	non-interruptible
 *  O	swapped out
 *
 * init	action 
 *	assert_wait	thread_block	clear_wait	suspend	resume	swapout	swapin
 *
 * R	RW, RWN		R;   setrun	-		RS	-	-
 * RS	RWS, RWNS	S;  wake_active	-		-	R	-
 * RN	RWN		RN;  setrun	-		RNS	-	-
 * RNS	RWNS		RNS; setrun	-		-	RN	-
 *
 * RW			W		R		RWS	-	-
 * RWN			WN		RN		RWNS	-	-
 * RWS			WS; wake_active	RS		-	RW	-
 * RWNS			WNS		RNS		-	RWN	-
 *
 * W					R;   setrun	WS	-	WO
 * WN					RN;  setrun	WNS	-	-
 * WNS					RNS; setrun	-	WN	-
 * WO					RO;  swapin	WSO	-	-
 *
 * S					-		-	R	SO
 * SO					-		-	RO	-
 * WS					S		-	W	WSO
 * WSO					SO		-	WO	-
 *
 * RO					-		RSO	-		R
 * RSO					-		-	RO		RS
 */

/*
 *	Waiting protocols and implementation:
 *
 *	Each thread may be waiting for exactly one event; this event
 *	is set using assert_wait().  That thread may be awakened either
 *	by performing a thread_wakeup_with_result() on its event,
 *	or by directly waking that thread up with clear_wait().
 *
 *	The implementation of wait events uses a hash table.  Each
 *	bucket is queue of threads having the same hash function
 *	value; the chain for the queue (linked list) is the run queue
 *	field.  [It is not possible to be waiting and runnable at the
 *	same time.]
 *
 *	Locks on both the thread and on the hash buckets govern the
 *	wait event field and the queue chain field.  Because wakeup
 *	operations only have the event as an argument, the event hash
 *	bucket must be locked before any thread.
 *
 *	Scheduling operations may also occur at interrupt level; therefore,
 *	interrupts below splsched() must be prevented when holding
 *	thread or hash bucket locks.
 *
 *	The wait event hash table declarations are as follows:
 */

#define NUMQUEUES	59

queue_head_t		wait_queue[NUMQUEUES];
decl_simple_lock_data(,	wait_lock[NUMQUEUES])

#define wait_hash(event) \
	(((int)((event) < 0 ? ((event) ^ -1) : (event)))%NUMQUEUES)

void sched_init()
{
	register int	i;

	wait_queue_init();
	simple_lock_init(&global_runq.lock);
	global_runq.low = 0;
	global_runq.count = 0;
	for (i = 0; i < NRQS; i++) {
		register int j;

		for (j = 0; j < NCPUS; j++) {
			simple_lock_init(&local_runq[j].lock);
			queue_init(&local_runq[j].runq[i]);
			local_runq[j].low = 0;
			local_runq[j].count = 0;
		}
		queue_init(&global_runq.runq[i]);
	}

	min_quantum = hz / 10;		/* context switch 10 times/second */

	for ( i=0 ; i < NCPUS ; i++ ) {
		queue_init(&cpu_info[i].cpi_queue);
		cpu_info[i].cpi_state = CPU_OFF_LINE;
		cpu_info[i].cpi_number = i;
		next_thread[i] = THREAD_NULL;
		idle_thread_array[i] = THREAD_NULL;
#if	NCPUS > 1
		last_quantum[i] = min_quantum;
#endif	NCPUS > 1
	}

	queue_init(&idle_queue);
	idle_count = 0;
#if	NCPUS > 1
	quantum_adj_index = 1;
	simple_lock_init(&quantum_adj_lock);
#endif	NCPUS > 1
	sched_tick = 0;
#if	SIMPLE_CLOCK
	sched_usec = 0;
#endif	SIMPLE_CLOCK
}

/*
 *	Precalculate the appropriate system quanta based on load.  The
 *	index into machine_quantum is the number of threads in the
 *	global_runq.  It is limited to machine_info.avail_cpus.
 */

quantum_set()
{
#if	NCPUS > 1
	register int	i,ncpus;
#endif	NCPUS > 1

#if	NCPUS > 1
	ncpus = machine_info.avail_cpus;

	for ( i=1 ; i <= ncpus ; i++) {
		machine_quantum[i] = ((min_quantum * ncpus) + (i/2)) / i ;
	}
	machine_quantum[0] = 2 * machine_quantum[1];
	i = ((global_runq.count > machine_info.avail_cpus) ?
		machine_info.avail_cpus : global_runq.count);
	sys_quantum = machine_quantum[i];
#else	NCPUS > 1
	sys_quantum = min_quantum;
#endif	NCPUS > 1
}

wait_queue_init()
{
	register int i;

	for (i = 0; i < NUMQUEUES; i++) {
		queue_init(&wait_queue[i]);
		simple_lock_init(&wait_lock[i]);
	}
}

int	sched_debug = 0;

/*
 *	Thread timeout routine, called when timer expires.
 *	Called at splhigh.
 */
thread_timeout(_thread, t)
	int	_thread;
	int	t;
{
	register thread_t	thread = (thread_t) _thread;
#ifdef	lint
	t++;
#endif	lint
	thread_lock(thread);
	thread->timer_set = FALSE;
	thread_unlock(thread);
	clear_wait(thread, THREAD_TIMED_OUT, FALSE);
}

/*
 *	thread_set_timeout:
 *
 *	Set a timer for the current thread, if the thread
 *	is ready to wait.  Must be called between assert_wait()
 *	and thread_block().
 */
 
void thread_set_timeout(t)
	int	t;	/* timeout interval in ticks */
{
	register thread_t	thread = current_thread();
	register int s;

	s = splsched();
	thread_lock(thread);
	if ((thread->state & TH_WAIT) != 0) {
		thread->timer_set = TRUE;
		timeout(thread_timeout, (caddr_t)thread, t);
	}
	thread_unlock(thread);
	splx(s);
}

/*
 *	assert_wait:
 *
 *	Assert that the current thread is about to go to
 *	sleep until the specified event occurs.
 */
void assert_wait(event, interruptible)
	int		event;
	boolean_t	interruptible;
{
	register queue_t	q;
	register int		index;
	register thread_t	thread;
#if	MACH_SLOCKS
	register simple_lock_t	lock;
#endif	MACH_SLOCKS
	int			s;

	thread = current_thread();
	if (sched_debug)
		printf("assert_wait: thread = 0x%x, event = 0x%x\n", thread, event);
	if (thread->wait_event != 0) {
		printf("assert_wait: already asserted event 0x%x\n",
			thread->wait_event);
		panic("assert_wait");
	}
 	s = splsched();
	if (event != 0) {
		index = wait_hash(event);
		q = &wait_queue[index];
#if	MACH_SLOCKS
		lock = &wait_lock[index];
#endif	MACH_SLOCKS
		simple_lock(lock);
		thread_lock(thread);
		enqueue_tail(q, (queue_entry_t) thread);
		thread->wait_event = event;
		thread->state |= TH_WAIT;
		thread->interruptible = interruptible;
		thread_unlock(thread);
		simple_unlock(lock);
	}
	else {
		thread_lock(thread);
		thread->state |= TH_WAIT;
		thread->interruptible = interruptible;
		thread_unlock(thread);
	}
	splx(s);
}

/*
 *	clear_wait:
 *
 *	Clear the wait condition for the specified thread.  Start the thread
 *	executing if that is appropriate.
 *
 *	parameters:
 *	  thread		thread to awaken
 *	  result		Wakeup result the thread should see
 *	  interrupt_only	Don't wake up the thread if it isn't
 *				interruptible.
 */
void clear_wait(thread, result, interrupt_only)
	register thread_t	thread;
	int			result;
	boolean_t		interrupt_only;
{
	register int		index;
	register queue_t	q;
#if	MACH_SLOCKS
	register simple_lock_t	lock;
#endif	MACH_SLOCKS
	register int		event;
	int			s;

	s = splsched();
	thread_lock(thread);
	if (interrupt_only && !thread->interruptible) {
		/*
		 *	can't interrupt thread
		 */
		thread_unlock(thread);
		splx(s);
		return;
	}

	event = thread->wait_event;
	if (event != 0) {
		thread_unlock(thread);
		index = wait_hash(event);
		q = &wait_queue[index];
#if	MACH_SLOCKS
		lock = &wait_lock[index];
#endif	MACH_SLOCKS
		simple_lock(lock);
		/*
		 *	If the thread is still waiting on that event,
		 *	then remove it from the list.  If it is waiting
		 *	on a different event, or no event at all, then
		 *	someone else did our job for us.
		 */
		thread_lock(thread);
		if (thread->wait_event == event) {
			remqueue(q, (queue_entry_t)thread);
			thread->wait_event = 0;
			event = 0;		/* cause to run below */
		}
		simple_unlock(lock);
	}
	if (event == 0) {
		register int	state = thread->state;

		if (thread->timer_set) {
			thread->timer_set = FALSE;
			untimeout(thread_timeout, (caddr_t)thread);
		}
		switch (state) {
		    case TH_WAIT | TH_SUSP:
			/*
			 *	Suspend thread if interruptible
			 */
			if (thread->interruptible) {
			    thread->state = TH_SUSP;
			    thread->wait_result = result;
			    break;
			}
			/* fall through */
		    case TH_WAIT:
			/*
			 *	Sleeping and not suspendable - put
			 *	on run queue.
			 */
			thread->state = (state & ~TH_WAIT) | TH_RUN;
			thread->wait_result = result;
			thread_setrun(thread, TRUE);
			break;

		    case TH_WAIT | TH_SWAPPED:
			/*
			 *	Thread is swapped out, but runnable
			 */
			thread->state = TH_RUN | TH_SWAPPED;
			thread->wait_result = result;
			thread_swapin(thread);
			break;

		    default:
			/*
			 *	Either already running, or suspended.
			 */
			if (state & TH_WAIT) {
				thread->state = state & ~TH_WAIT;
				thread->wait_result = result;
			}
			break;
		}
	}
	thread_unlock(thread);
	splx(s);
}

/*
 *	thread_wakeup_with_result:
 *
 *	Wakeup all threads that are waiting for the specified
 *	event.
 */
void thread_wakeup_with_result(event, result)
	register int	event;
{
	register queue_t	q;
	register int		index;
	register thread_t	thread, next_th;
#if	MACH_SLOCKS
	register simple_lock_t	lock;
#endif	MACH_SLOCKS
	int			s;
	register int		state;

	index = wait_hash(event);
	q = &wait_queue[index];
	s = splsched();
#if	MACH_SLOCKS
	lock = &wait_lock[index];
#endif	MACH_SLOCKS
	simple_lock(lock);
	thread = (thread_t) queue_first(q);
	while (!queue_end(q, (queue_entry_t)thread)) {
		next_th = (thread_t) queue_next((queue_t) thread);

		if (thread->wait_event == event) {
			thread_lock(thread);

			if (sched_debug)
				printf("thread_wakeup: thread 0x%x woken, event = 0x%x\n", thread, event);
			remqueue(q, (queue_entry_t) thread);
			thread->wait_event = 0;
			if (thread->timer_set) {
				thread->timer_set = FALSE;
				untimeout(thread_timeout, (caddr_t)thread);
			}
			state = thread->state;
			switch (state) {
			    case TH_WAIT | TH_SUSP:
				if (thread->interruptible) {
				    thread->state = TH_SUSP;
				    thread->wait_result = result;
				    break;
				}
				/* fall through */
			    case TH_WAIT:
				thread->state = (state & ~TH_WAIT) | TH_RUN;
				thread->wait_result = result;
				thread_setrun(thread, TRUE);
				break;
				
			    case TH_WAIT | TH_SWAPPED:
				simple_unlock(lock);
				thread->state = TH_RUN | TH_SWAPPED;
				thread->wait_result = result;
				thread_swapin(thread);
				thread_unlock(thread);
				/*
				 * Restart the search, since we had
				 * to unlock for thread_swapin (it calls
				 * thread_wakeup, which may find the
				 * swapin thread on the same queue).
				 */
				simple_lock(lock);
				thread = (thread_t) queue_first(q);
				continue;
				
			    default:
				if ((state & TH_WAIT) == 0)
				    panic("thread_wakeup");
				thread->state = state & ~TH_WAIT;
				thread->wait_result = result;
			    break;
			}
			thread_unlock(thread);
		}
		thread = next_th;
	}
	simple_unlock(lock);
	splx(s);
}

/*
 *	thread_wakeup_one:
 *
 *	Wakeup first thread in queue that is waiting for the specified
 *	event.
 */
thread_wakeup_one(event)
	register int	event;
{
	register queue_t	q;
	register int		index;
	register thread_t	thread, next_th;
#if	MACH_SLOCKS
	register simple_lock_t	lock;
#endif	MACH_SLOCKS
	int			s;
	register int		state;

	index = wait_hash(event);
	q = &wait_queue[index];
	s = splsched();
#if	MACH_SLOCKS
	lock = &wait_lock[index];
#endif	MACH_SLOCKS
	simple_lock(lock);
	thread = (thread_t) queue_first(q);
	while (!queue_end(q, (queue_entry_t)thread)) {
		next_th = (thread_t) queue_next((queue_t) thread);

		if (thread->wait_event == event) {
			thread_lock(thread);

			if (sched_debug)
				printf("thread_wakeup_one: thread 0x%x woken, event = 0x%x\n", thread, event);
			remqueue(q, thread);
			thread->wait_event = 0;
			if (thread->timer_set) {
				thread->timer_set = FALSE;
				untimeout(thread_timeout, (caddr_t)thread);
			}
			state = thread->state;
			switch (state) {
			    case TH_WAIT | TH_SUSP:
				if (thread->interruptible) {
				    thread->state = TH_SUSP;
				    thread->wait_result = THREAD_AWAKENED;
				    thread_unlock(thread);
				    goto out;
				}
				/* fall through */
			    case TH_WAIT:
				thread->state = (state & ~TH_WAIT) | TH_RUN;
				thread->wait_result = THREAD_AWAKENED;
				thread_setrun(thread, TRUE);
				thread_unlock(thread);
				goto out;
				
			    case TH_WAIT | TH_SWAPPED:
				simple_unlock(lock);
				thread->state = TH_RUN | TH_SWAPPED;
				thread->wait_result = THREAD_AWAKENED;
				thread_swapin(thread);
				thread_unlock(thread);
				/*
				 *	Done!
				 */
				splx(s);
				return;
				
			    default:
				if ((state & TH_WAIT) == 0)
				    panic("thread_wakeup");
				thread->state = state & ~TH_WAIT;
				thread->wait_result = THREAD_AWAKENED;
				thread_unlock(thread);
				goto out;
			}
		}
		thread = next_th;
	}
out:
	simple_unlock(lock);
	splx(s);
}

/*
 *	thread_sleep:
 *
 *	Cause the current thread to wait until the specified event
 *	occurs.  The specified lock is unlocked before releasing
 *	the cpu.  (This is a convenient way to sleep without manually
 *	calling assert_wait).
 */
void thread_sleep(event, lock, interruptible)
	int		event;
	simple_lock_t	lock;
	boolean_t	interruptible;
{
	if (sched_debug)
		printf("thread_sleep: event = 0x%x\n", event);
	assert_wait(event, interruptible);	/* assert event */
	simple_unlock(lock);			/* release the lock */
	thread_block();				/* block ourselves */
}

/*
 *	thread_bind:
 *
 *	Force a thread to execute on the specified processor slot.
 *	If the thread is currently executing, it may wait until its
 *	time slice is up before switching onto the specified processor.
 *
 *	A cpu number of -1 is a 'thread_unbind': let the thread run
 *	on any processor.
 */
thread_bind(thread, which_cpu)
	register thread_t	thread;
	int			which_cpu;
{
	int		s;

	s = splsched();
	thread_lock(thread);
	if (which_cpu == -1)
		thread->whichq = &global_runq;
	else
		thread->whichq = &local_runq[which_cpu];
	thread_unlock(thread);
	(void) splx(s);
}

/*
 *	thread_block:
 *
 *	Block the current thread.  If the thread is runnable
 *	then someone must have woken it up between its request
 *	to sleep and now.  In this case, it goes back on a
 *	run queue.
 */
void thread_block()
{
	register thread_t	thread = current_thread();
	register thread_t	*threadp;
	register int		mycpu = cpu_number();
	register int		state;

	if (sched_debug)
		printf("thread_block: thread = 0x%x\n", thread);

	if (save_context())
		return;

	if (vm_map_pmap(thread->task->map) != kernel_pmap) {
	    PMAP_DEACTIVATE(vm_map_pmap(thread->task->map), thread, mycpu);
	}

	timer_switch(&kernel_timer[mycpu]);

	/*
	 *	See if we should go back on a run queue.
	 *	Note that save_context is expected to leave
	 *	us in a non-interruptable state, so we don't
	 *	have to play around with spl changes.
	 */

	thread_lock(thread);
	state = thread->state;
	switch (state) {

	    case TH_RUN | TH_SUSP:
		if (thread->interruptible) {
		    /*
		     *	Suspend the thread
		     */
		    thread->state = TH_SUSP;
		    if (thread->wake_active) {
			thread->wake_active = FALSE;
			thread_wakeup((int)&thread->wake_active);
		    }
		    break;
		}
		/* fall through */

	    case TH_RUN:
		/*
		 *	No reason to stop.  Put back on a run queue.
		 */
		thread_setrun(thread, FALSE);
		break;

	    case TH_RUN | TH_WAIT | TH_SUSP:
		if (thread->interruptible) {
		    /*
		     *	Suspended and interruptible.
		     */
		    thread->state = TH_WAIT | TH_SUSP;
		    if (thread->wake_active) {
			/*
			 *	Someone wants to know when this thread really stops.
			 */
			thread->wake_active = FALSE;
			thread_wakeup((int)&thread->wake_active);
		    }
		    break;
		}
		/* fall through */

	    case TH_RUN | TH_WAIT:
		/*
		 *	Waiting, and not suspended or not interruptible.
		 */
		thread->state = state & ~TH_RUN;
		break;

	    default:
		/*
		 *	Drop idle thread -- it's already in idle_thread_array.
		 */
		if (state != (TH_RUN | TH_IDLE)) {
		    /*
		     *	Not running - oops
		     */
		    panic("thread_block");
		}
		break;
	}
	thread_unlock(thread);

	if (should_exit[mycpu]) {
		/*
		 *	Clean up idle structures for clean exit.
		 */
		idle_exit();
		PMAP_DEACTIVATE(kernel_pmap, thread, mycpu);
		cpu_down(mycpu);
		halt_cpu();
	}

	threadp = &next_thread[mycpu];
	thread = *threadp;
	if (thread != THREAD_NULL) {
		*threadp = THREAD_NULL;
		cpu_state(mycpu) = CPU_RUNNING;
	}
	else {
		/*
		 *	Check for obvious simple case; local runq is
		 *	empty and global runq has entry at hint.
		 */
		if (local_runq[mycpu].count > 0) {
			thread = choose_thread();
		}
		else {
			register queue_t	q;
			
			simple_lock(&global_runq.lock);
			q = global_runq.runq + global_runq.low;
			
			if ((global_runq.count == 0) || (queue_empty(q))) {
				simple_unlock(&global_runq.lock);
				thread = choose_thread();
			}
			else {
				thread = (thread_t) dequeue_head(q);
				thread->runq = RUN_QUEUE_NULL;
				global_runq.count--;
				simple_unlock(&global_runq.lock);
			}
			
		}
	}

#if	!defined(mips)
	active_threads[mycpu] = thread;
#endif

	/*
	 *	Thread is now interruptible.
	 */
	thread->interruptible = TRUE;
	thread->quantum = sys_quantum;

	timer_switch(&thread->system_timer);

	if (vm_map_pmap(thread->task->map) != kernel_pmap) {
	    PMAP_ACTIVATE(vm_map_pmap(thread->task->map), thread, mycpu);
	}

	load_context(thread);
	/*NOTREACHED*/
}

/*
 *	thread_switch:
 *
 *	Switch directly from the current thread to a specified
 *	thread.  Both the current and new threads must be
 *	runnable.
 */
void thread_switch(new_thread)
	register thread_t	new_thread;
{
	register thread_t	thread = current_thread();
	register int		mycpu = cpu_number();

	if (sched_debug)
		printf("thread_switch: thread = 0x%x\n", thread);

	if (save_context())
		return;

	if (vm_map_pmap(thread->task->map) != kernel_pmap) {
	    PMAP_DEACTIVATE(vm_map_pmap(thread->task->map), thread, mycpu);
	}

	timer_switch(&kernel_timer[mycpu]);

	/*
	 *	See if we should go back on a run queue.
	 *	Note that save_context is expected to leave
	 *	us in a non-interruptable state, so we don't
	 *	have to play around with spl changes.
	 */

	thread_lock(thread);
	switch (thread->state) {

	    case TH_RUN | TH_SUSP:
		if (thread->interruptible) {
		    /*
		     *	Suspend the thread
		     */
		    thread->state = TH_SUSP;
		    if (thread->wake_active) {
			thread->wake_active = FALSE;
			thread_wakeup((int)&thread->wake_active);
		    }
		    break;
		}
		/* fall through */

	    case TH_RUN:
		/*
		 *	No reason to stop.  Put back on a run queue.
		 */
		thread_setrun(thread, FALSE);
		break;

	    default:
		/*
		 *	Not runnable - oops
		 */
		panic("thread_switch");
		break;
	}
	thread_unlock(thread);

	/*
	 *	Directly activate the new thread
	 */
#if	!defined(mips)
	active_threads[mycpu] = new_thread;
#endif

	/*
	 *	Thread is now interruptible.
	 */
	new_thread->interruptible = TRUE;
	new_thread->quantum = sys_quantum;

	timer_switch(&new_thread->system_timer);

	if (vm_map_pmap(new_thread->task->map) != kernel_pmap) {
	    PMAP_ACTIVATE(vm_map_pmap(new_thread->task->map), new_thread,
		mycpu);
	}
	load_context(new_thread);
	/*NOTREACHED*/
}


/*
 *	Define shifts for simulating (5/8)**n
 */

shift_data_t	wait_shift[32] = {
	{1,1},{1,3},{1,-3},{2,-7},{3,5},{3,-5},{4,-8},{5,7},
	{5,-7},{6,-10},{7,10},{7,-9},{8,-11},{9,12},{9,-11},{10,-13},
	{11,14},{11,-13},{12,-15},{13,17},{13,-15},{14,-17},{15,19},{16,18},
	{16,-19},{17,22},{18,20},{18,-20},{19,26},{20,22},{20,-22},{21,-27}};

/*
 *	set_pri:
 *
 *	Set the priority of the specified thread to the specified
 *	priority.  This may cause the thread to change queues.
 *
 *	The thread *must* be locked by the caller.
 */

#define set_pri(th, pri)				\
	MACRO_BEGIN					\
	register struct run_queue	*rq;		\
							\
	rq = rem_runq((th));				\
	(th)->sched_pri = pri;				\
	if (rq != RUN_QUEUE_NULL) {			\
		thread_setrun(th, TRUE);		\
	}						\
	MACRO_END

#ifdef	PRI_SHIFT_2
#if	PRI_SHIFT_2 > 0
#define do_priority_computation(th, pri)				\
	MACRO_BEGIN							\
	(pri) = (th)->priority	/* start with base priority */		\
	    + ((th)->sched_usage >> (PRI_SHIFT + SCHED_SHIFT))		\
	    + ((th)->sched_usage >> (PRI_SHIFT_2 + SCHED_SHIFT));	\
	if ((pri) > 127) (pri) = 127;					\
	MACRO_END
#else	PRI_SHIFT_2
#define do_priority_computation(th, pri)				\
	MACRO_BEGIN							\
	(pri) = (th)->priority	/* start with base priority */		\
	    + ((th)->sched_usage >> (PRI_SHIFT + SCHED_SHIFT))		\
	    - ((th)->sched_usage >> (SCHED_SHIFT - PRI_SHIFT_2));	\
	if ((pri) > 127) (pri) = 127;					\
	MACRO_END
#endif	PRI_SHIFT_2
#else	defined(PRI_SHIFT_2)
#define do_priority_computation(th, pri)				\
	MACRO_BEGIN							\
	(pri) = (th)->priority	/* start with base priority */		\
	    + ((th)->sched_usage >> PRI_SHIFT + SCHED_SHIFT);		\
	if ((pri) > 127) (pri) = 127;					\
	MACRO_END
#endif	defined(PRI_SHIFT_2)

/*
 *	compute_priority:
 *
 *	Compute the effective priority of the specified thread.
 *	The effective priority computation is as follows:
 *
 *	Take the base priority for this thread and add
 *	to it an increment derived from its cpu_usage.
 *
 *	The thread *must* be locked by the caller. 
 */

compute_priority(thread)
	register thread_t	thread;
{
	register int	pri;

	do_priority_computation(thread, pri);
	set_pri(thread, pri);
}

/*
 *	compute_my_priority:
 *
 *	Version of compute priority for current thread or thread
 *	being manipulated by scheduler (going on or off a runq).
 */

compute_my_priority(thread)
	register thread_t	thread;
#define compute_my_priority(thread) 				\
	MACRO_BEGIN						\
	register int temp_pri;					\
								\
	do_priority_computation(thread,temp_pri);		\
	(thread)->sched_pri = temp_pri;				\
	MACRO_END

{
    	compute_my_priority(thread);
}

/*
 *	recompute_priorities:
 *
 *	Update the priorities of all threads periodically.
 */
recompute_priorities()
{
#if	SIMPLE_CLOCK
	int	new_usec;
#endif	SIMPLE_CLOCK

    	thread_swap_tick++;	/* for swapper */
	sched_tick++;		/* age usage one more time */
#if	SIMPLE_CLOCK
	/*
	 *	Compensate for clock drift.  sched_usec is an
	 *	exponential average of the number of microseconds in
	 *	a second.  It decays in the same fashion as cpu_usage.
	 */
	new_usec = sched_usec_elapsed();
	sched_usec = (5*sched_usec + 3*new_usec)/8;
#endif	SIMPLE_CLOCK
	timeout(recompute_priorities, (caddr_t) 0, hz);
	if (sched_tick & 1)
		do_thread_scan();
}

/*
 *	update_priority
 *
 *	Cause the priority computation of a thread that has been 
 *	sleeping or suspended to "catch up" with the system.  Thread
 *	*MUST* be locked by caller.  If thread is running, then this
 *	can only be called by the thread on itself.
 */
update_priority(thread)
	register thread_t	thread;

#define update_priority(thread)						\
	MACRO_BEGIN							\
	register int	ticks;						\
	register shift_t	shiftp;					\
									\
	ticks = sched_tick - (thread)->sched_stamp;			\
									\
	if (ticks <= 0) panic("Bad update");				\
									\
	/*								\
	 *	If asleep for more than 30 seconds forget all		\
	 *	cpu_usage, else catch up on missed aging.		\
	 *	5/8 ** n is approximated by the two shifts		\
	 *	in the wait_shift array.				\
	 */								\
	(thread)->sched_stamp += ticks;					\
	thread_timer_delta((thread));					\
	if (ticks >  30) {						\
		(thread)->cpu_usage = 0;				\
		(thread)->sched_usage = 0;				\
	}								\
	else {								\
		(thread)->cpu_usage += (thread)->cpu_delta;		\
		(thread)->sched_usage += (thread)->sched_delta;		\
		shiftp = &wait_shift[ticks];				\
		if (shiftp->shift2 > 0) {				\
		    (thread)->cpu_usage =				\
			((thread)->cpu_usage >> shiftp->shift1) +	\
			((thread)->cpu_usage >> shiftp->shift2);	\
		    (thread)->sched_usage =				\
			((thread)->sched_usage >> shiftp->shift1) +	\
			((thread)->sched_usage >> shiftp->shift2);	\
		}							\
		else {							\
		    (thread)->cpu_usage =				\
			((thread)->cpu_usage >> shiftp->shift1) -	\
			((thread)->cpu_usage >> -(shiftp->shift2));	\
		    (thread)->sched_usage =				\
			((thread)->sched_usage >> shiftp->shift1) -	\
			((thread)->sched_usage >> -(shiftp->shift2));	\
		}							\
	}								\
	(thread)->cpu_delta = 0;					\
	(thread)->sched_delta = 0;					\
	compute_my_priority(thread);					\
	(thread)->preempt_pri = (thread)->sched_pri;			\
	MACRO_END
{
    	update_priority(thread);
}

/*
 *	thread_setrun:
 *
 *	Put a thread on a run queue.  Run queue is determined by whichq
 *	field in thread.  Caller must lock thread.
 */

void thread_setrun(th, may_preempt)
	register thread_t	th;
	boolean_t		may_preempt;
{
	register run_queue_t	rq;
	register cpu_info_t	cpu_ptr;

	if ((rq = th->whichq) == RUN_QUEUE_NULL)
		panic("thread_setrun - null rq");
	/*
	 *	Update priority if appropriate.
	 */
	if (th->sched_stamp != sched_tick) {
		update_priority(th);
	}

	if (th->runq != RUN_QUEUE_NULL) {
	    printf("thread_setrun: thread 0x%x already on run queue 0x%x.\n",
		th, th->runq);
	    printf("thread_setrun: requested to place on run queue 0x%x.\n",
		rq);
	    panic("thread_setrun");
	}

#if	NCPUS > 1
	/*
	 *	Try to dispatch the thread directly onto an idle processor.
	 */

	if (idle_count > 0) {
	    simple_lock(&idle_lock);
	    if (rq == &global_runq) {
		if (idle_count > 0) {
		    cpu_ptr = (cpu_info_t) dequeue_head(&idle_queue);
		    idle_count--;
		    next_thread[cpu_ptr->cpi_number] = th;
		    cpu_ptr->cpi_state = CPU_DISPATCHING;
		    simple_unlock(&idle_lock);
		    return;
		}
	    }
	    else {
		register int	whichcpu;

		whichcpu = rq - local_runq;	/* XXX */
		if (cpu_info[whichcpu].cpi_state == CPU_IDLE) {
		    idle_count--;
		    cpu_ptr = &cpu_info[whichcpu];
		    remqueue(&idle_queue, (queue_entry_t)cpu_ptr);
		    next_thread[whichcpu] = th;
		    cpu_ptr->cpi_state = CPU_DISPATCHING;
		    simple_unlock(&idle_lock);
		    return;
		}
	    }
	    simple_unlock(&idle_lock);
	}
#else	NCPUS > 1
	if (idle_count > 0) {
	    cpu_ptr = (cpu_info_t) dequeue_head(&idle_queue);
	    idle_count--;
	    next_thread[cpu_ptr->cpi_number] = th;
	    cpu_ptr->cpi_state = CPU_DISPATCHING;
	    return;
	}
#endif	NCPUS > 1

	{
	    register unsigned int	whichq;

	    whichq = th->sched_pri >> 2;
	    if (whichq >= NRQS) {
		printf("thread_setrun: pri too high (%d)\n", th->sched_pri);
		whichq = NRQS - 1;
	    }

	    simple_lock(&rq->lock);	/* lock the run queue */
	    enqueue_tail(&rq->runq[whichq], (queue_entry_t) th);
	    if (whichq < rq->low) rq->low = whichq;	/* minimize */
	    rq->count++;
	    th->runq = rq;
#if	DEBUG
	    thread_check(th, rq);
	    checkrq(rq);
#endif	DEBUG
	    simple_unlock(&rq->lock);
	}

	/*
	 *	Preempt check.
	 */
	if (may_preempt && csw_check()) {
	    runrun[cpu_number()]++;
	    aston();
	}
}

/*
 *	rem_runq:
 *
 *	Remove a thread from its run queue.
 *	The run queue that the process was on is returned
 *	(or RUN_QUEUE_NULL if not on a run queue).  Thread *must* be locked
 *	before calling this routine.  Unusual locking protocol on runq
 *	field in thread structure makes this code interesting; see thread.h.
 */

struct run_queue *rem_runq(th)
	thread_t		th;
{
	register struct run_queue	*rq;

	rq = th->runq;
	/*
	 *	If rq is RUN_QUEUE_NULL, the thread will stay out of the
	 *	run_queues because the caller locked the thread.  Otherwise
	 *	the thread is on a runq, but could leave.
	 */
	if (rq != RUN_QUEUE_NULL) {
		simple_lock(&rq->lock);
#if	DEBUG
		checkrq(rq);
#endif	DEBUG
		if (rq == th->runq) {
			/*
			 *	Thread is in a runq and we have a lock on
			 *	that runq.
			 */
#if	DEBUG
			checkrq(rq);
			thread_check(th, rq);
#endif	DEBUG
			remqueue(&rq->runq[0], (queue_entry_t) th);
			rq->count--;
#if	DEBUG
			checkrq(rq);
#endif	DEBUG
			th->runq = RUN_QUEUE_NULL;
			simple_unlock(&rq->lock);
		}
		else {
			/*
			 *	The thread left the runq before we could
			 * 	lock the runq.  It is not on a runq now, and
			 *	can't move again because this routine's
			 *	caller locked the thread.
			 */
			simple_unlock(&rq->lock);
			rq = RUN_QUEUE_NULL;
		}
	}

	return(rq);
}


/*
 *	choose_thread:
 *
 *	Choose a thread to execute.  The thread chosen is removed
 *	from its run queue.  Note that this requires only that the runq
 *	lock be held.
 *
 *	Strategy:
 *		Check local runq first; if anything found, run it.
 *		Else check global runq; if nothing found, return idle thread.
 */

thread_t choose_thread()
{
	thread_t th;
	register queue_t q;
	register run_queue_t runq;
	register int i;
	int mycpu;

	/*
	 *	Macro to pull a thread off a runq and return it.
	 */

#define DEQUEUE_THREAD 						\
		q = runq->runq + runq->low;			\
		for (i = runq->low; i < NRQS ; i++) {		\
		    if (!queue_empty(q)) {			\
			th = (thread_t) dequeue_head(q);	\
			th->runq = RUN_QUEUE_NULL;		\
			runq->count--;				\
			runq->low = i;				\
			simple_unlock(&runq->lock);		\
			return(th);				\
		    }						\
		    else {					\
			q++;					\
		    }						\
		}						\
		panic("choose_thread: empty runq with non-zero count.\n")

	mycpu = cpu_number();
	runq = &local_runq[mycpu];

	if (runq->count > 0) {
	    simple_lock(&runq->lock);
	    if (runq->count > 0) {
	    	DEQUEUE_THREAD;
		/*NOTREACHED*/
	    }
	    else {
		simple_unlock(&runq->lock);
	    }
	}

	if (global_runq.count > 0) {
	    runq = &global_runq;
	    simple_lock(&runq->lock);
	    if (runq->count > 0) {
		DEQUEUE_THREAD;
		/*NOTREACHED*/
	    }
	    simple_unlock(&runq->lock);
	}
	/*
	 *	Nothing is runnable, so set this processor idle and return
	 *	its idle thread.
	 */
	simple_lock(&idle_lock);
	cpu_state(mycpu) = CPU_IDLE;
	if (mycpu == master_cpu)
		enqueue_tail(&idle_queue, &cpu_info[mycpu].cpi_queue);
	else
		enqueue_head(&idle_queue, &cpu_info[mycpu].cpi_queue);

	idle_count++;
	simple_unlock(&idle_lock);

	return(idle_thread_array[mycpu]);
}
#undef	DEQUEUE_THREAD

/*
 *	This is the idle thread, which just looks for other threads
 *	to execute.
 */


/*
 *	no_dispatch_count counts number of times processors go non-idle
 *	without being dispatched.  This should be very rare.
 */
int	no_dispatch_count = 0;

void idle_thread()
{
	register thread_t *threadp;
	register boolean_t *exitp;
	register int *gcount, *lcount;
	struct thread *th;
	int mycpu;

	th = current_thread();
	th->priority = 127;
	th->sched_pri = 127;
	thread_block();				/* return on correct cpu */

	(void) splsched();
	mycpu = cpu_number();			/* who am I? */
	/*
	 *	Now that we are on our processor, set the idle flag to
	 *	indicate that this is an idle thread, enter ourselves
	 *	in the idle array, and thread_block() to get us out of
	 *	the run queues (and set the processor idle when we
	 *	run next time).
	 */
	thread_lock(th);
	th->state |= TH_IDLE;
	thread_unlock(th);
	idle_thread_array[mycpu] = th;
	thread_block();

	threadp = &next_thread[mycpu];
	exitp = &should_exit[mycpu];
	gcount = &global_runq.count;
	lcount = &(local_runq[mycpu].count);

	while (TRUE) {
		runrun[mycpu] = 0;

#ifdef	MARK_CPU_IDLE
		MARK_CPU_IDLE(mycpu);
#else	MARK_CPU_IDLE
		/*
		 *	Deactivate kernel pmap to avoid shootdown
		 *	interupts.
		 */
		PMAP_DEACTIVATE(kernel_pmap, th, mycpu);
#ifdef	balance
		light_off(mycpu);
#endif	balance
#endif	MARK_CPU_IDLE

		spl0();		/* for idle loop */
/*
 *	This cpu will be dispatched (by thread_setrun) by setting next_thread
 *	to the value of the thread to run next.  Also check runq counts
 *	and should_exit.
 *
 */
		while ((*threadp == THREAD_NULL) && (*gcount == 0) &&
		       (*lcount == 0) &&  !(*exitp))
#ifdef	mips
				/*
				 * This funcall prevents the compiler from
				 * being too smart about caching pointers
				 */
				set_leds();
#else	mips
				continue;		/* wait */
#endif	mips

		(void) splsched();
		/*
		 * If cpu was not dispatched (rare) set it non-idle.
		 */
		if (cpu_info[mycpu].cpi_state == CPU_IDLE) {
			simple_lock(&idle_lock);
			if (cpu_info[mycpu].cpi_state == CPU_IDLE) {
				no_dispatch_count++;
				idle_count--;
				remqueue(&idle_queue,
				    (queue_entry_t) &cpu_info[mycpu]);
				cpu_state(mycpu) = CPU_RUNNING;
			}
			simple_unlock(&idle_lock);
		}

#ifdef	MARK_CPU_ACTIVE
		MARK_CPU_ACTIVE(mycpu);
#else	MARK_CPU_ACTIVE
		PMAP_ACTIVATE(kernel_pmap, th, mycpu);
#ifdef	balance
		light_on(mycpu);
#endif	balance
#endif	MARK_CPU_ACTIVE

		thread_block();
	}
}

/*
 *	Clean up idle state to exit cpu.  Called from thread_block(), assume
 *	interrupts locked out.
 */
idle_exit()
{
	register int		mycpu;
	register thread_t	thread;

	mycpu = cpu_number();
	thread = THREAD_NULL;

	simple_lock(&idle_lock);
	if (cpu_state(mycpu) == CPU_IDLE) {
		/*
		 *  Make this cpu no longer idle
		 */
		remqueue(&idle_queue, &cpu_info[mycpu].cpi_queue);
		idle_count--;
	}
	simple_unlock(&idle_lock);

	/*
	 *  Release the thread in next_thread if there is one.
	 */
	thread = next_thread[mycpu];
	next_thread[mycpu] = THREAD_NULL;

	if (thread != THREAD_NULL) {
		thread_lock(thread);
		thread_setrun(thread, TRUE);
		thread_unlock(thread);
	}

}
		
/*
 *	Just in case someone doesn't use the macro
 */
#undef	thread_wakeup
void		thread_wakeup(x)
	register int	x;
{
	thread_wakeup_with_result(x, THREAD_AWAKENED);
}

#define MAX_STUCK_THREADS	16

/*
 *	do_thread_scan: scan for stuck threads.  A thread is stuck if
 *	it is runnable but its priority is so low that it has not
 *	run for several seconds.  It's priority should be higher, but
 *	won't be until it runs and calls update_priority.  The scanner
 *	finds these threads and does the updates.
 *
 *	Scanner runs in two passes.  Pass one squirrels likely
 *	thread id's away in an array  (takes out references for them).
 *	Pass two does the priority updates.  This is necessary because
 *	the run queue lock is required for the candidate scan, but
 *	cannot be held during updates [set_pri will deadlock].
 *
 *	Array length should
 *	be enough so that restart isn't necessary, but restart
 *	logic is included.  Only scans global runq.  May have to
 *	be generalized when processor sets are implemented.
 */

do_thread_scan()
{
	thread_t		stuck_threads[MAX_STUCK_THREADS];
	register int		stuck_count = 0;
	int			s;
	register queue_t	q;
	run_queue_t		runq;
	boolean_t		restart_needed = FALSE;
	register thread_t	thread;
	register int		count;

	runq = &global_runq;
	s = splsched();

Restart:
	simple_lock(&runq->lock);
	if((count = runq->count) > 0) {
	    q = runq->runq + runq->low;
	    while (count > 0) {
		thread = (thread_t) queue_first(q);
		while(!queue_end(q, (queue_entry_t)thread)) {
		    if (thread->state == TH_RUN &&
			sched_tick - thread->sched_stamp > 1) {
			    /*
			     *	Stuck, save its id for later.
			     */
			    if (stuck_count == MAX_STUCK_THREADS) {
				/*
				 *	!@#$% No more room.
				 */
				restart_needed = TRUE;
				goto Done;
			    }
			    /*
			     *	Inline version of thread_reference
			     */
			    thread_lock(thread);
			    thread->ref_count++;
			    thread_unlock(thread);
			    stuck_threads[stuck_count++] = thread;
		    }
		    count--;
		    thread = (thread_t) queue_next((queue_t)thread);
		}
		q++;
	    }
	}
Done:
	simple_unlock(&runq->lock);

	/*
	 *	Ok, we now have a collection of candidates -- fix them.
	 */

	while (stuck_count > 0) {
	    thread = stuck_threads[--stuck_count];
	    stuck_threads[stuck_count] = THREAD_NULL;
	    thread_lock(thread);
	    if (thread->state == TH_RUN &&
		sched_tick - thread->sched_stamp > 1) {
		    /*
		     *	Do the priority update.  Have to do
		     *	separate set_pri because thread is probably
		     *	on wrong queue for new priority.
		     */
		    update_priority(thread);
		    set_pri(thread, thread->sched_pri);
	    }
	    thread_unlock(thread);
	    thread_deallocate(thread);
	}

	if (restart_needed) {
	    restart_needed = FALSE;
	    goto Restart;
	}

	splx(s);
}
		
#if	someday
/*
 *	create_wait(event, persistent)
 *
 *	Create and initialize a new wait structure corresponding to the
 *	specified event.  A persistence is specified to determine if the
 *	wait structure should ever be deallocated.  (Persistent wait
 *	structures are used for frequently used events).
 *
 *	The wait structure is entered into the event hash table.
 */

wait_t create_wait(event, persistent)
	event_t		event;
	boolean_t	persistent;
{
	wait_t		wait;
	wait_bucket_t	bucket;

	/*
	 *	Allocate and initialize and wait structure.
	 */

	wait = (wait_t) zalloc(wait_zone);
	wait->event = event;
	wait->persistent = persistent;
	queue_init(&wait->thread_list);
	simple_lock_init(&wait->lock);

	/*
	 *	Insert the wait structure into the hash table.
	 */

	bucket = wait_buckets[wait_hash(event)];
	lock_write(&bucket->lock);
	queue_enter(&bucket->waitq, wait, wait_t, listq);
	lock_write_done(&bucket->lock);
}

/*
 *	assert_wait(event)
 *
 *	assert that the current thread wants to wait for the specified
 *	event.  The thread does not actually wait at this time, but it
 *	should wait sometime in the near future.
 */

assert_wait(event)
	event_t		event;
{
	wait_t		wait;
	wait_bucket_t	bucket;
	boolean_t	found;
	thread_t	thread;

	/*
	 *	Find the bucket for this event.
	 */

	bucket = wait_buckets[wait_hash(event)];
	found = FALSE;

	/*
	 *	See if there is already a wait structure for the
	 *	event.
	 */

	lock_read(&bucket->lock);
	wait = (wait_t) queue_first(&bucket->waitq);
	while (!queue_end(&bucket->waitq, (queue_entry_t) wait)) {
		if (wait->event == event) {
			found = TRUE;
			break;
		}
		wait = (wait_t) queue_next(&wait->listq);
	}
	lock_read_done(&bucket->lock);

	/*
	 *	If there was no such entry, then create (and insert)
	 *	a non-persistent wait structure.
	 */

	if (!found)
		wait = create_wait(FALSE);
	}

	/*
	 *	Now we have a wait structure corresponding to our event
	 *	(which is in the hash table).  We must now insert our thread
	 *	into the list of threads waiting for this event, which means
	 *	we create yet another structure to represent it (because a
	 *	thread may be waiting for more than one event).
	 *
	 *	Then, link the thread wait structure into the thread list
	 *	of what it is waiting on.
	 */

	thread = current_thread();
	twait = (thread_wait_t) zalloc(thread_wait_zone);
	twait->thread = thread;

	simple_lock(&wait->lock);
	queue_enter(&wait->thread_list, twait, thread_wait_t, threadq);
	queue_enter(&thread->wait_list, twait, thread_wait_t, waitq);
	simple_unlock(&wait->lock);
}
#endif	someday
#if	DEBUG
checkrq(rq)
	run_queue_t	rq;
{
	register queue_t	q1;
	register int		i, j;
	register queue_entry_t	e;

	j = 0;
	q1 = rq->runq;
	for (i = 0; i < NRQS; i++) {
		if (q1->next == q1) {
			if (q1->prev != q1->next)
				panic("checkrq");
		}
		for (e = q1->next; e != q1; e = e->next) {
			j++;
			if (e->next->prev != e)
				panic("checkrq-2");
			if (e->prev->next != e)
				panic("checkrq-3");
		}
		q1++;
	}
	if (j != rq->count)
		panic("checkrq-count");
}

thread_check(th, rq)
	register thread_t	th;
	register run_queue_t	rq;
{
	register unsigned int 	whichq;

	whichq = th->sched_pri >> 2;
	if (whichq >= NRQS) {
		printf("thread_check: priority too high\n");
		whichq = NRQS-1;
	}
	if ((th->links.next == &rq->runq[whichq]) &&
		(rq->runq[whichq].prev != (queue_entry_t)th))
			panic("thread_check");
}
#endif	DEBUG
