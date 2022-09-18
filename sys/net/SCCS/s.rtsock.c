h62532
s 00021/00023/00788
d D 8.6.1.1 95/02/23 22:29:50 sklower 51 50
c document slightly closer to working code to send to mitre
e
s 00011/00002/00800
d D 8.6 95/02/11 16:35:47 sklower 50 48
c fixes from jch
e
s 00051/00018/00778
d D 8.3.2.1 94/12/02 15:15:00 sklower 49 46
c document non-working version sent to mitre
e
s 00002/00002/00800
d D 8.5 94/11/02 18:23:48 sklower 48 47
c this one actually compiles . . .
e
s 00017/00022/00785
d D 8.4 94/10/31 13:42:56 sklower 47 45
c compromise fixes for duped keys
e
s 00008/00019/00788
d D 8.3.1.1 94/10/09 01:57:16 sklower 46 45
c compromise fixes re: Richard Woundy; moves knowledge of dupedkey-chains
c and finding a match relative to a key **and** a mask to an AF-specific routine.
e
s 00002/00005/00805
d D 8.3 94/01/04 21:51:37 bostic 45 44
c lint
e
s 00000/00001/00810
d D 8.2 93/11/15 13:32:50 sklower 44 43
c af.h has been retired
e
s 00002/00002/00809
d D 8.1 93/06/10 22:45:38 bostic 43 42
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00012/00793
d D 7.38 93/06/04 17:30:45 bostic 42 41
c prototype everything
e
s 00003/00001/00802
d D 7.37 93/04/13 16:25:41 sklower 41 40
c fix two bugs: rn_lookup did not change conventions (still takes node);
c found cause of ifa_refcnt being wrong on route change.
e
s 00003/00003/00800
d D 7.36 93/04/08 17:12:41 sklower 40 39
c new conventions for using routing tree
e
s 00002/00003/00801
d D 7.35 93/03/05 12:19:46 sklower 39 38
c almost never needed m_pullup to insure at least 4 bytes in first
c mbuf causes double allocation of mbufs, causing grief in busy routers.
c (From Heimlich@IBM via jch)
e
s 00002/00002/00802
d D 7.34 93/03/05 12:13:08 bostic 38 37
c need type consistency for sysctl (by sklower)
e
s 00001/00000/00803
d D 7.33 93/03/05 12:12:13 sklower 37 36
c when doing a RTM_GET you can have different sockaddrs returned
c than what you started with.
e
s 00033/00023/00770
d D 7.32 93/02/04 00:57:20 mckusick 36 35
c convert kinfo_rtable to sysctl_rtable
e
s 00013/00013/00780
d D 7.31 92/10/11 11:49:08 bostic 35 34
c make kernel includes standard
e
s 00001/00000/00792
d D 7.30 92/07/12 17:38:15 pendry 34 33
c need to include "systm.h"
e
s 00002/00002/00790
d D 7.29 92/07/09 00:02:36 sklower 33 32
c changes to add routing tables via the domain switch
e
s 00001/00000/00791
d D 7.28 92/06/19 12:47:10 sklower 32 31
c set ifa_flags in NEWADDR message
e
s 00010/00003/00781
d D 7.27 92/03/02 22:25:25 ralph 31 30
c fix uninitialized variable (dst) if senderr called in route_output().
e
s 00012/00004/00772
d D 7.26 92/02/25 12:43:11 sklower 30 29
c make it possible to change routes with duped keys, when
c exactly matching netmasks are provided
e
s 00006/00003/00770
d D 7.25 92/02/21 12:05:08 sklower 29 28
c yet another oversight (need to mask off af bits from op)
e
s 00371/00197/00402
d D 7.24 92/02/18 15:47:10 sklower 28 27
c new kerninfo for surveying interface list; new conventions for
c rt_missmsg; new routing messages for interface added, deleted, state change
e
s 00000/00002/00599
d D 7.23 92/01/30 11:43:33 torek 27 26
c checked in for torek by sklower; Mike agrees to all these changes
e
s 00004/00010/00597
d D 7.22 91/08/08 14:33:24 sklower 26 25
c move logic about traversing dupkeyed entries from rtdumpentry to rn_walk
e
s 00001/00001/00606
d D 7.21 91/08/08 14:30:46 sklower 25 24
c RTM_LOCK immediately clears any lock it sets (dumb dumb dumb)
e
s 00004/00026/00603
d D 7.20 91/07/30 17:40:29 sklower 24 23
c use vector on AF for routing tables rather than linked list;
c allow for methods on an AF-by-AF basis for add, insert, delete, kinfo-walk
e
s 00001/00004/00628
d D 7.19 91/06/27 18:58:27 sklower 23 22
c dst and gateway sockaddr's allocated separately from rtentry;
c make RTM_CHANGE easier, and less total space.
e
s 00002/00001/00630
d D 7.18 91/06/27 18:57:15 sklower 22 20
c add setable rmx_expire
e
s 00002/00004/00627
d R 7.18 91/06/25 22:07:55 sklower 21 20
c dst and gateway sockaddr's allocated separately from rtentry;
c make RTM_CHANGE easier, and less total space.
e
s 00003/00005/00628
d D 7.17 91/04/26 14:42:31 sklower 20 19
c off by one error in m_copyback (would exhaust all mbufs when
c asked to append nothing at end); change u.u_cprocp to curproc
e
s 00031/00024/00602
d D 7.16 91/03/16 17:11:25 sklower 19 17
c allow ifa to be specifed idependently/in addition to
c ifp on RTM_CHANGE; allow fuzzy matching only on RTM_GET;
c experiment with different conventions on calling the ifa_rtrequest() on RTM_CHANGE.
e
s 00031/00024/00602
d R 7.16 91/03/16 17:07:39 sklower 18 17
c allow the ifa to be specified as well as the ifp on a RTM_CHANGE\;
e
s 00052/00033/00574
d D 7.15 90/11/29 15:50:57 sklower 17 16
c make changes to RTM_GET so that you can indicate that you want
c it to return ifp and ifa, by including null ones in message;
c make changes to allow that any supplied or gotten sockaddr may have a zero
c length field.
e
s 00047/00035/00560
d D 7.14 90/09/03 16:33:50 sklower 16 15
c checkpoint to run on arpa
e
s 00007/00003/00588
d D 7.13 90/07/24 18:15:52 sklower 15 14
c fix bug in routing socket, add sanity check . . . 
c set splnet() in route_usrreq(), which may not be necessary.
e
s 00001/00011/00590
d D 7.12 90/06/28 21:32:28 bostic 14 13
c new copyright notice
e
s 00002/00007/00599
d D 7.11 90/06/25 17:16:39 sklower 13 10
c inserting a zero-length mbuf for address in the sockbuf for a
c routing socket makes us nervous; remove extraneous protsw entry.
e
s 00001/00006/00600
d R 7.11 90/06/25 12:21:15 sklower 12 10
c routing messages have addresses embedded in them rather than 
c separately, as does udp, idp, etc. so PR_ADDR is wrong.
e
s 00001/00006/00600
d R 7.11 90/06/25 12:18:25 sklower 11 10
c routing messages do not come with attached addresses
e
s 00046/00005/00560
d D 7.10 90/06/20 19:05:27 sklower 10 9
c changes designed so that ESIS and ARP may use routing table
c instead of private cache; allow RTM_CHANGE to specify new ifp.
e
s 00024/00002/00541
d D 7.9 90/05/25 15:43:34 sklower 9 8
c getkerninfo skipped defaults ``dupedkeyed'' behind the root node;
c add sosetopt SO_USELOOPBACK == 0 to have a routing socket not echo it own msgs.
e
s 00081/00080/00462
d D 7.8 90/04/05 11:34:48 sklower 8 7
c rtmsg format changed; always include metrics; sockaddrs identified
c by bitvector; upped version number.
e
s 00167/00014/00375
d D 7.7 90/03/12 13:42:09 sklower 7 6
c changes to support getkerninfo()
e
s 00000/00001/00389
d D 7.6 90/02/17 10:22:02 mckusick 6 5
c get rid of dir.h
e
s 00013/00012/00377
d D 7.5 89/08/29 15:01:42 sklower 5 4
c plug memory leak; check in for ``alpha'' tape
e
s 00000/00001/00389
d D 7.4 89/05/05 00:24:10 mckusick 4 3
c get rid of unnedded include of dir.h
e
s 00001/00001/00389
d D 7.3 89/04/25 14:25:41 mckusick 3 2
c ../machine => machine
e
s 00032/00025/00358
d D 7.2 89/04/22 12:11:33 sklower 2 1
c checkpoint at first working tp4 connection; before gnodes
e
s 00383/00000/00000
d D 7.1 88/12/13 13:20:26 sklower 1 0
c date and time created 88/12/13 13:20:26 by sklower
e
u
U
f b 
f d 8.6
t
T
I 1
/*
D 22
 * Copyright (c) 1988 Regents of the University of California.
E 22
I 22
D 43
 * Copyright (c) 1988, 1991 Regents of the University of California.
E 22
 * All rights reserved.
E 43
I 43
 * Copyright (c) 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 43
 *
D 14
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
 *
 *	%W% (Berkeley) %G%
 */

D 8
#ifndef RTF_UP
E 8
D 35
#include "param.h"
I 34
#include "systm.h"
E 34
D 28
#include "mbuf.h"
E 28
I 5
D 6
#include "dir.h"
E 6
E 5
D 4
#include "dir.h"
E 4
D 20
#include "user.h"
E 20
#include "proc.h"
I 28
#include "mbuf.h"
E 28
#include "socket.h"
#include "socketvar.h"
#include "domain.h"
#include "protosw.h"
E 35
I 35
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
E 35
D 20
#include "errno.h"
E 20

D 35
#include "af.h"
I 7
#include "if.h"
E 7
#include "route.h"
#include "raw_cb.h"
E 35
I 35
D 44
#include <net/af.h>
E 44
#include <net/if.h>
#include <net/route.h>
#include <net/raw_cb.h>
E 35

D 3
#include "../machine/mtpr.h"
E 3
I 3
D 27
#include "machine/mtpr.h"
E 3
D 8
#endif
E 8

E 27
I 2
D 13
struct sockaddr route_dst = { 0, PF_ROUTE, };
struct sockaddr route_src = { 0, PF_ROUTE, };
E 13
I 13
D 28
struct sockaddr route_dst = { 2, PF_ROUTE, };
struct sockaddr route_src = { 2, PF_ROUTE, };
E 13
struct sockproto route_proto = { PF_ROUTE, };
E 28
I 28
struct	sockaddr route_dst = { 2, PF_ROUTE, };
struct	sockaddr route_src = { 2, PF_ROUTE, };
struct	sockproto route_proto = { PF_ROUTE, };
E 28

I 28
struct walkarg {
	int	w_op, w_arg, w_given, w_needed, w_tmemsize;
	caddr_t	w_where, w_tmem;
};

D 42
static	void rt_xaddrs		__P((caddr_t, caddr_t, struct rt_addrinfo *));
static	struct mbuf *rt_msg1	__P((int, struct rt_addrinfo *));
static	int rt_msg2		__P((int, struct rt_addrinfo *, caddr_t, 
					struct walkarg *));
E 42
I 42
static struct mbuf *
		rt_msg1 __P((int, struct rt_addrinfo *));
static int	rt_msg2 __P((int,
		    struct rt_addrinfo *, caddr_t, struct walkarg *));
D 49
D 51
static void	rt_xaddrs __P((caddr_t, caddr_t, struct rt_addrinfo *));
E 51
I 51
void	rt_xaddrs __P((caddr_t, caddr_t, struct rt_addrinfo *));
void	m_copyback __P((struct mbuf *, int, int, caddr_t));
E 51
E 49
I 49
caddr_t	rt_xaddrs __P((caddr_t, caddr_t, struct rt_addrinfo *));
void	m_copyback __P((struct mbuf *, int, int, caddr_t));
E 49
E 42

/* Sleazy use of local variables throughout file, warning!!!! */
#define dst	info.rti_info[RTAX_DST]
#define gate	info.rti_info[RTAX_GATEWAY]
#define netmask	info.rti_info[RTAX_NETMASK]
#define genmask	info.rti_info[RTAX_GENMASK]
#define ifpaddr	info.rti_info[RTAX_IFP]
#define ifaaddr	info.rti_info[RTAX_IFA]
#define brdaddr	info.rti_info[RTAX_BRD]

E 28
E 2
/*ARGSUSED*/
I 42
int
E 42
D 7
route_usrreq(so, req, m, nam, rights, control)
E 7
I 7
route_usrreq(so, req, m, nam, control)
E 7
	register struct socket *so;
	int req;
D 7
	struct mbuf *m, *nam, *rights, *control;
E 7
I 7
	struct mbuf *m, *nam, *control;
E 7
{
	register int error = 0;
	register struct rawcb *rp = sotorawcb(so);
I 15
	int s;
I 45
D 49

E 49
E 45
E 15
I 2
	if (req == PRU_ATTACH) {
		MALLOC(rp, struct rawcb *, sizeof(*rp), M_PCB, M_WAITOK);
		if (so->so_pcb = (caddr_t)rp)
			bzero(so->so_pcb, sizeof(*rp));

	}
E 2
	if (req == PRU_DETACH && rp) {
		int af = rp->rcb_proto.sp_protocol;
		if (af == AF_INET)
			route_cb.ip_count--;
		else if (af == AF_NS)
			route_cb.ns_count--;
D 2
#ifdef ISO
E 2
		else if (af == AF_ISO)
			route_cb.iso_count--;
D 2
#endif
E 2
		route_cb.any_count--;
	}
I 15
	s = splnet();
E 15
D 7
	error = raw_usrreq(so, req, m, nam, rights, control);
E 7
I 7
	error = raw_usrreq(so, req, m, nam, control);
E 7
	rp = sotorawcb(so);
D 2
	if (error == 0 && req == PRU_ATTACH && rp) {
E 2
I 2
	if (req == PRU_ATTACH && rp) {
E 2
		int af = rp->rcb_proto.sp_protocol;
I 2
		if (error) {
			free((caddr_t)rp, M_PCB);
I 15
			splx(s);
E 15
			return (error);
		}
E 2
		if (af == AF_INET)
			route_cb.ip_count++;
		else if (af == AF_NS)
			route_cb.ns_count++;
D 2
#ifdef ISO
E 2
		else if (af == AF_ISO)
			route_cb.iso_count++;
D 2
#endif
		rp->rcb_flags |= RAW_FADDR;
E 2
I 2
		rp->rcb_faddr = &route_src;
E 2
		route_cb.any_count++;
		soisconnected(so);
I 9
		so->so_options |= SO_USELOOPBACK;
E 9
	}
I 15
	splx(s);
E 15
	return (error);
}
D 17
#define ROUNDUP(a) (1 + (((a) - 1) | (sizeof(long) - 1)))
I 16
#define ADVANCE(x, n) (x += ((n) > 0 ? ROUNDUP(n) : sizeof(long)))
E 17
I 17
D 28
#define ROUNDUP(a) \
	((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
#define ADVANCE(x, n) (x += ROUNDUP((n)->sa_len))
E 28
E 17
E 16

D 2
struct sockaddr route_dst = { 0, PF_ROUTE, };
struct sockaddr route_src = { 0, PF_ROUTE, };
struct sockproto route_proto = { PF_ROUTE, };

E 2
I 2
/*ARGSUSED*/
I 42
int
E 42
E 2
route_output(m, so)
	register struct mbuf *m;
	struct socket *so;
{
D 10
	register struct rt_msghdr *rtm = 0;
E 10
I 10
D 15
	register struct rt_msghdr *rtm;
E 15
I 15
	register struct rt_msghdr *rtm = 0;
E 15
E 10
	register struct rtentry *rt = 0;
D 5
	struct mbuf *m0 = m;
E 5
D 7
	struct rtentry *saved_nrt;
E 7
I 7
	struct rtentry *saved_nrt = 0;
I 47
	struct radix_node_head *rnh;
E 47
I 46
D 49
	struct radix_node_head *rnh;
E 49
E 46
E 7
D 8
	struct sockaddr *dst = 0, *gate = 0, *netmask = 0, *author;
	struct rt_metrics *rmm = 0;
D 2
	struct radix_node_head *rnh;
	struct radix_node *rn;
E 2
	caddr_t cp = 0;
E 8
I 8
D 28
	struct sockaddr *dst = 0, *gate = 0, *netmask = 0, *genmask = 0;
I 10
D 17
	struct sockaddr *ifpaddr = 0;
E 17
I 17
D 19
	struct sockaddr *ifpaddr = 0, *ifaaddr;
E 19
I 19
	struct sockaddr *ifpaddr = 0, *ifaaddr = 0;
E 19
E 17
E 10
	caddr_t cp, lim;
E 28
I 28
	struct rt_addrinfo info;
E 28
E 8
D 2
	int len, error = 0, s;
E 2
I 2
	int len, error = 0;
I 10
	struct ifnet *ifp = 0;
D 19
	struct	ifaddr *ifa;
	extern struct ifaddr *ifaof_ifpforaddr(), *ifa_ifwithroute();
E 19
I 19
	struct ifaddr *ifa = 0;
I 49
	caddr_t pkthdr;
	struct radix_node_head *rnh;
E 49
D 42
	struct ifaddr *ifaof_ifpforaddr(), *ifa_ifwithroute();
E 42
E 19
E 10
E 2

D 7
#define FLUSH(e) { error = e; goto flush;}
E 7
I 7
#define senderr(e) { error = e; goto flush;}
E 7
D 5
	if (m == 0 || (m = m_pullup(m, sizeof(long))) == 0)
		FLUSH(ENOBUFS);
E 5
I 5
D 8
	if (m == 0)
E 8
I 8
D 39
	if (m == 0 || m->m_len < sizeof(long))
E 8
		return (ENOBUFS);
D 8
	if (m->m_len < sizeof(long))
		if ((m = m_pullup(m, sizeof(long))) == 0)
			return (ENOBUFS);
E 8
I 8
	if ((m = m_pullup(m, sizeof(long))) == 0)
E 39
I 39
	if (m == 0 || ((m->m_len < sizeof(long)) &&
		       (m = m_pullup(m, sizeof(long))) == 0))
E 39
		return (ENOBUFS);
E 8
E 5
	if ((m->m_flags & M_PKTHDR) == 0)
D 5
		return (EOPNOTSUPP);
E 5
I 5
		panic("route_output");
E 5
	len = m->m_pkthdr.len;
D 15
	rtm = mtod(m, struct rt_msghdr *);
	if (len < rtm->rtm_msglen)
E 15
I 15
	if (len < sizeof(*rtm) ||
D 31
	    len != mtod(m, struct rt_msghdr *)->rtm_msglen)
E 31
I 31
	    len != mtod(m, struct rt_msghdr *)->rtm_msglen) {
		dst = 0;
E 31
E 15
D 7
		FLUSH(EINVAL);
E 7
I 7
		senderr(EINVAL);
I 31
	}
E 31
E 7
	R_Malloc(rtm, struct rt_msghdr *, len);
D 31
	if (rtm == 0)
E 31
I 31
	if (rtm == 0) {
		dst = 0;
E 31
D 7
		FLUSH(ENOBUFS);
E 7
I 7
		senderr(ENOBUFS);
I 31
	}
E 31
E 7
	m_copydata(m, 0, len, (caddr_t)rtm);
D 8
	if (rtm->rtm_version != 1)
E 8
I 8
D 31
	if (rtm->rtm_version != RTM_VERSION)
E 31
I 31
	if (rtm->rtm_version != RTM_VERSION) {
		dst = 0;
E 31
E 8
D 7
		FLUSH(EPROTONOSUPPORT);
E 7
I 7
		senderr(EPROTONOSUPPORT);
I 31
	}
E 31
E 7
D 20
	rtm->rtm_pid = u.u_procp->p_pid;
E 20
I 20
	rtm->rtm_pid = curproc->p_pid;
E 20
I 8
D 28
	lim = len + (caddr_t) rtm;
E 8
	cp = (caddr_t) (rtm + 1);
D 8
#ifdef notyet
	switch (rtm->rtm_type) {

	case RTM_ADD: case RTM_CHANGE: case RTM_GET:
		rmm = (struct rt_metrics *)cp ;
		cp = (caddr_t) (rmm + 1);
	}
#endif
	if (rtm->rtm_count > 0) {
E 8
I 8
	if (rtm->rtm_addrs & RTA_DST) {
E 8
		dst = (struct sockaddr *)cp;
D 16
		cp += ROUNDUP(dst->sa_len);
E 16
I 16
D 17
		ADVANCE(cp, dst->sa_len);
E 17
I 17
		ADVANCE(cp, dst);
E 17
E 16
D 8
	}
	if (rtm->rtm_count > 1)  {
E 8
I 8
	} else
E 28
I 28
	info.rti_addrs = rtm->rtm_addrs;
D 49
	rt_xaddrs((caddr_t)(rtm + 1), len + (caddr_t)rtm, &info);
I 51
	info.rti_flags = rtm->rtm_flags;
E 51
E 49
I 49
	pkthdr = rt_xaddrs((caddr_t)(rtm + 1), len + (caddr_t)rtm, &info);
	info.rti_flags = rtm->rtm_flags;
E 49
	if (dst == 0)
E 28
		senderr(EINVAL);
D 28
	if ((rtm->rtm_addrs & RTA_GATEWAY) && cp < lim)  {
E 8
		gate = (struct sockaddr *)cp;
D 17
		cp += ROUNDUP(gate->sa_len);
E 17
I 17
		ADVANCE(cp, gate);
E 17
	}
D 8
	if (rtm->rtm_count > 2)  {
E 8
I 8
	if ((rtm->rtm_addrs & RTA_NETMASK) && cp < lim)  {
E 8
		netmask = (struct sockaddr *)cp;
D 2
		cp += ROUNDUP(netmask->sa_len);
E 2
I 2
D 16
		if (*cp)
			cp += ROUNDUP(netmask->sa_len);
		else
			cp += sizeof(long);

E 16
I 16
D 17
		ADVANCE(cp, netmask->sa_len);
E 17
I 17
		ADVANCE(cp, netmask);
E 17
E 16
E 2
	}
D 8
	if (rtm->rtm_count > 3)  {
		author = (struct sockaddr *)cp;
E 8
I 8
	if ((rtm->rtm_addrs & RTA_GENMASK) && cp < lim)  {
E 28
I 28
	if (genmask) {
E 28
I 10
D 42
		struct radix_node *t, *rn_addmask();
E 10
D 28
		genmask = (struct sockaddr *)cp;
I 10
D 16
		if (*cp)
			cp += ROUNDUP(netmask->sa_len);
		else
			cp += sizeof(long);
E 16
I 16
D 17
		ADVANCE(cp, genmask->sa_len);
E 17
I 17
		ADVANCE(cp, genmask);
E 28
E 17
E 16
		t = rn_addmask(genmask, 1, 2);
E 42
I 42
		struct radix_node *t;
D 46
D 47
		t = rn_addmask((caddr_t)genmask, 1, 2);
E 47
I 47
		t = rn_addmask((caddr_t)genmask, 0, 1);
E 47
E 46
I 46
D 49
		t = rn_addmask((caddr_t)genmask, 0, 1);
E 49
I 49
		t = rn_addmask((caddr_t)genmask, 1, 2);
E 49
E 46
E 42
		if (t && Bcmp(genmask, t->rn_key, *(u_char *)genmask) == 0)
			genmask = (struct sockaddr *)(t->rn_key);
		else
			senderr(ENOBUFS);
E 10
E 8
	}
I 10
D 28
	if ((rtm->rtm_addrs & RTA_IFP) && cp < lim)  {
		ifpaddr = (struct sockaddr *)cp;
I 19
		ADVANCE(cp, ifpaddr);
E 19
	}
I 19
	if ((rtm->rtm_addrs & RTA_IFA) && cp < lim)  {
		ifaaddr = (struct sockaddr *)cp;
	}
E 28
E 19
E 10
	switch (rtm->rtm_type) {
I 28

I 51
	case RTM_ADDPKT:
E 51
E 28
	case RTM_ADD:
I 8
		if (gate == 0)
			senderr(EINVAL);
E 8
D 49
D 51
		error = rtrequest(RTM_ADD, dst, gate, netmask,
					rtm->rtm_flags, &saved_nrt);
E 51
I 51
		error = rtrequest1(rtm->rtm_type, &info, &saved_nrt);
E 51
E 49
I 49
		error = rtrequest1(RTM_ADD, &info, &saved_nrt);
		goto add_metrics;

	case RTM_ADDPKT:
		if  ((rnh = rt_tables[dst->sa_family]) == 0 ||
		     rnh->rnh_addpkt == 0)
			senderr(EAFNOSUPPORT);
		error = rnh->rnh_addpkt(pkthdr, &info, rnh, 
			saved_nrt->rt_nodes);
	add_metrics:
E 49
D 8
		/* XXX -- add metrics !!! */
I 7
		if (error == 0 && saved_nrt)
E 8
I 8
		if (error == 0 && saved_nrt) {
			rt_setmetrics(rtm->rtm_inits,
				&rtm->rtm_rmx, &saved_nrt->rt_rmx);
E 8
			saved_nrt->rt_refcnt--;
I 10
			saved_nrt->rt_genmask = genmask;
E 10
I 8
		}
E 8
E 7
		break;

I 51
	case RTM_DELPKT:
E 51
I 49
	case RTM_DELPKT:
		if  ((rnh = rt_tables[dst->sa_family]) == 0 ||
		     rnh->rnh_delpkt == 0)
			senderr(EAFNOSUPPORT);
		error = rnh->rnh_delpkt(pkthdr, &info, rnh);

E 49
	case RTM_DELETE:
D 49
D 51
		error = rtrequest(RTM_DELETE, dst, gate, netmask,
D 2
					rtm->rtm_flags, 0);
E 2
I 2
D 47
				rtm->rtm_flags, (struct rtentry **)0);
E 49
I 49
		error = rtrequest1(RTM_DELETE, &info, (struct rtentry **)0);
E 49
E 47
I 47
				rtm->rtm_flags, &saved_nrt);
E 51
I 51
		error = rtrequest1(rtm->rtm_type, &info, &saved_nrt);
E 51
		if (error == 0) {
D 50
			if ((rt = saved_nrt)->rt_refcnt <= 0)
				rt->rt_refcnt++;
E 50
I 50
			(rt = saved_nrt)->rt_refcnt++;
E 50
			goto report;
		}
E 47
E 2
		break;

D 49
	case RTM_GET:
E 49
	case RTM_CHANGE:
I 49
	case RTM_GET:
E 49
	case RTM_LOCK:
D 46
D 47
		rt = rtalloc1(dst, 0);
		if (rt == 0)
E 47
I 47
D 48
		if ((rnh = rt_tables[dst->sa_family]) == 0)
E 48
I 48
		if ((rnh = rt_tables[dst->sa_family]) == 0) {
E 48
			senderr(EAFNOSUPPORT);
D 48
		else if (rt = (struct rtentry *)
E 48
I 48
		} else if (rt = (struct rtentry *)
E 48
				rnh->rnh_lookup(dst, netmask, rnh))
			rt->rt_refcnt++;
		else
E 47
E 46
I 46
D 49
		if ((rnh = rt_tables[dst->sa_family]) == 0)
			senderr(EAFNOSUPPORT);
		else if (rt = (struct rtentry *)
				rnh->rnh_lookup(dst, netmask, rnh))
			rt->rt_refcnt++;
		else
E 49
I 49
		rt = rtalloc1(dst, 0);
		if (rt == 0)
E 49
E 46
D 7
			FLUSH(ESRCH);
E 7
I 7
			senderr(ESRCH);
I 49
		if (rtm->rtm_type != RTM_GET) {/* XXX: too grotty */
			struct radix_node *rn;
			extern struct radix_node_head *mask_rnhead;

			if (Bcmp(dst, rt_key(rt), dst->sa_len) != 0)
				senderr(ESRCH);
			if (netmask && (rn = rn_search(netmask,
					    mask_rnhead->rnh_treetop)))
				netmask = (struct sockaddr *)rn->rn_key;
			for (rn = rt->rt_nodes; rn; rn = rn->rn_dupedkey)
				if (netmask == (struct sockaddr *)rn->rn_mask)
					break;
			if (rn == 0)
				senderr(ETOOMANYREFS);
			rt = (struct rtentry *)rn;
		}
E 49
I 16
D 19
		if (((struct radix_node *)rt)->rn_dupedkey) {
			if (netmask == 0 && rtm->rtm_type != RTM_GET)
E 19
I 19
D 30
		if (rtm->rtm_type != RTM_GET) {
E 30
I 30
D 46
D 47
		if (rtm->rtm_type != RTM_GET) {/* XXX: too grotty */
D 42
			struct radix_node *rn, *rn_search();
E 42
I 42
			struct radix_node *rn;
E 42
			extern struct radix_node_head *mask_rnhead;

E 30
			if (Bcmp(dst, rt_key(rt), dst->sa_len) != 0)
				senderr(ESRCH);
D 30
			if (rt->rt_nodes->rn_dupedkey &&
			    (netmask == 0 ||
			     Bcmp(netmask, rt_mask(rt), netmask->sa_len)))
E 30
I 30
			if (netmask && (rn = rn_search(netmask,
D 40
					    mask_rnhead->rnh_treetop)))
E 40
I 40
D 41
					    mask_rnhead)))
E 41
I 41
					    mask_rnhead->rnh_treetop)))
E 41
E 40
				netmask = (struct sockaddr *)rn->rn_key;
			for (rn = rt->rt_nodes; rn; rn = rn->rn_dupedkey)
				if (netmask == (struct sockaddr *)rn->rn_mask)
					break;
			if (rn == 0)
E 30
E 19
				senderr(ETOOMANYREFS);
I 30
			rt = (struct rtentry *)rn;
E 30
		}
E 47
E 46
E 16
E 7
		switch(rtm->rtm_type) {
D 16
			 struct	sockaddr *outmask;
E 16

		case RTM_GET:
I 47
		report:
E 47
D 16
			netmask = rt_mask(rt);
D 8
			len = sizeof(*rtm) + ROUNDUP(rt_key(rt)->sa_len)
					+ ROUNDUP(rt->rt_gateway->sa_len);
			if (netmask)
E 8
I 8
			len = sizeof(*rtm) + ROUNDUP(rt_key(rt)->sa_len);
			rtm->rtm_addrs = RTA_DST;
			if (rt->rt_gateway) {
E 16
I 16
D 17
			dst = rt_key(rt);
			len = sizeof(*rtm) + (dst->sa_len > 0 ?
				ROUNDUP(dst->sa_len) : sizeof(long));
E 17
I 17
D 28
			dst = rt_key(rt); len = sizeof(*rtm);
			ADVANCE(len, dst);
E 17
			rtm->rtm_addrs |= RTA_DST;
			if (gate = rt->rt_gateway) {
E 16
D 17
				len += ROUNDUP(rt->rt_gateway->sa_len);
E 17
I 17
				ADVANCE(len, gate);
E 17
				rtm->rtm_addrs |= RTA_GATEWAY;
D 16
			}
			if (netmask) {
E 16
I 16
			} else
				rtm->rtm_addrs &= ~RTA_GATEWAY;
			if (netmask = rt_mask(rt)) {
E 16
E 8
D 2
				len + netmask->sa_len;
E 2
I 2
D 17
				len += netmask->sa_len;
E 17
I 17
				ADVANCE(len, netmask);
E 17
I 8
				rtm->rtm_addrs |= RTA_NETMASK;
D 16
			}
E 16
I 16
			} else
				rtm->rtm_addrs &= ~RTA_NETMASK;
D 17
			if (rt->rt_genmask) {
				len += ROUNDUP(rt->rt_genmask->sa_len);
E 17
I 17
			if (genmask = rt->rt_genmask) {
				ADVANCE(len, genmask);
E 17
				rtm->rtm_addrs |= RTA_GENMASK;
			} else
				rtm->rtm_addrs &= ~RTA_GENMASK;
E 28
I 28
			dst = rt_key(rt);
			gate = rt->rt_gateway;
			netmask = rt_mask(rt);
			genmask = rt->rt_genmask;
E 28
I 17
			if (rtm->rtm_addrs & (RTA_IFP | RTA_IFA)) {
D 28
				if (rt->rt_ifp == 0)
					goto badif;
				for (ifa = rt->rt_ifp->if_addrlist;
				    ifa && ifa->ifa_addr->sa_family != AF_LINK;
				     ifa = ifa->ifa_next){}
				if (ifa && rt->rt_ifa) {
					ifpaddr = ifa->ifa_addr;
					ADVANCE(len, ifpaddr);
E 28
I 28
				if (ifp = rt->rt_ifp) {
					ifpaddr = ifp->if_addrlist->ifa_addr;
E 28
					ifaaddr = rt->rt_ifa->ifa_addr;
I 50
					if (ifp->if_flags & IFF_POINTOPOINT)
						brdaddr = rt->rt_ifa->ifa_dstaddr;
					else
						brdaddr = 0;
E 50
D 28
					ADVANCE(len, ifaaddr);
					rtm->rtm_addrs |= RTA_IFP | RTA_IFA;
E 28
I 28
					rtm->rtm_index = ifp->if_index;
E 28
				} else {
D 28
				badif:	ifpaddr = 0;
					rtm->rtm_addrs &= ~(RTA_IFP | RTA_IFA);
				}
E 28
I 28
					ifpaddr = 0;
					ifaaddr = 0;
			    }
E 28
			}
I 28
D 47
			len = rt_msg2(RTM_GET, &info, (caddr_t)0,
E 47
I 47
			len = rt_msg2(rtm->rtm_type, &info, (caddr_t)0,
E 47
				(struct walkarg *)0);
E 28
E 17
E 16
E 8
E 2
			if (len > rtm->rtm_msglen) {
				struct rt_msghdr *new_rtm;
				R_Malloc(new_rtm, struct rt_msghdr *, len);
				if (new_rtm == 0)
D 7
					FLUSH(ENOBUFS);
E 7
I 7
					senderr(ENOBUFS);
E 7
				Bcopy(rtm, new_rtm, rtm->rtm_msglen);
				Free(rtm); rtm = new_rtm;
D 16
				gate = (struct sockaddr *)
				    (ROUNDUP(rt->rt_gateway->sa_len)
								+ (char *)dst);
				Bcopy(&rt->rt_gateway, gate,
						rt->rt_gateway->sa_len);
				rtm->rtm_flags = rt->rt_flags;
D 8
				rtm->rtm_count = 2;
E 8
				if (netmask) {
				    outmask = (struct sockaddr *)
				       (ROUNDUP(netmask->sa_len)+(char *)gate);
				    Bcopy(netmask, outmask, netmask->sa_len);
D 8
				    rtm->rtm_count = 3;
E 8
				}
E 16
			}
I 16
D 28
			rtm->rtm_msglen = len;
E 28
I 28
D 47
			(void)rt_msg2(RTM_GET, &info, (caddr_t)rtm,
E 47
I 47
			(void)rt_msg2(rtm->rtm_type, &info, (caddr_t)rtm,
E 47
				(struct walkarg *)0);
E 28
			rtm->rtm_flags = rt->rt_flags;
			rtm->rtm_rmx = rt->rt_rmx;
I 37
			rtm->rtm_addrs = info.rti_addrs;
E 37
D 28
			cp = (caddr_t) (1 + rtm);
D 17
			Bcopy(dst, cp, dst->sa_len);
			ADVANCE(cp, dst->sa_len);
E 17
I 17
			len = ROUNDUP(dst->sa_len); 
			Bcopy(dst, cp, len); cp += len;
E 17
			if (gate) {
D 17
			    Bcopy(gate, cp, gate->sa_len);
			    ADVANCE(cp, gate->sa_len);
E 17
I 17
			    len = ROUNDUP(gate->sa_len);
			    Bcopy(gate, cp, len); cp += len;
E 17
			}
			if (netmask) {
D 17
			    Bcopy(netmask, cp, netmask->sa_len);
			    ADVANCE(cp, netmask->sa_len);
E 17
I 17
			    len = ROUNDUP(netmask->sa_len);
			    Bcopy(netmask, cp, len); cp += len;
E 17
			}
D 17
			if (rt->rt_genmask) {
			    Bcopy(rt->rt_genmask, cp, rt->rt_genmask->sa_len);
			    ADVANCE(cp, rt->rt_genmask->sa_len);
E 17
I 17
			if (genmask) {
			    len = ROUNDUP(genmask->sa_len);
			    Bcopy(genmask, cp, len); cp += len;
E 17
			}
I 17
			if (ifpaddr) {
			    len = ROUNDUP(ifpaddr->sa_len);
			    Bcopy(ifpaddr, cp, len); cp += len;
			    len = ROUNDUP(ifaaddr->sa_len);
			    Bcopy(ifaaddr, cp, len); cp += len;
			}
E 28
E 17
E 16
			break;

		case RTM_CHANGE:
I 8
D 10
			if (gate == 0)
E 10
I 10
D 16
			if (gate == 0 || netmask != 0)
E 10
				senderr(EINVAL);
E 8
			if (gate->sa_len > (len = rt->rt_gateway->sa_len))
E 16
I 16
D 23
			if (gate &&
			    (gate->sa_len > (len = rt->rt_gateway->sa_len)))
E 23
I 23
D 51
			if (gate && rt_setgate(rt, rt_key(rt), gate))
E 23
E 16
D 7
				FLUSH(EDQUOT);
			if (gate->sa_family != rt->rt_gateway->sa_family)
				FLUSH(EADDRINUSE);
E 7
I 7
				senderr(EDQUOT);
E 51
D 19
			if (rt->rt_ifa && rt->rt_ifa->ifa_rtrequest)
D 10
				rt->rt_ifa->ifa_rtrequest(RTM_CHANGE, rt, gate);
E 10
I 10
				rt->rt_ifa->ifa_rtrequest(RTM_DELETE, rt, gate);
E 19
			/* new gateway could require new ifaddr, ifp;
			   flags may also be different; ifp may be specified
			   by ll sockaddr when protocol address is ambiguous */
D 19
			if (ifpaddr &&
			    (ifa = ifa_ifwithnet(ifpaddr)) &&
			    (ifp = ifa->ifa_ifp) &&
			    (ifa = ifaof_ifpforaddr(gate, ifp))) {
				     /* We got it */
			} else {
			    ifa = 0; ifp = 0;
			}
E 10
E 7
D 16
			Bcopy(gate, rt->rt_gateway, len);
			rt->rt_gateway->sa_len = len;
E 16
I 16
			if (gate)
				Bcopy(gate, rt->rt_gateway, len);
E 16
D 10
		
E 10
D 8
#ifdef notdef
#define metric(f, e) if (rtm->rtm_inits & (f)) rt->rt_m.e = rtm->e;
			metric(RTM_RPIPE, rtm_recvpipe);
			metric(RTM_SPIPE, rtm_sendpipe);
			metric(RTM_SSTHRESH, rtm_ssthresh);
			metric(RTM_RTT, rtm_rtt);
			metric(RTM_RTTVAR, rtm_rttvar);
			metric(RTM_HOPCOUNT, rtm_hopcount);
			metric(RTM_MTU, rtm_mtu);
E 8
I 8
			rt_setmetrics(rtm->rtm_inits,
				&rtm->rtm_rmx, &rt->rt_rmx);
I 10
			if (ifa == 0)
			    ifa = ifa_ifwithroute(rt->rt_flags, rt_key(rt),
						gate);
E 19
I 19
D 51
			if (ifpaddr && (ifa = ifa_ifwithnet(ifpaddr)) &&
			    (ifp = ifa->ifa_ifp))
				ifa = ifaof_ifpforaddr(ifaaddr ? ifaaddr : gate,
							ifp);
			else if ((ifaaddr && (ifa = ifa_ifwithaddr(ifaaddr))) ||
				 (ifa = ifa_ifwithroute(rt->rt_flags,
							rt_key(rt), gate)))
				ifp = ifa->ifa_ifp;
E 19
			if (ifa) {
E 51
I 51
			if (error = rt_getifa(&info))
				senderr(error);
			if (gate && rt_setgate(rt, rt_key(rt), gate))
				senderr(EDQUOT);
			if (ifa = info.rti_ifa) {
E 51
D 19
				if (rt->rt_ifa != ifa) {
E 19
I 19
				register struct ifaddr *oifa = rt->rt_ifa;
				if (oifa != ifa) {
				    if (oifa && oifa->ifa_rtrequest)
					oifa->ifa_rtrequest(RTM_DELETE,
D 51
								rt, gate);
E 51
I 51
								rt, &info);
E 51
I 41
				    IFAFREE(rt->rt_ifa);
E 41
E 19
				    rt->rt_ifa = ifa;
I 41
				    ifa->ifa_refcnt++;
E 41
D 19
				    rt->rt_ifp = ifa->ifa_ifp;
E 19
I 19
D 51
				    rt->rt_ifp = ifp;
E 51
I 51
				    rt->rt_ifp = info.rti_ifp;
E 51
E 19
				}
			}
I 19
D 23
			if (gate)
				Bcopy(gate, rt->rt_gateway, len);
E 23
			rt_setmetrics(rtm->rtm_inits, &rtm->rtm_rmx,
					&rt->rt_rmx);
E 19
			if (rt->rt_ifa && rt->rt_ifa->ifa_rtrequest)
D 51
			       rt->rt_ifa->ifa_rtrequest(RTM_ADD, rt, gate);
E 51
I 51
			       rt->rt_ifa->ifa_rtrequest(RTM_ADD, rt, &info);
E 51
			if (genmask)
				rt->rt_genmask = genmask;
E 10
E 8
			/*
			 * Fall into
			 */
D 8
		case RTM_LOCKS:
			rt->rt_locks |= (rtm->rtm_inits & rtm->rtm_locks);
			rt->rt_locks &= ~(rtm->rtm_inits);
E 8
I 8
		case RTM_LOCK:
I 25
			rt->rt_rmx.rmx_locks &= ~(rtm->rtm_inits);
E 25
			rt->rt_rmx.rmx_locks |=
				(rtm->rtm_inits & rtm->rtm_rmx.rmx_locks);
D 25
			rt->rt_rmx.rmx_locks &= ~(rtm->rtm_inits);
E 25
E 8
			break;
D 8
#endif
E 8
		}
D 28
		goto cleanup;
E 28
I 28
		break;
E 28

	default:
D 7
		FLUSH(EOPNOTSUPP);
E 7
I 7
		senderr(EOPNOTSUPP);
E 7
	}

flush:
	if (rtm) {
		if (error)
			rtm->rtm_errno = error;
		else 
			rtm->rtm_flags |= RTF_DONE;
	}
I 49
cleanup:
E 49
D 45
cleanup:
E 45
	if (rt)
		rtfree(rt);
I 9
    {
	register struct rawcb *rp = 0;
	/*
	 * Check to see if we don't want our own messages.
	 */
	if ((so->so_options & SO_USELOOPBACK) == 0) {
		if (route_cb.any_count <= 1) {
			if (rtm)
				Free(rtm);
			m_freem(m);
			return (error);
		}
		/* There is another listener, so construct message */
		rp = sotorawcb(so);
	}
E 9
D 5
	cp = (caddr_t)rtm;
	m_copyback(m = m0, 0, len, cp);
	/*if (m->m_pkthdr.len != len) {
		m_freem(m);
		return (error);
	} */
E 5
I 5
D 17
	if (cp = (caddr_t)rtm) {
		m_copyback(m, 0, len, cp);
E 17
I 17
	if (rtm) {
		m_copyback(m, 0, rtm->rtm_msglen, (caddr_t)rtm);
E 17
		Free(rtm);
	}
I 9
	if (rp)
		rp->rcb_proto.sp_family = 0; /* Avoid us */
E 9
E 5
D 16
	route_proto.sp_protocol = dst->sa_family;
E 16
I 16
	if (dst)
		route_proto.sp_protocol = dst->sa_family;
E 16
D 5
	raw_input(m0, &route_proto, &route_src, &route_dst);
E 5
I 5
	raw_input(m, &route_proto, &route_src, &route_dst);
I 9
	if (rp)
		rp->rcb_proto.sp_family = PF_ROUTE;
    }
E 9
E 5
	return (error);
}

I 42
void
E 42
I 8
D 10
static rt_setmetrics(which, in, out)
E 10
I 10
rt_setmetrics(which, in, out)
E 10
	u_long which;
	register struct rt_metrics *in, *out;
{
#define metric(f, e) if (which & (f)) out->e = in->e;
	metric(RTV_RPIPE, rmx_recvpipe);
	metric(RTV_SPIPE, rmx_sendpipe);
	metric(RTV_SSTHRESH, rmx_ssthresh);
	metric(RTV_RTT, rmx_rtt);
	metric(RTV_RTTVAR, rmx_rttvar);
	metric(RTV_HOPCOUNT, rmx_hopcount);
	metric(RTV_MTU, rmx_mtu);
I 22
	metric(RTV_EXPIRE, rmx_expire);
E 22
#undef metric
}

I 28
#define ROUNDUP(a) \
	((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
#define ADVANCE(x, n) (x += ROUNDUP((n)->sa_len))

D 49
D 51
static void
E 51
I 51
void
E 51
E 49
I 49
caddr_t
E 49
rt_xaddrs(cp, cplim, rtinfo)
	register caddr_t cp, cplim;
	register struct rt_addrinfo *rtinfo;
{
	register struct sockaddr *sa;
D 51
	register int i;
E 51
I 51
	register int i, addrs = rtinfo->rti_addrs;
E 51
I 49
	caddr_t cp0 = cp;
E 49

D 51
	bzero(rtinfo->rti_info, sizeof(rtinfo->rti_info));
E 51
I 51
	bzero(rtinfo, sizeof(*rtinfo));
	rtinfo->rti_addrs = addrs;
E 51
	for (i = 0; (i < RTAX_MAX) && (cp < cplim); i++) {
D 51
		if ((rtinfo->rti_addrs & (1 << i)) == 0)
E 51
I 51
		if ((addrs & (1 << i)) == 0)
E 51
			continue;
		rtinfo->rti_info[i] = sa = (struct sockaddr *)cp;
		ADVANCE(cp, sa);
	}
I 51
	rtinfo->rti_pkthdr = cp;
E 51
I 49
	return cp;
E 49
}
I 31

E 31
E 28
E 8
/*
 * Copy data from a buffer back into the indicated mbuf chain,
 * starting "off" bytes from the beginning, extending the mbuf
 * chain if necessary.
 */
I 42
void
E 42
m_copyback(m0, off, len, cp)
	struct	mbuf *m0;
	register int off;
	register int len;
	caddr_t cp;
D 42

E 42
{
	register int mlen;
	register struct mbuf *m = m0, *n;
	int totlen = 0;

	if (m0 == 0)
		return;
D 20
	while (off >= (mlen = m->m_len)) {
E 20
I 20
	while (off > (mlen = m->m_len)) {
E 20
		off -= mlen;
		totlen += mlen;
		if (m->m_next == 0) {
			n = m_getclr(M_DONTWAIT, m->m_type);
			if (n == 0)
				goto out;
			n->m_len = min(MLEN, len + off);
			m->m_next = n;
		}
		m = m->m_next;
	}
	while (len > 0) {
		mlen = min (m->m_len - off, len);
D 2
		bcopy(cp, off + mtod(m, caddr_t), mlen);
E 2
I 2
		bcopy(cp, off + mtod(m, caddr_t), (unsigned)mlen);
E 2
		cp += mlen;
		len -= mlen;
		mlen += off;
		off = 0;
		totlen += mlen;
		if (len == 0)
			break;
		if (m->m_next == 0) {
			n = m_get(M_DONTWAIT, m->m_type);
			if (n == 0)
				break;
			n->m_len = min(MLEN, len);
			m->m_next = n;
		}
		m = m->m_next;
	}
out:	if (((m = m0)->m_flags & M_PKTHDR) && (m->m_pkthdr.len < totlen))
		m->m_pkthdr.len = totlen;
}

D 28
/* 
 * The miss message and losing message are very similar.
 */

D 2
rt_missmsg(type, dst, gate, mask, src, flags)
E 2
I 2
rt_missmsg(type, dst, gate, mask, src, flags, error)
E 2
register struct sockaddr *dst;
struct sockaddr *gate, *mask, *src;
E 28
I 28
static struct mbuf *
rt_msg1(type, rtinfo)
	int type;
	register struct rt_addrinfo *rtinfo;
E 28
{
	register struct rt_msghdr *rtm;
	register struct mbuf *m;
D 28
	int dlen = ROUNDUP(dst->sa_len);
	int len = dlen + sizeof(*rtm);
E 28
I 28
	register int i;
	register struct sockaddr *sa;
	int len, dlen;
E 28
D 2
	caddr_t cp = (caddr_t)dst;
E 2

D 28
	if (route_cb.any_count == 0)
		return;
E 28
	m = m_gethdr(M_DONTWAIT, MT_DATA);
	if (m == 0)
D 28
		return;
	m->m_pkthdr.len = m->m_len = min(len, MHLEN);
E 28
I 28
		return (m);
	switch (type) {

	case RTM_DELADDR:
	case RTM_NEWADDR:
		len = sizeof(struct ifa_msghdr);
		break;

	case RTM_IFINFO:
		len = sizeof(struct if_msghdr);
		break;

	default:
		len = sizeof(struct rt_msghdr);
	}
	if (len > MHLEN)
		panic("rt_msg1");
	m->m_pkthdr.len = m->m_len = len;
E 28
	m->m_pkthdr.rcvif = 0;
	rtm = mtod(m, struct rt_msghdr *);
D 28
	bzero((caddr_t)rtm, sizeof(*rtm)); /*XXX assumes sizeof(*rtm) < MHLEN*/
	rtm->rtm_flags = RTF_DONE | flags;
E 28
I 28
	bzero((caddr_t)rtm, len);
	for (i = 0; i < RTAX_MAX; i++) {
		if ((sa = rtinfo->rti_info[i]) == NULL)
			continue;
		rtinfo->rti_addrs |= (1 << i);
		dlen = ROUNDUP(sa->sa_len);
		m_copyback(m, len, dlen, (caddr_t)sa);
		len += dlen;
	}
	if (m->m_pkthdr.len != len) {
		m_freem(m);
		return (NULL);
	}
E 28
	rtm->rtm_msglen = len;
D 8
	rtm->rtm_version = 1;
E 8
I 8
	rtm->rtm_version = RTM_VERSION;
E 8
	rtm->rtm_type = type;
D 8
	rtm->rtm_count = 1;
E 8
I 8
D 28
	rtm->rtm_addrs = RTA_DST;
E 8
	if (type == RTM_OLDADD || type == RTM_OLDDEL) {
D 2
		int error = (int) src;
		src = (struct sockaddr *)0; /* XXXXXXX -- I admit. (KLS) */
E 2
D 20
		rtm->rtm_pid = u.u_procp->p_pid;
E 20
I 20
		rtm->rtm_pid = curproc->p_pid;
E 28
I 28
	return (m);
}

static int
rt_msg2(type, rtinfo, cp, w)
	int type;
	register struct rt_addrinfo *rtinfo;
	caddr_t cp;
	struct walkarg *w;
{
	register int i;
	int len, dlen, second_time = 0;
	caddr_t cp0;

	rtinfo->rti_addrs = 0;
again:
	switch (type) {

	case RTM_DELADDR:
	case RTM_NEWADDR:
		len = sizeof(struct ifa_msghdr);
		break;

	case RTM_IFINFO:
		len = sizeof(struct if_msghdr);
		break;

	default:
		len = sizeof(struct rt_msghdr);
E 28
E 20
D 2
		rtm->rtm_errno = error;
		if (error)
			rtm->rtm_flags &= ~RTF_DONE;
E 2
	}
D 28
	m_copyback(m, sizeof (*rtm), dlen, (caddr_t)dst);
	if (gate) {
		dlen = ROUNDUP(gate->sa_len);
		m_copyback(m, len ,  dlen, (caddr_t)gate);
E 28
I 28
	if (cp0 = cp)
		cp += len;
	for (i = 0; i < RTAX_MAX; i++) {
		register struct sockaddr *sa;

		if ((sa = rtinfo->rti_info[i]) == 0)
			continue;
		rtinfo->rti_addrs |= (1 << i);
		dlen = ROUNDUP(sa->sa_len);
		if (cp) {
			bcopy((caddr_t)sa, cp, (unsigned)dlen);
			cp += dlen;
		}
E 28
		len += dlen;
D 8
		rtm->rtm_count++;
E 8
I 8
D 28
		rtm->rtm_addrs |= RTA_GATEWAY;
E 28
E 8
	}
D 28
	if (mask) {
D 2
		dlen = ROUNDUP(mask->sa_len);
E 2
I 2
D 17
		if (mask->sa_len)
			dlen = ROUNDUP(mask->sa_len);
		else
			dlen = sizeof(long);
E 17
I 17
		dlen = ROUNDUP(mask->sa_len);
E 17
E 2
		m_copyback(m, len ,  dlen, (caddr_t)mask);
		len += dlen;
D 8
		rtm->rtm_count++;
E 8
I 8
		rtm->rtm_addrs |= RTA_NETMASK;
E 28
I 28
	if (cp == 0 && w != NULL && !second_time) {
		register struct walkarg *rw = w;

		rw->w_needed += len;
		if (rw->w_needed <= 0 && rw->w_where) {
			if (rw->w_tmemsize < len) {
				if (rw->w_tmem)
					free(rw->w_tmem, M_RTABLE);
				if (rw->w_tmem = (caddr_t)
						malloc(len, M_RTABLE, M_NOWAIT))
					rw->w_tmemsize = len;
			}
			if (rw->w_tmem) {
				cp = rw->w_tmem;
				second_time = 1;
				goto again;
			} else
				rw->w_where = 0;
		}
E 28
E 8
	}
D 28
	if (src) {
		dlen = ROUNDUP(src->sa_len);
		m_copyback(m, len ,  dlen, (caddr_t)src);
		len += dlen;
D 8
		rtm->rtm_count++;
E 8
I 8
		rtm->rtm_addrs |= RTA_AUTHOR;
E 28
I 28
	if (cp) {
		register struct rt_msghdr *rtm = (struct rt_msghdr *)cp0;

		rtm->rtm_version = RTM_VERSION;
		rtm->rtm_type = type;
		rtm->rtm_msglen = len;
E 28
E 8
	}
D 28
	if (m->m_pkthdr.len != len) {
		m_freem(m);
E 28
I 28
	return (len);
}

/*
 * This routine is called to generate a message from the routing
 * socket indicating that a redirect has occured, a routing lookup
 * has failed, or that a protocol has detected timeouts to a particular
 * destination.
 */
I 42
void
E 42
rt_missmsg(type, rtinfo, flags, error)
	int type, flags, error;
	register struct rt_addrinfo *rtinfo;
{
	register struct rt_msghdr *rtm;
	register struct mbuf *m;
I 49
	register int i;
E 49
D 45
	register int i;
E 45
	struct sockaddr *sa = rtinfo->rti_info[RTAX_DST];

	if (route_cb.any_count == 0)
E 28
		return;
D 28
	}
E 28
I 28
	m = rt_msg1(type, rtinfo);
	if (m == 0)
		return;
	rtm = mtod(m, struct rt_msghdr *);
	rtm->rtm_flags = RTF_DONE | flags;
E 28
I 2
	rtm->rtm_errno = error;
E 2
D 28
	rtm->rtm_msglen = len;
	route_proto.sp_protocol = dst->sa_family;
E 28
I 28
	rtm->rtm_addrs = rtinfo->rti_addrs;
	route_proto.sp_protocol = sa ? sa->sa_family : 0;
E 28
	raw_input(m, &route_proto, &route_src, &route_dst);
I 7
}

I 28
/*
 * This routine is called to generate a message from the routing
 * socket indicating that the status of a network interface has changed.
 */
I 42
void
E 42
rt_ifmsg(ifp)
	register struct ifnet *ifp;
{
	register struct if_msghdr *ifm;
	struct mbuf *m;
	struct rt_addrinfo info;

	if (route_cb.any_count == 0)
		return;
	bzero((caddr_t)&info, sizeof(info));
	m = rt_msg1(RTM_IFINFO, &info);
	if (m == 0)
		return;
	ifm = mtod(m, struct if_msghdr *);
	ifm->ifm_index = ifp->if_index;
	ifm->ifm_flags = ifp->if_flags;
	ifm->ifm_data = ifp->if_data;
	ifm->ifm_addrs = 0;
	route_proto.sp_protocol = 0;
	raw_input(m, &route_proto, &route_src, &route_dst);
}

/*
 * This is called to generate messages from the routing socket
 * indicating a network interface has had addresses associated with it.
 * if we ever reverse the logic and replace messages TO the routing
 * socket indicate a request to configure interfaces, then it will
 * be unnecessary as the routing socket will automatically generate
 * copies of it.
 */
I 42
void
E 42
rt_newaddrmsg(cmd, ifa, error, rt)
	int cmd, error;
	register struct ifaddr *ifa;
	register struct rtentry *rt;
{
	struct rt_addrinfo info;
	struct sockaddr *sa;
	int pass;
	struct mbuf *m;
	struct ifnet *ifp = ifa->ifa_ifp;

	if (route_cb.any_count == 0)
		return;
	for (pass = 1; pass < 3; pass++) {
		bzero((caddr_t)&info, sizeof(info));
		if ((cmd == RTM_ADD && pass == 1) ||
		    (cmd == RTM_DELETE && pass == 2)) {
			register struct ifa_msghdr *ifam;
			int ncmd = cmd == RTM_ADD ? RTM_NEWADDR : RTM_DELADDR;

			ifaaddr = sa = ifa->ifa_addr;
			ifpaddr = ifp->if_addrlist->ifa_addr;
			netmask = ifa->ifa_netmask;
			brdaddr = ifa->ifa_dstaddr;
			if ((m = rt_msg1(ncmd, &info)) == NULL)
				continue;
			ifam = mtod(m, struct ifa_msghdr *);
			ifam->ifam_index = ifp->if_index;
			ifam->ifam_metric = ifa->ifa_metric;
I 32
			ifam->ifam_flags = ifa->ifa_flags;
E 32
			ifam->ifam_addrs = info.rti_addrs;
		}
		if ((cmd == RTM_ADD && pass == 2) ||
		    (cmd == RTM_DELETE && pass == 1)) {
			register struct rt_msghdr *rtm;
			
			if (rt == 0)
				continue;
			netmask = rt_mask(rt);
			dst = sa = rt_key(rt);
			gate = rt->rt_gateway;
			if ((m = rt_msg1(cmd, &info)) == NULL)
				continue;
			rtm = mtod(m, struct rt_msghdr *);
			rtm->rtm_index = ifp->if_index;
			rtm->rtm_flags |= rt->rt_flags;
			rtm->rtm_errno = error;
			rtm->rtm_addrs = info.rti_addrs;
		}
		route_proto.sp_protocol = sa ? sa->sa_family : 0;
		raw_input(m, &route_proto, &route_src, &route_dst);
	}
}

E 28
D 35
#include "kinfo.h"
E 35
I 35
D 36
#include <sys/kinfo.h>
E 36
E 35
D 8
static long zero_l = 0;
E 8
D 28
struct walkarg {
	int	w_op, w_arg;
	int	w_given, w_needed;
	caddr_t	w_where;
	struct	{
		struct rt_msghdr m_rtm;
		char	m_sabuf[128];
	} w_m;
#define w_rtm w_m.m_rtm
};
E 28
/*
D 36
 * This is used in dumping the kernel table via getkinfo().
E 36
I 36
 * This is used in dumping the kernel table via sysctl().
E 36
 */
I 42
int
E 42
D 36
rt_dumpentry(rn, w)
E 36
I 36
sysctl_dumpentry(rn, w)
E 36
	struct radix_node *rn;
	register struct walkarg *w;
{
I 49
	register struct sockaddr *sa;
E 49
D 45
	register struct sockaddr *sa;
E 45
D 26
	int n, error;

D 9
    for (; rn && !(rn->rn_flags & RNF_ROOT); rn = rn->rn_dupedkey) {
E 9
I 9
    for (; rn; rn = rn->rn_dupedkey) {
E 9
	int count = 0, size = sizeof(w->w_rtm);
E 26
I 26
D 28
	int n, error, size = sizeof(w->w_rtm);
E 28
E 26
	register struct rtentry *rt = (struct rtentry *)rn;
I 28
D 45
	int n, error = 0, size;
E 45
I 45
D 49
	int error = 0, size;
E 49
I 49
	int n, error = 0, size;
E 49
E 45
	struct rt_addrinfo info;
E 28

I 9
D 26
	if (rn->rn_flags & RNF_ROOT)
		continue;
E 26
E 9
D 36
	if (w->w_op == KINFO_RT_FLAGS && !(rt->rt_flags & w->w_arg))
E 36
I 36
	if (w->w_op == NET_RT_FLAGS && !(rt->rt_flags & w->w_arg))
E 36
D 26
		continue;
E 26
I 26
		return 0;
E 26
I 8
D 28
#define next(a, l) {size += (l); w->w_rtm.rtm_addrs |= (a); }
	w->w_rtm.rtm_addrs = 0;
E 8
	if (sa = rt_key(rt))
D 8
		{size += ROUNDUP(sa->sa_len); count++;}
E 8
I 8
		next(RTA_DST, ROUNDUP(sa->sa_len));
E 8
	if (sa = rt->rt_gateway)
D 8
		{size += ROUNDUP(sa->sa_len); count++;}
	if (sa = rt_mask(rt)) {
		size += sa->sa_len ? ROUNDUP(sa->sa_len) : sizeof(long);
		count++;
	}
E 8
I 8
		next(RTA_GATEWAY, ROUNDUP(sa->sa_len));
	if (sa = rt_mask(rt))
D 17
		next(RTA_NETMASK,
			sa->sa_len ? ROUNDUP(sa->sa_len) : sizeof(long));
E 17
I 17
		next(RTA_NETMASK, ROUNDUP(sa->sa_len));
E 17
E 8
	if (sa = rt->rt_genmask)
D 8
		{size += ROUNDUP(sa->sa_len); count++;}
E 8
I 8
		next(RTA_GENMASK, ROUNDUP(sa->sa_len));
E 8
	w->w_needed += size;
	if (w->w_where == NULL || w->w_needed > 0)
D 26
		continue;
E 26
I 26
		return 0;
E 26
	w->w_rtm.rtm_msglen = size;
D 8
	w->w_rtm.rtm_count = count;
E 8
	w->w_rtm.rtm_flags = rt->rt_flags;
D 8

E 8
I 8
	w->w_rtm.rtm_use = rt->rt_use;
	w->w_rtm.rtm_rmx = rt->rt_rmx;
	w->w_rtm.rtm_index = rt->rt_ifp->if_index;
#undef next
#define next(l) {n = (l); Bcopy(sa, cp, n); cp += n;}
E 8
	if (size <= sizeof(w->w_m)) {
		register caddr_t cp = (caddr_t)(w->w_m.m_sabuf);
D 8
#define next(a, b) {n = (b); Bcopy((a), cp, n); cp += n;}
E 8
		if (sa = rt_key(rt))
D 8
			next(sa, ROUNDUP(sa->sa_len));
E 8
I 8
			next(ROUNDUP(sa->sa_len));
E 8
		if (sa = rt->rt_gateway)
D 8
			next(sa, ROUNDUP(sa->sa_len));
		if (sa = rt_mask(rt)) {
			w->w_rtm.rtm_flags |= RTF_MASK;
			if (sa->sa_len)
				{next(sa, ROUNDUP(sa->sa_len));}
			else
				next((&zero_l), sizeof(zero_l));
		}
E 8
I 8
			next(ROUNDUP(sa->sa_len));
		if (sa = rt_mask(rt))
D 17
			next(sa->sa_len ? ROUNDUP(sa->sa_len) : sizeof(long));
E 17
I 17
			next(ROUNDUP(sa->sa_len));
E 17
E 8
		if (sa = rt->rt_genmask)
D 8
			next(sa, ROUNDUP(sa->sa_len));
E 8
I 8
			next(ROUNDUP(sa->sa_len));
E 8
#undef next
D 8
#define next(a, b) {n = (b); \
    if (error = copyout((caddr_t)(a), w->w_where, n)) return (error); \
    w->w_where += n; }
E 8
I 8
#define next(s, l) {n = (l); \
    if (error = copyout((caddr_t)(s), w->w_where, n)) return (error); \
    w->w_where += n;}
E 28
I 28
	bzero((caddr_t)&info, sizeof(info));
	dst = rt_key(rt);
	gate = rt->rt_gateway;
	netmask = rt_mask(rt);
	genmask = rt->rt_genmask;
I 50
	if (rt->rt_ifp) {
		ifpaddr = rt->rt_ifp->if_addrlist->ifa_addr;
		ifaaddr = rt->rt_ifa->ifa_addr;
		if (rt->rt_ifp->if_flags & IFF_POINTOPOINT)
			brdaddr = rt->rt_ifa->ifa_dstaddr;
	}
E 50
	size = rt_msg2(RTM_GET, &info, 0, w);
	if (w->w_where && w->w_tmem) {
		register struct rt_msghdr *rtm = (struct rt_msghdr *)w->w_tmem;
E 28
E 8

D 28
		next(&w->w_m, size); /* Copy rtmsg and sockaddrs back */
D 26
		continue;
E 26
I 26
		return 0;
E 28
I 28
		rtm->rtm_flags = rt->rt_flags;
		rtm->rtm_use = rt->rt_use;
		rtm->rtm_rmx = rt->rt_rmx;
		rtm->rtm_index = rt->rt_ifp->if_index;
		rtm->rtm_errno = rtm->rtm_pid = rtm->rtm_seq = 0;
		rtm->rtm_addrs = info.rti_addrs;
		if (error = copyout((caddr_t)rtm, w->w_where, size))
			w->w_where = NULL;
		else
			w->w_where += size;
E 28
E 26
	}
D 28
	next(&w->w_rtm, sizeof(w->w_rtm));
	if (sa = rt_key(rt))
		next(sa, ROUNDUP(sa->sa_len));
	if (sa = rt->rt_gateway)
		next(sa, ROUNDUP(sa->sa_len));
D 8
	if (sa = rt_mask(rt)) {
		if (sa->sa_len)
			{next(sa, ROUNDUP(sa->sa_len));}
		else
			next(&zero_l, sizeof(zero_l));
	}
E 8
I 8
	if (sa = rt_mask(rt))
D 17
		next(sa, sa->sa_len ? ROUNDUP(sa->sa_len) : sizeof(long));
E 17
I 17
		next(sa, ROUNDUP(sa->sa_len));
E 17
E 8
	if (sa = rt->rt_genmask)
		next(sa, ROUNDUP(sa->sa_len));
E 28
I 28
	return (error);
}

I 42
int
E 42
D 36
kinfo_iflist(af, w)
E 36
I 36
sysctl_iflist(af, w)
E 36
	int	af;
	register struct	walkarg *w;
{
	register struct ifnet *ifp;
	register struct ifaddr *ifa;
	struct	rt_addrinfo info;
I 49
	struct	sockaddr *sa;
E 49
D 45
	struct	sockaddr *sa;
E 45
	int	len, error = 0;

	bzero((caddr_t)&info, sizeof(info));
	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
I 29
		if (w->w_arg && w->w_arg != ifp->if_index)
			continue;
E 29
		ifa = ifp->if_addrlist;
		ifpaddr = ifa->ifa_addr;
		len = rt_msg2(RTM_IFINFO, &info, (caddr_t)0, w);
		ifpaddr = 0;
		if (w->w_where && w->w_tmem) {
			register struct if_msghdr *ifm;

			ifm = (struct if_msghdr *)w->w_tmem;
			ifm->ifm_index = ifp->if_index;
			ifm->ifm_flags = ifp->if_flags;
			ifm->ifm_data = ifp->if_data;
			ifm->ifm_addrs = info.rti_addrs;
			if (error = copyout((caddr_t)ifm, w->w_where, len))
				return (error);
			w->w_where += len;
		}
		while (ifa = ifa->ifa_next) {
I 29
			if (af && af != ifa->ifa_addr->sa_family)
				continue;
E 29
			ifaaddr = ifa->ifa_addr;
			netmask = ifa->ifa_netmask;
			brdaddr = ifa->ifa_dstaddr;
			len = rt_msg2(RTM_NEWADDR, &info, 0, w);
			if (w->w_where && w->w_tmem) {
				register struct ifa_msghdr *ifam;

				ifam = (struct ifa_msghdr *)w->w_tmem;
				ifam->ifam_index = ifa->ifa_ifp->if_index;
				ifam->ifam_flags = ifa->ifa_flags;
				ifam->ifam_metric = ifa->ifa_metric;
				ifam->ifam_addrs = info.rti_addrs;
				if (error = copyout(w->w_tmem, w->w_where, len))
					return (error);
				w->w_where += len;
			}
D 29
			ifaaddr = netmask = brdaddr = 0;
E 29
		}
I 29
		ifaaddr = netmask = brdaddr = 0;
E 29
	}
E 28
D 26
    }
E 26
	return (0);
D 28
#undef next
E 28
}

I 42
int
E 42
I 28
D 29

E 29
E 28
D 36
kinfo_rtable(op, where, given, arg, needed)
	int	op, arg;
E 36
I 36
sysctl_rtable(name, namelen, where, given, new, newlen)
	int	*name;
	int	namelen;
E 36
	caddr_t	where;
D 36
	int	*given, *needed;
E 36
I 36
D 38
	int	*given;
E 38
I 38
	size_t	*given;
E 38
	caddr_t	*new;
D 38
	int	newlen;
E 38
I 38
	size_t	newlen;
E 38
E 36
{
	register struct radix_node_head *rnh;
D 24
	int	s, error = 0;
E 24
I 24
D 28
	int	s, error = 0, i;
E 28
I 28
	int	i, s, error = EINVAL;
E 28
E 24
D 36
	u_char  af = ki_af(op);
E 36
I 36
	u_char  af;
E 36
	struct	walkarg w;

I 36
	if (new)
		return (EPERM);
	if (namelen != 3)
		return (EINVAL);
	af = name[0];
E 36
D 28
	op &= 0xffff;
	if (op != KINFO_RT_DUMP && op != KINFO_RT_FLAGS)
		return (EINVAL);

E 28
	Bzero(&w, sizeof(w));
D 36
	if ((w.w_where = where) && given)
		w.w_given = *given;
E 36
I 36
	w.w_where = where;
	w.w_given = *given;
E 36
	w.w_needed = 0 - w.w_given;
D 36
	w.w_arg = arg;
D 29
	w.w_op = op;
E 29
I 29
	w.w_op = op = ki_op(op);
E 36
I 36
	w.w_op = name[1];
	w.w_arg = name[2];
E 36
E 29
D 8
	w.w_rtm.rtm_version = 1;
E 8
I 8
D 28
	w.w_rtm.rtm_version = RTM_VERSION;
E 8
	w.w_rtm.rtm_type = RTM_GET;
E 28

	s = splnet();
D 24
	for (rnh = radix_node_head; rnh; rnh = rnh->rnh_next) {
		if (rnh->rnh_af == 0)
E 24
I 24
D 28
	for (i = 0; i <= AF_MAX; i++) {
		if ((rnh = rt_tables[i]) == 0 || i == 0 || (af && af != i))
E 24
			continue;
D 24
		if (af && af != rnh->rnh_af)
			continue;
		error = rt_walk(rnh->rnh_treetop, rt_dumpentry, &w);
E 24
I 24
		error = rnh->rnh_walk(rnh->rnh_treetop, rt_dumpentry, &w);
E 24
		if (error)
			break;
E 28
I 28
D 36
	switch (op) {
E 36
I 36
	switch (w.w_op) {
E 36

D 36
	case KINFO_RT_DUMP:
	case KINFO_RT_FLAGS:
E 36
I 36
	case NET_RT_DUMP:
	case NET_RT_FLAGS:
E 36
		for (i = 1; i <= AF_MAX; i++)
			if ((rnh = rt_tables[i]) && (af == 0 || af == i) &&
D 40
			    (error = rnh->rnh_walk(rnh->rnh_treetop,
D 36
						  rt_dumpentry, &w)))
E 36
I 36
						  sysctl_dumpentry, &w)))
E 40
I 40
			    (error = rnh->rnh_walktree(rnh,
							sysctl_dumpentry, &w)))
E 40
E 36
				break;
		break;

D 36
	case KINFO_RT_IFLIST:
		error = kinfo_iflist(af, &w);
E 36
I 36
	case NET_RT_IFLIST:
		error = sysctl_iflist(af, &w);
E 36
E 28
	}
I 28
	splx(s);
	if (w.w_tmem)
		free(w.w_tmem, M_RTABLE);
E 28
	w.w_needed += w.w_given;
D 36
	if (where && given)
E 36
I 36
	if (where) {
E 36
		*given = w.w_where - where;
D 36
	else
		w.w_needed = (11 * w.w_needed) / 10;
	*needed = w.w_needed;
E 36
I 36
		if (*given < w.w_needed)
			return (ENOMEM);
	} else {
		*given = (11 * w.w_needed) / 10;
	}
E 36
D 28
	splx(s);
E 28
	return (error);
D 24
}

rt_walk(rn, f, w)
	register struct radix_node *rn;
	register int (*f)();
	struct walkarg *w;
{
	int error;
	for (;;) {
		while (rn->rn_b >= 0)
			rn = rn->rn_l;	/* First time through node, go left */
		if (error = (*f)(rn, w))
			return (error);	/* Process Leaf */
		while (rn->rn_p->rn_r == rn) {	/* if coming back from right */
			rn = rn->rn_p;		/* go back up */
			if (rn->rn_flags & RNF_ROOT)
				return 0;
		}
		rn = rn->rn_p->rn_r;		/* otherwise, go right*/
	}
E 24
E 7
}

/*
 * Definitions of protocols supported in the ROUTE domain.
 */

D 9
int	route_output();
E 9
D 33
int	raw_init(),raw_usrreq(),raw_input(),raw_ctlinput();
E 33
I 33
D 42
int	raw_init(),raw_usrreq(),raw_input(),raw_ctlinput(), route_init();
E 42
E 33
extern	struct domain routedomain;		/* or at least forward */

struct protosw routesw[] = {
{ SOCK_RAW,	&routedomain,	0,		PR_ATOMIC|PR_ADDR,
  raw_input,	route_output,	raw_ctlinput,	0,
  route_usrreq,
D 13
  raw_init,	0,		0,		0,
},
{ 0,		0,		0,		0,
  raw_input,	0,		raw_ctlinput,	0,
  raw_usrreq,
E 13
  raw_init,	0,		0,		0,
I 36
  sysctl_rtable,
E 36
}
};
D 42

int	unp_externalize(), unp_dispose();
E 42

struct domain routedomain =
D 33
    { PF_ROUTE, "route", 0, 0, 0,
E 33
I 33
    { PF_ROUTE, "route", route_init, 0, 0,
E 33
      routesw, &routesw[sizeof(routesw)/sizeof(routesw[0])] };
E 1
