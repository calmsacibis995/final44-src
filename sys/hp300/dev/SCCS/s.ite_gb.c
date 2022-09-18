h60053
s 00002/00002/00216
d D 8.1 93/06/10 21:33:27 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00217
d D 7.8 92/12/27 09:30:42 hibler 8 7
c cursor ops handled in ite.c
e
s 00012/00012/00208
d D 7.7 92/10/11 09:24:00 bostic 7 6
c make kernel includes standard
e
s 00054/00052/00166
d D 7.6 92/06/05 15:30:54 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00004/00004/00214
d D 7.5 91/05/07 09:54:03 hibler 5 4
c DIO-II support
e
s 00007/00009/00211
d D 7.4 91/05/04 19:49:18 karels 4 3
c update to current include, device calling conventions
e
s 00009/00009/00211
d D 7.3 90/12/16 16:36:29 bostic 3 2
c kernel reorg
e
s 00001/00001/00219
d D 7.2 90/11/04 19:34:27 mckusick 2 1
c update identifier from Utah
e
s 00220/00000/00000
d D 7.1 90/05/08 22:07:02 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: ite_gb.c 1.17 89/04/11$
E 2
I 2
D 5
 * from: Utah $Hdr: ite_gb.c 1.1 90/07/09$
E 5
I 5
D 6
 * from: Utah $Hdr: ite_gb.c 1.18 91/01/21$
E 6
I 6
D 8
 * from: Utah $Hdr: ite_gb.c 1.19 92/01/21$
E 8
I 8
 * from: Utah $Hdr: ite_gb.c 1.20 92/12/20$
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
#include "grf_gbreg.h"
E 7
I 7
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
#include <hp300/dev/grf_gbreg.h>
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

#define REGBASE     	((struct gboxfb *)(ip->regbase))
D 6
#define WINDOWMOVER 	gatorbox_windowmove
E 6
I 6
#define WINDOWMOVER 	gbox_windowmove
E 6

D 6
gatorbox_init(ip)
E 6
I 6
gbox_init(ip)
E 6
	register struct ite_softc *ip;
{
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
E 6
E 5
	}

	REGBASE->write_protect = 0x0;
	REGBASE->interrupt = 0x4;
	REGBASE->rep_rule = RR_COPY;
	REGBASE->blink1 = 0xff;
	REGBASE->blink2 = 0xff;
D 6
	gb_microcode(REGADDR);
E 6
I 6
	gb_microcode(ip->regbase);
E 6
	REGBASE->sec_interrupt = 0x01;

	/*
	 * Set up the color map entries. We use three entries in the
	 * color map. The first, is for black, the second is for
	 * white, and the very last entry is for the inverted cursor.
	 */
	REGBASE->creg_select = 0x00;
	REGBASE->cmap_red    = 0x00;
	REGBASE->cmap_grn    = 0x00;
	REGBASE->cmap_blu    = 0x00;
	REGBASE->cmap_write  = 0x00;
D 6
	gbcm_waitbusy(REGADDR);
E 6
I 6
	gbcm_waitbusy(ip->regbase);
E 6
	
	REGBASE->creg_select = 0x01;
	REGBASE->cmap_red    = 0xFF;
	REGBASE->cmap_grn    = 0xFF;
	REGBASE->cmap_blu    = 0xFF;
	REGBASE->cmap_write  = 0x01;
D 6
	gbcm_waitbusy(REGADDR);
E 6
I 6
	gbcm_waitbusy(ip->regbase);
E 6

	REGBASE->creg_select = 0xFF;
	REGBASE->cmap_red    = 0xFF;
	REGBASE->cmap_grn    = 0xFF;
	REGBASE->cmap_blu    = 0xFF;
	REGBASE->cmap_write  = 0x01;
D 6
	gbcm_waitbusy(REGADDR);
E 6
I 6
	gbcm_waitbusy(ip->regbase);
E 6

D 6
	ite_devinfo(ip);
E 6
I 6
	ite_fontinfo(ip);
E 6
	ite_fontinit(ip);

	/*
	 * Clear the display. This used to be before the font unpacking
	 * but it crashes. Figure it out later.
	 */
D 6
	gatorbox_windowmove(ip, 0, 0, 0, 0, ip->dheight, ip->dwidth, RR_CLEAR);
	tile_mover_waitbusy(REGADDR);
E 6
I 6
	gbox_windowmove(ip, 0, 0, 0, 0, ip->dheight, ip->dwidth, RR_CLEAR);
	tile_mover_waitbusy(ip->regbase);
E 6

	/*
	 * Stash the inverted cursor.
	 */
D 6
	gatorbox_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			    ip->cblanky, ip->cblankx, ip->ftheight,
			    ip->ftwidth, RR_COPYINVERTED);
E 6
I 6
	gbox_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			ip->cblanky, ip->cblankx, ip->ftheight,
			ip->ftwidth, RR_COPYINVERTED);
E 6
}

D 6
gatorbox_deinit(ip)
E 6
I 6
gbox_deinit(ip)
E 6
	struct ite_softc *ip;
{
D 6
	gatorbox_windowmove(ip, 0, 0, 0, 0,
			    ip->dheight, ip->dwidth, RR_CLEAR);
	tile_mover_waitbusy(REGADDR);
E 6
I 6
	gbox_windowmove(ip, 0, 0, 0, 0, ip->dheight, ip->dwidth, RR_CLEAR);
	tile_mover_waitbusy(ip->regbase);
E 6

   	ip->flags &= ~ITE_INITED;
}

D 6
gatorbox_putc(ip, c, dy, dx, mode)
E 6
I 6
gbox_putc(ip, c, dy, dx, mode)
E 6
	register struct ite_softc *ip;
        register int dy, dx;
	int c, mode;
{
        register int wrr = ((mode == ATTR_INV) ? RR_COPYINVERTED : RR_COPY);

D 6
	gatorbox_windowmove(ip, charY(ip, c), charX(ip, c),
E 6
I 6
	gbox_windowmove(ip, charY(ip, c), charX(ip, c),
E 6
			    dy * ip->ftheight, dx * ip->ftwidth,
			    ip->ftheight, ip->ftwidth, wrr);
}

D 6
gatorbox_cursor(ip, flag)
E 6
I 6
gbox_cursor(ip, flag)
E 6
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

D 6
gatorbox_clear(ip, sy, sx, h, w)
E 6
I 6
gbox_clear(ip, sy, sx, h, w)
E 6
	struct ite_softc *ip;
	register int sy, sx, h, w;
{
D 6
	gatorbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			    sy * ip->ftheight, sx * ip->ftwidth, 
			    h  * ip->ftheight, w  * ip->ftwidth,
			    RR_CLEAR);
E 6
I 6
	gbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			sy * ip->ftheight, sx * ip->ftwidth, 
			h  * ip->ftheight, w  * ip->ftwidth,
			RR_CLEAR);
E 6
}
D 6
#define	gatorbox_blockmove(ip, sy, sx, dy, dx, h, w) \
	gatorbox_windowmove((ip), \
			    (sy) * ip->ftheight, \
			    (sx) * ip->ftwidth, \
			    (dy) * ip->ftheight, \
			    (dx) * ip->ftwidth, \
			    (h)  * ip->ftheight, \
			    (w)  * ip->ftwidth, \
			    RR_COPY)
E 6
I 6
#define	gbox_blockmove(ip, sy, sx, dy, dx, h, w) \
	gbox_windowmove((ip), \
			(sy) * ip->ftheight, \
			(sx) * ip->ftwidth, \
			(dy) * ip->ftheight, \
			(dx) * ip->ftwidth, \
			(h)  * ip->ftheight, \
			(w)  * ip->ftwidth, \
			RR_COPY)
E 6

D 6
gatorbox_scroll(ip, sy, sx, count, dir)
E 6
I 6
gbox_scroll(ip, sy, sx, count, dir)
E 6
        register struct ite_softc *ip;
        register int sy;
        int dir, sx, count;
{
	register int height, dy, i;
	
D 6
	tile_mover_waitbusy(REGADDR);
E 6
I 6
	tile_mover_waitbusy(ip->regbase);
E 6
	REGBASE->write_protect = 0x0;
	
D 6
	gatorbox_cursor(ip, ERASE_CURSOR);
E 6
I 6
D 8
	gbox_cursor(ip, ERASE_CURSOR);
E 6

E 8
	if (dir == SCROLL_UP) {
		dy = sy - count;
		height = ip->rows - sy;
		for (i = 0; i < height; i++)
D 6
			gatorbox_blockmove(ip, sy + i, sx, dy + i, 0,
					   1, ip->cols);
E 6
I 6
			gbox_blockmove(ip, sy + i, sx, dy + i, 0, 1, ip->cols);
E 6
	}
	else if (dir == SCROLL_DOWN) {
		dy = sy + count;
		height = ip->rows - dy;
		for (i = (height - 1); i >= 0; i--)
D 6
			gatorbox_blockmove(ip, sy + i, sx, dy + i, 0,
					   1, ip->cols);
E 6
I 6
			gbox_blockmove(ip, sy + i, sx, dy + i, 0, 1, ip->cols);
E 6
	}
	else if (dir == SCROLL_RIGHT) {
D 6
		gatorbox_blockmove(ip, sy, sx, sy, sx + count,
				   1, ip->cols - (sx + count));
E 6
I 6
		gbox_blockmove(ip, sy, sx, sy, sx + count,
			       1, ip->cols - (sx + count));
E 6
	}
	else {
D 6
		gatorbox_blockmove(ip, sy, sx, sy, sx - count,
				   1, ip->cols - sx);
E 6
I 6
		gbox_blockmove(ip, sy, sx, sy, sx - count,
			       1, ip->cols - sx);
E 6
	}		
}

D 6
gatorbox_windowmove(ip, sy, sx, dy, dx, h, w, mask)
E 6
I 6
gbox_windowmove(ip, sy, sx, dy, dx, h, w, mask)
E 6
     register struct ite_softc *ip;
     int sy, sx, dy, dx, mask;
     register int h, w;
{
	register int src, dest;

	src  = (sy * 1024) + sx;	/* upper left corner in pixels */
	dest = (dy * 1024) + dx;

D 6
	tile_mover_waitbusy(REGADDR);
E 6
I 6
	tile_mover_waitbusy(ip->regbase);
E 6
	REGBASE->width = -(w / 4);
	REGBASE->height = -(h / 4);
	if (src < dest)
		REGBASE->rep_rule = MOVE_DOWN_RIGHT|mask;
	else {
		REGBASE->rep_rule = MOVE_UP_LEFT|mask;
		/*
		 * Adjust to top of lower right tile of the block.
		 */
		src = src + ((h - 4) * 1024) + (w - 4);
		dest= dest + ((h - 4) * 1024) + (w - 4);
	}
	FBBASE[dest] = FBBASE[src];
}
#endif
E 1
