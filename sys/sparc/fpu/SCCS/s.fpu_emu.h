h45167
s 00002/00002/00161
d D 8.1 93/06/11 15:09:30 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00161
d D 7.3 93/04/20 06:18:59 torek 3 2
c spelling
e
s 00005/00000/00158
d D 7.2 92/07/21 16:39:05 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00158/00000/00000
d D 7.1 92/07/13 00:42:18 torek 1 0
c date and time created 92/07/13 00:42:18 by torek
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
 * from: $Header: fpu_emu.h,v 1.2 92/06/17 05:41:31 torek Exp $
E 3
I 3
 * from: $Header: fpu_emu.h,v 1.3 92/11/26 01:30:54 torek Exp $
E 3
 */

/*
 * Floating point emulator (tailored for SPARC, but structurally
 * machine-independent).
 *
 * Floating point numbers are carried around internally in an `expanded'
 * or `unpacked' form consisting of:
 *	- sign
 *	- unbiased exponent
 *	- mantissa (`1.' + 112-bit fraction + guard + round)
 *	- sticky bit
 * Any implied `1' bit is inserted, giving a 113-bit mantissa that is
 * always nonzero.  Additional low-order `guard' and `round' bits are
 * scrunched in, making the entire mantissa 115 bits long.  This is divided
 * into four 32-bit words, with `spare' bits left over in the upper part
 * of the top word (the high bits of fp_mant[0]).  An internal `exploded'
 * number is thus kept within the half-open interval [1.0,2.0) (but see
 * the `number classes' below).  This holds even for denormalized numbers:
 * when we explode an external denorm, we normalize it, introducing low-order
 * zero bits, so that the rest of the code always sees normalized values.
 *
 * Note that a number of our algorithms use the `spare' bits at the top.
 * The most demanding algorithm---the one for sqrt---depends on two such
 * bits, so that it can represent values up to (but not including) 8.0,
 * and then it needs a carry on top of that, so that we need three `spares'.
 *
 * The sticky-word is 32 bits so that we can use `OR' operators to goosh
 * whole words from the mantissa into it.
 *
 * All operations are done in this internal extended precision.  According
 * to Hennesey & Patterson, Appendix A, rounding can be repeated---that is,
 * it is OK to do a+b in extended precision and then round the result to
 * single precision---provided single, double, and extended precisions are
 * `far enough apart' (they always are), but we will try to avoid any such
 * extra work where possible.
 */
struct fpn {
	int	fp_class;		/* see below */
	int	fp_sign;		/* 0 => positive, 1 => negative */
	int	fp_exp;			/* exponent (unbiased) */
	int	fp_sticky;		/* nonzero bits lost at right end */
	u_int	fp_mant[4];		/* 115-bit mantissa */
};

#define	FP_NMANT	115		/* total bits in mantissa (incl g,r) */
#define	FP_NG		2		/* number of low-order guard bits */
#define	FP_LG		((FP_NMANT - 1) & 31)	/* log2(1.0) for fp_mant[0] */
#define	FP_QUIETBIT	(1 << (FP_LG - 1))	/* Quiet bit in NaNs (0.5) */
#define	FP_1		(1 << FP_LG)		/* 1.0 in fp_mant[0] */
#define	FP_2		(1 << (FP_LG + 1))	/* 2.0 in fp_mant[0] */

/*
 * Number classes.  Since zero, Inf, and NaN cannot be represented using
 * the above layout, we distinguish these from other numbers via a class.
 * In addition, to make computation easier and to follow Appendix N of
 * the SPARC Version 8 standard, we give each kind of NaN a separate class.
 */
#define	FPC_SNAN	-2		/* signalling NaN (sign irrelevant) */
#define	FPC_QNAN	-1		/* quiet NaN (sign irrelevant) */
#define	FPC_ZERO	0		/* zero (sign matters) */
#define	FPC_NUM		1		/* number (sign matters) */
#define	FPC_INF		2		/* infinity (sign matters) */

#define	ISNAN(fp)	((fp)->fp_class < 0)
#define	ISZERO(fp)	((fp)->fp_class == 0)
#define	ISINF(fp)	((fp)->fp_class == FPC_INF)

/*
 * ORDER(x,y) `sorts' a pair of `fpn *'s so that the right operand (y) points
 * to the `more significant' operand for our purposes.  Appendix N says that
 * the result of a computation involving two numbers are:
 *
 *	If both are SNaN: operand 2, converted to Quiet
 *	If only one is SNaN: the SNaN operand, converted to Quiet
 *	If both are QNaN: operand 2
 *	If only one is QNaN: the QNaN operand
 *
 * In addition, in operations with an Inf operand, the result is usually
 * Inf.  The class numbers are carefully arranged so that if
 *	(unsigned)class(op1) > (unsigned)class(op2)
 * then op1 is the one we want; otherwise op2 is the one we want.
 */
#define	ORDER(x, y) { \
	if ((u_int)(x)->fp_class > (u_int)(y)->fp_class) \
		SWAP(x, y); \
}
#define	SWAP(x, y) { \
	register struct fpn *swap; \
	swap = (x), (x) = (y), (y) = swap; \
}

/*
 * Emulator state.
 */
struct fpemu {
	struct	fpstate *fe_fpstate;	/* registers, etc */
	int	fe_fsr;			/* fsr copy (modified during op) */
	int	fe_cx;			/* exceptions */
	struct	fpn fe_f1;		/* operand 1 */
	struct	fpn fe_f2;		/* operand 2, if required */
	struct	fpn fe_f3;		/* available storage for result */
};

/*
 * Arithmetic functions.
 * Each of these may modify its inputs (f1,f2) and/or the temporary.
 * Each returns a pointer to the result and/or sets exceptions.
 */
struct	fpn *fpu_add(struct fpemu *);
#define	fpu_sub(fe) ((fe)->fe_f2.fp_sign ^= 1, fpu_add(fe))
struct	fpn *fpu_mul(struct fpemu *);
struct	fpn *fpu_div(struct fpemu *);
struct	fpn *fpu_sqrt(struct fpemu *);

/*
 * Other functions.
 */

/* Perform a compare instruction (with or without unordered exception). */
void	fpu_compare(struct fpemu *, int);

/* Build a new Quiet NaN (sign=0, frac=all 1's). */
struct	fpn *fpu_newnan(struct fpemu *);

/*
 * Shift a number right some number of bits, taking care of round/sticky.
 * Note that the result is probably not a well-formed number (it will lack
 * the normal 1-bit mant[0]&FP_1).
 */
int	fpu_shr(struct fpn *, int);

/* Conversion to and from internal format -- note asymmetry. */
int	fpu_itofpn(struct fpn *, u_int);
int	fpu_stofpn(struct fpn *, u_int);
int	fpu_dtofpn(struct fpn *, u_int, u_int);
int	fpu_xtofpn(struct fpn *, u_int, u_int, u_int, u_int);

u_int	fpu_fpntoi(struct fpemu *, struct fpn *);
u_int	fpu_fpntos(struct fpemu *, struct fpn *);
u_int	fpu_fpntod(struct fpemu *, struct fpn *);
u_int	fpu_fpntox(struct fpemu *, struct fpn *);

void	fpu_explode(struct fpemu *, struct fpn *, int, int);
void	fpu_implode(struct fpemu *, struct fpn *, int, u_int *);
E 1
