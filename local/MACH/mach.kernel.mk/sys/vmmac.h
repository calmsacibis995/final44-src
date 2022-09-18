/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmmac.h,v $
 * Revision 2.4  89/03/15  15:59:27  gm0w
 * 	Elimiated everything that is unused by Mach
 * 	[89/03/14            mrt]
 * 
 * Revision 2.3  89/03/09  22:10:55  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  17:58:57  gm0w
 * 	Changes for cleanup.
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)vmmac.h	7.1 (Berkeley) 6/4/86
 */

/*
 * Virtual memory related conversion macros
 */

#ifndef	_SYS_VMMAC_H_
#define _SYS_VMMAC_H_

/* Bytes to pages without rounding, and back */
#define btop(x)		(((unsigned)(x)) >> PGSHIFT)
#define ptob(x)		((caddr_t)((x) << PGSHIFT))

/* Average new into old with aging factor time */
#define ave(smooth, cnt, time) \
	smooth = ((time - 1) * (smooth) + (cnt)) / (time)

#endif	_SYS_VMMAC_H_
