h03092
s 00002/00002/00025
d D 8.1 93/06/04 13:01:48 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00000/00000
d D 5.1 92/06/25 06:31:53 torek 1 0
c date and time created 92/06/25 06:31:53 by torek
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
 * from: $Header: abs.s,v 1.1 91/07/06 18:01:57 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/* abs - int absolute value */

#include "DEFS.h"

ENTRY(abs)
	tst	%o0
	bl,a	1f
	neg	%o0
1:	retl
	nop
E 1
