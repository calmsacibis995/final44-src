h38749
s 00002/00002/00280
d D 8.1 93/06/10 23:20:09 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00280
d D 7.12 93/05/25 11:51:46 bostic 12 11
c trailing comment after #else or #endif
e
s 00024/00024/00258
d D 7.11 92/10/11 12:21:56 bostic 11 10
c make kernel includes standard
e
s 00027/00009/00255
d D 7.10 91/07/29 14:55:32 sklower 10 9
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00001/00001/00263
d D 7.9 91/07/18 20:33:26 sklower 9 8
c this changes reflect getting rid of so_tpcb.
e
s 00001/00001/00263
d D 7.8 91/05/09 21:16:09 sklower 8 7
c stupid mistake concering (a & b) == 0 forgetting () needed.
e
s 00012/00009/00252
d D 7.7 91/05/06 19:24:18 bostic 7 6
c new copyright; att/bsd/shared
e
s 00003/00061/00258
d D 7.6 91/05/06 18:20:53 sklower 6 5
c when connecting, set refcount on isopcb to remember to clear pkcb;
c get rid of tpcons_mtu; tpclnp_mtu should do the right thing.
e
s 00001/00001/00318
d D 7.5 91/04/26 15:11:39 sklower 5 4
c call to tp_input lacks parameter
e
s 00073/00084/00246
d D 7.4 91/01/09 15:44:58 sklower 4 3
c Checkpoint integration of tp_cons with UBC X.25; compiles only;
c not tested, probably not complete.
e
s 00001/00000/00329
d D 7.3 89/08/29 13:44:49 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00012/00012/00317
d D 7.2 89/04/22 11:54:42 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00329/00000/00000
d D 7.1 88/12/14 15:29:55 sklower 1 0
c date and time created 88/12/14 15:29:55 by sklower
e
u
U
t
T
I 7
/*-
D 13
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 7
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
/* 
 * ARGO TP
 * $Header: tp_cons.c,v 5.6 88/11/18 17:27:13 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_cons.c,v $
I 3
D 7
 *	%W% (Berkeley) %G% *
E 7
E 3
 *
D 4
 * Here is where you find the iso-dependent code.  We've tried
E 4
I 4
 * Here is where you find the iso- and cons-dependent code.  We've tried
E 4
 * keep all net-level and (primarily) address-family-dependent stuff
 * out of the tp source, and everthing here is reached indirectly
 * through a switch table (struct nl_protosw *) tpcb->tp_nlproto 
 * (see tp_pcb.c). 
 * The routines here are:
D 6
 *		tpcons_mtu: figure out what size tpdu to use
E 6
D 7
 *		tpcons_input: pullup and call tp_input w/ correct arguments
D 4
 *		tpcons_output_dg: package a pkt for cons given 2 addresses & some data
E 4
 *		tpcons_output: package a pkt for cons given an isopcb & some data
 *		cons_chan_to_tpcb: find a tpcb based on the channel #
E 7
I 7
 *	tpcons_input: pullup and call tp_input w/ correct arguments
 *	tpcons_output: package a pkt for cons given an isopcb & some data
 *	cons_chan_to_tpcb: find a tpcb based on the channel #
E 7
 */
D 7

#ifndef lint
static char *rcsid = "$Header: tp_cons.c,v 5.6 88/11/18 17:27:13 nhall Exp $";
#endif lint

E 7
D 4
#include "argoxtwentyfive.h"
E 4

#ifdef ISO
D 4
#if NARGOXTWENTYFIVE > 0
E 4
I 4
#ifdef TPCONS
E 4

D 2
#include "types.h"
E 2
I 2
D 11
#include "param.h"
E 2
#include "socket.h"
#include "domain.h"
#include "mbuf.h"
#include "errno.h"
#include "time.h"
E 11
I 11
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/domain.h>
#include <sys/mbuf.h>
#include <sys/errno.h>
#include <sys/time.h>
E 11
I 4

E 4
D 11
#include "../net/if.h"
I 4
#include "../net/route.h"
E 11
I 11
#include <net/if.h>
#include <net/route.h>
E 11
E 4

D 2
#include "../netiso/tp_param.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_tpdu.h"
E 2
I 2
D 11
#include "tp_param.h"
#include "argo_debug.h"
#include "tp_stat.h"
#include "tp_pcb.h"
#include "tp_trace.h"
#include "tp_stat.h"
#include "tp_tpdu.h"
E 2
D 4
#include "../net/route.h"
E 4
D 2
#include "../netiso/iso.h"
#include "../netiso/iso_pcb.h"
#include "../netiso/cons.h"
#include "../netiso/tp_seq.h"
E 2
I 2
#include "iso.h"
I 4
#include "iso_errno.h"
E 4
#include "iso_pcb.h"
#include "cons.h"
#include "tp_seq.h"
E 11
I 11
#include <netiso/tp_param.h>
#include <netiso/argo_debug.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_tpdu.h>
#include <netiso/iso.h>
#include <netiso/iso_errno.h>
#include <netiso/iso_pcb.h>
#include <netiso/cons.h>
#include <netiso/tp_seq.h>
E 11
E 2

I 4
#undef FALSE
#undef TRUE
D 11
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 11
I 11
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 11

D 11
#include "if_cons.c"
E 11
I 11
#include <netiso/if_cons.c>
E 11
E 4
int tpcons_output();

/*
 * CALLED FROM:
I 4
 *  tp_route_to() for PRU_CONNECT
 * FUNCTION, ARGUMENTS, SIDE EFFECTS and RETURN VALUE:
 *  version of the previous procedure for X.25
 */

tpcons_pcbconnect(isop, nam)
struct isopcb *isop;
register struct mbuf *nam;
{
	int error;
	if (error = iso_pcbconnect(isop, nam))
		return error;
	if ((isop->isop_chan = (caddr_t) pk_attach((struct socket *)0)) == 0) {
		IFDEBUG(D_CCONS)
			printf("tpcons_pcbconnect: no pklcd; returns 0x%x\n", error);
		ENDDEBUG
		return ENOBUFS;
	}
	if (error = cons_connect(isop)) { /* if it doesn't work */
		/* oh, dear, throw packet away */
		pk_disconnect((struct pklcd *)isop->isop_chan);
		isop->isop_chan = 0;
D 6
		return error;
	}
E 6
I 6
	} else 
		isop->isop_refcnt = 1;
	return error;
E 6
}

D 6

/*
 * CALLED FROM:
E 4
 *  tp_input() on incoming CR, CC, and pr_usrreq() for PRU_CONNECT
 * FUNCTION, ARGUMENTS, SIDE EFFECTS and RETURN VALUE:
 *  version of the previous procedure for X.25
 */

void
tpcons_mtu(so, isop, size, negot)
	struct socket *so;
	struct isopcb *isop;
	int *size;
	u_char *negot;
{
	register struct ifnet *ifp;
D 4
	register int i=0;
E 4
I 4
	register int i=0, isize;
E 4
	int windowsize = so->so_rcv.sb_hiwat;
D 4
	struct ifnet	*iso_routeifp();
E 4

	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "ENTER GET MTU: size negot ",*size, *negot, 0, 0);
	ENDTRACE

D 4

	*size = 1 << *negot;
E 4
I 4
	isize = *size = 1 << *negot;
#ifdef ancient_history
E 4
	if ((ifp = iso_routeifp(&isop->isop_faddr)) == (struct ifnet *)0)
		return;
I 4
#endif
E 4

D 4
	if( *size > windowsize ) {
		*size = windowsize;
E 4
I 4
	if (isize > windowsize) {
		isize = windowsize;
E 4
		i++;
	}
D 4

	if(*size > ifp->if_mtu) {
		*size = ifp->if_mtu ;
E 4
I 4
	if (isize > ifp->if_mtu) {
		isize = ifp->if_mtu;
E 4
		i++;
	}
D 4
	if(i) {
E 4
I 4
	if (i) {
E 4
		/* size was changed by this routine - have to transform it to
		 * the log2 of size
		 */
D 4
		for(i=TP_MIN_TPDUSIZE; (i<TP_MAX_TPDUSIZE && ((1<<i)<*size)) ; i++)
			;
		/* are we on the same LAN? if so, negotiate one tpdu size larger,
		 * and actually send the real mtu size
		 */
		/* PHASE2: replace with iso_on_localnet(&isop->isop_faddr);
		 */
		if ( !iso_netmatch(&isop->isop_laddr, &isop->isop_faddr) ) {
			i--;
			*size = 1<<i;
E 4
I 4
		for (i = TP_MIN_TPDUSIZE; i < TP_MAX_TPDUSIZE; i++) {
			if (isize <  (1 << (1 + i)))
				break;
E 4
		}
		*negot = i;
I 4
		*size = 1 << i;
E 4
	}

	IFDEBUG(D_CONN)
		printf("GET MTU RETURNS: ifp %s size 0x%x negot 0x%x\n",
		ifp->if_name,	*size, *negot);
	ENDDEBUG
	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "EXIT GET MTU: tpcb size negot ",
		*size, *negot, 0, 0);
	ENDTRACE
}
E 6

/*
 * CALLED FROM:
 * 	cons
 * FUNCTION and ARGUMENTS:
 * THIS MAYBE BELONGS IN SOME OTHER PLACE??? but i think not -
 */
ProtoHook
tpcons_ctlinput(cmd, siso, isop)
	int cmd; 
	struct sockaddr_iso *siso;
	struct isopcb *isop;
{
I 10
	register struct tp_pcb *tpcb = 0;

	if (isop->isop_socket)
		tpcb = (struct tp_pcb *)isop->isop_socket->so_pcb;
E 10
	switch (cmd) {

	case PRC_CONS_SEND_DONE:
D 10
		if( isop->isop_socket ) { /* tp 0 only */
			register struct tp_pcb *tpcb = 
D 9
				(struct tp_pcb *)isop->isop_socket->so_tpcb;
E 9
I 9
				(struct tp_pcb *)isop->isop_socket->so_pcb;
E 10
I 10
		if (tpcb) {
E 10
E 9
			struct 	tp_event 		E;
			int 					error = 0;

D 10
			if( tpcb->tp_class == TP_CLASS_0 ) {
E 10
I 10
			if (tpcb->tp_class == TP_CLASS_0) {
E 10
				/* only if class is exactly class zero, not
				 * still in class negotiation
				 */
				/* fake an ack */
				register SeqNum	seq =  SEQ_ADD(tpcb, tpcb->tp_snduna, 1);

				IFTRACE(D_DATA)
					tptrace(TPPTmisc, "FAKE ACK seq cdt 1", 
						seq, 0,0,0);
				ENDTRACE
				IFDEBUG(D_DATA)
					printf("FAKE ACK seq 0x%x cdt 1\n", seq );
				ENDDEBUG
				E.ATTR(AK_TPDU).e_cdt = 1;
				E.ATTR(AK_TPDU).e_seq = seq;
				E.ATTR(AK_TPDU).e_subseq = 0;
				E.ATTR(AK_TPDU).e_fcc_present = 0;
				error =  DoEvent(AK_TPDU);
				if( error ) {
					tpcb->tp_sock->so_error = error;
				}
			} /* else ignore it */
D 10
		} 
E 10
I 10
		}
E 10
		break;
	case PRC_ROUTEDEAD:
D 10
		if( isop->isop_socket ) { /* tp 0 only */
E 10
I 10
		if (tpcb && tpcb->tp_class == TP_CLASS_0) {
E 10
			tpiso_reset(isop);
			break;
		} /* else drop through */
	default:
		(void) tpclnp_ctlinput(cmd, siso);
		break;
	}
	return 0;
}

/*
 * CALLED FROM:
 * 	cons's intr routine
 * FUNCTION and ARGUMENTS:
 * Take a packet (m) from cons, pullup m as required by tp,
 *  ignore the socket argument, and call tp_input. 
 * No return value.  
 */
ProtoHook
D 4
tpcons_input(m, faddr, laddr, so, channel)
E 4
I 4
tpcons_input(m, faddr, laddr, channel)
E 4
	struct mbuf 		*m;
	struct sockaddr_iso	*faddr, *laddr;
D 4
	struct socket 		*so; /* not used */
	int					channel;
E 4
I 4
	caddr_t				channel;
E 4
{
	if( m == MNULL)
		return 0;

	m = (struct mbuf *)tp_inputprep(m);

	IFDEBUG(D_TPINPUT)
		printf("tpcons_input before tp_input(m 0x%x)\n", m);
		dump_buf( m, 12+ m->m_len);
	ENDDEBUG
D 5
	tp_input(m, faddr, laddr, channel, tpcons_output);
E 5
I 5
	tp_input(m, faddr, laddr, channel, tpcons_output, 0);
E 5
	return 0;
}


/*
 * CALLED FROM:
 *  tp_emit()
 * FUNCTION and ARGUMENTS:
 *  Take a packet(m0) from tp and package it so that cons will accept it.
 *  This means filling in a few of the fields.
 *  inp is the isopcb structure; datalen is the length of the data in the
 *  mbuf string m0.
 * RETURN VALUE:
 *  whatever (E*) is returned form the net layer output routine.
 */

int
tpcons_output(isop, m0, datalen, nochksum)
	struct isopcb		*isop;
	struct mbuf 		*m0;
	int 				datalen;
	int					nochksum;
{
D 4
	struct tp_pcb 		*tpcb;
E 4
I 4
	register	struct mbuf *m = m0;
E 4
	int					error;

	IFDEBUG(D_EMIT)
		printf(
		"tpcons_output(isop 0x%x, m 0x%x, len 0x%x socket 0x%x\n",
			isop, m0, datalen, isop->isop_socket);
	ENDDEBUG
D 4
	if(m0 == MNULL)
E 4
I 4
	if (m == MNULL)
E 4
		return 0;
D 4
	ASSERT(m0->m_len > 0);
	tpcb = (struct tp_pcb *)isop->isop_socket->so_tpcb;

	/* check is for class EQUAL to 4: if still in negotiation stage, 
	 * cannot send as dgm
	 */
	error = cons_output(isop, m0,  datalen, (tpcb->tp_class == TP_CLASS_4));
E 4
I 4
D 8
	if (m->m_flags & M_PKTHDR == 0) {
E 8
I 8
	if ((m->m_flags & M_PKTHDR) == 0) {
E 8
		MGETHDR(m, M_DONTWAIT, MT_DATA);
		if (m == 0)
			return ENOBUFS;
		m->m_next = m0;
	}
	m->m_pkthdr.len = datalen;
D 10
	error = pk_send(isop->isop_chan, m);
E 4
	IncStat(ts_tpdu_sent);

E 10
I 10
	if (isop->isop_chan == 0) {
		/* got a restart maybe? */
		if ((isop->isop_chan = (caddr_t) pk_attach((struct socket *)0)) == 0) {
			IFDEBUG(D_CCONS)
				printf("tpcons_output: no pklcd\n");
			ENDDEBUG
			error = ENOBUFS;
		}
		if (error = cons_connect(isop)) {
			pk_disconnect((struct pklcd *)isop->isop_chan);
			isop->isop_chan = 0;
			IFDEBUG(D_CCONS)
				printf("tpcons_output: can't reconnect\n");
			ENDDEBUG
		}
	} else {
		error = pk_send(isop->isop_chan, m);
		IncStat(ts_tpdu_sent);
	}
E 10
D 4
	IFTRACE(D_EMIT)
		tptrace( TPPTmisc, 
		"tpcons_output( isop  m isdgm cons_output returns", 
			isop, m0, (tpcb->tp_class == TP_CLASS_4), error );
	ENDTRACE
E 4
	return error;
}
D 4

E 4
/*
 * CALLED FROM:
 *  tp_error_emit()
 * FUNCTION and ARGUMENTS:
D 4
 *  This is a copy of tpcons_output that takes the addresses
 *  instead of a pcb.  It's used by the tp_error_emit, when we
 *  don't have an iso_pcb with which to call the normal output rtn.
E 4
I 4
 *  Take a packet(m0) from tp and package it so that cons will accept it.
 *  chan is the cons channel to use; datalen is the length of the data in the
 *  mbuf string m0.
E 4
 * RETURN VALUE:
D 4
 *  ENOBUFS or
E 4
 *  whatever (E*) is returned form the net layer output routine.
 */

int
D 4
tpcons_output_dg(laddr, faddr, m0, datalen, ro, nochksum)
	struct iso_addr		*laddr, *faddr;
E 4
I 4
tpcons_dg_output(chan, m0, datalen)
	caddr_t				chan;
E 4
	struct mbuf 		*m0;
	int 				datalen;
D 4
	struct route 		*ro;
	int					nochksum;
E 4
{
D 4
	IFDEBUG(D_TPISO)
		printf("PANIC: tpcons_output_dg  datalen 0x%x m0 0x%x\n", datalen, m0);
	ENDDEBUG

	return 0;
E 4
I 4
	return tpcons_output(((struct pklcd *)chan)->lcd_upnext, m0, datalen, 0);
E 4
}
D 4

struct tp_pcb *
cons_chan_to_tpcb(chan)
	int chan;
{
	extern struct isopcb *cons_chan_to_pcb ();
#ifdef ARGO_DEBUG
	struct isopcb *isop = cons_chan_to_pcb (chan, -1);
#else ARGO_DEBUG
	struct isopcb *isop = cons_chan_to_pcb (chan);
#endif ARGO_DEBUG

	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "vc->tpcb(chan) socket",
			chan, isop->isop_socket, 0, 0);
	ENDTRACE
	IFDEBUG(D_CONN)
		printf("vc->tpcb(0x%x) socket 0x%x, *ISOP dump:",
			chan, isop->isop_socket);
		dump_buf( isop, 32);
	ENDDEBUG
	if( isop->isop_socket == (struct socket *)0 )
		return (struct tp_pcb *) 0;
	else {
		return (struct tp_pcb *)(isop->isop_socket->so_tpcb);
}
}
#endif NARGOXTWENTYFIVE
E 4
I 4
D 12
#endif TPCONS
E 4
#endif ISO
E 12
I 12
#endif /* TPCONS */
#endif /* ISO */
E 12
E 1
