h22098
s 00002/00002/00347
d D 8.1 93/06/10 23:18:22 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00015/00334
d D 7.8 92/10/11 12:21:33 bostic 8 7
c make kernel includes standard
e
s 00009/00005/00340
d D 7.7 91/05/06 18:58:47 bostic 7 6
c new copyright; att/bsd/shared
e
s 00002/00002/00343
d D 7.6 90/04/05 11:10:49 sklower 6 5
c change error for requiring fragmentation; if_output requires rtentry ptr.
e
s 00015/00020/00330
d D 7.5 89/09/22 00:15:07 sklower 5 4
c make changes for SNMP
e
s 00001/00000/00349
d D 7.4 89/08/29 13:43:47 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00030/00036/00319
d D 7.3 89/04/22 11:53:16 sklower 3 2
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00008/00005/00347
d D 7.2 89/02/14 18:22:29 sklower 2 1
c include wisconsin revisions
e
s 00352/00000/00000
d D 7.1 88/12/14 15:29:22 sklower 1 0
c date and time created 88/12/14 15:29:22 by sklower
e
u
U
t
T
I 7
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 7
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
/* $Header: clnp_er.c,v 4.4 88/09/10 18:31:10 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_er.c,v $ */
E 2
I 2
/* $Header: /var/src/sys/netiso/RCS/clnp_er.c,v 5.1 89/02/09 16:20:18 hagens Exp $ */
/* $Source: /var/src/sys/netiso/RCS/clnp_er.c,v $ */
I 4
D 7
/*	%W% (Berkeley) %G% */
E 4
E 2

#ifndef lint
D 2
static char *rcsid = "$Header: clnp_er.c,v 4.4 88/09/10 18:31:10 hagens Exp $";
E 2
I 2
static char *rcsid = "$Header: /var/src/sys/netiso/RCS/clnp_er.c,v 5.1 89/02/09 16:20:18 hagens Exp $";
E 2
#endif lint
E 7

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
E 3
I 3
#include "types.h"
E 5
D 8
#include "param.h"
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
E 8
I 8
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 8
E 3

D 8
#include "../net/if.h"
#include "../net/route.h"
E 8
I 8
#include <net/if.h>
#include <net/route.h>
E 8

D 3
#include "../netiso/iso.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
E 3
I 3
D 8
#include "iso.h"
#include "iso_var.h"
#include "iso_pcb.h"
E 8
I 8
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_pcb.h>
E 8
I 5
#define CLNP_ER_CODES
E 5
D 8
#include "clnp.h"
#include "clnp_stat.h"
#include "argo_debug.h"
E 8
I 8
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 8
E 3

static struct clnp_fixed er_template = {
	ISO8473_CLNP,	/* network identifier */
	0,				/* length */
	ISO8473_V1,		/* version */
	CLNP_TTL,		/* ttl */
D 3
#if BYTE_ORDER == LITTLE_ENDIAN
E 3
	CLNP_ER,		/* type */
D 3
	0, 				/* error report */
	0, 				/* more segments */
	0, 				/* segmentation permitted */
#endif
#if BYTE_ORDER == BIG_ENDIAN
	0, 				/* segmentation permitted */
	0, 				/* more segments */
	0, 				/* error report */
	CLNP_ER,		/* type */
#endif
E 3
	0,				/* segment length */
	0				/* checksum */
};

/*
 * FUNCTION:		clnp_er_input
 *
 * PURPOSE:			Process an ER pdu.
 *
 * RETURNS:			
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
clnp_er_input(m, src, reason)
struct mbuf		*m;		/* ptr to packet itself */
struct iso_addr	*src;	/* ptr to src of er */
D 3
char			reason;	/* reason code of er */
E 3
I 3
u_char			reason;	/* reason code of er */
E 3
{
	int	cmd = -1;
	extern u_char clnp_protox[];

	IFDEBUG(D_CTLINPUT)
		printf("clnp_er_input: m x%x, src %s, reason x%x\n", m, 
			clnp_iso_addrp(src), reason);
	ENDDEBUG

D 5
	INCSTAT(cns_errcvd);

E 5
I 5
	INCSTAT(cns_er_inhist[clnp_er_index(reason)]);
E 5
	switch (reason) {
		case GEN_NOREAS:
		case GEN_PROTOERR:
D 5
			INCSTAT(er_protoerr);
E 5
			break;
		case GEN_BADCSUM:		
			cmd = PRC_PARAMPROB;
D 5
			INCSTAT(er_badcsum);
E 5
			break;
		case GEN_CONGEST:		
			cmd = PRC_QUENCH;
D 5
			INCSTAT(er_congest);
E 5
			break;
		case GEN_HDRSYNTAX:		
			cmd = PRC_PARAMPROB;
D 5
			INCSTAT(er_protoerr);
E 5
			break;
		case GEN_SEGNEEDED:		
D 6
			cmd = PRC_UNREACH_NEEDFRAG; 
E 6
I 6
			cmd = PRC_MSGSIZE; 
E 6
D 5
			INCSTAT(er_segneeded);
E 5
			break;
		case GEN_INCOMPLETE:	
			cmd = PRC_PARAMPROB; 		
D 5
			INCSTAT(er_reassfail);
E 5
			break;
		case GEN_DUPOPT:		
			cmd = PRC_PARAMPROB;		
D 5
			INCSTAT(er_protoerr);
E 5
			break;
		case ADDR_DESTUNREACH:	
			cmd = PRC_UNREACH_HOST; 	
D 5
			INCSTAT(er_dstunreach);
E 5
			break;
		case ADDR_DESTUNKNOWN:	
			cmd = PRC_UNREACH_PROTOCOL; 
D 5
			INCSTAT(er_dstunreach);
E 5
			break;
		case SRCRT_UNSPECERR:
		case SRCRT_SYNTAX:
		case SRCRT_UNKNOWNADDR:
		case SRCRT_BADPATH:
			cmd = PRC_UNREACH_SRCFAIL;
D 5
			INCSTAT(er_srcrterr);
E 5
			break;
		case TTL_EXPTRANSIT:	
			cmd = PRC_TIMXCEED_INTRANS;	
D 5
			INCSTAT(er_ttlexpired);
E 5
			break;
		case TTL_EXPREASS:		
			cmd = PRC_TIMXCEED_REASS;	
D 5
			INCSTAT(er_ttlexpired);
E 5
			break;
		case DISC_UNSUPPOPT:
		case DISC_UNSUPPVERS:
		case DISC_UNSUPPSECURE:
		case DISC_UNSUPPSRCRT:
		case DISC_UNSUPPRECRT:
			cmd = PRC_PARAMPROB; 
D 5
			INCSTAT(er_unsupported); 
E 5
			break;
		case REASS_INTERFERE:	
			cmd = PRC_TIMXCEED_REASS;
D 5
			INCSTAT(er_reassfail);
E 5
			break;
	}

I 2
	/*
	 *	tpclnp_ctlinput1 is called directly so that we don't
	 *	have to build an iso_sockaddr out of src.
	 */
E 2
	if (cmd >= 0)
D 2
		(*isosw[clnp_protox[ISOPROTO_TP]].pr_ctlinput)(cmd, src);
E 2
I 2
		tpclnp_ctlinput1(cmd, src);
E 2

	m_freem(m);
}

/*
 * FUNCTION:		clnp_discard
 *
 * PURPOSE:			Discard a clnp datagram
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	Will emit an ER pdu if possible
 *
 * NOTES:			This code assumes that we have previously tried to pull
 *					up the header of the datagram into one mbuf.
 */
clnp_discard(m, reason)
struct mbuf	*m;		/* header of packet to discard */
char					reason;	/* reason for discard */
{
	IFDEBUG(D_DISCARD)
		printf("clnp_discard: m x%x, reason x%x\n", m, reason);
	ENDDEBUG

	if (m != NULL) {
		if (m->m_len >= sizeof(struct clnp_fixed)) {
			register struct clnp_fixed *clnp = mtod(m, struct clnp_fixed *);

D 3
			if ((clnp->cnf_type != CLNP_ER) && (clnp->cnf_err_ok)) {
				clnp_emit_er(m, reason);
				return;
E 3
I 3
			if (((clnp->cnf_type & CNF_TYPE) != CLNP_ER) &&
				(clnp->cnf_type & CNF_ERR_OK)) {
					clnp_emit_er(m, reason);
					return;
E 3
			}
		}
		m_freem(m);
	}
}

/*
 * FUNCTION:		clnp_emit_er
 *
 * PURPOSE:			Send an ER pdu.
 *					The src of the of the ER pdu is the host that is sending
 *					the ER (ie. us), *not* the original destination of the
 *					packet.
 *
 * RETURNS:			nothing
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			Takes responsibility for freeing mbuf passed
 *					This function may be called with a packet that
 *					was created by us; in this case, do not send
 *					an ER.
 */
clnp_emit_er(m, reason)
struct mbuf	*m;		/* header of packet to discard */
char					reason;	/* reason for discard */
{
	register struct clnp_fixed	*clnp = mtod(m, struct clnp_fixed *);
	register struct clnp_fixed	*er;
D 3
	struct route				route;
E 3
I 3
	struct route_iso			route;
E 3
	struct ifnet				*ifp;
	struct sockaddr				*first_hop;
	struct iso_addr				src, dst, *our_addr;
	caddr_t						hoff, hend;
	int							total_len;		/* total len of dg */
	struct mbuf 				*m0;			/* contains er pdu hdr */
I 3
	struct iso_ifaddr			*ia = 0;
E 3
D 2
/*	struct clnp_optidx			*oidx;	 index for options on orig pkt */
E 2

	IFDEBUG(D_DISCARD)
		printf("clnp_emit_er: m x%x, hdr len %d\n", m, clnp->cnf_hdr_len);
	ENDDEBUG

	bzero((caddr_t)&route, sizeof(route));

	/*
	 *	If header length is incorrect, or entire header is not contained
	 *	in this mbuf, we punt
	 */
	if ((clnp->cnf_hdr_len < CLNP_HDR_MIN) ||
		(clnp->cnf_hdr_len > CLNP_HDR_MAX) ||
		(clnp->cnf_hdr_len > m->m_len))
		goto bad;
	
	/* extract src, dest address */
	hend = (caddr_t)clnp + clnp->cnf_hdr_len;
	hoff = (caddr_t)clnp + sizeof(struct clnp_fixed);
	CLNP_EXTRACT_ADDR(dst, hoff, hend);
	if (hoff == (caddr_t)0) {
		goto bad;
	}
	CLNP_EXTRACT_ADDR(src, hoff, hend);
	if (hoff == (caddr_t)0) {
		goto bad;
	}
	
	/*
	 *	Do not send ER if we generated the packet.
	 */
	if (clnp_ours(&src))
		goto bad;

	/* 
	 *	Trim mbuf to hold only the header.
	 *	This mbuf will be the 'data' of the er pdu
	 */
	if (m->m_next != NULL) {
		m_freem(m->m_next);
		m->m_next = NULL;
	}

	if (m->m_len > clnp->cnf_hdr_len)
D 3
		m_adj(m, -(m->m_len - clnp->cnf_hdr_len));
E 3
I 3
		m_adj(m, (int)-(m->m_len - (int)clnp->cnf_hdr_len));
E 3

	/* route er pdu: note we send pkt to src of original packet  */
D 3
	if (clnp_route(&src, &route, /* flags */0, &first_hop, &ifp) != 0)
E 3
I 3
	if (clnp_route(&src, &route, /* flags */0, &first_hop, &ia) != 0)
E 3
		goto bad;

	/* compute our address based upon firsthop/ifp */
D 3
	our_addr = 
			clnp_srcaddr(ifp, &((struct sockaddr_iso *)first_hop)->siso_addr);
	if (our_addr == NULL)
		goto bad;
E 3
I 3
	if (ia)
			our_addr = &ia->ia_addr.siso_addr;
	else
			goto bad;
	ifp = ia->ia_ifp;
E 3

	IFDEBUG(D_DISCARD)
		printf("clnp_emit_er: to %s", clnp_iso_addrp(&src));
		printf(" from %s\n", clnp_iso_addrp(our_addr));
	ENDDEBUG

	IFDEBUG(D_DISCARD)
		printf("clnp_emit_er: packet routed to %s\n", 
			clnp_iso_addrp(&((struct sockaddr_iso *)first_hop)->siso_addr));
	ENDDEBUG

	/* allocate mbuf for er pdu header: punt on no space */
	MGET(m0, M_DONTWAIT, MT_HEADER);
	if (m0 == 0)
		goto bad;
	
	m0->m_next = m;
	er = mtod(m0, struct clnp_fixed *);
	*er = er_template;

	/* setup src/dst on er pdu */
	/* NOTE REVERSAL OF SRC/DST */
	hoff = (caddr_t)er + sizeof(struct clnp_fixed);
D 3
	CLNP_INSERT_ADDR(hoff, &src);
	CLNP_INSERT_ADDR(hoff, our_addr);
E 3
I 3
	CLNP_INSERT_ADDR(hoff, src);
	CLNP_INSERT_ADDR(hoff, *our_addr);
E 3

	/*
	 *	TODO: if complete src rt was specified, then reverse path, and
	 *	copy into er as option.
	 */

	/* add er option */
	*hoff++ = CLNPOVAL_ERREAS;	/* code */
	*hoff++ = 2;				/* length */
	*hoff++ = reason;			/* discard reason */
	*hoff++ = 0;				/* error localization = not specified */

	/* set length */
	er->cnf_hdr_len = m0->m_len = (u_char)(hoff - (caddr_t)er);
	total_len = m0->m_len + m->m_len;
	HTOC(er->cnf_seglen_msb, er->cnf_seglen_lsb, total_len);

	/* compute checksum (on header only) */
	iso_gen_csum(m0, CLNP_CKSUM_OFF, (int)er->cnf_hdr_len);

	/* trim packet if too large for interface */
	if (total_len > ifp->if_mtu)
		m_adj(m0, -(total_len - ifp->if_mtu));
	
	/* send packet */
I 5
	INCSTAT(cns_er_outhist[clnp_er_index(reason)]);
E 5
D 6
	(void) (*ifp->if_output)(ifp, m0, first_hop);
E 6
I 6
	(void) (*ifp->if_output)(ifp, m0, first_hop, route.ro_rt);
E 6
	goto done;

bad:
	m_freem(m);

done:
	/* free route if it is a temp */
	if (route.ro_rt != NULL)
		RTFREE(route.ro_rt);
}
D 5
#endif	ISO
E 5
I 5

clnp_er_index(p)
u_char p;
{
	register u_char *cp = clnp_er_codes + CLNP_ERRORS;
	while (cp > clnp_er_codes) {
		cp--;
		if (*cp == p)
			return (cp - clnp_er_codes);
	}
	return (CLNP_ERRORS + 1);
}
E 5
E 1
