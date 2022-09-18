/* 
 * Mach Operating System
 * Copyright (c) 1993-1989 Carnegie Mellon University
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
 * $Log:	net_io.c,v $
 * Revision 2.28  93/05/15  18:53:22  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.27  93/05/10  23:23:27  rvb
 * 	Checkin for MK80 branch.
 * 	[93/05/10  15:16:19  grm]
 * 
 * Revision 2.25.1.1  93/03/01  15:19:48  grm
 * 	Added TTD teledebug code to check for debugging packets.
 * 	[93/03/01            grm]
 * 
 * Revision 2.26  93/05/10  17:46:12  rvb
 * 	Added test to check that buffer is large enough to hold data
 * 	returned by net_getstat.
 * 	[93/04/20            kivinen]
 * 
 * Revision 2.25  93/01/14  17:27:08  danner
 * 	64bit cleanup.
 * 	[92/11/30            af]
 * 
 * Revision 2.24  92/08/03  17:33:48  jfriedl
 * 	removed silly prototypes
 * 	[92/08/02            jfriedl]
 * 
 * Revision 2.23  92/05/21  17:09:38  jfriedl
 * 	Cleanup to quiet gcc warnings.
 * 	[92/05/16            jfriedl]
 * 
 * Revision 2.22  92/03/10  16:25:28  jsb
 * 	Changed parameters to netipc_net_packet.
 * 	[92/03/09  12:57:30  jsb]
 * 
 * Revision 2.21  92/01/03  20:03:57  dbg
 * 	Add: NETF_PUSHHDR, NETF_PUSHSTK, NETF_PUSHIND, NETF_PUSHHDRIND.
 * 	[91/12/23            dbg]
 * 
 * Revision 2.20  91/08/28  11:11:28  jsb
 * 	Panic if network write attempted with continuation.
 * 	[91/08/12  17:29:53  dlb]
 * 
 * Revision 2.19  91/08/24  11:55:55  af
 * 	Missing include for Spls definitions.
 * 	[91/08/02  02:45:16  af]
 * 
 * Revision 2.18  91/08/03  18:17:43  jsb
 * 	Added NORMA_ETHER support.
 * 	[91/07/24  22:54:41  jsb]
 * 
 * Revision 2.17  91/05/14  15:59:34  mrt
 * 	Correcting copyright
 * 
 * Revision 2.16  91/05/10  11:48:47  dbg
 * 	Don't forget to copy the packet size when duplicating a packet
 * 	for multiple filters in net_filter().
 * 	[91/05/09            dpj]
 * 
 * Revision 2.15  91/03/16  14:43:14  rpd
 * 	Added net_thread, net_thread_continue.
 * 	[91/02/13            rpd]
 * 	Split net_rcv_msg_queue into high and low priority queues.
 * 	Cap the total number of buffers allocated.
 * 	[91/01/14            rpd]
 * 
 * 	Added net_rcv_msg_queue_size, net_rcv_msg_queue_max.
 * 	[91/01/12            rpd]
 * 
 * Revision 2.14  91/02/14  14:37:07  mrt
 * 	Added garbage collection of dead filters.
 * 	[91/02/12  12:11:10  af]
 * 
 * Revision 2.13  91/02/05  17:09:54  mrt
 * 	Changed to new Mach copyright
 * 	[91/01/31  17:30:04  mrt]
 * 
 * Revision 2.12  91/01/08  15:09:48  rpd
 * 	Replaced NET_KMSG_GET, NET_KMSG_FREE
 * 	with net_kmsg_get, net_kmsg_put, net_kmsg_collect.
 * 	Increased net_kmsg_ilist_min to 4.
 * 	[91/01/05            rpd]
 * 	Fixed net_rcv_msg_thread to round message sizes up to an int multiple.
 * 	[90/12/07            rpd]
 * 
 * 	Fixed net_rcv_msg_thread to not set vm_privilege.
 * 	[90/11/29            rpd]
 * 
 * Revision 2.11  90/09/09  23:20:00  rpd
 * 	Zero the mapped_size stats for non mappable interfaces.
 * 	[90/08/30  17:41:00  af]
 * 
 * Revision 2.10  90/08/27  21:55:18  dbg
 * 	If multiple filters receive a packet, copy the header as well as
 * 	the body.  Fix from Dan Julin.
 * 	[90/08/27            dbg]
 * 
 * 	Fix filter check to account for literal word.
 * 	[90/07/17            dbg]
 * 
 * Revision 2.9  90/08/06  15:06:57  rwd
 * 	Fixed a bug in parse_net_filter(), that was reading the
 * 	litteral from NETF_PUSHLIT as an instruction.
 * 	[90/07/18  21:56:20  dpj]
 * 
 * Revision 2.8  90/06/02  14:48:14  rpd
 * 	Converted to new IPC.
 * 	[90/03/26  21:57:43  rpd]
 * 
 * Revision 2.7  90/02/22  20:02:21  dbg
 * 	Track changes to kmsg structure.
 * 	[90/01/31            dbg]
 * 
 * Revision 2.6  90/01/11  11:42:20  dbg
 * 	Make run in parallel.
 * 	[89/12/15            dbg]
 * 
 * Revision 2.5  89/12/08  19:52:22  rwd
 * 	Picked up changes from rfr to minimize wired down memory
 * 	[89/11/21            rwd]
 * 
 * Revision 2.4  89/09/08  11:24:35  dbg
 * 	Convert to run in kernel task.  Removed some lint.
 * 	[89/07/26            dbg]
 * 
 * Revision 2.3  89/08/11  17:55:18  rwd
 * 	Picked up change from rfr which made zone collectable and
 * 	decreased min net_kmesg to 2.
 * 	[89/08/10            rwd]
 * 
 * Revision 2.2  89/08/05  16:06:58  rwd
 * 	Changed device_map to device_task_map
 * 	[89/08/04            rwd]
 * 
 * 13-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.  
 *
 */
/*
 *	Author: David B. Golub, Carnegie Mellon University
 *	Date: 	3/98
 *
 *	Packet filter code taken from vaxif/enet.c written		 
 *		CMU and Stanford. 
 */

#include <norma_ether.h>
#include <mach_ttd.h>

#include <device/net_status.h>
#include <machine/machspl.h>		/* spl definitions */
#include <device/net_io.h>
#include <device/if_hdr.h>
#include <device/io_req.h>
#include <device/ds_routines.h>

#include <mach/boolean.h>
#include <mach/vm_param.h>

#include <ipc/ipc_port.h>
#include <ipc/ipc_kmsg.h>
#include <ipc/ipc_mqueue.h>

#include <kern/counters.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/sched_prim.h>
#include <kern/thread.h>

#if	NORMA_ETHER
#include <norma/ipc_ether.h>
#endif	/*NORMA_ETHER*/

#include <machine/machspl.h>

#if	MACH_TTD
#include <ttd/ttd_stub.h>
#endif	/* MACH_TTD */

#if	MACH_TTD
int kttd_async_counter= 0;
#endif	/* MACH_TTD */

/*
 * Network IO.
 */

/*
 * Each interface has a write port and a set of read ports.
 * Each read port has one or more filters to determine what packets
 * should go to that port.
 */

/*
 * Receive port for net, with packet filter.
 */
struct net_rcv_port {
	queue_chain_t	chain;		/* list of open_descriptors */
	ipc_port_t	rcv_port;	/* port to send packet to */
	int		rcv_qlimit;	/* port's qlimit */
	int		rcv_count;	/* number of packets received */
	int		priority;	/* priority for filter */
	filter_t	*filter_end;	/* pointer to end of filter */
	filter_t	filter[NET_MAX_FILTER];
					/* filter operations */
};
typedef struct net_rcv_port *net_rcv_port_t;

/*
 * List of net kmsgs queued to be sent to users.
 * Messages can be high priority or low priority.
 * The network thread processes high priority messages first.
 */
decl_simple_lock_data(,net_queue_lock)
boolean_t	net_thread_awake = FALSE;
struct ipc_kmsg_queue	net_queue_high;
int		net_queue_high_size = 0;
int		net_queue_high_max = 0;		/* for debugging */
struct ipc_kmsg_queue	net_queue_low;
int		net_queue_low_size = 0;
int		net_queue_low_max = 0;		/* for debugging */

/*
 * List of net kmsgs that can be touched at interrupt level.
 * If it is empty, we will also steal low priority messages.
 */
decl_simple_lock_data(,net_queue_free_lock)
struct ipc_kmsg_queue	net_queue_free;
int		net_queue_free_size = 0;	/* on free list */
int		net_queue_free_max = 0;		/* for debugging */

/*
 * This value is critical to network performance.
 * At least this many buffers should be sitting in net_queue_free.
 * If this is set too small, we will drop network packets.
 * Even a low drop rate (<1%) can cause severe network throughput problems.
 * We add one to net_queue_free_min for every filter.
 */
int		net_queue_free_min = 3;

int		net_queue_free_hits = 0;	/* for debugging */
int		net_queue_free_steals = 0;	/* for debugging */
int		net_queue_free_misses = 0;	/* for debugging */

int		net_kmsg_send_high_hits = 0;	/* for debugging */
int		net_kmsg_send_low_hits = 0;	/* for debugging */
int		net_kmsg_send_high_misses = 0;	/* for debugging */
int		net_kmsg_send_low_misses = 0;	/* for debugging */

int		net_thread_awaken = 0;		/* for debugging */
int		net_ast_taken = 0;		/* for debugging */

decl_simple_lock_data(,net_kmsg_total_lock)
int		net_kmsg_total = 0;		/* total allocated */
int		net_kmsg_max;			/* initialized below */

vm_size_t	net_kmsg_size;			/* initialized below */

zone_t		net_rcv_zone;

/*
 *	We want more buffers when there aren't enough in the free queue
 *	and the low priority queue.  However, we don't want to allocate
 *	more than net_kmsg_max.
 */

#define net_kmsg_want_more()		\
	(((net_queue_free_size + net_queue_low_size) < net_queue_free_min) && \
	 (net_kmsg_total < net_kmsg_max))

ipc_kmsg_t net_kmsg_get()
{
	register ipc_kmsg_t kmsg;
	spl_t s;

	/*
	 *	First check the list of free buffers.
	 */
	s = splimp();
	simple_lock(&net_queue_free_lock);
	kmsg = ipc_kmsg_queue_first(&net_queue_free);
	if (kmsg != IKM_NULL) {
	    ipc_kmsg_rmqueue_first_macro(&net_queue_free, kmsg);
	    net_queue_free_size--;
	    net_queue_free_hits++;
	}
	simple_unlock(&net_queue_free_lock);

	if (kmsg == IKM_NULL) {
	    /*
	     *	Try to steal from the low priority queue.
	     */
	    simple_lock(&net_queue_lock);
	    kmsg = ipc_kmsg_queue_first(&net_queue_low);
	    if (kmsg != IKM_NULL) {
		ipc_kmsg_rmqueue_first_macro(&net_queue_low, kmsg);
		net_queue_low_size--;
		net_queue_free_steals++;
	    }
	    simple_unlock(&net_queue_lock);
	}

	if (kmsg == IKM_NULL)
	    net_queue_free_misses++;
	(void) splx(s);

	if (net_kmsg_want_more() || (kmsg == IKM_NULL)) {
	    boolean_t awake;

	    s = splimp();
	    simple_lock(&net_queue_lock);
	    awake = net_thread_awake;
	    net_thread_awake = TRUE;
	    simple_unlock(&net_queue_lock);
	    (void) splx(s);

	    if (!awake)
		thread_wakeup((event_t) &net_thread_awake);
	}

	return kmsg;
}

void net_kmsg_put(kmsg)
	register ipc_kmsg_t kmsg;
{
	spl_t s;

	s = splimp();
	simple_lock(&net_queue_free_lock);
	ipc_kmsg_enqueue_macro(&net_queue_free, kmsg);
	if (++net_queue_free_size > net_queue_free_max)
	    net_queue_free_max = net_queue_free_size;
	simple_unlock(&net_queue_free_lock);
	(void) splx(s);
}

void net_kmsg_collect()
{
	register ipc_kmsg_t kmsg;
	spl_t s;

	s = splimp();
	simple_lock(&net_queue_free_lock);
	while (net_queue_free_size > net_queue_free_min) {
	    kmsg = ipc_kmsg_dequeue(&net_queue_free);
	    net_queue_free_size--;
	    simple_unlock(&net_queue_free_lock);
	    (void) splx(s);

	    net_kmsg_free(kmsg);
	    simple_lock(&net_kmsg_total_lock);
	    net_kmsg_total--;
	    simple_unlock(&net_kmsg_total_lock);

	    s = splimp();
	    simple_lock(&net_queue_free_lock);
	}
	simple_unlock(&net_queue_free_lock);
	(void) splx(s);
}

void net_kmsg_more()
{
	register ipc_kmsg_t kmsg;

	/*
	 * Replenish net kmsg pool if low.  We don't have the locks
	 * necessary to look at these variables, but that's OK because
	 * misread values aren't critical.  The danger in this code is
	 * that while we allocate buffers, interrupts are happening
	 * which take buffers out of the free list.  If we are not
	 * careful, we will sit in the loop and allocate a zillion
	 * buffers while a burst of packets arrives.  So we count
	 * buffers in the low priority queue as available, because
	 * net_kmsg_get will make use of them, and we cap the total
	 * number of buffers we are willing to allocate.
	 */

	while (net_kmsg_want_more()) {
	    simple_lock(&net_kmsg_total_lock);
	    net_kmsg_total++;
	    simple_unlock(&net_kmsg_total_lock);
	    kmsg = net_kmsg_alloc();
	    net_kmsg_put(kmsg);
	}
}

/*
 *	ethernet_priority:
 *
 *	This function properly belongs in the ethernet interfaces;
 *	it should not be called by this module.  (We get packet
 *	priorities as an argument to net_filter.)  It is here
 *	to avoid massive code duplication.
 *
 *	Returns TRUE for high-priority packets.
 */

boolean_t ethernet_priority(kmsg)
	ipc_kmsg_t kmsg;
{
	register unsigned char *addr =
		(unsigned char *) net_kmsg(kmsg)->header;

	/*
	 *	A simplistic check for broadcast packets.
	 */

	if ((addr[0] == 0xff) && (addr[1] == 0xff) &&
	    (addr[2] == 0xff) && (addr[3] == 0xff) &&
	    (addr[4] == 0xff) && (addr[5] == 0xff))
	    return FALSE;
	else
	    return TRUE;
}

mach_msg_type_t header_type = {
	MACH_MSG_TYPE_BYTE,
	8,
	NET_HDW_HDR_MAX,
	TRUE,
	FALSE,
	FALSE,
	0
};

mach_msg_type_t packet_type = {
	MACH_MSG_TYPE_BYTE,	/* name */
	8,			/* size */
	0,			/* number */
	TRUE,			/* inline */
	FALSE,			/* longform */
	FALSE			/* deallocate */
};

/*
 *	net_deliver:
 *
 *	Called and returns holding net_queue_lock, at splimp.
 *	Dequeues a message and delivers it at spl0.
 *	Returns FALSE if no messages.
 */
boolean_t net_deliver(nonblocking)
	boolean_t nonblocking;
{
	register ipc_kmsg_t kmsg;
	boolean_t high_priority;
	struct ipc_kmsg_queue send_list;

	/*
	 * Pick up a pending network message and deliver it.
	 * Deliver high priority messages before low priority.
	 */

	if ((kmsg = ipc_kmsg_dequeue(&net_queue_high)) != IKM_NULL) {
	    net_queue_high_size--;
	    high_priority = TRUE;
	} else if ((kmsg = ipc_kmsg_dequeue(&net_queue_low)) != IKM_NULL) {
	    net_queue_low_size--;
	    high_priority = FALSE;
	} else
	    return FALSE;
	simple_unlock(&net_queue_lock);
	(void) spl0();

	/*
	 * Run the packet through the filters,
	 * getting back a queue of packets to send.
	 */
	net_filter(kmsg, &send_list);

	if (!nonblocking) {
	    /*
	     * There is a danger of running out of available buffers
	     * because they all get moved into the high priority queue
	     * or a port queue.  In particular, we might need to
	     * allocate more buffers as we pull (previously available)
	     * buffers out of the low priority queue.  But we can only
	     * allocate if we are allowed to block.
	     */
	    net_kmsg_more();
	}

	while ((kmsg = ipc_kmsg_dequeue(&send_list)) != IKM_NULL) {
	    int count;

	    /*
	     * Fill in the rest of the kmsg.
	     */
	    count = net_kmsg(kmsg)->net_rcv_msg_packet_count;

	    ikm_init_special(kmsg, IKM_SIZE_NETWORK);

	    kmsg->ikm_header.msgh_bits =
		    MACH_MSGH_BITS(MACH_MSG_TYPE_PORT_SEND, 0);
	    /* remember message sizes must be rounded up */
	    kmsg->ikm_header.msgh_size =
		    ((mach_msg_size_t) (sizeof(struct net_rcv_msg)
					- NET_RCV_MAX + count))+3 &~ 3;
	    kmsg->ikm_header.msgh_local_port = MACH_PORT_NULL;
	    kmsg->ikm_header.msgh_kind = MACH_MSGH_KIND_NORMAL;
	    kmsg->ikm_header.msgh_id = NET_RCV_MSG_ID;

	    net_kmsg(kmsg)->header_type = header_type;
	    net_kmsg(kmsg)->packet_type = packet_type;
	    net_kmsg(kmsg)->net_rcv_msg_packet_count = count;

	    /*
	     * Send the packet to the destination port.  Drop it
	     * if the destination port is over its backlog.
	     */

	    if (ipc_mqueue_send(kmsg, MACH_SEND_TIMEOUT, 0) ==
						    MACH_MSG_SUCCESS) {
		if (high_priority)
		    net_kmsg_send_high_hits++;
		else
		    net_kmsg_send_low_hits++;
		/* the receiver is responsible for the message now */
	    } else {
		if (high_priority)
		    net_kmsg_send_high_misses++;
		else
		    net_kmsg_send_low_misses++;
		ipc_kmsg_destroy(kmsg);
	    }
	}

	(void) splimp();
	simple_lock(&net_queue_lock);
	return TRUE;
}

/*
 *	We want to deliver packets using ASTs, so we can avoid the
 *	thread_wakeup/thread_block needed to get to the network
 *	thread.  However, we can't allocate memory in the AST handler,
 *	because memory allocation might block.  Hence we have the
 *	network thread to allocate memory.  The network thread also
 *	delivers packets, so it can be allocating and delivering for a
 *	burst.  net_thread_awake is protected by net_queue_lock
 *	(instead of net_queue_free_lock) so that net_packet and
 *	net_ast can safely determine if the network thread is running.
 *	This prevents a race that might leave a packet sitting without
 *	being delivered.  It is possible for net_kmsg_get to think
 *	the network thread is awake, and so avoid a wakeup, and then
 *	have the network thread sleep without allocating.  The next
 *	net_kmsg_get will do a wakeup.
 */

void net_ast()
{
	spl_t s;

	net_ast_taken++;

	/*
	 *	If the network thread is awake, then we would
	 *	rather deliver messages from it, because
	 *	it can also allocate memory.
	 */

	s = splimp();
	simple_lock(&net_queue_lock);
	while (!net_thread_awake && net_deliver(TRUE))
		continue;

	/*
	 *	Prevent an unnecessary AST.  Either the network
	 *	thread will deliver the messages, or there are
	 *	no messages left to deliver.
	 */

	simple_unlock(&net_queue_lock);
	(void) splsched();
	ast_off(cpu_number(), AST_NETWORK);
	(void) splx(s);
}

void net_thread_continue()
{
	for (;;) {
		spl_t s;

		net_thread_awaken++;

		/*
		 *	First get more buffers.
		 */
		net_kmsg_more();

		s = splimp();
		simple_lock(&net_queue_lock);
		while (net_deliver(FALSE))
			continue;

		net_thread_awake = FALSE;
		assert_wait(&net_thread_awake, FALSE);
		simple_unlock(&net_queue_lock);
		(void) splx(s);
		counter(c_net_thread_block++);
		thread_block(net_thread_continue);
	}
}

void net_thread()
{
	spl_t s;

	/*
	 *	We should be very high priority.
	 */

	thread_set_own_priority(0);

	/*
	 *	We sleep initially, so that we don't allocate any buffers
	 *	unless the network is really in use and they are needed.
	 */

	s = splimp();
	simple_lock(&net_queue_lock);
	net_thread_awake = FALSE;
	assert_wait(&net_thread_awake, FALSE);
	simple_unlock(&net_queue_lock);
	(void) splx(s);
	counter(c_net_thread_block++);
	thread_block(net_thread_continue);
	net_thread_continue();
	/*NOTREACHED*/
}

void
reorder_queue(first, last)
	register queue_t	first, last;
{
	register queue_entry_t	prev, next;

	prev = first->prev;
	next = last->next;

	prev->next = last;
	next->prev = first;

	last->prev = prev;
	last->next = first;

	first->next = next;
	first->prev = last;
}

/*
 * Incoming packet.  Header has already been moved to proper place.
 * We are already at splimp.
 */
void
net_packet(ifp, kmsg, count, priority)
	register struct ifnet	*ifp;
	register ipc_kmsg_t	kmsg;
	unsigned int		count;
	boolean_t		priority;
{
	boolean_t awake;

#if	NORMA_ETHER
	if (netipc_net_packet(kmsg, count)) {
		return;
	}
#endif	NORMA_ETHER

#if	MACH_TTD
	/*
	 * Do a quick check to see if it is a kernel TTD packet.
	 *
	 * Only check if KernelTTD is enabled, ie. the current
	 * device driver supports TTD, and the bootp succeded.
	 */
	if (kttd_enabled && kttd_handle_async(kmsg)) {
		/* 
		 * Packet was a valid ttd packet and
		 * doesn't need to be passed up to filter.
		 * The ttd code put the used kmsg buffer
		 * back onto the free list.
		 */
		if (kttd_debug)
			printf("**%x**", kttd_async_counter++);
		return;
	}
#endif	/* MACH_TTD */

	kmsg->ikm_header.msgh_remote_port = (mach_port_t) ifp;
	net_kmsg(kmsg)->net_rcv_msg_packet_count = count;

	simple_lock(&net_queue_lock);
	if (priority) {
	    ipc_kmsg_enqueue(&net_queue_high, kmsg);
	    if (++net_queue_high_size > net_queue_high_max)
		net_queue_high_max = net_queue_high_size;
	} else {
	    ipc_kmsg_enqueue(&net_queue_low, kmsg);
	    if (++net_queue_low_size > net_queue_low_max)
		net_queue_low_max = net_queue_low_size;
	}
	/*
	 *	If the network thread is awake, then we don't
	 *	need to take an AST, because the thread will
	 *	deliver the packet.
	 */
	awake = net_thread_awake;
	simple_unlock(&net_queue_lock);

	if (!awake) {
	    spl_t s = splsched();
	    ast_on(cpu_number(), AST_NETWORK);
	    (void) splx(s);
	}
}

/*
 * Run a packet through the filters, returning a list of messages.
 * We are *not* called at interrupt level.
 */
void
net_filter(kmsg, send_list)
	register ipc_kmsg_t	kmsg;
	ipc_kmsg_queue_t	send_list;
{
	register struct ifnet	*ifp;
	register net_rcv_port_t	infp, nextfp;
	register ipc_kmsg_t	new_kmsg;
	net_rcv_port_t		dead = 0;
	int count = net_kmsg(kmsg)->net_rcv_msg_packet_count;

	ifp = (struct ifnet *) kmsg->ikm_header.msgh_remote_port;
	ipc_kmsg_queue_init(send_list);

	/*
	 * Unfortunately we can't allocate or deallocate memory
	 * while holding this lock.  And we can't drop the lock
	 * while examining the filter list.
	 */
	simple_lock(&ifp->if_rcv_port_list_lock);
	for (infp = (net_rcv_port_t) queue_first(&ifp->if_rcv_port_list);
	     !queue_end(&ifp->if_rcv_port_list, (queue_entry_t)infp);
	     infp = nextfp) {
	    nextfp = (net_rcv_port_t) queue_next(&infp->chain);

	    if (net_do_filter(infp, net_kmsg(kmsg)->packet, count,
				net_kmsg(kmsg)->header)) {
		register ipc_port_t dest;

		/*
		 * Make a send right for the destination.
		 */

		dest = ipc_port_copy_send(infp->rcv_port);
		if (!IP_VALID(dest)) {
		    /*
		     * This filter is dead.  We remove it from the
		     * filter list and set it aside for deallocation.
		     */

		    queue_remove(&ifp->if_rcv_port_list, infp,
				 net_rcv_port_t, chain);
		    infp->chain.next = (queue_entry_t) dead;
		    dead = infp;
		    break;
		}

		/*
		 * Deliver copy of packet to this channel.
		 */
		if (ipc_kmsg_queue_empty(send_list)) {
		    /*
		     * Only receiver, so far
		     */
		    new_kmsg = kmsg;
		} else {
		    /*
		     * Other receivers - must allocate message and copy.
		     */
		    new_kmsg = net_kmsg_get();
		    if (new_kmsg == IKM_NULL) {
			ipc_port_release_send(dest);
			break;
		    }

		    bcopy(
			net_kmsg(kmsg)->packet,
			net_kmsg(new_kmsg)->packet,
			count);
		    bcopy(
			net_kmsg(kmsg)->header,
			net_kmsg(new_kmsg)->header,
			NET_HDW_HDR_MAX);
		    net_kmsg(new_kmsg)->net_rcv_msg_packet_count = count;
		}

		new_kmsg->ikm_header.msgh_remote_port = (mach_port_t) dest;
		ipc_kmsg_enqueue(send_list, new_kmsg);

	    {
		register net_rcv_port_t prevfp;
		int rcount = ++infp->rcv_count;

		/*
		 * See if ordering of filters is wrong
		 */
		if (infp->priority >= NET_HI_PRI) {
		    prevfp = (net_rcv_port_t) queue_prev(&infp->chain);
		    /*
		     * If infp is not the first element on the queue,
		     * and the previous element is at equal priority
		     * but has a lower count, then promote infp to
		     * be in front of prevfp.
		     */
		    if ((queue_t)prevfp != &ifp->if_rcv_port_list &&
			infp->priority == prevfp->priority) {
			/*
			 * Threshold difference to prevent thrashing
			 */
			if (100 + prevfp->rcv_count < rcount)
			    reorder_queue(&prevfp->chain, &infp->chain);
		    }
		    /*
		     * High-priority filter -> no more deliveries
		     */
		    break;
		}
	    }
	    }
	}
	simple_unlock(&ifp->if_rcv_port_list_lock);

	/*
	 * Deallocate dead filters.
	 */
	for (infp = dead; infp != 0; infp = nextfp) {
	    nextfp = (net_rcv_port_t) infp->chain.next;

	    ipc_port_release_send(infp->rcv_port);
	    simple_lock(&net_kmsg_total_lock);
	    net_queue_free_min--;
	    net_kmsg_max -= infp->rcv_qlimit + 1;
	    simple_unlock(&net_kmsg_total_lock);
	    zfree(net_rcv_zone, (vm_offset_t) infp);
	}

	if (ipc_kmsg_queue_empty(send_list)) {
	    /* Not sent - recycle */
	    net_kmsg_put(kmsg);
	}
}

boolean_t
net_do_filter(infp, data, data_count, header)
	net_rcv_port_t	infp;
	char *		data;
	unsigned int	data_count;
	char *		header;
{
	int		stack[NET_FILTER_STACK_DEPTH+1];
	register int	*sp;
	register filter_t	*fp, *fpe;
	register unsigned int	op, arg;

	/*
	 * The filter accesses the header and data
	 * as unsigned short words.
	 */
	data_count /= sizeof(unsigned short);

#define	data_word	((unsigned short *)data)
#define	header_word	((unsigned short *)header)

	sp = &stack[NET_FILTER_STACK_DEPTH];
	fp = &infp->filter[0];
	fpe = infp->filter_end;

	*sp = TRUE;

	while (fp < fpe) {
	    arg = *fp++;
	    op = NETF_OP(arg);
	    arg = NETF_ARG(arg);

	    switch (arg) {
		case NETF_NOPUSH:
		    arg = *sp++;
		    break;
		case NETF_PUSHZERO:
		    arg = 0;
		    break;
		case NETF_PUSHLIT:
		    arg = *fp++;
		    break;
		case NETF_PUSHIND:
		    arg = *sp++;
		    if (arg >= data_count)
			return FALSE;
		    arg = data_word[arg];
		    break;
		case NETF_PUSHHDRIND:
		    arg = *sp++;
		    if (arg >= NET_HDW_HDR_MAX/sizeof(unsigned short))
			return FALSE;
		    arg = header_word[arg];
		    break;
		default:
		    if (arg >= NETF_PUSHSTK) {
			arg = sp[arg - NETF_PUSHSTK];
		    }
		    else if (arg >= NETF_PUSHHDR) {
			arg = header_word[arg - NETF_PUSHHDR];
		    }
		    else {
			arg -= NETF_PUSHWORD;
			if (arg >= data_count)
			    return FALSE;
			arg = data_word[arg];
		    }
		    break;

	    }
	    switch (op) {
		case NETF_OP(NETF_NOP):
		    *--sp = arg;
		    break;
		case NETF_OP(NETF_AND):
		    *sp &= arg;
		    break;
		case NETF_OP(NETF_OR):
		    *sp |= arg;
		    break;
		case NETF_OP(NETF_XOR):
		    *sp ^= arg;
		    break;
		case NETF_OP(NETF_EQ):
		    *sp = (*sp == arg);
		    break;
		case NETF_OP(NETF_NEQ):
		    *sp = (*sp != arg);
		    break;
		case NETF_OP(NETF_LT):
		    *sp = (*sp < arg);
		    break;
		case NETF_OP(NETF_LE):
		    *sp = (*sp <= arg);
		    break;
		case NETF_OP(NETF_GT):
		    *sp = (*sp > arg);
		    break;
		case NETF_OP(NETF_GE):
		    *sp = (*sp >= arg);
		    break;
		case NETF_OP(NETF_COR):
		    if (*sp++ == arg)
			return (TRUE);
		    break;
		case NETF_OP(NETF_CAND):
		    if (*sp++ != arg)
			return (FALSE);
		    break;
		case NETF_OP(NETF_CNOR):
		    if (*sp++ == arg)
			return (FALSE);
		    break;
		case NETF_OP(NETF_CNAND):
		    if (*sp++ != arg)
			return (TRUE);
		    break;
		case NETF_OP(NETF_LSH):
		    *sp <<= arg;
		    break;
		case NETF_OP(NETF_RSH):
		    *sp >>= arg;
		    break;
		case NETF_OP(NETF_ADD):
		    *sp += arg;
		    break;
		case NETF_OP(NETF_SUB):
		    *sp -= arg;
		    break;
	    }
	}
	return ((*sp) ? TRUE : FALSE);

#undef	data_word
#undef	header_word
}

/*
 * Check filter for invalid operations or stack over/under-flow.
 */
boolean_t
parse_net_filter(filter, count)
	register filter_t	*filter;
	unsigned int		count;
{
	register int	sp;
	register filter_t	*fpe = &filter[count];
	register filter_t	op, arg;

	sp = NET_FILTER_STACK_DEPTH;

	for (; filter < fpe; filter++) {
	    op = NETF_OP(*filter);
	    arg = NETF_ARG(*filter);

	    switch (arg) {
		case NETF_NOPUSH:
		    break;
		case NETF_PUSHZERO:
		    sp--;
		    break;
		case NETF_PUSHLIT:
		    filter++;
		    if (filter >= fpe)
			return (FALSE);	/* literal value not in filter */
		    sp--;
		    break;
		case NETF_PUSHIND:
		case NETF_PUSHHDRIND:
		    break;
		default:
		    if (arg >= NETF_PUSHSTK) {
			if (arg - NETF_PUSHSTK + sp > NET_FILTER_STACK_DEPTH)
			    return FALSE;
		    }
		    else if (arg >= NETF_PUSHHDR) {
			if (arg - NETF_PUSHHDR >=
				NET_HDW_HDR_MAX/sizeof(unsigned short))
			    return FALSE;
		    }
		    /* else... cannot check for packet bounds
				without packet */
		    sp--;
		    break;
	    }
	    if (sp < 2) {
		return (FALSE);	/* stack overflow */
	    }
	    if (op == NETF_OP(NETF_NOP))
		continue;

	    /*
	     * all non-NOP operators are binary.
	     */
	    if (sp > NET_MAX_FILTER-2)
		return (FALSE);

	    sp++;
	    switch (op) {
		case NETF_OP(NETF_AND):
		case NETF_OP(NETF_OR):
		case NETF_OP(NETF_XOR):
		case NETF_OP(NETF_EQ):
		case NETF_OP(NETF_NEQ):
		case NETF_OP(NETF_LT):
		case NETF_OP(NETF_LE):
		case NETF_OP(NETF_GT):
		case NETF_OP(NETF_GE):
		case NETF_OP(NETF_COR):
		case NETF_OP(NETF_CAND):
		case NETF_OP(NETF_CNOR):
		case NETF_OP(NETF_CNAND):
		case NETF_OP(NETF_LSH):
		case NETF_OP(NETF_RSH):
		case NETF_OP(NETF_ADD):
		case NETF_OP(NETF_SUB):
		    break;
		default:
		    return (FALSE);
	    }
	}
	return (TRUE);
}

/*
 * Set a filter for a network interface.
 *
 * We are given a naked send right for the rcv_port.
 * If we are successful, we must consume that right.
 */
io_return_t
net_set_filter(ifp, rcv_port, priority, filter, filter_count)
	struct ifnet	*ifp;
	ipc_port_t	rcv_port;
	int		priority;
	filter_t	*filter;
	unsigned int	filter_count;
{
	boolean_t	found;
	register net_rcv_port_t	infp, new_infp;

	/*
	 * Check the filter syntax.
	 */
	if (!parse_net_filter(filter, filter_count))
	    return (D_INVALID_OPERATION);

	/*
	 * Look for an existing filter on the same reply port.
	 * If there is one, replace it.
	 */
	new_infp = 0;
	simple_lock(&ifp->if_rcv_port_list_lock);

	while (TRUE) {
	    found = FALSE;
	    queue_iterate(&ifp->if_rcv_port_list, infp, net_rcv_port_t, chain)
	    {
		if (infp->rcv_port == rcv_port) {
		    /*
		     * Remove the old filter from list, and re-use its
		     * data structure.
		     */
		    remqueue(&ifp->if_rcv_port_list, (queue_entry_t)infp);
		    found = TRUE;

		    /*
		     * We keep the existing reference for the receive
		     * port.
		     */
		    break;
		}
	    }
	    if (found)
		break;

	    if (new_infp) {
		/*
		 * No existing filter - use the new structure.
		 */
		infp = new_infp;
		new_infp = 0;
		break;
	    }

	    /*
	     * Must unlock to allocate a new filter.  If someone else
	     * has added a filter on the same port after we have
	     * allocated, release the new structure and indicate
	     * an error.
	     */
	    simple_unlock(&ifp->if_rcv_port_list_lock);

	    new_infp = (net_rcv_port_t)zalloc(net_rcv_zone);
	    new_infp->rcv_port = rcv_port;
	    new_infp->rcv_count = 0;

	    /*
	     * Re-lock and try the lookup again.
	     */
	    simple_lock(&ifp->if_rcv_port_list_lock);
	}

	/*
	 * Change filter.
	 */
	{
	    register int i;

	    infp->priority = priority;
	    for (i = 0; i < filter_count; i++)
		infp->filter[i] = filter[i];
	    infp->filter_end = &infp->filter[i];
	}

	/*
	 * Insert according to priority.
	 */
	{
	    register net_rcv_port_t	next;

	    queue_iterate(&ifp->if_rcv_port_list, next, net_rcv_port_t, chain)
		if (infp->priority > next->priority)
		    break;
	    enqueue_tail((queue_t)&next->chain, (queue_entry_t)infp);
	}

	if (found) {
	    /*
	     * We found the receive port, so we already have a reference.
	     * Deallocate the extra reference.
	     */
	    ipc_port_release_send(rcv_port);
	} else {
	    mach_port_msgcount_t qlimit = 0;

	    /*
	     * We allocated a new filter, so increase net_queue_free_min
	     * and net_kmsg_max to allow for more queued messages.
	     */

	    if (IP_VALID(rcv_port)) {
		ip_lock(rcv_port);
		if (ip_active(rcv_port))
		    qlimit = rcv_port->ip_qlimit;
		ip_unlock(rcv_port);
	    }

	    infp->rcv_qlimit = qlimit;
	    simple_lock(&net_kmsg_total_lock);
	    net_queue_free_min++;
	    net_kmsg_max += qlimit + 1;
	    simple_unlock(&net_kmsg_total_lock);
	}

	simple_unlock(&ifp->if_rcv_port_list_lock);

	if (new_infp) {
	    /*
	     * Allocated one filter structure too many.
	     */
	    zfree(net_rcv_zone, (vm_offset_t) new_infp);
	}

	return (D_SUCCESS);
}

/*
 * Other network operations
 */
io_return_t
net_getstat(ifp, flavor, status, count)
	struct ifnet	*ifp;
	dev_flavor_t	flavor;
	dev_status_t	status;		/* pointer to OUT array */
	natural_t	*count;		/* OUT */
{
	switch (flavor) {
	    case NET_STATUS:
	    {
		register struct net_status *ns = (struct net_status *)status;

		if (*count < NET_STATUS_COUNT)
		    return (D_INVALID_OPERATION);
		
		ns->min_packet_size = ifp->if_header_size;
		ns->max_packet_size = ifp->if_header_size + ifp->if_mtu;
		ns->header_format   = ifp->if_header_format;
		ns->header_size	    = ifp->if_header_size;
		ns->address_size    = ifp->if_address_size;
		ns->flags	    = ifp->if_flags;
		ns->mapped_size	    = 0;

		*count = NET_STATUS_COUNT;
		break;
	    }
	    case NET_ADDRESS:
	    {
		register int	addr_byte_count;
		register int	addr_int_count;
		register int	i;

		addr_byte_count = ifp->if_address_size;
		addr_int_count = (addr_byte_count + (sizeof(int)-1))
					 / sizeof(int);

		if (*count < addr_int_count)
		    return (D_INVALID_OPERATION);

		bcopy((char *)ifp->if_address,
		      (char *)status,
		      (unsigned) addr_byte_count);
		if (addr_byte_count < addr_int_count * sizeof(int))
		    bzero((char *)status + addr_byte_count,
			  (unsigned) (addr_int_count * sizeof(int)
				      - addr_byte_count));

		for (i = 0; i < addr_int_count; i++) {
		    register int word;

		    word = status[i];
		    status[i] = htonl(word);
		}
		*count = addr_int_count;
		break;
	    }
	    default:
		return (D_INVALID_OPERATION);
	}
	return (D_SUCCESS);
}

io_return_t
net_write(ifp, start, ior)
	register struct ifnet *ifp;
	int		(*start)();
	io_req_t	ior;
{
	spl_t	s;
	kern_return_t	rc;
	boolean_t	wait;

	/*
	 * Reject the write if the interface is down.
	 */
	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING))
	    return (D_DEVICE_DOWN);

	/*
	 * Reject the write if the packet is too large or too small.
	 */
	if (ior->io_count < ifp->if_header_size ||
	    ior->io_count > ifp->if_header_size + ifp->if_mtu)
	    return (D_INVALID_SIZE);

	/*
	 * Wire down the memory.
	 */

	rc = device_write_get(ior, &wait);
	if (rc != KERN_SUCCESS)
	    return (rc);

	/*
	 *	Network interfaces can't cope with VM continuations.
	 *	If wait is set, just panic.
	*/
	if (wait) {
		panic("net_write: VM continuation");
	}

	/*
	 * Queue the packet on the output queue, and
	 * start the device.
	 */
	s = splimp();
	IF_ENQUEUE(&ifp->if_snd, ior);
	(*start)(ifp->if_unit);
	splx(s);
	
	return (D_IO_QUEUED);
}

/*
 * Initialize the whole package.
 */
void
net_io_init()
{
	register vm_size_t	size;

	size = sizeof(struct net_rcv_port);
	net_rcv_zone = zinit(size,
			     size * 1000,
			     PAGE_SIZE,
			     FALSE,
			     "net_rcv_port");

	size = ikm_plus_overhead(sizeof(struct net_rcv_msg));
	net_kmsg_size = round_page(size);

	/*
	 *	net_kmsg_max caps the number of buffers
	 *	we are willing to allocate.  By default,
	 *	we allow for net_queue_free_min plus
	 *	the queue limit for each filter.
	 *	(Added as the filters are added.)
	 */

	simple_lock_init(&net_kmsg_total_lock);
	if (net_kmsg_max == 0)
	    net_kmsg_max = net_queue_free_min;

	simple_lock_init(&net_queue_free_lock);
	ipc_kmsg_queue_init(&net_queue_free);

	simple_lock_init(&net_queue_lock);
	ipc_kmsg_queue_init(&net_queue_high);
	ipc_kmsg_queue_init(&net_queue_low);
}
