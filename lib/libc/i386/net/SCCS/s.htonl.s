h15812
s 00002/00002/00022
d D 8.1 93/06/04 12:40:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00018
d D 5.3 90/12/17 15:28:22 william 3 2
c syntax errors,wrong code
e
s 00000/00000/00024
d D 5.2 90/12/17 15:24:00 william 2 1
c syntax errors, wrong code
e
s 00022/00000/00000
d D 5.1 90/04/23 20:01:37 william 1 0
c date and time created 90/04/23 20:01:37 by william
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

D 3
/* hostorder = ntohl(netorder) */
E 3
I 3
/* netorder = htonl(hostorder) */
E 3

#include "DEFS.h"

D 3
ENTRY(ntohl)
	mov	%eax,4(sp)
	xchg	%al,%ah
	rol	$16,%eax
	xchg	%al,%ah
E 3
I 3
ENTRY(htonl)
	movl	4(%esp),%eax
	xchgb	%al,%ah
	roll	$16,%eax
	xchgb	%al,%ah
E 3
	ret
E 1
