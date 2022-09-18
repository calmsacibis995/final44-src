h30065
s 00002/00002/00024
d D 8.1 93/06/10 23:02:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00025
d D 7.3 92/02/29 17:51:07 ralph 3 2
c added md_regs field
e
s 00002/00000/00023
d D 7.2 92/02/29 14:44:40 ralph 2 1
c add support for single step for ptrace()
e
s 00023/00000/00000
d D 7.1 92/01/07 20:35:51 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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
I 3
	int	*md_regs;		/* registers on current frame */
E 3
	int	md_flags;		/* machine-dependent flags */
	int	md_upte[UPAGES];	/* ptes for mapping u page */
I 2
	int	md_ss_addr;		/* single step address for ptrace */
	int	md_ss_instr;		/* single step instruction for ptrace */
E 2
};

/* md_flags */
#define	MDP_FPUSED	0x0001	/* floating point coprocessor used */
#define	MDP_ULTRIX	0x0002	/* ULTRIX process (ULTRIXCOMPAT) */
E 1
