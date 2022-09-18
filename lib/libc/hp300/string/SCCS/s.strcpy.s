h08804
s 00002/00002/00023
d D 8.1 93/06/04 12:35:35 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 90/05/12 16:16:25 bostic 1 0
c date and time created 90/05/12 16:16:25 by bostic
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

ENTRY(strcpy)
	movl	sp@(8),a0		/* a0 = fromaddr */
	movl	sp@(4),d0		/* return value is toaddr */
	movl	d0,a1			/* a1 = toaddr */
scloop:
	movb	a0@+,a1@+		/* copy a byte */
	jne	scloop			/* copied non-null, keep going */
	rts
E 1
