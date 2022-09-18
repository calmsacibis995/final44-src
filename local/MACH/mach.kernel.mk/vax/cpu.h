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
 * $Log:	cpu.h,v $
 * Revision 2.6  89/03/09  22:13:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  20:12:32  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/24  02:57:28  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  19:01:29  mwyoung]
 * 
 *
 * Revision 2.3  88/08/10  10:22:45  rvb
 *  26-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	From now on the variable, "cpu", is the machine architecture.
 * 	Every machine gets a unique "cpu" value.  "cpu_sid" is what
 * 	the SID register says the cpu is.  For cpu_sid == VAX_650,
 * 	we have two machines, VAX_650 and VAX_6200.  Them is the breaks.
 * 
 *  10-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 * 	Support for VAX650.
 * 
 * 18-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Define cpu_number() as a macro returning 0 for single-cpu
 *	systems.
 *
 *  5-Aug-87  David Golub (dbg) at Carnegie-Mellon University
 *	Moved CPU_NUMBER_R0 to vax/asm.h.
 *
 *  2-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for VAX-8800.  Removed some gratuitous conditionals.
 *
 * 19-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Eliminated CS_NEWCPU.
 *
 * 25-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC: reorganized ASSEMBLER and <sys/types.h> use.
 *	CS_NEWCPU:  updated for new processor specific support where
 *	still not provided in 4.3.
 *
 *  9-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed cpu_number_addr and CPU_NUMBER_DEST.  They are
 *	overridden by the cpu_number routine and CPU_NUMBER_R0 macros.
 *
 *  2-May-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Preliminary support for VAX 8200 (KA820).
 *
 */
 
#ifdef	KERNEL
#include <cpus.h>
#include <cputypes.h>
#endif	KERNEL
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)cpu.h	7.1 (Berkeley) 6/5/86
 */
#ifndef	_CPU_
#define _CPU_
 
/* 
 *  The ASSEMBLER flag subsumes LOCORE at CMU.
 */
#ifdef	ASSEMBLER
#ifdef	LOCORE
#define LOCORE_	1
#else	LOCORE
#define LOCORE_	0
#endif	LOCORE
#undef	LOCORE
#define LOCORE	1
#endif	ASSEMBLER

#ifndef	LOCORE
/* 
 *  We use these types in the definitions below and hence ought to include them
 *  directly to aid new callers (even if our caller is likely to have already
 *  done so).
 */
#include <sys/types.h>

/*
 * Cpu identification, from SID register.
 */
union cpusid {
	int	cpusid;
	struct cpuany {
		u_int	:24,
			cp_type:8;
	} cpuany;
	struct cpu8600 {
		u_int	cp_sno:12,		/* serial number */
			cp_plant:4,		/* plant number */
			cp_eco:8,		/* eco level */
			cp_type:8;		/* VAX_8600 */
	} cpu8600;
#if	VAX820 || CMUCS
	struct cpu820 {
		u_int	cp_urev:8,		/* ucode rev */
			cp_sp:1,		/* secondary patch */
			cp_prev:10,		/* patch rev */
			cp_crev:5,		/* cpu rev */
			cp_type:8;		/* VAX820 */
	} cpu820;
#endif	VAX820 || CMUCS
	struct cpu780 {
		u_int	cp_sno:12,		/* serial number */
			cp_plant:3,		/* plant number */
			cp_eco:9,		/* eco level */
			cp_type:8;		/* VAX_780 */
	} cpu780;
	struct cpu750 {
		u_int	cp_hrev:8,		/* hardware rev level */
			cp_urev:8,		/* ucode rev level */
			:8,
			cp_type:8;		/* VAX_750 */
	} cpu750;
	struct cpu730 {
		u_int	:8,			/* reserved */
			cp_urev:8,		/* ucode rev level */
			:8,			/* reserved */
			cp_type:8;		/* VAX_730 */
	} cpu730;
 	struct cpu650 {
 		u_int	cp_urev:8,		/* ucode rev level */
			:16,			/* reserved */
 			cp_type:8;		/* VAX_650 */
 	} cpu650;
 	struct cpu630 {
 		u_int	:24,			/* reserved */
 			cp_type:8;		/* VAX_630 */
 	} cpu630;
#if	VAX1 || CMUCS
	struct cpu1 {
		u_int	cp_hrev:8,		/* hardware rev level */
			cp_urev:8,		/* ucode rev level */
			:8,
			cp_type:8;		/* VAX_1 */
	} cpu1;
#endif	VAX1 || CMUCS
};
#endif
/*
 * Vax CPU types.
 * Similar types are grouped with their earliest example.
 */
/*
 *	Need to finish processor type table
 */
#define SYSTYPE		((int *) (0x20040004))

#define VAX_780		1
#define VAX_750		2
#define VAX_730		3
#define VAX_8600	4
#define VAX_820		5
#define VAX_8800	6
#define VAX_1		7
#define VAX_630		8
#define VAX_650		10
#define VAX_6200	11

#define VAX_MAX		11

/*
 * Main IO backplane types.
 * This gives us a handle on how to do autoconfiguration.
 */
#define IO_SBI780	1
#define IO_CMI750	2
#define IO_XXX730	3
#define IO_ABUS		4
#define IO_QBUS		5
#define IO_BI		6

#ifndef	LOCORE
/*
 * Per-cpu information for system.
 */
struct	percpu {
	short	pc_cputype;		/* cpu type code */
	short	pc_cpuspeed;		/* relative speed of cpu */
	short	pc_nioa;		/* number of IO adaptors/nexus blocks */
	struct	iobus *pc_io;		/* descriptions of IO adaptors */
};

struct iobus {
	int	io_type;		/* io adaptor types */
	caddr_t	io_addr;		/* phys address of IO adaptor */
	int	io_size;		/* size of an IO space */
	caddr_t	io_details;		/* specific to adaptor types */
};

/*
 * Description of a main bus that maps "nexi", ala the 780 SBI.
 */
struct nexusconnect {
	short	psb_nnexus;		/* number of nexus slots */
	struct	nexus *psb_nexbase;	/* base of nexus space */
/* we should be able to have just one address for the unibus memories */
/* and calculate successive addresses by adding to the base, but the 750 */
/* doesn't obey the sensible rule: uba1 has a lower address than uba0! */
	caddr_t	*psb_umaddr;		/* unibus memory addresses */
	short	psb_nubabdp;		/* number of bdp's per uba */
	short	psb_haveubasr;		/* have uba status register */
/* the 750 has some slots which don't promise to tell you their types */
/* if this pointer is non-zero, then you get the type from this array */
/* rather than from the (much more sensible) low byte of the config register */
	short	*psb_nextype;		/* botch */
};

#ifdef	KERNEL
int	cpu;
struct	percpu percpu[];
int	master_cpu;
#if	NCPUS == 1
#define cpu_number()	(0)
#define set_cpu_number()
#endif	NCPUS == 1
#endif
#endif
#ifdef	LOCORE_
#undef	LOCORE
#if	LOCORE_
#define LOCORE	1
#endif	LOCORE_
#undef	LOCORE_
#endif	LOCORE_
#endif	_CPU_
