h63050
s 00002/00002/00020
d D 8.1 93/06/04 12:41:01 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00021
d D 5.2 90/12/17 15:32:46 william 2 1
c wrong syntax
e
s 00020/00000/00000
d D 5.1 90/04/23 19:56:48 william 1 0
c date and time created 90/04/23 19:56:48 by william
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

ENTRY(abs)
D 2
	movl	4(sp),%eax
E 2
I 2
	movl	4(%esp),%eax
E 2
	cmpl	$0,%eax
	jge	1f
	negl	%eax
1:	ret
E 1
