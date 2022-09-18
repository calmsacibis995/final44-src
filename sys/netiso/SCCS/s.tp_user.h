h62081
s 00002/00002/00134
d D 8.1 93/06/10 23:21:28 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00135
d D 7.14 93/05/25 11:52:18 bostic 14 13
c trailing comment after #else or #endif
e
s 00000/00004/00136
d D 7.13 92/10/11 12:22:14 bostic 13 12
c make kernel includes standard
e
s 00001/00001/00139
d D 7.12 91/12/17 16:19:32 sklower 12 11
c big-or-odd-size packet option. (n x 128 instead of 2^n only)
e
s 00004/00010/00136
d D 7.11 91/07/29 14:55:20 sklower 11 10
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00009/00001/00137
d D 7.10 91/05/06 19:24:43 bostic 10 9
c new copyright; att/bsd/shared
e
s 00006/00000/00132
d D 7.9 91/04/26 14:54:51 sklower 9 8
c new ancillary datum -- disconnect reason here
c instead of as errno.
e
s 00001/00000/00131
d D 7.8 90/06/28 19:40:24 sklower 8 7
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00015/00014/00116
d D 7.7 90/05/30 17:04:19 sklower 7 6
c ISO standard says if the version number is wrong, use default;
c I think this is stupid, so I'm gonna save the version number being used!
e
s 00000/00006/00130
d D 7.6 90/05/30 11:56:49 sklower 6 5
c tp_control_hdr obsoleted by cmsghdr in socket.h
e
s 00003/00001/00133
d D 7.5 89/09/21 15:14:16 sklower 5 4
c fix broken include for user programs with -DKERNEL (ugh)
e
s 00002/00000/00132
d D 7.4 89/08/29 13:45:47 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00001/00001/00131
d D 7.3 89/04/25 17:19:59 mckusick 3 2
c ../h => (implicitly) ../sys
e
s 00014/00000/00118
d D 7.2 89/04/22 11:55:49 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00118/00000/00000
d D 7.1 88/12/14 15:30:21 sklower 1 0
c date and time created 88/12/14 15:30:21 by sklower
e
u
U
t
T
I 10
/*-
D 15
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 10
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
 * $Header: tp_user.h,v 5.2 88/11/04 15:44:44 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_user.h,v $
I 2
D 10
 *	%W% (Berkeley) %G%
E 10
E 2
 *
 * These are the values a real-live user ;-) needs. 
 */

I 5
#ifndef _TYPES_
E 5
D 13
#ifdef KERNEL
D 3
#include  "../h/types.h"
E 3
I 3
D 5
#include  "types.h"
E 5
I 5
#include  "../sys/types.h"
E 5
E 3
#else KERNEL
E 13
#include  <sys/types.h>
D 13
#endif KERNEL
E 13
I 5
#endif
E 5

#ifndef __TP_USER__
#define __TP_USER__

struct tp_conn_param {
	/* PER CONNECTION parameters */
	short	p_Nretrans; 
D 7
	short p_dr_ticks;
E 7
I 7
	short	p_dr_ticks;
E 7

D 7
	short p_cc_ticks;
	short p_dt_ticks;
E 7
I 7
	short	p_cc_ticks;
	short	p_dt_ticks;
E 7

D 7
	short p_x_ticks;
	short p_cr_ticks;
E 7
I 7
	short	p_x_ticks;
	short	p_cr_ticks;
E 7

D 7
	short p_keepalive_ticks;
	short p_sendack_ticks;
E 7
I 7
	short	p_keepalive_ticks;
	short	p_sendack_ticks;
E 7

D 7
	short p_ref_ticks;
	short p_inact_ticks;
E 7
I 7
	short	p_ref_ticks;
	short	p_inact_ticks;
E 7

D 7
	short p_unused;	/* local credit fraction reported (>0) no longer used*/
	short p_winsize;
E 7
I 7
D 12
	short	p_unused;	/* was .. local credit fraction reported (>0) */
E 12
I 12
	short	p_ptpdusize;	/* preferred tpdusize/128 */
E 12
	short	p_winsize;
E 7

D 7
	u_char p_tpdusize; 	/* log 2 of size */
E 7
I 7
	u_char	p_tpdusize; 	/* log 2 of size */
E 7

	u_char	p_ack_strat;	/* see comments in tp_pcb.h */
	u_char	p_rx_strat;	/* see comments in tp_pcb.h */
	u_char	p_class;	 	/* class bitmask */
	u_char	p_xtd_format;
	u_char	p_xpd_service;
	u_char	p_use_checksum;
	u_char	p_use_nxpd; 	/* netwk expedited data: not implemented */
	u_char	p_use_rcc;	/* receipt confirmation: not implemented */
	u_char	p_use_efc;	/* explicit flow control: not implemented */
D 7
	u_char	p_no_disc_indications; /* don't deliver indic on disc */
	u_char	p_dont_change_params; /* use these params as they are */
E 7
I 7
	u_char	p_no_disc_indications;	/* don't deliver indic on disc */
	u_char	p_dont_change_params;	/* use these params as they are */
E 7
	u_char	p_netservice;
I 7
	u_char	p_version;	/* only here for checking */
E 7
};

I 2
D 6
struct tp_control_hdr {
	u_short cmsg_len;
	u_short	cmsg_type;	/* TPOPT_[CONN,DISC,CFRM]_DATA */
	u_short cmsg_level;	/* e.g. SOL_SOCKET, _TRANSPORT, etc. */
/*	u_char	cmsg_data[msg_len - sizeof(tp_control_hdr)]; */
};
E 6
/*
 * These sockopt level definitions should be considered for socket.h
 */
#define	SOL_TRANSPORT	0xfffe
#define	SOL_NETWORK	0xfffd

E 2
/* get/set socket opt commands */
#define		TPACK_WINDOW	0x0 /* ack only on full window */
#define		TPACK_EACH		0x1 /* ack every packet */

#define		TPRX_USE_CW		0x8 /* use congestion window transmit */
#define		TPRX_EACH		0x4 /* retrans each packet of a set */
#define		TPRX_FASTSTART	0x1 /* don't use slow start */

I 8
#define TPOPT_INTERCEPT		0x200
E 8
#define TPOPT_FLAGS			0x300
#define TPOPT_CONN_DATA		0x400 
#define TPOPT_DISC_DATA		0x500 
I 2
#define TPOPT_CFRM_DATA		0x600 
E 2
#define TPOPT_CDDATA_CLEAR	0x700 
I 11
#define TPOPT_MY_TSEL		0x800 
#define TPOPT_PEER_TSEL		0x900 
E 11
#define TPOPT_PERF_MEAS		0xa00
#define TPOPT_PSTATISTICS	0xb00
#define TPOPT_PARAMS		0xc00 /* to replace a bunch of the others */
D 11
#define TPOPT_MY_TSEL		0x800 
#define TPOPT_PEER_TSEL		0x900 
I 4
#define TPOPT_NGC8_ACCEPT	0xd00 /* negotiate connection requests */
E 11
I 9
#define TPOPT_DISC_REASON	0xe00

struct tp_disc_reason {
	struct cmsghdr dr_hdr;
	u_int	dr_reason;
};
E 9
E 4

/* 
 ***********************flags**********************************
 */

/* read only flags */
D 11
#define TPFLAG_DISC_DATA_OUT	(u_char)0x10 /* disc data present */
#define TPFLAG_DISC_DATA_IN		(u_char)0x20 /* disc data present */
#define TPFLAG_CONN_DATA_OUT	(u_char)0x40 /* conn data present */
#define TPFLAG_CONN_DATA_IN		(u_char)0x80 /* conn data present */
#define TPFLAG_XPD_PRESENT		(u_char)0x08 /* xpd data present */
#define TPFLAG_PEER_ON_SAMENET	(u_char)0x02
E 11
#define TPFLAG_NLQOS_PDN		(u_char)0x01
I 4
D 11
#define TPFLAG_NGC8_ACCEPT		(u_char)0x04 /* negotiate conn rq's */
E 11
I 11
#define TPFLAG_PEER_ON_SAMENET	(u_char)0x02
#define TPFLAG_GENERAL_ADDR		(u_char)0x04 /* bound to wildcard addr */
E 11
E 4


/* 
 ***********************end flags******************************
 */


D 14
#endif __TP_USER__
E 14
I 14
#endif /* __TP_USER__ */
E 14
E 1
