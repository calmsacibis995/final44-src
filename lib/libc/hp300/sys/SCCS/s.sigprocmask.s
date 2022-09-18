h38242
s 00002/00002/00039
d D 8.1 93/06/04 12:36:37 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00040
d D 5.2 90/06/06 09:52:15 bostic 2 1
c add .even to guarantee jmp instruction is on even address
e
s 00040/00000/00000
d D 5.1 90/05/12 16:51:54 bostic 1 0
c date and time created 90/05/12 16:51:54 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

I 2
	.even
E 2
err:
	jmp	cerror

ENTRY(sigprocmask)
	tstl	sp@(8)			/* check new sigset pointer */
	jne	gotptr			/* if not null, indirect */
/*	movl	#0,sp@(8)		/* null mask pointer: block empty set */
	movl	#1,sp@(4)		/* SIG_BLOCK */
	jra	doit
gotptr:
	movl	sp@(8),a0
	movl	a0@,sp@(8)		/* indirect to new mask arg */
doit:
	movl	#SYS_sigprocmask,d0
	trap	#0
	jcs	err
	tstl	sp@(12)			/* test if old mask requested */
	jeq	out
	movl	sp@(12),a0
	movl	d0,a0@			/* store old mask */
out:
	clrl	d0
	rts
E 1
