h34075
s 00002/00002/00038
d D 8.1 93/06/04 13:02:47 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00040/00000/00000
d D 5.1 92/06/25 06:38:00 torek 1 0
c date and time created 92/06/25 06:38:00 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: sigprocmask.s,v 1.1 91/07/06 13:06:01 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

/*
 * sigprocmask(int how, sigset_t *set, sigset_t *oset)
 */
ENTRY(sigprocmask)
	tst	%o1		! set == NULL?
	bne,a	1f		! if not,
	 ld	[%o1], %o1	!    replace it in %o1 with *set
!	clr	%o1		! else block no signals ...
	mov	1, %o0		! ... using sigprocmask(SIG_BLOCK)
1:
	mov	SYS_sigprocmask, %g1
	t	ST_SYSCALL
	bcc	2f		! if success,
	 tst	%o2		!    check to see if oset requested
	ERROR()
2:
	bne,a	3f		! if oset != NULL,
	 st	%o0, [%o2]	!    *oset = oldmask
3:
	retl			! in any case, return 0
	 clr	%o0
E 1
