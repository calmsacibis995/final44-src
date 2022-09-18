h27788
s 00001/00001/00422
d D 8.3 95/02/19 08:00:25 cgd 16 15
c ohpuxssig -> compat_43_hpuxssig
e
s 00002/00002/00421
d D 8.2 93/09/23 16:42:21 bostic 15 14
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00421
d D 8.1 93/06/10 21:24:43 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00416
d D 7.13 92/10/11 09:01:44 bostic 13 12
c make kernel includes standard
e
s 00002/00000/00420
d D 7.12 92/08/03 14:15:12 hibler 12 11
c ifdef ohpuxssig under COMPAT_OHPUX
e
s 00048/00038/00372
d D 7.11 92/07/10 18:48:48 torek 11 10
c ANSIfy syscall args
e
s 00001/00001/00409
d D 7.10 92/06/05 15:22:15 hibler 10 9
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00409
d D 7.9 92/04/20 23:33:14 mckusick 9 8
c rename a signal control flag
e
s 00030/00026/00380
d D 7.8 91/04/20 17:44:29 karels 8 7
c new proc struct, sigacts struct
e
s 00001/00001/00405
d D 7.7 90/12/16 22:16:15 mckusick 7 6
c fix include paths
e
s 00006/00006/00400
d D 7.6 90/12/16 16:36:32 bostic 6 5
c kernel reorg
e
s 00171/00003/00247
d D 7.5 90/12/05 19:04:41 mckusick 5 4
c update from Mike Hibler for new VM and other machine support
e
s 00013/00013/00237
d D 7.4 90/06/28 19:35:07 karels 4 3
c RETURN => return, remove syscontext.h
e
s 00066/00059/00184
d D 7.3 90/06/22 18:01:02 hibler 3 2
c eliminate use of u_error
e
s 00002/00002/00241
d D 7.2 90/06/08 15:09:42 mckusick 2 1
c brave new world
e
s 00243/00000/00000
d D 7.1 90/05/08 22:18:40 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 14
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: hpux_compat.c 1.33 89/08/23$
E 5
I 5
D 10
 * from: Utah $Hdr: hpux_sig.c 1.1 90/07/09$
E 10
I 10
 * from: Utah $Hdr: hpux_sig.c 1.4 92/01/20$
E 10
E 5
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Signal related HPUX compatibility routines
 */

#ifdef HPUXCOMPAT

D 6
#include "param.h"
#include "systm.h"
D 3
#include "user.h"
E 3
I 3
D 4
#include "syscontext.h"
E 4
I 4
#include "user.h"
E 4
E 3
#include "kernel.h"
#include "proc.h"
#include "hpux.h"
E 6
I 6
D 8
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/kernel.h"
#include "sys/proc.h"
E 8
I 8
D 13
#include "param.h"
#include "systm.h"
#include "kernel.h"
#include "proc.h"
#include "signalvar.h"
E 8
D 7
#include "sys/hpux.h"
E 7
I 7
#include "hpux.h"
E 13
I 13
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/signalvar.h>

#include <hp/hpux/hpux.h>
E 13
E 7
E 6

/* indexed by HPUX signal number - 1 */
char hpuxtobsdsigmap[NSIG] = {
/*01*/	SIGHUP,  SIGINT, SIGQUIT, SIGILL,   SIGTRAP, SIGIOT,  SIGEMT,   SIGFPE,
/*09*/  SIGKILL, SIGBUS, SIGSEGV, SIGSYS,   SIGPIPE, SIGALRM, SIGTERM,  SIGUSR1,
/*17*/  SIGUSR2, SIGCHLD, 0,      SIGVTALRM,SIGPROF, SIGIO,   SIGWINCH, SIGSTOP,
/*25*/	SIGTSTP, SIGCONT,SIGTTIN, SIGTTOU,  SIGURG,  0,       0,        0
};

/* indexed by BSD signal number - 1 */
char bsdtohpuxsigmap[NSIG] = {
/*01*/	 1,  2,  3,  4,  5,  6,  7,  8,
/*09*/   9, 10, 11, 12, 13, 14, 15, 29,
/*17*/  24, 25, 26, 18, 27, 28, 22,  0,
/*25*/	 0, 20, 21, 23,  0, 16, 17,  0
};

/*
 * XXX: In addition to mapping the signal number we also have
 * to see if the "old" style signal mechinism is needed.
 * If so, we set the OUSIG flag.  This is not really correct
 * as under HP-UX "old" style handling can be set on a per
 * signal basis and we are setting it for all signals in one
 * swell foop.  I suspect we can get away with this since I
 * doubt any program of interest mixes the two semantics.
 */
I 11
struct hpuxsigvec_args {
	int	signo;
	struct	sigvec *nsv;
	struct	sigvec *osv;
};
E 11
D 3
hpuxsigvec()
{
	register struct a {
E 3
I 3
hpuxsigvec(p, uap, retval)
	struct proc *p;
D 11
	register struct args {
E 3
		int	signo;
		struct	sigvec *nsv;
		struct	sigvec *osv;
D 3
	} *uap = (struct a  *)u.u_ap;
E 3
I 3
	} *uap;
E 11
I 11
	register struct hpuxsigvec_args *uap;
E 11
	int *retval;
{
E 3
	struct sigvec vec;
I 8
	register struct sigacts *ps = p->p_sigacts;
E 8
	register struct sigvec *sv;
	register int sig;
D 3
	int bit;
E 3
I 3
	int bit, error;
E 3

	sig = hpuxtobsdsig(uap->signo);
D 3
	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP) {
		u.u_error = EINVAL;
		return;
	}
E 3
I 3
	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP)
D 4
		RETURN (EINVAL);
E 4
I 4
		return (EINVAL);
E 4
E 3
	sv = &vec;
	if (uap->osv) {
D 8
		sv->sv_handler = u.u_signal[sig];
		sv->sv_mask = u.u_sigmask[sig];
E 8
I 8
		sv->sv_handler = ps->ps_sigact[sig];
		sv->sv_mask = ps->ps_catchmask[sig];
E 8
		bit = sigmask(sig);
		sv->sv_flags = 0;
D 8
		if ((u.u_sigonstack & bit) != 0)
E 8
I 8
		if ((ps->ps_sigonstack & bit) != 0)
E 8
			sv->sv_flags |= SV_ONSTACK;
D 8
		if ((u.u_sigintr & bit) != 0)
E 8
I 8
		if ((ps->ps_sigintr & bit) != 0)
E 8
			sv->sv_flags |= SV_INTERRUPT;
#if 0
/* XXX -- SOUSIG no longer exists, do something here */
D 3
		if (u.u_procp->p_flag & SOUSIG)
E 3
I 3
		if (p->p_flag & SOUSIG)
E 3
			sv->sv_flags |= HPUXSV_RESET;		/* XXX */
#endif
D 3
		u.u_error =
		    copyout((caddr_t)sv, (caddr_t)uap->osv, sizeof (vec));
		if (u.u_error)
			return;
E 3
I 3
		error = copyout((caddr_t)sv, (caddr_t)uap->osv, sizeof (vec));
		if (error)
D 4
			RETURN (error);
E 4
I 4
			return (error);
E 4
E 3
	}
	if (uap->nsv) {
D 3
		u.u_error =
		    copyin((caddr_t)uap->nsv, (caddr_t)sv, sizeof (vec));
		if (u.u_error)
			return;
		if (sig == SIGCONT && sv->sv_handler == SIG_IGN) {
			u.u_error = EINVAL;
			return;
		}
D 2
		setsigvec(sig, (struct sigaction *)sv);
E 2
I 2
		setsigvec(u.u_procp, sig, (struct sigaction *)sv);
E 3
I 3
		error = copyin((caddr_t)uap->nsv, (caddr_t)sv, sizeof (vec));
		if (error)
D 4
			RETURN (error);
E 4
I 4
			return (error);
E 4
		if (sig == SIGCONT && sv->sv_handler == SIG_IGN)
D 4
			RETURN (EINVAL);
E 4
I 4
			return (EINVAL);
I 8
		sv->sv_flags ^= SA_RESTART;
E 8
E 4
		setsigvec(p, sig, (struct sigaction *)sv);
E 3
E 2
#if 0
/* XXX -- SOUSIG no longer exists, do something here */
		if (sv->sv_flags & HPUXSV_RESET)
D 3
			u.u_procp->p_flag |= SOUSIG;		/* XXX */
E 3
I 3
			p->p_flag |= SOUSIG;		/* XXX */
E 3
#endif
	}
I 3
D 4
	RETURN (0);
E 4
I 4
	return (0);
E 4
E 3
}

I 11
struct hpuxsigblock_args {
	int	mask;
};
E 11
D 3
hpuxsigblock()
{
	struct a {
E 3
I 3
hpuxsigblock(p, uap, retval)
	register struct proc *p;
D 11
	struct args {
E 3
		int	mask;
D 3
	} *uap = (struct a *)u.u_ap;
E 3
I 3
	} *uap;
E 11
I 11
	struct hpuxsigblock_args *uap;
E 11
	int *retval;
{
E 3

	(void) splhigh();
D 3
	u.u_r.r_val1 = bsdtohpuxmask(u.u_procp->p_sigmask);
	u.u_procp->p_sigmask |= hpuxtobsdmask(uap->mask) &~ sigcantmask;
E 3
I 3
	*retval = bsdtohpuxmask(p->p_sigmask);
	p->p_sigmask |= hpuxtobsdmask(uap->mask) &~ sigcantmask;
E 3
	(void) spl0();
I 3
D 4
	RETURN (0);
E 4
I 4
	return (0);
E 4
E 3
}

I 11
struct hpuxsigsetmask_args {
	int	mask;
};
E 11
D 3
hpuxsigsetmask()
{
	struct a {
E 3
I 3
hpuxsigsetmask(p, uap, retval)
	struct proc *p;
D 11
	struct args {
E 3
		int	mask;
D 3
	} *uap = (struct a *)u.u_ap;
E 3
I 3
	} *uap;
E 11
I 11
	struct hpuxsigsetmask_args *uap;
E 11
	int *retval;
{
E 3

	(void) splhigh();
D 3
	u.u_r.r_val1 = bsdtohpuxmask(u.u_procp->p_sigmask);
	u.u_procp->p_sigmask = hpuxtobsdmask(uap->mask) &~ sigcantmask;
E 3
I 3
	*retval = bsdtohpuxmask(p->p_sigmask);
	p->p_sigmask = hpuxtobsdmask(uap->mask) &~ sigcantmask;
E 3
	(void) spl0();
I 3
D 4
	RETURN (0);
E 4
I 4
	return (0);
E 4
E 3
}

I 11
struct hpuxsigpause_args {
	int	mask;
};
E 11
D 3
hpuxsigpause()
{
	struct a {
E 3
I 3
hpuxsigpause(p, uap, retval)
	struct proc *p;
D 11
	struct args {
E 3
		int	mask;
D 3
	} *uap = (struct a *)u.u_ap;
E 3
I 3
	} *uap;
E 11
I 11
	struct hpuxsigpause_args *uap;
E 11
	int *retval;
{
E 3

	uap->mask = hpuxtobsdmask(uap->mask);
D 3
	sigsuspend();
E 3
I 3
D 4
	RETURN (sigsuspend(p, uap, retval));
E 4
I 4
	return (sigsuspend(p, uap, retval));
E 4
E 3
}

/* not totally correct, but close enuf' */
I 11
struct hpuxkill_args {
	int	pid;
	int	signo;
};
E 11
D 3
hpuxkill()
{
	struct a {
E 3
I 3
hpuxkill(p, uap, retval)
	struct proc *p;
D 11
	struct args {
E 3
		int	pid;
		int	signo;
D 3
	} *uap = (struct a *)u.u_ap;
E 3
I 3
	} *uap;
E 11
I 11
	struct hpuxkill_args *uap;
E 11
	int *retval;
{
E 3

	if (uap->signo) {
		uap->signo = hpuxtobsdsig(uap->signo);
		if (uap->signo == 0)
			uap->signo = NSIG;
	}
D 3
	kill();
E 3
I 3
D 4
	RETURN (kill(p, uap, retval));
E 4
I 4
	return (kill(p, uap, retval));
I 5
}

/*
 * The following (sigprocmask, sigpending, sigsuspend, sigaction are
 * POSIX calls.  Under BSD, the library routine dereferences the sigset_t
 * pointers before traping.  Not so under HP-UX.
 */

/*
 * Manipulate signal mask.
 * Note that we receive new mask, not pointer,
 * and return old mask as return value;
 * the library stub does the rest.
 */
I 11
struct hpuxsigprocmask_args {
	int		how;
	hpuxsigset_t	*set;
	hpuxsigset_t	*oset;
};
E 11
hpuxsigprocmask(p, uap, retval)
	register struct proc *p;
D 11
	struct args {
		int		how;
		hpuxsigset_t	*set;
		hpuxsigset_t	*oset;
	} *uap;
E 11
I 11
	struct hpuxsigprocmask_args *uap;
E 11
	int *retval;
{
	int mask, error = 0;
	hpuxsigset_t sigset;

	/*
	 * Copy out old mask first to ensure no errors.
	 * (proc sigmask should not be changed if call fails for any reason)
	 */
	if (uap->oset) {
		bzero((caddr_t)&sigset, sizeof(sigset));
		sigset.sigset[0] = bsdtohpuxmask(p->p_sigmask);
		if (copyout((caddr_t)&sigset, (caddr_t)uap->oset, sizeof(sigset)))
			return (EFAULT);
	}
	if (uap->set) {
		if (copyin((caddr_t)uap->set, (caddr_t)&sigset, sizeof(sigset)))
			return (EFAULT);
		mask = hpuxtobsdmask(sigset.sigset[0]);
		(void) splhigh();
		switch (uap->how) {
		case HPUXSIG_BLOCK:
			p->p_sigmask |= mask &~ sigcantmask;
			break;
		case HPUXSIG_UNBLOCK:
			p->p_sigmask &= ~mask;
			break;
		case HPUXSIG_SETMASK:
			p->p_sigmask = mask &~ sigcantmask;
			break;
		default:
			error = EINVAL;
			break;
		}
		(void) spl0();
	}
	return (error);
}

I 11
struct hpuxsigpending_args {
	hpuxsigset_t	*set;
};
E 11
hpuxsigpending(p, uap, retval)
	register struct proc *p;
D 11
	struct args {
		hpuxsigset_t	*set;
	} *uap;
E 11
I 11
	struct hpuxsigpending_args *uap;
E 11
	int *retval;
{
	hpuxsigset_t sigset;

D 15
	sigset.sigset[0] = bsdtohpuxmask(p->p_sig);
E 15
I 15
	sigset.sigset[0] = bsdtohpuxmask(p->p_siglist);
E 15
	return (copyout((caddr_t)&sigset, (caddr_t)uap->set, sizeof(sigset)));
}

I 11
struct hpuxsigsuspend_args {
	hpuxsigset_t	*set;
};
E 11
hpuxsigsuspend(p, uap, retval)
	register struct proc *p;
D 11
	struct args {
		hpuxsigset_t	*set;
	} *uap;
E 11
I 11
	struct hpuxsigsuspend_args *uap;
E 11
	int *retval;
{
I 8
	register struct sigacts *ps = p->p_sigacts;
E 8
	hpuxsigset_t sigset;
	int mask;

	if (copyin((caddr_t)uap->set, (caddr_t)&sigset, sizeof(sigset)))
		return (EFAULT);
	mask = hpuxtobsdmask(sigset.sigset[0]);
D 8
	u.u_oldmask = p->p_sigmask;
	p->p_flag |= SOMASK;
E 8
I 8
	ps->ps_oldmask = p->p_sigmask;
D 9
	ps->ps_flags |= SA_OLDMASK;
E 9
I 9
	ps->ps_flags |= SAS_OLDMASK;
E 9
E 8
	p->p_sigmask = mask &~ sigcantmask;
D 8
	(void) tsleep((caddr_t)&u, PPAUSE | PCATCH, "pause", 0);
E 8
I 8
	(void) tsleep((caddr_t)ps, PPAUSE | PCATCH, "pause", 0);
E 8
	/* always return EINTR rather than ERESTART... */
	return (EINTR);
}

I 11
struct hpuxsigaction_args {
	int	signo;
	struct	hpuxsigaction *nsa;
	struct	hpuxsigaction *osa;
};
E 11
hpuxsigaction(p, uap, retval)
	struct proc *p;
D 11
	register struct args {
		int	signo;
		struct	hpuxsigaction *nsa;
		struct	hpuxsigaction *osa;
	} *uap;
E 11
I 11
	register struct hpuxsigaction_args *uap;
E 11
	int *retval;
{
	struct hpuxsigaction action;
I 8
	register struct sigacts *ps = p->p_sigacts;
E 8
	register struct hpuxsigaction *sa;
	register int sig;
	int bit;

	sig = hpuxtobsdsig(uap->signo);
	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP)
		return (EINVAL);

	sa = &action;
	if (uap->osa) {
D 8
		sa->sa_handler = u.u_signal[sig];
E 8
I 8
		sa->sa_handler = ps->ps_sigact[sig];
E 8
		bzero((caddr_t)&sa->sa_mask, sizeof(sa->sa_mask));
D 8
		sa->sa_mask.sigset[0] = bsdtohpuxmask(u.u_sigmask[sig]);
E 8
I 8
		sa->sa_mask.sigset[0] = bsdtohpuxmask(ps->ps_catchmask[sig]);
E 8
		bit = sigmask(sig);
		sa->sa_flags = 0;
D 8
		if ((u.u_sigonstack & bit) != 0)
E 8
I 8
		if ((ps->ps_sigonstack & bit) != 0)
E 8
			sa->sa_flags |= HPUXSA_ONSTACK;
#if 0
/* XXX -- SOUSIG no longer exists, do something here */
		if (p->p_flag & SOUSIG)
			sa->sa_flags |= HPUXSA_RESETHAND;	/* XXX */
#endif
D 15
		if (p->p_flag & SNOCLDSTOP)
E 15
I 15
		if (p->p_flag & P_NOCLDSTOP)
E 15
			sa->sa_flags |= HPUXSA_NOCLDSTOP;
		if (copyout((caddr_t)sa, (caddr_t)uap->osa, sizeof (action)))
			return (EFAULT);
	}
	if (uap->nsa) {
		struct sigaction act;

		if (copyin((caddr_t)uap->nsa, (caddr_t)sa, sizeof (action)))
			return (EFAULT);
		if (sig == SIGCONT && sa->sa_handler == SIG_IGN)
			return (EINVAL);
		/*
		 * Create a sigaction struct for setsigvec
		 */
		act.sa_handler = sa->sa_handler;
		act.sa_mask = hpuxtobsdmask(sa->sa_mask.sigset[0]);
D 8
		act.sa_flags = 0;
E 8
I 8
		act.sa_flags == SA_RESTART;
E 8
		if (sa->sa_flags & HPUXSA_ONSTACK)
			act.sa_flags |= SA_ONSTACK;
		if (sa->sa_flags & HPUXSA_NOCLDSTOP)
			act.sa_flags |= SA_NOCLDSTOP;
		setsigvec(p, sig, &act);
#if 0
/* XXX -- SOUSIG no longer exists, do something here */
		if (sa->sa_flags & HPUXSA_RESETHAND)
			p->p_flag |= SOUSIG;		/* XXX */
#endif
	}
	return (0);
E 5
E 4
E 3
}

I 12
#ifdef COMPAT_OHPUX
E 12
I 11
struct ohpuxssig_args {
	int	signo;
	sig_t	fun;
};
E 11
D 3
ohpuxssig()
{
	struct a {
E 3
I 3
D 16
ohpuxssig(p, uap, retval)
E 16
I 16
compat_43_hpuxssig(p, uap, retval)
E 16
	struct proc *p;
D 11
	struct args {
E 3
		int	signo;
		sig_t	fun;
D 3
	} *uap = (struct a *)u.u_ap;
E 3
I 3
	} *uap;
E 11
I 11
	struct ohpuxssig_args *uap;
E 11
	int *retval;
{
E 3
	register int a;
D 8
	struct sigvec vec;
	register struct sigvec *sv = &vec;
E 8
I 8
	struct sigaction vec;
	register struct sigaction *sa = &vec;
E 8
D 3
	struct proc *p = u.u_procp;
E 3

	a = hpuxtobsdsig(uap->signo);
D 8
	sv->sv_handler = uap->fun;
E 8
I 8
	sa->sa_handler = uap->fun;
E 8
	/*
	 * Kill processes trying to use job control facilities
	 * (this'll help us find any vestiges of the old stuff).
	 */
	if ((a &~ 0377) ||
D 8
	    (sv->sv_handler != SIG_DFL && sv->sv_handler != SIG_IGN &&
	     ((int)sv->sv_handler) & 1)) {
E 8
I 8
	    (sa->sa_handler != SIG_DFL && sa->sa_handler != SIG_IGN &&
	     ((int)sa->sa_handler) & 1)) {
E 8
		psignal(p, SIGSYS);
D 3
		return;
E 3
I 3
D 4
		RETURN (0);
E 4
I 4
		return (0);
E 4
E 3
	}
	if (a <= 0 || a >= NSIG || a == SIGKILL || a == SIGSTOP ||
D 3
	    a == SIGCONT && sv->sv_handler == SIG_IGN) {
		u.u_error = EINVAL;
		return;
	}
E 3
I 3
D 8
	    a == SIGCONT && sv->sv_handler == SIG_IGN)
E 8
I 8
	    a == SIGCONT && sa->sa_handler == SIG_IGN)
E 8
D 4
		RETURN (EINVAL);
E 4
I 4
		return (EINVAL);
E 4
E 3
D 8
	sv->sv_mask = 0;
	sv->sv_flags = SV_INTERRUPT;
D 3
	u.u_r.r_val1 = (int)u.u_signal[a];
D 2
	setsigvec(a, (struct sigaction *)sv);
E 2
I 2
	setsigvec(u.u_procp, a, (struct sigaction *)sv);
E 3
I 3
	*retval = (int)u.u_signal[a];
	setsigvec(p, a, (struct sigaction *)sv);
E 8
I 8
	sa->sa_mask = 0;
	sa->sa_flags = 0;
	*retval = (int)p->p_sigacts->ps_sigact[a];
	setsigvec(p, a, sa);
E 8
E 3
E 2
#if 0
	p->p_flag |= SOUSIG;		/* mark as simulating old stuff */
#endif
I 3
D 4
	RETURN (0);
E 4
I 4
	return (0);
E 4
E 3
}
I 12
#endif
E 12

/* signal numbers: convert from HPUX to BSD */
hpuxtobsdsig(sig)
	register int sig;
{
	if (--sig < 0 || sig >= NSIG)
		return(0);
	return((int)hpuxtobsdsigmap[sig]);
}

/* signal numbers: convert from BSD to HPUX */
bsdtohpuxsig(sig)
	register int sig;
{
	if (--sig < 0 || sig >= NSIG)
		return(0);
	return((int)bsdtohpuxsigmap[sig]);
}

/* signal masks: convert from HPUX to BSD (not pretty or fast) */
hpuxtobsdmask(mask)
	register int mask;
{
	register int nmask, sig, nsig;

	if (mask == 0 || mask == -1)
		return(mask);
	nmask = 0;
	for (sig = 1; sig < NSIG; sig++)
		if ((mask & sigmask(sig)) && (nsig = hpuxtobsdsig(sig)))
			nmask |= sigmask(nsig);
	return(nmask);
}

bsdtohpuxmask(mask)
	register int mask;
{
	register int nmask, sig, nsig;

	if (mask == 0 || mask == -1)
		return(mask);
	nmask = 0;
	for (sig = 1; sig < NSIG; sig++)
		if ((mask & sigmask(sig)) && (nsig = bsdtohpuxsig(sig)))
			nmask |= sigmask(nsig);
	return(nmask);
}
#endif
E 1
