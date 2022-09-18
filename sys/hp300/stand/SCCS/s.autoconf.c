h56603
s 00002/00002/00217
d D 8.1 93/06/10 21:46:24 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00214
d D 7.8 92/12/26 16:49:42 hibler 8 7
c Utah update (mostly disklabels)
e
s 00006/00006/00210
d D 7.7 92/10/11 10:01:33 bostic 7 6
c make kernel includes standard
e
s 00081/00006/00135
d D 7.6 92/06/18 21:33:37 hibler 6 5
c merge with latest Utah version
e
s 00035/00056/00106
d D 7.5 91/05/07 10:05:53 hibler 5 4
c DIO-II support
e
s 00003/00003/00159
d D 7.4 90/12/16 16:39:05 bostic 4 3
c kernel reorg
e
s 00036/00004/00126
d D 7.3 90/10/24 14:03:56 mckusick 3 2
c update from Mike Hibler
e
s 00032/00003/00098
d D 7.2 90/05/25 16:17:20 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00101/00000/00000
d D 7.1 90/05/08 22:45:59 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: autoconf.c 1.9 89/10/07$
E 5
I 5
D 6
 * from: Utah $Hdr: autoconf.c 1.13 91/01/21$
E 6
I 6
 * from: Utah $Hdr: autoconf.c 1.16 92/05/29$
E 6
E 5
 *
 *	%W% (Berkeley) %G%
 */

D 7
#include "samachdep.h"
I 6
#include "rominfo.h"
E 6
D 4
#include "param.h"
E 4
I 4
#include "sys/param.h"
I 6
#include "sys/reboot.h"
E 7
I 7
#include <hp300/stand/samachdep.h>
#include <hp300/stand/rominfo.h>
#include <sys/param.h>
#include <sys/reboot.h>
E 7
E 6
E 4

D 4
#include "../hpdev/device.h"
#include "../hpdev/grfvar.h"
E 4
I 4
D 6
#include "../dev/device.h"
#include "../dev/grfvar.h"
E 6
I 6
D 7
#include "hp/dev/device.h"
#include "hp/dev/grfreg.h"
E 7
I 7
#include <hp/dev/device.h>
#include <hp/dev/grfreg.h>
E 7
E 6
E 4

I 6
/*
 * Mapping of ROM MSUS types to BSD major device numbers
 * WARNING: major numbers must match bdevsw indices in hp300/conf.c.
 */
char rom2mdev[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/* 0-13: none */
	4,	/* 14: SCSI disk */
	0,	/* 15: none */
	2,	/* 16: CS/80 device on HPIB */
	2,	/* 17: CS/80 device on HPIB */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/* 18-31: none */
};

E 6
D 5
struct hp_hw sc_table[MAX_CTLR];
E 5
I 5
struct hp_hw sc_table[MAXCTLRS];
I 6
int cpuspeed;
E 6
E 5

I 2
extern int internalhpib;

#if 0
D 6
#include "rominfo.h"
E 6
printrominfo()
{
	struct rominfo *rp = (struct rominfo *)ROMADDR;
I 6

E 6
	printf("boottype %x, name %s, lowram %x, sysflag %x\n",
	       rp->boottype, rp->name, rp->lowram, rp->sysflag&0xff);
	printf("rambase %x, ndrives %x, sysflag2 %x, msus %x\n",
	       rp->rambase, rp->ndrives, rp->sysflag2&0xff, rp->msus);
}
#endif

E 2
configure()
{
I 6
	u_long msustobdev();

	switch (machineid) {
	case HP_320:
	case HP_330:
	case HP_340:
		cpuspeed = MHZ_16;
		break;
	case HP_350:
	case HP_360:
		cpuspeed = MHZ_25;
		break;
	case HP_370:
		cpuspeed = MHZ_33;
		break;
	case HP_375:
		cpuspeed = MHZ_50;
		break;
	case HP_380:
		cpuspeed = MHZ_25 * 2;	/* XXX */
		break;
D 8
	default:	/* assume the slowest */
		cpuspeed = MHZ_16;
E 8
I 8
	case HP_433:
		cpuspeed = MHZ_33 * 2;	/* XXX */
		break;
	default:	/* assume the fastest (largest delay value) */
		cpuspeed = MHZ_50;
E 8
		break;
	}
E 6
	find_devs();
	cninit();
I 2
#if 0
	printrominfo();
#endif
E 2
	hpibinit();
	scsiinit();
I 6
	if ((bootdev & B_MAGICMASK) != B_DEVMAGIC)
		bootdev = msustobdev();
E 6
}

I 6
/*
 * Convert HP MSUS to a valid bootdev layout:
 *	TYPE comes from MSUS device type as mapped by rom2mdev
 *	PARTITION is set to 0 ('a')
 *	UNIT comes from MSUS unit (almost always 0)
 *	CONTROLLER comes from MSUS primary address
 *	ADAPTOR comes from SCSI/HPIB driver logical unit number
 *		(passed back via unused hw_pa field)
 */
u_long
msustobdev()
{
	struct rominfo *rp = (struct rominfo *) ROMADDR;
	u_long bdev = 0;
	register struct hp_hw *hw;
	int sc;

	sc = (rp->msus >> 8) & 0xFF;
	for (hw = sc_table; hw < &sc_table[MAXCTLRS]; hw++)
		if (hw->hw_sc == sc)
			break;
	bdev |= rom2mdev[(rp->msus >> 24) & 0x1F] << B_TYPESHIFT;
	bdev |= 0 << B_PARTITIONSHIFT;
	bdev |= ((rp->msus >> 16) & 0xFF) << B_UNITSHIFT;
	bdev |= (rp->msus & 0xFF) << B_CONTROLLERSHIFT;
	bdev |= (int)hw->hw_pa << B_ADAPTORSHIFT;
	bdev |= B_DEVMAGIC;
#if 0
	printf("msus %x -> bdev %x\n", rp->msus, bdev);
#endif
	return (bdev);
}

E 6
sctoaddr(sc)
	int sc;
{
D 2
	extern int internalhpib;

E 2
D 3
	if (sc == -2)
		return(0x1000000);
E 3
	if (sc == -1)
		return(GRFIADDR);
D 2
	if (sc == 7)
E 2
I 2
	if (sc == 7 && internalhpib)
E 2
		return(internalhpib);
	if (sc < 32)
D 5
		return(0x600000+(0x10000*sc));
I 3
	if (sc >= 132 && sc < 134)
		return(0x1000000+((sc-132)*0x400000));
E 5
I 5
		return(DIOBASE + sc * DIOCSIZE);
	if (sc >= 132)
		return(DIOIIBASE + (sc - 132) * DIOIICSIZE);
E 5
E 3
	return(sc);
}

/*
D 3
 * Probe all select codes (0 - 32) and internal display address.
E 3
I 3
D 5
 * Probe all DIO select codes (0 - 32), the internal display address,.
 * and DIO-II select codes 132 (hack) and 133 (hack).
E 5
I 5
 * Probe all DIO select codes (0 - 32), the internal display address,
 * and DIO-II select codes (132 - 256).
E 5
 *
E 3
 * Note that we only care about displays, SCSIs and HP-IBs.
 */
find_devs()
{
I 5
	short sc, sctop;
E 5
	u_char *id_reg;
D 5
	register short sc;
	register int addr;
E 5
I 5
	register caddr_t addr;
E 5
	register struct hp_hw *hw;
I 5
D 6
	extern int machineid;
E 6
E 5

	hw = sc_table;
D 3
	for (sc = -2; sc < 32; sc++) {
E 3
I 3
D 5
	for (sc = -1; sc < 32; sc++) {
E 3
		addr = sctoaddr(sc);
E 5
I 5
	sctop = machineid == HP_320 ? 32 : 256;
	for (sc = -1; sc < sctop; sc++) {
		if (sc >= 32 && sc < 132)
			continue;
		addr = (caddr_t) sctoaddr(sc);
E 5
		if (badaddr(addr))
			continue;

		id_reg = (u_char *) addr;
D 5
		hw->hw_addr = (char *) addr;
		hw->hw_id = id_reg[1] & 0xff;
E 5
I 5
D 6
		hw->hw_pa = addr;
E 6
I 6
		hw->hw_pa = 0;	/* XXX used to pass back LUN from driver */
E 6
		if (sc >= 132)
			hw->hw_size = (id_reg[0x101] + 1) * 0x100000;
		else
			hw->hw_size = DIOCSIZE;
		hw->hw_kva = addr;
		hw->hw_id = id_reg[1];
E 5
		hw->hw_sc = sc;

I 2
		/*
		 * Not all internal HP-IBs respond rationally to id requests
		 * so we just go by the "internal HPIB" indicator in SYSFLAG.
		 */
		if (sc == 7 && internalhpib) {
D 5
			hw->hw_type = HPIB;
E 5
I 5
			hw->hw_type = C_HPIB;
E 5
			hw++;
			continue;
		}

E 2
		switch (hw->hw_id) {
I 2
		case 5:		/* 98642A */
D 5
		case 128+5:	/* 98642A remote */
			hw->hw_type = COMMDCM;
E 5
I 5
		case 5+128:	/* 98642A remote */
			hw->hw_type = D_COMMDCM;
E 5
			break;
E 2
		case 8:		/* 98625B */
		case 128:	/* 98624A */
D 5
			hw->hw_type = HPIB;
E 5
I 5
			hw->hw_type = C_HPIB;
E 5
			break;
		case 57:	/* Displays */
D 5
			hw->hw_type = BITMAP;
			hw->hw_id2 = id_reg[0x15];
			switch (hw->hw_id2) {
E 5
I 5
			hw->hw_type = D_BITMAP;
			hw->hw_secid = id_reg[0x15];
			switch (hw->hw_secid) {
E 5
			case 4:	/* renaissance */
			case 8: /* davinci */
				sc++;		/* occupy 2 select codes */
				break;
			}
			break;
		case 9:
D 5
			hw->hw_type = KEYBOARD;
E 5
I 5
			hw->hw_type = D_KEYBOARD;
E 5
			break;
		case 7:
D 5
		case 39:
		case 71:
		case 103:
			hw->hw_type = SCSI;
E 5
I 5
		case 7+32:
		case 7+64:
		case 7+96:
			hw->hw_type = C_SCSI;
E 5
I 3
			break;
		default:	/* who cares */
D 5
			hw->hw_type = MISC;
			break;
		}
		hw++;
	}
	/*
	 * Look for displays in DIO-II space
	 */
	for (sc = 132; sc < 134; sc++) {
		addr = sctoaddr(sc);
		if (badaddr(addr))
			continue;

		id_reg = (u_char *) addr;
		hw->hw_addr = (char *) addr;
		hw->hw_id = id_reg[1] & 0xff;
		hw->hw_sc = sc;

		switch (hw->hw_id) {
		case 57:	/* Displays */
			hw->hw_type = BITMAP;
			hw->hw_id2 = id_reg[0x15];
			switch (hw->hw_id2) {
			case 4:	/* renaissance */
			case 8: /* davinci */
				sc++;		/* occupy 2 select codes */
				break;
			}
E 3
			break;
		default:	/* who cares */
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
		}
		hw++;
	}
}
E 1
