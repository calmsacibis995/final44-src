h55892
s 00004/00000/00034
d D 8.2 95/05/03 22:02:40 mckusick 3 2
c more POSIX and ANSI compliance (from karels)
e
s 00002/00002/00032
d D 8.1 93/06/10 23:03:00 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 7.1 92/01/07 20:35:53 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine-dependent signal definitions
 */

typedef int sig_atomic_t;

I 3
#if !defined(_POSIX_SOURCE) && !defined(_ANSI_SOURCE)
#include <machine/trap.h>	/* codes for SIGILL, SIGFPE */

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
	int	sc_pc;		/* pc at time of signal */
	int	sc_regs[34];	/* processor regs 0 to 31, mullo, mullhi */
	int	sc_fpused;	/* fp has been used */
	int	sc_fpregs[33];	/* fp regs 0 to 31 and csr */
	int	sc_fpc_eir;	/* floating point exception instruction reg */
};
I 3
#endif
E 3
E 1
