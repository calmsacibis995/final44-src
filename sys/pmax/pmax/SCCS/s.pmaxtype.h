h38566
s 00001/00001/00024
d D 8.2 95/06/02 17:25:28 ralph 4 3
c final changes for pmax 4.4-Lite II release
e
s 00002/00002/00023
d D 8.1 93/06/10 23:07:46 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00024
d D 7.2 92/12/20 11:46:48 ralph 2 1
c changes from Rick Macklem
e
s 00024/00000/00000
d D 7.1 92/11/15 16:28:39 ralph 1 0
c date and time created 92/11/15 16:28:39 by ralph
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University,
 * Ralph Campbell and Rick Macklem.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Mother board type byte of "systype" environment variable.
 */
#define	DS_PMAX		0x1	/* DECstation 2100/3100 */
#define	DS_3MAX		0x2	/* DECstation 5000/200 */
#define	DS_3MIN		0x3	/* DECstation 5000/1xx */
I 4
#define	DS_3MAXPLUS	0x4	/* DECstation 5000/240 */
E 4
#define	DS_LSIS		0x5	/* DECsystem 5800 */
#define	DS_MIPSFAIR	0x6	/* DECsystem 5400 */
#define	DS_MAXINE	0x7	/* Personal DECstation 5000/xx */
I 2
D 4
#define	DS_3MAXPLUS	0x8	/* DECstation 5000/240 (JUST A GUESS) */
E 4
E 2
#define	DS_MIPSFAIR2	0xb	/* DECsystem 5500 */
#define	DS_MIPSMATE	0xc	/* DECsystem 5100 */
E 1
