h59768
s 00003/00001/00072
d D 8.2 93/09/09 14:45:15 hibler 6 5
c add MAP/UNMAP modes
e
s 00002/00002/00071
d D 8.1 93/06/10 21:23:37 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00046/00057
d D 7.4 92/06/05 15:23:16 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00012/00004/00091
d D 7.3 91/05/07 09:52:05 hibler 3 2
c 
e
s 00001/00001/00094
d D 7.2 90/11/04 19:30:16 mckusick 2 1
c update identifier from Utah
e
s 00095/00000/00000
d D 7.1 90/05/08 22:06:40 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: grfvar.h 1.8 89/01/18$
E 2
I 2
D 3
 * from: Utah $Hdr: grfvar.h 1.1 90/07/09$
E 3
I 3
D 4
 * from: Utah $Hdr: grfvar.h 1.9 91/01/21$
E 4
I 4
D 6
 * from: Utah $Hdr: grfvar.h 1.10 92/01/21$
E 6
I 6
 * from: Utah $Hdr: grfvar.h 1.11 93/08/13$
E 6
E 4
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

I 3
/* internal structure of lock page */
E 3
#define GRFMAXLCK	256
I 3
struct	grf_lockpage {
	u_char	gl_locks[GRFMAXLCK];
};
#define gl_lockslot gl_locks[0]
E 3

I 4
/*
 * Static configuration info for display types
 */
struct	grfsw {
	int	gd_hwid;	/* id returned by hardware */
	int	gd_swid;	/* id to be returned by software */
	char	*gd_desc;	/* description printed at config time */
	int	(*gd_init)();	/* boot time init routine */
	int	(*gd_mode)();	/* misc function routine */
};

E 4
/* per display info */
struct	grf_softc {
	int	g_flags;		/* software flags */
D 4
	int	g_type;			/* type of display */
E 4
I 4
	struct  grfsw *g_sw;		/* static configuration info */
E 4
D 3
	struct	grfinfo g_display;	/* hardware description */
E 3
I 3
	caddr_t	g_regkva;		/* KVA of registers */
	caddr_t	g_fbkva;		/* KVA of framebuffer */
	struct	grfinfo g_display;	/* hardware description (for ioctl) */
	struct	grf_lockpage *g_lock;	/* lock page associated with device */
E 3
	struct	proc *g_lockp;		/* process holding lock */
D 3
	int	g_lockpslot;		/* g_pid entry of g_lockp */
	u_char	*g_locks;		/* lock page associated with device */
E 3
	short	*g_pid;			/* array of pids with device open */
I 3
	int	g_lockpslot;		/* g_pid entry of g_lockp */
	caddr_t	g_data;			/* device dependent data */
E 3
};

/* flags */
#define	GF_ALIVE	0x01
#define GF_OPEN		0x02
#define GF_EXCLUDE	0x04
#define GF_WANTED	0x08
#define GF_BSDOPEN	0x10
#define GF_HPUXOPEN	0x20

D 4
/* display types - indices into grfdev */
#define	GT_TOPCAT	0
#define	GT_GATORBOX	1
#define	GT_RENAISSANCE	2
#define GT_LRCATSEYE	3
#define GT_HRCCATSEYE	4
#define GT_HRMCATSEYE	5
#define GT_DAVINCI	6

struct	grfdev {
	int	gd_hardid;	/* secondary id returned by hardware */
	int	gd_softid;	/* id returned by HP-UX */
	int	(*gd_init)();	/* boot time initialization */
	int	(*gd_mode)();	/* misc functions */
	char	*gd_desc;	/* text description */
};

/* hardware ids */
#define GID_GATORBOX	1
#define	GID_TOPCAT	2
#define GID_RENAISSANCE	4
#define GID_LRCATSEYE	5
#define GID_HRCCATSEYE	6
#define GID_HRMCATSEYE	7
#define GID_DAVINCI	8

/* software ids defined in grfioctl.h */

E 4
/* requests to mode routine */
#define GM_GRFON	1
#define GM_GRFOFF	2
#define GM_GRFOVON	3
#define GM_GRFOVOFF	4
I 4
#define GM_DESCRIBE	5
I 6
#define GM_MAP		6
#define GM_UNMAP	7
E 6
E 4

D 4
struct	grfreg {
	char	gr_pad0;
	u_char	gr_id;		/* +0x01 */
	char	gr_pad1[0x13];
	u_char	gr_id2;		/* +0x15 */
	char	gr_pad2[0x47];
	u_char	gr_fbomsb;	/* +0x5d */
	char	gr_pad3;
	u_char	gr_fbolsb;	/* +0x5f */
};
/* bitmapped display hardware id */
#define GRFHWID		0x39

/* internal bitmapped display address */
#define GRFIADDR	0x560000

E 4
/* minor device interpretation */
#define GRFOVDEV	0x10	/* overlay planes */
#define GRFIMDEV	0x20	/* images planes */
#define GRFUNIT(d)	((d) & 0x7)

#ifdef KERNEL
extern	struct grf_softc grf_softc[];
I 4
extern	struct grfsw grfsw[];
extern	int ngrfsw;
E 4
#endif
E 1
