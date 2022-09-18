/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	param.h,v $
 * Revision 2.2  89/07/11  23:32:25  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)param.h 1.6 88/03/01 SMI	*/

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 *
 * This file is intended to contain the basic
 * specific details of a given architecture.
 */

#ifndef _SUN4_PARAM_
#define _SUN4_PARAM_

/*
 * Machine dependent constants for Sun4.
 */

/*
 * Define the VAC symbol if we could run on a machine
 * which has a Virtual Address Cache (e.g. SUN4_260)
 */
#ifdef SUN4_260
#define VAC
#else
#undef VAC
#endif SUN4_260

/*
 * Define the FPU symbol if we could run on a machine with an external
 * FPU (i.e. not integrated with the normal machine state like the vax).
 */
#define FPU

/*
 * MMU_PAGES* describes the physical page size used by the mapping hardware.
 * PAGES* describes the logical page size used by the system.
 */

#define	MMU_PAGESIZE	0x2000		/* 8192 bytes */
#define	MMU_PAGESHIFT	13		/* log2(MMU_PAGESIZE) */
#define	MMU_PAGEOFFSET	(MMU_PAGESIZE-1)/* Mask of address bits in page */
#define	MMU_PAGEMASK	(~MMU_PAGEOFFSET)

#define	PAGESIZE	0x2000		/* All of the above, for logical */
#define	PAGESHIFT	13
#define	PAGEOFFSET	(PAGESIZE - 1)
#define	PAGEMASK	(~PAGEOFFSET)

/*
 * DATA_ALIGN is used to define the alignment of the Unix data segment.
 */
#define	DATA_ALIGN	0x2000

/*
 * Some random macros for units conversion.
 */

/*
 * MMU pages to bytes, and back (with and without rounding)
 */
#define	mmu_ptob(x)	((x) << MMU_PAGESHIFT)
#define	mmu_btop(x)	(((unsigned)(x)) >> MMU_PAGESHIFT)
#define	mmu_btopr(x)	((((unsigned)(x) + MMU_PAGEOFFSET) >> MMU_PAGESHIFT))

/*
 * pages to bytes, and back (with and without rounding)
 */
#define	ptob(x)		((x) << PAGESHIFT)
#define	btop(x)		(((unsigned)(x)) >> PAGESHIFT)
#define	btopr(x)	((((unsigned)(x) + PAGEOFFSET) >> PAGESHIFT))

/*
 * 2 versions of pages to disk blocks
 */
#define	mmu_ptod(x)	((x) << (MMU_PAGESHIFT - DEV_BSHIFT))
#define	ptod(x)		((x) << (PAGESHIFT - DEV_BSHIFT))

/*
 * Delay units are in microseconds.
 */
#define	DELAY(n)	\
{ \
	extern int cpudelay; \
	register int N = ((unsigned)((n)<<4) >> cpudelay); \
 \
	while (--N > 0) ; \
}

#define	CDELAY(c, n)	\
{ \
	extern int cpudelay; \
	register int N = ((unsigned)((n)<<3) >> cpudelay); \
 \
	while (--N > 0) \
		if (c) \
			break; \
}

/*
 * The Virtual Address Cache in Sun-4 requires aliasing addresses be
 * matched in modulo 256K (0x40000) to guarantee data consistency.
 */
#define shm_alignment	((cpu == CPU_SUN4_260) ? 0x20000 : PAGESIZE)

/*
 * UADDR and KERNSTACK must be defined such that the part of the u area
 * above the kernel stack must be >= (-4096) so that it may be addressed by
 * using g0 as a base register.
 */
#define	UPAGES		2	/* pages of u-area, NOT including red zone */

#if UPAGES == 2
#define	KERNSTACK	0x3000	/* size of kernel stack in u-area */
#endif UPAGES == 2

#if UPAGES == 1
#define	KERNSTACK	0x1800	/* size of kernel stack in u-area */
#endif UPAGES == 1

#define	UADDR		(0-(NBPG*UPAGES)) /* u-area virtual address */

/*
 * KERNSIZE the amount of vitual address space the kernel
 * uses in all contexts.
 */
#define KERNELSIZE	(128*1024*1024)

/*
 * KERNELBASE is the virtual address which
 * the kernel text/data mapping starts in all contexts.
 */
#define	KERNELBASE	(0-KERNELSIZE)

/*
 * SYSBASE is the virtual address which
 * the kernel allocated memory mapping starts in all contexts.
 */
#define	SYSBASE		(0-(16*1024*1024))

/*
 * Msgbuf size.
 */
#define MSG_BSIZE       ((7 * 1024) - sizeof (struct msgbuf_hd))

/*
 * XXX - Macros for compatibility
 */
/* Clicks (MMU PAGES) to disk blocks */
#define	ctod(x)		mmu_ptod(x)

/* Clicks (MMU PAGES) to bytes, and back (with rounding) */
#define	ctob(x)		mmu_ptob(x)
#define	btoc(x)		mmu_btopr(x)

/*
 * XXX - Old names for some backwards compatibility
 */
#define	NBPG		MMU_PAGESIZE
#define	PGOFSET		MMU_PAGEOFFSET
#define	PGSHIFT		MMU_PAGESHIFT

#define	CLSIZE		1
#define	CLSIZELOG2	0
#define	CLBYTES		PAGESIZE
#define	CLOFSET		PAGEOFFSET
#define	CLSHIFT		PAGESHIFT
#define	clrnd(i)	(i)

#endif /* _SUN4_PARAM_ */
