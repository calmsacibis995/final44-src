h59924
s 00002/00002/00630
d D 8.1 93/06/10 23:18:47 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00628
d D 7.17 93/06/04 17:01:55 sklower 17 16
c fix #endif something to #endif /* something */
e
s 00002/00002/00630
d D 7.16 93/02/12 14:54:04 sklower 16 15
c minor fixes from MITRE
e
s 00018/00019/00614
d D 7.15 92/10/11 12:21:39 bostic 15 14
c make kernel includes standard
e
s 00036/00000/00597
d D 7.14 92/02/14 14:16:26 sklower 14 13
c changes proposed by hagens to make CLNP EchoReply work
e
s 00009/00005/00588
d D 7.13 91/05/06 18:58:55 bostic 13 12
c new copyright; att/bsd/shared
e
s 00029/00030/00564
d D 7.12 91/04/26 15:06:02 sklower 12 11
c decsion to fragment now based on route in addition to ifp
e
s 00008/00012/00586
d D 7.11 90/06/20 19:02:26 sklower 11 10
c changed esis to make use of routing table; mostly works;
c checkpoint before UW merge
e
s 00005/00006/00593
d D 7.10 90/06/09 17:39:13 sklower 10 9
c change snpa cache to fold in to routing table; this doesn't work yet;
c but checkpoint anyhow
e
s 00009/00004/00590
d D 7.9 90/06/06 18:03:23 sklower 9 8
c do something about GOSIP v2 proliferations of NSAP's --
c interpret siso_tlen in the if's address, as an nsel length.
e
s 00003/00003/00591
d D 7.8 90/04/05 11:15:46 sklower 8 7
c if_output now called with pointer to rtentry.
e
s 00004/00000/00590
d D 7.7 89/09/22 02:43:36 sklower 7 6
c be more careful about forwarding statistics
e
s 00001/00000/00589
d D 7.6 89/08/29 13:44:03 sklower 6 5
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00012/00007/00577
d D 7.5 89/07/19 23:22:34 sklower 5 4
c fix clnp_route for SO_DONTROUTE to set first_hop correctly.
e
s 00066/00111/00518
d D 7.4 89/04/22 11:53:35 sklower 4 3
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00030/00004/00599
d D 7.3 89/02/14 18:53:03 sklower 3 2
c wisconsin changes
e
s 00002/00002/00601
d D 7.2 89/02/14 18:46:02 sklower 2 1
c minor berkeley change concering struct routes
e
s 00603/00000/00000
d D 7.1 88/12/14 15:29:29 sklower 1 0
c date and time created 88/12/14 15:29:29 by sklower
e
u
U
t
T
I 13
/*-
D 18
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
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
/* $Header: clnp_subr.c,v 4.10 88/09/14 11:31:33 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_subr.c,v $ */
E 3
I 3
/* $Header: /var/src/sys/netiso/RCS/clnp_subr.c,v 5.1 89/02/09 16:20:46 hagens Exp $ */
/* $Source: /var/src/sys/netiso/RCS/clnp_subr.c,v $ */
I 6
D 13
/*	%W% (Berkeley) %G% */
E 6
E 3

#ifndef lint
D 3
static char *rcsid = "$Header: clnp_subr.c,v 4.10 88/09/14 11:31:33 hagens Exp $";
E 3
I 3
static char *rcsid = "$Header: /var/src/sys/netiso/RCS/clnp_subr.c,v 5.1 89/02/09 16:20:46 hagens Exp $";
E 3
#endif lint
E 13

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
#include "../h/time.h"
E 4
I 4
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
E 4

D 15
#include "../net/if.h"
#include "../net/route.h"
I 10
#include "../net/if_dl.h"
E 15
I 15
#include <net/if.h>
#include <net/route.h>
#include <net/if_dl.h>
E 15
E 10

D 4
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
#include "../netiso/iso_snpac.h"
E 4
I 4
D 15
#include "iso.h"
#include "iso_var.h"
#include "iso_pcb.h"
#include "iso_snpac.h"
#include "clnp.h"
#include "clnp_stat.h"
#include "argo_debug.h"
E 15
I 15
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_pcb.h>
#include <netiso/iso_snpac.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 15
E 4

/*
 * FUNCTION:		clnp_data_ck
 *
 * PURPOSE:			Check that the amount of data in the mbuf chain is
 *					at least as much as the clnp header would have us
 *					expect. Trim mbufs if longer than expected, drop
 *					packet if shorter than expected.
 *
 * RETURNS:			success - ptr to mbuf chain
 *					failure - 0
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
struct mbuf *
clnp_data_ck(m, length)
register struct mbuf	*m;		/* ptr to mbuf chain containing hdr & data */
int						length;	/* length (in bytes) of packet */
 {
	register int 			len;		/* length of data */
	register struct mbuf	*mhead;		/* ptr to head of chain */

	len = -length;
	mhead = m;
	for (;;) {
		len += m->m_len;
		if (m->m_next == 0)
			break;
		m = m->m_next;
	}
	if (len != 0) {
		if (len < 0) {
			INCSTAT(cns_toosmall);
			clnp_discard(mhead, GEN_INCOMPLETE);
			return 0;
		}
		if (len <= m->m_len)
			m->m_len -= len;
		else
			m_adj(mhead, -len);
	}
	return mhead;
}

D 12
#ifdef ndef
E 12
I 12
#ifdef notdef
E 12
/*
 * FUNCTION:		clnp_extract_addr
 *
 * PURPOSE:			Extract the source and destination address from the
 *					supplied buffer. Place them in the supplied address buffers.
 *					If insufficient data is supplied, then fail.
 *
 * RETURNS:			success - Address of first byte in the packet past 
 *						the address part.
 *					failure - 0
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
caddr_t
clnp_extract_addr(bufp, buflen, srcp, destp)
caddr_t					bufp;		/* ptr to buffer containing addresses */
int						buflen;		/* length of buffer */
register struct iso_addr	*srcp;		/* ptr to source address buffer */
register struct iso_addr	*destp;		/* ptr to destination address buffer */
 {
	int	len;		/* argument to bcopy */

	/* 
	 *	check that we have enough data. Plus1 is for length octet
	 */
	if ((u_char)*bufp + 1 > buflen) {
		return((caddr_t)0);
	}
	len = destp->isoa_len = (u_char)*bufp++;
	(void) bcopy(bufp, (caddr_t)destp, len);
	buflen -= len;
	bufp += len;

	/* 
	 *	check that we have enough data. Plus1 is for length octet
	 */
	if ((u_char)*bufp + 1 > buflen) {
		return((caddr_t)0);
	}
	len = srcp->isoa_len = (u_char)* bufp++;
	(void) bcopy(bufp, (caddr_t)srcp, len);
	bufp += len;

	/*
	 *	Insure that the addresses make sense
	 */
	if (iso_ck_addr(srcp) && iso_ck_addr(destp))
		return bufp;
	else
		return (caddr_t) 0;
}
D 12
#endif	ndef
E 12
I 12
D 17
#endif	notdef
E 17
I 17
#endif	/* notdef */
E 17
E 12

/*
 * FUNCTION:		clnp_ours
 *
 * PURPOSE:			Decide whether the supplied packet is destined for
 *					us, or that it should be forwarded on.
 *
 * RETURNS:			packet is for us - 1
 *					packet is not for us - 0
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
clnp_ours(dst)
register struct iso_addr *dst;		/* ptr to destination address */
{
	register struct iso_ifaddr *ia;	/* scan through interface addresses */

	for (ia = iso_ifaddr; ia; ia = ia->ia_next) {
		IFDEBUG(D_ROUTE)
D 9
			printf("clnp_ours: ia_sis x%x, dst x%x\n", &IA_SIS(ia)->siso_addr, 
E 9
I 9
			printf("clnp_ours: ia_sis x%x, dst x%x\n", &ia->ia_addr, 
E 9
				dst);
		ENDDEBUG
D 9
		/* PHASE 2: uses iso_addrmatch & mask from iso_ifaddr */
		if (iso_addrmatch1(&IA_SIS(ia)->siso_addr, dst))
			return 1;
E 9
I 9
		/*
		 * XXX Warning:
		 * We are overloading siso_tlen in the if's address, as an nsel length.
		 */
D 11
		if (dst->isoa_len == ia->ia_addr.siso_tlen + ia->ia_addr.siso_nlen &&
E 11
I 11
		if (dst->isoa_len == ia->ia_addr.siso_nlen &&
E 11
			bcmp((caddr_t)ia->ia_addr.siso_addr.isoa_genaddr,
D 11
				 (caddr_t)dst->isoa_genaddr, ia->ia_addr.siso_nlen) == 0)
E 11
I 11
				 (caddr_t)dst->isoa_genaddr,
				 ia->ia_addr.siso_nlen - ia->ia_addr.siso_tlen) == 0)
E 11
					return 1;
E 9
	}
	return 0;
}

I 3
/* Dec bit set if ifp qlen is greater than congest_threshold */
int congest_threshold = 0;

E 3
/*
 * FUNCTION:		clnp_forward
 *
 * PURPOSE:			Forward the datagram passed
 *					clnpintr guarantees that the header will be
 *					contigious (a cluster mbuf will be used if necessary).
 *
 *					If oidx is NULL, no options are present.
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
clnp_forward(m, len, dst, oidx, seg_off, inbound_shp)
struct mbuf			*m;		/* pkt to forward */
int					len;	/* length of pkt */
struct iso_addr		*dst;	/* destination address */
struct clnp_optidx	*oidx;	/* option index */
int					seg_off;/* offset of segmentation part */
struct snpa_hdr		*inbound_shp;	/* subnetwork header of inbound packet */
{
	struct clnp_fixed		*clnp;	/* ptr to fixed part of header */
	int						error;	/* return value of route function */
	struct sockaddr			*next_hop;	/* next hop for dgram */
	struct ifnet			*ifp;	/* ptr to outgoing interface */
I 4
	struct iso_ifaddr		*ia = 0;/* ptr to iso name for ifp */
E 4
D 2
	struct route			route;	/* filled in by clnp_route */
E 2
I 2
	struct route_iso		route;	/* filled in by clnp_route */
E 2
	extern int				iso_systype;

	clnp = mtod(m, struct clnp_fixed *);
	bzero((caddr_t)&route, sizeof(route)); /* MUST be done before "bad:" */

	/*
	 *	Don't forward multicast or broadcast packets
	 */
	if ((inbound_shp) && (IS_MULTICAST(inbound_shp->snh_dhost))) {
		IFDEBUG(D_FORWARD)
			printf("clnp_forward: dropping multicast packet\n");
		ENDDEBUG
D 4
		clnp->cnf_err_ok = 0;	/* so we don't generate an ER */
E 4
I 4
		clnp->cnf_type &= ~CNF_ERR_OK; /* so we don't generate an ER */
E 4
		clnp_discard(m, 0);
I 7
		INCSTAT(cns_cantforward);
E 7
		goto done;
	}

	IFDEBUG(D_FORWARD)
		printf("clnp_forward: %d bytes, to %s, options x%x\n", len,
			clnp_iso_addrp(dst), oidx);
	ENDDEBUG

	/*
	 *	Decrement ttl, and if zero drop datagram
	 *	Can't compare ttl as less than zero 'cause its a unsigned
	 */
	if ((clnp->cnf_ttl == 0) || (--clnp->cnf_ttl == 0)) {
		IFDEBUG(D_FORWARD)
			printf("clnp_forward: discarding datagram because ttl is zero\n");
		ENDDEBUG
		INCSTAT(cns_ttlexpired);
		clnp_discard(m, TTL_EXPTRANSIT);
		goto done;
	}
D 4
	
E 4
	/*
	 *	Route packet; special case for source rt
	 */
	if CLNPSRCRT_VALID(oidx) {
		/*
		 *	Update src route first
		 */
		clnp_update_srcrt(m, oidx);
D 4
		error = clnp_srcroute(m, oidx, &route, &next_hop, &ifp, dst);
E 4
I 4
		error = clnp_srcroute(m, oidx, &route, &next_hop, &ia, dst);
E 4
	} else {
D 4
		error = clnp_route(dst, &route, 0, &next_hop, &ifp);
E 4
I 4
		error = clnp_route(dst, &route, 0, &next_hop, &ia);
E 4
	}
D 4
	if (error) {
E 4
I 4
	if (error || ia == 0) {
E 4
		IFDEBUG(D_FORWARD)
			printf("clnp_forward: can't route packet (errno %d)\n", error);
		ENDDEBUG
		clnp_discard(m, ADDR_DESTUNREACH);
I 7
		INCSTAT(cns_cantforward);
E 7
		goto done;
	}
I 4
	ifp = ia->ia_ifp;
E 4

	IFDEBUG(D_FORWARD)
		printf("clnp_forward: packet routed to %s\n", 
			clnp_iso_addrp(&((struct sockaddr_iso *)next_hop)->siso_addr));
	ENDDEBUG

	INCSTAT(cns_forward);

	/*
	 *	If we are an intermediate system and
	 *	we are routing outbound on the same ifp that the packet
	 *	arrived upon, and we know the next hop snpa, 
	 *	then generate a redirect request
	 */
	if ((iso_systype & SNPA_IS) && (inbound_shp) && 
D 11
		(ifp == inbound_shp->snh_ifp)) {
D 10
		struct snpa_cache 			*sc;

		sc = snpac_look(&((struct sockaddr_iso *)next_hop)->siso_addr);
		if (sc != NULL) {
			esis_rdoutput(inbound_shp, m, oidx, dst, sc);
		}
E 10
I 10
			register struct sockaddr_dl *sdl =
				(struct sockaddr_dl *) route.ro_rt->rt_gateway;
			if (sdl->sdl_family == AF_LINK && sdl->sdl_alen != 0)
				esis_rdoutput(inbound_shp, m, oidx, dst, route.ro_rt);
E 10
	}

E 11
I 11
		(ifp == inbound_shp->snh_ifp))
		    esis_rdoutput(inbound_shp, m, oidx, dst, route.ro_rt);
E 11
	/*
	 *	If options are present, update them
	 */
	if (oidx) {
D 4
		struct iso_addr	*mysrc = 
			clnp_srcaddr(ifp, &((struct sockaddr_iso *)next_hop)->siso_addr);
E 4
I 4
		struct iso_addr	*mysrc = &ia->ia_addr.siso_addr;
E 4
		if (mysrc == NULL) {
			clnp_discard(m, ADDR_DESTUNREACH);
I 7
			INCSTAT(cns_cantforward);
			clnp_stat.cns_forward--;
E 7
			goto done;
		} else {
D 3
		(void) clnp_dooptions(m, oidx, ifp, mysrc);
E 3
I 3
			(void) clnp_dooptions(m, oidx, ifp, mysrc);
E 3
		}
	}
I 3

#ifdef	DECBIT
	if (ifp->if_snd.ifq_len > congest_threshold) {
		/*
		 *	Congestion! Set the Dec Bit and thank Dave Oran
		 */
		IFDEBUG(D_FORWARD)
			printf("clnp_forward: congestion experienced\n");
		ENDDEBUG
		if ((oidx) && (oidx->cni_qos_formatp)) {
			caddr_t	qosp = CLNP_OFFTOOPT(m, oidx->cni_qos_formatp);
			u_char	qos = *qosp;
			IFDEBUG(D_FORWARD)
				printf("clnp_forward: setting congestion bit (qos x%x)\n", qos);
			ENDDEBUG
			if ((qos & CLNPOVAL_GLOBAL) == CLNPOVAL_GLOBAL) {
				qos |= CLNPOVAL_CONGESTED;
				INCSTAT(cns_congest_set);
				*qosp = qos;
			}
		}
	}
D 17
#endif	DECBIT
E 17
I 17
#endif	/* DECBIT */
E 17
E 3
	
	/*
	 *	Dispatch the datagram if it is small enough, otherwise fragment
	 */
D 12
	if (len <= SN_MTU(ifp)) {
E 12
I 12
	if (len <= SN_MTU(ifp, route.ro_rt)) {
E 12
		iso_gen_csum(m, CLNP_CKSUM_OFF, (int)clnp->cnf_hdr_len);
D 8
		(void) (*ifp->if_output)(ifp, m, next_hop);
E 8
I 8
		(void) (*ifp->if_output)(ifp, m, next_hop, route.ro_rt);
E 8
	} else {
D 8
		(void) clnp_fragment(ifp, m, next_hop, len, seg_off, /* flags */0);
E 8
I 8
		(void) clnp_fragment(ifp, m, next_hop, len, seg_off, /* flags */0, route.ro_rt);
E 8
	}
	
done:
	/*
	 *	Free route
	 */
	if (route.ro_rt != NULL) {
		RTFREE(route.ro_rt);
	}
}

D 12
#ifdef	ndef
E 12
I 12
#ifdef	notdef
E 12
/*
 * FUNCTION:		clnp_insert_addr
 *
 * PURPOSE:			Insert the address part into a clnp datagram.
 *
 * RETURNS:			Address of first byte after address part in datagram.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Assume that there is enough space for the address part.
 */
caddr_t
clnp_insert_addr(bufp, srcp, dstp)
caddr_t						bufp;	/* address of where addr part goes */
register struct iso_addr	*srcp;	/* ptr to src addr */
register struct iso_addr	*dstp;	/* ptr to dst addr */
{
	*bufp++ = dstp->isoa_len;
	(void) bcopy((caddr_t)dstp, bufp, dstp->isoa_len);
	bufp += dstp->isoa_len;

	*bufp++ = srcp->isoa_len;
	(void) bcopy((caddr_t)srcp, bufp, srcp->isoa_len);
	bufp += srcp->isoa_len;

	return bufp;
}

D 12
#endif	ndef
E 12
I 12
D 17
#endif	notdef
E 17
I 17
#endif	/* notdef */
E 17
E 12

/*
 * FUNCTION:		clnp_route
 *
 * PURPOSE:			Route a clnp datagram to the first hop toward its 
 *					destination. In many cases, the first hop will be
 *					the destination. The address of a route
 *					is specified. If a routing entry is present in
 *					that route, and it is still up to the same destination,
 *					then no further action is necessary. Otherwise, a
 *					new routing entry will be allocated.
 *
 * RETURNS:			route found - 0
 *					unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			It is up to the caller to free the routing entry
 *					allocated in route.
 */
D 4
clnp_route(dst, ro, flags, first_hop, ifp)
struct iso_addr		*dst;			/* ptr to datagram destination */
D 2
struct route		*ro;			/* existing route structure */
E 2
I 2
struct route_iso	*ro;			/* existing route structure */
E 2
int					flags;			/* flags for routing */
struct sockaddr		**first_hop;	/* result: fill in with ptr to firsthop */
struct ifnet		**ifp;			/* result: fill in with ptr to interface */
E 4
I 4
clnp_route(dst, ro, flags, first_hop, ifa)
	struct iso_addr	*dst;			/* ptr to datagram destination */
	register struct	route_iso *ro;	/* existing route structure */
	int flags;						/* flags for routing */
	struct sockaddr **first_hop;	/* result: fill in with ptr to firsthop */
	struct iso_ifaddr **ifa;		/* result: fill in with ptr to interface */
E 4
{
D 4
	register struct sockaddr_iso	*ro_dst;	/* ptr to route's destination */
E 4
I 4
	if (flags & SO_DONTROUTE) {
D 5
		struct sockaddr_iso dest;
E 5
		struct iso_ifaddr *ia;
E 4

D 4
	ro_dst = (struct sockaddr_iso *)&ro->ro_dst;

E 4
I 4
D 5
		bzero((caddr_t)&dest, sizeof(dest));
		bcopy((caddr_t)dst, (caddr_t)&dest.siso_addr,
E 5
I 5
		if (ro->ro_rt) {
			RTFREE(ro->ro_rt);
			ro->ro_rt = 0;
		}
		bzero((caddr_t)&ro->ro_dst, sizeof(ro->ro_dst));
		bcopy((caddr_t)dst, (caddr_t)&ro->ro_dst.siso_addr,
E 5
			1 + (unsigned)dst->isoa_len);
D 5
		dest.siso_family = AF_ISO;
		dest.siso_len = sizeof(dest);
		ia = iso_localifa(&dest);
E 5
I 5
		ro->ro_dst.siso_family = AF_ISO;
		ro->ro_dst.siso_len = sizeof(ro->ro_dst);
		ia = iso_localifa(&ro->ro_dst);
E 5
		if (ia == 0)
			return EADDRNOTAVAIL;
		if (ifa)
D 5
			*ifa = (struct iso_ifaddr *)ia;
E 5
I 5
			*ifa = ia;
		if (first_hop)
			*first_hop = (struct sockaddr *)&ro->ro_dst;
E 5
		return 0;
	}
E 4
	/*
	 *	If there is a cached route, check that it is still up and to
	 *	the same destination. If not, free it and try again.
	 */
	if (ro->ro_rt && ((ro->ro_rt->rt_flags & RTF_UP) == 0 ||
D 4
		(!iso_addrmatch1(&ro_dst->siso_addr, dst)))) {
E 4
I 4
		(Bcmp(ro->ro_dst.siso_data, dst->isoa_genaddr, dst->isoa_len)))) {
E 4
		IFDEBUG(D_ROUTE)
			printf("clnp_route: freeing old route: ro->ro_rt 0x%x\n",
				ro->ro_rt);
			printf("clnp_route: old route refcnt: 0x%x\n",
				ro->ro_rt->rt_refcnt);
		ENDDEBUG

		/* free old route entry */
		RTFREE(ro->ro_rt);
		ro->ro_rt = (struct rtentry *)0;
	} else {
		IFDEBUG(D_ROUTE)
			printf("clnp_route: OK route exists\n");
		ENDDEBUG
	}

	if (ro->ro_rt == 0) {
		/* set up new route structure */
D 4
		ro_dst->siso_family = AF_ISO;
		ro_dst->siso_addr = *dst;

E 4
I 4
		bzero((caddr_t)&ro->ro_dst, sizeof(ro->ro_dst));
		ro->ro_dst.siso_len = sizeof(ro->ro_dst);
		ro->ro_dst.siso_family = AF_ISO;
		Bcopy(dst, &ro->ro_dst.siso_addr, 1 + dst->isoa_len);
E 4
		/* allocate new route */
		IFDEBUG(D_ROUTE)
			printf("clnp_route: allocating new route to %s\n",
				clnp_iso_addrp(dst));
		ENDDEBUG
D 4
		rtalloc(ro);
E 4
I 4
		rtalloc((struct route *)ro);
E 4
	}
D 4

	if ((ro->ro_rt == 0) || ((*ifp = ro->ro_rt->rt_ifp) == 0)) {
E 4
I 4
	if (ro->ro_rt == 0)
E 4
		return(ENETUNREACH);	/* rtalloc failed */
D 4
	}

E 4
	ro->ro_rt->rt_use++;
D 4
	if (ro->ro_rt->rt_flags & (RTF_GATEWAY|RTF_HOST))
		*first_hop = &ro->ro_rt->rt_gateway;
	else
		*first_hop = (struct sockaddr *)ro_dst;
		
E 4
I 4
	if (ifa)
		if ((*ifa = (struct iso_ifaddr *)ro->ro_rt->rt_ifa) == 0)
			panic("clnp_route");
	if (first_hop) {
D 8
		if (ro->ro_rt->rt_flags & (RTF_GATEWAY|RTF_HOST))
E 8
I 8
		if (ro->ro_rt->rt_flags & RTF_GATEWAY)
E 8
			*first_hop = ro->ro_rt->rt_gateway;
		else
			*first_hop = (struct sockaddr *)&ro->ro_dst;
	}
E 4
	return(0);
}

/*
 * FUNCTION:		clnp_srcroute
 *
 * PURPOSE:			Source route the datagram. If complete source
 *					routing is specified but not possible, then
 *					return an error. If src routing is terminated, then
 *					try routing on destination.
 *					Usage of first_hop,
 *					ifp, and error return is identical to clnp_route.
 *
 * RETURNS:			0 or unix error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Remember that option index pointers are really
 *					offsets from the beginning of the mbuf.
 */
D 4
clnp_srcroute(options, oidx, route, first_hop, ifp, final_dst)
E 4
I 4
D 11
clnp_srcroute(options, oidx, route, first_hop, ifa, final_dst)
E 11
I 11
clnp_srcroute(options, oidx, ro, first_hop, ifa, final_dst)
E 11
E 4
struct mbuf			*options;		/* ptr to options */
struct clnp_optidx	*oidx;			/* index to options */
D 4
struct route		*route;			/* route structure */
E 4
I 4
D 11
struct route_iso	*route;			/* route structure */
E 11
I 11
struct route_iso	*ro;			/* route structure */
E 11
E 4
struct sockaddr		**first_hop;	/* RETURN: fill in with ptr to firsthop */
D 4
struct ifnet		**ifp;			/* RETURN: fill in with ptr to interface */
E 4
I 4
struct iso_ifaddr	**ifa;			/* RETURN: fill in with ptr to interface */
E 4
struct iso_addr		*final_dst;		/* final destination */
{
	struct iso_addr	dst;		/* first hop specified by src rt */
	int				error = 0;	/* return code */

	/*
	 *	Check if we have run out of routes 
	 *	If so, then try to route on destination.
	 */
	if CLNPSRCRT_TERM(oidx, options) {
		dst.isoa_len = final_dst->isoa_len;
D 4
		bcopy((caddr_t)final_dst, (caddr_t)&dst, dst.isoa_len);
E 4
I 4
		bcopy(final_dst->isoa_genaddr, dst.isoa_genaddr, dst.isoa_len);
E 4
	} else {
		/*
		 * setup dst based on src rt specified
		 */
		dst.isoa_len = CLNPSRCRT_CLEN(oidx, options);
D 4
		bcopy(CLNPSRCRT_CADDR(oidx, options), (caddr_t)&dst, dst.isoa_len);
E 4
I 4
		bcopy(CLNPSRCRT_CADDR(oidx, options), dst.isoa_genaddr, dst.isoa_len);
E 4
	}

	/*
	 *	try to route it
	 */
D 4
	error = clnp_route(&dst, route, 0, first_hop, ifp);
E 4
I 4
D 11
	error = clnp_route(&dst, route, 0, first_hop, ifa);
E 11
I 11
	error = clnp_route(&dst, ro, 0, first_hop, ifa);
E 11
E 4
	if (error != 0)
		return error;
	
	/*
	 *	If complete src rt, first hop must be equal to dst
	 */
	if ((CLNPSRCRT_TYPE(oidx, options) == CLNPOVAL_COMPRT) &&
	 (!iso_addrmatch1(&(*(struct sockaddr_iso **)first_hop)->siso_addr,&dst))){
		IFDEBUG(D_OPTIONS)
			printf("clnp_srcroute: complete src route failed\n");
		ENDDEBUG
		return EHOSTUNREACH; /* RAH? would like ESRCRTFAILED */
	}
	
	return error;
D 4
}

/*
 * FUNCTION:		clnp_srcaddr
 *
 * PURPOSE:			Build the correct source address for a datagram based on the
 *					outgoing interface and firsthop. The firsthop information
 *					is needed inorder to decide which addr to use if
 *					>1 ISO addr is present for an ifp.
 *
 * RETURNS:			a ptr to a static copy of the source address.
 *					or NULL
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			The ifp must be valid, or we will return NULL
 */
static struct iso_addr mysrc;
struct iso_addr *
clnp_srcaddr(ifp, firsthop)
struct ifnet	*ifp;		/* ptr to interface to send packet on */
struct iso_addr	*firsthop;	/* ptr to first hop for packet */
{
	register struct iso_ifaddr *ia;	/* scan through interface addresses */
	struct iso_addr				*maybe = NULL;

	for (ia = iso_ifaddr; ia; ia = ia->ia_next) {
		if (ia->ia_ifp == ifp) {
			struct iso_addr	*isoa = &IA_SIS(ia)->siso_addr;

			IFDEBUG(D_ROUTE)
				printf("clnp_srcaddr: isoa is %s\n", clnp_iso_addrp(isoa));
			ENDDEBUG

			if (iso_eqtype(isoa, firsthop)) {
				mysrc.isoa_len = isoa->isoa_len;
				bcopy((caddr_t)isoa, (caddr_t)&mysrc, mysrc.isoa_len);
				return(&mysrc);
			} else 
				maybe = isoa;
		}
	}

	if (maybe != NULL) {
		mysrc.isoa_len = maybe->isoa_len;
		bcopy((caddr_t)maybe, (caddr_t)&mysrc, mysrc.isoa_len);
		return(&mysrc);
	} else {
		/*
		 *	This will only happen if there are routes involving
		 *	an interface that has just had all iso addresses deleted
		 *	from it. This will happen if esisd has added a default
		 *	route to an interface, and then the interface was
		 *	marked down. As soon as esisd tries to send a pdu on that
		 *	interface, it will discover it is down, and remove the
		 *	route.  Nonetheless, there is a window for this discrepancy,
		 *	so we will return null here rather than panicing.
		 */
		return(NULL);
	}
E 4
}

/*
I 14
 * FUNCTION:		clnp_echoreply
 *
 * PURPOSE:			generate an echo reply packet and transmit
 *
 * RETURNS:			result of clnp_output
 *
 * SIDE EFFECTS:	
 */
clnp_echoreply(ec_m, ec_len, ec_src, ec_dst, ec_oidxp)
struct mbuf			*ec_m;		/* echo request */
int					ec_len;		/* length of ec */
struct sockaddr_iso	*ec_src;		/* src of ec */
struct sockaddr_iso	*ec_dst; 	/* destination of ec (i.e., us) */
struct clnp_optidx	*ec_oidxp;	/* options index to ec packet */
{
	struct isopcb	isopcb;
	int				flags = CLNP_NOCACHE|CLNP_ECHOR;
	int				ret;

	/* fill in fake isopcb to pass to output function */
	bzero(&isopcb, sizeof(isopcb));
	isopcb.isop_laddr = ec_dst;
	isopcb.isop_faddr = ec_src;

	/* forget copying the options for now. If implemented, need only
	 * copy record route option, but it must be reset to zero length */

	ret = clnp_output(ec_m, &isopcb, ec_len, flags);

	IFDEBUG(D_OUTPUT)
		printf("clnp_echoreply: output returns %d\n", ret);
	ENDDEBUG
	return ret;
}

/*
E 14
I 12
 * FUNCTION:		clnp_badmtu
 *
 * PURPOSE:			print notice of route with mtu not initialized.
 *
 * RETURNS:			mtu of ifp.
 *
 * SIDE EFFECTS:	prints notice, slows down system.
 */
clnp_badmtu(ifp, rt, line, file)
struct ifnet *ifp;	/* outgoing interface */
struct rtentry *rt; /* dst route */
int line;			/* where the dirty deed occured */
char *file;			/* where the dirty deed occured */
{
D 16
	printf("sending on route %x with no mtu, line %s of file %s\n",
E 16
I 16
	printf("sending on route 0x%x with no mtu, line %d of file %s\n",
E 16
		rt, line, file);
#ifdef ARGO_DEBUG
D 16
	printf("route dst is");
E 16
I 16
	printf("route dst is ");
E 16
	dump_isoaddr(rt_key(rt));
#endif
	return ifp->if_mtu;
}

/*
E 12
 * FUNCTION:		clnp_ypocb - backwards bcopy
 *
 * PURPOSE:			bcopy starting at end of src rather than beginning.
 *
 * RETURNS:			none
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			No attempt has been made to make this efficient
 */
clnp_ypocb(from, to, len)
caddr_t from;		/* src buffer */
caddr_t to;			/* dst buffer */
u_int	len;		/* number of bytes */
{
	while (len--)
		*(to + len) = *(from + len);
D 12
}

/*
 * FUNCTION:		clnp_hdrsize
 *
 * PURPOSE:			Return the size of a typical clnp hdr.
 *
 * RETURNS:			Size of hdr in bytes.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Assumes segmenting subset. If addrlen is
 *					zero, default to largest nsap address size.
 */
clnp_hdrsize(addrlen)
u_char	addrlen;		/* length of nsap address */
{
	if (addrlen == 0)
		addrlen = 20;
	
	addrlen++;			/* length of address byte */
	addrlen *= 2;		/* src and dst addresses */
	addrlen += sizeof(struct clnp_fixed) + sizeof(struct clnp_segment);

	return(addrlen);
E 12
}
D 17
#endif	ISO
E 17
I 17
#endif	/* ISO */
E 17
E 1
