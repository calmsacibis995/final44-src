/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	bwone.c,v $
 * Revision 2.4  89/07/11  17:37:35  jjc
 * 	Changed to include machine dependent header files from machine/ not sun3/
 * 	because the Sun 4 uses this device driver too.
 * 	[89/07/06  16:46:09  jjc]
 * 
 * Revision 2.3  89/03/09  21:40:07  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:49:31  gm0w
 * 	Changes for cleanup.
 * 
 */
#ifndef	lint
static  char sccsid[] = "@(#)bwone.c 1.1 86/02/03 Copyr 1983 Sun Micro";
#endif

/*
 * Copyright (c) 1983 by Sun Microsystems, Inc.
 */

/*
 * Sun-1 Black & White Frame Buffer Driver
 */

#include <bwone.h>
#include <win.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/ioctl.h>

#include <machine/pte.h>
#include <machine/mmu.h>

#include <sun/fbio.h>

#include <sundev/mbvar.h>
#include <pixrect/pixrect.h>
#include <pixrect/pr_util.h>
#include <pixrect/bw1reg.h>
#include <pixrect/bw1var.h>
#include <mon/sunromvec.h>

#define BW1SIZE	(sizeof (struct bw1fb))
struct	bw1pr bwoneprdatadefault =
    { 0, 0, BW_REVERSEVIDEO, 0, 0 };

#if	NWIN > 0
#define BW1_OPS	&bw1_ops
struct	pixrectops bw1_ops = {
	bw1_rop,
	bw1_putcolormap,
	bw1_putattributes,
};
#else
#define BW1_OPS	(struct pixrectops *)0
#endif

struct	pixrect bwonepixrectdefault =
    { BW1_OPS, { 1024, 800 }, 1, 0};

/*
 * Driver information for auto-configuration stuff.
 */
int	bwoneprobe(), bwoneintr();
struct	pixrect bwonepixrect[NBWONE];
struct	bw1pr bwoneprdata[NBWONE];
struct	mb_device *bwoneinfo[NBWONE];
struct	mb_driver bwonedriver = {
	bwoneprobe, 0, 0, 0, 0, bwoneintr,
	BW1SIZE, "bwone", bwoneinfo, 0, 0, 0,
};

/*
 * We determine that the thing we're addressing is a bwone
 * board by trying to read from it.  This probe is inadequate but will
 * do for now.
 */
/*ARGSUSED*/
bwoneprobe(reg, unit)
	caddr_t reg;
	int	unit;
{

	if (peekc(reg) != -1) {
		/*
		 * The Sun 1 bw frame buffer doesn't indicate that an
		 * interrupt is pending on itself.
		 * Also, the interrupt level is user program changable.
		 * Thus, the kernel never knows what level to expect an
		 * interrupt on this device and doesn't know is an interrupt
		 * is pending.
		 * So, we add the bwoneintr routine to a list of interrupt
		 * handlers that are called if no one handles an interrupt.
		 * Add_default_intr screens out multiple calls with the same
		 * interrupt procedure.
		 */
		add_default_intr(bwoneintr);
		return (BW1SIZE);
	}
	return (0);
}

/*
 * Only allow opens for writing or reading and writing
 * because reading is nonsensical.
 */
bwoneopen(dev, flag)
	dev_t dev;
{
	return (fbopen(dev, flag, NBWONE, bwoneinfo));
}

/*
 * When close driver destroy pixrect.
 */
/*ARGSUSED*/
bwoneclose(dev, flag)
	dev_t dev;
{
	register int unit = minor(dev);

	if ((caddr_t)&bwoneprdata[unit] == bwonepixrect[unit].pr_data) {
		bzero((caddr_t)&bwoneprdata[unit], sizeof (struct bw1pr));
		bzero((caddr_t)&bwonepixrect[unit], sizeof (struct pixrect));
	}
}

/*ARGSUSED*/
bwoneioctl(dev, cmd, data, flag)
	dev_t dev;
	caddr_t data;
{
	register int unit = minor(dev);

	switch (cmd) {

	case FBIOGTYPE: {
		register struct fbtype *fb = (struct fbtype *)data;

		fb->fb_type = FBTYPE_SUN1BW;
		fb->fb_height = 800;
		fb->fb_width = 1024;
		fb->fb_depth = 1;
		fb->fb_cmsize = 2;
		fb->fb_size = 128*1024;
		break;
		}
	case FBIOGPIXRECT: {
		register struct fbpixrect *fbpr = (struct fbpixrect *)data;
		register struct bw1fb *bw1fb =
		    (struct bw1fb *)bwoneinfo[(unit)]->md_addr;

		/*
		 * "Allocate" and initialize pixrect data with default.
		 */
		fbpr->fbpr_pixrect = &bwonepixrect[unit];
		bwonepixrect[unit] = bwonepixrectdefault;
		fbpr->fbpr_pixrect->pr_data = (caddr_t) &bwoneprdata[unit];
		bwoneprdata[unit] = bwoneprdatadefault;
		/*
		 * Fixup pixrect data.
		 */
		bwoneprdata[unit].bwpr_va = bw1fb;
		/*
		 * Enable video
		 */
		bw1_setreg(bw1fb, BW_REGOTHERS, BWCONTROL_VIDEOENABLE,
		    BWXY_CONTROL);
		/*
		 * Clear interrupt
		 */
		bw1_intclear(bw1fb);
		break;
		}

	default:
		return (ENOTTY);
	}
	return (0);
}

int
bwoneintclear(bw1fb)
	struct	bw1fb *bw1fb;
{
	/*
	 * The Sun 1 bw frame buffer doesn't indicate that an
	 * interrupt is pending on itself so we don't know if the interrupt
	 * is for our device.  So, just turn off interrupts on the bwone board.
	 * This routine can be called from any level.
	 */
	bw1_intclear(bw1fb);
	/*
	 * We return 0 so that if the interrupt is for some other device
	 * then that device will have a chance at it.
	 */
	return(0);
}

int
bwoneintr()
{
	return (fbintr(NBWONE, bwoneinfo, bwoneintclear));
}

/*ARGSUSED*/
bwonemmap(dev, off, prot)
	dev_t dev;
	off_t off;
	int prot;
{
	return (fbmmap(dev, off, prot, NBWONE, bwoneinfo, BW1SIZE));
}

