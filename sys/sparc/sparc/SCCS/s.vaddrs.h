h10893
s 00002/00002/00052
d D 8.1 93/06/11 15:17:40 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00052
d D 7.3 93/04/20 23:46:55 torek 3 2
c spelling
e
s 00005/00000/00049
d D 7.2 92/07/21 16:54:45 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00049/00000/00000
d D 7.1 92/07/13 00:44:43 torek 1 0
c date and time created 92/07/13 00:44:43 by torek
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
 * from: $Header: vaddrs.h,v 1.2 92/07/11 11:19:25 leres Exp $
E 3
I 3
 * from: $Header: vaddrs.h,v 1.3 92/11/26 03:05:11 torek Exp $
E 3
 */

/*
 * Special (fixed) virtual addresses on the SPARC.
 *
 * IO virtual space begins at 0xfe000000 (a segment boundary) and
 * continues up to the DMVA edge at 0xff000000.  (The upper all-1s
 * byte is special since some of the hardware supplies this to pad
 * a 24-bit address space out to 32 bits.  This is a legacy of the
 * IBM PC AT bus, actually, just so you know who to blame.)
 *
 * We reserve several pages at the base of our IO virtual space
 * for `oft-used' devices which must be present anyway in order to
 * configure.  In particular, we want the counter-timer register and
 * the Zilog ZSCC serial port chips to be mapped at fixed VAs to make
 * microtime() and the zs hardware interrupt handlers faster.
 *
 * Ideally, we should map the interrupt enable register here as well,
 * but that would require allocating pmegs in locore.s, so instead we
 * use one of the two `wasted' pages at KERNBASE+2*NBPG (see locore.s).
 */

#ifndef IODEV_0
#define	IODEV_0	0xfe000000	/* must match VM_MAX_KERNEL_ADDRESS */

#define	TIMERREG_VA	(IODEV_0 + 0*NBPG)
#define	ZS0_VA		(IODEV_0 + 1*NBPG)
#define	ZS1_VA		(IODEV_0 + 2*NBPG)
#define	AUXREG_VA	(IODEV_0 + 3*NBPG)
#define	IODEV_BASE	(IODEV_0 + 4*NBPG)
#define	IODEV_END	0xff000000		/* 16 MB of iospace */

#define	DVMA_BASE	0xfff00000
#define	DVMA_END	0xfffc0000

#endif /* IODEV_0 */
E 1
