h14013
s 00002/00002/00022
d D 8.1 93/06/04 13:02:56 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00022
d D 5.2 93/01/10 18:21:20 torek 2 1
c return via g2, not g7 (for ABI)
e
s 00024/00000/00000
d D 5.1 92/06/25 06:38:02 torek 1 0
c date and time created 92/06/25 06:38:02 by torek
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: syscall.s,v 1.1 91/07/06 13:06:02 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

ENTRY(syscall)
D 2
	mov	0|SYSCALL_RFLAG, %g1	! 0 == indir
	add	%o7, 8, %g7
E 2
I 2
	mov	0|SYSCALL_G2RFLAG, %g1	! 0 == indir
	add	%o7, 8, %g2
E 2
	t	ST_SYSCALL
	ERROR()
E 1
