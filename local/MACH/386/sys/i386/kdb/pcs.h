/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pcs.h,v $
 * Revision 1.4.1.1  90/05/14  13:18:49  rvb
 * 	Bring kdb up to Mach 2.5 production quality:
 * 		i386 opcodes
 * 	[90/05/10            rvb]
 * 
 * Revision 1.4  89/03/09  20:01:54  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:35:16  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
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

#define I_CALL 0xe8
#define I_RET 0xc3
 /*??*/
#define I_REI 0xcf
