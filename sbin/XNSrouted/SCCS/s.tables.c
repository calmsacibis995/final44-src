h53141
s 00002/00002/00291
d D 8.1 93/06/05 10:48:03 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00065/00011/00228
d D 5.10 92/02/20 11:59:53 sklower 10 9
c use new kerninfo instead of SIOCGCONF, routing socket instead of
c SIOC{ADD,DEL}RT; edit only, can't test for a while.
e
s 00001/00011/00238
d D 5.9 90/06/01 16:15:14 bostic 9 8
c new copyright notice
e
s 00018/00000/00231
d D 5.8 89/08/21 14:08:09 karels 8 7
c check for alpha release by sklower
e
s 00014/00005/00217
d D 5.7 88/09/20 11:32:25 bostic 7 6
c add Berkeley specific copyright notice
e
s 00009/00005/00213
d D 5.6 86/12/30 14:36:37 karels 6 5
c don't print useless messages
e
s 00015/00004/00203
d D 5.5 86/02/14 18:28:32 sklower 5 4
c 1.) Fixes from Nesheim viz pt to pt timeouts;
c 2.) Getting rid of ns_netof, to make common for Gould, CCI
e
s 00004/00004/00203
d D 5.4 85/09/17 21:42:13 sklower 4 3
c latest changes from nesheim@cornell:
c use syslog instead of perror, ignore remote requests unless specifically asked,
c handle requests from net 0.
e
s 00014/00005/00193
d D 5.3 85/08/16 21:49:22 sklower 3 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00006/00011/00192
d D 5.2 85/08/16 20:44:10 sklower 2 1
c status as of 4.3 alpha tape
e
s 00203/00000/00000
d D 5.1 85/08/16 20:22:53 sklower 1 0
c date and time created 85/08/16 20:22:53 by sklower
e
u
U
t
T
I 3
/*
D 7
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
D 11
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
E 7
 *
I 7
D 9
 * Redistribution and use in source and binary forms are permitted
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 7
 */

D 7

E 7
E 3
I 1
#ifndef lint
D 3
static char rcsid[] = "$Header$";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 3

/*
 * Routing Table Management Daemon
 */
#include "defs.h"
#include <sys/ioctl.h>
#include <errno.h>

#ifndef DEBUG
#define	DEBUG	0
#endif

I 6
extern	char *xns_ntoa();
I 8
#define FIXLEN(s) { if ((s)->sa_len == 0) (s)->sa_len = sizeof (*(s));}
E 8

E 6
int	install = !DEBUG;		/* if 1 call kernel */
D 2
static  int	s;			/* for routing table ioctl's */
E 2
I 2
int	delete = 1;
E 2
/*
 * Lookup dst in the tables for an exact match.
 */
struct rt_entry *
rtlookup(dst)
	struct sockaddr *dst;
{
	register struct rt_entry *rt;
	register struct rthash *rh;
	register u_int hash;
	struct afhash h;
	int doinghost = 1;

	if (dst->sa_family >= AF_MAX)
		return (0);
	(*afswitch[dst->sa_family].af_hash)(dst, &h);
	hash = h.afh_hosthash;
	rh = &hosthash[hash & ROUTEHASHMASK];
again:
	for (rt = rh->rt_forw; rt != (struct rt_entry *)rh; rt = rt->rt_forw) {
		if (rt->rt_hash != hash)
			continue;
		if (equal(&rt->rt_dst, dst))
			return (rt);
	}
	if (doinghost) {
		doinghost = 0;
		hash = h.afh_nethash;
		rh = &nethash[hash & ROUTEHASHMASK];
		goto again;
	}
	return (0);
}

/*
 * Find a route to dst as the kernel would.
 */
struct rt_entry *
rtfind(dst)
	struct sockaddr *dst;
{
	register struct rt_entry *rt;
	register struct rthash *rh;
	register u_int hash;
	struct afhash h;
	int af = dst->sa_family;
	int doinghost = 1, (*match)();

	if (af >= AF_MAX)
		return (0);
	(*afswitch[af].af_hash)(dst, &h);
	hash = h.afh_hosthash;
	rh = &hosthash[hash & ROUTEHASHMASK];

again:
	for (rt = rh->rt_forw; rt != (struct rt_entry *)rh; rt = rt->rt_forw) {
		if (rt->rt_hash != hash)
			continue;
		if (doinghost) {
			if (equal(&rt->rt_dst, dst))
				return (rt);
I 3
		} else {
			if (rt->rt_dst.sa_family == af &&
			    (*match)(&rt->rt_dst, dst))
				return (rt);
E 3
D 2
		} else {
			if (rt->rt_dst.sa_family == af &&
			    (*match)(&rt->rt_dst, dst))
				return (rt);
E 2
		}
I 2
D 3
		if (rt->rt_dst.sa_family == af &&
		    (*match)(&rt->rt_dst, dst))
			return (rt);
E 3
E 2
	}
	if (doinghost) {
		doinghost = 0;
		hash = h.afh_nethash;
		rh = &nethash[hash & ROUTEHASHMASK];
		match = afswitch[af].af_netmatch;
		goto again;
	}
	return (0);
}

rtadd(dst, gate, metric, state)
	struct sockaddr *dst, *gate;
	int metric, state;
{
	struct afhash h;
	register struct rt_entry *rt;
	struct rthash *rh;
	int af = dst->sa_family, flags;
	u_int hash;

I 8
	FIXLEN(dst);
	FIXLEN(gate);
E 8
	if (af >= AF_MAX)
		return;
	(*afswitch[af].af_hash)(dst, &h);
	flags = (*afswitch[af].af_ishost)(dst) ? RTF_HOST : 0;
	if (flags & RTF_HOST) {
		hash = h.afh_hosthash;
		rh = &hosthash[hash & ROUTEHASHMASK];
	} else {
		hash = h.afh_nethash;
		rh = &nethash[hash & ROUTEHASHMASK];
	}
	rt = (struct rt_entry *)malloc(sizeof (*rt));
	if (rt == 0)
		return;
	rt->rt_hash = hash;
	rt->rt_dst = *dst;
	rt->rt_router = *gate;
	rt->rt_metric = metric;
	rt->rt_timer = 0;
	rt->rt_flags = RTF_UP | flags;
	rt->rt_state = state | RTS_CHANGED;
	rt->rt_ifp = if_ifwithnet(&rt->rt_router);
	if (metric)
		rt->rt_flags |= RTF_GATEWAY;
	insque(rt, rh);
	TRACE_ACTION(ADD, rt);
	/*
	 * If the ioctl fails because the gateway is unreachable
	 * from this host, discard the entry.  This should only
	 * occur because of an incorrect entry in /etc/gateways.
	 */
D 10
	if (install && ioctl(s, SIOCADDRT, (char *)&rt->rt_rt) < 0) {
E 10
I 10
	if (install && rtioctl(ADD, &rt->rt_rt) < 0) {
E 10
D 4
		perror("SIOCADDRT");
E 4
I 4
D 6
		syslog(LOG_ERR,"SIOCADDRT: %m");
E 6
I 6
		if (errno != EEXIST)
			perror("SIOCADDRT");
E 6
E 4
		if (errno == ENETUNREACH) {
			TRACE_ACTION(DELETE, rt);
			remque(rt);
			free((char *)rt);
		}
	}
}

rtchange(rt, gate, metric)
	struct rt_entry *rt;
	struct sockaddr *gate;
	short metric;
{
	int doioctl = 0, metricchanged = 0;
	struct rtentry oldroute;

I 8
	FIXLEN(gate);
E 8
	if (!equal(&rt->rt_router, gate))
		doioctl++;
	if (metric != rt->rt_metric)
		metricchanged++;
	if (doioctl || metricchanged) {
		TRACE_ACTION(CHANGE FROM, rt);
		if (doioctl) {
			oldroute = rt->rt_rt;
			rt->rt_router = *gate;
		}
		rt->rt_metric = metric;
D 5
		rt->rt_state &= ~RTS_INTERFACE;
E 5
I 5
		if ((rt->rt_state & RTS_INTERFACE) && metric) {
			rt->rt_state &= ~RTS_INTERFACE;
			syslog(LOG_ERR,
				"changing route from interface %s (timed out)",
				rt->rt_ifp->int_name);
		}
E 5
		if (metric)
D 5
			rt->rt_state |= RTF_GATEWAY;
E 5
I 5
			rt->rt_flags |= RTF_GATEWAY;
		else
			rt->rt_flags &= ~RTF_GATEWAY;
E 5
		rt->rt_state |= RTS_CHANGED;
		TRACE_ACTION(CHANGE TO, rt);
	}
	if (doioctl && install) {
I 8
#ifndef RTM_ADD
E 8
D 10
		if (ioctl(s, SIOCADDRT, (char *)&rt->rt_rt) < 0)
D 4
			perror("SIOCADDRT");
E 4
I 4
D 6
			syslog(LOG_ERR,"SIOCADDRT %m");
E 4
I 2
		if (delete)
E 2
		if (ioctl(s, SIOCDELRT, (char *)&oldroute) < 0)
D 4
			perror("SIOCDELRT");
E 4
I 4
			syslog(LOG_ERR,"SIOCDELRT %m");
E 6
I 6
		  syslog(LOG_ERR, "SIOCADDRT dst %s, gw %s: %m",
E 10
I 10
		if (rtioctl(ADD, &rt->rt_rt) < 0)
		  syslog(LOG_ERR, "rtioctl ADD dst %s, gw %s: %m",
E 10
		   xns_ntoa(&((struct sockaddr_ns *)&rt->rt_dst)->sns_addr),
		   xns_ntoa(&((struct sockaddr_ns *)&rt->rt_router)->sns_addr));
D 10
		if (delete && ioctl(s, SIOCDELRT, (char *)&oldroute) < 0)
			perror("SIOCDELRT");
E 10
I 10
		if (delete && rtioctl(DELETE, &oldroute) < 0)
			perror("rtioctl DELETE");
E 10
I 8
#else
D 10
		if (delete && ioctl(s, SIOCDELRT, (char *)&oldroute) < 0)
			perror("SIOCDELRT");
		if (ioctl(s, SIOCADDRT, (char *)&rt->rt_rt) < 0)
		  syslog(LOG_ERR, "SIOCADDRT dst %s, gw %s: %m",
E 10
I 10
		if (delete == 0) {
			if (rtioctl(ADD, &rt->rt_rt) >= 0)
				return;
		} else {
			if (rtioctl(CHANGE, &rt->rt_rt) >= 0)
				return;
		}
	        syslog(LOG_ERR, "rtioctl ADD dst %s, gw %s: %m",
E 10
		   xns_ntoa(&((struct sockaddr_ns *)&rt->rt_dst)->sns_addr),
		   xns_ntoa(&((struct sockaddr_ns *)&rt->rt_router)->sns_addr));
#endif
E 8
E 6
E 4
	}
}

rtdelete(rt)
	struct rt_entry *rt;
{

I 8
	struct sockaddr *sa = &(rt->rt_rt.rt_gateway);
	FIXLEN(sa);
#undef rt_dst
	sa = &(rt->rt_rt.rt_dst);
	FIXLEN(sa);
E 8
I 5
	if (rt->rt_state & RTS_INTERFACE) {
		syslog(LOG_ERR, "deleting route to interface %s (timed out)",
			rt->rt_ifp->int_name);
	}
E 5
	TRACE_ACTION(DELETE, rt);
D 2
	if (install && ioctl(s, SIOCDELRT, (char *)&rt->rt_rt))
E 2
I 2
D 5
	if (install && delete && ioctl(s, SIOCDELRT, (char *)&rt->rt_rt))
E 2
D 4
		perror("SIOCDELRT");
E 4
I 4
		syslog(LOG_ERR,"SIOCDELR %m");
E 5
I 5
D 10
	if (install && ioctl(s, SIOCDELRT, (char *)&rt->rt_rt))
		perror("SIOCDELRT");
E 10
I 10
	if (install && rtioctl(DELETE, &rt->rt_rt) < 0)
		perror("rtioctl DELETE");
E 10
E 5
E 4
	remque(rt);
	free((char *)rt);
}

rtinit()
{
	register struct rthash *rh;

	for (rh = nethash; rh < &nethash[ROUTEHASHSIZ]; rh++)
		rh->rt_forw = rh->rt_back = (struct rt_entry *)rh;
	for (rh = hosthash; rh < &hosthash[ROUTEHASHSIZ]; rh++)
		rh->rt_forw = rh->rt_back = (struct rt_entry *)rh;
I 10
}
int seqno;

rtioctl(action, ort)
	int action;
	struct ortentry *ort;
{
#ifndef RTM_ADD
	switch (action) {

	case ADD:
		return (ioctl(s, SIOCADDRT, (char *)ort));

	case DELETE:
		return (ioctl(s, SIOCDELRT, (char *)ort));

	default:
		return (-1);
	}
#else /* RTM_ADD */
	struct {
		struct rt_msghdr w_rtm;
		struct sockaddr w_dst;
		struct sockaddr w_gate;
		struct sockaddr_ns w_netmask;
	} w;
#define rtm w.w_rtm

	bzero((char *)&w, sizeof(w));
	rtm.rtm_msglen = sizeof(w);
	rtm.rtm_version = RTM_VERSION;
	rtm.rtm_type = (action == ADD ? RTM_ADD :
				(action == DELETE ? RTM_DELETE : RTM_CHANGE));
#undef rt_flags
	rtm.rtm_flags = ort->rt_flags;
	rtm.rtm_seq = ++seqno;
	rtm.rtm_addrs = RTA_DST|RTA_GATEWAY;
	bcopy((char *)&ort->rt_dst, (char *)&w.w_dst, sizeof(w.w_dst));
	bcopy((char *)&ort->rt_gateway, (char *)&w.w_gate, sizeof(w.w_gate));
	w.w_gate.sa_family = w.w_dst.sa_family = AF_NS;
	w.w_gate.sa_len = w.w_dst.sa_len = sizeof(w.w_dst);
	if (rtm.rtm_flags & RTF_HOST) {
		rtm.rtm_msglen -= sizeof(w.w_netmask);
	} else {
		w.w_netmask = ns_netmask;
		rtm.rtm_msglen -= 8;
	}
	errno = 0;
	return write(r, (char *)&w, rtm.rtm_msglen);
#endif  /* RTM_ADD */
E 10
D 2
		
	if ((s = socket(AF_XNS, SOCK_RAW, IDPPROTO_RAW)) < 0) {
		perror("socket");
		exit(1);
	}
E 2
}
E 1
