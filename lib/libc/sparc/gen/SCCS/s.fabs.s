h11652
s 00002/00002/00024
d D 8.1 93/06/04 13:01:10 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00000/00000
d D 5.1 92/06/25 06:16:58 torek 1 0
c date and time created 92/06/25 06:16:58 by torek
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
 * from: $Header: fabs.s,v 1.4 91/10/07 23:59:05 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/* fabs - floating absolute value */

#include "DEFS.h"

ENTRY(fabs)
	std	%o0, [%sp + 32]		! return value => %f0:f1
	ldd	[%sp + 32], %f0		! (via kernel %o0/%o1 slot)
	retl
	 fabss	%f0, %f0		! return absolute value
E 1
