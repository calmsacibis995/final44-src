/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	device_pager.h,v $
 * Revision 2.5  89/03/09  19:34:44  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  15:00:52  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/07  01:00:59  mwyoung
 * Relocated from vm/device_pager.h
 * 
 *  8-Dec-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	builtin/device_pager.h
 *
 *	Exported things from the device pager.
 */

#ifndef	_BUILTIN_DEVICE_PAGER_H_
#define _BUILTIN_DEVICE_PAGER_H_

#ifdef	KERNEL
#include <mach/memory_object.h>

extern void		device_pager_init();
extern void		device_pager();
extern memory_object_t	device_pager_create();
#endif	KERNEL
#endif	_BUILTIN_DEVICE_PAGER_H_
