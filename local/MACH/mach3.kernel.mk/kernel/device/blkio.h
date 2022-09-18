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
 * $Log:	blkio.h,v $
 * Revision 2.2  94/12/15  15:17:22  dbg
 * 	Created.
 * 	[94/03/28            dbg]
 * 
 */

/*
 *	Declarations of block (disk) IO routines.
 */
#ifndef	_DEVICE_BLKIO_H_
#define	_DEVICE_BLKIO_H_

#include <device/device_types.h>
#include <device/io_req.h>

extern io_return_t	block_io(
		void		(*strat)(io_req_t),
		void		(*max_count)(io_req_t),
		io_req_t	ior);

extern void		minphys(
		io_req_t);

extern vm_offset_t	block_io_mmap();

extern void		disksort(
		io_req_t	head,
		io_req_t	ior);

extern io_req_t		geteblk(
		vm_size_t	size);

extern void		brelse(
		io_req_t	ior);

extern void		harderr(
		io_req_t	ior,
		const char *	name);

extern void		disk_read_page(
		void		*object,
		vm_offset_t	offset,
		vm_size_t	size,
		vm_prot_t	prot,
		ipc_port_t	reply);	/* read page from object */

extern void		disk_unlock_page(
		void		*object,
		vm_offset_t	offset,
		vm_size_t	size,
		vm_prot_t	prot,
		ipc_port_t	reply);	/* unlock existing page */

extern void		disk_write_page(
		void		*object,
		vm_offset_t	offset,
		pointer_t	data,
		vm_size_t	size,
		ipc_port_t	reply);	/* write page */

#endif	/* _DEVICE_BLKIO_H_ */

