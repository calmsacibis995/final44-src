h59332
s 00002/00002/00023
d D 8.1 93/06/04 12:47:42 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 92/02/29 12:55:31 bostic 1 0
c date and time created 92/02/29 12:55:31 by bostic
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
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

#include "SYS.h"

#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */

LEAF(ptrace)
	sw	zero, errno
	li	v0, SYS_ptrace
	syscall
	bne	a3, zero, 1f
	j	ra
1:
	j	_cerror
END(ptrace)
E 1
