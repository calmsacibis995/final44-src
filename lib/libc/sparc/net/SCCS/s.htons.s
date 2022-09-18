h05011
s 00002/00002/00023
d D 8.1 93/06/04 13:01:21 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 92/06/25 06:30:01 torek 1 0
c date and time created 92/06/25 06:30:01 by torek
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
 * from: $Header: htons.s,v 1.1 92/06/25 12:47:05 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/* netorder = htons(hostorder) */

#include "DEFS.h"

ENTRY(htons)
	sethi	%hi(0xffff0000), %o1
	retl
	 andn	%o0, %o1, %o0
E 1
