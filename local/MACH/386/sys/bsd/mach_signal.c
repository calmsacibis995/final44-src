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
 * $Log:	mach_signal.c,v $
 * Revision 2.4  89/03/09  19:29:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  14:42:59  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/02/09  04:31:57  mwyoung
 * Code cleanup cataclysm.
 * 
 *  1-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	Created by cutting down psignal to only deal with exceptions.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <kern/sched.h>
#include <kern/task.h>
#include <kern/thread.h>

/*
 * Send the specified exception signal to the specified thread.
 *
 * NOTE: unlike its full-blown counterpart, this is completely parallel!
 */
thread_psignal(sig_thread, sig)
	register thread_t	sig_thread;
	register int sig;
{
	register struct proc *p;
	register task_t		sig_task;
	int mask;

	if ((unsigned)sig > NSIG)
		return;

	mask = sigmask(sig);
	if ( (mask & threadmask) == 0) {
		printf("signal = %d\n");
		panic("thread_psignal: signal is not an exception!");
	}

	sig_task = sig_thread->task;
	p = &proc[sig_task->proc_index];

	/*
	 *	Forget ignored signals UNLESS process is being traced. (XXX)
	 */
	if ((p->p_sigignore & mask) && (p->p_flag & STRC) == 0 )
		return;

	/*
	 *	This is an exception signal - deliver directly to thread.
	 */
	sig_lock_simple(p);
	sig_thread->u_address.uthread->uu_sig |= mask;
	sig_unlock(p);
}
