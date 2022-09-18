h10802
s 00004/00002/00113
d D 8.2 94/02/17 06:57:58 bostic 9 8
c Protect against multiple inclusion
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00113
d D 8.1 93/06/02 19:52:56 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00005/00095
d D 7.6 93/02/01 11:34:39 torek 7 6
c make event counters separate
e
s 00010/00003/00090
d D 7.5 92/11/16 18:27:45 torek 6 4
c add event counters; expand dv_xname for external use; fix copyright
e
s 00010/00003/00090
d R 7.5 92/11/16 17:56:19 torek 5 4
c add event counters; expand dv_xname for external use; fix copyright
e
s 00001/00001/00092
d D 7.4 92/07/10 00:24:36 torek 4 3
c copyright The regents, not just regents...
e
s 00020/00008/00073
d D 7.3 92/06/19 22:13:51 mckusick 3 2
c update from Chris
e
s 00003/00003/00078
d D 7.2 92/04/01 18:12:21 mckusick 2 1
c fix LBL contrib notice
e
s 00081/00000/00000
d D 7.1 92/02/19 17:47:29 mckusick 1 0
c from Chris Torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 Regents of the University of California.
E 4
I 4
D 8
 * Copyright (c) 1992 The Regents of the University of California.
E 4
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 2
 * This code is derived from software contributed to Berkeley by
 * the Computer Systems Engineering group at Lawrence Berkeley
 * Laboratory under DARPA contract BG 91-66.
E 2
I 2
D 3
 * This code is derived from software developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA
 * contract BG 91-66 and contributed to Berkeley.
E 3
I 3
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
E 3
E 2
 *
I 6
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 7
 *	California, Lawrence Berkeley Laboratories.
E 7
I 7
 *	California, Lawrence Berkeley Laboratory.
E 7
 *
E 6
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
D 9
 *
D 3
 * from: $Header: device.h,v 1.3 92/01/15 18:25:53 torek Exp $ (LBL)
E 3
I 3
D 6
 * from: $Header: device.h,v 1.6 92/06/11 17:56:45 torek Exp $ (LBL)
E 6
I 6
D 7
 * from: $Header: device.h,v 1.7 92/11/17 01:55:17 torek Exp $ (LBL)
E 7
I 7
 * from: $Header: device.h,v 1.9 93/02/01 19:34:50 torek Exp $ (LBL)
E 9
E 7
E 6
E 3
 */

I 9
#ifndef _SYS_DEVICE_H_
#define	_SYS_DEVICE_H_

E 9
/*
 * Minimal device structures.
I 3
 * Note that all ``system'' device types are listed here.
E 3
 */
D 3
enum devtype { DV_DULL, DV_DISK, DV_TAPE, DV_TTY };
E 3
I 3
enum devclass {
	DV_DULL,		/* generic, no special info */
	DV_CPU,			/* CPU (carries resource utilization) */
	DV_DISK,		/* disk drive (label, etc) */
	DV_IFNET,		/* network interface */
	DV_TAPE,		/* tape device */
	DV_TTY			/* serial line interface (???) */
};
E 3

struct device {
D 3
/*	enum	devclass dv_class;	/* class */
E 3
I 3
	enum	devclass dv_class;	/* this device's classification */
	struct	device *dv_next;	/* next in list of all */
	struct	cfdata *dv_cfdata;	/* config data that found us */
E 3
D 6
	char	*dv_name;		/* device name */
E 6
	int	dv_unit;		/* device unit number */
D 3
	int	dv_flags;		/* flags (copied from config) */
E 3
D 6
	char	*dv_xname;		/* expanded name (name + unit) */
E 6
I 6
	char	dv_xname[16];		/* external name (name + unit) */
E 6
	struct	device *dv_parent;	/* pointer to parent device */
I 6
D 7
	int	dv_evcnt[2];		/* event counters */
	char	dv_evnam[2][8];		/* and their names */
E 7
E 6
};

I 7
/* `event' counters (use zero or more per device instance, as needed) */
struct evcnt {
	struct	evcnt *ev_next;		/* linked list */
	struct	device *ev_dev;		/* associated device */
	int	ev_count;		/* how many have occurred */
	char	ev_name[8];		/* what to call them (systat display) */
};

E 7
/*
 * Configuration data (i.e., data placed in ioconf.c).
 */
struct cfdata {
	struct	cfdriver *cf_driver;	/* config driver */
	short	cf_unit;		/* unit number */
	short	cf_fstate;		/* finding state (below) */
	int	*cf_loc;		/* locators (machine dependent) */
	int	cf_flags;		/* flags from config */
	short	*cf_parents;		/* potential parents */
	void	(**cf_ivstubs)();	/* config-generated vectors, if any */
};
#define FSTATE_NOTFOUND	0	/* has not been found */
#define	FSTATE_FOUND	1	/* has been found */
D 3
#define	FSTATE_STAR	2	/* duplicable leaf (unimplemented) */
E 3
I 3
#define	FSTATE_STAR	2	/* duplicable */
E 3

typedef int (*cfmatch_t) __P((struct device *, struct cfdata *, void *));

/*
 * `configuration' driver (what the machine-independent autoconf uses).
 * As devices are found, they are applied against all the potential matches.
 * The one with the best match is taken, and a device structure (plus any
 * other data desired) is allocated.  Pointers to these are placed into
 * an array of pointers.  The array itself must be dynamic since devices
 * can be found long after the machine is up and running.
 */
struct cfdriver {
	void	**cd_devs;		/* devices found */
	char	*cd_name;		/* device name */
	cfmatch_t cd_match;		/* returns a match level */
	void	(*cd_attach) __P((struct device *, struct device *, void *));
I 3
	enum	devclass cd_class;	/* device classification */
E 3
	size_t	cd_devsize;		/* size of dev data (for malloc) */
	void	*cd_aux;		/* additional driver, if any */
I 6
D 7
	char	cd_evnam[2][8];		/* names for dv_evnam */
E 7
E 6
	int	cd_ndevs;		/* size of cd_devs array */
};

/*
 * Configuration printing functions, and their return codes.  The second
 * argument is NULL if the device was configured; otherwise it is the name
 * of the parent device.  The return value is ignored if the device was
 * configured, so most functions can return UNCONF unconditionally.
 */
typedef int (*cfprint_t) __P((void *, char *));
#define	QUIET	0		/* print nothing */
#define	UNCONF	1		/* print " not configured\n" */
#define	UNSUPP	2		/* print " not supported\n" */
I 3

I 7
/*
 * Pseudo-device attach information (function + number of pseudo-devs).
 */
struct pdevinit {
	void	(*pdev_attach) __P((int));
	int	pdev_count;
};

E 7
struct	device *alldevs;	/* head of list of all devices */
I 7
struct	evcnt *allevents;	/* head of list of all events */
E 7
E 3

struct cfdata *config_search __P((cfmatch_t, struct device *, void *));
struct cfdata *config_rootsearch __P((cfmatch_t, char *, void *));
int config_found __P((struct device *, void *, cfprint_t));
int config_rootfound __P((char *, void *));
void config_attach __P((struct device *, struct cfdata *, void *, cfprint_t));
I 7
void evcnt_attach __P((struct device *, const char *, struct evcnt *));
I 9
#endif /* !_SYS_DEVICE_H_ */
E 9
E 7
E 1
