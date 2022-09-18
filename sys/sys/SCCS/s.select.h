h61034
s 00003/00003/00027
d D 8.2 94/01/04 16:16:46 bostic 7 6
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00028
d D 8.1 93/06/02 19:55:08 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00028
d D 7.5 92/02/20 11:37:25 mckusick 5 4
c #ifdef KERNEL around function prototypes
e
s 00003/00000/00026
d D 7.4 92/02/19 08:28:37 bostic 4 3
c add structure def's for gcc
e
s 00005/00000/00021
d D 7.3 92/02/18 09:25:48 bostic 3 2
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00000/00003/00021
d D 7.2 92/02/17 23:46:44 mckusick 2 1
c get rid of #ifdef KERNEL
e
s 00024/00000/00000
d D 7.1 92/02/17 23:46:01 mckusick 1 0
c date and time created 92/02/17 23:46:01 by mckusick
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 3
D 7
#ifndef _SELECT_H_
#define	_SELECT_H_
E 7
I 7
#ifndef _SYS_SELECT_H_
#define	_SYS_SELECT_H_
E 7

E 3
D 2
#ifdef KERNEL
E 2
/*
 * Used to maintain information about processes that wish to be
 * notified when I/O becomes possible.
 */
struct selinfo {
	pid_t	si_pid;		/* process to be notified */
	short	si_flags;	/* see below */
};
#define	SI_COLL	0x0001		/* collision occurred */

I 5
#ifdef KERNEL
E 5
I 4
struct proc;
D 5
struct selinfo;
E 5

E 4
void	selrecord __P((struct proc *selector, struct selinfo *));
void	selwakeup __P((struct selinfo *));
I 5
#endif
E 5
I 3

D 7
#endif /* !_SELECT_H_ */
E 7
I 7
#endif /* !_SYS_SELECT_H_ */
E 7
E 3
D 2

#endif	/* KERNEL */
E 2
E 1
