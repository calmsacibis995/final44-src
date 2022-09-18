h63828
s 00002/00002/00018
d D 8.1 93/06/04 12:38:59 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00019
d D 5.2 90/12/17 15:15:11 william 2 1
c silent typo to the asm (thinks sp is a local label?)
e
s 00016/00000/00000
d D 5.1 90/04/23 19:56:53 william 1 0
c date and time created 90/04/23 19:56:53 by william
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
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

ENTRY(fabs)
D 2
	fldl	4(sp)
E 2
I 2
	fldl	4(%esp)
E 2
	fabs
	ret
E 1
