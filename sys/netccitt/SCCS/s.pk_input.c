h16288
s 00002/00002/01091
d D 8.1 93/06/10 22:53:52 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00074/00073/01019
d D 7.20 93/02/12 15:29:26 sklower 21 20
c make use of UBC formatting conventions consistent
e
s 00007/00004/01085
d D 7.19 93/02/12 15:07:26 sklower 20 19
c CLNP needs rcvif to be correct. put back! (from MITRE)
e
s 00003/00000/01086
d D 7.18 92/12/08 18:10:46 sklower 19 18
c didn't get includes right
e
s 00190/00028/00896
d D 7.17 92/12/08 17:11:12 sklower 18 17
c changes to run over both LLC and HDLC, and also use explicit shifts
c instead of bitfields.
e
s 00011/00011/00913
d D 7.16 92/10/11 11:49:41 bostic 17 16
c make kernel includes standard
e
s 00002/00002/00922
d D 7.15 92/02/07 16:15:02 sklower 16 15
c m_copym call lacked 4th arg; reverted to m_copy; removed lint.
e
s 00005/00005/00919
d D 7.14 91/07/16 23:00:48 sklower 15 14
c fix outright bug (looking at wrong part of packet for facilities
c on incoming calls
e
s 00002/00002/00922
d D 7.13 91/06/06 19:39:39 sklower 14 13
c this version now supports IP over X.25; changes include setting 
c the X25_MBS_HOLD  flag and preserving flags through incoming call cloning and aassociation
e
s 00226/00125/00698
d D 7.12 91/05/29 19:27:52 sklower 13 12
c revive pk_newlink so LLC2 can generate them on the fly;
c try putting ISODE's x.121 canonicalization in kernel; (doesn't work yet);
c various other minor changes.  This works with IP  in loopback.
e
s 00010/00010/00813
d D 7.11 91/05/09 21:20:58 sklower 12 11
c debugging version
e
s 00015/00006/00808
d D 7.10 91/05/06 18:11:14 sklower 11 9
c change conventions on static routine, ``call_accepted'';
c have it call upper layers which invoked.
e
s 00014/00005/00809
d R 7.10 91/05/03 18:42:28 sklower 10 9
c notify non-socket upper layers when cleared or accepted;
c changed convetions on call_accepted to pass mbuf instead of x25 packet ptr
e
s 00004/00003/00810
d D 7.9 91/03/12 15:12:04 sklower 9 8
c fix minor bug dereferencing null control blocks\;
e
s 00096/00028/00717
d D 7.8 91/01/09 15:40:16 sklower 8 7
c checkpoint -- this version compiles and represents most of 
c the changes to have ISO CONS be a kernel client of X.25; not tested!!!!
e
s 00024/00015/00721
d D 7.7 90/11/13 14:36:18 sklower 7 6
c fix bug with mbit info lost due to being overwritten before tested;
c use entire 12 bit lcn space; start including DBIT support
e
s 00089/00029/00647
d D 7.6 90/10/04 19:50:05 sklower 6 5
c capture current work; fix minor bugs concerning packet lengths &
c conventions; add routine to fragment datagrams into complete sequences.
e
s 00013/00012/00663
d D 7.5 90/08/30 18:48:32 sklower 5 4
c this version compiles; completely untested
e
s 00008/00005/00667
d D 7.4 90/06/21 12:28:50 sklower 4 3
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00014/00113/00658
d D 7.3 90/05/22 15:46:15 sklower 3 2
c checkpoint before changing pq structure to be a sockbuf for downq 
c and only retaining up method
e
s 00013/00001/00758
d D 7.2 90/05/11 15:22:11 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00759/00000/00000
d D 7.1 90/05/11 11:19:39 sklower 1 0
c date and time created 90/05/11 11:19:39 by sklower
e
u
U
t
T
I 1
D 2
/* Copyright (c) University of British Columbia, 1984 */
E 2
I 2
/*
 * Copyright (c) University of British Columbia, 1984
D 11
 * Copyright (c) 1990 The Regents of the University of California.
E 11
I 11
D 18
 * Copyright (c) 1991 The Regents of the University of California.
E 18
I 18
 * Copyright (C) Computer Science Department IV, 
 * 		 University of Erlangen-Nuremberg, Germany, 1992
D 22
 * Copyright (c) 1991, 1992  The Regents of the University of California.
E 18
E 11
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
D 18
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
E 18
I 18
 * This code is derived from software contributed to Berkeley by the
 * Laboratory for Computation Vision and the Computer Science Department
 * of the the University of British Columbia and the Computer Science
 * Department (IV) of the University of Erlangen-Nuremberg, Germany.
E 18
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 5
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
E 5
I 5
D 17
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
#include "protosw.h"
#include "socketvar.h"
#include "errno.h"
E 17
I 17
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 17
E 5

D 17
#include "../net/if.h"
E 17
I 17
#include <net/if.h>
I 19
#include <net/if_dl.h>
#include <net/if_llc.h>
#include <net/route.h>
E 19
E 17

I 18
#include <netccitt/dll.h>
E 18
D 5
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 5
I 5
D 17
#include "x25.h"
#include "pk.h"
#include "pk_var.h"
E 17
I 17
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
I 18
#include <netccitt/llc_var.h>
E 18
E 17
E 5

I 18
struct pkcb_q pkcb_q = {&pkcb_q, &pkcb_q};

/*
 * ccittintr() is the generic interrupt handler for HDLC, LLC2, and X.25. This
 * allows to have kernel running X.25 but no HDLC or LLC2 or both (in case we
 * employ boards that do all the stuff themselves, e.g. ADAX X.25 or TPS ISDN.)
 */
void
D 21
ccittintr()
E 21
I 21
ccittintr ()
E 21
{
	extern struct ifqueue pkintrq;
	extern struct ifqueue hdintrq;
	extern struct ifqueue llcintrq;

#ifdef HDLC
	if (hdintrq.ifq_len)
		hdintr ();
#endif
#ifdef LLC
	if (llcintrq.ifq_len)
		llcintr ();
#endif
	if (pkintrq.ifq_len)
		pkintr ();
}

E 18
I 13
struct pkcb *
pk_newlink (ia, llnext)
struct x25_ifaddr *ia;
caddr_t llnext;
{
D 21
	register struct x25config *xcp = &ia->ia_xc;
E 21
I 21
	register struct x25config *xcp = &ia -> ia_xc;
E 21
	register struct pkcb *pkp;
	register struct pklcd *lcp;
	register struct protosw *pp;
	unsigned size;

D 21
	pp = pffindproto (AF_CCITT, (int)xcp -> xc_lproto, 0);
E 21
I 21
	pp = pffindproto (AF_CCITT, (int) xcp -> xc_lproto, 0);
E 21
	if (pp == 0 || pp -> pr_output == 0) {
		pk_message (0, xcp, "link level protosw error");
		return ((struct pkcb *)0);
	}
	/*
	 * Allocate a network control block structure
	 */
	size = sizeof (struct pkcb);
D 21
	pkp = (struct pkcb *)malloc(size, M_PCB, M_WAITOK);
E 21
I 21
	pkp = (struct pkcb *) malloc (size, M_PCB, M_WAITOK);
E 21
	if (pkp == 0)
		return ((struct pkcb *)0);
D 21
	bzero ((caddr_t)pkp, size);
E 21
I 21
	bzero ((caddr_t) pkp, size);
E 21
	pkp -> pk_lloutput = pp -> pr_output;
I 18
D 21
	pkp -> pk_llctlinput = (caddr_t (*)())pp -> pr_ctlinput;
E 21
I 21
	pkp -> pk_llctlinput = (caddr_t (*)()) pp -> pr_ctlinput;
E 21
E 18
	pkp -> pk_xcp = xcp;
	pkp -> pk_ia = ia;
	pkp -> pk_state = DTE_WAITING;
D 18
	pkp -> pk_next = pkcbhead;
E 18
	pkp -> pk_llnext = llnext;
D 18
	pkcbhead = pkp;
E 18
I 18
D 21
	insque(pkp, &pkcb_q);
E 21
I 21
	insque (pkp, &pkcb_q);
E 21
E 18

	/*
	 * set defaults
	 */

	if (xcp -> xc_pwsize == 0)
		xcp -> xc_pwsize = DEFAULT_WINDOW_SIZE;
	if (xcp -> xc_psize == 0)
		xcp -> xc_psize = X25_PS128;
	/*
	 * Allocate logical channel descriptor vector
	 */

D 21
	(void)pk_resize(pkp);
E 21
I 21
	(void) pk_resize (pkp);
E 21
	return (pkp);
}

I 18

pk_dellink (pkp)
register struct pkcb *pkp;
{
	register int i;
	register struct protosw *pp;
	
	/*
	 * Essentially we have the choice to
	 * (a) go ahead and let the route be deleted and
	 *     leave the pkcb associated with that route
	 *     as it is, i.e. the connections stay open
	 * (b) do a pk_disconnect() on all channels associated
	 *     with the route via the pkcb and then proceed.
	 *
	 * For the time being we stick with (b)
	 */
	
D 21
	for(i = 1; i < pkp->pk_maxlcn; ++i)
		if (pkp->pk_chan[i])
			pk_disconnect(pkp->pk_chan[i]);
E 21
I 21
	for (i = 1; i < pkp -> pk_maxlcn; ++i)
		if (pkp -> pk_chan[i])
			pk_disconnect (pkp -> pk_chan[i]);
E 21

	/*
	 * Free the pkcb
	 */

	/*
	 * First find the protoswitch to get hold of the link level
	 * protocol to be notified that the packet level entity is
	 * dissolving ...
	 */
D 21
	pp = pffindproto (AF_CCITT, (int)pkp ->pk_xcp -> xc_lproto, 0);
E 21
I 21
	pp = pffindproto (AF_CCITT, (int) pkp -> pk_xcp -> xc_lproto, 0);
E 21
	if (pp == 0 || pp -> pr_output == 0) {
		pk_message (0, pkp -> pk_xcp, "link level protosw error");
D 21
		return(EPROTONOSUPPORT);
E 21
I 21
		return (EPROTONOSUPPORT);
E 21
	}

	pkp -> pk_refcount--;
	if (!pkp -> pk_refcount) {
		struct dll_ctlinfo ctlinfo;

D 21
		remque(pkp);
E 21
I 21
		remque (pkp);
E 21
		if (pkp -> pk_rt -> rt_llinfo == (caddr_t) pkp)
			pkp -> pk_rt -> rt_llinfo = (caddr_t) NULL;
		
		/*
		 * Tell the link level that the pkcb is dissolving
		 */
		if (pp -> pr_ctlinput && pkp -> pk_llnext) {
			ctlinfo.dlcti_pcb = pkp -> pk_llnext;
			ctlinfo.dlcti_rt = pkp -> pk_rt;
			(pp -> pr_ctlinput)(PRC_DISCONNECT_REQUEST, 
					    pkp -> pk_xcp, &ctlinfo);
		}
D 21
		free((caddr_t) pkp -> pk_chan, M_IFADDR);
		free((caddr_t) pkp, M_PCB);
E 21
I 21
		free ((caddr_t) pkp -> pk_chan, M_IFADDR);
		free ((caddr_t) pkp, M_PCB);
E 21
	}

	return (0);
}


E 18
pk_resize (pkp)
register struct pkcb *pkp;
{
	struct pklcd *dev_lcp = 0;
	struct x25config *xcp = pkp -> pk_xcp;
	if (pkp -> pk_chan &&
	    (pkp -> pk_maxlcn != xcp -> xc_maxlcn)) {
		pk_restart (pkp, X25_RESTART_NETWORK_CONGESTION);
		dev_lcp = pkp -> pk_chan[0];
D 21
		free ((caddr_t)pkp -> pk_chan, M_IFADDR);
E 21
I 21
		free ((caddr_t) pkp -> pk_chan, M_IFADDR);
E 21
		pkp -> pk_chan = 0;
	}
	if (pkp -> pk_chan == 0) {
		unsigned size;
		pkp -> pk_maxlcn = xcp -> xc_maxlcn;
		size = (pkp -> pk_maxlcn + 1) * sizeof (struct pklcd *);
		pkp -> pk_chan =
			(struct pklcd **) malloc (size, M_IFADDR, M_WAITOK);
		if (pkp -> pk_chan) {
D 21
			bzero ((caddr_t)pkp -> pk_chan, size);
E 21
I 21
			bzero ((caddr_t) pkp -> pk_chan, size);
E 21
			/*
			 * Allocate a logical channel descriptor for lcn 0
			 */
			if (dev_lcp == 0 &&
			    (dev_lcp = pk_attach ((struct socket *)0)) == 0)
				return (ENOBUFS);
			dev_lcp -> lcd_state = READY;
			dev_lcp -> lcd_pkp = pkp;
			pkp -> pk_chan[0] = dev_lcp;
		} else {
			if (dev_lcp)
				pk_close (dev_lcp);
			return (ENOBUFS);
		}
	}
	return 0;
}

E 13
D 3
struct pkcb *
pk_newlink (xcp)
struct x25config *xcp;
{
	register struct pkcb *pkp;
	register struct mbuf *m;
	register struct pklcd *lcp;
	register struct protosw *pp;
	register unsigned size;

	if (xcp -> xc_ntnlen <= 0 || xcp -> xc_ntnlen > sizeof (xcp -> xc_ntn) * 2)
		return ((struct pkcb *)0);
#ifdef BSD4_3
	pp = pffindproto (AF_CCITT, (int)xcp -> xc_lproto, 0);
#else
	pp = pffindproto (AF_CCITT, (int)xcp -> xc_lproto);
#endif
	if (pp == 0 || pp -> pr_output == 0) {
		pk_message (0, xcp, "link level protosw error");
		return ((struct pkcb *)0);
	}

	/*
	 * Allocate a network control block structure
	 */

	size = sizeof (struct pkcb) + xcp->xc_maxlcn * sizeof (struct pklcd *);
#ifdef sun
	if (xcp -> xc_maxlcn < 1 || size > mclbytes) {
#else
	if (xcp -> xc_maxlcn < 1 || size > CLBYTES) {
#endif
		pk_message (0, xcp, "invalid maxlcn");
		return ((struct pkcb *)0);
	}
	m = m_get (M_DONTWAIT, MT_PCB);
	if (m == 0)
		return ((struct pkcb *)0);
	if (size > MLEN) {
#ifdef sun
		if (mclget (m) == 0) {
			m_freem (m);
			return ((struct pkcb *)0);
		}
#else
#ifdef BSD4_3
		MCLGET (m);
		if (m -> m_len != CLBYTES) {
			(void) m_free (m);
			return ((struct pkcb *)0);
		}
#else
		register struct mbuf *p;

		MCLGET (p, 1);
		if (p == 0) {
			m_freem (m);
			return ((struct pkcb *)0);
		}
		m -> m_off = (int)p - (int)m;
#endif
#endif
	}
	pkp = mtod (m, struct pkcb *);
	bzero ((caddr_t)pkp, size);

	/*
	 * Allocate a logical channel descriptor for lcn 0
	 */

	m = m_getclr (M_DONTWAIT, MT_PCB);
	if (m == 0) {
		m_freem (dtom (pkp));
		return ((struct pkcb *)0);
	}
	lcp = mtod (m, struct pklcd *);
	lcp -> lcd_state = READY;
	lcp -> lcd_pkp = pkp;
	pkp -> pk_chan[0] = lcp;

	pkp -> pk_output = pp -> pr_output;
	pkp -> pk_xcp = xcp;
	pkp -> pk_state = DTE_WAITING;
	pkp -> pk_maxlcn = xcp -> xc_maxlcn;
	pkp -> pk_next = pkcbhead;
	pkcbhead = pkp;

	/*
	 * set defaults
	 */

	if (xcp -> xc_pwsize == 0)
		xcp -> xc_pwsize = DEFAULT_WINDOW_SIZE;
	if (xcp -> xc_psize == 0)
		xcp -> xc_psize = X25_PS128;
	return (pkp);
}

E 3
/* 
 *  This procedure is called by the link level whenever the link
 *  becomes operational, is reset, or when the link goes down. 
 */
D 18

D 3
pk_ctlinput (code, xcp)
struct x25config *xcp;
E 3
I 3
D 6
pk_ctlinput (code, pkp)
register struct pkcb *pkp;
E 6
I 6
D 13
pk_ctlinput (code, xcp)
register struct x25config *xcp;
E 13
I 13
pk_ctlinput (code, pkp)
register struct pkcb *pkp;
E 18
I 18
/*VARARGS*/
caddr_t
pk_ctlinput (code, src, addr)
	struct sockaddr *src;
	caddr_t addr;
E 18
E 13
E 6
E 3
{
I 18
D 21
	register struct pkcb *pkp = (struct pkcb *)addr;
E 21
I 21
	register struct pkcb *pkp = (struct pkcb *) addr;
E 21
E 18
D 3
	register struct pkcb *pkp;
E 3

I 6
D 13
	register struct pkcb *pkp;
E 13
D 18

E 18
D 13
	for (pkp = pkcbhead; pkp; pkp = pkp -> pk_next)
		if (pkp -> pk_xcp == xcp)
			break;

E 6
D 3
	for (pkp = pkcbhead; pkp; pkp = pkp -> pk_next)
		if (pkp -> pk_xcp == xcp)
			break;

	if (pkp == 0 && (pkp = pk_newlink (xcp)) == 0)
E 3
I 3
	if (pkp == 0)
E 3
		return (EINVAL);
I 6

E 13
E 6
D 3

E 3
	switch (code) {
	case PRC_LINKUP: 
		if (pkp -> pk_state == DTE_WAITING)
			pk_restart (pkp, X25_RESTART_NETWORK_CONGESTION);
		break;

	case PRC_LINKDOWN: 
		pk_restart (pkp, -1);	/* Clear all active circuits */
		pkp -> pk_state = DTE_WAITING;
		break;

	case PRC_LINKRESET: 
		pk_restart (pkp, X25_RESTART_NETWORK_CONGESTION);
		break;
I 18
		
	case PRC_CONNECT_INDICATION: {
		struct rtentry *llrt;
E 18

I 18
		if ((llrt = rtalloc1(src, 0)) == 0)
			return 0;
D 21
		else llrt->rt_refcnt--;
E 21
I 21
		else llrt -> rt_refcnt--;
E 21
		
D 21
		pkp = (((struct npaidbentry *)llrt->rt_llinfo)->np_rt) ?
			(struct pkcb *)(((struct npaidbentry *)llrt->rt_llinfo)->np_rt->rt_llinfo) : (struct pkcb *) 0;
E 21
I 21
		pkp = (((struct npaidbentry *) llrt -> rt_llinfo) -> np_rt) ?
			(struct pkcb *)(((struct npaidbentry *) llrt -> rt_llinfo) -> np_rt -> rt_llinfo) : (struct pkcb *) 0;
E 21
		if (pkp == (struct pkcb *) 0)
			return 0;
D 21
		pkp->pk_llnext = addr;
E 21
I 21
		pkp -> pk_llnext = addr;
E 21

		return ((caddr_t) pkp);
E 18
	}
I 18
	case PRC_DISCONNECT_INDICATION:
		pk_restart (pkp, -1) ;  /* Clear all active circuits */
D 21
		pkp->pk_state = DTE_WAITING;
		pkp->pk_llnext = (caddr_t) 0;
E 21
I 21
		pkp -> pk_state = DTE_WAITING;
		pkp -> pk_llnext = (caddr_t) 0;
E 21
	}
E 18
	return (0);
}
I 6
struct ifqueue pkintrq;
/*
 * This routine is called if there are semi-smart devices that do HDLC
 * in hardware and want to queue the packet and call level 3 directly
 */
pkintr ()
{
	register struct mbuf *m;
	register struct ifaddr *ifa;
	register struct ifnet *ifp;
	register int s;
E 6

I 6
	for (;;) {
		s = splimp ();
		IF_DEQUEUE (&pkintrq, m);
		splx (s);
		if (m == 0)
			break;
D 21
		if (m->m_len < PKHEADERLN) {
E 21
I 21
		if (m -> m_len < PKHEADERLN) {
E 21
			printf ("pkintr: packet too short (len=%d)\n",
D 21
				m->m_len);
E 21
I 21
				m -> m_len);
E 21
			m_freem (m);
			continue;
		}
D 13
		if ((m->m_flags & M_PKTHDR) == 0)
			panic("pkintr");
		ifp = m->m_pkthdr.rcvif;
		/*
		 * look up the appropriate control block
		 */
		for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
			if (ifa->ifa_addr->sa_family == AF_CCITT)
				break;
		if (ifa == 0)
			continue;
		pk_input(m, ((struct x25_ifaddr *)ifa)->ia_xcp);
E 13
I 13
D 21
		pk_input(m);
E 21
I 21
		pk_input (m);
E 21
E 13
	}
}
struct mbuf *pk_bad_packet;
I 12
struct mbuf_cache pk_input_cache = {0 };
E 12
E 6
/* 
 *  X.25 PACKET INPUT
 *
 *  This procedure is called by a link level procedure whenever
 *  an information frame is received. It decodes the packet and
 *  demultiplexes based on the logical channel number.
 *
I 13
 *  We change the original conventions of the UBC code here --
D 20
 *  since there may be multiple pkcb's for 802.2 class 2
 *  for a given interface, we must be informed which one it is;
 *  so we overwrite the pkthdr.rcvif; it can be recovered if necessary.
 *
E 20
I 20
 *  since there may be multiple pkcb's for a given interface
 *  of type 802.2 class 2, we retrieve which one it is from
 *  m_pkthdr.rcvif (which has been overwritten by lower layers);
 *  That field is then restored for the benefit of upper layers which
 *  may make use of it, such as CLNP.
I 21
 *
E 21
E 20
E 13
 */

I 18
#define RESTART_DTE_ORIGINATED(xp) (((xp) -> packet_cause == X25_RESTART_DTE_ORIGINATED) || \
			    ((xp) -> packet_cause >= X25_RESTART_DTE_ORIGINATED2))

E 18
D 13
pk_input (m, xcp)
E 13
I 13
pk_input (m)
E 13
register struct mbuf *m;
D 13
struct x25config *xcp;
E 13
{
	register struct x25_packet *xp;
	register struct pklcd *lcp;
	register struct socket *so = 0;
	register struct pkcb *pkp;
	int  ptype, lcn, lcdstate = LISTEN;
D 13
	static struct x25config *lastxcp;
	static struct pkcb *lastpkp;
E 13

I 12
	if (pk_input_cache.mbc_size || pk_input_cache.mbc_oldsize)
D 21
		mbuf_cache(&pk_input_cache, m);
E 12
D 13
	if (xcp == lastxcp)
		pkp = lastpkp;
	else {
		for (pkp = pkcbhead; ; pkp = pkp -> pk_next) {
			if (pkp == 0) {
				pk_message (0, xcp, "pk_input: unknown network");
				m_freem (m);
				return;
			}
			if (pkp -> pk_xcp == xcp)
				break;
		}
		lastxcp = xcp;
		lastpkp = pkp;
	}

E 13
I 13
	if ((m->m_flags & M_PKTHDR) == 0)
		panic("pkintr");
E 21
I 21
		mbuf_cache (&pk_input_cache, m);
	if ((m -> m_flags & M_PKTHDR) == 0)
		panic ("pkintr");
E 21
I 18

E 18
D 21
	if ((pkp = (struct pkcb *)m->m_pkthdr.rcvif) == 0)
E 21
I 21
	if ((pkp = (struct pkcb *) m -> m_pkthdr.rcvif) == 0)
E 21
		return;
E 13
	xp = mtod (m, struct x25_packet *);
	ptype = pk_decode (xp);
D 7
	lcn = xp -> logical_channel_number;
E 7
I 7
	lcn = LCN(xp);
E 7
	lcp = pkp -> pk_chan[lcn];

	/* 
	 *  If the DTE is in Restart  state, then it will ignore data, 
	 *  interrupt, call setup and clearing, flow control and reset 
	 *  packets.
	 */
	if (lcn < 0 || lcn > pkp -> pk_maxlcn) {
		pk_message (lcn, pkp -> pk_xcp, "illegal lcn");
		m_freem (m);
		return;
	}

D 8
	pk_trace (pkp -> pk_xcp, xp, "P-In");
E 8
I 8
	pk_trace (pkp -> pk_xcp, m, "P-In");
E 8

	if (pkp -> pk_state != DTE_READY && ptype != RESTART && ptype != RESTART_CONF) {
		m_freem (m);
		return;
	}
	if (lcp) {
		so = lcp -> lcd_so;
		lcdstate = lcp -> lcd_state;
	} else {
		if (ptype == CLEAR) {	/* idle line probe (Datapac specific) */
			/* send response on lcd 0's output queue */
I 13
			lcp = pkp -> pk_chan[0];
E 13
			lcp -> lcd_template = pk_template (lcn, X25_CLEAR_CONFIRM);
			pk_output (lcp);
			m_freem (m);
			return;
		}
		if (ptype != CALL)
			ptype = INVALID_PACKET;
	}

	if (lcn == 0 && ptype != RESTART && ptype != RESTART_CONF) {
D 6
		pk_message (0, pkp -> pk_xcp, "illegal ptype (%s) on lcn 0",
			pk_name[ptype / MAXSTATES]);
		m_freem (m);
E 6
I 6
		pk_message (0, pkp -> pk_xcp, "illegal ptype (%d, %s) on lcn 0",
			ptype, pk_name[ptype / MAXSTATES]);
		if (pk_bad_packet)
			m_freem (pk_bad_packet);
		pk_bad_packet = m;
E 6
		return;
	}
I 20

	m -> m_pkthdr.rcvif = pkp -> pk_ia -> ia_ifp;
E 20

	switch (ptype + lcdstate) {
	/* 
	 *  Incoming Call packet received. 
	 */
	case CALL + LISTEN: 
D 8
		incoming_call (pkp, xp, m -> m_len);
E 8
I 8
D 12
		incoming_call (pkp, m);
E 12
I 12
		pk_incoming_call (pkp, m);
E 12
E 8
		break;

	/* 	
	 *  Call collision: Just throw this "incoming call" away since 
	 *  the DCE will ignore it anyway. 
	 */
	case CALL + SENT_CALL: 
D 7
		pk_message ((int)xp -> logical_channel_number, pkp -> pk_xcp, 
E 7
I 7
D 21
		pk_message ((int)lcn, pkp -> pk_xcp, 
E 21
I 21
		pk_message ((int) lcn, pkp -> pk_xcp, 
E 21
E 7
			"incoming call collision");
		break;

	/* 
	 *  Call confirmation packet received. This usually means our
	 *  previous connect request is now complete.
	 */
	case CALL_ACCEPTED + SENT_CALL: 
D 11
		call_accepted (lcp, xp, m -> m_len);
E 11
I 11
		MCHTYPE(m, MT_CONTROL);
D 12
		call_accepted (lcp, m);
E 12
I 12
		pk_call_accepted (lcp, m);
E 12
E 11
		break;

	/* 
	 *  This condition can only happen if the previous state was
	 *  SENT_CALL. Just ignore the packet, eventually a clear 
	 *  confirmation should arrive.
	 */
	case CALL_ACCEPTED + SENT_CLEAR: 
		break;

	/* 
	 *  Clear packet received. This requires a complete tear down
	 *  of the virtual circuit.  Free buffers and control blocks.
	 *  and send a clear confirmation.
	 */
	case CLEAR + READY:
	case CLEAR + RECEIVED_CALL: 
	case CLEAR + SENT_CALL: 
	case CLEAR + DATA_TRANSFER: 
		lcp -> lcd_state = RECEIVED_CLEAR;
		lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_CLEAR_CONFIRM);
		pk_output (lcp);
		pk_clearcause (pkp, xp);
I 11
		if (lcp -> lcd_upper) {
			MCHTYPE(m, MT_CONTROL);
			lcp -> lcd_upper (lcp, m);
		}
E 11
		pk_close (lcp);
I 11
		lcp = 0;
E 11
		break;

	/* 
	 *  Clear collision: Treat this clear packet as a confirmation.
	 */
	case CLEAR + SENT_CLEAR: 
		pk_close (lcp);
		break;

	/* 
	 *  Clear confirmation received. This usually means the virtual
	 *  circuit is now completely removed.
	 */
	case CLEAR_CONF + SENT_CLEAR: 
		pk_close (lcp);
		break;

	/* 
	 *  A clear confirmation on an unassigned logical channel - just
	 *  ignore it. Note: All other packets on an unassigned channel
	 *  results in a clear.
	 */
	case CLEAR_CONF + READY:
I 13
	case CLEAR_CONF + LISTEN:
E 13
		break;

	/* 
	 *  Data packet received. Pass on to next level. Move the Q and M
	 *  bits into the data portion for the next level.
	 */
	case DATA + DATA_TRANSFER: 
		if (lcp -> lcd_reset_condition) {
			ptype = DELETE_PACKET;
			break;
		}

		/* 
		 *  Process the P(S) flow control information in this Data packet. 
		 *  Check that the packets arrive in the correct sequence and that 
		 *  they are within the "lcd_input_window". Input window rotation is 
		 *  initiated by the receive interface.
		 */

		if (PS(xp) != ((lcp -> lcd_rsn + 1) % MODULUS) ||
D 21
			PS(xp) == ((lcp -> lcd_input_window + lcp->lcd_windowsize) % MODULUS)) {
E 21
I 21
			PS(xp) == ((lcp -> lcd_input_window + lcp -> lcd_windowsize) % MODULUS)) {
E 21
			m_freem (m);
D 8
			pk_procerror (RESET, lcp, "p(s) flow control error");
E 8
I 8
			pk_procerror (RESET, lcp, "p(s) flow control error", 1);
E 8
			break;
		}
		lcp -> lcd_rsn = PS(xp);

		if (pk_ack (lcp, PR(xp)) != PACKET_OK) {
			m_freem (m);
			break;
		}
D 6

E 6
I 6
D 8
		if (so == 0)
			break;
E 8
E 6
D 4
		m -> m_off += PKHEADERLN;
E 4
I 4
		m -> m_data += PKHEADERLN;
E 4
		m -> m_len -= PKHEADERLN;
I 8
		m -> m_pkthdr.len -= PKHEADERLN;

I 13
		lcp -> lcd_rxcnt++;
E 13
		if (lcp -> lcd_flags & X25_MBS_HOLD) {
			register struct mbuf *n = lcp -> lcd_cps;
			int mbit = MBIT(xp);
			octet q_and_d_bits;

			if (n) {
				n -> m_pkthdr.len += m -> m_pkthdr.len;
				while (n -> m_next)
					n = n -> m_next;
				n -> m_next = m;
				m = lcp -> lcd_cps;

				if (lcp -> lcd_cpsmax &&
				    n -> m_pkthdr.len > lcp -> lcd_cpsmax) {
					pk_procerror (RESET, lcp,
						"C.P.S. overflow", 128);
					return;
				}
D 21
				q_and_d_bits = 0xc0 & *(octet *)xp;
E 21
I 21
				q_and_d_bits = 0xc0 & *(octet *) xp;
E 21
				xp = (struct x25_packet *)
D 21
					(mtod(m, octet *) - PKHEADERLN);
				*(octet *)xp |= q_and_d_bits;
E 21
I 21
					(mtod (m, octet *) - PKHEADERLN);
				*(octet *) xp |= q_and_d_bits;
E 21
			}
			if (mbit) {
				lcp -> lcd_cps = m;
I 9
D 13
				lcp -> lcd_rxcnt++;
E 13
D 21
				pk_flowcontrol(lcp, 0, 1);
E 21
I 21
				pk_flowcontrol (lcp, 0, 1);
E 21
E 9
				return;
			}
			lcp -> lcd_cps = 0;
		}
		if (so == 0)
			break;
E 8
		if (lcp -> lcd_flags & X25_MQBIT) {
D 7
			octet *t;
E 7
I 7
D 18
			octet t = (xp -> q_bit) ? t = 0x80 : 0;
E 18
I 18
			octet t = (X25GBITS(xp -> bits, q_bit)) ? t = 0x80 : 0;
E 18
E 7

I 7
			if (MBIT(xp))
				t |= 0x40;
E 7
D 4
			m -> m_off -= 1;
E 4
I 4
			m -> m_data -= 1;
E 4
			m -> m_len += 1;
I 8
			m -> m_pkthdr.len += 1;
E 8
D 7
			t = mtod (m, octet *);
			*t = 0x00;
			if (xp -> q_bit)
				*t |= 0x80;
			if (MBIT(xp))
				*t |= 0x40;
E 7
I 7
D 21
			*mtod(m, octet *) = t;
E 21
I 21
			*mtod (m, octet *) = t;
E 21
E 7
		}

		/*
		 * Discard Q-BIT packets if the application
		 * doesn't want to be informed of M and Q bit status
		 */
D 18
		if (xp -> q_bit && (lcp -> lcd_flags & X25_MQBIT) == 0) {
E 18
I 18
		if (X25GBITS(xp -> bits, q_bit) 
		    && (lcp -> lcd_flags & X25_MQBIT) == 0) {
E 18
			m_freem (m);
D 13
			lcp -> lcd_rxcnt++;
E 13
			/*
			 * NB.  This is dangerous: sending a RR here can
			 * cause sequence number errors if a previous data
			 * packet has not yet been passed up to the application
			 * (RR's are normally generated via PRU_RCVD).
			 */
D 9
			lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_RR);
			pk_output (lcp);
E 9
I 9
D 21
			pk_flowcontrol(lcp, 0, 1);
E 21
I 21
			pk_flowcontrol (lcp, 0, 1);
E 21
E 9
		} else {
D 7
#ifdef BSD4_3
E 7
			sbappendrecord (&so -> so_rcv, m);
D 7
#else
			sbappend (&so -> so_rcv, m);
#endif
E 7
			sorwakeup (so);
		}
		break;

	/* 
	 *  Interrupt packet received.
	 */
	case INTERRUPT + DATA_TRANSFER: 
		if (lcp -> lcd_reset_condition)
			break;
		lcp -> lcd_intrdata = xp -> packet_data;
D 6
		sohasoutofband (so);
E 6
		lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_INTERRUPT_CONFIRM);
		pk_output (lcp);
I 8
		m -> m_data += PKHEADERLN;
		m -> m_len -= PKHEADERLN;
		m -> m_pkthdr.len -= PKHEADERLN;
E 8
I 6
		MCHTYPE(m, MT_OOBDATA);
D 8
		if (so)
E 8
I 8
		if (so) {
			if (so -> so_options & SO_OOBINLINE)
				sbinsertoob (&so -> so_rcv, m);
			else
				m_freem (m);
E 8
			sohasoutofband (so);
I 8
		}
E 8
E 6
		break;

	/* 
	 *  Interrupt confirmation packet received.
	 */
	case INTERRUPT_CONF + DATA_TRANSFER: 
		if (lcp -> lcd_reset_condition)
			break;
		if (lcp -> lcd_intrconf_pending == TRUE)
			lcp -> lcd_intrconf_pending = FALSE;
		else
D 8
			pk_procerror (RESET, lcp, "unexpected packet");
I 6
		MCHTYPE(m, MT_CONTROL);
E 8
I 8
			pk_procerror (RESET, lcp, "unexpected packet", 43);
E 8
E 6
		break;

	/* 
	 *  Receiver ready received. Rotate the output window and output
	 *  any data packets waiting transmission.
	 */
	case RR + DATA_TRANSFER: 
D 6
		if (lcp -> lcd_reset_condition)
E 6
I 6
		if (lcp -> lcd_reset_condition ||
		    pk_ack (lcp, PR(xp)) != PACKET_OK) {
			ptype = DELETE_PACKET;
E 6
			break;
D 6
		if (pk_ack (lcp, PR(xp)) != PACKET_OK)
			break;
E 6
I 6
		}
E 6
		if (lcp -> lcd_rnr_condition == TRUE)
			lcp -> lcd_rnr_condition = FALSE;
		pk_output (lcp);
I 6
D 8
		MCHTYPE(m, MT_CONTROL);
E 8
E 6
		break;

	/* 
	 *  Receiver Not Ready received. Packets up to the P(R) can be
	 *  be sent. Condition is cleared with a RR.
	 */
	case RNR + DATA_TRANSFER: 
D 6
		if (lcp -> lcd_reset_condition)
E 6
I 6
		if (lcp -> lcd_reset_condition ||
		    pk_ack (lcp, PR(xp)) != PACKET_OK) {
			ptype = DELETE_PACKET;
E 6
			break;
D 6
		if (pk_ack (lcp, PR(xp)) != PACKET_OK)
			break;
E 6
I 6
		}
E 6
		lcp -> lcd_rnr_condition = TRUE;
I 6
D 8
		MCHTYPE(m, MT_CONTROL);
E 8
E 6
		break;

	/* 
	 *  Reset packet received. Set state to FLOW_OPEN.  The Input and
	 *  Output window edges ar set to zero. Both the send and receive
	 *  numbers are reset. A confirmation is returned.
	 */
	case RESET + DATA_TRANSFER: 
		if (lcp -> lcd_reset_condition)
			/* Reset collision. Just ignore packet. */
			break;

		pk_resetcause (pkp, xp);
D 6
		sbflush (&so -> so_snd);
		sbflush (&so -> so_rcv);

		wakeup ((caddr_t) & so -> so_timeo);
		sorwakeup (so);
		sowwakeup (so);

E 6
		lcp -> lcd_window_condition = lcp -> lcd_rnr_condition =
			lcp -> lcd_intrconf_pending = FALSE;
		lcp -> lcd_output_window = lcp -> lcd_input_window =
			lcp -> lcd_last_transmitted_pr = 0;
		lcp -> lcd_ssn = 0;
		lcp -> lcd_rsn = MODULUS - 1;

		lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_RESET_CONFIRM);
		pk_output (lcp);
I 6

D 8
		MCHTYPE(m, MT_CONTROL);
E 8
I 8
D 21
		pk_flush(lcp);
E 21
I 21
		pk_flush (lcp);
E 21
E 8
		if (so == 0)
			break;
D 8
		sbflush (&so -> so_snd);
		sbflush (&so -> so_rcv);
E 8
		wakeup ((caddr_t) & so -> so_timeo);
		sorwakeup (so);
		sowwakeup (so);
E 6
		break;

	/* 
	 *  Reset confirmation received.
	 */
	case RESET_CONF + DATA_TRANSFER: 
		if (lcp -> lcd_reset_condition) {
			lcp -> lcd_reset_condition = FALSE;
			pk_output (lcp);
		}
		else
D 8
			pk_procerror (RESET, lcp, "unexpected packet");
I 6
		MCHTYPE(m, MT_CONTROL);
E 8
I 8
			pk_procerror (RESET, lcp, "unexpected packet", 32);
E 8
E 6
		break;

	case DATA + SENT_CLEAR: 
		ptype = DELETE_PACKET;
	case RR + SENT_CLEAR: 
	case RNR + SENT_CLEAR: 
	case INTERRUPT + SENT_CLEAR: 
	case INTERRUPT_CONF + SENT_CLEAR: 
	case RESET + SENT_CLEAR: 
	case RESET_CONF + SENT_CLEAR: 
D 6
		/* Just ignore packet if we have sent a CLEAR already.
E 6
I 6
		/* Just ignore p if we have sent a CLEAR already.
E 6
		   */
		break;

	/* 
	 *  Restart sets all the permanent virtual circuits to the "Data
	 *  Transfer" stae and  all the switched virtual circuits to the
	 *  "Ready" state.
	 */
	case RESTART + READY: 
		switch (pkp -> pk_state) {
		case DTE_SENT_RESTART: 
D 18
			/* Restart collision. */
E 18
I 18
			/* 
			 * Restart collision.
			 * If case the restart cause is "DTE originated" we
			 * have a DTE-DTE situation and are trying to resolve
			 * who is going to play DTE/DCE [ISO 8208:4.2-4.5]
			 */
			if (RESTART_DTE_ORIGINATED(xp)) {
				pk_restart (pkp, X25_RESTART_DTE_ORIGINATED);
				pk_message (0, pkp -> pk_xcp,
					    "RESTART collision");
				if ((pkp -> pk_restartcolls++) > MAXRESTARTCOLLISIONS) {
					pk_message (0, pkp -> pk_xcp,
						    "excessive RESTART collisions");
					pkp -> pk_restartcolls = 0;
				}
				break;
			}
E 18
			pkp -> pk_state = DTE_READY;
I 18
			pkp -> pk_dxerole |= DTE_PLAYDTE;
			pkp -> pk_dxerole &= ~DTE_PLAYDCE;
E 18
			pk_message (0, pkp -> pk_xcp,
				"Packet level operational");
I 18
			pk_message (0, pkp -> pk_xcp, 
				    "Assuming DTE role");
			if (pkp -> pk_dxerole & DTE_CONNECTPENDING)
D 21
				pk_callcomplete(pkp);
E 21
I 21
				pk_callcomplete (pkp);
E 21
E 18
			break;

		default: 
			pk_restart (pkp, -1);
			pk_restartcause (pkp, xp);
			pkp -> pk_chan[0] -> lcd_template = pk_template (0,
				X25_RESTART_CONFIRM);
			pk_output (pkp -> pk_chan[0]);
I 18
			pkp -> pk_state = DTE_READY;
			pkp -> pk_dxerole |= RESTART_DTE_ORIGINATED(xp) ? DTE_PLAYDCE :
				DTE_PLAYDTE;
			if (pkp -> pk_dxerole & DTE_PLAYDTE) {
				pkp -> pk_dxerole &= ~DTE_PLAYDCE;
				pk_message (0, pkp -> pk_xcp, 
					    "Assuming DTE role");
			} else {
				pkp -> pk_dxerole &= ~DTE_PLAYDTE;
				pk_message (0, pkp -> pk_xcp, 
					 "Assuming DCE role");
			}
			if (pkp -> pk_dxerole & DTE_CONNECTPENDING)
D 21
				pk_callcomplete(pkp);
E 21
I 21
				pk_callcomplete (pkp);
E 21
E 18
		}
		break;

	/* 
	 *  Restart confirmation received. All logical channels are set
	 *  to READY. 
	 */
	case RESTART_CONF + READY: 
		switch (pkp -> pk_state) {
		case DTE_SENT_RESTART: 
			pkp -> pk_state = DTE_READY;
I 18
			pkp -> pk_dxerole |= DTE_PLAYDTE;
			pkp -> pk_dxerole &= ~DTE_PLAYDCE;
E 18
			pk_message (0, pkp -> pk_xcp,
D 18
				"Packet level operational");
E 18
I 18
				    "Packet level operational");
D 21
			pk_message (0, pkp-> pk_xcp,
E 21
I 21
			pk_message (0, pkp -> pk_xcp,
E 21
				    "Assuming DTE role");
			if (pkp -> pk_dxerole & DTE_CONNECTPENDING)
D 21
				pk_callcomplete(pkp);
E 21
I 21
				pk_callcomplete (pkp);
E 21
E 18
			break;

		default: 
			/* Restart local procedure error. */
			pk_restart (pkp, X25_RESTART_LOCAL_PROCEDURE_ERROR);
			pkp -> pk_state = DTE_SENT_RESTART;
I 18
			pkp -> pk_dxerole &= ~(DTE_PLAYDTE | DTE_PLAYDCE);
E 18
		}
		break;

	default: 
		if (lcp) {
D 8
			pk_procerror (CLEAR, lcp, "unknown packet error");
E 8
I 8
			pk_procerror (CLEAR, lcp, "unknown packet error", 33);
E 8
			pk_message (lcn, pkp -> pk_xcp,
				"\"%s\" unexpected in \"%s\" state",
				pk_name[ptype/MAXSTATES], pk_state[lcdstate]);
D 8
		}
		else	/* Packets arrived on an unassigned channel. 
			*/
E 8
I 8
		} else
E 8
D 7
			pk_message ((int)xp->logical_channel_number, pkp -> pk_xcp,
E 7
I 7
			pk_message (lcn, pkp -> pk_xcp,
E 7
				"packet arrived on unassigned lcn");
		break;
	}
D 6
	if (ptype != DATA)
E 6
I 6
D 8
	if (so == 0 && lcdstate == DATA_TRANSFER && lcp -> lcd_upper)
E 8
I 8
D 9
	if (so == 0 && lcp -> lcd_upper &&
E 9
I 9
D 11
	if (so == 0 && lcp && lcp -> lcd_upper &&
E 9
	    (lcdstate == SENT_CALL || lcdstate == DATA_TRANSFER)) {
E 11
I 11
	if (so == 0 && lcp && lcp -> lcd_upper && lcdstate == DATA_TRANSFER) {
E 11
		if (ptype != DATA && ptype != INTERRUPT)
			MCHTYPE(m, MT_CONTROL);
E 8
		lcp -> lcd_upper (lcp, m);
D 8
	else if (ptype != DATA)
E 8
I 8
	} else if (ptype != DATA && ptype != INTERRUPT)
E 8
E 6
		m_freem (m);
}

I 13
static
D 21
prune_dnic(from, to, dnicname, xcp)
E 21
I 21
prune_dnic (from, to, dnicname, xcp)
E 21
char *from, *to, *dnicname;
register struct x25config *xcp;
{
	register char *cp1 = from, *cp2 = from;
D 21
	if (xcp->xc_prepnd0 && *cp1 == '0') {
E 21
I 21
	if (xcp -> xc_prepnd0 && *cp1 == '0') {
E 21
		from = ++cp1;
		goto copyrest;
	}
D 21
	if (xcp->xc_nodnic) {
E 21
I 21
	if (xcp -> xc_nodnic) {
E 21
		for (cp1 = dnicname; *cp2 = *cp1++;)
			cp2++;
		cp1 = from;
	}
copyrest:
	for (cp1 = dnicname; *cp2 = *cp1++;)
		cp2++;
}
/* static */
pk_simple_bsd (from, to, lower, len)
register octet *from, *to;
register len, lower;
{
	register int c;
	while (--len >= 0) {
		c = *from;
		if (lower & 0x01)
			*from++;
		else
			c >>= 4;
		c &= 0x0f; c |= 0x30; *to++ = c; lower++;
	}
	*to = 0;
}
E 13

I 13
/*static octet * */
pk_from_bcd (a, iscalling, sa, xcp)
register struct x25_calladdr *a;
register struct sockaddr_x25 *sa;
register struct x25config *xcp;
{
	octet buf[MAXADDRLN+1];
	octet *cp;
	unsigned count;

D 21
	bzero ((caddr_t)sa, sizeof (*sa));
E 21
I 21
	bzero ((caddr_t) sa, sizeof (*sa));
E 21
	sa -> x25_len = sizeof (*sa);
	sa -> x25_family = AF_CCITT;
	if (iscalling) {
D 18
		cp = a -> address_field + (a -> called_addrlen / 2);
		count = a -> calling_addrlen;
		pk_simple_bsd (cp, buf, a -> called_addrlen, count);
E 18
I 18
		cp = a -> address_field + (X25GBITS(a -> addrlens, called_addrlen) / 2);
		count = X25GBITS(a -> addrlens, calling_addrlen);
		pk_simple_bsd (cp, buf, X25GBITS(a -> addrlens, called_addrlen), count);
E 18
	} else {
D 18
		count = a -> called_addrlen;
E 18
I 18
		count = X25GBITS(a -> addrlens, called_addrlen);
E 18
		pk_simple_bsd (a -> address_field, buf, 0, count);
	}
D 21
	if (xcp -> xc_addr.x25_net && (xcp -> xc_nodnic || xcp ->xc_prepnd0)) {
		octet dnicname[sizeof(long) * NBBY/3 + 2];
E 21
I 21
	if (xcp -> xc_addr.x25_net && (xcp -> xc_nodnic || xcp -> xc_prepnd0)) {
		octet dnicname[sizeof (long) * NBBY/3 + 2];
E 21

D 16
		sprintf (dnicname, "%d", xcp -> xc_addr.x25_net);
E 16
I 16
D 18
		sprintf ((char *)dnicname, "%d", xcp -> xc_addr.x25_net);
E 16
		prune_dnic (buf, sa -> x25_addr, dnicname, xcp);
E 18
I 18
		sprintf ((char *) dnicname, "%d", xcp -> xc_addr.x25_net);
D 21
		prune_dnic ((char *)buf, sa -> x25_addr, dnicname, xcp);
E 21
I 21
		prune_dnic ((char *) buf, sa -> x25_addr, dnicname, xcp);
E 21
E 18
	} else
D 21
		bcopy ((caddr_t)buf, (caddr_t)sa -> x25_addr, count + 1);
E 21
I 21
		bcopy ((caddr_t) buf, (caddr_t) sa -> x25_addr, count + 1);
E 21
}

static
D 21
save_extra(m0, fp, so)
E 21
I 21
save_extra (m0, fp, so)
E 21
struct mbuf *m0;
octet *fp;
struct socket *so;
{
	register struct mbuf *m;
	struct cmsghdr cmsghdr;
D 16
	if (m = m_copym (m, 0, (int)M_COPYALL)) {
E 16
I 16
	if (m = m_copy (m, 0, (int)M_COPYALL)) {
E 16
		int off = fp - mtod (m0, octet *);
D 21
		int len = m->m_pkthdr.len - off + sizeof (cmsghdr);
E 21
I 21
		int len = m -> m_pkthdr.len - off + sizeof (cmsghdr);
E 21
		cmsghdr.cmsg_len = len;
		cmsghdr.cmsg_level = AF_CCITT;
		cmsghdr.cmsg_type = PK_FACILITIES;
		m_adj (m, off);
D 21
		M_PREPEND (m, sizeof(cmsghdr), M_DONTWAIT);
E 21
I 21
		M_PREPEND (m, sizeof (cmsghdr), M_DONTWAIT);
E 21
		if (m == 0)
			return;
		bcopy ((caddr_t)&cmsghdr, mtod (m, caddr_t), sizeof (cmsghdr));
		MCHTYPE(m, MT_CONTROL);
D 21
		sbappendrecord(&so -> so_rcv, m);
E 21
I 21
		sbappendrecord (&so -> so_rcv, m);
E 21
	}
}

E 13
/* 
 * This routine handles incoming call packets. It matches the protocol
 * field on the Call User Data field (usually the first four bytes) with 
 * sockets awaiting connections.
 */

D 12
static
D 8
incoming_call (pkp, xp, len)
E 8
I 8
incoming_call (pkp, m0)
E 12
I 12
pk_incoming_call (pkp, m0)
E 12
struct mbuf *m0;
E 8
struct pkcb *pkp;
D 8
struct x25_packet *xp;
E 8
{
D 3
	register struct pklcd *lcp, *l;
E 3
I 3
	register struct pklcd *lcp = 0, *l;
E 3
	register struct sockaddr_x25 *sa;
	register struct x25_calladdr *a;
D 3
	register struct socket *so;
E 3
I 3
	register struct socket *so = 0;
I 8
D 13
	struct x25_packet *xp = mtod(m0, struct x25_packet *);
E 8
E 3
	struct mbuf *m;
E 13
I 13
D 21
	struct	x25_packet *xp = mtod(m0, struct x25_packet *);
E 21
I 21
	struct	x25_packet *xp = mtod (m0, struct x25_packet *);
E 21
	struct	mbuf *m;
	struct	x25config *xcp = pkp -> pk_xcp;
E 13
I 8
D 21
	int len = m0->m_pkthdr.len;
E 21
I 21
	int len = m0 -> m_pkthdr.len;
E 21
E 8
D 13
	register int l1, l2;
	char *e, *errstr = "server unavailable";
E 13
I 13
	unsigned udlen;
	char *errstr = "server unavailable";
E 13
D 8
	octet *u;
E 8
I 8
	octet *u, *facp;
E 8
D 7
	int lcn = xp -> logical_channel_number;
E 7
I 7
	int lcn = LCN(xp);
E 7

D 13
	/* First, copy the data from the incoming call packet to a X25_socket
	   descriptor. */

	a = (struct x25_calladdr *) &xp -> packet_data;
	l1 = a -> calling_addrlen;
	l2 = a -> called_addrlen;
D 6
	if ((m = m_getclr (M_DONTWAIT, MT_HEADER)) == 0)
E 6
I 6
	if ((m = m_getclr (M_DONTWAIT, MT_SONAME)) == 0)
E 13
I 13
	/* First, copy the data from the incoming call packet to a X25 address
	   descriptor. It is to be regretted that you have
	   to parse the facilities into a sockaddr to determine
	   if reverse charging is being requested */
	if ((m = m_get (M_DONTWAIT, MT_SONAME)) == 0)
E 13
E 6
		return;
	sa = mtod (m, struct sockaddr_x25 *);
D 13
	u = (octet *) (a -> address_field + l2 / 2);
	e = sa -> x25_addr;
	if (l2 & 0x01) {
		*e++ = *u++ & 0x0f;
		l1--;
	}
	from_bcd (e, &u, l1);
	if (l1 & 0x01)
		u++;

I 8
	facp = u;
E 8
D 12
	parse_facilities (u, sa);
E 12
I 12
	pk_parse_facilities (u, sa);
E 13
I 13
	a = (struct x25_calladdr *) &xp -> packet_data;
	facp = u = (octet *) (a -> address_field +
D 18
		((a -> called_addrlen + a -> calling_addrlen + 1) / 2));
E 18
I 18
		((X25GBITS(a -> addrlens, called_addrlen) + X25GBITS(a -> addrlens, calling_addrlen) + 1) / 2));
E 18
E 13
E 12
	u += *u + 1;
D 13
	sa -> x25_udlen = min (16, ((octet *)xp) + len - u);
	if (sa -> x25_udlen < 0)
		sa -> x25_udlen = 0;
	bcopy ((caddr_t)u, sa -> x25_udata, (unsigned)sa -> x25_udlen);
E 13
I 13
D 21
	udlen = min (16, ((octet *)xp) + len - u);
E 21
I 21
	udlen = min (16, ((octet *) xp) + len - u);
E 21
	if (udlen < 0)
		udlen = 0;
	pk_from_bcd (a, 1, sa, pkp -> pk_xcp); /* get calling address */
D 15
	pk_parse_facilities (u, sa);
E 15
I 15
	pk_parse_facilities (facp, sa);
E 15
D 21
	bcopy ((caddr_t)u, sa -> x25_udata, udlen);
E 21
I 21
	bcopy ((caddr_t) u, sa -> x25_udata, udlen);
E 21
	sa -> x25_udlen = udlen;
E 13

	/*
D 15
	 * Now, loop through the  listen sockets looking for a match on the
	 * PID. That is  the first  four octets  of the user data field.  This
	 * is the closest thing to a port number for X.25 packets. What it
	 * does provide is away of  multiplexing  services at the user level. 
E 15
I 15
	 * Now, loop through the listen sockets looking for a match on the
	 * PID. That is the first few octets of the user data field.
	 * This is the closest thing to a port number for X.25 packets.
	 * It does provide a way of multiplexing services at the user level. 
E 15
	 */

	for (l = pk_listenhead; l; l = l -> lcd_listen) {
		struct sockaddr_x25 *sxp = l -> lcd_ceaddr;

D 13
		if (bcmp (sxp -> x25_udata, sa -> x25_udata, sxp->x25_udlen))
E 13
I 13
D 21
		if (bcmp (sxp -> x25_udata, u, sxp->x25_udlen))
E 21
I 21
		if (bcmp (sxp -> x25_udata, u, sxp -> x25_udlen))
E 21
E 13
			continue;
D 5
		if (sxp -> x25_net && sxp -> x25_net != pkp->pk_xcp->xc_net)
E 5
I 5
		if (sxp -> x25_net &&
D 13
		    sxp -> x25_net != pkp->pk_xc.xc_addr.x25_net)
E 13
I 13
		    sxp -> x25_net != xcp -> xc_addr.x25_net)
E 13
E 5
			continue;
		/*
I 13
		 * don't accept incoming calls with the D-Bit on
		 * unless the server agrees
		 */
D 18
		if (xp -> d_bit && !(sxp -> x25_opts.op_flags & X25_DBIT)) {
E 18
I 18
		if (X25GBITS(xp -> bits, d_bit) && !(sxp -> x25_opts.op_flags & X25_DBIT)) {
E 18
			errstr = "incoming D-Bit mismatch";
			break;
		}
		/*
E 13
		 * don't accept incoming collect calls unless
		 * the server sets the reverse charging option.
		 */
		if ((sxp -> x25_opts.op_flags & (X25_OLDSOCKADDR|X25_REVERSE_CHARGE)) == 0 &&
			sa -> x25_opts.op_flags & X25_REVERSE_CHARGE) {
			errstr = "incoming collect call refused";
			break;
		}
I 7
D 13
		/*
		 * don't accept incoming calls with the D-Bit on
		 * unless the server agrees
		 */
		if (xp -> d_bit && !(sxp -> x25_opts.op_flags & X25_DBIT)) {
			errstr = "incoming D-Bit mismatch";
			break;
		}
E 13
E 7
D 3
		so = sonewconn (l -> lcd_so);
		if (so == NULL) {
E 3
I 3
		if (l -> lcd_so) {
D 5
			if (so = sonewconn (l -> lcd_so, SO_ISCONNETED))
E 5
I 5
			if (so = sonewconn (l -> lcd_so, SS_ISCONNECTED))
E 5
				    lcp = (struct pklcd *) so -> so_pcb;
		} else 
D 21
			lcp = pk_attach((struct socket *) 0);
E 21
I 21
			lcp = pk_attach ((struct socket *) 0);
E 21
		if (lcp == 0) {
E 3
			/*
			 * Insufficient space or too many unaccepted
			 * connections.  Just throw the call away.
			 */
			errstr = "server malfunction";
			break;
		}
D 3
		lcp = (struct pklcd *) so -> so_pcb;
E 3
I 3
D 4
		lcp -> lcd_upq.pq_put = lcp -> lcd_upq.pq_put;
E 4
I 4
		lcp -> lcd_upper = l -> lcd_upper;
		lcp -> lcd_upnext = l -> lcd_upnext;
E 4
E 3
		lcp -> lcd_lcn = lcn;
		lcp -> lcd_state = RECEIVED_CALL;
D 13
		lcp -> lcd_craddr = sa;
E 13
D 14
		sa -> x25_opts.op_flags |= sxp -> x25_opts.op_flags &
			~X25_REVERSE_CHARGE;
E 14
I 14
		sa -> x25_opts.op_flags |= (sxp -> x25_opts.op_flags &
			~X25_REVERSE_CHARGE) | l -> lcd_flags;
E 14
		pk_assoc (pkp, lcp, sa);
I 13
		lcp -> lcd_faddr = *sa;
		lcp -> lcd_laddr.x25_udlen = sxp -> x25_udlen;
D 21
		lcp -> lcd_craddr = &lcp->lcd_faddr;
E 21
I 21
		lcp -> lcd_craddr = &lcp -> lcd_faddr;
E 21
E 13
		lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_CALL_ACCEPTED);
I 7
		if (lcp -> lcd_flags & X25_DBIT) {
D 18
			if (xp -> d_bit)
D 8
				lcp -> lcd_template -> d_bit = 1;
E 8
I 8
				mtod(lcp -> lcd_template,
					struct x25_packet *) -> d_bit = 1;
E 18
I 18
			if (X25GBITS(xp -> bits, d_bit))
D 21
				X25SBITS(mtod(lcp -> lcd_template,
E 21
I 21
				X25SBITS(mtod (lcp -> lcd_template,
E 21
					struct x25_packet *) -> bits, d_bit, 1);
E 18
E 8
			else
				lcp -> lcd_flags &= ~X25_DBIT;
		}
E 7
D 4
		pk_output (lcp);
D 3
		soisconnected (so);
E 3
I 3
		if (so)
E 4
I 4
		if (so) {
			pk_output (lcp);
E 4
			soisconnected (so);
I 4
D 8
		} else if (lcp->lcd_upper)
D 6
			(*lcp->lcd_upper)(lcp);
E 6
I 6
			(*lcp->lcd_upper)(lcp, m);
E 8
I 8
			if (so -> so_options & SO_OOBINLINE)
D 21
				save_extra(m0, facp, so);
E 21
I 21
				save_extra (m0, facp, so);
E 21
		} else if (lcp -> lcd_upper) {
D 13
			m -> m_next = m0;
			(*lcp -> lcd_upper) (lcp, m);
			(void) m_free (m);  /* only m; m0 freed by caller */
E 13
I 13
			(*lcp -> lcd_upper) (lcp, m0);
E 13
		}
I 13
		(void) m_free (m);
E 13
E 8
E 6
E 4
E 3
		return;
	}

	/*
	 * If the call fails for whatever reason, we still need to build a
	 * skeleton LCD in order to be able to properly  receive the CLEAR
	 * CONFIRMATION.
	 */
#ifdef WATERLOO		/* be explicit */
D 21
	if (l == 0 && bcmp(sa->x25_udata, "ean", 3) == 0)
E 21
I 21
	if (l == 0 && bcmp (sa -> x25_udata, "ean", 3) == 0)
E 21
		pk_message (lcn, pkp -> pk_xcp, "host=%s ean%c: %s",
D 21
			sa->x25_addr, sa->x25_udata[3] & 0xff, errstr);
	else if (l == 0 && bcmp(sa->x25_udata, "\1\0\0\0", 4) == 0)
E 21
I 21
			sa -> x25_addr, sa -> x25_udata[3] & 0xff, errstr);
	else if (l == 0 && bcmp (sa -> x25_udata, "\1\0\0\0", 4) == 0)
E 21
		pk_message (lcn, pkp -> pk_xcp, "host=%s x29d: %s",
D 21
			sa->x25_addr, errstr);
E 21
I 21
			sa -> x25_addr, errstr);
E 21
	else
#endif
	pk_message (lcn, pkp -> pk_xcp, "host=%s pid=%x %x %x %x: %s",
		sa -> x25_addr, sa -> x25_udata[0] & 0xff,
		sa -> x25_udata[1] & 0xff, sa -> x25_udata[2] & 0xff,
		sa -> x25_udata[3] & 0xff, errstr);
D 6
	if ((m = m_getclr (M_DONTWAIT, MT_HEADER)) == 0) {
		(void) m_free (dtom (sa));
E 6
I 6
D 21
	if ((lcp = pk_attach((struct socket *)0)) == 0) {
E 21
I 21
	if ((lcp = pk_attach ((struct socket *)0)) == 0) {
E 21
		(void) m_free (m);
E 6
		return;
	}
D 6
	lcp = mtod (m, struct pklcd *);
E 6
	lcp -> lcd_lcn = lcn;
	lcp -> lcd_state = RECEIVED_CALL;
	pk_assoc (pkp, lcp, sa);
D 6
	(void) m_free (dtom (sa));
E 6
I 6
	(void) m_free (m);
E 6
D 8
	pk_clear (lcp);
E 8
I 8
	pk_clear (lcp, 0, 1);
}

D 13
static
save_extra(m0, fp, so)
struct mbuf *m0;
octet *fp;
struct socket *so;
{
	register struct mbuf *m;
	struct cmsghdr cmsghdr;
	if (m = m_copym (m, 0, (int)M_COPYALL)) {
		int off = fp - mtod (m0, octet *);
		int len = m->m_pkthdr.len - off + sizeof (cmsghdr);
		cmsghdr.cmsg_len = len;
		cmsghdr.cmsg_level = AF_CCITT;
		cmsghdr.cmsg_type = PK_FACILITIES;
		m_adj (m, off);
		M_PREPEND (m, sizeof(cmsghdr), M_DONTWAIT);
		if (m == 0)
			return;
		bcopy ((caddr_t)&cmsghdr, mtod (m, caddr_t), sizeof (cmsghdr));
		MCHTYPE(m, MT_CONTROL);
		sbappendrecord(&so -> so_rcv, m);
	}
E 8
}

E 13
D 12
static
D 11
call_accepted (lcp, xp, len)
E 11
I 11
call_accepted (lcp, m)
E 12
I 12
pk_call_accepted (lcp, m)
E 12
E 11
struct pklcd *lcp;
D 11
struct x25_packet *xp;
E 11
I 11
struct mbuf *m;
E 11
{
	register struct x25_calladdr *ap;
	register octet *fcp;
I 11
	struct x25_packet *xp = mtod (m, struct x25_packet *);
	int len = m -> m_len;
E 11

	lcp -> lcd_state = DATA_TRANSFER;
D 6
	soisconnected (lcp -> lcd_so);
E 6
I 6
	if (lcp -> lcd_so)
		soisconnected (lcp -> lcd_so);
I 7
D 18
	if ((lcp -> lcd_flags & X25_DBIT) && (xp -> d_bit == 0))
E 18
I 18
	if ((lcp -> lcd_flags & X25_DBIT) && (X25GBITS(xp -> bits, d_bit) == 0))
E 18
		lcp -> lcd_flags &= ~X25_DBIT;
E 7
E 6
	if (len > 3) {
		ap = (struct x25_calladdr *) &xp -> packet_data;
D 18
		fcp = (octet *) ap -> address_field + (ap -> calling_addrlen +
			ap -> called_addrlen + 1) / 2;
E 18
I 18
		fcp = (octet *) ap -> address_field + (X25GBITS(ap -> addrlens, calling_addrlen) +
			X25GBITS(ap -> addrlens, called_addrlen) + 1) / 2;
E 18
D 21
		if (fcp + *fcp <= ((octet *)xp) + len)
E 21
I 21
		if (fcp + *fcp <= ((octet *) xp) + len)
E 21
D 12
			parse_facilities (fcp, lcp -> lcd_ceaddr);
E 12
I 12
			pk_parse_facilities (fcp, lcp -> lcd_ceaddr);
E 12
	}
	pk_assoc (lcp -> lcd_pkp, lcp, lcp -> lcd_ceaddr);
I 11
	if (lcp -> lcd_so == 0 && lcp -> lcd_upper)
D 21
		lcp -> lcd_upper(lcp, m);
E 21
I 21
		lcp -> lcd_upper (lcp, m);
E 21
E 11
}

D 12
static
parse_facilities (fcp, sa)
E 12
I 12
pk_parse_facilities (fcp, sa)
E 12
register octet *fcp;
register struct sockaddr_x25 *sa;
{
	register octet *maxfcp;

	maxfcp = fcp + *fcp;
	fcp++;
	while (fcp < maxfcp) {
		/*
		 * Ignore national DCE or DTE facilities
		 */
		if (*fcp == 0 || *fcp == 0xff)
			break;
		switch (*fcp) {
		case FACILITIES_WINDOWSIZE:
			sa -> x25_opts.op_wsize = fcp[1];
			fcp += 3;
			break;

		case FACILITIES_PACKETSIZE:
			sa -> x25_opts.op_psize = fcp[1];
			fcp += 3;
			break;

		case FACILITIES_THROUGHPUT:
			sa -> x25_opts.op_speed = fcp[1];
			fcp += 2;
			break;

		case FACILITIES_REVERSE_CHARGE:
			if (fcp[1] & 01)
				sa -> x25_opts.op_flags |= X25_REVERSE_CHARGE;
			/*
			 * Datapac specific: for a X.25(1976) DTE, bit 2
			 * indicates a "hi priority" (eg. international) call.
			 */
			if (fcp[1] & 02 && sa -> x25_opts.op_psize == 0)
				sa -> x25_opts.op_psize = X25_PS128;
			fcp += 2;
			break;

		default:
/*printf("unknown facility %x, class=%d\n", *fcp, (*fcp & 0xc0) >> 6);*/
			switch ((*fcp & 0xc0) >> 6) {
			case 0:			/* class A */
				fcp += 2;
				break;

			case 1:
				fcp += 3;
				break;

			case 2:
				fcp += 4;
				break;

			case 3:
				fcp++;
				fcp += *fcp;
			}
		}
D 13
	}
}

from_bcd (a, x, len)
register char *a;
register octet **x;
register int len;
{
	register int posn = 0;

	while (--len >= 0) {
		if (posn++ & 0x01)
			*a = *(*x)++ & 0x0f;
		else
			*a = (**x >> 4) & 0x0F;
		*a++ |= 0x30;
E 13
	}
}
E 1
