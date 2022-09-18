h08227
s 00002/00002/00037
d D 8.1 93/06/04 12:41:57 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00039/00000/00000
d D 5.1 90/04/23 19:39:31 william 1 0
c date and time created 90/04/23 19:39:31 by william
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

#define	SYS_brk		17

	.globl	_end
	.globl	minbrk
	.globl	curbrk

	.data
minbrk:	.long	_end
curbrk:	.long	_end
	.text

ENTRY(sbrk)
	movl	4(%esp),%ecx
	movl	curbrk,%eax
	addl	%eax,4(%esp)
	lea	SYS_brk,%eax
	LCALL(7,0)
	jb	err
	movl	curbrk,%eax
	addl	%ecx,curbrk
	ret
err:
	jmp	cerror
E 1
