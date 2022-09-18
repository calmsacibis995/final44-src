h13876
s 00002/00002/00026
d D 8.1 93/06/04 12:42:11 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00027
d D 5.2 90/12/17 15:39:59 william 2 1
c trivial errors and GAS heartburn.
e
s 00028/00000/00000
d D 5.1 90/07/01 00:05:15 bostic 1 0
c date and time created 90/07/01 00:05:15 by bostic
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
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */

#include "SYS.h"

err:
	jmp	cerror

ENTRY(sigsuspend)
	movl	4(%esp),%eax		# fetch mask arg
	movl	(%eax),%eax		# indirect to mask arg
	movl	%eax,4(%esp)
	movl	$ SYS_sigsuspend ,%eax
	LCALL(0x7,0)
	jb	err
D 2
	xorl	%eax,%eax		# shouldn't happen
E 2
I 2
	xorl	%eax,%eax		# shouldn t happen
E 2
	ret
E 1
