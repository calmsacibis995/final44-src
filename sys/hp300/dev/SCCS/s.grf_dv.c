h29277
s 00001/00000/00220
d D 8.4 94/01/12 09:46:56 bostic 10 9
c lint
e
s 00001/00001/00219
d D 8.3 94/01/04 22:27:54 bostic 9 8
c lint
e
s 00056/00002/00164
d D 8.2 93/09/09 14:13:44 hibler 8 7
c support GC_DESCRIBE, add MAP/UNMAP mode calls
e
s 00002/00002/00164
d D 8.1 93/06/10 21:32:33 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00160
d D 7.6 92/10/11 09:23:48 bostic 6 5
c make kernel includes standard
e
s 00003/00003/00163
d D 7.5 92/06/05 15:30:48 hibler 5 4
c merge latest Utah hp300 code including 68040 support
e
s 00027/00006/00139
d D 7.4 91/05/07 09:53:50 hibler 4 3
c DIO-II support
e
s 00003/00003/00142
d D 7.3 90/12/16 16:35:49 bostic 3 2
c kernel reorg
e
s 00001/00001/00144
d D 7.2 90/11/04 19:24:15 mckusick 2 1
c update identifier from Utah
e
s 00145/00000/00000
d D 7.1 90/05/08 22:06:55 mckusick 1 0
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
 * from: Utah $Hdr: grf_dv.c 1.6 89/04/11$
E 2
I 2
D 4
 * from: Utah $Hdr: grf_dv.c 1.1 90/07/09$
E 4
I 4
D 5
 * from: Utah $Hdr: grf_dv.c 1.10 91/04/02$
E 5
I 5
D 8
 * from: Utah $Hdr: grf_dv.c 1.11 92/01/21$
E 8
I 8
 * from: Utah $Hdr: grf_dv.c 1.12 93/08/13$
E 8
E 5
E 4
E 2
 *
 *	%W% (Berkeley) %G%
 */

#include "grf.h"
#if NGRF > 0

/*
 * Graphics routines for the DaVinci, HP98730/98731 Graphics system.
 */
D 3
#include "param.h"
#include "errno.h"
E 3
I 3
D 6
#include "sys/param.h"
#include "sys/errno.h"
E 6
I 6
#include <sys/param.h>
#include <sys/errno.h>
E 6
E 3

D 5
#include "grfioctl.h"
#include "grfvar.h"
E 5
I 5
D 6
#include "hp/dev/grfioctl.h"
#include "hp/dev/grfvar.h"
E 5
#include "grf_dvreg.h"
E 6
I 6
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
#include <hp300/dev/grf_dvreg.h>
E 6

D 3
#include "machine/cpu.h"
E 3
I 3
D 6
#include "../include/cpu.h"
E 6
I 6
#include <machine/cpu.h>
E 6
E 3

/*
 * Initialize hardware.
 * Must point g_display at a grfinfo structure describing the hardware.
 * Returns 0 if hardware not present, non-zero ow.
 */
dv_init(gp, addr)
	struct grf_softc *gp;
D 4
	u_char *addr;
E 4
I 4
	caddr_t addr;
E 4
{
	register struct dvboxfb *dbp;
	struct grfinfo *gi = &gp->g_display;
	int fboff;
I 4
	extern caddr_t sctopa(), iomap();
E 4

	dbp = (struct dvboxfb *) addr;
D 4
	gi->gd_regaddr = (caddr_t) UNIOV(addr);
E 4
I 4
	if (ISIIOVA(addr))
		gi->gd_regaddr = (caddr_t) IIOP(addr);
	else
		gi->gd_regaddr = sctopa(vatosc(addr));
E 4
	gi->gd_regsize = 0x20000;
	gi->gd_fbwidth = (dbp->fbwmsb << 8) | dbp->fbwlsb;
	gi->gd_fbheight = (dbp->fbhmsb << 8) | dbp->fbhlsb;
D 4
	fboff = (dbp->fbomsb << 8) | dbp->fbolsb;
	gi->gd_fbaddr = (caddr_t) (*(addr + fboff) << 16);
E 4
	gi->gd_fbsize = gi->gd_fbwidth * gi->gd_fbheight;
I 4
	fboff = (dbp->fbomsb << 8) | dbp->fbolsb;
	gi->gd_fbaddr = (caddr_t) (*((u_char *)addr + fboff) << 16);
	if (gi->gd_regaddr >= (caddr_t)DIOIIBASE) {
		/*
		 * For DIO II space the fbaddr just computed is the offset
		 * from the select code base (regaddr) of the framebuffer.
		 * Hence it is also implicitly the size of the register set.
		 */
		gi->gd_regsize = (int) gi->gd_fbaddr;
		gi->gd_fbaddr += (int) gi->gd_regaddr;
		gp->g_regkva = addr;
		gp->g_fbkva = addr + gi->gd_regsize;
	} else {
		/*
		 * For DIO space we need to map the seperate framebuffer.
		 */
		gp->g_regkva = addr;
		gp->g_fbkva = iomap(gi->gd_fbaddr, gi->gd_fbsize);
	}
E 4
	gi->gd_dwidth = (dbp->dwmsb << 8) | dbp->dwlsb;
	gi->gd_dheight = (dbp->dwmsb << 8) | dbp->dwlsb;
	gi->gd_planes = 0;	/* ?? */
	gi->gd_colors = 256;

	dv_reset(dbp);
	return(1);
}

/*
 *  Magic code herein.
 */
dv_reset(dbp)
	register struct dvboxfb *dbp;
{
  	dbp->reset = 0x80;
	DELAY(100);

	dbp->interrupt = 0x04;
	dbp->en_scan   = 0x01;
	dbp->fbwen     = ~0;
	dbp->opwen     = ~0;
	dbp->fold      = 0x01;
	dbp->drive     = 0x01;
	dbp->rep_rule  = 0x33;
	dbp->alt_rr    = 0x33;
	dbp->zrr       = 0x33;

	dbp->fbvenp    = 0xFF;
	dbp->dispen    = 0x01;
	dbp->fbvens    = 0x0;
	dbp->fv_trig   = 0x01;
	DELAY(100);
	dbp->vdrive    = 0x0;
	dbp->zconfig   = 0x0;

	while (dbp->wbusy & 0x01)
	  DELAY(100);

	dbp->cmapbank = 0;

	dbp->red0   = 0;
	dbp->red1   = 0;
	dbp->green0 = 0;
	dbp->green1 = 0;
	dbp->blue0  = 0;
	dbp->blue1  = 0;

	dbp->panxh   = 0;
	dbp->panxl   = 0;
	dbp->panyh   = 0;
	dbp->panyl   = 0;
	dbp->zoom    = 0;
	dbp->cdwidth = 0x50;
	dbp->chstart = 0x52;
	dbp->cvwidth = 0x22;
	dbp->pz_trig = 1;
}

/*
 * Change the mode of the display.
 * Right now all we can do is grfon/grfoff.
 * Return a UNIX error number or 0 for success.
 */
D 8
dv_mode(gp, cmd)
E 8
I 8
dv_mode(gp, cmd, data)
E 8
	register struct grf_softc *gp;
I 10
	int cmd;
E 10
I 8
	caddr_t data;
E 8
{
	register struct dvboxfb *dbp;
	int error = 0;

D 4
	dbp = (struct dvboxfb *) IOV(gp->g_display.gd_regaddr);
E 4
I 4
	dbp = (struct dvboxfb *) gp->g_regkva;
E 4
	switch (cmd) {
	case GM_GRFON:
	  	dbp->dispen = 0x01;
	  	break;
I 8

E 8
	case GM_GRFOFF:
		break;
I 8

E 8
	case GM_GRFOVON:
		dbp->opwen = 0xF;
		dbp->drive = 0x10;
		break;
I 8

E 8
	case GM_GRFOVOFF:
		dbp->opwen = 0;
		dbp->drive = 0x01;
		break;
I 8

	/*
	 * Remember UVA of mapping for GCDESCRIBE.
	 * XXX this should be per-process.
	 */
	case GM_MAP:
		gp->g_data = data;
		break;

	case GM_UNMAP:
		gp->g_data = 0;
		break;

#ifdef HPUXCOMPAT
	case GM_DESCRIBE:
	{
		struct grf_fbinfo *fi = (struct grf_fbinfo *)data;
		struct grfinfo *gi = &gp->g_display;
D 9
		int i, j;
E 9
I 9
		int i;
E 9

		/* feed it what HP-UX expects */
		fi->id = gi->gd_id;
		fi->mapsize = gi->gd_fbsize;
		fi->dwidth = gi->gd_dwidth;
		fi->dlength = gi->gd_dheight;
		fi->width = gi->gd_fbwidth;
		fi->length = gi->gd_fbheight;
		fi->bpp = NBBY;
		fi->xlen = (fi->width * fi->bpp) / NBBY;
		fi->npl = gi->gd_planes;
		fi->bppu = fi->npl;
		fi->nplbytes = fi->xlen * ((fi->length * fi->bpp) / NBBY);
		bcopy("HP98730", fi->name, 8);
		fi->attr = 2;	/* HW block mover */
		/*
		 * If mapped, return the UVA where mapped.
		 */
		if (gp->g_data) {
			fi->regbase = gp->g_data;
			fi->fbbase = fi->regbase + gp->g_display.gd_regsize;
		} else {
			fi->fbbase = 0;
			fi->regbase = 0;
		}
		for (i = 0; i < 6; i++)
			fi->regions[i] = 0;
		break;
	}
#endif

E 8
	default:
		error = EINVAL;
		break;
	}
	return(error);
}

#endif
E 1
