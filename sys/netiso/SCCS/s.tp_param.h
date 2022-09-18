h26075
s 00002/00002/00339
d D 8.1 93/06/10 23:20:44 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00333
d D 7.13 93/05/25 11:52:00 bostic 13 12
c trailing comment after #else or #endif
e
s 00003/00003/00338
d D 7.12 92/10/11 12:22:05 bostic 12 11
c make kernel includes standard
e
s 00008/00009/00333
d D 7.11 91/10/02 20:53:01 sklower 11 10
c define REXMTVAL & RANGESET macros for rtt timer calculation;
c declare associated variables; get rid of some unused defines;
c define tpdu options for ptpdusize & inactivity timer value.
e
s 00005/00009/00337
d D 7.10 91/09/26 17:02:45 sklower 10 9
c These changes represent a rewrite of retransmission policies to
c imitate the TCP algorithms more closely.  More tuning and testing need to
c be done, but the code runs at least somewhat, and these represent a checkpoint
e
s 00008/00005/00338
d D 7.9 91/09/03 21:23:15 sklower 9 8
c now that SO_RCVBUF calls down, calculate maxcredit, and use in
c LOCAL_CREDIT macro.
e
s 00004/00000/00339
d D 7.8 91/06/27 22:06:18 sklower 8 7
c minor changes to compile under both new and old vm systems
e
s 00009/00001/00330
d D 7.7 91/05/06 19:24:29 bostic 7 6
c new copyright; att/bsd/shared
e
s 00005/00002/00326
d D 7.6 91/04/26 15:20:59 sklower 6 5
c max number of conncurrent connections now settable without recompiling
e
s 00014/00006/00314
d D 7.5 90/01/16 21:59:03 sklower 5 4
c mitre decbit changes
e
s 00001/00000/00319
d D 7.4 89/08/29 13:45:23 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00001/00001/00318
d D 7.3 89/04/25 17:19:54 mckusick 3 2
c ../h => (implicitly) ../sys
e
s 00003/00003/00316
d D 7.2 89/04/22 11:55:16 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00319/00000/00000
d D 7.1 88/12/14 15:30:07 sklower 1 0
c date and time created 88/12/14 15:30:07 by sklower
e
u
U
t
T
I 7
/*-
D 14
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
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
 *
 * $Header: tp_param.h,v 5.3 88/11/18 17:28:18 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_param.h,v $
I 4
D 7
 *	%W% (Berkeley) %G% *
E 7
E 4
 *
 */

#ifndef __TP_PARAM__
#define __TP_PARAM__


/******************************************************
 * compile time parameters that can be changed
 *****************************************************/

#define 	TP_CLASSES_IMPLEMENTED 0x11 /* zero and 4 */

#define		TP_DECBIT_CLEAR_COUNT	3

D 6
#define 	N_TPREF				100
E 6
I 6
/*#define 	N_TPREF				100 */
#ifdef KERNEL
extern int N_TPREF;
#endif
E 6

D 2
#define 	TP_SOCKBUFSIZE		4096
#define 	TP0_SOCKBUFSIZE		512
E 2
I 2
#define 	TP_SOCKBUFSIZE		((u_long)4096)
#define 	TP0_SOCKBUFSIZE		((u_long)512)
E 2
#define		MAX_TSAP_SEL_LEN	64

/* maximum tpdu size we'll accept: */
#define 	TP_TPDUSIZE			0xc		/* 4096 octets for classes 1-4*/
#define 	TP0_TPDUSIZE		0xb		/* 2048 octets for class 0 */
#define 	TP_DFL_TPDUSIZE		0x7		/* 128 octets default */
	/* NOTE: don't ever negotiate 8192 because could get 
	 * wraparound in checksumming
	 * (No mtu is likely to be larger than 4K anyway...)
	 */
D 6
#define		TP_NRETRANS			1
E 6
I 6
D 10
#define		TP_NRETRANS			5 /* was 1; cray uses 6 */
E 10
I 10
#define		TP_NRETRANS			12		/* TCP_MAXRXTSHIFT + 1 */
#define		TP_MAXRXTSHIFT		6		/* factor of 64 */
E 10
E 6
#define		TP_MAXPORT			0xefff

D 10
#define		TP_RTT_NUM			0x7
E 10
/* ALPHA: to be used in the context: gain= 1/(2**alpha), or 
 * put another way, gaintimes(x) (x)>>alpha (forgetting the case alpha==0) 
 */
#define 	TP_RTT_ALPHA		3 
#define 	TP_RTV_ALPHA		2
I 11
#define		TP_REXMTVAL(tpcb)\
	((tp_rttadd + (tpcb)->tp_rtt + ((tpcb)->tp_rtv) << 2) / tp_rttdiv)
#define		TP_RANGESET(tv, value, min, max) \
	((tv = value) > (max) ? (tv = max) : (tv < min ? tv = min : tv))
E 11

/*
 * not sure how to treat data on disconnect 
 */
#define 	T_CONN_DATA			0x1
#define 	T_DISCONNECT		0x2
#define 	T_DISC_DATA			0x4
#define 	T_XDATA				0x8

#define ISO_CLNS	 0
#define IN_CLNS	 	 1
#define ISO_CONS	 2
#define ISO_COSNS	 3
#define TP_MAX_NETSERVICES 3

/* Indices into tp stats ackreason[i] */
#define _ACK_DONT_ 0
#define _ACK_STRAT_EACH_ 0x1
#define _ACK_STRAT_FULLWIN_ 0x2
#define _ACK_DUP_ 0x3
#define _ACK_EOT_ 0x4
#define _ACK_REORDER_ 0x5
#define _ACK_USRRCV_ 0x6
#define _ACK_FCC_ 0x7
#define _ACK_NUM_REASONS_ 0x8

/* masks for use in tp_stash() */
#define ACK_DONT 			0
#define ACK_STRAT_EACH		(1<< _ACK_STRAT_EACH_)
#define ACK_STRAT_FULLWIN	(1<< _ACK_STRAT_FULLWIN_)
#define ACK_DUP 			(1<< _ACK_DUP_)
#define ACK_EOT				(1<< _ACK_EOT_)
#define ACK_REORDER			(1<< _ACK_REORDER_)

/******************************************************
 * constants used in the protocol 
 *****************************************************/

#define		TP_VERSION 			0x1

#define 	TP_MAX_HEADER_LEN	256

#define 	TP_MIN_TPDUSIZE		0x7		/* 128 octets */
#define 	TP_MAX_TPDUSIZE		0xd		/* 8192 octets */

#define		TP_MAX_XPD_DATA		0x10	/* 16 octets */
#define		TP_MAX_CC_DATA		0x20	/* 32 octets */
#define		TP_MAX_CR_DATA		TP_MAX_CC_DATA
#define		TP_MAX_DR_DATA		0x40	/* 64 octets */

#define		TP_XTD_FMT_BIT 	0x80000000
#define		TP_XTD_FMT_MASK	0x7fffffff
#define		TP_NML_FMT_BIT 	0x80
#define		TP_NML_FMT_MASK	0x7f

/*  
 * values for the tpdu_type field, 2nd byte in a tpdu 
 */

#define TP_MIN_TPDUTYPE 0x1

#define XPD_TPDU_type	0x1
#define XAK_TPDU_type	0x2
#define GR_TPDU_type	0x3	
#define AK_TPDU_type	0x6
#define ER_TPDU_type	0x7
#define DR_TPDU_type	0x8
#define DC_TPDU_type	0xc
#define CC_TPDU_type	0xd
#define CR_TPDU_type	0xe
#define DT_TPDU_type	0xf

#define TP_MAX_TPDUTYPE 0xf

/*
 * identifiers for the variable-length options in tpdus 
 */

#define		TPP_acktime			0x85
#define		TPP_residER			0x86
#define		TPP_priority		0x87
#define		TPP_transdelay		0x88
#define		TPP_throughput		0x89
#define		TPP_subseq			0x8a
#define		TPP_flow_cntl_conf	0x8c	/* not implemented */
#define		TPP_addl_info		0xe0
#define		TPP_tpdu_size		0xc0
#define		TPP_calling_sufx	0xc1
#define		TPP_invalid_tpdu	0xc1	/* the bozos used a value twice */
#define		TPP_called_sufx		0xc2
#define		TPP_checksum		0xc3
#define		TPP_vers			0xc4
#define		TPP_security		0xc5
#define		TPP_addl_opt		0xc6
#define		TPP_alt_class		0xc7
#define		TPP_perf_meas		0xc8	/* local item : perf meas on, svp */
I 11
#define		TPP_ptpdu_size		0xf0	/* preferred TPDU size */
#define		TPP_inact_time		0xf2	/* inactivity time exchanged */
E 11

I 11

E 11
/******************************************************
 * Some fundamental data types
 *****************************************************/
#ifndef		TRUE
#define		TRUE				1
D 13
#endif		TRUE
E 13
I 13
#endif		/* TRUE */
E 13

#ifndef		FALSE
#define		FALSE				0
D 13
#endif		FALSE
E 13
I 13
#endif		/* FALSE */
E 13

#define		TP_LOCAL				22
#define		TP_FOREIGN				33

#ifndef 	EOK
#define 	EOK 	0
D 13
#endif  	EOK
E 13
I 13
#endif  	/* EOK */
E 13

#define 	TP_CLASS_0 	(1<<0)
#define 	TP_CLASS_1 	(1<<1)
#define 	TP_CLASS_2 	(1<<2)
#define 	TP_CLASS_3 	(1<<3)
#define 	TP_CLASS_4 	(1<<4)

#define 	TP_FORCE 	0x1
#define 	TP_STRICT 	0x2

#ifndef 	MNULL
#define 	MNULL				(struct mbuf *)0
D 13
#endif 	MNULL
E 13
I 13
#endif 	/* MNULL */
E 13
D 3
	/* if ../h/mbuf.h gets MT_types up to 0x40, these will 
E 3
I 3
	/* if ../sys/mbuf.h gets MT_types up to 0x40, these will 
E 3
	 * have to be changed:
	 */
#define 	MT_XPD 				0x44	
#define 	MT_EOT 				0x40

#define		TP_ENOREF			0x80000000

typedef 	unsigned int	SeqNum;
typedef		unsigned short	RefNum;
typedef		int				ProtoHook;

D 11

E 11
/******************************************************
D 11
 * Some fundamental constants
 *****************************************************/

#define TP_MIN_WIN	2048
#define TP_MAX_WIN 16384
#define TP_MAX_WIN_UNPRIV 8192

/******************************************************
E 11
 * Macro used all over, for driver
 *****************************************************/

#define  DoEvent(x) \
  ((E.ev_number=(x)),(tp_driver(tpcb,&E)))

/******************************************************
 * Some macros used all over, for timestamping
 *****************************************************/

#define GET_CUR_TIME(tvalp) ((*tvalp) = time)

#define GET_TIME_SINCE(oldtvalp, diffp) {\
	(diffp)->tv_sec = time.tv_sec - (oldtvalp)->tv_sec;\
	(diffp)->tv_usec = time.tv_usec - (oldtvalp)->tv_usec;\
	if( (diffp)->tv_usec <0 ) {\
		(diffp)->tv_sec --;\
		(diffp)->tv_usec = 1000000 - (diffp)->tv_usec;\
	}\
}
			
/******************************************************
 * Some macros used for address families
 *****************************************************/

#define satosiso(ADDR) ((struct sockaddr_iso *)(ADDR))
#define satosin(ADDR) ((struct sockaddr_in *)(ADDR))

/******************************************************
 * Macro used for changing types of mbufs
 *****************************************************/

#define CHANGE_MTYPE(m, TYPE)\
	if((m)->m_type != TYPE) { \
		mbstat.m_mtypes[(m)->m_type]--; mbstat.m_mtypes[TYPE]++; \
		(m)->m_type = TYPE; \
	}

/******************************************************
 * Macros used for adding options to a tpdu header and for
 * parsing the headers.
 * Options are variable-length and must be bcopy-d because on the
 * RT your assignments must be N-word aligned for objects of length
 * N.  Such a drag.
 *****************************************************/

struct tp_vbp {
	u_char	tpv_code;
	char 	tpv_len;
	char	tpv_val;
};
#define vbptr(x) ((struct tp_vbp *)(x))
#define vbval(x,type) (*((type *)&(((struct tp_vbp *)(x))->tpv_val)))
#define vbcode(x) (vbptr(x)->tpv_code)
#define vblen(x) (vbptr(x)->tpv_len)

#define vb_putval(dst,type,src)\
	bcopy((caddr_t)&(src),(caddr_t)&(((struct tp_vbp *)(dst))->tpv_val),\
	sizeof(type))

#define vb_getval(src,type,dst)\
bcopy((caddr_t)&(((struct tp_vbp *)(src))->tpv_val),(caddr_t)&(dst),sizeof(type))

#define ADDOPTION(type, DU, len, src)\
{	register caddr_t P;\
	P = (caddr_t)(DU) + (int)((DU)->tpdu_li);\
	vbptr(P)->tpv_code = type;\
	vbptr(P)->tpv_len = len;\
D 2
	bcopy((caddr_t)&src, (caddr_t)&(vbptr(P)->tpv_val), (int)len);\
E 2
I 2
	bcopy((caddr_t)&src, (caddr_t)&(vbptr(P)->tpv_val), (unsigned)len);\
E 2
	DU->tpdu_li += len+2;/* 1 for code, 1 for length */\
}
/******************************************************
 * Macro for the local credit:
 * uses max transmission unit for the ll
 * (as modified by the max TPDU size negotiated) 
 *****************************************************/

#if defined(ARGO_DEBUG)&&!defined(LOCAL_CREDIT_EXPAND)
#define LOCAL_CREDIT(tpcb) tp_local_credit(tpcb)
#else
D 9
#define LOCAL_CREDIT( tpcb ) {\
E 9
I 9
D 10
#define LOCAL_CREDIT(tpcb) {\
E 10
I 10
#define LOCAL_CREDIT(tpcb) { if (tpcb->tp_rsycnt == 0) {\
E 10
E 9
D 5
	register struct sockbuf *xxsb = &((tpcb)->tp_sock->so_rcv);\
	register int xxi = ((xxsb)->sb_hiwat-(xxsb)->sb_cc);\
	register int maxcredit = ((tpcb)->tp_xtd_format?0xffff:0xf);\
	maxcredit = ((tpcb)->tp_decbit?1:maxcredit);\
	xxi = (xxi<0) ? 0 : ((xxi)>>(tpcb)->tp_tpdusize);\
	(tpcb)->tp_lcredit = MIN( xxi ,maxcredit );\
E 5
I 5
    register struct sockbuf *xxsb = &((tpcb)->tp_sock->so_rcv);\
D 9
    register int xxi = ((xxsb)->sb_hiwat-(xxsb)->sb_cc);\
    register int maxcredit = ((tpcb)->tp_xtd_format?0xffff:0xf);\
    xxi = (xxi<0) ? 0 : ((xxi)>>(tpcb)->tp_tpdusize);\
    xxi = MIN(xxi, maxcredit); \
E 9
I 9
    register int xxi = sbspace(xxsb);\
    xxi = (xxi<0) ? 0 : ((xxi) / (tpcb)->tp_l_tpdusize);\
    xxi = min(xxi, (tpcb)->tp_maxlcredit); \
E 9
    if (!(tpcb->tp_cebit_off)) { \
        (tpcb)->tp_lcredit = ROUND((tpcb)->tp_win_recv); \
        if (xxi < (tpcb)->tp_lcredit) { \
            (tpcb)->tp_lcredit = xxi; \
        } \
D 10
    } \
    else { \
E 10
I 10
    } else \
E 10
        (tpcb)->tp_lcredit = xxi; \
D 10
    } \
E 5
}
E 10
I 10
} }
E 10
D 13
#endif ARGO_DEBUG
E 13
I 13
#endif /* ARGO_DEBUG */
E 13

#ifdef KERNEL
I 11
extern int tp_rttadd, tp_rttdiv;
E 11
I 9
D 10
#ifdef ARGO_DEBUG
E 10
D 12
#include "syslog.h"
E 12
I 12
#include <sys/syslog.h>
E 12
#define printf logpri(LOG_DEBUG),addlog
D 10
#endif
E 10
E 9

#ifndef  tp_NSTATES 

D 12
#include "tp_states.h"
#include "tp_events.h"
E 12
I 12
#include <netiso/tp_states.h>
#include <netiso/tp_events.h>
E 12
I 8
#if defined(__STDC__) || defined(__cplusplus)
#undef ATTR
#define ATTR(X) ev_union.EV_ ## X
#endif /* defined(__STDC__) || defined(__cplusplus) */
E 8

D 13
#endif  tp_NSTATES 
#endif KERNEL
E 13
I 13
#endif  /* tp_NSTATES  */
#endif /* KERNEL */
E 13

D 13
#endif __TP_PARAM__
E 13
I 13
#endif /* __TP_PARAM__ */
E 13
E 1
