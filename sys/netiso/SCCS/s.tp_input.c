h18786
s 00002/00002/01596
d D 8.1 93/06/10 23:20:23 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00014/01584
d D 7.32 93/05/25 11:51:50 bostic 32 31
c trailing comment after #else or #endif
e
s 00025/00025/01573
d D 7.31 92/10/11 12:22:00 bostic 31 30
c make kernel includes standard
e
s 00003/00003/01595
d D 7.30 92/07/22 18:00:43 sklower 30 29
c this version compiles at least
e
s 00035/00017/01563
d D 7.29 92/07/20 13:16:56 sklower 29 28
c bugfix for concatednated packets from mitre.org
e
s 00001/00001/01579
d D 7.28 92/05/27 16:11:18 sklower 28 27
c need to calculate initial credit on CC for other option viz CE_BIT
e
s 00001/00001/01579
d D 7.27 92/02/11 11:09:05 mckusick 27 26
c ovbcopy should be bcopy
e
s 00031/00001/01549
d D 7.26 91/12/17 16:19:38 sklower 26 25
c big-or-odd-size packet option. (n x 128 instead of 2^n only)
e
s 00000/00001/01550
d D 7.25 91/10/02 21:46:35 sklower 25 24
c don't stomp on sockbuff sizes if already set
e
s 00000/00016/01551
d D 7.24 91/10/02 20:42:10 sklower 24 23
c mtu calculations done in tp_route_to, checked by tp_consistency.
e
s 00008/00009/01559
d D 7.23 91/09/26 17:02:42 sklower 23 22
c These changes represent a rewrite of retransmission policies to
c imitate the TCP algorithms more closely.  More tuning and testing need to
c be done, but the code runs at least somewhat, and these represent a checkpoint
e
s 00002/00002/01566
d D 7.22 91/09/05 18:02:18 sklower 22 21
c effectively merge tp_ref structure with rest of tp_pcb;
c this version doesn't crash, but does exhibit lumpy behavior;
c ack & retrans policies need to be fixed
e
s 00057/00055/01511
d D 7.21 91/07/29 14:55:52 sklower 21 20
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00006/00006/01560
d D 7.20 91/07/18 20:33:29 sklower 20 19
c this changes reflect getting rid of so_tpcb.
e
s 00006/00001/01560
d D 7.19 91/06/27 16:55:48 sklower 19 18
c misc fix from mostek@cray
e
s 00009/00005/01552
d D 7.18 91/05/06 19:24:22 bostic 18 17
c new copyright; att/bsd/shared
e
s 00002/00001/01555
d D 7.17 91/04/30 16:28:46 sklower 17 16
c called tsel must match length of listening tsel
e
s 00023/00011/01533
d D 7.16 91/04/26 15:19:36 sklower 16 15
c new convention: disconnect reason passed as ancillary datum
e
s 00030/00019/01514
d D 7.15 91/01/09 15:45:04 sklower 15 14
c Checkpoint integration of tp_cons with UBC X.25; compiles only;
c not tested, probably not complete.
e
s 00004/00007/01529
d D 7.14 90/07/24 18:13:00 sklower 14 13
c fixes to talk to decnet phase V and retransmission timer
e
s 00010/00009/01526
d D 7.13 90/06/29 11:14:43 sklower 13 12
c fix minor bugs in setting up cross-list of listeners, intercepters, and their descendents
e
s 00039/00032/01496
d D 7.12 90/06/28 19:39:46 sklower 12 11
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00014/00008/01514
d D 7.11 90/06/20 19:03:09 sklower 11 10
c changed esis to make use of routing table; mostly works;
c checkpoint before UW merge
e
s 00067/00093/01455
d D 7.10 90/06/06 17:27:11 sklower 10 9
c about the first third of the COS failures attempted fixes, chkpoint for testing.
e
s 00008/00003/01540
d D 7.9 90/05/30 17:35:09 sklower 9 8
c document separate change that wrong version numbers are not labeled
c as errors
e
s 00001/00001/01542
d D 7.8 90/05/30 11:56:44 sklower 8 7
c tp_control_hdr obsoleted by cmsghdr in socket.h
e
s 00001/00002/01542
d D 7.7 90/03/26 19:53:33 karels 7 6
c my macros didn't work, make the code agree with the comments
e
s 00005/00008/01539
d D 7.6 90/02/05 18:48:50 sklower 6 5
c NIST claims that no user data implies always accept; emit void control header.
e
s 00013/00004/01534
d D 7.5 90/01/16 23:35:37 sklower 5 4
c mitre decbit changes
e
s 00001/00001/01537
d D 7.4 89/09/22 00:44:07 sklower 4 3
c fixes to tracing and avoiding silly window between
c socket layer and transport; more changes to come to usrreq and tp_send.
e
s 00021/00020/01517
d D 7.3 89/08/29 13:45:02 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00102/00106/01435
d D 7.2 89/04/22 11:54:58 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 01541/00000/00000
d D 7.1 88/12/14 15:30:01 sklower 1 0
c date and time created 88/12/14 15:30:01 by sklower
e
u
U
t
T
I 18
/*-
D 33
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 18
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
 * $Header: tp_input.c,v 5.6 88/11/18 17:27:38 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_input.c,v $
I 3
D 18
 *	%W% (Berkeley) %G% *
E 18
E 3
 *
 * tp_input() gets an mbuf chain from ip.  Actually, not directly
 * from ip, because ip calls a net-level routine that strips off
 * the net header and then calls tp_input(), passing the proper type
 * of addresses for the address family in use (how it figures out
D 21
 * which AF is not yet determined.
E 21
I 21
 * which AF is not yet determined.)
E 21
 *
 * Decomposing the tpdu is some of the most laughable code.  The variable-length
 * parameters and the problem of non-aligned memory references
 * necessitates such abominations as the macros WHILE_OPTIONS (q.v. below)
 * to loop through the header and decompose it.
 *
 * The routine tp_newsocket() is called when a CR comes in for a listening
 * socket.  tp_input calls sonewconn() and tp_newsocket() to set up the
 * "child" socket.  Most tpcb values are copied from the parent tpcb into
 * the child.
 * 
 * Also in here is tp_headersize() (grot) which tells the expected size
 * of a tp header, to be used by other layers.  It's in here because it
 * uses the static structure tpdu_info.
 */
D 18

#ifndef lint
static char *rcsid = "$Header: tp_input.c,v 5.6 88/11/18 17:27:38 nhall Exp $";
#endif lint
E 18

D 15
#include "argoxtwentyfive.h"
E 15
D 31
#include "param.h"
I 12
#include "systm.h"
E 12
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "domain.h"
#include "protosw.h"
#include "errno.h"
#include "time.h"
#include "kernel.h"
#include "types.h"
I 15
#include "iso.h"
E 15
D 2
#include "../netiso/iso_errno.h"
#include "../netiso/tp_param.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_tpdu.h"
#include "../netiso/iso.h"
#include "../netiso/cons.h"
E 2
I 2
#include "iso_errno.h"
I 15
#include "iso_pcb.h"
E 15
#include "tp_param.h"
#include "tp_timer.h"
#include "tp_stat.h"
#include "tp_pcb.h"
#include "argo_debug.h"
#include "tp_trace.h"
#include "tp_tpdu.h"
E 31
I 31
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
E 31
D 15
#include "iso.h"
#include "cons.h"
E 15
E 2

I 15
D 31
#include "../net/if.h"
E 31
I 31
#include <netiso/iso.h>
#include <netiso/iso_errno.h>
#include <netiso/iso_pcb.h>
#include <netiso/tp_param.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_pcb.h>
#include <netiso/argo_debug.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_tpdu.h>

#include <net/if.h>
E 31
#ifdef TRUE
#undef FALSE
#undef TRUE
#endif
D 31
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 31
I 31
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 31

E 15
int 	iso_check_csum(), tp_driver(), tp_headersize(), tp_error_emit();

D 2
#ifdef lint
#undef ATTR
#define ATTR(X)ev_number
#endif lint
E 2
I 2
/*
	#ifdef lint
	#undef ATTR
	#define ATTR(X)ev_number
	#endif lint
*/
E 2

struct mbuf *
tp_inputprep(m) 
D 2
	struct mbuf *m;
E 2
I 2
	register struct mbuf *m;
E 2
{
D 2
	struct tpdu *hdr;
E 2
I 2
	int hdrlen;
E 2

	IFDEBUG(D_TPINPUT)
D 2
		printf("tp_inputprep: m 0x%x\n") ;
E 2
I 2
		printf("tp_inputprep: m 0x%x\n", m) ;
E 2
	ENDDEBUG

	while(  m->m_len < 1 ) {
D 29
		if( (m = m_free(m)) == MNULL ) {
			return (struct mbuf *)0;
		}
E 29
I 29
	    /* The "m_free" logic
	     * if( (m = m_free(m)) == MNULL )
	     *      return (struct mbuf *)0;
		 * would cause a system crash if ever executed.
		 * This logic will be executed if the first mbuf
	     * in the chain only contains a CLNP header. The m_free routine
	     * will release the mbuf containing the CLNP header from the
	     * chain and the new head of the chain will not have the
	     * M_PKTHDR bit set. This routine, tp_inputprep, will
	     * eventually call the "sbappendaddr" routine. "sbappendaddr"
	     * calls "panic" if M_PKTHDR is not set. m_pullup is a cheap
	     * way of keeping the head of the chain from being freed.
		 */
D 30
		if((m = m_pullup(m)) == MNULL)
E 30
I 30
		if((m = m_pullup(m, 1)) == MNULL)
E 30
			return (MNULL);
E 29
	}
I 2
	if(((int)m->m_data) & 0x3) {
		/* If we are not 4-byte aligned, we have to be
		 * above the beginning of the mbuf, and it is ok just
		 * to slide it back. 
		 */
		caddr_t ocp = m->m_data;
E 2

D 2
	if(m->m_off & 0x3) {
		/* align to a 4-byte boundary - sigh */
		register struct mbuf *n;

		MGET(n, M_DONTWAIT, m->m_type);
		if( n == MNULL ) {
			m_freem(m);
			return (struct mbuf *)0;
		}
		n->m_act = MNULL;
		n->m_len = m->m_len;
		n->m_next = m->m_next;
		bcopy( mtod(m, caddr_t), mtod(n, caddr_t), m->m_len );
		m->m_next = 0;
		m_free(m);
		m = n;
E 2
I 2
		m->m_data = (caddr_t)(((int)m->m_data) & ~0x3);
D 27
		ovbcopy(ocp, m->m_data, (unsigned)m->m_len);
E 27
I 27
		bcopy(ocp, m->m_data, (unsigned)m->m_len);
E 27
E 2
	}
	CHANGE_MTYPE(m, TPMT_DATA);

D 2
	/* we KNOW that there is at least 1 byte in this mbuf */
E 2
I 2
	/* we KNOW that there is at least 1 byte in this mbuf
	   and that it is hdr->tpdu_li XXXXXXX!  */
E 2

D 2
	hdr = mtod( m, struct tpdu *);
E 2
I 2
	hdrlen = 1 + *mtod( m, u_char *);
E 2

	/*
	 * now pull up the whole tp header 
	 */
D 2
	if ( m->m_len < hdr->tpdu_li + 1 ) {
		if ((m = m_pullup(m, (int)(hdr->tpdu_li) + 1)) == MNULL ) {
E 2
I 2
	if ( m->m_len < hdrlen) {
		if ((m = m_pullup(m, hdrlen)) == MNULL ) {
E 2
			IncStat(ts_recv_drop);
			return (struct mbuf *)0;
		}
	}
	IFDEBUG(D_INPUT)
	printf(
	" at end: m 0x%x hdr->tpdu_li 0x%x m_len 0x%x\n",m,
D 2
		hdr->tpdu_li,m->m_len);
E 2
I 2
		hdrlen, m->m_len);
E 2
	ENDDEBUG
	return m;
}

/* begin groan
 * -- this array and the following macros allow you to step through the
 * parameters of the variable part of a header
 * note that if for any reason the values of the **_TPDU macros (in tp_events.h)
 * should change, this array has to be rearranged
 */

#define TP_LEN_CLASS_0_INDEX	2
#define TP_MAX_DATA_INDEX 3

static u_char tpdu_info[][4] =
{
/*								length						 max data len */
/*								reg fmt 	xtd fmt  class 0  		 	  */
 	/* UNUSED		0x0 */		0x0 ,		0x0,	0x0,		0x0,
 	/* XPD_TPDU_type 0x1 */		0x5,		0x8,	0x0,		TP_MAX_XPD_DATA,
 	/* XAK_TPDU_type 0x2 */		0x5 ,		0x8,	0x0,		0x0,
 	/* GR_TPDU_type	0x3 */		0x0 ,		0x0,	0x0,		0x0,
 	/* UNUSED		0x4 */		0x0 ,		0x0,	0x0,		0x0,
 	/* UNUSED		0x5 */		0x0 ,		0x0,	0x0,		0x0,
 	/* AK_TPDU_type 0x6 */		0x5,		0xa,	0x0,		0x0,
	/* ER_TPDU_type 0x7 */		0x5,		0x5,	0x0,		0x0,
 	/* DR_TPDU_type 0x8 */		0x7,		0x7,	0x7,		TP_MAX_DR_DATA,
 	/* UNUSED		0x9 */		0x0 ,		0x0,	0x0,		0x0,
 	/* UNUSED		0xa */		0x0 ,		0x0,	0x0,		0x0,
 	/* UNUSED		0xb */		0x0 ,		0x0,	0x0,		0x0,
 	/* DC_TPDU_type 0xc */		0x6,		0x6,	0x0,		0x0,
 	/* CC_TPDU_type 0xd */		0x7,		0x7,	0x7,		TP_MAX_CC_DATA,
 	/* CR_TPDU_type 0xe */		0x7,		0x7,	0x7,		TP_MAX_CR_DATA,
 	/* DT_TPDU_type 0xf */		0x5,		0x8,	0x3,		0x0,
};

I 10
#define CHECK(Phrase, Erval, Stat, Whattodo, Loc)\
D 11
	if(Phrase) { error = (Erval); errlen = (int)(Loc); IncStat(Stat); \
E 11
I 11
D 29
	if (Phrase) {error = (Erval); errlen = (int)(Loc); IncStat(Stat); tpibrk();\
E 29
I 29
	if (Phrase) {error = (Erval); errlen = (int)(Loc); IncStat(Stat);\
E 29
E 11
	goto Whattodo; }

I 11
D 29
tpibrk() {}

E 29
E 11
E 10
/* 
 * WHENEVER YOU USE THE FOLLOWING MACRO,
 * BE SURE THE TPDUTYPE IS A LEGIT VALUE FIRST! 
 */

D 10
#define WHILE_OPTIONS(P, hdr,format)\
{	register  caddr_t		P;\
	P = (caddr_t)(hdr) +\
	tpdu_info[(hdr)->tpdu_type][(format)];\
	while( P < (caddr_t)(hdr) + (int)((hdr)->tpdu_li) ) {
E 10
I 10
#define WHILE_OPTIONS(P, hdr, format)\
{	register caddr_t P = tpdu_info[(hdr)->tpdu_type][(format)] + (caddr_t)hdr;\
	caddr_t PLIM = 1 + hdr->tpdu_li + (caddr_t)hdr;\
	for (;; P += 2 + ((struct tp_vbp *)P)->tpv_len) {\
		CHECK((P > PLIM), E_TP_LENGTH_INVAL, ts_inv_length,\
				respond, P - (caddr_t)hdr);\
		if (P == PLIM) break;
E 10

D 10
#define END_WHILE_OPTIONS(P)\
	P = P  + 2 + (int)((struct tp_vbp *)P)->tpv_len ;\
} }
E 10
I 10
#define END_WHILE_OPTIONS(P) } }
E 10

D 10
#define CHECK(Phrase, Erval, Stat, Whattodo, Loc)\
	if(Phrase) { error = (Erval); errloc = (caddr_t)(Loc); IncStat(Stat); \
	goto Whattodo; }

E 10
/* end groan */

/*
 * NAME:  tp_newsocket()
 *
 * CALLED FROM:
 *  tp_input() on incoming CR, when a socket w/ the called suffix
 * is awaiting a  connection request
 *
 * FUNCTION and ARGUMENTS:
 *  Create a new socket structure, attach to it a new transport pcb,
 *  using a copy of the net level pcb for the parent socket.
 *  (so) is the parent socket.
 *  (fname) is the foreign address (all that's used is the nsap portion)
 *
 * RETURN VALUE:
 *  a new socket structure, being this end of the newly formed connection.
 *
 * SIDE EFFECTS:
 *  Sets a few things in the tpcb and net level pcb
 *
 * NOTES:
 */
static struct socket *
tp_newsocket(so, fname, cons_channel, class_to_use, netservice)
	struct socket				*so;
	struct sockaddr				*fname;
D 21
	u_int						cons_channel;
E 21
I 21
	caddr_t						cons_channel;
E 21
	u_char						class_to_use;
	u_int						netservice;
{
	register struct tp_pcb	*tpcb = sototpcb(so); /* old tpcb, needed below */
D 15
	struct tp_pcb *			 newtpcb;
E 15
I 15
	register struct tp_pcb	*newtpcb;
E 15
D 3
	struct proc *			selproc = so->so_rcv.sb_sel; /* kludge for select */
E 3
I 3
D 7
	extern struct socket *sonewsock();
E 7
E 3

	/* 
	 * sonewconn() gets a new socket structure,
	 * a new lower layer pcb and a new tpcb,
	 * but the pcbs are unnamed (not bound)
	 */
	IFTRACE(D_NEWSOCK)
D 3
		tptraceTPCB(TPPTmisc, "newsock: listg_so,_tpcb selproc, so_head",
			so, tpcb, selproc, so->so_head);
E 3
I 3
		tptraceTPCB(TPPTmisc, "newsock: listg_so, _tpcb, so_head",
D 4
			so, tpcb, so->so_head);
E 4
I 4
			so, tpcb, so->so_head, 0);
E 4
E 3
	ENDTRACE	

D 3
	if ((so = sonewconn(so)) == (struct socket *)0)
E 3
I 3
D 7
	if ((so = sonewsock(so, SS_ISCONFIRMING)) == (struct socket *)0)
E 7
I 7
	if ((so = sonewconn(so, SS_ISCONFIRMING)) == (struct socket *)0)
E 7
E 3
		return so;
	IFTRACE(D_NEWSOCK)
D 3
		tptraceTPCB(TPPTmisc, "newsock: after newconn so, selproc, so_head",
			so, selproc, so->so_head, 0);
E 3
I 3
		tptraceTPCB(TPPTmisc, "newsock: after newconn so, so_head",
			so, so->so_head, 0, 0);
E 3
	ENDTRACE	

D 3
	so->so_rcv.sb_sel = selproc; /* so that soisconnected() after receipt
		* of the ack will wake this guy up if he's selecting on the
		* listening socket
		*/
E 3
	IFDEBUG(D_NEWSOCK)
D 2
		printf("tp_newsocket(channel 0x%x)  after sonewconn so 0x%x \n", so);
		dump_isoaddr(fname);
E 2
I 2
		printf("tp_newsocket(channel 0x%x)  after sonewconn so 0x%x \n",
				cons_channel, so);
		dump_addr(fname);
E 2
		{ 
			struct socket *t, *head ;

			head = so->so_head;
			t = so;
			printf("so 0x%x so_head 0x%x so_q0 0x%x, q0len %d\n",
					t, t->so_head, t->so_q0, t->so_q0len);
			while( (t=t->so_q0)  && t!= so  && t!= head)
				printf("so 0x%x so_head 0x%x so_q0 0x%x, q0len %d\n",
					t, t->so_head, t->so_q0, t->so_q0len);
		}
	ENDDEBUG

	/* 
	 * before we clobber the old tpcb ptr, get these items from the parent pcb 
	 */
	newtpcb = sototpcb(so);
	newtpcb->_tp_param = tpcb->_tp_param;
	newtpcb->tp_flags = tpcb->tp_flags;
	newtpcb->tp_lcredit = tpcb->tp_lcredit;
	newtpcb->tp_l_tpdusize = tpcb->tp_l_tpdusize;
	newtpcb->tp_lsuffixlen = tpcb->tp_lsuffixlen;
	bcopy( tpcb->tp_lsuffix, newtpcb->tp_lsuffix, newtpcb->tp_lsuffixlen);
D 2
	soreserve(so, tpcb->tp_winsize, tpcb->tp_winsize);
E 2
I 2
D 25
	soreserve(so, (u_long)tpcb->tp_winsize, (u_long)tpcb->tp_winsize);
E 25
E 2

D 2
	if( /* old */ tpcb->tp_flags & (TPF_CONN_DATA_OUT | TPF_DISC_DATA_OUT )) {
E 2
I 2
	if( /* old */ tpcb->tp_ucddata) {
E 2
		/* 
D 2
		 * Flags has already been copied, now copy the data 
		 * -- these data are the connect- or disconnect- data.
E 2
I 2
		 * These data are the connect- , confirm- or disconnect- data.
E 2
		 */
		struct mbuf *conndata;

D 2
		ASSERT(tpcb->tp_sock->so_snd.sb_mb != MNULL);
		ASSERT(tpcb->tp_sock->so_snd.sb_cc != 0);
		conndata = m_copy( tpcb->tp_sock->so_snd.sb_mb, 0,
									tpcb->tp_sock->so_snd.sb_cc);
E 2
I 2
		conndata = m_copy(tpcb->tp_ucddata, 0, (int)M_COPYALL);
E 2
		IFDEBUG(D_CONN)
			dump_mbuf(conndata, "conndata after mcopy");
D 2
			dump_mbuf(tpcb->tp_sock->so_snd.sb_mb, "old sosnd after mcopy");
			dump_mbuf(so->so_snd.sb_mb, "new (so->)sosnd before sbapndrec");
			dump_mbuf(conndata, "conndata before sbappendrec");
E 2
		ENDDEBUG
D 2
		sbappendrecord( &so->so_snd, conndata );
E 2
I 2
		newtpcb->tp_ucddata = conndata;
E 2
	}

	tpcb = newtpcb;
	tpcb->tp_state = TP_LISTENING;
	tpcb->tp_class = class_to_use;
	tpcb->tp_netservice = netservice;


	ASSERT( fname != 0 ) ; /* just checking */
	if ( fname ) {
		/*
		 *	tp_route_to takes its address argument in the form of an mbuf.
		 */
		struct mbuf	*m;
		int			err;

		MGET(m, M_DONTWAIT, MT_SONAME);	/* mbuf type used is confusing */
		if (m) {
			/*
			 * this seems a bit grotesque, but tp_route_to expects
			 * an mbuf * instead of simply a sockaddr; it calls the ll
			 * pcb_connect, which expects the name/addr in an mbuf as well.
			 * sigh.
			 */
D 2
			bcopy((caddr_t)fname, mtod(m, caddr_t), sizeof (struct sockaddr));
			m->m_act = MNULL;
			m->m_len = (fname->sa_family == AF_INET) ? 
				sizeof(struct sockaddr_in) : sizeof(struct sockaddr_iso);
E 2
I 2
			bcopy((caddr_t)fname, mtod(m, caddr_t), fname->sa_len);
			m->m_len = fname->sa_len;
E 2

			/* grot  : have to say the kernel can override params in
			 * the passive open case
			 */
			tpcb->tp_dont_change_params = 0;
			err = tp_route_to( m, tpcb, cons_channel);
			m_free(m);

			if (!err)
				goto ok;
		}
		IFDEBUG(D_CONN)
			printf("tp_route_to FAILED! detaching tpcb 0x%x, so 0x%x\n",
				tpcb, so);
		ENDDEBUG
		(void) tp_detach(tpcb); 
		return 0;
	}
ok:
	IFDEBUG(D_TPINPUT)
		printf("tp_newsocket returning so 0x%x, sototpcb(so) 0x%x\n",
			so, sototpcb(so));
	ENDDEBUG
	return so;
}

D 15
#ifndef CONS
E 15
I 15
#ifndef TPCONS
E 15
tpcons_output()
{
	return(0);
}
D 32
#endif !CONS
E 32
I 32
#endif /* !CONS */
E 32

/* 
 * NAME: 	tp_input()
 *
 * CALLED FROM:
 *  net layer input routine
 *
 * FUNCTION and ARGUMENTS:
 *  Process an incoming TPDU (m), finding the associated tpcb if there
 *  is one. Create the appropriate type of event and call the driver.
 *  (faddr) and (laddr) are the foreign and local addresses.
 * 
 * 	When tp_input() is called we KNOW that the ENTIRE TP HEADER
 * 	has been m_pullup-ed.
 *
 * RETURN VALUE: Nada
 *  
 * SIDE EFFECTS:
 *	When using COSNS it may affect the state of the net-level pcb
 *
 * NOTE:
 *  The initial value of acktime is 2 so that we will never
 *  have a 0 value for tp_peer_acktime.  It gets used in the
 *  computation of the retransmission timer value, and so it
 *  mustn't be zero.
 *  2 seems like a reasonable minimum.
 */
ProtoHook
D 5
tp_input(m, faddr, laddr, cons_channel, dgout_routine)
E 5
I 5
tp_input(m, faddr, laddr, cons_channel, dgout_routine, ce_bit)
E 5
	register	struct mbuf 	*m;
	struct sockaddr 			*faddr, *laddr; /* NSAP addresses */
D 21
	u_int 						cons_channel;
E 21
I 21
	caddr_t						cons_channel;
E 21
	int 						(*dgout_routine)();
I 5
	int							ce_bit;
E 5

{
D 29
	register struct tp_pcb 	*tpcb = (struct tp_pcb *)0;
E 29
I 29
	register struct tp_pcb 	*tpcb;
E 29
D 14
	register struct tpdu 	*hdr = mtod(m, struct tpdu *);
E 14
I 14
	register struct tpdu 	*hdr;
E 14
	struct socket 			*so;
	struct tp_event 		e;
D 3
	int 					error = 0;
E 3
I 3
D 10
	int 					error;
E 10
I 10
D 29
	int 					error = 0;
E 29
I 29
	int 					error;
E 29
E 10
E 3
	unsigned 				dutype;
D 10
	u_short 				dref, sref, acktime, subseq; /*VAX*/
D 3
	u_char 					preferred_class=0, class_to_use=0;
E 3
I 3
	u_char 					preferred_class, class_to_use;
E 3
D 9
	u_char					opt, dusize, addlopt;
E 9
I 9
	u_char					opt, dusize, addlopt, version;
E 10
I 10
D 29
	u_short 				dref, sref = 0, acktime = 2, subseq = 0; /*VAX*/
D 26
	u_char 					preferred_class = 0, class_to_use = 0;
E 26
I 26
	u_char 					preferred_class = 0, class_to_use = 0, pdusize = 0;
E 26
	u_char					opt, dusize = TP_DFL_TPDUSIZE, addlopt = 0, version;
E 29
I 29
	u_short 				dref, sref, acktime, subseq;
	u_char 					preferred_class, class_to_use, pdusize;
	u_char					opt, dusize, addlopt, version;
E 29
E 10
E 9
#ifdef TP_PERF_MEAS
D 3
	u_char					perf_meas=0;
E 3
I 3
	u_char					perf_meas;
E 3
D 32
#endif TP_PERF_MEAS
E 32
I 32
#endif /* TP_PERF_MEAS */
E 32
D 10
	u_char					fsufxlen;
	u_char					lsufxlen;
D 3
	caddr_t					fsufxloc=0, lsufxloc=0;
E 3
I 3
	caddr_t					fsufxloc, lsufxloc;
E 3
	int						tpdu_len;
	u_int 					takes_data;
	u_int					fcc_present; 
D 3
	caddr_t					errloc=0;
E 3
I 3
	caddr_t					errloc;
E 10
I 10
D 12
	u_char					fsufxlen = 0;
	u_char					lsufxlen = 0;
E 12
I 12
D 21
	u_char					fsufxlen = 0, lsufxlen = 0, intercepted = 0;
E 21
I 21
D 29
	u_char					fsufxlen = 0, lsufxlen = 0;
E 21
E 12
	caddr_t					fsufxloc = 0, lsufxloc = 0;
	int						tpdu_len = 0;
	u_int 					takes_data = FALSE;
	u_int					fcc_present = FALSE; 
	int						errlen = 0;
E 29
I 29
	u_char					fsufxlen, lsufxlen;
	caddr_t					fsufxloc, lsufxloc;
	int						tpdu_len;
	u_int 					takes_data;
	u_int					fcc_present; 
	int						errlen;
E 29
E 10
E 3
	struct tp_conn_param 	tpp;
	int						tpcons_output();

I 3
again:
I 14
	hdr = mtod(m, struct tpdu *);
I 29
	tpcb = 0;
D 30
	error = errlen = tpdulen = 0;
E 30
I 30
	error = errlen = tpdu_len = 0;
E 30
	takes_data = fcc_present = FALSE;
	acktime = 2; sref = subseq = 0;
D 30
	fsufxloc = lsusfloc = NULL;
E 30
I 30
	fsufxloc = lsufxloc = NULL;
E 30
	fsufxlen = lsufxlen =
		preferred_class = class_to_use = pdusize = addlopt = 0;
	dusize = TP_DFL_TPDUSIZE;
E 29
E 14
E 3
#ifdef TP_PERF_MEAS
D 3
	GET_CUR_TIME( &e.e_time );
E 3
I 3
	GET_CUR_TIME( &e.e_time ); perf_meas = 0;
E 3
D 32
#endif TP_PERF_MEAS
E 32
I 32
#endif /* TP_PERF_MEAS */
E 32
	
	IFDEBUG(D_TPINPUT)
		printf("tp_input(0x%x, ... 0x%x)\n", m, cons_channel);
	ENDDEBUG

D 3
again:
E 3

D 10
	tpdu_len = 0;
	tpcb = (struct tp_pcb *)0;
D 3
	fsufxlen = 0;
	lsufxlen = 0;
E 3
I 3
	fsufxlen = 0; fsufxloc = 0;
	lsufxlen = 0; lsufxloc = 0;
	errloc = 0; error = 0;
E 3
	addlopt = 0;
	acktime = 2;
	dusize = TP_DFL_TPDUSIZE;
	sref = 0;
	subseq = 0;
	takes_data = FALSE;
	fcc_present = FALSE;
I 3
	preferred_class = 0; class_to_use = 0;
E 3

E 10
	/* 
	 * get the actual tpdu length - necessary for monitoring
	 * and for checksumming
	 * 
	 * Also, maybe measure the mbuf chain lengths and sizes.
	 */

	{ 	register struct mbuf *n=m;
#	ifdef ARGO_DEBUG
		int chain_length = 0;
#	endif ARGO_DEBUG

		for(;;) {
			tpdu_len += n->m_len;
			IFDEBUG(D_MBUF_MEAS)
D 2
				if( n->m_off > MMAXOFF) {
E 2
I 2
				if( n->m_flags & M_EXT) {
E 2
					IncStat(ts_mb_cluster);
				} else {
					IncStat(ts_mb_small);
				}
				chain_length ++;
			ENDDEBUG
			if (n->m_next == MNULL ) {
				break;
			}
			n = n->m_next;
		}
		IFDEBUG(D_MBUF_MEAS)
			if(chain_length > 16)
				chain_length = 0; /* zero used for anything > 16 */
			tp_stat.ts_mb_len_distr[chain_length] ++;
		ENDDEBUG
	}
	IFTRACE(D_TPINPUT)
		tptraceTPCB(TPPTtpduin, hdr->tpdu_type, hdr, hdr->tpdu_li+1, tpdu_len, 
			0);
	ENDTRACE

	dref = ntohs((short)hdr->tpdu_dref);
	sref = ntohs((short)hdr->tpdu_sref);
	dutype = (int)hdr->tpdu_type;

	IFDEBUG(D_TPINPUT)
		printf("input: dutype 0x%x cons_channel 0x%x dref 0x%x\n", dutype,
			cons_channel, dref);
		printf("input: dref 0x%x sref 0x%x\n", dref, sref);
	ENDDEBUG
	IFTRACE(D_TPINPUT)
		tptrace(TPPTmisc, "channel dutype dref ", 
			cons_channel, dutype, dref, 0);
	ENDTRACE


#ifdef ARGO_DEBUG
	if( (dutype < TP_MIN_TPDUTYPE) || (dutype > TP_MAX_TPDUTYPE)) {
		printf("BAD dutype! 0x%x, channel 0x%x dref 0x%x\n",
			dutype, cons_channel, dref);
		dump_buf (m, sizeof( struct mbuf ));

		IncStat(ts_inv_dutype);
		goto discard;
	}
D 32
#endif ARGO_DEBUG
E 32
I 32
#endif /* ARGO_DEBUG */
E 32

	CHECK( (dutype < TP_MIN_TPDUTYPE || dutype > TP_MAX_TPDUTYPE),
		E_TP_INV_TPDU, ts_inv_dutype, respond, 
		2 );
		/* unfortunately we can't take the address of the tpdu_type field,
		 * since it's a bit field - so we just use the constant offset 2
		 */

	/* Now this isn't very neat but since you locate a pcb one way
	 * at the beginning of connection establishment, and by
	 * the dref for each tpdu after that, we have to treat CRs differently
	 */
	if ( dutype == CR_TPDU_type ) {
		u_char alt_classes = 0;

D 10
#ifdef notdef  /* This is done up above */
		sref = hdr->tpdu_CRsref;
#endif notdef
E 10
D 2
		preferred_class = (1 << hdr->tpdu_CRclass);
E 2
I 2
		preferred_class = 1 << hdr->tpdu_CRclass;
E 2
		opt = hdr->tpdu_CRoptions;

		WHILE_OPTIONS(P, hdr, 1 ) /* { */

			switch( vbptr(P)->tpv_code ) {

			case	TPP_tpdu_size: 		
				vb_getval(P, u_char, dusize);
				IFDEBUG(D_TPINPUT)
					printf("CR dusize 0x%x\n", dusize);
				ENDDEBUG
D 10
				CHECK( (dusize < TP_MIN_TPDUSIZE || dusize > TP_MAX_TPDUSIZE),
						E_TP_INV_PVAL, ts_inv_pval, respond,
						(1 + (caddr_t)&vbptr(P)->tpv_val - P) )
E 10
I 10
				/* COS tests: NBS IA (Dec. 1987) Sec. 4.5.2.1 */
				if (dusize < TP_MIN_TPDUSIZE || dusize > TP_MAX_TPDUSIZE)
						dusize = TP_DFL_TPDUSIZE;
E 10
				break;
I 26
			case	TPP_ptpdu_size:
				switch (vbptr(P)->tpv_len) {
				case 1: pdusize = vbval(P, u_char); break;
				case 2: pdusize = ntohs(vbval(P, u_short)); break;
				default: ;
				IFDEBUG(D_TPINPUT)
					printf("malformed prefered TPDU option\n");
				ENDDEBUG
				}
				break;
E 26
			case	TPP_addl_opt:
				vb_getval(P, u_char, addlopt);
				break;
			case	TPP_calling_sufx:
				/* could use vb_getval, but we want to save the loc & len
				 * for later use
				 */
				fsufxloc = (caddr_t) &vbptr(P)->tpv_val;
				fsufxlen = vbptr(P)->tpv_len;
				IFDEBUG(D_TPINPUT)
					printf("CR fsufx:");
					{ register int j;
						for(j=0; j<fsufxlen; j++ ) {
							printf(" 0x%x. ", *((caddr_t)(fsufxloc+j)) );
						}
						printf("\n");
					}
				ENDDEBUG
				break;
			case	TPP_called_sufx:
				/* could use vb_getval, but we want to save the loc & len
				 * for later use
				 */
				lsufxloc = (caddr_t) &vbptr(P)->tpv_val;
				lsufxlen = vbptr(P)->tpv_len;
				IFDEBUG(D_TPINPUT)
					printf("CR lsufx:");
					{ register int j;
						for(j=0; j<lsufxlen; j++ ) {
D 2
							printf(" 0x%x. ", *((caddr_t)(lsufxloc+j)) );
E 2
I 2
							printf(" 0x%x. ", *((u_char *)(lsufxloc+j)) );
E 2
						}
						printf("\n");
					}
				ENDDEBUG
				break;

#ifdef TP_PERF_MEAS
			case	TPP_perf_meas:
				vb_getval(P, u_char, perf_meas);
				break;
D 32
#endif TP_PERF_MEAS
E 32
I 32
#endif /* TP_PERF_MEAS */
E 32

			case	TPP_vers:
				/* not in class 0; 1 octet; in CR_TPDU only */
I 9
D 10
				/* Iso says if version wrong, use default version????? */
E 10
I 10
				/* COS tests says if version wrong, use default version!?XXX */
E 10
E 9
				CHECK( (vbval(P, u_char) != TP_VERSION ), 
D 9
					E_TP_INV_PVAL, ts_inv_pval, respond,
					(1 + (caddr_t)&vbptr(P)->tpv_val - P) )
E 9
I 9
					E_TP_INV_PVAL, ts_inv_pval, setversion,
D 10
					(1 + (caddr_t)&vbptr(P)->tpv_val - P) );
E 10
I 10
					(1 + (caddr_t)&vbptr(P)->tpv_val - (caddr_t)hdr) );
E 10
			setversion:
				version = vbval(P, u_char);
D 10

E 10
E 9
				break;
			case	TPP_acktime:
				vb_getval(P, u_short, acktime);
				acktime = ntohs(acktime);
				acktime = acktime/500; /* convert to slowtimo ticks */
				if((short)acktime <=0 )
					acktime = 2; /* don't allow a bad peer to screw us up */
				IFDEBUG(D_TPINPUT)
					printf("CR acktime 0x%x\n", acktime);
				ENDDEBUG
				break;

			case	TPP_alt_class:
				{
					u_char *aclass = 0;
					register int i;
I 10
					static u_char bad_alt_classes[5] =
						{ ~0, ~3, ~5, ~0xf, ~0x1f};
E 10

I 10
					aclass = 
						(u_char *) &(((struct tp_vbp *)P)->tpv_val);
E 10
					for (i = ((struct tp_vbp *)P)->tpv_len; i>0; i--) {
D 10
						aclass = 
							(u_char *) &(((struct tp_vbp *)P)->tpv_val);
D 2
						alt_classes |= (1<<(*aclass));
E 2
I 2
						alt_classes |= (1<<((*aclass)>>4));
E 10
I 10
						alt_classes |= (1<<((*aclass++)>>4));
E 10
E 2
					}
I 10
					CHECK( (bad_alt_classes[hdr->tpdu_CRclass] & alt_classes),
						E_TP_INV_PVAL, ts_inv_aclass, respond,
						((caddr_t)aclass) - (caddr_t)hdr);
E 10
					IFDEBUG(D_TPINPUT)
						printf("alt_classes 0x%x\n", alt_classes);
					ENDDEBUG
				}
				break;

			case	TPP_security:
			case	TPP_residER:
			case	TPP_priority:
			case	TPP_transdelay:
			case	TPP_throughput: 
			case	TPP_addl_info: 
			case	TPP_subseq:
I 14
			default:
E 14
				IFDEBUG(D_TPINPUT)
					printf("param ignored CR_TPDU code= 0x%x\n",
						 vbptr(P)->tpv_code);
				ENDDEBUG
				IncStat(ts_param_ignored);
				break;

			case	TPP_checksum:		
				IFDEBUG(D_TPINPUT)
					printf("CR before cksum\n");
				ENDDEBUG

				CHECK( iso_check_csum(m, tpdu_len), 
					E_TP_INV_PVAL, ts_bad_csum, discard, 0)

				IFDEBUG(D_TPINPUT)
					printf("CR before cksum\n");
				ENDDEBUG
				break;
D 14

			default:
				IncStat(ts_inv_pcode);
				error = E_TP_INV_PCODE;
				goto discard;

E 14
			}

		/* } */ END_WHILE_OPTIONS(P)

D 12
		if( lsufxlen == 0) {
E 12
I 12
		if (lsufxlen == 0) {
E 12
			/* can't look for a tpcb w/o any called sufx */
			error =  E_TP_LENGTH_INVAL;
			IncStat(ts_inv_sufx);
			goto respond;
		} else {
D 12
			register	struct tp_ref 	*rp;
			register	int			r;
			extern		int			tp_maxrefopen;
E 12
I 12
			register struct tp_pcb *t;
E 12
D 21

D 12
			rp = &tp_ref[1]; /* zero-th one is never open */
			for(  r=1 ; (r <= tp_maxrefopen) ; r++,rp++ ) {
				if (rp->tpr_state!=REF_OPENING) 
E 12
I 12
D 13
			for (t = tp_intercepts; t ; t->tp_nextlisten) {
E 13
I 13
			for (t = tp_intercepts; t ; t = t->tp_nextlisten) {
E 13
				if (laddr->sa_family != t->tp_nlproto->nlp_afamily)
E 12
					continue;
D 12
				if ( bcmp(lsufxloc, rp->tpr_pcb->tp_lsuffix, lsufxlen)==0 ) {
					tpcb =  rp->tpr_pcb;
					if( laddr->sa_family !=
							tpcb->tp_sock->so_proto->pr_domain->dom_family ) {
						IFDEBUG(D_CONN)
						 	printf(
					"MISMATCHED AF on CR! laddr.family 0x%x expected 0x%x\n",
							laddr->sa_family, 
							tpcb->tp_sock->so_proto->pr_domain->dom_family );
						ENDDEBUG
						continue;
					}
					IFTRACE(D_TPINPUT)
						tptrace(TPPTmisc, "tp_input: ref *lsufxloc refstate", 
							r, *lsufxloc, rp->tpr_state, 0);
					ENDTRACE
					/* found it */
					break;
E 12
I 12
D 13
				if ((*tpcb->tp_nlproto->nlp_cmpnetaddr)(
E 13
I 13
				if ((*t->tp_nlproto->nlp_cmpnetaddr)(
E 13
						t->tp_npcb, laddr, TP_LOCAL)) {
							intercepted = 1;
							goto check_duplicate_cr;
E 12
				}
			}
E 21
I 21
			/*
			 * The intention here is to trap all CR requests
			 * to a given nsap, for constructing transport
			 * service bridges at user level; so these
			 * intercepts should precede the normal listens.
			 * Phrasing the logic in this way also allows for
			 * mop-up listeners, which we don't currently implement.
			 * We also wish to have a single socket be able to
			 * listen over any network service provider,
			 * (cons or clns or ip).
			 */
E 21
D 12

			CHECK( (r > tp_maxrefopen), E_TP_NO_SESSION, ts_inv_sufx, respond,
E 12
I 12
D 13
			for (t = tp_listeners; t ; t->tp_nextlisten) {
				if (bcmp(lsufxloc, t->tp_lsuffix, lsufxlen) != 0)
					continue;
				if (laddr->sa_family != t->tp_nlproto->nlp_afamily)
					continue;
			}
E 13
I 13
			for (t = tp_listeners; t ; t = t->tp_nextlisten)
D 17
				if (bcmp(lsufxloc, t->tp_lsuffix, lsufxlen) == 0 &&
E 17
I 17
D 21
				if (lsufxlen == t->tp_lsuffixlen &&
					bcmp(lsufxloc, t->tp_lsuffix, lsufxlen) == 0 &&
E 17
					laddr->sa_family == t->tp_nlproto->nlp_afamily)
						break;
E 21
I 21
				if ((t->tp_lsuffixlen == 0 ||
					 (lsufxlen == t->tp_lsuffixlen &&
					  bcmp(lsufxloc, t->tp_lsuffix, lsufxlen) == 0)) &&
					((t->tp_flags & TPF_GENERAL_ADDR) ||
					 (laddr->sa_family == t->tp_domain &&
					  (*t->tp_nlproto->nlp_cmpnetaddr)
								(t->tp_npcb, laddr, TP_LOCAL))))
					break;

E 21
E 13
			CHECK(t == 0, E_TP_NO_SESSION, ts_inv_sufx, respond,
E 12
				(1 + 2 + (caddr_t)&hdr->_tpduf - (caddr_t)hdr))
				/* _tpduf is the fixed part; add 2 to get the dref bits of 
				 * the fixed part (can't take the address of a bit field) 
				 */
I 13
			IFDEBUG(D_TPINPUT)
				printf("checking if dup CR\n");
			ENDDEBUG
E 13
I 12
D 21
		check_duplicate_cr:
E 21
			tpcb = t;
			for (t = tpcb->tp_next; t != tpcb; t = t->tp_next) {
				if (sref != t->tp_fref)
					continue;
				if ((*tpcb->tp_nlproto->nlp_cmpnetaddr)(
						t->tp_npcb, faddr, TP_FOREIGN)) {
					IFDEBUG(D_TPINPUT)
						printf("duplicate CR discarded\n");
					ENDDEBUG
					goto discard;
				}
			}
			IFTRACE(D_TPINPUT)
				tptrace(TPPTmisc, "tp_input: tpcb *lsufxloc tpstate", 
					tpcb, *lsufxloc, tpcb->tp_state, 0);
			ENDTRACE
E 12
		}

		/* 
		 * WE HAVE A TPCB 
		 * already know that the classes in the CR match at least
		 * one class implemented, but we don't know yet if they
		 * include any classes permitted by this server.
		 */

		IFDEBUG(D_TPINPUT)
			printf("HAVE A TPCB 1: 0x%x\n", tpcb);
		ENDDEBUG
		IFDEBUG(D_CONN)
			printf(
"CR: bef CHKS: flags 0x%x class_to_use 0x%x alt 0x%x opt 0x%x tp_class 0x%x\n", 
				tpcb->tp_flags, class_to_use, alt_classes, opt, tpcb->tp_class);
		ENDDEBUG
		/* tpcb->tp_class doesn't include any classes not implemented  */
		class_to_use = (preferred_class & tpcb->tp_class);
		if( (class_to_use = preferred_class & tpcb->tp_class) == 0 )
			class_to_use = alt_classes & tpcb->tp_class;

		class_to_use = 1 << tp_mask_to_num(class_to_use);

		{
			tpp = tpcb->_tp_param;
			tpp.p_class = class_to_use;
			tpp.p_tpdusize = dusize;
I 26
			tpp.p_ptpdusize = pdusize;
E 26
			tpp.p_xtd_format = (opt & TPO_XTD_FMT) == TPO_XTD_FMT;
			tpp.p_xpd_service = (addlopt & TPAO_USE_TXPD) == TPAO_USE_TXPD;
			tpp.p_use_checksum = (tpp.p_class == TP_CLASS_0)?0:
				(addlopt & TPAO_NO_CSUM) == 0;
I 9
			tpp.p_version = version;
E 9
#ifdef notdef
			tpp.p_use_efc = (opt & TPO_USE_EFC) == TPO_USE_EFC;
			tpp.p_use_nxpd = (addlopt & TPAO_USE_NXPD) == TPAO_USE_NXPD;
			tpp.p_use_rcc = (addlopt & TPAO_USE_RCC) == TPAO_USE_RCC;
D 32
#endif notdef
E 32
I 32
#endif /* notdef */
E 32

		CHECK(
			tp_consistency(tpcb, 0 /* not force or strict */, &tpp) != 0, 
D 21
			E_TP_NEGOT_FAILED, ts_negotfailed, respond,
E 21
I 21
			E_TP_NEGOT_FAILED, ts_negotfailed, clear_parent_tcb,
E 21
			(1 + 2 + (caddr_t)&hdr->_tpdufr.CRCC - (caddr_t)hdr) 
				/* ^ more or less the location of class */
			)
		}
		IFTRACE(D_CONN)
			tptrace(TPPTmisc, 
				"after 1 consist class_to_use class, out, tpconsout",
				class_to_use, 
				tpcb->tp_class, dgout_routine, tpcons_output
				);
		ENDTRACE
		CHECK(
			((class_to_use == TP_CLASS_0)&&(dgout_routine != tpcons_output)),
D 21
			E_TP_NEGOT_FAILED, ts_negotfailed, respond,
E 21
I 21
			E_TP_NEGOT_FAILED, ts_negotfailed, clear_parent_tcb,
E 21
			(1 + 2 + (caddr_t)&hdr->_tpdufr.CRCC - (caddr_t)hdr) 
				/* ^ more or less the location of class */
			)
		IFDEBUG(D_CONN)
			printf("CR: after CRCCCHECKS: tpcb 0x%x, flags 0x%x\n", 
				tpcb, tpcb->tp_flags);
		ENDDEBUG
		takes_data = TRUE;
		e.ATTR(CR_TPDU).e_cdt  =  hdr->tpdu_CRcdt;
		e.ev_number = CR_TPDU;

		so = tpcb->tp_sock;
		if (so->so_options & SO_ACCEPTCONN) {
I 12
			struct tp_pcb *parent_tpcb = tpcb;
E 12
			/* 
			 * Create a socket, tpcb, ll pcb, etc. 
			 * for this newborn connection, and fill in all the values. 
			 */
			IFDEBUG(D_CONN)
				printf("abt to call tp_newsocket(0x%x, 0x%x, 0x%x, 0x%x)\n",
					so, laddr, faddr, cons_channel);
			ENDDEBUG
			if( (so = 
				tp_newsocket(so, faddr, cons_channel, 
					class_to_use, 
D 2
					(dgout_routine == tpcons_output)?ISO_CONS:ISO_CLNS)
E 2
I 2
					((tpcb->tp_netservice == IN_CLNS) ? IN_CLNS :
					(dgout_routine == tpcons_output)?ISO_CONS:ISO_CLNS))
E 2
					) == (struct socket *)0 ) {
				/* note - even if netservice is IN_CLNS, as far as
				 * the tp entity is concerned, the only differences
D 2
				 * are CO vs CL 
E 2
I 2
				 * are CO vs CL
E 2
				 */
				IFDEBUG(D_CONN)
					printf("tp_newsocket returns 0\n");
				ENDDEBUG
				goto discard;
I 21
			clear_parent_tcb:
				tpcb = 0;
				goto respond;
E 21
			}
			tpcb = sototpcb(so);
I 12
D 13
			insque(parent_tpcb, tpcb);
E 13
I 13
			insque(tpcb, parent_tpcb);
E 13
E 12

D 2
			/* stash the f suffix in the new tpcb */
			/* l suffix is already there */

			bcopy( fsufxloc, tpcb->tp_fsuffix, fsufxlen);
			if( (tpcb->tp_fsuffixlen = fsufxlen) == sizeof(short) ) {
				/* even if it's AF_ISO */
				bcopy (fsufxloc, &(satosin(faddr)->sin_port), sizeof(short));
				(tpcb->tp_nlproto->nlp_putsufx)(so->so_pcb, faddr, TP_FOREIGN);
			}

E 2
			/*
D 2
			 * stash the addresses in the net level pcb 
E 2
I 2
			 * Stash the addresses in the net level pcb 
E 2
			 * kind of like a pcbconnect() but don't need
			 * or want all those checks.
			 */
D 20
			(tpcb->tp_nlproto->nlp_putnetaddr)(so->so_pcb, faddr, TP_FOREIGN);
			(tpcb->tp_nlproto->nlp_putnetaddr)(so->so_pcb, laddr, TP_LOCAL);
E 20
I 20
			(tpcb->tp_nlproto->nlp_putnetaddr)(tpcb->tp_npcb, faddr, TP_FOREIGN);
			(tpcb->tp_nlproto->nlp_putnetaddr)(tpcb->tp_npcb, laddr, TP_LOCAL);
E 20

D 2
			/*
			 * in the AF_INET case, we need the l,f addrs to contain the ports
			 */
			if( tpcb->tp_domain == AF_INET) {
				CHECK((fsufxlen != sizeof(short))||(lsufxlen != sizeof(short)),
					E_TP_ADDR_UNK, ts_inv_dref, respond, 
					(fsufxloc - (caddr_t)hdr))
				bcopy (lsufxloc, &(satosin(laddr)->sin_port), sizeof(short));
				(tpcb->tp_nlproto->nlp_putsufx)(so->so_pcb, laddr, TP_LOCAL);
				/*
					this has already been done 'cause the fsufxlen is
					sizeof(short):
					bcopy (fsufxloc, &(satosin(faddr)->sin_port), 
						sizeof(short));
					(tpcb->tp_nlproto->nlp_putsufx)(so->so_pcb, faddr, 
						TP_FOREIGN);
				*/
			}
E 2
I 2
			/* stash the f suffix in the new tpcb */
D 12
			/* l suffix is already there */
E 12
E 2
D 3

E 3
I 2
D 21
			bcopy(fsufxloc, tpcb->tp_fsuffix, fsufxlen);
I 3
D 12

E 12
I 12
			/* l suffix is already there, unless this is an intercept case */
			if (intercepted)
				bcopy(lsufxloc, tpcb->tp_lsuffix, lsufxlen);
E 21
I 21
			if (tpcb->tp_fsuffixlen = fsufxlen) {
				bcopy(fsufxloc, tpcb->tp_fsuffix, fsufxlen);
				(tpcb->tp_nlproto->nlp_putsufx)
						(tpcb->tp_npcb, fsufxloc, fsufxlen, TP_FOREIGN);
			}
			/* stash the l suffix in the new tpcb */
			tpcb->tp_lsuffixlen = lsufxlen;
			bcopy(lsufxloc, tpcb->tp_lsuffix, lsufxlen);
E 21
E 12
E 3
			(tpcb->tp_nlproto->nlp_putsufx)
D 20
					(so->so_pcb, fsufxloc, fsufxlen, TP_FOREIGN);
E 20
I 20
D 21
					(tpcb->tp_npcb, fsufxloc, fsufxlen, TP_FOREIGN);
E 20
I 3
			(tpcb->tp_nlproto->nlp_putsufx)
E 21
D 20
					(so->so_pcb, lsufxloc, lsufxlen, TP_LOCAL);
E 20
I 20
					(tpcb->tp_npcb, lsufxloc, lsufxlen, TP_LOCAL);
E 20
E 3
D 12

E 12
E 2
#ifdef TP_PERF_MEAS
			if( tpcb->tp_perf_on = perf_meas ) { /* assignment */
				/* ok, let's create an mbuf for stashing the
				 * statistics if one doesn't already exist 
				 */
				(void) tp_setup_perf(tpcb);
			}
D 32
#endif TP_PERF_MEAS
E 32
I 32
#endif /* TP_PERF_MEAS */
E 32
			tpcb->tp_fref = sref;

			/* We've already checked for consistency with the options 
			 * set in tpp,  but we couldn't set them earlier because 
			 * we didn't want to change options in the LISTENING tpcb.
			 * Now we set the options in the new socket's tpcb.
			 */
			(void) tp_consistency( tpcb, TP_FORCE, &tpp);

			if(!tpcb->tp_use_checksum)
				IncStat(ts_csum_off);
			if(tpcb->tp_xpd_service)
				IncStat(ts_use_txpd);
			if(tpcb->tp_xtd_format)
				IncStat(ts_xtd_fmt);

D 24
			/*
			 * Get the maximum transmission unit from the lower layer(s)
			 * so we can negotiate a reasonable max TPDU size.
			 */
D 20
			(tpcb->tp_nlproto->nlp_mtu)(so, so->so_pcb,
E 20
I 20
			(tpcb->tp_nlproto->nlp_mtu)(so, tpcb->tp_npcb,
E 20
						&tpcb->tp_l_tpdusize, &tpcb->tp_tpdusize, 0);
E 24
			tpcb->tp_peer_acktime = acktime;

			/* 
			 * The following kludge is used to test retransmissions and 
			 * timeout during connection establishment.
			 */
			IFDEBUG(D_ZDREF)
				IncStat(ts_zdebug);
D 2
				tpcb->tp_fref = 0;
E 2
I 2
				/*tpcb->tp_fref = 0;*/
E 2
			ENDDEBUG
		}
I 28
		LOCAL_CREDIT(tpcb);
E 28
		IncStat(ts_CR_rcvd);
I 5
		if (!tpcb->tp_cebit_off) {
			tpcb->tp_win_recv = tp_start_win << 8;
			tpcb->tp_cong_sample.cs_size = 0;
D 28
			LOCAL_CREDIT(tpcb);
E 28
			CONG_INIT_SAMPLE(tpcb);
			CONG_UPDATE_SAMPLE(tpcb, ce_bit);
		}
D 23
		tpcb->tp_ackrcvd = 0;
E 23
E 5
	} else if ( dutype == ER_TPDU_type ) {
		/* 
		 * ER TPDUs have to be recognized separately
		 * because they don't necessarily have a tpcb
		 * with them and we don't want err out looking for such
		 * a beast.
		 * We could put a bunch of little kludges in the 
		 * next section of code so it would avoid references to tpcb
		 * if dutype == ER_TPDU_type but we don't want code for ERs to
		 * mess up code for data transfer.
		 */
		IncStat(ts_ER_rcvd);
		e.ev_number = ER_TPDU;
		e.ATTR(ER_TPDU).e_reason =  (u_char)hdr->tpdu_ERreason;
D 16
		takes_data = 1;
E 16
I 16
D 19
		takes_data = FALSE;
E 19
I 19
D 22
		CHECK (((int)dref <= 0 || dref >= N_TPREF || 
E 22
I 22
		CHECK (((int)dref <= 0 || dref >= tp_refinfo.tpr_size || 
E 22
			(tpcb = tp_ref[dref].tpr_pcb ) == (struct tp_pcb *) 0 ||
D 23
			tpcb->tp_refp->tpr_state == REF_FREE ||
			tpcb->tp_refp->tpr_state == REF_FROZEN),
E 23
I 23
			tpcb->tp_refstate == REF_FREE ||
			tpcb->tp_refstate == REF_FROZEN),
E 23
		       E_TP_MISM_REFS, ts_inv_dref, discard, 0)

E 19
E 16
	} else {
		/* tpdu type is CC, XPD, XAK, GR, AK, DR, DC, or DT */

		/* In the next 4 checks,
		 * _tpduf is the fixed part; add 2 to get the dref bits of 
		 * the fixed part (can't take the address of a bit field) 
		 */
I 15
D 21
#ifdef old_history
E 15
		if(cons_channel) {
D 15
#if NARGOXTWENTYFIVE > 0
E 15
I 15
#ifdef NARGOXTWENTYFIVE
E 15
			extern struct tp_pcb *cons_chan_to_tpcb();
E 21
I 21
#ifdef TPCONS
		if (cons_channel && dutype == DT_TPDU_type) {
			struct isopcb *isop = ((struct isopcb *)
				((struct pklcd *)cons_channel)->lcd_upnext);
			if (isop && isop->isop_refcnt == 1 && isop->isop_socket &&
				(tpcb = sototpcb(isop->isop_socket)) &&
				 (tpcb->tp_class == TP_CLASS_0/* || == CLASS_1 */)) {
				IFDEBUG(D_TPINPUT)
					printf("tpinput_dt: class 0 short circuit\n");
				ENDDEBUG
				dref = tpcb->tp_lref;
				sref = tpcb->tp_fref;
D 23
				CHECK( (tpcb->tp_refp->tpr_state == REF_FREE), 
E 23
I 23
				CHECK( (tpcb->tp_refstate == REF_FREE), 
E 23
					E_TP_MISM_REFS,ts_inv_dref, nonx_dref,
					(1 + 2 + (caddr_t)&hdr->_tpduf - (caddr_t)hdr))
				goto tp0_data;
			}
E 21

D 21
			tpcb = cons_chan_to_tpcb( cons_channel );
			/* Problem:  We may have a legit
			 * error situation yet we may or may not have 
			 * a correspondence between the tpcb and the vc,
			 * e.g., TP4cr--> <no dice, respond w/ DR on vc>
			 *          <---  DR
			 * Now it's up to TP to look at the tpdu and do one of:
			 * confirm(dgm)(cr),  confirm(circuit)(cr), reject(cr), or
			 * nothing, if the circuit is already open (any other tpdu). 
			 * Sigh.
			 */

			/* I don't know about this error value */
			CHECK( (tpcb == (struct tp_pcb *)0) ,
				E_TP_NO_CR_ON_NC, ts_inv_dref, respond, 
				(1 + 2 + (caddr_t)&hdr->_tpduf - (caddr_t)hdr))
#else
			printf("tp_input(): X25 NOT CONFIGURED!!\n");
E 21
I 21
		}
E 21
D 15
#endif NARGOXTWENTYFIVE > 0
			
		} else {
E 15
I 15
#endif
D 21
		} else
			/* we've now made the error reporting thing check for
			multiple channels and not close out if more than
			one in use */
#endif old_history
E 21
		{
E 15

D 22
			CHECK( ((int)dref <= 0 || dref >= N_TPREF) ,
E 22
I 22
			CHECK( ((int)dref <= 0 || dref >= tp_refinfo.tpr_size) ,
E 22
D 10
				E_TP_MISM_REFS,ts_inv_dref, respond,
E 10
I 10
				E_TP_MISM_REFS,ts_inv_dref, nonx_dref,
E 10
				(1 + 2 + (caddr_t)&hdr->_tpduf - (caddr_t)hdr))
			CHECK( ((tpcb = tp_ref[dref].tpr_pcb ) == (struct tp_pcb *) 0 ), 
D 10
				E_TP_MISM_REFS,ts_inv_dref, respond,
E 10
I 10
				E_TP_MISM_REFS,ts_inv_dref, nonx_dref,
E 10
				(1 + 2 + (caddr_t)&hdr->_tpduf - (caddr_t)hdr))
D 23
			CHECK( (tpcb->tp_refp->tpr_state == REF_FREE), 
E 23
I 23
			CHECK( (tpcb->tp_refstate == REF_FREE), 
E 23
D 10
				E_TP_MISM_REFS,ts_inv_dref, respond,
E 10
I 10
				E_TP_MISM_REFS,ts_inv_dref, nonx_dref,
E 10
				(1 + 2 + (caddr_t)&hdr->_tpduf - (caddr_t)hdr))
		}

		IFDEBUG(D_TPINPUT)
			printf("HAVE A TPCB 2: 0x%x\n", tpcb);
		ENDDEBUG

		/* causes a DR to be sent for CC; ER for all else */
D 23
		CHECK( (tpcb->tp_refp->tpr_state == REF_FROZEN),
E 23
I 23
		CHECK( (tpcb->tp_refstate == REF_FROZEN),
E 23
			(dutype == CC_TPDU_type?E_TP_NO_SESSION:E_TP_MISM_REFS),
			ts_inv_dref, respond,
			(1 + 2 + (caddr_t)&hdr->_tpduf - (caddr_t)hdr))

		IFDEBUG(D_TPINPUT)
			printf("state of dref %d ok, tpcb 0x%x\n", dref,tpcb);
		ENDDEBUG
		/* 
		 * At this point the state of the dref could be
		 * FROZEN: tpr_pcb == NULL,  has ( reference only) timers
		 *		   for example, DC may arrive after the close() has detached
		 *         the tpcb (e.g., if user turned off SO_LISTEN option)
		 * OPENING : a tpcb exists but no timers yet
		 * OPEN  : tpcb exists & timers are outstanding
		 */

I 5
        if (!tpcb->tp_cebit_off)
            CONG_UPDATE_SAMPLE(tpcb, ce_bit);

E 5
		dusize = tpcb->tp_tpdusize;
I 26
		pdusize = tpcb->tp_ptpdusize;
E 26

		dutype = hdr->tpdu_type << 8; /* for the switch below */ 

		WHILE_OPTIONS(P, hdr, tpcb->tp_xtd_format) /* { */

D 2
#		define caseof(x,y) case (((x)<<8)+(y))
E 2
I 2
#define caseof(x,y) case (((x)<<8)+(y))
E 2
		switch( dutype | vbptr(P)->tpv_code ) {

			caseof( CC_TPDU_type, TPP_addl_opt ): 
					/* not in class 0; 1 octet */
					vb_getval(P, u_char, addlopt);
					break;
			caseof( CC_TPDU_type, TPP_tpdu_size ): 
I 10
				{
					u_char odusize = dusize;
E 10
					vb_getval(P, u_char, dusize);
D 10
					CHECK( (dusize < TP_MIN_TPDUSIZE || dusize > 
						TP_MAX_TPDUSIZE), E_TP_INV_PVAL, ts_inv_pval, respond,
						(1 + (caddr_t)&vbptr(P)->tpv_val - P) )
E 10
I 10
					CHECK( (dusize < TP_MIN_TPDUSIZE ||
							dusize > TP_MAX_TPDUSIZE || dusize > odusize),
						E_TP_INV_PVAL, ts_inv_pval, respond,
						(1 + (caddr_t)&vbptr(P)->tpv_val - (caddr_t)hdr) )
E 10
					IFDEBUG(D_TPINPUT)
						printf("CC dusize 0x%x\n", dusize);
					ENDDEBUG
I 10
				}
E 10
					break;
I 26
			caseof( CC_TPDU_type, TPP_ptpdu_size ): 
				{
					u_short opdusize = pdusize;
					switch (vbptr(P)->tpv_len) {
					case 1: pdusize = vbval(P, u_char); break;
					case 2: pdusize = ntohs(vbval(P, u_short)); break;
					default: ;
					IFDEBUG(D_TPINPUT)
						printf("malformed prefered TPDU option\n");
					ENDDEBUG
					}
					CHECK( (pdusize == 0 ||
							(opdusize && (pdusize > opdusize))),
						E_TP_INV_PVAL, ts_inv_pval, respond,
						(1 + (caddr_t)&vbptr(P)->tpv_val - (caddr_t)hdr) )
				}
					break;
E 26
			caseof( CC_TPDU_type, TPP_calling_sufx):
					IFDEBUG(D_TPINPUT)
						printf("CC calling (local) sufxlen 0x%x\n", lsufxlen);
					ENDDEBUG
					lsufxloc = (caddr_t) &vbptr(P)->tpv_val;
					lsufxlen = vbptr(P)->tpv_len;
					break;
			caseof(	CC_TPDU_type, TPP_acktime ):
					/* class 4 only, 2 octets */
					vb_getval(P, u_short, acktime);
I 14
					acktime = ntohs(acktime);
E 14
					acktime = acktime/500; /* convert to slowtimo ticks */
					if( (short)acktime <=0 )
						acktime = 2;
					break;
			caseof(	CC_TPDU_type, TPP_called_sufx):
					fsufxloc = (caddr_t) &vbptr(P)->tpv_val;
					fsufxlen = vbptr(P)->tpv_len;
					IFDEBUG(D_TPINPUT)
						printf("CC called (foreign) sufx len %d\n", fsufxlen);
					ENDDEBUG
					break;

			caseof( CC_TPDU_type,	TPP_checksum):		
			caseof( DR_TPDU_type,	TPP_checksum):		
			caseof( DT_TPDU_type,	TPP_checksum):		
			caseof( XPD_TPDU_type,	TPP_checksum):		
					if( tpcb->tp_use_checksum )  {
						CHECK( iso_check_csum(m, tpdu_len), 
							E_TP_INV_PVAL, ts_bad_csum, discard, 0)
					}
					break;

			/*  this is different from the above because in the context
			 *  of concat/ sep tpdu_len might not be the same as hdr len 
			 */
			caseof( AK_TPDU_type,	TPP_checksum):		
			caseof( XAK_TPDU_type,	TPP_checksum):		
			caseof( DC_TPDU_type,	TPP_checksum):		
					if( tpcb->tp_use_checksum )  {
D 2
						CHECK( iso_check_csum(m, hdr->tpdu_li + 1), 
E 2
I 2
						CHECK( iso_check_csum(m, (int)hdr->tpdu_li + 1), 
E 2
							E_TP_INV_PVAL, ts_bad_csum, discard, 0)
					}
					break;
#ifdef notdef
			caseof( DR_TPDU_type, TPP_addl_info ):
				/* ignore - its length and meaning are
				 * user defined and there's no way
				 * to pass this info to the user anyway
				 */
				break;
D 32
#endif notdef
E 32
I 32
#endif /* notdef */
E 32

			caseof( AK_TPDU_type, TPP_subseq ):
				/* used after reduction of window */
				vb_getval(P, u_short, subseq);
				subseq = ntohs(subseq);
				IFDEBUG(D_ACKRECV)
D 23
					printf("AK Subsequence # 0x%x\n", subseq);
E 23
I 23
					printf("AK dref 0x%x Subseq 0x%x\n", dref, subseq);
E 23
				ENDDEBUG
				break;

			caseof( AK_TPDU_type, TPP_flow_cntl_conf ):
				{
					u_int 	ylwe;
					u_short ysubseq, ycredit;

					fcc_present = TRUE;
					vb_getval(P, u_int,	 	ylwe);
					vb_getval(P, u_short, 	ysubseq);
					vb_getval(P, u_short, 	ycredit);
					ylwe = ntohl(ylwe);
					ysubseq = ntohs(ysubseq);
					ycredit = ntohs(ycredit);
					IFDEBUG(D_ACKRECV)
D 23
						printf("AK FCC lwe 0x%x, subseq 0x%x, cdt 0x%x\n", 
							ylwe, ysubseq, ycredit);
E 23
I 23
						printf("%s%x, subseq 0x%x, cdt 0x%x dref 0x%x\n", 
							"AK FCC lwe 0x", ylwe, ysubseq, ycredit, dref);
E 23
					ENDDEBUG
				}
				break;

			default: 
				IFDEBUG(D_TPINPUT)
					printf("param ignored dutype 0x%x, code  0x%x\n",
						dutype, vbptr(P)->tpv_code);
				ENDDEBUG
				IFTRACE(D_TPINPUT)
					tptrace(TPPTmisc, "param ignored dutype code ",
						dutype, vbptr(P)->tpv_code ,0,0);
				ENDTRACE
				IncStat(ts_param_ignored);
				break;
#undef caseof
		}
		/* } */ END_WHILE_OPTIONS(P)

		/* NOTE: the variable dutype has been shifted left! */

		switch( hdr->tpdu_type ) {
		case CC_TPDU_type: 
			/* If CC comes back with an unacceptable class
			 * respond with a DR or ER
			 */

			opt = hdr->tpdu_CCoptions; /* 1 byte */

			{
				tpp = tpcb->_tp_param;
				tpp.p_class = (1<<hdr->tpdu_CCclass);
				tpp.p_tpdusize = dusize;
I 26
				tpp.p_ptpdusize = pdusize;
E 26
				tpp.p_dont_change_params = 0;
				tpp.p_xtd_format = (opt & TPO_XTD_FMT) == TPO_XTD_FMT;
				tpp.p_xpd_service = (addlopt & TPAO_USE_TXPD) == TPAO_USE_TXPD;
				tpp.p_use_checksum = (addlopt & TPAO_NO_CSUM) == 0;
#ifdef notdef
				tpp.p_use_efc = (opt & TPO_USE_EFC) == TPO_USE_EFC;
				tpp.p_use_nxpd = (addlopt & TPAO_USE_NXPD) == TPAO_USE_NXPD;
				tpp.p_use_rcc = (addlopt & TPAO_USE_RCC) == TPAO_USE_RCC;
D 32
#endif notdef
E 32
I 32
#endif /* notdef */
E 32

			CHECK(
				tp_consistency(tpcb, TP_FORCE, &tpp) != 0, 
				E_TP_NEGOT_FAILED, ts_negotfailed, respond,
				(1 + 2 + (caddr_t)&hdr->_tpdufr.CRCC - (caddr_t)hdr) 
					/* ^ more or less the location of class */
				)
			IFTRACE(D_CONN)
				tptrace(TPPTmisc, 
					"after 1 consist class, out, tpconsout",
					tpcb->tp_class, dgout_routine, tpcons_output, 0
					);
			ENDTRACE
			CHECK(
				((class_to_use == TP_CLASS_0)&&
					(dgout_routine != tpcons_output)),
				E_TP_NEGOT_FAILED, ts_negotfailed, respond,
				(1 + 2 + (caddr_t)&hdr->_tpdufr.CRCC - (caddr_t)hdr) 
					/* ^ more or less the location of class */
				)
I 15
#ifdef TPCONS
				if (tpcb->tp_netservice == ISO_CONS &&
					class_to_use == TP_CLASS_0) {
					struct isopcb *isop = (struct isopcb *)tpcb->tp_npcb;
					struct pklcd *lcp = (struct pklcd *)isop->isop_chan;
					lcp->lcd_flags &= ~X25_DG_CIRCUIT;
				}
#endif
E 15
			}
			if( ! tpcb->tp_use_checksum)
				IncStat(ts_csum_off);
			if(tpcb->tp_xpd_service)
				IncStat(ts_use_txpd);
			if(tpcb->tp_xtd_format)
				IncStat(ts_xtd_fmt);

			IFTRACE(D_CONN)
				tptrace(TPPTmisc, "after CC class flags dusize CCclass",
					tpcb->tp_class, tpcb->tp_flags, tpcb->tp_tpdusize, 
					hdr->tpdu_CCclass);
			ENDTRACE
D 24

			/* 
			 * Get the maximum transmission unit from the lower layer(s)
			 * so we can decide how large a TPDU size to negotiate.
			 * It would be nice if the arguments to this
			 * were more reasonable.
			 */
D 20
			(tpcb->tp_nlproto->nlp_mtu)(tpcb->tp_sock, tpcb->tp_sock->so_pcb,
E 20
I 20
			(tpcb->tp_nlproto->nlp_mtu)(tpcb->tp_sock, tpcb->tp_npcb,
E 20
						&tpcb->tp_l_tpdusize, &tpcb->tp_tpdusize, 0);

E 24
D 15
#ifdef	CONS
			/* Could be that this CC came in on a NEW vc, in which case
			 * we have to confirm it.
			 */
			if( cons_channel )
				cons_netcmd( CONN_CONFIRM, tpcb->tp_npcb, cons_channel, 
						tpcb->tp_class == TP_CLASS_4);
#endif	CONS

			tpcb->tp_peer_acktime = acktime;
E 15

			/* if called or calling suffices appeared on the CC, 
			 * they'd better jive with what's in the pcb
			 */
			if( fsufxlen ) {
				CHECK( ((tpcb->tp_fsuffixlen != fsufxlen) ||
					bcmp(fsufxloc, tpcb->tp_fsuffix, fsufxlen)),
					E_TP_INV_PVAL,ts_inv_sufx, respond, 
					(1+fsufxloc - (caddr_t)hdr))
			}
			if( lsufxlen ) {
				CHECK( ((tpcb->tp_lsuffixlen != lsufxlen) ||
					bcmp(lsufxloc, tpcb->tp_lsuffix, lsufxlen)),
					E_TP_INV_PVAL,ts_inv_sufx, respond, 
					(1+lsufxloc - (caddr_t)hdr))
			}

D 10
#ifdef notdef
			e.ATTR(CC_TPDU).e_sref =  (u_short)hdr->tpdu_CCsref;
#else
E 10
			e.ATTR(CC_TPDU).e_sref =  sref;
D 10
#endif notdef
E 10
			e.ATTR(CC_TPDU).e_cdt  =  hdr->tpdu_CCcdt;
			takes_data = TRUE;
			e.ev_number = CC_TPDU;
			IncStat(ts_CC_rcvd);
			break;

		case DC_TPDU_type:
D 10
#ifdef notdef
			if (hdr->tpdu_DCsref != tpcb->tp_fref)
				printf("INPUT: inv sufx DCsref 0x%x, tp_fref 0x%x\n",
					hdr->tpdu_DCsref, tpcb->tp_fref);
#else
E 10
			if (sref != tpcb->tp_fref)
				printf("INPUT: inv sufx DCsref 0x%x, tp_fref 0x%x\n",
					sref, tpcb->tp_fref);
D 10
#endif notdef
E 10
					
D 10
#ifdef notdef
			CHECK( (hdr->tpdu_DCsref != tpcb->tp_fref), 
				E_TP_MISM_REFS, ts_inv_sufx, respond,
				(1 + (caddr_t)&hdr->tpdu_DCsref - (caddr_t)hdr))
#else
E 10
			CHECK( (sref != tpcb->tp_fref), 
D 10
				E_TP_MISM_REFS, ts_inv_sufx, respond,
E 10
I 10
				E_TP_MISM_REFS, ts_inv_sufx, discard,
E 10
				(1 + (caddr_t)&hdr->tpdu_DCsref - (caddr_t)hdr))
D 10
#endif notdef
E 10
I 10
		
E 10
			e.ev_number = DC_TPDU;
			IncStat(ts_DC_rcvd);
			break;

		case DR_TPDU_type: 
			IFTRACE(D_TPINPUT)
				tptrace(TPPTmisc, "DR recvd", hdr->tpdu_DRreason, 0, 0, 0);
			ENDTRACE
D 10
#ifdef vax
			if(sref != tpcb->tp_fref)
E 10
I 10
			if (sref != tpcb->tp_fref) {
E 10
				printf("INPUT: inv sufx DRsref 0x%x tp_fref 0x%x\n",
					sref, tpcb->tp_fref);
I 10
			}
E 10
					
D 10
			CHECK( (sref != tpcb->tp_fref), 
				E_TP_MISM_REFS,ts_inv_sufx, respond,
E 10
I 10
			CHECK( (sref != 0 && sref != tpcb->tp_fref &&
					tpcb->tp_state != TP_CRSENT), 
				(TP_ERROR_SNDC | E_TP_MISM_REFS),ts_inv_sufx, respond,
E 10
				(1 + (caddr_t)&hdr->tpdu_DRsref - (caddr_t)hdr))

			e.ATTR(DR_TPDU).e_reason = hdr->tpdu_DRreason;
			e.ATTR(DR_TPDU).e_sref =  (u_short)sref;
D 10
#else
			if(hdr->tpdu_DRsref != tpcb->tp_fref)
				printf("INPUT: inv sufx DRsref 0x%x tp_fref 0x%x\n",
					hdr->tpdu_DRsref, tpcb->tp_fref);
					
			CHECK( (hdr->tpdu_DRsref != tpcb->tp_fref), 
				E_TP_MISM_REFS,ts_inv_sufx, respond,
				(1 + (caddr_t)&hdr->tpdu_DRsref - (caddr_t)hdr))

			e.ATTR(DR_TPDU).e_reason = 
				hdr->tpdu_DRreason;
			e.ATTR(DR_TPDU).e_sref =  (u_short)hdr->tpdu_DRsref;
#endif vax
E 10
			takes_data = TRUE;
			e.ev_number = DR_TPDU;
			IncStat(ts_DR_rcvd);
			break;

		case ER_TPDU_type:
			IFTRACE(D_TPINPUT)
				tptrace(TPPTmisc, "ER recvd", hdr->tpdu_ERreason,0,0,0);
			ENDTRACE
			e.ev_number = ER_TPDU;
			e.ATTR(ER_TPDU).e_reason = hdr->tpdu_ERreason;
			IncStat(ts_ER_rcvd);
			break;

		case AK_TPDU_type: 

			e.ATTR(AK_TPDU).e_subseq = subseq;
			e.ATTR(AK_TPDU).e_fcc_present = fcc_present;

			if (tpcb->tp_xtd_format) {
#ifdef BYTE_ORDER
				union seq_type seqeotX;

				seqeotX.s_seqeot = ntohl(hdr->tpdu_seqeotX);
				e.ATTR(AK_TPDU).e_seq = seqeotX.s_seq;
				e.ATTR(AK_TPDU).e_cdt = ntohs(hdr->tpdu_AKcdtX);
#else
				e.ATTR(AK_TPDU).e_cdt = hdr->tpdu_AKcdtX;
				e.ATTR(AK_TPDU).e_seq = hdr->tpdu_AKseqX;
D 32
#endif BYTE_ORDER
E 32
I 32
#endif /* BYTE_ORDER */
E 32
			} else {
				e.ATTR(AK_TPDU).e_cdt = hdr->tpdu_AKcdt;
				e.ATTR(AK_TPDU).e_seq = hdr->tpdu_AKseq;
			}
			IFTRACE(D_TPINPUT)
				tptrace(TPPTmisc, "AK recvd seq cdt subseq fcc_pres", 
					e.ATTR(AK_TPDU).e_seq, e.ATTR(AK_TPDU).e_cdt,
					subseq, fcc_present);
			ENDTRACE

			e.ev_number = AK_TPDU;
			IncStat(ts_AK_rcvd);
			IncPStat(tpcb, tps_AK_rcvd);
			break;

		case XAK_TPDU_type: 
			if (tpcb->tp_xtd_format) {
#ifdef BYTE_ORDER
				union seq_type seqeotX;

				seqeotX.s_seqeot = ntohl(hdr->tpdu_seqeotX);
				e.ATTR(XAK_TPDU).e_seq = seqeotX.s_seq;
#else
				e.ATTR(XAK_TPDU).e_seq = hdr->tpdu_XAKseqX;
D 32
#endif BYTE_ORDER
E 32
I 32
#endif /* BYTE_ORDER */
E 32
			} else {
				e.ATTR(XAK_TPDU).e_seq = hdr->tpdu_XAKseq;
			}
			e.ev_number = XAK_TPDU;
			IncStat(ts_XAK_rcvd);
			IncPStat(tpcb, tps_XAK_rcvd);
			break;

		case XPD_TPDU_type: 
			if (tpcb->tp_xtd_format) {
#ifdef BYTE_ORDER
				union seq_type seqeotX;

				seqeotX.s_seqeot = ntohl(hdr->tpdu_seqeotX);
				e.ATTR(XPD_TPDU).e_seq = seqeotX.s_seq;
#else
				e.ATTR(XPD_TPDU).e_seq = hdr->tpdu_XPDseqX;
D 32
#endif BYTE_ORDER
E 32
I 32
#endif /* BYTE_ORDER */
E 32
			} else {
				e.ATTR(XPD_TPDU).e_seq = hdr->tpdu_XPDseq;
			}
			takes_data = TRUE;
			e.ev_number = XPD_TPDU;
			IncStat(ts_XPD_rcvd);
			IncPStat(tpcb, tps_XPD_rcvd);
			break;

		case DT_TPDU_type:
			{ /* the y option will cause occasional packets to be dropped.
			   * A little crude but it works.
			   */

				IFDEBUG(D_DROP)
					if(time.tv_usec & 0x4 && hdr->tpdu_DTseq & 0x1) {
						IncStat(ts_ydebug);
						goto discard;
					}
				ENDDEBUG
			}
			if (tpcb->tp_class == TP_CLASS_0) {
I 21
			tp0_data:
E 21
				e.ATTR(DT_TPDU).e_seq = 0; /* actually don't care */
				e.ATTR(DT_TPDU).e_eot = (((struct tp0du *)hdr)->tp0du_eot);
			} else if (tpcb->tp_xtd_format) {
#ifdef BYTE_ORDER
				union seq_type seqeotX;

				seqeotX.s_seqeot = ntohl(hdr->tpdu_seqeotX);
				e.ATTR(DT_TPDU).e_seq = seqeotX.s_seq;
				e.ATTR(DT_TPDU).e_eot = seqeotX.s_eot;
#else
				e.ATTR(DT_TPDU).e_seq = hdr->tpdu_DTseqX;
				e.ATTR(DT_TPDU).e_eot = hdr->tpdu_DTeotX;
D 32
#endif BYTE_ORDER
E 32
I 32
#endif /* BYTE_ORDER */
E 32
			} else {
				e.ATTR(DT_TPDU).e_seq = hdr->tpdu_DTseq;
				e.ATTR(DT_TPDU).e_eot = hdr->tpdu_DTeot;
			}
			if(e.ATTR(DT_TPDU).e_eot)
				IncStat(ts_eot_input);
			takes_data = TRUE;
			e.ev_number = DT_TPDU;
			IncStat(ts_DT_rcvd);
			IncPStat(tpcb, tps_DT_rcvd);
			break;

		case GR_TPDU_type: 
			tp_indicate(T_DISCONNECT, tpcb, ECONNABORTED);
			/* drop through */
		default:
			/* this should NEVER happen because there is a
			 * check for dutype well above here
			 */
			error = E_TP_INV_TPDU; /* causes an ER  */
			IFDEBUG(D_TPINPUT)
				printf("INVALID dutype 0x%x\n", hdr->tpdu_type);
			ENDDEBUG
			IncStat(ts_inv_dutype);
			goto respond;
		}
	}
D 11

E 11
	/* peel off the tp header; 
	 * remember that the du_li doesn't count itself.
	 * This may leave us w/ an empty mbuf at the front of a chain.
	 * We can't just throw away the empty mbuf because hdr still points
	 * into the mbuf's data area and we're still using hdr (the tpdu header)
	 */
	m->m_len -= ((int)hdr->tpdu_li + 1);
D 2
	m->m_off += ((int)hdr->tpdu_li + 1);
E 2
I 2
	m->m_data += ((int)hdr->tpdu_li + 1);
E 2

D 2
	if(takes_data) {
		register int max;
E 2
I 2
	if (takes_data) {
		int max = tpdu_info[ hdr->tpdu_type ] [TP_MAX_DATA_INDEX];
		int datalen = tpdu_len - hdr->tpdu_li - 1, mbtype = MT_DATA;
D 8
		struct tp_control_hdr c_hdr;
E 8
I 8
D 16
		struct cmsghdr c_hdr;
E 8
		struct mbuf *n;
E 16
I 16
		struct {
			struct tp_disc_reason dr;
			struct cmsghdr x_hdr;
		} x;
#define c_hdr x.x_hdr
		register struct mbuf *n;
E 16
E 2

I 2
		CHECK( (max && datalen > max), E_TP_LENGTH_INVAL,
		        ts_inv_length, respond, (max + hdr->tpdu_li + 1) );
E 2
		switch( hdr->tpdu_type ) {
I 2

E 2
		case CR_TPDU_type:
I 2
			c_hdr.cmsg_type = TPOPT_CONN_DATA;
			goto make_control_msg;

E 2
		case CC_TPDU_type:
I 2
			c_hdr.cmsg_type = TPOPT_CFRM_DATA;
			goto make_control_msg;

E 2
		case DR_TPDU_type:
I 16
			x.dr.dr_hdr.cmsg_len = sizeof(x) - sizeof(c_hdr);
			x.dr.dr_hdr.cmsg_type = TPOPT_DISC_REASON;
			x.dr.dr_hdr.cmsg_level = SOL_TRANSPORT;
			x.dr.dr_reason = hdr->tpdu_DRreason;
E 16
I 2
			c_hdr.cmsg_type = TPOPT_DISC_DATA;
		make_control_msg:
I 16
			datalen += sizeof(c_hdr);
			c_hdr.cmsg_len = datalen;
E 16
			c_hdr.cmsg_level = SOL_TRANSPORT;
			mbtype = MT_CONTROL;
D 6
			if (datalen > 0) {
				datalen += sizeof(c_hdr);
				m->m_len += sizeof(c_hdr);
				m->m_data -= sizeof(c_hdr);
				c_hdr.cmsg_len = datalen;
				bcopy((caddr_t)&c_hdr, mtod(m, caddr_t),
								sizeof(c_hdr));
			}
E 6
I 6
D 11
			datalen += sizeof(c_hdr);
			m->m_len += sizeof(c_hdr);
			m->m_data -= sizeof(c_hdr);
			c_hdr.cmsg_len = datalen;
			bcopy((caddr_t)&c_hdr, mtod(m, caddr_t), sizeof(c_hdr));
E 11
I 11
			MGET(n, M_DONTWAIT, MT_DATA);
D 16
			if (n) {
				datalen += sizeof(c_hdr);
				n->m_len = sizeof(c_hdr);
				c_hdr.cmsg_len = datalen;
				*mtod(n, struct cmsghdr *) = c_hdr;
				n->m_next = m;
				m = n;
			} else {m_freem(m); m = 0; goto invoke;}
E 16
I 16
			if (n == 0)
				{m_freem(m); m = 0; datalen = 0; goto invoke; }
			if (hdr->tpdu_type == DR_TPDU_type) {
				datalen += sizeof(x) - sizeof(c_hdr);
				bcopy((caddr_t)&x, mtod(n, caddr_t), n->m_len = sizeof(x));
			} else
				bcopy((caddr_t)&c_hdr, mtod(n, caddr_t),
					  n->m_len = sizeof(c_hdr));
			n->m_next = m;
			m = n;
E 16
E 11
E 6
			/* FALLTHROUGH */

E 2
		case XPD_TPDU_type:
D 2
		case DT_TPDU_type:
			e.ATTR(DT_TPDU).e_datalen = tpdu_len - hdr->tpdu_li - 1;
			max = tpdu_info[ hdr->tpdu_type ] [TP_MAX_DATA_INDEX];
			CHECK( (max && e.ATTR(DT_TPDU).e_datalen > max),
				 E_TP_LENGTH_INVAL,ts_inv_length, respond, (max + hdr->tpdu_li + 1))
E 2
I 2
			if (mbtype != MT_CONTROL)
				mbtype = MT_OOBDATA;
			m->m_flags |= M_EOR;
			/* FALLTHROUGH */
E 2

I 2
		case DT_TPDU_type:
			for (n = m; n; n = n->m_next) { 
				MCHTYPE(n, mbtype);
			}
I 11
		invoke:
E 11
			e.ATTR(DT_TPDU).e_datalen = datalen;
E 2
			e.ATTR(DT_TPDU).e_data =  m;
			break;

		default:
			printf(
				"ERROR in tp_input! hdr->tpdu_type 0x%x takes_data 0x%x m 0x%x\n",
				hdr->tpdu_type, takes_data, m);
			break;
		}
		/* prevent m_freem() after tp_driver() from throwing it all away */
		m = MNULL;
	}

	IncStat(ts_tpdu_rcvd);

	IFDEBUG(D_TPINPUT)
		printf( "tp_input: before driver, state 0x%x event 0x%x m 0x%x",
			tpcb->tp_state, e.ev_number, m );
		printf(" e.e_data 0x%x\n", e.ATTR(DT_TPDU).e_data);
		printf("takes_data 0x%x m_len 0x%x, tpdu_len 0x%x\n",
			takes_data, (m==MNULL)?0:m->m_len,  tpdu_len);
	ENDDEBUG
D 5

	if( tpcb->tp_decbit != 0 ) /* unsigned 4 bits */
		tpcb->tp_decbit --;
E 5

	error = tp_driver(tpcb, &e);

	ASSERT(tpcb != (struct tp_pcb *)0);
	ASSERT(tpcb->tp_sock != (struct socket *)0);
	if( tpcb->tp_sock->so_error == 0 )
		tpcb->tp_sock->so_error = error;

	/* Kludge to keep the state tables under control (adding
	 * data on connect & disconnect & freeing the mbuf containing
	 * the data would have exploded the tables and made a big mess ).
	 */
	switch(e.ev_number) {
		case CC_TPDU:
		case DR_TPDU:
		case CR_TPDU:
			m = e.ATTR(CC_TPDU).e_data; /* same field for all three dutypes */
			IFDEBUG(D_TPINPUT)
				printf("after driver, restoring m to 0x%x, takes_data 0x%x\n", 
				m, takes_data);
			ENDDEBUG
			break;
		default:
			break;
	}
	/* Concatenated sequences are terminated by any tpdu that 
	 * carries data: CR, CC, DT, XPD, DR.
	 * All other tpdu types may be concatenated: AK, XAK, DC, ER.
	 */

separate:
	if ( takes_data == 0 )  {
		ASSERT( m != MNULL );
		/* 
		 * we already peeled off the prev. tp header so 
		 * we can just pull up some more and repeat
		 */

I 2
		if( m = tp_inputprep(m) ) {
E 2
		IFDEBUG(D_TPINPUT)
			hdr = mtod(m, struct tpdu *);
			printf("tp_input @ separate: hdr 0x%x size %d m 0x%x\n", 
			hdr, (int) hdr->tpdu_li + 1, m);
			dump_mbuf(m, "tp_input after driver, at separate");
		ENDDEBUG

D 2
		if( m = tp_inputprep(m) ) {
E 2
			IncStat(ts_concat_rcvd);
			goto again;
		}
	}
	if ( m != MNULL ) {
		IFDEBUG(D_TPINPUT)
			printf("tp_input : m_freem(0x%x)\n", m);
		ENDDEBUG
		m_freem(m);
		IFDEBUG(D_TPINPUT)
			printf("tp_input : after m_freem 0x%x\n", m);
		ENDDEBUG
	}
	return (ProtoHook) tpcb;

discard:
	/* class 4: drop the tpdu */
	/* class 2,0: Should drop the net connection, if you can figure out
	 * to which connection it applies
	 */
	IFDEBUG(D_TPINPUT)
		printf("tp_input DISCARD\n");
	ENDDEBUG
	IFTRACE(D_TPINPUT)
		tptrace(TPPTmisc, "tp_input DISCARD m",  m,0,0,0);
	ENDTRACE
	m_freem(m);
	IncStat(ts_recv_drop);
	return (ProtoHook)0;

I 10
nonx_dref:
	switch (dutype) {
	default:
		goto discard;
	case CC_TPDU_type:
		/* error = E_TP_MISM_REFS; */
		break;
	case DR_TPDU_type:
		error |= TP_ERROR_SNDC;
	}
E 10
respond:
D 11
	IFDEBUG(D_ERROR_EMIT)
E 11
I 11
	IFDEBUG(D_TPINPUT)
E 11
D 10
		printf("RESPOND: error 0x%x, errloc 0x%x\n", error, errloc);
E 10
I 10
		printf("RESPOND: error 0x%x, errlen 0x%x\n", error, errlen);
E 10
	ENDDEBUG
	IFTRACE(D_TPINPUT)
D 10
		tptrace(TPPTmisc, "tp_input RESPOND m error sref",  m,error,sref,0);
E 10
I 10
		tptrace(TPPTmisc, "tp_input RESPOND m error sref", m, error, sref, 0);
E 10
	ENDTRACE
D 10
	if( sref == 0 )
E 10
I 10
	if (sref == 0)
E 10
		goto discard;
D 2
	(void) tp_error_emit(error, sref, faddr, laddr, 
		m, errloc, tpcb, cons_channel, dgout_routine
		);
E 2
I 2
	(void) tp_error_emit(error, (u_long)sref, (struct sockaddr_iso *)faddr,
D 10
				(struct sockaddr_iso *)laddr, m, (int)errloc, tpcb,
E 10
I 10
				(struct sockaddr_iso *)laddr, m, errlen, tpcb,
E 10
D 21
				(int)cons_channel, dgout_routine);
E 21
I 21
				cons_channel, dgout_routine);
E 21
E 2
	IFDEBUG(D_ERROR_EMIT)
		printf("tp_input after error_emit\n");
	ENDDEBUG

#ifdef lint
	printf("",sref,opt);
D 32
#endif lint
E 32
I 32
#endif /* lint */
E 32
	IncStat(ts_recv_drop);
	return (ProtoHook)0;
}


/*
 * NAME: tp_headersize()
 *
 * CALLED FROM:
 *  tp_emit() and tp_sbsend()
 *  TP needs to know the header size so it can figure out how
 *  much data to put in each tpdu.
 *
 * FUNCTION, ARGUMENTS, and RETURN VALUE:
 *  For a given connection, represented by (tpcb), and 
 *  tpdu type (dutype), return the size of a tp header.
 *
 * RETURNS:	  the expected size of the heade in bytesr
 *
 * SIDE EFFECTS:	
 *
 * NOTES:	 It would be nice if it got the network header size as well.
 */
int
tp_headersize(dutype, tpcb) 
	int 			dutype;
	struct tp_pcb 	*tpcb;
{
	register int size = 0;

	IFTRACE(D_CONN)
		tptrace(TPPTmisc, "tp_headersize dutype class xtd_format",
			dutype, tpcb->tp_class, tpcb->tp_xtd_format, 0);
	ENDTRACE
	if( !( (tpcb->tp_class == TP_CLASS_0) || 
			(tpcb->tp_class == TP_CLASS_4) || 
			(dutype == DR_TPDU_type) || 
			(dutype == CR_TPDU_type) )) {
				printf("tp_headersize:dutype 0x%x, class 0x%x", 
			dutype, tpcb->tp_class);
	/* TODO: identify this and GET RID OF IT */
	}
	ASSERT( (tpcb->tp_class == TP_CLASS_0) || 
			(tpcb->tp_class == TP_CLASS_4) || 
			(dutype == DR_TPDU_type) || 
			(dutype == CR_TPDU_type) );

	if( tpcb->tp_class == TP_CLASS_0 ) {
		size =  tpdu_info[ dutype ] [TP_LEN_CLASS_0_INDEX];
	} else  {
		size = tpdu_info[ dutype ] [tpcb->tp_xtd_format];
	} 
	return size;
	/* caller must get network level header size separately */
}
E 1
