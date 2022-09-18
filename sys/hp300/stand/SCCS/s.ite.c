h15135
s 00002/00002/00272
d D 8.1 93/07/08 11:31:59 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00001/00262
d D 7.6 93/07/08 10:54:57 hibler 7 5
c hack to get around bad framebuffer sizes from HW
e
s 00002/00002/00261
d R 8.1 93/06/10 21:46:58 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00257
d D 7.5 92/10/11 10:01:40 bostic 5 4
c make kernel includes standard
e
s 00055/00047/00208
d D 7.4 92/06/18 21:33:24 hibler 4 3
c merge with latest Utah version
e
s 00005/00005/00250
d D 7.3 91/05/07 10:05:51 hibler 3 2
c DIO-II support
e
s 00005/00005/00250
d D 7.2 90/12/16 16:39:24 bostic 2 1
c kernel reorg
e
s 00255/00000/00000
d D 7.1 90/05/08 22:46:05 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 3
 * from: Utah $Hdr: ite.c 1.19 89/08/22$
E 3
I 3
D 4
 * from: Utah $Hdr: ite.c 1.20 91/01/21$
E 4
I 4
D 7
 * from: Utah $Hdr: ite.c 1.23 92/02/28$
E 7
I 7
 * from: Utah $Hdr: ite.c 1.24 93/06/25$
E 7
E 4
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Standalone Internal Terminal Emulator (CRT and keyboard)
 */
D 5
#include "samachdep.h"
E 5
I 5
#include <hp300/stand/samachdep.h>
E 5

#ifdef ITECONSOLE

D 2
#include "param.h"
#include "machine/cons.h"
#include "../hpdev/device.h"
#include "../hpdev/itevar.h"
#include "../hpdev/grfvar.h"
E 2
I 2
D 5
#include "sys/param.h"
D 4
#include "../hp300/cons.h"
#include "../dev/device.h"
#include "../dev/itevar.h"
#include "../dev/grfvar.h"
E 4
I 4
#include "hp/dev/cons.h"
#include "hp/dev/device.h"
#include "hp/dev/itevar.h"
#include "hp/dev/grfreg.h"
E 5
I 5
#include <sys/param.h>
#include <hp/dev/cons.h>
#include <hp/dev/device.h>
#include <hp/dev/itevar.h>
#include <hp/dev/grfreg.h>
E 5
E 4
E 2

D 4
int nodev();
E 4
I 4
extern int nodev();
extern u_char ite_readbyte();
extern int ite_writeglyph();
E 4

D 4
int topcat_init(), topcat_putc();
int topcat_clear(), topcat_cursor(), topcat_scroll();
int gatorbox_init(), gatorbox_clear();
int gatorbox_putc(), gatorbox_cursor(), gatorbox_scroll();
int rbox_init(), rbox_clear();
int rbox_putc(), rbox_cursor(), rbox_scroll();
int dvbox_init(), dvbox_clear();
int dvbox_putc(), dvbox_cursor(), dvbox_scroll();
E 4
I 4
extern int topcat_init(), topcat_putc();
extern int topcat_clear(), topcat_cursor(), topcat_scroll();
extern int gbox_init(), gbox_clear();
extern int gbox_putc(), gbox_cursor(), gbox_scroll();
extern int rbox_init(), rbox_clear();
extern int rbox_putc(), rbox_cursor(), rbox_scroll();
extern int dvbox_init(), dvbox_clear();
extern int dvbox_putc(), dvbox_cursor(), dvbox_scroll();
extern int hyper_init(), hyper_clear();
extern int hyper_putc(), hyper_cursor(), hyper_scroll();
E 4

struct itesw itesw[] = {
D 4
	topcat_init,		nodev,			topcat_clear,
	topcat_putc,		topcat_cursor,		topcat_scroll,

	gatorbox_init,		nodev,			gatorbox_clear,
	gatorbox_putc,		gatorbox_cursor,	gatorbox_scroll,

	rbox_init,		nodev,			rbox_clear,
	rbox_putc,		rbox_cursor,		rbox_scroll,

      	dvbox_init,		nodev,			dvbox_clear,
	dvbox_putc,		dvbox_cursor,		dvbox_scroll,
E 4
I 4
	GID_TOPCAT,
	topcat_init,	nodev,		topcat_clear,	topcat_putc,
	topcat_cursor,	topcat_scroll,	ite_readbyte,	ite_writeglyph,
	GID_GATORBOX,
	gbox_init,	nodev,		gbox_clear,	gbox_putc,
	gbox_cursor,	gbox_scroll,	ite_readbyte,	ite_writeglyph,
	GID_RENAISSANCE,
	rbox_init,	nodev,		rbox_clear,	rbox_putc,
	rbox_cursor,	rbox_scroll,	ite_readbyte,	ite_writeglyph,
	GID_LRCATSEYE,
	topcat_init,	nodev,		topcat_clear,	topcat_putc,
	topcat_cursor,	topcat_scroll,	ite_readbyte,	ite_writeglyph,
	GID_HRCCATSEYE,
	topcat_init,	nodev,		topcat_clear,	topcat_putc,
	topcat_cursor,	topcat_scroll,	ite_readbyte,	ite_writeglyph,
	GID_HRMCATSEYE,
	topcat_init,	nodev,		topcat_clear,	topcat_putc,
	topcat_cursor,	topcat_scroll,	ite_readbyte,	ite_writeglyph,
	GID_DAVINCI,
      	dvbox_init,	nodev,		dvbox_clear,	dvbox_putc,
	dvbox_cursor,	dvbox_scroll,	ite_readbyte,	ite_writeglyph,
	GID_HYPERION,
	hyper_init,	nodev,		hyper_clear,	hyper_putc,
	hyper_cursor,	hyper_scroll,	ite_readbyte,	ite_writeglyph,
E 4
};
I 4
int	nitesw = sizeof(itesw) / sizeof(itesw[0]);
E 4

/* these guys need to be in initialized data */
int itecons = -1;
struct  ite_softc ite_softc[NITE] = { 0 };

/*
 * Locate all bitmapped displays
 */
iteconfig()
{
	extern struct hp_hw sc_table[];
	int dtype, fboff, i;
	struct hp_hw *hw;
	struct grfreg *gr;
	struct ite_softc *ip;

	i = 0;
D 3
	for (hw = sc_table; hw < &sc_table[MAX_CTLR]; hw++) {
		if (hw->hw_type != BITMAP)
E 3
I 3
	for (hw = sc_table; hw < &sc_table[MAXCTLRS]; hw++) {
	        if (!HW_ISDEV(hw, D_BITMAP))
E 3
			continue;
D 3
		gr = (struct grfreg *) hw->hw_addr;
E 3
I 3
		gr = (struct grfreg *) hw->hw_kva;
E 3
		/* XXX: redundent but safe */
		if (badaddr((caddr_t)gr) || gr->gr_id != GRFHWID)
			continue;
D 4
		switch (gr->gr_id2) {
		case GID_GATORBOX:
			dtype = ITE_GATORBOX;
			break;
		case GID_TOPCAT:
		case GID_LRCATSEYE:
		case GID_HRCCATSEYE:
		case GID_HRMCATSEYE:
			dtype = ITE_TOPCAT;
			break;
		case GID_RENAISSANCE:
			dtype = ITE_RENAISSANCE;
			break;
		case GID_DAVINCI:
			dtype = ITE_DAVINCI;
			break;
		default:
E 4
I 4
		for (dtype = 0; dtype < nitesw; dtype++)
			if (itesw[dtype].ite_hwid == gr->gr_id2)
				break;
		if (dtype == nitesw)
E 4
			continue;
D 4
		}
E 4
		if (i >= NITE)
			break;
		ip = &ite_softc[i];
I 4
		ip->isw = &itesw[dtype];
E 4
		ip->regbase = (caddr_t) gr;
		fboff = (gr->gr_fbomsb << 8) | gr->gr_fbolsb;
		ip->fbbase = (caddr_t) (*((u_char *)ip->regbase+fboff) << 16);
		/* DIO II: FB offset is relative to select code space */
D 3
		if (ip->regbase >= (caddr_t)0x1000000)
E 3
I 3
		if (ip->regbase >= (caddr_t)DIOIIBASE)
E 3
			ip->fbbase += (int)ip->regbase;
I 4
		ip->fbwidth  = gr->gr_fbwidth_h << 8 | gr->gr_fbwidth_l;
		ip->fbheight = gr->gr_fbheight_h << 8 | gr->gr_fbheight_l;
		ip->dwidth   = gr->gr_dwidth_h << 8 | gr->gr_dwidth_l;
		ip->dheight  = gr->gr_dheight_h << 8 | gr->gr_dheight_l;
I 7
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
E 7
E 4
		ip->flags = ITE_ALIVE|ITE_CONSOLE;
D 4
		ip->type = dtype;
E 4
		i++;
	}
}

#ifdef CONSDEBUG
/*
 * Allows us to cycle through all possible consoles (NITE ites and serial port)
 * by using SHIFT-RESET on the keyboard.
 */
int	whichconsole = -1;
#endif

iteprobe(cp)
	struct consdev *cp;
{
	register int ite;
	register struct ite_softc *ip;
	int unit, pri;

#ifdef CONSDEBUG
	whichconsole = ++whichconsole % (NITE+1);
#endif

	if (itecons != -1)
		return(1);

	iteconfig();
	unit = -1;
	pri = CN_DEAD;
	for (ite = 0; ite < NITE; ite++) {
#ifdef CONSDEBUG
		if (ite < whichconsole)
			continue;
#endif
		ip = &ite_softc[ite];
		if ((ip->flags & (ITE_ALIVE|ITE_CONSOLE))
		    != (ITE_ALIVE|ITE_CONSOLE))
			continue;
		if ((int)ip->regbase == GRFIADDR) {
			pri = CN_INTERNAL;
			unit = ite;
		} else if (unit < 0) {
			pri = CN_NORMAL;
			unit = ite;
		}
	}
	cp->cn_dev = unit;
	cp->cn_pri = pri;
}

iteinit(cp)
	struct consdev *cp;
{
	int ite = cp->cn_dev;
	struct ite_softc *ip;

	if (itecons != -1)
		return(1);

	ip = &ite_softc[ite];

	ip->curx = 0;
	ip->cury = 0;
	ip->cursorx = 0;
	ip->cursory = 0;

D 4
	(*itesw[ip->type].ite_init)(ip);
	(*itesw[ip->type].ite_cursor)(ip, DRAW_CURSOR);
E 4
I 4
	(*ip->isw->ite_init)(ip);
	(*ip->isw->ite_cursor)(ip, DRAW_CURSOR);
E 4

	itecons = ite;
	kbdinit();
}

iteputchar(c)
	register int c;
{
	register struct ite_softc *ip = &ite_softc[itecons];
D 4
	register struct itesw *sp = &itesw[ip->type];
E 4
I 4
	register struct itesw *sp = ip->isw;
E 4

	c &= 0x7F;
	switch (c) {

	case '\n':
		if (++ip->cury == ip->rows) {
			ip->cury--;
			(*sp->ite_scroll)(ip, 1, 0, 1, SCROLL_UP);
			ite_clrtoeol(ip, sp, ip->cury, 0);
		}
		else
			(*sp->ite_cursor)(ip, MOVE_CURSOR);
		break;

	case '\r':
		ip->curx = 0;
		(*sp->ite_cursor)(ip, MOVE_CURSOR);
		break;

	case '\b':
		if (--ip->curx < 0)
			ip->curx = 0;
		else
			(*sp->ite_cursor)(ip, MOVE_CURSOR);
		break;

	default:
		if (c < ' ' || c == 0177)
			break;
		(*sp->ite_putc)(ip, c, ip->cury, ip->curx, ATTR_NOR);
		(*sp->ite_cursor)(ip, DRAW_CURSOR);
		itecheckwrap(ip, sp);
		break;
	}
}

itecheckwrap(ip, sp)
     register struct ite_softc *ip;
     register struct itesw *sp;
{
	if (++ip->curx == ip->cols) {
		ip->curx = 0;
		if (++ip->cury == ip->rows) {
			--ip->cury;
			(*sp->ite_scroll)(ip, 1, 0, 1, SCROLL_UP);
			ite_clrtoeol(ip, sp, ip->cury, 0);
			return;
		}
	}
	(*sp->ite_cursor)(ip, MOVE_CURSOR);
}

ite_clrtoeol(ip, sp, y, x)
     register struct ite_softc *ip;
     register struct itesw *sp;
     register int y, x;
{
	(*sp->ite_clear)(ip, y, x, 1, ip->cols - x);
	(*sp->ite_cursor)(ip, DRAW_CURSOR);
}

itegetchar()
{
#ifdef SMALL
	return (0);
#else
	return (kbdgetc());
#endif
}
#endif
E 1
