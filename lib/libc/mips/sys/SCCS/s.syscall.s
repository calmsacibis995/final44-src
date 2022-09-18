h63256
s 00002/00002/00017
d D 8.1 93/06/04 12:48:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00018
d D 5.2 93/02/04 18:59:07 ralph 2 1
c use RSYSCALL to be like other machines
e
s 00019/00000/00000
d D 5.1 92/02/29 12:55:50 bostic 1 0
c date and time created 92/02/29 12:55:50 by bostic
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

#define SYS_syscall	0

D 2
SYSCALL(syscall)
E 2
I 2
RSYSCALL(syscall)
E 2
E 1
