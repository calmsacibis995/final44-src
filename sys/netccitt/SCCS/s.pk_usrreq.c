h05004
s 00001/00001/00577
d D 8.2 95/01/09 17:52:28 cgd 22 21
c pk_control takes a u_long command (64-bit changes
e
s 00002/00002/00576
d D 8.1 93/06/10 22:54:09 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00577
d D 7.19 92/12/08 18:10:48 sklower 20 19
c didn't get includes right
e
s 00020/00012/00557
d D 7.18 92/12/08 17:11:15 sklower 19 18
c changes to run over both LLC and HDLC, and also use explicit shifts
c instead of bitfields.
e
s 00014/00014/00555
d D 7.17 92/10/11 11:49:49 bostic 18 17
c make kernel includes standard
e
s 00005/00004/00564
d D 7.16 91/06/27 23:32:45 sklower 17 15
c this version should work under both new and old vm systems
e
s 00004/00002/00566
d R 7.16 91/06/26 17:06:32 sklower 16 15
c play catchup with newvm changes
e
s 00001/00001/00567
d D 7.15 91/06/26 15:43:56 sklower 15 14
c setsockopt(pk_ctloutput) always returned an error, even when it won.
e
s 00046/00047/00522
d D 7.14 91/05/29 19:31:17 sklower 14 13
c add two new sockopts (add vc to route, turn on/off kernel dg listen)
c Allow for dynamic creation of pkcb's again (for LLC2 operation),
c minor change to the way packet accounting & flow control is done
e
s 00011/00008/00558
d D 7.13 91/05/03 18:40:29 sklower 13 12
c note that pk_output does not return a value (for pk_start & iso operations;
c redo convention about lcd_send (called from pk_send, so that smart boards
e
s 00011/00007/00555
d D 7.12 91/04/26 15:32:12 sklower 12 11
c changes in dealing with old style sockaddrs for null PIDs
c for new CONS operation with ISODE.
e
s 00025/00024/00537
d D 7.11 91/03/12 15:03:59 sklower 11 10
c reformat to UBC conventions (space before parameter lists)
c this version works with ISODE 6.7m.
e
s 00141/00078/00420
d D 7.10 91/01/09 15:40:24 sklower 10 9
c checkpoint -- this version compiles and represents most of 
c the changes to have ISO CONS be a kernel client of X.25; not tested!!!!
e
s 00002/00003/00496
d D 7.9 90/11/13 17:39:02 sklower 9 8
c mark working version before changing OOB, facilities
e
s 00021/00040/00478
d D 7.8 90/10/04 19:50:13 sklower 8 7
c capture current work; fix minor bugs concerning packet lengths &
c conventions; add routine to fragment datagrams into complete sequences.
e
s 00040/00016/00478
d D 7.7 90/08/30 18:48:41 sklower 7 6
c this version compiles; completely untested
e
s 00002/00002/00492
d D 7.6 90/06/21 12:29:11 sklower 6 5
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00040/00014/00454
d D 7.5 90/05/22 15:46:24 sklower 5 4
c checkpoint before changing pq structure to be a sockbuf for downq 
c and only retaining up method
e
s 00028/00025/00440
d D 7.4 90/05/16 15:46:04 sklower 4 3
c periodic checkpoint against catastrophic loss
e
s 00050/00044/00415
d D 7.3 90/05/15 11:28:15 sklower 3 2
c checkpoint before trying including old pkcb in ifaddr.
e
s 00013/00001/00446
d D 7.2 90/05/11 15:22:21 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00447/00000/00000
d D 7.1 90/05/11 11:19:43 sklower 1 0
c date and time created 90/05/11 11:19:43 by sklower
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
D 19
 * Copyright (c) 1990 The Regents of the University of California.
E 19
I 19
 * Copyright (C) Computer Science Department IV, 
 * 		 University of Erlangen-Nuremberg, Germany, 1992
D 21
 * Copyright (c) 1991, 1992  The Regents of the University of California.
E 19
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 19
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
E 19
I 19
 * This code is derived from software contributed to Berkeley by the
 * Laboratory for Computation Vision and the Computer Science Department
 * of the the University of British Columbia and the Computer Science
 * Department (IV) of the University of Erlangen-Nuremberg, Germany.
E 19
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 4
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
#ifdef BSD4_3
#include "../net/if.h"
E 4
I 4
D 18
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
D 14
#include "protosw.h"
E 14
#include "socketvar.h"
I 14
#include "protosw.h"
E 14
#include "errno.h"
E 4
#include "ioctl.h"
D 4
#include "dir.h"
E 4
D 17
#include "user.h"
E 17
#include "stat.h"
E 18
I 18
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
E 18
D 4
#endif
E 4

D 4
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 4
I 4
D 18
#include "../net/if.h"
I 14
#include "../net/route.h"
E 18
I 18
#include <net/if.h>
I 20
#include <net/if_types.h>
E 20
#include <net/route.h>
E 18
E 14
E 4

I 4
D 18
#include "x25.h"
#include "pk.h"
#include "pk_var.h"
E 18
I 18
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 18

I 19
static old_to_new();
static new_to_old();
E 19
E 4
D 10
struct	x25_packet *pk_template ();

E 10
/*
 * 
 *  X.25 Packet level protocol interface to socket abstraction.
 *
 *  Process an X.25 user request on a logical channel.  If this is a send
 *  request then m is the mbuf chain of the send data. If this is a timer
 *  expiration (called from the software clock routine) them timertype is
 *  the particular timer.
 *
 */

D 3
pk_usrreq (so, req, m, nam, rights)
E 3
I 3
pk_usrreq (so, req, m, nam, control)
E 3
struct socket *so;
int req;
register struct mbuf *m, *nam;
D 3
struct mbuf *rights;
E 3
I 3
struct mbuf *control;
E 3
{
	register struct pklcd *lcp = (struct pklcd *) so -> so_pcb;
D 10
	register struct x25_packet *xp;
E 10
D 3
	register int s = splnet (), error = 0;
E 3
I 3
	register int error = 0;
E 3

D 3
#ifdef BSD4_3
	if (req == PRU_CONTROL) {
		error = pk_control(so, (int)m, (caddr_t)nam,
			(struct ifnet *)rights);
		splx (s);
		return (error);
E 3
I 3
	if (req == PRU_CONTROL)
D 11
		return (pk_control(so, (int)m, (caddr_t)nam,
E 11
I 11
		return (pk_control (so, (int)m, (caddr_t)nam,
E 11
			(struct ifnet *)control));
D 10
	if (control && control->m_len) {
E 10
I 10
	if (control && control -> m_len) {
E 10
		error = EINVAL;
		goto release;
E 3
	}
D 3
#endif
	if (rights && rights -> m_len) {
		splx (s);
		return (EINVAL);
E 3
I 3
	if (lcp == NULL && req != PRU_ATTACH) {
		error = EINVAL;
		goto release;
E 3
	}

/*
	pk_trace (pkcbhead, TR_USER, (struct pklcd *)0,
		req, (struct x25_packet *)0);
*/

D 3
	if (lcp == NULL && req != PRU_ATTACH) {
		splx (s);
E 3
D 7
		return (EINVAL);
D 3
	}
E 3

E 7
	switch (req) {
	/* 
	 *  X.25 attaches to socket via PRU_ATTACH and allocates a logical
	 *  channel descriptor.  If the socket is to  receive connections,
	 *  then the LISTEN state is entered.
	 */
	case PRU_ATTACH: 
		if (lcp) {
			error = EISCONN;
			/* Socket already connected. */
			break;
		}
D 7
		error = pk_attach (so);
E 7
I 7
		lcp = pk_attach (so);
		if (lcp == 0)
			error = ENOBUFS;
E 7
		break;

	/* 
	 *  Detach a logical channel from the socket. If the state of the
	 *  channel is embryonic, simply discard it. Otherwise we have to 
	 *  initiate a PRU_DISCONNECT which will finish later.
	 */
	case PRU_DETACH: 
		pk_disconnect (lcp);
		break;

	/* 
	 *  Give the socket an address.
	 */
	case PRU_BIND: 
		if (nam -> m_len == sizeof (struct x25_sockaddr))
			old_to_new (nam);
		error = pk_bind (lcp, nam);
		break;

	/* 
	 *  Prepare to accept connections.
	 */
	case PRU_LISTEN: 
D 10
		if (lcp -> lcd_ceaddr == 0) {
			error = EDESTADDRREQ;
			break;
		}
		lcp -> lcd_state = LISTEN;
		lcp -> lcd_listen = pk_listenhead;
		pk_listenhead = lcp;
E 10
I 10
		error = pk_listen (lcp);
E 10
		break;

	/* 
	 *  Initiate a CALL REQUEST to peer entity. Enter state SENT_CALL
	 *  and mark the socket as connecting. Set timer waiting for 
	 *  CALL ACCEPT or CLEAR.
	 */
	case PRU_CONNECT: 
		if (nam -> m_len == sizeof (struct x25_sockaddr))
			old_to_new (nam);
D 5
		error = pk_connect (lcp, nam);
E 5
I 5
D 10
		error = pk_connect (lcp, nam, (struct sockaddr_25 *)0);
E 10
I 10
		if (pk_checksockaddr (nam))
			return (EINVAL);
		error = pk_connect (lcp, mtod (nam, struct sockaddr_x25 *));
E 10
E 5
		break;

	/* 
	 *  Initiate a disconnect to peer entity via a CLEAR REQUEST packet.
	 *  The socket will be disconnected when we receive a confirmation
	 *  or a clear collision.
	 */
	case PRU_DISCONNECT: 
		pk_disconnect (lcp);
		break;

	/* 
	 *  Accept an INCOMING CALL. Most of the work has already been done
	 *  by pk_input. Just return the callers address to the user.
	 */
	case PRU_ACCEPT: 
		if (lcp -> lcd_craddr == NULL)
			break;
		bcopy ((caddr_t)lcp -> lcd_craddr, mtod (nam, caddr_t),
			sizeof (struct sockaddr_x25));
		nam -> m_len = sizeof (struct sockaddr_x25);
		if (lcp -> lcd_flags & X25_OLDSOCKADDR)
			new_to_old (nam);
		break;

	/* 
	 *  After a receive, we should send a RR.
	 */
	case PRU_RCVD: 
D 14
		lcp -> lcd_rxcnt++;
		lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_RR);
		pk_output (lcp);
I 11
		/*pk_flowcontrol (lcp, sbspace (&so -> so_rcv) <= 0, 1);*/
E 14
I 14
		pk_flowcontrol (lcp, /*sbspace (&so -> so_rcv) <= */ 0, 1);
E 14
E 11
		break;

	/* 
I 10
	 *  Send INTERRUPT packet.
	 */
	case PRU_SENDOOB: 
		if (m == 0) {
			MGETHDR(m, M_WAITOK, MT_OOBDATA);
			m -> m_pkthdr.len = m -> m_len = 1;
D 11
			*mtod(m, octet *) = 0;
E 11
I 11
			*mtod (m, octet *) = 0;
E 11
		}
		if (m -> m_pkthdr.len > 32) {
D 11
			m_freem(m);
E 11
I 11
			m_freem (m);
E 11
			error = EMSGSIZE;
			break;
		}
		MCHTYPE(m, MT_OOBDATA);
		/* FALLTHROUGH */

	/* 
E 10
	 *  Do send by placing data on the socket output queue.
D 10
	 *  SHOULD WE USE m_cat HERE.
E 10
	 */
	case PRU_SEND: 
D 10
		error = pk_send (lcp, m);
E 10
I 10
		if (control) {
D 11
			register struct cmsghdr *ch = mtod(m, struct cmsghdr *);
E 11
I 11
			register struct cmsghdr *ch = mtod (m, struct cmsghdr *);
E 11
			control -> m_len -= sizeof (*ch);
			control -> m_data += sizeof (*ch);
D 11
			pk_ctloutput(PRCO_SETOPT, so, ch -> cmsg_level,
E 11
I 11
D 14
			pk_ctloutput (PRCO_SETOPT, so, ch -> cmsg_level,
E 14
I 14
			error = pk_ctloutput (PRCO_SETOPT, so, ch -> cmsg_level,
E 14
E 11
					ch -> cmsg_type, &control);
		}
D 14
		if (m)
E 14
I 14
		if (error == 0 && m)
E 14
			error = pk_send (lcp, m);
E 10
		break;

	/* 
	 *  Abort a virtual circuit. For example all completed calls
	 *  waiting acceptance.
	 */
	case PRU_ABORT: 
		pk_disconnect (lcp);
		break;

	/* Begin unimplemented hooks. */

	case PRU_SHUTDOWN: 
		error = EOPNOTSUPP;
		break;

	case PRU_CONTROL: 
		error = EOPNOTSUPP;
		break;

	case PRU_SENSE: 
#ifdef BSD4_3
		((struct stat *)m) -> st_blksize = so -> so_snd.sb_hiwat;
#else
		error = EOPNOTSUPP;
#endif
		break;

	/* End unimplemented hooks. */

	case PRU_SOCKADDR: 
		if (lcp -> lcd_ceaddr == 0)
			return (EADDRNOTAVAIL);
		nam -> m_len = sizeof (struct sockaddr_x25);
		bcopy ((caddr_t)lcp -> lcd_ceaddr, mtod (nam, caddr_t),
			sizeof (struct sockaddr_x25));
		if (lcp -> lcd_flags & X25_OLDSOCKADDR)
			new_to_old (nam);
		break;

	case PRU_PEERADDR:
		if (lcp -> lcd_state != DATA_TRANSFER)
			return (ENOTCONN);
		nam -> m_len = sizeof (struct sockaddr_x25);
		bcopy (lcp -> lcd_craddr ? (caddr_t)lcp -> lcd_craddr :
			(caddr_t)lcp -> lcd_ceaddr,
			mtod (nam, caddr_t), sizeof (struct sockaddr_x25));
		if (lcp -> lcd_flags & X25_OLDSOCKADDR)
			new_to_old (nam);
		break;

	/* 
	 *  Receive INTERRUPT packet.
	 */
	case PRU_RCVOOB: 
I 10
		if (so -> so_options & SO_OOBINLINE) {
			register struct mbuf *n  = so -> so_rcv.sb_mb;
			if (n && n -> m_type == MT_OOBDATA) {
				unsigned len =  n -> m_pkthdr.len;
				so -> so_rcv.sb_mb = n -> m_nextpkt;
				if (len !=  n -> m_len &&
D 11
				    (n = m_pullup(n, len)) == 0)
E 11
I 11
				    (n = m_pullup (n, len)) == 0)
E 11
					break;
				m -> m_len = len;
D 11
				bcopy(mtod(m, caddr_t), mtod(n, caddr_t), len);
				m_freem(n);
E 11
I 11
				bcopy (mtod (m, caddr_t), mtod (n, caddr_t), len);
				m_freem (n);
E 11
			}
			break;
		}
E 10
		m -> m_len = 1;
		*mtod (m, char *) = lcp -> lcd_intrdata;
		break;

D 10
	/* 
	 *  Send INTERRUPT packet.
	 */
	case PRU_SENDOOB: 
D 9
		m_freem (m);
E 9
		if (lcp -> lcd_intrconf_pending) {
			error = ETOOMANYREFS;
			break;
		}
		lcp -> lcd_intrcnt++;
		xp = lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_INTERRUPT);
		xp -> packet_data = 0;
		(dtom (xp)) -> m_len++;
		pk_output (lcp);
I 9
		m_freem (m);
E 9
		break;

E 10
	default: 
		panic ("pk_usrreq");
	}
D 3

	splx (s);
E 3
I 3
release:
	if (control != NULL)
D 11
		m_freem(control);
E 11
I 11
		m_freem (control);
E 11
D 9
	if (m != NULL)
		m_freem(m);
E 9
E 3
	return (error);
}

I 5
/* 
 * If you want to use UBC X.25 level 3 in conjunction with some
D 10
 * other X.25 level 2 driver, have the ifp->if_ioctl routine
E 10
I 10
 * other X.25 level 2 driver, have the ifp -> if_ioctl routine
E 10
D 14
 * assign pk_start to pkp -> pk_start when called with SIOCSIFCONF_X25.
E 14
I 14
 * assign pk_start to ia -> ia_start when called with SIOCSIFCONF_X25.
E 14
 */
/* ARGSUSED */
pk_start (lcp)
register struct pklcd *lcp;
{
D 11
	extern int pk_send();
E 11
I 11
D 13
	extern int pk_send ();
E 11

D 6
	lcp -> lcp_downq.pq_put = pk_send;
E 6
I 6
D 7
	lcp -> lcp_send = pk_send;
E 7
I 7
	lcp -> lcd_send = pk_send;
E 7
E 6
D 11
	return (pk_output(lcp));
E 11
I 11
	return (pk_output (lcp));
E 13
I 13
	pk_output (lcp);
	return (0); /* XXX pk_output should return a value */
E 13
E 11
}

I 14
#ifndef _offsetof
#define _offsetof(t, m) ((int)((caddr_t)&((t *)0)->m))
#endif
struct sockaddr_x25 pk_sockmask = {
D 19
_offsetof(struct sockaddr_x25, x25_addr[0]),
0, -1};
E 19
I 19
	_offsetof(struct sockaddr_x25, x25_addr[0]),      /* x25_len */
	0,                                                /* x25_family */
	-1,                                               /* x25_net id */
};
E 19

E 14
E 5
D 3
#ifdef BSD4_3
E 3
/*ARGSUSED*/
pk_control (so, cmd, data, ifp)
struct socket *so;
D 22
int cmd;
E 22
I 22
u_long cmd;
E 22
caddr_t data;
register struct ifnet *ifp;
{
D 4
	register struct ifreq *ifr = (struct ifreq *)data;
E 4
I 4
	register struct ifreq_x25 *ifr = (struct ifreq_x25 *)data;
E 4
	register struct ifaddr *ifa = 0;
D 3
	register int error, s;
	struct sockaddr oldaddr;
E 3
I 3
	register struct x25_ifaddr *ia = 0;
I 5
	struct pklcd *dev_lcp = 0;
E 5
D 8
	int error, s;
E 8
I 8
	int error, s, old_maxlcn;
E 8
	unsigned n;
E 3

	/*
	 * Find address for this interface, if it exists.
	 */
	if (ifp)
D 10
		for (ifa = ifp->if_addrlist; ifa; ifa = ifa->ifa_next)
D 4
			if (ifa->ifa_addr.sa_family == AF_CCITT)
E 4
I 4
			if (ifa->ifa_addr->sa_family == AF_CCITT)
E 10
I 10
		for (ifa = ifp -> if_addrlist; ifa; ifa = ifa -> ifa_next)
			if (ifa -> ifa_addr -> sa_family == AF_CCITT)
E 10
E 4
				break;

I 3
	ia = (struct x25_ifaddr *)ifa;
E 3
	switch (cmd) {
D 4
	case SIOCGIFADDR:
E 4
I 4
	case SIOCGIFCONF_X25:
E 4
		if (ifa == 0)
			return (EADDRNOTAVAIL);
D 3
		ifr -> ifr_addr = ifa->ifa_addr;
E 3
I 3
D 4
		ifr->ifr_addr = *(struct sockaddr *)ia->ia_xc;
E 4
I 4
D 7
		ifr->ifr_xc = *(struct sockaddr *)ia->ia_xc;
E 7
I 7
D 10
		ifr->ifr_xc = ia->ia_xc;
E 10
I 10
		ifr -> ifr_xc = ia -> ia_xc;
E 10
E 7
E 4
E 3
		return (0);

D 4
	case SIOCSIFADDR:
E 4
I 4
	case SIOCSIFCONF_X25:
E 4
D 7
		if (!suser())
			return (u.u_error);

E 7
I 7
D 11
		if (error = suser(u.u_cred, &u.u_acflag))
E 11
I 11
D 17
		if (error = suser (u.u_cred, &u.u_acflag))
E 11
			return (error);
E 17
I 17
		if ((so->so_state & SS_PRIV) == 0)
			return (EPERM);
E 17
E 7
		if (ifp == 0)
D 11
			panic("pk_control");
E 11
I 11
			panic ("pk_control");
E 11
		if (ifa == (struct ifaddr *)0) {
D 3
			register struct ifaddr *ia;
E 3
			register struct mbuf *m;

D 5
			m = m_getclr(M_WAIT, MT_IFADDR);
			if (m == (struct mbuf *)NULL)
E 5
I 5
			MALLOC(ia, struct x25_ifaddr *, sizeof (*ia),
				M_IFADDR, M_WAITOK);
			if (ia == 0)
E 5
				return (ENOBUFS);
I 8
D 11
			bzero((caddr_t)ia, sizeof (*ia));
E 11
I 11
			bzero ((caddr_t)ia, sizeof (*ia));
E 11
E 8
D 3
			ia = mtod(m, struct ifaddr *);
E 3
I 3
D 5
			ia = mtod(m, struct x25_ifaddr *);
E 5
E 3
D 10
			if (ifa = ifp->if_addrlist) {
				for ( ; ifa->ifa_next; ifa = ifa->ifa_next)
E 10
I 10
			if (ifa = ifp -> if_addrlist) {
				for ( ; ifa -> ifa_next; ifa = ifa -> ifa_next)
E 10
					;
D 3
				ifa->ifa_next = ia;
E 3
I 3
D 10
				ifa->ifa_next = &ia->ia_ifa;
E 10
I 10
				ifa -> ifa_next = &ia -> ia_ifa;
E 10
E 3
			} else
D 3
				ifp->if_addrlist = ia;
			ifa = ia;
E 3
I 3
D 10
				ifp->if_addrlist = &ia->ia_ifa;
			ifa = &ia->ia_ifa;
E 3
D 4
			ifa->ifa_ifp = ifp;
I 3
			ifa->ifa_addr = (struct sockaddr *)&ia->ia_addr;
E 4
			ifa->ifa_netmask = (struct sockaddr *)&ia->ia_sockmask;
I 4
D 7
			ifa->ifa_addr = (struct sockaddr *)&ia->ia_addr;
E 7
I 7
			ifa->ifa_addr = (struct sockaddr *)&ia->ia_xc.xc_addr;
I 8
			ia->ia_xcp = &ia->ia_xc;
E 8
E 7
			ia->ia_ifp = ifp;
			ia->ia_pkcb.pk_ia = ia;
			ia->ia_pkcb.pk_next = pkcbhead;
I 8
			ia->ia_pkcb.pk_state = DTE_WAITING;
I 9
			ia->ia_pkcb.pk_start = pk_start;
E 9
E 8
			pkcbhead = &ia->ia_pkcb;
E 10
I 10
				ifp -> if_addrlist = &ia -> ia_ifa;
			ifa = &ia -> ia_ifa;
D 14
			ifa -> ifa_netmask = (struct sockaddr *)&ia -> ia_sockmask;
E 14
I 14
			ifa -> ifa_netmask = (struct sockaddr *)&pk_sockmask;
E 14
			ifa -> ifa_addr = (struct sockaddr *)&ia -> ia_xc.xc_addr;
D 14
			ia -> ia_xcp = &ia -> ia_xc;
E 14
I 14
			ifa -> ifa_dstaddr = (struct sockaddr *)&ia -> ia_dstaddr; /* XXX */
E 14
			ia -> ia_ifp = ifp;
D 14
			ia -> ia_pkcb.pk_ia = ia;
			ia -> ia_pkcb.pk_next = pkcbhead;
			ia -> ia_pkcb.pk_state = DTE_WAITING;
			ia -> ia_pkcb.pk_start = pk_start;
			pkcbhead = &ia -> ia_pkcb;
E 14
I 14
			ia -> ia_dstaddr.x25_family = AF_CCITT;
			ia -> ia_dstaddr.x25_len = pk_sockmask.x25_len;
D 19
		} else {
E 19
I 19
		} else if (ISISO8802(ifp) == 0) {
E 19
			rtinit (ifa, (int)RTM_DELETE, 0);
E 14
E 10
E 4
E 3
		}
D 3
		oldaddr = ifa->ifa_addr;
		s = splimp();
		ifa->ifa_addr = ifr->ifr_addr;
E 3
I 3
D 4
		ia->ia_xcp = (struct x25config *) &(ifr->ifr_addr);
E 4
I 4
D 8
		ia->ia_xcp = &(ifr->ifr_xc);
E 4
D 7
		if (ia->ia_chan && (ia->ia_maxlcn != ia->xcp->xc_maxlcn)) {
I 5
			pk_restart(&ia->ia_pkp, X25_RESTART_NETWORK_CONGESTION);
E 7
I 7
		if (ia->ia_chan && (ia->ia_maxlcn != ia->ia_xcp->xc_maxlcn)) {
E 8
I 8
D 10
		old_maxlcn = ia->ia_maxlcn;
		ia->ia_xc = ifr->ifr_xc;
		if (ia->ia_chan && (ia->ia_maxlcn != old_maxlcn)) {
E 8
			pk_restart(&ia->ia_pkcb, X25_RESTART_NETWORK_CONGESTION);
E 7
			dev_lcp = ia->ia_chan[0];
E 5
			free((caddr_t)ia->ia_chan, M_IFADDR);
D 5
			ia->ia_ia_chan = 0;
E 5
I 5
			ia->ia_chan = 0;
E 10
I 10
		old_maxlcn = ia -> ia_maxlcn;
		ia -> ia_xc = ifr -> ifr_xc;
D 14
		if (ia -> ia_chan && (ia -> ia_maxlcn != old_maxlcn)) {
D 11
			pk_restart(&ia -> ia_pkcb, X25_RESTART_NETWORK_CONGESTION);
E 11
I 11
			pk_restart (&ia -> ia_pkcb, X25_RESTART_NETWORK_CONGESTION);
E 11
			dev_lcp = ia -> ia_chan[0];
D 11
			free((caddr_t)ia -> ia_chan, M_IFADDR);
E 11
I 11
			free ((caddr_t)ia -> ia_chan, M_IFADDR);
E 11
			ia -> ia_chan = 0;
E 14
I 14
		ia -> ia_dstaddr.x25_net = ia -> ia_xc.xc_addr.x25_net;
		if (ia -> ia_maxlcn != old_maxlcn && old_maxlcn != 0) {
			/* VERY messy XXX */
			register struct pkcb *pkp;
D 19
			for (pkp = pkcbhead; pkp; pkp = pkp -> pk_next)
E 19
I 19
			FOR_ALL_PKCBS(pkp)
E 19
				if (pkp -> pk_ia == ia)
					pk_resize (pkp);
E 14
E 10
E 5
		}
D 5
		n = ia->ia_maxlcn * sizeof(struct pklcd *);
		if (ia->ia_chan == 0)
E 5
I 5
D 10
		if (ia->ia_chan == 0) {
D 8
			n = ia->ia_maxlcn * sizeof(struct pklcd *);
E 5
D 4
		    ia->ia_chan = (struct pklcd **) malloc(n, M_IFADDR);
E 4
I 4
			ia->ia_chan = (struct pklcd **) malloc(n, M_IFADDR);
E 8
I 8
			n = (ia->ia_maxlcn + 1) * sizeof(struct pklcd *);
			ia->ia_chan = (struct pklcd **) malloc(n, M_IFADDR, M_WAITOK);
E 8
E 4
D 5
		if (ia->ia_chan)
			bzero((caddr_t)ia->ia_chan, n);
D 4
		else
E 4
I 4
		else {
			ia->ia_xcp = &ia->ia_xc;
E 4
			return (ENOBUFS);
E 5
I 5
			if (ia->ia_chan) {
				bzero((caddr_t)ia->ia_chan, n);
E 10
I 10
D 14
		if (ia -> ia_chan == 0) {
D 11
			n = (ia -> ia_maxlcn + 1) * sizeof(struct pklcd *);
			ia -> ia_chan = (struct pklcd **) malloc(n, M_IFADDR, M_WAITOK);
E 11
I 11
			n = (ia -> ia_maxlcn + 1) * sizeof (struct pklcd *);
			ia -> ia_chan = (struct pklcd **) malloc (n, M_IFADDR, M_WAITOK);
E 11
			if (ia -> ia_chan) {
D 11
				bzero((caddr_t)ia -> ia_chan, n);
E 11
I 11
				bzero ((caddr_t)ia -> ia_chan, n);
E 11
E 10
				if (dev_lcp == 0)
D 11
					dev_lcp = pk_attach((struct socket *)0);
E 11
I 11
					dev_lcp = pk_attach ((struct socket *)0);
E 11
D 7
				ia->ia_chan = dev_lcp;
E 7
I 7
D 10
				ia->ia_chan[0] = dev_lcp;
I 8
				dev_lcp->lcd_state = READY;
				dev_lcp->lcd_pkp = &ia->ia_pkcb;
E 10
I 10
				ia -> ia_chan[0] = dev_lcp;
				dev_lcp -> lcd_state = READY;
				dev_lcp -> lcd_pkp = &ia -> ia_pkcb;
E 10
E 8
E 7
			} else {
				if (dev_lcp)
D 11
					pk_close(dev_lcp);
E 11
I 11
					pk_close (dev_lcp);
E 11
D 8
				ia->ia_xcp = &ia->ia_xc;
E 8
				return (ENOBUFS);
			}
E 5
I 4
		}
E 14
E 4
E 3
		/*
		 * Give the interface a chance to initialize if this
D 19
		 * is its first address, and to validate the address.
E 19
I 19
p		 * is its first address, and to validate the address.
E 19
		 */
I 14
		ia -> ia_start = pk_start;
E 14
D 3
		if (ifp->if_ioctl && (error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ifa))) {
			splx(s);
			ifa->ifa_addr = oldaddr;
			return (error);
		}
E 3
I 3
		s = splimp();
D 10
		if (ifp->if_ioctl)
D 4
			error = (*ifp->if_ioctl)(ifp, SIOCSIFADDR, ifa)));
E 4
I 4
D 7
			error = (*ifp->if_ioctl)(ifp, SIOCSIFCONF_X25, ifa)));
E 7
I 7
			error = (*ifp->if_ioctl)(ifp, SIOCSIFCONF_X25, ifa);
E 10
I 10
		if (ifp -> if_ioctl)
D 19
			error = (*ifp -> if_ioctl)(ifp, SIOCSIFCONF_X25, ifa);
E 19
I 19
			error = (*ifp -> if_ioctl)(ifp, SIOCSIFCONF_X25, 
						   (caddr_t) ifa);
E 19
E 10
I 8
		if (error)
D 10
			ifp->if_flags &= ~IFF_UP;
E 8
E 7
E 4
E 3
		splx(s);
E 10
I 10
			ifp -> if_flags &= ~IFF_UP;
I 14
D 19
		else
E 19
I 19
		else if (ISISO8802(ifp) == 0)
E 19
			error = rtinit (ifa, (int)RTM_ADD, RTF_UP);
E 14
		splx (s);
E 10
I 3
D 8
		if (error == 0) {
			ia->ia_xc = *ia->ia_xcp;
E 3
D 7
#ifndef WATERLOO
D 3
		(void) pk_accton ();
E 3
I 3
			(void) pk_accton ();
E 3
#endif
E 7
D 3
		return (0);
E 3
I 3
		}
		ia->ia_xcp = &ia->ia_xc;
E 8
		return (error);
E 3

	default:
D 10
		if (ifp == 0 || ifp->if_ioctl == 0)
E 10
I 10
		if (ifp == 0 || ifp -> if_ioctl == 0)
E 10
			return (EOPNOTSUPP);
D 10
		return ((*ifp->if_ioctl)(ifp, cmd, data));
E 10
I 10
		return ((*ifp -> if_ioctl)(ifp, cmd, data));
E 10
	}
I 7
}

D 11
pk_ctloutput(cmd, so, level, optname, mp)
E 11
I 11
pk_ctloutput (cmd, so, level, optname, mp)
E 11
struct socket *so;
struct mbuf **mp;
int cmd, level, optname;
{
	register struct mbuf *m = *mp;
I 10
	register struct pklcd *lcp = (struct pklcd *) so -> so_pcb;
E 10
D 14
	int error;
E 14
I 14
	int error = EOPNOTSUPP;
E 14

I 14
	if (m == 0)
		return (EINVAL);
E 14
	if (cmd == PRCO_SETOPT) switch (optname) {
D 14
	case PK_ACCTFILE:
E 14
I 14
	case PK_FACILITIES:
E 14
		if (m == 0)
			return (EINVAL);
I 14
		lcp -> lcd_facilities = m;
		*mp = 0;
		return (0);

	case PK_ACCTFILE:
E 14
D 10
		if (m->m_len)
			error = pk_accton(mtod(m, char *));
E 10
I 10
D 17
		if (m -> m_len)
E 17
I 17
		if ((so->so_state & SS_PRIV) == 0)
			error = EPERM;
		else if (m -> m_len)
E 17
D 11
			error = pk_accton (mtod(m, char *));
E 11
I 11
			error = pk_accton (mtod (m, char *));
E 11
E 10
		else
D 10
			error = pk_accton((char *)0);
		(void) m_freem(m);
E 10
I 10
			error = pk_accton ((char *)0);
D 14
		(void) m_freem (m);
E 10
		*mp = 0;
		return (error);
E 14
I 14
		break;
E 14
I 10

D 14
	case PK_FACILITIES:
		if (m == 0)
			return (EINVAL);
		lcp -> lcd_facilities = m;
		*mp = 0;
		return (0);
E 14
I 14
	case PK_RTATTACH:
		error = pk_rtattach (so, m);
		break;
	    
	case PK_PRLISTEN:
		error = pk_user_protolisten (mtod (m, u_char *));
E 14
E 10
	}
	if (*mp) {
D 10
		(void) m_freem(*mp);
E 10
I 10
		(void) m_freem (*mp);
E 10
		*mp = 0;
	}
D 15
	return (EOPNOTSUPP);
E 15
I 15
	return (error);
E 15

E 7
}
I 14

E 14
D 3
#endif
E 3

/*
 * Do an in-place conversion of an "old style"
 * socket address to the new style
 */

static
old_to_new (m)
register struct mbuf *m;
{
	register struct x25_sockaddr *oldp;
	register struct sockaddr_x25 *newp;
	register char *ocp, *ncp;
	struct sockaddr_x25 new;

	oldp = mtod (m, struct x25_sockaddr *);
	newp = &new;
	bzero ((caddr_t)newp, sizeof (*newp));

	newp -> x25_family = AF_CCITT;
I 12
	newp -> x25_len = sizeof(*newp);
E 12
D 10
	newp->x25_opts.op_flags = (oldp->xaddr_facilities & X25_REVERSE_CHARGE)
E 10
I 10
	newp -> x25_opts.op_flags = (oldp -> xaddr_facilities & X25_REVERSE_CHARGE)
E 10
		| X25_MQBIT | X25_OLDSOCKADDR;
	if (oldp -> xaddr_facilities & XS_HIPRIO)	/* Datapac specific */
		newp -> x25_opts.op_psize = X25_PS128;
	bcopy ((caddr_t)oldp -> xaddr_addr, newp -> x25_addr,
D 12
		(unsigned)min (oldp -> xaddr_len, sizeof (newp -> x25_addr) - 1));
	bcopy ((caddr_t)oldp -> xaddr_proto, newp -> x25_udata, 4);
	newp -> x25_udlen = 4;

E 12
I 12
	       (unsigned)min (oldp -> xaddr_len, sizeof (newp -> x25_addr) - 1));
	if (bcmp ((caddr_t)oldp -> xaddr_proto, newp -> x25_udata, 4) != 0) {
		bcopy ((caddr_t)oldp -> xaddr_proto, newp -> x25_udata, 4);
		newp -> x25_udlen = 4;
	}
E 12
	ocp = (caddr_t)oldp -> xaddr_userdata;
	ncp = newp -> x25_udata + 4;
	while (*ocp && ocp < (caddr_t)oldp -> xaddr_userdata + 12) {
I 12
		if (newp -> x25_udlen == 0)
			newp -> x25_udlen = 4;
E 12
		*ncp++ = *ocp++;
		newp -> x25_udlen++;
	}
D 12

E 12
	bcopy ((caddr_t)newp, mtod (m, char *), sizeof (*newp));
D 10
	m->m_len = sizeof (*newp);
E 10
I 10
	m -> m_len = sizeof (*newp);
E 10
}

/*
 * Do an in-place conversion of a new style
 * socket address to the old style
 */

static
new_to_old (m)
register struct mbuf *m;
{
	register struct x25_sockaddr *oldp;
	register struct sockaddr_x25 *newp;
	register char *ocp, *ncp;
	struct x25_sockaddr old;

	oldp = &old;
	newp = mtod (m, struct sockaddr_x25 *);
	bzero ((caddr_t)oldp, sizeof (*oldp));

	oldp -> xaddr_facilities = newp -> x25_opts.op_flags & X25_REVERSE_CHARGE;
	if (newp -> x25_opts.op_psize == X25_PS128)
		oldp -> xaddr_facilities |= XS_HIPRIO;	/* Datapac specific */
	ocp = (char *)oldp -> xaddr_addr;
	ncp = newp -> x25_addr;
	while (*ncp) {
		*ocp++ = *ncp++;
		oldp -> xaddr_len++;
	}

	bcopy (newp -> x25_udata, (caddr_t)oldp -> xaddr_proto, 4);
D 12
	bcopy (newp -> x25_udata + 4, (caddr_t)oldp -> xaddr_userdata,
		(unsigned)(newp -> x25_udlen - 4));
E 12
I 12
	if (newp -> x25_udlen > 4)
		bcopy (newp -> x25_udata + 4, (caddr_t)oldp -> xaddr_userdata,
			(unsigned)(newp -> x25_udlen - 4));
E 12

	bcopy ((caddr_t)oldp, mtod (m, char *), sizeof (*oldp));
	m -> m_len = sizeof (*oldp);
}

I 10

pk_checksockaddr (m)
struct mbuf *m;
{
	register struct sockaddr_x25 *sa = mtod (m, struct sockaddr_x25 *);
	register char *cp;

	if (m -> m_len != sizeof (struct sockaddr_x25))
		return (1);
	if (sa -> x25_family != AF_CCITT ||
		sa -> x25_udlen > sizeof (sa -> x25_udata))
		return (1);
	for (cp = sa -> x25_addr; *cp; cp++) {
		if (*cp < '0' || *cp > '9' ||
			cp >= &sa -> x25_addr[sizeof (sa -> x25_addr) - 1])
			return (1);
	}
	return (0);
}
I 13

E 13
E 10
pk_send (lcp, m)
D 8
register struct pklcd *lcp;
E 8
I 8
struct pklcd *lcp;
E 8
register struct mbuf *m;
{
D 8
	register struct x25_packet *xp;
	register struct mbuf *m0;
	register int len;
E 8
I 8
D 10
	int mqbit = 0, error;
E 10
I 10
	int mqbit = 0, error = 0;
	register struct x25_packet *xp;
I 13
	register struct socket *so;
E 13
E 10
E 8

I 10
	if (m -> m_type == MT_OOBDATA) {
		if (lcp -> lcd_intrconf_pending)
			error = ETOOMANYREFS;
		if (m -> m_pkthdr.len > 32)
			error = EMSGSIZE;
		M_PREPEND(m, PKHEADERLN, M_WAITOK);
		if (m == 0 || error)
			goto bad;
D 13
		lcp -> lcd_template = m;
E 13
		*(mtod (m, octet *)) = 0;
		xp = mtod (m, struct x25_packet *);
D 19
		xp -> fmt_identifier = 1;
E 19
I 19
		X25SBITS(xp -> bits, fmt_identifier, 1);
E 19
		xp -> packet_type = X25_INTERRUPT;
		SET_LCN(xp, lcp -> lcd_lcn);
D 13
		return (pk_output (lcp));
E 13
I 13
		sbinsertoob ( (so = lcp -> lcd_so) ?
			&so -> so_snd : &lcp -> lcd_sb, m);
		goto send;
E 13
	}
E 10
D 8
	m0 = dtom ((xp = pk_template (lcp -> lcd_lcn, X25_DATA)));
	m0 -> m_next = m;
E 8
	/*
	 * Application has elected (at call setup time) to prepend
	 * a control byte to each packet written indicating m-bit
	 * and q-bit status.  Examine and then discard this byte.
	 */
	if (lcp -> lcd_flags & X25_MQBIT) {
D 8
		register octet *cp;

E 8
		if (m -> m_len < 1) {
D 8
			m_freem (m0);
E 8
I 8
			m_freem (m);
E 8
			return (EMSGSIZE);
		}
D 8
		cp = mtod (m, octet *);
		if (*cp & 0x80)					/* XXX */
			xp -> q_bit = 1;
		xp -> packet_type |= (*cp & 0x40) >> 2;		/* XXX */
E 8
I 8
D 10
		mqbit = *(mtod(m, u_char *));
E 10
I 10
		mqbit = *(mtod (m, u_char *));
E 10
E 8
		m -> m_len--;
D 3
		m -> m_off++;
E 3
I 3
		m -> m_data++;
I 8
		m -> m_pkthdr.len--;
E 8
E 3
	}
D 8
	len = m -> m_len;
	while (m -> m_next) {
		m = m -> m_next;
		len += m -> m_len;
	}
	if (len > (1 << lcp -> lcd_packetsize)) {
		m_freem (m0);
		return (EMSGSIZE);
	}
D 5

D 3
#ifdef BSD4_3
E 3
 	sbappendrecord (&lcp -> lcd_so -> so_snd, m0);
E 5
I 5
	if (lcp -> lcd_so)
		sbappendrecord (&lcp -> lcd_so -> so_snd, m0);
	else
D 6
		pq_appendrecord (&lcp -> lcd_downq, m0);
E 6
I 6
		sbappendrecord (&lcp -> lcd_sb, m0);
E 6
E 5
D 3
#else
	m -> m_act = (struct mbuf *) 1;
	sbappend (&lcp -> lcd_so -> so_snd, m0);
#endif
E 3
	lcp -> lcd_template = 0;
	lcp -> lcd_txcnt++;
	pk_output (lcp);
	return (0);
E 8
I 8
D 11
	if ((error = pk_fragment(lcp, m, mqbit & 0x80, mqbit &0x40, 1)) == 0)
E 11
I 11
D 13
	if ((error = pk_fragment (lcp, m, mqbit & 0x80, mqbit & 0x40, 1)) == 0)
E 11
		error = pk_output (lcp);
E 13
I 13
	error = pk_fragment (lcp, m, mqbit & 0x80, mqbit & 0x40, 1);
send:
	if (error == 0 && lcp -> lcd_state == DATA_TRANSFER)
		lcp -> lcd_send (lcp); /* XXXXXXXXX fix pk_output!!! */
E 13
I 10
	return (error);
bad:
	if (m)
		m_freem (m);
E 10
	return (error);
E 8
}
E 1
