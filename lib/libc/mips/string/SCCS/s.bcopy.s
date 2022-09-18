h05113
s 00002/00002/00110
d D 8.1 93/06/04 12:47:07 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00004/00110
d D 5.6 93/02/21 13:41:22 ralph 6 5
c use MIPSEB & MIPSEL instead of BYTE_ORDER
e
s 00001/00001/00113
d D 5.5 93/02/04 18:56:01 ralph 5 4
c cpp can't handle ' in comments like ultrix assembler
e
s 00001/00001/00113
d D 5.4 92/07/26 21:41:34 ralph 4 3
c removed DEFS.h
e
s 00022/00007/00092
d D 5.3 92/06/20 12:40:07 ralph 3 2
c add bigendian support
e
s 00002/00002/00097
d D 5.2 92/02/29 12:57:09 bostic 2 1
c DEFS.h needed for ASMSTR macro
e
s 00099/00000/00000
d D 5.1 92/02/29 12:48:56 bostic 1 0
c date and time created 92/02/29 12:48:56 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

I 2
D 4
#include "DEFS.h"
E 4
I 4
#include <machine/machAsmDefs.h>
E 4

E 2
#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */
D 2

#include "DEFS.h"
E 2

/* bcopy(s1, s2, n) */

I 3
D 6
#include <machine/endian.h>

#if BYTE_ORDER == LITTLE_ENDIAN
E 6
I 6
#ifdef MIPSEL
E 6
#	define	LWHI	lwr
#	define	LWLO	lwl
#	define	SWHI	swr
#	define	SWLO	swl
#endif
D 6
#if BYTE_ORDER == BIG_ENDIAN
E 6
I 6
#ifdef MIPSEB
E 6
#	define	LWHI	lwl
#	define	LWLO	lwr
#	define	SWHI	swl
#	define	SWLO	swr
#endif

E 3
LEAF(bcopy)
	.set	noreorder
	addu	t0, a0, a2		# t0 = end of s1 region
	sltu	t1, a1, t0
	sltu	t2, a0, a1
	and	t1, t1, t2		# t1 = true if from < to < (from+len)
	beq	t1, zero, forward	# non overlapping, do forward copy
	slt	t2, a2, 12		# check for small copy

	ble	a2, zero, 2f
	addu	t1, a1, a2		# t1 = end of to region
1:
	lb	v0, -1(t0)		# copy bytes backwards,
D 5
	subu	t0, t0, 1		#   doesn't happen often so do slow way
E 5
I 5
	subu	t0, t0, 1		#   doesnt happen often so do slow way
E 5
	subu	t1, t1, 1
	bne	t0, a0, 1b
	sb	v0, 0(t1)
2:
	j	ra
	nop
forward:
	bne	t2, zero, smallcpy	# do a small bcopy
	xor	v0, a0, a1		# compare low two bits of addresses
	and	v0, v0, 3
	subu	a3, zero, a1		# compute # bytes to word align address
	beq	v0, zero, aligned	# addresses can be word aligned
	and	a3, a3, 3

	beq	a3, zero, 1f
	subu	a2, a2, a3		# subtract from remaining count
D 3
	lwr	v0, 0(a0)		# get next 4 bytes (unaligned)
	lwl	v0, 3(a0)
E 3
I 3
	LWHI	v0, 0(a0)		# get next 4 bytes (unaligned)
	LWLO	v0, 3(a0)
E 3
	addu	a0, a0, a3
D 3
	swr	v0, 0(a1)		# store 1, 2, or 3 bytes to align a1
E 3
I 3
	SWHI	v0, 0(a1)		# store 1, 2, or 3 bytes to align a1
E 3
	addu	a1, a1, a3
1:
	and	v0, a2, 3		# compute number of words left
	subu	a3, a2, v0
	move	a2, v0
	addu	a3, a3, a0		# compute ending address
2:
D 3
	lwr	v0, 0(a0)		# copy words a0 unaligned, a1 aligned
	lwl	v0, 3(a0)
E 3
I 3
	LWHI	v0, 0(a0)		# copy words a0 unaligned, a1 aligned
	LWLO	v0, 3(a0)
E 3
	addu	a0, a0, 4
	addu	a1, a1, 4
	bne	a0, a3, 2b
	sw	v0, -4(a1)
	b	smallcpy
	nop
aligned:
	beq	a3, zero, 1f
	subu	a2, a2, a3		# subtract from remaining count
D 3
	lwr	v0, 0(a0)		# copy 1, 2, or 3 bytes to align
E 3
I 3
	LWHI	v0, 0(a0)		# copy 1, 2, or 3 bytes to align
E 3
	addu	a0, a0, a3
D 3
	swr	v0, 0(a1)
E 3
I 3
	SWHI	v0, 0(a1)
E 3
	addu	a1, a1, a3
1:
	and	v0, a2, 3		# compute number of whole words left
	subu	a3, a2, v0
	move	a2, v0
	addu	a3, a3, a0		# compute ending address
2:
	lw	v0, 0(a0)		# copy words
	addu	a0, a0, 4
	addu	a1, a1, 4
	bne	a0, a3, 2b
	sw	v0, -4(a1)
smallcpy:
	ble	a2, zero, 2f
	addu	a3, a2, a0		# compute ending address
1:
	lbu	v0, 0(a0)		# copy bytes
	addu	a0, a0, 1
	addu	a1, a1, 1
	bne	a0, a3, 1b
	sb	v0, -1(a1)
2:
	j	ra
	nop
	.set	reorder
END(bcopy)
E 1
