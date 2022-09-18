h43369
s 00002/00000/00141
d D 8.6 95/02/19 07:51:38 cgd 11 10
c add setsigvec() and sigexit() protos.
e
s 00004/00004/00137
d D 8.5 95/01/09 18:16:18 cgd 10 9
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00002/00139
d D 8.4 94/05/03 23:15:34 mckusick 9 8
c minor cleanups
e
s 00003/00003/00138
d D 8.3 94/01/04 16:16:47 bostic 8 7
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00017/00016/00124
d D 8.2 93/09/23 15:31:35 bostic 7 6
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00138
d D 8.1 93/06/02 19:55:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00005/00137
d D 7.5 92/04/20 23:29:10 mckusick 5 4
c definitions for sigaltstack
e
s 00002/00001/00140
d D 7.4 92/02/05 21:52:02 mckusick 4 3
c reorg for backward compatibility; add extra info word
e
s 00001/00000/00140
d D 7.3 92/02/05 20:16:10 torek 3 2
c SunOS compatibility
e
s 00004/00004/00136
d D 7.2 92/02/05 20:05:21 torek 2 1
c separate ttystop from stop so that kern_sig can tell them apart
e
s 00140/00000/00000
d D 7.1 91/05/09 20:39:49 bostic 1 0
c date and time created 91/05/09 20:39:49 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 8
#ifndef	_SIGNALVAR_H_		/* tmp for user.h */
#define	_SIGNALVAR_H_
E 8
I 8
#ifndef	_SYS_SIGNALVAR_H_		/* tmp for user.h */
#define	_SYS_SIGNALVAR_H_
E 8

/*
 * Kernel signal definitions and data structures,
 * not exported to user programs.
 */

/*
 * Process signal actions and state, needed only within the process
 * (not necessarily resident).
 */
struct	sigacts {
	sig_t	ps_sigact[NSIG];	/* disposition of signals */
	sigset_t ps_catchmask[NSIG];	/* signals to be blocked */
	sigset_t ps_sigonstack;		/* signals to take on sigstack */
	sigset_t ps_sigintr;		/* signals that interrupt syscalls */
	sigset_t ps_oldmask;		/* saved mask from before sigpause */
	int	ps_flags;		/* signal flags, below */
D 5
	struct	sigstack ps_sigstack;	/* sp & on stack state variable */
E 5
I 5
	struct	sigaltstack ps_sigstk;	/* sp & on stack state variable */
E 5
I 3
D 4
	sigset_t ps_usertramp;		/* SunOS compat; libc sigtramp XXX */
E 4
E 3
	int	ps_sig;			/* for core dump/debugger XXX */
D 10
	int	ps_code;		/* for core dump/debugger XXX */
I 4
	int	ps_addr;		/* for core dump/debugger XXX */
E 10
I 10
	long	ps_code;		/* for core dump/debugger XXX */
	long	ps_addr;		/* for core dump/debugger XXX */
E 10
	sigset_t ps_usertramp;		/* SunOS compat; libc sigtramp XXX */
E 4
};

D 5
#define	ps_onstack	ps_sigstack.ss_onstack
#define	ps_sigsp	ps_sigstack.ss_sp

E 5
/* signal flags */
D 5
#define	SA_OLDMASK	0x01		/* need to restore mask before pause */
E 5
I 5
#define	SAS_OLDMASK	0x01		/* need to restore mask before pause */
#define	SAS_ALTSTACK	0x02		/* have alternate signal stack */
E 5

/* additional signal action values, used only temporarily/internally */
#define	SIG_CATCH	(void (*)())2
#define	SIG_HOLD	(void (*)())3

/*
 * get signal action for process and signal; currently only for current process
 */
#define SIGACTION(p, sig)	(p->p_sigacts->ps_sigact[(sig)])

/*
D 7
 * Determine signal that should be delivered to process p, the current process,
 * 0 if none.  If there is a pending stop signal with default action,
 * the process stops in issig().
E 7
I 7
 * Determine signal that should be delivered to process p, the current
 * process, 0 if none.  If there is a pending stop signal with default
D 9
 * action, the process stops in issig().
E 9
I 9
 * action, the process stops in issignal().
E 9
E 7
 */
D 7
#define	CURSIG(p) \
	(((p)->p_sig == 0 || \
	    ((p)->p_flag&STRC) == 0 && ((p)->p_sig &~ (p)->p_sigmask) == 0) ? \
	    0 : issig(p))
E 7
I 7
#define	CURSIG(p)							\
	(((p)->p_siglist == 0 ||					\
	    ((p)->p_flag & P_TRACED) == 0 &&				\
	    ((p)->p_siglist & ~(p)->p_sigmask) == 0) ?			\
	    0 : issignal(p))
E 7

/*
 * Clear a pending signal from a process.
 */
D 7
#define	CLRSIG(p, sig)	{ (p)->p_sig &= ~sigmask(sig); }
E 7
I 7
#define	CLRSIG(p, sig)	{ (p)->p_siglist &= ~sigmask(sig); }
E 7

/*
 * Signal properties and actions.
 * The array below categorizes the signals and their default actions
 * according to the following properties:
 */
#define	SA_KILL		0x01		/* terminates process by default */
#define	SA_CORE		0x02		/* ditto and coredumps */
#define	SA_STOP		0x04		/* suspend process */
D 2
#define	SA_TTYSTOP	(0x08|SA_STOP)	/* ditto, from tty */
E 2
I 2
#define	SA_TTYSTOP	0x08		/* ditto, from tty */
E 2
#define	SA_IGNORE	0x10		/* ignore by default */
#define	SA_CONT		0x20		/* continue if suspended */
#define	SA_CANTMASK	0x40		/* non-maskable, catchable */

#ifdef	SIGPROP
int sigprop[NSIG + 1] = {
	0,			/* unused */
	SA_KILL,		/* SIGHUP */
	SA_KILL,		/* SIGINT */
	SA_KILL|SA_CORE,	/* SIGQUIT */
	SA_KILL|SA_CORE,	/* SIGILL */
	SA_KILL|SA_CORE,	/* SIGTRAP */
	SA_KILL|SA_CORE,	/* SIGABRT */
	SA_KILL|SA_CORE,	/* SIGEMT */
	SA_KILL|SA_CORE,	/* SIGFPE */
	SA_KILL,		/* SIGKILL */
	SA_KILL|SA_CORE,	/* SIGBUS */
	SA_KILL|SA_CORE,	/* SIGSEGV */
	SA_KILL|SA_CORE,	/* SIGSYS */
	SA_KILL,		/* SIGPIPE */
	SA_KILL,		/* SIGALRM */
	SA_KILL,		/* SIGTERM */
	SA_IGNORE,		/* SIGURG */
	SA_STOP,		/* SIGSTOP */
D 2
	SA_TTYSTOP,		/* SIGTSTP */
E 2
I 2
	SA_STOP|SA_TTYSTOP,	/* SIGTSTP */
E 2
	SA_IGNORE|SA_CONT,	/* SIGCONT */
	SA_IGNORE,		/* SIGCHLD */
D 2
	SA_TTYSTOP,		/* SIGTTIN */
	SA_TTYSTOP,		/* SIGTTOU */
E 2
I 2
	SA_STOP|SA_TTYSTOP,	/* SIGTTIN */
	SA_STOP|SA_TTYSTOP,	/* SIGTTOU */
E 2
	SA_IGNORE,		/* SIGIO */
	SA_KILL,		/* SIGXCPU */
	SA_KILL,		/* SIGXFSZ */
	SA_KILL,		/* SIGVTALRM */
	SA_KILL,		/* SIGPROF */
	SA_IGNORE,		/* SIGWINCH  */
	SA_IGNORE,		/* SIGINFO */
	SA_KILL,		/* SIGUSR1 */
	SA_KILL,		/* SIGUSR2 */
};

D 7
#define	stopsigmask	(sigmask(SIGSTOP)|sigmask(SIGTSTP)|\
			 sigmask(SIGTTIN)|sigmask(SIGTTOU))
E 7
#define	contsigmask	(sigmask(SIGCONT))
I 7
#define	stopsigmask	(sigmask(SIGSTOP) | sigmask(SIGTSTP) | \
			    sigmask(SIGTTIN) | sigmask(SIGTTOU))
E 7

#endif /* SIGPROP */

D 7
#define	sigcantmask	(sigmask(SIGKILL)|sigmask(SIGSTOP))
E 7
I 7
#define	sigcantmask	(sigmask(SIGKILL) | sigmask(SIGSTOP))
E 7

#ifdef KERNEL
/*
 * Machine-independent functions:
 */
D 7
void	siginit __P((struct proc *p));
E 7
I 7
int	coredump __P((struct proc *p));
E 7
void	execsigs __P((struct proc *p));
void	gsignal __P((int pgid, int sig));
I 7
D 9
int	issig __P((struct proc *p));
E 9
I 9
int	issignal __P((struct proc *p));
E 9
E 7
void	pgsignal __P((struct pgrp *pgrp, int sig, int checkctty));
D 7
void	trapsignal __P((struct proc *p, int sig, unsigned code));
E 7
I 7
void	postsig __P((int sig));
E 7
void	psignal __P((struct proc *p, int sig));
I 11
void	setsigvec __P((struct proc *p, int signum, struct sigaction *sa));
void	sigexit __P((struct proc *p, int signum));
E 11
D 7
int	issig __P((struct proc *p));
void	psig __P((int sig));
int	coredump __P((struct proc *p));
E 7
I 7
void	siginit __P((struct proc *p));
D 10
void	trapsignal __P((struct proc *p, int sig, unsigned code));
E 10
I 10
void	trapsignal __P((struct proc *p, int sig, u_long code));
E 10
E 7

/*
 * Machine-dependent functions:
 */
D 10
void	sendsig __P((sig_t action, int sig, int returnmask, unsigned code));
E 10
I 10
void	sendsig __P((sig_t action, int sig, int returnmask, u_long code));
E 10
#endif	/* KERNEL */
D 8
#endif	/* !_SIGNALVAR_H_ */
E 8
I 8
#endif	/* !_SYS_SIGNALVAR_H_ */
E 8
E 1
