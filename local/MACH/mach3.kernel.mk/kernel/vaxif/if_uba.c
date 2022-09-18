/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_uba.c,v $
 * Revision 2.6  91/03/16  15:03:16  rpd
 * 	Changed net_filter to net_packet.
 * 	[91/01/15            rpd]
 * 
 * Revision 2.5  91/01/08  16:42:56  rpd
 * 	Changed NET_KMSG_GET, NET_KMSG_FREE to net_kmsg_get, net_kmsg_put.
 * 	[91/01/05            rpd]
 * 
 * Revision 2.4  90/06/02  15:09:23  rpd
 * 	Converted to new IPC.
 * 	[90/03/26  23:07:49  rpd]
 * 
 * Revision 2.3  90/01/11  11:47:01  dbg
 * 	Fix if_ubaget to recognize loopback packets (IFRW_W set) and
 * 	copy the packet to a new kmsg instead of mangling the transmit
 * 	buffer.
 * 	[89/12/18            dbg]
 * 
 * 	Clear ifw_addr in ifubaminit - it is not valid.  Set
 * 	it when mapping a transmit buffer.  Remove lint.
 * 	[89/12/15            dbg]
 * 
 * Revision 2.2  89/09/08  11:28:06  dbg
 * 	Don't include device_task.h - we don't use device_map.
 * 	[89/08/01            dbg]
 * 
 * 13-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Receive packets directly into message buffers.
 *
 *  3-Mar-89  David Golub (dbg) at Carnegie-Mellon University
 *	Heavily altered for MACH kernel.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)if_uba.c	7.9 (Berkeley) 5/24/88
 */

#include <mach/vm_param.h>
#include <vm/vm_kern.h>

#include <device/if_hdr.h>
#include <device/if_ether.h>
#include <device/net_io.h>
#include <vax/vm_defs.h>

#include <vaxif/if_uba.h>
#include <vaxuba/ubavar.h>

/*
 * Initialize UNIBUS memory for network interface.
 *
 * Adjust mapping information so that header ends on a 4-byte boundary.
 */
boolean_t
if_ubaminit(ifu, uban, hlen, nmr, ifr, nr, ifw, nw, minlen)
	register struct ifubinfo	*ifu;
	int		uban;	/* UNIBUS adaptor number */
	int		hlen;	/* header length */
	int		nmr;	/* number of pages for rest of each packet */
	register struct ifrw *ifr;
				/* receive buffer list */
	int		nr;	/* number of receive buffers */
	register struct ifxmt *ifw;
				/* transmit buffer list */
	int		nw;	/* number of transmit buffers */
	int		minlen;	/* minimum length packet to transmit */

{
	register int	i, hoff;
	vm_offset_t	cp;
	vm_size_t	size;

	/*
	 * Allocate enough mapping registers for both send and
	 * receive so that a full-size packet can be mapped on
	 * any alignment.  We may waste mapping registers this
	 * way, but it should be cheaper than copying the data.
	 */
	size = vax_round_page(nmr*VAX_PGBYTES + hlen + (VAX_PGBYTES-1));

	/*
	 * Set offset for receiving so that data lands at byte 4 of
	 * the network message.  For most interfaces, that will place
	 * the type word at byte 2, where the network message wants it.
	 */
	hoff = sizeof(struct packet_header) - hlen;

	cp = (vm_offset_t)ifr[0].ifrw_addr;
	if (cp == 0) {
	    /*
	     * Allocate initial receive buffers.  Each will be traded
	     * for a new one when handled out of the kernel.
	     */
	    for (i = 0; i < nr; i++) {
		register ipc_kmsg_t	kmsg;

		kmsg = net_kmsg_alloc();
		if (kmsg == IKM_NULL) {
		    return (FALSE);
		}
		ifr[i].ifrw_msg = kmsg;
		ifr[i].ifrw_addr = &net_kmsg(kmsg)->packet[hoff];
	    }

	    ifu->iff_uban = uban;
	    ifu->iff_hlen = hlen;
	    ifu->iff_hoff = hoff;
	    ifu->iff_size = size;
	    ifu->iff_min  = minlen;
	    ifu->iff_uba  = uba_hd[uban].uh_uba;

	    /*
	     * Point to the first receive buffer allocated,
	     * to fake a transmit area for uballoc.
	     */
	    cp = (vm_offset_t)ifr[0].ifrw_addr;
	}

	/*
	 * Allocate UNIBUS space for receive buffers.
	 */
	for (i = 0; i < nr; i++) {
	    if (!if_ubaalloc(ifu, &ifr[i])) {
		nr = i;
		nw = 0;
		goto bad;
	    }
	}

	/*
	 * Allocate UNIBUS space for transmit buffers.
	 * Since the allocation routine insists on mapping
	 * some memory during allocation, give it some.
	 * Remove any byte-offset within page so that
	 * the map register prototype is clean.
	 */
	for (i = 0; i < nw; i++) {
	    ifw[i].ifw_addr = (char *)(cp & ~PGOFSET);
	    if (!if_ubaalloc(ifu, &ifw[i].ifrw)) {
		nw = i;
		goto bad;
	    }
	    ifw[i].ifw_xtofree = 0;
	    ifw[i].ifw_flags = IFRW_W;

	    /*
	     * Clear the phony address to avoid confusion.
	     */
	    ifw[i].ifw_addr = (char *)-1;	/* invalid */
	}
	return (TRUE);

	/*
	 * If there is not enough UNIBUS space, deallocate
	 * everything.
	 */
    bad:
	while (--nw > 0)
	    ubarelse(ifu->iff_uban, &ifw[nw].ifw_info);
	for (i = 0; i < nr; i++)
	    net_kmsg_put(ifr[i].ifrw_msg);
	while (--nr > 0)
	    ubarelse(ifu->iff_uban, &ifr[nr].ifrw_info);
	ifr[0].ifrw_addr = 0;
	return (FALSE);
}

/*
 * Allocate map registers (and possibly a buffered data path)
 * for a receive or transmit buffer.
 */
boolean_t
if_ubaalloc(ifu, ifrw)
	register struct ifubinfo *ifu;
	register struct ifrw	*ifrw;
{
	register int	info;

	info = uballoc(ifu->iff_uban,
		       ifrw->ifrw_addr,
		       ifu->iff_size,
		       ifu->iff_flags);
	if (info == 0)
	    return (FALSE);

	ifrw->ifrw_bdp	 = UBAI_BDP(info);
	ifrw->ifrw_info	 = info;
	ifrw->ifrw_proto = UBAMR_MRV | (UBAI_BDP(info) << UBAMR_DPSHIFT);
	ifrw->ifrw_mr	 = &uba_hd[ifu->iff_uban].uh_mr[UBAI_MR(info)];

	return (TRUE);
}

/*
 * Map an area of memory onto a network interface.  Return
 * the UNIBUS address and length.
 */
void
if_ubaput(ifu, ifw, ior, bus_addr, length)
	struct ifubinfo		*ifu;
	register struct ifxmt	*ifw;
	io_req_t		ior;
	int			*bus_addr;	/* out */
	int			*length;	/* out */
{
	char		*addr;
	vm_size_t	size;
	register struct pte *pte;
	register int	*ip;
	register int	ncl, proto;
	int		o;
	boolean_t	pad;

	addr = ior->io_data;
	o = ((vm_offset_t) addr) & PGOFSET;

	size = ior->io_count;
	if (size > ifu->iff_size)
	    size = ifu->iff_size;

	ncl = btoc(size + o);
	pad = (ncl < btoc(ifu->iff_min + o));

	pte = (struct pte *)pmap_pte(kernel_pmap, (vm_offset_t) addr);

	proto = ifw->ifw_proto & ~UBAMR_BO;
	if (o & 01)
	    proto |= UBAMR_BO;

	ip = (int *)ifw->ifw_mr;
	while (--ncl >= 0)
	    *ip++ = proto | pte++->pg_pfnum;
	if (pad)
	    *ip++ = proto;	/* always data at page 0 */
	*ip = 0;

	ifw->ifw_addr = addr;
	ifw->ifw_xtofree = ior;

	*bus_addr = ifw->ifw_info | o;
	*length = size;
}

/*
 * Swap memory for incoming packet and receive buffer,
 * and move packet to receive-completed list.
 */
void
if_ubaget(ifu, ifr, totlen, ifp)
	struct ifubinfo		*ifu;
	register struct ifrw	*ifr;
	int			totlen;	/* including local header */
	struct ifnet		*ifp;
{
	register ipc_kmsg_t	new_kmsg, old_kmsg;
	char			*old_addr;

	/*
	 * Get a new kmsg to swap with.
	 */
	new_kmsg = net_kmsg_get();
	if (new_kmsg == IKM_NULL) {
	    /*
	     * Drop the received packet
	     */
	    ifp->if_rcvdrops++;
	    return;
	}

	if (ifr->ifrw_flags & IFRW_W) {
	    /*
	     * This is a looped-back transmit buffer, not a
	     * net_kmsg used as a receiver buffer.  Copy
	     * the packet into the net_kmsg instead of
	     * scrambling the transmit descriptor.
	     *
	     * To simplify the code, we copy the transmit packet
	     * into the receive message buffer as if it was
	     * received at the same location.  (We copy the
	     * hardware header twice.)
	     *
	     * We also grab the length from the IOR that holds
	     * the transmit packet, since the packet may have been
	     * padded (with invalid data) to any minimum transmit
	     * length.
	     */

	    totlen = ifr->ifrw_rw.w_xtofree->io_count;

	    old_kmsg = new_kmsg;
	    old_addr = &net_kmsg(new_kmsg)->packet[ifu->iff_hoff];

	    bcopy(ifr->ifrw_addr,
		  old_addr,
		  (unsigned) totlen);

	}
	else {
	    register struct pte	*pte;
	    register int	*ip;
	    register int	ncl, proto;
	    char		*new_addr;

	    /*
	     * Swap the received buffer with the memory from the
	     * new message.
	     */
	    old_kmsg = ifr->ifrw_msg;
	    old_addr = ifr->ifrw_addr;

	    ifr->ifrw_msg  = new_kmsg;
	    new_addr = &net_kmsg(new_kmsg)->packet[ifu->iff_hoff];
	    ifr->ifrw_addr = new_addr;

	    /*
	     * Map new address onto the UNIBUS.
	     */
	    ncl = btoc(ifu->iff_size);

	    pte = (struct pte *)pmap_pte(kernel_pmap, (vm_offset_t)new_addr);

	    proto = ifr->ifrw_proto & ~UBAMR_BO;
	    if ((vm_offset_t)new_addr & 01)
		proto |= UBAMR_BO;

	    ip = (int *)ifr->ifrw_mr;
	    while (--ncl >= 0)
		*ip++ = proto | pte++->pg_pfnum;
	    *ip = 0;

	    /*
	     * XXX offset may have changed!!!! net kmsgs are NOT dependably
	     * multiples of the page size!!!
	     * YYY for simplicity, we make them so.
	     */
	}

	/*
	 * Move the header to the proper place in the net message.
	 */
	bcopy(old_addr,
	      net_kmsg(old_kmsg)->header,
	      (unsigned) ifp->if_header_size);

	/*
	 * Set up the 'fake' header with length.  Type has been left
	 * in the correct place.
	 */
	totlen = totlen - ifp->if_header_size
			+ sizeof(struct packet_header);
	((struct packet_header *)&net_kmsg(old_kmsg)->packet[0])
		->length = totlen;
	/*
	 * Hand the packet to the network module.
	 */
	net_packet(ifp, old_kmsg, (unsigned) totlen,
		   ethernet_priority(old_kmsg));
}

