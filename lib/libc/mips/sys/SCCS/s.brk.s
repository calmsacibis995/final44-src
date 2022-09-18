h25343
s 00002/00002/00030
d D 8.1 93/06/04 12:47:22 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00030
d D 5.3 93/02/26 19:08:57 ralph 3 2
c change name of minbrk and curbrk for profiling.
e
s 00001/00001/00031
d D 5.2 93/02/04 18:58:14 ralph 2 1
c cpp can't handle ' in comments like ultrix assembler
e
s 00032/00000/00000
d D 5.1 92/02/29 12:55:23 bostic 1 0
c date and time created 92/02/29 12:55:23 by bostic
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

LEAF(brk)
D 3
	lw	v0, _minbrk
E 3
I 3
	lw	v0, minbrk
E 3
	bgeu	a0, v0, _brk
D 2
	move	a0, v0		# don't allow break < minbrk
E 2
I 2
	move	a0, v0		# dont allow break < minbrk
E 2
ALEAF(_brk)
	li	v0, SYS_brk
	syscall
	bne	a3, zero, 1f
D 3
	sw	a0, _curbrk
E 3
I 3
	sw	a0, curbrk
E 3
	move	v0, zero
	j	ra
1:
	j	_cerror
END(brk)
E 1
