/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fbutil.c,v $
 * Revision 2.6  90/02/19  15:13:45  jjc
 * 	Picked up SunOS 3.5 version and modified for Mach.
 * 	[90/02/12            jjc]
 * 
 */
#ifndef lint
static char sccsid[] = "@(#)fbutil.c 1.1 87/12/21 SMI";
#endif

/*
 * Copyright 1985, 1987 by Sun Microsystems, Inc.
 */

/*
 * Frame buffer driver utilities.
 */

#include <sys/param.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/mman.h>
#include <sys/vmmac.h>
#ifdef	MACH
#include <machine/pmap.h>
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <sundev/mbvar.h>

#ifdef	MACH
#else	MACH
/* detect new VM system */
#define	NEWVM	defined(_MAP_NEW)
#endif	MACH


/* ARGSUSED */
fbopen(dev, flag, numdevs, mb_devs)
	dev_t dev;
	int flag, numdevs;
	struct mb_device **mb_devs;
{
	register struct mb_device *md;

	if (minor(dev) >= numdevs || 
		(md = mb_devs[minor(dev)]) == 0 || 
		md->md_alive == 0)
		return ENXIO;

	return 0;
}

/*ARGSUSED*/
fbmmap(dev, off, prot, numdevs, mb_devs, size)
	dev_t dev;
	off_t off;
	int prot;
	int numdevs;
	struct mb_device **mb_devs;
	int size;
{
	if ((u_int) off >= size)
		return -1;

#ifdef	MACH
	return(getkpgmap(mb_devs[minor(dev)]->md_addr + off) & PG_PFNUM);
#else	MACH
	return fbgetpage(mb_devs[minor(dev)]->md_addr + off);
#endif	MACH
}

#ifdef	MACH
#else	MACH
/* get page frame number and type */
fbgetpage(addr)
	caddr_t addr;
{
#if NEWVM

	struct pte pte;
	void mmu_getkpte();

	mmu_getkpte(addr, &pte);
	return MAKE_PFNUM(&pte);

#else NEWVM

	return getkpgmap(addr) & PG_PFNUM;

#endif NEWVM
}

/* simplified mapin/mapout */
fbmapin(virt, phys, size)
	caddr_t virt;
	int phys;
	int size;
{
	mapin(&Usrptmap[btokmx((struct pte *) virt)], btop(virt),
		(u_int) phys, (int) btoc(size), PG_V | PG_KW);
}

fbmapout(virt, size)
	caddr_t virt;
	int size;
{
	mapout(&Usrptmap[btokmx((struct pte *) virt)], (int) btoc(size));
}
#endif	MACH

#ifdef sun2
/*
 * Call intclear to turn off interrupts on all configured devices.
 * If intclear returns a non-zero value, we found the interrupting
 * device.
 */
fbintr(numdevs, mb_devs, intclear)
	int numdevs;
	register struct mb_device **mb_devs;
	int (*intclear)();
{
	register struct mb_device *md;

	while (--numdevs >= 0) 
		if ((md = *mb_devs++) && 
			md->md_alive &&
			(*intclear)(md->md_addr))
			return 1;

	return 0;
}
#endif sun2

#ifndef sun2

#include <sundev/p4reg.h>

p4probe(addr, w, h)
	caddr_t addr;
	int *w, *h;
{
	static int size[P4_ID_RESCODES][2] = {
		1600, 1280,
		1152,  900,
		1024, 1024,
		1280, 1024,
		1440, 1440,
		 640,  480
	};

	register long *reg = (long *) addr;
	long id;
	int type;

	/* peek the P4 register, then try to modify the type code */
	if (peekl(reg, &id) ||
		pokel(reg, id ^ 0xffff0000))
		return -1;

	/* if the "type code" changed, put the old value back and quit */
	if ((*reg ^ id) & 0xffff0000) {
		*reg = id;
		return -1;
	}


	switch (type = (id = (u_long) id >> 24) & P4_ID_MASK) {
	case P4_ID_BW:
	case P4_ID_COLOR8P1:
		if ((id &= ~P4_ID_MASK) < P4_ID_RESCODES) {
			*w = size[id][0];
			*h = size[id][1];
			return type;
		}
		break;
	}

	return -1;
}

#endif !sun2
