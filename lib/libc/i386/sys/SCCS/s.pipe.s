h58452
s 00002/00002/00020
d D 8.1 93/06/04 12:41:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00000/00000
d D 5.1 90/04/23 19:39:21 william 1 0
c date and time created 90/04/23 19:39:21 by william
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
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */

#include "SYS.h"

SYSCALL(pipe)
	movl	4(%esp),%ecx
	movl	%eax,(%ecx)
	movl	%edx,4(%ecx)
	movl	$0,%eax
	ret
E 1
