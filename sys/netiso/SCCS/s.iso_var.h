h62356
s 00002/00002/00109
d D 8.1 93/06/10 23:20:00 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00110
d D 7.6 93/05/25 11:51:44 bostic 6 5
c trailing comment after #else or #endif
e
s 00009/00009/00102
d D 7.5 91/05/06 19:24:12 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00011/00110
d D 7.4 90/06/28 21:44:20 bostic 4 3
c new copyright notice
e
s 00001/00015/00120
d D 7.3 90/04/05 11:25:55 sklower 3 2
c remomve ISO snpac ioctl; move ia_flags to general ifaddr part
e
s 00086/00011/00049
d D 7.2 89/04/22 11:54:33 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00060/00000/00000
d D 7.1 88/12/14 15:29:51 sklower 1 0
c date and time created 88/12/14 15:29:51 by sklower
e
u
U
t
T
I 5
/*-
D 7
 * Copyright (c) 1988, 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1991, 1993
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
I 2
D 5
/*
 * Modifications,
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */
E 5
E 2

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
D 2
/* $Header: iso_var.h,v 4.2 88/06/29 15:00:08 hagens Exp $ */
/* $Source: /usr/argo/sys/netiso/RCS/iso_var.h,v $ */
E 2
I 2
/* $Header: iso_var.h,v 4.2 88/06/29 15:00:08 hagens Exp $
 * $Source: /usr/argo/sys/netiso/RCS/iso_var.h,v $
 */
E 2

/*
 *	Interface address, iso version. One of these structures is 
 *	allocated for each interface with an osi address. The ifaddr
 *	structure conatins the protocol-independent part
 *	of the structure, and is assumed to be first.
 */
struct iso_ifaddr {
	struct ifaddr		ia_ifa;		/* protocol-independent info */
I 2
#define ia_ifp		ia_ifa.ifa_ifp
E 2
D 3
	int					ia_flags;
E 3
I 3
#define	ia_flags	ia_ifa.ifa_flags
E 3
I 2
	int					ia_snpaoffset;
E 2
	struct iso_ifaddr	*ia_next;	/* next in list of iso addresses */
I 2
	struct	sockaddr_iso ia_addr;	/* reserve space for interface name */
	struct	sockaddr_iso ia_dstaddr; /* reserve space for broadcast addr */
#define	ia_broadaddr	ia_dstaddr
	struct	sockaddr_iso ia_sockmask; /* reserve space for general netmask */
E 2
};
D 2
#define ia_ifp		ia_ifa.ifa_ifp
#ifndef ia_addr
#define ia_addr		ia_ifa.ifa_addr
#endif	ia_addr
E 2

I 2
struct	iso_aliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_iso ifra_addr;
	struct	sockaddr_iso ifra_dstaddr;
	struct	sockaddr_iso ifra_mask;
	int	ifra_snpaoffset;
};

struct	iso_ifreq {
	char	ifr_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_iso ifr_Addr;
};

E 2
/*
 *	Given a pointer to an iso_ifaddr (ifaddr),
 *	return a pointer to the addr as a sockaddr_iso
 */
D 2
#define	IA_SIS(ia)\
	((struct sockaddr_iso *)(&((struct iso_ifaddr *)ia)->ia_addr))
E 2
I 2
/*
#define	IA_SIS(ia) ((struct sockaddr_iso *)(ia.ia_ifa->ifa_addr))
 * works if sockaddr_iso becomes variable sized.
 */
#define	IA_SIS(ia) (&(((struct iso_ifaddr *)ia)->ia_addr))
E 2

D 2
#ifndef	IFA_ROUTE
#define	IFA_ROUTE	0x01			/* routing entry installed */
#endif	IFA_ROUTE
E 2
I 2
#define	SIOCDIFADDR_ISO	_IOW('i',25, struct iso_ifreq)	/* delete IF addr */
#define	SIOCAIFADDR_ISO	_IOW('i',26, struct iso_aliasreq)/* add/chg IFalias */
#define	SIOCGIFADDR_ISO	_IOWR('i',33, struct iso_ifreq)	/* get ifnet address */
#define	SIOCGIFDSTADDR_ISO _IOWR('i',34, struct iso_ifreq) /* get dst address */
#define	SIOCGIFNETMASK_ISO _IOWR('i',37, struct iso_ifreq) /* get dst address */
E 2

I 2
D 3
#ifndef IFA_ROUTE
#define	IFA_ROUTE	0x01		/* routing entry installed */
#endif

/* ISO arp IOCTL data structures */
struct arpreq_iso {
	int	arp_flags;			/* flags */
	struct	sockaddr_iso arp_pa;		/* protocol address */
	struct	sockaddr arp_ha;		/* hardware address */
};

#define	SIOCSISOMAP	_IOW('a',30, struct arpreq_iso)	/* set arp entry */
#define	SIOCGISOMAP	_IOWR('a',38, struct arpreq_iso)/* get arp entry */
#define	SIOCDISOMAP	_IOW('a',31, struct arpreq_iso)	/* delete arp entry */
E 3
/*
 * This stuff should go in if.h or if_llc.h or someplace else,
 * but for now . . .
 */

struct llc_etherhdr {
	char dst[6];
	char src[6];
	char len[2];
	char llc_dsap;
	char llc_ssap;
	char llc_ui_byte;
};

struct snpa_hdr {
	struct	ifnet *snh_ifp;
	char	snh_dhost[6];
	char	snh_shost[6];
	short	snh_flags;
};
E 2
#ifdef KERNEL
struct iso_ifaddr	*iso_ifaddr;	/* linked list of iso address ifaces */
I 2
struct iso_ifaddr	*iso_localifa();	/* linked list of iso address ifaces */
E 2
struct ifqueue 		clnlintrq;		/* clnl packet input queue */
D 6
#endif KERNEL
E 6
I 6
#endif /* KERNEL */
E 6
E 1
