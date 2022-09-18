h06562
s 00002/00002/00022
d D 8.1 93/06/16 14:15:18 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00022
d D 5.2 93/06/16 14:14:42 mckusick 3 1
c update from Ralph
e
s 00002/00002/00020
d R 8.1 93/06/04 12:47:27 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00000/00000
d D 5.1 92/02/29 12:55:25 bostic 1 0
c date and time created 92/02/29 12:55:25 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

	.globl	errno
LEAF(_cerror)
I 3
	.set	noreorder
E 3
	sw	v0, errno
	li	v0, -1
	j	ra
I 3
	li	v1, -1
E 3
END(_cerror)
E 1
