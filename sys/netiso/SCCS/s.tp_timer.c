h08498
s 00002/00002/00349
d D 8.1 93/06/10 23:21:11 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00015/00336
d D 7.16 92/10/11 12:22:12 bostic 16 15
c make kernel includes standard
e
s 00001/00001/00350
d D 7.15 92/09/21 19:01:39 mckusick 15 14
c use min rather than MIN
e
s 00002/00002/00349
d D 7.14 92/05/27 16:10:22 sklower 14 13
c more informative debugging for tp_slowtimo
e
s 00011/00008/00340
d D 7.13 91/10/08 21:54:16 sklower 13 12
c Bug: must zero initial tpref table;
c minor rewrite of slow timout, worst offense was to not let tp_driver
c set appropriate next timeout.
e
s 00001/00001/00347
d D 7.12 91/10/02 22:24:24 sklower 12 11
c wrong order for includes
e
s 00018/00027/00330
d D 7.11 91/10/02 20:37:56 sklower 11 10
c use RANGESET and REXMTVAL macros, initial magic constants necessary for them;
c make it possible for the timeout routines to be macros
e
s 00084/00102/00273
d D 7.10 91/09/26 17:02:46 sklower 10 9
c These changes represent a rewrite of retransmission policies to
c imitate the TCP algorithms more closely.  More tuning and testing need to
c be done, but the code runs at least somewhat, and these represent a checkpoint
e
s 00028/00000/00347
d D 7.9 91/09/06 17:15:20 sklower 9 8
c adopt TCP's policies concerning acks & (among others) use the fast
c timeout mechanism and delayed acks.
e
s 00071/00176/00276
d D 7.8 91/09/05 18:02:21 sklower 8 7
c effectively merge tp_ref structure with rest of tp_pcb;
c this version doesn't crash, but does exhibit lumpy behavior;
c ack & retrans policies need to be fixed
e
s 00003/00000/00449
d D 7.7 91/09/05 17:58:18 sklower 7 6
c gather info in one place for netstat for variable allocated tp_refs
e
s 00008/00001/00441
d D 7.6 91/08/30 12:12:42 sklower 6 5
c paranoia about freeing a tpcb while still in the list of bound tcb's
c or list of children of a given TSEL
e
s 00009/00005/00433
d D 7.5 91/05/06 19:24:38 bostic 5 4
c new copyright; att/bsd/shared
e
s 00016/00009/00422
d D 7.4 91/04/26 15:24:38 sklower 4 3
c make number of simultaneous connections settable at init time
c instead of compile time.
e
s 00001/00000/00430
d D 7.3 89/08/29 13:45:42 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00014/00010/00416
d D 7.2 89/04/22 11:55:41 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00426/00000/00000
d D 7.1 88/12/14 15:30:17 sklower 1 0
c date and time created 88/12/14 15:30:17 by sklower
e
u
U
t
T
I 5
/*-
D 17
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
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
 * $Header: tp_timer.c,v 5.2 88/11/18 17:29:07 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_timer.c,v $
I 3
D 5
 *	%W% (Berkeley) %G% *
E 5
E 3
 *
D 11
 * Contains all the timer code.  
 * There are two sources of calls to these routines:
 * the clock, and tp.trans. (ok, and tp_pcb.c calls it at init time)
 *
 * Timers come in two flavors - those that generally get
 * cancelled (tp_ctimeout, tp_cuntimeout)
 * and those that either usually expire (tp_etimeout, 
 * tp_euntimeout, tp_slowtimo) or may require more than one instance
 * of the timer active at a time.
 *
 * The C timers are stored in the tp_ref structure. Their "going off"
 * is manifested by a driver event of the TM_xxx form.
 *
 * The E timers are handled like the generic kernel callouts.
 * Their "going off" is manifested by a function call w/ 3 arguments.
E 11
 */
D 5

#ifndef lint
static char *rcsid = "$Header: tp_timer.c,v 5.2 88/11/18 17:29:07 nhall Exp $";
#endif lint
E 5

D 16
#include "param.h"
D 11
#include "types.h"
E 11
I 11
#include "systm.h"
E 11
#include "time.h"
I 2
#include "malloc.h"
I 11
#include "protosw.h"
E 11
I 4
#include "socket.h"
I 11
#include "kernel.h"
E 16
I 16
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/malloc.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/kernel.h>
E 16
E 11
E 4
E 2

I 12
D 16
#include "argo_debug.h"
E 12
D 2
#include "../netiso/tp_param.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_seq.h"
E 2
I 2
#include "tp_param.h"
#include "tp_timer.h"
#include "tp_stat.h"
#include "tp_pcb.h"
#include "tp_tpdu.h"
D 12
#include "argo_debug.h"
E 12
#include "tp_trace.h"
#include "tp_seq.h"
E 16
I 16
#include <netiso/argo_debug.h>
#include <netiso/tp_param.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_tpdu.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_seq.h>
E 16
E 2

D 4
static  struct	Ecallout *TP_callfree;
static  struct	Ecallout TP_callout[N_TPREF*2]; 
E 4
I 4
D 10
struct	Ecallout *TP_callfree;
struct	Ecallout *TP_callout; 
E 10
struct	tp_ref *tp_ref;
D 8
int		N_TPREF = 100;
E 8
I 8
D 11
int		N_TPREF = 127;
E 11
I 11
int	tp_rttdiv, tp_rttadd, N_TPREF = 127;
E 11
E 8
I 7
struct	tp_refinfo tp_refinfo;
I 9
struct	tp_pcb *tp_ftimeolist = (struct tp_pcb *)&tp_ftimeolist;
E 9
E 7
E 4

D 8
extern int tp_maxrefopen;  /* highest ref # of an open tp connection */

E 8
/*
 * CALLED FROM:
 *  at autoconfig time from tp_init() 
 * 	a combo of event, state, predicate
 * FUNCTION and ARGUMENTS:
 *  initialize data structures for the timers
 */
void
tp_timerinit()
{
D 4
	register int i;
E 4
I 4
D 10
	register struct Ecallout *e;
E 10
	register int s;
D 11
#define GETME(x, t, n) {s = (n)*sizeof(*x); x = (t) malloc(s, M_PCB, M_NOWAIT);\
if (x == 0) panic("tp_timerinit"); bzero((caddr_t)x, s);}
E 11
E 4
	/*
D 4
	 * Initialize callouts
E 4
I 4
	 * Initialize storage
E 4
	 */
I 11
	if (tp_refinfo.tpr_base)
		return;
E 11
D 4
	TP_callfree = TP_callout;
	for (i = 1; i < N_TPREF*2; i++)
		TP_callout[i-1].c_next = &TP_callout[i];
E 4
I 4
D 8
	GETME(TP_callout, struct Ecallout *, 2 * N_TPREF);
E 8
D 10
	GETME(tp_ref, struct tp_ref *, 1 +  N_TPREF);
I 7
	tp_refinfo.tpr_base = tp_ref;
E 10
D 8
	tp_refinfo.tpr_size = N_TPREF;  /* XXX: There will be a better way */
E 7
E 4

D 4
	bzero( (caddr_t)tp_ref, N_TPREF * sizeof(struct tp_ref) );
E 4
I 4
	TP_callfree = TP_callout + ((2 * N_TPREF) - 1);
	for (e = TP_callfree; e > TP_callout; e--)
		e->c_next = e - 1;
E 4

	/* hate to do this but we really don't want zero to be a legit ref */
	tp_maxrefopen = 1;
	tp_ref[0].tpr_state = REF_FROZEN;  /* white lie -- no ref timer, don't
		* want this one to be allocated- ever
		* unless, of course, you make refs and address instead of an
		* index - then 0 can be allocated
		*/
E 8
I 8
	tp_refinfo.tpr_size = N_TPREF + 1;  /* Need to start somewhere */
I 10
D 11
	GETME(tp_ref, struct tp_ref *, tp_refinfo.tpr_size);
E 11
I 11
	s = sizeof(*tp_ref) * tp_refinfo.tpr_size;
	if ((tp_ref = (struct tp_ref *) malloc(s, M_PCB, M_NOWAIT)) == 0)
		panic("tp_timerinit");
I 13
	bzero((caddr_t)tp_ref, (unsigned) s);
E 13
E 11
	tp_refinfo.tpr_base = tp_ref;
E 10
E 8
D 4

E 4
I 4
D 11
#undef GETME
E 11
I 11
	tp_rttdiv = hz / PR_SLOWHZ;
	tp_rttadd = (2 * tp_rttdiv) - 1;
E 11
E 4
}
D 11

E 11
I 11
#ifdef TP_DEBUG_TIMERS
E 11
/**********************  e timers *************************/

I 8
D 10
int Enoisy = 1;
E 10
E 8
/*
 * CALLED FROM:
D 8
 *  tp_slowtimo() every 1/2 second, for each open reference
 * FUNCTION and ARGUMENTS:
 *  (refp) indicates a reference structure that is in use.
 *  This ref structure may contain active E-type timers.
 *  Update the timers and if any expire, create an event and
 *  call the driver.
 */
static void
tp_Eclock(refp)
	struct tp_ref	*refp; /* the reference structure */
{
	register struct Ecallout *p1; /* to drift through the list of callouts */
	struct tp_event			 E; /* event to pass to tp_driver() */
	int						 tp_driver(); /* drives the FSM */

	/*
	 * Update real-time timeout queue.
	 * At front of queue are some number of events which are ``due''.
	 * The time to these is <= 0 and if negative represents the
	 * number of ticks which have passed since it was supposed to happen.
	 * The rest of the q elements (times > 0) are events yet to happen,
	 * where the time for each is given as a delta from the previous.
	 * Decrementing just the first of these serves to decrement the time
	 * to all events.
	 * 
	 * This version, which calls the driver directly, doesn't pass
	 * along the ticks - may want to add the ticks if there's any use
	 * for them.
	 */
	IncStat(ts_Eticks);
	p1 = refp->tpr_calltodo.c_next;
	while (p1) {
		if (--p1->c_time > 0)
			break;
		if (p1->c_time == 0)
			break;
		p1 = p1->c_next;
	}

	for (;;) {
I 2
		struct tp_pcb *tpcb;
E 2
		if ((p1 = refp->tpr_calltodo.c_next) == 0 || p1->c_time > 0) {
			break;
		}
		refp->tpr_calltodo.c_next = p1->c_next;
		p1->c_next = TP_callfree;

#ifndef lint
		E.ev_number = p1->c_func;
		E.ATTR(TM_data_retrans).e_low = (SeqNum) p1->c_arg1;
		E.ATTR(TM_data_retrans).e_high = (SeqNum) p1->c_arg2;
		E.ATTR(TM_data_retrans).e_retrans =  p1->c_arg3;
#endif lint
		IFDEBUG(D_TIMER)
			printf("E expired! event 0x%x (0x%x,0x%x), pcb 0x%x ref %d\n",
				p1->c_func, p1->c_arg1, p1->c_arg2, refp->tpr_pcb,
				refp-tp_ref);
		ENDDEBUG

		TP_callfree = p1;
		IncStat(ts_Eexpired);
D 2
		(void) tp_driver( refp->tpr_pcb, &E);
E 2
I 2
		(void) tp_driver( tpcb = refp->tpr_pcb, &E);
D 6
		if (p1->c_func == TM_reference && tpcb->tp_state == TP_CLOSED)
E 6
I 6
		if (p1->c_func == TM_reference && tpcb->tp_state == TP_CLOSED) {
			if (tpcb->tp_notdetached) {
				IFDEBUG(D_CONN)
					printf("PRU_DETACH: not detached\n");
				ENDDEBUG
				tp_detach(tpcb);
			}
E 6
			free((caddr_t)tpcb, M_PCB); /* XXX wart; where else to do it? */
I 6
		}
E 6
E 2
	}
}

/*
 * CALLED FROM:
E 8
 *  tp.trans all over
 * FUNCTION and ARGUMENTS:
D 10
 * Set an E type timer.  (refp) is the ref structure.
 * Causes  fun(arg1,arg2,arg3) to be called after time t.
E 10
I 10
 * Set an E type timer.
E 10
 */
void
D 10
tp_etimeout(refp, fun, arg1, arg2, arg3, ticks)
	struct tp_ref	*refp;		
	int 			fun; 	/* function to be called */
	u_int			arg1, arg2; 
	int				arg3;
	register int	ticks;
E 10
I 10
tp_etimeout(tpcb, fun, ticks)
	register struct tp_pcb	*tpcb;
	int 					fun; 	/* function to be called */
	int						ticks;
E 10
{
D 8
	register struct Ecallout *p1, *p2, *pnew;
		/* p1 and p2 drift through the list of timeout callout structures,
		 * pnew points to the newly created callout structure
		 */
E 8

I 8
D 10
	register struct tp_pcb *tpcb = refp->tpr_pcb;
	register struct Ccallout *callp;
E 10
I 10
	register u_int *callp;
E 10
E 8
	IFDEBUG(D_TIMER)
D 10
		printf("etimeout pcb 0x%x state 0x%x\n", refp->tpr_pcb,
		refp->tpr_pcb->tp_state);
E 10
I 10
		printf("etimeout pcb 0x%x state 0x%x\n", tpcb, tpcb->tp_state);
E 10
	ENDDEBUG
	IFTRACE(D_TIMER)
D 10
		tptrace(TPPTmisc, "tp_etimeout ref refstate tks Etick", refp-tp_ref,
		refp->tpr_state, ticks, tp_stat.ts_Eticks);
E 10
I 10
		tptrace(TPPTmisc, "tp_etimeout ref refstate tks Etick", tpcb->tp_lref,
		tpcb->tp_state, ticks, tp_stat.ts_Eticks);
E 10
	ENDTRACE
D 8

E 8
I 8
	if (tpcb == 0)
		return;
E 8
	IncStat(ts_Eset);
	if (ticks == 0)
		ticks = 1;
D 8
	pnew = TP_callfree;
	if (pnew == (struct Ecallout *)0)
		panic("tp timeout table overflow");
	TP_callfree = pnew->c_next;
	pnew->c_arg1 = arg1;
	pnew->c_arg2 = arg2;
	pnew->c_arg3 = arg3;
	pnew->c_func = fun;
	for (p1 = &(refp->tpr_calltodo); 
							(p2 = p1->c_next) && p2->c_time < ticks; p1 = p2)
		if (p2->c_time > 0)
			ticks -= p2->c_time;
	p1->c_next = pnew;
	pnew->c_next = p2;
	pnew->c_time = ticks;
	if (p2)
		p2->c_time -= ticks;
E 8
I 8
D 10
	if (fun == TM_data_retrans) {
		tpcb->tp_retransargs.c_arg1 = arg1;
		tpcb->tp_retransargs.c_arg2 = arg2;
		tpcb->tp_retransargs.c_arg3 = arg3;
	}
	callp = tpcb->tp_refcallout + fun;
	if (Enoisy && callp->c_time)
		printf("E timer allready set: %d of ref %d\n", fun, tpcb->tp_lref);
	if (callp->c_time == 0 || callp->c_time > ticks)
		callp->c_time = ticks;
E 10
I 10
	callp = tpcb->tp_timer + fun;
	if (*callp == 0 || *callp > ticks)
		*callp = ticks;
E 10
E 8
}

/*
 * CALLED FROM:
 *  tp.trans all over
 * FUNCTION and ARGUMENTS:
 *  Cancel all occurrences of E-timer function (fun) for reference (refp)
 */
void
D 10
tp_euntimeout(refp, fun)
	struct tp_ref *refp;
E 10
I 10
tp_euntimeout(tpcb, fun)
	register struct tp_pcb	*tpcb;
E 10
	int			  fun;
{
D 8
	register struct Ecallout *p1, *p2; /* ptrs to drift through the list */
E 8
I 8
D 10
	register struct tp_pcb *tpcb = refp->tpr_pcb;
E 8

E 10
	IFTRACE(D_TIMER)
D 10
		tptrace(TPPTmisc, "tp_euntimeout ref", refp-tp_ref, 0, 0, 0);
E 10
I 10
		tptrace(TPPTmisc, "tp_euntimeout ref", tpcb->tp_lref, 0, 0, 0);
E 10
	ENDTRACE

D 8
	p1 = &refp->tpr_calltodo; 
	while ( (p2 = p1->c_next) != 0) {
		if (p2->c_func == fun)  {
			if (p2->c_next && p2->c_time > 0) 
				p2->c_next->c_time += p2->c_time;
			p1->c_next = p2->c_next;
			p2->c_next = TP_callfree;
			TP_callfree = p2;
			IncStat(ts_Ecan_act);
			continue;
		}
		p1 = p2;
	}
E 8
I 8
	if (tpcb)
D 10
		tpcb->tp_refcallout[fun].c_time = 0;
E 10
I 10
		tpcb->tp_timer[fun] = 0;
E 10
E 8
}

D 10
/*
 * CALLED FROM:
 *  tp.trans, when an incoming ACK causes things to be dropped
 *  from the retransmission queue, and we want their associated
 *  timers to be cancelled.
I 8
 *  NOTE: (by sklower) only called with TM_data_retrans.
E 8
 * FUNCTION and ARGUMENTS:
 *  cancel all occurrences of function (fun) where (arg2) < (seq)
 */
void
tp_euntimeout_lss(refp, fun, seq)
	struct tp_ref *refp;
	int			  fun;
	SeqNum		  seq;
{
D 8
	register struct Ecallout *p1, *p2;
E 8
I 8
	register struct tp_pcb *tpcb = refp->tpr_pcb;
E 8

	IFTRACE(D_TIMER)
		tptrace(TPPTmisc, "tp_euntimeoutLSS ref", refp-tp_ref, seq, 0, 0);
	ENDTRACE

D 8
	p1 = &refp->tpr_calltodo; 
	while ( (p2 = p1->c_next) != 0) {
		if ((p2->c_func == fun) && SEQ_LT(refp->tpr_pcb, p2->c_arg2, seq))  {
			if (p2->c_next && p2->c_time > 0) 
				p2->c_next->c_time += p2->c_time;
			p1->c_next = p2->c_next;
			p2->c_next = TP_callfree;
			TP_callfree = p2;
E 8
I 8
	if (tpcb == 0 || tpcb->tp_refcallout[fun].c_time == 0)
		return;
	if (SEQ_LT(tpcb, tpcb->tp_retransargs.c_arg2, seq))  {
E 8
			IncStat(ts_Ecan_act);
D 8
			continue;
		}
		p1 = p2;
E 8
I 8
			tpcb->tp_refcallout[fun].c_time = 0;
E 8
	}
}

E 10
/****************  c timers **********************
 *
 * These are not chained together; they sit
 * in the tp_ref structure. they are the kind that
 * are typically cancelled so it's faster not to
 * mess with the chains
 */
D 11

E 11
I 11
#endif
E 11
/*
 * CALLED FROM:
 *  the clock, every 500 ms
 * FUNCTION and ARGUMENTS:
 *  Look for open references with active timers.
 *  If they exist, call the appropriate timer routines to update
 *  the timers and possibly generate events.
D 13
 *  (The E timers are done in other procedures; the C timers are
 *  updated here, and events for them are generated here.)
E 13
 */
ProtoHook
tp_slowtimo()
{
D 8
	register int 		r,t;
	struct Ccallout 	*cp;
	struct tp_ref		*rp = tp_ref;
E 8
I 8
D 10
	register struct Ccallout 	*cp, *cpbase;
E 10
I 10
D 13
	register u_int 	*cp, *cpbase;
E 13
I 13
	register u_int 	*cp;
E 13
E 10
	register struct tp_ref		*rp;
	struct tp_pcb		*tpcb;
E 8
	struct tp_event		E;
D 8
	int 				s = splnet();
E 8
I 8
	int 				s = splnet(), t;
E 8

	/* check only open reference structures */
	IncStat(ts_Cticks);
D 8
	rp++;	/* tp_ref[0] is never used */
	for(  r=1 ; (r <= tp_maxrefopen) ; r++,rp++ ) {
		if (rp->tpr_state < REF_OPEN) 
E 8
I 8
	/* tp_ref[0] is never used */
	for (rp = tp_ref + tp_refinfo.tpr_maxopen; rp > tp_ref; rp--) {
D 11
		if ((tpcb = rp->tpr_pcb) == 0 || rp->tpr_state < REF_OPEN) 
E 11
I 11
		if ((tpcb = rp->tpr_pcb) == 0 || tpcb->tp_refstate < REF_OPEN) 
E 11
E 8
			continue;
D 8

E 8
I 8
D 10
		cpbase = tpcb->tp_refcallout;
		t = N_CTIMERS;
E 8
		/* check the C-type timers */
E 10
I 10
D 13
		cpbase = tpcb->tp_timer;
E 13
D 14
		t = TM_NTIMERS;
E 14
		/* check the timers */
E 10
D 8
		cp = rp->tpr_callout;
		for (t=0 ; t < N_CTIMERS; t++,cp++) {
			if( cp->c_active ) {
				if( --cp->c_time <= 0 ) {
					cp->c_active = FALSE;
					E.ev_number = t;
					IFDEBUG(D_TIMER)
						printf("C expired! type 0x%x\n", t);
					ENDDEBUG
					IncStat(ts_Cexpired);
					tp_driver( rp->tpr_pcb, &E);
E 8
I 8
D 13
		for (cp = cpbase + t; (--t, --cp) >= cpbase; ) {
E 13
I 13
		for (t = 0; t < TM_NTIMERS; t++) {
			cp = tpcb->tp_timer + t;
E 13
D 10
			if (cp->c_time && --(cp->c_time) <= 0 ) {
				cp->c_time = 0;
E 10
I 10
			if (*cp && --(*cp) <= 0 ) {
				*cp = 0;
E 10
				E.ev_number = t;
D 10
				if (t == TM_data_retrans) {
					register struct Ecallarg *p1 = &tpcb->tp_retransargs;
					E.ATTR(TM_data_retrans).e_low = (SeqNum) p1->c_arg1;
					E.ATTR(TM_data_retrans).e_high = (SeqNum) p1->c_arg2;
					E.ATTR(TM_data_retrans).e_retrans =  p1->c_arg3;
E 8
				}
E 10
I 8
				IFDEBUG(D_TIMER)
D 14
					printf("C expired! type 0x%x\n", t);
E 14
I 14
					printf("tp_slowtimo: pcb 0x%x t %d\n",
							tpcb, t);
E 14
				ENDDEBUG
				IncStat(ts_Cexpired);
D 13
				tp_driver( rp->tpr_pcb, &E);
E 13
I 13
				tp_driver(tpcb, &E);
E 13
				if (t == TM_reference && tpcb->tp_state == TP_CLOSED) {
					if (tpcb->tp_notdetached) {
						IFDEBUG(D_CONN)
							printf("PRU_DETACH: not detached\n");
						ENDDEBUG
						tp_detach(tpcb);
					}
					/* XXX wart; where else to do it? */
					free((caddr_t)tpcb, M_PCB);
				}
E 8
			}
		}
D 8
		/* now update the list */
		tp_Eclock(rp);
E 8
	}
	splx(s);
	return 0;
I 9
}

I 10
/*
 * Called From: tp.trans from tp_slowtimo() -- retransmission timer went off.
 */
tp_data_retrans(tpcb)
register struct tp_pcb *tpcb;
{
	int rexmt, win;
	tpcb->tp_rttemit = 0;	/* cancel current round trip time */
	tpcb->tp_dupacks = 0;
	tpcb->tp_sndnxt = tpcb->tp_snduna;
	if (tpcb->tp_fcredit == 0) {
		/*
		 * We transmitted new data, started timing it and the window
		 * got shrunk under us.  This can only happen if all data
		 * that they wanted us to send got acked, so don't
		 * bother shrinking the congestion windows, et. al.
		 * The retransmission timer should have been reset in goodack()
		 */
I 13
		IFDEBUG(D_ACKRECV)
			printf("tp_data_retrans: 0 window tpcb 0x%x una 0x%x\n",
				tpcb, tpcb->tp_snduna);
		ENDDEBUG
E 13
		tpcb->tp_rxtshift = 0;
		tpcb->tp_timer[TM_data_retrans] = 0;
		tpcb->tp_timer[TM_sendack] = tpcb->tp_dt_ticks;
I 13
		return;
E 13
	}
	rexmt = tpcb->tp_dt_ticks << min(tpcb->tp_rxtshift, TP_MAXRXTSHIFT);
	win = min(tpcb->tp_fcredit, (tpcb->tp_cong_win / tpcb->tp_l_tpdusize / 2));
	win = max(win, 2);
	tpcb->tp_cong_win = tpcb->tp_l_tpdusize;	/* slow start again. */
	tpcb->tp_ssthresh = win * tpcb->tp_l_tpdusize;
	/* We're losing; our srtt estimate is probably bogus.
	 * Clobber it so we'll take the next rtt measurement as our srtt;
	 * Maintain current rxt times until then.
	 */
	if (++tpcb->tp_rxtshift > TP_NRETRANS / 4) {
		/* tpcb->tp_nlprotosw->nlp_losing(tpcb->tp_npcb) someday */
		tpcb->tp_rtt = 0;
	}
D 11
	if (rexmt > 128)
		rexmt = 128; /* XXXX value from tcp_timer.h */
	tpcb->tp_timer[TM_data_retrans] = tpcb->tp_rxtcur = rexmt;
E 11
I 11
	TP_RANGESET(tpcb->tp_rxtcur, rexmt, tpcb->tp_peer_acktime, 128);
	tpcb->tp_timer[TM_data_retrans] = tpcb->tp_rxtcur;
E 11
	tp_send(tpcb);
}

E 10
int
tp_fasttimo()
{
	register struct tp_pcb *t;
	int s = splnet();
	struct tp_event		E;

	E.ev_number = TM_sendack;
	while ((t = tp_ftimeolist) != (struct tp_pcb *)&tp_ftimeolist) {
		if (t == 0) {
			printf("tp_fasttimeo: should panic");
			tp_ftimeolist = (struct tp_pcb *)&tp_ftimeolist;
		} else {
			if (t->tp_flags & TPF_DELACK) {
D 13
				t->tp_flags &= ~TPF_DELACK;
E 13
				IncStat(ts_Fdelack);
				tp_driver(t, &E);
D 10
				t->tp_refcallout[TM_sendack].c_time = t->tp_keepalive_ticks;
E 10
I 10
D 13
				t->tp_timer[TM_sendack] = t->tp_keepalive_ticks;
E 13
I 13
				t->tp_flags &= ~TPF_DELACK;
E 13
E 10
			} else
				IncStat(ts_Fpruned);
			tp_ftimeolist = t->tp_fasttimeo;
			t->tp_fasttimeo = 0;
		}
	}
	splx(s);
E 9
}

I 11
#ifdef TP_DEBUG_TIMERS
E 11
/*
 * CALLED FROM:
 *  tp.trans, tp_emit()
 * FUNCTION and ARGUMENTS:
 * 	Set a C type timer of type (which) to go off after (ticks) time.
 */
void
D 10
tp_ctimeout(refp, which, ticks)
	register struct tp_ref	*refp;
E 10
I 10
tp_ctimeout(tpcb, which, ticks)
	register struct tp_pcb	*tpcb;
E 10
	int 					which, ticks; 
{
D 10
	register struct Ccallout *cp = &(refp->tpr_callout[which]);
E 10

	IFTRACE(D_TIMER)
		tptrace(TPPTmisc, "tp_ctimeout ref which tpcb active", 
D 8
			(int)(refp - tp_ref), which, refp->tpr_pcb, cp->c_active);
E 8
I 8
D 10
			(int)(refp - tp_ref), which, refp->tpr_pcb, cp->c_time);
E 10
I 10
			tpcb->tp_lref, which, tpcb, tpcb->tp_timer[which]);
E 10
E 8
	ENDTRACE
D 8
	if(cp->c_active)
E 8
I 8
D 10
	if(cp->c_time)
E 10
I 10
	if(tpcb->tp_timer[which])
E 10
E 8
		IncStat(ts_Ccan_act);
	IncStat(ts_Cset);
I 8
	if (ticks <= 0)
		ticks = 1;
E 8
D 10
	cp->c_time = ticks;
E 10
I 10
	tpcb->tp_timer[which] = ticks;
E 10
D 8
	cp->c_active = TRUE;
E 8
}

/*
 * CALLED FROM:
 *  tp.trans 
 * FUNCTION and ARGUMENTS:
 * 	Version of tp_ctimeout that resets the C-type time if the 
 * 	parameter (ticks) is > the current value of the timer.
 */
void
D 10
tp_ctimeout_MIN(refp, which, ticks)
	register struct tp_ref	*refp;
E 10
I 10
tp_ctimeout_MIN(tpcb, which, ticks)
	register struct tp_pcb	*tpcb;
E 10
	int						which, ticks; 
{
D 10
	register struct Ccallout *cp = &(refp->tpr_callout[which]);

E 10
	IFTRACE(D_TIMER)
		tptrace(TPPTmisc, "tp_ctimeout_MIN ref which tpcb active", 
D 8
			(int)(refp - tp_ref), which, refp->tpr_pcb, cp->c_active);
E 8
I 8
D 10
			(int)(refp - tp_ref), which, refp->tpr_pcb, cp->c_time);
E 10
I 10
			tpcb->tp_lref, which, tpcb, tpcb->tp_timer[which]);
E 10
E 8
	ENDTRACE
D 8
	if(cp->c_active)
		IncStat(ts_Ccan_act);
E 8
	IncStat(ts_Cset);
D 8
	if( cp->c_active ) 
E 8
I 8
D 10
	if (cp->c_time)  {
E 8
		cp->c_time = MIN(ticks, cp->c_time);
E 10
I 10
	if (tpcb->tp_timer[which])  {
D 15
		tpcb->tp_timer[which] = MIN(ticks, tpcb->tp_timer[which]);
E 15
I 15
		tpcb->tp_timer[which] = min(ticks, tpcb->tp_timer[which]);
E 15
E 10
D 8
	else  {
E 8
I 8
		IncStat(ts_Ccan_act);
	} else
E 8
D 10
		cp->c_time = ticks;
E 10
I 10
		tpcb->tp_timer[which] = ticks;
E 10
D 8
		cp->c_active = TRUE;
	}
E 8
}

/*
 * CALLED FROM:
 *  tp.trans
 * FUNCTION and ARGUMENTS:
 *  Cancel the (which) timer in the ref structure indicated by (refp).
 */
void
D 10
tp_cuntimeout(refp, which)
E 10
I 10
tp_cuntimeout(tpcb, which)
	register struct tp_pcb	*tpcb;
E 10
	int						which;
D 10
	register struct tp_ref	*refp;
E 10
{
D 10
	register struct Ccallout *cp;

	cp = &(refp->tpr_callout[which]);

E 10
	IFDEBUG(D_TIMER)
D 2
		printf("tp_cuntimeout(0x%x, %d) active\n", refp, which, cp->c_active);
E 2
I 2
D 8
		printf("tp_cuntimeout(0x%x, %d) active %d\n", refp, which, cp->c_active);
E 8
I 8
D 10
		printf("tp_cuntimeout(0x%x, %d) active %d\n", refp, which, cp->c_time);
E 10
I 10
		printf("tp_cuntimeout(0x%x, %d) active %d\n",
				tpcb, which, tpcb->tp_timer[which]);
E 10
E 8
E 2
	ENDDEBUG

	IFTRACE(D_TIMER)
		tptrace(TPPTmisc, "tp_cuntimeout ref which, active", refp-tp_ref, 
D 8
			which, cp->c_active, 0);
E 8
I 8
D 10
			which, cp->c_time, 0);
E 10
I 10
			which, tpcb->tp_timer[which], 0);
E 10
E 8
	ENDTRACE

D 8
	if(cp->c_active)
E 8
I 8
D 10
	if (cp->c_time)
E 10
I 10
	if (tpcb->tp_timer[which])
E 10
E 8
		IncStat(ts_Ccan_act);
	else
		IncStat(ts_Ccan_inact);
D 8
	cp->c_active = FALSE;
E 8
I 8
D 10
	cp->c_time = 0;
E 10
I 10
	tpcb->tp_timer[which] = 0;
E 10
E 8
}
I 11
#endif
E 11
E 1
