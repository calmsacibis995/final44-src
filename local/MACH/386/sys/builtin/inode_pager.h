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
 * $Log:	inode_pager.h,v $
 * Revision 2.8  89/03/09  19:34:55  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/25  15:00:57  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/07  01:00:49  mwyoung
 * Relocated from vm/inode_pager.h
 * 
 * Revision 2.5  89/01/15  16:40:17  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:28:44  rpd]
 * 
 * Revision 2.4  88/10/18  03:42:57  mwyoung
 * 	Added inode_uncache_try(), so that all caching knowledge is
 * 	buried in the inode_pager itself.
 * 	[88/09/18            mwyoung]
 * 
 * Revision 2.3  88/08/25  18:25:30  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Add declaration for inode_pager_release().
 * 	[88/08/11  18:52:57  mwyoung]
 * 
 *  6-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed inode_pager_t structure declaration from this file...
 *	it should not be exported from the inode_pager implementation.
 *
 */

#ifndef	_BUILTIN_INODE_PAGER_H_
#define _BUILTIN_INODE_PAGER_H_

#include <mach/kern_return.h>

extern kern_return_t	inode_swap_preference();

#ifdef	KERNEL
#include <mach_xp.h>

#include <mach/boolean.h>
#include <mach/memory_object.h>

extern void		inode_pager_bootstrap();

extern memory_object_t	inode_pager_setup();
extern void		inode_pager_release();
extern boolean_t	inode_pager_active();
extern void		inode_uncache();
extern boolean_t	inode_uncache_try();

#if	MACH_XP
#include <kern/lock.h>

decl_simple_lock_data(extern,inode_pager_init_lock)

extern void		inode_pager();
#else	MACH_XP
extern boolean_t	inode_pagein();
extern boolean_t	inode_pageout();
extern boolean_t	inode_dealloc();
extern memory_object_t	inode_alloc();
extern boolean_t	inode_has_page();
#endif	MACH_XP

#endif	KERNEL
#endif	_BUILTIN_INODE_PAGER_H_
