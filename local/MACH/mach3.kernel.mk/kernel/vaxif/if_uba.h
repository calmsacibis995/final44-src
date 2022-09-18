/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_uba.h,v $
 * Revision 2.3  90/06/02  15:09:28  rpd
 * 	Converted to new IPC.
 * 	[90/03/26  23:08:12  rpd]
 * 
 * Revision 2.2  90/01/11  11:47:06  dbg
 * 	Remove unused field from struct ifxmt.
 * 	[89/12/15            dbg]
 * 
 * Revision 2.1  89/08/03  16:39:50  rwd
 * Created.
 * 
 * 12-Oct-88  David Golub (dbg) at Carnegie-Mellon University
 *	Rewrote for MACH_KERNEL.
 *
 * 18-Nov-86  David Golub (dbg) at Carnegie-Mellon University
 *	Moved definition of Mbmap here for MACH.
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
 *	@(#)if_uba.h	7.3 (Berkeley) 8/4/88
 */

#ifndef	_VAXIF_IF_UBA_H_
#define	_VAXIF_IF_UBA_H_

#include <ipc/ipc_kmsg.h>

#include <sys/types.h>
#include <device/device_types.h>
#include <device/io_req.h>
#include <device/if_hdr.h>

#include <vax/pte.h>
#include <vaxuba/ubareg.h>

/*
 * Structure and routine definitions
 * for UNIBUS network interfaces.
 */

#define	IF_MAXNUBAMR	10
/*
 * Each interface has structures giving information
 * about UNIBUS resources held by the interface
 * for each send and receive buffer.
 *
 * We hold IF_NUBAMR map registers for datagram data, starting
 * at ifr_mr[1].  Map register ifr_mr[0] maps the local network header.
 * Bdp's are reserved for read and for
 * write, given by ifr_bdp.  The prototype of the map register for
 * read and for write is saved in ifr_proto.
 *
 * Write transfers are mapped onto the UNIBUS, as for disk devices.
 *
 * When a read transfer completes, we swap the virtual and physical
 * addresses for a new buffer coming off the read request queue.  If
 * there are no new read requests, we drop the packet.
 */

/*
 * Common structures for network.
 */

/*
 * Information per interface.
 */
struct ifubinfo {
	short	iff_uban;		/* uba number */
	short	iff_hlen;		/* local net header length */
	short	iff_hoff;		/* offset from start of page
					   to start of header */
	short	iff_size;		/* total length of alloc data,
					   including all padding */
	short	iff_min;		/* minimum size packet to send */
	short	iff_flags;		/* used during uballoc */
	struct uba_regs *iff_uba;	/* uba regs, in vm */
};

/*
 * Information per buffer.
 */
struct ifrw {
	char	*ifrw_addr;			/* virtual addr of header */
	short	ifrw_bdp;			/* unibus bdp */
	short	ifrw_flags;
#define	IFRW_W	0x01				/* is a transmit buffer */
	int	ifrw_info;			/* addr from uballoc */
	int	ifrw_proto;			/* map register prototype */
	struct pte *ifrw_mr;			/* base of map registers */
	union ifrw_rw {
	    io_req_t	w_xtofree;		/* transmit: data to free
						   when done */
	    ipc_kmsg_t	r_msg;			/* receive: message buffer
						   to send */
	} ifrw_rw;
};
#define	ifrw_msg	ifrw_rw.r_msg

/*
 * Different name for transmit buffer (for historical reasons).
 */
struct ifxmt {
	struct ifrw	ifrw;
};
#define	ifw_addr	ifrw.ifrw_addr
#define	ifw_bdp		ifrw.ifrw_bdp
#define	ifw_flags	ifrw.ifrw_flags
#define	ifw_info	ifrw.ifrw_info
#define	ifw_proto	ifrw.ifrw_proto
#define	ifw_mr		ifrw.ifrw_mr
#define	ifw_xtofree	ifrw.ifrw_rw.w_xtofree

/*
 * Most interfaces have a single receive and a single transmit buffer.
 * and use struct ifuba to store all of the unibus information.
 */
struct ifuba {
	struct ifubinfo	ifu_info;
	struct ifrw	ifu_r;
	struct ifxmt	ifu_xmt;
};

#define	ifu_uban	ifu_info.iff_uban
#define	ifu_hlen	ifu_info.iff_hlen
#define	ifu_hoff	ifu_info.iff_hoff
#define	ifu_len		ifu_info.iff_len
#define	ifu_uba		ifu_info.iff_uba
#define	ifu_flags	ifu_info.iff_flags

#ifdef	KERNEL
boolean_t	if_ubaminit();
void		if_ubaput();
void		if_ubaget();

#define	if_ubainit(ifuba, uban, hlen, nmr, minlen) \
		if_ubaminit(&(ifuba)->ifu_info, ubah, hlen, nmr, \
			&(ifuba)->ifu_r, 1, &(ifuba)->ifu_xmt, 1, minlen)
#define	if_rubaget(ifu, totlen, ifp) \
		if_ubaget(&(ifu)->ifu_info, &(ifu)->ifu_r, totlen, ifp)
#define	if_wubaput(ifu, ior, bus_addr, length) \
		if_ubaput(&(ifu)->ifu_info, &(ifu)->ifu_xmt, ior, \
			bus_addr, length)

#endif	KERNEL

#endif	_VAXIF_IF_UBA_H_
