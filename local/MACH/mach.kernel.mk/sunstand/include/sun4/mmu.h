/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mmu.h,v $
 * Revision 2.2  89/07/11  23:32:18  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)mmu.h 1.10 88/02/08 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#ifndef _MMU_
#define _MMU_

/* 
 * Sun-4 memory management unit.
 * All sun-4 implementations use 32 bits of address.
 * A particular implementation may implement a smaller MMU.
 * If so, the missing addresses are in the "middle" of the
 * 32 bit address space. All accesses in this range behave
 * as if there was an invalid page map entry correspronding
 * to the address.
 */

/* 
 * Hardware context and segment information
 * Mnemonic decoding:
 *	PMENT - Page Map ENTry 
 *	PMGRP - Group of PMENTs (aka "segment")
 */
/* fixed SUN4 constants */
#define	NPMENTPERPMGRP		32
#define	NPMENTPERPMGRPSHIFT	5	/* log2(NPMENTPERPMGRP) */
#define	PMGRPSIZE	(NPMENTPERPMGRP * PAGESIZE)
#define PMGRPOFFSET	(PMGRPSIZE - 1)
#define	PMGRPSHIFT	(PAGESHIFT + NPMENTPERPMGRPSHIFT)
#define	PMGRPMASK	(~PMGRPOFFSET)

/* variable (per implementation) */

/* SUN4_260 */
#define	NCTXS_260		16
#define	NPMGRPPERCTX_260	4096
#define	NPMGRPS_260		512
/* SUN4_110 */
#define	NCTXS_110		8
#define	NPMGRPPERCTX_110	4096
#define	NPMGRPS_110		256

/*
 * Useful defines for hat constants
 */
#define NCTXS		nctxs
#define NPMGRPS		npmgrps
#define NPMGRPPERCTX	npmgrpperctx

/*
 * Max size parameters for vm_hat.
 */
#define MNCTXS		16
#define MNPMGRPS	512
#define MNPMENTS	(MNPMGRPS * NPMENTPERPMGRP)

/*
 * Variables set at boot time to reflect cpu type.
 */
#ifndef LOCORE
extern u_int nctxs;		/* number of implemented contexts */
extern u_int npmgrpperctx;	/* number of pmgrps per context */
extern u_int npmgrps;		/* number of pmgrps in page map */
extern u_int segmask;		/* mask for segment number */
extern addr_t hole_start;	/* addr of start of MMU "hole" */
extern addr_t hole_end;		/* addr of end of MMU "hole" */

#define	PMGRP_INVALID (NPMGRPS - 1)

/*
 * Macro to determine whether an address is within the range of the MMU.
 */
#define good_addr(a) \
	((addr_t)(a) < hole_start || (addr_t)(a) >= hole_end)
#endif !LOCORE

/*
 * Address space identifiers.
 */
#define	ASI_UP	0x8		/* user program */
#define	ASI_SP	0x9		/* supervisor program */
#define	ASI_UD	0xA		/* user data */
#define	ASI_SD	0xB		/* supervisor data */
#define ASI_FCS	0xC		/* flush cache segment */
#define ASI_FCP	0xD		/* flush cache page */
#define ASI_FCC	0xE		/* flush cache context */
#define ASI_CD	0xF		/* cache data */
#define	ASI_CTL	0x2		/* control space*/
#define	ASI_SM	0x3		/* segment map */
#define	ASI_PM	0x4		/* page map */

/*
 * ASI_CTL addresses
 */
#define	ID_PROM		0x00000000
#define	CONTEXT_REG	0x30000000
#define	SYSTEM_ENABLE	0x40000000
#define	BUS_ERROR_REG	0x60000000
#define	DIAGNOSTIC_REG	0x70000000
#define	CACHE_TAGS	0x80000000
#define	VME_INT_VEC	0xE0000000
#define	UART_BYPASS	0xF0000000

#define IDPROMSIZE	0x20		/* size of id prom in bytes */

/*
 * Constants for cache operations.
 * XXX Some of these are variable in the architecture,
 * but for now we will leave them be.
 */
#define VAC_SIZE		     0x20000	/* 128K */
#define VAC_LINESIZE			  16	/* 16 bytes per line */
#define VAC_LINESHIFT			   4	/* LOG2(VAC_LINESIZE) */
#define VAC_NLINES     VAC_SIZE/VAC_LINESIZE 	/* # of lines in cache */
#define VAC_CTXFLUSH_COUNT	  VAC_NLINES	/* context flush count */
#define VAC_SEGFLUSH_COUNT	  VAC_NLINES	/* segment flush count */
#define VAC_PAGEFLUSH_COUNT		 512	/* page flush count */

/*
 * Various I/O space related constants
 */
#define	VME16_BASE	0xFFFF0000
#define	VME16_SIZE	(1<<16)
#define	VME16_MASK	(VME16_SIZE-1)

#define	VME24_BASE	0xFF000000
#define	VME24_SIZE	(1<<24)
#define	VME24_MASK	(VME24_SIZE-1)

/*
 * The usable DVMA space size.
 */
#define	DVMASIZE	((1024*1024)-PMGRPSIZE)
#define DVMABASE	(0-(1024*1024))

/*
 * Context for kernel. On a Sun-4 the kernel is in every address space,
 * but KCONTEXT is magic in that there is never any user context there.
 */
#define	KCONTEXT	0

/*
 * SEGTEMP & SEGTEMP2 are virtual segments reserved for temporary operations.
 * We use the segments immediately before the start of debugger area.
 */
#include <debug/debug.h>
#define SEGTEMP		((addr_t)(DEBUGSTART - (2 * PMGRPSIZE)))
#define SEGTEMP2	((addr_t)(DEBUGSTART - PMGRPSIZE))

#if defined(KERNEL) && !defined(LOCORE)
/*
 * Low level mmu-specific functions 
 */
struct	ctx *mmu_getctx();
void	mmu_setctx(/* ctx */);
void	mmu_setpmg(/* base, pmg */);
void	mmu_settpmg(/* base, pmg */);
struct	pmgrp *mmu_getpmg(/* base */);
void	mmu_setpte(/* base, pte */);
void	mmu_getpte(/* base, ppte */);
void	mmu_getkpte(/* base, ppte */);
void	mmu_pmginval(/* pmg */);

/*
 * Cache specific routines - ifdef'ed out if there is no chance
 * of running on a machine with a virtual address cache.
 */
#ifdef VAC
void	vac_init();
void	vac_flushall();
void	vac_ctxflush();
void	vac_segflush(/* base */);
void	vac_pageflush(/* base */);
void	vac_flush(/* base, len */);
#else VAC
#define	vac_init()
#define	vac_flushall()
#define	vac_ctxflush()
#define	vac_segflush(base)
#define	vac_pageflush(base)
#define	vac_flush(base, len)
#endif VAC

int	valid_va_range(/* basep, lenp, minlen, dir */);

#endif defined(KERNEL) && !defined(LOCORE)

#endif !_MMU_
