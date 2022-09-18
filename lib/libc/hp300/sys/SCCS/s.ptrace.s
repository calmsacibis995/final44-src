h07075
s 00002/00002/00023
d D 8.1 93/06/07 22:40:51 bostic 3 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00023
d R 8.1 93/06/04 12:36:23 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 90/05/12 16:51:46 bostic 1 0
c date and time created 90/05/12 16:51:46 by bostic
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

ENTRY(ptrace)
	clrl	_errno
	movl	#SYS_ptrace,d0
	trap	#0
	jcs	err
	rts
err:
	jmp	cerror
E 1
