h13827
s 00002/00002/00919
d D 8.1 93/06/10 23:21:03 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00917
d D 7.21 93/05/25 11:52:07 bostic 21 20
c trailing comment after #else or #endif
e
s 00020/00021/00901
d D 7.20 92/10/11 12:22:09 bostic 20 19
c make kernel includes standard
e
s 00001/00000/00921
d D 7.19 92/09/21 19:06:04 mckusick 19 18
c need to include systm.h to get min and max
e
s 00009/00005/00912
d D 7.18 92/05/27 16:17:29 sklower 18 17
c 1.) don't set retransmit timers in tp0; 2.) tone down panic:tp_rsyflush
e
s 00014/00009/00903
d D 7.17 91/10/08 21:56:20 sklower 17 16
c misunderstood function of kernel variable ``ticks'';
c need a different one for cheap timer.
e
s 00018/00009/00894
d D 7.16 91/10/02 19:47:50 sklower 16 15
c make code more similar to TCP (use RANGESET & REXMTVAL macros);
c allow for faster initial zero window probes
e
s 00293/00229/00610
d D 7.15 91/09/26 17:02:28 sklower 15 14
c These changes represent a rewrite of retransmission policies to
c imitate the TCP algorithms more closely.  More tuning and testing need to
c be done, but the code runs at least somewhat, and these represent a checkpoint
e
s 00059/00090/00780
d D 7.14 91/09/17 19:09:35 sklower 14 13
c these changes reflect the TCP algorithm for round trip timing
c (not yet tested)
e
s 00004/00020/00866
d D 7.13 91/09/06 17:15:14 sklower 13 12
c adopt TCP's policies concerning acks & (among others) use the fast
c timeout mechanism and delayed acks.
e
s 00006/00006/00880
d D 7.12 91/09/03 21:23:17 sklower 12 11
c now that SO_RCVBUF calls down, calculate maxcredit, and use in
c LOCAL_CREDIT macro.
e
s 00224/00164/00662
d D 7.11 91/08/28 12:29:37 sklower 11 10
c changes to get rid of RTC structure; move packetizing to here.
e
s 00000/00005/00826
d D 7.10 91/08/14 15:49:40 sklower 10 9
c new ack strategy from mostek@cray
e
s 00006/00004/00825
d D 7.9 91/06/27 22:06:11 sklower 9 8
c minor changes to compile under both new and old vm systems
e
s 00009/00005/00820
d D 7.8 91/05/06 19:24:35 bostic 8 7
c new copyright; att/bsd/shared
e
s 00000/00040/00825
d D 7.7 91/03/12 15:54:50 sklower 7 6
c move tp0_stash to tp_subr2.c to avoid including x25 header files.
e
s 00002/00002/00863
d D 7.6 90/07/24 18:13:32 sklower 6 5
c fix retransmission timer
e
s 00007/00005/00858
d D 7.5 90/01/16 22:57:29 sklower 5 4
c mitre decbit changes
e
s 00003/00003/00860
d D 7.4 89/09/22 00:44:21 sklower 4 3
c fixes to tracing and avoiding silly window between
c socket layer and transport; more changes to come to usrreq and tp_send.
e
s 00010/00024/00853
d D 7.3 89/08/29 13:45:32 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00033/00147/00844
d D 7.2 89/04/22 11:55:32 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00991/00000/00000
d D 7.1 88/12/14 15:30:15 sklower 1 0
c date and time created 88/12/14 15:30:15 by sklower
e
u
U
t
T
I 8
/*-
D 22
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
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
 * $Header: tp_subr.c,v 5.3 88/11/18 17:28:43 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_subr.c,v $
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
 * The main work of data transfer is done here.
 * These routines are called from tp.trans.
 * They include the routines that check the validity of acks and Xacks,
 * (tp_goodack() and tp_goodXack() )
 * take packets from socket buffers and send them (tp_send()),
 * drop the data from the socket buffers (tp_sbdrop()),  
 * and put incoming packet data into socket buffers (tp_stash()).
 */
D 8

#ifndef lint
static char *rcsid = "$Header: tp_subr.c,v 5.3 88/11/18 17:28:43 nhall Exp $";
#endif lint
E 8

D 20
#include "param.h"
I 19
#include "systm.h"
E 19
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "protosw.h"
#include "errno.h"
#include "types.h"
#include "time.h"
I 14
#include "kernel.h"
E 20
I 20
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
E 20
E 14

D 2
#include "../netiso/tp_ip.h"
#include "../netiso/iso.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_param.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_meas.h"
#include "../netiso/tp_seq.h"
E 2
I 2
D 20
#include "tp_ip.h"
#include "iso.h"
#include "argo_debug.h"
#include "tp_timer.h"
#include "tp_param.h"
#include "tp_stat.h"
#include "tp_pcb.h"
#include "tp_tpdu.h"
#include "tp_trace.h"
#include "tp_meas.h"
#include "tp_seq.h"
E 20
I 20
#include <netiso/tp_ip.h>
#include <netiso/iso.h>
#include <netiso/argo_debug.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_param.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_tpdu.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_meas.h>
#include <netiso/tp_seq.h>
E 20
E 2

D 14
int 		tp_emit();
static void tp_sbdrop();
E 14
I 14
D 15
int 		tp_emit(), tp_sbdrop();
E 15
I 15
int		tp_emit(), tp_sbdrop();
int		tprexmtthresh = 3;
I 17
extern int	ticks;
E 17
void	tp_send();
E 15
E 14

D 14
#define SMOOTH(newtype, alpha, old, new) \
	(newtype) (((new - old)>>alpha) + (old))

#define ABS(type, val) \
	(type) (((int)(val)<0)?-(val):(val))

D 11
#define TP_MAKE_RTC( Xreg, Xseq, Xeot, Xdata, Xlen, Xretval, Xtype) \
{ 	struct mbuf *xxn;\
	MGET(xxn, M_DONTWAIT, Xtype);\
	if( xxn == (struct mbuf *)0 ) {\
		printf("MAKE RTC FAILED: ENOBUFS\n");\
		return (int)Xretval;\
	}\
	xxn->m_act=MNULL;\
	Xreg = mtod(xxn, struct tp_rtc *);\
	if( Xreg == (struct tp_rtc *)0 ) {\
		return (int)Xretval;\
	}\
	Xreg->tprt_eot = Xeot;\
	Xreg->tprt_seq = Xseq;\
	Xreg->tprt_data = Xdata;\
	Xreg->tprt_octets = Xlen;\
}
E 11

E 14
D 11

E 11
/*
 * CALLED FROM:
 *	tp.trans, when an XAK arrives
 * FUNCTION and ARGUMENTS:
 * 	Determines if the sequence number (seq) from the XAK 
 * 	acks anything new.  If so, drop the appropriate tpdu
 * 	from the XPD send queue.
 * RETURN VALUE:
 * 	Returns 1 if it did this, 0 if the ack caused no action.
 */
int
tp_goodXack(tpcb, seq)
	struct tp_pcb	*tpcb;
	SeqNum 			seq; 
{

	IFTRACE(D_XPD)
		tptraceTPCB(TPPTgotXack, 
D 15
			seq, tpcb->tp_Xuna, tpcb->tp_Xsndnxt, tpcb->tp_sndhiwat, 
E 15
I 15
			seq, tpcb->tp_Xuna, tpcb->tp_Xsndnxt, tpcb->tp_sndnew, 
E 15
			tpcb->tp_snduna); 
	ENDTRACE

	if ( seq == tpcb->tp_Xuna ) {
			tpcb->tp_Xuna = tpcb->tp_Xsndnxt;

			/* DROP 1 packet from the Xsnd socket buf - just so happens
			 * that only one packet can be there at any time
			 * so drop the whole thing.  If you allow > 1 packet
			 * the socket buffer, then you'll have to keep
			 * track of how many characters went w/ each XPD tpdu, so this
			 * will get messier
			 */
			IFDEBUG(D_XPD)
				dump_mbuf(tpcb->tp_Xsnd.sb_mb,
					"tp_goodXack Xsnd before sbdrop");
			ENDDEBUG

			IFTRACE(D_XPD)
				tptraceTPCB(TPPTmisc, 
					"goodXack: dropping cc ",
					(int)(tpcb->tp_Xsnd.sb_cc),
					0,0,0);
			ENDTRACE
D 15
			sbdrop( &tpcb->tp_Xsnd, (int)(tpcb->tp_Xsnd.sb_cc));
I 5
			CONG_ACK(tpcb, seq);
E 15
I 15
			sbdroprecord(&tpcb->tp_Xsnd);
E 15
E 5
			return 1;
	} 
	return 0;
}

/*
 * CALLED FROM:
 *  tp_good_ack()
 * FUNCTION and ARGUMENTS:
 *  updates
D 14
 *  smoothed average round trip time (base_rtt)
 *  roundtrip time variance (base_rtv) - actually deviation, not variance
E 14
I 14
 *  smoothed average round trip time (*rtt)
 *  roundtrip time variance (*rtv) - actually deviation, not variance
E 14
 *  given the new value (diff)
 * RETURN VALUE:
 * void
 */

void
D 14
tp_rtt_rtv( base_rtt, base_rtv, newmeas )
	struct 	timeval *base_rtt, *base_rtv, *newmeas;
E 14
I 14
D 15
tp_rtt_rtv( rtt, rtv, newmeas )
	register int	 *rtt, *rtv;
	int newmeas;
E 15
I 15
tp_rtt_rtv(tpcb)
register struct tp_pcb *tpcb;
E 15
E 14
{
D 14
	/* update  rt variance (really just the deviation): 
	 * 	rtv.smooth_ave =  SMOOTH( | oldrtt.smooth_avg - rtt.this_instance | )
	 */
	base_rtv->tv_sec = 
		SMOOTH( long,  TP_RTV_ALPHA, base_rtv->tv_sec, 
D 6
			ABS( long, base_rtv->tv_sec - newmeas->tv_sec ));
E 6
I 6
			ABS( long, base_rtt->tv_sec - newmeas->tv_sec ));
E 6
	base_rtv->tv_usec = 
		SMOOTH( long,  TP_RTV_ALPHA, base_rtv->tv_usec, 
D 6
			ABS(long, base_rtv->tv_usec - newmeas->tv_usec ));
E 6
I 6
			ABS(long, base_rtt->tv_usec - newmeas->tv_usec ));
E 14
I 14
D 15
	int delta = newmeas - *rtt;
E 15
I 15
D 17
	int new, old = tpcb->tp_dt_ticks;
	int delta, elapsed = tick - tpcb->tp_rttemit;
E 17
I 17
	int old = tpcb->tp_rtt;
	int delta, elapsed = ticks - tpcb->tp_rttemit;
E 17
E 15
E 14
E 6

D 14
	/* update smoothed average rtt */
	base_rtt->tv_sec = 
		SMOOTH( long,  TP_RTT_ALPHA, base_rtt->tv_sec, newmeas->tv_sec);
	base_rtt->tv_usec =
		SMOOTH( long,  TP_RTT_ALPHA, base_rtt->tv_usec, newmeas->tv_usec);

E 14
I 14
D 15
	if ((*rtt += (delta >> TP_RTT_ALPHA)) <= 0)
		*rtt = 1;
	if (delta < 0)
		delta = -delta;
	if (*rtv = ((delta - *rtv) >> TP_RTV_ALPHA) <= 0)
		*rtv = 1;
E 15
I 15
	if (tpcb->tp_rtt != 0) {
		/*
		 * rtt is the smoothed round trip time in machine clock ticks (hz).
D 16
		 * it is stored as a fixed point number, unscaled (unlike the tcp
		 * srtt.  The rationale here is that it is only significant to the
E 16
I 16
		 * It is stored as a fixed point number, unscaled (unlike the tcp
		 * srtt).  The rationale here is that it is only significant to the
E 16
		 * nearest unit of slowtimo, which is at least 8 machine clock ticks
		 * so there is no need to scale.  The smoothing is done according
		 * to the same formula as TCP (rtt = rtt*7/8 + measured_rtt/8).
		 */
		delta = elapsed - tpcb->tp_rtt;
		if ((tpcb->tp_rtt += (delta >> TP_RTT_ALPHA)) <= 0)
			tpcb->tp_rtt = 1;
		/*
		 * rtv is a smoothed accumulated mean difference, unscaled
		 * for reasons expressed above.
		 * It is smoothed with an alpha of .75, and the round trip timer
		 * will be set to rtt + 4*rtv, also as TCP does.
		 */
		if (delta < 0)
			delta = -delta;
		if ((tpcb->tp_rtv += ((delta - tpcb->tp_rtv) >> TP_RTV_ALPHA)) <= 0)
			tpcb->tp_rtv = 1;
	} else {
		/* 
		 * No rtt measurement yet - use the unsmoothed rtt.
		 * Set the variance to half the rtt (so our first
		 * retransmit happens at 3*rtt)
		 */
		tpcb->tp_rtt = elapsed;
		tpcb->tp_rtv = elapsed >> 1;
	}
	tpcb->tp_rttemit = 0;
	tpcb->tp_rxtshift = 0;
	/*
	 * Quoting TCP: "the retransmit should happen at rtt + 4 * rttvar.
	 * Because of the way we do the smoothing, srtt and rttvar
	 * will each average +1/2 tick of bias.  When we compute
	 * the retransmit timer, we want 1/2 tick of rounding and
	 * 1 extra tick because of +-1/2 tick uncertainty in the
	 * firing of the timer.  The bias will give us exactly the
	 * 1.5 tick we need.  But, because the bias is
	 * statistical, we have to test that we don't drop below
	 * the minimum feasible timer (which is 2 ticks)."
	 */
D 16
	new = (((tpcb->tp_rtt + (tpcb->tp_rtv << 2)) * PR_SLOWHZ) + hz) / hz;
	new = MAX(new + 1, tpcb->tp_peer_acktime);
	new = MAX(new, 2);
E 16
I 16
	TP_RANGESET(tpcb->tp_dt_ticks, TP_REXMTVAL(tpcb),
		tpcb->tp_peer_acktime, 128 /* XXX */);
E 16
D 17
	IFTRACE(D_RTT)
		tptraceTPCB(TPPTmisc, "oldticks ,rtv, rtt, newticks",
			old, rtv, rtt, new);
	ENDTRACE
E 17
I 17
	IFDEBUG(D_RTT)
		printf("%s tpcb 0x%x, elapsed %d, delta %d, rtt %d, rtv %d, old %d\n",
			"tp_rtt_rtv:",tpcb,elapsed,delta,tpcb->tp_rtt,tpcb->tp_rtv,old);
	ENDDEBUG
E 17
D 16
	tpcb->tp_rxtcur = tpcb->tp_dt_ticks = new;
E 16
I 16
	tpcb->tp_rxtcur = tpcb->tp_dt_ticks;
E 16
E 15
E 14
}

/*
 * CALLED FROM:
 *  tp.trans when an AK arrives
 * FUNCTION and ARGUMENTS:
 * 	Given (cdt), the credit from the AK tpdu, and 
 *	(seq), the sequence number from the AK tpdu,
 *  tp_goodack() determines if the AK acknowledges something in the send
 * 	window, and if so, drops the appropriate packets from the retransmission
 *  list, computes the round trip time, and updates the retransmission timer
 *  based on the new smoothed round trip time.
 * RETURN VALUE:
 * 	Returns 1 if
 * 	EITHER it actually acked something heretofore unacknowledged
 * 	OR no news but the credit should be processed.
 * 	If something heretofore unacked was acked with this sequence number,
 * 	the appropriate tpdus are dropped from the retransmission control list,
 * 	by calling tp_sbdrop().
 * 	No need to see the tpdu itself.
 */
int
tp_goodack(tpcb, cdt, seq, subseq)
	register struct tp_pcb	*tpcb;
	u_int					cdt;
D 15
	register SeqNum			seq, subseq;
E 15
I 15
	register SeqNum			seq;
	u_int					subseq;
E 15
{
D 15
	int 	old_fcredit = tpcb->tp_fcredit; 
E 15
I 15
	int 	old_fcredit; 
E 15
	int 	bang = 0; 	/* bang --> ack for something heretofore unacked */
I 15
	u_int	bytes_acked;
E 15

	IFDEBUG(D_ACKRECV)
D 15
		printf("goodack seq 0x%x cdt 0x%x snduna 0x%x sndhiwat 0x%x\n",
			seq, cdt, tpcb->tp_snduna, tpcb->tp_sndhiwat);
E 15
I 15
		printf("goodack tpcb 0x%x seq 0x%x cdt %d una 0x%x new 0x%x nxt 0x%x\n",
			tpcb, seq, cdt, tpcb->tp_snduna, tpcb->tp_sndnew, tpcb->tp_sndnxt);
E 15
	ENDDEBUG
	IFTRACE(D_ACKRECV)
		tptraceTPCB(TPPTgotack, 
D 15
			seq,cdt, tpcb->tp_snduna,tpcb->tp_sndhiwat,subseq); 
E 15
I 15
			seq,cdt, tpcb->tp_snduna,tpcb->tp_sndnew,subseq); 
E 15
	ENDTRACE

	IFPERF(tpcb)
D 2
		tpmeas(tpcb->tp_lref, TPtime_ack_rcvd, 0, seq, 0, 0);
E 2
I 2
		tpmeas(tpcb->tp_lref, TPtime_ack_rcvd, (struct timeval *)0, seq, 0, 0);
E 2
	ENDPERF

D 15
	if ( subseq != 0 && (subseq <= tpcb->tp_r_subseq) ) {
		/* discard the ack */
		IFTRACE(D_ACKRECV)
			tptraceTPCB(TPPTmisc, "goodack discard : subseq tp_r_subseq",
				subseq, tpcb->tp_r_subseq, 0, 0);
		ENDTRACE
		return 0;
	} else {
		tpcb->tp_r_subseq = subseq;
	}

	if ( IN_SWINDOW(tpcb, seq, 
			tpcb->tp_snduna, SEQ(tpcb, tpcb->tp_sndhiwat+1)) ) {

		IFDEBUG(D_XPD)
			dump_mbuf(tpcb->tp_sock->so_snd.sb_mb, 
				"tp_goodack snd before sbdrop");
		ENDDEBUG
D 11
		tp_sbdrop(tpcb, SEQ_SUB(tpcb, seq, 1) );
E 11
I 11
		tpsbcheck(tpcb, 0);
D 14
		tp_sbdrop(tpcb, seq);
E 14
I 14
		(void)tp_sbdrop(tpcb, seq);
E 14
		tpsbcheck(tpcb, 1);
E 11

		/* increase congestion window but don't let it get too big */
		{
			register int maxcdt = tpcb->tp_xtd_format?0xffff:0xf;
D 5
			
			if( ++tpcb->tp_cong_win > maxcdt )
				tpcb->tp_cong_win = maxcdt; 
E 5
I 5
			CONG_ACK(tpcb, seq);
E 15
I 15
	if (seq == tpcb->tp_snduna) {
		if (subseq < tpcb->tp_r_subseq ||
			(subseq == tpcb->tp_r_subseq && cdt <= tpcb->tp_fcredit)) {
		discard_the_ack:
			IFDEBUG(D_ACKRECV)
				printf("goodack discard : tpcb 0x%x subseq %d r_subseq %d\n",
					tpcb, subseq, tpcb->tp_r_subseq);
			ENDDEBUG
			goto done;
E 15
E 5
		}
I 15
		if (cdt == tpcb->tp_fcredit /*&& thus subseq > tpcb->tp_r_subseq */) {
			tpcb->tp_r_subseq = subseq;
			if (tpcb->tp_timer[TM_data_retrans] == 0)
				tpcb->tp_dupacks = 0;
			else if (++tpcb->tp_dupacks == tprexmtthresh) {
				/* partner went out of his way to signal with different
				   subsequences that he has the same lack of an expected
				   packet.  This may be an early indiciation of a loss */
E 15

D 15
		/* Compute smoothed round trip time.
D 14
		 * Only measure rtt for tp_snduna if tp_snduna was among 
D 5
		 * the last TP_RTT_NUM seq numbers sent.
E 5
I 5
		 * the last TP_RTT_NUM seq numbers sent, and if the data
E 14
I 14
		 * Only measure rtt for tp_snduna if acked and the data
E 14
		 * were not retransmitted.
E 5
		 */
D 14
		if (SEQ_GEQ(tpcb, tpcb->tp_snduna, 
D 5
			SEQ(tpcb, tpcb->tp_sndhiwat - TP_RTT_NUM))) {
E 5
I 5
			SEQ(tpcb, tpcb->tp_sndhiwat - TP_RTT_NUM))
			&& SEQ_GT(tpcb, seq, SEQ_ADD(tpcb, tpcb->tp_retrans_hiwat, 1))) {
E 14
I 14
		if (tpcb->tp_rttemit && SEQ_GT(tpcb, seq, tpcb->tp_rttseq)) {
			int x = tick - tpcb->tp_rttemit;
E 15
I 15
				SeqNum onxt = tpcb->tp_sndnxt;
				struct mbuf *onxt_m = tpcb->tp_sndnxt_m;
				u_int win = min(tpcb->tp_fcredit,
							tpcb->tp_cong_win / tpcb->tp_l_tpdusize) / 2;
I 17
				IFDEBUG(D_ACKRECV)
					printf("%s tpcb 0x%x seq 0x%x rttseq 0x%x onxt 0x%x\n",
						"goodack dupacks:", tpcb, seq, tpcb->tp_rttseq, onxt);
				ENDDEBUG
E 17
				if (win < 2)
					win = 2;
				tpcb->tp_ssthresh = win * tpcb->tp_l_tpdusize;
				tpcb->tp_timer[TM_data_retrans] = 0;
				tpcb->tp_rttemit = 0;
				tpcb->tp_sndnxt = tpcb->tp_snduna;
				tpcb->tp_sndnxt_m = 0;
				tpcb->tp_cong_win = tpcb->tp_l_tpdusize;
				tp_send(tpcb);
				tpcb->tp_cong_win = tpcb->tp_ssthresh +
					tpcb->tp_dupacks * tpcb->tp_l_tpdusize;
				if (SEQ_GT(tpcb, onxt, tpcb->tp_sndnxt)) {
					tpcb->tp_sndnxt = onxt;
					tpcb->tp_sndnxt_m = onxt_m;
				}
E 15
E 14
E 5

D 14
			struct timeval *t = &tpcb->tp_rttemit[tpcb->tp_snduna & TP_RTT_NUM];
			struct timeval x;
E 14
I 14
D 15
			if (tpcb->tp_rtt)
				tp_rtt_rtv(&(tpcb->tp_rtt), &(tpcb->tp_rtv), x);
			else {
				tpcb->tp_rtt = x;
				tpcb->tp_rtv = x >> 1;
E 15
I 15
			} else if (tpcb->tp_dupacks > tprexmtthresh) {
				tpcb->tp_cong_win += tpcb->tp_l_tpdusize;
E 15
			}
I 15
			goto done;
		}
	} else if (SEQ_LT(tpcb, seq, tpcb->tp_snduna))
		goto discard_the_ack;
	/*
	 * If the congestion window was inflated to account
	 * for the other side's cached packets, retract it.
	 */
	if (tpcb->tp_dupacks > tprexmtthresh &&
		tpcb->tp_cong_win > tpcb->tp_ssthresh)
			tpcb->tp_cong_win = tpcb->tp_ssthresh;
	tpcb->tp_r_subseq = subseq;
	old_fcredit = tpcb->tp_fcredit;
	tpcb->tp_fcredit = cdt;
	if (cdt > tpcb->tp_maxfcredit)
		tpcb->tp_maxfcredit = cdt;
	tpcb->tp_dupacks = 0;
E 15
E 14

D 14
			GET_TIME_SINCE(t, &x);

			tp_rtt_rtv( &(tpcb->tp_rtt), &(tpcb->tp_rtv), &x );

E 14
D 15
			{	/* update the global rtt, rtv stats */
D 14
				register int i =
				   (int) tpcb->tp_flags & (TPF_PEER_ON_SAMENET | TPF_NLQOS_PDN);
				tp_rtt_rtv( &(tp_stat.ts_rtt[i]), &(tp_stat.ts_rtv[i]), &x );
E 14
I 14
				int i = tpcb->tp_flags & (TPF_PEER_ON_SAMENET | TPF_NLQOS_PDN);
				tp_rtt_rtv(tp_stat.ts_rtt + i, tp_stat.ts_rtv + i, x);
E 15
I 15
	if (IN_SWINDOW(tpcb, seq, tpcb->tp_snduna, tpcb->tp_sndnew)) {
E 15
E 14

D 15
				IFTRACE(D_RTT)
					tptraceTPCB(TPPTmisc, "Global rtt, rtv: i", i, 0, 0, 0);
				ENDTRACE
			}
E 15
I 15
		tpsbcheck(tpcb, 0);
		bytes_acked = tp_sbdrop(tpcb, seq);
		tpsbcheck(tpcb, 1);
		/*
		 * If transmit timer is running and timed sequence
		 * number was acked, update smoothed round trip time.
		 * Since we now have an rtt measurement, cancel the
		 * timer backoff (cf., Phil Karn's retransmit alg.).
		 * Recompute the initial retransmit timer.
		 */
		if (tpcb->tp_rttemit && SEQ_GT(tpcb, seq, tpcb->tp_rttseq))
			tp_rtt_rtv(tpcb);
		/*
		 * If all outstanding data is acked, stop retransmit timer.
		 * If there is more data to be acked, restart retransmit
		 * timer, using current (possibly backed-off) value.
		 * OSI combines the keepalive and persistance functions.
		 * So, there is no persistance timer per se, to restart.
		 */
D 18
		tpcb->tp_timer[TM_data_retrans] =
			(seq == tpcb->tp_sndnew) ? 0 : tpcb->tp_rxtcur;
E 18
I 18
		if (tpcb->tp_class != TP_CLASS_0)
			tpcb->tp_timer[TM_data_retrans] =
				(seq == tpcb->tp_sndnew) ? 0 : tpcb->tp_rxtcur;
E 18
		/*
		 * When new data is acked, open the congestion window.
		 * If the window gives us less than ssthresh packets
		 * in flight, open exponentially (maxseg per packet).
		 * Otherwise open linearly: maxseg per window
		 * (maxseg^2 / cwnd per packet), plus a constant
		 * fraction of a packet (maxseg/8) to help larger windows
		 * open quickly enough.
		 */
		{
			u_int cw = tpcb->tp_cong_win, incr = tpcb->tp_l_tpdusize;
E 15

D 15
			IFTRACE(D_RTT)
				tptraceTPCB(TPPTmisc, 
				"Smoothed rtt: tp_snduna, (time.sec, time.usec), peer_acktime",
				tpcb->tp_snduna, time.tv_sec, time.tv_usec,
					tpcb->tp_peer_acktime);

				tptraceTPCB(TPPTmisc, 
D 14
				"(secs): emittime diff(x) rtt, rtv",
					t->tv_sec, 
					x.tv_sec, 
					tpcb->tp_rtt.tv_sec,
					tpcb->tp_rtv.tv_sec);
				tptraceTPCB(TPPTmisc, 
				"(usecs): emittime diff(x) rtt rtv",
					t->tv_usec, 
					x.tv_usec, 
					tpcb->tp_rtt.tv_usec,
					tpcb->tp_rtv.tv_usec);
E 14
I 14
					"(secs): emittime diff(x) rtt, rtv",
						tpcb->tp_rttemit, x, tpcb->tp_rtt, tpcb->tp_rtv);
E 14
			ENDTRACE

			{
				/* Update data retransmission timer based on the smoothed
				 * round trip time, peer ack time, and the pseudo-arbitrary
D 14
				 * number 4.
				 * new ticks: avg rtt + 2*dev
				 * rtt, rtv are in microsecs, and ticks are 500 ms
				 * so 1 tick = 500*1000 us = 500000 us
				 * so ticks = (rtt + 2 rtv)/500000
				 * with ticks no les than peer ack time and no less than 4
E 14
I 14
				 * number 2.
				 * new ticks: (avg rtt + 4*dev)
				 * rtt, rtv are in hz-ticks,
				 * and slowtimo-ticks are hz / 2;
				 * We want no less than peer ack time and no less than 2
E 14
				 */

D 14
				int rtt = tpcb->tp_rtt.tv_usec +
					tpcb->tp_rtt.tv_sec*1000000;
				int rtv = tpcb->tp_rtv.tv_usec +
					tpcb->tp_rtv.tv_sec*1000000;
E 14

I 14
				int rtt = tpcb->tp_rtt, rtv = tpcb->tp_rtv,
					old = tpcb->tp_dt_ticks, new;

				new = (((rtt + (rtv << 2)) << 1) + hz) / hz;
				new = MAX(new + 1, old);
				new = MAX(new, tpcb->tp_peer_acktime);
				new = MAX(new, 2);
E 14
				IFTRACE(D_RTT)
					tptraceTPCB(TPPTmisc, "oldticks ,rtv, rtt, newticks",
D 14
						tpcb->tp_dt_ticks, 
						rtv, rtt,
						(rtt/500000 + (2 * rtv)/500000));
E 14
I 14
						old, rtv, rtt, new);
E 14
				ENDTRACE
D 14
				tpcb->tp_dt_ticks = (rtt+ (2 * rtv))/500000;
				tpcb->tp_dt_ticks = MAX( tpcb->tp_dt_ticks, 
					tpcb->tp_peer_acktime);
				tpcb->tp_dt_ticks = MAX( tpcb->tp_dt_ticks,  4);
E 14
I 14
				tpcb->tp_dt_ticks = new;
E 14
			}
I 14
			tpcb->tp_rxtcur = tpcb->tp_dt_ticks;
			tpcb->tp_rxtshift = 0;

E 15
I 15
			incr = min(incr, bytes_acked);
			if (cw > tpcb->tp_ssthresh)
				incr = incr * incr / cw + incr / 8;
			tpcb->tp_cong_win =
				min(cw + incr, tpcb->tp_sock->so_snd.sb_hiwat);
E 15
E 14
		}
		tpcb->tp_snduna = seq;
I 5
D 15
		tpcb->tp_retrans = tpcb->tp_Nretrans; /* CE_BIT */
E 5

E 15
I 15
		if (SEQ_LT(tpcb, tpcb->tp_sndnxt, seq)) {
				tpcb->tp_sndnxt = seq;
				tpcb->tp_sndnxt_m = 0;
		}
E 15
		bang++;
	} 

	if( cdt != 0 && old_fcredit == 0 ) {
		tpcb->tp_sendfcc = 1;
	}
D 16
	if( cdt == 0 && old_fcredit != 0 ) {
		IncStat(ts_zfcdt);
E 16
I 16
	if (cdt == 0) {
		if (old_fcredit != 0)
			IncStat(ts_zfcdt);
		/* The following might mean that the window shrunk */
		if (tpcb->tp_timer[TM_data_retrans]) {
			tpcb->tp_timer[TM_data_retrans] = 0;
			tpcb->tp_timer[TM_sendack] = tpcb->tp_dt_ticks;
			if (tpcb->tp_sndnxt != tpcb->tp_snduna) {
				tpcb->tp_sndnxt = tpcb->tp_snduna;
				tpcb->tp_sndnxt_m = 0;
			}
		}
E 16
	}
	tpcb->tp_fcredit = cdt;
I 15
	bang |= (old_fcredit < cdt);
E 15

I 15
done:
E 15
	IFDEBUG(D_ACKRECV)
D 15
		printf("goodack returning 0x%x, bang 0x%x cdt 0x%x old_fcredit 0x%x\n",
			(bang || (old_fcredit < cdt) ), bang, cdt, old_fcredit );
E 15
I 15
		printf("goodack returns 0x%x, cdt 0x%x ocdt 0x%x cwin 0x%x\n",
			bang, cdt, old_fcredit, tpcb->tp_cong_win);
E 15
	ENDDEBUG
D 15

	return (bang || (old_fcredit < cdt)) ;
E 15
I 15
	/* if (bang) XXXXX Very bad to remove this test, but somethings broken */
		tp_send(tpcb);
	return (bang);
E 15
}

/*
 * CALLED FROM:
 *  tp_goodack()
 * FUNCTION and ARGUMENTS:
D 11
 *  drops everything up TO and INCLUDING seq # (seq)
E 11
I 11
 *  drops everything up TO but not INCLUDING seq # (seq)
E 11
 *  from the retransmission queue.
 */
D 14
static void
E 14
tp_sbdrop(tpcb, seq) 
D 11
	struct 	tp_pcb 			*tpcb;
E 11
I 11
	register struct 	tp_pcb 			*tpcb;
E 11
	SeqNum					seq;
{
D 11
	register struct tp_rtc	*s = tpcb->tp_snduna_rtc;
E 11
I 11
	struct sockbuf *sb = &tpcb->tp_sock->so_snd;
D 15
	register int i = ((int)seq)-((int)tpcb->tp_snduna);
I 14
	int	oldcc = sb->sb_cc;
E 15
I 15
	register int i = SEQ_SUB(tpcb, seq, tpcb->tp_snduna);
	int	oldcc = sb->sb_cc, oldi = i;
E 15
E 14
E 11

I 11
D 15
	if (i < 0) i += tpcb->tp_seqhalf;
E 11
	IFDEBUG(D_ACKRECV)
D 11
		printf("tp_sbdrop up through seq 0x%x\n", seq);
E 11
I 11
		printf("tp_sbdroping %d up through seq 0x%x\n", i, seq);
E 11
	ENDDEBUG
E 15
I 15
	if (i >= tpcb->tp_seqhalf)
		printf("tp_spdropping too much -- should panic");
E 15
D 11
	while (s != (struct tp_rtc *)0 && (SEQ_LEQ(tpcb, s->tprt_seq, seq))) {
		m_freem( s->tprt_data );
		tpcb->tp_snduna_rtc = s->tprt_next;
		(void) m_free( dtom( s ) );
		s = tpcb->tp_snduna_rtc;
	}
	if(tpcb->tp_snduna_rtc == (struct tp_rtc *)0)
		tpcb->tp_sndhiwat_rtc = (struct tp_rtc *) 0;
E 11
I 11
	while (i-- > 0)
		sbdroprecord(sb);
D 15
	if (SEQ_LT(tpcb, tpcb->tp_sndhiwat, seq))
		tpcb->tp_sndhiwat_m = 0;
E 15
I 15
	IFDEBUG(D_ACKRECV)
		printf("tp_sbdroping %d pkts %d bytes on %x at 0x%x\n",
			oldi, oldcc - sb->sb_cc, tpcb, seq);
	ENDDEBUG
	if (sb->sb_flags & SB_NOTIFY)
		sowwakeup(tpcb->tp_sock);
E 15
E 11
D 14

E 14
I 14
	return (oldcc - sb->sb_cc);
E 14
}

/*
 * CALLED FROM:
 * 	tp.trans on user send request, arrival of AK and arrival of XAK
 * FUNCTION and ARGUMENTS:
D 15
 * 	Emits tpdus starting at sequence number (lowseq).
E 15
I 15
 * 	Emits tpdus starting at sequence number (tpcb->tp_sndnxt).
E 15
 * 	Emits until a) runs out of data, or  b) runs into an XPD mark, or
D 15
 * 			c) it hits seq number (highseq)
E 15
I 15
 * 			c) it hits seq number (highseq) limited by cong or credit.
E 15
D 11
 * 	Removes the octets from the front of the socket buffer 
 * 	and repackages them in one mbuf chain per tpdu.
 * 	Moves the mbuf chain to the doubly linked list that runs from
 * 	tpcb->tp_sndhiwat_rtc to tpcb->tp_snduna_rtc.
E 11
 *
D 11
 * 	Creates tpdus that are no larger than <tpcb->tp_l_tpdusize - headersize>,
 *
E 11
 * 	If you want XPD to buffer > 1 du per socket buffer, you can
 * 	modifiy this to issue XPD tpdus also, but then it'll have
 * 	to take some argument(s) to distinguish between the type of DU to
D 11
 * 	hand tp_emit, the socket buffer from which to get the data, and
 * 	the chain of tp_rtc structures on which to put the data sent.
E 11
I 11
 * 	hand tp_emit.
E 11
 *
 * 	When something is sent for the first time, its time-of-send
D 15
 * 	is stashed (the last RTT_NUM of them are stashed).  When the
 * 	ack arrives, the smoothed round-trip time is figured using this value.
 * RETURN VALUE:
 * 	the highest seq # sent successfully.
E 15
I 15
 * 	is stashed (in system clock ticks rather than pf_slowtimo ticks).
 *  When the ack arrives, the smoothed round-trip time is figured
 *  using this value.
E 15
 */
I 15
void
E 15
D 2

/* For xpd marks we use mbufs of a special type with length 0;
 * the m_next field is really the seq number of the xpd tpdu that
 * must be acked before more normal data may be sent
 */

E 2
tp_send(tpcb)
	register struct tp_pcb	*tpcb;
{
	register int			len;
D 15
	register struct mbuf	*m; /* the one we're inspecting now */
	struct mbuf				*mb;/* beginning of this tpdu */
D 2
	register struct mbuf	**n;/* link field we'll be modifying when we
								take mb-->m out of the socket buffer */
E 2
	struct mbuf 			*nextrecord; /* NOT next tpdu but next sb record */
E 15
I 15
	register struct mbuf	*m;
	struct mbuf				*mb = 0;
E 15
	struct 	sockbuf			*sb = &tpcb->tp_sock->so_snd;
D 11
	int						maxsize = tpcb->tp_l_tpdusize 
										- tp_headersize(DT_TPDU_type, tpcb)
										- (tpcb->tp_use_checksum?4:0) ;
E 11
D 15
	unsigned int			eotsdu_reached=0;
	SeqNum					lowseq, highseq ;
	SeqNum					lowsave; 
E 15
I 15
	unsigned int			eotsdu = 0;
	SeqNum					highseq, checkseq;
	int						idle, idleticks, off, cong_win;
E 15
#ifdef TP_PERF_MEAS
I 9
D 15

E 15
E 9
D 14
	struct timeval 			send_start_time;
I 9
	IFPERF(tpcb)
		GET_CUR_TIME(&send_start_time);
	ENDPERF
E 14
I 14
D 17
	int			 			send_start_time = tick;
E 17
I 17
	int			 			send_start_time = ticks;
E 17
I 15
	SeqNum					oldnxt = tpcb->tp_sndnxt; 
E 15
E 14
E 9
D 21
#endif TP_PERF_MEAS
E 21
I 21
#endif /* TP_PERF_MEAS */
E 21

D 15
	lowsave =  lowseq = SEQ(tpcb, tpcb->tp_sndhiwat + 1);

	ASSERT( tpcb->tp_cong_win > 0 && tpcb->tp_cong_win < 0xffff);

	if( tpcb->tp_rx_strat & TPRX_USE_CW ) {
			/*first hiseq is temp vbl*/
		highseq = MIN(tpcb->tp_fcredit, tpcb->tp_cong_win); 
	} else {
		highseq = tpcb->tp_fcredit;
E 15
I 15
	idle = (tpcb->tp_snduna == tpcb->tp_sndnew);
	if (idle) {
		idleticks = tpcb->tp_inact_ticks - tpcb->tp_timer[TM_inact];
		if (idleticks > tpcb->tp_dt_ticks)
			/*
			 * We have been idle for "a while" and no acks are
			 * expected to clock out any data we send --
			 * slow start to get ack "clock" running again.
			 */
			tpcb->tp_cong_win = tpcb->tp_l_tpdusize;
E 15
	}
D 15
	highseq = SEQ(tpcb, tpcb->tp_snduna + highseq);
		
	SEQ_DEC(tpcb, highseq);
E 15

I 15
	cong_win = tpcb->tp_cong_win;
	highseq = SEQ(tpcb, tpcb->tp_fcredit + tpcb->tp_snduna);
	if (tpcb->tp_Xsnd.sb_mb)
		highseq = SEQ_MIN(tpcb, highseq, tpcb->tp_sndnew);
		
E 15
	IFDEBUG(D_DATA)
D 15
		printf( 
			"tp_send enter tpcb 0x%x l %d -> h %d\ndump of sb_mb:\n",
			tpcb, lowseq, highseq);
		dump_mbuf(sb->sb_mb, "sb_mb:");
E 15
I 15
		printf("tp_send enter tpcb 0x%x nxt 0x%x win %d high 0x%x\n",
				tpcb, tpcb->tp_sndnxt, cong_win, highseq);
E 15
	ENDDEBUG
	IFTRACE(D_DATA)
D 15
		tptraceTPCB( TPPTmisc, "tp_send lowsave sndhiwat snduna", 
			lowsave, tpcb->tp_sndhiwat,  tpcb->tp_snduna, 0);
		tptraceTPCB( TPPTmisc, "tp_send low high fcredit congwin", 
			lowseq, highseq, tpcb->tp_fcredit,  tpcb->tp_cong_win);
E 15
I 15
		tptraceTPCB( TPPTmisc, "tp_send sndnew snduna", 
			tpcb->tp_sndnew,  tpcb->tp_snduna, 0, 0);
		tptraceTPCB( TPPTmisc, "tp_send tpcb->tp_sndnxt win fcredit congwin", 
			tpcb->tp_sndnxt, cong_win, tpcb->tp_fcredit, tpcb->tp_cong_win);
E 15
	ENDTRACE
D 15


	if	( SEQ_GT(tpcb, lowseq, highseq) )
			return ; /* don't send, don't change hiwat, don't set timers */

D 9
	IFPERF(tpcb)
		GET_CUR_TIME(&send_start_time);
	ENDPERF

E 9
	ASSERT( SEQ_LEQ(tpcb, lowseq, highseq) );
	SEQ_DEC(tpcb, lowseq);

I 11
	if (tpcb->tp_Xsnd.sb_mb) {
		IFTRACE(D_XPD)
			tptraceTPCB( TPPTmisc,
				"tp_send XPD mark low high tpcb.Xuna", 
				lowseq, highseq, tpcb->tp_Xsnd.sb_mb, 0);
		ENDTRACE
		/* stop sending here because there are unacked XPD present
		 */
		IncStat(ts_xpd_intheway);
		goto done;
	}
E 15
E 11
	IFTRACE(D_DATA)
D 15
		tptraceTPCB( TPPTmisc, "tp_send 2 low high fcredit congwin", 
			lowseq, highseq, tpcb->tp_fcredit,  tpcb->tp_cong_win);
E 15
I 15
		tptraceTPCB( TPPTmisc, "tp_send 2 nxt high fcredit congwin", 
			tpcb->tp_sndnxt, highseq, tpcb->tp_fcredit, cong_win);
E 15
	ENDTRACE

D 3
	while( SEQ_LT( tpcb, lowseq, highseq ) ) {
		mb = m = sb->sb_mb; 
		if (m == (struct mbuf *)0) {
			break; /* empty socket buffer */
		}
E 3
I 3
D 11
	while ((SEQ_LT(tpcb, lowseq, highseq)) && (mb = m = sb->sb_mb)) {
E 3
D 2
		if ( m->m_type == TPMT_XPD ) {
E 2
I 2
		if (tpcb->tp_Xsnd.sb_mb) {
E 2
D 3
			register SeqNum Xuna = * (mtod(m, SeqNum *));
E 3
D 2
			register struct mbuf *mnext = MNULL;
E 2
			IFTRACE(D_XPD)
				tptraceTPCB( TPPTmisc,
					"tp_send XPD mark low high tpcb.Xuna", 
D 3
					Xuna, lowseq, highseq, tpcb->tp_Xuna);
E 3
I 3
					lowseq, highseq, tpcb->tp_Xsnd.sb_mb, 0);
E 3
			ENDTRACE
D 2
			if( SEQ_GEQ(tpcb, Xuna, tpcb->tp_Xuna))  {
				/* stop sending here because there are unacked XPD which were 
				 * given to us before the next data were. Leave mark in place.
				 */
				IncStat(ts_xpd_intheway);
				break;
			}
			/* otherwise, mark is obsolete; delete it */
			sbfree(sb, m); /* have to do this to delete the sb_mbcnt */
			sb->sb_mb = m->m_act;
			IncStat(ts_xpdmark_del);
			if( mnext = m_free(m) ) {
				IFTRACE(D_XPD)
					tptraceTPCB( TPPTmisc,
						"tp_send XPD mark deleted mnext old_act new_act",
						mnext, sb->sb_mb, mnext->m_act, 0);
				ENDTRACE
				IFDEBUG(D_XPD)
					printf(
			"tp_send XPD mark deleted mnext 0x%x old act 0x%x new act 0x%x\n",
						mnext, sb->sb_mb, mnext->m_act, 0);
				ENDDEBUG
				mnext->m_act = sb->sb_mb;
				sb->sb_mb = mnext;
			}
			continue;
E 2
I 2
			/* stop sending here because there are unacked XPD which were 
			 * given to us before the next data were.
			 */
			IncStat(ts_xpd_intheway);
			break;
E 2
		}
D 2
		n  = &sb->sb_mb; 
E 2
		eotsdu_reached = 0;
D 2
		len =  0;
E 2
		nextrecord = m->m_act;
D 2
		while ( eotsdu_reached == 0  &&  len < maxsize  && m != MNULL) {
			*n = m; /* meaningless first time through the loop */
E 2
I 2
		for (len = 0; m; m = m->m_next) {
E 2
			len += m->m_len; 
D 2
			if ( len > maxsize ) {
				/*  
				 * Won't use the whole mbuf - split into 2 mbufs. 
				 */
				int amount = m->m_len + maxsize - len;
				struct mbuf *mx;

				/* copy the part we are NOT using and put that back in the
				 * socket buf; leave m with this tpdu chain; adjust its fields
				 */
				IFTRACE(D_STASH)
					tptraceTPCB(TPPTmisc, 
					"tp_send SPLIT len, amount, m->m_len, tpdusize",
						len, amount, m->m_len, maxsize);
				ENDTRACE
				mx = m_copy(m, amount, m->m_len - amount); /* preserves type */
				mx->m_next = m->m_next;
				mx->m_act = m->m_act; /* preserve */

				CHANGE_MTYPE(m, TPMT_DATA);
				m->m_next = (struct mbuf *)0;
				m->m_act = (struct mbuf *)0; /* not strictly necessary */
				m->m_len = amount;

				/* would do an sbfree but don't want the mbcnt to be
				 * decremented since it was never sballoced 
				 */
				sb->sb_cc -= amount; 
				len = maxsize;
				m = mx;
				break;
			}

			/* going to use the whole mbuf */
			IFTRACE(D_STASH)
				tptraceTPCB(TPPTmisc, "tp_send whole mbuf: m_len len maxsize",
					 0, m->m_len, len, maxsize);
			ENDTRACE

			if ( m->m_type == TPMT_EOT )
E 2
I 2
			if (m->m_flags & M_EOR)
E 2
				eotsdu_reached = 1;
D 2

E 2
			sbfree(sb, m); /* reduce counts in socket buffer */
D 2
			n = &m->m_next;
			m = m->m_next;

			*n = (struct mbuf *)0;  /* unlink the to-be-sent stuff from
				the stuff still in the sb_mb so when we do the m_free
				it won't clobber part of the socket buffer */
E 2
		}
I 2
D 3
		m = sb->sb_mb = nextrecord;
E 3
I 3
		sb->sb_mb = nextrecord;
E 3
		IFTRACE(D_STASH)
			tptraceTPCB(TPPTmisc, "tp_send whole mbuf: m_len len maxsize",
				 0, mb->m_len, len, maxsize);
		ENDTRACE
E 11
I 11
D 15
	if (m = tpcb->tp_sndhiwat_m)
		mb  = m->m_nextpkt;
	else
		mb = sb->sb_mb;
	while ((SEQ_LT(tpcb, lowseq, highseq)) && mb ) {
E 15
I 15
	if (tpcb->tp_sndnxt_m)
		m = tpcb->tp_sndnxt_m;
	else {
		off = SEQ_SUB(tpcb, tpcb->tp_sndnxt, tpcb->tp_snduna);
		for (m = sb->sb_mb; m && off > 0; m = m->m_next)
			off--;
	}
send:
	/*
	 * Avoid silly window syndrome here . . . figure out how!
	 */
	checkseq = tpcb->tp_sndnum;
	if (idle && SEQ_LT(tpcb, tpcb->tp_sndnum, highseq))
D 16
		checkseq = highseq;
E 16
I 16
		checkseq = highseq; /* i.e. DON'T retain highest assigned packet */
E 16
E 15
E 11
E 2

D 11
		if ( len == 0 && !eotsdu_reached) {
			/* THIS SHOULD NEVER HAPPEN! */
			ASSERT( 0 );
			goto done;
		}

D 2
		/* sb_mb is non-null */
		if(m) {
			sb->sb_mb = m;
			if(nextrecord != m)
				m->m_act = nextrecord;
		} else
			sb->sb_mb = nextrecord;

E 2
		/* If we arrive here one of the following holds:
		 * 1. We have exactly <maxsize> octets of whole mbufs,
		 * 2. We accumulated <maxsize> octets using partial mbufs,
		 * 3. We found an TPMT_EOT or an XPD mark 
		 * 4. We hit the end of a chain through m_next.
		 *    In this case, we'd LIKE to continue with the next record,
		 *    but for the time being, for simplicity, we'll stop here.
E 11
I 11
D 15
		/* 
E 11
		 * In all cases, m points to mbuf containing first octet to be
		 * sent in the tpdu AFTER the one we're going to send now,
		 * or else m is null.
		 *
		 * The chain we're working on now begins at mb and has length <len>.
		 */
E 15
I 15
	while ((SEQ_LT(tpcb, tpcb->tp_sndnxt, highseq)) && m && cong_win > 0) {
E 15

I 11
D 15
		eotsdu_reached = (mb->m_flags & M_EOR) != 0;
		len = mb->m_pkthdr.len;
E 11
		IFTRACE(D_STASH)
			tptraceTPCB( TPPTmisc, 
				"tp_send mcopy low high eotsdu_reached len", 
				lowseq, highseq, eotsdu_reached, len);
		ENDTRACE

E 15
I 15
		eotsdu = (m->m_flags & M_EOR) != 0;
		len = m->m_pkthdr.len;
		if (tpcb->tp_sndnxt == checkseq && eotsdu == 0 &&
			len < (tpcb->tp_l_tpdusize / 2))
				break;  /* Nagle . . . . . */
		cong_win -= len;
E 15
		/* make a copy - mb goes into the retransmission list 
		 * while m gets emitted.  m_copy won't copy a zero-length mbuf.
		 */
I 15
		mb = m;
E 15
D 3
		if(len) {
			if( (m = m_copy(mb, 0, len )) == MNULL ) { 
E 3
I 3
D 11
		if (len) {
			if ((m = m_copy(mb, 0, len )) == MNULL)
E 11
I 11
		m = m_copy(mb, 0, M_COPYALL);
		if (m == MNULL)
E 11
E 3
D 15
				goto done;
D 3
			}
E 3
D 11
		} else {
			/* eotsdu reached */
			MGET(m, M_WAIT, TPMT_DATA);
D 3
			if (m == NULL)
E 3
I 3
			if (m == MNULL)
E 3
				goto done;
			m->m_len = 0;
D 3
			m->m_act = MNULL;
E 3
		}

E 11
		SEQ_INC(tpcb,lowseq);	/* it was decremented at the beginning */
D 11
		{
			struct tp_rtc *t;
			/* make an rtc and put it at the end of the chain */

			TP_MAKE_RTC( t, lowseq, eotsdu_reached, mb, len, lowseq, 
				TPMT_SNDRTC);
			t->tprt_next = (struct tp_rtc *)0;

			if ( tpcb->tp_sndhiwat_rtc != (struct tp_rtc *)0 )
				tpcb->tp_sndhiwat_rtc->tprt_next = t;
			else {
				ASSERT( tpcb->tp_snduna_rtc == (struct tp_rtc *)0 );
				tpcb->tp_snduna_rtc = t;
			}

			tpcb->tp_sndhiwat_rtc = t;
		}

E 11
		IFTRACE(D_DATA)
E 15
I 15
				break;
		IFTRACE(D_STASH)
E 15
			tptraceTPCB( TPPTmisc, 
D 4
				"tp_send emitting DT lowseq eotsdu_reached",
				lowseq, eotsdu_reached, 0, 0);
E 4
I 4
D 15
				"tp_send emitting DT lowseq eotsdu_reached len",
				lowseq, eotsdu_reached, len, 0);
E 15
I 15
				"tp_send mcopy nxt high eotsdu len", 
				tpcb->tp_sndnxt, highseq, eotsdu, len);
E 15
E 4
		ENDTRACE
D 11
		if( tpcb->tp_sock->so_error =
			tp_emit(DT_TPDU_type, tpcb, lowseq, eotsdu_reached, m) )  {
E 11
I 11
D 15
		if (mb->m_nextpkt == 0 && tpcb->tp_oktonagle) {
			SEQ_INC(tpcb, tpcb->tp_sndnum);
			tpcb->tp_oktonagle = 0;
			/* when headers are precomputed, may need to fill
E 15
I 15

		IFDEBUG(D_DATA)
			printf("tp_sending tpcb 0x%x nxt 0x%x\n",
				tpcb, tpcb->tp_sndnxt);
		ENDDEBUG
		/* when headers are precomputed, may need to fill
E 15
			   in checksum here */
D 15
		}
E 15
		if (tpcb->tp_sock->so_error =
D 15
			tp_emit(DT_TPDU_type, tpcb, lowseq, eotsdu_reached, m)) {
E 15
I 15
			tp_emit(DT_TPDU_type, tpcb, tpcb->tp_sndnxt, eotsdu, m)) {
E 15
E 11
			/* error */
D 15
			SEQ_DEC(tpcb, lowseq); 
			goto done;
E 15
I 15
			break;
E 15
		}
I 14
D 15
		/* set the transmit-time for computation of round-trip times */
		if (tpcb->tp_rttemit == 0) {
			tpcb->tp_rttemit = tick;
			tpcb->tp_rttseq = lowseq;
E 15
I 15
		m = mb->m_nextpkt;
		tpcb->tp_sndnxt_m = m;
		if (tpcb->tp_sndnxt == tpcb->tp_sndnew) {
			SEQ_INC(tpcb, tpcb->tp_sndnew);
			/*
			 * Time this transmission if not a retransmission and
			 * not currently timing anything.
			 */
			if (tpcb->tp_rttemit == 0) {
D 17
				tpcb->tp_rttemit = tick;
E 17
I 17
				tpcb->tp_rttemit = ticks;
E 17
				tpcb->tp_rttseq = tpcb->tp_sndnxt;
			}
			tpcb->tp_sndnxt = tpcb->tp_sndnew;
		} else
			SEQ_INC(tpcb, tpcb->tp_sndnxt);
		/*
		 * Set retransmit timer if not currently set.
		 * Initial value for retransmit timer is smoothed
		 * round-trip time + 2 * round-trip time variance.
		 * Initialize shift counter which is used for backoff
		 * of retransmit time.
		 */
D 18
		if (tpcb->tp_timer[TM_data_retrans] == 0) {
E 18
I 18
		if (tpcb->tp_timer[TM_data_retrans] == 0 &&
			tpcb->tp_class != TP_CLASS_0) {
E 18
			tpcb->tp_timer[TM_data_retrans] = tpcb->tp_dt_ticks;
			tpcb->tp_timer[TM_sendack] = tpcb->tp_keepalive_ticks;
			tpcb->tp_rxtshift = 0;
E 15
		}
E 14
I 11
D 15
		tpcb->tp_sndhiwat_m = mb;
		mb = mb->m_nextpkt;
E 15
E 11
D 14
		/* set the transmit-time for computation of round-trip times */
		bcopy( (caddr_t)&time, 
				(caddr_t)&( tpcb->tp_rttemit[ lowseq & TP_RTT_NUM ] ), 
				sizeof(struct timeval));

E 14
	}
D 15

done:
E 15
I 15
	if (SEQ_GT(tpcb, tpcb->tp_sndnew, tpcb->tp_sndnum))
		tpcb->tp_oktonagle = 0;
E 15
I 9
#ifdef TP_PERF_MEAS
E 9
	IFPERF(tpcb)
		{
			register int npkts;
D 14
			struct timeval send_end_time;
			register struct timeval *t;
E 14
I 14
D 17
			int	 elapsed = tick - send_start_time, *t;
E 17
I 17
			int	 elapsed = ticks - send_start_time, *t;
E 17
			struct timeval now;
E 14

D 15
			npkts = lowseq;
			SEQ_INC(tpcb, npkts);
			npkts = SEQ_SUB(tpcb, npkts, lowsave);
E 15
I 15
			npkts = SEQ_SUB(tpcb, tpcb->tp_sndnxt, oldnxt);
E 15

D 15
			if(npkts > 0) 
E 15
I 15
			if (npkts > 0) 
E 15
				tpcb->tp_Nwindow++;

			if (npkts > TP_PM_MAX) 
				npkts = TP_PM_MAX; 

D 14
			GET_TIME_SINCE(&send_start_time, &send_end_time);
E 14
			t = &(tpcb->tp_p_meas->tps_sendtime[npkts]);
D 14
			t->tv_sec =
				SMOOTH( long, TP_RTT_ALPHA, t->tv_sec, send_end_time.tv_sec);
			t->tv_usec =
				SMOOTH( long, TP_RTT_ALPHA, t->tv_usec, send_end_time.tv_usec);
E 14
I 14
			*t += (t - elapsed) >> TP_RTT_ALPHA;
E 14

D 15
			if ( SEQ_LT(tpcb, lowseq, highseq) ) {
E 15
I 15
			if (mb == 0) {
E 15
				IncPStat(tpcb, tps_win_lim_by_data[npkts] );
			} else {
				IncPStat(tpcb, tps_win_lim_by_cdt[npkts] );
				/* not true with congestion-window being used */
			}
I 14
			now.tv_sec = elapsed / hz;
			now.tv_usec = (elapsed - (hz * now.tv_sec)) * 1000000 / hz;
E 14
			tpmeas( tpcb->tp_lref, 
D 14
					TPsbsend, &send_end_time, lowsave, tpcb->tp_Nwindow, npkts);
E 14
I 14
D 15
					TPsbsend, &elapsed, lowsave, tpcb->tp_Nwindow, npkts);
E 15
I 15
					TPsbsend, &elapsed, newseq, tpcb->tp_Nwindow, npkts);
E 15
E 14
		}
	ENDPERF
I 9
D 21
#endif TP_PERF_MEAS
E 21
I 21
#endif /* TP_PERF_MEAS */
E 21
E 9

D 15
	tpcb->tp_sndhiwat = lowseq;
E 15

D 15
	if ( SEQ_LEQ(tpcb, lowsave, tpcb->tp_sndhiwat)  && 
			(tpcb->tp_class != TP_CLASS_0) ) 
			tp_etimeout(tpcb->tp_refp, TM_data_retrans, lowsave, 
				tpcb->tp_sndhiwat,
				(u_int)tpcb->tp_Nretrans, (int)tpcb->tp_dt_ticks);
E 15
	IFTRACE(D_DATA)
		tptraceTPCB( TPPTmisc, 
D 15
			"tp_send at end: sndhiwat lowseq eotsdu_reached error",
			tpcb->tp_sndhiwat, lowseq, eotsdu_reached, tpcb->tp_sock->so_error);
E 15
I 15
			"tp_send at end: new nxt eotsdu error",
			tpcb->tp_sndnew, tpcb->tp_sndnxt, eotsdu, tpcb->tp_sock->so_error);
E 15
		
	ENDTRACE
}

I 11
int TPNagleok;
int TPNagled;

tp_packetize(tpcb, m, eotsdu)
register struct tp_pcb *tpcb;
register struct mbuf *m;
int eotsdu;
{
	register struct mbuf *n;
	register struct sockbuf *sb = &tpcb->tp_sock->so_snd;
	int	maxsize = tpcb->tp_l_tpdusize 
			- tp_headersize(DT_TPDU_type, tpcb)
			- (tpcb->tp_use_checksum?4:0) ;
	int totlen = m->m_pkthdr.len;
	struct mbuf *m_split();
	/*
	 * Pre-packetize the data in the sockbuf
	 * according to negotiated mtu.  Do it here
	 * where we can safely wait for mbufs.
	 *
	 * This presumes knowledge of sockbuf conventions.
	 * TODO: allocate space for header and fill it in (once!).
	 */
D 15
	IFTRACE(D_DATA)
		tptraceTPCB(TPPTmisc,
		"SEND BF: maxsize totlen eotsdu",
			maxsize, totlen, eotsdu, 0);
E 15
I 15
	IFDEBUG(D_DATA)
		printf("SEND BF: maxsize %d totlen %d eotsdu %d sndnum 0x%x\n",
			maxsize, totlen, eotsdu, tpcb->tp_sndnum);
E 15
	ENDTRACE
	if (tpcb->tp_oktonagle) {
		if ((n = sb->sb_mb) == 0)
			panic("tp_packetize");
		while (n->m_act)
			n = n->m_act;
		if (n->m_flags & M_EOR)
			panic("tp_packetize 2");
		SEQ_INC(tpcb, tpcb->tp_sndnum);
		if (totlen + n->m_pkthdr.len < maxsize) {
			/* There is an unsent packet with space, combine data */
			struct mbuf *old_n = n;
			tpsbcheck(tpcb,3);
			n->m_pkthdr.len += totlen;
			while (n->m_next)
				n = n->m_next;
			sbcompress(sb, m, n);
			tpsbcheck(tpcb,4);
			n = old_n;
			TPNagled++;
			goto out;
		}
	}
	while (m) {
		n = m;
		if (totlen > maxsize) {
			if ((m = m_split(n, maxsize, M_WAIT)) == 0)
				panic("tp_packetize");
		} else
			m = 0;
		totlen -= maxsize;
		tpsbcheck(tpcb, 5);
		sbappendrecord(sb, n);
		tpsbcheck(tpcb, 6);
		SEQ_INC(tpcb, tpcb->tp_sndnum);
	}
out:
	if (eotsdu) {
		n->m_flags |= M_EOR;  /* XXX belongs at end */
		tpcb->tp_oktonagle = 0;
	} else {
		SEQ_DEC(tpcb, tpcb->tp_sndnum);
		tpcb->tp_oktonagle = 1;
		TPNagleok++;
	}
I 15
	IFDEBUG(D_DATA)
		printf("SEND out: oktonagle %d sndnum 0x%x\n",
			tpcb->tp_oktonagle, tpcb->tp_sndnum);
	ENDTRACE
E 15
	return 0;
}


E 11
/*
 * NAME: tp_stash()
 * CALLED FROM:
 *	tp.trans on arrival of a DT tpdu
 * FUNCTION, ARGUMENTS, and RETURN VALUE:
 * 	Returns 1 if 
 *		a) something new arrived and it's got eotsdu_reached bit on,
 * 		b) this arrival was caused other out-of-sequence things to be
 *    	accepted, or
 * 		c) this arrival is the highest seq # for which we last gave credit
 *   	(sender just sent a whole window)
 *  In other words, returns 1 if tp should send an ack immediately, 0 if 
 *  the ack can wait a while.
 *
 * Note: this implementation no longer renegs on credit, (except
 * when debugging option D_RENEG is on, for the purpose of testing
 * ack subsequencing), so we don't  need to check for incoming tpdus 
 * being in a reneged portion of the window.
 */

D 11
int
E 11
D 15
tp_stash( tpcb, e )
E 15
I 15
tp_stash(tpcb, e)
E 15
	register struct tp_pcb		*tpcb;
	register struct tp_event	*e;
{
	register int		ack_reason= tpcb->tp_ack_strat & ACK_STRAT_EACH;
									/* 0--> delay acks until full window */
									/* 1--> ack each tpdu */
D 10
	int		newrec = 0;

E 10
#ifndef lint
#define E e->ATTR(DT_TPDU)
D 21
#else lint
E 21
I 21
#else /* lint */
E 21
#define E e->ev_union.EV_DT_TPDU
D 21
#endif lint
E 21
I 21
#endif /* lint */
E 21

	if ( E.e_eot ) {
		register struct mbuf *n = E.e_data;
D 2

		/* sigh. have to go through this again! */
		/* a kludgy optimization would be to take care of this in
		 * tp_input (oh, horrors!) 
		 * BTW, don't set ack_reason here because we don't know if the
		 * sequence number is right
		 */
		while (n->m_next )
			n = n->m_next;

		n->m_act = MNULL; /* set on tp_input */
		CHANGE_MTYPE(n, TPMT_EOT);

E 2
I 2
		n->m_flags |= M_EOR;
I 3
		n->m_act = 0;
E 3
	}
E 2
		IFDEBUG(D_STASH)
D 2
			printf("EOT! changing m_type of m 0x%x\n",  n);
E 2
			dump_mbuf(tpcb->tp_sock->so_rcv.sb_mb, 
				"stash: so_rcv before appending");
			dump_mbuf(E.e_data,
				"stash: e_data before appending");
		ENDDEBUG
D 2
	}
E 2

	IFPERF(tpcb)
		PStat(tpcb, Nb_from_ll) += E.e_datalen;
		tpmeas(tpcb->tp_lref, TPtime_from_ll, &e->e_time,
D 2
				E.e_seq, PStat(tpcb, Nb_from_ll), E.e_datalen);
E 2
I 2
			E.e_seq, (u_int)PStat(tpcb, Nb_from_ll), (u_int)E.e_datalen);
E 2
	ENDPERF

D 13
	if( E.e_seq == tpcb->tp_rcvnxt ) {
E 13
I 13
	if (E.e_seq == tpcb->tp_rcvnxt) {
E 13

		IFDEBUG(D_STASH)
			printf("stash EQ: seq 0x%x datalen 0x%x eot 0x%x\n", 
			E.e_seq, E.e_datalen, E.e_eot);
		ENDDEBUG

		IFTRACE(D_STASH)
			tptraceTPCB(TPPTmisc, "stash EQ: seq len eot", 
			E.e_seq, E.e_datalen, E.e_eot, 0);
		ENDTRACE

I 13
		SET_DELACK(tpcb);

E 13
D 2
		if( E.e_datalen == 0 && E.e_eot ) {
			IFDEBUG(D_STASH)
				printf("stash EQ: appendrec\n");
			ENDDEBUG
			sbappendrecord (&tpcb->tp_sock->so_rcv, E.e_data);
			/* 'cause sbappend won't append something of length zero */
		} else {
			IFDEBUG(D_STASH)
				printf("stash EQ: plain old append\n");
			ENDDEBUG
			sbappend(&tpcb->tp_sock->so_rcv, E.e_data);
		}
E 2
I 2
		sbappend(&tpcb->tp_sock->so_rcv, E.e_data);
D 10

E 2
		if (newrec = E.e_eot ) /* ASSIGNMENT */
			ack_reason |= ACK_EOT;
E 10

		SEQ_INC( tpcb, tpcb->tp_rcvnxt );
		/* 
D 11
		 * move chains from the rtc list to the socket buffer
		 * and free the rtc header
E 11
I 11
		 * move chains from the reassembly queue to the socket buffer
E 11
		 */
D 11
		{
			register struct tp_rtc	**r =  &tpcb->tp_rcvnxt_rtc;
			register struct tp_rtc	*s = tpcb->tp_rcvnxt_rtc;
E 11
I 11
		if (tpcb->tp_rsycnt) {
			register struct mbuf **mp;
			struct mbuf **mplim;
E 11

D 11
			while (s != (struct tp_rtc *)0 && s->tprt_seq == tpcb->tp_rcvnxt) {
				*r = s->tprt_next;
E 11
I 11
			mp = tpcb->tp_rsyq + (tpcb->tp_rcvnxt % tpcb->tp_maxlcredit);
			mplim = tpcb->tp_rsyq + tpcb->tp_maxlcredit;
E 11

D 2
				if ( newrec ) {
					sbappendrecord(&tpcb->tp_sock->so_rcv, s->tprt_data);
				} else
					sbappend(&tpcb->tp_sock->so_rcv, s->tprt_data);
				newrec = s->tprt_eot;
E 2
I 2
D 11
				sbappend(&tpcb->tp_sock->so_rcv, s->tprt_data);
E 2

				SEQ_INC( tpcb, tpcb->tp_rcvnxt );

				(void) m_free( dtom( s ) );
				s = *r;
E 11
I 11
			while (tpcb->tp_rsycnt && *mp) {
				sbappend(&tpcb->tp_sock->so_rcv, *mp);
				tpcb->tp_rsycnt--;
				*mp = 0;
				SEQ_INC(tpcb, tpcb->tp_rcvnxt);
E 11
				ack_reason |= ACK_REORDER;
I 11
				if (++mp == mplim)
					mp = tpcb->tp_rsyq;
E 11
			}
		}
		IFDEBUG(D_STASH)
			dump_mbuf(tpcb->tp_sock->so_rcv.sb_mb, 
				"stash: so_rcv after appending");
		ENDDEBUG

	} else {
D 11
		register struct tp_rtc **s = &tpcb->tp_rcvnxt_rtc;
		register struct tp_rtc *r = tpcb->tp_rcvnxt_rtc;
		register struct tp_rtc *t;
E 11
I 11
		register struct mbuf **mp;
		SeqNum uwe;
E 11

		IFTRACE(D_STASH)
			tptraceTPCB(TPPTmisc, "stash Reseq: seq rcvnxt lcdt", 
			E.e_seq, tpcb->tp_rcvnxt, tpcb->tp_lcredit, 0);
		ENDTRACE

D 11
		r = tpcb->tp_rcvnxt_rtc;
		while (r != (struct tp_rtc *)0  && SEQ_LT(tpcb, r->tprt_seq, E.e_seq)) {
			s = &r->tprt_next;
			r = r->tprt_next;
		}

		if (r == (struct tp_rtc *)0 || SEQ_GT(tpcb, r->tprt_seq, E.e_seq) ) {
			IncStat(ts_dt_ooo);

			IFTRACE(D_STASH)
				tptrace(TPPTmisc,
				"tp_stash OUT OF ORDER- MAKE RTC: seq, 1st seq in list\n",
					E.e_seq, r->tprt_seq,0,0);
			ENDTRACE
			IFDEBUG(D_STASH)
				printf("tp_stash OUT OF ORDER- MAKE RTC\n");
			ENDDEBUG
			TP_MAKE_RTC(t, E.e_seq, E.e_eot, E.e_data, E.e_datalen, 0,
				TPMT_RCVRTC);

			*s = t;
			t->tprt_next = (struct tp_rtc *)r;
E 11
I 11
D 12
		if (tpcb->tp_rsyq == 0 ||
			(tpcb->tp_rsycnt == 0 &&
			 (tpcb->tp_sbmax != tpcb->tp_sock->so_rcv.sb_hiwat)))
				tp_rsyset(tpcb);
E 12
I 12
		if (tpcb->tp_rsyq == 0)
			tp_rsyset(tpcb);
E 12
		uwe = SEQ(tpcb, tpcb->tp_rcvnxt + tpcb->tp_maxlcredit);
		if (tpcb->tp_rsyq == 0 ||
						!IN_RWINDOW(tpcb, E.e_seq, tpcb->tp_rcvnxt, uwe)) {
E 11
			ack_reason = ACK_DONT;
D 11
			goto done;
		} else {
E 11
I 11
			m_freem(E.e_data);
		} else if (*(mp = tpcb->tp_rsyq + (E.e_seq % tpcb->tp_maxlcredit))) {
E 11
			IFDEBUG(D_STASH)
				printf("tp_stash - drop & ack\n");
			ENDDEBUG

			/* retransmission - drop it and force an ack */
			IncStat(ts_dt_dup);
			IFPERF(tpcb)
				IncPStat(tpcb, tps_n_ack_cuz_dup);
			ENDPERF

D 11
			m_freem( E.e_data );
E 11
I 11
			m_freem(E.e_data);
E 11
			ack_reason |= ACK_DUP;
D 11
			goto done;
E 11
I 11
		} else {
			*mp = E.e_data;
			tpcb->tp_rsycnt++;
			ack_reason = ACK_DONT;
E 11
		}
	}
D 11


E 11
D 13
	/*
	 * an ack should be sent when at least one of the
	 * following holds:
D 11
	 * a) we've received a TPDU with EOTSDU set
	 * b) the TPDU that just arrived represents the
E 11
I 11
	 * a) the TPDU that just arrived represents the
E 11
	 *    full window last advertised, or
D 11
	 * c) when seq X arrives [ where
E 11
I 11
	 * b) when seq X arrives [ where
E 11
	 * 		X = last_sent_uwe - 1/2 last_lcredit_sent 
	 * 		(the packet representing 1/2 the last advertised window) ]
	 * 		and lcredit at the time of X arrival >  last_lcredit_sent/2
	 * 		In other words, if the last ack sent advertised cdt=8 and uwe = 8
	 * 		then when seq 4 arrives I'd like to send a new ack
	 * 		iff the credit at the time of 4's arrival is > 4.
	 * 		The other end thinks it has cdt of 4 so if local cdt
	 * 		is still 4 there's no point in sending an ack, but if
	 * 		my credit has increased because the receiver has taken
	 * 		some data out of the buffer (soreceive doesn't notify
	 * 		me until the SYSTEM CALL finishes), I'd like to tell
	 * 		the other end.  
	 */
E 13
I 13
	/* there were some comments of historical interest here. */
E 13
D 11

done:
E 11
	{
		LOCAL_CREDIT(tpcb);

		if ( E.e_seq ==  tpcb->tp_sent_uwe )
			ack_reason |= ACK_STRAT_FULLWIN;

		IFTRACE(D_STASH)
			tptraceTPCB(TPPTmisc, 
				"end of stash, eot, ack_reason, sent_uwe ",
				E.e_eot, ack_reason, tpcb->tp_sent_uwe, 0); 
		ENDTRACE

		if ( ack_reason == ACK_DONT ) {
			IncStat( ts_ackreason[ACK_DONT] );
			return 0;
		} else {
			IFPERF(tpcb)
D 11
				if(ack_reason & ACK_EOT) {
					IncPStat(tpcb, tps_n_ack_cuz_eot);
				} 
E 11
				if(ack_reason & ACK_STRAT_EACH) {
					IncPStat(tpcb, tps_n_ack_cuz_strat);
				} else if(ack_reason & ACK_STRAT_FULLWIN) {
					IncPStat(tpcb, tps_n_ack_cuz_fullwin);
				} else if(ack_reason & ACK_REORDER) {
					IncPStat(tpcb, tps_n_ack_cuz_reorder);
				}
				tpmeas(tpcb->tp_lref, TPtime_ack_sent, 0, 
							SEQ_ADD(tpcb, E.e_seq, 1), 0, 0);
			ENDPERF
			{
				register int i;

				/* keep track of all reasons that apply */
				for( i=1; i<_ACK_NUM_REASONS_ ;i++) {
					if( ack_reason & (1<<i) ) 
						IncStat( ts_ackreason[i] );
				}
			}
			return 1;
		}
I 11
	}
}

/*
 * tp_rsyflush - drop all the packets on the reassembly queue.
 * Do this when closing the socket, or when somebody has changed
 * the space avaible in the receive socket (XXX).
 */
tp_rsyflush(tpcb)
register struct tp_pcb *tpcb;
{
	register struct mbuf *m, **mp;
	if (tpcb->tp_rsycnt) {
		for (mp == tpcb->tp_rsyq + tpcb->tp_maxlcredit;
									 --mp >= tpcb->tp_rsyq; )
			if (*mp) {
				tpcb->tp_rsycnt--;
				m_freem(*mp);
			}
D 18
		if (tpcb->tp_rsycnt)
			panic("tp_rsyflush");
E 18
I 18
		if (tpcb->tp_rsycnt) {
			printf("tp_rsyflush %x\n", tpcb);
			tpcb->tp_rsycnt = 0;
		}
E 18
	}
	free((caddr_t)tpcb->tp_rsyq, M_PCB);
	tpcb->tp_rsyq = 0;
}

tp_rsyset(tpcb)
register struct tp_pcb *tpcb;
{
	register struct socket *so = tpcb->tp_sock;
	int maxcredit  = tpcb->tp_xtd_format ? 0xffff : 0xf;
D 12
	caddr_t rsyq;
E 12
I 12
	int old_credit = tpcb->tp_maxlcredit;
	caddr_t	rsyq;
E 12

D 12
	tpcb->tp_sbmax = so->so_rcv.sb_hiwat;
E 12
	tpcb->tp_maxlcredit = maxcredit = min(maxcredit,
		  (so->so_rcv.sb_hiwat + tpcb->tp_l_tpdusize)/ tpcb->tp_l_tpdusize);

I 12
	if (old_credit == tpcb->tp_maxlcredit && tpcb->tp_rsyq != 0)
		return;
E 12
	maxcredit *= sizeof(struct mbuf *);
	if (tpcb->tp_rsyq)
		tp_rsyflush(tpcb);
	if (rsyq = (caddr_t)malloc(maxcredit, M_PCB, M_NOWAIT))
		bzero(rsyq, maxcredit);
	tpcb->tp_rsyq = (struct mbuf **)rsyq;
}

tpsbcheck(tpcb, i)
struct tp_pcb *tpcb;
{
	register struct mbuf *n, *m;
	register int len = 0, mbcnt = 0, pktlen;
	struct sockbuf *sb = &tpcb->tp_sock->so_snd;

	for (n = sb->sb_mb; n; n = n->m_nextpkt) {
		if ((n->m_flags & M_PKTHDR) == 0)
			panic("tpsbcheck nohdr");
		pktlen = len + n->m_pkthdr.len;
	    for (m = n; m; m = m->m_next) {
			len += m->m_len;
			mbcnt += MSIZE;
			if (m->m_flags & M_EXT)
				mbcnt += m->m_ext.ext_size;
		}
		if (len != pktlen) {
			printf("test %d; len %d != pktlen %d on mbuf 0x%x\n",
				i, len, pktlen, n);
			panic("tpsbcheck short");
		}
	}
	if (len != sb->sb_cc || mbcnt != sb->sb_mbcnt) {
		printf("test %d: cc %d != %d || mbcnt %d != %d\n", i, len, sb->sb_cc,
		    mbcnt, sb->sb_mbcnt);
		panic("tpsbcheck");
E 11
	}
}
D 7

/* class zero version */
void
tp0_stash( tpcb, e )
	register struct tp_pcb		*tpcb;
	register struct tp_event	*e;
{
#ifndef lint
#define E e->ATTR(DT_TPDU)
#else lint
#define E e->ev_union.EV_DT_TPDU
#endif lint

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
D 3

		/* sigh. have to go through this again! */
		/* a kludgy optimization would be to take care of this in
		 * tp_input (oh, horrors!) 
		 */
		while (n->m_next )
			n = n->m_next;

		n->m_act = MNULL; /* set on tp_input */

E 3
D 2
		CHANGE_MTYPE(n, TPMT_EOT);
E 2
I 2
		n->m_flags |= M_EOR;
I 3
		n->m_act = MNULL; /* set on tp_input */
E 3
E 2
	}
D 2
	if( E.e_datalen == 0 && E.e_eot ) {
		sbappendrecord (&tpcb->tp_sock->so_rcv, E.e_data);
	} else {
		sbappend(&tpcb->tp_sock->so_rcv, E.e_data);
	}
E 2
I 2
D 3
	sbappendrecord (&tpcb->tp_sock->so_rcv, E.e_data);
E 3
I 3
	sbappend(&tpcb->tp_sock->so_rcv, E.e_data);
E 3
E 2
	IFDEBUG(D_STASH)
		dump_mbuf(tpcb->tp_sock->so_rcv.sb_mb, 
			"stash 0: so_rcv after appending");
	ENDDEBUG
} 
E 7
D 2

E 2
E 1
