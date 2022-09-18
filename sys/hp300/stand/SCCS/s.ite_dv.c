h54538
s 00002/00002/00224
d D 8.1 93/06/10 21:47:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00221
d D 7.4 92/10/11 10:01:41 bostic 4 3
c make kernel includes standard
e
s 00009/00010/00217
d D 7.3 92/06/18 21:33:25 hibler 3 2
c merge with latest Utah version
e
s 00005/00005/00222
d D 7.2 90/12/16 16:39:26 bostic 2 1
c kernel reorg
e
s 00227/00000/00000
d D 7.1 90/05/08 22:46:06 mckusick 1 0
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
D 3
 * from: Utah $Hdr: ite_dv.c 1.1 89/02/28$
E 3
I 3
 * from: Utah $Hdr: ite_dv.c 1.2 92/01/20$
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 4
#include "samachdep.h"
E 4
I 4
#include <hp300/stand/samachdep.h>
E 4

#ifdef ITECONSOLE

D 2
#include "param.h"
#include "../hpdev/itevar.h"
#include "../hpdev/itereg.h"
#include "../hpdev/grfvar.h"
#include "../hpdev/grf_dvreg.h"
E 2
I 2
D 4
#include "sys/param.h"
D 3
#include "../dev/itevar.h"
#include "../dev/itereg.h"
#include "../dev/grfvar.h"
E 3
I 3
#include "hp/dev/itevar.h"
#include "hp/dev/itereg.h"
E 3
#include "../dev/grf_dvreg.h"
E 4
I 4
#include <sys/param.h>
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
#include <hp300/dev/grf_dvreg.h>
E 4
E 2

#define REGBASE		((struct dvboxfb *)(ip->regbase))
#define WINDOWMOVER	dvbox_windowmove

dvbox_init(ip)
	struct ite_softc *ip;
{
	int i;
	
D 3
	dv_reset(REGADDR);
E 3
I 3
	dv_reset(ip->regbase);
E 3
	DELAY(4000);

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
	DELAY(400);

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
	
D 3
	db_waitbusy(REGADDR);
E 3
I 3
	db_waitbusy(ip->regbase);
E 3

D 3
	ite_devinfo(ip);
E 3
I 3
	ite_fontinfo(ip);
E 3
	ite_fontinit(ip);

	/*
	 * Clear the (visible) framebuffer.
	 */
	dvbox_windowmove(ip, 0, 0, 0, 0, ip->dheight, ip->dwidth, RR_CLEAR);
D 3
	db_waitbusy(REGADDR);
E 3
I 3
	db_waitbusy(ip->regbase);
E 3

	/*
	 * Stash the inverted cursor.
	 */
	dvbox_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			 ip->cblanky, ip->cblankx, ip->ftheight,
			 ip->ftwidth, RR_COPYINVERTED);
D 3
	db_waitbusy(REGADDR);
E 3
I 3
	db_waitbusy(ip->regbase);
E 3
}

dvbox_putc(ip, c, dy, dx, mode)
	register struct ite_softc *ip;
        register int dy, dx;
	int c, mode;
{
	dvbox_windowmove(ip, charY(ip, c), charX(ip, c),
			 dy * ip->ftheight, dx * ip->ftwidth,
			 ip->ftheight, ip->ftwidth, RR_COPY);
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
	register int dy = sy - count;
	register int height = ip->rows - sy;

	dvbox_cursor(ip, ERASE_CURSOR);

	dvbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			 dy * ip->ftheight, sx * ip->ftwidth,
			 height * ip->ftheight,
			 ip->cols * ip->ftwidth, RR_COPY);
}

dvbox_windowmove(ip, sy, sx, dy, dx, h, w, func)
	struct ite_softc *ip;
	int sy, sx, dy, dx, h, w, func;
{
	register struct dvboxfb *dp = REGBASE;
	if (h == 0 || w == 0)
		return;
	
D 3
	db_waitbusy(REGADDR);
E 3
I 3
	db_waitbusy(ip->regbase);
E 3
	dp->rep_rule = func << 4 | func;
	dp->source_y = sy;
	dp->source_x = sx;
	dp->dest_y   = dy;
	dp->dest_x   = dx;
	dp->wheight  = h;
	dp->wwidth   = w;
	dp->wmove    = 1;
}

dv_reset(dbp)
	register struct dvboxfb *dbp;
{
  	dbp->reset = 0x80;
	DELAY(400);

	dbp->interrupt = 0x04;
	dbp->en_scan   = 0x01;
	dbp->fbwen     = ~0;
	dbp->opwen     = ~0;
	dbp->fold      = 0x01;
	dbp->drive     = 0x01;
	dbp->rep_rule  = 0x33;
	dbp->alt_rr    = 0x33;
	dbp->zrr       = 0x33;

	dbp->fbvenp    = 0xFF;
	dbp->dispen    = 0x01;
	dbp->fbvens    = 0x0;
	dbp->fv_trig   = 0x01;
	DELAY(400);
	dbp->vdrive    = 0x0;
	dbp->zconfig   = 0x0;

	while (dbp->wbusy & 0x01)
	  DELAY(400);

	/*
	 * Start of missing ROM code.
	 */
	dbp->cmapbank = 0;

	dbp->red0   = 0;
	dbp->red1   = 0;
	dbp->green0 = 0;
	dbp->green1 = 0;
	dbp->blue0  = 0;
	dbp->blue1  = 0;

	dbp->panxh   = 0;
	dbp->panxl   = 0;
	dbp->panyh   = 0;
	dbp->panyl   = 0;
	dbp->zoom    = 0;
	dbp->cdwidth = 0x50;
	dbp->chstart = 0x52;
	dbp->cvwidth = 0x22;
	dbp->pz_trig = 1;
	/*
	 * End of missing ROM code.
	 */
}

#endif
E 1
