h06525
s 00002/00002/00773
d D 8.1 93/06/10 22:53:15 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00774
d D 7.21 93/06/05 15:57:01 sklower 21 20
c various lintish things come to light by protoypes.
e
s 00005/00003/00770
d D 7.20 93/02/12 14:59:24 sklower 20 19
c need to free RR packets (plug mbuf leak reported by MITRE)
e
s 00003/00003/00770
d D 7.19 92/12/08 17:46:51 sklower 19 18
c changes from dkhusema
e
s 00026/00026/00747
d D 7.18 92/12/08 13:36:42 bostic 18 17
c new conventions for kernel header includes (by sklower);
c version of oct 11, 1992
e
s 00019/00015/00754
d D 7.17 92/12/08 13:34:02 sklower 17 16
c routing tables set up after proto inits called now, need lazy evaluation.
e
s 00001/00002/00768
d D 7.16 92/07/09 00:12:40 sklower 16 15
c changes to add routing tables via the domain switch
e
s 00001/00002/00769
d D 7.15 91/07/30 17:41:51 sklower 15 14
c change required by using routing vector instead of linked list
e
s 00001/00001/00770
d D 7.14 91/06/26 15:41:59 sklower 14 13
c use pk_disconnect to cease listening instead of pk_close
e
s 00022/00000/00749
d D 7.13 91/06/06 19:39:35 sklower 13 12
c this version now supports IP over X.25; changes include setting 
c the X25_MBS_HOLD  flag and preserving flags through incoming call cloning and aassociation
e
s 00156/00037/00593
d D 7.12 91/05/29 19:22:14 sklower 12 11
c many fixes & changes -- add routine to glue or spit vc to route;
c and routine to turn on, off dg listening in kernel;\ 
e
s 00021/00009/00609
d D 7.11 91/05/16 14:06:30 sklower 11 10
c mark state before allowing dynamic pkcb's
e
s 00304/00206/00314
d D 7.10 91/05/15 00:07:58 sklower 10 9
c note current state -- compiles, includes frob to glue socket to route.
e
s 00041/00027/00479
d D 7.9 91/05/03 18:42:56 sklower 9 8
c this still isn't expect to work.
e
s 00103/00135/00403
d D 7.8 91/01/09 15:40:27 sklower 8 7
c checkpoint -- this version compiles and represents most of 
c the changes to have ISO CONS be a kernel client of X.25; not tested!!!!
e
s 00035/00007/00503
d D 7.7 90/10/04 19:50:17 sklower 7 6
c capture current work; fix minor bugs concerning packet lengths &
c conventions; add routine to fragment datagrams into complete sequences.
e
s 00086/00077/00424
d D 7.6 90/08/30 18:48:45 sklower 6 5
c this version compiles; completely untested
e
s 00033/00036/00468
d D 7.5 90/06/21 12:29:24 sklower 5 4
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00008/00007/00496
d D 7.4 90/05/22 15:46:27 sklower 4 3
c checkpoint before changing pq structure to be a sockbuf for downq 
c and only retaining up method
e
s 00128/00094/00375
d D 7.3 90/05/16 15:46:10 sklower 3 2
c periodic checkpoint against catastrophic loss
e
s 00003/00013/00466
d D 7.2 90/05/11 15:22:03 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00479/00000/00000
d D 7.1 90/05/11 11:21:30 sklower 1 0
c date and time created 90/05/11 11:21:30 by sklower
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1989 Regents of the University of California.
E 2
I 2
D 22
 * Copyright (c) 1990 The Regents of the University of California.
E 2
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
D 2
 *	@(#)if_x25subr.c	0.1 (Berkeley) 9/20/89
E 2
I 2
 *	%W% (Berkeley) %G%
E 2
 */

D 18
#include "param.h"
#include "systm.h"
#include "malloc.h"
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
I 6
#include "socketvar.h"
E 6
#include "ioctl.h"
#include "errno.h"
#include "syslog.h"
E 18
I 18
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/syslog.h>
E 18

I 19
#include <machine/mtpr.h>

E 19
D 3
#include "if.h"
#include "netisr.h"
#include "route.h"
E 3
I 3
D 18
#include "../net/if.h"
I 6
#include "../net/if_types.h"
E 6
#include "../net/netisr.h"
#include "../net/route.h"
E 18
I 18
#include <net/if.h>
#include <net/if_types.h>
#include <net/netisr.h>
#include <net/route.h>
E 18
E 3

D 3
#include "x25_var.h"
#include "x25_pk.h"
E 3
I 3
D 18
#include "x25.h"
D 6
#include "x25error.h"
E 6
I 6
#include "x25err.h"
#include "pk.h"
E 6
#include "pk_var.h"
E 18
I 18
#include <netccitt/x25.h>
#include <netccitt/x25err.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 18

E 3
D 18
#include "machine/mtpr.h"
E 18
I 18
D 19
#include <machine/mtpr.h>
E 18

E 19
#ifdef INET
D 18
#include "../netinet/in.h"
#include "../netinet/in_var.h"
E 18
I 18
#include <netinet/in.h>
#include <netinet/in_var.h>
E 18
#endif

#ifdef NS
D 18
#include "../netns/ns.h"
#include "../netns/ns_if.h"
E 18
I 18
#include <netns/ns.h>
#include <netns/ns_if.h>
E 18
#endif

#ifdef ISO
I 12
int tp_incoming();
E 12
D 18
#include "../netiso/argo_debug.h"
#include "../netiso/iso.h"
#include "../netiso/iso_var.h"
E 18
I 18
#include <netiso/argo_debug.h>
#include <netiso/iso.h>
#include <netiso/iso_var.h>
E 18
#endif

extern	struct ifnet loif;
I 10
struct llinfo_x25 llinfo_x25 = {&llinfo_x25, &llinfo_x25};
I 17
#ifndef _offsetof
#define _offsetof(t, m) ((int)((caddr_t)&((t *)0)->m))
#endif
E 17
I 12
struct sockaddr *x25_dgram_sockmask;
I 17
struct sockaddr_x25 x25_dgmask = {
 _offsetof(struct sockaddr_x25, x25_udata[1]),			/* _len */
 0,								/* _family */
 0,								/* _net */
 { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, /* _addr */
 {0},								/* opts */
 -1,								/* _udlen */
 {-1}								/* _udata */
};
E 17
 
I 13
struct if_x25stats {
	int	ifx_wrongplen;
	int	ifx_nophdr;
} if_x25stats;
E 13
E 12
int x25_autoconnect = 0;
E 10

I 6
D 8
union imp_addr {
	struct in_addr  ip;
	struct imp {
		u_char		s_net;
		u_char		s_host;
		u_char		s_lh;
		u_char		s_impno;
	}		    imp;
};

E 8
E 6
#define senderr(x) {error = x; goto bad;}
/*
I 10
 * Ancillary routines
 */
static struct llinfo_x25 *
x25_lxalloc(rt)
register struct rtentry *rt;
{
	register struct llinfo_x25 *lx;
	register struct sockaddr *dst = rt_key(rt);
	register struct ifaddr *ifa;

	MALLOC(lx, struct llinfo_x25 *, sizeof (*lx), M_PCB, M_NOWAIT);
	if (lx == 0)
		return lx;
	Bzero(lx, sizeof(*lx));
	lx->lx_rt = rt;
	lx->lx_family = dst->sa_family;
	rt->rt_refcnt++;
	if (rt->rt_llinfo)
		insque(lx, (struct llinfo_x25 *)rt->rt_llinfo);
	else {
		rt->rt_llinfo = (caddr_t)lx;
		insque(lx, &llinfo_x25);
	}
	for (ifa = rt->rt_ifp->if_addrlist; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr->sa_family == AF_CCITT)
			lx->lx_ia = (struct x25_ifaddr *)ifa;
	}
	return lx;
}
x25_lxfree(lx)
register struct llinfo_x25 *lx;
{
	register struct rtentry *rt = lx->lx_rt;
	register struct pklcd *lcp = lx->lx_lcd;

	if (lcp) {
		lcp->lcd_upper = 0;
		pk_disconnect(lcp);
	}
	if ((rt->rt_llinfo == (caddr_t)lx) && (lx->lx_next->lx_rt == rt))
		rt->rt_llinfo = (caddr_t)lx->lx_next;
	else
		rt->rt_llinfo = 0;
	RTFREE(rt);
	remque(lx);
	FREE(lx, M_PCB);
}
/*
 * Process a x25 packet as datagram;
 */
x25_ifinput(lcp, m)
struct pklcd *lcp;
register struct mbuf *m;
{
	struct llinfo_x25 *lx = (struct llinfo_x25 *)lcp->lcd_upnext;
	register struct ifnet *ifp;
	struct ifqueue *inq;
	extern struct timeval time;
	int s, len, isr;
 
	if (m == 0 || lcp->lcd_state != DATA_TRANSFER) {
		x25_connect_callback(lcp, 0);
		return;
	}
I 12
	pk_flowcontrol(lcp, 0, 1); /* Generate RR */
E 12
	ifp = m->m_pkthdr.rcvif;
	ifp->if_lastchange = time;
	switch (m->m_type) {
D 20
	case MT_OOBDATA:
E 20
I 20
	default:
E 20
		if (m)
			m_freem(m);
D 20
	default:
E 20
		return;

	case MT_DATA:
		/* FALLTHROUGH */;
	}
	switch (lx->lx_family) {
#ifdef INET
	case AF_INET:
		isr = NETISR_IP;
		inq = &ipintrq;
		break;

#endif
#ifdef NS
	case AF_NS:
		isr = NETISR_NS;
		inq = &nsintrq;
		break;

#endif
#ifdef	ISO
	case AF_ISO:
		isr = NETISR_ISO;
		inq = &clnlintrq;
		break;
#endif
	default:
		m_freem(m);
		ifp->if_noproto++;
		return;
	}
	s = splimp();
	schednetisr(isr);
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
	} else {
		IF_ENQUEUE(inq, m);
		ifp->if_ibytes += m->m_pkthdr.len;
	}
	splx(s);
}
x25_connect_callback(lcp, m)
register struct pklcd *lcp;
register struct mbuf *m;
{
	register struct llinfo_x25 *lx = (struct llinfo_x25 *)lcp->lcd_upnext;
I 20
	int do_clear = 1;
E 20
	if (m == 0)
		goto refused;
	if (m->m_type != MT_CONTROL) {
		printf("x25_connect_callback: should panic\n");
		goto refused;
	}
	switch (pk_decode(mtod(m, struct x25_packet *))) {
	case CALL_ACCEPTED:
		lcp->lcd_upper = x25_ifinput;
		if (lcp->lcd_sb.sb_mb)
			lcp->lcd_send(lcp); /* XXX start queued packets */
		return;
	default:
I 20
		do_clear = 0;
E 20
	refused:
		lcp->lcd_upper = 0;
		lx->lx_lcd = 0;
D 20
		pk_disconnect(lcp);
E 20
I 20
		if (do_clear)
			pk_disconnect(lcp);
E 20
		return;
	}
}
I 12
#define SA(p) ((struct sockaddr *)(p))
#define RT(p) ((struct rtentry *)(p))

x25_dgram_incoming(lcp, m0)
register struct pklcd *lcp;
struct mbuf *m0;
{
	register struct rtentry *rt, *nrt;
	register struct mbuf *m = m0->m_next; /* m0 has calling sockaddr_x25 */
D 16
	int x25_rtrequest();
E 16
I 16
	void x25_rtrequest();
E 16

	rt = rtalloc1(SA(&lcp->lcd_faddr), 0);
	if (rt == 0) {
refuse: 	lcp->lcd_upper = 0;
		pk_close(lcp);
		return;
	}
	rt->rt_refcnt--;
	if ((nrt = RT(rt->rt_llinfo)) == 0 || rt_mask(rt) != x25_dgram_sockmask)
		goto refuse;
	if ((nrt->rt_flags & RTF_UP) == 0) {
		rt->rt_llinfo = (caddr_t)rtalloc1(rt->rt_gateway, 0);
		rtfree(nrt);
		if ((nrt = RT(rt->rt_llinfo)) == 0)
			goto refuse;
		nrt->rt_refcnt--;
	}
	if (nrt->rt_ifa == 0 || nrt->rt_ifa->ifa_rtrequest != x25_rtrequest)
		goto refuse;
	lcp->lcd_send(lcp); /* confirm call */
	x25_rtattach(lcp, nrt);
	m_freem(m);
}

E 12
/*
E 10
 * X.25 output routine.
 */
D 3
x25_ifoutput(xc, m0, dst, rt)
struct	x25com *xc;
E 3
I 3
x25_ifoutput(ifp, m0, dst, rt)
struct	ifnet *ifp;
E 3
struct	mbuf *m0;
struct	sockaddr *dst;
register struct	rtentry *rt;
{
D 3
	register struct mbuf *m = m0;
	register struct x25lcb *xl;
	register struct xq *oq;
	register struct x25lcb **xlp;
E 3
I 3
D 10
	register struct mbuf *m;
D 4
	struct rtextension_x25 *rtx;
	struct pq *pq;
E 4
I 4
D 6
	register struct rtextension_x25 *rtx;
E 6
I 6
	register struct llinfo_x25 *lx;
E 6
	register struct pq *pq;
E 10
I 10
D 12
	register struct	mbuf *m;
E 12
I 12
	register struct	mbuf *m = m0;
E 12
	register struct	llinfo_x25 *lx;
E 10
E 4
	struct pklcd *lcp;
D 10
	struct x25_ifaddr *ia;
E 3
	struct mbuf    *prev;
D 7
	int             s, error = 0, flags = 0;
E 7
I 7
	int             s, error = 0, flags = 0, af;
E 10
I 10
	int             s, error = 0;
E 10
E 7
D 8
	union imp_addr  imp_addr;
E 8
D 6
	int flags = 0;
E 6

I 13
int plen;
for (plen = 0; m; m = m->m_next)
	plen += m->m_len;
m = m0;

E 13
D 3
	if ((xc->xc_if.if_flags & IFF_UP) == 0)
E 3
I 3
	if ((ifp->if_flags & IFF_UP) == 0)
E 3
D 10
		return (ENETDOWN);
E 10
I 10
		senderr(ENETDOWN);
E 10
D 11
	if (rt == 0 ||
	    ((rt->rt_flags & RTF_GATEWAY) && (dst = rt->rt_gateway))) {
E 11
I 11
	while (rt == 0 || (rt->rt_flags & RTF_GATEWAY)) {
		if (rt) {
			if (rt->rt_llinfo) {
				rt = (struct rtentry *)rt->rt_llinfo;
				continue;
			}
			dst = rt->rt_gateway;
		}
E 11
		if ((rt = rtalloc1(dst, 1)) == 0)
D 10
			return (EHOSTUNREACH);
		rt->rt_refcnt++;
D 3
		flags = XL_RTHELD;
E 3
I 3
D 6
		flags = XRF_RTHELD;
E 6
I 6
		flags = LXF_RTHELD;
E 10
I 10
			senderr(EHOSTUNREACH);
		rt->rt_refcnt--;
E 10
E 6
E 3
	}
	/*
	 * Sanity checks.
	 */
D 3
	if ((rt->rt_ifp != (struct ifnet *)xc) ||
E 3
I 3
	if ((rt->rt_ifp != ifp) ||
E 3
	    (rt->rt_flags & (RTF_CLONING | RTF_GATEWAY)) ||
D 3
	    ((xl = (struct x25lcb *)rt->rt_llinfo) == 0)) {
E 3
I 3
D 6
	    ((rtx = (struct rtextension_x25 *)rt->rt_llinfo) == 0)) {
E 6
I 6
	    ((lx = (struct llinfo_x25 *)rt->rt_llinfo) == 0)) {
E 6
E 3
D 10
		printf("Inconsistent call to x25_output, should panic\n");
E 10
		senderr(ENETUNREACH);
	}
I 13
if ((m->m_flags & M_PKTHDR) == 0) {
	if_x25stats.ifx_nophdr++;
	m = m_gethdr(M_NOWAIT, MT_HEADER);
	if (m == 0)
		senderr(ENOBUFS);
	m->m_pkthdr.len = plen;
	m->m_next = m0;
}
if (plen != m->m_pkthdr.len) {
	if_x25stats.ifx_wrongplen++;
	m->m_pkthdr.len = plen;
}
E 13
D 3
	xq = &xl->xl_downq;
	switch (xl->xl_state) {
E 3
I 3
D 10
    {
	register struct ifaddr *ifa;
	for (ifa = ifp->if_addrlist; ; ifa = ifa->ifa_next) {
		if (ifa == 0)
			senderr(ENETDOWN);
		if (ifa->ifa_addr->sa_family == AF_CCITT)
			break;
E 10
I 10
D 11
	if (dst->sa_family == AF_INET &&
	    ifp->if_type == IFT_X25DDN &&
	    rt->rt_gateway->sa_family != AF_CCITT)
		x25_ddnip_to_ccitt(dst, rt);
E 11
next_circuit:
	lcp = lx->lx_lcd;
	if (lcp == 0) {
		lx->lx_lcd = lcp = pk_attach((struct socket *)0);
		if (lcp == 0)
			senderr(ENOBUFS);
		lcp->lcd_upper = x25_connect_callback;
		lcp->lcd_upnext = (caddr_t)lx;
		lcp->lcd_packetsize = lx->lx_ia->ia_xc.xc_psize;
I 13
		lcp->lcd_flags = X25_MBS_HOLD;
E 13
E 10
	}
D 10
	ia = (struct x25_ifaddr *)ifa;
    }
D 6
	if (rtx->rtx_lcd == 0) {
E 6
I 6
D 8
	if (lx->lx_lcd == 0) {
E 6
		int x25_ifinput();
E 3

D 3
	case XLS_CONNECTED:
		xl->xl_timer = xc->xc_dg_idletimo;
E 3
I 3
D 4
		m = m_getclr(M_DONTWAIT, MT_PCB);
		if (m == 0)
E 4
I 4
		lcp = pk_attach((struct socket *)0);
		if (lcp == 0)
E 4
			senderr(ENOBUFS);
D 4
		rtx->rtx_lcd = lcp = mtod(m, struct pklcd *);
E 4
I 4
D 6
		rtx->rtx_lcd = lcp;
E 4
		rtx->rtx_rt = rt;
		rtx->rtx_ia = ia;
D 5
		lcp->lcd_upq.pq_next = (caddr_t)rtx;
		lcp->lcd_upq.pq_put = x25_ifinput;
E 5
I 5
		lcp->lcd_upnext = (caddr_t)rtx;
E 6
I 6
		lx->lx_lcd = lcp;
		lx->lx_rt = rt;
		lx->lx_ia = ia;
I 7
		lx->lx_family = dst->sa_family;
E 7
		lcp->lcd_upnext = (caddr_t)lx;
E 6
		lcp->lcd_upper = x25_ifinput;
I 7
		lcp->lcd_packetsize = ia->ia_xc.xc_psize; /* XXX pk_fragment */
E 7
E 5
	}
E 8
D 5
	pq = &lcp->lcd_downq;
E 5
D 6
	switch (rtx->rtx_state) {
E 6
I 6
	switch (lx->lx_state) {
E 6

D 6
	case XRS_CONNECTED:
		lcd->lcd_dg_timer = ia->ia_xc.xc_dg_idletimo;
E 6
I 6
D 9
	case LXS_CONNECTED:
		lcp->lcd_dg_timer = ia->ia_xc.xc_dg_idletimo;
E 6
E 3
		/* FALLTHROUGH */
D 3
	case XLS_CONNECTING:
		if (xq->xq_space < 0)
E 3
I 3
D 6
	case XRS_CONNECTING:
E 6
I 6
	case LXS_CONNECTING:
E 6
D 5
		if (pq->pq_space < 0)
E 5
I 5
		if (sbspace(&lcp->lcd_sb) < 0)
E 5
E 3
			senderr(ENOBUFS);
D 3
		xq->xq_put(xq, m);
E 3
I 3
D 5
		pq->pq_put(pq, m);
E 5
I 5
		lcp->lcd_send(lcp, m);
E 5
E 3
		break;

E 9
D 3
	case XLS_NEWBORN:
		xq = &xl->xl_upq;
		xq->xq_next = (caddr_t)rt;
		xq->xq_put = x25_ifinput;
E 3
I 3
D 6
	case XRS_NEWBORN:
E 6
I 6
	case LXS_NEWBORN:
E 6
E 3
		if (dst->sa_family == AF_INET &&
D 3
		    xc->xc_if.if_type == IFT_DDN &&
E 3
I 3
D 6
		    ia->xc_if.if_type == IFT_DDN &&
E 6
I 6
		    ia->ia_ifp->if_type == IFT_X25DDN &&
E 6
E 3
		    rt->rt_gateway->sa_family != AF_CCITT)
			x25_ddnip_to_ccitt(dst, rt->rt_gateway);
D 3
		xl->xl_xc = xc;
		xq = &xl->xl_downq;
		xq->xq_space = 2048;  /* XXX: bogus xq before if_start called */
		xl->xl_flags |= XL_DGRAM;
		xl->xl_state = XLS_FREE;
E 3
I 3
D 5
		pq->pq_space = 2048;  /* XXX: bogus pq before if_start called */
E 5
		lcp->lcd_flags |= X25_DG_CIRCUIT;
D 6
		rtx->rtx_state = XRS_FREE;
E 6
I 6
		lx->lx_state = LXS_FREE;
E 10
I 10
	switch (lcp->lcd_state) {
	case READY:
I 11
		if (dst->sa_family == AF_INET &&
		    ifp->if_type == IFT_X25DDN &&
		    rt->rt_gateway->sa_family != AF_CCITT)
			x25_ddnip_to_ccitt(dst, rt);
E 11
E 10
E 6
E 3
		if (rt->rt_gateway->sa_family != AF_CCITT) {
D 10
			/*
			 * Need external resolution of dst
			 */
E 10
			if ((rt->rt_flags & RTF_XRESOLVE) == 0)
D 10
				senderr(ENETUNREACH);
D 3
			xl->xl_flags |= flags;
			xl->xl_timer = xc->xc_rslvtimo;
E 3
I 3
D 6
			rtx->rtx_flags |= flags;
E 6
I 6
			lx->lx_flags |= flags;
E 6
E 3
			flags = 0;
D 9
			rt_missmsg(RTM_RESOLVE, dst,
			    (struct sockaddr *)0, (struct sockaddr *)0,
			    (struct sockaddr *)0, 0, 0);
E 9
D 3
			xl->xl_state = XLS_RESOLVING;
E 3
I 3
D 6
			rtx->rtx_state = XRS_RESOLVING;
E 6
I 6
			lx->lx_state = LXS_RESOLVING;
E 6
E 3
			/* FALLTHROUGH */
I 9
	case LXS_CONNECTED:
			lcp->lcd_dg_timer = ia->ia_xc.xc_dg_idletimo;
			/* FALLTHROUGH */
	case LXS_CONNECTING:
E 9
D 3
	case XLS_RESOLVING:
			if (xq->xq_space < 0)
E 3
I 3
D 6
	case XRS_RESOLVING:
E 6
I 6
	case LXS_RESOLVING:
E 6
D 5
			if (pq->pq_space < 0)
E 5
I 5
			if (sbspace(&lcp->lcd_sb) < 0)
E 5
E 3
				senderr(ENOBUFS);
D 3
			xq->xq_space -= m->m_pkthdr.len;
			if (xq->xq_data == 0)
				xq->xq_data = m;
E 3
I 3
D 5
			pq->pq_space -= m->m_pkthdr.len;
			if (pq->pq_data == 0)
				pq->pq_data = m;
E 3
			else {
D 3
				for (m = xq->xq_data; m->m_nextpkt; )
E 3
I 3
				for (m = pq->pq_data; m->m_nextpkt; )
E 3
					m = m->m_nextpkt;
				m->m_nextpkt = m0;
			}
E 5
I 5
D 7
			sbappendrecord(&lcp->lcd_sb, m);
E 7
I 7
D 9
			pk_fragment(lcp, m, 0, 0, 0);
E 9
I 9
			pk_send(lcp, m);
E 9
E 7
E 5
			break;
		}
E 10
I 10
				senderr(EHOSTUNREACH);
		} else if (x25_autoconnect)
			error = pk_connect(lcp,
					(struct sockaddr_x25 *)rt->rt_gateway);
		if (error)
			senderr(error);
E 10
		/* FALLTHROUGH */
D 3
	case XLS_FREE:
		xlp = xc->xc_lcbvec + xc->xc_nchan;
		s = splimp(); /* need to block out incoming requests */
		if (xc->xc_nactive < xc->xc_nchan) {
			while (--xlp > xc->xc_lcbvec && *xlp)
				;
			if (xlp > xc->xc_lcbvec) {
				xc->xc_nactive++;
				*xlp = xl;
				xl->xl_index = xlp - xc->xc_lcbvec;
				x25_ifstart(xl, m, rt->rt_gateway, dst);
				splx(s);
				break;
			}
		}
		splx(s);
E 3
I 3
D 6
	case XRS_FREE:
E 6
I 6
D 10
	case LXS_FREE:
E 6
D 5
		lcp->lcd_downq.pq_data = m;
E 5
I 5
D 7
		sbappendrecord(&lcp->lcd_sb, m);
E 7
E 5
D 6
		lcp->lcd_pkcb = &(rtx->rtx_ia->ia_pkcb);
E 6
I 6
		lcp->lcd_pkp = &(lx->lx_ia->ia_pkcb);
I 7
D 9
		pk_fragment(lcp, m, 0, 0, 0);
E 9
E 7
E 6
D 4
		pk_connect(lcp, rt->rt_gateway);
E 4
I 4
D 8
		pk_connect(lcp, (struct mbuf *)0,
				(struct sockaddr_x25 *)rt->rt_gateway);
E 8
I 8
		pk_connect(lcp, (struct sockaddr_x25 *)rt->rt_gateway);
E 10
I 10
	case SENT_CALL:
	case DATA_TRANSFER:
		if (sbspace(&lcp->lcd_sb) < 0) {
			lx = lx->lx_next;
			if (lx->lx_rt != rt)
				senderr(ENOSPC);
			goto next_circuit;
		}
		if (lx->lx_ia)
			lcp->lcd_dg_timer =
				       lx->lx_ia->ia_xc.xc_dg_idletimo;
E 10
I 9
		pk_send(lcp, m);
E 9
E 8
E 4
		break;
E 3
D 9
		/* FALLTHROUGH */
E 9
I 9
D 10

E 10
E 9
	default:
		/*
		 * We count on the timer routine to close idle
		 * connections, if there are not enough circuits to go
		 * around.
		 *
		 * So throw away data for now.
		 * After we get it all working, we'll rewrite to handle
		 * actively closing connections (other than by timers),
		 * when circuits get tight.
		 *
		 * In the DDN case, the imp itself closes connections
		 * under heavy load.
		 */
		error = ENOBUFS;
	bad:
		if (m)
			m_freem(m);
	}
D 10
out:
D 3
	if (flags & XL_RTHELD)
E 3
I 3
D 6
	if (flags & XRF_RTHELD)
E 6
I 6
	if (flags & LXF_RTHELD)
E 6
E 3
		RTFREE(rt);
E 10
	return (error);
}

/*
D 3
 * Simpleminded timer for very smart devices.
E 3
I 3
 * Simpleminded timer routine.
E 3
 */
D 3
x25_iftimeout(xc)
register struct x25com *xc;
E 3
I 3
x25_iftimeout(ifp)
struct ifnet *ifp;
E 3
{
D 3
	register struct x25lcb **xlp = xc->xc_lcbvec + xc->xc_nchan;
	register struct x25lcb *xl;
E 3
I 3
	register struct pkcb *pkcb = 0;
D 12
	register struct ifaddr *ifa;
E 12
	register struct pklcd **lcpp, *lcp;
E 3
	int s = splimp();

D 3
	if (xc->xc_disconnect)
	    while (--xlp > xc->xc_lcbvec)
		if ((xl = *xlp) && xl->xl_state == XLS_CONECTED &&
		    (xl->xl_flags & XL_DGRAM) && --(xl->xl_timer) <= 0)
			xc->xc_disconnect(xl);
E 3
I 3
D 10
	for (ifa = ifp->if_addrlist; ; ifa = ifa->ifa_next) {
E 10
I 10
D 12
	for (ifa = ifp->if_addrlist; ifa && !pkcb; ifa = ifa->ifa_next) {
E 10
		if (ifa->ifa_addr->sa_family == AF_CCITT)
D 10
			break;
E 10
I 10
			pkcb = &((struct x25_ifaddr *)ifa)->ia_pkcb;
E 10
	}
D 10
	if (ifa)
		pkcb = &((struct x25_ifaddr *)ifa)->ia_pkcb;
E 10
	if (pkcb)
E 12
I 12
D 19
	for (pkcb = pkcbhead; pkcb; pkcb = pkcb->pk_next)
E 19
I 19
	FOR_ALL_PKCBS(pkcb)
E 19
	    if (pkcb->pk_ia->ia_ifp == ifp)
E 12
		for (lcpp = pkcb->pk_chan + pkcb->pk_maxlcn;
D 8
		     --lcpp >= pkcb->pk_chan;)
E 8
I 8
		     --lcpp > pkcb->pk_chan;)
E 8
			if ((lcp = *lcpp) &&
			    lcp->lcd_state == DATA_TRANSFER &&
D 6
			    (lcp->lcd_flags & X25_DG_CICRUIT) &&
E 6
I 6
			    (lcp->lcd_flags & X25_DG_CIRCUIT) &&
E 6
D 8
			    (--(lcp->lcd_dg_timer) <= 0)) {
D 6
				register struct rtextension_x25 *rtx;
E 6
I 6
				register struct llinfo_x25 *lx;
E 8
I 8
			    (lcp->lcd_dg_timer && --lcp->lcd_dg_timer == 0)) {
E 8
E 6
D 10
				pk_disconnect(lcp);
E 10
I 10
				lcp->lcd_upper(lcp, 0);
E 10
D 6
				rtx = (struct rtextension_x25 *)
D 5
						lcp->lcp_upq.pq_next;
E 5
I 5
						lcp->lcp_upnext;
E 5
				if (rtx)
					rtx->rtx_state = XRS_DISCONNECTING;
E 6
I 6
D 8
				lx = (struct llinfo_x25 *)
						lcp->lcd_upnext;
				if (lx)
					lx->lx_state = LXS_DISCONNECTING;
E 6
			    }
E 8
I 8
			}
E 8
E 3
	splx(s);
}
D 10

E 10
/*
D 10
 * Process a x25 packet as datagram;
E 10
I 10
 * This routine gets called when validating additions of new routes
D 11
 * or deletions of old *ones.
E 11
I 11
 * or deletions of old ones.
E 11
E 10
 */
D 3
x25_ifinput(xq, m)
struct xq *xq;
E 3
I 3
D 5
x25_ifinput(pq, m)
struct pq *pq;
E 5
I 5
D 10
x25_ifinput(lcp, m)
struct pklcd *lcp;
E 5
E 3
D 7
struct mbuf *m;
E 7
I 7
register struct mbuf *m;
E 7
{
D 3
	struct rtentry *rt = (struct rtentry *)xq->xq_next;
	struct x25lcb *xl = (struct x25lcb *)rt->rt_llinfo;
E 3
I 3
D 5
	struct rtentry *rt = (struct rtentry *)pq->pq_next;
	struct pklcd *xl = (struct pklcd *)rt->rt_llinfo;
E 3
	register struct ifnet *ifp = &xl->xl_xc.xc_if;
	register struct llc *l;
E 5
I 5
D 6
	struct rtextension *rtx = (struct rtentry *)lcp->lcd_upnext;
	register struct ifnet *ifp = &rtx->rtx_rt->rt_ifp;
E 6
I 6
	struct llinfo_x25 *lx = (struct llinfo_x25 *)lcp->lcd_upnext;
D 8
	struct rtentry *rt = lx->lx_rt;
	register struct ifnet *ifp = rt->rt_ifp;
E 8
I 8
	register struct ifnet *ifp = m->m_pkthdr.rcvif;
E 8
	struct ifqueue *inq;
I 8
	struct rtentry *rt;
E 8
	extern struct timeval time;
E 6
E 5
D 7
	int s;
E 7
I 7
D 8
	struct x25_packet *xp = mtod(m, struct x25_packet *);
	struct mbuf **mp = &lcp->lcd_ifrag;
E 8
D 9
	int s, len;
E 9
I 9
	int s, len, isr;
E 9
E 7

I 8
	if (m == 0)
		goto trouble;
	ifp = m->m_pkthdr.rcvif;
E 8
	ifp->if_lastchange = time;
I 7
	switch (m->m_type) {
I 8
	trouble:
E 8
	case MT_CONTROL:
I 8
		if (lcp->lcd_state != DATA_TRANSFER) {
			lx->lx_lcd = 0;
			if (lx->lx_rt == 0)
				FREE(lx, M_PCB);
			pk_close(lcp);
		}
E 8
	case MT_OOBDATA:
D 8
		m_freem(m);
E 8
I 8
		if (m)
			m_freem(m);
E 8
		return;
E 7
D 8

D 6
	switch (rt_dst(rt)->sa_family) {
E 6
I 6
D 7
	switch ((rt_key(rt))->sa_family) {
E 7
I 7
	case MT_DATA:
	case MT_HEADER:
		m->m_len -= PKHEADERLN;
		m->m_data += PKHEADERLN;
		m->m_pkthdr.len -= PKHEADERLN;
		while (*mp)
			mp = &((*mp)->m_next);
		*mp = m;
		if (MBIT(xp))
			return;
E 8
	}
D 8
	m = lcp->lcd_ifrag;
	if (m->m_flags & M_PKTHDR) {
		for (len = 0; m; m = m->m_next)
			len += m->m_len;
		m = lcp->lcd_ifrag;
		m->m_pkthdr.len = len;
	}
E 8

	switch (lx->lx_family) {
E 7
E 6
#ifdef INET
	case AF_INET:
D 9
		schednetisr(NETISR_IP);
E 9
I 9
		isr = NETISR_IP;
E 9
		inq = &ipintrq;
		break;

#endif
#ifdef NS
	case AF_NS:
D 9
		schednetisr(NETISR_NS);
E 9
I 9
		isr = NETISR_NS;
E 9
		inq = &nsintrq;
		break;

#endif
#ifdef	ISO
	case AF_ISO:
D 8
		/* XXXX need to find out about tearing off COSNS
		   headers if any */
E 8
D 9
		schednetisr(NETISR_ISO);
E 9
I 9
		isr = NETISR_ISO;
E 9
		inq = &clnlintrq;
		break;
#endif
	default:
		m_freem(m);
		ifp->if_noproto++;
		return;
	}
	s = splimp();
I 9
	schednetisr(isr);
E 9
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
	} else {
		IF_ENQUEUE(inq, m);
		ifp->if_ibytes += m->m_pkthdr.len;
	}
	splx(s);
}
I 8

/*
 * This routine gets called when validing new routes or deletions of old
 * ones.
 */
E 10
D 12
x25_ifrtchange(cmd, rt, dst)
E 12
I 12
x25_rtrequest(cmd, rt, dst)
E 12
register struct rtentry *rt;
struct sockaddr *dst;
{
	register struct llinfo_x25 *lx = (struct llinfo_x25 *)rt->rt_llinfo;
	register struct sockaddr_x25 *sa =(struct sockaddr_x25 *)rt->rt_gateway;
	register struct pklcd *lcp;
D 10
	register struct x25_ifaddr *ia;
	register struct sockaddr *sa2;
I 9
	struct rtentry *rt2;
E 9
	int x25_ifinput();
E 10
D 12
#define SA(p) ((struct sockaddr *)(p))
E 12

I 17
	/* would put this pk_init, except routing table doesn't
	   exist yet. */
	if (x25_dgram_sockmask == 0) {
		struct radix_node *rn_addmask();
		x25_dgram_sockmask =
			SA(rn_addmask((caddr_t)&x25_dgmask, 0, 4)->rn_key);
	}
E 17
I 9
D 10
	if (cmd == RTM_DELETE) {
		if (rt->rt_flags & RTF_GATEWAY) {
			rt = (struct rtentry *)rt->rt_llinfo;
		} else {
			if (lx) {
				if (lcp = lx->lx_lcd)
					pk_disconnect(lcp);
				FREE(lx, M_PCB);
			}
			rtrequest(RTM_DELETE, rt->rt_gateway, rt_key(rt),
				SA(0), 0, (struct rtentry **) 0);
		}
		rt->rt_refcnt--;
		rt->rt_llinfo = 0;
E 10
I 10
	if (rt->rt_flags & RTF_GATEWAY) {
		if (rt->rt_llinfo)
			RTFREE((struct rtentry *)rt->rt_llinfo);
		rt->rt_llinfo = (cmd == RTM_ADD) ? 
			(caddr_t)rtalloc1(rt->rt_gateway, 1) : 0;
E 10
		return;
	}
I 11
	if ((rt->rt_flags & RTF_HOST) == 0)
		return;
E 11
E 9
D 10
	if (lx == 0) {
		MALLOC(lx, struct llinfo_x25 *, sizeof (*lx), M_PCB, M_NOWAIT);
		if (lx == 0)
			return;
		Bzero(lx, sizeof(*lx));
		rt->rt_llinfo = (caddr_t)lx;
		rt->rt_refcnt++;
		lx->lx_rt = rt;
		lx->lx_ia = (struct x25_ifaddr *)rt->rt_ifa;
	}
D 9
	lcp = lx->lx_lcd;
	if (cmd == RTM_DELETE) {
		if (lcp)
			pk_disconnect(lcp);
		rt->rt_refcnt--;
		rt->rt_llinfo = 0;
		FREE(lx, M_PCB);
E 9
I 9
	if (rt->rt_flags & RTF_GATEWAY) {
		rt2 = rtalloc1(rt_key(rt), 1);
		if (rt2) {
			rt->rt_refcnt++;
			rt->rt_llinfo = (caddr_t)rt2;
		}
E 10
I 10
	if (cmd == RTM_DELETE) {
		while (rt->rt_llinfo)
			x25_lxfree((struct llinfo *)rt->rt_llinfo);
		x25_rtinvert(RTM_DELETE, rt->rt_gateway, rt);
E 10
E 9
		return;
	}
D 10
	if (lcp && lcp->lcd_state != READY) {
		pk_disconnect(lcp);
E 10
I 10
D 11
	if (lx == 0)
		lx = x25_lxalloc(rt);
E 11
I 11
	if (lx == 0 && (lx = x25_lxalloc(rt)) == 0)
		return;
E 11
	if ((lcp = lx->lx_lcd) && lcp->lcd_state != READY) {
		/*
		 * This can only happen on a RTM_CHANGE operation
		 * though cmd will be RTM_ADD.
		 */
		if (lcp->lcd_ceaddr &&
		    Bcmp(rt->rt_gateway, lcp->lcd_ceaddr,
					 lcp->lcd_ceaddr->x25_len) != 0) {
			x25_rtinvert(RTM_DELETE, lcp->lcd_ceaddr, rt);
			lcp->lcd_upper = 0;
			pk_disconnect(lcp);
		}
E 10
		lcp = 0;
	}
D 10
	if (lcp == 0) {
		if (rt->rt_flags & RTF_XRESOLVE || sa->x25_family != AF_CCITT)
			return;
		lx->lx_lcd = lcp = pk_attach((struct socket *)0);
		ia = lx->lx_ia;
		if (lcp == 0)
			return;
		lcp->lcd_upnext = (caddr_t)lx;
		lcp->lcd_upper = x25_ifinput;
		lcp->lcd_packetsize = ia->ia_xc.xc_psize; /* XXX pk_fragment */
		lcp->lcd_pkp = &(ia->ia_pkcb);
	}
	pk_connect(lcp, sa);
E 10
I 10
	x25_rtinvert(RTM_ADD, rt->rt_gateway, rt);
}

I 11
D 12
int x25_dont_rtinvert = 1;
E 12
I 12
int x25_dont_rtinvert = 0;
E 12

E 11
x25_rtinvert(cmd, sa, rt)
register struct sockaddr *sa;
register struct rtentry *rt;
{
	struct rtentry *rt2 = 0;
	/*
	 * rt_gateway contains PID indicating which proto
	 * family on the other end, so will be different
	 * from general host route via X.25.
	 */
I 11
D 12
	if (x25_dont_rtinvert)
E 12
I 12
	if (rt->rt_ifp->if_type == IFT_X25DDN || x25_dont_rtinvert)
E 12
		return;
E 11
E 10
D 12
	if (rt->rt_ifp->if_type == IFT_X25DDN)
		return;
E 12
I 9
D 10
	rtrequest(cmd, rt->rt_gateway, rt_key(rt), rt_mask(rt), rt->rt_flags,
			&rt2);
	if (rt2) {
		rt2->rt_llinfo = (caddr_t) rt;
	}
E 9
	sa2 = rt_key(rt);
	if (cmd == RTM_CHANGE) {
		if (sa->x25_family == AF_CCITT) {
			sa->x25_opts.op_speed = sa2->sa_family;
			(void) rtrequest(RTM_DELETE, SA(sa), sa2,
			       SA(0), RTF_HOST, (struct rtentry **)0);
E 10
I 10
	if (sa->sa_family != AF_CCITT)
		return;
D 12
	if (cmd == RTM_ADD) {
		rtrequest(RTM_ADD, sa, rt_key(rt), SA(0),
				RTF_HOST|RTF_PROTO1, &rt2);
E 12
I 12
	if (cmd != RTM_DELETE) {
		rtrequest(RTM_ADD, sa, rt_key(rt), x25_dgram_sockmask,
				RTF_PROTO2, &rt2);
E 12
		if (rt2) {
			rt2->rt_llinfo = (caddr_t) rt;
			rt->rt_refcnt++;
E 10
		}
D 10
		sa = (struct sockaddr_x25 *)dst;
		cmd = RTM_ADD;
E 10
I 10
		return;
E 10
	}
D 10
	if (sa->x25_family == AF_CCITT) {
		sa->x25_opts.op_speed = sa2->sa_family;
		(void) rtrequest(cmd, SA(sa), sa2, SA(0), RTF_HOST,
							(struct rtentry **)0);
		sa->x25_opts.op_speed = 0;
	}
E 10
I 10
	rt2 = rt;
	if ((rt = rtalloc1(sa, 0)) == 0 ||
D 12
	    (rt->rt_flags & RTF_PROTO1) == 0 ||
	    rt->rt_llinfo != (caddr_t)rt) {
E 12
I 12
	    (rt->rt_flags & RTF_PROTO2) == 0 ||
	    rt->rt_llinfo != (caddr_t)rt2) {
E 12
		printf("x25_rtchange: inverse route screwup\n");
		return;
	} else
		rt2->rt_refcnt--;
D 12
	rtrequest(RTM_DELETE, rt->rt_gateway, rt_key(rt),
		SA(0), 0, (struct rtentry **) 0);
E 12
I 12
	rtrequest(RTM_DELETE, sa, rt_key(rt2), x25_dgram_sockmask,
				0, (struct rtentry **) 0);
E 12
E 10
}

E 8
D 6

union imp_addr {
	struct in_addr  ip;
	struct imp {
		u_char		s_net;
		u_char		s_host;
		u_char		s_lh;
		u_char		s_impno;
	}		    imp;
};
E 6
static struct sockaddr_x25 blank_x25 = {sizeof blank_x25, AF_CCITT};
/*
 * IP to X25 address routine copyright ACC, used by permission.
 */
I 8
union imp_addr {
	struct in_addr  ip;
	struct imp {
		u_char		s_net;
		u_char		s_host;
		u_char		s_lh;
		u_char		s_impno;
	}		    imp;
};

E 8
D 10
x25_ddnip_to_ccitt(src, dst)
E 10
I 10
/*
 * The following is totally bogus and here only to preserve
 * the IP to X.25 translation.
 */
x25_ddnip_to_ccitt(src, rt)
E 10
struct sockaddr_in *src;
D 10
register struct sockaddr_x25 *dst;
E 10
I 10
register struct rtentry *rt;
E 10
{
I 10
	register struct sockaddr_x25 *dst = (struct sockaddr_x25 *)rt->rt_gateway;
E 10
	union imp_addr imp_addr;
D 6
	int             imp_no, imp_port;
	char *x25addr = dst->x25_x25addr;
E 6
I 6
	int             imp_no, imp_port, temp;
	char *x25addr = dst->x25_addr;
E 6


D 6
	imp_addr.ip = src->sin_addr.s_addr;
E 6
I 6
	imp_addr.ip = src->sin_addr;
E 6
	*dst = blank_x25;
	if ((imp_addr.imp.s_net & 0x80) == 0x00) {	/* class A */
	    imp_no = imp_addr.imp.s_impno;
	    imp_port = imp_addr.imp.s_host;
	} else if ((imp_addr.imp.s_net & 0xc0) == 0x80) {	/* class B */
	    imp_no = imp_addr.imp.s_impno;
	    imp_port = imp_addr.imp.s_lh;
	} else {		/* class C */
	    imp_no = imp_addr.imp.s_impno / 32;
	    imp_port = imp_addr.imp.s_impno % 32;
	}

	x25addr[0] = 12; /* length */
	/* DNIC is cleared by struct copy above */

	if (imp_port < 64) {	/* Physical:  0000 0 IIIHH00 [SS] *//* s_impno
				 *  -> III, s_host -> HH */
	    x25addr[5] = 0;	/* set flag bit */
	    x25addr[6] = imp_no / 100;
	    x25addr[7] = (imp_no % 100) / 10;
	    x25addr[8] = imp_no % 10;
	    x25addr[9] = imp_port / 10;
	    x25addr[10] = imp_port % 10;
	} else {		/* Logical:   0000 1 RRRRR00 [SS]	 *//* s
				 * _host * 256 + s_impno -> RRRRR */
	    temp = (imp_port << 8) + imp_no;
	    x25addr[5] = 1;
	    x25addr[6] = temp / 10000;
	    x25addr[7] = (temp % 10000) / 1000;
	    x25addr[8] = (temp % 1000) / 100;
	    x25addr[9] = (temp % 100) / 10;
	    x25addr[10] = temp % 10;
	}
}

D 8
#ifdef caseof
#undef caseof
#endif
#define caseof(a, b) (b + 8 * a)
#define SA(p) ((struct sockaddr *)(p))

/*
 * This routine gets called when validing new routes or deletions of old
 * ones.
 */
x25_ifrtchange(cmd, rt, dst)
register struct rtentry *rt;
struct sockaddr *dst;
{
D 3
	register struct x25lcb *xl = (struct x25lcb *)rt->rt_llinfo;
	register struct x25com *xc;
E 3
I 3
D 6
	register struct rtextension_x25 *rtx = (struct pklcd *)rt->rt_llinfo;
E 6
I 6
	register struct llinfo_x25 *lx = (struct llinfo_x25 *)rt->rt_llinfo;
E 6
E 3
	register struct sockaddr_x25 *sa =(struct sockaddr_x25 *)rt->rt_gateway;
I 3
	register struct pklcd *lcp;
	register struct x25_ifaddr *ia;
E 3
	register struct sockaddr *sa2;
	struct mbuf *m, *mold;
I 3
D 5
	int x25_ifrtree();
E 5
I 5
	int x25_ifrtfree();
E 5
E 3

D 3
	if (xl == 0)
E 3
I 3
D 6
	if (rtx == 0)
E 6
I 6
	if (lx == 0)
E 6
E 3
		return;
D 3
	xc = xl->xl_xc;
E 3
I 3
D 6
	ia = rtx->rtx_ia;
	lcp = rtx->rtx_lcd;
E 6
I 6
	ia = lx->lx_ia;
	lcp = lx->lx_lcd;
E 6

E 3
D 6
	switch (caseof(xl->xl_state, cmd)) {
E 6
I 6
	switch (caseof(lx->lx_state, cmd)) {
E 6
D 3
	case caseof(XLS_CONNECTED, RTM_DELETE):
	case caseof(XLS_CONNECTED, RTM_CHANGE):
	case caseof(XLS_CONNECTING, RTM_DELETE):
	case caseof(XLS_CONNECTING, RTM_CHANGE):
		xc->xc_disconnect(xl);
E 3
I 3

D 6
	case caseof(XRS_CONNECTED, RTM_DELETE):
	case caseof(XRS_CONNECTED, RTM_CHANGE):
	case caseof(XRS_CONNECTING, RTM_DELETE):
	case caseof(XRS_CONNECTING, RTM_CHANGE):
E 6
I 6
	case caseof(LXS_CONNECTED, RTM_DELETE):
	case caseof(LXS_CONNECTED, RTM_CHANGE):
	case caseof(LXS_CONNECTING, RTM_DELETE):
	case caseof(LXS_CONNECTING, RTM_CHANGE):
E 6
		pk_disconnect(lcp);
D 5
		lcp->lcd_upq.pq_unblock = x25_ifrtfree;
E 5
I 5
D 7
		lcp->lcd_upper = x25_ifrtfree;
E 7
I 7
		/*lcp->lcd_upper = x25_ifrtfree; */
E 7
E 5
		rt->rt_refcnt++;
E 3
		break;

D 3
	case caseof(XLS_CONNECTED, RTM_ADD):
	case caseof(XLS_CONNECTING, RTM_ADD):
	case caseof(XLS_RESOLVING, RTM_ADD):
E 3
I 3
D 6
	case caseof(XRS_CONNECTED, RTM_ADD):
	case caseof(XRS_CONNECTING, RTM_ADD):
	case caseof(XRS_RESOLVING, RTM_ADD):
E 6
I 6
	case caseof(LXS_CONNECTED, RTM_ADD):
	case caseof(LXS_CONNECTING, RTM_ADD):
	case caseof(LXS_RESOLVING, RTM_ADD):
E 6
E 3
		printf("ifrtchange: impossible transition, should panic\n");
		break;

D 3
	case caseof(XLS_RESOLVING, RTM_DELETE):
		for (m = xl->xl_downq.xq_data; m;) {
E 3
I 3
D 6
	case caseof(XRS_RESOLVING, RTM_DELETE):
D 5
		for (m = lcp->lcd_downq.pq_data; m;) {
E 3
			mold = m;
			m = m->m_nextpkt;
			m_freem(mold);
		}
I 3
		m_free(dtom(rtx->rtx_lcd));
E 5
I 5
		sbflush(&(rtx->rtx_lcd->lcd_sb));
		free((caddr_t)rtx->rtx_lcd, M_PCB);
E 5
		rtx->rtx_lcd = 0;
E 6
I 6
	case caseof(LXS_RESOLVING, RTM_DELETE):
		sbflush(&(lx->lx_lcd->lcd_sb));
		free((caddr_t)lx->lx_lcd, M_PCB);
		lx->lx_lcd = 0;
E 6
E 3
		break;

D 3
	case caseof(XLS_RESOLVING, RTM_CHANGE):
		xc->xc_if.if_start(xl, 0, dst);
E 3
I 3
D 6
	case caseof(XRS_RESOLVING, RTM_CHANGE):
		lcp->lcd_pkcb = &(ia->ia_pkcb);
E 6
I 6
	case caseof(LXS_RESOLVING, RTM_CHANGE):
		lcp->lcd_pkp = &(ia->ia_pkcb);
E 6
D 4
		pk_connect(lcp, nam);
E 4
I 4
		pk_connect(lcp, (struct mbuf *)0, sa);
E 4
E 3
		break;
	}
D 3
	if (xc->xc_if.if_type == IFT_DDN)
		return;  /* reverse name table not necessary */
E 3
I 3
D 6
	if (rt->rt_ifp->if_type == IFT_DDN)
E 6
I 6
	if (rt->rt_ifp->if_type == IFT_X25DDN)
E 6
		return;
E 3
D 6
	sa2 = SA(rt->rt_key);
E 6
I 6
	sa2 = rt_key(rt);
E 6
	if (cmd == RTM_CHANGE) {
D 6
		if (sa->sa_family == AF_CCITT) {
E 6
I 6
		if (sa->x25_family == AF_CCITT) {
E 6
D 5
			sa->sa_rfamily = sa2->sa_family;
E 5
I 5
			sa->x25_opts.op_speed = sa2->sa_family;
E 5
			(void) rtrequest(RTM_DELETE, SA(sa), sa2,
			       SA(0), RTF_HOST, (struct rtentry **)0);
		}
		sa = (struct sockaddr_x25 *)dst;
		cmd = RTM_ADD;
	}
D 6
	if (sa->sa_family == AF_CCITT) {
E 6
I 6
	if (sa->x25_family == AF_CCITT) {
E 6
D 5
		sa->sa_rfamily = sa2->sa_family;
E 5
I 5
		sa->x25_opts.op_speed = sa2->sa_family;
E 5
		(void) rtrequest(cmd, SA(sa), sa2, SA(0), RTF_HOST,
							(struct rtentry **)0);
D 5
		sa->sa_rfamily = 0;
E 5
I 5
		sa->x25_opts.op_speed = 0;
E 5
	}
}
I 5

E 8
E 5
D 6
static struct sockaddr sin = {sizeof(sin), AF_INET};
E 6
I 6
D 10
static struct sockaddr_in sin = {sizeof(sin), AF_INET};
E 10
E 6
/*
I 8
 * This routine is a sketch and is not to be believed!!!!!
 *
E 8
 * This is a utility routine to be called by x25 devices when a
 * call request is honored with the intent of starting datagram forwarding.
 */
D 3
x25_dg_rtinit(dst, xc, af)
E 3
I 3
x25_dg_rtinit(dst, ia, af)
E 3
struct sockaddr_x25 *dst;
D 3
register struct x25com *xc;
E 3
I 3
D 6
register struct x25com *ia;
E 6
I 6
register struct x25_ifaddr *ia;
E 6
E 3
{
	struct sockaddr *sa = 0;
D 3
	if (xc->xc_if.if_type == IFT_DDN && af == AF_INET) {
E 3
I 3
D 6
	if (ia->xc_if.if_type == IFT_DDN && af == AF_INET) {
E 6
I 6
	struct rtentry *rt;
	struct in_addr my_addr;
I 10
	static struct sockaddr_in sin = {sizeof(sin), AF_INET};
E 10

	if (ia->ia_ifp->if_type == IFT_X25DDN && af == AF_INET) {
E 6
E 3
	/*
D 6
	 * Inverse X25 to IPP mapping copyright and courtesy ACC.
E 6
I 6
	 * Inverse X25 to IP mapping copyright and courtesy ACC.
E 6
	 */
		int             imp_no, imp_port, temp;
		union imp_addr imp_addr;
	    {
		/*
		 * First determine our IP addr for network
		 */
D 6
		register struct in_ifaddr *ia;
E 6
I 6
		register struct in_ifaddr *ina;
E 6
		extern struct in_ifaddr *in_ifaddr;
D 6
		for (ia = in_ifaddr; ia; ia = ia->ia_next)
D 3
			if (ia->ia_ifp == &xc->xc_if) {
E 3
I 3
			if (ia->ia_ifp == &ia->xc_if) {
E 3
				imp_addr.ip = ia->ia_addr.sin_addr;
E 6
I 6

		for (ina = in_ifaddr; ina; ina = ina->ia_next)
			if (ina->ia_ifp == ia->ia_ifp) {
				my_addr = ina->ia_addr.sin_addr;
E 6
				break;
			}
	    }
	    {

		register char *x25addr = dst->x25_addr;

		switch (x25addr[5] & 0x0f) {
		  case 0:	/* Physical:  0000 0 IIIHH00 [SS]	 */
		    imp_no =
			((int) (x25addr[6] & 0x0f) * 100) +
			((int) (x25addr[7] & 0x0f) * 10) +
			((int) (x25addr[8] & 0x0f));


		    imp_port =
			((int) (x25addr[9] & 0x0f) * 10) +
			((int) (x25addr[10] & 0x0f));
		    break;
		  case 1:	/* Logical:   0000 1 RRRRR00 [SS]	 */
		    temp = ((int) (x25addr[6] & 0x0f) * 10000)
			+ ((int) (x25addr[7] & 0x0f) * 1000)
			+ ((int) (x25addr[8] & 0x0f) * 100)
			+ ((int) (x25addr[9] & 0x0f) * 10)
			+ ((int) (x25addr[10] & 0x0f));

		    imp_port = temp >> 8;
		    imp_no = temp & 0xff;
		    break;
		  default:
		    return (0L);
		}
D 6
		imp_addr.ip.s_addr = my_addr;
E 6
I 6
		imp_addr.ip = my_addr;
E 6
		if ((imp_addr.imp.s_net & 0x80) == 0x00) {
		/* class A */
		    imp_addr.imp.s_host = imp_port;
		    imp_addr.imp.s_impno = imp_no;
		    imp_addr.imp.s_lh = 0;
		} else if ((imp_addr.imp.s_net & 0xc0) == 0x80) {
		/* class B */
		    imp_addr.imp.s_lh = imp_port;
		    imp_addr.imp.s_impno = imp_no;
		} else {
		/* class C */
		    imp_addr.imp.s_impno = (imp_no << 5) + imp_port;
		}
	    }
		sin.sin_addr = imp_addr.ip;
		sa = (struct sockaddr *)&sin;
	} else {
		/*
		 * This uses the X25 routing table to do inverse
		 * lookup of x25 address to sockaddr.
		 */
D 5
		dst->sa_rfamily = af;
E 5
I 5
D 10
		dst->x25_opts.op_speed = af;
E 10
E 5
D 21
		if (rt = rtalloc1(dst, 0)) {
E 21
I 21
		if (rt = rtalloc1(SA(dst), 0)) {
E 21
			sa = rt->rt_gateway;
			rt->rt_refcnt--;
		}
D 5
		dst->sa_rfamily = 0;
E 5
I 5
D 10
		dst->x25_opts.op_speed = 0;
E 10
E 5
	}
	/* 
	 * Call to rtalloc1 will create rtentry for reverse path
	 * to callee by virtue of cloning magic and will allocate
	 * space for local control block.
	 */
D 6
	if (sa && rt = rtalloc1(sa, 1))
E 6
I 6
	if (sa && (rt = rtalloc1(sa, 1)))
E 6
		rt->rt_refcnt--;
I 5
}
D 12

E 12
I 12
D 17
#ifndef _offsetof
#define _offsetof(t, m) ((int)((caddr_t)&((t *)0)->m))
#endif
struct sockaddr_x25 x25_dgmask = {
 _offsetof(struct sockaddr_x25, x25_udata[1]),			/* _len */
 0,								/* _family */
 0,								/* _net */
 { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, /* _addr */
 {0},								/* opts */
 -1,								/* _udlen */
 {-1}								/* _udata */
};
E 17
int x25_startproto = 1;
E 12
D 15
struct radix_tree_head *x25_rnhead;
E 15

pk_init()
{
	/*
	 * warning, sizeof (struct sockaddr_x25) > 32,
	 * but contains no data of interest beyond 32
	 */
I 12
D 17
	struct radix_node *rn_addmask();
E 12
D 9
	rn_inithead(&x25_rnhead, 16, AF_CCITT);
E 9
I 9
D 15
	rn_inithead(&x25_rnhead, 32, AF_CCITT);
E 15
I 15
D 16
	rn_inithead(&rt_tables[AF_CCITT], 32);
E 16
E 15
I 12
	x25_dgram_sockmask =
		SA(rn_addmask((caddr_t)&x25_dgmask, 0, 4)->rn_key);
E 17
	if (x25_startproto) {
		pk_protolisten(0xcc, 1, x25_dgram_incoming);
		pk_protolisten(0x81, 1, x25_dgram_incoming);
	}
E 12
I 10
}
I 12

struct x25_dgproto {
	u_char spi;
	u_char spilen;
	int (*f)();
} x25_dgprototab[] = {
#if defined(ISO) && defined(TPCONS)
{ 0x0, 0, tp_incoming},
#endif
{ 0xcc, 1, x25_dgram_incoming},
{ 0xcd, 1, x25_dgram_incoming},
{ 0x81, 1, x25_dgram_incoming},
};

pk_user_protolisten(info)
register u_char *info;
{
	register struct x25_dgproto *dp = x25_dgprototab
		    + ((sizeof x25_dgprototab) / (sizeof *dp));
	register struct pklcd *lcp;
	
	while (dp > x25_dgprototab)
		if ((--dp)->spi == info[0])
			goto gotspi;
	return ESRCH;

gotspi:	if (info[1])
		return pk_protolisten(dp->spi, dp->spilen, dp->f);
	for (lcp = pk_listenhead; lcp; lcp = lcp->lcd_listen)
		if (lcp->lcd_laddr.x25_udlen == dp->spilen &&
		    Bcmp(&dp->spi, lcp->lcd_laddr.x25_udata, dp->spilen) == 0) {
D 14
			pk_close(lcp);
E 14
I 14
			pk_disconnect(lcp);
E 14
			return 0;
		}
	return ESRCH;
}

E 12
/*
D 12
 * This routine steals a virtual circuit from a socket,
 * and glues it to a routing entry.  It wouldn't be hard
 * to extend this to a routine that stole back the vc from
 * rtentry.
E 12
I 12
 * This routine transfers an X.25 circuit to or from a routing entry.
 * If the supplied circuit is * in DATA_TRANSFER state, it is added to the
 * routing entry.  If freshly allocated, it glues back the vc from
 * the rtentry to the socket.
E 12
 */
pk_rtattach(so, m0)
register struct socket *so;
struct mbuf *m0;
{
	register struct pklcd *lcp = (struct pklcd *)so->so_pcb;
	register struct mbuf *m = m0;
	struct sockaddr *dst = mtod(m, struct sockaddr *);
	register struct rtentry *rt = rtalloc1(dst, 0);
	register struct llinfo_x25 *lx;
	caddr_t cp;
#define ROUNDUP(a) \
	((a) > 0 ? (1 + (((a) - 1) | (sizeof(long) - 1))) : sizeof(long))
#define transfer_sockbuf(s, f, l) \
D 12
	while (m = (s)->sb_mb) {(s)->sb_mb = m->m_act; sbfree((s), m); f(l, m);}
E 12
I 12
	while (m = (s)->sb_mb)\
		{(s)->sb_mb = m->m_act; m->m_act = 0; sbfree((s), m); f(l, m);}
E 12

	if (rt)
		rt->rt_refcnt--;
	cp = (dst->sa_len < m->m_len) ? ROUNDUP(dst->sa_len) + (caddr_t)dst : 0;
	while (rt &&
	       ((cp == 0 && rt_mask(rt) != 0) ||
		(cp != 0 && (rt_mask(rt) == 0 ||
			     Bcmp(cp, rt_mask(rt), rt_mask(rt)->sa_len)) != 0)))
			rt = (struct rtentry *)rt->rt_nodes->rn_dupedkey;
	if (rt == 0 || (rt->rt_flags & RTF_GATEWAY) ||
	    (lx = (struct llinfo_x25 *)rt->rt_llinfo) == 0)
		return ESRCH;
D 12
	if (lcp == 0 || lcp->lcd_state != DATA_TRANSFER)
E 12
I 12
	if (lcp == 0)
E 12
		return ENOTCONN;
I 12
	switch (lcp->lcd_state) {
	default:
		return ENOTCONN;

	case READY:
		/* Detach VC from rtentry */
		if (lx->lx_lcd == 0)
			return ENOTCONN;
		lcp->lcd_so = 0;
		pk_close(lcp);
		lcp = lx->lx_lcd;
		if (lx->lx_next->lx_rt == rt)
			x25_lxfree(lx);
		lcp->lcd_so = so;
		lcp->lcd_upper = 0;
		lcp->lcd_upnext = 0;
		transfer_sockbuf(&lcp->lcd_sb, sbappendrecord, &so->so_snd);
		soisconnected(so);
		return 0;

	case DATA_TRANSFER:
		/* Add VC to rtentry */
		lcp->lcd_so = 0;
		lcp->lcd_sb = so->so_snd; /* structure copy */
		bzero((caddr_t)&so->so_snd, sizeof(so->so_snd)); /* XXXXXX */
		so->so_pcb = 0;
		x25_rtattach(lcp, rt);
		transfer_sockbuf(&so->so_rcv, x25_ifinput, lcp);
		soisdisconnected(so);
	}
	return 0;
}
x25_rtattach(lcp0, rt)
register struct pklcd *lcp0;
struct rtentry *rt;
{
	register struct llinfo_x25 *lx = (struct llinfo_x25 *)rt->rt_llinfo;
	register struct pklcd *lcp;
	register struct mbuf *m;
E 12
	if (lcp = lx->lx_lcd) { /* adding an additional VC */
		if (lcp->lcd_state == READY) {
D 12
			transfer_sockbuf(&lcp->lcd_sb, pk_output,
					 (struct pklcd *)so->so_pcb);
E 12
I 12
			transfer_sockbuf(&lcp->lcd_sb, pk_output, lcp0);
E 12
			lcp->lcd_upper = 0;
			pk_close(lcp);
		} else {
			lx = x25_lxalloc(rt);
			if (lx == 0)
				return ENOBUFS;
		}
	}
D 12
	lx->lx_lcd = lcp = (struct pklcd *)so->so_pcb;
	lcp->lcd_so = 0;
	lcp->lcd_sb = so->so_snd; /* structure copy */
E 12
I 12
	lx->lx_lcd = lcp = lcp0;
E 12
	lcp->lcd_upper = x25_ifinput;
	lcp->lcd_upnext = (caddr_t)lx;
D 12
	transfer_sockbuf(&so->so_rcv, x25_ifinput, lcp);
	so->so_pcb = 0;
	bzero((caddr_t)&so->so_snd, sizeof(so->so_snd)); /* XXXXXX */
	soisdisconnected(so);
	return (0);
E 12
E 10
E 9
E 5
}
E 1
