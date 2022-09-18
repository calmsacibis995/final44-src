h56444
s 00001/00001/00145
d D 8.2 95/04/28 11:17:21 bostic 22 21
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00144
d D 8.1 93/06/05 11:14:05 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00145
d D 5.15 91/02/28 18:08:02 bostic 20 19
c ANSI
e
s 00001/00011/00145
d D 5.14 90/06/01 16:29:35 bostic 19 18
c new copyright notice
e
s 00003/00000/00153
d D 5.13 89/08/21 12:34:08 sklower 18 17
c provision bandaids for new sockaddrs
e
s 00022/00009/00131
d D 5.12 89/02/18 11:28:34 karels 17 16
c working with dynamic updates, auto-loading timer; tracing additions and fixes
e
s 00010/00005/00130
d D 5.11 88/06/18 13:56:35 bostic 16 15
c install approved copyright notice
e
s 00009/00002/00126
d D 5.10 88/05/31 12:02:35 karels 15 14
c send only one packet to self; finish perspective change
e
s 00009/00003/00119
d D 5.9 88/02/16 18:50:55 bostic 14 13
c add Berkeley specific headers
e
s 00001/00000/00121
d D 5.8 87/12/12 17:55:57 karels 13 12
c clear must-be-zero field
e
s 00008/00010/00113
d D 5.7 87/05/28 11:26:10 karels 12 11
c rework interface metrics to invert perspective; other misc. fixes
e
s 00002/00001/00121
d D 5.6 87/04/28 18:26:58 karels 11 10
c send interface routes out on the "same" interface,
c mostly for pt-pt's
e
s 00002/00001/00120
d D 5.5 87/04/02 13:06:28 karels 10 9
c finish up interface metric code: store metric from our perspective,
c plus increment for those we send to; delete route from kernel when unreachable,
c but keep in tables to advertise deletion
e
s 00003/00001/00118
d D 5.4 86/10/30 20:37:41 karels 9 8
c send at least one packet even if nothing to say
e
s 00001/00001/00118
d D 5.3 86/05/30 13:56:22 karels 8 7
c don't send net route to subnet gw's unless on subnet 0;
c a few checks for imposters; bug fix in "external" route configuration;
c rm loopback net defn.
e
s 00021/00000/00098
d D 5.2 86/04/20 23:34:21 karels 7 6
c changes to allow subnets to remain local, propogate net route
c where subnets don't go, and allow external routes from /etc/gateways
c to block routed from installing routes from elsewhere
e
s 00007/00001/00091
d D 5.1 85/06/04 16:36:36 dist 6 5
c Add copyright
e
s 00000/00000/00092
d D 4.5 84/04/09 15:05:27 karels 5 4
c many cleanups; avoid interface timing out; put it back asap
e
s 00001/00004/00091
d D 4.4 83/06/01 16:26:53 sam 4 3
c notyet has come
e
s 00007/00002/00088
d D 4.3 83/05/25 17:50:55 sam 3 2
c protocol change; byte swap those fields which need it;  also add 
c a version stamp to allow future changes
e
s 00011/00009/00079
d D 4.2 83/01/11 14:38:24 sam 2 1
c 4.1c conversion contortions
e
s 00088/00000/00000
d D 4.1 82/11/02 22:28:06 sam 1 0
c date and time created 82/11/02 22:28:06 by sam
e
u
U
t
T
I 6
/*
D 15
 * Copyright (c) 1983 Regents of the University of California.
E 15
I 15
D 21
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 15
D 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 19
 * Redistribution and use in source and binary forms are permitted
D 16
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 16
I 16
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 16
E 14
 */

E 6
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% %G%";
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
D 6
#endif
E 6
I 6
D 14
#endif not lint
E 14
I 14
#endif /* not lint */
E 14
E 6

/*
 * Routing Table Management Daemon
 */
D 2
#include "router.h"
E 2
I 2
#include "defs.h"
E 2

/*
 * Apply the function "f" to all non-passive
 * interfaces.  If the interface supports the
 * use of broadcasting use it, otherwise address
 * the output to the known router.
 */
D 17
toall(f)
E 17
I 17
toall(f, rtstate, skipif)
E 17
	int (*f)();
I 17
	int rtstate;
	struct interface *skipif;
E 17
{
	register struct interface *ifp;
	register struct sockaddr *dst;
I 2
	register int flags;
E 2
	extern struct interface *ifnet;

	for (ifp = ifnet; ifp; ifp = ifp->int_next) {
D 17
		if (ifp->int_flags & IFF_PASSIVE)
E 17
I 17
		if (ifp->int_flags & IFF_PASSIVE || ifp == skipif)
E 17
			continue;
		dst = ifp->int_flags & IFF_BROADCAST ? &ifp->int_broadaddr :
		      ifp->int_flags & IFF_POINTOPOINT ? &ifp->int_dstaddr :
		      &ifp->int_addr;
D 2
		(*f)(dst, ifp->int_flags & IFF_INTERFACE, ifp);
E 2
I 2
D 3
		flags = ifp->int_flags & IFF_INTERFACE ? SOF_DONTROUTE : 0;
E 3
I 3
		flags = ifp->int_flags & IFF_INTERFACE ? MSG_DONTROUTE : 0;
E 3
D 17
		(*f)(dst, flags, ifp);
E 17
I 17
		(*f)(dst, flags, ifp, rtstate);
E 17
E 2
	}
}

/*
 * Output a preformed packet.
 */
/*ARGSUSED*/
D 2
sendmsg(dst, dontroute, ifp)
E 2
I 2
D 17
sendmsg(dst, flags, ifp)
E 17
I 17
D 20
sendmsg(dst, flags, ifp, rtstate)
E 20
I 20
sndmsg(dst, flags, ifp, rtstate)
E 20
E 17
E 2
	struct sockaddr *dst;
D 2
	int dontroute;
E 2
I 2
	int flags;
E 2
	struct interface *ifp;
I 17
	int rtstate;
E 17
{

D 2
	(*afswitch[dst->sa_family].af_output)(dontroute ? snoroute : s,
E 2
I 2
	(*afswitch[dst->sa_family].af_output)(s, flags,
E 2
		dst, sizeof (struct rip));
	TRACE_OUTPUT(ifp, dst, sizeof (struct rip));
}

/*
 * Supply dst with the contents of the routing tables.
 * If this won't fit in one packet, chop it up into several.
 */
D 2
supply(dst, dontroute, ifp)
E 2
I 2
D 17
supply(dst, flags, ifp)
E 17
I 17
supply(dst, flags, ifp, rtstate)
E 17
E 2
	struct sockaddr *dst;
I 2
	int flags;
E 2
D 12
	struct interface *ifp;
E 12
I 12
	register struct interface *ifp;
I 17
	int rtstate;
E 17
E 12
{
	register struct rt_entry *rt;
D 12
	struct netinfo *n = msg->rip_nets;
E 12
I 12
	register struct netinfo *n = msg->rip_nets;
E 12
	register struct rthash *rh;
	struct rthash *base = hosthash;
	int doinghost = 1, size;
	int (*output)() = afswitch[dst->sa_family].af_output;
I 7
D 12
	int (*sendsubnet)() = afswitch[dst->sa_family].af_sendsubnet;
E 12
I 12
	int (*sendroute)() = afswitch[dst->sa_family].af_sendroute;
E 12
I 9
	int npackets = 0;
E 9
E 7
D 2
	int sto = dontroute ? snoroute : s;
E 2

	msg->rip_cmd = RIPCMD_RESPONSE;
I 3
	msg->rip_vers = RIPVERSION;
I 13
D 22
	bzero(msg->rip_res1, sizeof(msg->rip_res1));
E 22
I 22
	memset(msg->rip_res1, 0, sizeof(msg->rip_res1));
E 22
E 13
E 3
again:
	for (rh = base; rh < &base[ROUTEHASHSIZ]; rh++)
	for (rt = rh->rt_forw; rt != (struct rt_entry *)rh; rt = rt->rt_forw) {
I 7
		/*
D 12
		 * Don't resend the information
		 * on the network from which it was received.
E 12
I 12
		 * Don't resend the information on the network
		 * from which it was received (unless sending
		 * in response to a query).
E 12
		 */
D 11
		if (ifp && rt->rt_ifp == ifp)
E 11
I 11
		if (ifp && rt->rt_ifp == ifp &&
		    (rt->rt_state & RTS_INTERFACE) == 0)
E 11
			continue;
		if (rt->rt_state & RTS_EXTERNAL)
			continue;
		/*
I 17
		 * For dynamic updates, limit update to routes
		 * with the specified state.
		 */
		if (rtstate && (rt->rt_state & rtstate) == 0)
			continue;
		/*
E 17
		 * Limit the spread of subnet information
		 * to those who are interested.
		 */
		if (doinghost == 0 && rt->rt_state & RTS_SUBNET) {
D 12
			if (ifp && (ifp->int_flags & IFF_SUBNET) == 0)
				continue;
E 12
			if (rt->rt_dst.sa_family != dst->sa_family)
				continue;
D 8
			if ((*sendsubnet)(&rt->rt_dst, dst) == 0)
E 8
I 8
D 12
			if ((*sendsubnet)(rt, dst) == 0)
E 12
I 12
			if ((*sendroute)(rt, dst) == 0)
E 12
E 8
				continue;
		}
E 7
		size = (char *)n - packet;
		if (size > MAXPACKETSIZE - sizeof (struct netinfo)) {
D 2
			(*output)(sto, dst, size);
E 2
I 2
D 17
			(*output)(s, flags, dst, size);
E 17
E 2
			TRACE_OUTPUT(ifp, dst, size);
I 17
			(*output)(s, flags, dst, size);
E 17
I 15
			/*
			 * If only sending to ourselves,
			 * one packet is enough to monitor interface.
			 */
D 17
			if ((ifp->int_flags &
E 17
I 17
			if (ifp && (ifp->int_flags &
E 17
			   (IFF_BROADCAST | IFF_POINTOPOINT | IFF_REMOTE)) == 0)
				return;
E 15
			n = msg->rip_nets;
I 9
			npackets++;
E 9
		}
		n->rip_dst = rt->rt_dst;
I 17
#if BSD < 198810
		if (sizeof(n->rip_dst.sa_family) > 1)	/* XXX */
E 17
D 4
		n->rip_metric = min(rt->rt_metric + 1, HOPCNT_INFINITY);
I 3
#ifdef notyet
E 4
		n->rip_dst.sa_family = htons(n->rip_dst.sa_family);
I 18
#else
#define osa(x) ((struct osockaddr *)(&(x)))
		osa(n->rip_dst)->sa_family = htons(n->rip_dst.sa_family);
E 18
I 17
#endif
E 17
D 4
		n->rip_metric = htonl(n->rip_metric);
#endif
E 4
I 4
D 10
		n->rip_metric = htonl(min(rt->rt_metric + 1, HOPCNT_INFINITY));
E 10
I 10
D 12
		n->rip_metric = htonl(min(rt->rt_metric + rt->rt_ifmetric,
		    HOPCNT_INFINITY));
E 12
I 12
D 15
		n->rip_metric = htonl(min(rt->rt_metric + 1, HOPCNT_INFINITY));
E 15
I 15
		n->rip_metric = htonl(rt->rt_metric);
E 15
E 12
E 10
E 4
E 3
		n++;
	}
	if (doinghost) {
		doinghost = 0;
		base = nethash;
		goto again;
	}
D 9
	if (n != msg->rip_nets) {
E 9
I 9
D 17
	if (n != msg->rip_nets || npackets == 0) {
E 17
I 17
	if (n != msg->rip_nets || (npackets == 0 && rtstate == 0)) {
E 17
E 9
		size = (char *)n - packet;
D 2
		(*output)(sto, dst, size);
E 2
I 2
D 17
		(*output)(s, flags, dst, size);
E 17
E 2
		TRACE_OUTPUT(ifp, dst, size);
I 17
		(*output)(s, flags, dst, size);
E 17
	}
}
E 1
