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
 * $Log:	vm_pageout.h,v $
 * Revision 2.9  89/04/18  21:28:02  mwyoung
 * 	No relevant history.
 * 
 */
/*
 *	File:	vm/vm_pageout.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	Copyright (C) 1986, Avadis Tevanian, Jr.
 *
 *	Declarations for the pageout daemon interface.
 */

#ifndef	_VM_VM_PAGEOUT_H_
#define _VM_VM_PAGEOUT_H_

#include <mach_xp.h>

#if	!MACH_XP
#include <kern/lock.h>
#include <kern/sched_prim.h>

/*
 *	Exported data structures.
 */

extern int	vm_pages_needed;	/* should be some "event" structure */
decl_simple_lock_data(extern,vm_pages_needed_lock)


#endif	!MACH_XP
/*
 *	Exported routines.
 */

#if	MACH_XP
extern void	vm_pageout_page();
#else	MACH_XP
#define vm_pageout_page(p, bool)	panic("vm_pageout_page")
#endif	MACH_XP

#if	MACH_XP
/* Get VM_WAIT macro from <vm/vm_page.h>, for compatibility */
#include <vm/vm_page.h>
#else	MACH_XP
#include <kern/macro_help.h>
/*
 *	Signal pageout-daemon and wait for it.
 */

#define VM_WAIT							\
MACRO_BEGIN							\
	simple_lock(&vm_pages_needed_lock);			\
	thread_wakeup((int)&vm_pages_needed);			\
	thread_sleep((int)&vm_page_free_count,			\
		     simple_lock_addr(vm_pages_needed_lock),	\
		     FALSE);					\
MACRO_END

#endif	MACH_XP

#endif	_VM_VM_PAGEOUT_H_
