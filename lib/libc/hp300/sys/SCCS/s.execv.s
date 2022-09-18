h53210
s 00026/00000/00000
d D 5.1 90/05/12 16:51:40 bostic 1 0
c date and time created 90/05/12 16:51:40 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
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

ENTRY(execv)
	.globl	_environ
	lea	sp@(4),a0
	movl	_environ,sp@-
	movl	a0@(4),sp@-
	movl	a0@,sp@-
	jbsr	_execve
	addl	#12,sp
	rts			/* execv(file, argv) */
E 1
