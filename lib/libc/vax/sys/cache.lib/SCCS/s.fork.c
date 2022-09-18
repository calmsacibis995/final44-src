h59320
s 00002/00002/00020
d D 8.1 93/06/04 15:45:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00020
d D 5.2 91/04/12 13:43:14 bostic 2 1
c new copyright; att/bsd/shared
e
s 00032/00000/00000
d D 5.1 91/04/12 13:40:33 bostic 1 0
c date and time created 91/04/12 13:40:33 by bostic
e
u
U
t
T
I 1
D 2
/*
E 2
I 2
/*-
E 2
D 3
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

	.globl	mypid, myppid

SYSCALL(fork)
	jlbc	r1,1f	# parent, since r1 == 0 in parent, 1 in child
	movl	r0,myppid
	clrl	mypid
	clrl	r0
1:
	ret		# pid = fork()
E 1
