h64790
s 00006/00000/00379
d D 8.7 95/05/15 17:32:08 mckusick 50 49
c missing ifdef MROUTING (from hibler)
e
s 00028/00016/00351
d D 8.6 95/05/01 22:33:28 mckusick 49 48
c update for SETOPT/GETOPT (from karels)
e
s 00002/00002/00365
d D 8.5 95/02/09 16:49:59 mckusick 48 47
c wrong sense of comparison (from karels)
e
s 00004/00003/00363
d D 8.4 95/02/09 10:37:04 cgd 47 46
c casts to quiet compiler
e
s 00004/00001/00362
d D 8.3 95/01/12 10:22:48 mckusick 46 45
c ensure that the option mbuf is freed (from mycroft)
e
s 00000/00001/00363
d D 8.2 94/01/04 21:54:29 bostic 45 44
c lint
e
s 00002/00002/00362
d D 8.1 93/06/10 23:05:15 bostic 44 43
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00359
d D 7.14 93/06/04 17:23:13 bostic 43 42
c prototype everything
e
s 00003/00000/00357
d D 7.13 93/04/09 19:47:48 andrew 42 41
c Van's suggestion: add a means to let kernel set IP header ident #
c in IP_HDRINCL case
e
s 00009/00005/00348
d D 7.12 93/02/12 23:14:55 andrew 41 39
c for INP_HDRINCL, tell ip_output to not clobber header, so pkts
c with options are sent correctly.
e
s 00009/00005/00348
d R 7.12 93/02/12 23:04:03 andrew 40 39
c for INP_HDRINCL, tell ip_output to not clobber header, so pkts
e
s 00004/00007/00349
d D 7.11 93/01/08 18:42:49 andrew 39 38
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00016/00016/00340
d D 7.10 92/10/11 12:02:02 bostic 38 37
c make kernel includes standard
e
s 00229/00108/00127
d D 7.9 92/07/06 15:08:29 sklower 37 35
c multicast changes from lbl
e
s 00001/00000/00235
d R 7.9 92/02/15 18:00:06 mckusick 36 35
c have to include proc.h before socketvar.h
e
s 00001/00001/00234
d D 7.8 90/07/25 22:39:11 sklower 35 34
c outright bug in connect() on a raw socket.
e
s 00001/00011/00234
d D 7.7 90/06/28 21:39:02 bostic 34 33
c new copyright notice
e
s 00005/00002/00240
d D 7.6 89/09/20 13:20:08 sklower 33 32
c count undelievered IP packets for SNMP
e
s 00130/00051/00112
d D 7.5 89/04/08 16:33:55 karels 32 31
c IP_HDRINCL, separate raw_inpcb struct (by sklower)
e
s 00010/00005/00153
d D 7.4 88/06/29 17:07:10 bostic 31 30
c install approved copyright notice
e
s 00008/00002/00150
d D 7.3 87/12/07 17:45:56 bostic 30 29
c use Berkeley specific header
e
s 00001/00001/00151
d D 7.2 87/06/20 12:32:17 mckusick 29 28
c check for null mbuf ptr before freeing (4.3BSD/sys/{130,131,133})
e
s 00001/00001/00151
d D 7.1 86/06/05 00:28:54 mckusick 28 27
c 4.3BSD release version
e
s 00002/00002/00150
d D 6.8 86/02/23 23:25:05 karels 27 26
c lint
e
s 00052/00002/00100
d D 6.7 86/02/02 20:23:43 karels 26 25
c support options for raw ip
e
s 00007/00001/00095
d D 6.6 85/06/08 12:41:20 mckusick 25 24
c Add copyright
e
s 00001/00001/00095
d D 6.5 85/06/02 23:39:06 karels 24 23
c raw protocol number from raw_cb instead of protosw
e
s 00010/00010/00086
d D 6.4 84/08/29 15:36:53 bloom 23 22
c Include file changes.  No more ../h
e
s 00001/00000/00095
d D 6.3 84/07/31 17:59:30 karels 22 21
c clear ip_tos on output
e
s 00001/00000/00094
d D 6.2 83/12/15 14:58:09 karels 21 20
c must clear ip_off before output (don't want IP_DF)
e
s 00000/00000/00094
d D 6.1 83/07/29 07:12:00 sam 20 19
c 4.2 distribution
e
s 00005/00005/00089
d D 4.19 83/06/30 01:22:13 sam 19 18
c raw routing
e
s 00002/00001/00092
d D 4.18 83/05/12 15:04:24 sam 18 17
c fix ip packet forwarding to not stomp on headers when fragmented;
e
s 00005/00003/00088
d D 4.17 83/02/10 22:11:44 sam 17 16
c remove /usr/include dependencies
e
s 00001/00001/00090
d D 4.16 82/12/14 17:15:37 sam 16 15
c typed mbufs
e
s 00000/00001/00091
d D 4.15 82/10/17 14:55:42 root 15 14
c fix lint
e
s 00004/00004/00088
d D 4.14 82/10/09 05:46:42 wnj 14 13
c localize header files
e
s 00000/00002/00092
d D 4.13 82/06/20 00:54:57 sam 13 12
c purge COUNT stuff now that we can use gprof
e
s 00010/00016/00084
d D 4.12 82/06/12 23:19:43 wnj 12 11
c now the routing code might wokr
e
s 00002/00002/00098
d D 4.11 82/04/11 15:51:40 sam 11 10
c sundry patches to raw code after rewrite
e
s 00028/00010/00072
d D 4.10 82/04/10 23:41:34 sam 10 9
c purge so_addr from socket structure and start cleaning up raw code
e
s 00004/00041/00078
d D 4.9 82/03/28 14:23:19 sam 9 8
c convert interfaces to sockaddr's and add hooks for routing
e
s 00001/00001/00118
d D 4.8 82/03/15 04:44:27 wnj 8 7
c interfac queueing, restrictions on packets, tcp keep alives done 
c properly, bug fix to raw
e
s 00003/00002/00116
d D 4.7 82/03/13 12:52:30 sam 7 6
c lint
e
s 00001/00003/00117
d D 4.6 82/03/12 16:15:02 sam 6 5
c lint
e
s 00001/00001/00119
d D 4.5 82/03/05 10:20:31 root 5 4
c move location of errno.h
e
s 00005/00002/00115
d D 4.4 82/02/02 19:40:23 sam 4 3
c pass structures by reference
e
s 00005/00006/00112
d D 4.3 82/02/01 17:50:36 sam 3 2
c raw interfaces brought up to date
e
s 00078/00018/00040
d D 4.2 82/01/24 18:36:02 wnj 2 1
c early versions
e
s 00058/00000/00000
d D 4.1 81/11/29 22:19:36 wnj 1 0
c date and time created 81/11/29 22:19:36 by wnj
e
u
U
t
T
I 1
D 25
/*	%M%	%I%	%E%	*/
E 25
I 25
/*
D 28
 * Copyright (c) 1982 Regents of the University of California.
E 28
I 28
D 32
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 32
I 32
D 44
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 32
E 28
D 30
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 30
I 30
 * All rights reserved.
E 44
I 44
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 44
 *
D 34
 * Redistribution and use in source and binary forms are permitted
D 31
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 31
I 31
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
E 34
I 34
 * %sccs.include.redist.c%
E 34
E 31
E 30
 *
 *	%W% (Berkeley) %G%
 */
E 25

D 23
#include "../h/param.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
I 2
#include "../h/protosw.h"
E 2
#include "../h/socketvar.h"
I 17
#include "../h/errno.h"
E 23
I 23
D 38
#include "param.h"
I 32
#include "malloc.h"
E 32
#include "mbuf.h"
#include "socket.h"
#include "protosw.h"
#include "socketvar.h"
#include "errno.h"
I 37
#include "systm.h"
E 38
I 38
#include <sys/param.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/systm.h>
E 38
E 37
E 23

E 17
I 10
D 38
#include "../net/if.h"
I 17
D 19
#include "../net/raw_cb.h"
E 19
#include "../net/route.h"
E 38
I 38
#include <net/if.h>
#include <net/route.h>
E 38
I 19
D 37
#include "../net/raw_cb.h"
E 37
E 19

E 17
E 10
D 14
#include "../net/in.h"
#include "../net/in_systm.h"
I 2
#include "../net/ip.h"
#include "../net/ip_var.h"
E 14
I 14
D 23
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
#include "../netinet/ip.h"
#include "../netinet/ip_var.h"
E 23
I 23
D 38
#include "in.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
I 37
#include "ip_mroute.h"
E 37
I 32
#include "in_pcb.h"
E 38
I 38
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_mroute.h>
#include <netinet/in_pcb.h>
E 38
E 32
E 23
E 14
D 17
#include "../net/raw_cb.h"
I 12
#include "../net/route.h"
E 12
D 5
#include "/usr/include/errno.h"
E 5
I 5
D 10
#include "../errno.h"
E 10
I 10
#include <errno.h>
E 17
E 10
E 5
E 2

I 37
struct inpcb rawinpcb;

E 37
/*
I 37
 * Nominal space allocated to a raw ip socket.
 */
#define	RIPSNDQ		8192
#define	RIPRCVQ		8192

/*
E 37
D 2
 * Raw protocol interface.
E 2
I 2
 * Raw interface to IP protocol.
E 2
 */
D 2
/*ARGSUSED*/
E 2
I 2

D 3
static struct sockaddr_in ripaddr = { PF_INET };
E 3
I 3
D 9
static struct sockaddr_in ripdst = { PF_INET };
static struct sockaddr_in ripsrc = { PF_INET };
E 3
static struct sockproto ripproto = { AF_INET };
E 9
I 9
D 19
static struct sockaddr_in ripdst = { AF_INET };
static struct sockaddr_in ripsrc = { AF_INET };
static struct sockproto ripproto = { PF_INET };
E 19
I 19
D 32
struct	sockaddr_in ripdst = { AF_INET };
struct	sockaddr_in ripsrc = { AF_INET };
E 32
I 32
D 37
struct	sockaddr_in ripdst = { sizeof(ripdst), AF_INET };
E 37
I 37
/*
 * Initialize raw connection block q.
 */
I 43
void
E 43
rip_init()
{

	rawinpcb.inp_next = rawinpcb.inp_prev = &rawinpcb;
}

E 37
struct	sockaddr_in ripsrc = { sizeof(ripsrc), AF_INET };
E 32
D 37
struct	sockproto ripproto = { PF_INET };
E 37
E 19
E 9
D 10

E 10
/*
 * Setup generic address and protocol structures
 * for raw_input routine, then pass them along with
 * mbuf chain.
 */
I 43
void
E 43
E 2
rip_input(m)
	struct mbuf *m;
{
I 2
	register struct ip *ip = mtod(m, struct ip *);
I 37
	register struct inpcb *inp;
	struct socket *last = 0;
E 37
D 6
	struct sockaddr_in sin;
	struct sockproto sp;
E 6
E 2

D 13
COUNT(RIP_INPUT);
E 13
D 2

	/* call raw_input with prepared parameters */
E 2
I 2
D 37
	ripproto.sp_protocol = ip->ip_p;
D 3
	ripaddr.sin_addr = ip->ip_dst;
	raw_input(m, ripproto, ripaddr);
E 3
I 3
	ripdst.sin_addr = ip->ip_dst;
E 37
	ripsrc.sin_addr = ip->ip_src;
D 4
	raw_input(m, ripproto, ripdst, ripsrc);
E 4
I 4
D 7
	raw_input(m, &ripproto, &ripdst, &ripsrc);
E 7
I 7
D 11
	raw_input(m, &ripproto, (struct sockaddr *)&ripdst,
	  (struct sockaddr *)&ripsrc);
E 11
I 11
D 33
	raw_input(m, &ripproto, (struct sockaddr *)&ripsrc,
	  (struct sockaddr *)&ripdst);
E 33
I 33
D 37
	if (raw_input(m, &ripproto, (struct sockaddr *)&ripsrc,
	  (struct sockaddr *)&ripdst) == 0) {
E 37
I 37
	for (inp = rawinpcb.inp_next; inp != &rawinpcb; inp = inp->inp_next) {
		if (inp->inp_ip.ip_p && inp->inp_ip.ip_p != ip->ip_p)
			continue;
		if (inp->inp_laddr.s_addr &&
D 48
		    inp->inp_laddr.s_addr == ip->ip_dst.s_addr)
E 48
I 48
		    inp->inp_laddr.s_addr != ip->ip_dst.s_addr)
E 48
			continue;
		if (inp->inp_faddr.s_addr &&
D 48
		    inp->inp_faddr.s_addr == ip->ip_src.s_addr)
E 48
I 48
		    inp->inp_faddr.s_addr != ip->ip_src.s_addr)
E 48
			continue;
		if (last) {
			struct mbuf *n;
			if (n = m_copy(m, 0, (int)M_COPYALL)) {
D 47
				if (sbappendaddr(&last->so_rcv, &ripsrc,
				    n, (struct mbuf *)0) == 0)
E 47
I 47
				if (sbappendaddr(&last->so_rcv,
				    (struct sockaddr *)&ripsrc, n,
				    (struct mbuf *)0) == 0)
E 47
					/* should notify about lost packet */
					m_freem(n);
				else
					sorwakeup(last);
			}
		}
		last = inp->inp_socket;
	}
	if (last) {
D 47
		if (sbappendaddr(&last->so_rcv, &ripsrc,
E 47
I 47
		if (sbappendaddr(&last->so_rcv, (struct sockaddr *)&ripsrc,
E 47
		    m, (struct mbuf *)0) == 0)
			m_freem(m);
		else
			sorwakeup(last);
	} else {
		m_freem(m);
E 37
		ipstat.ips_noproto++;
		ipstat.ips_delivered--;
	}
E 33
E 11
E 7
E 4
E 3
E 2
}

D 9
/*ARGSUSED*/
rip_ctlinput(m)
	struct mbuf *m;
{
D 2

E 2
COUNT(RIP_CTLINPUT);
D 2

E 2
}

E 9
D 2
/*ARGSUSED*/
rip_output(m)
	struct mbuf *m;
E 2
I 2
/*
 * Generate IP header and pass packet to ip_output.
 * Tack on options user may have setup with control call.
 */
I 43
int
E 43
D 32
rip_output(m0, so)
	struct mbuf *m0;
E 32
I 32
D 37
#define	satosin(sa)	((struct sockaddr_in *)(sa))
rip_output(m, so)
E 37
I 37
rip_output(m, so, dst)
E 37
	register struct mbuf *m;
E 32
	struct socket *so;
I 37
	u_long dst;
E 37
E 2
{
I 2
D 32
	register struct mbuf *m;
E 32
	register struct ip *ip;
D 10
	register int len = 0;
	register struct rawcb *rp = sotorawcb(so);
E 10
I 10
D 32
	int len = 0, error;
	struct rawcb *rp = sotorawcb(so);
D 15
	struct ifnet *ifp;
E 15
D 12
	struct sockaddr_in *src;
E 12
I 12
	struct sockaddr_in *sin;
E 32
I 32
D 37
	register struct raw_inpcb *rp = sotorawinpcb(so);
E 37
I 37
	register struct inpcb *inp = sotoinpcb(so);
E 37
D 45
	register struct sockaddr_in *sin;
E 45
I 41
	struct mbuf *opts;
	int flags = (so->so_options & SO_DONTROUTE) | IP_ALLOWBROADCAST;
E 41
E 32
E 12
E 10
E 2

D 13
COUNT(RIP_OUTPUT);
E 13
D 2

E 2
I 2
D 3
	if (so->so_options & SO_DEBUG)
		printf("rip_output\n");
E 3
	/*
D 32
	 * Calculate data length and get an mbuf
	 * for IP header.
E 32
I 32
	 * If the user handed us a complete IP packet, use it.
	 * Otherwise, allocate an mbuf for a header and fill it in.
E 32
	 */
D 32
	for (m = m0; m; m = m->m_next)
		len += m->m_len;
D 16
	m = m_get(M_DONTWAIT);
E 16
I 16
	m = m_get(M_DONTWAIT, MT_HEADER);
E 16
	if (m == 0) {
D 4
		(void) m_freem(m);
E 4
I 4
D 10
		m_freem(m);
E 4
D 6
		return;
E 6
I 6
		return (0);
E 10
I 10
		error = ENOBUFS;
		goto bad;
E 32
I 32
D 37
	if (rp->rinp_flags & RINPF_HDRINCL)
		ip = mtod(m, struct ip *);
	else {
E 37
I 37
	if ((inp->inp_flags & INP_HDRINCL) == 0) {
E 37
		M_PREPEND(m, sizeof(struct ip), M_WAIT);
		ip = mtod(m, struct ip *);
		ip->ip_tos = 0;
		ip->ip_off = 0;
D 37
		ip->ip_p = rp->rinp_rcb.rcb_proto.sp_protocol;
E 37
I 37
		ip->ip_p = inp->inp_ip.ip_p;
E 37
		ip->ip_len = m->m_pkthdr.len;
D 37
		if (sin = satosin(rp->rinp_rcb.rcb_laddr)) {
			ip->ip_src = sin->sin_addr;
		} else
			ip->ip_src.s_addr = 0;
		if (sin = satosin(rp->rinp_rcb.rcb_faddr))
		    ip->ip_dst = sin->sin_addr;
E 37
I 37
		ip->ip_src = inp->inp_laddr;
		ip->ip_dst.s_addr = dst;
E 37
		ip->ip_ttl = MAXTTL;
I 41
		opts = inp->inp_options;
	} else {
I 42
		ip = mtod(m, struct ip *);
		if (ip->ip_id == 0)
			ip->ip_id = htons(ip_id++);
E 42
		opts = NULL;
		/* XXX prevent ip_output from overwriting header fields */
		flags |= IP_RAWOUTPUT;
		ipstat.ips_rawout++;
E 41
E 32
E 10
E 6
	}
D 32
	
	/*
	 * Fill in IP header as needed.
	 */
	m->m_off = MMAXOFF - sizeof(struct ip);
	m->m_len = sizeof(struct ip);
	m->m_next = m0;
	ip = mtod(m, struct ip *);
I 22
	ip->ip_tos = 0;
E 22
I 21
	ip->ip_off = 0;
E 21
D 24
	ip->ip_p = so->so_proto->pr_protocol;
E 24
I 24
	ip->ip_p = rp->rcb_proto.sp_protocol;
E 24
	ip->ip_len = sizeof(struct ip) + len;
D 10
	ip->ip_dst =
		((struct sockaddr_in *)&rp->rcb_addr)->sin_addr;
	ip->ip_src =
		((struct sockaddr_in *)&so->so_addr)->sin_addr;
E 10
I 10
D 12
	ip->ip_dst = ((struct sockaddr_in *)&rp->rcb_faddr)->sin_addr;
	/* local address may not be specified -- XXX */
	ifp = if_ifonnetof(ip->ip_dst.s_net);
	if (ifp == 0) {
		error = ENETUNREACH;
		goto bad;
	}
	if (rp->rcb_flags & RAW_LADDR)
		src = (struct sockaddr_in *)&rp->rcb_laddr;
	else {
		if (ifp->if_addr.sa_family != AF_INET) {
E 12
I 12
	if (rp->rcb_flags & RAW_LADDR) {
		sin = (struct sockaddr_in *)&rp->rcb_laddr;
		if (sin->sin_family != AF_INET) {
E 12
			error = EAFNOSUPPORT;
			goto bad;
		}
D 12
		src = (struct sockaddr_in *)&ifp->if_addr;
	}
	ip->ip_src = src->sin_addr;
E 12
I 12
		ip->ip_src.s_addr = sin->sin_addr.s_addr;
	} else
		ip->ip_src.s_addr = 0;
	ip->ip_dst = ((struct sockaddr_in *)&rp->rcb_faddr)->sin_addr;
E 12
E 10
	ip->ip_ttl = MAXTTL;
D 3
printf("ip=<p=%d,len=%d,dst=%x,src=%x>\n",ip->ip_p,ip->ip_len,ip->ip_dst,ip->ip_src);
E 3
D 7
	return (ip_output(m, 0));
E 7
I 7
D 8
	return (ip_output(m, (struct mbuf *)0));
E 8
I 8
D 9
	return (ip_output(m, (struct mbuf *)0, 1));
E 8
E 7
E 2
}

D 2
/*ARGSUSED*/
E 2
I 2
/*
 * Intercept control operations related to
 * handling of IP options.  Otherwise,
 * just pass things on to the raw_usrreq
 * routine for setup and tear down of
 * raw control block data structures.
 */
E 2
rip_usrreq(so, req, m, addr)
	struct socket *so;
	int req;
	struct mbuf *m;
	caddr_t addr;
{
I 2
	register struct rawcb *rp = sotorawcb(so);
E 2

COUNT(RAW_USRREQ);
I 2
	if (rp == 0 && req != PRU_ATTACH)
		return (EINVAL);
E 2

D 2
}

rip_slowtimo()
{

COUNT(RIP_SLOWTIMO);

E 2
I 2
	switch (req) {
	
I 4
	/*
	 * SHOULD HAVE CONTROL TO SET PROTOCOL NUMBER (e.g. GGP)
	 */
E 4
	case PRU_CONTROL:
		return (EOPNOTSUPP);
	}
	return (raw_usrreq(so, req, m, addr));
E 9
I 9
D 12
	return (ip_output(m, (struct mbuf *)0, 0, 1));
E 12
I 12
D 18
	return (ip_output(m, (struct mbuf *)0, &routetoif, 1));
E 18
I 18
D 19
	return (ip_output(m, (struct mbuf *)0, (struct route *)0, 
E 19
I 19
D 26
	return (ip_output(m, (struct mbuf *)0, &rp->rcb_route, 
E 19
	   IP_ROUTETOIF|IP_ALLOWBROADCAST));
E 26
I 26
	return (ip_output(m, rp->rcb_options, &rp->rcb_route, 
E 32
I 32
D 41
	return (ip_output(m,
D 37
	   (rp->rinp_flags & RINPF_HDRINCL)? (struct mbuf *)0: rp->rinp_options,
	    &rp->rinp_route, 
E 32
	   (so->so_options & SO_DONTROUTE) | IP_ALLOWBROADCAST));
E 37
I 37
	   (inp->inp_flags & INP_HDRINCL)? (struct mbuf *)0: inp->inp_options,
	    &inp->inp_route, 
D 39
	   (so->so_options & SO_DONTROUTE) | IP_ALLOWBROADCAST
#ifdef MULTICAST
	   , inp->inp_moptions
#endif
	   ));
E 39
I 39
	   (so->so_options & SO_DONTROUTE) | IP_ALLOWBROADCAST,
	   inp->inp_moptions));
E 41
I 41
	return (ip_output(m, opts, &inp->inp_route, flags, inp->inp_moptions));
E 41
E 39
E 37
E 26
E 18
E 12
I 10
D 32
bad:
	m_freem(m);
I 26
	return (error);
E 32
}

/*
 * Raw IP socket option processing.
 */
I 43
int
E 43
rip_ctloutput(op, so, level, optname, m)
	int op;
	struct socket *so;
	int level, optname;
	struct mbuf **m;
{
D 37
	int error = 0;
D 32
	register struct rawcb *rp = sotorawcb(so);
E 32
I 32
	register struct raw_inpcb *rp = sotorawinpcb(so);
E 37
I 37
	register struct inpcb *inp = sotoinpcb(so);
	register int error;
E 37
E 32

D 46
	if (level != IPPROTO_IP)
E 46
I 46
	if (level != IPPROTO_IP) {
D 49
		if (m != 0 && *m != 0)
			(void)m_free(*m);
E 49
I 49
		if (op == PRCO_SETOPT && *m)
			(void) m_free(*m);
E 49
E 46
D 37
		error = EINVAL;
	else switch (op) {
E 37
I 37
		return (EINVAL);
I 46
	}
E 46
E 37

D 37
	case PRCO_SETOPT:
		switch (optname) {
E 37
I 37
	switch (optname) {
E 37
I 32

E 32
D 37
		case IP_OPTIONS:
D 32
			return (ip_pcbopts(&rp->rcb_options, *m));
E 32
I 32
			return (ip_pcbopts(&rp->rinp_options, *m));
E 32

I 32
		case IP_HDRINCL:
			if (m == 0 || *m == 0 || (*m)->m_len < sizeof (int)) {
				error = EINVAL;
				break;
E 37
I 37
	case IP_HDRINCL:
D 49
		if (op == PRCO_SETOPT || op == PRCO_GETOPT) {
			if (m == 0 || *m == 0 || (*m)->m_len < sizeof (int))
				return (EINVAL);
			if (op == PRCO_SETOPT) {
				if (*mtod(*m, int *))
					inp->inp_flags |= INP_HDRINCL;
				else
					inp->inp_flags &= ~INP_HDRINCL;
E 49
I 49
		error = 0;
		if (op == PRCO_SETOPT) {
			if (*m == 0 || (*m)->m_len < sizeof (int))
				error = EINVAL;
			else if (*mtod(*m, int *))
				inp->inp_flags |= INP_HDRINCL;
			else
				inp->inp_flags &= ~INP_HDRINCL;
			if (*m)
E 49
				(void)m_free(*m);
D 49
			} else {
				(*m)->m_len = sizeof (int);
				*mtod(*m, int *) = inp->inp_flags & INP_HDRINCL;
E 37
			}
D 37
			if (*mtod(*m, int *))
				rp->rinp_flags |= RINPF_HDRINCL;
			else
				rp->rinp_flags &= ~RINPF_HDRINCL;
			break;

E 32
		default:
			error = EINVAL;
			break;
E 37
I 37
			return (0);
E 49
I 49
		} else {
			*m = m_get(M_WAIT, MT_SOOPTS);
			(*m)->m_len = sizeof (int);
			*mtod(*m, int *) = inp->inp_flags & INP_HDRINCL;
E 49
E 37
		}
D 49
		break;
E 49
I 49
		return (error);
E 49

D 37
	case PRCO_GETOPT:
I 32
		*m = m_get(M_WAIT, MT_SOOPTS);
E 32
		switch (optname) {
I 32

E 32
		case IP_OPTIONS:
D 32
			*m = m_get(M_WAIT, MT_SOOPTS);
			if (rp->rcb_options) {
				(*m)->m_off = rp->rcb_options->m_off;
				(*m)->m_len = rp->rcb_options->m_len;
				bcopy(mtod(rp->rcb_options, caddr_t),
E 32
I 32
			if (rp->rinp_options) {
				(*m)->m_len = rp->rinp_options->m_len;
				bcopy(mtod(rp->rinp_options, caddr_t),
E 32
D 27
				    mtod(*m, caddr_t), (*m)->m_len);
E 27
I 27
				    mtod(*m, caddr_t), (unsigned)(*m)->m_len);
E 27
			} else
				(*m)->m_len = 0;
			break;
I 32

		case IP_HDRINCL:
			(*m)->m_len = sizeof (int);
			*mtod(*m, int *) = rp->rinp_flags & RINPF_HDRINCL;
			break;

E 32
		default:
E 37
I 37
	case DVMRP_INIT:
	case DVMRP_DONE:
	case DVMRP_ADD_VIF:
	case DVMRP_DEL_VIF:
	case DVMRP_ADD_LGRP:
	case DVMRP_DEL_LGRP:
	case DVMRP_ADD_MRT:
	case DVMRP_DEL_MRT:
#ifdef MROUTING
		if (op == PRCO_SETOPT) {
			error = ip_mrouter_cmd(optname, so, *m);
			if (*m)
				(void)m_free(*m);
		} else
E 37
			error = EINVAL;
I 32
D 37
			m_freem(*m);
			*m = 0;
E 32
			break;
		}
		break;
E 37
I 37
		return (error);
#else
		if (op == PRCO_SETOPT && *m)
			(void)m_free(*m);
		return (EOPNOTSUPP);
#endif
I 49

	default:
		if (optname >= DVMRP_INIT) {
I 50
#ifdef MROUTING
E 50
			if (op == PRCO_SETOPT) {
				error = ip_mrouter_cmd(optname, so, *m);
				if (*m)
					(void)m_free(*m);
			} else
				error = EINVAL;
			return (error);
I 50
#else
			if (op == PRCO_SETOPT && *m)
				(void)m_free(*m);
			return (EOPNOTSUPP);
#endif
E 50
		}

E 49
E 37
	}
D 29
	if (op == PRCO_SETOPT)
E 29
I 29
D 37
	if (op == PRCO_SETOPT && *m)
E 29
D 27
		m_free(*m);
E 27
I 27
		(void)m_free(*m);
I 32
	return (error);
E 37
I 37
	return (ip_ctloutput(op, so, level, optname, m));
E 37
}

I 37
u_long	rip_sendspace = RIPSNDQ;
u_long	rip_recvspace = RIPRCVQ;

E 37
/*ARGSUSED*/
I 43
int
E 43
D 37
rip_usrreq(so, req, m, nam, rights, control)
E 37
I 37
rip_usrreq(so, req, m, nam, control)
E 37
	register struct socket *so;
	int req;
D 37
	struct mbuf *m, *nam, *rights, *control;
E 37
I 37
	struct mbuf *m, *nam, *control;
E 37
{
	register int error = 0;
D 37
	register struct raw_inpcb *rp = sotorawinpcb(so);
E 37
I 37
	register struct inpcb *inp = sotoinpcb(so);
D 39
#if defined(MULTICAST) && defined(MROUTING)
E 39
I 39
#ifdef MROUTING
E 39
	extern struct socket *ip_mrouter;
#endif
E 37
D 43

E 43
	switch (req) {

	case PRU_ATTACH:
D 37
		if (rp)
E 37
I 37
		if (inp)
E 37
			panic("rip_attach");
D 37
		MALLOC(rp, struct raw_inpcb *, sizeof *rp, M_PCB, M_WAITOK);
		if (rp == 0)
			return (ENOBUFS);
		bzero((caddr_t)rp, sizeof *rp);
		so->so_pcb = (caddr_t)rp;
E 37
I 37
		if ((so->so_state & SS_PRIV) == 0) {
			error = EACCES;
			break;
		}
		if ((error = soreserve(so, rip_sendspace, rip_recvspace)) ||
		    (error = in_pcballoc(so, &rawinpcb)))
			break;
		inp = (struct inpcb *)so->so_pcb;
		inp->inp_ip.ip_p = (int)nam;
E 37
		break;

I 37
	case PRU_DISCONNECT:
		if ((so->so_state & SS_ISCONNECTED) == 0) {
			error = ENOTCONN;
			break;
		}
		/* FALLTHROUGH */
	case PRU_ABORT:
		soisdisconnected(so);
		/* FALLTHROUGH */
E 37
	case PRU_DETACH:
D 37
		if (rp == 0)
E 37
I 37
		if (inp == 0)
E 37
			panic("rip_detach");
D 37
		if (rp->rinp_options)
			m_freem(rp->rinp_options);
		if (rp->rinp_route.ro_rt)
			RTFREE(rp->rinp_route.ro_rt);
		if (rp->rinp_rcb.rcb_laddr)
			rp->rinp_rcb.rcb_laddr = 0;
E 37
I 37
D 39
#if defined(MULTICAST) && defined(MROUTING)
E 39
I 39
#ifdef MROUTING
E 39
		if (so == ip_mrouter)
			ip_mrouter_done();
#endif
		in_pcbdetach(inp);
E 37
		break;

	case PRU_BIND:
	    {
		struct sockaddr_in *addr = mtod(nam, struct sockaddr_in *);

D 37
		if (nam->m_len != sizeof(*addr))
			return (EINVAL);
E 37
I 37
		if (nam->m_len != sizeof(*addr)) {
			error = EINVAL;
			break;
		}
E 37
		if ((ifnet == 0) ||
		    ((addr->sin_family != AF_INET) &&
		     (addr->sin_family != AF_IMPLINK)) ||
		    (addr->sin_addr.s_addr &&
D 37
		     ifa_ifwithaddr((struct sockaddr *)addr) == 0))
			return (EADDRNOTAVAIL);
		rp->rinp_rcb.rcb_laddr = (struct sockaddr *)&rp->rinp_laddr;
		rp->rinp_laddr = *addr;
		return (0);
E 37
I 37
		     ifa_ifwithaddr((struct sockaddr *)addr) == 0)) {
			error = EADDRNOTAVAIL;
			break;
		}
		inp->inp_laddr = addr->sin_addr;
		break;
E 37
	    }
	case PRU_CONNECT:
	    {
		struct sockaddr_in *addr = mtod(nam, struct sockaddr_in *);

D 37
		if (nam->m_len != sizeof(*addr))
			return (EINVAL);
		if (ifnet == 0)
			return (EADDRNOTAVAIL);
E 37
I 37
		if (nam->m_len != sizeof(*addr)) {
			error = EINVAL;
			break;
		}
		if (ifnet == 0) {
			error = EADDRNOTAVAIL;
			break;
		}
E 37
		if ((addr->sin_family != AF_INET) &&
D 37
		     (addr->sin_family != AF_IMPLINK))
			return (EAFNOSUPPORT);
		rp->rinp_rcb.rcb_faddr = (struct sockaddr *)&rp->rinp_faddr;
D 35
		rp->rinp_laddr = *addr;
E 35
I 35
		rp->rinp_faddr = *addr;
E 37
I 37
		     (addr->sin_family != AF_IMPLINK)) {
			error = EAFNOSUPPORT;
			break;
		}
		inp->inp_faddr = addr->sin_addr;
E 37
E 35
		soisconnected(so);
D 37
		return (0);
E 37
I 37
		break;
E 37
	    }
D 37
	}
	error =  raw_usrreq(so, req, m, nam, rights, control);
E 37

D 37
	if (error && (req == PRU_ATTACH) && so->so_pcb)
		free(so->so_pcb, M_PCB);
E 37
I 37
	case PRU_CONNECT2:
		error = EOPNOTSUPP;
		break;

	/*
	 * Mark the connection as being incapable of further input.
	 */
	case PRU_SHUTDOWN:
		socantsendmore(so);
		break;

	/*
	 * Ship a packet out.  The appropriate raw output
	 * routine handles any massaging necessary.
	 */
	case PRU_SEND:
	    {
		register u_long dst;

		if (so->so_state & SS_ISCONNECTED) {
			if (nam) {
				error = EISCONN;
				break;
			}
			dst = inp->inp_faddr.s_addr;
		} else {
			if (nam == NULL) {
				error = ENOTCONN;
				break;
			}
			dst = mtod(nam, struct sockaddr_in *)->sin_addr.s_addr;
		}
		error = rip_output(m, so, dst);
		m = NULL;
		break;
	    }

	case PRU_SENSE:
		/*
		 * stat: don't bother with a blocksize.
		 */
		return (0);

	/*
	 * Not supported.
	 */
	case PRU_RCVOOB:
	case PRU_RCVD:
	case PRU_LISTEN:
	case PRU_ACCEPT:
	case PRU_SENDOOB:
		error = EOPNOTSUPP;
		break;

	case PRU_SOCKADDR:
		in_setsockaddr(inp, nam);
		break;

	case PRU_PEERADDR:
		in_setpeeraddr(inp, nam);
		break;

	default:
		panic("rip_usrreq");
	}
	if (m != NULL)
		m_freem(m);
E 37
E 32
E 27
E 26
	return (error);
E 10
E 9
E 2
}
E 1
