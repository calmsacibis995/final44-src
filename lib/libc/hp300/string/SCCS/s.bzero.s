h11802
s 00002/00002/00050
d D 8.1 93/06/04 12:35:21 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00052/00000/00000
d D 5.1 90/05/12 16:16:13 bostic 1 0
c date and time created 90/05/12 16:16:13 by bostic
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

/*
 * This is probably not the best we can do, but it is still much
 * faster than the C version in the portable gen directory.
 *
 * Things that might help:
 *	- unroll the longword loop (might not be good for a 68020)
 *	- longword, as opposed to word, align when possible (only on the 68020)
 *	- use nested DBcc instructions or use one and limit size to 64K
 */
ENTRY(bzero)
	movl	sp@(4),a0	/* destination */
	movl	sp@(8),d0	/* count */
	jeq	bzdone		/* nothing to do */
	movl	a0,d1
	btst	#0,d1		/* address odd? */
	jeq	bzeven		/* no, skip alignment */
	clrb	a0@+		/* yes, clear a byte */
	subql	#1,d0		/* adjust count */
	jeq	bzdone		/* if zero, all done */
bzeven:
	movl	d0,d1
	lsrl	#2,d1		/* convert to longword count */
	jeq	bzbloop		/* no longwords, skip loop */
bzlloop:
	clrl	a0@+		/* clear a longword */
	subql	#1,d1		/* adjust count */
	jne	bzlloop		/* still more, keep going */
	andl	#3,d0		/* what remains */
	jeq	bzdone		/* nothing, all done */
bzbloop:
	clrb	a0@+		/* clear a byte */
	subql	#1,d0		/* adjust count */
	jne	bzbloop		/* still more, keep going */
bzdone:
	rts
E 1
