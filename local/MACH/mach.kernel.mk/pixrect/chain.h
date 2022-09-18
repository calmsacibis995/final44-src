/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	chain.h,v $
 * Revision 2.4  89/03/09  20:55:55  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:11:10  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/* @(#)chain.h 1.3 87/01/08 SMI */

#ifndef	CHAIN_H_
#define CHAIN_H_

/*
 * Copyright 1986 by Sun Microsystems,  Inc.
 */
struct pr_curve {
	char	x, y;
	short	bits;
};

#endif	CHAIN_H_
