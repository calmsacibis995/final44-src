h18825
s 00002/00002/00028
d D 8.1 93/06/04 12:35:29 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 5.1 90/05/12 16:16:20 bostic 1 0
c date and time created 90/05/12 16:16:20 by bostic
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

ENTRY(rindex)
	movl	sp@(4),a0	/* string */
	movb	sp@(11),d0	/* char to look for */
	subl	a1,a1		/* clear rindex pointer */
rixloop:
	cmpb	a0@,d0		/* found our char? */
	jne	rixnope		/* no, check for null */
	movl	a0,a1		/* yes, remember location */
rixnope:
	tstb	a0@+		/* null? */
	jne	rixloop		/* no, keep going */
	movl	a1,d0		/* return value */
	rts
E 1
