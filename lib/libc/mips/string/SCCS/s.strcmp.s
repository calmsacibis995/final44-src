h34347
s 00002/00002/00036
d D 8.1 93/06/04 12:47:29 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00037
d D 5.3 92/07/26 21:41:39 ralph 3 2
c removed DEFS.h
e
s 00002/00002/00036
d D 5.2 92/02/29 12:57:16 bostic 2 1
c DEFS.h needed for ASMSTR macro
e
s 00038/00000/00000
d D 5.1 92/02/29 12:49:01 bostic 1 0
c date and time created 92/02/29 12:49:01 by bostic
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

I 2
D 3
#include "DEFS.h"
E 3
I 3
#include <machine/machAsmDefs.h>
E 3

E 2
#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */
D 2

#include "DEFS.h"
E 2

/*
 * NOTE: this version assumes unsigned chars in order to be "8 bit clean".
 */
LEAF(strcmp)
1:
	lbu	t0, 0(a0)		# get two bytes and compare them
	lbu	t1, 0(a1)
	beq	t0, zero, LessOrEq	# end of first string?
	bne	t0, t1, NotEq
	lbu	t0, 1(a0)		# unroll loop
	lbu	t1, 1(a1)
	add	a0, a0, 2
	beq	t0, zero, LessOrEq	# end of first string?
	add	a1, a1, 2
	beq	t0, t1, 1b
NotEq:
	subu	v0, t0, t1
	j	ra
LessOrEq:
	subu	v0, zero, t1
	j	ra
END(strcmp)
E 1
