/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vcmd.h,v $
 * Revision 2.5  90/08/30  11:51:08  bohman
 * 	Ioctl changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.4  89/03/09  22:10:14  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  17:58:20  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/24  02:52:39  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:27:43  mwyoung]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)vcmd.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_VCMD_H_
#define _SYS_VCMD_H_

#include <sys/ioctl.h>

#define VPRINT		0100
#define VPLOT		0200
#define VPRINTPLOT	0400

#ifdef	__STDC__
#define VGETSTATE	_IOR('v', 0, int)
#define VSETSTATE	_IOW('v', 1, int)
#else
#define VGETSTATE	_IOR(v, 0, int)
#define VSETSTATE	_IOW(v, 1, int)
#endif

#endif	_SYS_VCMD_H_
