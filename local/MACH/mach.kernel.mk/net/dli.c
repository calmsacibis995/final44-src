/* 
 * Mach Operating System
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 **********************************************************************
 * HISTORY
 * $Log:	dli.c,v $
 * Revision 2.6  90/07/03  16:40:28  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  17:57:29  mrt]
 * 
 * Revision 2.3  88/11/21  16:56:51  rvb
 * 	MACH_DEVICE option modifies the behaviour of DLI:
 * 		0) You do not have to be root to open the DLI socket to
 * 			simplify life.  SSPRIV is asserted before raw
 * 			socket is dispatched to.
 * 		1) You specify the complete packet to be send on the
 * 			ether, including ether header.
 * 		2) You receive all the ether traffic coming from machine
 * 			(with ether address) "dli_from".  Doing a
 * 			connect on the dli socket does nothing but as a
 * 			side effect sets dli_from.  (You can use either
 * 			the AF_DLI if you know the targets ether address
 * 			or AF_INET to have an arp generated to find out
 * 			for the connect.)
 * 		3) N.B. the AF_DLI socket you receive on must not be
 * 			bound or connected (LADDR or FADDR) since it will
 * 			screw up the match on raw_input
 * 	[88/11/09            rvb]
 * 
 * Revision 2.2  88/08/24  01:52:42  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:06:36  mwyoung]
 * 
 *
 * 15-Sep-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 06-May-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created.
 *	[ V5.1(F10) ]
 *
 **********************************************************************
 *
 *  Direct data-link interface protocol
 *
 *  The AF_DLI address family is used to provide raw access at the
 *  data-link level of a network interface (I have no idea if this
 *  is the usage for which it was originally intended).
 */

#include <dli.h>
#include <mach_device.h>

#if	DLI
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <net/route.h>
#include <net/raw_cb.h>

#include <net/dli_var.h>



/*
 *  Direct data-link interface to device.
 */

int dli_active = 0;	/* active raw DLI sockets */



/*
 *  Send a packet directly at the data-link interface level
 *
 *  The local address bound to the socket is used to determine the
 *  interface over which to send the packet with no other routing.
 */

dli_output(m, so)
	register struct mbuf *m;
	struct socket *so;
{
	register struct rawcb *rp = sotorawcb(so);
	struct ifaddr *ia = ifa_ifwithaddr((struct sockaddr *)&rp->rcb_laddr);

	if (ia)
        {
		struct ifnet *ifp = ia->ifa_ifp;

		return ((*ifp->if_output)(ifp, m,
				          (struct sockaddr *)&rp->rcb_faddr));
	}
	m_freem(m);
	return (ENETUNREACH);
}



/*
 *  Receive a packet directly from the data-link interface level
 *
 *  Stuff the receive protocol identifier and source address into the
 *  appropriate structures expected by raw_iput().
 *
 *  Remove the interface pointer at the beginning of the mbuf and prepend a
 *  packet header mbuf containing the physical data-link interface header (this
 *  is different from most other protocols where the source address information
 *  is only provided out of band from the message data since it also permits
 *  the destination addess and protocol to be included which would otherwise be
 *  unavailable).
 *
 *  As an optimization, we keep track of whether or not any raw sockets are
 *  currently open for input at the DLI protocol and don't bother to do any of
 *  the raw packet filtering if we know that nobody will want the packet.
 */

dli_input(m, proto, src, dlv, lh)
	struct mbuf *m;
	int proto;
	char *src;
	register struct dli_var *dlv;
	char *lh;
{
	if (dli_active)
	{
		register struct mbuf *b;

		dlv->dlv_rproto.sp_protocol = proto;
		bcopy(src, &dlv->dlv_rsrc.sa_data[0], dlv->dlv_hln);
		IF_ADJ(m);
		MGET(b, M_DONTWAIT, MT_HEADER);
		if (b)
		{
		    b->m_len = dlv->dlv_lhl;
		    b->m_off = MMAXOFF-b->m_len;
		    b->m_next = m;
		    bcopy(lh, mtod(b, char *), dlv->dlv_lhl);
		    raw_input(b, &dlv->dlv_rproto, &dlv->dlv_rsrc, &dlv->dlv_da.da_addr);
		    return;
		}
	}
	m_freem(m);
}



/*
 *  Process "user" request
 *
 *  Forward all "control" requests on to dli_control().
 *
 *  Pass all other requests on to the standard raw_usrreq() handler although we
 *  eavesdrop on the communication to:
 *
 *  - monitor ATTACH and DETACH operations on raw sockets to maintain a count 
 *    of open sockets for dli_input().
 *  - allow ATTACH and DETACH operations on other sockets (only SOCK_DGRAM at
 *    the moment) to allow them to be opened for control purposes.
 */

/*ARGSUSED*/
#if	MACH_DEVICE
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <socket.h>

static struct arpcom *ac;	/* remembered for arp */
char dli_from[6] = { 0x8, 0x0, 0x20, 0x0, 0x51, 0xc7 }; /* rvb.mach.cs.cmu.edu */
char dli_all[6] =  { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
int  dli_see = 0;

#endif	MACH_DEVICE
dli_usrreq(so, req, m, nam, rights)
	struct socket *so;
	int req;
	struct mbuf *m, *nam, *rights;
{

	if (req != PRU_CONTROL)
	{
		int error = 0;

		switch (req)
		{
		    case PRU_DETACH:
			if (so->so_type == SOCK_RAW)
			     dli_active--;
			break;
		    case PRU_ATTACH:
#if	MACH_DEVICE
			so->so_state |= SS_PRIV;
#endif	MACH_DEVICE
			break;
#if	MACH_DEVICE
		    case PRU_CONNECT:
		    {
			int usetrailers;
			struct sockaddr *sp = mtod(nam, struct sockaddr *);

			switch (sp->sa_family) {
			case AF_INET: {
				struct in_addr *ip =
					&(((struct sockaddr_in *)sp)->sin_addr);
				char desten[7];

				if (arpresolve(ac, 0, ip, desten, &usetrailers) != 1)
					return EHOSTUNREACH;
				else {

					bcopy(desten, dli_from, 6);
				}
			}
				break;
			case AF_DLI:
				bcopy(mtod(nam, struct sockaddr *)->sa_data, dli_from,6);
				break;
			}
			return 0;
		    }
#endif	MACH_DEVICE
		    default:
			error = EOPNOTSUPP;
			break;
		}
		if (so->so_type == SOCK_RAW)
		{
		    error = raw_usrreq(so, req, m, nam, rights);
		    if (error == 0 && req == PRU_ATTACH)
			dli_active++;
		}
		else
		{
		    if (m != NULL)
			    m_freem(m);
		}
		return(error);
	}
	else
		return (dli_control(so, (int)m, (caddr_t)nam,
			(struct ifnet *)rights));
}



/*
 *  Handle interface status and control requests
 *
 *  SIOCGIFADDR - returns hardware address of interface
 *  SIOCGIFBRDADDR - returns hardware broadcast address of interface
 *  SIOCGIFDSTADDR - returns hardware destination address of interface (unused)
 *  SIOCGIFGIFNETMASK - returns mask of hardware address length for interface
 */

dli_control(so, cmd, data, ifp)
	struct socket *so;
	int cmd;
	caddr_t data;
	register struct ifnet *ifp;
{
	register struct ifreq *ifr = (struct ifreq *)data;
	register struct ifaddr *ifa = 0;

#ifdef	lint
	so++;
#endif	lint

	if (ifp)
		for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
			if (ifa->ifa_addr.sa_family == AF_DLI)
				break;
	if (ifa == 0)
		return (EOPNOTSUPP);

	switch (cmd) {

	case SIOCGIFADDR:
		ifr->ifr_addr = ifa->ifa_addr;
		break;

	case SIOCGIFBRDADDR:
		if ((ifp->if_flags & IFF_BROADCAST) == 0)
			return (EINVAL);
		ifr->ifr_dstaddr = ifa->ifa_broadaddr;
		break;

	case SIOCGIFDSTADDR:
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
		ifr->ifr_dstaddr = ifa->ifa_dstaddr;
		break;

	case SIOCGIFNETMASK:
	{
		register int i;

		ifr->ifr_addr.sa_family = AF_DLI;
		bzero(&ifr->ifr_addr.sa_data[0], sizeof(ifr->ifr_addr.sa_data));
		for (i=0; i<((struct dli_ifaddr *)(ifa))->da_dlv->dlv_hln; i++)
			ifr->ifr_addr.sa_data[i] = 0xff;
		break;
	}

	default:
		if (ifp == 0 || ifp->if_ioctl == 0)
			return (EOPNOTSUPP);
		return ((*ifp->if_ioctl)(ifp, cmd, data));
	}
	return(0);
}



/*
 *  Initialize the DLI protocol for a network interface
 *
 *  Set the address family in all the socket address structures and our
 *  hardware address and broadcast address.
 *
 *  Initialize the hardware address and header length fields.
 *
 *  Link our DLI address onto the master address list for this interface.
 */

dli_init(dlv, ifp, addr, broadaddr, addrlen, lhlen)
	register struct dli_var *dlv;
	register struct ifnet *ifp;
	char *addr;
	char *broadaddr;
	u_int addrlen;
{
	register struct ifaddr *ifa;
	struct dli_ifaddr *da = &dlv->dlv_da;

#ifdef	lint
	broadaddr++;
#endif	lint

	if (da->da_addr.sa_family)
		return;

	da->da_addr.sa_family =
        da->da_broadaddr.sa_family = 
	dlv->dlv_rsrc.sa_family = 
	dlv->dlv_rproto.sp_family = AF_DLI;
	dlv->dlv_hln = addrlen;
	dlv->dlv_lhl = lhlen;
	bcopy(addr, da->da_addr.sa_data, addrlen);
	bcopy(addr, da->da_broadaddr.sa_data, addrlen);
        da->da_dlv = dlv;
	da->da_ifp = ifp;
	if (ifa = ifp->if_addrlist) {
		for ( ; ifa->ifa_next; ifa = ifa->ifa_next)
			;
		ifa->ifa_next = (struct ifaddr *) da;
	} else
		ifp->if_addrlist = (struct ifaddr *) da;
#if	MACH_DEVICE
	ac = (struct arpcom *) ifp;
#endif	MACH_DEVICE
}
#endif	DLI
