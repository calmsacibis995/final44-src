h30960
s 00001/00000/00156
d D 8.4 94/01/12 09:47:35 bostic 6 5
c lint
e
s 00001/00001/00155
d D 8.3 94/01/04 22:28:23 bostic 5 4
c lint
e
s 00053/00002/00103
d D 8.2 93/09/09 14:13:52 hibler 4 3
c support GC_DESCRIBE, add MAP/UNMAP mode calls
e
s 00002/00002/00103
d D 8.1 93/06/10 21:32:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00099
d D 7.2 92/10/11 09:23:51 bostic 2 1
c make kernel includes standard
e
s 00105/00000/00000
d D 7.1 92/06/05 15:33:05 hibler 1 0
c merge latest Utah hp300 code including 68040 support
e
u
U
t
T
I 1
/*
 * Copyright (c) 1991 University of Utah.
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Mark Davies of the Department of Computer
 * Science, Victoria University of Wellington, New Zealand.
 *
 * %sccs.include.redist.c%
 *
D 4
 * from: Utah $Hdr: grf_hy.c 1.1 92/01/22$
E 4
I 4
 * from: Utah $Hdr: grf_hy.c 1.2 93/08/13$
E 4
 *
 *	%W% (Berkeley) %G%
 */

#include "grf.h"
#if NGRF > 0

/*
 * Graphics routines for HYPERION frame buffer
 */
D 2
#include "sys/param.h"
#include "sys/errno.h"
E 2
I 2
#include <sys/param.h>
#include <sys/errno.h>
E 2

D 2
#include "hp/dev/grfioctl.h"
#include "hp/dev/grfvar.h"
#include "grf_hyreg.h"
E 2
I 2
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
#include <hp300/dev/grf_hyreg.h>
E 2

D 2
#include "../include/cpu.h"
E 2
I 2
#include <machine/cpu.h>
E 2

caddr_t badhyaddr = (caddr_t) -1;

/*
 * Initialize hardware.
 * Must fill in the grfinfo structure in g_softc.
 * Returns 0 if hardware not present, non-zero ow.
 */
hy_init(gp, addr)
	struct grf_softc *gp;
	caddr_t addr;
{
	register struct hyboxfb *hy = (struct hyboxfb *) addr;
	struct grfinfo *gi = &gp->g_display;
	int fboff;
	extern caddr_t sctopa(), iomap();

	if (ISIIOVA(addr))
		gi->gd_regaddr = (caddr_t) IIOP(addr);
	else
		gi->gd_regaddr = sctopa(vatosc(addr));
	gi->gd_regsize = 0x20000;
	gi->gd_fbwidth = (hy->fbwmsb << 8) | hy->fbwlsb;
	gi->gd_fbheight = (hy->fbhmsb << 8) | hy->fbhlsb;
	gi->gd_fbsize = (gi->gd_fbwidth * gi->gd_fbheight) >> 3;
	fboff = (hy->fbomsb << 8) | hy->fbolsb;
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
	gi->gd_dwidth = (hy->dwmsb << 8) | hy->dwlsb;
	gi->gd_dheight = (hy->dhmsb << 8) | hy->dhlsb;
	gi->gd_planes = hy->num_planes;
	gi->gd_colors = 1 << gi->gd_planes;

	return(1);
}

/*
 * Change the mode of the display.
 * Right now all we can do is grfon/grfoff.
 * Return a UNIX error number or 0 for success.
 * Function may not be needed anymore.
 */
D 4
hy_mode(gp, cmd)
E 4
I 4
hy_mode(gp, cmd, data)
E 4
	struct grf_softc *gp;
I 6
	int cmd;
E 6
I 4
	caddr_t data;
E 4
{
	int error = 0;

	switch (cmd) {
	case GM_GRFON:
	case GM_GRFOFF:
		break;
I 4

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
D 5
		int i, j;
E 5
I 5
		int i;
E 5

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
		bcopy("A1096A", fi->name, 7);	/* ?? */
		fi->attr = 0;			/* ?? */
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

E 4
	default:
		error = EINVAL;
		break;
	}
	return(error);
}
#endif
E 1
