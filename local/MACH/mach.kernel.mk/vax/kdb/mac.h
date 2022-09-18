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
 * $Log:	mac.h,v $
 * Revision 2.2  89/02/25  20:22:32  gm0w
 * 	Changes for cleanup.
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
