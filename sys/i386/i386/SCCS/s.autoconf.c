h07760
s 00002/00002/00158
d D 8.1 93/06/11 15:34:24 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00156
d D 7.3 93/04/19 18:07:43 torek 11 10
c terminate swap list with NODEV, not 0 (0 is a valid device!)
e
s 00009/00009/00151
d D 7.2 92/10/11 10:10:52 bostic 10 9
c make kernel includes standard
e
s 00003/00005/00157
d D 7.1 91/05/09 20:42:47 william 9 8
c remove ref to argdev
e
s 00005/00003/00157
d D 5.7 91/04/15 17:53:11 william 8 7
c dumps, new vm
e
s 00002/00002/00158
d D 5.6 91/01/19 12:35:24 william 7 6
c minor corrections
e
s 00001/00054/00159
d D 5.5 90/11/18 11:30:06 bill 6 5
c fix autoconf, move code to isa.c, remove debugging, drop redundant tlbflushes, macros for tlb et al
e
s 00065/00024/00148
d D 5.4 90/11/14 13:55:11 bill 5 4
c 
e
s 00000/00002/00172
d D 5.3 90/11/14 12:12:25 bill 4 3
c add support for splmask and device tables
e
s 00003/00002/00171
d D 5.2 90/06/23 19:22:32 donahn 3 2
c iba to isa
e
s 00034/00341/00139
d D 5.1 90/04/24 18:56:19 william 2 1
c 1st Berkeley Release
e
s 00480/00000/00000
d D 1.1 90/03/12 15:47:40 bill 1 0
c date and time created 90/03/12 15:47:40 by bill
e
u
U
t
T
I 1
D 2
/*	autoconf.c	1.13	87/04/02	*/
E 2
I 2
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 8
 * %sccs.include.386.c%
E 8
I 8
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 2

I 3
D 4
/*	autoconf.c	1.13	87/04/02	*/

E 4
E 3
/*
 * Setup the system to run on the current machine.
 *
 * Configure() is called at boot time and initializes the vba 
 * device tables and the memory controller monitoring.  Available
 * devices are determined (from possibilities mentioned in ioconf.c),
 * and the drivers are initialized.
 */
D 10
#include "param.h"
#include "systm.h"
#include "map.h"
#include "buf.h"
#include "dkstat.h"
D 8
#include "vm.h"
E 8
#include "conf.h"
#include "dmap.h"
#include "reboot.h"
E 10
I 10
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/dkstat.h>
#include <sys/conf.h>
#include <sys/dmap.h>
#include <sys/reboot.h>
E 10

D 5
#include "pte.h"
D 2
#include "mem.h"
#include "mtpr.h"
#include "scb.h"
E 2
I 2
#include "../machine/device.h"
E 5
I 5
D 10
#include "machine/pte.h"
E 10
I 10
#include <machine/pte.h>
E 10
E 5
E 2

D 2
#include "vba.h"

#include "../tahoevba/vbavar.h"
#include "../tahoevba/vbaparam.h"

E 2
/*
 * The following several variables are related to
 * the configuration process, and are used in initializing
 * the machine.
 */
int	dkn;		/* number of iostat dk numbers assigned so far */
D 7
int	cold;		/* cold start flag initialized in locore.s */
E 7
I 7
extern int	cold;		/* cold start flag initialized in locore.s */
E 7

/*
D 2
 * This allocates the space for the per-vba information.
 */
struct	vba_hd vba_hd[NVBA];

/*
E 2
 * Determine i/o configuration for a machine.
 */
configure()
{
I 6

E 6
D 5
	register int *ip;
	extern caddr_t Sysbase;
I 2
	struct device *dvp;
	struct driver *dp;
	register s;
E 5
I 5
#include "isa.h"
#if NISA > 0
	isa_configure();
#endif
E 5
E 2

D 2
	vbafind(numvba, (caddr_t)&vmem, VMEMmap);
	numvba++;
	/*
	 * Write protect the scb.  It is strange
	 * that this code is here, but this is as soon
	 * as we are done mucking with it, and the
	 * write-enable was done in assembly language
	 * to which we will never return.
	 */
	ip = (int *)&Sysmap[2]; *ip &= ~PG_PROT; *ip |= PG_KR;
	mtpr(TBIS, Sysbase+2*NBPG);
#if GENERIC
E 2
I 2
D 5
	for (dvp = devtab; dp = dvp->driver; dvp++) {
		s = splhigh();
		dvp->alive = (*dp->probe)(dvp);
		if (dvp->alive) {
			printf("%s%d", dp->name, dvp->unit);
			(*dp->attach)(dvp);
D 3
			printf(" at 0x%x on iba0\n", dvp->ioa);
E 3
I 3
			printf(" at 0x%x on isa0\n", dvp->ioa);
E 3
		}
		splx(s);
	}

/*pg("setroot");*/
E 5
#if GENERICxxx
E 2
	if ((boothowto & RB_ASKNAME) == 0)
		setroot();
	setconf();
#else
	setroot();
#endif
	/*
	 * Configure swap area and related system
	 * parameter based on device(s) used.
	 */
I 2
D 5
/*pg("swapconf");*/
E 5
E 2
	swapconf();
	cold = 0;
I 2
D 3
rootdev=0;
E 3
E 2
}
D 6

I 5
#if NISA > 0
#include "machine/isa/device.h"
#include "machine/isa/icu.h"
isa_configure() {
	struct isa_device *dvp;
	struct isa_driver *dp;

	splhigh();
	INTREN(IRQ_SLAVE);
	for (dvp = isa_devtab_bio; config_isadev(dvp,&biomask); dvp++);
	for (dvp = isa_devtab_tty; config_isadev(dvp,&ttymask); dvp++);
	for (dvp = isa_devtab_net; config_isadev(dvp,&netmask); dvp++);
	for (dvp = isa_devtab_null; config_isadev(dvp,0); dvp++);
#include "sl.h"
#if NSL > 0
	netmask |= ttymask;
	ttymask |= netmask;
#endif
	/* biomask |= ttymask ;  can some tty devices use buffers? */
	printf("biomask %x ttymask %x netmask %x\n", biomask, ttymask, netmask);
	splnone();
}

config_isadev(isdp, mp)
	struct isa_device *isdp;
	int *mp;
{
	struct isa_driver *dp;
 
	if (dp = isdp->id_driver) {
		if (isdp->id_maddr) {
			extern int atdevbase[];

			isdp->id_maddr -= 0xa0000;
			isdp->id_maddr += (int)&atdevbase;
		}
		isdp->id_alive = (*dp->probe)(isdp);
		if (isdp->id_alive) {
			printf("%s%d", dp->name, isdp->id_unit);
			(*dp->attach)(isdp);
			printf(" at 0x%x ", isdp->id_iobase);
			if(isdp->id_irq) {
				printf("irq %d ", ffs(isdp->id_irq)-1);
				INTREN(isdp->id_irq);
				if(mp)INTRMASK(*mp,isdp->id_irq);
			}
			if (isdp->id_drq != -1) printf("drq %d ", isdp->id_drq);
			printf("on isa0\n");
		}
		return (1);
	} else	return(0);
}
#endif
E 6

E 5
/*
D 2
 * Make the controllers accessible at physical address phys
 * by mapping kernel ptes starting at pte.
 */
vbaccess(pte, iobase, n)
	register struct pte *pte;
	caddr_t iobase;
	register int n;
{
	register unsigned v = btop(iobase);
	
	do
		*(int *)pte++ = PG_V|PG_KW|v++;
	while (--n > 0);
	mtpr(TBIA, 0);
}

/*
 * Fixctlrmask fixes the masks of the driver ctlr routines
 * which otherwise save r11 and r12 where the interrupt and br
 * level are passed through.
 */
fixctlrmask()
{
	register struct vba_ctlr *vm;
	register struct vba_device *vi;
	register struct vba_driver *vd;
#define	phys(a,b) ((b)(((int)(a))&~0xc0000000))

	vm = phys(vbminit, struct vba_ctlr *);
	for (; vd = phys(vm->um_driver, struct vba_driver *); vm++)
		*phys(vd->ud_probe, short *) &= ~0x1800;
	vi = phys(vbdinit, struct vba_device *);
	for (; vd = phys(vi->ui_driver, struct vba_driver *); vi++)
		*phys(vd->ud_probe, short *) &= ~0x1800;
}

/*
 * Find devices on the VERSAbus.
 * Uses per-driver routine to see who is on the bus
 * and then fills in the tables, with help from a per-driver
 * slave initialization routine.
 */
vbafind(vban, vumem, memmap)
	int vban;
	caddr_t vumem;
	struct pte memmap[];
{
	register int br, cvec;			/* must be r12, r11 */
	register struct vba_device *ui;
	register struct vba_ctlr *um;
	u_short *reg;
	long addr, *ap;
	struct vba_hd *vhp;
	struct vba_driver *udp;
	int i, octlr, (**ivec)();
	caddr_t valloc, zmemall();
	extern long catcher[SCB_LASTIV*2];

#ifdef lint
	br = 0; cvec = 0;
#endif
	vhp = &vba_hd[vban];
	/*
	 * Make the controllers accessible at physical address phys
	 * by mapping kernel ptes starting at pte.
	 */
	vbaccess(memmap, (caddr_t)VBIOBASE, VBIOSIZE);
	printf("vba%d at %x\n", vban, VBIOBASE);
	/*
	 * Setup scb device entries to point into catcher array.
	 */
	for (i = 0; i < SCB_LASTIV; i++)
		scb.scb_devint[i] = (int (*)())&catcher[i*2];
	/*
	 * Set last free interrupt vector for devices with
	 * programmable interrupt vectors.  Use is to decrement
	 * this number and use result as interrupt vector.
	 */
	vhp->vh_lastiv = SCB_LASTIV;
	/*
	 * Grab some memory to record the address space we allocate,
	 * so we can be sure not to place two devices at the same address.
	 *
	 * We could use just 1/8 of this (we only want a 1 bit flag) but
	 * we are going to give it back anyway, and that would make the
	 * code here bigger (which we can't give back), so ...
	 */
	valloc = zmemall(memall, ctob(VBIOSIZE));
	if (valloc == (caddr_t)0)
		panic("no mem for vbafind");

	/*
	 * Check each VERSAbus mass storage controller.
	 * For each one which is potentially on this vba,
	 * see if it is really there, and if it is record it and
	 * then go looking for slaves.
	 */
#define	vbaddr(off)	(u_short *)(vumem + vboff(off))
	for (um = vbminit; udp = um->um_driver; um++) {
		if (um->um_vbanum != vban && um->um_vbanum != '?')
			continue;
		/*
		 * Use the particular address specified first,
		 * or if it is given as "0", if there is no device
		 * at that address, try all the standard addresses
		 * in the driver until we find it.
		 */
		addr = (long)um->um_addr;
	    for (ap = udp->ud_addr; addr || (addr = *ap++); addr = 0) {
		if (VBIOMAPPED(addr)) {
			if (valloc[vboff(addr)])
				continue;
			reg = vbaddr(addr);
		} else
			reg = (u_short *)addr;
		um->um_hd = vhp;
		cvec = SCB_LASTIV, cold &= ~0x2;
		i = (*udp->ud_probe)(reg, um);
		cold |= 0x2;
		if (i == 0)
			continue;
		printf("%s%d at vba%d csr %x ",
		    udp->ud_mname, um->um_ctlr, vban, addr);
		if (cvec < 0 && vhp->vh_lastiv == cvec) {
			printf("no space for vector(s)\n");
			continue;
		}
		if (cvec == SCB_LASTIV) {
			printf("didn't interrupt\n");
			continue;
		}
		printf("vec %x, ipl %x\n", cvec, br);
		csralloc(valloc, addr, i);
		um->um_alive = 1;
		um->um_vbanum = vban;
		um->um_addr = (caddr_t)reg;
		udp->ud_minfo[um->um_ctlr] = um;
		for (ivec = um->um_intr; *ivec; ivec++)
			((long *)&scb)[cvec++] = (long)*ivec;
		for (ui = vbdinit; ui->ui_driver; ui++) {
			if (ui->ui_driver != udp || ui->ui_alive ||
			    ui->ui_ctlr != um->um_ctlr && ui->ui_ctlr != '?' ||
			    ui->ui_vbanum != vban && ui->ui_vbanum != '?')
				continue;
			octlr = ui->ui_ctlr, ui->ui_ctlr = um->um_ctlr;
			if ((*udp->ud_slave)(ui, reg)) {
				ui->ui_alive = 1;
				ui->ui_ctlr = um->um_ctlr;
				ui->ui_vbanum = vban;
				ui->ui_addr = (caddr_t)reg;
				ui->ui_physaddr = (caddr_t)addr;
				if (ui->ui_dk && dkn < DK_NDRIVE)
					ui->ui_dk = dkn++;
				else
					ui->ui_dk = -1;
				ui->ui_mi = um;
				ui->ui_hd = vhp;
				/* ui_type comes from driver */
				udp->ud_dinfo[ui->ui_unit] = ui;
				printf("%s%d at %s%d slave %d",
				    udp->ud_dname, ui->ui_unit,
				    udp->ud_mname, um->um_ctlr,
				    ui->ui_slave);
				(*udp->ud_attach)(ui);
				printf("\n");
			} else
				ui->ui_ctlr = octlr;
		}
		break;
	    }
	}
	/*
	 * Now look for non-mass storage peripherals.
	 */
	for (ui = vbdinit; udp = ui->ui_driver; ui++) {
		if (ui->ui_vbanum != vban && ui->ui_vbanum != '?' ||
		    ui->ui_alive || ui->ui_slave != -1)
			continue;
		addr = (long)ui->ui_addr;
	    for (ap = udp->ud_addr; addr || (addr = *ap++); addr = 0) {
		if (VBIOMAPPED(addr)) {
			if (valloc[vboff(addr)])
				continue;
			reg = vbaddr(addr);
		} else
			reg = (u_short *)addr;
		ui->ui_hd = vhp;
		cvec = SCB_LASTIV, cold &= ~0x2;
		i = (*udp->ud_probe)(reg, ui);
		cold |= 0x2;
		if (i == 0)
			continue;
		printf("%s%d at vba%d csr %x ",
		    ui->ui_driver->ud_dname, ui->ui_unit, vban, addr);
		if (ui->ui_intr) {
			if (cvec < 0 && vhp->vh_lastiv == cvec) {
				printf("no space for vector(s)\n");
				continue;
			}
			if (cvec == SCB_LASTIV) {
				printf("didn't interrupt\n");
				continue;
			}
			printf("vec %x, ipl %x\n", cvec, br);
			for (ivec = ui->ui_intr; *ivec; ivec++)
				((long *)&scb)[cvec++] = (long)*ivec;
		} else
			printf("no interrupts\n");
		csralloc(valloc, addr, i);
		ui->ui_alive = 1;
		ui->ui_vbanum = vban;
		ui->ui_addr = (caddr_t)reg;
		ui->ui_physaddr = (caddr_t)addr;
		ui->ui_dk = -1;
		/* ui_type comes from driver */
		udp->ud_dinfo[ui->ui_unit] = ui;
		(*udp->ud_attach)(ui);
		break;
	    }
	}
	wmemfree(valloc, ctob(VBIOSIZE));
}

/*
 * Mark addresses starting at addr and continuing
 * size bytes as allocated in the map.
 * Warn if the new allocation overlaps a previous allocation.
 */
csralloc(valloc, addr, size)
	caddr_t valloc;
	long addr;
	register int size;
{
	register caddr_t p;
	int warned = 0;

	if (!VBIOMAPPED(addr))
		return;
	p = &valloc[vboff(addr+size)];
	while (--size >= 0) {
		if (*--p && !warned) {
			printf(
	"WARNING: device registers overlap those for a previous device\n");
			warned = 1;
		}
		*p = 1;
	}
}

/*
 * Tahoe VERSAbus adapator support routines.
 */

caddr_t	vbcur = (caddr_t)&vbbase;
int	vbx = 0;
/*
 * Allocate page tables for mapping intermediate i/o buffers.
 * Called by device drivers during autoconfigure.
 */
vbmapalloc(npf, ppte, putl)
	int npf;
	struct pte **ppte;
	caddr_t *putl;
{

	if (vbcur + npf*NBPG >= (caddr_t)&vbend)
		panic("vbmapalloc");
	*ppte = &VBmap[vbx];
	*putl = vbcur;
	vbx += npf;
	vbcur += npf*NBPG;
}

caddr_t	vbmcur = (caddr_t)&vmem1;
int	vbmx = 0;
/*
 * Allocate page tables and map VERSAbus i/o space.
 * Called by device drivers during autoconfigure.
 */
vbmemalloc(npf, addr, ppte, putl)
	int npf;
	caddr_t addr;
	struct pte **ppte;
	caddr_t *putl;
{

	if (vbmcur + npf*NBPG >= (caddr_t)&vmemend)
		panic("vbmemalloc");
	*ppte = &VMEMmap1[vbmx];
	*putl = vbmcur;
	vbmx += npf;
	vbmcur += npf*NBPG;
	vbaccess(*ppte, addr, npf);		/* map i/o space */
}

/*
E 2
 * Configure swap space and related parameters.
 */
swapconf()
{
	register struct swdevt *swp;
	register int nblks;
I 8
extern int Maxmem;
E 8

D 2
	for (swp = swdevt; swp->sw_dev; swp++)
E 2
I 2
D 11
	for (swp = swdevt; swp->sw_dev > 0; swp++)
E 11
I 11
	for (swp = swdevt; swp->sw_dev != NODEV; swp++)
E 11
	{
D 11
		if ( swp->sw_dev < 0 || swp->sw_dev > nblkdev ) break;
E 11
I 11
		if ( (u_int)swp->sw_dev >= nblkdev ) break;	/* XXX */
E 11
E 2
		if (bdevsw[major(swp->sw_dev)].d_psize) {
			nblks =
			  (*bdevsw[major(swp->sw_dev)].d_psize)(swp->sw_dev);
			if (nblks != -1 &&
			    (swp->sw_nblks == 0 || swp->sw_nblks > nblks))
				swp->sw_nblks = nblks;
		}
I 2
	}
E 2
	if (dumplo == 0 && bdevsw[major(dumpdev)].d_psize)
D 8
		dumplo = (*bdevsw[major(dumpdev)].d_psize)(dumpdev) - physmem;
E 8
I 8
	/*dumplo = (*bdevsw[major(dumpdev)].d_psize)(dumpdev) - physmem;*/
		dumplo = (*bdevsw[major(dumpdev)].d_psize)(dumpdev) -
			Maxmem*NBPG/512;
E 8
	if (dumplo < 0)
		dumplo = 0;
}

D 9
#define	DOSWAP			/* change swdevt, argdev, and dumpdev too */
E 9
I 9
#define	DOSWAP			/* change swdevt and dumpdev */
E 9
D 7
u_long	bootdev;		/* should be dev_t, but not until 32 bits */
E 7
I 7
u_long	bootdev = 0;		/* should be dev_t, but not until 32 bits */
E 7

static	char devname[][2] = {
D 5
	0,0,		/* 0 = ud */
	'd','k',	/* 1 = vd */
	0,0,		/* 2 = xp */
E 5
I 5
	'w','d',	/* 0 = wd */
	's','w',	/* 1 = sw */
	'f','d',	/* 2 = fd */
	'w','t',	/* 3 = wt */
	'x','d',	/* 4 = xd */
E 5
};

#define	PARTITIONMASK	0x7
#define	PARTITIONSHIFT	3

/*
 * Attempt to find the device from which we were booted.
 * If we can do so, and not instructed not to do so,
 * change rootdev to correspond to the load device.
 */
setroot()
{
	int  majdev, mindev, unit, part, adaptor;
	dev_t temp, orootdev;
	struct swdevt *swp;

	if (boothowto & RB_DFLTROOT ||
	    (bootdev & B_MAGICMASK) != (u_long)B_DEVMAGIC)
		return;
	majdev = (bootdev >> B_TYPESHIFT) & B_TYPEMASK;
	if (majdev > sizeof(devname) / sizeof(devname[0]))
		return;
	adaptor = (bootdev >> B_ADAPTORSHIFT) & B_ADAPTORMASK;
	part = (bootdev >> B_PARTITIONSHIFT) & B_PARTITIONMASK;
	unit = (bootdev >> B_UNITSHIFT) & B_UNITMASK;
D 2
	/*
	 * Search Versabus devices.
	 *
	 * WILL HAVE TO DISTINGUISH VME/VERSABUS SOMETIME
	 */
	{
		register struct vba_device *vbap;

		for (vbap = vbdinit; vbap->ui_driver; vbap++)
			if (vbap->ui_alive && vbap->ui_slave == unit &&
			   vbap->ui_vbanum == adaptor &&
			   vbap->ui_driver->ud_dname[0] == devname[majdev][0] &&
			   vbap->ui_driver->ud_dname[1] == devname[majdev][1])
				break;
		if (vbap->ui_driver == 0)
			return;
		mindev = vbap->ui_unit;
	}
E 2
D 5
	mindev = (mindev << PARTITIONSHIFT) + part;
E 5
I 5
	mindev = (unit << PARTITIONSHIFT) + part;
E 5
	orootdev = rootdev;
	rootdev = makedev(majdev, mindev);
	/*
	 * If the original rootdev is the same as the one
	 * just calculated, don't need to adjust the swap configuration.
	 */
	if (rootdev == orootdev)
		return;
	printf("changing root device to %c%c%d%c\n",
		devname[majdev][0], devname[majdev][1],
		mindev >> PARTITIONSHIFT, part + 'a');
#ifdef DOSWAP
	mindev &= ~PARTITIONMASK;
D 11
	for (swp = swdevt; swp->sw_dev; swp++) {
E 11
I 11
	for (swp = swdevt; swp->sw_dev != NODEV; swp++) {
E 11
		if (majdev == major(swp->sw_dev) &&
		    mindev == (minor(swp->sw_dev) & ~PARTITIONMASK)) {
			temp = swdevt[0].sw_dev;
			swdevt[0].sw_dev = swp->sw_dev;
			swp->sw_dev = temp;
			break;
		}
	}
D 11
	if (swp->sw_dev == 0)
E 11
I 11
	if (swp->sw_dev == NODEV)
E 11
		return;
	/*
D 9
	 * If argdev and dumpdev were the same as the old primary swap
	 * device, move them to the new primary swap device.
E 9
I 9
	 * If dumpdev was the same as the old primary swap
	 * device, move it to the new primary swap device.
E 9
	 */
	if (temp == dumpdev)
		dumpdev = swdevt[0].sw_dev;
D 9
	if (temp == argdev)
		argdev = swdevt[0].sw_dev;
E 9
#endif
}
E 1
