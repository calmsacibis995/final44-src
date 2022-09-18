h39993
s 00002/00002/00334
d D 8.1 93/06/10 23:06:11 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00335
d D 7.11 93/05/09 17:48:05 ralph 11 10
c delete extra space
e
s 00022/00001/00314
d D 7.10 93/05/09 15:56:58 ralph 10 9
c recognize boot devices with strings like '5/rz0/vmunix'.
e
s 00003/00003/00312
d D 7.9 93/04/19 18:09:54 torek 9 8
c terminate swap list with NODEV, not 0 (0 is a valid device!)
e
s 00003/00001/00312
d D 7.8 93/03/23 18:55:39 ralph 8 7
c changes from Rick Macklem
e
s 00001/00000/00312
d D 7.7 92/12/20 11:46:41 ralph 7 6
c changes from Rick Macklem
e
s 00042/00023/00270
d D 7.6 92/11/15 16:30:25 ralph 6 5
c updates from Rick Macklem for maxine.
e
s 00010/00010/00283
d D 7.5 92/10/11 11:23:04 bostic 5 4
c make kernel includes standard
e
s 00001/00001/00292
d D 7.4 92/09/13 11:42:10 ralph 4 3
c change if GENERIC to ifdef GENERIC so it works!
e
s 00001/00004/00292
d D 7.3 92/03/29 20:54:32 ralph 3 2
c fix auto root switching
e
s 00043/00000/00253
d D 7.2 92/02/29 11:27:50 ralph 2 1
c added support for DS5000
e
s 00253/00000/00000
d D 7.1 92/01/07 17:29:18 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 12
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: autoconf.c 1.31 91/01/21$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Setup the system to run on the current machine.
 *
 * Configure() is called at boot time.  Available
 * devices are determined (from possibilities mentioned in ioconf.c),
 * and the drivers are initialized.
 */

D 5
#include "param.h"
#include "systm.h"
#include "map.h"
#include "buf.h"
#include "dkstat.h"
#include "conf.h"
#include "dmap.h"
#include "reboot.h"
E 5
I 5
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/dkstat.h>
#include <sys/conf.h>
#include <sys/dmap.h>
#include <sys/reboot.h>
E 5

D 5
#include "../include/cpu.h"
#include "../dev/device.h"
E 5
I 5
#include <machine/cpu.h>
#include <pmax/dev/device.h>
I 6
#include <pmax/pmax/pmaxtype.h>
#include <pmax/pmax/turbochannel.h>
E 6
E 5

/*
 * The following several variables are related to
 * the configuration process, and are used in initializing
 * the machine.
 */
int	cold = 1;	/* if 1, still working on cold-start */
int	dkn;		/* number of iostat dk numbers assigned so far */
int	cpuspeed = 30;	/* approx # instr per usec. */
I 6
extern	int pmax_boardtype;
extern	tc_option_t tc_slot_info[TC_MAX_LOGICAL_SLOTS];
E 6

/*
 * Determine mass storage and memory configuration for a machine.
 * Get cpu type, and then switch out to machine specific procedures
 * which will probe adaptors to see what is out there.
 */
configure()
{
	register struct pmax_ctlr *cp;
	register struct scsi_device *dp;
	register struct driver *drp;
I 2
D 6
#ifdef DS5000
E 6
	register int i;
D 6
#endif
E 6
E 2

	/* print what type of CPU and FPU we have */
I 6

	/*
	 * for some reason the Pmax has an R2000 cpu with an implementation
	 * level of 2 and DEC's R3000s are level 2 as well?
	 */
	if (pmax_boardtype == DS_PMAX) {
		cpu.cpu.cp_imp = MIPS_R2000;
		fpu.cpu.cp_imp = MIPS_R2010;
	}

E 6
	switch (cpu.cpu.cp_imp) {
	case MIPS_R2000:
		printf("cpu0 (MIPS R2000 revision %d.%d)\n",
			cpu.cpu.cp_majrev, cpu.cpu.cp_minrev);
		break;

I 2
	case MIPS_R3000:
		printf("cpu0 (MIPS R3000 revision %d.%d)\n",
			cpu.cpu.cp_majrev, cpu.cpu.cp_minrev);
		break;

	case MIPS_R4000:
		printf("cpu0 (MIPS R4000 revision %d.%d)\n",
			cpu.cpu.cp_majrev, cpu.cpu.cp_minrev);
		break;

E 2
	default:
		printf("cpu0 (implementation %d revision %d.%d)\n",
			cpu.cpu.cp_imp, cpu.cpu.cp_majrev, cpu.cpu.cp_minrev);
	}
	switch (fpu.cpu.cp_imp) {
	case MIPS_R2010:
		printf("fpu0 (MIPS R2010 revision %d.%d)\n",
			fpu.cpu.cp_majrev, fpu.cpu.cp_minrev);
		break;

I 2
	case MIPS_R3010:
		printf("fpu0 (MIPS R3010 revision %d.%d)\n",
			fpu.cpu.cp_majrev, fpu.cpu.cp_minrev);
		break;

	case MIPS_R4010:
		printf("fpu0 (MIPS R4010 revision %d.%d)\n",
			fpu.cpu.cp_majrev, fpu.cpu.cp_minrev);
		break;

E 2
	default:
		printf("fpu0 (implementation %d revision %d.%d)\n",
			fpu.cpu.cp_imp, fpu.cpu.cp_majrev, fpu.cpu.cp_minrev);
	}
	printf("data cache size %dK inst cache size %dK\n",
		machDataCacheSize >> 10, machInstCacheSize >> 10);

	/* probe and initialize controllers */
	for (cp = pmax_cinit; drp = cp->pmax_driver; cp++) {
I 2
D 6
#ifdef DS3100
E 2
		if (!(*drp->d_init)(cp))
			continue;
I 2
#endif
E 6
I 6
		switch (pmax_boardtype) {
		case DS_PMAX:
			if (cp->pmax_addr == (char *)QUES)
				continue;
			if (!(*drp->d_init)(cp))
				continue;
			break;
E 6
#ifdef DS5000
D 6
		/*
		 * If the device is still in an unknown slot,
		 * then it was not found by tc_find_all_options().
		 */
		if (cp->pmax_addr == (char *)QUES)
			continue;
		if (!(*drp->d_init)(cp))
			continue;
		if (drp->d_intr && (i = cp->pmax_pri) >= 0) {
			if (intr_tab[i].func)
				printf("%s: slot %d already in use\n",
					drp->d_name, i);
			intr_tab[i].func = drp->d_intr;
			intr_tab[i].unit = cp->pmax_unit;
			tc_enable_interrupt(i, 1);
		}
#endif
E 6
I 6
		case DS_3MAX:
		case DS_3MIN:
		case DS_MAXINE:
I 7
		case DS_3MAXPLUS:
E 7
			/*
			 * If the device is still in an unknown slot,
			 * then it was not found by tc_find_all_options().
			 */
			if (cp->pmax_addr == (char *)QUES)
				continue;
D 8
			if (!(*drp->d_init)(cp))
E 8
I 8
			if (!(*drp->d_init)(cp)) {
				cp->pmax_alive = 0;
E 8
				continue;
I 8
			}
E 8
			if (drp->d_intr && (i = cp->pmax_pri) >= 0) {
				if (tc_slot_info[i].intr)
					printf("%s: slot %d already in use\n",
						drp->d_name, i);
				tc_slot_info[i].intr = drp->d_intr;
				tc_slot_info[i].unit = cp->pmax_unit;
			}
			break;
#endif /* DS5000 */
		};
E 6
E 2

		cp->pmax_alive = 1;

		/* probe and initialize devices connected to controller */
		for (dp = scsi_dinit; drp = dp->sd_driver; dp++) {
			/* might want to get fancier later */
			if (dp->sd_cdriver != cp->pmax_driver ||
			    dp->sd_ctlr != cp->pmax_unit)
				continue;	/* not connected */
			if (!(*drp->d_init)(dp))
				continue;
			dp->sd_alive = 1;
			/* if device is a disk, assign number for statistics */
			if (dp->sd_dk && dkn < DK_NDRIVE)
				dp->sd_dk = dkn++;
			else
				dp->sd_dk = -1;
		}
	}

D 4
#if GENERIC
E 4
I 4
#ifdef GENERIC
E 4
	if ((boothowto & RB_ASKNAME) == 0)
		setroot();
	setconf();
#else
	setroot();
#endif
	swapconf();
	cold = 0;
}

/*
 * Configure swap space and related parameters.
 */
swapconf()
{
	register struct swdevt *swp;
	register int nblks;

D 9
	for (swp = swdevt; swp->sw_dev; swp++)
E 9
I 9
	for (swp = swdevt; swp->sw_dev != NODEV; swp++)
E 9
		if (bdevsw[major(swp->sw_dev)].d_psize) {
			nblks =
			  (*bdevsw[major(swp->sw_dev)].d_psize)(swp->sw_dev);
			if (nblks != -1 &&
			    (swp->sw_nblks == 0 || swp->sw_nblks > nblks))
				swp->sw_nblks = nblks;
		}
	dumpconf();
}

#define	DOSWAP			/* Change swdevt and dumpdev too */
u_long	bootdev;		/* should be dev_t, but not until 32 bits */

static	char devname[][2] = {
	'r','z',	/* 0 = rz */
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
	register struct scsi_device *dp;
	int  majdev, mindev, unit, part, controller;
	dev_t temp, orootdev;
	struct swdevt *swp;

	if (boothowto & RB_DFLTROOT ||
	    (bootdev & B_MAGICMASK) != B_DEVMAGIC)
		return;
	majdev = B_TYPE(bootdev);
	if (majdev >= sizeof(devname) / sizeof(devname[0]))
		return;
	controller = B_CONTROLLER(bootdev);
	part = B_PARTITION(bootdev);
	unit = B_UNIT(bootdev);

	for (dp = scsi_dinit; ; dp++) {
		if (dp->sd_driver == 0)
			return;
		if (dp->sd_alive && dp->sd_drive == unit &&
		    dp->sd_ctlr == controller &&
		    dp->sd_driver->d_name[0] == devname[majdev][0] &&
		    dp->sd_driver->d_name[1] == devname[majdev][1]) {
			mindev = dp->sd_unit;
		    	break;
		}
	}
	/*
	 * Form a new rootdev
	 */
	mindev = (mindev << PARTITIONSHIFT) + part;
	orootdev = rootdev;
	rootdev = makedev(majdev, mindev);
	/*
	 * If the original rootdev is the same as the one
	 * just calculated, don't need to adjust the swap configuration.
	 */
	if (rootdev == orootdev)
		return;

	printf("Changing root device to %c%c%d%c\n",
		devname[majdev][0], devname[majdev][1],
		mindev >> PARTITIONSHIFT, part + 'a');

#ifdef DOSWAP
	mindev &= ~PARTITIONMASK;
D 9
	for (swp = swdevt; swp->sw_dev; swp++) {
E 9
I 9
	for (swp = swdevt; swp->sw_dev != NODEV; swp++) {
E 9
		if (majdev == major(swp->sw_dev) &&
		    mindev == (minor(swp->sw_dev) & ~PARTITIONMASK)) {
			temp = swdevt[0].sw_dev;
			swdevt[0].sw_dev = swp->sw_dev;
			swp->sw_dev = temp;
			break;
		}
	}
D 9
	if (swp->sw_dev == 0)
E 9
I 9
	if (swp->sw_dev == NODEV)
E 9
		return;

	/*
	 * If dumpdev was the same as the old primary swap
	 * device, move it to the new primary swap device.
	 */
	if (temp == dumpdev)
		dumpdev = swdevt[0].sw_dev;
#endif
}

/*
 * Look at the string 'cp' and decode the boot device.
I 10
 * Boot names can be something like 'rz(0,0,0)vmunix' or '5/rz0/vmunix'.
E 10
 */
void
makebootdev(cp)
	register char *cp;
{
D 10
	int  majdev, unit, part, ctrl;
E 10
I 10
	int majdev, unit, part, ctrl;
E 10

I 10
	if (*cp >= '0' && *cp <= '9') {
		/* XXX should be able to specify controller */
		if (cp[1] != '/' || cp[4] < '0' || cp[4] > '9')
D 11
			 goto defdev;
E 11
I 11
			goto defdev;
E 11
		unit = cp[4] - '0';
		if (cp[5] >= 'a' && cp[5] <= 'h')
			part = cp[5] - 'a';
		else
			part = 0;
		cp += 2;
		for (majdev = 0; majdev < sizeof(devname)/sizeof(devname[0]);
		    majdev++) {
			if (cp[0] == devname[majdev][0] &&
			    cp[1] == devname[majdev][1]) {
				bootdev = MAKEBOOTDEV(majdev, 0, 0, unit, part);
				return;
			}
		}
		goto defdev;
	}
E 10
	for (majdev = 0; majdev < sizeof(devname)/sizeof(devname[0]); majdev++)
		if (cp[0] == devname[majdev][0] &&
		    cp[1] == devname[majdev][1] &&
		    cp[2] == '(')
			goto fndmaj;
defdev:
	bootdev = B_DEVMAGIC;
	return;

fndmaj:
	for (ctrl = 0, cp += 3; *cp >= '0' && *cp <= '9'; )
		ctrl = ctrl * 10 + *cp++ - '0';
	if (*cp == ',')
		cp++;
	for (unit = 0; *cp >= '0' && *cp <= '9'; )
		unit = unit * 10 + *cp++ - '0';
	if (*cp == ',')
		cp++;
	for (part = 0; *cp >= '0' && *cp <= '9'; )
		part = part * 10 + *cp++ - '0';
	if (*cp != ')')
		goto defdev;
D 3
	bootdev = (majdev << B_TYPESHIFT) |
		(ctrl << B_CONTROLLERSHIFT) |
		(unit << B_UNITSHIFT) |
		(part << B_PARTITIONSHIFT);
E 3
I 3
	bootdev = MAKEBOOTDEV(majdev, 0, ctrl, unit, part);
E 3
}
E 1
