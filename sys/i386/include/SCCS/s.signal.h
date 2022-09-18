h43676
s 00002/00002/00033
d D 8.2 95/05/03 22:01:17 mckusick 3 2
c more POSIX and ANSI compliance (from karels)
e
s 00002/00002/00033
d D 8.1 93/06/11 15:48:38 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00035/00000/00000
d D 7.1 91/09/08 12:24:18 karels 1 0
c split from sys/signal.h
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1986, 1989, 1991 Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine-dependent signal definitions
 */

typedef int sig_atomic_t;

D 3
#ifndef _POSIX_SOURCE
E 3
I 3
#if !defined(_POSIX_SOURCE) && !defined(_ANSI_SOURCE)
E 3
#include <machine/trap.h>	/* codes for SIGILL, SIGFPE */
D 3
#endif
E 3

/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to restore state properly if
 * a non-standard exit is performed.
 */
struct	sigcontext {
	int	sc_onstack;	/* sigstack state to restore */
	int	sc_mask;	/* signal mask to restore */
	int	sc_sp;		/* sp to restore */
	int	sc_fp;		/* fp to restore */
	int	sc_ap;		/* ap to restore */
	int	sc_pc;		/* pc to restore */
	int	sc_ps;		/* psl to restore */
};
I 3
#endif
E 3
E 1
