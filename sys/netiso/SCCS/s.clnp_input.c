h32916
s 00002/00002/00523
d D 8.1 93/06/10 23:18:30 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00522
d D 7.16 93/05/25 11:51:27 bostic 16 15
c trailing comment after #else or #endif
e
s 00023/00024/00502
d D 7.15 92/10/11 12:21:35 bostic 15 14
c make kernel includes standard
e
s 00003/00015/00523
d D 7.14 92/02/14 14:16:24 sklower 14 13
c changes proposed by hagens to make CLNP EchoReply work
e
s 00009/00005/00529
d D 7.13 91/05/06 18:58:50 bostic 13 12
c new copyright; att/bsd/shared
e
s 00011/00002/00523
d D 7.12 90/06/20 19:02:21 sklower 12 11
c changed esis to make use of routing table; mostly works;
c checkpoint before UW merge
e
s 00001/00001/00524
d D 7.11 90/05/03 17:39:06 sklower 11 10
c fix minor bugs for raw access
e
s 00001/00009/00524
d D 7.10 90/01/16 23:45:45 sklower 10 9
c mitre decbit changes; consumer side only
c Van J. promises better forwarding code real-soon-now!
e
s 00007/00005/00526
d D 7.9 90/01/16 23:38:20 sklower 9 8
c checkpoint before merging mitre decbit changes
e
s 00003/00002/00528
d D 7.8 89/09/26 23:57:56 sklower 8 7
c Fixes from Dave Katz at um
e
s 00005/00001/00525
d D 7.7 89/09/22 00:15:27 sklower 7 6
c make changes for SNMP
e
s 00006/00005/00520
d D 7.6 89/08/29 13:43:52 sklower 6 5
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00009/00009/00516
d D 7.5 89/04/25 17:19:31 mckusick 5 4
c ../h => (implicitly) ../sys
e
s 00065/00041/00460
d D 7.4 89/04/22 11:53:22 sklower 4 3
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00053/00024/00448
d D 7.3 89/02/14 18:31:04 sklower 3 2
c wisconsin changes for DEC bit, etc.
e
s 00017/00005/00455
d D 7.2 89/02/14 18:30:34 sklower 2 1
c berkeley changes to deal with new mbufs, different paradigm for headers
e
s 00460/00000/00000
d D 7.1 88/12/14 15:29:24 sklower 1 0
c date and time created 88/12/14 15:29:24 by sklower
e
u
U
t
T
I 13
/*-
D 17
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 13
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
D 3
/* $Header: clnp_input.c,v 4.4 88/09/08 08:38:15 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_input.c,v $ */
E 3
I 3
/* $Header: /var/src/sys/netiso/RCS/clnp_input.c,v 5.1 89/02/09 16:20:32 hagens Exp $ */
/* $Source: /var/src/sys/netiso/RCS/clnp_input.c,v $ */
E 3
I 2
D 13
/*	%W% (Berkeley) %G% */
E 2

#ifndef lint
D 3
static char *rcsid = "$Header: clnp_input.c,v 4.4 88/09/08 08:38:15 hagens Exp $";
E 3
I 3
static char *rcsid = "$Header: /var/src/sys/netiso/RCS/clnp_input.c,v 5.1 89/02/09 16:20:32 hagens Exp $";
E 3
#endif lint
E 13

D 5
#include "../h/types.h"
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
#include "../h/time.h"
E 5
I 5
D 15
#include "types.h"
#include "param.h"
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
#include "time.h"
E 15
I 15
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>
E 15
E 5

D 15
#include "../net/if.h"
I 4
D 7
#include "../net/iftypes.h"
E 7
I 7
#include "../net/if_types.h"
E 7
E 4
#include "../net/route.h"
E 15
I 15
#include <net/if.h>
#include <net/if_types.h>
#include <net/route.h>
E 15

D 4
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
#include "../netiso/iso_snpac.h"
#include "../netiso/clnp.h"
#include "../netiso/clnl.h"
#include "../netiso/esis.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
E 4
I 4
D 15
#include "iso.h"
#include "iso_var.h"
#include "iso_snpac.h"
#include "clnp.h"
#include "clnl.h"
I 6
#include "esis.h"
E 6
#include "../netinet/in_systm.h"
#include "../netinet/ip.h"
I 6
#include "../netinet/if_ether.h"
E 6
#include "eonvar.h"
D 6
#include "esis.h"
E 6
#include "clnp_stat.h"
#include "argo_debug.h"
E 15
I 15
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_snpac.h>
#include <netiso/clnp.h>
#include <netiso/clnl.h>
#include <netiso/esis.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netiso/eonvar.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 15
E 4

#ifdef ISO
u_char		clnp_protox[ISOPROTO_MAX];
struct clnl_protosw clnl_protox[256];
int			clnpqmaxlen = IFQ_MAXLEN;	/* RAH? why is this a variable */
struct mbuf	*clnp_data_ck();

int	clnp_input();

int	esis_input();

#ifdef	ISO_X25ESIS
int	x25esis_input();
D 16
#endif	ISO_X25ESIS
E 16
I 16
#endif	/* ISO_X25ESIS */
E 16

/*
 * FUNCTION:		clnp_init
 *
 * PURPOSE:			clnp initialization. Fill in clnp switch tables.
 *
 * RETURNS:			none
 *
 * SIDE EFFECTS:	fills in clnp_protox table with correct offsets into
 *					the isosw table.
 *
 * NOTES:			
 */
clnp_init()
{
	register struct protosw *pr;

	/*
	 *	CLNP protox initialization
	 */
	if ((pr = pffindproto(PF_ISO, ISOPROTO_RAW, SOCK_RAW)) == 0)
		printf("clnl_init: no raw CLNP\n");
	else
		clnp_protox[ISOPROTO_RAW] = pr - isosw;

	if ((pr = pffindproto(PF_ISO, ISOPROTO_TP, SOCK_SEQPACKET)) == 0)
		printf("clnl_init: no tp/clnp\n");
	else
		clnp_protox[ISOPROTO_TP] = pr - isosw;

	/*
	 *	CLNL protox initialization
	 */
	clnl_protox[ISO8473_CLNP].clnl_input = clnp_input;

	clnlintrq.ifq_maxlen = clnpqmaxlen;
}

/*
 * FUNCTION:		clnlintr
 *
 * PURPOSE:			Process a packet on the clnl input queue
 *
 * RETURNS:			nothing.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
clnlintr()
{
	register struct mbuf		*m;		/* ptr to first mbuf of pkt */
	register struct clnl_fixed	*clnl;	/* ptr to fixed part of clnl hdr */
D 4
	struct ifnet				*ifp;	/* ptr to interface pkt arrived on */
E 4
	int							s;		/* save and restore priority */
	struct clnl_protosw			*clnlsw;/* ptr to protocol switch */
	struct snpa_hdr				sh;		/* subnetwork hdr */

	/*
	 *	Get next datagram off clnl input queue
	 */
next:
	s = splimp();
D 4

E 4
D 2
	IF_DEQUEUESNPAHDR(&clnlintrq, m, sh);
E 2
I 2
	/* IF_DEQUEUESNPAHDR(&clnlintrq, m, sh);*/
	IF_DEQUEUE(&clnlintrq, m);
I 4
	splx(s);
E 4
E 2

I 2

D 4
	splx(s);
E 4
	if (m == 0)		/* nothing to do */
		return;
D 4
	if (m->m_flags & M_PKTHDR == 0) {
E 4
I 4
D 12
	if ((m->m_flags & M_PKTHDR) == 0) {
E 12
I 12
	if ((m->m_flags & M_PKTHDR) == 0 || m->m_pkthdr.rcvif == 0) {
E 12
E 4
		m_freem(m);
		goto next;
I 12
	} else {
		register struct ifaddr *ifa;
		for (ifa = m->m_pkthdr.rcvif->if_addrlist; ifa; ifa = ifa->ifa_next)
			if (ifa->ifa_addr->sa_family == AF_ISO)
				break;
		if (ifa == 0) {
			m_freem(m);
			goto next;
		}
E 12
	}
D 4
	bcopy((caddr_t)(mtod(m, struct llc_etherhdr *)->dst),
		(caddr_t)sh.snh_dhost, 2*sizeof(sh.snh_dhost));
	m->m_data += sizeof (struct llc_etherhdr);
	m->m_len -= sizeof (struct llc_etherhdr);
	m->m_pkthdr.len -= sizeof (struct llc_etherhdr);
	sh.snh_ifp = m->m_pkthdr.rcvif;
E 4
I 4
	bzero((caddr_t)&sh, sizeof(sh));
	sh.snh_flags = m->m_flags & (M_MCAST|M_BCAST);
	switch((sh.snh_ifp = m->m_pkthdr.rcvif)->if_type) {
		extern int ether_output();
	case IFT_EON:
		bcopy(mtod(m, caddr_t), (caddr_t)sh.snh_dhost, sizeof(u_long));
		bcopy(sizeof(u_long) + mtod(m, caddr_t),
					(caddr_t)sh.snh_shost, sizeof(u_long));
		sh.snh_dhost[4] = mtod(m, u_char *)[sizeof(struct ip) +
								_offsetof(struct eon_hdr, eonh_class)];
		m->m_data += EONIPLEN;
		m->m_len -= EONIPLEN;
		m->m_pkthdr.len -= EONIPLEN;
		break;

	default:
		if (sh.snh_ifp->if_output == ether_output) {
D 6
			bcopy((caddr_t)(mtod(m, struct llc_etherhdr *)->dst),
E 6
I 6
			bcopy((caddr_t)(mtod(m, struct ether_header *)->ether_dhost),
E 6
				(caddr_t)sh.snh_dhost, 2*sizeof(sh.snh_dhost));
D 6
			m->m_data += sizeof (struct llc_etherhdr);
			m->m_len -= sizeof (struct llc_etherhdr);
			m->m_pkthdr.len -= sizeof (struct llc_etherhdr);
E 6
I 6
			m->m_data += sizeof (struct ether_header);
			m->m_len -= sizeof (struct ether_header);
			m->m_pkthdr.len -= sizeof (struct ether_header);
E 6
		}
	}
E 4
E 2
	IFDEBUG(D_INPUT)
		int i;
		printf("clnlintr: src:");
		for (i=0; i<6; i++)
			printf("%x%c", sh.snh_shost[i] & 0xff, (i<5) ? ':' : ' ');
		printf(" dst:");
		for (i=0; i<6; i++)
			printf("%x%c", sh.snh_dhost[i] & 0xff, (i<5) ? ':' : ' ');
		printf("\n");
	ENDDEBUG
D 2

	splx(s);
	if (m == 0)		/* nothing to do */
		return;
E 2

	/*
	 *	Get the fixed part of the clnl header into the first mbuf.
	 *	Drop the packet if this fails.
	 *	Do not call m_pullup if we have a cluster mbuf or the
	 *	data is not there.
	 */
	if ((IS_CLUSTER(m) || (m->m_len < sizeof(struct clnl_fixed))) &&
		((m = m_pullup(m, sizeof(struct clnl_fixed))) == 0)) {
		INCSTAT(cns_toosmall);	/* TODO: use clnl stats */
		goto next;				/* m_pullup discards mbuf */
	}

	clnl = mtod(m, struct clnl_fixed *);

	/*
	 *	Drop packet if the length of the header is not reasonable.
	 */
	if ((clnl->cnf_hdr_len < CLNP_HDR_MIN) || 
		(clnl->cnf_hdr_len > CLNP_HDR_MAX)) {
		INCSTAT(cns_badhlen);	/* TODO: use clnl stats */
		m_freem(m);
		goto next;
	}

	/*
	 *	If the header is not contained in this mbuf, make it so.
	 *	Drop packet if this fails.
	 *	Note: m_pullup will allocate a cluster mbuf if necessary
	 */
	if (clnl->cnf_hdr_len > m->m_len) {
D 4
		if ((m = m_pullup(m, clnl->cnf_hdr_len)) == 0) {
E 4
I 4
		if ((m = m_pullup(m, (int)clnl->cnf_hdr_len)) == 0) {
E 4
			INCSTAT(cns_badhlen);	/* TODO: use clnl stats */
			goto next;	/* m_pullup discards mbuf */
		}
		clnl = mtod(m, struct clnl_fixed *);
	}

	clnlsw = &clnl_protox[clnl->cnf_proto_id];


	if (clnlsw->clnl_input)
		(*clnlsw->clnl_input) (m, &sh);
	else
		m_freem(m);

	goto next;
}

/*
 * FUNCTION:		clnp_input
 *
 * PURPOSE:			process an incoming clnp packet
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	increments fields of clnp_stat structure.
 *					
 * NOTES:
 *	TODO: I would like to make seg_part a pointer into the mbuf, but 
 *	will it be correctly aligned?
 */
D 4
int clnp_input(m, shp)
E 4
I 4
clnp_input(m, shp)
E 4
struct mbuf		*m;		/* ptr to first mbuf of pkt */
struct snpa_hdr	*shp;	/* subnetwork header */
{
	register struct clnp_fixed	*clnp;	/* ptr to fixed part of header */
D 9
	struct iso_addr				src;	/* source address of pkt */
	struct iso_addr				dst;	/* destination address of pkt */
E 9
I 9
	struct sockaddr_iso			source; /* source address of pkt */
	struct sockaddr_iso			target; /* destination address of pkt */
#define src	source.siso_addr
#define dst	target.siso_addr
E 9
	caddr_t						hoff;	/* current offset in packet */
	caddr_t						hend;	/* address of end of header info */
	struct clnp_segment			seg_part; /* segment part of hdr */
	int							seg_off=0; /* offset of segment part of hdr */
	int							seg_len;/* length of packet data&hdr in bytes */
	struct clnp_optidx			oidx, *oidxp = NULL;	/* option index */
	extern int 					iso_systype;	/* used by ESIS config resp */
I 9
	extern struct sockaddr_iso	blank_siso;		/* used for initializing */
E 9
I 3
	int							need_afrin = 0; 
										/* true if congestion experienced */
										/* which means you need afrin nose */
										/* spray. How clever! */
E 3

	IFDEBUG(D_INPUT)
		printf(
D 3
		"clnp_input: proccessing dg; First mbuf m_len %d, m_type x%x, data:\n", 
			m->m_len, m->m_type);
E 3
I 3
		   "clnp_input: proccessing dg; First mbuf m_len %d, m_type x%x, %s\n", 
			m->m_len, m->m_type, IS_CLUSTER(m) ? "cluster" : "normal");
E 3
	ENDDEBUG
D 3
	IFDEBUG(D_DUMPIN)
		printf("clnp_input: first mbuf:\n");
		dump_buf(mtod(m, caddr_t), m->m_len);
	ENDDEBUG
E 3
I 3
	need_afrin = 0;
E 3

	/*
	 *	If no iso addresses have been set, there is nothing
	 *	to do with the packet.
	 */
	if (iso_ifaddr == NULL) {
		clnp_discard(m, ADDR_DESTUNREACH);
		return;
	}
	
	INCSTAT(cns_total);
	clnp = mtod(m, struct clnp_fixed *);

I 3
	IFDEBUG(D_DUMPIN)
		struct mbuf *mhead;
		int			total_len = 0;
		printf("clnp_input: clnp header:\n");
		dump_buf(mtod(m, caddr_t), clnp->cnf_hdr_len);
		printf("clnp_input: mbuf chain:\n");
		for (mhead = m; mhead != NULL; mhead=mhead->m_next) {
			printf("m x%x, len %d\n", mhead, mhead->m_len);
			total_len += mhead->m_len;
		}
		printf("clnp_input: total length of mbuf chain %d:\n", total_len);
	ENDDEBUG

E 3
	/*
	 *	Compute checksum (if necessary) and drop packet if
	 *	checksum does not match
	 */
D 4
	if (CKSUM_REQUIRED(clnp) && iso_check_csum(m, clnp->cnf_hdr_len)) {
E 4
I 4
	if (CKSUM_REQUIRED(clnp) && iso_check_csum(m, (int)clnp->cnf_hdr_len)) {
E 4
		INCSTAT(cns_badcsum);
		clnp_discard(m, GEN_BADCSUM);
D 3
		return;
E 3
I 3
D 4
		return 0;
E 4
I 4
		return;
E 4
E 3
	}

	if (clnp->cnf_vers != ISO8473_V1) {
		INCSTAT(cns_badvers);
		clnp_discard(m, DISC_UNSUPPVERS);
D 3
		return;
E 3
I 3
D 4
		return 0;
E 4
I 4
		return;
E 4
E 3
	}


 	/* check mbuf data length: clnp_data_ck will free mbuf upon error */
	CTOH(clnp->cnf_seglen_msb, clnp->cnf_seglen_lsb, seg_len);
	if ((m = clnp_data_ck(m, seg_len)) == 0)
D 3
		return;
E 3
I 3
D 4
		return 0;
E 4
I 4
		return;
E 4
E 3
	
	clnp = mtod(m, struct clnp_fixed *);
	hend = (caddr_t)clnp + clnp->cnf_hdr_len;

	/* 
	 *	extract the source and destination address
	 *	drop packet on failure
	 */
D 9
	bzero((caddr_t)&src, sizeof(src));
	bzero((caddr_t)&dst, sizeof(dst));
E 9
I 9
	source = target = blank_siso;
E 9

	hoff = (caddr_t)clnp + sizeof(struct clnp_fixed);
	CLNP_EXTRACT_ADDR(dst, hoff, hend);
	if (hoff == (caddr_t)0) {
		INCSTAT(cns_badaddr);
		clnp_discard(m, GEN_INCOMPLETE);
D 3
		return;
E 3
I 3
D 4
		return 0;
E 4
I 4
		return;
E 4
E 3
	}
	CLNP_EXTRACT_ADDR(src, hoff, hend);
	if (hoff == (caddr_t)0) {
		INCSTAT(cns_badaddr);
		clnp_discard(m, GEN_INCOMPLETE);
D 3
		return;
E 3
I 3
D 4
		return 0;
E 4
I 4
		return;
E 4
E 3
	}

	IFDEBUG(D_INPUT)
		printf("clnp_input: from %s", clnp_iso_addrp(&src));
		printf(" to %s\n", clnp_iso_addrp(&dst));
	ENDDEBUG

	/*
	 *	extract the segmentation information, if it is present.
	 *	drop packet on failure
	 */
D 4
	if ((clnp->cnf_type != CLNP_ER) && (clnp->cnf_seg_ok)) {
E 4
I 4
	if (((clnp->cnf_type & CNF_TYPE) != CLNP_ER) &&
		(clnp->cnf_type & CNF_SEG_OK)) {
E 4
		if (hoff + sizeof(struct clnp_segment) > hend) {
			INCSTAT(cns_noseg);
			clnp_discard(m, GEN_INCOMPLETE);
D 3
			return;
E 3
I 3
D 4
			return 0;
E 4
I 4
			return;
E 4
E 3
		} else {
			(void) bcopy(hoff, (caddr_t)&seg_part, sizeof(struct clnp_segment));
			/* make sure segmentation fields are in host order */
			seg_part.cng_id = ntohs(seg_part.cng_id);
			seg_part.cng_off = ntohs(seg_part.cng_off);
			seg_part.cng_tot_len = ntohs(seg_part.cng_tot_len);
			seg_off = hoff - (caddr_t)clnp;
			hoff += sizeof(struct clnp_segment);
		}
	}

	/*
	 *	process options if present. If clnp_opt_sanity returns
	 *	false (indicating an error was found in the options) or
	 *	an unsupported option was found
	 *	then drop packet and emit an ER.
	 */
	if (hoff < hend) {
		int		errcode;

		oidxp = &oidx;
		errcode = clnp_opt_sanity(m, hoff, hend-hoff, oidxp);

		/* we do not support security */
		if ((errcode == 0) && (oidxp->cni_securep))
			errcode = DISC_UNSUPPSECURE;

		/* the er option is valid with ER pdus only */
		if ((errcode == 0) && (oidxp->cni_er_reason != ER_INVALREAS) && 
D 4
			(clnp->cnf_type != CLNP_ER))
E 4
I 4
			((clnp->cnf_type & CNF_TYPE) != CLNP_ER))
E 4
			errcode = DISC_UNSUPPOPT;

I 3
#ifdef	DECBIT
		/* check if the congestion experienced bit is set */
		if (oidxp->cni_qos_formatp) {
			caddr_t	qosp = CLNP_OFFTOOPT(m, oidxp->cni_qos_formatp);
			u_char	qos = *qosp;

			need_afrin = ((qos & (CLNPOVAL_GLOBAL|CLNPOVAL_CONGESTED)) ==
				(CLNPOVAL_GLOBAL|CLNPOVAL_CONGESTED));
			if (need_afrin)
				INCSTAT(cns_congest_rcvd);
		}
D 16
#endif	DECBIT
E 16
I 16
#endif	/* DECBIT */
E 16

E 3
		if (errcode != 0) {
			clnp_discard(m, (char)errcode);
			IFDEBUG(D_INPUT)
				printf("clnp_input: dropped (err x%x) due to bad options\n",
					errcode);
			ENDDEBUG
D 3
			return;
E 3
I 3
D 4
			return 0;
E 4
I 4
			return;
E 4
E 3
		}
	}
	
	/*
	 *	check if this packet is for us. if not, then forward
	 */
	if (clnp_ours(&dst) == 0) {
		IFDEBUG(D_INPUT)
			printf("clnp_input: forwarding packet not for us\n");
		ENDDEBUG
 		clnp_forward(m, seg_len, &dst, oidxp, seg_off, shp);
D 3
		return;
E 3
I 3
D 4
		return 0;
E 4
I 4
		return;
E 4
E 3
	}

	/*
	 *	ESIS Configuration Response Function
	 *
	 *	If the packet received was sent to the multicast address
	 *	all end systems, then send an esh to the source
	 */
D 4
	if ((IS_MULTICAST(shp->snh_dhost)) && (iso_systype == SNPA_ES)) {
E 4
I 4
	if ((shp->snh_flags & M_MCAST) && (iso_systype == SNPA_ES)) {
E 4
		extern short esis_holding_time;

		esis_shoutput(shp->snh_ifp, ESIS_ESH, esis_holding_time,
D 12
			shp->snh_shost, 6);
E 12
I 12
			shp->snh_shost, 6, &dst);
E 12
	}

	/*
	 *	If this is a fragment, then try to reassemble it. If clnp_reass
	 *	returns non NULL, the packet has been reassembled, and should
	 *	be give to TP. Otherwise the fragment has been delt with
	 *	by the reassembly code (either stored or deleted). In either case
	 *	we should have nothing more to do with it.
	 */
D 4
	if ((clnp->cnf_type != CLNP_ER) && (clnp->cnf_seg_ok) &&
E 4
I 4
	if (((clnp->cnf_type & CNF_TYPE) != CLNP_ER) &&
		(clnp->cnf_type & CNF_SEG_OK) &&
E 4
		(seg_len != seg_part.cng_tot_len)) {
		struct mbuf	*m0;

		if ((m0 = clnp_reass(m, &src, &dst, &seg_part)) != NULL) {
			m = m0;
			clnp = mtod(m, struct clnp_fixed *);
I 7
			INCSTAT(cns_reassembled);
E 7
		} else {
D 3
			return;
E 3
I 3
D 4
			return 0;
E 4
I 4
			return;
E 4
E 3
		}
	}
	
	/*
	 *	give the packet to the higher layer
D 3
	 *	TODO: how do we tell TP that congestion bit is on in QOS option?
E 3
	 *
	 *	Note: the total length of packet
	 *	is the total length field of the segmentation part,
	 *	or, if absent, the segment length field of the
	 *	header.
	 */
I 7
	INCSTAT(cns_delivered);
E 7
D 4
	switch (clnp->cnf_type) {
E 4
I 4
	switch (clnp->cnf_type & CNF_TYPE) {
E 4
	case CLNP_ER:
		/*
		 *	This ER must have the er option.
		 *	If the option is not present, discard datagram.
		 */
		if (oidxp == NULL || oidxp->cni_er_reason == ER_INVALREAS) {
			clnp_discard(m, GEN_HDRSYNTAX);
		} else {
			clnp_er_input(m, &src, oidxp->cni_er_reason);
		}
		break;

	case CLNP_DT:
I 3
D 10
 		if (need_afrin) {
 			/* NOTE: do this before TP gets the packet so tp ack can use info*/
 			IFDEBUG(D_INPUT)
 				printf("clnp_input: Calling tpclnp_ctlinput(%s)\n",
 					clnp_iso_addrp(&src));
 			ENDDEBUG
 			tpclnp_ctlinput1(PRC_QUENCH2, &src);
 		}
E 10
E 3
D 9
		(*isosw[clnp_protox[ISOPROTO_TP]].pr_input)(m, &src, &dst,
E 9
I 9
		(*isosw[clnp_protox[ISOPROTO_TP]].pr_input)(m, &source, &target,
E 9
D 10
			clnp->cnf_hdr_len);
E 10
I 10
			clnp->cnf_hdr_len, need_afrin);
E 10
		break;

 	case CLNP_RAW:
	case CLNP_ECR:
		IFDEBUG(D_INPUT)
			printf("clnp_input: raw input of %d bytes\n",
D 4
				clnp->cnf_seg_ok ? seg_part.cng_tot_len : seg_len);
E 4
I 4
				clnp->cnf_type & CNF_SEG_OK ? seg_part.cng_tot_len : seg_len);
E 4
		ENDDEBUG
D 11
		(*isosw[clnp_protox[ISOPROTO_RAW]].pr_input)(m, &src, &dst,
E 11
I 11
		(*isosw[clnp_protox[ISOPROTO_RAW]].pr_input)(m, &source, &target,
E 11
					clnp->cnf_hdr_len);
		break;

	case CLNP_EC:
		IFDEBUG(D_INPUT)
			printf("clnp_input: echoing packet\n");
		ENDDEBUG
D 14
		/*
		 *	Switch the source and destination address,
		 */
		hoff = (caddr_t)clnp + sizeof(struct clnp_fixed);
D 4
		CLNP_INSERT_ADDR(hoff, &src);
		CLNP_INSERT_ADDR(hoff, &dst);
		clnp->cnf_type = CLNP_ECR;
E 4
I 4
		CLNP_INSERT_ADDR(hoff, src);
		CLNP_INSERT_ADDR(hoff, dst);
		clnp->cnf_type &= ~CNF_TYPE;
		clnp->cnf_type |= CLNP_ECR;
E 4

		/*
		 *	Forward back to sender
		 */
D 4
 		clnp_forward(m, clnp->cnf_seg_ok ? seg_part.cng_tot_len : seg_len,
E 4
I 4
D 8
 		clnp_forward(m, (int)(clnp->cnf_type & CNF_SEG_OK?seg_part.cng_tot_len : seg_len),
E 4
			&src, oidxp, seg_off, shp);
E 8
I 8
		clnp_forward(m, (int)
			(clnp->cnf_type & CNF_SEG_OK ? seg_part.cng_tot_len : seg_len),
			&src, oidxp, seg_off, 0);
E 14
I 14
		(void)clnp_echoreply(m,
			(clnp->cnf_type & CNF_SEG_OK ? (int)seg_part.cng_tot_len : seg_len),
			&source, &target, oidxp);
E 14
E 8
		break;

	default:
D 4
 		printf("clnp_input: unknown clnp pkt type %d\n", clnp->cnf_type);
E 4
I 4
 		printf("clnp_input: unknown clnp pkt type %d\n",
			clnp->cnf_type & CNF_TYPE);
I 7
		clnp_stat.cns_delivered--;
		clnp_stat.cns_noproto++;
E 7
E 4
		clnp_discard(m, GEN_HDRSYNTAX);
 		break;
	}
}
D 3

int clnp_ctlinput()
{
}

E 3
D 16
#endif ISO
E 16
I 16
#endif /* ISO */
E 16
E 1
