h50778
s 00002/00002/00067
d D 8.1 93/06/04 12:46:30 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00069/00000/00000
d D 5.1 93/03/08 18:48:14 ralph 1 0
c date and time created 93/03/08 18:48:14 by ralph
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

#include <machine/machAsmDefs.h>

#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */


#define DEXP_INF	0x7ff

	.set	noreorder

/*
 * isnan(x)
 *	double x;
 *
 * Return true if x is a NAN.
 */
LEAF(isnan)
	mfc1	v1, $f13		# get MSW of x
	mfc1	t3, $f12		# get LSW of x
	sll	t1, v1, 1		# get x exponent
	srl	t1, t1, 32 - 11
	bne	t1, DEXP_INF, 2f	# is it a finite number?
	sll	t2, v1, 32 - 20		# get x fraction
	bne	t3, zero, 1f		# is it a NAN?
	nop
	beq	t2, zero, 2f		# its infinity
	nop
1:
	j	ra
	li	v0, 1			# x is a NAN
2:
	j	ra
	move	v0, zero		# x is NOT a NAN
END(isnan)

/*
 * isinf(x)
 *	double x;
 *
 * Return true if x is infinity.
 */
LEAF(isinf)
	mfc1	v1, $f13		# get MSW of x
	mfc1	t3, $f12		# get LSW of x
	sll	t1, v1, 1		# get x exponent
	srl	t1, t1, 32 - 11
	bne	t1, DEXP_INF, 1f	# is it a finite number?
	sll	t2, v1, 32 - 20		# get x fraction
	bne	t3, zero, 1f		# is it a NAN?
	nop
	bne	t2, zero, 1f		# is it a NAN?
	nop
	j	ra
	li	v0, 1			# x is infinity
1:
	j	ra
	move	v0, zero		# x is NOT infinity
END(isinf)
E 1
