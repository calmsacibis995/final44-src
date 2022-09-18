h61025
s 00016/00001/00080
d D 8.2 93/09/09 14:45:36 hibler 5 4
c support for GCDESCRIBE
e
s 00002/00002/00079
d D 8.1 93/06/10 21:23:30 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00005/00078
d D 7.3 92/06/05 15:23:17 hibler 3 2
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00082
d D 7.2 90/11/04 19:29:48 mckusick 2 1
c update identifier from Utah
e
s 00083/00000/00000
d D 7.1 90/05/08 22:06:39 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: grfioctl.h 1.13 89/01/18$
E 2
I 2
D 3
 * from: Utah $Hdr: grfioctl.h 1.1 90/07/09$
E 3
I 3
D 5
 * from: Utah $Hdr: grfioctl.h 1.15 92/01/22$
E 5
I 5
 * from: Utah $Hdr: grfioctl.h 1.17 93/08/13$
E 5
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

struct	grfinfo {
	int	gd_id;			/* HPUX identifier */
	caddr_t	gd_regaddr;		/* control registers physaddr */
	int	gd_regsize;		/* control registers size */
	caddr_t	gd_fbaddr;		/* frame buffer physaddr */
	int	gd_fbsize;		/* frame buffer size */
	short	gd_colors;		/* number of colors */
	short	gd_planes;		/* number of planes */
/* new stuff */
	int	gd_fbwidth;		/* frame buffer width */
	int	gd_fbheight;		/* frame buffer height */
	int	gd_dwidth;		/* displayed part width */
	int	gd_dheight;		/* displayed part height */
	int	gd_pad[6];		/* for future expansion */
};

/* types */
#define GRFGATOR	8
#define GRFBOBCAT	9
#define	GRFCATSEYE	9
#define GRFRBOX		10
I 3
#define GRFFIREEYE	11
#define GRFHYPERION	12
E 3
#define GRFDAVINCI	14

/*
 * HPUX ioctls (here for the benefit of the driver)
 */
struct	grf_slot {
	int	slot;
	u_char	*addr;
};

I 5
struct	grf_fbinfo {
	int	id;
	int	mapsize;
	int	dwidth, dlength;
	int	width, length;
	int	xlen;
	int	bpp, bppu;
	int	npl, nplbytes;
	char	name[32];
	int	attr;
	caddr_t	fbbase, regbase;
	caddr_t	regions[6];
};

E 5
#ifndef _IOH
#define _IOH(x,y)	(IOC_IN|((x)<<8)|y)	/* IOC_IN is IOC_VOID */

#define	GCID		_IOR('G', 0, int)
#define	GCON		_IOH('G', 1)
#define	GCOFF		_IOH('G', 2)
#define	GCAON		_IOH('G', 3)
#define	GCAOFF		_IOH('G', 4)
#define	GCMAP		_IOWR('G', 5, int)
#define	GCUNMAP		_IOWR('G', 6, int)
#define	GCLOCK		_IOH('G', 7)
#define	GCUNLOCK	_IOH('G', 8)
#define	GCLOCK_MINIMUM	_IOH('G', 9)
#define	GCUNLOCK_MINIMUM _IOH('G', 10)
#define	GCSTATIC_CMAP	_IOH('G', 11)
#define	GCVARIABLE_CMAP _IOH('G', 12)
#define GCSLOT		_IOWR('G', 13, struct grf_slot)
I 5
#define GCDESCRIBE	_IOR('G', 21, struct grf_fbinfo)
E 5

/* XXX: for now */
#define	IOMAPID		_IOR('M',0,int)	/* ??? */
#define	IOMAPMAP	_IOWR('M',1,int)
#define	IOMAPUNMAP	_IOWR('M',2,int)
#endif

/*
 * BSD ioctls
 */
#define	GRFIOCGINFO	_IOR('G', 0, struct grfinfo) /* get info on device */
#define	GRFIOCON	_IO('G', 1)		/* turn graphics on */
#define	GRFIOCOFF	_IO('G', 2)		/* turn graphics off */
#define GRFIOCMAP	_IOWR('G', 5, int)	/* map in regs+framebuffer */
#define GRFIOCUNMAP	_IOW('G', 6, int)	/* unmap regs+framebuffer */
D 3

/* compat - for old grfinfo structure */
struct ogrfinfo { char	oinfo[24]; };
#define	OGRFIOCGINFO	_IOR('G', 0, struct ogrfinfo)
E 3
E 1
