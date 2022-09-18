/* 
 * Mach Operating System
 * Copyright (c) 1994-1987 Carnegie Mellon University
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
 * $Log:	sched.c,v $
 * Revision 2.3  94/12/16  10:50:46  dbg
 * 	RT-MACH merge: use periodic_clock instead of sys_clock.
 * 	[94/06/15            dbg]
 * 
 * Revision 2.2  93/11/17  17:20:51  dbg
 * 	machparam.h -> machspl.h
 * 	[93/05/21            dbg]
 * 
 * 	Created file to hold routines for periodic scheduling
 * 	calculations.
 * 	[93/05/11            dbg]
 * 
 */ 

#include <kern/mach_clock.h>
#include <kern/mach_timer.h>
#include <kern/sched.h>

#include <machine/machspl.h>

/*
 *	sched_tick increments once a second.  Used to age priorities.
 */
unsigned int	sched_tick = 0;

#if	SIMPLE_CLOCK
/*
 *	sched_usec is an exponential average of number of microseconds
 *	in a second for clock drift compensation.
 */

int	sched_usec = 0;
#endif	/* SIMPLE_CLOCK */

extern void	compute_mach_factor(void);
extern void	ts_thread_scan(void);

/*
 *	sched_calculations:
 *
 *	Perform various periodic scheduling and statistics
 *	functions.  Runs off a periodic timer, at one-second
 *	intervals.
 */
void sched_calculations(void)
{
	/*
	 *	Age usage one more second
	 */
	sched_tick++;

#if	SIMPLE_CLOCK
	/*
	 *	Compensate for clock drift.  sched_usec is an
	 *	exponential average of the number of microseconds in
	 *	a second.  It decays in the same fashion as cpu_usage.
	 */
	{
	    int	new_usec;

	    new_usec = sched_usec_elapsed();
	    sched_usec = (5*sched_usec + 3*new_usec)/8;
	}
#endif	/* SIMPLE_CLOCK */

	/*
	 *	Compute the load factors
	 */
	compute_mach_factor();

	/*
	 *	Raise the priorities of low-priority timesharing threads,
	 *	every other second.
	 */
	if (sched_tick & 1)
	    ts_thread_scan();
}

/*
 *	Periodic timer for sched_calculations.
 */
struct timer_elt	sched_timer;

/*
 *	Initialize the timer.
 */
void init_sched_calculations(void)
{
	/*
	 * Recalculate priorities once per second
	 */
	sched_timer.te_fcn	= (void (*)(void *))sched_calculations;
	sched_timer.te_param	= 0;
	sched_timer.te_flags	= TELT_PERIODIC;
	sched_timer.te_period.seconds = 1;
	sched_timer.te_period.nanoseconds = 0;
	sched_timer.te_clock	= periodic_clock;

	timer_elt_enqueue(&sched_timer, sched_timer.te_period, FALSE);
}

