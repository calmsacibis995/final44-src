h03438
s 00002/00004/00166
d D 8.4 95/05/04 16:03:33 mckusick 47 46
c sa_handler always takes an int argument
e
s 00007/00005/00163
d D 8.3 95/05/03 21:58:20 mckusick 46 45
c more POSIX and ANSI compliance (from karels)
e
s 00005/00000/00163
d D 8.2 94/01/21 17:25:18 bostic 45 44
c add USL's copyright notice
e
s 00002/00002/00161
d D 8.1 93/06/02 19:55:14 bostic 44 43
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00000/00153
d D 7.26 93/03/28 19:48:42 torek 43 42
c conform to the letter of the law (ANSI / C++ signal() returns).
c This really should be done with a compat layer in libc....
e
s 00013/00010/00140
d D 7.25 92/04/20 23:28:47 mckusick 42 41
c definitions for sigaltstack
e
s 00002/00000/00148
d D 7.24 92/02/11 11:16:30 bostic 41 40
c _ANSI_SOURCE fix from Chris
e
s 00003/00000/00145
d D 7.23 92/02/05 20:16:09 torek 40 39
c SunOS compatibility
e
s 00008/00000/00137
d D 7.22 91/11/11 11:55:20 bostic 39 38
c move signal(3)'s prototype back into <sys/signal.h> to make the
c applications happy again
e
s 00008/00043/00129
d D 7.21 91/11/01 16:30:29 bostic 38 37
c create a user-level signal.h
e
s 00022/00057/00150
d D 7.20 91/09/08 12:22:36 karels 37 36
c move machine-dependent stuff to <machine/signal.h>; try to clean up
c (note that sig_t and signal prototypes are incomplete but standard...)
e
s 00018/00007/00189
d D 7.19 91/09/06 17:18:36 ralph 36 35
c add pmax sigcontext
e
s 00002/00002/00194
d D 7.18 91/09/03 15:19:17 bostic 35 34
c #define BADSIG as SIG_ERR
e
s 00005/00003/00191
d D 7.17 91/09/03 15:11:32 bostic 34 33
c add sig_atomic_t (ANSI); fix SA_RESTART comment; add SIG_ERR (ANSI)
e
s 00030/00036/00164
d D 7.16 91/03/17 15:34:09 karels 33 32
c more-or-less working with new proc & user structs
e
s 00021/00028/00179
d D 7.15 91/02/05 17:03:19 bostic 32 31
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00000/00004/00207
d D 7.14 90/12/16 16:42:12 bostic 31 30
c kernel reorg
e
s 00002/00004/00209
d D 7.13 90/10/31 11:17:09 bostic 30 29
c don't include function prototypes in the kernel
e
s 00005/00000/00208
d D 7.12 90/10/23 22:53:42 mckusick 29 28
c need types for function prototypes
e
s 00001/00001/00207
d D 7.11 90/07/01 16:19:46 karels 28 27
c correct return value from sigfillset
e
s 00005/00000/00203
d D 7.10 90/06/27 14:38:56 karels 27 26
c add CLRSIG for mfs unmount
e
s 00002/00002/00201
d D 7.9 90/05/29 19:29:51 bostic 26 25
c C++ needs prototypes, too
e
s 00036/00006/00167
d D 7.8 90/05/26 12:39:29 bostic 25 24
c add Berkeley copyright (nothing but SIG_* left); function prototypes
e
s 00011/00000/00162
d D 7.7 90/02/23 14:51:44 karels 24 23
c mv ISSIG from param.h and rename to CURSIG (now returns signal num)
e
s 00010/00004/00152
d D 7.6 90/02/20 13:27:23 karels 23 22
c cleanups of posix stuff
e
s 00071/00021/00085
d D 7.5 89/08/26 16:34:55 karels 22 21
c posix
e
s 00001/00001/00105
d D 7.4 89/04/25 11:01:03 mckusick 21 20
c ../machine => machine
e
s 00004/00000/00102
d D 7.3 88/05/14 11:24:40 karels 20 19
c use "../machine" for consistency (for now)
e
s 00002/00014/00100
d D 7.2 87/07/11 15:24:56 karels 19 18
c move code definitions to <machine/trap.h>
e
s 00001/00001/00113
d D 7.1 86/06/04 23:27:39 mckusick 18 17
c 4.3BSD release version
e
s 00003/00003/00111
d D 6.9 86/02/20 14:04:41 karels 17 16
c typo
e
s 00002/00000/00112
d D 6.8 86/02/02 21:32:54 karels 16 15
c compatibility with those other people
e
s 00007/00001/00105
d D 6.7 85/06/08 15:06:58 mckusick 15 14
c Add copyright
e
s 00002/00000/00104
d D 6.6 85/05/22 18:35:00 mckusick 14 13
c define SIGUSR1 and SIGUSR2
e
s 00004/00001/00100
d D 6.5 85/03/11 20:48:13 mckusick 13 11
c generalize sv_onstack to sv_flags to allow extensions for other options
e
s 00004/00001/00100
d R 6.5 85/03/11 20:37:26 mckusick 12 11
c generalize sv_onstack to sv_flags to allow extensions for other options
e
s 00002/00000/00099
d D 6.4 85/03/07 22:17:55 mckusick 11 9
c add fp and ap to signal context so sigcatch() can become a real syscall
e
s 00002/00000/00099
d R 6.4 85/03/07 20:28:10 mckusick 10 9
c add fp and ap to signal context so sigcatch() can become a real syscall
e
s 00001/00000/00098
d D 6.3 84/12/31 12:41:49 bloom 9 8
c added SIGWINCH
e
s 00006/00000/00092
d D 6.2 84/08/30 13:35:59 ralph 8 7
c added sigmask macro to convert signal number to bit mask.
e
s 00000/00000/00092
d D 6.1 83/08/14 14:21:50 sam 7 6
c 4.2 distribution
e
s 00001/00000/00091
d D 4.4 83/08/14 14:21:35 sam 6 4
c must have sp as well for signal stacks to work 
e
s 00000/00000/00091
d R 6.1 83/08/08 18:29:50 sam 5 4
c 4.2 distribution
e
s 00000/00001/00091
d D 4.3 83/08/08 18:29:34 sam 4 2
c sigvec incorrectly defined
e
s 00000/00000/00092
d R 6.1 83/07/29 06:13:54 sam 3 2
c 4.2 distribution
e
s 00018/00000/00074
d D 4.2 83/06/09 21:56:57 sam 2 1
c "final" sigvec interface?
e
s 00074/00000/00000
d D 4.1 83/06/02 15:52:54 sam 1 0
c date and time created 83/06/02 15:52:54 by sam
e
u
U
t
T
I 1
D 15
/*	%M%	%I%	%E%	*/
E 15
I 15
/*
D 18
 * Copyright (c) 1982 Regents of the University of California.
E 18
I 18
D 22
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 22
I 22
D 33
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 33
I 33
D 44
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 33
E 22
E 18
D 25
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 25
I 25
 * All rights reserved.
E 44
I 44
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 45
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 45
E 44
E 25
 *
I 25
 * %sccs.include.redist.c%
 *
E 25
 *	%W% (Berkeley) %G%
 */
E 15

D 32
#ifndef	NSIG
E 32
I 32
D 38
#ifndef	_SIGNAL_H_
#define	_SIGNAL_H_
E 38
I 38
#ifndef	_SYS_SIGNAL_H_
#define	_SYS_SIGNAL_H_
E 38

I 46
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 46
E 32
D 22
#define NSIG	32
E 22
I 22
D 23
#define NSIG	32		/* could be 33, as masks hold 1-32 */
E 23
I 23
#define NSIG	32		/* counting 0; could be 33 (mask is 1-32) */
I 46
#endif
E 46
E 23
E 22

I 41
D 46
#ifndef _ANSI_SOURCE
E 46
E 41
I 22
D 37
#ifndef _POSIX_SOURCE
E 22
I 20
D 31
#ifdef KERNEL
D 21
#include "../machine/trap.h"	/* codes for SIGILL, SIGFPE */
E 21
I 21
#include "machine/trap.h"	/* codes for SIGILL, SIGFPE */
E 21
#else
E 31
E 20
I 19
#include <machine/trap.h>	/* codes for SIGILL, SIGFPE */
E 37
I 37
D 38
#ifndef KERNEL
#include <sys/types.h>
#include <sys/cdefs.h>
E 37
I 20
D 31
#endif
E 31
I 22
D 34
#endif /* _POSIX_SOURCE */
E 34
I 34
#endif
E 38
I 37
#include <machine/signal.h>	/* sigcontext; codes for SIGILL, SIGFPE */
I 41
D 46
#endif
E 46
E 41
E 37
E 34
E 22
E 20

E 19
#define	SIGHUP	1	/* hangup */
#define	SIGINT	2	/* interrupt */
#define	SIGQUIT	3	/* quit */
#define	SIGILL	4	/* illegal instruction (not reset when caught) */
I 22
#ifndef _POSIX_SOURCE
E 22
D 19
#define	    ILL_RESAD_FAULT	0x0	/* reserved addressing fault */
#define	    ILL_PRIVIN_FAULT	0x1	/* privileged instruction fault */
#define	    ILL_RESOP_FAULT	0x2	/* reserved operand fault */
/* CHME, CHMS, CHMU are not yet given back to users reasonably */
E 19
#define	SIGTRAP	5	/* trace trap (not reset when caught) */
D 22
#define	SIGIOT	6	/* IOT instruction */
I 16
#define	SIGABRT	SIGIOT	/* compatibility */
E 22
I 22
#endif
#define	SIGABRT	6	/* abort() */
#ifndef _POSIX_SOURCE
#define	SIGIOT	SIGABRT	/* compatibility */
E 22
E 16
#define	SIGEMT	7	/* EMT instruction */
I 22
#endif
E 22
#define	SIGFPE	8	/* floating point exception */
D 19
#define	    FPE_INTOVF_TRAP	0x1	/* integer overflow */
#define	    FPE_INTDIV_TRAP	0x2	/* integer divide by zero */
#define	    FPE_FLTOVF_TRAP	0x3	/* floating overflow */
#define	    FPE_FLTDIV_TRAP	0x4	/* floating/decimal divide by zero */
#define	    FPE_FLTUND_TRAP	0x5	/* floating underflow */
#define	    FPE_DECOVF_TRAP	0x6	/* decimal overflow */
#define	    FPE_SUBRNG_TRAP	0x7	/* subscript out of range */
#define	    FPE_FLTOVF_FAULT	0x8	/* floating overflow fault */
#define	    FPE_FLTDIV_FAULT	0x9	/* divide by zero floating fault */
#define	    FPE_FLTUND_FAULT	0xa	/* floating underflow fault */
E 19
#define	SIGKILL	9	/* kill (cannot be caught or ignored) */
I 22
#ifndef _POSIX_SOURCE
E 22
#define	SIGBUS	10	/* bus error */
I 22
#endif
E 22
#define	SIGSEGV	11	/* segmentation violation */
I 22
#ifndef _POSIX_SOURCE
E 22
#define	SIGSYS	12	/* bad argument to system call */
I 22
#endif
E 22
#define	SIGPIPE	13	/* write on a pipe with no one to read it */
#define	SIGALRM	14	/* alarm clock */
#define	SIGTERM	15	/* software termination signal from kill */
I 22
#ifndef _POSIX_SOURCE
E 22
#define	SIGURG	16	/* urgent condition on IO channel */
I 22
#endif
E 22
#define	SIGSTOP	17	/* sendable stop signal not from tty */
#define	SIGTSTP	18	/* stop signal from tty */
#define	SIGCONT	19	/* continue a stopped process */
#define	SIGCHLD	20	/* to parent on child stop or exit */
I 16
D 22
#define	SIGCLD	SIGCHLD	/* compatibility */
E 22
E 16
#define	SIGTTIN	21	/* to readers pgrp upon background tty read */
#define	SIGTTOU	22	/* like TTIN for output if (tp->t_local&LTOSTOP) */
I 22
#ifndef _POSIX_SOURCE
E 22
#define	SIGIO	23	/* input/output possible signal */
#define	SIGXCPU	24	/* exceeded CPU time limit */
#define	SIGXFSZ	25	/* exceeded file size limit */
#define	SIGVTALRM 26	/* virtual time alarm */
#define	SIGPROF	27	/* profiling time alarm */
I 9
#define SIGWINCH 28	/* window size changes */
I 22
#define SIGINFO	29	/* information request */
#endif
E 22
I 14
#define SIGUSR1 30	/* user defined signal 1 */
#define SIGUSR2 31	/* user defined signal 2 */
E 14
E 9

I 43
#if defined(_ANSI_SOURCE) || defined(__cplusplus)
/*
 * Language spec sez we must list exactly one parameter, even though we
 * actually supply three.  Ugh!
 */
#define	SIG_DFL		(void (*)(int))0
#define	SIG_IGN		(void (*)(int))1
#define	SIG_ERR		(void (*)(int))-1
I 46
D 47
#define	_SIGARG		int		/* one int parameter */
E 47
E 46
#else
E 43
I 33
D 37
#include <sys/cdefs.h>
E 37
I 37
#define	SIG_DFL		(void (*)())0
#define	SIG_IGN		(void (*)())1
#define	SIG_ERR		(void (*)())-1
I 46
D 47
#define	_SIGARG		void	/* unspecified parameters */
E 47
E 46
I 43
#endif
E 43
E 37

I 38
#ifndef _ANSI_SOURCE
E 38
E 33
I 22
D 37
#ifndef _POSIX_SOURCE
D 33
typedef	void (*sig_t)();
E 33
I 33
typedef	void (*sig_t) __P((int));
E 33
D 25
#endif	/* _POSIX_SOURCE */
E 25
I 25
#endif

I 34
typedef int sig_atomic_t;		/* XXX should be machine dependent. */
E 37
E 34
E 25
E 22
D 33
#ifndef KERNEL
D 22
int	(*signal())();
I 2
D 4
int	(*sigvec())();
E 4
E 2
#endif
E 22
I 22
void	(*signal())();
D 25
#endif /* KERNEL */
E 25
I 25
#endif
E 25
E 22
I 2

E 33
I 22
D 23
typedef int sigset_t;
E 23
I 23
typedef unsigned int sigset_t;
E 23

I 25
D 26
#ifdef __STDC__
E 26
I 26
D 32
#if __STDC__ || c_plusplus
E 26
int sigemptyset(sigset_t *);
int sigfillset(sigset_t *);
int sigaddset(sigset_t *, int);
int sigdelset(sigset_t *, int);
int sigismember(const sigset_t *, int);
#else
int sigemptyset();
int sigfillset();
int sigaddset();
int sigdelset();
int sigismember();
#endif
E 32
I 32
D 33
#include <sys/cdefs.h>
E 32

E 33
I 32
D 37
__BEGIN_DECLS
int	sigaddset __P((sigset_t *, int));
int	sigdelset __P((sigset_t *, int));
int	sigemptyset __P((sigset_t *));
int	sigfillset __P((sigset_t *));
int	sigismember __P((const sigset_t *, int));
__END_DECLS

E 32
E 25
D 23
#define sigemptyset(set)	{ *(set) = 0; }
#define sigfillset(set)		{ *(set) = 0xffff; }
E 23
I 23
#define sigemptyset(set)	( *(set) = 0 )
D 28
#define sigfillset(set)		( *(set) = ~(sigset_t)0 )
E 28
I 28
#define sigfillset(set)		( *(set) = ~(sigset_t)0, 0 )
E 28
E 23
#define sigaddset(set, signo)	( *(set) |= 1 << ((signo) - 1), 0)
#define sigdelset(set, signo)	( *(set) &= ~(1 << ((signo) - 1)), 0)
#define sigismember(set, signo)	( (*(set) & (1 << ((signo) - 1))) != 0)

E 37
E 22
/*
I 22
 * Signal vector "template" used in sigaction call.
 */
struct	sigaction {
D 46
	void	(*sa_handler)();	/* signal handler */
E 46
I 46
D 47
	void	(*sa_handler)(_SIGARG);	/* signal handler */
E 47
I 47
	void	(*sa_handler)(int);	/* signal handler */
E 47
E 46
	sigset_t sa_mask;		/* signal mask to apply */
	int	sa_flags;		/* see signal options below */
};
#ifndef _POSIX_SOURCE
#define SA_ONSTACK	0x0001	/* take signal on signal stack */
D 34
#define SA_RESTART	0x0002	/* do not restart system on signal return */
E 34
I 34
#define SA_RESTART	0x0002	/* restart system on signal return */
I 42
#define	SA_DISABLE	0x0004	/* disable taking signals on alternate stack */
E 42
I 40
#ifdef COMPAT_SUNOS
#define	SA_USERTRAMP	0x0100	/* do not bounce off kernel's sigtramp */
#endif
E 40
E 34
D 25
#endif	/* _POSIX_SOURCE */
E 25
I 25
#endif
E 25
D 42
#define SA_NOCLDSTOP	0x0004	/* do not generate SIGCHLD on child stop */
E 42
I 42
#define SA_NOCLDSTOP	0x0008	/* do not generate SIGCHLD on child stop */
E 42

/*
 * Flags for sigprocmask:
 */
#define	SIG_BLOCK	1	/* block specified signal set */
#define	SIG_UNBLOCK	2	/* unblock specified signal set */
#define	SIG_SETMASK	3	/* set specified signal set */

D 46
#ifndef _POSIX_SOURCE
E 46
I 46
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 46
I 38
#ifndef KERNEL
#include <sys/cdefs.h>
#endif
E 38
I 37
typedef	void (*sig_t) __P((int));	/* type of signal function */

E 37
/*
I 42
 * Structure used in sigaltstack call.
 */
struct	sigaltstack {
	char	*ss_base;		/* signal stack base */
	int	ss_size;		/* signal stack length */
	int	ss_flags;		/* SA_DISABLE and/or SA_ONSTACK */
};
#define	MINSIGSTKSZ	8192			/* minimum allowable stack */
#define	SIGSTKSZ	(MINSIGSTKSZ + 32768)	/* recommended stack size */

/*
E 42
 * 4.3 compatibility:
E 22
 * Signal vector "template" used in sigvec call.
 */
struct	sigvec {
D 22
	int	(*sv_handler)();	/* signal handler */
E 22
I 22
D 46
	void	(*sv_handler)();	/* signal handler */
E 46
I 46
D 47
	void	(*sv_handler)(_SIGARG);	/* signal handler */
E 47
I 47
	void	(*sv_handler)(int);	/* signal handler */
E 47
E 46
E 22
	int	sv_mask;		/* signal mask to apply */
D 13
	int	sv_onstack;		/* if non-zero, take on signal stack */
E 13
I 13
	int	sv_flags;		/* see signal options below */
E 13
};
I 37

E 37
I 13
D 22
#define SV_ONSTACK	0x0001	/* take signal on signal stack */
#define SV_INTERRUPT	0x0002	/* do not restart system on signal return */
E 22
I 22
#define SV_ONSTACK	SA_ONSTACK
#define SV_INTERRUPT	SA_RESTART	/* same bit, opposite sense */
E 22
#define sv_onstack sv_flags	/* isn't compatibility wonderful! */
E 13
D 42

/*
I 33
 * Structure used in sigaltstack call.
 */
struct	sigaltstack {
	char	*ss_base;		/* signal stack base */
	int	ss_len;			/* signal stack length */
	int	ss_onstack;		/* current status */
};
E 42

/*
E 33
 * Structure used in sigstack call.
 */
struct	sigstack {
	char	*ss_sp;			/* signal stack pointer */
	int	ss_onstack;		/* current status */
};
E 2

/*
D 37
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
D 22
 * to the handler to allow it to properly restore state if
E 22
I 22
 * to the handler to allow it to restore state properly if
E 22
 * a non-standard exit is performed.
 */
struct	sigcontext {
D 36
	int	sc_onstack;		/* sigstack state to restore */
	int	sc_mask;		/* signal mask to restore */
I 6
	int	sc_sp;			/* sp to restore */
I 11
D 17
	int	sc_fp;			/* fp to retore */
	int	sc_ap;			/* ap to retore */
E 11
E 6
	int	sc_pc;			/* pc to retore */
E 17
I 17
	int	sc_fp;			/* fp to restore */
	int	sc_ap;			/* ap to restore */
	int	sc_pc;			/* pc to restore */
E 17
	int	sc_ps;			/* psl to restore */
E 36
I 36
#if defined(vax) || defined(tahoe) || defined(hp300) || defined(i386)
	int	sc_onstack;	/* sigstack state to restore */
	int	sc_mask;	/* signal mask to restore */
	int	sc_sp;		/* sp to restore */
	int	sc_fp;		/* fp to restore */
	int	sc_ap;		/* ap to restore */
	int	sc_pc;		/* pc to restore */
	int	sc_ps;		/* psl to restore */
#endif
#if defined(mips)
	int	sc_onstack;	/* sigstack state to restore */
	int	sc_mask;	/* signal mask to restore */
	int	sc_pc;		/* pc at time of signal */
	int	sc_regs[34];	/* processor regs 0 to 31, mullo, mullhi */
	int	sc_fpused;	/* fp has been used */
	int	sc_fpregs[33];	/* fp regs 0 to 31 and csr */
	int	sc_fpc_eir;	/* floating point exception instruction reg */
#endif
E 36
};

D 22
#define	BADSIG		(int (*)())-1
#define	SIG_DFL		(int (*)())0
#define	SIG_IGN		(int (*)())1

#ifdef KERNEL
#define	SIG_CATCH	(int (*)())2
#define	SIG_HOLD	(int (*)())3
#endif
#endif
I 8

E 22
/*
E 37
 * Macro for converting signal number to a mask suitable for
 * sigblock().
 */
#define sigmask(m)	(1 << ((m)-1))
I 22

D 35
#define	BADSIG		(void (*)())-1
#endif	/* _POSIX_SOURCE */
E 35
I 35
#define	BADSIG		SIG_ERR
D 38
#endif	/* !_POSIX_SOURCE */
E 38
E 35

D 37
#define	SIG_DFL		(void (*)())0
#define	SIG_IGN		(void (*)())1
I 34
#define	SIG_ERR		(void (*)())-1
E 34

E 37
D 33
#ifdef KERNEL
#define	SIG_CATCH	(void (*)())2
#define	SIG_HOLD	(void (*)())3
I 23

#define	sigcantmask	(sigmask(SIGKILL)|sigmask(SIGSTOP))
/*
 * get signal action for process and signal; currently only for current process
 */
#define SIGACTION(p, sig)	(u.u_signal[(sig)])
I 24

/*
 * Determine signal that should be delivered to process p, the current process,
 * 0 if none.  If there is a pending stop signal with default action,
 * the process stops in issig().
 */
#define	CURSIG(p) \
	(((p)->p_sig == 0 || \
	    ((p)->p_flag&STRC) == 0 && ((p)->p_sig &~ (p)->p_sigmask) == 0) ? \
	    0 : issig())

I 27
/*
 * Clear a pending signal from a process.
 */
#define	CLRSIG(p, sig)	{ (p)->p_sig &= ~sigmask(sig); }

E 27
I 25
#endif /* KERNEL */

E 33
I 30
D 38
#ifndef KERNEL
E 30
D 26
#ifdef __STDC__
E 26
I 26
D 32
#if __STDC__ || c_plusplus
E 32
I 29
D 30
#ifdef KERNEL
#include "types.h"
#else
E 30
D 37
#include <sys/types.h>
D 30
#endif
E 30
E 29
E 26
D 32
int kill(pid_t, int);
int sigaction(int, const struct sigaction *, struct sigaction *);
int sigprocmask(int, const sigset_t *, sigset_t *);
int sigpending(sigset_t *);
int sigsuspend(const sigset_t *);
#else
int kill();
int sigaction();
int sigprocmask();
int sigpending();
int sigsuspend();
E 32
I 32

E 37
__BEGIN_DECLS
I 33
void	(*signal __P((int, void (*) __P((int))))) __P((int));
int	raise __P((int));
#ifndef	_ANSI_SOURCE
E 33
int	kill __P((pid_t, int));
int	sigaction __P((int, const struct sigaction *, struct sigaction *));
int	sigpending __P((sigset_t *));
int	sigprocmask __P((int, const sigset_t *, sigset_t *));
int	sigsuspend __P((const sigset_t *));
E 38
I 38
#endif	/* !_POSIX_SOURCE */
E 38
I 33
#endif	/* !_ANSI_SOURCE */
I 39

/*
 * For historical reasons; programs expect signal's return value to be
 * defined by <sys/signal.h>.
 */
__BEGIN_DECLS
void	(*signal __P((int, void (*) __P((int))))) __P((int));
__END_DECLS
E 39
D 38
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
int	killpg __P((pid_t, int));
D 34
void	psignal __P((unsigned, const char *));
E 34
I 34
void	psignal __P((unsigned int, const char *));
E 34
int	sigblock __P((int));
int	siginterrupt __P((int, int));
int	sigpause __P((int));
int	sigreturn __P((struct sigcontext *));
int	sigsetmask __P((int));
int	sigstack __P((const struct sigstack *, struct sigstack *));
int	sigvec __P((int, struct sigvec *, struct sigvec *));
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */
I 37
int	sigaddset __P((sigset_t *, int));
int	sigdelset __P((sigset_t *, int));
int	sigemptyset __P((sigset_t *));
int	sigfillset __P((sigset_t *));
int	sigismember __P((const sigset_t *, int));
E 37
E 33
__END_DECLS
E 32
I 30
D 33
#endif
E 33
I 33
D 37

E 37
#endif	/* !KERNEL */
I 37

#define sigemptyset(set)	( *(set) = 0 )
#define sigfillset(set)		( *(set) = ~(sigset_t)0, 0 )
#define sigaddset(set, signo)	( *(set) |= 1 << ((signo) - 1), 0)
#define sigdelset(set, signo)	( *(set) &= ~(1 << ((signo) - 1)), 0)
#define sigismember(set, signo)	( (*(set) & (1 << ((signo) - 1))) != 0)

E 37
E 33
E 30
E 25
E 24
E 23
D 32
#endif
D 25
#endif
E 25
I 25
#endif /* NSIG */
E 32
I 32
#endif	/* !_SIGNAL_H_ */
E 38
I 38
#endif	/* !_SYS_SIGNAL_H_ */
E 38
E 32
E 25
E 22
E 8
E 1
