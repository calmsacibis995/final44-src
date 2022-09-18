h10728
s 00002/00002/00017
d D 8.1 93/06/10 22:38:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00015
d D 7.3 92/11/15 15:49:07 ralph 3 2
c changes for maxine from Rick Macklem.
e
s 00001/00001/00018
d D 7.2 92/02/29 17:26:17 ralph 2 1
c change function return to void
e
s 00019/00000/00000
d D 7.1 92/01/07 18:29:21 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1992 Regents of the University of California.
E 3
I 3
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
E 3
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
D 3
 * Ralph Campbell.
E 3
I 3
 * Ralph Campbell and Rick Macklem.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct pdma {
D 3
	dcregs	*p_addr;
E 3
I 3
	void	*p_addr;
E 3
	char	*p_mem;
	char	*p_end;
	int	p_arg;
D 2
	int	(*p_fcn)();
E 2
I 2
	void	(*p_fcn)();
E 2
};
E 1
