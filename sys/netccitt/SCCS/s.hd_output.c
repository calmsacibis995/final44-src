h27263
s 00002/00002/00219
d D 8.1 93/06/10 22:52:59 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00014/00207
d D 7.8 92/10/11 11:49:46 bostic 8 7
c make kernel includes standard
e
s 00001/00001/00220
d D 7.7 92/02/06 16:32:35 sklower 7 6
c comparison wrongly takes precedence over bitwise-and
e
s 00001/00001/00220
d D 7.6 91/05/29 19:20:11 sklower 6 5
c for LLC2/2, there may be many pkp's to one xcp;
c so stuff pkp in m_pkthdr.rcvif, and change conventions for pk_ctlinput to get pkp
e
s 00017/00008/00204
d D 7.5 90/10/04 19:46:29 sklower 5 4
c This version appears to work with accunet.
e
s 00014/00014/00198
d D 7.4 90/08/30 18:48:24 sklower 4 3
c this version compiles; completely untested
e
s 00033/00039/00179
d D 7.3 90/06/21 12:28:36 sklower 3 2
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00013/00001/00205
d D 7.2 90/05/11 15:21:53 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00206/00000/00000
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
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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
D 8
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "domain.h"
#include "socket.h"
I 5
#include "syslog.h"
E 5
#include "protosw.h"
#include "errno.h"
#include "time.h"
#include "kernel.h"
E 8
I 8
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/socket.h>
#include <sys/syslog.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
E 8

E 4
D 8
#include "../net/if.h"
E 8
I 8
#include <net/if.h>
E 8

D 4
#include "../netccitt/hdlc.h"
#include "../netccitt/hd_var.h"
#include "../netccitt/x25.h"
E 4
I 4
D 8
#include "hdlc.h"
#include "hd_var.h"
#include "x25.h"
E 8
I 8
#include <netccitt/hdlc.h>
#include <netccitt/hd_var.h>
#include <netccitt/x25.h>
E 8
E 4

/*
 *      HDLC OUTPUT INTERFACE
 *
 *      This routine is called when the X.25 packet layer output routine
 *      has a information frame (iframe)  to write.   It is  also called 
 *      by the input and control routines of the HDLC layer.
 */

D 3
hd_output (m, xcp)
struct x25config *xcp;
E 3
I 3
D 5
hd_output (m, info)
E 3
register struct mbuf *m;
I 3
caddr_t	info;
E 5
I 5
hd_output (hdp, m0)
register struct hdcb *hdp;
struct mbuf *m0;
E 5
E 3
{
D 3
	register struct hdcb *hdp;
	static struct x25config *lastxcp;
	static struct hdcb *lasthdp;
E 3
I 3
D 5
	register struct hdcb *hdp = (struct hdcb *)info;
E 5
	struct x25config *xcp;
I 5
	register struct mbuf *m = m0;
	int len;
E 5
E 3

	if (m == NULL)
		panic ("hd_output");
I 5
D 7
	if (m->m_flags & M_PKTHDR == 0)
E 7
I 7
	if ((m->m_flags & M_PKTHDR) == 0)
E 7
		panic ("hd_output 2");
E 5

D 3
	if (xcp == lastxcp)
		hdp = lasthdp;
	else {
		for (hdp = hdcbhead; ; hdp = hdp->hd_next) {
			if (hdp == 0) {
				printf("hd_output: can't find hdcb for %X\n", xcp);
				m_freem (m);
				return;
			}
			if (hdp->hd_xcp == xcp)
				break;
		}
		lastxcp = xcp;
		lasthdp = hdp;
	}

E 3
	if (hdp->hd_state != ABM) {
		m_freem (m);
		return;
	}

	/*
	 * Make room for the hdlc header either by prepending
	 * another mbuf, or by adjusting the offset and length
	 * of the first mbuf in the mbuf chain.
	 */

D 3
	if (m->m_off < MMINOFF + HDHEADERLN) {
		register struct mbuf *m0;
E 3
I 3
D 5
	M_PREPEND(m, M_DONTWAIT, HDHEADERLN);
E 5
I 5
	M_PREPEND(m, HDHEADERLN, M_DONTWAIT);
E 5
	if (m == NULL)
		return;
I 5
	for (len = 0; m; m = m->m_next)
		len += m->m_len;
	m = m0;
	m->m_pkthdr.len = len;
E 5
E 3

D 3
		m0 = m_get (M_DONTWAIT, MT_DATA);
		if (m0 == NULL) {
			m_freem (m);
			return;
		}
		m0->m_next = m;
		m0->m_len = HDHEADERLN;
		m = m0;
	} else {
		m->m_off -= HDHEADERLN;
		m->m_len += HDHEADERLN;
	}

E 3
	hd_append (&hdp->hd_txq, m);
	hd_start (hdp);
}

hd_start (hdp)
register struct hdcb *hdp;
{
	register struct mbuf *m;

	/* 
	 * The iframe is only transmitted if all these conditions are FALSE.
	 * The iframe remains queued (hdp->hd_txq) however and will be
	 * transmitted as soon as these conditions are cleared.
	 */

	while (!(hdp->hd_condition & (TIMER_RECOVERY_CONDITION | REMOTE_RNR_CONDITION | REJ_CONDITION))) {
		if (hdp->hd_vs == (hdp->hd_lastrxnr + hdp->hd_xcp->xc_lwsize) % MODULUS) {

			/* We have now exceeded the  maximum  number  of 
			   outstanding iframes. Therefore,  we must wait 
			   until  at least  one is acknowledged if this 
			   condition  is not  turned off before we are
			   requested to write another iframe. */
			hdp->hd_window_condition++;
			break;
		}

		/* hd_remove top iframe from transmit queue. */
		if ((m = hd_remove (&hdp->hd_txq)) == NULL)
			break;

		hd_send_iframe (hdp, m, POLLOFF);
	}
}

/* 
 *  This procedure is passed a buffer descriptor for an iframe. It builds
 *  the rest of the control part of the frame and then writes it out.  It
 *  also  starts the  acknowledgement  timer and keeps  the iframe in the
 *  Retransmit queue (Retxq) just in case  we have to do this again.
 *
 *  Note: This routine is also called from hd_input.c when retransmission
 *       of old frames is required.
 */

hd_send_iframe (hdp, buf, poll_bit)
register struct hdcb *hdp;
register struct mbuf *buf;
int poll_bit;
{
	register struct Hdlc_iframe *iframe;
D 3
	register struct ifnet *ifp = hdp->hd_ifp;
E 3
	struct mbuf *m;
I 3
D 4
	int s
E 4
E 3

	KILL_TIMER (hdp);

	if (buf == 0) {
		printf ("hd_send_iframe: zero arg\n");
#ifdef HDLCDEBUG
		hd_status (hdp);
		hd_dumptrace (hdp);
#endif
		hdp->hd_vs = (hdp->hd_vs + 7) % MODULUS;
		return;
	}
	iframe = mtod (buf, struct Hdlc_iframe *);

	iframe -> hdlc_0 = 0;
	iframe -> nr = hdp->hd_vr;
	iframe -> pf = poll_bit;
	iframe -> ns = hdp->hd_vs;
	iframe -> address = ADDRESS_B;
	hdp->hd_lasttxnr = hdp->hd_vr;
	hdp->hd_rrtimer = 0;

	if (hdp->hd_vs == hdp->hd_retxqi) {
		/* Check for retransmissions. */
		/* Put iframe only once in the Retransmission queue. */
		hdp->hd_retxq[hdp->hd_retxqi] = buf;
		hdp->hd_retxqi = (hdp->hd_retxqi + 1) % MODULUS;
		hdp->hd_iframes_out++;
	}

	hdp->hd_vs = (hdp->hd_vs + 1) % MODULUS;

	hd_trace (hdp, TX, (struct Hdlc_frame *)iframe);

	/* Write buffer on device. */
	m = hdp->hd_dontcopy ? buf : m_copy(buf, 0, (int)M_COPYALL);
	if (m == 0) {
		printf("hdlc: out of mbufs\n");
		return;
	}
D 3
	(*ifp -> if_output) (ifp, m, (struct sockaddr *)hdp->hd_xcp);

E 3
I 3
	(*hdp->hd_output)(hdp, m);
E 3
	SET_TIMER (hdp);
}
I 3

hd_ifoutput(hdp, m)
D 5
register struct hdcb *hdp;
E 5
register struct mbuf *m;
I 5
register struct hdcb *hdp;
E 5
{
	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
D 4
	register struct ifnet *ifp = hdp->hdp_ifp;
E 4
I 4
	register struct ifnet *ifp = hdp->hd_ifp;
E 4
	int s = splimp();
I 5

E 5
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
D 5
		printf("%s%d: HDLC says OK to send but queue full, may hang\n",
			ifp->if_name, ifp->if_unit);
E 5
I 5
	    /* printf("%s%d: HDLC says OK to send but queue full, may hang\n",
			ifp->if_name, ifp->if_unit);*/
E 5
		m_freem(m);
	} else {
		IF_ENQUEUE(&ifp->if_snd, m);
		if ((ifp->if_flags & IFF_OACTIVE) == 0)
			(*ifp->if_start)(ifp);
	}
	splx(s);
}

E 3

/* 
 *  This routine gets control when the timer expires because we have not
 *  received an acknowledgement for a iframe.
 */

hd_resend_iframe (hdp)
register struct hdcb *hdp;
{

	if (hdp->hd_retxcnt++ < hd_n2) {
		if (!(hdp->hd_condition & TIMER_RECOVERY_CONDITION)) {
			hdp->hd_xx = hdp->hd_vs;
			hdp->hd_condition |= TIMER_RECOVERY_CONDITION;
		}

		hdp->hd_vs = hdp->hd_lastrxnr;
		hd_send_iframe (hdp, hdp->hd_retxq[hdp->hd_vs], POLLON);
	} else {
		/* At this point we have not received a RR even after N2
		   retries - attempt to reset link. */

		hd_initvars (hdp);
		hd_writeinternal (hdp, SABM, POLLOFF);
		hdp->hd_state = WAIT_UA;
		SET_TIMER (hdp);
		hd_message (hdp, "Timer recovery failed: link down");
D 6
		(void) pk_ctlinput (PRC_LINKDOWN, hdp->hd_xcp);
E 6
I 6
		(void) pk_ctlinput (PRC_LINKDOWN, hdp->hd_pkp);
E 6
	}
}
E 1
