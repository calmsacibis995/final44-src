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
 * $Log:	cmap.h,v $
 * Revision 2.5  89/03/09  22:02:48  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  17:52:23  gm0w
 * 	Got rid of conditional on CMU and MACH and the code that
 * 	was defined for non-MACH case
 * 	[89/02/13            mrt]
 * 
 * Revision 2.3  89/01/30  22:08:06  rpd
 * 	Made variable declarations use "extern".
 * 	[89/01/25  15:20:04  rpd]
 * 
 * Revision 2.2  88/08/24  02:24:02  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:10:21  mwyoung]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)cmap.h	7.1 (Berkeley) 6/4/86
 */

/*
 * This file used to define the BSD4.4 core map entry
 * which is not used by Mach.
 *
 */

#ifndef	_SYS_CMAP_H_
#define _SYS_CMAP_H_

#if	defined(KERNEL) && !defined(LOCORE)
extern int	maxfree;
#endif	defined(KERNEL) && !defined(LOCORE)

#endif	_SYS_CMAP_H_
