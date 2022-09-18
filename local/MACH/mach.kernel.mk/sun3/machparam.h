/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	machparam.h,v $
 * Revision 2.8  90/07/03  16:48:12  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:14:42  mrt]
 * 
 * Revision 2.7  89/07/11  13:56:01  jjc
 * 	Added definition of SYSBASE.
 * 	[89/07/05  20:21:02  jjc]
 * 
 * Revision 2.6  89/03/09  21:36:29  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  19:44:47  gm0w
 * 	Added include of cputypes.h as SUN3_260 was being used but
 * 	not defined.
 * 	[89/02/19            mrt]
 * 
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * Revision 2.4  88/08/09  17:46:36  rvb
 * gcc asm is now the rule.
 *
 * 29-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	GCC: Code for "asm" expansion of the spl's rather than using the
 *	inline program.
 *	The code is not active right now awaiting resolving of some
 *	compiler problems.
 *
 * 26-Jun-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added defintions of NSGVA, VAC, and shm_alignment.
 *
 *  2-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Fixed mach_tt.h include for non-kernel compilation.
 *
 * 30-Apr-87  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: remove definition of UADDR.
 *
 * 23-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Reduce KERNELBASE to 0xE000000 to allow 32 megabytes of kernel
 *	virtual space.
 *
 * 22-Oct-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added definition of splbio.
 *
 * 20-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added definitions of splhigh, splvm, splsched, splsoftclock,
 *	and spltty.
 *	Moved u-area from above monitor to beginning of segment below
 *	kernel.
 *
 */
/*      @(#)param.h 1.1 86/02/03 SMI      */

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 *
 * This file is intended to contain the
 * specific details of a given architecture.
 */

#ifndef	_MACHPARAM_H_
#define _MACHPARAM_H_

#ifdef	KERNEL
#include <cputypes.h>
#endif	KERNEL

#include <mach/sun3/vm_param.h>

#define	MACHINE	"sun3"

#include <machine/endian.h>

/*
 * Machine dependent constants for Sun-3.
 */
#define NBPG	SUN3_PGBYTES	/* bytes/page */
#define PGOFSET	(NBPG-1)	/* byte offset into page */
#define PGSHIFT	SUN3_PGSHIFT	/* LOG2(NBPG) */

#define NBSG	131072		/* bytes/segment */
#define SGOFSET	(NBSG-1)	/* byte offset into segment */
#define SGSHIFT	17		/* LOG2(NBSG) */
#define NSGVA	2048		/* segments per virtual address space */

#define CLSIZE		1
#define CLSIZELOG2	0

#define SSIZE		1	/* initial stack size/NBPG */
#define SINCR		1	/* increment of stack/NBPG */

#define	CHAR_BIT	NBBY
#define	CHAR_MAX	0x7f
#define	CHAR_MIN	0x80
#define	CLK_TCK		60			/* for times() */
#define	INT_MAX		0x7fffffff
#define	INT_MIN		0x80000000
#define	LONG_MAX	0x7fffffff
#define	LONG_MIN	0x80000000
#define	SCHAR_MAX	0x7f
#define	SCHAR_MIN	0x80
#define	SHRT_MAX	0x7fff
#define	SHRT_MIN	0x8000
#define	UCHAR_MAX	0xff
#define	UINT_MAX	0xffffffff
#define	ULONG_MAX	0xffffffff
#define	USHRT_MAX	0xffff

/*
 * Define UADDR as a 32 bit address so that the compiler will
 * generate short absolute references to access the u-area.
 */
#define UPAGES		1	/* pages of u-area, NOT including red zone */

#define KERNSTACK	0x800	/* size of kernel stack in u-area */

#define SYSBASE		0x0F000000

/*
 * Some macros for units conversion
 */
/* Core clicks (8192 bytes) to segments and vice versa */
#define ctos(x)	(((x)+15)>>(SGSHIFT-PGSHIFT))
#define stoc(x)	((x)<<(SGSHIFT-PGSHIFT))

/* Page number to segment number */
#define ptos(x)	((x)>>(SGSHIFT-PGSHIFT))

/* Core clicks (8192 bytes) to disk blocks and vice versa */
#define ctod(x)	((x)<<4)
#define dtoc(x)	(((x)+15)>>4)
#define dtob(x)	((x)<<9)

/* clicks to bytes */
#define ctob(x)	((x)<<PGSHIFT)

/* bytes to clicks */
#define btoc(x)	((((unsigned)(x)+(NBPG-1))>>PGSHIFT))

#define	btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
	((unsigned)(bytes) >> DEV_BSHIFT)
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
	((unsigned)(db) << DEV_BSHIFT)

/*
 * Map a ``block device block'' to a file system block.
 * This should be device dependent, and will be if we
 * add an entry to cdevsw/bdevsw for that purpose.
 * For now though just use DEV_BSIZE.
 */
#define	bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))

/*
 * Macros to decode processor status word.
 */
#define USERMODE(ps)	(((ps) & SR_SMODE) == 0)
#define BASEPRI(ps)	(((ps) & SR_INTPRI) == 0)

/*
 * Delay units are in microseconds.
 */
#define DELAY(n)	\
{ \
	extern int cpudelay; \
	register int N = (((n)<<4) >> cpudelay); \
 \
	while (--N > 0) ; \
}

#define CDELAY(c, n)	\
{ \
	extern int cpudelay; \
	register int N = (((n)<<3) >> cpudelay); \
 \
	while (--N > 0) \
		if (c) \
			break; \
}

/*
 * Macros for setting interrupt priority levels
 */
#ifdef	__GNU__
#define splx(y) \
({ int _spl__, _tmp1__, _tmp2__; \
	asm volatile("movew sr, %0" : "=d" (_spl__) : "r" (_tmp1__)); \
	asm volatile("movew %1, sr" : "=r" (_tmp2__) : "di" (y)); \
	_spl__; })

#define splzs()		splx(0x2600)
#define spl7()		splx(0x2700)
#define spl6()		splx(0x2500)
#define spl5()		splx(0x2500)
#define spl4()		splx(0x2400)
#define spl3()		splx(0x2300)
#define spl2()		splx(0x2200)
#define spl1()		splx(0x2100)
#define spl0()		splx(0x2000)

#define np_splhigh()	splx(0x2700)
#define np_splx(x)	splx(x)


#define splr(y) \
({ int _spl__; \
	asm volatile("movew sr, %0; andw #0x2700, %0; cmpw %1, %0; jge 1f; movew %1, sr; 1:" : "=di" (_spl__) : "di" (y)); \
	_spl__; })

#define splimp()	splr(0x2300)
#define splnet()	splr(0x2100)
#define splie()		splr(0x2300)
#define splclock()	splr(0x2500)
#endif	__GNU__

#define splhigh()	spl7()
#define splsched()	spl7()
#define splsoftclock()	spl1()
#define spltty()	splzs()
#define splvm()		splimp()	/* highest interrupt that plays
					   with VM */
#define splbio()	spl6()

/*
 * Define the VAC symbol if we could run on a machine
 * which has a Virtual Address Cache (e.g. SUN3_260)
 */
#if	defined(KERNEL) && defined(SUN3_260)
#define VAC
#else	defined(KERNEL) && defined(SUN3_260)
#undef VAC
#endif	defined(KERNEL) && defined(SUN3_260)

/*
 * The Virtual Address Cache in Sun-3 requires aliasing addresses be
 * matched in modulo 128K (0x20000) to guarantee data consistency.
 */
#define shm_alignment \
    ((cpu == CPU_SUN3_260) ? 0x20000 : CLBYTES)	/* shared memory alignment */

#endif	_MACHPARAM_H_
