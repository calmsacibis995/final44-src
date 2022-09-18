h00980
s 00002/00002/00027
d D 8.1 93/06/04 15:40:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00028
d D 5.2 91/05/12 14:50:53 bostic 2 1
c return the base; bug report 4.3BSD-reno/lib/3
e
s 00028/00000/00000
d D 5.1 90/05/15 21:29:51 bostic 1 0
c date and time created 90/05/15 21:29:51 by bostic
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
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/* void *memset(base, c, length) */

#include "DEFS.h"

ENTRY(memset, 0)
	movl	4(ap),r3
1:
	movzwl	$65535,r0
	movq	8(ap),r1
	cmpl	r2,r0
	jgtru	2f
	movc5	$0,(r3),r1,r2,(r3)
I 2
	movl	r1,r0
E 2
	ret
2:
	subl2	r0,12(ap)
	movc5	$0,(r3),r1,r0,(r3)
	jbr	1b
E 1
