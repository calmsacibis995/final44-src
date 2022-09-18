h33536
s 00002/00002/00072
d D 8.1 93/06/10 21:34:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00074/00000/00000
d D 7.1 92/12/27 09:40:51 hibler 1 0
c date and time created 92/12/27 09:40:51 by hibler
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 2
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: rdvar.h 1.1 92/12/21$
 *
 *	%W% (Berkeley) %G%
 */

struct	rdidentinfo {
	short	ri_hwid;		/* 2 byte HW id */
	short	ri_maxunum;		/* maximum allowed unit number */
	char	*ri_desc;		/* drive type description */
	int	ri_nblocks;		/* DEV_BSIZE blocks on disk */
};

struct	rdinfo {
	struct	disklabel ri_label;	/* label */
	int	ri_bopen;		/* mask of open block devs */
	int	ri_copen;		/* mask of open char devs */
	int	ri_open;		/* composite mask of open devs */
};

struct	rd_softc {
	struct	hp_device *sc_hd;
	int	sc_flags;
	short	sc_type;
	short	sc_punit;
	char	*sc_addr;
	int	sc_resid;
	u_int	sc_wpms;
	struct	rdinfo sc_info;
	struct	devqueue sc_dq;
	struct	rd_iocmd sc_ioc;
	struct	rd_rscmd sc_rsc;
	struct	rd_stat sc_stat;
	struct	rd_ssmcmd sc_ssmc;
	struct	rd_srcmd sc_src;
	struct	rd_clearcmd sc_clear;
};

/* sc_flags values */
#define	RDF_ALIVE	0x01
#define	RDF_SEEK	0x02
#define RDF_SWAIT	0x04
#define RDF_OPENING	0x08
#define RDF_CLOSING	0x10
#define RDF_WANTED	0x20
#define RDF_WLABEL	0x40

struct rdstats {
	long	rdretries;
	long	rdresets;
	long	rdtimeouts;
	long	rdpolltries;
	long	rdpollwaits;
};

#define	rdunit(x)	(minor(x) >> 3)
#define rdpart(x)	(minor(x) & 0x7)
#define	rdpunit(x)	((x) & 7)
#define rdlabdev(d)	(dev_t)(((int)(d)&~7)|2)	/* rd?c */

#define	b_cylin		b_resid

#define	RDRETRY		5
#define RDWAITC		1	/* min time for timeout in seconds */
E 1
