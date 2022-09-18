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
 * $Log:	exception.h,v $
 * Revision 2.2  93/11/17  19:07:14  dbg
 * 	64-bit cleanup.  Subcode must be integer_t, since it holds an
 * 	address for EXC_BAD_ADDRESS.  I made exception and code be
 * 	natural_t for consistency.
 * 	[93/11/09            dbg]
 * 
 * 	Created.
 * 	[93/11/03            dbg]
 * 
 */

/*
 *	Routines exported by the exception handling package.
 */
#ifndef	_KERN_EXCEPTION_H_
#define	_KERN_EXCEPTION_H_

#include <mach/machine/vm_types.h>	/* integer_t */
#include <ipc/ipc_types.h>		/* ipc_port_t, ipc_kmsg_t */
#include <kern/kern_types.h>		/* no_return */

extern no_return
exception(
	integer_t	_exception,
	integer_t	code,
	integer_t	subcode);

extern no_return
exception_raise_continue(void);

extern no_return
exception_raise_continue_fast(
	ipc_port_t	reply_port,
	ipc_kmsg_t	kmsg);
	
#endif	/* _KERN_EXCEPTION_H_ */
