h47782
s 00002/00002/00268
d D 8.1 93/06/10 23:21:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00268
d D 7.5 93/05/25 11:52:15 bostic 5 4
c trailing comment after #else or #endif
e
s 00009/00001/00261
d D 7.4 91/05/06 19:24:40 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00261
d D 7.3 89/08/29 13:45:37 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00007/00006/00254
d D 7.2 89/04/22 11:55:44 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00260/00000/00000
d D 7.1 88/12/14 15:30:19 sklower 1 0
c date and time created 88/12/14 15:30:19 by sklower
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
/* 
 * ARGO TP
 *
 * $Header: tp_tpdu.h,v 4.4 88/07/26 16:45:40 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_tpdu.h,v $
I 3
D 4
 *	%W% (Berkeley) %G% *
E 4
E 3
 *
 * This ghastly set of macros makes it possible to
 * refer to tpdu structures without going mad.
 */

#ifndef __TP_TPDU__
#define __TP_TPDU__

#ifndef BYTE_ORDER
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */

#ifdef vax
#define	BYTE_ORDER	LITTLE_ENDIAN
#else
#define	BYTE_ORDER	BIG_ENDIAN	/* mc68000, tahoe, most others */
#endif
D 5
#endif BYTE_ORDER
E 5
I 5
#endif /* BYTE_ORDER */
E 5

/* This much of a tpdu is the same for all types of tpdus  (except
 * DT tpdus in class 0; their exceptions are handled by the data
 * structure below
 */
struct tpdu_fixed {
D 2
	unsigned	_tpduf_li:8,		/* length indicator */
E 2
I 2
	u_char			_tpduf_li:8,		/* length indicator */
E 2
#if BYTE_ORDER == LITTLE_ENDIAN
				_tpduf_cdt: 4,		/* credit */
D 2
				_tpduf_type: 4,		/* type of tpdu (DT, CR, etc.) */
E 2
I 2
				_tpduf_type: 4;		/* type of tpdu (DT, CR, etc.) */
E 2
#endif
#if BYTE_ORDER == BIG_ENDIAN
				_tpduf_type: 4,		/* type of tpdu (DT, CR, etc.) */
D 2
				_tpduf_cdt: 4,		/* credit */
E 2
I 2
				_tpduf_cdt: 4;		/* credit */
E 2
#endif
D 2
				_tpduf_dref: 16;	/* destination ref; not in DT in class 0 */
E 2
I 2
	u_short			_tpduf_dref;		/* destination ref; not in DT in class 0 */
E 2
};

#define tpdu_li _tpduf._tpduf_li
#define tpdu_type _tpduf._tpduf_type
#define tpdu_cdt _tpduf._tpduf_cdt
#define tpdu_dref _tpduf._tpduf_dref
			
struct tp0du {
D 2
	unsigned	_tp0same:16,		/* same as in tpdu_fixed */
E 2
I 2
	u_char		_tp0_li,
				_tp0_cdt_type,		/* same as in tpdu_fixed */
E 2
#if BYTE_ORDER == BIG_ENDIAN
				_tp0_eot: 1,		/* eot */
				_tp0_mbz: 7,		/* must be zero */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
				_tp0_mbz: 7,		/* must be zero */
				_tp0_eot: 1,		/* eot */
#endif
				_tp0_notused: 8;	/* data begins on this octet */
};

#define tp0du_eot _tp0_eot
#define tp0du_mbz _tp0_mbz
			
/*
 * This is used when the extended format seqence numbers are
 * being sent and received. 
 */
				/*
				 * the seqeot field is an int that overlays the seq
				 * and eot fields, this allows the htonl operation
				 * to be applied to the entire 32 bit quantity, and
				 * simplifies the structure definitions.
				 */
union seq_type {
	struct {
#if BYTE_ORDER == BIG_ENDIAN
		unsigned int	st_eot:1,		/* end-of-tsdu */
				 		st_seq:31;		/* 31 bit sequence number */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
		unsigned int	st_seq:31,		/* 31 bit sequence number */
						st_eot:1;		/* end-of-tsdu */
#endif
	} st;
	unsigned int s_seqeot;
#define s_eot	st.st_eot
#define s_seq	st.st_seq
};

/* Then most tpdu types have a portion that is always present but
 * differs among the tpdu types :
 */
union  tpdu_fixed_rest {

		struct {
D 2
			unsigned	_tpdufr_sref:16, 	/* source reference */
E 2
I 2
			u_short		_tpdufr_sref, 		/* source reference */
E 2
#if BYTE_ORDER == BIG_ENDIAN
						_tpdufr_class: 4,	/* class [ ISO 8073 13.3.3.e ] */
						_tpdufr_opt: 4,		/* options [ ISO 8073 13.3.3.e ] */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
						_tpdufr_opt: 4,		/* options [ ISO 8073 13.3.3.e ] */
						_tpdufr_class: 4,	/* class [ ISO 8073 13.3.3.e ] */
#endif
						_tpdufr_xx: 8;		/* unused */
		} CRCC;

#define tpdu_CRli _tpduf._tpduf_li
#define tpdu_CRtype _tpduf._tpduf_type
#define tpdu_CRcdt _tpduf._tpduf_cdt
#define tpdu_CRdref_0 _tpduf._tpduf_dref
#define tpdu_CRsref _tpdufr.CRCC._tpdufr_sref
#define tpdu_sref _tpdufr.CRCC._tpdufr_sref
#define tpdu_CRclass _tpdufr.CRCC._tpdufr_class
#define tpdu_CRoptions _tpdufr.CRCC._tpdufr_opt

#define tpdu_CCli _tpduf._tpduf_li
#define tpdu_CCtype _tpduf._tpduf_type
#define tpdu_CCcdt _tpduf._tpduf_cdt
#define tpdu_CCdref _tpduf._tpduf_dref
#define tpdu_CCsref _tpdufr.CRCC._tpdufr_sref
#define tpdu_CCclass _tpdufr.CRCC._tpdufr_class
#define tpdu_CCoptions _tpdufr.CRCC._tpdufr_opt

/* OPTIONS and ADDL OPTIONS bits */
#define TPO_USE_EFC	 			0x1
#define TPO_XTD_FMT	 			0x2
#define TPAO_USE_TXPD 			0x1
#define TPAO_NO_CSUM 			0x2
#define TPAO_USE_RCC 			0x4
#define TPAO_USE_NXPD 			0x8

		struct {
			unsigned short _tpdufr_sref;	/* source reference */
			unsigned char  _tpdufr_reason;	/* [ ISO 8073 13.5.3.d ] */
		} DR;
#define tpdu_DRli _tpduf._tpduf_li
#define tpdu_DRtype _tpduf._tpduf_type
#define tpdu_DRdref _tpduf._tpduf_dref
#define tpdu_DRsref _tpdufr.DR._tpdufr_sref
#define tpdu_DRreason _tpdufr.DR._tpdufr_reason

		unsigned short _tpdufr_sref;	/* source reference */

#define tpdu_DCli _tpduf._tpduf_li
#define tpdu_DCtype _tpduf._tpduf_type
#define tpdu_DCdref _tpduf._tpduf_dref
#define tpdu_DCsref _tpdufr._tpdufr_sref

		struct {
#if BYTE_ORDER == BIG_ENDIAN
			unsigned char _tpdufr_eot:1,	/* end-of-tsdu */
						  _tpdufr_seq:7; 	/* 7 bit sequence number */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
			unsigned char	_tpdufr_seq:7, 	/* 7 bit sequence number */
							_tpdufr_eot:1;	/* end-of-tsdu */
#endif
		}SEQEOT;
		struct {
#if BYTE_ORDER == BIG_ENDIAN
			unsigned int	_tpdufr_Xeot:1,		/* end-of-tsdu */
					 		_tpdufr_Xseq:31;	/* 31 bit sequence number */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
			unsigned int	_tpdufr_Xseq:31,	/* 31 bit sequence number */
							_tpdufr_Xeot:1;		/* end-of-tsdu */
#endif
		}SEQEOT31;
		unsigned int _tpdufr_Xseqeot;
#define tpdu_seqeotX _tpdufr._tpdufr_Xseqeot

#define tpdu_DTli _tpduf._tpduf_li
#define tpdu_DTtype _tpduf._tpduf_type
#define tpdu_DTdref _tpduf._tpduf_dref
#define tpdu_DTseq _tpdufr.SEQEOT._tpdufr_seq
#define tpdu_DTeot _tpdufr.SEQEOT._tpdufr_eot
#define tpdu_DTseqX _tpdufr.SEQEOT31._tpdufr_Xseq
#define tpdu_DTeotX _tpdufr.SEQEOT31._tpdufr_Xeot

#define tpdu_XPDli _tpduf._tpduf_li
#define tpdu_XPDtype _tpduf._tpduf_type
#define tpdu_XPDdref _tpduf._tpduf_dref
#define tpdu_XPDseq _tpdufr.SEQEOT._tpdufr_seq
#define tpdu_XPDeot _tpdufr.SEQEOT._tpdufr_eot
#define tpdu_XPDseqX _tpdufr.SEQEOT31._tpdufr_Xseq
#define tpdu_XPDeotX _tpdufr.SEQEOT31._tpdufr_Xeot

		struct {
#if BYTE_ORDER == BIG_ENDIAN
			unsigned	_tpdufr_yrseq0:1,	/* always zero */
						_tpdufr_yrseq:31; 	/* [ ISO 8073 13.9.3.d ] */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
			unsigned	_tpdufr_yrseq:31, 	/* [ ISO 8073 13.9.3.d ] */
						_tpdufr_yrseq0:1;	/* always zero */
#endif
			unsigned short _tpdufr_cdt; /* [ ISO 8073 13.9.3.b ] */
		} AK31;

#define tpdu_AKli _tpduf._tpduf_li
#define tpdu_AKtype _tpduf._tpduf_type
#define tpdu_AKdref _tpduf._tpduf_dref
#define tpdu_AKseq _tpdufr.SEQEOT._tpdufr_seq
#define tpdu_AKseqX _tpdufr.AK31._tpdufr_yrseq
/* location of cdt depends on size of seq. numbers */
#define tpdu_AKcdt _tpduf._tpduf_cdt
#define tpdu_AKcdtX _tpdufr.AK31._tpdufr_cdt

#define tpdu_XAKli _tpduf._tpduf_li
#define tpdu_XAKtype _tpduf._tpduf_type
#define tpdu_XAKdref _tpduf._tpduf_dref
#define tpdu_XAKseq _tpdufr.SEQEOT._tpdufr_seq
#define tpdu_XAKseqX _tpdufr.SEQEOT31._tpdufr_Xseq

		unsigned char _tpdu_ERreason;  	/* [ ISO 8073 13.12.3.c ] */

#define tpdu_ERli _tpduf._tpduf_li
#define tpdu_ERtype _tpduf._tpduf_type
#define tpdu_ERdref _tpduf._tpduf_dref
#define tpdu_ERreason _tpdufr._tpdu_ERreason

};

struct tpdu {
	struct	tpdu_fixed 		_tpduf;
	union 	tpdu_fixed_rest _tpdufr;
};

D 5
#endif __TP_TPDU__
E 5
I 5
#endif /* __TP_TPDU__ */
E 5
E 1
