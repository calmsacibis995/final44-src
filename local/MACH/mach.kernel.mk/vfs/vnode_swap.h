/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vnode_swap.h,v $
 * Revision 2.4  89/03/09  22:45:30  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:14:00  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:27:48  jsb
 * 	Include file references.
 * 	[89/01/17  17:36:18  jsb]
 * 
 *
 *  5-Jul-88  Rick Rashid (rfr) at Carnegie-Mellon University
 *	Built to define VS_PREFER and VS_NEVER.  These values are a
 *	guess right now.
 *
 */
#ifndef	_VNODE_SWAP_
#define _VNODE_SWAP_	1

#define VS_PREFER	1
#define VS_NEVER	2

#endif	_VNODE_SWAP_
