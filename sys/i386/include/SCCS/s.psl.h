h60299
s 00002/00002/00033
d D 8.1 93/06/11 15:48:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00034
d D 5.2 91/01/18 14:32:14 william 3 2
c fixed just which copyright notice is included.
e
s 00012/00000/00023
d D 5.1 90/04/24 18:52:26 william 2 1
c 1st Berkeley Release
e
s 00023/00000/00000
d D 1.1 90/03/12 15:48:15 bill 1 0
c date and time created 90/03/12 15:48:15 by bill
e
u
U
t
T
I 2
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 3
 * %sccs.include.noredist.c%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
 * 386 processor status longword.
 */
#define	PSL_C		0x00000001	/* carry bit */
#define	PSL_PF		0x00000004	/* parity bit */
#define	PSL_AF		0x00000010	/* bcd carry bit */
#define	PSL_Z		0x00000040	/* zero bit */
#define	PSL_N		0x00000080	/* negative bit */
#define	PSL_ALLCC	0x000000d5	/* all cc bits - unlikely */
#define	PSL_T		0x00000100	/* trace enable bit */
#define	PSL_I		0x00000200	/* interrupt enable bit */
#define	PSL_D		0x00000400	/* string instruction direction bit */
#define	PSL_V		0x00000800	/* overflow bit */
#define	PSL_IOPL	0x00003000	/* i/o priviledge level enable */
#define	PSL_NT		0x00004000	/* nested task bit */
#define	PSL_RF		0x00010000	/* restart flag bit */
#define	PSL_VM		0x00020000	/* virtual 8086 mode bit */

#define	PSL_MBZ		0xfffc7fb7	/* must be zero bits */
#define	PSL_MBO		0x00000002	/* must be one bits */

#define	PSL_USERSET	(PSL_IOPL)
#define	PSL_USERCLR	(PSL_I|PSL_NT)
E 1
