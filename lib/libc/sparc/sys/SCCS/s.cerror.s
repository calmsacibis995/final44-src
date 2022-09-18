h17792
s 00002/00002/00024
d D 8.1 93/06/04 13:02:21 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00023
d D 5.2 92/07/02 19:40:25 torek 2 1
c need to return a quad -1
e
s 00025/00000/00000
d D 5.1 92/06/25 06:37:55 torek 1 0
c date and time created 92/06/25 06:37:55 by torek
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
D 2
 * from: $Header: cerror.s,v 1.1 92/06/25 12:56:39 torek Exp $
E 2
I 2
 * from: $Header: cerror.s,v 1.3 92/07/02 04:17:59 torek Exp $
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "DEFS.h"

	.globl	_errno
FUNC(cerror)
	sethi	%hi(_errno), %g1
	st	%o0, [%g1 + %lo(_errno)]
I 2
	mov	-1, %o0
E 2
	retl
D 2
	 mov	-1, %o0
E 2
I 2
	 mov	-1, %o1
E 2
E 1
