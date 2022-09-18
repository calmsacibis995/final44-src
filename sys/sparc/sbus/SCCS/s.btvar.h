h15977
s 00002/00002/00045
d D 8.2 94/01/21 19:49:19 bostic 2 1
c copyright typo
e
s 00047/00000/00000
d D 8.1 93/10/30 22:02:05 torek 1 0
c date and time created 93/10/30 22:02:05 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: btvar.h,v 1.1 93/10/12 15:29:01 torek Exp $
 */

/*
 * Brooktree color frame buffer state variables (see btreg.h).
 *
 * Unfortunately, remarkably little code can be shared between the
 * cg3 and cg6 drivers here, as the cg3 registers do longword-ops
 * `as expected', but the cg6 ones use only the upper byte.
 *
 * Still, the software color map manipulation is not completely trivial.
 */
union bt_cmap {
	u_char  cm_map[256][3];		/* 256 R/G/B entries */
	u_int   cm_chip[256 * 3 / 4];	/* the way the chip gets loaded */
};

/*
 * Routines in bt_subr.c.
 */
int	bt_getcmap __P((struct fbcmap *, union bt_cmap *, int));
int	bt_putcmap __P((struct fbcmap *, union bt_cmap *, int));

/*
 * Compute (x / 4) * 3 and (x / 4) * 4.  These are used in turning
 * RGB indices (which are in multiples of three) into `chip RGB' values
 * (which are in multiples of four).
 */
#define	BT_D4M3(x) ((((x) >> 2) << 1) + ((x) >> 2))	/* (x / 4) * 3 */
#define	BT_D4M4(x) ((x) & ~3)				/* (x / 4) * 4 */
E 1
