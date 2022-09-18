h13458
s 00004/00001/00112
d D 8.2 93/09/30 15:43:54 torek 6 5
c 1.11: Add parsedisk prototype.
e
s 00002/00002/00111
d D 8.1 93/06/11 15:11:36 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00002/00102
d D 7.3 93/04/20 06:30:52 torek 4 2
c update from elf: add bootpath and bootdv
e
s 00010/00001/00103
d R 7.3 93/04/20 06:28:46 torek 3 2
c update from elf: add bootpath and bootdv
e
s 00005/00000/00099
d D 7.2 92/07/21 16:41:25 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00099/00000/00000
d D 7.1 92/07/13 00:42:58 torek 1 0
c date and time created 92/07/13 00:42:58 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: autoconf.h,v 1.8 92/06/24 08:55:42 torek Exp $ (LBL)
E 4
I 4
D 6
 * from: $Header: autoconf.h,v 1.10 92/11/26 02:04:32 torek Exp $ (LBL)
E 6
I 6
 * from: $Header: autoconf.h,v 1.11 93/09/28 05:26:41 leres Exp $ (LBL)
E 6
E 4
 */

/*
 * Autoconfiguration information.
 */

/*
 * Most devices are configured according to information kept in
 * the FORTH PROMs.  In particular, we extract the `name', `reg',
 * and `address' properties of each device attached to the mainbus;
 * other drives may also use this information.  The mainbus itself
 * (which `is' the CPU, in some sense) gets just the node, with a
 * fake name ("mainbus").
 */
#define	RA_MAXINTR	8		/* max interrupts per device */
struct romaux {
	const char *ra_name;		/* name from FORTH PROM */
	int	ra_node;		/* FORTH PROM node ID */
	int	ra_iospace;		/* register space (obio, etc) */
	void	*ra_paddr;		/* register physical address */
	int	ra_len;			/* register length */
	void	*ra_vaddr;		/* ROM mapped virtual address, or 0 */
	struct rom_intr {		/* interrupt information: */
		int	int_pri;		/* priority (IPL) */
		int	int_vec;		/* vector (always 0?) */
	} ra_intr[RA_MAXINTR];
	int	ra_nintr;		/* number of interrupt info elements */
I 4
	struct	bootpath *ra_bp;	/* used for locating boot device */
E 4
};

/*
 * The various getprop* functions obtain `properties' from the ROMs.
 * getprop() obtains a property as a byte-sequence, and returns its
 * length; the others convert or make some other guarantee.
 */
int	getprop __P((int node, char *name, void *buf, int bufsiz));
char	*getpropstring __P((int node, char *name));
int	getpropint __P((int node, char *name, int deflt));

/* Frequently used options node */
extern int optionsnode;

/*
 * The romprop function gets physical and virtual addresses from the PROM
 * and fills in a romaux.  It returns 1 on success, 0 if the physical
 * address is not available as a "reg" property.
 */
int	romprop __P((struct romaux *ra, const char *name, int node));

/*
 * The matchbyname function is useful in drivers that are matched
 * by romaux name, i.e., all `mainbus attached' devices.  It expects
 * its aux pointer to point to a pointer to the name (the address of
 * a romaux structure suffices, for instance).
 */
int	matchbyname __P((struct device *, struct cfdata *cf, void *aux));

/*
 * `clockfreq' produces a printable representation of a clock frequency
 * (this is just a frill).
 */
char	*clockfreq __P((int freq));

/*
 * mapiodev maps an I/O device to a virtual address, returning the address.
 * mapdev does the real work: you can supply a special virtual address and
 * it will use that instead of creating one, but you must only do this if
 * you get it from ../sparc/vaddrs.h.
 */
void	*mapdev __P((void *pa, int va, int size));
#define	mapiodev(pa, size)	mapdev(pa, 0, size)

/*
 * Memory description arrays.  Shared between pmap.c and autoconf.c; no
 * one else should use this (except maybe mem.c, e.g., if we fix the VM to
 * handle discontiguous physical memory).
 */
struct memarr {
	u_int	addr;
	u_int	len;
};
int	makememarr(struct memarr *, int max, int which);
#define	MEMARR_AVAILPHYS	0
#define	MEMARR_TOTALPHYS	1

/* Pass a string to the FORTH interpreter.  May fail silently. */
void	rominterpret __P((char *));
I 4

/* Openprom V2 style boot path */
struct bootpath {
	char	name[8];		/* name of this node */
	int	val[2];			/* up to two optional values */
};

struct device *bootdv;			/* found during autoconfiguration */
I 6

/* Parse a disk string into a dev_t, return device struct pointer */
struct	device *parsedisk __P((char *, int, int, dev_t *));
E 6
E 4
E 1
