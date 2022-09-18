h19159
s 00002/00002/00032
d D 8.1 93/06/04 12:48:01 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 5.1 92/02/29 12:55:45 bostic 1 0
c date and time created 92/02/29 12:55:45 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

#include "SYS.h"

#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */

LEAF(sigprocmask)	# sigprocmask(how, new, old) sigset_t *new, *old;
	bne	a1, zero, gotptr	# if new sigset pointer not null
	li	a0, 1			# how = SIG_BLOCK
	b	doit			# mask = zero
gotptr:
	lw	a1, 0(a1)		# indirect to new mask arg
doit:
	li	v0, SYS_sigprocmask
	syscall
	bne	a3, zero, err
	beq	a2, zero, out		# test if old mask requested
	sw	v0, 0(a2)		# store old mask
out:
	move	v0, zero
	j	ra
err:
	j	_cerror
END(sigprocmask)
E 1
