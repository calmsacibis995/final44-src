/* 
 * Mach Operating System
 * Copyright (c) 1992 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	setroot.c,v $
 * Revision 2.9  93/03/11  13:47:19  danner
 * 	u_long -> u_int
 * 	[93/03/09            danner]
 * 
 * Revision 2.8  92/04/01  19:36:28  rpd
 * 	Changed to use machine-independent safe_gets.
 * 	[92/03/31            rpd]
 * 
 * Revision 2.7  91/06/19  17:20:26  rvb
 * 	gets() defined in kern/printf strikes again.
 * 
 * Revision 2.6  91/06/19  12:01:44  rvb
 * 	a kinder gentler setroot
 * 	[91/06/18  21:37:37  rvb]
 * 
 * 	Fix setroot for scsi device.
 * 	[91/06/11            rvb]
 * 	Support for VaxStation 3100: use rz disk and two digit
 * 	unit number
 * 	[91/06/04            rvb]
 * 
 * Revision 2.5  91/05/08  13:24:21  dbg
 * 	Move root_name string out of text segment (for standard C).
 * 	[91/04/16            dbg]
 * 
 * Revision 2.4  90/08/27  22:14:21  dbg
 * 	Echo character returned by cngetc.
 * 	[90/07/20            dbg]
 * 
 * Revision 2.3  90/01/11  11:46:30  dbg
 * 	De-linted.
 * 	[90/01/03            dbg]
 * 
 * Revision 2.2  89/11/29  14:16:47  af
 * 	Made root_name a pointer rather than an array, so that it
 * 	can be changed more easily.
 * 	[89/10/28  16:22:45  af]
 * 
 */
#include <platforms.h>

#include <mba.h>
#include <uba.h>

#include <hp.h>
#include <rk.h>
#include <ra.h>
#include <up.h>
#include <rb.h>
#include <rl.h>
#include <scsi.h>

/*
 * Set root device - from BSD autoconf
 */
#include <sys/types.h>
#include <sys/reboot.h>

#include <vax/cpu_data.h>

#if	NMBA > 0
#include <vaxmba/mbavar.h>
#endif	NMBA > 0
#if	NUBA > 0
#include <vaxuba/ubavar.h>
#endif	NUBA > 0
#if	NSCSI > 0
#include <chips/busses.h>
#endif

dev_t	rootdev = NODEV;
u_int	bootdev;		/* should be dev_t, but not until 32 bits */

static	char devname[][2] = {
	'h','p',	/* 0 = hp */
	0,0,		/* 1 = ht */
	'u','p',	/* 2 = up */
	'r','k',	/* 3 = hk */
	0,0,		/* 4 = sw */
	0,0,		/* 5 = tm */
	0,0,		/* 6 = ts */
	0,0,		/* 7 = mt */
	0,0,		/* 8 = tu */
	'r','a',	/* 9 = ra */
	0,0,		/* 10 = ut */
	'r','b',	/* 11 = rb */
	0,0,		/* 12 = rx */
	0,0,		/* 13 = uu */
	'r','l',	/* 14 = rl */
	0,0,		/* 15 = ?? */
	0,0,		/* 16 = ?? */
	0,0,		/* 17 = ?? */
	0,0,		/* 18 = ?? */
	0,0,		/* 19 = ?? */
	0,0,		/* 20 = ?? */
	'r','z',	/* 21 = rz */
};

#define	PARTITIONMASK	0x7
#define	PARTITIONSHIFT	3

/*
 * Attempt to find the device from which we were booted.
 * If we can do so, and not instructed not to do so,
 * change rootdev to correspond to the load device.
 */
dev_t
setroot(str)
register char *str;
{
	int  majdev, mindev, unit, part, adaptor;
	int i;
	int ctlr;

	if (boothowto & RB_DFLTROOT ||
	    (bootdev & B_MAGICMASK) != (u_int)B_DEVMAGIC)
		return;

	majdev = B_TYPE(bootdev);
	if (majdev > sizeof(devname) / sizeof(devname[0]))
		return;

	adaptor = B_ADAPTOR(bootdev);
	part = B_PARTITION(bootdev);
	unit = B_UNIT(bootdev);

	if (!(ctlr = B_CONTROLLER(bootdev))) {
		ctlr = unit >> 3;
		unit = unit & 07;
	}

	if (majdev == 0) {	/* MBA device */
#if NMBA > 0
		register struct mba_device *mbap;
		int mask;

/*
 * The MBA number used at boot time is not necessarily the same as the
 * MBA number used by the kernel.  In order to change the rootdev we need to
 * convert the boot MBA number to the kernel MBA number.  The address space
 * for an MBA used by the boot code is 0x20010000 + 0x2000 * MBA_number
 * on the 78? and 86?0, 0xf28000 + 0x2000 * MBA_number on the 750.
 * Therefore we can search the mba_hd table for the MBA that has the physical
 * address corresponding to the boot MBA number.
 */
#define	PHYSADRSHFT	13
#define	PHYSMBAMASK780	0x7
#define	PHYSMBAMASK750	0x3

		switch (cpu) {

		case VAX_780:
		case VAX_8600:
		default:
			mask = PHYSMBAMASK780;
			break;

		case VAX_750:
			mask = PHYSMBAMASK750;
			break;
		}
		for (mbap = mbdinit; mbap->mi_driver; mbap++)
			if (mbap->mi_alive && mbap->mi_drive == unit &&
			    (((long)mbap->mi_hd->mh_physmba >> PHYSADRSHFT)
			      & mask) == adaptor)
			    	break;
		if (mbap->mi_driver == 0)
			return;
		mindev = mbap->mi_unit;
#else
		return;
#endif
	}
#if	NSCSI > 0
	  else if (cpu == VAX_3100) {
/*
 *	actually
 *		mindev = (ctlr << 3) + unit;
 */
		register struct bus_device *ui;

		for (ui = bus_device_init; ui->driver; ui++)
			if (ui->alive && ui->slave == unit &&
			   ui->ctlr == ctlr &&
/*			   (ui->adaptor == adaptor || ui->adaptor == '?') && */
			   ui->name[0] == devname[majdev][0] &&
			   ui->name[1] == devname[majdev][1])
				break;
		if (ui->driver == 0)
			return;
		mindev = ui->unit;
	  }
#endif	NSCSI > 0
	   else {
		register struct uba_device *ubap;

		for (ubap = ubdinit; ubap->ui_driver; ubap++)
			if (ubap->ui_alive && ubap->ui_slave == unit &&
			   ubap->ui_mi->um_ctlr == ctlr &&
			   ubap->ui_ubanum == adaptor &&
			   ubap->ui_driver->ud_dname[0] == devname[majdev][0] &&
			   ubap->ui_driver->ud_dname[1] == devname[majdev][1])
			    	break;

		if (ubap->ui_driver == 0)
			return;
		mindev = ubap->ui_unit;
	}
	mindev = (mindev << PARTITIONSHIFT) + part;

	*str++ = devname[majdev][0];
	*str++ = devname[majdev][1];
	if ((i = mindev >> PARTITIONSHIFT) <= 9) 
		*str++ = '0' + i;
	else {
		*str++ = '0' + (i/10);
		*str++ = '0' + (i%10);
	}
	*str++ = part + 'a';
	*str++ = 0;
	return makedev(majdev, mindev);

}


/*
 * Generic configuration;  all in one
 */

#if	NHP > 0
extern struct mba_driver hpdriver;
#endif	NHP
#if	NSC > 0
extern struct uba_driver scdriver;
#endif	NSC
#if	NHK > 0
extern struct uba_driver hkdriver;
#endif	NHK
#if	NIDC > 0
extern struct uba_driver idcdriver;
#endif	NIDC
#if	NHL > 0
extern struct uba_driver hldriver;
#endif	NHL
#if	NUDA > 0
extern struct uba_driver udadriver;
#endif	NUDA
#if	NSCSI > 0
extern struct bus_driver sci_driver;
#endif

struct	genericconf {
	caddr_t	gc_driver;
	char	*gc_name;
	dev_t	gc_root;
} genericconf[] = {

#if	NHP > 0
	{ (caddr_t)&hpdriver,	"hp",	makedev( 0, 0), },
#endif	NHP
#if	NSC > 0
	{ (caddr_t)&scdriver,	"up",	makedev( 2, 0), },
#endif	NSC
#if	NUDA > 0
	{ (caddr_t)&udadriver,	"ra",	makedev( 9, 0), },
#endif	NUDA
#if	NIDC > 0
	{ (caddr_t)&idcdriver,	"rb",	makedev(11, 0), },
#endif	NIDC
#if	NHL > 0
	{ (caddr_t)&hldriver,	"rl",	makedev(14, 0), },
#endif	NHL
#if	NHK > 0
	{ (caddr_t)&hkdriver,	"hk",	makedev( 3, 0), },
	{ (caddr_t)&hkdriver,	"rk",	makedev( 3, 0),	},
#endif	NHK
#if	NSCSI > 0
	{ (caddr_t)&sci_driver,	"rz",	makedev(21, 0),	},
#endif
	{ 0 },
};

setconf(new_root, str)
dev_t new_root;
char *str;
{
	register struct genericconf *gc;
	int unit = 0;
	int slice = 0;
	char name[128];
	int i = 2;

	if (rootdev != NODEV)
		goto doswap;
	if (boothowto & RB_ASKNAME) {
retry:
		printf("root device [%s]? ", str);
		safe_gets(name, sizeof name);
		if (*name == 0) {
			rootdev = new_root;
			return;
		}

		for (gc = genericconf; gc->gc_driver; gc++)
			if (gc->gc_name[0] == name[0] &&
			    gc->gc_name[1] == name[1])
				goto gotit;
		goto bad;
gotit:
		/*
		 * Syntax is: dvNP with
		 *	dv = 2 letters for the device
		 *	N  = decimal number (1|2 digits) for the unit
		 *	P  = 1 letter (a..h) for the partition
		 */
		if (name[i] >= '0' && name[i] <= '9') {
			/* two digits for unit ? */
			if (name[i+1] >= '0' && name[i+1] <= '9') {
				unit = (name[i] - '0') * 10;
				i++;
			}
			unit += name[i] - '0';
			if (name[++i] >= 'a' && name[i] <= 'h') {
				slice = name[i] - 'a';
			} else if (name[i]) {
				printf("bad partition number\n");
				goto bad;
			}

			goto found;
		}
		printf("bad/missing unit number\n");
bad:
		for (gc = genericconf; gc->gc_driver; gc++)
			printf("%s%s%%d",
			       (gc == genericconf)?"use ":
				    (((gc+1)->gc_driver)?", ":" or "),
			       gc->gc_name);
		printf("\n");
		goto retry;
	}
	unit = 0;
	for (gc = genericconf; gc->gc_driver; gc++) {
#if	NMBA > 0
	    {
		register struct mba_device *mi;

		for (mi = mbdinit; mi->mi_driver; mi++) {
			if (mi->mi_alive == 0)
				continue;
			if (mi->mi_unit == 0 && mi->mi_driver ==
			    (struct mba_driver *)gc->gc_driver) {
				printf("root on %s0\n",
				    mi->mi_driver->md_dname);
				goto found;
			}
		}
	    }
#endif	NMBA > 0
#if	NUBA > 0
	    {
		register struct uba_device *ui;

		for (ui = ubdinit; ui->ui_driver; ui++) {
			if (ui->ui_alive == 0)
				continue;
			if (ui->ui_unit == 0 && ui->ui_driver ==
			    (struct uba_driver *)gc->gc_driver) {
				printf("root on %s0\n",
				    ui->ui_driver->ud_dname);
				goto found;
			}
		}
	    }
#endif	NUBA > 0
#if	NSCSI > 0
	    {
		register struct bus_device *ui;

		for (ui = bus_device_init; ui->driver; ui++) {
			if (ui->alive == 0)
				continue;
			if (ui->unit == 0 && ui->driver ==
			    (struct bus_driver *)gc->gc_driver) {
				printf("root on %s0\n",
				    ui->driver->dname);
				goto found;
			}
		}
	    }
#endif
	}
	printf("no suitable root\n");
	asm("halt");
found:
	gc->gc_root = makedev(major(gc->gc_root), unit*8+slice);
	rootdev = gc->gc_root;

	bcopy(name, str, i);
	str[i++] = 'a' + slice;
	str[i] = 0;
doswap:
	;
}

char	root_name_string[16] = "\0\0\0\0\0\0\0";	/* at least ddNNp */
char	*root_name = root_name_string;

get_root_device()
{
	register int	root_major, root_minor;
	register char	*name;
	dev_t		new_root = setroot(root_name);

	if ((boothowto & RB_ASKNAME) == 0) {
		printf("Changing root device to %s\n",
			root_name_string);
		rootdev = new_root;
		return;
	}
	setconf(new_root, root_name);
}
