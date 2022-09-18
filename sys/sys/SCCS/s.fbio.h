h01320
s 00039/00001/00121
d D 8.2 93/10/30 23:02:47 torek 4 3
c add ioctls needed for X11 on cg6
e
s 00002/00002/00120
d D 8.1 93/06/02 19:53:27 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00119
d D 7.2 92/04/01 18:12:22 mckusick 2 1
c fix LBL contrib notice
e
s 00122/00000/00000
d D 7.1 92/02/19 17:48:19 mckusick 1 0
c from Chris Torek
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
D 2
 * This code is derived from software contributed to Berkeley by
 * the Computer Systems Engineering group at Lawrence Berkeley
 * Laboratory under DARPA contract BG 91-66.
E 2
I 2
 * This code is derived from software developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA
 * contract BG 91-66 and contributed to Berkeley.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: fbio.h,v 1.3 91/12/13 22:16:32 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: fbio.h,v 1.6 93/10/31 06:01:56 torek Exp $ (LBL)
E 4
 */

/*
 * Frame buffer ioctls (from Sprite, trimmed to essentials for X11).
 */

/*
 * Frame buffer type codes.
 */
#define	FBTYPE_SUN1BW		0	/* multibus mono */
#define	FBTYPE_SUN1COLOR	1	/* multibus color */
#define	FBTYPE_SUN2BW		2	/* memory mono */
#define	FBTYPE_SUN2COLOR	3	/* color w/rasterop chips */
#define	FBTYPE_SUN2GP		4	/* GP1/GP2 */
#define	FBTYPE_SUN5COLOR	5	/* RoadRunner accelerator */
#define	FBTYPE_SUN3COLOR	6	/* memory color */
#define	FBTYPE_MEMCOLOR		7	/* memory 24-bit */
#define	FBTYPE_SUN4COLOR	8	/* memory color w/overlay */

#define	FBTYPE_NOTSUN1		9	/* reserved for customer */
#define	FBTYPE_NOTSUN2		10	/* reserved for customer */
#define	FBTYPE_NOTSUN3		11	/* reserved for customer */

#define	FBTYPE_SUNFAST_COLOR	12	/* accelerated 8bit */
#define	FBTYPE_SUNROP_COLOR	13	/* MEMCOLOR with rop h/w */
#define	FBTYPE_SUNFB_VIDEO	14	/* Simple video mixing */
#define	FBTYPE_RESERVED5	15	/* reserved, do not use */
#define	FBTYPE_RESERVED4	16	/* reserved, do not use */
#define	FBTYPE_RESERVED3	17	/* reserved, do not use */
#define	FBTYPE_RESERVED2	18	/* reserved, do not use */
#define	FBTYPE_RESERVED1	19	/* reserved, do not use */

#define	FBTYPE_LASTPLUSONE	20	/* max number of fbs (change as add) */

/*
 * Frame buffer descriptor as returned by FBIOGTYPE.
 */
struct fbtype {
	int	fb_type;	/* as defined above */
	int	fb_height;	/* in pixels */
	int	fb_width;	/* in pixels */
	int	fb_depth;	/* bits per pixel */
	int	fb_cmsize;	/* size of color map (entries) */
	int	fb_size;	/* total size in bytes */
};
#define	FBIOGTYPE	_IOR('F', 0, struct fbtype)

#ifdef notdef
/*
 * General purpose structure for passing info in and out of frame buffers
 * (used for gp1) -- unsupported.
 */
struct fbinfo {
	int	fb_physaddr;	/* physical frame buffer address */
	int	fb_hwwidth;	/* fb board width */
	int	fb_hwheight;	/* fb board height */
	int	fb_addrdelta;	/* phys addr diff between boards */
	u_char	*fb_ropaddr;	/* fb virtual addr */
	int	fb_unit;	/* minor devnum of fb */
};
#define	FBIOGINFO	_IOR('F', 2, struct fbinfo)
#endif

/*
 * Color map I/O.
 */
struct fbcmap {
	int	index;		/* first element (0 origin) */
	int	count;		/* number of elements */
	u_char	*red;		/* red color map elements */
	u_char	*green;		/* green color map elements */
	u_char	*blue;		/* blue color map elements */
};
#define	FBIOPUTCMAP	_IOW('F', 3, struct fbcmap)
#define	FBIOGETCMAP	_IOW('F', 4, struct fbcmap)

/*
 * Set/get attributes.
 */
#define	FB_ATTR_NDEVSPECIFIC	8	/* no. of device specific values */
#define	FB_ATTR_NEMUTYPES	4	/* no. of emulation types */

struct fbsattr {
	int	flags;			/* flags; see below */
	int	emu_type;		/* emulation type (-1 if unused) */
	int	dev_specific[FB_ATTR_NDEVSPECIFIC];	/* catchall */
};
#define	FB_ATTR_AUTOINIT	1	/* emulation auto init flag */
#define	FB_ATTR_DEVSPECIFIC	2	/* dev. specific stuff valid flag */

struct fbgattr {
	int	real_type;		/* real device type */
	int	owner;			/* PID of owner, 0 if myself */
	struct	fbtype fbtype;		/* fbtype info for real device */
	struct	fbsattr sattr;		/* see above */
	int	emu_types[FB_ATTR_NEMUTYPES];	/* possible emulations */
						/* (-1 if unused) */
};
/*	FBIOSATTR	_IOW('F', 5, struct fbsattr) -- unsupported */
#define	FBIOGATTR	_IOR('F', 6, struct fbgattr)

/*
 * Video control.
 */
#define	FBVIDEO_OFF		0
#define	FBVIDEO_ON		1

#define	FBIOSVIDEO	_IOW('F', 7, int)
#define	FBIOGVIDEO	_IOR('F', 8, int)
I 4

/*
 * Hardware cursor control (for, e.g., CG6).  A rather complex and icky
 * interface that smells like VMS, but there it is....
 */
struct fbcurpos {
	short	x;
	short	y;
};

struct fbcursor {
	short	set;		/* flags; see below */
	short	enable;		/* nonzero => cursor on, 0 => cursor off */
	struct	fbcurpos pos;	/* position on display */
	struct	fbcurpos hot;	/* hot-spot within cursor */
	struct	fbcmap cmap;	/* cursor color map */
	struct	fbcurpos size;	/* number of valid bits in image & mask */
	caddr_t	image;		/* cursor image bits */
	caddr_t	mask;		/* cursor mask bits */
};
#define	FB_CUR_SETCUR	0x01	/* set on/off (i.e., obey fbcursor.enable) */
#define	FB_CUR_SETPOS	0x02	/* set position */
#define	FB_CUR_SETHOT	0x04	/* set hot-spot */
#define	FB_CUR_SETCMAP	0x08	/* set cursor color map */
#define	FB_CUR_SETSHAPE	0x10	/* set size & bits */
#define	FB_CUR_SETALL	(FB_CUR_SETCUR | FB_CUR_SETPOS | FB_CUR_SETHOT | \
			 FB_CUR_SETCMAP | FB_CUR_SETSHAPE)

/* controls for cursor attributes & shape (including position) */
#define	FBIOSCURSOR	_IOW('F', 24, struct fbcursor)
#define	FBIOGCURSOR	_IOWR('F', 25, struct fbcursor)

/* controls for cursor position only */
#define	FBIOSCURPOS	_IOW('F', 26, struct fbcurpos)
#define	FBIOGCURPOS	_IOW('F', 27, struct fbcurpos)

/* get maximum cursor size */
#define	FBIOGCURMAX	_IOR('F', 28, struct fbcurpos)
E 4
E 1
