h13761
s 00002/00002/00255
d D 8.1 93/06/10 23:20:59 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00255
d D 7.8 93/05/25 11:52:06 bostic 9 8
c trailing comment after #else or #endif
e
s 00003/00003/00254
d D 7.7 91/09/17 19:09:38 sklower 8 7
c these changes reflect the TCP algorithm for round trip timing
c (not yet tested)
e
s 00002/00000/00255
d D 7.6 91/09/06 17:15:16 sklower 7 6
c adopt TCP's policies concerning acks & (among others) use the fast
c timeout mechanism and delayed acks.
e
s 00006/00007/00249
d D 7.5 91/06/27 22:06:15 sklower 6 5
c minor changes to compile under both new and old vm systems
e
s 00009/00000/00247
d D 7.4 91/05/06 19:24:34 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00000/00246
d D 7.3 90/06/06 17:27:17 sklower 4 2
c about the first third of the COS failures attempted fixes, chkpoint for testing.
e
s 00003/00002/00244
d R 7.3 90/05/30 17:16:21 sklower 3 2
c note version mismatches
e
s 00001/00002/00245
d D 7.2 89/04/22 11:55:28 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00247/00000/00000
d D 7.1 88/12/14 15:30:12 sklower 1 0
c date and time created 88/12/14 15:30:12 by sklower
e
u
U
t
T
I 5
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 5
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
 * $Header: tp_stat.h,v 5.4 88/11/18 17:28:38 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_stat.h,v $
 *
 * Here are the data structures in which the global
 * statistics(counters) are gathered.
 */

#ifndef __TP_STAT__
#define __TP_STAT__

struct tp_stat {
	u_long ts_param_ignored;
	u_long ts_unused3;
	u_long ts_bad_csum;

	u_long ts_inv_length;
	u_long ts_inv_pcode;
	u_long ts_inv_dutype;
	u_long ts_negotfailed;
	u_long ts_inv_dref;
	u_long ts_inv_pval;
	u_long ts_inv_sufx;
I 4
	u_long ts_inv_aclass;
E 4

	u_long ts_xtd_fmt;
	u_long ts_use_txpd;
	u_long ts_csum_off;
	u_long	ts_send_drop;
	u_long	ts_recv_drop;

	u_long ts_xpd_intheway;/* xpd mark caused data flow to stop */
	u_long ts_xpdmark_del;	/* xpd markers thrown away */
	u_long ts_dt_ooo;		/* dt tpdus received out of order */
	u_long ts_dt_niw;		/* dt tpdus received & not in window */
	u_long ts_xpd_niw;		/* xpd tpdus received & not in window */
	u_long ts_xpd_dup;		
	u_long ts_dt_dup;		/* dt tpdus received & are duplicates */

	u_long ts_zfcdt;		/* # times f credit went down to 0 */
	u_long ts_lcdt_reduced; /* 
		# times local cdt reduced on an acknowledgement.
		*/

	u_long	ts_pkt_rcvd; /* from ip */
	u_long	ts_tpdu_rcvd; /* accepted as a TPDU in tp_input */
	u_long	ts_tpdu_sent;
	u_long	ts_unused2;

	u_long	ts_retrans_cr;
	u_long	ts_retrans_cc;
	u_long	ts_retrans_dr;
	u_long	ts_retrans_dt;
	u_long	ts_retrans_xpd;
	u_long	ts_conn_gaveup;

	u_long ts_ER_sent;
	u_long	ts_DT_sent;
	u_long	ts_XPD_sent;
	u_long	ts_AK_sent;
	u_long	ts_XAK_sent;
	u_long	ts_DR_sent;
	u_long	ts_DC_sent;
	u_long	ts_CR_sent;
	u_long	ts_CC_sent;

	u_long ts_ER_rcvd;
	u_long	ts_DT_rcvd;
	u_long	ts_XPD_rcvd;
	u_long	ts_AK_rcvd;
	u_long	ts_XAK_rcvd;
	u_long	ts_DR_rcvd;
	u_long	ts_DC_rcvd;
	u_long	ts_CR_rcvd;
	u_long	ts_CC_rcvd;

	u_long	ts_Eticks;
	u_long	ts_Eexpired;
	u_long	ts_Eset;
	u_long	ts_Ecan_act;
	u_long	ts_Cticks;
	u_long	ts_Cexpired;
	u_long	ts_Cset;
	u_long	ts_Ccan_act;
	u_long	ts_Ccan_inact;
I 7
	u_long	ts_Fdelack;
	u_long	ts_Fpruned;
E 7

	u_long	ts_concat_rcvd;

	u_long	ts_zdebug; /* zero dref to test timeout on conn estab tp_input.c */
	u_long ts_ydebug; /* throw away pseudo-random pkts tp_input.c */
	u_long ts_unused5;
	u_long ts_unused; /* kludged concat to test separation tp_emit.c */
	u_long ts_vdebug; /* kludge to test input size checking tp_emit.c */
	u_long ts_unused4;
	u_long ts_ldebug; /* faked a renegging of credit */

	u_long ts_mb_small;
	u_long ts_mb_cluster;
	u_long ts_mb_len_distr[17];

	u_long ts_eot_input;
	u_long ts_eot_user;
	u_long	ts_EOT_sent;
	u_long ts_tp0_conn;
	u_long ts_tp4_conn;
	u_long ts_quench;
	u_long ts_rcvdecbit;

#define NRTT_CATEGORIES 4
	/*  The 4 categories are:
	 * 0 --> tp_flags: ~TPF_PEER_ON_SAMENET |  TPF_NL_PDN
	 * 1 --> tp_flags: ~TPF_PEER_ON_SAMENET | ~TPF_NL_PDN
	 * 2 --> tp_flags:  TPF_PEER_ON_SAMENET | ~TPF_NL_PDN
	 * 3 --> tp_flags:  TPF_PEER_ON_SAMENET |  TPF_NL_PDN
	 */
D 8
	struct timeval ts_rtt[NRTT_CATEGORIES];
	struct timeval ts_rtv[NRTT_CATEGORIES];
E 8
I 8
	int ts_rtt[NRTT_CATEGORIES];
	int ts_rtv[NRTT_CATEGORIES];
E 8

	u_long ts_ackreason[_ACK_NUM_REASONS_];
		/*  ACK_DONT 0 / ACK_STRAT_EACH 0x1 / ACK_STRAT_FULLWIN 0x4
	  	 *	ACK_DUP 0x8 / ACK_EOT 0x10  / ACK_REORDER 0x20
	  	 *	ACK_USRRCV **
	  	 *	ACK_FCC **
		 */
} tp_stat ;
I 6
#define 	TP_PM_MAX			0xa /* 10 decimal */
E 6

#define IncStat(x) tp_stat./**/x/**/++

#ifdef TP_PERF_MEAS

#define PStat(Tpcb, X) (Tpcb)->tp_p_meas->/**/X/**/
#define IncPStat(Tpcb, X) if((Tpcb)->tp_perf_on) (Tpcb)->tp_p_meas->/**/X/**/++

/* BEWARE OF MACROS like this ^^^ must be sure it's surrounded by {} if
 * it's used in an if-else statement. 
 */


/* for perf measurement stuff: maximum window size it can handle */
D 6
#define 	TP_PM_MAX			0xa /* 10 decimal */
E 6

struct tp_pmeas {
		/* the first few are distributions as a fn of window size 
		 * only keep enough space for normal format plus 1 slot for
		 * extended format, in case any windows larger than 15 are used
		 */

		/* 
		 * tps_npdusent: for each call to tp_sbsend, we inc the 
		 * element representing the number of pdus sent in this call
		 */
		int		tps_win_lim_by_cdt[TP_PM_MAX+1]; 
		int		tps_win_lim_by_data[TP_PM_MAX+1]; 
		/* 
		 * tps_sendtime: Each call to tp_sbsend() is timed.  For
		 * Each window size, we keep the running average of the time
		 * taken by tp_sbsend() for each window size.
		 */
D 8
		struct timeval	tps_sendtime[TP_PM_MAX+1]; 
E 8
I 8
		int	tps_sendtime[TP_PM_MAX+1]; 
E 8
		/*
		 * n_TMsendack: # times ack sent because timer went off
		 * n_ack_cuz_eot: # times ack sent due to EOTSDU on incoming packet
		 * n_ack_cuz_dup: # times ack sent for receiving a duplicate pkt.
		 * n_ack_cuz_fullwin: # times ack sent for receiving the full window.
		 * n_ack_cuz_doack: # times ack sent for having just reordered data.
		 */
		int		tps_n_TMsendack;
		int		tps_n_ack_cuz_eot;
		int		tps_n_ack_cuz_fullwin;
		int		tps_n_ack_cuz_reorder;
		int		tps_n_ack_cuz_dup;
		int		tps_n_ack_cuz_strat;
		/*
		 * when we send an ack: how much less than the "expected" window
		 * did we actually ack.  For example: if we last sent a credit
		 * of 10, and we're acking now for whatever reason, and have
		 * only received 6 since our last credit advertisement, we'll
		 * keep the difference, 4, in this variable.
		 */
		int		tps_ack_early[TP_PM_MAX+1]; 
		/*
		 * when we ack, for the # pkts we actually acked w/ this ack,
		 * how much cdt are we advertising?
		 * [ size of window acknowledged ] [ cdt we're giving ]
		 */
		int		tps_cdt_acked[TP_PM_MAX+1][TP_PM_MAX+1]; 

		int 	tps_AK_sent;
		int 	tps_XAK_sent;
		int 	tps_DT_sent;
		int 	tps_XPD_sent;
		int 	tps_AK_rcvd;
		int 	tps_XAK_rcvd;
		int 	tps_DT_rcvd;
		int 	tps_XPD_rcvd;

		int		Nb_from_sess;
		int		Nb_to_sess;
		int		Nb_to_ll;
		int		Nb_from_ll;
};

D 2
#define  IFPERF(tpcb)  if (tpcb->tp_perf_on &&\
					(tpcb->tp_p_meas != (struct tp_pmeas *)0 )) {
E 2
I 2
#define  IFPERF(tpcb)  if (tpcb->tp_perf_on && tpcb->tp_p_meas) {
E 2
#define  ENDPERF }

#else

D 6
#define PStat(tpcb, x)  /* no-op */
E 6
I 6
int PStat_Junk;
#define PStat(tpcb, x)  PStat_Junk
E 6
#define IncPStat(tpcb, x)  /* no-op */
I 6
#define tpmeas(a,b,c,d,e,f) 0
E 6

D 6
#ifndef STAR
#define STAR *
#endif	STAR
#define IFPERF	//*beginning of comment*/STAR
#define ENDPERF		 STAR/*end of comment*//
E 6
I 6
#define IFPERF(x)	if (0) {
#define ENDPERF }
E 6

D 9
#endif TP_PERF_MEAS
E 9
I 9
#endif /* TP_PERF_MEAS */
E 9

D 9
#endif __TP_STAT__
E 9
I 9
#endif /* __TP_STAT__ */
E 9
E 1
