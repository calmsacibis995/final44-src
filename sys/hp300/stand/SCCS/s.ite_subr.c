h26905
s 00002/00002/00115
d D 8.1 93/06/10 21:47:14 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00113
d D 7.4 92/10/11 10:01:44 bostic 4 3
c make kernel includes standard
e
s 00057/00044/00060
d D 7.3 92/06/18 21:33:28 hibler 3 2
c merge with latest Utah version
e
s 00003/00003/00101
d D 7.2 90/12/16 16:39:31 bostic 2 1
c kernel reorg
e
s 00104/00000/00000
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
 * from: Utah $Hdr: ite_subr.c 1.1 89/02/17$
E 3
I 3
 * from: Utah $Hdr: ite_subr.c 1.2 92/01/20$
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
E 2
I 2
D 4
#include "sys/param.h"
D 3
#include "../dev/itevar.h"
#include "../dev/itereg.h"
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
E 2

D 3
ite_devinfo(ip)
E 3
I 3
ite_fontinfo(ip)
E 3
	struct ite_softc *ip;
{
D 3
	struct fontinfo *fi;
	struct font *fd;
E 3
I 3
	u_long fontaddr = getword(ip, getword(ip, FONTROM) + FONTADDR);
E 3

D 3
	fi = (struct fontinfo *) ((*FONTROM << 8 | *(FONTROM + 2)) + REGADDR);
	fd = (struct font *) ((fi->haddr << 8 | fi->laddr) + REGADDR);

	ip->ftheight = fd->fh;
	ip->ftwidth  = fd->fw;
	ip->fbwidth  = ITEREGS->fbwidth_h << 8 | ITEREGS->fbwidth_l;
	ip->fbheight = ITEREGS->fbheight_h << 8 | ITEREGS->fbheight_l;
	ip->dwidth   = ITEREGS->dispwidth_h << 8 | ITEREGS->dispwidth_l;
	ip->dheight  = ITEREGS->dispheight_h << 8 | ITEREGS->dispheight_l;
E 3
I 3
	ip->ftheight = getbyte(ip, fontaddr + FONTHEIGHT);
	ip->ftwidth  = getbyte(ip, fontaddr + FONTWIDTH);
E 3
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
D 3
	struct fontinfo *fi;
	struct font *fd;
	register u_char *fbmem, *dp;
	register int bn;
	int c, l, b;
E 3
I 3
	int bytewidth = (((ip->ftwidth - 1) / 8) + 1);
	int glyphsize = bytewidth * ip->ftheight;
	u_char fontbuf[500];
	u_char *dp, *fbmem;
	int c, i, romp;
E 3

D 3
	fi = (struct fontinfo *) ((*FONTROM << 8 | *(FONTROM + 2)) + REGADDR);
	fd = (struct font *) ((fi->haddr << 8 | fi->laddr) + REGADDR);
E 3
I 3
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
E 3

D 3
	dp = fd->data;
E 3
I 3
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
E 3

D 3
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
E 3
I 3
ite_writeglyph(ip, fbmem, glyphp)
	register struct ite_softc *ip;
	register u_char *fbmem, *glyphp;
{
	register int bn;
	int c, l, b;

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
E 3
			}
D 3
			if (bn < 7)
				dp += 2;
			fbmem -= ip->ftwidth;
			fbmem += ip->fbwidth;
E 3
		}
I 3
		if (bn < 7)
			glyphp++;
		fbmem -= ip->ftwidth;
		fbmem += ip->fbwidth;
E 3
	}
D 3

E 3
}
#endif
E 1
