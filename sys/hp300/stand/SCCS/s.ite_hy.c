h11301
s 00002/00002/00338
d D 8.1 93/06/10 21:47:07 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00338
d D 7.4 93/06/01 13:34:09 mckusick 4 3
c bug fix from Mark Davies <mark@comp.vuw.ac.nz>
e
s 00006/00006/00333
d D 7.3 92/10/11 10:01:42 bostic 3 2
c make kernel includes standard
e
s 00002/00001/00337
d D 7.2 92/06/23 22:09:15 hibler 2 1
c correct attribution
e
s 00338/00000/00000
d D 7.1 92/06/18 21:36:58 hibler 1 0
c date and time created 92/06/18 21:36:58 by hibler
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
D 2
 * Science Department.
E 2
I 2
 * Science Department and Mark Davies of the Department of Computer
 * Science, Victoria University of Wellington, New Zealand.
E 2
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: ite_hy.c 1.1 92/01/22$
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "samachdep.h"
E 3
I 3
#include <hp300/stand/samachdep.h>
E 3

#ifdef ITECONSOLE
D 3
#include "sys/param.h"
E 3
I 3
#include <sys/param.h>
E 3

D 3
#include "hp/dev/itevar.h"
#include "hp/dev/itereg.h"
#include "../dev/grf_hyreg.h"
E 3
I 3
#include <hp/dev/itevar.h>
#include <hp/dev/itereg.h>
#include <hp300/dev/grf_hyreg.h>
E 3

#define REGBASE	    	((struct hyboxfb *)(ip->regbase))
#define WINDOWMOVER     hyper_windowmove

#undef charX
#define	charX(ip,c)	\
	(((c) % (ip)->cpl) * ((((ip)->ftwidth + 7) / 8) * 8) + (ip)->fontx)

hyper_init(ip)
	register struct ite_softc *ip;
{
	int width;

	ite_fontinfo(ip);
	width = ((ip->ftwidth + 7) / 8) * 8;
	ip->cpl      = (ip->fbwidth - ip->dwidth) / width;
	ip->cblanky  = ip->fonty + ((128 / ip->cpl) +1) * ip->ftheight;

	REGBASE->nblank = 0x05;
	
	/*
	 * Clear the framebuffer on all planes.
	 */
	hyper_windowmove(ip, 0, 0, 0, 0, ip->fbheight, ip->fbwidth, RR_CLEAR);

	hyper_ite_fontinit(ip);

	/*
	 * Stash the inverted cursor.
	 */
	hyper_windowmove(ip, charY(ip, ' '), charX(ip, ' '),
			 ip->cblanky, ip->cblankx, ip->ftheight,
			 ip->ftwidth, RR_COPYINVERTED);
}

hyper_ite_fontinit(ip)
	register struct ite_softc *ip;
{
	register u_char *fbmem, *dp;
	int c, l, b;
	int stride, width;

D 4
	dp = (u_char *)getword(ip, getword(ip, FONTROM) + FONTADDR) + FONTDATA;
E 4
I 4
	dp = (u_char *)(getword(ip, getword(ip, FONTROM) + FONTADDR) +
	    ip->regbase) + FONTDATA;
E 4
	stride = ip->fbwidth >> 3;
	width = (ip->ftwidth + 7) / 8;

	for (c = 0; c < 128; c++) {
		fbmem = (u_char *) FBBASE +
			(ip->fonty + (c / ip->cpl) * ip->ftheight) *
			stride;
		fbmem += (ip->fontx >> 3) + (c % ip->cpl) * width;
		for (l = 0; l < ip->ftheight; l++) {
			for (b = 0; b < width; b++) {
				*fbmem++ = *dp;
				dp += 2;
			}
			fbmem -= width;
			fbmem += stride;
		}
	}
}

hyper_putc(ip, c, dy, dx, mode)
	register struct ite_softc *ip;
        register int dy, dx;
	int c, mode;
{
	hyper_windowmove(ip, charY(ip, c), charX(ip, c),
			 dy * ip->ftheight, dx * ip->ftwidth,
			 ip->ftheight, ip->ftwidth, RR_COPY);
}

hyper_cursor(ip, flag)
	register struct ite_softc *ip;
        int flag;
{
	switch (flag) {
	case MOVE_CURSOR:
		erase_cursor(ip);
		/* fall through ... */
	case DRAW_CURSOR:
		draw_cursor(ip);
		break;
	default:
		erase_cursor(ip);
		break;
	}
}

hyper_clear(ip, sy, sx, h, w)
	struct ite_softc *ip;
	register int sy, sx, h, w;
{
	hyper_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			 sy * ip->ftheight, sx * ip->ftwidth, 
			 h  * ip->ftheight, w  * ip->ftwidth,
			 RR_CLEAR);
}

hyper_scroll(ip, sy, sx, count, dir)
        register struct ite_softc *ip;
        register int sy, count;
        int dir, sx;
{
	register int dy = sy - count;
	register int height = ip->rows - sy;

	hyper_cursor(ip, ERASE_CURSOR);

	hyper_windowmove(ip, sy * ip->ftheight, sx * ip->ftwidth,
			 dy * ip->ftheight, sx * ip->ftwidth,
			 height * ip->ftheight,
			 ip->cols  * ip->ftwidth, RR_COPY);
}

D 3
#include "../dev/maskbits.h"
E 3
I 3
#include <hp300/dev/maskbits.h>
E 3

/* NOTE:
 * the first element in starttab could be 0xffffffff.  making it 0
 * lets us deal with a full first word in the middle loop, rather
 * than having to do the multiple reads and masks that we'd
 * have to do if we thought it was partial.
 */
int starttab[32] =
    {
	0x00000000,
	0x7FFFFFFF,
	0x3FFFFFFF,
	0x1FFFFFFF,
	0x0FFFFFFF,
	0x07FFFFFF,
	0x03FFFFFF,
	0x01FFFFFF,
	0x00FFFFFF,
	0x007FFFFF,
	0x003FFFFF,
	0x001FFFFF,
	0x000FFFFF,
	0x0007FFFF,
	0x0003FFFF,
	0x0001FFFF,
	0x0000FFFF,
	0x00007FFF,
	0x00003FFF,
	0x00001FFF,
	0x00000FFF,
	0x000007FF,
	0x000003FF,
	0x000001FF,
	0x000000FF,
	0x0000007F,
	0x0000003F,
	0x0000001F,
	0x0000000F,
	0x00000007,
	0x00000003,
	0x00000001
    };

int endtab[32] =
    {
	0x00000000,
	0x80000000,
	0xC0000000,
	0xE0000000,
	0xF0000000,
	0xF8000000,
	0xFC000000,
	0xFE000000,
	0xFF000000,
	0xFF800000,
	0xFFC00000,
	0xFFE00000,
	0xFFF00000,
	0xFFF80000,
	0xFFFC0000,
	0xFFFE0000,
	0xFFFF0000,
	0xFFFF8000,
	0xFFFFC000,
	0xFFFFE000,
	0xFFFFF000,
	0xFFFFF800,
	0xFFFFFC00,
	0xFFFFFE00,
	0xFFFFFF00,
	0xFFFFFF80,
	0xFFFFFFC0,
	0xFFFFFFE0,
	0xFFFFFFF0,
	0xFFFFFFF8,
	0xFFFFFFFC,
	0xFFFFFFFE
    };

hyper_windowmove(ip, sy, sx, dy, dx, h, w, func)
	struct ite_softc *ip;
	int sy, sx, dy, dx, h, w, func;
{
	unsigned int *psrcBase, *pdstBase;
				/* start of src and dst bitmaps */
	int width;		/* add to get to same position in next line */

	unsigned int *psrcLine, *pdstLine;
                                /* pointers to line with current src and dst */
	register unsigned int *psrc;  /* pointer to current src longword */
	register unsigned int *pdst;  /* pointer to current dst longword */

                                /* following used for looping through a line */
	unsigned int startmask, endmask;  /* masks for writing ends of dst */
	int nlMiddle;		/* whole longwords in dst */
	register int nl;	/* temp copy of nlMiddle */
	register unsigned int tmpSrc;
                                /* place to store full source word */
	register int xoffSrc;	/* offset (>= 0, < 32) from which to
                                   fetch whole longwords fetched
                                   in src */
	int nstart;		/* number of ragged bits at start of dst */
	int nend;		/* number of ragged bits at end of dst */
	int srcStartOver;	/* pulling nstart bits from src
                                   overflows into the next word? */

	if (h == 0 || w == 0)
		return;

	width = ip->fbwidth >> 5;
	psrcLine = ((unsigned int *) ip->fbbase) + (sy * width);
	pdstLine = ((unsigned int *) ip->fbbase) + (dy * width);

	/* x direction doesn't matter for < 1 longword */
	if (w <= 32)
	{
	    int srcBit, dstBit;     /* bit offset of src and dst */

	    pdstLine += (dx >> 5);
	    psrcLine += (sx >> 5);
	    psrc = psrcLine;
	    pdst = pdstLine;

	    srcBit = sx & 0x1f;
	    dstBit = dx & 0x1f;

	    while(h--)
	    {
                getandputrop(psrc, srcBit, dstBit, w, pdst, func)
	        pdst += width;
		psrc += width;
	    }
	}
	else
        {
	    maskbits(dx, w, startmask, endmask, nlMiddle)
	    if (startmask)
	      nstart = 32 - (dx & 0x1f);
	    else
	      nstart = 0;
	    if (endmask)
	      nend = (dx + w) & 0x1f;
	    else
	      nend = 0;

	    xoffSrc = ((sx & 0x1f) + nstart) & 0x1f;
	    srcStartOver = ((sx & 0x1f) + nstart) > 31;

	    pdstLine += (dx >> 5);
	    psrcLine += (sx >> 5);

	    while (h--)
	    {
	        psrc = psrcLine;
		pdst = pdstLine;

		if (startmask)
		{
		    getandputrop(psrc, (sx & 0x1f),
				 (dx & 0x1f), nstart, pdst, func)
		    pdst++;
		    if (srcStartOver)
		        psrc++;
		}

		/* special case for aligned operations */
		if (xoffSrc == 0)
		{
		    nl = nlMiddle;
		    while (nl--)
		    {
		        DoRop (*pdst, func, *psrc++, *pdst);
			pdst++;
		    }
		}
		else
		{
		    nl = nlMiddle + 1;
		    while (--nl)
		    {
		        getunalignedword (psrc, xoffSrc, tmpSrc)
			DoRop (*pdst, func, tmpSrc, *pdst);
			pdst++;
			psrc++;
		    }
		}

		if (endmask)
		{
		    getandputrop0(psrc, xoffSrc, nend, pdst, func);
		}

		pdstLine += width;
		psrcLine += width;
	    }
	}
}
#endif
E 1
