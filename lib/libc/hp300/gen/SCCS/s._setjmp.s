h06054
s 00002/00002/00058
d D 8.1 93/06/04 12:22:42 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00060/00000/00000
d D 5.1 90/05/12 15:47:25 bostic 1 0
c date and time created 90/05/12 15:47:25 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
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
 * C library -- _setjmp, _longjmp
 *
 *	_longjmp(a,v)
 * will generate a "return(v)" from
 * the last call to
 *	_setjmp(a)
 * by restoring registers from the stack,
 * The previous signal state is NOT restored.
 */

#include "DEFS.h"

ENTRY(_setjmp)
	movl	sp@(4),a0	/* save area pointer */
	clrl	a0@+		/* no old onstack */
	clrl	a0@+		/* no old sigmask */
	movl	sp,a0@+		/* save old SP */
	movl	a6,a0@+		/* save old FP */
	clrl	a0@+		/* no old AP */
	movl	sp@,a0@+	/* save old PC */
	clrl	a0@+		/* clear PS */
	moveml	#0x3CFC,a0@	/* save other non-scratch regs */
	clrl	d0		/* return zero */
	rts

ENTRY(_longjmp)
	movl	sp@(4),a0	/* save area pointer */
	addql	#8,a0		/* skip onstack/sigmask */
	tstl	a0@		/* ensure non-zero SP */
	jeq	botch		/* oops! */
	movl	sp@(8),d0	/* grab return value */
	jne	ok		/* non-zero ok */
	moveq	#1,d0		/* else make non-zero */
ok:
	movl	a0@+,sp		/* restore SP */
	movl	a0@+,a6		/* restore FP */
	addql	#4,a0		/* skip AP */
	movl	a0@+,sp@	/* restore PC */
	moveml	a0@(4),#0x3CFC	/* restore non-scratch regs */
	rts

botch:
	jsr	_longjmperror
	stop	#0
E 1
