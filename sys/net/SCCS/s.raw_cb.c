h15275
s 00002/00002/00116
d D 8.1 93/06/10 22:45:17 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00114
d D 7.14 93/06/04 17:31:35 bostic 48 47
c prototype everything
e
s 00012/00012/00102
d D 7.13 92/10/11 11:49:04 bostic 47 45
c make kernel includes standard
e
s 00001/00000/00114
d R 7.13 92/02/15 17:44:52 mckusick 46 45
c must include proc.h before socketvar.h
e
s 00000/00002/00114
d D 7.12 92/01/30 11:43:31 torek 45 44
c checked in for torek by sklower; Mike agrees to all these changes
e
s 00001/00011/00115
d D 7.11 90/06/28 21:31:44 bostic 44 43
c new copyright notice
e
s 00003/00008/00123
d D 7.10 90/06/28 17:30:36 karels 43 42
c use soreserve instead of sbreserve * 2 (sets lowat)
e
s 00001/00001/00130
d D 7.9 89/04/25 11:06:28 mckusick 42 41
c ../machine => machine
e
s 00022/00051/00109
d D 7.8 89/04/22 12:10:56 sklower 41 40
c checkpoint at first working tp4 connection; before gnodes
e
s 00005/00002/00155
d D 7.7 89/02/17 10:43:12 karels 40 39
c patchable raw sockbuf sizes
e
s 00010/00005/00147
d D 7.6 88/06/27 18:59:38 bostic 39 38
c install approved copyright notice
e
s 00002/00002/00150
d D 7.5 88/05/31 08:39:04 karels 38 37
c lint
e
s 00008/00002/00144
d D 7.4 87/12/30 11:57:35 bostic 37 36
c add Berkeley header
e
s 00001/00001/00145
d D 7.3 86/10/28 22:31:21 karels 36 35
c merge in tahoe
e
s 00001/00001/00145
d D 7.2 86/07/17 10:20:09 karels 35 34
c unneeded
e
s 00001/00001/00145
d D 7.1 86/06/04 23:40:57 mckusick 34 33
c 4.3BSD release version
e
s 00000/00003/00146
d D 6.10 86/03/30 21:40:51 karels 33 32
c expunge PUP; fill in AFNULL entries up to AF_MAX again
e
s 00002/00000/00147
d D 6.9 86/02/02 20:11:20 karels 32 31
c add per-protocol options in rawcb (freed at detach)
e
s 00001/00023/00146
d D 6.8 85/12/19 16:12:59 karels 31 30
c rm bbnnet; rm PUP
e
s 00003/00001/00166
d D 6.7 85/09/16 21:13:06 karels 30 29
c free those routes; INET || BBNNET
e
s 00007/00001/00160
d D 6.6 85/06/08 12:26:42 mckusick 29 28
c Add copyright
e
s 00007/00002/00154
d D 6.5 85/06/02 23:37:53 karels 28 27
c allow raw socket of any protocol if family has wildcard entry,
c with actual protocol number in raw_cb instead of protosw
e
s 00002/00000/00154
d D 6.4 85/05/04 22:53:59 bloom 27 26
c ifdef PUP include files
e
s 00003/00003/00151
d D 6.3 85/03/19 16:01:13 karels 26 25
c move net addresses from interface layer into protocols
e
s 00009/00009/00145
d D 6.2 84/08/29 16:07:05 bloom 25 22
c Include file changes.  No more ../h
e
s 00011/00011/00143
d R 6.2 84/08/28 17:39:04 bloom 24 22
c fix header includes.  no more ../h
e
s 00006/00006/00148
d R 6.2 84/08/28 17:13:28 bloom 23 22
c Change include paths.  No more ../h.
e
s 00000/00000/00154
d D 6.1 83/07/29 07:08:43 sam 22 21
c 4.2 distribution
e
s 00001/00000/00153
d D 4.20 83/06/30 01:14:29 sam 21 20
c routing for raw stuff
e
s 00001/00002/00152
d D 4.19 83/06/20 21:45:55 sam 20 18
c do it "right"?
e
s 00001/00002/00152
d R 4.19 83/06/19 17:25:39 sam 19 18
c do it "right"?
e
s 00002/00002/00152
d D 4.18 83/05/30 18:49:10 sam 18 17
c track pup changes
e
s 00006/00007/00148
d D 4.17 83/05/27 13:56:35 sam 17 16
c lint and wnj changes
e
s 00004/00002/00151
d D 4.16 83/02/10 22:00:55 sam 16 15
c remove /usr/include dependencies
e
s 00001/00001/00152
d D 4.15 82/12/14 17:13:44 sam 15 14
c typed mbufs
e
s 00003/00001/00150
d D 4.14 82/11/13 23:10:40 sam 14 13
c merge 4.1b and 4.1c
e
s 00003/00003/00148
d D 4.13 82/10/31 15:01:26 root 13 12
c header file changes; still wont work (interface to socket code)
e
s 00066/00052/00085
d D 4.12 82/10/09 05:40:13 wnj 12 11
c header file dependencies fixed up and untested changes to raw interface
e
s 00001/00001/00136
d D 4.11 82/07/24 18:21:20 root 11 10
c from calder
e
s 00001/00001/00136
d D 4.10 82/06/26 22:02:17 sam 10 9
c use <errno.h>
e
s 00000/00004/00137
d D 4.9 82/06/20 00:54:47 sam 9 8
c purge COUNT stuff now that we can use gprof
e
s 00003/00002/00138
d D 4.8 82/04/11 15:51:33 sam 8 7
c sundry patches to raw code after rewrite
e
s 00006/00004/00134
d D 4.7 82/04/10 23:41:24 sam 7 6
c purge so_addr from socket structure and start cleaning up raw code
e
s 00030/00016/00108
d D 4.6 82/03/28 14:23:08 sam 6 5
c convert interfaces to sockaddr's and add hooks for routing
e
s 00003/00003/00121
d D 4.5 82/03/13 12:52:22 sam 5 4
c lint
e
s 00006/00001/00118
d D 4.4 82/03/05 14:07:00 wnj 4 3
c minor fixes
e
s 00001/00000/00118
d D 4.3 82/02/12 15:17:41 wnj 3 2
c closer to a working imp driver
e
s 00000/00009/00118
d D 4.2 82/02/01 17:50:23 sam 2 1
c raw interfaces brought up to date
e
s 00127/00000/00000
d D 4.1 82/02/01 12:59:37 root 1 0
c date and time created 82/02/01 12:59:37 by root
e
u
U
t
T
I 1
D 29
/*	%M%	%I%	%E%	*/
E 29
I 29
/*
D 34
 * Copyright (c) 1980 Regents of the University of California.
E 34
I 34
D 49
 * Copyright (c) 1980, 1986 Regents of the University of California.
E 34
D 37
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 37
I 37
 * All rights reserved.
E 49
I 49
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 49
 *
D 44
 * Redistribution and use in source and binary forms are permitted
D 39
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 39
I 39
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
E 44
I 44
 * %sccs.include.redist.c%
E 44
E 39
E 37
 *
 *	%W% (Berkeley) %G%
 */
E 29

D 25
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
D 13
#include "../h/mtpr.h"
E 13
I 13
D 16
#include "../vax/mtpr.h"
E 16
I 16
#include "../h/errno.h"
E 25
I 25
D 47
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
I 28
#include "domain.h"
#include "protosw.h"
E 28
#include "errno.h"
E 47
I 47
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/errno.h>
E 47
E 25

E 16
E 13
D 12
#include "../net/in.h"
#include "../net/in_systm.h"
E 12
D 25
#include "../net/if.h"
I 21
#include "../net/route.h"
E 21
#include "../net/raw_cb.h"
E 25
I 25
D 47
#include "if.h"
#include "route.h"
#include "raw_cb.h"
E 25
I 17
#include "../netinet/in.h"
E 47
I 47
#include <net/if.h>
#include <net/route.h>
#include <net/raw_cb.h>
#include <netinet/in.h>
E 47
I 27
D 33
#ifdef PUP
E 27
#include "../netpup/pup.h"
I 27
#endif
E 33
E 27
E 17
I 6
D 12
#include "../net/pup.h"
E 12
E 6
D 4
#include "/usr/include/errno.h"
E 4
I 4
D 10
#include "../errno.h"
E 10
I 10
D 16
#include <errno.h>
E 16
I 16

D 36
#include "../vax/mtpr.h"
E 36
I 36
D 42
#include "../machine/mtpr.h"
E 42
I 42
D 45
#include "machine/mtpr.h"
E 42
E 36
E 16
E 10
E 4

E 45
/*
 * Routines to manage the raw protocol control blocks. 
 *
 * TODO:
 *	hash lookups by protocol family/protocol + address family
D 6
 *	take care of unique address problems per AF
E 6
I 6
 *	take care of unique address problems per AF?
E 6
I 4
 *	redo address binding to allow wildcards
E 4
 */

I 40
u_long	raw_sendspace = RAWSNDQ;
u_long	raw_recvspace = RAWRCVQ;

E 40
/*
 * Allocate a control block and a nominal amount
 * of buffer space for the socket.
 */
I 48
int
E 48
D 12
raw_attach(so, addr)
E 12
I 12
D 28
raw_attach(so)
E 28
I 28
raw_attach(so, proto)
E 28
E 12
	register struct socket *so;
I 28
	int proto;
E 28
D 12
	struct sockaddr *addr;
E 12
{
D 41
	struct mbuf *m;
	register struct rawcb *rp;
E 41
I 41
	register struct rawcb *rp = sotorawcb(so);
I 43
	int error;
E 43
E 41
D 6
	struct ifnet *ifp = ifnet;
E 6

D 9
COUNT(RAW_ATTACH);
E 9
I 6
D 12
	if (ifnet == 0)
		return (EADDRNOTAVAIL);
E 6
D 2
	if (so->so_options & SO_DEBUG)
		printf("raw_attach: addr=%d\n", addr->sa_family);
E 2
	/*
	 * Should we verify address not already in use?
	 * Some say yes, others no.
	 */
	if (addr) switch (addr->sa_family) {

I 3
	case AF_IMPLINK:
E 3
D 6
	case AF_INET: {
		register struct sockaddr_in *sin = (struct sockaddr_in *)addr;

		if (ifnet && sin->sin_addr.s_addr == 0)
			sin->sin_addr = ifnet->if_addr;
		ifp = if_ifwithaddr(sin->sin_addr);
E 6
I 6
	case AF_INET:
		if (((struct sockaddr_in *)addr)->sin_addr.s_addr &&
		    if_ifwithaddr(addr) == 0)
			return (EADDRNOTAVAIL);
E 6
		break;
D 6
		}
E 6
I 4

D 6
	case AF_PUP:
		ifp = ifnet;
E 6
I 6
#ifdef PUP
	/*
	 * Curious, we convert PUP address format to internet
	 * to allow us to verify we're asking for an Ethernet
	 * interface.  This is wrong, but things are heavily
	 * oriented towards the internet addressing scheme, and
	 * converting internet to PUP would be very expensive.
	 */
	case AF_PUP: {
		struct sockaddr_pup *spup = (struct sockaddr_pup *)addr;
		struct sockaddr_in inpup;

		bzero((caddr_t)&inpup, sizeof(inpup));
I 7
		inpup.sin_family = AF_INET;
E 7
		inpup.sin_addr.s_net = spup->sp_net;
		inpup.sin_addr.s_impno = spup->sp_host;
		if (inpup.sin_addr.s_addr &&
		    if_ifwithaddr((struct sockaddr *)&inpup) == 0)
			return (EADDRNOTAVAIL);
E 6
		break;
I 6
	}
#endif
E 6
E 4

	default:
		return (EAFNOSUPPORT);
	}
E 12
D 6
	if (ifp == 0)
		return (EADDRNOTAVAIL);
E 6
D 15
	m = m_getclr(M_DONTWAIT);
E 15
I 15
D 41
	m = m_getclr(M_DONTWAIT, MT_PCB);
E 15
	if (m == 0)
E 41
I 41
	/*
	 * It is assumed that raw_attach is called
	 * after space has been allocated for the
	 * rawcb.
	 */
	if (rp == 0)
E 41
		return (ENOBUFS);
D 38
	if (sbreserve(&so->so_snd, RAWSNDQ) == 0)
E 38
I 38
D 40
	if (sbreserve(&so->so_snd, (u_long) RAWSNDQ) == 0)
E 40
I 40
D 43
	if (sbreserve(&so->so_snd, raw_sendspace) == 0)
E 40
E 38
		goto bad;
D 38
	if (sbreserve(&so->so_rcv, RAWRCVQ) == 0)
E 38
I 38
D 40
	if (sbreserve(&so->so_rcv, (u_long) RAWRCVQ) == 0)
E 40
I 40
	if (sbreserve(&so->so_rcv, raw_recvspace) == 0)
E 40
E 38
		goto bad2;
E 43
I 43
	if (error = soreserve(so, raw_sendspace, raw_recvspace))
		return (error);
E 43
D 41
	rp = mtod(m, struct rawcb *);
E 41
	rp->rcb_socket = so;
D 28
	insque(rp, &rawcb);
E 28
D 41
	so->so_pcb = (caddr_t)rp;
	rp->rcb_pcb = 0;
E 41
I 28
	rp->rcb_proto.sp_family = so->so_proto->pr_domain->dom_family;
	rp->rcb_proto.sp_protocol = proto;
	insque(rp, &rawcb);
E 28
D 6

E 6
D 8
	if (addr)
E 8
I 8
D 12
	if (addr) {
E 8
D 5
		bcopy(addr, &so->so_addr, sizeof(*addr));
E 5
I 5
D 7
		bcopy((caddr_t)addr, (caddr_t)&so->so_addr, sizeof(*addr));
E 7
I 7
		bcopy((caddr_t)addr, (caddr_t)&rp->rcb_laddr, sizeof(*addr));
D 8
	rp->rcb_flags |= RAW_LADDR;
E 8
I 8
		rp->rcb_flags |= RAW_LADDR;
	}
E 12
E 8
E 7
E 5
	return (0);
D 43
bad2:
	sbrelease(&so->so_snd);
bad:
D 41
	(void) m_free(m);
E 41
	return (ENOBUFS);
E 43
}

/*
 * Detach the raw connection block and discard
 * socket resources.
 */
I 48
void
E 48
raw_detach(rp)
	register struct rawcb *rp;
{
	struct socket *so = rp->rcb_socket;

I 30
D 41
	if (rp->rcb_route.ro_rt)
		rtfree(rp->rcb_route.ro_rt);
E 41
E 30
D 9
COUNT(RAW_DETACH);
E 9
D 2
	if (rp->rcb_socket->so_options & SO_DEBUG)
		printf("raw_detach: rp=%X\n", rp);
E 2
	so->so_pcb = 0;
	sofree(so);
	remque(rp);
I 32
D 41
	if (rp->rcb_options)
D 35
		m_freem(dtom(rp->rcb_options));
E 35
I 35
		m_freem(rp->rcb_options);
E 35
E 32
D 5
	(void) m_freem(dtom(rp));
E 5
I 5
D 6
	m_freem(dtom(rp));
E 6
I 6
D 13
	(void) m_freem(dtom(rp));
E 13
I 13
	m_freem(dtom(rp));
E 41
I 41
#ifdef notdef
	if (rp->rcb_laddr)
		m_freem(dtom(rp->rcb_laddr));
	rp->rcb_laddr = 0;
#endif
	free((caddr_t)(rp), M_PCB);
E 41
E 13
E 6
E 5
}

/*
 * Disconnect and possibly release resources.
 */
I 48
void
E 48
raw_disconnect(rp)
	struct rawcb *rp;
{
I 13

E 13
D 9
COUNT(RAW_DISCONNECT);
E 9
D 2
	if (rp->rcb_socket->so_options & SO_DEBUG)
		printf("raw_disconnect: rp=%X\n", rp);
E 2
D 7
	rp->rcb_flags &= ~RAW_ADDR;
E 7
I 7
D 41
	rp->rcb_flags &= ~RAW_FADDR;
E 41
I 41
#ifdef notdef
	if (rp->rcb_faddr)
		m_freem(dtom(rp->rcb_faddr));
	rp->rcb_faddr = 0;
#endif
E 41
E 7
D 11
	if (rp->rcb_socket->so_state & SS_USERGONE)
E 11
I 11
	if (rp->rcb_socket->so_state & SS_NOFDREF)
E 11
		raw_detach(rp);
}

I 41
#ifdef notdef
I 48
int
E 48
E 41
I 12
raw_bind(so, nam)
	register struct socket *so;
	struct mbuf *nam;
{
	struct sockaddr *addr = mtod(nam, struct sockaddr *);
D 13
	struct mbuf *m;
E 13
	register struct rawcb *rp;

	if (ifnet == 0)
		return (EADDRNOTAVAIL);
D 17
{
I 14
#include "../h/domain.h"
E 14
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
E 17
D 41
/* BEGIN DUBIOUS */
	/*
	 * Should we verify address not already in use?
	 * Some say yes, others no.
	 */
	switch (addr->sa_family) {

I 17
D 30
#ifdef INET
E 30
I 30
D 31
#if defined(INET) || defined(BBNNET)
E 31
I 31
#ifdef INET
E 31
E 30
E 17
	case AF_IMPLINK:
D 17
	case AF_INET:
E 17
I 17
	case AF_INET: {
E 17
		if (((struct sockaddr_in *)addr)->sin_addr.s_addr &&
D 26
		    if_ifwithaddr(addr) == 0)
E 26
I 26
		    ifa_ifwithaddr(addr) == 0)
E 26
D 31
			return (EADDRNOTAVAIL);
		break;
I 17
	}
#endif
E 17

#ifdef PUP
	/*
	 * Curious, we convert PUP address format to internet
	 * to allow us to verify we're asking for an Ethernet
	 * interface.  This is wrong, but things are heavily
	 * oriented towards the internet addressing scheme, and
	 * converting internet to PUP would be very expensive.
	 */
	case AF_PUP: {
D 17
#include "../netpup/pup.h"
E 17
		struct sockaddr_pup *spup = (struct sockaddr_pup *)addr;
		struct sockaddr_in inpup;

D 14
		bzero((caddr_t)&inpup, sizeof(inpup));
E 14
I 14
		bzero((caddr_t)&inpup, (unsigned)sizeof(inpup));
E 14
		inpup.sin_family = AF_INET;
D 18
		inpup.sin_addr.s_net = spup->sp_net;
		inpup.sin_addr.s_impno = spup->sp_host;
E 18
I 18
D 20
		inpup.sin_addr.s_net = spup->spup_net;
		inpup.sin_addr.s_impno = spup->spup_host;
E 20
I 20
D 26
		inpup.sin_addr = if_makeaddr(spup->spup_net, spup->spup_host);
E 26
I 26
		inpup.sin_addr = in_makeaddr(spup->spup_net, spup->spup_host);
E 26
E 20
E 18
		if (inpup.sin_addr.s_addr &&
D 26
		    if_ifwithaddr((struct sockaddr *)&inpup) == 0)
E 26
I 26
		    ifa_ifwithaddr((struct sockaddr *)&inpup) == 0)
E 31
E 26
			return (EADDRNOTAVAIL);
		break;
	}
#endif

	default:
		return (EAFNOSUPPORT);
	}
D 17
}
E 17
/* END DUBIOUS */
E 41
I 14
	rp = sotorawcb(so);
E 14
D 41
	bcopy((caddr_t)addr, (caddr_t)&rp->rcb_laddr, sizeof (*addr));
	rp->rcb_flags |= RAW_LADDR;
E 41
I 41
	nam = m_copym(nam, 0, M_COPYALL, M_WAITOK);
	rp->rcb_laddr = mtod(nam, struct sockaddr *);
E 41
	return (0);
}
D 41

E 12
/*
 * Associate a peer's address with a
 * raw connection block.
 */
D 12
raw_connaddr(rp, addr)
E 12
I 12
raw_connaddr(rp, nam)
E 12
	struct rawcb *rp;
D 12
	struct sockaddr *addr;
E 12
I 12
	struct mbuf *nam;
E 12
{
I 12
	struct sockaddr *addr = mtod(nam, struct sockaddr *);

E 12
D 9
COUNT(RAW_CONNADDR);
E 9
D 2
	if (rp->rcb_socket->so_options & SO_DEBUG);
		printf("raw_connaddr: rp=%x, addr=<%x,%x>\n",
		 rp, addr->sa_family, ((struct sockaddr_in *)addr)->sin_addr);
E 2
D 5
	bcopy(addr, &rp->rcb_addr, sizeof(struct sockaddr));
E 5
I 5
D 6
	bcopy((caddr_t)addr, (caddr_t)&rp->rcb_addr, sizeof(struct sockaddr));
E 6
I 6
D 7
	bcopy((caddr_t)addr, (caddr_t)&rp->rcb_addr, sizeof(*addr));
E 6
E 5
	rp->rcb_flags |= RAW_ADDR;
E 7
I 7
	bcopy((caddr_t)addr, (caddr_t)&rp->rcb_faddr, sizeof(*addr));
	rp->rcb_flags |= RAW_FADDR;
E 7
}
E 41
I 41
#endif
E 41
E 1
