h60662
s 00002/00002/00042
d D 8.1 93/06/11 15:54:20 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00001/00035
d D 7.1 91/05/09 23:32:52 bostic 2 1
c new copyright; att/bsd/shared
e
s 00036/00000/00000
d D 1.1 90/11/08 19:26:59 bill 1 0
c date and time created 90/11/08 19:26:59 by bill
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
 * ISA Bus Autoconfiguration
D 2
 *	%W% (Berkeley) %G%
E 2
 */

/*
 * Per device structure.
 */
struct isa_device {
	struct	isa_driver *id_driver;
	short	id_iobase;	/* base i/o address */
	short	id_irq;		/* interrupt request */
	short	id_drq;		/* DMA request */
	caddr_t id_maddr;	/* physical i/o memory address on bus (if any)*/
	int	id_msize;	/* size of i/o memory */
	int	(*id_intr)();	/* interrupt interface routine */
	int	id_unit;	/* unit number */
	int	id_scsiid;	/* scsi id if needed */
	int	id_alive;	/* device is present */
};

/*
 * Per-driver structure.
 *
 * Each device driver defines entries for a set of routines
 * as well as an array of types which are acceptable to it.
 * These are used at boot time by the configuration program.
 */
struct isa_driver {
	int	(*probe)();		/* test whether device is present */
	int	(*attach)();		/* setup driver for a device */
	char	*name;			/* device name */
};

extern struct isa_device isa_devtab_bio[], isa_devtab_tty[], isa_devtab_net[],
		isa_devtab_null[];
E 1
