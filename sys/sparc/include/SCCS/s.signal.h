h48009
s 00004/00000/00064
d D 8.2 95/05/03 22:04:49 mckusick 6 5
c more POSIX and ANSI compliance (from karels)
e
s 00002/00002/00062
d D 8.1 93/06/11 15:12:45 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00062
d D 7.4 93/05/16 22:05:35 torek 4 3
c add sig_atomic_t
e
s 00002/00002/00060
d D 7.3 93/04/20 18:54:42 torek 3 2
c spelling
e
s 00005/00000/00057
d D 7.2 92/07/21 16:41:39 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00057/00000/00000
d D 7.1 92/07/13 00:43:07 torek 1 0
c date and time created 92/07/13 00:43:07 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: signal.h,v 1.4 92/06/17 06:10:28 torek Exp $
E 3
I 3
 * from: $Header: signal.h,v 1.5 92/11/26 02:04:46 torek Exp $
E 3
 */

#ifndef LOCORE
I 4
typedef int sig_atomic_t;

I 6
#if !defined(_POSIX_SOURCE) && !defined(_ANSI_SOURCE)
E 6
E 4
/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to restore state properly if
 * a non-standard exit is performed.
 *
 * All machines must have an sc_onstack and sc_mask.
 */
struct sigcontext {
	int	sc_onstack;		/* sigstack state to restore */
	int	sc_mask;		/* signal mask to restore */
	/* begin machine dependent portion */
	int	sc_sp;			/* %sp to restore */
	int	sc_pc;			/* pc to restore */
	int	sc_npc;			/* npc to restore */
	int	sc_psr;			/* psr to restore */
	int	sc_g1;			/* %g1 to restore */
	int	sc_o0;			/* %o0 to restore */
};
I 6
#endif
E 6
#else /* LOCORE */
#define	SC_SP_OFFSET	8
#define	SC_PC_OFFSET	12
#define	SC_NPC_OFFSET	16
#define	SC_PSR_OFFSET	20
#define	SC_G1_OFFSET	24
#define	SC_O0_OFFSET	28
#endif /* LOCORE */

I 6
#if !defined(_POSIX_SOURCE) && !defined(_ANSI_SOURCE)
E 6
/*
 * `Code' arguments to signal handlers.  The names, and the funny numbering.
 * are defined so as to match up with what SunOS uses; I have no idea why
 * they did the numbers that way, except maybe to match up with the 68881.
 */
#define	FPE_INTOVF_TRAP		0x01	/* integer overflow */
#define	FPE_INTDIV_TRAP		0x14	/* integer divide by zero */
#define	FPE_FLTINEX_TRAP	0xc4	/* inexact */
#define	FPE_FLTDIV_TRAP		0xc8	/* divide by zero */
#define	FPE_FLTUND_TRAP		0xcc	/* underflow */
#define	FPE_FLTOPERR_TRAP	0xd0	/* operand error */
#define	FPE_FLTOVF_TRAP		0xd4	/* overflow */
I 6
#endif
E 6
E 1
