/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Tunneling interface driver.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <machine/cpu.h>

#include <net/if.h>
#include <net/if_types.h>
#include <net/netisr.h>
#include <net/route.h>
#include <net/bpf.h>

#ifdef	INET
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#endif

#ifdef NS
#include <netns/ns.h>
#include <netns/ns_if.h>
#include <netns/idp.h>
#endif

#ifdef ISO
#include <netiso/iso.h>
#include <netiso/iso_var.h>
#include <netiso/iso_pcb.h>
#endif

#include "bpfilter.h"

#define	TUMTU	(1024*63)

struct	ifnet tuif;

struct	tu_llinfo {
	u_int	ti_af;
	caddr_t	ti_data;		/* what to prepend to outgoing dg */
	u_int	ti_datalen;		/* length of the header */
	struct	route ti_ro;		/* for sending output datagram */
	caddr_t	ti_pcb;			/* for ISO, etc. */
	struct	sockaddr *ti_srcaddr;	/* when doing NAT */
};
int	tuioctl __P((struct ifnet *, int, caddr_t));
int	tuoutput __P((struct ifnet *,
		      struct mbuf *, struct sockaddr *, struct rtentry *));

/* ARGSUSED */
void
tuattach(n)
	int n;
{
	register struct ifnet *ifp = &tuif;

#ifdef lint
	n = n;			/* Highlander: there can only be one... */
#endif
	ifp->if_name = "tu";
	ifp->if_mtu = TUMTU;
	ifp->if_flags = IFF_MULTICAST;
	ifp->if_ioctl = tuioctl;
	ifp->if_output = tuoutput;
	ifp->if_type = IFT_LOOP;
	ifp->if_hdrlen = 0;
	ifp->if_addrlen = 0;
	if_attach(ifp);
#if NBPFILTER > 0
	bpfattach(&ifp->if_bpf, ifp, DLT_NULL, sizeof(u_int));
#endif
}

int
tuoutput(ifp, m, dst, rt)
	struct ifnet *ifp;
	register struct mbuf *m;
	struct sockaddr *dst;
	register struct rtentry *rt;
{
	int	s, pktlen, error;
	struct	tu_llinfo *ti;
	struct	rtentry *ert;

	if ((m->m_flags & M_PKTHDR) == 0)
		panic("tuoutput no HDR");
	ifp->if_lastchange = time;
#if NBPFILTER > 0
	if (tuif.if_bpf) {
		/*
		 * We need to prepend the address family as
		 * a four byte field.  Cons up a dummy header
		 * to pacify bpf.  This is safe because bpf
		 * will only read from the mbuf (i.e., it won't
		 * try to free it or keep a pointer a to it).
		 */
		struct mbuf m0;
		u_int af = dst->sa_family;

		m0.m_next = m;
		m0.m_len = 4;
		m0.m_data = (char *)&af;
		
		bpf_mtap(tuif.if_bpf, &m0);
	}
#endif
	if (rt == 0) {
	unreach:
		m_freem(m);
		return (EHOSTUNREACH);
	}
	if ((rt->rt_flags & RTF_GATEWAY) && rt->rt_gwroute)
		rt = rt->rt_gwroute; /* Share PCB's for common next hops */
	if ((ti = (struct tu_llinfo *)rt->rt_llinfo) == 0)
		goto unreach;
	pktlen = m->m_pkthdr.len;
	switch  (rt->rt_gateway->sa_family) {
#ifdef INET
	case AF_INET:
	    {
		register struct ip *ip = (struct ip *)ti->ti_data;

		ip->ip_len = pktlen + ti->ti_datalen;
		if ((m = m_prepend(m, ti->ti_datalen, M_DONTWAIT)) == 0)
			return (ENOBUFS);
		m_copyback(m, 0, ti->ti_datalen, ti->ti_data);
		error =  ip_output(m, (struct mbuf *)0, &ti->ti_ro, 0, NULL);
		break;

	    }
#endif /* INET */
#ifdef ISO
	case AF_ISO:
		if (dst->sa_family = AF_INET) {
			if ((m = m_prepend(m, sizeof(u_char), M_DONTWAIT)) == 0)
				return (ENOBUFS);
			*mtod(m, u_char *) = 0xcc;
		}
		error = clnp_output(m, (struct isopcb *)ti->ti_pcb, pktlen, 0);
		break;
#endif /* ISO */
	}
	if (error)
		ifp->if_oerrors++;
	return (error);
}

u_char eonhdr[4] = { 1, 0, 0xfc, 2};

/* ARGSUSED */
void
turtrequest(cmd, rt, info)
	int cmd;
	struct rtentry *rt;
	struct rt_addrinfo *info;
{
	struct tu_llinfo *ti;

	if ((rt->rt_flags & RTF_GATEWAY) && rt->rt_gwroute)
		return;
	switch (cmd) {
	case RTM_ADD:
	case RTM_ADDPKT:
	case RTM_RESOLVE:

		MALLOC(ti, struct tu_llinfo *, sizeof(*ti),
				M_RTABLE, M_WAITOK);
		if (ti == 0)
			return;
		bzero((caddr_t)ti, sizeof(*ti));
		switch (rt->rt_gateway->sa_family) {
#ifdef INET
#define SINADDR(s) ((struct sockaddr_in *)(s))->sin_addr
		case AF_INET:
		    {
			struct ip *ip;
			MALLOC(ip, struct ip *, 8 + sizeof(*ip),
					M_RTABLE, M_WAITOK);
			if (ip == 0) {
				free(ti, M_RTABLE);
				return;
			}
			bzero((caddr_t)ip, sizeof(*ip));
			ti->ti_data = (caddr_t)ip;
			ti->ti_datalen = sizeof(ip);
			ip->ip_src = SINADDR(rt->rt_ifa->ifa_addr);
			ip->ip_dst = SINADDR(rt->rt_gateway);
			ip->ip_ttl = MAXTTL;
			switch (rt_key(rt)->sa_family) {
#if defined(EON) && defined(ISO)
			case AF_ISO:
				ti->ti_datalen += 4;
				bcopy((caddr_t)eonhdr, (caddr_t)(ip + 1), 4);
				ip->ip_p = IPPROTO_EON;
				break;

#endif
#if defined (NS) && defined(NSIP)
			case AF_NS:
				ip->ip_p = IPPROTO_IDP;
				break;
#endif
			case AF_INET:
				ip->ip_p = IPPROTO_ENCAP;
			
			}
			break;
		    }
#endif /* INET */
#ifdef ISO
		case AF_ISO:
		    {
			struct isopcb *isop;

			MALLOC(isop, struct isopcb *, sizeof(*isop),
					M_PCB, M_NOWAIT);
			if (isop == NULL) {
				free(ti, M_RTABLE);
				return;
			}
			bzero((caddr_t)isop, sizeof(*isop));
#define SISO(s) ((struct sockaddr_iso *)(s))
			isop->isop_laddr = &isop->isop_sladdr;
			isop->isop_faddr = &isop->isop_sfaddr;
			isop->isop_sfaddr = *SISO(rt->rt_gateway);
			isop->isop_sladdr = *SISO(rt->rt_ifa->ifa_addr);
			isop->isop_next = isop->isop_prev = isop;
			ti->ti_pcb = (caddr_t)isop;
			break;

		    }
#endif /* ISO */
		}
		break;

	case RTM_DELETE:
	case RTM_DELPKT:
		switch (rt->rt_gateway->sa_family) {
#ifdef INET
		case AF_INET:
			if (ti->ti_ro.ro_rt)
				rtfree(ti->ti_ro.ro_rt);
			free(ti->ti_data, M_RTABLE);
			break;
#endif /* INET */
#ifdef ISO
		case AF_ISO:
			iso_pcbdetach((struct isopcb *)ti->ti_pcb);
			break;
#endif /* ISO */
		}
		free(ti, M_RTABLE);
	}
}

/*
 * Process an ioctl request.
 */
/* ARGSUSED */
int
tuioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register struct ifaddr *ifa;
	register struct ifreq *ifr;
	register int error = 0;

	switch (cmd) {

	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		ifa = (struct ifaddr *)data;
		if (ifa != 0)
			ifa->ifa_rtrequest = turtrequest;
		/*
		 * Everything else is done at a higher level.
		 */

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		break;

	default:
		error = EINVAL;
	}
	return (error);
}

/*
 * Associated protocol specific input routines.
 */

#if defined(ISO) && defined (EON)
int eonerrors = 0;

eoninput(m, iphlen)
	register struct mbuf *m;
	int iphlen;
{
#define EONIPLEN (sizeof(struct ip) + sizeof(eonhdr))
	register struct ip *ip;
	int s;
	struct snpa_hdr snh;
	struct clnl_fixed *clnl;

	if (m == 0)
		return;
	if (iphlen > sizeof (struct ip))
		ip_stripoptions(m, (struct mbuf *)0);
	if (m->m_len < EONIPLEN) {
		if ((m = m_pullup(m, EONIPLEN)) == 0) {
		drop:	tuif.if_ierrors++;
			eonerrors++;
			m_freem(m);
			return;
		}
	}
	tuif.if_ibytes += m->m_pkthdr.len;
	tuif.if_lastchange = time;
	ip = mtod(m, struct ip *);

	m->m_data += EONIPLEN;
	m->m_len -= EONIPLEN;
	m->m_pkthdr.len -= EONIPLEN;
	m->m_flags &= ~(M_BCAST|M_MCAST);
		
	/* checks for debugging */
	if (bcmp((caddr_t)(ip + 1), eonhdr, sizeof(eonhdr)))
		goto drop;
	tuif.if_ipackets++;

	bzero((caddr_t)&snh, sizeof(snh));
	snh.snh_ifp = m->m_pkthdr.rcvif = &tuif; /* KLUDGE */
	bcopy((caddr_t)&ip->ip_src, snh.snh_shost, sizeof(ip->ip_src));
	bcopy((caddr_t)&ip->ip_dst, snh.snh_dhost, sizeof(ip->ip_src));
	clnl_input1(m, &snh);
}

/* ARGSUSED */
int
eonctlinput(cmd, sin, badip)
	int cmd;
	struct sockaddr_in *sin;
	caddr_t badip;
{
	extern u_char inetctlerrmap[];


	if (cmd < 0 || cmd > PRC_NCMDS)
		return 0;

	switch (cmd) {

		case	PRC_QUENCH:
		case	PRC_QUENCH2:
			/* TODO: set the dec bit */
			break;
		case	PRC_TIMXCEED_REASS:
		case	PRC_ROUTEDEAD:
		case	PRC_HOSTUNREACH:
		case	PRC_UNREACH_NET:
		case	PRC_IFDOWN:
		case	PRC_UNREACH_HOST:
		case	PRC_HOSTDEAD:
		case	PRC_TIMXCEED_INTRANS:
			/* TODO: mark the link down */
			break;

		case	PRC_UNREACH_PROTOCOL:
		case	PRC_UNREACH_PORT:
		case	PRC_UNREACH_SRCFAIL:
		case	PRC_REDIRECT_NET:
		case	PRC_REDIRECT_HOST:
		case	PRC_REDIRECT_TOSNET:
		case	PRC_REDIRECT_TOSHOST:
		case	PRC_MSGSIZE:
		case	PRC_PARAMPROB:
			/* printf("eonctlinput: ICMP cmd 0x%x\n", cmd );*/
		break;
	}
	return 0;
}
#endif

#if defined(NS) && defined(NSIP)
struct mbuf *nsip_badlen;
struct mbuf *nsip_lastin;
int nsip_hold_input;
extern struct ifqueue nsintrq;

idpip_input(m, ihlen)
	register struct mbuf *m;
	int ihlen;
{
	register struct ip *ip;
	register struct ifqueue *ifq = &nsintrq;
	int len, s;

	if (nsip_hold_input) {
		if (nsip_lastin) {
			m_freem(nsip_lastin);
		}
		nsip_lastin = m_copym(m, 0, (int)M_COPYALL, M_DONTWAIT);
	}
	/*
	 * Get IP and IDP header together in first mbuf.
	 */
	tuif.if_ipackets++;
	s = sizeof (struct ip) + sizeof (struct idp);
	if (((m->m_flags & M_EXT) || m->m_len < s) &&
	    (m = m_pullup(m, s)) == 0) {
		tuif.if_ierrors++;
		return;
	}
	ip = mtod(m, struct ip *);
	if (ip->ip_hl > ihlen) {
		ip_stripoptions(m, (struct mbuf *)0);
		if (m->m_len < s) {
			if ((m = m_pullup(m, s)) == 0) {
				tuif.if_ierrors++;
				return;
			}
			ip = mtod(m, struct ip *);
		}
	}
	/*
	 * Make mbuf data length reflect IDP length.
	 * If not enough data to reflect IDP length, drop.
	 */
	m->m_data += sizeof (struct ip);
	m->m_len -= sizeof (struct ip);
	m->m_pkthdr.len -= sizeof (struct ip);
	m->m_pkthdr.rcvif = &tuif;

	/*
	 * Deliver to NS
	 */
	s = splimp();
	if (IF_QFULL(ifq)) {
		IF_DROP(ifq);
bad:
		m_freem(m);
		splx(s);
		return;
	}
	IF_ENQUEUE(ifq, m);
	splx(s);
	nsintr();
}

nsip_rtchange(dst)
	register struct in_addr *dst;
{
	register struct ifnet_en *ifn;

#ifdef notdef
	/* should maintain list of encapsulating routes, and do a search
	   to update everything using this as a gateway */
	for (ifn = nsip_list; ifn; ifn = ifn->ifen_next) {
		if (ifn->ifen_dst.s_addr == dst->s_addr &&
			ifn->ifen_route.ro_rt) {
				RTFREE(ifn->ifen_route.ro_rt);
				ifn->ifen_route.ro_rt = 0;
		}
	}
#endif
}

/* ARGSUSED */
nsip_ctlinput(cmd, sa, badip)
	int cmd;
	struct sockaddr *sa;
	caddr_t badip;
{
	extern u_char inetctlerrmap[];
	struct sockaddr_in *sin;
	int in_rtchange();

	if ((unsigned)cmd >= PRC_NCMDS)
		return;
	if (sa->sa_family != AF_INET && sa->sa_family != AF_IMPLINK)
		return;
	sin = (struct sockaddr_in *)sa;
	if (sin->sin_addr.s_addr == INADDR_ANY)
		return;

	switch (cmd) {

	case PRC_ROUTEDEAD:
	case PRC_REDIRECT_NET:
	case PRC_REDIRECT_HOST:
	case PRC_REDIRECT_TOSNET:
	case PRC_REDIRECT_TOSHOST:
		nsip_rtchange(&sin->sin_addr);
		break;
	}
}
#endif
