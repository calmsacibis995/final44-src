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
 * $Log:	mach_factor.c,v $
 * Revision 2.3  89/02/25  18:05:36  gm0w
 * 	Changes for cleanup.
 * 
 * 25-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Added sched_load calculation.
 *
 *  4-Dec-87  David Black (dlb) at Carnegie-Mellon University
 *	Fix calculation to correctly account for threads that are
 *	actually on cpus.  This used to work by accident because if a
 *	processor is not idle, its idle thread was on the local runq;
 *	this is no longer the case.
 *
 * 18-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed conditionals, compute every second.
 *
 */
/*
 *	File:	kern/mach_factor.c
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr.
 *
 *	Compute the Mach Factor.
 */

#include <cpus.h>

#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <kern/sched.h>
#include <mach/machine.h>
#include <sys/types.h>		/* for caddr_t */

long	avenrun[3] = {0, 0, 0};
long	mach_factor[3] = {0, 0, 0};

extern int hz;

/*
 * Values are scaled by LSCALE, defined in h/kernel.h
 */
static	long	fract[3] = {
	800,			/* (4.0/5.0) 5 second average */
	966,			/* (29.0/30.0) 30 second average */
	983,			/* (59.0/60.) 1 minute average */
};

compute_mach_factor()
{
	register int		i;
	register int		ncpus;
	register int		nthreads;
	register machine_slot_t	ms;
	register long		factor_now;
	register long		average_now;
	register long		load_now;

	ncpus = 0;
	nthreads = global_runq.count;
	ms = machine_slot;
	for (i = 0; i < NCPUS; i++) {
		if (ms->running) {
			ncpus++;
			nthreads += local_runq[i].count;
		}
		ms++;
	}
	if (ncpus <= 0)		/* Just in case */
		ncpus = 1;

	nthreads += ncpus - idle_count;  /* account for threads on cpus. */

	factor_now = (ncpus - nthreads);

	if (factor_now <= 0) {
		factor_now = (ncpus * LSCALE) / (nthreads + 1);
		load_now = (nthreads << SCHED_SHIFT) / ncpus;
	}
	else {
		factor_now = (ncpus - nthreads) * LSCALE;
		load_now = SCHED_SCALE;
	}

	/*
	 *	Some bogus calculation intended to make
	 *	the scheduler happy... in general, we're
	 *	making a stab at the number of runnable
	 *	things.
	 *
	 *	Differences between our numbers and our predecessor's:
	 *		We don't count things sleeping with
	 *			priority < PZERO.
	 *		We don't use quite the same decay function.
	 *
	 *	Generally, this number should increase with
	 *	the cpu demand, and be greater than one when
	 *	there aren't enough cycles to go around.
	 */

	average_now = nthreads * LSCALE;

	for (i = 0; i < 3; i++) {
		mach_factor[i] = ( (mach_factor[i]*fract[i])
				 + (factor_now*(LSCALE-fract[i])) ) / LSCALE;
		avenrun[i] = ( (avenrun[i]*fract[i])
			     + (average_now*(LSCALE-fract[i])) ) / LSCALE;
	}

	sched_load = (sched_load + load_now) >> 1;

	/*
	 *	Reschedule ourselves in 1 second.
	 */
	timeout(compute_mach_factor, (caddr_t) 0, 1*hz);
}
