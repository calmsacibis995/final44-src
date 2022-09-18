/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	autoconf.c,v $
 * Revision 2.8  93/05/17  16:04:45  rvb
 * 	Type casts, etc to quiet gcc 2.3.3 warnings
 * 	[93/05/17            rvb]
 * 
 * Revision 2.7  93/02/05  08:17:58  danner
 * 	Fix includes.
 * 	[93/02/04            danner]
 * 
 * Revision 2.6  92/01/03  20:32:27  dbg
 * 	Remove include of device/map.h.
 * 	[91/12/19            dbg]
 * 
 * Revision 2.5  91/06/19  11:59:52  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:47:08  rvb]
 * 
 * Revision 2.4  91/05/08  13:13:18  dbg
 * 	Move br and cvec (Unibus probe variables) to memory.
 * 	[91/03/26            dbg]
 * 
 * 	Remove 'static' from csralloc (gcc fix).
 * 	Zero the Unibus allocation map.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.3  91/03/16  15:01:49  rpd
 * 	Updated for new kmem_alloc interface.
 * 	[91/03/03            rpd]
 * 
 * Revision 2.2  90/01/11  11:44:45  dbg
 * 	In unifind, define vubp for DWBUA also.
 * 	[89/11/17            dbg]
 * 
 * Revision 2.1  89/08/03  16:22:43  rwd
 * Created.
 * 
 * 24-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Adapted for MACH kernel:
 *		Removed code to configure CPU
 *		Conditionalized routines in file on bus and CPU types
 *		Added multiport memory support.
 *		Added DWBUA (Unibus on BI bus) support.
 *
 */
/*
 * Copyright (c) 1982,1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)autoconf.c	7.6 (Berkeley) 4/2/87
 */

/*
 * Setup the system to run on the current machine.
 *
 * Configure() is called at boot time and initializes the uba and mba
 * device tables and the memory controller monitoring.  Available
 * devices are determined (from possibilities mentioned in ioconf.c),
 * and the drivers are initialized.
 */

#include <platforms.h>
#include <mach_mpm.h>
#include <mba.h>
#include <uba.h>

#include <mach/machine/vm_types.h>
#include <vm/vm_kern.h>
#include <kern/kalloc.h>

#include <sys/types.h>
#include <device/dk.h>
#include <device/conf.h>

#include <vax/pte.h>
#include <vax/cpu_data.h>
#include <vax/io_map.h>
#include <vax/mem.h>
#include <vax/mtpr.h>
#include <vax/nexus.h>
#include <vax/scb.h>
#include <vax/ioa.h>
#if	NMACH_MPM > 0
#include <vax/ma780var.h>
#endif	NMACH_MPM > 0

#include <vaxmba/mbareg.h>
#include <vaxmba/mbavar.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

/*
 * The following several variables are related to
 * the configuration process, and are used in initializing
 * the machine.
 */
int	cold;		/* if 1, still working on cold-start */
int	dkn;		/* number of iostat dk numbers assigned so far */

/*
 * Addresses of the (locore) routines which bootstrap us from
 * hardware traps to C code.  Filled into the system control block
 * as necessary.
 */
#if NMBA > 0
int	(*mbaintv[4])() =	{ Xmba0int, Xmba1int, Xmba2int, Xmba3int };
#if NMBA > 4
	Need to expand the table for more than 4 massbus adaptors
#endif
#endif
#ifdef DW780
int	(*ubaintv[])() =
{
	Xua0int, Xua1int, Xua2int, Xua3int,
#if NUBA > 4
	Xua4int, Xua5int, Xua6int, Xua7int,
#endif
#if NUBA > 8
	Need to expand the table for more than 8 unibus adaptors
#endif
};
#endif

#if VAX8600 || VAX780 || VAX750 || VAX730
int	nexnum;		/* current nexus number */
int	nsbi;		/* current sbi number */
#endif

#if VAX8600
probe_Abus(ioanum, iob)
	register struct ioa_connect *iob;
{
	register struct ioa *ioap;
	union ioacsr ioacsr;
	int type;
	struct sbia_regs *sbiaregs;

	(void) kmem_alloc_pageable(kernel_map,
				   (vm_offset_t *) &ioap, iob->io_size);
	ioaccess((vm_offset_t)iob->io_addr, (vm_offset_t)ioap, iob->io_size);
	if (badaddr((caddr_t)ioap, 4))
		return;

	ioacsr.ioa_csr = ioap->ioacsr.ioa_csr;
	type = ioacsr.ioa_type & IOA_TYPMSK;

	switch (type) {

	case IOA_SBIA:
		printf("SBIA%d at IO adaptor %d address 0x%x\n",
		    nsbi, ioanum, iob->io_addr);
		probenexi(iob->io_details);
		nsbi++;
		sbiaregs = (struct sbia_regs *)ioap;
		sbiaregs->sbi_errsum = -1;
		sbiaregs->sbi_error = 0x1000;
		sbiaregs->sbi_fltsts = 0xc0000;
		break;

	default:
		printf("IOA%d at address 0x%x is unsupported (type = 0x%x)\n",
		    ioanum, iob->io_addr, ioacsr.ioa_type);
		break;
	}
}
#endif

#if VAX8600 || VAX780 || VAX750 || VAX730
/*
 * Probe nexus space, finding the interconnects
 * and setting up and probing mba's and uba's for devices.
 */
/*ARGSUSED*/
probenexi(pnc)
	register struct nexusconnect *pnc;
{
	register struct nexus *nxv;
	struct nexus *nxp = pnc->psb_nexbase;
	long	nex_csr;
	int	nex_type;
	int	i;
	
	(void) kmem_alloc_pageable(kernel_map,
				   (vm_offset_t *) &nxv,
				   NNEXSBI * sizeof(struct nexus));

	for (nexnum = 0;
	     nexnum < pnc->psb_nnexus;
	     nexnum++, nxp++, nxv++) {

		ioaccess((vm_offset_t)nxp,
			 (vm_offset_t)nxv,
			 sizeof(struct nexus));

		if (badaddr((caddr_t)nxv, 4))
			continue;
		if (pnc->psb_nextype && pnc->psb_nextype[nexnum] != NEX_ANY)
			nex_csr = pnc->psb_nextype[nexnum];
		else
			nex_csr = nxv->nex_csr;
		if (nex_csr&NEX_APD)
			continue;
		nex_type = nex_csr & NEX_TYPE_MASK;
		switch (nex_type) {

		case NEX_MBA:
			printf("mba%d at tr%d\n", nummba, nexnum);
			if (nummba >= NMBA) {
				printf("%d mba's", nummba++);
				goto unconfig;
			}
#if NMBA > 0
			mbafind(nxv, nxp);
			nummba++;
#endif
			break;

		case NEX_UBA0:
		case NEX_UBA1:
		case NEX_UBA2:
		case NEX_UBA3:
			printf("uba%d at tr%d\n", numuba, nexnum);
#if VAX750
			if (numuba >= 2 && cpu == VAX_750) {
				printf("More than 2 UBA's");
				goto unsupp;
			}
#endif
			if (numuba >= NUBA) {
				printf("%d uba's", ++numuba);
				goto unconfig;
			}
#if defined(VAX780) || defined(VAX8600)
			if ((cpu == VAX_780) || (cpu == VAX_8600))
				setscbnex(ubaintv[numuba]);
#endif
			i = nex_type - NEX_UBA0;
			probeuba((struct uba_regs *)nxv, (struct uba_regs *)nxp,
			    pnc->psb_umaddr[i], pnc->psb_ubatype);
			break;

		case NEX_DR32:
		/* there can be more than one... are there other codes??? */
			printf("dr32");
			goto unsupp;

		case NEX_MEM4:
		case NEX_MEM4I:
		case NEX_MEM16:
		case NEX_MEM16I:
			printf("mcr%d at tr%d\n", nmcr, nexnum);
			if (nmcr >= MAXNMCR) {
				printf("%d mcr's", MAXNMCR+1);
				goto unsupp;
			}
			switch (cpu) {
			case VAX_780:
				mcrtype[nmcr] = M780C;
				break;
			case VAX_750:
				mcrtype[nmcr] = M750;
				break;
			case VAX_730:
				mcrtype[nmcr] = M730;
				break;
			}
			mcraddr[nmcr++] = (struct mcr *)nxv;
			break;

		case NEX_MEM64I:
		case NEX_MEM64L:
		case NEX_MEM64LI:
		case NEX_MEM256I:
		case NEX_MEM256L:
		case NEX_MEM256LI:
			printf("mcr%d (el) at tr%d\n", nmcr, nexnum);
			if (nmcr >= MAXNMCR) {
				printf("%d mcr's", MAXNMCR+1);
				goto unsupp;
			}
			if (cpu == VAX_780)
				mcrtype[nmcr] = M780EL;
			mcraddr[nmcr++] = (struct mcr *)nxv;
			if (nex_type != NEX_MEM64I && 
			    nex_type != NEX_MEM256I)
				break;
			/* fall into ... */

		case NEX_MEM64U:
		case NEX_MEM64UI:
		case NEX_MEM256U:
		case NEX_MEM256UI:
			printf("mcr%d (eu) at tr%d\n", nmcr, nexnum);
			if (nmcr >= MAXNMCR) {
				printf("%d mcr's", MAXNMCR+1);
				goto unsupp;
			}
			if (cpu == VAX_780)
				mcrtype[nmcr] = M780EU;
			mcraddr[nmcr++] = (struct mcr *)nxv;
			break;

		case NEX_MPM0:
		case NEX_MPM1:
		case NEX_MPM2:
		case NEX_MPM3:
#if	NMACH_MPM > 0
			printf("mpm%d/mcr%d at tr%d (%x) ",
				nummpm, nmcr, nexnum, nxp);
			if (nummpm >= NMACH_MPM) {
				printf("%d mpm's", nummpm);
				goto unconfig;
			}
			mpmfind(nxv, nxp, nexnum);
			nummpm++;
			switch (cpu) {
			case VAX_780:
				mcrtype[nmcr] = M780MA;
				break;
			}
			mcraddr[nmcr++] = (struct mcr *)nxv;
			break;
#else	NMACH_MPM > 0
			printf("mpm");
			goto unsupp;
#endif	NMACH_MPM > 0

		case NEX_CI:
			printf("ci");
			goto unsupp;

		default:
			printf("nexus type %x", nex_type);
unsupp:
			printf(" unsupported (at tr %d)\n", nexnum);
			continue;
unconfig:
			printf(" not configured\n");
			continue;
		}
	}
	if (nummba > NMBA)
		nummba = NMBA;
	if (numuba > NUBA)
		numuba = NUBA;
}

setscbnex(fn)
	int (*fn)();
{
	register struct scb *scbp = &scb;

	scbp = (struct scb *)((caddr_t)scbp + nsbi * 512);
	scbp->scb_ipl14[nexnum] = scbp->scb_ipl15[nexnum] =
	    scbp->scb_ipl16[nexnum] = scbp->scb_ipl17[nexnum] =
		scbentry(fn, SCB_ISTACK);
}
#endif

#if NMBA > 0
struct	mba_device *mbaconfig();
/*
 * Find devices attached to a particular mba
 * and look for each device found in the massbus
 * initialization tables.
 */
mbafind(nxv, nxp)
	struct nexus *nxv, *nxp;
{
	register struct mba_regs *mdp;
	register struct mba_drv *mbd;
	register struct mba_device *mi;
	register struct mba_slave *ms;
	int dn, dt, sn;
	struct mba_device fnd;

	mdp = (struct mba_regs *)nxv;
	mba_hd[nummba].mh_mba = mdp;
	mba_hd[nummba].mh_physmba = (struct mba_regs *)nxp;
	setscbnex(mbaintv[nummba]);
	mdp->mba_cr = MBCR_INIT;
	mdp->mba_cr = MBCR_IE;
	fnd.mi_mba = mdp;
	fnd.mi_mbanum = nummba;
	for (mbd = mdp->mba_drv, dn = 0; mbd < &mdp->mba_drv[8]; mbd++, dn++) {
		if ((mbd->mbd_ds&MBDS_DPR) == 0)
			continue;
		mdp->mba_sr |= MBSR_NED;		/* si kludge */
		dt = mbd->mbd_dt & 0xffff;
		if (dt == 0)
			continue;
		if (mdp->mba_sr&MBSR_NED)
			continue;			/* si kludge */
		if (dt == MBDT_MOH)
			continue;
		fnd.mi_drive = dn;
#define	qeq(a, b)	( a == b || a == '?' )
		if ((mi = mbaconfig(&fnd, dt)) && (dt & MBDT_TAP))
		    for (sn = 0; sn < 8; sn++) {
			mbd->mbd_tc = sn;
		        for (ms = mbsinit; ms->ms_driver; ms++)
			    if (ms->ms_driver == mi->mi_driver &&
				ms->ms_alive == 0 && 
				qeq(ms->ms_ctlr, mi->mi_unit) &&
				qeq(ms->ms_slave, sn) &&
				(*ms->ms_driver->md_slave)(mi, ms, sn)) {
					printf("%s%d at %s%d slave %d\n"
					    , ms->ms_driver->md_sname
					    , ms->ms_unit
					    , mi->mi_driver->md_dname
					    , mi->mi_unit
					    , sn
					);
					ms->ms_alive = 1;
					ms->ms_ctlr = mi->mi_unit;
					ms->ms_slave = sn;
				}
		    }
	}
}

/*
 * Have found a massbus device;
 * see if it is in the configuration table.
 * If so, fill in its data.
 */
struct mba_device *
mbaconfig(ni, type)
	register struct mba_device *ni;
	register int type;
{
	register struct mba_device *mi;
	register short *tp;
	register struct mba_hd *mh;

	for (mi = mbdinit; mi->mi_driver; mi++) {
		if (mi->mi_alive)
			continue;
		tp = mi->mi_driver->md_type;
		for (mi->mi_type = 0; *tp; tp++, mi->mi_type++)
			if (*tp == (type&MBDT_TYPE))
				goto found;
		continue;
found:
#define	match(fld)	(ni->fld == mi->fld || mi->fld == '?')
		if (!match(mi_drive) || !match(mi_mbanum))
			continue;
		printf("%s%d at mba%d drive %d",
		    mi->mi_driver->md_dname, mi->mi_unit,
		    ni->mi_mbanum, ni->mi_drive);
		mi->mi_alive = 1;
		mh = &mba_hd[ni->mi_mbanum];
		mi->mi_hd = mh;
		mh->mh_mbip[ni->mi_drive] = mi;
		mh->mh_ndrive++;
		mi->mi_mba = ni->mi_mba;
		mi->mi_drv = &mi->mi_mba->mba_drv[ni->mi_drive];
		mi->mi_mbanum = ni->mi_mbanum;
		mi->mi_drive = ni->mi_drive;
		/*
		 * If drive has never been seen before,
		 * give it a dkn for statistics.
		 */
		if (mi->mi_driver->md_info[mi->mi_unit] == 0) {
			mi->mi_driver->md_info[mi->mi_unit] = mi;
			if (mi->mi_dk && dkn < DK_NDRIVE)
				mi->mi_dk = dkn++;
			else
				mi->mi_dk = -1;
		}
		(*mi->mi_driver->md_attach)(mi);
		printf("\n");
		return (mi);
	}
	return (0);
}
#endif

/*
 * Fixctlrmask fixes the masks of the driver ctlr routines
 * which otherwise save r10 and r11 where the interrupt and br
 * level are passed through.
 */
fixctlrmask()
{
	register struct uba_ctlr *um;
	register struct uba_device *ui;
	register struct uba_driver *ud;
#define	phys(a,b) ((b)(((int)(a))&0x7fffffff))

	for (um = ubminit; ud = phys(um->um_driver, struct uba_driver *); um++)
		*phys(ud->ud_probe, short *) &= ~0xc00;
	for (ui = ubdinit; ud = phys(ui->ui_driver, struct uba_driver *); ui++)
		*phys(ud->ud_probe, short *) &= ~0xc00;
}

#if defined(DW780) || defined(DW750) || defined(DW730)
probeuba(vubp, pubp, pumem, ubatype)
	struct uba_regs *vubp, *pubp;
	caddr_t pumem;
	int	ubatype;
{
	register struct uba_hd *uhp = &uba_hd[numuba];

	/*
	 * Save virtual and physical addresses of adaptor.
	 */
	uhp->uh_type = ubatype;
	uhp->uh_uba = vubp;
	uhp->uh_physuba = pubp;
	uhp->uh_mr = vubp->uba_map;
	uhp->uh_memsize = UBAPAGES;

	(void) kmem_alloc_pageable(kernel_map,
				   &unibus_start[numuba],
				   (UBAPAGES + UBAIOPAGES) * VAX_PGBYTES);
	unibus_end[numuba] = unibus_start[numuba] +
					(UBAPAGES + UBAIOPAGES) * VAX_PGBYTES;

	uhp->uh_mem = (caddr_t)unibus_start[numuba];
	uhp->uh_iopage = (caddr_t)unibus_start[numuba] +
					(uhp->uh_memsize * VAX_PGBYTES);

	ioaccess((vm_offset_t)pumem,
		 (vm_offset_t)uhp->uh_mem,
		 (UBAPAGES + UBAIOPAGES) * VAX_PGBYTES);

	unifind(uhp);
}
#endif defined(DW780) || defined(DW750) || defined(DW730)

#ifdef DWBUA
probe_dwbua(vubp, pubp, pumem)
	struct dwbua_regs *vubp, *pubp;
	caddr_t pumem;
{
	register struct uba_hd *uhp = &uba_hd[numuba];

	uhp->uh_type = DWBUA;
	/*
	 * Save virtual and physical addresses of adaptor.
	 */
	uhp->uh_uba = (struct uba_regs *)vubp;
	uhp->uh_physuba = (struct uba_regs *)pubp;
	uhp->uh_mr = vubp->bua_map;
	uhp->uh_memsize = UBAPAGES;

	(void) kmem_alloc_pageable(kernel_map,
				   &unibus_start[numuba],
				   (UBAPAGES + UBAIOPAGES) * VAX_PGBYTES);
	unibus_end[numuba] = unibus_start[numuba] +
					(UBAPAGES + UBAIOPAGES) * VAX_PGBYTES;

	uhp->uh_mem = (caddr_t)unibus_start[numuba];
	uhp->uh_iopage = (caddr_t)unibus_start[numuba] +
					(uhp->uh_memsize * VAX_PGBYTES);
	ioaccess((vm_offset_t)pumem,
		 (vm_offset_t)uhp->uh_mem,
		 (UBAPAGES + UBAIOPAGES) * VAX_PGBYTES);

	unifind(uhp);
}
#endif DWBUA

/*
 * Find devices on a UNIBUS.
 * Uses per-driver routine to set <br,cvec>,
 * and then fills in the tables, with help from a per-driver
 * slave initialization routine.
 */

/*
 * The Unibus interrupt routine in locore.s sets these variables
 * to the IPL and vector where the device interrupted.
 */
volatile int	br;		/* IPL of interrupting device */
volatile int	cvec;		/* vector of interrupting device */

unifind(uhp0)
	struct uba_hd *uhp0;
{
	register struct uba_device *ui;
	register struct uba_ctlr *um;
	register struct uba_hd *uhp = uhp0;
	u_short *reg, *ap, addr;
	struct uba_driver *udp;
	int i, (**ivec)();
	caddr_t ualloc;
	extern int catcher[256];
#if	defined(DW780) || defined(DWBUA)
	struct uba_regs *vubp = uhp->uh_uba;
#endif
	caddr_t pumem = (caddr_t)pmap_extract(kernel_pmap,
					      (vm_offset_t)uhp0->uh_iopage);

#define calloc(size) ((caddr_t)kalloc((vm_size_t)(size)))

	/*
	 * Initialize the UNIBUS, by freeing the map
	 * registers and the buffered data path registers
	 */
	uhp->uh_map = (struct map *)calloc(UAMSIZ * sizeof (struct map));
	ubainitmaps(uhp);

	/*
	 * Allocate and initialize space
	 * for the UNIBUS interrupt vectors.
	 * On the 8600, can't use UNIvec;
	 * the vectors for the second SBI overlap it.
	 */
#if	VAX8600
	if (cpu == VAX_8600)
		uhp->uh_vec = (int(**)())calloc(512);
	else
#endif
	if (numuba == 0)
		uhp->uh_vec = UNIvec;
#if NUBA > 1
	else if (numuba == 1)
		uhp->uh_vec = UNI1vec;
	else
		uhp->uh_vec = (int(**)())calloc(512);
#endif
	for (i = 0; i < 128; i++)
		uhp->uh_vec[i] =
		    scbentry(&catcher[i*2], SCB_ISTACK);
	/*
	 * Set last free interrupt vector for devices with
	 * programmable interrupt vectors.  Use is to decrement
	 * this number and use result as interrupt vector.
	 */
	uhp->uh_lastiv = 0x200;

#ifdef DWBUA
	if (uhp->uh_type == DWBUA) {
		int offset = (int)uhp->uh_vec - (int)UNIvec + 512;
		if (offset > 1024) {
			printf("unifind: too many ubas\n");
			return;
		}
		((struct dwbua_regs *)vubp)->bua_vec_offset = offset;
	}
#endif
#ifdef DW780
	if (uhp->uh_type == DW780) {
		vubp->uba_sr = vubp->uba_sr;
		vubp->uba_cr = UBACR_IFS|UBACR_BRIE;
	}
#endif
	/*
	 * First configure devices that have unibus memory,
	 * allowing them to allocate the correct map registers.
	 */
	ubameminit(numuba);
	/*
	 * Grab some memory to record the umem address space we allocate,
	 * so we can be sure not to place two devices at the same address.
	 *
	 * We could use just 1/8 of this (we only want a 1 bit flag) but
	 * we are going to give it back anyway, and that would make the
	 * code here bigger (which we can't give back), so ...
	 *
	 * One day, someone will make a unibus with something other than
	 * an 8K i/o address space, & screw this totally.
	 */
	if (kmem_alloc_wired(kernel_map,
			     (vm_offset_t *)&ualloc,
			     8*1024) != KERN_SUCCESS)
		panic("no mem for unifind");
	bzero(ualloc, 8*1024);

	/*
	 * Map the first page of UNIBUS i/o
	 * space to the first page of memory
	 * for devices which will need to dma
	 * output to produce an interrupt.
	 */
	*(int *)(&uhp->uh_mr[0]) = UBAMR_MRV;

#define	ubaddr(uhp, off)    (u_short *)((int)(uhp)->uh_iopage + ubdevreg(off))
	/*
	 * Check each unibus mass storage controller.
	 * For each one which is potentially on this uba,
	 * see if it is really there, and if it is record it and
	 * then go looking for slaves.
	 */
	for (um = ubminit; udp = um->um_driver; um++) {
	    if (um->um_alive)
		continue;
	    if (um->um_ubanum != numuba && um->um_ubanum != '?')
		continue;
	    addr = (u_short)(unsigned long)um->um_addr;
	    /*
	     * use the particular address specified first,
	     * or if it is given as "0", or there is no device
	     * at that address, try all the standard addresses
	     * in the driver til we find it
	     */
	    for (ap = udp->ud_addr; addr || (addr = *ap++); addr = 0) {

		if (ualloc[ubdevreg(addr)])
			continue;
		reg = ubaddr(uhp, addr);
		if (badaddr((caddr_t)reg, 2))
			continue;
#ifdef DW780
		if (uhp->uh_type == DW780 && vubp->uba_sr) {
			vubp->uba_sr = vubp->uba_sr;
			continue;
		}
#endif
		cvec = 0x200;
		i = (*udp->ud_probe)(reg, um->um_ctlr, um);
#ifdef DW780
		if (uhp->uh_type == DW780 && vubp->uba_sr) {
			vubp->uba_sr = vubp->uba_sr;
			continue;
		}
#endif
		if (i == 0)
			continue;
		printf("%s%d at uba%d csr %o ",
		    udp->ud_mname, um->um_ctlr, numuba, addr);
		if (cvec == 0) {
			printf("zero vector\n");
			continue;
		}
		if (cvec == 0x200) {
			printf("didn't interrupt\n");
			continue;
		}
		printf("vec %o, ipl %x\n", cvec, br);
		csralloc(ualloc, addr, i);
		um->um_alive = 1;
		um->um_ubanum = numuba;
		um->um_hd = &uba_hd[numuba];
		um->um_addr = (caddr_t)reg;
		udp->ud_minfo[um->um_ctlr] = um;
		for (ivec = um->um_intr; *ivec; ivec++) {
			um->um_hd->uh_vec[cvec/4] =
			    scbentry(*ivec, SCB_ISTACK);
			cvec += 4;
		}
		for (ui = ubdinit; ui->ui_driver; ui++) {
			if (ui->ui_driver != udp || ui->ui_alive ||
			    ui->ui_ctlr != um->um_ctlr && ui->ui_ctlr != '?' ||
			    ui->ui_ubanum != numuba && ui->ui_ubanum != '?')
				continue;
			if ((*udp->ud_slave)(ui, reg)) {
				ui->ui_alive = 1;
				ui->ui_ctlr = um->um_ctlr;
				ui->ui_ubanum = numuba;
				ui->ui_hd = &uba_hd[numuba];
				ui->ui_addr = (caddr_t)reg;
				ui->ui_physaddr = pumem + ubdevreg(addr);
				if (ui->ui_dk && dkn < DK_NDRIVE)
					ui->ui_dk = dkn++;
				else
					ui->ui_dk = -1;
				ui->ui_mi = um;
				/* ui_type comes from driver */
				udp->ud_dinfo[ui->ui_unit] = ui;
				printf("%s%d at %s%d slave %d\n",
				    udp->ud_dname, ui->ui_unit,
				    udp->ud_mname, um->um_ctlr, ui->ui_slave);
				(*udp->ud_attach)(ui);
			}
		}
		break;
	    }
	}
	/*
	 * Now look for non-mass storage peripherals.
	 */
	for (ui = ubdinit; udp = ui->ui_driver; ui++) {
	    if (ui->ui_ubanum != numuba && ui->ui_ubanum != '?' ||
	        ui->ui_alive || ui->ui_slave != -1)
		continue;
	    addr = (u_short)(unsigned long)ui->ui_addr;

	    for (ap = udp->ud_addr; addr || (addr = *ap++); addr = 0) {
		
		if (ualloc[ubdevreg(addr)])
			continue;
		reg = ubaddr(uhp, addr);
		if (badaddr((caddr_t)reg, 2))
			continue;
#ifdef DW780
		if (uhp->uh_type == DW780 && vubp->uba_sr) {
			vubp->uba_sr = vubp->uba_sr;
			continue;
		}
#endif
		cvec = 0x200;
		i = (*udp->ud_probe)(reg, ui);
#ifdef DW780
		if (uhp->uh_type == DW780 && vubp->uba_sr) {
			vubp->uba_sr = vubp->uba_sr;
			continue;
		}
#endif
		if (i == 0)
			continue;
		printf("%s%d at uba%d csr %o ",
		    ui->ui_driver->ud_dname, ui->ui_unit, numuba, addr);
		if (cvec == 0) {
			printf("zero vector\n");
			continue;
		}
		if (cvec == 0x200) {
			printf("didn't interrupt\n");
			continue;
		}
		printf("vec %o, ipl %x\n", cvec, br);
		csralloc(ualloc, addr, i);
		ui->ui_hd = &uba_hd[numuba];
		for (ivec = ui->ui_intr; *ivec; ivec++) {
			ui->ui_hd->uh_vec[cvec/4] =
			    scbentry(*ivec, SCB_ISTACK);
			cvec += 4;
		}
		ui->ui_alive = 1;
		ui->ui_ubanum = numuba;
		ui->ui_addr = (caddr_t)reg;
		ui->ui_physaddr = pumem + ubdevreg(addr);
		ui->ui_dk = -1;
		/* ui_type comes from driver */
		udp->ud_dinfo[ui->ui_unit] = ui;
		(*udp->ud_attach)(ui);
		break;
	    }
	}

#ifdef DW780
	if (uhp->uh_type == DW780)
		uhp->uh_uba->uba_cr = UBACR_IFS | UBACR_BRIE |
		    UBACR_USEFIE | UBACR_SUEFIE |
		    (uhp->uh_uba->uba_cr & 0x7c000000);
#endif
#ifdef DWBUA
	if (uhp->uh_type == DWBUA)
		((struct dwbua_regs *)vubp)->bua_csr =
		    ((struct dwbua_regs *)vubp)->bua_csr;
#endif
	numuba++;

#ifdef	AUTO_DEBUG
	printf("Unibus allocation map");
	for (i = 0; i < 8*1024; ) {
		register n, m;

		if ((i % 128) == 0) {
			printf("\n%6o:", i);
			for (n = 0; n < 128; n++)
				if (ualloc[i+n])
					break;
			if (n == 128) {
				i += 128;
				continue;
			}
		}

		for (n = m = 0; n < 16; n++) {
			m <<= 1;
			m |= ualloc[i++];
		}

		printf(" %4x", m);
	}
	printf("\n");
#endif

	kmem_free(kernel_map, (vm_offset_t)ualloc, (vm_size_t)(8*1024));
}

/*
 * Mark addresses starting at "addr" and continuing
 * "size" bytes as allocated in the map "ualloc".
 * Warn if the new allocation overlaps a previous allocation.
 */
csralloc(ualloc, addr, size)
	caddr_t ualloc;
	u_short addr;
	register int size;
{
	register caddr_t p;
	int warned = 0;

	p = &ualloc[ubdevreg(addr+size)];
	while (--size >= 0) {
		if (*--p && !warned) {
			printf(
	"WARNING: device registers overlap those for a previous device!\n");
			warned = 1;
		}
		*p = 1;
	}
}

