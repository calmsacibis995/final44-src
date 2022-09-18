h61902
s 00002/00002/00064
d D 8.1 93/06/04 12:24:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00061
d D 5.2 92/05/28 18:17:27 mckusick 3 1
c replace sigstack with sigaltstack
e
s 00004/00003/00062
d R 5.2 92/05/28 17:10:25 mckusick 2 1
c replace sigstack with sigaltstack
e
s 00065/00000/00000
d D 5.1 90/05/12 15:47:41 bostic 1 0
c date and time created 90/05/12 15:47:41 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

/*
 * C library -- setjmp, longjmp
 *
 *	longjmp(a,v)
 * will generate a "return(v)" from
 * the last call to
 *	setjmp(a)
 * by restoring registers from the stack,
 * and a struct sigcontext, see <signal.h>
 */

#include "DEFS.h"

ENTRY(setjmp)
D 3
	subql	#8,sp		/* space for sigstack args/rvals */
E 3
I 3
	subl	#12,sp		/* space for sigaltstack args/rvals */
E 3
	clrl	sp@		/* don't change it... */
	movl	sp,sp@(4)	/* ...but return the current val */
D 3
	jsr	_sigstack	/* note: onstack returned in sp@(4) */
E 3
I 3
	jsr	_sigaltstack	/* note: onstack returned in sp@(8) */
E 3
	clrl	sp@		/* don't change mask, just return */
	jsr	_sigblock	/*   old value */
D 3
	movl	sp@(4),d1	/* old onstack value */
	addql	#8,sp
E 3
I 3
	movl	sp@(8),d1	/* old onstack value */
	andl	#1,d1		/* extract onstack flag */
	addl	#12,sp
E 3
	movl	sp@(4),a0	/* save area pointer */
	movl	d1,a0@+		/* save old onstack value */
	movl	d0,a0@+		/* save old signal mask */
	lea	sp@(4),a1	/* adjust saved SP since we won't rts */
	movl	a1,a0@+		/* save old SP */
	movl	a6,a0@+		/* save old FP */
	clrl	a0@+		/* no AP */
	movl	sp@,a0@+	/* save old PC */
	clrl	a0@+		/* clean PS */
	moveml	#0x3CFC,a0@	/* save remaining non-scratch regs */
	clrl	d0		/* return 0 */
	rts

ENTRY(longjmp)
	movl	sp@(4),a0	/* save area pointer */
	tstl	a0@(8)		/* ensure non-zero SP */
	jeq	botch		/* oops! */
	movl	sp@(8),d0	/* grab return value */
	jne	ok		/* non-zero ok */
	moveq	#1,d0		/* else make non-zero */
ok:
	moveml	a0@(28),#0x3CFC	/* restore non-scratch regs */
	movl	a0,sp@-		/* let sigreturn */
	jsr	_sigreturn	/*   finish for us */

botch:
	jsr	_longjmperror
	stop	#0
E 1
