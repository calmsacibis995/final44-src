h02994
s 00002/00002/00324
d D 8.1 93/06/10 23:18:41 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00005/00325
d D 7.12 93/06/04 17:02:14 sklower 12 11
c fix #endif something to #endif /* something */
e
s 00003/00003/00327
d D 7.11 93/05/25 11:51:29 bostic 11 10
c trailing comment after #else or #endif
e
s 00017/00017/00313
d D 7.10 92/10/11 12:21:38 bostic 10 9
c make kernel includes standard
e
s 00001/00001/00329
d D 7.9 92/02/06 16:37:47 sklower 9 8
c comparison wrongly takes precedence over bitwise and
e
s 00009/00004/00321
d D 7.8 91/05/06 18:58:54 bostic 8 7
c new copyright; att/bsd/shared
e
s 00003/00003/00322
d D 7.7 90/04/05 11:21:29 sklower 7 6
c rights special case of ancillary data
e
s 00004/00008/00321
d D 7.6 90/01/17 00:01:40 sklower 6 5
c changes for cltp
e
s 00007/00007/00322
d D 7.5 89/09/22 00:15:35 sklower 5 4
c make changes for SNMP
e
s 00005/00001/00324
d D 7.4 89/08/29 13:44:01 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00009/00009/00316
d D 7.3 89/04/25 17:19:36 mckusick 3 2
c ../h => (implicitly) ../sys
e
s 00111/00099/00214
d D 7.2 89/04/22 11:53:31 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00313/00000/00000
d D 7.1 88/12/14 15:29:27 sklower 1 0
c date and time created 88/12/14 15:29:27 by sklower
e
u
U
t
T
I 8
/*-
D 13
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 8
I 1
D 2
/***********************************************************
		Copyright IBM Corporation 1987
E 2
I 2
D 5
/*********************************************************** Copyright IBM Corporation 1987
E 5
I 5
/***********************************************************
				Copyright IBM Corporation 1987
E 5
E 2

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
/* $Header: clnp_raw.c,v 4.2 88/06/29 14:58:56 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/clnp_raw.c,v $ */
I 4
D 8
/*	%W% (Berkeley) %G% */
E 4
#ifndef lint
static char *rcsid = "$Header: clnp_raw.c,v 4.2 88/06/29 14:58:56 hagens Exp $";
#endif lint
E 8

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
D 10
#include "param.h"
#include "mbuf.h"
#include "domain.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "errno.h"
#include "time.h"
E 10
I 10
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>
E 10
E 3

D 10
#include "../net/if.h"
#include "../net/route.h"
#include "../net/raw_cb.h"
E 10
I 10
#include <net/if.h>
#include <net/route.h>
#include <net/raw_cb.h>
E 10

D 2
#include "../netiso/iso.h"
#include "../netiso/iso_pcb.h"
#include "../netiso/clnp.h"
#include "../netiso/clnp_stat.h"
#include "../netiso/argo_debug.h"
E 2
I 2
D 10
#include "iso.h"
#include "iso_pcb.h"
#include "clnp.h"
#include "clnp_stat.h"
#include "argo_debug.h"
E 10
I 10
#include <netiso/iso.h>
#include <netiso/iso_pcb.h>
#include <netiso/clnp.h>
#include <netiso/clnp_stat.h>
#include <netiso/argo_debug.h>
E 10
E 2

D 2
struct sockaddr_iso	rclnp_src	= { AF_ISO };
struct sockaddr_iso	rclnp_dst	= { AF_ISO };
E 2
I 2
D 10
#include "tp_user.h"/* XXX -- defines SOL_NETWORK */
E 10
I 10
#include <netiso/tp_user.h>		/* XXX -- defines SOL_NETWORK */
E 10

D 6
struct sockaddr_iso	rclnp_src	= { sizeof(rclnp_src), AF_ISO };
struct sockaddr_iso	rclnp_dst	= { sizeof(rclnp_src), AF_ISO };
E 6
E 2
struct sockproto	rclnp_proto	= { PF_ISO, 0 };
/*
 * FUNCTION:		rclnp_input
 *
 * PURPOSE:			Setup generic address an protocol structures for
 *					raw input routine, then pass them along with the
 *					mbuf chain.
 *
 * RETURNS:			none
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			The protocol field of rclnp_proto is set to zero indicating
 *					no protocol.
 */
rclnp_input(m, src, dst, hdrlen)
struct mbuf 		*m;		/* ptr to packet */
D 6
struct iso_addr		*src;	/* ptr to src address */
struct iso_addr		*dst;	/* ptr to dest address */
E 6
I 6
struct sockaddr_iso	*src;	/* ptr to src address */
struct sockaddr_iso	*dst;	/* ptr to dest address */
E 6
int					hdrlen; /* length (in bytes) of clnp header */
{
#ifdef	TROLL
	if (trollctl.tr_ops & TR_CHUCK) {
		m_freem(m);
		return;
	}
D 11
#endif	TROLL
E 11
I 11
#endif	/* TROLL */
E 11

D 6
	rclnp_src.siso_addr = *src;
	rclnp_dst.siso_addr = *dst;
D 5
	raw_input(m, &rclnp_proto, (struct sockaddr *)&rclnp_src,
		(struct sockaddr *)&rclnp_dst);
E 5
I 5
	if (raw_input(m, &rclnp_proto, (struct sockaddr *)&rclnp_src,
		(struct sockaddr *)&rclnp_dst) == 0) {
E 6
I 6
D 12
	if (raw_input(m, &rclnp_proto, (struct sockaddr *)src,
		(struct sockaddr *)dst) == 0) {
E 6
			clnp_stat.cns_delivered--;
			clnp_stat.cns_noproto++;
	}
E 12
I 12
	raw_input(m, &rclnp_proto, (struct sockaddr *)src, (struct sockaddr *)dst);
E 12
E 5
}

/*
 * FUNCTION:		rclnp_output
 *
 * PURPOSE:			Prepare to send a raw clnp packet. Setup src and dest
 *					addresses, count the number of bytes to send, and
 *					call clnp_output.
 *
 * RETURNS:			success - 0
 *					failure - an appropriate error code
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
rclnp_output(m0, so)
struct mbuf		*m0;		/* packet to send */
struct socket	*so;	/* socket to send from */
{
	register struct mbuf	*m;			/* used to scan a chain */
	int						len = 0;	/* store length of chain here */
D 2
	struct rawcb			*rp = sotorawcb(so); /* ptr to raw cb */
E 2
I 2
	struct rawisopcb		*rp = sotorawisopcb(so); /* ptr to raw cb */
E 2
	int						error;		/* return value of function */
D 2
	u_int					flags;		/* flags for clnp_output */
	struct isopcb			isopcb;		/* isopcb used to interface w/clnp */
E 2
I 2
	int						flags;		/* flags for clnp_output */
E 2

I 4
D 9
	if (0 == m0->m_flags & M_PKTHDR)
E 9
I 9
	if (0 == (m0->m_flags & M_PKTHDR))
E 9
		return (EINVAL);
E 4
D 2
	/* Calculate length of data */
	for (m = m0; m; m = m->m_next)
		len += m->m_len;
	
	bzero((caddr_t)&isopcb, sizeof(isopcb));

E 2
	/*
	 *	Set up src address. If user has bound socket to an address, use it.
	 *	Otherwise, do not specify src (clnp_output will fill it in).
	 */
D 2
	if (rp->rcb_flags & RAW_LADDR) {
		if (rp->rcb_laddr.sa_family != AF_ISO) {
E 2
I 2
	if (rp->risop_rcb.rcb_laddr) {
		if (rp->risop_isop.isop_sladdr.siso_family != AF_ISO) {
bad:
E 2
			m_freem(m0);
			return(EAFNOSUPPORT);
		}
D 2
		bcopy((caddr_t)&rp->rcb_laddr, &isopcb.isop_laddr,
			sizeof(struct sockaddr_iso));
E 2
	}
D 2

	/* set up route structure, if route is present */
	if (rp->rcb_route.ro_rt != NULL)
		bcopy((caddr_t)&rp->rcb_route, (caddr_t)&isopcb.isop_route,
			sizeof(struct route));

E 2
	/* set up dest address */
D 2
	bcopy((caddr_t)&rp->rcb_faddr, &isopcb.isop_faddr,
		sizeof(struct sockaddr_iso));
		
	/* 
	 *	setup option index - this was done when option was set, but raw
	 *	cb has no place to put it.
	 */
	if (rp->rcb_options != NULL) {
		isopcb.isop_options = rp->rcb_options;
		isopcb.isop_optindex = m_get(M_WAIT, MT_SOOPTS);
		(void) clnp_opt_sanity(isopcb.isop_options, 
			mtod(isopcb.isop_options, caddr_t), isopcb.isop_options->m_len, 
			mtod(isopcb.isop_optindex, struct clnp_optidx *));
	}
E 2
I 2
	if (rp->risop_rcb.rcb_faddr == 0)
		goto bad;
	rp->risop_isop.isop_sfaddr =
				*(struct sockaddr_iso *)rp->risop_rcb.rcb_faddr;
	rp->risop_isop.isop_faddr = &rp->risop_isop.isop_sfaddr;
E 2

	/* get flags and ship it off */
D 2
	flags = rp->rcb_flags & CLNP_VFLAGS;
E 2
I 2
	flags = rp->risop_flags & CLNP_VFLAGS;
E 2

D 2
#ifdef	TROLL
	if (trollctl.tr_ops & TR_BLAST) {
		register int i;
		struct timeval start, stop;
		extern struct timeval	time;
		struct mbuf *mbuf_orig;
E 2
I 2
D 4
	error = clnp_output(m0, &rp->risop_isop, flags|CLNP_NOCACHE);
E 4
I 4
	error = clnp_output(m0, &rp->risop_isop, m0->m_pkthdr.len,
												flags|CLNP_NOCACHE);
E 4
E 2

D 2
		mbuf_orig = m0;
		start = time;
		for (i=0; i<trollctl.tr_blast_cnt; i++) {
			m0 = m_copy(mbuf_orig, 0, M_COPYALL);
			if (m0 == NULL) {
				error = ENOBUFS;
			} else {
				error = clnp_output(m0, &isopcb, len, flags);
			}
			if (error)
				break;
		}
		stop = time;
		printf("rclnp_output: %d pkts in %d sec\n", i,
			stop.tv_sec - start.tv_sec);
		m_freem(mbuf_orig);
	} else {
		/*
		 *	Don't bother creating the cache since this is raw; probably
		 *	a one shot send
		 */
		error = clnp_output(m0, &isopcb, len, flags|CLNP_NOCACHE);
	}
#else
		error = clnp_output(m0, &isopcb, len, flags|CLNP_NOCACHE);
#endif	TROLL

	if (isopcb.isop_route.ro_rt)
		RTFREE(isopcb.isop_route.ro_rt);

	/* free clnp cached hdr if necessary */
	if (isopcb.isop_clnpcache != NULL) {
		struct clnp_cache *clcp = 
			mtod(isopcb.isop_clnpcache, struct clnp_cache *);
		if (clcp->clc_hdr != NULL) {
			m_free(clcp->clc_hdr);
		}
		m_free(isopcb.isop_clnpcache);
	}

	if (isopcb.isop_optindex != NULL)
		m_free(isopcb.isop_optindex);

E 2
	return (error);
}

/*
 * FUNCTION:		rclnp_ctloutput
 *
 * PURPOSE:			Raw clnp socket option processing
 *					All options are stored inside an mbuf. 
 *
 * RETURNS:			success - 0
 *					failure - unix error code
 *
 * SIDE EFFECTS:	If the options mbuf does not exist, it the mbuf passed
 *					is used.
 *
 * NOTES:			
 */
rclnp_ctloutput(op, so, level, optname, m)
int				op;				/* type of operation */
struct socket	*so;			/* ptr to socket */
int 			level;			/* level of option */
int				optname;		/* name of option */
struct mbuf		**m;			/* ptr to ptr to option data */
{
	int						error = 0;
D 2
	register struct rawcb	*rp = sotorawcb(so);/* raw cb ptr */
E 2
I 2
	register struct rawisopcb	*rp = sotorawisopcb(so);/* raw cb ptr */
E 2

	IFDEBUG(D_CTLOUTPUT)
		printf("rclnp_ctloutput: op = x%x, level = x%x, name = x%x\n",
			op, level, optname);
		if (*m != NULL) {
			printf("rclnp_ctloutput: %d bytes of mbuf data\n", (*m)->m_len);
			dump_buf(mtod((*m), caddr_t), (*m)->m_len);
		}
	ENDDEBUG

#ifdef SOL_NETWORK
	if (level != SOL_NETWORK)
		error = EINVAL;
	else switch (op) {
#else
	switch (op) {
D 11
#endif SOL_NETWORK
E 11
I 11
#endif /* SOL_NETWORK */
E 11
		case PRCO_SETOPT:
			switch (optname) {
				case CLNPOPT_FLAGS: {
					u_short	usr_flags;
					/* 
					 *	Insure that the data passed has exactly one short in it 
					 */
					if ((*m == NULL) || ((*m)->m_len != sizeof(short))) {
						error = EINVAL;
						break;
					}
					 
					/*
					 *	Don't allow invalid flags to be set
					 */
					usr_flags = (*mtod((*m), short *));

					if ((usr_flags & (CLNP_VFLAGS)) != usr_flags) {
						error = EINVAL;
					} else
D 2
						rp->rcb_flags |= usr_flags;
E 2
I 2
						rp->risop_flags |= usr_flags;
E 2

					} break;
			
				case CLNPOPT_OPTS:
D 2
					error = clnp_set_opts(&rp->rcb_options, m);
E 2
I 2
					if (error = clnp_set_opts(&rp->risop_isop.isop_options, m))
						break;
					rp->risop_isop.isop_optindex = m_get(M_WAIT, MT_SOOPTS);
					(void) clnp_opt_sanity(rp->risop_isop.isop_options, 
						mtod(rp->risop_isop.isop_options, caddr_t),
						rp->risop_isop.isop_options->m_len, 
						mtod(rp->risop_isop.isop_optindex,
							struct clnp_optidx *));
E 2
					break;
			} 
			break;

		case PRCO_GETOPT:
#ifdef notdef
			/* commented out to keep hi C quiet */
			switch (optname) {
				default:
					error = EINVAL;
					break;
			}
D 11
#endif notdef
E 11
I 11
#endif /* notdef */
E 11
			break;
		default:
			error = EINVAL;
			break;
	}
	if (op == PRCO_SETOPT) {
		/* note: m_freem does not barf is *m is NULL */
		m_freem(*m);
		*m = NULL;
	}
	
	return error;
}

/*ARGSUSED*/
D 2
clnp_usrreq(so, req, m, nam, rights)
	struct socket *so;
E 2
I 2
D 7
clnp_usrreq(so, req, m, nam, rights, control)
E 7
I 7
clnp_usrreq(so, req, m, nam, control)
E 7
	register struct socket *so;
E 2
	int req;
D 2
	struct mbuf *m, *nam, *rights;
E 2
I 2
D 7
	struct mbuf *m, *nam, *rights, *control;
E 7
I 7
	struct mbuf *m, *nam, *control;
E 7
E 2
{
D 2
	return EPROTOTYPE;
E 2
I 2
	register int error = 0;
	register struct rawisopcb *rp = sotorawisopcb(so);

	rp = sotorawisopcb(so);
	switch (req) {

	case PRU_ATTACH:
		if (rp)
			panic("rip_attach");
		MALLOC(rp, struct rawisopcb *, sizeof *rp, M_PCB, M_WAITOK);
		if (rp == 0)
			return (ENOBUFS);
		bzero((caddr_t)rp, sizeof *rp);
		so->so_pcb = (caddr_t)rp;
		break;

	case PRU_DETACH:
		if (rp == 0)
			panic("rip_detach");
		if (rp->risop_isop.isop_options)
			m_freem(rp->risop_isop.isop_options);
		if (rp->risop_isop.isop_route.ro_rt)
			RTFREE(rp->risop_isop.isop_route.ro_rt);
		if (rp->risop_rcb.rcb_laddr)
			rp->risop_rcb.rcb_laddr = 0;
		/* free clnp cached hdr if necessary */
		if (rp->risop_isop.isop_clnpcache != NULL) {
			struct clnp_cache *clcp = 
				mtod(rp->risop_isop.isop_clnpcache, struct clnp_cache *);
			if (clcp->clc_hdr != NULL) {
				m_free(clcp->clc_hdr);
			}
			m_free(rp->risop_isop.isop_clnpcache);
		}
		if (rp->risop_isop.isop_optindex != NULL)
			m_free(rp->risop_isop.isop_optindex);

		break;

	case PRU_BIND:
	    {
		struct sockaddr_iso *addr = mtod(nam, struct sockaddr_iso *);

		if (nam->m_len != sizeof(*addr))
			return (EINVAL);
		if ((ifnet == 0) ||
		    (addr->siso_family != AF_ISO) ||
		    (addr->siso_addr.isoa_len  &&
		     ifa_ifwithaddr((struct sockaddr *)addr) == 0))
			return (EADDRNOTAVAIL);
		rp->risop_isop.isop_sladdr = *addr;
		rp->risop_rcb.rcb_laddr = (struct sockaddr *)
			(rp->risop_isop.isop_laddr = &rp->risop_isop.isop_sladdr);
		return (0);
	    }
	case PRU_CONNECT:
	    {
		struct sockaddr_iso *addr = mtod(nam, struct sockaddr_iso *);

		if ((nam->m_len > sizeof(*addr)) || (addr->siso_len > sizeof(*addr)))
			return (EINVAL);
		if (ifnet == 0)
			return (EADDRNOTAVAIL);
		if (addr->siso_family != AF_ISO)
		rp->risop_isop.isop_sfaddr = *addr;
		rp->risop_rcb.rcb_faddr = (struct sockaddr *)
			(rp->risop_isop.isop_faddr = &rp->risop_isop.isop_sfaddr);
		soisconnected(so);
		return (0);
	    }
	}
D 7
	error =  raw_usrreq(so, req, m, nam, rights, control);
E 7
I 7
	error =  raw_usrreq(so, req, m, nam, control);
E 7

	if (error && req == PRU_ATTACH && so->so_pcb)
		free((caddr_t)rp, M_PCB);
	return (error);
E 2
}
D 5
#endif	ISO
E 5
E 1
