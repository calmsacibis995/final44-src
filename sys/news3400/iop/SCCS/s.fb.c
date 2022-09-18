h42615
s 00002/00002/00693
d D 8.1 93/06/11 15:00:28 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00695
d D 7.3 93/03/09 23:51:26 utashiro 3 2
c cleanup header and machine dependency.
e
s 00018/00018/00679
d D 7.2 92/12/17 03:18:12 utashiro 2 1
c make kernel includes standard
e
s 00697/00000/00000
d D 7.1 92/06/04 15:54:54 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: fb.c,v 4.300 91/06/27 20:43:06 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "../include/fix_machine_type.h"
E 2
I 2
D 3
#include <machine/fix_machine_type.h>
E 2

E 3
#include "fb.h"
#if NFB > 0
/*
 * Frame buffer driver
 */

D 2
#include "types.h"
#include "../include/pte.h"
#include "../include/cpu.h"
E 2
I 2
#include <sys/types.h>
#include <machine/pte.h>
#include <machine/cpu.h>
E 2

D 2
#include "param.h"
#include "proc.h"
#include "user.h"
#include "buf.h"
#include "vm/vm.h"
#include "systm.h"
#include "map.h"
#include "uio.h"
#include "kernel.h"
E 2
I 2
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <vm/vm.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/uio.h>
#include <sys/kernel.h>
E 2

D 2
#include "../iop/framebuf.h"
#include "../iop/fbreg.h"
#include "../iodev/ioptohb.h"
E 2
I 2
#include <news3400/iop/framebuf.h>
#include <news3400/iop/fbreg.h>
#include <news3400/iodev/ioptohb.h>
E 2

#ifdef CPU_SINGLE
D 2
#include "../hbdev/hbvar.h"
E 2
I 2
#include <news3400/hbdev/hbvar.h>
E 2

#define ipc_phys(x)	(caddr_t)((int)(x))
#define ipc_log(x)	(caddr_t)((int)(x) | 0x80000000)

#define iop_driver	hb_driver
#define iop_device	hb_device

extern rop_xint();
#else /* CPU_SINGLE */
D 2
#include "../iop/iopvar.h"
E 2
I 2
#include <news3400/iop/iopvar.h>
E 2

#ifdef IPC_MRX
#include "../ipc/newsipc.h"

#ifdef mips
#define ipc_phys(x)	K0_TT0(x)
#define ipc_log(x)	TT0_K0(x)
#else
#define	ipc_phys(x)	(caddr_t)((int)(x) & ~0x80000000)
#define	ipc_log(x)	(caddr_t)((int)(x) | 0x80000000)
#endif

static int port_fb, port_fb_iop;
#endif /* IPC_MRX */
#endif /* CPU_SINGLE */

#define FB_USED		1
#define VIDEO_USED	2

/*
 * driver definition
 */
int fbprobe(), fbattach();

struct iop_device *fbinfo[NFB];
struct iop_driver fbdriver =
#ifdef CPU_SINGLE
	{ fbprobe, 0, fbattach, 0, 0, "fb", fbinfo, "fbc", 0, 0 };
#else
	{ fbprobe, 0, fbattach, 0, "fb", fbinfo };
#endif

/* static */
static struct fb_softc fb_softc[NFB];
static struct fbreg	fbreg[NFB];
static int fbstate;
static struct fbreg	*last_fb;

static char *devname[] = {
/* 0*/	"",
/* 1*/	"NWB-512",
/* 2*/	"NWB-225",
/* 3*/	"POP-MONO",
/* 4*/	"POP-COLOR",
/* 5*/	"NWB-514",
/* 6*/	"NWB-251",
/* 7*/	"LCD-MONO",
/* 8*/	"LDC-COLOR",
/* 9*/	"NWB-518",
/*10*/	"NWB-252",
/*11*/	"NWB-253",
/*12*/	"NWB-254",
/*13*/	"NWB-255",
/*14*/	"SLB-101",
/*15*/	"NWB-256",
/*16*/	"NWB-257",
};

static void	fblock(), fbunlock(), fbreset();
static int	fbinit();

#ifdef CPU_DOUBLE
#ifdef USE_RAW_INTR

#include "../mrx/h/ipc.h"

#ifdef mips
# define	FB_ADDR		&IPC_ARG(&ipc_block, ARG_CPU, 4)
#else
# define	FB_ADDR		&IPC_ARG(&ipc_block, ARG_CPU0, 4)
# define	volatile
#endif

typedef struct fbreg *fbregp;
int fb_waiting;

Xfb_intr(chan, arg)
	int chan;
	int arg;
{

	intrcnt[INTR_BITMAP]++;
	if (fb_waiting) {
		fb_waiting = 0;
		wakeup((caddr_t)&fb_waiting);
	}
}

static void
fbwait()
{
	int s = splfb();

	while (*(volatile fbregp *)FB_ADDR) {
		fb_waiting = 1;
		sleep((caddr_t)&fb_waiting, FBPRI);
	}
	(void) splx(s);
}

void
fbstart(fbp, wait)
	struct fbreg *fbp;
	int wait;
{

	fbwait();
	*(volatile fbregp *)FB_ADDR =
#ifdef mips
	    (volatile fbregp)ipc_phys(MACH_UNCACHED_TO_CACHED(fbp));
#else
	    (volatile fbregp)ipc_phys(fbp);
#endif
	if (wait)
		fbwait();
}

#else /* USE_RAW_INTR */

void
fbstart(fbp, wait)
	register struct fbreg *fbp;
	int wait;
{
	int s = splfb();

#ifdef IPC_MRX
	msg_send(port_fb_iop, port_fb, fbp, sizeof(*fbp), MSG_INDIRECT);
#endif

	last_fb = fbp;
	if (wait) {
		fbstate |= FB_WAIT;
		sleep((caddr_t)fbreg, FBPRI);
	} else {
		fbstate |= FB_DELAY;
	}
	splx(s);
}

void
fbcint(arg)
	int arg;
{

	intrcnt[INTR_BITMAP]++;

#ifdef IPC_MRX
	msg_recv(arg, NULL, NULL, NULL, 0);
#ifdef mips
	clean_dcache((caddr_t)last_fb, sizeof(struct fbreg));
#endif
#endif /* IPC_MRX */

	if (fbstate & FB_WAIT) {
		fbstate &= ~FB_WAIT;
		wakeup((caddr_t)fbreg);
	} else if (fbstate & FB_DELAY) {
		fbstate &= ~FB_DELAY;
	} else if (fbstate & FB_DELAY2) {
		fbstate &= ~(FB_BUSY|FB_DELAY2);
		if (fbstate & FB_WANTED) {
			fbstate &= ~FB_WANTED;
			wakeup((caddr_t)&fbstate);
		}
	}
	return;
}
#endif /* USE_RAW_INTR */
#endif /* CPU_DOUBLE */

/* ARGSUSED */
fbprobe(ii)
	struct iop_device *ii;
{
	register int unit = ii->ii_unit;
	register struct fb_softc *fb = &fb_softc[unit];
#if defined(IPC_MRX) && defined(mips)
	register struct fbreg *fbp =
	    (struct fbreg *)MACH_CACHED_TO_UNCACHED(&fbreg[unit]);
#else
	register struct fbreg *fbp = &fbreg[unit];
#endif

#ifdef CPU_SINGLE
	if (unit == 0)
		register_hb_intr2(rop_xint, ii->ii_unit, ii->ii_intr);
#endif

#ifdef IPC_MRX
	if (port_fb_iop <= 0) {
#ifdef USE_RAW_INTR
		register_ipcintr(4, Xfb_intr);
#endif
		port_fb_iop = object_query("framebuf");
		if (port_fb_iop <= 0) {
			return (0);
		}
#ifndef USE_RAW_INTR
		port_fb = port_create("@port_fb", fbcint, -1);
#endif
	}
#endif /* IPC_MRX */

	fbp->fb_command = FB_CPROBE;
	fbp->fb_device = 0;
	fbp->fb_unit = unit;
	fbp->fb_data = -1;
	fbstart(fbp, 1);

	if ((fb->fbs_device = fbp->fb_data) == -1)
		return (0);
	else
		return (-1);
}

/* ARGSUSED */
fbattach(ii)
	struct iop_device *ii;
{
	register int unit = ii->ii_unit;
	register struct fb_softc *fb = &fb_softc[unit];
#if defined(IPC_MRX) && defined(mips)
	register struct fbreg *fbp =
	    (struct fbreg *)MACH_CACHED_TO_UNCACHED(&fbreg[unit]);
#else
	register struct fbreg *fbp = &fbreg[unit];
#endif

	fbp->fb_command = FB_CATTACH;
	fbp->fb_device = fb->fbs_device;
	fbstart(fbp, 1);
	fb->fbs_type = fbp->fb_scrtype;

	if (fb->fbs_type.type) {
		fb->fbs_state = 0;
		fb->fbs_flag = 0;
		printf("fb%d: %s", unit,
			(fb->fbs_type.type < sizeof(devname)/sizeof(*devname))
				? devname[fb->fbs_type.type] : "UNKNOWN");
		printf(" (%d x %d %d plane)\n",
				fb->fbs_type.visiblerect.extent.x,
				fb->fbs_type.visiblerect.extent.y,
				fb->fbs_type.plane);
	}
}

/*ARGSUSED*/
fbopen(dev, flag)
	dev_t dev;
	int flag;
{
	register int unit = FBUNIT(dev);
	register struct fb_softc *fb = &fb_softc[unit];
	register struct iop_device *ii;
#if defined(IPC_MRX) && defined(mips)
	register struct fbreg *fbp =
	    (struct fbreg *)MACH_CACHED_TO_UNCACHED(&fbreg[unit]);
#else
	register struct fbreg *fbp = &fbreg[unit];
#endif

	if (unit >= NFB || (ii = fbinfo[unit]) == 0 || ii->ii_alive == 0)
		return (ENXIO);
	if (fb->fbs_flag && !FBVIDEO(dev))
		return (EBUSY);

	if (fb->fbs_state == 0) {
		fbp->fb_device = fb->fbs_device;
		if(fbinit(fbp))
			return (EBUSY);
	}

        fb->fbs_state |= FBVIDEO(dev) ? VIDEO_USED : FB_USED;

	return (0);
}

/*ARGSUSED*/
fbclose(dev, flag)
	dev_t dev;
	int flag;
{
	register int unit = FBUNIT(dev);
	register struct fb_softc *fb = &fb_softc[unit];
	register struct iop_device *ii;
#if defined(IPC_MRX) && defined(mips)
	register struct fbreg *fbp =
	    (struct fbreg *)MACH_CACHED_TO_UNCACHED(&fbreg[unit]);
#else
	register struct fbreg *fbp = &fbreg[unit];
#endif

	if (unit >= NFB || (ii = fbinfo[unit]) == 0 || ii->ii_alive == 0)
		return (ENXIO);

	if (fb->fbs_state == 0)
		return(0);

	if(!FBVIDEO(dev))
		fb->fbs_flag = 0;

	fb->fbs_state &= ~(FBVIDEO(dev) ? VIDEO_USED : FB_USED);

	if (fb->fbs_state == 0) {
		fbp->fb_device = fb->fbs_device;
		fbreset(fbp);
	}

	return (0);
}

fbioctl(dev, cmd, data, flag)
	dev_t dev;
	caddr_t data;
{
	register int unit = FBUNIT(dev);
	register struct fb_softc *fb = &fb_softc[unit];
	register struct iop_device *ii;
	register int error = 0;
#if defined(IPC_MRX) && defined(mips)
	register struct fbreg *fbp =
	    (struct fbreg *)MACH_CACHED_TO_UNCACHED(&fbreg[unit]);
#else
	register struct fbreg *fbp = &fbreg[unit];
#endif

	if (unit >= NFB || (ii = fbinfo[unit]) == 0 || ii->ii_alive == 0)
		return (ENXIO);

	fblock();

	fbp->fb_device = fb->fbs_device;

	switch (cmd) {
	case FBIOCENABLE:
		fb->fbs_flag = 0;
		break;
	case FBIOCDISABLE:
		fb->fbs_flag = 1;
		break;
	case FBIOCAUTODIM:
		fbp->fb_command = FB_CAUTODIM;
		fbp->fb_data = *((int *)data);
		fbstart(fbp, 0);
		break;
	case FBIOCSETDIM:
		fbp->fb_command = FB_CSETDIM;
		fbp->fb_data = *((int*)data);
		fbstart(fbp, 0);
		break;
	case FBIOCGETDIM:
		fbp->fb_command = FB_CGETDIM;
		fbstart(fbp, 1);
		*((int*)data) = fbp->fb_data;
		break;
	case FBIOCBITBLT:
		error = fbbitblt(fbp, (sBitblt *)data);
		break;
	case FBIOCNBITBLT:
		error = fbnbitblt(fbp, (lBitblt *)data, UIO_USERSPACE);
		break;
	case FBIOCBATCHBITBLT:
		error = fbbatchbitblt(fbp, (sBatchBitblt*)data, UIO_USERSPACE);
		break;
	case FBIOCNBATCHBITBLT:
		error = fbnbatchbitblt(fbp, (lBatchBitblt*)data, UIO_USERSPACE);
		break;
	case FBIOCTILEBITBLT:
		error = fbtilebitblt(fbp, (sTileBitblt *)data);
		break;
	case FBIOCNTILEBITBLT:
		error = fbntilebitblt(fbp, (lTileBitblt *)data);
		break;
	case FBIOCBITBLT3:
		error = fbbitblt3(fbp, (sBitblt3 *)data);
		break;
	case FBIOCNBITBLT3:
		error = fbnbitblt3(fbp, (lBitblt3 *)data);
		break;
	case FBIOCPOLYLINE:
		error = fbpolyline(fbp, (sPrimLine *)data, 0);
		break;
	case FBIOCNPOLYLINE:
		error = fbnpolyline(fbp, (lPrimLine *)data, 0, UIO_USERSPACE);
		break;
	case FBIOCDJPOLYLINE:
		error = fbpolyline(fbp, (sPrimLine *)data, 1);
		break;
	case FBIOCNDJPOLYLINE:
		error = fbnpolyline(fbp, (lPrimLine *)data, 1, UIO_USERSPACE);
		break;
	case FBIOCPOLYMARKER:
		error = fbpolymarker(fbp, (sPrimMarker *)data);
		break;
	case FBIOCNPOLYMARKER:
		error = fbnpolymarker(fbp, (lPrimMarker *)data, UIO_USERSPACE);
		break;
	case FBIOCRECTANGLE:
		error = fbrectangle(fbp, (sPrimRect *)data);
		break;
	case FBIOCNRECTANGLE:
		error = fbnrectangle(fbp, (lPrimRect *)data);
		break;
	case FBIOCFILLSCAN:
		error = fbfillscan(fbp, (sPrimFill *)data);
		break;
	case FBIOCNFILLSCAN:
		error = fbnfillscan(fbp, (lPrimFill *)data, UIO_USERSPACE);
		break;
	case FBIOCTEXT:
		error = fbtext(fbp, (sPrimText *)data);
		break;
	case FBIOCNTEXT:
		error = fbntext(fbp, (lPrimText *)data);
		break;
	case FBIOCPOLYDOT:
		error = fbpolydot(fbp, (sPrimDot *)data);
		break;
	case FBIOCNPOLYDOT:
		error = fbnpolydot(fbp, (lPrimDot *)data, UIO_USERSPACE);
		break;

	case FBIOCGETSCRTYPE:
		fbgetscrtype(fbp, (sScrType *)data);
		break;
	case FBIOCNGETSCRTYPE:
		fbp->fb_command = FB_CGETSCRTYPE;
		fbstart(fbp, 1);
		*((lScrType*)data) = fbp->fb_scrtype;
		break;
	case FBIOCSETPALETTE:
		fbsetpalette(fbp, (sPalette *)data);
		break;
	case FBIOCNSETPALETTE:
		error = fbnsetpalette(fbp, (lPalette *)data);
		break;
	case FBIOCGETPALETTE:
		fbgetpalette(fbp, (sPalette *)data);
		break;
	case FBIOCNGETPALETTE:
		error = fbngetpalette(fbp, (lPalette *)data);
		break;
	case FBIOCSETCURSOR:
		fbsetcursor(fbp, (sCursor *)data);
		break;
	case FBIOCNSETCURSOR:
		fbnsetcursor(fbp, (lCursor *)data);
		break;
	case FBIOCNSETCURSOR2:
		fbp->fb_command = FB_CSETCURSOR;
		fbp->fb_cursor = *((lCursor2 *)data);
		fbstart(fbp, 0);
		break;
	case FBIOCUNSETCURSOR:
		fbp->fb_command = FB_CUNSETCURSOR;
		fbstart(fbp, 0);
		break;
	case FBIOCNUNSETCURSOR:
		fbp->fb_command = FB_CUNSETCURSOR;
		fbstart(fbp, 0);
		break;
	case FBIOCSHOWCURSOR:
		fbp->fb_command = FB_CSHOWCURSOR;
		fbstart(fbp, 0);
		break;
	case FBIOCNSHOWCURSOR:
		fbp->fb_command = FB_CSHOWCURSOR;
		fbstart(fbp, 0);
		break;
	case FBIOCHIDECURSOR:
		fbp->fb_command = FB_CHIDECURSOR;
		fbstart(fbp, 0);
		break;
	case FBIOCNHIDECURSOR:
		fbp->fb_command = FB_CHIDECURSOR;
		fbstart(fbp, 0);
		break;
	case FBIOCSETXY:
		fbsetxy(fbp, (sPoint *)data);
		break;
	case FBIOCNSETXY:
		fbp->fb_command = FB_CSETXY;
		fbp->fb_point = *((lPoint *)data);
		fbstart(fbp, 0);
		break;
	case FBIOCNSETPALETTEMODE:
		fbp->fb_command = FB_CSETPMODE;
		fbp->fb_data = *((int*)data);
		fbstart(fbp, 0);
		break;
	case FBIOCNGETPALETTEMODE:
		fbp->fb_command = FB_CGETPMODE;
		fbstart(fbp, 1);
		*((int*)data) = fbp->fb_data;
		break;
	case FBIOCNSETVIDEO:
		fbp->fb_command = FB_CSETVIDEO;
		fbp->fb_videoctl = *((lVideoCtl*)data);
		fbstart(fbp, 0);
		break;
	case FBIOCNGETVIDEO:
		fbp->fb_command = FB_CGETVIDEO;
		fbp->fb_videostatus.request = VIDEO_STATUS;
		fbstart(fbp, 1);
		*((lVideoStatus*)data) = fbp->fb_videostatus;
		error = fbp->fb_result;
		break;
	case FBIOCNIOCTL:
		fbp->fb_command = FB_CIOCTL;
		fbp->fb_fbioctl = *((lFbIoctl*)data);
		fbstart(fbp, 1);
		*((lFbIoctl*)data) = fbp->fb_fbioctl;
		if (fbp->fb_result == FB_RERROR)
			error = EINVAL;
		break;

	default:
		error = ENXIO;
		break;
	}

	fbunlock(error);

	return (error);
}

fbmmap(dev, off, prot)
	dev_t dev;
	off_t off;
	int prot;
{
	register int unit = FBUNIT(dev);
	register struct fb_softc *fb = &fb_softc[unit];
	register struct iop_device *ii;
	register int page;
	register struct fbreg *fbp = &fbreg[unit];

	if (unit >= NFB || (ii = fbinfo[unit]) == 0 || ii->ii_alive == 0)
		return (-1);

	fblock();
	fbp->fb_device = fb->fbs_device;
	fbp->fb_command = FB_CGETPAGE;
	fbp->fb_data = off;
	fbstart(fbp, 1);
	page = fbp->fb_data;
	if (fbp->fb_result == FB_RERROR)
		page = -1;
	else
		fb->fbs_flag = 1;
	fbunlock(fbp->fb_result);

	return (page);
}

static void
fblock()
{
	int s;

#ifdef USE_RAW_INTR
	fbwait();
#endif
	s = splfb();
	while (fbstate & FB_BUSY) {
		fbstate |= FB_WANTED;
		sleep((caddr_t)&fbstate, FBPRI);
	}
	fbstate |= FB_BUSY;
	splx(s);
}

static void
fbunlock(error)
	int error;
{
	int s = splfb();

#ifdef CPU_SINGLE
	fbstate &= ~FB_BUSY;
	if (fbstate & FB_WANTED) {
		fbstate &= ~FB_WANTED;
		wakeup((caddr_t)&fbstate);
	}
#else
#ifdef USE_RAW_INTR
	fbstate &= ~FB_BUSY;
	if (fbstate & FB_WANTED) {
		fbstate &= ~FB_WANTED;
		wakeup((caddr_t)&fbstate);
	}
#else
	if (error || (fbstate & FB_DELAY) == 0) {
		fbstate &= ~(FB_BUSY | FB_WAIT | FB_DELAY);
		if (fbstate & FB_WANTED) {
			fbstate &= ~FB_WANTED;
			wakeup((caddr_t)&fbstate);
		}
	}
	if (fbstate & FB_DELAY) {
		fbstate &= ~FB_DELAY;
		fbstate |= FB_DELAY2;
	}
#endif
#endif /* CPU_SINGLE */
	splx(s);
}

static int
fbinit(fbp)
	struct fbreg *fbp;
{
	fblock();

	fbp->fb_command = FB_COPEN;
	fbstart(fbp, 1);
	if (fbp->fb_result != FB_ROK) {
		fbunlock(0);
		return (FB_RERROR);
	}

	fbp->fb_command = FB_CUNSETCURSOR;
	fbstart(fbp, 0);

	fbunlock(0);

	return (FB_ROK);
}

static void
fbreset(fbp)
	struct fbreg *fbp;
{
	fblock();

	fbp->fb_command = FB_CUNSETCURSOR;
	fbstart(fbp, 1);

	fbp->fb_command = FB_CCLOSE;
	fbstart(fbp, 0);

	fbunlock(0);
}
#endif /* NFB */
E 1
