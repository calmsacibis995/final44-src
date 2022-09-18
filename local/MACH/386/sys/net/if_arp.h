/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_arp.h,v $
 * Revision 2.5  89/03/09  20:39:05  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  18:53:59  gm0w
 * 	Updated copyright.  Removed CMUCS/SUN_RPC conditionals.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.3  89/01/18  00:52:23  jsb
 * 	Merged in NeXT SUN_RPC changes.
 * 	[89/01/17  10:37:19  jsb]
 * 
 * Revision 2.2  88/08/24  01:53:29  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:09:07  mwyoung]
 * 
 * 20-Oct-87  Peter King (king) at NeXT, Inc.
 *	SUN_RPC:  Added Sun's RARP support.
 *
 * 24-Aug-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Added ARPHRD_802 definition from 4.3 ACIS to support new lan
 *	driver.
 *
 * 20-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_INET:  Added ARPHRD_XETHER definition.
 *
 */
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)if_arp.h	7.1 (Berkeley) 6/4/86
 */

/*
 * Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  ARP packets are variable
 * in size; the arphdr structure defines the fixed-length portion.
 * Protocol type values are the same as those for 10 Mb/s Ethernet.
 * It is followed by the variable-sized fields ar_sha, arp_spa,
 * arp_tha and arp_tpa in that order, according to the lengths
 * specified.  Field names used correspond to RFC 826.
 */
struct	arphdr {
	u_short	ar_hrd;		/* format of hardware address */
#define ARPHRD_ETHER 	1	/* ethernet hardware address */
#define ARPHRD_XETHER 	2	/* exp. ethernet hardware address */
#define ARPHRD_802 	6	/* 802 net hardware address */
	u_short	ar_pro;		/* format of protocol address */
	u_char	ar_hln;		/* length of hardware address */
	u_char	ar_pln;		/* length of protocol address */
	u_short	ar_op;		/* one of: */
#define ARPOP_REQUEST	1	/* request to resolve address */
#define ARPOP_REPLY	2	/* response to previous request */
#define REVARP_REQUEST  3	/* reverse ARP request */
#define REVARP_REPLY    4	/* reverse ARP reply */
/*
 * The remaining fields are variable in size,
 * according to the sizes above.
 */
/*	u_char	ar_sha[];	/* sender hardware address */
/*	u_char	ar_spa[];	/* sender protocol address */
/*	u_char	ar_tha[];	/* target hardware address */
/*	u_char	ar_tpa[];	/* target protocol address */
};

/*
 * ARP ioctl request
 */
struct arpreq {
	struct	sockaddr arp_pa;		/* protocol address */
	struct	sockaddr arp_ha;		/* hardware address */
	int	arp_flags;			/* flags */
};
/*  arp_flags and at_flags field values */
#define ATF_INUSE	0x01	/* entry in use */
#define ATF_COM		0x02	/* completed entry (enaddr valid) */
#define ATF_PERM	0x04	/* permanent entry */
#define ATF_PUBL	0x08	/* publish entry (respond for other host) */
#define ATF_USETRAILERS	0x10	/* has requested trailers */
