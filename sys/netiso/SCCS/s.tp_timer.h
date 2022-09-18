h09723
s 00002/00002/00065
d D 8.1 93/06/10 23:21:14 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00065
d D 7.8 93/05/25 11:52:14 bostic 8 7
c trailing comment after #else or #endif
e
s 00017/00016/00050
d D 7.7 91/10/02 20:28:28 sklower 7 6
c get rid of obsolete structures and allow timer-setting routines to be  macros
e
s 00005/00000/00061
d D 7.6 91/09/06 17:15:21 sklower 6 5
c adopt TCP's policies concerning acks & (among others) use the fast
c timeout mechanism and delayed acks.
e
s 00005/00010/00056
d D 7.5 91/09/05 18:02:22 sklower 5 4
c effectively merge tp_ref structure with rest of tp_pcb;
c this version doesn't crash, but does exhibit lumpy behavior;
c ack & retrans policies need to be fixed
e
s 00009/00001/00057
d D 7.4 91/05/06 19:24:39 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00057
d D 7.3 89/08/29 13:45:45 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00000/00057
d D 7.2 89/04/22 11:55:43 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00057/00000/00000
d D 7.1 88/12/14 15:30:18 sklower 1 0
c date and time created 88/12/14 15:30:18 by sklower
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
 * $Header: tp_timer.h,v 5.1 88/10/12 12:21:41 root Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_timer.h,v $
I 3
D 4
 *	%W% (Berkeley) %G% *
E 4
E 3
 *
 * ARGO TP
 * The callout structures used by the tp timers.
 */

D 7
#ifndef __TP_CALLOUT__
#define __TP_CALLOUT__
E 7
I 7
#ifndef __TP_TIMER__
#define __TP_TIMER__
E 7

D 7
/* C timers - one per tpcb, generally cancelled */

D 5
struct	Ccallout {
	int	c_time;		/* incremental time */
	int c_active;	/* this timer is active? */
E 5
I 5
struct	Ecallarg {
	u_int	c_arg1;
	u_int	c_arg2;
	int		c_arg3;
E 5
};

D 5
/* E timers - generally expire or there must be > 1 active per tpcb */
struct Ecallout {
E 5
I 5
struct	Ccallout {
E 5
	int	c_time;		/* incremental time */
D 5
	int c_func;		/* function to call */
	u_int c_arg1;	/* argument to routine */
	u_int c_arg2;	/* argument to routine */
	int c_arg3;		/* argument to routine */
	struct Ecallout *c_next;
E 5
};

E 7
I 6
#define SET_DELACK(t) {\
    (t)->tp_flags |= TPF_DELACK; \
    if ((t)->tp_fasttimeo == 0)\
D 7
	{ (t)->tp_fasttimeo = tp_ftimeolist; tp_ftimeolist = (t); } }
E 7
I 7
		{ (t)->tp_fasttimeo = tp_ftimeolist; tp_ftimeolist = (t); } }
E 7

E 6
D 7
#endif __TP_CALLOUT__
E 7
I 7
#ifdef ARGO_DEBUG
#define TP_DEBUG_TIMERS
#endif

#ifndef TP_DEBUG_TIMERS
#define tp_ctimeout(tpcb, which, timo) ((tpcb)->tp_timer[which] = (timo))
#define tp_cuntimeout(tpcb, which) ((tpcb)->tp_timer[which] = 0)
#define tp_etimeout tp_ctimeout
#define tp_euntimeout tp_cuntimeout
#define tp_ctimeout_MIN(p, w, t) \
    { if((p)->tp_timer[w] > (t)) (p)->tp_timer[w] = (t);}
D 8
#endif TP_DEBUG_TIMERS
E 8
I 8
#endif /* TP_DEBUG_TIMERS */
E 8

D 8
#endif __TP_TIMER__
E 8
I 8
#endif /* __TP_TIMER__ */
E 8
E 7
E 1
