h30303
s 00002/00002/00132
d D 8.1 93/06/10 23:35:06 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00013/00121
d D 7.9 92/10/11 12:26:28 bostic 19 18
c make kernel includes standard
e
s 00001/00001/00133
d D 7.8 90/12/16 16:40:02 bostic 18 17
c kernel reorg
e
s 00001/00011/00133
d D 7.7 90/06/28 21:48:36 bostic 17 16
c new copyright notice
e
s 00002/00001/00142
d D 7.6 90/04/05 11:52:49 sklower 16 15
c if_output needs rtentry ptr
e
s 00005/00002/00138
d D 7.5 89/04/22 12:14:16 sklower 15 14
c changes for var. length sockaddrs, routing lookup changes,
c checkpoint at first working tp4 connection, before gnodes
e
s 00001/00000/00139
d D 7.4 88/10/12 14:56:35 sklower 14 13
c checkpoint version with mbuf changes before var sockaddrs
e
s 00011/00006/00128
d D 7.3 88/06/29 17:13:29 bostic 13 12
c install approved copyright notice
e
s 00010/00004/00124
d D 7.2 88/01/20 15:15:23 sklower 12 11
c Change licensing/use notice.
e
s 00001/00001/00127
d D 7.1 86/06/05 00:37:30 mckusick 11 10
c 4.3BSD release version
e
s 00001/00001/00127
d D 6.10 86/02/23 23:27:51 karels 10 9
c lint
e
s 00001/00001/00127
d D 6.9 86/02/03 17:40:41 sklower 9 8
c Correct erroneous copyright information.
e
s 00001/00000/00127
d D 6.8 85/11/20 17:29:30 sklower 8 7
c must wipe out pointer to old rtentry before rtalloc'ing a new one.
e
s 00008/00017/00119
d D 6.7 85/09/26 15:24:55 sklower 7 6
c 1.) under rare circumstances, interface tracing attempts might fail
c 2.) simplify ROUTETOIF for pt to pt interfaces.
c 3.) trace interfaces when debugging output.
e
s 00011/00000/00125
d D 6.6 85/09/13 20:03:41 sklower 6 5
c if we got a packet from network zero, it didn't advance the ia
c pointer when searching to identify the interface it arrived on.
e
s 00002/00003/00123
d D 6.5 85/08/09 11:35:25 sklower 5 4
c 
e
s 00004/00003/00122
d D 6.4 85/06/16 12:43:17 sklower 4 3
c For routing to pt to pt hosts, port # must be 0 in sockaddr.
e
s 00007/00001/00118
d D 6.3 85/06/08 12:51:09 mckusick 3 2
c Add copyright
e
s 00003/00003/00116
d D 6.2 85/06/01 10:52:15 sklower 2 1
c turn debugging options off by default.
e
s 00119/00000/00000
d D 6.1 85/05/30 19:10:59 sklower 1 0
c date and time created 85/05/30 19:10:59 by sklower
e
u
U
t
T
I 1
D 3
/*      %M%     %I%     %E%     */
E 3
I 3
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
D 11
 * Copyright (c) 1984, 1985 Regents of the University of California.
E 11
I 11
D 12
 * Copyright (c) 1984, 1985, 1986 Regents of the University of California.
E 11
E 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
D 20
 * Copyright (c) 1984, 1985, 1986, 1987 Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1984, 1985, 1986, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
E 12
 *
D 12
 *	%W% (Berkeley) %G%
E 12
I 12
D 17
 * Redistribution and use in source and binary forms are permitted
D 13
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 13
I 13
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
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 13
 *
D 13
 *      %W% (Berkeley) %G%
E 13
I 13
 *	%W% (Berkeley) %G%
E 13
E 12
 */
E 3

D 19
#include "param.h"
I 14
#include "malloc.h"
E 14
#include "mbuf.h"
#include "errno.h"
#include "socket.h"
#include "socketvar.h"
E 19
I 19
#include <sys/param.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
E 19

D 19
#include "../net/if.h"
#include "../net/route.h"
E 19
I 19
#include <net/if.h>
#include <net/route.h>
E 19

D 19
#include "ns.h"
#include "ns_if.h"
#include "idp.h"
#include "idp_var.h"
E 19
I 19
#include <netns/ns.h>
#include <netns/ns_if.h>
#include <netns/idp.h>
#include <netns/idp_var.h>
E 19

#ifdef vax
D 18
#include "../vax/mtpr.h"
E 18
I 18
D 19
#include "vax/include/mtpr.h"
E 19
I 19
#include <machine/mtpr.h>
E 19
E 18
#endif
D 2
int ns_hold_output = 1;
int ns_copy_output = 1;
E 2
I 2
int ns_hold_output = 0;
int ns_copy_output = 0;
int ns_output_cnt = 0;
E 2
struct mbuf *ns_lastout;

D 2
int ns_output_cnt = 0;
E 2
ns_output(m0, ro, flags)
	struct mbuf *m0;
	struct route *ro;
	int flags;
{
	register struct idp *idp = mtod(m0, struct idp *);
D 7
	register struct ifnet *ifp;
E 7
I 7
	register struct ifnet *ifp = 0;
E 7
D 5
	register struct mbuf *m;
	int len, rlen, off, error = 0;
E 5
I 5
	int error = 0;
E 5
	struct route idproute;
	struct sockaddr_ns *dst;
	extern int idpcksum;

D 4
	if(ns_hold_output) {
		if(ns_lastout) {
E 4
I 4
	if (ns_hold_output) {
		if (ns_lastout) {
E 4
D 10
			m_free(ns_lastout);
E 10
I 10
			(void)m_free(ns_lastout);
E 10
		}
D 5
		ns_lastout = m_copy(m0, 0, M_COPYALL);
E 5
I 5
		ns_lastout = m_copy(m0, 0, (int)M_COPYALL);
E 5
	}
D 4
	if(ns_copy_output) {
E 4
I 4
D 7
	if (ns_copy_output) {
E 4
		ns_watch_output(m0);
	}

E 7
	/*
	 * Route packet.
	 */
	if (ro == 0) {
		ro = &idproute;
		bzero((caddr_t)ro, sizeof (*ro));
	}
	dst = (struct sockaddr_ns *)&ro->ro_dst;
	if (ro->ro_rt == 0) {
		dst->sns_family = AF_NS;
I 15
		dst->sns_len = sizeof (*dst);
E 15
		dst->sns_addr = idp->idp_dna;
I 4
		dst->sns_addr.x_port = 0;
E 4
		/*
		 * If routing to interface only,
		 * short circuit routing lookup.
		 */
		if (flags & NS_ROUTETOIF) {
D 7
			struct ns_ifaddr *ia;
I 6
			struct ifaddr *ifa_ifwithdstaddr();
E 7
I 7
			struct ns_ifaddr *ia = ns_iaonnetof(&idp->idp_dna);
E 7

E 6
D 7
			ia = ns_iaonnetof(idp->idp_dna.x_net);
E 7
			if (ia == 0) {
				error = ENETUNREACH;
				goto bad;
			}
			ifp = ia->ia_ifp;
I 6
D 7
			if (ifp->if_flags & IFF_POINTOPOINT) {
				ia = (struct ns_ifaddr *)
					ifa_ifwithdstaddr(&ro->ro_dst);
				if (ia == 0) {
					error = ENETUNREACH;
					goto bad;
				}
				ifp = ia->ia_ifp;
			}
E 7
E 6
			goto gotif;
		}
		rtalloc(ro);
	} else if ((ro->ro_rt->rt_flags & RTF_UP) == 0) {
		/*
		 * The old route has gone away; try for a new one.
		 */
		rtfree(ro->ro_rt);
I 8
		ro->ro_rt = NULL;
E 8
		rtalloc(ro);
	}
	if (ro->ro_rt == 0 || (ifp = ro->ro_rt->rt_ifp) == 0) {
		error = ENETUNREACH;
		goto bad;
	}
	ro->ro_rt->rt_use++;
	if (ro->ro_rt->rt_flags & (RTF_GATEWAY|RTF_HOST))
D 15
		dst = (struct sockaddr_ns *)&ro->ro_rt->rt_gateway;
E 15
I 15
		dst = (struct sockaddr_ns *)ro->ro_rt->rt_gateway;
E 15
gotif:

	/*
	 * Look for multicast addresses and
	 * and verify user is allowed to send
	 * such a packet.
	 */
	if (dst->sns_addr.x_host.c_host[0]&1) {
		if ((ifp->if_flags & IFF_BROADCAST) == 0) {
			error = EADDRNOTAVAIL;
			goto bad;
		}
		if ((flags & NS_ALLOWBROADCAST) == 0) {
			error = EACCES;
			goto bad;
		}
	}

	if (htons(idp->idp_len) <= ifp->if_mtu) {
		ns_output_cnt++;
I 7
		if (ns_copy_output) {
			ns_watch_output(m0, ifp);
		}
E 7
D 16
		error = (*ifp->if_output)(ifp, m0, (struct sockaddr *)dst);
E 16
I 16
		error = (*ifp->if_output)(ifp, m0,
					(struct sockaddr *)dst, ro->ro_rt);
E 16
		goto done;
	} else error = EMSGSIZE;


bad:
I 7
	if (ns_copy_output) {
		ns_watch_output(m0, ifp);
	}
E 7
	m_freem(m0);
done:
D 15
	if (ro == &idproute && (flags & NS_ROUTETOIF) == 0 && ro->ro_rt)
E 15
I 15
	if (ro == &idproute && (flags & NS_ROUTETOIF) == 0 && ro->ro_rt) {
E 15
		RTFREE(ro->ro_rt);
I 15
		ro->ro_rt = 0;
	}
E 15
	return (error);
}
E 1
