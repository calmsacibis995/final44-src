h01667
s 00002/00002/00035
d D 8.1 93/06/11 15:53:42 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00036
d D 7.2 92/10/11 10:20:04 bostic 4 3
c make kernel includes standard
e
s 00009/00001/00028
d D 7.1 91/05/09 23:32:49 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00000/00029
d D 1.2 91/05/09 20:35:50 william 2 1
c interim version, changes for net2 tape
e
s 00029/00000/00000
d D 1.1 90/11/08 18:44:18 bill 1 0
c date and time created 90/11/08 18:44:18 by bill
e
u
U
t
T
I 3
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/*
 * AT floppy controller registers and bitfields
D 3
 *	%W% (Berkeley) %G%
E 3
 */

/* uses NEC765 controller */
D 4
#include "../i386/isa/ic/nec765.h"
E 4
I 4
#include <i386/isa/ic/nec765.h>
E 4

/* registers */
#define	fdout	2	/* Digital Output Register (W) */
#define	FDO_FDSEL	0x01	/*  floppy device select */
#define	FDO_FRST	0x04	/*  floppy controller reset */
#define	FDO_FDMAEN	0x08	/*  enable floppy DMA and Interrupt */
#define	FDO_MOEN0	0x10	/*  motor enable drive 0 */
#define	FDO_MOEN1	0x20	/*  motor enable drive 1 */

#define	fdsts	4	/* NEC 765 Main Status Register (R) */
#define	fddata	5	/* NEC 765 Data Register (R/W) */

#define	fdctl	7	/* Control Register (W) */
#define	FDC_500KBPS	0x00	/* 500KBPS MFM drive transfer rate */
#define	FDC_300KBPS	0x01	/* 300KBPS MFM drive transfer rate */
#define	FDC_250KBPS	0x02	/* 250KBPS MFM drive transfer rate */
#define	FDC_125KBPS	0x03	/* 125KBPS FM drive transfer rate */

#define	fdin	7	/* Digital Input Register (R) */
#define	FDI_DCHG	0x80	/* diskette has been changed */


E 1
