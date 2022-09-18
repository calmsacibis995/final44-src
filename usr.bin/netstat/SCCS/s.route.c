h25639
s 00092/00025/00622
d D 8.6 95/04/28 16:36:44 sklower 45 44
c includes many changes, including some of vixie's and karel's
e
s 00001/00001/00646
d D 8.5 94/11/08 19:15:22 sklower 44 43
c unnecessary & wrong arg to printf when citing normal masks
e
s 00008/00001/00639
d D 8.4 94/10/31 13:46:58 sklower 43 41
c optimization for normal masks requires keeping ptr
c to associated leaf, rather than just the mask itself
e
s 00000/00000/00640
d R 8.4 94/10/31 13:45:49 sklower 42 41
c optimization for normal masks requires keeping ptr to associated leaf,
e
s 00001/00001/00639
d D 8.3 94/03/09 17:48:29 sklower 41 40
c blooper in my fix
e
s 00007/00005/00633
d D 8.2 94/03/06 23:54:49 sklower 40 39
c fix from chris d.
e
s 00002/00002/00636
d D 8.1 93/06/06 15:44:16 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00637
d D 5.27 93/05/12 16:17:32 sklower 38 37
c fix from David Burren on name lookup of gateways in netstat -r
c (davidb@otto.bf.rmit.oz.au)
e
s 00013/00006/00625
d D 5.26 93/04/01 15:25:26 mckusick 37 36
c convert kinfo to sysctl
e
s 00005/00005/00626
d D 5.25 92/07/07 16:57:25 sklower 36 35
c not every value return in an nlist structure was being
c coerced to an (off_t) which was only being smashed back down to a (u_long)
c as an argument to kvm_read.  If you ask me nl.n_value ought to be a (void *)
c but since the type of nl.n_value and the second argument to kvm_read are
c the same I got fed up and changed all the off_t's to be that type (u_long).
e
s 00007/00003/00624
d D 5.24 92/07/06 15:36:16 sklower 35 34
c Multicast changes from lbl
e
s 00060/00035/00567
d D 5.23 92/05/27 18:11:51 sklower 34 33
c incorporate changes for new kvm interfaces from lbl
e
s 00014/00006/00588
d D 5.22 91/08/20 20:30:50 sklower 33 32
c uses vector of routing trees rather than linked list
e
s 00145/00131/00449
d D 5.21 91/07/30 12:38:11 karels 32 31
c (By Sklower) Checkpoint Mike's changes before making some of my own
e
s 00078/00024/00502
d D 5.20 90/11/29 17:13:56 sklower 31 30
c make netstat -r -A print all kinds of debugging crap (like address
c of routing entry, internal nodes, annnotations).
e
s 00008/00014/00518
d D 5.19 90/06/18 17:20:53 sklower 30 29
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00021/00016/00511
d D 5.18 90/06/18 14:27:44 sklower 29 28
c add C(loning),R(esolving),L(inklayer) flags;
c netstat -n should print out all of iso routes rather than truncating to allign columns
e
s 00004/00014/00523
d D 5.17 90/06/06 17:33:19 sklower 28 26
c New copyright and terms scheme; strings.h --> string.h
e
s 00006/00005/00532
d R 5.17 90/05/01 15:51:18 sklower 27 26
c off by one error in limit for general sockaddr.
e
s 00128/00083/00409
d D 5.16 90/04/07 16:17:27 sklower 26 25
c dump routing tree via getkerninfo call (in progress)
e
s 00192/00067/00300
d D 5.15 88/12/07 17:07:30 karels 25 24
c new version distinguishing between rtentries and ortentries
e
s 00013/00008/00354
d D 5.14 88/06/29 20:42:11 bostic 24 23
c install approved copyright notice
e
s 00009/00003/00353
d D 5.13 88/02/07 20:38:23 karels 23 22
c new copyrights
e
s 00005/00005/00351
d D 5.12 87/12/12 18:13:03 karels 22 21
c use MAXHOSTNAMELEN, not "50", print if_name correctly
e
s 00008/00008/00348
d D 5.11 87/08/29 18:54:55 karels 21 20
c readjust field widths
e
s 00012/00013/00344
d D 5.10 87/04/28 19:44:01 karels 20 19
c we paid for it, we might as well use it (and initialize it)
c (why did this work on vax?)
e
s 00001/00000/00356
d D 5.9 87/02/03 22:19:43 karels 19 18
c add M flag
e
s 00005/00005/00351
d D 5.8 86/12/15 17:10:42 sam 18 17
c all statistics are unsigned
e
s 00018/00015/00338
d D 5.7 86/08/11 11:51:12 kupfer 17 16
c Some lint.
e
s 00093/00051/00260
d D 5.6 86/04/23 12:20:27 karels 16 15
c format changes and other fixes
e
s 00002/00001/00309
d D 5.5 85/09/18 17:59:52 karels 15 14
c oops
e
s 00042/00017/00268
d D 5.4 85/09/18 16:47:37 karels 14 13
c add dynamic route flag; truncate domain names if same as ours;
c simplify subnet guessing, so as not to guess forever
e
s 00002/00002/00283
d D 5.3 85/08/16 19:40:25 sklower 13 12
c Add XNS statistics and control blocks; fix bug printing port numbers
e
s 00066/00003/00219
d D 5.2 85/06/15 22:24:30 sklower 12 11
c print xns interfaces and route reasonably
e
s 00008/00002/00214
d D 5.1 85/06/04 15:47:00 dist 11 10
c Add copyright
e
s 00064/00061/00152
d D 4.10 85/06/03 13:29:21 karels 10 9
c new subnets, interface addressing
e
s 00016/00012/00197
d D 4.9 84/10/31 11:39:02 karels 9 8
c get rthashsize from kernel
e
s 00003/00000/00206
d D 4.8 84/05/17 11:17:42 karels 8 7
c subnet fixes
e
s 00041/00006/00165
d D 4.7 84/05/11 12:23:38 karels 7 6
c print subnet addresses correctly; wider address fields
e
s 00030/00001/00141
d D 4.6 83/05/30 21:10:26 sam 6 5
c routing statistics
e
s 00003/00001/00139
d D 4.5 82/11/14 15:11:55 sam 5 4
c convert to 4.1c directory layout
e
s 00002/00002/00138
d D 4.4 82/10/07 18:14:28 sam 4 3
c use routines now in libc.a
e
s 00003/00002/00137
d D 4.3 82/10/06 17:52:51 sam 3 2
c add address format
e
s 00003/00002/00136
d D 4.2 82/10/05 22:18:13 sam 2 1
c new library routines
e
s 00138/00000/00000
d D 4.1 82/08/25 22:21:47 sam 1 0
c date and time created 82/08/25 22:21:47 by sam
e
u
U
t
T
I 11
/*
D 23
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 23
I 23
D 24
 * Copyright (c) 1983,1988 Regents of the University of California.
E 24
I 24
D 39
 * Copyright (c) 1983, 1988 Regents of the University of California.
E 24
 * All rights reserved.
E 39
I 39
 * Copyright (c) 1983, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
D 28
 * Redistribution and use in source and binary forms are permitted
D 24
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 24
I 24
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
E 28
I 28
 * %sccs.include.redist.c%
E 28
E 24
E 23
 */

E 11
I 1
#ifndef lint
D 11
static char sccsid[] = "%W% %E%";
#endif
E 11
I 11
D 12
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 12
I 12
D 16
static char sccsid[] = "%W% %E%";
E 16
I 16
D 24
static char sccsid[] = "%W% (Berkeley) %E%";
E 16
#endif
E 24
I 24
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 24
E 12
E 11

I 17
D 28
#include <stdio.h>
#include <strings.h>

E 28
E 17
D 14
#include <sys/types.h>
E 14
I 14
#include <sys/param.h>
I 34
#include <sys/protosw.h>
E 34
E 14
#include <sys/socket.h>
#include <sys/mbuf.h>
I 5

E 5
#include <net/if.h>
I 32
#include <net/if_dl.h>
#include <net/if_types.h>
E 32
I 25
#define  KERNEL
E 25
D 5
#include <net/in.h>
E 5
D 9
#define	KERNEL		/* to get routehash and RTHASHSIZ */
E 9
#include <net/route.h>
I 25
#undef KERNEL
E 25
I 5
#include <netinet/in.h>

I 12
#include <netns/ns.h>

E 12
E 5
D 34
#include <netdb.h>
E 34
I 26
D 37
#include <sys/kinfo.h>
E 37
I 37
#include <sys/sysctl.h>
E 37
I 28

I 34
#include <netdb.h>
E 34
#include <stdio.h>
I 34
#include <stdlib.h>
E 34
#include <string.h>
I 35
#include <unistd.h>
E 35
I 34
#include "netstat.h"
E 34
E 28
E 26

D 30
extern	int kmem;
E 30
D 31
extern	int nflag;
E 31
I 31
D 34
extern	int nflag, aflag, Aflag, af;
D 32
int do_rtent;
E 32
E 31
D 10
extern	char *routename();
E 10
I 10
D 12
extern	char *routename(), *netname();
E 12
I 12
D 17
extern	char *routename(), *netname(), *ns_print();
E 17
I 17
extern	char *routename(), *netname(), *ns_print(), *plural();
extern	char *malloc();
E 34
I 25
D 35
#define kget(p, d) \
D 30
	(klseek(kmem, (off_t)(p), 0), read(kmem, (char *)&(d), sizeof (d)))
E 30
I 30
D 34
	(kvm_read((off_t)(p), (char *)&(d), sizeof (d)))
E 34
I 34
	(kread((off_t)(p), (char *)&(d), sizeof (d)))
E 35
I 35
D 36
#define kget(p, d) (kread((off_t)(p), (char *)&(d), sizeof (d)))
E 36
I 36
#define kget(p, d) (kread((u_long)(p), (char *)&(d), sizeof (d)))
E 36
E 35
E 34
E 30
E 25
E 17
E 12
E 10

/*
 * Definitions for showing gateway flags.
 */
struct bits {
	short	b_mask;
	char	b_val;
} bits[] = {
	{ RTF_UP,	'U' },
	{ RTF_GATEWAY,	'G' },
	{ RTF_HOST,	'H' },
I 35
	{ RTF_REJECT,	'R' },
E 35
I 14
	{ RTF_DYNAMIC,	'D' },
I 19
	{ RTF_MODIFIED,	'M' },
I 35
	{ RTF_DONE,	'd' }, /* Completed -- for routing messages only */
	{ RTF_MASK,	'm' }, /* Mask Present -- for routing messages only */
E 35
I 29
	{ RTF_CLONING,	'C' },
D 31
	{ RTF_XRESOLVE,	'R' },
E 31
I 31
	{ RTF_XRESOLVE,	'X' },
E 31
	{ RTF_LLINFO,	'L' },
I 31
D 35
	{ RTF_REJECT,	'R' },
E 35
I 33
	{ RTF_STATIC,	'S' },
I 35
	{ RTF_PROTO1,	'1' },
	{ RTF_PROTO2,	'2' },
E 35
E 33
E 31
E 29
E 19
E 14
	{ 0 }
};

I 32
static union {
	struct	sockaddr u_sa;
	u_short	u_data[128];
} pt_u;

int	do_rtent = 0;
struct	rtentry rtentry;
struct	radix_node rnode;
struct	radix_mask rmask;

int	NewTree = 0;

I 34
static struct sockaddr *kgetsa __P((struct sockaddr *));
static void p_tree __P((struct radix_node *));
static void p_rtnode __P(());
static void ntreestuff __P(());
static void np_rtentry __P((struct rt_msghdr *));
D 45
static void p_sockaddr __P((struct sockaddr *, int, int));
E 45
I 45
static void p_sockaddr __P((struct sockaddr *, struct sockaddr *, int, int));
E 45
static void p_flags __P((int, char *));
static void p_rtentry __P((struct rtentry *));

E 34
E 32
/*
 * Print routing tables.
 */
I 34
void
E 34
D 9
routepr(hostaddr, netaddr)
	off_t hostaddr, netaddr;
E 9
I 9
D 25
routepr(hostaddr, netaddr, hashsizeaddr)
	off_t hostaddr, netaddr, hashsizeaddr;
E 25
I 25
D 32
routepr(hostaddr, netaddr, hashsizeaddr, treeaddr)
	off_t hostaddr, netaddr, hashsizeaddr, treeaddr;
E 32
I 32
routepr(rtree)
D 36
	off_t rtree;
E 36
I 36
	u_long rtree;
E 36
E 32
E 25
E 9
{
D 32
	struct mbuf mb;
D 25
	register struct rtentry *rt;
E 25
I 25
	register struct ortentry *rt;
E 25
	register struct mbuf *m;
D 25
	register struct bits *p;
E 25
D 9
	struct netent *np;
	struct hostent *hp;
E 9
	char name[16], *flags;
D 9
	struct mbuf *routehash[RTHASHSIZ];
E 9
I 9
	struct mbuf **routehash;
E 9
D 25
	struct ifnet ifnet;
E 25
D 9
	int first = 1, i, doinghost = 1;
E 9
I 9
	int hashsize;
	int i, doinghost = 1;
E 32
I 32
	struct radix_node_head *rnh, head;
I 33
	int i;
E 33
E 32
E 9

I 25
	printf("Routing tables\n");
I 31
D 32
	if (Aflag)
		printf("%-8.8s ","Address");
E 31
	printf("%-16.16s %-18.18s %-6.6s  %6.6s%8.8s  %s\n",
		"Destination", "Gateway",
		"Flags", "Refs", "Use", "Interface");
	if (treeaddr)
		return treestuff(treeaddr);
E 25
	if (hostaddr == 0) {
		printf("rthost: symbol not in namelist\n");
		return;
	}
	if (netaddr == 0) {
		printf("rtnet: symbol not in namelist\n");
		return;
	}
I 9
	if (hashsizeaddr == 0) {
		printf("rthashsize: symbol not in namelist\n");
		return;
	}
D 25
	klseek(kmem, hashsizeaddr, 0);
D 17
	read(kmem, &hashsize, sizeof (hashsize));
E 17
I 17
	read(kmem, (char *)&hashsize, sizeof (hashsize));
E 25
I 25
	kget(hashsizeaddr, hashsize);
E 25
E 17
	routehash = (struct mbuf **)malloc( hashsize*sizeof (struct mbuf *) );
E 9
D 30
	klseek(kmem, hostaddr, 0);
D 9
	read(kmem, routehash, sizeof (routehash));
E 9
I 9
D 17
	read(kmem, routehash, hashsize*sizeof (struct mbuf *));
E 17
I 17
	read(kmem, (char *)routehash, hashsize*sizeof (struct mbuf *));
E 30
I 30
	kvm_read(hostaddr, (char *)routehash, hashsize*sizeof (struct mbuf *));
E 30
E 17
E 9
D 25
	printf("Routing tables\n");
D 16
	printf("%-15.15s %-15.15s %-8.8s %-6.6s %-10.10s %s\n",
E 16
I 16
D 21
	printf("%-20.20s %-20.20s %-8.8s %-6.6s %-10.10s %s\n",
E 21
I 21
	printf("%-16.16s %-18.18s %-6.6s  %6.6s%8.8s  %s\n",
E 21
E 16
		"Destination", "Gateway",
D 21
		"Flags", "Refcnt", "Use", "Interface");
E 21
I 21
		"Flags", "Refs", "Use", "Interface");
E 25
E 21
again:
D 9
	for (i = 0; i < RTHASHSIZ; i++) {
E 9
I 9
	for (i = 0; i < hashsize; i++) {
E 9
		if (routehash[i] == 0)
			continue;
		m = routehash[i];
		while (m) {
D 25
			struct sockaddr_in *sin;
I 12
D 17
			struct sockaddr_ns *sns;
E 17
D 16
			long *l = (long *)&rt->rt_dst;
E 16
E 12

D 17
			klseek(kmem, m, 0);
			read(kmem, &mb, sizeof (mb));
E 17
I 17
			klseek(kmem, (off_t)m, 0);
			read(kmem, (char *)&mb, sizeof (mb));
E 17
			rt = mtod(&mb, struct rtentry *);
I 16
			if ((unsigned)rt < (unsigned)&mb ||
			    (unsigned)rt >= (unsigned)(&mb + 1)) {
				printf("???\n");
				return;
			}

E 16
I 12
			switch(rt->rt_dst.sa_family) {
D 16
		case AF_INET:
E 12
			sin = (struct sockaddr_in *)&rt->rt_dst;
D 6
			printf("%-15.15s ", routename(sin->sin_addr));
E 6
I 6
			printf("%-15.15s ",
D 10
			    sin->sin_addr.s_addr ?
				routename(sin->sin_addr) : "default");
E 10
I 10
			    (sin->sin_addr.s_addr == 0) ? "default" :
			    (rt->rt_flags & RTF_HOST) ?
			    routename(sin->sin_addr) : netname(sin->sin_addr, 0));
E 10
E 6
			sin = (struct sockaddr_in *)&rt->rt_gateway;
			printf("%-15.15s ", routename(sin->sin_addr));
I 12
			break;
		case AF_NS:
			printf("%-15s ",
			    ns_print((struct sockaddr_ns *)&rt->rt_dst));
			printf("%-15s ",
			    ns_print((struct sockaddr_ns *)&rt->rt_gateway));
			break;
		default:
			printf("%8.8x %8.8x %8.8x %8.8x",*l, l[1], l[2], l[3]);
			l = (long *)&rt->rt_gateway;
			printf("%8.8x %8.8x %8.8x %8.8x",*l, l[1], l[2], l[3]);
E 16
I 16
			case AF_INET:
				sin = (struct sockaddr_in *)&rt->rt_dst;
D 21
				printf("%-20.20s ",
E 21
I 21
				printf("%-16.16s ",
E 21
				    (sin->sin_addr.s_addr == 0) ? "default" :
				    (rt->rt_flags & RTF_HOST) ?
				    routename(sin->sin_addr) :
D 17
					netname(sin->sin_addr, 0));
E 17
I 17
					netname(sin->sin_addr, 0L));
E 17
				sin = (struct sockaddr_in *)&rt->rt_gateway;
D 21
				printf("%-20.20s ", routename(sin->sin_addr));
E 21
I 21
				printf("%-18.18s ", routename(sin->sin_addr));
E 21
				break;
			case AF_NS:
D 21
				printf("%-20s ",
E 21
I 21
				printf("%-16s ",
E 21
				    ns_print((struct sockaddr_ns *)&rt->rt_dst));
D 21
				printf("%-20s ",
E 21
I 21
				printf("%-18s ",
E 21
				    ns_print((struct sockaddr_ns *)&rt->rt_gateway));
				break;
			default:
				{
				u_short *s = (u_short *)rt->rt_dst.sa_data;
				printf("(%d)%x %x %x %x %x %x %x ",
				    rt->rt_dst.sa_family,
				    s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
				s = (u_short *)rt->rt_gateway.sa_data;
				printf("(%d)%x %x %x %x %x %x %x ",
				    rt->rt_gateway.sa_family,
				    s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
				}
E 16
			}
E 12
			for (flags = name, p = bits; p->b_mask; p++)
				if (p->b_mask & rt->rt_flags)
					*flags++ = p->b_val;
			*flags = '\0';
D 21
			printf("%-8.8s %-6d %-10d ", name,
E 21
I 21
			printf("%-6.6s %6d %8d ", name,
E 21
				rt->rt_refcnt, rt->rt_use);
			if (rt->rt_ifp == 0) {
				putchar('\n');
				m = mb.m_next;
				continue;
			}
D 17
			klseek(kmem, rt->rt_ifp, 0);
			read(kmem, &ifnet, sizeof (ifnet));
			klseek(kmem, (int)ifnet.if_name, 0);
E 17
I 17
			klseek(kmem, (off_t)rt->rt_ifp, 0);
			read(kmem, (char *)&ifnet, sizeof (ifnet));
			klseek(kmem, (off_t)ifnet.if_name, 0);
E 17
			read(kmem, name, 16);
D 21
			printf("%s%d\n", name, ifnet.if_unit);
E 21
I 21
D 22
			printf(" %s%d\n", name, ifnet.if_unit);
E 22
I 22
			printf(" %.15s%d\n", name, ifnet.if_unit);
E 25
I 25
			kget(m, mb);
D 31
			p_rtentry((struct rtentry *)(mb.m_dat));
E 31
I 31
			if (Aflag)
				printf("%8.8x ", m);
			p_ortentry((struct ortentry *)(mb.m_dat));
E 31
E 25
E 22
E 21
			m = mb.m_next;
E 32
I 32

	if (Aflag == 0 && NewTree)
		ntreestuff();
	else {
		if (rtree == 0) {
D 33
			printf("radix_node_head: symbol not in namelist\n");
E 33
I 33
			printf("rt_tables: symbol not in namelist\n");
E 33
			return;
E 32
		}
I 32

D 33
		for (kget(rtree, rnh); rnh; rnh = head.rnh_next) {
E 33
I 33
		kget(rtree, rt_tables);
		for (i = 0; i <= AF_MAX; i++) {
			if ((rnh = rt_tables[i]) == 0)
				continue;
E 33
			kget(rnh, head);
D 33
			if (head.rnh_af == AF_UNSPEC) {
				if (Aflag) { 
E 33
I 33
			if (i == AF_UNSPEC) {
D 34
				if (Aflag && af == 0) { 
E 34
I 34
				if (Aflag && af == 0) {
E 34
E 33
					printf("Netmasks:\n");
					p_tree(head.rnh_treetop);
				}
D 33
			} else if (af == AF_UNSPEC || af == head.rnh_af) {
				pr_family(head.rnh_af);
E 33
I 33
			} else if (af == AF_UNSPEC || af == i) {
				pr_family(i);
E 33
				do_rtent = 1;
				pr_rthdr();
				p_tree(head.rnh_treetop);
			}
		}
E 32
	}
D 32
	if (doinghost) {
D 30
		klseek(kmem, netaddr, 0);
D 9
		read(kmem, routehash, sizeof (routehash));
E 9
I 9
D 17
		read(kmem, routehash, hashsize*sizeof (struct mbuf *));
E 17
I 17
		read(kmem, (char *)routehash, hashsize*sizeof (struct mbuf *));
E 30
I 30
		kvm_read(netaddr, (char *)routehash,
			hashsize*sizeof (struct mbuf *));
E 30
E 17
E 9
		doinghost = 0;
		goto again;
E 32
I 32
}

/*
 * Print address family header before a section of the routing table.
 */
I 34
void
E 34
pr_family(af)
	int af;
{
	char *afname;

	switch (af) {
	case AF_INET:
		afname = "Internet";
		break;
	case AF_NS:
		afname = "XNS";
		break;
	case AF_ISO:
		afname = "ISO";
I 33
		break;
	case AF_CCITT:
		afname = "X.25";
E 33
		break;
	default:
		afname = NULL;
		break;
E 32
	}
I 9
D 17
	free(routehash);
E 17
I 17
D 32
	free((char *)routehash);
I 25
	return;
E 32
I 32
	if (afname)
		printf("\n%s:\n", afname);
	else
		printf("\nProtocol Family %d:\n", af);
E 32
}

D 32
static union {
	struct	sockaddr u_sa;
	u_short	u_data[128];
} pt_u;
D 31
static struct rtentry rtentry;
E 31
I 31
int do_rtent = 0;
struct rtentry rtentry;
struct radix_node rnode;
struct radix_mask rmask;
E 32
I 32
/* column widths; each followed by one space */
#define	WID_DST		16	/* width of destination column */
#define	WID_GW		18	/* width of gateway column */
E 32
E 31

I 26
D 32
int NewTree = 0;
E 26
treestuff(rtree)
off_t rtree;
E 32
I 32
/*
 * Print header for routing table columns.
 */
I 34
void
E 34
pr_rthdr()
E 32
{
D 32
	struct radix_node_head *rnh, head;
E 32
D 29
	    
E 29
I 29

E 29
I 26
D 31
	if (NewTree)
E 31
I 31
D 32
	if (Aflag == 0 && NewTree)
E 31
		return(ntreestuff());
E 26
	for (kget(rtree, rnh); rnh; rnh = head.rnh_next) {
		kget(rnh, head);
		if (head.rnh_af == 0) {
D 31
			printf("Netmasks:\n");
			p_tree(head.rnh_treetop, 0);
		} else {
E 31
I 31
			if (Aflag || af == AF_UNSPEC) { 
				printf("Netmasks:\n");
				p_tree(head.rnh_treetop);
			}
		} else if (af == AF_UNSPEC || af == head.rnh_af) {
E 31
			printf("\nRoute Tree for Protocol Family %d:\n",
								head.rnh_af);
D 31
			p_tree(head.rnh_treetop, 1);
E 31
I 31
			do_rtent = 1;
			p_tree(head.rnh_treetop);
E 31
		}
	}
E 32
I 32
	if (Aflag)
		printf("%-8.8s ","Address");
	printf("%-*.*s %-*.*s %-6.6s  %6.6s%8.8s  %s\n",
		WID_DST, WID_DST, "Destination",
		WID_GW, WID_GW, "Gateway",
		"Flags", "Refs", "Use", "Interface");
E 32
}

I 26
D 34
struct sockaddr *
E 34
I 34
static struct sockaddr *
E 34
kgetsa(dst)
D 32
register struct sockaddr *dst;
E 32
I 32
	register struct sockaddr *dst;
E 32
{
I 32

E 32
	kget(dst, pt_u.u_sa);
D 32
	if (pt_u.u_sa.sa_len > sizeof (pt_u.u_sa)) {
E 32
I 32
	if (pt_u.u_sa.sa_len > sizeof (pt_u.u_sa))
E 32
D 30
		klseek(kmem, (off_t)dst, 0);
		read(kmem, pt_u.u_data, pt_u.u_sa.sa_len);
E 30
I 30
D 34
		kvm_read((off_t)dst, pt_u.u_data, pt_u.u_sa.sa_len);
E 34
I 34
D 36
		kread((off_t)dst, (char *)pt_u.u_data, pt_u.u_sa.sa_len);
E 36
I 36
		kread((u_long)dst, (char *)pt_u.u_data, pt_u.u_sa.sa_len);
E 36
E 34
E 30
D 32
	}
E 32
	return (&pt_u.u_sa);
}

I 34
static void
E 34
E 26
D 31
p_tree(rn, do_rtent)
E 31
I 31
p_tree(rn)
E 31
D 32
struct radix_node *rn;
E 32
I 32
	struct radix_node *rn;
E 32
{
D 31
	struct radix_node rnode;
	register u_short *s, *slim;
	int len;
E 31

again:
	kget(rn, rnode);
	if (rnode.rn_b < 0) {
I 31
		if (Aflag)
			printf("%-8.8x ", rn);
E 31
D 32
		if (rnode.rn_flags & RNF_ROOT)
D 31
			printf("(root node)\n");
E 31
I 31
			printf("(root node)%s",
E 32
I 32
		if (rnode.rn_flags & RNF_ROOT) {
			if (Aflag)
				printf("(root node)%s",
E 32
				    rnode.rn_dupedkey ? " =>\n" : "\n");
E 31
D 32
		else if (do_rtent) {
E 32
I 32
		} else if (do_rtent) {
E 32
			kget(rn, rtentry);
			p_rtentry(&rtentry);
I 31
			if (Aflag)
				p_rtnode();
E 31
		} else {
D 26
			kget(rnode.rn_key, pt_u);
			printf("(%d) ",pt_u.u_sa.sa_family);
			if ((len = pt_u.u_sa.sa_len) == 0 || len > MAXKEYLEN)
				len = MAXKEYLEN;
			s = pt_u.u_data + 1;
			for (slim = s + ((len - 1)/2); s < slim; s++)
				printf("%x ", *s);
E 26
I 26
			p_sockaddr(kgetsa((struct sockaddr *)rnode.rn_key),
D 29
				    0, "%-44.44s ");
E 29
I 29
D 32
				    0, 44);
E 32
I 32
D 45
			    0, 44);
E 45
I 45
				   NULL, 0, 44);
E 45
E 32
E 29
E 26
			putchar('\n');
		}
		if (rn = rnode.rn_dupedkey)
			goto again;
	} else {
D 31
		p_tree(rnode.rn_l, do_rtent);
		p_tree(rnode.rn_r, do_rtent);
E 31
I 31
		if (Aflag && do_rtent) {
			printf("%-8.8x ", rn);
			p_rtnode();
		}
		rn = rnode.rn_r;
		p_tree(rnode.rn_l);
		p_tree(rn);
E 31
	}
}
I 31
D 32
char nbuf[20];
E 32
E 31

I 32
char	nbuf[20];

I 34
static void
E 34
E 32
I 31
p_rtnode()
{
D 32

E 32
	struct radix_mask *rm = rnode.rn_mklist;
I 32

E 32
	if (rnode.rn_b < 0) {
		if (rnode.rn_mask) {
			printf("\t  mask ");
			p_sockaddr(kgetsa((struct sockaddr *)rnode.rn_mask),
D 45
				    0, -1);
E 45
I 45
				   NULL, 0, -1);
E 45
		} else if (rm == 0)
			return;
	} else {
		sprintf(nbuf, "(%d)", rnode.rn_b);
		printf("%6.6s %8.8x : %8.8x", nbuf, rnode.rn_l, rnode.rn_r);
	}
	while (rm) {
		kget(rm, rmask);
		sprintf(nbuf, " %d refs, ", rmask.rm_refs);
		printf(" mk = %8.8x {(%d),%s",
			rm, -1 - rmask.rm_b, rmask.rm_refs ? nbuf : " ");
D 43
		p_sockaddr(kgetsa((struct sockaddr *)rmask.rm_mask), 0, -1);
E 43
I 43
		if (rmask.rm_flags & RNF_NORMAL) {
			struct radix_node rnode_aux;
D 44
			printf(nbuf, " <normal>, ");
E 44
I 44
			printf(" <normal>, ");
E 44
			kget(rmask.rm_leaf, rnode_aux);
D 45
			p_sockaddr(
			 kgetsa((struct sockaddr *)rnode_aux.rn_mask), 0, -1);
E 45
I 45
			p_sockaddr(kgetsa((struct sockaddr *)rnode_aux.rn_mask),
				    NULL, 0, -1);
E 45
		} else
D 45
		    p_sockaddr(kgetsa((struct sockaddr *)rmask.rm_mask), 0, -1);
E 45
I 45
		    p_sockaddr(kgetsa((struct sockaddr *)rmask.rm_mask),
				NULL, 0, -1);
E 45
E 43
		putchar('}');
		if (rm = rmask.rm_mklist)
			printf(" ->");
	}
	putchar('\n');
}

I 34
static void
E 34
E 31
D 26
struct sockaddr *
kgetsa(dst)
register struct sockaddr *dst;
E 26
I 26
ntreestuff()
E 26
{
D 26
	kget(dst, pt_u.u_sa);
	if (pt_u.u_sa.sa_len > sizeof (pt_u.u_sa)) {
		klseek(kmem, (off_t)dst, 0);
		read(kmem, pt_u.u_data, pt_u.u_sa.sa_len);
E 26
I 26
D 37
	int needed;
E 37
I 37
	size_t needed;
	int mib[6];
E 37
	char *buf, *next, *lim;
	register struct rt_msghdr *rtm;

D 37
	if ((needed = getkerninfo(KINFO_RT_DUMP, 0, 0, 0)) < 0)
		{ perror("route-getkerninfo-estimate"); exit(1);}
E 37
I 37
        mib[0] = CTL_NET;
        mib[1] = PF_ROUTE;
        mib[2] = 0;
        mib[3] = 0;
        mib[4] = NET_RT_DUMP;
        mib[5] = 0;
        if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0)
		{ perror("route-sysctl-estimate"); exit(1);}
E 37
	if ((buf = malloc(needed)) == 0)
D 29
		{ printf("out of space\n");; exit(1);}
E 29
I 29
		{ printf("out of space\n"); exit(1);}
E 29
D 37
	if (getkerninfo(KINFO_RT_DUMP, buf, &needed, 0) < 0)
D 32
		{ perror("actual retrieval of routing table"); exit(1);}
E 32
I 32
		{ perror("getkerninfo of routing table"); exit(1);}
E 37
I 37
        if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0)
		{ perror("sysctl of routing table"); exit(1);}
E 37
E 32
	lim  = buf + needed;
	for (next = buf; next < lim; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)next;
		np_rtentry(rtm);
E 26
	}
D 26
	return (&pt_u.u_sa);
E 26
}

I 34
static void
E 34
D 26
p_rtentry(rt)
register struct rtentry *rt;
E 26
I 26
np_rtentry(rtm)
D 32
register struct rt_msghdr *rtm;
E 32
I 32
	register struct rt_msghdr *rtm;
E 32
E 26
{
D 26
	char name[16], *flags;
	register struct bits *p;
	register struct sockaddr_in *sin;
	struct ifnet ifnet;
E 26
I 26
	register struct sockaddr *sa = (struct sockaddr *)(rtm + 1);
D 34
	static int masks_done, old_af, banner_printed;
E 34
I 34
#ifdef notdef
	static int masks_done, banner_printed;
#endif
	static int old_af;
E 34
	int af = 0, interesting = RTF_UP | RTF_GATEWAY | RTF_HOST;
E 26

D 26
	sin = (struct sockaddr_in *)kgetsa(rt_key(rt));
	switch(sin->sin_family) {
E 26
I 26
#ifdef notdef
	/* for the moment, netmasks are skipped over */
	if (!banner_printed) {
		printf("Netmasks:\n");
		banner_printed = 1;
	}
	if (masks_done == 0) {
		if (rtm->rtm_addrs != RTA_DST ) {
			masks_done = 1;
			af = sa->sa_family;
		}
	} else
#endif
		af = sa->sa_family;
	if (af != old_af) {
D 32
		printf("\nRoute Tree for Protocol Family %d:\n", af);
E 32
I 32
		pr_family(af);
E 32
		old_af = af;
	}
	if (rtm->rtm_addrs == RTA_DST)
D 29
		p_sockaddr(sa, 0, "%-36.36s ");
E 29
I 29
D 45
		p_sockaddr(sa, 0, 36);
E 45
I 45
		p_sockaddr(sa, NULL, 0, 36);
E 45
E 29
	else {
D 29
		p_sockaddr(sa, rtm->rtm_flags, "%-16.16s ");
E 29
I 29
D 45
		p_sockaddr(sa, rtm->rtm_flags, 16);
E 45
I 45
		p_sockaddr(sa, NULL, rtm->rtm_flags, 16);
E 45
E 29
		if (sa->sa_len == 0)
			sa->sa_len = sizeof(long);
		sa = (struct sockaddr *)(sa->sa_len + (char *)sa);
D 29
		p_sockaddr(sa, 0, "%-18.18s ");
E 29
I 29
D 45
		p_sockaddr(sa, 0, 18);
E 45
I 45
		p_sockaddr(sa, NULL, 0, 18);
E 45
E 29
	}
	p_flags(rtm->rtm_flags & interesting, "%-6.6s ");
	putchar('\n');
}

I 34
static void
E 34
D 29
p_sockaddr(sa, flags, format)
E 29
I 29
D 45
p_sockaddr(sa, flags, width)
E 29
D 32
struct sockaddr *sa;
D 29
int flags;
char *format;
E 29
I 29
int flags, width;
E 32
I 32
	struct sockaddr *sa;
E 45
I 45
p_sockaddr(sa, mask, flags, width)
	struct sockaddr *sa, *mask;
E 45
	int flags, width;
E 32
E 29
{
D 29
	char workbuf[128], *cp, *cplim;
E 29
I 29
D 32
	char format[20], workbuf[128], *cp, *cplim;
E 29
	register char *cpout;
E 32
I 32
D 34
	char format[20], workbuf[128], *cplim;
E 34
I 34
	char workbuf[128], *cplim;
E 34
	register char *cp = workbuf;
E 32

	switch(sa->sa_family) {
E 26
	case AF_INET:
D 26
		printf("%-16.16s ",
		    (sin->sin_addr.s_addr == 0) ? "default" :
		    (rt->rt_flags & RTF_HOST) ?
		    routename(sin->sin_addr) :
			netname(sin->sin_addr, 0L));
		sin = (struct sockaddr_in *)kgetsa(rt->rt_gateway);
		printf("%-18.18s ", routename(sin->sin_addr));
E 26
I 26
	    {
		register struct sockaddr_in *sin = (struct sockaddr_in *)sa;

D 45
		cp = (sin->sin_addr.s_addr == 0) ? "default" :
		      ((flags & RTF_HOST) ?
D 34
			routename(sin->sin_addr) : netname(sin->sin_addr, 0L));
E 34
I 34
			routename(sin->sin_addr.s_addr) :
			netname(sin->sin_addr.s_addr, 0L));
E 45
I 45
		if (sin->sin_addr.s_addr == INADDR_ANY)
			cp = "default";
		else if (flags & RTF_HOST)
			cp = routename(sin->sin_addr.s_addr);
		else if (mask)
			cp = netname(sin->sin_addr.s_addr,
				     ntohl(((struct sockaddr_in *)mask)
					   ->sin_addr.s_addr));
		else
			cp = netname(sin->sin_addr.s_addr, 0L);
E 45
E 34
D 32
	    }
E 32
E 26
		break;
I 32
	    }
E 32
I 26

E 26
	case AF_NS:
D 26
		printf("%-16s ",
		    ns_print((struct sockaddr_ns *)sin));
		printf("%-18s ",
		    ns_print((struct sockaddr_ns *)kgetsa(rt->rt_gateway)));
E 26
I 26
D 34
		cp = ns_print((struct sockaddr_ns *)sa);
E 34
I 34
		cp = ns_print(sa);
E 34
E 26
		break;
I 26

I 32
	case AF_LINK:
	    {
		register struct sockaddr_dl *sdl = (struct sockaddr_dl *)sa;
D 34
		extern char *link_ntoa();
E 34

		if (sdl->sdl_nlen == 0 && sdl->sdl_alen == 0 &&
		    sdl->sdl_slen == 0)
			(void) sprintf(workbuf, "link#%d", sdl->sdl_index);
		else switch (sdl->sdl_type) {
		case IFT_ETHER:
		    {
			register int i;
			register u_char *lla = (u_char *)sdl->sdl_data +
			    sdl->sdl_nlen;

			cplim = "";
			for (i = 0; i < sdl->sdl_alen; i++, lla++) {
				cp += sprintf(cp, "%s%x", cplim, *lla);
				cplim = ":";
			}
			cp = workbuf;
			break;
		    }
		default:
			cp = link_ntoa(sdl);
			break;
		}
		break;
	    }

E 32
E 26
	default:
D 26
		{
		u_short *s = (u_short *)pt_u.u_sa.sa_data;
		printf("(%d)%x %x %x %x %x %x %x ",
		    sin->sin_family,
		    s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
		(void) kgetsa(rt->rt_gateway);
		printf("(%d)%x %x %x %x %x %x %x ",
		    sin->sin_family,
		    s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
		}
E 26
I 26
	    {
D 31
		register u_short *s = ((u_short *)sa->sa_data),
				*slim = ((sa->sa_len + 1)/2) + s;
E 31
I 31
D 40
		register u_short *s = ((u_short *)sa->sa_data), *slim;
E 40
I 40
D 41
		register u_char *s = ((u_char *)sa->sa_data, *slim;
E 41
I 41
		register u_char *s = (u_char *)sa->sa_data, *slim;
E 41
E 40
E 31

I 31
D 40
		slim = (u_short *) sa + ((sa->sa_len + sizeof(u_short) - 1) /
		    sizeof(u_short));
E 40
I 40
		slim =  sa->sa_len + (u_char *) sa;
E 40
E 31
D 32
		cp = workbuf;
E 32
		cplim = cp + sizeof(workbuf) - 6;
		cp += sprintf(cp, "(%d)", sa->sa_family);
D 40
		while (s < slim && cp < cplim)
D 31
			cp += sprintf(cp, "%x ", *s++);
E 31
I 31
			cp += sprintf(cp, " %x", *s++);
E 40
I 40
		while (s < slim && cp < cplim) {
			cp += sprintf(cp, " %02x", *s++);
			if (s < slim)
			    cp += sprintf(cp, "%02x", *s++);
		}
E 40
E 31
		cp = workbuf;
	    }
E 26
	}
D 26
	for (flags = name, p = bits; p->b_mask; p++)
		if (p->b_mask & rt->rt_flags)
E 26
I 26
D 29
	printf(format, cp);
E 29
I 29
D 31
	if (nflag)
		printf("%-*s ", width, cp);
	else
		printf("%-*.*s ", width, width, cp);
E 31
I 31
	if (width < 0 )
		printf("%s ", cp);
	else {
		if (nflag)
			printf("%-*s ", width, cp);
		else
			printf("%-*.*s ", width, width, cp);
	}
E 31
E 29
}

I 34
static void
E 34
p_flags(f, format)
D 32
register int f;
char *format;
E 32
I 32
	register int f;
	char *format;
E 32
{
	char name[33], *flags;
	register struct bits *p = bits;
I 32

E 32
	for (flags = name; p->b_mask; p++)
		if (p->b_mask & f)
E 26
			*flags++ = p->b_val;
	*flags = '\0';
D 26
	printf("%-6.6s %6d %8d ", name,
		rt->rt_refcnt, rt->rt_use);
E 26
I 26
	printf(format, name);
}

I 34
static void
E 34
p_rtentry(rt)
D 34
register struct rtentry *rt;
E 34
I 34
	register struct rtentry *rt;
E 34
{
D 32
	char name[16];
E 32
D 34
	register struct sockaddr *sa;
E 34
D 32
	struct ifnet ifnet;
E 32
I 32
	static struct ifnet ifnet, *lastif;
	static char name[16];
I 45
	register struct sockaddr *sa;
	struct sockaddr addr, mask;
E 45
E 32

D 29
	p_sockaddr(kgetsa(rt_key(rt)), rt->rt_flags, "%-16.16s ");
	p_sockaddr(kgetsa(rt->rt_gateway), 0, "%-18.18s ");;
E 29
I 29
D 32
	p_sockaddr(kgetsa(rt_key(rt)), rt->rt_flags, 16);
	p_sockaddr(kgetsa(rt->rt_gateway), 0, 18);
E 32
I 32
D 45
	p_sockaddr(kgetsa(rt_key(rt)), rt->rt_flags, WID_DST);
D 38
	p_sockaddr(kgetsa(rt->rt_gateway), 0, WID_GW);
E 38
I 38
	p_sockaddr(kgetsa(rt->rt_gateway), RTF_HOST, WID_GW);
E 45
I 45
	if (!(sa = kgetsa(rt_key(rt))))
		bzero(&addr, sizeof addr);
	else
		addr = *sa;
	if (!rt_mask(rt) || !(sa = kgetsa(rt_mask(rt))))
		bzero(&mask, sizeof mask);
	else
		mask = *sa;
	p_sockaddr(&addr, &mask, rt->rt_flags, WID_DST);
	p_sockaddr(kgetsa(rt->rt_gateway), NULL, RTF_HOST, WID_GW);
E 45
E 38
E 32
E 29
	p_flags(rt->rt_flags, "%-6.6s ");
	printf("%6d %8d ", rt->rt_refcnt, rt->rt_use);
E 26
D 32
	if (rt->rt_ifp == 0) {
		putchar('\n');
		return;
E 32
I 32
	if (rt->rt_ifp) {
		if (rt->rt_ifp != lastif) {
			kget(rt->rt_ifp, ifnet);
D 34
			kvm_read((off_t)ifnet.if_name, name, 16);
E 34
I 34
D 36
			kread((off_t)ifnet.if_name, name, 16);
E 36
I 36
			kread((u_long)ifnet.if_name, name, 16);
E 36
E 34
			lastif = rt->rt_ifp;
		}
		printf(" %.15s%d%s", name, ifnet.if_unit,
			rt->rt_nodes[0].rn_dupedkey ? " =>" : "");
E 32
	}
D 32
	kget(rt->rt_ifp, ifnet);
D 30
	klseek(kmem, (off_t)ifnet.if_name, 0);
	read(kmem, name, 16);
E 30
I 30
	kvm_read((off_t)ifnet.if_name, name, 16);
E 30
D 31
	printf(" %.15s%d\n", name, ifnet.if_unit);
E 31
I 31
	printf(" %.15s%d%s", name, ifnet.if_unit,
		rt->rt_nodes[0].rn_dupedkey ? " =>\n" : "\n");
E 31
}

p_ortentry(rt)
register struct ortentry *rt;
{
	char name[16], *flags;
	register struct bits *p;
	register struct sockaddr_in *sin;
	struct ifnet ifnet;

D 26
	switch(rt->rt_dst.sa_family) {
	case AF_INET:
		sin = (struct sockaddr_in *)&rt->rt_dst;
		printf("%-16.16s ",
		    (sin->sin_addr.s_addr == 0) ? "default" :
		    (rt->rt_flags & RTF_HOST) ?
		    routename(sin->sin_addr) :
			netname(sin->sin_addr, 0L));
		sin = (struct sockaddr_in *)&rt->rt_gateway;
		printf("%-18.18s ", routename(sin->sin_addr));
		break;
	case AF_NS:
		printf("%-16s ",
		    ns_print((struct sockaddr_ns *)&rt->rt_dst));
		printf("%-18s ",
		    ns_print((struct sockaddr_ns *)&rt->rt_gateway));
		break;
	default:
		{
		u_short *s = (u_short *)rt->rt_dst.sa_data;
		printf("(%d)%x %x %x %x %x %x %x ",
		    rt->rt_dst.sa_family,
		    s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
		s = (u_short *)rt->rt_gateway.sa_data;
		printf("(%d)%x %x %x %x %x %x %x ",
		    rt->rt_gateway.sa_family,
		    s[0], s[1], s[2], s[3], s[4], s[5], s[6]);
		}
	}
	for (flags = name, p = bits; p->b_mask; p++)
		if (p->b_mask & rt->rt_flags)
			*flags++ = p->b_val;
	*flags = '\0';
	printf("%-6.6s %6d %8d ", name,
		rt->rt_refcnt, rt->rt_use);
E 26
I 26
D 29
	p_sockaddr(&rt->rt_dst, rt->rt_flags, "%-16.16s ");
	p_sockaddr(&rt->rt_gateway, 0, "%-18.18s ");
E 29
I 29
	p_sockaddr(&rt->rt_dst, rt->rt_flags, 16);
	p_sockaddr(&rt->rt_gateway, 0, 18);
E 29
	p_flags(rt->rt_flags, "%-6.6s ");
	printf("%6d %8d ", rt->rt_refcnt, rt->rt_use);
E 26
	if (rt->rt_ifp == 0) {
		putchar('\n');
		return;
	}
	kget(rt->rt_ifp, ifnet);
D 30
	klseek(kmem, (off_t)ifnet.if_name, 0);
	read(kmem, name, 16);
E 30
I 30
	kvm_read((off_t)ifnet.if_name, name, 16);
E 30
	printf(" %.15s%d\n", name, ifnet.if_unit);
E 32
I 32
	putchar('\n');
E 32
E 25
E 17
E 9
}

char *
routename(in)
D 34
	struct in_addr in;
E 34
I 34
	u_long in;
E 34
{
D 14
	char *cp = 0;
E 14
I 14
D 15
	register char *cp = 0;
E 15
I 15
	register char *cp;
E 15
E 14
D 22
	static char line[50];
E 22
I 22
	static char line[MAXHOSTNAMELEN + 1];
E 22
D 7
	int lna, net;
E 7
I 7
	struct hostent *hp;
I 14
	static char domain[MAXHOSTNAMELEN + 1];
	static int first = 1;
D 34
	char *index();
E 34
E 14
D 10
	struct netent *np;
	int lna, net, subnet;
E 10
E 7

I 14
	if (first) {
		first = 0;
		if (gethostname(domain, MAXHOSTNAMELEN) == 0 &&
		    (cp = index(domain, '.')))
			(void) strcpy(domain, cp + 1);
		else
			domain[0] = 0;
	}
I 15
	cp = 0;
E 15
E 14
D 4
	net = in_netof(in);
	lna = in_lnaof(in);
E 4
I 4
D 10
	net = inet_netof(in);
I 7
	subnet = inet_subnetof(in);
E 7
	lna = inet_lnaof(in);
E 10
E 4
	if (!nflag) {
D 10
		if (lna == INADDR_ANY) {
D 2
			struct netent *np = getnetaddr(net);
E 2
I 2
D 3
			struct netent *np = getnetbyaddr(net);
E 3
I 3
D 7
			struct netent *np = getnetbyaddr(net, AF_INET);
E 3
E 2

E 7
I 7
			np = getnetbyaddr(net, AF_INET);
E 7
			if (np)
				cp = np->n_name;
I 7
D 9
			else if (net == 0)
				cp = "default";
E 9
		} else if ((subnet != net) && ((lna & 0xff) == 0) &&
		    (np = getnetbyaddr(subnet, AF_INET))) {
			struct in_addr subnaddr, inet_makeaddr();
			subnaddr = inet_makeaddr(subnet, INADDR_ANY);
			if (bcmp(&in, &subnaddr, sizeof(in)) == 0)
				cp = np->n_name;
I 8
			else
				goto host;
E 8
E 7
		} else {
I 8
host:
E 8
D 2
			struct hostent *hp = gethostaddr(in.s_addr);
E 2
I 2
D 7
			struct hostent *hp;
E 2

E 7
I 2
D 3
			hp = gethostbyaddr(&in, sizeof (struct in_addr));
E 3
I 3
			hp = gethostbyaddr(&in, sizeof (struct in_addr),
				AF_INET);
E 3
E 2
			if (hp)
				cp = hp->h_name;
		}
E 10
I 10
D 17
		hp = gethostbyaddr(&in, sizeof (struct in_addr),
E 17
I 17
		hp = gethostbyaddr((char *)&in, sizeof (struct in_addr),
E 17
			AF_INET);
D 14
		if (hp)
E 14
I 14
		if (hp) {
			if ((cp = index(hp->h_name, '.')) &&
			    !strcmp(cp + 1, domain))
				*cp = 0;
E 14
			cp = hp->h_name;
I 14
		}
E 14
E 10
	}
	if (cp)
D 22
		strcpy(line, cp);
E 22
I 22
		strncpy(line, cp, sizeof(line) - 1);
E 22
	else {
D 10
		u_char *ucp = (u_char *)&in;
		if (lna == INADDR_ANY)
			sprintf(line, "%u.%u.%u", ucp[0], ucp[1], ucp[2]);
		else
			sprintf(line, "%u.%u.%u.%u", ucp[0], ucp[1],
				ucp[2], ucp[3]);
E 10
I 10
#define C(x)	((x) & 0xff)
D 34
		in.s_addr = ntohl(in.s_addr);
		sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8), C(in.s_addr));
E 34
I 34
		in = ntohl(in);
		sprintf(line, "%u.%u.%u.%u",
		    C(in >> 24), C(in >> 16), C(in >> 8), C(in));
E 34
E 10
	}
	return (line);
I 6
}
I 10

I 45
static u_long
forgemask(a)
	u_long a;
{
	u_long m;

	if (IN_CLASSA(a))
		m = IN_CLASSA_NET;
	else if (IN_CLASSB(a))
		m = IN_CLASSB_NET;
	else
		m = IN_CLASSC_NET;
	return (m);
}

static void
domask(dst, addr, mask)
	char *dst;
	u_long addr, mask;
{
	register int b, i;

	if (!mask || (forgemask(addr) == mask)) {
		*dst = '\0';
		return;
	}
	i = 0;
	for (b = 0; b < 32; b++)
		if (mask & (1 << b)) {
			register int bb;

			i = b;
			for (bb = b+1; bb < 32; bb++)
				if (!(mask & (1 << bb))) {
					i = -1;	/* noncontig */
					break;
				}
			break;
		}
	if (i == -1)
		sprintf(dst, "&0x%lx", mask);
	else
		sprintf(dst, "/%d", 32-i);
}

E 45
E 10
D 7

E 7
/*
I 10
 * Return the name of the network whose address is given.
 * The address is assumed to be that of a net or subnet, not a host.
 */
char *
netname(in, mask)
D 34
	struct in_addr in;
	u_long mask;
E 34
I 34
	u_long in, mask;
E 34
{
	char *cp = 0;
D 22
	static char line[50];
E 22
I 22
	static char line[MAXHOSTNAMELEN + 1];
E 22
	struct netent *np = 0;
D 45
	u_long net;
D 34
	register i;
E 34
I 34
	register int i;
E 45
I 45
	u_long net, omask;
	register u_long i;
E 45
E 34
I 14
	int subnetshift;
E 14

D 20
	in.s_addr = ntohl(in.s_addr);
	if (!nflag && in.s_addr) {
E 20
I 20
D 34
	i = ntohl(in.s_addr);
E 34
I 34
	i = ntohl(in);
I 45
	omask = mask;
E 45
E 34
	if (!nflag && i) {
E 20
D 14
		if (mask) {
			net = in.s_addr & mask;
			while ((mask & 1) == 0)
				mask >>= 1, net >>= 1;
			np = getnetbyaddr(net, AF_INET);
		}
		if (np == 0) {
E 14
I 14
		if (mask == 0) {
D 45
			if (IN_CLASSA(i)) {
				mask = IN_CLASSA_NET;
E 45
I 45
			switch (mask = forgemask(i)) {
			case IN_CLASSA_NET:
E 45
				subnetshift = 8;
D 45
			} else if (IN_CLASSB(i)) {
				mask = IN_CLASSB_NET;
E 45
I 45
				break;
			case IN_CLASSB_NET:
E 45
				subnetshift = 8;
D 45
			} else {
				mask = IN_CLASSC_NET;
E 45
I 45
				break;
			case IN_CLASSC_NET:
E 45
				subnetshift = 4;
I 45
				break;
			default:
				abort();
E 45
			}
E 14
			/*
D 14
			 * Try for subnet addresses.
E 14
I 14
			 * If there are more bits than the standard mask
			 * would suggest, subnets must be in use.
			 * Guess at the subnet mask, assuming reasonable
			 * width subnet fields.
E 14
			 */
D 14
			for (i = 0; ((0xf<<i) & in.s_addr) == 0; i += 4)
				;
			for ( ; i; i -= 4)
			    if (np = getnetbyaddr((unsigned)in.s_addr >> i,
				    AF_INET))
					break;
E 14
I 14
D 20
			while (in.s_addr &~ mask)
E 20
I 20
			while (i &~ mask)
E 20
				mask = (long)mask >> subnetshift;
E 14
		}
I 14
D 20
		net = in.s_addr & mask;
E 20
I 20
		net = i & mask;
E 20
		while ((mask & 1) == 0)
			mask >>= 1, net >>= 1;
		np = getnetbyaddr(net, AF_INET);
E 14
		if (np)
			cp = np->n_name;
D 17
	}
E 17
I 17
D 34
	}	
E 34
I 34
	}
E 34
E 17
	if (cp)
D 22
		strcpy(line, cp);
E 22
I 22
		strncpy(line, cp, sizeof(line) - 1);
E 22
D 20
	else if ((in.s_addr & 0xffffff) == 0)
		sprintf(line, "%u", C(in.s_addr >> 24));
	else if ((in.s_addr & 0xffff) == 0)
		sprintf(line, "%u.%u", C(in.s_addr >> 24) , C(in.s_addr >> 16));
	else if ((in.s_addr & 0xff) == 0)
		sprintf(line, "%u.%u.%u", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8));
E 20
I 20
	else if ((i & 0xffffff) == 0)
		sprintf(line, "%u", C(i >> 24));
	else if ((i & 0xffff) == 0)
		sprintf(line, "%u.%u", C(i >> 24) , C(i >> 16));
	else if ((i & 0xff) == 0)
		sprintf(line, "%u.%u.%u", C(i >> 24), C(i >> 16), C(i >> 8));
E 20
	else
D 20
		sprintf(line, "%u.%u.%u.%u", C(in.s_addr >> 24),
			C(in.s_addr >> 16), C(in.s_addr >> 8), C(in.s_addr));
E 20
I 20
		sprintf(line, "%u.%u.%u.%u", C(i >> 24),
			C(i >> 16), C(i >> 8), C(i));
I 45
	domask(line+strlen(line), i, omask);
E 45
E 20
	return (line);
}
I 14

E 14
/*
E 10
 * Print routing statistics
 */
I 34
void
E 34
rt_stats(off)
D 36
	off_t off;
E 36
I 36
	u_long off;
E 36
{
	struct rtstat rtstat;

	if (off == 0) {
		printf("rtstat: symbol not in namelist\n");
		return;
	}
D 30
	klseek(kmem, off, 0);
	read(kmem, (char *)&rtstat, sizeof (rtstat));
E 30
I 30
D 34
	kvm_read(off, (char *)&rtstat, sizeof (rtstat));
E 34
I 34
	kread(off, (char *)&rtstat, sizeof (rtstat));
E 34
E 30
	printf("routing:\n");
D 18
	printf("\t%d bad routing redirect%s\n",
E 18
I 18
	printf("\t%u bad routing redirect%s\n",
E 18
		rtstat.rts_badredirect, plural(rtstat.rts_badredirect));
D 18
	printf("\t%d dynamically created route%s\n",
E 18
I 18
	printf("\t%u dynamically created route%s\n",
E 18
		rtstat.rts_dynamic, plural(rtstat.rts_dynamic));
D 18
	printf("\t%d new gateway%s due to redirects\n",
E 18
I 18
	printf("\t%u new gateway%s due to redirects\n",
E 18
		rtstat.rts_newgateway, plural(rtstat.rts_newgateway));
D 18
	printf("\t%d destination%s found unreachable\n",
E 18
I 18
	printf("\t%u destination%s found unreachable\n",
E 18
		rtstat.rts_unreach, plural(rtstat.rts_unreach));
D 18
	printf("\t%d use%s of a wildcard route\n",
E 18
I 18
	printf("\t%u use%s of a wildcard route\n",
E 18
		rtstat.rts_wildcard, plural(rtstat.rts_wildcard));
I 12
}
I 16
short ns_nullh[] = {0,0,0};
E 16
short ns_bh[] = {-1,-1,-1};

char *
D 34
ns_print(sns)
struct sockaddr_ns *sns;
E 34
I 34
ns_print(sa)
	register struct sockaddr *sa;
E 34
{
I 34
	register struct sockaddr_ns *sns = (struct sockaddr_ns*)sa;
E 34
D 16
	register struct ns_addr *dna = &sns->sns_addr;
	long net = ntohl(ns_netof(*dna));
	static char mybuf[50];
	register char *p = mybuf;
	short port = dna->x_port;
E 16
I 16
	struct ns_addr work;
	union { union ns_net net_e; u_long long_e; } net;
	u_short port;
	static char mybuf[50], cport[10], chost[25];
	char *host = "";
D 17
	register char *p; register u_char *q; u_char *q_lim;
E 17
I 17
	register char *p; register u_char *q;
E 17
E 16

D 13
	sprintf(p,"%ld:", net);
E 13
I 13
D 16
	sprintf(p,"%lx:", net);
E 16
I 16
	work = sns->sns_addr;
	port = ntohs(work.x_port);
	work.x_port = 0;
	net.net_e  = work.x_net;
	if (ns_nullhost(work) && net.long_e == 0) {
		if (port ) {
			sprintf(mybuf, "*.%xH", port);
			upHex(mybuf);
		} else
			sprintf(mybuf, "*.*");
		return (mybuf);
	}
E 16
E 13

D 16
	while(*p)p++; /* find end of string */

	if (strncmp(ns_bh,dna->x_host.c_host,6)==0)
		sprintf(p,"any");
	else
		sprintf(p,"%x.%x.%x.%x.%x.%x",
			    dna->x_host.c_host[0], dna->x_host.c_host[1],
			    dna->x_host.c_host[2], dna->x_host.c_host[3],
			    dna->x_host.c_host[4], dna->x_host.c_host[5]);
	if (port) {
	while(*p)p++; /* find end of string */
D 13
		printf(":%d",port);
E 13
I 13
		sprintf(p,":%x",ntohs(port));
E 16
I 16
D 29
	if (bcmp(ns_bh, work.x_host.c_host, 6) == 0) { 
E 29
I 29
	if (bcmp(ns_bh, work.x_host.c_host, 6) == 0) {
E 29
		host = "any";
	} else if (bcmp(ns_nullh, work.x_host.c_host, 6) == 0) {
		host = "*";
	} else {
		q = work.x_host.c_host;
		sprintf(chost, "%02x%02x%02x%02x%02x%02xH",
			q[0], q[1], q[2], q[3], q[4], q[5]);
D 34
		for (p = chost; *p == '0' && p < chost + 12; p++);
E 34
I 34
		for (p = chost; *p == '0' && p < chost + 12; p++)
			continue;
E 34
		host = p;
E 16
E 13
	}
I 16
	if (port)
		sprintf(cport, ".%xH", htons(port));
	else
		*cport = 0;

	sprintf(mybuf,"%xH.%s%s", ntohl(net.long_e), host, cport);
	upHex(mybuf);
E 16
	return(mybuf);
}
I 16

E 16
char *
D 34
ns_phost(sns)
struct sockaddr_ns *sns;
E 34
I 34
ns_phost(sa)
	struct sockaddr *sa;
E 34
{
I 34
	register struct sockaddr_ns *sns = (struct sockaddr_ns *)sa;
E 34
D 16
	register struct ns_addr *dna = &sns->sns_addr;
	long net = ntohl(ns_netof(*dna));
	static char mybuf[50];
	register char *p = mybuf;
	if (strncmp(ns_bh,dna->x_host.c_host,6)==0)
		sprintf(p,"any");
	else
		sprintf(p,"%x,%x,%x",
			   dna->x_host.s_host[0], dna->x_host.s_host[1],
			    dna->x_host.s_host[2]);
	return(mybuf);
E 16
I 16
	struct sockaddr_ns work;
	static union ns_net ns_zeronet;
	char *p;
D 34
	
E 34
I 34

E 34
	work = *sns;
	work.sns_addr.x_port = 0;
	work.sns_addr.x_net = ns_zeronet;

D 34
	p = ns_print(&work);
E 34
I 34
	p = ns_print((struct sockaddr *)&work);
E 34
	if (strncmp("0H.", p, 3) == 0) p += 3;
	return(p);
}
I 34

void
E 34
upHex(p0)
D 34
char *p0;
E 34
I 34
	char *p0;
E 34
{
	register char *p = p0;
	for (; *p; p++) switch (*p) {

	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		*p += ('A' - 'a');
	}
E 16
E 12
I 7
D 10
}

/*
 * Return the possible subnetwork number from an internet address.
 * If the address is of the form of a subnet address (most significant
 * bit of the host part is set), believe the subnet exists.
 * Otherwise, return the network number.
 * SHOULD FIND OUT WHETHER THIS IS A LOCAL NETWORK BEFORE LOOKING
 * INSIDE OF THE HOST PART.  We can only believe this if we have other
 * information (e.g., we can find a name for this number).
 */
inet_subnetof(in)
	struct in_addr in;
{
	register u_long i = ntohl(in.s_addr);

	if (IN_CLASSA(i)) {
		if (IN_SUBNETA(i))
			return ((i & IN_CLASSA_SUBNET) >> IN_CLASSA_SUBNSHIFT);
		else
			return ((i & IN_CLASSA_NET) >> IN_CLASSA_NSHIFT);
	} else if (IN_CLASSB(i)) {
		if (IN_SUBNETB(i))
			return ((i & IN_CLASSB_SUBNET) >> IN_CLASSB_SUBNSHIFT);
		else
			return ((i & IN_CLASSB_NET) >> IN_CLASSB_NSHIFT);
	} else
		return ((i & IN_CLASSC_NET) >> IN_CLASSC_NSHIFT);
E 10
E 7
E 6
}
E 1
