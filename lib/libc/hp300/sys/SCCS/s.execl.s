h50224
s 00024/00000/00000
d D 5.1 90/05/12 16:51:35 bostic 1 0
c date and time created 90/05/12 16:51:35 by bostic
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

ENTRY(execl)
	lea	sp@(4),a0
	pea	a0@(4)
	movl	a0@,sp@-
	jbsr	_execv
	addql	#8,sp
	rts		/* execl(file, arg1, arg2, ..., 0); */
E 1
