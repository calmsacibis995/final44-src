h02057
s 00001/00000/00123
d D 8.2 94/01/12 09:46:38 bostic 4 3
c lint
e
s 00002/00002/00121
d D 8.1 93/06/10 21:32:52 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00118
d D 7.2 92/10/11 09:23:53 bostic 2 1
c make kernel includes standard
e
s 00123/00000/00000
d D 7.1 92/06/05 15:33:04 hibler 1 0
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
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: grf_machdep.c 1.1 92/01/21
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Graphics display driver for the HP300/400 DIO/DIO-II based machines.
 * This is the hardware-dependent configuration portion of the driver.
 */

#include "grf.h"
#if NGRF > 0

D 2
#include "sys/param.h"
E 2
I 2
#include <sys/param.h>
E 2

D 2
#include "hp/dev/device.h"
#include "hp/dev/grfioctl.h"
#include "hp/dev/grfvar.h"
#include "hp/dev/grfreg.h"
E 2
I 2
#include <hp/dev/device.h>
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
#include <hp/dev/grfreg.h>
E 2

int grfprobe();
struct	driver grfdriver = { grfprobe, "grf" };

/*
 * XXX called from ite console init routine.
 * Does just what configure will do later but without printing anything.
 */
grfconfig()
{
	register caddr_t addr;
	register struct hp_hw *hw;
	register struct hp_device *hd, *nhd;

	for (hw = sc_table; hw->hw_type; hw++) {
	        if (!HW_ISDEV(hw, D_BITMAP))
			continue;
		/*
		 * Found one, now match up with a logical unit number
		 */
		nhd = NULL;		
		addr = hw->hw_kva;
		for (hd = hp_dinit; hd->hp_driver; hd++) {
			if (hd->hp_driver != &grfdriver || hd->hp_alive)
				continue;
			/*
			 * Wildcarded.  If first, remember as possible match.
			 */
			if (hd->hp_addr == NULL) {
				if (nhd == NULL)
					nhd = hd;
				continue;
			}
			/*
			 * Not wildcarded.
			 * If exact match done searching, else keep looking.
			 */
			if (sctova(hd->hp_addr) == addr) {
				nhd = hd;
				break;
			}
		}
		/*
		 * Found a match, initialize
		 */
		if (nhd && grfinit(addr, nhd->hp_unit))
			nhd->hp_addr = addr;
	}
}

/*
 * Normal init routine called by configure() code
 */
grfprobe(hd)
	struct hp_device *hd;
{
	struct grf_softc *gp = &grf_softc[hd->hp_unit];

	if ((gp->g_flags & GF_ALIVE) == 0 &&
	    !grfinit(hd->hp_addr, hd->hp_unit))
		return(0);
	printf("grf%d: %d x %d ", hd->hp_unit,
	       gp->g_display.gd_dwidth, gp->g_display.gd_dheight);
	if (gp->g_display.gd_colors == 2)
		printf("monochrome");
	else
		printf("%d color", gp->g_display.gd_colors);
	printf(" %s display\n", gp->g_sw->gd_desc);
	return(1);
}

grfinit(addr, unit)
	caddr_t addr;
I 4
	int unit;
E 4
{
	struct grf_softc *gp = &grf_softc[unit];
	register struct grfsw *gsw;
	struct grfreg *gr;

	gr = (struct grfreg *) addr;
	if (gr->gr_id != GRFHWID)
		return(0);
	for (gsw = grfsw; gsw < &grfsw[ngrfsw]; gsw++)
		if (gsw->gd_hwid == gr->gr_id2)
			break;
	if (gsw < &grfsw[ngrfsw] && (*gsw->gd_init)(gp, addr)) {
		gp->g_sw = gsw;
		gp->g_display.gd_id = gsw->gd_swid;
		gp->g_flags = GF_ALIVE;
		return(1);
	}
	return(0);
}
#endif
E 1
