/* 
 **********************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 **********************************************************************
 * HISTORY
 * $Log:	nexus.h,v $
 * Revision 2.3  91/06/19  12:01:33  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:50:11  rvb]
 * 
 * Revision 2.2  91/05/13  06:07:45  af
 * 	Removed CMU conditionals.
 * 	[91/05/12  16:32:08  af]
 * 
 * Revision 2.1  89/08/03  16:27:22  rwd
 * Created.
 * 
 * 14-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH_KERNEL: remove Qbus and 650 support; add definition
 *	of struct nexusconnect.
 *
 * 10-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Support for VAX650: treat like 630.
 *
 * 25-Feb-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Install VM changes.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 16-May-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Carried over change below.
 *	[V1(1)]
 *
 * 17-Aug-84  Andy Gruss (gruss) at Carnegie-Mellon University
 *	CS_GFB:  New nexus type "NEX_GFB" added as support for Gruss
 *	frame buffer device.
 *
 **********************************************************************
 */

#ifdef	KERNEL
#include <platforms.h>

#else	KERNEL
#include <sys/features.h>
#endif	KERNEL
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)nexus.h	7.1 (Berkeley) 6/5/86
 */

#ifndef	ASSEMBLER
#include <sys/types.h>
#endif	ASSEMBLER

/*
 * Information about nexus's.
 *
 * Each machine has an address of backplane slots (nexi).
 * Each nexus is some type of adapter, whose code is the low
 * byte of the first word of the adapter address space.
 * At boot time the system looks through the array of available
 * slots and finds the interconnects for the machine.
 */
#define	NNEXSBI		16
#if VAX8600
#define	NNEX8600	NNEXSBI
#define	NEXA8600	((struct nexus *)(0x20000000))
#define	NEXB8600	((struct nexus *)(0x22000000))
#endif
#if VAX780
#define	NNEX780	NNEXSBI
#define	NEX780	((struct nexus *)0x20000000)
#endif
#if VAX750
#define	NNEX750	NNEXSBI
#define	NEX750	((struct nexus *)0xf20000)
#endif
#if VAX730
#define	NNEX730	NNEXSBI
#define	NEX730	((struct nexus *)0xf20000)
#endif

#if VAX8600
#define	MAXNNEXUS (2 * NNEXSBI)
#else 
#define	MAXNNEXUS NNEXSBI
#endif

#define	NEXSIZE	0x2000
#ifndef ASSEMBLER
struct	nexus {
	long	nex_csr;
	long	nex_pad[NEXSIZE / sizeof (long) - 1];
};
#endif

/*
 * Bits in high word of nexus's.
 */
#define	SBI_PARFLT	(1<<31)		/* sbi parity fault */
#define	SBI_WSQFLT	(1<<30)		/* write sequence fault */
#define	SBI_URDFLT	(1<<29)		/* unexpected read data fault */
#define	SBI_ISQFLT	(1<<28)		/* interlock sequence fault */
#define	SBI_MXTFLT	(1<<27)		/* multiple transmitter fault */
#define	SBI_XMTFLT	(1<<26)		/* transmit fault */

#define	NEX_CFGFLT	(0xfc000000)

#ifndef ASSEMBLER
#if defined(VAX780) || defined(VAX8600)
#define	NEXFLT_BITS \
"\20\40PARFLT\37WSQFLT\36URDFLT\35ISQFLT\34MXTFLT\33XMTFLT"
#endif
#endif

#define	NEX_APD		(1<<23)		/* adaptor power down */
#define	NEX_APU		(1<<22)		/* adaptor power up */

#define	MBA_OT		(1<<21)		/* overtemperature */

#define	UBA_UBINIT	(1<<18)		/* unibus init */
#define	UBA_UBPDN	(1<<17)		/* unibus power down */
#define	UBA_UBIC	(1<<16)		/* unibus initialization complete */

/*
 * Types for nex_type.
 */
#define	NEX_TYPE_MASK	0xff		/* types are in low 8 bits */

#define	NEX_ANY		0		/* pseudo for handling 11/750 */
#define	NEX_MEM4	0x08		/* 4K chips, non-interleaved mem */
#define	NEX_MEM4I	0x09		/* 4K chips, interleaved mem */
#define	NEX_MEM16	0x10		/* 16K chips, non-interleaved mem */
#define	NEX_MEM16I	0x11		/* 16K chips, interleaved mem */
#define	NEX_MBA		0x20		/* Massbus adaptor */
#define	NEX_UBA0	0x28		/* Unibus adaptor */
#define	NEX_UBA1	0x29		/* 4 flavours for 4 addr spaces */
#define	NEX_UBA2	0x2a
#define	NEX_UBA3	0x2b
#define	NEX_DR32	0x30		/* DR32 user i'face to SBI */
#define	NEX_CI		0x38		/* CI adaptor */
#define	NEX_MPM0	0x40		/* Multi-port mem */
#define	NEX_MPM1	0x41		/* Who knows why 4 different ones ? */
#define	NEX_MPM2	0x42
#define	NEX_MPM3	0x43
#define	NEX_MEM64L	0x68		/* 64K chips, non-interleaved, lower */
#define	NEX_MEM64LI	0x69		/* 64K chips, ext-interleaved, lower */
#define	NEX_MEM64U	0x6a		/* 64K chips, non-interleaved, upper */
#define	NEX_MEM64UI	0x6b		/* 64K chips, ext-interleaved, upper */
#define	NEX_MEM64I	0x6c		/* 64K chips, interleaved */
#define	NEX_MEM256L	0x70		/* 256K chips, non-interleaved, lower */
#define	NEX_MEM256LI	0x71		/* 256K chips, ext-interleaved, lower */
#define	NEX_MEM256U	0x72		/* 256K chips, non-interleaved, upper */
#define	NEX_MEM256UI	0x73		/* 256K chips, ext-interleaved, upper */
#define	NEX_MEM256I	0x74		/* 256K chips, interleaved */
#if	MACH
#define	NEX_GFB		0xc0		/* New one for Gruss frame buffer */
#endif	MACH

#ifndef	ASSEMBLER
/*
 * Description of a main bus that maps "nexi", ala the 780 SBI.
 */
struct nexusconnect {
	short	psb_nnexus;		/* number of nexus slots */
	struct	nexus *psb_nexbase;	/* base of nexus space */
	short	psb_ubatype;		/* type of unibus adaptor */
	short	psb_nubabdp;		/* number of bdp's per uba */
/* we should be able to have just one address for the unibus memories */
/* and calculate successive addresses by adding to the base, but the 750 */
/* doesn't obey the sensible rule: uba1 has a lower address than uba0! */
	caddr_t	*psb_umaddr;		/* unibus memory addresses */
/* the 750 has some slots which don't promise to tell you their types */
/* if this pointer is non-zero, then you get the type from this array */
/* rather than from the (much more sensible) low byte of the config register */
	short	*psb_nextype;		/* botch */
};
#endif	ASSEMBLER
