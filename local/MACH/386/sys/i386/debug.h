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
 * $Log:	debug.h,v $
 * Revision 2.1.1.1  89/10/22  11:30:02  rvb
 * 	Revision 1.1  89/08/07  17:16:07  kupfer
 * 	Definitions for the i386 debug registers.
 * 	Initial revision
 * 
 * 
 */

/*
 * Debug status register (dr6) definitions
 */

#define DBG_BD	0x2000		/* Debug trap, conflict with ICE-386 */
#define DBG_BS	0x4000		/* Single step trap occurred */
#define DBG_BT	0x8000		/* TSS trace trap occurred */

