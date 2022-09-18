h15740
s 00003/00003/00038
d D 8.2 94/01/04 16:16:41 bostic 10 9
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00039
d D 8.1 93/06/02 19:54:54 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00038
d D 7.6 92/06/23 19:50:07 mckusick 8 7
c prototype for proc_reparent
e
s 00005/00000/00034
d D 7.5 92/02/05 19:52:50 torek 7 6
c add definitions for ATTACH and DETACH; 
c make provision for machine specific ptrace commands
e
s 00010/00000/00024
d D 7.4 91/02/22 10:44:32 donn 6 5
c Prototype declarations.
e
s 00018/00017/00006
d D 7.3 91/02/15 14:30:51 bostic 5 4
c add Berkeley specific copyright notice
e
s 00003/00003/00020
d D 7.2 91/02/05 17:03:54 bostic 4 3
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00022
d D 7.1 86/06/04 23:26:54 mckusick 3 2
c 4.3BSD release version
e
s 00007/00001/00016
d D 5.1 85/05/30 09:39:19 dist 2 1
c Add copyright
e
s 00017/00000/00000
d D 4.1 84/04/11 09:15:04 ralph 1 0
c date and time created 84/04/11 09:15:04 by ralph
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 5
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
E 3
I 3
 * Copyright (c) 1980, 1986 Regents of the University of California.
E 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 9
 * Copyright (c) 1984 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1984, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
E 5
 *
I 5
 * %sccs.include.redist.c%
 *
E 5
 *	%W% (Berkeley) %G%
 */
E 2

D 4
#ifndef _PTRACE_
#define _PTRACE_
E 4
I 4
D 5
#ifndef _PTRACE_H_
#define _PTRACE_H_
E 5
I 5
D 10
#ifndef	_PTRACE_H_
#define	_PTRACE_H_
E 10
I 10
#ifndef	_SYS_PTRACE_H_
#define	_SYS_PTRACE_H_
E 10
E 5
E 4

D 5
#define PT_TRACE_ME	0	/* child declares it's being traced */
#define PT_READ_I	1	/* read word in child's I space */
#define PT_READ_D	2	/* read word in child's D space */
#define PT_READ_U	3	/* read word in child's user structure */
#define PT_WRITE_I	4	/* write word in child's I space */
#define PT_WRITE_D	5	/* write word in child's D space */
#define PT_WRITE_U	6	/* write word in child's user structure */
#define PT_CONTINUE	7	/* continue the child */
#define PT_KILL		8	/* kill the child process */
#define PT_STEP		9	/* single step the child */
E 5
I 5
#define	PT_TRACE_ME	0	/* child declares it's being traced */
#define	PT_READ_I	1	/* read word in child's I space */
#define	PT_READ_D	2	/* read word in child's D space */
#define	PT_READ_U	3	/* read word in child's user structure */
#define	PT_WRITE_I	4	/* write word in child's I space */
#define	PT_WRITE_D	5	/* write word in child's D space */
#define	PT_WRITE_U	6	/* write word in child's user structure */
#define	PT_CONTINUE	7	/* continue the child */
#define	PT_KILL		8	/* kill the child process */
#define	PT_STEP		9	/* single step the child */
I 7
#define	PT_ATTACH	10	/* trace some running process */
#define	PT_DETACH	11	/* stop tracing a process */

#define	PT_FIRSTMACH	32	/* for machine-specific requests */
#include <machine/ptrace.h>	/* machine-specific requests, if any */
E 7
E 5

I 6
D 8
#ifndef KERNEL
E 8
I 8
#ifdef KERNEL
void	proc_reparent __P((struct proc *child, struct proc *newparent));
#else /* !KERNEL */
E 8

#include <sys/cdefs.h>

__BEGIN_DECLS
int	ptrace __P((int _request, pid_t _pid, caddr_t _addr, int _data));
__END_DECLS

#endif /* !KERNEL */

E 6
D 4
#endif
E 4
I 4
D 5
#endif /* !_PTRACE_H_ */
E 5
I 5
D 10
#endif	/* !_PTRACE_H_ */
E 10
I 10
#endif	/* !_SYS_PTRACE_H_ */
E 10
E 5
E 4
E 1
