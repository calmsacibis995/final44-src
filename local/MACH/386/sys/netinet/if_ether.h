/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_ether.h,v $
 * Revision 2.7  89/03/09  20:43:10  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  18:58:10  gm0w
 * 	Updated copyright. Changed romp to ibmrt
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.5  89/01/18  00:54:04  jsb
 * 	Merged in NeXT's changes.
 * 	[89/01/17  10:44:29  jsb]
 * 
 * Revision 2.4  88/09/27  17:30:43  rvb
 * 	Fixed Log
 * 
 * Revision 2.3  88/09/27  16:06:58  rvb
 * 	Only include token ring routing on romp.
 * 	[88/09/23            rvb]
 *
 * Revision 2.2  88/08/24  01:58:39  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  18:51:36  mwyoung]
 *
 * 20-Oct-87  Peter King (king) at NeXT, Inc.
 *	SUN_RPC: Add definition for ether_addr.  Add RARP support.
 *
 * 24-Aug-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Merged in 4.3 ACIS changes to struct arptab.  These changes are
 *	required to support the new 4.3 lan protocol.
 *
 * 16-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Merged in IP Multicast code.
 *  
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 15-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_INET:  added ac_if field to arptab definition to allow
 *	multiple interfaces to co-exist.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)if_ether.h	7.1 (Berkeley) 6/5/86
 */
 
#ifndef	_ETHER_ADDR_
#define _ETHER_ADDR_
/*
 * Ethernet address - 6 octets
 */
struct ether_addr {
	u_char	ether_addr_octet[6];
};
#endif	_ETHER_ADDR_

/*
 * Structure of a 10Mb/s Ethernet header.
 */
struct	ether_header {
	u_char	ether_dhost[6];
	u_char	ether_shost[6];
	u_short	ether_type;
};

#define ETHERTYPE_PUP	0x0200		/* PUP protocol */
#define ETHERTYPE_IP	0x0800		/* IP protocol */
#define ETHERTYPE_ARP	0x0806		/* Addr. resolution protocol */
#define ETHERTYPE_REVARP 0x8035		/* Reverse ARP */

/*
 * The ETHERTYPE_NTRAILER packet types starting at ETHERTYPE_TRAIL have
 * (type-ETHERTYPE_TRAIL)*512 bytes of data followed
 * by an ETHER type (as given above) and then the (variable-length) header.
 */
#define ETHERTYPE_TRAIL		0x1000		/* Trailer packet */
#define ETHERTYPE_NTRAILER	16

#define ETHERMTU	1500
#define ETHERMIN	(60-14)

#define ETHER_IP_MULTICAST0 0x09 /* high-order 3 bytes of ethernet address  */
#define ETHER_IP_MULTICAST1 0x00 /* for IP multicast datagrams; low 3 bytes */
#define ETHER_IP_MULTICAST2 0x56 /* are taken from destination IP address.  */
				 /* (TEMPORARY -- AWAITING OFFICIAL VALUES) */

/*
 * Ethernet Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  Structure below is adapted
 * to resolving internet addresses.  Field names used correspond to 
 * RFC 826.
 */
struct	ether_arp {
	struct	arphdr ea_hdr;	/* fixed-size header */
	u_char	arp_sha[6];	/* sender hardware address */
	u_char	arp_spa[4];	/* sender protocol address */
	u_char	arp_tha[6];	/* target hardware address */
	u_char	arp_tpa[4];	/* target protocol address */
};
#define arp_hrd	ea_hdr.ar_hrd
#define arp_pro	ea_hdr.ar_pro
#define arp_hln	ea_hdr.ar_hln
#define arp_pln	ea_hdr.ar_pln
#define arp_op	ea_hdr.ar_op


/*
 * Structure shared between the ethernet driver modules and
 * the address resolution code.  For example, each ec_softc or il_softc
 * begins with this structure.
 */
struct	arpcom {
	struct 	ifnet ac_if;		/* network-visible interface */
	u_char	ac_enaddr[6];		/* ethernet hardware address */
	struct in_addr ac_ipaddr;	/* copy of ip address- XXX */
};

/*
 * Internet to ethernet address resolution table.
 */
struct	arptab {
	struct	in_addr at_iaddr;	/* internet address */
	u_char	at_enaddr[6];		/* ethernet address */
	u_char	at_timer;		/* minutes since last reference */
	u_char	at_flags;		/* flags */
	struct	mbuf *at_hold;		/* last packet until resolved/timeout */
	struct  ifnet *at_if;		/* interface */
#ifdef	ibmrt
	u_short at_rcf;			/* token ring routing control field */
	u_short at_rseg[8];		/* token ring routing segments */
#endif	ibmrt
};

#ifdef	KERNEL
u_char etherbroadcastaddr[6];
struct	arptab *arptnew();
char *ether_sprintf();
#endif
