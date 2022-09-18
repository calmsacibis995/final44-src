/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	raw_cb.c,v $
 * Revision 2.5  89/03/09  20:39:34  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:54:28  gm0w
 * 	Added new copyright, fixed conditionals.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.3  89/01/18  00:52:40  jsb
 * 	Merged in NeXT's changes.
 * 	[89/01/17  10:38:07  jsb]
 * 
 * Revision 2.2  88/08/24  01:54:16  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:09:19  mwyoung]
 * 
 *
 * 13-Aug-87  Peter King (king) at NeXT
 *	SUN_RPC:  Increased size of socket receive buffer to hold 
 *		     enough space for the socket address.
 *
 * 16-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Added support for IP Multicast.
 *
 * 06-May-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	DLI:  Add data-link protocol support to raw_bind().
 *	[ V5.1(F10) ]
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 */
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)raw_cb.c	7.1 (Berkeley) 6/4/86
 */
 
#include <dli.h>
#include <ttlcontrol.h>
#include <sun_rpc.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/route.h>
#include <net/raw_cb.h>
#include <netinet/in.h>

#ifdef	MACH
#else	MACH
#include <vax/mtpr.h>
#endif	MACH

#if	TTLCONTROL
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#endif	TTLCONTROL

/*
 * Routines to manage the raw protocol control blocks. 
 *
 * TODO:
 *	hash lookups by protocol family/protocol + address family
 *	take care of unique address problems per AF?
 *	redo address binding to allow wildcards
 */

/*
 * Allocate a control block and a nominal amount
 * of buffer space for the socket.
 */
raw_attach(so, proto)
	register struct socket *so;
	int proto;
{
	struct mbuf *m;
	register struct rawcb *rp;

	m = m_getclr(M_DONTWAIT, MT_PCB);
	if (m == 0)
		return (ENOBUFS);
	if (sbreserve(&so->so_snd, RAWSNDQ) == 0)
		goto bad;
#if	SUN_RPC
        /* recvfrom needs extra space for address */
        if (sbreserve(&so->so_rcv, RAWRCVQ + sizeof(struct sockaddr)) == 0)
#else	SUN_RPC
	if (sbreserve(&so->so_rcv, RAWRCVQ) == 0)
#endif	SUN_RPC
		goto bad2;
	rp = mtod(m, struct rawcb *);
	rp->rcb_socket = so;
	so->so_pcb = (caddr_t)rp;
	rp->rcb_pcb = 0;
	rp->rcb_proto.sp_family = so->so_proto->pr_domain->dom_family;
	rp->rcb_proto.sp_protocol = proto;
#if	TTLCONTROL
	rp->rcb_ttl = MAXTTL;
#endif	TTLCONTROL
	insque(rp, &rawcb);
	return (0);
bad2:
	sbrelease(&so->so_snd);
bad:
	(void) m_free(m);
	return (ENOBUFS);
}

/*
 * Detach the raw connection block and discard
 * socket resources.
 */
raw_detach(rp)
	register struct rawcb *rp;
{
	struct socket *so = rp->rcb_socket;

	if (rp->rcb_route.ro_rt)
		rtfree(rp->rcb_route.ro_rt);
	so->so_pcb = 0;
	sofree(so);
	remque(rp);
	if (rp->rcb_options)
		m_freem(dtom(rp->rcb_options));
	m_freem(dtom(rp));
}

/*
 * Disconnect and possibly release resources.
 */
raw_disconnect(rp)
	struct rawcb *rp;
{

	rp->rcb_flags &= ~RAW_FADDR;
	if (rp->rcb_socket->so_state & SS_NOFDREF)
		raw_detach(rp);
}

raw_bind(so, nam)
	register struct socket *so;
	struct mbuf *nam;
{
	struct sockaddr *addr = mtod(nam, struct sockaddr *);
	register struct rawcb *rp;

	if (ifnet == 0)
		return (EADDRNOTAVAIL);
/* BEGIN DUBIOUS */
	/*
	 * Should we verify address not already in use?
	 * Some say yes, others no.
	 */
	switch (addr->sa_family) {

#ifdef	INET
	case AF_IMPLINK:
	case AF_INET: {
		if (((struct sockaddr_in *)addr)->sin_addr.s_addr &&
		    ifa_ifwithaddr(addr) == 0)
			return (EADDRNOTAVAIL);
		break;
	}
#endif
#if	DLI
	case AF_DLI: {
		if ( ifa_ifwithaddr(addr) == 0)
			return (EADDRNOTAVAIL);
		break;
	}
#endif	DLI

	default:
		return (EAFNOSUPPORT);
	}
/* END DUBIOUS */
	rp = sotorawcb(so);
	bcopy((caddr_t)addr, (caddr_t)&rp->rcb_laddr, sizeof (*addr));
	rp->rcb_flags |= RAW_LADDR;
	return (0);
}

/*
 * Associate a peer's address with a
 * raw connection block.
 */
raw_connaddr(rp, nam)
	struct rawcb *rp;
	struct mbuf *nam;
{
	struct sockaddr *addr = mtod(nam, struct sockaddr *);

	bcopy((caddr_t)addr, (caddr_t)&rp->rcb_faddr, sizeof(*addr));
	rp->rcb_flags |= RAW_FADDR;
}
