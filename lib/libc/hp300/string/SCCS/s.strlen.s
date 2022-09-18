h04286
s 00002/00002/00023
d D 8.1 93/06/04 12:35:38 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 90/05/12 16:16:27 bostic 1 0
c date and time created 90/05/12 16:16:27 by bostic
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

ENTRY(strlen)
	moveq	#-1,d0
	movl	sp@(4),a0	/* string */
slloop:
	addql	#1,d0		/* increment count */
	tstb	a0@+		/* null? */
	jne	slloop		/* no, keep going */
	rts
E 1
