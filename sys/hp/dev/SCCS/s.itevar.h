h64578
s 00002/00002/00159
d D 8.1 93/06/10 21:24:28 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00159
d D 7.4 92/12/27 09:12:59 hibler 4 3
c add ITE_CURSORON
e
s 00035/00008/00125
d D 7.3 92/06/05 15:23:29 hibler 3 2
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00132
d D 7.2 90/11/04 19:36:55 mckusick 2 1
c update identifier from Utah
e
s 00133/00000/00000
d D 7.1 90/05/08 22:06:45 mckusick 1 0
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
 * from: Utah $Hdr: itevar.h 1.13 89/02/27$
E 2
I 2
D 3
 * from: Utah $Hdr: itevar.h 1.1 90/07/09$
E 3
I 3
D 4
 * from: Utah $Hdr: itevar.h 1.14 92/01/21$
E 4
I 4
 * from: Utah $Hdr: itevar.h 1.15 92/12/20$
E 4
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

#define UNIT(dev)       minor(dev)

struct itesw {
I 3
	int	ite_hwid;		/* Hardware id */
E 3
	int	(*ite_init)();
	int	(*ite_deinit)();
	int	(*ite_clear)();
	int	(*ite_putc)();
	int	(*ite_cursor)();
	int	(*ite_scroll)();
I 3
	u_char	(*ite_readbyte)();
	int	(*ite_writeglyph)();
E 3
};

I 3
#define getbyte(ip, offset) \
	((*(ip)->isw->ite_readbyte)(ip, offset))

#define getword(ip, offset) \
	((getbyte(ip, offset) << 8) | getbyte(ip, (offset) + 2))

#define writeglyph(ip, offset, fontbuf) \
	((*(ip)->isw->ite_writeglyph)((ip), (offset), (fontbuf)))

E 3
struct ite_softc {
	int	flags;
D 3
	int	type;
E 3
I 3
	struct  itesw *isw;
	struct  grf_softc *grf;
E 3
	caddr_t regbase, fbbase;
	short	curx, cury;
	short   cursorx, cursory;
	short   cblankx, cblanky;
	short	rows, cols;
	short   cpl;
	short	dheight, dwidth;
	short	fbheight, fbwidth;
	short	ftheight, ftwidth;
	short	fontx, fonty;
	short   attribute;
	u_char	*attrbuf;
	short	planemask;
	short	pos;
	char	imode, escape, fpd, hold;
I 3
	caddr_t	devdata;			/* display dependent data */
E 3
};

/* Flags */
#define ITE_ALIVE	0x01	/* hardware exists */
#define ITE_INITED	0x02	/* device has been initialized */
#define ITE_CONSOLE	0x04	/* device can be console */
#define ITE_ISCONS	0x08	/* device is console */
#define ITE_ACTIVE	0x10	/* device is being used as ITE */
#define ITE_INGRF	0x20	/* device in use as non-ITE */
I 4
#define ITE_CURSORON	0x40	/* cursor being tracked */
E 4

D 3
/* Types - indices into itesw */
#define	ITE_TOPCAT	0
#define	ITE_GATORBOX	1
#define	ITE_RENAISSANCE	2
#define ITE_DAVINCI	3

E 3
#define attrloc(ip, y, x) \
	(ip->attrbuf + ((y) * ip->cols) + (x))

#define attrclr(ip, sy, sx, h, w) \
	bzero(ip->attrbuf + ((sy) * ip->cols) + (sx), (h) * (w))
  
#define attrmov(ip, sy, sx, dy, dx, h, w) \
	bcopy(ip->attrbuf + ((sy) * ip->cols) + (sx), \
	      ip->attrbuf + ((dy) * ip->cols) + (dx), \
	      (h) * (w))

#define attrtest(ip, attr) \
	((* (u_char *) attrloc(ip, ip->cury, ip->curx)) & attr)

#define attrset(ip, attr) \
	((* (u_char *) attrloc(ip, ip->cury, ip->curx)) = attr)
  
/*
 * X and Y location of character 'c' in the framebuffer, in pixels.
 */
#define	charX(ip,c)	\
	(((c) % (ip)->cpl) * (ip)->ftwidth + (ip)->fontx)

#define	charY(ip,c)	\
	(((c) / (ip)->cpl) * (ip)->ftheight + (ip)->fonty)

I 3
/*
 * The cursor is just an inverted space.
 */
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
/* Character attributes */
#define ATTR_NOR        0x0             /* normal */
#define	ATTR_INV	0x1		/* inverse */
#define	ATTR_UL		0x2		/* underline */
#define ATTR_ALL	(ATTR_INV | ATTR_UL)

/* Keyboard attributes */
#define ATTR_KPAD	0x4		/* keypad transmit */
  
/* Replacement Rules */
#define RR_CLEAR		0x0
#define RR_COPY			0x3
#define RR_XOR			0x6
#define RR_COPYINVERTED  	0xc

#define SCROLL_UP	0x01
#define SCROLL_DOWN	0x02
#define SCROLL_LEFT	0x03
#define SCROLL_RIGHT	0x04
#define DRAW_CURSOR	0x05
#define ERASE_CURSOR    0x06
#define MOVE_CURSOR	0x07

#define KBD_SSHIFT	4		/* bits to shift status */
#define	KBD_CHARMASK	0x7F

/* keyboard status */
#define	KBD_SMASK	0xF		/* service request status mask */
#define	KBD_CTRLSHIFT	0x8		/* key + CTRL + SHIFT */
#define	KBD_CTRL	0x9		/* key + CTRL */
#define	KBD_SHIFT	0xA		/* key + SHIFT */
#define	KBD_KEY		0xB		/* key only */

#define KBD_CAPSLOCK    0x18

#define KBD_EXT_LEFT_DOWN     0x12
#define KBD_EXT_LEFT_UP       0x92
#define KBD_EXT_RIGHT_DOWN    0x13
#define KBD_EXT_RIGHT_UP      0x93

#define	TABSIZE		8
#define	TABEND(u)	(ite_tty[u].t_winsize.ws_col - TABSIZE)

#ifdef KERNEL
extern	struct ite_softc ite_softc[];
I 3
extern	struct itesw itesw[];
extern	int nitesw;
E 3
#endif
E 1
