h46148
s 00002/00002/00068
d D 8.1 93/06/11 15:09:21 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00068
d D 7.3 93/04/20 06:18:57 torek 3 2
c spelling
e
s 00005/00000/00065
d D 7.2 92/07/21 16:39:03 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00065/00000/00000
d D 7.1 92/07/13 00:42:16 torek 1 0
c date and time created 92/07/13 00:42:16 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: fpu_arith.h,v 1.2 92/06/17 05:41:28 torek Exp $
E 3
I 3
 * from: $Header: fpu_arith.h,v 1.3 92/11/26 01:30:50 torek Exp $
E 3
 */

/*
 * Extended-precision arithmetic.
 *
 * We hold the notion of a `carry register', which may or may not be a
 * machine carry bit or register.  On the SPARC, it is just the machine's
 * carry bit.
 *
 * In the worst case, you can compute the carry from x+y as
 *	(unsigned)(x + y) < (unsigned)x
 * and from x+y+c as
 *	((unsigned)(x + y + c) <= (unsigned)x && (y|c) != 0)
 * for example.
 */

/* set up for extended-precision arithemtic */
#define	FPU_DECL_CARRY

/*
 * We have three kinds of add:
 *	add with carry:					  r = x + y + c
 *	add (ignoring current carry) and set carry:	c'r = x + y + 0
 *	add with carry and set carry:			c'r = x + y + c
 * The macros use `C' for `use carry' and `S' for `set carry'.
 * Note that the state of the carry is undefined after ADDC and SUBC,
 * so if all you have for these is `add with carry and set carry',
 * that is OK.
 *
 * The same goes for subtract, except that we compute x - y - c.
 *
 * Finally, we have a way to get the carry into a `regular' variable,
 * or set it from a value.  SET_CARRY turns 0 into no-carry, nonzero
 * into carry; GET_CARRY sets its argument to 0 or 1.
 */
#define	FPU_ADDC(r, x, y) \
	asm volatile("addx %1,%2,%0" : "=r"(r) : "r"(x), "r"(y))
#define	FPU_ADDS(r, x, y) \
	asm volatile("addcc %1,%2,%0" : "=r"(r) : "r"(x), "r"(y))
#define	FPU_ADDCS(r, x, y) \
	asm volatile("addxcc %1,%2,%0" : "=r"(r) : "r"(x), "r"(y))
#define	FPU_SUBC(r, x, y) \
	asm volatile("subx %1,%2,%0" : "=r"(r) : "r"(x), "r"(y))
#define	FPU_SUBS(r, x, y) \
	asm volatile("subcc %1,%2,%0" : "=r"(r) : "r"(x), "r"(y))
#define	FPU_SUBCS(r, x, y) \
	asm volatile("subxcc %1,%2,%0" : "=r"(r) : "r"(x), "r"(y))

#define	FPU_GET_CARRY(r) asm volatile("addx %%g0,%%g0,%0" : "=r"(r))
#define	FPU_SET_CARRY(v) asm volatile("addcc %0,-1,%%g0" : : "r"(v))

#define	FPU_SHL1_BY_ADD	/* shift left 1 faster by ADDC than (a<<1)|(b>>31) */
E 1
