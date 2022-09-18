h58669
s 00036/00000/00000
d D 5.1 90/04/23 19:38:44 william 1 0
c date and time created 90/04/23 19:38:44 by william
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
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

ENTRY(execle)
	lea	4(%esp),%eax
1:
	cmpl	$0,(%eax)
	je	1f
	addl	$4,%eax
	jmp	1b
1:	
	addl	$4,%eax
	movl	(%eax),%eax
	pushl	%eax		/* *envp */
	lea	8+4(%esp),%eax
	pushl	%eax		/* *ap */
	movl	4+8(%esp),%eax
	pushl	%eax		/* file */

	call	_execve
	addl	$12,%esp
	ret			/* execle(file, arg1, arg2, ..., 0, env); */
				/* execve (file, *ap, env) */
E 1
