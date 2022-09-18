h33554
s 00010/00010/00479
d D 8.2 95/04/28 11:17:22 bostic 34 33
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00487
d D 8.1 93/06/05 11:14:16 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00006/00476
d D 5.23 93/04/01 14:15:37 mckusick 32 31
c convert kinfo to sysctl
e
s 00001/00001/00481
d D 5.22 92/08/14 12:55:40 sklower 31 30
c ifm_flags is a signed short and IFF_MULTICAST gets propagated ruinning
c private flags
e
s 00006/00006/00476
d D 5.21 92/02/20 10:51:43 sklower 30 29
c use per-address metrics
e
s 00112/00090/00370
d D 5.20 92/02/19 17:03:04 sklower 29 28
c use kinfo to survey interface list, and use routing socket instead of
c old ioctls
e
s 00001/00000/00459
d D 5.19 91/02/28 18:08:03 bostic 28 27
c ANSI
e
s 00001/00011/00458
d D 5.18 90/06/01 16:29:49 bostic 27 26
c new copyright notice
e
s 00012/00003/00457
d D 5.17 89/08/21 13:29:16 sklower 26 25
c skip over ISO interfaces
e
s 00002/00001/00458
d D 5.16 89/04/02 14:47:21 bostic 25 24
c add pathnames.h
e
s 00041/00020/00418
d D 5.15 89/02/18 11:28:43 karels 24 23
c working with dynamic updates, auto-loading timer; tracing additions and fixes
e
s 00010/00005/00428
d D 5.14 88/06/18 13:56:36 bostic 23 22
c install approved copyright notice
e
s 00004/00002/00429
d D 5.13 88/06/06 16:16:29 karels 22 21
c missed a few: make default, local-loop routes have metric 1,
c as not incremented when sent; check for 0 on input (can't be right)
e
s 00020/00004/00411
d D 5.12 88/05/31 12:06:55 karels 21 20
c allow multiple pt-pt links with same source address;
c mark loopback IFF_PASSIVE; finish perspective change
e
s 00009/00003/00406
d D 5.11 88/02/16 18:50:57 bostic 20 19
c add Berkeley specific headers
e
s 00001/00001/00408
d D 5.10 87/12/12 17:55:31 karels 19 18
c don't bother to ping loopback
e
s 00070/00018/00339
d D 5.9 87/05/28 11:26:12 karels 18 17
c rework interface metrics to invert perspective; other misc. fixes
e
s 00001/00001/00356
d D 5.8 87/04/02 13:06:29 karels 17 16
c finish up interface metric code: store metric from our perspective,
c plus increment for those we send to; delete route from kernel when unreachable,
c but keep in tables to advertise deletion
e
s 00012/00012/00345
d D 5.7 86/06/03 18:31:53 karels 16 15
c delicately balanced on the point of a pin...
e
s 00004/00003/00353
d D 5.6 86/06/03 16:32:35 karels 15 14
c try again; can't block subnet 0 with internal "network" route
e
s 00004/00003/00352
d D 5.5 86/05/30 13:56:27 karels 14 13
c don't send net route to subnet gw's unless on subnet 0;
c a few checks for imposters; bug fix in "external" route configuration;
c rm loopback net defn.
e
s 00034/00003/00321
d D 5.4 86/04/20 23:34:25 karels 13 12
c changes to allow subnets to remain local, propogate net route
c where subnets don't go, and allow external routes from /etc/gateways
c to block routed from installing routes from elsewhere
e
s 00007/00004/00317
d D 5.3 86/02/07 10:05:01 karels 12 11
c 
e
s 00008/00000/00313
d D 5.2 85/11/20 14:37:50 karels 11 10
c want to act as supplier if we have only a single point-point link;
c can't run timer on any interfaces if not a supplier
e
s 00007/00001/00306
d D 5.1 85/06/04 16:37:05 dist 10 9
c Add copyright
e
s 00084/00074/00223
d D 4.9 85/06/03 09:49:43 karels 9 8
c careful with routes to interfaces; don't accidentally delete
c with addroutetoif, if route exists but we think it changes
e
s 00005/00003/00292
d D 4.8 85/02/25 13:44:54 karels 8 7
c careful about deleting route to interface in addrouteforif
e
s 00003/00000/00292
d D 4.7 84/12/20 18:04:24 karels 7 6
c syslog for interface transitions; broadcast all unreachable before exit
e
s 00001/00001/00291
d D 4.6 84/05/16 17:15:52 karels 6 5
c logic error
e
s 00034/00005/00258
d D 4.5 84/04/10 21:43:56 karels 5 4
c subnet routing; don't copy routes from the gateways files everywhere
e
s 00001/00001/00262
d D 4.4 83/05/25 17:51:04 sam 4 3
c protocol change; byte swap those fields which need it;  also add 
c a version stamp to allow future changes
e
s 00008/00006/00255
d D 4.3 83/03/10 19:13:28 sam 3 2
c from shannon
e
s 00056/00021/00205
d D 4.2 83/01/11 14:38:29 sam 2 1
c 4.1c conversion contortions
e
s 00226/00000/00000
d D 4.1 82/11/02 22:28:07 sam 1 0
c date and time created 82/11/02 22:28:07 by sam
e
u
U
t
T
I 10
/*
D 21
 * Copyright (c) 1983 Regents of the University of California.
E 21
I 21
D 33
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 21
D 20
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
D 27
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
E 27
I 27
 * %sccs.include.redist.c%
E 27
E 23
E 20
 */

E 10
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% %G%";
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
D 10
#endif
E 10
I 10
D 20
#endif not lint
E 20
I 20
#endif /* not lint */
E 20
E 10

/*
 * Routing Table Management Daemon
 */
D 2
#include "router.h"
E 2
I 2
#include "defs.h"
I 5
#include <sys/ioctl.h>
I 29
D 32
#include <sys/kinfo.h>
E 32
I 32
#include <sys/sysctl.h>
E 32
E 29
E 5
E 2
#include <net/if.h>
I 29
#include <net/if_dl.h>
E 29
D 13
#include <nlist.h>
E 13
I 7
#include <syslog.h>
I 28
#include <stdlib.h>
E 28
I 25
#include "pathnames.h"
E 25
E 7

struct	interface *ifnet;
I 24
struct	interface **ifnext = &ifnet;
E 24
D 9
int	kmem = -1;
E 9
int	lookforinterfaces = 1;
D 13
int	performnlist = 1;
E 13
int	externalinterfaces = 0;		/* # of remote and local interfaces */
I 18
int	foundloopback;			/* valid flag for loopaddr */
struct	sockaddr loopaddr;		/* our address on loopback */
E 18
I 5
D 9
int	gateway = 0;		/* 1 if we are a gateway to parts beyond */
E 9
E 5

I 29

void
quit(s)
	char *s;
{
	extern int errno;
	int sverrno = errno;

	(void) fprintf(stderr, "route: ");
	if (s)
		(void) fprintf(stderr, "%s: ", s);
	(void) fprintf(stderr, "%s\n", strerror(sverrno));
	exit(1);
	/* NOTREACHED */
}

struct rt_addrinfo info;
/* Sleazy use of local variables throughout file, warning!!!! */
#define netmask	info.rti_info[RTAX_NETMASK]
#define ifaaddr	info.rti_info[RTAX_IFA]
#define brdaddr	info.rti_info[RTAX_BRD]

#define ROUNDUP(a) \
	((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
#define ADVANCE(x, n) (x += ROUNDUP((n)->sa_len))

void
rt_xaddrs(cp, cplim, rtinfo)
	register caddr_t cp, cplim;
	register struct rt_addrinfo *rtinfo;
{
	register struct sockaddr *sa;
	register int i;

D 34
	bzero(rtinfo->rti_info, sizeof(rtinfo->rti_info));
E 34
I 34
	memset(rtinfo->rti_info, 0, sizeof(rtinfo->rti_info));
E 34
	for (i = 0; (i < RTAX_MAX) && (cp < cplim); i++) {
		if ((rtinfo->rti_addrs & (1 << i)) == 0)
			continue;
		rtinfo->rti_info[i] = sa = (struct sockaddr *)cp;
		ADVANCE(cp, sa);
	}
}

E 29
D 9
struct nlist nl[] = {
#define	N_IFNET		0
	{ "_ifnet" },
D 2
	0,
E 2
I 2
	{ "" },
E 2
};

E 9
/*
D 9
 * Probe the kernel through /dev/kmem to find the network
 * interfaces which have configured themselves.  If the
 * interface is present but not yet up (for example an
E 9
I 9
 * Find the network interfaces which have configured themselves.
 * If the interface is present but not yet up (for example an
E 9
 * ARPANET IMP), set the lookforinterfaces flag so we'll
 * come back later and look again.
 */
ifinit()
{
D 9
	struct interface *ifp;
	struct ifnet ifs, *next;
	char name[32], *cp, *index();
E 9
I 9
	struct interface ifs, *ifp;
D 26
	int s, n;
	char buf[BUFSIZ];
E 26
I 26
D 29
	int s;
	char buf[BUFSIZ], *cp, *cplim;
E 26
        struct ifconf ifc;
        struct ifreq ifreq, *ifr;
E 29
I 29
D 32
	int needed, rlen, no_ipaddr = 0, flags = 0;
E 32
I 32
	size_t needed;
	int mib[6], no_ipaddr = 0, flags = 0;
E 32
	char *buf, *cplim, *cp;
	register struct if_msghdr *ifm;
	register struct ifa_msghdr *ifam;
	struct sockaddr_dl *sdl;
E 29
        struct sockaddr_in *sin;
	u_long i;
E 9

D 9
	if (performnlist) {
		nlist("/vmunix", nl);
		if (nl[N_IFNET].n_value == 0) {
			printf("ifnet: not in namelist\n");
			goto bad;
		}
		performnlist = 0;
I 5
D 6
		if (gateway)
E 6
I 6
		if (gateway > 0)
E 6
			rtdefault();
E 9
I 9
D 29
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		syslog(LOG_ERR, "socket: %m");
D 24
		exit(1);
E 24
I 24
		close(s);
                return;
E 24
E 9
E 5
	}
D 9
	if (kmem < 0) {
		kmem = open("/dev/kmem", 0);
		if (kmem < 0) {
			perror("/dev/kmem");
			goto bad;
		}
	}
	if (lseek(kmem, (long)nl[N_IFNET].n_value, 0) == -1 ||
	    read(kmem, (char *)&next, sizeof (next)) != sizeof (next)) {
		printf("ifnet: error reading kmem\n");
		goto bad;
	}
E 9
I 9
        ifc.ifc_len = sizeof (buf);
        ifc.ifc_buf = buf;
        if (ioctl(s, SIOCGIFCONF, (char *)&ifc) < 0) {
                syslog(LOG_ERR, "ioctl (get interface configuration)");
		close(s);
D 24
                return (0);
E 24
I 24
                return;
E 24
        }
        ifr = ifc.ifc_req;
E 29
I 29
D 32
	if ((needed = getkerninfo(KINFO_RT_IFLIST, 0, 0, 0)) < 0)
		quit("route-getkerninfo-estimate");
E 32
I 32
        mib[0] = CTL_NET;
        mib[1] = PF_ROUTE;
        mib[2] = 0;
        mib[3] = AF_INET;
        mib[4] = NET_RT_IFLIST;
        mib[5] = 0;
        if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0)
                quit("route-sysctl-estimate");
E 32
	if ((buf = malloc(needed)) == NULL)
		quit("malloc");
D 32
	if ((rlen = getkerninfo(KINFO_RT_IFLIST, buf, &needed, 0)) < 0)
E 32
I 32
        if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0)
E 32
		quit("actual retrieval of interface table");
E 29
E 9
	lookforinterfaces = 0;
D 9
	while (next) {
		if (lseek(kmem, (long)next, 0) == -1 ||
		    read(kmem, (char *)&ifs, sizeof (ifs)) != sizeof (ifs)) {
			perror("read");
			goto bad;
		}
		next = ifs.if_next;
		if ((ifs.if_flags & IFF_UP) == 0) {
E 9
I 9
D 26
        for (n = ifc.ifc_len / sizeof (struct ifreq); n > 0; n--, ifr++) {
E 26
I 26
D 29
#ifdef RTM_ADD
#define max(a, b) (a > b ? a : b)
#define size(p)	max((p).sa_len, sizeof(p))
#else
#define size(p) (sizeof (p))
#endif
	cplim = buf + ifc.ifc_len; /*skip over if's with big ifr_addr's */
	for (cp = buf; cp < cplim;
			cp += sizeof (ifr->ifr_name) + size(ifr->ifr_addr)) {
		ifr = (struct ifreq *)cp;
E 26
		bzero((char *)&ifs, sizeof(ifs));
		ifs.int_addr = ifr->ifr_addr;
		ifreq = *ifr;
                if (ioctl(s, SIOCGIFFLAGS, (char *)&ifreq) < 0) {
D 24
                        syslog(LOG_ERR, "ioctl (get interface flags)");
E 24
I 24
                        syslog(LOG_ERR, "%s: ioctl (get interface flags)",
			    ifr->ifr_name);
E 24
                        continue;
                }
		ifs.int_flags = ifreq.ifr_flags | IFF_INTERFACE;
I 12
D 18
		/* no one cares about software loopback interfaces */
		if (ifs.int_flags & IFF_LOOPBACK)
			continue;
E 18
E 12
		if ((ifs.int_flags & IFF_UP) == 0 ||
		    ifr->ifr_addr.sa_family == AF_UNSPEC) {
E 9
			lookforinterfaces = 1;
E 29
I 29
D 32
	cplim = buf + rlen;
E 32
I 32
	cplim = buf + needed;
E 32
	for (cp = buf; cp < cplim; cp += ifm->ifm_msglen) {
		ifm = (struct if_msghdr *)cp;
		if (ifm->ifm_type == RTM_IFINFO) {
D 34
			bzero(&ifs, sizeof(ifs));
E 34
I 34
			memset(&ifs, 0, sizeof(ifs));
E 34
D 31
			ifs.int_flags = flags = ifm->ifm_flags | IFF_INTERFACE;
E 31
I 31
			ifs.int_flags = flags = (0xffff & ifm->ifm_flags) | IFF_INTERFACE;
E 31
			if ((flags & IFF_UP) == 0 || no_ipaddr)
				lookforinterfaces = 1;
			sdl = (struct sockaddr_dl *) (ifm + 1);
			sdl->sdl_data[sdl->sdl_nlen] = 0;
D 30
			/*
			 * Use a minimum metric of one;
			 * treat the interface metric (default 0)
			 * as an increment to the hop count of one.
			 */
			ifs.int_metric = ifm->ifm_data.ifi_metric + 1;
E 30
			no_ipaddr = 1;
E 29
			continue;
		}
I 24
D 29
		/* argh, this'll have to change sometime */
E 29
I 29
		if (ifm->ifm_type != RTM_NEWADDR)
			quit("ifinit: out of sync");
		if ((flags & IFF_UP) == 0)
			continue;
		ifam = (struct ifa_msghdr *)ifm;
		info.rti_addrs = ifam->ifam_addrs;
		rt_xaddrs((char *)(ifam + 1), cp + ifam->ifam_msglen, &info);
		if (ifaaddr == 0) {
			syslog(LOG_ERR, "%s: (get addr)", sdl->sdl_data);
			continue;
		}
		ifs.int_addr = *ifaaddr;
E 29
		if (ifs.int_addr.sa_family != AF_INET)
			continue;
D 29
                if (ifs.int_flags & IFF_POINTOPOINT) {
                        if (ioctl(s, SIOCGIFDSTADDR, (char *)&ifreq) < 0) {
                                syslog(LOG_ERR, "%s: ioctl (get dstaddr)",
				    ifr->ifr_name);
                                continue;
E 29
I 29
		no_ipaddr = 0;
		if (ifs.int_flags & IFF_POINTOPOINT) {
			if (brdaddr == 0) {
				syslog(LOG_ERR, "%s: (get dstaddr)",
					sdl->sdl_data);
				continue;
E 29
			}
D 29
			if (ifr->ifr_addr.sa_family == AF_UNSPEC) {
E 29
I 29
			if (brdaddr->sa_family == AF_UNSPEC) {
E 29
				lookforinterfaces = 1;
				continue;
			}
D 29
			ifs.int_dstaddr = ifreq.ifr_dstaddr;
E 29
I 29
			ifs.int_dstaddr = *brdaddr;
E 29
		}
E 24
D 21
		/* already known to us? */
D 9
		if (if_ifwithaddr(&ifs.if_addr))
E 9
I 9
		if (if_ifwithaddr(&ifs.int_addr))
E 21
I 21
		/*
		 * already known to us?
		 * This allows multiple point-to-point links
		 * to share a source address (possibly with one
		 * other link), but assumes that there will not be
		 * multiple links with the same destination address.
		 */
		if (ifs.int_flags & IFF_POINTOPOINT) {
			if (if_ifwithdstaddr(&ifs.int_dstaddr))
				continue;
		} else if (if_ifwithaddr(&ifs.int_addr))
E 21
E 9
			continue;
D 24
		/* argh, this'll have to change sometime */
D 9
		if (ifs.if_addr.sa_family != AF_INET)
E 9
I 9
		if (ifs.int_addr.sa_family != AF_INET)
E 9
			continue;
E 24
I 18
		if (ifs.int_flags & IFF_LOOPBACK) {
I 21
			ifs.int_flags |= IFF_PASSIVE;
E 21
			foundloopback = 1;
			loopaddr = ifs.int_addr;
			for (ifp = ifnet; ifp; ifp = ifp->int_next)
			    if (ifp->int_flags & IFF_POINTOPOINT)
				add_ptopt_localrt(ifp);
		}
E 18
I 9
D 24
                if (ifs.int_flags & IFF_POINTOPOINT) {
                        if (ioctl(s, SIOCGIFDSTADDR, (char *)&ifreq) < 0) {
                                syslog(LOG_ERR, "ioctl (get dstaddr)");
                                continue;
			}
			ifs.int_dstaddr = ifreq.ifr_dstaddr;
		}
E 24
D 29
                if (ifs.int_flags & IFF_BROADCAST) {
                        if (ioctl(s, SIOCGIFBRDADDR, (char *)&ifreq) < 0) {
D 24
                                syslog(LOG_ERR, "ioctl (get broadaddr)");
E 24
I 24
                                syslog(LOG_ERR, "%s: ioctl (get broadaddr)",
				    ifr->ifr_name);
E 24
                                continue;
                        }
I 24
#ifndef sun
E 24
			ifs.int_broadaddr = ifreq.ifr_broadaddr;
I 24
#else
			ifs.int_broadaddr = ifreq.ifr_addr;
#endif
E 29
I 29
		if (ifs.int_flags & IFF_BROADCAST) {
			if (brdaddr == 0) {
				syslog(LOG_ERR, "%s: (get broadaddr)",
					sdl->sdl_data);
				continue;
			}
			ifs.int_dstaddr = *brdaddr;
E 29
E 24
		}
I 30
		/*
		 * Use a minimum metric of one;
		 * treat the interface metric (default 0)
		 * as an increment to the hop count of one.
		 */
		ifs.int_metric = ifam->ifam_metric + 1;
E 30
I 12
D 24
		if (ioctl(s, SIOCGIFMETRIC, (char *)&ifreq) < 0)
			syslog(LOG_ERR, "ioctl (get metric)");
		else
E 24
I 24
D 29
#ifdef SIOCGIFMETRIC
		if (ioctl(s, SIOCGIFMETRIC, (char *)&ifreq) < 0) {
			syslog(LOG_ERR, "%s: ioctl (get metric)",
			    ifr->ifr_name);
			ifs.int_metric = 0;
		} else
E 24
			ifs.int_metric = ifreq.ifr_metric;
I 24
#else
		ifs.int_metric = 0;
#endif
E 24
I 21
		/*
		 * Use a minimum metric of one;
		 * treat the interface metric (default 0)
		 * as an increment to the hop count of one.
		 */
		ifs.int_metric++;
E 21
E 12
		if (ioctl(s, SIOCGIFNETMASK, (char *)&ifreq) < 0) {
D 24
			syslog(LOG_ERR, "ioctl (get netmask)");
E 24
I 24
			syslog(LOG_ERR, "%s: ioctl (get netmask)",
			    ifr->ifr_name);
E 24
			continue;
E 29
I 29
		if (netmask == 0) {
				syslog(LOG_ERR, "%s: (get netmask)",
					sdl->sdl_data);
				continue;
E 29
		}
D 29
		sin = (struct sockaddr_in *)&ifreq.ifr_addr;
E 29
I 29
		sin = (struct sockaddr_in *)netmask;
E 29
		ifs.int_subnetmask = ntohl(sin->sin_addr.s_addr);
		sin = (struct sockaddr_in *)&ifs.int_addr;
		i = ntohl(sin->sin_addr.s_addr);
		if (IN_CLASSA(i))
			ifs.int_netmask = IN_CLASSA_NET;
		else if (IN_CLASSB(i))
			ifs.int_netmask = IN_CLASSB_NET;
		else
			ifs.int_netmask = IN_CLASSC_NET;
		ifs.int_net = i & ifs.int_netmask;
		ifs.int_subnet = i & ifs.int_subnetmask;
I 13
		if (ifs.int_subnetmask != ifs.int_netmask)
			ifs.int_flags |= IFF_SUBNET;
E 13
E 9
D 12
		/* no one cares about software loopback interfaces */
D 9
		if (ifs.if_net == LOOPBACKNET)
E 9
I 9
		if (ifs.int_net == LOOPBACKNET)
E 9
			continue;
E 12
D 29
		ifp = (struct interface *)malloc(sizeof (struct interface));
E 29
I 29
		ifp = (struct interface *)
			malloc(sdl->sdl_nlen + 1 + sizeof(ifs));
E 29
		if (ifp == 0) {
			printf("routed: out of memory\n");
I 29
			lookforinterfaces = 1;
E 29
			break;
		}
I 9
		*ifp = ifs;
E 9
		/*
		 * Count the # of directly connected networks
		 * and point to point links which aren't looped
		 * back to ourself.  This is used below to
		 * decide if we should be a routing ``supplier''.
		 */
D 9
		if ((ifs.if_flags & IFF_POINTOPOINT) == 0 ||
		    if_ifwithaddr(&ifs.if_dstaddr) == 0)
E 9
I 9
D 18
		if ((ifs.int_flags & IFF_POINTOPOINT) == 0 ||
		    if_ifwithaddr(&ifs.int_dstaddr) == 0)
E 18
I 18
		if ((ifs.int_flags & IFF_LOOPBACK) == 0 &&
		    ((ifs.int_flags & IFF_POINTOPOINT) == 0 ||
		    if_ifwithaddr(&ifs.int_dstaddr) == 0))
E 18
E 9
			externalinterfaces++;
I 11
		/*
		 * If we have a point-to-point link, we want to act
		 * as a supplier even if it's our only interface,
		 * as that's the only way our peer on the other end
		 * can tell that the link is up.
		 */
		if ((ifs.int_flags & IFF_POINTOPOINT) && supplier < 0)
			supplier = 1;
E 11
I 5
D 9
		if ((ifs.if_flags & IFF_LOCAL) == 0 && gateway == 0) {
			/*
			 * If we have an interface to a non-local network,
			 * we are a candidate for use as a gateway.
			 */
			gateway = 1;
			rtdefault();
		}
E 5
		lseek(kmem, ifs.if_name, 0);
		read(kmem, name, sizeof (name));
		name[sizeof (name) - 1] = '\0';
		cp = index(name, '\0');
		*cp++ = ifs.if_unit + '0';
		*cp = '\0';
		ifp->int_name = malloc(strlen(name) + 1);
E 9
I 9
D 29
		ifp->int_name = malloc(strlen(ifr->ifr_name) + 1);
E 9
		if (ifp->int_name == 0) {
			fprintf(stderr, "routed: ifinit: out of memory\n");
D 18
			goto bad;		/* ??? */
E 18
I 18
			syslog(LOG_ERR, "routed: ifinit: out of memory\n");
I 24
			close(s);
E 24
			return;
E 18
		}
D 9
		strcpy(ifp->int_name, name);
		ifp->int_addr = ifs.if_addr;
		ifp->int_flags = ifs.if_flags | IFF_INTERFACE;
		/* this works because broadaddr overlaps dstaddr */
		ifp->int_broadaddr = ifs.if_broadaddr;
		ifp->int_net = ifs.if_net;
E 9
I 9
		strcpy(ifp->int_name, ifr->ifr_name);
E 29
I 29
		ifp->int_name = (char *)(ifp + 1);
		strcpy(ifp->int_name, sdl->sdl_data);
E 29
E 9
D 12
		ifp->int_metric = 0;
E 12
D 24
		ifp->int_next = ifnet;
		ifnet = ifp;
E 24
I 24
		*ifnext = ifp;
		ifnext = &ifp->int_next;
E 24
		traceinit(ifp);
		addrouteforif(ifp);
	}
	if (externalinterfaces > 1 && supplier < 0)
		supplier = 1;
I 9
D 29
	close(s);
E 29
I 29
	free(buf);
E 29
E 9
D 18
	return;
bad:
	sleep(60);
D 2
	close(kmem), close(s), close(snoroute);
E 2
I 2
	close(kmem), close(s);
E 2
	execv("/etc/routed", argv0);
	_exit(0177);
E 18
}

I 13
/*
 * Add route for interface if not currently installed.
 * Create route to other end if a point-to-point link,
 * otherwise a route to this (sub)network.
 * INTERNET SPECIFIC.
 */
E 13
addrouteforif(ifp)
D 18
	struct interface *ifp;
E 18
I 18
	register struct interface *ifp;
E 18
{
	struct sockaddr_in net;
	struct sockaddr *dst;
D 22
	int state, metric;
E 22
I 22
	int state;
E 22
D 18
	struct rt_entry *rt;
E 18
I 18
	register struct rt_entry *rt;
E 18

	if (ifp->int_flags & IFF_POINTOPOINT)
		dst = &ifp->int_dstaddr;
	else {
D 34
		bzero((char *)&net, sizeof (net));
E 34
I 34
		memset(&net, 0, sizeof (net));
E 34
		net.sin_family = AF_INET;
D 9
		net.sin_addr = inet_makeaddr(ifp->int_net, INADDR_ANY);
E 9
I 9
		net.sin_addr = inet_makeaddr(ifp->int_subnet, INADDR_ANY);
E 9
		dst = (struct sockaddr *)&net;
	}
I 8
D 9
	rt = rtlookup(dst);
	if (rt && equal(&ifp->int_addr, &rt->rt_router))
E 9
I 9
	rt = rtfind(dst);
D 16
	if (rt && (rt->rt_state & RTS_INTERFACE))
E 16
I 16
	if (rt &&
	    (rt->rt_state & (RTS_INTERFACE | RTS_INTERNAL)) == RTS_INTERFACE)
E 16
E 9
		return;
E 8
I 7
D 9
	if (ifp->int_transitions++ > 0)
		syslog(LOG_ERR, "re-installing interface %s", ifp->int_name);
E 9
E 7
D 8
	rt = rtlookup(dst);
	rtadd(dst, &ifp->int_addr, ifp->int_metric,
		ifp->int_flags & (IFF_INTERFACE|IFF_PASSIVE|IFF_REMOTE));
E 8
	if (rt)
		rtdelete(rt);
I 9
D 16
	if (ifp->int_transitions++ > 0)
		syslog(LOG_ERR, "re-installing interface %s", ifp->int_name);
E 9
I 8
	rtadd(dst, &ifp->int_addr, ifp->int_metric,
D 13
		ifp->int_flags & (IFF_INTERFACE|IFF_PASSIVE|IFF_REMOTE));
E 13
I 13
	    ifp->int_flags & (IFF_INTERFACE|IFF_PASSIVE|IFF_REMOTE|IFF_SUBNET));

E 16
	/*
	 * If interface on subnetted network,
	 * install route to network as well.
	 * This is meant for external viewers.
	 */
	if ((ifp->int_flags & (IFF_SUBNET|IFF_POINTOPOINT)) == IFF_SUBNET) {
I 18
		struct in_addr subnet;

		subnet = net.sin_addr;
E 18
		net.sin_addr = inet_makeaddr(ifp->int_net, INADDR_ANY);
		rt = rtfind(dst);
D 15
		if (rt && (rt->rt_state & RTS_INTERFACE))
E 15
I 15
D 16
		if (rt && (rt->rt_state & (RTS_INTERNAL | RTS_INTERFACE)) ==
		    (RTS_INTERNAL | RTS_INTERFACE))
E 15
			return;
		rtadd(dst, &ifp->int_addr, ifp->int_metric,
D 15
		    (ifp->int_flags & (IFF_INTERFACE|IFF_PASSIVE|IFF_REMOTE) |
D 14
			RTS_INTERNAL));
E 14
I 14
			RTS_INTERNAL | RTS_SUBNET));
E 15
I 15
		    ((ifp->int_flags & (IFF_INTERFACE|IFF_REMOTE)) |
			RTS_PASSIVE | RTS_INTERNAL | RTS_SUBNET));
E 16
I 16
		if (rt == 0)
			rtadd(dst, &ifp->int_addr, ifp->int_metric,
			    ((ifp->int_flags & (IFF_INTERFACE|IFF_REMOTE)) |
D 18
				RTS_PASSIVE | RTS_INTERNAL | RTS_SUBNET));
		net.sin_addr = inet_makeaddr(ifp->int_subnet, INADDR_ANY);
E 18
I 18
			    RTS_PASSIVE | RTS_INTERNAL | RTS_SUBNET));
		else if ((rt->rt_state & (RTS_INTERNAL|RTS_SUBNET)) == 
		    (RTS_INTERNAL|RTS_SUBNET) &&
		    ifp->int_metric < rt->rt_metric)
			rtchange(rt, &rt->rt_router, ifp->int_metric);
		net.sin_addr = subnet;
E 18
E 16
E 15
E 14
	}
I 16
	if (ifp->int_transitions++ > 0)
		syslog(LOG_ERR, "re-installing interface %s", ifp->int_name);
D 18
	rtadd(dst, &ifp->int_addr, ifp->int_metric,
	    ifp->int_flags & (IFF_INTERFACE|IFF_PASSIVE|IFF_REMOTE|IFF_SUBNET));
E 18
I 18
	state = ifp->int_flags &
	    (IFF_INTERFACE | IFF_PASSIVE | IFF_REMOTE | IFF_SUBNET);
	if (ifp->int_flags & IFF_POINTOPOINT &&
	    (ntohl(((struct sockaddr_in *)&ifp->int_dstaddr)->sin_addr.s_addr) &
	    ifp->int_netmask) != ifp->int_net)
		state &= ~RTS_SUBNET;
	if (ifp->int_flags & IFF_LOOPBACK)
D 19
		state |= RTS_EXTERNAL;
E 19
I 19
D 21
		state |= RTS_EXTERNAL | RTS_PASSIVE;
E 21
I 21
		state |= RTS_EXTERNAL;
E 21
E 19
	rtadd(dst, &ifp->int_addr, ifp->int_metric, state);
	if (ifp->int_flags & IFF_POINTOPOINT && foundloopback)
		add_ptopt_localrt(ifp);
}
E 18

I 18
/*
 * Add route to local end of point-to-point using loopback.
 * If a route to this network is being sent to neighbors on other nets,
 * mark this route as subnet so we don't have to propagate it too.
 */
add_ptopt_localrt(ifp)
	register struct interface *ifp;
{
	struct rt_entry *rt;
	struct sockaddr *dst;
	struct sockaddr_in net;
	int state;

	state = RTS_INTERFACE | RTS_PASSIVE;

	/* look for route to logical network */
D 34
	bzero((char *)&net, sizeof (net));
E 34
I 34
	memset(&net, 0, sizeof (net));
E 34
	net.sin_family = AF_INET;
	net.sin_addr = inet_makeaddr(ifp->int_net, INADDR_ANY);
	dst = (struct sockaddr *)&net;
	rt = rtfind(dst);
	if (rt && rt->rt_state & RTS_INTERNAL)
		state |= RTS_SUBNET;

	dst = &ifp->int_addr;
	if (rt = rtfind(dst)) {
		if (rt && rt->rt_state & RTS_INTERFACE)
			return;
		rtdelete(rt);
	}
D 22
	rtadd(dst, &loopaddr, 0, state);
E 22
I 22
	rtadd(dst, &loopaddr, 1, state);
E 22
E 18
E 16
E 13
E 8
}

/*
 * As a concession to the ARPANET we read a list of gateways
 * from /etc/gateways and add them to our tables.  This file
 * exists at each ARPANET gateway and indicates a set of ``remote''
 * gateways (i.e. a gateway which we can't immediately determine
 * if it's present or not as we can do for those directly connected
 * at the hardware level).  If a gateway is marked ``passive''
 * in the file, then we assume it doesn't have a routing process
 * of our design and simply assume it's always present.  Those
 * not marked passive are treated as if they were directly
 * connected -- they're added into the interface list so we'll
 * send them routing updates.
I 18
 *
 * PASSIVE ENTRIES AREN'T NEEDED OR USED ON GATEWAYS RUNNING EGP.
E 18
 */
gwkludge()
{
	struct sockaddr_in dst, gate;
	FILE *fp;
	char *type, *dname, *gname, *qual, buf[BUFSIZ];
	struct interface *ifp;
D 14
	int metric;
E 14
I 14
	int metric, n;
E 14
I 5
	struct rt_entry route;
E 5

D 25
	fp = fopen("/etc/gateways", "r");
E 25
I 25
	fp = fopen(_PATH_GATEWAYS, "r");
E 25
	if (fp == NULL)
		return;
	qual = buf;
	dname = buf + 64;
	gname = buf + ((BUFSIZ - 64) / 3);
	type = buf + (((BUFSIZ - 64) * 2) / 3);
D 34
	bzero((char *)&dst, sizeof (dst));
	bzero((char *)&gate, sizeof (gate));
I 5
	bzero((char *)&route, sizeof(route));
E 34
I 34
	memset(&dst, 0, sizeof (dst));
	memset(&gate, 0, sizeof (gate));
	memset(&route, 0, sizeof(route));
E 34
E 5
D 2
	dst.sin_family = gate.sin_family = AF_INET;
E 2
D 17
	/* format: {net | host} XX gateway XX metric DD [passive]\n */
E 17
I 17
/* format: {net | host} XX gateway XX metric DD [passive | external]\n */
E 17
#define	readentry(fp) \
	fscanf((fp), "%s %s gateway %s metric %d %s\n", \
		type, dname, gname, &metric, qual)
	for (;;) {
D 2
		struct hostent *host;
		struct netent *net;

E 2
D 14
		if (readentry(fp) == EOF)
E 14
I 14
		if ((n = readentry(fp)) == EOF)
E 14
			break;
D 2
		if (strcmp(type, "net") == 0) {
			net = getnetbyname(dname);
			if (net == 0 || net->n_addrtype != AF_INET)
				continue;
			dst.sin_addr = inet_makeaddr(net->n_net, INADDR_ANY);
		} else if (strcmp(type, "host") == 0) {
			host = gethostbyname(dname);
			if (host == 0)
				continue;
			bcopy(host->h_addr, &dst.sin_addr, host->h_length);
		} else
E 2
I 2
		if (!getnetorhostname(type, dname, &dst))
E 2
			continue;
D 2
		host = gethostbyname(gname);
		if (host == 0)
E 2
I 2
		if (!gethostnameornumber(gname, &gate))
E 2
			continue;
I 22
		if (metric == 0)			/* XXX */
			metric = 1;
E 22
I 5
		if (strcmp(qual, "passive") == 0) {
			/*
			 * Passive entries aren't placed in our tables,
			 * only the kernel's, so we don't copy all of the
			 * external routing information within a net.
			 * Internal machines should use the default
			 * route to a suitable gateway (like us).
			 */
			route.rt_dst = *(struct sockaddr *) &dst;
			route.rt_router = *(struct sockaddr *) &gate;
			route.rt_flags = RTF_UP;
			if (strcmp(type, "host") == 0)
				route.rt_flags |= RTF_HOST;
			if (metric)
				route.rt_flags |= RTF_GATEWAY;
D 29
			(void) ioctl(s, SIOCADDRT, (char *)&route.rt_rt);
E 29
I 29
			(void) rtioctl(ADD, &route.rt_rt);
E 29
			continue;
I 13
		}
		if (strcmp(qual, "external") == 0) {
			/*
			 * Entries marked external are handled
			 * by other means, e.g. EGP,
			 * and are placed in our tables only
			 * to prevent overriding them
			 * with something else.
			 */
			rtadd(&dst, &gate, metric, RTS_EXTERNAL|RTS_PASSIVE);
I 14
			continue;
E 14
E 13
		}
		/* assume no duplicate entries */
		externalinterfaces++;
E 5
D 2
		bcopy(host->h_addr, &gate.sin_addr, host->h_length);
E 2
		ifp = (struct interface *)malloc(sizeof (*ifp));
D 34
		bzero((char *)ifp, sizeof (*ifp));
E 34
I 34
		memset(ifp, 0, sizeof (*ifp));
E 34
		ifp->int_flags = IFF_REMOTE;
		/* can't identify broadcast capability */
		ifp->int_net = inet_netof(dst.sin_addr);
		if (strcmp(type, "host") == 0) {
			ifp->int_flags |= IFF_POINTOPOINT;
			ifp->int_dstaddr = *((struct sockaddr *)&dst);
		}
D 5
		if (strcmp(qual, "passive") == 0)
			ifp->int_flags |= IFF_PASSIVE;
		else
			/* assume no duplicate entries */
			externalinterfaces++;
E 5
		ifp->int_addr = *((struct sockaddr *)&gate);
		ifp->int_metric = metric;
		ifp->int_next = ifnet;
		ifnet = ifp;
		addrouteforif(ifp);
	}
	fclose(fp);
I 2
}

getnetorhostname(type, name, sin)
	char *type, *name;
	struct sockaddr_in *sin;
{

	if (strcmp(type, "net") == 0) {
		struct netent *np = getnetbyname(name);
		int n;

D 3
		if (np->n_addrtype != AF_INET)
			return (0);
E 3
		if (np == 0)
			n = inet_network(name);
D 3
		else
E 3
I 3
		else {
			if (np->n_addrtype != AF_INET)
				return (0);
E 3
			n = np->n_net;
I 9
			/*
			 * getnetbyname returns right-adjusted value.
			 */
			if (n < 128)
				n <<= IN_CLASSA_NSHIFT;
			else if (n < 65536)
				n <<= IN_CLASSB_NSHIFT;
			else
				n <<= IN_CLASSC_NSHIFT;
E 9
I 3
		}
E 3
		sin->sin_family = AF_INET;
		sin->sin_addr = inet_makeaddr(n, INADDR_ANY);
		return (1);
	}
	if (strcmp(type, "host") == 0) {
		struct hostent *hp = gethostbyname(name);

D 3
		if (hp->h_addrtype != AF_INET)
			return (0);
E 3
		if (hp == 0)
			sin->sin_addr.s_addr = inet_addr(name);
D 3
		else
E 3
I 3
		else {
			if (hp->h_addrtype != AF_INET)
				return (0);
E 3
D 34
			bcopy(hp->h_addr, &sin->sin_addr, hp->h_length);
E 34
I 34
			memmove(&sin->sin_addr, hp->h_addr, hp->h_length);
E 34
I 3
		}
E 3
		sin->sin_family = AF_INET;
		return (1);
	}
	return (0);
}

gethostnameornumber(name, sin)
	char *name;
	struct sockaddr_in *sin;
{
	struct hostent *hp;

	hp = gethostbyname(name);
	if (hp) {
D 34
		bcopy(hp->h_addr, &sin->sin_addr, hp->h_length);
E 34
I 34
		memmove(&sin->sin_addr, hp->h_addr, hp->h_length);
E 34
		sin->sin_family = hp->h_addrtype;
		return (1);
	}
	sin->sin_addr.s_addr = inet_addr(name);
	sin->sin_family = AF_INET;
	return (sin->sin_addr.s_addr != -1);
E 2
}
E 1
