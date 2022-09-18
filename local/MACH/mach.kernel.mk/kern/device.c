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
 * $Log:	device.c,v $
 * Revision 2.17  89/12/22  16:27:23  rpd
 * 	Updated to new SERVER_LOOP interface.
 * 	[89/11/24  23:05:18  rpd]
 * 
 * Revision 2.16  89/10/11  14:03:06  dlb
 * 	New calling sequence for vm_map_pageable.
 * 	[89/01/25            dlb]
 * 
 * Revision 2.15  89/10/10  10:50:22  mwyoung
 * 	Use vm_map_copyin().
 * 	[89/06/08  18:19:14  mwyoung]
 * 
 * Revision 2.14  89/05/01  15:23:32  rpd
 * 	Don't initialize task->reply_port here.
 * 	[89/05/01  13:47:12  rpd]
 * 
 * Revision 2.13  89/03/10  01:29:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.12  89/03/05  16:44:58  rpd
 * 	Made block_write_async always return something.
 * 	[89/02/16  13:41:47  rpd]
 * 
 * Revision 2.11  89/02/25  18:00:46  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.10  89/01/15  16:21:05  rpd
 * 	Updated includes for the new mach/ directory.
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  14:55:27  rpd]
 * 
 * Revision 2.9  89/01/12  07:51:09  rpd
 * 	Needs to include <kern/device_types.h> now.
 * 	[89/01/12  04:40:31  rpd]
 * 
 * Revision 2.8  89/01/10  23:26:09  rpd
 * 	Removed MACH_DEVICE conditionals.  Removed use of obsolete "xxx_port"
 * 	functions.
 * 	[89/01/10  13:20:10  rpd]
 * 
 * Revision 2.7  88/12/22  11:53:57  mja
 * 	Correct block_write() parameter order.
 * 	[88/12/21            mrt]
 * 
 * Revision 2.6  88/12/21  14:21:11  mja
 * 	Restore 2.3 vm_move change. 
 * 
 * Revision 2.5  88/12/19  02:42:57  mwyoung
 * 	Fix include file references.
 * 	[88/12/19  00:27:24  mwyoung]
 * 	
 * 	Use task_name() to identify our task.
 * 	[88/12/13            mwyoung]
 * 	
 * 	Remove more lint.
 * 	[88/12/09            mwyoung]
 * 	
 * 	Remove lint.
 * 	[88/12/08            mwyoung]
 * 
 * Revision 2.4  88/11/21  16:56:16  rvb
 * 	Fix it file so it compiles, anyone's guess if it works.
 * 	[88/11/21            rvb]
 * 
 * Revision 2.3  88/10/01  21:52:44  rpd
 * 	Updated vm_move calls.
 * 	[88/09/28  17:04:36  rpd]
 * 
 * Revision 2.2  88/07/20  16:29:05  rpd
 * Use old forms of port_allocate and port_enable.
 * 
 * 10-Feb-88  Douglas Orr (dorr) at Carnegie-Mellon University
 *	Created.
 */
/*
 * File:	device.c
 * Purpose:
 *	Kernel device i/o interface
 */

#include <mach/kern_return.h>
#include <mach/mach_types.h>
#include <mach/device_types.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <kern/lock.h>
#include <kern/task.h>
#include <mach/port.h>
#include <kern/kern_port.h>

#define DEV_IO_BAD_DEVICE -2
#define DEV_IO_ERROR	  -3
#include <mach/error.h>

#include <vm/vm_kern.h>
#include <vm/vm_map.h>
#include <mach/vm_prot.h>

extern vm_map_t ipc_soft_map;
extern vm_map_t kernel_map;
#define kern_device_io_map	kernel_map	/* XXX allocate submap */
#ifndef	private
#define private static
#endif	private

/*
 *	state variables
 */

private task_t		device_task;
private kern_port_t	device_server_port;
private port_set_name_t	device_enabled_set;
decl_simple_lock_data(private,dev_lock)

#ifdef	block_write
typedef struct dev_q {
	queue_chain_t	qc;
	struct buf q_bp;
} * dev_q_t;

private dev_q_t	dev_block_q;

zone_t	dev_io_zone;
#endif	/* block_write */

#ifdef	block_write
int block_write_done( bp )
struct buf * bp;
{
	thread_wakeup( &dev_block_q );
}
#endif	/* block_write */

kern_return_t block_write( port, device, block_number, block_size, block )
	port_t		port;
	dev_t		device;
	int		block_number;
	int		block_size;
	io_buf_t	block;
{
#ifdef	lint
	port++; device++; block_number++; block++; block_size++;
#endif	lint
	return( KERN_SUCCESS );
}


kern_return_t block_write_async( port, device, block_number, block_size, block )
	port_t		port;
	dev_t		device;
	int		block_number;
	int		block_size;
	io_buf_t	block;
{
#ifdef	block_write
	struct buf 		* bp;
	kern_return_t		result;
	static struct buf	bufinit = {
		B_WRITE|B_BUSY,
	};
#endif	block_write

#ifdef	lint
	port++; device++; block_number++; block++; block_size++;
#endif	lint

#ifdef	block_write

	buf = bufinit;

	if( major(device) > nblkdev )
		return( DEV_IO_BAD_DEVICE );

	/*
	 *  wire down our copy of user space buffer
	 */
	if( vm_map_pageable(kern_device_io_map, block, block+block_size,
	    VM_PROT_READ|VM_PROT_WRITE) != KERN_SUCCESS)
		panic("block_read: can't wire buffer\n");

	/* drag a new buf header out of the buffer queue */
	q = zalloc( dev_io_zone );
	q->bp = bufinit;

	/* save the old block in a queue to be reused */
	simple_lock( &dev_lock );
	queue_enter(&dev_block_q, q, dev_q_t, links);

	bp = &(q->q_bp);
	bp->b_flags = B_WRITE;

	bp->b_bcount = bp->b_bufsize = block_size;
	bp->b_dev = device;
	bp->b_blkno = block_number;
	(*bdevsw[major(device)].d_strategy)(bp);


	if ( bp->b_error != 0 ) {
		result = unix_err(bp->b_error);
		thread_wakeup( &dev_block_q );	/* wake up the buf reaper */
	} else
		result = KERN_SUCCESS;

	simple_unlock( &dev_lock );

	return( result );
#else	block_write
	return( KERN_SUCCESS );
#endif	block_write
}


kern_return_t block_read( port, device, block_number, block_size, block, blockCnt )
	port_t		port;
	dev_t		device;
	daddr_t		block_number;
	int		block_size;
	io_buf_ptr_t	block;
	int		* blockCnt;
{
	struct buf		local_buf;

	caddr_t			addr;
	vm_address_t		_addr;
	kern_return_t		err;
	static struct buf	bufinit = {
		B_READ|B_BUSY,
	};

#ifdef	lint
	port++; device++; block_number++; block++; block_size++; blockCnt++;
#endif	lint

	if( major(device) > nblkdev )
		return( DEV_IO_BAD_DEVICE );

	local_buf = bufinit;

	/*
	 *  allocate and wire down a buffer
	 */
	if ( (err = vm_allocate(
			kern_device_io_map,
			&_addr,
			(vm_size_t) block_size,
			TRUE))
	    != KERN_SUCCESS) {
		printf("block_read: cannot allocate a buffer!");
		return( err );
	}
	addr = (caddr_t) _addr;

	if( (err = vm_map_pageable(kern_device_io_map, _addr,
	    _addr+block_size, VM_PROT_READ|VM_PROT_WRITE)) != KERN_SUCCESS) {
		printf("block_read: can't wire buffer\n");
		return( err );
	}

		
	local_buf.b_un.b_addr = addr;

	local_buf.b_bcount = local_buf.b_bufsize = block_size;
	local_buf.b_dev = device;
	local_buf.b_blkno = block_number;
	(*bdevsw[major(device)].d_strategy)(&local_buf);
	if( local_buf.b_error != 0 )
		return( unix_err(local_buf.b_error) );

	biowait(&local_buf);

	if ( local_buf.b_error != 0 )
		return( unix_err(local_buf.b_error) );

	*blockCnt = local_buf.b_bcount - local_buf.b_resid;

	/* 
	 * move it into the ipc soft map so it will get magically moved
	 * back into the user's map on exit from the message.
	 *
	 * XXX this is entirely temporary
	 */
	(void) vm_map_copyin(
			kern_device_io_map,
			_addr,
			(vm_size_t) *blockCnt,
			TRUE,
			(vm_map_copy_t *) block);

	return( KERN_SUCCESS );
}


kern_return_t block_read_ahead( port, device, block_number, 
			       block_size, ra_block_number, ra_block_size,
			       block )
	port_t		port;
	dev_t		device;
	daddr_t		block_number;
	io_buf_ptr_t	block;
	int		block_size;
	daddr_t		ra_block_number;
	daddr_t		ra_block_size;
{
	struct buf		local_buf;
	struct buf *		rabp;
	caddr_t			addr;
	vm_address_t		_addr;
	static struct buf	bufinit = {
		B_READ|B_BUSY,
	};

#ifdef	lint
	port++;
#endif	lint

	local_buf = bufinit;

	/*
	 *  allocate and wire some data in user space
	 */

#ifdef	block_write
	/* keep a cache of blocks allocated by block_write */
#endif	/* block_write */

	if (vm_allocate(
		kern_device_io_map,
		&_addr,
		(vm_size_t) block_size,
		TRUE)
	    != KERN_SUCCESS)
		panic("block_read_ahead: cannot allocate a buffer!");
	if( vm_map_pageable(kern_device_io_map, _addr, _addr+block_size,
	    VM_PROT_READ|VM_PROT_WRITE) != KERN_SUCCESS)
		panic("block_read_ahead: can't wire buffer\n");
	addr = (caddr_t) _addr;

	*block = addr;
	local_buf.b_un.b_addr = (io_buf_t)addr;
	local_buf.b_bcount = local_buf.b_bufsize = block_size;
	local_buf.b_dev = device;
	local_buf.b_blkno = block_number;
	(*bdevsw[major(device)].d_strategy)(&local_buf);
	if( local_buf.b_error != 0 )
		return( DEV_IO_ERROR );

	/*
	 * If there's a read-ahead block, start i/o
	 * on it also (as above).
	 */
	if (ra_block_number && !incore(device, ra_block_number)) {
		rabp = getblk(device, ra_block_number, ra_block_size);
		if (rabp->b_flags & B_DONE) {
			brelse(rabp);
		} else {
			rabp->b_flags |= B_READ|B_ASYNC;
			if (rabp->b_bcount > rabp->b_bufsize)
				panic("breadrabp");
			(*bdevsw[major(device)].d_strategy)(rabp);
		}
	}
	
	biowait(&local_buf);
	if( local_buf.b_error != 0 )
		return( DEV_IO_ERROR );

	return( KERN_SUCCESS );

}

#ifdef	block_write
private 
void buf_reaper()
{
	dev_q_t q;

	/*
	 *  a separate thread runs through here and deallocates buffers and frees
	 *  the buf structure associated with buffers used for writes
	 */
	while (1) {

		simple_lock( &dev_lock );
		thread_sleep( &dev_io_q, simple_lock_addr(dev_lock), FALSE );

		simple_lock( &dev_lock );
		if ( ! queue_empty(dev_io_q) ) {
			q = queue_first(dev_io_q);
			do
				if ( q->q_bp->b_flags & (B_DONE|B_ERROR) ) {
					vm_deallocate( kern_dev_io_map, q->bp->b_un.addr, q->bp->b_bufsize );
					queue_remove( q, q, dev_io_q_t, qc );
					zfree( q );
				}
				q = queue_next(q);
			while( ! queue_end(q, dev_io_q) );
		}
		simple_unlock( &dev_lock );
	}
}
#endif	/* block_write */

/*
 *	task_get_io_port:  give the device port to user space (no
 *	restrictions as yet)
 */
task_get_io_port( task, port )
	task_t		task;
	kern_port_t	* port;
{
#ifdef	lint
	task++;
#endif	lint

	if (!suser()) {
		return(KERN_FAILURE);
	}
	port_reference( device_server_port );
	*port = device_server_port;
	return( KERN_SUCCESS );
}


void		device_init(task)
	task_t		task;
{
	port_name_t port;

	device_task = task;

	if (port_allocate(device_task, &port) != KERN_SUCCESS)
		panic("device_init: device server port allocate");

	if (port_set_allocate(device_task, &device_enabled_set) != KERN_SUCCESS)
		panic("device_init: device enabled set allocate");

	if (port_set_add(device_task, device_enabled_set, port) != KERN_SUCCESS)
		panic("device_init: device server port enable");

	(void) object_copyin(device_task, port,
			     MSG_TYPE_PORT, FALSE,
			     (kern_obj_t *) &device_server_port);

	simple_lock_init(&dev_lock);
#ifdef	block_write
	dev_io_zone = zinit( sizeof(dev_q_t), DEV_IO_ZMAX, DEV_IO_ZMAX, FALSE, "dev_io zone" );

	/*
	 * start up the task that will reclaim bufs allocated when writing
	 */
	(void)kernel_thread( task, buf_reaper );
#endif	block_write
		      
}

/*
 *  mach_user_internal.h is needed to redefine server_loop's idea of
 *  how functions should behave for use inside the kernel
 */
#include <mach/mach_user_internal.h>

/*
 *	Deallocate the page structures allocated for a device
 */
void		device_terminate(port)
	port_t		port;
{
#ifdef	lint
	port++;
#endif	lint
	printf( "device_terminate!\n" );
}


/*
 *  include some canned code to perform our server function
 */

#define SERVER_LOOP		device_server_loop
#define SERVER_NAME		"device_server"
#define SERVER_DISPATCH(in,out)	device_server(in,out)
#define TERMINATE_FUNCTION	device_terminate

#include <kern/server_loop.c>

void device_loop()
{
	extern void task_name();

	task_name("device server");
	SERVER_LOOP(device_enabled_set, TRUE);
}
