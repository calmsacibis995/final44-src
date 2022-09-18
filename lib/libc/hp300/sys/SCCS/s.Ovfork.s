h11982
s 00002/00002/00046
d D 8.1 93/06/07 22:43:26 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00005/00046
d D 5.3 93/06/07 22:43:21 bostic 5 3
c needs SYS.h, too
e
s 00002/00002/00049
d R 8.1 93/06/07 22:40:43 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00050
d D 5.2 93/06/07 22:40:02 bostic 3 1
c use ENTRY; needed .even call
e
s 00002/00002/00051
d R 8.1 93/06/04 12:36:06 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00053/00000/00000
d D 5.1 90/05/12 16:51:26 bostic 1 0
c date and time created 90/05/12 16:51:26 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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

/*
D 5
 * @(#)vfork.s	4.1 (Berkeley) 12/21/80
 * C library -- vfork
 */

/*
E 5
 * pid = vfork();
 *
 * d1 == 0 in parent process, d1 == 1 in child process.
 * d0 == pid of child in parent, d0 == pid of parent in child.
 *
 * trickery here, due to keith sklower, uses ret to clear the stack,
 * and then returns with a jump indirect, since only one person can return
 * with a ret off this stack... we do the ret before we vfork!
 */
I 5

#include "SYS.h"
E 5

	vfork = 66
D 3
.globl	_vfork

_vfork:
E 3
I 3
ENTRY(vfork)
E 3
	movl	sp@+,a0
	movl	#vfork,d0
	trap	#0
	jcc	vforkok
	jmp	verror
vforkok:
	tstl	d1		/* child process ? */
	jne	child		/* yes */
	jcc 	parent		/* if c-bit not set, fork ok */
	.globl	_errno
verror:
	movl	d0,_errno
	moveq	#-1,d0
	jmp	a0@
child:
	clrl	d0
parent:
	jmp	a0@
E 1
