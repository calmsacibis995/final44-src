h48162
s 00002/00002/00169
d D 8.1 93/06/10 21:47:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00166
d D 7.4 92/10/11 10:01:42 bostic 4 3
c make kernel includes standard
e
s 00039/00040/00132
d D 7.3 92/06/18 21:33:26 hibler 3 2
c merge with latest Utah version
e
s 00005/00005/00167
d D 7.2 90/12/16 16:39:28 bostic 2 1
c kernel reorg
e
s 00172/00000/00000
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
 * from: Utah $Hdr: ite_gb.c 1.8 89/02/23$
E 3
I 3
 * from: Utah $Hdr: ite_gb.c 1.9 92/01/20$
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
E 2
I 2
D 4
#include "sys/param.h"
E 4
I 4
#include <sys/param.h>
E 4
E 2

D 2
#include "../hpdev/itevar.h"
#include "../hpdev/itereg.h"
#include "../hpdev/grfvar.h"
#include "../hpdev/grf_gbreg.h"
E 2
I 2
D 3
#include "../dev/itevar.h"
#include "../dev/itereg.h"
#include "../dev/grfvar.h"
E 3
I 3
D 4
#include "hp/dev/itevar.h"
#include "hp/dev/itereg.h"
E 3
#include "../dev/grf_gbreg.h"
E 4
I 4
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
#include <hp300/dev/grf_gbreg.h>
E 4
E 2

#define REGBASE     	((struct gboxfb *)(ip->regbase))
D 3
#define WINDOWMOVER 	gatorbox_windowmove
E 3
I 3
#define WINDOWMOVER 	gbox_windowmove
E 3

D 3
gatorbox_init(ip)
E 3
I 3
gbox_init(ip)
E 3
	register struct ite_softc *ip;
{
	REGBASE->write_protect = 0x0;
	REGBASE->interrupt = 0x4;
	REGBASE->rep_rule = RR_COPY;
	REGBASE->blink1 = 0xff;
	REGBASE->blink2 = 0xff;
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
D 3
	gbcm_waitbusy(REGADDR);
E 3
I 3
	gbcm_waitbusy(ip->regbase);
E 3
	
	REGBASE->creg_select = 0x01;
	REGBASE->cmap_red    = 0xFF;
	REGBASE->cmap_grn    = 0xFF;
	REGBASE->cmap_blu    = 0xFF;
	REGBASE->cmap_write  = 0x01;
D 3
	gbcm_waitbusy(REGADDR);
E 3
I 3
	gbcm_waitbusy(ip->regbase);
E 3

	REGBASE->creg_select = 0xFF;
	REGBASE->cmap_red    = 0xFF;
	REGBASE->cmap_grn    = 0xFF;
	REGBASE->cmap_blu    = 0xFF;
	REGBASE->cmap_write  = 0x01;
D 3
	gbcm_waitbusy(REGADDR);
E 3
I 3
	gbcm_waitbusy(ip->regbase);
E 3

D 3
	ite_devinfo(ip);
E 3
I 3
	ite_fontinfo(ip);
E 3
	ite_fontinit(ip);

	/*
	 * Clear the display. This used to be before the font unpacking
	 * but it crashes. Figure it out later.
	 */
D 3
	gatorbox_windowmove(ip, 0, 0, 0, 0, ip->dheight, ip->dwidth, RR_CLEAR);
	tile_mover_waitbusy(REGADDR);
E 3
I 3
	gbox_windowmove(ip, 0, 0, 0, 0, ip->dheight, ip->dwidth, RR_CLEAR);
	tile_mover_waitbusy(ip->regbase);
E 3

	/*
	 * Stash the inverted cursor.
	 */
D 3
	gatorbox_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			    ip->cblanky, ip->cblankx, ip->ftheight,
			    ip->ftwidth, RR_COPYINVERTED);
E 3
I 3
	gbox_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			ip->cblanky, ip->cblankx, ip->ftheight,
			ip->ftwidth, RR_COPYINVERTED);
E 3
}

D 3
gatorbox_putc(ip, c, dy, dx, mode)
E 3
I 3
gbox_putc(ip, c, dy, dx, mode)
E 3
	register struct ite_softc *ip;
        register int dy, dx;
	int c, mode;
{
D 3
	gatorbox_windowmove(ip, charY(ip, c), charX(ip, c),
			    dy * ip->ftheight, dx * ip->ftwidth,
			    ip->ftheight, ip->ftwidth, RR_COPY);
E 3
I 3
	gbox_windowmove(ip, charY(ip, c), charX(ip, c),
			dy * ip->ftheight, dx * ip->ftwidth,
			ip->ftheight, ip->ftwidth, RR_COPY);
E 3
}

D 3
gatorbox_cursor(ip, flag)
E 3
I 3
gbox_cursor(ip, flag)
E 3
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

D 3
gatorbox_clear(ip, sy, sx, h, w)
E 3
I 3
gbox_clear(ip, sy, sx, h, w)
E 3
	struct ite_softc *ip;
	register int sy, sx, h, w;
{
D 3
	gatorbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			    sy * ip->ftheight, sx * ip->ftwidth, 
			    h  * ip->ftheight, w  * ip->ftwidth,
			    RR_CLEAR);
E 3
I 3
	gbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			sy * ip->ftheight, sx * ip->ftwidth, 
			h  * ip->ftheight, w  * ip->ftwidth,
			RR_CLEAR);
E 3
}

D 3
#define	gatorbox_blockmove(ip, sy, sx, dy, dx, h, w) \
	gatorbox_windowmove((ip), \
			    (sy) * ip->ftheight, \
			    (sx) * ip->ftwidth, \
			    (dy) * ip->ftheight, \
			    (dx) * ip->ftwidth, \
			    (h)  * ip->ftheight, \
			    (w)  * ip->ftwidth, \
			    RR_COPY)
E 3
I 3
#define	gbox_blockmove(ip, sy, sx, dy, dx, h, w) \
	gbox_windowmove((ip), \
			(sy) * ip->ftheight, \
			(sx) * ip->ftwidth, \
			(dy) * ip->ftheight, \
			(dx) * ip->ftwidth, \
			(h)  * ip->ftheight, \
			(w)  * ip->ftwidth, \
			RR_COPY)
E 3

D 3
gatorbox_scroll(ip, sy, sx, count, dir)
E 3
I 3
gbox_scroll(ip, sy, sx, count, dir)
E 3
        register struct ite_softc *ip;
        register int sy;
        int dir, sx, count;
{
	register int height, dy, i;
	
D 3
	tile_mover_waitbusy(REGADDR);
E 3
I 3
	tile_mover_waitbusy(ip->regbase);
E 3
	REGBASE->write_protect = 0x0;

D 3
	gatorbox_cursor(ip, ERASE_CURSOR);
E 3
I 3
	gbox_cursor(ip, ERASE_CURSOR);
E 3

	dy = sy - count;
	height = ip->rows - sy;
	for (i = 0; i < height; i++)
D 3
		gatorbox_blockmove(ip, sy + i, sx, dy + i, 0, 1, ip->cols);
E 3
I 3
		gbox_blockmove(ip, sy + i, sx, dy + i, 0, 1, ip->cols);
E 3
}

D 3
gatorbox_windowmove(ip, sy, sx, dy, dx, h, w, mask)
E 3
I 3
gbox_windowmove(ip, sy, sx, dy, dx, h, w, mask)
E 3
     register struct ite_softc *ip;
     int sy, sx, dy, dx, mask;
     register int h, w;
{
	register int src, dest;

	src  = (sy * 1024) + sx;	/* upper left corner in pixels */
	dest = (dy * 1024) + dx;

D 3
	tile_mover_waitbusy(REGADDR);
E 3
I 3
	tile_mover_waitbusy(ip->regbase);
E 3
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
