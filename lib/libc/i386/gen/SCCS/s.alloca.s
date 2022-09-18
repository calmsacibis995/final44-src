h33775
s 00002/00002/00029
d D 8.1 93/06/04 12:38:54 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00027
d D 5.2 90/05/14 15:16:06 karels 2 1
c Release 0.1 changes
e
s 00030/00000/00000
d D 5.1 90/04/23 19:56:49 william 1 0
c date and time created 90/04/23 19:56:49 by william
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

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/* like alloc, but automatic automatic free in return */

#include "DEFS.h"

ENTRY(alloca)
D 2
	popl	%edx

E 2
	popl	%edx		/*  pop return addr */
	popl	%eax		/*  pop amount to allocate */
	movl	%esp,%ecx
D 2
	addl	$3,%eax		/*  round up to next word, compensate for arg */
E 2
I 2
	addl	$3,%eax		/*  round up to next word */
E 2
	andl	$0xfffffffc,%eax
	subl	%eax,%esp
I 2
	movl	%esp,%eax	/* base of newly allocated space */
E 2
	pushl	8(%ecx)		/* copy possible saved registers */
	pushl	4(%ecx)
	pushl	0(%ecx)
	pushl	%eax		/* dummy to pop at callsite */
	jmp	%edx		/* "return" */
E 1
