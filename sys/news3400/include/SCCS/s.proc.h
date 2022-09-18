h17985
s 00002/00002/00024
d D 8.1 93/06/11 14:58:56 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00000/00000
d D 7.1 92/06/04 16:03:07 mckusick 1 0
c initial port from Kazumasa Utashiro
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
 * Machine-dependent part of the proc structure for DEC Station.
 */
struct mdproc {
	int	*md_regs;		/* registers on current frame */
	int	md_flags;		/* machine-dependent flags */
	int	md_upte[UPAGES];	/* ptes for mapping u page */
	int	md_ss_addr;		/* single step address for ptrace */
	int	md_ss_instr;		/* single step instruction for ptrace */
};

/* md_flags */
#define	MDP_FPUSED	0x0001	/* floating point coprocessor used */
#define	MDP_ULTRIX	0x0002	/* ULTRIX process (ULTRIXCOMPAT) */
E 1
