h62874
s 00002/00002/00085
d D 8.1 93/06/10 23:19:46 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00086
d D 7.6 93/02/25 16:55:14 sklower 6 5
c quick hack for TUBA
e
s 00009/00001/00077
d D 7.5 91/05/06 19:24:08 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00076
d D 7.4 91/01/09 15:42:12 sklower 4 3
c first version to integrate to UBC X.25 (compiles only).
e
s 00001/00002/00077
d D 7.3 89/08/29 13:44:32 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00027/00009/00052
d D 7.2 89/04/22 11:54:22 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00061/00000/00000
d D 7.1 88/12/14 15:29:47 sklower 1 0
c date and time created 88/12/14 15:29:47 by sklower
e
u
U
t
T
I 5
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
/* $Header: iso_pcb.h,v 4.3 88/06/29 15:00:01 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/iso_pcb.h,v $ */
I 3
D 5
/*	%W% (Berkeley) %G% */
E 5
E 3

#define	MAXX25CRUDLEN	16	/* 16 bytes of call request user data */

/*
 * Common structure pcb for argo protocol implementation.
 */
struct isopcb {
	struct	isopcb			*isop_next,*isop_prev; /* pointers to other pcb's */
	struct	isopcb			*isop_head;	/* pointer back to chain of pcbs for 
								this protocol */
	struct	socket			*isop_socket;	/* back pointer to socket */
D 2
	struct	sockaddr_iso	isop_laddr;
#define isop_lport isop_laddr.siso_tsuffix
#define isop_lportlen isop_laddr.siso_tsuffixlen
	struct	sockaddr_iso	isop_faddr;
#define isop_fport isop_faddr.siso_tsuffix
#define isop_fportlen isop_faddr.siso_tsuffixlen
	struct	route			isop_route;			/* CLNP routing entry */
E 2
I 2
	struct	sockaddr_iso	*isop_laddr;
	struct	sockaddr_iso	*isop_faddr;
D 3
#define isop_lportlen isop_laddr->siso_tsuffixlen
#define isop_fportlen isop_faddr->siso_tsuffixlen
E 3
	struct	route_iso {
		struct	rtentry 	*ro_rt;
		struct	sockaddr_iso ro_dst;
	}						isop_route;			/* CLNP routing entry */
E 2
	struct	mbuf			*isop_options;		/* CLNP options */
	struct	mbuf			*isop_optindex;		/* CLNP options index */
	struct	mbuf			*isop_clnpcache;	/* CLNP cached hdr */
D 4
	u_int			isop_chanmask;		/* which ones used - max 32 supported */
	u_int			isop_negchanmask;	/* which ones used - max 32 supported */
E 4
I 4
	caddr_t					isop_chan;		/* actually struct pklcb * */
	u_short					isop_refcnt;		/* mult TP4 tpcb's -> here */
E 4
I 2
	u_short					isop_lport;			/* MISLEADLING work var */
I 6
	u_short					isop_tuba_cached;	/* for tuba address ref cnts */
E 6
E 2
	int						isop_x25crud_len;	/* x25 call request ud */
	char					isop_x25crud[MAXX25CRUDLEN];
D 2
	struct ifnet			*isop_ifp;		/* ESIS interface assoc w/sock */
E 2
I 2
	struct ifaddr			*isop_ifa;		/* ESIS interface assoc w/sock */
	struct	sockaddr_iso	isop_sladdr,		/* preallocated laddr */
							isop_sfaddr;		/* preallocated faddr */
E 2
};

D 2
#define	sotoisopcb(so)	((struct isopcb *)(so)->so_npcb)
E 2
I 2
#ifdef sotorawcb
/*
 * Common structure pcb for raw clnp protocol access.
 * Here are clnp specific extensions to the raw control block,
 * and space is allocated to the necessary sockaddrs.
 */
struct rawisopcb {
	struct	rawcb risop_rcb;		/* common control block prefix */
	int		risop_flags;			/* flags, e.g. raw sockopts */
	struct	isopcb risop_isop;		/* space for bound addresses, routes etc.*/
};
#endif

#define	sotoisopcb(so)	((struct isopcb *)(so)->so_pcb)
#define	sotorawisopcb(so)	((struct rawisopcb *)(so)->so_pcb)
E 2

#ifdef KERNEL
struct	isopcb *iso_pcblookup();
#endif
E 1
