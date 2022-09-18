h47065
s 00002/00002/00022
d D 8.1 93/06/10 21:45:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/00019
d D 7.4 92/12/27 09:28:14 hibler 4 3
c many MD flags moved here from sys/proc.h and include/pcb.h
e
s 00001/00001/00018
d D 7.3 92/02/05 18:15:21 mckusick 3 2
c keep the offsets the same in the proc structure
e
s 00001/00003/00018
d D 7.2 92/02/05 16:30:18 mckusick 2 1
c p_regs moves to p_md.md_regs
e
s 00021/00000/00000
d D 7.1 91/05/15 11:38:22 mckusick 1 0
c date and time created 91/05/15 11:38:22 by mckusick
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1991 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Machine-dependent part of the proc structure for hp300.
 */
struct mdproc {
D 3
	int	md_flags;		/* machine-dependent flags */
E 3
D 2
#ifdef notyet
	int	*p_regs;		/* registers on current frame */
#endif
E 2
I 2
	int	*md_regs;		/* registers on current frame */
I 3
	int	md_flags;		/* machine-dependent flags */
E 3
E 2
};

/* md_flags */
#define	MDP_AST		0x0001	/* async trap pending */
I 4
#define	MDP_HPUX	0x0002	/* HP-UX process */
#define	MDP_HPUXTRACE	0x0004	/* being traced by HP-UX process */
#define	MDP_HPUXMMAP	0x0008	/* VA space is multiply mapped */
#define MDP_CCBDATA	0x0010	/* copyback caching of data (68040) */
#define MDP_CCBSTACK	0x0020	/* copyback caching of stack (68040) */
E 4
E 1
