h50902
s 00026/00000/00000
d D 5.1 92/06/25 06:17:13 torek 1 0
c date and time created 92/06/25 06:17:13 by torek
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: main.s,v 1.1 92/06/25 12:43:03 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/*
 * Dummy for gcc version 2
 */

#include "DEFS.h"

ENTRY(__main)
	retl
	nop
E 1
