h34852
s 00001/00000/00190
d D 8.4 94/01/12 09:47:37 bostic 10 9
c lint
e
s 00001/00001/00189
d D 8.3 94/01/04 22:28:45 bostic 9 8
c lint
e
s 00078/00002/00112
d D 8.2 93/09/09 14:14:01 hibler 8 7
c support GC_DESCRIBE, add MAP/UNMAP mode calls
e
s 00002/00002/00112
d D 8.1 93/06/10 21:33:01 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00108
d D 7.6 92/10/11 09:23:55 bostic 6 5
c make kernel includes standard
e
s 00004/00004/00110
d D 7.5 92/06/05 15:30:52 hibler 5 4
c merge latest Utah hp300 code including 68040 support
e
s 00027/00006/00087
d D 7.4 91/05/07 09:54:00 hibler 4 3
c DIO-II support
e
s 00003/00003/00090
d D 7.3 90/12/16 16:35:56 bostic 3 2
c kernel reorg
e
s 00000/00014/00093
d D 7.2 90/12/05 18:26:28 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00107/00000/00000
d D 7.1 90/05/08 22:06:57 mckusick 1 0
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
D 4
 * from: Utah $Hdr: grf_tc.c 1.13 89/08/25$
E 4
I 4
D 5
 * from: Utah $Hdr: grf_tc.c 1.18 91/04/02$
E 5
I 5
D 8
 * from: Utah $Hdr: grf_tc.c 1.19 92/01/21$
E 8
I 8
 * from: Utah $Hdr: grf_tc.c 1.20 93/08/13$
E 8
E 5
E 4
 *
 *	%W% (Berkeley) %G%
 */

#include "grf.h"
#if NGRF > 0

/*
D 5
 * Graphics routines for TOPCAT frame buffer
E 5
I 5
 * Graphics routines for TOPCAT and CATSEYE frame buffers
E 5
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
#include "grf_tcreg.h"
E 6
I 6
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
I 8
#include <hp/dev/grfreg.h>
E 8
#include <hp300/dev/grf_tcreg.h>
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
 * Must fill in the grfinfo structure in g_softc.
 * Returns 0 if hardware not present, non-zero ow.
 */
tc_init(gp, addr)
	struct grf_softc *gp;
D 4
	u_char *addr;
E 4
I 4
	caddr_t addr;
E 4
{
	register struct tcboxfb *tp = (struct tcboxfb *) addr;
	struct grfinfo *gi = &gp->g_display;
	volatile u_char *fbp;
	u_char save;
	int fboff;
I 4
	extern caddr_t sctopa(), iomap();
E 4

D 2
#if defined(HP360) || defined(HP370)
	extern char grfregs[];
	if (addr == (u_char *)grfregs)
		gi->gd_regaddr = (caddr_t) DIOIIBASE;
	else
#endif
E 2
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
	gi->gd_fbwidth = (tp->fbwmsb << 8) | tp->fbwlsb;
	gi->gd_fbheight = (tp->fbhmsb << 8) | tp->fbhlsb;
D 4
	fboff = (tp->fbomsb << 8) | tp->fbolsb;
	gi->gd_fbaddr = (caddr_t) (*(addr + fboff) << 16);
E 4
D 2
#if defined(HP360) || defined(HP370)
	/*
	 * For DIO II space addresses offset is relative to the DIO II space.
	 * XXX: this should apply to all frame buffer types.
	 */
	if (gi->gd_regaddr >= (caddr_t)DIOIIBASE)
		gi->gd_fbaddr += (int) gi->gd_regaddr;
#endif
E 2
	gi->gd_fbsize = gi->gd_fbwidth * gi->gd_fbheight;
I 4
	fboff = (tp->fbomsb << 8) | tp->fbolsb;
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
	gi->gd_dwidth = (tp->dwmsb << 8) | tp->dwlsb;
	gi->gd_dheight = (tp->dhmsb << 8) | tp->dhlsb;
	gi->gd_planes = tp->num_planes;
	gi->gd_colors = 1 << gi->gd_planes;
	if (gi->gd_colors == 1) {
D 4
		fbp = (u_char *) IOV(gi->gd_fbaddr);
E 4
I 4
		fbp = (u_char *) gp->g_fbkva;
E 4
		tp->wen = ~0;
		tp->prr = 0x3;
		tp->fben = ~0;
		save = *fbp;
		*fbp = 0xFF;
		gi->gd_colors = *fbp + 1;
		*fbp = save;
	}
	return(1);
}

/*
 * Change the mode of the display.
 * Right now all we can do is grfon/grfoff.
 * Return a UNIX error number or 0 for success.
 * Function may not be needed anymore.
 */
/*ARGSUSED*/
D 8
tc_mode(gp, cmd)
E 8
I 8
tc_mode(gp, cmd, data)
E 8
	struct grf_softc *gp;
I 10
	int cmd;
E 10
I 8
	caddr_t data;
E 8
{
	int error = 0;

	switch (cmd) {
	case GM_GRFON:
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
		/* XXX */
		switch (gp->g_sw->gd_hwid) {
		case GID_HRCCATSEYE:
			bcopy("HP98550", fi->name, 8);
			break;
		case GID_LRCATSEYE:
			bcopy("HP98549", fi->name, 8);
			break;
		case GID_HRMCATSEYE:
			bcopy("HP98548", fi->name, 8);
			break;
		case GID_TOPCAT:
			switch (gi->gd_colors) {
			case 64:
				bcopy("HP98547", fi->name, 8);
				break;
			case 16:
				bcopy("HP98545", fi->name, 8);
				break;
			case 2:
				bcopy("HP98544", fi->name, 8);
				break;
			}
			break;
		}
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
