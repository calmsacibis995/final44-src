h00075
s 00002/00002/01164
d D 8.1 93/06/10 22:54:03 bostic 28 27
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/01165
d D 7.26 93/06/05 15:57:03 sklower 27 26
c various lintish things come to light by protoypes.
e
s 00049/00026/01117
d D 7.25 93/02/23 17:25:15 sklower 26 25
c added pk_ifwithaddr(), reformated according to UBC conventions
e
s 00001/00000/01142
d D 7.24 92/12/08 18:10:44 sklower 25 24
c didn't get includes right
e
s 00217/00062/00925
d D 7.23 92/12/08 17:11:09 sklower 24 23
c changes to run over both LLC and HDLC, and also use explicit shifts
c instead of bitfields.
e
s 00014/00014/00973
d D 7.22 92/10/11 11:49:37 bostic 23 22
c make kernel includes standard
e
s 00001/00001/00986
d D 7.21 92/05/29 16:02:28 sklower 22 21
c make compile under new and old systems /* hope this is right */
e
s 00001/00001/00986
d D 7.20 92/02/06 16:32:33 sklower 21 20
c comparison wrongly takes precedence over bitwise-and
e
s 00000/00001/00987
d D 7.19 91/12/17 16:31:15 sklower 20 18
c another fix from Dirk Husemann
e
s 00000/00000/00988
d R 7.19 91/12/17 16:30:24 sklower 19 18
c another fix from dkhusema
e
s 00001/00000/00987
d D 7.18 91/11/18 16:24:41 sklower 18 17
c bug fix from dkhusema@uni-erlangen.de - pkthdr.len not increment in pk_clear
e
s 00000/00059/00987
d D 7.17 91/11/18 16:21:54 sklower 17 16
c m_split moved into common code.
e
s 00015/00016/01031
d D 7.16 91/06/06 19:39:37 sklower 16 15
c this version now supports IP over X.25; changes include setting 
c the X25_MBS_HOLD  flag and preserving flags through incoming call cloning and aassociation
e
s 00011/00015/01036
d D 7.15 91/05/29 19:25:19 sklower 15 14
c fix outright bug for reporting errors when no socket;
c pk_flowcontrol called pk_template with the wrong values; a || b generates only 1 or 0;
c move start routine to x25_ifaddr, since there may be many pkp's with a given ifa
e
s 00048/00029/01003
d D 7.14 91/05/16 14:04:52 sklower 14 13
c make build_facilities known so that OSI can use it.
e
s 00009/00011/01023
d D 7.13 91/05/09 21:23:08 sklower 13 12
c in clearcause; check that socket is there before setting error ;
c set lengths in various pkthdrs; get rid of call to lcd_upper meaning flow on;
c fix some return values for pk_fragment.
e
s 00002/00000/01032
d D 7.12 91/05/03 18:35:52 sklower 12 11
c set default lower level output routine when creating an x25 control block.
e
s 00001/00001/01031
d D 7.11 91/04/30 16:34:17 sklower 11 10
c DIAGNOSTIC is already defined for general error catching
e
s 00082/00046/00950
d D 7.10 91/03/12 15:17:42 sklower 10 9
c reformat according to UBC conventions (space before parameters);
c doubly link all pklcd's for debugging; allow for two new packet types --
c (Reject and Diagnostic) in decode; uniformize generation of RR's and RNR's
e
s 00168/00098/00828
d D 7.9 91/01/09 15:40:21 sklower 9 8
c checkpoint -- this version compiles and represents most of 
c the changes to have ISO CONS be a kernel client of X.25; not tested!!!!
e
s 00085/00012/00841
d D 7.8 90/11/13 17:20:58 sklower 8 7
c working version fixing bugs in pk_fragment;
c also allow 12 bits of lcn; this version includes but does not reference
c a new mbuf utility m_split, which will be put in uipc_mbuf.c eventually.
e
s 00087/00021/00766
d D 7.7 90/10/04 19:50:10 sklower 7 6
c capture current work; fix minor bugs concerning packet lengths &
c conventions; add routine to fragment datagrams into complete sequences.
e
s 00008/00024/00779
d D 7.6 90/08/30 18:48:36 sklower 6 5
c this version compiles; completely untested
e
s 00004/00005/00799
d D 7.5 90/06/21 12:29:01 sklower 5 4
c assign SCCS numbers for ``June'' beta tape; not yet tested.
e
s 00042/00046/00762
d D 7.4 90/05/22 15:46:20 sklower 4 3
c checkpoint before changing pq structure to be a sockbuf for downq 
c and only retaining up method
e
s 00032/00024/00776
d D 7.3 90/05/16 15:45:59 sklower 3 2
c periodic checkpoint against catastrophic loss
e
s 00013/00001/00787
d D 7.2 90/05/11 15:22:18 sklower 2 1
c install combined copyright headers using sccs include for terms
e
s 00788/00000/00000
d D 7.1 90/05/11 11:19:41 sklower 1 0
c date and time created 90/05/11 11:19:41 by sklower
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
D 24
 * Copyright (c) 1990 The Regents of the University of California.
E 24
I 24
 * Copyright (C) Computer Science Department IV, 
 * 		 University of Erlangen-Nuremberg, Germany, 1992
D 28
 * Copyright (c) 1991, 1992  The Regents of the University of California.
E 24
 * All rights reserved.
E 28
I 28
 * Copyright (c) 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 28
 *
D 24
 * This code is derived from software contributed to Berkeley by
 * the Laboratory for Computation Vision and the Computer Science Department
 * of the University of British Columbia.
E 24
I 24
 * This code is derived from software contributed to Berkeley by the
 * Laboratory for Computation Vision and the Computer Science Department
 * of the the University of British Columbia and the Computer Science
 * Department (IV) of the University of Erlangen-Nuremberg, Germany.
E 24
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 3
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/protosw.h"
#include "../h/socketvar.h"
#include "../h/errno.h"
#include "../h/time.h"
#include "../h/kernel.h"
E 3
I 3
D 23
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
#include "protosw.h"
#include "socketvar.h"
#include "errno.h"
#include "time.h"
#include "kernel.h"
E 23
I 23
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
E 23
E 3

I 4
D 23
#include "../net/if.h"
E 23
I 23
#include <net/if.h>
I 25
#include <net/route.h>
E 25
E 23

I 24
#include <netccitt/dll.h>
E 24
E 4
D 3
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
#include "../netccitt/x25err.h"
E 3
I 3
D 23
#include "x25.h"
#include "pk.h"
#include "pk_var.h"
#include "x25err.h"
E 23
I 23
#include <netccitt/x25.h>
I 24
#include <netccitt/x25err.h>
E 24
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
D 24
#include <netccitt/x25err.h>
E 24
E 23
E 3

int     pk_sendspace = 1024 * 2 + 8;
int     pk_recvspace = 1024 * 2 + 8;

I 10
struct pklcd_q pklcd_q = {&pklcd_q, &pklcd_q};

I 24
struct x25bitslice x25_bitslice[] = {
/*	  mask, shift value */
	{ 0xf0, 0x4 },
	{ 0xf,  0x0 },
	{ 0x80, 0x7 },
	{ 0x40, 0x6 },
	{ 0x30, 0x4 },
	{ 0xe0, 0x5 },
	{ 0x10, 0x4 },
	{ 0xe,  0x1 },
	{ 0x1,  0x0 }
};


E 24
E 10
D 9
struct	x25_packet *pk_template ();

E 9
/* 
 *  Attach X.25 protocol to socket, allocate logical channel descripter
 *  and buffer space, and enter LISTEN state if we are to accept
 *  IN-COMMING CALL packets.  
 *
 */

I 4
struct pklcd *
E 4
pk_attach (so)
struct socket *so;
{
	register struct pklcd *lcp;
D 4
	register struct mbuf *m;
	register int error;
E 4
I 4
	register int error = ENOBUFS;
I 12
D 26
	int pk_output();
E 26
I 26
	int pk_output ();
E 26
E 12
E 4

D 4
	if (error = soreserve (so, pk_sendspace, pk_recvspace))
		return (error);
E 4
I 4
D 10
	MALLOC(lcp, struct pklcd *, sizeof(*lcp), M_PCB, M_NOWAIT);
E 10
I 10
	MALLOC(lcp, struct pklcd *, sizeof (*lcp), M_PCB, M_NOWAIT);
E 10
	if (lcp) {
D 10
		bzero((caddr_t)lcp, sizeof(*lcp));
E 10
I 10
		bzero ((caddr_t)lcp, sizeof (*lcp));
		insque (&lcp -> lcd_q, &pklcd_q);
I 13
		lcp -> lcd_state = READY;
		lcp -> lcd_send = pk_output;
E 13
E 10
		if (so) {
			error = soreserve (so, pk_sendspace, pk_recvspace);
D 5
			so -> so_snd.sb_mbmax = pk_sendspace;
E 5
			lcp -> lcd_so = so;
			if (so -> so_options & SO_ACCEPTCONN)
				lcp -> lcd_state = LISTEN;
D 13
			else
				lcp -> lcd_state = READY;
E 13
D 5
		}
E 4

E 5
I 5
		} else
D 6
			sbreserve (&lcp -> lcd_sb, pk_sendpace);
E 6
I 6
			sbreserve (&lcp -> lcd_sb, pk_sendspace);
E 6
E 5
D 4
	/* Hopefully we can remove this when SEQ_PKT is available (4.3?) */
	so -> so_snd.sb_mbmax = pk_sendspace;

	if ((m = m_getclr (M_DONTWAIT, MT_PCB)) == 0)
		return (ENOBUFS);
	lcp = mtod (m, struct pklcd *);
	so -> so_pcb = (caddr_t) lcp;
	lcp -> lcd_so = so;

	if (so -> so_options & SO_ACCEPTCONN)
		lcp -> lcd_state = LISTEN;
	else
		lcp -> lcd_state = READY;

	return (0);
E 4
I 4
	}
	if (so) {
		so -> so_pcb = (caddr_t) lcp;
		so -> so_error = error;
	}
I 12
D 13
	lcp -> lcd_send = pk_output;
E 13
E 12
	return (lcp);
E 4
}

/* 
 *  Disconnect X.25 protocol from socket.
 */

pk_disconnect (lcp)
register struct pklcd *lcp;
{
	register struct socket *so = lcp -> lcd_so;
	register struct pklcd *l, *p;

	switch (lcp -> lcd_state) {
	case LISTEN: 
		for (p = 0, l = pk_listenhead; l && l != lcp; p = l, l = l -> lcd_listen);
		if (p == 0) {
			if (l != 0)
				pk_listenhead = l -> lcd_listen;
		}
		else
		if (l != 0)
			p -> lcd_listen = l -> lcd_listen;
		pk_close (lcp);
		break;

	case READY: 
		pk_acct (lcp);
		pk_close (lcp);
		break;

	case SENT_CLEAR: 
	case RECEIVED_CLEAR: 
		break;

	default: 
		pk_acct (lcp);
D 3
		soisdisconnecting (so);
		sbflush (&so -> so_rcv);
E 3
I 3
		if (so) {
			soisdisconnecting (so);
			sbflush (&so -> so_rcv);
		}
E 3
D 9
		pk_clear (lcp);
E 9
I 9
		pk_clear (lcp, 241, 0); /* Normal Disconnect */
E 9

	}
}

/* 
 *  Close an X.25 Logical Channel. Discard all space held by the
 *  connection and internal descriptors. Wake up any sleepers.
 */

pk_close (lcp)
struct pklcd *lcp;
{
	register struct socket *so = lcp -> lcd_so;

D 24
	pk_freelcd (lcp);
E 24
I 24
	/*
	 * If the X.25 connection is torn down due to link
	 * level failure (e.g. LLC2 FRMR) and at the same the user
	 * level is still filling up the socket send buffer that
D 26
	 * send buffer is locked. An attempt to sbflush() that send
E 26
I 26
	 * send buffer is locked. An attempt to sbflush () that send
E 26
	 * buffer will lead us into - no, not temptation but - panic!
	 * So - we'll just check wether the send buffer is locked
	 * and if that's the case we'll mark the lcp as zombie and 
D 26
	 * have the pk_timer() do the cleaning ...
E 26
I 26
	 * have the pk_timer () do the cleaning ...
E 26
	 */
	
	if (so && so -> so_snd.sb_flags & SB_LOCK)
		lcp -> lcd_state = LCN_ZOMBIE;
	else
		pk_freelcd (lcp);
E 24

	if (so == NULL)
		return;

	so -> so_pcb = 0;
D 9
	sbflush (&so -> so_snd);
	sbflush (&so -> so_rcv);
E 9
	soisdisconnected (so);
D 9
	sofree (so);	/* gak!!! you can't do that here */
E 9
I 9
	/* sofree (so);	/* gak!!! you can't do that here */
E 9
}

/* 
 *  Create a template to be used to send X.25 packets on a logical
 *  channel. It allocates an mbuf and fills in a skeletal packet
 *  depending on its type. This packet is passed to pk_output where
 *  the remainer of the packet is filled in.
*/

D 9
struct x25_packet *
E 9
I 9
struct mbuf *
E 9
pk_template (lcn, type)
int lcn, type;
{
	register struct mbuf *m;
	register struct x25_packet *xp;

D 7
	MGET (m, M_DONTWAIT, MT_HEADER);
E 7
I 7
	MGETHDR (m, M_DONTWAIT, MT_HEADER);
E 7
	if (m == 0)
		panic ("pk_template");
	m -> m_act = 0;

	/*
	 * Efficiency hack: leave a four byte gap at the beginning
	 * of the packet level header with the hope that this will
	 * be enough room for the link level to insert its header.
	 */
D 3
/* XXX does the above still apply? */
	m -> m_off = MMINOFF + 4;
E 3
I 3
D 7
	m -> m_data += 4;
E 7
I 7
	m -> m_data += max_linkhdr;
E 7
E 3
D 13
	m -> m_len = PKHEADERLN;
E 13
I 13
	m -> m_pkthdr.len = m -> m_len = PKHEADERLN;
E 13

	xp = mtod (m, struct x25_packet *);
	*(long *)xp = 0;		/* ugly, but fast */
/*	xp -> q_bit = 0;*/
D 24
	xp -> fmt_identifier = 1;
E 24
I 24
	X25SBITS(xp -> bits, fmt_identifier, 1);
E 24
/*	xp -> lc_group_number = 0;*/

D 8
	xp -> logical_channel_number = lcn;
E 8
I 8
	SET_LCN(xp, lcn);
E 8
	xp -> packet_type = type;

D 9
	return (xp);
E 9
I 9
	return (m);
E 9
}

/* 
 *  This routine restarts all the virtual circuits. Actually,
 *  the virtual circuits are not "restarted" as such. Instead,
 *  any active switched circuit is simply returned to READY
 *  state.
 */

pk_restart (pkp, restart_cause)
register struct pkcb *pkp;
int restart_cause;
{
D 9
	register struct x25_packet *xp;
E 9
I 9
	register struct mbuf *m;
E 9
	register struct pklcd *lcp;
	register int i;

	/* Restart all logical channels. */
I 3
D 7
	if (pkp->pk_chan == 0)
E 7
I 7
	if (pkp -> pk_chan == 0)
E 7
		return;
E 3
D 7
	for (i = 1; i <= pkp->pk_maxlcn; ++i)
		if ((lcp = pkp->pk_chan[i]) != NULL) {
E 7
I 7
D 24
	for (i = 1; i <= pkp -> pk_maxlcn; ++i)
		if ((lcp = pkp -> pk_chan[i]) != NULL) {
E 7
D 9
			if (lcp -> lcd_so)
E 9
I 9
			if (lcp -> lcd_so) {
E 9
D 7
				lcp->lcd_so -> so_error = ENETRESET;
E 7
I 7
				lcp -> lcd_so -> so_error = ENETRESET;
E 7
D 9
			pk_close (lcp);
E 9
I 9
				pk_close (lcp);
			} else {
				pk_flush (lcp);
				lcp -> lcd_state = READY;
				if (lcp -> lcd_upper)
D 10
					lcp -> lcd_upper(lcp, 0);
E 10
I 10
					lcp -> lcd_upper (lcp, 0);
E 24
I 24

	/*
	 * Don't do this if we're doing a restart issued from
D 26
	 * inside pk_connect() --- which is only done if and
E 26
I 26
	 * inside pk_connect () --- which is only done if and
E 26
	 * only if the X.25 link is down, i.e. a RESTART needs
	 * to be done to get it up.
	 */
	if (!(pkp -> pk_dxerole & DTE_CONNECTPENDING)) {
		for (i = 1; i <= pkp -> pk_maxlcn; ++i)
			if ((lcp = pkp -> pk_chan[i]) != NULL) {
				if (lcp -> lcd_so) {
					lcp -> lcd_so -> so_error = ENETRESET;
					pk_close (lcp);
				} else {
					pk_flush (lcp);
					lcp -> lcd_state = READY;
					if (lcp -> lcd_upper)
						lcp -> lcd_upper (lcp, 0);
				}
E 24
E 10
			}
E 9
D 24
		}
E 24
I 24
	}
E 24

	if (restart_cause < 0)
		return;

D 7
	pkp->pk_state = DTE_SENT_RESTART;
	lcp = pkp->pk_chan[0];
E 7
I 7
	pkp -> pk_state = DTE_SENT_RESTART;
I 24
	pkp -> pk_dxerole &= ~(DTE_PLAYDCE | DTE_PLAYDTE);
E 24
	lcp = pkp -> pk_chan[0];
E 7
D 9
	xp = lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_RESTART);
	(dtom (xp)) -> m_len++;
	xp -> packet_data = 0;	/* DTE only */
E 9
I 9
	m = lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_RESTART);
D 13
	m -> m_len += 2;
E 13
I 13
	m -> m_pkthdr.len = m -> m_len += 2;
E 13
D 10
	mtod(m, struct x25_packet *) -> packet_data = 0;	/* DTE only */
	mtod(m, octet *)[4]  = restart_cause;
E 10
I 10
	mtod (m, struct x25_packet *) -> packet_data = 0;	/* DTE only */
	mtod (m, octet *)[4]  = restart_cause;
E 10
E 9
	pk_output (lcp);
}


/* 
 *  This procedure frees up the Logical Channel Descripter.
 */

D 4
static
E 4
pk_freelcd (lcp)
register struct pklcd *lcp;
{
	if (lcp == NULL)
		return;

D 9
	if (lcp -> lcd_template)
		m_freem (dtom (lcp -> lcd_template));

E 9
D 4
	if (lcp -> lcd_craddr)
		m_freem (dtom (lcp -> lcd_craddr));

	if (lcp -> lcd_ceaddr)
		m_freem (dtom (lcp -> lcd_ceaddr));

E 4
	if (lcp -> lcd_lcn > 0)
		lcp -> lcd_pkp -> pk_chan[lcp -> lcd_lcn] = NULL;

I 9
D 10
	pk_flush(lcp);
E 9
D 4
	m_freem (dtom (lcp));
E 4
I 4
	free((caddr_t)lcp, M_PCB);
E 10
I 10
	pk_flush (lcp);
	remque (&lcp -> lcd_q);
	free ((caddr_t)lcp, M_PCB);
E 10
E 4
}

I 26
static struct x25_ifaddr *
pk_ifwithaddr (sx)
	struct sockaddr_x25 *sx;
{
	struct ifnet *ifp;
	struct ifaddr *ifa;
	register struct x25_ifaddr *ia;
	char *addr = sx -> x25_addr;
E 26

I 26
	for (ifp = ifnet; ifp; ifp = ifp -> if_next)
		for (ifa = ifp -> if_addrlist; ifa; ifa = ifa -> ifa_next)
			if (ifa -> ifa_addr -> sa_family == AF_CCITT) {
				ia = (struct x25_ifaddr *)ifa;
				if (bcmp (addr, ia -> ia_xc.xc_addr.x25_addr,
					 16) == 0)
					return (ia);
				
			}
	return ((struct x25_ifaddr *)0);
}


E 26
/* 
 *  Bind a address and protocol value to a socket.  The important
 *  part is the protocol value - the first four characters of the 
 *  Call User Data field.
 */

I 24
D 26
#define XTRACTPKP(rt)	((rt)->rt_flags & RTF_GATEWAY ? \
			 ((rt)->rt_llinfo ? \
			  (struct pkcb *) ((struct rtentry *)((rt)->rt_llinfo))->rt_llinfo : \
E 26
I 26
#define XTRACTPKP(rt)	((rt) -> rt_flags & RTF_GATEWAY ? \
			 ((rt) -> rt_llinfo ? \
			  (struct pkcb *) ((struct rtentry *)((rt) -> rt_llinfo)) -> rt_llinfo : \
E 26
			  (struct pkcb *) NULL) : \
D 26
			 (struct pkcb *)((rt)->rt_llinfo))
E 26
I 26
			 (struct pkcb *)((rt) -> rt_llinfo))
E 26

E 24
pk_bind (lcp, nam)
struct pklcd *lcp;
struct mbuf *nam;
{
D 4
	register struct sockaddr_x25 *sa;
E 4
D 26
	register struct pkcb *pkp;
E 26
D 9
	register struct mbuf *m;
E 9
	register struct pklcd *pp;
I 4
	register struct sockaddr_x25 *sa;
I 24
D 26
	register struct rtentry *rt;
E 26
E 24
E 4

	if (nam == NULL)
		return (EADDRNOTAVAIL);
	if (lcp -> lcd_ceaddr)				/* XXX */
		return (EADDRINUSE);
D 9
	if (checksockaddr (nam))
E 9
I 9
	if (pk_checksockaddr (nam))
E 9
		return (EINVAL);
	sa = mtod (nam, struct sockaddr_x25 *);

	/*
	 * If the user wishes to accept calls only from a particular
	 * net (net != 0), make sure the net is known
	 */

D 24
	if (sa -> x25_net)
		for (pkp = pkcbhead; ; pkp = pkp -> pk_next) {
			if (pkp == 0)
				return (ENETUNREACH);
D 6
			if (pkp -> pk_xcp -> xc_net == sa -> x25_net)
E 6
I 6
			if (pkp -> pk_xcp -> xc_addr.x25_net == sa -> x25_net)
E 6
				break;
		}
E 24
I 24
D 26
	if ( !(rt =  rtalloc1(sa, 1)))
		return (ENETUNREACH);
	pkp = XTRACTPKP(rt);
E 26
I 26
	if (sa -> x25_addr[0]) {
		if (!pk_ifwithaddr (sa))
			return (ENETUNREACH);
	} else if (sa -> x25_net) {
		if (!ifa_ifwithnet ((struct sockaddr *)sa))
			return (ENETUNREACH);
	}
E 26
E 24

D 9
	for (pp = pk_listenhead; pp; pp = pp -> lcd_listen)
		if (bcmp (pp -> lcd_ceaddr -> x25_udata, sa -> x25_udata,
D 7
			min (pp->lcd_ceaddr->x25_udlen, sa->x25_udlen)) == 0)
E 7
I 7
		          min (pp -> lcd_ceaddr -> x25_udlen, sa -> x25_udlen)) == 0)
E 7
			return (EADDRINUSE);

E 9
I 9
	/*
	 * For ISO's sake permit default listeners, but only one such . . .
	 */
	for (pp = pk_listenhead; pp; pp = pp -> lcd_listen) {
		register struct sockaddr_x25 *sa2 = pp -> lcd_ceaddr;
		if ((sa2 -> x25_udlen == sa -> x25_udlen) &&
		    (sa2 -> x25_udlen == 0 ||
		     (bcmp (sa2 -> x25_udata, sa -> x25_udata,
			    min (sa2 -> x25_udlen, sa -> x25_udlen)) == 0)))
				return (EADDRINUSE);
	}
E 9
D 4
	if ((m = m_copy (nam, 0, (int)M_COPYALL)) == 0)
		return (ENOBUFS);
	lcp -> lcd_ceaddr = mtod (m, struct sockaddr_x25 *);
E 4
I 4
	lcp -> lcd_laddr = *sa;
	lcp -> lcd_ceaddr = &lcp -> lcd_laddr;
E 4
	return (0);
}

/*
I 9
 * Include a bound control block in the list of listeners.
 */
pk_listen (lcp)
register struct pklcd *lcp;
{
	register struct pklcd **pp;

	if (lcp -> lcd_ceaddr == 0)
		return (EDESTADDRREQ);

	lcp -> lcd_state = LISTEN;
	/*
	 * Add default listener at end, any others at start.
	 */
	if (lcp -> lcd_ceaddr -> x25_udlen == 0) {
		for (pp = &pk_listenhead; *pp; )
			pp = &((*pp) -> lcd_listen);
		*pp = lcp;
	} else {
		lcp -> lcd_listen = pk_listenhead;
		pk_listenhead = lcp;
	}
	return (0);
}
/*
 * Include a listening control block for the benefit of other protocols.
 */
pk_protolisten (spi, spilen, callee)
D 10
int (*callee)();
E 10
I 10
int (*callee) ();
E 10
{
	register struct pklcd *lcp = pk_attach ((struct socket *)0);
	register struct mbuf *nam;
	register struct sockaddr_x25 *sa;
	int error = ENOBUFS;

	if (lcp) {
D 10
		if (nam = m_getclr(MT_SONAME, M_DONTWAIT)) {
			sa = mtod(nam, struct sockaddr_x25 *);
E 10
I 10
		if (nam = m_getclr (MT_SONAME, M_DONTWAIT)) {
			sa = mtod (nam, struct sockaddr_x25 *);
E 10
			sa -> x25_family = AF_CCITT;
			sa -> x25_len = nam -> m_len = sizeof (*sa);
			sa -> x25_udlen = spilen;
			sa -> x25_udata[0] = spi;
			lcp -> lcd_upper = callee;
			lcp -> lcd_flags = X25_MBS_HOLD;
D 15
			error = pk_bind (lcp, nam) || pk_listen (lcp);
E 15
I 15
			if ((error = pk_bind (lcp, nam)) == 0)
				error = pk_listen (lcp);
E 15
			(void) m_free (nam);
		}
		if (error)
D 10
			pk_freelcd(lcp);
E 10
I 10
			pk_freelcd (lcp);
E 10
	}
	return error; /* Hopefully Zero !*/
}

/*
E 9
 * Associate a logical channel descriptor with a network.
 * Fill in the default network specific parameters and then
 * set any parameters explicitly specified by the user or
 * by the remote DTE.
 */

pk_assoc (pkp, lcp, sa)
register struct pkcb *pkp;
register struct pklcd *lcp;
register struct sockaddr_x25 *sa;
{

	lcp -> lcd_pkp = pkp;
	lcp -> lcd_packetsize = pkp -> pk_xcp -> xc_psize;
	lcp -> lcd_windowsize = pkp -> pk_xcp -> xc_pwsize;
	lcp -> lcd_rsn = MODULUS - 1;
	pkp -> pk_chan[lcp -> lcd_lcn] = lcp;

	if (sa -> x25_opts.op_psize)
		lcp -> lcd_packetsize = sa -> x25_opts.op_psize;
	else
		sa -> x25_opts.op_psize = lcp -> lcd_packetsize;
	if (sa -> x25_opts.op_wsize)
		lcp -> lcd_windowsize = sa -> x25_opts.op_wsize;
	else
		sa -> x25_opts.op_wsize = lcp -> lcd_windowsize;
D 6
	sa -> x25_net = pkp -> pk_xcp -> xc_net;
E 6
I 6
	sa -> x25_net = pkp -> pk_xcp -> xc_addr.x25_net;
E 6
D 16
	lcp -> lcd_flags = sa -> x25_opts.op_flags;
E 16
I 16
	lcp -> lcd_flags |= sa -> x25_opts.op_flags;
E 16
	lcp -> lcd_stime = time.tv_sec;
}

D 4
pk_connect (lcp, nam)
E 4
I 4
D 9
pk_connect (lcp, nam, sa)
E 9
I 9
pk_connect (lcp, sa)
E 9
E 4
register struct pklcd *lcp;
I 4
register struct sockaddr_x25 *sa;
E 4
D 9
struct mbuf *nam;
E 9
{
	register struct pkcb *pkp;
I 24
	register struct rtentry *rt;
	register struct rtentry *nrt;
E 24
D 4
	register struct sockaddr_x25 *sa;
E 4
D 9
	register struct mbuf *m;
I 4
	register struct ifnet *ifp;
E 9
E 4

I 24
D 26
	struct rtentry *npaidb_enter();
	struct pkcb *pk_newlink();
E 26
I 26
	struct rtentry *npaidb_enter ();
	struct pkcb *pk_newlink ();
E 26

E 24
D 4
	if (checksockaddr (nam))
		return (EINVAL);
	sa = mtod (nam, struct sockaddr_x25 *);
E 4
I 4
D 9
	if (sa == 0) {
		if (checksockaddr (nam))
			return (EINVAL);
		sa = mtod (nam, struct sockaddr_x25 *);
	}
E 9
E 4
	if (sa -> x25_addr[0] == '\0')
		return (EDESTADDRREQ);
D 4
	for (pkp = pkcbhead; ; pkp = pkp->pk_next) {
E 4
I 4
D 7
	if (lcp->lcd_pkp == 0)
	    for (pkp = pkcbhead; ; pkp = pkp->pk_next) {
E 7
I 7
D 24
	if (lcp -> lcd_pkp == 0)
	    for (pkp = pkcbhead; ; pkp = pkp -> pk_next) {
E 7
E 4
		if (pkp == 0)
			return (ENETUNREACH);
		/*
		 * use first net configured (last in list
		 * headed by pkcbhead) if net is zero
I 15
		 *
		 * This is clearly bogus for many llc2's sharing
		 * the same xcp; we will replace this with a
		 * routing lookup.
E 15
		 */
		if (sa -> x25_net == 0 && pkp -> pk_next == 0)
			break;
D 6
		if (sa -> x25_net == pkp -> pk_xcp -> xc_net)
E 6
I 6
		if (sa -> x25_net == pkp -> pk_xcp -> xc_addr.x25_net)
E 6
			break;
E 24
I 24

	/*
	 * Is the destination address known?
	 */
D 27
	if (!(rt = rtalloc1 (sa, 1)))
E 27
I 27
	if (!(rt = rtalloc1 ((struct sockaddr *)sa, 1)))
E 27
		return (ENETUNREACH);

	if (!(pkp = XTRACTPKP(rt)))
D 26
		pkp = pk_newlink((struct x25_ifaddr *) (rt -> rt_ifa), 
E 26
I 26
		pkp = pk_newlink ((struct x25_ifaddr *) (rt -> rt_ifa), 
E 26
				 (caddr_t) 0);

	/*
	 * Have we entered the LLC address?
	 */
D 26
	if (nrt = npaidb_enter(rt -> rt_gateway, rt_key(rt), rt, 0))
E 26
I 26
	if (nrt = npaidb_enter (rt -> rt_gateway, rt_key (rt), rt, 0))
E 26
		pkp -> pk_llrt = nrt;

	/*
	 * Have we allocated an LLC2 link yet?
	 */
D 26
	if (pkp->pk_llnext == (caddr_t)0 && pkp->pk_llctlinput) {
E 26
I 26
	if (pkp -> pk_llnext == (caddr_t)0 && pkp -> pk_llctlinput) {
E 26
		struct dll_ctlinfo ctlinfo;

		ctlinfo.dlcti_rt = rt;
		ctlinfo.dlcti_pcb = (caddr_t) pkp;
		ctlinfo.dlcti_conf = 
D 26
			(struct dllconfig *) (&((struct x25_ifaddr *)(rt->rt_ifa))->ia_xc);
		pkp->pk_llnext = 
			(pkp->pk_llctlinput)(PRC_CONNECT_REQUEST, 0, &ctlinfo);
E 26
I 26
			(struct dllconfig *) (&((struct x25_ifaddr *)(rt -> rt_ifa)) -> ia_xc);
		pkp -> pk_llnext = 
			(pkp -> pk_llctlinput) (PRC_CONNECT_REQUEST, 0, &ctlinfo);
E 26
E 24
	}

D 24
	if (pkp -> pk_state != DTE_READY)
		return (ENETDOWN);
E 24
I 24
	if (pkp -> pk_state != DTE_READY && pkp -> pk_state != DTE_WAITING)
			return (ENETDOWN);
E 24
	if ((lcp -> lcd_lcn = pk_getlcn (pkp)) == 0)
		return (EMFILE);
I 24

E 24
D 4
	if ((m = m_copy (nam, 0, (int)M_COPYALL)) == 0)
		return (ENOBUFS);
	lcp -> lcd_ceaddr = mtod (m, struct sockaddr_x25 *);
E 4
I 4
	lcp -> lcd_faddr = *sa;
D 7
	lcp -> lcd_ceaddr = & lcp->lcd_faddr;
E 7
I 7
	lcp -> lcd_ceaddr = & lcp -> lcd_faddr;
E 7
E 4
	pk_assoc (pkp, lcp, lcp -> lcd_ceaddr);
I 24

	/*
	 * If the link is not up yet, initiate an X.25 RESTART
	 */
	if (pkp -> pk_state == DTE_WAITING) {
		pkp -> pk_dxerole |= DTE_CONNECTPENDING;
D 26
		pk_ctlinput(PRC_LINKUP, (struct sockaddr *)0, pkp);
E 26
I 26
		pk_ctlinput (PRC_LINKUP, (struct sockaddr *)0, pkp);
E 26
		if (lcp -> lcd_so)
			soisconnecting (lcp -> lcd_so);
		return 0;
	}

E 24
D 3
	soisconnecting (lcp -> lcd_so);
E 3
I 3
D 6
	if (lcp -> so)
E 6
I 6
	if (lcp -> lcd_so)
E 6
		soisconnecting (lcp -> lcd_so);
E 3
	lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_CALL);
D 4
	pk_callrequest (lcp, m, pkp -> pk_xcp);
	pk_output (lcp);
	return (0);
E 4
I 4
	pk_callrequest (lcp, lcp -> lcd_ceaddr, pkp -> pk_xcp);
D 10
	return (*pkp -> pk_start)(lcp);
E 10
I 10
D 15
	return (*pkp -> pk_start) (lcp);
E 15
I 15
	return (*pkp -> pk_ia -> ia_start) (lcp);
E 15
E 10
E 4
}

I 24
/*
 * Complete all pending X.25 call requests --- this gets called after
 * the X.25 link has been restarted.
 */
#define RESHUFFLELCN(maxlcn, lcn) ((maxlcn) - (lcn) + 1)

D 26
pk_callcomplete(pkp)
E 26
I 26
pk_callcomplete (pkp)
E 26
	register struct pkcb *pkp;
{
	register struct pklcd *lcp;
	register int i;
	register int ni;
	

	if (pkp -> pk_dxerole & DTE_CONNECTPENDING) 
		pkp -> pk_dxerole &= ~DTE_CONNECTPENDING;
	else return;

	if (pkp -> pk_chan == 0)
		return;
	
	/*
	 * We pretended to be a DTE for allocating lcns, if
	 * it turns out that we are in reality performing as a
	 * DCE we need to reshuffle the lcps.
	 *			        	  	      
         *             /+---------------+--------     -	      
	 *            / | a  (maxlcn-1) |              \      
	 *           /  +---------------+              	\     
	 *     +--- *   | b  (maxlcn-2) |         	 \    
	 *     |     \  +---------------+         	  \   
	 *   r |      \ | c  (maxlcn-3) |         	   \  
	 *   e |       \+---------------+         	    | 
	 *   s |        |	 .                	    |  
	 *   h |        |        .                	    | m
	 *   u |        |	 .      	  	    | a
	 *   f |        |	 .      	  	    | x
	 *   f |        |	 .                	    | l
	 *   l |       /+---------------+         	    | c
	 *   e |      / | c' (   3    ) |         	    | n
	 *     |     /  +---------------+         	    | 
	 *     +--> *   | b' (   2    ) |         	   /
	 *           \  +---------------+         	  / 
	 *            \ | a' (   1    ) |         	 /  
    	 *             \+---------------+               /   
         *              | 0             |              /    
	 *              +---------------+--------     -     
	 *	    
	 */	    
	if (pkp -> pk_dxerole & DTE_PLAYDCE) {
		/* Sigh, reshuffle it */
		for (i = pkp -> pk_maxlcn; i > 0; --i)
			if (pkp -> pk_chan[i]) {
				ni = RESHUFFLELCN(pkp -> pk_maxlcn, i);
				pkp -> pk_chan[ni] = pkp -> pk_chan[i];
				pkp -> pk_chan[i] = NULL;
				pkp -> pk_chan[ni] -> lcd_lcn = ni;
			}
	}

	for (i = 1; i <= pkp -> pk_maxlcn; ++i)
		if ((lcp = pkp -> pk_chan[i]) != NULL) {
			/* if (lcp -> lcd_so)
				soisconnecting (lcp -> lcd_so); */
			lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_CALL);
			pk_callrequest (lcp, lcp -> lcd_ceaddr, pkp -> pk_xcp);
D 26
			(*pkp -> pk_ia -> ia_start)(lcp);
E 26
I 26
			(*pkp -> pk_ia -> ia_start) (lcp);
E 26
		}
}

E 24
I 14
struct bcdinfo {
	octet *cp;
	unsigned posn;
};
E 14
/* 
 *  Build the rest of the CALL REQUEST packet. Fill in calling
 *  address, facilities fields and the user data field.
 */

D 4
pk_callrequest (lcp, nam, xcp)
E 4
I 4
pk_callrequest (lcp, sa, xcp)
E 4
struct pklcd *lcp;
D 4
struct mbuf *nam;
E 4
I 4
register struct sockaddr_x25 *sa;
E 4
register struct x25config *xcp;
{
	register struct x25_calladdr *a;
D 4
	register struct sockaddr_x25 *sa = mtod (nam, struct sockaddr_x25 *);
E 4
D 9
	register struct mbuf *m = dtom (lcp -> lcd_template);
E 9
I 9
	register struct mbuf *m = lcp -> lcd_template;
D 10
	register struct x25_packet *xp = mtod(m, struct x25_packet *);
E 10
I 10
	register struct x25_packet *xp = mtod (m, struct x25_packet *);
E 10
E 9
D 14
	unsigned posn = 0;
	octet *cp;
E 14
I 14
	struct bcdinfo b;
E 14
D 6
	char addr[sizeof (xcp -> xc_ntn) * 2];
E 6

I 8
	if (lcp -> lcd_flags & X25_DBIT)
D 9
		lcp -> lcd_template -> d_bit = 1;
E 8
	a = (struct x25_calladdr *) &lcp -> lcd_template -> packet_data;
E 9
I 9
D 24
		xp -> d_bit = 1;
E 24
I 24
		X25SBITS(xp -> bits, d_bit, 1);
E 24
	a = (struct x25_calladdr *) &xp -> packet_data;
E 9
D 6
	a -> calling_addrlen = xcp -> xc_ntnlen;
	cp = (octet *) xcp -> xc_ntn;
	from_bcd (addr, &cp, xcp -> xc_ntnlen);
E 6
I 6
D 14
	a -> calling_addrlen = strlen (xcp -> xc_addr.x25_addr);
E 6
	a -> called_addrlen = strlen (sa -> x25_addr);
	cp = (octet *) a -> address_field;
	to_bcd (&cp, (int)a -> called_addrlen, sa -> x25_addr, &posn);
D 6
	to_bcd (&cp, (int)a -> calling_addrlen, addr, &posn);
E 6
I 6
	to_bcd (&cp, (int)a -> calling_addrlen, xcp -> xc_addr.x25_addr, &posn);
E 6
	if (posn & 0x01)
		*cp++ &= 0xf0;
D 9

	build_facilities (&cp, sa, (int)xcp -> xc_type);

	bcopy (sa -> x25_udata, (caddr_t)cp, (unsigned)sa -> x25_udlen);
	cp += sa -> x25_udlen;

E 9
D 13
	m -> m_len += cp - (octet *) a;
E 13
I 13
	m -> m_pkthdr.len = m -> m_len += cp - (octet *) a;
E 14
I 14
	b.cp = (octet *) a -> address_field;
	b.posn = 0;
D 24
	a -> called_addrlen = to_bcd (&b, sa, xcp);
	a -> calling_addrlen = to_bcd (&b, &xcp -> xc_addr, xcp);
E 24
I 24
	X25SBITS(a -> addrlens, called_addrlen, to_bcd (&b, sa, xcp));
	X25SBITS(a -> addrlens, calling_addrlen, to_bcd (&b, &xcp -> xc_addr, xcp));
E 24
	if (b.posn & 0x01)
		*b.cp++ &= 0xf0;
	m -> m_pkthdr.len = m -> m_len += b.cp - (octet *) a;
E 14
E 13

I 9
	if (lcp -> lcd_facilities) {
D 10
		m -> m_next = lcp -> lcd_facilities;
E 10
I 10
		m -> m_pkthdr.len += 
D 14
			(m -> m_next = lcp -> lcd_facilities) -> m_len;
E 14
I 14
			(m -> m_next = lcp -> lcd_facilities) -> m_pkthdr.len;
E 14
E 10
		lcp -> lcd_facilities = 0;
D 10
		m -> m_pkthdr.len += m -> m_next -> m_len;
E 10
	} else
D 14
		build_facilities (m, sa, (int)xcp -> xc_type);
E 14
I 14
		pk_build_facilities (m, sa, (int)xcp -> xc_type);
E 14

D 10
	m_copyback(m, m -> m_pkthdr.len, sa -> x25_udlen, sa -> x25_udata);
E 10
I 10
	m_copyback (m, m -> m_pkthdr.len, sa -> x25_udlen, sa -> x25_udata);
E 10
E 9
D 14
#ifdef ANDREW
	printf ("call: ");
D 7
	for (cp = mtod (m, octet *), posn = 0; posn < m->m_len; ++posn)
E 7
I 7
	for (cp = mtod (m, octet *), posn = 0; posn < m -> m_len; ++posn)
E 7
		printf ("%x ", *cp++);
	printf ("\n");
#endif
E 14
}

I 10
D 14
static
E 10
D 9
build_facilities (cp, sa, type)
register octet **cp;
E 9
I 9
build_facilities (m, sa, type)
E 14
I 14
pk_build_facilities (m, sa, type)
E 14
register struct mbuf *m;
E 9
struct sockaddr_x25 *sa;
{
I 9
	register octet *cp;
E 9
	register octet *fcp;
	register int revcharge;

D 9
	fcp = *cp + 1;
E 9
I 9
D 10
	cp = mtod(m, octet *) + m -> m_len;
E 10
I 10
	cp = mtod (m, octet *) + m -> m_len;
E 10
	fcp = cp + 1;
E 9
	revcharge = sa -> x25_opts.op_flags & X25_REVERSE_CHARGE ? 1 : 0;
	/*
	 * This is specific to Datapac X.25(1976) DTEs.  International
	 * calls must have the "hi priority" bit on.
	 */
	if (type == X25_1976 && sa -> x25_opts.op_psize == X25_PS128)
		revcharge |= 02;
	if (revcharge) {
		*fcp++ = FACILITIES_REVERSE_CHARGE;
		*fcp++ = revcharge;
	}
	switch (type) {
	case X25_1980:
	case X25_1984:
		*fcp++ = FACILITIES_PACKETSIZE;
		*fcp++ = sa -> x25_opts.op_psize;
		*fcp++ = sa -> x25_opts.op_psize;

		*fcp++ = FACILITIES_WINDOWSIZE;
		*fcp++ = sa -> x25_opts.op_wsize;
		*fcp++ = sa -> x25_opts.op_wsize;
	}
D 9
	**cp = fcp - *cp - 1;
	*cp = fcp;
E 9
I 9
	*cp = fcp - cp - 1;
	m -> m_pkthdr.len = (m -> m_len += *cp + 1);
E 9
}

D 14
to_bcd (a, len, x, posn)
register octet **a;
register char *x;
register int len;
register unsigned *posn;
E 14
I 14
to_bcd (b, sa, xcp)
register struct bcdinfo *b;
struct sockaddr_x25 *sa;
register struct x25config *xcp;
E 14
{
D 14
	while (--len >= 0)
		if ((*posn)++ & 0x01)
			*(*a)++ |= *x++ & 0x0F;
E 14
I 14
	register char *x = sa -> x25_addr;
	unsigned start = b -> posn;
	/*
	 * The nodnic and prepnd0 stuff looks tedious,
	 * but it does allow full X.121 addresses to be used,
	 * which is handy for routing info (& OSI type 37 addresses).
	 */
	if (xcp -> xc_addr.x25_net && (xcp -> xc_nodnic || xcp -> xc_prepnd0)) {
D 26
		char dnicname[sizeof(long) * NBBY/3 + 2];
E 26
I 26
		char dnicname[sizeof (long) * NBBY/3 + 2];
E 26
		register char *p = dnicname;

		sprintf (p, "%d", xcp -> xc_addr.x25_net & 0x7fff);
		for (; *p; p++) /* *p == 0 means dnic matched */
			if ((*p ^ *x++) & 0x0f)
				break;
		if (*p || xcp -> xc_nodnic == 0)
			x = sa -> x25_addr;
		if (*p && xcp -> xc_prepnd0) {
			if ((b -> posn)++ & 0x01)
				*(b -> cp)++;
			else
				*(b -> cp) = 0;
		}
	}
	while (*x)
		if ((b -> posn)++ & 0x01)
			*(b -> cp)++ |= *x++ & 0x0F;
E 14
		else
D 14
			**a = *x++ << 4;
E 14
I 14
			*(b -> cp) = *x++ << 4;
	return ((b -> posn) - start);
E 14
}

/* 
 *  This routine gets the  first available logical channel number.  The
D 24
 *  search is from the highest number to lowest number (DTE).
E 24
I 24
 *  search is 
 *  		- from the highest number to lowest number if playing DTE, and
 *		- from lowest to highest number if playing DCE.
E 24
 */

pk_getlcn (pkp)
register struct pkcb *pkp;
{
	register int i;

I 3
D 7
	if (pkp->pk_chan == 0)
E 7
I 7
	if (pkp -> pk_chan == 0)
E 7
		return (0);
E 3
D 24
	for (i = pkp -> pk_maxlcn; i > 0; --i)
		if (pkp -> pk_chan[i] == NULL)
			break;
E 24
I 24
	if ( pkp -> pk_dxerole & DTE_PLAYDCE ) {
		for (i = 1; i <= pkp -> pk_maxlcn; ++i)
			if (pkp -> pk_chan[i] == NULL)
				break;
	} else { 
		for (i = pkp -> pk_maxlcn; i > 0; --i)
			if (pkp -> pk_chan[i] == NULL)
				break;
	}
	i = ( i > pkp -> pk_maxlcn ? 0 : i );
E 24
	return (i);
D 24

E 24
}

D 9
static
checksockaddr (m)
struct mbuf *m;
{
	register struct sockaddr_x25 *sa = mtod (m, struct sockaddr_x25 *);
	register char *cp;

	if (m -> m_len != sizeof (struct sockaddr_x25))
		return (1);
	if (sa -> x25_family != AF_CCITT || sa -> x25_udlen == 0 ||
		sa -> x25_udlen > sizeof (sa -> x25_udata))
		return (1);
	for (cp = sa -> x25_addr; *cp; cp++) {
		if (*cp < '0' || *cp > '9' ||
			cp >= &sa -> x25_addr[sizeof (sa -> x25_addr) - 1])
			return (1);
	}
	return (0);
}

E 9
/* 
 *  This procedure sends a CLEAR request packet. The lc state is
 *  set to "SENT_CLEAR". 
 */

D 9
pk_clear (lcp)
struct pklcd *lcp;
E 9
I 9
pk_clear (lcp, diagnostic, abortive)
register struct pklcd *lcp;
E 9
{
D 9
	register struct x25_packet *xp;
E 9
I 9
	register struct mbuf *m = pk_template (lcp -> lcd_lcn, X25_CLEAR);
E 9

D 9
	xp = lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_CLEAR);
	(dtom (xp)) -> m_len++;
	xp -> packet_data = 0;

E 9
I 9
	m -> m_len += 2;
I 18
	m -> m_pkthdr.len += 2;
E 18
D 10
	mtod(m, struct x25_packet *) -> packet_data = 0;
	mtod(m, octet *)[4] = diagnostic;
E 10
I 10
	mtod (m, struct x25_packet *) -> packet_data = 0;
	mtod (m, octet *)[4] = diagnostic;
E 10
	if (lcp -> lcd_facilities) {
		m -> m_next = lcp -> lcd_facilities;
		m -> m_pkthdr.len += m -> m_next -> m_len;
		lcp -> lcd_facilities = 0;
	}
	if (abortive)
		lcp -> lcd_template = m;
	else {
		struct socket *so = lcp -> lcd_so;
		struct sockbuf *sb = so ? & so -> so_snd : & lcp -> lcd_sb;
D 10
		sbappendrecord(sb, m);
E 10
I 10
		sbappendrecord (sb, m);
E 10
	}
E 9
	pk_output (lcp);

}

I 10
/*
 * This procedure generates RNR's or RR's to inhibit or enable
 * inward data flow, if the current state changes (blocked ==> open or
 * vice versa), or if forced to generate one.  One forces RNR's to ack data.  
 */
pk_flowcontrol (lcp, inhibit, forced)
register struct pklcd *lcp;
{
	inhibit = (inhibit != 0);
	if (lcp == 0 || lcp -> lcd_state != DATA_TRANSFER ||
	    (forced == 0 && lcp -> lcd_rxrnr_condition == inhibit))
		return;
	lcp -> lcd_rxrnr_condition = inhibit;
D 15
	lcp -> lcd_template = pk_template (lcp -> lcd_lcn, inhibit ? RNR : RR);
E 15
I 15
	lcp -> lcd_template =
		pk_template (lcp -> lcd_lcn, inhibit ? X25_RNR : X25_RR);
E 15
	pk_output (lcp);
}

E 10
/* 
D 10
 *  This procedure sends a RESET request packet. It re-intializes 
E 10
I 10
 *  This procedure sends a RESET request packet. It re-intializes
E 10
 *  virtual circuit.
 */

static
D 9
pk_reset (lcp)
E 9
I 9
pk_reset (lcp, diagnostic)
E 9
register struct pklcd *lcp;
{
D 9
	register struct x25_packet *xp;
	register struct socket *so;
E 9
I 9
	register struct mbuf *m;
	register struct socket *so = lcp -> lcd_so;
E 9

	if (lcp -> lcd_state != DATA_TRANSFER)
		return;

I 9
	if (so)
		so -> so_error = ECONNRESET;
E 9
	lcp -> lcd_reset_condition = TRUE;

	/* Reset all the control variables for the channel. */
I 9
	pk_flush (lcp);
E 9
	lcp -> lcd_window_condition = lcp -> lcd_rnr_condition =
		lcp -> lcd_intrconf_pending = FALSE;
	lcp -> lcd_rsn = MODULUS - 1;
	lcp -> lcd_ssn = 0;
	lcp -> lcd_output_window = lcp -> lcd_input_window =
		lcp -> lcd_last_transmitted_pr = 0;
I 9
	m = lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_RESET);
D 13
	m -> m_len += 2;
E 13
I 13
	m -> m_pkthdr.len = m -> m_len += 2;
E 13
D 10
	mtod(m, struct x25_packet *) -> packet_data = 0;
	mtod(m, octet *)[4] = diagnostic;
E 10
I 10
	mtod (m, struct x25_packet *) -> packet_data = 0;
	mtod (m, octet *)[4] = diagnostic;
E 10
	pk_output (lcp);

}

/*
 * This procedure frees all data queued for output or delivery on a
 *  virtual circuit.
 */

pk_flush (lcp)
register struct pklcd *lcp;
{
	register struct socket *so;

	if (lcp -> lcd_template)
		m_freem (lcp -> lcd_template);

	if (lcp -> lcd_cps) {
D 10
		m_freem(lcp -> lcd_cps);
E 10
I 10
		m_freem (lcp -> lcd_cps);
E 10
		lcp -> lcd_cps = 0;
	}
E 9
D 3
	so = lcp -> lcd_so;
	so -> so_error = ECONNRESET;
	sbflush (&so -> so_rcv);
	sbflush (&so -> so_snd);

E 3
I 3
D 10
	if (so = lcp -> lcd_so)  {
E 10
I 10
	if (lcp -> lcd_facilities) {
		m_freem (lcp -> lcd_facilities);
		lcp -> lcd_facilities = 0;
	}
D 24
	if (so = lcp -> lcd_so) {
E 24
I 24
	if (so = lcp -> lcd_so) 
E 24
E 10
D 9
		so -> so_error = ECONNRESET;
E 9
D 20
		sbflush (&so -> so_rcv);
E 20
		sbflush (&so -> so_snd);
D 9
	}
E 3
	xp = lcp -> lcd_template = pk_template (lcp -> lcd_lcn, X25_RESET);
	(dtom (xp)) -> m_len += 2;
	xp -> packet_data = 0;
	pk_output (lcp);

E 9
I 9
D 24
	} else 
E 24
I 24
	else 
E 24
		sbflush (&lcp -> lcd_sb);
E 9
}

D 10

E 10
/* 
 *  This procedure handles all local protocol procedure errors.
 */

D 9
pk_procerror (error, lcp, errstr)
E 9
I 9
pk_procerror (error, lcp, errstr, diagnostic)
E 9
register struct pklcd *lcp;
char *errstr;
{

	pk_message (lcp -> lcd_lcn, lcp -> lcd_pkp -> pk_xcp, errstr);

	switch (error) {
	case CLEAR: 
D 7
		if (lcp->lcd_so) {
			lcp->lcd_so -> so_error = ECONNABORTED;
			soisdisconnecting (lcp->lcd_so);
E 7
I 7
		if (lcp -> lcd_so) {
			lcp -> lcd_so -> so_error = ECONNABORTED;
			soisdisconnecting (lcp -> lcd_so);
E 7
		}
D 9
		pk_clear (lcp);
E 9
I 9
		pk_clear (lcp, diagnostic, 1);
E 9
		break;

	case RESET: 
D 9
		pk_reset (lcp);
E 9
I 9
		pk_reset (lcp, diagnostic);
E 9
	}
}

/* 
 *  This procedure is called during the DATA TRANSFER state to check 
 *  and  process  the P(R) values  received  in the DATA,  RR OR RNR
 *  packets.
 */

pk_ack (lcp, pr)
struct pklcd *lcp;
unsigned pr;
{
	register struct socket *so = lcp -> lcd_so;

	if (lcp -> lcd_output_window == pr)
		return (PACKET_OK);
	if (lcp -> lcd_output_window < lcp -> lcd_ssn) {
		if (pr < lcp -> lcd_output_window || pr > lcp -> lcd_ssn) {
D 9
			pk_procerror (RESET, lcp, "p(r) flow control error");
E 9
I 9
			pk_procerror (RESET, lcp,
				"p(r) flow control error", 2);
E 9
			return (ERROR_PACKET);
		}
	}
	else {
		if (pr < lcp -> lcd_output_window && pr > lcp -> lcd_ssn) {
D 9
			pk_procerror (RESET, lcp, "p(r) flow control error");
E 9
I 9
			pk_procerror (RESET, lcp,
D 10
				"p(r) flow control error", 2);
E 10
I 10
				"p(r) flow control error #2", 2);
E 10
E 9
			return (ERROR_PACKET);
		}
	}

	lcp -> lcd_output_window = pr;		/* Rotate window. */
	if (lcp -> lcd_window_condition == TRUE)
		lcp -> lcd_window_condition = FALSE;

D 3
	if ((so -> so_snd.sb_flags & SB_WAIT) || so -> so_snd.sb_sel)
E 3
I 3
D 22
	if (so && ((so -> so_snd.sb_flags & SB_WAIT) || so -> so_snd.sb_sel))
E 22
I 22
D 24
	if (so && (so -> so_snd.sb_flags & SB_NOTIFY))
E 24
I 24
	if (so && ((so -> so_snd.sb_flags & SB_WAIT) || 
		   (so -> so_snd.sb_flags & SB_NOTIFY)))
E 24
E 22
E 3
		sowwakeup (so);
I 3
D 5
	if (lcp -> lcd_downq.pq_unblock)
		(*lcp -> lcd_downq.pq_unblock)(lcp);
E 5
I 5
D 13
	if (lcp -> lcd_upper)
D 10
		(*lcp -> lcd_upper)(lcp, 0);
E 10
I 10
		(*lcp -> lcd_upper) (lcp, 0);
E 13
E 10
E 5
E 3

	return (PACKET_OK);
}

/* 
 *  This procedure decodes the X.25 level 3 packet returning a 
 *  code to be used in switchs or arrays.
 */

pk_decode (xp)
register struct x25_packet *xp;
{
	register int type;

D 24
	if (xp -> fmt_identifier != 1)
E 24
I 24
	if (X25GBITS(xp -> bits, fmt_identifier) != 1)
E 24
		return (INVALID_PACKET);
D 9

E 9
I 9
#ifdef ancient_history
E 9
	/* 
	 *  Make sure that the logical channel group number is 0.
	 *  This restriction may be removed at some later date.
	 */
	if (xp -> lc_group_number != 0)
		return (INVALID_PACKET);
D 9

E 9
I 9
#endif
E 9
	/* 
	 *  Test for data packet first.
	 */
	if (!(xp -> packet_type & DATA_PACKET_DESIGNATOR))
		return (DATA);

	/* 
	 *  Test if flow control packet (RR or RNR).
	 */
	if (!(xp -> packet_type & RR_OR_RNR_PACKET_DESIGNATOR))
D 10
		if (!(xp -> packet_type & RR_PACKET_DESIGNATOR))
E 10
I 10
		switch (xp -> packet_type & 0x1f) {
		case X25_RR:
E 10
			return (RR);
D 10
		else
E 10
I 10
		case X25_RNR:
E 10
			return (RNR);
I 10
		case X25_REJECT:
			return (REJECT);
		}
E 10

	/* 
	 *  Determine the rest of the packet types.
	 */
	switch (xp -> packet_type) {
	case X25_CALL: 
		type = CALL;
		break;

	case X25_CALL_ACCEPTED: 
		type = CALL_ACCEPTED;
		break;

	case X25_CLEAR: 
		type = CLEAR;
		break;

	case X25_CLEAR_CONFIRM: 
		type = CLEAR_CONF;
		break;

	case X25_INTERRUPT: 
		type = INTERRUPT;
		break;

	case X25_INTERRUPT_CONFIRM: 
		type = INTERRUPT_CONF;
		break;

	case X25_RESET: 
		type = RESET;
		break;

	case X25_RESET_CONFIRM: 
		type = RESET_CONF;
		break;

	case X25_RESTART: 
		type = RESTART;
		break;

	case X25_RESTART_CONFIRM: 
		type = RESTART_CONF;
		break;

I 10
	case X25_DIAGNOSTIC:
D 11
		type = DIAGNOSTIC;
E 11
I 11
		type = DIAG_TYPE;
E 11
		break;

E 10
	default: 
		type = INVALID_PACKET;
	}
	return (type);
}

/* 
 *  A restart packet has been received. Print out the reason
 *  for the restart.
 */

pk_restartcause (pkp, xp)
struct pkcb *pkp;
register struct x25_packet *xp;
{
	register struct x25config *xcp = pkp -> pk_xcp;
D 8
	register int lcn = xp -> logical_channel_number;
E 8
I 8
	register int lcn = LCN(xp);
E 8

	switch (xp -> packet_data) {
	case X25_RESTART_LOCAL_PROCEDURE_ERROR: 
		pk_message (lcn, xcp, "restart: local procedure error");
		break;

	case X25_RESTART_NETWORK_CONGESTION: 
		pk_message (lcn, xcp, "restart: network congestion");
		break;

	case X25_RESTART_NETWORK_OPERATIONAL: 
		pk_message (lcn, xcp, "restart: network operational");
		break;

	default: 
		pk_message (lcn, xcp, "restart: unknown cause");
	}
}

#define MAXRESETCAUSE	7

int     Reset_cause[] = {
	EXRESET, EXROUT, 0, EXRRPE, 0, EXRLPE, 0, EXRNCG
};

/* 
 *  A reset packet has arrived. Return the cause to the user.
 */

pk_resetcause (pkp, xp)
struct pkcb *pkp;
register struct x25_packet *xp;
{
D 7
	register struct pklcd *lcp = pkp->pk_chan[xp -> logical_channel_number];
E 7
I 7
	register struct pklcd *lcp =
D 8
				pkp -> pk_chan[xp -> logical_channel_number];
E 8
I 8
				pkp -> pk_chan[LCN(xp)];
E 8
E 7
	register int code = xp -> packet_data;

	if (code > MAXRESETCAUSE)
		code = 7;	/* EXRNCG */

I 10
D 26
	pk_message(LCN(xp), lcp -> lcd_pkp, "reset code 0x%x, diagnostic 0x%x",
E 26
I 26
	pk_message (LCN(xp), lcp -> lcd_pkp, "reset code 0x%x, diagnostic 0x%x",
E 26
			xp -> packet_data, 4[(u_char *)xp]);
			
E 10
D 7
	lcp->lcd_so -> so_error = Reset_cause[code];
E 7
I 7
D 15
	lcp -> lcd_so -> so_error = Reset_cause[code];
E 15
I 15
	if (lcp -> lcd_so)
		lcp -> lcd_so -> so_error = Reset_cause[code];
E 15
E 7
}

#define MAXCLEARCAUSE	25

int     Clear_cause[] = {
	EXCLEAR, EXCBUSY, 0, EXCINV, 0, EXCNCG, 0,
	0, 0, EXCOUT, 0, EXCAB, 0, EXCNOB, 0, 0, 0, EXCRPE,
	0, EXCLPE, 0, 0, 0, 0, 0, EXCRRC
};

/* 
 *  A clear packet has arrived. Return the cause to the user.
 */

pk_clearcause (pkp, xp)
struct pkcb *pkp;
register struct x25_packet *xp;
{
D 7
	register struct pklcd *lcp = pkp->pk_chan[xp -> logical_channel_number];
E 7
I 7
	register struct pklcd *lcp =
D 8
		pkp -> pk_chan[xp -> logical_channel_number];
E 8
I 8
		pkp -> pk_chan[LCN(xp)];
E 8
E 7
	register int code = xp -> packet_data;

	if (code > MAXCLEARCAUSE)
		code = 5;	/* EXRNCG */
D 7
	lcp->lcd_so -> so_error = Clear_cause[code];
E 7
I 7
D 13
	lcp -> lcd_so -> so_error = Clear_cause[code];
E 13
I 13
	if (lcp -> lcd_so)
		lcp -> lcd_so -> so_error = Clear_cause[code];
E 13
E 7
}

char *
format_ntn (xcp)
register struct x25config *xcp;
{
D 6
	register int i;
	register char *src, *dest;
	static char ntn[12];
E 6

D 6
	src = xcp->xc_ntn;
	dest = ntn;
	for (i = 0; i < xcp->xc_ntnlen / 2; i++) {
		*dest++ = ((*src & 0xf0) >> 4) + '0';
		*dest++ = (*src++ & 0xf) + '0';
	}
	if (xcp->xc_ntnlen & 01)
		dest[-1] = 0;
	else
		*dest = 0;
	return (ntn);
E 6
I 6
	return (xcp -> xc_addr.x25_addr);
E 6
}

/* VARARGS1 */
pk_message (lcn, xcp, fmt, a1, a2, a3, a4, a5, a6)
struct x25config *xcp;
char *fmt;
{

	if (lcn)
D 24
		if (pkcbhead -> pk_next)
E 24
I 24
		if (!PQEMPTY)
E 24
			printf ("X.25(%s): lcn %d: ", format_ntn (xcp), lcn);
		else
			printf ("X.25: lcn %d: ", lcn);
	else
D 24
		if (pkcbhead -> pk_next)
E 24
I 24
		if (!PQEMPTY)
E 24
			printf ("X.25(%s): ", format_ntn (xcp));
		else
			printf ("X.25: ");

	printf (fmt, a1, a2, a3, a4, a5, a6);
	printf ("\n");
I 7
D 15
}

D 10
pk_ifattach(ia, lloutput, llnext)
E 10
I 10
pk_ifattach (ia, lloutput, llnext)
E 10
register struct x25_ifaddr *ia;
D 10
int (*lloutput)();
E 10
I 10
int (*lloutput) ();
E 10
caddr_t llnext;
{
	/* this is here because you can't include both pk_var and hd_var */
	/* this will probably be replace by a streams gluing mechanism */
	ia -> ia_pkcb.pk_lloutput = lloutput;
	ia -> ia_pkcb.pk_llnext = llnext;
E 15
}

D 10
pk_fragment(lcp, m0, qbit, mbit, wait)
E 10
I 10
pk_fragment (lcp, m0, qbit, mbit, wait)
E 10
struct mbuf *m0;
register struct pklcd *lcp;
{
	register struct mbuf *m = m0;
	register struct x25_packet *xp;
	register struct sockbuf *sb;
D 8
	struct mbuf *next = 0;
E 8
I 8
D 9
	struct mbuf *head = 0, *next, **mp = &head;
E 9
I 9
D 10
	struct mbuf *head = 0, *next, **mp = &head, *m_split();
E 10
I 10
	struct mbuf *head = 0, *next, **mp = &head, *m_split ();
E 10
E 9
E 8
	int totlen, psize = 1 << (lcp -> lcd_packetsize);

	if (m == 0)
D 13
		return;
E 13
I 13
		return 0;
E 13
D 9
	if (m->m_flags & M_PKTHDR == 0)
E 9
I 9
D 21
	if (m -> m_flags & M_PKTHDR == 0)
E 21
I 21
D 24
	if ((m -> m_flags & M_PKTHDR) == 0)
E 24
I 24
	if (m -> m_flags & M_PKTHDR == 0)
E 24
E 21
E 9
D 10
		panic("pk_fragment");
E 10
I 10
		panic ("pk_fragment");
E 10
	totlen = m -> m_pkthdr.len;
I 8
	m -> m_act = 0;
E 8
	sb = lcp -> lcd_so ? &lcp -> lcd_so -> so_snd : & lcp -> lcd_sb;
	do {
		if (totlen > psize) {
D 9
			next = m;
			m = m_copym(m, 0, psize, wait);
			if (m == 0)
E 9
I 9
D 10
			if ((next = m_split(m, psize, wait)) == 0)
E 10
I 10
			if ((next = m_split (m, psize, wait)) == 0)
E 10
E 9
				goto abort;
D 9
			m_adj(next, psize);
E 9
			totlen -= psize;
D 8
		}
E 8
I 8
		} else
			next = 0;
E 8
		M_PREPEND(m, PKHEADERLN, wait);
		if (m == 0)
			goto abort;
I 8
		*mp = m;
		mp = & m -> m_act;
		*mp = 0;
E 8
D 10
		xp = mtod(m, struct x25_packet *);
E 10
I 10
		xp = mtod (m, struct x25_packet *);
E 10
		0[(char *)xp] = 0;
		if (qbit)
D 8
			xp -> q_bit = qbit;
E 8
I 8
D 24
			xp -> q_bit = 1;
E 24
I 24
			X25SBITS(xp -> bits, q_bit, 1);
E 24
		if (lcp -> lcd_flags & X25_DBIT)
D 24
			xp -> d_bit = 1;
E 8
		xp -> fmt_identifier = 1;
E 24
I 24
			X25SBITS(xp -> bits, d_bit, 1);
		X25SBITS(xp -> bits, fmt_identifier, 1);
E 24
D 8
		xp -> logical_channel_number = lcp -> lcd_lcn;
E 8
		xp -> packet_type = X25_DATA;
D 8
		if (next || mbit)
E 8
I 8
		SET_LCN(xp, lcp -> lcd_lcn);
		if (next || (mbit && (totlen == psize ||
				      (lcp -> lcd_flags & X25_DBIT))))
E 8
D 24
			MBIT(xp) = 1;
E 24
I 24
			SMBIT(xp, 1);
E 24
D 8
		m->m_act = next;
E 8
	} while (m = next);
D 8
	for (m = m0; m; m = next) {
E 8
I 8
	for (m = head; m; m = next) {
E 8
		next = m -> m_act;
		m -> m_act = 0;
D 10
		sbappendrecord(sb, m);
E 10
I 10
		sbappendrecord (sb, m);
E 10
	}
	return 0;
abort:
D 8
	for (m = m0; m; m = next) {
E 8
I 8
	if (wait)
D 10
		panic("pk_fragment null mbuf after wait");
E 10
I 10
		panic ("pk_fragment null mbuf after wait");
E 10
	if (next)
D 10
		m_freem(next);
E 10
I 10
		m_freem (next);
E 10
	for (m = head; m; m = next) {
E 8
		next = m -> m_act;
D 10
		m_freem(m);
E 10
I 10
		m_freem (m);
E 10
	}
	return ENOBUFS;
I 8
}
D 17

struct mbuf *
D 10
m_split(m0, len0, wait)
E 10
I 10
m_split (m0, len0, wait)
E 10
register struct mbuf *m0;
int len0;
{
	register struct mbuf *m, *n;
D 16
	unsigned len = len0;
E 16
I 16
	unsigned len = len0, remain;
E 16

	for (m = m0; m && len > m -> m_len; m = m -> m_next)
		len -= m -> m_len;
	if (m == 0)
		return (0);
I 16
	remain = m -> m_len - len;
E 16
	if (m0 -> m_flags & M_PKTHDR) {
		MGETHDR(n, wait, m0 -> m_type);
		if (n == 0)
			return (0);
		n -> m_pkthdr.rcvif = m0 -> m_pkthdr.rcvif;
		n -> m_pkthdr.len = m0 -> m_pkthdr.len - len0;
		m0 -> m_pkthdr.len = len0;
		if (m -> m_flags & M_EXT)
			goto extpacket;
D 16
		if (len > MHLEN) {
E 16
I 16
		if (remain > MHLEN) {
E 16
			/* m can't be the lead packet */
			MH_ALIGN(n, 0);
D 10
			n -> m_next = m_split(m, len, wait);
E 10
I 10
			n -> m_next = m_split (m, len, wait);
E 10
			if (n -> m_next == 0) {
D 10
				(void) m_free(n);
E 10
I 10
				(void) m_free (n);
E 10
				return (0);
			} else
				return (n);
		} else
D 16
			MH_ALIGN(n, len);
	} else if (len == m -> m_len) {
E 16
I 16
			MH_ALIGN(n, remain);
	} else if (remain == 0) {
E 16
		n = m -> m_next;
		m -> m_next = 0;
		return (n);
I 16
	} else {
		MGET(n, wait, m -> m_type);
		if (n == 0)
			return (0);
		M_ALIGN(n, remain);
E 16
	}
extpacket:
D 16
	len = m -> m_len - len;		/* remainder to be copied */
	m -> m_len -= len;		/* now equals original len */
E 16
D 9
	if (m -> m>flags & M_EXT) {
E 9
I 9
	if (m -> m_flags & M_EXT) {
E 9
		n -> m_flags |= M_EXT;
		n -> m_ext = m -> m_ext;
D 10
		mclrefcnt[mtocl(m -> m_ext.ext_buf)]++;
E 10
I 10
		mclrefcnt[mtocl (m -> m_ext.ext_buf)]++;
E 10
D 16
		n -> m_data = m -> m_data + m -> m_len;
E 16
I 16
		n -> m_data = m -> m_data + len;
E 16
	} else {
D 16
		MGET(n, wait, m -> m_type);
		if (n == 0) {
			m -> m_len += len;
			return (0);
		}
		M_ALIGN(n, len);
D 10
		bcopy(mtod(m, caddr_t), mtod(n, caddr_t), len);
E 10
I 10
		bcopy (mtod (m, caddr_t), mtod (n, caddr_t), len);
E 16
I 16
		bcopy (mtod (m, caddr_t) + len, mtod (n, caddr_t), remain);
E 16
E 10
	}
D 16
	n -> m_len = len;
E 16
I 16
	n -> m_len = remain;
	m -> m_len = len;
E 16
	n -> m_next = m -> m_next;
	m -> m_next = 0;
	return (n);
E 8
E 7
}
E 17
E 1
