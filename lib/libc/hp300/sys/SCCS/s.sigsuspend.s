h15632
s 00002/00002/00027
d D 8.1 93/06/04 12:36:43 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00028
d D 5.2 90/06/06 09:52:16 bostic 2 1
c add .even to guarantee jmp instruction is on even address
e
s 00028/00000/00000
d D 5.1 90/05/12 16:51:57 bostic 1 0
c date and time created 90/05/12 16:51:57 by bostic
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

ENTRY(sigsuspend)
	movl	sp@(4),a0
	movl	a0@,sp@(4)		/* indirect to mask arg */
	movl	#SYS_sigsuspend,d0
	trap	#0
	jcs	err
	clrl	d0			/* shouldn't happen */
	rts
E 1
