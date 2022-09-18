/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/* 
 **********************************************************************
 * HISTORY
 * $Log:	autoconf.c,v $
 * Revision 2.6  89/03/09  21:13:25  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/26  14:17:02  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/08  13:41:19  rvb
 * umaddr was defined wrong for the 650 and although correct for
 * the 620 for the moment, would soon be wrong for that too when
 * the the definition of UMEM630 gets changed in ubareg.h.  So...
 * make umaddr for both make sense.  They both have mapping regs,
 * csr, and qbus memory at 2008800, 20000000, and 30000000
 * respectively.
 * If bi dev is "BROKE", don't touch it.
 * 1)	Support for ka62a and review all the bi support.
 * 2)	It is too hard to understand what the SMALL option does;
 * it has been revamped.  Device code is now controlled
 * by configuring for the BUSes and machines you are interested in.
 * 4)	AND SMALL now is used to exclude trash that you don't need
 * for the 15 sector boot (as it is used in prf.c and sys.c)
 * VAX650 support.
 * Conditionalize all code by the vax type for which it is
 * appropriate.  In particular, if VAX630 and VAX1 are not defined
 * we do not reference qv_probe and qd_probe.
 * 
 *
 * 16-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added SMALL conditional around BI/SBI CPU's for generating
 *	secondary boot file Q-bus/Unibus systems (this needs to be
 *	generalized); added SMALL630 conditional to translate uVax-2
 *	hardware bootstrap parameters; reinserted Q-bus map invalidate
 *	code for the uVax-2 (the kernel UDA driver will initiate a
 *	random I/O when it is probed that will clobber a page of kernel
 *	memory if all pages are left mapped valid).
 *	[ V5.1(F8) ]
 *
 *  7-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Flushed CS_NEWCPU and remerged Multiport memory and BI code that
 *	was lost in a previous merge.
 *
 * 11-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for BI bus, in particular, KDB50 as boot device.
 *
 * 01-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_NEWCPU:  added support for MicroVax-I and -II (a la ULTRIX-32).
 *
 * 15-Sep-84  Robert V Baron (rvb) at Carnegie-Mellon University
 *	two basic major changes:
 * 1)	Coded has been added to support MA780
 * 2)	uba0, mba0, now correspond to the first unibus, (massbus)
 *	independent of wether they are tr3 and tr8.  The code mimic's
 *	autoconf of the real OS
 **********************************************************************
 */

#include <sys/features.h>

#ifdef	VAXSBI
#define VAX8600	1
#define VAX780	1
#define VAX750	1
#define VAX730	1
#endif	VAXSBI

#ifdef	VAXQBUS
#define VAX650	1
#define VAX630	1
#define VAX1	1
#endif	VAXQBUS

#ifdef	VAXBI
#define NBI	1
#define VAX820	1
#define VAX8800	1
#define VAX6200	1
#endif	VAXBI

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)autoconf.c	7.1 (Berkeley) 6/5/86
 */

#include <machine/pte.h>

#include <sys/param.h>
#if	CMU
#include <sys/reboot.h>
#endif	CMU

#include <vax/cpu.h>
#include <vax/nexus.h>
#include <vaxuba/ubareg.h>
#include <vaxmba/mbareg.h>
#include <vax/ma780reg.h>
#include <vax/ma780var.h>
#include <vax/bi_node.h>
#include <vax/mtpr.h>

#include "savax.h"
#if	defined(VAX780) || defined(VAX8600)
#define UTR(i)	((struct uba_regs *)(NEX780+(i)))
#define UMA(i)	((caddr_t)UMEM780(i))
#define MTR(i)	((struct mba_regs *)(NEX780+(i)))

#define MTC ((struct mpm_regs *) -1)

struct	mpm_regs *mpmaddr[4] = { MTC, MTC, MTC, MTC };
/*
 * NOTE!!!!: umaddr780 must be the address of the device
 * registers i.e. 0x20100000+0760000+0x40000*i
 */
struct	uba_regs *ubaddr780[] = { UTR(3), UTR(4), UTR(5), UTR(6) };
caddr_t	umaddr780[] = { UMA(0), UMA(1), UMA(2), UMA(3) };
struct	mba_regs *mbaddr780[] = { MTR(8), MTR(9), MTR(10), MTR(11) };

#undef	UTR
#undef	UMA
#undef	MTR
#endif	defined(VAX780) || defined(VAX8600)

#ifdef	VAX750
#define UTR(i)	((struct uba_regs *)(NEX750+(i)))
#define UMA(i)	((caddr_t)UMEM750(i))
#define MTR(i)	((struct mba_regs *)(NEX750+(i)))

struct	uba_regs *ubaddr750[] = { UTR(8), UTR(9) };
caddr_t	umaddr750[] = { UMA(0), UMA(1) };
struct	mba_regs *mbaddr750[] = { MTR(4), MTR(5), MTR(6), MTR(7) };

#undef	UTR
#undef	UMA
#undef	MTR
#endif	VAX750

#ifdef	VAX730
#define UTR(i)	((struct uba_regs *)(NEX730+(i)))
#define UMA	((caddr_t)UMEM730)

struct	uba_regs *ubaddr730[] = { UTR(3) };
caddr_t	umaddr730[] = { UMA };

#undef	UTR
#undef	UMA
#endif	VAX730

/*
 *  The uVax-2 has no general Q22-bus control/status registers although it does
 *  use mapping registers.  Thus, we fudge the address below (which is
 *  calculated from the beginning of the mapping register area) with an
 *  artificial negative offset to provide a virtual bus register area below the
 *  map that will never be accessed but that allows the standard bus map code
 *  to function without modification.
 */
#if	defined(VAX630) || defined(VAX650)
struct  uba_regs *ubaddruvax[] = { (struct uba_regs *)(0x20088000-0x800) };
caddr_t umaddruvax[] = { (caddr_t)0x20000000-ubdevreg(0) };
#endif	defined(VAX630) || defined(VAX650)

#ifdef	VAX1
caddr_t umaddr1[] = { (caddr_t)UMEM1 };
#endif	VAX1

#if	defined(VAXBI)
struct	uba_regs *ubaddrbi[] = {
		(struct uba_regs *)-1, (struct uba_regs *)-1,
		(struct uba_regs *)-1, (struct uba_regs *)-1};
caddr_t	umaddrbi[] = { (caddr_t)-1, (caddr_t)-1, (caddr_t)-1, (caddr_t)-1};
#endif	defined(VAXBI)

static int nmba, nuba, nmpm;

configure(r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,ap)
long *ap;
{
	union cpusid cpusid;
	register int systype, cputype_sid;
	register int i;

	nmba = 0, nuba = 0, nmpm = 0;

	cpusid.cpusid = mfpr(SID);
	cpu = cpusid.cpuany.cp_type;
	cputype_sid = cpu;
#ifdef	VAXBI
	if (cpu == VAX_650 || cpu == VAX_630)
		systype = *SYSTYPE;
	else
		systype = -1;
	if (cpu == VAX_650) {
		/* we are running physical here so: */
		switch (systype >> 24) {
		case 1:
			break;
		case 2:
			cpu = VAX_6200;
			break;
		default:
			asm("halt");
		}
	}
#endif	VAXBI
	switch (cpu) {

#ifdef	VAX780
	case VAX_8600:
	case VAX_780:
		mbaddr = mbaddr780;
		ubaddr = ubaddr780;
		umaddr = umaddr780;
		probe_sbi();
		break;
#endif	VAX780

#ifdef	VAX750
	case VAX_750:
		mbaddr = mbaddr750;
		ubaddr = ubaddr750;
		umaddr = umaddr750;
		nmba = sizeof (mbaddr750) / sizeof (mbaddr750[0]);
		break;
#endif	VAX750

#ifdef	VAX730
	case VAX_730:
		ubaddr = ubaddr730;
		umaddr = umaddr730;
		break;
#endif	VAX730

#ifdef	VAXBI
	case VAX_820:
		probe_bi(BI_ADDR(0));
		break;
	case VAX_8800:
		for (i = 0; i < 4; i++)
			probe_bi(BI_ADDR(i));
		break;
#define XMI_IOA_RANGE1	((caddr_t) 0x22000000)
#define XMI_IOA_RANGE2	((caddr_t) 0x36000000)
#define XMI_IOA_SIZE	(32 * 1024 * 1024)
	case VAX_6200:
		mtpr(CADR, 0xec);	/* level 1 cache on */

		i = *(int *)(0x20000000);
		*(int *)(0x20000000) = i | 0x00140000; /* FCI & FMISS */
		*(int *)(0x20000000) = i & ~0x00140000; /* FCI & FMISS */

		for (i = 0; i < 4; i++)
			probe_bi(XMI_IOA_RANGE1 + XMI_IOA_SIZE * i);
		for (i = 0; i < 4; i++)
			probe_bi(XMI_IOA_RANGE2 + XMI_IOA_SIZE * i);
		break;
#endif	VAXBI

#if	defined(VAX630) || defined(VAX650)
	case VAX_650:
	case VAX_630:
		ubaddr = ubaddruvax;
		umaddr = umaddruvax;
#ifdef	SMALL
		/*
		 *  When running as the secondary bootstrap (bootrq), we need
		 *  to translate the hardware bootstrap parameters to our
		 *  software conventions.  The extended RPB is addressed by
		 *  R11.  The two letter boot device name is in the low word at
		 *  offset 0x1c (saved R0 - although we don't currently use it
		 *  since no drivers exist to boot from any devices other than
		 *  "ra").  The boot flags are at offset 0x30 (saved R5).  The
		 *  boot device CSR is at offset 0x54 and we compare its low
		 *  word against the table of CSR address to produce the
		 *  controller number.  The drive number is in the low word at
		 *  offset 0x64.
		 */
		{
		    register short *xrpb = (short *)r11;
		    register u_short *csrp;
		    extern u_short udastd[];

		    r10 = (9<<B_TYPESHIFT);	/* (only ra) */
		    r10 |= ((xrpb[0x64>>1])<<B_UNITSHIFT);
		    for (csrp= &udastd[0]; *csrp; csrp++)
			if (xrpb[0x54>>1] == (*csrp&017777))
			    break;
		    r10 |= (csrp-udastd)<<B_ADAPTORSHIFT;
		    r10 |= B_DEVMAGIC;
		    r11 = ((int *)xrpb)[0x30>>2];

		    r5 = ap[3];		/* mem 1st page */
		    r6 = ap[4];		/* mem last page */
		    r7 = ap[5];		/* bit map size */
		    r8 = ap[6];		/* bit map addr */

		}
#endif	SMALL
		break;
#endif	defined(VAX630) || defined(VAX650)

#ifdef	VAX1
	case VAX_1:
		umaddr = umaddr1;
 		break;
#endif	VAX1
 	}
	/*
	 *  Initialize UNIBUS/Q22-Bus as appropriate per cpu.
	 */
	switch (cpu) {
#if	defined(VAX8800) || defined(VAX6200)
	     case VAX_8800:
	     case VAX_6200:
		for (i = 0; i < nuba; i++)
			((struct dwbua_regs *)ubaddr[i])->csr =
				((struct dwbua_regs *)ubaddr[i])->csr;
#endif	defined(VAX8800) || defined(VAX6200)
#if	defined(VAX8600) || defined(VAX780)
	     case VAX_8600:
	     case VAX_780:
		for (i = 0; i < nuba; i++)
			ubaddr[i]->uba_cr = UBACR_ADINIT;
		break;
#endif	defined(VAX8600) || defined(VAX780)
#if	defined(VAX650) || defined(VAX630) || defined(VAX750) || defined(VAX730)
	     case VAX_650:
	     case VAX_630:
	     case VAX_750:
	     case VAX_730:
	     case VAX_1:
		mtpr(IUR, 0);
  		break;
#endif	defined(VAX650) || defined(VAX630) || defined(VAX750) || defined(VAX730)
 	}
	/* give unibus devices a chance to recover... */
	if (nuba > 0)
		DELAY(2000000);
	switch (cpu) {
#if	defined(VAX630) || defined(VAX650)
	case VAX_650:
	case VAX_630:
	{
		u_int *qmbase;

		/* invalidate Q-bus map */
		for (qmbase = (u_int *)0x20088000, i=0;
		     i < 8192;
		     qmbase++, i++)
			*qmbase = i;
		*((u_short *)0x20001f40) = 0x20;	/* enable LM EAE */
		/* fall through */
	}
#endif	defined(VAX630) || defined(VAX650)
#if	defined(VAX650) || defined(VAX630) || defined(VAX1)
	case VAX_1:
		qv_probe();
		qd_probe();
		break;
#endif	defined(VAX650) || defined(VAX630) || defined(VAX1)
	}
}

/*
 * Probe SBI nexus space, finding the interconnects
 * and setting up and probing mba's and uba's for devices.
 * We especially need to do this for UBA's since the original
 * code incorrectly located the device register space for
 * an adaptor not at its default location.
 */
#if	defined(VAXSBI)
probe_sbi()
{
	struct nexus *phys_addr_nexusp = (struct nexus *) NEX780;
	register struct mpm_regs *mpmp;
	union nexcsr nexcsr;
	register int i;
	register int	nexnum;

	nexnum = 0;

	for (; nexnum < NNEX780; nexnum++, phys_addr_nexusp++) {
		if (badloc((caddr_t)phys_addr_nexusp)) {
			continue;
		}

		nexcsr = phys_addr_nexusp->nexcsr;
		if (nexcsr.nex_csr&NEX_APD)
			continue;

		switch (nexcsr.nex_type) {
		case NEX_MBA:
			if (nmba < MAXNMBA) {
				mbaddr[nmba++] = (struct mba_regs *)phys_addr_nexusp;
			}
			break;
		case NEX_UBA0:
		case NEX_UBA1:
		case NEX_UBA2:
		case NEX_UBA3:
			if (nuba < 4) {
				i = nexcsr.nex_type - NEX_UBA0;
				umaddr[nuba] = (caddr_t) UMEM780(i);
				ubaddr[nuba++] = (struct uba_regs *)phys_addr_nexusp;
			}
			break;

		case NEX_MPM0:
		case NEX_MPM1:
		case NEX_MPM2:
		case NEX_MPM3:
			if (nmpm >= 4)
				break;
			mpmaddr[nmpm++] = (struct mpm_regs *)phys_addr_nexusp;

			mpmp = (struct mpm_regs *) phys_addr_nexusp;
			mpmp->mpm_cr &= ~(MPCR_IVDTACK|MPCR_MSTRIE);
			mpmp->mpm_sr &= ~ MPSR_INVALDIS;
			mpmp->mpm_invld = (mpmp->mpm_invld & 
					    ~(MPADDR_MSK<<MPADDR_SFT))
					   | (((MPMEM_ORIGIN/0x40000)
						 | 8 * (nexnum - 2))
						  << MPADDR_SFT);
			break;
		}
	}
}
#endif	defined(VAXSBI)

/*
 *	Probe BI node space.
 */
#if	defined(VAXBI)
probe_bi(phys)
	caddr_t		phys;
{
	register struct bi_node *bi;
	register caddr_t	window_space = phys + 0x400000;
	register int		i;
	register int		nodenum;
	register int		nkdb = 0;
	u_short			dev_type;
	extern caddr_t		udaddr;		/* for uda driver */
	extern			iskdb50;

	nodenum = 0;
	for (; nodenum < BI_MAX_NODE; nodenum++, phys += BI_NODE_SIZE) {
		if (badloc((caddr_t)phys)) {
			continue;
		}
		bi = (struct bi_node *) phys;
		dev_type = bi->dev_type;
		if (bi->bicsr & BICSR_BROKE &&
		    dev_type != 1 &&
		    *((int *) bi) != 0xfff1ffff) {
#ifndef	SMALL
			printf("NODE %x TYPE %x FAILED SELF TEST. bicsr = %x\n",
				nodenum, dev_type, bi->bicsr);
#endif	SMALL
			continue;
		}
		bi->ber = 0x3fff0007;		/* clear bus error register */
		switch (dev_type) {
		case BI_UBA:
			if (nuba == 0) {
				ubaddr = ubaddrbi;
				umaddr = umaddrbi;
			}
			if (nuba < 4) {
				/*
				 * Lets follow the VAX630 practice:
				 * 	ubaddr+0x800 is the base of the
				 *	unibus map.
				 * 	umaddr is the base of a 256K space
				 	that has the dev regs at the end.
				 */
				ubaddr[nuba] = (struct uba_regs *)
							phys;
				umaddr[nuba] = (caddr_t)(window_space +
							 0x40000*nodenum);
			}
			nuba++;
			break;
		case 0xffff:
		case BI_NBI:
		case BI_XMI:
			bi->sadr = 0;
			bi->eadr = 0x200000;
			break;
		case BI_KDB50:
			if (nkdb == 0) {
				register int i;

				bi->intrdes = 0xffff;
				for (i = 0; i < 10000; i++) {
					if (i == 1)
						bi->bicsr |= BICSR_NRST;
				}
				udaddr = phys + 0xf2;
				iskdb50 = 1;
			}
			nkdb++;
			break;
		case 0:
			break;
		default:
			break;
		}
	}
}
#endif	defined(VAXBI)
