h29268
s 00002/00002/00045
d D 8.1 93/06/11 15:15:04 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00045
d D 7.3 93/04/20 19:29:05 torek 3 2
c spelling
e
s 00005/00000/00042
d D 7.2 92/07/21 16:52:09 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00042/00000/00000
d D 7.1 92/07/13 00:44:08 torek 1 0
c date and time created 92/07/13 00:44:08 by torek
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
 * from: $Header: sbusvar.h,v 1.5 92/06/17 06:59:44 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: sbusvar.h,v 1.6 92/11/26 02:28:14 torek Exp $ (LBL)
E 3
 */

/*
 * S-bus variables.
 */
struct sbusdev {
	struct	device *sd_dev;		/* backpointer to generic */
	struct	sbusdev *sd_bchain;	/* forward link in bus chain */
	void	(*sd_reset) __P((struct device *));
};

/*
 * Sbus driver attach arguments.
 */
struct sbus_attach_args {
	struct	romaux sa_ra;		/* name, node, addr, etc */
	int	sa_slot;		/* Sbus slot number */
	int	sa_offset;		/* offset within slot */
};

/* variables per Sbus */
struct sbus_softc {
	struct	device sc_dev;		/* base device */
	int	sc_clockfreq;		/* clock frequency (in Hz) */
	struct	sbusdev *sc_sbdev;	/* list of all children */
};

int	sbusdev_match __P((struct cfdata *, void *));
void	sbus_establish __P((struct sbusdev *, struct device *));
E 1
