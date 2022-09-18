h38927
s 00002/00002/00363
d D 8.1 93/06/10 22:53:02 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00363
d D 7.9 92/12/08 18:00:55 sklower 9 8
c didn't quite get includes right . . .
e
s 00022/00001/00341
d D 7.8 92/12/08 15:21:52 sklower 8 7
c changes from husemann
e
s 00013/00013/00329
d D 7.7 92/10/11 11:49:45 bostic 7 6
c make kernel includes standard
e
s 00009/00007/00333
d D 7.6 91/05/29 19:20:09 sklower 6 5
c for LLC2/2, there may be many pkp's to one xcp;
c so stuff pkp in m_pkthdr.rcvif, and change conventions for pk_ctlinput to get pkp
e
s 00027/00019/00313
d D 7.5 90/10/04 19:46:31 sklower 5 4
c This version appears to work with accunet.
e
s 00014/00014/00318
d D 7.4 90/08/30 18:48:25 sklower 4 3
c this version compiles; completely untested
e
s 00001/00003/00331
d D 7.3 90/06/21 12:28:40 sklower 3 2
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00013/00001/00321
d D 7.2 90/05/11 15:21:55 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00322/00000/00000
d D 7.1 90/05/11 11:19:35 sklower 1 0
c date and time created 90/05/11 11:19:35 by sklower
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
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 4
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/domain.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/errno.h"
#include "../h/time.h"
#include "../h/kernel.h"
E 4
I 4
D 7
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "domain.h"
#include "socket.h"
#include "protosw.h"
#include "errno.h"
#include "time.h"
#include "kernel.h"
E 7
I 7
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/socket.h>
I 9
#include <sys/socketvar.h>
E 9
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
E 7
E 4

D 7
#include "../net/if.h"
E 7
I 7
#include <net/if.h>
E 7

D 4
#include "../netccitt/hdlc.h"
#include "../netccitt/hd_var.h"
#include "../netccitt/x25.h"
E 4
I 4
D 7
#include "hdlc.h"
#include "hd_var.h"
#include "x25.h"
E 7
I 7
#include <netccitt/hdlc.h>
#include <netccitt/hd_var.h>
#include <netccitt/x25.h>
I 9
#include <netccitt/pk_var.h>
E 9
E 7
E 4

hd_init ()
{

	hdintrq.ifq_maxlen = IFQ_MAXLEN;
}

hd_ctlinput (prc, addr)
D 5
caddr_t addr;
E 5
I 5
struct sockaddr *addr;
E 5
{
	register struct x25config *xcp = (struct x25config *)addr;
D 5
	register struct ifnet *ifp;
E 5
	register struct hdcb *hdp;
	register struct ifaddr *ifa;
I 5
	struct ifnet *ifp;
I 6
	caddr_t pk_newlink();
E 6
E 5

D 4
	if (xcp->xc_family != AF_CCITT)
E 4
I 4
D 5
	if (xcp->xc_addr.x25_family != AF_CCITT)
E 5
I 5
	if (addr->sa_family != AF_CCITT)
E 5
E 4
		return (EAFNOSUPPORT);
	if (xcp->xc_lptype != HDLCPROTO_LAPB)
		return (EPROTONOSUPPORT);
D 5
	for (ifa = ifa_ifwithaddr ((struct sockaddr *)xcp); ifa; ifa = ifa->ifa_next)
D 4
		if (ifa->ifa_addr.sa_family == AF_CCITT)
E 4
I 4
		if (ifa->ifa_addr->sa_family == AF_CCITT)
E 4
			break;
	if (ifa == 0 || (ifp = ifa->ifa_ifp) == 0)
E 5
I 5
	ifa = ifa_ifwithaddr(addr);
	if (ifa == 0 || ifa->ifa_addr->sa_family != AF_CCITT ||
	    (ifp = ifa->ifa_ifp) == 0)
E 5
		panic ("hd_ctlinput");
	for (hdp = hdcbhead; hdp; hdp = hdp->hd_next)
		if (hdp->hd_ifp == ifp)
			break;

	if (hdp == 0) {		/* new interface */
D 5
		register int error;
		register struct mbuf *m;
E 5
I 5
		int error, hd_ifoutput(), hd_output();
E 5

D 5
		m = m_getclr (M_DONTWAIT, MT_PCB);
		if (m == 0)
E 5
I 5
		/* an hdcb is now too big to fit in an mbuf */
		MALLOC(hdp, struct hdcb *, sizeof (*hdp), M_PCB, M_DONTWAIT);
		if (hdp == 0)
E 5
			return (ENOBUFS);
I 5
		bzero((caddr_t)hdp, sizeof(*hdp));
E 5
D 6
		if (error = pk_ctlinput (PRC_LINKDOWN, xcp)) {
D 5
			m_freem (m);
E 5
I 5
			free((caddr_t)hdp, M_PCB);
E 5
			return (error);
E 6
I 6
		hdp->hd_pkp =
D 8
			pk_newlink ((struct x25_ifaddr *)ifa, (caddr_t)hdp);
E 8
I 8
			(caddr_t) pk_newlink ((struct x25_ifaddr *) ifa, 
					      (caddr_t) hdp);
		((struct x25_ifaddr *)ifa)->ia_pkcb = 
			(struct pkcb *) hdp->hd_pkp;
E 8
		if (hdp -> hd_pkp == 0) {
			free(hdp, M_PCB);
			return (ENOBUFS);
E 6
		}
D 5

		hdp = mtod (m, struct hdcb *);
		hdp->hd_ifp = ifp;
		hdp->hd_xcp = xcp;
E 5
D 6
		hdp->hd_next = hdcbhead;
		hdcbhead = hdp;
E 6
I 5
		hdp->hd_ifp = ifp;
		hdp->hd_ifa = ifa;
		hdp->hd_xcp = xcp;
E 5
		hdp->hd_state = INIT;
I 5
		hdp->hd_output = hd_ifoutput;
D 6
		pk_ifattach((struct x25_ifaddr *)ifa, hd_output, (caddr_t)hdp);
E 6
I 6
		hdp->hd_next = hdcbhead;
		hdcbhead = hdp;
I 8
	} else if (hdp->hd_pkp == 0) { /* interface got reconfigured */
		hdp->hd_pkp =
			(caddr_t) pk_newlink ((struct x25_ifaddr *) ifa, 
					      (caddr_t) hdp);
		((struct x25_ifaddr *)ifa)->ia_pkcb = 
			(struct pkcb *) hdp->hd_pkp;
		if (hdp -> hd_pkp == 0) {
			free(hdp, M_PCB);
			return (ENOBUFS);
		}
E 8
E 6
E 5
	}

	switch (prc) {
	case PRC_IFUP:
		if (xcp->xc_lwsize == 0 ||
			xcp->xc_lwsize > MAX_WINDOW_SIZE)
				xcp->xc_lwsize = MAX_WINDOW_SIZE;
		if (hdp->hd_state == INIT)
			SET_TIMER (hdp);
		break;

	case PRC_IFDOWN:
		if (hdp->hd_state == ABM)
			hd_message (hdp, "Operator shutdown: link closed");
D 6
		(void) pk_ctlinput (PRC_LINKDOWN, xcp);
E 6
I 6
		(void) pk_ctlinput (PRC_LINKDOWN, hdp->hd_pkp);
I 8

		/* fall thru to ... */

	case PRC_DISCONNECT_REQUEST:
		/* drop reference to pkcb --- it's dead meat */
		hdp->hd_pkp = (caddr_t) 0;
		((struct x25_ifaddr *)ifa)->ia_pkcb = (struct pkcb *) 0;

E 8
E 6
		hd_writeinternal (hdp, DISC, POLLON);
		hdp->hd_state = DISC_SENT;
		SET_TIMER (hdp);
	}
	return (0);
}

hd_initvars (hdp)
register struct hdcb *hdp;
{
	register struct mbuf *m;
	register int i;

	/* Clear Transmit queue. */
	while ((m = hd_remove (&hdp->hd_txq)) != NULL)
		m_freem (m);

	/* Clear Retransmit queue. */
	i = hdp->hd_lastrxnr;
	while (i != hdp->hd_retxqi) {
		m_freem (hdp->hd_retxq[i]);
		i = (i + 1) % MODULUS;
	}
	hdp->hd_retxqi = 0;

	hdp->hd_vs = hdp->hd_vr = 0;
	hdp->hd_lasttxnr = hdp->hd_lastrxnr = 0;
	hdp->hd_rrtimer = 0;
	KILL_TIMER(hdp);
	hdp->hd_retxcnt = 0;
	hdp->hd_condition = 0;
}

hd_decode (hdp, frame)
register struct hdcb *hdp;
struct Hdlc_frame *frame;
{
	register int frametype = ILLEGAL;
	register struct Hdlc_iframe *iframe = (struct Hdlc_iframe *) frame;
	register struct Hdlc_sframe *sframe = (struct Hdlc_sframe *) frame;
	register struct Hdlc_uframe *uframe = (struct Hdlc_uframe *) frame;

	if (iframe -> hdlc_0 == 0) {
		frametype = IFRAME;
		hdp->hd_iframes_in++;
	}

	else if (sframe -> hdlc_01 == 1) {
		/* Supervisory format. */
		switch (sframe -> s2) {
		case 0: 
			frametype = RR;
			hdp->hd_rrs_in++;
			break;

		case 1: 
			frametype = RNR;
			hdp->hd_rnrs_in++;
			break;

		case 2: 
			frametype = REJ;
			hdp->hd_rejs_in++;
		}
	}
	else if (uframe -> hdlc_11 == 3) {
		/* Unnumbered format. */
		switch (uframe -> m3) {
		case 0: 
			frametype = DM;
			break;

		case 1: 
			frametype = SABM;
			break;

		case 2: 
			frametype = DISC;
			break;

		case 3: 
			frametype = UA;
			break;

		case 4: 
			frametype = FRMR;
			hdp->hd_frmrs_in++;
		}
	}
	return (frametype);
}

/* 
 *  This routine is called when the HDLC layer internally  generates a
 *  command or  response  for  the remote machine ( eg. RR, UA etc. ). 
 *  Only supervisory or unnumbered frames are processed.
 */

hd_writeinternal (hdp, frametype, pf)
register struct hdcb *hdp;
register int frametype, pf;
{
	register struct mbuf *buf;
	struct Hdlc_frame *frame;
	register struct Hdlc_sframe *sframe;
	register struct Hdlc_uframe *uframe;

D 5
	MGET (buf, M_DONTWAIT, MT_HEADER);
E 5
I 5
	MGETHDR (buf, M_DONTWAIT, MT_HEADER);
E 5
	if (buf == 0)
		return;
	frame = mtod (buf, struct Hdlc_frame *);
	sframe = mtod (buf, struct Hdlc_sframe *);
	uframe = mtod (buf, struct Hdlc_uframe *);

	/* Assume a response - address structure for DTE */
	frame -> address = ADDRESS_A;
	buf -> m_len = 2;
	buf -> m_act = buf -> m_next = NULL;

	switch (frametype) {
	case RR: 
		frame -> control = RR_CONTROL;
		hdp->hd_rrs_out++;
		break;

	case RNR: 
		frame -> control = RNR_CONTROL;
		hdp->hd_rnrs_out++;
		break;

	case REJ: 
		frame -> control = REJ_CONTROL;
		hdp->hd_rejs_out++;
		break;

	case SABM: 
		frame -> control = SABM_CONTROL;
		frame -> address = ADDRESS_B;
		break;

	case DISC: 
I 5
		if ((hdp->hd_ifp->if_flags & IFF_UP) == 0) {
			hdp->hd_state = DISCONNECTED;
			(void) m_freem (buf);
			hd_flush (hdp->hd_ifp);
			return;
		}
E 5
		frame -> control = DISC_CONTROL;
		frame -> address = ADDRESS_B;
		break;

	case DM: 
		frame -> control = DM_CONTROL;
		break;

	case UA: 
		frame -> control = UA_CONTROL;
		break;

	case FRMR: 
		frame -> control = FRMR_CONTROL;
		bcopy ((caddr_t)&hd_frmr, (caddr_t)frame -> info, 3);
		buf -> m_len = 5;
		hdp->hd_frmrs_out++;

	}

	if (sframe -> hdlc_01 == 1) {
		/* Supervisory format - RR, REJ, or RNR. */
		sframe -> nr = hdp->hd_vr;
		sframe -> pf = pf;
		hdp->hd_lasttxnr = hdp->hd_vr;
		hdp->hd_rrtimer = 0;
	}
	else
		uframe -> pf = pf;

	hd_trace (hdp, TX, frame);
D 3
	(*hdp -> hd_ifp -> if_output) (hdp -> hd_ifp, buf,
		(struct sockaddr *)hdp->hd_xcp);

E 3
I 3
D 5
	(*hdp->hd_output)(hdp, buf);
E 5
I 5
	buf -> m_pkthdr.len = buf -> m_len;
	(*hdp->hd_output) (hdp, buf);
E 5
E 3
}

struct mbuf *
hd_remove (q)
struct hdtxq *q;
{
	register struct mbuf *m;

	m = q -> head;
	if (m) {
		if ((q -> head = m -> m_act) == NULL)
			q -> tail = NULL;
		m -> m_act = 0;
	}
	return (m);
}

hd_append (q, m)
register struct hdtxq *q;
register struct mbuf *m;
{

	m -> m_act = NULL;
	if (q -> tail == NULL)
		q -> head = m;
	else
		q -> tail -> m_act = m;
	q -> tail = m;
}

hd_flush (ifp)
struct ifnet *ifp;
{
	register struct mbuf *m;
	register int s;

	while (1) {
D 5
		s = spl6 ();		/* XXX SHOULDN'T THIS BE splimp? */
E 5
I 5
		s = splimp ();
E 5
		IF_DEQUEUE (&ifp->if_snd, m);
		splx (s);
		if (m == 0)
			break;
		m_freem (m);
	}
}

hd_message (hdp, msg)
struct hdcb *hdp;
char *msg;
{
	char *format_ntn ();

	if (hdcbhead -> hd_next)
		printf ("HDLC(%s): %s\n", format_ntn (hdp->hd_xcp), msg);
	else
		printf ("HDLC: %s\n", msg);
}

#ifdef HDLCDEBUG
hd_status (hdp)
struct hdcb *hdp;
{
	printf ("HDLC STATUS:\n V(S)=%d, V(R)=%d, retxqi=%d,\n",
		hdp->hd_vs, hdp->hd_vr, hdp->hd_retxqi);

	printf ("Last_rx_nr=%d, Last_tx_nr=%d,\n Condition=%d, Xx=%d\n",
		hdp->hd_lastrxnr, hdp->hd_lasttxnr, hdp->hd_condition, hdp->hd_xx);
}
#endif
E 1
