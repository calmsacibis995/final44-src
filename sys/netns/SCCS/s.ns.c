h50442
s 00002/00001/00338
d D 8.5 95/02/09 08:06:48 sklower 26 25
c more stupid lint tricks
e
s 00013/00016/00326
d D 8.4 95/01/12 10:40:03 mckusick 25 24
c missing splx, minor cleanups (from mycroft)
e
s 00001/00001/00341
d D 8.3 95/01/09 17:53:00 cgd 24 23
c 64-bit changes -- ioctl cmds are u_longs.
e
s 00000/00001/00342
d D 8.2 93/11/15 13:36:15 sklower 23 22
c af.h has been retired
e
s 00002/00002/00341
d D 8.1 93/06/10 23:34:41 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00013/00331
d D 7.13 92/10/11 12:26:24 bostic 21 20
c make kernel includes standard
e
s 00003/00003/00341
d D 7.12 92/05/08 11:59:54 sklower 20 19
c remove #define for ia_net
e
s 00001/00000/00343
d D 7.11 92/02/21 10:43:35 sklower 19 18
c forgot to zero out new ifaddr structure
e
s 00001/00000/00342
d D 7.10 92/02/20 10:41:56 sklower 18 17
c make it possible to have different metrics for different networks
c on same phys interface
e
s 00007/00007/00335
d D 7.9 91/12/19 17:42:36 sklower 17 16
c reference count ifaddrs to make them safe for deletion
e
s 00003/00003/00339
d D 7.8 91/06/27 23:10:15 sklower 16 14
c make compile under both new and old vm
e
s 00002/00003/00339
d R 7.8 91/06/27 22:59:30 sklower 15 14
c make compile under both new and old vm system
e
s 00001/00011/00341
d D 7.7 90/06/28 21:47:23 bostic 14 13
c new copyright notice
e
s 00000/00002/00352
d D 7.6 89/05/05 00:29:30 mckusick 13 12
c get rid of unneeded include files
e
s 00003/00003/00351
d D 7.5 89/04/26 18:49:05 mckusick 12 11
c usr new form of suser()
e
s 00133/00081/00221
d D 7.4 89/04/22 12:13:59 sklower 11 10
c changes for var. length sockaddrs, routing lookup changes,
c checkpoint at first working tp4 connection, before gnodes
e
s 00011/00006/00291
d D 7.3 88/06/29 17:13:14 bostic 10 9
c install approved copyright notice
e
s 00010/00004/00287
d D 7.2 88/01/20 15:15:08 sklower 9 8
c Change licensing/use notice.
e
s 00001/00001/00290
d D 7.1 86/06/05 00:36:04 mckusick 8 7
c 4.3BSD release version
e
s 00010/00008/00281
d D 6.7 86/02/03 17:31:50 sklower 7 6
c remove ns_netof (non-portable), add zero and broadcast ns nets to compare to.
e
s 00052/00044/00237
d D 6.6 85/11/09 15:57:12 sklower 6 5
c change the way pt to pt links are handle to be closer to inet
c to allow net(addr)!=net(dstaddr); also change interface to rtinit so that
c renaming pt to pt links will delete existing routes.
e
s 00025/00007/00256
d D 6.5 85/09/26 16:09:44 sklower 5 4
c make ns_iaonnetof smarter about point to point links, and think about the issue of longs which need to be long aligned.
e
s 00001/00001/00262
d D 6.4 85/08/09 11:35:00 sklower 4 3
c 
e
s 00025/00031/00238
d D 6.3 85/07/31 13:01:36 sklower 3 2
c Allow non super users to run ifconfig to get state of interface.
e
s 00007/00001/00262
d D 6.2 85/06/08 12:49:25 mckusick 2 1
c Add copyright
e
s 00263/00000/00000
d D 6.1 85/05/30 19:10:50 sklower 1 0
c date and time created 85/05/30 19:10:50 by sklower
e
u
U
t
T
I 1
D 2
/*      %M%     %I%     %E%     */
E 2
I 2
/*
D 6
 * Copyright (c) 1982 Regents of the University of California.
E 6
I 6
D 8
 * Copyright (c) 1984, 1985 Regents of the University of California.
E 8
I 8
D 9
 * Copyright (c) 1984, 1985, 1986 Regents of the University of California.
E 8
E 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 22
 * Copyright (c) 1984, 1985, 1986, 1987 Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1984, 1985, 1986, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
E 9
 *
D 9
 *	%W% (Berkeley) %G%
E 9
I 9
D 14
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 10
 *
D 10
 *      %W% (Berkeley) %G%
E 10
I 10
 *	%W% (Berkeley) %G%
E 10
E 9
 */
E 2

D 21
#include "param.h"
#include "mbuf.h"
#include "ioctl.h"
#include "protosw.h"
I 16
#include "errno.h"
E 16
#include "socket.h"
#include "socketvar.h"
E 21
I 21
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/ioctl.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
E 21
D 13
#include "uio.h"
#include "dir.h"
E 13
D 16
#include "user.h"
E 16

I 21
#include <net/if.h>
#include <net/route.h>
D 23
#include <net/af.h>
E 23
E 21

D 21
#include "../net/if.h"
#include "../net/route.h"
#include "../net/af.h"

#include "ns.h"
#include "ns_if.h"
E 21
I 21
#include <netns/ns.h>
#include <netns/ns_if.h>
E 21

#ifdef NS

struct ns_ifaddr *ns_ifaddr;
I 11
int ns_interfaces;
extern struct sockaddr_ns ns_netmask, ns_hostmask;
E 11

D 11
ns_hash(sns, hp)
	register struct sockaddr_ns *sns;
	struct afhash *hp;
{
	register long hash = 0;
	register u_short *s =  sns->sns_addr.x_host.s_host;
I 7
	union {
		union ns_net	net_e;
		long		long_e;
	} net;
E 7

D 7
	hp->afh_nethash = ns_netof(sns->sns_addr);
E 7
I 7
	net.net_e = sns->sns_addr.x_net;
	hp->afh_nethash = net.long_e;
E 7
	hash = *s++; hash <<= 8; hash += *s++; hash <<= 8; hash += *s;
	hp->afh_hosthash =  hash;
}


ns_netmatch(sns1, sns2)
	struct sockaddr_ns *sns1, *sns2;
{

D 7
	return (ns_netof(sns1->sns_addr) == ns_netof(sns2->sns_addr));
E 7
I 7
	return (ns_neteq(sns1->sns_addr, sns2->sns_addr));
E 7
}

E 11
/*
 * Generic internet control operations (ioctl's).
 */
I 4
/* ARGSUSED */
E 4
ns_control(so, cmd, data, ifp)
	struct socket *so;
D 24
	int cmd;
E 24
I 24
	u_long cmd;
E 24
	caddr_t data;
	register struct ifnet *ifp;
{
	register struct ifreq *ifr = (struct ifreq *)data;
I 11
	register struct ns_aliasreq *ifra = (struct ns_aliasreq *)data;
E 11
	register struct ns_ifaddr *ia;
	struct ifaddr *ifa;
I 11
	struct ns_ifaddr *oia;
E 11
D 17
	struct mbuf *m;
E 17
I 11
D 12
	int dstIsNew, hostIsNew;
E 12
I 12
	int error, dstIsNew, hostIsNew;
E 12
E 11
D 4
	int error;
E 4

D 3
	if (!suser())
		return (u.u_error);

E 3
	/*
	 * Find address for this interface, if it exists.
	 */
I 3
D 6
	if (ifp==0)
E 6
I 6
	if (ifp == 0)
E 6
		return (EADDRNOTAVAIL);
E 3
	for (ia = ns_ifaddr; ia; ia = ia->ia_next)
		if (ia->ia_ifp == ifp)
			break;

	switch (cmd) {

	case SIOCGIFADDR:
I 3
		if (ia == (struct ns_ifaddr *)0)
			return (EADDRNOTAVAIL);
D 11
		ifr->ifr_addr = ia->ia_addr;
E 11
I 11
		*(struct sockaddr_ns *)&ifr->ifr_addr = ia->ia_addr;
E 11
		return (0);


E 3
	case SIOCGIFBRDADDR:
I 3
		if (ia == (struct ns_ifaddr *)0)
			return (EADDRNOTAVAIL);
		if ((ifp->if_flags & IFF_BROADCAST) == 0)
			return (EINVAL);
D 11
		ifr->ifr_dstaddr = ia->ia_broadaddr;
E 11
I 11
		*(struct sockaddr_ns *)&ifr->ifr_dstaddr = ia->ia_broadaddr;
E 11
		return (0);

E 3
	case SIOCGIFDSTADDR:
		if (ia == (struct ns_ifaddr *)0)
			return (EADDRNOTAVAIL);
D 3
		break;
E 3
I 3
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
D 11
		ifr->ifr_dstaddr = ia->ia_dstaddr;
E 11
I 11
		*(struct sockaddr_ns *)&ifr->ifr_dstaddr = ia->ia_dstaddr;
E 11
		return (0);
	}
E 3

I 3
D 12
	if (!suser())
		return (u.u_error);
E 12
I 12
D 16
	if (error = suser(u.u_cred, &u.u_acflag))
		return (error);
E 16
I 16
	if ((so->so_state & SS_PRIV) == 0)
		return (EPERM);
E 16
E 12

	switch (cmd) {
I 11
	case SIOCAIFADDR:
	case SIOCDIFADDR:
		if (ifra->ifra_addr.sns_family == AF_NS)
		    for (oia = ia; ia; ia = ia->ia_next) {
			if (ia->ia_ifp == ifp  &&
			    ns_neteq(ia->ia_addr.sns_addr,
				  ifra->ifra_addr.sns_addr))
			    break;
		    }
		if (cmd == SIOCDIFADDR && ia == 0)
			return (EADDRNOTAVAIL);
		/* FALLTHROUGH */
E 11

E 3
D 6
	case SIOCSIFDSTADDR:
		return (EOPNOTSUPP);

E 6
	case SIOCSIFADDR:
I 6
	case SIOCSIFDSTADDR:
E 6
		if (ia == (struct ns_ifaddr *)0) {
D 17
			m = m_getclr(M_WAIT, MT_IFADDR);
			if (m == (struct mbuf *)NULL)
E 17
I 17
			oia = (struct ns_ifaddr *)
				malloc(sizeof *ia, M_IFADDR, M_WAITOK);
			if (oia == (struct ns_ifaddr *)NULL)
E 17
				return (ENOBUFS);
I 19
			bzero((caddr_t)oia, sizeof(*oia));
E 19
			if (ia = ns_ifaddr) {
				for ( ; ia->ia_next; ia = ia->ia_next)
					;
D 17
				ia->ia_next = mtod(m, struct ns_ifaddr *);
E 17
I 17
				ia->ia_next = oia;
E 17
			} else
D 17
				ns_ifaddr = mtod(m, struct ns_ifaddr *);
			ia = mtod(m, struct ns_ifaddr *);
E 17
I 17
				ns_ifaddr = oia;
			ia = oia;
E 17
			if (ifa = ifp->if_addrlist) {
				for ( ; ifa->ifa_next; ifa = ifa->ifa_next)
					;
				ifa->ifa_next = (struct ifaddr *) ia;
			} else
				ifp->if_addrlist = (struct ifaddr *) ia;
			ia->ia_ifp = ifp;
D 11
			IA_SNS(ia)->sns_family = AF_NS;
E 11
I 11
			ia->ia_ifa.ifa_addr = (struct sockaddr *)&ia->ia_addr;

			ia->ia_ifa.ifa_netmask =
				(struct sockaddr *)&ns_netmask;

			ia->ia_ifa.ifa_dstaddr =
				(struct sockaddr *)&ia->ia_dstaddr;
			if (ifp->if_flags & IFF_BROADCAST) {
				ia->ia_broadaddr.sns_family = AF_NS;
				ia->ia_broadaddr.sns_len = sizeof(ia->ia_addr);
				ia->ia_broadaddr.sns_addr.x_host = ns_broadhost;
			}
			ns_interfaces++;
E 11
		}
I 6
	}

	switch (cmd) {
I 11
		int error;
E 11

	case SIOCSIFDSTADDR:
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
		if (ia->ia_flags & IFA_ROUTE) {
D 11
			rtinit(&ia->ia_dstaddr, &ia->ia_addr,
				(int)SIOCDELRT, RTF_HOST);
E 11
I 11
			rtinit(&(ia->ia_ifa), (int)RTM_DELETE, RTF_HOST);
E 11
			ia->ia_flags &= ~IFA_ROUTE;
		}
		if (ifp->if_ioctl) {
D 11
			int error = (*ifp->if_ioctl)(ifp, SIOCSIFDSTADDR, ia);
E 11
I 11
D 26
			error = (*ifp->if_ioctl)(ifp, SIOCSIFDSTADDR, ia);
E 26
I 26
			error = (*ifp->if_ioctl)
				        (ifp, SIOCSIFDSTADDR, (caddr_t)ia);
E 26
E 11
			if (error)
				return (error);
		}
D 11
		ia->ia_dstaddr = ifr->ifr_dstaddr;
E 11
I 11
		*(struct sockaddr *)&ia->ia_dstaddr = ifr->ifr_dstaddr;
E 11
		return (0);

	case SIOCSIFADDR:
E 6
D 3
		break;
	}

	switch (cmd) {

	case SIOCGIFADDR:
		ifr->ifr_addr = ia->ia_addr;
		break;

	case SIOCGIFBRDADDR:
		if (ia == (struct ns_ifaddr *)0)
			return (EADDRNOTAVAIL);
		if ((ifp->if_flags & IFF_BROADCAST) == 0)
			return (EINVAL);
		ifr->ifr_dstaddr = ia->ia_broadaddr;
		break;

	case SIOCGIFDSTADDR:
		if (ia == (struct ns_ifaddr *)0)
			return (EADDRNOTAVAIL);
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
		ifr->ifr_dstaddr = ia->ia_dstaddr;
		break;

	case SIOCSIFADDR:
E 3
D 11
		return
		    (ns_ifinit(ifp, ia, (struct sockaddr_ns *)&ifr->ifr_addr));
E 11
I 11
		return (ns_ifinit(ifp, ia,
				(struct sockaddr_ns *)&ifr->ifr_addr, 1));
E 11

I 11
	case SIOCDIFADDR:
		ns_ifscrub(ifp, ia);
		if ((ifa = ifp->if_addrlist) == (struct ifaddr *)ia)
			ifp->if_addrlist = ifa->ifa_next;
		else {
			while (ifa->ifa_next &&
			       (ifa->ifa_next != (struct ifaddr *)ia))
				    ifa = ifa->ifa_next;
			if (ifa->ifa_next)
			    ifa->ifa_next = ((struct ifaddr *)ia)->ifa_next;
			else
				printf("Couldn't unlink nsifaddr from ifp\n");
		}
		oia = ia;
		if (oia == (ia = ns_ifaddr)) {
			ns_ifaddr = ia->ia_next;
		} else {
			while (ia->ia_next && (ia->ia_next != oia)) {
				ia = ia->ia_next;
			}
			if (ia->ia_next)
			    ia->ia_next = oia->ia_next;
			else
				printf("Didn't unlink nsifadr from list\n");
		}
D 17
		(void) m_free(dtom(oia));
E 17
I 17
		IFAFREE((&oia->ia_ifa));
E 17
		if (0 == --ns_interfaces) {
			/*
			 * We reset to virginity and start all over again
			 */
			ns_thishost = ns_zerohost;
		}
		return (0);
	
	case SIOCAIFADDR:
		dstIsNew = 0; hostIsNew = 1;
		if (ia->ia_addr.sns_family == AF_NS) {
			if (ifra->ifra_addr.sns_len == 0) {
				ifra->ifra_addr = ia->ia_addr;
				hostIsNew = 0;
			} else if (ns_neteq(ifra->ifra_addr.sns_addr,
					 ia->ia_addr.sns_addr))
				hostIsNew = 0;
		}
		if ((ifp->if_flags & IFF_POINTOPOINT) &&
		    (ifra->ifra_dstaddr.sns_family == AF_NS)) {
			if (hostIsNew == 0)
				ns_ifscrub(ifp, ia);
			ia->ia_dstaddr = ifra->ifra_dstaddr;
			dstIsNew  = 1;
		}
		if (ifra->ifra_addr.sns_family == AF_NS &&
					    (hostIsNew || dstIsNew))
			error = ns_ifinit(ifp, ia, &ifra->ifra_addr, 0);
		return (error);

E 11
	default:
		if (ifp->if_ioctl == 0)
			return (EOPNOTSUPP);
		return ((*ifp->if_ioctl)(ifp, cmd, data));
	}
D 3
	return (0);
E 3
}

/*
I 11
* Delete any previous route for an old address.
*/
ns_ifscrub(ifp, ia)
	register struct ifnet *ifp;
	register struct ns_ifaddr *ia; 
{
	if (ia->ia_flags & IFA_ROUTE) {
		if (ifp->if_flags & IFF_POINTOPOINT) {
			rtinit(&(ia->ia_ifa), (int)RTM_DELETE, RTF_HOST);
		} else
			rtinit(&(ia->ia_ifa), (int)RTM_DELETE, 0);
		ia->ia_flags &= ~IFA_ROUTE;
	}
}
/*
E 11
 * Initialize an interface's internet address
 * and routing table entry.
 */
D 11
ns_ifinit(ifp, ia, sns)
E 11
I 11
ns_ifinit(ifp, ia, sns, scrub)
E 11
	register struct ifnet *ifp;
	register struct ns_ifaddr *ia;
D 11
	struct sockaddr_ns *sns;
E 11
I 11
	register struct sockaddr_ns *sns;
E 11
{
D 11
	struct sockaddr_ns netaddr;
	register union ns_host *h = &(IA_SNS(ia)->sns_addr.x_host);
E 11
I 11
	struct sockaddr_ns oldaddr;
	register union ns_host *h = &ia->ia_addr.sns_addr.x_host;
E 11
	int s = splimp(), error;

	/*
I 11
	 * Set up new addresses.
	 */
	oldaddr = ia->ia_addr;
	ia->ia_addr = *sns;
	/*
E 11
	 * The convention we shall adopt for naming is that
	 * a supplied address of zero means that "we don't care".
	 * if there is a single interface, use the address of that
	 * interface as our 6 byte host address.
	 * if there are multiple interfaces, use any address already
	 * used.
	 *
D 11
	 * If we have gotten into trouble and want to reset back to
	 * virginity, we recognize a request of the broadcast address.
	 */
	if (ns_hosteqnh(sns->sns_addr.x_host, ns_broadhost)) {
		ns_thishost = ns_zerohost;
		splx(s);
D 6
		return(EINVAL);
E 6
I 6
		return (0);
E 6
	}

	/*
	 * Delete any previous route for an old address.
	 */
D 6

E 6
	bzero((caddr_t)&netaddr, sizeof (netaddr));
	netaddr.sns_family = AF_NS;
	netaddr.sns_addr.x_host = ns_broadhost;
	netaddr.sns_addr.x_net = ia->ia_net;
	if (ia->ia_flags & IFA_ROUTE) {
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0) {
D 6
		    rtinit((struct sockaddr *)&netaddr, &ia->ia_addr, -1);
E 6
I 6
		    rtinit((struct sockaddr *)&netaddr, &ia->ia_addr,
				    (int)SIOCDELRT, 0);
E 6
		} else
D 6
		    rtinit((struct sockaddr *)&ia->ia_dstaddr, &ia->ia_addr, -1);
E 6
I 6
		    rtinit(&ia->ia_dstaddr, &ia->ia_addr,
				    (int)SIOCDELRT, RTF_HOST);
E 6
	}

	/*
	 * Set up new addresses.
	 */
	ia->ia_addr = *(struct sockaddr *)sns;
	ia->ia_net = sns->sns_addr.x_net;
	netaddr.sns_addr.x_net = ia->ia_net;
	if (ifp->if_flags & IFF_BROADCAST) {
		ia->ia_broadaddr = * (struct sockaddr *) &netaddr;
	}
I 6

E 6
	/*
E 11
D 6
	 * Point to point links are a little touchier --
	 * We have to have an address of our own first,
	 * and will use the supplied address as that of the other end.
	 */
	if (ifp->if_flags & IFF_POINTOPOINT) {
		struct sockaddr_ns *sns2 = IA_SNS(ia);
		if (ns_hosteqnh(ns_zerohost,ns_thishost))
			return(EINVAL);
		ia->ia_dstaddr = ia->ia_addr;
		sns2->sns_addr.x_host = ns_thishost;
		sns->sns_addr.x_host = ns_thishost;
	}
	/*
E 6
	 * Give the interface a chance to initialize
	 * if this is its first address,
	 * and to validate the address if necessary.
	 */
D 6

E 6
	if (ns_hosteqnh(ns_thishost, ns_zerohost)) {
		if (ifp->if_ioctl &&
D 25
		     (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ia))) {
I 11
			ia->ia_addr = oldaddr;
E 11
			splx(s);
			return (error);
		}
E 25
I 25
		     (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, (caddr_t)ia)))
			goto bad;
E 25
		ns_thishost = *h;
	} else if (ns_hosteqnh(sns->sns_addr.x_host, ns_zerohost)
	    || ns_hosteqnh(sns->sns_addr.x_host, ns_thishost)) {
		*h = ns_thishost;
		if (ifp->if_ioctl &&
D 25
		     (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ia))) {
I 11
			ia->ia_addr = oldaddr;
E 11
			splx(s);
			return (error);
		}
E 25
I 25
		     (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, (caddr_t)ia)))
			goto bad;
E 25
D 6
		if(!ns_hosteqnh(ns_thishost,*h)) {
E 6
I 6
		if (!ns_hosteqnh(ns_thishost,*h)) {
I 11
D 25
			ia->ia_addr = oldaddr;
E 11
E 6
			splx(s);
			return (EINVAL);
E 25
I 25
			error = EINVAL;
			goto bad;
E 25
		}
	} else {
I 11
D 25
		ia->ia_addr = oldaddr;
E 11
		splx(s);
D 6
		return(EINVAL);
E 6
I 6
		return (EINVAL);
E 25
I 25
		error = EINVAL;
		goto bad;
E 25
E 6
	}
I 18
	ia->ia_ifa.ifa_metric = ifp->if_metric;
E 18
I 6
D 11

E 11
E 6
	/*
	 * Add route for the network.
	 */
I 11
	if (scrub) {
		ia->ia_ifa.ifa_addr = (struct sockaddr *)&oldaddr;
		ns_ifscrub(ifp, ia);
		ia->ia_ifa.ifa_addr = (struct sockaddr *)&ia->ia_addr;
	}
E 11
D 6
	if ((ifp->if_flags & IFF_POINTOPOINT) == 0) {
		rtinit((struct sockaddr *)&netaddr, &ia->ia_addr, RTF_UP);
	} else
		rtinit((struct sockaddr *)&ia->ia_dstaddr, &ia->ia_addr,
E 6
I 6
	if (ifp->if_flags & IFF_POINTOPOINT)
D 11
		rtinit(&ia->ia_dstaddr, &ia->ia_addr, (int)SIOCADDRT,
E 6
			RTF_HOST|RTF_UP);
I 6
	else
		rtinit(&ia->ia_broadaddr, &ia->ia_addr, (int)SIOCADDRT,
			RTF_UP);
E 11
I 11
		rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_HOST|RTF_UP);
	else {
D 20
		ia->ia_broadaddr.sns_addr.x_net = ia->ia_net;
E 20
I 20
		ia->ia_broadaddr.sns_addr.x_net = ia->ia_addr.sns_addr.x_net;
E 20
		rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_UP);
	}
E 11
E 6
	ia->ia_flags |= IFA_ROUTE;
I 25
	splx(s);
E 25
D 6
	return(0);
E 6
I 6
	return (0);
I 25
bad:
	ia->ia_addr = oldaddr;
	splx(s);
	return (error);
E 25
E 6
}

/*
 * Return address info for specified internet network.
 */
struct ns_ifaddr *
D 5
ns_iaonnetof(net)
	union ns_net net;
E 5
I 5
ns_iaonnetof(dst)
	register struct ns_addr *dst;
E 5
{
	register struct ns_ifaddr *ia;
I 5
	register struct ns_addr *compare;
D 6
	struct ifnet *ifp;
E 6
I 6
	register struct ifnet *ifp;
	struct ns_ifaddr *ia_maybe = 0;
E 6
D 7
	long net = ns_netof(*dst);
	static struct ns_addr laddr;
E 7
I 7
	union ns_net net = dst->x_net;
E 7
D 6
	struct ns_ifaddr *ia_maybe = 0;
E 6
E 5

D 5
#define	NtoL(x)	(*(long *)(&(x)))
	for (ia = ns_ifaddr; ia; ia = ia->ia_next)
		if (NtoL(ia->ia_net) == NtoL(net))
			return (ia);
	return ((struct ns_ifaddr *)0);
E 5
I 5
	for (ia = ns_ifaddr; ia; ia = ia->ia_next) {
D 6
		laddr.x_net = ia->ia_net;
		if (ns_netof(laddr) == net) {
			ia_maybe = ia;
			ifp = ia->ia_ifp;
			if (ifp) {
				if (ifp->if_flags & IFF_POINTOPOINT) {
					compare = &satons_addr(ia->ia_dstaddr);
					if (ns_hosteq(*dst, *compare))
						return (ia);
					else
						continue;
				} else
E 6
I 6
		if (ifp = ia->ia_ifp) {
			if (ifp->if_flags & IFF_POINTOPOINT) {
				compare = &satons_addr(ia->ia_dstaddr);
				if (ns_hosteq(*dst, *compare))
					return (ia);
D 7
				laddr.x_net = ia->ia_net;
				if (ns_netof(laddr) == net)
E 7
I 7
D 20
				if (ns_neteqnn(net, ia->ia_net))
E 20
I 20
				if (ns_neteqnn(net, ia->ia_addr.sns_addr.x_net))
E 20
E 7
					ia_maybe = ia;
			} else {
D 7
				laddr.x_net = ia->ia_net;
				if (ns_netof(laddr) == net)
E 7
I 7
D 20
				if (ns_neteqnn(net, ia->ia_net))
E 20
I 20
				if (ns_neteqnn(net, ia->ia_addr.sns_addr.x_net))
E 20
E 7
E 6
					return (ia);
			}
		}
	}
	return (ia_maybe);
E 5
}
#endif
E 1
