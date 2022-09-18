h46377
s 00020/00000/00000
d D 5.1 90/05/30 12:58:23 bostic 1 0
c date and time created 90/05/30 12:58:23 by bostic
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

PSEUDO(getegid,getgid)		/* egid = getegid(); */
	movl	d1,d0
	rts
E 1
