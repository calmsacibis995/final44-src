/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fbio.h,v $
 * Revision 2.4  89/12/11  15:54:39  mja
 * 	Update to SunOS revision 5.14.
 * 	[89/12/11            mja]
 * 
 * Revision 2.3  89/03/09  21:30:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:28:38  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)fbio.h 5.14 88/09/19 SMI	*/

/*
 * Copyright 1986 by Sun Microsystems, Inc.
 */

#ifndef	FBIO_H_
#define FBIO_H_

#ifndef	ASM
/*
 * Frame buffer descriptor.
 * Returned by FBIOGTYPE ioctl on frame buffer devices.
 */
struct	fbtype {
	int	fb_type;	/* as defined below */
	int	fb_height;	/* in pixels */
	int	fb_width;	/* in pixels */
	int	fb_depth;	/* bits per pixel */
	int	fb_cmsize;	/* size of color map (entries) */
	int	fb_size;	/* total size in bytes */
};

#define FBIOGTYPE _IOR(F, 0, struct fbtype)

#ifdef	KERNEL
struct  fbpixrect {
	struct  pixrect *fbpr_pixrect;  /* Pixrect of dev returned here */
};
 
#define FBIOGPIXRECT _IOWR(F, 1, struct fbpixrect)
#endif	KERNEL

/*
 * General purpose structure for passing info in and out of frame buffers
 * (used for gp1)
 */
struct	fbinfo {
	int		fb_physaddr;	/* physical frame buffer address */
	int		fb_hwwidth;	/* fb board width */
	int		fb_hwheight;	/* fb board height */
	int		fb_addrdelta;	/* phys addr diff between boards */
	unsigned char	*fb_ropaddr;	/* fb va thru kernelmap */
	int		fb_unit;	/* minor devnum of fb */
};

#define FBIOGINFO _IOR(F, 2, struct fbinfo)

/*
 * Color map I/O
 */
struct	fbcmap {
	int		index;		/* first element (0 origin) */
	int		count;		/* number of elements */
	unsigned char	*red;		/* red color map elements */
	unsigned char	*green;		/* green color map elements */
	unsigned char	*blue;		/* blue color map elements */
};

#define FBIOPUTCMAP _IOW(F, 3, struct fbcmap)
#define FBIOGETCMAP _IOW(F, 4, struct fbcmap)

/* 
 * Set/Get attributes 
 */
#define FB_ATTR_NDEVSPECIFIC	8	/* no. of device specific values */
#define FB_ATTR_NEMUTYPES	4	/* no. of emulation types */

struct fbsattr {
	int	flags;			/* misc flags */
#define FB_ATTR_AUTOINIT	1	/* emulation auto init flag */
#define FB_ATTR_DEVSPECIFIC	2	/* dev. specific stuff valid flag */
	int	emu_type;		/* emulation type (-1 if unused) */
	int	dev_specific[FB_ATTR_NDEVSPECIFIC];	/* catchall */
};

struct fbgattr {
	int	real_type;		/* real device type */
	int	owner;			/* PID of owner, 0 if myself */
	struct fbtype fbtype;		/* fbtype info for real device */
	struct fbsattr sattr;		/* see above */
	int	emu_types[FB_ATTR_NEMUTYPES];	/* possible emulations */
						/* (-1 if unused) */
};

#define FBIOSATTR	_IOW(F, 5, struct fbsattr)
#define FBIOGATTR	_IOR(F, 6, struct fbgattr)


/* 
 * Video control 
 * (the unused bits are reserved for future use)
 */
#define FBVIDEO_OFF	0
#define FBVIDEO_ON	1

#define FBIOSVIDEO	_IOW(F, 7, int)
#define FBIOGVIDEO	_IOR(F, 8, int)

/* Vertical retrace support. */
#define FBIOVERTICAL	_IOW(F, 9, int)

#endif	!ASM

/* frame buffer type codes */
#define	FBTYPE_SUN1BW		0	/* Multibus mono */
#define	FBTYPE_SUN1COLOR	1	/* Multibus color */
#define	FBTYPE_SUN2BW		2	/* memory mono */
#define	FBTYPE_SUN2COLOR	3	/* color w/rasterop chips */
#define	FBTYPE_SUN2GP		4	/* GP1/GP2 */
#define	FBTYPE_SUN5COLOR	5	/* RoadRunner accelerator */
#define	FBTYPE_SUN3COLOR	6	/* memory color */
#define	FBTYPE_MEMCOLOR		7	/* memory 24-bit */
#define	FBTYPE_SUN4COLOR	8	/* memory color w/overlay */

#define FBTYPE_NOTSUN1          9       /* reserved for customer */
#define FBTYPE_NOTSUN2          10      /* reserved for customer */
#define FBTYPE_NOTSUN3          11      /* reserved for customer */
 
#define FBTYPE_SUNFAST_COLOR    12      /* accelerated 8bit */
#define FBTYPE_SUNROP_COLOR     13      /* MEMCOLOR with rop h/w */
#define FBTYPE_SUNFB_VIDEO      14      /* Simple video mixing */
#define FBTYPE_RESERVED5        15      /* reserved, do not use */
#define FBTYPE_RESERVED4        16      /* reserved, do not use */
#define FBTYPE_RESERVED3        17      /* reserved, do not use */
#define FBTYPE_RESERVED2        18      /* reserved, do not use */
#define FBTYPE_RESERVED1        19      /* reserved, do not use */

#define FBTYPE_LASTPLUSONE      20      /* max number of fbs (change as add) */

#endif	!FBIO_H_
