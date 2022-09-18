/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	seg.h,v $
 * Revision 2.2  89/07/12  00:11:49  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)seg.h 2.6 88/02/08 SMI; from UCB 4.2 81/02/19	*/

/*
 * Mapper addresses and bits
 */

#define	RO	PG_URKR		/* access abilities */
#define	RW	PG_UW
