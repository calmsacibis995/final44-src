h41856
s 00002/00002/00037
d D 8.1 93/06/04 12:47:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00033
d D 5.3 93/02/26 19:08:58 ralph 3 2
c change name of minbrk and curbrk for profiling.
e
s 00001/00001/00038
d D 5.2 93/02/04 18:58:37 ralph 2 1
c gas doesn't understand .sdata yet
e
s 00039/00000/00000
d D 5.1 92/02/29 12:55:35 bostic 1 0
c date and time created 92/02/29 12:55:35 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
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

#define	SYS_brk		17

D 2
	.sdata
E 2
I 2
	.data
E 2
D 3
	.globl	_minbrk
_minbrk:
E 3
I 3
	.globl	minbrk
minbrk:
E 3
	.word	end
D 3
	.globl	_curbrk
_curbrk:
E 3
I 3
	.globl	curbrk
curbrk:
E 3
	.word	end
	.text

LEAF(sbrk)
D 3
	lw	v1, _curbrk
E 3
I 3
	lw	v1, curbrk
E 3
	li	v0, SYS_brk
	addu	a0, a0, v1	# compute current break
	syscall
	bne	a3, zero, 1f
	move	v0, v1		# return old val of _curbrk from above
D 3
	sw	a0, _curbrk	# save current val of _curbrk from above
E 3
I 3
	sw	a0, curbrk	# save current val of _curbrk from above
E 3
	j	ra
1:
	j	_cerror
END(sbrk)
E 1
