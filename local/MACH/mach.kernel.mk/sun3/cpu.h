/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	cpu.h,v $
 * Revision 2.8  89/03/09  21:32:26  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  19:33:34  gm0w
 * 	Added include of cputypes.h under and #ifdef KERNEL and removed
 * 	the include of sys/features.h
 * 	[89/02/18            mrt]
 * 
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.6  88/12/19  02:49:21  mwyoung
 * 	Fix include file references.
 * 	[88/12/19  00:40:34  mwyoung]
 *
 * Revision 2.3.3.1  88/12/13  03:29:21  mwyoung
 * 	Make declarations "extern".  Fix include file references.
 * 	Remove old and redudant code.
 * 	[88/12/12            mwyoung]
 * 
 * Revision 2.5  88/12/08  15:36:19  mikeg
 * 	Entered cpu.h into the kernel RCS tree with Jonathan Chew's 
 * 	changes for the DVMA problem in the new kernels.
 * 	[88/11/30  15:21:57  mikeg]
 *
 * 08-Jul-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Defined DVMA_KLUGE for Sun 3.
 *	Added definitions for MACH_E and CPU_SUN3_E.
 *
 *  1-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Changes for new pmap module:
 *		Do not define pmeg and context for mach
 *
 * 07-Aug-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Fixed up include of types.h for both kernel and user
 *	programs to include.
 *
 * 23-Jun-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added declarations for virtual address cache and Sun 3/110.
 *
 * 23-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Proper includes for options.
 *
 * 23-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Define cpu_number as a macro returning 0.
 *
 *  3-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added conditional compilation depending on whether "_CPU_"
 *	is defined.
 *	Included "mmu.h" so "NSEGMAP" will be defined.
 *
 * 18-Jul-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed pointers in context and pmeg structures to point at
 *	the pmaps they belong to rather than the proc.s they belong
 *	to.
 *
 * 20-Jun-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added definition of "master_cpu".
 *
 */

/*      @(#)cpu.h 1.6 87/02/16 SMI      */

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 *
 * This file is intended to contain the specific details
 * of various implementations of a given architecture.
 */

#ifndef	CPU_H_
#define CPU_H_

#ifdef	KERNEL
#include <cputypes.h>
#endif	KERNEL

/* This was included in Sun 3.0 but not 3.4 */
#ifndef	ASSEMBLER
#include <mon/sunromvec.h>
#endif	ASSEMBLER

#include <sys/types.h>
#include <sun3/mmu.h>

#define CPU_ARCH	0xf0		/* mask for architecture bits */
#define SUN3_ARCH	0x10		/* arch value for Sun 3 */

#define CPU_MACH	0x0f		/* mask for machine implementation */
#define MACH_160	0x01
#define MACH_50		0x02
#define MACH_260	0x03
#define MACH_110	0x04
#define MACH_60		0x07
#define MACH_E		0x08

#define CPU_SUN3_160	(SUN3_ARCH + MACH_160)
#define CPU_SUN3_50	(SUN3_ARCH + MACH_50)
#define CPU_SUN3_260	(SUN3_ARCH + MACH_260)
#define CPU_SUN3_110	(SUN3_ARCH + MACH_110)
#define CPU_SUN3_60	(SUN3_ARCH + MACH_60)
#define CPU_SUN3_E	(SUN3_ARCH + MACH_E)

#if	defined(KERNEL) && !defined(LOCORE)
#ifndef	ASSEMBLER
extern int cpu;				/* machine type we are running on */
extern int dvmasize;			/* usable dvma size in clicks */
extern int fbobmemavail;		/* video copy memory is available */
#ifdef	SUN3_260
extern int vac;				/* there is virtual address cache */
#endif	SUN3_260


/*
 * Macros that are nothing until have multiprocessor
 */
#define halt_cpu()
#define set_cpu_number()

#define cpu_number()	(0)

int	master_cpu;
#endif	ASSEMBLER

#define CPU_NUMBER_D0	movl	#0,d0
#endif	defined(KERNEL) && !defined(LOCORE)

#if	!defined(LOCORE) && !defined(ASSEMBLER)
#define CSEG	((MONSTART - NBSG) >> SGSHIFT)
#endif	!LOCORE

/*
 * Various I/O space related constants
 */
#define VME16_BASE	0xFFFF0000
#define VME16_SIZE	(1<<16)
#define VME16_MASK	(VME16_SIZE-1)

#define VME24_BASE	0xFF000000
#define VME24_SIZE	(1<<24)
#define VME24_MASK	(VME24_SIZE-1)

/*
 * The Basic DVMA space size for all Sun-3 implementations
 * is given by DVMASIZE.  The actual usable dvma size
 * (in clicks) is given by the dvmasize variable declared
 * above (for compatibility with Sun-2).
 */
#define DVMASIZE	0x100000
#if	sun3
#define DVMA_KLUGE	0x0F000000
#endif	sun3

/*
 * FBSIZE is the amount of memory we will use for the frame buffer 
 * copy region if the copy mode of the frame buffer is to be used.
 */
#define FBSIZE   0x20000	/* size of frame buffer memory region */
#define OBFBADDR 0x100000	/* location of frame buffer in memory */
#endif	CPU_H_
