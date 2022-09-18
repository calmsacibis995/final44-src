h24375
s 00005/00034/00033
d D 8.2 93/10/30 22:11:31 torek 6 4
c move Brooktree registers & colormap data structures to common code
c to share between cg3 and cg6 drivers.
e
s 00005/00034/00033
d R 8.2 93/10/30 22:07:33 torek 5 4
c 1.6: move Brooktree registers & colormap data structures to common code
c to share between cg3 and cg6 drivers.
e
s 00002/00002/00065
d D 8.1 93/06/11 15:14:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00065
d D 7.3 93/04/20 19:29:03 torek 3 2
c spelling
e
s 00005/00000/00062
d D 7.2 92/07/21 16:52:04 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00062/00000/00000
d D 7.1 92/07/13 00:44:03 torek 1 0
c date and time created 92/07/13 00:44:03 by torek
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
 * from: $Header: cgthreereg.h,v 1.4 92/06/17 06:59:32 torek Exp $
E 3
I 3
D 6
 * from: $Header: cgthreereg.h,v 1.5 92/11/26 02:28:07 torek Exp $
E 6
I 6
 * from: $Header: cgthreereg.h,v 1.7 93/10/31 05:09:28 torek Exp $
E 6
E 3
 */

/*
D 6
 * cgthree display registers.
 *
 * The registers start at offset 0x400000 and repeat every 32 bytes
 * (presumably only the low order address lines are decoded).  Video RAM
 * starts at offset 0x800000.  We use separate pointers to each so that
 * the sparc addressing modes work well.
 *
 * The cg3 has a Brooktree Bt458 (?) chip to do everything (Brooktree
 * makes the only decent color frame buffer chips).  To update the
 * color map one would normally do byte writes, but the hardware
 * takes longword writes.  Since there are three registers for each
 * color map entry (R, then G, then B), we have to set color 1 with
 * a write to address 0 (setting 0's R/G/B and color 1's R) followed
 * by a second write to address 1 (setting color 1's G/B and color 2's
 * R/G).  Software must therefore keep a copy of the current map.
 *
 * The colormap address register increments automatically, so the above
 * write is done as:
 *
 *	p->cg3_cadr = 0;
 *	p->cg3_cmap = R0G0B0R1;
 *	p->cg3_cmap = G1B1R2G2;
 *
 * Yow!
E 6
I 6
 * cgthree display registers.  Much like bwtwo registers, except that
 * there is a Brooktree Video DAC in there (so we also use btreg.h).
E 6
 */
D 6
struct cgthreereg {
	u_int	cg3_addr;		/* ?any? address register */
	u_int	cg3_cmap;		/* colormap data register */
	u_int	cg3_ctrl;		/* control register */
	u_int	cg3_omap;		/* overlay map register */
	char	cg3_xxx0[16];		/* ? (make same size as bwtwo) */
};
E 6

/* offsets */
#define	CG3REG_ID	0
#define	CG3REG_REG	0x400000
#define	CG3REG_MEM	0x800000

/* same, but for gdb */
struct cgthree_all {
	long	ba_id;			/* ID = 0xfe010104 on my IPC */
	char	ba_xxx0[0x400000-4];
D 6
	struct	cgthreereg ba_reg;	/* control registers */
	char	ba_xxx1[0x400000-32];
E 6
I 6
	struct	bt_regs ba_btreg;	/* Brooktree registers */
	char	ba_xxx1[0x400000-sizeof(struct bt_regs)];
E 6
	char	ba_ram[4096];		/* actually larger */
};
E 1
