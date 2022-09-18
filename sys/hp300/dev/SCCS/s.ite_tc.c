h23818
s 00002/00002/00240
d D 8.1 93/06/10 21:33:38 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00241
d D 7.7 92/12/27 09:30:45 hibler 8 7
c cursor ops handled in ite.c
e
s 00013/00013/00231
d D 7.6 92/10/11 09:24:03 bostic 7 6
c make kernel includes standard
e
s 00023/00017/00221
d D 7.5 92/06/05 15:30:56 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00019/00004/00219
d D 7.4 91/05/07 09:51:27 hibler 5 4
c DIO-II support, additional init for catseye
e
s 00007/00009/00216
d D 7.3 91/05/04 19:49:20 karels 4 3
c update to current include, device calling conventions
e
s 00009/00009/00216
d D 7.2 90/12/16 16:36:41 bostic 3 1
c kernel reorg
e
s 00000/00000/00225
d R 7.2 90/12/05 18:26:35 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00225/00000/00000
d D 7.1 90/05/08 22:07:04 mckusick 1 0
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
D 5
 * from: Utah $Hdr: ite_tc.c 1.22 89/04/11$
E 5
I 5
D 6
 * from: Utah $Hdr: ite_tc.c 1.25 91/03/25$
E 6
I 6
D 8
 * from: Utah $Hdr: ite_tc.c 1.26 92/01/21$
E 8
I 8
 * from: Utah $Hdr: ite_tc.c 1.27 92/12/20$
E 8
E 6
E 5
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

D 7
#include "grf_tcreg.h"
D 6
#include "itereg.h"
#include "itevar.h"
E 6
I 6
#include "hp/dev/grfreg.h"
#include "hp/dev/itereg.h"
#include "hp/dev/itevar.h"
E 7
I 7
#include <hp300/dev/grf_tcreg.h>
#include <hp/dev/grfreg.h>
#include <hp/dev/itereg.h>
#include <hp/dev/itevar.h>
E 7
E 6

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

I 6
/* XXX */
D 7
#include "hp/dev/grfioctl.h"
#include "hp/dev/grfvar.h"
E 7
I 7
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
E 7

E 6
#define REGBASE	    	((struct tcboxfb *)(ip->regbase))
#define WINDOWMOVER 	topcat_windowmove

D 6
/* XXX */
#include "grfioctl.h"
#include "grfvar.h"

E 6
topcat_init(ip)
	register struct ite_softc *ip;
{
	/* XXX */
	if (ip->regbase == NULL) {
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
	}

	/*
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
E 5
	}

	/*
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

D 6
	ite_devinfo(ip);
E 6
I 6
	ite_fontinfo(ip);
E 6

	/*
	 * Clear the framebuffer on all planes.
	 */
	topcat_windowmove(ip, 0, 0, 0, 0, ip->fbheight, ip->fbwidth, RR_CLEAR);
D 6
	tc_waitbusy(REGADDR, ip->planemask);
E 6
I 6
	tc_waitbusy(ip->regbase, ip->planemask);
E 6

	ite_fontinit(ip);

	/*
	 * Initialize color map for color displays
	 */
	if (ip->planemask != 1) {
D 6
	  	tc_waitbusy(REGADDR, ip->planemask);
E 6
I 6
	  	tc_waitbusy(ip->regbase, ip->planemask);
E 6
		REGBASE->nblank = 0x01;

D 6
		tccm_waitbusy(REGADDR);
E 6
I 6
		tccm_waitbusy(ip->regbase);
E 6
		REGBASE->rdata  = 0x0;
		REGBASE->gdata  = 0x0;
		REGBASE->bdata  = 0x0;
		REGBASE->cindex = 0xFF;
		REGBASE->strobe = 0xFF;

		DELAY(100);
D 6
		tccm_waitbusy(REGADDR);
E 6
I 6
		tccm_waitbusy(ip->regbase);
E 6
		REGBASE->rdata  = 0x0;
		REGBASE->gdata  = 0x0;
		REGBASE->bdata  = 0x0;
		REGBASE->cindex = 0x0;

		DELAY(100);
D 6
		tccm_waitbusy(REGADDR);
E 6
I 6
		tccm_waitbusy(ip->regbase);
E 6
		REGBASE->rdata  = 0xFF;
		REGBASE->gdata  = 0xFF;
		REGBASE->bdata  = 0xFF;
		REGBASE->cindex = 0xFE;
		REGBASE->strobe = 0xFF;

		DELAY(100);
D 6
		tccm_waitbusy(REGADDR);
E 6
I 6
		tccm_waitbusy(ip->regbase);
E 6
		REGBASE->rdata  = 0x0;
		REGBASE->gdata  = 0x0;
		REGBASE->bdata  = 0x0;
		REGBASE->cindex = 0x0;
	}

	/*
	 * Stash the inverted cursor.
	 */
	topcat_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			  ip->cblanky, ip->cblankx, ip->ftheight,
			  ip->ftwidth, RR_COPYINVERTED);
}

topcat_deinit(ip)
	register struct ite_softc *ip;
{
	topcat_windowmove(ip, 0, 0, 0, 0, ip->fbheight, ip->fbwidth, RR_CLEAR);
D 6
	tc_waitbusy(REGADDR, ip->planemask);
E 6
I 6
	tc_waitbusy(ip->regbase, ip->planemask);
E 6

	REGBASE->nblank = ~0;
   	ip->flags &= ~ITE_INITED;
}

topcat_putc(ip, c, dy, dx, mode)
	register struct ite_softc *ip;
	int c, dy, dx, mode;
{
        int wmrr = ((mode == ATTR_INV) ? RR_COPYINVERTED : RR_COPY);
	
	topcat_windowmove(ip, charY(ip, c), charX(ip, c),
			  dy * ip->ftheight, dx * ip->ftwidth,
			  ip->ftheight, ip->ftwidth, wmrr);
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
	register struct ite_softc *ip;
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
	register int dy;
	register int dx = sx;
	register int height = 1;
	register int width = ip->cols;
D 8

	topcat_cursor(ip, ERASE_CURSOR);
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

	topcat_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			  dy * ip->ftheight, dx * ip->ftwidth,
			  height * ip->ftheight,
			  width  * ip->ftwidth, RR_COPY);
}

topcat_windowmove(ip, sy, sx, dy, dx, h, w, func)
	struct ite_softc *ip;
	int sy, sx, dy, dx, h, w, func;
{
  	register struct tcboxfb *rp = REGBASE;
	
	if (h == 0 || w == 0)
		return;
D 6
	tc_waitbusy(REGADDR, ip->planemask);
E 6
I 6
	tc_waitbusy(ip->regbase, ip->planemask);
E 6
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
