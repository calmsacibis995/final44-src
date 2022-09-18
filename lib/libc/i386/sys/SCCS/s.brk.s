h15265
s 00002/00002/00037
d D 8.1 93/06/04 12:41:27 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00038
d D 5.2 90/12/17 15:39:57 william 2 1
c trivial errors and GAS heartburn.
e
s 00039/00000/00000
d D 5.1 90/04/23 19:38:34 william 1 0
c date and time created 90/04/23 19:38:34 by william
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

#define	SYS_brk		17

	.globl	curbrk
	.globl	minbrk
ENTRY(_brk)
	jmp	ok

ENTRY(brk)
	movl	4(%esp),%eax
	cmpl	%eax,minbrk
D 2
	jge	ok
E 2
I 2
	jl	ok
E 2
	movl	minbrk,%eax
	movl	%eax,4(%esp)
ok:
	lea	SYS_brk,%eax
	LCALL(7,0)
	jb	err
	movl	4(%esp),%eax
	movl	%eax,curbrk
	movl	$0,%eax
	ret
err:
	jmp	cerror
E 1
