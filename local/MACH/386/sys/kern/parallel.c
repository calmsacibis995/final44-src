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
 * $Log:	parallel.c,v $
 * Revision 2.2  89/02/25  18:07:24  gm0w
 * 	Changes for cleanup.
 * 
 * 15-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Use thread_bind (inline version) to bind thread to master cpu
 *	while holding unix-lock.
 *
 *  9-Oct-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Define unix_reset for longjmp/setjmp reset.
 *
 * 25-Sep-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Clean out some debugging code.
 *
 * 21-Sep-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Created.
 *
 */


#include <cpus.h>

#if	NCPUS > 1

#include <kern/thread.h>
#include <kern/sched_prim.h>
#include <kern/parallel.h>


void unix_master()
{
	register thread_t t = current_thread();
	
	if (! (++( t->unix_lock )))	{

		/* thread_bind(t, master_cpu); */
		t->whichq = &local_runq[master_cpu];

		if (cpu_number() != master_cpu) {
			t->interruptible = FALSE;
			thread_block();
		}
	}
}

void unix_release()
{
	register thread_t t = current_thread();

	t->unix_lock--;
	if (t->unix_lock < 0) {
		/* thread_bind(t, -1); */
		t->whichq = &global_runq;
	}
}

void unix_reset()
{
	register thread_t	t = current_thread();

	if (t->unix_lock != -1)
		t->unix_lock = 0;
}

#endif	NCPUS > 1
