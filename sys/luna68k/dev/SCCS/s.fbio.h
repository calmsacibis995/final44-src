h46234
s 00002/00002/00070
d D 8.1 93/06/10 22:16:29 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00072
d D 7.3 93/02/02 10:56:23 akito 3 2
c delete FBIO_ON & FBIO_OFF
e
s 00006/00004/00068
d D 7.2 92/12/20 12:38:52 akito 2 1
c add FBIO_ON & FBIO_OFF ioctl
e
s 00072/00000/00000
d D 7.1 92/12/19 09:55:21 akito 1 0
c date and time created 92/12/19 09:55:21 by akito
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA
 * contract BG 91-66 and contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: fbio.h,v 1.3 91/12/13 22:16:32 torek Exp $ (LBL)
 *
 * from: sys/fbio.h		7.2 (Berkeley) 4/1/92
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Frame buffer ioctls (from Sprite, trimmed to essentials for X11).
 */

/*
 * Frame buffer type codes.
 */

#define	FBTYPE_BM		100	/* LUNA 4bit(1bit) frame buffer */

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
I 2
D 3
#define	FBIO_ON		_IO('F', 1)
#define	FBIO_OFF	_IO('F', 2)
E 3
E 2


/*
 * Reflesh Countor I/O
 */

struct fb_rfc {
	short	rfc_hcnt;
	short	rfc_vcnt;
};

D 2
#define	FBIOPUTRFCT	_IOW('F', 1, struct fb_rfc)
#define	FBIOGETRFCT	_IOR('F', 2, struct fb_rfc)
E 2
I 2
#define	FBIOSETRFCT	_IOW('F', 3, struct fb_rfc)
#define	FBIOGETRFCT	_IOR('F', 4, struct fb_rfc)
E 2


/*
 * Color map I/O.
 */

#ifdef notyet
struct fb_palette {
	int	index;		/* first element (0 origin) */
	int	count;		/* number of elements */
	u_char	*red;		/* red color map elements */
	u_char	*green;		/* green color map elements */
	u_char	*blue;		/* blue color map elements */
};

D 2
#define	FBIOPUTPALT	_IOW('F', 3, struct fb_palette)
#define	FBIOGETPALT	_IOR('F', 4, struct fb_palette)
E 2
I 2
#define	FBIOSETPALT	_IOW('F', 5, struct fb_palette)
#define	FBIOGETPALT	_IOR('F', 6, struct fb_palette)
E 2
#endif
E 1
