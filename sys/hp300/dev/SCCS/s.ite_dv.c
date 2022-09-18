h24159
s 00002/00002/00232
d D 8.1 93/07/08 11:31:25 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00001/00222
d D 7.9 93/07/08 10:54:33 hibler 10 8
c hack to get around bad framebuffer sizes from HW
e
s 00002/00002/00221
d R 8.1 93/06/10 21:33:23 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00222
d D 7.8 92/12/27 09:30:40 hibler 8 7
c cursor ops handled in ite.c
e
s 00012/00012/00213
d D 7.7 92/10/11 09:23:59 bostic 7 6
c make kernel includes standard
e
s 00019/00014/00206
d D 7.6 92/06/05 15:30:53 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00004/00004/00216
d D 7.5 91/05/07 09:53:56 hibler 5 4
c DIO-II support
e
s 00007/00009/00213
d D 7.4 91/05/04 19:49:13 karels 4 3
c update to current include, device calling conventions
e
s 00009/00009/00213
d D 7.3 90/12/16 16:36:26 bostic 3 2
c kernel reorg
e
s 00001/00001/00221
d D 7.2 90/11/04 19:33:57 mckusick 2 1
c update identifier from Utah
e
s 00222/00000/00000
d D 7.1 90/05/08 22:07:01 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: ite_dv.c 1.5 89/04/11$
E 2
I 2
D 5
 * from: Utah $Hdr: ite_dv.c 1.1 90/07/09$
E 5
I 5
D 6
 * from: Utah $Hdr: ite_dv.c 1.7 91/01/21$
E 6
I 6
D 8
 * from: Utah $Hdr: ite_dv.c 1.8 92/01/21$
E 8
I 8
D 10
 * from: Utah $Hdr: ite_dv.c 1.9 92/12/20$
E 10
I 10
 * from: Utah $Hdr: ite_dv.c 1.10 93/06/25$
E 10
E 8
E 6
E 5
E 2
 *
 *	%W% (Berkeley) %G%
 */

#include "ite.h"
#if NITE > 0

D 3
#include "param.h"
#include "conf.h"
#include "user.h"
#include "proc.h"
#include "ioctl.h"
#include "tty.h"
#include "systm.h"
#include "uio.h"
E 3
I 3
D 4
#include "sys/param.h"
#include "sys/conf.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/systm.h"
#include "sys/uio.h"
E 4
I 4
D 7
#include "param.h"
#include "conf.h"
#include "proc.h"
#include "ioctl.h"
#include "tty.h"
#include "systm.h"
E 7
I 7
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/systm.h>
E 7
E 4
E 3

D 6
#include "itevar.h"
#include "itereg.h"
E 6
I 6
D 7
#include "hp/dev/itevar.h"
#include "hp/dev/itereg.h"
E 6
#include "grf_dvreg.h"
E 7
I 7
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
#include <hp300/dev/grf_dvreg.h>
E 7

D 3
#include "machine/cpu.h"
E 3
I 3
D 4
#include "../include/cpu.h"
E 4
I 4
D 7
#include "machine/cpu.h"
E 7
I 7
#include <machine/cpu.h>
E 7
E 4
E 3

/* XXX */
D 6
#include "grfioctl.h"
#include "grfvar.h"
E 6
I 6
D 7
#include "hp/dev/grfioctl.h"
#include "hp/dev/grfvar.h"
E 7
I 7
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
E 7
E 6

#define REGBASE		((struct dvboxfb *)(ip->regbase))
#define WINDOWMOVER	dvbox_windowmove

dvbox_init(ip)
D 6
	struct ite_softc *ip;
E 6
I 6
	register struct ite_softc *ip;
E 6
{
	int i;
	
	/* XXX */
	if (ip->regbase == 0) {
D 5
		struct grfinfo *gi = &grf_softc[ip - ite_softc].g_display;
		ip->regbase = IOV(gi->gd_regaddr);
		ip->fbbase = IOV(gi->gd_fbaddr);
E 5
I 5
D 6
		struct grf_softc *gp = &grf_softc[ip - ite_softc];
E 6
I 6
		struct grf_softc *gp = ip->grf;

E 6
		ip->regbase = gp->g_regkva;
		ip->fbbase = gp->g_fbkva;
I 6
		ip->fbwidth = gp->g_display.gd_fbwidth;
		ip->fbheight = gp->g_display.gd_fbheight;
		ip->dwidth = gp->g_display.gd_dwidth;
		ip->dheight = gp->g_display.gd_dheight;
I 10
		/*
		 * XXX some displays (e.g. the davinci) appear
		 * to return a display height greater than the
		 * returned FB height.  Guess we should go back
		 * to getting the display dimensions from the
		 * fontrom...
		 */
		if (ip->dwidth > ip->fbwidth)
			ip->dwidth = ip->fbwidth;
		if (ip->dheight > ip->fbheight)
			ip->dheight = ip->fbheight;
E 10
E 6
E 5
	}

D 6
	dv_reset(REGADDR);
E 6
I 6
	dv_reset(ip->regbase);
E 6

	/*
	 * Turn on frame buffer, turn on overlay planes, set replacement
	 * rule, enable top overlay plane writes for ite, disable all frame
	 * buffer planes, set byte per pixel, and display frame buffer 0.
	 * Lastly, turn on the box.
	 */
	REGBASE->interrupt = 0x04;
	REGBASE->drive     = 0x10;		
 	REGBASE->rep_rule  = RR_COPY << 4 | RR_COPY;
	REGBASE->opwen     = 0x01;
	REGBASE->fbwen     = 0x0;
	REGBASE->fold      = 0x01;
	REGBASE->vdrive    = 0x0;
	REGBASE->dispen    = 0x01;

	/*
	 * Video enable top overlay plane.
	 */
	REGBASE->opvenp = 0x01;
	REGBASE->opvens = 0x01;

	/*
	 * Make sure that overlay planes override frame buffer planes.
	 */
	REGBASE->ovly0p  = 0x0;
	REGBASE->ovly0s  = 0x0;
	REGBASE->ovly1p  = 0x0;
	REGBASE->ovly1s  = 0x0;
	REGBASE->fv_trig = 0x1;
	DELAY(100);

	/*
	 * Setup the overlay colormaps. Need to set the 0,1 (black/white)
	 * color for both banks.
	 */

	for (i = 0; i <= 1; i++) {
		REGBASE->cmapbank = i;
		REGBASE->rgb[0].red   = 0x00;
		REGBASE->rgb[0].green = 0x00;
		REGBASE->rgb[0].blue  = 0x00;
		REGBASE->rgb[1].red   = 0xFF;
		REGBASE->rgb[1].green = 0xFF;
		REGBASE->rgb[1].blue  = 0xFF;
	}
	REGBASE->cmapbank = 0;
	
D 6
	db_waitbusy(REGADDR);
E 6
I 6
	db_waitbusy(ip->regbase);
E 6

D 6
	ite_devinfo(ip);
E 6
I 6
	ite_fontinfo(ip);
E 6
	ite_fontinit(ip);

	/*
	 * Clear the (visible) framebuffer.
	 */
	dvbox_windowmove(ip, 0, 0, 0, 0, ip->dheight, ip->dwidth, RR_CLEAR);
D 6
	db_waitbusy(REGADDR);
E 6
I 6
	db_waitbusy(ip->regbase);
E 6

	/*
	 * Stash the inverted cursor.
	 */
	dvbox_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			 ip->cblanky, ip->cblankx, ip->ftheight,
			 ip->ftwidth, RR_COPYINVERTED);
}

dvbox_deinit(ip)
D 6
	struct ite_softc *ip;
E 6
I 6
	register struct ite_softc *ip;
E 6
{
	dvbox_windowmove(ip, 0, 0, 0, 0, ip->fbheight, ip->fbwidth, RR_CLEAR);
D 6
	db_waitbusy(REGADDR);
E 6
I 6
	db_waitbusy(ip->regbase);
E 6

   	ip->flags &= ~ITE_INITED;
}

dvbox_putc(ip, c, dy, dx, mode)
	register struct ite_softc *ip;
        register int dy, dx;
	int c, mode;
{
        register int wrr = ((mode == ATTR_INV) ? RR_COPYINVERTED : RR_COPY);
	
	dvbox_windowmove(ip, charY(ip, c), charX(ip, c),
			 dy * ip->ftheight, dx * ip->ftwidth,
			 ip->ftheight, ip->ftwidth, wrr);
}

dvbox_cursor(ip, flag)
	register struct ite_softc *ip;
        register int flag;
{
	if (flag == DRAW_CURSOR)
		draw_cursor(ip)
	else if (flag == MOVE_CURSOR) {
		erase_cursor(ip)
		draw_cursor(ip)
	}
	else
		erase_cursor(ip)
}

dvbox_clear(ip, sy, sx, h, w)
	struct ite_softc *ip;
	register int sy, sx, h, w;
{
	dvbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			 sy * ip->ftheight, sx * ip->ftwidth, 
			 h  * ip->ftheight, w  * ip->ftwidth,
			 RR_CLEAR);
}

dvbox_scroll(ip, sy, sx, count, dir)
        register struct ite_softc *ip;
        register int sy, count;
        int dir, sx;
{
	register int dy;
	register int dx = sx;
	register int height = 1;
	register int width = ip->cols;
D 8

	dvbox_cursor(ip, ERASE_CURSOR);
E 8

	if (dir == SCROLL_UP) {
		dy = sy - count;
		height = ip->rows - sy;
	}
	else if (dir == SCROLL_DOWN) {
		dy = sy + count;
		height = ip->rows - dy - 1;
	}
	else if (dir == SCROLL_RIGHT) {
		dy = sy;
		dx = sx + count;
		width = ip->cols - dx;
	}
	else {
		dy = sy;
		dx = sx - count;
		width = ip->cols - sx;
	}		

	dvbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			 dy * ip->ftheight, dx * ip->ftwidth,
			 height * ip->ftheight,
			 width  * ip->ftwidth, RR_COPY);
}

dvbox_windowmove(ip, sy, sx, dy, dx, h, w, func)
	struct ite_softc *ip;
	int sy, sx, dy, dx, h, w, func;
{
	register struct dvboxfb *dp = REGBASE;
	if (h == 0 || w == 0)
		return;
	
D 6
	db_waitbusy(REGADDR);
E 6
I 6
	db_waitbusy(ip->regbase);
E 6
	dp->rep_rule = func << 4 | func;
	dp->source_y = sy;
	dp->source_x = sx;
	dp->dest_y   = dy;
	dp->dest_x   = dx;
	dp->wheight  = h;
	dp->wwidth   = w;
	dp->wmove    = 1;
}
#endif
E 1
