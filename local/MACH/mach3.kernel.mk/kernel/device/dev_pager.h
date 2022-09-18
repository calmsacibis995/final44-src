/* 
 * Mach Operating System
 * Copyright (c) 1994 Carnegie Mellon University
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
 * $Log:	dev_pager.h,v $
 * Revision 2.2  94/12/15  15:19:03  dbg
 * 	Created.
 * 	[94/05/26            dbg]
 * 
 */

/*
 *	Generalized device pager.
 *	Handles internal memory-mapped objects as well as
 *	devices.
 */
#ifndef	_DEVICE_DEV_PAGER_H_
#define	_DEVICE_DEV_PAGER_H_

#include <mach/std_types.h>
#include <mach/memory_object.h>

/*
 *	Operations vector for pager.
 */
struct dev_pager_ops {
	void			(*reference)(
		void	*object);	/* reference object */
	void			(*deallocate)(
		void	*object);	/* deallocate object */
	vm_offset_t		(*page_map)(
		void	    *object,
		vm_offset_t offset,
		vm_prot_t   prot);	/* get physical page at offset
					   into object */
	void			(*read_page)(
		void	    *object,
		vm_offset_t offset,
		vm_size_t   size,
		vm_prot_t   prot,
		ipc_port_t  reply);	/* read page from object */

	void			(*unlock_page)(
		void	    *object,
		vm_offset_t offset,
		vm_size_t   size,
		vm_prot_t   prot,
		ipc_port_t  reply);	/* unlock existing page */

	void			(*write_page)(
		void	    *object,
		vm_offset_t offset,
		pointer_t   data,
		vm_size_t   size,
		ipc_port_t  reply);	/* write page */
};

/*
 *	Exported routines.
 */
extern void	     device_pager_init(void);

extern kern_return_t device_pager_setup(
	void		*object,
	struct dev_pager_ops ops,
	vm_prot_t	prot,
	vm_offset_t	offset,
	vm_size_t	size,
	ipc_port_t	*pager);

#endif	/* _DEVICE_DEV_PAGER_H_ */
