h44173
s 00002/00002/00165
d D 8.1 93/06/10 23:19:03 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00164
d D 7.5 93/05/25 11:51:31 bostic 5 4
c trailing comment after #else or #endif
e
s 00009/00001/00158
d D 7.4 91/05/06 18:58:57 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00158
d D 7.3 89/08/29 13:44:08 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00000/00158
d D 7.2 89/04/22 11:53:41 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00158/00000/00000
d D 7.1 88/12/14 15:29:31 sklower 1 0
c date and time created 88/12/14 15:29:31 by sklower
e
u
U
t
T
I 4
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 4
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
/* $Header: cons_pcb.h,v 4.2 88/06/29 14:59:08 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/cons_pcb.h,v $ */
I 3
D 4
/*	%W% (Berkeley) %G% */
E 4
E 3

/*
 * protocol control block for the connection oriented network service
 */

/*
 * legit port #s for cons "transport" are 0..23 for su users only, and
 * 1024..1099 for public users
 */
#define X25_SBSIZE 	512
#define	X25_PORT_RESERVED 24
#define	X25_PORT_USERMAX 1099
#define X25_FACIL_LEN_MAX  109
#define X25_PARTIAL_PKT_LEN_MAX (MLEN - sizeof(struct cons_pcb))

#ifndef ARGO_DEBUG
#define X25_TTL 600 /* 5 min */
D 5
#else ARGO_DEBUG
E 5
I 5
#else /* ARGO_DEBUG */
E 5
#define X25_TTL 120 /* 1 min */
D 5
#endif ARGO_DEBUG
E 5
I 5
#endif /* ARGO_DEBUG */
E 5

struct cons_pcb {
	struct isopcb 	_co_isopcb;
#define co_next	_co_isopcb.isop_next
/* prev used for netstat only */
#define co_prev	_co_isopcb.isop_prev
#define co_head	_co_isopcb.isop_head
#define co_laddr _co_isopcb.isop_laddr
#define co_faddr _co_isopcb.isop_faddr
#define co_lport _co_isopcb.isop_laddr.siso_tsuffix
#define co_fport _co_isopcb.isop_faddr.siso_tsuffix
#define co_route _co_isopcb.isop_route
#define co_socket _co_isopcb.isop_socket
#define	co_chanmask _co_isopcb.isop_chanmask
#define	co_negchanmask _co_isopcb.isop_negchanmask
#define	co_x25crud _co_isopcb.isop_x25crud
#define	co_x25crud_len _co_isopcb.isop_x25crud_len
	u_short 		co_state; 
	u_char 			co_flags; 
	u_short			co_ttl; /* time to live timer */
	u_short			co_init_ttl; /* initial value of ttl  */
	int 			co_channel; /* logical channel */
	struct ifnet *	co_ifp; /* interface */
	struct protosw *co_proto; 

	struct ifqueue 	co_pending; /* queue data to send when connection
						completes*/
#define MAX_DTE_LEN 0x7 /* 17 bcd digits */
	struct dte_addr	co_peer_dte;
	struct	cons_pcb *co_myself; /* DEBUGGING AID */
};

/*
 * X.25 Packet types 
 */
#define XPKT_DATA		1
#define XPKT_INTERRUPT	2
#define XPKT_FLOWCONTROL 3 /* not delivered? */

/*
 * pcb xtates
 */

#define	CLOSED		0x0
#define	LISTENING	0x1
#define	CLOSING		0x2
/* USABLE STATES MUST BE LAST */
#define	CONNECTING	0x3
#define	ACKWAIT		0x4
#define	OPEN		0x5
#define MIN_USABLE_STATE CONNECTING

#define	cons_NSTATES		0x6


/* type */
#define CONSF_OCRE	0x40 /* created on OUTPUT */
#define CONSF_ICRE	0x20 /* created on INPUT */
#define CONSF_unused	0x10 /* not used */
#define CONSF_unused2	0x08 /* not used */
#define CONSF_DGM		0x04 /* for dgm use only */
#define CONSF_XTS		0x02 /* for cons-as-transport-service */
#define CONSF_LOOPBACK	0x01 /* loopback was on when connection commenced */

#define X_NOCHANNEL 0x80


struct cons_stat {
	u_int co_intr;	/* input from eicon board */
	u_int co_restart; /* ecn_restart() request issued to board */
	u_int co_slowtimo; /* times slowtimo called */
	u_int co_timedout; /* connections closed by slowtimo */
	u_int co_ack; /* ECN_ACK indication came from eicon board */
	u_int co_receive; /* ECN_RECEIVE indication came from eicon board */
	u_int co_send; /* ECN_SEND request issued to board */
	u_int co_reset_in; /* ECN_RESET indication came from eicon board */
	u_int co_reset_out; /* ECN_RESET issued to the eicon board */
	u_int co_clear_in; /* ECN_CLEAR indication came from eicon board */
	u_int co_clear_out; /* ECN_CLEAR request issued to board */
	u_int co_refuse; /* ECN_REFUSE indication came from eicon board */
	u_int co_accept; /* ECN_ACCEPT indication came from eicon board */
	u_int co_connect; /* ECN_CONNECT indication came from eicon board */
	u_int co_call; /* ECN_CALL request issued to board */
	u_int co_Rdrops; /* bad pkt came from ll */
	u_int co_Xdrops; /* can't keep up */

	u_int	co_intrpt_pkts_in; /* interrupt packets in */
	u_int co_avg_qlen;
	u_int co_avg_qdrop;
	u_int co_active;

	u_int co_noresources;
	u_int co_parse_facil_err;
	u_int co_addr_proto_consist_err;
	u_int co_no_copcb;
} cons_stat;

u_char x25_error_stats[CONL_ERROR_MAX + 1];

struct ifqueue consintrq; 

/* reasons for clear are in a data mbuf chained to a clear ecn_request */
struct e_clear_data 				{
	u_char ecd_cause;
	u_char ecd_diagnostic;
};

#ifdef KERNEL
#define IncStat(XYZ) cons_stat.XYZ++
D 5
#endif KERNEL
E 5
I 5
#endif /* KERNEL */
E 5
E 1
