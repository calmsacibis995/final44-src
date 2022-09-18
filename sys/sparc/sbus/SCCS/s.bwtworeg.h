h50789
s 00002/00002/00054
d D 8.1 93/06/11 15:14:29 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00054
d D 7.3 93/04/20 19:29:01 torek 3 2
c spelling
e
s 00005/00000/00051
d D 7.2 92/07/21 16:52:02 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00051/00000/00000
d D 7.1 92/07/13 00:44:02 torek 1 0
c date and time created 92/07/13 00:44:02 by torek
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
 * from: $Header: bwtworeg.h,v 1.3 92/06/17 06:59:30 torek Exp $
E 3
I 3
 * from: $Header: bwtworeg.h,v 1.4 92/11/26 02:28:05 torek Exp $
E 3
 */

/*
 * bwtwo display registers.
 *
 * The registers start at offset 0x400000 and repeat every 32 bytes
 * (presumably only the low order address lines are decoded).  Video RAM
 * starts at offset 0x800000.  We use separate pointers to each so that
 * the sparc addressing modes work well.
 */
struct bwtworeg {
	/*
	 * The xxx0 range is all 0xff on my IPC but causes a screen glitch
	 * on my SS1+, so it must do *some*thing... the xxx1 range is full
	 * of values but I do not know what they are.  bw_ctl changes for
	 * a blanked screen.
	 */
	char	bw_xxx0[16];
	u_char	bw_ctl;			/* contains video enable */
	char	bw_xxx1[15];
};

/* bits in bw_ctl */
#define	CTL_VE	0x40			/* video enable */

/* offsets */
#define	BWREG_ID	0
#define	BWREG_REG	0x400000
#define	BWREG_MEM	0x800000

/* same, but for gdb */
struct bwtwo_all {
	long	ba_id;			/* ID = 0xfe010104 on my IPC */
	char	ba_xxx0[0x400000-4];
	struct	bwtworeg ba_reg;	/* control registers */
	char	ba_xxx1[0x400000-32];
	char	ba_ram[4096];		/* actually larger */
};
E 1
