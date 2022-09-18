h00512
s 00002/00008/00248
d D 8.2 93/09/27 14:16:13 torek 6 5
c 1.29: move cursor address magic to autoconf.c (now that it is getting
c more and more complicated).
e
s 00002/00002/00254
d D 8.1 93/06/11 15:14:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00254
d D 7.4 93/04/20 19:20:15 torek 4 3
c spelling
e
s 00011/00011/00245
d D 7.3 92/10/11 12:45:41 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00251
d D 7.2 92/07/21 16:50:39 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00251/00000/00000
d D 7.1 92/07/13 00:43:48 torek 1 0
c date and time created 92/07/13 00:43:48 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: rcons_kern.c,v 1.26 92/07/09 08:01:28 torek Exp $
E 4
I 4
D 6
 * from: $Header: rcons_kern.c,v 1.28 93/04/20 11:15:38 torek Exp $
E 6
I 6
 * from: $Header: rcons_kern.c,v 1.29 93/09/27 00:52:02 torek Exp $
E 6
E 4
 */

D 3
#include "sys/param.h"
#include "sys/device.h"
#include "sys/fbio.h"
#include "sys/kernel.h"
#include "sys/systm.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
E 3
I 3
#include <sys/param.h>
#include <sys/device.h>
#include <sys/fbio.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
E 3

D 3
#include "machine/fbvar.h"
#include "machine/autoconf.h"
E 3
I 3
#include <machine/fbvar.h>
#include <machine/autoconf.h>
E 3

D 3
#include "../dev/kbd.h"
E 3
I 3
#include <sparc/dev/kbd.h>
E 3

D 3
#include "raster.h"
E 3
I 3
#include <sparc/rcons/raster.h>
E 3

extern struct tty *fbconstty;

static void rcons_belltmr(void *);

extern void rcons_puts(struct fbdevice *, char *, int);
extern void rcons_font(struct fbdevice *);

extern int (*v_putc)();
extern void ttrstrt(void *);

static struct fbdevice *myfbdevicep;

static void
rcons_cnputc(c)
	int c;
{
	char buf[1];

	if (c == '\n')
		rcons_puts(myfbdevicep, "\r\n", 2);
	else {
		buf[0] = c;
		rcons_puts(myfbdevicep, buf, 1);
	}
}

static void
rcons_output(tp)
	register struct tty *tp;
{
	register int s, n, i;
	char buf[OBUFSIZ];

	s = spltty();
	if (tp->t_state & (TS_TIMEOUT | TS_BUSY | TS_TTSTOP)) {
		splx(s);
		return;
	}
	tp->t_state |= TS_BUSY;
	splx(s);
	n = q_to_b(&tp->t_outq, buf, sizeof(buf));
	for (i = 0; i < n; ++i)
		buf[i] &= 0177;		/* strip parity (argh) */
	rcons_puts(myfbdevicep, buf, n);

	s = spltty();
	tp->t_state &= ~TS_BUSY;
	/* Come back if there's more to do */
	if (tp->t_outq.c_cc) {
		tp->t_state |= TS_TIMEOUT;
		timeout(ttrstrt, tp, 1);
	}
	if (tp->t_outq.c_cc <= tp->t_lowat) {
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		selwakeup(&tp->t_wsel);
	}
	splx(s);
}

/* Ring the console bell */
void
rcons_bell(fb)
	register struct fbdevice *fb;
{
	register int i, s;

	if (fb->fb_bits & FB_VISBELL) {
		/* invert the screen twice */
		for (i = 0; i < 2; ++i)
			raster_op(fb->fb_sp, 0, 0,
			    fb->fb_sp->width, fb->fb_sp->height,
			    RAS_INVERT, (struct raster *) 0, 0, 0);
	}

	s = splhigh();
	if (fb->fb_belldepth++) {
		if (fb->fb_belldepth > 3)
			fb->fb_belldepth = 3;
		splx(s);
	} else {
		fb->fb_ringing = 1;
		splx(s);
		(void) kbd_docmd(KBD_CMD_BELL, 0);
		/* XXX Chris doesn't like the following divide */
		timeout(rcons_belltmr, fb, hz/10);
	}
}

/* Bell timer service routine */
static void
rcons_belltmr(p)
	void *p;
{
	register struct fbdevice *fb = p;
	register int s = splhigh(), i;

	if (fb->fb_ringing) {
		fb->fb_ringing = 0;
		i = --fb->fb_belldepth;
		splx(s);
		(void) kbd_docmd(KBD_CMD_NOBELL, 0);
		if (i != 0)
			/* XXX Chris doesn't like the following divide */
			timeout(rcons_belltmr, fb, hz/30);
	} else {
		fb->fb_ringing = 1;
		splx(s);
		(void) kbd_docmd(KBD_CMD_BELL, 0);
		timeout(rcons_belltmr, fb, hz/10);
	}
}

static int
rcons_a2int(cp, deflt)
	register char *cp;
	register int deflt;
{
	register int i = 0;

	if (*cp == '\0')
		return (deflt);
	while (*cp != '\0')
		i = i * 10 + *cp++ - '0';
	return (i);
}

void
rcons_init(fb)
	register struct fbdevice *fb;
{
	/* XXX this should go away */
	static struct raster xxxraster;
	register struct raster *rp = fb->fb_sp = &xxxraster;
	register struct fbtype *ft = &fb->fb_type;
	register struct winsize *ws;
	register int i;
	static int row, col;
D 6
	char buf[100];
E 6

	myfbdevicep = fb;

	fb->fb_maxcol =
	    rcons_a2int(getpropstring(optionsnode, "screen-#columns"), 80);
	fb->fb_maxrow =
	    rcons_a2int(getpropstring(optionsnode, "screen-#rows"), 34);

	/* XXX mostly duplicates of data in other places */
	rp->width = ft->fb_width;
	rp->height = ft->fb_height;
	rp->depth = ft->fb_depth;
	if (fb->fb_linebytes & 0x3) {
		printf("rcons_init: linebytes assumption botched (0x%x)\n",
		    fb->fb_linebytes);
		return;
	}
	rp->linelongs = fb->fb_linebytes >> 2;
	rp->pixels = (u_long *)fb->fb_pixels;

	fb->fb_ras_blank = RAS_CLEAR;

	/* Setup the static font */
	rcons_font(fb);

	/* Impose upper bounds on fb_max{row,col} */
	i = ft->fb_height / fb->fb_font->height;
	if (fb->fb_maxrow > i)
		fb->fb_maxrow = i;
	i = ft->fb_width / fb->fb_font->width;
	if (fb->fb_maxcol > i)
		fb->fb_maxcol = i;

	/* Let the system know how big the console is */
	ws = &fbconstty->t_winsize;
	ws->ws_row = fb->fb_maxrow;
	ws->ws_col = fb->fb_maxcol;
	ws->ws_xpixel = ft->fb_width;
	ws->ws_ypixel = ft->fb_height;

	/* Center emulator screen (but align x origin to 32 bits) */
	fb->fb_xorigin =
	    ((ft->fb_width - fb->fb_maxcol * fb->fb_font->width) / 2) & ~0x1f;
	fb->fb_yorigin =
	    (ft->fb_height - fb->fb_maxrow * fb->fb_font->height) / 2;

	/* Emulator width and height used for scrolling */
	fb->fb_emuwidth = fb->fb_maxcol * fb->fb_font->width;
	if (fb->fb_emuwidth & 0x1f) {
		/* Pad to 32 bits */
		i = (fb->fb_emuwidth + 0x1f) & ~0x1f;
		/* Make sure emulator width isn't too wide */
		if (fb->fb_xorigin + i <= ft->fb_width)
			fb->fb_emuwidth = i;
	}
	fb->fb_emuheight = fb->fb_maxrow * fb->fb_font->height;

	/* Determine addresses of prom emulator row and column */
D 6
	fb->fb_row = fb->fb_col = NULL;
	sprintf(buf, "' line# >body >user %x !", &fb->fb_row);
	rominterpret(buf);
	sprintf(buf, "' column# >body >user %x !", &fb->fb_col);
	rominterpret(buf);
	if (fb->fb_row == NULL || fb->fb_col == NULL) {
E 6
I 6
	if (romgetcursoraddr(&fb->fb_row, &fb->fb_col)) {
E 6
		/* Can't find addresses; use private copies */
		fb->fb_row = &row;
		fb->fb_col = &col;
		row = col = 0;
		rcons_clear2eop(fb);	/* clear the display */
		rcons_cursor(fb);	/* and draw the initial cursor */
	} else {
		/* Prom emulator cursor is currently visible */
		fb->fb_bits |= FB_CURSOR;
	}

	/* Initialization done; hook us up */
	v_putc = (int (*)())rcons_cnputc;
	fbconstty->t_oproc = rcons_output;
	fbconstty->t_stop = (void (*)()) nullop;
}
E 1
