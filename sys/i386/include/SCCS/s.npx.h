h51752
s 00002/00002/00051
d D 8.1 93/06/11 15:48:03 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00052
d D 5.3 91/01/18 14:32:11 william 4 3
c fixed just which copyright notice is included.
e
s 00010/00004/00043
d D 5.2 90/11/14 12:59:14 bill 3 2
c fpu.h ->npx.h, added emc stuff
e
s 00012/00000/00035
d D 5.1 90/04/24 18:52:09 william 2 1
c 1st Berkeley Release
e
s 00035/00000/00000
d D 1.1 90/03/12 15:47:52 bill 1 0
c date and time created 90/03/12 15:47:52 by bill
e
u
U
t
T
I 2
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 4
 * %sccs.include.noredist.c%
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
D 3
 * 287/387 Floating Point Data Structures and Constants
E 3
I 3
 * 287/387 NPX Coprocessor Data Structures and Constants
E 3
 * W. Jolitz 1/90
 */

D 3
#ifndef	___FPU87___
#define	___FPU87___
E 3
I 3
#ifndef	___NPX87___
#define	___NPX87___
E 3

/* Environment information of floating point unit */
struct	env87 {
	long	en_cw;		/* control word (16bits) */
	long	en_sw;		/* status word (16bits) */
	long	en_tw;		/* tag word (16bits) */
	long	en_fip;		/* floating point instruction pointer */
	u_short	en_fcs;		/* floating code segment selector */
	u_short	en_opcode;	/* opcode last executed (11 bits ) */
	long	en_foo;		/* floating operand offset */
	long	en_fos;		/* floating operand segment selector */
};

/* Contents of each floating point accumulator */
struct	fpacc87 {
	u_long	fp_mantlo;	/* mantissa low (31:0) */
	u_long	fp_manthi;	/* mantissa high (63:32) */
	int	fp_exp:15;	/* exponent */
	int	fp_sgn:1;	/* mantissa sign */
};

/* Floating point context */
struct	save87 {
	struct	env87 sv_env;		/* floating point control/status */
	struct	fpacc87	sv_ac[8];	/* accumulator contents, 0-7 */
};

D 3
#endif	___FPU87___
E 3
I 3
/* Cyrix EMC memory - mapped coprocessor context switch information */
struct	emcsts {
	long	em_msw;		/* memory mapped status register when swtched */
	long	em_tar;		/* memory mapped temp A register when swtched */
	long	em_dl;		/* memory mapped D low register when swtched */
};
#endif	___NPX87___
E 3
E 1
