h40180
s 00002/00002/00037
d D 8.1 93/06/04 13:02:38 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00037
d D 5.2 92/07/01 18:00:00 torek 2 1
c do not clobber errno on failed sbrk
e
s 00039/00000/00000
d D 5.1 92/06/25 06:37:59 torek 1 0
c date and time created 92/06/25 06:37:59 by torek
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: $Header: sbrk.s,v 1.1 91/07/06 13:05:59 torek Exp $
E 2
I 2
 * from: $Header: sbrk.s,v 1.3 92/07/02 00:56:49 torek Exp $
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

	.globl	_end
	.globl	curbrk

	.data
curbrk:	.long	_end
	.text

ENTRY(sbrk)
	sethi	%hi(curbrk), %o2
	ld	[%o2 + %lo(curbrk)], %o3	! %o3 = old break
	add	%o3, %o0, %o4			! %o4 = new break
	mov	%o4, %o0			! copy for syscall
	mov	SYS_break, %g1
	t	ST_SYSCALL			! break(new_break)
D 2
	bcc	1f				! if success,
E 2
I 2
	bcc,a	1f				! if success,
E 2
	 mov	%o3, %o0			!    set return value
	ERROR()
1:
	retl					! and update curbrk
	 st	%o4, [%o2 + %lo(curbrk)]
E 1
