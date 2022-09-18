/* 
 **********************************************************************
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 **********************************************************************
 */ 
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)machparam.h	7.1 (Berkeley) 6/5/86
 */
/*
 **********************************************************************
 * HISTORY
 * $Log:	vm_defs.h,v $
 * Revision 2.1  89/08/03  16:28:26  rwd
 * Created.
 * 
 * 10-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Removed all but VAX page-size related definitions.  This file
 *	should be replaced by vax/vm_param.h, but I don't want to
 *	rewrite all of the affected files to use the new definitions.
 *
 **********************************************************************
 */
 

/*
 * Machine dependent constants for vax.
 */
#define	NBPG	512		/* bytes/page */
#define	PGOFSET	(NBPG-1)	/* byte offset into page */
#define	PGSHIFT	9		/* LOG2(NBPG) */

/*
 * Some macros for units conversion
 */

/* Core clicks (512 bytes) to disk blocks */
#define	ctod(x)	(x)
#define	dtoc(x)	(x)
#define	dtob(x)	((x)<<9)

/* clicks to bytes */
#define	ctob(x)	((x)<<PGSHIFT)
#define	ptob(x)	((caddr_t)((x)<<PGSHIFT))

/* bytes to clicks, with rounding */
#define	btoc(x)	((((unsigned)(x)+(NBPG-1))>>PGSHIFT))

/* bytes to clicks, without rounding */
#define	btop(x)	(((unsigned)(x))>>PGSHIFT)

/* running average - needs floating-point! */
#define	ave(smooth, cnt, time) \
	smooth = ((time - 1) * (smooth) + (cnt)) / (time)

#ifdef KERNEL
#ifndef LOCORE
int	cpuspeed;
#endif
#define	DELAY(n)	{ register int N = cpuspeed * (n); while (--N > 0); }

#else KERNEL
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
#endif KERNEL
