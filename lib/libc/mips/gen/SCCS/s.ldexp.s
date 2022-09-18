h01581
s 00002/00002/00187
d D 8.1 93/06/04 12:46:34 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00188
d D 5.5 93/02/04 18:51:56 ralph 5 4
c cpp can't handle ' in comments like ultrix assembler
e
s 00001/00001/00188
d D 5.4 92/07/26 21:36:52 ralph 4 3
c removed DEFS.h
e
s 00158/00071/00031
d D 5.3 92/03/07 09:23:39 ralph 3 2
c do denorms correctly
e
s 00002/00002/00100
d D 5.2 92/02/29 12:58:55 bostic 2 1
c need DEFS.h for ASMSTR macro
e
s 00102/00000/00000
d D 5.1 92/02/29 12:40:58 bostic 1 0
c date and time created 92/02/29 12:40:58 by bostic
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

D 3
	.sdata
infinity:
	.word	0x7ff00000	# IEEE infinity
	.text
E 3
I 3
#define DEXP_INF	0x7ff
#define DEXP_BIAS	1023
#define DEXP_MIN	-1022
#define DEXP_MAX	1023
#define DFRAC_BITS	52
#define DIMPL_ONE	0x00100000
#define DLEAD_ZEROS	31 - 20
#define STICKYBIT	1
#define GUARDBIT	0x80000000
#define DSIGNAL_NAN	0x00040000
#define DQUIET_NAN0	0x0007ffff
#define DQUIET_NAN1	0xffffffff
E 3

/*
D 3
 * double ldexp(val, exp)
 * returns: val * (2**exp), for integer exp
E 3
I 3
 * double ldexp(x, N)
 *	double x; int N;
 *
 * Return x * (2**N), for integer values N.
E 3
 */
LEAF(ldexp)
D 3
	.set	noreorder
	mfc1	t0, $f13
	mov.d	$f0, $f12
	sll	t1, t0, 1
	srl	t1, t1, 21
	addu	t1, t1, a2
	blez	t1, 3f
	slti	t2, t1, 2047
	beq	t2, zero, 2f
	sll	a2, a2, 20
	addu	t0, t0, a2
	mtc1	t0, $f1
1:
E 3
I 3
	mfc1	v1, $f13		# get MSW of x
	mfc1	t3, $f12		# get LSW of x
	sll	t1, v1, 1		# get x exponent
	srl	t1, t1, 32 - 11
	beq	t1, DEXP_INF, 9f	# is it a NAN or infinity?
	beq	t1, zero, 1f		# zero or denormalized number?
	addu	t1, t1, a2		# scale exponent
	sll	v0, a2, 20		# position N for addition
	bge	t1, DEXP_INF, 8f	# overflow?
	addu	v0, v0, v1		# multiply by (2**N)
	ble	t1, zero, 4f		# underflow?
	mtc1	v0, $f1			# save MSW of result
	mtc1	t3, $f0			# save LSW of result
E 3
	j	ra
D 3
	nop
E 3
I 3
1:
	sll	t2, v1, 32 - 20		# get x fraction
	srl	t2, t2, 32 - 20
	srl	t0, v1, 31		# get x sign
	bne	t2, zero, 1f
	beq	t3, zero, 9f		# result is zero
1:
/*
 * Find out how many leading zero bits are in t2,t3 and put in t9.
 */
	move	v0, t2
	move	t9, zero
	bne	t2, zero, 1f
	move	v0, t3
	addu	t9, 32
1:
	srl	t4, v0, 16
	bne	t4, zero, 1f
	addu	t9, 16
	sll	v0, 16
1:
	srl	t4, v0, 24
	bne	t4, zero, 1f
	addu	t9, 8
	sll	v0, 8
1:
	srl	t4, v0, 28
	bne	t4, zero, 1f
	addu	t9, 4
	sll	v0, 4
1:
	srl	t4, v0, 30
	bne	t4, zero, 1f
	addu	t9, 2
	sll	v0, 2
1:
	srl	t4, v0, 31
	bne	t4, zero, 1f
	addu	t9, 1
/*
 * Now shift t2,t3 the correct number of bits.
 */
1:
D 5
	subu	t9, t9, DLEAD_ZEROS	# don't count normal leading zeros
E 5
I 5
	subu	t9, t9, DLEAD_ZEROS	# dont count normal leading zeros
E 5
	li	t1, DEXP_MIN + DEXP_BIAS
	subu	t1, t1, t9		# adjust exponent
	addu	t1, t1, a2		# scale exponent
	li	v0, 32
	blt	t9, v0, 1f
	subu	t9, t9, v0		# shift fraction left >= 32 bits
	sll	t2, t3, t9
	move	t3, zero
	b	2f
1:
	subu	v0, v0, t9		# shift fraction left < 32 bits
	sll	t2, t2, t9
	srl	t4, t3, v0
	or	t2, t2, t4
	sll	t3, t3, t9
E 3
2:
D 3
	lwc1	$f1, infinity
	bgez	t0, 1b
	mtc1	zero, $f0
	j	ra
	neg.d	$f0, $f0
E 3
I 3
	bge	t1, DEXP_INF, 8f	# overflow?
	ble	t1, zero, 4f		# underflow?
	sll	t2, t2, 32 - 20		# clear implied one bit
	srl	t2, t2, 32 - 20
E 3
3:
D 3
	blt	t1, -51, 9f
	mfc1	t5, $f13
	li	t2, 0x80000000
	sll	t5, t5, 11
	blt	t1, -30, 7f
	or	t5, t5, t2
	srl	t5, t5, 11
	mfc1	t4, $f12
	addiu	t1, t1, -1
	sll	t3, t5, t1
	srl	t2, t4, t1
	subu	t1, zero, t1
	srl	t4, t4, t1
	or	t4, t4, t3
	bgez	t2, 6f
	srl	t5, t5, t1
	addiu	t4, t4, 1
	sltiu	t6, t4, 1
	sll	t2, t2, 1
	bne	t2, zero, 6f
	addu	t5, t5, t6
	and	t4, t4, ~1
6:
	mtc1	t4, $f0
	bgez	t0, 1b
	mtc1	t5, $f1
E 3
I 3
	sll	t1, t1, 31 - 11		# reposition exponent
	sll	t0, t0, 31		# reposition sign
	or	t0, t0, t1		# put result back together
	or	t0, t0, t2
	mtc1	t0, $f1			# save MSW of result
	mtc1	t3, $f0			# save LSW of result
E 3
	j	ra
D 3
	neg.d	$f0, $f0
E 3
I 3
4:
	li	v0, 0x80000000
	ble	t1, -52, 7f		# is result too small for denorm?
	sll	t2, v1, 31 - 20		# clear exponent, extract fraction
	or	t2, t2, v0		# set implied one bit
	blt	t1, -30, 2f		# will all bits in t3 be shifted out?
	srl	t2, t2, 31 - 20		# shift fraction back to normal position
	subu	t1, t1, 1
	sll	t4, t2, t1		# shift right t2,t3 based on exponent
	srl	t8, t3, t1		# save bits shifted out
	negu	t1
	srl	t3, t3, t1
	or	t3, t3, t4
	srl	t2, t2, t1
	bge	t8, zero, 1f		# does result need to be rounded?
	addu	t3, t3, 1		# round result
	sltu	t4, t3, 1
	sll	t8, t8, 1
	addu	t2, t2, t4
	bne	t8, zero, 1f		# round result to nearest
	and	t3, t3, ~1
1:
	mtc1	t3, $f0			# save denormalized result (LSW)
	mtc1	t2, $f1			# save denormalized result (MSW)
	bge	v1, zero, 1f		# should result be negative?
	neg.d	$f0, $f0		# negate result
1:
	j	ra
2:
	mtc1	zero, $f1		# exponent and upper fraction
	addu	t1, t1, 20		# compute amount to shift right by
	sll	t8, t2, t1		# save bits shifted out
	negu	t1
	srl	t3, t2, t1
	bge	t8, zero, 1f		# does result need to be rounded?
	addu	t3, t3, 1		# round result
	sltu	t4, t3, 1
	sll	t8, t8, 1
	mtc1	t4, $f1			# exponent and upper fraction
	bne	t8, zero, 1f		# round result to nearest
	and	t3, t3, ~1
1:
	mtc1	t3, $f0
	bge	v1, zero, 1f		# is result negative?
	neg.d	$f0, $f0		# negate result
1:
	j	ra
E 3
7:
I 3
	mtc1	zero, $f0		# result is zero
E 3
	mtc1	zero, $f1
D 3
	addiu	t1, t1, 20
	sll	t2, t5, t1
	subu	t1, zero, t1
	bgez	t2, 8f
	srl	t4, t5, t1
	addiu	t4, t4, 1
	sltiu	t6, t4, 1
	sll	t2, t2, 1
	bne	t2, zero, 8f
	mtc1	t6, $f1
	and	t4, t4, ~1
E 3
I 3
	beq	t0, zero, 1f		# is result positive?
	neg.d	$f0, $f0		# negate result
1:
	j	ra
E 3
8:
D 3
	bgez	t0, 1b
	mtc1	t4, $f0
E 3
I 3
	li	t1, 0x7ff00000		# result is infinity (MSW)
	mtc1	t1, $f1	
	mtc1	zero, $f0		# result is infinity (LSW)
	bge	v1, zero, 1f		# should result be negative infinity?
	neg.d	$f0, $f0		# result is negative infinity
1:
	add.d	$f0, $f0		# cause overflow faults if enabled
E 3
	j	ra
D 3
	neg.d	$f0, $f0
E 3
9:
D 3
	mtc1	zero, $f0
	bgez	t0, 1b
	mtc1	zero, $f1
E 3
I 3
	mov.d	$f0, $f12		# yes, result is just x
E 3
	j	ra
D 3
	neg.d	$f0, $f0
	.set	reorder
E 3
END(ldexp)
E 1
