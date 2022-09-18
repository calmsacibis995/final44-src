/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon 
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	kern_kmsg.h,v $
 * Revision 2.2  93/11/17  17:13:18  dbg
 * 	Created.
 * 	[93/03/29            dbg]
 * 
 */

/*
 *	File:	kern/kern_kmsg.h
 *	Author:	David Golub, 1993
 *
 *	Routines for allocating and freeing reply messages from
 *	the kernel IPC interface.
 */

#ifndef	_KERN_KERN_KMSG_H_
#define	_KERN_KERN_KMSG_H_

#include <ipc/ipc_kmsg.h>
#include <kern/macro_help.h>
#include <kern/zalloc.h>

/*
 *	Kernel reply kmsg allocation.
 */

extern zone_t	kernel_reply_kmsg_zone;

extern void	kernel_reply_kmsg_init(void);

#define	kernel_reply_kmsg_get(kmsg) \
MACRO_BEGIN \
	(kmsg) = ((ipc_kmsg_t) zalloc(kernel_reply_kmsg_zone)); \
	if ((kmsg) != IKM_NULL) \
	    ikm_init_special((kmsg), IKM_SIZE_KERN_REPLY); \
MACRO_END

#define	kernel_reply_kmsg_put(kmsg) \
MACRO_BEGIN \
	ikm_check_initialized((kmsg), IKM_SIZE_KERN_REPLY); \
	zfree(kernel_reply_kmsg_zone, (vm_offset_t)(kmsg)); \
MACRO_END

#endif	/* _KERN_KERN_KMSG_H_ */
