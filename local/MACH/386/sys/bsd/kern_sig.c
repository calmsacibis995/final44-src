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
 * $Log:	kern_sig.c,v $
 * Revision 2.21.3.1  90/02/28  15:45:59  rvb
 * 	Get rid of ifdef's that turned off pcb_synch for i386. [kupfer]
 * 	Use UIO_*SPACE constants for calls to rdwri(). [kupfer]
 * 
 * Revision 2.21  89/08/08  21:45:45  jsb
 * 	Fixed core() not to overwrite the fake_u for mips, after
 * 	the kernel stack size was increased to 8k.
 * 	Zero the fake_uarea before writing it out.
 * 	Cleanups.
 * 	[89/07/24            af]
 * 
 * Revision 2.20  89/07/14  15:34:43  rvb
 * 	I386: New Signal Handling from Olivetti.
 * 	PMAX: FLush "hideous bug" debugging for 
 * 	[89/07/10            rvb]
 * 
 * Revision 2.19  89/05/31  12:26:56  rvb
 * 	mips: turn of "hideous bug" debugging. [af]
 * 
 * Revision 2.18  89/05/30  10:34:04  rvb
 * 	Fixed the SWITCH_INT thing: only the object you
 * 	switch on needs to be recasted, NOT the individual "case foo"
 * 	entries. [Next time make sure you test your code, tx]
 * 
 * Revision 2.17  89/04/22  15:20:51  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.16  89/04/18  16:42:12  mwyoung
 * 	Pick up issig() fix from dlb/avie to avoid signal action on
 * 	system processes, as the comment said.
 * 	[89/04/16            mwyoung]
 * 
 * Revision 2.15  89/03/10  01:27:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.14  89/03/04  17:09:44  rpd
 * 	i386 needs SWITCH_INT true
 * 	[89/03/01            rvb]
 * 
 * Revision 2.13  89/02/27  21:03:04  mrt
 * 	Removed include of sys/seg.h
 * 	[89/02/27            mrt]
 * 	dlb version
 * 	[89/02/26  18:37:28  mrt]
 * 
 * Revision 2.11  89/02/09  04:31:24  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.10  89/01/23  22:03:55  af
 * 	Changes for I386: no pcb_synch() and some bizarre code I
 * 	 don't understand in sigvec
 * 	[89/01/09            rvb]
 * 	
 * 	Added changes for Mips.
 * 	Also solved a religious issue about  SIG_DFL and friends, e.g.
 * 	whether a switch statement should accept a type of (int (*)()).
 * 	The chosen solution seems to go against ANSI C, but makes
 * 	everybody happy on a bitchy issue.
 * 	[89/01/04            af]
 * 
 * Revision 2.9.1.3  89/02/07  00:22:07  dlb
 * 	Prevent internal tasks from taking signals.
 * 	Fix religious issue regarding switch statments so that each
 * 	compiler can have it its own way.  XXX What a mess!!
 * 	[89/02/01            dlb]
 * 
 * Revision 2.9.1.2  89/01/31  20:12:44  dlb
 *	Changes for I386: no pcb_synch() and some bizarre code I
 *	don't understand in sigvec
 * 	[89/01/09            rvb]
 * 	
 * 	Added changes for Mips.
 * 	Also solved a religious issue about  SIG_DFL and friends, e.g.
 * 	whether a switch statement should accept a type of (int (*)()).
 * 	The chosen solution seems to go against ANSI C, but makes
 * 	everybody happy on a bitchy issue.
 * 	[89/01/04            af]
 * 
 * Revision 2.9.1.1  89/01/30  15:12:32  dlb
 * 	MACH_HOST: SIGKILL may reassign thread to default pset.
 * 	[88/11/04            dlb]
 * 	
 * 	Pass thread to thread_should_halt().
 * 	[88/08/11            dlb]
 * 
 * Revision 2.9  89/01/18  14:59:13  jsb
 * 	Re-remove old MACH conditionals which were accidently merged back in.
 * 
 * Revision 2.8  89/01/18  00:37:12  jsb
 * 	Vnode support (for core).
 * 	[89/01/13            jsb]
 * 
 * Revision 2.7  89/01/04  13:32:08  rpd
 * 	Don't resource-pause when core-dumping.
 * 	[88/12/31  14:53:32  rpd]
 * 
 * Revision 2.6  88/12/19  02:34:06  mwyoung
 * 	Remove lint.
 * 	[88/12/17            mwyoung]
 * 	
 * 	Removed old MACH conditionals.
 * 	[88/12/13            mwyoung]
 * 
 * Revision 2.5  88/08/22  21:24:02  mja
 * 	Clear any pending resource pause notification message in psig()
 * 	before processing a signal.
 * 	[88/08/08  14:31:03  mja]
 * 
 *  4-May-88  David Black (dlb) at Carnegie-Mellon University
 *	MACH: No more SSLEEP.
 *
 * 20-Apr-88  David Black (dlb) at Carnegie-Mellon University
 *	Allow exception signals to be used as back-door ipc.  (XXX)
 *
 * 29-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH: Include "machine/vmparam.h" rather than "sys/vm.h" to get
 *	USRSTACK declaration.
 *
 * 15-Jan-88  David Golub (dbg) at Carnegie-Mellon University
 *	Call task_suspend_nowait from interrupt level.
 *
 * 29-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	issig() and psig() no longer need to switch to/from master; they
 *	are always called when already on master CPU.  (Besides that, there
 *	is no unix_release() in the return path of sig_lock!)
 *
 * 21-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Better sig_lock; and completely set signal state before calling
 *	sendsig().
 *
 * 21-Nov-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Cleaned up conditionals (whew!).  Purged history.  Conditionals
 *	could probably be further reduced.
 *
 * 17-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	VICE:  Fix from Jay Kistler to only avoid core dumps during
 *	system calls when the current directory is remote.
 *	[ V5.1(F7) ]
 *
 * 21-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  enabled core dumping in remote (Andrew) directories.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added handling of SRMT flag to prevent ITC/Andrew
 *	remote syscall from getting screwed up.
 *
 * 21-May-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.  Carried over changes below:
 *
 *	CMUCS:  Change current user and group to real user and group
 *	before creating core file;  No core dump if execute-only.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_sig.c	7.1 (Berkeley) 6/5/86
 */

#include <cputypes.h>
#include <vice.h>

#include <machine/reg.h>
#if	defined(vax) || defined(sun) || defined(i386)
#include <machine/psl.h>
#endif	defined(vax) || defined(sun) || defined(i386)

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/mount.h>
#include <machine/vmparam.h>	/* Get USRSTACK */
#include <sys/acct.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <kern/sched.h>
#include <mach/vm_param.h>
#include <kern/thread.h>
#include <kern/parallel.h>
#include <machine/cpu.h>
#include <kern/sched_prim.h>
#include <kern/task.h>

#if	VICE
#include <sys/file.h>
#endif	VICE

#ifdef	multimax
#include <mmax/mmax_ptrace.h>
#endif	multimax

#define cantmask	(sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP))
#define stopsigmask	(sigmask(SIGSTOP)|sigmask(SIGTSTP)| \
			sigmask(SIGTTIN)|sigmask(SIGTTOU))

/*
 *	XXX Some ancient code in this file contains a statement that
 *	XXX different compilers want written differently.  Add your machine
 *	XXX to the following #if if its compiler insists that the argument
 *	XXX to switch and all of its cases be integers.  If your compiler
 *	XXX doesn't mind using function pointers that happen to be small
 *	XXX integers, then this doesn't concern you.
 */
#if	defined(vax) || defined(mips) || defined(NeXT) || defined(sequent) || defined(multimax) || defined(__GNU__) || defined(i386)
#define SWITCH_INT	1
#else	
#define SWITCH_INT	0
#endif

/*
 * Generalized interface signal handler.
 */
sigvec()
{
	register struct a {
		int	signo;
		struct	sigvec *nsv;
		struct	sigvec *osv;
#if	defined(balance) || defined(mips)
		int	(*sigtramp)();		/* signal trampoline code */
#endif	defined(balance) || defined(mips)
	} *uap = (struct a  *)u.u_ap;
	struct sigvec vec;
	register struct sigvec *sv;
	register int sig;
	int bit;
#ifdef	i386
	u.u_sigreturn = (int (*)())u.u_ar0[EDX];
#endif	i386

	sig = uap->signo;
#ifdef	multimax
	/*
	 * On the MMax the u area is not visible to the user tasks,
	 * therefore, the task must declare the address of its
	 * trampoline code before it attempts to catch signals.
	 * This is done by using the special signal SIGCATCHALL
	 */
	/* If this is the intermediate signal catcher then set it. */
	if (sig == SIGCATCHALL) {

		/* Copy the uap->nsv structure from user space to system
		 *	space.  Then set the return value and the signal
		 *	catcher.
		 */
		u.u_error = 
			copyin ((caddr_t)uap->nsv, (caddr_t)&vec, sizeof(vec));
		if (u.u_error)
			return;
		u.u_r.r_val1 = (int)u.u_sigcatch;
		u.u_sigcatch = vec.sv_handler;
		return;
	}
#endif	multimax
	if (sig <= 0 || sig > NSIG || sig == SIGKILL || sig == SIGSTOP) {
		u.u_error = EINVAL;
		return;
	}
	sv = &vec;
	if (uap->osv) {
		sv->sv_handler = u.u_signal[sig];
		sv->sv_mask = u.u_sigmask[sig];
		bit = sigmask(sig);
		sv->sv_flags = 0;
		if ((u.u_sigonstack & bit) != 0)
			sv->sv_flags |= SV_ONSTACK;
		if ((u.u_sigintr & bit) != 0)
			sv->sv_flags |= SV_INTERRUPT;
		u.u_error =
		    copyout((caddr_t)sv, (caddr_t)uap->osv, sizeof (vec));
		if (u.u_error)
			return;
	}
	if (uap->nsv) {
		u.u_error =
		    copyin((caddr_t)uap->nsv, (caddr_t)sv, sizeof (vec));
		if (u.u_error)
			return;
		if (sig == SIGCONT && sv->sv_handler == SIG_IGN) {
			u.u_error = EINVAL;
			return;
		}
#ifdef	mips
		/*
		 * check for unaligned pc on sighandler
		 */
		if (sv->sv_handler != SIG_IGN
		    && ((int)sv->sv_handler & (sizeof(int)-1))) {
			u.u_error = EINVAL;
			return;
		}
#endif	mips
		if ((sig == SIGMSG) || (sig == SIGEMSG)) {
			task_t		me = current_task();
			me->ipc_intr_msg = TRUE;
		}
		setsigvec(sig, sv);
#if	defined(balance) || defined(mips)
		/*
		 * On the Sequent Balance and Mips, struct user isn't
		 * visible to the executing thread; thus the trampoline
		 * code pointer is explicitly passed in when setting
		 * a signal handler.
		 */
		u.u_sigtramp = uap->sigtramp;
#endif	defined(balance) || defined(mips)
	}
}

setsigvec(sig, sv)
	int sig;
	register struct sigvec *sv;
{
	register struct proc *p;
	register int bit;

	bit = sigmask(sig);
	p = u.u_procp;
	/*
	 * Change setting atomically.
	 */
	(void) splhigh();
	sig_lock_simple(p);
	u.u_signal[sig] = sv->sv_handler;
	u.u_sigmask[sig] = sv->sv_mask &~ cantmask;

	if (sv->sv_flags & SV_INTERRUPT)
		u.u_sigintr |= bit;
	else
		u.u_sigintr &= ~bit;
	if (sv->sv_flags & SV_ONSTACK)
		u.u_sigonstack |= bit;
	else
		u.u_sigonstack &= ~bit;
	if (sv->sv_handler == SIG_IGN) {
		p->p_sig &= ~bit;		/* never to be seen again */
		/*
		 *	If this is a thread signal, clean out the
		 *	threads as well.
		 */
		if (bit & threadmask) {
			register	queue_head_t	*list;
			register	thread_t	thread;

			list = &(p->task->thread_list);
			task_lock(p->task);
			thread = (thread_t) queue_first(list);
			while (!queue_end(list, (queue_entry_t) thread)) {
				thread->u_address.uthread->uu_sig &= ~bit;
				thread = (thread_t)
					queue_next(&thread->thread_list);
			}
			task_unlock(p->task);
		}
		p->p_sigignore |= bit;
		p->p_sigcatch &= ~bit;
	} else {
		p->p_sigignore &= ~bit;
		if (sv->sv_handler == SIG_DFL)
			p->p_sigcatch &= ~bit;
		else
			p->p_sigcatch |= bit;
	}
	sig_unlock(p);
	(void) spl0();
}

sigblock()
{
	struct a {
		int	mask;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;

	(void) splhigh();
	u.u_r.r_val1 = p->p_sigmask;
	p->p_sigmask |= uap->mask &~ cantmask;
	(void) spl0();
}

sigsetmask()
{
	struct a {
		int	mask;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;

	(void) splhigh();
	u.u_r.r_val1 = p->p_sigmask;
	p->p_sigmask = uap->mask &~ cantmask;
	(void) spl0();
}

sigpause()
{
	struct a {
		int	mask;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;

	/*
	 * When returning from sigpause, we want
	 * the old mask to be restored after the
	 * signal handler has finished.  Thus, we
	 * save it here and mark the proc structure
	 * to indicate this (should be in u.).
	 */
	u.u_oldmask = p->p_sigmask;
	p->p_flag |= SOMASK;
	p->p_sigmask = uap->mask &~ cantmask;
	for (;;)
		sleep((caddr_t)&u, PSLEP);
	/*NOTREACHED*/
}
#undef cantmask

sigstack()
{
	register struct a {
		struct	sigstack *nss;
		struct	sigstack *oss;
	} *uap = (struct a *)u.u_ap;
	struct sigstack ss;

	if (uap->oss) {
		u.u_error = copyout((caddr_t)&u.u_sigstack, (caddr_t)uap->oss, 
		    sizeof (struct sigstack));
		if (u.u_error)
			return;
	}
	if (uap->nss) {
		u.u_error =
		    copyin((caddr_t)uap->nss, (caddr_t)&ss, sizeof (ss));
		if (u.u_error == 0)
			u.u_sigstack = ss;
	}
}

kill()
{
	register struct a {
		int	pid;
		int	signo;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p;

	if (uap->signo < 0 || uap->signo > NSIG) {
#ifdef	balance
		/*
		 * Special case of init doing `kill(1, LEGAL_USER|nusers)' is
		 * a hook telling system "/etc/init" is the *REAL* one
		 * (and passing back number of users).  This is only
		 * necessary if running DYNIX /etc/init.
		 */
#define LEGAL_MAGIC (0x12210000)
		if ((uap->signo & 0xffff0000) == LEGAL_MAGIC) {
			if (uap->pid == 1 && u.u_procp == &proc[1]) {
				extern unsigned sec0eaddr;
				sec0eaddr = uap->signo & 0xffff;
			}
		}
#endif	balance
		u.u_error = EINVAL;
		return;
	}
	if (uap->pid > 0) {
		/* kill single process */
		p = pfind(uap->pid);
		if (p == 0) {
			u.u_error = ESRCH;
			return;
		}
		if (u.u_uid && u.u_uid != p->p_uid)
			u.u_error = EPERM;
		else if (uap->signo)
			psignal(p, uap->signo);
		return;
	}
	switch (uap->pid) {
	case -1:		/* broadcast signal */
		u.u_error = killpg1(uap->signo, 0, 1);
		break;
	case 0:			/* signal own process group */
		u.u_error = killpg1(uap->signo, 0, 0);
		break;
	default:		/* negative explicit process group */
		u.u_error = killpg1(uap->signo, -uap->pid, 0);
		break;
	}
	return;
}

killpg()
{
	register struct a {
		int	pgrp;
		int	signo;
	} *uap = (struct a *)u.u_ap;

	if (uap->signo < 0 || uap->signo > NSIG) {
		u.u_error = EINVAL;
		return;
	}
	u.u_error = killpg1(uap->signo, uap->pgrp, 0);
}

/* KILL CODE SHOULDNT KNOW ABOUT PROCESS INTERNALS !?! */

killpg1(signo, pgrp, all)
	int signo, pgrp, all;
{
	register struct proc *p;
	int f, error = 0;

	if (!all && pgrp == 0) {
		/*
		 * Zero process id means send to my process group.
		 */
		pgrp = u.u_procp->p_pgrp;
		if (pgrp == 0)
			return (ESRCH);
	}
	for (f = 0, p = allproc; p != NULL; p = p->p_nxt) {
		if ((p->p_pgrp != pgrp && !all) || p->p_ppid == 0 ||
		    (p->p_flag&SSYS) || (all && p == u.u_procp))
			continue;
		if (u.u_uid != 0 && u.u_uid != p->p_uid &&
		    (signo != SIGCONT || !inferior(p))) {
			if (!all)
				error = EPERM;
			continue;
		}
		f++;
		if (signo)
			psignal(p, signo);
	}
	return (error ? error : (f == 0 ? ESRCH : 0));
}

/*
 * Send the specified signal to
 * all processes with 'pgrp' as
 * process group.
 */
gsignal(pgrp, sig)
	register int pgrp;
{
	register struct proc *p;

	if (pgrp == 0)
		return;
	for (p = allproc; p != NULL; p = p->p_nxt)
		if (p->p_pgrp == pgrp)
			psignal(p, sig);
}

/*
 * Send the specified signal to
 * the specified process.
 */
psignal(p, sig)
	register struct proc *p;
	register int sig;
{
	register int s;
	register int (*action)();
	register thread_t	sig_thread;
	register task_t		sig_task;
	int mask;

	if ((unsigned)sig > NSIG)
		return;
	mask = sigmask(sig);
	/*
	 *	We will need the task pointer later.  Grab it now to
	 *	check for a zombie process.
	 */
	if ((sig_task = p->task) == TASK_NULL)
		return;

	/*
	 *	Kernel internal tasks don't take signals.
	 */
	if (sig_task->kernel_vm_space)
		return;

	/* 
	 *	Pick a thread to get signal -- 	current thread
	 *	if possible, else first thread in the task.
	 */
	if (sig_task == current_task())
		sig_thread = current_thread();
	else
		sig_thread = (thread_t) sig_task->thread_list.next;
 

	/*
	 * If proc is traced, always give parent a chance.
	 */
	if (p->p_flag & STRC)
		action = SIG_DFL;
	else {
		/*
		 * If the signal is being ignored,
		 * then we forget about it immediately.
		 */
		if (p->p_sigignore & mask)
			return;
		if (p->p_sigmask & mask)
			action = SIG_HOLD;
		else if (p->p_sigcatch & mask)
			action = SIG_CATCH;
		else
			action = SIG_DFL;
	}
	if (sig) {
		p->p_sig |= mask;
		switch (sig) {

		case SIGTERM:
			if ((p->p_flag&STRC) || action != SIG_DFL)
				break;
			/* fall into ... */

		case SIGKILL:
			if (p->p_nice > NZERO) {
 				p->p_nice = NZERO;
				sig_thread->priority = BASEPRI_USER;
			}
			break;

		case SIGCONT:
			p->p_sig &= ~stopsigmask;
			break;

		case SIGSTOP:
		case SIGTSTP:
		case SIGTTIN:
		case SIGTTOU:
			p->p_sig &= ~sigmask(SIGCONT);
			break;
		case SIGMSG:
		case SIGEMSG:
			/*
			 *	Don't post these signals unless
			 *	they'll be handled, regardless of
			 *	the state of the recipient.
			 */
			if (action == SIG_DFL) {
				p->p_sig &= ~mask;
				return;
			}
			break;
		}
	}
	/*
	 * Defer further processing for signals which are held.
	 */
	if (action == SIG_HOLD)
		return;
	s = splhigh();
	if (p->p_flag&STRC) {
		/*
		 *	Process is traced - wake it up (if not already
		 *	stopped) so that it can discover the signal in
		 *	issig() and stop for the parent.
		 */
		if (sig_task->user_stop_count == 0) {
			/*
			 *	Wake it up to get signal
			 */
			goto run;
		}
		goto out;
	}
	else if (action != SIG_DFL) {
		/*
		 *	User wants to catch the signal.
		 *	Wake up the thread, but don't un-suspend it
		 *	(except for SIGCONT).
		 */
		if (sig == SIGCONT) {
			(void) task_resume(sig_task);
			/*
			 *	Process will be running after 'run'
			 */
			p->p_stat = SRUN;
		}
		goto run;
	}
	else {
		/*
		 *	Default action - varies
		 */

		switch (sig) {

		case SIGSTOP:
		case SIGTSTP:
		case SIGTTIN:
		case SIGTTOU:
			/*
			 * These are the signals which by default
			 * stop a process.
			 *
			 * Don't clog system with children of init
			 * stopped from the keyboard.
			 */
			if (sig != SIGSTOP && p->p_pptr == &proc[1]) {
				psignal(p, SIGKILL);
				p->p_sig &= ~mask;
				splx(s);
				return;
			}
#if	VICE
			/*
			 * Buffering problems don't allow us to stop the job
			 * during a remote file system call.
			 */
			if (p->p_flag&SRMT)
				goto out;
#endif	VICE
			/*
			 *	Stop the task.
			 */
			if ((sig_thread->state & TH_RUN) == 0) {
				/*
				 *	If task hasn't already been stopped by
				 *	a signal, stop it.
				 */
				p->p_sig &= ~mask;
				if (sig_task->user_stop_count == 0) {
					/*
					 * p_cursig must not be set, because
					 * it will be psig()'d if it is not
					 * zero, and the signal is being
					 * handled here.  But save the signal
					 * in p_stopsig so WUNTRACED
					 * option to wait can find it.
					 */
					p->p_stopsig = sig;
					psignal(p->p_pptr, SIGCHLD);
					stop(p);
				}
				goto out;
			}
			else {
				if ((p == u.u_procp) && (p->p_stat != SZOMB))
#ifdef	vax
#include <vax/mtpr.h>
#endif	vax
					aston();
				goto out;
			}

		case SIGIO:
		case SIGURG:
		case SIGCHLD:
		case SIGWINCH:
		case SIGMSG:
		case SIGEMSG:
			/*
			 * These signals do not get propagated.  If the
			 * process isn't interested, forget it.
			 */
			p->p_sig &= ~mask;
			goto out;

		case SIGKILL:
			/*
			 * Kill signal always sets process running and
			 * unsuspends it.
			 */
			(void) task_resume(sig_task);
			/*
			 *	Process will be running after 'run'
			 */
			p->p_stat = SRUN;

			/*
			 * Break it out of user wait, as well.
			 */
			(void) thread_resume(sig_thread);

			/*
			 *	Clear system wait if possible.
			 */
			clear_wait(sig_thread, THREAD_SHOULD_TERMINATE, FALSE);
			goto out;

		case SIGCONT:
			/*
			 * Let the process run.  If it's sleeping on an
			 * event, it remains so.
			 */
			(void) task_resume(sig_task);
			p->p_stat = SRUN;
			goto out;

		default:
			/*
			 * All other signals wake up the process, but don't
			 * resume it.
			 */
			goto run;
		}
	}
	/*NOTREACHED*/
run:
	/*
	 * Raise priority to at least PUSER.
	 */
	if (p->p_pri > PUSER)
		p->p_pri = PUSER;
	/*
	 *	Wake up the thread if it is interruptible.
	 */
	clear_wait(sig_thread, THREAD_INTERRUPTED, TRUE);
out:
	splx(s);
}

/*
 * Returns true if the current
 * process has a signal to process.
 * The signal to process is put in p_cursig.
 * This is asked at least once each time a process enters the
 * system (though this can usually be done without actually
 * calling issig by checking the pending signal masks.)
 * A signal does not do anything
 * directly to a process; it sets
 * a flag that asks the process to
 * do something to itself.
 */
issig()
{
	register struct proc *p;
	register int sig;
	int sigbits, mask;

	p = u.u_procp;
	/*
	 *	This must be called on master cpu
	 */
	if (cpu_number() != master_cpu)
		panic("issig not on master");

	/*
	 *	Try for the signal lock.
	 *	If we already have it, return FALSE: don't handle any signals.
	 *	If we must halt, return TRUE to clean up our state.
	 */
	sig_lock_or_return(p, return(FALSE), return(TRUE));
	for (;;) {
		/*
		 *	In a multi-threaded task it is possible for
		 *	one thread to interrupt another's issig(); psig()
		 *	sequence.  In this case, the thread signal may
		 *	be left in u.u_cursig.  We recover here
		 *	by getting it out and starting over.
		 */
		if(u.u_cursig != 0) {
		    u.u_sig |= sigmask(u.u_cursig);
		    u.u_cursig = 0;
		}
		sigbits = (u.u_sig | p->p_sig) &~ p->p_sigmask;
		if ((p->p_flag&STRC) == 0)
			sigbits &= ~p->p_sigignore;
#if	VICE
		if (p->p_flag&(SVFORK|SRMT))
#else	VICE
		if (p->p_flag&SVFORK)
#endif	VICE
			sigbits &= ~stopsigmask;
		if (sigbits == 0)
			break;
		sig = ffs((long)sigbits);
		mask = sigmask(sig);
		if (mask & threadmask) {
			u.u_sig &= ~mask;
			u.u_cursig = sig;
		}
		p->p_sig &= ~mask;		/* take the signal! */
		p->p_cursig = sig;
#if	VICE
		if (p->p_flag&STRC && (p->p_flag&(SVFORK|SRMT)) == 0) {
#else	VICE
		if (p->p_flag&STRC && (p->p_flag&SVFORK) == 0) {
#endif	VICE
			/*
			 * If traced, always stop, and stay
			 * stopped until released by the parent.
			 */
			psignal(p->p_pptr, SIGCHLD);
			/*
			 *	New ptrace() has no procxmt.  Only action
			 *	executed on behalf of parent is exit.
			 *	This is requested via a large p_cursig.
			 *	sig_lock_to_wait causes other threads
			 *	that try to handle signals to stop for
			 *	debugger.
			 */
			p->thread = current_thread();
			pcb_synch(p->thread);
			stop(p);
			sig_lock_to_wait(p);
			thread_block();
			sig_wait_to_lock(p);
			/*
			 *	We get here only if task
			 *	is continued or killed.  Kill condition
			 *	is signalled by adding NSIG to p_cursig.
			 *	Pass original p_cursig as exit value in
			 *	this case.
			 */
			if (p->p_cursig > NSIG) {
				sig = p->p_cursig - NSIG;
				/*
				 *	Wait event may still be outstanding;
				 *	clear it, since sig_lock_to_exit will
				 *	wait.
				 */
				clear_wait(current_thread(),
					THREAD_INTERRUPTED,
					FALSE);
				sig_lock_to_exit(p);
				exit(sig);
			}

			/* 
			 *	We may have to quit
			 */
			if (thread_should_halt()) {
				sig_unlock(p);
				return(TRUE);
			}

			/*
			 * If the traced bit got turned off,
			 * then put the signal taken above back into p_sig
			 * and go back up to the top to rescan signals.
			 * This ensures that p_sig* and u_signal are consistent.
			 */
			if ((p->p_flag&STRC) == 0) {
				if (mask & threadmask)
					u.u_sig |= mask;
				else
					p->p_sig |= mask;
				continue;
			}

			/*
			 * If parent wants us to take the signal,
			 * then it will leave it in p->p_cursig;
			 * otherwise we just look for signals again.
			 */
			sig = p->p_cursig;
			if (sig == 0)
				continue;

			/*
			 * If signal is being masked put it back
			 * into p_sig and look for other signals.
			 */
			mask = sigmask(sig);
			if (p->p_sigmask & mask) {
				if (mask & threadmask)
					u.u_sig |= mask;
				else
					p->p_sig |= mask;
				continue;
			}
		}

#if	SWITCH_INT
		switch ((int)u.u_signal[sig]) {
#else	SWITCH_INT
		switch (u.u_signal[sig]) {
#endif	SWITCH_INT
		case SIG_DFL:

			/*
			 * Don't take default actions on system processes.
			 */
			if (p->p_ppid == 0) {
				u.u_cursig = 0;
				break;
			}
			switch (sig) {

			case SIGTSTP:
			case SIGTTIN:
			case SIGTTOU:
				/*
				 * Children of init aren't allowed to stop
				 * on signals from the keyboard.
				 */
				if (p->p_pptr == &proc[1]) {
					psignal(p, SIGKILL);
					continue;
				}
				/* fall into ... */

			case SIGSTOP:
				if (p->p_flag&STRC)
					continue;
				psignal(p->p_pptr, SIGCHLD);
				stop(p);
				sig_lock_to_wait(p);
				thread_block();
				sig_wait_to_lock(p);
				/*
				 *	We may have to quit
				 */
				if (thread_should_halt()) {
					sig_unlock(p);
					return(TRUE);
				}
				continue;

			case SIGCONT:
			case SIGCHLD:
			case SIGURG:
			case SIGIO:
			case SIGWINCH:
			case SIGMSG:
			case SIGEMSG:
				/*
				 * These signals are normally not
				 * sent if the action is the default.
				 */
				continue;		/* == ignore */

			default:
				goto send;
			}
			/*NOTREACHED*/

		case SIG_HOLD:
		case SIG_IGN:
			/*
			 * Masking above should prevent us
			 * ever trying to take action on a held
			 * or ignored signal, unless process is traced.
			 */
			if ((p->p_flag&STRC) == 0)
				printf("issig\n");
			continue;

		default:
			/*
			 * This signal has an action, let
			 * psig process it.
			 */
			goto send;
		}
		/*NOTREACHED*/
	}
	/*
	 * Didn't find a signal to send.
	 */
	p->p_cursig = 0;
	u.u_cursig = 0;
	sig_unlock(p);
	return (0);

send:
	/*
	 * Let psig process the signal.
	 */
	sig_unlock(p);
	return (sig);
}

/*
 * Put the argument process into the stopped
 * state and notify the parent via wakeup.
 * Signals are handled elsewhere.
 */
stop(p)
	register struct proc *p;
{

	/*
	 *	Call special task_suspend routine,
	 *	because this routine is called from interrupts
	 *	(psignal) and cannot sleep.
	 */
	(void) task_suspend_nowait(p->task);	/*XXX*/

	p->p_stat = SSTOP;
	p->p_flag &= ~SWTED;
	wakeup((caddr_t)p->p_pptr);
}

/*
 * Perform the action specified by
 * the current signal.
 * The usual sequence is:
 *	if (issig())
 *		psig();
 * The signal bit has already been cleared by issig,
 * and the current signal number stored in p->p_cursig.
 */
psig()
{
	register struct proc *p = u.u_procp;
	register int sig = p->p_cursig;
	int mask = sigmask(sig), returnmask;
	register int (*action)();

	/*
	 *	This must be called on master cpu
	 */
	if (cpu_number() != master_cpu)
		panic("psig not on master");

	/*
	 *	Try for the signal lock.  Don't proceed further if we
	 *	are already supposed to halt.
	 */
	sig_lock(p);
	sig = p->p_cursig;
	mask = sigmask(sig);

	/*
	 *	If another thread got here first (sig == 0) or this is
	 *	a thread signal for another thread, bail out.
	 */
	if ((sig == 0) || ((mask & threadmask) && (sig != u.u_cursig))) {
		sig_unlock(p);
		return;
	}
	/*
	 *  A polled resource pause condition which is being retried from the
	 *  system call level may be interrupted on the way back out to user
	 *  mode to be retried with a pause diagnostic message pending.  Always
	 *  clear the condition here before processing an interrupting signal
	 *  to keep the pause/continue diagnostic messages paired.
	 */
	if (u.u_rpswhich&URPW_NOTIFY)
	    rpcont();

	action = u.u_signal[sig];
	if (action != SIG_DFL) {
		if (action == SIG_IGN || (p->p_sigmask & mask))
			panic("psig action");
		u.u_error = 0;
		/*
		 * Set the new mask value and also defer further
		 * occurences of this signal (unless we're simulating
		 * the old signal facilities). 
		 *
		 * Special case: user has done a sigpause.  Here the
		 * current mask is not of interest, but rather the
		 * mask from before the sigpause is what we want restored
		 * after the signal processing is completed.
		 */
		(void) splhigh();
		if (p->p_flag & SOUSIG) {
			if (sig != SIGILL && sig != SIGTRAP) {
				u.u_signal[sig] = SIG_DFL;
				p->p_sigcatch &= ~mask;
			}
			mask = 0;
		}
		if (p->p_flag & SOMASK) {
			returnmask = u.u_oldmask;
			p->p_flag &= ~SOMASK;
		} else
			returnmask = p->p_sigmask;
		p->p_sigmask |= u.u_sigmask[sig] | mask;
		/*
		 *	Fix up the signal state and unlock before
		 *	we send the signal.
		 */
		p->p_cursig = 0;
		if (sigmask(sig) & threadmask)
			u.u_cursig = 0;
		sig_unlock(p);
 		(void) spl0();
 		u.u_ru.ru_nsignals++;
 		sendsig(action, sig, returnmask);
		return;
	}
	u.u_acflag |= AXSIG;
	switch (sig) {
	/*
	 *	The new signal code for multiple threads makes it possible
	 *	for a multi-threaded task to get here (a thread that didn't
	 *	originally process a "stop" signal notices that cursig is
	 *	set), therefore, we must handle this.
	 */
	case SIGTSTP:
	case SIGTTIN:
	case SIGTTOU:
	case SIGSTOP:
		sig_unlock(p);
		return;

	case SIGILL:
	case SIGIOT:
	case SIGBUS:
	case SIGQUIT:
	case SIGTRAP:
	case SIGEMT:
	case SIGFPE:
	case SIGSEGV:
	case SIGSYS:
		u.u_arg[0] = sig;
		/*
		 *	Indicate that we are about to exit.
		 *	disables all further signal processing for p.
		 */
		sig_lock_to_exit(p);
		if (core())
			sig += 0200;
		break;
	default:
		sig_lock_to_exit(p);
	}
	exit(sig);
}

/*
 * Create a core image on the file "core"
 * If you are looking for protection glitches,
 * there are probably a wealth of them here
 * when this occurs to a suid command.
 *
 * It writes UPAGES block of the
 * user.h area followed by the entire
 * data+stack segments.
 */
core()
{
	struct inode *ip;
#if	VICE
	struct file	*fp = NULL;
#endif	VICE
	vm_size_t	stack_size;
	vm_offset_t	stack_addr;
#ifdef	multimax
	struct ptrace_user	fake_uarea;
#else	multimax
#ifndef	sun
	struct user	fake_uarea;
#endif	sun
#endif	multimax
#ifdef	sun
	off_t		offset = 0;
#endif	sun

	if (u.u_procp->p_flag&SXONLY)
		return (0);
	u.u_uid = u.u_ruid;
	u.u_procp->p_uid = u.u_ruid;
	u.u_gid = u.u_rgid;

	/*
	 *	Don't want to resource-pause while core-dumping.
	 */
	u.u_rpause = 0;

	if (ctob(UPAGES+u.u_dsize+u.u_ssize) >=
	    u.u_rlimit[RLIMIT_CORE].rlim_cur)
		return (0);
	/*
	 *	Make sure all registers, etc. are in pcb so they get
	 *	into core file.
	 */
	pcb_synch(current_thread());
#if	VICE
	/* Won't dump core during syscall if current directory is remote */
	if (u.u_rmt_code != 0 && u.u_rmtWd.dev != NODEV)
		return (0);
	u.u_rmt_code = -1;	/* Should be a manifest */
	u.u_rmt_requested = 1;
#endif	VICE
	u.u_error = 0;
	CREATE_CORE_FILE(ip);
	u.u_acflag |= ACORE;
	/*
	 *	Fool Unix about the size of the stack.  Then
	 *	let it dump the stack in the way it normally does
	 *	below.
	 */
#ifdef	i386
	stack_addr = trunc_page(u.u_ar0[UESP]);
#endif	i386
#ifdef	mips
	stack_addr = trunc_page(u.u_ar0[EF_SP]);
#endif	mips
#if	!defined(i386) && !defined(mips)
	stack_addr = trunc_page(u.u_ar0[SP]);
#endif	!defined(i386) && !defined(mips)
	stack_size = (vm_offset_t)USRSTACK - stack_addr;
	stack_size = round_page(stack_size);
	u.u_ssize = btoc(stack_size);
#ifdef	sun
	/*
	 *	Write out the core structure, data, stack, and then
	 *	the u-area for the Sun
	 */
	sun_core(ip, &offset);
#else	sun
	/*
	 *	Fake the required fields in the u area to keep the
	 *	debuggers happy. Zero the unused fields.
	 */
	bzero(&fake_uarea, sizeof fake_uarea);
#if	MULTIMAX
	mmax_fake_ptrace_u(&fake_uarea, current_thread());
#else	MULTIMAX
	fake_u(&fake_uarea, current_thread());
#endif	MULTIMAX

	/* 
	 *	MACH breaks conventional debuggers because the kernel
	 *	stack is no longer at the top of memory.  Dump the forged
	 *	uarea where it is expected, followed by the current
	 *	kernel stack at the end of the UPAGES where the u-area
	 *	used to be.  Since the thread uarea contains the thread pcb
	 *	which contains the kernel stack offset, there is enough
	 *	information to decode what's going on.  This assumes that a
	 *	struct user, and a kernel stack all fit in UPAGES.
	 */
#ifdef	multimax
	/*
	 *	Multimax does this differently -- just dump the faked
	 *	uarea followed by data and user stack, that's all.
	 */
#endif	multimax
#ifdef	ibmrt
	/*
	 *	The RT's kernel stack is BELOW the U area, unlike everyone
	 *	else.
	 */
    {
	u_int k_max = ctob(UPAGES) - sizeof(struct user);
	if (k_max >= KERNEL_STACK_SIZE) {
	    u.u_error = RDWRI(UIO_WRITE, ip,
			      (caddr_t)(current_thread()->kernel_stack),
			      KERNEL_STACK_SIZE,
			      (off_t)(k_max - KERNEL_STACK_SIZE),
			      UIO_SYSSPACE, (int *)0);
	}
	else {
	    u_int k_diff = KERNEL_STACK_SIZE - k_max;
	    u.u_error = RDWRI(UIO_WRITE, ip,
			      (caddr_t)(current_thread()->kernel_stack +
					k_diff),
			      KERNEL_STACK_SIZE - k_diff,
			      (off_t) 0, UIO_SYSSPACE, (int *)0);
	}
    }
	if (u.u_error == 0)
	    u.u_error = RDWRI(UIO_WRITE, ip,
			      (caddr_t)&fake_uarea, sizeof(struct user),
			      (off_t)(ctob(UPAGES)-sizeof(struct user)),
			      UIO_SYSSPACE, (int *) 0);
#else	ibmrt
#ifdef	multimax
 	u.u_error = RDWRI(UIO_WRITE, ip, (caddr_t)&fake_uarea,
			  sizeof(struct ptrace_user),
			  (off_t)0, UIO_SYSSPACE, (int *)0);
#else	multimax

 	u.u_error = RDWRI(UIO_WRITE, ip, (caddr_t)&fake_uarea,
			  sizeof(struct user),
			  (off_t)0, UIO_SYSSPACE, (int *)0);
	if (u.u_error == 0)
#if	mips
	/*
	 * Had to increase the kernel stack size to accomodate..
	 * this very one function!
	 */
	    u.u_error = RDWRI(UIO_WRITE, ip,
			      (caddr_t)(current_thread()->kernel_stack +
					sizeof(struct user)),
			      KERNEL_STACK_SIZE - sizeof(struct user),
			      (off_t)(sizeof(struct user)), UIO_SYSSPACE,
			      (int *)0);
#else	mips
	    u.u_error = RDWRI(UIO_WRITE, ip,
			      (caddr_t)(current_thread()->kernel_stack),
			      KERNEL_STACK_SIZE,
			      (off_t)(ctob(UPAGES) - KERNEL_STACK_SIZE),
			      UIO_SYSSPACE, (int *)0);
#endif	mips
#endif	multimax
#endif	ibmrt
#endif	sun
#ifdef	multimax
 	if (u.u_error == 0)
 		u.u_error = RDWRI(UIO_WRITE, ip, (caddr_t)u.u_data_start,
				  (int)ctob(u.u_dsize),
				  sizeof(struct ptrace_user), UIO_USERSPACE,
				  (int *)0);
 	if (u.u_error == 0)
 		u.u_error = RDWRI(UIO_WRITE, ip, (caddr_t)stack_addr,
				  (int)stack_size,
				  sizeof(struct ptrace_user)+ctob(u.u_dsize),
				  UIO_USERSPACE, (int *)0);
#else	multimax
	if (u.u_error == 0) {
		caddr_t base = (caddr_t)u.u_data_start;
#ifdef	sun
		u.u_error = RDWRI(UIO_WRITE, ip, base,
				  (int)ctob(u.u_dsize),
				  offset, UIO_USERSPACE, (int *)0);
	}
	offset += ctob(u.u_dsize);
#else	sun
		u.u_error = RDWRI(UIO_WRITE, ip, base, (int)ctob(u.u_dsize),
				  (off_t)ctob(UPAGES), UIO_USERSPACE,
				  (int *)0);
	}
#endif	sun
	if (u.u_error == 0) {
		caddr_t base =	(caddr_t)stack_addr;
		int size = 	(int)stack_size;
#ifdef	sun
		u.u_error = RDWRI(UIO_WRITE, ip, base, size,
				  offset, UIO_USERSPACE, (int *)0);
	}
	offset+= ctob(u.u_ssize);
#else	sun
		u.u_error = RDWRI(UIO_WRITE, ip, base, size,
				  (off_t)ctob(UPAGES)+ctob(u.u_dsize),
				  UIO_USERSPACE, (int *)0);
	}
#endif	sun
#endif	multimax
#ifdef	sun
	/*
	 *	Write u-area last
	 */
	u.u_error = RDWRI(UIO_WRITE, ip,
			  (caddr_t)(current_thread()->u_address.uthread),
			  sizeof(struct user), offset, UIO_SYSSPACE, (int *)0);
	if (u.u_error == 0)
		u.u_error = RDWRI(UIO_WRITE, ip,
				  (caddr_t)(current_thread()->kernel_stack), 
				  KERNEL_STACK_SIZE,
				  (off_t)(offset + ctob(UPAGES) - 
					  KERNEL_STACK_SIZE),
				  UIO_SYSSPACE, (int *)0);
#endif	sun
out:
	FINISH_WITH_INODE(ip);
#if	VICE
	if (fp)
		closef(fp);
#endif	VICE
	return (u.u_error == 0);
}

