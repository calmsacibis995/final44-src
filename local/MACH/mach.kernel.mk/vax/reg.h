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
 * $Log:	reg.h,v $
 * Revision 2.3  89/03/09  22:20:58  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:28:01  gm0w
 * 	Changes for cleanup.
 * 
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)reg.h	7.1 (Berkeley) 6/5/86
 */

/*
 * Location of the users' stored
 * registers relative to R0.
 * Usage is u.u_ar0[XX].
 */
#define R0	(-18)
#define R1	(-17)
#define R2	(-16)
#define R3	(-15)
#define R4	(-14)
#define R5	(-13)
#define R6	(-12)
#define R7	(-11)
#define R8	(-10)
#define R9	(-9)
#define R10	(-8)
#define R11	(-7)
#define R12	(-21)
#define R13	(-20)

#define AP	(-21)
#define FP	(-20)
#define SP	(-5)
#define PS	(-1)
#define PC	(-2)
