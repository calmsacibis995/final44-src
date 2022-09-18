h10084
s 00002/00002/00728
d D 8.1 93/06/10 23:21:32 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00728
d D 7.29 93/06/10 21:02:23 sklower 29 28
c fix suggested by Jim Mostek & Tim Kirby against mbuf leek on explicitly
c retrieving Xtpdu's
e
s 00003/00003/00726
d D 7.28 93/05/25 11:52:19 bostic 28 27
c trailing comment after #else or #endif
e
s 00020/00020/00709
d D 7.27 92/10/11 12:22:15 bostic 27 26
c make kernel includes standard
e
s 00002/00002/00727
d D 7.26 92/05/11 15:03:45 sklower 26 25
c bugfix from julian@tfs.com (Julian Elischer)
e
s 00002/00002/00727
d D 7.25 92/01/07 14:25:12 sklower 25 24
c changes required by nov 92 version of socketvar.h
e
s 00000/00002/00729
d D 7.24 91/10/02 19:48:32 sklower 24 23
c mtu calculation done by tp_route_to.
e
s 00006/00014/00725
d D 7.23 91/08/30 12:12:43 sklower 23 22
c paranoia about freeing a tpcb while still in the list of bound tcb's
c or list of children of a given TSEL
e
s 00004/00067/00735
d D 7.22 91/08/28 12:55:00 sklower 22 21
c move packetizing routine to tp_subr.c
e
s 00012/00012/00790
d D 7.21 91/08/28 12:47:35 sklower 21 20
c fix outright bug disrupting chain of bound tpcb's -- PRU_DETACH
c may happen twice; combine intercepts and normal listeners into single chain.
e
s 00004/00010/00798
d D 7.20 91/07/29 14:55:21 sklower 20 19
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00009/00020/00799
d D 7.19 91/07/23 17:03:59 sklower 19 18
c note semi working version with  only listen and bind changes
e
s 00012/00012/00807
d D 7.18 91/07/18 20:33:22 sklower 18 17
c this changes reflect getting rid of so_tpcb.
e
s 00001/00001/00818
d D 7.17 91/06/27 22:06:12 sklower 17 16
c minor changes to compile under both new and old vm systems
e
s 00009/00005/00810
d D 7.16 91/05/06 19:24:45 bostic 16 15
c new copyright; att/bsd/shared
e
s 00017/00021/00798
d D 7.15 91/04/26 14:56:53 sklower 15 14
c allow implict confirmation by sending data after accept()
e
s 00000/00001/00819
d D 7.14 91/03/12 16:05:12 sklower 14 13
c fix from mostek@cray
e
s 00001/00001/00819
d D 7.13 90/06/29 11:14:51 sklower 13 12
c fix minor bugs in setting up cross-list of listeners, intercepters, and their descendents
e
s 00025/00000/00795
d D 7.12 90/06/28 19:40:29 sklower 12 11
c check for duplicate CR's; allow intercepting all CR's to a given
c nsap; not yet tested, but check in for tape anyhow
e
s 00036/00036/00759
d D 7.11 90/06/26 18:54:47 sklower 11 10
c conform to UC kernel conventions concerning if(, function calls, etc.
e
s 00002/00002/00793
d D 7.10 90/05/30 11:56:51 sklower 10 9
c tp_control_hdr obsoleted by cmsghdr in socket.h
e
s 00020/00014/00775
d D 7.9 90/05/14 16:03:06 sklower 9 8
c new conventions for who frees ancillary data
e
s 00003/00003/00786
d D 7.8 90/04/05 11:03:53 sklower 8 7
c access rights made special case of ancillary data
e
s 00029/00018/00760
d D 7.7 90/01/17 00:18:35 sklower 7 6
c more fixes to silly window fix this version 6 dec 89.
e
s 00011/00012/00767
d D 7.6 89/11/28 11:16:36 sklower 6 5
c silly window fix causes panics; fix ``fix''
e
s 00058/00011/00721
d D 7.5 89/09/22 00:44:14 sklower 5 4
c fixes to tracing and avoiding silly window between
c socket layer and transport; more changes to come to usrreq and tp_send.
e
s 00056/00078/00676
d D 7.4 89/08/29 13:45:52 sklower 4 3
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00000/00001/00754
d D 7.3 89/05/05 00:27:55 mckusick 3 2
c get rid of unneeded include's
e
s 00163/00192/00592
d D 7.2 89/04/22 11:55:51 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00784/00000/00000
d D 7.1 88/12/14 15:30:22 sklower 1 0
c date and time created 88/12/14 15:30:22 by sklower
e
u
U
t
T
I 16
/*-
D 30
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 16
I 1
/***********************************************************
D 5
		Copyright IBM Corporation 1987
E 5
I 5
				Copyright IBM Corporation 1987
E 5

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
 * $Header: tp_usrreq.c,v 5.4 88/11/18 17:29:18 nhall Exp $
 * $Source: /usr/argo/sys/netiso/RCS/tp_usrreq.c,v $
I 4
D 5
 *	%W% (Berkeley) %G% *
E 5
I 5
D 16
 *	%W% (Berkeley) %G%
E 16
E 5
E 4
 *
 * tp_usrreq(), the fellow that gets called from most of the socket code.
 * Pretty straighforward.
 * THe only really awful stuff here is the OOB processing, which is done
 * wholly here.
 * tp_rcvoob() and tp_sendoob() are contained here and called by tp_usrreq().
 */
D 16

#ifndef lint
static char *rcsid = "$Header: tp_usrreq.c,v 5.4 88/11/18 17:29:18 nhall Exp $";
#endif lint
E 16

D 27
#include "param.h"
#include "systm.h"
D 3
#include "dir.h"
E 3
D 17
#include "user.h"
E 17
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "domain.h"
#include "protosw.h"
#include "errno.h"
I 17
#include "time.h"
E 27
I 27
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/time.h>
E 27
E 17

D 2
#include "../netiso/tp_param.h"
#include "../netiso/tp_timer.h"
#include "../netiso/tp_stat.h"
#include "../netiso/tp_seq.h"
#include "../netiso/tp_ip.h"
#include "../netiso/tp_pcb.h"
#include "../netiso/argo_debug.h"
#include "../netiso/tp_trace.h"
#include "../netiso/tp_meas.h"
#include "../netiso/iso.h"
#include "../netiso/iso_errno.h"
E 2
I 2
D 27
#include "tp_param.h"
#include "tp_timer.h"
#include "tp_stat.h"
#include "tp_seq.h"
#include "tp_ip.h"
#include "tp_pcb.h"
#include "argo_debug.h"
#include "tp_trace.h"
#include "tp_meas.h"
#include "iso.h"
#include "iso_errno.h"
E 27
I 27
#include <netiso/tp_param.h>
#include <netiso/tp_timer.h>
#include <netiso/tp_stat.h>
#include <netiso/tp_seq.h>
#include <netiso/tp_ip.h>
#include <netiso/tp_pcb.h>
#include <netiso/argo_debug.h>
#include <netiso/tp_trace.h>
#include <netiso/tp_meas.h>
#include <netiso/iso.h>
#include <netiso/iso_errno.h>
E 27
E 2

D 19
int tp_attach(), tp_driver();
E 19
I 19
int tp_attach(), tp_driver(), tp_pcbbind();
E 19
I 7
int TNew;
int TPNagle1, TPNagle2;
I 12
struct tp_pcb *tp_listeners, *tp_intercepts;
E 12
E 7

#ifdef ARGO_DEBUG
/*
 * CALLED FROM:
 *  anywhere you want to debug...
 * FUNCTION and ARGUMENTS:
 *  print (str) followed by the control info in the mbufs of an mbuf chain (n)
 */
void
dump_mbuf(n, str)
	struct mbuf *n;
	char *str;
{
	struct mbuf *nextrecord;

	printf("dump %s\n", str);

D 11
	if( n == MNULL)  {
E 11
I 11
	if (n == MNULL)  {
E 11
		printf("EMPTY:\n");
		return;
	}
		
D 11
	for(;n;) {
E 11
I 11
	while (n) {
E 11
		nextrecord = n->m_act;
		printf("RECORD:\n");
		while (n) {
D 2
			printf("%x : Len %x Of %x A %x Nx %x Tp %x\n",
				n, n->m_len, n->m_off, n->m_act, n->m_next, n->m_type);
E 2
I 2
			printf("%x : Len %x Data %x A %x Nx %x Tp %x\n",
				n, n->m_len, n->m_data, n->m_act, n->m_next, n->m_type);
E 2
#ifdef notdef
			{
				register char *p = mtod(n, char *);
				register int i;

				printf("data: ");
D 11
				for(i=0; i < n->m_len; i++ ) {
					if(i%8 == 0)
E 11
I 11
				for (i = 0; i < n->m_len; i++) {
					if (i%8 == 0)
E 11
						printf("\n");
					printf("0x%x ", *(p+i));
				}
				printf("\n");
			}
D 28
#endif notdef
E 28
I 28
#endif /* notdef */
E 28
D 11
			if( n->m_next == n ) {
E 11
I 11
			if (n->m_next == n) {
E 11
				printf("LOOP!\n");
				return;
			}
			n = n->m_next;
		}
		n = nextrecord;
	}
	printf("\n");
}

D 28
#endif ARGO_DEBUG
E 28
I 28
#endif /* ARGO_DEBUG */
E 28

/*
 * CALLED FROM:
 *  tp_usrreq(), PRU_RCVOOB
 * FUNCTION and ARGUMENTS:
 * 	Copy data from the expedited data socket buffer into
 * 	the pre-allocated mbuf m.
 * 	There is an isomorphism between XPD TPDUs and expedited data TSDUs.
 * 	XPD tpdus are limited to 16 bytes of data so they fit in one mbuf.
 * RETURN VALUE:
 *  EINVAL if debugging is on and a disaster has occurred
 *  ENOTCONN if the socket isn't connected
 *  EWOULDBLOCK if the socket is in non-blocking mode and there's no
 *		xpd data in the buffer
 *  E* whatever is returned from the fsm.
 */
D 2
static int 
E 2
tp_rcvoob(tpcb, so, m, outflags, inflags)
	struct tp_pcb	*tpcb;
	register struct socket	*so;
	register struct mbuf 	*m;
	int 		 	*outflags;
	int 		 	inflags;
{
	register struct mbuf *n;
D 2
	register struct sockbuf *sb = &tpcb->tp_Xrcv;
E 2
I 2
	register struct sockbuf *sb = &so->so_rcv;
E 2
	struct tp_event E;
	int error = 0;
I 2
	register struct mbuf **nn;
E 2

	IFDEBUG(D_XPD)
		printf("PRU_RCVOOB, sostate 0x%x\n", so->so_state);
	ENDDEBUG

	/* if you use soreceive */
D 11
	if (m==MNULL)
E 11
I 11
	if (m == MNULL)
E 11
		return ENOBUFS;

restart:
D 4
	sblock(sb);

E 4
	if ((((so->so_state & SS_ISCONNECTED) == 0)
		 || (so->so_state & SS_ISDISCONNECTING) != 0) &&
		(so->so_proto->pr_flags & PR_CONNREQUIRED)) {
			return ENOTCONN;
	}

D 2
	if ( sb->sb_cc == 0) {
E 2
I 2
	/* Take the first mbuf off the chain.
	 * Each XPD TPDU gives you a complete TSDU so the chains don't get 
	 * coalesced, but one TSDU may span several mbufs.
	 * Nevertheless, since n should have a most 16 bytes, it
	 * will fit into m.  (size was checked in tp_input() )
	 */

	/*
	 * Code for excision of OOB data should be added to
	 * uipc_socket2.c (like sbappend).
	 */
	
I 4
D 25
	sblock(sb);
E 25
I 25
	sblock(sb, M_WAITOK);
E 25
E 4
	for (nn = &sb->sb_mb; n = *nn; nn = &n->m_act)
		if (n->m_type == MT_OOBDATA)
			break;

	if (n == 0) {
E 2
D 11
		ASSERT( (tpcb->tp_flags & TPF_DISC_DATA_IN)  == 0 );
E 11
I 11
D 14
		ASSERT((tpcb->tp_flags & TPF_DISC_DATA_IN) == 0);
E 14
E 11
		IFDEBUG(D_XPD)
			printf("RCVOOB: empty queue!\n");
		ENDDEBUG
I 4
		sbunlock(sb);
E 4
		if (so->so_state & SS_NBIO) {
			return  EWOULDBLOCK;
		}
D 4
		sbunlock(sb);
E 4
		sbwait(sb);
		goto restart;
	}
D 2
	/* Take the first mbuf off the chain.
	 * Each XPD TPDU gives you a complete TSDU so the chains don't get 
	 * coalesced, but one TSDU may span several mbufs.
	 * Nevertheless, since n should have a most 16 bytes, it
	 * will fit into m.  (size was checked in tp_input() )
	 */

	n = sb->sb_mb;
	ASSERT((n->m_type == TPMT_DATA) ||
		n->m_type == TPMT_IPHDR || n->m_type == TPMT_TPHDR);

	/* 
	 * mtod doesn't work for cluster-type mbufs, hence this disaster check: 
	 */
	if( n->m_off > MMAXOFF )
		panic("tp_rcvoob: unexpected cluster ");

	m->m_next = MNULL;
	m->m_act = MNULL;
	m->m_off = MMINOFF;
E 2
	m->m_len = 0;

	/* Assuming at most one xpd tpdu is in the buffer at once */
D 11
	while ( n != MNULL ) {
E 11
I 11
	while (n != MNULL) {
E 11
		m->m_len += n->m_len;
D 2
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t), n->m_len);
		m->m_off += n->m_len; /* so mtod() in bcopy() above gives right addr */
E 2
I 2
		bcopy(mtod(n, caddr_t), mtod(m, caddr_t), (unsigned)n->m_len);
		m->m_data += n->m_len; /* so mtod() in bcopy() above gives right addr */
E 2
		n = n->m_next;
	}
D 2
	m->m_off = MMINOFF; /* restore it to its proper value */
E 2
I 2
	m->m_data = m->m_dat;
	m->m_flags |= M_EOR;
E 2

	IFDEBUG(D_XPD)
		printf("tp_rcvoob: xpdlen 0x%x\n", m->m_len);
		dump_mbuf(so->so_rcv.sb_mb, "RCVOOB: Rcv socketbuf");
		dump_mbuf(sb->sb_mb, "RCVOOB: Xrcv socketbuf");
	ENDDEBUG

D 2
	if( (inflags & MSG_PEEK) == 0 )
		sbdrop(sb, m->m_len);
E 2
I 2
D 11
	if( (inflags & MSG_PEEK) == 0 ) {
E 11
I 11
	if ((inflags & MSG_PEEK) == 0) {
E 11
		n = *nn;
		*nn = n->m_act;
D 29
		sb->sb_cc -= m->m_len;
E 29
I 29
		for (; n; n = m_free(n)) 
			sbfree(sb, n);
E 29
	}
E 2

release:
	sbunlock(sb);

	IFTRACE(D_XPD)
		tptraceTPCB(TPPTmisc, "PRU_RCVOOB @ release sb_cc m_len",
D 11
			tpcb->tp_Xrcv.sb_cc, m->m_len,0,0 );
E 11
I 11
			tpcb->tp_Xrcv.sb_cc, m->m_len, 0, 0);
E 11
	ENDTRACE
D 2
	if(outflags)
		*outflags = MSG_OOB | MSG_EOTSDU | inflags; /* always on xpd recv */
E 2
	if (error == 0)
		error = DoEvent(T_USR_Xrcvd); 
	return error;
}

/*
 * CALLED FROM:
 *  tp_usrreq(), PRU_SENDOOB
 * FUNCTION and ARGUMENTS:
 * 	Send what's in the mbuf chain (m) as an XPD TPDU.
 * 	The mbuf may not contain more then 16 bytes of data.
 * 	XPD TSDUs aren't segmented, so they translate into
 * 	exactly one XPD TPDU, with EOT bit set.
 * RETURN VALUE:
 *  EWOULDBLOCK if socket is in non-blocking mode and the previous
 *   xpd data haven't been acked yet.
 *  EMSGSIZE if trying to send > max-xpd bytes (16)
 *  ENOBUFS if ran out of mbufs
 */
D 2
static int
E 2
tp_sendoob(tpcb, so, xdata, outflags)
	struct tp_pcb	*tpcb;
	register struct socket	*so;
	register struct mbuf 	*xdata;
	int 		 	*outflags; /* not used */
{
	/*
	 * Each mbuf chain represents a sequence # in the XPD seq space.
	 * The first one in the queue has sequence # tp_Xuna.
	 * When we add to the XPD queue, we stuff a zero-length
	 * mbuf (mark) into the DATA queue, with its sequence number in m_next
	 * to be assigned to this XPD tpdu, so data xfer can stop
	 * when it reaches the zero-length mbuf if this XPD TPDU hasn't
	 * yet been acknowledged.  
	 */
	register struct sockbuf *sb = &(tpcb->tp_Xsnd);
	register struct mbuf 	*xmark;
	register int 			len=0;
	struct tp_event E;

	IFDEBUG(D_XPD)
		printf("tp_sendoob:");
D 11
		if(xdata)
E 11
I 11
		if (xdata)
E 11
			printf("xdata len 0x%x\n", xdata->m_len);
	ENDDEBUG
D 4
oob_again:
E 4
	/* DO NOT LOCK the Xsnd buffer!!!! You can have at MOST one 
	 * socket buf locked at any time!!! (otherwise you might
	 * sleep() in sblock() w/ a signal pending and cause the
	 * system call to be aborted w/ a locked socketbuf, which
	 * is a problem.  So the so_snd buffer lock
	 * (done in sosend()) serves as the lock for Xpd.
	 */
D 4
	if (sb->sb_mb) { /* anything already in this sockbuf? */
E 4
I 4
	if (sb->sb_mb) { /* Anything already in eXpedited data sockbuf? */
E 4
		if (so->so_state & SS_NBIO) {
			return EWOULDBLOCK;
		}
D 4
		sbunlock(&so->so_snd);
		sbwait(&so->so_snd);
		sblock(&so->so_snd);
		goto oob_again;
E 4
I 4
		while (sb->sb_mb) {
			sbunlock(&so->so_snd); /* already locked by sosend */
			sbwait(&so->so_snd);
D 25
			sblock(&so->so_snd);  /* sosend will unlock on return */
E 25
I 25
			sblock(&so->so_snd, M_WAITOK);  /* sosend will unlock on return */
E 25
		}
E 4
	}

	if (xdata == (struct mbuf *)0) {
		/* empty xpd packet */
D 2
		MGET(xdata, M_WAIT, TPMT_DATA);
E 2
I 2
		MGETHDR(xdata, M_WAIT, MT_OOBDATA);
E 2
		if (xdata == NULL) {
			return ENOBUFS;
		}
		xdata->m_len = 0;
D 2
		xdata->m_act = MNULL;
E 2
I 2
		xdata->m_pkthdr.len = 0;
E 2
	}
	IFDEBUG(D_XPD)
		printf("tp_sendoob 1:");
D 11
		if(xdata)
E 11
I 11
		if (xdata)
E 11
			printf("xdata len 0x%x\n", xdata->m_len);
	ENDDEBUG
	xmark = xdata; /* temporary use of variable xmark */
	while (xmark) {
		len += xmark->m_len;
		xmark = xmark->m_next;
	}
	if (len > TP_MAX_XPD_DATA) {
		return EMSGSIZE;
	}
	IFDEBUG(D_XPD)
		printf("tp_sendoob 2:");
D 11
		if(xdata)
E 11
I 11
		if (xdata)
E 11
			printf("xdata len 0x%x\n", len);
	ENDDEBUG

D 2
	/* stick an xpd mark in the normal data queue
	 * make sure we have enough mbufs before we stick anything into any queues
	 */
	MGET(xmark,M_WAIT, TPMT_XPD);
	if (xmark == MNULL) {
		return ENOBUFS;
	}
	xmark->m_len = 0;
	xmark->m_act = MNULL;
	
	{	/* stash the xpd sequence number in the mark */ 
		SeqNum *Xuna = mtod(xmark, SeqNum *);
		*Xuna = tpcb->tp_Xuna;
	}
E 2

	IFTRACE(D_XPD)
D 4
		tptraceTPCB(TPPTmisc, "XPD mark m_next ", xmark->m_next, 0, 0, 0);
E 4
I 4
		tptraceTPCB(TPPTmisc, "XPD mark m_next ", xdata->m_next, 0, 0, 0);
E 4
	ENDTRACE

D 2
	sbappendrecord(&so->so_snd, xmark); /* the mark */
E 2
	sbappendrecord(sb, xdata);	

	IFDEBUG(D_XPD)
		printf("tp_sendoob len 0x%x\n", len);
		dump_mbuf(so->so_snd.sb_mb, "XPD request Regular sndbuf:");
		dump_mbuf(tpcb->tp_Xsnd.sb_mb, "XPD request Xsndbuf:");
	ENDDEBUG
D 2
	u.u_r.r_val1  += len; 
E 2
	return DoEvent(T_XPD_req); 
D 4

E 4
}

/*
 * CALLED FROM:
 *  the socket routines
 * FUNCTION and ARGUMENTS:
 * 	Handles all "user requests" except the [gs]ockopts() requests.
 * 	The argument (req) is the request type (PRU*), 
 * 	(m) is an mbuf chain, generally used for send and
 * 	receive type requests only.
 * 	(nam) is used for addresses usually, in particular for the bind request.
 * 
D 4
 * 	The last argument (rights in most usrreq()s) has been stolen for 
 * 	returning flags values.  Since rights can't be passed around w/ tp,
 * 	this field is used only for RCVOOB user requests, and is assumed
 * 	to be either 0 (as soreceive() would have it) or a ptr to the int flags
 * 	(as recvv()'s version of soreceive() would have it
E 4
 */
/*ARGSUSED*/
ProtoHook
D 2
tp_usrreq(so, req, m, nam, rightsp, outflags)
E 2
I 2
D 8
tp_usrreq(so, req, m, nam, rightsp, controlp)
E 8
I 8
tp_usrreq(so, req, m, nam, controlp)
E 8
E 2
	struct socket *so;
	u_int req;
D 2
	struct mbuf *m, *nam, *rightsp /* not used */;
	int *outflags; 
E 2
I 2
D 8
	struct mbuf *m, *nam, *rightsp, *controlp;
E 8
I 8
	struct mbuf *m, *nam, *controlp;
E 8
E 2
{	
	register struct tp_pcb *tpcb =  sototpcb(so);
	int s = splnet();
	int error = 0;
I 2
	int flags, *outflags = &flags; 
E 2
	u_long eotsdu = 0;
	struct tp_event E;

	IFDEBUG(D_REQUEST)
		printf("usrreq(0x%x,%d,0x%x,0x%x,0x%x)\n",so,req,m,nam,outflags);
D 11
		if(so->so_error)
E 11
I 11
		if (so->so_error)
E 11
			printf("WARNING!!! so->so_error is 0x%x\n", so->so_error);
	ENDDEBUG
	IFTRACE(D_REQUEST)
		tptraceTPCB(TPPTusrreq, "req so m state [", req, so, m, 
			tpcb?tpcb->tp_state:0);
	ENDTRACE

	if ((u_int)tpcb == 0 && req != PRU_ATTACH) {
		IFTRACE(D_REQUEST)
			tptraceTPCB(TPPTusrreq, "req failed NO TPCB[", 0, 0, 0, 0);
		ENDTRACE
		splx(s);
		return ENOTCONN;
	}

D 2

	IFDEBUG(D_XPD)
		extern struct mbuf *mfree;
		struct mbuf *m = mfree, *n=MNULL;

		if ( (u_int) tpcb != 0 )  {
			n = tpcb->tp_Xrcv.sb_mb;
			if(n) while(m) {
				if(m == n) {
				printf("enter usrreq %d Xrcv sb_mb 0x%x is on freelist!\n",
					req, n);
				}
				m = m->m_next;
			}
		}
	ENDDEBUG

E 2
	switch (req) {

	case PRU_ATTACH:
		if (tpcb) {
			error = EISCONN;
D 20
			break;
		}
D 11
		if( error = tp_attach(so, so->so_proto->pr_domain->dom_family ) )
E 11
I 11
		if (error = tp_attach(so, so->so_proto->pr_domain->dom_family))
E 11
			break;
		tpcb = sototpcb(so);
E 20
I 20
		} else if ((error = tp_attach(so, (int)nam)) == 0)
			tpcb = sototpcb(so);
E 20
		break;

	case PRU_ABORT: 	/* called from close() */
		/* called for each incoming connect queued on the 
		 *	parent (accepting) socket 
		 */
D 11
		if( tpcb->tp_state == TP_OPEN ) {
E 11
I 11
D 20
		if (tpcb->tp_state == TP_OPEN) {
E 20
I 20
		if (tpcb->tp_state == TP_OPEN || tpcb->tp_state == TP_CONFIRMING) {
E 20
E 11
			E.ATTR(T_DISC_req).e_reason = E_TP_NO_SESSION;
			error = DoEvent(T_DISC_req); /* pretend it was a close() */
			break;
		} /* else DROP THROUGH */

	case PRU_DETACH: 	/* called from close() */
		/* called only after disconnect was called */
I 12
D 23
		if (tpcb->tp_state == TP_LISTENING) {
			register struct tp_pcb **tt;
			for (tt = &tp_listeners; *tt; tt = &((*tt)->tp_nextlisten))
				if (*tt == tpcb)
					break;
			if (*tt)
				*tt = tpcb->tp_nextlisten;
D 21
			else {
				for (tt = &tp_intercepts; *tt; tt = &((*tt)->tp_nextlisten))
					if (*tt == tpcb)
						break;
				if (*tt)
					*tt = tpcb->tp_nextlisten;
				else
					printf("tp_usrreq - detach: should panic\n");
			}
E 21
I 21
			else
				printf("tp_usrreq - detach: should panic\n");
E 21
		}
D 21
		if (tpcb->tp_next)
E 21
I 21
		if (tpcb->tp_next) {
E 21
			remque(tpcb);
I 21
			tpcb->tp_next = tpcb->tp_prev = 0;
		}
E 23
E 21
E 12
		error = DoEvent(T_DETACH);
I 2
		if (tpcb->tp_state == TP_CLOSED) {
I 23
			if (tpcb->tp_notdetached) {
				IFDEBUG(D_CONN)
					printf("PRU_DETACH: not detached\n");
				ENDDEBUG
				tp_detach(tpcb);
			}
E 23
			free((caddr_t)tpcb, M_PCB);
			tpcb = 0;
		}
E 2
		break;

	case PRU_SHUTDOWN:
		/* recv end may have been released; local credit might be zero  */
	case PRU_DISCONNECT:
		E.ATTR(T_DISC_req).e_reason = E_TP_NORMAL_DISC;
		error = DoEvent(T_DISC_req);
		break;

	case PRU_BIND:
D 11
		error =  (tpcb->tp_nlproto->nlp_pcbbind)( so->so_pcb, nam );
E 11
I 11
D 18
		error =  (tpcb->tp_nlproto->nlp_pcbbind)(so->so_pcb, nam);
E 18
I 18
D 19
		error =  (tpcb->tp_nlproto->nlp_pcbbind)(tpcb->tp_npcb, nam);
E 18
E 11
		if (error == 0) {
D 2
			tpcb->tp_lsuffixlen = sizeof(short); /* default */ 
			*(u_short *)(tpcb->tp_lsuffix) = (u_short) 
				(tpcb->tp_nlproto->nlp_getsufx)( so->so_pcb, TP_LOCAL );
E 2
I 2
D 18
			(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, &tpcb->tp_lsuffixlen,
E 18
I 18
			(tpcb->tp_nlproto->nlp_getsufx)(tpcb->tp_npcb, &tpcb->tp_lsuffixlen,
E 18
D 11
				tpcb->tp_lsuffix, TP_LOCAL );
E 11
I 11
				tpcb->tp_lsuffix, TP_LOCAL);
E 11
E 2
		}
E 19
I 19
		error =  tp_pcbbind(tpcb, nam);
E 19
		break;

	case PRU_LISTEN:
D 4
		if ( *SHORT_LSUFXP(tpcb) == (short)0 ) {
			/* note: this suffix is independent of the extended suffix */
E 4
I 4
D 11
		if( tpcb->tp_lsuffixlen ==  0) {
E 4
			if( error = (tpcb->tp_nlproto->nlp_pcbbind)(so->so_pcb, MNULL) )
E 11
I 11
D 19
		if (tpcb->tp_lsuffixlen == 0) {
D 18
			if (error = (tpcb->tp_nlproto->nlp_pcbbind)(so->so_pcb, MNULL))
E 18
I 18
			if (error = (tpcb->tp_nlproto->nlp_pcbbind)(tpcb->tp_npcb, MNULL))
E 18
E 11
				break;
D 4
		}
		if( tpcb->tp_lsuffixlen ==  0) {
E 4
D 2
			tpcb->tp_lsuffixlen = sizeof(short); /* default */ 
			*SHORT_LSUFXP(tpcb)  = (short) 
				(tpcb->tp_nlproto->nlp_getsufx)( so->so_pcb, TP_LOCAL );
E 2
I 2
D 18
			(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, &tpcb->tp_lsuffixlen,
E 18
I 18
			(tpcb->tp_nlproto->nlp_getsufx)(tpcb->tp_npcb, &tpcb->tp_lsuffixlen,
E 18
D 11
				tpcb->tp_lsuffix, TP_LOCAL );
E 11
I 11
				tpcb->tp_lsuffix, TP_LOCAL);
I 12
		}
		if (tpcb->tp_next == 0) {
			tpcb->tp_next = tpcb->tp_prev = tpcb;
E 19
I 19
		if (tpcb->tp_state != TP_CLOSED || tpcb->tp_lsuffixlen == 0 ||
				tpcb->tp_next == 0)
			error = EINVAL;
		else {
I 21
			register struct tp_pcb **tt;
E 21
			remque(tpcb);
E 19
D 21
			tpcb->tp_nextlisten = tp_listeners;
D 13
			tp_listeners = tpcb->tp_nextlisten;
E 13
I 13
D 19
			tp_listeners = tpcb;
E 19
I 19
			tpcb->tp_next = tpcb->tp_prev = tp_listeners = tpcb;
E 21
I 21
			tpcb->tp_next = tpcb->tp_prev = tpcb;
			for (tt = &tp_listeners; *tt; tt = &((*tt)->tp_nextlisten))
				if ((*tt)->tp_lsuffixlen)
					break;
			tpcb->tp_nextlisten = *tt;
			*tt = tpcb;
E 21
			error = DoEvent(T_LISTEN_req);
E 19
E 13
E 12
E 11
E 2
		}
D 19
		IFDEBUG(D_TPISO)
D 11
			if(tpcb->tp_state != TP_CLOSED)
E 11
I 11
			if (tpcb->tp_state != TP_CLOSED)
E 11
				printf("LISTEN ERROR: state 0x%x\n", tpcb->tp_state);
		ENDDEBUG
		error = DoEvent(T_LISTEN_req);
E 19
		break;

	case PRU_CONNECT2:
		error = EOPNOTSUPP; /* for unix domain sockets */
		break;

	case PRU_CONNECT:
		IFTRACE(D_CONN)
			tptraceTPCB(TPPTmisc, 
D 2
			"PRU_CONNECT: so *SHORT_LSUFXP(tpcb) 0x%x lsuflen 0x%x, class 0x%x",
E 2
I 2
			"PRU_CONNECT: so 0x%x *SHORT_LSUFXP(tpcb) 0x%x lsuflen 0x%x, class 0x%x",
E 2
			tpcb->tp_sock, *SHORT_LSUFXP(tpcb), tpcb->tp_lsuffixlen,
				tpcb->tp_class);
		ENDTRACE
		IFDEBUG(D_CONN)
			printf("PRU_CONNECT: so *SHORT_LSUFXP(tpcb) 0x%x lsuflen 0x%x, class 0x%x",
			tpcb->tp_sock, *SHORT_LSUFXP(tpcb), tpcb->tp_lsuffixlen,
				tpcb->tp_class);
		ENDDEBUG
D 4
		if (*SHORT_LSUFXP(tpcb) == (short)0) {
			/* no bind was done */
			/* note: this suffix is independent of the extended suffix */
E 4
I 4
D 11
		if( tpcb->tp_lsuffixlen ==  0) {
E 4
			if( error = (tpcb->tp_nlproto->nlp_pcbbind)(so->so_pcb, MNULL) ) {
E 11
I 11
		if (tpcb->tp_lsuffixlen == 0) {
D 18
			if (error = (tpcb->tp_nlproto->nlp_pcbbind)(so->so_pcb, MNULL)) {
E 18
I 18
D 20
			if (error = (tpcb->tp_nlproto->nlp_pcbbind)(tpcb->tp_npcb, MNULL)) {
E 20
I 20
			if (error = tp_pcbbind(tpcb, MNULL)) {
E 20
E 18
E 11
				IFDEBUG(D_CONN)
D 11
					printf("pcbbind returns error 0x%x\n", error );
E 11
I 11
					printf("pcbbind returns error 0x%x\n", error);
E 11
				ENDDEBUG
				break;
			}
D 4
		}
D 2
		if (tpcb->tp_lsuffixlen == 0) { 
			/* didn't set an extended suffix */
			tpcb->tp_lsuffixlen = sizeof(short);
			*SHORT_LSUFXP(tpcb) = (short)
					(tpcb->tp_nlproto->nlp_getsufx)( so->so_pcb, TP_LOCAL );
		} 
E 2
I 2
		if( tpcb->tp_lsuffixlen ==  0) {
E 4
D 18
			(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, &tpcb->tp_lsuffixlen,
E 18
I 18
D 20
			(tpcb->tp_nlproto->nlp_getsufx)(tpcb->tp_npcb, &tpcb->tp_lsuffixlen,
E 18
D 11
				tpcb->tp_lsuffix, TP_LOCAL );
E 11
I 11
				tpcb->tp_lsuffix, TP_LOCAL);
E 20
E 11
		}
E 2
D 20

E 20
		IFDEBUG(D_CONN)
			printf("isop 0x%x isop->isop_socket offset 12 :\n", tpcb->tp_npcb);
D 11
			dump_buf( tpcb->tp_npcb, 16);
E 11
I 11
			dump_buf(tpcb->tp_npcb, 16);
E 11
		ENDDEBUG
D 11
		if( error = tp_route_to( nam, tpcb, /* channel */0) )
E 11
I 11
		if (error = tp_route_to(nam, tpcb, /* channel */0))
E 11
			break;
		IFDEBUG(D_CONN)
			printf(
				"PRU_CONNECT after tpcb 0x%x so 0x%x npcb 0x%x flags 0x%x\n", 
				tpcb, so, tpcb->tp_npcb, tpcb->tp_flags);
			printf("isop 0x%x isop->isop_socket offset 12 :\n", tpcb->tp_npcb);
D 11
			dump_buf( tpcb->tp_npcb, 16);
E 11
I 11
			dump_buf(tpcb->tp_npcb, 16);
E 11
		ENDDEBUG
D 2
		if( tpcb->tp_fsuffixlen == 0 ) {
E 2
I 2
D 11
		if( tpcb->tp_fsuffixlen ==  0) {
E 11
I 11
		if (tpcb->tp_fsuffixlen ==  0) {
E 11
E 2
			/* didn't set peer extended suffix */
D 2
			tpcb->tp_fsuffixlen = sizeof(short);
			*SHORT_FSUFXP(tpcb) = (short)
					(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, TP_FOREIGN);
E 2
I 2
D 18
			(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, &tpcb->tp_fsuffixlen,
E 18
I 18
			(tpcb->tp_nlproto->nlp_getsufx)(tpcb->tp_npcb, &tpcb->tp_fsuffixlen,
E 18
D 11
				tpcb->tp_fsuffix, TP_FOREIGN );
E 11
I 11
				tpcb->tp_fsuffix, TP_FOREIGN);
E 11
E 2
		}
D 18
		(void) (tpcb->tp_nlproto->nlp_mtu)(so, so->so_pcb,
E 18
I 18
D 24
		(void) (tpcb->tp_nlproto->nlp_mtu)(so, tpcb->tp_npcb,
E 18
					&tpcb->tp_l_tpdusize, &tpcb->tp_tpdusize, 0);
E 24
D 11
		if( tpcb->tp_state == TP_CLOSED) {
E 11
I 11
		if (tpcb->tp_state == TP_CLOSED) {
E 11
			soisconnecting(so);  
			error = DoEvent(T_CONN_req);
		} else {
D 18
			(tpcb->tp_nlproto->nlp_pcbdisc)(so->so_pcb);
E 18
I 18
			(tpcb->tp_nlproto->nlp_pcbdisc)(tpcb->tp_npcb);
E 18
			error = EISCONN;
		}
		IFPERF(tpcb)
			u_int lsufx, fsufx;
D 5
			lsufx = *(u_int *)(tpcb->tp_lsuffix);
			fsufx = *(u_int *)(tpcb->tp_fsuffix);
E 5
I 5
			lsufx = *(u_short *)(tpcb->tp_lsuffix);
			fsufx = *(u_short *)(tpcb->tp_fsuffix);
E 5

D 11
			tpmeas( tpcb->tp_lref, 
				TPtime_open | (tpcb->tp_xtd_format <<4 ), 
E 11
I 11
			tpmeas(tpcb->tp_lref, 
				TPtime_open | (tpcb->tp_xtd_format << 4), 
E 11
				&time, lsufx, fsufx, tpcb->tp_fref);
		ENDPERF
		break;

	case PRU_ACCEPT: 
D 4
		/* all this garbage is to keep accept from returning
		 * before the 3-way handshake is done in class 4.
		 * it'll have to be modified for other classes 
		 */
E 4
I 4
D 18
		(tpcb->tp_nlproto->nlp_getnetaddr)(so->so_pcb, nam, TP_FOREIGN);
E 18
I 18
		(tpcb->tp_nlproto->nlp_getnetaddr)(tpcb->tp_npcb, nam, TP_FOREIGN);
E 18
E 4
		IFDEBUG(D_REQUEST)
D 4
			printf("PRU_ACCEPT so_error 0x%x\n", so->so_error);
E 4
I 4
			printf("ACCEPT PEERADDDR:");
			dump_buf(mtod(nam, char *), nam->m_len);
E 4
		ENDDEBUG
D 4
		so->so_error = 0;
		if ((so->so_state & SS_NBIO) && (so->so_state & SS_ISCONNECTED)== 0) {
			error = EWOULDBLOCK;
			break;
		}
		while ((so->so_state & SS_ISCONNECTED) == 0 && so->so_error == 0) {
			sleep((caddr_t)&so->so_timeo, PZERO+1);
		}
		if (so->so_error) {
			error = so->so_error;
		} else {
D 2
			struct sockaddr *sa = mtod(nam, struct sockaddr *);

			nam->m_len = sizeof (struct sockaddr);
			(tpcb->tp_nlproto->nlp_getnetaddr)(so->so_pcb, sa, TP_FOREIGN);

			switch(sa->sa_family = sototpcb(so)->tp_domain) {
			case AF_INET:
				satosin(sa)->sin_port =
					(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, TP_FOREIGN);
				break;
			case AF_ISO:
				satosiso(sa)->siso_tsuffix =
					(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, TP_FOREIGN);
				/* doesn't cover the case where the suffix is extended -
				 * grotesque - the user *has* to do the getsockopt */
				break;
			}
E 2
I 2
			(tpcb->tp_nlproto->nlp_getnetaddr)(so->so_pcb, nam, TP_FOREIGN);
E 2
			IFDEBUG(D_REQUEST)
				printf("ACCEPT PEERADDDR:");
D 2
				dump_buf(sa, sizeof(struct sockaddr));
E 2
I 2
				dump_buf(mtod(nam, char *), nam->m_len);
E 2
			ENDDEBUG
		}
E 4
		IFPERF(tpcb)
			u_int lsufx, fsufx;
D 5
			lsufx = *(u_int *)(tpcb->tp_lsuffix);
			fsufx = *(u_int *)(tpcb->tp_fsuffix);
E 5
I 5
			lsufx = *(u_short *)(tpcb->tp_lsuffix);
			fsufx = *(u_short *)(tpcb->tp_fsuffix);
E 5

D 11
			tpmeas( tpcb->tp_lref, TPtime_open, 
E 11
I 11
			tpmeas(tpcb->tp_lref, TPtime_open, 
E 11
				&time, lsufx, fsufx, tpcb->tp_fref);
		ENDPERF
		break;

	case PRU_RCVD:
I 4
		if (so->so_state & SS_ISCONFIRMING) {
			if (tpcb->tp_state == TP_CONFIRMING)
				error = tp_confirm(tpcb);
			break;
		}
E 4
		IFTRACE(D_DATA)
			tptraceTPCB(TPPTmisc,
			"RCVD BF: lcredit sent_lcdt cc hiwat \n",
				tpcb->tp_lcredit, tpcb->tp_sent_lcdt,
				so->so_rcv.sb_cc, so->so_rcv.sb_hiwat);
			LOCAL_CREDIT(tpcb);
			tptraceTPCB(TPPTmisc, 
				"PRU_RCVD AF sbspace lcredit hiwat cc",
				sbspace(&so->so_rcv), tpcb->tp_lcredit,
				so->so_rcv.sb_cc, so->so_rcv.sb_hiwat);
		ENDTRACE
D 2
		error = DoEvent(T_USR_rcvd); 
E 2
I 2
		IFDEBUG(D_REQUEST)
			printf("RCVD: cc %d space %d hiwat %d\n",
				so->so_rcv.sb_cc, sbspace(&so->so_rcv),
				so->so_rcv.sb_hiwat);
		ENDDEBUG
		if (((int)nam) & MSG_OOB)
			error = DoEvent(T_USR_Xrcvd); 
		else 
			error = DoEvent(T_USR_rcvd); 
E 2
		break;

	case PRU_RCVOOB:
		if ((so->so_state & SS_ISCONNECTED) == 0) {
			error = ENOTCONN;
			break;
		}
D 11
		if( ! tpcb->tp_xpd_service ) {
E 11
I 11
		if (! tpcb->tp_xpd_service) {
E 11
			error = EOPNOTSUPP;
			break;
		}
		/* kludge - nam is really flags here */
		error = tp_rcvoob(tpcb, so, m, outflags, (int)nam);
		break;

I 4
	case PRU_SEND:
E 4
	case PRU_SENDOOB:
D 2
		if ((so->so_state & SS_ISCONNECTED) == 0) {
			error = ENOTCONN;
E 2
I 2
D 9
		if (controlp && (error = tp_snd_control(controlp, so, &m)))
E 2
			break;
E 9
I 9
		if (controlp) {
			error = tp_snd_control(controlp, so, &m);
			controlp = NULL;
			if (error)
				break;
		}
E 9
I 4
D 15
		if (so->so_state & SS_ISCONFIRMING) {
			if (tpcb->tp_state == TP_CONFIRMING)
				error = tp_confirm(tpcb);
			if (m) {
				if (error == 0 && m->m_len != 0)
					error =  ENOTCONN;
				m_freem(m);
				m = 0;
			}
E 15
I 15
		if ((so->so_state & SS_ISCONFIRMING) &&
		    (tpcb->tp_state == TP_CONFIRMING) &&
		    (error = tp_confirm(tpcb)))
			    break;
		if (req == PRU_SENDOOB) {
			error = (tpcb->tp_xpd_service == 0) ?
						EOPNOTSUPP : tp_sendoob(tpcb, so, m, outflags);
E 15
			break;
		}
E 4
D 2
		}
E 2
I 2
		if (m == 0)
			break;
D 4
		if (so->so_state & SS_ISCONFIRMING)
			tp_confirm();
E 2
		if( ! tpcb->tp_xpd_service ) {
			error = EOPNOTSUPP;
E 4
I 4
D 15

		if (req == PRU_SENDOOB) {
			if (tpcb->tp_xpd_service == 0) {
				error = EOPNOTSUPP;
				break;
			}
			error = tp_sendoob(tpcb, so, m, outflags);
E 15
I 15
		if (m->m_flags & M_EOR) {
			eotsdu = 1;
			m->m_flags &= ~M_EOR;
		}
		if (eotsdu == 0 && m->m_pkthdr.len == 0)
E 15
E 4
			break;
I 15
		if (tpcb->tp_state != TP_AKWAIT && tpcb->tp_state != TP_OPEN) {
			error = ENOTCONN;
			break;
E 15
		}
D 4
		error = tp_sendoob(tpcb, so, m, outflags);
		break;

D 2
	case PRU_SENDEOT:
		eotsdu = 1;
		/* fall through */
E 2
	case PRU_SEND:
E 4
		/*
		 * The protocol machine copies mbuf chains,
		 * prepends headers, assigns seq numbers, and
		 * puts the packets on the device.
		 * When they are acked they are removed from the socket buf.
		 *
		 * sosend calls this up until sbspace goes negative.
		 * Sbspace may be made negative by appending this mbuf chain,
		 * possibly by a whole cluster.
		 */
D 2
		if ((so->so_state & SS_ISCONNECTED) == 0) {
			error = ENOTCONN;
E 2
I 2
D 4
		if (controlp && (error = tp_snd_control(controlp, so, &m)))
E 2
			break;
D 2
		}
E 2
I 2
		if (m == 0)
			break;
		if (so->so_state & SS_ISCONFIRMING)
			tp_confirm();
E 4
E 2
		{
D 2
			register struct mbuf *n;
E 2
I 2
D 22
			register struct mbuf *n = m;
E 2
D 7
			register int len=0;
E 7
			register struct sockbuf *sb = &so->so_snd;
I 2
			int	maxsize = tpcb->tp_l_tpdusize 
				    - tp_headersize(DT_TPDU_type, tpcb)
				    - (tpcb->tp_use_checksum?4:0) ;
			int totlen = n->m_pkthdr.len;
I 7
			int	mbufcnt = 0;
E 7
I 5
			struct mbuf *nn;
E 5
E 2

E 22
D 2
			n = m;
			while (n) { /* Could have eotsdu and no data.(presently MUST have
						 *	an mbuf though, even if its length == 0) 
						 */
				len += n->m_len;
				if( n->m_next == MNULL && eotsdu )  {
					CHANGE_MTYPE(n, TPMT_EOT);
				}
				n = n->m_next;
			}
E 2
I 2
			/*
			 * Could have eotsdu and no data.(presently MUST have
			 * an mbuf though, even if its length == 0) 
			 */
I 22
			int totlen = m->m_pkthdr.len;
			struct sockbuf *sb = &so->so_snd;
E 22
D 4
			if (n->m_flags & M_EOR)
E 4
I 4
D 15
			if (n->m_flags & M_EOR) {
E 4
				eotsdu = 1;
I 4
				n->m_flags &= ~M_EOR;
			}
E 15
E 4
E 2
			IFPERF(tpcb)
D 2
			   PStat(tpcb, Nb_from_sess) += len;
E 2
I 2
			   PStat(tpcb, Nb_from_sess) += totlen;
E 2
			   tpmeas(tpcb->tp_lref, TPtime_from_session, 0, 0, 
D 2
					PStat(tpcb, Nb_from_sess), len);
E 2
I 2
					PStat(tpcb, Nb_from_sess), totlen);
E 2
			ENDPERF
			IFDEBUG(D_SYSCALL)
				printf(
				"PRU_SEND: eot %d before sbappend 0x%x len 0x%x to sb @ 0x%x\n",
D 2
					eotsdu, m,len, &sb->sb_mb);
E 2
I 2
D 7
					eotsdu, m,len, sb);
E 7
I 7
					eotsdu, m, totlen, sb);
E 7
E 2
				dump_mbuf(sb->sb_mb, "so_snd.sb_mb");
				dump_mbuf(m, "m : to be added");
			ENDDEBUG
D 2
			/* The last mbuf has type TPMT_EOT so it will never be compressed
			 * with TPMT_DATA mbufs, but if this was an EOTSDU request w/o
			 * any data, the only way to keep this mbuf from being thrown
			 * away is to link it through the m_act field
			 * We are ASSUMING that if there are any data at all with this
			 * request, the last mbuf will be non-empty!!!
E 2
I 2
D 22
			/*
			 * Pre-packetize the data in the sockbuf
			 * according to negotiated mtu.  Do it here
			 * where we can safely wait for mbufs.
I 5
			 *
			 * This presumes knowledge of sockbuf conventions.
E 5
E 2
			 */
D 2
			if( m->m_type == TPMT_EOT ) /* first mbuf in chain is EOT? */
				sbappendrecord(sb, m);  /* to keep 2 TPMT_EOTs from being
												compressed */
			else
				sbappend(sb, m);
E 2
I 2
D 5
			while (n->m_pkthdr.len > maxsize) {
				struct mbuf *nn
					    = m_copym(n, 0, maxsize, M_WAIT);
E 5
I 5
D 7
			len = 0;
E 7
			if (n = sb->sb_mb)
				while (n->m_act)
					n = n->m_act;
D 6
			if (n && n->m_pkthdr.len < maxsize) {
E 6
I 6
			if ((nn = n) && n->m_pkthdr.len < maxsize) {
E 6
D 7
				int space = maxsize - n->m_pkthdr.len;
E 7
I 7
				u_int space = maxsize - n->m_pkthdr.len;
E 7
D 6
				int eorseen = 0;
				nn = n; 
				for (;; n = n->m_next) {
				 eorseen |= n->m_flags & M_EOR;
					if (n->m_next == 0)
						break;
				}  
				if (eorseen)
					goto on1;
E 6
I 6

				do {
					if (n->m_flags & M_EOR)
						goto on1;
				} while (n->m_next && (n = n->m_next));
D 7
				nn->m_pkthdr.len += space;
E 6
				if (m->m_pkthdr.len <= space) {
E 7
I 7
				if (totlen <= space) {
					TPNagle1++;
E 7
					n->m_next = m; 
I 6
D 7
					sballoc(sb, m);
E 7
I 7
					nn->m_pkthdr.len += totlen;
					while (n = n->m_next)
						sballoc(sb, n);
E 7
E 6
					if (eotsdu)
						nn->m_flags |= M_EOR; 
					goto on2; 
D 7
				} else {   
D 6
					nn->m_next = m_copym(n, 0, space, M_WAIT);
					m_adj(n, space);
E 6
I 6
					nn->m_next = m_copym(m, 0, space, M_WAIT);
					sballoc(sb, nn->m_next);
					m_adj(m, space);
E 7
I 7
				} else {
					/*
					 * Can't sleep here, because when you wake up
					 * packet you want to attach to may be gone!
					 */
					if (TNew && (n->m_next = m_copym(m, 0, space, M_NOWAIT))) {
						nn->m_pkthdr.len += space;
						TPNagle2++;
						while (n = n->m_next)
							sballoc(sb, n);
						m_adj(m, space);
					}
E 7
E 6
				}
			}	
D 7
	on1:	len++;
E 7
I 7
	on1:	mbufcnt++;
E 7
			for (n = m; n->m_pkthdr.len > maxsize;) {
D 7
				nn = m_copym(n, 0, len, M_WAIT);
E 7
I 7
				nn = m_copym(n, 0, maxsize, M_WAIT);
E 7
E 5
D 4
				if (eotsdu)
					n->m_flags &= ~M_EOR;
E 4
				sbappendrecord(sb, nn);
				m_adj(n, maxsize);
I 5
D 7
				len++;
E 7
I 7
				mbufcnt++;
E 7
E 5
			}
D 5
			sbappendrecord(sb, n);
I 4
			if (eotsdu)	/* This presumes knowledge of sbappendrecord() */
E 5
I 5
			if (eotsdu)
E 5
				n->m_flags |= M_EOR;
I 5
			sbappendrecord(sb, n);
	on2:	
			IFTRACE(D_DATA)
				tptraceTPCB(TPPTmisc,
D 7
				"SEND BF: maxsize totlen frags eotsdu",
					maxsize, totlen, len, eotsdu);
E 7
I 7
				"SEND BF: maxsize totlen mbufcnt eotsdu",
					maxsize, totlen, mbufcnt, eotsdu);
E 7
			ENDTRACE
E 22
I 22
			tp_packetize(tpcb, m, eotsdu);
E 22
E 5
E 4
E 2
			IFDEBUG(D_SYSCALL)
D 7
				printf("PRU_SEND: eot %d after sbappend 0x%x len 0x%x\n",
D 2
					eotsdu, m,len);
E 2
I 2
					eotsdu, n, len);
E 7
I 7
D 22
				printf("PRU_SEND: eot %d after sbappend 0x%x mbufcnt 0x%x\n",
					eotsdu, n, mbufcnt);
E 22
I 22
				printf("PRU_SEND: eot %d after sbappend 0x%x\n", eotsdu, m);
E 22
E 7
E 2
				dump_mbuf(sb->sb_mb, "so_snd.sb_mb");
			ENDDEBUG
D 2
			u.u_r.r_val1  += len; 
E 2
D 15
			error = DoEvent(T_DATA_req); 
E 15
I 15
			if (tpcb->tp_state == TP_OPEN)
				error = DoEvent(T_DATA_req); 
E 15
			IFDEBUG(D_SYSCALL)
				printf("PRU_SEND: after driver error 0x%x \n",error);
I 2
				printf("so_snd 0x%x cc 0t%d mbcnt 0t%d\n",
						sb, sb->sb_cc, sb->sb_mbcnt);
				dump_mbuf(sb->sb_mb, "so_snd.sb_mb after driver");
E 2
			ENDDEBUG
		}
		break;

D 2
	case PRU_SOCKADDR: {
			struct sockaddr *sa = mtod(nam, struct sockaddr *);

			nam->m_len = sizeof (struct sockaddr);
			(tpcb->tp_nlproto->nlp_getnetaddr)(so->so_pcb, sa, TP_LOCAL);
			switch ( sa->sa_family = sototpcb(so)->tp_domain ) {
			case AF_INET:
				satosin(sa)->sin_port =
					(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, TP_LOCAL);
				break;
			case AF_ISO:
				satosiso(sa)->siso_tsuffix =
					(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, TP_LOCAL);
				break;
			}
		}
E 2
I 2
	case PRU_SOCKADDR:
D 18
		(tpcb->tp_nlproto->nlp_getnetaddr)(so->so_pcb, nam, TP_LOCAL);
E 18
I 18
		(tpcb->tp_nlproto->nlp_getnetaddr)(tpcb->tp_npcb, nam, TP_LOCAL);
E 18
E 2
		break;

	case PRU_PEERADDR:
D 2
		if( (so->so_state & SS_ISCONNECTED) && 
			(so->so_state & SS_ISDISCONNECTING) == 0) {
				struct sockaddr *sa = mtod(nam, struct sockaddr *);

			nam->m_len = sizeof (struct sockaddr);

			(tpcb->tp_nlproto->nlp_getnetaddr)(so->so_pcb, sa, TP_FOREIGN);

			switch ( sa->sa_family = sototpcb(so)->tp_domain ) {
			case AF_INET:
				satosin(sa)->sin_port =
					(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, TP_FOREIGN);
				break;
			case AF_ISO:
				satosiso(sa)->siso_tsuffix =
					(tpcb->tp_nlproto->nlp_getsufx)(so->so_pcb, TP_FOREIGN);
				break;
			}
			IFDEBUG(D_REQUEST)
				printf("PEERADDDR:");
				dump_buf(sa, sizeof(struct sockaddr));
			ENDDEBUG
E 2
I 2
D 4
		if ((so->so_state & SS_ISCONNECTED) && 
		    (so->so_state & SS_ISDISCONNECTING) == 0) {
				(tpcb->tp_nlproto->nlp_getnetaddr)(so->so_pcb, nam, TP_FOREIGN);
				IFDEBUG(D_REQUEST)
					printf("PEERADDDR:");
					dump_buf(mtod(nam, char *), nam->m_len);
				ENDDEBUG
E 2
		} else 
			error = ENOTCONN;
E 4
I 4
D 18
		(tpcb->tp_nlproto->nlp_getnetaddr)(so->so_pcb, nam, TP_FOREIGN);
E 18
I 18
		(tpcb->tp_nlproto->nlp_getnetaddr)(tpcb->tp_npcb, nam, TP_FOREIGN);
E 18
E 4
		break;

	case PRU_CONTROL:
		error = EOPNOTSUPP;
		break;

	case PRU_PROTOSEND:
	case PRU_PROTORCV:
	case PRU_SENSE:
	case PRU_SLOWTIMO:
	case PRU_FASTTIMO:
		error = EOPNOTSUPP;
		break;

	default:
#ifdef ARGO_DEBUG
		printf("tp_usrreq UNKNOWN PRU %d\n", req);
D 28
#endif ARGO_DEBUG
E 28
I 28
#endif /* ARGO_DEBUG */
E 28
		error = EOPNOTSUPP;
	}

	IFDEBUG(D_REQUEST)
D 4
		printf("returning from tp_usrreq(so 0x%x) error 0x%x\n", so, error);
E 4
I 4
		printf("%s, so 0x%x, tpcb 0x%x, error %d, state %d\n",
			"returning from tp_usrreq", so, tpcb, error,
D 26
			tpcb ? 0 : tpcb->tp_state);
E 26
I 26
			tpcb ? tpcb->tp_state : 0);
E 26
E 4
	ENDDEBUG
	IFTRACE(D_REQUEST)
		tptraceTPCB(TPPTusrreq, "END req so m state [", req, so, m, 
D 26
			tpcb?0:tpcb->tp_state);
E 26
I 26
			tpcb ? tpcb->tp_state : 0);
E 26
	ENDTRACE
I 9
	if (controlp) {
		m_freem(controlp);
		printf("control data unexpectedly retained in tp_usrreq()");
	}
E 9
	splx(s);
I 2
	return error;
I 5
}
tp_ltrace(so, uio)
struct socket *so;
struct uio *uio;
{
	IFTRACE(D_DATA)
		register struct tp_pcb *tpcb =  sototpcb(so);
		if (tpcb) {
			tptraceTPCB(TPPTmisc, "sosend so resid iovcnt", so,
				uio->uio_resid, uio->uio_iovcnt, 0);
		}
	ENDTRACE
E 5
}

D 4
/*
 * Stub for future negotiated confirmation of connections.
 */
tp_confirm()
E 4
I 4
tp_confirm(tpcb)
register struct tp_pcb *tpcb;
E 4
{
I 4
	struct tp_event E;
	if (tpcb->tp_state == TP_CONFIRMING)
	    return DoEvent(T_ACPT_req);
	printf("Tp confirm called when not confirming; tpcb 0x%x, state 0x%x\n",
		tpcb, tpcb->tp_state);
	return 0;
E 4
}

/*
 * Process control data sent with sendmsg()
 */
D 9
tp_snd_control(m0, so, data)
	register struct mbuf *m0;
E 9
I 9
tp_snd_control(m, so, data)
	struct mbuf *m;
E 9
	struct socket *so;
	register struct mbuf **data;
{
D 10
	register struct tp_control_hdr *ch;
E 10
I 10
	register struct cmsghdr *ch;
E 10
D 9
	struct mbuf *m;
E 9
	int error = 0;

D 9
	if (m0 && m0->m_len) {
		ch = mtod(m0, struct tp_control_hdr *);
		m0->m_len -= sizeof (*ch);
		m0->m_data += sizeof (*ch);
		m = m_copym(m0, 0, M_COPYALL, M_WAIT);
E 9
I 9
	if (m && m->m_len) {
D 10
		ch = mtod(m, struct tp_control_hdr *);
E 10
I 10
		ch = mtod(m, struct cmsghdr *);
E 10
		m->m_len -= sizeof (*ch);
		m->m_data += sizeof (*ch);
E 9
		error = tp_ctloutput(PRCO_SETOPT,
							 so, ch->cmsg_level, ch->cmsg_type, &m);
D 9
		if (m)
			m_freem(m);
E 9
		if (ch->cmsg_type == TPOPT_DISC_DATA) {
			if (data && *data) {
				m_freem(*data);
				*data = 0;
			}
D 9
			m0 = 0;
D 8
			error = tp_usrreq(so, PRU_DISCONNECT, m0, (caddr_t)0, m0, m0);
E 8
I 8
			error = tp_usrreq(so, PRU_DISCONNECT, m0, (caddr_t)0, m0);
E 9
I 9
			error = tp_usrreq(so, PRU_DISCONNECT, (struct mbuf *)0,
								(caddr_t)0, (struct mbuf *)0);
E 9
E 8
		}
	}
I 9
	if (m)
		m_freem(m);
E 9
E 2
	return error;
}
E 1
