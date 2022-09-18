h41198
s 00002/00002/00170
d D 8.1 93/06/10 23:21:25 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00168
d D 7.8 93/05/25 11:52:17 bostic 8 7
c trailing comment after #else or #endif
e
s 00002/00002/00170
d D 7.7 92/10/11 12:22:13 bostic 7 6
c make kernel includes standard
e
s 00001/00001/00171
d D 7.6 91/10/02 19:44:33 sklower 6 5
c get rid of struct tp_param, which contained no interesting info.
e
s 00022/00019/00150
d D 7.5 91/06/27 22:06:19 sklower 5 4
c minor changes to compile under both new and old vm systems
e
s 00009/00001/00160
d D 7.4 91/05/06 19:24:42 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00160
d D 7.3 89/08/29 13:45:50 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00000/00160
d D 7.2 89/04/22 11:55:48 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00160/00000/00000
d D 7.1 88/12/14 15:30:20 sklower 1 0
c date and time created 88/12/14 15:30:20 by sklower
e
u
U
t
T
I 4
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
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
 * $Header: tp_trace.h,v 5.1 88/10/12 12:21:51 root Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_trace.h,v $
I 3
D 4
 *	%W% (Berkeley) %G% *
E 4
E 3
 *
 * 
 * Definitions needed for the protocol trace mechanism.
 */

#ifndef __TP_TRACE__
#define __TP_TRACE__

D 5
#ifdef TPPT
E 5

#define TPPTsendack	1
#define TPPTgotack	2
#define TPPTXack	3
#define TPPTgotXack	4
#define TPPTack		5
#define TPPTindicate	6
#define TPPTusrreq	7
#define TPPTmisc	8
#define TPPTpcb		9
#define TPPTref		10
#define TPPTtpduin	11
#define TPPTparam	12
#define TPPTertpdu	13
#define TPPTdriver	14
#define TPPTtpduout	15

D 7
#include "../netiso/tp_pcb.h"
E 7
I 7
#include <netiso/tp_pcb.h>
E 7

/* this #if is to avoid lint */

#if  defined(TP_TRACEFILE)||!defined(KERNEL)

D 7
#include "../netiso/tp_tpdu.h"
E 7
I 7
#include <netiso/tp_tpdu.h>
E 7

#define TPTRACE_STRLEN 50


/* for packet tracing */
struct tp_timeval {
	SeqNum	tptv_seq;
	u_int tptv_kind;
	u_int tptv_window;
	u_int tptv_size;
};

struct	tp_Trace {
	u_int	tpt_event;
	u_int	tpt_arg;
	u_int 	tpt_arg2;
	int	tpt_tseq;
	struct timeval	tpt_time;
	union {
		struct inpcb	tpt_Inpcb; /* protocol control block */
		struct tp_ref 	tpt_Ref; /* ref part of pcb */
		struct tpdu 	tpt_Tpdu; /* header*/
D 6
		struct tp_param tpt_Param; /* ?? bytes, make sure < 128??*/
E 6
I 6
		struct tp_refinfo tpt_Param; /* ?? bytes, make sure < 128??*/
E 6
		struct tp_timeval tpt_Time;
		struct {
			u_int tptm_2;
			u_int tptm_3;
			u_int tptm_4;
			u_int tptm_5;
			char tpt_Str[TPTRACE_STRLEN];
			u_int tptm_1;
		} tptmisc;
		u_char 			tpt_Ertpdu; /* use rest of structure */
	} tpt_stuff;
};
#define tpt_inpcb tpt_stuff.tpt_Inpcb
#define tpt_pcb tpt_stuff.tpt_Pcb
#define tpt_ref tpt_stuff.tpt_Ref
#define tpt_tpdu tpt_stuff.tpt_Tpdu
#define tpt_param tpt_stuff.tpt_Param
#define tpt_ertpdu tpt_stuff.tpt_Ertpdu
#define tpt_str tpt_stuff.tptmisc.tpt_Str
#define tpt_m1 tpt_stuff.tptmisc.tptm_1
#define tpt_m2 tpt_stuff.tptmisc.tptm_2
#define tpt_m3 tpt_stuff.tptmisc.tptm_3
#define tpt_m4 tpt_stuff.tptmisc.tptm_4
#define tpt_m5 tpt_stuff.tptmisc.tptm_5

#define tpt_seq tpt_stuff.tpt_Time.tptv_seq
#define tpt_kind tpt_stuff.tpt_Time.tptv_kind
#define tpt_window tpt_stuff.tpt_Time.tptv_window
#define tpt_size tpt_stuff.tpt_Time.tptv_size

D 5
#define TPTRACEN 300
int tp_Tracen = 0;
struct tp_Trace tp_Trace[TPTRACEN];

E 5
D 8
#endif defined(TP_TRACEFILE)||!defined(KERNEL)
E 8
I 8
#endif /* defined(TP_TRACEFILE)||!defined(KERNEL) */
E 8

D 5
extern u_char	tp_traceflags[];
E 5

D 5
#define IFTRACE(ascii)\
	if(tp_traceflags[ascii]) {
/* 
 * for some reason lint complains about tp_param being undefined no
 * matter where or how many times I define it.
 */
E 5
I 5
#ifdef TPPT
E 5

I 5
#define TPTRACEN 300
E 5

D 5
#define ENDTRACE  }

E 5
#define tptrace(A,B,C,D,E,F) \
	tpTrace((struct tp_pcb *)0,\
	(u_int)(A),(u_int)(B),(u_int)(C),(u_int)(D),(u_int)(E),(u_int)(F))

#define tptraceTPCB(A,B,C,D,E,F) \
	tpTrace(tpcb,\
	(u_int)(A),(u_int)(B),(u_int)(C),(u_int)(D),(u_int)(E),(u_int)(F))

extern void tpTrace();
I 5
extern struct tp_Trace tp_Trace[];
extern u_char	tp_traceflags[];
int tp_Tracen = 0;
E 5

I 5
#define IFTRACE(ascii)\
	if(tp_traceflags[ascii]) {
/* 
 * for some reason lint complains about tp_param being undefined no
 * matter where or how many times I define it.
 */
#define ENDTRACE  }


E 5
D 8
#else  TPPT
E 8
I 8
#else  /* TPPT */
E 8

/***********************************************
 * NO TPPT TRACE STUFF
 **********************************************/
I 5
#define TPTRACEN 1
E 5

D 5
#ifndef STAR
#define STAR *
#endif	STAR
#define IFTRACE(ascii)	 //*beginning of comment*/STAR
#define ENDTRACE	 STAR/*end of comment*//
E 5
I 5
#define tptrace(A,B,C,D,E,F) 0
#define tptraceTPCB(A,B,C,D,E,F) 0
E 5

I 5
#define IFTRACE(ascii)	 if (0) {
#define ENDTRACE	 }

E 5
D 8
#endif TPPT
E 8
I 8
#endif /* TPPT */
E 8
I 5


E 5

D 8
#endif __TP_TRACE__
E 8
I 8
#endif /* __TP_TRACE__ */
E 8
E 1
