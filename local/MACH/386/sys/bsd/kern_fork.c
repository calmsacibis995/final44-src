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
 * $Log:	kern_fork.c,v $
 * Revision 2.11  89/05/30  10:33:23  rvb
 * 	Removed include of psl.h for mips too.
 * 	[89/05/15            af]
 * 
 * Revision 2.10  89/04/22  15:20:27  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.9  89/03/15  15:03:26  gm0w
 * 	Added code to newproc to save a pointer to the utask structure
 * 	in the proc structure.
 * 	[89/03/15            mrt]
 * 
 * Revision 2.8  89/03/09  19:28:30  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  14:28:22  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:31:04  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  89/01/18  00:36:04  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.4  88/08/24  01:19:51  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	Set p_stat to SRUN before resuming child.
 *
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Remove references to multprog.
 *
 * 19-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Copy controlling tty fields to new proc structures in
 *	newproc().
 *	[ V5.1(XF23) ]
 *
 * 30-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 15-Dec-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Deleted #ifdef ibmrt call to float_fork().
 *
 * 21-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Cleaned up some conditionals.  Deleted old history.
 *
 * 19-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS: Convert from inode usage to vnode usage.
 *		 Don't propigate file-descriptor-oriented locks.
 *		 Add credentials as info to be duplicated.
 *
 * 28-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  updated newproc() to avoid propagating new
 *	p_logdev field in child process; made MAXUPRC reference the new
 *	field in the U area rather than the old global variable.
 *	[ V5.1(F1) ]
 *
 * 12-Dec-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	MACH:  nothing mysterious about the reappearance of
 *	pte.h; it is only unnecessary under MACH; back one more
 *	time...
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added hooks for ITC/Andrew remote file system.
 *
 * 08-May-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS: split RFS hooks into two calls: rfs_newproc() from
 *	parent context in newproc() and rfs_fork from child context in
 *	fork().
 *
 * 26-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Added hook to inform remote system call handler about
 *	a new process in case the current process is using any remote
 *	objects which must be duplicated.
 *	CMUCS:  Fixed to also replicate execute only bit across
 *	fork().
 *	[V1(1)]
 *
 * 10-May-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Carried over changes below [V1(1)].
 *
 * 19-Feb-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Changed inode reference count modifications to use
 *	incr/decr macros to check for consistency (V3.04c).
 *
 */
 
#include <cputypes.h>

#include <mach_rfs.h>
#include <quota.h>
#include <vice.h>
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_fork.c	7.1 (Berkeley) 6/5/86
 */

#include <machine/reg.h>
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
#include <sys/inode.h>
#include <sys/vm.h>
#include <sys/file.h>
#include <sys/acct.h>
#include <sys/quota.h>
#include <kern/thread.h>

#undef	MAXUPRC
#define MAXUPRC		u.u_maxuprc

thread_t	newproc(), procdup();

/*
 * fork system call.
 */
fork()
{
	fork1(0);
}

vfork()
{
	fork1(1);
}

fork1(isvfork)
	int isvfork;
{
	register struct proc *p1, *p2;
	register a;
	thread_t	th = THREAD_NULL;

	a = 0;
	if (u.u_uid != 0) {
		for (p1 = allproc; p1; p1 = p1->p_nxt)
			if (p1->p_uid == u.u_uid)
				a++;
		for (p1 = zombproc; p1; p1 = p1->p_nxt)
			if (p1->p_uid == u.u_uid)
				a++;
	}
	/*
	 * Disallow if
	 *  No processes at all;
	 *  not su and too many procs owned; or
	 *  not su and would take last slot.
	 */
	p2 = freeproc;
	if (p2==NULL)
		tablefull("proc");
	if (p2==NULL || (u.u_uid!=0 && (p2->p_nxt == NULL || a>MAXUPRC))) {
		u.u_error = EAGAIN;
		goto out;
	}
	p1 = u.u_procp;
	th = newproc(isvfork);
	thread_dup(current_thread(), th);
	th->u_address.uthread->uu_r.r_val1 = p1->p_pid;
	th->u_address.uthread->uu_r.r_val2 = 1;	/* child */
	th->u_address.utask->uu_start = time;
	th->u_address.utask->uu_acflag = AFORK;
#if	MACH_RFS
	{
#ifdef	balance
#include <sqt/lmc.h>
#include <sqt/hwparam.h>
#endif	balance
		struct utask	*usave1;
		struct uthread	 *usave2;

		usave1 = u.utask;
		usave2 = u.uthread;
#ifdef	balance
		((struct lm *)VA_PRIVRAM)->lm_u_address_thread = th->u_address.uthread;
		((struct lm *)VA_PRIVRAM)->lm_u_address_task = th->u_address.utask;
#else	balance
		u.utask = th->u_address.utask;
		u.uthread = th->u_address.uthread;
#endif	balance
		rfs_fork();
#if	balance
		((struct lm *)VA_PRIVRAM)->lm_u_address_thread = usave2;
		((struct lm *)VA_PRIVRAM)->lm_u_address_task = usave1;
#else	balance
		u.utask = usave1;
		u.uthread = usave2;
#endif	balance
	}
#endif	MACH_RFS
	u.u_r.r_val1 = p2->p_pid;

	(void) thread_resume(th);
out:
	u.u_r.r_val2 = 0;

}

/*
 * Create a new process-- the internal version of
 * sys fork.
 * It returns 1 in the new process, 0 in the old.
 */
thread_t newproc(isvfork)
	int isvfork;
{
	register struct proc *rpp, *rip;
	register int n;
	register struct file *fp;
	static int pidchecked = 0;
	thread_t	th;

	/*
	 * First, just locate a slot for a process
	 * and copy the useful info from this process into it.
	 * The panic "cannot happen" because fork has already
	 * checked for the existence of a slot.
	 */
	mpid++;
retry:
	if (mpid >= 30000) {
		mpid = 100;
		pidchecked = 0;
	}
	if (mpid >= pidchecked) {
		int doingzomb = 0;

		pidchecked = 30000;
		/*
		 * Scan the proc table to check whether this pid
		 * is in use.  Remember the lowest pid that's greater
		 * than mpid, so we can avoid checking for a while.
		 */
		rpp = allproc;
again:
		for (; rpp != NULL; rpp = rpp->p_nxt) {
			if (rpp->p_pid == mpid || rpp->p_pgrp == mpid) {
				mpid++;
				if (mpid >= pidchecked)
					goto retry;
			}
			if (rpp->p_pid > mpid && pidchecked > rpp->p_pid)
				pidchecked = rpp->p_pid;
			if (rpp->p_pgrp > mpid && pidchecked > rpp->p_pgrp)
				pidchecked = rpp->p_pgrp;
		}
		if (!doingzomb) {
			doingzomb = 1;
			rpp = zombproc;
			goto again;
		}
	}
	if ((rpp = freeproc) == NULL)
		panic("no procs");

	freeproc = rpp->p_nxt;			/* off freeproc */

	/*
	 * Make a proc table entry for the new process.
	 */
	rip = u.u_procp;
#if	QUOTA
	rpp->p_quota = rip->p_quota;
	rpp->p_quota->q_cnt++;
#endif	QUOTA
	rpp->p_stat = SIDL;
	timerclear(&rpp->p_realtimer.it_value);
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGI|SOUSIG|SXONLY));
	rpp->p_ttyd = rip->p_ttyd;
	rpp->p_ttyp = rip->p_ttyp;
	rpp->p_ndx = rpp - proc;
	rpp->p_uid = rip->p_uid;
	rpp->p_pgrp = rip->p_pgrp;
	rpp->p_nice = rip->p_nice;
	rpp->p_pid = mpid;
	rpp->p_ppid = rip->p_pid;
	rpp->p_pptr = rip;
	rpp->p_osptr = rip->p_cptr;
	if (rip->p_cptr)
		rip->p_cptr->p_ysptr = rpp;
	rpp->p_ysptr = NULL;
	rpp->p_cptr = NULL;
	rip->p_cptr = rpp;
	rpp->p_time = 0;
	rpp->p_cpu = 0;
	rpp->p_sigmask = rip->p_sigmask;
	rpp->p_sigcatch = rip->p_sigcatch;
	rpp->p_sigignore = rip->p_sigignore;
	/* take along any pending signals like stops? */
	rpp->p_rssize = 0;
	rpp->p_maxrss = rip->p_maxrss;
	rpp->p_slptime = 0;
	rpp->p_pctcpu = 0;
	rpp->p_cpticks = 0;
	rpp->p_logdev = NODEV;
#ifdef	balance
	save_fpu();		/* inherit FPU context across fork() */
#endif	balance
	n = PIDHASH(rpp->p_pid);
	rpp->p_idhash = pidhash[n];
	pidhash[n] = rpp - proc;

	/*
	 * Increase reference counts on shared objects.
	 */
	for (n = 0; n <= u.u_lastfile; n++) {
		fp = u.u_ofile[n];
		if (fp == NULL)
			continue;
		fp->f_count++;
	}
	if (u.u_cdir)
		INCR_INODE(u.u_cdir);
	if (u.u_rdir)
		INCR_INODE(u.u_rdir);
	u.u_identity->id_ref++;
#if	VICE
	if (u.u_textfile)
		u.u_textfile->f_count++;
#endif	VICE

	/*
	 * This begins the section where we must prevent the parent
	 * from being swapped.
	 */
	rip->p_flag |= SKEEP;
#if	MACH_RFS
	/*
	 *  Notify the remote file system module that a new process is being
	 *  created.
	 */
	rfs_newproc(rpp, isvfork);
#endif	MACH_RFS
	simple_lock_init(&rpp->siglock);
	rpp->sigwait = FALSE;
	rpp->exit_thread = THREAD_NULL;
	th = procdup(rpp, rip);	/* child, parent */
	uarea_init(th);		/* this shouldn't be necessary here XXX */
	rpp->utask = th->u_address.utask;

	/*
	 *	It is now safe to link onto allproc
	 */
	rpp->p_nxt = allproc;			/* onto allproc */
	rpp->p_nxt->p_prev = &rpp->p_nxt;	/*   (allproc is never NULL) */
	rpp->p_prev = &allproc;
	allproc = rpp;
	rpp->p_stat = SRUN;			/* XXX */
	(void) spl0();

	/*
	 * Cause child to take a non-local goto as soon as it runs.
	 * On older systems this was done with SSWAP bit in proc
	 * table; on VAX we use u.u_pcb.pcb_sswap so don't need
	 * to do rpp->p_flag |= SSWAP.  Actually do nothing here.
	 */
	/* rpp->p_flag |= SSWAP; */

	/*
	 * Now can be swapped.
	 */
	rip->p_flag &= ~SKEEP;


	return(th);
}

uarea_init(th)
	register thread_t	th;
{
	th->u_address.uthread->uu_ap = th->u_address.uthread->uu_arg;
	th->u_address.uthread->uu_nd.ni_iov = &th->u_address.uthread->uu_nd.ni_iovec;
}

uarea_zero(th)
	thread_t	th;
{
	bzero((caddr_t) th->u_address.uthread, sizeof(struct uthread));
}
