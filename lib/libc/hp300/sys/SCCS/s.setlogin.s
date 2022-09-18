h53004
s 00002/00002/00016
d D 8.1 93/06/04 12:36:30 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00000/00000
d D 5.1 91/05/06 14:44:17 bostic 1 0
c date and time created 91/05/06 14:44:17 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

.globl	__logname_valid		/* in getlogin() */

SYSCALL(setlogin)
	movl	#0,__logname_valid
	rts				/* setlogin(name) */
E 1
