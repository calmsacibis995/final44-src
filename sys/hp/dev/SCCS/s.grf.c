h04474
s 00004/00002/00644
d D 8.5 95/01/09 17:38:49 cgd 21 20
c strategy returns void, ioctl cmd is u_long
e
s 00001/00003/00645
d D 8.4 94/01/12 16:37:45 hibler 20 19
c lint
e
s 00006/00000/00642
d D 8.3 94/01/12 10:00:42 bostic 19 18
c lint
e
s 00137/00132/00505
d D 8.2 93/09/09 14:44:57 hibler 18 17
c rearranging and add support for GRFDESCRIBE
e
s 00002/00002/00635
d D 8.1 93/06/10 21:23:26 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00635
d D 7.16 93/03/09 10:53:35 hibler 16 15
c additional parameter to vm_mmap
e
s 00002/00002/00634
d D 7.15 92/12/27 09:10:44 hibler 15 14
c SHPUX moved to MD flags
e
s 00001/00001/00635
d D 7.14 92/10/11 08:55:06 bostic 14 13
c make kernel includes standard
e
s 00019/00019/00617
d D 7.13 92/07/12 16:18:16 mckusick 13 12
c new include syntax
e
s 00001/00001/00635
d D 7.12 92/06/23 17:13:43 mckusick 12 11
c MAP_FILE is now the default
e
s 00012/00129/00624
d D 7.11 92/06/05 15:23:10 hibler 11 10
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00752
d D 7.10 92/05/14 15:24:34 heideman 10 9
c include reordering due to vn_if change
e
s 00001/00001/00752
d D 7.9 92/05/04 16:00:17 mckusick 9 8
c lint inspired bug fix
e
s 00022/00021/00731
d D 7.8 91/05/07 09:49:33 hibler 8 7
c update from utah, DIO-II support
e
s 00040/00039/00712
d D 7.7 91/05/04 19:49:09 karels 7 6
c update to current include, device calling conventions
e
s 00015/00015/00736
d D 7.6 90/12/16 16:35:46 bostic 6 5
c kernel reorg
e
s 00043/00143/00708
d D 7.5 90/12/05 18:26:24 mckusick 5 4
c update from Mike Hibler for new VM and other machine support
e
s 00034/00031/00817
d D 7.4 90/06/22 09:26:04 hibler 4 3
c get rid of u_error uses
e
s 00026/00024/00822
d D 7.3 90/06/20 11:06:32 mckusick 3 2
c update for new structure
e
s 00008/00000/00838
d D 7.2 90/05/25 15:43:51 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00838/00000/00000
d D 7.1 90/05/08 22:06:54 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 17
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 8
 * from: Utah $Hdr: grf.c 1.28 89/08/14$
E 8
I 8
D 11
 * from: Utah $Hdr: grf.c 1.31 91/01/21$
E 11
I 11
D 18
 * from: Utah $Hdr: grf.c 1.32 92/01/21$
E 18
I 18
 * from: Utah $Hdr: grf.c 1.36 93/08/13$
E 18
E 11
E 8
 *
 *	%W% (Berkeley) %G%
 */

/*
D 11
 * Graphics display driver for the HP300.
E 11
I 11
 * Graphics display driver for HP 300/400/700/800 machines.
E 11
 * This is the hardware-independent portion of the driver.
D 11
 * Hardware access is through the grfdev routines below.
E 11
I 11
 * Hardware access is through the machine dependent grf switch routines.
E 11
 */

D 13
#include "grf.h"
E 13
I 13
D 14
#include <grf.h>
E 14
I 14
#include "grf.h"
E 14
E 13
#if NGRF > 0

D 6
#include "param.h"
#include "user.h"
#include "proc.h"
#include "ioctl.h"
#include "file.h"
D 5
#include "mapmem.h"
E 5
#include "malloc.h"
E 6
I 6
D 7
#include "sys/param.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/ioctl.h"
#include "sys/file.h"
#include "sys/malloc.h"
E 7
I 7
D 13
#include "param.h"
#include "proc.h"
#include "ioctl.h"
#include "file.h"
#include "malloc.h"
E 13
I 13
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/malloc.h>
#include <sys/vnode.h>
#include <sys/mman.h>
E 13
E 7
E 6

D 11
#include "device.h"
E 11
D 13
#include "grfioctl.h"
#include "grfvar.h"
I 11
#include "grfreg.h"
E 13
I 13
#include <hp/dev/grfioctl.h>
#include <hp/dev/grfvar.h>
#include <hp/dev/grfreg.h>
E 13
E 11

D 6
#include "machine/cpu.h"
E 6
I 6
D 7
#include "../include/cpu.h"
E 7
I 7
D 13
#include "machine/cpu.h"
E 13
I 13
#include <machine/cpu.h>
E 13
E 7
E 6

#ifdef HPUXCOMPAT
D 13
#include "../hpux/hpux.h"
E 13
I 13
#include <hp/hpux/hpux.h>
E 13
#endif

I 5
D 6
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_kern.h"
#include "../vm/vm_page.h"
#include "../vm/vm_pager.h"
#include "specdev.h"
#include "vnode.h"
#include "mman.h"
E 6
I 6
D 7
#include "vm/vm_param.h"
#include "vm/vm_map.h"
E 7
I 7
D 13
#include "vm/vm.h"
E 7
#include "vm/vm_kern.h"
#include "vm/vm_page.h"
#include "vm/vm_pager.h"
E 13
I 13
#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_page.h>
#include <vm/vm_pager.h>
E 13
D 7
#include "sys/specdev.h"
#include "sys/vnode.h"
#include "sys/mman.h"
E 7
E 6

I 7
D 10
#include "specdev.h"
E 10
D 13
#include "vnode.h"
I 10
#include "specdev.h"
E 10
#include "mman.h"
E 13
I 13
#include <miscfs/specfs/specdev.h>
E 13

E 7
E 5
D 13
#include "ite.h"
E 13
I 13
#include <ite.h>
E 13
#if NITE == 0
#define	iteon(u,f)
#define	iteoff(u,f)
#endif

D 11
int	grfprobe();
int	tc_init(), tc_mode();
int	gb_init(), gb_mode();
int	rb_init(), rb_mode();
int	dv_init(), dv_mode();

struct grfdev grfdev[] = {
	GID_TOPCAT,	GRFBOBCAT,	tc_init,	tc_mode,
	"topcat",
	GID_GATORBOX,	GRFGATOR,	gb_init,	gb_mode,
	"gatorbox",
	GID_RENAISSANCE,GRFRBOX,	rb_init,	rb_mode,
	"renaissance",
	GID_LRCATSEYE,	GRFCATSEYE,	tc_init,	tc_mode,
	"lo-res catseye",
	GID_HRCCATSEYE,	GRFCATSEYE,	tc_init,	tc_mode,
	"hi-res catseye",
	GID_HRMCATSEYE,	GRFCATSEYE,	tc_init,	tc_mode,
	"hi-res catseye",
	GID_DAVINCI,    GRFDAVINCI,	dv_init,	dv_mode,
	"davinci",
};
int	ngrfdev = sizeof(grfdev) / sizeof(grfdev[0]);

struct	driver grfdriver = { grfprobe, "grf" };
E 11
struct	grf_softc grf_softc[NGRF];

D 5
#ifdef MAPMEM
int grfexit();
struct mapmemops grfops = { (int (*)())0, (int (*)())0, grfexit, grfexit };
#ifdef HPUXCOMPAT
struct mapmemops grflckops = { (int (*)())0, (int (*)())0, grfexit, grfexit };
struct mapmemops grfiomops = { (int (*)())0, (int (*)())0, grfexit, grfexit };
#endif
#endif

E 5
#ifdef DEBUG
int grfdebug = 0;
#define GDB_DEVNO	0x01
#define GDB_MMAP	0x02
#define GDB_IOMAP	0x04
#define GDB_LOCK	0x08
#endif

D 11
/*
 * XXX: called from ite console init routine.
 * Does just what configure will do later but without printing anything.
 */
grfconfig()
{
	register caddr_t addr;
	register struct hp_hw *hw;
	register struct hp_device *hd, *nhd;

	for (hw = sc_table; hw->hw_type; hw++) {
D 8
	        if (hw->hw_type != BITMAP)
E 8
I 8
	        if (!HW_ISDEV(hw, D_BITMAP))
E 8
			continue;
		/*
		 * Found one, now match up with a logical unit number
		 */
		nhd = NULL;		
D 8
		addr = hw->hw_addr;
E 8
I 8
		addr = hw->hw_kva;
E 8
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
D 8
			if ((caddr_t)sctoaddr(hd->hp_addr) == addr) {
E 8
I 8
			if (sctova(hd->hp_addr) == addr) {
E 8
				nhd = hd;
				break;
			}
		}
		/*
		 * Found a match, initialize
		 */
D 8
		if (nhd && grfinit(addr, nhd->hp_unit)) {
E 8
I 8
		if (nhd && grfinit(addr, nhd->hp_unit))
E 8
			nhd->hp_addr = addr;
D 8
		}
E 8
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
	printf(" %s display\n", grfdev[gp->g_type].gd_desc);
	return(1);
}

grfinit(addr, unit)
	caddr_t addr;
{
	struct grf_softc *gp = &grf_softc[unit];
	struct grfreg *gr;
	register struct grfdev *gd;

	gr = (struct grfreg *) addr;
	if (gr->gr_id != GRFHWID)
		return(0);
	for (gd = grfdev; gd < &grfdev[ngrfdev]; gd++)
		if (gd->gd_hardid == gr->gr_id2)
			break;
	if (gd < &grfdev[ngrfdev] && (*gd->gd_init)(gp, addr)) {
		gp->g_display.gd_id = gd->gd_softid;
		gp->g_type = gd - grfdev;
		gp->g_flags = GF_ALIVE;
		return(1);
	}
	return(0);
}

E 11
/*ARGSUSED*/
grfopen(dev, flags)
	dev_t dev;
I 19
	int flags;
E 19
{
	int unit = GRFUNIT(dev);
	register struct grf_softc *gp = &grf_softc[unit];
	int error = 0;

	if (unit >= NGRF || (gp->g_flags & GF_ALIVE) == 0)
		return(ENXIO);
	if ((gp->g_flags & (GF_OPEN|GF_EXCLUDE)) == (GF_OPEN|GF_EXCLUDE))
		return(EBUSY);
#ifdef HPUXCOMPAT
	/*
	 * XXX: cannot handle both HPUX and BSD processes at the same time
	 */
D 7
	if (u.u_procp->p_flag & SHPUX)
E 7
I 7
D 15
	if (curproc->p_flag & SHPUX)
E 15
I 15
	if (curproc->p_md.md_flags & MDP_HPUX)
E 15
E 7
		if (gp->g_flags & GF_BSDOPEN)
			return(EBUSY);
		else
			gp->g_flags |= GF_HPUXOPEN;
	else
		if (gp->g_flags & GF_HPUXOPEN)
			return(EBUSY);
		else
			gp->g_flags |= GF_BSDOPEN;
#endif
	/*
	 * First open.
	 * XXX: always put in graphics mode.
	 */
	error = 0;
	if ((gp->g_flags & GF_OPEN) == 0) {
		gp->g_flags |= GF_OPEN;
		error = grfon(dev);
	}
	return(error);
}

/*ARGSUSED*/
grfclose(dev, flags)
	dev_t dev;
I 19
	int flags;
E 19
{
	register struct grf_softc *gp = &grf_softc[GRFUNIT(dev)];

	(void) grfoff(dev);
I 18
#ifdef HPUXCOMPAT
E 18
	(void) grfunlock(gp);
I 18
#endif
E 18
	gp->g_flags &= GF_ALIVE;
	return(0);
}

/*ARGSUSED*/
D 7
grfioctl(dev, cmd, data, flag)
E 7
I 7
grfioctl(dev, cmd, data, flag, p)
E 7
	dev_t dev;
I 19
D 21
	int cmd, flag;
E 21
I 21
	u_long cmd;
E 21
E 19
	caddr_t data;
I 21
	int flag;
E 21
I 7
	struct proc *p;
E 7
{
	register struct grf_softc *gp = &grf_softc[GRFUNIT(dev)];
	int error;

#ifdef HPUXCOMPAT
D 7
	if (u.u_procp->p_flag & SHPUX)
		return(hpuxgrfioctl(dev, cmd, data, flag));
E 7
I 7
D 15
	if (p->p_flag & SHPUX)
E 15
I 15
	if (p->p_md.md_flags & MDP_HPUX)
E 15
		return(hpuxgrfioctl(dev, cmd, data, flag, p));
E 7
#endif
	error = 0;
	switch (cmd) {

D 11
	/* XXX: compatibility hack */
	case OGRFIOCGINFO:
		bcopy((caddr_t)&gp->g_display, data, sizeof(struct ogrfinfo));
		break;

E 11
	case GRFIOCGINFO:
		bcopy((caddr_t)&gp->g_display, data, sizeof(struct grfinfo));
		break;

	case GRFIOCON:
		error = grfon(dev);
		break;

	case GRFIOCOFF:
		error = grfoff(dev);
		break;

D 5
#ifdef MAPMEM
E 5
	case GRFIOCMAP:
D 7
		error = grfmmap(dev, (caddr_t *)data);
E 7
I 7
		error = grfmmap(dev, (caddr_t *)data, p);
E 7
		break;

	case GRFIOCUNMAP:
D 7
		error = grfunmmap(dev, *(caddr_t *)data);
E 7
I 7
		error = grfunmmap(dev, *(caddr_t *)data, p);
E 7
		break;
D 5
#endif
E 5

	default:
		error = EINVAL;
		break;

	}
	return(error);
}

/*ARGSUSED*/
grfselect(dev, rw)
	dev_t dev;
I 19
	int rw;
E 19
{
	if (rw == FREAD)
		return(0);
	return(1);
}

D 18
grflock(gp, block)
	register struct grf_softc *gp;
	int block;
E 18
I 18
/*ARGSUSED*/
grfmap(dev, off, prot)
	dev_t dev;
I 19
	int off, prot;
E 19
E 18
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
I 7
D 18
	struct proc *p = curproc;		/* XXX */
E 7
E 3
I 2
	int error;
	extern char devioc[];

E 2
#ifdef DEBUG
	if (grfdebug & GDB_LOCK)
		printf("grflock(%d): dev %x flags %x lockpid %x\n",
D 3
		       u.u_procp->p_pid, gp-grf_softc, gp->g_flags,
E 3
I 3
		       p->p_pid, gp-grf_softc, gp->g_flags,
E 3
		       gp->g_lockp ? gp->g_lockp->p_pid : -1);
#endif
#ifdef HPUXCOMPAT
	if (gp->g_pid) {
#ifdef DEBUG
		if (grfdebug & GDB_LOCK)
D 8
			printf("  lock[0] %d lockslot %d lock[lockslot] %d\n",
			       gp->g_locks[0], gp->g_lockpslot,
			       gp->g_locks[gp->g_lockpslot]);
E 8
I 8
			printf(" lockpslot %d lockslot %d lock[lockslot] %d\n",
			       gp->g_lock->gl_lockslot, gp->g_lockpslot,
			       gp->g_lock->gl_locks[gp->g_lockpslot]);
E 8
#endif
D 8
		gp->g_locks[0] = 0;
		if (gp->g_locks[gp->g_lockpslot] == 0) {
E 8
I 8
		gp->g_lock->gl_lockslot = 0;
		if (gp->g_lock->gl_locks[gp->g_lockpslot] == 0) {
E 8
			gp->g_lockp = NULL;
			gp->g_lockpslot = 0;
		}
	}
#endif
	if (gp->g_lockp) {
D 3
		if (gp->g_lockp == u.u_procp)
E 3
I 3
		if (gp->g_lockp == p)
E 3
			return(EBUSY);
		if (!block)
			return(EAGAIN);
		do {
			gp->g_flags |= GF_WANTED;
D 4
			sleep((caddr_t)&gp->g_flags, PZERO+1);
I 2

E 4
			if (error = tsleep((caddr_t)&gp->g_flags,
					   (PZERO+1) | PCATCH, devioc, 0))
				return (error);
D 4

E 4
E 2
		} while (gp->g_lockp);
	}
D 3
	gp->g_lockp = u.u_procp;
E 3
I 3
	gp->g_lockp = p;
E 3
#ifdef HPUXCOMPAT
	if (gp->g_pid) {
		int slot = grffindpid(gp);
#ifdef DEBUG
		if (grfdebug & GDB_LOCK)
			printf("  slot %d\n", slot);
#endif
D 8
		gp->g_lockpslot = gp->g_locks[0] = slot;
		gp->g_locks[slot] = 1;
E 8
I 8
		gp->g_lockpslot = gp->g_lock->gl_lockslot = slot;
		gp->g_lock->gl_locks[slot] = 1;
E 8
	}
#endif
	return(0);
E 18
I 18
	return(grfaddr(&grf_softc[GRFUNIT(dev)], off));
E 18
}

D 18
grfunlock(gp)
	register struct grf_softc *gp;
E 18
I 18
grfon(dev)
	dev_t dev;
E 18
{
D 18
#ifdef DEBUG
	if (grfdebug & GDB_LOCK)
		printf("grfunlock(%d): dev %x flags %x lockpid %d\n",
D 7
		       u.u_procp->p_pid, gp-grf_softc, gp->g_flags,
E 7
I 7
		       curproc->p_pid, gp-grf_softc, gp->g_flags,
E 7
		       gp->g_lockp ? gp->g_lockp->p_pid : -1);
#endif
D 7
	if (gp->g_lockp != u.u_procp)
E 7
I 7
	if (gp->g_lockp != curproc)
E 7
		return(EBUSY);
#ifdef HPUXCOMPAT
	if (gp->g_pid) {
#ifdef DEBUG
		if (grfdebug & GDB_LOCK)
D 8
			printf("  lock[0] %d lockslot %d lock[lockslot] %d\n",
			       gp->g_locks[0], gp->g_lockpslot,
			       gp->g_locks[gp->g_lockpslot]);
E 8
I 8
			printf(" lockpslot %d lockslot %d lock[lockslot] %d\n",
			       gp->g_lock->gl_lockslot, gp->g_lockpslot,
			       gp->g_lock->gl_locks[gp->g_lockpslot]);
E 8
#endif
D 8
		gp->g_locks[gp->g_lockpslot] = gp->g_locks[0] = 0;
		gp->g_lockpslot = 0;
E 8
I 8
		gp->g_lock->gl_locks[gp->g_lockpslot] = 0;
		gp->g_lockpslot = gp->g_lock->gl_lockslot = 0;
E 8
	}
#endif
	if (gp->g_flags & GF_WANTED) {
		wakeup((caddr_t)&gp->g_flags); 
		gp->g_flags &= ~GF_WANTED;
	}
	gp->g_lockp = NULL;
	return(0);
E 18
I 18
	int unit = GRFUNIT(dev);
	struct grf_softc *gp = &grf_softc[unit];

	/*
	 * XXX: iteoff call relies on devices being in same order
	 * as ITEs and the fact that iteoff only uses the minor part
	 * of the dev arg.
	 */
	iteoff(unit, 3);
	return((*gp->g_sw->gd_mode)(gp,
				    (dev&GRFOVDEV) ? GM_GRFOVON : GM_GRFON,
				    (caddr_t)0));
E 18
}

D 18
/*ARGSUSED*/
grfmap(dev, off, prot)
E 18
I 18
grfoff(dev)
E 18
	dev_t dev;
{
D 18
	return(grfaddr(&grf_softc[GRFUNIT(dev)], off));
E 18
I 18
	int unit = GRFUNIT(dev);
	struct grf_softc *gp = &grf_softc[unit];
	int error;

	(void) grfunmmap(dev, (caddr_t)0, curproc);
	error = (*gp->g_sw->gd_mode)(gp,
				     (dev&GRFOVDEV) ? GM_GRFOVOFF : GM_GRFOFF,
				     (caddr_t)0);
	/* XXX: see comment for iteoff above */
	iteon(unit, 2);
	return(error);
E 18
}

I 18
grfaddr(gp, off)
	struct grf_softc *gp;
	register int off;
{
	register struct grfinfo *gi = &gp->g_display;

	/* control registers */
	if (off >= 0 && off < gi->gd_regsize)
		return(((u_int)gi->gd_regaddr + off) >> PGSHIFT);

	/* frame buffer */
	if (off >= gi->gd_regsize && off < gi->gd_regsize+gi->gd_fbsize) {
		off -= gi->gd_regsize;
		return(((u_int)gi->gd_fbaddr + off) >> PGSHIFT);
	}
	/* bogus */
	return(-1);
}

/*
 * HP-UX compatibility routines
 */
E 18
#ifdef HPUXCOMPAT

/*ARGSUSED*/
D 7
hpuxgrfioctl(dev, cmd, data, flag)
E 7
I 7
hpuxgrfioctl(dev, cmd, data, flag, p)
E 7
	dev_t dev;
I 19
D 21
	int cmd, flag;
E 21
I 21
	u_long cmd;
E 21
E 19
	caddr_t data;
I 21
	int flag;
E 21
I 7
	struct proc *p;
E 7
{
	register struct grf_softc *gp = &grf_softc[GRFUNIT(dev)];
	int error;

	error = 0;
	switch (cmd) {

	case GCID:
		*(int *)data = gp->g_display.gd_id;
		break;

	case GCON:
		error = grfon(dev);
		break;

	case GCOFF:
		error = grfoff(dev);
		break;

	case GCLOCK:
		error = grflock(gp, 1);
		break;

	case GCUNLOCK:
		error = grfunlock(gp);
		break;

	case GCAON:
	case GCAOFF:
		break;

	/* GCSTATIC is implied by our implementation */
	case GCSTATIC_CMAP:
	case GCVARIABLE_CMAP:
		break;

D 5
#ifdef MAPMEM
E 5
	/* map in control regs and frame buffer */
	case GCMAP:
D 7
		error = grfmmap(dev, (caddr_t *)data);
E 7
I 7
		error = grfmmap(dev, (caddr_t *)data, p);
E 7
		break;

	case GCUNMAP:
D 7
		error = grfunmmap(dev, *(caddr_t *)data);
E 7
I 7
		error = grfunmmap(dev, *(caddr_t *)data, p);
E 7
		/* XXX: HP-UX uses GCUNMAP to get rid of GCSLOT memory */
		if (error)
			error = grflckunmmap(dev, *(caddr_t *)data);
		break;

	case GCSLOT:
	{
		struct grf_slot *sp = (struct grf_slot *)data;

		sp->slot = grffindpid(gp);
D 5
		if (sp->slot)
E 5
I 5
		if (sp->slot) {
E 5
			error = grflckmmap(dev, (caddr_t *)&sp->addr);
D 5
		else
E 5
I 5
			if (error && gp->g_pid) {
				free((caddr_t)gp->g_pid, M_DEVBUF);
				gp->g_pid = NULL;
			}
		} else
E 5
			error = EINVAL;		/* XXX */
		break;
	}

I 18
	case GCDESCRIBE:
		error = (*gp->g_sw->gd_mode)(gp, GM_DESCRIBE, data);
		break;

E 18
	/*
	 * XXX: only used right now to map in rbox control registers
	 * Will be replaced in the future with a real IOMAP interface.
	 */
	case IOMAPMAP:
		error = iommap(dev, (caddr_t *)data);
I 4
#if 0
		/*
		 * It may not be worth kludging this (using p_devtmp) to
		 * make this work.  It was an undocumented side-effect
		 * in HP-UX that the mapped address was the return value
		 * of the ioctl.  The only thing I remember that counted
		 * on this behavior was the rbox X10 server.
		 */
E 4
		if (!error)
			u.u_r.r_val1 = *(int *)data;	/* XXX: this sux */
I 4
#endif
E 4
		break;

	case IOMAPUNMAP:
		error = iounmmap(dev, *(caddr_t *)data);
		break;
D 5
#endif
E 5

	default:
		error = EINVAL;
		break;
	}
	return(error);
}

D 18
#endif

grfon(dev)
	dev_t dev;
E 18
I 18
grflock(gp, block)
	register struct grf_softc *gp;
	int block;
E 18
{
D 18
	int unit = GRFUNIT(dev);
	struct grf_softc *gp = &grf_softc[unit];

	/*
	 * XXX: iteoff call relies on devices being in same order
	 * as ITEs and the fact that iteoff only uses the minor part
	 * of the dev arg.
	 */
	iteoff(unit, 3);
D 11
	return((*grfdev[gp->g_type].gd_mode)
			(gp, (dev&GRFOVDEV) ? GM_GRFOVON : GM_GRFON));
E 11
I 11
	return((*gp->g_sw->gd_mode)(gp,
				    (dev&GRFOVDEV) ? GM_GRFOVON : GM_GRFON,
				    (caddr_t)0));
E 11
}

grfoff(dev)
	dev_t dev;
{
	int unit = GRFUNIT(dev);
	struct grf_softc *gp = &grf_softc[unit];
E 18
I 18
	struct proc *p = curproc;		/* XXX */
E 18
	int error;
I 18
	extern char devioc[];
E 18

D 5
#ifdef MAPMEM
E 5
D 7
	(void) grfunmmap(dev, (caddr_t)0);
E 7
I 7
D 18
	(void) grfunmmap(dev, (caddr_t)0, curproc);
E 7
D 5
#endif
E 5
D 11
	error = (*grfdev[gp->g_type].gd_mode)
			(gp, (dev&GRFOVDEV) ? GM_GRFOVOFF : GM_GRFOFF);
E 11
I 11
	error = (*gp->g_sw->gd_mode)(gp,
				     (dev&GRFOVDEV) ? GM_GRFOVOFF : GM_GRFOFF,
				     (caddr_t)0);
E 11
	/* XXX: see comment for iteoff above */
	iteon(unit, 2);
	return(error);
E 18
I 18
#ifdef DEBUG
	if (grfdebug & GDB_LOCK)
		printf("grflock(%d): dev %x flags %x lockpid %x\n",
		       p->p_pid, gp-grf_softc, gp->g_flags,
		       gp->g_lockp ? gp->g_lockp->p_pid : -1);
#endif
	if (gp->g_pid) {
#ifdef DEBUG
		if (grfdebug & GDB_LOCK)
			printf(" lockpslot %d lockslot %d lock[lockslot] %d\n",
			       gp->g_lock->gl_lockslot, gp->g_lockpslot,
			       gp->g_lock->gl_locks[gp->g_lockpslot]);
#endif
		gp->g_lock->gl_lockslot = 0;
		if (gp->g_lock->gl_locks[gp->g_lockpslot] == 0) {
			gp->g_lockp = NULL;
			gp->g_lockpslot = 0;
		}
	}
	if (gp->g_lockp) {
		if (gp->g_lockp == p)
			return(EBUSY);
		if (!block)
			return(OEAGAIN);
		do {
			gp->g_flags |= GF_WANTED;
			if (error = tsleep((caddr_t)&gp->g_flags,
					   (PZERO+1) | PCATCH, devioc, 0))
				return (error);
		} while (gp->g_lockp);
	}
	gp->g_lockp = p;
	if (gp->g_pid) {
		int slot = grffindpid(gp);

#ifdef DEBUG
		if (grfdebug & GDB_LOCK)
			printf("  slot %d\n", slot);
#endif
		gp->g_lockpslot = gp->g_lock->gl_lockslot = slot;
		gp->g_lock->gl_locks[slot] = 1;
	}
	return(0);
E 18
}

D 18
grfaddr(gp, off)
	struct grf_softc *gp;
	register int off;
E 18
I 18
grfunlock(gp)
	register struct grf_softc *gp;
E 18
{
D 5
#ifdef MAPMEM
E 5
D 18
	register struct grfinfo *gi = &gp->g_display;

	/* control registers */
	if (off >= 0 && off < gi->gd_regsize)
		return(((u_int)gi->gd_regaddr + off) >> PGSHIFT);

	/* frame buffer */
	if (off >= gi->gd_regsize && off < gi->gd_regsize+gi->gd_fbsize) {
		off -= gi->gd_regsize;
		return(((u_int)gi->gd_fbaddr + off) >> PGSHIFT);
E 18
I 18
#ifdef DEBUG
	if (grfdebug & GDB_LOCK)
		printf("grfunlock(%d): dev %x flags %x lockpid %d\n",
		       curproc->p_pid, gp-grf_softc, gp->g_flags,
		       gp->g_lockp ? gp->g_lockp->p_pid : -1);
#endif
	if (gp->g_lockp != curproc)
		return(EBUSY);
	if (gp->g_pid) {
#ifdef DEBUG
		if (grfdebug & GDB_LOCK)
			printf(" lockpslot %d lockslot %d lock[lockslot] %d\n",
			       gp->g_lock->gl_lockslot, gp->g_lockpslot,
			       gp->g_lock->gl_locks[gp->g_lockpslot]);
#endif
		gp->g_lock->gl_locks[gp->g_lockpslot] = 0;
		gp->g_lockpslot = gp->g_lock->gl_lockslot = 0;
E 18
	}
D 5
#endif
E 5
D 18
	/* bogus */
	return(-1);
E 18
I 18
	if (gp->g_flags & GF_WANTED) {
		wakeup((caddr_t)&gp->g_flags); 
		gp->g_flags &= ~GF_WANTED;
	}
	gp->g_lockp = NULL;
	return(0);
E 18
}

D 18
#ifdef HPUXCOMPAT
E 18
/*
 * Convert a BSD style minor devno to HPUX style.
 * We cannot just create HPUX style nodes as they require 24 bits
 * of minor device number and we only have 8.
 * XXX: This may give the wrong result for remote stats of other
 * machines where device 10 exists.
 */
grfdevno(dev)
	dev_t dev;
{
	int unit = GRFUNIT(dev);
	struct grf_softc *gp = &grf_softc[unit];
D 8
	int newdev;
E 8
I 8
D 11
	int newdev, sc;
E 11
I 11
	int newdev;
E 11
E 8

	if (unit >= NGRF || (gp->g_flags&GF_ALIVE) == 0)
		return(bsdtohpuxdev(dev));
	/* magic major number */
	newdev = 12 << 24;
	/* now construct minor number */
D 5
#if defined(HP360) || defined(HP370)
	if (gp->g_display.gd_regaddr == (caddr_t)DIOIIBASE)
		newdev |= 0x840200;
	else
#endif
E 5
D 8
	if (gp->g_display.gd_regaddr != (caddr_t)GRFIADDR)
		newdev |= ((u_int)gp->g_display.gd_regaddr-EXTIOBASE) | 0x200;
E 8
I 8
	if (gp->g_display.gd_regaddr != (caddr_t)GRFIADDR) {
D 11
		sc = patosc(gp->g_display.gd_regaddr);
E 11
I 11
		int sc = patosc(gp->g_display.gd_regaddr);
E 11
		newdev |= (sc << 16) | 0x200;
	}
E 8
	if (dev & GRFIMDEV)
		newdev |= 0x02;
	else if (dev & GRFOVDEV)
		newdev |= 0x01;
#ifdef DEBUG
	if (grfdebug & GDB_DEVNO)
		printf("grfdevno: dev %x newdev %x\n", dev, newdev);
#endif
	return(newdev);
}
D 18
#endif
E 18

I 18
#endif	/* HPUXCOMPAT */

E 18
D 5
#ifdef MAPMEM
grfmapin(mp, off)
	struct mapmem *mp;
{
	return(grfaddr(&grf_softc[GRFUNIT(mp->mm_id)], off));
}

E 5
D 7
grfmmap(dev, addrp)
E 7
I 7
grfmmap(dev, addrp, p)
E 7
	dev_t dev;
	caddr_t *addrp;
I 7
	struct proc *p;
E 7
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
E 3
	struct grf_softc *gp = &grf_softc[GRFUNIT(dev)];
D 3
	register struct mapmem *mp;
E 3
I 3
D 5
	struct mapmem *mp;
E 3
D 4
	int len, grfmapin();
E 4
I 4
	int len, error, grfmapin();
E 5
I 5
	int len, error;
	struct vnode vn;
	struct specinfo si;
	int flags;
E 5
E 4

#ifdef DEBUG
	if (grfdebug & GDB_MMAP)
D 3
		printf("grfmmap(%d): addr %x\n", u.u_procp->p_pid, *addrp);
E 3
I 3
		printf("grfmmap(%d): addr %x\n", p->p_pid, *addrp);
E 3
#endif
	len = gp->g_display.gd_regsize + gp->g_display.gd_fbsize;
D 3
	mp = mmalloc(minor(dev), addrp, len, MM_RW|MM_CI|MM_NOCORE, &grfops);
	if (mp == MMNIL)
E 3
I 3
D 4
	if (u.u_error = mmalloc(p, minor(dev), addrp, len, MM_RW|MM_CI|MM_NOCORE, &grfops, &mp))
E 3
		return(u.u_error);
D 3
	if (!mmmapin(mp, grfmapin)) {
		mmfree(mp);
E 3
I 3
	if (!mmmapin(p, mp, grfmapin)) {
		mmfree(p, mp);
E 3
		return(u.u_error);
	}
	return(0);
E 4
I 4
D 5
	error = mmalloc(p, minor(dev), addrp, len, MM_RW|MM_CI|MM_NOCORE,
			&grfops, &mp);
	if (error == 0)
		if (error = mmmapin(p, mp, grfmapin))
			(void) mmfree(p, mp);
E 5
I 5
D 12
	flags = MAP_FILE|MAP_SHARED;
E 12
I 12
	flags = MAP_SHARED;
E 12
	if (*addrp)
		flags |= MAP_FIXED;
	else
		*addrp = (caddr_t)0x1000000;	/* XXX */
	vn.v_type = VCHR;			/* XXX */
	vn.v_specinfo = &si;			/* XXX */
	vn.v_rdev = dev;			/* XXX */
D 7
	error = vm_mmap(u.u_procp->p_map, (vm_offset_t *)addrp,
E 7
I 7
	error = vm_mmap(&p->p_vmspace->vm_map, (vm_offset_t *)addrp,
E 7
D 16
			(vm_size_t)len, VM_PROT_ALL, flags, (caddr_t)&vn, 0);
E 16
I 16
			(vm_size_t)len, VM_PROT_ALL, VM_PROT_ALL,
			flags, (caddr_t)&vn, 0);
I 18
	if (error == 0)
		(void) (*gp->g_sw->gd_mode)(gp, GM_MAP, *addrp);
E 18
E 16
E 5
	return(error);
E 4
}

D 7
grfunmmap(dev, addr)
E 7
I 7
grfunmmap(dev, addr, p)
E 7
	dev_t dev;
	caddr_t addr;
I 7
	struct proc *p;
E 7
{
D 5
	register struct mapmem *mp, **mpp;
	int found, unit = minor(dev);

#ifdef DEBUG
	if (grfdebug & GDB_MMAP)
		printf("grfunmmap(%d): id %d addr %x\n",
		       u.u_procp->p_pid, unit, addr);
#endif
	found = 0;
	mpp = &u.u_mmap;
	for (mp = *mpp; mp; mp = *mpp) {
		if (mp->mm_ops != &grfops || mp->mm_id != unit) {
			mpp = &mp->mm_next;
			continue;
		}
		if (addr &&
		    (addr < mp->mm_uva || addr >= mp->mm_uva+mp->mm_size)) {
			mpp = &mp->mm_next;
			continue;
		}
D 4
		grfexit(mp);
E 4
I 4
		(void) grfexit(mp);
E 4
		found++;
	}
	return(found ? 0 : EINVAL);
}

grfexit(mp)
	struct mapmem *mp;
{
E 5
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
E 3
D 5
	struct grf_softc *gp = &grf_softc[GRFUNIT(mp->mm_id)];
E 5
I 5
	struct grf_softc *gp = &grf_softc[GRFUNIT(dev)];
	vm_size_t size;
	int rv;
E 5

#ifdef DEBUG
	if (grfdebug & GDB_MMAP)
D 5
		printf("grfexit(%d): id %d %x@%x\n",
D 3
		       u.u_procp->p_pid, mp->mm_id, mp->mm_size, mp->mm_uva);
E 3
I 3
		       p->p_pid, mp->mm_id, mp->mm_size, mp->mm_uva);
E 5
I 5
		printf("grfunmmap(%d): dev %x addr %x\n", p->p_pid, dev, addr);
E 5
E 3
#endif
D 5
	(void) grfunlock(gp);
#ifdef HPUXCOMPAT
	grfrmpid(gp);
#endif
D 3
	mmmapout(mp);
	mmfree(mp);
E 3
I 3
	mmmapout(p, mp);
D 4
	mmfree(p, mp);
E 4
I 4
	return(mmfree(p, mp));
E 5
I 5
	if (addr == 0)
		return(EINVAL);		/* XXX: how do we deal with this? */
I 18
	(void) (*gp->g_sw->gd_mode)(gp, GM_UNMAP, 0);
E 18
	size = round_page(gp->g_display.gd_regsize + gp->g_display.gd_fbsize);
D 7
	rv = vm_deallocate(p->p_map, (vm_offset_t)addr, size);
E 7
I 7
D 9
	rv = vm_deallocate(p->p_vmspace->vm_map, (vm_offset_t)addr, size);
E 9
I 9
	rv = vm_deallocate(&p->p_vmspace->vm_map, (vm_offset_t)addr, size);
E 9
E 7
	return(rv == KERN_SUCCESS ? 0 : EINVAL);
E 5
E 4
E 3
}

#ifdef HPUXCOMPAT
iommap(dev, addrp)
	dev_t dev;
	caddr_t *addrp;
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7
I 7
D 20
	struct proc *p = curproc;		/* XXX */
E 7
E 3
	struct grf_softc *gp = &grf_softc[GRFUNIT(dev)];
E 20
D 3
	register struct mapmem *mp;
E 3
I 3
D 5
	struct mapmem *mp;
E 3
D 4
	int len, grfmapin();
E 4
I 4
	int len, error, grfmapin();
E 5
E 4

#ifdef DEBUG
	if (grfdebug & (GDB_MMAP|GDB_IOMAP))
D 3
		printf("iommap(%d): addr %x\n", u.u_procp->p_pid, *addrp);
E 3
I 3
D 20
		printf("iommap(%d): addr %x\n", p->p_pid, *addrp);
E 20
I 20
		printf("iommap(%d): addr %x\n", curproc->p_pid, *addrp);
E 20
E 3
#endif
D 5
	len = gp->g_display.gd_regsize;
D 3
	mp = mmalloc(minor(dev), addrp, len, MM_RW|MM_CI|MM_NOCORE, &grfiomops);
	if (mp == MMNIL)
E 3
I 3
D 4
	if (u.u_error = mmalloc(p, minor(dev), addrp, len, MM_RW|MM_CI|MM_NOCORE, &grfiomops, &mp))
E 3
		return(u.u_error);
D 3
	if (!mmmapin(mp, grfmapin)) {
		mmfree(mp);
E 3
I 3
	if (!mmmapin(p, mp, grfmapin)) {
		mmfree(p, mp);
E 3
		return(u.u_error);
	}
	return(0);
E 4
I 4
	error = mmalloc(p, minor(dev), addrp, len, MM_RW|MM_CI|MM_NOCORE,
			&grfiomops, &mp);
	if (error == 0)
		if (error = mmmapin(p, mp, grfmapin))
			(void) mmfree(p, mp);
	return(error);
E 5
I 5
	return(EINVAL);
E 5
E 4
}

iounmmap(dev, addr)
	dev_t dev;
	caddr_t addr;
{
D 5
	struct grf_softc *gp = &grf_softc[GRFUNIT(dev)];
	register struct mapmem *mp, **mpp;
	int found, len, unit = minor(dev);
E 5
I 5
	int unit = minor(dev);
E 5

#ifdef DEBUG
	if (grfdebug & (GDB_MMAP|GDB_IOMAP))
		printf("iounmmap(%d): id %d addr %x\n",
D 7
		       u.u_procp->p_pid, unit, addr);
E 7
I 7
		       curproc->p_pid, unit, addr);
E 7
#endif
D 5
	found = 0;
	len = gp->g_display.gd_regsize;
	mpp = &u.u_mmap;
	for (mp = *mpp; mp; mp = *mpp) {
		if (mp->mm_ops != &grfiomops || mp->mm_id != unit) {
			mpp = &mp->mm_next;
			continue;
		}
		if (addr &&
		    (addr < mp->mm_uva || addr >= mp->mm_uva+mp->mm_size ||
		    len != mp->mm_size)) {
			mpp = &mp->mm_next;
			continue;
		}
D 4
		grfexit(mp);
E 4
I 4
		(void) grfexit(mp);
E 4
		found++;
	}
	return(found ? 0 : EINVAL);
E 5
I 5
	return(0);
E 5
}

/*
 * Processes involved in framebuffer mapping via GCSLOT are recorded in
 * an array of pids.  The first element is used to record the last slot used
 * (for faster lookups).  The remaining elements record up to GRFMAXLCK-1
 * process ids.  Returns a slot number between 1 and GRFMAXLCK or 0 if no
 * slot is available. 
 */
grffindpid(gp)
	struct grf_softc *gp;
{
	register short pid, *sp;
	register int i, limit;
	int ni;

	if (gp->g_pid == NULL) {
		gp->g_pid = (short *)
			malloc(GRFMAXLCK * sizeof(short), M_DEVBUF, M_WAITOK);
		bzero((caddr_t)gp->g_pid, GRFMAXLCK * sizeof(short));
	}
D 7
	pid = u.u_procp->p_pid;
E 7
I 7
	pid = curproc->p_pid;
E 7
	ni = limit = gp->g_pid[0];
	for (i = 1, sp = &gp->g_pid[1]; i <= limit; i++, sp++) {
		if (*sp == pid)
			goto done;
		if (*sp == 0)
			ni = i;
	}
	i = ni;
	if (i < limit) {
		gp->g_pid[i] = pid;
		goto done;
	}
	if (++i == GRFMAXLCK)
		return(0);
	gp->g_pid[0] = i;
	gp->g_pid[i] = pid;
done:
#ifdef DEBUG
	if (grfdebug & GDB_LOCK)
		printf("grffindpid(%d): slot %d of %d\n",
		       pid, i, gp->g_pid[0]);
#endif
	return(i);
}

grfrmpid(gp)
	struct grf_softc *gp;
{
	register short pid, *sp;
	register int limit, i;
	int mi;

	if (gp->g_pid == NULL || (limit = gp->g_pid[0]) == 0)
		return;
D 7
	pid = u.u_procp->p_pid;
E 7
I 7
	pid = curproc->p_pid;
E 7
	limit = gp->g_pid[0];
	mi = 0;
	for (i = 1, sp = &gp->g_pid[1]; i <= limit; i++, sp++) {
		if (*sp == pid)
			*sp = 0;
		else if (*sp)
			mi = i;
	}
	i = mi;
	if (i < limit)
		gp->g_pid[0] = i;
#ifdef DEBUG
	if (grfdebug & GDB_LOCK)
		printf("grfrmpid(%d): slot %d of %d\n",
		       pid, sp-gp->g_pid, gp->g_pid[0]);
#endif
}

D 5
/*ARGSUSED*/
grflckmapin(mp, off)
	struct mapmem *mp;
{
	u_int pa = kvtop((u_int)grf_softc[GRFUNIT(mp->mm_id)].g_locks);

#ifdef DEBUG
	if (grfdebug & GDB_LOCK)
		printf("grflckmapin(%d): va %x pa %x\n", u.u_procp->p_pid,
		       grf_softc[GRFUNIT(mp->mm_id)].g_locks, pa);
#endif
	return(pa >> PGSHIFT);
}

E 5
grflckmmap(dev, addrp)
	dev_t dev;
	caddr_t *addrp;
{
I 3
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 3
D 5
	struct grf_softc *gp = &grf_softc[GRFUNIT(dev)];
D 3
	register struct mapmem *mp;
E 3
I 3
	struct mapmem *mp;
E 3
D 4
	int grflckmapin();
E 4
I 4
	int error, grflckmapin();
E 5
E 4

E 7
#ifdef DEBUG
I 7
	struct proc *p = curproc;		/* XXX */

E 7
	if (grfdebug & (GDB_MMAP|GDB_LOCK))
		printf("grflckmmap(%d): addr %x\n",
D 3
		       u.u_procp->p_pid, *addrp);
E 3
I 3
		       p->p_pid, *addrp);
E 3
#endif
D 5
	if (gp->g_locks == NULL) {
		gp->g_locks = (u_char *) cialloc(NBPG);
		if (gp->g_locks == NULL)
			return(ENOMEM);
	}
D 3
	mp = mmalloc(minor(dev), addrp, NBPG, MM_RW|MM_CI, &grflckops);
	if (mp == MMNIL)
E 3
I 3
D 4
	if (u.u_error = mmalloc(p, minor(dev), addrp, NBPG, MM_RW|MM_CI, &grflckops, &mp))
E 3
		return(u.u_error);
D 3
	if (!mmmapin(mp, grflckmapin)) {
		mmfree(mp);
E 3
I 3
	if (!mmmapin(p, mp, grflckmapin)) {
		mmfree(p, mp);
E 3
		return(u.u_error);
	}
	return(0);
E 4
I 4
	error = mmalloc(p, minor(dev), addrp, NBPG, MM_RW|MM_CI,
			&grflckops, &mp);
	if (error == 0)
		if (error = mmmapin(p, mp, grflckmapin))
			(void) mmfree(p, mp);
	return(error);
E 5
I 5
	return(EINVAL);
E 5
E 4
}

grflckunmmap(dev, addr)
	dev_t dev;
	caddr_t addr;
{
I 7
#ifdef DEBUG
E 7
D 5
	register struct mapmem *mp;
E 5
	int unit = minor(dev);

D 7
#ifdef DEBUG
E 7
	if (grfdebug & (GDB_MMAP|GDB_LOCK))
		printf("grflckunmmap(%d): id %d addr %x\n",
D 7
		       u.u_procp->p_pid, unit, addr);
E 7
I 7
		       curproc->p_pid, unit, addr);
E 7
#endif
D 5
	for (mp = u.u_mmap; mp; mp = mp->mm_next)
		if (mp->mm_ops == &grflckops && mp->mm_id == unit &&
		    mp->mm_uva == addr) {
D 4
			grfexit(mp);
E 4
I 4
			(void) grfexit(mp);
E 4
			return(0);
		}
E 5
	return(EINVAL);
}
#endif	/* HPUXCOMPAT */
D 5
#endif	/* MAPMEM */
E 5
I 5

E 5
#endif	/* NGRF > 0 */
E 1
