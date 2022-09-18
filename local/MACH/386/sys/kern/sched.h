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
 * $Log:	sched.h,v $
 * Revision 2.9  89/03/09  20:15:11  rpd
 * 	More cleanup.
 * 
 * Revision 2.8  89/02/25  18:07:55  gm0w
 * 	Kernel code cleanup.
 * 	Put entire file under #indef KERNEL.
 * 	[89/02/15            mrt]
 * 
 * Revision 2.7  89/02/07  01:04:03  mwyoung
 * Relocated from sys/sched.h
 * 
 * Revision 2.6  89/01/30  22:08:24  rpd
 * 	Made variable declarations use "extern".
 * 	[89/01/25  15:23:09  rpd]
 * 
 * Revision 2.5  89/01/15  16:34:43  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:17:50  rpd]
 * 
 * Revision 2.4  88/12/19  02:51:43  mwyoung
 * 	Use <kern/macro_help.h> to avoid lint.
 * 	[88/12/08            mwyoung]
 * 
 * Revision 2.3  88/08/24  02:42:44  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:22:04  mwyoung]
 *
 * 29-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	SIMPLE_CLOCK: added sched_usec for drift compensation.
 *
 * 25-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Added sched_load and related constants.  Moved thread_timer_delta
 *	here because it depends on sched_load.
 *
 * 19-Feb-88  David Black (dlb) at Carnegie-Mellon University
 *	Added sched_tick and shift definitions for more flexible ageing.
 *
 * 18-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed conditionals, purged history.
 */
/*
 *	File:	sched.h
 *	Author:	Avadis Tevanian, Jr.
 *	Copyright (C) 1985, Avadis Tevanian, Jr.
 *
 *	Header file for scheduler.
 *
 */

#ifndef	_KERN_SCHED_H_
#define _KERN_SCHED_H_

#include <cpus.h>
#include <simple_clock.h>
#include <stat_time.h>

#include <kern/queue.h>
#include <kern/lock.h>
#include <kern/macro_help.h>

#if	STAT_TIME

/*
 *	Statistical timing uses microseconds as timer units.  16 bit shift
 *	yields priorities.  PRI_SHIFT_2 isn't needed.
 */
#define PRI_SHIFT	16

#else	STAT_TIME

/*
 *	Otherwise machine provides shift(s) based on time units it uses.
 */
#include <machine/sched_param.h>

#endif	STAT_TIME

#define NRQS	32			/* 32 run queues per cpu */

struct run_queue {
	queue_head_t		runq[NRQS];	/* one for each priority */
	decl_simple_lock_data(,	lock)		/* one lock for all queues */
	int			low;		/* low queue value */
	int			count;		/* count of threads runable */
};

typedef struct run_queue	*run_queue_t;
#define RUN_QUEUE_NULL	((run_queue_t) 0)

extern struct run_queue	global_runq;
extern struct run_queue	local_runq[NCPUS];

#define other_threads_runnable(rqi, runq) \
	(((runq)->count > 0) &&  (rqi >= (runq)->low))

/*
 *	Scheduler routines.
 */

extern struct run_queue	*rem_runq();
extern struct thread	*choose_thread();

/*
 *	Structures for efficient dispatching of idle cpus.
 */

struct cpu_info {
	struct queue_entry	cpi_queue;	/* for idle_queue */
	int			cpi_state;	/* state of each cpu */
	int			cpi_number;	/* this cpu's number */
};

typedef	struct cpu_info		*cpu_info_t;

#define cpu_state(cpu)		cpu_info[cpu].cpi_state

#define CPU_OFF_LINE	(-1)
#define CPU_RUNNING	0
#define CPU_IDLE	1
#define CPU_DISPATCHING	2

#define cpu_idle(cpu)	(cpu_info[cpu].cpi_state == CPU_IDLE)

extern struct cpu_info	cpu_info[NCPUS];
extern struct thread	*next_thread[NCPUS];	/* next thread to run */
extern int		runrun[NCPUS];	/* cpu can be resched. at same pri */

extern struct thread	*idle_thread_array[NCPUS]; /* holds idle threads */

extern queue_head_t	idle_queue;		/* queue for idle cpus */
extern int		idle_count;		/* number of idle cpus */
decl_simple_lock_data(extern,idle_lock)	/* lock for idle structures */

	/*
	 *	Data structures for runtime quantum adjustment.
	 */
#if	NCPUS > 1
extern int		machine_quantum[NCPUS+1];
extern int		quantum_adj_index;	/* used to spread out cpus
						   when quantum changes */
decl_simple_lock_data(extern,quantum_adj_lock)

extern int		last_quantum[NCPUS];	/* used to detect changes */
#endif	NCPUS > 1
extern int		min_quantum;	/* defines max context switch rate */
extern int		sys_quantum;	/* used by set_runq */

/*
 *	Default base priorities for threads.
 */
#define BASEPRI_SYSTEM	25
#define BASEPRI_USER	50

/*
 *	Shift structures for holding update shifts.  Actual computation
 *	is  usage = (usage >> shift1) +/- (usage >> abs(shift2))  where the
 *	+/- is determined by the sign of shift 2.
 */
struct shift {
	int	shift1;
	int	shift2;
};

typedef	struct shift	*shift_t, shift_data_t;

/*
 *	sched_tick increments once a second.  Used to age priorities.
 *	sched_load is the load factor for the scheduler.
 */

extern unsigned	sched_tick;
extern int	sched_load;

#define SCHED_SCALE	128
#define SCHED_SHIFT	7

/*
 *	thread_timer_delta macro takes care of both thread timers.
 */

#define thread_timer_delta(thread)  				\
MACRO_BEGIN							\
	register unsigned	delta;				\
								\
	delta = 0;						\
	TIMER_DELTA((thread)->system_timer,			\
		(thread)->system_timer_save, delta);		\
	TIMER_DELTA((thread)->user_timer,			\
		(thread)->user_timer_save, delta);		\
	(thread)->cpu_delta += delta;				\
	(thread)->sched_delta += delta * sched_load;		\
MACRO_END

#if	SIMPLE_CLOCK
/*
 *	sched_usec is an exponential average of number of microseconds
 *	in a second for clock drift compensation.
 */

extern int	sched_usec;
#endif	SIMPLE_CLOCK

#endif	_KERN_SCHED_H_
