h38549
s 00001/00001/00591
d D 8.3 94/07/19 10:36:07 sklower 18 17
c isop_laddr is a pointer to a sockaddr_iso, not the thing itself;
c change line about 231 to isop->laddr->siso_tlen
e
s 00002/00001/00590
d D 8.2 94/06/30 20:05:22 sklower 17 16
c fix bugs about binding to a specific NSAP ignoring NSEL
e
s 00002/00002/00589
d D 8.1 93/06/10 23:19:43 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00590
d D 7.14 93/05/25 11:51:43 bostic 15 14
c trailing comment after #else or #endif
e
s 00018/00018/00573
d D 7.13 92/10/11 12:21:52 bostic 14 13
c make kernel includes standard
e
s 00010/00011/00581
d D 7.12 92/04/21 11:27:44 sklower 13 12
c missing ntohs on checks and auto binding  in pcbbind()
e
s 00005/00002/00587
d D 7.11 91/07/29 14:55:25 sklower 12 11
c checkpoint almost working version of kernel TP0/X.25; TP4/Cons seems
c to crash system still.
e
s 00003/00002/00586
d D 7.10 91/06/27 20:10:53 sklower 11 10
c common version for new and old vm
e
s 00009/00005/00579
d D 7.9 91/05/06 19:24:06 bostic 10 9
c new copyright; att/bsd/shared
e
s 00019/00002/00565
d D 7.8 91/04/26 14:59:33 sklower 9 8
c changes for direct TP0 over CONS
e
s 00001/00001/00566
d D 7.7 90/04/16 18:44:55 sklower 8 7
c was freeing iso_pcb's with wrong type
e
s 00016/00016/00551
d D 7.6 90/01/17 00:04:24 sklower 7 6
c mark version to ship to nist; changes for cltp & some fixes
e
s 00014/00045/00553
d D 7.5 89/08/29 13:44:28 sklower 6 5
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00013/00000/00585
d D 7.4 89/07/19 23:34:59 sklower 5 3
c change iso_pcbconnect so that specifying a null nsap as target
c means the first configured iso interface, as in the inet case.
e
s 00011/00000/00585
d R 7.4 89/07/19 23:23:24 sklower 4 3
c change iso_pcbconnect so that connecting to null nsap means first iso nsap on the local machine.
e
s 00000/00001/00585
d D 7.3 89/05/05 00:27:48 mckusick 3 2
c get rid of unneeded include's
e
s 00160/00199/00426
d D 7.2 89/04/22 11:54:19 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00625/00000/00000
d D 7.1 88/12/14 15:29:46 sklower 1 0
c date and time created 88/12/14 15:29:46 by sklower
e
u
U
t
T
I 10
/*-
D 16
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
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
 * $Header: iso_pcb.c,v 4.5 88/06/29 14:59:56 hagens Exp $
 * $Source: /usr/argo/sys/netiso/RCS/iso_pcb.c,v $
I 5
D 6
 *	%W% (Berkeley) %G%
E 6
I 6
D 7
 *	%W% (Berkeley) %G% *
E 7
I 7
D 10
 *	%W% (Berkeley) %G%
E 10
E 7
E 6
E 5
 *
 * Iso address family net-layer(s) pcb stuff. NEH 1/29/87
 */
I 5
D 10

E 5
#ifndef lint
static char *rcsid = "$Header: iso_pcb.c,v 4.5 88/06/29 14:59:56 hagens Exp $";
#endif
E 10

#ifdef ISO

D 14
#include "param.h"
#include "systm.h"
D 3
#include "dir.h"
E 3
D 11
#include "user.h"
E 11
#include "mbuf.h"
D 2
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../netiso/argo_debug.h"
#include "../netiso/iso.h"
#include "../netiso/clnp.h"
E 2
I 2
#include "socket.h"
#include "socketvar.h"
I 11
#include "errno.h"
E 14
I 14
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
E 14

E 11
D 14
#include "argo_debug.h"
#include "iso.h"
#include "clnp.h"
E 2
#include "../netinet/in_systm.h"
#include "../net/if.h"
#include "../net/route.h"
D 2
#include "../netiso/iso_pcb.h"
#include "../netiso/iso_var.h"
E 2
I 2
#include "iso_pcb.h"
#include "iso_var.h"
E 2
#include "protosw.h"
E 14
I 14
#include <netiso/argo_debug.h>
#include <netiso/iso.h>
#include <netiso/clnp.h>
#include <netinet/in_systm.h>
#include <net/if.h>
#include <net/route.h>
#include <netiso/iso_pcb.h>
#include <netiso/iso_var.h>
#include <sys/protosw.h>
E 14

I 9
#ifdef TPCONS
D 14
#include "../netccitt/x25.h"
#include "../netccitt/pk.h"
#include "../netccitt/pk_var.h"
E 14
I 14
#include <netccitt/x25.h>
#include <netccitt/pk.h>
#include <netccitt/pk_var.h>
E 14
#endif

E 9
#define PCBNULL (struct isopcb *)0
struct	iso_addr zeroiso_addr = {
	0
};


/*
 * FUNCTION:		iso_pcballoc
 *
 * PURPOSE:			creates an isopcb structure in an mbuf,
 *					with socket (so), and 
 *					puts it in the queue with head (head)
 *
 * RETURNS:			0 if OK, ENOBUFS if can't alloc the necessary mbuf
 */
int
iso_pcballoc(so, head)
	struct socket *so;
	struct isopcb *head;
{
D 2
	struct mbuf *m;
E 2
	register struct isopcb *isop;

	IFDEBUG(D_ISO)
		printf("iso_pcballoc(so 0x%x)\n", so);
	ENDDEBUG
D 2
	m = m_getclr(M_DONTWAIT, MT_PCB);
	if (m == NULL)
E 2
I 2
	MALLOC(isop, struct isopcb *, sizeof(*isop), M_PCB, M_NOWAIT);
	if (isop == NULL)
E 2
		return ENOBUFS;
D 2
	isop = mtod(m, struct isopcb *);
E 2
I 2
	bzero((caddr_t)isop, sizeof(*isop));
E 2
	isop->isop_head = head;
	isop->isop_socket = so;
	insque(isop, head);
D 9
	so->so_pcb = (caddr_t)isop;
E 9
I 9
	if (so)
		so->so_pcb = (caddr_t)isop;
E 9
	return 0;
}
	
/*
 * FUNCTION:		iso_pcbbind
 *
 * PURPOSE:			binds the address given in *(nam) to the socket
 *					specified by the isopcb in *(isop)
 *					If the given address is zero, it makes sure the
 *					address isn't already in use and if it's got a network
 *					portion, we look for an interface with that network
 *					address.  If the address given is zero, we allocate
 *					a port and stuff it in the (nam) structure.
 *
 * RETURNS:			errno E* or 0 if ok.
 *
 * SIDE EFFECTS:	increments head->isop_lport if it allocates a port #
 *
 * NOTES:			
 */
I 2
#define	satosiso(sa)	((struct sockaddr_iso *)(sa))
E 2
int
iso_pcbbind(isop, nam)
	register struct isopcb *isop;
	struct mbuf *nam;
{
	register struct isopcb *head = isop->isop_head;
	register struct sockaddr_iso *siso;
D 2
	struct ifaddr *ia;
	u_short suf = 0;
E 2
I 2
	struct iso_ifaddr *ia;
	union {
		char data[2];
		u_short s;
	} suf;
E 2

	IFDEBUG(D_ISO)
		printf("iso_pcbbind(isop 0x%x, nam 0x%x)\n", isop, nam);
	ENDDEBUG
I 2
	suf.s = 0;
E 2
	if (iso_ifaddr == 0) /* any interfaces attached? */
		return EADDRNOTAVAIL;
D 2
	if (isop->isop_lport)  /* already bound */
E 2
I 2
	if (isop->isop_laddr)  /* already bound */
E 2
		return EADDRINUSE;
D 2
	if(nam == (struct mbuf *)0)
E 2
I 2
	if(nam == (struct mbuf *)0) {
		isop->isop_laddr = &isop->isop_sladdr;
D 6
		isop->isop_sladdr.siso_tsuffixlen = 2;
		isop->isop_sladdr.siso_nlen = 0;
		isop->isop_sladdr.siso_family = AF_ISO;
E 6
		isop->isop_sladdr.siso_len = sizeof(struct sockaddr_iso);
I 6
		isop->isop_sladdr.siso_family = AF_ISO;
		isop->isop_sladdr.siso_tlen = 2;
		isop->isop_sladdr.siso_nlen = 0;
		isop->isop_sladdr.siso_slen = 0;
		isop->isop_sladdr.siso_plen = 0;
E 6
E 2
		goto noname;
I 2
	}
E 2
	siso = mtod(nam, struct sockaddr_iso *);
	IFDEBUG(D_ISO)
		printf("iso_pcbbind(name len 0x%x)\n", nam->m_len);
		printf("The address is %s\n", clnp_iso_addrp(&siso->siso_addr));
	ENDDEBUG
	/*
	 * We would like sort of length check but since some OSI addrs
	 * do not have fixed length, we can't really do much.
	 * The ONLY thing we can say is that an osi addr has to have
	 * at LEAST an afi and one more byte and had better fit into
	 * a struct iso_addr.
	 * However, in fact the size of the whole thing is a struct
	 * sockaddr_iso, so probably this is what we should check for.
	 */
D 2
	if( (nam->m_len < 2) || (nam->m_len > sizeof(struct sockaddr_iso))) {
E 2
I 2
	if( (nam->m_len < 2) || (nam->m_len < siso->siso_len)) {
E 2
			return ENAMETOOLONG;
	}
D 2
	suf = siso->siso_tsuffix;

	if (bcmp(&siso->siso_addr,&zeroiso_addr, 1)) {
E 2
I 2
D 6
	if (siso->siso_tsuffixlen) {
E 6
I 6
D 13
	if (siso->siso_tlen) {
E 6
			register char *cp = TSEL(siso);
			suf.data[0] = cp[0];
			suf.data[1] = cp[1];
	}
E 13
	if (siso->siso_nlen) {
E 2
		/* non-zero net addr- better match one of our interfaces */
		IFDEBUG(D_ISO)
			printf("iso_pcbbind: bind to NOT zeroisoaddr\n");
		ENDDEBUG
D 2
		siso->siso_tsuffix = 0;		/* yech... */
		/* PHASE 2: this call is ok */
		if ((ia = ifa_ifwithaddr((struct sockaddr *)siso))
											== (struct ifaddr *)0)
E 2
I 2
		for (ia = iso_ifaddr; ia; ia = ia->ia_next) 
D 17
			if (SAME_ISOADDR(siso, &ia->ia_addr))
E 17
I 17
			if (SAME_ISOIFADDR(siso, &ia->ia_addr))
E 17
				break;
		if (ia == 0)
E 2
			return EADDRNOTAVAIL;
D 2
		/* copy to the inpcb */
		bcopy( (caddr_t)&((struct sockaddr_iso *)&(ia->ifa_addr))->siso_addr,
			(caddr_t)&(isop->isop_laddr.siso_addr), 
			sizeof(struct sockaddr_iso) );
		isop->isop_laddr.siso_tsuffix = suf;
		/* copy also to the nam parameter */
		bcopy( (caddr_t)&(isop->isop_laddr.siso_addr),
			(caddr_t)&(siso->siso_addr), sizeof(struct sockaddr_iso));
		siso->siso_tsuffix = suf;
E 2
	} 
D 2
	if (suf) {
		if((suf < ISO_PORT_RESERVED) && (u.u_uid != 0))
E 2
I 2
	if (siso->siso_len <= sizeof (isop->isop_sladdr)) {
		isop->isop_laddr = &isop->isop_sladdr;
	} else {
		if ((nam = m_copy(nam, 0, (int)M_COPYALL)) == 0)
			return ENOBUFS;
		isop->isop_laddr = mtod(nam, struct sockaddr_iso *);
	}
	bcopy((caddr_t)siso, (caddr_t)isop->isop_laddr, siso->siso_len);
D 7
	if (suf.s) {
E 7
I 7
D 13
	if (suf.s || siso->siso_tlen != 2) {
E 7
D 6
		if((suf.s < ISO_PORT_RESERVED) && (siso->siso_tsuffixlen <= 2) &&
E 6
I 6
		if((suf.s < ISO_PORT_RESERVED) && (siso->siso_tlen <= 2) &&
E 13
I 13
	if (siso->siso_tlen == 0)
		goto noname;
	if ((isop->isop_socket->so_options & SO_REUSEADDR) == 0 &&
		iso_pcblookup(head, 0, (caddr_t)0, isop->isop_laddr))
		return EADDRINUSE;
	if (siso->siso_tlen <= 2) {
		bcopy(TSEL(siso), suf.data, sizeof(suf.data));
		suf.s = ntohs(suf.s);
		if((suf.s < ISO_PORT_RESERVED) &&
E 13
E 6
D 11
		   (u.u_uid != 0))
E 11
I 11
		   (isop->isop_socket->so_state && SS_PRIV) == 0)
E 11
E 2
			return EACCES;
D 13
		if ((isop->isop_socket->so_options & SO_REUSEADDR) == 0 &&
D 2
			iso_pcblookup(head, 0, &(isop->isop_laddr.siso_addr), suf, 0) )
E 2
I 2
			iso_pcblookup(head, 0, (caddr_t)0, isop->isop_laddr))
E 2
			return EADDRINUSE;
E 13
D 2
	}
	/* copy the if addr to the result (siso) and to the isopcb */
E 2
I 2
	} else {
		register char *cp;
E 2
noname:
I 2
		cp = TSEL(isop->isop_laddr);
I 17
D 18
		isop->isop_laddr.siso_tlen = 2;
E 18
I 18
		isop->isop_laddr->siso_tlen = 2;
E 18
E 17
E 2
	IFDEBUG(D_ISO)
		printf("iso_pcbbind noname\n");
	ENDDEBUG
D 2
	if (suf == 0)
E 2
		do {
			if (head->isop_lport++ < ISO_PORT_RESERVED ||
			    head->isop_lport > ISO_PORT_USERRESERVED)
				head->isop_lport = ISO_PORT_RESERVED;
D 2
			suf = head->isop_lport;
		} while (iso_pcblookup(head, 0, &(isop->isop_laddr.siso_addr), suf, 0));
	isop->isop_lport = suf;
E 2
I 2
D 13
			suf.s = head->isop_lport;
E 13
I 13
			suf.s = htons(head->isop_lport);
E 13
			cp[0] = suf.data[0];
			cp[1] = suf.data[1];
		} while (iso_pcblookup(head, 0, (caddr_t)0, isop->isop_laddr));
	}
E 2
	IFDEBUG(D_ISO)
		printf("iso_pcbbind returns 0, suf 0x%x\n", suf);
	ENDDEBUG
	return 0;
}
D 2

E 2
/*
 * FUNCTION:		iso_pcbconnect
 *
 * PURPOSE:			Make the isopcb (isop) look like it's connected.
 *					In other words, give it the peer address given in 
 *					the mbuf * (nam).   Make sure such a combination
 *					of local, peer addresses doesn't already exist
 *					for this protocol.  Internet mentality prevails here,
 *					wherein a src,dst pair uniquely identifies a connection.
 * 					Both net address and port must be specified in argument 
 *					(nam).
 * 					If we don't have a local address for this socket yet, 
 *					we pick one by calling iso_pcbbind().
 *
 * RETURNS:			errno E* or 0 if ok.
 *
 * SIDE EFFECTS:	Looks up a route, which may cause one to be left
 *					in the isopcb.
 *
 * NOTES:			
 */
D 2
#define	satosiso(sa)	((struct sockaddr_iso *)(sa))

E 2
int
iso_pcbconnect(isop, nam)
D 2
	struct isopcb *isop;
E 2
I 2
	register struct isopcb *isop;
E 2
	struct mbuf *nam;
{
D 2
	struct	ifnet 					*ifp = (struct ifnet *)0;
	struct sockaddr_iso				ifaddr;
E 2
	register struct sockaddr_iso	*siso = mtod(nam, struct sockaddr_iso *);
D 2
	int								local_zero = 0;
E 2
I 2
	int								local_zero, error = 0;
	struct iso_ifaddr 				*ia;
E 2

	IFDEBUG(D_ISO)
D 2
		printf(
	"iso_pcbconnect(isop 0x%x sock 0x%x nam 0x%x nam->m_len 0x%x), addr:\n", 
			isop, isop->isop_socket, nam, nam->m_len);
E 2
I 2
		printf("iso_pcbconnect(isop 0x%x sock 0x%x nam 0x%x",
					isop, isop->isop_socket, nam);
		printf("nam->m_len 0x%x), addr:\n", nam->m_len);
E 2
		dump_isoaddr(siso);
	ENDDEBUG
D 2
	if (nam->m_len > sizeof (*siso))
		return ENAMETOOLONG; /* not great but better than EINVAL! */
E 2
I 2
	if (nam->m_len < siso->siso_len)
		return EINVAL; 
E 2
	if (siso->siso_family != AF_ISO)
		return EAFNOSUPPORT;
I 5
	if (siso->siso_nlen == 0) {
		if (ia = iso_ifaddr) {
			int nlen = ia->ia_addr.siso_nlen;
			ovbcopy(TSEL(siso), nlen + TSEL(siso),
D 6
				siso->siso_tsuffixlen + siso->siso_ssuffixlen);
E 6
I 6
				siso->siso_plen + siso->siso_tlen + siso->siso_slen);
E 6
			bcopy((caddr_t)&ia->ia_addr.siso_addr,
				  (caddr_t)&siso->siso_addr, nlen + 1);
			/* includes siso->siso_nlen = nlen; */
		} else
			return EADDRNOTAVAIL;
	}
E 5
D 2
#ifdef notdef
	/* removed for the sake of extended tsels - 
	 * user may setsockopt for extended tsel (foreign) and then
	 * connect to nsap w/ tsuffix zero 
E 2
I 2
	/*
	 * Local zero means either not bound, or bound to a TSEL, but no
	 * particular local interface.  So, if we want to send somebody
	 * we need to choose a return address.
E 2
	 */
D 2
	if (siso->siso_tsuffix == 0)
		return EADDRNOTAVAIL;
	local_zero = iso_addrmatch1(&(isop->isop_laddr.siso_addr), &zeroiso_addr); 
#endif notdef
	local_zero = !bcmp(&(isop->isop_laddr.siso_addr), &zeroiso_addr, 1); 

#ifdef	PHASEONE
E 2
I 2
	local_zero = 
		((isop->isop_laddr == 0) || (isop->isop_laddr->siso_nlen == 0));
E 2
	if (local_zero) {
D 2
		/*
		 *	We need to get the local nsap address.
		 *	First, route to the destination. This will provide us with
		 *	an ifp. Second, determine which local address linked on
		 *	that ifp is appropriate
		 */
		struct sockaddr_iso	*first_hop;		/* filled by clnp_route */
		struct ifnet	*ifp;			/* filled by clnp_route */
		int				err;
		struct iso_addr	*localaddr;
E 2
I 2
		int flags;
E 2

D 2
		if (err = clnp_route(&siso->siso_addr, &isop->isop_route, /* flags */0,
			&first_hop, &ifp))
			return(err);
		
		/* determine local address based upon ifp */
		if ((localaddr = clnp_srcaddr(ifp, &first_hop->siso_addr)) == NULL)
			return(ENETUNREACH);

		ifaddr.siso_family = AF_ISO;
		ifaddr.siso_addr = *localaddr;

		if (isop->isop_lport == 0)
			(void)iso_pcbbind(isop, (struct mbuf *)0);
		isop->isop_laddr = ifaddr;
	}
#else
	if (local_zero) {
		struct iso_ifaddr 		*ia;
		register struct route *ro;

E 2
		IFDEBUG(D_ISO)
			printf("iso_pcbconnect localzero 1\n");
		ENDDEBUG
D 2
		ia = (struct iso_ifaddr *)0;
E 2
		/* 
		 * If route is known or can be allocated now,
		 * our src addr is taken from the i/f, else punt.
		 */
D 2
		ro = &isop->isop_route;
E 2
I 2
		flags = isop->isop_socket->so_options & SO_DONTROUTE;
		if (error = clnp_route(&siso->siso_addr, &isop->isop_route, flags,
						(struct sockaddr **)0, &ia))
			return error;
E 2
		IFDEBUG(D_ISO)
D 2
			printf("iso_pcbconnect rtalloc 1.1, ro->ro_rt 0x%x\n",
				ro->ro_rt);
E 2
I 2
			printf("iso_pcbconnect localzero 2, ro->ro_rt 0x%x",
				isop->isop_route.ro_rt);
			printf(" ia 0x%x\n", ia);
E 2
		ENDDEBUG
D 2
		if (ro->ro_rt && ! iso_addrmatch1( &(satosiso(&ro->ro_dst)->siso_addr), 
					&siso->siso_addr)) {
			RTFREE(ro->ro_rt);
			ro->ro_rt = (struct rtentry *)0;
		}
		/*
		 *	TODO: it seems this code has a lot in common with clnp_route.
		 *	Maybe they could be combined? (RAH)
		 */
		if ((isop->isop_socket->so_options & SO_DONTROUTE) == 0 && /*XXX*/
		    (ro->ro_rt == (struct rtentry *)0 ||
		    (ifp = ro->ro_rt->rt_ifp) == (struct ifnet *)0)) {
				/* No route yet, so try to acquire one */
				ro->ro_dst.sa_family = AF_ISO;
				((struct sockaddr_iso *) &ro->ro_dst)->siso_addr =
					siso->siso_addr;
				rtalloc(ro);
				IFDEBUG(D_ISO)
					printf("iso_pcbconnect rtalloc 1.5, ro->ro_rt 0x%x\n",
						ro->ro_rt);
					if (ro->ro_rt != NULL) {
						printf("ro->ro_rt->rt_refcnt %d\n",
							ro->ro_rt->rt_refcnt);
						printf("rt entry rt_gateway (as sockaddr):\n");
						dump_buf(&ro->ro_rt->rt_gateway, 
							sizeof (struct sockaddr));
					}
				ENDDEBUG
				/*
				 * If we found a route, use the address
				 * corresponding to the outgoing interface
				 * unless it is the loopback (in case a route
				 * to our address on another net goes to loopback).
				 *
				 *	We must check to use the address that is of the
				 *	same type (in the case where the interface has more
				 *	than one type associated with it). (ie ecn0 has
				 *	both t37 and osinet addresses.
				 */
				if (ro->ro_rt && (ifp = ro->ro_rt->rt_ifp) &&
					(ifp->if_flags & IFF_LOOPBACK) == 0)
					for (ia = iso_ifaddr; ia; ia = ia->ia_next) {
						struct iso_addr *isoap = &IA_SIS(ia)->siso_addr;

						IFDEBUG(D_ISO)
							printf("iso_pcbconnect: ia x%x yields: %s\n",
								ia, clnp_iso_addrp(isoap));
						ENDDEBUG

						if ((ia->ia_ifp == ifp) &&
							(iso_eqtype(&siso->siso_addr, isoap)))
							break;
					}
		}
		IFDEBUG(D_ISO)
			printf("iso_pcbconnect localzero 2: ia x%x\n", ia);
		ENDDEBUG
		if (ia == 0) {
			ia = (struct iso_ifaddr *)
			    ifa_ifwithdstaddr((struct sockaddr *)siso);
			if (ia == 0)
				ia = iso_iaonnetof(siso);
			if (ia == 0)
				return EADDRNOTAVAIL;
		}
		ifaddr = *(struct sockaddr_iso *)&ia->ia_addr;
E 2
	}
	IFDEBUG(D_ISO)
		printf("in iso_pcbconnect before lookup isop 0x%x isop->sock 0x%x\n", 
			isop, isop->isop_socket);
	ENDDEBUG
	if (local_zero) {
D 2
		if (isop->isop_lport == 0)
E 2
I 2
		int nlen, tlen, totlen; caddr_t oldtsel, newtsel;
		siso = isop->isop_laddr;
D 6
		if (siso == 0 || siso->siso_tsuffixlen == 0)
E 6
I 6
		if (siso == 0 || siso->siso_tlen == 0)
E 6
E 2
			(void)iso_pcbbind(isop, (struct mbuf *)0);
D 2
		isop->isop_laddr.siso_addr = ifaddr.siso_addr;
		isop->isop_laddr.siso_family = AF_ISO;
E 2
I 2
		/*
		 * Here we have problem of squezeing in a definite network address
		 * into an existing sockaddr_iso, which in fact may not have room
		 * for it.  This gets messy.
		 */
		siso = isop->isop_laddr;
		oldtsel = TSEL(siso);
D 6
		tlen = siso->siso_tsuffixlen;
E 6
I 6
		tlen = siso->siso_tlen;
E 6
		nlen = ia->ia_addr.siso_nlen;
		totlen = tlen + nlen + _offsetof(struct sockaddr_iso, siso_data[0]);
		if ((siso == &isop->isop_sladdr) &&
			(totlen > sizeof(isop->isop_sladdr))) {
			struct mbuf *m = m_get(MT_SONAME, M_DONTWAIT);
			if (m == 0)
					return ENOBUFS;
			m->m_len = totlen;
			isop->isop_laddr = siso = mtod(m, struct sockaddr_iso *);
		}
		siso->siso_nlen = ia->ia_addr.siso_nlen;
		newtsel = TSEL(siso);
		ovbcopy(oldtsel, newtsel, tlen);
		bcopy(ia->ia_addr.siso_data, siso->siso_data, nlen);
D 6
		siso->siso_tsuffixlen = tlen;
E 6
I 6
		siso->siso_tlen = tlen;
E 6
		siso->siso_family = AF_ISO;
		siso->siso_len = totlen;
		siso = mtod(nam, struct sockaddr_iso *);
E 2
	}
D 2
#endif	PHASEONE
E 2
	IFDEBUG(D_ISO)
		printf("in iso_pcbconnect before bcopy isop 0x%x isop->sock 0x%x\n", 
			isop, isop->isop_socket);
	ENDDEBUG
D 2
	bcopy((caddr_t) &(siso->siso_addr), (caddr_t) &(isop->isop_faddr.siso_addr),
		sizeof(struct iso_addr));
E 2
I 2
	/*
	 * If we had to allocate space to a previous big foreign address,
	 * and for some reason we didn't free it, we reuse it knowing
	 * that is going to be big enough, as sockaddrs are delivered in
	 * 128 byte mbufs.
	 * If the foreign address is small enough, we use default space;
	 * otherwise, we grab an mbuf to copy into.
	 */
	if (isop->isop_faddr == 0 || isop->isop_faddr == &isop->isop_sfaddr) {
		if (siso->siso_len <= sizeof(isop->isop_sfaddr))
			isop->isop_faddr = &isop->isop_sfaddr;
		else {
			struct mbuf *m = m_get(MT_SONAME, M_DONTWAIT);
			if (m == 0)
				return ENOBUFS;
			isop->isop_faddr = mtod(m, struct sockaddr_iso *);
		}
	}
	bcopy((caddr_t)siso, (caddr_t)isop->isop_faddr, siso->siso_len);
E 2
	IFDEBUG(D_ISO)
		printf("in iso_pcbconnect after bcopy isop 0x%x isop->sock 0x%x\n", 
			isop, isop->isop_socket);
D 2
	ENDDEBUG
	isop->isop_faddr.siso_family = AF_ISO;
	isop->isop_fport = siso->siso_tsuffix;
	IFDEBUG(D_ISO)
		printf("in iso_pcbconnect end isop 0x%x isop->sock 0x%x\n", 
			isop, isop->isop_socket);
E 2
		printf("iso_pcbconnect connected to addr:\n");
D 2
		dump_isoaddr(&isop->isop_faddr);
E 2
I 2
		dump_isoaddr(isop->isop_faddr);
E 2
		printf("iso_pcbconnect end: src addr:\n");
D 2
		dump_isoaddr(&isop->isop_laddr);
E 2
I 2
		dump_isoaddr(isop->isop_laddr);
E 2
	ENDDEBUG
	return 0;
}

/*
 * FUNCTION:		iso_pcbdisconnect()
 *
 * PURPOSE:			washes away the peer address info so the socket
 *					appears to be disconnected.
 *					If there's no file descriptor associated with the socket
 *					it detaches the pcb.
 *
 * RETURNS:			Nada.
 *
 * SIDE EFFECTS:	May detach the pcb.
 *
 * NOTES:			
 */
void
iso_pcbdisconnect(isop)
	struct isopcb *isop;
{
	void iso_pcbdetach();
I 7
	register struct sockaddr_iso *siso;
E 7

	IFDEBUG(D_ISO)
		printf("iso_pcbdisconnect(isop 0x%x)\n", isop);
	ENDDEBUG
D 2
	isop->isop_laddr.siso_addr = zeroiso_addr;
	isop->isop_fport = 0;
E 2
I 2
	/*
	 * Preserver binding infnormation if already bound.
	 */
D 7
	if (isop->isop_laddr && isop->isop_laddr->siso_nlen)
		isop->isop_laddr->siso_nlen = 0;
E 7
I 7
	if ((siso = isop->isop_laddr) && siso->siso_nlen && siso->siso_tlen) {
		caddr_t otsel = TSEL(siso);
		siso->siso_nlen = 0;
		ovbcopy(otsel, TSEL(siso), siso->siso_tlen);
	}
E 7
	if (isop->isop_faddr && isop->isop_faddr != &isop->isop_sfaddr)
		m_freem(dtom(isop->isop_faddr));
	isop->isop_faddr = 0;
E 2
	if (isop->isop_socket->so_state & SS_NOFDREF)
		iso_pcbdetach(isop);
}

/*
 * FUNCTION:		iso_pcbdetach
 *
 * PURPOSE:			detach the pcb at *(isop) from it's socket and free
 *					the mbufs associated with the pcb..
 *					Dequeues (isop) from its head.
 *
 * RETURNS:			Nada.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
void
iso_pcbdetach(isop)
	struct isopcb *isop;
{
	struct socket *so = isop->isop_socket;

	IFDEBUG(D_ISO)
		printf("iso_pcbdetach(isop 0x%x socket 0x%x so 0x%x)\n", 
			isop, isop->isop_socket, so);
	ENDDEBUG
D 9
	if (so ) { /* in the x.25 domain, we sometimes have no socket */
E 9
I 9
#ifdef TPCONS
D 12
	if (isop->isop_refcnt) {
E 12
I 12
	if (isop->isop_chan) {
E 12
		register struct pklcd *lcp = (struct pklcd *)isop->isop_chan;
		if (--isop->isop_refcnt > 0)
			return;
D 12
		if (lcp && lcp->lcd_state == DATA_TRANSFER)
E 12
I 12
		if (lcp && lcp->lcd_state == DATA_TRANSFER) {
			lcp->lcd_upper = 0;
			lcp->lcd_upnext = 0;
E 12
			pk_disconnect(lcp);
I 12
		}
E 12
		isop->isop_chan = 0;
	}
#endif
	if (so) { /* in the x.25 domain, we sometimes have no socket */
E 9
		so->so_pcb = 0;
		sofree(so); 
	}
	IFDEBUG(D_ISO)
		printf("iso_pcbdetach 2 \n");
	ENDDEBUG
	if (isop->isop_options)
		(void)m_free(isop->isop_options);
	IFDEBUG(D_ISO)
		printf("iso_pcbdetach 3 \n");
	ENDDEBUG
	if (isop->isop_route.ro_rt)
		rtfree(isop->isop_route.ro_rt);
	IFDEBUG(D_ISO)
		printf("iso_pcbdetach 3.1\n");
	ENDDEBUG
	if (isop->isop_clnpcache != NULL) {
		struct clnp_cache *clcp =
			mtod(isop->isop_clnpcache, struct clnp_cache *);
		IFDEBUG(D_ISO)
			printf("iso_pcbdetach 3.2: clcp 0x%x freeing clc_hdr x%x\n", 
				clcp, clcp->clc_hdr);
		ENDDEBUG
		if (clcp->clc_hdr != NULL)
			m_free(clcp->clc_hdr);
		IFDEBUG(D_ISO)
			printf("iso_pcbdetach 3.3: freeing cache x%x\n", 
				isop->isop_clnpcache);
		ENDDEBUG
		m_free(isop->isop_clnpcache);
	}
	IFDEBUG(D_ISO)
		printf("iso_pcbdetach 4 \n");
	ENDDEBUG
	remque(isop);
	IFDEBUG(D_ISO)
		printf("iso_pcbdetach 5 \n");
	ENDDEBUG
D 2
	(void) m_free(dtom(isop));
E 2
I 2
	if (isop->isop_laddr && (isop->isop_laddr != &isop->isop_sladdr))
		m_freem(dtom(isop->isop_laddr));
D 8
	free((caddr_t)isop, M_IFADDR);
E 8
I 8
	free((caddr_t)isop, M_PCB);
E 8
E 2
}

D 6
#ifdef notdef
/* NEEDED? */
void
iso_setsockaddr(isop, nam)
	register struct isopcb *isop;
	struct mbuf *nam;
{
	register struct sockaddr_iso *siso = mtod(nam, struct sockaddr_iso *);
	
	nam->m_len = sizeof (*siso);
	siso = mtod(nam, struct sockaddr_iso *);
	bzero((caddr_t)siso, sizeof (*siso));
	siso->siso_family = AF_ISO;
	siso->siso_tsuffix = isop->isop_lport;
	siso->siso_addr = isop->isop_laddr.siso_addr;
}
E 6

D 6
/* NEEDED? */
void
iso_setpeeraddr(isop, nam)
	register struct isopcb *isop;
	struct mbuf *nam;
{
	register struct sockaddr_iso *siso = mtod(nam, struct sockaddr_iso *);
	
	nam->m_len = sizeof (*siso);
	siso = mtod(nam, struct sockaddr_iso *);
	bzero((caddr_t)siso, sizeof (*siso));
	siso->siso_family = AF_ISO;
	siso->siso_tsuffix = isop->isop_fport;
	siso->siso_addr = isop->isop_faddr.siso_addr;
}
#endif notdef

E 6
/*
 * FUNCTION:		iso_pcbnotify
 *
 * PURPOSE:			notify all connections in this protocol's queue (head)
 *					that have peer address (dst) of the problem (errno)
 *					by calling (notify) on the connections' isopcbs.
 *
 * RETURNS:			Rien.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			(notify) is called at splimp!
 */
void
D 7
iso_pcbnotify(head, dst, errno, notify)
E 7
I 7
iso_pcbnotify(head, siso, errno, notify)
E 7
	struct isopcb *head;
D 7
	register struct iso_addr *dst;
E 7
I 7
	register struct sockaddr_iso *siso;
E 7
	int errno, (*notify)();
{
D 7
	register struct isopcb *isop, *oisop;
E 7
I 7
	register struct isopcb *isop;
E 7
	int s = splimp();

	IFDEBUG(D_ISO)
		printf("iso_pcbnotify(head 0x%x, notify 0x%x) dst:\n", head, notify);
	ENDDEBUG
D 7
	for (isop = head->isop_next; isop != head;) {
D 2
		if (!iso_addrmatch1(&(isop->isop_faddr.siso_addr), dst) ||
E 2
I 2
		if (!iso_addrmatch1(&(isop->isop_faddr->siso_addr), dst) ||
E 2
		    isop->isop_socket == 0) {
E 7
I 7
	for (isop = head->isop_next; isop != head; isop = isop->isop_next) {
		if (isop->isop_socket == 0 || isop->isop_faddr == 0 ||
			!SAME_ISOADDR(siso, isop->isop_faddr)) {
E 7
			IFDEBUG(D_ISO)
				printf("iso_pcbnotify: CONTINUE isop 0x%x, sock 0x%x\n" ,
					isop, isop->isop_socket);
D 7
				printf("addrmatch cmp'd with (0x%x):\n",
D 2
					&(isop->isop_faddr.siso_addr));
				dump_isoaddr(&isop->isop_faddr);
E 2
I 2
					&(isop->isop_faddr->siso_addr));
E 7
I 7
				printf("addrmatch cmp'd with (0x%x):\n", isop->isop_faddr);
E 7
				dump_isoaddr(isop->isop_faddr);
E 2
			ENDDEBUG
D 7
			isop = isop->isop_next;
E 7
			continue;
		}
		if (errno) 
			isop->isop_socket->so_error = errno;
D 7
		oisop = isop;
		isop = isop->isop_next;
E 7
		if (notify)
D 7
			(*notify)(oisop);
E 7
I 7
			(*notify)(isop);
E 7
	}
	splx(s);
	IFDEBUG(D_ISO)
		printf("END OF iso_pcbnotify\n" );
	ENDDEBUG
}


/*
 * FUNCTION:		iso_pcblookup
 *
 * PURPOSE:			looks for a given combination of (faddr), (fport),
 *					(lport), (laddr) in the queue named by (head).
 *					Argument (flags) is ignored.
 *
 * RETURNS:			ptr to the isopcb if it finds a connection matching
 *					these arguments, o.w. returns zero.
 *
 * SIDE EFFECTS:	
 *
 * NOTES:			
 */
struct isopcb *
D 2
iso_pcblookup(head, fport, laddr, lport, flags)
E 2
I 2
iso_pcblookup(head, fportlen, fport, laddr)
E 2
	struct isopcb *head;
D 2
	struct iso_addr *laddr;
	u_short fport, lport;
	int flags;
E 2
I 2
	register struct sockaddr_iso *laddr;
	caddr_t fport;
	int fportlen;
E 2
{
	register struct isopcb *isop;
I 2
	register caddr_t lp = TSEL(laddr);
D 6
	unsigned int llen = laddr->siso_tsuffixlen;
E 6
I 6
	unsigned int llen = laddr->siso_tlen;
E 6
E 2

	IFDEBUG(D_ISO)
D 2
		printf("iso_pcblookup(head 0x%x lport 0x%x fport 0x%x)\n", 
			head, lport, fport);
E 2
I 2
		printf("iso_pcblookup(head 0x%x laddr 0x%x fport 0x%x)\n", 
			head, laddr, fport);
E 2
	ENDDEBUG
	for (isop = head->isop_next; isop != head; isop = isop->isop_next) {
D 2
#ifdef notdef
	/*
	 * This should be changed to do bcmp on lsuffix in the tpcb instead
	 * since we should be ignoring the lport concept.
	 */
#endif notdef
		if (isop->isop_lport != lport)
E 2
I 2
		if (isop->isop_laddr == 0 || isop->isop_laddr == laddr)
E 2
			continue;
D 2
		if (isop->isop_fport != fport)
E 2
I 2
D 6
		if (isop->isop_laddr->siso_tsuffixlen != llen)
E 6
I 6
		if (isop->isop_laddr->siso_tlen != llen)
E 6
E 2
			continue;
I 2
		if (bcmp(lp, TSEL(isop->isop_laddr), llen))
			continue;
		if (fportlen && isop->isop_faddr &&
			bcmp(fport, TSEL(isop->isop_faddr), (unsigned)fportlen))
			continue;
E 2
		/*	PHASE2
		 *	addrmatch1 should be iso_addrmatch(a, b, mask)
		 *	where mask is taken from isop->isop_laddrmask (new field)
		 *	isop_lnetmask will also be available in isop
D 2
		 */
E 2
		if (laddr != &zeroiso_addr &&
			!iso_addrmatch1(laddr, &(isop->isop_laddr.siso_addr)))
I 2
			continue;
		*/
		if (laddr->siso_nlen && (!SAME_ISOADDR(laddr, isop->isop_laddr)))
E 2
			continue;
		return (isop);
	}
	return (struct isopcb *)0;
}
D 15
#endif ISO
E 15
I 15
#endif /* ISO */
E 15
E 1
