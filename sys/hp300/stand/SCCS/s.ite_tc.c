h32801
s 00002/00002/00151
d D 8.1 93/06/10 21:47:17 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00147
d D 7.4 92/10/11 10:01:45 bostic 4 3
c make kernel includes standard
e
s 00022/00007/00131
d D 7.3 92/06/18 21:33:28 hibler 3 2
c merge with latest Utah version
e
s 00005/00005/00133
d D 7.2 90/12/16 16:39:33 bostic 2 1
c kernel reorg
e
s 00138/00000/00000
d D 7.1 90/05/08 22:46:08 mckusick 1 0
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
 * from: Utah $Hdr: ite_tc.c 1.9 89/02/20$
E 3
I 3
 * from: Utah $Hdr: ite_tc.c 1.11 92/01/20$
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
#include "../hpdev/grf_tcreg.h"
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
#include "hp/dev/grfreg.h"
E 3
#include "../dev/grf_tcreg.h"
E 4
I 4
#include <sys/param.h>
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
#include <hp/dev/grfreg.h>
#include <hp300/dev/grf_tcreg.h>
E 4
E 2

#define REGBASE	    	((struct tcboxfb *)(ip->regbase))
#define WINDOWMOVER 	topcat_windowmove

topcat_init(ip)
	register struct ite_softc *ip;
{

	/*
I 3
	 * Catseye looks a lot like a topcat, but not completely.
	 * So, we set some bits to make it work.
	 */
	if (REGBASE->fbid != GID_TOPCAT) {
		while ((REGBASE->catseye_status & 1))
			;
		REGBASE->catseye_status = 0x0;
		REGBASE->vb_select      = 0x0;
		REGBASE->tcntrl         = 0x0;
		REGBASE->acntrl         = 0x0;
		REGBASE->pncntrl        = 0x0;
		REGBASE->rug_cmdstat    = 0x90;
	}

	/*
E 3
	 * Determine the number of planes by writing to the first frame
	 * buffer display location, then reading it back. 
	 */
	REGBASE->wen = ~0;
	REGBASE->fben = ~0;
	REGBASE->prr = RR_COPY;
	*FBBASE = 0xFF;
	ip->planemask = *FBBASE;

	/*
	 * Enable reading/writing of all the planes.
	 */
	REGBASE->fben = ip->planemask;
	REGBASE->wen  = ip->planemask;
	REGBASE->ren  = ip->planemask;
	REGBASE->prr  = RR_COPY;

D 3
	ite_devinfo(ip);
E 3
I 3
	ite_fontinfo(ip);
E 3

	/*
	 * Clear the framebuffer on all planes.
	 */
	topcat_windowmove(ip, 0, 0, 0, 0, ip->fbheight, ip->fbwidth, RR_CLEAR);
D 3
	tc_waitbusy(REGADDR, ip->planemask);
E 3
I 3
	tc_waitbusy(ip->regbase, ip->planemask);
E 3

	ite_fontinit(ip);

	/*
	 * Stash the inverted cursor.
	 */
	topcat_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			  ip->cblanky, ip->cblankx, ip->ftheight,
			  ip->ftwidth, RR_COPYINVERTED);
}

topcat_putc(ip, c, dy, dx, mode)
	register struct ite_softc *ip;
        register int dy, dx;
	int c, mode;
{
	topcat_windowmove(ip, charY(ip, c), charX(ip, c),
			  dy * ip->ftheight, dx * ip->ftwidth,
			  ip->ftheight, ip->ftwidth, RR_COPY);
}

topcat_cursor(ip, flag)
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

topcat_clear(ip, sy, sx, h, w)
	struct ite_softc *ip;
	register int sy, sx, h, w;
{
	topcat_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			  sy * ip->ftheight, sx * ip->ftwidth, 
			  h  * ip->ftheight, w  * ip->ftwidth,
			  RR_CLEAR);
}

topcat_scroll(ip, sy, sx, count, dir)
        register struct ite_softc *ip;
        register int sy, count;
        int dir, sx;
{
	register int dy = sy - count;
	register int height = ip->rows - sy;

	topcat_cursor(ip, ERASE_CURSOR);

	topcat_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			  dy * ip->ftheight, sx * ip->ftwidth,
			  height * ip->ftheight,
			  ip->cols  * ip->ftwidth, RR_COPY);
}

topcat_windowmove(ip, sy, sx, dy, dx, h, w, func)
	struct ite_softc *ip;
	int sy, sx, dy, dx, h, w, func;
{
  	register struct tcboxfb *rp = REGBASE;
	
	if (h == 0 || w == 0)
		return;
D 3
	tc_waitbusy(REGADDR, ip->planemask);
E 3
I 3
	tc_waitbusy(ip->regbase, ip->planemask);
E 3
	rp->wmrr     = func;
	rp->source_y = sy;
	rp->source_x = sx;
	rp->dest_y   = dy;
	rp->dest_x   = dx;
	rp->wheight  = h;
	rp->wwidth   = w;
	rp->wmove    = ip->planemask;
}
#endif
E 1
