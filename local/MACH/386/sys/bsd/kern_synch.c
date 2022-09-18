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
 * $Log:	kern_synch.c,v $
 * Revision 2.15  89/05/30  10:34:31  rvb
 * 	Eliminated unused filter() macro [leftover from BSD], and
 * 	with it all mips dependencies.
 * 	[89/05/15            af]
 * 
 * Revision 2.14  89/04/22  15:21:03  gm0w
 * 	Unconditionalized code to implement PCATCH flag in priority.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.13  89/04/05  12:55:11  rvb
 * 	Forward declaration of should_exit() as boolean_t.
 * 	[89/03/21            rvb]
 * 
 * Revision 2.12  89/03/09  19:29:06  rpd
 * 	More cleanup.
 * 
 * Revision 2.11  89/02/25  14:42:23  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.10  89/02/09  04:31:35  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.9  89/01/23  22:04:19  af
 * 	ccpu is no longer used for anyone ... except mips ??
 * 	[89/01/09            rvb]
 * 	
 * 	Added changes for Mips.  Basically, avoid floating point numbers.
 * 	[89/01/08            af]
 * 
 * Revision 2.8  89/01/18  00:37:38  jsb
 * 	NFS support: add wakeup_one.
 * 	SUN_RPC support: add PCATCH flag for sleep.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.7  89/01/15  16:17:38  rpd
 * 	Include <sys/callout.h> instead of declaring callout_lock by hand.
 * 	[89/01/15  14:48:15  rpd]
 * 
 * Revision 2.6  88/08/24  01:20:45  mwyoung
 * 	Corrected include file references.
 * 	[88/08/23  01:00:57  mwyoung]
 * 
 * Revision 2.5  88/07/17  17:24:32  mwyoung
 * Converted use of kernel_only to kernel_vm_space in schedcpu().
 * It's unclear that this is the best choice, but it's compatible.
 * 
 * Revision 2.3.1.1  88/06/28  20:16:26  mwyoung
 * Converted use of kernel_only to kernel_vm_space in schedcpu().
 * It's unclear that this is the best choice, but it's compatible.
 * 
 *
 * 21-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Converted use of kernel_only to kernel_vm_space in schedcpu().
 *	It's unclear that this is the best choice, but it's compatible.
 *
 * Revision 2.4  88/07/15  18:22:10  mja
 * Changed to include <sys/table.h> instead of <sys/syscalls.h> for
 * setmodes bit definitons.
 * 
 *  2-Jun-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: added missing check for UMODE_NONICE mode bit in schedcpu()
 *	to disable auto-nice mechanism.
 *	[ V5.1(XF27) ]
 *
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	MACH: Cleaned up conditionals in sleep().
 *	      Moved autonice code here from softclock().
 *	      No more SSLEEP state for P_STAT.
 *
 * 21-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Revised rpsleep() routine to support polled resource pause
 *	operation and moved continuation message display into new
 *	rpcont() routine.
 *	[ V5.1(XF23) ]
 *
 * 18-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Check for use of kernel_pmap to determine whether to (de,)activate.
 *
 * 26-Jan-88  David Black (dlb) at Carnegie-Mellon University
 *	Don't activate pmaps for kernel_only tasks.
 *
 * 21-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Reduced conditionals, purged history.
 *
 * 19-Aug-87  Peter King (king) at NeXT
 *	SUN_RPC: If PCATCH is set, sleep will return 1 rather than longjmp.
 *	MACH_NFS: Create wakeup_one that will only wakeup one process sleeping
 *		 on a channel.
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RPAUSE: Renamed rpause() to be rpsleep() since rpause()
 *	is now the system call used to enable/disable resource pausing;
 *
 * 03-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RPAUSE:  Added rpause() routine.
 *	[V1(1)]
 *
 * 10-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_COMPAT:  Redid tsleep() to use a private timeout()
 *	routine since piggybacking off the alarm (real interval) timer
 *	is no longer appropriate.
 *	[V1(1)]
 *
 * 15-May-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over changes below:
 *
 *	CS_COMPAT:  Carry over tsleep() routine from 4.1BSD.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_synch.c	7.1 (Berkeley) 6/5/86
 */

#include <cputypes.h>
#include <cpus.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/inode.h>
#include <sys/vm.h>
#include <sys/kernel.h>
#include <sys/buf.h>
#include <sys/table.h>


#include <sys/callout.h>
#include <kern/queue.h>
#include <kern/lock.h>
#include <kern/thread.h>
#include <kern/sched.h>
#include <kern/sched_prim.h>
#include <mach/machine.h>
#include <kern/parallel.h>

#include <machine/cpu.h>
#include <vm/pmap.h>
#include <vm/vm_kern.h>

#ifdef	vax
#include <vax/mtpr.h>	/* XXX */
#endif

#include <kern/task.h>
#include <mach/time_value.h>

/*
 * Recompute process priorities, once a second
 */
schedcpu()
{
	register thread_t th;

	wakeup((caddr_t)&lbolt);

	/*
	 *	Autonice code moved here from kern_clock.c
	 */
	th = current_thread();
	if (!(th->task->kernel_vm_space)) {
	    register struct proc *p;

	    p = u.u_procp;
	    if (p->p_uid && p->p_nice == NZERO &&
		(u.u_modes & UMODE_NONICE) == 0)
	    {
		time_value_t	user_time;

		timer_read(&(th->user_timer), &user_time);
		if (user_time.seconds > 10 * 60) {
		    register int	s;

		    p->p_nice = NZERO+4;
		    th->priority = BASEPRI_USER + 2*p->p_nice;
		    s = splsched();
		    thread_lock(th);
		    compute_my_priority(th);
		    thread_unlock(th);
		    splx(s);
		}
	    }
	}
	timeout(schedcpu, (caddr_t)0, hz);
}

/*
 * Give up the processor till a wakeup occurs
 * on chan, at which time the process
 * enters the scheduling queue at priority pri.
 * The most important effect of pri is that when
 * pri<=PZERO a signal cannot disturb the sleep;
 * if pri>PZERO signals will be processed.
 * If pri&PCATCH is set, signals will cause sleep
 * to return 1, rather than longjmp.
 * Callers of this routine must be prepared for
 * premature return, and check that the reason for
 * sleeping has gone away.
 */
int
sleep(chan, pri)
	caddr_t chan;
	int pri;
{
	register struct proc *rp;
	register s;

	rp = u.u_procp;
	s = splhigh();
	if (panicstr) {
		/*
		 * After a panic, just give interrupts a chance,
		 * then just return; don't run any other procs 
		 * or panic below, in case this is the idle process
		 * and already asleep.
		 * The splnet should be spl0 if the network was being used
		 * by the filesystem, but for now avoid network interrupts
		 * that might cause another panic.
		 */
		(void) splnet();
		splx(s);
		return(0);
	}
	rp->p_slptime = 0;
	rp->p_pri = pri & PMASK;
	assert_wait((int) chan, pri > PZERO);
	if (pri > PZERO) {
		/*
		 * If wakeup occurs while in issig, thread_block()
		 * below is a no-op.  If ISSIG finds a signal, clear
		 * sleep condition before going to process it.
		 */
		if (ISSIG(rp)) {
			clear_wait(current_thread(), THREAD_INTERRUPTED,
					TRUE);
			(void) spl0();
			goto psig;
		}
		(void) spl0();
		u.u_ru.ru_nvcsw++;
		if (cpu_number() != master_cpu) {
			printf("unix sleep: on slave?");
		}
		thread_block();
		if (ISSIG(rp))
			goto psig;
	} else {
		(void) spl0();
		u.u_ru.ru_nvcsw++;
		if (cpu_number() != master_cpu) {
			printf("unix sleep: on slave?");
		}
		thread_block();
	}
	splx(s);
	return(0);

	/*
	 * If priority was low (>PZERO) and
	 * there has been a signal, execute non-local goto through
	 * u.u_qsave, aborting the system call in progress (see trap.c),
	 * unless PCATCH is set, in which case we just return 1 so our
	 * caller can release resources and unwind the system call,
	 * or finishing a tsleep (see below).
	 */
psig:
	if (pri & PCATCH)
		return(1);
	longjmp(&u.u_qsave);
	/*NOTREACHED*/
}

/* 
 *  rpsleep - perform a resource pause sleep
 *
 *  rsleep = function to perform resource specific sleep
 *  arg1   = first function parameter
 *  arg2   = second function parameter
 *  mesg1  = first component of user pause message
 *  mesg2  = second component of user pause message
 *
 *  Display the appropriate pause message on the user's controlling terminal.
 *  Save the current non-local goto information and establish a new return
 *  environment to transfer here.  Invoke the supplied function to sleep
 *  (possibly interruptably) until the resource becomes available.  When the
 *  sleep finishes (either normally or abnormally via a non-local goto caused
 *  by a signal), restore the old return environment and display a resume
 *  message on the terminal.  The notify flag bit is set when the pause message
 *  is first printed.  If it is cleared on return from the function, the
 *  continue message is printed here.  If not, this bit will remain set for the
 *  duration of the polling process and the rpcont() routine will be called
 *  directly from the poller when the resource pause condition is no longer
 *  pending.
 *
 *  Return: true if the resource has now become available, or false if the wait
 *  was interrupted by a signal.
 */

boolean_t
rpsleep(rsleep, arg1, arg2, mesg1, mesg2)
int (*rsleep)();
int arg1;
int arg2;
char *mesg1;
char *mesg2;
{
    label_t lsave;
    boolean_t ret = TRUE;

    if ((u.u_rpswhich&URPW_NOTIFY) == 0)
    {
        u.u_rpswhich |= URPW_NOTIFY;
	uprintf("[%s: %s%s, pausing ...]\r\n", u.u_comm, mesg1, mesg2);
    }
    
    bcopy((caddr_t)&u.u_qsave, (caddr_t)&lsave, sizeof(lsave));
    if (setjmp(&u.u_qsave) == 0)
	(*rsleep)(arg1, arg2);
    else
	ret = FALSE;
    bcopy((caddr_t)&lsave, (caddr_t)&u.u_qsave, sizeof(lsave));

    if ((u.u_rpswhich&URPW_NOTIFY) == 0)
	rpcont();
    return(ret);
}
 
 
 
/* 
 *  rpcont - continue from resource pause sleep
 *
 *  Clear the notify flag and print the continuation message on the controlling
 *  terminal.  When this routine is called, the resource pause condition is no
 *  longer pending and we can afford to clear all bits since only the notify
 *  bit should be set to begin with.
 */

rpcont()
{
    u.u_rpswhich = 0;
    uprintf("[%s: ... continuing]\r\n", u.u_comm);
}

/* 
 * Sleep on chan at pri.
 * Return in no more than the indicated number of seconds.
 * (If seconds==0, no timeout implied)
 * Return	TS_OK if chan was awakened normally
 *		TS_TIME if timeout occurred
 *		TS_SIG if asynchronous signal occurred
 */


tsleep(chan, pri, seconds)
	caddr_t	chan;
{
 	struct timeval when;
	int	s;
	register struct proc *p = u.u_procp;

	s = splhigh();
	assert_wait((int)chan, pri > PZERO);
	if (seconds) {
		when = time;
		when.tv_sec += seconds;
		thread_set_timeout(hzto(&when));
	}
	if (pri > PZERO) {
		if (ISSIG(p)) {
			clear_wait(current_thread(), THREAD_INTERRUPTED, TRUE);
			splx(s);
			return (TS_SIG);
		}
		thread_block();
		if (ISSIG(p)) {
			splx(s);
			return (TS_SIG);
		}
	}
	else {
		thread_block();
	}
	if (current_thread()->wait_result == THREAD_TIMED_OUT) {
		splx(s);
		return(TS_TIME);
	}
	splx(s);
	return(TS_OK);
}


/*
 * Wake up all processes sleeping on chan.
 */
wakeup(chan)
	register caddr_t chan;
{
	int s;

	s = splhigh();
	thread_wakeup((int) chan);
	splx(s);
}

/*
 * Wake up the first process sleeping on chan.
 *
 * Be very sure that the first process is really
 * the right one to wakeup.
 */
wakeup_one(chan)
	register caddr_t chan;
{
	int s;

	s = splhigh();
	thread_wakeup_one((int) chan);
	splx(s);
}

/*
 * Initialize the (doubly-linked) run queues
 * to be empty.
 */
rqinit()
{
	register int i;

	for (i = 0; i < NQS; i++)
		qs[i].ph_link = qs[i].ph_rlink = (struct proc *)&qs[i];
	simple_lock_init(&callout_lock);
}

slave_start()
{
	register struct thread	*th;
	register int		mycpu;
	extern 	boolean_t	should_exit[];

	/*	Find a thread to execute */

	mycpu = cpu_number();

	splhigh();
	th = choose_thread();
	if (th == NULL) {
		printf("Slave %d failed to find any threads.\n", mycpu);
		printf("Should have at least found idle thread.\n");
		halt_cpu();
	}

	/*
	 *	Show that this cpu is using the kernel pmap
	 */
	PMAP_ACTIVATE(kernel_pmap, th, mycpu);

	active_threads[mycpu] = th;

	if (vm_map_pmap(th->task->map) != kernel_pmap) {
		PMAP_ACTIVATE(vm_map_pmap(th->task->map), th, mycpu);
	}

	/*
	 *	Clock interrupt requires that this cpu have an active
	 *	thread, hence it can't be done before this.
	 */
	startrtclock();
	load_context(th);
	/*NOTREACHED*/
}
