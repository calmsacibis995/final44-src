h25076
s 00002/00002/00852
d D 8.1 93/06/10 23:21:08 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00009/00848
d D 7.22 93/05/25 11:52:12 bostic 22 21
c trailing comment after #else or #endif
e
s 00030/00030/00827
d D 7.21 92/10/11 12:22:10 bostic 21 20
c make kernel includes standard
e
s 00001/00001/00856
d D 7.20 92/09/21 19:02:29 mckusick 20 19
c use max rather than MAX
e
s 00004/00001/00853
d D 7.19 92/05/27 16:19:04 sklower 19 18
c must calculate tp_maxlcredit as soon as mss known for initial credit
c offering in CC and CR packets (by calling tp_rsyset).
e
s 00010/00004/00844
d D 7.18 91/12/17 16:19:35 sklower 18 17
c big-or-odd-size packet option. (n x 128 instead of 2^n only)
e
s 00130/00090/00718
d D 7.17 91/10/02 20:55:02 sklower 17 16
c collect commmon code to calculate mtu, tpdu, & window sizes
c based on info cached in the routing table.  (also compute initial values for
c rtt and rttvar)
e
s 00001/00001/00807
d D 7.16 91/09/30 17:54:18 sklower 16 15
c remove back pointer to entry in tp_ref table; use tp_lref instead.
e
s 00002/00001/00806
d D 7.15 91/09/30 13:48:54 sklower 15 14
c reinstate connection refused socket error
e
s 00002/00002/00805
d D 7.14 91/09/26 17:02:37 sklower 14 13
c These changes represent a rewrite of retransmission policies to
c imitate the TCP algorithms more closely.  More tuning and testing need to
c be done, but the code runs at least somewhat, and these represent a checkpoint
e
s 00002/00001/00805
d D 7.13 91/09/03 21:23:20 sklower 13 12
c now that SO_RCVBUF calls down, calculate maxcredit, and use in
c LOCAL_CREDIT macro.
e
s 00060/00036/00746
d D 7.12 91/07/29 14:55:35 sklower 12 11
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00003/00003/00779
d D 7.11 91/07/18 20:33:27 sklower 11 10
c this changes reflect getting rid of so_tpcb.
e
s 00001/00000/00781
d D 7.10 91/06/28 00:00:05 sklower 10 9
c remque requires inclusion of systm.h
e
s 00004/00004/00777
d D 7.9 91/06/27 22:06:16 sklower 9 8
c minor changes to compile under both new and old vm systems
e
s 00014/00010/00767
d D 7.8 91/05/06 19:24:37 bostic 8 7
c new copyright; att/bsd/shared
e
s 00018/00000/00759
d D 7.7 91/04/26 15:14:07 sklower 7 6
c changing conventions for disconnect reason
e
s 00067/00000/00692
d D 7.6 91/03/12 16:02:08 sklower 6 5
c move tp0_stash here from tp_subr.c since we include x.25 header files
e
s 00049/00046/00643
d D 7.5 91/01/09 15:45:12 sklower 5 4
c Checkpoint integration of tp_cons with UBC X.25; compiles only;
c not tested, probably not complete.
e
s 00004/00004/00685
d D 7.4 89/09/22 00:52:52 sklower 4 3
c tracing alignment bug
e
s 00002/00000/00687
d D 7.3 89/08/29 13:45:39 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00092/00064/00595
d D 7.2 89/04/22 11:55:37 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00659/00000/00000
d D 7.1 88/12/14 15:30:16 sklower 1 0
c date and time created 88/12/14 15:30:16 by sklower
e
u
U
t
T
I 8
/*-
D 23
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 8
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
 *
 * $Header: tp_subr2.c,v 5.5 88/11/18 17:28:55 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_subr2.c,v $
I 3
D 4
 *	%W% (Berkeley) %G% *
E 4
I 4
D 8
 *	%W% (Berkeley) %G%
E 8
E 4
E 3
 *
 * Some auxiliary routines:
D 8
 * 		tp_protocol_error: required by xebec- called when a combo of state,
 *			event, predicate isn't covered for by the transition file.
 *		tp_indicate: gives indications(signals) to the user process
 *		tp_getoptions: initializes variables that are affected by the options
 *          chosen.
E 8
I 8
 * 	tp_protocol_error: required by xebec- called when a combo of state,
 *	    event, predicate isn't covered for by the transition file.
 *	tp_indicate: gives indications(signals) to the user process
 *	tp_getoptions: initializes variables that are affected by the options
 *	    chosen.
E 8
 */
D 8

#ifndef lint
static char *rcsid = "$Header: tp_subr2.c,v 5.5 88/11/18 17:28:55 nhall Exp $";
#endif lint
E 8

D 5
#include "argoxtwentyfive.h"

E 5
/* this def'n is to cause the expansion of this macro in the
 * routine tp_local_credit :
 */
#define LOCAL_CREDIT_EXPAND

D 21
#include "param.h"
I 10
#include "systm.h"
E 10
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "domain.h"
#include "protosw.h"
#include "errno.h"
#include "types.h"
#include "time.h"
#include "kernel.h"
E 21
I 21
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>

E 21
#undef MNULL
D 2
#include "../netiso/tp_ip.h"
#include "../netiso/tp_param.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_stat.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/iso.h"
#include "../netiso/iso_errno.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_seq.h"
#include "../netiso/tp_trace.h"
#include "../netiso/iso_pcb.h"
#include "../netiso/tp_user.h"
#include "../netiso/cons.h"
E 2
I 2
D 21
#include "argo_debug.h"
#include "tp_param.h"
#include "tp_ip.h"
#include "iso.h"
#include "iso_errno.h"
#include "iso_pcb.h"
#include "tp_timer.h"
#include "tp_stat.h"
#include "tp_tpdu.h"
#include "tp_pcb.h"
#include "tp_seq.h"
#include "tp_trace.h"
#include "tp_user.h"
#include "cons.h"
E 21
I 21
#include <netiso/argo_debug.h>
#include <netiso/tp_param.h>
#include <netiso/tp_ip.h>
#include <netiso/iso.h>
#include <netiso/iso_errno.h>
#include <netiso/iso_pcb.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_tpdu.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_seq.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_user.h>
#include <netiso/cons.h>
E 21
E 2

I 5
D 21
#include "../net/if.h"
I 12
#include "../net/if_types.h"
E 21
I 21
#include <net/if.h>
#include <net/if_types.h>
E 21
E 12
#ifdef TRUE
#undef FALSE
#undef TRUE
#endif
D 21
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 21
I 21
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 21

I 19
void tp_rsyset();

E 19
E 5
/*
 * NAME: 	tp_local_credit()
 *
 * CALLED FROM:
 *  tp_emit(), tp_usrreq()
 *
 * FUNCTION and ARGUMENTS:
 *	Computes the local credit and stashes it in tpcb->tp_lcredit.
 *  It's a macro in the production system rather than a procdure.
 *
 * RETURNS:
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 *  This doesn't actually get called in a production system - 
 *  the macro gets expanded instead in place of calls to this proc.
 *  But for debugging, we call this and that allows us to add
 *  debugging messages easily here.
 */
void
tp_local_credit(tpcb)
	struct tp_pcb *tpcb;
{
	LOCAL_CREDIT(tpcb);
	IFDEBUG(D_CREDIT)
		printf("ref 0x%x lcdt 0x%x l_tpdusize 0x%x decbit 0x%x\n",
D 16
			tpcb->tp_refp - tp_ref, 
E 16
I 16
			tpcb->tp_lref, 
E 16
			tpcb->tp_lcredit, 
			tpcb->tp_l_tpdusize, 
			tpcb->tp_decbit, 
			tpcb->tp_cong_win
			);
	ENDDEBUG
	IFTRACE(D_CREDIT)
		tptraceTPCB(TPPTmisc,
			"lcdt tpdusz \n",
			 tpcb->tp_lcredit, tpcb->tp_l_tpdusize, 0, 0);
	ENDTRACE
}

/*
 * NAME:  tp_protocol_error()
 *
 * CALLED FROM:
 *  tp_driver(), when it doesn't know what to do with
 * 	a combo of event, state, predicate
 *
 * FUNCTION and ARGUMENTS:
 *  print error mesg 
 *
 * RETURN VALUE:
 *  EIO - always
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 */
int
tp_protocol_error(e,tpcb)
	struct tp_event	*e;
	struct tp_pcb	*tpcb;
{
	printf("TP PROTOCOL ERROR! tpcb 0x%x event 0x%x, state 0x%x\n",
		tpcb, e->ev_number, tpcb->tp_state);
	IFTRACE(D_DRIVER)
		tptraceTPCB(TPPTmisc, "PROTOCOL ERROR tpcb event state",
			tpcb, e->ev_number, tpcb->tp_state, 0 );
	ENDTRACE
	return EIO; /* for lack of anything better */
}


/* Not used at the moment */
ProtoHook
tp_drain()
{
	return 0;
}


/*
 * NAME: tp_indicate()
 *
 * CALLED FROM:
 * 	tp.trans when XPD arrive, when a connection is being disconnected by
 *  the arrival of a DR or ER, and when a connection times out.
 *
 * FUNCTION and ARGUMENTS:
 *  (ind) is the type of indication : T_DISCONNECT, T_XPD
 *  (error) is an E* value that will be put in the socket structure
 *  to be passed along to the user later.
 * 	Gives a SIGURG to the user process or group indicated by the socket
 * 	attached to the tpcb.
 *
 * RETURNS:  Rien
 * 
 * SIDE EFFECTS:
 *
 * NOTES:
 */
void
tp_indicate(ind, tpcb, error)
	int				ind; 
	u_short			error;
	register struct tp_pcb	*tpcb;
{
	register struct socket *so = tpcb->tp_sock;
	IFTRACE(D_INDICATION)
D 4
		tptraceTPCB(TPPTindicate, ind, *(int *)(tpcb->tp_lsuffix), 
D 2
			*(int *)(tpcb->tp_fsuffix), error,so->so_pgrp);
E 2
I 2
			*(int *)(tpcb->tp_fsuffix), error,so->so_pgid);
E 4
I 4
		tptraceTPCB(TPPTindicate, ind, *(u_short *)(tpcb->tp_lsuffix), 
			*(u_short *)(tpcb->tp_fsuffix), error,so->so_pgid);
E 4
E 2
	ENDTRACE
	IFDEBUG(D_INDICATION)
D 2
		u_char *ls, *fs;
E 2
I 2
		char *ls, *fs;
E 2
		ls = tpcb->tp_lsuffix, 
		fs = tpcb->tp_fsuffix, 

		printf(
D 2
"indicate 0x%x lsuf 0x%02x%02x fsuf 0x%02x%02x err 0x%x prgp 0x%x noind 0x%x ref 0x%x\n",
E 2
I 2
"indicate 0x%x lsuf 0x%02x%02x fsuf 0x%02x%02x err 0x%x  noind 0x%x ref 0x%x\n",
E 2
		ind, 
		*ls, *(ls+1), *fs, *(fs+1),
D 2
		error,so->so_pgrp,
E 2
I 2
		error, /*so->so_pgrp,*/
E 2
		tpcb->tp_no_disc_indications,
		tpcb->tp_lref);
	ENDDEBUG

I 7
	if (ind == ER_TPDU) {
		register struct mbuf *m;
		struct tp_disc_reason x;

		if ((so->so_state & SS_CANTRCVMORE) == 0 &&
				(m = m_get(M_DONTWAIT, MT_OOBDATA)) != 0) {

			x.dr_hdr.cmsg_len = m->m_len = sizeof(x);
			x.dr_hdr.cmsg_level = SOL_TRANSPORT;
			x.dr_hdr.cmsg_type= TPOPT_DISC_REASON;
			x.dr_reason = error;
			*mtod(m, struct tp_disc_reason *) = x;
			sbappendrecord(&tpcb->tp_Xrcv, m);
			error = 0;
		} else
			error = ECONNRESET;
	}
E 7
	so->so_error = error;

	if (ind == T_DISCONNECT)  {
I 7
D 15
		so->so_error = ENOTCONN;
E 15
I 15
		if (error == 0)
			so->so_error = ENOTCONN;
E 15
E 7
		if ( tpcb->tp_no_disc_indications )
			return;
	}
	IFTRACE(D_INDICATION)
		tptraceTPCB(TPPTmisc, "doing sohasoutofband(so)", so,0,0,0);
	ENDTRACE
	sohasoutofband(so);
}

/*
 * NAME : tp_getoptions()
 *
 * CALLED FROM:
 * 	tp.trans whenever we go into OPEN state 
 *
 * FUNCTION and ARGUMENTS:
 *  sets the proper flags and values in the tpcb, to control
 *  the appropriate actions for the given class, options,
 *  sequence space, etc, etc.
 * 
 * RETURNS: Nada
 * 
 * SIDE EFFECTS:
 *
 * NOTES:
 */
void
tp_getoptions(tpcb)
struct tp_pcb *tpcb;
{
	tpcb->tp_seqmask = 
		tpcb->tp_xtd_format ?	TP_XTD_FMT_MASK :	TP_NML_FMT_MASK ;
	tpcb->tp_seqbit =
		tpcb->tp_xtd_format ?	TP_XTD_FMT_BIT :	TP_NML_FMT_BIT ;
	tpcb->tp_seqhalf = tpcb->tp_seqbit >> 1;
	tpcb->tp_dt_ticks =
D 20
		MAX(tpcb->tp_dt_ticks, (tpcb->tp_peer_acktime + 2));
E 20
I 20
		max(tpcb->tp_dt_ticks, (tpcb->tp_peer_acktime + 2));
E 20
D 13

E 13
I 13
D 19
	(void) tp_rsyset(tpcb);
E 19
I 19
	tp_rsyset(tpcb);
E 19
	
E 13
}

/*
 * NAME:  tp_recycle_tsuffix()
 *
 * CALLED FROM:
 *  Called when a ref is frozen.
 *
 * FUNCTION and ARGUMENTS:
 *  allows the suffix to be reused. 
 *
 * RETURNS: zilch
 *
 * SIDE EFFECTS:
 *
 * NOTES:
 */
void
tp_recycle_tsuffix(tpcb)
	struct tp_pcb	*tpcb;
{
D 2
	bzero( tpcb->tp_lsuffix, sizeof( tpcb->tp_lsuffix));
	bzero( tpcb->tp_fsuffix, sizeof( tpcb->tp_fsuffix));
E 2
I 2
	bzero((caddr_t)tpcb->tp_lsuffix, sizeof( tpcb->tp_lsuffix));
	bzero((caddr_t)tpcb->tp_fsuffix, sizeof( tpcb->tp_fsuffix));
E 2
	tpcb->tp_fsuffixlen = tpcb->tp_lsuffixlen = 0;

	(tpcb->tp_nlproto->nlp_recycle_suffix)(tpcb->tp_npcb);
}

/*
 * NAME: tp_quench()
 *
 * CALLED FROM:
 *  tp{af}_quench() when ICMP source quench or similar thing arrives.
 *
 * FUNCTION and ARGUMENTS:
 *  Drop the congestion window back to 1.
 *  Congestion window scheme:
 *  Initial value is 1.  ("slow start" as Nagle, et. al. call it)
 *  For each good ack that arrives, the congestion window is increased
 *  by 1 (up to max size of logical infinity, which is to say, 
 *	it doesn't wrap around).
 *  Source quench causes it to drop back to 1.
 *  tp_send() uses the smaller of (regular window, congestion window). 
 *  One retransmission strategy option is to have any retransmission 
 *	cause reset the congestion window back  to 1.
 *
 *	(cmd) is either PRC_QUENCH: source quench, or
 *		PRC_QUENCH2: dest. quench (dec bit)
 *
 * RETURNS:
 * 
 * SIDE EFFECTS:
 * 
 * NOTES:
 */
void
tp_quench( tpcb, cmd )
	struct tp_pcb *tpcb;
	int cmd;
{
	IFDEBUG(D_QUENCH)
		printf("tp_quench tpcb 0x%x ref 0x%x sufx 0x%x\n",
D 4
			tpcb, tpcb->tp_lref, *(int *)(tpcb->tp_lsuffix));
E 4
I 4
			tpcb, tpcb->tp_lref, *(u_short *)(tpcb->tp_lsuffix));
E 4
		printf("cong_win 0x%x decbit 0x%x \n",
			tpcb->tp_cong_win, tpcb->tp_decbit);
	ENDDEBUG
	switch(cmd) {
		case PRC_QUENCH:
D 14
			tpcb->tp_cong_win = 1;
E 14
I 14
			tpcb->tp_cong_win = tpcb->tp_l_tpdusize;
E 14
			IncStat(ts_quench);
			break;
		case PRC_QUENCH2:
D 14
			tpcb->tp_cong_win = 1; /* might as well quench source also */
E 14
I 14
			tpcb->tp_cong_win = tpcb->tp_l_tpdusize; /* might as well quench source also */
E 14
			tpcb->tp_decbit = TP_DECBIT_CLEAR_COUNT;
			IncStat(ts_rcvdecbit);
			break;
	}
}


/*
 * NAME:	tp_netcmd()
 *
 * CALLED FROM:			
 *
 * FUNCTION and ARGUMENTS:			
 *
 * RETURNS:			
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
tp_netcmd( tpcb, cmd )
	struct tp_pcb *tpcb;
	int cmd;
{
D 5
#if NARGOXTWENTYFIVE > 0
E 5
I 5
#ifdef TPCONS
	struct isopcb *isop;
	struct pklcd *lcp;

	if (tpcb->tp_netservice != ISO_CONS)
		return;
	isop = (struct isopcb *)tpcb->tp_npcb;
	lcp = (struct pklcd *)isop->isop_chan;
E 5
	switch (cmd) {

	case CONN_CLOSE:
	case CONN_REFUSE:
D 5
		cons_netcmd( cmd, tpcb->tp_npcb, 0, tpcb->tp_class == TP_CLASS_4);
		/* TODO: can this last param be replaced by 
	 	*	tpcb->tp_netserv != ISO_CONS?)
		*/
E 5
I 5
D 12
		if (isop->isop_refcnt == 1)
E 12
I 12
		if (isop->isop_refcnt == 1) {
			/* This is really superfluous, since it would happen
			   anyway in iso_pcbdetach, although it is a courtesy
			   to free up the x.25 channel before the refwait timer
			   expires. */
			lcp->lcd_upper = 0;
			lcp->lcd_upnext = 0;
E 12
			pk_disconnect(lcp);
D 12
		isop->isop_chan = 0;
		isop->isop_refcnt = 0;
E 12
I 12
			isop->isop_chan = 0;
			isop->isop_refcnt = 0;
		}
E 12
E 5
		break;

	default:
		printf("tp_netcmd(0x%x, 0x%x) NOT IMPLEMENTED\n", tpcb, cmd);
		break;
	}
D 5
#else NARGOXTWENTYFIVE
E 5
I 5
D 22
#else TPCONS
E 22
I 22
#else /* TPCONS */
E 22
E 5
	printf("tp_netcmd(): X25 NOT CONFIGURED!!\n");
D 5
#endif NARGOXTWENTYFIVE > 0
E 5
I 5
#endif
E 5
}
/*
 * CALLED FROM:
 *  tp_ctloutput() and tp_emit()
 * FUNCTION and ARGUMENTS:
 * 	Convert a class mask to the highest numeric value it represents.
 */

int
tp_mask_to_num(x)
	u_char x;
{
	register int j;

	for(j = 4; j>=0 ;j--) {
		if(x & (1<<j))
			break;
	}
	ASSERT( (j == 4) || (j == 0) ); /* for now */
	if( (j != 4) && (j != 0) ) {
		printf("ASSERTION ERROR: tp_mask_to_num: x 0x%x j %d\n",
			x, j);
	}
	IFTRACE(D_TPINPUT)
		tptrace(TPPTmisc, "tp_mask_to_num(x) returns j", x, j, 0, 0);
	ENDTRACE
	IFDEBUG(D_TPINPUT)
		printf("tp_mask_to_num(0x%x) returns 0x%x\n", x, j);
	ENDDEBUG
	return j;
}

static 
copyQOSparms(src, dst)
	struct tp_conn_param *src, *dst;
{
	/* copy all but the bits stuff at the end */
#define COPYSIZE (12 * sizeof(short))

D 2
	bcopy( src, dst, COPYSIZE);
E 2
I 2
	bcopy((caddr_t)src, (caddr_t)dst, COPYSIZE);
E 2
	dst->p_tpdusize = src->p_tpdusize;
	dst->p_ack_strat = src->p_ack_strat;
	dst->p_rx_strat = src->p_rx_strat;
#undef COPYSIZE
}
I 17
/*
 * Determine a reasonable value for maxseg size.
 * If the route is known, check route for mtu.
 * We also initialize the congestion/slow start
 * window to be a single segment if the destination isn't local.
 * While looking at the routing entry, we also initialize other path-dependent
 * parameters from pre-set or cached values in the routing entry.
 */
void
tp_mss(tpcb, nhdr_size)
	register struct tp_pcb *tpcb;
	int nhdr_size;
{
	register struct rtentry *rt;
	struct ifnet *ifp;
	register int rtt, mss;
	u_long bufsize;
D 18
	int i, ssthresh = 0;
E 18
I 18
	int i, ssthresh = 0, rt_mss;
E 18
	struct socket *so;
E 17

I 17
D 18
	mss = 1 << tpcb->tp_tpdusize;
E 18
I 18
	if (tpcb->tp_ptpdusize)
		mss = tpcb->tp_ptpdusize << 7;
	else
		mss = 1 << tpcb->tp_tpdusize;
E 18
	so = tpcb->tp_sock;
	if ((rt = *(tpcb->tp_routep)) == 0) {
		bufsize = so->so_rcv.sb_hiwat;
		goto punt_route;
	}
	ifp = rt->rt_ifp;

#ifdef RTV_MTU	/* if route characteristics exist ... */
	/*
	 * While we're here, check if there's an initial rtt
	 * or rttvar.  Convert from the route-table units
	 * to hz ticks for the smoothed timers and slow-timeout units
	 * for other inital variables.
	 */
	if (tpcb->tp_rtt == 0 && (rtt = rt->rt_rmx.rmx_rtt)) {
		tpcb->tp_rtt = rtt * hz / RTM_RTTUNIT;
		if (rt->rt_rmx.rmx_rttvar)
			tpcb->tp_rtv = rt->rt_rmx.rmx_rttvar
						* hz / RTM_RTTUNIT;
		else
			tpcb->tp_rtv = tpcb->tp_rtt;
	}
	/*
	 * if there's an mtu associated with the route, use it
	 */
	if (rt->rt_rmx.rmx_mtu)
D 18
		mss = rt->rt_rmx.rmx_mtu - nhdr_size;
E 18
I 18
		rt_mss = rt->rt_rmx.rmx_mtu - nhdr_size;
E 18
	else
#endif /* RTV_MTU */
D 18
		mss = (ifp->if_mtu - nhdr_size);
E 18
I 18
		rt_mss = (ifp->if_mtu - nhdr_size);
	if (tpcb->tp_ptpdusize == 0 || /* assume application doesn't care */
	    mss > rt_mss /* network won't support what was asked for */)
		mss = rt_mss;
E 18
	/* can propose mtu which are multiples of 128 */
	mss &= ~0x7f;
	/*
	 * If there's a pipesize, change the socket buffer
	 * to that size.
	 */
#ifdef RTV_SPIPE
	if ((bufsize = rt->rt_rmx.rmx_sendpipe) > 0) {
#endif
		bufsize = min(bufsize, so->so_snd.sb_hiwat);
		(void) sbreserve(&so->so_snd, bufsize);
	}
#ifdef RTV_SPIPE
	if ((bufsize = rt->rt_rmx.rmx_recvpipe) > 0) {
#endif
		bufsize = min(bufsize, so->so_rcv.sb_hiwat);
		(void) sbreserve(&so->so_rcv, bufsize);
	} else
		bufsize = so->so_rcv.sb_hiwat;
#ifdef RTV_SSTHRESH
	/*
	 * There's some sort of gateway or interface
	 * buffer limit on the path.  Use this to set
	 * the slow start threshhold, but set the
	 * threshold to no less than 2*mss.
	 */
	ssthresh = rt->rt_rmx.rmx_ssthresh;
punt_route:
	/*
	 * The current mss is initialized to the default value.
	 * If we compute a smaller value, reduce the current mss.
	 * If we compute a larger value, return it for use in sending
	 * a max seg size option.
	 * If we received an offer, don't exceed it.
	 * However, do not accept offers under 128 bytes.
	 */
	if (tpcb->tp_l_tpdusize)
		mss = min(mss, tpcb->tp_l_tpdusize);
	/*
	 * We want a minimum recv window of 4 packets to
	 * signal packet loss by duplicate acks.
	 */
	mss = min(mss, bufsize >> 2) & ~0x7f;
	mss = max(mss, 128);		/* sanity */
	tpcb->tp_cong_win =
		(rt == 0 || (rt->rt_flags & RTF_GATEWAY)) ? mss : bufsize;
	tpcb->tp_l_tpdusize = mss;
I 19
	tp_rsyset(tpcb);
E 19
	tpcb->tp_ssthresh = max(2 * mss, ssthresh);
	/* Calculate log2 of mss */
	for (i = TP_MIN_TPDUSIZE + 1; i <= TP_MAX_TPDUSIZE; i++)
		if ((1 << i) > mss)
			break;
	i--;
	tpcb->tp_tpdusize = i;
#endif /* RTV_MTU */
}

E 17
/*
 * CALLED FROM:
 *  tp_usrreq on PRU_CONNECT and tp_input on receipt of CR
 *	
 * FUNCTION and ARGUMENTS:
D 17
 * 	route directly to x.25 if the address is type 37 - GROT.
 *  furthermore, let TP0 handle only type-37 addresses
E 17
I 17
 * 	-- An mbuf containing the peer's network address.
 *  -- Our control block, which will be modified
 *  -- In the case of cons, a control block for that layer.
E 17
 *
D 17
 *	Since this assumes that its address argument is in a mbuf, the
 *	parameter was changed to reflect this assumtion. This also
 *	implies that an mbuf must be allocated when this is
 *	called from tp_input
E 17
 *	
 * RETURNS:
 *	errno value	 : 
 *	EAFNOSUPPORT if can't find an nl_protosw for x.25 (really could panic)
 *	ECONNREFUSED if trying to run TP0 with non-type 37 address
 *  possibly other E* returned from cons_netcmd()
D 17
 * NOTE:
 *  Would like to eliminate as much of this as possible -- 
 *  only one set of defaults (let the user set the parms according
 *  to parameters provided in the directory service).
 *  Left here for now 'cause we don't yet have a clean way to handle
 *  it on the passive end.
E 17
I 17
 *
 * SIDE EFFECTS:
 *   Determines recommended tpdusize, buffering and intial delays
 *	 based on information cached on the route.
E 17
 */
int
tp_route_to( m, tpcb, channel)
	struct mbuf					*m;
	register struct tp_pcb		*tpcb;
D 5
	u_int 						channel;
E 5
I 5
	caddr_t 					channel;
E 5
{
	register struct sockaddr_iso *siso;	/* NOTE: this may be a sockaddr_in */
	extern struct tp_conn_param tp_conn_param[];
I 5
D 12
	struct pklcd *lcp = (struct pklcd *)channel;
E 5
	int error = 0;
E 12
I 12
	int error = 0, save_netservice = tpcb->tp_netservice;
	register struct rtentry *rt = 0;
I 17
	int nhdr_size, mtu, bufsize;
E 17
E 12
D 5
	int	vc_to_kill = 0; /* kludge */
E 5

	siso = mtod(m, struct sockaddr_iso *);
	IFTRACE(D_CONN)
		tptraceTPCB(TPPTmisc, 
		"route_to: so  afi netservice class",
D 2
		tpcb->tp_sock, siso->siso_addr.isoa_afi, tpcb->tp_netservice,
E 2
I 2
		tpcb->tp_sock, siso->siso_addr.isoa_genaddr[0], tpcb->tp_netservice,
E 2
			tpcb->tp_class);
	ENDTRACE
	IFDEBUG(D_CONN)
		printf("tp_route_to( m x%x, channel 0x%x, tpcb 0x%x netserv 0x%x)\n", 
			m, channel, tpcb, tpcb->tp_netservice);
		printf("m->mlen x%x, m->m_data:\n", m->m_len);
		dump_buf(mtod(m, caddr_t), m->m_len);
	ENDDEBUG
D 5
	if( siso->siso_family != tpcb->tp_domain ) {
E 5
I 5
D 12
	if (siso->siso_family != tpcb->tp_domain) {
E 5
		error = EAFNOSUPPORT;
		goto done;
	}
I 2
	IFDEBUG(D_CONN)
		printf("tp_route_to  calling nlp_pcbconn, netserv %d\n",
			tpcb->tp_netservice);
	ENDDEBUG
E 12
I 12
	if (channel) {
E 12
D 5
	error = (tpcb->tp_nlproto->nlp_pcbconn)(tpcb->tp_sock->so_pcb, m);
E 5
I 5
#ifdef TPCONS
D 12
	if (lcp) {
E 12
I 12
		struct pklcd *lcp = (struct pklcd *)channel;
E 12
		struct isopcb *isop = (struct isopcb *)lcp->lcd_upnext,
D 11
			*isop_new = (struct isopcb *)tpcb->tp_sock->so_pcb;
E 11
I 11
			*isop_new = (struct isopcb *)tpcb->tp_npcb;
I 12
		/* The next 2 lines believe that you haven't
		   set any network level options or done a pcbconnect
		   and XXXXXXX'edly apply to both inpcb's and isopcb's */
E 12
E 11
		remque(isop_new);
		free(isop_new, M_PCB);
D 11
		tpcb->tp_sock->so_pcb = (caddr_t)isop;
E 11
I 11
		tpcb->tp_npcb = (caddr_t)isop;
E 11
D 12
		if (isop->isop_refcnt == 0) {
			extern struct isopcb tp_isopcb;
			remque(isop);
			insque(isop, &tp_isopcb);
			isop->isop_head = &tp_isopcb;
E 12
I 12
		tpcb->tp_netservice = ISO_CONS;
		tpcb->tp_nlproto = nl_protosw + ISO_CONS;
D 17
		isop->isop_socket = tpcb->tp_sock;
		if (isop->isop_refcnt == 0)
E 17
I 17
		if (isop->isop_refcnt++ == 0) {
E 17
E 12
			iso_putsufx(isop, tpcb->tp_lsuffix, tpcb->tp_lsuffixlen, TP_LOCAL);
D 12
		}
		/* else there are already connections sharing this */
E 12
I 12
D 17
		else
E 17
I 17
			isop->isop_socket = tpcb->tp_sock;
		} else
E 17
			/* there are already connections sharing this */;
E 12
D 17
		isop->isop_refcnt++;
E 17
D 12
	} else
E 12
#endif
I 12
	} else {
		switch (siso->siso_family) {
		default:
			error = EAFNOSUPPORT;
			goto done;
#ifdef ISO
		case AF_ISO:
I 17
		{
			struct isopcb *isop = (struct isopcb *)tpcb->tp_npcb;
			int flags = tpcb->tp_sock->so_options & SO_DONTROUTE;
E 17
			tpcb->tp_netservice = ISO_CLNS;
D 17
			if (rt = rtalloc1((struct sockaddr *)siso, 0)) {
				rt->rt_refcnt--;
				if (rt->rt_flags & RTF_PROTO1)
E 17
I 17
			if (clnp_route(&siso->siso_addr, &isop->isop_route,
							flags, (void **)0, (void **)0) == 0) {
				rt = isop->isop_route.ro_rt;
				if (rt && rt->rt_flags & RTF_PROTO1)
E 17
					tpcb->tp_netservice = ISO_CONS;
			}
D 17
			break;
E 17
I 17
		}    break;
E 17
#endif
#ifdef INET
		case AF_INET:
			tpcb->tp_netservice = IN_CLNS;
D 17
		}
E 17
#endif
I 17
		}
E 17
		if (tpcb->tp_nlproto->nlp_afamily != siso->siso_family) {
			IFDEBUG(D_CONN)
				printf("tp_route_to( CHANGING nlproto old 0x%x new 0x%x)\n", 
						save_netservice, tpcb->tp_netservice);
			ENDDEBUG
			if (error = tp_set_npcb(tpcb))
				goto done;
		}
		IFDEBUG(D_CONN)
			printf("tp_route_to  calling nlp_pcbconn, netserv %d\n",
				tpcb->tp_netservice);
		ENDDEBUG
		tpcb->tp_nlproto = nl_protosw + tpcb->tp_netservice;
E 12
D 11
		error = (tpcb->tp_nlproto->nlp_pcbconn)(tpcb->tp_sock->so_pcb, m);
E 11
I 11
		error = (tpcb->tp_nlproto->nlp_pcbconn)(tpcb->tp_npcb, m);
I 12
	}
E 12
E 11
E 5
D 17
	if( error )
E 17
I 17
	if (error)
E 17
		goto done;
D 17

E 2
	{
D 12
		register int save_netservice = tpcb->tp_netservice;

E 12
		switch(tpcb->tp_netservice) {
		case ISO_COSNS:
		case ISO_CLNS:
			/* This is a kludge but seems necessary so the passive end
			 * can get long enough timers. sigh.
I 2
			if( siso->siso_addr.osinet_idi[1] == (u_char)IDI_OSINET )
E 2
			 */
I 3
D 12
#define	IDI_OSINET	0x0004	/* bcd of "0004" */	
E 3
D 2
			if( siso->siso_addr.osinet_idi[1] == (u_char)IDI_OSINET ) {
E 2
I 2
			if( siso->siso_addr.isoa_genaddr[2] == (char)IDI_OSINET ) {
E 12
I 12
			if (rt && rt->rt_ifp && rt->rt_ifp->if_type == IFT_X25) {
E 12
E 2
				if( tpcb->tp_dont_change_params == 0) {
					copyQOSparms( &tp_conn_param[ISO_COSNS],
							&tpcb->_tp_param);
				}
				tpcb->tp_flags |= TPF_NLQOS_PDN;
			}
			/* drop through to IN_CLNS*/
		case IN_CLNS:
I 2
			if (iso_localifa(siso))
				tpcb->tp_flags |= TPF_PEER_ON_SAMENET;
E 2
D 12
			if( (tpcb->tp_class & TP_CLASS_4)==0 ) {
E 12
I 12
			if((tpcb->tp_class & TP_CLASS_4) == 0) {
E 12
				error = EPROTOTYPE;
				break;
			} 
			tpcb->tp_class = TP_CLASS_4;  /* IGNORE dont_change_parms */
			break;

		case ISO_CONS:
D 5
#if NARGOXTWENTYFIVE > 0
E 5
I 5
#ifdef TPCONS
E 5
			tpcb->tp_flags |= TPF_NLQOS_PDN;
			if( tpcb->tp_dont_change_params == 0 ) {
				copyQOSparms( &tp_conn_param[ISO_CONS],
							&tpcb->_tp_param);
			}
			/*
			 * for use over x.25 really need a small receive window,
			 * need to start slowly, need small max negotiable tpdu size,
			 * and need to use the congestion window to the max
			 * IGNORES tp_dont_change_params for these!
			 */
			if( tpcb->tp_sock->so_snd.sb_hiwat > 512 ) {
				(void) soreserve(tpcb->tp_sock, 512, 512 );/* GAG */
			}
			tpcb->tp_rx_strat =  TPRX_USE_CW;

D 12
			if( (tpcb->tp_nlproto != &nl_protosw[ISO_CONS]) ) {
D 5
				/* if the listener was restricting us to clns,
				 * ( we never get here if the listener isn't af_iso )
				 * refuse the connection :
				 * but we don't have a way to restrict thus - it's
				 * utterly permissive.
					if(channel)  {
						(void) cons_netcmd(CONN_REFUSE, tpcb->tp_npcb, 
								channel, tpcb->tp_class == TP_CLASS_4);
						error = EPFNOSUPPORT;
						goto done;
					}
				 */
E 5
				IFDEBUG(D_CONN)
					printf(
					"tp_route_to( CHANGING nlproto old 0x%x new 0x%x)\n", 
							tpcb->tp_nlproto , &nl_protosw[ISO_CONS]);
				ENDDEBUG
				tpcb->tp_nlproto = &nl_protosw[ISO_CONS];
			}
E 12
D 5
			/* Now we've got the right nl_protosw. 
			 * If we already have a channel (we were called from tp_input())
			 * tell cons that we'll hang onto this channel.
			 * If we don't already have one (we were called from usrreq())
			 * -and if it's TP0 open a net connection and wait for it to finish.
			 */
			if( channel ) {
				error = cons_netcmd( CONN_CONFIRM, tpcb->tp_npcb, 
								channel, tpcb->tp_class == TP_CLASS_4);
				vc_to_kill ++;
			} else if( tpcb->tp_class != TP_CLASS_4 /* class 4 only */) {
				/* better open vc if any possibility of ending up 
				 * in non-multiplexing class
				 */
				error = cons_openvc(tpcb->tp_npcb, siso, tpcb->tp_sock);
				vc_to_kill ++;
			}
E 5
			/* class 4 doesn't need to open a vc now - may use one already 
			 * opened or may open one only when it sends a pkt.
			 */
D 5
#else NARGOXTWENTYFIVE > 0
E 5
I 5
#else TPCONS
E 5
			error = ECONNREFUSED;
D 5
#endif NARGOXTWENTYFIVE > 0
E 5
I 5
#endif TPCONS
E 5
			break;
		default:
			error = EPROTOTYPE;
		}

D 12
		ASSERT( save_netservice == tpcb->tp_netservice);
E 12
	}
D 2
	if( error )
		goto done;
	IFDEBUG(D_CONN)
		printf("tp_route_to  calling nlp_pcbconn, netserv %d\n",
			tpcb->tp_netservice);
	ENDDEBUG
	error = (tpcb->tp_nlproto->nlp_pcbconn)(tpcb->tp_sock->so_pcb, m);

E 2
D 5
	if( error && vc_to_kill ) {
E 5
I 5
	if (error) {
E 5
		tp_netcmd( tpcb, CONN_CLOSE);
		goto done;
	} 
D 2

	/* PHASE 2: replace iso_netmatch with iso_on_localnet(foreign addr) */
	if( iso_netmatch( 
		&(((struct isopcb *)(tpcb->tp_sock->so_pcb))->isop_laddr), 
		&(((struct isopcb *)(tpcb->tp_sock->so_pcb))->isop_faddr)
					 )) {
		tpcb->tp_flags |= TPF_PEER_ON_SAMENET;
	}

E 2
	{	/* start with the global rtt, rtv stats */
		register int i =
		   (int) tpcb->tp_flags & (TPF_PEER_ON_SAMENET | TPF_NLQOS_PDN);

		tpcb->tp_rtt = tp_stat.ts_rtt[i];
		tpcb->tp_rtv = tp_stat.ts_rtv[i];
	}
E 17
I 17
	nhdr_size = tpcb->tp_nlproto->nlp_mtu(tpcb); /* only gets common info */
	tp_mss(tpcb, nhdr_size);
E 17
done:
	IFDEBUG(D_CONN)
		printf("tp_route_to  returns 0x%x\n", error);
	ENDDEBUG
	IFTRACE(D_CONN)
		tptraceTPCB(TPPTmisc, "route_to: returns: error netserv class", error, 
			tpcb->tp_netservice, tpcb->tp_class, 0);
	ENDTRACE
	return error;
}

I 6

/* class zero version */
void
tp0_stash( tpcb, e )
	register struct tp_pcb		*tpcb;
	register struct tp_event	*e;
{
#ifndef lint
#define E e->ATTR(DT_TPDU)
D 22
#else lint
E 22
I 22
#else /* lint */
E 22
#define E e->ev_union.EV_DT_TPDU
D 22
#endif lint
E 22
I 22
#endif /* lint */
E 22

	register struct sockbuf *sb = &tpcb->tp_sock->so_rcv;
	register struct isopcb *isop = (struct isopcb *)tpcb->tp_npcb;

	IFPERF(tpcb)
		PStat(tpcb, Nb_from_ll) += E.e_datalen;
		tpmeas(tpcb->tp_lref, TPtime_from_ll, &e->e_time,
				E.e_seq, PStat(tpcb, Nb_from_ll), E.e_datalen);
	ENDPERF

	IFDEBUG(D_STASH)
		printf("stash EQ: seq 0x%x datalen 0x%x eot 0x%x", 
		E.e_seq, E.e_datalen, E.e_eot);
	ENDDEBUG

	IFTRACE(D_STASH)
		tptraceTPCB(TPPTmisc, "stash EQ: seq len eot", 
		E.e_seq, E.e_datalen, E.e_eot, 0);
	ENDTRACE

	if ( E.e_eot ) {
		register struct mbuf *n = E.e_data;
		n->m_flags |= M_EOR;
		n->m_act = MNULL; /* set on tp_input */
	}
	sbappend(sb, E.e_data);
	IFDEBUG(D_STASH)
		dump_mbuf(sb->sb_mb, "stash 0: so_rcv after appending");
	ENDDEBUG
	if (tpcb->tp_netservice != ISO_CONS)
		printf("tp0_stash: tp running over something wierd\n");
	else {
		register struct pklcd *lcp = (struct pklcd *)isop->isop_chan;
		pk_flowcontrol(lcp, sbspace(sb) <= 0, 1);
	}
} 

void
tp0_openflow(tpcb)
register struct tp_pcb *tpcb;
{
	register struct isopcb *isop = (struct isopcb *)tpcb->tp_npcb;
	if (tpcb->tp_netservice != ISO_CONS)
		printf("tp0_openflow: tp running over something wierd\n");
	else {
		register struct pklcd *lcp = (struct pklcd *)isop->isop_chan;
		if (lcp->lcd_rxrnr_condition)
			pk_flowcontrol(lcp, 0, 0);
	}
}
#ifndef TPCONS
static
pk_flowcontrol() {}
#endif

E 6
#ifdef TP_PERF_MEAS
/*
 * CALLED FROM:
 *  tp_ctloutput() when the user sets TPOPT_PERF_MEAS on
 *  and tp_newsocket() when a new connection is made from 
 *  a listening socket with tp_perf_on == true.
 * FUNCTION and ARGUMENTS:
 *  (tpcb) is the usual; this procedure gets a clear cluster mbuf for
 *  a tp_pmeas structure, and makes tpcb->tp_p_meas point to it.
 * RETURN VALUE:
 *  ENOBUFS if it cannot get a cluster mbuf.
 */

int 
tp_setup_perf(tpcb)
	register struct tp_pcb *tpcb;
{
	register struct mbuf *q;

D 2
	if( tpcb->tp_p_meas == (struct tp_pmeas *)0 ) {

		/* allocate a cluster for all the stats */
		MGET(q, M_DONTWAIT, TPMT_PERF); /* something we don't otherwise use */
E 2
I 2
	if( tpcb->tp_p_meas == 0 ) {
		MGET(q, M_WAITOK, MT_PCB);
E 2
		if (q == 0)
			return ENOBUFS;
D 2
		q->m_act = MNULL;
		MCLGET(q);	/* for the tp_pmeas struct */
		if(q->m_len == 0) {
			m_free(q);
E 2
I 2
		MCLGET(q, M_WAITOK);
		if ((q->m_flags & M_EXT) == 0) {
			(void) m_free(q);
E 2
			return ENOBUFS;
D 2
		} else {
			/* point into the cluster */
			tpcb->tp_p_meas = mtod(q, struct tp_pmeas *);
			/* get rid of the original little mbuf */
			q->m_off = 0; q->m_len = 0;
			m_free(q);
			bzero( (caddr_t)tpcb->tp_p_meas, sizeof (struct tp_pmeas) );
			IFDEBUG(D_PERF_MEAS)
				printf(
				"tpcb 0x%x so 0x%x ref 0x%x tp_p_meas 0x%x tp_perf_on 0x%x\n", 
					tpcb, tpcb->tp_sock, tpcb->tp_lref, 
					tpcb->tp_p_meas, tpcb->tp_perf_on);
			ENDDEBUG
			tpcb->tp_perf_on = 1;
E 2
		}
I 2
		q->m_len = sizeof (struct tp_pmeas);
		tpcb->tp_p_mbuf = q;
		tpcb->tp_p_meas = mtod(q, struct tp_pmeas *);
		bzero( (caddr_t)tpcb->tp_p_meas, sizeof (struct tp_pmeas) );
		IFDEBUG(D_PERF_MEAS)
			printf(
			"tpcb 0x%x so 0x%x ref 0x%x tp_p_meas 0x%x tp_perf_on 0x%x\n", 
				tpcb, tpcb->tp_sock, tpcb->tp_lref, 
				tpcb->tp_p_meas, tpcb->tp_perf_on);
		ENDDEBUG
		tpcb->tp_perf_on = 1;
E 2
	}
	return 0;
}
D 22
#endif TP_PERF_MEAS
E 22
I 22
#endif /* TP_PERF_MEAS */
E 22

#ifdef ARGO_DEBUG
dump_addr (addr)
	register struct sockaddr *addr;
{
	switch( addr->sa_family ) {
		case AF_INET:
D 2
			dump_inaddr(addr);
E 2
I 2
			dump_inaddr((struct sockaddr_in *)addr);
E 2
			break;
I 2
#ifdef ISO
E 2
		case AF_ISO:
D 2
			dump_isoaddr(addr);
E 2
I 2
			dump_isoaddr((struct sockaddr_iso *)addr);
E 2
			break;
I 2
D 22
#endif ISO
E 22
I 22
#endif /* ISO */
E 22
E 2
		default:
			printf("BAD AF: 0x%x\n", addr->sa_family);
			break;
	}
}
I 2

#define	MAX_COLUMNS	8
/*
 *	Dump the buffer to the screen in a readable format. Format is:
 *
 *		hex/dec  where hex is the hex format, dec is the decimal format.
 *		columns of hex/dec numbers will be printed, followed by the
 *		character representations (if printable).
 */
Dump_buf(buf, len)
caddr_t	buf;
int		len;
{
	int		i,j;
D 9

E 9
I 9
#define Buf ((u_char *)buf)
E 9
	printf("Dump buf 0x%x len 0x%x\n", buf, len);
	for (i = 0; i < len; i += MAX_COLUMNS) {
		printf("+%d:\t", i);
		for (j = 0; j < MAX_COLUMNS; j++) {
			if (i + j < len) {
D 9
				printf("%x/%d\t", buf[i+j]&0xff, buf[i+j]);
E 9
I 9
				printf("%x/%d\t", Buf[i+j], Buf[i+j]);
E 9
			} else {
				printf("	");
			}
		}

		for (j = 0; j < MAX_COLUMNS; j++) {
			if (i + j < len) {
D 9
				if (((buf[i+j]) > 31) && ((buf[i+j]) < 128))
					printf("%c", buf[i+j]&0xff);
E 9
I 9
				if (((Buf[i+j]) > 31) && ((Buf[i+j]) < 128))
					printf("%c", Buf[i+j]);
E 9
				else
					printf(".");
			}
		}
		printf("\n");
	}
}
D 22

E 2

#endif ARGO_DEBUG

E 22
I 22
#endif /* ARGO_DEBUG */
E 22
E 1
