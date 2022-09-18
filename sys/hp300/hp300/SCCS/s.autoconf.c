h64846
s 00021/00006/01014
d D 8.2 94/01/12 14:36:51 hibler 13 12
c handle "reverse priority" searches of SCSI devices (like HP boot ROM).
e
s 00002/00002/01018
d D 8.1 93/06/10 21:40:19 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00037/01020
d D 7.11 93/05/09 20:04:37 hibler 11 10
c concatonated disk support moved to cd.c
e
s 00003/00003/01054
d D 7.10 93/04/19 18:07:12 torek 10 9
c terminate swap list with NODEV, not 0 (0 is a valid device!)
e
s 00002/00002/01055
d D 7.9 92/12/27 09:44:02 hibler 9 8
c cpuspeed starts at 0
e
s 00016/00016/01041
d D 7.8 92/10/11 09:42:29 bostic 8 7
c make kernel includes standard
e
s 00000/00009/01057
d D 7.7 92/06/24 09:20:49 bostic 7 6
c delete strcmp routine, now in libkern
e
s 00036/00019/01030
d D 7.6 92/06/05 15:37:03 hibler 6 5
c merge latest Utah hp300 code including 68040 support
e
s 00267/00141/00782
d D 7.5 91/05/07 10:02:54 hibler 5 4
c DIO-II support
e
s 00013/00013/00910
d D 7.4 90/12/16 16:35:51 bostic 4 3
c kernel reorg
e
s 00008/00032/00915
d D 7.3 90/12/05 18:53:25 mckusick 3 2
c update from Mike Hibler for new VM and other machine support
e
s 00048/00018/00899
d D 7.2 90/05/25 15:48:53 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00917/00000/00000
d D 7.1 90/05/08 18:09:05 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 12
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 5
 * from: Utah $Hdr: autoconf.c 1.25 89/10/07$
E 5
I 5
D 6
 * from: Utah $Hdr: autoconf.c 1.31 91/01/21$
E 6
I 6
D 9
 * from: Utah $Hdr: autoconf.c 1.35 92/01/22$
E 9
I 9
 * from: Utah $Hdr: autoconf.c 1.36 92/12/20$
E 9
E 6
E 5
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

D 4
#include "param.h"
#include "systm.h"
#include "map.h"
#include "buf.h"
#include "dkstat.h"
D 3
#include "vm.h"
E 3
#include "conf.h"
#include "dmap.h"
#include "reboot.h"
E 4
I 4
D 8
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/map.h"
#include "sys/buf.h"
#include "sys/dkstat.h"
#include "sys/conf.h"
#include "sys/dmap.h"
#include "sys/reboot.h"
E 8
I 8
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/dkstat.h>
#include <sys/conf.h>
#include <sys/dmap.h>
#include <sys/reboot.h>
E 8
E 4

I 5
D 8
#include "../include/vmparam.h"
E 5
D 3
#include "pte.h"
E 3
D 4
#include "cpu.h"
E 4
I 4
#include "../include/cpu.h"
I 5
#include "pte.h"
E 5
E 4
#include "isr.h"
D 4
#include "../hpdev/device.h"
#include "../hpdev/grfioctl.h"
#include "../hpdev/grfvar.h"
E 4
I 4
D 6
#include "../dev/device.h"
#include "../dev/grfioctl.h"
#include "../dev/grfvar.h"
E 6
I 6
#include "hp/dev/device.h"
#include "hp/dev/grfreg.h"
#include "hp/dev/hilreg.h"
E 8
I 8
#include <machine/vmparam.h>
#include <machine/cpu.h>
#include <hp300/hp300/pte.h>
#include <hp300/hp300/isr.h>
#include <hp/dev/device.h>
#include <hp/dev/grfreg.h>
#include <hp/dev/hilreg.h>
E 8
E 6
E 4

/*
 * The following several variables are related to
 * the configuration process, and are used in initializing
 * the machine.
 */
int	cold;		    /* if 1, still working on cold-start */
int	dkn;		    /* number of iostat dk numbers assigned so far */
D 9
int	cpuspeed = MHZ_8;   /* relative cpu speed */
E 9
I 9
int	cpuspeed = 0;	    /* relative cpu speed -- can be patched */	
E 9
struct	isr isrqueue[NISR];
D 5
struct	hp_hw sc_table[MAX_CTLR];
E 5
I 5
struct	hp_hw sc_table[MAXCTLRS];
E 5

I 2
D 5
extern	int internalhpib;
E 5
I 5
/* XXX must be allocated statically because of early console init */
struct	map extiomap[EIOMAPSIZE/16];
E 5

I 5
extern	caddr_t internalhpib;
extern	char *extiobase;

E 5
E 2
#ifdef DEBUG
int	acdebug = 0;
#endif

/*
 * Determine mass storage and memory configuration for a machine.
 */
configure()
{
	register struct hp_hw *hw;
	int found;

	/*
	 * XXX: these should be consolidated into some kind of table
	 */
D 6
	hilinit();
E 6
I 6
	hilsoftinit(0, HILADDR);
	hilinit(0, HILADDR);
E 6
	isrinit();
	dmainit();

	/*
	 * Look over each hardware device actually found and attempt
	 * to match it with an ioconf.c table entry.
	 */
	for (hw = sc_table; hw->hw_type; hw++) {
D 5
		if (hw->hw_type & CONTROLLER)
E 5
I 5
		if (HW_ISCTLR(hw))
E 5
			found = find_controller(hw);
		else
			found = find_device(hw);
#ifdef DEBUG
		if (!found) {
D 5
			int sc = addrtosc((u_int)hw->hw_addr);
E 5
I 5
			int sc = patosc(hw->hw_pa);
E 5

D 5
			printf("unconfigured %s ", hw->hw_name);
E 5
I 5
			printf("unconfigured card id %x ", hw->hw_id);
E 5
			if (sc < 256)
				printf("at sc%d\n", sc);
			else
				printf("csr at %x\n", sc);
		}
#endif
	}

D 11
#include "cd.h"
#if NCD > 0
	/*
	 * Now deal with concatenated disks
	 */
	find_cdevices();
#endif

E 11
#if GENERIC
	if ((boothowto & RB_ASKNAME) == 0)
		setroot();
	setconf();
#else
	setroot();
#endif
	swapconf();
	cold = 0;
}

#define dr_type(d, s)	\
D 2
	((d)->d_name[0] == (s)[0] && (d)->d_name[1] == (s)[1])
E 2
I 2
	(strcmp((d)->d_name, (s)) == 0)
E 2

#define same_hw_ctlr(hw, hc) \
D 5
	((hw)->hw_type == HPIB && dr_type((hc)->hp_driver, "hpib") || \
	 (hw)->hw_type == SCSI && dr_type((hc)->hp_driver, "scsi"))
E 5
I 5
	(HW_ISHPIB(hw) && dr_type((hc)->hp_driver, "hpib") || \
	 HW_ISSCSI(hw) && dr_type((hc)->hp_driver, "scsi"))
E 5

find_controller(hw)
	register struct hp_hw *hw;
{
	register struct hp_ctlr *hc;
	struct hp_ctlr *match_c;
	caddr_t oaddr;
	int sc;

#ifdef DEBUG
	if (acdebug)
D 5
		printf("find_controller: hw: %s at sc%d (%x), type %x...",
		       hw->hw_name, hw->hw_sc, hw->hw_addr, hw->hw_type);
E 5
I 5
		printf("find_controller: hw: id%x at sc%d (%x), type %x...",
		       hw->hw_id, hw->hw_sc, hw->hw_kva, hw->hw_type);
E 5
#endif
	sc = hw->hw_sc;
	match_c = NULL;
	for (hc = hp_cinit; hc->hp_driver; hc++) {
		if (hc->hp_alive)
			continue;
		/*
		 * Make sure we are looking at the right
		 * controller type.
		 */
		if (!same_hw_ctlr(hw, hc))
			continue;
		/*
		 * Exact match; all done
		 */
		if ((int)hc->hp_addr == sc) {
			match_c = hc;
			break;
		}
		/*
		 * Wildcard; possible match so remember first instance
		 * but continue looking for exact match.
		 */
D 5
		if ((int)hc->hp_addr == WILD_CARD_CTLR && match_c == NULL)
E 5
I 5
		if (hc->hp_addr == NULL && match_c == NULL)
E 5
			match_c = hc;
	}
#ifdef DEBUG
	if (acdebug) {
		if (match_c)
			printf("found %s%d\n",
			       match_c->hp_driver->d_name,
			       match_c->hp_unit);
		else
			printf("not found\n");
	}
#endif
	/*
	 * Didn't find an ioconf entry for this piece of hardware,
	 * just ignore it.
	 */
	if (match_c == NULL)
		return(0);
	/*
	 * Found a match, attempt to initialize and configure all attached
	 * slaves.  Note, we can still fail if HW won't initialize.
	 */
	hc = match_c;
	oaddr = hc->hp_addr;
D 5
	hc->hp_addr = hw->hw_addr;
E 5
I 5
	hc->hp_addr = hw->hw_kva;
E 5
	if ((*hc->hp_driver->d_init)(hc)) {
		hc->hp_alive = 1;
		printf("%s%d", hc->hp_driver->d_name, hc->hp_unit);
D 5
		sc = addrtosc((u_int)hc->hp_addr);
E 5
I 5
		sc = patosc(hw->hw_pa);
E 5
		if (sc < 256)
			printf(" at sc%d,", sc);
		else
			printf(" csr 0x%x,", sc);
		printf(" ipl %d", hc->hp_ipl);
		if (hc->hp_flags)
			printf(" flags 0x%x", hc->hp_flags);
		printf("\n");
		find_slaves(hc);
	} else
		hc->hp_addr = oaddr;
	return(1);
}

find_device(hw)
	register struct hp_hw *hw;
{
	register struct hp_device *hd;
	struct hp_device *match_d;
	caddr_t oaddr;
	int sc;

#ifdef DEBUG
	if (acdebug)
D 5
		printf("find_device: hw: %s at sc%d (%x), type %x...",
		       hw->hw_name, hw->hw_sc, hw->hw_addr, hw->hw_type);
E 5
I 5
		printf("find_device: hw: id%x at sc%d (%x), type %x...",
		       hw->hw_id, hw->hw_sc, hw->hw_kva, hw->hw_type);
E 5
#endif
	match_d = NULL;
	for (hd = hp_dinit; hd->hp_driver; hd++) {
		if (hd->hp_alive)
			continue;
		/* Must not be a slave */
		if (hd->hp_cdriver)
			continue;
		/*
		 * XXX: A graphics device that was found as part of the
		 * console init will have the hp_addr field already set
		 * (i.e. no longer the select code).  Gotta perform a
		 * slightly different check for an exact match.
		 */
D 5
		if (hw->hw_type == BITMAP && hd->hp_addr >= (caddr_t)IOBASE) {
E 5
I 5
		if (HW_ISDEV(hw, D_BITMAP) && hd->hp_addr >= intiobase) {
E 5
			/* must be an exact match */
D 5
			if (hd->hp_addr == hw->hw_addr) {
E 5
I 5
			if (hd->hp_addr == hw->hw_kva) {
E 5
				match_d = hd;
				break;
			}
			continue;
		}
		sc = (int) hd->hp_addr;
		/*
		 * Exact match; all done.
		 */
		if (sc > 0 && sc == hw->hw_sc) {
			match_d = hd;
			break;
		}
		/*
		 * Wildcard; possible match so remember first instance
		 * but continue looking for exact match.
		 */
		if (sc == 0 && same_hw_device(hw, hd) && match_d == NULL)
			match_d = hd;
	}
#ifdef DEBUG
	if (acdebug) {
		if (match_d)
			printf("found %s%d\n",
			       match_d->hp_driver->d_name,
			       match_d->hp_unit);
		else
			printf("not found\n");
	}
#endif
	/*
	 * Didn't find an ioconf entry for this piece
	 * of hardware, just ignore it.
	 */
	if (match_d == NULL)
		return(0);
	/*
	 * Found a match, attempt to initialize.
	 * Note, we can still fail if HW won't initialize.
	 */
	hd = match_d;
	oaddr = hd->hp_addr;
D 5
	hd->hp_addr = hw->hw_addr;
E 5
I 5
	hd->hp_addr = hw->hw_kva;
E 5
	if ((*hd->hp_driver->d_init)(hd)) {
		hd->hp_alive = 1;
		printf("%s%d", hd->hp_driver->d_name, hd->hp_unit);
D 5
		sc = addrtosc((u_int)hd->hp_addr);
E 5
I 5
		sc = patosc(hw->hw_pa);
E 5
D 3
		if (sc < 32)
E 3
I 3
		if (sc < 256)
E 3
			printf(" at sc%d", sc);
		else
			printf(" csr 0x%x", sc);
		if (hd->hp_ipl)
			printf(", ipl %d", hd->hp_ipl);
		if (hd->hp_flags)
			printf(", flags 0x%x", hd->hp_flags);
		printf("\n");
	} else
		hd->hp_addr = oaddr;
	return(1);
}

find_slaves(hc)
	struct hp_ctlr *hc;
{
	/*
	 * The SCSI bus is structured very much like the HP-IB 
	 * except that the host adaptor is slave 7 so we only want
	 * to look at the first 6 slaves.
	 */
	if (dr_type(hc->hp_driver, "hpib"))
D 13
		find_busslaves(hc, MAXSLAVES);
E 13
I 13
		find_busslaves(hc, 0, MAXSLAVES-1);
E 13
	else if (dr_type(hc->hp_driver, "scsi"))
D 13
		find_busslaves(hc, MAXSLAVES-1);
E 13
I 13
#ifdef SCSI_REVPRI
		/*
		 * Later releases of the HP boot ROM start searching for
		 * boot devices starting with slave 6 and working down.
		 * This is apparently the order in which priority is given
		 * to slaves on the host adaptor.
		 */
		find_busslaves(hc, MAXSLAVES-2, 0);
#else
		find_busslaves(hc, 0, MAXSLAVES-2);
#endif
E 13
}

/*
 * Search each BUS controller found for slaves attached to it.
 * The bad news is that we don't know how to uniquely identify all slaves
 * (e.g. PPI devices on HP-IB).  The good news is that we can at least
 * differentiate those from slaves we can identify.  At worst (a totally
 * wildcarded entry) this will cause us to locate such a slave at the first
 * unused position instead of where it really is.  To save grief, non-
 * identifing devices should always be fully qualified.
 */
D 13
find_busslaves(hc, maxslaves)
E 13
I 13
find_busslaves(hc, startslave, endslave)
E 13
	register struct hp_ctlr *hc;
D 13
	int maxslaves;
E 13
I 13
	int startslave, endslave;
E 13
{
	register int s;
	register struct hp_device *hd;
	struct hp_device *match_s;
	int new_s, new_c, old_s, old_c;
	int rescan;
	
I 13
#define NEXTSLAVE(s) (startslave < endslave ? (s)++ : (s)--)
#define LASTSLAVE(s) (startslave < endslave ? (s)-- : (s)++)
E 13
#ifdef DEBUG
	if (acdebug)
		printf("find_busslaves: for %s%d\n",
		       hc->hp_driver->d_name, hc->hp_unit);
#endif
D 13
	for (s = 0; s < maxslaves; s++) {
E 13
I 13
	NEXTSLAVE(endslave);
	for (s = startslave; s != endslave; NEXTSLAVE(s)) {
E 13
		rescan = 1;
		match_s = NULL;
		for (hd = hp_dinit; hd->hp_driver; hd++) {
			/*
			 * Rule out the easy ones:
			 * 1. slave already assigned or not a slave
			 * 2. not of the proper type
			 * 3. controller specified but not this one
			 * 4. slave specified but not this one
			 */
			if (hd->hp_alive || hd->hp_cdriver == NULL)
				continue;
			if (!dr_type(hc->hp_driver, hd->hp_cdriver->d_name))
				continue;
			if (hd->hp_ctlr >= 0 && hd->hp_ctlr != hc->hp_unit)
				continue;
			if (hd->hp_slave >= 0 && hd->hp_slave != s)
				continue;
			/*
			 * Case 0: first possible match.
			 * Remember it and keep looking for better.
			 */
			if (match_s == NULL) {
				match_s = hd;
				new_c = hc->hp_unit;
				new_s = s;
				continue;
			}
			/*
			 * Case 1: exact match.
			 * All done.  Note that we do not attempt any other
			 * matches if this one fails.  This allows us to
			 * "reserve" locations for dynamic addition of
			 * disk/tape drives by fully qualifing the location.
			 */
			if (hd->hp_slave == s && hd->hp_ctlr == hc->hp_unit) {
				match_s = hd;
				rescan = 0;
				break;
			}
			/*
			 * Case 2: right controller, wildcarded slave.
			 * Remember first and keep looking for an exact match.
			 */
			if (hd->hp_ctlr == hc->hp_unit &&
			    match_s->hp_ctlr < 0) {
				match_s = hd;
				new_s = s;
				continue;
			}
			/*
			 * Case 3: right slave, wildcarded controller.
			 * Remember and keep looking for a better match.
			 */
			if (hd->hp_slave == s &&
			    match_s->hp_ctlr < 0 && match_s->hp_slave < 0) {
				match_s = hd;
				new_c = hc->hp_unit;
				continue;
			}
			/*
			 * OW: we had a totally wildcarded spec.
			 * If we got this far, we have found a possible
			 * match already (match_s != NULL) so there is no
			 * reason to remember this one.
			 */
			continue;
		}
		/*
		 * Found a match.  We need to set hp_ctlr/hp_slave properly
		 * for the init routines but we also need to remember all
		 * the old values in case this doesn't pan out.
		 */
		if (match_s) {
			hd = match_s;
			old_c = hd->hp_ctlr;
			old_s = hd->hp_slave;
			if (hd->hp_ctlr < 0)
				hd->hp_ctlr = new_c;
			if (hd->hp_slave < 0)
				hd->hp_slave = new_s;
#ifdef DEBUG
			if (acdebug)
				printf("looking for %s%d at slave %d...",
				       hd->hp_driver->d_name,
				       hd->hp_unit, hd->hp_slave);
#endif

			if ((*hd->hp_driver->d_init)(hd)) {
#ifdef DEBUG
				if (acdebug)
					printf("found\n");
#endif
				printf("%s%d at %s%d, slave %d",
				       hd->hp_driver->d_name, hd->hp_unit,
				       hc->hp_driver->d_name, hd->hp_ctlr,
				       hd->hp_slave);
				if (hd->hp_flags)
					printf(" flags 0x%x", hd->hp_flags);
				printf("\n");
				hd->hp_alive = 1;
				if (hd->hp_dk && dkn < DK_NDRIVE)
					hd->hp_dk = dkn++;
				else
					hd->hp_dk = -1;
				rescan = 1;
			} else {
#ifdef DEBUG
				if (acdebug)
					printf("not found\n");
#endif
				hd->hp_ctlr = old_c;
				hd->hp_slave = old_s;
			}
			/*
			 * XXX: This should be handled better.
			 * Re-scan a slave.  There are two reasons to do this.
			 * 1. It is possible to have both a tape and disk
			 *    (e.g. 7946) or two disks (e.g. 9122) at the
			 *    same slave address.  Here we need to rescan
			 *    looking only at entries with a different
			 *    physical unit number (hp_flags).
			 * 2. It is possible that an init failed because the
			 *    slave was there but of the wrong type.  In this
			 *    case it may still be possible to match the slave
			 *    to another ioconf entry of a different type.
			 *    Here we need to rescan looking only at entries
			 *    of different types.
			 * In both cases we avoid looking at undesirable
			 * ioconf entries of the same type by setting their
			 * alive fields to -1.
			 */
			if (rescan) {
				for (hd = hp_dinit; hd->hp_driver; hd++) {
					if (hd->hp_alive)
						continue;
					if (match_s->hp_alive == 1) {	/* 1 */
						if (hd->hp_flags == match_s->hp_flags)
							hd->hp_alive = -1;
					} else {			/* 2 */
						if (hd->hp_driver == match_s->hp_driver)
							hd->hp_alive = -1;
					}
				}
D 13
				s--;
E 13
I 13
				LASTSLAVE(s);
E 13
				continue;
			}
		}
		/*
		 * Reset bogon alive fields prior to attempting next slave
		 */
		for (hd = hp_dinit; hd->hp_driver; hd++)
			if (hd->hp_alive == -1)
				hd->hp_alive = 0;
	}
I 13
#undef NEXTSLAVE
#undef LASTSLAVE
E 13
}

D 5
sctoaddr(addr)
	register int addr;
E 5
I 5
caddr_t
sctopa(sc)
	register int sc;
E 5
{
D 2
	extern int internalhpib;

	if (addr == 7)
E 2
I 2
D 5
	if (addr == 7 && internalhpib)
E 5
I 5
	register caddr_t addr;

	if (sc == 7 && internalhpib)
E 5
E 2
		addr = internalhpib;
D 5
	else if (addr < 32)
		addr = IOV(EXTIOBASE + (addr * IOCARDSIZE));
E 5
I 5
	else if (sc < 32)
		addr = (caddr_t) (DIOBASE + sc * DIOCSIZE);
	else if (sc >= 132)
		addr = (caddr_t) (DIOIIBASE + (sc - 132) * DIOIICSIZE);
E 5
	else
D 5
		addr = IOV(addr);
E 5
I 5
		addr = 0;
E 5
	return(addr);
}

D 5
addrtosc(addr)
	register u_int addr;
E 5
I 5
patosc(addr)
	register caddr_t addr;
E 5
{
D 2
	extern int internalhpib;

E 2
D 3
#if defined(HP360) || defined(HP370)
	extern char grfregs[];

	if (addr == (u_int)grfregs)
		addr = 132;
	else
#endif
E 3
D 5
	if (addr == internalhpib)
		addr = 7;
	else if (addr >= IOV(IOBASE)) {
		addr = UNIOV(addr);
		if (addr >= EXTIOBASE)
			addr = (addr - EXTIOBASE) / IOCARDSIZE;
	}
E 5
I 5
	if (addr == (caddr_t)0x478000)
		return(7);
	if (addr >= (caddr_t)DIOBASE && addr < (caddr_t)DIOTOP)
		return(((unsigned)addr - DIOBASE) / DIOCSIZE);
	if (addr >= (caddr_t)DIOIIBASE && addr < (caddr_t)DIOIITOP)
		return(((unsigned)addr - DIOIIBASE) / DIOIICSIZE + 132);
E 5
	return((int)addr);
}

I 5
caddr_t
sctova(sc)
	register int sc;
{
	register struct hp_hw *hw;

	for (hw = sc_table; hw->hw_type; hw++)
		if (sc == hw->hw_sc)
			return(hw->hw_kva);
	return((caddr_t)sc);
}

vatosc(addr)
	register caddr_t addr;
{
	register struct hp_hw *hw;

	for (hw = sc_table; hw->hw_type; hw++)
		if (addr == hw->hw_kva)
			return(hw->hw_sc);
	return((int)addr);
}

E 5
same_hw_device(hw, hd)
	struct hp_hw *hw;
	struct hp_device *hd;
{
	int found = 0;

D 5
	switch (hw->hw_type) {
	case HPIB:
	case RD:
	case PPI:
	case CT:
E 5
I 5
	switch (hw->hw_type & ~B_MASK) {
	case C_HPIB:
E 5
		found = dr_type(hd->hp_driver, "hpib");
		break;
D 5
	case BITMAP:
E 5
I 5
	case C_SCSI:
		found = dr_type(hd->hp_driver, "scsi");
		break;
	case D_BITMAP:
E 5
		found = dr_type(hd->hp_driver, "grf");
		break;
D 5
	case NET:
E 5
I 5
	case D_LAN:
E 5
		found = dr_type(hd->hp_driver, "le");
		break;
D 2
	case COMM:
		found = dr_type(hd->hp_driver, "dca") ||
			dr_type(hd->hp_driver, "dcm");
E 2
I 2
D 5
	case COMMDCA:
E 5
I 5
	case D_COMMDCA:
E 5
		found = dr_type(hd->hp_driver, "dca");
E 2
		break;
I 2
D 5
	case COMMDCL:
E 5
I 5
	case D_COMMDCL:
E 5
		found = dr_type(hd->hp_driver, "dcl");
		break;
D 5
	case COMMDCM:
E 5
I 5
	case D_COMMDCM:
E 5
		found = dr_type(hd->hp_driver, "dcm");
		break;
E 2
D 5
	case SCSI:
		found = dr_type(hd->hp_driver, "scsi");
E 5
I 5
	default:
E 5
		break;
D 5
	case FPA:    /* Unsupported so far */
	case VME:
	case FLINK:
	case MISC:
		break;
E 5
	}
	return(found);
}

I 5
char notmappedmsg[] = "WARNING: no space to map IO card, ignored\n";

/*
 * Scan the IO space looking for devices.
 */
E 5
find_devs()
{
	short sc;
	u_char *id_reg;
D 5
	register int addr;
E 5
I 5
	register caddr_t addr;
E 5
	register struct hp_hw *hw;
I 5
	int didmap, sctop;
E 5

I 3
	/*
D 5
	 * XXX record actual address of internal HP-IB if present.
E 5
I 5
	 * Initialize IO resource map for iomap().
E 5
	 */
D 5
	if (internalhpib)
		internalhpib = IOV(INTERNALHPIB);

E 5
I 5
	rminit(extiomap, (long)EIOMAPSIZE, (long)1, "extio", EIOMAPSIZE/16);
E 5
E 3
	hw = sc_table;
D 5
	for (sc = -1; sc < 32; sc++) {
E 5
I 5
	/*
	 * Probe all select codes + internal display addr
	 */
	sctop = machineid == HP_320 ? 32 : 256;
	for (sc = -1; sc < sctop; sc++) {
E 5
D 3
#if defined(HP360) || defined(HP370)
E 3
		/*
D 3
		 * XXX: special check for bit-mapped display
		 * at SC132 in DIO II space on the 340.
		 */
		if (sc == -1 && machineid == HP_340) {
			extern struct pte Grfmap[];
			extern char grfregs[];

			physaccess(Grfmap, (caddr_t)DIOIIBASE,
				   DIOIICSIZE, PG_RW|PG_CI);
			addr = (int) grfregs;
			/*
			 * Nothing there or not a display,
			 * try the usual internal display address.
			 */
			if (badaddr((caddr_t)addr) ||
			    (((u_char *)addr)[1] & 0xff) != 57)
				addr = IOV(GRFIADDR);
		} else
#endif
		/*
E 3
D 5
		 * Probe all select codes + internal display addr
E 5
I 5
		 * Invalid select codes
E 5
		 */
D 5
		if (sc == -1)
			addr = IOV(GRFIADDR);
		else
			addr = sctoaddr(sc);
		if (badaddr((caddr_t)addr))
E 5
I 5
		if (sc >= 32 && sc < 132)
E 5
			continue;

I 5
		if (sc == -1) {
			hw->hw_pa = (caddr_t) GRFIADDR;
			addr = (caddr_t) IIOV(hw->hw_pa);
			didmap = 0;
		} else if (sc == 7 && internalhpib) {
			hw->hw_pa = (caddr_t) 0x478000;
			addr = internalhpib = (caddr_t) IIOV(hw->hw_pa);
			didmap = 0;
		} else {
			hw->hw_pa = sctopa(sc);
			addr = iomap(hw->hw_pa, NBPG);
			if (addr == 0) {
				printf(notmappedmsg);
				continue;
			}
			didmap = 1;
		}
		if (badaddr(addr)) {
			if (didmap)
				iounmap(addr, NBPG);
			continue;
		}
E 5
		id_reg = (u_char *) addr;
D 5
		hw->hw_id = id_reg[1] & 0xff;
E 5
I 5
		if (sc >= 132)
			hw->hw_size = (id_reg[0x101] + 1) * 0x100000;
		else
			hw->hw_size = DIOCSIZE;
		hw->hw_kva = addr;
		hw->hw_id = id_reg[1];
E 5
		hw->hw_sc = sc;
D 5
		hw->hw_addr = (char *) addr;
E 5
D 2

E 2
		/*
I 2
		 * Internal HP-IB on some machines (345/375) doesn't return
		 * consistant id info so we use the info gleaned from the
		 * boot ROMs SYSFLAG.
		 */
		if (sc == 7 && internalhpib) {
D 5
			hw->hw_name = "98624A";
			hw->hw_type = HPIB;
E 5
I 5
			hw->hw_type = C_HPIB;
E 5
			hw++;
			continue;
		}
		/*
E 2
		 * XXX: the following could be in a big static table
		 */
		switch (hw->hw_id) {
		/* Null device? */
		case 0:
			break;
I 5
		/* 98644A */
E 5
		case 2:
I 2
D 5
		case 128+2:
E 2
			hw->hw_name = "98626A";
D 2
			hw->hw_type = COMM;
E 2
I 2
			hw->hw_type = COMMDCA;
E 5
I 5
		case 2+128:
			hw->hw_type = D_COMMDCA;
E 5
E 2
			break;
I 5
		/* 98622A */
E 5
		case 3:
D 5
			hw->hw_name = "98622A";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
I 5
		/* 98623A */
E 5
		case 4:
D 5
			hw->hw_name = "98623A";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
I 5
		/* 98642A */
E 5
		case 5:
I 2
D 5
		case 128+5:
E 2
			hw->hw_name = "98642A";
D 2
			hw->hw_type = COMM;
E 2
I 2
			hw->hw_type = COMMDCM;
E 5
I 5
		case 5+128:
			hw->hw_type = D_COMMDCM;
E 5
E 2
			break;
I 5
		/* 345/375 builtin parallel port */
E 5
I 2
		case 6:
D 5
			hw->hw_name = "Parallel Port";
			hw->hw_type = PPORT;
E 5
I 5
			hw->hw_type = D_PPORT;
E 5
			break;
I 5
		/* 98625A */
E 5
E 2
		case 7:
D 5
		case 39:
		case 71:
		case 103:
			hw->hw_name = "98265A";
			hw->hw_type = SCSI;
E 5
I 5
		case 7+32:
		case 7+64:
		case 7+96:
			hw->hw_type = C_SCSI;
E 5
			break;
I 5
		/* 98625B */
E 5
		case 8:
D 5
			hw->hw_name = "98625B";
			hw->hw_type = HPIB;
E 5
I 5
			hw->hw_type = C_HPIB;
E 5
			break;
I 5
		/* 98287A */
E 5
		case 9:
D 5
			hw->hw_name = "98287A";
			hw->hw_type = KEYBOARD;
E 5
I 5
			hw->hw_type = D_KEYBOARD;
E 5
			break;
I 5
		/* 98635A */
E 5
		case 10:
D 5
			hw->hw_name = "98635A";
			hw->hw_type = FPA;
E 5
I 5
			hw->hw_type = D_FPA;
E 5
			break;
I 5
		/* timer */
E 5
		case 11:
D 5
			hw->hw_name = "Timer";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
I 5
		/* 98640A */
E 5
		case 18:
D 5
			hw->hw_name = "98640A";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
I 5
		/* 98643A */
E 5
D 2
		case 20:
			hw->hw_name = "98628A";
			hw->hw_type = COMM;
			break;
E 2
		case 21:
D 5
			hw->hw_name = "98643A";
			hw->hw_type = NET;
E 5
I 5
			hw->hw_type = D_LAN;
E 5
			break;
I 5
		/* 98659A */
E 5
		case 22:
D 5
			hw->hw_name = "98659A";
D 2
			hw->hw_type = COMM;
E 2
I 2
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
E 2
			break;
I 5
		/* 237 display */
E 5
		case 25:
D 5
			hw->hw_name = "237";
			hw->hw_type = BITMAP;
E 5
I 5
			hw->hw_type = D_BITMAP;
E 5
			break;
I 5
		/* quad-wide card */
E 5
		case 26:
D 5
			hw->hw_name = "Quad";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
			hw->hw_size *= 4;
			sc += 3;
E 5
			break;
I 5
		/* 98253A */
E 5
		case 27:
D 5
			hw->hw_name = "98253A";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
I 5
		/* 98627A */
E 5
		case 28:
D 5
			hw->hw_name = "98627A";
			hw->hw_type = BITMAP;
E 5
I 5
			hw->hw_type = D_BITMAP;
E 5
			break;
I 5
		/* 98633A */
E 5
		case 29:
D 5
			hw->hw_name = "98633A";
			hw->hw_type = BITMAP;
E 5
I 5
			hw->hw_type = D_BITMAP;
E 5
			break;
I 5
		/* 98259A */
E 5
		case 30:
D 5
			hw->hw_name = "98259A";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
I 5
		/* 8741 */
E 5
		case 31:
D 5
			hw->hw_name = "8741";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
I 5
		/* 98577A */
E 5
		case 49:
D 5
			hw->hw_name = "98577A";
			hw->hw_type = VME;
			sc++;
E 5
I 5
			hw->hw_type = C_VME;
			if (sc < 132) {
				hw->hw_size *= 2;
				sc++;
			}
E 5
			break;
I 5
		/* 98628A */
E 5
I 2
		case 52:
D 3
		case 180:
E 3
I 3
D 5
		case 128+52:
E 3
			hw->hw_name = "98628A";
			hw->hw_type = COMMDCL;
E 5
I 5
		case 52+128:
			hw->hw_type = D_COMMDCL;
E 5
			break;
I 5
		/* bitmap display */
E 5
E 2
		case 57:
D 5
			hw->hw_type = BITMAP;
			hw->hw_id2 = id_reg[0x15];
			switch (hw->hw_id2) {
E 5
I 5
			hw->hw_type = D_BITMAP;
			hw->hw_secid = id_reg[0x15];
			switch (hw->hw_secid) {
			/* 98700/98710 */
E 5
			case 1:
D 5
				hw->hw_name = "98700 ";
E 5
				break;
I 5
			/* 98544-547 topcat */
E 5
			case 2:
D 5
				hw->hw_name = "TOPCAT";
E 5
				break;
I 5
D 6
			/* 98720/721 */
E 6
I 6
			/* 98720/721 renassiance */
E 6
E 5
			case 4:
D 5
				hw->hw_name = "98720 ";
				sc++;
E 5
I 5
				if (sc < 132) {
					hw->hw_size *= 2;
					sc++;
				}
E 5
				break;
I 5
			/* 98548-98556 catseye */
E 5
			case 5:
			case 6:
			case 7:
			case 9:
D 5
				hw->hw_name = "CATSEYE";
E 5
				break;
I 5
D 6
			/* 98730/731 */
E 6
I 6
			/* 98730/731 davinci */
E 6
E 5
			case 8:
D 5
				hw->hw_name = "98730 ";
				sc++;
E 5
I 5
				if (sc < 132) {
					hw->hw_size *= 2;
					sc++;
				}
E 5
				break;
I 6
			/* A1096A hyperion */
			case 14:
				break;
E 6
I 5
			/* 987xx */
E 5
			default:
D 5
				hw->hw_name = "987xx ";
E 5
				break;
			}
			break;
I 5
		/* 98644A */
E 5
		case 66:
I 2
D 5
		case 128+66:
E 2
			hw->hw_name = "98644A";
D 2
			hw->hw_type = COMM;
E 2
I 2
			hw->hw_type = COMMDCA;
E 5
I 5
		case 66+128:
			hw->hw_type = D_COMMDCA;
E 5
E 2
			break;
I 5
		/* 98624A */
E 5
		case 128:
D 5
			hw->hw_name = "98624A";
			hw->hw_type = HPIB;
E 5
I 5
			hw->hw_type = C_HPIB;
E 5
			break;
		default:
D 5
			hw->hw_name = "DEFAULT";
			hw->hw_type = MISC;
E 5
I 5
			hw->hw_type = D_MISC;
E 5
			break;
		}
I 5
		/*
		 * Re-map to proper size
		 */
		if (didmap) {
			iounmap(addr, NBPG);
			addr = iomap(hw->hw_pa, hw->hw_size);
			if (addr == 0) {
				printf(notmappedmsg);
				continue;
			}
			hw->hw_kva = addr;
		}
		/*
		 * Encode bus type
		 */
		if (sc >= 132)
			hw->hw_type |= B_DIOII;
		else
			hw->hw_type |= B_DIO;
E 5
		hw++;
	}
}

I 5
/*
 * Allocate/deallocate a cache-inhibited range of kernel virtual address
 * space mapping the indicated physical address range [pa - pa+size)
 */
caddr_t
iomap(pa, size)
	caddr_t pa;
	int size;
{
	int ix, npf;
	caddr_t kva;

#ifdef DEBUG
	if (((int)pa & PGOFSET) || (size & PGOFSET))
		panic("iomap: unaligned");
#endif
	npf = btoc(size);
	ix = rmalloc(extiomap, npf);
	if (ix == 0)
		return(0);
	kva = extiobase + ctob(ix-1);
	physaccess(kva, pa, size, PG_RW|PG_CI);
	return(kva);
}

iounmap(kva, size)
	caddr_t kva;
	int size;
{
	int ix;

#ifdef DEBUG
	if (((int)kva & PGOFSET) || (size & PGOFSET))
		panic("iounmap: unaligned");
	if (kva < extiobase || kva >= extiobase + ctob(EIOMAPSIZE))
		panic("iounmap: bad address");
#endif
	physunaccess(kva, size);
	ix = btoc(kva - extiobase) + 1;
	rmfree(extiomap, btoc(size), ix);
}
D 11

E 5
#if NCD > 0
D 4
#include "../hpdev/cdvar.h"
E 4
I 4
D 6
#include "../dev/cdvar.h"
E 6
I 6
D 8
#include "dev/cdvar.h"
E 8
I 8
#include <dev/cdvar.h>
E 8
E 6
E 4

find_cdevices()
{
	register struct cddevice *cd;

	for (cd = cddevice; cd->cd_unit >= 0; cd++) {
		/*
		 * XXX
		 * Assign disk index first so that init routine
		 * can use it (saves having the driver drag around
		 * the cddevice pointer just to set up the dk_*
		 * info in the open routine).
		 */
		if (dkn < DK_NDRIVE)
			cd->cd_dk = dkn++;
		else
			cd->cd_dk = -1;
		if (cdinit(cd))
			printf("cd%d configured\n", cd->cd_unit);
		else if (cd->cd_dk >= 0) {
			cd->cd_dk = -1;
			dkn--;
		}
	}
}
#endif
E 11

isrinit()
{
	register int i;

	for (i = 0; i < NISR; i++)
		isrqueue[i].isr_forw = isrqueue[i].isr_back = &isrqueue[i];
}

void
isrlink(isr)
	register struct isr *isr;
{
	int i = ISRIPL(isr->isr_ipl);

	if (i < 0 || i >= NISR) {
		printf("bad IPL %d\n", i);
		panic("configure");
	}
	insque(isr, isrqueue[i].isr_back);
}

/*
 * Configure swap space and related parameters.
 */
swapconf()
{
	register struct swdevt *swp;
	register int nblks;

D 10
	for (swp = swdevt; swp->sw_dev; swp++)
E 10
I 10
	for (swp = swdevt; swp->sw_dev != NODEV; swp++)
E 10
		if (bdevsw[major(swp->sw_dev)].d_psize) {
			nblks =
			  (*bdevsw[major(swp->sw_dev)].d_psize)(swp->sw_dev);
			if (nblks != -1 &&
			    (swp->sw_nblks == 0 || swp->sw_nblks > nblks))
				swp->sw_nblks = nblks;
		}
	dumpconf();
}

D 5
#define	DOSWAP			/* Change swdevt, argdev, and dumpdev too */
E 5
I 5
#define	DOSWAP			/* Change swdevt and dumpdev too */
E 5
u_long	bootdev;		/* should be dev_t, but not until 32 bits */

static	char devname[][2] = {
	0,0,		/* 0 = ct */
	0,0,		/* 1 = xx */
	'r','d',	/* 2 = rd */
	0,0,		/* 3 = sw */
	's','d',	/* 4 = rd */
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
	register struct hp_ctlr *hc;
	register struct hp_device *hd;
D 6
	int  majdev, mindev, unit, part, adaptor;
E 6
I 6
	int  majdev, mindev, unit, part, controller, adaptor;
E 6
	dev_t temp, orootdev;
	struct swdevt *swp;

	if (boothowto & RB_DFLTROOT ||
	    (bootdev & B_MAGICMASK) != (u_long)B_DEVMAGIC)
		return;
D 6
	majdev = (bootdev >> B_TYPESHIFT) & B_TYPEMASK;
	if (majdev > sizeof(devname) / sizeof(devname[0]))
E 6
I 6
	majdev = B_TYPE(bootdev);
	if (majdev >= sizeof(devname) / sizeof(devname[0]))
E 6
		return;
D 6
	adaptor = (bootdev >> B_ADAPTORSHIFT) & B_ADAPTORMASK;
	part = (bootdev >> B_PARTITIONSHIFT) & B_PARTITIONMASK;
	unit = (bootdev >> B_UNITSHIFT) & B_UNITMASK;
E 6
I 6
	adaptor = B_ADAPTOR(bootdev);
	controller = B_CONTROLLER(bootdev);
	part = B_PARTITION(bootdev);
	unit = B_UNIT(bootdev);
E 6
	/*
D 6
	 * First, find the controller type which support this device.
E 6
I 6
	 * First, find the controller type which supports this device.
E 6
	 */
	for (hd = hp_dinit; hd->hp_driver; hd++)
		if (hd->hp_driver->d_name[0] == devname[majdev][0] &&
		    hd->hp_driver->d_name[1] == devname[majdev][1])
			break;
	if (hd->hp_driver == 0)
		return;
	/*
D 6
	 * Next, find the controller of that type corresponding to
	 * the adaptor number.
E 6
I 6
	 * Next, find the "controller" (bus adaptor) of that type
	 * corresponding to the adaptor number.
E 6
	 */
	for (hc = hp_cinit; hc->hp_driver; hc++)
		if (hc->hp_alive && hc->hp_unit == adaptor &&
		    hc->hp_driver == hd->hp_cdriver)
			break;
	if (hc->hp_driver == 0)
		return;
	/*
D 6
	 * Finally, find the device in question attached to that controller.
E 6
I 6
	 * Finally, find the "device" (controller or slave) in question
	 * attached to that "controller".
E 6
	 */
	for (hd = hp_dinit; hd->hp_driver; hd++)
D 6
		if (hd->hp_alive && hd->hp_slave == unit &&
E 6
I 6
		if (hd->hp_alive && hd->hp_slave == controller &&
E 6
		    hd->hp_cdriver == hc->hp_driver &&
		    hd->hp_ctlr == hc->hp_unit)
			break;
	if (hd->hp_driver == 0)
		return;
I 6
	/*
	 * XXX note that we are missing one level, the unit, here.
	 * Most HP drives come with one controller per disk.  There
	 * are some older drives (e.g. 7946) which have two units
	 * on the same controller but those are typically a disk as
	 * unit 0 and a tape as unit 1.  This would have to be
	 * rethought if you ever wanted to boot from other than unit 0.
	 */
	if (unit != 0)
		printf("WARNING: using device at unit 0 of controller\n");

E 6
	mindev = hd->hp_unit;
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
D 10
	for (swp = swdevt; swp->sw_dev; swp++) {
E 10
I 10
	for (swp = swdevt; swp->sw_dev != NODEV; swp++) {
E 10
		if (majdev == major(swp->sw_dev) &&
		    mindev == (minor(swp->sw_dev) & ~PARTITIONMASK)) {
			temp = swdevt[0].sw_dev;
			swdevt[0].sw_dev = swp->sw_dev;
			swp->sw_dev = temp;
			break;
		}
	}
D 10
	if (swp->sw_dev == 0)
E 10
I 10
	if (swp->sw_dev == NODEV)
E 10
		return;

	/*
D 5
	 * If argdev and dumpdev were the same as the old primary swap
	 * device, move them to the new primary swap device.
E 5
I 5
	 * If dumpdev was the same as the old primary swap
	 * device, move it to the new primary swap device.
E 5
	 */
	if (temp == dumpdev)
		dumpdev = swdevt[0].sw_dev;
D 5
	if (temp == argdev)
		argdev = swdevt[0].sw_dev;
E 5
#endif
I 2
}
D 7

strcmp(s1, s2)
	register char *s1, *s2;
{
	while (*s1 == *s2++)
		if (*s1++=='\0')
			return (0);
	return (*s1 - *--s2);
E 2
}
E 7
E 1
