/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	udp_usrreq.c,v $
 * Revision 2.5  89/03/09  20:47:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:02:36  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.3  89/01/18  00:54:26  jsb
 * 	Merged in NeXT's changes.
 * 	[89/01/17  10:45:31  jsb]
 * 
 * Revision 2.2  88/08/24  02:02:50  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  18:55:45  mwyoung]
 * 
 * 20-Oct-87  Peter King (king) at NeXT
 *	SUN_RPC: Increase packet size.
 *
 * 16-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Merged in code for IP multicast.
 *
 * 21-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_INET: Added temporary check against sending ICMP replies to
 *	a wide variety of broadcast addresses until this is handled
 *	better at a lower level.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)udp_usrreq.c	7.1 (Berkeley) 6/5/86
 */
#include <multibind.h>
#include <ttlcontrol.h>
#include <sun_rpc.h>

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/stat.h>

#include <net/if.h>
#include <net/route.h>

#include "in.h"
#include "in_pcb.h"
#include "in_systm.h"
#ifdef	MACH
#include "in_var.h"
#endif	MACH
#include "ip.h"
#include "ip_var.h"
#include "ip_icmp.h"
#include "udp.h"
#include "udp_var.h"


/*
 * UDP protocol implementation.
 * Per RFC 768, August, 1980.
 */
udp_init()
{

	udb.inp_next = udb.inp_prev = &udb;
}

#ifndef	COMPAT_42
int	udpcksum = 1;
#else
int	udpcksum = 0;		/* XXX */
#endif

struct	sockaddr_in udp_in = { AF_INET };

udp_input(m0, ifp)
	struct mbuf *m0;
	struct ifnet *ifp;
{
	register struct udpiphdr *ui;
	register struct inpcb *inp;
	register struct mbuf *m;
	int len;
	struct ip ip;
#if	MULTIBIND
	struct socket *last;
	struct in_addr faddr, laddr;
	u_short fport;
#endif	MULTIBIND

	/*
	 * Get IP and UDP header together in first mbuf.
	 */
	m = m0;
	if ((m->m_off > MMAXOFF || m->m_len < sizeof (struct udpiphdr)) &&
	    (m = m_pullup(m, sizeof (struct udpiphdr))) == 0) {
		udpstat.udps_hdrops++;
		return;
	}
	ui = mtod(m, struct udpiphdr *);
	if (((struct ip *)ui)->ip_hl > (sizeof (struct ip) >> 2))
		ip_stripoptions((struct ip *)ui, (struct mbuf *)0);

	/*
	 * Make mbuf data length reflect UDP length.
	 * If not enough data to reflect UDP length, drop.
	 */
	len = ntohs((u_short)ui->ui_ulen);
	if (((struct ip *)ui)->ip_len != len) {
		if (len > ((struct ip *)ui)->ip_len) {
			udpstat.udps_badlen++;
			goto bad;
		}
		m_adj(m, len - ((struct ip *)ui)->ip_len);
		/* ((struct ip *)ui)->ip_len = len; */
	}
	/*
	 * Save a copy of the IP header in case we want restore it for ICMP.
	 */
	ip = *(struct ip*)ui;

	/*
	 * Checksum extended UDP header and data.
	 */
	if (udpcksum && ui->ui_sum) {
		ui->ui_next = ui->ui_prev = 0;
		ui->ui_x1 = 0;
		ui->ui_len = ui->ui_ulen;
		if (ui->ui_sum = in_cksum(m, len + sizeof (struct ip))) {
			udpstat.udps_badsum++;
			m_freem(m);
			return;
		}
	}

#if	MULTIBIND
	    udp_in.sin_port = ui->ui_sport;
	    udp_in.sin_addr = ui->ui_src;
	    m->m_len -= sizeof (struct udpiphdr);
	    m->m_off += sizeof (struct udpiphdr);
	    faddr = ui->ui_src;
	    fport = ui->ui_sport;
	    laddr = ui->ui_dst;

	    last = 0;
	    for (inp = udb.inp_next; inp != &udb; inp = inp->inp_next) {
		if (inp->inp_lport != ui->ui_dport) continue;

		if (inp->inp_laddr.s_addr != INADDR_ANY) {
			if (inp->inp_laddr.s_addr != laddr.s_addr)
				continue;
		}
		if (inp->inp_faddr.s_addr != INADDR_ANY) {
			if (inp->inp_faddr.s_addr != faddr.s_addr ||
			    inp->inp_fport != fport)
				continue;
		}

		if (last) {
		    struct mbuf *n;

		    if ((n = m_copy(m,0,(int) M_COPYALL)) != NULL) {
			if (sbappendaddr(&last->so_rcv,(struct sockaddr *)&udp_in,
			    n, (struct mbuf *) 0) == 0) {
				if (n) m_freem(n);
			}
			else sorwakeup(last);
		    }
		}
	        last = inp->inp_socket;
	    }

	    if (last) {
		if (sbappendaddr(&last->so_rcv,(struct sockaddr *)&udp_in,
		    m, (struct mbuf *) 0) == 0) {
			if (m) m_freem(m);
		}
		else {
		    sorwakeup(last);
		}
	    } 
	    else
bad:
		if (m) m_freem(m);
#else	MULTIBIND
	/*
	 * Locate pcb for datagram.
	 */
	inp = in_pcblookup(&udb,
	    ui->ui_src, ui->ui_sport, ui->ui_dst, ui->ui_dport,
		INPLOOKUP_WILDCARD);
	if (inp == 0) {
#ifdef	MACH
		register struct in_ifaddr *ia;
	        u_long dst = ntohl(ui->ui_dst.s_addr);

		/*
		 *  Temporary check for many different flavors of broadcast addresses
		 *  (the drivers should really pass a broadcast indication up to the
		 *  IP level rather than having to go through these contortions).
		 */
		for (ia = in_ifaddr; ia; ia = ia->ia_next)
		{
			if ((ia->ia_ifp->if_flags & IFF_BROADCAST))
			{
				u_long match;

				/*
				 *  Look for a match on our network number with
				 *  a host of-all 0's or all-1's.
				 */
				match = (ia->ia_net^dst);
				if (match == ~ia->ia_netmask || match == 0)
				    goto bad;
				/*
				 *  Look for a match on our sub-network number with
				 *  a sub-host of-all 0's or all-1's.
				 */
				match = (ia->ia_subnet^dst);
				if (match == ~ia->ia_subnetmask || match == 0)
				    goto bad;
			}
		}
		if (ui->ui_dst.s_addr == (u_long)INADDR_BROADCAST)
			goto bad;
		if (ui->ui_dst.s_addr == INADDR_ANY)
			goto bad;
#endif	MACH
		/* don't send ICMP response for broadcast packet */
		if (in_broadcast(ui->ui_dst))
			goto bad;
		*(struct ip *)ui = ip;
		icmp_error((struct ip *)ui, ICMP_UNREACH, ICMP_UNREACH_PORT,
		    ifp);
		return;
	}

	/*
	 * Construct sockaddr format source address.
	 * Stuff source address and datagram in user buffer.
	 */
	udp_in.sin_port = ui->ui_sport;
	udp_in.sin_addr = ui->ui_src;
	m->m_len -= sizeof (struct udpiphdr);
	m->m_off += sizeof (struct udpiphdr);
	if (sbappendaddr(&inp->inp_socket->so_rcv, (struct sockaddr *)&udp_in,
	    m, (struct mbuf *)0) == 0)
		goto bad;
	sorwakeup(inp->inp_socket);
	return;
bad:
	m_freem(m);
#endif	MULTIBIND
}

/*
 * Notify a udp user of an asynchronous error;
 * just wake up so that he can collect error status.
 */
udp_notify(inp)
	register struct inpcb *inp;
{

	sorwakeup(inp->inp_socket);
	sowwakeup(inp->inp_socket);
}

udp_ctlinput(cmd, sa)
	int cmd;
	struct sockaddr *sa;
{
	extern u_char inetctlerrmap[];
	struct sockaddr_in *sin;
	int in_rtchange();

	if ((unsigned)cmd > PRC_NCMDS)
		return;
	if (sa->sa_family != AF_INET && sa->sa_family != AF_IMPLINK)
		return;
	sin = (struct sockaddr_in *)sa;
	if (sin->sin_addr.s_addr == INADDR_ANY)
		return;

	switch (cmd) {

	case PRC_QUENCH:
		break;

	case PRC_ROUTEDEAD:
	case PRC_REDIRECT_NET:
	case PRC_REDIRECT_HOST:
	case PRC_REDIRECT_TOSNET:
	case PRC_REDIRECT_TOSHOST:
		in_pcbnotify(&udb, &sin->sin_addr, 0, in_rtchange);
		break;

	default:
		if (inetctlerrmap[cmd] == 0)
			return;		/* XXX */
		in_pcbnotify(&udb, &sin->sin_addr, (int)inetctlerrmap[cmd],
			udp_notify);
	}
}

udp_output(inp, m0)
	register struct inpcb *inp;
	struct mbuf *m0;
{
	register struct mbuf *m;
	register struct udpiphdr *ui;
	register int len = 0;

	/*
	 * Calculate data length and get a mbuf
	 * for UDP and IP headers.
	 */
	for (m = m0; m; m = m->m_next)
		len += m->m_len;
	MGET(m, M_DONTWAIT, MT_HEADER);
	if (m == 0) {
		m_freem(m0);
		return (ENOBUFS);
	}

	/*
	 * Fill in mbuf with extended UDP header
	 * and addresses and length put into network format.
	 */
	m->m_off = MMAXOFF - sizeof (struct udpiphdr);
	m->m_len = sizeof (struct udpiphdr);
	m->m_next = m0;
	ui = mtod(m, struct udpiphdr *);
	ui->ui_next = ui->ui_prev = 0;
	ui->ui_x1 = 0;
	ui->ui_pr = IPPROTO_UDP;
	ui->ui_len = htons((u_short)len + sizeof (struct udphdr));
	ui->ui_src = inp->inp_laddr;
	ui->ui_dst = inp->inp_faddr;
	ui->ui_sport = inp->inp_lport;
	ui->ui_dport = inp->inp_fport;
	ui->ui_ulen = ui->ui_len;

	/*
	 * Stuff checksum and output datagram.
	 */
	ui->ui_sum = 0;
	if (udpcksum) {
	    if ((ui->ui_sum = in_cksum(m, sizeof (struct udpiphdr) + len)) == 0)
		ui->ui_sum = -1;
	}
	((struct ip *)ui)->ip_len = sizeof (struct udpiphdr) + len;
#if	TTLCONTROL
	((struct ip *)ui)->ip_ttl = inp->inp_ttl;
#else	TTLCONTROL
	((struct ip *)ui)->ip_ttl = UDP_TTL;
#endif	TTLCONTROL
	return (ip_output(m, inp->inp_options, &inp->inp_route,
	    inp->inp_socket->so_options & (SO_DONTROUTE | SO_BROADCAST)));
}

#if	SUN_RPC
	/* udp delivers data + sockaddr, must make space */
int	udp_sendspace = 9000;		/* really max datagram size */
int	udp_recvspace = 2*(9000+sizeof(struct sockaddr)); /* 2 8K dgrams */
#else	SUN_RPC
int	udp_sendspace = 2048;		/* really max datagram size */
int	udp_recvspace = 4 * (1024+sizeof(struct sockaddr_in)); /* 4 1K dgrams */
#endif	SUN_RPC

/*ARGSUSED*/
udp_usrreq(so, req, m, nam, rights)
	struct socket *so;
	int req;
	struct mbuf *m, *nam, *rights;
{
	struct inpcb *inp = sotoinpcb(so);
	int error = 0;

#if	SUN_RPC
        /*
         * XXX Protect udp_usrreq just like tcp.
         * Avoids race condition with in_pcballoc;
         * also keeps icmp error from aborting a udp
         * socket that is not connected (sendto used).
         */
        int s;
         
        s = splnet();
#endif	SUN_RPC

	if (req == PRU_CONTROL) {
#if	SUN_RPC
		splx(s);
#endif	SUN_RPC
		return (in_control(so, (int)m, (caddr_t)nam,
			(struct ifnet *)rights));
	}
	if (rights && rights->m_len) {
		error = EINVAL;
		goto release;
	}
	if (inp == NULL && req != PRU_ATTACH) {
		error = EINVAL;
		goto release;
	}
	switch (req) {

	case PRU_ATTACH:
		if (inp != NULL) {
			error = EINVAL;
			break;
		}
		error = in_pcballoc(so, &udb);
		if (error)
			break;
#if	TTLCONTROL
		inp = sotoinpcb(so);
		inp->inp_ttl = UDP_TTL;
#endif	TTLCONTROL
		error = soreserve(so, udp_sendspace, udp_recvspace);
		if (error)
			break;
		break;

	case PRU_DETACH:
		in_pcbdetach(inp);
		break;

	case PRU_BIND:
		error = in_pcbbind(inp, nam);
		break;

	case PRU_LISTEN:
		error = EOPNOTSUPP;
		break;

	case PRU_CONNECT:
		if (inp->inp_faddr.s_addr != INADDR_ANY) {
			error = EISCONN;
			break;
		}
		error = in_pcbconnect(inp, nam);
		if (error == 0)
			soisconnected(so);
		break;

	case PRU_CONNECT2:
		error = EOPNOTSUPP;
		break;

	case PRU_ACCEPT:
		error = EOPNOTSUPP;
		break;

	case PRU_DISCONNECT:
		if (inp->inp_faddr.s_addr == INADDR_ANY) {
			error = ENOTCONN;
			break;
		}
		in_pcbdisconnect(inp);
		so->so_state &= ~SS_ISCONNECTED;		/* XXX */
		break;

	case PRU_SHUTDOWN:
		socantsendmore(so);
		break;

	case PRU_SEND: {
		struct in_addr laddr;
		int s;

		if (nam) {
			laddr = inp->inp_laddr;
			if (inp->inp_faddr.s_addr != INADDR_ANY) {
				error = EISCONN;
				break;
			}
			/*
			 * Must block input while temporarily connected.
			 */
			s = splnet();
			error = in_pcbconnect(inp, nam);
			if (error) {
				splx(s);
				break;
			}
		} else {
			if (inp->inp_faddr.s_addr == INADDR_ANY) {
				error = ENOTCONN;
				break;
			}
		}
		error = udp_output(inp, m);
		m = NULL;
		if (nam) {
			in_pcbdisconnect(inp);
			inp->inp_laddr = laddr;
			splx(s);
		}
		}
		break;

	case PRU_ABORT:
		in_pcbdetach(inp);
		sofree(so);
		soisdisconnected(so);
		break;

	case PRU_SOCKADDR:
		in_setsockaddr(inp, nam);
		break;

	case PRU_PEERADDR:
		in_setpeeraddr(inp, nam);
		break;

	case PRU_SENSE:
		/*
		 * stat: don't bother with a blocksize.
		 */
#if	SUN_RPC
		splx(s);
#endif	SUN_RPC
		return (0);

	case PRU_SENDOOB:
	case PRU_FASTTIMO:
	case PRU_SLOWTIMO:
	case PRU_PROTORCV:
	case PRU_PROTOSEND:
		error =  EOPNOTSUPP;
		break;

	case PRU_RCVD:
	case PRU_RCVOOB:
#if	SUN_RPC
		splx(s);
#endif	SUN_RPC
		return (EOPNOTSUPP);	/* do not free mbuf's */

	default:
		panic("udp_usrreq");
	}
release:
#if	SUN_RPC
	splx(s);
#endif	SUN_RPC
	if (m != NULL)
		m_freem(m);
	return (error);
}
