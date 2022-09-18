h28390
s 00001/00001/00123
d D 8.2 94/01/12 16:38:13 hibler 8 7
c lint
e
s 00002/00002/00122
d D 8.1 93/06/10 21:24:18 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00009/00115
d D 7.6 92/10/11 08:55:13 bostic 6 5
c make kernel includes standard
e
s 00055/00042/00069
d D 7.5 92/06/05 15:23:27 hibler 5 4
c merge latest Utah hp300 code including 68040 support
e
s 00007/00009/00104
d D 7.4 91/05/04 19:49:19 karels 4 3
c update to current include, device calling conventions
e
s 00009/00009/00104
d D 7.3 90/12/16 16:36:37 bostic 3 2
c kernel reorg
e
s 00001/00001/00112
d D 7.2 90/11/04 19:35:22 mckusick 2 1
c update identifier from Utah
e
s 00113/00000/00000
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
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: ite_subr.c 1.3 89/04/11$
E 2
I 2
D 5
 * from: Utah $Hdr: ite_subr.c 1.1 90/07/09$
E 5
I 5
 * from: Utah $Hdr: ite_subr.c 1.4 92/01/21$
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
D 6
#include "param.h"
#include "conf.h"
#include "proc.h"
#include "ioctl.h"
#include "tty.h"
#include "systm.h"
E 6
I 6
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/systm.h>
E 6
E 4
E 3

D 6
#include "itevar.h"
#include "itereg.h"
E 6
I 6
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
E 6

D 3
#include "machine/cpu.h"
E 3
I 3
D 4
#include "../include/cpu.h"
E 4
I 4
D 6
#include "machine/cpu.h"
E 6
I 6
#include <machine/cpu.h>
E 6
E 4
E 3

D 5
ite_devinfo(ip)
E 5
I 5
ite_fontinfo(ip)
E 5
	struct ite_softc *ip;
{
D 5
	struct fontinfo *fi;
	struct font *fd;
E 5
I 5
	u_long fontaddr = getword(ip, getword(ip, FONTROM) + FONTADDR);
E 5

D 5
	fi = (struct fontinfo *) ((*FONTROM << 8 | *(FONTROM + 2)) + REGADDR);
	fd = (struct font *) ((fi->haddr << 8 | fi->laddr) + REGADDR);

	ip->ftheight = fd->fh;
	ip->ftwidth  = fd->fw;
	ip->fbwidth  = ITEREGS->fbwidth_h << 8 | ITEREGS->fbwidth_l;
	ip->fbheight = ITEREGS->fbheight_h << 8 | ITEREGS->fbheight_l;
	ip->dwidth   = ITEREGS->dispwidth_h << 8 | ITEREGS->dispwidth_l;
	ip->dheight  = ITEREGS->dispheight_h << 8 | ITEREGS->dispheight_l;
E 5
I 5
	ip->ftheight = getbyte(ip, fontaddr + FONTHEIGHT);
	ip->ftwidth  = getbyte(ip, fontaddr + FONTWIDTH);
E 5
	ip->rows     = ip->dheight / ip->ftheight;
	ip->cols     = ip->dwidth / ip->ftwidth;

	if (ip->fbwidth > ip->dwidth) {
		/*
		 * Stuff goes to right of display.
		 */
		ip->fontx    = ip->dwidth;
		ip->fonty    = 0;
		ip->cpl      = (ip->fbwidth - ip->dwidth) / ip->ftwidth;
		ip->cblankx  = ip->dwidth;
		ip->cblanky  = ip->fonty + ((128 / ip->cpl) +1) * ip->ftheight;
	}
	else {
		/*
		 * Stuff goes below the display.
		 */
		ip->fontx   = 0;
		ip->fonty   = ip->dheight;
		ip->cpl     = ip->fbwidth / ip->ftwidth;
		ip->cblankx = 0;
		ip->cblanky = ip->fonty + ((128 / ip->cpl) + 1) * ip->ftheight;
	}
}

ite_fontinit(ip)
	register struct ite_softc *ip;
{
D 5
	struct fontinfo *fi;
	struct font *fd;
	register u_char *fbmem, *dp;
	register int bn;
	int c, l, b;
E 5
I 5
	int bytewidth = (((ip->ftwidth - 1) / 8) + 1);
	int glyphsize = bytewidth * ip->ftheight;
	u_char fontbuf[500];		/* XXX malloc not initialize yet */
	u_char *dp, *fbmem;
	int c, i, romp;
E 5

D 5
	fi = (struct fontinfo *) ((*FONTROM << 8 | *(FONTROM + 2)) + REGADDR);
	fd = (struct font *) ((fi->haddr << 8 | fi->laddr) + REGADDR);
E 5
I 5
	romp = getword(ip, getword(ip, FONTROM) + FONTADDR) + FONTDATA;
	for (c = 0; c < 128; c++) {
		fbmem = (u_char *)
		    (FBBASE +
		     (ip->fonty + (c / ip->cpl) * ip->ftheight) * ip->fbwidth +
		     (ip->fontx + (c % ip->cpl) * ip->ftwidth));
		dp = fontbuf;
		for (i = 0; i < glyphsize; i++) {
			*dp++ = getbyte(ip, romp);
			romp += 2;
		}
		writeglyph(ip, fbmem, fontbuf);
	}
}
E 5

D 5
	dp = fd->data;
E 5
I 5
/*
 * Display independent versions of the readbyte and writeglyph routines.
 */
u_char
ite_readbyte(ip, disp)
	struct ite_softc *ip;
	int disp;
{
	return((u_char) *(((u_char *)ip->regbase) + disp));
}
E 5

D 5
	for (c = 0; c < 128; c++) {
		fbmem = (u_char *) FBBASE +
			(ip->fonty + (c / ip->cpl) * ip->ftheight) *
			ip->fbwidth;
		fbmem += ip->fontx + (c % ip->cpl) * ip->ftwidth;
		for (l = 0; l < ip->ftheight; l++) {
			bn = 7;
			for (b = 0; b < ip->ftwidth; b++) {
				if ((1 << bn) & *dp)
					*fbmem++ = 1;
				else
					*fbmem++ = 0;
				if (--bn < 0) {
					bn = 7;
					dp += 2;
				}
E 5
I 5
ite_writeglyph(ip, fbmem, glyphp)
	register struct ite_softc *ip;
	register u_char *fbmem, *glyphp;
{
	register int bn;
D 8
	int c, l, b;
E 8
I 8
	int l, b;
E 8

	for (l = 0; l < ip->ftheight; l++) {
		bn = 7;
		for (b = 0; b < ip->ftwidth; b++) {
			if ((1 << bn) & *glyphp)
				*fbmem++ = 1;
			else
				*fbmem++ = 0;
			if (--bn < 0) {
				bn = 7;
				glyphp++;
E 5
			}
D 5
			if (bn < 7)
				dp += 2;
			fbmem -= ip->ftwidth;
			fbmem += ip->fbwidth;
E 5
		}
I 5
		if (bn < 7)
			glyphp++;
		fbmem -= ip->ftwidth;
		fbmem += ip->fbwidth;
E 5
	}
D 5

E 5
}
#endif
E 1
