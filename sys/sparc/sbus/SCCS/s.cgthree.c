h18349
s 00084/00092/00243
d D 8.2 93/10/30 22:11:30 torek 7 5
c move Brooktree registers & colormap data structures to common code
c to share between cg3 and cg6 drivers.
e
s 00084/00092/00243
d R 8.2 93/10/30 22:06:28 torek 6 5
c 1.7: move Brooktree registers & colormap data structures to common code
c to share between cg3 and cg6 drivers.
e
s 00002/00002/00333
d D 8.1 93/06/11 15:14:32 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00004/00333
d D 7.4 93/04/20 19:29:00 torek 4 3
c spelling
e
s 00013/00013/00324
d D 7.3 92/10/11 12:49:45 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00332
d D 7.2 92/07/21 16:52:03 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00332/00000/00000
d D 7.1 92/07/13 00:44:02 torek 1 0
c date and time created 92/07/13 00:44:02 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: cgthree.c,v 1.5 92/06/17 06:59:31 torek Exp $
E 4
I 4
D 7
 * from: $Header: cgthree.c,v 1.6 92/11/26 02:28:06 torek Exp $
E 7
I 7
 * from: $Header: cgthree.c,v 1.8 93/10/31 05:09:24 torek Exp $
E 7
E 4
 */

/*
 * color display (cgthree) driver.
 *
 * Does not handle interrupts, even though they can occur.
I 7
 *
 * XXX should defer colormap updates to vertical retrace interrupts
E 7
 */
D 4

#include "cgthree.h"
E 4

D 3
#include "sys/param.h"
#include "sys/buf.h"
#include "sys/device.h"
#include "sys/fbio.h"
#include "sys/ioctl.h"
#include "sys/malloc.h"
#include "sys/mman.h"
#include "sys/tty.h"
E 3
I 3
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/device.h>
#include <sys/fbio.h>
#include <sys/ioctl.h>
#include <sys/malloc.h>
#include <sys/mman.h>
#include <sys/tty.h>
E 3

D 3
#include "machine/autoconf.h"
#include "machine/pmap.h"
#include "machine/fbvar.h"
E 3
I 3
#include <machine/autoconf.h>
#include <machine/pmap.h>
#include <machine/fbvar.h>
E 3

I 7
#include <sparc/sbus/btreg.h>
#include <sparc/sbus/btvar.h>
E 7
D 3
#include "cgthreereg.h"
#include "sbusvar.h"
E 3
I 3
#include <sparc/sbus/cgthreereg.h>
#include <sparc/sbus/sbusvar.h>
E 3

D 7
union colormap {
	u_char	cm_map[256][3];		/* 256 R/G/B entries */
	u_int	cm_chip[256 * 3 / 4];	/* the way the chip gets loaded */
};

E 7
/* per-display variables */
struct cgthree_softc {
	struct	device sc_dev;		/* base device */
	struct	sbusdev sc_sd;		/* sbus device */
	struct	fbdevice sc_fb;		/* frame buffer device */
D 7
	volatile struct cgthreereg *sc_reg;/* control registers */
E 7
I 7
	volatile struct bt_regs *sc_bt;	/* Brooktree registers */
E 7
	caddr_t	sc_phys;		/* display RAM (phys addr) */
	int	sc_blanked;		/* true if blanked */
D 7
	union	colormap sc_cmap;	/* current color map */
E 7
I 7
	union	bt_cmap sc_cmap;	/* Brooktree color map */
E 7
};

/* autoconfiguration driver */
static void	cgthreeattach(struct device *, struct device *, void *);
struct cfdriver cgthreecd =
    { NULL, "cgthree", matchbyname, cgthreeattach,
      DV_DULL, sizeof(struct cgthree_softc) };

D 7
/*
 * XXX we do not handle frame buffer interrupts (do not know how) ... we
 * need these to do color map loading at vertical retrace time!
 */

E 7
/* frame buffer generic driver */
static void	cgthreeunblank(struct device *);
static struct fbdriver cgthreefbdriver = { cgthreeunblank };

extern int fbnode;
extern struct tty *fbconstty;
extern int (*v_putc)();
extern int nullop();
static int cgthree_cnputc();
D 7
#ifdef notdef
static struct cgthree_softc *bwcons;
#endif
E 7

I 7
static void cgthreeloadcmap __P((struct cgthree_softc *, int, int));

E 7
#define	CGTHREE_MAJOR	55		/* XXX */

/*
 * Attach a display.  We need to notice if it is the console, too.
 */
void
cgthreeattach(parent, self, args)
	struct device *parent, *self;
	void *args;
{
	register struct cgthree_softc *sc = (struct cgthree_softc *)self;
	register struct sbus_attach_args *sa = args;
	register int node = sa->sa_ra.ra_node, ramsize, i;
D 7
	register volatile struct cgthreereg *cg3;
E 7
I 7
	register volatile struct bt_regs *bt;
E 7
	register struct cgthree_all *p;
	int isconsole;

	sc->sc_fb.fb_major = CGTHREE_MAJOR;	/* XXX to be removed */

	sc->sc_fb.fb_driver = &cgthreefbdriver;
	sc->sc_fb.fb_device = &sc->sc_dev;
	/*
	 * The defaults below match my screen, but are not guaranteed
	 * to be correct as defaults go...
	 */
	sc->sc_fb.fb_type.fb_type = FBTYPE_SUN3COLOR;
	sc->sc_fb.fb_type.fb_width = getpropint(node, "width", 1152);
	sc->sc_fb.fb_type.fb_height = getpropint(node, "height", 900);
	sc->sc_fb.fb_linebytes = getpropint(node, "linebytes", 1152);
	ramsize = sc->sc_fb.fb_type.fb_height * sc->sc_fb.fb_linebytes;
	sc->sc_fb.fb_type.fb_depth = 8;
	sc->sc_fb.fb_type.fb_cmsize = 256;
	sc->sc_fb.fb_type.fb_size = ramsize;
	printf(": %s, %d x %d", getpropstring(node, "model"),
	    sc->sc_fb.fb_type.fb_width, sc->sc_fb.fb_type.fb_height);

	/*
	 * When the ROM has mapped in a cgthree display, the address
	 * maps only the video RAM, so in any case we have to map the
	 * registers ourselves.  We only need the video RAM if we are
	 * going to print characters via rconsole.
	 */
	isconsole = node == fbnode && fbconstty != NULL;
	p = (struct cgthree_all *)sa->sa_ra.ra_paddr;
	if ((sc->sc_fb.fb_pixels = sa->sa_ra.ra_vaddr) == NULL && isconsole) {
		/* this probably cannot happen, but what the heck */
		sc->sc_fb.fb_pixels = mapiodev(p->ba_ram, ramsize);
	}
D 7
	sc->sc_reg = cg3 = (volatile struct cgthreereg *)
	    mapiodev((caddr_t)&p->ba_reg, sizeof(p->ba_reg));
E 7
I 7
	sc->sc_bt = bt = (volatile struct bt_regs *)
	    mapiodev((caddr_t)&p->ba_btreg, sizeof(p->ba_btreg));
E 7
	sc->sc_phys = p->ba_ram;

D 7
	/* grab initial (current) color map, then set video */
	cg3->cg3_addr = 0;
E 7
I 7
	/* grab initial (current) color map */
	bt->bt_addr = 0;
E 7
	for (i = 0; i < 256 * 3 / 4; i++)
D 7
		sc->sc_cmap.cm_chip[i] = cg3->cg3_cmap;
	cgthreeunblank(&sc->sc_dev);
E 7
I 7
		sc->sc_cmap.cm_chip[i] = bt->bt_cmap;
	/* make sure we are not blanked (see cgthreeunblank) */
	bt->bt_addr = 0x06;		/* command reg */
	bt->bt_ctrl = 0x73;		/* overlay plane */
	bt->bt_addr = 0x04;		/* read mask */
	bt->bt_ctrl = 0xff;		/* color planes */
E 7

	if (isconsole) {
		printf(" (console)\n");
#ifdef RCONSOLE
		rcons_init(&sc->sc_fb);
#endif
	} else
		printf("\n");
	sbus_establish(&sc->sc_sd, &sc->sc_dev);
	if (node == fbnode)
		fb_attach(&sc->sc_fb);
}

int
cgthreeopen(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{
	int unit = minor(dev);

	if (unit >= cgthreecd.cd_ndevs || cgthreecd.cd_devs[unit] == NULL)
		return (ENXIO);
	return (0);
}

int
cgthreeclose(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{

	return (0);
}

int
cgthreeioctl(dev, cmd, data, flags, p)
	dev_t dev;
	int cmd;
D 7
	caddr_t data;
E 7
I 7
	register caddr_t data;
E 7
	int flags;
	struct proc *p;
{
	register struct cgthree_softc *sc = cgthreecd.cd_devs[minor(dev)];
	register struct fbgattr *fba;
I 7
	int error;
E 7

	switch (cmd) {

	case FBIOGTYPE:
		*(struct fbtype *)data = sc->sc_fb.fb_type;
		break;

	case FBIOGATTR:
		fba = (struct fbgattr *)data;
		fba->real_type = sc->sc_fb.fb_type.fb_type;
		fba->owner = 0;		/* XXX ??? */
		fba->fbtype = sc->sc_fb.fb_type;
		fba->sattr.flags = 0;
		fba->sattr.emu_type = sc->sc_fb.fb_type.fb_type;
		fba->sattr.dev_specific[0] = -1;
		fba->emu_types[0] = sc->sc_fb.fb_type.fb_type;
		fba->emu_types[1] = -1;
		break;

D 7
	case FBIOGETCMAP: {
		register struct fbcmap *p = (struct fbcmap *)data;
		register int i, color, count, error;
		register u_char *cp;
E 7
I 7
	case FBIOGETCMAP:
		return (bt_getcmap((struct fbcmap *)data, &sc->sc_cmap, 256));
E 7

D 7
		/* get color map from software copy */
		if ((unsigned)(color = p->index) >= 256 ||
		    (unsigned)(count = p->count) > 256 - color)
			return (EINVAL);
		if (!useracc(p->red, count, B_WRITE) ||
		    !useracc(p->green, count, B_WRITE) ||
		    !useracc(p->blue, count, B_WRITE))
			return (EFAULT);
		cp = &sc->sc_cmap.cm_map[color][0];
		for (i = 0; i < count; cp += 3, i++) {
			p->red[i] = cp[0];
			p->green[i] = cp[1];
			p->blue[i] = cp[2];
		}
	}
		break;

	case FBIOPUTCMAP: {
		register struct fbcmap *p = (struct fbcmap *)data;
		register int i, color, count, error;
		register u_char *cp;
		register u_int *ip;

		/* update software copy */
		if ((unsigned)(color = p->index) >= 256 ||
		    (unsigned)(count = p->count) > 256 - color)
			return (EINVAL);
		if (!useracc(p->red, count, B_READ) ||
		    !useracc(p->green, count, B_READ) ||
		    !useracc(p->blue, count, B_READ))
			return (EFAULT);
		cp = &sc->sc_cmap.cm_map[color][0];
		for (i = 0; i < count; cp += 3, i++) {
			cp[0] = p->red[i];
			cp[1] = p->green[i];
			cp[2] = p->blue[i];
		}
		/* then blast them into the chip */
E 7
I 7
	case FBIOPUTCMAP:
		/* copy to software map */
#define p ((struct fbcmap *)data)
		error = bt_putcmap(p, &sc->sc_cmap, 256);
		if (error)
			return (error);
		/* now blast them into the chip */
E 7
		/* XXX should use retrace interrupt */
D 7
#define	D4M3(x)	((((x) >> 2) << 1) + ((x) >> 2))	/* (x / 4) * 3 */
#define	D4M4(x)	((x) & ~3)				/* (x / 4) * 4 */
		ip = &sc->sc_cmap.cm_chip[D4M3(color)];
		count = D4M3(color + count - 1) - D4M3(color) + 3;
		sc->sc_reg->cg3_addr = D4M4(color);
		while (--count >= 0)
			sc->sc_reg->cg3_cmap = *ip++;
	}
E 7
I 7
		cgthreeloadcmap(sc, p->index, p->count);
#undef p
E 7
		break;

	case FBIOGVIDEO:
		*(int *)data = sc->sc_blanked;
		break;

	case FBIOSVIDEO:
		if (*(int *)data)
			cgthreeunblank(&sc->sc_dev);
D 7
		else {
			register volatile struct cgthreereg *cg3 = sc->sc_reg;
E 7
I 7
		else if (!sc->sc_blanked) {
			register volatile struct bt_regs *bt;
E 7

I 7
			bt = sc->sc_bt;
			bt->bt_addr = 0x06;	/* command reg */
			bt->bt_ctrl = 0x70;	/* overlay plane */
			bt->bt_addr = 0x04;	/* read mask */
			bt->bt_ctrl = 0x00;	/* color planes */
			/*
			 * Set color 0 to black -- note that this overwrites
			 * R of color 1.
			 */
			bt->bt_addr = 0;
			bt->bt_cmap = 0;

E 7
			sc->sc_blanked = 1;
D 7
			cg3->cg3_addr = 0x06;	/* command reg */
			cg3->cg3_ctrl = 0x70;	/* overlay plane */
			cg3->cg3_addr = 0x04;	/* read mask */
			cg3->cg3_ctrl = 0x00;	/* color planes */
			/* set color 0 to black; scribble on R of color 1 */
			cg3->cg3_addr = 0;
			cg3->cg3_cmap = 0;
E 7
		}
		break;

	default:
		return (ENOTTY);
	}
	return (0);
}

I 7
/*
 * Undo the effect of an FBIOSVIDEO that turns the video off.
 */
E 7
static void
cgthreeunblank(dev)
	struct device *dev;
{
	struct cgthree_softc *sc = (struct cgthree_softc *)dev;
D 7
	register volatile struct cgthreereg *cg3 = sc->sc_reg;
E 7
I 7
	register volatile struct bt_regs *bt;
E 7

D 7
	sc->sc_blanked = 0;
	cg3->cg3_addr = 0x06;	/* command reg */
	cg3->cg3_ctrl = 0x73;	/* overlay plane */
	cg3->cg3_addr = 0x04;	/* read mask */
	cg3->cg3_ctrl = 0xff;	/* color planes */
	/* restore color 0 and R of color 1 */
	cg3->cg3_addr = 0;
	cg3->cg3_cmap = sc->sc_cmap.cm_chip[0];
E 7
I 7
	if (sc->sc_blanked) {
		sc->sc_blanked = 0;
		bt = sc->sc_bt;
		/* restore color 0 (and R of color 1) */
		bt->bt_addr = 0;
		bt->bt_cmap = sc->sc_cmap.cm_chip[0];

		/* restore read mask */
		bt->bt_addr = 0x06;	/* command reg */
		bt->bt_ctrl = 0x73;	/* overlay plane */
		bt->bt_addr = 0x04;	/* read mask */
		bt->bt_ctrl = 0xff;	/* color planes */
	}
}

/*
 * Load a subset of the current (new) colormap into the Brooktree DAC.
 */
static void
cgthreeloadcmap(sc, start, ncolors)
	register struct cgthree_softc *sc;
	register int start, ncolors;
{
	register volatile struct bt_regs *bt;
	register u_int *ip;
	register int count;

	ip = &sc->sc_cmap.cm_chip[BT_D4M3(start)];	/* start/4 * 3 */
	count = BT_D4M3(start + ncolors - 1) - BT_D4M3(start) + 3;
	bt = sc->sc_bt;
	bt->bt_addr = BT_D4M4(start);
	while (--count >= 0)
		bt->bt_cmap = *ip++;
E 7
}

/*
 * Return the address that would map the given device at the given
 * offset, allowing for the given protection, or return -1 for error.
 *
 * The cg3 is mapped starting at 256KB, for pseudo-compatibility with
 * the cg4 (which had an overlay plane in the first 128K and an enable
 * plane in the next 128K).  X11 uses only 256k+ region but tries to
 * map the whole thing, so we repeatedly map the first 256K to the
 * first page of the color screen.  If someone tries to use the overlay
 * and enable regions, they will get a surprise....
 */
int
cgthreemap(dev, off, prot)
	dev_t dev;
	int off, prot;
{
	register struct cgthree_softc *sc = cgthreecd.cd_devs[minor(dev)];
#define	START	(128*1024 + 128*1024)

	if (off & PGOFSET)
		panic("cgthreemap");
	if ((unsigned)off < START)
		off = 0;
	else
		off -= START;
	if ((unsigned)off >= sc->sc_fb.fb_type.fb_size)
		return (-1);
	/*
	 * I turned on PMAP_NC here to disable the cache as I was
	 * getting horribly broken behaviour with it on.
	 */
	return ((int)sc->sc_phys + off + PMAP_OBIO + PMAP_NC);
}
E 1
