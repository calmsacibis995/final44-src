h37590
s 00017/00000/00000
d D 5.1 90/04/23 19:56:47 william 1 0
c date and time created 90/04/23 19:56:47 by william
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "DEFS.h"

ENTRY(abort)
	hlt
	/* NOTREACHED */
E 1
