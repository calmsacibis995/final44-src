h49961
s 00001/00001/00595
d D 8.4 95/01/09 18:19:40 cgd 67 66
c ioctl cmd arg is u_long
e
s 00001/00001/00595
d D 8.3 94/11/07 12:06:52 sklower 66 65
c off by one error prevents installing routes for class A interfaces
c (fix provided by Karl Fox of Morningstar, reported via karels).
e
s 00000/00001/00596
d D 8.2 93/11/15 13:34:10 sklower 65 64
c af.h has been retire
e
s 00002/00002/00595
d D 8.1 93/06/10 23:04:12 bostic 64 63
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00005/00588
d D 7.34 93/06/09 17:34:53 sklower 63 62
c allow supernetting (aggregation of multiple class C nets, for example).
e
s 00003/00002/00590
d D 7.33 93/06/04 17:23:03 bostic 62 61
c prototype everything
e
s 00000/00073/00592
d D 7.32 93/04/08 17:19:39 sklower 61 60
c get rid of in_makeaddr, in_sockmaskof by request from jch
e
s 00044/00080/00621
d D 7.31 93/04/07 19:28:05 sklower 60 59
c Mostly changes recommended by jch for variable subnets & multiple
c IP addresses per physical interface. May require further work.
e
s 00005/00010/00696
d D 7.30 93/03/03 13:29:52 sklower 59 58
c proposed multicast address MUST be in list for ->if_ioctl(.. ADDMULTI);
c however, back out gracefully under failure
e
s 00001/00001/00705
d D 7.29 93/02/11 19:35:30 sklower 58 57
c fix bug in in_canforward reported by yval@cs.huji.ac.il
e
s 00003/00003/00703
d D 7.28 93/02/04 19:46:10 andrew 57 56
c in in_addmulti, don't link the inm to the ia until the SIOCADDMULTI ioctl
c succeeds to prevent accesses to deallocated memory.
e
s 00000/00008/00706
d D 7.27 93/01/08 18:42:23 andrew 56 55
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00014/00012/00700
d D 7.26 92/10/11 12:01:51 bostic 55 54
c make kernel includes standard
e
s 00138/00003/00574
d D 7.25 92/07/06 15:08:19 sklower 54 53
c multicast changes from lbl
e
s 00002/00002/00575
d D 7.24 92/03/11 21:53:07 torek 53 52
c gcc lint
e
s 00002/00002/00575
d D 7.23 92/02/20 10:45:15 sklower 52 51
c shut up lint
e
s 00001/00000/00576
d D 7.22 92/02/20 10:39:40 sklower 51 49
c make it possible to have different metrics on different addresses
c on same physical interface
e
s 00001/00000/00576
d R 7.22 92/02/15 18:16:00 mckusick 50 49
c have to include proc.h before socketvar.h
e
s 00000/00004/00576
d D 7.21 92/02/03 15:07:09 sklower 49 48
c yet another torek fix
e
s 00003/00001/00577
d D 7.20 92/01/30 14:07:56 torek 48 47
c lint changes for sparc port, bug fix on default case
e
s 00008/00007/00570
d D 7.19 91/12/19 17:42:00 sklower 47 46
c reference count ifaddrs to make them safe for deletion
e
s 00006/00000/00571
d D 7.18 91/06/25 22:11:58 sklower 46 45
c rather than change umpteen ethernet drivers, add kludge in
c common code to stomp on in_ifaddr structure to set ethernet rtrequest method.
e
s 00008/00010/00563
d D 7.17 91/04/20 17:02:18 karels 45 44
c use SS_PRIV instead of suser; fix includes (rm user.h)
e
s 00016/00016/00557
d D 7.16 90/10/31 13:57:37 sklower 44 43
c SIOCSIFDSTADDR does the wrong thing (droid@cray.com);
c rtinit() now returns an error which may be reported to users doing ifconfigs.
e
s 00001/00011/00572
d D 7.15 90/06/28 21:36:22 bostic 43 42
c new copyright notice
e
s 00010/00009/00573
d D 7.14 90/06/28 14:09:00 karels 42 41
c eliminate u.u_error, more like KNF
e
s 00019/00002/00563
d D 7.13 89/09/20 13:10:08 sklower 41 40
c change default actions on some ioctls, describe better way of finding end of mask.
e
s 00000/00002/00565
d D 7.12 89/05/05 00:25:35 mckusick 40 39
c get rid of unneeded include of dir.h
e
s 00004/00004/00563
d D 7.11 89/04/26 18:53:12 mckusick 39 38
c use new form of suser()
e
s 00181/00079/00386
d D 7.10 89/04/22 12:06:06 sklower 38 37
c checkpoint at first working tp4 connection; & before gnodes
e
s 00010/00005/00455
d D 7.9 88/06/29 17:06:31 bostic 37 36
c install approved copyright notice
e
s 00002/00001/00458
d D 7.8 88/05/26 09:38:20 karels 36 35
c lint
e
s 00000/00007/00459
d D 7.7 88/04/03 17:34:47 karels 35 34
c netbroadcast should always be all-ones
e
s 00008/00002/00458
d D 7.6 87/12/07 17:45:09 bostic 34 33
c use Berkeley specific header
e
s 00027/00003/00433
d D 7.5 87/06/04 21:48:40 karels 33 32
c add class D, experimental; don't forward those, net 0 or loopback
e
s 00009/00011/00427
d D 7.4 87/03/30 20:51:40 karels 32 31
c get this right
e
s 00013/00004/00425
d D 7.3 87/02/19 16:49:58 karels 31 30
c liberalize interpretation of in_broadcast to avoid responding
c to most UDP broadcasts
e
s 00001/00001/00428
d D 7.2 86/11/23 20:30:52 karels 30 29
c yow
e
s 00001/00001/00428
d D 7.1 86/06/05 00:25:07 mckusick 29 28
c 4.3BSD release version
e
s 00042/00020/00387
d D 6.15 86/04/13 21:42:01 karels 28 27
c delete old routes properly, use route to host for loopback
e
s 00001/00001/00406
d D 6.14 86/03/04 13:58:55 karels 27 25
c ... but need to set dstaddr before addr, or garbage routes installed
e
s 00001/00001/00406
d R 6.14 86/02/27 00:42:59 karels 26 25
c Sorry, do the dstaddr first
e
s 00009/00002/00398
d D 6.13 86/02/23 23:23:24 karels 25 24
c lint
e
s 00032/00029/00368
d D 6.12 86/02/21 15:25:18 karels 24 23
c reorder code for interface initialization so that nothing is modified
c if the interface can't initialize (in particular, not net or subnet)
e
s 00007/00004/00390
d D 6.11 85/11/09 15:52:27 sklower 23 22
c in rtinit, allow for deleting pt to pt hosts, by requiring
c new argument, rather than overloading flags.
e
s 00009/00000/00385
d D 6.10 85/10/14 17:19:55 karels 22 21
c recognize other attempts to broadcast
e
s 00012/00006/00373
d D 6.9 85/09/16 22:43:11 karels 21 20
c simplifications; count external interfaces; typos
e
s 00007/00001/00372
d D 6.8 85/06/08 12:37:23 mckusick 20 19
c Add copyright
e
s 00001/00000/00372
d D 6.7 85/04/16 09:57:23 karels 19 18
c missing return
e
s 00276/00104/00096
d D 6.6 85/03/18 15:50:08 karels 18 17
c move net addresses from interface to protocol layer;
c ioctls (PRU_CONTROL) move to protocol, new ioctls to get/set netmask,
c broadcast addr
e
s 00030/00000/00170
d D 6.5 84/10/19 15:02:36 karels 17 16
c bind local address according to routing (caching the route);
c pick maximum seg sizes (offered and accepted) based on interface mtu,
c with default if not local
e
s 00007/00007/00163
d D 6.4 84/08/29 15:35:51 bloom 16 15
c Include file changes.  No more ../h
e
s 00062/00034/00108
d D 6.3 84/04/24 17:28:24 karels 15 14
c fix to subnet routing (for initial calculation of if_net's)
e
s 00053/00012/00089
d D 6.2 84/04/12 11:31:54 karels 14 13
c subnet routing
e
s 00000/00000/00101
d D 6.1 83/07/29 07:11:08 sam 13 12
c 4.2 distribution
e
s 00002/00002/00099
d D 4.12 83/03/14 14:52:09 sam 12 11
c didn't match class b & c nets correctly
e
s 00000/00002/00101
d D 4.11 82/11/13 23:11:27 sam 11 10
c merge 4.1b with 4.1c
e
s 00003/00014/00100
d D 4.10 82/10/30 13:02:37 root 10 9
c get rid of conditional htons/ntohs etc
e
s 00002/00002/00112
d D 4.9 82/10/21 21:05:33 root 9 8
c lint
e
s 00002/00000/00112
d D 4.8 82/10/20 03:16:05 root 8 7
c lint
e
s 00015/00012/00097
d D 4.7 82/10/20 01:22:04 root 7 6
c lint
e
s 00001/00001/00108
d D 4.6 82/10/17 22:47:12 root 6 5
c lint
e
s 00028/00013/00081
d D 4.5 82/10/17 14:54:23 root 5 4
c fix lint
e
s 00002/00002/00092
d D 4.4 82/10/09 05:44:46 wnj 4 3
c localize header files
e
s 00000/00004/00094
d D 4.3 82/06/20 00:53:47 sam 3 2
c purge COUNT stuff now that we can use gprof
e
s 00002/00000/00096
d D 4.2 82/06/13 23:01:23 sam 2 1
c add class a/b/c net #'s and purge logical host kludge code
e
s 00096/00000/00000
d D 4.1 82/06/13 14:10:27 sam 1 0
c date and time created 82/06/13 14:10:27 by sam
e
u
U
t
T
I 1
D 20
/*	%M%	%I%	%E%	*/
E 20
I 20
/*
D 29
 * Copyright (c) 1982 Regents of the University of California.
E 29
I 29
D 45
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 45
I 45
D 64
 * Copyright (c) 1982, 1986, 1991 Regents of the University of California.
E 45
E 29
D 34
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 34
I 34
 * All rights reserved.
E 64
I 64
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 64
 *
D 43
 * Redistribution and use in source and binary forms are permitted
D 37
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 37
I 37
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
E 43
I 43
 * %sccs.include.redist.c%
E 43
E 37
E 34
 *
 *	%W% (Berkeley) %G%
 */
E 20

D 16
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
D 4
#include "../net/in.h"
#include "../net/in_systm.h"
E 4
I 4
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
E 16
I 16
D 55
#include "param.h"
I 18
#include "ioctl.h"
I 46
#include "errno.h"
E 46
E 18
D 54
#include "mbuf.h"
E 54
I 54
#include "malloc.h"
E 54
D 45
#include "protosw.h"
E 45
#include "socket.h"
#include "socketvar.h"
D 18
#include "in.h"
E 18
I 18
D 40
#include "uio.h"
#include "dir.h"
E 40
D 45
#include "user.h"
E 45
E 18
#include "in_systm.h"
E 16
E 4
I 2
D 45
#include "../net/if.h"
#include "../net/route.h"
E 2
#include "../net/af.h"
E 45
I 45
#include "net/if.h"
#include "net/route.h"
#include "net/af.h"
E 45
I 18
#include "in.h"
#include "in_var.h"
E 55
I 55
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/malloc.h>
#include <sys/socket.h>
#include <sys/socketvar.h>

#include <net/if.h>
#include <net/route.h>
D 65
#include <net/af.h>
E 65

#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/in_var.h>
I 62
#include <netinet/if_ether.h>
E 62
E 55
E 18

#ifdef INET
D 38
inet_hash(sin, hp)
	register struct sockaddr_in *sin;
	struct afhash *hp;
{
I 18
	register u_long n;
E 18
I 5

E 5
D 3
COUNT(INET_HASH);
E 3
D 18
	hp->afh_nethash = in_netof(sin->sin_addr);
E 18
I 18
	n = in_netof(sin->sin_addr);
	if (n)
	    while ((n & 0xff) == 0)
		n >>= 8;
	hp->afh_nethash = n;
E 18
D 7
	hp->afh_hosthash = ntohl(sin->sin_addr.s_addr);
E 7
I 7
D 10
	hp->afh_hosthash = sin->sin_addr.s_addr;
#if vax || pdp11 || ns16032
	hp->afh_hosthash = ntohl((u_long)hp->afh_hosthash);
D 9
#else
E 9
I 9
#endif
E 10
I 10
	hp->afh_hosthash = ntohl(sin->sin_addr.s_addr);
E 10
E 9
E 7
D 5
	if (hp->afh_hosthash < 0)
		hp->afh_hosthash = -hp->afh_hosthash;
E 5
}

inet_netmatch(sin1, sin2)
	struct sockaddr_in *sin1, *sin2;
{
I 5

E 5
D 3
COUNT(INET_NETMATCH);
E 3
D 12
	return (sin1->sin_addr.s_net == sin2->sin_addr.s_net);
E 12
I 12
	return (in_netof(sin1->sin_addr) == in_netof(sin2->sin_addr));
E 12
}

E 38
/*
D 18
 * Formulate an Internet address from network + host.  Used in
 * building addresses stored in the ifnet structure.
E 18
I 18
D 61
 * Formulate an Internet address from network + host.
E 18
 */
struct in_addr
D 18
if_makeaddr(net, host)
	int net, host;
E 18
I 18
in_makeaddr(net, host)
	u_long net, host;
E 18
{
I 18
	register struct in_ifaddr *ia;
	register u_long mask;
E 18
	u_long addr;

D 3
COUNT(IF_MAKEADDR);
E 3
D 14
	if (net < 128)
E 14
I 14
D 18
	if (net < IN_CLASSA_MAX)
E 14
D 5
		addr = (net << 24) | host;
E 5
I 5
D 7
		addr = (net << IN_CLASSANSHIFT) | host;
E 7
I 7
		addr = (net << IN_CLASSA_NSHIFT) | host;
E 7
E 5
D 14
	else if (net < 65536)
E 14
I 14
	else if (net < IN_CLASSB_MAX)
E 14
D 5
		addr = (net << 16) | host;
E 5
I 5
D 7
		addr = (net << IN_CLASSBNSHIFT) | host;
E 7
I 7
		addr = (net << IN_CLASSB_NSHIFT) | host;
E 18
I 18
	if (IN_CLASSA(net))
		mask = IN_CLASSA_HOST;
	else if (IN_CLASSB(net))
		mask = IN_CLASSB_HOST;
E 18
E 7
E 5
	else
D 5
		addr = (net << 8) | host;
#ifdef vax
E 5
I 5
D 7
		addr = (net << IN_CLASSCNSHIFT) | host;
E 7
I 7
D 18
		addr = (net << IN_CLASSC_NSHIFT) | host;
E 7
D 10
#ifdef vax || pdp11 || ns16032
E 10
E 5
	addr = htonl(addr);
E 18
I 18
		mask = IN_CLASSC_HOST;
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
		if ((ia->ia_netmask & net) == ia->ia_net) {
			mask = ~ia->ia_subnetmask;
			break;
		}
	addr = htonl(net | (host & mask));
E 18
D 10
#endif
E 10
	return (*(struct in_addr *)&addr);
}

/*
E 61
D 5
 * Return the network number from an internet
 * address; handles class a/b/c network #'s.
E 5
I 5
 * Return the network number from an internet address.
E 5
 */
I 21
u_long
E 21
in_netof(in)
	struct in_addr in;
{
I 5
D 7
	register u_int i = in.s_addr;
E 7
I 7
D 10
	register u_long i = in.s_addr;
E 10
I 10
	register u_long i = ntohl(in.s_addr);
I 14
D 15
	register net;
E 15
I 15
D 18
	register u_long net, subnet;
	register struct ifnet *ifp;
E 18
I 18
	register u_long net;
	register struct in_ifaddr *ia;
E 18
E 15
E 14
E 10
E 7
E 5

D 5
	return (IN_NETOF(in));
E 5
I 5
D 10
#ifdef vax || pdp11 || ns16032
	i = ntohl(i);
#endif
E 10
D 14
	if (IN_CLASSA(i))
D 7
		return (((i)&IN_CLASSANET) >> IN_CLASSANSHIFT);
E 7
I 7
		return (((i)&IN_CLASSA_NET) >> IN_CLASSA_NSHIFT);
E 7
	else if (IN_CLASSB(i))
D 7
		return (((i)&IN_CLASSBNET) >> IN_CLASSBNSHIFT);
E 7
I 7
		return (((i)&IN_CLASSB_NET) >> IN_CLASSB_NSHIFT);
E 7
	else
E 14
I 14
D 18
	if (IN_CLASSA(i)) {
D 15
		net = ((i)&IN_CLASSA_NET) >> IN_CLASSA_NSHIFT;
		if (in_localnet(net) && IN_SUBNETA(i))
			return (((i)&IN_CLASSA_SUBNET) >> IN_CLASSA_SUBNSHIFT);
		else
E 15
I 15
		net = (i & IN_CLASSA_NET) >> IN_CLASSA_NSHIFT;
		if (IN_SUBNETA(i)) {
			subnet = (i & IN_CLASSA_SUBNET) >> IN_CLASSA_SUBNSHIFT;
			/* Fall through and check whether a subnet */
		} else
E 15
			return (net);
	} else if (IN_CLASSB(i)) {
D 15
		net = ((i)&IN_CLASSB_NET) >> IN_CLASSB_NSHIFT;
		if (in_localnet(net) && IN_SUBNETB(i))
			return (((i)&IN_CLASSB_SUBNET) >> IN_CLASSB_SUBNSHIFT);
		else
E 15
I 15
		net = (i & IN_CLASSB_NET) >> IN_CLASSB_NSHIFT;
		if (IN_SUBNETB(i)) {
			subnet = (i & IN_CLASSB_SUBNET) >> IN_CLASSB_SUBNSHIFT;
			/* Fall through and check whether a subnet */
		} else
E 15
			return (net);
	} else {
E 14
D 7
		return (((i)&IN_CLASSCNET) >> IN_CLASSCNSHIFT);
E 7
I 7
D 15
		return (((i)&IN_CLASSC_NET) >> IN_CLASSC_NSHIFT);
E 15
I 15
		return ((i & IN_CLASSC_NET) >> IN_CLASSC_NSHIFT);
E 15
I 14
	}
E 18
I 18
	if (IN_CLASSA(i))
		net = i & IN_CLASSA_NET;
	else if (IN_CLASSB(i))
		net = i & IN_CLASSB_NET;
D 33
	else
E 33
I 33
	else if (IN_CLASSC(i))
E 33
		net = i & IN_CLASSC_NET;
I 54
D 56
#ifdef MULTICAST
E 56
	else if (IN_CLASSD(i))
		net = i & IN_CLASSD_NET;
D 56
#endif
E 56
E 54
I 33
	else
		return (0);
E 33
E 18
I 15

	/*
D 18
	 * Check whether network is a subnet of a `local' network;
E 18
I 18
	 * Check whether network is a subnet;
E 18
	 * if so, return subnet number.
	 */
D 18
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		if (ifp->if_addr.sa_family != AF_INET)
			continue;
		if (ifp->if_flags & IFF_LOCAL) {
			if (ifp->if_net == net)
				return (subnet);
			if ((ifp->if_net >> SUBNETSHIFT) == net)
				return (subnet);
			/*
			 * Hack for use in setting if_net initially.
			 */
			if (ifp->if_net == 0) {
				register struct sockaddr_in *sin;
				sin = (struct sockaddr_in *) &ifp->if_addr;
				if (sin->sin_addr.s_addr == in.s_addr)
					return (subnet);
			}
		}
	}
E 18
I 18
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
D 21
		if ((ia->ia_netmask & net) == ia->ia_net)
E 21
I 21
		if (net == ia->ia_net)
E 21
			return (i & ia->ia_subnetmask);
E 18
	return (net);
E 15
E 14
E 7
E 5
D 61
}

I 8
D 9
#ifndef notdef
E 9
I 9
D 11
#ifdef notdef
E 11
E 9
E 8
/*
I 38
 * Compute and save network mask as sockaddr from an internet address.
 */
in_sockmaskof(in, sockmask)
	struct in_addr in;
	register struct sockaddr_in *sockmask;
{
	register u_long net;
	register u_long mask;
    {
	register u_long i = ntohl(in.s_addr);

	if (i == 0)
		net = 0, mask = 0;
	else if (IN_CLASSA(i))
		net = i & IN_CLASSA_NET, mask = IN_CLASSA_NET;
	else if (IN_CLASSB(i))
		net = i & IN_CLASSB_NET, mask = IN_CLASSB_NET;
	else if (IN_CLASSC(i))
		net = i & IN_CLASSC_NET, mask = IN_CLASSC_NET;
	else
		net = i, mask = -1;
    }
    {
	register struct in_ifaddr *ia;
	/*
	 * Check whether network is a subnet;
	 * if so, return subnet number.
	 */
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
		if (net == ia->ia_net)
			mask =  ia->ia_subnetmask;
    }
    {
D 41
	register char *cp = (char *)&(sockmask->sin_port);
E 41
	register char *cpbase = (char *)&(sockmask->sin_addr);
I 41
	register char *cp = (char *)(1 + &(sockmask->sin_addr));
E 41

	sockmask->sin_addr.s_addr = htonl(mask);
	sockmask->sin_len = 0;
	while (--cp >= cpbase)
		if (*cp) {
			sockmask->sin_len = 1 + cp - (caddr_t)sockmask;
			break;
		}
    }
E 61
}

D 60
/*
E 38
D 5
 * Return the local network address portion of an
 * internet address; handles class a/b/c network
 * number formats.
E 5
I 5
 * Return the host portion of an internet address.
E 5
 */
I 25
u_long
E 25
in_lnaof(in)
	struct in_addr in;
{
I 5
D 7
	register u_int i = in.s_addr;
E 7
I 7
D 10
	register u_long i = in.s_addr;
E 10
I 10
	register u_long i = ntohl(in.s_addr);
I 15
D 18
	register u_long net, host, subhost;
	register struct ifnet *ifp;
E 18
I 18
	register u_long net, host;
	register struct in_ifaddr *ia;
E 18
E 15
E 10
E 7
E 5

D 5
	return (IN_LNAOF(in));
E 5
I 5
D 10
#ifdef vax || pdp11 || ns16032
	i = ntohl(i);
#endif
E 10
D 14
	if (IN_CLASSA(i))
D 7
		return ((i)&IN_CLASSAHOST);
E 7
I 7
		return ((i)&IN_CLASSA_HOST);
E 7
	else if (IN_CLASSB(i))
D 7
		return ((i)&IN_CLASSBHOST);
E 7
I 7
		return ((i)&IN_CLASSB_HOST);
E 7
	else
E 14
I 14
	if (IN_CLASSA(i)) {
D 15
		if (IN_SUBNETA(i) &&
		    in_localnet(((i)&IN_CLASSA_NET) >> IN_CLASSA_NSHIFT))
			return ((i)&IN_CLASSA_SUBHOST);
		else
			return ((i)&IN_CLASSA_HOST);
E 15
I 15
D 18
		if (IN_SUBNETA(i)) {
			net = (i & IN_CLASSA_NET) >> IN_CLASSA_NSHIFT;
			host = i & IN_CLASSA_HOST;
			subhost = i & IN_CLASSA_SUBHOST;
			/* Fall through and check whether a subnet */
		} else
			return (i & IN_CLASSA_HOST);
E 18
I 18
		net = i & IN_CLASSA_NET;
		host = i & IN_CLASSA_HOST;
E 18
E 15
	} else if (IN_CLASSB(i)) {
D 15
		if (IN_SUBNETB(i) &&
		    in_localnet(((i)&IN_CLASSB_NET) >> IN_CLASSB_NSHIFT) )
			return ((i)&IN_CLASSB_SUBHOST);
		else
			return ((i)&IN_CLASSB_HOST);
E 15
I 15
D 18
		if (IN_SUBNETB(i)) {
			net = (i & IN_CLASSB_NET) >> IN_CLASSB_NSHIFT;
			host = i & IN_CLASSB_HOST;
			subhost = i & IN_CLASSB_SUBHOST;
			/* Fall through and check whether a subnet */
		} else
			return (i & IN_CLASSB_HOST);
E 18
I 18
		net = i & IN_CLASSB_NET;
		host = i & IN_CLASSB_HOST;
E 18
E 15
D 33
	} else {
E 33
I 33
	} else if (IN_CLASSC(i)) {
E 33
E 14
D 7
		return ((i)&IN_CLASSCHOST);
E 7
I 7
D 15
		return ((i)&IN_CLASSC_HOST);
E 15
I 15
D 18
		return (i & IN_CLASSC_HOST);
E 18
I 18
		net = i & IN_CLASSC_NET;
		host = i & IN_CLASSC_HOST;
I 54
D 56
#ifdef MULTICAST
E 56
	} else if (IN_CLASSD(i)) {
		net = i & IN_CLASSD_NET;
		host = i & IN_CLASSD_HOST;
D 56
#endif
E 56
E 54
E 18
E 15
I 14
D 33
	}
E 33
I 33
	} else
		return (i);
E 33
D 15
}
E 15

D 15
/*
 * Return true if the network is a ``local'' net
 * (one for which we can interpret the host part).
 */
in_localnet(net)
	register int net;
{
	register struct ifnet *ifp;

E 15
I 15
	/*
D 18
	 * Check whether network is a subnet of a `local' network;
E 18
I 18
	 * Check whether network is a subnet;
E 18
	 * if so, use the modified interpretation of `host'.
	 */
E 15
D 18
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		if (ifp->if_addr.sa_family != AF_INET)
			continue;
		if (ifp->if_flags & IFF_LOCAL) {
			if (ifp->if_net == net)
D 15
				return (1);
E 15
I 15
			    return (subhost);
E 15
			if ((ifp->if_net >> SUBNETSHIFT) == net)
D 15
				return (1);
E 15
I 15
			    return (subhost);
E 15
		}
	}
E 18
I 18
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
D 21
		if ((ia->ia_netmask & net) == ia->ia_net)
E 21
I 21
		if (net == ia->ia_net)
E 21
			return (host &~ ia->ia_subnetmask);
E 18
D 15
	return (0);
E 15
I 15
	return (host);
E 15
E 14
E 7
E 5
}
I 8
D 11
#endif
E 11
E 8

E 60
I 25
#ifndef SUBNETSARELOCAL
#define	SUBNETSARELOCAL	1
#endif
int subnetsarelocal = SUBNETSARELOCAL;
E 25
/*
I 17
D 18
 * Return 1 if an internet address is for a ``local'' host.
E 18
I 18
 * Return 1 if an internet address is for a ``local'' host
D 21
 * (one to which we have a connection).
E 21
I 21
D 25
 * (one to which we have a connection through a local logical net).
E 25
I 25
 * (one to which we have a connection).  If subnetsarelocal
 * is true, this includes other subnets of the local net.
 * Otherwise, it includes only the directly-connected (sub)nets.
E 25
E 21
E 18
 */
in_localaddr(in)
	struct in_addr in;
{
	register u_long i = ntohl(in.s_addr);
D 32
	register u_long net;
E 32
D 18
	register struct ifnet *ifp;
E 18
I 18
	register struct in_ifaddr *ia;
E 18

D 32
	if (IN_CLASSA(i))
D 18
		net = (i & IN_CLASSA_NET) >> IN_CLASSA_NSHIFT;
E 18
I 18
		net = i & IN_CLASSA_NET;
E 18
	else if (IN_CLASSB(i))
D 18
		net = (i & IN_CLASSB_NET) >> IN_CLASSB_NSHIFT;
E 18
I 18
		net = i & IN_CLASSB_NET;
E 18
	else
D 18
		net = (i & IN_CLASSC_NET) >> IN_CLASSC_NSHIFT;
E 18
I 18
		net = i & IN_CLASSC_NET;
E 18

D 18
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		if (ifp->if_addr.sa_family != AF_INET)
			continue;
		if (ifp->if_flags & IFF_LOCAL) {
			if (ifp->if_net == net)
				return (1);
			if ((ifp->if_net >> SUBNETSHIFT) == net)
				return (1);
E 18
I 18
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
D 21
		if ((ia->ia_netmask & net) == ia->ia_net)
E 21
I 21
D 25
		if (net == ia->ia_net)
E 25
I 25
D 30
		if (net == subnetsarelocal ? ia->ia_net : ia->ia_subnet)
E 30
I 30
		if (net == (subnetsarelocal ? ia->ia_net : ia->ia_subnet))
E 30
E 25
E 21
			return (1);
E 32
I 32
	if (subnetsarelocal) {
		for (ia = in_ifaddr; ia; ia = ia->ia_next)
			if ((i & ia->ia_netmask) == ia->ia_net)
				return (1);
	} else {
		for (ia = in_ifaddr; ia; ia = ia->ia_next)
			if ((i & ia->ia_subnetmask) == ia->ia_subnet)
				return (1);
	}
E 32
	return (0);
I 33
}

/*
 * Determine whether an IP address is in a reserved set of addresses
 * that may not be forwarded, or whether datagrams to that destination
 * may be forwarded.
 */
in_canforward(in)
	struct in_addr in;
{
	register u_long i = ntohl(in.s_addr);
	register u_long net;

D 60
	if (IN_EXPERIMENTAL(i))
E 60
I 60
	if (IN_EXPERIMENTAL(i) || IN_MULTICAST(i))
E 60
		return (0);
	if (IN_CLASSA(i)) {
		net = i & IN_CLASSA_NET;
D 58
		if (net == 0 || net == IN_LOOPBACKNET)
E 58
I 58
		if (net == 0 || net == (IN_LOOPBACKNET << IN_CLASSA_NSHIFT))
E 58
			return (0);
	}
	return (1);
E 33
}

I 60
/*
 * Trim a mask in a sockaddr
 */
void
in_socktrim(ap)
struct sockaddr_in *ap;
{
    register char *cplim = (char *) &ap->sin_addr;
    register char *cp = (char *) (&ap->sin_addr + 1);

    ap->sin_len = 0;
D 66
    while (--cp > cplim)
E 66
I 66
    while (--cp >= cplim)
E 66
        if (*cp) {
	    (ap)->sin_len = cp - (char *) (ap) + 1;
	    break;
	}
}

E 60
I 21
int	in_interfaces;		/* number of external internet interfaces */
extern	struct ifnet loif;

E 21
/*
 * Generic internet control operations (ioctl's).
 * Ifp is 0 if not an interface-specific ioctl.
 */
I 21
/* ARGSUSED */
E 21
in_control(so, cmd, data, ifp)
	struct socket *so;
D 67
	int cmd;
E 67
I 67
	u_long cmd;
E 67
	caddr_t data;
	register struct ifnet *ifp;
{
	register struct ifreq *ifr = (struct ifreq *)data;
	register struct in_ifaddr *ia = 0;
I 22
D 35
	u_long tmp;
E 35
E 22
D 38
	struct ifaddr *ifa;
E 38
I 38
	register struct ifaddr *ifa;
	struct in_ifaddr *oia;
	struct in_aliasreq *ifra = (struct in_aliasreq *)data;
E 38
D 47
	struct mbuf *m;
E 47
D 38
	int error;
E 38
I 38
	struct sockaddr_in oldaddr;
	int error, hostIsNew, maskIsNew;
	u_long i;
E 38

	/*
	 * Find address for this interface, if it exists.
	 */
	if (ifp)
		for (ia = in_ifaddr; ia; ia = ia->ia_next)
			if (ia->ia_ifp == ifp)
				break;

	switch (cmd) {

I 38
	case SIOCAIFADDR:
	case SIOCDIFADDR:
		if (ifra->ifra_addr.sin_family == AF_INET)
		    for (oia = ia; ia; ia = ia->ia_next) {
			if (ia->ia_ifp == ifp  &&
			    ia->ia_addr.sin_addr.s_addr ==
				ifra->ifra_addr.sin_addr.s_addr)
			    break;
		}
		if (cmd == SIOCDIFADDR && ia == 0)
			return (EADDRNOTAVAIL);
		/* FALLTHROUGH */
E 38
D 24
	case SIOCGIFADDR:
	case SIOCGIFBRDADDR:
	case SIOCGIFDSTADDR:
	case SIOCGIFNETMASK:
		if (ia == (struct in_ifaddr *)0)
			return (EADDRNOTAVAIL);
		break;

E 24
	case SIOCSIFADDR:
D 24
	case SIOCSIFDSTADDR:
	case SIOCSIFBRDADDR:
E 24
	case SIOCSIFNETMASK:
I 27
	case SIOCSIFDSTADDR:
E 27
D 39
		if (!suser())
			return (u.u_error);
E 39
I 39
D 45
		if (error = suser(u.u_cred, &u.u_acflag))
			return (error);
E 45
I 45
		if ((so->so_state & SS_PRIV) == 0)
			return (EPERM);
E 45
E 39

		if (ifp == 0)
			panic("in_control");
		if (ia == (struct in_ifaddr *)0) {
D 47
			m = m_getclr(M_WAIT, MT_IFADDR);
			if (m == (struct mbuf *)NULL)
E 47
I 47
			oia = (struct in_ifaddr *)
				malloc(sizeof *oia, M_IFADDR, M_WAITOK);
			if (oia == (struct in_ifaddr *)NULL)
E 47
				return (ENOBUFS);
I 47
			bzero((caddr_t)oia, sizeof *oia);
E 47
			if (ia = in_ifaddr) {
				for ( ; ia->ia_next; ia = ia->ia_next)
D 53
					;
E 53
I 53
					continue;
E 53
D 47
				ia->ia_next = mtod(m, struct in_ifaddr *);
E 47
I 47
				ia->ia_next = oia;
E 47
			} else
D 47
				in_ifaddr = mtod(m, struct in_ifaddr *);
			ia = mtod(m, struct in_ifaddr *);
E 47
I 47
				in_ifaddr = oia;
			ia = oia;
E 47
			if (ifa = ifp->if_addrlist) {
				for ( ; ifa->ifa_next; ifa = ifa->ifa_next)
D 53
					;
E 53
I 53
					continue;
E 53
				ifa->ifa_next = (struct ifaddr *) ia;
			} else
				ifp->if_addrlist = (struct ifaddr *) ia;
I 38
			ia->ia_ifa.ifa_addr = (struct sockaddr *)&ia->ia_addr;
			ia->ia_ifa.ifa_dstaddr
					= (struct sockaddr *)&ia->ia_dstaddr;
			ia->ia_ifa.ifa_netmask
					= (struct sockaddr *)&ia->ia_sockmask;
			ia->ia_sockmask.sin_len = 8;
			if (ifp->if_flags & IFF_BROADCAST) {
				ia->ia_broadaddr.sin_len = sizeof(ia->ia_addr);
				ia->ia_broadaddr.sin_family = AF_INET;
			}
E 38
			ia->ia_ifp = ifp;
D 38
			IA_SIN(ia)->sin_family = AF_INET;
E 38
I 21
			if (ifp != &loif)
				in_interfaces++;
E 21
E 18
		}
I 18
		break;
I 24

	case SIOCSIFBRDADDR:
D 27
	case SIOCSIFDSTADDR:
E 27
D 39
		if (!suser())
			return (u.u_error);
E 39
I 39
D 45
		if (error = suser(u.u_cred, &u.u_acflag))
			return (error);
E 45
I 45
		if ((so->so_state & SS_PRIV) == 0)
			return (EPERM);
E 45
E 39
		/* FALLTHROUGH */

D 41
	default:
E 41
I 41
	case SIOCGIFADDR:
	case SIOCGIFNETMASK:
	case SIOCGIFDSTADDR:
	case SIOCGIFBRDADDR:
E 41
		if (ia == (struct in_ifaddr *)0)
			return (EADDRNOTAVAIL);
		break;
I 41
D 49

	default:
		return (EOPNOTSUPP);
		break;
E 49
E 41
E 24
E 18
	}
I 18
D 38

E 38
	switch (cmd) {

	case SIOCGIFADDR:
D 38
		ifr->ifr_addr = ia->ia_addr;
E 38
I 38
		*((struct sockaddr_in *)&ifr->ifr_addr) = ia->ia_addr;
E 38
		break;

	case SIOCGIFBRDADDR:
		if ((ifp->if_flags & IFF_BROADCAST) == 0)
			return (EINVAL);
D 38
		ifr->ifr_dstaddr = ia->ia_broadaddr;
E 38
I 38
		*((struct sockaddr_in *)&ifr->ifr_dstaddr) = ia->ia_broadaddr;
E 38
		break;

	case SIOCGIFDSTADDR:
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
D 38
		ifr->ifr_dstaddr = ia->ia_dstaddr;
E 38
I 38
		*((struct sockaddr_in *)&ifr->ifr_dstaddr) = ia->ia_dstaddr;
E 38
		break;

	case SIOCGIFNETMASK:
D 38
#define	satosin(sa)	((struct sockaddr_in *)(sa))
		satosin(&ifr->ifr_addr)->sin_family = AF_INET;
		satosin(&ifr->ifr_addr)->sin_addr.s_addr = htonl(ia->ia_subnetmask);
E 38
I 38
		*((struct sockaddr_in *)&ifr->ifr_addr) = ia->ia_sockmask;
E 38
		break;

	case SIOCSIFDSTADDR:
I 28
D 38
	    {
		struct sockaddr oldaddr;

E 38
E 28
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0)
			return (EINVAL);
I 28
		oldaddr = ia->ia_dstaddr;
D 38
		ia->ia_dstaddr = ifr->ifr_dstaddr;
E 38
I 38
		ia->ia_dstaddr = *(struct sockaddr_in *)&ifr->ifr_dstaddr;
E 38
E 28
D 52
		if (ifp->if_ioctl &&
D 21
		    (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ia)))
E 21
I 21
D 28
		    (error = (*ifp->if_ioctl)(ifp, SIOCSIFDSTADDR, ia)))
E 28
I 28
		    (error = (*ifp->if_ioctl)(ifp, SIOCSIFDSTADDR, ia))) {
E 52
I 52
		if (ifp->if_ioctl && (error = (*ifp->if_ioctl)
					(ifp, SIOCSIFDSTADDR, (caddr_t)ia))) {
E 52
			ia->ia_dstaddr = oldaddr;
E 28
E 21
			return (error);
D 28
		ia->ia_dstaddr = ifr->ifr_dstaddr;
E 28
I 28
		}
		if (ia->ia_flags & IFA_ROUTE) {
D 38
			rtinit(&oldaddr, &ia->ia_addr, (int)SIOCDELRT,
			    RTF_HOST);
			rtinit(&ia->ia_dstaddr, &ia->ia_addr, (int)SIOCADDRT,
			    RTF_HOST|RTF_UP);
E 38
I 38
			ia->ia_ifa.ifa_dstaddr = (struct sockaddr *)&oldaddr;
			rtinit(&(ia->ia_ifa), (int)RTM_DELETE, RTF_HOST);
D 44
			ia->ia_ifa.ifa_dstaddr = (struct sockaddr *)&ia->ia_addr;
E 44
I 44
			ia->ia_ifa.ifa_dstaddr =
					(struct sockaddr *)&ia->ia_dstaddr;
E 44
			rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_HOST|RTF_UP);
E 38
		}
D 38
	    }
E 38
E 28
		break;

	case SIOCSIFBRDADDR:
		if ((ifp->if_flags & IFF_BROADCAST) == 0)
			return (EINVAL);
D 38
		ia->ia_broadaddr = ifr->ifr_broadaddr;
E 38
I 38
		ia->ia_broadaddr = *(struct sockaddr_in *)&ifr->ifr_broadaddr;
E 38
I 22
D 35
		tmp = ntohl(satosin(&ia->ia_broadaddr)->sin_addr.s_addr);
		if ((tmp &~ ia->ia_subnetmask) == ~ia->ia_subnetmask)
			tmp |= ~ia->ia_netmask;
		else if ((tmp &~ ia->ia_subnetmask) == 0)
			tmp &= ia->ia_netmask;
		ia->ia_netbroadcast.s_addr = htonl(tmp);
E 35
E 22
		break;

	case SIOCSIFADDR:
D 36
		return (in_ifinit(ifp, ia, &ifr->ifr_addr));
E 36
I 36
		return (in_ifinit(ifp, ia,
D 38
		    (struct sockaddr_in *) &ifr->ifr_addr));
E 38
I 38
		    (struct sockaddr_in *) &ifr->ifr_addr, 1));
E 38
E 36
D 21
		break;
E 21

	case SIOCSIFNETMASK:
D 38
		ia->ia_subnetmask = ntohl(satosin(&ifr->ifr_addr)->sin_addr.s_addr);
E 38
I 38
		i = ifra->ifra_addr.sin_addr.s_addr;
		ia->ia_subnetmask = ntohl(ia->ia_sockmask.sin_addr.s_addr = i);
E 38
		break;

I 38
	case SIOCAIFADDR:
D 42
		maskIsNew = 0; hostIsNew = 1; error = u.u_error;
E 42
I 42
		maskIsNew = 0;
		hostIsNew = 1;
		error = 0;
E 42
		if (ia->ia_addr.sin_family == AF_INET) {
			if (ifra->ifra_addr.sin_len == 0) {
				ifra->ifra_addr = ia->ia_addr;
				hostIsNew = 0;
			} else if (ifra->ifra_addr.sin_addr.s_addr ==
					       ia->ia_addr.sin_addr.s_addr)
				hostIsNew = 0;
		}
		if (ifra->ifra_mask.sin_len) {
			in_ifscrub(ifp, ia);
			ia->ia_sockmask = ifra->ifra_mask;
			ia->ia_subnetmask =
D 42
					ntohl(ia->ia_sockmask.sin_addr.s_addr);
E 42
I 42
			     ntohl(ia->ia_sockmask.sin_addr.s_addr);
E 42
			maskIsNew = 1;
		}
		if ((ifp->if_flags & IFF_POINTOPOINT) &&
		    (ifra->ifra_dstaddr.sin_family == AF_INET)) {
			in_ifscrub(ifp, ia);
			ia->ia_dstaddr = ifra->ifra_dstaddr;
			maskIsNew  = 1; /* We lie; but the effect's the same */
		}
		if (ifra->ifra_addr.sin_family == AF_INET &&
D 42
					    (hostIsNew || maskIsNew))
E 42
I 42
		    (hostIsNew || maskIsNew))
E 42
			error = in_ifinit(ifp, ia, &ifra->ifra_addr, 0);
		if ((ifp->if_flags & IFF_BROADCAST) &&
		    (ifra->ifra_broadaddr.sin_family == AF_INET))
			ia->ia_broadaddr = ifra->ifra_broadaddr;
		return (error);

	case SIOCDIFADDR:
		in_ifscrub(ifp, ia);
		if ((ifa = ifp->if_addrlist) == (struct ifaddr *)ia)
			ifp->if_addrlist = ifa->ifa_next;
		else {
			while (ifa->ifa_next &&
			       (ifa->ifa_next != (struct ifaddr *)ia))
				    ifa = ifa->ifa_next;
			if (ifa->ifa_next)
D 42
			    ifa->ifa_next = ((struct ifaddr *)ia)->ifa_next;
E 42
I 42
				ifa->ifa_next = ((struct ifaddr *)ia)->ifa_next;
E 42
			else
				printf("Couldn't unlink inifaddr from ifp\n");
		}
		oia = ia;
D 42
		if (oia == (ia = in_ifaddr)) {
E 42
I 42
		if (oia == (ia = in_ifaddr))
E 42
			in_ifaddr = ia->ia_next;
D 42
		} else {
			while (ia->ia_next && (ia->ia_next != oia)) {
E 42
I 42
		else {
			while (ia->ia_next && (ia->ia_next != oia))
E 42
				ia = ia->ia_next;
D 42
			}
E 42
			if (ia->ia_next)
D 42
			    ia->ia_next = oia->ia_next;
E 42
I 42
				ia->ia_next = oia->ia_next;
E 42
			else
				printf("Didn't unlink inifadr from list\n");
		}
D 47
		(void) m_free(dtom(oia));
E 47
I 47
		IFAFREE((&oia->ia_ifa));
E 47
		break;

E 38
	default:
		if (ifp == 0 || ifp->if_ioctl == 0)
			return (EOPNOTSUPP);
		return ((*ifp->if_ioctl)(ifp, cmd, data));
	}
E 18
	return (0);
}

/*
I 38
 * Delete any existing route for an interface.
 */
I 62
void
E 62
in_ifscrub(ifp, ia)
	register struct ifnet *ifp;
	register struct in_ifaddr *ia;
{

	if ((ia->ia_flags & IFA_ROUTE) == 0)
		return;
	if (ifp->if_flags & (IFF_LOOPBACK|IFF_POINTOPOINT))
		rtinit(&(ia->ia_ifa), (int)RTM_DELETE, RTF_HOST);
	else
		rtinit(&(ia->ia_ifa), (int)RTM_DELETE, 0);
	ia->ia_flags &= ~IFA_ROUTE;
}

/*
E 38
E 17
D 18
 * Initialize an interface's routing
 * table entry according to the network.
 * INTERNET SPECIFIC.
E 18
I 18
 * Initialize an interface's internet address
 * and routing table entry.
E 18
 */
D 18
if_rtinit(ifp, flags)
E 18
I 18
D 38
in_ifinit(ifp, ia, sin)
E 38
I 38
in_ifinit(ifp, ia, sin, scrub)
E 38
E 18
	register struct ifnet *ifp;
D 18
	int flags;
E 18
I 18
	register struct in_ifaddr *ia;
	struct sockaddr_in *sin;
I 48
	int scrub;
E 48
E 18
{
D 18
	struct sockaddr_in sin;
E 18
I 18
	register u_long i = ntohl(sin->sin_addr.s_addr);
D 24
	struct sockaddr_in netaddr;
E 24
I 24
D 28
	struct sockaddr_in tmpaddr;
E 28
I 28
D 38
	struct sockaddr oldaddr;
	struct sockaddr_in netaddr;
E 38
I 38
	struct sockaddr_in oldaddr;
E 38
E 28
E 24
D 44
	int s = splimp(), error;
E 44
I 44
D 54
	int s = splimp(), error, flags = RTF_UP;
I 46
	int ether_output(), arp_rtrequest();
E 54
I 54
	int s = splimp(), flags = RTF_UP, error, ether_output();
D 62
	void arp_rtrequest();
E 62
E 54
E 46
E 44
E 18

D 3
COUNT(IF_RTINIT);
E 3
D 18
	if (ifp->if_flags & IFF_ROUTE)
		return;
	bzero((caddr_t)&sin, sizeof (sin));
	sin.sin_family = AF_INET;
D 12
	sin.sin_addr = if_makeaddr(ifp->if_net, 0);
E 12
I 12
	sin.sin_addr = if_makeaddr(ifp->if_net, INADDR_ANY);
E 12
D 6
	rtinit(&sin, &ifp->if_addr, flags);
E 6
I 6
	rtinit((struct sockaddr *)&sin, &ifp->if_addr, flags);
E 18
I 18
D 24
	bzero((caddr_t)&netaddr, sizeof (netaddr));
	netaddr.sin_family = AF_INET;
E 24
I 24
D 28
	tmpaddr = *(struct sockaddr_in *)&ia->ia_addr;
E 28
I 28
	oldaddr = ia->ia_addr;
E 28
D 38
	ia->ia_addr = *(struct sockaddr *)sin;

E 38
I 38
	ia->ia_addr = *sin;
E 38
E 24
	/*
I 24
	 * Give the interface a chance to initialize
	 * if this is its first address,
	 * and to validate the address if necessary.
	 */
D 48
	if (ifp->if_ioctl && (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ia))) {
E 48
I 48
	if (ifp->if_ioctl &&
	    (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, (caddr_t)ia))) {
E 48
		splx(s);
D 28
		ia->ia_addr = *(struct sockaddr *)&tmpaddr;
E 28
I 28
		ia->ia_addr = oldaddr;
E 28
		return (error);
I 46
	}
	if (ifp->if_output == ether_output) { /* XXX: Another Kludge */
		ia->ia_ifa.ifa_rtrequest = arp_rtrequest;
		ia->ia_ifa.ifa_flags |= RTF_CLONING;
E 46
	}
I 44
	splx(s);
E 44
D 38

D 28
	bzero((caddr_t)&tmpaddr, sizeof (tmpaddr));
	tmpaddr.sin_family = AF_INET;
E 28
	/*
E 24
	 * Delete any previous route for an old address.
	 */
I 28
	bzero((caddr_t)&netaddr, sizeof (netaddr));
	netaddr.sin_family = AF_INET;
E 28
	if (ia->ia_flags & IFA_ROUTE) {
D 28
		if ((ifp->if_flags & IFF_POINTOPOINT) == 0) {
D 24
		    netaddr.sin_addr = in_makeaddr(ia->ia_subnet, INADDR_ANY);
D 23
		    rtinit((struct sockaddr *)&netaddr, &ia->ia_addr, -1);
E 23
I 23
		    rtinit((struct sockaddr *)&netaddr, &ia->ia_addr, 
E 24
I 24
		    tmpaddr.sin_addr = in_makeaddr(ia->ia_subnet, INADDR_ANY);
		    rtinit((struct sockaddr *)&tmpaddr, &ia->ia_addr, 
E 28
I 28
		if (ifp->if_flags & IFF_LOOPBACK)
			rtinit(&oldaddr, &oldaddr, (int)SIOCDELRT, RTF_HOST);
		else if (ifp->if_flags & IFF_POINTOPOINT)
			rtinit(&ia->ia_dstaddr, &oldaddr, (int)SIOCDELRT,
			    RTF_HOST);
		else {
			netaddr.sin_addr = in_makeaddr(ia->ia_subnet,
			    INADDR_ANY);
			rtinit((struct sockaddr *)&netaddr, &oldaddr, 
E 28
E 24
			    (int)SIOCDELRT, 0);
E 23
D 28
		} else
D 23
		    rtinit((struct sockaddr *)&ia->ia_dstaddr, &ia->ia_addr, -1);
E 23
I 23
		    rtinit((struct sockaddr *)&ia->ia_dstaddr, &ia->ia_addr,
			    (int)SIOCDELRT, RTF_HOST);
E 28
I 28
		}
E 28
E 23
		ia->ia_flags &= ~IFA_ROUTE;
E 38
I 38
	if (scrub) {
		ia->ia_ifa.ifa_addr = (struct sockaddr *)&oldaddr;
		in_ifscrub(ifp, ia);
		ia->ia_ifa.ifa_addr = (struct sockaddr *)&ia->ia_addr;
E 38
	}
D 24
	ia->ia_addr = *(struct sockaddr *)sin;
E 24
	if (IN_CLASSA(i))
		ia->ia_netmask = IN_CLASSA_NET;
	else if (IN_CLASSB(i))
		ia->ia_netmask = IN_CLASSB_NET;
	else
		ia->ia_netmask = IN_CLASSC_NET;
D 63
	ia->ia_net = i & ia->ia_netmask;
E 63
	/*
D 63
	 * The subnet mask includes at least the standard network part,
	 * but may already have been set to a larger value.
E 63
I 63
	 * The subnet mask usually includes at least the standard network part,
	 * but may may be smaller in the case of supernetting.
	 * If it is set, we believe it.
E 63
	 */
D 63
	ia->ia_subnetmask |= ia->ia_netmask;
E 63
I 63
	if (ia->ia_subnetmask == 0) {
		ia->ia_subnetmask = ia->ia_netmask;
		ia->ia_sockmask.sin_addr.s_addr = htonl(ia->ia_subnetmask);
	} else
		ia->ia_netmask &= ia->ia_subnetmask;
	ia->ia_net = i & ia->ia_netmask;
E 63
	ia->ia_subnet = i & ia->ia_subnetmask;
I 38
D 63
	ia->ia_sockmask.sin_addr.s_addr = htonl(ia->ia_subnetmask);
E 63
I 41
D 60
	{
		register char *cp = (char *) (1 + &(ia->ia_sockmask.sin_addr));
		register char *cpbase = (char *) &(ia->ia_sockmask.sin_addr);
		while (--cp >= cpbase)
			if (*cp) {
				ia->ia_sockmask.sin_len =
					1 + cp - (char *) &(ia->ia_sockmask);
				break;
			}
	}
E 60
I 60
	in_socktrim(&ia->ia_sockmask);
E 60
I 44
	/*
	 * Add route for the network.
	 */
I 51
	ia->ia_ifa.ifa_metric = ifp->if_metric;
E 51
E 44
E 41
E 38
	if (ifp->if_flags & IFF_BROADCAST) {
D 38
		ia->ia_broadaddr.sa_family = AF_INET;
		((struct sockaddr_in *)(&ia->ia_broadaddr))->sin_addr =
E 38
I 38
D 60
		ia->ia_broadaddr.sin_addr = 
E 38
			in_makeaddr(ia->ia_subnet, INADDR_BROADCAST);
E 60
I 60
		ia->ia_broadaddr.sin_addr.s_addr =
			htonl(ia->ia_subnet | ~ia->ia_subnetmask);
E 60
I 22
		ia->ia_netbroadcast.s_addr =
D 60
		    htonl(ia->ia_net | (INADDR_BROADCAST &~ ia->ia_netmask));
E 60
I 60
			htonl(ia->ia_net | ~ ia->ia_netmask);
E 60
E 22
D 44
	}
D 24

	/*
	 * Give the interface a chance to initialize
	 * if this is its first address,
	 * and to validate the address if necessary.
	 */
	if (ifp->if_ioctl && (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ia))) {
		splx(s);
		bzero((caddr_t)&ia->ia_addr, sizeof(ia->ia_addr));
		return (error);
	}
E 24
D 31
	splx(s);
E 31
	/*
	 * Add route for the network.
	 */
D 28
	if ((ifp->if_flags & IFF_POINTOPOINT) == 0) {
D 24
		netaddr.sin_addr = in_makeaddr(ia->ia_subnet, INADDR_ANY);
D 23
		rtinit((struct sockaddr *)&netaddr, &ia->ia_addr, RTF_UP);
E 23
I 23
		rtinit((struct sockaddr *)&netaddr, &ia->ia_addr,
E 24
I 24
		tmpaddr.sin_addr = in_makeaddr(ia->ia_subnet, INADDR_ANY);
		rtinit((struct sockaddr *)&tmpaddr, &ia->ia_addr,
E 24
			(int)SIOCADDRT, RTF_UP);
E 23
	} else
		rtinit((struct sockaddr *)&ia->ia_dstaddr, &ia->ia_addr,
D 23
			RTF_HOST|RTF_UP);
E 23
I 23
			(int)SIOCADDRT, RTF_HOST|RTF_UP);
E 28
I 28
D 38
	if (ifp->if_flags & IFF_LOOPBACK)
		rtinit(&ia->ia_addr, &ia->ia_addr, (int)SIOCADDRT,
		    RTF_HOST|RTF_UP);
	else if (ifp->if_flags & IFF_POINTOPOINT)
		rtinit(&ia->ia_dstaddr, &ia->ia_addr, (int)SIOCADDRT,
		    RTF_HOST|RTF_UP);
E 38
I 38
	if (ifp->if_flags & IFF_LOOPBACK) {
E 44
I 44
	} else if (ifp->if_flags & IFF_LOOPBACK) {
E 44
		ia->ia_ifa.ifa_dstaddr = ia->ia_ifa.ifa_addr;
D 44
		rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_HOST|RTF_UP);
	} else if (ifp->if_flags & IFF_POINTOPOINT &&
		 ia->ia_dstaddr.sin_family == AF_INET)
		rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_HOST|RTF_UP);
E 38
	else {
D 38
		netaddr.sin_addr = in_makeaddr(ia->ia_subnet, INADDR_ANY);
		rtinit((struct sockaddr *)&netaddr, &ia->ia_addr,
		    (int)SIOCADDRT, RTF_UP);
E 38
I 38
		rtinit(&(ia->ia_ifa), (int)RTM_ADD, RTF_UP);
E 44
I 44
		flags |= RTF_HOST;
	} else if (ifp->if_flags & IFF_POINTOPOINT) {
		if (ia->ia_dstaddr.sin_family != AF_INET)
			return (0);
		flags |= RTF_HOST;
E 44
E 38
	}
E 28
E 23
D 44
	ia->ia_flags |= IFA_ROUTE;
I 31
	splx(s);
E 31
I 19
	return (0);
E 44
I 44
	if ((error = rtinit(&(ia->ia_ifa), (int)RTM_ADD, flags)) == 0)
		ia->ia_flags |= IFA_ROUTE;
I 54
D 56
#ifdef MULTICAST
E 56
	/*
	 * If the interface supports multicast, join the "all hosts"
	 * multicast group on that interface.
	 */
	if (ifp->if_flags & IFF_MULTICAST) {
		struct in_addr addr;

		addr.s_addr = htonl(INADDR_ALLHOSTS_GROUP);
		in_addmulti(&addr, ifp);
	}
D 56
#endif
E 56
E 54
	return (error);
E 44
E 19
}

D 60
/*
 * Return address info for specified internet network.
 */
struct in_ifaddr *
in_iaonnetof(net)
	u_long net;
{
	register struct in_ifaddr *ia;
E 60

D 60
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
		if (ia->ia_subnet == net)
			return (ia);
	return ((struct in_ifaddr *)0);
}

E 60
/*
D 31
 * Return 1 if the address is a local broadcast address.
E 31
I 31
 * Return 1 if the address might be a local broadcast address.
E 31
 */
D 60
in_broadcast(in)
E 60
I 60
in_broadcast(in, ifp)
E 60
	struct in_addr in;
I 60
        struct ifnet *ifp;
E 60
{
D 60
	register struct in_ifaddr *ia;
E 60
I 60
	register struct ifaddr *ifa;
E 60
I 31
	u_long t;
E 31

I 60
	if (in.s_addr == INADDR_BROADCAST ||
	    in.s_addr == INADDR_ANY)
		return 1;
	if ((ifp->if_flags & IFF_BROADCAST) == 0)
		return 0;
	t = ntohl(in.s_addr);
E 60
	/*
	 * Look through the list of addresses for a match
	 * with a broadcast address.
	 */
D 60
	for (ia = in_ifaddr; ia; ia = ia->ia_next)
D 31
	    if (((struct sockaddr_in *)&ia->ia_broadaddr)->sin_addr.s_addr ==
		in.s_addr && (ia->ia_ifp->if_flags & IFF_BROADCAST))
E 31
I 31
	    if (ia->ia_ifp->if_flags & IFF_BROADCAST) {
D 38
		if (satosin(&ia->ia_broadaddr)->sin_addr.s_addr == in.s_addr)
E 38
I 38
		if (ia->ia_broadaddr.sin_addr.s_addr == in.s_addr)
E 38
E 31
		     return (1);
I 31
		/*
		 * Check for old-style (host 0) broadcast.
		 */
		if ((t = ntohl(in.s_addr)) == ia->ia_subnet || t == ia->ia_net)
		    return (1);
	}
	if (in.s_addr == INADDR_BROADCAST || in.s_addr == INADDR_ANY)
		return (1);
E 31
	return (0);
E 60
I 60
#define ia ((struct in_ifaddr *)ifa)
	for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
		if (ifa->ifa_addr->sa_family == AF_INET &&
		    (in.s_addr == ia->ia_broadaddr.sin_addr.s_addr ||
		     in.s_addr == ia->ia_netbroadcast.s_addr ||
		     /*
		      * Check for old-style (host 0) broadcast.
		      */
		     t == ia->ia_subnet || t == ia->ia_net))
			    return 1;
D 62
	return 0;
E 62
I 62
	return (0);
E 62
#undef ia
E 60
E 18
E 6
}
I 54
D 60

E 60
D 56
#ifdef MULTICAST
E 56
/*
 * Add an address to the list of IP multicast addresses for a given interface.
 */
struct in_multi *
in_addmulti(ap, ifp)
	register struct in_addr *ap;
	register struct ifnet *ifp;
{
	register struct in_multi *inm;
	struct ifreq ifr;
	struct in_ifaddr *ia;
	int s = splnet();
D 57
int error;
E 57
I 57
D 59
	int error;
E 59
E 57

	/*
	 * See if address already in list.
	 */
	IN_LOOKUP_MULTI(*ap, ifp, inm);
	if (inm != NULL) {
		/*
		 * Found it; just increment the reference count.
		 */
		++inm->inm_refcount;
	}
	else {
		/*
		 * New address; allocate a new multicast record
		 * and link it into the interface's multicast list.
		 */
		inm = (struct in_multi *)malloc(sizeof(*inm),
		    M_IPMADDR, M_NOWAIT);
		if (inm == NULL) {
			splx(s);
			return (NULL);
		}
		inm->inm_addr = *ap;
		inm->inm_ifp = ifp;
		inm->inm_refcount = 1;
		IFP_TO_IA(ifp, ia);
		if (ia == NULL) {
			free(inm, M_IPMADDR);
			splx(s);
			return (NULL);
		}
		inm->inm_ia = ia;
I 59
		inm->inm_next = ia->ia_multiaddrs;
		ia->ia_multiaddrs = inm;
E 59
D 57
		inm->inm_next = ia->ia_multiaddrs;
		ia->ia_multiaddrs = inm;
E 57
		/*
		 * Ask the network driver to update its multicast reception
		 * filter appropriately for the new address.
		 */
		((struct sockaddr_in *)&ifr.ifr_addr)->sin_family = AF_INET;
		((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr = *ap;
D 59
		if (ifp->if_ioctl == NULL) {
E 59
I 59
		if ((ifp->if_ioctl == NULL) ||
		    (*ifp->if_ioctl)(ifp, SIOCADDMULTI,(caddr_t)&ifr) != 0) {
			ia->ia_multiaddrs = inm->inm_next;
E 59
			free(inm, M_IPMADDR);
			splx(s);
			return (NULL);
		}
D 59
		error = (*ifp->if_ioctl)(ifp, SIOCADDMULTI,(caddr_t)&ifr);
		if (error != 0) {
			free(inm, M_IPMADDR);
			splx(s);
			return (NULL);
		}
I 57
		inm->inm_next = ia->ia_multiaddrs;
		ia->ia_multiaddrs = inm;
E 59
E 57
		/*
		 * Let IGMP know that we have joined a new IP multicast group.
		 */
		igmp_joingroup(inm);
	}
	splx(s);
	return (inm);
}

/*
 * Delete a multicast address record.
 */
int
in_delmulti(inm)
	register struct in_multi *inm;
{
	register struct in_multi **p;
	struct ifreq ifr;
	int s = splnet();

	if (--inm->inm_refcount == 0) {
		/*
		 * No remaining claims to this record; let IGMP know that
		 * we are leaving the multicast group.
		 */
		igmp_leavegroup(inm);
		/*
		 * Unlink from list.
		 */
		for (p = &inm->inm_ia->ia_multiaddrs;
		     *p != inm;
		     p = &(*p)->inm_next)
			 continue;
		*p = (*p)->inm_next;
		/*
		 * Notify the network driver to update its multicast reception
		 * filter.
		 */
		((struct sockaddr_in *)&(ifr.ifr_addr))->sin_family = AF_INET;
		((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr =
								inm->inm_addr;
		(*inm->inm_ifp->if_ioctl)(inm->inm_ifp, SIOCDELMULTI,
							     (caddr_t)&ifr);
		free(inm, M_IPMADDR);
	}
	splx(s);
}
D 56
#endif
E 56
E 54
#endif
E 1
