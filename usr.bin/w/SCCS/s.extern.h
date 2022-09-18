h47432
s 00002/00002/00011
d D 8.1 93/06/06 22:23:00 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00000/00000
d D 5.1 93/04/27 15:19:53 bostic 1 0
c date and time created 93/04/27 15:19:53 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct proc;
void	pr_attime __P((time_t *, time_t *));
void	pr_idle __P((time_t));
int	proc_compare __P((struct proc *, struct proc *));
E 1
