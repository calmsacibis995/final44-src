h20702
s 00001/00001/00220
d D 8.2 95/01/09 17:54:27 cgd 54 53
c 64-bit changes: casts, and ioctl cmds are u_longs
e
s 00002/00002/00219
d D 8.1 93/06/10 22:44:48 bostic 53 52
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00219
d D 7.22 93/06/04 17:31:41 bostic 52 51
c prototype everything
e
s 00007/00001/00213
d D 7.21 93/04/17 18:56:10 torek 51 50
c loattach => loopattach, for generic pseudo-device attachment
e
s 00003/00002/00211
d D 7.20 93/04/08 17:14:11 sklower 50 49
c changes proposed by jch
e
s 00000/00008/00213
d D 7.19 93/02/25 16:45:13 sklower 49 48
c MULTICAST is now standard
e
s 00022/00022/00199
d D 7.18 92/10/11 11:49:00 bostic 48 47
c make kernel includes standard
e
s 00059/00001/00162
d D 7.17 92/07/06 15:28:47 sklower 47 46
c multicast changes from lbl
e
s 00004/00002/00159
d D 7.16 92/03/15 00:22:53 torek 46 45
c gcc lint
e
s 00008/00008/00153
d D 7.15 92/01/30 12:02:20 sklower 45 44
c header include uniformity
e
s 00005/00006/00156
d D 7.14 92/01/30 11:43:28 torek 44 43
c checked in for torek by sklower; Mike agrees to all these changes
e
s 00014/00017/00148
d D 7.13 91/04/26 14:40:27 sklower 43 42
c give loopback iso routes default mtu in rtentry;
c remove AF_CCITT stuff for now.
e
s 00028/00026/00137
d D 7.12 90/11/06 16:48:38 sklower 42 41
c add AF_CCITT for testing, make common the IF_ENQUEUE's
e
s 00006/00014/00157
d D 7.11 90/09/04 10:41:43 sklower 41 40
c check for ``REJECT'' routes
e
s 00001/00011/00170
d D 7.10 90/06/28 21:30:49 bostic 40 39
c new copyright notice
e
s 00002/00000/00179
d D 7.9 89/09/20 17:35:26 sklower 39 38
c put in SNMP counters
e
s 00001/00001/00178
d D 7.8 89/09/04 19:19:28 karels 38 37
c rename if_types.h
e
s 00001/00001/00178
d D 7.7 89/04/25 11:06:24 mckusick 37 36
c ../machine => machine
e
s 00024/00002/00155
d D 7.6 89/04/22 12:11:06 sklower 36 35
c checkpoint at first working tp4 connection; before gnodes
e
s 00024/00026/00133
d D 7.5 88/10/12 14:41:13 karels 35 34
c mark state of working kernel before var. length sockaddrs
e
s 00010/00005/00149
d D 7.4 88/06/27 18:59:33 bostic 34 33
c install approved copyright notice
e
s 00008/00002/00146
d D 7.3 87/12/30 11:57:29 bostic 33 32
c add Berkeley header
e
s 00002/00004/00146
d D 7.2 86/10/28 22:31:18 karels 32 31
c merge in tahoe
e
s 00000/00000/00150
d D 7.1 86/06/04 23:53:04 mckusick 31 30
c 4.3BSD release version
e
s 00002/00002/00148
d D 6.10 86/06/04 23:48:45 karels 30 29
c use the right include
e
s 00001/00000/00149
d D 6.9 86/02/06 14:18:03 karels 29 28
c add LOOPBACK flag, interface metric
e
s 00000/00003/00149
d D 6.8 85/12/19 16:12:54 karels 28 27
c rm bbnnet; rm PUP
e
s 00031/00007/00121
d D 6.7 85/09/16 21:07:12 karels 27 26
c move to net directory; prepend ifp to packet for protocols;
c INET || BBNNET
e
s 00007/00001/00121
d D 6.6 85/06/08 12:37:07 mckusick 26 25
c Add copyright
e
s 00000/00002/00122
d D 6.5 85/05/30 09:02:32 karels 25 24
c delete extraneous definitions
e
s 00018/00000/00106
d D 6.4 85/04/27 11:55:12 sklower 24 23
c add NS protocol stuff
e
s 00006/00018/00100
d D 6.3 85/03/18 15:27:45 karels 23 22
c move protocol addresses and address initialization to protocol layer
e
s 00010/00010/00108
d D 6.2 84/08/29 15:35:47 bloom 22 21
c Include file changes.  No more ../h
e
s 00000/00000/00118
d D 6.1 83/07/29 07:11:05 sam 21 20
c 4.2 distribution
e
s 00036/00003/00082
d D 4.19 83/06/13 00:27:15 sam 20 19
c ioctls
e
s 00003/00001/00082
d D 4.18 83/05/27 13:45:04 sam 19 18
c local host can't be zero, that's a broadcast
e
s 00003/00001/00080
d D 4.17 83/05/15 17:20:24 sam 18 17
c one more time, this time mtpr.h is vax specific
e
s 00008/00005/00073
d D 4.16 83/02/11 08:09:59 sam 17 15
c remove /usr/include dependencies
e
s 00008/00005/00073
d R 4.16 83/02/10 22:10:55 sam 16 15
c remove /usr/include dependencies
e
s 00001/00001/00077
d D 4.15 82/10/13 22:43:59 root 15 14
c move mtpr.h to vax directory
e
s 00005/00004/00073
d D 4.14 82/10/09 05:44:39 wnj 14 13
c localize header files
e
s 00000/00002/00077
d D 4.13 82/06/20 00:53:11 sam 13 12
c purge COUNT stuff now that we can use gprof
e
s 00001/00001/00078
d D 4.12 82/06/12 23:18:54 wnj 12 11
c now the routing code might wokr
e
s 00001/00000/00078
d D 4.11 82/04/16 14:49:45 sam 11 10
c missing include
e
s 00003/00003/00075
d D 4.10 82/04/13 20:41:06 feldman 10 9
c fixed error returns
e
s 00004/00000/00074
d D 4.9 82/03/30 11:32:00 sam 9 8
c with routing, but not forwarding
e
s 00013/00009/00061
d D 4.8 82/03/28 14:21:59 sam 8 7
c convert interfaces to sockaddr's and add hooks for routing
e
s 00001/00001/00069
d D 4.7 82/03/19 01:48:57 wnj 7 6
c fix to use only one soft intr for net thereby fixing bug in raw sockets
e
s 00010/00002/00060
d D 4.6 82/03/15 04:43:49 wnj 6 5
c interfac queueing, restrictions on packets, tcp keep alives done 
c properly, bug fix to raw
e
s 00001/00001/00061
d D 4.5 81/12/22 23:11:26 root 5 4
c LONET->127
e
s 00001/00001/00061
d D 4.4 81/12/07 22:02:03 wnj 4 3
c MTU allow for headers
e
s 00004/00001/00058
d D 4.3 81/12/03 17:29:18 wnj 3 2
c cleanup
e
s 00001/00001/00058
d D 4.2 81/12/02 16:58:23 wnj 2 1
c yet more lint
e
s 00059/00000/00000
d D 4.1 81/11/29 22:18:03 wnj 1 0
c date and time created 81/11/29 22:18:03 by wnj
e
u
U
t
T
I 1
D 26
/*	%M%	%I%	%E%	*/
E 26
I 26
/*
D 30
 * Copyright (c) 1982 Regents of the University of California.
E 30
I 30
D 53
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 30
D 33
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 33
I 33
 * All rights reserved.
E 53
I 53
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 53
 *
D 40
 * Redistribution and use in source and binary forms are permitted
D 34
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 34
I 34
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
E 40
I 40
 * %sccs.include.redist.c%
E 40
E 34
E 33
 *
 *	%W% (Berkeley) %G%
 */
E 26

/*
 * Loopback interface driver for protocol testing and timing.
 */

D 22
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
D 14
#include "../net/in.h"
#include "../net/in_systm.h"
E 14
I 14
D 17
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
E 17
I 17
#include "../h/errno.h"
I 20
#include "../h/ioctl.h"
E 22
I 22
D 48
#include "param.h"
#include "systm.h"
I 47
#include "kernel.h"
E 47
#include "mbuf.h"
#include "socket.h"
#include "errno.h"
#include "ioctl.h"
I 44
#include "machine/cpu.h"
I 47
#include "time.h"
E 48
I 48
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <machine/cpu.h>
E 48
E 47
E 44
E 22
E 20

I 27
D 28
#ifdef	BBNNET
#define INET
#endif
E 28
E 27
E 17
E 14
D 44
#include "../net/if.h"
I 36
D 38
#include "../net/iftypes.h"
E 38
I 38
#include "../net/if_types.h"
E 38
E 36
D 14
#include "../net/ip.h"
#include "../net/ip_var.h"
E 14
I 14
#include "../net/netisr.h"
I 17
#include "../net/route.h"

I 32
D 37
#include "../machine/mtpr.h"
E 37
I 37
#include "machine/mtpr.h"
E 44
I 44
D 48
#include "if.h"
#include "if_types.h"
#include "netisr.h"
#include "route.h"
I 47
#include "bpf.h"
E 48
I 48
#include <net/if.h>
#include <net/if_types.h>
#include <net/netisr.h>
#include <net/route.h>
#include <net/bpf.h>
E 48
E 47
E 44
E 37

E 32
D 22
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
E 17
#include "../netinet/ip.h"
#include "../netinet/ip_var.h"
E 22
I 22
D 27
#include "in.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
E 27
I 27
#ifdef	INET
D 45
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
I 30
#include "../netinet/in_var.h"
E 30
#include "../netinet/ip.h"
E 45
I 45
D 48
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
E 48
I 48
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
E 48
E 45
D 30
#include "../netinet/ip_var.h"
E 30
D 32
#endif
E 27
E 22
E 14
D 15
#include "../h/mtpr.h"
E 15
I 15
D 17
#include "../vax/mtpr.h"
E 15
I 9
#include "../net/route.h"
I 11
#include <errno.h>
E 17
I 17

D 18
#include "../machine/mtpr.h"
E 18
I 18
#ifdef vax
#include "../vax/mtpr.h"
E 32
#endif
E 18
E 17
E 11
E 9

I 24
#ifdef NS
D 45
#include "../netns/ns.h"
#include "../netns/ns_if.h"
E 45
I 45
D 48
#include "netns/ns.h"
#include "netns/ns_if.h"
E 48
I 48
#include <netns/ns.h>
#include <netns/ns_if.h>
E 48
E 45
#endif

I 36
#ifdef ISO
D 45
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
E 45
I 45
D 48
#include "netiso/iso.h"
#include "netiso/iso_var.h"
E 48
I 48
#include <netiso/iso.h>
#include <netiso/iso_var.h>
E 48
E 45
#endif

I 47
#include "bpfilter.h"

E 47
I 42
D 43
#ifdef CCITT
#include "../netccitt/x25.h"
#include "../netccitt/hdlc.h"
#include "../netccitt/hd_var.h"
#endif

E 43
E 42
E 36
E 24
D 5
#define	LONET	254
E 5
I 5
D 25
#define	LONET	127
I 19
#define	LOHOST	1			/* can't be 0, that's broadcast */
E 25
E 19
E 5
D 4
#define	LOMTU	1024
E 4
I 4
#define	LOMTU	(1024+512)
E 4

struct	ifnet loif;
D 20
int	looutput();
E 20
I 20
D 52
int	looutput(), loioctl();
E 52
E 20

D 51
loattach()
E 51
I 51
/* ARGSUSED */
void
loopattach(n)
	int n;
E 51
{
	register struct ifnet *ifp = &loif;
I 8
D 27
	register struct sockaddr_in *sin;
E 27
E 8

I 51
#ifdef lint
	n = n;			/* Highlander: there can only be one... */
#endif
E 51
I 9
D 13
COUNT(LOATTACH);
E 13
E 9
I 3
	ifp->if_name = "lo";
E 3
	ifp->if_mtu = LOMTU;
I 47
D 49
#ifdef MULTICAST
E 49
	ifp->if_flags = IFF_LOOPBACK | IFF_MULTICAST;
D 49
#else
E 47
I 29
	ifp->if_flags = IFF_LOOPBACK;
I 47
#endif
E 49
E 47
E 29
D 23
	ifp->if_net = LONET;
I 19
	ifp->if_host[0] = LOHOST;
E 19
I 3
D 8
	ifp->if_addr = if_makeaddr(ifp->if_net, 0);
E 8
I 8
	sin = (struct sockaddr_in *)&ifp->if_addr;
	sin->sin_family = AF_INET;
D 19
	sin->sin_addr = if_makeaddr(ifp->if_net, 0);
E 19
I 19
D 20
	sin->sin_addr = if_makeaddr(ifp->if_net, LOHOST);
E 19
	ifp->if_flags = IFF_UP;
E 20
I 20
	sin->sin_addr = if_makeaddr(LONET, LOHOST);
	ifp->if_flags = IFF_UP | IFF_RUNNING;
E 23
	ifp->if_ioctl = loioctl;
E 20
E 8
E 3
	ifp->if_output = looutput;
I 36
	ifp->if_type = IFT_LOOP;
	ifp->if_hdrlen = 0;
	ifp->if_addrlen = 0;
E 36
D 3
	ifp->if_next = ifnet;
E 3
D 2
	ifnet = ifp;
E 2
I 2
	if_attach(ifp);
I 47
#if NBPFILTER > 0
	bpfattach(&ifp->if_bpf, ifp, DLT_NULL, sizeof(u_int));
#endif
E 47
I 9
D 12
	if_rtinit(ifp, RTF_DIRECT|RTF_UP);
E 12
I 12
D 23
	if_rtinit(ifp, RTF_UP);
E 23
E 12
E 9
E 2
}

I 52
int
E 52
D 8
looutput(ifp, m0, pf)
E 8
I 8
D 35
looutput(ifp, m0, dst)
E 35
I 35
D 41
struct mbuf *Loop_Sanity;

looutput(ifp, m, dst)
E 41
I 41
looutput(ifp, m, dst, rt)
E 41
E 35
E 8
	struct ifnet *ifp;
D 27
	struct mbuf *m0;
E 27
I 27
D 35
	register struct mbuf *m0;
E 35
I 35
	register struct mbuf *m;
E 35
E 27
D 8
	int pf;
E 8
I 8
	struct sockaddr *dst;
I 41
	register struct rtentry *rt;
E 41
E 8
{
D 27
	int s = splimp();
E 27
I 27
D 42
	int s;
E 27
I 6
	register struct ifqueue *ifq;
E 42
I 42
	int s, isr;
	register struct ifqueue *ifq = 0;
E 42
I 27
D 35
	struct mbuf *m;
E 35
E 27
E 6

I 27
D 35
	/*
	 * Place interface pointer before the data
	 * for the receiving protocol.
	 */
	if (m0->m_off <= MMAXOFF &&
	    m0->m_off >= MMINOFF + sizeof(struct ifnet *)) {
		m0->m_off -= sizeof(struct ifnet *);
		m0->m_len += sizeof(struct ifnet *);
	} else {
		MGET(m, M_DONTWAIT, MT_HEADER);
		if (m == (struct mbuf *)0)
			return (ENOBUFS);
		m->m_off = MMINOFF;
		m->m_len = sizeof(struct ifnet *);
		m->m_next = m0;
		m0 = m;
	}
	*(mtod(m0, struct ifnet **)) = ifp;
E 35
I 35
	if ((m->m_flags & M_PKTHDR) == 0)
		panic("looutput no HDR");
I 47
	ifp->if_lastchange = time;
#if NBPFILTER > 0
	if (loif.if_bpf) {
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
		
		bpf_mtap(loif.if_bpf, &m0);
	}
#endif
E 47
	m->m_pkthdr.rcvif = ifp;

D 41
{struct mbuf *mm; int mlen = 0;
D 36
for (mm = m; m; m = m->m_next) /* XXX debugging code -- sklwoer */
E 36
I 36
for (mm = m; m; m = m->m_next) /* XXX debugging code -- sklower */
E 36
    mlen += m->m_len;
m = mm;
if (mlen != m->m_pkthdr.len) {
	if (Loop_Sanity)
		m_freem(Loop_Sanity);
D 36
	Loop_Sanity = m_copy(m, 0, M_COPYALL);
E 36
I 36
	Loop_Sanity = m_copy(m, 0, (int)M_COPYALL);
E 36
}
}

E 41
I 41
D 50
	if (rt && rt->rt_flags & RTF_REJECT) {
E 50
I 50
	if (rt && rt->rt_flags & (RTF_REJECT|RTF_BLACKHOLE)) {
E 50
		m_freem(m);
D 50
		return (rt->rt_flags & RTF_HOST ? EHOSTUNREACH : ENETUNREACH);
E 50
I 50
		return (rt->rt_flags & RTF_BLACKHOLE ? 0 :
		        rt->rt_flags & RTF_HOST ? EHOSTUNREACH : ENETUNREACH);
E 50
	}
E 41
E 35
D 43
	s = splimp();
E 43
E 27
I 9
D 13
COUNT(LOOUTPUT);
E 13
E 9
I 3
	ifp->if_opackets++;
I 39
	ifp->if_obytes += m->m_pkthdr.len;
E 39
E 3
D 8
	switch (pf) {
E 8
I 8
	switch (dst->sa_family) {
E 8

#ifdef INET
D 8
	case PF_INET:
E 8
I 8
	case AF_INET:
E 8
D 6
		IF_ENQUEUE(&ipintrq, m0);
E 6
I 6
		ifq = &ipintrq;
D 42
		if (IF_QFULL(ifq)) {
			IF_DROP(ifq);
D 8
			(void) m_freem(m0);
E 8
I 8
D 35
			m_freem(m0);
E 35
I 35
			m_freem(m);
E 35
E 8
			splx(s);
D 10
			return (0);
E 10
I 10
			return (ENOBUFS);
E 10
		}
D 35
		IF_ENQUEUE(ifq, m0);
E 35
I 35
		IF_ENQUEUE(ifq, m);
E 35
E 6
D 7
		setipintr();
E 7
I 7
		schednetisr(NETISR_IP);
E 42
I 42
		isr = NETISR_IP;
E 42
I 24
		break;
#endif
#ifdef NS
	case AF_NS:
		ifq = &nsintrq;
D 42
		if (IF_QFULL(ifq)) {
			IF_DROP(ifq);
D 35
			m_freem(m0);
E 35
I 35
			m_freem(m);
E 35
			splx(s);
			return (ENOBUFS);
		}
D 35
		IF_ENQUEUE(ifq, m0);
E 35
I 35
		IF_ENQUEUE(ifq, m);
E 35
		schednetisr(NETISR_NS);
E 42
I 42
		isr = NETISR_NS;
E 42
I 36
		break;
#endif
#ifdef ISO
	case AF_ISO:
		ifq = &clnlintrq;
D 42
		if (IF_QFULL(ifq)) {
			IF_DROP(ifq);
			m_freem(m);
			splx(s);
			return (ENOBUFS);
		}
		IF_ENQUEUE(ifq, m);
		schednetisr(NETISR_ISO);
E 42
I 42
		isr = NETISR_ISO;
E 42
E 36
E 24
E 7
		break;
#endif
I 42
D 43
#ifdef CCITT
	case AF_CCITT:
		ifq = &hdintrq;
		isr = NETISR_CCITT;
		break;
#endif
E 43
E 42
D 8

E 8
	default:
D 43
		splx(s);
E 43
D 8
		printf("lo%d: can't encapsulate pf%d\n", ifp->if_unit, pf);
D 6
		m_freem(m0);
E 6
I 6
		(void) m_freem(m0);
E 8
I 8
		printf("lo%d: can't handle af%d\n", ifp->if_unit,
			dst->sa_family);
D 35
		m_freem(m0);
E 35
I 35
		m_freem(m);
E 35
E 8
E 6
D 10
		return (0);
E 10
I 10
		return (EAFNOSUPPORT);
E 10
	}
I 43
	s = splimp();
E 43
I 42
	if (IF_QFULL(ifq)) {
		IF_DROP(ifq);
		m_freem(m);
		splx(s);
		return (ENOBUFS);
	}
	IF_ENQUEUE(ifq, m);
	schednetisr(isr);
E 42
I 3
	ifp->if_ipackets++;
I 39
	ifp->if_ibytes += m->m_pkthdr.len;
E 39
E 3
	splx(s);
D 10
	return (1);
E 10
I 10
	return (0);
I 20
}

I 43
/* ARGSUSED */
I 47
void
E 47
lortrequest(cmd, rt, sa)
D 46
struct rtentry *rt;
struct sockaddr *sa;
E 46
I 46
	int cmd;
	struct rtentry *rt;
	struct sockaddr *sa;
E 46
{
I 46

E 46
	if (rt)
		rt->rt_rmx.rmx_mtu = LOMTU;
}

E 43
/*
 * Process an ioctl request.
 */
I 23
/* ARGSUSED */
I 52
int
E 52
E 23
loioctl(ifp, cmd, data)
	register struct ifnet *ifp;
D 54
	int cmd;
E 54
I 54
	u_long cmd;
E 54
	caddr_t data;
{
I 43
	register struct ifaddr *ifa;
E 43
D 23
	struct ifreq *ifr = (struct ifreq *)data;
	struct sockaddr_in *sin;
	int s = splimp(), error = 0;
E 23
I 23
D 47
	int error = 0;
E 47
I 47
D 49
#ifdef MULTICAST
E 49
	register struct ifreq *ifr;
D 49
#endif
E 49
	register int error = 0;
E 47
E 23

	switch (cmd) {

I 42
D 43
#ifdef CCITT
	case SIOCSIFCONF_X25:
#endif
E 43
E 42
	case SIOCSIFADDR:
D 23
		if (ifp->if_flags & IFF_RUNNING)
			if_rtinit(ifp, -1);	/* delete previous route */
		ifp->if_addr = ifr->ifr_addr;
		sin = (struct sockaddr_in *)&ifp->if_addr;
		ifp->if_net = in_netof(sin->sin_addr);
		ifp->if_host[0] = in_lnaof(sin->sin_addr);
		if_rtinit(ifp, RTF_UP);
E 23
I 23
		ifp->if_flags |= IFF_UP;
I 43
		ifa = (struct ifaddr *)data;
		if (ifa != 0 && ifa->ifa_addr->sa_family == AF_ISO)
			ifa->ifa_rtrequest = lortrequest;
E 43
		/*
		 * Everything else is done at a higher level.
		 */
E 23
		break;
I 47

D 49
#ifdef MULTICAST
E 49
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		ifr = (struct ifreq *)data;
		if (ifr == 0) {
			error = EAFNOSUPPORT;		/* XXX */
			break;
		}
		switch (ifr->ifr_addr.sa_family) {

#ifdef INET
		case AF_INET:
			break;
#endif

		default:
			error = EAFNOSUPPORT;
			break;
		}
		break;
D 49
#endif
E 49
E 47

	default:
		error = EINVAL;
	}
D 23
	splx(s);
E 23
	return (error);
E 20
E 10
}
E 1
