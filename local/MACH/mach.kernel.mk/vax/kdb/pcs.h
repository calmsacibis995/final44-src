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
 * $Log:	pcs.h,v $
 * Revision 2.3  89/03/09  22:17:58  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:23:27  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Dec-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added "single step until matching return" form of ":j".
 *
 * 6-jan-86	David Golub (dbg)
 *	declarations for new single-step features
 *
 */

int	sstepmode;
int	icount;
int	call_depth;

#define STEP_NONE	0
#define STEP_NORM	1
#define STEP_PRINT	2
#define STEP_CALLT	3
#define STEP_RETURN	4

#define I_CALLG		0xfa
#define I_CALLS		0xfb
#define I_RET		0x04
#define I_REI		0x02
