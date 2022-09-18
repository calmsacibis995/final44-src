h30892
s 00002/00002/00040
d D 8.1 93/06/04 13:02:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00042/00000/00000
d D 5.1 92/06/25 06:37:54 torek 1 0
c date and time created 92/06/25 06:37:54 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: brk.s,v 1.3 92/06/25 12:56:05 mccanne Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

	.globl	curbrk
	.globl	minbrk

	.data
minbrk:	.long	_end			! lower brk limit; also for gmon code
	.text

ENTRY(brk)
	sethi	%hi(minbrk), %o1	! %o1 = minbrk
	ld	[%o1 + %lo(minbrk)], %o1
	cmp	%o1, %o0		! if (minbrk > %o0)
	bg,a	0f
	 mov	%o1, %o0		!	%o0 = minbrk
0:
	mov	%o0, %o2		! save argument to syscall
	mov	SYS_break, %g1
	t	ST_SYSCALL
	bcc,a	1f
	 sethi	%hi(curbrk), %g1
	ERROR()
1:
	retl				! success, return 0 & record new break
	 st	%o2, [%g1 + %lo(curbrk)]
E 1
