h08604
s 00002/00002/00022
d D 8.1 93/06/04 12:36:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00022
d D 5.2 92/07/07 16:34:17 mckusick 3 1
c return quad -1
e
s 00001/00000/00022
d R 5.2 92/07/07 16:15:52 mckusick 2 1
c return a quad -1
e
s 00022/00000/00000
d D 5.1 90/05/12 16:51:33 bostic 1 0
c date and time created 90/05/12 16:51:33 by bostic
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

I 3
	.even
E 3
	.globl	_errno
cerror:
	movl	d0,_errno
	movl	#-1,d0
I 3
	movl	#-1,d1
E 3
	rts
E 1
