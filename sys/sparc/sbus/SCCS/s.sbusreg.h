h22342
s 00002/00002/00033
d D 8.1 93/06/11 15:15:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00033
d D 7.3 93/04/20 19:29:04 torek 3 2
c spelling
e
s 00005/00000/00030
d D 7.2 92/07/21 16:52:08 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00030/00000/00000
d D 7.1 92/07/13 00:44:07 torek 1 0
c date and time created 92/07/13 00:44:07 by torek
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
 * from: $Header: sbusreg.h,v 1.5 92/06/17 06:59:44 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: sbusreg.h,v 1.6 92/11/26 02:28:14 torek Exp $ (LBL)
E 3
 */

/*
 * Sun-4c S-bus definitions.  (Should be made generic!)
 *
 * Sbus slot 0 is not a separate slot; it talks to the onboard I/O devices.
 * It is, however, addressed just like any `real' Sbus.
 *
 * Sbus device addresses are obtained from the FORTH PROMs.  They come
 * in `absolute' and `relative' address flavors, so we have to handle both.
 * Relative addresses do *not* include the slot number.
 */
#define	SBUS_BASE		0xf8000000
#define	SBUS_ADDR(slot, off)	(SBUS_BASE + ((slot) << 25) + (off))
#define	SBUS_ABS(a)		((unsigned)(a) >= SBUS_BASE)
#define	SBUS_ABS_TO_SLOT(a)	(((a) - SBUS_BASE) >> 25)
#define	SBUS_ABS_TO_OFFSET(a)	(((a) - SBUS_BASE) & 0x1ffffff)
E 1
