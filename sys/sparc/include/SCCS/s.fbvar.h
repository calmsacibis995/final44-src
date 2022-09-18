h16257
s 00002/00002/00082
d D 8.1 93/06/11 15:11:55 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00082
d D 7.3 93/04/20 18:48:50 torek 3 2
c spelling
e
s 00005/00000/00079
d D 7.2 92/07/21 16:41:28 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00079/00000/00000
d D 7.1 92/07/13 00:43:00 torek 1 0
c date and time created 92/07/13 00:43:00 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: fbvar.h,v 1.14 92/06/17 06:10:16 torek Exp $
E 3
I 3
 * from: $Header: fbvar.h,v 1.15 92/11/26 02:04:34 torek Exp $
E 3
 */

/*
 * Frame buffer variables.  All frame buffer drivers must provide the
 * following in order to participate.
 */
struct fbdriver {
	/* device unblank function (force kernel output to display) */
	void	(*fbd_unblank)(struct device *);
#ifdef notyet
	void	(*fbd_wrrop)();		/* `write region' rasterop */
	void	(*fbd_cprop)();		/* `copy region' rasterop */
	void	(*fbd_clrop)();		/* `clear region' rasterop */
#endif
};

struct fbdevice {
	int	fb_major;		/* XXX */
	struct	fbtype fb_type;		/* what it says */
	caddr_t	fb_pixels;		/* display RAM */
	int	fb_linebytes;		/* bytes per display line */

	struct	fbdriver *fb_driver;	/* pointer to driver */
	struct	device *fb_device;	/* parameter for fbd_unblank */

	/* Raster console emulator state */
	u_int	fb_bits;		/* see defines below */
	int	fb_ringing;		/* bell currently ringing */
	int	fb_belldepth;		/* audible bell depth */
	int	fb_scroll;		/* stupid sun scroll mode */

	int	fb_p0;			/* escape sequence parameter 0 */
	int	fb_p1;			/* escape sequence parameter 1 */

	int	*fb_row;		/* emulator row */
	int	*fb_col;		/* emulator column */

	int	fb_maxrow;		/* emulator height of screen */
	int	fb_maxcol;		/* emulator width of screen */

	int	fb_emuwidth;		/* emulator screen width  */
	int	fb_emuheight;		/* emulator screen height */

	int	fb_xorigin;		/* x origin for first column */
	int	fb_yorigin;		/* y origin for first row */

	struct	raster *fb_sp;		/* frame buffer raster */
	struct	raster *fb_cursor;	/* optional cursor */
	int	fb_ras_blank;		/* current screen blank raster op */

	struct	raster_font *fb_font;	/* font and related info */
	int	fb_font_ascent;		/* distance from font to char origin */
};

#define FB_INESC	0x001		/* processing an escape sequence */
#define FB_STANDOUT	0x002		/* standout mode */
/* #define FB_BOLD	0x?		/* boldface mode */
#define FB_INVERT	0x008		/* white on black mode */
#define FB_VISBELL	0x010		/* visual bell */
#define FB_CURSOR	0x020		/* cursor is visible */
#define FB_P0_DEFAULT	0x100		/* param 0 is defaulted */
#define FB_P1_DEFAULT	0x200		/* param 1 is defaulted */
#define FB_P0		0x400		/* working on param 0 */
#define FB_P1		0x800		/* working on param 1 */

void	fbattach __P((struct fbdevice *));
E 1
