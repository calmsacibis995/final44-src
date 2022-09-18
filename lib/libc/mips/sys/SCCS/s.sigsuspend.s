h10096
s 00002/00002/00024
d D 8.1 93/06/04 12:48:06 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00025
d D 5.2 93/02/20 19:01:33 ralph 2 1
c cpp doesn't like single quote in comment.
e
s 00026/00000/00000
d D 5.1 92/02/29 12:55:48 bostic 1 0
c date and time created 92/02/29 12:55:48 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
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

LEAF(sigsuspend)
	lw	a0, 0(a0)		# indirect to mask arg
	li	v0, SYS_sigsuspend
	syscall
	bne	a3, zero, 1f
D 2
	move	v0, zero		# shouldn't happen
E 2
I 2
	move	v0, zero		# should not happen
E 2
	j	ra
1:
	j	_cerror
END(sigsuspend)
E 1
