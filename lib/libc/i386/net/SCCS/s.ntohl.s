h05317
s 00002/00002/00022
d D 8.1 93/06/04 12:40:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00020
d D 5.2 90/12/17 15:24:01 william 2 1
c syntax errors,wrong code
e
s 00022/00000/00000
d D 5.1 90/04/23 20:01:39 william 1 0
c date and time created 90/04/23 20:01:39 by william
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

/* hostorder = ntohl(netorder) */

#include "DEFS.h"

ENTRY(ntohl)
D 2
	mov	%eax,4(sp)
	xchg	%al,%ah
	rol	$16,%eax
	xchg	%al,%ah
E 2
I 2
	movl	4(%esp),%eax
	xchgb	%al,%ah
	roll	$16,%eax
	xchgb	%al,%ah
E 2
	ret
E 1
