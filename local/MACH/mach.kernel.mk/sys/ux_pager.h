/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ux_pager.h,v $
 * Revision 2.2  90/09/07  19:02:53  mrt
 * 	Moved declaration of mach_swapon, inode_swap_preference and
 * 	flags from builtin/inode_pager.h to here where it can be
 * 	exported to the user.
 * 	[90/09/07            mrt]
 * 
 */

#ifndef	_SYS_UX_PAGER_H_
#define _SYS_UX_PAGER_H_

#include <mach/kern_return.h>

extern kern_return_t inode_swap_preference();

extern kern_return_t mach_swapon();

#define MS_NONE		0x0000
#define MS_PREFER	0x0001		/* Prefer this file. */

#endif	_SYS_UX_PAGER_H_
