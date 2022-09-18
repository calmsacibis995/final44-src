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
 * $Log:	mac.h,v $
 * Revision 1.4.1.1  90/01/08  13:27:33  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4  89/03/09  20:01:10  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:33:26  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 *  1-Jan-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Undefine TRUE/FALSE under KERNEL compilation.
 *
 */

/*	mac.h	4.1	81/05/14	*/

/*
 *	UNIX debugger
 */

#undef	TRUE
#undef	FALSE
#define TRUE	 (-1)
#define FALSE	0

#define EOF	0
