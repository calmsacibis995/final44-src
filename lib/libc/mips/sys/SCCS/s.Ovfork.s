h13905
s 00002/00002/00032
d D 8.1 93/06/04 12:47:16 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 5.1 92/02/29 12:55:21 bostic 1 0
c date and time created 92/02/29 12:55:21 by bostic
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

/*
 * pid = vfork();
 *
 * v1 == 0 in parent process, v1 == 1 in child process.
 * v0 == pid of child in parent, v0 == pid of parent in child.
 */

LEAF(vfork)
	li	v0, SYS_vfork		# system call number for vfork
	syscall
	beq	a3, zero, 1f		# jump if no errors
	j	_cerror
1:
	beq	v1, zero, 2f		# parent process ?
	move	v0, zero		# return zero in child
2:
	j	ra
END(vfork)
E 1
