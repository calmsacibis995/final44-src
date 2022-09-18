h60287
s 00122/00058/00454
d D 8.3.1.1 95/02/23 22:29:48 sklower 88 87
c document slightly closer to working code to send to mitre
e
s 00001/00001/00511
d D 8.3 95/01/09 17:54:21 cgd 87 85
c 64-bit changes: casts, and ioctl cmds are u_longs
e
s 00109/00028/00484
d D 8.2.1.1 94/12/02 15:02:13 sklower 86 85
c document state of non-working code for tunnel driver as sent to mitre
e
s 00000/00001/00512
d D 8.2 93/11/15 13:32:48 sklower 85 84
c af.h has been retired
e
s 00002/00002/00511
d D 8.1 93/06/11 14:02:26 bostic 84 83
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00010/00506
d D 7.35 93/06/11 14:02:17 sklower 83 80
c this works, change to actually free the storage
e
s 00002/00002/00514
d R 8.1 93/06/11 00:04:58 bostic 82 80
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00514
d R 8.1 93/06/10 22:45:29 bostic 81 80
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00012/00495
d D 7.34 93/06/04 17:31:22 bostic 80 79
c prototype everything
e
s 00010/00068/00497
d D 7.33 93/04/08 17:12:43 sklower 79 78
c new conventions for using routing tree
e
s 00016/00016/00549
d D 7.32 92/10/11 11:49:06 bostic 78 77
c make kernel includes standard
e
s 00048/00027/00517
d D 7.31 92/08/14 12:49:29 sklower 77 76
c fix an outright bug in the cloning code (if a cloned route 
c could not be added to the tree, the parent node was returned, but the 
c reference count was not incremented.)  Be more vigilant about neg. ref cnts in 
c rtfree in general.
e
s 00012/00013/00532
d D 7.30 92/07/09 00:02:39 sklower 76 75
c changes to add routing tables via the domain switch
e
s 00033/00016/00512
d D 7.29 92/02/18 15:48:26 sklower 75 74
c get rid for ifa->ifa_ft; new routing messages for adding/deleting
c /state change on interfaces', new convention for rt_missmsg
e
s 00004/00003/00524
d D 7.28 92/02/03 10:37:17 sklower 74 73
c apply fix from torek
e
s 00010/00005/00517
d D 7.27 92/01/30 11:25:55 sklower 73 72
c check in torek's changes for sparc and sklower's workarounds on ifa problems
e
s 00014/00000/00508
d D 7.26 91/12/19 17:40:24 sklower 72 71
c dirs
e
s 00001/00000/00507
d D 7.25 91/09/26 19:56:15 sklower 71 70
c if you are erroneously asked to add a route, remember to free the dst addr
e
s 00009/00013/00498
d D 7.24 91/07/30 17:40:26 sklower 70 69
c use vector on AF for routing tables rather than linked list;
c allow for methods on an AF-by-AF basis for add, insert, delete, kinfo-walk
e
s 00059/00029/00452
d D 7.23 91/06/27 18:52:33 sklower 69 68
c mostly changes to merge arp and routing tables; save space by
c separately allocated dst and gateway sockaddrs from rest of rtentry;
c also have routing layer look up route to gateway and cache it when
c installing RTF_GATEWAY type routes.
e
s 00016/00002/00465
d D 7.22 91/06/27 18:48:09 sklower 68 66
c fixes from following version for net2 release
e
s 00074/00030/00437
d R 7.22 91/06/25 21:58:05 sklower 67 66
c mostly changes to merge arp and routing tables; save space by
c separately allocated dst and gateway sockaddrs from rest of rtentry;
c also have routing layer look up route to gateway and cache it when
c installing RTF_GATEWAY type routes.
e
s 00004/00000/00463
d D 7.21 91/05/04 21:55:05 william 66 65
c missing ifdefs for NS protocol
e
s 00006/00006/00457
d D 7.20 91/04/20 16:34:07 karels 65 64
c rm user.h, reg.h; pass proc to rtioctl
e
s 00046/00008/00417
d D 7.19 91/02/19 10:56:02 sklower 64 63
c having cloning messages generated rtalloc;
c make sure when doing rtinit that you install a route to the
c correct ifaddr.  Old slip lines caused problems.
e
s 00005/00004/00420
d D 7.18 90/11/29 15:45:11 sklower 63 62
c 1.) not all interfaces set ifa_dstaddr; 2.) rn->rn_key set by addroute
c 3.) ROUNDUP should be changed to save space for default routes (otherwise 0 len)
c check in before machine directory re-org.
e
s 00001/00011/00423
d D 7.17 90/06/28 21:32:06 bostic 62 61
c new copyright notice
e
s 00039/00031/00395
d D 7.16 90/06/20 19:04:54 sklower 61 60
c changes designed so that ESIS and ARP may use routing table
c instead of private cache; allow RTM_CHANGE to specify new ifp.
e
s 00034/00028/00392
d D 7.15 90/06/09 17:40:18 sklower 60 59
c checkpoint before changes conventions about who allocates llinfo space
e
s 00013/00004/00407
d D 7.14 90/05/14 15:50:02 sklower 59 58
c minor bugfix concerning LL routes
e
s 00067/00068/00344
d D 7.13 90/04/05 11:31:11 sklower 58 57
c add notion of cloning routes; allocate extra space for llinfo when creating routes;
c no longer include rtsock.c and radix.c
e
s 00000/00002/00412
d D 7.12 89/05/04 13:42:24 mckusick 57 56
c get rid of unneeded header files
e
s 00002/00002/00412
d D 7.11 89/04/26 18:56:19 mckusick 56 55
c use new form of suser()
e
s 00002/00002/00412
d D 7.10 89/04/25 14:25:37 mckusick 55 54
c ../machine => machine
e
s 00060/00063/00354
d D 7.9 89/04/22 12:10:47 sklower 54 53
c checkpoint at first working tp4 connection; before gnodes
e
s 00196/00183/00221
d D 7.8 88/12/13 13:31:26 karels 53 52
c checkpoint semi-working version with routing socket (by sklower)
e
s 00172/00132/00232
d D 7.7 88/11/09 20:37:55 karels 52 51
c checkpoint first working version with routing trees. (by sklower).
e
s 00018/00001/00346
d D 7.6 88/10/18 17:00:08 karels 51 50
c checkpoint working kernel before introducing radix trees (by sklower)
e
s 00000/00001/00347
d D 7.5 88/10/12 14:41:11 karels 50 49
c mark state of working kernel before var. length sockaddrs
e
s 00010/00005/00338
d D 7.4 88/06/27 18:59:43 bostic 49 48
c install approved copyright notice
e
s 00008/00002/00335
d D 7.3 87/12/30 11:57:40 bostic 48 47
c add Berkeley header
e
s 00002/00001/00335
d D 7.2 87/01/15 15:09:37 karels 47 46
c mark routes modified by redirects
e
s 00001/00001/00335
d D 7.1 86/06/04 23:42:21 mckusick 46 45
c 4.3BSD release version
e
s 00002/00001/00334
d D 6.19 86/04/12 22:52:38 karels 45 42
c in rtrequest, use local addr to find I/F for host if not pt-pt
e
s 00006/00002/00333
d R 6.19 86/04/12 22:48:16 karels 44 42
c in rtrequest, use local addr if route to host, not pt-pt
e
s 00002/00001/00334
d R 6.19 86/04/12 22:05:31 karels 43 42
c in rtrequest, look up gw addr if no dstaddr on route to host
e
s 00002/00001/00333
d D 6.18 86/03/21 10:56:37 karels 42 41
c oops, logic error that doesn't hit often
e
s 00003/00002/00331
d D 6.17 86/03/04 14:00:15 karels 41 40
c lint
e
s 00003/00005/00330
d D 6.16 86/02/17 17:58:57 karels 40 39
c redirect installing new route to host is dynamic, mark it
e
s 00004/00002/00331
d D 6.15 86/02/16 20:20:28 karels 39 38
c don't install gatewayed routes to ourself as a result of redirects
e
s 00002/00002/00331
d D 6.14 85/11/22 11:41:13 sklower 38 37
c get the rest of the references to rtinit.
e
s 00002/00009/00331
d D 6.13 85/11/09 15:51:09 sklower 37 36
c in rtinit, allow for deleting pt to pt hosts, by requiring
e
s 00036/00026/00304
d D 6.12 85/09/16 21:17:15 karels 36 35
c only accept redirects from current gateway; mark dynamically
c created routes; put new routes on front of chain instead of tail
e
s 00020/00001/00310
d D 6.11 85/07/18 22:34:00 sklower 35 34
c Changes to allow multiple pt to pt links to have the same local address.
e
s 00007/00001/00304
d D 6.10 85/06/08 12:27:51 mckusick 34 33
c Add copyright
e
s 00001/00002/00304
d D 6.9 85/05/27 20:32:18 karels 33 32
c free route after receiving redirect for route to interface
c (thanks, Symbolics, for making it possible to find this one!)
e
s 00007/00007/00299
d D 6.8 85/03/19 16:01:47 karels 32 31
c move net addresses from interface layer into protocols
e
s 00013/00015/00293
d D 6.7 84/09/05 17:49:50 karels 31 30
c allow variable-size hash tables, with size in global;
c spl while searching hash list (if we want it be still be there when we use it);)
c take the first route found for now
e
s 00012/00012/00296
d D 6.6 84/08/28 17:39:18 bloom 30 28
c fix header includes.  no more ../h
e
s 00009/00009/00299
d R 6.6 84/08/28 17:14:01 bloom 29 28
c Change include paths.  No more ../h.
e
s 00003/00003/00305
d D 6.5 84/07/08 15:37:22 sam 28 27
c checked in for karels; make hash index a macro so it can be turned into a mask operation
e
s 00003/00004/00305
d D 6.4 84/04/12 11:33:38 karels 27 26
c rtredirect must distinguish routes to hosts
e
s 00024/00014/00285
d D 6.3 83/12/15 15:24:07 karels 26 25
c rtalloc reallocates route if old one is not marked RTF_UP;
c rtredirect has additional argument to distinguish between host and network
c redirects
e
s 00003/00002/00296
d D 6.2 83/10/20 15:11:29 karels 25 24
c route hash values are unsigned, else hash function gives negative index
e
s 00000/00000/00298
d D 6.1 83/07/29 07:08:53 sam 24 23
c 4.2 distribution
e
s 00009/00004/00289
d D 4.22 83/06/30 01:15:23 sam 23 22
c create dynamic routes on wildcard match
c *** CHANGED *** 83/06/30 01:16:31 sam
c don't create dynamic routes on wildcard match
e
s 00017/00000/00276
d D 4.21 83/06/12 19:47:35 sam 22 21
c revamp network ioctls; add IFF_NOTRAILERS
e
s 00069/00038/00207
d D 4.20 83/05/30 18:49:40 sam 21 20
c add wildcard routing and routing statistics; also routing redirects 
c can generate new routing table entries
e
s 00003/00002/00242
d D 4.19 83/04/05 14:27:52 sam 20 19
c families are really unsigned, avoid sign extension pitfalls
e
s 00008/00001/00236
d D 4.18 83/03/15 18:24:40 sam 19 18
c socket ioctls
e
s 00040/00000/00197
d D 4.17 83/03/12 19:45:02 sam 18 17
c handle routing redirects, albeit simplisticly
e
s 00002/00001/00195
d D 4.16 83/02/10 22:01:09 sam 17 16
c remove /usr/include dependencies
e
s 00002/00001/00194
d D 4.15 83/02/02 16:45:47 sam 16 14
c fix unsigned problem in hash values
e
s 00001/00001/00194
d R 4.15 83/02/02 12:23:00 sam 15 14
c make hash's unsigned so % doesn't give negative value
e
s 00001/00001/00194
d D 4.14 82/12/14 17:13:58 sam 14 13
c typed mbufs
e
s 00002/00004/00193
d D 4.13 82/10/17 22:16:32 root 13 12
c lint
e
s 00000/00002/00197
d D 4.12 82/10/09 05:40:39 wnj 12 11
c header file dependencies fixed up and untested changes to raw interface
e
s 00000/00002/00199
d D 4.11 82/06/20 00:55:13 sam 11 10
c purge COUNT stuff now that we can use gprof
e
s 00044/00049/00157
d D 4.10 82/06/12 23:19:48 wnj 10 9
c now the routing code might wokr
e
s 00034/00042/00172
d D 4.9 82/06/06 21:21:00 wnj 9 8
c fix search loop
e
s 00006/00000/00208
d D 4.8 82/05/11 22:24:44 sam 8 7
c don't look at routes (or routes with interfaces) marked down
e
s 00004/00000/00204
d D 4.7 82/05/04 20:26:37 sam 7 6
c bounds check on afswitch array
e
s 00011/00004/00193
d D 4.6 82/03/31 20:36:58 sam 6 5
c routing tried and working, add logical host stuff
e
s 00045/00049/00152
d D 4.5 82/03/30 19:57:38 sam 5 4
c routing code now operational
e
s 00044/00052/00157
d D 4.4 82/03/30 11:32:53 sam 4 3
c with routing, but not forwarding
e
s 00052/00047/00157
d D 4.3 82/03/29 11:32:53 sam 3 2
c first cut (incomplete) at routing
e
s 00021/00011/00183
d D 4.2 82/03/28 14:23:29 sam 2 1
c convert interfaces to sockaddr's and add hooks for routing
e
s 00194/00000/00000
d D 4.1 82/03/27 22:57:39 sam 1 0
c date and time created 82/03/27 22:57:39 by sam
e
u
U
f b 
f d 8.3
t
T
I 1
D 34
/*	%M%	%I%	%E%	*/
E 34
I 34
/*
D 46
 * Copyright (c) 1980 Regents of the University of California.
E 46
I 46
D 68
 * Copyright (c) 1980, 1986 Regents of the University of California.
E 68
I 68
D 84
 * Copyright (c) 1980, 1986, 1991 Regents of the University of California.
E 68
E 46
D 48
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 48
I 48
 * All rights reserved.
E 84
I 84
 * Copyright (c) 1980, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 84
 *
D 62
 * Redistribution and use in source and binary forms are permitted
D 49
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 49
I 49
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
E 62
I 62
 * %sccs.include.redist.c%
E 62
E 49
E 48
 *
 *	%W% (Berkeley) %G%
 */
I 83

E 83
E 34
D 53

E 53
I 53
D 55
#include "../machine/reg.h"
E 55
I 55
D 65
#include "machine/reg.h"
E 55
 
E 65
E 53
D 30
#include "../h/param.h"
I 2
#include "../h/systm.h"
D 3
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/file.h"
#include "../h/inode.h"
#include "../h/buf.h"
E 3
E 2
#include "../h/mbuf.h"
#include "../h/protosw.h"
#include "../h/socket.h"
I 22
#include "../h/dir.h"
#include "../h/user.h"
E 22
D 3
#include "../h/socketvar.h"
E 3
I 2
#include "../h/ioctl.h"
I 17
#include "../h/errno.h"
E 30
I 30
D 78
#include "param.h"
#include "systm.h"
D 53
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
E 53
D 57
#include "dir.h"
E 57
D 65
#include "user.h"
E 65
D 53
#include "ioctl.h"
E 53
I 53
D 57
#include "inode.h"
E 57
#include "proc.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "domain.h"
#include "protosw.h"
E 53
D 65
#include "errno.h"
E 65
I 53
#include "ioctl.h"
E 78
I 78
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/ioctl.h>
E 78
E 53
E 30

E 17
E 2
D 12
#include "../net/in.h"
#include "../net/in_systm.h"
E 12
I 2
D 30
#include "../net/if.h"
E 2
#include "../net/af.h"
#include "../net/route.h"
E 30
I 30
D 78
#include "if.h"
#include "af.h"
#include "route.h"
I 52
D 53
#include "radix.h"
E 52
E 30
I 3
D 17
#include <errno.h>
E 17
E 3
D 2
#include <errno.h>
E 2

I 52
#include "radix.c"
#ifdef INET
E 53
I 53
#include "raw_cb.h"
E 78
I 78
#include <net/if.h>
D 85
#include <net/af.h>
E 85
#include <net/route.h>
#include <net/raw_cb.h>
E 78
I 65

E 65
E 53
D 78
#include "../netinet/in.h"
#include "../netinet/in_var.h"
E 78
I 78
#include <netinet/in.h>
#include <netinet/in_var.h>
E 78
D 53
#endif
E 53

I 66
#ifdef NS
E 66
I 54
D 78
#include "../netns/ns.h"
E 78
I 78
#include <netns/ns.h>
E 78
I 66
#endif
E 66
E 54
I 53
D 55
#include "../machine/mtpr.h"
E 55
I 55
D 73
#include "machine/mtpr.h"
E 55
#include "netisr.h"
E 73
I 65

E 65
I 60
#define	SA(p) ((struct sockaddr *)(p))
E 60

D 58
#include "rtsock.c"

E 58
E 53
E 52
I 10
int	rttrash;		/* routes not in table but not freed */
I 21
struct	sockaddr wildcard;	/* zero valued cookie for wildcard searches */
I 31
D 75
int	rthashsize = RTHASHSIZ;	/* for netstat, etc. */
E 75
E 31

I 80
void
E 80
I 52
D 76
static int rtinits_done = 0;
D 70
struct radix_node_head *ns_rnhead, *in_rnhead;
E 70
I 53
struct radix_node *rn_match(), *rn_delete(), *rn_addroute();
E 76
I 76
rtable_init(table)
D 80
void **table;
E 80
I 80
	void **table;
E 80
{
	struct domain *dom;
	for (dom = domains; dom; dom = dom->dom_next)
		if (dom->dom_rtattach)
			dom->dom_rtattach(&table[dom->dom_family],
D 80
							dom->dom_rtoffset);
E 80
I 80
			    dom->dom_rtoffset);
E 80
}
E 76
I 65

I 80
void
E 80
E 65
E 53
D 76
rtinitheads()
E 76
I 76
route_init()
E 76
{
I 70
D 76
	extern struct radix_node_head *mask_rnhead;
E 70
	if (rtinits_done == 0 &&
I 66
#ifdef NS
E 66
D 70
	    rn_inithead(&ns_rnhead, 16, AF_NS) &&
E 70
I 70
	    rn_inithead(&rt_tables[AF_NS], 16) &&
E 70
I 66
#endif
E 66
D 70
	    rn_inithead(&in_rnhead, 32, AF_INET))
E 70
I 70
	    rn_inithead(&rt_tables[AF_INET], 32) &&
	    (rt_tables[0] = mask_rnhead) != 0)
E 70
		rtinits_done = 1;
E 76
I 76
	rn_init();	/* initialize all zeroes, all ones, mask table */
	rtable_init((void **)rt_tables);
E 76
}

E 52
E 21
E 10
/*
 * Packet routing routines.
 */
I 80
void
E 80
D 10

E 10
D 4
/*
 * With much ado about nothing...
 * route the cars that climb halfway to the stars...
 */
D 3
route(ro)
E 3
I 3
allocroute(ro)
E 4
I 4
rtalloc(ro)
E 4
E 3
	register struct route *ro;
{
I 53
	if (ro->ro_rt && ro->ro_rt->rt_ifp && (ro->ro_rt->rt_flags & RTF_UP))
		return;				 /* XXX */
	ro->ro_rt = rtalloc1(&ro->ro_dst, 1);
}

struct rtentry *
rtalloc1(dst, report)
D 60
	struct sockaddr *dst;
E 60
I 60
	register struct sockaddr *dst;
E 60
D 80
	int  report;
E 80
I 80
	int report;
E 80
{
E 53
D 21
	register struct rtentry *rt, *rtmin;
E 21
I 21
D 52
	register struct rtentry *rt;
E 21
	register struct mbuf *m;
I 2
D 4
	register int key;
E 4
I 4
D 5
	register int hash;
E 5
I 5
D 16
	register int hash, (*match)();
E 16
I 16
D 25
	register unsigned hash;
E 25
I 25
	register u_long hash;
E 25
D 21
	register int (*match)();
E 16
E 5
E 4
E 2
	struct afhash h;
E 21
	struct sockaddr *dst = &ro->ro_dst;
I 21
D 31
	int (*match)(), doinghost;
E 31
I 31
	int (*match)(), doinghost, s;
E 31
	struct afhash h;
E 21
D 2
	int af = dst->sa_family;
E 2
I 2
D 5
	int af = dst->sa_family, doinghost;
E 5
I 5
D 20
	int af = dst->sa_family;
E 20
I 20
	u_int af = dst->sa_family;
I 21
D 31
	struct rtentry *rtmin;
E 31
	struct mbuf **table;
E 52
I 52
D 70
	register struct radix_node_head *rnh;
E 70
I 70
	register struct radix_node_head *rnh = rt_tables[dst->sa_family];
E 70
I 60
	register struct rtentry *rt;
E 60
	register struct radix_node *rn;
D 60
	register struct rtentry *rt = 0;
D 53
	u_char af = ro->ro_dst.sa_family;
	int  s;
E 53
I 53
	u_char af = dst->sa_family;
	int  s = splnet();
E 60
I 60
	struct rtentry *newrt = 0;
I 75
	struct rt_addrinfo info;
E 75
D 64
	int  s = splnet(), err = 0;
E 64
I 64
	int  s = splnet(), err = 0, msgtype = RTM_MISS;
E 64
E 60
E 53
E 52
E 21
E 20
E 5
E 2

I 86
	bzero((caddr_t)&info, sizeof(info));
	info.rti_info[RTAX_DST] = dst;
E 86
D 3
COUNT(ROUTE);
D 2
	if (ro->ro_ifp)		/* ??? */
E 2
I 2
	if (ro && ro->ro_rt && ro->ro_rt->rt_ifp)	/* ??? */
E 3
I 3
D 4
COUNT(ALLOCROUTE);
	if (ro->ro_rt && ro->ro_rt->rt_ifp)	/* can't happen */
E 4
I 4
D 11
COUNT(RTALLOC);
E 11
D 26
	if (ro->ro_rt && ro->ro_rt->rt_ifp)			/* XXX */
E 4
E 3
E 2
		return;
E 26
I 26
D 53
	if (ro->ro_rt && ro->ro_rt->rt_ifp && (ro->ro_rt->rt_flags & RTF_UP))
		return;				 /* XXX */
E 26
I 7
D 52
	if (af >= AF_MAX)
		return;
E 7
	(*afswitch[af].af_hash)(dst, &h);
D 4
	m = routehash[h.afh_hosthash % RTHASHSIZ];
	key = h.afh_hostkey;
E 4
I 4
D 5
	hash = h.afh_hosthash;
E 4
	rtmin = 0, doinghost = 1;
again:
I 4
	m = routehash[hash % RTHASHSIZ];
E 4
	for (; m; m = m->m_next) {
E 5
I 5
D 21
	rtmin = 0, hash = h.afh_hosthash;
	for (m = rthost[hash % RTHASHSIZ]; m; m = m->m_next) {
E 5
		rt = mtod(m, struct rtentry *);
D 3
#define	equal(a1, a2) \
	(bcmp((caddr_t)(a1), (caddr_t)(a2), sizeof(struct sockaddr)) == 0)
E 3
D 4
		if (rt->rt_key != key)
E 4
I 4
D 5
		if (rt->rt_hash[doinghost] != hash)
E 5
I 5
		if (rt->rt_hash != hash)
E 5
E 4
			continue;
I 8
		if ((rt->rt_flags & RTF_UP) == 0 ||
		    (rt->rt_ifp->if_flags & IFF_UP) == 0)
			continue;
E 8
D 5
		if (doinghost) {
I 3
#define	equal(a1, a2) \
	(bcmp((caddr_t)(a1), (caddr_t)(a2), sizeof(struct sockaddr)) == 0)
E 3
			if (!equal(&rt->rt_dst, dst))
				continue;
		} else {
			if (rt->rt_dst.sa_family != af)
				continue;
			if ((*afswitch[af].af_netmatch)(&rt->rt_dst, dst) == 0)
				continue;
		}
E 5
I 5
		if (bcmp((caddr_t)&rt->rt_dst, (caddr_t)dst, sizeof (*dst)))
			continue;
E 5
		if (rtmin == 0 || rt->rt_use < rtmin->rt_use)
			rtmin = rt;
	}
D 5
	if (rtmin) {
D 4
		ro->ro_dst = rt->rt_dst;
E 4
		ro->ro_rt = rt;
		rt->rt_refcnt++;
D 3
		return;
E 3
I 3
D 4
		return (rt->rt_flags & RTF_DIRECT);
E 4
I 4
		return;
E 5
I 5
	if (rtmin) 
		goto found;

	hash = h.afh_nethash;
E 21
I 21
D 31
	rtmin = 0;
E 31
E 21
	match = afswitch[af].af_netmatch;
D 21
	for (m = rtnet[hash % RTHASHSIZ]; m; m = m->m_next) {
E 21
I 21
	hash = h.afh_hosthash, table = rthost, doinghost = 1;
E 52
I 31
	s = splnet();
E 53
E 31
D 52
again:
D 28
	for (m = table[hash % RTHASHSIZ]; m; m = m->m_next) {
E 28
I 28
	for (m = table[RTHASHMOD(hash)]; m; m = m->m_next) {
E 28
E 21
		rt = mtod(m, struct rtentry *);
		if (rt->rt_hash != hash)
I 8
			continue;
		if ((rt->rt_flags & RTF_UP) == 0 ||
		    (rt->rt_ifp->if_flags & IFF_UP) == 0)
E 8
			continue;
D 21
		if (rt->rt_dst.sa_family != af || !(*match)(&rt->rt_dst, dst))
			continue;
E 21
I 21
		if (doinghost) {
			if (bcmp((caddr_t)&rt->rt_dst, (caddr_t)dst,
			    sizeof (*dst)))
				continue;
		} else {
			if (rt->rt_dst.sa_family != af ||
			    !(*match)(&rt->rt_dst, dst))
				continue;
		}
E 52
I 52
D 60
	for (rnh = radix_node_head; rnh && (af != rnh->rnh_af); )
E 60
I 60
D 70
	for (rnh = radix_node_head; rnh && (dst->sa_family != rnh->rnh_af); )
E 60
		rnh = rnh->rnh_next;
E 70
D 79
	if (rnh && rnh->rnh_treetop &&
D 53
	    (rn = rn_match((char *)&(ro->ro_dst), rnh->rnh_treetop)) &&
E 53
I 53
D 70
	    (rn = rn_match((caddr_t)dst, rnh->rnh_treetop)) &&
E 70
I 70
	    (rn = rnh->rnh_match((caddr_t)dst, rnh->rnh_treetop)) &&
E 79
I 79
	if (rnh && (rn = rnh->rnh_matchaddr((caddr_t)dst, rnh)) &&
E 79
E 70
E 53
	    ((rn->rn_flags & RNF_ROOT) == 0)) {
D 53
		rt = &(((struct nrtentry *)rn)->nrt_rt);
E 53
I 53
D 60
		rt = (struct rtentry *)rn;
E 60
I 60
		newrt = rt = (struct rtentry *)rn;
E 60
E 53
E 52
E 21
D 31
		if (rtmin == 0 || rt->rt_use < rtmin->rt_use)
			rtmin = rt;
E 31
I 31
D 58
		rt->rt_refcnt++;
E 58
I 58
		if (report && (rt->rt_flags & RTF_CLONING)) {
D 60
			struct rtentry *newrt = 0;
			int flags = rt->rt_flags & ~RTF_CLONING;

			if (rt->rt_genmask == 0) flags |= RTF_HOST;
			(void) rtrequest(RTM_ADD, dst, rt->rt_gateway,
			      rt->rt_genmask, flags, &newrt);
			rt = newrt;
E 60
I 60
D 64
			if (err = rtrequest(RTM_RESOLVE, dst, SA(0),
					      SA(0), 0, &newrt))
				goto miss;
E 64
I 64
D 77
			if ((err = rtrequest(RTM_RESOLVE, dst, SA(0),
					      SA(0), 0, &newrt)) ||
			    ((rt->rt_flags & RTF_XRESOLVE)
D 69
			      && (msgtype = RTM_RESOLVE))) /* intended! */
E 69
I 69
			      && (msgtype = RTM_RESOLVE))) /* assign intended */
E 69
			    goto miss;
E 77
I 77
D 86
			err = rtrequest(RTM_RESOLVE, dst, SA(0),
					      SA(0), 0, &newrt);
E 86
I 86
			info.rti_ifa = rt->rt_ifa;
			info.rti_ifp = rt->rt_ifp;
			info.rti_flags = rt->rt_flags & ~RTF_CLONING;
			info.rti_info[RTAX_GATEWAY] = rt->rt_gateway;
			if ((info.rti_info[RTAX_NETMASK] = rt->rt_genmask) == 0)
				info.rti_flags |= RTF_HOST;
			err = rtrequest1(RTM_RESOLVE, &info, &newrt);
E 86
			if (err) {
				newrt = rt;
				rt->rt_refcnt++;
				goto miss;
			}
D 86
			if ((rt = newrt) && (rt->rt_flags & RTF_XRESOLVE)) {
E 86
I 86
			newrt->rt_rmx = rt->rt_rmx;
			if (rt->rt_flags & RTF_XRESOLVE) {
E 86
				msgtype = RTM_RESOLVE;
				goto miss;
			}
E 77
E 64
E 60
		} else
			rt->rt_refcnt++;
D 60
		if (rt == 0)
			goto miss;
E 60
E 58
D 52
		splx(s);
		if (dst == &wildcard)
			rtstat.rts_wildcard++;
		ro->ro_rt = rt;
		return;
E 31
E 5
E 4
E 3
	}
D 5
	if (doinghost) {
		doinghost = 0;
D 2
		m = routethash[h.afh_nethash % RTHASHSIZ];
E 2
I 2
D 4
		m = routehash[h.afh_nethash % RTHASHSIZ];
E 2
		key = h.afh_netkey;
E 4
I 4
		hash = h.afh_nethash;
E 4
		goto again;
	}
D 2
	ro->ro_ifp = 0;
E 2
	ro->ro_rt = 0;
I 3
D 4
	return (0);
E 4
I 4
	return;
E 5
I 5
D 21
found:
E 21
I 21
D 31
	if (rtmin == 0 && doinghost) {
E 31
I 31
	if (doinghost) {
E 31
		doinghost = 0;
		hash = h.afh_nethash, table = rtnet;
		goto again;
	}
	/*
	 * Check for wildcard gateway, by convention network 0.
	 */
D 31
	if (rtmin == 0 && dst != &wildcard) {
E 31
I 31
	if (dst != &wildcard) {
E 31
		dst = &wildcard, hash = 0;
		goto again;
	}
E 52
I 52
D 53
	} else
E 53
I 53
	} else {
E 53
		rtstat.rts_unreach++;
D 53
	ro->ro_rt = rt;
E 53
I 53
D 54
		if (report && route_cb.any_count)
E 54
I 54
D 58
		if (report)
E 58
I 58
D 75
	miss:	if (report)
E 58
E 54
D 60
			rt_missmsg(RTM_MISS, dst, (struct sockaddr *)0,
D 54
			       (struct sockaddr *)0, (struct sockaddr *)0, 0);
E 54
I 54
			   (struct sockaddr *)0, (struct sockaddr *)0, 0, 0);
E 60
I 60
D 64
			rt_missmsg(RTM_MISS, dst, SA(0), SA(0), SA(0), 0, err);
E 64
I 64
			rt_missmsg(msgtype, dst, SA(0), SA(0), SA(0), 0, err);
E 75
I 75
	miss:	if (report) {
D 86
			bzero((caddr_t)&info, sizeof(info));
			info.rti_info[RTAX_DST] = dst;
E 86
			rt_missmsg(msgtype, &info, 0, err);
		}
E 75
E 64
E 60
E 54
	}
E 53
E 52
E 21
D 31
	ro->ro_rt = rtmin;
I 6
D 21
	if (rtmin)
		rtmin->rt_refcnt++;
E 21
I 21
	if (rtmin == 0) {
		rtstat.rts_unreach++;
		return;
	}
	rtmin->rt_refcnt++;
	if (dst == &wildcard)
		rtstat.rts_wildcard++;
E 31
I 31
	splx(s);
I 53
D 60
	return (rt);
E 60
I 60
	return (newrt);
E 60
E 53
D 52
	rtstat.rts_unreach++;
E 52
E 31
E 21
E 6
E 5
E 4
E 3
}

I 80
void
E 80
I 3
D 4
freeroute(rt)
E 4
I 4
rtfree(rt)
E 4
	register struct rtentry *rt;
{
I 58
	register struct ifaddr *ifa;
I 77

E 77
E 58
I 10
D 13
	register struct mbuf **mp;
E 13
E 10
I 4
D 52

E 52
I 52
D 53
	register struct nrtentry *nrt;
E 53
D 54
	u_char *af;
E 54
E 52
E 4
D 6
COUNT(FREEROUTE);
E 6
	if (rt == 0)
D 13
		panic("freeroute");
E 13
I 13
		panic("rtfree");
E 13
	rt->rt_refcnt--;
D 10
	/* on refcnt == 0 reclaim? notify someone? */
E 10
I 10
D 52
	if (rt->rt_refcnt == 0 && (rt->rt_flags&RTF_UP) == 0) {
E 52
I 52
D 58
	if (rt->rt_refcnt <= 0 && (rt->rt_flags&RTF_UP) == 0) {
E 58
I 58
	if (rt->rt_refcnt <= 0 && (rt->rt_flags & RTF_UP) == 0) {
E 58
E 52
D 77
		rttrash--;
I 72
		ifa = rt->rt_ifa;
E 77
E 72
D 52
		(void) m_free(dtom(rt));
E 52
I 52
D 53
		nrt = (struct nrtentry *) (((struct radix_node *)rt) - 2);
		if (nrt->nrt_nodes->rn_flags & (RNF_ACTIVE | RNF_ROOT))
E 53
I 53
		if (rt->rt_nodes->rn_flags & (RNF_ACTIVE | RNF_ROOT))
E 53
			panic ("rtfree 2");
I 77
		rttrash--;
		if (rt->rt_refcnt < 0) {
			printf("rtfree: %x not freed (neg refs)\n", rt);
			return;
		}
		ifa = rt->rt_ifa;
		IFAFREE(ifa);
E 77
D 53
		free((caddr_t)nrt, M_RTABLE);
E 53
I 53
D 69
		free((caddr_t)rt, M_RTABLE);
E 69
I 69
		Free(rt_key(rt));
		Free(rt);
I 72
D 77
		IFAFREE(ifa);
E 77
E 72
E 69
E 53
E 52
	}
E 10
}
D 73

E 73
I 73
D 77
int ifafree_verbose;
I 75
struct ifaddr *ifafree_usedlist;
E 77
I 77

D 83
int ifafree_verbose = 1;
/*
 * We are still debugging potential overfreeing of ifaddr's
 */
E 83
E 77
E 75
E 73
I 72
void
ifafree(ifa)
	register struct ifaddr *ifa;
{
D 83
	if (ifa == 0)
E 83
I 83
	if (ifa == NULL)
E 83
		panic("ifafree");
I 73
D 77
	/* for now . . . . */
	if (ifafree_verbose) {
	    if (ifa->ifa_refcnt < 0)
D 75
		    printf("ifafree: would panic\n");
	    if (ifa->ifa_refcnt == 0)
E 75
I 75
		    printf("ifafree(%x): would panic\n", ifa);
	    if (ifa->ifa_refcnt == 0) {
E 75
		    printf("ifafree((caddr_t)ifa, M_IFADDR)\n");
I 75
		    ifa->ifa_next = ifafree_usedlist;
		    ifafree_usedlist = ifa;
	    }
E 75
	    if (ifa->ifa_flags & IFA_ROUTE)
		    printf("ifafree: has route \n");
	}
E 77
I 77
D 83
	if (ifa->ifa_refcnt < 0)
		printf("ifafree: %x ref %d\n", ifa, ifa->ifa_refcnt);
	if (ifa->ifa_refcnt == 0 && ifafree_verbose)
		printf("ifafree: %x not freed.\n", ifa);
E 77
E 73
	ifa->ifa_refcnt--;
E 83
I 83
	if (ifa->ifa_refcnt == 0)
		free(ifa, M_IFADDR);
	else
		ifa->ifa_refcnt--;
E 83
D 73
	if (ifa->ifa_refcnt <= 0 && (ifa->ifa_flags & IFA_ROUTE) == 0)
		free((caddr_t)ifa, M_IFADDR);
E 73
}

E 72
I 5
D 10
#define	equal(a1, a2) \
	(bcmp((caddr_t)(a1), (caddr_t)(a2), sizeof (struct sockaddr)) == 0)
E 10
E 5
D 4
#ifdef notdef
E 3
struct rtentry *
reroute(sa)
	register struct sockaddr *sa;
{
	register struct rtentry *rt;
	register struct mbuf *m;
I 2
	register int key;
E 2
	struct afhash h;

COUNT(REROUTE);
	(*afswitch[sa->sa_family].af_hash)(sa, &h);
	m = routehash[h.afh_hosthash];
	key = h.afh_hostkey;
	for (; m; m = m->m_next) {
		rt = mtod(m, struct rtentry *);
		if (rt->rt_key != key)
			continue;
		if (equal(&rt->rt_gateway, sa))
			return (rt);
	}
	return (0);
}
I 3
#endif
E 3

E 4
/*
I 18
 * Force a routing table entry to the specified
 * destination to go through the given gateway.
 * Normally called as a result of a routing redirect
 * message from the network layer.
 *
D 52
 * N.B.: must be called at splnet or higher
E 52
I 52
 * N.B.: must be called at splnet
E 52
 *
D 36
 * Should notify all parties with a reference to
 * the route that it's changed (so, for instance,
D 21
 * round trip time estimates may be recalculated),
E 21
I 21
 * current round trip time estimates could be flushed),
E 21
 * but we have no back pointers at the moment.
E 36
 */
I 80
int
E 80
D 26
rtredirect(dst, gateway)
E 26
I 26
D 36
rtredirect(dst, gateway, flags)
E 26
	struct sockaddr *dst, *gateway;
E 36
I 36
D 53
rtredirect(dst, gateway, flags, src)
E 53
I 53
D 54
rtredirect(dst, gateway, netmask, flags, src)
E 53
	struct sockaddr *dst, *gateway, *src;
E 54
I 54
rtredirect(dst, gateway, netmask, flags, src, rtp)
	struct sockaddr *dst, *gateway, *netmask, *src;
E 54
E 36
I 26
	int flags;
I 54
	struct rtentry **rtp;
E 54
E 26
{
D 53
	struct route ro;
E 53
	register struct rtentry *rt;
I 54
	int error = 0;
	short *stat = 0;
I 75
	struct rt_addrinfo info;
I 79
	struct ifaddr *ifa;
E 79
E 75
E 54

	/* verify the gateway is directly reachable */
D 21
	if (if_ifwithnet(gateway) == 0)
E 21
I 21
D 32
	if (if_ifwithnet(gateway) == 0) {
E 32
I 32
D 79
	if (ifa_ifwithnet(gateway) == 0) {
E 79
I 79
	if ((ifa = ifa_ifwithnet(gateway)) == 0) {
E 79
E 32
D 54
		rtstat.rts_badredirect++;
E 21
		return;
E 54
I 54
		error = ENETUNREACH;
D 74
		goto done;
E 74
I 74
		goto out;
E 74
E 54
I 21
	}
E 21
D 53
	ro.ro_dst = *dst;
D 21
	ro.ro_rt = NULL;
E 21
I 21
	ro.ro_rt = 0;
E 21
	rtalloc(&ro);
	rt = ro.ro_rt;
E 53
I 53
D 54
	rt = rtalloc1(dst, 1);
E 53
I 36
#define	equal(a1, a2) \
D 51
	(bcmp((caddr_t)(a1), (caddr_t)(a2), sizeof(struct sockaddr)) == 0)
E 51
I 51
  (bcmp((caddr_t)(a1), (caddr_t)(a2), ((struct sockaddr *)(a1))->sa_len) == 0)
E 54
I 54
	rt = rtalloc1(dst, 0);
E 54
E 51
E 36
	/*
I 36
	 * If the redirect isn't from our current router for this dst,
D 39
	 * it's either old or wrong.
E 39
I 39
	 * it's either old or wrong.  If it redirects us to ourselves,
	 * we have a routing loop, perhaps as a result of an interface
	 * going down recently.
E 39
	 */
D 39
	if (rt && !equal(src, &rt->rt_gateway)) {
E 39
I 39
D 54
	if ((rt && !equal(src, &rt->rt_gateway)) || ifa_ifwithaddr(gateway)) {
E 39
		rtstat.rts_badredirect++;
D 42
		rtfree(rt);
E 42
I 42
		if (rt)
			rtfree(rt);
E 42
		return;
	}
E 54
I 54
#define	equal(a1, a2) (bcmp((caddr_t)(a1), (caddr_t)(a2), (a1)->sa_len) == 0)
D 79
	if (!(flags & RTF_DONE) && rt && !equal(src, rt->rt_gateway))
E 79
I 79
	if (!(flags & RTF_DONE) && rt &&
	     (!equal(src, rt->rt_gateway) || rt->rt_ifa != ifa))
E 79
		error = EINVAL;
	else if (ifa_ifwithaddr(gateway))
		error = EHOSTUNREACH;
	if (error)
		goto done;
E 54
	/*
I 52
D 54
	 * Old comment:
E 54
E 52
E 36
I 21
D 23
	 * Create a new entry if the lookup failed.
	 * This is necessary for hosts which use routing
	 * redirects generated by smart gateways to dynamically
	 * build the routing tables.
E 23
I 23
	 * Create a new entry if we just got back a wildcard entry
	 * or the the lookup failed.  This is necessary for hosts
	 * which use routing redirects generated by smart gateways
	 * to dynamically build the routing tables.
E 23
D 52
	 */
I 23
	if (rt &&
	    (*afswitch[dst->sa_family].af_netmatch)(&wildcard, &rt->rt_dst)) {
E 52
I 52
D 54
	 *
	 * New comment:
	 * If we survived the previous tests, it doesn't matter
	 * what sort of entry we got when we looked it up;
	 * we should just go ahead and free the reference to
	 * the route we created.  rtalloc will not give a
	 * pointer to the root node.  And if we got a pointer
	 * to a default gateway, we should free the reference
	 * in any case.
	if (rt) {
E 52
		rtfree(rt);
		rt = 0;
	}
I 53
	if (route_cb.any_count)
		rt_missmsg(RTM_REDIRECT, dst, gateway, netmask, src,
				(flags & RTF_HOST) | RTF_GATEWAY | RTF_DYNAMIC);
E 54
E 53
I 52
	 */
E 52
E 23
D 54
	if (rt == 0) {
D 27
		rtinit(dst, gateway, RTF_GATEWAY);
E 27
I 27
D 36
		rtinit(dst, gateway, (flags & RTF_HOST) | RTF_GATEWAY);
E 36
I 36
D 38
		rtinit(dst, gateway,
E 38
I 38
D 41
		rtinit(dst, gateway, SIOCADDRT,
E 41
I 41
D 53
		rtinit(dst, gateway, (int)SIOCADDRT,
E 41
E 38
		    (flags & RTF_HOST) | RTF_GATEWAY | RTF_DYNAMIC);
E 53
I 53
		rtrequest((int)RTM_ADD, dst, gateway, 0,
		    (flags & RTF_HOST) | RTF_GATEWAY | RTF_DYNAMIC, 0);
E 53
E 36
E 27
		rtstat.rts_dynamic++;
		return;
	}
E 54
I 54
	if ((rt == 0) || (rt_mask(rt) && rt_mask(rt)->sa_len < 2))
		goto create;
E 54
	/*
E 21
	 * Don't listen to the redirect if it's
	 * for a route to an interface. 
D 21
	 *
	 * Should probably create a new entry when
	 * the lookup fails.  This will be necessary
	 * when wildcard routes are added.
E 21
	 */
D 21
	if (rt == NULL || (rt->rt_flags & RTF_GATEWAY) == 0)
E 21
I 21
	if (rt->rt_flags & RTF_GATEWAY) {
D 26
		/*
		 * Smash the current notion of the gateway to
		 * this destination.  This is probably not right,
		 * as it's conceivable a flurry of redirects could
		 * cause the gateway value to fluctuate wildly during
		 * dynamic routing reconfiguration.
		 */
		rt->rt_gateway = *gateway;
		rtfree(rt);
		rtstat.rts_newgateway++;
E 21
		return;
E 26
I 26
		if (((rt->rt_flags & RTF_HOST) == 0) && (flags & RTF_HOST)) {
			/*
D 27
			 * Changing from route to gateway => route to host.
E 27
I 27
			 * Changing from route to net => route to host.
E 27
			 * Create new route, rather than smashing route to net.
			 */
D 33
			rtfree(rt);
E 33
D 38
			rtinit(dst, gateway, flags);
E 38
I 38
D 40
			rtinit(dst, gateway, SIOCADDRT, flags);
E 40
I 40
D 41
			rtinit(dst, gateway, SIOCADDRT, flags | RTF_DYNAMIC);
E 41
I 41
D 53
			rtinit(dst, gateway, (int)SIOCADDRT,
			    flags | RTF_DYNAMIC);
E 53
I 53
D 54
			rtrequest((int)RTM_ADD, dst, gateway, 0,
			    (flags & RTF_HOST) | RTF_GATEWAY | RTF_DYNAMIC, 0);
E 53
E 41
			rtstat.rts_dynamic++;
E 54
I 54
		create:
			flags |=  RTF_GATEWAY | RTF_DYNAMIC;
			error = rtrequest((int)RTM_ADD, dst, gateway,
D 60
				    (struct sockaddr *)0, flags,
E 60
I 60
D 79
				    SA(0), flags,
E 79
I 79
				    netmask, flags,
E 79
E 60
				    (struct rtentry **)0);
			stat = &rtstat.rts_dynamic;
E 54
E 40
E 38
D 27
			rtstat.rts_newgateway++;
E 27
		} else {
			/*
			 * Smash the current notion of the gateway to
D 40
			 * this destination.  This is probably not right,
			 * as it's conceivable a flurry of redirects could
			 * cause the gateway value to fluctuate wildly during
			 * dynamic routing reconfiguration.
E 40
I 40
D 54
			 * this destination.
E 54
I 54
			 * this destination.  Should check about netmask!!!
E 54
E 40
			 */
D 52
			rt->rt_gateway = *gateway;
E 52
I 52
D 53
			rt->rt_gateway = *gateway; /*XXX -- size? */
E 52
I 47
			rt->rt_flags |= RTF_MODIFIED;
			rtstat.rts_newgateway++;
E 53
I 53
D 69
			if (gateway->sa_len <= rt->rt_gateway->sa_len) {
				Bcopy(gateway, rt->rt_gateway, gateway->sa_len);
				rt->rt_flags |= RTF_MODIFIED;
D 54
				rtstat.rts_newgateway++;
E 54
I 54
				flags |= RTF_MODIFIED;
				stat = &rtstat.rts_newgateway;
E 54
			} else
D 54
				rtstat.rts_badredirect++;
E 54
I 54
				error = ENOSPC;
E 69
I 69
			rt->rt_flags |= RTF_MODIFIED;
			flags |= RTF_MODIFIED;
			stat = &rtstat.rts_newgateway;
			rt_setgate(rt, rt_key(rt), gateway);
E 69
E 54
E 53
E 47
D 33
			rtfree(rt);
E 33
D 27
			rtstat.rts_newgateway++;
E 27
		}
I 27
D 47
		rtstat.rts_newgateway++;
E 47
E 27
E 26
D 21
	rt->rt_gateway = *gateway;
	rtfree(rt);
E 21
I 21
D 36
	}
E 36
I 36
	} else
I 54
		error = EHOSTUNREACH;
done:
	if (rt) {
		if (rtp && !error)
			*rtp = rt;
		else
			rtfree(rt);
	}
I 74
out:
E 74
	if (error)
E 54
		rtstat.rts_badredirect++;
E 36
I 33
D 54
	rtfree(rt);
E 54
I 54
D 74
	else
		(stat && (*stat)++);
E 74
I 74
	else if (stat != NULL)
		(*stat)++;
E 74
D 75
	rt_missmsg(RTM_REDIRECT, dst, gateway, netmask, src, flags, error);
E 75
I 75
	bzero((caddr_t)&info, sizeof(info));
	info.rti_info[RTAX_DST] = dst;
	info.rti_info[RTAX_GATEWAY] = gateway;
	info.rti_info[RTAX_NETMASK] = netmask;
	info.rti_info[RTAX_AUTHOR] = src;
	rt_missmsg(RTM_REDIRECT, &info, flags, error);
E 75
E 54
E 33
I 22
}

/*
D 54
 * Routing table ioctl interface.
 */
E 54
I 54
* Routing table ioctl interface.
*/
I 80
int
E 80
E 54
D 53
rtioctl(cmd, data)
	int cmd;
E 53
I 53
D 65
rtioctl(req, data)
E 65
I 65
rtioctl(req, data, p)
E 65
D 87
	int req;
E 87
I 87
	u_long req;
E 87
E 53
	caddr_t data;
I 65
	struct proc *p;
E 65
{
I 53
D 79
#ifndef COMPAT_43
E 79
	return (EOPNOTSUPP);
D 79
#else
	register struct ortentry *entry = (struct ortentry *)data;
	int error;
	struct sockaddr *netmask = 0;
E 53

D 53
	if (cmd != SIOCADDRT && cmd != SIOCDELRT)
E 53
I 53
	if (req == SIOCADDRT)
		req = RTM_ADD;
	else if (req == SIOCDELRT)
		req = RTM_DELETE;
	else
E 53
		return (EINVAL);
I 53

E 53
D 56
	if (!suser())
		return (u.u_error);
E 56
I 56
D 65
	if (error = suser(u.u_cred, &u.u_acflag))
E 65
I 65
	if (error = suser(p->p_ucred, &p->p_acflag))
E 65
		return (error);
E 56
D 53
	return (rtrequest(cmd, (struct rtentry *)data));
E 22
E 21
}
I 52
/*
 * This routine will go away soon.
 * Tries to guess which netmask is appropriate for a given net.
 */
static struct sockaddr_in rtgmask = { 8, 0 };
E 52

I 52
char *
rtgetmask(sa, ifa)
register struct sockaddr *sa;
register struct ifaddr *ifa;
{
	u_long i, net, mask, subnet;

	switch (sa->sa_family) {
#ifdef INET
	register struct in_ifaddr *ia;

	case AF_INET:

		i = ntohl(((struct sockaddr_in *)sa)->sin_addr.s_addr);
		if (i == 0) {
			rtgmask.sin_addr.s_addr = 0;
			return ((char *)&rtgmask);
		} else if (IN_CLASSA(i)) {
			net = i & IN_CLASSA_NET;
			mask = IN_CLASSA_NET;
		} else if (IN_CLASSB(i)) {
			net = i & IN_CLASSB_NET;
			mask = IN_CLASSB_NET;
		} else if (IN_CLASSC(i)) {
			net = i & IN_CLASSC_NET;
			mask = IN_CLASSC_NET;
		} else {
			net = i;
			mask = 0xffffffff;
		}

		/*
		 * Check whether network is a subnet;
		 * if so, return subnet number.
		 */
		for (ia = in_ifaddr; ia; ia = ia->ia_next)
			if (net == ia->ia_net) {
				ifa = &ia->ia_ifa;
				break;
			}
		if (ia == 0) {
			rtgmask.sin_addr.s_addr = ntohl(mask);
			return ((char *)&rtgmask);
		}
#endif
	}
	return ((char *)ifa->ifa_netmask);
}

E 52
/*
E 18
D 3
 * Routing control calls allow a routing daemon
 * to consistenly access the routing data base for updates.
E 3
I 3
 * Carry out a request to change the routing table.  Called by
D 21
 * interfaces at boot time to make their ``local routes'' known
 * and for ioctl's.
E 21
I 21
 * interfaces at boot time to make their ``local routes'' known,
 * for ioctl's, and as the result of routing redirects.
E 21
E 3
 */
D 3
rtcontrol(req, addr)
	caddr_t addr;
{
D 2
	register struct rtreq rq;
E 2
I 2
	register struct rtentry rq;
E 2
	int x = splimp(), err = 0;

COUNT(RTCONTROL);
	if (suser())
		goto bad;
D 2
	if (copyin(addr, (caddr_t)&rq, sizeof(struct rtreq))) {
E 2
I 2
	if (copyin(addr, (caddr_t)&rq, sizeof(struct rtentry))) {
E 2
		u.u_error = EFAULT;
		goto bad;
	}
	err = rtrequest(req, &rq);
bad:
	splx(x);
	return (err);
}

/*
 * Carry out a user request to modify the data base.
 */
E 3
D 10
rtrequest(req, new)
E 10
I 10
rtrequest(req, entry)
E 10
	int req;
D 9
	register struct rtentry *new;
E 9
I 9
D 10
	struct rtentry *new;
E 10
I 10
	register struct rtentry *entry;
E 10
E 9
{
D 10
	register struct rtentry *rt;
E 10
D 52
	register struct mbuf *m, **mprev;
I 36
	struct mbuf **mfirst;
E 52
E 36
I 2
D 4
	register int key;
E 4
I 4
D 5
	register int hash;
E 4
E 2
	struct sockaddr *sa = &new->rt_dst;
E 5
I 5
D 9
	register int hash, (*match)();
E 9
D 10
	register struct sockaddr *sa = &new->rt_dst;
	register struct sockaddr *gate = &new->rt_gateway;
E 10
I 10
	register struct rtentry *rt;
E 10
E 5
D 52
	struct afhash h;
I 6
D 9
	struct mbuf **oldmprev;
E 9
E 6
D 2
	int af = sa->sa_family;
E 2
I 2
D 3
	int af = sa->sa_family, doinghost;
E 3
I 3
D 10
	int af = sa->sa_family, doinghost, s, error = 0;
I 9
	int hash, (*match)();
E 10
I 10
D 20
	int af, s, error = 0, hash, (*match)();
E 20
I 20
D 25
	int s, error = 0, hash, (*match)();
E 25
I 25
	int s, error = 0, (*match)();
E 25
	u_int af;
I 25
	u_long hash;
E 52
I 52
	int s, error = 0, found;
	u_char af;
E 52
E 25
E 20
D 32
	struct ifnet *ifp;
E 32
I 32
	struct ifaddr *ifa;
I 35
	struct ifaddr *ifa_ifwithdstaddr();
I 52
	register struct nrtentry *nrt;
	register struct radix_node *rn;
	register struct radix_node_head *rnh;
	struct radix_node *head;
	char *netmask;
E 52
E 35
E 32
E 10
E 9
E 3
E 2

I 51
#ifdef COMPAT_43
E 53
#if BYTE_ORDER != BIG_ENDIAN
I 52
D 53
	s = splnet();
E 53
E 52
	if (entry->rt_dst.sa_family == 0 && entry->rt_dst.sa_len < 16) {
		entry->rt_dst.sa_family = entry->rt_dst.sa_len;
		entry->rt_dst.sa_len = 16;
	}
	if (entry->rt_gateway.sa_family == 0 && entry->rt_gateway.sa_len < 16) {
		entry->rt_gateway.sa_family = entry->rt_gateway.sa_len;
		entry->rt_gateway.sa_len = 16;
	}
#else
	if (entry->rt_dst.sa_len == 0)
		entry->rt_dst.sa_len = 16;
	if (entry->rt_gateway.sa_len == 0)
		entry->rt_gateway.sa_len = 16;
#endif
I 53
	if ((entry->rt_flags & RTF_HOST) == 0)
		switch (entry->rt_dst.sa_family) {
#ifdef INET
		case AF_INET:
			{
				extern struct sockaddr_in icmpmask;
D 54
				u_long in_maskof();
E 54
				struct sockaddr_in *dst_in = 
					(struct sockaddr_in *)&entry->rt_dst;
D 54
				u_long i = ntohl(dst_in->sin_addr.s_addr);
E 54

D 54
				icmpmask.sin_addr.s_addr = ntohl(in_maskof(i));
E 54
I 54
				in_sockmaskof(dst_in->sin_addr, &icmpmask);
E 54
				netmask = (struct sockaddr *)&icmpmask;
			}
			break;
E 53
#endif
I 53
#ifdef NS
		case AF_NS:
			{
				extern struct sockaddr_ns ns_netmask;
				netmask = (struct sockaddr *)&ns_netmask;
			}
#endif
		}
	error =  rtrequest(req, &(entry->rt_dst), &(entry->rt_gateway), netmask,
D 54
					entry->rt_flags, 0);
E 54
I 54
				entry->rt_flags, (struct rtentry **)0);
E 54
D 75
	rt_missmsg((req == RTM_ADD ? RTM_OLDADD : RTM_OLDDEL),
E 75
I 75
	/* rt_missmsg((req == RTM_ADD ? RTM_OLDADD : RTM_OLDDEL),
E 75
		   &(entry->rt_dst), &(entry->rt_gateway),
D 54
		   netmask, (struct sockaddr *)error, entry->rt_flags);
E 54
I 54
D 60
		   netmask, (struct sockaddr *)0, entry->rt_flags, error);
E 60
I 60
D 75
		   netmask, SA(0), entry->rt_flags, error);
E 75
I 75
		   netmask, SA(0), entry->rt_flags, error); */
E 75
E 60
E 54
	return (error);
#endif
E 79
}
I 61

struct ifaddr *
ifa_ifwithroute(flags, dst, gateway)
D 80
int	flags;
struct sockaddr	*dst, *gateway;
E 80
I 80
	int flags;
	struct sockaddr	*dst, *gateway;
E 80
{
D 68
	struct ifaddr *ifa;
E 68
I 68
	register struct ifaddr *ifa;
E 68
	if ((flags & RTF_GATEWAY) == 0) {
		/*
		 * If we are adding a route to an interface,
		 * and the interface is a pt to pt link
		 * we should search for the destination
		 * as our clue to the interface.  Otherwise
		 * we can use the local address.
		 */
		ifa = 0;
		if (flags & RTF_HOST) 
			ifa = ifa_ifwithdstaddr(dst);
		if (ifa == 0)
			ifa = ifa_ifwithaddr(gateway);
	} else {
		/*
		 * If we are adding a route to a remote net
		 * or host, the gateway may still be on the
		 * other end of a pt to pt link.
		 */
		ifa = ifa_ifwithdstaddr(gateway);
	}
	if (ifa == 0)
		ifa = ifa_ifwithnet(gateway);
I 68
D 88
	if (ifa == 0) {
		struct rtentry *rt = rtalloc1(dst, 0);
		if (rt == 0)
			return (0);
		rt->rt_refcnt--;
		if ((ifa = rt->rt_ifa) == 0)
			return (0);
	}
	if (ifa->ifa_addr->sa_family != dst->sa_family) {
D 80
		struct ifaddr *oifa = ifa, *ifaof_ifpforaddr();
E 80
I 80
		struct ifaddr *oifa = ifa;
E 80
		ifa = ifaof_ifpforaddr(dst, ifa->ifa_ifp);
		if (ifa == 0)
			ifa = oifa;
	}
E 88
E 68
	return (ifa);
}

I 86
int
rtgateinfo(info)
	register struct rt_addrinfo *info;
{
	struct ifaddr *ifa;
	struct ifnet *ifp;
	int error = 0;
/* Sleazy use of local variables throughout this function and next, XXX!!!! */
#define dst	info->rti_info[RTAX_DST]
#define gateway	info->rti_info[RTAX_GATEWAY]
#define netmask	info->rti_info[RTAX_NETMASK]
#define ifaaddr	info->rti_info[RTAX_IFA]
#define ifpaddr	info->rti_info[RTAX_IFP]
#define flags	info->rti_flags

	/* ifp may be specified by sockaddr_dl
		   when protcol address is ambiguous */
	if (info->rti_ifp == 0 && ifpaddr) {
		ifa = ifa_ifwithnet(ifpaddr);
		info->rti_ifp = ifa ? ifa->ifa_ifp : 0;
	}
	if (info->rti_ifa == 0) {
		struct sockaddr *sa;
		if (ifp = info->rti_ifp) {
			sa = ifaaddr ? ifaaddr : (gateway ? gateway : dst);
			info->rti_ifa = ifaof_ifpforaddr(sa, ifp);
		} else
			info->rti_ifa = ifa_ifwithroute(flags, dst, gateway);
	}
	if (ifa = info->rti_ifa) {
		if (info->rti_ifp == 0)
			info->rti_ifp = ifa->ifa_ifp;
		if (gateway == 0)
		    gateway = ifa->ifa_addr;
	} else
		error = ENETUNREACH;
	return error;
}


E 86
E 61
I 58
D 63
#define ROUNDUP(a) (1 + (((a) - 1) | (sizeof(long) - 1)))
E 63
I 63
D 88
#define ROUNDUP(a) (a>0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
E 63
E 58

E 88
I 80
int
E 80
D 86
rtrequest(req, dst, gateway, netmask, flags, ret_nrt)
	int req, flags;
	struct sockaddr *dst, *gateway, *netmask;
E 86
I 86
rtrequest1(req, info, ret_nrt)
	int req;
	register struct rt_addrinfo *info;
E 86
	struct rtentry **ret_nrt;
{
I 88
	struct rt_addrinfo info;

	bzero((caddr_t)&info, sizeof(info));
	info.rti_flags = flags;
	info.rti_info[RTAX_DST] = dst;
	info.rti_info[RTAX_GATEWAY] = gateway;
	info.rti_info[RTAX_NETMASK] = netmask;
	return rtrequest1(req, &info, ret_nrt);
}

/*
 * These (questionable) definitions of apparent local variables apply
 * to the next two functions.  XXXXXX!!!
 */
#define dst	info->rti_info[RTAX_DST]
#define gateway	info->rti_info[RTAX_GATEWAY]
#define netmask	info->rti_info[RTAX_NETMASK]
#define ifaaddr	info->rti_info[RTAX_IFA]
#define ifpaddr	info->rti_info[RTAX_IFP]
#define flags	info->rti_flags

int
rt_getifa(info)
	register struct rt_addrinfo *info;
{
	struct ifaddr *ifa;
	int error = 0;

	/* ifp may be specified by sockaddr_dl
		   when protocol address is ambiguous */
	if (info->rti_ifp == 0 && ifpaddr && ifpaddr->sa_family == AF_LINK) {
		ifa = ifa_ifwithnet(ifpaddr);
		info->rti_ifp = ifa ? ifa->ifa_ifp : 0;
	}
	if (info->rti_ifa == 0) {
		struct sockaddr *sa;

		sa = ifaaddr ? ifaaddr : (gateway ? gateway : dst);
		if (sa && info->rti_ifp)
			info->rti_ifa = ifaof_ifpforaddr(sa, info->rti_ifp);
		else if (dst && gateway)
			info->rti_ifa = ifa_ifwithroute(flags, dst, gateway);
		else if (sa)
			info->rti_ifa = ifa_ifwithroute(flags, sa, sa);
	}
	if (ifa = info->rti_ifa) {
		if (info->rti_ifp == 0)
			info->rti_ifp = ifa->ifa_ifp;
	} else
		error = ENETUNREACH;
	return error;
}

int
rtrequest1(req, info, ret_nrt)
	int req;
	register struct rt_addrinfo *info;
	struct rtentry **ret_nrt;
{
E 88
D 69
	int s = splnet(), len, error = 0;
E 69
I 69
	int s = splnet(); int error = 0;
E 69
	register struct rtentry *rt;
	register struct radix_node *rn;
	register struct radix_node_head *rnh;
D 80
	struct ifaddr *ifa, *ifa_ifwithdstaddr();
E 80
I 80
D 86
	struct ifaddr *ifa;
E 86
E 80
I 58
	struct sockaddr *ndst;
I 86
	struct ifaddr *ifa = info->rti_ifa;
	struct ifnet *ifp;
E 86
E 58
D 70
	u_char af = dst->sa_family;
E 70
I 58
#define senderr(x) { error = x ; goto bad; }
I 86
#define RTE(x) ((struct rtentry *)x)
E 86
E 58

E 53
I 52
D 76
	if (rtinits_done == 0)
		rtinitheads();
E 76
E 52
E 51
I 3
D 11
COUNT(RTREQUEST);
E 11
I 10
D 53
	af = entry->rt_dst.sa_family;
E 53
E 10
I 7
D 52
	if (af >= AF_MAX)
		return (EAFNOSUPPORT);
E 7
E 3
D 10
	(*afswitch[af].af_hash)(sa, &h);
D 4
	mprev = &routehash[h.afh_hosthash % RTHASHSIZ];
	key = h.afh_hostkey;
E 4
I 4
D 9
	hash = h.afh_hosthash;
I 5
	mprev = &rthost[hash % RTHASHSIZ];
E 5
E 4
	doinghost = 1;
E 9
I 9
	doinghost = new->rt_flags & RTF_HOST;
	if (doinghost) {
E 10
I 10
	(*afswitch[af].af_hash)(&entry->rt_dst, &h);
	if (entry->rt_flags & RTF_HOST) {
E 10
		hash = h.afh_hosthash;
D 28
		mprev = &rthost[hash % RTHASHSIZ];
E 28
I 28
		mprev = &rthost[RTHASHMOD(hash)];
E 52
I 52
D 70
	for (rnh = radix_node_head; rnh && (af != rnh->rnh_af); )
		rnh = rnh->rnh_next;
D 58
	if (rnh == 0) {
		error = ESRCH;
		goto bad;
	}
E 58
I 58
	if (rnh == 0)
E 70
I 70
	if ((rnh = rt_tables[dst->sa_family]) == 0)
E 70
D 88
		senderr(ESRCH);
E 88
I 88
		senderr(EAFNOSUPPORT);
E 88
	if (flags & RTF_HOST)
		netmask = 0;
E 58
D 53
	head = rnh->rnh_treetop;
	if ((entry->rt_flags & RTF_GATEWAY) == 0) {
		/*
		 * If we are adding a route to an interface,
		 * and the interface is a pt to pt link
		 * we should search for the destination
		 * as our clue to the interface.  Otherwise
		 * we can use the local address.
		 */
		ifa = 0;
		if (entry->rt_flags & RTF_HOST) 
			ifa = ifa_ifwithdstaddr(&entry->rt_dst);
		if (ifa == 0)
			ifa = ifa_ifwithaddr(&entry->rt_gateway);
E 52
E 28
	} else {
D 52
		hash = h.afh_nethash;
D 28
		mprev = &rtnet[hash % RTHASHSIZ];
E 28
I 28
		mprev = &rtnet[RTHASHMOD(hash)];
E 52
I 52
		/*
		 * If we are adding a route to a remote net
		 * or host, the gateway may still be on the
		 * other end of a pt to pt link.
		 */
		ifa = ifa_ifwithdstaddr(&entry->rt_gateway);
E 52
E 28
	}
D 52
	match = afswitch[af].af_netmatch;
E 9
I 3
	s = splimp();
E 3
D 9
again:
E 9
I 4
D 5
	mprev = &routehash[hash % RTHASHSIZ];
E 5
E 4
D 36
	for (; m = *mprev; mprev = &m->m_next) {
E 36
I 36
	for (mfirst = mprev; m = *mprev; mprev = &m->m_next) {
E 36
		rt = mtod(m, struct rtentry *);
D 4
		if (rt->rt_key != key)
E 4
I 4
D 5
		if (rt->rt_hash[doinghost] != hash)
E 5
I 5
		if (rt->rt_hash != hash)
E 5
E 4
			continue;
D 10
		if (doinghost) {
D 2
			if (!equal(&rt->rt_dst, dst))
E 2
I 2
D 5
			if (!equal(&rt->rt_dst, &new->rt_dst))
E 5
I 5
			if (!equal(&rt->rt_dst, sa))
E 10
I 10
		if (entry->rt_flags & RTF_HOST) {
D 36
#define	equal(a1, a2) \
	(bcmp((caddr_t)(a1), (caddr_t)(a2), sizeof (struct sockaddr)) == 0)
E 36
			if (!equal(&rt->rt_dst, &entry->rt_dst))
E 10
E 5
E 2
				continue;
		} else {
D 5
			if (rt->rt_dst.sa_family != af)
E 5
I 5
D 10
			if (rt->rt_dst.sa_family != sa->sa_family ||
			    (*match)(&rt->rt_dst, sa) == 0)
E 10
I 10
			if (rt->rt_dst.sa_family != entry->rt_dst.sa_family ||
			    (*match)(&rt->rt_dst, &entry->rt_dst) == 0)
E 10
E 5
				continue;
E 52
I 52
	if (ifa == 0) {
		ifa = ifa_ifwithnet(&entry->rt_gateway);
		if (ifa == 0 && req == SIOCADDRT) {
			error = ENETUNREACH;
			goto bad;
E 52
D 5
			if ((*afswitch[af].af_netmatch)(&rt->rt_dst, sa) == 0)
				continue;
E 5
		}
I 3
D 9
		/* require full match on deletions */
D 5
		if (req == SIOCDELRT &&
		    !equal(&rt->rt_gateway, &new->rt_gateway))
E 5
I 5
		if (req == SIOCDELRT && !equal(&rt->rt_gateway, gate))
E 5
			continue;
		/* don't keep multiple identical entries */
D 5
		if (req == SIOCADDRT &&
		    equal(&rt->rt_gateway, &new->rt_gateway)) {
E 5
I 5
		if (req == SIOCADDRT && equal(&rt->rt_gateway, gate)) {
E 5
			error = EEXIST;
			goto bad;
		}
E 3
		break;
E 9
I 9
D 10
		if (equal(&rt->rt_gateway, gate))
E 10
I 10
D 52
		if (equal(&rt->rt_gateway, &entry->rt_gateway))
E 10
			break;
E 52
E 9
	}
I 52
	if (entry->rt_flags & RTF_HOST)
		netmask = 0;
	else
		netmask = rtgetmask(&entry->rt_dst, ifa);
E 53
E 52
D 9
	if (m == 0 && doinghost) {
D 5
		doinghost = 0;
E 5
D 4
		mprev = &routehash[h.afh_nethash % RTHASHSIZ];
		key = h.afh_netkey;
E 4
I 4
		hash = h.afh_nethash;
I 6
		oldmprev = mprev;
E 6
I 5
		mprev = &rtnet[hash % RTHASHSIZ];
		match = afswitch[af].af_netmatch;
		doinghost = 0;
E 5
E 4
		goto again;
	}
I 5

E 5
D 4

E 4
D 3
	if (m == 0 && req != SIOCADDRT)
D 2
		return (ESEARCH);
E 2
I 2
		return (ESRCH);
E 3
I 3
	if (m == 0 && req != SIOCADDRT) {
		error = ESRCH;
		goto bad;
	}
I 5
found:
E 9
E 5
E 3
E 2
	switch (req) {
I 88
	case RTM_DELPKT:
		if (rnh->rnh_deladdr == 0)
			senderr(EOPNOTSUPP);
		rn = rnh->rnh_delpkt(info->rti_pkthdr, (caddr_t)info, rnh);
		goto delete;
E 88
D 53

	case SIOCDELRT:
I 9
D 52
		if (m == 0) {
E 52
I 52
		if ((rn = rn_delete((char *)&entry->rt_dst,
					netmask, head)) == 0) {
E 53
I 53
	case RTM_DELETE:
D 58
		if ((rn = rn_delete((caddr_t)dst, (caddr_t)netmask, 
					rnh->rnh_treetop)) == 0) {
E 53
E 52
			error = ESRCH;
			goto bad;
E 58
I 58
D 69
		if (ret_nrt && (rt = *ret_nrt)) {
			RTFREE(rt);
			*ret_nrt = 0;
E 58
		}
E 69
I 58
D 70
		if ((rn = rn_delete((caddr_t)dst, (caddr_t)netmask, 
E 70
I 70
D 79
		if ((rn = rnh->rnh_delete((caddr_t)dst, (caddr_t)netmask, 
E 70
					rnh->rnh_treetop)) == 0)
E 79
I 79
D 80
		if ((rn = rnh->rnh_deladdr((caddr_t)dst, (caddr_t)netmask, 
					rnh)) == 0)
E 80
I 80
D 86
D 88
		if ((rn = rnh->rnh_deladdr(dst, netmask, rnh)) == 0)
E 88
I 88
		rn = rnh->rnh_deladdr(dst, netmask, rnh);
	delete:
		if (rn == 0)
E 88
E 86
I 86
		if ((ifaaddr || ifpaddr) && rnh->rnh_delete1) {
			extern struct radix_node_head *mask_rnhead;
			if (error = rtgateinfo(info))
				senderr(error);
			ifa = info->rti_ifa;
			ifp = info->rti_ifp;
			if (netmask && (rn = rn_search(netmask,
                                            mask_rnhead->rnh_treetop)))
                                netmask = SA(rn->rn_key);
			for (rn = rnh->rnh_matchaddr(dst, rnh); rn;
						    rn = rn->rn_dupedkey) {
				/* following test includes case netmask == 0 */
				if (SA(rn->rn_mask) == netmask &&
				    ((ifaaddr && ifa == RTE(rn)->rt_ifa) ||
				     (!ifaaddr && ifp == RTE(rn)->rt_ifp)))
					break;
			if (rn == 0 || (rn = rnh->rnh_delete1(rn, rnh)) == 0)
				senderr(ESRCH);
			}
		} else if ((rn = rnh->rnh_deladdr(dst, netmask, rnh)) == 0)
E 86
E 80
E 79
			senderr(ESRCH);
E 58
E 9
D 10
		rt->rt_flags &= ~RTF_UP;
		if (rt->rt_refcnt > 0)	/* should we notify protocols? */
D 3
			break;
		*mprev = m_free(m);
E 3
I 3
			error = EBUSY;
		else
			*mprev = m_free(m);
E 3
		break;

	case SIOCCHGRT:
I 9
		if (m == 0) {
			error = ESRCH;
			goto bad;
		}
E 9
		rt->rt_flags = new->rt_flags;
E 10
I 10
D 52
		*mprev = m->m_next;
E 10
D 9
		if (rt->rt_refcnt > 0)
E 9
I 9
		if (rt->rt_refcnt > 0) {
E 9
D 2
			return (EINUSE);
E 2
I 2
D 3
			return (EBUSY);
E 2
		if (!equal(&rt->rt_gateway, &new->rt_gateway))
E 3
I 3
D 10
			error = EBUSY;
D 5
		else if (!equal(&rt->rt_gateway, &new->rt_gateway))
E 5
I 5
D 9
		else if (!equal(&rt->rt_gateway, gate))
E 5
E 3
			goto newneighbor;
E 9
I 9
			goto bad;
		}
		if (!equal(&rt->rt_gateway, gate))
			goto changerouter;
E 10
I 10
			rt->rt_flags &= ~RTF_UP;
E 52
I 52
		if (rn->rn_flags & (RNF_ACTIVE | RNF_ROOT))
			panic ("rtrequest delete");
D 53
		nrt = (struct nrtentry *)rn;
		nrt->nrt_rt.rt_flags &= ~RTF_UP;
		if (nrt->nrt_rt.rt_refcnt > 0)
E 53
I 53
D 86
		rt = (struct rtentry *)rn;
E 86
I 86
		rt = RTE(rn);
E 86
		rt->rt_flags &= ~RTF_UP;
I 69
		if (rt->rt_gwroute) {
			rt = rt->rt_gwroute; RTFREE(rt);
D 86
			(rt = (struct rtentry *)rn)->rt_gwroute = 0;
E 86
I 86
			(rt = RTE(rn))->rt_gwroute = 0;
E 86
		}
E 69
D 58
		if (rt->rt_refcnt > 0)
E 53
E 52
			rttrash++;
D 52
			m->m_next = 0;
		} else
			(void) m_free(m);
E 52
I 52
		else 
D 53
			free((caddr_t)nrt, M_RTABLE);
E 53
I 53
			free((caddr_t)rt, M_RTABLE);
E 58
I 58
		if ((ifa = rt->rt_ifa) && ifa->ifa_rtrequest)
D 60
			ifa->ifa_rtrequest(RTM_DELETE, rt, (struct sockaddr *)0);
E 60
I 60
D 86
D 88
			ifa->ifa_rtrequest(RTM_DELETE, rt, SA(0));
E 88
I 88
			ifa->ifa_rtrequest(req, rt, info);
E 88
E 86
I 86
			ifa->ifa_rtrequest(RTM_DELETE, rt, info);
E 86
E 60
		rttrash++;
D 75
		if (rt->rt_refcnt <= 0)
E 75
I 75
		if (ret_nrt)
			*ret_nrt = rt;
D 77
		else if (rt->rt_refcnt <= 0)
E 77
I 77
		else if (rt->rt_refcnt <= 0) {
			rt->rt_refcnt++;
E 77
E 75
			rtfree(rt);
I 77
		}
E 77
E 58
E 53
E 52
E 10
E 9
		break;

I 60
D 86
	case RTM_RESOLVE:
D 61
		if (ret_nrt== 0 || (rt = *ret_nrt) == 0)
E 61
I 61
		if (ret_nrt == 0 || (rt = *ret_nrt) == 0)
E 61
			senderr(EINVAL);
		ifa = rt->rt_ifa;
		flags = rt->rt_flags & ~RTF_CLONING;
		gateway = rt->rt_gateway;
		if ((netmask = rt->rt_genmask) == 0)
			flags |= RTF_HOST;
		goto makeroute;
E 86

I 88
	case RTM_ADDPKT:
		if (rnh->rnh_addpkt == 0)
			senderr(EOPNOTSUPP);
		/*FALLTHROUGH*/
E 88
E 60
D 53
	case SIOCADDRT:
I 9
D 10
		if (m != 0) {
E 10
I 10
D 52
		if (m) {
E 10
			error = EEXIST;
E 52
I 52
		Malloc(nrt, struct nrtentry *, sizeof *nrt);
		if (nrt == 0) {
E 53
I 53
	case RTM_ADD:
D 61
		if ((flags & RTF_GATEWAY) == 0) {
			/*
			 * If we are adding a route to an interface,
			 * and the interface is a pt to pt link
			 * we should search for the destination
			 * as our clue to the interface.  Otherwise
			 * we can use the local address.
			 */
			ifa = 0;
			if (flags & RTF_HOST) 
				ifa = ifa_ifwithdstaddr(dst);
			if (ifa == 0)
				ifa = ifa_ifwithaddr(gateway);
		} else {
			/*
			 * If we are adding a route to a remote net
			 * or host, the gateway may still be on the
			 * other end of a pt to pt link.
			 */
			ifa = ifa_ifwithdstaddr(gateway);
		}
		if (ifa == 0) {
			ifa = ifa_ifwithnet(gateway);
D 58
			if (ifa == 0 && req == RTM_ADD) {
				error = ENETUNREACH;
				goto bad;
			}
E 58
I 58
			if (ifa == 0 && req == RTM_ADD)
				senderr(ENETUNREACH);
E 58
		}
D 60
		len = sizeof (*rt) + ROUNDUP(gateway->sa_len)
E 60
I 60
    makeroute: len = sizeof (*rt) + ROUNDUP(gateway->sa_len)
E 60
D 58
						+ ROUNDUP(dst->sa_len);
E 58
I 58
		    + ROUNDUP(dst->sa_len) + ROUNDUP(ifa->ifa_llinfolen);
E 61
I 61
D 86
D 88
		if ((ifa = ifa_ifwithroute(flags, dst, gateway)) == 0)
			senderr(ENETUNREACH);
E 88
I 88
		if (info->rti_ifa == 0 && (error = rt_getifa(info)))
			senderr(error);
		ifa = info->rti_ifa;
E 88
	makeroute:
E 86
I 86
		if (ifa == 0) {
			if (error = rtgateinfo(info))
				senderr(error);
			ifa = info->rti_ifa;
		}
	case RTM_RESOLVE:
E 86
D 69
		len = sizeof (*rt) + ROUNDUP(gateway->sa_len)
		    + ROUNDUP(dst->sa_len);
E 61
E 58
		R_Malloc(rt, struct rtentry *, len);
E 69
I 69
		R_Malloc(rt, struct rtentry *, sizeof(*rt));
E 69
D 58
		if (rt == 0) {
E 53
			error = ENOBUFS;
E 52
			goto bad;
		}
E 58
I 58
		if (rt == 0)
			senderr(ENOBUFS);
E 58
I 10
D 32
		ifp = if_ifwithaddr(&entry->rt_gateway);
		if (ifp == 0) {
			ifp = if_ifwithnet(&entry->rt_gateway);
			if (ifp == 0) {
E 32
I 32
D 35
		ifa = ifa_ifwithaddr(&entry->rt_gateway);
E 35
I 35
D 36
		/*
		 * If we are adding a route to an interface,
		 * and the interface is a pt to pt link
		 * we should search for the destination
		 * as our clue to the interface.  Otherwise
		 * we can use the local address.
		 */
		if ((entry->rt_flags & RTF_GATEWAY)==0) {
E 36
I 36
D 52
		if ((entry->rt_flags & RTF_GATEWAY) == 0) {
			/*
			 * If we are adding a route to an interface,
			 * and the interface is a pt to pt link
			 * we should search for the destination
			 * as our clue to the interface.  Otherwise
			 * we can use the local address.
			 */
I 45
			ifa = 0;
E 45
E 36
			if (entry->rt_flags & RTF_HOST) 
				ifa = ifa_ifwithdstaddr(&entry->rt_dst);
D 45
			else
E 45
I 45
			if (ifa == 0)
E 45
				ifa = ifa_ifwithaddr(&entry->rt_gateway);
		} else {
D 36
		/* If we are adding a route to a remote net
		 * or host, the gateway may still be on the
		 * other end of a pt to pt link.
		 */
E 36
I 36
			/*
			 * If we are adding a route to a remote net
			 * or host, the gateway may still be on the
			 * other end of a pt to pt link.
			 */
E 36
			ifa = ifa_ifwithdstaddr(&entry->rt_gateway);
		}
E 35
		if (ifa == 0) {
			ifa = ifa_ifwithnet(&entry->rt_gateway);
			if (ifa == 0) {
E 32
				error = ENETUNREACH;
				goto bad;
			}
		}
E 10
E 9
D 4
		m = m_getclr(M_DONTWAIT);
E 4
I 4
D 14
		m = m_get(M_DONTWAIT);
E 14
I 14
		m = m_get(M_DONTWAIT, MT_RTABLE);
E 14
E 4
D 3
		if (m == 0)
			return (ENOBUFS);
E 3
I 3
		if (m == 0) {
			error = ENOBUFS;
E 52
I 52
D 53
		Bzero(nrt, sizeof *nrt);
		rn = rn_addroute((char *)&entry->rt_dst, netmask,
						    head, nrt->nrt_nodes);
E 53
I 53
D 69
		Bzero(rt, len);
D 58
		rn = rn_addroute((caddr_t)dst, (caddr_t)netmask,
E 58
I 58
		ndst = (struct sockaddr *)(rt + 1);
E 69
I 69
		Bzero(rt, sizeof(*rt));
		rt->rt_flags = RTF_UP | flags;
		if (rt_setgate(rt, dst, gateway)) {
			Free(rt);
			senderr(ENOBUFS);
		}
I 88
		if (req == RTM_ADDPKT) {
			rn = rnh->rnh_addpkt(info->rti_pkthdr, (caddr_t)info,
						rnh, rt->rt_nodes);
			goto add; /* addpkt() must allocate space */
		}
E 88
		ndst = rt_key(rt);
E 69
		if (netmask) {
			rt_maskedcopy(dst, ndst, netmask);
		} else
			Bcopy(dst, ndst, dst->sa_len);
D 70
		rn = rn_addroute((caddr_t)ndst, (caddr_t)netmask,
E 70
I 70
D 79
		rn = rnh->rnh_add((caddr_t)ndst, (caddr_t)netmask,
E 70
E 58
					rnh->rnh_treetop, rt->rt_nodes);
E 79
I 79
		rn = rnh->rnh_addaddr((caddr_t)ndst, (caddr_t)netmask,
					rnh, rt->rt_nodes);
I 88
	add:
E 88
E 79
E 53
		if (rn == 0) {
D 53
			free((caddr_t)nrt, M_RTABLE);
E 53
I 53
D 69
			free((caddr_t)rt, M_RTABLE);
E 69
I 69
			if (rt->rt_gwroute)
				rtfree(rt->rt_gwroute);
I 71
			Free(rt_key(rt));
E 71
			Free(rt);
E 69
E 53
D 58
			error = EEXIST;
E 52
D 9
			break;
E 9
I 9
			goto bad;
E 58
I 58
			senderr(EEXIST);
E 58
E 9
		}
I 72
		ifa->ifa_refcnt++;
E 72
I 10
D 36
		*mprev = m;
E 36
I 36
D 52
		m->m_next = *mfirst;
		*mfirst = m;
E 36
E 10
E 3
D 50
		m->m_off = MMINOFF;
E 50
I 4
		m->m_len = sizeof (struct rtentry);
E 4
D 6
		*mprev = m;
E 6
		rt = mtod(m, struct rtentry *);
D 10
		*rt = *new;
E 10
D 4
		rt->rt_key = h.afh_nethash | h.afh_hosthash;
E 4
I 4
D 5
		rt->rt_hash[0] = h.afh_nethash;
		rt->rt_hash[1] = h.afh_hosthash;
E 5
I 5
D 6
		rt->rt_hash = new->rt_flags & RTF_HOST ?
			h.afh_hosthash : h.afh_nethash;
E 6
I 6
D 9
		if (new->rt_flags & RTF_HOST) {
			rt->rt_hash = h.afh_hosthash;
			*oldmprev = m;
		} else {
			rt->rt_hash = h.afh_nethash;
			*mprev = m;
		}
E 9
I 9
		rt->rt_hash = hash;
E 52
I 52
D 53
		rt = &nrt->nrt_rt;
		rn->rn_key = (char *)&(nrt->nrt_rt.rt_dst);
E 52
D 10
		*mprev = m;
E 9
E 6
		rt->rt_use = 0;
E 10
I 10
		rt->rt_dst = entry->rt_dst;
		rt->rt_gateway = entry->rt_gateway;
D 36
		rt->rt_flags =
		    RTF_UP | (entry->rt_flags & (RTF_HOST|RTF_GATEWAY));
E 36
I 36
		rt->rt_flags = RTF_UP |
		    (entry->rt_flags & (RTF_HOST|RTF_GATEWAY|RTF_DYNAMIC));
E 53
I 53
D 58
		if (ret_nrt)
			*ret_nrt = rt; /* == (struct rtentry *)rn */
E 58
D 60
		rt->rt_ifp = ifa->ifa_ifp;
E 60
I 54
		rt->rt_ifa = ifa;
E 54
E 53
E 36
E 10
D 52
		rt->rt_refcnt = 0;
E 52
E 5
E 4
D 9
newneighbor:
E 9
I 9
D 10
changerouter:
E 9
D 4
		rt->rt_ifp = if_ifonnetof(&new->rt_gateway);
E 4
I 4
D 5
		rt->rt_ifp = if_ifwithnet(&new->rt_gateway);
E 5
I 5
		rt->rt_ifp = if_ifwithnet(gate);
E 5
E 4
		if (rt->rt_ifp == 0)
			rt->rt_flags &= ~RTF_UP;
E 10
I 10
D 58
		rt->rt_use = 0;
I 52
		rt->rt_refcnt = 0;
E 52
D 32
		rt->rt_ifp = ifp;
E 32
I 32
D 53
		rt->rt_ifp = ifa->ifa_ifp;
E 53
I 53
		rt->rt_flags = RTF_UP |
		    (flags & (RTF_HOST|RTF_GATEWAY|RTF_DYNAMIC));
		rn->rn_key = (caddr_t) (rt + 1); /* == rt_dst */
		Bcopy(dst, rn->rn_key, dst->sa_len);
E 58
I 58
D 60
		if (ret_nrt) {
			*ret_nrt = rt;
			rt->rt_refcnt++;
		}
E 60
I 60
		rt->rt_ifp = ifa->ifa_ifp;
E 60
D 69
		rt->rt_flags = RTF_UP | flags;
D 63
		rn->rn_key = (caddr_t) ndst; /* == rt_dst */
E 63
E 58
		rt->rt_gateway = (struct sockaddr *)
					(rn->rn_key + ROUNDUP(dst->sa_len));
		Bcopy(gateway, rt->rt_gateway, gateway->sa_len);
E 69
I 58
D 59
		rt->rt_llinfo = ROUNDUP(gateway->sa_len) + (caddr_t)gateway;
E 59
I 59
D 61
		rt->rt_llinfo = ROUNDUP(gateway->sa_len)
					+ (caddr_t)rt->rt_gateway;
E 61
I 60
D 86
		if (req == RTM_RESOLVE)
			rt->rt_rmx = (*ret_nrt)->rt_rmx; /* copy metrics */
E 86
E 60
E 59
		if (ifa->ifa_rtrequest)
D 60
			ifa->ifa_rtrequest(RTM_ADD, rt, (struct sockaddr *)0);
E 60
I 60
D 86
D 88
			ifa->ifa_rtrequest(req, rt, SA(ret_nrt ? *ret_nrt : 0));
E 88
I 88
			ifa->ifa_rtrequest(req, rt, info);
E 88
E 86
I 86
			ifa->ifa_rtrequest(req, rt, info);
E 86
		if (ret_nrt) {
			*ret_nrt = rt;
			rt->rt_refcnt++;
		}
E 60
E 58
E 53
E 32
E 10
I 4
D 5
		rt->rt_use = 0;
E 4
		rt->rt_refcnt = 0;
E 5
		break;
I 88
	default:
		error = EOPNOTSUPP;
E 88
	}
D 3
	return (0);
E 3
I 3
bad:
	splx(s);
	return (error);
I 88
#undef dst
#undef gateway
#undef netmask
#undef ifaaddr
#undef ifpaddr
#undef flags
E 88
I 86
#undef dst
#undef gateway
#undef netmask
#undef ifaaddr
#undef ifpaddr
#undef flags
}

int
rtrequest(req, dst, gateway, netmask, flags, ret_nrt)
	int req, flags;
	struct sockaddr *dst, *gateway, *netmask;
	struct rtentry **ret_nrt;
{
	struct rt_addrinfo info;

	bzero((caddr_t)&info, sizeof(info));
	info.rti_flags = flags;
	info.rti_info[RTAX_DST] = dst;
	info.rti_info[RTAX_GATEWAY] = gateway;
	info.rti_info[RTAX_NETMASK] = netmask;
	return rtrequest1(req, info, ret_nrt);
E 86
I 4
}
I 88
#define ROUNDUP(a) (a>0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
E 88
I 58

I 80
int
E 80
I 69
rt_setgate(rt0, dst, gate)
D 80
struct rtentry *rt0;
struct sockaddr *dst, *gate;
E 80
I 80
	struct rtentry *rt0;
	struct sockaddr *dst, *gate;
E 80
{
	caddr_t new, old;
	int dlen = ROUNDUP(dst->sa_len), glen = ROUNDUP(gate->sa_len);
	register struct rtentry *rt = rt0;

	if (rt->rt_gateway == 0 || glen > ROUNDUP(rt->rt_gateway->sa_len)) {
		old = (caddr_t)rt_key(rt);
		R_Malloc(new, caddr_t, dlen + glen);
		if (new == 0)
			return 1;
		rt->rt_nodes->rn_key = new;
	} else {
		new = rt->rt_nodes->rn_key;
		old = 0;
	}
	Bcopy(gate, (rt->rt_gateway = (struct sockaddr *)(new + dlen)), glen);
	if (old) {
		Bcopy(dst, new, dlen);
		Free(old);
	}
	if (rt->rt_gwroute) {
		rt = rt->rt_gwroute; RTFREE(rt);
		rt = rt0; rt->rt_gwroute = 0;
	}
D 88
	if (rt->rt_flags & RTF_GATEWAY) {
		rt->rt_gwroute = rtalloc1(gate, 1);
	}
E 88
	return 0;
}

I 80
void
E 80
E 69
rt_maskedcopy(src, dst, netmask)
D 80
struct sockaddr *src, *dst, *netmask;
E 80
I 80
	struct sockaddr *src, *dst, *netmask;
E 80
{
D 59
	register caddr_t cp1 = (caddr_t)src, cp2 = (caddr_t)dst,
	    cp3 = 2 + (caddr_t)netmask, cplim = cp1 + *(u_char *)cp1;
E 59
I 59
	register u_char *cp1 = (u_char *)src;
	register u_char *cp2 = (u_char *)dst;
	register u_char *cp3 = (u_char *)netmask;
	u_char *cplim = cp2 + *cp3;
	u_char *cplim2 = cp2 + *cp1;
E 59

	*cp2++ = *cp1++; *cp2++ = *cp1++; /* copies sa_len & sa_family */
D 59
	while (cp1 < cplim)
E 59
I 59
	cp3 += 2;
	if (cplim > cplim2)
		cplim = cplim2;
	while (cp2 < cplim)
E 59
		*cp2++ = *cp1++ & *cp3++;
I 59
	if (cp2 < cplim2)
		bzero((caddr_t)cp2, (unsigned)(cplim2 - cp2));
E 59
}
I 83

E 83
E 58
D 53

E 53
/*
 * Set up a routing table entry, normally
 * for an interface.
 */
I 80
int
E 80
D 37
rtinit(dst, gateway, flags)
E 37
I 37
D 53
rtinit(dst, gateway, cmd, flags)
E 37
	struct sockaddr *dst, *gateway;
E 53
I 53
rtinit(ifa, cmd, flags)
	register struct ifaddr *ifa;
E 53
D 37
	int flags;
E 37
I 37
	int cmd, flags;
E 37
{
D 53
	struct rtentry route;
E 53
I 53
D 54
	struct sockaddr net, *netp;
E 54
I 54
D 58
	struct sockaddr net, *netp = &net;
E 54
	register caddr_t cp, cp2, cp3;
	caddr_t cplim, freeit = 0;
	int len;
E 53
I 19
D 37
	int cmd;
E 37
E 19
D 13
	struct route ro;
E 13

I 19
D 37
	if (flags == -1) {
		cmd = (int)SIOCDELRT;
		flags = 0;
	} else {
		cmd = (int)SIOCADDRT;
	}
E 37
E 19
I 10
D 53
	bzero((caddr_t)&route, sizeof (route));
E 10
	route.rt_dst = *dst;
	route.rt_gateway = *gateway;
	route.rt_flags = flags;
D 10
	route.rt_use = 0;
E 10
D 13
	(void) rtrequest(SIOCADDRT, &route);
E 13
I 13
D 19
	(void) rtrequest((int)SIOCADDRT, &route);
E 19
I 19
	(void) rtrequest(cmd, &route);
E 53
I 53
	if (flags & RTF_HOST || ifa->ifa_netmask == 0) {
		(void) rtrequest(cmd, ifa->ifa_dstaddr, ifa->ifa_addr,
D 54
								0, flags, 0);
E 54
I 54
			    (struct sockaddr *)0, flags, (struct rtentry **)0);
E 54
	} else {
D 54
		if ((len = ifa->ifa_addr->sa_len) >= sizeof (net)) {
E 54
I 54
		if ((len = ifa->ifa_addr->sa_len) >= sizeof (*netp)) {
E 54
			R_Malloc(freeit, caddr_t, len);
			if (freeit == 0)
				return;
			netp = (struct sockaddr *)freeit;
		}
D 54
		netp->sa_len = len;
E 54
I 54
		bzero((caddr_t)netp, len);
		cp = (caddr_t) netp->sa_data;
		cp3 = (caddr_t) ifa->ifa_netmask->sa_data;
		cplim = ifa->ifa_netmask->sa_len +
					 (caddr_t) ifa->ifa_netmask;
E 54
		cp2 = 1 + (caddr_t)ifa->ifa_addr;
		netp->sa_family = *cp2++;
D 54
		cp3 = (caddr_t) ifa->ifa_netmask->sa_data;
		cp = (caddr_t) netp->sa_data;
		cplim = cp + len - 2;
		while (cp < cplim)
E 54
I 54
		netp->sa_len = len;
		while (cp3 < cplim)
E 54
			*cp++ = *cp2++ & *cp3++;
		(void) rtrequest(cmd, netp, ifa->ifa_addr, ifa->ifa_netmask,
D 54
					flags, 0);
E 54
I 54
				    flags, (struct rtentry **)0);
E 54
		if (freeit)
D 54
			Free(freeit);
E 54
I 54
			free((caddr_t)freeit, M_RTABLE);
E 54
	}
E 58
I 58
D 63
	return rtrequest(cmd, ifa->ifa_dstaddr, ifa->ifa_addr,
		    ifa->ifa_netmask, flags | ifa->ifa_flags, &ifa->ifa_rt);
E 63
I 63
D 64
	return
	    rtrequest(cmd, flags & RTF_HOST ? ifa->ifa_dstaddr : ifa->ifa_addr,
			ifa->ifa_addr, ifa->ifa_netmask,
E 64
I 64
	register struct rtentry *rt;
	register struct sockaddr *dst;
	register struct sockaddr *deldst;
	struct mbuf *m = 0;
I 75
	struct rtentry *nrt = 0;
I 88
	struct radix_node_head *rnh;
	struct radix_node *rn;
E 88
E 75
	int error;
I 88
	struct rt_addrinfo info;
E 88

	dst = flags & RTF_HOST ? ifa->ifa_dstaddr : ifa->ifa_addr;
D 69
	if (ifa->ifa_flags & IFA_ROUTE) {
		if ((rt = ifa->ifa_rt) && (rt->rt_flags & RTF_UP) == 0) {
			RTFREE(rt);
			ifa->ifa_rt = 0;
		}
E 69
I 69
D 75
	if (rt = ifa->ifa_rt) {
		rtfree(rt);
		ifa->ifa_rt = 0;
E 69
	}
E 75
	if (cmd == RTM_DELETE) {
		if ((flags & RTF_HOST) == 0 && ifa->ifa_netmask) {
			m = m_get(M_WAIT, MT_SONAME);
			deldst = mtod(m, struct sockaddr *);
			rt_maskedcopy(dst, deldst, ifa->ifa_netmask);
			dst = deldst;
		}
D 88
		if (rt = rtalloc1(dst, 0)) {
			rt->rt_refcnt--;
			if (rt->rt_ifa != ifa) {
				if (m)
					(void) m_free(m);
				return (flags & RTF_HOST ? EHOSTUNREACH
							: ENETUNREACH);
			}
E 88
I 88
		if ((rnh = rt_tables[dst->sa_family]) == 0 ||
		    (rn = rnh->rnh_lookup(dst, ifa->ifa_netmask, rnh)) == 0 ||
		    (rn->rn_flags & RNF_ROOT) != 0 ||
		    ((struct rtentry *)rn)->rt_ifa != ifa ||
		    !equal(rt_key(rt), dst))
		     {
			if (m)
				(void) m_free(m);
			return (flags & RTF_HOST ? EHOSTUNREACH : ENETUNREACH);
E 88
		}
	}
D 88
	error = rtrequest(cmd, dst, ifa->ifa_addr, ifa->ifa_netmask,
E 64
D 75
			flags | ifa->ifa_flags, &ifa->ifa_rt);
E 75
I 75
			flags | ifa->ifa_flags, &nrt);
E 88
I 88
	bzero((caddr_t)&info, sizeof(info));
	info.rti_ifa = ifa;
	info.rti_flags = flags | ifa->ifa_flags;
	info.rti_info[RTAX_DST] = dst;
	info.rti_info[RTAX_GATEWAY] = ifa->ifa_addr;
	info.rti_info[RTAX_NETMASK] = ifa->ifa_netmask;
	error = rtrequest1(cmd, &info, &nrt);

	if (error == 0 && (rt = nrt)) {
		rt_newaddrmsg(cmd, ifa, error, rt);
		if (cmd == RTM_DELETE) {
			if (rt->rt_refcnt <= 0) {
				rt->rt_refcnt++;
				rtfree(rt);
			}
		} else if (cmd == RTM_ADD)
			rt->rt_refcnt--;
	}
E 88
D 77
	rt_newaddrmsg(cmd, ifa, error, nrt);
E 77
E 75
I 64
	if (m)
		(void) m_free(m);
D 75
	if (cmd == RTM_ADD && error == 0 && (rt = ifa->ifa_rt)
						&& rt->rt_ifa != ifa) {
E 75
I 75
D 88
	if (cmd == RTM_DELETE && error == 0 && (rt = nrt)) {
D 77
		if (rt->rt_refcnt <= 0)
E 77
I 77
		rt_newaddrmsg(cmd, ifa, error, nrt);
		if (rt->rt_refcnt <= 0) {
			rt->rt_refcnt++;
E 77
			rtfree(rt);
I 77
		}
E 77
	}
	if (cmd == RTM_ADD && error == 0 && (rt = nrt)) {
E 75
D 77
		rt->rt_ifa = ifa;
		rt->rt_ifp = ifa->ifa_ifp;
E 77
I 75
		rt->rt_refcnt--;
I 77
		if (rt->rt_ifa != ifa) {
			printf("rtinit: wrong ifa (%x) was (%x)\n", ifa,
				rt->rt_ifa);
			if (rt->rt_ifa->ifa_rtrequest)
			    rt->rt_ifa->ifa_rtrequest(RTM_DELETE, rt, SA(0));
			IFAFREE(rt->rt_ifa);
			rt->rt_ifa = ifa;
			rt->rt_ifp = ifa->ifa_ifp;
			ifa->ifa_refcnt++;
			if (ifa->ifa_rtrequest)
			    ifa->ifa_rtrequest(RTM_ADD, rt, SA(0));
		}
		rt_newaddrmsg(cmd, ifa, error, nrt);
E 77
E 75
	}
E 88
	return (error);
E 64
E 63
E 58
E 53
E 19
E 13
D 10
	ro.ro_rt = 0;
	ro.ro_dst = *dst;
	rtalloc(&ro);
E 10
E 4
E 3
}
I 53
D 58
#include "radix.c"
E 58
E 53
E 1
