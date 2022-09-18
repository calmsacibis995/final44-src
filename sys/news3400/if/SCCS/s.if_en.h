h43273
s 00002/00002/00054
d D 8.1 93/06/11 14:56:58 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00055
d D 7.2 92/06/27 03:57:51 utashiro 2 1
c make bpf works
e
s 00055/00000/00000
d D 7.1 92/06/04 15:59:11 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: if_en.h,v 4.300 91/06/09 06:25:56 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Structure of an Ethernet header -- receive format
 */
struct en_rheader {
	u_char	enr_dhost[6];		/* Destination Host */
	u_char	enr_shost[6];		/* Source Host */
	u_short	enr_type;		/* Type of packet */
};

#ifdef KERNEL
/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * es_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 * We also have, for each interface, a IOP interface structure, which
 * contains information about the IOP resources held by the interface:
 * map registers, buffered data paths, etc.  Information is cached in this
 * structure for use by the if_iop.c routines in running the interface
 * efficiently.
 */
struct	en_softc {
	struct	arpcom es_ac;		/* Ethernet common part */
	struct	ifnews es_ifnews;	/* IOP resources */
	int	es_flags;
#ifdef NOTDEF /* KU:XXX */
	int	es_oactive;		/* # of active output buffers */
#endif
	int	es_interval;		/* interval of watchdog */
I 2
	caddr_t	es_bpf;
E 2
};

#define	es_if	es_ac.ac_if		/* network-visible interface */
#define	es_addr	es_ac.ac_enaddr		/* hardware Ethernet address */

#define	ENF_RUNNING	0x01		/* board is running */
#define	ENF_SETADDR	0x02		/* physical address is changed */

#define	ENWATCHINTERVAL	60		/* once every 60 seconds */

#endif /* KERNEL */
E 1
