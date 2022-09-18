/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pcs.h,v $
 * Revision 2.5  89/04/05  18:16:39  rvb
 * 	Changes for J in debugger by rfr.
 * 	[89/04/05            rvb]
 * 
 * Revision 2.4  89/03/09  21:35:05  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:42:05  gm0w
 * 	 8-Sep-86 David Golub (dbg) at Carnegie-Mellon University
 * 
 *	Converted for SUN.
 *
 *  6-Jan-86 David Golub (dbg) at Carnegie-Mellon University
 *	declarations for new single-step features
 *
 */

int	sstepmode;
int	call_depth;
int	icount;

#define STEP_NONE	0
#define STEP_NORM	1
#define STEP_PRINT	2
#define STEP_CALLT	3
#define STEP_RETURN	4

#define I_RTS		0x4E75
#define M_JSR		0xffc0
#define I_JSR		0x4e80
#define M_BSR		0xff00
#define I_BSR		0x6100
#define I_BPT		0x4e4f
