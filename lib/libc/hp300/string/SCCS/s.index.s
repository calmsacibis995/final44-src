h16317
s 00002/00002/00028
d D 8.1 93/06/04 12:35:27 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 5.1 90/05/12 16:16:17 bostic 1 0
c date and time created 90/05/12 16:16:17 by bostic
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

#include "DEFS.h"

ENTRY(index)
	movl	sp@(4),a0	/* string */
	movb	sp@(11),d0	/* char to look for */
ixloop:
	cmpb	a0@,d0		/* found our char? */
	jeq	ixfound		/* yes, break out */
	tstb	a0@+		/* null? */
	jne	ixloop		/* no, keep going */
	moveq	#0,d0		/* not found, return null */
	rts
ixfound:
	movl	a0,d0		/* found, return pointer */
	rts
E 1
