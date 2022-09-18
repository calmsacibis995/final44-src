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
 * Revision 2.11  90/07/03  16:58:00  mrt
 * 	Add vm_pageout_setup declaration.
 * 	[90/06/11            dlb]
 * 
 * Revision 2.10  89/10/10  13:48:48  mwyoung
 * 	Eliminate XP conditionals.
 * 	[89/10/10            mwyoung]
 * 
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

/*
 *	For VM_WAIT and definition of vm_page_t
 */
#include <vm/vm_page.h>

/*
 *	Exported routines.
 */

extern void		vm_pageout_page();
extern vm_page_t	vm_pageout_setup();

#endif	_VM_VM_PAGEOUT_H_
