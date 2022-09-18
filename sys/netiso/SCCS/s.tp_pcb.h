h30357
s 00000/00001/00329
d D 8.2 94/09/22 19:11:02 sklower 27 26
c minor fixes from cgd@alpha.bostic.com
e
s 00002/00002/00328
d D 8.1 93/06/10 23:20:53 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00327
d D 7.25 93/05/25 11:52:04 bostic 25 24
c trailing comment after #else or #endif
e
s 00003/00003/00327
d D 7.24 92/10/17 13:39:27 bostic 24 23
c make kernel includes standard
e
s 00004/00004/00326
d D 7.23 92/10/11 12:22:08 bostic 23 22
c make kernel includes standard
e
s 00002/00002/00328
d D 7.22 92/09/21 19:05:39 mckusick 22 21
c use min for MIN and max for MAX
e
s 00012/00012/00318
d D 7.21 92/05/27 16:12:51 sklower 21 20
c remember so_rcvbuf size, so that if it gets increased, we can know
c to open window
e
s 00001/00000/00329
d D 7.20 91/12/17 16:19:31 sklower 20 19
c big-or-odd-size packet option. (n x 128 instead of 2^n only)
e
s 00002/00010/00327
d D 7.19 91/10/02 20:40:05 sklower 19 18
c get rid of obsolete and unused elements and structures
e
s 00002/00002/00335
d D 7.18 91/09/30 17:54:17 sklower 18 17
c remove back pointer to entry in tp_ref table; use tp_lref instead.
e
s 00013/00034/00324
d D 7.17 91/09/26 17:02:33 sklower 17 16
c These changes represent a rewrite of retransmission policies to
c imitate the TCP algorithms more closely.  More tuning and testing need to
c be done, but the code runs at least somewhat, and these represent a checkpoint
e
s 00014/00019/00344
d D 7.16 91/09/17 19:09:37 sklower 16 15
c these changes reflect the TCP algorithm for round trip timing
c (not yet tested)
e
s 00019/00008/00344
d D 7.15 91/09/05 18:02:17 sklower 15 14
c effectively merge tp_ref structure with rest of tp_pcb;
c this version doesn't crash, but does exhibit lumpy behavior;
c ack & retrans policies need to be fixed
e
s 00007/00002/00345
d D 7.14 91/09/05 17:58:16 sklower 14 13
c gather info in one place for netstat for variable allocated tp_refs
e
s 00002/00001/00345
d D 7.13 91/08/30 12:12:41 sklower 13 12
c paranoia about freeing a tpcb while still in the list of bound tcb's
c or list of children of a given TSEL
e
s 00011/00007/00335
d D 7.12 91/08/28 12:55:58 sklower 12 11
c changes to get rid of RTC structure
e
s 00003/00009/00339
d D 7.11 91/08/15 15:44:01 sklower 11 10
c get rid of some old flags; TPF_GENERAL_ADDR means somebody is listening
c for an incomming call independent of nsap.
e
s 00002/00002/00346
d D 7.10 91/07/18 20:33:21 sklower 10 9
c this changes reflect getting rid of so_tpcb.
e
s 00009/00001/00339
d D 7.9 91/05/06 19:24:32 bostic 9 8
c new copyright; att/bsd/shared
e
s 00001/00001/00339
d D 7.8 91/04/26 14:53:56 sklower 8 7
c make tp_ref structures allocated at protocol initialization time
c so that you don't need to recompile to allow more simultaneous connections
e
s 00010/00002/00330
d D 7.7 90/06/28 19:40:19 sklower 7 6
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00001/00000/00331
d D 7.6 90/05/30 17:04:16 sklower 6 5
c ISO standard says if the version number is wrong, use default;
c I think this is stupid, so I'm gonna save the version number being used!
e
s 00058/00001/00273
d D 7.5 90/01/16 21:53:32 sklower 5 4
c Mitre decbit changes
e
s 00001/00000/00273
d D 7.4 89/08/29 13:45:26 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00001/00001/00272
d D 7.3 89/04/25 17:19:56 mckusick 3 2
c ../h => (implicitly) ../sys
e
s 00030/00052/00243
d D 7.2 89/04/22 11:55:22 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00295/00000/00000
d D 7.1 88/12/14 15:30:09 sklower 1 0
c date and time created 88/12/14 15:30:09 by sklower
e
u
U
t
T
I 9
/*-
D 26
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 26
I 26
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 9
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
 * $Header: tp_pcb.h,v 5.2 88/11/18 17:09:32 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_pcb.h,v $
I 4
D 9
 *	%W% (Berkeley) %G% *
E 9
E 4
 *
 * 
 * This file defines the transport protocol control block (tpcb).
 * and a bunch of #define values that are used in the tpcb.
 */

#ifndef  __TP_PCB__
#define  __TP_PCB__

D 23
#include "../netiso/tp_param.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_user.h"
E 23
I 23
D 24
#include <netiso/netiso/tp_param.h>
#include <netiso/netiso/tp_timer.h>
#include <netiso/netiso/tp_user.h>
E 24
I 24
#include <netiso/tp_param.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_user.h>
E 24
E 23
#ifndef sblock
D 3
#include "../h/socketvar.h"
E 3
I 3
D 23
#include "socketvar.h"
E 23
I 23
#include <sys/socketvar.h>
E 23
E 3
D 25
#endif sblock
E 25
I 25
#endif /* sblock */
E 25

/* NOTE: the code depends on REF_CLOSED > REF_OPEN > the rest, and
 * on REF_FREE being zero
 *
 * Possible improvement:
 * think about merging the tp_ref w/ the tpcb and doing a search
 * through the tpcb list, from tpb. This would slow down lookup
 * during data transfer
 * It would be a little nicer also to have something based on the
 * clock (like top n bits of the reference is part of the clock, to
 * minimize the likelihood  of reuse after a crash)
 * also, need to keep the timer servicing part to a minimum (although
 * the cost of this is probably independent of whether the timers are
 * in the pcb or in an array..
 * Last, would have to make the number of timers a function of the amount of
 * mbufs available, plus some for the frozen references.
 *
 * Possible improvement:
 * Might not need the ref_state stuff either...
 * REF_FREE could correspond to tp_state == CLOSED or nonexistend tpcb,
 * REF_OPEN to tp_state anywhere from AK_WAIT or CR_SENT to CLOSING
 * REF_OPENING could correspond to LISTENING, because that's the
 * way it's used, not because the correspondence is exact.
 * REF_CLOSED could correspond to REFWAIT
 */
#define REF_FROZEN 3	/* has ref timer only */
#define REF_OPEN 2		/* has timers, possibly active */
#define REF_OPENING 1	/* in use (has a pcb) but no timers */
#define REF_FREE 0		/* free to reallocate */

D 15
#define N_CTIMERS 		4
#define N_ETIMERS 		2
E 15
I 15
D 17
#define N_CTIMERS 		6
E 17
I 17
#define TM_NTIMERS 		6
E 17
E 15

struct tp_ref {
D 15
	u_char	 			tpr_state; /* values REF_FROZEN, etc. above */
	struct Ccallout 	tpr_callout[N_CTIMERS]; /* C timers */
	struct Ecallout		tpr_calltodo;			/* list of active E timers */
E 15
I 15
D 19
/*	u_char	 			tpr_state; /* values REF_FROZEN, etc. above */
D 17
/*	struct Ccallout 	tpr_callout[N_CTIMERS]; /* C timers */
/*	struct Ecallout		tpr_calltodo;			/* list of active E timers */
E 17
#define	tpr_state		tpr_pcb->tp_refstate
E 19
D 17
#define	tpr_callout		tpr_pcb->tp_refcallout
#define	tpr_calltodo 	tpr_pcb->tp_refcalltodo
E 17
E 15
	struct tp_pcb 		*tpr_pcb;	/* back ptr to PCB */
};

I 19
/* PER system stuff (one static structure instead of a bunch of names) */
E 19
I 14
struct tp_refinfo {
	struct tp_ref		*tpr_base;
	int					tpr_size;
I 15
	int					tpr_maxopen;
	int					tpr_numopen;
E 15
};

E 14
D 19
struct tp_param {
	/* PER system stuff (one static structure instead of a bunch of names) */
	unsigned 	tpp_configed:1;			/* Has TP been initialized? */
};


E 19
D 16
/*
 * retransmission control and performance measurement 
 */
struct tp_rtc {
	struct tp_rtc	*tprt_next; /* ptr to next rtc structure in the list */
	SeqNum 			tprt_seq;	/* seq # of this TPDU */
	int				tprt_eot;	/* Will this TPDU have the eot bit set? */
	int				tprt_octets;/* # octets in this TPDU */
	struct mbuf		*tprt_data; /* ptr to the octets of data */
};

E 16
D 7
extern
E 7
struct nl_protosw {
	int		nlp_afamily;			/* address family */
	int		(*nlp_putnetaddr)();	/* puts addresses in nl pcb */
	int		(*nlp_getnetaddr)();	/* gets addresses from nl pcb */
I 7
	int		(*nlp_cmpnetaddr)();	/* compares address in pcb with sockaddr */
E 7
	int		(*nlp_putsufx)();		/* puts transport suffixes in nl pcb */
	int		(*nlp_getsufx)();		/* gets transport suffixes from nl pcb */
	int		(*nlp_recycle_suffix)();/* clears suffix from nl pcb */
	int		(*nlp_mtu)();			/* figures out mtu based on nl used */
	int		(*nlp_pcbbind)();		/* bind to pcb for net level */
	int		(*nlp_pcbconn)();		/* connect for net level */
	int		(*nlp_pcbdisc)();		/* disconnect net level */
	int		(*nlp_pcbdetach)();		/* detach net level pcb */
	int		(*nlp_pcballoc)();		/* allocate a net level pcb */
	int		(*nlp_output)();		/* prepare a packet to give to nl */
	int		(*nlp_dgoutput)();		/* prepare a packet to give to nl */
	int		(*nlp_ctloutput)();		/* hook for network set/get options */
	caddr_t	nlp_pcblist;			/* list of xx_pcb's for connections */
D 7
} nl_protosw[];
E 7
I 7
};
E 7

D 2
struct tp_pcb_aux {
	/* addressing */
	u_short				tpa_domain;		/* domain (INET, ISO) */
	/* for compatibility with the *old* way and with INET, be sure that
	 * that lsuffix and fsuffix are aligned to a short addr.
	 * having them follow the u_short *suffixlen should suffice (choke)
	 */
	u_short				tpa_fsuffixlen;	/* foreign suffix */
	u_char				tpa_fsuffix[MAX_TSAP_SEL_LEN];
	u_short				tpa_lsuffixlen;	/* local suffix */
	u_char				tpa_lsuffix[MAX_TSAP_SEL_LEN];
#define SHORT_LSUFXP(tpcb) ((short *)((tpcb)->tp_aux->tpa_lsuffix))
#define SHORT_FSUFXP(tpcb) ((short *)((tpcb)->tp_aux->tpa_fsuffix))
E 2

D 2
	u_char 				tpa_vers;		/* protocol version */
	u_char 				tpa_peer_acktime; /* used to compute DT retrans time */

	struct sockbuf		tpa_Xsnd;		/* for expedited data */
	struct sockbuf		tpa_Xrcv;		/* for expedited data */
	SeqNum				tpa_Xsndnxt;	/* next XPD seq # to send */
	SeqNum				tpa_Xuna;		/* seq # of unacked XPD */
	SeqNum				tpa_Xrcvnxt;	/* next XPD seq # expect to recv */

	/* AK subsequencing */
	u_short				tpa_s_subseq;	/* next subseq to send */
	u_short				tpa_r_subseq;	/* highest recv subseq */

};

E 2
struct tp_pcb {
I 7
	struct tp_pcb		*tp_next;
	struct tp_pcb		*tp_prev;
	struct tp_pcb		*tp_nextlisten; /* chain all listeners */
I 18
	struct socket 		*tp_sock;		/* back ptr */
E 18
E 7
	u_short 			tp_state;		/* state of fsm */
	short 				tp_retrans;		/* # times can still retrans */
D 18
	struct tp_ref 		*tp_refp;		/* rest of pcb	*/
E 18
D 2
	struct tp_pcb_aux	*tp_aux;		/* second half of the tpcb */
E 2
	caddr_t				tp_npcb;		/* to lower layer pcb */
	struct nl_protosw	*tp_nlproto;	/* lower-layer dependent routines */
D 18
	struct socket 		*tp_sock;		/* back ptr */
E 18
I 18
	struct rtentry		**tp_routep;	/* obtain mtu; inside npcb */
E 18

D 2
#define tp_Xsnd tp_aux->tpa_Xsnd
#define tp_Xrcv tp_aux->tpa_Xrcv
E 2

	RefNum				tp_lref;	 	/* local reference */
	RefNum 				tp_fref;		/* foreign reference */

	u_int				tp_seqmask;		/* mask for seq space */
	u_int				tp_seqbit;		/* bit for seq number wraparound */
	u_int				tp_seqhalf;		/* half the seq space */

I 12
	struct mbuf			*tp_ucddata;	/* user connect/disconnect data */

E 12
D 2
#define		tp_vers	tp_aux->tpa_vers
#define		tp_peer_acktime tp_aux->tpa_peer_acktime

E 2
	/* credit & sequencing info for SENDING */
	u_short 			tp_fcredit;		/* current remote credit in # packets */
D 16

E 16
I 16
D 17
	u_short				tp_ssthresh;	/* cong_win threshold for slow start
E 17
I 17
	u_short 			tp_maxfcredit;	/* max remote credit in # packets */
	u_short				tp_dupacks;		/* intuit packet loss before rxt timo */
	u_long				tp_cong_win;	/* congestion window in bytes.
										 * see profuse comments in TCP code
										 */
	u_long				tp_ssthresh;	/* cong_win threshold for slow start
E 17
										 * exponential to linear switch
										 */
E 16
D 17
	u_short				tp_cong_win;	/* congestion window : set to 1 on
										 * source quench
										 * Minimizes the amount of retrans-
										 * missions (independently of the
										 * retrans strategy).  Increased
										 * by one for each good ack received.
										 * Minimizes the amount sent in a
										 * regular tp_send() also.
										 */
I 5
	u_int   tp_ackrcvd; /* ACKs received since the send window was updated */
	SeqNum              tp_last_retrans;
	SeqNum              tp_retrans_hiwat;
E 17
E 5
D 2
#define tp_Xsndnxt  tp_aux->tpa_Xsndnxt
#define tp_Xuna  	tp_aux->tpa_Xuna
E 2
	SeqNum				tp_snduna;		/* seq # of lowest unacked DT */
D 12
	struct tp_rtc		*tp_snduna_rtc;	/* lowest unacked stuff sent so far */
E 12
D 17
	SeqNum				tp_sndhiwat;	/* highest seq # sent so far */
E 17
I 17
	SeqNum				tp_sndnew;		/* seq # of lowest unsent DT  */
E 17
I 5
D 12

E 5
	struct tp_rtc		*tp_sndhiwat_rtc;	/* last stuff sent so far */
E 12
I 12
	SeqNum				tp_sndnum;		/* next seq # to be assigned */
D 17
	struct mbuf			*tp_sndhiwat_m; /* packet corres. to sndhiwat*/
E 17
I 17
	SeqNum				tp_sndnxt;		/* what to do next; poss. rxt */
	struct mbuf			*tp_sndnxt_m;	/* packet corres. to sndnxt*/
E 17
E 12
	int					tp_Nwindow;		/* for perf. measurement */
I 2
D 12
	struct mbuf			*tp_ucddata;	/* user connect/disconnect data */
E 12
E 2

	/* credit & sequencing info for RECEIVING */
I 17
	SeqNum				tp_rcvnxt;		/* next DT seq # expect to recv */
E 17
	SeqNum	 			tp_sent_lcdt;	/* cdt according to last ack sent */
	SeqNum	 			tp_sent_uwe;	/* uwe according to last ack sent */
I 12
D 17
	SeqNum				tp_rcvnxt;		/* next DT seq # expect to recv */
E 17
E 12
	SeqNum	 			tp_sent_rcvnxt;	/* rcvnxt according to last ack sent 
										 * needed for perf measurements only
										 */
	u_short				tp_lcredit;		/* current local credit in # packets */
D 12
	SeqNum				tp_rcvnxt;		/* next DT seq # expect to recv */
	struct tp_rtc		*tp_rcvnxt_rtc;	/* unacked stuff recvd out of order */
E 12
I 12
	u_short				tp_maxlcredit;	/* needed for reassembly queue */
D 14
	u_long				tp_sbmax;		/* needed for reassembly queue */
E 14
	struct mbuf			**tp_rsyq;		/* unacked stuff recvd out of order */
D 17
	int					tp_rsycnt;		/* number of packets */
E 17
I 17
	int					tp_rsycnt;		/* number of packets "" "" "" ""    */
I 21
	u_long				tp_rhiwat;		/* remember original RCVBUF size */
E 21
E 17
E 12
D 2
#define	tp_Xrcvnxt		tp_aux->tpa_Xrcvnxt
#define tp_domain		tp_aux->tpa_domain
#define tp_fsuffix		tp_aux->tpa_fsuffix
#define tp_fsuffixlen		tp_aux->tpa_fsuffixlen
#define tp_lsuffix		tp_aux->tpa_lsuffix
#define tp_lsuffixlen		tp_aux->tpa_lsuffixlen
E 2

I 5
	/* receiver congestion state stuff ...  */
	u_int               tp_win_recv;

	/* receive window as a scaled int (8 bit fraction part) */

	struct cong_sample {
		ushort  cs_size; 				/* current window size */
		ushort  cs_received;   			/* PDUs received in this sample */
		ushort  cs_ce_set;    /* PDUs received in this sample with CE bit set */
	} tp_cong_sample;


E 5
	/* parameters per-connection controllable by user */
	struct tp_conn_param _tp_param; 

#define	tp_Nretrans _tp_param.p_Nretrans
#define	tp_dr_ticks _tp_param.p_dr_ticks
#define	tp_cc_ticks _tp_param.p_cc_ticks
#define	tp_dt_ticks _tp_param.p_dt_ticks
#define	tp_xpd_ticks _tp_param.p_x_ticks
#define	tp_cr_ticks _tp_param.p_cr_ticks
#define	tp_keepalive_ticks _tp_param.p_keepalive_ticks
#define	tp_sendack_ticks _tp_param.p_sendack_ticks
#define	tp_refer_ticks _tp_param.p_ref_ticks
#define	tp_inact_ticks _tp_param.p_inact_ticks
#define	tp_xtd_format _tp_param.p_xtd_format
#define	tp_xpd_service _tp_param.p_xpd_service
#define	tp_ack_strat _tp_param.p_ack_strat
#define	tp_rx_strat _tp_param.p_rx_strat
#define	tp_use_checksum _tp_param.p_use_checksum
#define	tp_use_efc _tp_param.p_use_efc
#define	tp_use_nxpd _tp_param.p_use_nxpd
#define	tp_use_rcc _tp_param.p_use_rcc
#define	tp_tpdusize _tp_param.p_tpdusize
#define	tp_class _tp_param.p_class
#define	tp_winsize _tp_param.p_winsize
#define	tp_no_disc_indications _tp_param.p_no_disc_indications
#define	tp_dont_change_params _tp_param.p_dont_change_params
#define	tp_netservice _tp_param.p_netservice
I 6
#define	tp_version _tp_param.p_version
I 20
#define	tp_ptpdusize _tp_param.p_ptpdusize
E 20
E 6

D 16
	int tp_l_tpdusize;
E 16
I 16
	int					tp_l_tpdusize;
E 16
		/* whereas tp_tpdusize is log2(the negotiated max size)
		 * l_tpdusize is the size we'll use when sending, in # chars
		 */

D 16
	struct timeval	tp_rtv;					/* max round-trip time variance */
	struct timeval	tp_rtt; 					/* smoothed round-trip time */
	struct timeval 	tp_rttemit[ TP_RTT_NUM + 1 ]; 
					/* times that the last TP_RTT_NUM DT_TPDUs were emitted */
E 16
I 16
	int					tp_rtv;			/* max round-trip time variance */
	int					tp_rtt; 		/* smoothed round-trip time */
	SeqNum				tp_rttseq;		/* packet being timed */
	int					tp_rttemit;		/* when emitted, in ticks */
	int					tp_idle;		/* last activity, in ticks */
	short				tp_rxtcur;		/* current retransmit value */
	short				tp_rxtshift;	/* log(2) of rexmt exp. backoff */
D 21

E 16
	unsigned 
		tp_sendfcc:1,			/* shall next ack include FCC parameter? */
		tp_trace:1,				/* is this pcb being traced? (not used yet) */
		tp_perf_on:1,			/* 0/1 -> performance measuring on  */
		tp_reneged:1,			/* have we reneged on cdt since last ack? */
D 5
		tp_decbit:4,			/* dec bit was set, we're in reneg mode  */
E 5
I 5
		tp_decbit:3,			/* dec bit was set, we're in reneg mode  */
		tp_cebit_off:1,			/* the real DEC bit algorithms not in use */
E 5
		tp_flags:8,				/* values: */
E 21
I 21
	u_char				tp_cebit_off;	/* real DEC bit algorithms not in use */
	u_char				tp_oktonagle;	/* Last unsent pckt may be append to */
	u_char				tp_flags;		/* values: */
E 21
D 11
#define TPF_CONN_DATA_OUT	TPFLAG_CONN_DATA_OUT
#define TPF_CONN_DATA_IN	TPFLAG_CONN_DATA_IN
#define TPF_DISC_DATA_IN	TPFLAG_DISC_DATA_IN
#define TPF_DISC_DATA_OUT	TPFLAG_DISC_DATA_OUT
#define TPF_XPD_PRESENT 	TPFLAG_XPD_PRESENT 
E 11
#define TPF_NLQOS_PDN	 	TPFLAG_NLQOS_PDN
#define TPF_PEER_ON_SAMENET	TPFLAG_PEER_ON_SAMENET
I 11
#define TPF_GENERAL_ADDR	TPFLAG_GENERAL_ADDR
I 15
#define TPF_DELACK			0x8
#define TPF_ACKNOW			0x10
E 15
E 11

D 11
#define PEER_IS_LOCAL(t) \
			(((t)->tp_flags & TPF_PEER_ON_SAME_NET)==TPF_PEER_ON_SAME_NET)
#define USES_PDN(t)	\
			(((t)->tp_flags & TPF_NLQOS_PDN)==TPF_NLQOS_PDN)
E 11
I 11
#define PEER_IS_LOCAL(t)	(((t)->tp_flags & TPF_PEER_ON_SAME_NET) != 0)
#define USES_PDN(t)			(((t)->tp_flags & TPF_NLQOS_PDN) != 0)
E 11

D 12
		tp_unused:16;
E 12
I 12
D 21
		tp_oktonagle:1,			/* Last unsent packet that may be append to */
D 13
		tp_unused:15;
E 13
I 13
		tp_notdetached:1,		/* Call tp_detach before freeing XXXXXXX */
		tp_unused:14;
E 21
I 21

	unsigned 
		tp_sendfcc:1,			/* shall next ack include FCC parameter? */
		tp_trace:1,				/* is this pcb being traced? (not used yet) */
		tp_perf_on:1,			/* 0/1 -> performance measuring on  */
		tp_reneged:1,			/* have we reneged on cdt since last ack? */
		tp_decbit:3,			/* dec bit was set, we're in reneg mode  */
		tp_notdetached:1;		/* Call tp_detach before freeing XXXXXXX */
E 21
E 13
E 12

D 2
#define tp_s_subseq tp_aux->tpa_s_subseq
#define tp_r_subseq tp_aux->tpa_r_subseq
E 2
D 19

E 19
#ifdef TP_PERF_MEAS
	/* performance stats - see tp_stat.h */
D 2
	struct tp_pmeas *tp_p_meas;
E 2
I 2
	struct tp_pmeas		*tp_p_meas;
	struct mbuf			*tp_p_mbuf;
E 2
D 25
#endif TP_PERF_MEAS
E 25
I 25
#endif /* TP_PERF_MEAS */
E 25
I 19

E 19
I 2
	/* addressing */
	u_short				tp_domain;		/* domain (INET, ISO) */
	/* for compatibility with the *old* way and with INET, be sure that
	 * that lsuffix and fsuffix are aligned to a short addr.
	 * having them follow the u_short *suffixlen should suffice (choke)
	 */
	u_short				tp_fsuffixlen;	/* foreign suffix */
	char				tp_fsuffix[MAX_TSAP_SEL_LEN];
	u_short				tp_lsuffixlen;	/* local suffix */
	char				tp_lsuffix[MAX_TSAP_SEL_LEN];
#define SHORT_LSUFXP(tpcb) ((short *)((tpcb)->tp_lsuffix))
#define SHORT_FSUFXP(tpcb) ((short *)((tpcb)->tp_fsuffix))

D 15
	u_char 				tp_vers;		/* protocol version */
	u_char 				tp_peer_acktime; /* used to compute DT retrans time */
E 15
I 15
	/* Timer stuff */
	u_char 				tp_vers;			/* protocol version */
	u_char 				tp_peer_acktime;	/* used for DT retrans time */
	u_char	 			tp_refstate;		/* values REF_FROZEN, etc. above */
	struct tp_pcb		*tp_fasttimeo;		/* limit pcbs to examine */
D 17
	struct Ccallout 	tp_refcallout[N_CTIMERS]; /* C timers */
E 17
I 17
	u_int			 	tp_timer[TM_NTIMERS]; /* C timers */
E 17
D 19
	struct Ecallarg		tp_retransargs;		/* dunt ask ... */
E 19
E 15

	struct sockbuf		tp_Xsnd;		/* for expedited data */
/*	struct sockbuf		tp_Xrcv;		/* for expedited data */
#define tp_Xrcv tp_sock->so_rcv
	SeqNum				tp_Xsndnxt;	/* next XPD seq # to send */
	SeqNum				tp_Xuna;		/* seq # of unacked XPD */
	SeqNum				tp_Xrcvnxt;	/* next XPD seq # expect to recv */

	/* AK subsequencing */
	u_short				tp_s_subseq;	/* next subseq to send */
	u_short				tp_r_subseq;	/* highest recv subseq */

E 2
};
I 5

u_int	tp_start_win;

#define ROUND(scaled_int) (((scaled_int) >> 8) + (((scaled_int) & 0x80) ? 1:0))

/* to round off a scaled int with an 8 bit fraction part */

#define CONG_INIT_SAMPLE(pcb) \
	pcb->tp_cong_sample.cs_received = \
    pcb->tp_cong_sample.cs_ce_set = 0; \
D 22
    pcb->tp_cong_sample.cs_size = MAX(pcb->tp_lcredit, 1) << 1;
E 22
I 22
    pcb->tp_cong_sample.cs_size = max(pcb->tp_lcredit, 1) << 1;
E 22

#define CONG_UPDATE_SAMPLE(pcb, ce_bit) \
    pcb->tp_cong_sample.cs_received++; \
    if (ce_bit) { \
        pcb->tp_cong_sample.cs_ce_set++; \
    } \
    if (pcb->tp_cong_sample.cs_size <= pcb->tp_cong_sample.cs_received) { \
        if ((pcb->tp_cong_sample.cs_ce_set << 1) >=  \
                    pcb->tp_cong_sample.cs_size ) { \
            pcb->tp_win_recv -= pcb->tp_win_recv >> 3; /* multiply by .875 */ \
D 22
            pcb->tp_win_recv = MAX(1 << 8, pcb->tp_win_recv); \
E 22
I 22
            pcb->tp_win_recv = max(1 << 8, pcb->tp_win_recv); \
E 22
        } \
        else { \
            pcb->tp_win_recv += (1 << 8); /* add one to the scaled int */ \
        } \
        pcb->tp_lcredit = ROUND(pcb->tp_win_recv); \
        CONG_INIT_SAMPLE(pcb); \
    }
D 17

#define CONG_ACK(pcb, seq) \
{ int   newacks = SEQ_SUB(pcb, seq, pcb->tp_snduna); \
	if (newacks > 0) { \
		pcb->tp_ackrcvd += newacks; \
		if (pcb->tp_ackrcvd >= MIN(pcb->tp_fcredit, pcb->tp_cong_win)) { \
			++pcb->tp_cong_win; \
			pcb->tp_ackrcvd = 0; \
		} \
	} \
}
E 17
E 5

I 7
#ifdef KERNEL
E 7
D 16
extern struct timeval 	time;
E 16
D 8
extern struct tp_ref 	tp_ref[];
E 8
I 8
D 14
extern struct tp_ref 	*tp_ref;
E 14
I 14
extern struct tp_refinfo 	tp_refinfo;
D 16
extern struct tp_ref *tp_ref;
E 16
I 16
D 27
extern struct timeval 	time;
E 27
extern struct tp_ref	*tp_ref;
E 16
E 14
E 8
extern struct tp_param	tp_param;
I 7
extern struct nl_protosw  nl_protosw[];
extern struct tp_pcb	*tp_listeners;
D 15
extern struct tp_pcb	*tp_intercepts;
E 15
I 15
extern struct tp_pcb	*tp_ftimeolist;
E 15
#endif
E 7

D 2
#ifdef lint
#define	sototpcb(so) 	((struct tp_pcb *)0)
#define	sototpref(so)	((struct tp_ref *)0)
#define	tpcbtoso(tp)	((struct socket *)0)
#define	tpcbtoref(tp)	((struct tp_ref *)0)
#else
E 2
D 10
#define	sototpcb(so) 	((struct tp_pcb *)(so->so_tpcb))
#define	sototpref(so)	((struct tp_ref *)((so)->so_tpcb->tp_ref))
E 10
I 10
#define	sototpcb(so) 	((struct tp_pcb *)(so->so_pcb))
#define	sototpref(so)	((sototpcb(so)->tp_ref))
E 10
#define	tpcbtoso(tp)	((struct socket *)((tp)->tp_sock))
#define	tpcbtoref(tp)	((struct tp_ref *)((tp)->tp_ref))
D 2
#endif
E 2

D 25
#endif  __TP_PCB__
E 25
I 25
#endif  /* __TP_PCB__ */
E 25
E 1
