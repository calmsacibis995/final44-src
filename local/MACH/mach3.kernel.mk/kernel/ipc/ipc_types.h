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
 * $Log:	ipc_types.h,v $
 * Revision 2.2  93/11/17  17:03:27  dbg
 * 	Renamed to ipc/ipc_types.h.  Included union for
 * 	message return type for ipc_mqueue_receive.
 * 	[93/03/15            dbg]
 * 
 * Revision 2.2  93/01/27  09:31:56  danner
 * 	Created to break latent circularity between
 *	ipc_kmsg_queue.h and kern/thread.h.
 * 	[93/01/27            danner]
 * 
 */
/*
 *	File:	ipc/ipc_types.h
 *	Author:	Dan Stodolsky and David Golub
 *	Date:	1993
 *
 *	Definitions for commonly used IPC structures
 *	included in or referenced by other kernel data
 *	structures.  Many of these are handles to opaque
 *	data structures defined elsewhere.  Others are
 *	defined here to break circular chains of include
 *	files.
 */

#ifndef _IPC_IPC_TYPES_H_
#define _IPC_IPC_TYPES_H_

#include <mach/message.h>	/* mach_msg_size_t */

/*
 *	A kernel IPC message structure, from ipc/ipc_kmsg.h.
 */
typedef	struct ipc_kmsg *	ipc_kmsg_t;
#define	IKM_NULL		((ipc_kmsg_t) 0)

/*
 *	Queue of ipc_kmsgs.
 */
struct ipc_kmsg_queue {
	struct ipc_kmsg *ikmq_base;
};
typedef	struct ipc_kmsg_queue	*ipc_kmsg_queue_t;

#define	IKMQ_NULL		((ipc_kmsg_queue_t) 0)

/*
 *	Return value for receiving an ipc_kmsg.
 *	May be a pointer to an ipc_kmsg, or
 *	the size of a too-large message.
 */
union ipc_kmsg_return {
	struct ipc_kmsg	*kmsg;		/* received message */
	mach_msg_size_t	msize;		/* max size for received message */
};

/*
 *	From ipc/ipc_space.h:
 */
typedef	struct ipc_space *	ipc_space_t;
#define	IS_NULL			((ipc_space_t) 0)

/*
 *	From ipc/ipc_port.h:
 */

typedef	struct ipc_port	*	ipc_port_t;

#endif	/* _IPC_IPC_TYPES_H_ */
