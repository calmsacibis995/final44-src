h08349
s 00001/00001/00189
d D 8.2 94/09/22 19:12:58 sklower 15 14
c ( ? : ) does not yield an l-value.  Fix from cgd.
e
s 00002/00002/00188
d D 8.1 93/06/10 22:53:59 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00008/00179
d D 7.13 92/12/08 17:11:11 sklower 13 12
c changes to run over both LLC and HDLC, and also use explicit shifts
c instead of bitfields.
e
s 00011/00011/00176
d D 7.12 92/10/11 11:49:39 bostic 12 11
c make kernel includes standard
e
s 00005/00003/00182
d D 7.11 91/07/17 11:20:45 sklower 11 10
c useful debugging changes
e
s 00004/00005/00181
d D 7.10 91/05/29 19:29:15 sklower 10 9
c (temporarily) redo the way RR's and RNR's are generated;
c may change back.  This allows you to stupidly RR the same packet twice without
c generating errors.  I can't track it down now, so this is a bandaid.
e
s 00003/00000/00183
d D 7.9 91/05/09 21:20:07 sklower 9 8
c add debugging code
e
s 00001/00001/00182
d D 7.8 91/03/12 15:13:40 sklower 8 7
c old version ignored negotiated window size and used default;
c this version works with ISODE 6.7m
e
s 00004/00002/00179
d D 7.7 91/01/09 15:40:20 sklower 7 6
c checkpoint -- this version compiles and represents most of 
c the changes to have ISO CONS be a kernel client of X.25; not tested!!!!
e
s 00001/00001/00180
d D 7.6 90/10/04 19:50:08 sklower 6 5
c capture current work; fix minor bugs concerning packet lengths &
c conventions; add routine to fragment datagrams into complete sequences.
e
s 00011/00011/00170
d D 7.5 90/08/30 18:48:35 sklower 5 4
c this version compiles; completely untested
e
s 00008/00021/00173
d D 7.4 90/06/21 12:28:58 sklower 4 3
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00009/00014/00185
d D 7.3 90/05/22 15:46:18 sklower 3 2
c checkpoint before changing pq structure to be a sockbuf for downq 
c and only retaining up method
e
s 00013/00001/00186
d D 7.2 90/05/11 15:22:14 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00187/00000/00000
d D 7.1 90/05/11 11:19:40 sklower 1 0
c date and time created 90/05/11 11:19:40 by sklower
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
D 13
 * Copyright (c) 1990 The Regents of the University of California.
E 13
I 13
 * Copyright (C) Computer Science Department IV, 
 * 		 University of Erlangen-Nuremberg, Germany, 1992
D 14
 * Copyright (c) 1991, 1992  The Regents of the University of California.
E 13
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 13
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
E 13
I 13
 * This code is derived from software contributed to Berkeley by the
 * Laboratory for Computation Vision and the Computer Science Department
 * of the the University of British Columbia and the Computer Science
 * Department (IV) of the University of Erlangen-Nuremberg, Germany.
E 13
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
#include "../h/socketvar.h"
#include "../h/protosw.h"
#include "../h/errno.h"
E 5
I 5
D 12
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "protosw.h"
#include "errno.h"
E 12
I 12
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/errno.h>
E 12
E 5

D 12
#include "../net/if.h"
E 12
I 12
#include <net/if.h>
E 12

D 5
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
#include "../netccitt/x25.h"
E 5
I 5
D 12
#include "x25.h"
#include "pk.h"
#include "pk_var.h"
E 12
I 12
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 12
E 5

I 9
D 11
struct mbuf_cache pk_output_cache = {0 };
E 11
I 11
struct mbuf_cache pk_output_cache = {0 }, pk_input_cache;
E 11
E 9
struct	mbuf *nextpk ();

pk_output (lcp)
register struct pklcd *lcp;
{
	register struct x25_packet *xp;
	register struct mbuf *m;
	register struct pkcb *pkp = lcp -> lcd_pkp;

	if (lcp == 0 || pkp == 0) {
		printf ("pk_output: zero arg\n");
		return;
	}

	while ((m = nextpk (lcp)) != NULL) {
		xp = mtod (m, struct x25_packet *);

		switch (pk_decode (xp) + lcp -> lcd_state) {
		/* 
		 *  All the work is already done - just set the state and
		 *  pass to peer.
		 */
		case CALL + READY: 
			lcp -> lcd_state = SENT_CALL;
			lcp -> lcd_timer = pk_t21;
			break;

		/*
		 *  Just set the state to allow packet to flow and send the
		 *  confirmation.
		 */
		case CALL_ACCEPTED + RECEIVED_CALL: 
			lcp -> lcd_state = DATA_TRANSFER;
			break;

		/* 
		 *  Just set the state. Keep the LCD around till the clear
		 *  confirmation is returned.
		 */
		case CLEAR + RECEIVED_CALL: 
		case CLEAR + SENT_CALL: 
		case CLEAR + DATA_TRANSFER: 
			lcp -> lcd_state = SENT_CLEAR;
			lcp -> lcd_retry = 0;
			/* fall through */

		case CLEAR + SENT_CLEAR:
			lcp -> lcd_timer = pk_t23;
			lcp -> lcd_retry++;
			break;

		case CLEAR_CONF + RECEIVED_CLEAR: 
		case CLEAR_CONF + SENT_CLEAR: 
		case CLEAR_CONF + READY: 
			lcp -> lcd_state = READY;
			break;

		case DATA + DATA_TRANSFER: 
D 13
			PS(xp) = lcp -> lcd_ssn;
E 13
I 13
			SPS(xp, lcp -> lcd_ssn);
E 13
I 10
			lcp -> lcd_input_window =
				(lcp -> lcd_rsn + 1) % MODULUS;
E 10
D 13
			PR(xp) = lcp -> lcd_input_window;
E 13
I 13
			SPR(xp, lcp -> lcd_input_window);
E 13
			lcp -> lcd_last_transmitted_pr = lcp -> lcd_input_window;
			lcp -> lcd_ssn = (lcp -> lcd_ssn + 1) % MODULUS;
D 8
			if (lcp -> lcd_ssn == ((lcp -> lcd_output_window + pkp->pk_xcp->xc_pwsize) % MODULUS))
E 8
I 8
			if (lcp -> lcd_ssn == ((lcp -> lcd_output_window + lcp -> lcd_windowsize) % MODULUS))
E 8
				lcp -> lcd_window_condition = TRUE;
			break;

		case INTERRUPT + DATA_TRANSFER: 
I 7
#ifdef ancient_history
E 7
			xp -> packet_data = 0;
I 7
#endif
E 7
			lcp -> lcd_intrconf_pending = TRUE;
			break;

		case INTERRUPT_CONF + DATA_TRANSFER: 
			break;

		case RR + DATA_TRANSFER: 
D 10
			lcp -> lcd_input_window = (lcp -> lcd_input_window + 1) % MODULUS;
			PR(xp) = lcp -> lcd_input_window;
			lcp -> lcd_last_transmitted_pr = lcp -> lcd_input_window;
			break;

E 10
		case RNR + DATA_TRANSFER: 
I 10
			lcp -> lcd_input_window =
				(lcp -> lcd_rsn + 1) % MODULUS;
E 10
D 13
			PR(xp) = lcp -> lcd_input_window;
E 13
I 13
			SPR(xp, lcp -> lcd_input_window);
E 13
			lcp -> lcd_last_transmitted_pr = lcp -> lcd_input_window;
			break;

		case RESET + DATA_TRANSFER: 
			lcp -> lcd_reset_condition = TRUE;
			break;

		case RESET_CONF + DATA_TRANSFER: 
			lcp -> lcd_reset_condition = FALSE;
			break;

		/* 
		 *  A restart should be only generated internally. Therefore
		 *  all logic for restart is in the pk_restart routine.
		 */
		case RESTART + READY: 
			lcp -> lcd_timer = pk_t20;
			break;

		/* 
		 *  Restarts are all  handled internally.  Therefore all the
		 *  logic for the incoming restart packet is handled in  the
		 *  pk_input routine.
		 */
		case RESTART_CONF + READY: 
			break;

		default: 
			m_freem (m);
			return;
		}

		/* Trace the packet. */
D 7
		pk_trace (pkp -> pk_xcp, xp, "P-Out");
E 7
I 7
		pk_trace (pkp -> pk_xcp, m, "P-Out");
E 7

		/* Pass the packet on down to the link layer */
I 9
D 11
		if (pk_output_cache.mbc_size || pk_output_cache.mbc_oldsize)
			mbuf_cache(&pk_output_cache, m);
E 11
I 11
		if (pk_input_cache.mbc_size || pk_input_cache.mbc_oldsize) {
			m->m_flags |= 0x08;
			mbuf_cache(&pk_input_cache, m);
		}
E 11
E 9
D 3
		(*pkp -> pk_output) (m, pkp -> pk_xcp);
E 3
I 3
D 4
		(*pkp -> pk_lloutput) (m, pkp -> pk_xcp);
E 4
I 4
D 5
		(*pkp -> pk_lloutput) (m, pkp -> llnext);
E 5
I 5
D 6
		(*pkp -> pk_lloutput) (m, pkp -> pk_llnext);
E 6
I 6
D 13
		(*pkp -> pk_lloutput) (pkp -> pk_llnext, m);
E 13
I 13
		(*pkp -> pk_lloutput) (pkp -> pk_llnext, m, pkp -> pk_rt);
E 13
E 6
E 5
E 4
E 3
	}
}

/* 
 *  This procedure returns the next packet to send or null. A
 *  packet is composed of one or more mbufs.
 */

struct mbuf *
nextpk (lcp)
struct pklcd *lcp;
{
D 4
	register struct socket *so = lcp -> lcd_so;
	register struct mbuf *m = 0, *n;
E 4
I 4
	register struct mbuf *m, *n;
	struct socket *so = lcp -> lcd_so;
D 15
	register struct sockbuf *sb = & (so ? so -> so_snd : lcp -> lcd_sb);
E 15
I 15
	register struct sockbuf *sb = (so ? &so -> so_snd : &lcp -> lcd_sb);
E 15
E 4

	if (lcp -> lcd_template) {
D 7
		m = dtom (lcp -> lcd_template);
E 7
I 7
		m = lcp -> lcd_template;
E 7
		lcp -> lcd_template = NULL;
	} else {
		if (lcp -> lcd_rnr_condition || lcp -> lcd_window_condition ||
				lcp -> lcd_reset_condition)
			return (NULL);

D 3
		if (so == 0)
			return (NULL);
E 3
I 3
D 4
		if (so == 0) {
			if ((m = lcp->lcd_downq.pq_data) == 0)
				return (NULL);
			lcp->lcd_downq.pq_data = m->m_nextpkt;
			lcp->lcd_downq.pq_space += m->m_pkthdr.len;
			m->m_nextpkt = 0;
				return (m);
		}
E 3

		if ((m = so -> so_snd.sb_mb) == 0)
E 4
I 4
		if ((m = sb -> sb_mb) == 0)
E 4
			return (NULL);

D 4
		n = m;
		while (n) {
			sbfree (&so -> so_snd, n);
D 3
#ifndef BSD4_3
			if ((int) n -> m_act == 1)
				break;
#endif
E 3
			n = n -> m_next;
		}

D 3
#ifdef BSD4_3
E 3
 		so->so_snd.sb_mb = m->m_act;
E 4
I 4
 		sb -> sb_mb = m -> m_nextpkt;
E 4
 		m->m_act = 0;
I 4
		for (n = m; n; n = n -> m_next)
			sbfree (sb, n);
E 4
D 3
#else
		if (n) {
			so -> so_snd.sb_mb = n -> m_next;
			n -> m_next = 0;
		}
#endif
E 3
	}
D 4

E 4
	return (m);
}
E 1
