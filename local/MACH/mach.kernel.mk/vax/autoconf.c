/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	autoconf.c,v $
 * Revision 2.10  89/03/09  04:49:54  rpd
 * 	More cleanup.  Ripped out MACH_TIME.
 * 
 * Revision 2.9  89/02/25  20:11:23  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.8  88/10/18  03:39:30  mwyoung
 * 	lint: Get rid of unused variables.
 * 	[88/10/06            mwyoung]
 * 
 * Revision 2.7  88/09/28  18:26:07  mrt
 * 	28-Sep-88 Mary R. Thompson (mrt) at Carnegie-Mellon
 * 	Removed excess #ifdef VAX630 inside the NEX_BDRMEM case.
 * 	[88/09/28  18:01:49  mrt]
 * 
 * Revision 2.6  88/08/25  18:21:48  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Conditionalize more of the NEX_BDRMEM case on VAX630.
 * 	[88/08/18  02:20:57  mwyoung]
 * 
 * Revision 2.5  88/08/10  10:08:21  rvb
 * 	Handle new 6200 machine.  Make all the bi machines use
 * 	the new_probe() and pull the probe out of this file.
 * 	Less verbose slave printout.
 * 	[88/04/08            rvb]
 * 
 *  5-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Use #if, not #ifdef, for determining whether NNI > 0.
 *
 * 18-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	NBI:  augmented VAX820 and VAX8800 conditionals to also require
 *	this symbol so that BI support can be omitted more easily
 *	without changing the cpu set.
 *	[ V5.1(XF24) ]
 *
 * 19-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	More fixes to compile (although not run) for 8200 and 8800
 *	without Mach.
 *	[ V5.1(XF23) ]
 *
 * 18-Apr-88  Steve Schwab (schwab) at Carnegie-Mellon University
 *	Add if_ni.c for DEBNA == bi ethernet
 *
 *  8-Apr-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Handle new 6200 machine.  Maybe I'll make all the bi machines use
 *	the new_probe().
 *
 * 20-Feb-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed to call device probe routine during KDB-50 configuration
 *	so that any initialization code there (e.g. in the new UDA
 *	driver) is executed.
 *	[ V5.1(XF22) ]
 *
 * 26-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed obsolete MACH_REMOTE option.
 *
 * 28-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Changes to support 650: NEX_CACR_BDR and NEX_MEMCTL
 *
 * 29-Sep-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Include bi_badaddr routine only if NBI > 0.
 *
 * 28-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Use kernel_map instead of user_pt_map to allocate UNIBus
 *	allocation array.  Change local variable name from 'cpu_number'
 *	in mpm_find, since cpu_number() is a macro in single-cpu
 *	configurations.
 *
 * 27-Aug-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Enable ecc error reporting from wbx slaves.
 *
 * 30-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Include nmi.h for 8800 support, deleted obsolete MACH_REMOTE
 *	code.
 *
 * 25-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	VAX 8800 support.
 *
 *  2-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Started VAX 8800 support.
 *
 * 22-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  modified setroot() to permit multiple Qbus/Unibus
 *	controllers.
 *	NBI: corrected conditionals for BI specific code.
 *	[ V5.1(F10) ]
 *
 *  6-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed dead MACH_ONLY code.
 *
 * 12-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Enable interprocessor interrupts for 8200 cpus.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Correct 8200 identification.
 *
 * 31-Dec-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Beautify slave console printing with an extra newline.
 *
 * 16-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Removed include of dmap.h for MACH.
 *
 * 12-Dec-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed to compile (a panic) with VAX820 and not MACH or
 *	MACH on.
 *	[ V5.1(F1) ]
 *
 *  8-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flush mp_queue.h.
 *
 *  9-Nov-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 *  7-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Updated memory board reporting for BI memory now that we have 4
 *	meg boards.
 *
 *  2-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Allocate fake Unibus mapping registers for the KDB50.
 *
 * 27-Sep-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added include of "generic.h"
 *
 * 11-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Conditionalized "ka630cpu" uses on VAX630.
 *
 * 23-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Forced include of "param.h" to find "../h" version.
 *
 * 14-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	More fixes to 4.3 merge to make the 8200 work.
 *
 *  8-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	Modified VAX-8200 (BI) code to fit in with the 4.3 autoconf
 *	structures.  Moved VAX-8200 master CPU initialization (local
 *	BI space, for example) to per/CPU routine instead of in
 *	BI code (there may be more than 1 BI bus).
 *
 * 31-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Send an initialize command (I) to 8200 logical consoles before
 *	starting them.
 *
 * 20-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Map the watch chip into virtual memory.
 *
 * 18-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Modified the BI code to not fire up every cpu it finds... it
 *	keeps firing up cpus until it reaches "max_bi_cpus", which
 *	can be patched in the kernel binary.
 *
 *  9-May-86  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Extended memory error code to handle mpm controller.
 *
 *  6-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	CMUCS:  If a Unibus device is already alive, don't try
 *	probing it an additional time (unifind).
 *
 *  5-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	BI support:  probe_bi, support in unifind for DWBUA.
 *
 * 25-Feb-86  David Golub (dbg) at Carnegie-Mellon University
 *	Converted to new virtual memory code.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 19-Dec-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Fix unifind() to also update the UNIBUS address
 *	allocation area for mass storage controllers as well as the
 *	other peripherals.
 *
 * 23-Oct-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Setup multiport memory to do proper cache invalidates.
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Changed where shm and ipc are initialized
 *
 * 10-Sep-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Several changes... don't set cpu_number here (unless we have
 *	multiport memory).  Improvements (and fixes) to multiport
 *	configuration.  Removed some annoying printfs (by popular request).
 *
 * 20-Aug-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Set cpu_number, etc based on whether loadpt < MPMEM_ORIGIN, i.e.
 *	unless we are loaded into shared memory there, we are a
 *	uniprocessor.
 *	Configure rootdev, dumpdev, argdev, swapdev based on bootdev
 *
 * 19-Aug-85  David L. Black (dlb) at CMU  Added timing offset for 780's only
 *	in UBA configure code due to interaction of autoconf catcher
 *	array with (brain-damaged) VAX780 uba.  Should 780s ever come
 *	with uba's that work right (i.e. like 750s) this will have to
 *	be modified again.
 *
 * 15-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added support for MicroVAX I and II based on Ultrix.
 *
 * 07-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Carried over changes below [V1(1)].
 *
 * 06-Mar-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	added abstophys for kernel location to phys macro in fixctlrmask
 *
 * 15-Nov-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	use mp_init for multiprocessor shminit and accentinit initializations
 *
 * 20-Sep-84  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Specify address of memory for ml driver to use in mlattach.  Add
 *	a call to mp_msg_init which will initialize the interprocessor
 *	communication area for this processor.
 *
 * 18-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Moved the shared memory intiialization code from machdep.c to
 *	configure -- which makes more sense.  Also added call to
 *	unxshmprocfree after unxshmpeek, viz.try to give back processor
 *	shared memory when its comming up.
 *
 * 15-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	I left in a lot of code to make a mpm look like a mass bus or unibus
 *	as far as it could support devices with probe, attach ..., but have
 *	never followed through.
 *
 * 14-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Add code to recognize and initialize the multiport memory
 *
 * 17-Aug-84  Andy Gruss (gruss) at Carnegie-Mellon University
 *	CS_GFB:  New nexus type "NEX_GFB" added as support for Gruss
 *	frame buffer device.
 *
 */
 
#include <cpus.h>
#include <cputypes.h>
#include <generic.h>
#include <mach_load.h>
#include <mach_mpm.h>
#include <net_uda.h>

#include <gfb.h>
#include <bi.h>
/*
 * Copyright (c) 1982,1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)autoconf.c	7.1 (Berkeley) 6/6/86
 */

/*
 * Setup the system to run on the current machine.
 *
 * Configure() is called at boot time and initializes the uba and mba
 * device tables and the memory controller monitoring.  Available
 * devices are determined (from possibilities mentioned in ioconf.c),
 * and the drivers are initialized.
 */

#include <mba.h>
#include <uba.h>

#include <vax/pmap.h>
#include <vax/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/dk.h>
#include <sys/vm.h>
#include <sys/conf.h>
#include <sys/reboot.h>

#if	NGFB > 0
#include <vax/gfbreg.h>
#endif	NGFB
#include <vax/cpu.h>
#include <vax/mem.h>
#include <vax/mtpr.h>
#include <vax/nexus.h>
#include <vax/scb.h>
#include <vax/ioa.h>
#include <vaxmba/mbareg.h>
#include <vaxmba/mbavar.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

#if	NMACH_MPM > 0
#include <vax/ma780reg.h>
#include <vax/ma780var.h>
#endif	NMACH_MPM > 0
#include <mach/machine.h>
#include <vm/vm_kern.h>
#include <mach/vm_param.h>
#if	VAX650 || VAX630
#include <vax/uvax.h>
#endif	VAX650 || VAX630
#if	VAX650
#include <vax/ka650.h>
#endif	VAX650
#include <vax/ka630.h>

/*
 * The following several variables are related to
 * the configuration process, and are used in initializing
 * the machine.
 */
int	cold;		/* if 1, still working on cold-start */
int	nexnum;		/* current nexus number */
int	nsbi;		/* current sbi number */
int	dkn;		/* number of iostat dk numbers assigned so far */
int	cpuspeed = 1;	/* relative cpu speed */

extern int loadpt;

/*
 * Addresses of the (locore) routines which bootstrap us from
 * hardware traps to C code.  Filled into the system control block
 * as necessary.
 */

#if	NMBA > 0
int	(*mbaintv[4])() =	{ Xmba0int, Xmba1int, Xmba2int, Xmba3int };
#if	NMBA > 4
	Need to expand the table for more than 4 massbus adaptors
#endif
#endif
#if	defined(VAX780) || defined(VAX8600)
int	(*ubaintv[])() =
{
	Xua0int, Xua1int, Xua2int, Xua3int,
#if	NUBA > 4
	Xua4int, Xua5int, Xua6int, Xua7int,
#endif
#if	NUBA > 8
	Need to expand the table for more than 8 unibus adaptors
#endif
};
#endif

/*
 * This allocates the space for the per-uba information,
 * such as buffered data path usage.
 */
struct	uba_hd uba_hd[NUBA];
/*
 *	Allocated memory for mapping in I/O busses (Unibus, Massbus, Qbus).
 *	Zero the first item ([0]) since it may be allocated by vcons_init
 *	and can't be allocated twice.
 */
vm_offset_t	unibus_start[NUBA] = { 0 };
vm_offset_t	unibus_end[NUBA]   = { 0 };

/*
 * Determine mass storage and memory configuration for a machine.
 * Get cpu type, and then switch out to machine specific procedures
 * which will probe adaptors to see what is out there.
 */
configure()
{
	union cpusid cpusid;
	register struct percpu *ocp;
	register int *ip;
	cpu_subtype_t	subtype;
	extern char Sysbase[];

	/* lets start fresh */
	switch (cpu) {
#if	VAX820 || VAX8800 || VAX6200
	case VAX_820:
	case VAX_8800:
	case VAX_6200:
		bi_configure();
		/*
		 * Write protect the scb and UNIBUS interrupt vectors.
		 * It is strange that this code is here, but this is
		 * as soon as we are done mucking with it, and the
		 * write-enable was done in assembly language
		 * to which we will never return.
		 */
		ip = (int *)Sysmap + 1; *ip &= ~PG_PROT; *ip |= PG_KR;
		ip++; *ip &= ~PG_PROT; *ip |= PG_KR;
#if	NUBA > 1
		ip++; *ip &= ~PG_PROT; *ip |= PG_KR;
#endif
		mtpr(TBIS, Sysbase);
#if	GENERIC
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
		swapconf();
		cold = 0;
		memenable();
		return;
#endif	VAX820 || VAX8800 || VAX6200
	default: ;
	}
	master_cpu = 0;
	ioa = (struct ioa *)kmem_alloc_pageable(kernel_map, MAXNIOA*IOAMAPSIZ);
#if	NBI > 0
/*
	bi_node = (struct bi_node *) kmem_alloc_pageable(kernel_map,
					MAX_BI*BI_MAX_NODE*BI_NODE_SIZE);
*/
#endif	NBI > 0
	nexus = (struct nexus *) kmem_alloc_pageable(kernel_map,
					(vm_size_t)(MAXNNEXUS*NEXSIZE));
	cpusid.cpusid = mfpr(SID);
	switch (cpu) {
#ifdef	VAX8600
	case VAX_8600:
		printf("VAX 8600, serial#%d(%d), hardware ECO level=%d(%d)\n",
		       cpusid.cpu780.cp_sno, cpusid.cpu780.cp_plant,
		       (cpusid.cpu780.cp_eco>>4)&0xf, cpusid.cpu780.cp_eco&0xf);
		subtype = CPU_SUBTYPE_VAX8600;
		break;
#endif	VAX8600
#ifdef	VAX780
	case VAX_780:
		printf("VAX 11/78%c, serial#%d(%d), hardware ECO level=%d(%d)\n",
		       cpusid.cpu780.cp_eco&0x100?'5':'0',
		       cpusid.cpu780.cp_sno, cpusid.cpu780.cp_plant,
		       (cpusid.cpu780.cp_eco>>4)&0xf, cpusid.cpu780.cp_eco&0xf);
		if (cpusid.cpu780.cp_eco&0x100)
			subtype = CPU_SUBTYPE_VAX785;
		else
			subtype = CPU_SUBTYPE_VAX780;
		break;
#endif	VAX780
#ifdef	VAX750
	case VAX_750:
		printf("VAX 11/750, hardware level=%d, microcode level=%d\n",
		       cpusid.cpu750.cp_hrev, cpusid.cpu750.cp_urev);
		subtype = CPU_SUBTYPE_VAX750;
		break;
#endif	VAX750
#if	VAX1
	case VAX_1:
	{
		extern int D_float;

		printf("MicroVAX-I, hardware level=%d, %c-Float microcode level=%d\n",
		       cpusid.cpu1.cp_hrev, D_float?'D':'G',cpusid.cpu1.cp_urev);
		subtype = CPU_SUBTYPE_UVAXI;
		break;
	}
#endif	VAX1
#if	VAX650
	case VAX_650:
	{
		extern int D_float;
		struct sie
		{
		    long  sie_pad;
		    short sie_reserved;
		    char  sie_version;
		    char  sie_syscode;
		} *sie = (struct sie *)firmware;
		printf("MayFair (with%s FPU, SYSCODE:%d, ROM Rev:%d)\n",
		       D_float?"":"out", sie->sie_syscode, sie->sie_version);
		subtype = CPU_SUBTYPE_UVAXII;
		break;
	}
#endif	VAX650
#if	VAX630
	case VAX_630:
	{
		extern int D_float;
		struct sie
		{
		    long  sie_pad;
		    short sie_reserved;
		    char  sie_version;
		    char  sie_syscode;
		} *sie;
		extern char *ka630ROM;

		/*
		 *  As long as we are examining the System Identification
		 *  Extension register, we might as well map the entire ROM in
		 *  case we need to look at it sometime.
		 */
		ka630ROM = (caddr_t)kmem_alloc_pageable(kernel_map,
							32*2*NBPG);
		ioaccess((caddr_t)0x20040000, (vm_offset_t) ka630ROM,
			 32*2*NBPG);
		sie = (struct sie *)ka630ROM;
		printf("MicroVAX-II (with%s FPU, SYSCODE:%d, ROM Rev:%d)\n",
		       D_float?"":"out", sie->sie_syscode, sie->sie_version);
		subtype = CPU_SUBTYPE_UVAXII;
		break;
	}
#endif	VAX630
	default:
		break;
	}
	for (ocp = percpu; ocp->pc_cputype; ocp++)
/*
 * This should really be cpu, but 6200 code does not work this way.
 */
		if (ocp->pc_cputype == cpusid.cpuany.cp_type) {
			cpuspeed = ocp->pc_cpuspeed;
			probeio(ocp);
			/*
			 * Write protect the scb and UNIBUS interrupt vectors.
			 * It is strange that this code is here, but this is
			 * as soon as we are done mucking with it, and the
			 * write-enable was done in assembly language
			 * to which we will never return.
			 */
			ip = (int *)Sysmap + 1; *ip &= ~PG_PROT; *ip |= PG_KR;
			ip++; *ip &= ~PG_PROT; *ip |= PG_KR;
#if	NUBA > 1
			ip++; *ip &= ~PG_PROT; *ip |= PG_KR;
#endif
			mtpr(TBIS, Sysbase);
#if	GENERIC
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
			swapconf();
			cold = 0;
			memenable();

#if	NCPUS == 1
			master_cpu = 0;
#endif	NCPUS == 1
			set_cpu_number();
			printf("Master cpu at slot %d.\n", master_cpu);

			machine_slot[master_cpu].is_cpu = TRUE;
			machine_slot[master_cpu].running = TRUE;
			machine_slot[master_cpu].cpu_type = CPU_TYPE_VAX;
			machine_slot[master_cpu].cpu_subtype = subtype;
			return;
		}
	printf("cpu type %d not configured\n", cpusid.cpuany.cp_type);
	asm("halt");
}

/*
 * Probe the main IO bus(es).
 * The percpu structure gives us a handle on the addresses and/or types.
 */
probeio(pcpu)
	register struct percpu *pcpu;
{
	register struct iobus *iob;
	int ioanum;

	ioanum = 0;
	for (iob = pcpu->pc_io; ioanum < pcpu->pc_nioa; ioanum++, iob++) {

		switch (iob->io_type) {

#if	VAX780 || VAX750 || VAX730 || VAX650 || VAX630
		case IO_SBI780:
		case IO_CMI750:
		case IO_XXX730:
		case IO_QBUS:
			probenexi((struct nexusconnect *)iob->io_details);
			break;
#endif

#if	VAX8600
		case IO_ABUS:
			probe_Abus(ioanum, iob);
			break;
#endif
		default:
			if (iob->io_addr) {
			    printf(
		"IO adaptor %d, type %d, at address 0x%x is unsupported\n",
				ioanum, iob->io_type, iob->io_addr);
			} else
			    printf("IO adaptor %d, type %d, is unsupported\n",
				ioanum, iob->io_type);
			break;
		}
	}
}

#if	VAX8600
probe_Abus(ioanum, iob)
	register struct iobus *iob;
{
	register struct ioa *ioap;
	union ioacsr ioacsr;
	int type;
	struct sbia_regs *sbiaregs;

	ioap = &ioa[ioanum];
	ioaccess(iob->io_addr, (vm_offset_t)ioap, iob->io_size);
	if (badaddr((caddr_t)ioap, 4))
		return;
	ioacsr.ioa_csr = ioap->ioacsr.ioa_csr;
	type = ioacsr.ioa_type & IOA_TYPMSK;

	switch (type) {

	case IOA_SBIA:
		printf("SBIA%d at IO adaptor %d address 0x%x\n",
		    nsbi, ioanum, iob->io_addr);
		probenexi((struct nexusconnect *)iob->io_details);
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
	union nexcsr nexcsr;
	int i;
	
	nexnum = 0, nxv = &nexus[nsbi * NNEXSBI];
	for (; nexnum < pnc->psb_nnexus; nexnum++, nxp++, nxv++) {
		ioaccess((caddr_t)nxp, (vm_offset_t) nxv,
		     sizeof(struct nexus));
		if (badaddr((caddr_t)nxv, 4))
			continue;
		if (pnc->psb_nextype && pnc->psb_nextype[nexnum] != NEX_ANY)
			nexcsr.nex_csr = pnc->psb_nextype[nexnum];
		else
			nexcsr = nxv->nexcsr;
		if (nexcsr.nex_csr&NEX_APD)
			continue;
		switch (nexcsr.nex_type) {

		case NEX_MBA:
			printf("mba%d at tr%d\n", nummba, nexnum);
			if (nummba >= NMBA) {
				printf("%d mba's", nummba++);
				goto unconfig;
			}
#if	NMBA > 0
			mbafind(nxv, nxp);
			nummba++;
#endif
			break;

		case NEX_UBA0:
		case NEX_UBA1:
		case NEX_UBA2:
		case NEX_UBA3:
			printf("uba%d at tr%d\n", numuba, nexnum);
#if	VAX750
			if (numuba >= 2 && cpu == VAX_750) {
				printf("More than 2 UBA's");
				goto unsupp;
			}
#endif
			if (numuba >= NUBA) {
				printf("%d uba's", ++numuba);
				goto unconfig;
			}
#if	defined(VAX780) || defined(VAX8600)
			if ((cpu == VAX_780) || (cpu == VAX_8600))
				setscbnex(ubaintv[numuba]);
#endif
			i = nexcsr.nex_type - NEX_UBA0;
			/*
			 * Allocate enough virtual address space to map the
			 * Unibus (pc_umsize), unless the unibus has already
			 * been mapped.
			 */
			if (unibus_start[numuba] == 0) {
				unibus_start[numuba] = kmem_alloc_pageable(kernel_map,
					VAX_PGBYTES*UBAPAGES);
				unibus_end[numuba] = unibus_start[numuba] +
					VAX_PGBYTES*UBAPAGES;
			}
		 	unifind((struct uba_regs *)nxv, (struct uba_regs *)nxp,
			    (caddr_t)unibus_start[numuba], pnc->psb_umaddr[i],
			    pnc->psb_haveubasr);
#if	defined(VAX780) || defined(VAX8600)
			if ((cpu == VAX_780) || (cpu == VAX_8600))
				((struct uba_regs *)nxv)->uba_cr =
				    UBACR_IFS|UBACR_BRIE|
				    UBACR_USEFIE|UBACR_SUEFIE|
				    (((struct uba_regs *)nxv)->uba_cr&0x7c000000);
#endif
			numuba++;
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
#if	NMACH_MPM > 0
			if (nmcr >= MAXNMCR) {
				printf("%d mcr's", MAXNMCR+1);
				goto unsupp;
			}
#else	NMACH_MPM > 0
			if (nmcr >= 4) {
				printf("5 mcr's");
				goto unsupp;
			}
#endif	NMACH_MPM > 0
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
#if	NMACH_MPM > 0
			if (nmcr >= MAXNMCR) {
				printf("%d mcr's", MAXNMCR+1);
				goto unsupp;
			}
#else	NMACH_MPM > 0
			if (nmcr >= 4) {
				printf("5 mcr's");
				goto unsupp;
			}
#endif	NMACH_MPM > 0
			if (cpu == VAX_780)
				mcrtype[nmcr] = M780EL;
			mcraddr[nmcr++] = (struct mcr *)nxv;
			if (nexcsr.nex_type != NEX_MEM64I && 
			  nexcsr.nex_type != NEX_MEM256I)
				break;
			/* fall into ... */

		case NEX_MEM64U:
		case NEX_MEM64UI:
		case NEX_MEM256U:
		case NEX_MEM256UI:
			printf("mcr%d (eu) at tr%d\n", nmcr, nexnum);
#if	NMACH_MPM > 0
			if (nmcr >= MAXNMCR) {
				printf("%d mcr's", MAXNMCR+1);
				goto unsupp;
			}
#else	NMACH_MPM > 0
			if (nmcr >= 4) {
				printf("5 mcr's");
				goto unsupp;
			}
#endif	NMACH_MPM > 0
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
			mpmfind(nxv, nxp);
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

#ifdef	VAX630
		case NEX_BDRMEM:
		{
			short bdr = *(short *)nxv;
			static char *cpumodes[] = {"Normal", "Language Query", "Loopback", "Maintenance"};

			printf("bdr at tr%d (HALT %sabled, %s Mode)\n", nexnum,
				(bdr&KA630BDR_HLTENB)?"En":"Dis", cpumodes[(bdr>>8)&3]);

			printf("mcr%d at tr%d\n", nmcr, nexnum);
			mcraddr[nmcr++] = (struct mcr *)(nxv);
			/*
			 *	Save the "nexus" as the address of the ka630cpu structure.
			 */
			ka630cpu = (struct ka630cpu *)nxv;
			break;
		}
#endif	VAX630
#if	VAX650
		case NEX_MEMCTL:
		{
			ka650_memctl((struct ka650_mem *)nxv);
			mcraddr[nmcr++] = (struct mcr *)(nxv);
			break;
		}
		case NEX_CACR_BDR:
		{
			static char *cpumodes[] = {"Normal", "Language Inquiry", "Test", "Manufacturing"};
			char bdr;

			ka650_cacr_bdr((struct ka650_cacr_bdr *)nxv);
			bdr = c2cntl->bdr;
			printf("BDR: HALT %sabled, %d baud, %s Mode\n",
				(bdr&KA650BDR_HLTENB)?"En":"Dis",
				(1<<((bdr&KA650BDR_BRS)>>4))*300,
				cpumodes[bdr&3]);
			break;
		}
#endif	VAX650
#if	NGFB > 0
		case NEX_GFB:
		{
			if (numgfb) {
				printf("More than 1 gfb");
				goto unsupp;
			}
			else {
				printf("gfb%d at tr%d (%u byte frame)\n",
					numgfb++, nexnum,
					gfb_frame.size = gfb_map());
				gfb_frame.addr = (byte *)GFBmem;
				gfb_preg = (struct gfb_reg *)nxv;
			}
			break;
		}
#endif	NGFB > 0
		default:
			printf("nexus type %x", nexcsr.nex_type);
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

#if	NMBA > 0
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
#define qeq(a, b)	( a == b || a == '?' )
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
	mdp->mba_cr = MBCR_INIT;
	mdp->mba_cr = MBCR_IE;
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
#define match(fld)	(ni->fld == mi->fld || mi->fld == '?')
		if (!match(mi_drive) || !match(mi_mbanum))
			continue;
		printf("%s%d at mba%d drive %d\n",
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
		return (mi);
	}
	return (0);
}
#endif
#if	NMACH_MPM > 0
 
/* 
 * Find multiport memory.
 */
mpmfind(nxv, nxp)
	struct nexus *nxv, *nxp;
{
	register struct mpm_regs *mpmp;
	register caddr_t addr;
	register int which_cpu;
	int	i;
 
	mpmp = (struct mpm_regs *)nxv;
	mpm_hd[nummpm].ph_mpm = mpmp;
	mpm_hd[nummpm].ph_physmpm = (struct mpm_regs *)nxp;
 
	mpmp->mpm_sr &= ~ MPSR_INVALDIS;
	mpmp->mpm_cr &= ~(MPCR_IVDTACK|MPCR_MSTRIE);
 
	/*
	 *	Force cache invalidates on all SBI ID's.  This
	 *	can be turned off as soon as the cache ID is set
	 *	but I'm not sure how to do this yet.
	 */
 
	mpmp->mpm_invld |= (MPINVLD_CACHEFORCED);
 
	mpmp->mpm_invld = (mpmp->mpm_invld & ~(MPADDR_MSK<<MPADDR_SFT))
			   | (((MPMEM_ORIGIN/0x40000) | 8 * (nexnum - 2))
					  << MPADDR_SFT);
	addr = (caddr_t) (0x40000*(MPADDR_MSK&(mpmp->mpm_invld>>MPADDR_SFT)));
	printf("mem at %x ", addr);
 
	which_cpu = mpmp->mpm_csr & 3;
	if (!nummpm) {
		for (i = 0; i < NMACH_MPM; i++) {
			if (i >= NCPUS)
				break;
			machine_slot[i].is_cpu = TRUE;
		}
		mpm_port_addr = (int *) &mpmp->mpm_csr;
		master_cpu = which_cpu;
	} else if (master_cpu != (mpmp->mpm_csr & 3)) {
		printf("\n\nTurkey!!! The same CPU has different port numbers for different MA780\'s.  Have your hardware fixed.\n");
		asm("halt");
	}
	printf("port %d\n", which_cpu );
 
	mpm_dismiss(nummpm, MP_TO_ME);
	mpm_dismiss(nummpm, MP_FROM_ME);
	mpm_on(nummpm);
	mpm_enable(nummpm, MP_TO_ME);
}
 
hack_mpm(i)
int i;
{
	register struct mpm_regs *mpmp;

	mpmp = mpm_hd[i].ph_mpm;
	M780MA_ENA( ((struct mcr *) mpmp) );

	mpmp->mpm_sr &= ~ MPSR_INVALDIS;
	mpmp->mpm_cr &= ~(MPCR_IVDTACK|MPCR_MSTRIE);
  
	mpmp->mpm_invld |= (MPINVLD_CACHEFORCED);	/* see earlier */
  
	printf("mem at %x ", 0x40000 * (
			       MPADDR_MSK&(mpmp->mpm_invld>>MPADDR_SFT)));
 
	printf("port %d\n", mpmp->mpm_csr & 3);
 
	mpm_dismiss(i, MP_TO_ME);
	mpm_dismiss(i, MP_FROM_ME);
	mpm_on(i);
	mpm_enable(i, MP_TO_ME);
}
#endif	NMACH_MPM > 0
slave_config()
{
	register int i;
	union cpusid	sid;
	cpu_subtype_t	subtype;
 
	set_cpu_number();
	/*
	 * Use cpu, setup by master
	 */
	switch (cpu) {
#if	VAX8800
	case VAX_8800:
		subtype = CPU_SUBTYPE_VAX8800;
		break;
#endif	VAX8800
#if	VAX6200
	case VAX_6200:
		subtype = CPU_SUBTYPE_UVAXIII;
#endif	VAX6200
#if	VAX780
	case VAX_780:
		subtype = sid.cpu780.cp_eco&0x100 ? CPU_SUBTYPE_VAX785 :
							CPU_SUBTYPE_VAX780;
		break;
#endif	VAX780
	default:
		break;
	}
	machine_slot[cpu_number()].cpu_type = CPU_TYPE_VAX;
	machine_slot[cpu_number()].cpu_subtype = subtype;
	initcpu();
#if	NMACH_MPM > 0
	for (i = 0; i < nummpm; i++)
		hack_mpm(i);
#endif	NMACH_MPM > 0
	printf("\tSlave started;  master cpu at slot %d.\n",
		master_cpu);
	slave_cnenable();
}

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
#if	MACH_LOAD
#define phys(a,b) ((b) ( ( ((int)(a)) & 0x7fffffff) + loadpt))
#else	MACH_LOAD
#define phys(a,b) ((b)(((int)(a))&0x7fffffff))
#endif	MACH_LOAD

#if	MACH_LOAD
	for (um = ubminit;
	       ud = phys(um->um_driver, struct uba_driver *),
	       (int) ud != loadpt;
	     um++)
#else	MACH_LOAD
	for (um = ubminit; ud = phys(um->um_driver, struct uba_driver *); um++)
#endif	MACH_LOAD
		*phys(ud->ud_probe, short *) &= ~0xc00;
#if	MACH_LOAD
	for (ui = ubdinit;
	      ud = phys(ui->ui_driver, struct uba_driver *),
	      (int) ud != loadpt;
	     ui++)
#else	MACH_LOAD
	for (ui = ubdinit; ud = phys(ui->ui_driver, struct uba_driver *); ui++)
#endif	MACH_LOAD
		*phys(ud->ud_probe, short *) &= ~0xc00;
}

/*
 * Find devices on a UNIBUS.
 * Uses per-driver routine to set <br,cvec> into <r11,r10>,
 * and then fills in the tables, with help from a per-driver
 * slave initialization routine.
 */
unifind(vubp, pubp, vumem, pumem, haveubasr)
	struct uba_regs *vubp, *pubp;
	caddr_t vumem, pumem;
	int haveubasr;
{
#ifndef	lint
	register int br, cvec;			/* MUST BE r11, r10 */
#else
	/*
	 * Lint doesn't realize that these
	 * can be initialized asynchronously
	 * when devices interrupt.
	 */
	register int br = 0, cvec = 0;
#endif
	register struct uba_device *ui;
	register struct uba_ctlr *um;
	u_short *reg, *ap, addr;
	struct uba_hd *uhp;
	struct uba_driver *udp;
	int i, (**ivec)();
	caddr_t ualloc;
	extern int catcher[256];

#if	VAX630 || VAX650
	/*
	 * The map registers start right at 20088000 on the
	 * ka630, so we have to subtract out the 2k offset to make the
	 * pointers work..
	 */
	if (cpu == VAX_630 || cpu == VAX_650) {
		vubp = (struct uba_regs *)(((u_long)vubp)-0x800);
		pubp = (struct uba_regs *)(((u_long)pubp)-0x800);
	}
#endif
	/*
	 * Initialize the UNIBUS, by freeing the map
	 * registers and the buffered data path registers
	 */
	uhp = &uba_hd[numuba];
	uhp->uh_map = (struct map *)calloc(UAMSIZ * sizeof (struct map));
	ubainitmaps(uhp);

	/*
	 * Save virtual and physical addresses
	 * of adapter, and allocate and initialize
	 * the UNIBUS interrupt vector.
	 */
	uhp->uh_uba = vubp;
	uhp->uh_physuba = pubp;
	/*
	 * On the 8600, can't use UNIvec;
	 * the vectors for the second SBI overlap it.
	 */
	if (cpu == VAX_8600)
		uhp->uh_vec = (int(**)())calloc(512);
	else if (numuba == 0)
		uhp->uh_vec = UNIvec;
#if	NUBA > 1
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

#if	NBI > 0
	if (uhp->uh_type == UBATYPE_DWBUA) {
		int	offset;

		offset = (int)uhp->uh_vec - (int)UNIvec + 512;
		if (offset > 1024) {
			printf("unifind: too many uba's\n");
			return;
		}
		((struct dwbua_regs *)vubp)->vec_offset = offset;
	}
#endif	NBI > 0
#if	VAX650 || VAX630
	/*
	 * Kludge time again. The q22 memory and device reg. address spaces
	 * are not physically contiguous, so we need 2 loops to map them
	 * into contiguous virtual space.
	 */
	if (cpu == VAX_650 || cpu == VAX_630) {
		ioaccess(pumem, (vm_offset_t)vumem, (UBAPAGES-16)*NBPG);
		ioaccess(QBUS_CSR, (vm_offset_t)vumem+(UBAPAGES-16)*NBPG,
			 16*NBPG);
	} else
#endif	VAX650 || VAX630
		ioaccess(pumem, (vm_offset_t)vumem, UBAPAGES * NBPG);
#if	defined(VAX780) || defined(VAX8600)
	if (haveubasr) {
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
	ualloc = (caddr_t)kmem_alloc(kernel_map, 8*1024);
	if (ualloc == (caddr_t)0)
		panic("no mem for unifind");

	/*
	 * Map the first page of UNIBUS i/o
	 * space to the first page of memory
	 * for devices which will need to dma
	 * output to produce an interrupt.
	 */
	*(int *)(&vubp->uba_map[0]) = UBAMR_MRV;

#define ubaoff(off)	((off)&0x1fff)
#define ubaddr(off)	(u_short *)((int)vumem + (ubaoff(off)|0x3e000))
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
		addr = (u_short)um->um_addr;
		/*
		 * use the particular address specified first,
		 * or if it is given as "0", of there is no device
		 * at that address, try all the standard addresses
		 * in the driver til we find it
		 */
	    for (ap = udp->ud_addr; addr || (addr = *ap++); addr = 0) {

		if (ualloc[ubaoff(addr)])
			continue;
		reg = ubaddr(addr);
		if (bi_badaddr((caddr_t)reg, 2))
			continue;
#if	defined(VAX780) || defined(VAX8600)
		if (haveubasr && vubp->uba_sr) {
			vubp->uba_sr = vubp->uba_sr;
			continue;
		}
#endif
		cvec = 0x200;
		i = (*udp->ud_probe)(reg, um->um_ctlr, um);
#if	defined(VAX780) || defined(VAX8600)
		if (haveubasr && vubp->uba_sr) {
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
		while (--i >= 0)
			ualloc[ubaoff(addr+i)] = 1;
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
		addr = (u_short)ui->ui_addr;

	    for (ap = udp->ud_addr; addr || (addr = *ap++); addr = 0) {
		
		if (ualloc[ubaoff(addr)])
			continue;
		reg = ubaddr(addr);
		if (bi_badaddr((caddr_t)reg, 2))
			continue;
#if	defined(VAX780) || defined(VAX8600)
		if (haveubasr && vubp->uba_sr) {
			vubp->uba_sr = vubp->uba_sr;
			continue;
		}
#endif
		cvec = 0x200;
		i = (*udp->ud_probe)(reg, ui);
#if	defined(VAX780) || defined(VAX8600)
		if (haveubasr && vubp->uba_sr) {
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
		while (--i >= 0)
			ualloc[ubaoff(addr+i)] = 1;
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

	kmem_free(kernel_map, (vm_offset_t) ualloc, (vm_size_t) 8*1024);
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


#if	NBI > 0
/*
 *	bi_badaddr() is defined in biconf.c
 */
#else	NBI > 0
/*
 *	Check for a bad address not only by a machine check but also
 *	a BI error (necessary on 8800).
 */
bi_badaddr(addr, size)
	caddr_t	addr;
	int	size;
{
	if (badaddr(addr, size)) {
		return(1);
	}
	return(0);
}
#endif	NBI > 0

/*
 * Make an IO register area accessible at physical address physa
 * by mapping kernel ptes starting at pte.
 */
ioaccess(physa, vaddr, size)
	caddr_t		physa;
	vm_offset_t	vaddr;
	int		size;
{
	register int		i = btop(size);
	register pt_entry_t	*pte = pmap_pte(vm_map_pmap(kernel_map), vaddr);
	register unsigned	p = btop(physa);

	do {
		*(int *)pte++ = VAX_PTE_VALID|VAX_PTE_KW|p++;
	} while (--i > 0);
	mtpr(TBIA, 0);
}

/*
 * Configure swap space and related parameters.
 */
swapconf()
{
	/*
	 *	We swap to normal file systems for new VM.
	 */
	if (!cold)			/* in case called for mba device */
		return;
	if (dumplo == 0 && bdevsw[major(dumpdev)].d_psize)
		dumplo = (*bdevsw[major(dumpdev)].d_psize)(dumpdev) - physmem;
	if (dumplo < 0)
		dumplo = 0;
}

#define DOSWAP			/* Change swdevt, argdev, and dumpdev too */
u_long	bootdev;		/* should be dev_t, but not until 32 bits */

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
	0,0,		/* 12 = uu */
	0,0,		/* 13 = rx */
	'r','l',	/* 14 = rl */
};

#define PARTITIONMASK	0x7
#define PARTITIONSHIFT	3

/*
 * Attempt to find the device from which we were booted.
 * If we can do so, and not instructed not to do so,
 * change rootdev to correspond to the load device.
 */
setroot()
{
	int  majdev, mindev, unit, part, adaptor;
	int ctlr;
	dev_t orootdev;

	if (boothowto & RB_DFLTROOT ||
	    (bootdev & B_MAGICMASK) != (u_long)B_DEVMAGIC)
		return;
	majdev = (bootdev >> B_TYPESHIFT) & B_TYPEMASK;
	if (majdev > sizeof(devname) / sizeof(devname[0]))
		return;
	adaptor = (bootdev >> B_ADAPTORSHIFT) & B_ADAPTORMASK;
	part = (bootdev >> B_PARTITIONSHIFT) & B_PARTITIONMASK;
	unit = (bootdev >> B_UNITSHIFT) & B_UNITMASK;
	ctlr = unit >> 3;
	unit = unit & 07;
	if (majdev == 0) {	/* MBA device */
#if	NMBA > 0
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
#define PHYSADRSHFT	13
#define PHYSMBAMASK780	0x7
#define PHYSMBAMASK750	0x3

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
	} else {
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

#ifdef	DOSWAP
#endif
}
