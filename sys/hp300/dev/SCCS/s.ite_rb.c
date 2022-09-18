h25223
s 00002/00002/00231
d D 8.1 93/07/08 11:31:16 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00001/00221
d D 7.9 93/07/08 10:54:44 hibler 10 8
c hack to get around bad framebuffer sizes from HW
e
s 00002/00002/00220
d R 8.1 93/06/10 21:33:35 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00221
d D 7.8 92/12/27 09:30:44 hibler 8 7
c cursor ops handled in ite.c
e
s 00012/00012/00212
d D 7.7 92/10/11 09:24:02 bostic 7 6
c make kernel includes standard
e
s 00024/00019/00200
d D 7.6 92/06/05 15:30:55 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00004/00004/00215
d D 7.5 91/05/07 09:54:08 hibler 5 4
c DIO-II support
e
s 00007/00009/00212
d D 7.4 91/05/04 19:49:19 karels 4 3
c update to current include, device calling conventions
e
s 00009/00009/00212
d D 7.3 90/12/16 16:36:33 bostic 3 2
c kernel reorg
e
s 00001/00001/00220
d D 7.2 90/11/04 19:34:54 mckusick 2 1
c update identifier from Utah
e
s 00221/00000/00000
d D 7.1 90/05/08 22:07:03 mckusick 1 0
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
 * from: Utah $Hdr: ite_rb.c 1.15 89/04/11$
E 2
I 2
D 5
 * from: Utah $Hdr: ite_rb.c 1.1 90/07/09$
E 5
I 5
D 6
 * from: Utah $Hdr: ite_rb.c 1.16 91/01/21$
E 6
I 6
D 8
 * from: Utah $Hdr: ite_rb.c 1.17 92/01/21$
E 8
I 8
D 10
 * from: Utah $Hdr: ite_rb.c 1.18 92/12/20$
E 10
I 10
 * from: Utah $Hdr: ite_rb.c 1.19 93/06/25$
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
#include "grf_rbreg.h"
E 7
I 7
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
#include <hp300/dev/grf_rbreg.h>
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

#define REGBASE		((struct rboxfb *)(ip->regbase))
#define WINDOWMOVER	rbox_windowmove

rbox_init(ip)
	struct ite_softc *ip;
{
	register int i;

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
	rb_waitbusy(REGADDR);
E 6
I 6
	rb_waitbusy(ip->regbase);
E 6

	REGBASE->reset = 0x39;
	DELAY(1000);

	REGBASE->interrupt = 0x04;
	REGBASE->display_enable = 0x01;
	REGBASE->video_enable = 0x01;
	REGBASE->drive = 0x01;
	REGBASE->vdrive = 0x0;

D 6
	ite_devinfo(ip);
E 6
I 6
	ite_fontinfo(ip);
E 6
	
	REGBASE->opwen = 0xFF;

	/*
	 * Clear the framebuffer.
	 */
	rbox_windowmove(ip, 0, 0, 0, 0, ip->fbheight, ip->fbwidth, RR_CLEAR);
D 6
	rb_waitbusy(REGADDR);
E 6
I 6
	rb_waitbusy(ip->regbase);
E 6

	for(i = 0; i < 16; i++) {
D 6
		*(REGADDR + 0x63c3 + i*4) = 0x0;
		*(REGADDR + 0x6403 + i*4) = 0x0;
		*(REGADDR + 0x6803 + i*4) = 0x0;
		*(REGADDR + 0x6c03 + i*4) = 0x0;
		*(REGADDR + 0x73c3 + i*4) = 0x0;
		*(REGADDR + 0x7403 + i*4) = 0x0;
		*(REGADDR + 0x7803 + i*4) = 0x0;
		*(REGADDR + 0x7c03 + i*4) = 0x0;
E 6
I 6
		*(ip->regbase + 0x63c3 + i*4) = 0x0;
		*(ip->regbase + 0x6403 + i*4) = 0x0;
		*(ip->regbase + 0x6803 + i*4) = 0x0;
		*(ip->regbase + 0x6c03 + i*4) = 0x0;
		*(ip->regbase + 0x73c3 + i*4) = 0x0;
		*(ip->regbase + 0x7403 + i*4) = 0x0;
		*(ip->regbase + 0x7803 + i*4) = 0x0;
		*(ip->regbase + 0x7c03 + i*4) = 0x0;
E 6
	}

	REGBASE->rep_rule = 0x33;
	
	/*
	 * I cannot figure out how to make the blink planes stop. So, we
	 * must set both colormaps so that when the planes blink, and
	 * the secondary colormap is active, we still get text.
	 */
	CM1RED[0x00].value = 0x00;
	CM1GRN[0x00].value = 0x00;
	CM1BLU[0x00].value = 0x00;
	CM1RED[0x01].value = 0xFF;
	CM1GRN[0x01].value = 0xFF;
	CM1BLU[0x01].value = 0xFF;

	CM2RED[0x00].value = 0x00;
	CM2GRN[0x00].value = 0x00;
	CM2BLU[0x00].value = 0x00;
	CM2RED[0x01].value = 0xFF;
	CM2GRN[0x01].value = 0xFF;
	CM2BLU[0x01].value = 0xFF;

 	REGBASE->blink = 0x00;
	REGBASE->write_enable = 0x01;
	REGBASE->opwen = 0x00;
	
	ite_fontinit(ip);
	
	/*
	 * Stash the inverted cursor.
	 */
	rbox_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			    ip->cblanky, ip->cblankx, ip->ftheight,
			    ip->ftwidth, RR_COPYINVERTED);
}

rbox_deinit(ip)
	struct ite_softc *ip;
{
	rbox_windowmove(ip, 0, 0, 0, 0, ip->fbheight, ip->fbwidth, RR_CLEAR);
D 6
	rb_waitbusy(REGADDR);
E 6
I 6
	rb_waitbusy(ip->regbase);
E 6

   	ip->flags &= ~ITE_INITED;
}

rbox_putc(ip, c, dy, dx, mode)
	register struct ite_softc *ip;
        register int dy, dx;
	int c, mode;
{
        register int wrr = ((mode == ATTR_INV) ? RR_COPYINVERTED : RR_COPY);
	
	rbox_windowmove(ip, charY(ip, c), charX(ip, c),
			dy * ip->ftheight, dx * ip->ftwidth,
			ip->ftheight, ip->ftwidth, wrr);
}

rbox_cursor(ip, flag)
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

rbox_clear(ip, sy, sx, h, w)
	struct ite_softc *ip;
	register int sy, sx, h, w;
{
	rbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			sy * ip->ftheight, sx * ip->ftwidth, 
			h  * ip->ftheight, w  * ip->ftwidth,
			RR_CLEAR);
}

rbox_scroll(ip, sy, sx, count, dir)
        register struct ite_softc *ip;
        register int sy, count;
        int dir, sx;
{
	register int dy;
	register int dx = sx;
	register int height = 1;
	register int width = ip->cols;
D 8

	rbox_cursor(ip, ERASE_CURSOR);
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

	rbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			dy * ip->ftheight, dx * ip->ftwidth,
			height * ip->ftheight,
			width  * ip->ftwidth, RR_COPY);
}

rbox_windowmove(ip, sy, sx, dy, dx, h, w, func)
	struct ite_softc *ip;
	int sy, sx, dy, dx, h, w, func;
{
	register struct rboxfb *rp = REGBASE;
	if (h == 0 || w == 0)
		return;
	
D 6
	rb_waitbusy(REGADDR);
E 6
I 6
	rb_waitbusy(ip->regbase);
E 6
	rp->rep_rule = func << 4 | func;
	rp->source_y = sy;
	rp->source_x = sx;
	rp->dest_y = dy;
	rp->dest_x = dx;
	rp->wheight = h;
	rp->wwidth  = w;
	rp->wmove = 1;
}
#endif
E 1
