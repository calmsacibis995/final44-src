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
 * $Log:	kern_exit.c,v $
 * Revision 2.15  89/08/08  21:45:37  jsb
 * 	Made wait3 machine-independent again, as per mja wish.
 * 	Now someone else cleans their wait() ?
 * 	[89/07/22            af]
 * 
 * Revision 2.14  89/05/31  12:26:43  rvb
 * 	Floating Point Support. [af]
 * 
 * Revision 2.13  89/05/30  10:33:04  rvb
 * 	Cleaned up the wait business for mips.
 * 	[89/04/19            af]
 * 
 * Revision 2.12  89/04/22  15:20:19  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.11  89/03/09  19:28:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.10  89/02/25  14:28:15  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.9  89/02/09  04:31:00  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.8  89/01/23  22:03:29  af
 * 	Changes for MIPS: added wait and friends
 * 	[89/01/10            af]
 * 	
 * 	Changes for I386: i386 processor registers in wait
 * 	[89/01/09            rvb]
 * 
 * Revision 2.7  89/01/18  00:35:42  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.6  88/12/19  02:33:50  mwyoung
 * 	Removed old MACH conditionals.
 * 	[88/12/13            mwyoung]
 * 
 * Revision 2.5  88/08/24  01:18:58  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 * Revision 2.4  88/08/06  17:59:09  rpd
 * Eliminated use of kern/mach_ipc_defs.h.
 * 
 *  2-Jun-88  David Golub (dbg) at Carnegie-Mellon University
 *	Removed call to fpaclose_thread; it is done by thread_terminate
 *	(via pcb_terminate).
 *
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	MACH_TIME_NEW is now standard.
 *	Check p_stat when looking for stopped processes.
 * 
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Remove references to multprog.
 *
 *  2-Mar-88  David Black (dlb) at Carnegie-Mellon University
 *	Use thread_read_times to get times.  This replaces and
 *	generalizes the MACH_TIME_NEW code.
 *
 * 17-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added call to fpaclose_thread() in exit().
 *
 * 12-Feb-88  David Black (dlb) at Carnegie-Mellon University
 *	Update MACH_TIME_NEW interface to use time_value_t's.
 *
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 23-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Made exit halt all threads in task before cleaning up.
 *
 *  8-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Follow task_terminate with thread_halt_self for new termination
 *	logic.  Check for null p->task for Zombie check in wait.
 *
 * 21-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Condensed some conditionals, purged previous history.
 *
 * 19-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS: Change inode references to vnode references.
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  changed wait() to handle new WLOGINDEV option and
 *	slightly reorganized the ns32000 exit path to make it more
 *	common;  changed exit() to call new ttylogout() routine.
 *	[ V5.1(F1) ]
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added hooks for ITC/Andrew remote file system.
 *
 * 09-May-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over changes:
 *	CS_IPC:  Added call to IPCSuicide() in exit().
 *	CS_RFS:  Added call to rfs_exit() in exit().
 *	NILDR:  Added call to ildrrma() in exit().
 *	[V1(1)]
 *
 */
 
#include <cputypes.h>

#include <mach_rfs.h>
#include <quota.h>
#include <vice.h>
#include <ild.h>
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_exit.c	7.1 (Berkeley) 6/5/86
 */

#include <machine/reg.h>
#ifdef	ibmrt
#include <ca/scr.h>
#endif	ibmrt
#if	!defined(ibmrt) && !defined(mips)
#include <machine/psl.h>
#endif	!defined(ibmrt) && !defined(mips)

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/wait.h>
#include <sys/vm.h>
#include <sys/file.h>
#include <sys/mbuf.h>
#include <sys/inode.h>
#include <sys/syslog.h>

#include <mach/kern_return.h>
#include <kern/task.h>
#include <vm/vm_map.h>
#include <kern/thread.h>
#include <kern/parallel.h>
#include <kern/sched_prim.h>
#include <mach/time_value.h>

/*
 * Exit system call: pass back caller's arg
 */
rexit()
{
	register struct a {
		int	rval;
	} *uap;

	uap = (struct a *)u.u_ap;
	exit((uap->rval & 0377) << 8);
}

/*
 * Release resources.
 * Save u. area for parent to look at.
 * Enter zombie state.
 * Wake up parent and init processes,
 * and dispose of children.
 */
exit(rv)
	int rv;
{
	register int i;
	register struct proc *p, *q, *nq;
	register int x;
	struct mbuf *m = m_getclr(M_WAIT, MT_ZOMBIE);
	time_value_t		sys_time, user_time;
	register struct	timeval	*tvp;

#ifdef	PGINPROF
	vmsizmon();
#endif	PGINPROF
	p = u.u_procp;

	/*
	 *	Since exit can be called from psig or syscall, we have
	 *	to worry about the potential race.  sig_lock_to_exit
	 *	causes any thread in this task encountering a sig_lock
	 *	anywhere (including here) to immediately suspend permanently.
	 */
	if (current_thread() != p->exit_thread) {
	    sig_lock(p);
	    sig_lock_to_exit(p);
	}
	/*
	 *	Halt all threads in the task, except for the current
	 *	thread.
	 */
	(void) task_halt(current_task(), TRUE);

	/*
	 *	Set SWEXIT just to humor ps.
	 */
	p->p_flag &= ~(STRC|SULOCK);
	p->p_flag |= SWEXIT;
	p->p_sigignore = ~0;
	p->p_cpticks = 0;
	p->p_pctcpu = 0;
	for (i = 0; i < NSIG; i++)
		u.u_signal[i] = SIG_IGN;
	untimeout(realitexpire, (caddr_t)p);
	for (i = 0; i <= u.u_lastfile; i++) {
		struct file *f;

		f = u.u_ofile[i];
		if (f) {
			closef(f);
			u.u_ofile[i] = NULL;
		}
		u.u_pofile[i] = 0;
	}
#if	MACH_RFS
	/*  after closing all files ... */
	rfs_exit();
#endif	MACH_RFS
	ttylogout(p->p_logdev);
#if	VICE
	if (u.u_cdir) {
#endif	VICE
	LOCK_INODE(u.u_cdir);
	FINISH_WITH_INODE(u.u_cdir);
#if	VICE
	}
#endif	VICE
	if (u.u_rdir) {
		LOCK_INODE(u.u_rdir);
		FINISH_WITH_INODE(u.u_rdir);
	}
#if	VICE
	if (u.u_textfile)
	{
		closef(u.u_textfile);
		u.u_textfile = NULL;
	}
#endif	VICE
#if	NILD > 0
	/*
	 * remove outstanding ingres locks for
	 * the dying process
	 */
	ildrma(p->p_pid);
#endif	NILD
	u.u_rlimit[RLIMIT_FSIZE].rlim_cur = RLIM_INFINITY;
	acct();
	free_identity(u.u_identity);
#if	QUOTA
	qclean();
#endif	QUOTA
	if (*p->p_prev = p->p_nxt)		/* off allproc queue */
		p->p_nxt->p_prev = p->p_prev;
	if (p->p_nxt = zombproc)		/* onto zombproc */
		p->p_nxt->p_prev = &p->p_nxt;
	p->p_prev = &zombproc;
	zombproc = p;
	p->p_stat = SZOMB;
	i = PIDHASH(p->p_pid);
	x = p - proc;
	if (pidhash[i] == x)
		pidhash[i] = p->p_idhash;
	else {
		for (i = pidhash[i]; i != 0; i = proc[i].p_idhash)
			if (proc[i].p_idhash == x) {
				proc[i].p_idhash = p->p_idhash;
				goto done;
			}
		panic("exit");
	}
	if (p->p_pid == 1) {
		printf("init exited with %d\n", rv>>8);
		if (u.u_data_start == 0) {
			printf("Can't exec /etc/init\n");
			for (;;)
				;
		} else
			panic("init died");
	}
done:
	p->p_xstat = rv;
	/*
	 *	This is the current_thread.  Don't need to lock it.
	 */
	thread_read_times(current_thread(), &user_time, &sys_time);
	tvp = &u.u_ru.ru_utime;
	tvp->tv_sec = user_time.seconds;
	tvp->tv_usec = user_time.microseconds;
	tvp = &u.u_ru.ru_stime;
	tvp->tv_sec = sys_time.seconds;
	tvp->tv_usec = sys_time.microseconds;
	p->p_ru = mtod(m, struct rusage *);
	*p->p_ru = u.u_ru;
	ruadd(p->p_ru, &u.u_cru);
	if (p->p_cptr)		/* only need this if any child is S_ZOMB */
		wakeup((caddr_t)&proc[1]);
	for (q = p->p_cptr; q != NULL; q = nq) {
		nq = q->p_osptr;
		if (nq != NULL)
			nq->p_ysptr = NULL;
		if (proc[1].p_cptr)
			proc[1].p_cptr->p_ysptr = q;
		q->p_osptr = proc[1].p_cptr;
		q->p_ysptr = NULL;
		proc[1].p_cptr = q;

		q->p_pptr = &proc[1];
		q->p_ppid = 1;
		/*
		 * Traced processes are killed
		 * since their existence means someone is screwing up.
		 * Stopped processes are sent a hangup and a continue.
		 * This is designed to be ``safe'' for setuid
		 * processes since they must be willing to tolerate
		 * hangups anyways.
		 */
		if (q->p_flag&STRC) {
			q->p_flag &= ~STRC;
			psignal(q, SIGKILL);
		} else if ((q->task != TASK_NULL) &&
		    (q->task->user_stop_count > 0)) {
			psignal(q, SIGHUP);
			psignal(q, SIGCONT);
		}
		/*
		 * Protect this process from future
		 * tty signals, clear TSTP/TTIN/TTOU if pending.
		 */
		(void) spgrp(q);
	}
	p->p_cptr = NULL;
	psignal(p->p_pptr, SIGCHLD);
	wakeup((caddr_t)p->p_pptr);
	p->task = TASK_NULL;
	p->thread = THREAD_NULL;
	(void) task_terminate(current_task());
	thread_halt_self();
	/*NOTREACHED*/
}

#ifndef	mips

wait()
{
	/*
	 *  In order to address the "logged-in" terminal problem for window
	 *  managers, telnet servers, etc. which are not created initially by
	 *  init but which we want init to clean up after, we add the concept
	 *  of the "login device" associated with a process.  The login
	 *  program executes a special ioctl() call to distinguish the top
	 *  process in the tree and record the controlling device with which
	 *  it is associated.  The new wait3() option, WLOGINDEV, (used by
	 *  init) indicates that the returned resource usage record should
	 *  include the device number of the controlling terminal for the
	 *  top level process (this will be NODEV for any other process).
	 *  This way, init need not create terminal listeners for all
	 *  potential login terminals but can still know enough to clean
	 *  things up after such processes (which it has inherited) do exit.
	 */
	int options;
	struct rusage_dev ru, *rup;

#ifdef	multimax
	/*
	 *	All wait calls use the same interface.
	 */
	rup = (struct rusage_dev *)fuword(u.u_ar0[R1] + 8);
	u.u_error = wait3(options=fuword(u.u_ar0[R1] + 4), &ru);
#else	multimax

#ifdef	ibmrt
	if ((u.u_ar0[ICSCS] & ICSCS_HOKEY) != ICSCS_HOKEY)
#endif	ibmrt
#ifdef	balance
	if ((u.u_ar0[MODPSR] & (PSR_C<<PSRADJ)) == 0)
#endif	balance
#ifdef	vax
	if ((u.u_ar0[PS] & PSL_ALLCC) != PSL_ALLCC)
#endif	vax
#ifdef	sun
	if ((u.u_ar0[PS] & PSL_ALLCC) != PSL_ALLCC)
#endif	sun
#ifdef	i386
	if ((u.u_ar0[EFL] & EFL_ALLCC) != EFL_ALLCC)
#endif	i386
	{
		u.u_error = wait3(0, (struct rusage_dev *)0);
		return;
	}
#ifdef	ibmrt
	rup = (struct rusage_dev *)u.u_ar0[R4];	 /* as per C linkage */
	u.u_error = wait3(options=u.u_ar0[R3], &ru);     /* as per C linkage */
#endif	ibmrt
#ifdef	balance
	rup = (struct rusage_dev *)u.u_ar0[R2];
	u.u_error = wait3(options=u.u_ar0[R1], &ru);
#endif	balance
#ifdef	vax
	rup = (struct rusage_dev *)u.u_ar0[R1];
	u.u_error = wait3(options=u.u_ar0[R0], &ru);
#endif	vax
#ifdef	sun
	rup = (struct rusage_dev *)u.u_ar0[R1];
	u.u_error = wait3(options=u.u_ar0[R0], &ru);
#endif	sun
#ifdef	i386
	rup = (struct rusage_dev *)u.u_ar0[EDX];
	u.u_error = wait3(options=u.u_ar0[ECX], &ru);
#endif	i386
#endif	multimax

	if (u.u_error)
		return;
	if (rup != (struct rusage_dev *)0)
		u.u_error = copyout((caddr_t)&ru, (caddr_t)rup, 
			(options&WLOGINDEV)?sizeof(ru):sizeof(ru.ru_rusage));
}

#else	mips

wait()
{
	struct wait3 {
		union wait *status;	/* user supplied pointer */
		int options;		/* user supplied options */
		struct rusage_dev *ru;	/* user supplied pointer */
	} *uap = (struct wait3 *)u.u_ap;
	struct rusage_dev ru;
	register int error;

	error = wait3(uap->options, &ru);
	if (error)
		goto ret;
	if (uap->ru) {
		error = copyout((caddr_t)&ru, (caddr_t)uap->ru,
			(uap->options&WLOGINDEV)?
				sizeof(struct rusage_dev) :sizeof(struct rusage));
		if (error)
			goto ret;
	}
	if (uap->status != (union wait *)0)
		error = copyout((caddr_t)&u.u_r.r_val2,
			(caddr_t)uap->status, sizeof (union wait));
ret:
	u.u_error = error;
}

#endif	mips

/*
 * Wait system call.
 * Search for a terminated (zombie) child,
 * finally lay it to rest, and collect its status.
 * Look also for stopped (traced) children,
 * and pass back status from them.
 */
wait3(options, ru)
	register int options;
	struct rusage_dev *ru;
{
	register f;
	register struct proc *p, *q;

	f = 0;
loop:
	q = u.u_procp;
	for (p = q->p_cptr; p; p = p->p_osptr) {
		f++;
		if (p->task == TASK_NULL)
		{
			u.u_r.r_val1 = p->p_pid;
			u.u_r.r_val2 = p->p_xstat;
			p->p_xstat = 0;

			if (ru) {
			    if (p->p_ru)
				ru->ru_rusage = *p->p_ru;
			    ru->ru_dev = p->p_logdev;
			}
			if (p->p_ru) {
				ruadd(&u.u_cru, p->p_ru);
				(void) m_free(dtom(p->p_ru));
				p->p_ru = 0;
			}
			p->p_stat = NULL;
			p->p_pid = 0;
			p->p_ppid = 0;
			if (*p->p_prev = p->p_nxt)	/* off zombproc */
				p->p_nxt->p_prev = p->p_prev;
			p->p_nxt = freeproc;		/* onto freeproc */
			freeproc = p;
			if (q = p->p_ysptr)
				q->p_osptr = p->p_osptr;
			if (q = p->p_osptr)
				q->p_ysptr = p->p_ysptr;
			if ((q = p->p_pptr)->p_cptr == p)
				q->p_cptr = p->p_osptr;
			p->p_pptr = 0;
			p->p_ysptr = 0;
			p->p_osptr = 0;
			p->p_cptr = 0;
			p->p_sig = 0;
			p->p_sigcatch = 0;
			p->p_sigignore = 0;
			p->p_sigmask = 0;
			p->p_pgrp = 0;
			p->p_flag = 0;
			p->p_cursig = 0;
			return (0);
		}
		if (p->task->user_stop_count > 0 && p->p_stat == SSTOP &&
		    (p->p_flag&SWTED)==0 &&
		    (p->p_flag&STRC || options&WUNTRACED)) {
			p->p_flag |= SWTED;
			u.u_r.r_val1 = p->p_pid;
			/*
			 *	Stop-class signals are in p_stopsig instead
			 *	of p_cursig under some circumstances.
			 */
			if (p->p_cursig == 0)
				u.u_r.r_val2 = (p->p_stopsig<<8) | WSTOPPED;
			else
				u.u_r.r_val2 = (p->p_cursig<<8) | WSTOPPED;
			return (0);
		}
	}
	if (f == 0)
		return (ECHILD);
	if (options&WNOHANG) {
		u.u_r.r_val1 = 0;
		return (0);
	}
	if (setjmp(&u.u_qsave)) {
		p = u.u_procp;
		if ((u.u_sigintr & sigmask(p->p_cursig)) != 0)
			return(EINTR);
		u.u_eosys = RESTARTSYS;
		return (0);
	}
	sleep((caddr_t)u.u_procp, PWAIT);
	goto loop;
}

kern_return_t	init_process()
/*
 *	Make the current process an "init" process, meaning
 *	that it doesn't have a parent, and that it won't be
 *	gunned down by kill(-1, 0).
 */
{
	register struct proc *p;


	if (!suser())
		return(KERN_NO_ACCESS);

	unix_master();
	p = u.u_procp;

	/*
	 *	Take us out of the sibling chain, and
	 *	out of our parent's child chain.
	 */

	if (p->p_osptr)
		p->p_osptr->p_ysptr = p->p_ysptr;
	if (p->p_ysptr)
		p->p_ysptr->p_osptr = p->p_osptr;
	if (p->p_pptr->p_cptr == p)
		p->p_pptr->p_cptr = p->p_osptr;
	p->p_pptr = p;
	p->p_ysptr = p->p_osptr = 0;
	p->p_pgrp = p->p_pid;
	p->p_ppid = 0;

	unix_release();
	return(KERN_SUCCESS);
}
