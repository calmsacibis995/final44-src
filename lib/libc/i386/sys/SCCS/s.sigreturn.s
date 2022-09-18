h23499
s 00002/00002/00026
d D 8.1 93/06/04 12:42:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00026
d D 5.2 90/12/17 15:40:01 william 2 1
c trivial errors and GAS heartburn.
e
s 00028/00000/00000
d D 5.1 90/04/23 19:39:49 william 1 0
c date and time created 90/04/23 19:39:49 by william
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

/*
 * We must preserve the state of the registers as the user has set them up.
 */
#ifdef PROF
#undef ENTRY
#define	ENTRY(x) \
D 2
	.globl _/**/x; .align 4; _/**/x:  pusha ; \
	.data; 1:; .long 0; .text; movl $1b,%eax; call mcount; popa
E 2
I 2
	.globl _/**/x; .align 2; _/**/x:  pusha ; \
	.data; 1:; .long 0; .text; movl $1b,%eax; call mcount; popa ; nop
E 2
#endif /* PROF */

SYSCALL(sigreturn)
	ret
E 1
