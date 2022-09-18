h49226
s 00002/00002/00079
d D 8.1 93/06/10 22:53:08 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00079
d D 7.4 91/05/29 19:20:08 sklower 4 3
c for LLC2/2, there may be many pkp's to one xcp;
c so stuff pkp in m_pkthdr.rcvif, and change conventions for pk_ctlinput to get pkp
e
s 00002/00000/00078
d D 7.3 90/06/21 12:28:46 sklower 3 2
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00013/00001/00065
d D 7.2 90/05/11 15:21:59 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00066/00000/00000
d D 7.1 90/05/11 11:19:37 sklower 1 0
c date and time created 90/05/11 11:19:37 by sklower
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
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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

/*
 *
 * hdlc control block
 *
 */

struct	hdtxq {
	struct	mbuf *head;
	struct	mbuf *tail;
};

struct	hdcb {
	struct	hdcb *hd_next;	/* pointer to next hdlc control block */
	char	hd_state;	/* link state */
	char	hd_vs;		/* send state variable */
	char	hd_vr;		/* receive state variable */
	char	hd_lastrxnr;	/* last received N(R) */
	char	hd_lasttxnr;	/* last transmitted N(R) */
	char	hd_condition;
#define TIMER_RECOVERY_CONDITION        0x01
#define REJ_CONDITION                   0x02
#define REMOTE_RNR_CONDITION            0X04
	char	hd_retxcnt;
	char	hd_xx;
	struct	hdtxq hd_txq;
	struct	mbuf *hd_retxq[MODULUS];
	char	hd_retxqi;
	char	hd_rrtimer;
	char	hd_timer;
#define SET_TIMER(hdp)		hdp->hd_timer = hd_t1
#define KILL_TIMER(hdp)		hdp->hd_timer = 0
	char	hd_dontcopy;	/* if-driver doesn't free I-frames */
	struct	ifnet *hd_ifp;	/* device's network visible interface */
I 3
	struct	ifaddr *hd_ifa;	/* device's X.25 network address */
I 4
	struct	x25config *hd_xcp;
	caddr_t	hd_pkp;		/* Level III junk */
E 4
	int	(*hd_output)();	/* separate entry for HDLC direct output */
E 3
D 4
	struct	x25config *hd_xcp;	/* copy of &hdp->hd_if->if_addr */
E 4

	/* link statistics */

	long	hd_iframes_in;
	long	hd_iframes_out;
	long	hd_rrs_in;
	long	hd_rrs_out;
	short	hd_rejs_in;
	short	hd_rejs_out;
	long	hd_window_condition;
	short	hd_invalid_ns;
	short	hd_invalid_nr;
	short	hd_timeouts;
	short	hd_resets;
	short	hd_unknown;
	short	hd_frmrs_in;
	short	hd_frmrs_out;
	short	hd_rnrs_in;
	short	hd_rnrs_out;
};

#ifdef KERNEL
struct	hdcb *hdcbhead;		/* head of linked list of hdcb's */
struct	Frmr_frame hd_frmr;	/* rejected frame diagnostic info */
struct	ifqueue hdintrq;	/* hdlc packet input queue */

int	hd_t1;			/* timer T1 value */
int	hd_t3;			/* RR send timer */
int	hd_n2;			/* frame retransmission limit */
#endif
E 1
