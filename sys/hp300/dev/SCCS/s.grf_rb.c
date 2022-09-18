h21314
s 00001/00000/00170
d D 8.4 94/01/12 09:47:36 bostic 11 10
c lint
e
s 00001/00001/00169
d D 8.3 94/01/04 22:28:35 bostic 10 9
c lint
e
s 00055/00002/00115
d D 8.2 93/09/09 14:13:55 hibler 9 8
c support GC_DESCRIBE, add MAP/UNMAP mode calls
e
s 00002/00002/00115
d D 8.1 93/06/10 21:32:55 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00111
d D 7.7 92/10/11 09:23:53 bostic 7 6
c make kernel includes standard
e
s 00003/00003/00114
d D 7.6 92/06/05 15:30:51 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00027/00006/00090
d D 7.5 91/05/07 09:53:58 hibler 5 4
c DIO-II support
e
s 00003/00003/00093
d D 7.4 90/12/16 16:35:54 bostic 4 3
c kernel reorg
e
s 00001/00001/00095
d D 7.3 90/11/04 19:28:25 mckusick 3 2
c update identifier from Utah
e
s 00000/00058/00096
d D 7.2 90/05/25 15:44:15 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00154/00000/00000
d D 7.1 90/05/08 22:06:56 mckusick 1 0
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
 * from: Utah $Hdr: grf_rb.c 1.10 89/04/11$
E 3
I 3
D 5
 * from: Utah $Hdr: grf_rb.c 1.1 90/07/09$
E 5
I 5
D 6
 * from: Utah $Hdr: grf_rb.c 1.13 91/04/02$
E 6
I 6
D 9
 * from: Utah $Hdr: grf_rb.c 1.14 92/01/21$
E 9
I 9
 * from: Utah $Hdr: grf_rb.c 1.15 93/08/13$
E 9
E 6
E 5
E 3
 *
 *	%W% (Berkeley) %G%
 */

#include "grf.h"
#if NGRF > 0

/*
 * Graphics routines for the Renaissance, HP98720 Graphics system.
 */
D 4
#include "param.h"
#include "errno.h"
E 4
I 4
D 7
#include "sys/param.h"
#include "sys/errno.h"
E 7
I 7
#include <sys/param.h>
#include <sys/errno.h>
E 7
E 4

D 6
#include "grfioctl.h"
#include "grfvar.h"
E 6
I 6
D 7
#include "hp/dev/grfioctl.h"
#include "hp/dev/grfvar.h"
E 6
#include "grf_rbreg.h"
E 7
I 7
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
#include <hp300/dev/grf_rbreg.h>
E 7

D 4
#include "machine/cpu.h"
E 4
I 4
D 7
#include "../include/cpu.h"
E 7
I 7
#include <machine/cpu.h>
E 7
E 4

D 2
#ifdef notyet
static short rb_microcode[] = {
	0x5efe, 0x8a38, 0x0000, 0x0000, 0x0f00, 0, 0, 0,
	0x3efe, 0x8a38, 0x0000, 0x7003, 0xf706, 0, 0, 0,
	0x1efe, 0x8a38, 0x0000, 0x0000, 0x0000, 0, 0, 0,
	0x3efe, 0x8a38, 0x0000, 0x7003, 0xfc06, 0, 0, 0,
	0x1efe, 0x8a38, 0x0000, 0x0000, 0x0000, 0, 0, 0,
	0x3efe, 0x8a38, 0x0004, 0x40f7, 0xa006, 0, 0, 0,
	0x9efe, 0x8a38, 0x0000, 0x0000, 0x0000, 0, 0, 0,
	0x1efe, 0x8a38, 0x0000, 0x0000, 0x0000
};
#endif

E 2
/*
 * Initialize hardware.
 * Must point g_display at a grfinfo structure describing the hardware.
 * Returns 0 if hardware not present, non-zero ow.
 */
rb_init(gp, addr)
	struct grf_softc *gp;
D 5
	u_char *addr;
E 5
I 5
	caddr_t addr;
E 5
{
	register struct rboxfb *rbp;
	struct grfinfo *gi = &gp->g_display;
	int fboff;
I 5
	extern caddr_t sctopa(), iomap();
E 5

	rbp = (struct rboxfb *) addr;
D 5
	gi->gd_regaddr = (caddr_t) UNIOV(addr);
E 5
I 5
	if (ISIIOVA(addr))
		gi->gd_regaddr = (caddr_t) IIOP(addr);
	else
		gi->gd_regaddr = sctopa(vatosc(addr));
E 5
	gi->gd_regsize = 0x20000;
	gi->gd_fbwidth = (rbp->fbwmsb << 8) | rbp->fbwlsb;
	gi->gd_fbheight = (rbp->fbhmsb << 8) | rbp->fbhlsb;
D 5
	fboff = (rbp->fbomsb << 8) | rbp->fbolsb;
	gi->gd_fbaddr = (caddr_t) (*(addr + fboff) << 16);
E 5
	gi->gd_fbsize = gi->gd_fbwidth * gi->gd_fbheight;
I 5
	fboff = (rbp->fbomsb << 8) | rbp->fbolsb;
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
E 5
	gi->gd_dwidth = (rbp->dwmsb << 8) | rbp->dwlsb;
	gi->gd_dheight = (rbp->dwmsb << 8) | rbp->dwlsb;
	gi->gd_planes = 0;	/* ?? */
	gi->gd_colors = 256;
	return(1);
}
D 2

#ifdef notyet
/*
 * Download the microcode to the rbox.
 */
rb_download_microcode(regbase)
     caddr_t regbase;
{
	register short *rb_microcode_ptr = rb_microcode;
	register short *rb_cntlstore_ptr = (short *)((char *)regbase + 0xC000);
	register int i;

	/*
	 * Reset and halt transform engine
	 */
	*((char *)regbase + 0x8002) = 0x00a0;
	*((char *)regbase + 0x8002) = 0x0020;
	*((char *)regbase + 0x8002) = 0x0080;

	/*
	 * Select the first bank of control store.
	 */
	*((char *)regbase + 0x8007) = 0x0;

	/*
	 * Write the microcode into the control store address space.
	 */
	for (i = 0; i < sizeof(rb_microcode) / sizeof(rb_microcode[0]); i++)
		*rb_cntlstore_ptr++ = *rb_microcode_ptr++;

	/*
	 * Start microcode execution.
	 */
	*(short *)((char *)regbase + 0x8002) = 0x2000;
	*(short *)((char *)regbase + 0x8002) = 0x0;
	
	/*
	 * wait for renaissance to finish up.
	 */
	for (i = 0; i < 1000; i++) {
		if (*((char *)regbase + 0x8012) < 0)
			continue;
	}
}
#endif
E 2

/*
 * Change the mode of the display.
 * Right now all we can do is grfon/grfoff.
 * Return a UNIX error number or 0 for success.
 */
D 9
rb_mode(gp, cmd)
E 9
I 9
rb_mode(gp, cmd, data)
E 9
	register struct grf_softc *gp;
I 11
	int cmd;
E 11
I 9
	caddr_t data;
E 9
{
	register struct rboxfb *rbp;
	int error = 0;

D 5
	rbp = (struct rboxfb *) IOV(gp->g_display.gd_regaddr);
E 5
I 5
	rbp = (struct rboxfb *) gp->g_regkva;
E 5
	switch (cmd) {
	/*
	 * The minimal register info here is from the Renaissance X driver.
	 */
	case GM_GRFON:
	case GM_GRFOFF:
		break;
I 9

E 9
	case GM_GRFOVON:
		rbp->write_enable = 0;
		rbp->opwen = 0xF;
		rbp->drive = 0x10;
		break;
I 9

E 9
	case GM_GRFOVOFF:
		rbp->opwen = 0;
		rbp->write_enable = 0xffffffff;
		rbp->drive = 0x01;
		break;
I 9

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
D 10
		int i, j;
E 10
I 10
		int i;
E 10

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
		bcopy("HP98720", fi->name, 8);
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

E 9
	default:
		error = EINVAL;
		break;
	}
	return(error);
}

#endif
E 1
