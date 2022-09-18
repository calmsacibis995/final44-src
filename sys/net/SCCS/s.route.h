h39631
s 00010/00001/00236
d D 8.5.1.1 95/02/23 22:19:24 sklower 46 45
c document more trial code for mitre; maybe release it
e
s 00002/00000/00235
d D 8.5 95/02/08 14:40:23 cgd 45 44
c lint
e
s 00001/00001/00234
d D 8.4 95/01/09 17:54:26 cgd 44 42
c 64-bit changes: casts, and ioctl cmds are u_longs
e
s 00006/00000/00235
d D 8.3.1.1 94/12/02 15:49:28 sklower 43 42
c document non-working code sent to mitre
e
s 00001/00001/00234
d D 8.3 94/04/19 07:39:30 bostic 42 41
c spell
e
s 00001/00001/00234
d D 8.2 94/04/19 07:36:44 bostic 41 40
c spell
e
s 00002/00002/00233
d D 8.1 93/06/10 22:45:34 bostic 40 39
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00001/00211
d D 7.19 93/06/04 17:31:39 bostic 39 38
c prototype everything
e
s 00001/00000/00211
d D 7.18 93/03/12 18:01:43 sklower 38 37
c jch requested flag to temporarily discard pkts silently
e
s 00001/00001/00210
d D 7.17 92/10/11 11:49:07 bostic 37 36
c make kernel includes standard
e
s 00036/00024/00175
d D 7.16 92/02/18 15:45:33 sklower 36 35
c rearrange routing message format so that common parts are first;
c consequently up version number; remove old RTHASH cruft; add new sockaddr for
c RTA_{NEW,DEL}ADDR, new convention and structure for calling rt_missmsg
e
s 00002/00000/00197
d D 7.15 91/07/30 17:39:13 sklower 35 34
c add RTF_STATIC for gated; use vector for routing tables per address
c family rather than linked list
e
s 00001/00001/00196
d D 7.14 91/06/18 21:17:38 sklower 34 33
c change to routing layer; reference to route of gateway for routes that use them.
e
s 00004/00000/00193
d D 7.13 91/04/25 19:45:10 sklower 33 32
c reserve a couple of flags for protocol specific use; i.e.
c ISO connectionless services prefered to this class of host.
e
s 00001/00000/00192
d D 7.12 90/07/26 16:33:34 sklower 32 31
c add way to actively reject or consume certain routes
e
s 00001/00011/00191
d D 7.11 90/06/28 21:32:20 bostic 31 30
c new copyright notice
e
s 00002/00000/00200
d D 7.10 90/06/09 17:49:17 sklower 30 29
c minor changes to ease folding ARP, ESIS tables into routing table
e
s 00008/00000/00192
d D 7.9 90/06/08 15:00:39 karels 29 27
c add macros for rtt units
e
s 00003/00000/00192
d R 7.9 90/05/24 19:00:03 sklower 28 27
c define sockopt for quieting things down
e
s 00031/00019/00161
d D 7.8 90/04/05 11:36:55 sklower 27 26
c new version of message format for routing socket.
e
s 00007/00002/00173
d D 7.7 90/03/12 13:40:46 sklower 26 25
c changes to support cloning routes
e
s 00001/00000/00174
d D 7.6 89/04/22 12:10:42 sklower 25 24
c checkpoint at first working tp4 connection; before gnodes
e
s 00083/00001/00091
d D 7.5 88/12/13 13:30:24 sklower 24 23
c checkpoint semi-working version with routing socket
e
s 00010/00005/00082
d D 7.4 88/06/27 18:59:46 bostic 23 22
c install approved copyright notice
e
s 00008/00002/00079
d D 7.3 87/12/30 11:57:42 bostic 22 21
c add Berkeley header
e
s 00001/00000/00080
d D 7.2 87/01/15 15:09:41 karels 21 20
c mark routes modified by redirects
e
s 00001/00001/00079
d D 7.1 86/06/04 23:42:54 mckusick 20 19
c 4.3BSD release version
e
s 00000/00001/00080
d D 6.8 86/03/12 11:28:12 karels 19 18
c rm unused
e
s 00000/00012/00081
d D 6.7 85/12/19 16:20:13 karels 18 17
c rm bbnnet
e
s 00006/00008/00087
d D 6.6 85/09/16 21:22:51 karels 17 15
c mark dynamically created routes; keep incompatibility in its place
e
s 00005/00007/00088
d R 6.6 85/09/16 21:21:27 karels 16 15
c mark dynamically created routes; keep incompatibility in its place
e
s 00014/00001/00081
d D 6.5 85/08/21 15:40:35 walsh 15 14
c need to remember gateway ping information.
e
s 00007/00001/00075
d D 6.4 85/06/08 12:28:30 mckusick 14 13
c Add copyright
e
s 00004/00000/00072
d D 6.3 84/08/29 16:07:08 karels 13 12
c bigger routing hash tables for gateways
e
s 00006/00001/00066
d D 6.2 84/05/30 16:24:56 karels 12 11
c use mask instead of urem for route hashing
e
s 00000/00000/00067
d D 6.1 83/07/29 07:08:58 sam 11 10
c 4.2 distribution
e
s 00018/00009/00049
d D 4.10 83/05/30 18:49:49 sam 10 9
c add wildcard routing and routing statistics; also routing redirects 
c can generate new routing table entries
e
s 00000/00007/00058
d D 4.9 83/05/12 14:59:31 sam 9 8
c no more routetoif (yeah)
e
s 00040/00030/00025
d D 4.8 82/06/12 23:19:56 wnj 8 7
c now the routing code might wokr
e
s 00016/00007/00039
d D 4.7 82/03/31 20:37:05 sam 7 6
c routing tried and working, add logical host stuff
e
s 00005/00003/00041
d D 4.6 82/03/30 19:57:44 sam 6 5
c routing code now operational
e
s 00002/00004/00042
d D 4.5 82/03/30 11:32:59 sam 5 4
c with routing, but not forwarding
e
s 00001/00002/00045
d D 4.4 82/03/29 14:36:02 sam 4 3
c no need for RTF_MUNGE, figured out a better way
e
s 00001/00000/00046
d D 4.3 82/03/29 11:32:58 sam 3 2
c first cut (incomplete) at routing
e
s 00003/00001/00043
d D 4.2 82/03/28 14:23:35 sam 2 1
c convert interfaces to sockaddr's and add hooks for routing
e
s 00044/00000/00000
d D 4.1 82/03/27 22:57:41 sam 1 0
c date and time created 82/03/27 22:57:41 by sam
e
u
U
f b 
f d 8.5
t
T
I 1
D 14
/*	%M%	%I%	%E%	*/
E 14
I 14
/*
D 20
 * Copyright (c) 1980 Regents of the University of California.
E 20
I 20
D 40
 * Copyright (c) 1980, 1986 Regents of the University of California.
E 20
D 22
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
 * All rights reserved.
E 40
I 40
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 40
 *
D 31
 * Redistribution and use in source and binary forms are permitted
D 23
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 23
I 23
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
E 31
I 31
 * %sccs.include.redist.c%
E 31
E 23
E 22
 *
D 15
 *	%W% (Berkeley) %G%
E 15
I 15
D 17
 *	@(#)route.h	6.4 (Berkeley) 6/8/85
E 17
I 17
D 24
 *	%W% (Berkeley) %G%
E 24
I 24
D 26
 *	@(#)route.h	7.4 (Berkeley) 6/27/88
E 26
I 26
 *	%W% (Berkeley) %G%
E 26
E 24
E 17
E 15
 */
E 14

/*
D 7
 * Structure of kernel resident routing
 * data base.  Assumption is user routing
 * daemon maintains this data base based
 * on routing information it gleans from
 * gateway protocols it listens to (e.g. GGP).
E 7
I 7
 * Kernel resident routing tables.
 * 
D 8
 * Each interface makes an entry at boot time so that
 * correspondents directly addressible can be found.
 * User programs can update this data base from information
 * stored in the file system or information gleaned from
 * routing protocol interactions with gateways.
E 8
I 8
D 17
 * The routing tables are initialized at boot time by
 * making entries for all directly connected interfaces.
E 17
I 17
 * The routing tables are initialized when interface addresses
 * are set by making entries for all directly connected interfaces.
E 17
D 10
 * Routing daemons can thereafter update the routing tables.
E 8
E 7
 *
D 7
 * TO ADD:
 *	more statistics -- smooth usage figures
E 7
I 7
 * TODO:
 *	keep statistics
E 10
D 8
 *	smooth usage figures
E 8
E 7
 */
D 8
struct rtentry {
D 5
	u_long	rt_key;			/* lookup key */
E 5
I 5
D 6
	u_long	rt_hash[2];		/* [0] for net, [1] for host */
E 6
I 6
	u_long	rt_hash;		/* for net or for host */
E 6
E 5
	struct	sockaddr rt_dst;	/* match value */
	struct	sockaddr rt_gateway;	/* who to forward to */
	short	rt_flags;		/* see below */
	short	rt_refcnt;		/* # held references */
	u_long	rt_use;			/* raw # packets forwarded */
	struct	ifnet *rt_ifp;		/* interface to use */
};
E 8

I 8
/*
 * A route consists of a destination address and a reference
 * to a routing entry.  These are often held by protocols
 * in their control blocks, e.g. inpcb.
 */
E 8
struct route {
	struct	rtentry *ro_rt;
	struct	sockaddr ro_dst;
D 8
	caddr_t	ro_pcb;			/* back pointer? */
E 8
I 8
D 17
#ifdef notdef
	caddr_t	ro_pcb;			/* not used yet */
#endif
E 17
E 8
};
I 8
D 9
#ifdef KERNEL
/*
 * The route ``routetoif'' is a special atom passed to the output routines
 * to implement the SO_DONTROUTE option.
 */
struct	route routetoif;
#endif
E 9
E 8

/*
I 27
 * These numbers are used by reliable protocols for determining
 * retransmission behavior and are included in the routing structure.
 */
struct rt_metrics {
	u_long	rmx_locks;	/* Kernel must leave these values alone */
	u_long	rmx_mtu;	/* MTU for this path */
	u_long	rmx_hopcount;	/* max hops expected */
	u_long	rmx_expire;	/* lifetime for route, e.g. redirect */
	u_long	rmx_recvpipe;	/* inbound delay-bandwith product */
	u_long	rmx_sendpipe;	/* outbound delay-bandwith product */
	u_long	rmx_ssthresh;	/* outbound gateway buffer limit */
	u_long	rmx_rtt;	/* estimated round trip time */
	u_long	rmx_rttvar;	/* estimated rtt variance */
I 36
	u_long	rmx_pksent;	/* packets sent using this route */
E 36
};

/*
I 29
 * rmx_rtt and rmx_rttvar are stored as microseconds;
 * RTTTOPRHZ(rtt) converts to a value suitable for use
 * by a protocol slowtimo counter.
 */
#define	RTM_RTTUNIT	1000000	/* units for rtt, rttvar, as units per sec */
#define	RTTTOPRHZ(r)	((r) / (RTM_RTTUNIT / PR_SLOWHZ))

/*
E 29
E 27
D 8
 * Flags and host/network status.
E 8
I 8
 * We distinguish between routes to hosts and routes to networks,
 * preferring the former if available.  For each route we infer
 * the interface to use from the gateway address supplied when
 * the route was entered.  Routes that forward packets through
 * gateways are marked so that the output routines know to address the
 * gateway rather than the ultimate destination.
E 8
 */
I 33
#ifndef RNF_NORMAL
E 33
I 24
D 37
#include "radix.h"
E 37
I 37
#include <net/radix.h>
E 37
I 33
#endif
E 33
E 24
I 8
struct rtentry {
I 24
	struct	radix_node rt_nodes[2];	/* tree glue, and other values */
#define	rt_key(r)	((struct sockaddr *)((r)->rt_nodes->rn_key))
#define	rt_mask(r)	((struct sockaddr *)((r)->rt_nodes->rn_mask))
	struct	sockaddr *rt_gateway;	/* value */
	short	rt_flags;		/* up/down?, host/net */
	short	rt_refcnt;		/* # held references */
	u_long	rt_use;			/* raw # packets forwarded */
	struct	ifnet *rt_ifp;		/* the answer: interface to use */
I 25
	struct	ifaddr *rt_ifa;		/* the answer: interface to use */
I 26
	struct	sockaddr *rt_genmask;	/* for generation of cloned routes */
	caddr_t	rt_llinfo;		/* pointer to link level info cache */
I 27
	struct	rt_metrics rt_rmx;	/* metrics used by rx'ing protocols */
I 30
D 34
	short	rt_idle;		/* easy to tell llayer still live */
E 34
I 34
	struct	rtentry *rt_gwroute;	/* implied entry for gatewayed routes */
E 34
E 30
E 27
E 26
E 25
};

/*
 * Following structure necessary for 4.3 compatibility;
 * We should eventually move it to a compat file.
 */
struct ortentry {
E 24
	u_long	rt_hash;		/* to speed lookups */
	struct	sockaddr rt_dst;	/* key */
	struct	sockaddr rt_gateway;	/* value */
	short	rt_flags;		/* up/down?, host/net */
	short	rt_refcnt;		/* # held references */
	u_long	rt_use;			/* raw # packets forwarded */
	struct	ifnet *rt_ifp;		/* the answer: interface to use */
I 17
D 18
#ifdef BBNNET
E 17
I 15
	union {				/* domain specific info */
D 17
#ifdef INET
E 17
	    struct {
		int in_rt_pc;		/* count of pings not answered */
	    } rt_in_data;

#define	irt_pings	rt_data.rt_in_data.in_rt_pc
#define irt_gdown	rt_data.rt_in_data.in_rt_pc

D 17
#endif
E 17
	    char rt_dummy[32];
	} rt_data;
I 17
#endif
E 18
E 17
E 15
};
D 10
#ifdef KERNEL
#define	RTHASHSIZ	7
struct	mbuf *rthost[RTHASHSIZ];
struct	mbuf *rtnet[RTHASHSIZ];
#endif
E 10

E 8
D 2
#define	RTS_UP		0x1		/* route useable */
E 2
I 2
D 42
#define	RTF_UP		0x1		/* route useable */
E 42
I 42
#define	RTF_UP		0x1		/* route usable */
E 42
E 2
D 4
#define	RTF_MUNGE	0x2		/* munge packet src address */
I 3
#define	RTF_DIRECT	0x4		/* destination is a neighbor */
E 4
I 4
D 8
#define	RTF_DIRECT	0x2		/* destination is a neighbor */
E 8
I 8
#define	RTF_GATEWAY	0x2		/* destination is a gateway */
E 8
I 6
#define	RTF_HOST	0x4		/* host entry (net otherwise) */
I 32
#define	RTF_REJECT	0x8		/* host or net unreachable */
E 32
I 15
D 19
#define RTF_REINSTATE	0x8		/* re-instate route after timeout */
E 19
I 17
#define	RTF_DYNAMIC	0x10		/* created dynamically (by redirect) */
I 21
#define	RTF_MODIFIED	0x20		/* modified dynamically (by redirect) */
I 24
#define RTF_DONE	0x40		/* message confirmed */
#define RTF_MASK	0x80		/* subnet mask present */
I 26
#define RTF_CLONING	0x100		/* generate new routes on use */
#define RTF_XRESOLVE	0x200		/* external daemon resolves name */
I 30
#define RTF_LLINFO	0x400		/* generated by ARP or ESIS */
I 35
#define RTF_STATIC	0x800		/* manually added */
I 38
#define RTF_BLACKHOLE	0x1000		/* just discard pkts (during updates) */
I 46
#define RTF_MULTICAST	0x2000		/* try joining uni/multicast routing */
E 46
E 38
E 35
I 33
#define RTF_PROTO2	0x4000		/* protocol specific routing flag */
#define RTF_PROTO1	0x8000		/* protocol specific routing flag */
E 33
E 30
E 26
E 24
E 21
E 17
E 15
I 7

I 24

E 24
I 10
/*
 * Routing statistics.
 */
struct	rtstat {
	short	rts_badredirect;	/* bogus redirect calls */
	short	rts_dynamic;		/* routes created by redirects */
	short	rts_newgateway;		/* routes modified by redirects */
	short	rts_unreach;		/* lookups which failed */
	short	rts_wildcard;		/* lookups satisfied by a wildcard */
};
I 24
/*
 * Structures for routing messages.
 */
D 27
struct rt_metrics {
	u_long	rtm_mtu;	/* MTU for this path */
	u_long	rtm_hopcount;	/* max hops expected */
	u_long	rtm_expire;	/* lifetime for route, e.g. redirect */
	u_long	rtm_recvpipe;	/* inbound delay-bandwith product */
	u_long	rtm_sendpipe;	/* outbound delay-bandwith product */
	u_long	rtm_ssthresh;	/* outbound gateway buffer limit */
	u_long	rtm_rtt;	/* estimated round trip time */
	u_long	rtm_rttvar;	/* estimated rtt variance */
};
E 24

E 27
I 24
struct rt_msghdr {
	u_short	rtm_msglen;	/* to skip over non-understood messages */
D 41
	u_char	rtm_version;	/* future binary compatability */
E 41
I 41
	u_char	rtm_version;	/* future binary compatibility */
E 41
	u_char	rtm_type;	/* message type */
D 27
	u_char	rtm_count;	/* number of sockaddrs */
E 27
I 27
	u_short	rtm_index;	/* index for associated ifp */
E 27
D 36
	pid_t	rtm_pid;	/* identify sender */
E 36
I 36
	int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
E 36
I 27
	int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
I 36
	pid_t	rtm_pid;	/* identify sender */
E 36
E 27
	int	rtm_seq;	/* for sender to identify action */
	int	rtm_errno;	/* why failed */
D 36
	int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
E 36
D 27
	int	rtm_locks;	/* which values kernel can alter */
	int	rtm_inits;	/* which values we are initializing */
E 27
I 27
	int	rtm_use;	/* from rtentry */
	u_long	rtm_inits;	/* which metrics we are initializing */
	struct	rt_metrics rtm_rmx; /* metrics themselves */
E 27
};

D 27
struct rt_chgmsg {		/* Good for RTM_ADD, RTM_CHANGE, RTM_GET */
	struct	rt_msghdr cm_h;
	struct	rt_metrics cm_m;
};

E 27
D 36
struct route_cb {
	int	ip_count;
	int	ns_count;
	int	iso_count;
	int	any_count;
};
I 27
#define RTM_VERSION	2	/* Up the ante and ignore older versions */
E 36
I 36
#define RTM_VERSION	3	/* Up the ante and ignore older versions */
E 36
E 27

#define RTM_ADD		0x1	/* Add Route */
#define RTM_DELETE	0x2	/* Delete Route */
#define RTM_CHANGE	0x3	/* Change Metrics or flags */
#define RTM_GET		0x4	/* Report Metrics */
#define RTM_LOSING	0x5	/* Kernel Suspects Partitioning */
#define RTM_REDIRECT	0x6	/* Told to use different route */
#define RTM_MISS	0x7	/* Lookup failed on this address */
#define RTM_LOCK	0x8	/* fix specified metrics */
#define RTM_OLDADD	0x9	/* caused by SIOCADDRT */
#define RTM_OLDDEL	0xa	/* caused by SIOCDELRT */
I 26
#define RTM_RESOLVE	0xb	/* req to resolve dst to LL addr */
I 36
#define RTM_NEWADDR	0xc	/* address being added to iface */
#define RTM_DELADDR	0xd	/* address being removed from iface */
#define RTM_IFINFO	0xe	/* iface going up/down etc. */
I 46
#define RTM_ADDPKT	0xf	/* Add Route based on entire packet hdr */
#define RTM_DELPKT	0x10	/* Delete Route base on entire packet hdr */
E 46
I 43
#define RTM_ADDPKT	0xf	/* Add Route based on entire packet hdr */
#define RTM_DELPKT	0x10	/* Delete Route base on entire packet hdr */
E 43
E 36
E 26

#define RTV_MTU		0x1	/* init or lock _mtu */
#define RTV_HOPCOUNT	0x2	/* init or lock _hopcount */
#define RTV_EXPIRE	0x4	/* init or lock _hopcount */
#define RTV_RPIPE	0x8	/* init or lock _recvpipe */
#define RTV_SPIPE	0x10	/* init or lock _sendpipe */
#define RTV_SSTHRESH	0x20	/* init or lock _ssthresh */
#define RTV_RTT		0x40	/* init or lock _rtt */
#define RTV_RTTVAR	0x80	/* init or lock _rttvar */
I 27

I 36
/*
 * Bitmask values for rtm_addr.
 */
E 36
#define RTA_DST		0x1	/* destination sockaddr present */
#define RTA_GATEWAY	0x2	/* gateway sockaddr present */
#define RTA_NETMASK	0x4	/* netmask sockaddr present */
#define RTA_GENMASK	0x8	/* cloning mask sockaddr present */
#define RTA_IFP		0x10	/* interface name sockaddr present */
#define RTA_IFA		0x20	/* interface addr sockaddr present */
#define RTA_AUTHOR	0x40	/* sockaddr for author of redirect */
I 36
#define RTA_BRD		0x80	/* for NEWADDR, broadcast or p-p dest addr */
E 36
E 27

E 24
D 36
#ifdef KERNEL
I 24
struct route_cb route_cb;
#endif
E 36
I 36
/*
 * Index offsets for sockaddr array for alternate internal encoding.
 */
#define RTAX_DST	0	/* destination sockaddr present */
#define RTAX_GATEWAY	1	/* gateway sockaddr present */
#define RTAX_NETMASK	2	/* netmask sockaddr present */
#define RTAX_GENMASK	3	/* cloning mask sockaddr present */
#define RTAX_IFP	4	/* interface name sockaddr present */
#define RTAX_IFA	5	/* interface addr sockaddr present */
#define RTAX_AUTHOR	6	/* sockaddr for author of redirect */
#define RTAX_BRD	7	/* for NEWADDR, broadcast or p-p dest addr */
#define RTAX_MAX	8	/* size of array to allocate */
E 36

I 36
struct rt_addrinfo {
	int	rti_addrs;
	struct	sockaddr *rti_info[RTAX_MAX];
I 46
	int	rti_flags;
	struct	ifaddr *rti_ifa;
	struct	ifnet *rti_ifp;
	struct	rt_msghdr *rti_rtm;
	caddr_t rti_pkthdr;
E 46
I 43
	int	rti_flags;
	struct	ifaddr *rti_ifa;
	struct	ifnet *rti_ifp;
	struct	rt_msghdr *rti_rtm;
E 43
};

struct route_cb {
	int	ip_count;
	int	ns_count;
	int	iso_count;
	int	any_count;
};

E 36
#ifdef KERNEL
E 24
E 10
#define	RTFREE(rt) \
D 26
	if ((rt)->rt_refcnt == 1) \
E 26
I 26
	if ((rt)->rt_refcnt <= 1) \
E 26
		rtfree(rt); \
	else \
		(rt)->rt_refcnt--;
I 10

I 13
D 36
#ifdef	GATEWAY
#define	RTHASHSIZ	64
#else
E 13
D 12
#define	RTHASHSIZ	7
E 12
I 12
#define	RTHASHSIZ	8
I 13
#endif
E 13
#if	(RTHASHSIZ & (RTHASHSIZ - 1)) == 0
#define RTHASHMOD(h)	((h) & (RTHASHSIZ - 1))
#else
#define RTHASHMOD(h)	((h) % RTHASHSIZ)
#endif
E 12
struct	mbuf *rthost[RTHASHSIZ];
struct	mbuf *rtnet[RTHASHSIZ];
E 36
I 36
struct	route_cb route_cb;
E 36
struct	rtstat	rtstat;
I 24
D 39
struct	rtentry *rtalloc1();
E 39
I 35
struct	radix_node_head *rt_tables[AF_MAX+1];
I 39

I 45
D 46
struct socket;
E 46
I 46
struct	socket;
E 46

E 45
void	 route_init __P((void));
int	 route_output __P((struct mbuf *, struct socket *));
int	 route_usrreq __P((struct socket *,
	    int, struct mbuf *, struct mbuf *, struct mbuf *));
void	 rt_ifmsg __P((struct ifnet *));
void	 rt_maskedcopy __P((struct sockaddr *,
	    struct sockaddr *, struct sockaddr *));
void	 rt_missmsg __P((int, struct rt_addrinfo *, int, int));
void	 rt_newaddrmsg __P((int, struct ifaddr *, int, struct rtentry *));
int	 rt_setgate __P((struct rtentry *,
	    struct sockaddr *, struct sockaddr *));
void	 rt_setmetrics __P((u_long, struct rt_metrics *, struct rt_metrics *));
void	 rtable_init __P((void **));
void	 rtalloc __P((struct route *));
struct rtentry *
	 rtalloc1 __P((struct sockaddr *, int));
void	 rtfree __P((struct rtentry *));
int	 rtinit __P((struct ifaddr *, int, int));
D 44
int	 rtioctl __P((int, caddr_t, struct proc *));
E 44
I 44
int	 rtioctl __P((u_long, caddr_t, struct proc *));
E 44
int	 rtredirect __P((struct sockaddr *, struct sockaddr *,
	    struct sockaddr *, int, struct sockaddr *, struct rtentry **));
int	 rtrequest __P((int, struct sockaddr *,
	    struct sockaddr *, struct sockaddr *, int, struct rtentry **));
I 46
int	 rtrequest1 __P((int, struct rt_addrinfo *, struct rtentry **));
E 46
E 39
E 35
E 24
#endif
E 10
E 7
E 6
E 4
E 3
D 8

#ifdef KERNEL
/*
 * Lookup are hashed by a key.  Each hash bucket
 * consists of a linked list of mbuf's
 * containing routing entries.  Dead entries are
 * reclaimed along with mbufs.
 */
D 6
#define	RTHASHSIZ	16
D 5
struct mbuf *routehash[RTHASHSIZ];
I 2

struct	rtentry *reroute();
E 5
I 5
struct	mbuf *routehash[RTHASHSIZ];
E 6
I 6
#define	RTHASHSIZ	7
struct	mbuf *rthost[RTHASHSIZ];
struct	mbuf *rtnet[RTHASHSIZ];
E 6
E 5
E 2
#endif
E 8
E 1
