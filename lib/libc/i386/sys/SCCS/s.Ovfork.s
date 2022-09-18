h21023
s 00002/00002/00042
d D 8.1 93/06/04 12:41:24 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00049/00000/00000
d D 5.1 90/04/23 19:38:28 william 1 0
c date and time created 90/04/23 19:38:28 by william
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */

#include "SYS.h"

/*
 * pid = vfork();
 *
 * %edx == 0 in parent process, %edx == 1 in child process.
 * %eax == pid of child in parent, %eax == pid of parent in child.
 *
 */
	.set	vfork,66
.globl	_vfork

_vfork:
	popl	%ecx		/* my rta into ecx */
	movl	$vfork, %eax
	LCALL(7,0)
	jb	verror
vforkok:
	cmpl	$0,%edx		/* child process? */
	jne	child		/* yes */
	jmp 	parent 
.globl	_errno
verror:
	movl	%eax,_errno
	movl	$-1,%eax
	jmp	%ecx
child:
	movl	$0,%eax
parent:
	jmp	%ecx
E 1
