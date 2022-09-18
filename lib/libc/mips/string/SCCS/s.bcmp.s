h35870
s 00002/00002/00104
d D 8.1 93/06/04 12:47:04 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00004/00104
d D 5.5 93/02/21 13:41:18 ralph 5 4
c use MIPSEB & MIPSEL instead of BYTE_ORDER
e
s 00001/00001/00107
d D 5.4 92/07/26 21:41:33 ralph 4 3
c removed DEFS.h
e
s 00019/00004/00089
d D 5.3 92/06/20 12:40:06 ralph 3 2
c add bigendian support
e
s 00002/00002/00091
d D 5.2 92/02/29 12:57:08 bostic 2 1
c DEFS.h needed for ASMSTR macro
e
s 00093/00000/00000
d D 5.1 92/02/29 12:48:55 bostic 1 0
c date and time created 92/02/29 12:48:55 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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

/* bcmp(s1, s2, n) */

I 3
D 5
#include <machine/endian.h>

#if BYTE_ORDER == LITTLE_ENDIAN
E 5
I 5
#ifdef MIPSEL
E 5
#	define	LWHI	lwr
#	define	LWLO	lwl
#	define	SWHI	swr
#	define	SWLO	swl
#endif
D 5
#if BYTE_ORDER == BIG_ENDIAN
E 5
I 5
#ifdef MIPSEB
E 5
#	define	LWHI	lwl
#	define	LWLO	lwr
#	define	SWHI	swl
#	define	SWLO	swr
#endif

E 3
LEAF(bcmp)
	.set	noreorder
	blt	a2, 16, small		# is it worth any trouble?
	xor	v0, a0, a1		# compare low two bits of addresses
	and	v0, v0, 3
	subu	a3, zero, a1		# compute # bytes to word align address
	bne	v0, zero, unaligned	# not possible to align addresses
	and	a3, a3, 3

	beq	a3, zero, 1f
	subu	a2, a2, a3		# subtract from remaining count
	move	v0, v1			# init v0,v1 so unmodified bytes match
D 3
	lwr	v0, 0(a0)		# read 1, 2, or 3 bytes
	lwr	v1, 0(a1)
E 3
I 3
	LWHI	v0, 0(a0)		# read 1, 2, or 3 bytes
	LWHI	v1, 0(a1)
E 3
	addu	a1, a1, a3
	bne	v0, v1, nomatch
	addu	a0, a0, a3
1:
	and	a3, a2, ~3		# compute number of whole words left
	subu	a2, a2, a3		#   which has to be >= (16-3) & ~3
	addu	a3, a3, a0		# compute ending address
2:
	lw	v0, 0(a0)		# compare words
	lw	v1, 0(a1)
	addu	a0, a0, 4
	bne	v0, v1, nomatch
	addu	a1, a1, 4
	bne	a0, a3, 2b
	nop
	b	small			# finish remainder
	nop
unaligned:
	beq	a3, zero, 2f
	subu	a2, a2, a3		# subtract from remaining count
	addu	a3, a3, a0		# compute ending address
1:
	lbu	v0, 0(a0)		# compare bytes until a1 word aligned
	lbu	v1, 0(a1)
	addu	a0, a0, 1
	bne	v0, v1, nomatch
	addu	a1, a1, 1
	bne	a0, a3, 1b
	nop
2:
	and	a3, a2, ~3		# compute number of whole words left
	subu	a2, a2, a3		#   which has to be >= (16-3) & ~3
	addu	a3, a3, a0		# compute ending address
3:
D 3
	lwr	v0, 0(a0)		# compare words a0 unaligned, a1 aligned
	lwl	v0, 3(a0)
E 3
I 3
	LWHI	v0, 0(a0)		# compare words a0 unaligned, a1 aligned
	LWLO	v0, 3(a0)
E 3
	lw	v1, 0(a1)
	addu	a0, a0, 4
	bne	v0, v1, nomatch
	addu	a1, a1, 4
	bne	a0, a3, 3b
	nop
small:
	ble	a2, zero, match
	addu	a3, a2, a0		# compute ending address
1:
	lbu	v0, 0(a0)
	lbu	v1, 0(a1)
	addu	a0, a0, 1
	bne	v0, v1, nomatch
	addu	a1, a1, 1
	bne	a0, a3, 1b
	nop
match:
	j	ra
	move	v0, zero
nomatch:
	j	ra
	li	v0, 1
	.set	reorder
END(bcmp)
E 1
