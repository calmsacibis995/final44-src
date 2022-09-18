h00158
s 00002/00002/00025
d D 8.1 93/06/04 12:47:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 5.1 92/02/29 12:55:29 bostic 1 0
c date and time created 92/02/29 12:55:29 by bostic
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

LEAF(pipe)
	li	v0, SYS_pipe	# pipe(fildes) int fildes[2];
	syscall
	bne	a3, zero, 1f
	sw	v0, 0(a0)	# store the two file descriptors
	sw	v1, 4(a0)
	move	v0, zero
	j	ra
1:
	j	_cerror
END(pipe)
E 1
