/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * Copyright (c) 1985 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	in_pcb.c,v $
 * Revision 2.5  89/03/09  20:44:28  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:59:24  gm0w
 * 	Updated copyright.  All CMUCS changes made default except
 * 	code to allocate reserved ports that avoided our port space.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.3  88/08/24  01:59:31  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  18:52:34  mwyoung]
 * 
 * 09-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Revised default port allocation algorithm to implement
 *	SO_USEPRIV option (based on ECE implementation).
 *	[ V5.1(XF23) ]
 *
 * 16-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Merged in code for IP multicast.
 *
 * 15-Nov-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	NET_BUGFIX:  Installed bug fix for local interface address
 *	binding from UCB.
 *	[ V5.1(F1) ]
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 11-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_INET:  changed to use larger minimum port for default
 *	allocations so that these do not conflict with the CMU reserved
 *	non-privileged port area.
 *
 * 11-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_INET:  changed to use the SS_PRIV bit in the socket rather
 *	than u_uid to verify use of reserved port numbers.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)in_pcb.c	7.2 (Berkeley) 9/4/86
 */
 
#include <multibind.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/ioctl.h>
#include "in.h"
#include "in_systm.h"
#include <net/if.h>
#include <net/route.h>
#include "in_pcb.h"
#include "in_var.h"
#include <sys/protosw.h>


struct mbuf *hosts = 0;		/* for netstat */

struct	in_addr zeroin_addr;

in_pcballoc(so, head)
	struct socket *so;
	struct inpcb *head;
{
	struct mbuf *m;
	register struct inpcb *inp;

	m = m_getclr(M_DONTWAIT, MT_PCB);
	if (m == NULL)
		return (ENOBUFS);
	inp = mtod(m, struct inpcb *);
	inp->inp_head = head;
	inp->inp_socket = so;
	insque(inp, head);
	so->so_pcb = (caddr_t)inp;
	return (0);
}
	
in_pcbbind(inp, nam)
	register struct inpcb *inp;
	struct mbuf *nam;
{
	register struct socket *so = inp->inp_socket;
	register struct inpcb *head = inp->inp_head;
	register struct sockaddr_in *sin;
	u_short lport = 0;
#if	MULTIBIND
	struct inpcb *chkinpcb;
#endif	MULTIBIND

	if (in_ifaddr == 0)
		return (EADDRNOTAVAIL);
	if (inp->inp_lport || inp->inp_laddr.s_addr != INADDR_ANY)
		return (EINVAL);
	if (nam == 0)
		goto noname;
	sin = mtod(nam, struct sockaddr_in *);
	if (nam->m_len != sizeof (*sin))
		return (EINVAL);
	if (sin->sin_addr.s_addr != INADDR_ANY) {
		int tport = sin->sin_port;

		sin->sin_port = 0;		/* yech... */
		if (ifa_ifwithaddr((struct sockaddr *)sin) == 0)
			return (EADDRNOTAVAIL);
		sin->sin_port = tport;
	}
	lport = sin->sin_port;
	if (lport) {
		u_short aport = ntohs(lport);
		int wild = 0;

		/* GROSS */
		if (aport < IPPORT_RESERVED && u.u_uid != 0 && (so->so_state&SS_PRIV) == 0)
			return (EACCES);
		/* even GROSSER, but this is the Internet */
		if ((so->so_options & SO_REUSEADDR) == 0 &&
		    ((so->so_proto->pr_flags & PR_CONNREQUIRED) == 0 ||
		     (so->so_options & SO_ACCEPTCONN) == 0))
			wild = INPLOOKUP_WILDCARD;
#if	MULTIBIND
		    if (chkinpcb = in_pcblookup(head,
		        zeroin_addr, 0, sin->sin_addr, lport, wild)) {
			  if ((chkinpcb->inp_socket->so_options & SO_MULTIBIND)
			     && (so->so_options & SO_MULTIBIND)) {
			     /* Do nothing, since this is okay */
			  }
			  else return (EADDRINUSE);
		    }
#else	MULTIBIND
		    if (in_pcblookup(head,
		        zeroin_addr, 0, sin->sin_addr, lport, wild))
			    return (EADDRINUSE);
#endif	MULTIBIND
	}
	inp->inp_laddr = sin->sin_addr;
noname:
	if (lport == 0)
#ifdef	CMUCS
	{
		u_short minport, maxport, *portp;

		/*
		 *  Allocate from privileged port range if requested (and
		 *  permitted) otherwise from normal range (augmented to avoid
		 *  conflict with non-privileged CMU reserved ports).
		 */
		if (so->so_options&SO_USEPRIV) {
			if ((so->so_state&SS_PRIV) == 0)
				return(EACCES);
			portp = &head->inp_fport;
			minport = IPPORT_RESERVED-IPPORT_RESERVED/8;
			maxport = IPPORT_RESERVED;
		} else {
			portp = &head->inp_lport;
			minport = (IPPORT_RESERVED/2)*5;
			maxport = IPPORT_USERRESERVED;
		}
 		do {
			if ((*portp)++ < minport || *portp >= maxport)
				(*portp) = minport;
			lport = htons(*portp);
 		} while (in_pcblookup(head, 
 			    zeroin_addr, 0, inp->inp_laddr, lport, 0)); 
	}
#else	CMUCS
		do {
			if (head->inp_lport++ < IPPORT_RESERVED ||
			    head->inp_lport > IPPORT_USERRESERVED)
				head->inp_lport = IPPORT_RESERVED;
			lport = htons(head->inp_lport);
		} while (in_pcblookup(head,
			    zeroin_addr, 0, inp->inp_laddr, lport, 0));
#endif	CMUCS
	inp->inp_lport = lport;
	return (0);
}

/*
 * Connect from a socket to a specified address.
 * Both address and port must be specified in argument sin.
 * If don't have a local address for this socket yet,
 * then pick one.
 */
in_pcbconnect(inp, nam)
	struct inpcb *inp;
	struct mbuf *nam;
{
	struct in_ifaddr *ia;
	struct sockaddr_in *ifaddr;
	register struct sockaddr_in *sin = mtod(nam, struct sockaddr_in *);

	if (nam->m_len != sizeof (*sin))
		return (EINVAL);
	if (sin->sin_family != AF_INET)
		return (EAFNOSUPPORT);
	if (sin->sin_port == 0)
		return (EADDRNOTAVAIL);
	if (in_ifaddr) {
		/*
		 * If the destination address is INADDR_ANY,
		 * use the primary local address.
		 * If the supplied address is INADDR_BROADCAST,
		 * and the primary interface supports broadcast,
		 * choose the broadcast address for that interface.
		 */
#define satosin(sa)	((struct sockaddr_in *)(sa))
		if (sin->sin_addr.s_addr == INADDR_ANY)
		    sin->sin_addr = IA_SIN(in_ifaddr)->sin_addr;
		else if (sin->sin_addr.s_addr == (u_long)INADDR_BROADCAST &&
		  (in_ifaddr->ia_ifp->if_flags & IFF_BROADCAST))
		    sin->sin_addr = satosin(&in_ifaddr->ia_broadaddr)->sin_addr;
	}
	if (inp->inp_laddr.s_addr == INADDR_ANY) {
		register struct route *ro;
		struct ifnet *ifp;

		ia = (struct in_ifaddr *)0;
		/* 
		 * If route is known or can be allocated now,
		 * our src addr is taken from the i/f, else punt.
		 */
		ro = &inp->inp_route;
		if (ro->ro_rt &&
		    satosin(&ro->ro_dst)->sin_addr.s_addr !=
		    sin->sin_addr.s_addr) {
			RTFREE(ro->ro_rt);
			ro->ro_rt = (struct rtentry *)0;
		}
		if ((inp->inp_socket->so_options & SO_DONTROUTE) == 0 && /*XXX*/
		    (ro->ro_rt == (struct rtentry *)0 ||
 		    ro->ro_rt->rt_ifp == (struct ifnet *)0)) {
			/* No route yet, so try to acquire one */
			ro->ro_dst.sa_family = AF_INET;
			((struct sockaddr_in *) &ro->ro_dst)->sin_addr =
				sin->sin_addr;
			rtalloc(ro);
 		}
 		/*
 		 * If we found a route, use the address
 		 * corresponding to the outgoing interface
 		 * unless it is the loopback (in case a route
 		 * to our address on another net goes to loopback).
 		 */
 		if (ro->ro_rt && (ifp = ro->ro_rt->rt_ifp) &&
 		    (ifp->if_flags & IFF_LOOPBACK) == 0)
 			for (ia = in_ifaddr; ia; ia = ia->ia_next)
 				if (ia->ia_ifp == ifp)
 					break;
		if (ia == 0) {
			ia = (struct in_ifaddr *)
			    ifa_ifwithdstaddr((struct sockaddr *)sin);
			if (ia == 0)
				ia = in_iaonnetof(in_netof(sin->sin_addr));
			if (ia == 0)
				ia = in_ifaddr;
			if (ia == 0)
				return (EADDRNOTAVAIL);
		}
		ifaddr = (struct sockaddr_in *)&ia->ia_addr;
	}
	if (in_pcblookup(inp->inp_head,
	    sin->sin_addr,
	    sin->sin_port,
	    inp->inp_laddr.s_addr ? inp->inp_laddr : ifaddr->sin_addr,
	    inp->inp_lport,
	    0))
		return (EADDRINUSE);
	if (inp->inp_laddr.s_addr == INADDR_ANY) {
		if (inp->inp_lport == 0)
			(void)in_pcbbind(inp, (struct mbuf *)0);
		inp->inp_laddr = ifaddr->sin_addr;
	}
	inp->inp_faddr = sin->sin_addr;
	inp->inp_fport = sin->sin_port;
	return (0);
}

in_pcbdisconnect(inp)
	struct inpcb *inp;
{

	inp->inp_faddr.s_addr = INADDR_ANY;
	inp->inp_fport = 0;
	if (inp->inp_socket->so_state & SS_NOFDREF)
		in_pcbdetach(inp);
}

in_pcbdetach(inp)
	struct inpcb *inp;
{
	struct socket *so = inp->inp_socket;

	so->so_pcb = 0;
	sofree(so);
	if (inp->inp_options)
		(void)m_free(inp->inp_options);
	if (inp->inp_route.ro_rt)
		rtfree(inp->inp_route.ro_rt);
	remque(inp);
	(void) m_free(dtom(inp));
}

in_setsockaddr(inp, nam)
	register struct inpcb *inp;
	struct mbuf *nam;
{
	register struct sockaddr_in *sin = mtod(nam, struct sockaddr_in *);
	
	nam->m_len = sizeof (*sin);
	sin = mtod(nam, struct sockaddr_in *);
	bzero((caddr_t)sin, sizeof (*sin));
	sin->sin_family = AF_INET;
	sin->sin_port = inp->inp_lport;
	sin->sin_addr = inp->inp_laddr;
}

in_setpeeraddr(inp, nam)
	register struct inpcb *inp;
	struct mbuf *nam;
{
	register struct sockaddr_in *sin = mtod(nam, struct sockaddr_in *);
	
	nam->m_len = sizeof (*sin);
	sin = mtod(nam, struct sockaddr_in *);
	bzero((caddr_t)sin, sizeof (*sin));
	sin->sin_family = AF_INET;
	sin->sin_port = inp->inp_fport;
	sin->sin_addr = inp->inp_faddr;
}

/*
 * Pass some notification to all connections of a protocol
 * associated with address dst.  Call the protocol specific
 * routine (if any) to handle each connection.
 */
in_pcbnotify(head, dst, errno, notify)
	struct inpcb *head;
	register struct in_addr *dst;
	int errno, (*notify)();
{
	register struct inpcb *inp, *oinp;
	int s = splimp();

	for (inp = head->inp_next; inp != head;) {
		if (inp->inp_faddr.s_addr != dst->s_addr ||
		    inp->inp_socket == 0) {
			inp = inp->inp_next;
			continue;
		}
		if (errno) 
			inp->inp_socket->so_error = errno;
		oinp = inp;
		inp = inp->inp_next;
		if (notify)
			(*notify)(oinp);
	}
	splx(s);
}

/*
 * Check for alternatives when higher level complains
 * about service problems.  For now, invalidate cached
 * routing information.  If the route was created dynamically
 * (by a redirect), time to try a default gateway again.
 */
in_losing(inp)
	struct inpcb *inp;
{
	register struct rtentry *rt;

	if ((rt = inp->inp_route.ro_rt)) {
		if (rt->rt_flags & RTF_DYNAMIC)
			(void) rtrequest((int)SIOCDELRT, rt);
		rtfree(rt);
		inp->inp_route.ro_rt = 0;
		/*
		 * A new route can be allocated
		 * the next time output is attempted.
		 */
	}
}

/*
 * After a routing change, flush old routing
 * and allocate a (hopefully) better one.
 */
in_rtchange(inp)
	register struct inpcb *inp;
{
	if (inp->inp_route.ro_rt) {
		rtfree(inp->inp_route.ro_rt);
		inp->inp_route.ro_rt = 0;
		/*
		 * A new route can be allocated the next time
		 * output is attempted.
		 */
	}
}

struct inpcb *
in_pcblookup(head, faddr, fport, laddr, lport, flags)
	struct inpcb *head;
	struct in_addr faddr, laddr;
	u_short fport, lport;
	int flags;
{
	register struct inpcb *inp, *match = 0;
	int matchwild = 3, wildcard;

	for (inp = head->inp_next; inp != head; inp = inp->inp_next) {
		if (inp->inp_lport != lport)
			continue;
		wildcard = 0;
		if (inp->inp_laddr.s_addr != INADDR_ANY) {
			if (laddr.s_addr == INADDR_ANY)
				wildcard++;
			else if (inp->inp_laddr.s_addr != laddr.s_addr)
				continue;
		} else {
			if (laddr.s_addr != INADDR_ANY)
				wildcard++;
		}
		if (inp->inp_faddr.s_addr != INADDR_ANY) {
			if (faddr.s_addr == INADDR_ANY)
				wildcard++;
			else if (inp->inp_faddr.s_addr != faddr.s_addr ||
			    inp->inp_fport != fport)
				continue;
		} else {
			if (faddr.s_addr != INADDR_ANY)
				wildcard++;
		}
		if (wildcard && (flags & INPLOOKUP_WILDCARD) == 0)
			continue;
		if (wildcard < matchwild) {
			match = inp;
			matchwild = wildcard;
			if (matchwild == 0)
				break;
		}
	}
	return (match);
}
