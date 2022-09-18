h55809
s 00002/00002/00017
d D 8.1 93/06/11 15:48:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00000/00000
d D 5.1 92/02/05 16:32:47 mckusick 1 0
c date and time created 92/02/05 16:32:47 by mckusick
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
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine-dependent part of the proc structure for hp300.
 */
struct mdproc {
	int	md_flags;		/* machine-dependent flags */
	int	*md_regs;		/* registers on current frame */
};

/* md_flags */
#define	MDP_AST		0x0001	/* async trap pending */
E 1
