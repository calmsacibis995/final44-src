h13046
s 00002/00002/00831
d D 8.1 93/06/10 23:18:26 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00830
d D 7.15 93/06/04 17:01:39 sklower 15 14
c fix #endif something to #endif /* something */
e
s 00016/00016/00817
d D 7.14 92/10/11 12:21:34 bostic 14 13
c make kernel includes standard
e
s 00001/00000/00832
d D 7.13 92/09/21 19:06:01 mckusick 13 12
c need to include systm.h to get min and max
e
s 00009/00005/00823
d D 7.12 91/05/06 18:58:48 bostic 12 11
c new copyright; att/bsd/shared
e
s 00001/00001/00827
d D 7.11 91/04/26 14:50:13 sklower 11 10
c make fragsize reflect mtu found in route to dest
e
s 00001/00001/00827
d D 7.10 91/03/20 18:55:47 sklower 10 9
c fix bug reported by swise@ibm.com
e
s 00019/00018/00809
d D 7.9 90/06/04 16:46:13 sklower 9 8
c Fix bugs reported in fragmentation and reassembly reported by D. Katz
e
s 00010/00008/00817
d D 7.8 90/04/05 11:15:42 sklower 8 7
c if_output now called with pointer to rtentry.
e
s 00037/00030/00788
d D 7.7 89/09/26 23:57:58 sklower 7 6
c Fixes from Dave Katz at um
e
s 00004/00005/00814
d D 7.6 89/09/22 00:15:22 sklower 6 5
c make changes for SNMP
e
s 00001/00000/00818
d D 7.5 89/08/29 13:43:49 sklower 5 4
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00009/00009/00809
d D 7.4 89/04/25 17:19:27 mckusick 4 3
c ../h => (implicitly) ../sys
e
s 00020/00021/00798
d D 7.3 89/04/22 11:53:18 sklower 3 2
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00042/00010/00777
d D 7.2 89/02/14 18:24:12 sklower 2 1
c wisconsin fixes
e
s 00787/00000/00000
d D 7.1 88/12/14 15:29:23 sklower 1 0
c date and time created 88/12/14 15:29:23 by sklower
e
u
U
t
T
I 12
/*-
D 16
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 12
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
D 2
/* $Header: clnp_frag.c,v 4.2 88/06/29 14:58:40 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_frag.c,v $ */
E 2
I 2
/* $Header: /var/src/sys/netiso/RCS/clnp_frag.c,v 5.1 89/02/09 16:20:26 hagens Exp $ */
/* $Source: /var/src/sys/netiso/RCS/clnp_frag.c,v $ */
I 5
D 12
/*	%W% (Berkeley) %G% */
E 5
E 2

#ifndef lint
D 2
static char *rcsid = "$Header: clnp_frag.c,v 4.2 88/06/29 14:58:40 hagens Exp $";
E 2
I 2
static char *rcsid = "$Header: /var/src/sys/netiso/RCS/clnp_frag.c,v 5.1 89/02/09 16:20:26 hagens Exp $";
E 2
#endif lint
E 12

D 6
#ifdef ISO

D 4
#include "../h/types.h"
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
E 4
I 4
#include "types.h"
E 6
D 14
#include "param.h"
I 13
#include "systm.h"
E 13
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
E 14
I 14
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 14
E 4

D 14
#include "../net/if.h"
#include "../net/route.h"
E 14
I 14
#include <net/if.h>
#include <net/route.h>
E 14

D 3
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
E 3
I 3
D 14
#include "iso.h"
#include "iso_var.h"
#include "clnp.h"
#include "clnp_stat.h"
#include "argo_debug.h"
E 14
I 14
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 14
E 3

/* all fragments are hung off this list */
struct clnp_fragl	*clnp_frags = NULL;

struct mbuf	*clnp_comp_pdu();

D 3
#ifdef	TROLL
float troll_random();
static int troll_cnt = 0;
#endif	TROLL
E 3

D 3

E 3
/*
 * FUNCTION:		clnp_fragment
 *
 * PURPOSE:			Fragment a datagram, and send the itty bitty pieces
 *					out over an interface.
 *
 * RETURNS:			success - 0
 *					failure - unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			If there is an error sending the packet, clnp_discard
 *					is called to discard the packet and send an ER. If
 *					clnp_fragment was called from clnp_output, then
 *					we generated the packet, and should not send an 
 *					ER -- clnp_emit_er will check for this. Otherwise,
 *					the packet was fragmented during forwarding. In this
 *					case, we ought to send an ER back.
 */
D 8
clnp_fragment(ifp, m, first_hop, total_len, segoff, flags)
E 8
I 8
clnp_fragment(ifp, m, first_hop, total_len, segoff, flags, rt)
E 8
struct ifnet	*ifp;		/* ptr to outgoing interface */
struct mbuf		*m;			/* ptr to packet */
struct sockaddr	*first_hop;	/* ptr to first hop */
int				total_len;	/* length of datagram */
int				segoff;		/* offset of segpart in hdr */
int				flags;		/* flags passed to clnp_output */
I 8
struct rtentry *rt;			/* route if direct ether */
E 8
{
D 7
	struct clnp_fixed	*clnp;		/* ptr to fixed part of header */
E 7
I 7
	struct clnp_fixed		*clnp = mtod(m, struct clnp_fixed *);
	int						hdr_len = (int)clnp->cnf_hdr_len;
D 11
	int						frag_size = (ifp->if_mtu - hdr_len) & ~7;
E 11
I 11
	int						frag_size = (SN_MTU(ifp, rt) - hdr_len) & ~7;
E 11
E 7

D 7
	clnp = mtod(m, struct clnp_fixed *);
E 7
I 7
	total_len -= hdr_len;
	if ((clnp->cnf_type & CNF_SEG_OK) &&
		(total_len >= 8) &&
		(frag_size > 8 || (frag_size == 8 && !(total_len & 7)))) {
E 7

D 3
	if (clnp->cnf_seg_ok) {
E 3
I 3
D 7
	if (clnp->cnf_type & CNF_SEG_OK) {
E 7
E 3
		struct mbuf			*hdr = NULL;		/* save copy of clnp hdr */
		struct mbuf			*frag_hdr = NULL;
		struct mbuf			*frag_data = NULL;
D 9
		struct clnp_segment	seg_part, tmp_seg;	/* segmentation header */
		extern int 			clnp_id;			/* id of datagram */
I 7
		int					frag_size;
E 9
I 9
		struct clnp_segment	seg_part;			/* segmentation header */
D 10
		int					frag_size, frag_base;
E 10
I 10
		int					frag_base;
E 10
E 9
E 7
		int					error = 0;

D 6
		INCSTAT(cns_frag);
E 6
I 6
D 7
		INCSTAT(cns_fragmented);
E 7
E 6

I 7
		INCSTAT(cns_fragmented);
E 7
D 9
		seg_part.cng_id = clnp_id++;
		seg_part.cng_off = 0;
D 7
		seg_part.cng_tot_len = total_len;

E 7
I 7
		seg_part.cng_tot_len = total_len + hdr_len;
E 9
I 9
        (void) bcopy(segoff + mtod(m, caddr_t), (caddr_t)&seg_part,
            sizeof(seg_part));
		frag_base = ntohs(seg_part.cng_off);
E 9
E 7
		/*
		 *	Duplicate header, and remove from packet
		 */
D 3
		if ((hdr = m_copy(m, 0, clnp->cnf_hdr_len)) == NULL) {
E 3
I 3
D 7
		if ((hdr = m_copy(m, 0, (int)clnp->cnf_hdr_len)) == NULL) {
E 7
I 7
		if ((hdr = m_copy(m, 0, hdr_len)) == NULL) {
E 7
E 3
			clnp_discard(m, GEN_CONGEST);
			return(ENOBUFS);
		}
D 3
		m_adj(m, clnp->cnf_hdr_len);
E 3
I 3
D 7
		m_adj(m, (int)clnp->cnf_hdr_len);
E 3
		total_len -= clnp->cnf_hdr_len;
		
E 7
I 7
		m_adj(m, hdr_len);

E 7
		while (total_len > 0) {
D 7
			int		frag_size;
			int		last_frag = 0;		/* true if this is the last fragment */
E 7
I 7
			int		remaining, last_frag;
E 7
I 2

			IFDEBUG(D_FRAG)
				struct mbuf *mdump = frag_hdr;
				int tot_mlen = 0;
				printf("clnp_fragment: total_len %d:\n", total_len);
				while (mdump != NULL) {
					printf("\tmbuf x%x, m_len %d\n", 
						mdump, mdump->m_len);
					tot_mlen += mdump->m_len;
					mdump = mdump->m_next;
				}
				printf("clnp_fragment: sum of mbuf chain %d:\n", tot_mlen);
			ENDDEBUG
E 2
			
D 7
			frag_size = min(total_len, ifp->if_mtu - clnp->cnf_hdr_len);

			/*
			 *	For some stupid reason, fragments must be at least 8 bytes
			 *	in length. If this fragment will cause the last one to 
			 *	be less than 8 bytes, shorten this fragment a bit.
			 */
			if (((total_len - frag_size) > 0) && ((total_len - frag_size) < 8))
				frag_size -= (8 - (total_len - frag_size));
E 7
I 7
			frag_size = min(total_len, frag_size);
			if ((remaining = total_len - frag_size) == 0)
				last_frag = 1;
			else {
				/*
				 *  If this fragment will cause the last one to 
				 *	be less than 8 bytes, shorten this fragment a bit.
				 *  The obscure test on frag_size above ensures that
				 *  frag_size will be positive.
				 */
				last_frag = 0;
				if (remaining < 8)
						frag_size -= 8;
			}
E 7
			
D 7
			last_frag = ((total_len - frag_size) == 0);
E 7

			IFDEBUG(D_FRAG)
				printf("clnp_fragment: seg off %d, size %d, remaining %d\n", 
D 9
					seg_part.cng_off, frag_size, total_len-frag_size);
E 9
I 9
					ntohs(seg_part.cng_off), frag_size, total_len-frag_size);
E 9
				if (last_frag)
					printf("clnp_fragment: last fragment\n");
			ENDDEBUG

			if (last_frag) {
				/* 
				 *	this is the last fragment; we don't need to get any other
				 *	mbufs.
				 */
				frag_hdr = hdr;
				frag_data = m;
			} else {
				/* duplicate header and data mbufs */
D 3
				if ((frag_hdr = m_copy(hdr, 0, M_COPYALL)) == NULL) {
E 3
I 3
				if ((frag_hdr = m_copy(hdr, 0, (int)M_COPYALL)) == NULL) {
E 3
D 7
					clnp_discard(m, GEN_CONGEST);
					m_freem(hdr);
E 7
I 7
					clnp_discard(hdr, GEN_CONGEST);
					m_freem(m);
E 7
					return(ENOBUFS);
				}
				if ((frag_data = m_copy(m, 0, frag_size)) == NULL) {
D 7
					clnp_discard(m, GEN_CONGEST);
					m_freem(hdr);
E 7
I 7
					clnp_discard(hdr, GEN_CONGEST);
					m_freem(m);
E 7
					m_freem(frag_hdr);
					return(ENOBUFS);
				}
I 6
				INCSTAT(cns_fragments);
E 6
			}
			clnp = mtod(frag_hdr, struct clnp_fixed *);

			if (!last_frag)
D 3
				clnp->cnf_more_segs = 1;
E 3
I 3
				clnp->cnf_type |= CNF_MORE_SEGS;
E 3
			
			/* link together */
			m_cat(frag_hdr, frag_data);

D 9
			/* make sure segmentation fields are in network order */
			tmp_seg.cng_id = htons(seg_part.cng_id);
			tmp_seg.cng_off = htons(seg_part.cng_off);
			tmp_seg.cng_tot_len = htons(seg_part.cng_tot_len);

			/* insert segmentation part */
			bcopy((caddr_t)&tmp_seg, mtod(frag_hdr, caddr_t) + segoff,
E 9
I 9
			/* insert segmentation part; updated below */
			bcopy((caddr_t)&seg_part, mtod(frag_hdr, caddr_t) + segoff,
E 9
				sizeof(struct clnp_segment));

			{
D 7
				int	derived_len = clnp->cnf_hdr_len + frag_size;
E 7
I 7
				int	derived_len = hdr_len + frag_size;
E 7
				HTOC(clnp->cnf_seglen_msb, clnp->cnf_seglen_lsb, derived_len);
I 3
				if ((frag_hdr->m_flags & M_PKTHDR) == 0)
					panic("clnp_frag:lost header");
				frag_hdr->m_pkthdr.len = derived_len;
E 3
			}
			/* compute clnp checksum (on header only) */
			if (flags & CLNP_NO_CKSUM) {
				HTOC(clnp->cnf_cksum_msb, clnp->cnf_cksum_lsb, 0);
			} else {
D 7
				iso_gen_csum(frag_hdr, CLNP_CKSUM_OFF, (int)clnp->cnf_hdr_len);
E 7
I 7
				iso_gen_csum(frag_hdr, CLNP_CKSUM_OFF, hdr_len);
E 7
			}

			IFDEBUG(D_DUMPOUT)
				struct mbuf *mdump = frag_hdr;
				printf("clnp_fragment: sending dg:\n");
D 2
/* 				dump_buf(mtod(mdump, caddr_t), mdump->m_len);*/
E 2
				while (mdump != NULL) {
D 2
					printf("mbuf x%x, m_len %d\n", mdump, mdump->m_len);
/*  					dump_buf(mtod(mdump, caddr_t), mdump->m_len);*/
E 2
I 2
					printf("\tmbuf x%x, m_len %d\n", mdump, mdump->m_len);
E 2
					mdump = mdump->m_next;
				}
			ENDDEBUG

#ifdef	TROLL
D 8
			error = troll_output(ifp, frag_hdr, first_hop);
E 8
I 8
			error = troll_output(ifp, frag_hdr, first_hop, rt);
E 8
#else
D 8
			error = (*ifp->if_output)(ifp, frag_hdr, first_hop);
E 8
I 8
			error = (*ifp->if_output)(ifp, frag_hdr, first_hop, rt);
E 8
D 15
#endif	TROLL
E 15
I 15
#endif	/* TROLL */
E 15

			/*
			 *	Tough situation: if the error occured on the last 
			 *	fragment, we can not send an ER, as the if_output
			 *	routine consumed the packet. If the error occured
			 *	on any intermediate packets, we can send an ER
			 *	because we still have the original header in (m).
			 */
			if (error) {
				if (frag_hdr != hdr) {
					/* 
					 *	The error was not on the last fragment. We must
					 *	free hdr and m before returning
					 */
D 7
					clnp_discard(m, GEN_NOREAS);
					m_freem(hdr);
E 7
I 7
					clnp_discard(hdr, GEN_NOREAS);
					m_freem(m);
E 7
				}
				return(error);
			}

			/* bump segment offset, trim data mbuf, and decrement count left */
#ifdef	TROLL
			/*
			 *	Decrement frag_size by some fraction. This will cause the
			 *	next fragment to start 'early', thus duplicating the end
			 *	of the current fragment.  troll.tr_dup_size controls
			 *	the fraction. If positive, it specifies the fraction. If
			 *	negative, a random fraction is used.
			 */
			if ((trollctl.tr_ops & TR_DUPEND) && (!last_frag)) {
				int num_bytes = frag_size;

				if (trollctl.tr_dup_size > 0) 
					num_bytes *= trollctl.tr_dup_size;
				else
					num_bytes *= troll_random();
				frag_size -= num_bytes;
			}
D 15
#endif	TROLL
E 15
I 15
#endif	/* TROLL */
E 15
			total_len -= frag_size;
			if (!last_frag) {
D 9
				seg_part.cng_off += frag_size;
E 9
I 9
				frag_base += frag_size;
				seg_part.cng_off = htons(frag_base);
E 9
				m_adj(m, frag_size);
			}
		}
		return(0);
	} else {
I 7
	cantfrag:
E 7
I 6
		INCSTAT(cns_cantfrag);
E 6
		clnp_discard(m, GEN_SEGNEEDED);
		return(EMSGSIZE);
	}
}

/*
 * FUNCTION:		clnp_reass
 *
 * PURPOSE:			Attempt to reassemble a clnp packet given the current
 *					fragment. If reassembly succeeds (all the fragments
 *					are present), then return a pointer to an mbuf chain
 *					containing the reassembled packet. This packet will
 *					appear in the mbufs as if it had just arrived in
 *					one piece. 
 *
 *					If reassembly fails, then save this fragment and
 *					return 0.
 *
 * RETURNS:			Ptr to assembled packet, or 0
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 *		clnp_slowtimo can not affect this code because clnpintr, and thus
 *		this code, is called at a higher priority than clnp_slowtimo.
 */
struct mbuf *
clnp_reass(m, src, dst, seg)
struct mbuf 		*m;		/* new fragment */
struct iso_addr		*src;	/* src of new fragment */
struct iso_addr		*dst; 	/* dst of new fragment */
struct clnp_segment	*seg;	/* segment part of fragment header */
{
	register struct clnp_fragl		*cfh;

	/* look for other fragments of this datagram */
	for (cfh = clnp_frags; cfh != NULL; cfh = cfh->cfl_next) {
D 9
		if (iso_addrmatch1(src, &cfh->cfl_src) && 
			iso_addrmatch1(dst, &cfh->cfl_dst) && seg->cng_id == cfh->cfl_id) {
E 9
I 9
		if (seg->cng_id == cfh->cfl_id &&
		    iso_addrmatch1(src, &cfh->cfl_src) && 
			iso_addrmatch1(dst, &cfh->cfl_dst)) {
E 9
			IFDEBUG(D_REASS)
				printf("clnp_reass: found packet\n");
			ENDDEBUG
			/*
			 *	There are other fragments here already. Lets see if
			 *	this fragment is of any help
			 */
			clnp_insert_frag(cfh, m, seg);
D 9
			return (clnp_comp_pdu(cfh));
E 9
I 9
			if (m = clnp_comp_pdu(cfh)) {
				register struct clnp_fixed *clnp = mtod(m, struct clnp_fixed *);
				HTOC(clnp->cnf_seglen_msb, clnp->cnf_seglen_lsb,
					 seg->cng_tot_len);
			}
			return (m);
E 9
		}
	}

	IFDEBUG(D_REASS)
		printf("clnp_reass: new packet!\n");
	ENDDEBUG

	/*
	 *	This is the first fragment. If src is not consuming too many
	 *	resources, then create a new fragment list and add
	 *	this fragment to the list.
	 */
	/* TODO: don't let one src hog all the reassembly buffers */
	if (!clnp_newpkt(m, src, dst, seg) /* || this src is a hog */) {
I 6
		INCSTAT(cns_fragdropped);
E 6
		clnp_discard(m, GEN_CONGEST);
	}

	return(NULL);
}

/*
 * FUNCTION:		clnp_newpkt
 *
 * PURPOSE:			Create the necessary structures to handle a new
 *					fragmented clnp packet.
 *
 * RETURNS:			non-zero if it succeeds, zero if fails.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Failure is only due to insufficient resources.
 */
clnp_newpkt(m, src, dst, seg)
struct mbuf 		*m;		/* new fragment */
struct iso_addr		*src;	/* src of new fragment */
struct iso_addr		*dst; 	/* dst of new fragment */
struct clnp_segment	*seg;	/* segment part of fragment header */
{
	register struct clnp_fragl		*cfh;
	register struct clnp_fixed		*clnp;
	struct mbuf 					*m0;
	
	clnp = mtod(m, struct clnp_fixed *);

	/* 
	 *	Allocate new clnp fragl structure to act as header of all fragments
	 *	for this datagram.
	 */
	MGET(m0, M_DONTWAIT, MT_FTABLE);
	if (m0 == NULL) {
		return (0);
	}
	cfh = mtod(m0, struct clnp_fragl *);

	/* 
	 *	Duplicate the header of this fragment, and save in cfh.
	 *	Free m0 and return if m_copy does not succeed.
	 */
D 3
	if ((cfh->cfl_orighdr = m_copy(m, 0, clnp->cnf_hdr_len)) == NULL) {
E 3
I 3
	if ((cfh->cfl_orighdr = m_copy(m, 0, (int)clnp->cnf_hdr_len)) == NULL) {
E 3
		m_freem(m0);
		return (0);
	}
	
	/* Fill in rest of fragl structure */
	bcopy((caddr_t)src, (caddr_t)&cfh->cfl_src, sizeof(struct iso_addr));
	bcopy((caddr_t)dst, (caddr_t)&cfh->cfl_dst, sizeof(struct iso_addr));
	cfh->cfl_id = seg->cng_id;
	cfh->cfl_ttl = clnp->cnf_ttl;
	cfh->cfl_last = (seg->cng_tot_len - clnp->cnf_hdr_len) - 1;
	cfh->cfl_frags = NULL;
	cfh->cfl_next = NULL;

	/* Insert into list of packets */
	cfh->cfl_next = clnp_frags;
	clnp_frags = cfh;

	/* Insert this fragment into list headed by cfh */
	clnp_insert_frag(cfh, m, seg);
	return(1);
}

/*
 * FUNCTION:		clnp_insert_frag
 *
 * PURPOSE:			Insert fragment into list headed by 'cf'.
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			This is the 'guts' of the reassembly algorithm.
 *					Each fragment in this list contains a clnp_frag
 *					structure followed by the data of the fragment.
 *					The clnp_frag structure actually lies on top of
 *					part of the old clnp header.
 */
clnp_insert_frag(cfh, m, seg)
struct clnp_fragl	*cfh;	/* header of list of packet fragments */
struct mbuf 		*m;		/* new fragment */
struct clnp_segment	*seg;	/* segment part of fragment header */
{
	register struct clnp_fixed	*clnp;	/* clnp hdr of fragment */
	register struct clnp_frag	*cf;	/* generic fragment ptr */
	register struct clnp_frag 	*cf_sub = NULL;	/* frag subsequent to new one */
	register struct clnp_frag 	*cf_prev = NULL; /* frag previous to new one */
	u_short						first;	/* offset of first byte of initial pdu*/
	u_short						last;	/* offset of last byte of initial pdu */
	u_short						fraglen;/* length of fragment */
	
	clnp = mtod(m, struct clnp_fixed *);
	first = seg->cng_off;
	CTOH(clnp->cnf_seglen_msb, clnp->cnf_seglen_lsb, fraglen);
	fraglen -= clnp->cnf_hdr_len;
	last = (first + fraglen) - 1;

	IFDEBUG(D_REASS)
		printf("clnp_insert_frag: New fragment: [%d ... %d], len %d\n",
			first, last, fraglen);
		printf("clnp_insert_frag: current fragments:\n");
		for (cf = cfh->cfl_frags; cf != NULL; cf = cf->cfr_next) {
			printf("\tcf x%x: [%d ... %d]\n", cf, cf->cfr_first, cf->cfr_last);
		}
	ENDDEBUG

	if (cfh->cfl_frags != NULL) {
		/*
		 *	Find fragment which begins after the new one
		 */
		for (cf = cfh->cfl_frags; cf != NULL; cf_prev = cf, cf = cf->cfr_next) {
			if (cf->cfr_first > first) {
				cf_sub = cf;
				break;
			}
		}

		IFDEBUG(D_REASS)
			printf("clnp_insert_frag: Previous frag is ");
			if (cf_prev == NULL)
				printf("NULL\n");
			else 
				printf("[%d ... %d]\n", cf_prev->cfr_first, cf_prev->cfr_last);
			printf("clnp_insert_frag: Subsequent frag is ");
			if (cf_sub == NULL)
				printf("NULL\n");
			else 
				printf("[%d ... %d]\n", cf_sub->cfr_first, cf_sub->cfr_last);
		ENDDEBUG

		/*
		 *	If there is a fragment before the new one, check if it
		 *	overlaps the new one. If so, then trim the end of the
		 *	previous one.
		 */
		if (cf_prev != NULL) {
			if (cf_prev->cfr_last > first) {
				u_short overlap = cf_prev->cfr_last - first;

				IFDEBUG(D_REASS)
					printf("clnp_insert_frag: previous overlaps by %d\n",
						overlap);
				ENDDEBUG

				if (overlap > fraglen) {
					/*
					 *	The new fragment is entirely contained in the
					 *	preceeding one. We can punt on the new frag
					 *	completely.
					 */
					m_freem(m);
					return;
				} else {
					/* Trim data off of end of previous fragment */
					/* inc overlap to prevent duplication of last byte */
					overlap++;
D 3
					m_adj(cf_prev->cfr_data, -overlap);
E 3
I 3
					m_adj(cf_prev->cfr_data, -(int)overlap);
E 3
					cf_prev->cfr_last -= overlap;
				}
			}
		}

		/*
		 *	For all fragments past the new one, check if any data on
		 *	the new one overlaps data on existing fragments. If so,
		 *	then trim the extra data off the end of the new one.
		 */
		for (cf = cf_sub; cf != NULL; cf = cf->cfr_next) {
			if (cf->cfr_first < last) {
				u_short overlap = last - cf->cfr_first;

				IFDEBUG(D_REASS)
					printf("clnp_insert_frag: subsequent overlaps by %d\n",
						overlap);
				ENDDEBUG

				if (overlap > fraglen) {
					/*
					 *	The new fragment is entirely contained in the
					 *	succeeding one. This should not happen, because
					 *	early on in this code we scanned for the fragment
					 *	which started after the new one!
					 */
					m_freem(m);
					printf("clnp_insert_frag: internal error!\n");
					return;
				} else {
					/* Trim data off of end of new fragment */
					/* inc overlap to prevent duplication of last byte */
					overlap++;
D 3
					m_adj(m, -overlap);
E 3
I 3
					m_adj(m, -(int)overlap);
E 3
					last -= overlap;
				}
			}
		}
	}

	/*
	 *	Insert the new fragment beween cf_prev and cf_sub
	 *
	 *	Note: the clnp hdr is still in the mbuf. 
	 *	If the data of the mbuf is not word aligned, shave off enough
	 *	so that it is. Then, cast the clnp_frag structure on top
	 *	of the clnp header. 
	 *	The clnp_hdr will not be used again (as we already have
	 *	saved a copy of it).
	 *
	 *	Save in cfr_bytes the number of bytes to shave off to get to
	 *	the data of the packet. This is used when we coalesce fragments;
	 *	the clnp_frag structure must be removed before joining mbufs.
	 */
	{
		int	pad;
		u_int	bytes;

		/* determine if header is not word aligned */
		pad = (int)clnp % 4;
		if (pad < 0)
			pad = -pad;

		/* bytes is number of bytes left in front of data */
		bytes = clnp->cnf_hdr_len - pad;

I 2
		IFDEBUG(D_REASS)
			printf("clnp_insert_frag: clnp x%x requires %d alignment\n",
				clnp, pad);
		ENDDEBUG

E 2
		/* make it word aligned if necessary */
		if (pad)
			m_adj(m, pad);

		cf = mtod(m, struct clnp_frag *);
		cf->cfr_bytes = bytes;
I 2

		IFDEBUG(D_REASS)
			printf("clnp_insert_frag: cf now x%x, cfr_bytes %d\n", cf,
				cf->cfr_bytes);
		ENDDEBUG
E 2
	}
	cf->cfr_first = first;
	cf->cfr_last = last;


	/*
	 *	The data is the mbuf itself, although we must remember that the
	 *	first few bytes are actually a clnp_frag structure
	 */
	cf->cfr_data = m;

	/* link into place */
	cf->cfr_next = cf_sub;
	if (cf_prev == NULL)
		cfh->cfl_frags = cf;
	else
		cf_prev->cfr_next = cf;
}

/*
 * FUNCTION:		clnp_comp_pdu
 *
 * PURPOSE:			Scan the list of fragments headed by cfh. Merge
 *					any contigious fragments into one. If, after
 *					traversing all the fragments, it is determined that
 *					the packet is complete, then return a pointer to
 *					the packet (with header prepended). Otherwise,
 *					return NULL.
 *
 * RETURNS:			NULL, or a pointer to the assembled pdu in an mbuf chain.
 *
 * SIDE EFFECTS:	Will colapse contigious fragments into one.
 *
 * NOTES:			This code assumes that there are no overlaps of
 *					fragment pdus.
 */
struct mbuf *
clnp_comp_pdu(cfh)
struct clnp_fragl	*cfh;		/* fragment header */
{
	register struct clnp_frag	*cf = cfh->cfl_frags;

	while (cf->cfr_next != NULL) {
		register struct clnp_frag	*cf_next = cf->cfr_next;

		IFDEBUG(D_REASS)
			printf("clnp_comp_pdu: comparing: [%d ... %d] to [%d ... %d]\n",
				cf->cfr_first, cf->cfr_last, cf_next->cfr_first, 
				cf_next->cfr_last);
		ENDDEBUG

		if (cf->cfr_last == (cf_next->cfr_first - 1)) {
			/*
			 *	Merge fragment cf and cf_next
			 *
			 *	- update cf header
			 *	- trim clnp_frag structure off of cf_next
			 *	- append cf_next to cf
			 */
			struct clnp_frag	cf_next_hdr;
			struct clnp_frag	*next_frag;

			cf_next_hdr = *cf_next;
			next_frag = cf_next->cfr_next;

			IFDEBUG(D_REASS)
				struct mbuf *mdump;
I 2
				int l;
E 2
				printf("clnp_comp_pdu: merging fragments\n");
D 2
				printf("clnp_comp_pdu: 1st: [%d ... %d]\n", cf->cfr_first, 
					cf->cfr_last);
E 2
I 2
				printf("clnp_comp_pdu: 1st: [%d ... %d] (bytes %d)\n", 
					cf->cfr_first, cf->cfr_last, cf->cfr_bytes);
E 2
				mdump = cf->cfr_data;
I 2
				l = 0;
E 2
				while (mdump != NULL) {
					printf("\tmbuf x%x, m_len %d\n", mdump, mdump->m_len);
I 2
					l += mdump->m_len;
E 2
					mdump = mdump->m_next;
				}
D 2
				printf("clnp_comp_pdu: 2nd: [%d ... %d]\n", cf_next->cfr_first, 
					cf_next->cfr_last);
E 2
I 2
				printf("\ttotal len: %d\n", l);
				printf("clnp_comp_pdu: 2nd: [%d ... %d] (bytes %d)\n", 
					cf_next->cfr_first, cf_next->cfr_last, cf_next->cfr_bytes);
E 2
				mdump = cf_next->cfr_data;
I 2
				l = 0;
E 2
				while (mdump != NULL) {
					printf("\tmbuf x%x, m_len %d\n", mdump, mdump->m_len);
I 2
					l += mdump->m_len;
E 2
					mdump = mdump->m_next;
				}
I 2
				printf("\ttotal len: %d\n", l);
E 2
			ENDDEBUG

			cf->cfr_last = cf_next->cfr_last;
			/*
			 *	After this m_adj, the cf_next ptr is useless because we
			 *	have adjusted the clnp_frag structure away...
			 */
I 2
			IFDEBUG(D_REASS)
				printf("clnp_comp_pdu: shaving off %d bytes\n", 
					cf_next_hdr.cfr_bytes);
			ENDDEBUG
E 2
D 3
			m_adj(cf_next_hdr.cfr_data, cf_next_hdr.cfr_bytes);
E 3
I 3
			m_adj(cf_next_hdr.cfr_data, (int)cf_next_hdr.cfr_bytes);
E 3
			m_cat(cf->cfr_data, cf_next_hdr.cfr_data);
			cf->cfr_next = next_frag;
		} else {
			cf = cf->cfr_next;
		}
	}

	cf = cfh->cfl_frags;

	IFDEBUG(D_REASS)
		struct mbuf *mdump = cf->cfr_data;
		printf("clnp_comp_pdu: first frag now: [%d ... %d]\n", cf->cfr_first,
			cf->cfr_last);
		printf("clnp_comp_pdu: data for frag:\n");
		while (mdump != NULL) {
			printf("mbuf x%x, m_len %d\n", mdump, mdump->m_len);
/* 			dump_buf(mtod(mdump, caddr_t), mdump->m_len);*/
			mdump = mdump->m_next;
		}
	ENDDEBUG

	/* Check if datagram is complete */
	if ((cf->cfr_first == 0) && (cf->cfr_last == cfh->cfl_last)) {
		/*
		 *	We have a complete pdu!
		 *	- Remove the frag header from (only) remaining fragment
		 *		(which is not really a fragment anymore, as the datagram is
		 *		complete).
		 *	- Prepend a clnp header
		 */
		struct mbuf	*data = cf->cfr_data;
		struct mbuf	*hdr = cfh->cfl_orighdr;
		struct clnp_fragl *scan;

		IFDEBUG(D_REASS)
			printf("clnp_comp_pdu: complete pdu!\n");
		ENDDEBUG

D 3
		m_adj(data, cf->cfr_bytes);
E 3
I 3
		m_adj(data, (int)cf->cfr_bytes);
E 3
		m_cat(hdr, data);

		IFDEBUG(D_DUMPIN)
			struct mbuf *mdump = hdr;
			printf("clnp_comp_pdu: pdu is:\n");
			while (mdump != NULL) {
				printf("mbuf x%x, m_len %d\n", mdump, mdump->m_len);
/* 				dump_buf(mtod(mdump, caddr_t), mdump->m_len);*/
				mdump = mdump->m_next;
			}
		ENDDEBUG

		/*
		 *	Remove cfh from the list of fragmented pdus
		 */
		if (clnp_frags == cfh) {
			clnp_frags = cfh->cfl_next;
		} else {
			for (scan = clnp_frags; scan != NULL; scan = scan->cfl_next) {
				if (scan->cfl_next == cfh) {
					scan->cfl_next = cfh->cfl_next;
					break;
				}
			}
		}

		/* free cfh */
		m_freem(dtom(cfh));

		return(hdr);
	}

	return(NULL);
}
#ifdef	TROLL
I 3
static int troll_cnt;
E 3
D 4
#include "../h/time.h"
E 4
I 4
D 14
#include "time.h"
E 14
I 14
#include <sys/time.h>
E 14
E 4
/*
 * FUNCTION:		troll_random
 *
 * PURPOSE:			generate a pseudo-random number between 0 and 1
 *
 * RETURNS:			the random number
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			This is based on the clock.
 */
float troll_random()
{
	extern struct timeval time;
	long	t = time.tv_usec % 100;

	return((float)t / (float) 100);
}

/*
 * FUNCTION:		troll_output
 *
 * PURPOSE:			Do something sneaky with the datagram passed. Possible
 *					operations are:
 *						Duplicate the packet
 *						Drop the packet
 *						Trim some number of bytes from the packet
 *						Munge some byte in the packet
 *
 * RETURNS:			0, or unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			The operation of this procedure is regulated by the
 *					troll control structure (Troll).
 */
D 8
troll_output(ifp, m, dst)
E 8
I 8
troll_output(ifp, m, dst, rt)
E 8
struct ifnet	*ifp;
struct mbuf		*m;
struct sockaddr	*dst;
I 8
struct rtentry *rt;
E 8
{
	int	err = 0;
	troll_cnt++;

	if (trollctl.tr_ops & TR_DUPPKT) {
		/*
		 *	Duplicate every Nth packet
		 *	TODO: random?
		 */
		float	f_freq = troll_cnt * trollctl.tr_dup_freq;
		int		i_freq = troll_cnt * trollctl.tr_dup_freq;
		if (i_freq == f_freq) {
D 3
			struct mbuf *dup = m_copy(m, 0, M_COPYALL);
E 3
I 3
			struct mbuf *dup = m_copy(m, 0, (int)M_COPYALL);
E 3
			if (dup != NULL)
D 8
				err = (*ifp->if_output)(ifp, dup, dst);
E 8
I 8
				err = (*ifp->if_output)(ifp, dup, dst, rt);
E 8
		}
		if (!err)
D 8
			err = (*ifp->if_output)(ifp, m, dst);
E 8
I 8
			err = (*ifp->if_output)(ifp, m, dst, rt);
E 8
		return(err);
	} else if (trollctl.tr_ops & TR_DROPPKT) {
	} else if (trollctl.tr_ops & TR_CHANGE) {
		struct clnp_fixed *clnp = mtod(m, struct clnp_fixed *);
		clnp->cnf_cksum_msb = 0;
D 8
		err = (*ifp->if_output)(ifp, m, dst);
E 8
I 8
		err = (*ifp->if_output)(ifp, m, dst, rt);
E 8
		return(err);
	} else {
D 8
		err = (*ifp->if_output)(ifp, m, dst);
E 8
I 8
		err = (*ifp->if_output)(ifp, m, dst, rt);
E 8
		return(err);
	}
}

D 15
#endif	TROLL
E 15
I 15
#endif	/* TROLL */
E 15
D 6
#endif	ISO
E 6
E 1
