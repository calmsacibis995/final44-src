h34036
s 00002/00002/00038
d D 8.1 93/06/11 15:17:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00038
d D 7.3 93/04/20 23:37:31 torek 3 2
c spelling
e
s 00005/00000/00035
d D 7.2 92/07/21 16:54:37 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00035/00000/00000
d D 7.1 92/07/13 00:44:40 torek 1 0
c date and time created 92/07/13 00:44:40 by torek
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
 * from: $Header: memreg.h,v 1.5 92/06/17 05:22:18 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: memreg.h,v 1.6 92/11/26 03:05:05 torek Exp $ (LBL)
E 3
 */

/*
 * Sun-4c memory error register.
 * The register is a single word.
 */
volatile int	*par_err_reg;	/* virtual address; NULL if not yet mapped */

/*
 * Bits in parity error register.
 * The register is cleared when read, except for the test and enable bits.
 */
#define	PER_ERR		0x80	/* a parity error occurred */
#define	PER_MULTI	0x40	/* more than one occurred */
#define	PER_TEST	0x20	/* test (invert parity) */
#define	PER_ENABLE	0x10	/* enable parity error reports */
#define	PER_BYTE0	0x08	/* error occurred in byte 0 (bits 31..24) */
#define	PER_BYTE1	0x04	/* error occurred in byte 1 (bits 23..16) */
#define	PER_BYTE2	0x02	/* error occurred in byte 2 (bits 15..8) */
#define	PER_BYTE3	0x01	/* error occurred in byte 3 (bits 7..0) */

#define	PER_BITS "\20\10ERR\7MULTI\6TEST\5ENABLE\4BYTE0\3BYTE1\2BYTE2\1BYTE3"
E 1
