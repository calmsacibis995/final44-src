h51630
s 00002/00002/00041
d D 8.1 93/06/04 12:35:40 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00043/00000/00000
d D 5.1 90/05/12 16:16:29 bostic 1 0
c date and time created 90/05/12 16:16:29 by bostic
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
 * NOTE: this guy returns result compatible with the VAX assembly version.
 * The C version on the portable gen directory returns different results
 * (different signs!) when comparing chars with the high bit on.  Who is
 * right??
 */
ENTRY(strncmp)
	movl	sp@(12),d1	/* count */
	jeq	scdone		/* nothing to do */
	movl	sp@(4),a0	/* a0 = string1 */
	movl	sp@(8),a1	/* a1 = string2 */
scloop:
	movb	a0@+,d0		/* get *string1 */
	cmpb	a1@+,d0		/* compare a byte */
	jne	scexit		/* not equal, break out */
	tstb	d0		/* at end of string1? */
	jeq	scdone		/* yes, all done */
	subql	#1,d1		/* no, adjust count */
	jne	scloop		/* more to do, keep going */
scdone:
	moveq	#0,d0		/* strings are equal */
	rts
scexit:
	subb	a1@-,d0		/* *string1 - *string2 */
	extbl	d0
	rts
E 1
