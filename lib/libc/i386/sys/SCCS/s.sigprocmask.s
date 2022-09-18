h39587
s 00002/00002/00036
d D 8.1 93/06/04 12:42:06 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00037
d D 5.2 90/12/17 15:40:00 william 2 1
c trivial errors and GAS heartburn.
e
s 00038/00000/00000
d D 5.1 90/07/01 00:05:56 bostic 1 0
c date and time created 90/07/01 00:05:56 by bostic
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

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* SYSLIBC_SCCS and not lint */

#include "SYS.h"

err:
	jmp	cerror

ENTRY(sigprocmask)
	movl	8(%esp),%ecx		# fetch new sigset pointer
D 2
	cmpl	$0,(%ecx)		# check new sigset pointer
E 2
I 2
	cmpl	$0,%ecx			# check new sigset pointer
E 2
	jne	1f			# if not null, indirect
/*	movl	$0,8(%esp)		# null mask pointer: block empty set */
	movl	$1,4(%esp)		# SIG_BLOCK
	jmp	2f
1:	movl	(%ecx),%ecx		# fetch indirect  ...
	movl	%ecx,8(%esp)		# to new mask arg
2:	movl	$ SYS_sigprocmask , %eax
	LCALL(0x7,0)
	jb	err
	movl	12(%esp),%ecx		# fetch old mask requested
	cmpl	$0,%ecx			# test if old mask requested
	je	out
	movl	%eax,(%ecx)		# store old mask
out:
	xorl	%eax,%eax
	ret
E 1
