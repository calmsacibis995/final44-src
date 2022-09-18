h01823
s 00001/00000/00188
d D 8.4 94/01/12 09:48:05 bostic 10 9
c lint
e
s 00001/00001/00187
d D 8.3 94/01/04 22:28:10 bostic 9 8
c lint
e
s 00054/00002/00134
d D 8.2 93/09/09 14:13:49 hibler 8 7
c support GC_DESCRIBE, add MAP/UNMAP mode calls
e
s 00002/00002/00134
d D 8.1 93/06/10 21:32:39 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00130
d D 7.6 92/10/11 09:23:50 bostic 6 5
c make kernel includes standard
e
s 00003/00003/00133
d D 7.5 92/06/05 15:30:49 hibler 5 4
c merge latest Utah hp300 code including 68040 support
e
s 00013/00007/00123
d D 7.4 91/05/07 09:53:54 hibler 4 3
c DIO-II support
e
s 00003/00003/00127
d D 7.3 90/12/16 16:35:52 bostic 3 2
c kernel reorg
e
s 00001/00001/00129
d D 7.2 90/11/04 19:26:25 mckusick 2 1
c update identifier from Utah
e
s 00130/00000/00000
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
 * from: Utah $Hdr: grf_gb.c 1.13 89/04/11$
E 2
I 2
D 4
 * from: Utah $Hdr: grf_gb.c 1.1 90/07/09$
E 4
I 4
D 5
 * from: Utah $Hdr: grf_gb.c 1.16 91/04/02$
E 5
I 5
D 8
 * from: Utah $Hdr: grf_gb.c 1.17 92/01/21$
E 8
I 8
 * from: Utah $Hdr: grf_gb.c 1.18 93/08/13$
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
 * Graphics routines for the Gatorbox.
 *
 * Note: In the context of this system, "gator" and "gatorbox" both refer to
 *       HP 987x0 graphics systems.  "Gator" is not used for high res mono.
 *       (as in 9837 Gator systems)
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
#include "grf_gbreg.h"
E 6
I 6
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
E 6

D 3
#include "machine/cpu.h"
E 3
I 3
D 6
#include "../include/cpu.h"
E 6
I 6
#include <hp300/dev/grf_gbreg.h>
#include <machine/cpu.h>
E 6
E 3

#define CRTC_DATA_LENGTH  0x0e
u_char crtc_init_data[CRTC_DATA_LENGTH] = {
    0x29, 0x20, 0x23, 0x04, 0x30, 0x0b, 0x30,
    0x30, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00
};

/*
 * Initialize hardware.
 * Must point g_display at a grfinfo structure describing the hardware.
 * Returns 0 if hardware not present, non-zero ow.
 */
gb_init(gp, addr)
	struct grf_softc *gp;
D 4
	u_char *addr;
E 4
I 4
	caddr_t addr;
E 4
{
	register struct gboxfb *gbp;
	struct grfinfo *gi = &gp->g_display;
	u_char *fbp, save;
	int fboff;
I 4
	extern caddr_t sctopa(), iomap();
E 4

	gbp = (struct gboxfb *) addr;
D 4
	gi->gd_regaddr = (caddr_t) UNIOV(addr);
E 4
I 4
	if (ISIIOVA(addr))
		gi->gd_regaddr = (caddr_t) IIOP(addr);
	else
		gi->gd_regaddr = sctopa(vatosc(addr));
E 4
	gi->gd_regsize = 0x10000;
	gi->gd_fbwidth = 1024;		/* XXX */
	gi->gd_fbheight = 1024;		/* XXX */
D 4
	fboff = (gbp->fbomsb << 8) | gbp->fbolsb;
	gi->gd_fbaddr = (caddr_t) (*(addr + fboff) << 16);
E 4
	gi->gd_fbsize = gi->gd_fbwidth * gi->gd_fbheight;
I 4
	fboff = (gbp->fbomsb << 8) | gbp->fbolsb;
	gi->gd_fbaddr = (caddr_t) (*((u_char *)addr + fboff) << 16);
	gp->g_regkva = addr;
	gp->g_fbkva = iomap(gi->gd_fbaddr, gi->gd_fbsize);
E 4
	gi->gd_dwidth = 1024;		/* XXX */
	gi->gd_dheight = 768;		/* XXX */
	gi->gd_planes = 0;		/* how do we do this? */
	/*
	 * The minimal register info here is from the Gatorbox X driver.
	 */
D 4
	fbp = (u_char *) IOV(gi->gd_fbaddr);
E 4
I 4
	fbp = (u_char *) gp->g_fbkva;
E 4
	gbp->write_protect = 0;
	gbp->interrupt = 4;		/** fb_enable ? **/
	gbp->rep_rule = 3;		/* GXcopy */
	gbp->blink1 = 0xff;
	gbp->blink2 = 0xff;

	gb_microcode(gbp);

	/*
	 * Find out how many colors are available by determining
	 * which planes are installed.  That is, write all ones to
	 * a frame buffer location, see how many ones are read back.
	 */
	save = *fbp;
	*fbp = 0xFF;
	gi->gd_colors = *fbp + 1;
	*fbp = save;
	return(1);
}

/*
 * Program the 6845.
 */
gb_microcode(gbp)
	register struct gboxfb *gbp;
{
	register int i;
	
	for (i = 0; i < CRTC_DATA_LENGTH; i++) {
		gbp->crtc_address = i;
		gbp->crtc_data = crtc_init_data[i];
	}
}

/*
 * Change the mode of the display.
 * Right now all we can do is grfon/grfoff.
 * Return a UNIX error number or 0 for success.
 */
D 8
gb_mode(gp, cmd)
E 8
I 8
gb_mode(gp, cmd, data)
E 8
	register struct grf_softc *gp;
I 10
	int cmd;
E 10
I 8
	caddr_t data;
E 8
{
	struct gboxfb *gbp;
	int error = 0;

D 4
	gbp = (struct gboxfb *) IOV(gp->g_display.gd_regaddr);
E 4
I 4
	gbp = (struct gboxfb *) gp->g_regkva;
E 4
	switch (cmd) {
	case GM_GRFON:
		gbp->sec_interrupt = 1;
		break;
I 8

E 8
	case GM_GRFOFF:
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
		bcopy("HP98700", fi->name, 8);
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
