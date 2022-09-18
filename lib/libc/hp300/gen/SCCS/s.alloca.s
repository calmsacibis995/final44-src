h23931
s 00002/00002/00026
d D 8.1 93/06/04 12:23:03 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00000/00000
d D 5.1 90/05/12 15:47:29 bostic 1 0
c date and time created 90/05/12 15:47:29 by bostic
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

/* like alloc, but automatic free in return */

#include "DEFS.h"

ENTRY(alloca)
	movl	sp@,a0		/* save return addr */
	movl	sp,d0		/* get current SP value */
	subl	sp@(4),d0	/* allocate requested space */
	andb	#~3,d0		/* longword align for efficiency */
	addql	#8,d0		/* reuse space of call frame */
	movl	d0,sp		/* set new SP value */
	lea	sp@(-4),sp	/* account for argument pop in caller */
	jmp 	a0@		/* funny return */
E 1
