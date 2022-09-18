h07995
s 00002/00002/00020
d D 8.1 93/06/04 12:36:33 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00020
d D 5.2 90/08/06 10:25:10 hibler 2 1
c store the mask where the argument points not in the arg itself
e
s 00021/00000/00000
d D 5.1 90/05/12 16:51:53 bostic 1 0
c date and time created 90/05/12 16:51:53 by bostic
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

SYSCALL(sigpending)
D 2
	movl	d0,sp@(4)
E 2
I 2
	movl	sp@(4),a0
	movl	d0,a0@
E 2
	clrl	d0
	rts
E 1
