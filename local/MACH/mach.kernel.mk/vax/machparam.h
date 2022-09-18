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
 * $Log:	machparam.h,v $
 * Revision 2.5  89/03/09  22:18:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  20:25:12  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/24  03:01:24  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  18:57:41  mwyoung]
 * 
 *
 * 30-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  Always use UPAGES of 16 rather than just under
 *	MACH; the current RFS operation abort code will often cause
 *	a kernel stack overflow with only 12 pages.
 *	[ V5.1(XF20) ]
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3
 *
 * 19-Jun-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC:  Expanded UPAGES to 12 since with the extended
 *	number of file descriptors, the old size only allowed for one
 *	kernel stack page before reaching the red-zone.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)machparam.h	7.1 (Berkeley) 6/5/86
 */

/*
 * Machine dependent constants for vax.
 */
#define NBPG	512		/* bytes/page */
#define PGOFSET	(NBPG-1)	/* byte offset into page */
#define PGSHIFT	9		/* LOG2(NBPG) */

#define CLSIZE		2
#define CLSIZELOG2	1

#define SSIZE	4		/* initial stack size/NBPG */
#define SINCR	4		/* increment of stack/NBPG */

#define UPAGES	16		/* pages of u-area */

/*
 * Some macros for units conversion
 */
/* Core clicks (512 bytes) to segments and vice versa */
#define ctos(x)	(x)
#define stoc(x)	(x)

/* Core clicks (512 bytes) to disk blocks */
#define ctod(x)	(x)
#define dtoc(x)	(x)
#define dtob(x)	((x)<<9)

/* clicks to bytes */
#define ctob(x)	((x)<<9)

/* bytes to clicks */
#define btoc(x)	((((unsigned)(x)+511)>>9))

/*
 * Macros to decode processor status word.
 */
#define USERMODE(ps)	(((ps) & PSL_CURMOD) == PSL_CURMOD)
#define BASEPRI(ps)	(((ps) & PSL_IPL) == 0)

#ifdef	KERNEL
#ifndef	LOCORE
int	cpuspeed;
#endif
#define DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }

#else	KERNEL
#define DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif	KERNEL
