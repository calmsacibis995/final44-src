/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	raw_ip.c,v $
 * Revision 2.4  90/07/03  16:43:35  mrt
 * 	Added rel5 multicast code from Stanford.
 * 	[90/06/28            jjk]
 * 
 * 	Merged mt Xinu 2.6 MSD changes.
 * 	[90/05/17            emg]
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
 *	@(#)raw_ip.c	7.4 (Berkeley) 6/29/88
 */

#include <multicast.h>

#include "param.h"
#include "mbuf.h"
#include "socket.h"
#include "protosw.h"
#include "socketvar.h"
#include "errno.h"

#include "../net/if.h"
#include "../net/route.h"
#include "../net/raw_cb.h"

#include "in.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#if	MULTICAST
#include "in_var.h"
#endif	MULTICAST

/*
 * Raw interface to IP protocol.
 */

struct	sockaddr_in ripdst = { AF_INET };
struct	sockaddr_in ripsrc = { AF_INET };
struct	sockproto ripproto = { PF_INET };
/*
 * Setup generic address and protocol structures
 * for raw_input routine, then pass them along with
 * mbuf chain.
 */
rip_input(m)
	struct mbuf *m;
{
	register struct ip *ip = mtod(m, struct ip *);

	ripproto.sp_protocol = ip->ip_p;
	ripdst.sin_addr = ip->ip_dst;
	ripsrc.sin_addr = ip->ip_src;
	raw_input(m, &ripproto, (struct sockaddr *)&ripsrc,
	  (struct sockaddr *)&ripdst);
}

/*
 * Generate IP header and pass packet to ip_output.
 * Tack on options user may have setup with control call.
 */
rip_output(m, so)
	register struct mbuf *m;
	struct socket *so;
{
	register struct ip *ip;
	int error;
	struct rawcb *rp = sotorawcb(so);
	struct sockaddr_in *sin;

	/*
	 * If the user handed us a complete IP packet, use it.
	 * Otherwise, allocate an mbuf for a header and fill it in.
	 */
	if (rp->rcb_flags & RAW_HDRINCL)
		ip = mtod(m, struct ip *);
	else {
		int len = 0;
		struct mbuf *m0;

		/* calculate data length */
		for (m0 = m; m; m = m->m_next)
			len += m->m_len;

		/* get mbuf for IP header */
		m = m_get(M_DONTWAIT, MT_HEADER);
		if (m == 0) {
			m = m0;
			error = ENOBUFS;
			goto bad;
		}
		m->m_off = MMAXOFF - sizeof(struct ip);
		m->m_len = sizeof(struct ip);
		m->m_next = m0;

		ip = mtod(m, struct ip *);
		ip->ip_tos = 0;
		ip->ip_off = 0;
		ip->ip_p = rp->rcb_proto.sp_protocol;
		ip->ip_len = sizeof(struct ip) + len;
		ip->ip_ttl = MAXTTL;
	}

	if (rp->rcb_flags & RAW_LADDR) {
		sin = (struct sockaddr_in *)&rp->rcb_laddr;
		if (sin->sin_family != AF_INET) {
			error = EAFNOSUPPORT;
			goto bad;
		}
		ip->ip_src.s_addr = sin->sin_addr.s_addr;
	} else
		ip->ip_src.s_addr = 0;
#if	MULTICAST
	if (ip->ip_src.s_addr != 0) {
	    /*
	     * Verify that the source address is one of ours.
	     */
	    struct ifnet *ifp;
	    INADDR_TO_IFP(ip->ip_src, ifp);
	    if (ifp == NULL) {
		error = EADDRNOTAVAIL;
		goto bad;
	    }
	}
#endif	MULTICAST

	ip->ip_dst = ((struct sockaddr_in *)&rp->rcb_faddr)->sin_addr;

#if	MULTICAST
	return (ip_output(m,
	   (rp->rcb_flags & RAW_HDRINCL)? (struct mbuf *)0: rp->rcb_options,
	   &rp->rcb_route, (so->so_options&SO_DONTROUTE) | IP_ALLOWBROADCAST
	   | IP_MULTICASTOPTS, rp->rcb_moptions));
#else	MULTICAST
	return (ip_output(m,
	   (rp->rcb_flags & RAW_HDRINCL)? (struct mbuf *)0: rp->rcb_options,
	   &rp->rcb_route, (so->so_options&SO_DONTROUTE) | IP_ALLOWBROADCAST));
#endif	MULTICAST
bad:
	m_freem(m);
	return (error);
}

/*
 * Raw IP socket option processing.
 */
rip_ctloutput(op, so, level, optname, m)
	int op;
	struct socket *so;
	int level, optname;
	struct mbuf **m;
{
	int error = 0;
	register struct rawcb *rp = sotorawcb(so);

	if (level != IPPROTO_IP)
		error = EINVAL;
	else switch (op) {

	case PRCO_SETOPT:
		switch (optname) {

		case IP_OPTIONS:
			return (ip_pcbopts(&rp->rcb_options, *m));

		case IP_HDRINCL:
			if (m == 0 || *m == 0 || (*m)->m_len < sizeof (int)) {
				error = EINVAL;
				break;
			}
			if (*mtod(*m, int *))
				rp->rcb_flags |= RAW_HDRINCL;
			else
				rp->rcb_flags &= ~RAW_HDRINCL;
			break;

#if	MULTICAST
		case IP_MULTICAST_IF:
		case IP_MULTICAST_TTL:
		case IP_MULTICAST_LOOP:
		case IP_ADD_MEMBERSHIP:
		case IP_DROP_MEMBERSHIP:
			error = ip_setmoptions(optname, &rp->rcb_moptions, *m);
			break;
		default:
			error = ip_mrouter_cmd(optname, so, *m);
			break;
#else	MULTICAST
		default:
			error = EINVAL;
			break;
#endif	MULTICAST
		}
		break;

	case PRCO_GETOPT:
		switch (optname) {

		case IP_OPTIONS:
			*m = m_get(M_WAIT, MT_SOOPTS);
			if (rp->rcb_options) {
				(*m)->m_off = rp->rcb_options->m_off;
				(*m)->m_len = rp->rcb_options->m_len;
				bcopy(mtod(rp->rcb_options, caddr_t),
				    mtod(*m, caddr_t), (unsigned)(*m)->m_len);
			} else
				(*m)->m_len = 0;
			break;

		case IP_HDRINCL:
			*m = m_get(M_WAIT, MT_SOOPTS);
			(*m)->m_len = sizeof (int);
			*mtod(*m, int *) = rp->rcb_flags & RAW_HDRINCL;
			break;

#if	MULTICAST
		case IP_MULTICAST_IF:
		case IP_MULTICAST_TTL:
		case IP_MULTICAST_LOOP:
		case IP_ADD_MEMBERSHIP:
		case IP_DROP_MEMBERSHIP:
			error = ip_getmoptions(optname, rp->rcb_moptions, m);
			break;
#endif	MULTICAST

		default:
			error = EINVAL;
			break;
		}
		break;
	}
	if (op == PRCO_SETOPT && *m)
		(void)m_free(*m);
	return (error);
}
