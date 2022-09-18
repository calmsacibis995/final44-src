h60320
s 00002/00002/00166
d D 8.1 93/06/10 21:47:11 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00163
d D 7.4 92/10/11 10:01:43 bostic 4 3
c make kernel includes standard
e
s 00016/00016/00152
d D 7.3 92/06/18 21:33:27 hibler 3 2
c merge with latest Utah version
e
s 00005/00005/00163
d D 7.2 90/12/16 16:39:30 bostic 2 1
c kernel reorg
e
s 00168/00000/00000
d D 7.1 90/05/08 22:46:07 mckusick 1 0
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
 * from: Utah $Hdr: ite_rb.c 1.5 89/02/20$
E 3
I 3
 * from: Utah $Hdr: ite_rb.c 1.6 92/01/20$
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
#include "../hpdev/grf_rbreg.h"
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
E 4
I 4
#include <sys/param.h>
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
E 4

E 3
D 4
#include "../dev/grf_rbreg.h"
E 4
I 4
#include <hp300/dev/grf_rbreg.h>
E 4
E 2

#define REGBASE		((struct rboxfb *)(ip->regbase))
#define WINDOWMOVER	rbox_windowmove

rbox_init(ip)
	struct ite_softc *ip;
{
	int i;
	
D 3
	rb_waitbusy(REGADDR);
E 3
I 3
	rb_waitbusy(ip->regbase);
E 3
	DELAY(3000);

	REGBASE->interrupt = 0x04;
	REGBASE->display_enable = 0x01;
	REGBASE->video_enable = 0x01;
	REGBASE->drive = 0x01;
	REGBASE->vdrive = 0x0;

D 3
	ite_devinfo(ip);
E 3
I 3
	ite_fontinfo(ip);
E 3
	
	REGBASE->opwen = 0xFF;

	/*
	 * Clear the framebuffer.
	 */
	rbox_windowmove(ip, 0, 0, 0, 0, ip->fbheight, ip->fbwidth, RR_CLEAR);
D 3
	rb_waitbusy(REGADDR);
E 3
I 3
	rb_waitbusy(ip->regbase);
E 3
	
	for(i = 0; i < 16; i++) {
D 3
		*(REGADDR + 0x63c3 + i*4) = 0x0;
		*(REGADDR + 0x6403 + i*4) = 0x0;
		*(REGADDR + 0x6803 + i*4) = 0x0;
		*(REGADDR + 0x6c03 + i*4) = 0x0;
		*(REGADDR + 0x73c3 + i*4) = 0x0;
		*(REGADDR + 0x7403 + i*4) = 0x0;
		*(REGADDR + 0x7803 + i*4) = 0x0;
		*(REGADDR + 0x7c03 + i*4) = 0x0;
E 3
I 3
		*(ip->regbase + 0x63c3 + i*4) = 0x0;
		*(ip->regbase + 0x6403 + i*4) = 0x0;
		*(ip->regbase + 0x6803 + i*4) = 0x0;
		*(ip->regbase + 0x6c03 + i*4) = 0x0;
		*(ip->regbase + 0x73c3 + i*4) = 0x0;
		*(ip->regbase + 0x7403 + i*4) = 0x0;
		*(ip->regbase + 0x7803 + i*4) = 0x0;
		*(ip->regbase + 0x7c03 + i*4) = 0x0;
E 3
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

rbox_putc(ip, c, dy, dx, mode)
	register struct ite_softc *ip;
        register int dy, dx;
	int c, mode;
{
	rbox_windowmove(ip, charY(ip, c), charX(ip, c),
			dy * ip->ftheight, dx * ip->ftwidth,
			ip->ftheight, ip->ftwidth, RR_COPY);
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
	register int dy = sy - count;
	register int height = ip->rows - sy;

	rbox_cursor(ip, ERASE_CURSOR);

	rbox_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			dy * ip->ftheight, sx * ip->ftwidth,
			height * ip->ftheight,
			ip->cols * ip->ftwidth, RR_COPY);
}

rbox_windowmove(ip, sy, sx, dy, dx, h, w, func)
	struct ite_softc *ip;
	int sy, sx, dy, dx, h, w, func;
{
	register struct rboxfb *rp = REGBASE;
	if (h == 0 || w == 0)
		return;
	
D 3
	rb_waitbusy(REGADDR);
E 3
I 3
	rb_waitbusy(ip->regbase);
E 3
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
