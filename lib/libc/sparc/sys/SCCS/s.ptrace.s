h07274
s 00002/00002/00028
d D 8.1 93/06/04 13:02:32 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 5.1 92/06/25 06:37:57 torek 1 0
c date and time created 92/06/25 06:37:57 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: ptrace.s,v 1.2 91/12/20 01:59:00 leres Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

ENTRY(ptrace)
	sethi	%hi(_errno), %g1
	st	%g0, [%g1 + %lo(_errno)]
	mov	SYS_ptrace, %g1
	t	ST_SYSCALL
	bcc	1f
	nop
	ERROR()
1:
	retl
	nop
E 1
