h09311
s 00002/00002/00029
d D 8.1 93/06/10 21:24:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00056/00018
d D 7.3 92/06/05 15:23:28 hibler 3 2
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00073
d D 7.2 90/11/04 19:36:27 mckusick 2 1
c update identifier from Utah
e
s 00074/00000/00000
d D 7.1 90/05/08 22:06:44 mckusick 1 0
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
 * from: Utah $Hdr: itereg.h 1.2 89/08/25$
E 2
I 2
D 3
 * from: Utah $Hdr: itereg.h 1.1 90/07/09$
E 3
I 3
 * from: Utah $Hdr: itereg.h 1.3 92/01/21$
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

D 3
#define REGADDR		ip->regbase
#define FBBASE		((volatile u_char *)ip->fbbase)
#define	FONTROM		((u_char *)(REGADDR+0x3B))
#define ITEREGS		((struct iteregs *)(REGADDR))

E 3
/*
D 3
 * All of the HP displays use the same font ROM setup. These structures
 * are used to get at them.
E 3
I 3
 * Offsets into the display ROM that is part of the first 4K of each
 * display device.
E 3
 */
I 3
#define FONTROM		0x3B	/* Offset of font information structure. */
#define FONTADDR	0x4	/* Offset from FONTROM to font address. */
#define FONTHEIGHT	0x0	/* Offset from font address to font height. */
#define FONTWIDTH	0x2	/* Offset from font address to font width. */
#define FONTDATA	0xA	/* Offset from font address to font glyphs. */
E 3

D 3
struct	iteregs {
	u_short	reset;
	u_short	interrupt;
	u_char	:8,
		fbwidth_h,
		:8,
		fbwidth_l,
		:8,
		fbheight_h,
		:8,
		fbheight_l,
		:8,
		dispwidth_h,
		:8,
		dispwidth_l,
		:8,
		dispheight_h,
		:8,
		dispheight_l;
};

struct	fontinfo {
	u_char	nfonts,	:8,
		fontid,	:8,
		haddr,	:8,
		laddr,	:8;
};

struct	font {
	u_char	fh,	:8,
		fw;
	u_char	pad[7],
		data[256];
};

#define draw_cursor(ip) { \
	WINDOWMOVER(ip, ip->cblanky, ip->cblankx, \
		    ip->cury * ip->ftheight, \
		    ip->curx * ip->ftwidth, \
		    ip->ftheight, ip->ftwidth, RR_XOR); \
        ip->cursorx = ip->curx; \
	ip->cursory = ip->cury; }

#define erase_cursor(ip) \
  	WINDOWMOVER(ip, ip->cblanky, ip->cblankx, \
		    ip->cursory * ip->ftheight, \
		    ip->cursorx * ip->ftwidth, \
		    ip->ftheight, ip->ftwidth, RR_XOR);
E 3
I 3
#ifdef hp300
#define FBBASE		((volatile u_char *)ip->fbbase)
#else
#define FBBASE		((volatile u_long *)ip->fbbase)
#endif
E 3
E 1
