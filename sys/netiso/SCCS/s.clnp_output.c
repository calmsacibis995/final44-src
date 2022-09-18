h30694
s 00002/00002/00533
d D 8.1 93/06/10 23:18:37 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00533
d D 7.13 93/06/04 17:02:09 sklower 13 12
c fix #endif something to #endif /* something */
e
s 00016/00016/00519
d D 7.12 92/10/11 12:21:37 bostic 12 11
c make kernel includes standard
e
s 00012/00000/00523
d D 7.11 92/02/14 14:16:29 sklower 11 10
c changes proposed by hagens to make CLNP EchoReply work
e
s 00009/00005/00514
d D 7.10 91/05/06 18:58:52 bostic 10 9
c new copyright; att/bsd/shared
e
s 00003/00002/00516
d D 7.9 91/04/26 15:09:34 sklower 9 8
c fragmentation decision considers route 
e
s 00010/00010/00508
d D 7.8 90/06/04 16:46:19 sklower 8 7
c Fix bugs reported in fragmentation and reassembly reported by D. Katz
e
s 00008/00001/00510
d D 7.7 90/05/03 17:39:08 sklower 7 6
c fix minor bugs for raw access
e
s 00003/00001/00508
d D 7.6 90/04/05 11:16:44 sklower 6 5
c if_output now called with rtentry ptr.
e
s 00011/00010/00498
d D 7.5 89/09/22 00:15:31 sklower 5 4
c make changes for SNMP
e
s 00003/00007/00505
d D 7.4 89/08/29 13:43:55 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00047/00079/00465
d D 7.3 89/04/22 11:53:28 sklower 3 2
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00031/00003/00513
d D 7.2 89/02/14 18:35:25 sklower 2 1
c wisconsin changes
e
s 00516/00000/00000
d D 7.1 88/12/14 15:29:26 sklower 1 0
c date and time created 88/12/14 15:29:26 by sklower
e
u
U
t
T
I 10
/*-
D 14
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 10
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
/* $Header: clnp_output.c,v 4.5 88/09/15 18:57:57 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_output.c,v $ */
E 2
I 2
/* $Header: /var/src/sys/netiso/RCS/clnp_output.c,v 5.0 89/02/08 12:00:15 hagens Exp $ */
/* $Source: /var/src/sys/netiso/RCS/clnp_output.c,v $ */
I 4
D 10
/*	%W% (Berkeley) %G% */
E 4
E 2

#ifndef lint
D 2
static char *rcsid = "$Header: clnp_output.c,v 4.5 88/09/15 18:57:57 hagens Exp $";
E 2
I 2
static char *rcsid = "$Header: /var/src/sys/netiso/RCS/clnp_output.c,v 5.0 89/02/08 12:00:15 hagens Exp $";
E 2
#endif lint
E 10

D 5
#ifdef ISO
D 3
#include "../h/types.h"
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
#include "../h/time.h"
E 3
I 3
#include "types.h"
E 5
D 12
#include "param.h"
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
#include "time.h"
E 12
I 12
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>
E 12
E 3

D 12
#include "../net/if.h"
#include "../net/route.h"
E 12
I 12
#include <net/if.h>
#include <net/route.h>
E 12

D 3
#include "../netiso/iso.h"
#include "../netiso/iso_pcb.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
E 3
I 3
D 12
#include "iso.h"
#include "iso_var.h"
#include "iso_pcb.h"
#include "clnp.h"
#include "clnp_stat.h"
#include "argo_debug.h"
E 12
I 12
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_pcb.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 12
E 3

static struct clnp_fixed dt_template = {
	ISO8473_CLNP,	/* network identifier */
	0,				/* length */
	ISO8473_V1,		/* version */
	CLNP_TTL,		/* ttl */
D 3
#if BYTE_ORDER == LITTLE_ENDIAN
	CLNP_DT,		/* type */
	1, 				/* error report */
	0, 				/* more segments */
	1, 				/* segmentation permitted */
#endif
#if BYTE_ORDER == BIG_ENDIAN
	1, 				/* segmentation permitted */
	0, 				/* more segments */
	1, 				/* error report */
	CLNP_DT,		/* type */
#endif 
E 3
I 3
	CLNP_DT|CNF_SEG_OK|CNF_ERR_OK,		/* type */
E 3
	0,				/* segment length */
	0				/* checksum */
};

static struct clnp_fixed raw_template = {
	ISO8473_CLNP,	/* network identifier */
	0,				/* length */
	ISO8473_V1,		/* version */
	CLNP_TTL,		/* ttl */
D 3
#if BYTE_ORDER == LITTLE_ENDIAN
	CLNP_RAW,		/* type */
	1, 				/* error report */
	0, 				/* more segments */
	1, 				/* segmentation permitted */
#endif
#if BYTE_ORDER == BIG_ENDIAN
	1, 				/* segmentation permitted */
	0, 				/* more segments */
	1, 				/* error report */
	CLNP_RAW,		/* type */
#endif
E 3
I 3
	CLNP_RAW|CNF_SEG_OK|CNF_ERR_OK,		/* type */
E 3
	0,				/* segment length */
	0				/* checksum */
};

static struct clnp_fixed echo_template = {
	ISO8473_CLNP,	/* network identifier */
	0,				/* length */
	ISO8473_V1,		/* version */
	CLNP_TTL,		/* ttl */
D 3
#if BYTE_ORDER == LITTLE_ENDIAN
	CLNP_EC,		/* type */
	1, 				/* error report */
	0, 				/* more segments */
	1, 				/* segmentation permitted */
#endif
#if BYTE_ORDER == BIG_ENDIAN
	1, 				/* segmentation permitted */
	0, 				/* more segments */
	1, 				/* error report */
	CLNP_EC,		/* type */
#endif
E 3
I 3
	CLNP_EC|CNF_SEG_OK|CNF_ERR_OK,		/* type */
E 3
	0,				/* segment length */
	0				/* checksum */
};

I 11
static struct clnp_fixed echor_template = {
	ISO8473_CLNP,	/* network identifier */
	0,				/* length */
	ISO8473_V1,		/* version */
	CLNP_TTL,		/* ttl */
	CLNP_ECR|CNF_SEG_OK|CNF_ERR_OK,		/* type */
	0,				/* segment length */
	0				/* checksum */
};

E 11
I 2
#ifdef	DECBIT
u_char qos_option[] = {CLNPOVAL_QOS, 1, 
	CLNPOVAL_GLOBAL|CLNPOVAL_SEQUENCING|CLNPOVAL_LOWDELAY};
D 13
#endif	DECBIT
E 13
I 13
#endif	/* DECBIT */
E 13

E 2
int				clnp_id = 0;		/* id for segmented dgrams */

/*
 * FUNCTION:		clnp_output
 *
 * PURPOSE:			output the data in the mbuf as a clnp datagram
 *
 *					The data specified by m0 is sent as a clnp datagram. 
 *					The mbuf chain m0 will be freed when this routine has
 *					returned.
 *
 *					If options is non-null, it points to an mbuf which contains
 *					options to be sent with the datagram. The options must
 *					be formatted in the mbuf according to clnp rules. Options
 *					will not be freed.
 *
 *					Datalen specifies the length of the data in m0. 
 *
 *					Src and dst are the addresses for the packet. 
 *
 *					If route is non-null, it is used as the route for 
 *					the packet. 
 *
 *					By default, a DT is sent. However, if flags & CNLP_SEND_ER
 *					then an ER will be sent. If flags & CLNP_SEND_RAW, then
 *					the packet will be send as raw clnp.
 *
 * RETURNS:			0	success
 *					appropriate error code
 *
 * SIDE EFFECTS:	none
 *
 * NOTES:			
 *					Flags are interpretated as follows:
 *						CLNP_NO_SEG - do not allow this pkt to be segmented.
 *						CLNP_NO_ER  - have pkt request ER suppression.
 *						CLNP_SEND_RAW - send pkt as RAW DT rather than TP DT
 *						CLNP_NO_CKSUM - don't compute clnp checksum
 *						CLNP_ECHO - send as ECHO packet
 *
 *					When checking for a cached packet, clnp checks
 *					that the route taken is still up. It does not
 *					check that the route is still to the same destination.
 *					This means that any entity that alters an existing
 *					route for an isopcb (such as when a redirect arrives)
 *					must invalidate the clnp cache. It might be perferable
 *					to have clnp check that the route has the same dest, but
 *					by avoiding this check, we save a call to iso_addrmatch1.
 */
D 3
clnp_output(m0, isop, datalen, flags)
E 3
I 3
D 4
clnp_output(m0, isop, flags)
E 4
I 4
clnp_output(m0, isop, datalen, flags)
E 4
E 3
struct mbuf			*m0;		/* data for the packet */
struct isopcb		*isop;		/* iso pcb */
I 4
int					datalen;	/* number of bytes of data in m0 */
E 4
D 3
int					datalen;	/* number of bytes of data in m */
E 3
int					flags;		/* flags */
{
	int							error = 0;		/* return value of function */
D 3
	register struct mbuf		*m;				/* mbuf for clnp header chain */
E 3
I 3
	register struct mbuf		*m = m0;		/* mbuf for clnp header chain */
D 4
	int							datalen;	/* number of bytes of data in m */
E 4
E 3
	register struct clnp_fixed	*clnp;			/* ptr to fixed part of hdr */
	register caddr_t			hoff;			/* offset into header */
	int							total_len;		/* total length of packet */
	struct iso_addr				*src;		/* ptr to source address */
	struct iso_addr				*dst;		/* ptr to destination address */
	struct clnp_cache			clc;		/* storage for cache information */
	struct clnp_cache			*clcp = NULL;	/* ptr to clc */
I 2
	int							hdrlen = 0;
E 2

D 3
	src = &isop->isop_laddr.siso_addr;
	dst = &isop->isop_faddr.siso_addr;
E 3
I 3
D 7
	src = &isop->isop_laddr->siso_addr;
E 7
	dst = &isop->isop_faddr->siso_addr;
I 7
	if (isop->isop_laddr == 0) {
		struct iso_ifaddr *ia = 0;
		clnp_route(dst, &isop->isop_route, flags, 0, &ia);
		if (ia == 0 || ia->ia_ifa.ifa_addr->sa_family != AF_ISO)
			return (ENETUNREACH);
		src = &ia->ia_addr.siso_addr;
	} else
		src = &isop->isop_laddr->siso_addr;
E 7
E 3

I 3
D 4
	if ((m->m_flags & M_PKTHDR) == 0) {
		m_freem(m);
		return EINVAL;
	}
	datalen = m->m_pkthdr.len;
E 4
E 3
	IFDEBUG(D_OUTPUT)
		printf("clnp_output: to %s", clnp_iso_addrp(dst));
		printf(" from %s of %d bytes\n", clnp_iso_addrp(src), datalen);
		printf("\toptions x%x, flags x%x, isop_clnpcache x%x\n", 
			isop->isop_options, flags, isop->isop_clnpcache);
	ENDDEBUG

	if (isop->isop_clnpcache != NULL) {
		clcp = mtod(isop->isop_clnpcache, struct clnp_cache *);
	}
	
	/*
	 *	Check if cache is valid ...
	 */
	IFDEBUG(D_OUTPUT)
		printf("clnp_output: ck cache: clcp %x\n", clcp);
		if (clcp != NULL) {
			printf("\tclc_dst %s\n", clnp_iso_addrp(&clcp->clc_dst));
			printf("\tisop_opts x%x, clc_opts x%x\n", isop->isop_options,
				clcp->clc_options);
			if (isop->isop_route.ro_rt)
				printf("\tro_rt x%x, rt_flags x%x\n",
					isop->isop_route.ro_rt, isop->isop_route.ro_rt->rt_flags);
			printf("\tflags x%x, clc_flags x%x\n", flags, clcp->clc_flags);
			printf("\tclc_hdr x%x\n", clcp->clc_hdr);
		}
	ENDDEBUG
	if ((clcp != NULL) &&								/* cache exists */
		(isop->isop_options == clcp->clc_options) && 	/* same options */
		(iso_addrmatch1(dst, &clcp->clc_dst)) &&		/* dst still same */
		(isop->isop_route.ro_rt != NULL) &&				/* route exists */
I 6
		(isop->isop_route.ro_rt == clcp->clc_rt) &&		/* and is cached */
E 6
		(isop->isop_route.ro_rt->rt_flags & RTF_UP) &&	/* route still up */
		(flags == clcp->clc_flags) &&					/* same flags */
		(clcp->clc_hdr != NULL)) {						/* hdr mbuf exists */
		/*
		 *	The cache is valid
		 */

		IFDEBUG(D_OUTPUT)
			printf("clnp_output: using cache\n");
		ENDDEBUG

D 3
		m = m_copy(clcp->clc_hdr, 0, M_COPYALL);
E 3
I 3
		m = m_copy(clcp->clc_hdr, 0, (int)M_COPYALL);
E 3
		if (m == NULL) {
			/*
			 *	No buffers left to copy cached packet header. Use
			 *	the cached packet header this time, and
			 *	mark the hdr as vacant
			 */
			m = clcp->clc_hdr;
			clcp->clc_hdr = NULL;
		}
		m->m_next = m0;	/* ASSUMES pkt hdr is 1 mbuf long */
		clnp = mtod(m, struct clnp_fixed *);
	} else {
		struct clnp_optidx	*oidx = NULL;		/* index to clnp options */

		/*
		 *	The cache is not valid. Allocate an mbuf (if necessary)
		 *	to hold cached info. If one is not available, then
		 *	don't bother with the cache
		 */
		INCSTAT(cns_cachemiss);
		if (flags & CLNP_NOCACHE) {
			clcp = &clc;
		} else {
			if (isop->isop_clnpcache == NULL) {
				/*
				 *	There is no clnpcache. Allocate an mbuf to hold one
				 */
				if ((isop->isop_clnpcache = m_get(M_DONTWAIT, MT_HEADER))
					== NULL) {
					/*
					 *	No mbufs available. Pretend that we don't want
					 *	caching this time.
					 */
					IFDEBUG(D_OUTPUT)
						printf("clnp_output: no mbufs to allocate to cache\n");
					ENDDEBUG
					flags  |= CLNP_NOCACHE;
					clcp = &clc;
				} else {
					clcp = mtod(isop->isop_clnpcache, struct clnp_cache *);
				}
			} else {
				/*
				 *	A clnpcache mbuf exists. If the clc_hdr is not null,
				 *	we must free it, as a new one is about to be created.
				 */
				clcp = mtod(isop->isop_clnpcache, struct clnp_cache *);
				if (clcp->clc_hdr != NULL) {
					/*
					 *	The clc_hdr is not null but a clnpcache mbuf exists.
					 *	This means that there was a cache, but the existing
					 *	copy of the hdr is no longer valid. Free it now
					 *	before we lose the pointer to it.
					 */
					IFDEBUG(D_OUTPUT)
						printf("clnp_output: freeing old clc_hdr 0x%x\n",
						clcp->clc_hdr);
					ENDDEBUG
					m_free(clcp->clc_hdr);
					IFDEBUG(D_OUTPUT)
						printf("clnp_output: freed old clc_hdr (done)\n");
					ENDDEBUG
				}
			}
		}
		IFDEBUG(D_OUTPUT)
			printf("clnp_output: NEW clcp x%x\n",clcp);
		ENDDEBUG
		bzero((caddr_t)clcp, sizeof(struct clnp_cache));

		if (isop->isop_optindex)
			oidx = mtod(isop->isop_optindex, struct clnp_optidx *);

		/*
		 *	Don't allow packets with security, quality of service,
		 *	priority, or error report options to be sent.
		 */
		if ((isop->isop_options) && (oidx)) {
			if ((oidx->cni_securep) ||
				(oidx->cni_priorp) ||
				(oidx->cni_qos_formatp) ||
				(oidx->cni_er_reason != ER_INVALREAS)) {
				IFDEBUG(D_OUTPUT)
					printf("clnp_output: pkt dropped - option unsupported\n");
				ENDDEBUG
				m_freem(m0);
				return(EINVAL);
			}
		}

		/*
		 *	Don't allow any invalid flags to be set
		 */
		if ((flags & (CLNP_VFLAGS)) != flags) {
			IFDEBUG(D_OUTPUT)
				printf("clnp_output: packet dropped - flags unsupported\n");
			ENDDEBUG
I 5
			INCSTAT(cns_odropped);
E 5
			m_freem(m0);
			return(EINVAL);
		}

		/*
		 *	Don't allow funny lengths on dst; src may be zero in which
		 *	case we insert the source address based upon the interface
		 */
		if ((src->isoa_len > sizeof(struct iso_addr)) || 
			(dst->isoa_len == 0) ||
			(dst->isoa_len > sizeof(struct iso_addr))) {
			m_freem(m0);
I 5
			INCSTAT(cns_odropped);
E 5
			return(ENAMETOOLONG);
		}

		/*
		 *	Grab mbuf to contain header
		 */
D 3
		MGET(m, M_DONTWAIT, MT_HEADER);
E 3
I 3
		MGETHDR(m, M_DONTWAIT, MT_HEADER);
E 3
		if (m == 0) {
			m_freem(m0);
I 5
			INCSTAT(cns_odropped);
E 5
			return(ENOBUFS);
		}
D 5

E 5
I 5
		INCSTAT(cns_sent);
E 5
		m->m_next = m0;
		clnp = mtod(m, struct clnp_fixed *);
		clcp->clc_segoff = 0;

		/*
		 *	Fill in all of fixed hdr except lengths and checksum
		 */
		if (flags & CLNP_SEND_RAW) {
			*clnp = raw_template;
		} else if (flags & CLNP_ECHO) {
			*clnp = echo_template;
I 11
		} else if (flags & CLNP_ECHOR) {
			*clnp = echor_template;
E 11
		} else {
			*clnp = dt_template;
		}
		if (flags & CLNP_NO_SEG)
D 3
			clnp->cnf_seg_ok = 0;
E 3
I 3
			clnp->cnf_type &= ~CNF_SEG_OK;
E 3
		if (flags & CLNP_NO_ER)
D 3
			clnp->cnf_err_ok = 0;
E 3
I 3
			clnp->cnf_type &= ~CNF_ERR_OK;
E 3

		/*
		 *	Route packet; special case for source rt
		 */
		if ((isop->isop_options) && CLNPSRCRT_VALID(oidx)) {
			IFDEBUG(D_OUTPUT)
				printf("clnp_output: calling clnp_srcroute\n");
			ENDDEBUG
			error = clnp_srcroute(isop->isop_options, oidx, &isop->isop_route,
D 3
				&clcp->clc_firsthop, &clcp->clc_ifp, dst);
E 3
I 3
				&clcp->clc_firsthop, &clcp->clc_ifa, dst);
E 3
		} else {
			IFDEBUG(D_OUTPUT)
			ENDDEBUG
			error = clnp_route(dst, &isop->isop_route, flags, 
D 3
				&clcp->clc_firsthop, &clcp->clc_ifp);
E 3
I 3
				&clcp->clc_firsthop, &clcp->clc_ifa);
E 3
		}
D 3
		if (error != 0) {
E 3
I 3
		if (error || (clcp->clc_ifa == 0)) {
E 3
			IFDEBUG(D_OUTPUT)
				printf("clnp_output: route failed, errno %d\n", error);
				printf("@clcp:\n");
				dump_buf(clcp, sizeof (struct clnp_cache));
			ENDDEBUG
			goto bad;
		}
I 6
		clcp->clc_rt = isop->isop_route.ro_rt;	/* XXX */
I 9
		clcp->clc_ifp = clcp->clc_ifa->ia_ifp;  /* XXX */
E 9
E 6

		IFDEBUG(D_OUTPUT)
			printf("clnp_output: packet routed to %s\n", 
				clnp_iso_addrp(
					&((struct sockaddr_iso *)clcp->clc_firsthop)->siso_addr));
		ENDDEBUG
		
		/*
		 *	If src address is not yet specified, use address of 
		 *	interface. NOTE: this will now update the laddr field in
		 *	the isopcb. Is this desirable? RAH?
		 */
		if (src->isoa_len == 0) {
D 3
			src = clnp_srcaddr(clcp->clc_ifp,
				&((struct sockaddr_iso *)clcp->clc_firsthop)->siso_addr);
			if (src == NULL) {
				error = ENETDOWN;
				goto bad;
			}
E 3
I 3
			src = &(clcp->clc_ifa->ia_addr.siso_addr);
E 3
			IFDEBUG(D_OUTPUT)
				printf("clnp_output: new src %s\n", clnp_iso_addrp(src));
			ENDDEBUG
		}

		/*
		 *	Insert the source and destination address,
		 */
		hoff = (caddr_t)clnp + sizeof(struct clnp_fixed);
D 3
		CLNP_INSERT_ADDR(hoff, dst);
		CLNP_INSERT_ADDR(hoff, src);
E 3
I 3
		CLNP_INSERT_ADDR(hoff, *dst);
		CLNP_INSERT_ADDR(hoff, *src);
E 3

		/*
		 *	Leave room for the segment part, if segmenting is selected
		 */
D 3
		if (clnp->cnf_seg_ok) {
E 3
I 3
		if (clnp->cnf_type & CNF_SEG_OK) {
E 3
			clcp->clc_segoff = hoff - (caddr_t)clnp;
			hoff += sizeof(struct clnp_segment);
		}

		clnp->cnf_hdr_len = m->m_len = (u_char)(hoff - (caddr_t)clnp);
I 2
		hdrlen = clnp->cnf_hdr_len;
E 2

I 2
#ifdef	DECBIT
E 2
		/*
I 2
		 *	Add the globally unique QOS (with room for congestion experienced
		 *	bit). I can safely assume that this option is not in the options
		 *	mbuf below because I checked that the option was not specified
		 *	previously
		 */
		if ((m->m_len + sizeof(qos_option)) < MLEN) {
			bcopy((caddr_t)qos_option, hoff, sizeof(qos_option));
			clnp->cnf_hdr_len += sizeof(qos_option);
			hdrlen += sizeof(qos_option);
			m->m_len += sizeof(qos_option);
		}
D 13
#endif	DECBIT
E 13
I 13
#endif	/* DECBIT */
E 13

		/*
E 2
		 *	If an options mbuf is present, concatenate a copy to the hdr mbuf.
		 */
		if (isop->isop_options) {
D 3
			struct mbuf *opt_copy = m_copy(isop->isop_options, 0, M_COPYALL);
E 3
I 3
			struct mbuf *opt_copy = m_copy(isop->isop_options, 0, (int)M_COPYALL);
E 3
			if (opt_copy == NULL) {
				error = ENOBUFS;
				goto bad;
			}
			/* Link in place */
			opt_copy->m_next = m->m_next;
			m->m_next = opt_copy;

			/* update size of header */
			clnp->cnf_hdr_len += opt_copy->m_len;
I 2
			hdrlen += opt_copy->m_len;
		}

		if (hdrlen > CLNP_HDR_MAX) {
			error = EMSGSIZE;
			goto bad;
E 2
		}

		/*
		 *	Now set up the cache entry in the pcb
		 */
		if ((flags & CLNP_NOCACHE) == 0) {
D 3
			if ((clcp->clc_hdr = m_copy(m, 0, clnp->cnf_hdr_len)) != NULL) {
				bcopy((caddr_t)dst, (caddr_t)&clcp->clc_dst, 
					sizeof(struct iso_addr));
E 3
I 3
			if (clcp->clc_hdr = m_copy(m, 0, (int)clnp->cnf_hdr_len)) {
				clcp->clc_dst  = *dst;
E 3
				clcp->clc_flags = flags;
				clcp->clc_options = isop->isop_options;
			}
		}
	}
D 5
	INCSTAT(cns_sent);
E 5
	/*
	 *	If small enough for interface, send directly
	 *	Fill in segmentation part of hdr if using the full protocol
	 */
D 3
	if ((total_len = clnp->cnf_hdr_len + datalen) <= SN_MTU(clcp->clc_ifp)) {
		if (clnp->cnf_seg_ok) {
E 3
I 3
D 8
	if ((total_len = clnp->cnf_hdr_len + datalen)
			<= SN_MTU(clcp->clc_ifa->ia_ifp)) {
		if (clnp->cnf_type & CNF_SEG_OK) {
E 3
			struct clnp_segment	seg_part;		/* segment part of hdr */
			seg_part.cng_id = htons(clnp_id++);
			seg_part.cng_off = htons(0);
			seg_part.cng_tot_len = htons(total_len);
			(void) bcopy((caddr_t)&seg_part, (caddr_t) clnp + clcp->clc_segoff, 
				sizeof(seg_part));
		}
E 8
I 8
	total_len = clnp->cnf_hdr_len + datalen;
	if (clnp->cnf_type & CNF_SEG_OK) {
		struct clnp_segment	seg_part;		/* segment part of hdr */
		seg_part.cng_id = htons(clnp_id++);
		seg_part.cng_off = htons(0);
		seg_part.cng_tot_len = htons(total_len);
		(void) bcopy((caddr_t)&seg_part, (caddr_t) clnp + clcp->clc_segoff, 
			sizeof(seg_part));
	}
D 9
	if (total_len <= SN_MTU(clcp->clc_ifa->ia_ifp)) {
E 9
I 9
	if (total_len <= SN_MTU(clcp->clc_ifp, clcp->clc_rt)) {
E 9
E 8
		HTOC(clnp->cnf_seglen_msb, clnp->cnf_seglen_lsb, total_len);
D 3

E 3
I 3
		m->m_pkthdr.len = total_len;
E 3
		/*
		 *	Compute clnp checksum (on header only)
		 */
		if (flags & CLNP_NO_CKSUM) {
			HTOC(clnp->cnf_cksum_msb, clnp->cnf_cksum_lsb, 0);
		} else {
			iso_gen_csum(m, CLNP_CKSUM_OFF, (int)clnp->cnf_hdr_len);
		}

		IFDEBUG(D_DUMPOUT)
			struct mbuf *mdump = m;
			printf("clnp_output: sending dg:\n");
			while (mdump != NULL) {
				dump_buf(mtod(mdump, caddr_t), mdump->m_len);
				mdump = mdump->m_next;
			}
		ENDDEBUG

		error = SN_OUTPUT(clcp, m);
		goto done;
	} else {
		/*
		 * Too large for interface; fragment if possible.
		 */
D 3
		error = clnp_fragment(clcp->clc_ifp, m, clcp->clc_firsthop, total_len, 
E 3
I 3
D 5
		error = clnp_fragment(clcp->clc_ifa->ia_ifp, m, clcp->clc_firsthop, total_len, 
E 3
			clcp->clc_segoff, flags);
E 5
I 5
D 9
		error = clnp_fragment(clcp->clc_ifa->ia_ifp, m, clcp->clc_firsthop,
E 9
I 9
		error = clnp_fragment(clcp->clc_ifp, m, clcp->clc_firsthop,
E 9
D 6
									total_len, clcp->clc_segoff, flags);
E 6
I 6
							total_len, clcp->clc_segoff, flags, clcp->clc_rt);
E 6
E 5
		goto done;
	}
bad:
	m_freem(m);
D 5

E 5
done:
D 5
	return(error);
E 5
I 5
	if (error) {
		clnp_stat.cns_sent--;
		clnp_stat.cns_odropped++;
	}
	return (error);
E 5
}

int clnp_ctloutput()
{
}
D 5

#endif ISO
E 5
E 1
