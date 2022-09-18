h47143
s 00002/00002/00017
d D 8.1 93/06/10 21:40:49 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00000/00000
d D 7.1 90/05/08 17:51:17 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct isr {
	struct	isr *isr_forw;
	struct	isr *isr_back;
	int	(*isr_intr)();
	int	isr_arg;
	int	isr_ipl;
};

#define	NISR		3
#define	ISRIPL(x)	((x) - 3)
E 1
